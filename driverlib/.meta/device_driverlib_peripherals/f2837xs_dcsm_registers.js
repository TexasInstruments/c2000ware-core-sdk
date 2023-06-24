let DCSMRegisters = [
	{ name: "Z1OTP_LINKPOINTER1", description: "Zone 1 Link Pointer1 in Z1 OTP", offset: "0x0",
		bits: [
		]
	},
	{ name: "Z1OTP_LINKPOINTER2", description: "Zone 1 Link Pointer2 in Z1 OTP", offset: "0x4",
		bits: [
		]
	},
	{ name: "Z1OTP_LINKPOINTER3", description: "Zone 1 Link Pointer3 in Z1 OTP", offset: "0x8",
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
	{ name: "Z1OTP_BOOTCTRL", description: "Boot Mode in Z1 OTP", offset: "0x1E",
		bits: [
		]
	},
	{ name: "Z2OTP_LINKPOINTER1", description: "Zone 2 Link Pointer1 in Z2 OTP", offset: "0x0",
		bits: [
		]
	},
	{ name: "Z2OTP_LINKPOINTER2", description: "Zone 2 Link Pointer2 in Z2 OTP", offset: "0x4",
		bits: [
		]
	},
	{ name: "Z2OTP_LINKPOINTER3", description: "Zone 2 Link Pointer3 in Z2 OTP", offset: "0x8",
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
	{ name: "Z2OTP_BOOTCTRL", description: "Boot Mode in Z2 OTP", offset: "0x1E",
		bits: [
		]
	},
	{ name: "Z1_LINKPOINTER", description: "Zone 1 Link Pointer", offset: "0x0",
		bits: [
			{ name: "LINKPOINTER", description: "Zone1 LINK Pointer.", size: "29", shift: "0", mask: "0x1FFFFFFF" },
		]
	},
	{ name: "Z1_OTPSECLOCK", description: "Zone 1 OTP Secure JTAG lock", offset: "0x2",
		bits: [
			{ name: "PSWDLOCK", description: "Zone1 Password Lock.", size: "4", shift: "4", mask: "0xF0" },
			{ name: "CRCLOCK", description: "Zone1 CRC Lock.", size: "4", shift: "8", mask: "0xF00" },
		]
	},
	{ name: "Z1_BOOTCTRL", description: "Boot Mode", offset: "0x4",
		bits: [
			{ name: "KEY", description: "OTP Boot Key", size: "8", shift: "0", mask: "0xFF" },
			{ name: "BMODE", description: "OTP Boot Mode", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "BOOTPIN0", description: "OTP Boot Pin 0 Mapping", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "BOOTPIN1", description: "OTP Boot Pin 1 Mapping", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "Z1_LINKPOINTERERR", description: "Link Pointer Error", offset: "0x6",
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
			{ name: "ARMED", description: "CSM Armed", size: "1", shift: "6", mask: "0x40" },
			{ name: "FORCESEC", description: "Force Secure", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "Z1_GRABSECTR", description: "Zone 1 Grab Flash Sectors Register", offset: "0x1A",
		bits: [
			{ name: "GRAB_SECTA", description: "Grab Flash Sector A", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECTB", description: "Grab Flash Sector B", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECTC", description: "Grab Flash Sector C", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECTD", description: "Grab Flash Sector D", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECTE", description: "Grab Flash Sector E", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECTF", description: "Grab Flash Sector F", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECTG", description: "Grab Flash Sector G", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECTH", description: "Grab Flash Sector H", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECTI", description: "Grab Flash Sector I", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECTJ", description: "Grab Flash Sector J", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECTK", description: "Grab Flash Sector K", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECTL", description: "Grab Flash Sector L", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECTM", description: "Grab Flash Sector M", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECTN", description: "Grab Flash Sector N", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_BANK1", description: "Grab BANK1 (all sectors of bank 1)", size: "2", shift: "28", mask: "0x30000000" },
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
			{ name: "GRAB_RAM6", description: "Grab RAM D0", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM D1", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_CLA1", description: "Grab CLA1", size: "2", shift: "28", mask: "0x30000000" },
		]
	},
	{ name: "Z1_EXEONLYSECTR", description: "Zone 1 Flash Execute_Only Sector Register", offset: "0x1E",
		bits: [
			{ name: "EXEONLY_SECTA", description: "Execute-Only Flash Sector A", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_SECTB", description: "Execute-Only Flash Sector B", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_SECTC", description: "Execute-Only Flash Sector C", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_SECTD", description: "Execute-Only Flash Sector D", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_SECTE", description: "Execute-Only Flash Sector E", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_SECTF", description: "Execute-Only Flash Sector F", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_SECTG", description: "Execute-Only Flash Sector G", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_SECTH", description: "Execute-Only Flash Sector H", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_SECTI", description: "Execute-Only Flash Sector I", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_SECTJ", description: "Execute-Only Flash Sector J", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_SECTK", description: "Execute-Only Flash Sector K", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_SECTL", description: "Execute-Only Flash Sector L", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_SECTM", description: "Execute-Only Flash Sector M", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_SECTN", description: "Execute-Only Flash Sector N", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_BANK1", description: "Execute-Only Flash BANK1", size: "1", shift: "14", mask: "0x4000" },
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
			{ name: "EXEONLY_RAM6", description: "Execute-Only RAM D0", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_RAM7", description: "Execute-Only RAM D1", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "Z2_LINKPOINTER", description: "Zone 2 Link Pointer", offset: "0x0",
		bits: [
			{ name: "LINKPOINTER", description: "Zone2 LINK Pointer.", size: "29", shift: "0", mask: "0x1FFFFFFF" },
		]
	},
	{ name: "Z2_OTPSECLOCK", description: "Zone 2 OTP Secure JTAG lock", offset: "0x2",
		bits: [
			{ name: "PSWDLOCK", description: "Zone2 Password Lock.", size: "4", shift: "4", mask: "0xF0" },
			{ name: "CRCLOCK", description: "Zone2 CRC Lock.", size: "4", shift: "8", mask: "0xF00" },
		]
	},
	{ name: "Z2_BOOTCTRL", description: "Boot Mode", offset: "0x4",
		bits: [
			{ name: "KEY", description: "OTP Boot Key", size: "8", shift: "0", mask: "0xFF" },
			{ name: "BMODE", description: "OTP Boot Mode", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "BOOTPIN0", description: "OTP Boot Pin 0 Mapping", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "BOOTPIN1", description: "OTP Boot Pin 1 Mapping", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "Z2_LINKPOINTERERR", description: "Link Pointer Error", offset: "0x6",
		bits: [
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
			{ name: "ARMED", description: "CSM Armed", size: "1", shift: "6", mask: "0x40" },
			{ name: "FORCESEC", description: "Force Secure", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "Z2_GRABSECTR", description: "Zone 2 Grab Flash Sectors Register", offset: "0x1A",
		bits: [
			{ name: "GRAB_SECTA", description: "Grab Flash Sector A", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECTB", description: "Grab Flash Sector B", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECTC", description: "Grab Flash Sector C", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECTD", description: "Grab Flash Sector D", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECTE", description: "Grab Flash Sector E", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECTF", description: "Grab Flash Sector F", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECTG", description: "Grab Flash Sector G", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECTH", description: "Grab Flash Sector H", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECTI", description: "Grab Flash Sector I", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECTJ", description: "Grab Flash Sector J", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECTK", description: "Grab Flash Sector K", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECTL", description: "Grab Flash Sector L", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECTM", description: "Grab Flash Sector M", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECTN", description: "Grab Flash Sector N", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_BANK1", description: "Grab BANK1 (all sectors of bank 1)", size: "2", shift: "28", mask: "0x30000000" },
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
			{ name: "GRAB_RAM6", description: "Grab RAM D0", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM D1", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_CLA1", description: "Grab CLA1", size: "2", shift: "28", mask: "0x30000000" },
		]
	},
	{ name: "Z2_EXEONLYSECTR", description: "Zone 2 Flash Execute_Only Sector Register", offset: "0x1E",
		bits: [
			{ name: "EXEONLY_SECTA", description: "Execute-Only Flash Sector A", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_SECTB", description: "Execute-Only Flash Sector B", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_SECTC", description: "Execute-Only Flash Sector C", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_SECTD", description: "Execute-Only Flash Sector D", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_SECTE", description: "Execute-Only Flash Sector E", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_SECTF", description: "Execute-Only Flash Sector F", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_SECTG", description: "Execute-Only Flash Sector G", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_SECTH", description: "Execute-Only Flash Sector H", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_SECTI", description: "Execute-Only Flash Sector I", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_SECTJ", description: "Execute-Only Flash Sector J", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_SECTK", description: "Execute-Only Flash Sector K", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_SECTL", description: "Execute-Only Flash Sector L", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_SECTM", description: "Execute-Only Flash Sector M", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_SECTN", description: "Execute-Only Flash Sector N", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_BANK1", description: "Execute-Only Flash BANK1", size: "1", shift: "14", mask: "0x4000" },
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
			{ name: "EXEONLY_RAM6", description: "Execute-Only RAM D0", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_RAM7", description: "Execute-Only RAM D1", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "FLSEM", description: "Flash Wrapper Semaphore Register", offset: "0x0",
		bits: [
			{ name: "SEM", description: "Flash Semaphore Bit", size: "2", shift: "0", mask: "0x3" },
			{ name: "KEY", description: "Semaphore Key", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "SECTSTAT", description: "Sectors Status Register", offset: "0x2",
		bits: [
			{ name: "STATUS_SECTA", description: "Zone Status Flash Sector A", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_SECTB", description: "Zone Status Flash Sector B", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_SECTC", description: "Zone Status Flash Sector C", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_SECTD", description: "Zone Status Flash Sector D", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_SECTE", description: "Zone Status Flash Sector E", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_SECTF", description: "Zone Status Flash Sector F", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_SECTG", description: "Zone Status Flash Sector G", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_SECTH", description: "Zone Status Flash Sector H", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_SECTI", description: "Zone Status Flash Sector I", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_SECTJ", description: "Zone Status Flash Sector J", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_SECTK", description: "Zone Status Flash Sector K", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_SECTL", description: "Zone Status Flash Sector L", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_SECTM", description: "Zone Status Flash Sector M", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_SECTN", description: "Zone Status Flash Sector N", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "STATUS_BANK1", description: "Zone Status Flash BANK1", size: "2", shift: "28", mask: "0x30000000" },
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
			{ name: "STATUS_RAM6", description: "Zone Status RAM D0", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_RAM7", description: "Zone Status RAM D1", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_CLA1", description: "Zone Status CLA1", size: "2", shift: "28", mask: "0x30000000" },
		]
	},
];
module.exports = {
	DCSMRegisters: DCSMRegisters,
}
