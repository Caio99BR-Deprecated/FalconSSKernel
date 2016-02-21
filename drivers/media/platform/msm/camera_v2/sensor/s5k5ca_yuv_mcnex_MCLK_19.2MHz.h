//****************************************/
//****************************************/
//=================================================================================================
// * Name: S5K5CAGX EVT1.0 Initial Setfile
// * PLL mode: MCLK=24MHz / SYSCLK=30MHz / PCLK=60MHz
// * FPS : Preview YUV QXGA 7.5fps / Capture YUV QXGA 7.5fps
// * Analog and TnP modified(20100225)
//=================================================================================================
// ARM GO
// Direct mode
//{0xFCFC, 0xD000 },
//{0x0010, 0x0001 }, //Reset
//{0x1030, 0x0000 }, //Clear host interrupt so main will wait
//{0x0014, 0x0001 ,16,10}, //ARM go
//p10 //Min.10ms delay is required

// Start T&P part
// DO NOT DELETE T&P SECTION COMMENTS! They are required to debug T&P related issues.
// svn://transrdsrv/svn/svnroot/System/Software/tcevb/SDK+FW/ISP_5CA/Firmware
// Rev: WC
// Signature:
// md5 b093df4c68b392b85938fb2d5d1a3ed8 .btp
// md5 4013ff93e02c5ca42ee80f5d436679cb .htp
// md5 8c46487f45dee2566f9a04abe3fd8f52 .RegsMap.h
// md5 90230b6b3e71c02e34af139b81219a11 .RegsMap.bin
// md5 506b4144bd48cdb79cbecdda4f7176ba .base.RegsMap.h
// md5 fd8f92f13566c1a788746b23691c5f5f .base.RegsMap.bin
//
{0x0028, 0x7000 },
{0x002A, 0x2CF8 },
{0x0F12, 0xB510 },
{0x0F12, 0x4827 },
{0x0F12, 0x21C0 },
{0x0F12, 0x8041 },
{0x0F12, 0x4825 },
{0x0F12, 0x4A26 },
{0x0F12, 0x3020 },
{0x0F12, 0x8382 },
{0x0F12, 0x1D12 },
{0x0F12, 0x83C2 },
{0x0F12, 0x4822 },
{0x0F12, 0x3040 },
{0x0F12, 0x8041 },
{0x0F12, 0x4821 },
{0x0F12, 0x4922 },
{0x0F12, 0x3060 },
{0x0F12, 0x8381 },
{0x0F12, 0x1D09 },
{0x0F12, 0x83C1 },
{0x0F12, 0x4821 },
{0x0F12, 0x491D },
{0x0F12, 0x8802 },
{0x0F12, 0x3980 },
{0x0F12, 0x804A },
{0x0F12, 0x8842 },
{0x0F12, 0x808A },
{0x0F12, 0x8882 },
{0x0F12, 0x80CA },
{0x0F12, 0x88C2 },
{0x0F12, 0x810A },
{0x0F12, 0x8902 },
{0x0F12, 0x491C },
{0x0F12, 0x80CA },
{0x0F12, 0x8942 },
{0x0F12, 0x814A },
{0x0F12, 0x8982 },
{0x0F12, 0x830A },
{0x0F12, 0x89C2 },
{0x0F12, 0x834A },
{0x0F12, 0x8A00 },
{0x0F12, 0x4918 },
{0x0F12, 0x8188 },
{0x0F12, 0x4918 },
{0x0F12, 0x4819 },
{0x0F12, 0xF000 },
{0x0F12, 0xFA0C },
{0x0F12, 0x4918 },
{0x0F12, 0x4819 },
{0x0F12, 0x6341 },
{0x0F12, 0x4919 },
{0x0F12, 0x4819 },
{0x0F12, 0xF000 },
{0x0F12, 0xFA05 },
{0x0F12, 0x4816 },
{0x0F12, 0x4918 },
{0x0F12, 0x3840 },
{0x0F12, 0x62C1 },
{0x0F12, 0x4918 },
{0x0F12, 0x3880 },
{0x0F12, 0x63C1 },
{0x0F12, 0x4917 },
{0x0F12, 0x6301 },
{0x0F12, 0x4917 },
{0x0F12, 0x3040 },
{0x0F12, 0x6181 },
{0x0F12, 0x4917 },
{0x0F12, 0x4817 },
{0x0F12, 0xF000 },
{0x0F12, 0xF9F5 },
{0x0F12, 0x4917 },
{0x0F12, 0x4817 },
{0x0F12, 0xF000 },
{0x0F12, 0xF9F1 },
{0x0F12, 0x4917 },
{0x0F12, 0x4817 },
{0x0F12, 0xF000 },
{0x0F12, 0xF9ED },
{0x0F12, 0xBC10 },
{0x0F12, 0xBC08 },
{0x0F12, 0x4718 },
{0x0F12, 0x1100 },
{0x0F12, 0xD000 },
{0x0F12, 0x267C },
{0x0F12, 0x0000 },
{0x0F12, 0x2CE8 },
{0x0F12, 0x0000 },
{0x0F12, 0x3274 },
{0x0F12, 0x7000 },
{0x0F12, 0xF400 },
{0x0F12, 0xD000 },
{0x0F12, 0xF520 },
{0x0F12, 0xD000 },
{0x0F12, 0x2DF1 },
{0x0F12, 0x7000 },
{0x0F12, 0x89A9 },
{0x0F12, 0x0000 },
{0x0F12, 0x2E43 },
{0x0F12, 0x7000 },
{0x0F12, 0x0140 },
{0x0F12, 0x7000 },
{0x0F12, 0x2E75 },
{0x0F12, 0x7000 },
{0x0F12, 0xB4F7 },
{0x0F12, 0x0000 },
{0x0F12, 0x2EFF },
{0x0F12, 0x7000 },
{0x0F12, 0x2F23 },
{0x0F12, 0x7000 },
{0x0F12, 0x2FCD },
{0x0F12, 0x7000 },
{0x0F12, 0x2FE1 },
{0x0F12, 0x7000 },
{0x0F12, 0x2FB5 },
{0x0F12, 0x7000 },
{0x0F12, 0x013D },
{0x0F12, 0x0001 },
{0x0F12, 0x3067 },
{0x0F12, 0x7000 },
{0x0F12, 0x5823 },
{0x0F12, 0x0000 },
{0x0F12, 0x30B5 },
{0x0F12, 0x7000 },
{0x0F12, 0xD789 },
{0x0F12, 0x0000 },
{0x0F12, 0xB570 },
{0x0F12, 0x6804 },
{0x0F12, 0x6845 },
{0x0F12, 0x6881 },
{0x0F12, 0x6840 },
{0x0F12, 0x2900 },
{0x0F12, 0x6880 },
{0x0F12, 0xD007 },
{0x0F12, 0x49C2 },
{0x0F12, 0x8949 },
{0x0F12, 0x084A },
{0x0F12, 0x1880 },
{0x0F12, 0xF000 },
{0x0F12, 0xF9B8 },
{0x0F12, 0x80A0 },
{0x0F12, 0xE000 },
{0x0F12, 0x80A0 },
{0x0F12, 0x88A0 },
{0x0F12, 0x2800 },
{0x0F12, 0xD010 },
{0x0F12, 0x68A9 },
{0x0F12, 0x6828 },
{0x0F12, 0x084A },
{0x0F12, 0x1880 },
{0x0F12, 0xF000 },
{0x0F12, 0xF9AC },
{0x0F12, 0x8020 },
{0x0F12, 0x1D2D },
{0x0F12, 0xCD03 },
{0x0F12, 0x084A },
{0x0F12, 0x1880 },
{0x0F12, 0xF000 },
{0x0F12, 0xF9A5 },
{0x0F12, 0x8060 },
{0x0F12, 0xBC70 },
{0x0F12, 0xBC08 },
{0x0F12, 0x4718 },
{0x0F12, 0x2000 },
{0x0F12, 0x8060 },
{0x0F12, 0x8020 },
{0x0F12, 0xE7F8 },
{0x0F12, 0xB510 },
{0x0F12, 0xF000 },
{0x0F12, 0xF9A0 },
{0x0F12, 0x48B1 },
{0x0F12, 0x49B2 },
{0x0F12, 0x8800 },
{0x0F12, 0x4AB2 },
{0x0F12, 0x2805 },
{0x0F12, 0xD003 },
{0x0F12, 0x4BB1 },
{0x0F12, 0x795B },
{0x0F12, 0x2B00 },
{0x0F12, 0xD005 },
{0x0F12, 0x2001 },
{0x0F12, 0x8008 },
{0x0F12, 0x8010 },
{0x0F12, 0xBC10 },
{0x0F12, 0xBC08 },
{0x0F12, 0x4718 },
{0x0F12, 0x2800 },
{0x0F12, 0xD1FA },
{0x0F12, 0x2000 },
{0x0F12, 0x8008 },
{0x0F12, 0x8010 },
{0x0F12, 0xE7F6 },
{0x0F12, 0xB5F8 },
{0x0F12, 0x2407 },
{0x0F12, 0x2C06 },
{0x0F12, 0xD035 },
{0x0F12, 0x2C07 },
{0x0F12, 0xD033 },
{0x0F12, 0x48A3 },
{0x0F12, 0x8BC1 },
{0x0F12, 0x2900 },
{0x0F12, 0xD02A },
{0x0F12, 0x00A2 },
{0x0F12, 0x1815 },
{0x0F12, 0x4AA4 },
{0x0F12, 0x6DEE },
{0x0F12, 0x8A92 },
{0x0F12, 0x4296 },
{0x0F12, 0xD923 },
{0x0F12, 0x0028 },
{0x0F12, 0x3080 },
{0x0F12, 0x0007 },
{0x0F12, 0x69C0 },
{0x0F12, 0xF000 },
{0x0F12, 0xF96D },
{0x0F12, 0x1C71 },
{0x0F12, 0x0280 },
{0x0F12, 0xF000 },
{0x0F12, 0xF969 },
{0x0F12, 0x0006 },
{0x0F12, 0x4898 },
{0x0F12, 0x0061 },
{0x0F12, 0x1808 },
{0x0F12, 0x8D80 },
{0x0F12, 0x0A01 },
{0x0F12, 0x0600 },
{0x0F12, 0x0E00 },
{0x0F12, 0x1A08 },
{0x0F12, 0xF000 },
{0x0F12, 0xF96C },
{0x0F12, 0x0002 },
{0x0F12, 0x6DE9 },
{0x0F12, 0x6FE8 },
{0x0F12, 0x1A08 },
{0x0F12, 0x4351 },
{0x0F12, 0x0300 },
{0x0F12, 0x1C49 },
{0x0F12, 0xF000 },
{0x0F12, 0xF955 },
{0x0F12, 0x0401 },
{0x0F12, 0x0430 },
{0x0F12, 0x0C00 },
{0x0F12, 0x4301 },
{0x0F12, 0x61F9 },
{0x0F12, 0xE004 },
{0x0F12, 0x00A2 },
{0x0F12, 0x4990 },
{0x0F12, 0x1810 },
{0x0F12, 0x3080 },
{0x0F12, 0x61C1 },
{0x0F12, 0x1E64 },
{0x0F12, 0xD2C5 },
{0x0F12, 0x2006 },
{0x0F12, 0xF000 },
{0x0F12, 0xF95B },
{0x0F12, 0x2007 },
{0x0F12, 0xF000 },
{0x0F12, 0xF958 },
{0x0F12, 0xBCF8 },
{0x0F12, 0xBC08 },
{0x0F12, 0x4718 },
{0x0F12, 0xB510 },
{0x0F12, 0xF000 },
{0x0F12, 0xF95A },
{0x0F12, 0x2800 },
{0x0F12, 0xD00A },
{0x0F12, 0x4881 },
{0x0F12, 0x8B81 },
{0x0F12, 0x0089 },
{0x0F12, 0x1808 },
{0x0F12, 0x6DC1 },
{0x0F12, 0x4883 },
{0x0F12, 0x8A80 },
{0x0F12, 0x4281 },
{0x0F12, 0xD901 },
{0x0F12, 0x2001 },
{0x0F12, 0xE7A1 },
{0x0F12, 0x2000 },
{0x0F12, 0xE79F },
{0x0F12, 0xB5F8 },
{0x0F12, 0x0004 },
{0x0F12, 0x4F80 },
{0x0F12, 0x227D },
{0x0F12, 0x8938 },
{0x0F12, 0x0152 },
{0x0F12, 0x4342 },
{0x0F12, 0x487E },
{0x0F12, 0x9000 },
{0x0F12, 0x8A01 },
{0x0F12, 0x0848 },
{0x0F12, 0x1810 },
{0x0F12, 0xF000 },
{0x0F12, 0xF91F },
{0x0F12, 0x210F },
{0x0F12, 0xF000 },
{0x0F12, 0xF942 },
{0x0F12, 0x497A },
{0x0F12, 0x8C49 },
{0x0F12, 0x090E },
{0x0F12, 0x0136 },
{0x0F12, 0x4306 },
{0x0F12, 0x4979 },
{0x0F12, 0x2C00 },
{0x0F12, 0xD003 },
{0x0F12, 0x2001 },
{0x0F12, 0x0240 },
{0x0F12, 0x4330 },
{0x0F12, 0x8108 },
{0x0F12, 0x4876 },
{0x0F12, 0x2C00 },
{0x0F12, 0x8D00 },
{0x0F12, 0xD001 },
{0x0F12, 0x2501 },
{0x0F12, 0xE000 },
{0x0F12, 0x2500 },
{0x0F12, 0x4972 },
{0x0F12, 0x4328 },
{0x0F12, 0x8008 },
{0x0F12, 0x207D },
{0x0F12, 0x00C0 },
{0x0F12, 0xF000 },
{0x0F12, 0xF930 },
{0x0F12, 0x2C00 },
{0x0F12, 0x496E },
{0x0F12, 0x0328 },
{0x0F12, 0x4330 },
{0x0F12, 0x8108 },
{0x0F12, 0x88F8 },
{0x0F12, 0x2C00 },
{0x0F12, 0x01AA },
{0x0F12, 0x4310 },
{0x0F12, 0x8088 },
{0x0F12, 0x2C00 },
{0x0F12, 0xD00B },
{0x0F12, 0x9800 },
{0x0F12, 0x8A01 },
{0x0F12, 0x4869 },
{0x0F12, 0xF000 },
{0x0F12, 0xF8F1 },
{0x0F12, 0x4969 },
{0x0F12, 0x8809 },
{0x0F12, 0x4348 },
{0x0F12, 0x0400 },
{0x0F12, 0x0C00 },
{0x0F12, 0xF000 },
{0x0F12, 0xF918 },
{0x0F12, 0x0020 },
{0x0F12, 0xF000 },
{0x0F12, 0xF91D },
{0x0F12, 0x4865 },
{0x0F12, 0x7004 },
{0x0F12, 0xE7A1 },
{0x0F12, 0xB510 },
{0x0F12, 0x0004 },
{0x0F12, 0xF000 },
{0x0F12, 0xF91E },
{0x0F12, 0x6020 },
{0x0F12, 0x4962 },
{0x0F12, 0x8B49 },
{0x0F12, 0x0789 },
{0x0F12, 0xD001 },
{0x0F12, 0x0040 },
{0x0F12, 0x6020 },
{0x0F12, 0xE74A },
{0x0F12, 0xB510 },
{0x0F12, 0xF000 },
{0x0F12, 0xF91B },
{0x0F12, 0x485E },
{0x0F12, 0x8880 },
{0x0F12, 0x0601 },
{0x0F12, 0x4853 },
{0x0F12, 0x1609 },
{0x0F12, 0x8141 },
{0x0F12, 0xE740 },
{0x0F12, 0xB5F8 },
{0x0F12, 0x000F },
{0x0F12, 0x4C54 },
{0x0F12, 0x3420 },
{0x0F12, 0x2500 },
{0x0F12, 0x5765 },
{0x0F12, 0x0039 },
{0x0F12, 0xF000 },
{0x0F12, 0xF913 },
{0x0F12, 0x9000 },
{0x0F12, 0x2600 },
{0x0F12, 0x57A6 },
{0x0F12, 0x4C4B },
{0x0F12, 0x42AE },
{0x0F12, 0xD01B },
{0x0F12, 0x4D53 },
{0x0F12, 0x8AE8 },
{0x0F12, 0x2800 },
{0x0F12, 0xD013 },
{0x0F12, 0x484C },
{0x0F12, 0x8A01 },
{0x0F12, 0x8B80 },
{0x0F12, 0x4378 },
{0x0F12, 0xF000 },
{0x0F12, 0xF8B5 },
{0x0F12, 0x89A9 },
{0x0F12, 0x1A41 },
{0x0F12, 0x484D },
{0x0F12, 0x3820 },
{0x0F12, 0x8AC0 },
{0x0F12, 0x4348 },
{0x0F12, 0x17C1 },
{0x0F12, 0x0D89 },
{0x0F12, 0x1808 },
{0x0F12, 0x1280 },
{0x0F12, 0x8961 },
{0x0F12, 0x1A08 },
{0x0F12, 0x8160 },
{0x0F12, 0xE003 },
{0x0F12, 0x88A8 },
{0x0F12, 0x0600 },
{0x0F12, 0x1600 },
{0x0F12, 0x8160 },
{0x0F12, 0x200A },
{0x0F12, 0x5E20 },
{0x0F12, 0x42B0 },
{0x0F12, 0xD011 },
{0x0F12, 0xF000 },
{0x0F12, 0xF8AB },
{0x0F12, 0x1D40 },
{0x0F12, 0x00C3 },
{0x0F12, 0x1A18 },
{0x0F12, 0x214B },
{0x0F12, 0xF000 },
{0x0F12, 0xF897 },
{0x0F12, 0x211F },
{0x0F12, 0xF000 },
{0x0F12, 0xF8BA },
{0x0F12, 0x210A },
{0x0F12, 0x5E61 },
{0x0F12, 0x0FC9 },
{0x0F12, 0x0149 },
{0x0F12, 0x4301 },
{0x0F12, 0x483C },
{0x0F12, 0x81C1 },
{0x0F12, 0x9800 },
{0x0F12, 0xE748 },
{0x0F12, 0xB5F1 },
{0x0F12, 0xB082 },
{0x0F12, 0x2500 },
{0x0F12, 0x4839 },
{0x0F12, 0x9001 },
{0x0F12, 0x2400 },
{0x0F12, 0x2028 },
{0x0F12, 0x4368 },
{0x0F12, 0x4A39 },
{0x0F12, 0x4937 },
{0x0F12, 0x1887 },
{0x0F12, 0x1840 },
{0x0F12, 0x9000 },
{0x0F12, 0x9800 },
{0x0F12, 0x0066 },
{0x0F12, 0x9A01 },
{0x0F12, 0x1980 },
{0x0F12, 0x218C },
{0x0F12, 0x5A09 },
{0x0F12, 0x8A80 },
{0x0F12, 0x8812 },
{0x0F12, 0xF000 },
{0x0F12, 0xF8CA },
{0x0F12, 0x53B8 },
{0x0F12, 0x1C64 },
{0x0F12, 0x2C14 },
{0x0F12, 0xDBF1 },
{0x0F12, 0x1C6D },
{0x0F12, 0x2D03 },
{0x0F12, 0xDBE6 },
{0x0F12, 0x9802 },
{0x0F12, 0x6800 },
{0x0F12, 0x0600 },
{0x0F12, 0x0E00 },
{0x0F12, 0xF000 },
{0x0F12, 0xF8C5 },
{0x0F12, 0xBCFE },
{0x0F12, 0xBC08 },
{0x0F12, 0x4718 },
{0x0F12, 0xB570 },
{0x0F12, 0x6805 },
{0x0F12, 0x2404 },
{0x0F12, 0xF000 },
{0x0F12, 0xF8C5 },
{0x0F12, 0x2800 },
{0x0F12, 0xD103 },
{0x0F12, 0xF000 },
{0x0F12, 0xF8C9 },
{0x0F12, 0x2800 },
{0x0F12, 0xD000 },
{0x0F12, 0x2400 },
{0x0F12, 0x3540 },
{0x0F12, 0x88E8 },
{0x0F12, 0x0500 },
{0x0F12, 0xD403 },
{0x0F12, 0x4822 },
{0x0F12, 0x89C0 },
{0x0F12, 0x2800 },
{0x0F12, 0xD002 },
{0x0F12, 0x2008 },
{0x0F12, 0x4304 },
{0x0F12, 0xE001 },
{0x0F12, 0x2010 },
{0x0F12, 0x4304 },
{0x0F12, 0x481F },
{0x0F12, 0x8B80 },
{0x0F12, 0x0700 },
{0x0F12, 0x0F81 },
{0x0F12, 0x2001 },
{0x0F12, 0x2900 },
{0x0F12, 0xD000 },
{0x0F12, 0x4304 },
{0x0F12, 0x491C },
{0x0F12, 0x8B0A },
{0x0F12, 0x42A2 },
{0x0F12, 0xD004 },
{0x0F12, 0x0762 },
{0x0F12, 0xD502 },
{0x0F12, 0x4A19 },
{0x0F12, 0x3220 },
{0x0F12, 0x8110 },
{0x0F12, 0x830C },
{0x0F12, 0xE693 },
{0x0F12, 0x0C3C },
{0x0F12, 0x7000 },
{0x0F12, 0x26E8 },
{0x0F12, 0x7000 },
{0x0F12, 0x6100 },
{0x0F12, 0xD000 },
{0x0F12, 0x6500 },
{0x0F12, 0xD000 },
{0x0F12, 0x1A7C },
{0x0F12, 0x7000 },
{0x0F12, 0x1120 },
{0x0F12, 0x7000 },
{0x0F12, 0xFFFF },
{0x0F12, 0x0000 },
{0x0F12, 0x3374 },
{0x0F12, 0x7000 },
{0x0F12, 0x1D6C },
{0x0F12, 0x7000 },
{0x0F12, 0x167C },
{0x0F12, 0x7000 },
{0x0F12, 0xF400 },
{0x0F12, 0xD000 },
{0x0F12, 0x2C2C },
{0x0F12, 0x7000 },
{0x0F12, 0x40A0 },
{0x0F12, 0x00DD },
{0x0F12, 0xF520 },
{0x0F12, 0xD000 },
{0x0F12, 0x2C29 },
{0x0F12, 0x7000 },
{0x0F12, 0x1A54 },
{0x0F12, 0x7000 },
{0x0F12, 0x1564 },
{0x0F12, 0x7000 },
{0x0F12, 0xF2A0 },
{0x0F12, 0xD000 },
{0x0F12, 0x2440 },
{0x0F12, 0x7000 },
{0x0F12, 0x3274 },
{0x0F12, 0x7000 },
{0x0F12, 0x05A0 },
{0x0F12, 0x7000 },
{0x0F12, 0x2894 },
{0x0F12, 0x7000 },
{0x0F12, 0x1224 },
{0x0F12, 0x7000 },
{0x0F12, 0xB000 },
{0x0F12, 0xD000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0x1A3F },
{0x0F12, 0x0001 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xF004 },
{0x0F12, 0xE51F },
{0x0F12, 0x1F48 },
{0x0F12, 0x0001 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0x24BD },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0x36DD },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0xB4CF },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0xB5D7 },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0x36ED },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0xF53F },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0xF5D9 },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0x013D },
{0x0F12, 0x0001 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0xF5C9 },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0xFAA9 },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0x3723 },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0x5823 },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0xD771 },
{0x0F12, 0x0000 },
{0x0F12, 0x4778 },
{0x0F12, 0x46C0 },
{0x0F12, 0xC000 },
{0x0F12, 0xE59F },
{0x0F12, 0xFF1C },
{0x0F12, 0xE12F },
{0x0F12, 0xD75B },
{0x0F12, 0x0000 },
{0x0F12, 0x7E77 },
{0x0F12, 0x0000 }, // End T&P part

{0x0028, 0x7000 }, // CIS/APS/Analog setting   
{0x002A, 0x157A },
{0x0F12, 0x0001 },
{0x002A, 0x1578 },
{0x0F12, 0x0001 },
{0x002A, 0x1576 },
{0x0F12, 0x0020 },
{0x002A, 0x1574 },
{0x0F12, 0x0006 },
{0x002A, 0x156E },
{0x0F12, 0x0001 }, // Slope calibration tolerance in units of 1/256
{0x002A, 0x1568 },
{0x0F12, 0x00FC },
{0x002A, 0x155A }, //ADC control
{0x0F12, 0x01CC }, //ADC SAT of 450mV for 10bit default in EVT1
{0x002A, 0x157E },
{0x0F12, 0x0C80 }, // 3200 Max. Reset ramp DCLK counts (default 2048 800)
{0x0F12, 0x0578 }, // 1400 Max. Reset ramp DCLK counts for x3.5
{0x002A, 0x157C },
{0x0F12, 0x0190 }, // 400 Reset ramp for x1 in DCLK counts
{0x002A, 0x1570 },
{0x0F12, 0x00A0 }, // 256 LSB
{0x0F12, 0x0010 }, // reset threshold
{0x002A, 0x12C4 },
{0x0F12, 0x006A }, // 106 additional timing columns.
{0x002A, 0x12C8 },
{0x0F12, 0x08AC }, // 2220 ADC columns in normal mode including Hold & Latch
{0x0F12, 0x0050 }, // 80 addition of ADC columns in Y-ave mode (default 244 74)
{0x002A, 0x1696 }, //WRITE #senHal_ForceModeType   0001 // Long exposure mode
{0x0F12, 0x0000 }, // based on APS guidelines
{0x0F12, 0x0000 }, // based on APS guidelines
{0x0F12, 0x00C6 }, // default. 1492 used for ADC dark characteristics
{0x0F12, 0x00C6 },
{0x002A, 0x12B8 },
{0x0F12, 0x0B00 }, //disable CINTR 0
{0x002A, 0x1690 },
{0x0F12, 0x0001 }, // when set double sampling is activated - requires different set of pointers
{0x002A, 0x12B0 },
{0x0F12, 0x0055 }, // comp and pixel bias control F40E - default for EVT1
{0x0F12, 0x005A }, // comp and pixel bias control F40E for binning mode
{0x002A, 0x337A },
{0x0F12, 0x0006 }, // [7] - is used for rest-only mode (EVT0 value is D and HW 6)
{0x0F12, 0x0068 }, // 104M
{0x002A, 0x327C },
{0x0F12, 0x1000 }, // [11]: Enable DBLR Regulation
{0x0F12, 0x6998 }, //7996// [3:0]: VPIX ~2.8V ****
{0x0F12, 0x0078 }, // [0]: Static RC-filter
{0x0F12, 0x04FE }, // [7:4]: Full RC-filter
{0x0F12, 0x8800 }, // [11]: Add load to CDS block
{0x002A, 0x3274 },
{0x0F12, 0x0155 }, //#Tune_TP_IO_DrivingCurrent_D0_D4_cs10Set IO driving current 
{0x0F12, 0x0155 }, //#Tune_TP_IO_DrivingCurrent_D9_D5_cs10Set IO driving current
{0x0F12, 0x1555 }, //#Tune_TP_IO_DrivingCurrent_GPIO_cd10 Set IO driving current
{0x0F12, 0x0FFF }, //#Tune_TP_IO_DrivingCurrent_CLKs_cd10 Set IO driving current
{0x002A, 0x169E },
{0x0F12, 0x0007 }, // [3:0]- specifies the target (default 7)- DCLK = 64MHz instead of 116MHz.
{0x002A, 0x0BF6 },
{0x0F12, 0x0000 }, //from ALEX //Enable Bayer Downscaler
{0x0028, 0x7000 }, //Asserting CDS pointers - Long exposure MS Normal
{0x002A, 0x12D2 },
{0x0F12, 0x0003 }, //#senHal_pContSenModesRegsArray[0][0]2 700012D2
{0x0F12, 0x0003 }, //#senHal_pContSenModesRegsArray[0][1]2 700012D4
{0x0F12, 0x0003 }, //#senHal_pContSenModesRegsArray[0][2]2 700012D6
{0x0F12, 0x0003 }, //#senHal_pContSenModesRegsArray[0][3]2 700012D8
{0x0F12, 0x0884 }, //#senHal_pContSenModesRegsArray[1][0]2 700012DA
{0x0F12, 0x08CF }, //#senHal_pContSenModesRegsArray[1][1]2 700012DC
{0x0F12, 0x0500 }, //#senHal_pContSenModesRegsArray[1][2]2 700012DE
{0x0F12, 0x054B }, //#senHal_pContSenModesRegsArray[1][3]2 700012E0
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[2][0]2 700012E2
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[2][1]2 700012E4
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[2][2]2 700012E6
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[2][3]2 700012E8
{0x0F12, 0x0885 }, //#senHal_pContSenModesRegsArray[3][0]2 700012EA
{0x0F12, 0x0467 }, //#senHal_pContSenModesRegsArray[3][1]2 700012EC
{0x0F12, 0x0501 }, //#senHal_pContSenModesRegsArray[3][2]2 700012EE
{0x0F12, 0x02A5 }, //#senHal_pContSenModesRegsArray[3][3]2 700012F0
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[4][0]2 700012F2
{0x0F12, 0x046A }, //#senHal_pContSenModesRegsArray[4][1]2 700012F4
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[4][2]2 700012F6
{0x0F12, 0x02A8 }, //#senHal_pContSenModesRegsArray[4][3]2 700012F8
{0x0F12, 0x0885 }, //#senHal_pContSenModesRegsArray[5][0]2 700012FA
{0x0F12, 0x08D0 }, //#senHal_pContSenModesRegsArray[5][1]2 700012FC
{0x0F12, 0x0501 }, //#senHal_pContSenModesRegsArray[5][2]2 700012FE
{0x0F12, 0x054C }, //#senHal_pContSenModesRegsArray[5][3]2 70001300
{0x0F12, 0x0006 }, //#senHal_pContSenModesRegsArray[6][0]2 70001302
{0x0F12, 0x0020 }, //#senHal_pContSenModesRegsArray[6][1]2 70001304
{0x0F12, 0x0006 }, //#senHal_pContSenModesRegsArray[6][2]2 70001306
{0x0F12, 0x0020 }, //#senHal_pContSenModesRegsArray[6][3]2 70001308
{0x0F12, 0x0881 }, //#senHal_pContSenModesRegsArray[7][0]2 7000130A
{0x0F12, 0x0463 }, //#senHal_pContSenModesRegsArray[7][1]2 7000130C
{0x0F12, 0x04FD }, //#senHal_pContSenModesRegsArray[7][2]2 7000130E
{0x0F12, 0x02A1 }, //#senHal_pContSenModesRegsArray[7][3]2 70001310
{0x0F12, 0x0006 }, //#senHal_pContSenModesRegsArray[8][0]2 70001312
{0x0F12, 0x0489 }, //#senHal_pContSenModesRegsArray[8][1]2 70001314
{0x0F12, 0x0006 }, //#senHal_pContSenModesRegsArray[8][2]2 70001316
{0x0F12, 0x02C7 }, //#senHal_pContSenModesRegsArray[8][3]2 70001318
{0x0F12, 0x0881 }, //#senHal_pContSenModesRegsArray[9][0]2 7000131A
{0x0F12, 0x08CC }, //#senHal_pContSenModesRegsArray[9][1]2 7000131C
{0x0F12, 0x04FD }, //#senHal_pContSenModesRegsArray[9][2]2 7000131E
{0x0F12, 0x0548 }, //#senHal_pContSenModesRegsArray[9][3]2 70001320
{0x0F12, 0x03A2 }, //#senHal_pContSenModesRegsArray[10][0] 2 70001322
{0x0F12, 0x01D3 }, //#senHal_pContSenModesRegsArray[10][1] 2 70001324
{0x0F12, 0x01E0 }, //#senHal_pContSenModesRegsArray[10][2] 2 70001326
{0x0F12, 0x00F2 }, //#senHal_pContSenModesRegsArray[10][3] 2 70001328
{0x0F12, 0x03F2 }, //#senHal_pContSenModesRegsArray[11][0] 2 7000132A
{0x0F12, 0x0223 }, //#senHal_pContSenModesRegsArray[11][1] 2 7000132C
{0x0F12, 0x0230 }, //#senHal_pContSenModesRegsArray[11][2] 2 7000132E
{0x0F12, 0x0142 }, //#senHal_pContSenModesRegsArray[11][3] 2 70001330
{0x0F12, 0x03A2 }, //#senHal_pContSenModesRegsArray[12][0] 2 70001332
{0x0F12, 0x063C }, //#senHal_pContSenModesRegsArray[12][1] 2 70001334
{0x0F12, 0x01E0 }, //#senHal_pContSenModesRegsArray[12][2] 2 70001336
{0x0F12, 0x0399 }, //#senHal_pContSenModesRegsArray[12][3] 2 70001338
{0x0F12, 0x03F2 }, //#senHal_pContSenModesRegsArray[13][0] 2 7000133A
{0x0F12, 0x068C }, //#senHal_pContSenModesRegsArray[13][1] 2 7000133C
{0x0F12, 0x0230 }, //#senHal_pContSenModesRegsArray[13][2] 2 7000133E
{0x0F12, 0x03E9 }, //#senHal_pContSenModesRegsArray[13][3] 2 70001340
{0x0F12, 0x0002 }, //#senHal_pContSenModesRegsArray[14][0] 2 70001342
{0x0F12, 0x0002 }, //#senHal_pContSenModesRegsArray[14][1] 2 70001344
{0x0F12, 0x0002 }, //#senHal_pContSenModesRegsArray[14][2] 2 70001346
{0x0F12, 0x0002 }, //#senHal_pContSenModesRegsArray[14][3] 2 70001348
{0x0F12, 0x003C }, //#senHal_pContSenModesRegsArray[15][0] 2 7000134A
{0x0F12, 0x003C }, //#senHal_pContSenModesRegsArray[15][1] 2 7000134C
{0x0F12, 0x003C }, //#senHal_pContSenModesRegsArray[15][2] 2 7000134E
{0x0F12, 0x003C }, //#senHal_pContSenModesRegsArray[15][3] 2 70001350
{0x0F12, 0x01D3 }, //#senHal_pContSenModesRegsArray[16][0] 2 70001352
{0x0F12, 0x01D3 }, //#senHal_pContSenModesRegsArray[16][1] 2 70001354
{0x0F12, 0x00F2 }, //#senHal_pContSenModesRegsArray[16][2] 2 70001356
{0x0F12, 0x00F2 }, //#senHal_pContSenModesRegsArray[16][3] 2 70001358
{0x0F12, 0x020B }, //#senHal_pContSenModesRegsArray[17][0] 2 7000135A
{0x0F12, 0x024A }, //#senHal_pContSenModesRegsArray[17][1] 2 7000135C
{0x0F12, 0x012A }, //#senHal_pContSenModesRegsArray[17][2] 2 7000135E
{0x0F12, 0x0169 }, //#senHal_pContSenModesRegsArray[17][3] 2 70001360
{0x0F12, 0x0002 }, //#senHal_pContSenModesRegsArray[18][0] 2 70001362
{0x0F12, 0x046B }, //#senHal_pContSenModesRegsArray[18][1] 2 70001364
{0x0F12, 0x0002 }, //#senHal_pContSenModesRegsArray[18][2] 2 70001366
{0x0F12, 0x02A9 }, //#senHal_pContSenModesRegsArray[18][3] 2 70001368
{0x0F12, 0x0419 }, //#senHal_pContSenModesRegsArray[19][0] 2 7000136A
{0x0F12, 0x04A5 }, //#senHal_pContSenModesRegsArray[19][1] 2 7000136C
{0x0F12, 0x0257 }, //#senHal_pContSenModesRegsArray[19][2] 2 7000136E
{0x0F12, 0x02E3 }, //#senHal_pContSenModesRegsArray[19][3] 2 70001370
{0x0F12, 0x0630 }, //#senHal_pContSenModesRegsArray[20][0] 2 70001372
{0x0F12, 0x063C }, //#senHal_pContSenModesRegsArray[20][1] 2 70001374
{0x0F12, 0x038D }, //#senHal_pContSenModesRegsArray[20][2] 2 70001376
{0x0F12, 0x0399 }, //#senHal_pContSenModesRegsArray[20][3] 2 70001378
{0x0F12, 0x0668 }, //#senHal_pContSenModesRegsArray[21][0] 2 7000137A
{0x0F12, 0x06B3 }, //#senHal_pContSenModesRegsArray[21][1] 2 7000137C
{0x0F12, 0x03C5 }, //#senHal_pContSenModesRegsArray[21][2] 2 7000137E
{0x0F12, 0x0410 }, //#senHal_pContSenModesRegsArray[21][3] 2 70001380
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[22][0] 2 70001382
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[22][1] 2 70001384
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[22][2] 2 70001386
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[22][3] 2 70001388
{0x0F12, 0x03A2 }, //#senHal_pContSenModesRegsArray[23][0] 2 7000138A
{0x0F12, 0x01D3 }, //#senHal_pContSenModesRegsArray[23][1] 2 7000138C
{0x0F12, 0x01E0 }, //#senHal_pContSenModesRegsArray[23][2] 2 7000138E
{0x0F12, 0x00F2 }, //#senHal_pContSenModesRegsArray[23][3] 2 70001390
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[24][0] 2 70001392
{0x0F12, 0x0461 }, //#senHal_pContSenModesRegsArray[24][1] 2 70001394
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[24][2] 2 70001396
{0x0F12, 0x029F }, //#senHal_pContSenModesRegsArray[24][3] 2 70001398
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[25][0] 2 7000139A
{0x0F12, 0x063C }, //#senHal_pContSenModesRegsArray[25][1] 2 7000139C
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[25][2] 2 7000139E
{0x0F12, 0x0399 }, //#senHal_pContSenModesRegsArray[25][3] 2 700013A0
{0x0F12, 0x003D }, //#senHal_pContSenModesRegsArray[26][0] 2 700013A2
{0x0F12, 0x003D }, //#senHal_pContSenModesRegsArray[26][1] 2 700013A4
{0x0F12, 0x003D }, //#senHal_pContSenModesRegsArray[26][2] 2 700013A6
{0x0F12, 0x003D }, //#senHal_pContSenModesRegsArray[26][3] 2 700013A8
{0x0F12, 0x01D0 }, //#senHal_pContSenModesRegsArray[27][0] 2 700013AA
{0x0F12, 0x01D0 }, //#senHal_pContSenModesRegsArray[27][1] 2 700013AC
{0x0F12, 0x00EF }, //#senHal_pContSenModesRegsArray[27][2] 2 700013AE
{0x0F12, 0x00EF }, //#senHal_pContSenModesRegsArray[27][3] 2 700013B0
{0x0F12, 0x020C }, //#senHal_pContSenModesRegsArray[28][0] 2 700013B2
{0x0F12, 0x024B }, //#senHal_pContSenModesRegsArray[28][1] 2 700013B4
{0x0F12, 0x012B }, //#senHal_pContSenModesRegsArray[28][2] 2 700013B6
{0x0F12, 0x016A }, //#senHal_pContSenModesRegsArray[28][3] 2 700013B8
{0x0F12, 0x039F }, //#senHal_pContSenModesRegsArray[29][0] 2 700013BA
{0x0F12, 0x045E }, //#senHal_pContSenModesRegsArray[29][1] 2 700013BC
{0x0F12, 0x01DD }, //#senHal_pContSenModesRegsArray[29][2] 2 700013BE
{0x0F12, 0x029C }, //#senHal_pContSenModesRegsArray[29][3] 2 700013C0
{0x0F12, 0x041A }, //#senHal_pContSenModesRegsArray[30][0] 2 700013C2
{0x0F12, 0x04A6 }, //#senHal_pContSenModesRegsArray[30][1] 2 700013C4
{0x0F12, 0x0258 }, //#senHal_pContSenModesRegsArray[30][2] 2 700013C6
{0x0F12, 0x02E4 }, //#senHal_pContSenModesRegsArray[30][3] 2 700013C8
{0x0F12, 0x062D }, //#senHal_pContSenModesRegsArray[31][0] 2 700013CA
{0x0F12, 0x0639 }, //#senHal_pContSenModesRegsArray[31][1] 2 700013CC
{0x0F12, 0x038A }, //#senHal_pContSenModesRegsArray[31][2] 2 700013CE
{0x0F12, 0x0396 }, //#senHal_pContSenModesRegsArray[31][3] 2 700013D0
{0x0F12, 0x0669 }, //#senHal_pContSenModesRegsArray[32][0] 2 700013D2
{0x0F12, 0x06B4 }, //#senHal_pContSenModesRegsArray[32][1] 2 700013D4
{0x0F12, 0x03C6 }, //#senHal_pContSenModesRegsArray[32][2] 2 700013D6
{0x0F12, 0x0411 }, //#senHal_pContSenModesRegsArray[32][3] 2 700013D8
{0x0F12, 0x087C }, //#senHal_pContSenModesRegsArray[33][0] 2 700013DA
{0x0F12, 0x08C7 }, //#senHal_pContSenModesRegsArray[33][1] 2 700013DC
{0x0F12, 0x04F8 }, //#senHal_pContSenModesRegsArray[33][2] 2 700013DE
{0x0F12, 0x0543 }, //#senHal_pContSenModesRegsArray[33][3] 2 700013E0
{0x0F12, 0x0040 }, //#senHal_pContSenModesRegsArray[34][0] 2 700013E2
{0x0F12, 0x0040 }, //#senHal_pContSenModesRegsArray[34][1] 2 700013E4
{0x0F12, 0x0040 }, //#senHal_pContSenModesRegsArray[34][2] 2 700013E6
{0x0F12, 0x0040 }, //#senHal_pContSenModesRegsArray[34][3] 2 700013E8
{0x0F12, 0x01D0 }, //#senHal_pContSenModesRegsArray[35][0] 2 700013EA
{0x0F12, 0x01D0 }, //#senHal_pContSenModesRegsArray[35][1] 2 700013EC
{0x0F12, 0x00EF }, //#senHal_pContSenModesRegsArray[35][2] 2 700013EE
{0x0F12, 0x00EF }, //#senHal_pContSenModesRegsArray[35][3] 2 700013F0
{0x0F12, 0x020F }, //#senHal_pContSenModesRegsArray[36][0] 2 700013F2
{0x0F12, 0x024E }, //#senHal_pContSenModesRegsArray[36][1] 2 700013F4
{0x0F12, 0x012E }, //#senHal_pContSenModesRegsArray[36][2] 2 700013F6
{0x0F12, 0x016D }, //#senHal_pContSenModesRegsArray[36][3] 2 700013F8
{0x0F12, 0x039F }, //#senHal_pContSenModesRegsArray[37][0] 2 700013FA
{0x0F12, 0x045E }, //#senHal_pContSenModesRegsArray[37][1] 2 700013FC
{0x0F12, 0x01DD }, //#senHal_pContSenModesRegsArray[37][2] 2 700013FE
{0x0F12, 0x029C }, //#senHal_pContSenModesRegsArray[37][3] 2 70001400
{0x0F12, 0x041D }, //#senHal_pContSenModesRegsArray[38][0] 2 70001402
{0x0F12, 0x04A9 }, //#senHal_pContSenModesRegsArray[38][1] 2 70001404
{0x0F12, 0x025B }, //#senHal_pContSenModesRegsArray[38][2] 2 70001406
{0x0F12, 0x02E7 }, //#senHal_pContSenModesRegsArray[38][3] 2 70001408
{0x0F12, 0x062D }, //#senHal_pContSenModesRegsArray[39][0] 2 7000140A
{0x0F12, 0x0639 }, //#senHal_pContSenModesRegsArray[39][1] 2 7000140C
{0x0F12, 0x038A }, //#senHal_pContSenModesRegsArray[39][2] 2 7000140E
{0x0F12, 0x0396 }, //#senHal_pContSenModesRegsArray[39][3] 2 70001410
{0x0F12, 0x066C }, //#senHal_pContSenModesRegsArray[40][0] 2 70001412
{0x0F12, 0x06B7 }, //#senHal_pContSenModesRegsArray[40][1] 2 70001414
{0x0F12, 0x03C9 }, //#senHal_pContSenModesRegsArray[40][2] 2 70001416
{0x0F12, 0x0414 }, //#senHal_pContSenModesRegsArray[40][3] 2 70001418
{0x0F12, 0x087C }, //#senHal_pContSenModesRegsArray[41][0] 2 7000141A
{0x0F12, 0x08C7 }, //#senHal_pContSenModesRegsArray[41][1] 2 7000141C
{0x0F12, 0x04F8 }, //#senHal_pContSenModesRegsArray[41][2] 2 7000141E
{0x0F12, 0x0543 }, //#senHal_pContSenModesRegsArray[41][3] 2 70001420
{0x0F12, 0x0040 }, //#senHal_pContSenModesRegsArray[42][0] 2 70001422
{0x0F12, 0x0040 }, //#senHal_pContSenModesRegsArray[42][1] 2 70001424
{0x0F12, 0x0040 }, //#senHal_pContSenModesRegsArray[42][2] 2 70001426
{0x0F12, 0x0040 }, //#senHal_pContSenModesRegsArray[42][3] 2 70001428
{0x0F12, 0x01D0 }, //#senHal_pContSenModesRegsArray[43][0] 2 7000142A
{0x0F12, 0x01D0 }, //#senHal_pContSenModesRegsArray[43][1] 2 7000142C
{0x0F12, 0x00EF }, //#senHal_pContSenModesRegsArray[43][2] 2 7000142E
{0x0F12, 0x00EF }, //#senHal_pContSenModesRegsArray[43][3] 2 70001430
{0x0F12, 0x020F }, //#senHal_pContSenModesRegsArray[44][0] 2 70001432
{0x0F12, 0x024E }, //#senHal_pContSenModesRegsArray[44][1] 2 70001434
{0x0F12, 0x012E }, //#senHal_pContSenModesRegsArray[44][2] 2 70001436
{0x0F12, 0x016D }, //#senHal_pContSenModesRegsArray[44][3] 2 70001438
{0x0F12, 0x039F }, //#senHal_pContSenModesRegsArray[45][0] 2 7000143A
{0x0F12, 0x045E }, //#senHal_pContSenModesRegsArray[45][1] 2 7000143C
{0x0F12, 0x01DD }, //#senHal_pContSenModesRegsArray[45][2] 2 7000143E
{0x0F12, 0x029C }, //#senHal_pContSenModesRegsArray[45][3] 2 70001440
{0x0F12, 0x041D }, //#senHal_pContSenModesRegsArray[46][0] 2 70001442
{0x0F12, 0x04A9 }, //#senHal_pContSenModesRegsArray[46][1] 2 70001444
{0x0F12, 0x025B }, //#senHal_pContSenModesRegsArray[46][2] 2 70001446
{0x0F12, 0x02E7 }, //#senHal_pContSenModesRegsArray[46][3] 2 70001448
{0x0F12, 0x062D }, //#senHal_pContSenModesRegsArray[47][0] 2 7000144A
{0x0F12, 0x0639 }, //#senHal_pContSenModesRegsArray[47][1] 2 7000144C
{0x0F12, 0x038A }, //#senHal_pContSenModesRegsArray[47][2] 2 7000144E
{0x0F12, 0x0396 }, //#senHal_pContSenModesRegsArray[47][3] 2 70001450
{0x0F12, 0x066C }, //#senHal_pContSenModesRegsArray[48][0] 2 70001452
{0x0F12, 0x06B7 }, //#senHal_pContSenModesRegsArray[48][1] 2 70001454
{0x0F12, 0x03C9 }, //#senHal_pContSenModesRegsArray[48][2] 2 70001456
{0x0F12, 0x0414 }, //#senHal_pContSenModesRegsArray[48][3] 2 70001458
{0x0F12, 0x087C }, //#senHal_pContSenModesRegsArray[49][0] 2 7000145A
{0x0F12, 0x08C7 }, //#senHal_pContSenModesRegsArray[49][1] 2 7000145C
{0x0F12, 0x04F8 }, //#senHal_pContSenModesRegsArray[49][2] 2 7000145E
{0x0F12, 0x0543 }, //#senHal_pContSenModesRegsArray[49][3] 2 70001460
{0x0F12, 0x003D }, //#senHal_pContSenModesRegsArray[50][0] 2 70001462
{0x0F12, 0x003D }, //#senHal_pContSenModesRegsArray[50][1] 2 70001464
{0x0F12, 0x003D }, //#senHal_pContSenModesRegsArray[50][2] 2 70001466
{0x0F12, 0x003D }, //#senHal_pContSenModesRegsArray[50][3] 2 70001468
{0x0F12, 0x01D2 }, //#senHal_pContSenModesRegsArray[51][0] 2 7000146A
{0x0F12, 0x01D2 }, //#senHal_pContSenModesRegsArray[51][1] 2 7000146C
{0x0F12, 0x00F1 }, //#senHal_pContSenModesRegsArray[51][2] 2 7000146E
{0x0F12, 0x00F1 }, //#senHal_pContSenModesRegsArray[51][3] 2 70001470
{0x0F12, 0x020C }, //#senHal_pContSenModesRegsArray[52][0] 2 70001472
{0x0F12, 0x024B }, //#senHal_pContSenModesRegsArray[52][1] 2 70001474
{0x0F12, 0x012B }, //#senHal_pContSenModesRegsArray[52][2] 2 70001476
{0x0F12, 0x016A }, //#senHal_pContSenModesRegsArray[52][3] 2 70001478
{0x0F12, 0x03A1 }, //#senHal_pContSenModesRegsArray[53][0] 2 7000147A
{0x0F12, 0x0460 }, //#senHal_pContSenModesRegsArray[53][1] 2 7000147C
{0x0F12, 0x01DF }, //#senHal_pContSenModesRegsArray[53][2] 2 7000147E
{0x0F12, 0x029E }, //#senHal_pContSenModesRegsArray[53][3] 2 70001480
{0x0F12, 0x041A }, //#senHal_pContSenModesRegsArray[54][0] 2 70001482
{0x0F12, 0x04A6 }, //#senHal_pContSenModesRegsArray[54][1] 2 70001484
{0x0F12, 0x0258 }, //#senHal_pContSenModesRegsArray[54][2] 2 70001486
{0x0F12, 0x02E4 }, //#senHal_pContSenModesRegsArray[54][3] 2 70001488
{0x0F12, 0x062F }, //#senHal_pContSenModesRegsArray[55][0] 2 7000148A
{0x0F12, 0x063B }, //#senHal_pContSenModesRegsArray[55][1] 2 7000148C
{0x0F12, 0x038C }, //#senHal_pContSenModesRegsArray[55][2] 2 7000148E
{0x0F12, 0x0398 }, //#senHal_pContSenModesRegsArray[55][3] 2 70001490
{0x0F12, 0x0669 }, //#senHal_pContSenModesRegsArray[56][0] 2 70001492
{0x0F12, 0x06B4 }, //#senHal_pContSenModesRegsArray[56][1] 2 70001494
{0x0F12, 0x03C6 }, //#senHal_pContSenModesRegsArray[56][2] 2 70001496
{0x0F12, 0x0411 }, //#senHal_pContSenModesRegsArray[56][3] 2 70001498
{0x0F12, 0x087E }, //#senHal_pContSenModesRegsArray[57][0] 2 7000149A
{0x0F12, 0x08C9 }, //#senHal_pContSenModesRegsArray[57][1] 2 7000149C
{0x0F12, 0x04FA }, //#senHal_pContSenModesRegsArray[57][2] 2 7000149E
{0x0F12, 0x0545 }, //#senHal_pContSenModesRegsArray[57][3] 2 700014A0
{0x0F12, 0x03A2 }, //#senHal_pContSenModesRegsArray[58][0] 2 700014A2
{0x0F12, 0x01D3 }, //#senHal_pContSenModesRegsArray[58][1] 2 700014A4
{0x0F12, 0x01E0 }, //#senHal_pContSenModesRegsArray[58][2] 2 700014A6
{0x0F12, 0x00F2 }, //#senHal_pContSenModesRegsArray[58][3] 2 700014A8
{0x0F12, 0x03AF }, //#senHal_pContSenModesRegsArray[59][0] 2 700014AA
{0x0F12, 0x01E0 }, //#senHal_pContSenModesRegsArray[59][1] 2 700014AC
{0x0F12, 0x01ED }, //#senHal_pContSenModesRegsArray[59][2] 2 700014AE
{0x0F12, 0x00FF }, //#senHal_pContSenModesRegsArray[59][3] 2 700014B0
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[60][0] 2 700014B2
{0x0F12, 0x0461 }, //#senHal_pContSenModesRegsArray[60][1] 2 700014B4
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[60][2] 2 700014B6
{0x0F12, 0x029F }, //#senHal_pContSenModesRegsArray[60][3] 2 700014B8
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[61][0] 2 700014BA
{0x0F12, 0x046E }, //#senHal_pContSenModesRegsArray[61][1] 2 700014BC
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[61][2] 2 700014BE
{0x0F12, 0x02AC }, //#senHal_pContSenModesRegsArray[61][3] 2 700014C0
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[62][0] 2 700014C2
{0x0F12, 0x063C }, //#senHal_pContSenModesRegsArray[62][1] 2 700014C4
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[62][2] 2 700014C6
{0x0F12, 0x0399 }, //#senHal_pContSenModesRegsArray[62][3] 2 700014C8
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[63][0] 2 700014CA
{0x0F12, 0x0649 }, //#senHal_pContSenModesRegsArray[63][1] 2 700014CC
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[63][2] 2 700014CE
{0x0F12, 0x03A6 }, //#senHal_pContSenModesRegsArray[63][3] 2 700014D0
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[64][0] 2 700014D2
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[64][1] 2 700014D4
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[64][2] 2 700014D6
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[64][3] 2 700014D8
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[65][0] 2 700014DA
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[65][1] 2 700014DC
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[65][2] 2 700014DE
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[65][3] 2 700014E0
{0x0F12, 0x03AA }, //#senHal_pContSenModesRegsArray[66][0] 2 700014E2
{0x0F12, 0x01DB }, //#senHal_pContSenModesRegsArray[66][1] 2 700014E4
{0x0F12, 0x01E8 }, //#senHal_pContSenModesRegsArray[66][2] 2 700014E6
{0x0F12, 0x00FA }, //#senHal_pContSenModesRegsArray[66][3] 2 700014E8
{0x0F12, 0x03B7 }, //#senHal_pContSenModesRegsArray[67][0] 2 700014EA
{0x0F12, 0x01E8 }, //#senHal_pContSenModesRegsArray[67][1] 2 700014EC
{0x0F12, 0x01F5 }, //#senHal_pContSenModesRegsArray[67][2] 2 700014EE
{0x0F12, 0x0107 }, //#senHal_pContSenModesRegsArray[67][3] 2 700014F0
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[68][0] 2 700014F2
{0x0F12, 0x0469 }, //#senHal_pContSenModesRegsArray[68][1] 2 700014F4
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[68][2] 2 700014F6
{0x0F12, 0x02A7 }, //#senHal_pContSenModesRegsArray[68][3] 2 700014F8
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[69][0] 2 700014FA
{0x0F12, 0x0476 }, //#senHal_pContSenModesRegsArray[69][1] 2 700014FC
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[69][2] 2 700014FE
{0x0F12, 0x02B4 }, //#senHal_pContSenModesRegsArray[69][3] 2 70001500
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[70][0] 2 70001502
{0x0F12, 0x0644 }, //#senHal_pContSenModesRegsArray[70][1] 2 70001504
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[70][2] 2 70001506
{0x0F12, 0x03A1 }, //#senHal_pContSenModesRegsArray[70][3] 2 70001508
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[71][0] 2 7000150A
{0x0F12, 0x0651 }, //#senHal_pContSenModesRegsArray[71][1] 2 7000150C
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[71][2] 2 7000150E
{0x0F12, 0x03AE }, //#senHal_pContSenModesRegsArray[71][3] 2 70001510
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[72][0] 2 70001512
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[72][1] 2 70001514
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[72][2] 2 70001516
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[72][3] 2 70001518
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[73][0] 2 7000151A
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[73][1] 2 7000151C
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[73][2] 2 7000151E
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[73][3] 2 70001520
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[74][0] 2 70001522
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[74][1] 2 70001524
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[74][2] 2 70001526
{0x0F12, 0x0001 }, //#senHal_pContSenModesRegsArray[74][3] 2 70001528
{0x0F12, 0x000F }, //#senHal_pContSenModesRegsArray[75][0] 2 7000152A
{0x0F12, 0x000F }, //#senHal_pContSenModesRegsArray[75][1] 2 7000152C
{0x0F12, 0x000F }, //#senHal_pContSenModesRegsArray[75][2] 2 7000152E
{0x0F12, 0x000F }, //#senHal_pContSenModesRegsArray[75][3] 2 70001530
{0x0F12, 0x05AD }, //#senHal_pContSenModesRegsArray[76][0] 2 70001532
{0x0F12, 0x03DE }, //#senHal_pContSenModesRegsArray[76][1] 2 70001534
{0x0F12, 0x030A }, //#senHal_pContSenModesRegsArray[76][2] 2 70001536
{0x0F12, 0x021C }, //#senHal_pContSenModesRegsArray[76][3] 2 70001538
{0x0F12, 0x062F }, //#senHal_pContSenModesRegsArray[77][0] 2 7000153A
{0x0F12, 0x0460 }, //#senHal_pContSenModesRegsArray[77][1] 2 7000153C
{0x0F12, 0x038C }, //#senHal_pContSenModesRegsArray[77][2] 2 7000153E
{0x0F12, 0x029E }, //#senHal_pContSenModesRegsArray[77][3] 2 70001540
{0x0F12, 0x07FC }, //#senHal_pContSenModesRegsArray[78][0] 2 70001542
{0x0F12, 0x0847 }, //#senHal_pContSenModesRegsArray[78][1] 2 70001544
{0x0F12, 0x0478 }, //#senHal_pContSenModesRegsArray[78][2] 2 70001546
{0x0F12, 0x04C3 }, //#senHal_pContSenModesRegsArray[78][3] 2 70001548
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[79][0] 2 7000154A
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[79][1] 2 7000154C
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[79][2] 2 7000154E
{0x0F12, 0x0000 }, //#senHal_pContSenModesRegsArray[79][3] 2 70001550
              
//============================================================
// Analog Setting END
//============================================================
              
////============================================================
//// AF Interface setting
////============================================================
//WRITE 700001D4 0000 //REG_TC_IPRM_AuxGpios : 0 - no Flash
//WRITE 700001DE 0003 //REG_TC_IPRM_CM_Init_AfModeType : 3 - AFD_VCM_I2C
//WRITE 700001E0 0000 //REG_TC_IPRM_CM_Init_PwmConfig1 : 0 - no PWM
//WRITE 700001E4 0000 //REG_TC_IPRM_CM_Init_GpioConfig1 : 0 - no GPIO
//WRITE 700001E8 200C //REG_TC_IPRM_CM_Init_Mi2cBits : MSCL - GPIO1 MSDA - GPIO2 Device ID (0C)
//WRITE 700001EA 0190 //REG_TC_IPRM_CM_Init_Mi2cRateKhz : MI2C Speed - 400KHz
//            
////============================================================
//// AF Parameter setting
////============================================================
//// AF Window Settings
//WRITE 7000025A 0100 //#REG_TC_AF_FstWinStartX
//WRITE 7000025C 00E3 //#REG_TC_AF_FstWinStartY
//WRITE 7000025E 0200 //#REG_TC_AF_FstWinSizeX
//WRITE 70000260 0238 //#REG_TC_AF_FstWinSizeY
//WRITE 70000262 018C //#REG_TC_AF_ScndWinStartX
//WRITE 70000264 0166 //#REG_TC_AF_ScndWinStartY
//WRITE 70000266 00E6 //#REG_TC_AF_ScndWinSizeX
//WRITE 70000268 0132 //#REG_TC_AF_ScndWinSizeY
//WRITE 7000026A 0001 //#REG_TC_AF_WinSizesUpdated
//
//// AF Setot Settings
//WRITE 70000586 00FF //#skl_af_StatOvlpExpFactor
//
//// AF Scene Settings
//WRITE 7000115E 0003 //#af_scene_usSaturatedScene
//
//// AF Fine Search Settings
//WRITE 700010D4 1000 //FineSearch Disable //#af_search_usSingleAfFlags
//WRITE 700010DE 0004 //#af_search_usFinePeakCount
//WRITE 7000106C 0202 //#af_pos_usFineStepNumSize
//
//// AF Peak Threshold Setting
//WRITE 700010CA 00C0
//
//// AF Default Position
//WRITE 70001060 003C //#af_pos_usHomePos
//WRITE 70001062 783C //#af_pos_usLowConfPos
//
//// AF LowConfThr Setting
//WRITE 700010F4 0280
//WRITE 70001100 03A0
//WRITE 70001102 0320
//
//WRITE 70001134 0030 //af_stat_usMinStatVal
//
//// AF low Br Th
//WRITE 70001154 0060
//
//// AF Policy
//WRITE 700010E2 0000 //#af_search_usCapturePolicy: Focus_Priority, 0002 : Shutter_Priority_Fixed, 0001 : Shutter_Priority_Last_BFP 0000: Shutter_Priority_Current
//WRITE 70001072 003C //#af_pos_usCaptureFixedPos// 0x0008
//
//// AF Lens Position Table Settings
//WRITE 70001074 0010 //#af_pos_usTableLastInd// 16 Steps 091222
//WRITE 70001076 003C //#af_pos_usTable_0_// af_pos_usTable
//WRITE 70001078 003F //#af_pos_usTable_1_
//WRITE 7000107A 0042 //#af_pos_usTable_2_
//WRITE 7000107C 0045 //#af_pos_usTable_3_
//WRITE 7000107E 0048 //#af_pos_usTable_4_
//WRITE 70001080 004B //#af_pos_usTable_5_
//WRITE 70001082 004E //#af_pos_usTable_6_
//WRITE 70001084 0051 //#af_pos_usTable_7_
//WRITE 70001086 0054 //#af_pos_usTable_8_
//WRITE 70001088 0057 //#af_pos_usTable_9_
//WRITE 7000108A 005A //#af_pos_usTable_10_
//WRITE 7000108C 005E //#af_pos_usTable_11_
//WRITE 7000108E 0061 //#af_pos_usTable_12_
//WRITE 70001090 0064 //#af_pos_usTable_13_
//WRITE 70001092 0068 //#af_pos_usTable_14_
//WRITE 70001094 006C //#af_pos_usTable_15_
//WRITE 70001096 0078 //#af_pos_usTable_16_
//
//WRITE 70000252 0003 //init

//============================================================
// ISP-FE Setting
//============================================================
{0x002A, 0x158A },
{0x0F12, 0xEAF0 },
{0x002A, 0x15C6 },
{0x0F12, 0x0020 },
{0x0F12, 0x0060 },
{0x002A, 0x15BC },
{0x0F12, 0x0200 },
              
//Analog Offset for MSM
{0x002A, 0x1608 },
{0x0F12, 0x0100 }, //#gisp_msm_sAnalogOffset[0]
{0x0F12, 0x0100 }, //#gisp_msm_sAnalogOffset[1]
{0x0F12, 0x0100 }, //#gisp_msm_sAnalogOffset[2]
{0x0F12, 0x0100 }, //#gisp_msm_sAnalogOffset[3]
              
//================================================================================================
// SET AE   
//================================================================================================
// AE target
{0x002A, 0x0F70 },
{0x0F12, 0x0048 }, //003A // #TVAR_ae_BrAve
// AE mode  
{0x002A, 0x0F76 },
{0x0F12, 0x000F }, //Disable illumination & contrast  // #ae_StatMode
// AE weight
{0x002A, 0x0F7E },
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_0_
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_1_
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_2_
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_3_
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_4_
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_5_
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_6_
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_7_
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_8_
{0x0F12, 0x0303 }, // #ae_WeightTbl_16_9_
{0x0F12, 0x0303 }, // #ae_WeightTbl_16_10
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_11
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_12
{0x0F12, 0x0303 }, // #ae_WeightTbl_16_13
{0x0F12, 0x0303 }, // #ae_WeightTbl_16_14
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_15
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_16
{0x0F12, 0x0303 }, // #ae_WeightTbl_16_17
{0x0F12, 0x0303 }, // #ae_WeightTbl_16_18
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_19
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_20
{0x0F12, 0x0303 }, // #ae_WeightTbl_16_21
{0x0F12, 0x0303 }, // #ae_WeightTbl_16_22
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_23
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_24
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_25
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_26
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_27
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_28
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_29
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_30
{0x0F12, 0x0101 }, // #ae_WeightTbl_16_31
              
//================================================================================================
// SET FLICKER
//================================================================================================
{0x002A, 0x0C18 },                                     
{0x0F12, 0x0001 }, // 0001: 60Hz start auto / 0000: 50Hz start auto
{0x002A, 0x04D2 },
{0x0F12, 0x067F }, // #REG_TC_DBG_AutoAlgEnBits
//{0x002A, 0x04BA },
//{0x0F12, 0x0002 }, // #REG_SF_USER_FlickerQuant
{0x002A, 0x0C04 },
{0x0F12, 0x2000 }, // #AFC_StandingWavesLimit
              
//================================================================================================
// SET GAS    
//================================================================================================
// GAS alpha  
// R, Gr, Gb, B per light source
{0x002A, 0x06CE },
{0x0F12, 0x00FD }, //0150//0100 // #TVAR_ash_GASAlpha[0] // Horizon
{0x0F12, 0x00FD }, //0113//0100 // #TVAR_ash_GASAlpha[1]
{0x0F12, 0x00FD }, //011D//0100 // #TVAR_ash_GASAlpha[2]
{0x0F12, 0x00FC }, //0100//0100 // #TVAR_ash_GASAlpha[3]
{0x0F12, 0x00FD }, //0146//0100 // #TVAR_ash_GASAlpha[4] // IncandA
{0x0F12, 0x00FD }, //0113//0100 // #TVAR_ash_GASAlpha[5]
{0x0F12, 0x00FD }, //011D//0100 // #TVAR_ash_GASAlpha[6]
{0x0F12, 0x00FC }, //0109//0100 // #TVAR_ash_GASAlpha[7]
{0x0F12, 0x00FD }, //0120//0100 // #TVAR_ash_GASAlpha[8] // WW
{0x0F12, 0x00FD }, //00E6//0100 // #TVAR_ash_GASAlpha[9]
{0x0F12, 0x00FD }, //00F0//0100 // #TVAR_ash_GASAlpha[10]
{0x0F12, 0x00FC }, //00DD//0100 // #TVAR_ash_GASAlpha[11]
{0x0F12, 0x00FD }, //00D7//0100 // #TVAR_ash_GASAlpha[12]// CWF
{0x0F12, 0x00FD }, //00F9//0100 // #TVAR_ash_GASAlpha[13]
{0x0F12, 0x00FD }, //00F7//0100 // #TVAR_ash_GASAlpha[14]
{0x0F12, 0x00FC }, //00EF//0100 // #TVAR_ash_GASAlpha[15]
{0x0F12, 0x00FD }, //00F0//0100 // #TVAR_ash_GASAlpha[16]// D50
{0x0F12, 0x00FD }, //0103//0100 // #TVAR_ash_GASAlpha[17]
{0x0F12, 0x00FD }, //00FC//0100 // #TVAR_ash_GASAlpha[18]
{0x0F12, 0x00FC }, //010C//0100 // #TVAR_ash_GASAlpha[19]
{0x0F12, 0x00FD }, //0100//0100 // #TVAR_ash_GASAlpha[20]// D65
{0x0F12, 0x00FD }, //00FF//0100 // #TVAR_ash_GASAlpha[21]
{0x0F12, 0x00FD }, //00F3//0100 // #TVAR_ash_GASAlpha[22]
{0x0F12, 0x00FC }, //010F//0100 // #TVAR_ash_GASAlpha[23]
{0x0F12, 0x00FD }, //0100//0100 // #TVAR_ash_GASAlpha[24]// D75
{0x0F12, 0x00FD }, //0109//0100 // #TVAR_ash_GASAlpha[25]
{0x0F12, 0x00FD }, //00FA//0100 // #TVAR_ash_GASAlpha[26]
{0x0F12, 0x00FC }, //011E//0100 // #TVAR_ash_GASAlpha[27]
{0x0F12, 0x00FD }, //00C8//0100 // #TVAR_ash_GASOutdoorAlpha[0] // Outdoor
{0x0F12, 0x00FD }, //00F0//0100 // #TVAR_ash_GASOutdoorAlpha[1]
{0x0F12, 0x00FD }, //00F8//0100 // #TVAR_ash_GASOutdoorAlpha[2]
{0x0F12, 0x00FC }, //00F8//0100 // #TVAR_ash_GASOutdoorAlpha[3]
// GAS beta   
{0x0F12, 0x0032 }, //005A//0000 // #ash_GASBeta[0]// Horizon
{0x0F12, 0x0019 }, //002D//0000 // #ash_GASBeta[1]
{0x0F12, 0x0017 }, //002D//0000 // #ash_GASBeta[2]
{0x0F12, 0x0000 }, //0000//0000 // #ash_GASBeta[3]
{0x0F12, 0x0032 }, //005B//0000 // #ash_GASBeta[4]// IncandA
{0x0F12, 0x0019 }, //0029//0000 // #ash_GASBeta[5]
{0x0F12, 0x0017 }, //002A//0000 // #ash_GASBeta[6]
{0x0F12, 0x0000 }, //0000//0000 // #ash_GASBeta[7]
{0x0F12, 0x0032 }, //0040//0000 // #ash_GASBeta[8]// WW
{0x0F12, 0x0019 }, //002E//0000 // #ash_GASBeta[9]
{0x0F12, 0x0017 }, //0031//0000 // #ash_GASBeta[10]
{0x0F12, 0x0000 }, //0000//0000 // #ash_GASBeta[11]
{0x0F12, 0x0032 }, //0025//0000 // #ash_GASBeta[12] // CWF
{0x0F12, 0x0019 }, //0029//0000 // #ash_GASBeta[13]
{0x0F12, 0x0017 }, //0027//0000 // #ash_GASBeta[14]
{0x0F12, 0x0000 }, //0000//0000 // #ash_GASBeta[15]
{0x0F12, 0x0032 }, //0037//0000 // #ash_GASBeta[16] // D50
{0x0F12, 0x0019 }, //001F//0000 // #ash_GASBeta[17]
{0x0F12, 0x0017 }, //001C//0000 // #ash_GASBeta[18]
{0x0F12, 0x0000 }, //0000//0000 // #ash_GASBeta[19]
{0x0F12, 0x0032 }, //0031//0000 // #ash_GASBeta[20] // D65
{0x0F12, 0x0019 }, //001A//0000 // #ash_GASBeta[21]
{0x0F12, 0x0017 }, //0017//0000 // #ash_GASBeta[22]
{0x0F12, 0x0000 }, //0000//0000 // #ash_GASBeta[23]
{0x0F12, 0x0032 }, //0031//0000 // #ash_GASBeta[24] // D75
{0x0F12, 0x0019 }, //0019//0000 // #ash_GASBeta[25]
{0x0F12, 0x0017 }, //0014//0000 // #ash_GASBeta[26]
{0x0F12, 0x0000 }, //0000//0000 // #ash_GASBeta[27]
{0x0F12, 0x0032 }, //0035//0000 // #ash_GASOutdoorBeta[0] // Outdoor
{0x0F12, 0x0019 }, //001D//0000 // #ash_GASOutdoorBeta[1]
{0x0F12, 0x0017 }, //001A//0000 // #ash_GASOutdoorBeta[2]
{0x0F12, 0x0000 }, //0000//0000 // #ash_GASOutdoorBeta[3]
              
// Parabloic function
{0x002A, 0x075A },
{0x0F12, 0x0000 }, //0000 // #ash_bParabolicEstimation
{0x0F12, 0x0400 }, //0400 // #ash_uParabolicCenterX
{0x0F12, 0x0300 }, //0300 // #ash_uParabolicCenterY
{0x0F12, 0x0010 }, //0010 // #ash_uParabolicScalingA
{0x0F12, 0x0011 }, //0011 // #ash_uParabolicScalingB
              
//ash_CGrasAlp },has
{0x002A, 0x06C6 },
{0x0F12, 0x0100 }, //0100 //ash_CGrasAlphas_0_
{0x0F12, 0x0100 }, //0100 //ash_CGrasAlphas_1_
{0x0F12, 0x0100 }, //0100 //ash_CGrasAlphas_2_
{0x0F12, 0x0100 }, //0100 //ash_CGrasAlphas_3_
{0x002A, 0x0E3C },                          
{0x0F12, 0x00C0 }, // #awbb_Alpha_Comp_Mode               
{0x002A, 0x074E },
{0x0F12, 0x0000 }, // #ash_bLumaMode //use Beta : 0001 not use Beta : 0000
{0x002A, 0x0D30 },
{0x0F12, 0x02A7 }, //02A7 // #awbb_GLocusR
{0x0F12, 0x0343 }, //0343 // #awbb_GLocusB
              
// GAS LUT start address // 7000_347C
{0x002A, 0x0754 },
{0x0F12, 0x347C },
{0x0F12, 0x7000 },
// GAS LUT    
{0x002A, 0x347C },
{0x0F12, 0x0220 }, //#TVAR_ash_pGAS[0]
{0x0F12, 0x01D0 }, //#TVAR_ash_pGAS[1]
{0x0F12, 0x019C }, //#TVAR_ash_pGAS[2]
{0x0F12, 0x0163 }, //#TVAR_ash_pGAS[3]
{0x0F12, 0x0138 }, //#TVAR_ash_pGAS[4]
{0x0F12, 0x011C }, //#TVAR_ash_pGAS[5]
{0x0F12, 0x010D }, //#TVAR_ash_pGAS[6]
{0x0F12, 0x0112 }, //#TVAR_ash_pGAS[7]
{0x0F12, 0x0123 }, //#TVAR_ash_pGAS[8]
{0x0F12, 0x0149 }, //#TVAR_ash_pGAS[9]
{0x0F12, 0x0180 }, //#TVAR_ash_pGAS[10]
{0x0F12, 0x01B0 }, //#TVAR_ash_pGAS[11]
{0x0F12, 0x01E4 }, //#TVAR_ash_pGAS[12]
{0x0F12, 0x01C3 }, //#TVAR_ash_pGAS[13]
{0x0F12, 0x019A }, //#TVAR_ash_pGAS[14]
{0x0F12, 0x0156 }, //#TVAR_ash_pGAS[15]
{0x0F12, 0x0115 }, //#TVAR_ash_pGAS[16]
{0x0F12, 0x00E9 }, //#TVAR_ash_pGAS[17]
{0x0F12, 0x00CB }, //#TVAR_ash_pGAS[18]
{0x0F12, 0x00BE }, //#TVAR_ash_pGAS[19]
{0x0F12, 0x00C4 }, //#TVAR_ash_pGAS[20]
{0x0F12, 0x00DB }, //#TVAR_ash_pGAS[21]
{0x0F12, 0x0101 }, //#TVAR_ash_pGAS[22]
{0x0F12, 0x013D }, //#TVAR_ash_pGAS[23]
{0x0F12, 0x0184 }, //#TVAR_ash_pGAS[24]
{0x0F12, 0x01AF }, //#TVAR_ash_pGAS[25]
{0x0F12, 0x0197 }, //#TVAR_ash_pGAS[26]
{0x0F12, 0x015C }, //#TVAR_ash_pGAS[27]
{0x0F12, 0x010A }, //#TVAR_ash_pGAS[28]
{0x0F12, 0x00CC }, //#TVAR_ash_pGAS[29]
{0x0F12, 0x009C }, //#TVAR_ash_pGAS[30]
{0x0F12, 0x007D }, //#TVAR_ash_pGAS[31]
{0x0F12, 0x006F }, //#TVAR_ash_pGAS[32]
{0x0F12, 0x0078 }, //#TVAR_ash_pGAS[33]
{0x0F12, 0x0092 }, //#TVAR_ash_pGAS[34]
{0x0F12, 0x00BC }, //#TVAR_ash_pGAS[35]
{0x0F12, 0x00F8 }, //#TVAR_ash_pGAS[36]
{0x0F12, 0x0149 }, //#TVAR_ash_pGAS[37]
{0x0F12, 0x0189 }, //#TVAR_ash_pGAS[38]
{0x0F12, 0x016D }, //#TVAR_ash_pGAS[39]
{0x0F12, 0x0122 }, //#TVAR_ash_pGAS[40]
{0x0F12, 0x00D2 }, //#TVAR_ash_pGAS[41]
{0x0F12, 0x0091 }, //#TVAR_ash_pGAS[42]
{0x0F12, 0x005F }, //#TVAR_ash_pGAS[43]
{0x0F12, 0x0042 }, //#TVAR_ash_pGAS[44]
{0x0F12, 0x0035 }, //#TVAR_ash_pGAS[45]
{0x0F12, 0x003E }, //#TVAR_ash_pGAS[46]
{0x0F12, 0x0058 }, //#TVAR_ash_pGAS[47]
{0x0F12, 0x0085 }, //#TVAR_ash_pGAS[48]
{0x0F12, 0x00C4 }, //#TVAR_ash_pGAS[49]
{0x0F12, 0x0119 }, //#TVAR_ash_pGAS[50]
{0x0F12, 0x0165 }, //#TVAR_ash_pGAS[51]
{0x0F12, 0x0149 }, //#TVAR_ash_pGAS[52]
{0x0F12, 0x00FA }, //#TVAR_ash_pGAS[53]
{0x0F12, 0x00A9 }, //#TVAR_ash_pGAS[54]
{0x0F12, 0x0066 }, //#TVAR_ash_pGAS[55]
{0x0F12, 0x0037 }, //#TVAR_ash_pGAS[56]
{0x0F12, 0x0019 }, //#TVAR_ash_pGAS[57]
{0x0F12, 0x0010 }, //#TVAR_ash_pGAS[58]
{0x0F12, 0x0018 }, //#TVAR_ash_pGAS[59]
{0x0F12, 0x0032 }, //#TVAR_ash_pGAS[60]
{0x0F12, 0x0062 }, //#TVAR_ash_pGAS[61]
{0x0F12, 0x00A2 }, //#TVAR_ash_pGAS[62]
{0x0F12, 0x00F5 }, //#TVAR_ash_pGAS[63]
{0x0F12, 0x0145 }, //#TVAR_ash_pGAS[64]
{0x0F12, 0x0138 }, //#TVAR_ash_pGAS[65]
{0x0F12, 0x00EA }, //#TVAR_ash_pGAS[66]
{0x0F12, 0x0099 }, //#TVAR_ash_pGAS[67]
{0x0F12, 0x0056 }, //#TVAR_ash_pGAS[68]
{0x0F12, 0x0025 }, //#TVAR_ash_pGAS[69]
{0x0F12, 0x000A }, //#TVAR_ash_pGAS[70]
{0x0F12, 0x0000 }, //#TVAR_ash_pGAS[71]
{0x0F12, 0x0008 }, //#TVAR_ash_pGAS[72]
{0x0F12, 0x0023 }, //#TVAR_ash_pGAS[73]
{0x0F12, 0x0052 }, //#TVAR_ash_pGAS[74]
{0x0F12, 0x0094 }, //#TVAR_ash_pGAS[75]
{0x0F12, 0x00E7 }, //#TVAR_ash_pGAS[76]
{0x0F12, 0x013D }, //#TVAR_ash_pGAS[77]
{0x0F12, 0x0138 }, //#TVAR_ash_pGAS[78]
{0x0F12, 0x00EB }, //#TVAR_ash_pGAS[79]
{0x0F12, 0x0097 }, //#TVAR_ash_pGAS[80]
{0x0F12, 0x0057 }, //#TVAR_ash_pGAS[81]
{0x0F12, 0x0029 }, //#TVAR_ash_pGAS[82]
{0x0F12, 0x000A }, //#TVAR_ash_pGAS[83]
{0x0F12, 0x0002 }, //#TVAR_ash_pGAS[84]
{0x0F12, 0x000B }, //#TVAR_ash_pGAS[85]
{0x0F12, 0x0025 }, //#TVAR_ash_pGAS[86]
{0x0F12, 0x0055 }, //#TVAR_ash_pGAS[87]
{0x0F12, 0x0096 }, //#TVAR_ash_pGAS[88]
{0x0F12, 0x00EB }, //#TVAR_ash_pGAS[89]
{0x0F12, 0x013D }, //#TVAR_ash_pGAS[90]
{0x0F12, 0x0148 }, //#TVAR_ash_pGAS[91]
{0x0F12, 0x00FF }, //#TVAR_ash_pGAS[92]
{0x0F12, 0x00AB }, //#TVAR_ash_pGAS[93]
{0x0F12, 0x006C }, //#TVAR_ash_pGAS[94]
{0x0F12, 0x003D }, //#TVAR_ash_pGAS[95]
{0x0F12, 0x0021 }, //#TVAR_ash_pGAS[96]
{0x0F12, 0x0017 }, //#TVAR_ash_pGAS[97]
{0x0F12, 0x0021 }, //#TVAR_ash_pGAS[98]
{0x0F12, 0x003C }, //#TVAR_ash_pGAS[99]
{0x0F12, 0x006D }, //#TVAR_ash_pGAS[100]
{0x0F12, 0x00AD }, //#TVAR_ash_pGAS[101]
{0x0F12, 0x0100 }, //#TVAR_ash_pGAS[102]
{0x0F12, 0x0153 }, //#TVAR_ash_pGAS[103]
{0x0F12, 0x016B }, //#TVAR_ash_pGAS[104]
{0x0F12, 0x0123 }, //#TVAR_ash_pGAS[105]
{0x0F12, 0x00D2 }, //#TVAR_ash_pGAS[106]
{0x0F12, 0x0093 }, //#TVAR_ash_pGAS[107]
{0x0F12, 0x0066 }, //#TVAR_ash_pGAS[108]
{0x0F12, 0x0049 }, //#TVAR_ash_pGAS[109]
{0x0F12, 0x003F }, //#TVAR_ash_pGAS[110]
{0x0F12, 0x004A }, //#TVAR_ash_pGAS[111]
{0x0F12, 0x0069 }, //#TVAR_ash_pGAS[112]
{0x0F12, 0x0099 }, //#TVAR_ash_pGAS[113]
{0x0F12, 0x00D8 }, //#TVAR_ash_pGAS[114]
{0x0F12, 0x0125 }, //#TVAR_ash_pGAS[115]
{0x0F12, 0x016E }, //#TVAR_ash_pGAS[116]
{0x0F12, 0x0190 }, //#TVAR_ash_pGAS[117]
{0x0F12, 0x0155 }, //#TVAR_ash_pGAS[118]
{0x0F12, 0x0106 }, //#TVAR_ash_pGAS[119]
{0x0F12, 0x00CC }, //#TVAR_ash_pGAS[120]
{0x0F12, 0x009F }, //#TVAR_ash_pGAS[121]
{0x0F12, 0x0086 }, //#TVAR_ash_pGAS[122]
{0x0F12, 0x007D }, //#TVAR_ash_pGAS[123]
{0x0F12, 0x0088 }, //#TVAR_ash_pGAS[124]
{0x0F12, 0x00A4 }, //#TVAR_ash_pGAS[125]
{0x0F12, 0x00D2 }, //#TVAR_ash_pGAS[126]
{0x0F12, 0x0113 }, //#TVAR_ash_pGAS[127]
{0x0F12, 0x015C }, //#TVAR_ash_pGAS[128]
{0x0F12, 0x0192 }, //#TVAR_ash_pGAS[129]
{0x0F12, 0x01A8 }, //#TVAR_ash_pGAS[130]
{0x0F12, 0x0185 }, //#TVAR_ash_pGAS[131]
{0x0F12, 0x0140 }, //#TVAR_ash_pGAS[132]
{0x0F12, 0x0107 }, //#TVAR_ash_pGAS[133]
{0x0F12, 0x00DC }, //#TVAR_ash_pGAS[134]
{0x0F12, 0x00C4 }, //#TVAR_ash_pGAS[135]
{0x0F12, 0x00BE }, //#TVAR_ash_pGAS[136]
{0x0F12, 0x00C9 }, //#TVAR_ash_pGAS[137]
{0x0F12, 0x00E3 }, //#TVAR_ash_pGAS[138]
{0x0F12, 0x010D }, //#TVAR_ash_pGAS[139]
{0x0F12, 0x014D }, //#TVAR_ash_pGAS[140]
{0x0F12, 0x018F }, //#TVAR_ash_pGAS[141]
{0x0F12, 0x01A9 }, //#TVAR_ash_pGAS[142]
{0x0F12, 0x01CD }, //#TVAR_ash_pGAS[143]
{0x0F12, 0x0174 }, //#TVAR_ash_pGAS[144]
{0x0F12, 0x0149 }, //#TVAR_ash_pGAS[145]
{0x0F12, 0x0118 }, //#TVAR_ash_pGAS[146]
{0x0F12, 0x00F2 }, //#TVAR_ash_pGAS[147]
{0x0F12, 0x00D8 }, //#TVAR_ash_pGAS[148]
{0x0F12, 0x00CC }, //#TVAR_ash_pGAS[149]
{0x0F12, 0x00CD }, //#TVAR_ash_pGAS[150]
{0x0F12, 0x00DF }, //#TVAR_ash_pGAS[151]
{0x0F12, 0x00FC }, //#TVAR_ash_pGAS[152]
{0x0F12, 0x0125 }, //#TVAR_ash_pGAS[153]
{0x0F12, 0x0150 }, //#TVAR_ash_pGAS[154]
{0x0F12, 0x018B }, //#TVAR_ash_pGAS[155]
{0x0F12, 0x017B }, //#TVAR_ash_pGAS[156]
{0x0F12, 0x0144 }, //#TVAR_ash_pGAS[157]
{0x0F12, 0x0109 }, //#TVAR_ash_pGAS[158]
{0x0F12, 0x00D7 }, //#TVAR_ash_pGAS[159]
{0x0F12, 0x00B4 }, //#TVAR_ash_pGAS[160]
{0x0F12, 0x009A }, //#TVAR_ash_pGAS[161]
{0x0F12, 0x008E }, //#TVAR_ash_pGAS[162]
{0x0F12, 0x0090 }, //#TVAR_ash_pGAS[163]
{0x0F12, 0x00A2 }, //#TVAR_ash_pGAS[164]
{0x0F12, 0x00C2 }, //#TVAR_ash_pGAS[165]
{0x0F12, 0x00EE }, //#TVAR_ash_pGAS[166]
{0x0F12, 0x0127 }, //#TVAR_ash_pGAS[167]
{0x0F12, 0x015A }, //#TVAR_ash_pGAS[168]
{0x0F12, 0x0157 }, //#TVAR_ash_pGAS[169]
{0x0F12, 0x0116 }, //#TVAR_ash_pGAS[170]
{0x0F12, 0x00D4 }, //#TVAR_ash_pGAS[171]
{0x0F12, 0x00A0 }, //#TVAR_ash_pGAS[172]
{0x0F12, 0x007A }, //#TVAR_ash_pGAS[173]
{0x0F12, 0x0061 }, //#TVAR_ash_pGAS[174]
{0x0F12, 0x0056 }, //#TVAR_ash_pGAS[175]
{0x0F12, 0x005B }, //#TVAR_ash_pGAS[176]
{0x0F12, 0x006F }, //#TVAR_ash_pGAS[177]
{0x0F12, 0x008F }, //#TVAR_ash_pGAS[178]
{0x0F12, 0x00BE }, //#TVAR_ash_pGAS[179]
{0x0F12, 0x00FA }, //#TVAR_ash_pGAS[180]
{0x0F12, 0x013A }, //#TVAR_ash_pGAS[181]
{0x0F12, 0x0133 }, //#TVAR_ash_pGAS[182]
{0x0F12, 0x00EA }, //#TVAR_ash_pGAS[183]
{0x0F12, 0x00A9 }, //#TVAR_ash_pGAS[184]
{0x0F12, 0x0075 }, //#TVAR_ash_pGAS[185]
{0x0F12, 0x004D }, //#TVAR_ash_pGAS[186]
{0x0F12, 0x0034 }, //#TVAR_ash_pGAS[187]
{0x0F12, 0x002A }, //#TVAR_ash_pGAS[188]
{0x0F12, 0x002F }, //#TVAR_ash_pGAS[189]
{0x0F12, 0x0043 }, //#TVAR_ash_pGAS[190]
{0x0F12, 0x0066 }, //#TVAR_ash_pGAS[191]
{0x0F12, 0x0097 }, //#TVAR_ash_pGAS[192]
{0x0F12, 0x00D7 }, //#TVAR_ash_pGAS[193]
{0x0F12, 0x011B }, //#TVAR_ash_pGAS[194]
{0x0F12, 0x0115 }, //#TVAR_ash_pGAS[195]
{0x0F12, 0x00CB }, //#TVAR_ash_pGAS[196]
{0x0F12, 0x008D }, //#TVAR_ash_pGAS[197]
{0x0F12, 0x0056 }, //#TVAR_ash_pGAS[198]
{0x0F12, 0x002F }, //#TVAR_ash_pGAS[199]
{0x0F12, 0x0016 }, //#TVAR_ash_pGAS[200]
{0x0F12, 0x000C }, //#TVAR_ash_pGAS[201]
{0x0F12, 0x0012 }, //#TVAR_ash_pGAS[202]
{0x0F12, 0x0029 }, //#TVAR_ash_pGAS[203]
{0x0F12, 0x004C }, //#TVAR_ash_pGAS[204]
{0x0F12, 0x007F }, //#TVAR_ash_pGAS[205]
{0x0F12, 0x00BF }, //#TVAR_ash_pGAS[206]
{0x0F12, 0x0109 }, //#TVAR_ash_pGAS[207]
{0x0F12, 0x0107 }, //#TVAR_ash_pGAS[208]
{0x0F12, 0x00BC }, //#TVAR_ash_pGAS[209]
{0x0F12, 0x007D }, //#TVAR_ash_pGAS[210]
{0x0F12, 0x004B }, //#TVAR_ash_pGAS[211]
{0x0F12, 0x0022 }, //#TVAR_ash_pGAS[212]
{0x0F12, 0x0008 }, //#TVAR_ash_pGAS[213]
{0x0F12, 0x0000 }, //#TVAR_ash_pGAS[214]
{0x0F12, 0x0006 }, //#TVAR_ash_pGAS[215]
{0x0F12, 0x001E }, //#TVAR_ash_pGAS[216]
{0x0F12, 0x0043 }, //#TVAR_ash_pGAS[217]
{0x0F12, 0x0074 }, //#TVAR_ash_pGAS[218]
{0x0F12, 0x00B8 }, //#TVAR_ash_pGAS[219]
{0x0F12, 0x0100 }, //#TVAR_ash_pGAS[220]
{0x0F12, 0x0102 }, //#TVAR_ash_pGAS[221]
{0x0F12, 0x00BB }, //#TVAR_ash_pGAS[222]
{0x0F12, 0x007C }, //#TVAR_ash_pGAS[223]
{0x0F12, 0x0049 }, //#TVAR_ash_pGAS[224]
{0x0F12, 0x0022 }, //#TVAR_ash_pGAS[225]
{0x0F12, 0x0009 }, //#TVAR_ash_pGAS[226]
{0x0F12, 0x0001 }, //#TVAR_ash_pGAS[227]
{0x0F12, 0x0009 }, //#TVAR_ash_pGAS[228]
{0x0F12, 0x0021 }, //#TVAR_ash_pGAS[229]
{0x0F12, 0x0047 }, //#TVAR_ash_pGAS[230]
{0x0F12, 0x0077 }, //#TVAR_ash_pGAS[231]
{0x0F12, 0x00BA }, //#TVAR_ash_pGAS[232]
{0x0F12, 0x0105 }, //#TVAR_ash_pGAS[233]
{0x0F12, 0x010D }, //#TVAR_ash_pGAS[234]
{0x0F12, 0x00C8 }, //#TVAR_ash_pGAS[235]
{0x0F12, 0x0088 }, //#TVAR_ash_pGAS[236]
{0x0F12, 0x0057 }, //#TVAR_ash_pGAS[237]
{0x0F12, 0x0032 }, //#TVAR_ash_pGAS[238]
{0x0F12, 0x001A }, //#TVAR_ash_pGAS[239]
{0x0F12, 0x0012 }, //#TVAR_ash_pGAS[240]
{0x0F12, 0x0019 }, //#TVAR_ash_pGAS[241]
{0x0F12, 0x0032 }, //#TVAR_ash_pGAS[242]
{0x0F12, 0x0059 }, //#TVAR_ash_pGAS[243]
{0x0F12, 0x0088 }, //#TVAR_ash_pGAS[244]
{0x0F12, 0x00C8 }, //#TVAR_ash_pGAS[245]
{0x0F12, 0x0116 }, //#TVAR_ash_pGAS[246]
{0x0F12, 0x0128 }, //#TVAR_ash_pGAS[247]
{0x0F12, 0x00E3 }, //#TVAR_ash_pGAS[248]
{0x0F12, 0x00A4 }, //#TVAR_ash_pGAS[249]
{0x0F12, 0x0074 }, //#TVAR_ash_pGAS[250]
{0x0F12, 0x0051 }, //#TVAR_ash_pGAS[251]
{0x0F12, 0x003B }, //#TVAR_ash_pGAS[252]
{0x0F12, 0x0033 }, //#TVAR_ash_pGAS[253]
{0x0F12, 0x003C }, //#TVAR_ash_pGAS[254]
{0x0F12, 0x0055 }, //#TVAR_ash_pGAS[255]
{0x0F12, 0x007B }, //#TVAR_ash_pGAS[256]
{0x0F12, 0x00AB }, //#TVAR_ash_pGAS[257]
{0x0F12, 0x00E8 }, //#TVAR_ash_pGAS[258]
{0x0F12, 0x012E }, //#TVAR_ash_pGAS[259]
{0x0F12, 0x0145 }, //#TVAR_ash_pGAS[260]
{0x0F12, 0x010C }, //#TVAR_ash_pGAS[261]
{0x0F12, 0x00CC }, //#TVAR_ash_pGAS[262]
{0x0F12, 0x009E }, //#TVAR_ash_pGAS[263]
{0x0F12, 0x007B }, //#TVAR_ash_pGAS[264]
{0x0F12, 0x0069 }, //#TVAR_ash_pGAS[265]
{0x0F12, 0x0063 }, //#TVAR_ash_pGAS[266]
{0x0F12, 0x006C }, //#TVAR_ash_pGAS[267]
{0x0F12, 0x0083 }, //#TVAR_ash_pGAS[268]
{0x0F12, 0x00AA }, //#TVAR_ash_pGAS[269]
{0x0F12, 0x00D8 }, //#TVAR_ash_pGAS[270]
{0x0F12, 0x0115 }, //#TVAR_ash_pGAS[271]
{0x0F12, 0x0147 }, //#TVAR_ash_pGAS[272]
{0x0F12, 0x015C }, //#TVAR_ash_pGAS[273]
{0x0F12, 0x012F }, //#TVAR_ash_pGAS[274]
{0x0F12, 0x00F8 }, //#TVAR_ash_pGAS[275]
{0x0F12, 0x00C9 }, //#TVAR_ash_pGAS[276]
{0x0F12, 0x00AB }, //#TVAR_ash_pGAS[277]
{0x0F12, 0x0099 }, //#TVAR_ash_pGAS[278]
{0x0F12, 0x0093 }, //#TVAR_ash_pGAS[279]
{0x0F12, 0x009E }, //#TVAR_ash_pGAS[280]
{0x0F12, 0x00B5 }, //#TVAR_ash_pGAS[281]
{0x0F12, 0x00D7 }, //#TVAR_ash_pGAS[282]
{0x0F12, 0x0108 }, //#TVAR_ash_pGAS[283]
{0x0F12, 0x0141 }, //#TVAR_ash_pGAS[284]
{0x0F12, 0x015B }, //#TVAR_ash_pGAS[285]
{0x0F12, 0x018E }, //#TVAR_ash_pGAS[286]
{0x0F12, 0x0147 }, //#TVAR_ash_pGAS[287]
{0x0F12, 0x0121 }, //#TVAR_ash_pGAS[288]
{0x0F12, 0x00F6 }, //#TVAR_ash_pGAS[289]
{0x0F12, 0x00D9 }, //#TVAR_ash_pGAS[290]
{0x0F12, 0x00C8 }, //#TVAR_ash_pGAS[291]
{0x0F12, 0x00C1 }, //#TVAR_ash_pGAS[292]
{0x0F12, 0x00CC }, //#TVAR_ash_pGAS[293]
{0x0F12, 0x00E2 }, //#TVAR_ash_pGAS[294]
{0x0F12, 0x0107 }, //#TVAR_ash_pGAS[295]
{0x0F12, 0x0134 }, //#TVAR_ash_pGAS[296]
{0x0F12, 0x0160 }, //#TVAR_ash_pGAS[297]
{0x0F12, 0x0193 }, //#TVAR_ash_pGAS[298]
{0x0F12, 0x0158 }, //#TVAR_ash_pGAS[299]
{0x0F12, 0x0127 }, //#TVAR_ash_pGAS[300]
{0x0F12, 0x00EF }, //#TVAR_ash_pGAS[301]
{0x0F12, 0x00C3 }, //#TVAR_ash_pGAS[302]
{0x0F12, 0x00A3 }, //#TVAR_ash_pGAS[303]
{0x0F12, 0x0090 }, //#TVAR_ash_pGAS[304]
{0x0F12, 0x008B }, //#TVAR_ash_pGAS[305]
{0x0F12, 0x0092 }, //#TVAR_ash_pGAS[306]
{0x0F12, 0x00A8 }, //#TVAR_ash_pGAS[307]
{0x0F12, 0x00CE }, //#TVAR_ash_pGAS[308]
{0x0F12, 0x00FF }, //#TVAR_ash_pGAS[309]
{0x0F12, 0x0138 }, //#TVAR_ash_pGAS[310]
{0x0F12, 0x0169 }, //#TVAR_ash_pGAS[311]
{0x0F12, 0x013B }, //#TVAR_ash_pGAS[312]
{0x0F12, 0x00FD }, //#TVAR_ash_pGAS[313]
{0x0F12, 0x00C0 }, //#TVAR_ash_pGAS[314]
{0x0F12, 0x0092 }, //#TVAR_ash_pGAS[315]
{0x0F12, 0x0072 }, //#TVAR_ash_pGAS[316]
{0x0F12, 0x005C }, //#TVAR_ash_pGAS[317]
{0x0F12, 0x0055 }, //#TVAR_ash_pGAS[318]
{0x0F12, 0x005F }, //#TVAR_ash_pGAS[319]
{0x0F12, 0x0076 }, //#TVAR_ash_pGAS[320]
{0x0F12, 0x009B }, //#TVAR_ash_pGAS[321]
{0x0F12, 0x00CD }, //#TVAR_ash_pGAS[322]
{0x0F12, 0x010D }, //#TVAR_ash_pGAS[323]
{0x0F12, 0x014A }, //#TVAR_ash_pGAS[324]
{0x0F12, 0x011C }, //#TVAR_ash_pGAS[325]
{0x0F12, 0x00DA }, //#TVAR_ash_pGAS[326]
{0x0F12, 0x009E }, //#TVAR_ash_pGAS[327]
{0x0F12, 0x006C }, //#TVAR_ash_pGAS[328]
{0x0F12, 0x0048 }, //#TVAR_ash_pGAS[329]
{0x0F12, 0x0031 }, //#TVAR_ash_pGAS[330]
{0x0F12, 0x002A }, //#TVAR_ash_pGAS[331]
{0x0F12, 0x0033 }, //#TVAR_ash_pGAS[332]
{0x0F12, 0x004A }, //#TVAR_ash_pGAS[333]
{0x0F12, 0x0071 }, //#TVAR_ash_pGAS[334]
{0x0F12, 0x00A4 }, //#TVAR_ash_pGAS[335]
{0x0F12, 0x00E6 }, //#TVAR_ash_pGAS[336]
{0x0F12, 0x012B }, //#TVAR_ash_pGAS[337]
{0x0F12, 0x0108 }, //#TVAR_ash_pGAS[338]
{0x0F12, 0x00C2 }, //#TVAR_ash_pGAS[339]
{0x0F12, 0x0085 }, //#TVAR_ash_pGAS[340]
{0x0F12, 0x0054 }, //#TVAR_ash_pGAS[341]
{0x0F12, 0x002C }, //#TVAR_ash_pGAS[342]
{0x0F12, 0x0014 }, //#TVAR_ash_pGAS[343]
{0x0F12, 0x000C }, //#TVAR_ash_pGAS[344]
{0x0F12, 0x0014 }, //#TVAR_ash_pGAS[345]
{0x0F12, 0x002D }, //#TVAR_ash_pGAS[346]
{0x0F12, 0x0055 }, //#TVAR_ash_pGAS[347]
{0x0F12, 0x0088 }, //#TVAR_ash_pGAS[348]
{0x0F12, 0x00C9 }, //#TVAR_ash_pGAS[349]
{0x0F12, 0x0111 }, //#TVAR_ash_pGAS[350]
{0x0F12, 0x0101 }, //#TVAR_ash_pGAS[351]
{0x0F12, 0x00B9 }, //#TVAR_ash_pGAS[352]
{0x0F12, 0x007C }, //#TVAR_ash_pGAS[353]
{0x0F12, 0x004A }, //#TVAR_ash_pGAS[354]
{0x0F12, 0x0021 }, //#TVAR_ash_pGAS[355]
{0x0F12, 0x0009 }, //#TVAR_ash_pGAS[356]
{0x0F12, 0x0000 }, //#TVAR_ash_pGAS[357]
{0x0F12, 0x0007 }, //#TVAR_ash_pGAS[358]
{0x0F12, 0x0020 }, //#TVAR_ash_pGAS[359]
{0x0F12, 0x0047 }, //#TVAR_ash_pGAS[360]
{0x0F12, 0x0079 }, //#TVAR_ash_pGAS[361]
{0x0F12, 0x00BA }, //#TVAR_ash_pGAS[362]
{0x0F12, 0x0106 }, //#TVAR_ash_pGAS[363]
{0x0F12, 0x0104 }, //#TVAR_ash_pGAS[364]
{0x0F12, 0x00BE }, //#TVAR_ash_pGAS[365]
{0x0F12, 0x007F }, //#TVAR_ash_pGAS[366]
{0x0F12, 0x004D }, //#TVAR_ash_pGAS[367]
{0x0F12, 0x0025 }, //#TVAR_ash_pGAS[368]
{0x0F12, 0x000A }, //#TVAR_ash_pGAS[369]
{0x0F12, 0x0001 }, //#TVAR_ash_pGAS[370]
{0x0F12, 0x0008 }, //#TVAR_ash_pGAS[371]
{0x0F12, 0x001F }, //#TVAR_ash_pGAS[372]
{0x0F12, 0x0044 }, //#TVAR_ash_pGAS[373]
{0x0F12, 0x0074 }, //#TVAR_ash_pGAS[374]
{0x0F12, 0x00B4 }, //#TVAR_ash_pGAS[375]
{0x0F12, 0x0101 }, //#TVAR_ash_pGAS[376]
{0x0F12, 0x0114 }, //#TVAR_ash_pGAS[377]
{0x0F12, 0x00CE }, //#TVAR_ash_pGAS[378]
{0x0F12, 0x008F }, //#TVAR_ash_pGAS[379]
{0x0F12, 0x005D }, //#TVAR_ash_pGAS[380]
{0x0F12, 0x0036 }, //#TVAR_ash_pGAS[381]
{0x0F12, 0x001C }, //#TVAR_ash_pGAS[382]
{0x0F12, 0x0011 }, //#TVAR_ash_pGAS[383]
{0x0F12, 0x0018 }, //#TVAR_ash_pGAS[384]
{0x0F12, 0x002E }, //#TVAR_ash_pGAS[385]
{0x0F12, 0x0052 }, //#TVAR_ash_pGAS[386]
{0x0F12, 0x0080 }, //#TVAR_ash_pGAS[387]
{0x0F12, 0x00BC }, //#TVAR_ash_pGAS[388]
{0x0F12, 0x0108 }, //#TVAR_ash_pGAS[389]
{0x0F12, 0x0136 }, //#TVAR_ash_pGAS[390]
{0x0F12, 0x00EE }, //#TVAR_ash_pGAS[391]
{0x0F12, 0x00AD }, //#TVAR_ash_pGAS[392]
{0x0F12, 0x007D }, //#TVAR_ash_pGAS[393]
{0x0F12, 0x0058 }, //#TVAR_ash_pGAS[394]
{0x0F12, 0x003E }, //#TVAR_ash_pGAS[395]
{0x0F12, 0x0032 }, //#TVAR_ash_pGAS[396]
{0x0F12, 0x0037 }, //#TVAR_ash_pGAS[397]
{0x0F12, 0x004D }, //#TVAR_ash_pGAS[398]
{0x0F12, 0x006F }, //#TVAR_ash_pGAS[399]
{0x0F12, 0x009D }, //#TVAR_ash_pGAS[400]
{0x0F12, 0x00D4 }, //#TVAR_ash_pGAS[401]
{0x0F12, 0x011D }, //#TVAR_ash_pGAS[402]
{0x0F12, 0x0158 }, //#TVAR_ash_pGAS[403]
{0x0F12, 0x0119 }, //#TVAR_ash_pGAS[404]
{0x0F12, 0x00D9 }, //#TVAR_ash_pGAS[405]
{0x0F12, 0x00AB }, //#TVAR_ash_pGAS[406]
{0x0F12, 0x0085 }, //#TVAR_ash_pGAS[407]
{0x0F12, 0x006E }, //#TVAR_ash_pGAS[408]
{0x0F12, 0x0063 }, //#TVAR_ash_pGAS[409]
{0x0F12, 0x0066 }, //#TVAR_ash_pGAS[410]
{0x0F12, 0x007B }, //#TVAR_ash_pGAS[411]
{0x0F12, 0x009A }, //#TVAR_ash_pGAS[412]
{0x0F12, 0x00C5 }, //#TVAR_ash_pGAS[413]
{0x0F12, 0x00FD }, //#TVAR_ash_pGAS[414]
{0x0F12, 0x0135 }, //#TVAR_ash_pGAS[415]
{0x0F12, 0x0173 }, //#TVAR_ash_pGAS[416]
{0x0F12, 0x0140 }, //#TVAR_ash_pGAS[417]
{0x0F12, 0x0106 }, //#TVAR_ash_pGAS[418]
{0x0F12, 0x00D7 }, //#TVAR_ash_pGAS[419]
{0x0F12, 0x00B7 }, //#TVAR_ash_pGAS[420]
{0x0F12, 0x00A0 }, //#TVAR_ash_pGAS[421]
{0x0F12, 0x0096 }, //#TVAR_ash_pGAS[422]
{0x0F12, 0x0097 }, //#TVAR_ash_pGAS[423]
{0x0F12, 0x00A9 }, //#TVAR_ash_pGAS[424]
{0x0F12, 0x00C6 }, //#TVAR_ash_pGAS[425]
{0x0F12, 0x00F0 }, //#TVAR_ash_pGAS[426]
{0x0F12, 0x0126 }, //#TVAR_ash_pGAS[427]
{0x0F12, 0x0145 }, //#TVAR_ash_pGAS[428]
{0x0F12, 0x0163 }, //#TVAR_ash_pGAS[429]
{0x0F12, 0x012E }, //#TVAR_ash_pGAS[430]
{0x0F12, 0x0108 }, //#TVAR_ash_pGAS[431]
{0x0F12, 0x00E2 }, //#TVAR_ash_pGAS[432]
{0x0F12, 0x00C5 }, //#TVAR_ash_pGAS[433]
{0x0F12, 0x00B9 }, //#TVAR_ash_pGAS[434]
{0x0F12, 0x00B2 }, //#TVAR_ash_pGAS[435]
{0x0F12, 0x00B9 }, //#TVAR_ash_pGAS[436]
{0x0F12, 0x00CE }, //#TVAR_ash_pGAS[437]
{0x0F12, 0x00EF }, //#TVAR_ash_pGAS[438]
{0x0F12, 0x0119 }, //#TVAR_ash_pGAS[439]
{0x0F12, 0x0144 }, //#TVAR_ash_pGAS[440]
{0x0F12, 0x016D }, //#TVAR_ash_pGAS[441]
{0x0F12, 0x012D }, //#TVAR_ash_pGAS[442]
{0x0F12, 0x0108 }, //#TVAR_ash_pGAS[443]
{0x0F12, 0x00D8 }, //#TVAR_ash_pGAS[444]
{0x0F12, 0x00AE }, //#TVAR_ash_pGAS[445]
{0x0F12, 0x0094 }, //#TVAR_ash_pGAS[446]
{0x0F12, 0x0087 }, //#TVAR_ash_pGAS[447]
{0x0F12, 0x0080 }, //#TVAR_ash_pGAS[448]
{0x0F12, 0x0088 }, //#TVAR_ash_pGAS[449]
{0x0F12, 0x009C }, //#TVAR_ash_pGAS[450]
{0x0F12, 0x00BC }, //#TVAR_ash_pGAS[451]
{0x0F12, 0x00E7 }, //#TVAR_ash_pGAS[452]
{0x0F12, 0x011C }, //#TVAR_ash_pGAS[453]
{0x0F12, 0x0143 }, //#TVAR_ash_pGAS[454]
{0x0F12, 0x010F }, //#TVAR_ash_pGAS[455]
{0x0F12, 0x00E3 }, //#TVAR_ash_pGAS[456]
{0x0F12, 0x00AA }, //#TVAR_ash_pGAS[457]
{0x0F12, 0x0081 }, //#TVAR_ash_pGAS[458]
{0x0F12, 0x0066 }, //#TVAR_ash_pGAS[459]
{0x0F12, 0x0056 }, //#TVAR_ash_pGAS[460]
{0x0F12, 0x0050 }, //#TVAR_ash_pGAS[461]
{0x0F12, 0x0059 }, //#TVAR_ash_pGAS[462]
{0x0F12, 0x006C }, //#TVAR_ash_pGAS[463]
{0x0F12, 0x008D }, //#TVAR_ash_pGAS[464]
{0x0F12, 0x00B9 }, //#TVAR_ash_pGAS[465]
{0x0F12, 0x00F1 }, //#TVAR_ash_pGAS[466]
{0x0F12, 0x0125 }, //#TVAR_ash_pGAS[467]
{0x0F12, 0x00EF }, //#TVAR_ash_pGAS[468]
{0x0F12, 0x00BB }, //#TVAR_ash_pGAS[469]
{0x0F12, 0x0083 }, //#TVAR_ash_pGAS[470]
{0x0F12, 0x005B }, //#TVAR_ash_pGAS[471]
{0x0F12, 0x003E }, //#TVAR_ash_pGAS[472]
{0x0F12, 0x002F }, //#TVAR_ash_pGAS[473]
{0x0F12, 0x002A }, //#TVAR_ash_pGAS[474]
{0x0F12, 0x0030 }, //#TVAR_ash_pGAS[475]
{0x0F12, 0x0044 }, //#TVAR_ash_pGAS[476]
{0x0F12, 0x0062 }, //#TVAR_ash_pGAS[477]
{0x0F12, 0x0091 }, //#TVAR_ash_pGAS[478]
{0x0F12, 0x00C9 }, //#TVAR_ash_pGAS[479]
{0x0F12, 0x00FF }, //#TVAR_ash_pGAS[480]
{0x0F12, 0x00D6 }, //#TVAR_ash_pGAS[481]
{0x0F12, 0x009F }, //#TVAR_ash_pGAS[482]
{0x0F12, 0x006A }, //#TVAR_ash_pGAS[483]
{0x0F12, 0x0041 }, //#TVAR_ash_pGAS[484]
{0x0F12, 0x0021 }, //#TVAR_ash_pGAS[485]
{0x0F12, 0x0011 }, //#TVAR_ash_pGAS[486]
{0x0F12, 0x000D }, //#TVAR_ash_pGAS[487]
{0x0F12, 0x0012 }, //#TVAR_ash_pGAS[488]
{0x0F12, 0x0025 }, //#TVAR_ash_pGAS[489]
{0x0F12, 0x0046 }, //#TVAR_ash_pGAS[490]
{0x0F12, 0x0070 }, //#TVAR_ash_pGAS[491]
{0x0F12, 0x00A9 }, //#TVAR_ash_pGAS[492]
{0x0F12, 0x00E1 }, //#TVAR_ash_pGAS[493]
{0x0F12, 0x00CB }, //#TVAR_ash_pGAS[494]
{0x0F12, 0x0094 }, //#TVAR_ash_pGAS[495]
{0x0F12, 0x005F }, //#TVAR_ash_pGAS[496]
{0x0F12, 0x0036 }, //#TVAR_ash_pGAS[497]
{0x0F12, 0x0017 }, //#TVAR_ash_pGAS[498]
{0x0F12, 0x0005 }, //#TVAR_ash_pGAS[499]
{0x0F12, 0x0001 }, //#TVAR_ash_pGAS[500]
{0x0F12, 0x0006 }, //#TVAR_ash_pGAS[501]
{0x0F12, 0x0018 }, //#TVAR_ash_pGAS[502]
{0x0F12, 0x0037 }, //#TVAR_ash_pGAS[503]
{0x0F12, 0x005E }, //#TVAR_ash_pGAS[504]
{0x0F12, 0x009A }, //#TVAR_ash_pGAS[505]
{0x0F12, 0x00D9 }, //#TVAR_ash_pGAS[506]
{0x0F12, 0x00C9 }, //#TVAR_ash_pGAS[507]
{0x0F12, 0x0094 }, //#TVAR_ash_pGAS[508]
{0x0F12, 0x0060 }, //#TVAR_ash_pGAS[509]
{0x0F12, 0x0037 }, //#TVAR_ash_pGAS[510]
{0x0F12, 0x0018 }, //#TVAR_ash_pGAS[511]
{0x0F12, 0x0005 }, //#TVAR_ash_pGAS[512]
{0x0F12, 0x0000 }, //#TVAR_ash_pGAS[513]
{0x0F12, 0x0005 }, //#TVAR_ash_pGAS[514]
{0x0F12, 0x0017 }, //#TVAR_ash_pGAS[515]
{0x0F12, 0x0033 }, //#TVAR_ash_pGAS[516]
{0x0F12, 0x005A }, //#TVAR_ash_pGAS[517]
{0x0F12, 0x0090 }, //#TVAR_ash_pGAS[518]
{0x0F12, 0x00CF }, //#TVAR_ash_pGAS[519]
{0x0F12, 0x00D8 }, //#TVAR_ash_pGAS[520]
{0x0F12, 0x00A3 }, //#TVAR_ash_pGAS[521]
{0x0F12, 0x006D }, //#TVAR_ash_pGAS[522]
{0x0F12, 0x0044 }, //#TVAR_ash_pGAS[523]
{0x0F12, 0x0028 }, //#TVAR_ash_pGAS[524]
{0x0F12, 0x0015 }, //#TVAR_ash_pGAS[525]
{0x0F12, 0x000D }, //#TVAR_ash_pGAS[526]
{0x0F12, 0x0013 }, //#TVAR_ash_pGAS[527]
{0x0F12, 0x0023 }, //#TVAR_ash_pGAS[528]
{0x0F12, 0x003F }, //#TVAR_ash_pGAS[529]
{0x0F12, 0x0063 }, //#TVAR_ash_pGAS[530]
{0x0F12, 0x0095 }, //#TVAR_ash_pGAS[531]
{0x0F12, 0x00D3 }, //#TVAR_ash_pGAS[532]
{0x0F12, 0x00F6 }, //#TVAR_ash_pGAS[533]
{0x0F12, 0x00C2 }, //#TVAR_ash_pGAS[534]
{0x0F12, 0x008A }, //#TVAR_ash_pGAS[535]
{0x0F12, 0x0061 }, //#TVAR_ash_pGAS[536]
{0x0F12, 0x0045 }, //#TVAR_ash_pGAS[537]
{0x0F12, 0x0035 }, //#TVAR_ash_pGAS[538]
{0x0F12, 0x002B }, //#TVAR_ash_pGAS[539]
{0x0F12, 0x0030 }, //#TVAR_ash_pGAS[540]
{0x0F12, 0x003F }, //#TVAR_ash_pGAS[541]
{0x0F12, 0x005A }, //#TVAR_ash_pGAS[542]
{0x0F12, 0x007D }, //#TVAR_ash_pGAS[543]
{0x0F12, 0x00AB }, //#TVAR_ash_pGAS[544]
{0x0F12, 0x00E4 }, //#TVAR_ash_pGAS[545]
{0x0F12, 0x0116 }, //#TVAR_ash_pGAS[546]
{0x0F12, 0x00EB }, //#TVAR_ash_pGAS[547]
{0x0F12, 0x00B4 }, //#TVAR_ash_pGAS[548]
{0x0F12, 0x008C }, //#TVAR_ash_pGAS[549]
{0x0F12, 0x0071 }, //#TVAR_ash_pGAS[550]
{0x0F12, 0x0060 }, //#TVAR_ash_pGAS[551]
{0x0F12, 0x005A }, //#TVAR_ash_pGAS[552]
{0x0F12, 0x005B }, //#TVAR_ash_pGAS[553]
{0x0F12, 0x0068 }, //#TVAR_ash_pGAS[554]
{0x0F12, 0x0081 }, //#TVAR_ash_pGAS[555]
{0x0F12, 0x00A4 }, //#TVAR_ash_pGAS[556]
{0x0F12, 0x00D5 }, //#TVAR_ash_pGAS[557]
{0x0F12, 0x00FA }, //#TVAR_ash_pGAS[558]
{0x0F12, 0x0138 }, //#TVAR_ash_pGAS[559]
{0x0F12, 0x0113 }, //#TVAR_ash_pGAS[560]
{0x0F12, 0x00DF }, //#TVAR_ash_pGAS[561]
{0x0F12, 0x00B9 }, //#TVAR_ash_pGAS[562]
{0x0F12, 0x009F }, //#TVAR_ash_pGAS[563]
{0x0F12, 0x008C }, //#TVAR_ash_pGAS[564]
{0x0F12, 0x0084 }, //#TVAR_ash_pGAS[565]
{0x0F12, 0x0086 }, //#TVAR_ash_pGAS[566]
{0x0F12, 0x0090 }, //#TVAR_ash_pGAS[567]
{0x0F12, 0x00A9 }, //#TVAR_ash_pGAS[568]
{0x0F12, 0x00CE }, //#TVAR_ash_pGAS[569]
{0x0F12, 0x00FA }, //#TVAR_ash_pGAS[570]
{0x0F12, 0x0107 }, //#TVAR_ash_pGAS[571]
              
// param_start TVAR_ash_AwbAshCord
{0x002A, 0x06B8 },
{0x0F12, 0x00C7 }, //00C0//00D0 // #TVAR_ash_AwbAshCord_0_
{0x0F12, 0x00d9 }, //00E0//0102 // #TVAR_ash_AwbAshCord_1_
{0x0F12, 0x0110 }, //00F0//010E // #TVAR_ash_AwbAshCord_2_
{0x0F12, 0x0129 }, //0129//0137 // #TVAR_ash_AwbAshCord_3_
{0x0F12, 0x0159 }, //0156//0171 // #TVAR_ash_AwbAshCord_4_
{0x0F12, 0x0179 }, //017F//0198 // #TVAR_ash_AwbAshCord_5_
{0x0F12, 0x018c }, //018F//01A8 // #TVAR_ash_AwbAshCord_6_
              
//================================================================================================
// SET CCM    
//================================================================================================
{0x002A, 0x06A6 },
{0x0F12, 0x00DE }, //00C0//00D8 // #SARR_AwbCcmCord_0_
{0x0F12, 0x00FE }, //00E0//00FC // #SARR_AwbCcmCord_1_
{0x0F12, 0x0107 }, //00F0//0120 // #SARR_AwbCcmCord_2_
{0x0F12, 0x0138 }, //0129//014C // #SARR_AwbCcmCord_3_
{0x0F12, 0x016B }, //0156//0184 // #SARR_AwbCcmCord_4_
{0x0F12, 0x0198 }, //017F//01AD // #SARR_AwbCcmCord_5_
              
// CCM start address // 7000_33A4
{0x002A, 0x0698 }, // SET CCM  
{0x0F12, 0x33A4 },
{0x0F12, 0x7000 },
{0x002A, 0x33A4 }, // Horizon
{0x0F12, 0x0172 }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFF64 }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFFA0 }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFF4D }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x01FA }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFEF4 }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFFD9 }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0025 }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x026F }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0299 }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x012F }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFE21 }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0143 }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFF4E }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0183 }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0xFEBA }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0191 }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x013D }, //#TVAR_wbt_pBaseCcms                            
{0x0F12, 0x0172 }, //#TVAR_wbt_pBaseCcms[18] // Inca                
{0x0F12, 0xFF64 }, //#TVAR_wbt_pBaseCcms[19]                        
{0x0F12, 0xFFA0 }, //#TVAR_wbt_pBaseCcms[20]                        
{0x0F12, 0xFF4D }, //#TVAR_wbt_pBaseCcms[21]                        
{0x0F12, 0x01FA }, //#TVAR_wbt_pBaseCcms[22]                        
{0x0F12, 0xFEF4 }, //#TVAR_wbt_pBaseCcms[23]                        
{0x0F12, 0xFFD9 }, //#TVAR_wbt_pBaseCcms[24]                        
{0x0F12, 0x0025 }, //#TVAR_wbt_pBaseCcms[25]                        
{0x0F12, 0x026F }, //#TVAR_wbt_pBaseCcms[26]                        
{0x0F12, 0x0299 }, //#TVAR_wbt_pBaseCcms[27]                        
{0x0F12, 0x012F }, //#TVAR_wbt_pBaseCcms[28]                        
{0x0F12, 0xFE21 }, //#TVAR_wbt_pBaseCcms[29]                        
{0x0F12, 0x0143 }, //#TVAR_wbt_pBaseCcms[30]                        
{0x0F12, 0xFF4E }, //#TVAR_wbt_pBaseCcms[31]                        
{0x0F12, 0x0183 }, //#TVAR_wbt_pBaseCcms[32]                        
{0x0F12, 0xFEBA }, //#TVAR_wbt_pBaseCcms[33]                        
{0x0F12, 0x0191 }, //#TVAR_wbt_pBaseCcms[34]                        
{0x0F12, 0x013D }, //#TVAR_wbt_pBaseCcms[35]                        
{0x0F12, 0x01C8 }, //#TVAR_wbt_pBaseCcms[36] // WW                  
{0x0F12, 0xFF57 }, //#TVAR_wbt_pBaseCcms[37]                        
{0x0F12, 0xFFC3 }, //#TVAR_wbt_pBaseCcms[38]                        
{0x0F12, 0xFF67 }, //#TVAR_wbt_pBaseCcms[39]                        
{0x0F12, 0x01AD }, //#TVAR_wbt_pBaseCcms[40]                        
{0x0F12, 0xFF39 }, //#TVAR_wbt_pBaseCcms[41]                        
{0x0F12, 0xFFE6 }, //#TVAR_wbt_pBaseCcms[42]                        
{0x0F12, 0xFFF0 }, //#TVAR_wbt_pBaseCcms[43]                        
{0x0F12, 0x01B0 }, //#TVAR_wbt_pBaseCcms[44]                        
{0x0F12, 0x00EF }, //#TVAR_wbt_pBaseCcms[45]                        
{0x0F12, 0x00EE }, //#TVAR_wbt_pBaseCcms[46]                        
{0x0F12, 0xFF1D }, //#TVAR_wbt_pBaseCcms[47]                        
{0x0F12, 0x01A4 }, //#TVAR_wbt_pBaseCcms[48]                        
{0x0F12, 0xFF70 }, //#TVAR_wbt_pBaseCcms[49]                        
{0x0F12, 0x01D0 }, //#TVAR_wbt_pBaseCcms[50]                        
{0x0F12, 0xFF3B }, //#TVAR_wbt_pBaseCcms[51]                        
{0x0F12, 0x016F }, //#TVAR_wbt_pBaseCcms[52]                        
{0x0F12, 0x012C }, //#TVAR_wbt_pBaseCcms[53]                        
{0x0F12, 0x01C8 }, //#TVAR_wbt_pBaseCcms[54] // CWF                 
{0x0F12, 0xFF57 }, //#TVAR_wbt_pBaseCcms[55]                        
{0x0F12, 0xFFC3 }, //#TVAR_wbt_pBaseCcms[56]                        
{0x0F12, 0xFF67 }, //#TVAR_wbt_pBaseCcms[57]                        
{0x0F12, 0x01AD }, //#TVAR_wbt_pBaseCcms[58]                        
{0x0F12, 0xFF39 }, //#TVAR_wbt_pBaseCcms[59]                        
{0x0F12, 0xFFE6 }, //#TVAR_wbt_pBaseCcms[60]                        
{0x0F12, 0xFFF0 }, //#TVAR_wbt_pBaseCcms[61]                        
{0x0F12, 0x01B0 }, //#TVAR_wbt_pBaseCcms[62]                        
{0x0F12, 0x00EF }, //#TVAR_wbt_pBaseCcms[63]                        
{0x0F12, 0x00EE }, //#TVAR_wbt_pBaseCcms[64]                        
{0x0F12, 0xFF1D }, //#TVAR_wbt_pBaseCcms[65]                        
{0x0F12, 0x01A4 }, //#TVAR_wbt_pBaseCcms[66]                        
{0x0F12, 0xFF70 }, //#TVAR_wbt_pBaseCcms[67]                        
{0x0F12, 0x01D0 }, //#TVAR_wbt_pBaseCcms[68]                        
{0x0F12, 0xFF3B }, //#TVAR_wbt_pBaseCcms[69]                        
{0x0F12, 0x016F }, //#TVAR_wbt_pBaseCcms[70]                        
{0x0F12, 0x012C }, //#TVAR_wbt_pBaseCcms[71]                        
{0x0F12, 0x0184 }, //#TVAR_wbt_pBaseCcms[72] // D50                 
{0x0F12, 0xFFA0 }, //#TVAR_wbt_pBaseCcms[73]                        
{0x0F12, 0xFFF4 }, //#TVAR_wbt_pBaseCcms[74]                        
{0x0F12, 0xFF71 }, //#TVAR_wbt_pBaseCcms[75]                        
{0x0F12, 0x019E }, //#TVAR_wbt_pBaseCcms[76]                        
{0x0F12, 0xFF45 }, //#TVAR_wbt_pBaseCcms[77]                        
{0x0F12, 0xFFFE }, //#TVAR_wbt_pBaseCcms[78]                        
{0x0F12, 0x0006 }, //#TVAR_wbt_pBaseCcms[79]                        

{0x0F12, 0x018A }, //#TVAR_wbt_pBaseCcms[80]                        
{0x0F12, 0x0110 }, //#TVAR_wbt_pBaseCcms[81]                        
{0x0F12, 0x010F }, //#TVAR_wbt_pBaseCcms[82]                        
{0x0F12, 0xFF52 }, //#TVAR_wbt_pBaseCcms[83]                        
{0x0F12, 0x01D7 }, //#TVAR_wbt_pBaseCcms[84]                        
{0x0F12, 0xFF9D }, //#TVAR_wbt_pBaseCcms[85]                        
{0x0F12, 0x0203 }, //#TVAR_wbt_pBaseCcms[86]                        
{0x0F12, 0xFF55 }, //#TVAR_wbt_pBaseCcms[87]                        
{0x0F12, 0x0163 }, //#TVAR_wbt_pBaseCcms[88]                        
{0x0F12, 0x0126 }, //#TVAR_wbt_pBaseCcms[89]                        
{0x0F12, 0x0199 }, //#TVAR_wbt_pBaseCcms[90] // D65                 
{0x0F12, 0xFFA5 }, //#TVAR_wbt_pBaseCcms[91]                        
{0x0F12, 0xFFFC }, //#TVAR_wbt_pBaseCcms[92]                        
{0x0F12, 0xFF6F }, //#TVAR_wbt_pBaseCcms[93]                        
{0x0F12, 0x019F }, //#TVAR_wbt_pBaseCcms[94]                        
{0x0F12, 0xFF43 }, //#TVAR_wbt_pBaseCcms[95]                        
{0x0F12, 0xFFFB }, //#TVAR_wbt_pBaseCcms[96]                        
{0x0F12, 0x0003 }, //#TVAR_wbt_pBaseCcms[97]                        
{0x0F12, 0x018E }, //#TVAR_wbt_pBaseCcms[98]                        
{0x0F12, 0x010C }, //#TVAR_wbt_pBaseCcms[99]                        
{0x0F12, 0x010B }, //#TVAR_wbt_pBaseCcms[100]                       
{0x0F12, 0xFF4B }, //#TVAR_wbt_pBaseCcms[101]                       
{0x0F12, 0x01F6 }, //#TVAR_wbt_pBaseCcms[102]                       
{0x0F12, 0xFFBC }, //#TVAR_wbt_pBaseCcms[103]                       
{0x0F12, 0x0222 }, //#TVAR_wbt_pBaseCcms[104]                       
{0x0F12, 0xFF4F }, //#TVAR_wbt_pBaseCcms[105]                       
{0x0F12, 0x0162 }, //#TVAR_wbt_pBaseCcms[106]                       
{0x0F12, 0x0124 }, //#TVAR_wbt_pBaseCcms[107]                       
{0x002A, 0x06A0 }, // Outdoor CCM address // 7000_3380              
{0x0F12, 0x3380 },
{0x0F12, 0x7000 },
{0x002A, 0x3380 },
{0x0F12, 0x01E0 }, //#TVAR_wbt_pOutdoorCcm[0]// Outdoor CCM     
{0x0F12, 0xFF80 }, //#TVAR_wbt_pOutdoorCcm[1]                   
{0x0F12, 0xFFD0 }, //#TVAR_wbt_pOutdoorCcm[2]                   
{0x0F12, 0xFF61 }, //#TVAR_wbt_pOutdoorCcm[3]                   
{0x0F12, 0x01BD }, //#TVAR_wbt_pOutdoorCcm[4]                   
{0x0F12, 0xFF34 }, //#TVAR_wbt_pOutdoorCcm[5]                   
{0x0F12, 0xFFFE }, //#TVAR_wbt_pOutdoorCcm[6]                   
{0x0F12, 0xFFF6 }, //#TVAR_wbt_pOutdoorCcm[7]                   
{0x0F12, 0x019D }, //#TVAR_wbt_pOutdoorCcm[8]                   
{0x0F12, 0x0107 }, //#TVAR_wbt_pOutdoorCcm[9]                   
{0x0F12, 0x010F }, //#TVAR_wbt_pOutdoorCcm[10]                  
{0x0F12, 0xFF67 }, //#TVAR_wbt_pOutdoorCcm[11]                  
{0x0F12, 0x016C }, //#TVAR_wbt_pOutdoorCcm[12]                  
{0x0F12, 0xFF54 }, //#TVAR_wbt_pOutdoorCcm[13]                  
{0x0F12, 0x01FC }, //#TVAR_wbt_pOutdoorCcm[14]                  
{0x0F12, 0xFF82 }, //#TVAR_wbt_pOutdoorCcm[15]                  
{0x0F12, 0x015D }, //#TVAR_wbt_pOutdoorCcm[16]                  
{0x0F12, 0x00FD }, //#TVAR_wbt_pOutdoorCcm[17]
//===============================================================================================
// SET AWB   
//===============================================================================================
// Indoor boundary
//           
{0x002A, 0x0C48 }, // set awb                                                                                    
{0x0F12, 0x03B6 }, //03B6 //03C8 // #awbb_IndoorGrZones_m_BGrid[0] // Indoor boundary                                 
{0x0F12, 0x03E2 }, //03E2 //03E2 // #awbb_IndoorGrZones_m_BGrid[1]                                                    
{0x0F12, 0x0352 }, //0352 //038A // #awbb_IndoorGrZones_m_BGrid[2]                                                    
{0x0F12, 0x03F4 }, //03F4 //03F4 // #awbb_IndoorGrZones_m_BGrid[3]                                                    
{0x0F12, 0x0300 }, //0300 //034E // #awbb_IndoorGrZones_m_BGrid[4]                                                    
{0x0F12, 0x03E2 }, //03E2 //03E2 // #awbb_IndoorGrZones_m_BGrid[5]                                                    
{0x0F12, 0x02CC }, //02CA //030A // #awbb_IndoorGrZones_m_BGrid[6]                                                    
{0x0F12, 0x03B6 }, //03B6 //03B8 // #awbb_IndoorGrZones_m_BGrid[7]                                                    
{0x0F12, 0x0298 }, //0298 //02C8 // #awbb_IndoorGrZones_m_BGrid[8]                                                    
{0x0F12, 0x038A }, //038A //038A // #awbb_IndoorGrZones_m_BGrid[9]                                                    
{0x0F12, 0x027A }, //027A //029C // #awbb_IndoorGrZones_m_BGrid[10]                                                   
{0x0F12, 0x0356 }, //0356 //0356 // #awbb_IndoorGrZones_m_BGrid[11]                                                   
{0x0F12, 0x025E }, //025E //0286 // #awbb_IndoorGrZones_m_BGrid[12]                                                   
{0x0F12, 0x0322 }, //0322 //0322 // #awbb_IndoorGrZones_m_BGrid[13]                                                   
{0x0F12, 0x023C }, //024C //026C // #awbb_IndoorGrZones_m_BGrid[14]                                                   
{0x0F12, 0x02F6 }, //02F6 //02F6 // #awbb_IndoorGrZones_m_BGrid[15]                                                   
{0x0F12, 0x021C }, //0232 //0254 // #awbb_IndoorGrZones_m_BGrid[16]                                                   
{0x0F12, 0x02CA }, //02CA //02CA // #awbb_IndoorGrZones_m_BGrid[17]                                                   
{0x0F12, 0x01FE }, //0210 //023E // #awbb_IndoorGrZones_m_BGrid[18]                                                   
{0x0F12, 0x02B8 }, //02B8 //02B8 // #awbb_IndoorGrZones_m_BGrid[19]                                                   
{0x0F12, 0x01EE }, //01F6 //022E // #awbb_IndoorGrZones_m_BGrid[20]                                                   
{0x0F12, 0x02A6 }, //02A6 //02A4 // #awbb_IndoorGrZones_m_BGrid[21]                                                   
{0x0F12, 0x01E4 }, //01E4 //0226 // #awbb_IndoorGrZones_m_BGrid[22]                                                   
{0x0F12, 0x0294 }, //0294 //0294 // #awbb_IndoorGrZones_m_BGrid[23]                                                   
{0x0F12, 0x01E0 }, //01E6 //0220 // #awbb_IndoorGrZones_m_BGrid[24]                                                   
{0x0F12, 0x027E }, //027E //027E // #awbb_IndoorGrZones_m_BGrid[25]                                                   
{0x0F12, 0x01E4 }, //01EE //022A // #awbb_IndoorGrZones_m_BGrid[26]                                                   
{0x0F12, 0x0264 }, //025A //025E // #awbb_IndoorGrZones_m_BGrid[27]                                                   
{0x0F12, 0x01EA }, //01FC //0000 // #awbb_IndoorGrZones_m_BGrid[28]                                                   
{0x0F12, 0x024A }, //0238 //0000 // #awbb_IndoorGrZones_m_BGrid[29]                                                   
{0x0F12, 0x01F6 }, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[30]                                                   
{0x0F12, 0x0230 }, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[31]                                                   
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[32]                                                   
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[33]                                                   
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[34]                                                   
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[35]                                                   
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[36]                                                   
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[37]                                                   
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[38]                                                   
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_IndoorGrZones_m_BGrid[39]                                                   
{0x0F12, 0x0005 }, // #awbb_IndoorGrZones_m_GridStep                                                    
{0x002A, 0x0C9C },                                                                                      
{0x0F12, 0x0010 }, // #awbb_IndoorGrZones_ZInfo_m_GridSz                                                     
{0x002A, 0x0CA0 },                                                                                      
{0x0F12, 0x00FE }, // #awbb_IndoorGrZones_m_Boffs[0]                
{0x002A, 0x0CA4 },                 
{0x0F12, 0x0218 }, //0290 //027E // #awbb_OutdoorGrZones_m_BGrid[0] // Outdoor boundary                               
{0x0F12, 0x0294 }, //02C0 //02AE // #awbb_OutdoorGrZones_m_BGrid[1]                                                   
{0x0F12, 0x0200 }, //026A //025C // #awbb_OutdoorGrZones_m_BGrid[2]                                                   
{0x0F12, 0x0290 }, //02B4 //02B2 // #awbb_OutdoorGrZones_m_BGrid[3]                                                   
{0x0F12, 0x01F4 }, //0246 //0244 // #awbb_OutdoorGrZones_m_BGrid[4]                                                   
{0x0F12, 0x027A }, //02A8 //02A0 // #awbb_OutdoorGrZones_m_BGrid[5]                                                   
{0x0F12, 0x0204 }, //022A //0236 // #awbb_OutdoorGrZones_m_BGrid[6]                                                   
{0x0F12, 0x022C }, //02A0 //0290 // #awbb_OutdoorGrZones_m_BGrid[7]                                                   
{0x0F12, 0x0000 }, //0214 //0230 // #awbb_OutdoorGrZones_m_BGrid[8]                                                   
{0x0F12, 0x0000 }, //0290 //027A // #awbb_OutdoorGrZones_m_BGrid[9]                                                   
{0x0F12, 0x0000 }, //020C //0236 // #awbb_OutdoorGrZones_m_BGrid[10]                                                  
{0x0F12, 0x0000 }, //027A //025E // #awbb_OutdoorGrZones_m_BGrid[11]                                                  
{0x0F12, 0x0000 }, //0218 //0000 // #awbb_OutdoorGrZones_m_BGrid[12]                                                  
{0x0F12, 0x0000 }, //025E //0000 // #awbb_OutdoorGrZones_m_BGrid[13]                                                  
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[14]                                                  
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[15]                                                  
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[16]                                                  
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[17]                                                  
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[18]                                                  
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[19]                                                  
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[20]                                                  
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[21]                                                  
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[22]                                  
{0x0F12, 0x0000 }, //0000 //0000 // #awbb_OutdoorGrZones_m_BGrid[23]                                  
{0x0F12, 0x0005 }, // #awbb_OutdoorGrZones_m_GridStep                                                         
{0x002A, 0x0CD8 },                                                                                            
{0x0F12, 0x0006 }, // #awbb_OutdoorGrZones_ZInfo_m_GridSz
{0x002A, 0x0CDC }, 
{0x0F12, 0x022E }, // #awbb_OutdoorGrZones_m_Boffs                                                            
{0x002A, 0x0D88 },                                                                                            
{0x0F12, 0x0054 }, // #awbb_OutdoorDetectionZone_m_BGrid[0]_m_left // Outdoor detection zone                  
{0x0F12, 0x00CD }, // #awbb_OutdoorDetectionZone_m_BGrid[0]_m_right                                           
{0x0F12, 0xFFCB }, // #awbb_OutdoorDetectionZone_m_BGrid[1]_m_left                                            
{0x0F12, 0x00ED }, // #awbb_OutdoorDetectionZone_m_BGrid[1]_m_right                                           
{0x0F12, 0xFF75 }, // #awbb_OutdoorDetectionZone_m_BGrid[2]_m_left                                            
{0x0F12, 0x0118 }, // #awbb_OutdoorDetectionZone_m_BGrid[2]_m_right                                           
{0x0F12, 0xFF30 }, // #awbb_OutdoorDetectionZone_m_BGrid[3]_m_left                                            
{0x0F12, 0x0134 }, // #awbb_OutdoorDetectionZone_m_BGrid[3]_m_right                                           
{0x0F12, 0xFED9 }, // #awbb_OutdoorDetectionZone_m_BGrid[4]_m_left                                            
{0x0F12, 0x0176 }, // #awbb_OutdoorDetectionZone_m_BGrid[4]_m_right                                           
{0x0F12, 0x0E74 }, // #awbb_OutdoorDetectionZone_ZInfo_m_AbsGridStep                                          
{0x0F12, 0x0000 },                                                                                            
{0x0F12, 0x0005 }, // #awbb_OutdoorDetectionZone_ZInfo_m_GridSz                                               
{0x0F12, 0x0000 },                                                                                            
{0x0F12, 0x008A }, // #awbb_OutdoorDetectionZone_ZInfo_m_NBoffs                                               
{0x0F12, 0x0000 },                                                                                           
{0x0F12, 0x4E20 }, // #awbb_OutdoorDetectionZone_ZInfo_m_MaxNB                                               
{0x0F12, 0x0000 },
{0x002A, 0x0CE0 }, 
{0x0F12, 0x03EA }, // #awbb_LowBrGrZones_m_BGrid[0] // LowBr boundary   
{0x0F12, 0x044E }, // #awbb_LowBrGrZones_m_BGrid[1]                     
{0x0F12, 0x035E }, // #awbb_LowBrGrZones_m_BGrid[2]                     
{0x0F12, 0x044C }, // #awbb_LowBrGrZones_m_BGrid[3]                     
{0x0F12, 0x02FA }, // #awbb_LowBrGrZones_m_BGrid[4]                     
{0x0F12, 0x0434 }, // #awbb_LowBrGrZones_m_BGrid[5]                     
{0x0F12, 0x0296 }, // #awbb_LowBrGrZones_m_BGrid[6]                     
{0x0F12, 0x03F2 }, // #awbb_LowBrGrZones_m_BGrid[7]                     
{0x0F12, 0x0250 }, // #awbb_LowBrGrZones_m_BGrid[8]                     
{0x0F12, 0x03AE }, // #awbb_LowBrGrZones_m_BGrid[9]                     
{0x0F12, 0x0216 }, // #awbb_LowBrGrZones_m_BGrid[10]                    
{0x0F12, 0x0364 }, // #awbb_LowBrGrZones_m_BGrid[11]                    
{0x0F12, 0x01DE }, // #awbb_LowBrGrZones_m_BGrid[12]                    
{0x0F12, 0x031C }, // #awbb_LowBrGrZones_m_BGrid[13]                    
{0x0F12, 0x01BE }, // #awbb_LowBrGrZones_m_BGrid[14]                    
{0x0F12, 0x02D4 }, // #awbb_LowBrGrZones_m_BGrid[15]                    
{0x0F12, 0x019C }, // #awbb_LowBrGrZones_m_BGrid[16]                    
{0x0F12, 0x029A }, // #awbb_LowBrGrZones_m_BGrid[17]                    
{0x0F12, 0x0184 }, // #awbb_LowBrGrZones_m_BGrid[18]                    
{0x0F12, 0x0262 }, // #awbb_LowBrGrZones_m_BGrid[19]                    
{0x0F12, 0x0190 }, // #awbb_LowBrGrZones_m_BGrid[20]                    
{0x0F12, 0x0216 }, // #awbb_LowBrGrZones_m_BGrid[21]                    
{0x0F12, 0x0000 }, // #awbb_LowBrGrZones_m_BGrid[22]                    
{0x0F12, 0x0000 }, // #awbb_LowBrGrZones_m_BGrid[23]                    
{0x0F12, 0x0006 }, // #awbb_LowBrGrZones_m_GridStep                     
{0x002A, 0x0D14 },                                                      
{0x0F12, 0x000B }, // #awbb_LowBrGrZones_ZInfo_m_GridSz                    
{0x002A, 0x0D18 },
{0x0F12, 0x009A }, // #awbb_LowBrGrZones_m_Boffs    
{0x002A, 0x0D1C },
{0x0F12, 0x036C }, // #awbb_CrclLowT_R_c                                                       
{0x002A, 0x0D20 },                                                                             
{0x0F12, 0x011C }, // #awbb_CrclLowT_B_c                                                       
{0x002A, 0x0D24 },                                                                             
{0x0F12, 0x6184 }, // #awbb_CrclLowT_Rad_c                                                     
{0x002A, 0x0D2C },                                                                             
{0x0F12, 0x0135 }, // #awbb_IntcR                                                              
{0x0F12, 0x012B }, // #awbb_IntcB                                                              
{0x002A, 0x0D28 },                                                                             
{0x0F12, 0x024E }, // #awbb_OutdoorWP_r                                                        
{0x0F12, 0x027B }, // #awbb_OutdoorWP_b                                                        
{0x002A, 0x0E4C },                                                                             
{0x0F12, 0x0000 }, // #awbboost_useBoosting4Outdoor                                            
{0x002A, 0x0D4C },                                                                             
{0x0F12, 0x0653 }, // #awbb_GamutWidthThr1                                                     
{0x0F12, 0x02EB }, // #awbb_GamutHeightThr1                                                    
{0x0F12, 0x002C }, // #awbb_GamutWidthThr2                                                     
{0x0F12, 0x000B }, // #awbb_GamutHeightThr2                                                    
{0x002A, 0x0D5C },                                                                             
{0x0F12, 0x7FFF }, // #awbb_LowTempRB                                                          
{0x0F12, 0x0050 }, // #awbb_LowTemp_RBzone                                                     
{0x002A, 0x0D46 },                                                                             
{0x0F12, 0x053A }, //035E // #awbb_MvEq_RBthresh                                              
{0x002A, 0x0D4A },                                                                             
{0x0F12, 0x000A }, // #awbb_MovingScale10                                                      
{0x002A, 0x0DD4 },                                                                             
{0x0F12, 0xFFFE }, // #awbb_GridCorr_R_0__0_ 
{0x0F12, 0xFFFE }, // #awbb_GridCorr_R_0__1_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_0__2_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_0__3_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_0__4_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_0__5_ 
{0x0F12, 0xFFFD }, // #awbb_GridCorr_R_1__0_ 
{0x0F12, 0xFFFD }, // #awbb_GridCorr_R_1__1_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_1__2_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_1__3_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_1__4_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_1__5_ 
{0x0F12, 0xFFFC }, // #awbb_GridCorr_R_2__0_ 
{0x0F12, 0xFFFC }, // #awbb_GridCorr_R_2__1_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_2__2_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_2__3_                                                                              
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_2__4_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_R_2__5_ 
{0x0F12, 0x000C }, // #awbb_GridCorr_B_0__0_ 
{0x0F12, 0x0006 }, // #awbb_GridCorr_B_0__1_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_0__2_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_0__3_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_0__4_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_0__5_ 
{0x0F12, 0x000C }, // #awbb_GridCorr_B_1__0_ 
{0x0F12, 0x0006 }, // #awbb_GridCorr_B_1__1_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_1__2_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_1__3_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_1__4_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_1__5_ 
{0x0F12, 0x000C }, // #awbb_GridCorr_B_2__0_ 
{0x0F12, 0x0006 }, // #awbb_GridCorr_B_2__1_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_2__2_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_2__3_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_2__4_ 
{0x0F12, 0x0000 }, // #awbb_GridCorr_B_2__5_ 
{0x0F12, 0x02F0 }, // #awbb_GridConst_1_0_ 
{0x0F12, 0x0358 }, // #awbb_GridConst_1_1_ 
{0x0F12, 0x03A5 }, // #awbb_GridConst_1_2_ 
{0x0F12, 0x0F9C }, // #awbb_GridConst_2_0_
{0x0F12, 0x0FFA }, // #awbb_GridConst_2_1_
{0x0F12, 0x10B5 }, // #awbb_GridConst_2_2_
{0x0F12, 0x1126 }, // #awbb_GridConst_2_3_
{0x0F12, 0x1176 }, // #awbb_GridConst_2_4_
{0x0F12, 0x1220 }, // #awbb_GridConst_2_5_
{0x0F12, 0x00B2 }, // #awbb_GridCoeff_R_1
{0x0F12, 0x00B8 }, // #awbb_GridCoeff_B_1
{0x0F12, 0x00B7 }, // #awbb_GridCoeff_R_2
{0x0F12, 0x00B3 }, // #awbb_GridCoeff_B_2
{0x002A, 0x0E3E },
{0x0F12, 0x0000 }, // #awbb_rpl_InvalidOutdoor off                                             
{0x002A, 0x22DE },                                                                             
{0x0F12, 0x0004 }, // #Mon_AWB_ByPassMode // [0]Outdoor [1]LowBr [2]LowTemp                    
{0x002A, 0x337C },                                                                             
{0x0F12, 0x00B3 }, // #Tune_TP_ChMoveToNearR                                                   
{0x0F12, 0x0040 }, // #Tune_TP_AvMoveToGamutDist                                               
{0x002A, 0x0E44 }, // AWB initial point                                                        
{0x0F12, 0x053C }, // #define awbb_GainsInit_0_                                               
{0x0F12, 0x0400 }, // #define awbb_GainsInit_1_                                                
{0x0F12, 0x055C }, // #define awbb_GainsInit_2_                                                
{0x002A, 0x0E36 }, // Set AWB global offset                                                    
{0x0F12, 0x0000 }, // #awbb_RGainOff                                                            
{0x0F12, 0x0000 }, // #awbb_BGainOff                                                            
{0x0F12, 0x0000 }, // #awbb_GGainOff                                                            
{0x002A, 0x0E4A },                                                                             
{0x0F12, 0x0002 },
//===============================================================================================
// SET GAMMA 
//===============================================================================================
{0x002A, 0x3288 },
{0x0F12, 0x0000 }, // #SARR_usDualGammaLutRGBIndoor_0__0_ 70003288// Indoor gamma                
{0x0F12, 0x0046 }, // #SARR_usDualGammaLutRGBIndoor_0__1_ 7000328A                               
{0x0F12, 0x0064 }, // #SARR_usDualGammaLutRGBIndoor_0__2_ 7000328C                               
{0x0F12, 0x008A }, // #SARR_usDualGammaLutRGBIndoor_0__3_ 7000328E                               
{0x0F12, 0x00BE }, // #SARR_usDualGammaLutRGBIndoor_0__4_ 70003290                               
{0x0F12, 0x0118 }, // #SARR_usDualGammaLutRGBIndoor_0__5_ 70003292                               
{0x0F12, 0x015E }, // #SARR_usDualGammaLutRGBIndoor_0__6_ 70003294                               
{0x0F12, 0x017C }, // #SARR_usDualGammaLutRGBIndoor_0__7_ 70003296                               
{0x0F12, 0x0194 }, // #SARR_usDualGammaLutRGBIndoor_0__8_ 70003298                               
{0x0F12, 0x01C0 }, // #SARR_usDualGammaLutRGBIndoor_0__9_ 7000329A                               
{0x0F12, 0x01E7 }, // #SARR_usDualGammaLutRGBIndoor_0__10_ 7000329C                              
{0x0F12, 0x020E }, // #SARR_usDualGammaLutRGBIndoor_0__11_ 7000329E                              
{0x0F12, 0x0232 }, // #SARR_usDualGammaLutRGBIndoor_0__12_ 700032A0                              
{0x0F12, 0x0273 }, // #SARR_usDualGammaLutRGBIndoor_0__13_ 700032A2                              
{0x0F12, 0x02AF }, // #SARR_usDualGammaLutRGBIndoor_0__14_ 700032A4                              
{0x0F12, 0x0309 }, // #SARR_usDualGammaLutRGBIndoor_0__15_ 700032A6                              
{0x0F12, 0x0355 }, // #SARR_usDualGammaLutRGBIndoor_0__16_ 700032A8                              
{0x0F12, 0x0394 }, // #SARR_usDualGammaLutRGBIndoor_0__17_ 700032AA                              
{0x0F12, 0x03CE }, // #SARR_usDualGammaLutRGBIndoor_0__18_ 700032AC                              
{0x0F12, 0x03FF }, // #SARR_usDualGammaLutRGBIndoor_0__19_ 700032AE                              
{0x0F12, 0x0000 }, // #SARR_usDualGammaLutRGBIndoor_1__0_ 700032B0                               
{0x0F12, 0x0046 }, // #SARR_usDualGammaLutRGBIndoor_1__1_ 700032B2                               
{0x0F12, 0x0064 }, // #SARR_usDualGammaLutRGBIndoor_1__2_ 700032B4                               
{0x0F12, 0x008A }, // #SARR_usDualGammaLutRGBIndoor_1__3_ 700032B6                               
{0x0F12, 0x00BE }, // #SARR_usDualGammaLutRGBIndoor_1__4_ 700032B8                               
{0x0F12, 0x0118 }, // #SARR_usDualGammaLutRGBIndoor_1__5_ 700032BA                               
{0x0F12, 0x015E }, // #SARR_usDualGammaLutRGBIndoor_1__6_ 700032BC                               
{0x0F12, 0x017C }, // #SARR_usDualGammaLutRGBIndoor_1__7_ 700032BE                               
{0x0F12, 0x0194 }, // #SARR_usDualGammaLutRGBIndoor_1__8_ 700032C0                               
{0x0F12, 0x01C0 }, // #SARR_usDualGammaLutRGBIndoor_1__9_ 700032C2                               
{0x0F12, 0x01E7 }, // #SARR_usDualGammaLutRGBIndoor_1__10_ 700032C4                              
{0x0F12, 0x020E }, // #SARR_usDualGammaLutRGBIndoor_1__11_ 700032C6                              
{0x0F12, 0x0232 }, // #SARR_usDualGammaLutRGBIndoor_1__12_ 700032C8                              
{0x0F12, 0x0273 }, // #SARR_usDualGammaLutRGBIndoor_1__13_ 700032CA                              
{0x0F12, 0x02AF }, // #SARR_usDualGammaLutRGBIndoor_1__14_ 700032CC                              
{0x0F12, 0x0309 }, // #SARR_usDualGammaLutRGBIndoor_1__15_ 700032CE                              
{0x0F12, 0x0355 }, // #SARR_usDualGammaLutRGBIndoor_1__16_ 700032D0                              
{0x0F12, 0x0394 }, // #SARR_usDualGammaLutRGBIndoor_1__17_ 700032D2                              
{0x0F12, 0x03CE }, // #SARR_usDualGammaLutRGBIndoor_1__18_ 700032D4                              
{0x0F12, 0x03FF }, // #SARR_usDualGammaLutRGBIndoor_1__19_ 700032D6                              
{0x0F12, 0x0000 }, // #SARR_usDualGammaLutRGBIndoor_2__0_ 700032D8                               
{0x0F12, 0x0046 }, // #SARR_usDualGammaLutRGBIndoor_2__1_ 700032DA                               
{0x0F12, 0x0064 }, // #SARR_usDualGammaLutRGBIndoor_2__2_ 700032DC                               
{0x0F12, 0x008A }, // #SARR_usDualGammaLutRGBIndoor_2__3_ 700032DE                               
{0x0F12, 0x00BE }, // #SARR_usDualGammaLutRGBIndoor_2__4_ 700032E0                               
{0x0F12, 0x0118 }, // #SARR_usDualGammaLutRGBIndoor_2__5_ 700032E2                               
{0x0F12, 0x015E }, // #SARR_usDualGammaLutRGBIndoor_2__6_ 700032E4                               
{0x0F12, 0x017C }, // #SARR_usDualGammaLutRGBIndoor_2__7_ 700032E6                               
{0x0F12, 0x0194 }, // #SARR_usDualGammaLutRGBIndoor_2__8_ 700032E8                               
{0x0F12, 0x01C0 }, // #SARR_usDualGammaLutRGBIndoor_2__9_ 700032EA                               
{0x0F12, 0x01E7 }, // #SARR_usDualGammaLutRGBIndoor_2__10_ 700032EC                              
{0x0F12, 0x020E }, // #SARR_usDualGammaLutRGBIndoor_2__11_ 700032EE                              
{0x0F12, 0x0232 }, // #SARR_usDualGammaLutRGBIndoor_2__12_ 700032F0                              
{0x0F12, 0x0273 }, // #SARR_usDualGammaLutRGBIndoor_2__13_ 700032F2                              
{0x0F12, 0x02AF }, // #SARR_usDualGammaLutRGBIndoor_2__14_ 700032F4                              
{0x0F12, 0x0309 }, // #SARR_usDualGammaLutRGBIndoor_2__15_ 700032F6                              
{0x0F12, 0x0355 }, // #SARR_usDualGammaLutRGBIndoor_2__16_ 700032F8                              
{0x0F12, 0x0394 }, // #SARR_usDualGammaLutRGBIndoor_2__17_ 700032FA                              
{0x0F12, 0x03CE }, // #SARR_usDualGammaLutRGBIndoor_2__18_ 700032FC                              
{0x0F12, 0x03FF }, // #SARR_usDualGammaLutRGBIndoor_2__19_ 700032FE                              
{0x0F12, 0x0000 }, // #SARR_usDualGammaLutRGBOutdoor_0__0_ 70003300// Outdoor gamma              
{0x0F12, 0x0004 }, // #SARR_usDualGammaLutRGBOutdoor_0__1_ 70003302                              
{0x0F12, 0x0010 }, // #SARR_usDualGammaLutRGBOutdoor_0__2_ 70003304                              
{0x0F12, 0x002A }, // #SARR_usDualGammaLutRGBOutdoor_0__3_ 70003306                              
{0x0F12, 0x0062 }, // #SARR_usDualGammaLutRGBOutdoor_0__4_ 70003308                              
{0x0F12, 0x00D5 }, // #SARR_usDualGammaLutRGBOutdoor_0__5_ 7000330A                              
{0x0F12, 0x0138 }, // #SARR_usDualGammaLutRGBOutdoor_0__6_ 7000330C                              
{0x0F12, 0x0161 }, // #SARR_usDualGammaLutRGBOutdoor_0__7_ 7000330E                              
{0x0F12, 0x0186 }, // #SARR_usDualGammaLutRGBOutdoor_0__8_ 70003310                              
{0x0F12, 0x01BC }, // #SARR_usDualGammaLutRGBOutdoor_0__9_ 70003312                              
{0x0F12, 0x01E8 }, // #SARR_usDualGammaLutRGBOutdoor_0__10_70003314                              
{0x0F12, 0x020F }, // #SARR_usDualGammaLutRGBOutdoor_0__11_70003316                              
{0x0F12, 0x0232 }, // #SARR_usDualGammaLutRGBOutdoor_0__12_70003318                              
{0x0F12, 0x0273 }, // #SARR_usDualGammaLutRGBOutdoor_0__13_7000331A                              
{0x0F12, 0x02AF }, // #SARR_usDualGammaLutRGBOutdoor_0__14_7000331C                              
{0x0F12, 0x0309 }, // #SARR_usDualGammaLutRGBOutdoor_0__15_7000331E                              
{0x0F12, 0x0355 }, // #SARR_usDualGammaLutRGBOutdoor_0__16_70003320                              
{0x0F12, 0x0394 }, // #SARR_usDualGammaLutRGBOutdoor_0__17_70003322                              
{0x0F12, 0x03CE }, // #SARR_usDualGammaLutRGBOutdoor_0__18_70003324                              
{0x0F12, 0x03FF }, // #SARR_usDualGammaLutRGBOutdoor_0__19_70003326                              
{0x0F12, 0x0000 }, // #SARR_usDualGammaLutRGBOutdoor_1__0_ 70003328                              
{0x0F12, 0x0004 }, // #SARR_usDualGammaLutRGBOutdoor_1__1_ 7000332A                              
{0x0F12, 0x0010 }, // #SARR_usDualGammaLutRGBOutdoor_1__2_ 7000332C                              
{0x0F12, 0x002A }, // #SARR_usDualGammaLutRGBOutdoor_1__3_ 7000332E                              
{0x0F12, 0x0062 }, // #SARR_usDualGammaLutRGBOutdoor_1__4_ 70003330                              
{0x0F12, 0x00D5 }, // #SARR_usDualGammaLutRGBOutdoor_1__5_ 70003332                              
{0x0F12, 0x0138 }, // #SARR_usDualGammaLutRGBOutdoor_1__6_ 70003334                              
{0x0F12, 0x0161 }, // #SARR_usDualGammaLutRGBOutdoor_1__7_ 70003336                              
{0x0F12, 0x0186 }, // #SARR_usDualGammaLutRGBOutdoor_1__8_ 70003338                              
{0x0F12, 0x01BC }, // #SARR_usDualGammaLutRGBOutdoor_1__9_ 7000333A                              
{0x0F12, 0x01E8 }, // #SARR_usDualGammaLutRGBOutdoor_1__10_7000333C                              
{0x0F12, 0x020F }, // #SARR_usDualGammaLutRGBOutdoor_1__11_7000333E                              
{0x0F12, 0x0232 }, // #SARR_usDualGammaLutRGBOutdoor_1__12_70003340                              
{0x0F12, 0x0273 }, // #SARR_usDualGammaLutRGBOutdoor_1__13_70003342                              
{0x0F12, 0x02AF }, // #SARR_usDualGammaLutRGBOutdoor_1__14_70003344                              
{0x0F12, 0x0309 }, // #SARR_usDualGammaLutRGBOutdoor_1__15_70003346                              
{0x0F12, 0x0355 }, // #SARR_usDualGammaLutRGBOutdoor_1__16_70003348                              
{0x0F12, 0x0394 }, // #SARR_usDualGammaLutRGBOutdoor_1__17_7000334A                              
{0x0F12, 0x03CE }, // #SARR_usDualGammaLutRGBOutdoor_1__18_7000334C                              
{0x0F12, 0x03FF }, // #SARR_usDualGammaLutRGBOutdoor_1__19_7000334E                              
{0x0F12, 0x0000 }, // #SARR_usDualGammaLutRGBOutdoor_2__0_ 70003350                              
{0x0F12, 0x0004 }, // #SARR_usDualGammaLutRGBOutdoor_2__1_ 70003352                              
{0x0F12, 0x0010 }, // #SARR_usDualGammaLutRGBOutdoor_2__2_ 70003354                              
{0x0F12, 0x002A }, // #SARR_usDualGammaLutRGBOutdoor_2__3_ 70003356                              
{0x0F12, 0x0062 }, // #SARR_usDualGammaLutRGBOutdoor_2__4_ 70003358                              
{0x0F12, 0x00D5 }, // #SARR_usDualGammaLutRGBOutdoor_2__5_ 7000335A                              
{0x0F12, 0x0138 }, // #SARR_usDualGammaLutRGBOutdoor_2__6_ 7000335C                              
{0x0F12, 0x0161 }, // #SARR_usDualGammaLutRGBOutdoor_2__7_ 7000335E                              
{0x0F12, 0x0186 }, // #SARR_usDualGammaLutRGBOutdoor_2__8_ 70003360                              
{0x0F12, 0x01BC }, // #SARR_usDualGammaLutRGBOutdoor_2__9_ 70003362                              
{0x0F12, 0x01E8 }, // #SARR_usDualGammaLutRGBOutdoor_2__10_70003364                              
{0x0F12, 0x020F }, // #SARR_usDualGammaLutRGBOutdoor_2__11_70003366                              
{0x0F12, 0x0232 }, // #SARR_usDualGammaLutRGBOutdoor_2__12_70003368                              
{0x0F12, 0x0273 }, // #SARR_usDualGammaLutRGBOutdoor_2__13_7000336A                              
{0x0F12, 0x02AF }, // #SARR_usDualGammaLutRGBOutdoor_2__14_7000336C                              
{0x0F12, 0x0309 }, // #SARR_usDualGammaLutRGBOutdoor_2__15_7000336E                              
{0x0F12, 0x0355 }, // #SARR_usDualGammaLutRGBOutdoor_2__16_70003370                              
{0x0F12, 0x0394 }, // #SARR_usDualGammaLutRGBOutdoor_2__17_70003372                              
{0x0F12, 0x03CE }, // #SARR_usDualGammaLutRGBOutdoor_2__18_70003374                              
{0x0F12, 0x03FF }, // #SARR_usDualGammaLutRGBOutdoor_2__19_70003376                              
{0x002A, 0x06A6 },
{0x0F12, 0x00CA }, // #SARR_AwbCcmCord_0_
{0x0F12, 0x00EA }, // #SARR_AwbCcmCord_1_
{0x0F12, 0x0110 }, // #SARR_AwbCcmCord_2_
{0x0F12, 0x0124 }, // #SARR_AwbCcmCord_3_
{0x0F12, 0x0160 }, // #SARR_AwbCcmCord_4_
{0x0F12, 0x0180 }, // #SARR_AwbCcmCord_5_
//================================================================================================
// SET AFIT
//================================================================================================
// Noise index
{0x002A, 0x0764 },
{0x0F12, 0x0041 }, //0049 ,16,0}, //0041 // #afit_uNoiseIndInDoor[0] // 64
{0x0F12, 0x0063 }, //005F ,16,0}, //0063 // #afit_uNoiseIndInDoor[1] // 165
{0x0F12, 0x00BB }, //0138 ,16,0}, //00BB // #afit_uNoiseIndInDoor[2] // 377
{0x0F12, 0x0193 }, //01E0 ,16,0}, //0193 // #afit_uNoiseIndInDoor[3] // 616
{0x0F12, 0x02BC }, //0220 ,16,0}, //02BC // #afit_uNoiseIndInDoor[4] // 700
// AFIT table start address // 7000_07C4
{0x002A, 0x0770 },
{0x0F12, 0x07C4 },
{0x0F12, 0x7000 },
// AFIT table (Variables)
{0x002A, 0x07C4 },
{0x0F12, 0x0014 }, //0014 //0014 //0014 //0014
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0046 }, //0014 //0014 //0014 //0014
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x00C4 }, //00C4 //00C1 //00C1 //00C1
{0x0F12, 0x03FF }, //03FF //03FF //03FF //03FF
{0x0F12, 0x009C }, //009C //009C //009C //009C
{0x0F12, 0x017C }, //017C //017C //017C //017C
{0x0F12, 0x03FF }, //03FF //03FF //03FF //03FF
{0x0F12, 0x000C }, //000C //000C //000C //000C
{0x0F12, 0x0010 }, //0010 //0010 //0010 //0010
{0x0F12, 0x012C }, //012C //012C //012C //012C
{0x0F12, 0x03E8 }, //03E8 //03E8 //03E8 //03E8
{0x0F12, 0x0046 }, //0046 //0046 //0046 //0046
{0x0F12, 0x005A }, //005A //005A //005A //005A
{0x0F12, 0x0070 }, //0070 //0070 //0070 //0070
{0x0F12, 0x0019 }, //0019 //0028 //0028 //0028
{0x0F12, 0x0019 }, //0019 //0028 //0028 //0028
{0x0F12, 0x01AA }, //01AA //01AA //01AA //01AA
{0x0F12, 0x0064 }, //0064 //0064 //0064 //0064
{0x0F12, 0x0064 }, //0064 //0064 //0064 //0064
{0x0F12, 0x000A }, //000A //0014 //0014 //0014
{0x0F12, 0x000A }, //000A //0014 //0014 //0014
{0x0F12, 0x0032 }, //0032 //003C //003C //003C
{0x0F12, 0x0012 }, //0012 //0014 //0014 //0014
{0x0F12, 0x002A }, //002A //003C //003C //003C
{0x0F12, 0x0024 }, //0024 //001E //001E //001E
{0x0F12, 0x002A }, //002A //003C //003C //003C
{0x0F12, 0x0024 }, //0024 //001E //001E //001E
{0x0F12, 0x0A24 }, //0A24 //0A24 //0A24 //0A24
{0x0F12, 0x1701 }, //1701 //1701 //1701 //1701
{0x0F12, 0x0229 }, //0229 //0229 //0229 //0229
{0x0F12, 0x1403 }, //1403 //1403 //1403 //1403
{0x0F12, 0x0000 }, //0000 //6464 //6464 //6464
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x00FF }, //00FF //00FF //00FF //00FF
{0x0F12, 0x043B }, //043B //0A3B //0A3B //0A3B
{0x0F12, 0x1414 }, //1414 //1414 //1414 //1414
{0x0F12, 0x0301 }, //0301 //0301 //0301 //0301
{0x0F12, 0xFF07 }, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x051E }, //051E //081E //081E //081E
{0x0F12, 0x0A1E }, //0A1E //0A1E //0A1E //0A1E
{0x0F12, 0x0F0F }, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0A00 }, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x0A3C }, //0A3C //0028 //0028 //0028
{0x0F12, 0x0A28 }, //0A28 //001E //001E //001E
{0x0F12, 0x0002 }, //0002 //0002 //0002 //0002
{0x0F12, 0x00FF }, //00FF //00FF //00FF //00FF
{0x0F12, 0x1102 }, //1102 //1102 //1102 //1102
{0x0F12, 0x001B }, //001B //001B //001B //001B
{0x0F12, 0x0900 }, //0900 //0900 //0900 //0900
{0x0F12, 0x0600 }, //0600 //0600 //0600 //0600
{0x0F12, 0x0504 }, //0504 //0504 //0504 //0504
{0x0F12, 0x0305 }, //0305 //0306 //0306 //0306
{0x0F12, 0x1E03 }, // 1E03 //1E03 //1E03 //1E03
{0x0F12, 0x0080 }, //0080 //0080 //0080 //0078
{0x0F12, 0x0064 }, //0064 //0064 //0064 //0F64
{0x0F12, 0x0080 }, //0080 //0080 //0080 //0080
{0x0F12, 0x1414 }, //1414 //1414 //1414 //1414
{0x0F12, 0x0101 }, //0101 //0101 //0101 //0101
{0x0F12, 0x5002 }, //5002 //B402 //B402 //B402
{0x0F12, 0x7850 }, //7850 //DCB4 //DCB4 //DCB4
{0x0F12, 0x2878 }, //2878 //46DC //46DC //46DC
{0x0F12, 0x0A00 }, //0A00 //0A0A //0A0A //0A0A
{0x0F12, 0x1403 }, //1403 //0003 //0003 //0003
{0x0F12, 0x1E0C }, // 1E0C //1E00 //1E00 //1E00
{0x0F12, 0x070A }, //070A //0714 //0714 //0714
{0x0F12, 0x32FF }, //32FF //50FF //50FF //50FF
{0x0F12, 0x4104 }, //4104 //0506 //0506 //0506
{0x0F12, 0x123C }, //123C //0F05 //0F05 //0F05
{0x0F12, 0x4012 }, //4012 //400F //400F //400F
{0x0F12, 0x0204 }, //0204 //0204 //0204 //0204
{0x0F12, 0x1E03 }, // 1E03 //1403 //1403 //1403
{0x0F12, 0x011E }, //011E //0114 //0114 //0114
{0x0F12, 0x0201 }, //0201 //0201 //0201 //0201
{0x0F12, 0x5050 }, //5050 //445A //445A //445A
{0x0F12, 0x3C3C }, // 3C3C //DCDC //DCDC //DCDC
{0x0F12, 0x0028 }, //0028 //0028 //0028 //0028
{0x0F12, 0x030A }, //030A //030A //030A //030A
{0x0F12, 0x0714 }, //0714 //0000 //0000 //0000
{0x0F12, 0x0A1E }, //0A1E //141E //141E //141E
{0x0F12, 0xFF07 }, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x0432 }, //0432 //0432 //0432 //0432
{0x0F12, 0x4050 }, //4050 //0000 //0000 //0000
{0x0F12, 0x0F0F }, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0440 }, //0440 //0440 //0440 //0440
{0x0F12, 0x0302 }, //0302 //0302 //0302 //0302
{0x0F12, 0x1E1E }, // 1E1E //1414 //1414 //1414
{0x0F12, 0x0101 }, //0101 //0101 //0101 //0101
{0x0F12, 0x5002 }, //5002 //4601 //4601 //4601
{0x0F12, 0x3C50 }, // 3C50 //6444 //6444 //6444
{0x0F12, 0x283C }, //283C //285A //285A //285A
{0x0F12, 0x0A00 }, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x1403 }, //1403 //0003 //0003 //0003
{0x0F12, 0x1E07 }, // 1E07 //1E00 //1E00 //1E00
{0x0F12, 0x070A }, //070A //0714 //0714 //0714
{0x0F12, 0x32FF }, //32FF //32FF //32FF //32FF
{0x0F12, 0x5004 }, //5004 //0004 //0004 //0004
{0x0F12, 0x0F40 }, //0F40 //0F00 //0F00 //0F00
{0x0F12, 0x400F }, //400F //400F //400F //400F
{0x0F12, 0x0204 }, //0204 //0204 //0204 //0204
{0x0F12, 0x0003 }, //0003 //0003 //0003 //0003
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0046 }, //0014 //0014 //0014 //0014
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x00C4 }, //00C4 //00C1 //00C1 //00C1
{0x0F12, 0x03FF }, //03FF //03FF //03FF //03FF
{0x0F12, 0x009C }, //009C //009C //009C //009C
{0x0F12, 0x017C }, //017C //017C //017C //017C
{0x0F12, 0x03FF }, //03FF //03FF //03FF //03FF
{0x0F12, 0x000C }, //000C //000C //000C //000C
{0x0F12, 0x0010 }, //0010 //0010 //0010 //0010
{0x0F12, 0x012C }, //012C //012C //012C //012C
{0x0F12, 0x03E8 }, //03E8 //03E8 //03E8 //03E8
{0x0F12, 0x0046 }, //0046 //0046 //0046 //0046
{0x0F12, 0x005A }, //005A //005A //005A //005A
{0x0F12, 0x0070 }, //0070 //0070 //0070 //0070
{0x0F12, 0x000F }, //000F //0000 //0000 //0000
{0x0F12, 0x000F }, //000F //0000 //0000 //0000
{0x0F12, 0x01AA }, //01AA //01AA //01AA //01AA
{0x0F12, 0x003C }, //003C //0064 //0064 //0064
{0x0F12, 0x003C }, //003C //0064 //0064 //0064
{0x0F12, 0x0005 }, //0005 //0014 //0014 //0014
{0x0F12, 0x0005 }, //0005 //0014 //0014 //0014
{0x0F12, 0x0046 }, //0046 //0064 //0064 //0064
{0x0F12, 0x0019 }, //0019 //0014 //0014 //0014
{0x0F12, 0x002A }, //002A //003C //003C //003C
{0x0F12, 0x0024 }, //0024 //001E //001E //001E
{0x0F12, 0x002A }, //002A //003C //003C //003C
{0x0F12, 0x0024 }, //0024 //001E //001E //001E
{0x0F12, 0x0A24 }, //0A24 //0A24 //0A24 //0A24
{0x0F12, 0x1701 }, //1701 //1701 //1701 //1701
{0x0F12, 0x0229 }, //0229 //0229 //0229 //0229
{0x0F12, 0x1403 }, //1403 //1403 //1403 //1403
{0x0F12, 0x0000 }, //0000 //6464 //6464 //6464
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x00FF }, //00FF //00FF //00FF //00FF
{0x0F12, 0x043B }, //043B //023B //023B //023B
{0x0F12, 0x1414 }, //1414 //1414 //1414 //1414
{0x0F12, 0x0301 }, //0301 //0301 //0301 //0301
{0x0F12, 0xFF07 }, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x051E }, //051E //081E //081E //081E
{0x0F12, 0x0A1E }, //0A1E //0A1E //0A1E //0A1E
{0x0F12, 0x0F0F }, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0A00 }, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x0A3C }, //0A3C //0028 //0028 //0028
{0x0F12, 0x0A28 }, //0A28 //0005 //0005 //0005
{0x0F12, 0x0002 }, //0002 //0002 //0002 //0002
{0x0F12, 0x00FF }, //00FF //00FF //00FF //00FF
{0x0F12, 0x1102 }, //1102 //1102 //1102 //1102
{0x0F12, 0x001B }, //001B //001B //001B //001B
{0x0F12, 0x0900 }, //0900 //0900 //0900 //0900
{0x0F12, 0x0600 }, //0600 //0600 //0600 //0600
{0x0F12, 0x0504 }, //0504 //0504 //0504 //0504
{0x0F12, 0x0305 }, //0305 //0306 //0306 //0306
{0x0F12, 0x4603 }, //4603 //4603 //4603 //4603
{0x0F12, 0x0080 }, //0080 //0080 //0080 //006E
{0x0F12, 0x0080 }, //0080 //0080 //0080 //0F80
{0x0F12, 0x0080 }, //0080 //0080 //0080 //0080
{0x0F12, 0x1919 }, //1919 //2323 //2323 //2323
{0x0F12, 0x0101 }, //0101 //0101 //0101 //0101
{0x0F12, 0x3C02 }, // 3C02 //6402 //6402 //6402
{0x0F12, 0x643C }, //643C //7864 //7864 //7864
{0x0F12, 0x2864 }, //2864 //4678 //4678 //4678
{0x0F12, 0x0A00 }, //0A00 //0A0A //0A0A //0A0A
{0x0F12, 0x1403 }, //1403 //0003 //0003 //0003
{0x0F12, 0x1E0C }, // 1E0C //1E02 //1E02 //1E02
{0x0F12, 0x070A }, //070A //0764 //0764 //0764
{0x0F12, 0x32FF }, //32FF //50FF //50FF //50FF
{0x0F12, 0x4104 }, //4104 //0506 //0506 //0506
{0x0F12, 0x123C }, //123C //0F05 //0F05 //0F05
{0x0F12, 0x4012 }, //4012 //400F //400F //400F
{0x0F12, 0x0204 }, //0204 //0204 //0204 //0204
{0x0F12, 0x1E03 }, // 1E03 //1E03 //1E03 //1E03
{0x0F12, 0x011E }, //011E //011E //011E //011E
{0x0F12, 0x0201 }, //0201 //0201 //0201 //0201
{0x0F12, 0x3232 }, //3232 //3A3C //3A3C //3A3C
{0x0F12, 0x3C3C }, // 3C3C //4E50 //4E50 //4E50
{0x0F12, 0x0028 }, //0028 //0028 //0028 //0028
{0x0F12, 0x030A }, //030A //030A //030A //030A
{0x0F12, 0x0714 }, //0714 //0000 //0000 //0000
{0x0F12, 0x0A1E }, //0A1E //141E //141E //141E
{0x0F12, 0xFF07 }, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x0432 }, //0432 //0432 //0432 //0432
{0x0F12, 0x4050 }, //4050 //0000 //0000 //0000
{0x0F12, 0x0F0F }, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0440 }, //0440 //0440 //0440 //0440
{0x0F12, 0x0302 }, //0302 //0302 //0302 //0302
{0x0F12, 0x1E1E }, // 1E1E //1E1E //1E1E //1E1E
{0x0F12, 0x0101 }, //0101 //0101 //0101 //0101
{0x0F12, 0x3202 }, //3202 //3C01 //3C01 //3C01
{0x0F12, 0x3C32 }, // 3C32 //503A //503A //503A
{0x0F12, 0x283C }, //283C //284E //284E //284E
{0x0F12, 0x0A00 }, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x1403 }, //1403 //0003 //0003 //0003
{0x0F12, 0x1E07 }, // 1E07 //1E00 //1E00 //1E00
{0x0F12, 0x070A }, //070A //0714 //0714 //0714
{0x0F12, 0x32FF }, //32FF //32FF //32FF //32FF
{0x0F12, 0x5004 }, //5004 //0004 //0004 //0004
{0x0F12, 0x0F40 }, //0F40 //0F00 //0F00 //0F00
{0x0F12, 0x400F }, //400F //400F //400F //400F
{0x0F12, 0x0204 }, //0204 //0204 //0204 //0204
{0x0F12, 0x0003 }, //0003 //0003 //0003 //0003
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x00C4 }, //00C4 //00C1 //00C1 //00C1
{0x0F12, 0x03FF }, //03FF //03FF //03FF //03FF
{0x0F12, 0x009C }, //009C //009C //009C //009C
{0x0F12, 0x017C }, //017C //017C //017C //017C
{0x0F12, 0x03FF }, //03FF //03FF //03FF //03FF
{0x0F12, 0x000C }, //000C //000C //000C //000C
{0x0F12, 0x0010 }, //0010 //0010 //0010 //0010
{0x0F12, 0x012C }, //012C //012C //012C //012C
{0x0F12, 0x03E8 }, //03E8 //03E8 //03E8 //03E8
{0x0F12, 0x0046 }, //0046 //0046 //0046 //0046
{0x0F12, 0x0078 }, //0078 //005A //005A //005A
{0x0F12, 0x0070 }, //0070 //0070 //0070 //0070
{0x0F12, 0x0004 }, //0004 //0000 //0000 //0000
{0x0F12, 0x0004 }, //0004 //0000 //0000 //0000
{0x0F12, 0x01AA }, //01AA //01AA //01AA //01AA
{0x0F12, 0x001E }, //001E //0032 //0032 //0032
{0x0F12, 0x001E }, //001E //0032 //0032 //0032
{0x0F12, 0x0002 }, //0002 //0002 //0002 //0002
{0x0F12, 0x0002 }, //0002 //0002 //0002 //0002
{0x0F12, 0x0064 }, //0064 //00C8 //00C8 //00C8
{0x0F12, 0x003C }, //001B //0014 //0014 //0014
{0x0F12, 0x002A }, //002A //003C //003C //003C
{0x0F12, 0x0024 }, //0024 //001E //001E //001E
{0x0F12, 0x002A }, //002A //003C //003C //003C
{0x0F12, 0x0024 }, //0024 //001E //001E //001E
{0x0F12, 0x0A24 }, //0A24 //0A24 //0A24 //0A24
{0x0F12, 0x1701 }, //1701 //1701 //1701 //1701
{0x0F12, 0x0229 }, //0229 //0229 //0229 //0229
{0x0F12, 0x1403 }, //1403 //1403 //1403 //1403
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x00FF }, //00FF //00FF //00FF //00FF
{0x0F12, 0x043B }, //043B //023B //023B //023B
{0x0F12, 0x1414 }, //1414 //1414 //1414 //1414
{0x0F12, 0x0301 }, //0301 //0301 //0301 //0301
{0x0F12, 0xFF07 }, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x051E }, //051E //081E //081E //081E
{0x0F12, 0x0A1E }, //0A1E //0A1E //0A1E //0A1E
{0x0F12, 0x0F0F }, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0A00 }, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x0A3C }, //0A3C //0028 //0028 //0028
{0x0F12, 0x0D2E }, //0528 //0528 //0005 //0005 //0005
{0x0F12, 0x0002 }, //0002 //0001 //0001 //0001
{0x0F12, 0x00FF }, //00FF //00FF //00FF //00FF
{0x0F12, 0x1102 }, //1102 //1102 //1102 //1102
{0x0F12, 0x001B }, //001B //001B //001B //001B
{0x0F12, 0x0900 }, //0900 //0900 //0900 //0900
{0x0F12, 0x0600 }, //0600 //0600 //0600 //0600
{0x0F12, 0x0504 }, //0504 //0504 //0504 //0504
{0x0F12, 0x0305 }, //0305 //0306 //0306 //0306
{0x0F12, 0x4602 }, //4602 //4602 //4602 //4602
{0x0F12, 0x2880 }, //2880 //2880 //0080 //0080
{0x0F12, 0x0080 }, //0080 //0080 //0080 //0080
{0x0F12, 0x0080 }, //0080 //0080 //0080 //0080
{0x0F12, 0x2323 }, //2323 //3C3C //3C3C //3C3C
{0x0F12, 0x0101 }, //0101 //0101 //0101 //0101
{0x0F12, 0x2A02 }, // 2A02 //1E02 //1E02 //1E02
{0x0F12, 0x3C2A }, // 3C2A //2428 //2428 //2428
{0x0F12, 0x283C }, //283C //462D //462D //462D
{0x0F12, 0x0A00 }, //0A00 //0A0A //0A0A //0A0A
{0x0F12, 0x1403 }, //1403 //2303 //2303 //2303
{0x0F12, 0x1E0C }, // 1E0C //1402 //1402 //1402
{0x0F12, 0x070A }, //070A //08C8 //08C8 //08C8
{0x0F12, 0x32FF }, //32FF //1464 //1464 //1464
{0x0F12, 0x6E04 }, //6E04 //B402 //B402 //B402
{0x0F12, 0x0F96 }, //0F48 //2514 //2514 //2514
{0x0F12, 0x400F }, //400F //4009 //4009 //4009
{0x0F12, 0x0204 }, //0204 //0204 //0204 //0204
{0x0F12, 0x2303 }, //2303 //2803 //2803 //2803
{0x0F12, 0x0123 }, //0123 //0128 //0128 //0128
{0x0F12, 0x0201 }, //0201 //0201 //0201 //0201
{0x0F12, 0x262A }, //262A //2224 //2224 //2224
{0x0F12, 0x2C2C }, // 2C2C //282C //282C //282C
{0x0F12, 0x0028 }, //0028 //0028 //0028 //0028
{0x0F12, 0x030A }, //030A //030A //030A //030A
{0x0F12, 0x0714 }, //0714 //0410 //0410 //0410
{0x0F12, 0x0A1E }, //0A1E //141E //141E //141E
{0x0F12, 0xFF07 }, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x0432 }, //0432 //0432 //0432 //0432
{0x0F12, 0x4050 }, //4050 //4050 //4050 //4050
{0x0F12, 0x0F0F }, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0440 }, //0440 //0440 //0440 //0440
{0x0F12, 0x0302 }, //0302 //0302 //0302 //0302
{0x0F12, 0x2323 }, //2323 //2828 //2828 //2828
{0x0F12, 0x0101 }, //0101 //0101 //0101 //0101
{0x0F12, 0x2A02 }, // 2A02 //2401 //2401 //2401
{0x0F12, 0x2C26 }, // 2C26 //2C22 //2C22 //2C22
{0x0F12, 0x282C }, //282C //2828 //2828 //2828
{0x0F12, 0x0A00 }, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x1403 }, //1403 //1003 //1003 //1003
{0x0F12, 0x1E07 }, // 1E07 //1E04 //1E04 //1E04
{0x0F12, 0x070A }, //070A //0714 //0714 //0714
{0x0F12, 0x32FF }, //32FF //32FF //32FF //32FF
{0x0F12, 0x5004 }, //5004 //5004 //5004 //5004
{0x0F12, 0x0F40 }, //0F40 //0F40 //0F40 //0F40
{0x0F12, 0x400F }, //400F //400F //400F //400F
{0x0F12, 0x0204 }, //0204 //0204 //0204 //0204
{0x0F12, 0x0003 }, //0003 //0003 //0003 //0003
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x00C4 }, //00C4 //00C1 //00C1 //00C1
{0x0F12, 0x03FF }, //03FF //03FF //03FF //03FF
{0x0F12, 0x009C }, //009C //009C //009C //009C
{0x0F12, 0x017C }, //017C //017C //017C //017C
{0x0F12, 0x03FF }, //03FF //03FF //03FF //03FF
{0x0F12, 0x000C }, //000C //000C //000C //000C
{0x0F12, 0x0010 }, //0010 //0010 //0010 //0010
{0x0F12, 0x00C8 }, //00C8 //00C8 //00C8 //00C8
{0x0F12, 0x03E8 }, //03E8 //03E8 //03E8 //03E8
{0x0F12, 0x0046 }, //0046 //0046 //0046 //0046
{0x0F12, 0x0082 }, //0082 //0050 //0050 //0050
{0x0F12, 0x0070 }, //0070 //0070 //0070 //0070
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x01AA }, //01AA //01AA //01AA //01AA
{0x0F12, 0x001E }, //001E //0032 //0032 //0032
{0x0F12, 0x001E }, //001E //0032 //0032 //0032
{0x0F12, 0x0002 }, //0002 //0002 //0002 //0002
{0x0F12, 0x0002 }, //0002 //0002 //0002 //0002
{0x0F12, 0x010E }, //010E //00C8 //00C8 //00C8
{0x0F12, 0x003C }, //0028 //0014 //0014 //0014
{0x0F12, 0x0032 }, //0032 //002D //002D //002D
{0x0F12, 0x0028 }, //0028 //0019 //0019 //0019
{0x0F12, 0x0032 }, //0032 //002D //002D //002D
{0x0F12, 0x0028 }, //0028 //0019 //0019 //0019
{0x0F12, 0x0A24 }, //0A24 //0A24 //0A24 //0A24
{0x0F12, 0x1701 }, //1701 //1701 //1701 //1701
{0x0F12, 0x0229 }, //0229 //0229 //0229 //0229
{0x0F12, 0x1403 }, //1403 //1403 //1403 //1403
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x00FF }, //00FF //00FF //00FF //00FF
{0x0F12, 0x043B }, //043B //023B //023B //023B
{0x0F12, 0x1414 }, //1414 //1414 //1414 //1414
{0x0F12, 0x0301 }, //0301 //0301 //0301 //0301
{0x0F12, 0xFF07 }, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x051E }, //051E //081E //081E //081E
{0x0F12, 0x0A1E }, //0A1E //0A1E //0A1E //0A1E
{0x0F12, 0x0F0F }, //0F0F //0F0F //0F0F //0F0F
{0x0F12, 0x0A00 }, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x0A3C }, //0A3C //0028 //0028 //0028
{0x0F12, 0x173E }, //0532 //0532 //0005 //0005 //0005
{0x0F12, 0x0002 }, //0002 //0001 //0001 //0001
{0x0F12, 0x00FF }, //00FF //00FF //00FF //00FF
{0x0F12, 0x1002 }, //1002 //1002 //1002 //1002
{0x0F12, 0x001E }, //001E //001E //001E //001E
{0x0F12, 0x0900 }, //0900 //0900 //0900 //0900
{0x0F12, 0x0600 }, //0600 //0600 //0600 //0600
{0x0F12, 0x0504 }, //0504 //0504 //0504 //0504
{0x0F12, 0x0305 }, //0305 //0307 //0307 //0307
{0x0F12, 0x5002 }, //5002 //5002 //5002 //5002
{0x0F12, 0x2880 }, //2880 //2880 //0080 //0080
{0x0F12, 0x0080 }, //0080 //0080 //0080 //0080
{0x0F12, 0x0080 }, //0080 //0080 //0080 //0080
{0x0F12, 0x2328 }, //2328 //4646 //4646 //4646
{0x0F12, 0x0101 }, //0101 //0101 //0101 //0101
{0x0F12, 0x2A02 }, // 2A02 //1E02 //1E02 //1E02
{0x0F12, 0x2228 }, //2228 //1D28 //1D28 //1D28
{0x0F12, 0x2822 }, //2822 //321D //321D //321D
{0x0F12, 0x0A00 }, //0A00 //0A0A //0A0A //0A0A
{0x0F12, 0x1903 }, //1903 //2303 //2303 //2303
{0x0F12, 0x1E0F }, // 1E0F //1402 //1402 //1402
{0x0F12, 0x070A }, //070A //08B4 //08B4 //08B4
{0x0F12, 0x32FF }, //32FF //1464 //1464 //1464
{0x0F12, 0xAA04 }, //AA04 //B402 //B402 //B402
{0x0F12, 0x0F96 }, //0F5A //2514 //2514 //2514
{0x0F12, 0x400F }, //400F //4009 //4009 //4009
{0x0F12, 0x0504 }, //0504 //0204 //0204 //0204
{0x0F12, 0x2805 }, //2805 //3C03 //3C03 //3C03
{0x0F12, 0x0123 }, //0123 //013C //013C //013C
{0x0F12, 0x0201 }, //0201 //0201 //0201 //0201
{0x0F12, 0x2024 }, //2024 //1C1E //1C1E //1C1E
{0x0F12, 0x1C1C }, // 1C1C //1418 //1418 //1418
{0x0F12, 0x0028 }, //0028 //0028 //0028 //0028
{0x0F12, 0x030A }, //030A //030A //030A //030A
{0x0F12, 0x0A0A }, //0A0A //0214 //0214 //0214
{0x0F12, 0x0A2D }, //0A2D //0E14 //0E14 //0E14
{0x0F12, 0xFF07 }, //FF07 //FF06 //FF06 //FF06
{0x0F12, 0x0432 }, //0432 //0432 //0432 //0432
{0x0F12, 0x4050 }, //4050 //4052 //4052 //4052
{0x0F12, 0x0F0F }, //0F0F //150C //150C //150C
{0x0F12, 0x0440 }, //0440 //0440 //0440 //0440
{0x0F12, 0x0302 }, //0302 //0302 //0302 //0302
{0x0F12, 0x2328 }, //2328 //3C3C //3C3C //3C3C
{0x0F12, 0x0101 }, //0101 //0101 //0101 //0101
{0x0F12, 0x3C02 }, // 3C02 //1E01 //1E01 //1E01
{0x0F12, 0x1C3C }, // 1C3C //181C //181C //181C
{0x0F12, 0x281C }, //281C //2814 //2814 //2814
{0x0F12, 0x0A00 }, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x0A03 }, //0A03 //1403 //1403 //1403
{0x0F12, 0x2D0A }, // 2D0A //1402 //1402 //1402
{0x0F12, 0x070A }, //070A //060E //060E //060E
{0x0F12, 0x32FF }, //32FF //32FF //32FF //32FF
{0x0F12, 0x5004 }, //5004 //5204 //5204 //5204
{0x0F12, 0x0F40 }, //0F40 //0C40 //0C40 //0C40
{0x0F12, 0x400F }, //400F //4015 //4015 //4015
{0x0F12, 0x0204 }, //0204 //0204 //0204 //0204
{0x0F12, 0x0003 }, //0003 //0003 //0003 //0003
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x00C4 }, //00C4 //00C1 //00C1 //00C1
{0x0F12, 0x03FF }, //03FF //03FF //03FF //03FF
{0x0F12, 0x009C }, //009C //009C //009C //009C
{0x0F12, 0x017C }, //017C //017C //017C //017C
{0x0F12, 0x03FF }, //03FF //03FF //03FF //03FF
{0x0F12, 0x000C }, //000C //000C //000C //000C
{0x0F12, 0x0010 }, //0010 //0010 //0010 //0010
{0x0F12, 0x00C8 }, //00C8 //0032 //0032 //0032
{0x0F12, 0x028A }, //028A //028A //028A //028A
{0x0F12, 0x0046 }, //0046 //0032 //0032 //0032
{0x0F12, 0x015E }, //015E //01F4 //01F4 //01F4
{0x0F12, 0x0070 }, //0070 //0070 //0070 //0070
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x01AA }, //01AA //01AA //01AA //01AA
{0x0F12, 0x0014 }, //0014 //003C //003C //003C
{0x0F12, 0x0014 }, //0014 //0050 //0050 //0050
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x0140 }, //0140 //00B4 //00B4 //00B4
{0x0F12, 0x003C }, //003C //0014 //0014 //0014
{0x0F12, 0x0032 }, //0032 //0046 //0046 //0046
{0x0F12, 0x0023 }, //0023 //0019 //0019 //0019
{0x0F12, 0x0023 }, //0023 //0046 //0046 //0046
{0x0F12, 0x0032 }, //0032 //0019 //0019 //0019
{0x0F12, 0x0A24 }, //0A24 //0A24 //0A24 //0A24
{0x0F12, 0x1701 }, //1701 //1701 //1701 //1701
{0x0F12, 0x0229 }, //0229 //0229 //0229 //0229
{0x0F12, 0x1403 }, //1403 //0503 //0503 //0503
{0x0F12, 0x0000 }, //0000 //080F //080F //080F
{0x0F12, 0x0000 }, //0000 //0808 //0808 //0808
{0x0F12, 0x0000 }, //0000 //0000 //0000 //0000
{0x0F12, 0x00FF }, //00FF //00FF //00FF //00FF
{0x0F12, 0x043B }, //043B //022D //022D //022D
{0x0F12, 0x1414 }, //1414 //1414 //1414 //1414
{0x0F12, 0x0301 }, //0301 //0301 //0301 //0301
{0x0F12, 0xFF07 }, //FF07 //FF07 //FF07 //FF07
{0x0F12, 0x051E }, //051E //061E //061E //061E
{0x0F12, 0x0A1E }, //0A1E //0A1E //0A1E //0A1E
{0x0F12, 0x0606 }, //0606 //0606 //0606 //0606
{0x0F12, 0x0A01 }, //0A01 //0A01 //0A01 //0A01
{0x0F12, 0x143C }, //143C //0028 //0028 //0028
{0x0F12, 0x203E }, //0532 //0532 //0002 //0002 //0002
{0x0F12, 0x0002 }, //0002 //0001 //0001 //0001
{0x0F12, 0x00FF }, //00FF //00FF //00FF //00FF
{0x0F12, 0x1002 }, //1002 //1002 //1002 //1002
{0x0F12, 0x001E }, //001E //001E //001E //001E
{0x0F12, 0x0900 }, //0900 //0900 //0900 //0900
{0x0F12, 0x0600 }, //0600 //0600 //0600 //0600
{0x0F12, 0x0504 }, //0504 //0504 //0504 //0504
{0x0F12, 0x0305 }, //0305 //0307 //0307 //0307
{0x0F12, 0x5001 }, //5001 //5001 //5001 //5001
{0x0F12, 0x1980 }, //2880 //2880 //0080 //0080
{0x0F12, 0x0080 }, //0080 //0080 //0080 //0080
{0x0F12, 0x0080 }, //0080 //0080 //0080 //0080
{0x0F12, 0x5050 }, //5050 //5050 //5050 //5050
{0x0F12, 0x0101 }, //0101 //0101 //0101 //0101
{0x0F12, 0x1C02 }, // 1C02 //1E02 //1E02 //1E02
{0x0F12, 0x191C }, //191C //1219 //1219 //1219
{0x0F12, 0x2819 }, //2819 //320E //320E //320E
{0x0F12, 0x0A00 }, //0A00 //0A0A //0A0A //0A0A
{0x0F12, 0x1E03 }, // 1E03 //2504 //2504 //2504
{0x0F12, 0x1E0F }, // 1E0F //0A08 //0A08 //0A08
{0x0F12, 0x0508 }, //0508 //0832 //0832 //0832
{0x0F12, 0x32FF }, //32FF //1432 //1432 //1432
{0x0F12, 0xBE04 }, //BE04 //A001 //A001 //A001
{0x0F12, 0x1496 }, //146E //250A //250A //250A
{0x0F12, 0x4015 }, //4015 //4005 //4005 //4005
{0x0F12, 0x0604 }, //0604 //0604 //0604 //0604
{0x0F12, 0x5006 }, //5006 //4606 //4606 //4606
{0x0F12, 0x0150 }, //0150 //0146 //0146 //0146
{0x0F12, 0x0201 }, //0201 //0201 //0201 //0201
{0x0F12, 0x1E1E }, // 1E1E //1C18 //1C18 //1C18
{0x0F12, 0x1212 }, //1212 //0E0F //0E0F //0E0F
{0x0F12, 0x0028 }, //0028 //0028 //0028 //0028
{0x0F12, 0x030A }, //030A //030A //030A //030A
{0x0F12, 0x0A10 }, //0A10 //0514 //0514 //0514
{0x0F12, 0x0819 }, //0819 //0C14 //0C14 //0C14
{0x0F12, 0xFF05 }, //FF05 //FF05 //FF05 //FF05
{0x0F12, 0x0432 }, //0432 //0432 //0432 //0432
{0x0F12, 0x4052 }, //4052 //4052 //4052 //4052
{0x0F12, 0x1514 }, //1514 //1514 //1514 //1514
{0x0F12, 0x0440 }, //0440 //0440 //0440 //0440
{0x0F12, 0x0302 }, //0302 //0302 //0302 //0302
{0x0F12, 0x5050 }, //5050 //4646 //4646 //4646
{0x0F12, 0x0101 }, //0101 //0101 //0101 //0101
{0x0F12, 0x1E02 }, // 1E02 //1801 //1801 //1801
{0x0F12, 0x121E }, //121E //0F1C //0F1C //0F1C
{0x0F12, 0x2812 }, //2812 //280E //280E //280E
{0x0F12, 0x0A00 }, //0A00 //0A00 //0A00 //0A00
{0x0F12, 0x1003 }, //1003 //1403 //1403 //1403
{0x0F12, 0x190A }, //190A //1405 //1405 //1405
{0x0F12, 0x0508 }, //0508 //050C //050C //050C
{0x0F12, 0x32FF }, //32FF //32FF //32FF //32FF
{0x0F12, 0x5204 }, //5204 //5204 //5204 //5204
{0x0F12, 0x1440 }, //1440 //1440 //1440 //1440
{0x0F12, 0x4015 }, //4015 //4015 //4015 //4015
{0x0F12, 0x0204 }, //0204 //0204 //0204 //0204
{0x0F12, 0x0003 }, //0003 //0003 //0003 //0003
// AFIT table (Constants)
{0x0F12, 0x7F7A }, //7FFA // #afit_pConstBaseVals[0]
{0x0F12, 0x7FBD }, //FFBD // #afit_pConstBaseVals[1]
{0x0F12, 0xBEFC }, //26FE // #afit_pConstBaseVals[2]
{0x0F12, 0xF7BC }, //F7BC // #afit_pConstBaseVals[3]
{0x0F12, 0x7E06 }, //7E06 // #afit_pConstBaseVals[4]
{0x0F12, 0x0053 }, //00D3 // #afit_pConstBaseVals[5]
// Update Changed Registers
{0x002A, 0x0664 },
{0x0F12, 0x013E }, //013E //seti_uContrastCenter

//WRITE 700004D6 0001 // #REG_TC_DBG_ReInitCmd

//============================================================
// ISP-FE Setting END
//============================================================
              
//================================================================================================
// SET PLL    
//================================================================================================
// How to set 
// 1. MCLK    
// 2. System CLK
// 3. PCLK    
//================================================================================================
// Set input CLK // 24MHz
              
{0x002A, 0x01CC },
{0x0F12, 0x4B00 }, // #REG_TC_IPRM_InClockLSBs 19.2MHz
{0x0F12, 0x0000 }, // #REG_TC_IPRM_InClockMSBs
{0x002A, 0x01EE },
{0x0F12, 0x0000 }, // #REG_TC_IPRM_UseNPviClocks // Number of PLL setting
// Set system CLK // 58MHz
{0x0F12, 0x0001 },  //#REG_TC_IPRM_UseNMiPiClocks  // Number of PLL setting                                     
{0x0F12, 0x0001 },  //#REG_TC_IPRM_NumberOfMipiLanes      // Number of MIPI Lane  
{0x002A, 0x01F6 },
{0x0F12, 0x38A4 }, //1D4C //50M 1D4C // #REG_TC_IPRM_OpClk4KHz_0
// Set pixel CLK // 48MHz (0x3A98)
{0x0F12, 0x2ED0 }, // #REG_TC_IPRM_MinOutRate4KHz_0
{0x0F12, 0x2EF0 }, // #REG_TC_IPRM_MaxOutRate4KHz_0

// Set system CLK // 30MHz
{0x0F12, 0x1D4C }, //1D4C //50M 1D4C // #REG_TC_IPRM_OpClk4KHz_1
// Set pixel CLK // 48MHz (0x3A98)
{0x0F12, 0x2ED0 }, // #REG_TC_IPRM_MinOutRate4KHz_1
{0x0F12, 0x2EF0 }, // #REG_TC_IPRM_MaxOutRate4KHz_1

// Update PLL 
{0x002A, 0x0208 },
{0x0F12, 0x0001 }, // #REG_TC_IPRM_InitParamsUpdated
              
//============================================================
// Frame rate setting
//============================================================
// How to set 
// 1. Exposure value
// dec2hex((1 / (frame rate you want(ms))) * 100d * 4d)
// 2. Analog Digital gain
// dec2hex((Analog gain you want) * 256d)
//============================================================
// Set preview exposure time
{0x002A, 0x0530 },
{0x0F12, 0x3A98 }, // #lt_uMaxExp1    30ms
{0x0F12, 0x0000 },
{0x0F12, 0x7EF4 }, // #lt_uMaxExp2    65ms
{0x0F12, 0x0000 },
{0x002A, 0x167C },
{0x0F12, 0x9C40 }, // #evt1_lt_uMaxExp3  80ms
{0x0F12, 0x0000 },
{0x0F12, 0xF424 }, // #evt1_lt_uMaxExp4  125ms
{0x0F12, 0x0000 },
              
// Set capture, exposure time
{0x002A, 0x0538 },
{0x0F12, 0x3A98 }, // #lt_uCapMaxExp1   30ms
{0x0F12, 0x0000 },
{0x0F12, 0x7EF4 }, // #lt_uCapMaxExp2      65ms
{0x0F12, 0x0000 },
{0x002A, 0x1684 },
{0x0F12, 0x9C40 }, // #evt1_lt_uCapMaxExp3 80ms
{0x0F12, 0x0000 },
{0x0F12, 0xF424 }, // #evt1_lt_uCapMaxExp4 125ms
{0x0F12, 0x0000 },

// Set gain   
{0x002A, 0x0540 },
{0x0F12, 0x0170 }, //0320 // #lt_uMaxAnGain1
{0x0F12, 0x0250 }, //0380 // #lt_uMaxAnGain2
{0x002A, 0x168C },
{0x0F12, 0x0380 }, //0500 // #evt1_lt_uMaxAnGain3
{0x0F12, 0x0800 }, //0800 // #evt1_lt_uMaxAnGain4
              
{0x002A, 0x0544 },
{0x0F12, 0x0100 }, // #lt_uMaxDigGain
{0x0F12, 0x0800 }, // #lt_uMaxTotGain

{0x002A, 0x1694 },
{0x0F12, 0x0001 }, // #evt1_senHal_bExpandForbid

{0x002A, 0x051A },
{0x0F12, 0x0111 }, // #lt_uLimitHigh
{0x0F12, 0x00F0 }, // #lt_uLimitLow
              
{0x002A, 0x0572 },
{0x0F12, 0x0007 }, //#skl_usConfigStbySettings // Enable T&P code after HW stby + skip ZI part on HW wakeup.
               
//================================================================================================
// SET PREVIEW CONFIGURATION_0
// # Foramt : YUV422
// # Size: QXGA
// # FPS : 30fps
//================================================================================================
{0x002A, 0x026C },
{0x0F12, 0x0280 }, //#REG_0TC_PCFG_usWidth//640
{0x0F12, 0x01E0 }, //#REG_0TC_PCFG_usHeight //480    026E
{0x0F12, 0x0005 }, //#REG_0TC_PCFG_Format            0270
{0x0F12, 0x2EF0 }, //#REG_0TC_PCFG_usMaxOut4KHzRate  0272
{0x0F12, 0x2ED0 }, //#REG_0TC_PCFG_usMinOut4KHzRate  0274
{0x0F12, 0x0100 }, //#REG_0TC_PCFG_OutClkPerPix88    0276
{0x0F12, 0x0800 }, //#REG_0TC_PCFG_uMaxBpp88         027
{0x0F12, 0x0052 }, //#REG_0TC_PCFG_PVIMask //s0050 = FALSE in MSM6290 : s0052 = TRUE in MSM6800 //reg 027A
{0x002A, 0x027E },
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_usJpegPacketSize
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_usJpegTotalPackets
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_uClockInd
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_usFrTimeType
{0x0F12, 0x0001 }, //#REG_0TC_PCFG_FrRateQualityType
{0x0F12, 0x0535 }, //#REG_0TC_PCFG_usMaxFrTimeMsecMult10 //7.5fps
{0x0F12, 0x014E }, //029a //#REG_0TC_PCFG_usMinFrTimeMsecMult10 //25fps
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_bSmearOutput
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_sSaturation
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_sSharpBlur
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_sColorTemp
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_uDeviceGammaIndex
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_uPrevMirror
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_uCaptureMirror
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_uRotation
 //================================================================================================
// SET PREVIEW CONFIGURATION_1
// # Foramt : YUV422
// # Size: QXGA
// # FPS : 5fps~30fps
//================================================================================================
{0x0F12, 0x0280 }, //REG_PrevConfigControls_1_
{0x0F12, 0x01E0 }, //REG_1TC_PCFG_usHeight
{0x0F12, 0x0005 }, //REG_1TC_PCFG_Format
{0x0F12, 0x2EF0 }, //#REG_0TC_PCFG_usMaxOut4KHzRate  0272
{0x0F12, 0x2ED0 }, //#REG_0TC_PCFG_usMinOut4KHzRate  0274
{0x0F12, 0x0100 }, //REG_1TC_PCFG_OutClkPerPix884BC4
{0x0F12, 0x0800 }, //REG_1TC_PCFG_uMaxBpp88
{0x0F12, 0x0052 }, //REG_1TC_PCFG_PVIMask
{0x0F12, 0x0000 }, //REG_1TC_PCFG_OIFMask
{0x002A, 0x02B2 },
{0x0F12, 0x0000 }, //REG_1TC_PCFG_uClockInd
{0x0F12, 0x0000 }, //REG_1TC_PCFG_usFrTimeType
{0x0F12, 0x0002 }, //REG_1TC_PCFG_FrRateQualityType
{0x0F12, 0x0535 }, //REG_0TC_PCFG_usMaxFrTimeMsecMult10  //7.5fps 
{0x0F12, 0x029A }, //REG_0TC_PCFG_usMinFrTimeMsecMult10  //15fps   
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_bSmearOutput
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_sSaturation
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_sSharpBlur
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_sColorTemp
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_uDeviceGammaIndex
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_uPrevMirror
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_uCaptureMirror
{0x0F12, 0x0000 }, //#REG_0TC_PCFG_uRotation
//================================================================================================
// SET PREVIEW CONFIGURATION_2 (Night Mode)
// # Foramt : YUV422
// # Size: QXGA
// # FPS : 4fps~15fps
//================================================================================================
{0x002A, 0x02CC }, 
{0x0F12, 0x0280 },  //REG_2TC_PCFG_usWidth
{0x0F12, 0x01E0 },  //REG_2TC_PCFG_usHeight
{0x0F12, 0x0005 },  //REG_2TC_PCFG_Format
{0x0F12, 0x2EF0 },  //REG_2TC_PCFG_usMaxOut4KHzRate
{0x0F12, 0x2ED0 },  //REG_2TC_PCFG_usMinOut4KHzRate
{0x0F12, 0x0100 },  //REG_2TC_PCFG_OutClkPerPix88
{0x0F12, 0x0800 },  //REG_2TC_PCFG_uMaxBpp88
{0x0F12, 0x0052 },  //REG_2TC_PCFG_PVIMask
{0x0F12, 0x0000 },  //REG_2TC_PCFG_OIFMask
{0x0F12, 0x01E0 },  //REG_2TC_PCFG_usJpegPacketSize
{0x0F12, 0x0000 },  //REG_2TC_PCFG_usJpegTotalPackets
{0x0F12, 0x0000 },  //REG_2TC_PCFG_uClockInd
{0x0F12, 0x0000 },  //REG_2TC_PCFG_usFrTimeType
{0x0F12, 0x0001 },  //REG_2TC_PCFG_FrRateQualityType
{0x0F12, 0x09C4 },  //REG_2TC_PCFG_usMaxFrTimeMsecMult10 //4fps
{0x0F12, 0x029A },  //REG_2TC_PCFG_usMinFrTimeMsecMult10 //15fps
{0x0F12, 0x0000 },  //REG_2TC_PCFG_bSmearOutput
{0x0F12, 0x0000 },  //REG_2TC_PCFG_sSaturation
{0x0F12, 0x0000 },  //REG_2TC_PCFG_sSharpBlur
{0x0F12, 0x0000 },  //REG_2TC_PCFG_sColorTemp
{0x0F12, 0x0000 },  //REG_2TC_PCFG_uDeviceGammaIndex
{0x0F12, 0x0000 },  //REG_2TC_PCFG_uPrevMirror
{0x0F12, 0x0000 },  //REG_2TC_PCFG_uCaptureMirror
{0x0F12, 0x0000 },  //REG_2TC_PCFG_uRotation

//================================================================================================
// APPLY PREVIEW CONFIGURATION & RUN PREVIEW
//================================================================================================
{0x002A, 0x023C },
{0x0F12, 0x0000 }, // #REG_TC_GP_ActivePrevConfig // Select preview configuration_0
{0x002A, 0x0240 },
{0x0F12, 0x0001 }, // #REG_TC_GP_PrevOpenAfterChange
{0x002A, 0x0230 },
{0x0F12, 0x0001 }, // #REG_TC_GP_NewConfigSync // Update preview configuration
{0x002A, 0x023E },
{0x0F12, 0x0001 }, // #REG_TC_GP_PrevConfigChanged
{0x002A, 0x0220 },
{0x0F12, 0x0001 }, // #REG_TC_GP_EnablePreview // Start preview
//{0x0028, 0xD000 },
//{0x002A, 0xB0A0 },
//{0x0F12, 0x0000 }, // Clear cont. clock befor config change
//{0x0028, 0x7000 },
//{0x002A, 0x0222 },
{0x0F12, 0x0001 }, // #REG_TC_GP_EnablePreviewChanged
              
//================================================================================================
// SET CAPTURE CONFIGURATION_0
// # Foramt :JPEG
// # Size: QXGA
// # FPS : 10 ~ 7.5fps
//================================================================================================
{0x002A, 0x035C },
{0x0F12, 0x0000 }, //#REG_0TC_CCFG_uCaptureModeJpEG
{0x0F12, 0x0800 }, //#REG_0TC_CCFG_usWidth
{0x0F12, 0x0600 }, //#REG_0TC_CCFG_usHeight
{0x0F12, 0x0005 }, //#REG_0TC_CCFG_Format//5:YUV9:JPEG
{0x0F12, 0x2EF0 }, //#REG_0TC_CCFG_usMaxOut4KHzRate
{0x0F12, 0x2ED0 }, //#REG_0TC_CCFG_usMinOut4KHzRate
{0x0F12, 0x0100 }, //#REG_0TC_CCFG_OutClkPerPix88
{0x0F12, 0x0800 }, //#REG_0TC_CCFG_uMaxBpp88
{0x0F12, 0x0052 }, //#REG_0TC_CCFG_PVIMask
{0x0F12, 0x0000 }, //#REG_0TC_CCFG_OIFMask
//WRITE 70000370 0600 //#REG_0TC_CCFG_usJpegPacketSize
//WRITE 70000372 0400  //08FC //#REG_0TC_CCFG_usJpegTotalPackets
{0x002A, 0x0374 },
{0x0F12, 0x0000 }, //#REG_0TC_CCFG_uClockInd
{0x0F12, 0x0000 }, //#REG_0TC_CCFG_usFrTimeType
{0x0F12, 0x0002 }, //#REG_0TC_CCFG_FrRateQualityType
{0x0F12, 0x0596 }, //#REG_0TC_CCFG_usMaxFrTimeMsecMult10 //7.5fps
{0x0F12, 0x029A }, //#REG_0TC_CCFG_usMinFrTimeMsecMult10 //15fps
{0x0F12, 0x0000 }, //#REG_0TC_CCFG_bSmearOutput
{0x0F12, 0x0000 }, //#REG_0TC_CCFG_sSaturation
{0x0F12, 0x0000 }, //#REG_0TC_CCFG_sSharpBlur
{0x0F12, 0x0000 }, //#REG_0TC_CCFG_sColorTemp
{0x0F12, 0x0000 }, //#REG_0TC_CCFG_uDeviceGammaIndex
              
//================================================================================================
// SET CAPTURE CONFIGURATION_1 (Night Mode)
// # Foramt :JPEG
// # Size: 3M (2048x1536)
// # FPS : 10 ~ 7.5fps
//================================================================================================
{0x002A, 0x038A }, 
{0x0F12, 0x0800 },  //#REG_1TC_CCFG_usWidth
{0x0F12, 0x0600 },  //#REG_1TC_CCFG_usHeight
{0x0F12, 0x0005 },  //#REG_1TC_CCFG_Format
{0x0F12, 0x2EF0 },  //#REG_1TC_CCFG_usMaxOut4KHzRate
{0x0F12, 0x2ED0 },  //#REG_1TC_CCFG_usMinOut4KHzRate
{0x0F12, 0x0100 },  //#REG_1TC_CCFG_OutClkPerPix88
{0x0F12, 0x0800 },  //#REG_1TC_CCFG_uMaxBpp88
{0x0F12, 0x0052 },  //#REG_1TC_CCFG_PVIMask
{0x0F12, 0x0000 },  //#REG_1TC_CCFG_OIFMask
{0x002A, 0x03A0 },  //#REG_1TC_CCFG_usJpegTotalPackets
{0x0F12, 0x0000 },  //#REG_1TC_CCFG_uClockInd
{0x0F12, 0x0000 },  //#REG_1TC_CCFG_usFrTimeType
{0x0F12, 0x0002 },  //#REG_1TC_CCFG_FrRateQualityType
{0x0F12, 0x07d0 },  //#REG_1TC_CCFG_usMaxFrTimeMsecMult10
{0x0F12, 0x07d0 },  //#REG_1TC_CCFG_usMinFrTimeMsecMult10

//================================================================================================
// SET JPEG & SPOOF
//================================================================================================
{0x002A, 0x0454 },
{0x0F12, 0x0055 }, // #REG_TC_BRC_usCaptureQuality // JPEG BRC (BitRateControl) value // 85
//WRITE D000007A         0A02     // JPEG CLK off
//WRITE 70000450  0001  //#BRC_BRC_Type // JPEG inspection off

//================================================================================================
// SET THUMBNAIL
// # Foramt : RGB565
// # Size: VGA
//================================================================================================
{0x0F12, 0x0000 }, //0001 // thumbnail disable
{0x0F12, 0x0140 }, // Width//320 //640
{0x0F12, 0x00F0 }, // Height //240 //480
{0x0F12, 0x0000 }, // Thumbnail format : 0RGB565 1 RGB888 2 Full-YUV (0-255)
              

             
// Fill RAM wi },th alternative op-codes
{0x002A, 0x2CE8 },
{0x0F12, 0x0007 }, // Modify LSB to control AWBB_YThreshLow
{0x0F12, 0x00E2 }, //
{0x0F12, 0x0005 }, // Modify LSB to control AWBB_YThreshLowBrLow
{0x0F12, 0x00E2 }, //
             
/////////////////////////////////////////////////////////////////////////
// AFC - fix i },f ( G_AFC_Confidence[G_AFC_SuspectedState] > AFC_CONFIDENCE_HIGH_THR ) condition to if ( G_AFC_Confidence[G_AFC_SuspectedState] > (10<<10) )
// Fill RAM wi },th alternative op-codes
{0x002A, 0x2CE6 },
{0x0F12, 0x220A }, //  3 ==> A Modify AFC_CONFIDENCE_HIGH_THR
{0x002A, 0x3378 },
{0x0F12, 0x0034 }, //#Tune_TP_AFC_SCD_Thresh ==> Set > 0 to activate the SCD T&P code for AFC.
             
{0x002A, 0x10E2 },
{0x0F12, 0x00C0 }, // 192, decay factor (using af_search_usCapturePolicy) ==> change to 230 ??
{0x002A, 0x10E0 },
{0x0F12, 0x0006 }, // 8 frames wait for scene stable (using M_af_search_usFineMaxScale) ==> can vary between 4..10
             
// force zeroing of "G_AFC_Conf50_VerySlow" and "G_AFC_Conf60_VerySlow", (using M_af_stat_usG2)
             
{0x002A, 0x0C1E },
{0x0F12, 0x0016 }, // change "alpha" parameter from "0x10" to "0x16"
/////////////////////////////////////////////////////////////////////////
             
{0x0028, 0xD000 },
{0x002A, 0x1000 },
{0x0F12, 0x0001 },              




