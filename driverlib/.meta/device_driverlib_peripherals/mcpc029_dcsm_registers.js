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
			{ name: "GRAB_B0_SECT0", description: "Grab Flash Bank0 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_B0_SECT1", description: "Grab Flash Bank0 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_B0_SECT2", description: "Grab Flash Bank0 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_B0_SECT3", description: "Grab Flash Bank0 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_B0_SECT31_4", description: "Grab Flash Bank0 Sector 31-4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_B0_SECT63_32", description: "Grab Flash Bank0 Sector 63-32", size: "2", shift: "10", mask: "0xC00" },
		]
	},
	{ name: "Z1_EXEONLYSECT1R", description: "Zone 1 Execute Only Flash Status Register 1", offset: "0x26",
		bits: [
			{ name: "EXEONLY_B0_SECT0", description: "Execute-Only Flash Bank0 Sector 0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_B0_SECT1", description: "Execute-Only Flash Bank0 Sector 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_B0_SECT2", description: "Execute-Only Flash Bank0 Sector 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_B0_SECT3", description: "Execute-Only Flash Bank0 Sector 3", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_B0_SECT31_4", description: "Execute-Only Flash Bank0 Sector", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_B0_SECT63_32", description: "Execute-Only Flash Bank0 Sector", size: "1", shift: "5", mask: "0x20" },
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
			{ name: "GRAB_B0_SECT0", description: "Grab Flash Bank0 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "GRAB_B0_SECT1", description: "Grab Flash Bank0 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "GRAB_B0_SECT2", description: "Grab Flash Bank0 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRAB_B0_SECT3", description: "Grab Flash Bank0 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "GRAB_B0_SECT31_4", description: "Grab Flash Bank0 Sector 31-4", size: "2", shift: "8", mask: "0x300" },
			{ name: "GRAB_B0_SECT63_32", description: "Grab Flash Bank0 Sector 63-32", size: "2", shift: "10", mask: "0xC00" },
		]
	},
	{ name: "Z2_EXEONLYSECT1R", description: "Zone 2 Execute Only Flash Status Register 1", offset: "0x26",
		bits: [
			{ name: "EXEONLY_B0_SECT0", description: "Execute-Only Flash Bank0 Sector 0", size: "1", shift: "0", mask: "0x1" },
			{ name: "EXEONLY_B0_SECT1", description: "Execute-Only Flash Bank0 Sector 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXEONLY_B0_SECT2", description: "Execute-Only Flash Bank0 Sector 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXEONLY_B0_SECT3", description: "Execute-Only Flash Bank0 Sector 3", size: "1", shift: "3", mask: "0x8" },
			{ name: "EXEONLY_B0_SECT31_4", description: "Execute-Only Flash Bank0 Sector", size: "1", shift: "4", mask: "0x10" },
			{ name: "EXEONLY_B0_SECT63_32", description: "Execute-Only Flash Bank0 Sector", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "SECTSTAT1", description: "Flash Sectors Status Register 1", offset: "0x8",
		bits: [
			{ name: "STATUS_B0_SECT0", description: "Zone Status Flash Bank0 Sector 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "STATUS_B0_SECT1", description: "Zone Status Flash Bank0 Sector 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "STATUS_B0_SECT2", description: "Zone Status Flash Bank0 Sector 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "STATUS_B0_SECT3", description: "Zone Status Flash Bank0 Sector 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "STATUS_B0_SECT31_4", description: "Zone Status Flash Bank0 Sector 31-4", size: "2", shift: "8", mask: "0x300" },
			{ name: "STATUS_B0_SECT63_32", description: "Zone Status Flash Bank0 Sector 63-32", size: "2", shift: "10", mask: "0xC00" },
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
	{ name: "UID_UNIQUE_31_0", description: "Unique Identification Number Low", offset: "0x28",
		bits: [
		]
	},
	{ name: "UID_UNIQUE_63_32", description: "Unique Identification Number High", offset: "0x2A",
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
