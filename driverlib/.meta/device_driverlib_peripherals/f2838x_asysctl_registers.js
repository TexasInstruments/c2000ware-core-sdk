let ASYSCTLRegisters = [
	{ name: "INTOSC1TRIM", description: "Internal Oscillator 1 Trim Register", offset: "0x20",
		bits: [
			{ name: "VALFINETRIM", description: "Oscillator Value Fine Trim Bits", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "INTOSC2TRIM", description: "Internal Oscillator 2 Trim Register", offset: "0x22",
		bits: [
			{ name: "VALFINETRIM", description: "Oscillator Value Fine Trim Bits", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "TSNSCTL", description: "Temperature Sensor Control Register", offset: "0x26",
		bits: [
			{ name: "ENABLE", description: "Temperature Sensor Enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "LOCK", description: "Lock Register", offset: "0x2E",
		bits: [
			{ name: "TSNSCTL", description: "Temperature Sensor Control Register Lock", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "ANAREFTRIMA", description: "Analog Reference Trim A Register", offset: "0x36",
		bits: [
			{ name: "BGVALTRIM", description: "Bandgap Value Trim", size: "6", shift: "0", mask: "0x3F" },
			{ name: "BGSLOPETRIM", description: "Bandgap Slope Trim", size: "5", shift: "6", mask: "0x7C0" },
			{ name: "IREFTRIM", description: "Reference Current Trim", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "ANAREFTRIMB", description: "Analog Reference Trim B Register", offset: "0x38",
		bits: [
			{ name: "BGVALTRIM", description: "Bandgap Value Trim", size: "6", shift: "0", mask: "0x3F" },
			{ name: "BGSLOPETRIM", description: "Bandgap Slope Trim", size: "5", shift: "6", mask: "0x7C0" },
			{ name: "IREFTRIM", description: "Reference Current Trim", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "ANAREFTRIMC", description: "Analog Reference Trim C Register", offset: "0x3A",
		bits: [
			{ name: "BGVALTRIM", description: "Bandgap Value Trim", size: "6", shift: "0", mask: "0x3F" },
			{ name: "BGSLOPETRIM", description: "Bandgap Slope Trim", size: "5", shift: "6", mask: "0x7C0" },
			{ name: "IREFTRIM", description: "Reference Current Trim", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "ANAREFTRIMD", description: "Analog Reference Trim D Register", offset: "0x3C",
		bits: [
			{ name: "BGVALTRIM", description: "Bandgap Value Trim", size: "6", shift: "0", mask: "0x3F" },
			{ name: "BGSLOPETRIM", description: "Bandgap Slope Trim", size: "5", shift: "6", mask: "0x7C0" },
			{ name: "IREFTRIM", description: "Reference Current Trim", size: "5", shift: "11", mask: "0xF800" },
		]
	},
];
module.exports = {
	ASYSCTLRegisters: ASYSCTLRegisters,
}
