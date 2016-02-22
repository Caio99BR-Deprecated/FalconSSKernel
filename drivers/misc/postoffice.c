/* Copyright (C) 2013-2014 HuizeWeng@Arimacomm
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/module.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/postoffice.h>
#include <linux/fb.h>

DECLARE_RWSEM(postoffice_list_lock);
LIST_HEAD(postoffice_list);

DECLARE_RWSEM(postoffice_timerPackage_list_lock);
LIST_HEAD(postoffice_timerPackage_list);

DECLARE_RWSEM(postoffice_deliverPackage_list_lock);
LIST_HEAD(postoffice_deliverPackage_list);

#define __BIN_ATTR(name_, mode_, size_, private_, read_, write_) { \
		.attr    = { .name = __stringify(name_), .mode = mode_ }, \
		.size    = size_, \
		.private = private_, \
		.read    = read_, \
		.write   = write_, \
}

typedef struct Postman{
	atomic_t		refresh;
	Package			package;
	struct mutex	mutex;
}Postman;

typedef struct TimerPackage{
	Package				package;
	struct delayed_work	dwork;
	struct list_head	node;
}TimerPackage;

typedef struct AddressNode{
	deliverAddress*		address;
	struct list_head	node;
}AddressNode;

typedef struct Postoffice{
	struct class*				class;
	struct device*				device;
	wait_queue_head_t			event;
	Postman						postman;
	atomic_t					readToGo;
	atomic_t					systemPermission;
	struct notifier_block		notifier;
	struct workqueue_struct*	wq;
}Postoffice;

static Postoffice* pOffice = NULL;

/**
 * To deliver the package to mailbox with task process
 */
static void postoffice_deliverPackage(struct work_struct* work)
{
	TimerPackage* tPackage = NULL;
	down_write(&postoffice_deliverPackage_list_lock);
	list_for_each_entry(tPackage, &postoffice_deliverPackage_list, node){
		if(&(tPackage->dwork.work) == work){
			list_del_init(&tPackage->node);
			list_del_init(&tPackage->dwork.work.entry);
			break;
		}
	}
	up_write(&postoffice_deliverPackage_list_lock);
	if(tPackage){
		AddressNode* addressNode = NULL;
		AddressNode* tmpNode = NULL;
		const Package* package = &tPackage->package;
		down_read(&postoffice_list_lock);
		list_for_each_entry_safe(addressNode, tmpNode, &postoffice_list, node){
			deliverAddress* address = addressNode->address;
			if(!IS_ERR_OR_NULL(address)){
				bool deliver = (package->category == InnerInterrupt);
				deliver |= (package->category & address->receivedCategory);
				if(deliver && address->mailbox){
					address->mailbox(package);
				}
			}else{
				// Remove garbage node
				list_del_init(&addressNode->node);
				kfree(addressNode);
			}
		}
		up_read(&postoffice_list_lock);
		kfree(tPackage);
	}
}

/**
 * Scheduled the package such that delivering the package to mailbox of registered
 */
static void postoffice_schedulingPackage(const Package* package, const unsigned int msleep)
{
	TimerPackage* tPackage = kzalloc(sizeof(TimerPackage), GFP_KERNEL);
	memcpy(&tPackage->package, package, sizeof(Package));
	INIT_DELAYED_WORK(&tPackage->dwork, postoffice_deliverPackage);
	down_write(&postoffice_deliverPackage_list_lock);
	list_add_tail(&tPackage->node, &postoffice_deliverPackage_list);
	up_write(&postoffice_deliverPackage_list_lock);
	queue_delayed_work(pOffice->wq, &tPackage->dwork, msecs_to_jiffies(msleep));
}

/**
 * To send the event of InnerInterrupt to inform listerner
 */
static void postoffice_sendInterrupt(void)
{
	Package package = {
		.category = InnerInterrupt,
	};
	postoffice_schedulingPackage(&package, 0);
	atomic_set(&pOffice->readToGo, 0);
	flush_workqueue(pOffice->wq);
}

static bool postoffice_classifyPackage(const Package* package)
{
	bool state = true;
	switch(package->category){
		case InnerInterrupt:
			atomic_set(&pOffice->readToGo, 0);
			break;
		case ReadyToWork:
			// This is Postoffice's communicates protocol,
			// it needs to send event of ReadyToWork to user space 
			atomic_set(&pOffice->systemPermission, 1);
			postoffice_sendPackageDelayed(package, 0);
			break;
		case AllPackage:
			state = false;
			break;
		default:
			if(!atomic_read(&pOffice->readToGo)){
				state = false;
			}
			break;
	}
	return state;
}

static ssize_t postoffice_receive(struct file* file, struct kobject* kobj, struct bin_attribute* attr, char* buf, loff_t pos, size_t size)
{
	Postman* postman = &pOffice->postman;
	if(0 == wait_event_interruptible(pOffice->event, (atomic_read(&postman->refresh) == 1))){
		memcpy(buf, &postman->package, sizeof(Package));
	}else{
		// It means system was interrupted
		postoffice_sendInterrupt();
		memset(buf, 0, sizeof(Package));
	}	
	atomic_set(&postman->refresh, 0);
	wake_up(&pOffice->event);
	return sizeof(Package);
}

static ssize_t postoffice_deliver(struct file* file,struct kobject* kobj, struct bin_attribute* attr, char* buf, loff_t pos, size_t size)
{
	const Package* package = (Package *) buf;
	if(postoffice_classifyPackage(package) && pOffice->wq){
		postoffice_schedulingPackage(package, 0);
	}
	return sizeof(Package);
}

static int postoffice_suspend(void)
{
	flush_workqueue(pOffice->wq);
	return 0;
}

static int postoffice_resume(void)
{
	return 0;
}

static struct device_attribute postoffice_class_attrs[] = {
	__ATTR_NULL,
};

static struct bin_attribute postoffice_class_bin_attrs[] = {
	__BIN_ATTR(deliver, 0220, sizeof(Package), NULL, NULL, postoffice_deliver),
	__BIN_ATTR(receive, 0440, sizeof(Package), NULL, postoffice_receive, NULL),
	__ATTR_NULL,
};

static void postoffice_timerAlarm(struct work_struct* work)
{
	TimerPackage* tPackage = NULL;
	down_write(&postoffice_timerPackage_list_lock);
	list_for_each_entry(tPackage, &postoffice_timerPackage_list, node){
		if(&(tPackage->dwork.work) == work){
			list_del_init(&tPackage->node);
			list_del_init(&tPackage->dwork.work.entry);
			break;
		}
	}
	up_write(&postoffice_timerPackage_list_lock);
	if(tPackage){
		postoffice_sendPackage(&tPackage->package);
		kfree(tPackage);
	}
}

static bool postoffice_waitProcess(const Package* package)
{
	Postman* postman = &pOffice->postman;
	bool sucessful = false;
	mutex_lock(&(postman->mutex));
	// Add package wait for being processed
	memcpy(&(postman->package), package, sizeof(Package));
	atomic_set(&postman->refresh, 1);
	wake_up(&pOffice->event);
	sucessful = (wait_event_timeout(pOffice->event, (atomic_read(&postman->refresh) == 0), msecs_to_jiffies(3000)) > 0);
	memset(&(postman->package), 0, sizeof(Package));
	atomic_set(&postman->refresh, 0);
	wake_up(&pOffice->event);
	mutex_unlock(&(postman->mutex));
	return sucessful;
}

/**
 * To send local package with task process
 * Note that max msleep should be less than 30000
 */
void postoffice_sendLocalPackageDelayed(const Package * package, const unsigned int msleep)
{
	if(!package || !pOffice || !pOffice->wq){
        return;
	}
	switch(package->category){
		case InnerInterrupt:
		case ReadyToWork:
		case AllPackage:
			return;
		default:
			break;
	}
	postoffice_schedulingPackage(package, ((msleep <= 30000) ? msleep : 30000));
}
EXPORT_SYMBOL_GPL(postoffice_sendLocalPackageDelayed);

/**
 * To send package with task process
 * Note that max msleep should be less than 30000
 */
void postoffice_sendPackageDelayed(const Package* package, const unsigned int msleep)
{
	TimerPackage* tPackage = NULL;
	if(!package || !pOffice || !pOffice->wq){
		return;
	}
	tPackage = kzalloc(sizeof(TimerPackage), GFP_KERNEL);
	memcpy(&tPackage->package, package, sizeof(Package));
	INIT_DELAYED_WORK(&tPackage->dwork, postoffice_timerAlarm);
	down_write(&postoffice_timerPackage_list_lock);
	list_add_tail(&tPackage->node, &postoffice_timerPackage_list);
	up_write(&postoffice_timerPackage_list_lock);
	queue_delayed_work(pOffice->wq, &tPackage->dwork, msecs_to_jiffies((msleep <= 30000) ? msleep : 30000));
}
EXPORT_SYMBOL_GPL(postoffice_sendPackageDelayed);

/**
 * To send package directly,
 * it will be block until Completed or Timeout.
 * Note that it will put in queue for re-sending,
 * if service has not ready.
 */
void postoffice_sendPackage(const Package* package)
{
	Postman* postman = (pOffice) ? &pOffice->postman : NULL;
	bool sucessful = false;
	if(!package|| !postman){
		return;
	}
	switch(package->category){
		case InnerInterrupt:
		case ReadyToWork:
			if(!atomic_read(&pOffice->systemPermission)){
				return;
			}
			atomic_set(&pOffice->systemPermission, 0);
			break;
		case AllPackage:
			return;
		default :
			if(!atomic_read(&pOffice->readToGo)){
				postoffice_sendPackageDelayed(package, 5000);
				pr_warning("%s, postoffice service hasn't ready re-sent at 5 secs later", __func__);
				return;
			}
			break;
	}
	sucessful = postoffice_waitProcess(package);
	if(sucessful && ReadyToWork == package->category){
		atomic_set(&pOffice->readToGo, 1);
	}
}
EXPORT_SYMBOL_GPL(postoffice_sendPackage);

/**
 * To register the mailbox address,
 * it will receive the package what you want
 */
int postoffice_registerAddress(deliverAddress* address)
{
	bool find = false;
	AddressNode* addressNode = NULL;
	if(IS_ERR_OR_NULL(address)){
		return -1;
	}
	/* add to the list of postoffice */
	down_write(&postoffice_list_lock);
	list_for_each_entry(addressNode, &postoffice_list, node){
		if(addressNode->address == address){
			find = true;
			break;
		}
	}
	if(!find){
		addressNode = kzalloc(sizeof(AddressNode), GFP_KERNEL);
		addressNode->address = address;
		list_add_tail(&addressNode->node, &postoffice_list);
	}
	up_write(&postoffice_list_lock);
	return 0;
}
EXPORT_SYMBOL_GPL(postoffice_registerAddress);

/**
 * To unregister the mailbox address, 
 * it will stop receiving the package
 */
void postoffice_unregisterAddress(deliverAddress* address)
{
	AddressNode* addressNode = NULL;
	if(IS_ERR_OR_NULL(address)){
		return;
	}
	down_write(&postoffice_list_lock);
	list_for_each_entry(addressNode, &postoffice_list, node){
		if(addressNode->address == address){
			list_del_init(&addressNode->node);
			kfree(addressNode);
			break;
		}
	}
	up_write(&postoffice_list_lock);
}
EXPORT_SYMBOL_GPL(postoffice_unregisterAddress);

static int postoffice_notify(struct notifier_block* self, unsigned long event, void* data)
{
	struct fb_event* evdata = data;
	if(evdata && evdata->data && event == FB_EVENT_BLANK){
		int* state = (int *) evdata->data;
		switch(*state){
			case FB_BLANK_POWERDOWN:
				return postoffice_suspend();
			case FB_BLANK_UNBLANK:
				return postoffice_resume();
			default:
				break;
		}
	}
	return 0;
}

static int __init postoffice_init(void)
{
	struct class* cls = class_create(THIS_MODULE, "postoffice");
	if(IS_ERR(cls)){
		return PTR_ERR(cls);
	}
	cls->dev_attrs = postoffice_class_attrs;
	cls->dev_bin_attrs = postoffice_class_bin_attrs;
	pOffice = kzalloc(sizeof(Postoffice), GFP_KERNEL);
	if(!pOffice){
		class_destroy(cls);
		return -ENOMEM;
	}
	pOffice->class = cls;
	pOffice->device = device_create(cls, NULL, 0, pOffice, "%s", "postman");
	pOffice->wq = create_singlethread_workqueue("postoffice");
	pOffice->notifier.notifier_call = postoffice_notify;
	mutex_init(&(pOffice->postman.mutex));
	init_waitqueue_head(&pOffice->event);
	fb_register_client(&pOffice->notifier);
	return 0;
}

static void __exit postoffice_exit(void)
{
	down_write(&postoffice_timerPackage_list_lock);
	{
		TimerPackage* tPackage = NULL;
		tPackage = list_first_entry(&postoffice_timerPackage_list, TimerPackage, node);
		while(tPackage && !list_empty(&tPackage->node)){
			cancel_delayed_work_sync(&tPackage->dwork);
			list_del_init(&tPackage->node);
			kfree(tPackage);
			tPackage = list_first_entry(&postoffice_timerPackage_list, TimerPackage, node);
		}
	}
	up_write(&postoffice_timerPackage_list_lock);
	down_write(&postoffice_list_lock);
	{
		AddressNode* addressNode = NULL;
		AddressNode* tmpNode = NULL;
		list_for_each_entry_safe(addressNode, tmpNode, &postoffice_list, node){
			list_del_init(&addressNode->node);
			kfree(addressNode);
		}
	}
	up_write(&postoffice_list_lock);
	flush_workqueue(pOffice->wq);
	destroy_workqueue(pOffice->wq);
	pOffice->wq = NULL;
	fb_unregister_client(&pOffice->notifier);
	device_unregister(pOffice->device);
	class_destroy(pOffice->class);
	kfree(pOffice);
}

subsys_initcall(postoffice_init);
module_exit(postoffice_exit);

MODULE_DESCRIPTION("Huize Weng");
MODULE_LICENSE("GPLv2");
MODULE_ALIAS("Postoffice Interface");
