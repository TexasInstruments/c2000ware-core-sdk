let ASYSCTLRegisters = [
	{ name: "INTERNALTESTCTL", description: "INTERNALTEST Node Control Register", offset: "0x4A",
		bits: [
			{ name: "TESTSEL", description: "Test Select", size: "5", shift: "0", mask: "0x1F" },
			{ name: "KEY", description: "Key to Enable writes", size: "16", shift: "16", mask: "0xFFFF0000" },
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
	{ name: "ANAREFCTL", description: "Analog Reference Control Register", offset: "0x68",
		bits: [
			{ name: "ANAREFSEL", description: "Analog Reference Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "ANAREF2P5SEL", description: "Analog Reference Select", size: "1", shift: "8", mask: "0x100" },
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
			{ name: "ENLB2ADCA", description: "Enable DACL loopback to ADCA", size: "1", shift: "0", mask: "0x1" },
			{ name: "ENLB2ADCC", description: "Enable DACL loopback to ADCC", size: "1", shift: "2", mask: "0x4" },
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
		]
	},
	{ name: "AGPIOCTRLA", description: "AGPIO Control Register", offset: "0x102",
		bits: [
			{ name: "GPIO20", description: "AGPIOCTRL for GPIO20", size: "1", shift: "20", mask: "0x100000" },
			{ name: "GPIO21", description: "AGPIOCTRL for GPIO21", size: "1", shift: "21", mask: "0x200000" },
		]
	},
];
module.exports = {
	ASYSCTLRegisters: ASYSCTLRegisters,
}
