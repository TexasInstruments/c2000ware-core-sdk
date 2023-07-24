let ASYSCTLRegisters = [
	{ name: "EXTROSCCSR1", description: "ExtR Oscillator Status Register", offset: "0x24",
		bits: [
			{ name: "OSCSTATUS", description: "Running status of ExtR.", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "CONFIGLOCK", description: "Lock Register for all the config registers.", offset: "0x5E",
		bits: [
			{ name: "AGPIOCTRL", description: "Locks all AGPIOCTRL Register", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "TSNSCTL", description: "Temperature Sensor Control Register", offset: "0x60",
		bits: [
			{ name: "ENABLE", description: "Temperature Sensor Enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "ANAREFCTL", description: "Analog Reference Control Register. This register is", offset: "0x68",
		bits: [
			{ name: "ANAREFSEL", description: "Analog Reference Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "ANAREF2P5SEL", description: "Analog Reference Select", size: "1", shift: "8", mask: "0x100" },
			{ name: "ANAREFSEL_SUP_OVERRIDE", description: "Control for overriding the analog", size: "1", shift: "15", mask: "0x8000" },
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
			{ name: "ENLB2ADCC", description: "Enable DACA loopback to ADCC", size: "1", shift: "2", mask: "0x4" },
			{ name: "KEY", description: "Key to enable writes", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CMPSSCTL", description: "CMPSS Control Register", offset: "0x8B",
		bits: [
			{ name: "CMP1LDACOUTEN", description: "Enable general purpose DAC functionality for", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPSSCTLEN", description: "Enable the CMPSSCTL Register", size: "1", shift: "15", mask: "0x8000" },
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
		]
	},
	{ name: "AGPIOCTRLA", description: "AGPIO Control Register", offset: "0x10A",
		bits: [
			{ name: "GPIO12", description: "AGPIOCTRL for GPIO12", size: "1", shift: "12", mask: "0x1000" },
			{ name: "GPIO13", description: "AGPIOCTRL for GPIO13", size: "1", shift: "13", mask: "0x2000" },
			{ name: "GPIO20", description: "AGPIOCTRL for GPIO20", size: "1", shift: "20", mask: "0x100000" },
			{ name: "GPIO21", description: "AGPIOCTRL for GPIO21", size: "1", shift: "21", mask: "0x200000" },
			{ name: "GPIO28", description: "AGPIOCTRL for GPIO28", size: "1", shift: "28", mask: "0x10000000" },
		]
	},
	{ name: "AGPIOCTRLH", description: "AGPIO Control Register", offset: "0x118",
		bits: [
			{ name: "GPIO224", description: "AGPIOCTRL for GPIO224", size: "1", shift: "0", mask: "0x1" },
			{ name: "GPIO226", description: "AGPIOCTRL for GPIO226", size: "1", shift: "2", mask: "0x4" },
			{ name: "GPIO227", description: "AGPIOCTRL for GPIO227", size: "1", shift: "3", mask: "0x8" },
			{ name: "GPIO228", description: "AGPIOCTRL for GPIO228", size: "1", shift: "4", mask: "0x10" },
			{ name: "GPIO230", description: "AGPIOCTRL for GPIO230", size: "1", shift: "6", mask: "0x40" },
			{ name: "GPIO242", description: "AGPIOCTRL for GPIO242", size: "1", shift: "18", mask: "0x40000" },
		]
	},
];
module.exports = {
	ASYSCTLRegisters: ASYSCTLRegisters,
}
