let DCSMRegisters = [
	{ name: "B0_Z1OTP_LINKPOINTER1", description: "Zone 1 Link Pointer1 in Z1 OTP for flash BANK0", offset: "0x0",
		bits: [
		]
	},
	{ name: "B0_Z1OTP_LINKPOINTER2", description: "Zone 1 Link Pointer2 in Z1 OTP for flash BANK0", offset: "0x4",
		bits: [
		]
	},
	{ name: "B0_Z1OTP_LINKPOINTER3", description: "Zone 1 Link Pointer3 in Z1 OTP for flash BANK0", offset: "0x8",
		bits: [
		]
	},
	{ name: "Z1OTP_BOOTPIN_CONFIG", description: "Boot Pin Configuration", offset: "0xC",
		bits: [
		]
	},
	{ name: "Z1OTP_GPREG2", description: "Zone-1 General Purpose Register-2 content", offset: "0xE",
		bits: [
		]
	},
	{ name: "Z1OTP_PSWDLOCK", description: "Secure Password Lock in Z1 OTP", offset: "0x10",
		bits: [
		]
	},
	{ name: "Z1OTP_CRCLOCK", description: "Secure CRC Lock in Z1 OTP", offset: "0x14",
		bits: [
		]
	},
	{ name: "Z1OTP_BOOTDEF_LOW", description: "Boot definition (low 32bit)", offset: "0x1C",
		bits: [
		]
	},
	{ name: "Z1OTP_BOOTDEF_HIGH", description: "Boot definition (high 32bit)", offset: "0x1E",
		bits: [
		]
	},
	{ name: "B0_Z2OTP_LINKPOINTER1", description: "Zone 2Link Pointer1 in Z2 OTP for flash BANK0", offset: "0x0",
		bits: [
		]
	},
	{ name: "B0_Z2OTP_LINKPOINTER2", description: "Zone 2 Link Pointer2 in Z2 OTP for flash BANK0", offset: "0x4",
		bits: [
		]
	},
	{ name: "B0_Z2OTP_LINKPOINTER3", description: "Zone 12Link Pointer3 in Z2 OTP for flash BANK0", offset: "0x8",
		bits: [
		]
	},
	{ name: "Z2OTP_PSWDLOCK", description: "Secure Password Lock in Z2 OTP", offset: "0x10",
		bits: [
		]
	},
	{ name: "Z2OTP_CRCLOCK", description: "Secure CRC Lock in Z2 OTP", offset: "0x14",
		bits: [
		]
	},
	{ name: "B0_Z1_LINKPOINTER", description: "Zone 1 Link Pointer for flash BANK0", offset: "0x0",
		bits: [
			{ name: "LINKPOINTER", description: "Zone1 LINK Pointer for zone Flash", size: "29", shift: "0", mask: "0x1FFFFFFF" },
		]
	},
	{ name: "Z1_OTPSECLOCK", description: "Zone 1 OTP Secure JTAG lock", offset: "0x2",
		bits: [
			{ name: "PSWDLOCK", description: "Zone1 Password Lock.", size: "4", shift: "4", mask: "0xF0" },
			{ name: "CRCLOCK", description: "Zone1 CRC Lock.", size: "4", shift: "8", mask: "0xF00" },
		]
	},
	{ name: "Z1_BOOTDEF_HIGH", description: "Boot definition (high 32bit)", offset: "0x4",
		bits: [
		]
	},
	{ name: "B0_Z1_LINKPOINTERERR", description: "Link Pointer Error for flash BANK0", offset: "0x6",
		bits: [
			{ name: "Z1_LINKPOINTERERR", description: "Error to Resolve Z1 Link", size: "29", shift: "0", mask: "0x1FFFFFFF" },
		]
	},
	{ name: "Z1_BOOTPIN_CONFIG", description: "Boot Pin Configuration", offset: "0x8",
		bits: [
		]
	},
	{ name: "Z1_GPREG2", description: "Zone1 General Purpose Register-2", offset: "0xA",
		bits: [
		]
	},
	{ name: "Z1_BOOTDEF_LOW", description: "Boot definition (low 32bit)", offset: "0xC",
		bits: [
		]
	},
	{ name: "Z1_CSMKEY0", description: "Zone 1 CSM Key 0", offset: "0x10",
		bits: [
		]
	},
	{ name: "Z1_CSMKEY1", description: "Zone 1 CSM Key 1", offset: "0x12",
		bits: [
		]
	},
	{ name: "Z1_CSMKEY2", description: "Zone 1 CSM Key 2", offset: "0x14",
		bits: [
		]
	},
	{ name: "Z1_CSMKEY3", description: "Zone 1 CSM Key 3", offset: "0x16",
		bits: [
		]
	},
	{ name: "Z1_CR", description: "Zone 1 CSM Control Register", offset: "0x19",
		bits: [
			{ name: "ALLZERO", description: "CSMPSWD All Zeros", size: "1", shift: "3", mask: "0x8" },
			{ name: "ALLONE", description: "CSMPSWD All Ones", size: "1", shift: "4", mask: "0x10" },
			{ name: "UNSECURE", description: "CSMPSWD Match CSMKEY", size: "1", shift: "5", mask: "0x20" },
			{ name: "ARMED", description: "CSM Passwords Read Status", size: "1", shift: "6", mask: "0x40" },
			{ name: "FORCESEC", description: "Force Secure", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "B0_Z1_GRABSECTR", description: "Zone 1 Grab Flash BANK0 Sectors Register", offset: "0x1A",
		bits: [
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0 in BANK0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1 in BANK0", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2 in BANK0", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3 in BANK0", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4 in BANK0", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5 in BANK0", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6 in BANK0", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7 in BANK0", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8 in BANK0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9 in BANK0", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10 in BANK0", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11 in BANK0", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12 in BANK0", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13 in BANK0", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_SECT14", description: "Grab Flash Sector 14 in BANK0", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_SECT15", description: "Grab Flash Sector 15 in BANK0", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z1_GRABRAMR", description: "Zone 1 Grab RAM Blocks Register", offset: "0x1C",
		bits: [
			{ name: "GRAB_RAM0", description: "Grab RAM LS0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM1", description: "Grab RAM LS1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM2", description: "Grab RAM LS2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_RAM3", description: "Grab RAM LS3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_RAM4", description: "Grab RAM LS4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_RAM5", description: "Grab RAM LS5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_RAM6", description: "Grab RAM LS6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM LS7", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "B0_Z1_EXEONLYSECTR", description: "Zone 1 Flash BANK0 Execute_Only Sector Register", offset: "0x1E",
		bits: [
			{ name: "EXEONLY_SECT0", description: "Execute-Only Flash Sector 0 in Flash", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_SECT1", description: "Execute-Only Flash Sector 1 in Flash", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_SECT2", description: "Execute-Only Flash Sector 2 in Flash", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_SECT3", description: "Execute-Only Flash Sector 3 in Flash", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_SECT4", description: "Execute-Only Flash Sector 4 in Flash", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_SECT5", description: "Execute-Only Flash Sector 5 in Flash", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_SECT6", description: "Execute-Only Flash Sector 6 in Flash", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_SECT7", description: "Execute-Only Flash Sector 7 in Flash", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_SECT8", description: "Execute-Only Flash Sector 8 in Flash", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_SECT9", description: "Execute-Only Flash Sector 9 in Flash", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_SECT10", description: "Execute-Only Flash Sector 10 in Flash", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_SECT11", description: "Execute-Only Flash Sector 11 in Flash", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_SECT12", description: "Execute-Only Flash Sector 12 in Flash", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_SECT13", description: "Execute-Only Flash Sector 13 in Flash", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_SECT14", description: "Execute-Only Flash Sector 14 in Flash", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_SECT15", description: "Execute-Only Flash Sector 15 in Flash", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "Z1_EXEONLYRAMR", description: "Zone 1 RAM Execute_Only Block Register", offset: "0x20",
		bits: [
			{ name: "EXEONLY_RAM0", description: "Execute-Only RAM LS0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_RAM1", description: "Execute-Only RAM LS1", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_RAM2", description: "Execute-Only RAM LS2", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_RAM3", description: "Execute-Only RAM LS3", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_RAM4", description: "Execute-Only RAM LS4", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_RAM5", description: "Execute-Only RAM LS5", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_RAM6", description: "Execute-Only RAM LS6", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_RAM7", description: "Execute-Only RAM LS7", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "B0_Z2_LINKPOINTER", description: "Zone 2 Link Pointer for flash BANK0", offset: "0x0",
		bits: [
			{ name: "LINKPOINTER", description: "Zone2 LINK Pointer in Flash BANK0", size: "29", shift: "0", mask: "0x1FFFFFFF" },
		]
	},
	{ name: "Z2_OTPSECLOCK", description: "Zone 2 OTP Secure JTAG lock", offset: "0x2",
		bits: [
			{ name: "PSWDLOCK", description: "Zone2 Password Lock.", size: "4", shift: "4", mask: "0xF0" },
			{ name: "CRCLOCK", description: "Zone2 CRC Lock.", size: "4", shift: "8", mask: "0xF00" },
		]
	},
	{ name: "B0_Z2_LINKPOINTERERR", description: "Link Pointer Error for flash BANK0", offset: "0x6",
		bits: [
			{ name: "Z2_LINKPOINTERERR", description: "Error to Resolve Z2 Link", size: "29", shift: "0", mask: "0x1FFFFFFF" },
		]
	},
	{ name: "Z2_CSMKEY0", description: "Zone 2 CSM Key 0", offset: "0x10",
		bits: [
		]
	},
	{ name: "Z2_CSMKEY1", description: "Zone 2 CSM Key 1", offset: "0x12",
		bits: [
		]
	},
	{ name: "Z2_CSMKEY2", description: "Zone 2 CSM Key 2", offset: "0x14",
		bits: [
		]
	},
	{ name: "Z2_CSMKEY3", description: "Zone 2 CSM Key 3", offset: "0x16",
		bits: [
		]
	},
	{ name: "Z2_CR", description: "Zone 2 CSM Control Register", offset: "0x19",
		bits: [
			{ name: "ALLZERO", description: "CSMPSWD All Zeros", size: "1", shift: "3", mask: "0x8" },
			{ name: "ALLONE", description: "CSMPSWD All Ones", size: "1", shift: "4", mask: "0x10" },
			{ name: "UNSECURE", description: "CSMPSWD Match CSMKEY", size: "1", shift: "5", mask: "0x20" },
			{ name: "ARMED", description: "CSM Passwords Read Status", size: "1", shift: "6", mask: "0x40" },
			{ name: "FORCESEC", description: "Force Secure", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "B0_Z2_GRABSECTR", description: "Zone 2 Grab Flash BANK0 Sectors Register", offset: "0x1A",
		bits: [
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0 in Flash BANK0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1 in Flash BANK0", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2 in Flash BANK0", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3 in Flash BANK0", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4 in Flash BANK0", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5 in Flash BANK0", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6 in Flash BANK0", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7 in Flash BANK0", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8 in Flash BANK0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9 in Flash BANK0", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10 in Flash BANK0", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11 in Flash BANK0", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12 in Flash BANK0", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13 in Flash BANK0", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_SECT14", description: "Grab Flash Sector 14 in Flash BANK0", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_SECT15", description: "Grab Flash Sector 15 in Flash BANK0", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z2_GRABRAMR", description: "Zone 2 Grab RAM Blocks Register", offset: "0x1C",
		bits: [
			{ name: "GRAB_RAM0", description: "Grab RAM LS0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM1", description: "Grab RAM LS1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM2", description: "Grab RAM LS2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_RAM3", description: "Grab RAM LS3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_RAM4", description: "Grab RAM LS4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_RAM5", description: "Grab RAM LS5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_RAM6", description: "Grab RAM LS6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM LS7", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "B0_Z2_EXEONLYSECTR", description: "Zone 2 Flash BANK0 Execute_Only Sector Register", offset: "0x1E",
		bits: [
			{ name: "EXEONLY_SECT0", description: "Execute-Only Flash Sector 0 in Flash", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_SECT1", description: "Execute-Only Flash Sector 1 in Flash", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_SECT2", description: "Execute-Only Flash Sector 2 in Flash", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_SECT3", description: "Execute-Only Flash Sector 3 in Flash", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_SECT4", description: "Execute-Only Flash Sector 4 in Flash", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_SECT5", description: "Execute-Only Flash Sector 5 in Flash", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_SECT6", description: "Execute-Only Flash Sector 6 in Flash", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_SECT7", description: "Execute-Only Flash Sector 7 in Flash", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_SECT8", description: "Execute-Only Flash Sector 8 in Flash", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_SECT9", description: "Execute-Only Flash Sector 9 in Flash", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_SECT10", description: "Execute-Only Flash Sector 10 in Flash", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_SECT11", description: "Execute-Only Flash Sector 11 in Flash", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_SECT12", description: "Execute-Only Flash Sector 12 in Flash", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_SECT13", description: "Execute-Only Flash Sector 13 in Flash", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_SECT14", description: "Execute-Only Flash Sector 14 in Flash", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_SECT15", description: "Execute-Only Flash Sector 15 in Flash", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "Z2_EXEONLYRAMR", description: "Zone 2 RAM Execute_Only Block Register", offset: "0x20",
		bits: [
			{ name: "EXEONLY_RAM0", description: "Execute-Only RAM LS0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_RAM1", description: "Execute-Only RAM LS1", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_RAM2", description: "Execute-Only RAM LS2", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_RAM3", description: "Execute-Only RAM LS3", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_RAM4", description: "Execute-Only RAM LS4", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_RAM5", description: "Execute-Only RAM LS5", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_RAM6", description: "Execute-Only RAM LS6", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_RAM7", description: "Execute-Only RAM LS7", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "FLSEM", description: "Flash Wrapper Semaphore Register", offset: "0x0",
		bits: [
			{ name: "SEM", description: "Flash Semaphore Bit", size: "2", shift: "0", mask: "0x3" },
			{ name: "KEY", description: "Semaphore Key", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "B0_SECTSTAT", description: "Flash BANK0 Sectors Status Register", offset: "0x2",
		bits: [
			{ name: "STATUS_SECT0", description: "Zone Status Flash BANK0 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_SECT1", description: "Zone Status Flash BANK0 sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_SECT2", description: "Zone Status Flash BANK0 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_SECT3", description: "Zone Status Flash BANK0 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_SECT4", description: "Zone Status Flash BANK0 Sector 4", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_SECT5", description: "Zone Status Flash BANK0 Sector 5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_SECT6", description: "Zone Status Flash BANK0 Sector 6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_SECT7", description: "Zone Status Flash BANK0 Sector 7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_SECT8", description: "Zone Status Flash BANK0 sector 8", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_SECT9", description: "Zone Status Flash BANK0 Sector 9", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_SECT10", description: "Zone Status Flash BANK0 Sector 10", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_SECT11", description: "Zone Status Flash BANK0 Sector 11", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_SECT12", description: "Zone Status Flash BANK0 Sector 12", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_SECT13", description: "Zone Status Flash BANK0 Sector 13", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "STATUS_SECT14", description: "Zone Status Flash BANK0 Sector 14", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "STATUS_SECT15", description: "Zone Status Flash BANK0 Sector 15", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "RAMSTAT", description: "RAM Status Register", offset: "0x4",
		bits: [
			{ name: "STATUS_RAM0", description: "Zone Status RAM LS0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_RAM1", description: "Zone Status RAM LS1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_RAM2", description: "Zone Status RAM LS2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_RAM3", description: "Zone Status RAM LS3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_RAM4", description: "Zone Status RAM LS4", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_RAM5", description: "Zone Status RAM LS5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_RAM6", description: "Zone Status RAM LS6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_RAM7", description: "Zone Status RAM LS7", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "B1_SECTSTAT", description: "Flash BANK1 Sectors Status Register", offset: "0x8",
		bits: [
			{ name: "STATUS_SECT0", description: "Zone Status Flash BANK1 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_SECT1", description: "Zone Status Flash BANK1 sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_SECT2", description: "Zone Status Flash BANK1 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_SECT3", description: "Zone Status Flash BANK1 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_SECT4", description: "Zone Status Flash BANK1 Sector 4", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_SECT5", description: "Zone Status Flash BANK1 Sector 5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_SECT6", description: "Zone Status Flash BANK1 Sector 6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_SECT7", description: "Zone Status Flash BANK1 Sector 7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_SECT8", description: "Zone Status Flash BANK1 sector 8", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_SECT9", description: "Zone Status Flash BANK1 Sector 9", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_SECT10", description: "Zone Status Flash BANK1 Sector 10", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_SECT11", description: "Zone Status Flash BANK1 Sector 11", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_SECT12", description: "Zone Status Flash BANK1 Sector 12", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_SECT13", description: "Zone Status Flash BANK1 Sector 13", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "STATUS_SECT14", description: "Zone Status Flash BANK1 Sector 14", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "STATUS_SECT15", description: "Zone Status Flash BANK1 Sector 15", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "SECERRSTAT", description: "Security Error Status Register", offset: "0xA",
		bits: [
			{ name: "ERR", description: "Security Configuration load Error Status", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SECERRCLR", description: "Security Error Clear Register", offset: "0xC",
		bits: [
			{ name: "ERR", description: "Clear Security Configuration Load Error Status Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SECERRFRC", description: "Security Error Force Register", offset: "0xE",
		bits: [
			{ name: "ERR", description: "Set Security Configuration Load Error Status Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "B1_Z1OTP_LINKPOINTER1", description: "Zone 1 Link Pointer1 in Z1 OTP for flash BANK1", offset: "0x0",
		bits: [
		]
	},
	{ name: "B1_Z1OTP_LINKPOINTER2", description: "Zone 1 Link Pointer2 in Z1 OTP for flash BANK1", offset: "0x4",
		bits: [
		]
	},
	{ name: "B1_Z1OTP_LINKPOINTER3", description: "Zone 1 Link Pointer3 in Z1 OTP for flash BANK1", offset: "0x8",
		bits: [
		]
	},
	{ name: "B1_Z2OTP_LINKPOINTER1", description: "Zone 2 Link Pointer1 in Z2 OTP for flash BANK1", offset: "0x0",
		bits: [
		]
	},
	{ name: "B1_Z2OTP_LINKPOINTER2", description: "Zone 2 Link Pointer2 in Z2 OTP for flash BANK1", offset: "0x4",
		bits: [
		]
	},
	{ name: "B1_Z2OTP_LINKPOINTER3", description: "Zone 2 Link Pointer3 in Z2 OTP for flash BANK1", offset: "0x8",
		bits: [
		]
	},
	{ name: "B1_Z1_LINKPOINTER", description: "Zone 1 Link Pointer for flash BANK1", offset: "0x0",
		bits: [
			{ name: "LINKPOINTER", description: "Zone1 LINK Pointer in Flash BANK1", size: "29", shift: "0", mask: "0x1FFFFFFF" },
		]
	},
	{ name: "B1_Z1_LINKPOINTERERR", description: "Link Pointer Error for flash BANK1", offset: "0x6",
		bits: [
			{ name: "Z1_LINKPOINTERERR", description: "Error to Resolve Z1 Link", size: "29", shift: "0", mask: "0x1FFFFFFF" },
		]
	},
	{ name: "B1_Z1_GRABSECTR", description: "Zone 1 Grab Flash BANK1 Sectors Register", offset: "0x1A",
		bits: [
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0 in BANK1", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1 in BANK1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2 in BANK1", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3 in BANK1", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4 in BANK1", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5 in BANK1", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6 in BANK1", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7 in BANK1", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8 in BANK1", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9 in BANK1", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10 in BANK1", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11 in BANK1", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12 in BANK1", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13 in BANK1", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_SECT14", description: "Grab Flash Sector 14 in BANK1", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_SECT15", description: "Grab Flash Sector 15 in BANK1", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "B1_Z1_EXEONLYSECTR", description: "Zone 1 Flash BANK1 Execute_Only Sector Register", offset: "0x1E",
		bits: [
			{ name: "EXEONLY_SECT0", description: "Execute-Only Flash Sector 0 in Flash", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_SECT1", description: "Execute-Only Flash Sector 1 in Flash", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_SECT2", description: "Execute-Only Flash Sector 2 in Flash", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_SECT3", description: "Execute-Only Flash Sector 3 in Flash", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_SECT4", description: "Execute-Only Flash Sector 4 in Flash", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_SECT5", description: "Execute-Only Flash Sector 5 in Flash", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_SECT6", description: "Execute-Only Flash Sector 6 in Flash", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_SECT7", description: "Execute-Only Flash Sector 7 in Flash", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_SECT8", description: "Execute-Only Flash Sector 8 in Flash", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_SECT9", description: "Execute-Only Flash Sector 9 in Flash", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_SECT10", description: "Execute-Only Flash Sector 10 in Flash", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_SECT11", description: "Execute-Only Flash Sector 11 in Flash", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_SECT12", description: "Execute-Only Flash Sector 12 in Flash", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_SECT13", description: "Execute-Only Flash Sector 13 in Flash", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_SECT14", description: "Execute-Only Flash Sector 14 in Flash", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_SECT15", description: "Execute-Only Flash Sector 15 in Flash", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "B1_Z2_LINKPOINTER", description: "Zone 2 Link Pointer for flash BANK1", offset: "0x0",
		bits: [
			{ name: "LINKPOINTER", description: "Zone2 LINK Pointer in Flash BANK1", size: "29", shift: "0", mask: "0x1FFFFFFF" },
		]
	},
	{ name: "B1_Z2_LINKPOINTERERR", description: "Link Pointer Error for flash BANK1", offset: "0x6",
		bits: [
			{ name: "Z2_LINKPOINTERERR", description: "Error to Resolve Z2 Link", size: "29", shift: "0", mask: "0x1FFFFFFF" },
		]
	},
	{ name: "B1_Z2_GRABSECTR", description: "Zone 2 Grab Flash BANK1 Sectors Register", offset: "0x1A",
		bits: [
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0 in Flash BANK1", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1 in Flash BANK1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2 in Flash BANK1", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3 in Flash BANK1", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4 in Flash BANK1", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5 in Flash BANK1", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6 in Flash BANK1", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7 in Flash BANK1", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8 in Flash BANK1", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9 in Flash BANK1", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10 in Flash BANK1", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11 in Flash BANK1", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12 in Flash BANK1", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13 in Flash BANK1", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_SECT14", description: "Grab Flash Sector 14 in Flash BANK1", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_SECT15", description: "Grab Flash Sector 15 in Flash BANK1", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "B1_Z2_EXEONLYSECTR", description: "Zone 2 Flash BANK1 Execute_Only Sector Register", offset: "0x1E",
		bits: [
			{ name: "EXEONLY_SECT0", description: "Execute-Only Flash Sector 0 in Flash", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_SECT1", description: "Execute-Only Flash Sector 1 in Flash", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_SECT2", description: "Execute-Only Flash Sector 2 in Flash", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_SECT3", description: "Execute-Only Flash Sector 3 in Flash", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_SECT4", description: "Execute-Only Flash Sector 4 in Flash", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_SECT5", description: "Execute-Only Flash Sector 5 in Flash", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_SECT6", description: "Execute-Only Flash Sector 6 in Flash", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_SECT7", description: "Execute-Only Flash Sector 7 in Flash", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_SECT8", description: "Execute-Only Flash Sector 8 in Flash", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_SECT9", description: "Execute-Only Flash Sector 9 in Flash", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_SECT10", description: "Execute-Only Flash Sector 10 in Flash", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_SECT11", description: "Execute-Only Flash Sector 11 in Flash", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_SECT12", description: "Execute-Only Flash Sector 12 in Flash", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_SECT13", description: "Execute-Only Flash Sector 13 in Flash", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_SECT14", description: "Execute-Only Flash Sector 14 in Flash", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_SECT15", description: "Execute-Only Flash Sector 15 in Flash", size: "1", shift: "15", mask: "0x8000" },
		]
	},
];
module.exports = {
	DCSMRegisters: DCSMRegisters,
}
