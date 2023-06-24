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
	{ name: "Z1OTP_CRCLOCK", description: "Secure CRC Lock", offset: "0x12",
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
	{ name: "Z2OTP_CRCLOCK", description: "Secure CRC Lock", offset: "0x12",
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
			{ name: "CRCLOCK", description: "Zone1 CRC Lock.", size: "4", shift: "8", mask: "0xF00" },
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
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0 in CPU1 BANK", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1 in CPU1 BANK", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2 in CPU1 BANK", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3 in CPU1 BANK", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4 in CPU1 BANK", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5 in CPU1 BANK", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6 in CPU1 BANK", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7 in CPU1 BANK", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8 in CPU1 BANK", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9 in CPU1 BANK", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10 in CPU1 BANK", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11 in CPU1 BANK", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12 in CPU1 BANK", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13 in CPU1 BANK", size: "2", shift: "26", mask: "0xC000000" },
		]
	},
	{ name: "Z1_GRABSECT2R", description: "Zone 1 Grab Flash Status Register 2", offset: "0x1C",
		bits: [
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0 in CM BANK", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1 in CM BANK", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2 in CM BANK", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3 in CM BANK", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4 in CM BANK", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5 in CM BANK", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6 in CM BANK", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7 in CM BANK", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8 in CM BANK", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9 in CM BANK", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10 in CM BANK", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11 in CM BANK", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12 in CM BANK", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13 in CM BANK", size: "2", shift: "26", mask: "0xC000000" },
		]
	},
	{ name: "Z1_GRABSECT3R", description: "Zone 1 Grab Flash Status Register 3", offset: "0x1E",
		bits: [
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0 in CPU2 BANK", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1 in CPU2 BANK", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2 in CPU2 BANK", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3 in CPU2 BANK", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4 in CPU2 BANK", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5 in CPU2 BANK", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6 in CPU2 BANK", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7 in CPU2 BANK", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8 in CPU2 BANK", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9 in CPU2 BANK", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10 in CPU2 BANK", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11 in CPU2 BANK", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12 in CPU2 BANK", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13 in CPU2 BANK", size: "2", shift: "26", mask: "0xC000000" },
		]
	},
	{ name: "Z1_GRABRAM1R", description: "Zone 1 Grab RAM Status Register 1", offset: "0x20",
		bits: [
			{ name: "GRAB_RAM0", description: "Grab RAM CPU1.LS0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM1", description: "Grab RAM CPU1.LS1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM2", description: "Grab RAM CPU1.LS2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_RAM3", description: "Grab RAM CPU1.LS3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_RAM4", description: "Grab RAM CPU1.LS4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_RAM5", description: "Grab RAM CPU1.LS5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_RAM6", description: "Grab RAM CPU1.LS6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM CPU1.LS7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_RAM8", description: "Grab RAM CPU1.D0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_RAM9", description: "Grab RAM CPU1.D1", size: "2", shift: "18", mask: "0xC0000" },
		]
	},
	{ name: "Z1_GRABRAM2R", description: "Zone 1 Grab RAM Status Register 2", offset: "0x22",
		bits: [
			{ name: "GRAB_RAM0", description: "Grab RAM CM.C0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM1", description: "Grab RAM CM.C1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM4", description: "Grab RAM CPU1TOCM MSGRAM0_L", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_RAM5", description: "Grab RAM CPU1TOCM MSGRAM0_H", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_RAM6", description: "Grab RAM CMTOCPU1 MSGRAM0_L", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM CMTOCPU1 MSGRAM0_H", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_RAM8", description: "Grab RAM CPU2TOCM MSGRAM0_L", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_RAM9", description: "Grab RAM CPU2TOCM MSGRAM0_H", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_RAM10", description: "Grab RAM CMTOCPU2 MSGRAM0_L", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_RAM11", description: "Grab RAM CMTOCPU2 MSGRAM0_H", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_RAM12", description: "Grab RAM CPU1TOCPU2 MSGRAM0_L", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_RAM13", description: "Grab RAM CPU1TOCPU2 MSGRAM0_H", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_RAM14", description: "Grab RAM CPU2TOCPU1 MSGRAM0_L", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_RAM15", description: "Grab RAM CPU2TOCPU1 MSGRAM0_H", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z1_GRABRAM3R", description: "Zone 1 Grab RAM Status Register 3", offset: "0x24",
		bits: [
			{ name: "GRAB_RAM0", description: "Grab RAM CPU2.LS0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM1", description: "Grab RAM CPU2.LS1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM2", description: "Grab RAM CPU2.LS2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_RAM3", description: "Grab RAM CPU2.LS3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_RAM4", description: "Grab RAM CPU2.LS4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_RAM5", description: "Grab RAM CPU2.LS5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_RAM6", description: "Grab RAM CPU2.LS6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM CPU2.LS7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_RAM8", description: "Grab RAM CPU2.D0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_RAM9", description: "Grab RAM CPU2.D1", size: "2", shift: "18", mask: "0xC0000" },
		]
	},
	{ name: "Z1_EXEONLYSECT1R", description: "Zone 1 Execute Only Flash Status Register 1", offset: "0x26",
		bits: [
			{ name: "EXEONLY_CPU1_SECT0", description: "Execute-Only Flash Sector 0 in", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_CPU1_SECT1", description: "Execute-Only Flash Sector 1 in", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_CPU1_SECT2", description: "Execute-Only Flash Sector 2 in", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_CPU1_SECT3", description: "Execute-Only Flash Sector 3 in", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_CPU1_SECT4", description: "Execute-Only Flash Sector 4 in", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_CPU1_SECT5", description: "Execute-Only Flash Sector 5 in", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_CPU1_SECT6", description: "Execute-Only Flash Sector 6 in", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_CPU1_SECT7", description: "Execute-Only Flash Sector 7 in", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_CPU1_SECT8", description: "Execute-Only Flash Sector 8 in", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_CPU1_SECT9", description: "Execute-Only Flash Sector 9 in", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_CPU1_SECT10", description: "Execute-Only Flash Sector 10", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_CPU1_SECT11", description: "Execute-Only Flash Sector 11", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_CPU1_SECT12", description: "Execute-Only Flash Sector 12", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_CPU1_SECT13", description: "Execute-Only Flash Sector 13", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_CM_SECT0", description: "Execute-Only Flash Sector 0 in", size: "1", shift: "16", mask: "0x10000" },
			{ name: "EXEONLY_CM_SECT1", description: "Execute-Only Flash Sector 1 in", size: "1", shift: "17", mask: "0x20000" },
			{ name: "EXEONLY_CM_SECT2", description: "Execute-Only Flash Sector 2 in", size: "1", shift: "18", mask: "0x40000" },
			{ name: "EXEONLY_CM_SECT3", description: "Execute-Only Flash Sector 3 in", size: "1", shift: "19", mask: "0x80000" },
			{ name: "EXEONLY_CM_SECT4", description: "Execute-Only Flash Sector 4 in", size: "1", shift: "20", mask: "0x100000" },
			{ name: "EXEONLY_CM_SECT5", description: "Execute-Only Flash Sector 5 in", size: "1", shift: "21", mask: "0x200000" },
			{ name: "EXEONLY_CM_SECT6", description: "Execute-Only Flash Sector 6 in", size: "1", shift: "22", mask: "0x400000" },
			{ name: "EXEONLY_CM_SECT7", description: "Execute-Only Flash Sector 7 in", size: "1", shift: "23", mask: "0x800000" },
			{ name: "EXEONLY_CM_SECT8", description: "Execute-Only Flash Sector 8 in", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "EXEONLY_CM_SECT9", description: "Execute-Only Flash Sector 9 in", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "EXEONLY_CM_SECT10", description: "Execute-Only Flash Sector 10", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "EXEONLY_CM_SECT11", description: "Execute-Only Flash Sector 11", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "EXEONLY_CM_SECT12", description: "Execute-Only Flash Sector 12", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "EXEONLY_CM_SECT13", description: "Execute-Only Flash Sector 13", size: "1", shift: "29", mask: "0x20000000" },
		]
	},
	{ name: "Z1_EXEONLYSECT2R", description: "Zone 1 Execute Only Flash Status Register 2", offset: "0x28",
		bits: [
			{ name: "EXEONLY_CPU2_SECT0", description: "Execute-Only Flash Sector 0 in", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_CPU2_SECT1", description: "Execute-Only Flash Sector 1 in", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_CPU2_SECT2", description: "Execute-Only Flash Sector 2 in", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_CPU2_SECT3", description: "Execute-Only Flash Sector 3 in", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_CPU2_SECT4", description: "Execute-Only Flash Sector 4 in", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_CPU2_SECT5", description: "Execute-Only Flash Sector 5 in", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_CPU2_SECT6", description: "Execute-Only Flash Sector 6 in", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_CPU2_SECT7", description: "Execute-Only Flash Sector 7 in", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_CPU2_SECT8", description: "Execute-Only Flash Sector 8 in", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_CPU2_SECT9", description: "Execute-Only Flash Sector 9 in", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_CPU2_SECT10", description: "Execute-Only Flash Sector 10 in", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_CPU2_SECT11", description: "Execute-Only Flash Sector 11 in", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_CPU2_SECT12", description: "Execute-Only Flash Sector 12 in", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_CPU2_SECT13", description: "Execute-Only Flash Sector 13 in", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "Z1_EXEONLYRAM1R", description: "Zone 1 Execute Only RAM Status Register 1", offset: "0x2A",
		bits: [
			{ name: "EXEONLY_RAM0", description: "Execute-Only RAM CPU1.LS0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_RAM1", description: "Execute-Only RAM CPU1.LS1", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_RAM2", description: "Execute-Only RAM CPU1.LS2", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_RAM3", description: "Execute-Only RAM CPU1.LS3", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_RAM4", description: "Execute-Only RAM CPU1.LS4", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_RAM5", description: "Execute-Only RAM CPU1.LS5", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_RAM6", description: "Execute-Only RAM CPU1.LS6", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_RAM7", description: "Execute-Only RAM CPU1.LS7", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_RAM8", description: "Execute-Only RAM CPU1.D0", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_RAM9", description: "Execute-Only RAM CPU1.D1", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_RAM16", description: "Execute-Only RAM on CM.C0", size: "1", shift: "16", mask: "0x10000" },
			{ name: "EXEONLY_RAM17", description: "Execute-Only RAM on CM.C1", size: "1", shift: "17", mask: "0x20000" },
			{ name: "EXEONLY_RAM22", description: "Execute-Only RAM CPU2.D1", size: "1", shift: "22", mask: "0x400000" },
			{ name: "EXEONLY_RAM23", description: "Execute-Only RAM CPU2.D0", size: "1", shift: "23", mask: "0x800000" },
			{ name: "EXEONLY_RAM24", description: "Execute-Only RAM CPU2.LS7", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "EXEONLY_RAM25", description: "Execute-Only RAM CPU2.LS6", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "EXEONLY_RAM26", description: "Execute-Only RAM CPU2.LS5", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "EXEONLY_RAM27", description: "Execute-Only RAM CPU2.LS4", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "EXEONLY_RAM28", description: "Execute-Only RAM CPU2.LS3", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "EXEONLY_RAM29", description: "Execute-Only RAM CPU2.LS2", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "EXEONLY_RAM30", description: "Execute-Only RAM CPU2.LS1", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "EXEONLY_RAM31", description: "Execute-Only RAM CPU2.LS0", size: "1", shift: "31", mask: "0x80000000" },
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
			{ name: "CRCLOCK", description: "Zone2 CRC Lock.", size: "4", shift: "8", mask: "0xF00" },
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
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0 in CPU1 BANK", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1 in CPU1 BANK", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2 in CPU1 BANK", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3 in CPU1 BANK", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4 in CPU1 BANK", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5 in CPU1 BANK", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6 in CPU1 BANK", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7 in CPU1 BANK", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8 in CPU1 BANK", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9 in CPU1 BANK", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10 in CPU1 BANK", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11 in CPU1 BANK", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12 in CPU1 BANK", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13 in CPU1 BANK", size: "2", shift: "26", mask: "0xC000000" },
		]
	},
	{ name: "Z2_GRABSECT2R", description: "Zone 2 Grab Flash Status Register 2", offset: "0x1C",
		bits: [
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0 in CM BANK", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1 in CM BANK", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2 in CM BANK", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3 in CM BANK", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4 in CM BANK", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5 in CM BANK", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6 in CM BANK", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7 in CM BANK", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8 in CM BANK", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9 in CM BANK", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10 in CM BANK", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11 in CM BANK", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12 in CM BANK", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13 in CM BANK", size: "2", shift: "26", mask: "0xC000000" },
		]
	},
	{ name: "Z2_GRABSECT3R", description: "Zone 2 Grab Flash Status Register 3", offset: "0x1E",
		bits: [
			{ name: "GRAB_SECT0", description: "Grab Flash Sector 0 in CPU2 BANK", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_SECT1", description: "Grab Flash Sector 1 in CPU2 BANK", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_SECT2", description: "Grab Flash Sector 2 in CPU2 BANK", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_SECT3", description: "Grab Flash Sector 3 in CPU2 BANK", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_SECT4", description: "Grab Flash Sector 4 in CPU2 BANK", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_SECT5", description: "Grab Flash Sector 5 in CPU2 BANK", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_SECT6", description: "Grab Flash Sector 6 in CPU2 BANK", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_SECT7", description: "Grab Flash Sector 7 in CPU2 BANK", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_SECT8", description: "Grab Flash Sector 8 in CPU2 BANK", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_SECT9", description: "Grab Flash Sector 9 in CPU2 BANK", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_SECT10", description: "Grab Flash Sector 10 in CPU2 BANK", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_SECT11", description: "Grab Flash Sector 11 in CPU2 BANK", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_SECT12", description: "Grab Flash Sector 12 in CPU2 BANK", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_SECT13", description: "Grab Flash Sector 13 in CPU2 BANK", size: "2", shift: "26", mask: "0xC000000" },
		]
	},
	{ name: "Z2_GRABRAM1R", description: "Zone 2 Grab RAM Status Register 1", offset: "0x20",
		bits: [
			{ name: "GRAB_RAM0", description: "Grab RAM CPU1.LS0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM1", description: "Grab RAM CPU1.LS1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM2", description: "Grab RAM CPU1.LS2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_RAM3", description: "Grab RAM CPU1.LS3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_RAM4", description: "Grab RAM CPU1.LS4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_RAM5", description: "Grab RAM CPU1.LS5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_RAM6", description: "Grab RAM CPU1.LS6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM CPU1.LS7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_RAM8", description: "Grab RAM CPU1.D0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_RAM9", description: "Grab RAM CPU1.D1", size: "2", shift: "18", mask: "0xC0000" },
		]
	},
	{ name: "Z2_GRABRAM2R", description: "Zone 2 Grab RAM Status Register 2", offset: "0x22",
		bits: [
			{ name: "GRAB_RAM0", description: "Grab RAM CM.C0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM1", description: "Grab RAM CM.C1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM4", description: "Grab RAM CPU1TOCM MSGRAM0_L", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_RAM5", description: "Grab RAM CPU1TOCM MSGRAM0_H", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_RAM6", description: "Grab RAM CMTOCPU1 MSGRAM0_L", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM CMTOCPU1 MSGRAM0_H", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_RAM8", description: "Grab RAM CPU2TOCM MSGRAM0_L", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_RAM9", description: "Grab RAM CPU2TOCM MSGRAM0_H", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_RAM10", description: "Grab RAM CMTOCPU2 MSGRAM0_L", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_RAM11", description: "Grab RAM CMTOCPU2 MSGRAM0_H", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_RAM12", description: "Grab RAM CPU1TOCPU2 MSGRAM0_L", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_RAM13", description: "Grab RAM CPU1TOCPU2 MSGRAM0_H", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_RAM14", description: "Grab RAM CPU2TOCPU1 MSGRAM0_L", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_RAM15", description: "Grab RAM CPU2TOCPU1 MSGRAM0_H", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z2_GRABRAM3R", description: "Zone 2 Grab RAM Status Register 3", offset: "0x24",
		bits: [
			{ name: "GRAB_RAM0", description: "Grab RAM CPU2.LS0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM1", description: "Grab RAM CPU2.LS1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM2", description: "Grab RAM CPU2.LS2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_RAM3", description: "Grab RAM CPU2.LS3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_RAM4", description: "Grab RAM CPU2.LS4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_RAM5", description: "Grab RAM CPU2.LS5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_RAM6", description: "Grab RAM CPU2.LS6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_RAM7", description: "Grab RAM CPU2.LS7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_RAM8", description: "Grab RAM CPU2.D0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_RAM9", description: "Grab RAM CPU2.D1", size: "2", shift: "18", mask: "0xC0000" },
		]
	},
	{ name: "Z2_EXEONLYSECT1R", description: "Zone 2 Execute Only Flash Status Register 1", offset: "0x26",
		bits: [
			{ name: "EXEONLY_CPU1_SECT0", description: "Execute-Only Flash Sector 0 in", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_CPU1_SECT1", description: "Execute-Only Flash Sector 1 in", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_CPU1_SECT2", description: "Execute-Only Flash Sector 2 in", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_CPU1_SECT3", description: "Execute-Only Flash Sector 3 in", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_CPU1_SECT4", description: "Execute-Only Flash Sector 4 in", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_CPU1_SECT5", description: "Execute-Only Flash Sector 5 in", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_CPU1_SECT6", description: "Execute-Only Flash Sector 6 in", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_CPU1_SECT7", description: "Execute-Only Flash Sector 7 in", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_CPU1_SECT8", description: "Execute-Only Flash Sector 8 in", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_CPU1_SECT9", description: "Execute-Only Flash Sector 9 in", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_CPU1_SECT10", description: "Execute-Only Flash Sector 10", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_CPU1_SECT11", description: "Execute-Only Flash Sector 11", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_CPU1_SECT12", description: "Execute-Only Flash Sector 12", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_CPU1_SECT13", description: "Execute-Only Flash Sector 13", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_CM_SECT0", description: "Execute-Only Flash Sector 0 in", size: "1", shift: "16", mask: "0x10000" },
			{ name: "EXEONLY_CM_SECT1", description: "Execute-Only Flash Sector 1 in", size: "1", shift: "17", mask: "0x20000" },
			{ name: "EXEONLY_CM_SECT2", description: "Execute-Only Flash Sector 2 in", size: "1", shift: "18", mask: "0x40000" },
			{ name: "EXEONLY_CM_SECT3", description: "Execute-Only Flash Sector 3 in", size: "1", shift: "19", mask: "0x80000" },
			{ name: "EXEONLY_CM_SECT4", description: "Execute-Only Flash Sector 4 in", size: "1", shift: "20", mask: "0x100000" },
			{ name: "EXEONLY_CM_SECT5", description: "Execute-Only Flash Sector 5 in", size: "1", shift: "21", mask: "0x200000" },
			{ name: "EXEONLY_CM_SECT6", description: "Execute-Only Flash Sector 6 in", size: "1", shift: "22", mask: "0x400000" },
			{ name: "EXEONLY_CM_SECT7", description: "Execute-Only Flash Sector 7 in", size: "1", shift: "23", mask: "0x800000" },
			{ name: "EXEONLY_CM_SECT8", description: "Execute-Only Flash Sector 8 in", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "EXEONLY_CM_SECT9", description: "Execute-Only Flash Sector 9 in", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "EXEONLY_CM_SECT10", description: "Execute-Only Flash Sector 10", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "EXEONLY_CM_SECT11", description: "Execute-Only Flash Sector 11", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "EXEONLY_CM_SECT12", description: "Execute-Only Flash Sector 12", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "EXEONLY_CM_SECT13", description: "Execute-Only Flash Sector 13", size: "1", shift: "29", mask: "0x20000000" },
		]
	},
	{ name: "Z2_EXEONLYSECT2R", description: "Zone 2 Execute Only Flash Status Register 2", offset: "0x28",
		bits: [
			{ name: "EXEONLY_CPU2_SECT0", description: "Execute-Only Flash Sector 0 in", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_CPU2_SECT1", description: "Execute-Only Flash Sector 1 in", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_CPU2_SECT2", description: "Execute-Only Flash Sector 2 in", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_CPU2_SECT3", description: "Execute-Only Flash Sector 3 in", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_CPU2_SECT4", description: "Execute-Only Flash Sector 4 in", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_CPU2_SECT5", description: "Execute-Only Flash Sector 5 in", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_CPU2_SECT6", description: "Execute-Only Flash Sector 6 in", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_CPU2_SECT7", description: "Execute-Only Flash Sector 7 in", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_CPU2_SECT8", description: "Execute-Only Flash Sector 8 in", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_CPU2_SECT9", description: "Execute-Only Flash Sector 9 in", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_CPU2_SECT10", description: "Execute-Only Flash Sector 10 in", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_CPU2_SECT11", description: "Execute-Only Flash Sector 11 in", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_CPU2_SECT12", description: "Execute-Only Flash Sector 12 in", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_CPU2_SECT13", description: "Execute-Only Flash Sector 13 in", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "Z2_EXEONLYRAM1R", description: "Zone 2 Execute Only RAM Status Register 1", offset: "0x2A",
		bits: [
			{ name: "EXEONLY_RAM0", description: "Execute-Only RAM CPU1.LS0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_RAM1", description: "Execute-Only RAM CPU1.LS1", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_RAM2", description: "Execute-Only RAM CPU1.LS2", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_RAM3", description: "Execute-Only RAM CPU1.LS3", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_RAM4", description: "Execute-Only RAM CPU1.LS4", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_RAM5", description: "Execute-Only RAM CPU1.LS5", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_RAM6", description: "Execute-Only RAM CPU1.LS6", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_RAM7", description: "Execute-Only RAM CPU1.LS7", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_RAM8", description: "Execute-Only RAM CPU1.D0", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_RAM9", description: "Execute-Only RAM CPU1.D1", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_RAM16", description: "Execute-Only RAM on CM.C0", size: "1", shift: "16", mask: "0x10000" },
			{ name: "EXEONLY_RAM17", description: "Execute-Only RAM on CM.C1", size: "1", shift: "17", mask: "0x20000" },
			{ name: "EXEONLY_RAM22", description: "Execute-Only RAM CPU2.D1", size: "1", shift: "22", mask: "0x400000" },
			{ name: "EXEONLY_RAM23", description: "Execute-Only RAM CPU2.D0", size: "1", shift: "23", mask: "0x800000" },
			{ name: "EXEONLY_RAM24", description: "Execute-Only RAM CPU2.LS7", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "EXEONLY_RAM25", description: "Execute-Only RAM CPU2.LS6", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "EXEONLY_RAM26", description: "Execute-Only RAM CPU2.LS5", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "EXEONLY_RAM27", description: "Execute-Only RAM CPU2.LS4", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "EXEONLY_RAM28", description: "Execute-Only RAM CPU2.LS3", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "EXEONLY_RAM29", description: "Execute-Only RAM CPU2.LS2", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "EXEONLY_RAM30", description: "Execute-Only RAM CPU2.LS1", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "EXEONLY_RAM31", description: "Execute-Only RAM CPU2.LS0", size: "1", shift: "31", mask: "0x80000000" },
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
			{ name: "STATUS_SECT0", description: "Zone Status flash CPU1 BANK Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_SECT1", description: "Zone Status flash CPU1 BANK sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_SECT2", description: "Zone Status flash CPU1 BANK Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_SECT3", description: "Zone Status flash CPU1 BANK Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_SECT4", description: "Zone Status flash CPU1 BANK Sector 4", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_SECT5", description: "Zone Status flash CPU1 BANK Sector 5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_SECT6", description: "Zone Status flash CPU1 BANK Sector 6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_SECT7", description: "Zone Status flash CPU1 BANK Sector 7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_SECT8", description: "Zone Status flash CPU1 BANK sector 8", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_SECT9", description: "Zone Status flash CPU1 BANK Sector 9", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_SECT10", description: "Zone Status flash CPU1 BANK Sector 10", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_SECT11", description: "Zone Status flash CPU1 BANK Sector 11", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_SECT12", description: "Zone Status flash CPU1 BANK Sector 12", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_SECT13", description: "Zone Status flash CPU1 BANK Sector 13", size: "2", shift: "26", mask: "0xC000000" },
		]
	},
	{ name: "SECTSTAT2", description: "Flash Sectors Status Register 2", offset: "0xA",
		bits: [
			{ name: "STATUS_SECT0", description: "Zone Status flash CM BANK Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_SECT1", description: "Zone Status flash CM BANK sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_SECT2", description: "Zone Status flash CM BANK Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_SECT3", description: "Zone Status flash CM BANK Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_SECT4", description: "Zone Status flash CM BANK Sector 4", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_SECT5", description: "Zone Status flash CM BANK Sector 5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_SECT6", description: "Zone Status flash CM BANK Sector 6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_SECT7", description: "Zone Status flash CM BANK Sector 7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_SECT8", description: "Zone Status flash CM BANK sector 8", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_SECT9", description: "Zone Status flash CM BANK Sector 9", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_SECT10", description: "Zone Status flash CM BANK Sector 10", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_SECT11", description: "Zone Status flash CM BANK Sector 11", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_SECT12", description: "Zone Status flash CM BANK Sector 12", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_SECT13", description: "Zone Status flash CM BANK Sector 13", size: "2", shift: "26", mask: "0xC000000" },
		]
	},
	{ name: "SECTSTAT3", description: "Flash Sectors Status Register 3", offset: "0xC",
		bits: [
			{ name: "STATUS_SECT0", description: "Zone Status flash CPU2 BANK Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_SECT1", description: "Zone Status flash CPU2 BANK sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_SECT2", description: "Zone Status flash CPU2 BANK Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_SECT3", description: "Zone Status flash CPU2 BANK Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_SECT4", description: "Zone Status flash CPU2 BANK Sector 4", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_SECT5", description: "Zone Status flash CPU2 BANK Sector 5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_SECT6", description: "Zone Status flash CPU2 BANK Sector 6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_SECT7", description: "Zone Status flash CPU2 BANK Sector 7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_SECT8", description: "Zone Status flash CPU2 BANK sector 8", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_SECT9", description: "Zone Status flash CPU2 BANK Sector 9", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_SECT10", description: "Zone Status flash CPU2 BANK Sector 10", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_SECT11", description: "Zone Status flash CPU2 BANK Sector 11", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_SECT12", description: "Zone Status flash CPU2 BANK Sector 12", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_SECT13", description: "Zone Status flash CPU2 BANK Sector 13", size: "2", shift: "26", mask: "0xC000000" },
		]
	},
	{ name: "RAMSTAT1", description: "RAM Status Register 1", offset: "0x10",
		bits: [
			{ name: "STATUS_RAM0", description: "Zone Status RAM CPU1.LS0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_RAM1", description: "Zone Status RAM CPU1.LS1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_RAM2", description: "Zone Status RAM CPU1.LS2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_RAM3", description: "Zone Status RAM CPU1.LS3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_RAM4", description: "Zone Status RAM CPU1.LS4", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_RAM5", description: "Zone Status RAM CPU1.LS5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_RAM6", description: "Zone Status RAM CPU1.LS6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_RAM7", description: "Zone Status RAM CPU1.LS7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_RAM8", description: "Zone Status RAM CPU1.D0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_RAM9", description: "Zone Status RAM CPU1.D1", size: "2", shift: "18", mask: "0xC0000" },
		]
	},
	{ name: "RAMSTAT2", description: "RAM Status Register 2", offset: "0x12",
		bits: [
			{ name: "STATUS_RAM0", description: "Zone Status RAM CM.C0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_RAM1", description: "Zone Status RAM CM.C1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_RAM4", description: "Zone Status RAM CPU1 to CM MSG RAM 1", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_RAM5", description: "Zone Status RAM CPU1 to CM MSG RAM 2", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_RAM6", description: "Zone Status RAM CM to CPU1 MSG RAM 1", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_RAM7", description: "Zone Status RAM CM to CPU1 MSG RAM 2", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_RAM8", description: "Zone Status RAM CPU2 to CM MSG RAM 1", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_RAM9", description: "Zone Status RAM CPU2 to CM MSG RAM 2", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_RAM10", description: "Zone Status RAM CM to CPU2 MSG RAM 1", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_RAM11", description: "Zone Status RAM CM to CPU2 MSG RAM 2", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_RAM12", description: "Zone Status RAM CPU1 to CPU2 MSG RAM 1", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_RAM13", description: "Zone Status RAM CPU1 to CPU2 MSG RAM 2", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "STATUS_RAM14", description: "Zone Status RAM CPU2 to CPU1 MSG RAM 1", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "STATUS_RAM15", description: "Zone Status RAM CPU2 to CPU1 MSG RAM 2", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "RAMSTAT3", description: "RAM Status Register 3", offset: "0x14",
		bits: [
			{ name: "STATUS_RAM0", description: "Zone Status RAM CPU2.LS0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_RAM1", description: "Zone Status RAM CPU2.LS1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_RAM2", description: "Zone Status RAM CPU2.LS2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_RAM3", description: "Zone Status RAM CPU2.LS3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_RAM4", description: "Zone Status RAM CPU2.LS4", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_RAM5", description: "Zone Status RAM CPU2.LS5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_RAM6", description: "Zone Status RAM CPU2.LS6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_RAM7", description: "Zone Status RAM CPU2.LS7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_RAM8", description: "Zone Status RAM CPU2.D0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_RAM9", description: "Zone Status RAM CPU2.D1", size: "2", shift: "18", mask: "0xC0000" },
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
];
module.exports = {
	DCSMRegisters: DCSMRegisters,
}
