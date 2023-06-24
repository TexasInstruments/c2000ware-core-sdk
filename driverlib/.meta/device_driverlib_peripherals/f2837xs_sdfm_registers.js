let SDFMRegisters = [
	{ name: "SDIFLG", description: "Interrupt Flag Register", offset: "0x0",
		bits: [
			{ name: "IFH1", description: "High-level Interrupt flag Filter 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "IFL1", description: "Low-Level Interrupt flag Filter 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "IFH2", description: "High-level Interrupt flag Filter 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "IFL2", description: "Low-Level Interrupt flag Filter 2", size: "1", shift: "3", mask: "0x8" },
			{ name: "IFH3", description: "High-level Interrupt flag Filter 3", size: "1", shift: "4", mask: "0x10" },
			{ name: "IFL3", description: "Low-Level Interrupt flag Filter 3", size: "1", shift: "5", mask: "0x20" },
			{ name: "IFH4", description: "High-level Interrupt flag Filter 4", size: "1", shift: "6", mask: "0x40" },
			{ name: "IFL4", description: "Low-Level Interrupt flag Filter 4", size: "1", shift: "7", mask: "0x80" },
			{ name: "MF1", description: "Modulator Failure for Filter 1", size: "1", shift: "8", mask: "0x100" },
			{ name: "MF2", description: "Modulator Failure for Filter 2", size: "1", shift: "9", mask: "0x200" },
			{ name: "MF3", description: "Modulator Failure for Filter 3", size: "1", shift: "10", mask: "0x400" },
			{ name: "MF4", description: "Modulator Failure for Filter 4", size: "1", shift: "11", mask: "0x800" },
			{ name: "AF1", description: "Acknowledge flag for Filter 1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "AF2", description: "Acknowledge flag for Filter 2", size: "1", shift: "13", mask: "0x2000" },
			{ name: "AF3", description: "Acknowledge flag for Filter 3", size: "1", shift: "14", mask: "0x4000" },
			{ name: "AF4", description: "Acknowledge flag for Filter 4", size: "1", shift: "15", mask: "0x8000" },
			{ name: "MIF", description: "Master Interrupt Flag", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SDIFLGCLR", description: "Interrupt Flag Clear Register", offset: "0x2",
		bits: [
			{ name: "IFH1", description: "High-level Interrupt flag Filter 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "IFL1", description: "Low-Level Interrupt flag Filter 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "IFH2", description: "High-level Interrupt flag Filter 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "IFL2", description: "Low-Level Interrupt flag Filter 2", size: "1", shift: "3", mask: "0x8" },
			{ name: "IFH3", description: "High-level Interrupt flag Filter 3", size: "1", shift: "4", mask: "0x10" },
			{ name: "IFL3", description: "Low-Level Interrupt flag Filter 3", size: "1", shift: "5", mask: "0x20" },
			{ name: "IFH4", description: "High-level Interrupt flag Filter 4", size: "1", shift: "6", mask: "0x40" },
			{ name: "IFL4", description: "Low-Level Interrupt flag Filter 4", size: "1", shift: "7", mask: "0x80" },
			{ name: "MF1", description: "Modulator Failure for Filter 1", size: "1", shift: "8", mask: "0x100" },
			{ name: "MF2", description: "Modulator Failure for Filter 2", size: "1", shift: "9", mask: "0x200" },
			{ name: "MF3", description: "Modulator Failure for Filter 3", size: "1", shift: "10", mask: "0x400" },
			{ name: "MF4", description: "Modulator Failure for Filter 4", size: "1", shift: "11", mask: "0x800" },
			{ name: "AF1", description: "Acknowledge flag for Filter 1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "AF2", description: "Acknowledge flag for Filter 2", size: "1", shift: "13", mask: "0x2000" },
			{ name: "AF3", description: "Acknowledge flag for Filter 3", size: "1", shift: "14", mask: "0x4000" },
			{ name: "AF4", description: "Acknowledge flag for Filter 4", size: "1", shift: "15", mask: "0x8000" },
			{ name: "MIF", description: "Master Interrupt Flag", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SDCTL", description: "SD Control Register", offset: "0x4",
		bits: [
			{ name: "MIE", description: "Master Interrupt enable", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "SDMFILEN", description: "SD Master Filter Enable", offset: "0x6",
		bits: [
			{ name: "MFE", description: "Master Filter Enable.", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "SDCTLPARM1", description: "Control Parameter Register for Ch1", offset: "0x10",
		bits: [
			{ name: "MOD", description: "Delta-Sigma Modulator mode", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "SDDFPARM1", description: "Data Filter Parameter Register for Ch1", offset: "0x11",
		bits: [
			{ name: "DOSR", description: "Data Filter Oversample Ratio= DOSR+1", size: "8", shift: "0", mask: "0xFF" },
			{ name: "FEN", description: "Filter Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "AE", description: "Ack Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SST", description: "Data Filter Structure (DataFast/1/2/3)", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SDSYNCEN", description: "Data FILTER Reset Enable", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "SDDPARM1", description: "Integer Parameter Register for Ch1", offset: "0x12",
		bits: [
			{ name: "DR", description: "Data Representation (0/1 = 16/32b 2's complement)", size: "1", shift: "10", mask: "0x400" },
			{ name: "SH", description: "Shift Control (# bits to shift in 16b mode)", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "SDCMPH1", description: "High-level Threshold Register for Ch1", offset: "0x13",
		bits: [
			{ name: "HLT", description: "High-level threshold for the comparator filter output.", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCMPL1", description: "Low-level Threshold Register for Ch1", offset: "0x14",
		bits: [
			{ name: "LLT", description: "Low-level threshold for the comparator filter output.", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCPARM1", description: "Comparator Parameter Register for Ch1", offset: "0x15",
		bits: [
			{ name: "COSR", description: "Comparator Oversample Ratio = COSR + 1", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IEH", description: "High-level interrupt enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "IEL", description: "Low-level interrupt enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "CS1_CS0", description: "Comparator filter structure", size: "2", shift: "7", mask: "0x180" },
			{ name: "MFIE", description: "Modulator Failure Interrupt enable", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "SDDATA1", description: "Filter Data Register (16 or 32bit) for Ch1", offset: "0x16",
		bits: [
			{ name: "DATA16", description: "16-bit Data in 16b mode, Lo-order 16b in 32b", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SDCTLPARM2", description: "Control Parameter Register for Ch2", offset: "0x20",
		bits: [
			{ name: "MOD", description: "Delta-Sigma Modulator mode", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "SDDFPARM2", description: "Data Filter Parameter Register for Ch2", offset: "0x21",
		bits: [
			{ name: "DOSR", description: "Data Filter Oversample Ratio= DOSR+1", size: "8", shift: "0", mask: "0xFF" },
			{ name: "FEN", description: "Filter Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "AE", description: "Ack Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SST", description: "Data Filter Structure (SincFast/1/2/3)", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SDSYNCEN", description: "Data FILTER Reset Enable", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "SDDPARM2", description: "Integer Parameter Register for Ch2", offset: "0x22",
		bits: [
			{ name: "DR", description: "Data Representation (0/1 = 16/32b 2's complement)", size: "1", shift: "10", mask: "0x400" },
			{ name: "SH", description: "Shift Control (# bits to shift in 16b mode)", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "SDCMPH2", description: "High-level Threshold Register for Ch2", offset: "0x23",
		bits: [
			{ name: "HLT", description: "High-level threshold for the comparator filter output.", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCMPL2", description: "Low-level Threshold Register for Ch2", offset: "0x24",
		bits: [
			{ name: "LLT", description: "Low-level threshold for the comparator filter output.", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCPARM2", description: "Comparator Parameter Register for Ch2", offset: "0x25",
		bits: [
			{ name: "COSR", description: "Comparator Oversample Ratio = COSR + 1", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IEH", description: "High-level interrupt enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "IEL", description: "Low-level interrupt enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "CS1_CS0", description: "Comparator filter structure", size: "2", shift: "7", mask: "0x180" },
			{ name: "MFIE", description: "Modulator Failure Interrupt enable", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "SDDATA2", description: "Filter Data Register (16 or 32bit) for Ch2", offset: "0x26",
		bits: [
			{ name: "DATA16", description: "16-bit Data in 16b mode, Lo-order 16b in 32b", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SDCTLPARM3", description: "Control Parameter Register for Ch3", offset: "0x30",
		bits: [
			{ name: "MOD", description: "Delta-Sigma Modulator mode", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "SDDFPARM3", description: "Data Filter Parameter Register for Ch3", offset: "0x31",
		bits: [
			{ name: "DOSR", description: "Data Filter Oversample Ratio= DOSR+1", size: "8", shift: "0", mask: "0xFF" },
			{ name: "FEN", description: "Filter Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "AE", description: "Ack Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SST", description: "Data filter structure (SincFast/1/2/3)", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SDSYNCEN", description: "Data FILTER Reset Enable", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "SDDPARM3", description: "Integer Parameter Register for Ch3", offset: "0x32",
		bits: [
			{ name: "DR", description: "Data Representation (0/1 = 16/32b 2's complement)", size: "1", shift: "10", mask: "0x400" },
			{ name: "SH", description: "Shift Control (# bits to shift in 16b mode)", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "SDCMPH3", description: "High-level Threshold Register for Ch3", offset: "0x33",
		bits: [
			{ name: "HLT", description: "High-level threshold for the comparator filter output.", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCMPL3", description: "Low-level Threshold Register for Ch3", offset: "0x34",
		bits: [
			{ name: "LLT", description: "Low-level threshold for the comparator filter output.", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCPARM3", description: "Comparator Parameter Register for Ch3", offset: "0x35",
		bits: [
			{ name: "COSR", description: "Comparator Oversample Ratio = COSR + 1", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IEH", description: "High-level interrupt enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "IEL", description: "Low-level interrupt enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "CS1_CS0", description: "Comparator filter structure", size: "2", shift: "7", mask: "0x180" },
			{ name: "MFIE", description: "Modulator Failure Interrupt enable", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "SDDATA3", description: "Filter Data Register (16 or 32bit) for Ch3", offset: "0x36",
		bits: [
			{ name: "DATA16", description: "16-bit Data in 16b mode, Lo-order 16b in 32b", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SDCTLPARM4", description: "Control Parameter Register for Ch4", offset: "0x40",
		bits: [
			{ name: "MOD", description: "Delta-Sigma Modulator mode", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "SDDFPARM4", description: "Data Filter Parameter Register for Ch4", offset: "0x41",
		bits: [
			{ name: "DOSR", description: "SINC Filter Oversample Ratio= DOSR+1", size: "8", shift: "0", mask: "0xFF" },
			{ name: "FEN", description: "Filter Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "AE", description: "Ack Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SST", description: "Data filter structure (SincFast/1/2/3)", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SDSYNCEN", description: "SINC FILTER Reset Enable", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "SDDPARM4", description: "Integer Parameter Register for Ch4", offset: "0x42",
		bits: [
			{ name: "DR", description: "Data Representation (0/1 = 16/32b 2's complement)", size: "1", shift: "10", mask: "0x400" },
			{ name: "SH", description: "Shift Control (# bits to shift in 16b mode)", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "SDCMPH4", description: "High-level Threshold Register for Ch4", offset: "0x43",
		bits: [
			{ name: "HLT", description: "High-level threshold for the comparator filter output.", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCMPL4", description: "Low-level Threshold Register for Ch4", offset: "0x44",
		bits: [
			{ name: "LLT", description: "Low-level threshold for the comparator filter output.", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCPARM4", description: "Comparator Parameter Register for Ch4", offset: "0x45",
		bits: [
			{ name: "COSR", description: "Comparator Oversample Ratio = COSR + 1", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IEH", description: "High-level interrupt enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "IEL", description: "Low-level interrupt enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "CS1_CS0", description: "Comparator filter structure", size: "2", shift: "7", mask: "0x180" },
			{ name: "MFIE", description: "Modulator Failure Interrupt enable", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "SDDATA4", description: "Filter Data Register (16 or 32bit) for Ch4", offset: "0x46",
		bits: [
			{ name: "DATA16", description: "16-bit Data in 16b mode, Lo-order 16b in 32b", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
];
module.exports = {
	SDFMRegisters: SDFMRegisters,
}
