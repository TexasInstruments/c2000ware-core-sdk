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
			{ name: "FORCESEC", description: "Force Secure", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "Z1_GRABSECT1R", description: "Zone 1 Grab Flash Status Register 1", offset: "0x1A",
		bits: [
			{ name: "GRAB_B0_SECT0", description: "Grab Flash Bank0 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_B0_SECT1", description: "Grab Flash Bank0 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_B0_SECT2", description: "Grab Flash Bank0 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_B0_SECT3", description: "Grab Flash Bank0 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_B0_SECT31_4", description: "Grab Flash Bank0 Sector 31-4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_B0_SECT63_32", description: "Grab Flash Bank0 Sector 63-32", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_B0_SECT95_64", description: "Grab Flash Bank0 Sector 95-64", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_B0_SECT127_96", description: "Grab Flash Bank1 Sector 127-96", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_B1_SECT0", description: "Grab Flash Bank1 Sector 0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_B1_SECT1", description: "Grab Flash Bank1 Sector 1", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_B1_SECT2", description: "Grab Flash Bank1 Sector 2", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_B1_SECT3", description: "Grab Flash Bank1 Sector 3", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_B1_SECT31_4", description: "Grab Flash Bank1 Sector 31-4", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_B1_SECT63_32", description: "Grab Flash Bank1 Sector 63-32", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_B1_SECT95_64", description: "Grab Flash Bank1 Sector 95-64", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_B1_SECT127_96", description: "Grab Flash Bank1 Sector 127-96", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z1_GRABSECT2R", description: "Zone 1 Grab Flash Status Register 2", offset: "0x1C",
		bits: [
			{ name: "GRAB_B2_SECT0", description: "Grab Flash Bank2 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_B2_SECT1", description: "Grab Flash Bank2 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_B2_SECT2", description: "Grab Flash Bank2 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_B2_SECT3", description: "Grab Flash Bank2 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_B2_SECT31_4", description: "Grab Flash Bank2 Sector 31-4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_B2_SECT63_32", description: "Grab Flash Bank2 Sector 63-32", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_B2_SECT95_64", description: "Grab Flash Bank2 Sector 95-64", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_B2_SECT127_96", description: "Grab Flash Bank2 Sector 127-96", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_B3_SECT0", description: "Grab Flash Bank3 Sector 0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_B3_SECT1", description: "Grab Flash Bank3 Sector 1", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_B3_SECT2", description: "Grab Flash Bank3 Sector 2", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_B3_SECT3", description: "Grab Flash Bank3 Sector 3", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_B3_SECT31_4", description: "Grab Flash Bank3 Sector 31-4", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_B3_SECT63_32", description: "Grab Flash Bank3 Sector 63-32", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_B3_SECT95_64", description: "Grab Flash Bank3 Sector 95-64", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_B3_SECT127_96", description: "Grab Flash Bank3 Sector 127-96", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z1_GRABSECT3R", description: "Zone 1 Grab Flash Status Register 3", offset: "0x1E",
		bits: [
			{ name: "GRAB_B4_SECT0", description: "Grab Flash Bank4 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_B4_SECT1", description: "Grab Flash Bank4 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_B4_SECT2", description: "Grab Flash Bank4 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_B4_SECT3", description: "Grab Flash Bank4 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_B4_SECT31_4", description: "Grab Flash Bank4 Sector 31-4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_B4_SECT63_32", description: "Grab Flash Bank4 Sector 63-32", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_B4_SECT95_64", description: "Grab Flash Bank4 Sector 95-64", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_B4_SECT127_96", description: "Grab Flash Bank4 Sector 127-96", size: "2", shift: "14", mask: "0xC000" },
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
			{ name: "GRAB_RAM8", description: "Grab RAM CPU1.LS8", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_RAM9", description: "Grab RAM CPU1.LS9", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_RAM10", description: "Grab RAM D0", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_RAM11", description: "Grab RAM D1", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_RAM12", description: "Grab RAM D2", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_RAM13", description: "Grab RAM D3", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_RAM14", description: "Grab RAM D4", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_RAM15", description: "Grab RAM D5", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z1_GRABRAM2R", description: "Zone 1 Grab RAM Status Register 2", offset: "0x22",
		bits: [
			{ name: "GRAB_RAM12", description: "Grab RAM CPU1TOCPU2 MSGRAM0_L", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM13", description: "Grab RAM CPU1TOCPU2 MSGRAM0_H", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM14", description: "Grab RAM CPU2TOCPU1 MSGRAM0_L", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_RAM15", description: "Grab RAM CPU2TOCPU1 MSGRAM0_H", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "Z1_EXEONLYSECT1R", description: "Zone 1 Execute Only Flash Status Register 1", offset: "0x26",
		bits: [
			{ name: "EXEONLY_B0_SECT0", description: "Execute-Only Flash Bank0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_B0_SECT1", description: "Execute-Only Flash Bank0", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_B0_SECT2", description: "Execute-Only Flash Bank0", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_B0_SECT3", description: "Execute-Only Flash Bank0", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_B0_SECT31_4", description: "Execute-Only Flash Bank0", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_B0_SECT63_32", description: "Execute-Only Flash Bank0", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_B0_SECT95_64", description: "Execute-Only Flash Bank0", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_B0_SECT127_96", description: "Execute-Only Flash Bank0", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_B1_SECT0", description: "Execute-Only Flash Bank1", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_B1_SECT1", description: "Execute-Only Flash Bank1", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_B1_SECT2", description: "Execute-Only Flash Bank1", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_B1_SECT3", description: "Execute-Only Flash Bank1", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_B1_SECT31_4", description: "Execute-Only Flash Bank1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_B1_SECT63_32", description: "Execute-Only Flash Bank1", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_B1_SECT95_64", description: "Execute-Only Flash Bank1", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_B1_SECT127_96", description: "Execute-Only Flash Bank1", size: "1", shift: "15", mask: "0x8000" },
			{ name: "EXEONLY_B2_SECT0", description: "Execute-Only Flash Bank2", size: "1", shift: "16", mask: "0x10000" },
			{ name: "EXEONLY_B2_SECT1", description: "Execute-Only Flash Bank2", size: "1", shift: "17", mask: "0x20000" },
			{ name: "EXEONLY_B2_SECT2", description: "Execute-Only Flash Bank2", size: "1", shift: "18", mask: "0x40000" },
			{ name: "EXEONLY_B2_SECT3", description: "Execute-Only Flash Bank2", size: "1", shift: "19", mask: "0x80000" },
			{ name: "EXEONLY_B2_SECT31_4", description: "Execute-Only Flash Bank2", size: "1", shift: "20", mask: "0x100000" },
			{ name: "EXEONLY_B2_SECT63_32", description: "Execute-Only Flash Bank2", size: "1", shift: "21", mask: "0x200000" },
			{ name: "EXEONLY_B2_SECT95_64", description: "Execute-Only Flash Bank2", size: "1", shift: "22", mask: "0x400000" },
			{ name: "EXEONLY_B2_SECT127_96", description: "Execute-Only Flash Bank2", size: "1", shift: "23", mask: "0x800000" },
			{ name: "EXEONLY_B3_SECT0", description: "Execute-Only Flash Bank3", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "EXEONLY_B3_SECT1", description: "Execute-Only Flash Bank3", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "EXEONLY_B3_SECT2", description: "Execute-Only Flash Bank3", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "EXEONLY_B3_SECT3", description: "Execute-Only Flash Bank3", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "EXEONLY_B3_SECT31_4", description: "Execute-Only Flash Bank3", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "EXEONLY_B3_SECT63_32", description: "Execute-Only Flash Bank3", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "EXEONLY_B3_SECT95_64", description: "Execute-Only Flash Bank3", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "EXEONLY_B3_SECT127_96", description: "Execute-Only Flash Bank3", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "Z1_EXEONLYSECT2R", description: "Zone 1 Execute Only Flash Status Register 2", offset: "0x28",
		bits: [
			{ name: "EXEONLY_B4_SECT0", description: "Execute-Only Flash Bank4 Sector 0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_B4_SECT1", description: "Execute-Only Flash Bank4 Sector 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_B4_SECT2", description: "Execute-Only Flash Bank4 Sector 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_B4_SECT3", description: "Execute-Only Flash Bank4 Sector 3", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_B4_SECT31_4", description: "Execute-Only Flash Bank4 Sector", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_B4_SECT63_32", description: "Execute-Only Flash Bank4 Sector", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_B4_SECT95_64", description: "Execute-Only Flash Bank4 Sector", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_B4_SECT127_96", description: "Execute-Only Flash Bank4 Sector", size: "1", shift: "7", mask: "0x80" },
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
			{ name: "EXEONLY_RAM8", description: "Execute-Only RAM CPU1.LS8", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_RAM9", description: "Execute-Only RAM CPU1.LS9", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_RAM10", description: "Execute-Only RAM D0", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_RAM11", description: "Execute-Only RAM D1", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_RAM12", description: "Execute-Only RAM D2", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_RAM13", description: "Execute-Only RAM D3", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_RAM14", description: "Execute-Only RAM D4", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_RAM15", description: "Execute-Only RAM D5", size: "1", shift: "15", mask: "0x8000" },
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
	{ name: "Z1_DIAG", description: "Diagnostics Configuration Register", offset: "0x3E",
		bits: [
			{ name: "MPOST_EN", description: "MPOST Enable", size: "2", shift: "4", mask: "0x30" },
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
			{ name: "FORCESEC", description: "Force Secure", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "Z2_GRABSECT1R", description: "Zone 2 Grab Flash Status Register 1", offset: "0x1A",
		bits: [
			{ name: "GRAB_B0_SECT0", description: "Grab Flash Bank0 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_B0_SECT1", description: "Grab Flash Bank0 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_B0_SECT2", description: "Grab Flash Bank0 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_B0_SECT3", description: "Grab Flash Bank0 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_B0_SECT31_4", description: "Grab Flash Bank0 Sector 31-4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_B0_SECT63_32", description: "Grab Flash Bank0 Sector 63-32", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_B0_SECT95_64", description: "Grab Flash Bank0 Sector 95-64", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_B0_SECT127_96", description: "Grab Flash Bank1 Sector 127-96", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_B1_SECT0", description: "Grab Flash Bank1 Sector 0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_B1_SECT1", description: "Grab Flash Bank1 Sector 1", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_B1_SECT2", description: "Grab Flash Bank1 Sector 2", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_B1_SECT3", description: "Grab Flash Bank1 Sector 3", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_B1_SECT31_4", description: "Grab Flash Bank1 Sector 31-4", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_B1_SECT63_32", description: "Grab Flash Bank1 Sector 63-32", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_B1_SECT95_64", description: "Grab Flash Bank1 Sector 95-64", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_B1_SECT127_96", description: "Grab Flash Bank1 Sector 127-96", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z2_GRABSECT2R", description: "Zone 2 Grab Flash Status Register 2", offset: "0x1C",
		bits: [
			{ name: "GRAB_B2_SECT0", description: "Grab Flash Bank2 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_B2_SECT1", description: "Grab Flash Bank2 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_B2_SECT2", description: "Grab Flash Bank2 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_B2_SECT3", description: "Grab Flash Bank2 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_B2_SECT31_4", description: "Grab Flash Bank2 Sector 31-4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_B2_SECT63_32", description: "Grab Flash Bank2 Sector 63-32", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_B2_SECT95_64", description: "Grab Flash Bank2 Sector 95-64", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_B2_SECT127_96", description: "Grab Flash Bank2 Sector 127-96", size: "2", shift: "14", mask: "0xC000" },
			{ name: "GRAB_B3_SECT0", description: "Grab Flash Bank3 Sector 0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_B3_SECT1", description: "Grab Flash Bank3 Sector 1", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_B3_SECT2", description: "Grab Flash Bank3 Sector 2", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_B3_SECT3", description: "Grab Flash Bank3 Sector 3", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_B3_SECT31_4", description: "Grab Flash Bank3 Sector 31-4", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_B3_SECT63_32", description: "Grab Flash Bank3 Sector 63-32", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_B3_SECT95_64", description: "Grab Flash Bank3 Sector 95-64", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_B3_SECT127_96", description: "Grab Flash Bank3 Sector 127-96", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z2_GRABSECT3R", description: "Zone 2 Grab Flash Status Register 3", offset: "0x1E",
		bits: [
			{ name: "GRAB_B4_SECT0", description: "Grab Flash Bank4 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_B4_SECT1", description: "Grab Flash Bank4 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_B4_SECT2", description: "Grab Flash Bank4 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_B4_SECT3", description: "Grab Flash Bank4 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_B4_SECT31_4", description: "Grab Flash Bank4 Sector 31-4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_B4_SECT63_32", description: "Grab Flash Bank4 Sector 63-32", size: "2", shift: "10", mask: "0xC00" },
			{ name: "GRAB_B4_SECT95_64", description: "Grab Flash Bank4 Sector 95-64", size: "2", shift: "12", mask: "0x3000" },
			{ name: "GRAB_B4_SECT127_96", description: "Grab Flash Bank4 Sector 127-96", size: "2", shift: "14", mask: "0xC000" },
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
			{ name: "GRAB_RAM8", description: "Grab RAM CPU1.LS8", size: "2", shift: "16", mask: "0x30000" },
			{ name: "GRAB_RAM9", description: "Grab RAM CPU1.LS9", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "GRAB_RAM10", description: "Grab RAM D0", size: "2", shift: "20", mask: "0x300000" },
			{ name: "GRAB_RAM11", description: "Grab RAM D1", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "GRAB_RAM12", description: "Grab RAM D2", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "GRAB_RAM13", description: "Grab RAM D3", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "GRAB_RAM14", description: "Grab RAM D4", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "GRAB_RAM15", description: "Grab RAM D5", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "Z2_GRABRAM2R", description: "Zone 2 Grab RAM Status Register 2", offset: "0x22",
		bits: [
			{ name: "GRAB_RAM12", description: "Grab RAM CPU1TOCPU2 MSGRAM0_L", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_RAM13", description: "Grab RAM CPU1TOCPU2 MSGRAM0_H", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_RAM14", description: "Grab RAM CPU2TOCPU1 MSGRAM0_L", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_RAM15", description: "Grab RAM CPU2TOCPU1 MSGRAM0_H", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "Z2_EXEONLYSECT1R", description: "Zone 2 Execute Only Flash Status Register 1", offset: "0x26",
		bits: [
			{ name: "EXEONLY_B0_SECT0", description: "Execute-Only Flash Bank0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_B0_SECT1", description: "Execute-Only Flash Bank0", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_B0_SECT2", description: "Execute-Only Flash Bank0", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_B0_SECT3", description: "Execute-Only Flash Bank0", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_B0_SECT31_4", description: "Execute-Only Flash Bank0", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_B0_SECT63_32", description: "Execute-Only Flash Bank0", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_B0_SECT95_64", description: "Execute-Only Flash Bank0", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_B0_SECT127_96", description: "Execute-Only Flash Bank0", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXEONLY_B1_SECT0", description: "Execute-Only Flash Bank1", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_B1_SECT1", description: "Execute-Only Flash Bank1", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_B1_SECT2", description: "Execute-Only Flash Bank1", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_B1_SECT3", description: "Execute-Only Flash Bank1", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_B1_SECT31_4", description: "Execute-Only Flash Bank1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_B1_SECT63_32", description: "Execute-Only Flash Bank1", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_B1_SECT95_64", description: "Execute-Only Flash Bank1", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_B1_SECT127_96", description: "Execute-Only Flash Bank1", size: "1", shift: "15", mask: "0x8000" },
			{ name: "EXEONLY_B2_SECT0", description: "Execute-Only Flash Bank2", size: "1", shift: "16", mask: "0x10000" },
			{ name: "EXEONLY_B2_SECT1", description: "Execute-Only Flash Bank2", size: "1", shift: "17", mask: "0x20000" },
			{ name: "EXEONLY_B2_SECT2", description: "Execute-Only Flash Bank2", size: "1", shift: "18", mask: "0x40000" },
			{ name: "EXEONLY_B2_SECT3", description: "Execute-Only Flash Bank2", size: "1", shift: "19", mask: "0x80000" },
			{ name: "EXEONLY_B2_SECT31_4", description: "Execute-Only Flash Bank2", size: "1", shift: "20", mask: "0x100000" },
			{ name: "EXEONLY_B2_SECT63_32", description: "Execute-Only Flash Bank2", size: "1", shift: "21", mask: "0x200000" },
			{ name: "EXEONLY_B2_SECT95_64", description: "Execute-Only Flash Bank2", size: "1", shift: "22", mask: "0x400000" },
			{ name: "EXEONLY_B2_SECT127_96", description: "Execute-Only Flash Bank2", size: "1", shift: "23", mask: "0x800000" },
			{ name: "EXEONLY_B3_SECT0", description: "Execute-Only Flash Bank3", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "EXEONLY_B3_SECT1", description: "Execute-Only Flash Bank3", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "EXEONLY_B3_SECT2", description: "Execute-Only Flash Bank3", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "EXEONLY_B3_SECT3", description: "Execute-Only Flash Bank3", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "EXEONLY_B3_SECT31_4", description: "Execute-Only Flash Bank3", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "EXEONLY_B3_SECT63_32", description: "Execute-Only Flash Bank3", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "EXEONLY_B3_SECT95_64", description: "Execute-Only Flash Bank3", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "EXEONLY_B3_SECT127_96", description: "Execute-Only Flash Bank3", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "Z2_EXEONLYSECT2R", description: "Zone 2 Execute Only Flash Status Register 2", offset: "0x28",
		bits: [
			{ name: "EXEONLY_B4_SECT0", description: "Execute-Only Flash Bank4 Sector 0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_B4_SECT1", description: "Execute-Only Flash Bank4 Sector 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_B4_SECT2", description: "Execute-Only Flash Bank4 Sector 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_B4_SECT3", description: "Execute-Only Flash Bank4 Sector 3", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_B4_SECT31_4", description: "Execute-Only Flash Bank4 Sector", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_B4_SECT63_32", description: "Execute-Only Flash Bank4 Sector", size: "1", shift: "5", mask: "0x20" },
			{ name: "EXEONLY_B4_SECT95_64", description: "Execute-Only Flash Bank4 Sector", size: "1", shift: "6", mask: "0x40" },
			{ name: "EXEONLY_B4_SECT127_96", description: "Execute-Only Flash Bank4 Sector", size: "1", shift: "7", mask: "0x80" },
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
			{ name: "EXEONLY_RAM8", description: "Execute-Only RAM CPU1.LS8", size: "1", shift: "8", mask: "0x100" },
			{ name: "EXEONLY_RAM9", description: "Execute-Only RAM CPU1.LS9", size: "1", shift: "9", mask: "0x200" },
			{ name: "EXEONLY_RAM10", description: "Execute-Only RAM D0", size: "1", shift: "10", mask: "0x400" },
			{ name: "EXEONLY_RAM11", description: "Execute-Only RAM D1", size: "1", shift: "11", mask: "0x800" },
			{ name: "EXEONLY_RAM12", description: "Execute-Only RAM D2", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EXEONLY_RAM13", description: "Execute-Only RAM D3", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXEONLY_RAM14", description: "Execute-Only RAM D4", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EXEONLY_RAM15", description: "Execute-Only RAM D5", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "FLSEM", description: "Flash Wrapper Semaphore Register", offset: "0x0",
		bits: [
			{ name: "SEM", description: "Flash Semaphore Bit", size: "2", shift: "0", mask: "0x3" },
			{ name: "KEY", description: "Semaphore Key", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "BOOTERR", description: "Boot Error Register", offset: "0x6",
		bits: [
			{ name: "ILLTRIMPSWD", description: "Illegal Trim Password", size: "1", shift: "0", mask: "0x1" },
			{ name: "TRIMPSWDERR", description: "Trim Password Error", size: "1", shift: "1", mask: "0x2" },
			{ name: "SELOVRD", description: "Password Select Override", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "SECTSTAT1", description: "Flash Sectors Status Register 1", offset: "0x8",
		bits: [
			{ name: "STATUS_B0_SECT0", description: "Zone Status Flash Bank0 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_B0_SECT1", description: "Zone Status Flash Bank0 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_B0_SECT2", description: "Zone Status Flash Bank0 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_B0_SECT3", description: "Zone Status Flash Bank0 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_B0_SECT31_4", description: "Zone Status Flash Bank0 Sector", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_B0_SECT63_32", description: "Zone Status Flash Bank0 Sector", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_B0_SECT95_64", description: "Zone Status Flash Bank0 Sector", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_B0_SECT127_96", description: "Zone Status Flash Bank0 Sector", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_B1_SECT0", description: "Zone Status Flash Bank1 Sector 0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_B1_SECT1", description: "Zone Status Flash Bank1 Sector 1", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_B1_SECT2", description: "Zone Status Flash Bank1 Sector 2", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_B1_SECT3", description: "Zone Status Flash Bank1 Sector 3", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_B1_SECT31_4", description: "Zone Status Flash Bank1 Sector", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_B1_SECT63_32", description: "Zone Status Flash Bank1 Sector", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "STATUS_B1_SECT95_64", description: "Zone Status Flash Bank1 Sector", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "STATUS_B1_SECT127_96", description: "Zone Status Flash Bank1 Sector", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "SECTSTAT2", description: "Flash Sectors Status Register 2", offset: "0xA",
		bits: [
			{ name: "STATUS_B2_SECT0", description: "Zone Status Flash Bank2 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_B2_SECT1", description: "Zone Status Flash Bank2 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_B2_SECT2", description: "Zone Status Flash Bank2 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_B2_SECT3", description: "Zone Status Flash Bank2 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_B2_SECT31_4", description: "Zone Status Flash Bank2 Sector", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_B2_SECT63_32", description: "Zone Status Flash Bank2 Sector", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_B2_SECT95_64", description: "Zone Status Flash Bank2 Sector", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_B2_SECT127_96", description: "Zone Status Flash Bank2 Sector", size: "2", shift: "14", mask: "0xC000" },
			{ name: "STATUS_B3_SECT0", description: "Zone Status Flash Bank3 Sector 0", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_B3_SECT1", description: "Zone Status Flash Bank3 Sector 1", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_B3_SECT2", description: "Zone Status Flash Bank3 Sector 2", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_B3_SECT3", description: "Zone Status Flash Bank3 Sector 3", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_B3_SECT31_4", description: "Zone Status Flash Bank3 Sector", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_B3_SECT63_32", description: "Zone Status Flash Bank3 Sector", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "STATUS_B3_SECT95_64", description: "Zone Status Flash Bank3 Sector", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "STATUS_B3_SECT127_96", description: "Zone Status Flash Bank3 Sector", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "SECTSTAT3", description: "Flash Sectors Status Register 3", offset: "0xC",
		bits: [
			{ name: "STATUS_B4_SECT0", description: "Zone Status Flash Bank4 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_B4_SECT1", description: "Zone Status Flash Bank4 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_B4_SECT2", description: "Zone Status Flash Bank4 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_B4_SECT3", description: "Zone Status Flash Bank4 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_B4_SECT31_4", description: "Zone Status Flash Bank4 Sector 31-4", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_B4_SECT63_32", description: "Zone Status Flash Bank4 Sector 63-32", size: "2", shift: "10", mask: "0xC00" },
			{ name: "STATUS_B4_SECT95_64", description: "Zone Status Flash Bank4 Sector 95-64", size: "2", shift: "12", mask: "0x3000" },
			{ name: "STATUS_B4_SECT127_96", description: "Zone Status Flash Bank4 Sector 127-96", size: "2", shift: "14", mask: "0xC000" },
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
			{ name: "STATUS_RAM8", description: "Zone Status RAM CPU1.LS8", size: "2", shift: "16", mask: "0x30000" },
			{ name: "STATUS_RAM9", description: "Zone Status RAM CPU1.LS9", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "STATUS_RAM10", description: "Zone Status RAM D0", size: "2", shift: "20", mask: "0x300000" },
			{ name: "STATUS_RAM11", description: "Zone Status RAM D1", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "STATUS_RAM12", description: "Zone Status RAM D2", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "STATUS_RAM13", description: "Zone Status RAM D3", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "STATUS_RAM14", description: "Zone Status RAM D4", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "STATUS_RAM15", description: "Zone Status RAM D5", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "RAMSTAT2", description: "RAM Status Register 2", offset: "0x12",
		bits: [
			{ name: "STATUS_RAM12", description: "Zone Status RAM CPU1TOCPU2 MSGRAM0_L", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_RAM13", description: "Zone Status RAM CPU1TOCPU2 MSGRAM0_H", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_RAM14", description: "Zone Status RAM CPU2TOCPU1 MSGRAM0_L", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_RAM15", description: "Zone Status RAM CPU2TOCPU1 MSGRAM0_H", size: "2", shift: "6", mask: "0xC0" },
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
	{ name: "UID_UNIQUE_31_0", description: "Unique Identification Number", offset: "0x28",
		bits: [
		]
	},
	{ name: "UID_UNIQUE_63_32", description: "Part Identification High Register", offset: "0x2A",
		bits: [
		]
	},
	{ name: "PARTIDH", description: "Part Identification High Register", offset: "0x2C",
		bits: [
		]
	},
	{ name: "PERSEM1", description: "Peripheral Semaphore Register", offset: "0x2E",
		bits: [
			{ name: "GRABWD", description: "Grab Watchdog module", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRABNMIWD", description: "GRAB NMIWD module", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRABTIMER1", description: "Grab TIMER1 module", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRABCLKCTL", description: "Grab Clock Configuration", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRABRSTCTL", description: "Grab Reset Configuration", size: "2", shift: "8", mask: "0x300" },
			{ name: "KEY", description: "Semaphore Key", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
];
module.exports = {
	DCSMRegisters: DCSMRegisters,
}
