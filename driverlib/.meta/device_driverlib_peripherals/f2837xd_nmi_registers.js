let NMIRegisters = [
	{ name: "CFG", description: "NMI Configuration Register", offset: "0x0",
		bits: [
			{ name: "NMIE", description: "Global NMI Enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "FLG", description: "NMI Flag Register (XRSn Clear)", offset: "0x1",
		bits: [
			{ name: "NMIINT", description: "NMI Interrupt Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLOCKFAIL", description: "Clock Fail Interrupt Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "RAMUNCERR", description: "RAM Uncorrectable Error NMI Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "FLUNCERR", description: "Flash Uncorrectable Error NMI Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "CPU1HWBISTERR", description: "HW BIST Error NMI Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "CPU2HWBISTERR", description: "HW BIST Error NMI Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "PIEVECTERR", description: "PIE Vector Fetch Error Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "CLBNMI", description: "Configurable Logic Block NMI Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPU2WDRSN", description: "CPU2 WDRSn Reset Indication Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "CPU2NMIWDRSN", description: "CPU2 NMIWDRSn Reset Indication Flag", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "FLGCLR", description: "NMI Flag Clear Register", offset: "0x2",
		bits: [
			{ name: "NMIINT", description: "NMIINT Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLOCKFAIL", description: "CLOCKFAIL Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "RAMUNCERR", description: "RAMUNCERR Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "FLUNCERR", description: "FLUNCERR Flag Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "CPU1HWBISTERR", description: "CPU1HWBISTERR Flag Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "CPU2HWBISTERR", description: "CPU2HWBISTERR Flag Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "PIEVECTERR", description: "PIEVECTERR Flag Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "CLBNMI", description: "CLBNMI Flag Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPU2WDRSN", description: "CPU2WDRSn Flag Clear", size: "1", shift: "9", mask: "0x200" },
			{ name: "CPU2NMIWDRSN", description: "CPU2NMIWDRSn Flag Clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "OVF", description: "OVF Flag Clear", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "FLGFRC", description: "NMI Flag Force Register", offset: "0x3",
		bits: [
			{ name: "CLOCKFAIL", description: "CLOCKFAIL Flag Force", size: "1", shift: "1", mask: "0x2" },
			{ name: "RAMUNCERR", description: "RAMUNCERR Flag Force", size: "1", shift: "2", mask: "0x4" },
			{ name: "FLUNCERR", description: "FLUNCERR Flag Force", size: "1", shift: "3", mask: "0x8" },
			{ name: "CPU1HWBISTERR", description: "CPU1HWBISTERR Flag Force", size: "1", shift: "4", mask: "0x10" },
			{ name: "CPU2HWBISTERR", description: "CPU2HWBISTERR Flag Force", size: "1", shift: "5", mask: "0x20" },
			{ name: "PIEVECTERR", description: "PIEVECTERR Flag Force", size: "1", shift: "6", mask: "0x40" },
			{ name: "CLBNMI", description: "CLBNMI Flag Force", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPU2WDRSN", description: "CPU2WDRSn Flag Force", size: "1", shift: "9", mask: "0x200" },
			{ name: "CPU2NMIWDRSN", description: "CPU2NMIWDRSn Flag Force", size: "1", shift: "10", mask: "0x400" },
			{ name: "OVF", description: "OVF Flag Force", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "WDCNT", description: "NMI Watchdog Counter Register", offset: "0x4",
		bits: [
		]
	},
	{ name: "WDPRD", description: "NMI Watchdog Period Register", offset: "0x5",
		bits: [
		]
	},
	{ name: "SHDFLG", description: "NMI Shadow Flag Register", offset: "0x6",
		bits: [
			{ name: "CLOCKFAIL", description: "Shadow CLOCKFAIL Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "RAMUNCERR", description: "Shadow RAMUNCERR Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "FLUNCERR", description: "Shadow FLUNCERR Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "CPU1HWBISTERR", description: "Shadow CPU1HWBISTERR Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "CPU2HWBISTERR", description: "Shadow CPU2HWBISTERR Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "PIEVECTERR", description: "Shadow PIEVECTERR Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "CLBNMI", description: "Shadow CLBNMI Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPU2WDRSN", description: "Shadow CPU2WDRSn Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "CPU2NMIWDRSN", description: "Shadow CPU2NMIWDRSn Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "OVF", description: "Shadow OVF Flag", size: "1", shift: "11", mask: "0x800" },
		]
	},
];
module.exports = {
	NMIRegisters: NMIRegisters,
}
