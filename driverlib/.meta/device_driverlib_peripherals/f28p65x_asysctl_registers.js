let ASYSCTLRegisters = [
	{ name: "CONFIGLOCK", description: "Lock Register for all the config registers.", offset: "0x5E",
		bits: [
			{ name: "AGPIOFILTER", description: "Locks AGPIOFILTER Register", size: "1", shift: "1", mask: "0x2" },
			{ name: "AGPIOCTRL", description: "Locks all AGPIOCTRL Register", size: "1", shift: "3", mask: "0x8" },
			{ name: "GPIOINENACTRL", description: "Locks all GPIOINENACTRL Register", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "TSNSCTL", description: "Temperature Sensor Control Register", offset: "0x60",
		bits: [
			{ name: "ENABLE", description: "Temperature Sensor Enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "ANAREFCTL", description: "Analog Reference Control Register.", offset: "0x68",
		bits: [
			{ name: "ANAREFASEL", description: "Analog Reference Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "ANAREFBSEL", description: "Analog Reference B Select", size: "1", shift: "1", mask: "0x2" },
			{ name: "ANAREFCSEL", description: "Analog Reference C Select", size: "1", shift: "2", mask: "0x4" },
			{ name: "ANAREFA2P5SEL", description: "Analog Reference Select", size: "1", shift: "8", mask: "0x100" },
			{ name: "ANAREFB2P5SEL", description: "Analog Reference B Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "ANAREFC2P5SEL", description: "Analog Reference C Select", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "VMONCTL", description: "Voltage Monitor Control Register", offset: "0x70",
		bits: [
			{ name: "BORLVMONDIS", description: "Disable BORL(ow) feature on VDDIO", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "CMPHPMXSEL", description: "Bits to select one of the many sources on CopmHP", offset: "0x82",
		bits: [
			{ name: "CMP1HPMXSEL", description: "CMP1HPMXSEL bits", size: "3", shift: "0", mask: "0x7" },
			{ name: "CMP2HPMXSEL", description: "CMP2HPMXSEL bits", size: "3", shift: "3", mask: "0x38" },
			{ name: "CMP3HPMXSEL", description: "CMP3HPMXSEL bits", size: "3", shift: "6", mask: "0x1C0" },
			{ name: "CMP4HPMXSEL", description: "CMP4HPMXSEL bits", size: "3", shift: "9", mask: "0xE00" },
			{ name: "CMP5HPMXSEL", description: "CMP5HPMXSEL bits", size: "3", shift: "12", mask: "0x7000" },
			{ name: "CMP6HPMXSEL", description: "CMP6HPMXSEL bits", size: "3", shift: "15", mask: "0x38000" },
			{ name: "CMP7HPMXSEL", description: "CMP7HPMXSEL bits", size: "3", shift: "18", mask: "0x1C0000" },
			{ name: "CMP8HPMXSEL", description: "CMP8HPMXSEL bits", size: "3", shift: "21", mask: "0xE00000" },
			{ name: "CMP9HPMXSEL", description: "CMP9HPMXSEL bits", size: "3", shift: "24", mask: "0x7000000" },
			{ name: "CMP10HPMXSEL", description: "CMP10HPMXSEL bits", size: "3", shift: "27", mask: "0x38000000" },
		]
	},
	{ name: "CMPLPMXSEL", description: "Bits to select one of the many sources on CopmLP", offset: "0x84",
		bits: [
			{ name: "CMP1LPMXSEL", description: "CMP1LPMXSEL bits", size: "3", shift: "0", mask: "0x7" },
			{ name: "CMP2LPMXSEL", description: "CMP2LPMXSEL bits", size: "3", shift: "3", mask: "0x38" },
			{ name: "CMP3LPMXSEL", description: "CMP3LPMXSEL bits", size: "3", shift: "6", mask: "0x1C0" },
			{ name: "CMP4LPMXSEL", description: "CMP4LPMXSEL bits", size: "3", shift: "9", mask: "0xE00" },
			{ name: "CMP5LPMXSEL", description: "CMP5LPMXSEL bits", size: "3", shift: "12", mask: "0x7000" },
			{ name: "CMP6LPMXSEL", description: "CMP6LPMXSEL bits", size: "3", shift: "15", mask: "0x38000" },
			{ name: "CMP7LPMXSEL", description: "CMP7LPMXSEL bits", size: "3", shift: "18", mask: "0x1C0000" },
			{ name: "CMP8LPMXSEL", description: "CMP8LPMXSEL bits", size: "3", shift: "21", mask: "0xE00000" },
			{ name: "CMP9LPMXSEL", description: "CMP9LPMXSEL bits", size: "3", shift: "24", mask: "0x7000000" },
			{ name: "CMP10LPMXSEL", description: "CMP10LPMXSEL bits", size: "3", shift: "27", mask: "0x38000000" },
		]
	},
	{ name: "CMPHNMXSEL", description: "Bits to select one of the many sources on CopmHN", offset: "0x86",
		bits: [
			{ name: "CMP1HNMXSEL", description: "CMP1HNMXSEL bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMP2HNMXSEL", description: "CMP2HNMXSEL bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMP3HNMXSEL", description: "CMP3HNMXSEL bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMP4HNMXSEL", description: "CMP4HNMXSEL bits", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMP5HNMXSEL", description: "CMP5HNMXSEL bits", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMP6HNMXSEL", description: "CMP6HNMXSEL bits", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMP7HNMXSEL", description: "CMP7HNMXSEL bits", size: "1", shift: "6", mask: "0x40" },
			{ name: "CMP8HNMXSEL", description: "CMP8HNMXSEL bits", size: "1", shift: "7", mask: "0x80" },
			{ name: "CMP9HNMXSEL", description: "CMP9HNMXSEL bits", size: "1", shift: "8", mask: "0x100" },
			{ name: "CMP10HNMXSEL", description: "CMP10HNMXSEL bits", size: "1", shift: "9", mask: "0x200" },
			{ name: "CMP11HNMXSEL", description: "CMP11HNMXSEL bits", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "CMPLNMXSEL", description: "Bits to select one of the many sources on CopmLN", offset: "0x87",
		bits: [
			{ name: "CMP1LNMXSEL", description: "CMP1LNMXSEL bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMP2LNMXSEL", description: "CMP2LNMXSEL bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMP3LNMXSEL", description: "CMP3LNMXSEL bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMP4LNMXSEL", description: "CMP4LNMXSEL bits", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMP5LNMXSEL", description: "CMP5LNMXSEL bits", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMP6LNMXSEL", description: "CMP6LNMXSEL bits", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMP7LNMXSEL", description: "CMP7LNMXSEL bits", size: "1", shift: "6", mask: "0x40" },
			{ name: "CMP8LNMXSEL", description: "CMP8LNMXSEL bits", size: "1", shift: "7", mask: "0x80" },
			{ name: "CMP9LNMXSEL", description: "CMP9LNMXSEL bits", size: "1", shift: "8", mask: "0x100" },
			{ name: "CMP10LNMXSEL", description: "CMP10LNMXSEL bits", size: "1", shift: "9", mask: "0x200" },
			{ name: "CMP11LNMXSEL", description: "CMP11LNMXSEL bits", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "ADCDACLOOPBACK", description: "Enabble loopback from DAC to ADCs", offset: "0x88",
		bits: [
			{ name: "ENLB2ADCA", description: "Enable COMPDACA loopback to ADCA", size: "1", shift: "0", mask: "0x1" },
			{ name: "ENLB2ADCB", description: "Enable COMPDACA loopback to ADCB", size: "1", shift: "1", mask: "0x2" },
			{ name: "ENLB2ADCC", description: "Enable COMPDACA loopback to ADCC", size: "1", shift: "2", mask: "0x4" },
			{ name: "KEY", description: "Key to enable writes", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "LOCK", description: "Lock Register", offset: "0x8E",
		bits: [
			{ name: "TSNSCTL", description: "TSNSCTL Register lock bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ANAREFCTL", description: "ANAREFCTL Register lock bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "VMONCTL", description: "VMONCTL Register lock bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMPHPMXSEL", description: "CMPHPMXSEL Register lock bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMPLPMXSEL", description: "CMPLPMXSEL Register lock bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "CMPHNMXSEL", description: "CMPHNMXSEL Register lock bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "CMPLNMXSEL", description: "CMPLNMXSEL Register lock bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "VREGCTL", description: "VREGCTL Register lock bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "CMPSSCTL", description: "CMPSSCTL Register lock bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "CMPHPMXSEL1", description: "CMPHPMXSEL1 Register lock bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "CMPLPMXSEL1", description: "CMPLPMXSEL1 Register lock bit", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "CMPHPMXSEL1", description: "Bits to select one of the many sources on CopmHP", offset: "0x90",
		bits: [
			{ name: "CMP11HPMXSEL", description: "CMP15HPMXSEL bits", size: "3", shift: "0", mask: "0x7" },
		]
	},
	{ name: "CMPLPMXSEL1", description: "Bits to select one of the many sources on CopmLP", offset: "0x92",
		bits: [
			{ name: "CMP11LPMXSEL", description: "CMP15LPMXSEL bits", size: "3", shift: "0", mask: "0x7" },
		]
	},
	{ name: "ADCSOCFRCGB", description: "ADC Global SOC Force", offset: "0x10E",
		bits: [
			{ name: "SOC0", description: "Generate synchronous SW trigger for SOC0", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOC1", description: "Generate synchronous SW trigger for SOC1", size: "1", shift: "1", mask: "0x2" },
			{ name: "SOC2", description: "Generate synchronous SW trigger for SOC2", size: "1", shift: "2", mask: "0x4" },
			{ name: "SOC3", description: "Generate synchronous SW trigger for SOC3", size: "1", shift: "3", mask: "0x8" },
			{ name: "SOC4", description: "Generate synchronous SW trigger for SOC4", size: "1", shift: "4", mask: "0x10" },
			{ name: "SOC5", description: "Generate synchronous SW trigger for SOC5", size: "1", shift: "5", mask: "0x20" },
			{ name: "SOC6", description: "Generate synchronous SW trigger for SOC6", size: "1", shift: "6", mask: "0x40" },
			{ name: "SOC7", description: "Generate synchronous SW trigger for SOC7", size: "1", shift: "7", mask: "0x80" },
			{ name: "SOC8", description: "Generate synchronous SW trigger for SOC8", size: "1", shift: "8", mask: "0x100" },
			{ name: "SOC9", description: "Generate synchronous SW trigger for SOC9", size: "1", shift: "9", mask: "0x200" },
			{ name: "SOC10", description: "Generate synchronous SW trigger for SOC10", size: "1", shift: "10", mask: "0x400" },
			{ name: "SOC11", description: "Generate synchronous SW trigger for SOC11", size: "1", shift: "11", mask: "0x800" },
			{ name: "SOC12", description: "Generate synchronous SW trigger for SOC12", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SOC13", description: "Generate synchronous SW trigger for SOC13", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SOC14", description: "Generate synchronous SW trigger for SOC14", size: "1", shift: "14", mask: "0x4000" },
			{ name: "SOC15", description: "Generate synchronous SW trigger for SOC15", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "ADCSOCFRCGBSEL", description: "ADC Global SOC Force Select", offset: "0x110",
		bits: [
			{ name: "ADCA", description: "Generate synchronous SW trigger for ADCA", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCB", description: "Generate synchronous SW trigger for ADCB", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCC", description: "Generate synchronous SW trigger for ADCC", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "AGPIOFILTER", description: "AGPIO Filter Control Register", offset: "0x111",
		bits: [
			{ name: "RIGHT", description: "AGPIOFILTER Control for right side pins", size: "2", shift: "0", mask: "0x3" },
			{ name: "BOTTOM", description: "AGPIOFILTER Control for bottom side pins", size: "2", shift: "8", mask: "0x300" },
		]
	},
	{ name: "AGPIOCTRLG", description: "AGPIO Control Register", offset: "0x120",
		bits: [
			{ name: "GPIO198", description: "AGPIOCTRL for GPIO198", size: "1", shift: "6", mask: "0x40" },
			{ name: "GPIO199", description: "AGPIOCTRL for GPIO199", size: "1", shift: "7", mask: "0x80" },
			{ name: "GPIO200", description: "AGPIOCTRL for GPIO200", size: "1", shift: "8", mask: "0x100" },
			{ name: "GPIO201", description: "AGPIOCTRL for GPIO201", size: "1", shift: "9", mask: "0x200" },
			{ name: "GPIO202", description: "AGPIOCTRL for GPIO202", size: "1", shift: "10", mask: "0x400" },
			{ name: "GPIO203", description: "AGPIOCTRL for GPIO203", size: "1", shift: "11", mask: "0x800" },
			{ name: "GPIO204", description: "AGPIOCTRL for GPIO204", size: "1", shift: "12", mask: "0x1000" },
			{ name: "GPIO205", description: "AGPIOCTRL for GPIO205", size: "1", shift: "13", mask: "0x2000" },
			{ name: "GPIO206", description: "AGPIOCTRL for GPIO206", size: "1", shift: "14", mask: "0x4000" },
			{ name: "GPIO207", description: "AGPIOCTRL for GPIO207", size: "1", shift: "15", mask: "0x8000" },
			{ name: "GPIO208", description: "AGPIOCTRL for GPIO208", size: "1", shift: "16", mask: "0x10000" },
			{ name: "GPIO209", description: "AGPIOCTRL for GPIO209", size: "1", shift: "17", mask: "0x20000" },
			{ name: "GPIO210", description: "AGPIOCTRL for GPIO210", size: "1", shift: "18", mask: "0x40000" },
			{ name: "GPIO211", description: "AGPIOCTRL for GPIO211", size: "1", shift: "19", mask: "0x80000" },
			{ name: "GPIO212", description: "AGPIOCTRL for GPIO212", size: "1", shift: "20", mask: "0x100000" },
			{ name: "GPIO213", description: "AGPIOCTRL for GPIO213", size: "1", shift: "21", mask: "0x200000" },
			{ name: "GPIO214", description: "AGPIOCTRL for GPIO214", size: "1", shift: "22", mask: "0x400000" },
			{ name: "GPIO215", description: "AGPIOCTRL for GPIO215", size: "1", shift: "23", mask: "0x800000" },
			{ name: "GPIO216", description: "AGPIOCTRL for GPIO216", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "GPIO217", description: "AGPIOCTRL for GPIO217", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "GPIO218", description: "AGPIOCTRL for GPIO218", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "GPIO219", description: "AGPIOCTRL for GPIO219", size: "1", shift: "27", mask: "0x8000000" },
		]
	},
	{ name: "GPIOINENACTRL", description: "GPIOINENACTRL Control Register", offset: "0x134",
		bits: [
			{ name: "GPIO0", description: "Input Buffer Control for GPIO0", size: "1", shift: "0", mask: "0x1" },
			{ name: "GPIO23", description: "Input Buffer Control for GPIO23", size: "1", shift: "1", mask: "0x2" },
			{ name: "GPIO25", description: "Input Buffer Control for GPIO25", size: "1", shift: "2", mask: "0x4" },
			{ name: "GPIO31", description: "Input Buffer Control for GPIO31", size: "1", shift: "3", mask: "0x8" },
			{ name: "GPIO46", description: "Input Buffer Control for GPIO46", size: "1", shift: "4", mask: "0x10" },
			{ name: "GPIO103", description: "Input Buffer Control for GPIO103", size: "1", shift: "5", mask: "0x20" },
		]
	},
];
module.exports = {
	ASYSCTLRegisters: ASYSCTLRegisters,
}
