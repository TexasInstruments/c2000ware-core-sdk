let DCSMRegisters = [
	{ name: "Z1OTP_LINKPOINTER1", description: "Zone 1 Link Pointer1", offset: "0x0",
		bits: [
		]
	},
	{ name: "Z1OTP_LINKPOINTER2", description: "Zone 1 Link Pointer2", offset: "0x2",
		bits: [
		]
	},
	{ name: "Z1OTP_LINKPOINTER3", description: "Zone 1 Link Pointer3", offset: "0x4",
		bits: [
		]
	},
	{ name: "Z1OTP_JLM_ENABLE", description: "Zone 1 JTAGLOCK Enable Register", offset: "0x6",
		bits: [
		]
	},
	{ name: "Z1OTP_GPREG1", description: "Zone 1 General Purpose Register 1", offset: "0x8",
		bits: [
		]
	},
	{ name: "Z1OTP_GPREG2", description: "Zone 1 General Purpose Register 2", offset: "0xA",
		bits: [
		]
	},
	{ name: "Z1OTP_GPREG3", description: "Zone 1 General Purpose Register 3", offset: "0xC",
		bits: [
		]
	},
	{ name: "Z1OTP_GPREG4", description: "Zone 1 General Purpose Register 4", offset: "0xE",
		bits: [
		]
	},
	{ name: "Z1OTP_PSWDLOCK", description: "Secure Password Lock", offset: "0x10",
		bits: [
		]
	},
	{ name: "Z1OTP_JTAGPSWDH0", description: "JTAG Lock Permanent Password 0", offset: "0x14",
		bits: [
		]
	},
	{ name: "Z1OTP_JTAGPSWDH1", description: "JTAG Lock Permanent Password 1", offset: "0x16",
		bits: [
		]
	},
	{ name: "Z1OTP_CMACKEY0", description: "Secure Boot CMAC Key 0", offset: "0x18",
		bits: [
		]
	},
	{ name: "Z1OTP_CMACKEY1", description: "Secure Boot CMAC Key 1", offset: "0x1A",
		bits: [
		]
	},
	{ name: "Z1OTP_CMACKEY2", description: "Secure Boot CMAC Key 2", offset: "0x1C",
		bits: [
		]
	},
	{ name: "Z1OTP_CMACKEY3", description: "Secure Boot CMAC Key 3", offset: "0x1E",
		bits: [
		]
	},
	{ name: "Z2OTP_LINKPOINTER1", description: "Zone 2 Link Pointer1", offset: "0x0",
		bits: [
		]
	},
	{ name: "Z2OTP_LINKPOINTER2", description: "Zone 2 Link Pointer2", offset: "0x2",
		bits: [
		]
	},
	{ name: "Z2OTP_LINKPOINTER3", description: "Zone 2 Link Pointer3", offset: "0x4",
		bits: [
		]
	},
	{ name: "Z2OTP_GPREG1", description: "Zone 2 General Purpose Register 1", offset: "0x8",
		bits: [
		]
	},
	{ name: "Z2OTP_GPREG2", description: "Zone 2 General Purpose Register 2", offset: "0xA",
		bits: [
		]
	},
	{ name: "Z2OTP_GPREG3", description: "Zone 2 General Purpose Register 3", offset: "0xC",
		bits: [
		]
	},
	{ name: "Z2OTP_GPREG4", description: "Zone 2 General Purpose Register 4", offset: "0xE",
		bits: [
		]
	},
	{ name: "Z2OTP_PSWDLOCK", description: "Secure Password Lock", offset: "0x10",
		bits: [
		]
	},
	{ name: "Z1_LINKPOINTER", description: "Zone 1 Link Pointer", offset: "0x0",
		bits: [
			{ name: "LINKPOINTER", description: "Zone1 LINK Pointer", size: "14", shift: "0", mask: "0x3FFF" },
		]
	},
	{ name: "Z1_OTPSECLOCK", description: "Zone 1 OTP Secure Lock", offset: "0x2",
		bits: [
			{ name: "JTAGLOCK", description: "JTAG Lock Status", size: "1", shift: "0", mask: "0x1" },
			{ name: "PSWDLOCK", description: "Zone1 Password Lock.", size: "4", shift: "4", mask: "0xF0" },
		]
	},
	{ name: "Z1_JLM_ENABLE", description: "Zone 1 JTAGLOCK Enable Register", offset: "0x4",
		bits: [
			{ name: "Z1_JLM_ENABLE", description: "Zone1 JLM_ENABLE register.", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "Z1_LINKPOINTERERR", description: "Link Pointer Error", offset: "0x6",
		bits: [
			{ name: "Z1_LINKPOINTERERR", description: "Error to Resolve Z1 Link pointer", size: "14", shift: "0", mask: "0x3FFF" },
		]
	},
	{ name: "Z1_GPREG1", description: "Zone 1 General Purpose Register-1", offset: "0x8",
		bits: [
		]
	},
	{ name: "Z1_GPREG2", description: "Zone 1 General Purpose Register-2", offset: "0xA",
		bits: [
		]
	},
	{ name: "Z1_GPREG3", description: "Zone 1 General Purpose Register-3", offset: "0xC",
		bits: [
		]
	},
	{ name: "Z1_GPREG4", description: "Zone 1 General Purpose Register-4", offset: "0xE",
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
	{ name: "Z1_CR", description: "Zone 1 CSM Control Register", offset: "0x18",
		bits: [
			{ name: "ALLZERO", description: "CSMPSWD All Zeros", size: "1", shift: "19", mask: "0x80000" },
			{ name: "ALLONE", description: "CSMPSWD All Ones", size: "1", shift: "20", mask: "0x100000" },
			{ name: "UNSECURE", description: "CSMPSWD Match CSMKEY", size: "1", shift: "21", mask: "0x200000" },
			{ name: "ARMED", description: "CSM Passwords Read Status", size: "1", shift: "22", mask: "0x400000" },
			{ name: "FORCESEC", description: "Force Secure", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "Z1_GRABSECT1R", description: "Zone 1 Grab Flash Status Register 1", offset: "0x1A",
		bits: [
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_SECT14", description: "Grab Flash Sector 14", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_SECT15", description: "Grab Flash Sector 15", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z1_GRABSECT2R", description: "Zone 1 Grab Flash Status Register 2", offset: "0x1C",
		bits: [
			{ name: "GRAB_SECT16", description: "Grab Flash Sector 16", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT17", description: "Grab Flash Sector 17", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT18", description: "Grab Flash Sector 18", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT19", description: "Grab Flash Sector 19", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT20", description: "Grab Flash Sector 20", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT21", description: "Grab Flash Sector 21", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT22", description: "Grab Flash Sector 22", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT23", description: "Grab Flash Sector 23", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT24", description: "Grab Flash Sector 24", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT25", description: "Grab Flash Sector 25", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT26", description: "Grab Flash Sector 26", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT27", description: "Grab Flash Sector 27", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT28", description: "Grab Flash Sector 28", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT29", description: "Grab Flash Sector 29", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_SECT30", description: "Grab Flash Sector 30", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_SECT31", description: "Grab Flash Sector 31", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z1_GRABSECT3R", description: "Zone 1 Grab Flash Status Register 3", offset: "0x1E",
		bits: [
			{ name: "GRAB_SECT39_32", description: "Grab Flash Sectors 39-32", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT47_40", description: "Grab Flash Sectors 47-40", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT55_48", description: "Grab Flash Sectors 55-48", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT63_56", description: "Grab Flash Sectors 63-56", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT71_64", description: "Grab Flash Sectors 71_64", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT79_72", description: "Grab Flash Sectors 79-72", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT87_80", description: "Grab Flash Sectors 87-80", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT95_88", description: "Grab Flash Sectors 95-88", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT103_96", description: "Grab Flash Sectors 103-96", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT111_104", description: "Grab Flash Sectors 111_104", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_SECT119_112", description: "Grab Flash Sectors 119-112", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_SECT127_120", description: "Grab Flash Sectors 127-120", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z1_GRABRAM1R", description: "Zone 1 Grab RAM Status Register 1", offset: "0x20",
		bits: [
			{ name: "GRAB_RAM0", description: "Grab RAM LS0 Section A", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM1", description: "Grab RAM LS0 Section B", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM2", description: "Grab RAM LS0 Section C", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_RAM3", description: "Grab RAM LS0 Section D", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_RAM4", description: "Grab RAM LS1 Section A", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_RAM5", description: "Grab RAM LS1 Section B", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_RAM6", description: "Grab RAM LS1 Section C", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM LS1 Section D", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "Z1_EXEONLYSECT1R", description: "Zone 1 Execute Only Flash Status Register 1", offset: "0x26",
		bits: [
			{ name: "EXEONLY_SECT0", description: "Execute-Only Flash Sector 0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_SECT1", description: "Execute-Only Flash Sector 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_SECT2", description: "Execute-Only Flash Sector 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_SECT3", description: "Execute-Only Flash Sector 3", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_SECT4", description: "Execute-Only Flash Sector 4", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_SECT5", description: "Execute-Only Flash Sector 5", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_SECT6", description: "Execute-Only Flash Sector 6", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_SECT7", description: "Execute-Only Flash Sector 7", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_SECT8", description: "Execute-Only Flash Sector 8", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_SECT9", description: "Execute-Only Flash Sector 9", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_SECT10", description: "Execute-Only Flash Sector 10", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_SECT11", description: "Execute-Only Flash Sector 11", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_SECT12", description: "Execute-Only Flash Sector 12", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_SECT13", description: "Execute-Only Flash Sector 13", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_SECT14", description: "Execute-Only Flash Sector 14", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_SECT15", description: "Execute-Only Flash Sector 15", size: "1", shift: "15", mask: "0x8000" },
			{ name: "EXEONLY_SECT16", description: "Execute-Only Flash Sector 16", size: "1", shift: "16", mask: "0x10000" },
			{ name: "EXEONLY_SECT17", description: "Execute-Only Flash Sector 17", size: "1", shift: "17", mask: "0x20000" },
			{ name: "EXEONLY_SECT18", description: "Execute-Only Flash Sector 18", size: "1", shift: "18", mask: "0x40000" },
			{ name: "EXEONLY_SECT19", description: "Execute-Only Flash Sector 19", size: "1", shift: "19", mask: "0x80000" },
			{ name: "EXEONLY_SECT20", description: "Execute-Only Flash Sector 20", size: "1", shift: "20", mask: "0x100000" },
			{ name: "EXEONLY_SECT21", description: "Execute-Only Flash Sector 21", size: "1", shift: "21", mask: "0x200000" },
			{ name: "EXEONLY_SECT22", description: "Execute-Only Flash Sector 22", size: "1", shift: "22", mask: "0x400000" },
			{ name: "EXEONLY_SECT23", description: "Execute-Only Flash Sector 23", size: "1", shift: "23", mask: "0x800000" },
			{ name: "EXEONLY_SECT24", description: "Execute-Only Flash Sector 24", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "EXEONLY_SECT25", description: "Execute-Only Flash Sector 25", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "EXEONLY_SECT26", description: "Execute-Only Flash Sector 26", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "EXEONLY_SECT27", description: "Execute-Only Flash Sector 27", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "EXEONLY_SECT28", description: "Execute-Only Flash Sector 28", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "EXEONLY_SECT29", description: "Execute-Only Flash Sector 29", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "EXEONLY_SECT30", description: "Execute-Only Flash Sector 30", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "EXEONLY_SECT31", description: "Execute-Only Flash Sector 31", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "Z1_EXEONLYSECT2R", description: "Zone 1 Execute Only Flash Status Register 2", offset: "0x28",
		bits: [
			{ name: "EXEONLY_SECT39_32", description: "Execute-Only Flash Sectors 39_32", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_SECT47_40", description: "Execute-Only Flash Sectors 47-40", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_SECT55_48", description: "Execute-Only Flash Sectors 55-48", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_SECT63_56", description: "Execute-Only Flash Sectors 63-56", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_SECT71_64", description: "Execute-Only Flash Sectors 71-64", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_SECT79_72", description: "Execute-Only Flash Sectors 79-72", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_SECT87_80", description: "Execute-Only Flash Sectors 87-80", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_SECT95_88", description: "Execute-Only Flash Sectors 95-88", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_SECT103_96", description: "Execute-Only Flash Sectors 103-96", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_SECT111_104", description: "Execute-Only Flash Sectors 111-104", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_SECT119_112", description: "Execute-Only Flash Sectors 119-112", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_SECT127_120", description: "Execute-Only Flash Sectors 127-120", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "Z1_EXEONLYRAM1R", description: "Zone 1 Execute Only RAM Status Register 1", offset: "0x2A",
		bits: [
			{ name: "EXEONLY_RAM0", description: "Execute-Only RAM LS0 Section A", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_RAM1", description: "Execute-Only RAM LS0 Section B", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_RAM2", description: "Execute-Only RAM LS0 Section C", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_RAM3", description: "Execute-Only RAM LS0 Section D", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_RAM4", description: "Execute-Only RAM LS1 Section A", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_RAM5", description: "Execute-Only RAM LS1 Section B", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_RAM6", description: "Execute-Only RAM LS1 Section C", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_RAM7", description: "Execute-Only RAM LS1 Section D", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "Z1_JTAGKEY0", description: "JTAG Unlock Key Register 0", offset: "0x2E",
		bits: [
		]
	},
	{ name: "Z1_JTAGKEY1", description: "JTAG Unlock Key Register 1", offset: "0x30",
		bits: [
		]
	},
	{ name: "Z1_JTAGKEY2", description: "JTAG Unlock Key Register 2", offset: "0x32",
		bits: [
		]
	},
	{ name: "Z1_JTAGKEY3", description: "JTAG Unlock Key Register 3", offset: "0x34",
		bits: [
		]
	},
	{ name: "Z1_CMACKEY0", description: "Secure Boot CMAC Key Status Register 0", offset: "0x36",
		bits: [
		]
	},
	{ name: "Z1_CMACKEY1", description: "Secure Boot CMAC Key Status Register 1", offset: "0x38",
		bits: [
		]
	},
	{ name: "Z1_CMACKEY2", description: "Secure Boot CMAC Key Status Register 2", offset: "0x3A",
		bits: [
		]
	},
	{ name: "Z1_CMACKEY3", description: "Secure Boot CMAC Key Status Register 3", offset: "0x3C",
		bits: [
		]
	},
	{ name: "Z2_LINKPOINTER", description: "Zone 2 Link Pointer", offset: "0x0",
		bits: [
			{ name: "LINKPOINTER", description: "Zone2 LINK Pointer", size: "14", shift: "0", mask: "0x3FFF" },
		]
	},
	{ name: "Z2_OTPSECLOCK", description: "Zone 2 OTP Secure Lock", offset: "0x2",
		bits: [
			{ name: "JTAGLOCK", description: "JTAG Lock Status", size: "1", shift: "0", mask: "0x1" },
			{ name: "PSWDLOCK", description: "Zone2 Password Lock.", size: "4", shift: "4", mask: "0xF0" },
		]
	},
	{ name: "Z2_LINKPOINTERERR", description: "Link Pointer Error", offset: "0x6",
		bits: [
			{ name: "Z2_LINKPOINTERERR", description: "Error to Resolve Z2 Link pointer", size: "14", shift: "0", mask: "0x3FFF" },
		]
	},
	{ name: "Z2_GPREG1", description: "Zone 2 General Purpose Register-1", offset: "0x8",
		bits: [
		]
	},
	{ name: "Z2_GPREG2", description: "Zone 2 General Purpose Register-2", offset: "0xA",
		bits: [
		]
	},
	{ name: "Z2_GPREG3", description: "Zone 2 General Purpose Register-3", offset: "0xC",
		bits: [
		]
	},
	{ name: "Z2_GPREG4", description: "Zone 2 General Purpose Register-4", offset: "0xE",
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
	{ name: "Z2_CR", description: "Zone 2 CSM Control Register", offset: "0x18",
		bits: [
			{ name: "ALLZERO", description: "CSMPSWD All Zeros", size: "1", shift: "19", mask: "0x80000" },
			{ name: "ALLONE", description: "CSMPSWD All Ones", size: "1", shift: "20", mask: "0x100000" },
			{ name: "UNSECURE", description: "CSMPSWD Match CSMKEY", size: "1", shift: "21", mask: "0x200000" },
			{ name: "ARMED", description: "CSM Passwords Read Status", size: "1", shift: "22", mask: "0x400000" },
			{ name: "FORCESEC", description: "Force Secure", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "Z2_GRABSECT1R", description: "Zone 2 Grab Flash Status Register 1", offset: "0x1A",
		bits: [
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_SECT14", description: "Grab Flash Sector 14", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_SECT15", description: "Grab Flash Sector 15", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z2_GRABSECT2R", description: "Zone 2 Grab Flash Status Register 2", offset: "0x1C",
		bits: [
			{ name: "GRAB_SECT16", description: "Grab Flash Sector 16", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT17", description: "Grab Flash Sector 17", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT18", description: "Grab Flash Sector 18", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT19", description: "Grab Flash Sector 19", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT20", description: "Grab Flash Sector 20", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT21", description: "Grab Flash Sector 21", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT22", description: "Grab Flash Sector 22", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT23", description: "Grab Flash Sector 23", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT24", description: "Grab Flash Sector 24", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT25", description: "Grab Flash Sector 25", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT26", description: "Grab Flash Sector 26", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT27", description: "Grab Flash Sector 27", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT28", description: "Grab Flash Sector 28", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT29", description: "Grab Flash Sector 29", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_SECT30", description: "Grab Flash Sector 30", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_SECT31", description: "Grab Flash Sector 31", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z2_GRABSECT3R", description: "Zone 2 Grab Flash Status Register 3", offset: "0x1E",
		bits: [
			{ name: "GRAB_SECT39_32", description: "Grab Flash Sectors 39-32", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT47_40", description: "Grab Flash Sectors 47-40", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT55_48", description: "Grab Flash Sectors 55-48", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT63_56", description: "Grab Flash Sectors 63-56", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT71_64", description: "Grab Flash Sectors 71_64", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT79_72", description: "Grab Flash Sectors 79-72", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT87_80", description: "Grab Flash Sectors 87-80", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT95_88", description: "Grab Flash Sectors 95-88", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT103_96", description: "Grab Flash Sectors 103-96", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT111_104", description: "Grab Flash Sectors 111_104", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_SECT119_112", description: "Grab Flash Sectors 119-112", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_SECT127_120", description: "Grab Flash Sectors 127-120", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z2_GRABRAM1R", description: "Zone 2 Grab RAM Status Register 1", offset: "0x20",
		bits: [
			{ name: "GRAB_RAM0", description: "Grab RAM LS0 Section A", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM1", description: "Grab RAM LS0 Section B", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM2", description: "Grab RAM LS0 Section C", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_RAM3", description: "Grab RAM LS0 Section D", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_RAM4", description: "Grab RAM LS1 Section A", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_RAM5", description: "Grab RAM LS1 Section B", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_RAM6", description: "Grab RAM LS1 Section C", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM LS1 Section D", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "Z2_EXEONLYSECT1R", description: "Zone 2 Execute Only Flash Status Register 1", offset: "0x26",
		bits: [
			{ name: "EXEONLY_SECT0", description: "Execute-Only Flash Sector 0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_SECT1", description: "Execute-Only Flash Sector 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_SECT2", description: "Execute-Only Flash Sector 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_SECT3", description: "Execute-Only Flash Sector 3", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_SECT4", description: "Execute-Only Flash Sector 4", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_SECT5", description: "Execute-Only Flash Sector 5", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_SECT6", description: "Execute-Only Flash Sector 6", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_SECT7", description: "Execute-Only Flash Sector 7", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_SECT8", description: "Execute-Only Flash Sector 8", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_SECT9", description: "Execute-Only Flash Sector 9", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_SECT10", description: "Execute-Only Flash Sector 10", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_SECT11", description: "Execute-Only Flash Sector 11", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_SECT12", description: "Execute-Only Flash Sector 12", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_SECT13", description: "Execute-Only Flash Sector 13", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_SECT14", description: "Execute-Only Flash Sector 14", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_SECT15", description: "Execute-Only Flash Sector 15", size: "1", shift: "15", mask: "0x8000" },
			{ name: "EXEONLY_SECT16", description: "Execute-Only Flash Sector 16", size: "1", shift: "16", mask: "0x10000" },
			{ name: "EXEONLY_SECT17", description: "Execute-Only Flash Sector 17", size: "1", shift: "17", mask: "0x20000" },
			{ name: "EXEONLY_SECT18", description: "Execute-Only Flash Sector 18", size: "1", shift: "18", mask: "0x40000" },
			{ name: "EXEONLY_SECT19", description: "Execute-Only Flash Sector 19", size: "1", shift: "19", mask: "0x80000" },
			{ name: "EXEONLY_SECT20", description: "Execute-Only Flash Sector 20", size: "1", shift: "20", mask: "0x100000" },
			{ name: "EXEONLY_SECT21", description: "Execute-Only Flash Sector 21", size: "1", shift: "21", mask: "0x200000" },
			{ name: "EXEONLY_SECT22", description: "Execute-Only Flash Sector 22", size: "1", shift: "22", mask: "0x400000" },
			{ name: "EXEONLY_SECT23", description: "Execute-Only Flash Sector 23", size: "1", shift: "23", mask: "0x800000" },
			{ name: "EXEONLY_SECT24", description: "Execute-Only Flash Sector 24", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "EXEONLY_SECT25", description: "Execute-Only Flash Sector 25", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "EXEONLY_SECT26", description: "Execute-Only Flash Sector 26", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "EXEONLY_SECT27", description: "Execute-Only Flash Sector 27", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "EXEONLY_SECT28", description: "Execute-Only Flash Sector 28", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "EXEONLY_SECT29", description: "Execute-Only Flash Sector 29", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "EXEONLY_SECT30", description: "Execute-Only Flash Sector 30", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "EXEONLY_SECT31", description: "Execute-Only Flash Sector 31", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "Z2_EXEONLYSECT2R", description: "Zone 2 Execute Only Flash Status Register 2", offset: "0x28",
		bits: [
			{ name: "EXEONLY_SECT39_32", description: "Execute-Only Flash Sectors 39-32", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_SECT47_40", description: "Execute-Only Flash Sectors 47-40", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_SECT55_48", description: "Execute-Only Flash Sectors 55-48", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_SECT63_56", description: "Execute-Only Flash Sectors 63-56", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_SECT71_64", description: "Execute-Only Flash Sectors 71-64", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_SECT79_72", description: "Execute-Only Flash Sectors 79-72", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_SECT87_80", description: "Execute-Only Flash Sectors 87-80", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_SECT95_88", description: "Execute-Only Flash Sectors 95-88", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_SECT103_96", description: "Execute-Only Flash Sectors 103-96", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_SECT111_104", description: "Execute-Only Flash Sectors 111-104", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_SECT119_112", description: "Execute-Only Flash Sectors 119-112", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_SECT127_120", description: "Execute-Only Flash Sectors 127-120", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "Z2_EXEONLYRAM1R", description: "Zone 2 Execute Only RAM Status Register 1", offset: "0x2A",
		bits: [
			{ name: "EXEONLY_RAM0", description: "Execute-Only RAM LS0 Section A", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_RAM1", description: "Execute-Only RAM LS0 Section B", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_RAM2", description: "Execute-Only RAM LS0 Section C", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_RAM3", description: "Execute-Only RAM LS0 Section D", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_RAM4", description: "Execute-Only RAM LS1 Section A", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_RAM5", description: "Execute-Only RAM LS1 Section B", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_RAM6", description: "Execute-Only RAM LS1 Section C", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_RAM7", description: "Execute-Only RAM LS1 Section D", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "FLSEM", description: "Flash Wrapper Semaphore Register", offset: "0x0",
		bits: [
			{ name: "SEM", description: "Flash Semaphore Bit", size: "2", shift: "0", mask: "0x3" },
			{ name: "KEY", description: "Semaphore Key", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "SECTSTAT1", description: "Flash Sectors Status Register 1", offset: "0x8",
		bits: [
			{ name: "STATUS_SECT0", description: "Zone Status Flash Bank 0 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_SECT1", description: "Zone Status Flash Bank 0 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_SECT2", description: "Zone Status Flash Bank 0 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_SECT3", description: "Zone Status Flash Bank 0 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_SECT4", description: "Zone Status Flash Bank 0 Sector 4", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_SECT5", description: "Zone Status Flash Bank 0 Sector 5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_SECT6", description: "Zone Status Flash Bank 0 Sector 6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_SECT7", description: "Zone Status Flash Bank 0 Sector 7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_SECT8", description: "Zone Status Flash Bank 0 Sector 8", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_SECT9", description: "Zone Status Flash Bank 0 Sector 9", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_SECT10", description: "Zone Status Flash Bank 0 Sector 10", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_SECT11", description: "Zone Status Flash Bank 0 Sector 11", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_SECT12", description: "Zone Status Flash Bank 0 Sector 12", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_SECT13", description: "Zone Status Flash Bank 0 Sector 13", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "STATUS_SECT14", description: "Zone Status Flash Bank 0 Sector 14", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "STATUS_SECT15", description: "Zone Status Flash Bank 0 Sector 15", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "SECTSTAT2", description: "Flash Sectors Status Register 2", offset: "0xA",
		bits: [
			{ name: "STATUS_SECT16", description: "Zone Status Flash Bank 0 Sector 16", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_SECT17", description: "Zone Status Flash Bank 0 Sector 17", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_SECT18", description: "Zone Status Flash Bank 0 Sector 18", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_SECT19", description: "Zone Status Flash Bank 0 Sector 19", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_SECT20", description: "Zone Status Flash Bank 0 Sector 20", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_SECT21", description: "Zone Status Flash Bank 0 Sector 21", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_SECT22", description: "Zone Status Flash Bank 0 Sector 22", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_SECT23", description: "Zone Status Flash Bank 0 Sector 23", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_SECT24", description: "Zone Status Flash Bank 0 Sector 24", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_SECT25", description: "Zone Status Flash Bank 0 Sector 25", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_SECT26", description: "Zone Status Flash Bank 0 Sector 26", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_SECT27", description: "Zone Status Flash Bank 0 Sector 27", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_SECT28", description: "Zone Status Flash Bank 0 Sector 28", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_SECT29", description: "Zone Status Flash Bank 0 Sector 29", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "STATUS_SECT30", description: "Zone Status Flash Bank 0 Sector 30", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "STATUS_SECT31", description: "Zone Status Flash Bank 0 Sector 31", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "SECTSTAT3", description: "Flash Sectors Status Register 3", offset: "0xC",
		bits: [
			{ name: "STATUS_SECT39_32", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_SECT47_40", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_SECT55_48", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_SECT63_56", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_SECT71_64", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_SECT79_72", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_SECT87_80", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_SECT95_88", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_SECT103_96", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_SECT111_104", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "STATUS_SECT119_112", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "STATUS_SECT127_120", description: "Zone Status flash Bank 0 Sectors", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "RAMSTAT1", description: "RAM Status Register 1", offset: "0x10",
		bits: [
			{ name: "STATUS_RAM0", description: "Zone Status RAM LS0 Section A", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_RAM1", description: "Zone Status RAM LS0 Section B", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_RAM2", description: "Zone Status RAM LS0 Section C", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_RAM3", description: "Zone Status RAM LS0 Section D", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_RAM4", description: "Zone Status RAM LS1 Section A", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_RAM5", description: "Zone Status RAM LS1 Section B", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_RAM6", description: "Zone Status RAM LS1 Section C", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_RAM7", description: "Zone Status RAM LS1 Section D", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "SECERRSTAT", description: "Security Error Status Register", offset: "0x18",
		bits: [
			{ name: "ERR", description: "Security Configuration load Error Status", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SECERRCLR", description: "Security Error Clear Register", offset: "0x1A",
		bits: [
			{ name: "ERR", description: "Clear Security Configuration Load Error Status Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SECERRFRC", description: "Security Error Force Register", offset: "0x1C",
		bits: [
			{ name: "ERR", description: "Set Security Configuration Load Error Status Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Valid Register Write Key", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "DENYCODE", description: "Flash Authorization Denial Code", offset: "0x1E",
		bits: [
			{ name: "BLOCKED", description: "Blocked Code", size: "1", shift: "0", mask: "0x1" },
			{ name: "ILLADDR", description: "Illegal Address Code", size: "1", shift: "1", mask: "0x2" },
			{ name: "ILLPROG", description: "Illegal Program Address", size: "1", shift: "2", mask: "0x4" },
			{ name: "ILLERASE", description: "Illegal Erase Address", size: "1", shift: "3", mask: "0x8" },
			{ name: "ILLRDVER", description: "Illegal Read Verify Address", size: "1", shift: "4", mask: "0x10" },
			{ name: "ILLMODECH", description: "Illegal Mode Change", size: "1", shift: "5", mask: "0x20" },
			{ name: "ILLCMD", description: "Illegal Command", size: "1", shift: "6", mask: "0x40" },
			{ name: "ILLSIZE", description: "Illegal Command Size", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "RAMOPENSTAT", description: "RAM Security Open Status Register", offset: "0x20",
		bits: [
			{ name: "RAMOPEN", description: "RAM Security Open", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "RAMOPENFRC", description: "RAM Security Open Force Register", offset: "0x22",
		bits: [
			{ name: "SET", description: "Set RAM Open request", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Valid Write KEY", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "RAMOPENCLR", description: "RAM Security Open Clear Register", offset: "0x24",
		bits: [
			{ name: "CLEAR", description: "Clear RAM Open request", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Valid Write KEY", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "RAMOPENLOCK", description: "RAMOPEN Lock Register", offset: "0x26",
		bits: [
			{ name: "LOCK", description: "RAMOPEN Lock", size: "1", shift: "0", mask: "0x1" },
		]
	},
];
module.exports = {
	DCSMRegisters: DCSMRegisters,
}
