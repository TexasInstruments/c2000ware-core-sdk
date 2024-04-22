let ASYSCTLRegisters = [
	{ name: "INTERNALTESTCTL", description: "INTERNALTEST Node Control Register", offset: "0x4A",
		bits: [
			{ name: "TESTSEL", description: "Test Select", size: "6", shift: "0", mask: "0x3F" },
			{ name: "KEY", description: "Key to Enable writes", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
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
	{ name: "ANAREFPCTL", description: "Analog Reference Control Register for VREFHI", offset: "0x68",
		bits: [
			{ name: "REFPMUXSELA", description: "Analog Reference Select ADCA", size: "2", shift: "0", mask: "0x3" },
			{ name: "REFPMUXSELB", description: "Analog Reference Select ADCB", size: "2", shift: "2", mask: "0xC" },
			{ name: "REFPMUXSELC", description: "Analog Reference Select ADCC", size: "2", shift: "4", mask: "0x30" },
			{ name: "REFPMUXSELD", description: "Analog Reference Select ADCD", size: "2", shift: "6", mask: "0xC0" },
			{ name: "REFPMUXSELE", description: "Analog Reference Select ADCE", size: "2", shift: "8", mask: "0x300" },
			{ name: "ANAREFA1P65SEL", description: "1.65v Reference Select ADCA", size: "1", shift: "10", mask: "0x400" },
			{ name: "ANAREFB1P65SEL", description: "1.65v Reference Select ADCB", size: "1", shift: "11", mask: "0x800" },
			{ name: "ANAREFC1P65SEL", description: "1.65v Reference Select ADCC", size: "1", shift: "12", mask: "0x1000" },
			{ name: "ANAREFD1P65SEL", description: "1.65v Reference Select ADCD", size: "1", shift: "13", mask: "0x2000" },
			{ name: "ANAREFE1P65SEL", description: "1.65v Reference Select ADCE", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "ANAREFNCTL", description: "Analog Reference Control Register for VREFLO", offset: "0x69",
		bits: [
			{ name: "REFNMUXSELA", description: "Analog Reference Select ADCA", size: "2", shift: "0", mask: "0x3" },
			{ name: "REFNMUXSELB", description: "Analog Reference Select ADCB", size: "2", shift: "2", mask: "0xC" },
			{ name: "REFNMUXSELC", description: "Analog Reference Select ADCC", size: "2", shift: "4", mask: "0x30" },
			{ name: "REFNMUXSELD", description: "Analog Reference Select ADCD", size: "2", shift: "6", mask: "0xC0" },
			{ name: "REFNMUXSELE", description: "Analog Reference Select ADCE", size: "2", shift: "8", mask: "0x300" },
		]
	},
	{ name: "VMONCTL", description: "Voltage Monitor Control Register", offset: "0x70",
		bits: [
			{ name: "BORLVMONDIS", description: "Disable BORL(ow) feature on VDDIO", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "CMPHPMXSEL", description: "Bits to select one of the many sources on CompHP", offset: "0x82",
		bits: [
			{ name: "CMP1HPMXSEL", description: "CMP1HPMXSEL bits", size: "3", shift: "0", mask: "0x7" },
			{ name: "CMP2HPMXSEL", description: "CMP2HPMXSEL bits", size: "3", shift: "3", mask: "0x38" },
			{ name: "CMP3HPMXSEL", description: "CMP3HPMXSEL bits", size: "3", shift: "6", mask: "0x1C0" },
			{ name: "CMP4HPMXSEL", description: "CMP4HPMXSEL bits", size: "3", shift: "9", mask: "0xE00" },
		]
	},
	{ name: "CMPLPMXSEL", description: "Bits to select one of the many sources on CompLP", offset: "0x84",
		bits: [
			{ name: "CMP1LPMXSEL", description: "CMP1LPMXSEL bits", size: "3", shift: "0", mask: "0x7" },
			{ name: "CMP2LPMXSEL", description: "CMP2LPMXSEL bits", size: "3", shift: "3", mask: "0x38" },
			{ name: "CMP3LPMXSEL", description: "CMP3LPMXSEL bits", size: "3", shift: "6", mask: "0x1C0" },
			{ name: "CMP4LPMXSEL", description: "CMP4LPMXSEL bits", size: "3", shift: "9", mask: "0xE00" },
		]
	},
	{ name: "CMPHNMXSEL", description: "Bits to select one of the many sources on CompHN", offset: "0x86",
		bits: [
			{ name: "CMP1HNMXSEL", description: "CMP1HNMXSEL bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMP2HNMXSEL", description: "CMP2HNMXSEL bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMP3HNMXSEL", description: "CMP3HNMXSEL bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMP4HNMXSEL", description: "CMP4HNMXSEL bits", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "CMPLNMXSEL", description: "Bits to select one of the many sources on CompLN", offset: "0x87",
		bits: [
			{ name: "CMP1LNMXSEL", description: "CMP1LNMXSEL bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMP2LNMXSEL", description: "CMP2LNMXSEL bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMP3LNMXSEL", description: "CMP3LNMXSEL bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMP4LNMXSEL", description: "CMP4LNMXSEL bits", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "ADCDACLOOPBACK", description: "Enabble loopback from DAC to ADCs", offset: "0x88",
		bits: [
			{ name: "ENLB2ADCA", description: "Enable DACA loopback to ADCA", size: "1", shift: "0", mask: "0x1" },
			{ name: "ENLB2ADCB", description: "Enable DACA loopback to ADCB", size: "1", shift: "1", mask: "0x2" },
			{ name: "ENLB2ADCC", description: "Enable DACA loopback to ADCC", size: "1", shift: "2", mask: "0x4" },
			{ name: "ENLB2ADCD", description: "Enable DACA loopback to ADCD", size: "1", shift: "3", mask: "0x8" },
			{ name: "ENLB2ADCE", description: "Enable DACA loopback to ADCE", size: "1", shift: "4", mask: "0x10" },
			{ name: "KEY", description: "Key to enable writes", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CMPSSCTL", description: "CMPSS Control Register", offset: "0x8B",
		bits: [
			{ name: "CMP1LDACOUTEN", description: "Enable general purpose DAC functionality for", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPSSCTLEN", description: "Enable the CMPSSCTL Register", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CMPSSDACBUFCONFIG", description: "Config bits for CMPSS DAC buffer", offset: "0x8C",
		bits: [
			{ name: "CMPSSADACL", description: "Configuration bits for CMPSS DACA", size: "8", shift: "0", mask: "0xFF" },
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
		]
	},
	{ name: "AGPIOFILTER", description: "AGPIO Filter Control Register", offset: "0x108",
		bits: [
			{ name: "GROUP1", description: "AGPIOFILTER Control for group1 side pins", size: "2", shift: "0", mask: "0x3" },
			{ name: "GROUP2", description: "AGPIOFILTER Control for group2 side pins", size: "2", shift: "8", mask: "0x300" },
		]
	},
	{ name: "AGPIOCTRLA", description: "AGPIO Control Register", offset: "0x10A",
		bits: [
			{ name: "GPIO11", description: "AGPIOCTRL for GPIO11", size: "1", shift: "11", mask: "0x800" },
			{ name: "GPIO12", description: "AGPIOCTRL for GPIO12", size: "1", shift: "12", mask: "0x1000" },
			{ name: "GPIO13", description: "AGPIOCTRL for GPIO13", size: "1", shift: "13", mask: "0x2000" },
			{ name: "GPIO16", description: "AGPIOCTRL for GPIO16", size: "1", shift: "16", mask: "0x10000" },
			{ name: "GPIO17", description: "AGPIOCTRL for GPIO17", size: "1", shift: "17", mask: "0x20000" },
			{ name: "GPIO20", description: "AGPIOCTRL for GPIO20", size: "1", shift: "20", mask: "0x100000" },
			{ name: "GPIO21", description: "AGPIOCTRL for GPIO21", size: "1", shift: "21", mask: "0x200000" },
			{ name: "GPIO24", description: "AGPIOCTRL for GPIO24", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "GPIO28", description: "AGPIOCTRL for GPIO28", size: "1", shift: "28", mask: "0x10000000" },
		]
	},
	{ name: "AGPIOCTRLB", description: "AGPIO Control Register", offset: "0x10C",
		bits: [
			{ name: "GPIO33", description: "AGPIOCTRL for GPIO33", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "AGPIOCTRLG", description: "AGPIO Control Register", offset: "0x116",
		bits: [
			{ name: "GPIO211", description: "AGPIOCTRL for GPIO211", size: "1", shift: "19", mask: "0x80000" },
			{ name: "GPIO212", description: "AGPIOCTRL for GPIO212", size: "1", shift: "20", mask: "0x100000" },
			{ name: "GPIO213", description: "AGPIOCTRL for GPIO213", size: "1", shift: "21", mask: "0x200000" },
			{ name: "GPIO214", description: "AGPIOCTRL for GPIO214", size: "1", shift: "22", mask: "0x400000" },
			{ name: "GPIO215", description: "AGPIOCTRL for GPIO215", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "AGPIOCTRLH", description: "AGPIO Control Register", offset: "0x118",
		bits: [
			{ name: "GPIO224", description: "AGPIOCTRL for GPIO224", size: "1", shift: "0", mask: "0x1" },
			{ name: "GPIO226", description: "AGPIOCTRL for GPIO226", size: "1", shift: "2", mask: "0x4" },
			{ name: "GPIO227", description: "AGPIOCTRL for GPIO227", size: "1", shift: "3", mask: "0x8" },
			{ name: "GPIO228", description: "AGPIOCTRL for GPIO228", size: "1", shift: "4", mask: "0x10" },
			{ name: "GPIO230", description: "AGPIOCTRL for GPIO230", size: "1", shift: "6", mask: "0x40" },
			{ name: "GPIO236", description: "AGPIOCTRL for GPIO236", size: "1", shift: "12", mask: "0x1000" },
			{ name: "GPIO242", description: "AGPIOCTRL for GPIO242", size: "1", shift: "18", mask: "0x40000" },
			{ name: "GPIO247", description: "AGPIOCTRL for GPIO247", size: "1", shift: "23", mask: "0x800000" },
			{ name: "GPIO253", description: "AGPIOCTRL for GPIO253", size: "1", shift: "29", mask: "0x20000000" },
		]
	},
	{ name: "GPIOINENACTRL", description: "GPIOINENACTRL Control Register", offset: "0x132",
		bits: [
			{ name: "GPIO20", description: "Input Buffer Control for GPIO20", size: "1", shift: "0", mask: "0x1" },
			{ name: "GPIO21", description: "Input Buffer Control for GPIO21", size: "1", shift: "1", mask: "0x2" },
			{ name: "GPIO62", description: "Input Buffer Control for GPIO62", size: "1", shift: "2", mask: "0x4" },
			{ name: "GPIO63", description: "Input Buffer Control for GPIO63", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "IO_DRVSEL", description: "IO Drive strength select register", offset: "0x134",
		bits: [
			{ name: "DRVSEL_GPIO2", description: "Drive select for GPIO 2", size: "1", shift: "0", mask: "0x1" },
			{ name: "DRVSEL_GPIO3", description: "Drive select for GPIO 3", size: "1", shift: "1", mask: "0x2" },
			{ name: "DRVSEL_GPIO9", description: "Drive select for GPIO 9", size: "1", shift: "2", mask: "0x4" },
			{ name: "DRVSEL_GPIO32", description: "Drive select for GPIO 32", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "IO_MODESEL", description: "IO Mode select register", offset: "0x135",
		bits: [
			{ name: "MODESEL_GPIO2", description: "Mode select for GPIO 2", size: "1", shift: "0", mask: "0x1" },
			{ name: "MODESEL_GPIO3", description: "Mode select for GPIO 3", size: "1", shift: "1", mask: "0x2" },
			{ name: "MODESEL_GPIO9", description: "Mode select for GPIO 9", size: "1", shift: "2", mask: "0x4" },
			{ name: "MODESEL_GPIO32", description: "Mode select for GPIO 32", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "ADCSOCFRCGB", description: "ADC Global SOC Force", offset: "0x136",
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
	{ name: "ADCSOCFRCGBSEL", description: "ADC Global SOC Force Select", offset: "0x138",
		bits: [
			{ name: "ADCA", description: "Generate synchronous SW trigger for ADCA", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCB", description: "Generate synchronous SW trigger for ADCB", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCC", description: "Generate synchronous SW trigger for ADCC", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADCD", description: "Generate synchronous SW trigger for ADCD", size: "1", shift: "3", mask: "0x8" },
			{ name: "ADCE", description: "Generate synchronous SW trigger for ADCE", size: "1", shift: "4", mask: "0x10" },
		]
	},
];
module.exports = {
	ASYSCTLRegisters: ASYSCTLRegisters,
}
