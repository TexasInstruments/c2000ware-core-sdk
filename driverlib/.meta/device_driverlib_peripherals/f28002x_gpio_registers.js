let GPIORegisters = [
	{ name: "TRL", description: "GPIO A Qualification Sampling Period Control (GPIO0 to 31)", offset: "0x0",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO A Qualifier Select 1 Register (GPIO0 to 15)", offset: "0x2",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO A Qualifier Select 2 Register (GPIO16 to 31)", offset: "0x4",
		bits: [
		]
	},
	{ name: "UX1", description: "GPIO A Mux 1 Register (GPIO0 to 15)", offset: "0x6",
		bits: [
		]
	},
	{ name: "UX2", description: "GPIO A Mux 2 Register (GPIO16 to 31)", offset: "0x8",
		bits: [
		]
	},
	{ name: "IR", description: "GPIO A Direction Register (GPIO0 to 31)", offset: "0xA",
		bits: [
		]
	},
	{ name: "UD", description: "GPIO A Pull Up Disable Register (GPIO0 to 31)", offset: "0xC",
		bits: [
		]
	},
	{ name: "NV", description: "GPIO A Input Polarity Invert Registers (GPIO0 to 31)", offset: "0x10",
		bits: [
		]
	},
	{ name: "DR", description: "GPIO A Open Drain Output Register (GPIO0 to GPIO31)", offset: "0x12",
		bits: [
		]
	},
	{ name: "MUX1", description: "GPIO A Peripheral Group Mux (GPIO0 to 15)", offset: "0x20",
		bits: [
		]
	},
	{ name: "MUX2", description: "GPIO A Peripheral Group Mux (GPIO16 to 31)", offset: "0x22",
		bits: [
		]
	},
	{ name: "OCK", description: "GPIO A Lock Configuration Register (GPIO0 to 31)", offset: "0x3C",
		bits: [
		]
	},
	{ name: "R", description: "GPIO A Lock Commit Register (GPIO0 to 31)", offset: "0x3E",
		bits: [
		]
	},
	{ name: "TRL", description: "GPIO B Qualification Sampling Period Control (GPIO32 to 63)", offset: "0x40",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO B Qualifier Select 1 Register (GPIO32 to 47)", offset: "0x42",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO B Qualifier Select 2 Register (GPIO48 to 63)", offset: "0x44",
		bits: [
		]
	},
	{ name: "UX1", description: "GPIO B Mux 1 Register (GPIO32 to 47)", offset: "0x46",
		bits: [
		]
	},
	{ name: "UX2", description: "GPIO B Mux 2 Register (GPIO48 to 63)", offset: "0x48",
		bits: [
		]
	},
	{ name: "IR", description: "GPIO B Direction Register (GPIO32 to 63)", offset: "0x4A",
		bits: [
		]
	},
	{ name: "UD", description: "GPIO B Pull Up Disable Register (GPIO32 to 63)", offset: "0x4C",
		bits: [
		]
	},
	{ name: "NV", description: "GPIO B Input Polarity Invert Registers (GPIO32 to 63)", offset: "0x50",
		bits: [
		]
	},
	{ name: "DR", description: "GPIO B Open Drain Output Register (GPIO32 to GPIO63)", offset: "0x52",
		bits: [
		]
	},
	{ name: "MUX1", description: "GPIO B Peripheral Group Mux (GPIO32 to 47)", offset: "0x60",
		bits: [
		]
	},
	{ name: "MUX2", description: "GPIO B Peripheral Group Mux (GPIO48 to 63)", offset: "0x62",
		bits: [
		]
	},
	{ name: "OCK", description: "GPIO B Lock Configuration Register (GPIO32 to 63)", offset: "0x7C",
		bits: [
		]
	},
	{ name: "R", description: "GPIO B Lock Commit Register (GPIO32 to 63)", offset: "0x7E",
		bits: [
		]
	},
	{ name: "TRL", description: "GPIO H Qualification Sampling Period Control (GPIO224 to 255)", offset: "0x1C0",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO H Qualifier Select 1 Register (GPIO224 to 239)", offset: "0x1C2",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO H Qualifier Select 2 Register (GPIO240 to 255)", offset: "0x1C4",
		bits: [
		]
	},
	{ name: "UX1", description: "GPIO H Mux 1 Register (GPIO224 to 239)", offset: "0x1C6",
		bits: [
		]
	},
	{ name: "UX2", description: "GPIO H Mux 2 Register (GPIO240 to 255)", offset: "0x1C8",
		bits: [
		]
	},
	{ name: "NV", description: "GPIO H Input Polarity Invert Registers (GPIO224 to 255)", offset: "0x1D0",
		bits: [
		]
	},
	{ name: "MSEL", description: "GPIO H Analog Mode Select register (GPIO224 to GPIO255)", offset: "0x1D4",
		bits: [
		]
	},
	{ name: "MUX1", description: "GPIO H Peripheral Group Mux (GPIO224 to 239)", offset: "0x1E0",
		bits: [
		]
	},
	{ name: "MUX2", description: "GPIO H Peripheral Group Mux (GPIO240 to 255)", offset: "0x1E2",
		bits: [
		]
	},
	{ name: "OCK", description: "GPIO H Lock Configuration Register (GPIO224 to 255)", offset: "0x1FC",
		bits: [
		]
	},
	{ name: "R", description: "GPIO H Lock Commit Register (GPIO224 to 255)", offset: "0x1FE",
		bits: [
		]
	},
	{ name: "AT", description: "GPIO A Data Register (GPIO0 to 31)", offset: "0x0",
		bits: [
		]
	},
	{ name: "ET", description: "GPIO A Data Set Register (GPIO0 to 31)", offset: "0x2",
		bits: [
		]
	},
	{ name: "LEAR", description: "GPIO A Data Clear Register (GPIO0 to 31)", offset: "0x4",
		bits: [
		]
	},
	{ name: "OGGLE", description: "GPIO A Data Toggle Register (GPIO0 to 31)", offset: "0x6",
		bits: [
		]
	},
	{ name: "AT", description: "GPIO B Data Register (GPIO32 to 63)", offset: "0x8",
		bits: [
		]
	},
	{ name: "ET", description: "GPIO B Data Set Register (GPIO32 to 63)", offset: "0xA",
		bits: [
		]
	},
	{ name: "LEAR", description: "GPIO B Data Clear Register (GPIO32 to 63)", offset: "0xC",
		bits: [
		]
	},
	{ name: "OGGLE", description: "GPIO B Data Toggle Register (GPIO32 to 63)", offset: "0xE",
		bits: [
		]
	},
	{ name: "AT", description: "GPIO H Data Register (GPIO224 to 255)", offset: "0x38",
		bits: [
		]
	},
	{ name: "AT_R", description: "GPIO A Data Read Register", offset: "0x0",
		bits: [
		]
	},
	{ name: "AT_R", description: "GPIO B Data Read Register", offset: "0x2",
		bits: [
		]
	},
	{ name: "AT_R", description: "GPIO H Data Read Register", offset: "0xE",
		bits: [
		]
	},
];
module.exports = {
	GPIORegisters: GPIORegisters,
}
