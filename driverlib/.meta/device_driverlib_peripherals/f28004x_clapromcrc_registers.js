let CLAPROMCRCRegisters = [
	{ name: "_CONTROLREG", description: "CRC32-Control Register", offset: "0x0",
		bits: [
		]
	},
	{ name: "_STARTADDRESS", description: "CRC32-Start address register", offset: "0x2",
		bits: [
		]
	},
	{ name: "_SEED", description: "CRC32-Seed Register", offset: "0x4",
		bits: [
		]
	},
	{ name: "_STATUSREG", description: "CRC32-Status Register", offset: "0x6",
		bits: [
		]
	},
	{ name: "_CRCRESULT", description: "CRC32-CRC result Register", offset: "0x8",
		bits: [
		]
	},
	{ name: "_GOLDENCRC", description: "CRC32-Golden CRC register", offset: "0xA",
		bits: [
		]
	},
	{ name: "_INTEN", description: "CRC32-Interrupt enable register", offset: "0x18",
		bits: [
		]
	},
	{ name: "_FLG", description: "CRC32-Interrupt Flag Register", offset: "0x1A",
		bits: [
		]
	},
	{ name: "_CLR", description: "CRC32-Interrupt Clear Register", offset: "0x1C",
		bits: [
		]
	},
	{ name: "_FRC", description: "CRC32-Interrupt Force Register", offset: "0x1E",
		bits: [
		]
	},
];
module.exports = {
	CLAPROMCRCRegisters: CLAPROMCRCRegisters,
}
