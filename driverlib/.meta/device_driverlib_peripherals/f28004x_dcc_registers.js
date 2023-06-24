let DCCRegisters = [
	{ name: "GCTRL", description: "Global Control Register", offset: "0x0",
		bits: [
			{ name: "DCCENA", description: "DCC Enable", size: "4", shift: "0", mask: "0xF" },
			{ name: "ERRENA", description: "Error Enable", size: "4", shift: "4", mask: "0xF0" },
			{ name: "SINGLESHOT", description: "Single-Shot Enable", size: "4", shift: "8", mask: "0xF00" },
			{ name: "DONEENA", description: "DONE Enable", size: "4", shift: "12", mask: "0xF000" },
		]
	},
	{ name: "REV", description: "DCC Revision Register", offset: "0x4",
		bits: [
			{ name: "MINOR", description: "Minor Revision Number", size: "6", shift: "0", mask: "0x3F" },
			{ name: "MAJOR", description: "Major Revision Number", size: "3", shift: "8", mask: "0x700" },
		]
	},
	{ name: "CNTSEED0", description: "Counter 0 Seed Value", offset: "0x8",
		bits: [
			{ name: "COUNTSEED0", description: "Seed Value for Counter 0", size: "20", shift: "0", mask: "0xFFFFF" },
		]
	},
	{ name: "VALIDSEED0", description: "Valid 0 Seed Value", offset: "0xC",
		bits: [
			{ name: "VALIDSEED", description: "Seed Value for Valid Duration Counter 0", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "CNTSEED1", description: "Counter 1 Seed Value", offset: "0x10",
		bits: [
			{ name: "COUNTSEED1", description: "Seed Value for Counter 1", size: "20", shift: "0", mask: "0xFFFFF" },
		]
	},
	{ name: "STATUS", description: "DCC Status", offset: "0x14",
		bits: [
			{ name: "ERR", description: "Error Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "DONE", description: "Single-Shot Done Flag", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CNT0", description: "Counter 0 Value", offset: "0x18",
		bits: [
			{ name: "COUNT0", description: "Current Value of Counter 0", size: "20", shift: "0", mask: "0xFFFFF" },
		]
	},
	{ name: "VALID0", description: "Valid Value 0", offset: "0x1C",
		bits: [
			{ name: "VALID0", description: "Current Value of Valid 0", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "CNT1", description: "Counter 1 Value", offset: "0x20",
		bits: [
			{ name: "COUNT1", description: "Current Value of Counter 1", size: "20", shift: "0", mask: "0xFFFFF" },
		]
	},
	{ name: "CLKSRC1", description: "Clock Source 1", offset: "0x24",
		bits: [
			{ name: "CLKSRC1", description: "Clock Source Select for Counter 1", size: "4", shift: "0", mask: "0xF" },
			{ name: "KEY", description: "Enables or Disables Clock Source Selection for COUNT1", size: "4", shift: "12", mask: "0xF000" },
		]
	},
	{ name: "CLKSRC0", description: "Clock Source 0", offset: "0x28",
		bits: [
			{ name: "CLKSRC0", description: "Clock Source Select for Counter 0", size: "4", shift: "0", mask: "0xF" },
		]
	},
];
module.exports = {
	DCCRegisters: DCCRegisters,
}
