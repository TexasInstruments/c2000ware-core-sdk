let GPIORegisters = [
	{ name: "TRL", description: "GPIO A Qualification Sampling Period (GPIO0 to GPIO31)", offset: "0x0",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO A Qualification Type (GPIO0 to GPIO15)", offset: "0x2",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO A Qualification Type (GPIO16 to GPIO31)", offset: "0x4",
		bits: [
		]
	},
	{ name: "UX1", description: "GPIO A Peripheral Mux (GPIO0 to GPIO15)", offset: "0x6",
		bits: [
		]
	},
	{ name: "UX2", description: "GPIO A Peripheral Mux (GPIO16 to GPIO31)", offset: "0x8",
		bits: [
		]
	},
	{ name: "IR", description: "GPIO A Direction (GPIO0 to GPIO31)", offset: "0xA",
		bits: [
		]
	},
	{ name: "UD", description: "GPIO A Pull-Up Disable (GPIO0 to GPIO31)", offset: "0xC",
		bits: [
		]
	},
	{ name: "NV", description: "GPIO A Input Inversion (GPIO0 to GPIO31)", offset: "0x10",
		bits: [
		]
	},
	{ name: "DR", description: "GPIO A Open Drain Output Mode (GPIO0 to GPIO31)", offset: "0x12",
		bits: [
		]
	},
	{ name: "MSEL", description: "GPIO A Analog Mode Select (GPIO0 to GPIO31)", offset: "0x14",
		bits: [
		]
	},
	{ name: "MUX1", description: "GPIO A Peripheral Group Mux (GPIO0 to GPIO15)", offset: "0x20",
		bits: [
		]
	},
	{ name: "MUX2", description: "GPIO A Peripheral Group Mux (GPIO16 to GPIO31)", offset: "0x22",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO A Master Core Select (GPIO0 to GPIO7)", offset: "0x28",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO A Master Core Select (GPIO8 to GPIO15)", offset: "0x2A",
		bits: [
		]
	},
	{ name: "SEL3", description: "GPIO A Master Core Select (GPIO16 to GPIO23)", offset: "0x2C",
		bits: [
		]
	},
	{ name: "SEL4", description: "GPIO A Master Core Select (GPIO24 to GPIO31)", offset: "0x2E",
		bits: [
		]
	},
	{ name: "OCK", description: "GPIO A Lock Register (GPIO0 to GPIO31)", offset: "0x3C",
		bits: [
		]
	},
	{ name: "R", description: "GPIO A Lock Commit Register (GPIO0 to GPIO31)", offset: "0x3E",
		bits: [
		]
	},
	{ name: "TRL", description: "GPIO B Qualification Sampling Period (GPIO32 to GPIO63)", offset: "0x40",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO B Qualification Type (GPIO32 to GPIO47)", offset: "0x42",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO B Qualification Type (GPIO48 to GPIO63)", offset: "0x44",
		bits: [
		]
	},
	{ name: "UX1", description: "GPIO B Peripheral Mux (GPIO32 to GPIO47)", offset: "0x46",
		bits: [
		]
	},
	{ name: "UX2", description: "GPIO B Peripheral Mux (GPIO48 to GPIO63)", offset: "0x48",
		bits: [
		]
	},
	{ name: "IR", description: "GPIO B Direction (GPIO32 to GPIO63)", offset: "0x4A",
		bits: [
		]
	},
	{ name: "UD", description: "GPIO B Pull-Up Disable (GPIO32 to GPIO63)", offset: "0x4C",
		bits: [
		]
	},
	{ name: "NV", description: "GPIO B Input Inversion (GPIO32 to GPIO63)", offset: "0x50",
		bits: [
		]
	},
	{ name: "DR", description: "GPIO B Open Drain Output Mode (GPIO32 to GPIO63)", offset: "0x52",
		bits: [
		]
	},
	{ name: "MUX1", description: "GPIO B Peripheral Group Mux (GPIO32 to GPIO47)", offset: "0x60",
		bits: [
		]
	},
	{ name: "MUX2", description: "GPIO B Peripheral Group Mux (GPIO48 to GPIO63)", offset: "0x62",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO B Master Core Select (GPIO32 to GPIO39)", offset: "0x68",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO B Master Core Select (GPIO40 to GPIO47)", offset: "0x6A",
		bits: [
		]
	},
	{ name: "SEL3", description: "GPIO B Master Core Select (GPIO48 to GPIO55)", offset: "0x6C",
		bits: [
		]
	},
	{ name: "SEL4", description: "GPIO B Master Core Select (GPIO56 to GPIO63)", offset: "0x6E",
		bits: [
		]
	},
	{ name: "OCK", description: "GPIO B Lock Register (GPIO32 to GPIO63)", offset: "0x7C",
		bits: [
		]
	},
	{ name: "R", description: "GPIO B Lock Commit Register (GPIO32 to GPIO63)", offset: "0x7E",
		bits: [
		]
	},
	{ name: "TRL", description: "GPIO H Qualification Sampling Period (GPIO224 to GPIO255)", offset: "0x1C0",
		bits: [
		]
	},
	{ name: "SEL1", description: "GPIO H Qualification Type (GPIO224 to GPIO239)", offset: "0x1C2",
		bits: [
		]
	},
	{ name: "SEL2", description: "GPIO H Qualification Type (GPIO240 to GPIO255)", offset: "0x1C4",
		bits: [
		]
	},
	{ name: "UD", description: "GPIO H Pull-Up Disable (GPIO224 to GPIO255)", offset: "0x1CC",
		bits: [
		]
	},
	{ name: "NV", description: "GPIO H Input Inversion (GPIO224 to GPIO255)", offset: "0x1D0",
		bits: [
		]
	},
	{ name: "MSEL", description: "GPIO H Analog Mode Select (GPIO224 to GPIO255)", offset: "0x1D4",
		bits: [
		]
	},
	{ name: "OCK", description: "GPIO H Lock Register (GPIO224 to GPIO255)", offset: "0x1FC",
		bits: [
		]
	},
	{ name: "R", description: "GPIO H Lock Commit Register (GPIO224 to GPIO255)", offset: "0x1FE",
		bits: [
		]
	},
	{ name: "AT", description: "GPIO A Data Register (GPIO0 to GPIO31)", offset: "0x0",
		bits: [
		]
	},
	{ name: "ET", description: "GPIO A Output Set (GPIO0 to GPIO31)", offset: "0x2",
		bits: [
		]
	},
	{ name: "LEAR", description: "GPIO A Output Clear (GPIO0 to GPIO31)", offset: "0x4",
		bits: [
		]
	},
	{ name: "OGGLE", description: "GPIO A Output Toggle (GPIO0 to GPIO31)", offset: "0x6",
		bits: [
		]
	},
	{ name: "AT", description: "GPIO B Data Register (GPIO32 to GPIO64)", offset: "0x8",
		bits: [
		]
	},
	{ name: "ET", description: "GPIO B Output Set (GPIO32 to GPIO64)", offset: "0xA",
		bits: [
		]
	},
	{ name: "LEAR", description: "GPIO B Output Clear (GPIO32 to GPIO64)", offset: "0xC",
		bits: [
		]
	},
	{ name: "OGGLE", description: "GPIO B Output Toggle (GPIO32 to GPIO64)", offset: "0xE",
		bits: [
		]
	},
	{ name: "AT", description: "GPIO H Data Register (GPIO0 to GPIO255)", offset: "0x38",
		bits: [
		]
	},
];
module.exports = {
	GPIORegisters: GPIORegisters,
}
