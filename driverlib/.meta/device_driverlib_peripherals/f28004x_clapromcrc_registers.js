let CLAPROMCRCRegisters = [
	{ name: "CRC32_CONTROLREG", description: "CRC32-Control Register", offset: "0x0",
		bits: [
			{ name: "START", description: "Start Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "FREE_SOFT", description: "emulation control bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "HALT", description: "Halt Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "BLOCKSIZE", description: "Block size of ROM for which CRC is", size: "7", shift: "16", mask: "0x7F0000" },
		]
	},
	{ name: "CRC32_STARTADDRESS", description: "CRC32-Start address register", offset: "0x2",
		bits: [
		]
	},
	{ name: "CRC32_SEED", description: "CRC32-Seed Register", offset: "0x4",
		bits: [
		]
	},
	{ name: "CRC32_STATUSREG", description: "CRC32-Status Register", offset: "0x6",
		bits: [
			{ name: "CURRENTADDR", description: "Point to the data fetch unit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "CRCCHECKSTATUS", description: "CRC active status", size: "1", shift: "23", mask: "0x800000" },
			{ name: "RUNSTATUS", description: "CRC active status", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "CRC32_CRCRESULT", description: "CRC32-CRC result Register", offset: "0x8",
		bits: [
		]
	},
	{ name: "CRC32_GOLDENCRC", description: "CRC32-Golden CRC register", offset: "0xA",
		bits: [
		]
	},
	{ name: "CRC32_INTEN", description: "CRC32-Interrupt enable register", offset: "0x18",
		bits: [
			{ name: "CRCDONE", description: "CRCDONE interrupt enable register", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CRC32_FLG", description: "CRC32-Interrupt Flag Register", offset: "0x1A",
		bits: [
			{ name: "INT", description: "Global Interrupt status flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CRCDONE", description: "CRCDONE Interrupt status flag", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CRC32_CLR", description: "CRC32-Interrupt Clear Register", offset: "0x1C",
		bits: [
			{ name: "INT", description: "Global Interrupt clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "CRCDONE", description: "CRCDONE Interrupt clear", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CRC32_FRC", description: "CRC32-Interrupt Force Register", offset: "0x1E",
		bits: [
			{ name: "CRCDONE", description: "CRCDONE Interrupt force", size: "1", shift: "1", mask: "0x2" },
		]
	},
];
module.exports = {
	CLAPROMCRCRegisters: CLAPROMCRCRegisters,
}
