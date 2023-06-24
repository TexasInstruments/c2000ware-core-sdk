let ASYSCTLRegisters = [
	{ name: "ANAREFPP", description: "ADC Analog Reference Peripheral Properties register. The", offset: "0x1E",
		bits: [
			{ name: "ANAREFBDIS", description: "Disable ANAREFB", size: "1", shift: "0", mask: "0x1" },
			{ name: "ANAREFCDIS", description: "Disable ANAREFC", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "TSNSCTL", description: "Temperature Sensor Control Register", offset: "0x60",
		bits: [
			{ name: "ENABLE", description: "Temperature Sensor Enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "ANAREFCTL", description: "Analog Reference Control Register", offset: "0x68",
		bits: [
			{ name: "ANAREFASEL", description: "Analog Reference A Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "ANAREFBSEL", description: "Analog Reference B Select", size: "1", shift: "1", mask: "0x2" },
			{ name: "ANAREFCSEL", description: "Analog Reference C Select", size: "1", shift: "2", mask: "0x4" },
			{ name: "ANAREFA2P5SEL", description: "Analog Reference A Select", size: "1", shift: "8", mask: "0x100" },
			{ name: "ANAREFB2P5SEL", description: "Analog Reference B Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "ANAREFC2P5SEL", description: "Analog Reference B Select", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "VMONCTL", description: "Voltage Monitor Control Register", offset: "0x70",
		bits: [
			{ name: "BORLVMONDIS", description: "Disable BORL(ow) feature on VDDIO", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "DCDCCTL", description: "DC-DC control register.", offset: "0x78",
		bits: [
			{ name: "DCDCEN", description: "DCDC Enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "DCDCSTS", description: "DC-DC status register.", offset: "0x7A",
		bits: [
			{ name: "INDDETECT", description: "Inductor Detected", size: "1", shift: "0", mask: "0x1" },
			{ name: "SWSEQDONE", description: "Switch sequence to DC-DC done.", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CMPHPMXSEL", description: "Bits to select one of the many sources on CopmHP inputs.", offset: "0x82",
		bits: [
			{ name: "CMP1HPMXSEL", description: "CMP1HPMXSEL bits", size: "3", shift: "0", mask: "0x7" },
			{ name: "CMP2HPMXSEL", description: "CMP2HPMXSEL bits", size: "3", shift: "3", mask: "0x38" },
			{ name: "CMP3HPMXSEL", description: "CMP3HPMXSEL bits", size: "3", shift: "6", mask: "0x1C0" },
			{ name: "CMP4HPMXSEL", description: "CMP4HPMXSEL bits", size: "3", shift: "9", mask: "0xE00" },
			{ name: "CMP5HPMXSEL", description: "CMP5HPMXSEL bits", size: "3", shift: "12", mask: "0x7000" },
			{ name: "CMP6HPMXSEL", description: "CMP6HPMXSEL bits", size: "3", shift: "16", mask: "0x70000" },
			{ name: "CMP7HPMXSEL", description: "CMP7HPMXSEL bits", size: "3", shift: "19", mask: "0x380000" },
		]
	},
	{ name: "CMPLPMXSEL", description: "Bits to select one of the many sources on CopmLP inputs.", offset: "0x84",
		bits: [
			{ name: "CMP1LPMXSEL", description: "CMP1LPMXSEL bits", size: "3", shift: "0", mask: "0x7" },
			{ name: "CMP2LPMXSEL", description: "CMP2LPMXSEL bits", size: "3", shift: "3", mask: "0x38" },
			{ name: "CMP3LPMXSEL", description: "CMP3LPMXSEL bits", size: "3", shift: "6", mask: "0x1C0" },
			{ name: "CMP4LPMXSEL", description: "CMP4LPMXSEL bits", size: "3", shift: "9", mask: "0xE00" },
			{ name: "CMP5LPMXSEL", description: "CMP5LPMXSEL bits", size: "3", shift: "12", mask: "0x7000" },
			{ name: "CMP6LPMXSEL", description: "CMP6LPMXSEL bits", size: "3", shift: "16", mask: "0x70000" },
			{ name: "CMP7LPMXSEL", description: "CMP7LPMXSEL bits", size: "3", shift: "19", mask: "0x380000" },
		]
	},
	{ name: "CMPHNMXSEL", description: "Bits to select one of the many sources on CopmHN inputs.", offset: "0x86",
		bits: [
			{ name: "CMP1HNMXSEL", description: "CMP1HNMXSEL bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMP2HNMXSEL", description: "CMP2HNMXSEL bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMP3HNMXSEL", description: "CMP3HNMXSEL bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMP4HNMXSEL", description: "CMP4HNMXSEL bits", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMP5HNMXSEL", description: "CMP5HNMXSEL bits", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMP6HNMXSEL", description: "CMP6HNMXSEL bits", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMP7HNMXSEL", description: "CMP7HNMXSEL bits", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "CMPLNMXSEL", description: "Bits to select one of the many sources on CopmLN inputs.", offset: "0x87",
		bits: [
			{ name: "CMP1LNMXSEL", description: "CMP1LNMXSEL bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMP2LNMXSEL", description: "CMP2LNMXSEL bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMP3LNMXSEL", description: "CMP3LNMXSEL bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMP4LNMXSEL", description: "CMP4LNMXSEL bits", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMP5LNMXSEL", description: "CMP5LNMXSEL bits", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMP6LNMXSEL", description: "CMP6LNMXSEL bits", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMP7LNMXSEL", description: "CMP7LNMXSEL bits", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "LOCK", description: "Lock Register", offset: "0x8E",
		bits: [
			{ name: "TSNSCTL", description: "TSNSCTL Register lock bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ANAREFCTL", description: "ANAREFCTL Register lock bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "VMONCTL", description: "VMONCTL Register lock bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "DCDCCTL", description: "DCDCCTL Register lock bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "ADCINMXSEL", description: "ADCINMXSEL Register lock bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMPHPMXSEL", description: "CMPHPMXSEL Register lock bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMPLPMXSEL", description: "CMPLPMXSEL Register lock bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "CMPHNMXSEL", description: "CMPHNMXSEL Register lock bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "CMPLNMXSEL", description: "CMPLNMXSEL Register lock bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "VREGCTL", description: "VREGCTL Register lock bit", size: "1", shift: "9", mask: "0x200" },
		]
	},
];
module.exports = {
	ASYSCTLRegisters: ASYSCTLRegisters,
}
