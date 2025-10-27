let ASYSCTLRegisters = [
	{ name: "ADCOSDETECT", description: "I2V Logic Control", offset: "0x2C",
		bits: [
			{ name: "OSDETECT_EN", description: "Enable OS Detect Logic", size: "1", shift: "4", mask: "0x10" },
			{ name: "DETECTCFG", description: "OS Detect configuration bits", size: "3", shift: "5", mask: "0xE0" },
		]
	},
	{ name: "REFCONFIGA", description: "Config register for analog reference A.", offset: "0x3A",
		bits: [
			{ name: "ANAREFSEL", description: "Analog reference mode select", size: "1", shift: "20", mask: "0x100000" },
		]
	},
	{ name: "INTERNALTESTCTL", description: "INTERNALTEST Node Control Register", offset: "0x56",
		bits: [
			{ name: "TESTSEL", description: "Test Select", size: "6", shift: "0", mask: "0x3F" },
		]
	},
	{ name: "CONFIGLOCK", description: "Lock Register for all the config registers.", offset: "0x6A",
		bits: [
			{ name: "AGPIOCTRL", description: "Locks all AGPIOCTRL Register", size: "1", shift: "3", mask: "0x8" },
			{ name: "GPIOINENACTRL", description: "Locks all GPIOINENACTRL Register", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "TSNSCTL", description: "Temperature Sensor Control Register", offset: "0x6C",
		bits: [
			{ name: "ENABLE", description: "Temperature Sensor Enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "ANAREFCTL", description: "Analog Reference Control Register. This register is", offset: "0x74",
		bits: [
			{ name: "ANAREF2P5SEL", description: "Analog Reference Select", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "VMONCTL", description: "Voltage Monitor Control Register", offset: "0x7C",
		bits: [
			{ name: "BORLVMONDIS", description: "Disable BORL(ow) feature on VDDIO", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "CMPHPMXSEL", description: "Bits to select one of the many sources on CompHP", offset: "0x8E",
		bits: [
			{ name: "CMP1HPMXSEL", description: "CMP1HPMXSEL bits", size: "3", shift: "0", mask: "0x7" },
			{ name: "CMP2HPMXSEL", description: "CMP2HPMXSEL bits", size: "3", shift: "3", mask: "0x38" },
			{ name: "CMP3HPMXSEL", description: "CMP3HPMXSEL bits", size: "3", shift: "6", mask: "0x1C0" },
		]
	},
	{ name: "CMPLPMXSEL", description: "Bits to select one of the many sources on CompLP", offset: "0x90",
		bits: [
			{ name: "CMP1LPMXSEL", description: "CMP1LPMXSEL bits", size: "3", shift: "0", mask: "0x7" },
			{ name: "CMP2LPMXSEL", description: "CMP2LPMXSEL bits", size: "3", shift: "3", mask: "0x38" },
			{ name: "CMP3LPMXSEL", description: "CMP3LPMXSEL bits", size: "3", shift: "6", mask: "0x1C0" },
		]
	},
	{ name: "CMPHNMXSEL", description: "Bits to select one of the many sources on CompHN", offset: "0x92",
		bits: [
			{ name: "CMP1HNMXSEL", description: "CMP1HNMXSEL bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMP2HNMXSEL", description: "CMP2HNMXSEL bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMP3HNMXSEL", description: "CMP3HNMXSEL bits", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "CMPLNMXSEL", description: "Bits to select one of the many sources on CompLN", offset: "0x93",
		bits: [
			{ name: "CMP1LNMXSEL", description: "CMP1LNMXSEL bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMP2LNMXSEL", description: "CMP2LNMXSEL bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMP3LNMXSEL", description: "CMP3LNMXSEL bits", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "ADCDACLOOPBACK", description: "Enabble loopback from DAC to ADCs", offset: "0x94",
		bits: [
			{ name: "ENLB2ADCA", description: "Enable CMPSS.DAC loopback to ADCA", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Key to enable writes", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CMPSSCTL", description: "CMPSS Control Register", offset: "0x97",
		bits: [
			{ name: "CMP3LDACOUTEN", description: "Enable general purpose DAC functionality for", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPSSCTLEN", description: "Enable the CMPSSCTL Register", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "LOCK", description: "Lock Register", offset: "0x9A",
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
		]
	},
	{ name: "AGPIOCTRLA", description: "AGPIO Control Register", offset: "0x120",
		bits: [
			{ name: "GPIO12", description: "AGPIOCTRL for GPIO12", size: "1", shift: "12", mask: "0x1000" },
			{ name: "GPIO13", description: "AGPIOCTRL for GPIO13", size: "1", shift: "13", mask: "0x2000" },
			{ name: "GPIO28", description: "AGPIOCTRL for GPIO28", size: "1", shift: "28", mask: "0x10000000" },
		]
	},
	{ name: "AGPIOCTRLH", description: "AGPIO Control Register", offset: "0x12E",
		bits: [
			{ name: "GPIO224", description: "AGPIOCTRL for GPIO224", size: "1", shift: "0", mask: "0x1" },
			{ name: "GPIO226", description: "AGPIOCTRL for GPIO226", size: "1", shift: "2", mask: "0x4" },
			{ name: "GPIO227", description: "AGPIOCTRL for GPIO227", size: "1", shift: "3", mask: "0x8" },
			{ name: "GPIO228", description: "AGPIOCTRL for GPIO228", size: "1", shift: "4", mask: "0x10" },
			{ name: "GPIO230", description: "AGPIOCTRL for GPIO230", size: "1", shift: "6", mask: "0x40" },
			{ name: "GPIO242", description: "AGPIOCTRL for GPIO242", size: "1", shift: "18", mask: "0x40000" },
			{ name: "GPIO243", description: "AGPIOCTRL for GPIO243", size: "1", shift: "19", mask: "0x80000" },
		]
	},
	{ name: "GPIOINENACTRL", description: "GPIOINENACTRL Control Register", offset: "0x140",
		bits: [
			{ name: "GPIO43", description: "Input Buffer Control for GPIO43", size: "1", shift: "0", mask: "0x1" },
			{ name: "GPIO44", description: "Input Buffer Control for GPIO44", size: "1", shift: "1", mask: "0x2" },
			{ name: "GPIO45", description: "Input Buffer Control for GPIO45", size: "1", shift: "2", mask: "0x4" },
		]
	},
];
module.exports = {
	ASYSCTLRegisters: ASYSCTLRegisters,
}
