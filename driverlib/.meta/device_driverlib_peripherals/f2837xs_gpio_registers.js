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
	{ name: "SEL1", description: "GPIO A Core Select Register (GPIO0 to 7)", offset: "0x28",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO A Core Select Register (GPIO8 to 15)", offset: "0x2A",
		bits: [
		]
	},
	{ name: "SEL3", description: "GPIO A Core Select Register (GPIO16 to 23)", offset: "0x2C",
		bits: [
		]
	},
	{ name: "SEL4", description: "GPIO A Core Select Register (GPIO24 to 31)", offset: "0x2E",
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
	{ name: "MSEL", description: "GPIO B Analog Mode Select register (GPIO32 to GPIO63)", offset: "0x54",
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
	{ name: "SEL1", description: "GPIO B Core Select Register (GPIO32 to 39)", offset: "0x68",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO B Core Select Register (GPIO40 to 47)", offset: "0x6A",
		bits: [
		]
	},
	{ name: "SEL3", description: "GPIO B Core Select Register (GPIO48 to 55)", offset: "0x6C",
		bits: [
		]
	},
	{ name: "SEL4", description: "GPIO B Core Select Register (GPIO56 to 63)", offset: "0x6E",
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
	{ name: "TRL", description: "GPIO C Qualification Sampling Period Control (GPIO64 to 95)", offset: "0x80",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO C Qualifier Select 1 Register (GPIO64 to 79)", offset: "0x82",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO C Qualifier Select 2 Register (GPIO80  to 95)", offset: "0x84",
		bits: [
		]
	},
	{ name: "UX1", description: "GPIO C Mux 1 Register (GPIO64 to 79)", offset: "0x86",
		bits: [
		]
	},
	{ name: "UX2", description: "GPIO C Mux 2 Register (GPIO80  to 95)", offset: "0x88",
		bits: [
		]
	},
	{ name: "IR", description: "GPIO C Direction Register (GPIO64 to 95)", offset: "0x8A",
		bits: [
		]
	},
	{ name: "UD", description: "GPIO C Pull Up Disable Register (GPIO64 to 95)", offset: "0x8C",
		bits: [
		]
	},
	{ name: "NV", description: "GPIO C Input Polarity Invert Registers (GPIO64 to 95)", offset: "0x90",
		bits: [
		]
	},
	{ name: "DR", description: "GPIO C Open Drain Output Register (GPIO64 to GPIO95)", offset: "0x92",
		bits: [
		]
	},
	{ name: "MUX1", description: "GPIO C Peripheral Group Mux (GPIO64 to 79)", offset: "0xA0",
		bits: [
		]
	},
	{ name: "MUX2", description: "GPIO C Peripheral Group Mux (GPIO80  to 95)", offset: "0xA2",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO C Core Select Register (GPIO64 to 71)", offset: "0xA8",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO C Core Select Register (GPIO72 to 79)", offset: "0xAA",
		bits: [
		]
	},
	{ name: "SEL3", description: "GPIO C Core Select Register (GPIO80  to 87)", offset: "0xAC",
		bits: [
		]
	},
	{ name: "SEL4", description: "GPIO C Core Select Register (GPIO88 to 95)", offset: "0xAE",
		bits: [
		]
	},
	{ name: "OCK", description: "GPIO C Lock Configuration Register (GPIO64 to 95)", offset: "0xBC",
		bits: [
		]
	},
	{ name: "R", description: "GPIO C Lock Commit Register (GPIO64 to 95)", offset: "0xBE",
		bits: [
		]
	},
	{ name: "TRL", description: "GPIO D Qualification Sampling Period Control (GPIO96 to 127)", offset: "0xC0",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO D Qualifier Select 1 Register (GPIO96 to 111)", offset: "0xC2",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO D Qualifier Select 2 Register (GPIO112 to 127)", offset: "0xC4",
		bits: [
		]
	},
	{ name: "UX1", description: "GPIO D Mux 1 Register (GPIO96 to 111)", offset: "0xC6",
		bits: [
		]
	},
	{ name: "UX2", description: "GPIO D Mux 2 Register (GPIO112 to 127)", offset: "0xC8",
		bits: [
		]
	},
	{ name: "IR", description: "GPIO D Direction Register (GPIO96 to 127)", offset: "0xCA",
		bits: [
		]
	},
	{ name: "UD", description: "GPIO D Pull Up Disable Register (GPIO96 to 127)", offset: "0xCC",
		bits: [
		]
	},
	{ name: "NV", description: "GPIO D Input Polarity Invert Registers (GPIO96 to 127)", offset: "0xD0",
		bits: [
		]
	},
	{ name: "DR", description: "GPIO D Open Drain Output Register (GPIO96 to GPIO127)", offset: "0xD2",
		bits: [
		]
	},
	{ name: "MUX1", description: "GPIO D Peripheral Group Mux (GPIO96 to 111)", offset: "0xE0",
		bits: [
		]
	},
	{ name: "MUX2", description: "GPIO D Peripheral Group Mux (GPIO112 to 127)", offset: "0xE2",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO D Core Select Register (GPIO96 to 103)", offset: "0xE8",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO D Core Select Register (GPIO104 to 111)", offset: "0xEA",
		bits: [
		]
	},
	{ name: "SEL3", description: "GPIO D Core Select Register (GPIO112 to 119)", offset: "0xEC",
		bits: [
		]
	},
	{ name: "SEL4", description: "GPIO D Core Select Register (GPIO120 to 127)", offset: "0xEE",
		bits: [
		]
	},
	{ name: "OCK", description: "GPIO D Lock Configuration Register (GPIO96 to 127)", offset: "0xFC",
		bits: [
		]
	},
	{ name: "R", description: "GPIO D Lock Commit Register (GPIO96 to 127)", offset: "0xFE",
		bits: [
		]
	},
	{ name: "TRL", description: "GPIO E Qualification Sampling Period Control (GPIO128 to 159)", offset: "0x100",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO E Qualifier Select 1 Register (GPIO128 to 143)", offset: "0x102",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO E Qualifier Select 2 Register (GPIO144  to 159)", offset: "0x104",
		bits: [
		]
	},
	{ name: "UX1", description: "GPIO E Mux 1 Register (GPIO128 to 143)", offset: "0x106",
		bits: [
		]
	},
	{ name: "UX2", description: "GPIO E Mux 2 Register (GPIO144  to 159)", offset: "0x108",
		bits: [
		]
	},
	{ name: "IR", description: "GPIO E Direction Register (GPIO128 to 159)", offset: "0x10A",
		bits: [
		]
	},
	{ name: "UD", description: "GPIO E Pull Up Disable Register (GPIO128 to 159)", offset: "0x10C",
		bits: [
		]
	},
	{ name: "NV", description: "GPIO E Input Polarity Invert Registers (GPIO128 to 159)", offset: "0x110",
		bits: [
		]
	},
	{ name: "DR", description: "GPIO E Open Drain Output Register (GPIO128 to GPIO159)", offset: "0x112",
		bits: [
		]
	},
	{ name: "MUX1", description: "GPIO E Peripheral Group Mux (GPIO128 to 143)", offset: "0x120",
		bits: [
		]
	},
	{ name: "MUX2", description: "GPIO E Peripheral Group Mux (GPIO144  to 159)", offset: "0x122",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO E Core Select Register (GPIO128 to 135)", offset: "0x128",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO E Core Select Register (GPIO136 to 143)", offset: "0x12A",
		bits: [
		]
	},
	{ name: "SEL3", description: "GPIO E Core Select Register (GPIO144  to 151)", offset: "0x12C",
		bits: [
		]
	},
	{ name: "SEL4", description: "GPIO E Core Select Register (GPIO152 to 159)", offset: "0x12E",
		bits: [
		]
	},
	{ name: "OCK", description: "GPIO E Lock Configuration Register (GPIO128 to 159)", offset: "0x13C",
		bits: [
		]
	},
	{ name: "R", description: "GPIO E Lock Commit Register (GPIO128 to 159)", offset: "0x13E",
		bits: [
		]
	},
	{ name: "TRL", description: "GPIO F Qualification Sampling Period Control (GPIO160 to 168)", offset: "0x140",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO F Qualifier Select 1 Register (GPIO160 to 168)", offset: "0x142",
		bits: [
		]
	},
	{ name: "UX1", description: "GPIO F Mux 1 Register (GPIO160 to 168)", offset: "0x146",
		bits: [
		]
	},
	{ name: "IR", description: "GPIO F Direction Register (GPIO160 to 168)", offset: "0x14A",
		bits: [
		]
	},
	{ name: "UD", description: "GPIO F Pull Up Disable Register (GPIO160 to 168)", offset: "0x14C",
		bits: [
		]
	},
	{ name: "NV", description: "GPIO F Input Polarity Invert Registers (GPIO160 to 168)", offset: "0x150",
		bits: [
		]
	},
	{ name: "DR", description: "GPIO F Open Drain Output Register (GPIO160 to GPIO168)", offset: "0x152",
		bits: [
		]
	},
	{ name: "MUX1", description: "GPIO F Peripheral Group Mux (GPIO160 to 168)", offset: "0x160",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO F Core Select Register (GPIO160 to 167)", offset: "0x168",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO F Core Select Register (GPIO168)", offset: "0x16A",
		bits: [
		]
	},
	{ name: "OCK", description: "GPIO F Lock Configuration Register (GPIO160 to 168)", offset: "0x17C",
		bits: [
		]
	},
	{ name: "R", description: "GPIO F Lock Commit Register (GPIO160 to 168)", offset: "0x17E",
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
	{ name: "AT", description: "GPIO C Data Register (GPIO64 to 95)", offset: "0x10",
		bits: [
		]
	},
	{ name: "ET", description: "GPIO C Data Set Register (GPIO64 to 95)", offset: "0x12",
		bits: [
		]
	},
	{ name: "LEAR", description: "GPIO C Data Clear Register (GPIO64 to 95)", offset: "0x14",
		bits: [
		]
	},
	{ name: "OGGLE", description: "GPIO C Data Toggle Register (GPIO64 to 95)", offset: "0x16",
		bits: [
		]
	},
	{ name: "AT", description: "GPIO D Data Register (GPIO96 to 127)", offset: "0x18",
		bits: [
		]
	},
	{ name: "ET", description: "GPIO D Data Set Register (GPIO96 to 127)", offset: "0x1A",
		bits: [
		]
	},
	{ name: "LEAR", description: "GPIO D Data Clear Register (GPIO96 to 127)", offset: "0x1C",
		bits: [
		]
	},
	{ name: "OGGLE", description: "GPIO D Data Toggle Register (GPIO96 to 127)", offset: "0x1E",
		bits: [
		]
	},
	{ name: "AT", description: "GPIO E Data Register (GPIO128 to 159)", offset: "0x20",
		bits: [
		]
	},
	{ name: "ET", description: "GPIO E Data Set Register (GPIO128 to 159)", offset: "0x22",
		bits: [
		]
	},
	{ name: "LEAR", description: "GPIO E Data Clear Register (GPIO128 to 159)", offset: "0x24",
		bits: [
		]
	},
	{ name: "OGGLE", description: "GPIO E Data Toggle Register (GPIO128 to 159)", offset: "0x26",
		bits: [
		]
	},
	{ name: "AT", description: "GPIO F Data Register (GPIO160 to 168)", offset: "0x28",
		bits: [
		]
	},
	{ name: "ET", description: "GPIO F Data Set Register (GPIO160 to 168)", offset: "0x2A",
		bits: [
		]
	},
	{ name: "LEAR", description: "GPIO F Data Clear Register (GPIO160 to 168)", offset: "0x2C",
		bits: [
		]
	},
	{ name: "OGGLE", description: "GPIO F Data Toggle Register (GPIO160 to 168)", offset: "0x2E",
		bits: [
		]
	},
];
module.exports = {
	GPIORegisters: GPIORegisters,
}
