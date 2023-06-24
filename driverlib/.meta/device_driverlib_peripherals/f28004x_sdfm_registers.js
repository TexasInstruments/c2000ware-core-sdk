let SDFMRegisters = [
	{ name: "SDIFLG", description: "SD Interrupt Flag Register", offset: "0x0",
		bits: [
			{ name: "IFH1", description: "High-level Interrupt flag for Ch1", size: "1", shift: "0", mask: "0x1" },
			{ name: "IFL1", description: "Low-level Interrupt flag for Ch1", size: "1", shift: "1", mask: "0x2" },
			{ name: "IFH2", description: "High-level Interrupt flag for Ch2", size: "1", shift: "2", mask: "0x4" },
			{ name: "IFL2", description: "Low-level Interrupt flag for Ch2", size: "1", shift: "3", mask: "0x8" },
			{ name: "IFH3", description: "High-level Interrupt flag for Ch3", size: "1", shift: "4", mask: "0x10" },
			{ name: "IFL3", description: "Low-level Interrupt flag for Ch3", size: "1", shift: "5", mask: "0x20" },
			{ name: "IFH4", description: "High-level Interrupt flag for Ch4", size: "1", shift: "6", mask: "0x40" },
			{ name: "IFL4", description: "Low-level Interrupt flag for Ch4", size: "1", shift: "7", mask: "0x80" },
			{ name: "MF1", description: "Modulator Failure for Filter 1", size: "1", shift: "8", mask: "0x100" },
			{ name: "MF2", description: "Modulator Failure for Filter 2", size: "1", shift: "9", mask: "0x200" },
			{ name: "MF3", description: "Modulator Failure for Filter 3", size: "1", shift: "10", mask: "0x400" },
			{ name: "MF4", description: "Modulator Failure for Filter 4", size: "1", shift: "11", mask: "0x800" },
			{ name: "AF1", description: "Acknowledge flag for Filter 1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "AF2", description: "Acknowledge flag for Filter 2", size: "1", shift: "13", mask: "0x2000" },
			{ name: "AF3", description: "Acknowledge flag for Filter 3", size: "1", shift: "14", mask: "0x4000" },
			{ name: "AF4", description: "Acknowledge flag for Filter 4", size: "1", shift: "15", mask: "0x8000" },
			{ name: "SDFFOVF1", description: "FIFO Overflow Flag for Ch1.", size: "1", shift: "16", mask: "0x10000" },
			{ name: "SDFFOVF2", description: "FIFO Overflow Flag for Ch2", size: "1", shift: "17", mask: "0x20000" },
			{ name: "SDFFOVF3", description: "FIFO Overflow Flag for Ch3", size: "1", shift: "18", mask: "0x40000" },
			{ name: "SDFFOVF4", description: "FIFO Overflow Flag for Ch4", size: "1", shift: "19", mask: "0x80000" },
			{ name: "SDFFINT1", description: "SDFIFO interrupt for Ch1", size: "1", shift: "20", mask: "0x100000" },
			{ name: "SDFFINT2", description: "SDFIFO interrupt for Ch2", size: "1", shift: "21", mask: "0x200000" },
			{ name: "SDFFINT3", description: "SDFIFO interrupt for Ch3", size: "1", shift: "22", mask: "0x400000" },
			{ name: "SDFFINT4", description: "SDFIFO interrupt for Ch4", size: "1", shift: "23", mask: "0x800000" },
			{ name: "MIF", description: "Master Interrupt Flag", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SDIFLGCLR", description: "SD Interrupt Flag Clear Register", offset: "0x2",
		bits: [
			{ name: "IFH1", description: "High-level Interrupt flag for Ch1", size: "1", shift: "0", mask: "0x1" },
			{ name: "IFL1", description: "Low-level Interrupt flag for Ch1", size: "1", shift: "1", mask: "0x2" },
			{ name: "IFH2", description: "High-level Interrupt flag for Ch2", size: "1", shift: "2", mask: "0x4" },
			{ name: "IFL2", description: "Low-level Interrupt flag for Ch2", size: "1", shift: "3", mask: "0x8" },
			{ name: "IFH3", description: "High-level Interrupt flag for Ch3", size: "1", shift: "4", mask: "0x10" },
			{ name: "IFL3", description: "Low-level Interrupt flag for Ch3", size: "1", shift: "5", mask: "0x20" },
			{ name: "IFH4", description: "High-level Interrupt flag for Ch4", size: "1", shift: "6", mask: "0x40" },
			{ name: "IFL4", description: "Low-level Interrupt flag for Ch4", size: "1", shift: "7", mask: "0x80" },
			{ name: "MF1", description: "Modulator Failure for Filter 1", size: "1", shift: "8", mask: "0x100" },
			{ name: "MF2", description: "Modulator Failure for Filter 2", size: "1", shift: "9", mask: "0x200" },
			{ name: "MF3", description: "Modulator Failure for Filter 3", size: "1", shift: "10", mask: "0x400" },
			{ name: "MF4", description: "Modulator Failure for Filter 4", size: "1", shift: "11", mask: "0x800" },
			{ name: "AF1", description: "Acknowledge flag for Filter 1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "AF2", description: "Acknowledge flag for Filter 2", size: "1", shift: "13", mask: "0x2000" },
			{ name: "AF3", description: "Acknowledge flag for Filter 3", size: "1", shift: "14", mask: "0x4000" },
			{ name: "AF4", description: "Acknowledge flag for Filter 4", size: "1", shift: "15", mask: "0x8000" },
			{ name: "SDFFOVF1", description: "SDFIFO overflow clear Ch1", size: "1", shift: "16", mask: "0x10000" },
			{ name: "SDFFOVF2", description: "SDFIFO overflow clear Ch2", size: "1", shift: "17", mask: "0x20000" },
			{ name: "SDFFOVF3", description: "SDFIFO overflow clear Ch3", size: "1", shift: "18", mask: "0x40000" },
			{ name: "SDFFOVF4", description: "SDFIFO overflow clear Ch4", size: "1", shift: "19", mask: "0x80000" },
			{ name: "SDFFINT1", description: "SDFIFO Interrupt flag-clear bit for Ch1", size: "1", shift: "20", mask: "0x100000" },
			{ name: "SDFFINT2", description: "SDFIFO Interrupt flag-clear bit for Ch2", size: "1", shift: "21", mask: "0x200000" },
			{ name: "SDFFINT3", description: "SDFIFO Interrupt flag-clear bit for Ch3", size: "1", shift: "22", mask: "0x400000" },
			{ name: "SDFFINT4", description: "SDFIFO Interrupt flag-clear bit for Ch4", size: "1", shift: "23", mask: "0x800000" },
			{ name: "MIF", description: "Master Interrupt Flag", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SDCTL", description: "SD Control Register", offset: "0x4",
		bits: [
			{ name: "HZ1", description: "High-level Threshold crossing (Z) flag Ch1", size: "1", shift: "0", mask: "0x1" },
			{ name: "HZ2", description: "High-level Threshold crossing (Z) flag Ch2", size: "1", shift: "1", mask: "0x2" },
			{ name: "HZ3", description: "High-level Threshold crossing (Z) flag Ch3", size: "1", shift: "2", mask: "0x4" },
			{ name: "HZ4", description: "High-level Threshold crossing (Z) flag Ch4", size: "1", shift: "3", mask: "0x8" },
			{ name: "MIE", description: "Master SDy_ERR Interrupt enable", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "SDMFILEN", description: "SD Master Filter Enable", offset: "0x6",
		bits: [
			{ name: "MFE", description: "Master Filter Enable.", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "SDSTATUS", description: "SD Status Register", offset: "0x7",
		bits: [
			{ name: "HZ1", description: "High-level Threshold crossing (Z) flag Ch1", size: "1", shift: "0", mask: "0x1" },
			{ name: "HZ2", description: "High-level Threshold crossing (Z) flag Ch2", size: "1", shift: "1", mask: "0x2" },
			{ name: "HZ3", description: "High-level Threshold crossing (Z) flag Ch3", size: "1", shift: "2", mask: "0x4" },
			{ name: "HZ4", description: "High-level Threshold crossing (Z) flag Ch4", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "SDCTLPARM1", description: "Control Parameter Register for Ch1", offset: "0x10",
		bits: [
			{ name: "MOD", description: "Modulator clocking modes", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "SDDFPARM1", description: "Data Filter Parameter Register for Ch1", offset: "0x11",
		bits: [
			{ name: "DOSR", description: "Data Filter Oversample Ratio= DOSR+1", size: "8", shift: "0", mask: "0xFF" },
			{ name: "FEN", description: "Filter Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "AE", description: "Ack Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SST", description: "Data filter Structure (SincFast/1/2/3)", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SDSYNCEN", description: "Data Filter Reset Enable", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "SDDPARM1", description: "Data Parameter Register for Ch1", offset: "0x12",
		bits: [
			{ name: "DR", description: "Data Representation (0/1 = 16/32b 2's complement)", size: "1", shift: "10", mask: "0x400" },
			{ name: "SH", description: "Shift Control (# bits to shift in 16b mode)", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "SDCMPH1", description: "High-level Threshold Register for Ch1", offset: "0x13",
		bits: [
			{ name: "HLT", description: "High-level threshold for the comparator filter output", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCMPL1", description: "Low-level Threshold Register for Ch1", offset: "0x14",
		bits: [
			{ name: "LLT", description: "Low-level threshold for the comparator filter output", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCPARM1", description: "Comparator Filter Parameter Register for Ch1", offset: "0x15",
		bits: [
			{ name: "COSR", description: "Comparator Oversample Ratio. Actual rate COSR+1", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IEH", description: "High-level Interrupt enable.", size: "1", shift: "5", mask: "0x20" },
			{ name: "IEL", description: "Low-level interrupt enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "CS1_CS0", description: "Comparator Filter Structure (SincFast/1/2/3)", size: "2", shift: "7", mask: "0x180" },
			{ name: "MFIE", description: "Modulator Failure Interrupt enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "HZEN", description: "High level (Z) Threshold crossing output enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "CEN", description: "Comparator Enable", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "SDDATA1", description: "Data Filter Data Register (16 or 32bit) for Ch1", offset: "0x16",
		bits: [
			{ name: "DATA16", description: "Lo-order 16b in 32b mode", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode, 16-bit Data in 16b", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SDDATFIFO1", description: "Filter Data FIFO Output(32b) for Ch1", offset: "0x18",
		bits: [
			{ name: "DATA16", description: "Lo-order 16b in 32b mode", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode, 16-bit Data in 16b", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SDCDATA1", description: "Comparator Filter Data Register (16b) for Ch1", offset: "0x1A",
		bits: [
		]
	},
	{ name: "SDCMPHZ1", description: "High-level (Z) Threshold Register for Ch1", offset: "0x1C",
		bits: [
			{ name: "HLTZ", description: "High-level threshold (Z) for the comparator filter", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDFIFOCTL1", description: "FIFO Control Register for Ch1", offset: "0x1D",
		bits: [
			{ name: "SDFFIL", description: "SDFIFO Interrupt Level", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SDFFST", description: "SDFIFO Status", size: "5", shift: "6", mask: "0x7C0" },
			{ name: "FFIEN", description: "SDFIFO data ready Interrupt Enable", size: "1", shift: "12", mask: "0x1000" },
			{ name: "FFEN", description: "SDFIFO Enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "DRINTSEL", description: "Data-Ready Interrupt Source Select", size: "1", shift: "14", mask: "0x4000" },
			{ name: "OVFIEN", description: "SDFIFO Overflow interrupt enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SDSYNC1", description: "SD Filter Sync control for Ch1", offset: "0x1E",
		bits: [
			{ name: "SYNCSEL", description: "SDSYNC Source Select", size: "6", shift: "0", mask: "0x3F" },
			{ name: "WTSYNCEN", description: "Wait-for-Sync Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "WTSYNFLG", description: "Wait-for-Sync Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "WTSYNCLR", description: "Wait-for-Sync Flag Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "FFSYNCCLREN", description: "FIFO Clear-on-SDSYNC Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "WTSCLREN", description: "WTSYNFLG Clear-on-FIFOINT Enable", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "SDCTLPARM2", description: "Control Parameter Register for Ch2", offset: "0x20",
		bits: [
			{ name: "MOD", description: "Modulator clocking modes", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "SDDFPARM2", description: "Data Filter Parameter Register for Ch2", offset: "0x21",
		bits: [
			{ name: "DOSR", description: "Data Filter Oversample Ratio= DOSR+1", size: "8", shift: "0", mask: "0xFF" },
			{ name: "FEN", description: "Filter Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "AE", description: "Ack Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SST", description: "Data filter Structure (SincFast/1/2/3)", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SDSYNCEN", description: "Data Filter Reset Enable", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "SDDPARM2", description: "Data Parameter Register for Ch2", offset: "0x22",
		bits: [
			{ name: "DR", description: "Data Representation (0/1 = 16/32b 2's complement)", size: "1", shift: "10", mask: "0x400" },
			{ name: "SH", description: "Shift Control (# bits to shift in 16b mode)", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "SDCMPH2", description: "High-level Threshold Register for Ch2", offset: "0x23",
		bits: [
			{ name: "HLT", description: "High-level threshold for the comparator filter output", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCMPL2", description: "Low-level Threshold Register for Ch2", offset: "0x24",
		bits: [
			{ name: "LLT", description: "Low-level threshold for the comparator filter output", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCPARM2", description: "Comparator Filter Parameter Register for Ch2", offset: "0x25",
		bits: [
			{ name: "COSR", description: "Comparator Oversample Ratio. Actual rate COSR+1", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IEH", description: "High-level Interrupt enable.", size: "1", shift: "5", mask: "0x20" },
			{ name: "IEL", description: "Low-level interrupt enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "CS1_CS0", description: "Comparator Filter Structure (SincFast/1/2/3)", size: "2", shift: "7", mask: "0x180" },
			{ name: "MFIE", description: "Modulator Failure Interrupt enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "HZEN", description: "High level (Z) Threshold crossing output enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "CEN", description: "Comparator Enable", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "SDDATA2", description: "Data Filter Data Register (16 or 32bit) for Ch2", offset: "0x26",
		bits: [
			{ name: "DATA16", description: "Lo-order 16b in 32b mode", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode, 16-bit Data in 16b", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SDDATFIFO2", description: "Filter Data FIFO Output(32b) for Ch2", offset: "0x28",
		bits: [
			{ name: "DATA16", description: "Lo-order 16b in 32b mode", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode, 16-bit Data in 16b", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SDCDATA2", description: "Comparator Filter Data Register (16b) for Ch2", offset: "0x2A",
		bits: [
		]
	},
	{ name: "SDCMPHZ2", description: "High-level (Z) Threshold Register for Ch2", offset: "0x2C",
		bits: [
			{ name: "HLTZ", description: "High-level threshold (Z) for the comparator filter", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDFIFOCTL2", description: "FIFO Control Register for Ch2", offset: "0x2D",
		bits: [
			{ name: "SDFFIL", description: "SDFIFO Interrupt Level", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SDFFST", description: "SDFIFO Status", size: "5", shift: "6", mask: "0x7C0" },
			{ name: "FFIEN", description: "SDFIFO data ready Interrupt Enable", size: "1", shift: "12", mask: "0x1000" },
			{ name: "FFEN", description: "SDFIFO Enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "DRINTSEL", description: "Data-Ready Interrupt Source Select", size: "1", shift: "14", mask: "0x4000" },
			{ name: "OVFIEN", description: "SDFIFO Overflow interrupt enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SDSYNC2", description: "SD Filter Sync control for Ch2", offset: "0x2E",
		bits: [
			{ name: "SYNCSEL", description: "SDSYNC Source Select", size: "6", shift: "0", mask: "0x3F" },
			{ name: "WTSYNCEN", description: "Wait-for-Sync Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "WTSYNFLG", description: "Wait-for-Sync Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "WTSYNCLR", description: "Wait-for-Sync Flag Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "FFSYNCCLREN", description: "FIFO Clear-on-SDSYNC Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "WTSCLREN", description: "WTSYNFLG Clear-on-FIFOINT Enable", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "SDCTLPARM3", description: "Control Parameter Register for Ch3", offset: "0x30",
		bits: [
			{ name: "MOD", description: "Modulator clocking modes", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "SDDFPARM3", description: "Data Filter Parameter Register for Ch3", offset: "0x31",
		bits: [
			{ name: "DOSR", description: "Data Filter Oversample Ratio= DOSR+1", size: "8", shift: "0", mask: "0xFF" },
			{ name: "FEN", description: "Filter Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "AE", description: "Ack Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SST", description: "Data filter Structure (SincFast/1/2/3)", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SDSYNCEN", description: "Data Filter Reset Enable", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "SDDPARM3", description: "Data Parameter Register for Ch3", offset: "0x32",
		bits: [
			{ name: "DR", description: "Data Representation (0/1 = 16/32b 2's complement)", size: "1", shift: "10", mask: "0x400" },
			{ name: "SH", description: "Shift Control (# bits to shift in 16b mode)", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "SDCMPH3", description: "High-level Threshold Register for Ch3", offset: "0x33",
		bits: [
			{ name: "HLT", description: "High-level threshold for the comparator filter output", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCMPL3", description: "Low-level Threshold Register for Ch3", offset: "0x34",
		bits: [
			{ name: "LLT", description: "Low-level threshold for the comparator filter output", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCPARM3", description: "Comparator Filter Parameter Register for Ch3", offset: "0x35",
		bits: [
			{ name: "COSR", description: "Comparator Oversample Ratio. Actual rate COSR+1", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IEH", description: "High-level Interrupt enable.", size: "1", shift: "5", mask: "0x20" },
			{ name: "IEL", description: "Low-level interrupt enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "CS1_CS0", description: "Comparator Filter Structure (SincFast/1/2/3)", size: "2", shift: "7", mask: "0x180" },
			{ name: "MFIE", description: "Modulator Failure Interrupt enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "HZEN", description: "High level (Z) Threshold crossing output enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "CEN", description: "Comparator Enable", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "SDDATA3", description: "Data Filter Data Register (16 or 32bit) for Ch3", offset: "0x36",
		bits: [
			{ name: "DATA16", description: "Lo-order 16b in 32b mode", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode, 16-bit Data in 16b", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SDDATFIFO3", description: "Filter Data FIFO Output(32b) for Ch3", offset: "0x38",
		bits: [
			{ name: "DATA16", description: "Lo-order 16b in 32b mode", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode, 16-bit Data in 16b", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SDCDATA3", description: "Comparator Filter Data Register (16b) for Ch3", offset: "0x3A",
		bits: [
		]
	},
	{ name: "SDCMPHZ3", description: "High-level (Z) Threshold Register for Ch3", offset: "0x3C",
		bits: [
			{ name: "HLTZ", description: "High-level threshold (Z) for the comparator filter", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDFIFOCTL3", description: "FIFO Control Register for Ch3", offset: "0x3D",
		bits: [
			{ name: "SDFFIL", description: "SDFIFO Interrupt Level", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SDFFST", description: "SDFIFO Status", size: "5", shift: "6", mask: "0x7C0" },
			{ name: "FFIEN", description: "SDFIFO data ready Interrupt Enable", size: "1", shift: "12", mask: "0x1000" },
			{ name: "FFEN", description: "SDFIFO Enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "DRINTSEL", description: "Data-Ready Interrupt Source Select", size: "1", shift: "14", mask: "0x4000" },
			{ name: "OVFIEN", description: "SDFIFO Overflow interrupt enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SDSYNC3", description: "SD Filter Sync control for Ch3", offset: "0x3E",
		bits: [
			{ name: "SYNCSEL", description: "SDSYNC Source Select", size: "6", shift: "0", mask: "0x3F" },
			{ name: "WTSYNCEN", description: "Wait-for-Sync Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "WTSYNFLG", description: "Wait-for-Sync Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "WTSYNCLR", description: "Wait-for-Sync Flag Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "FFSYNCCLREN", description: "FIFO Clear-on-SDSYNC Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "WTSCLREN", description: "WTSYNFLG Clear-on-FIFOINT Enable", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "SDCTLPARM4", description: "Control Parameter Register for Ch4", offset: "0x40",
		bits: [
			{ name: "MOD", description: "Modulator clocking modes", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "SDDFPARM4", description: "Data Filter Parameter Register for Ch4", offset: "0x41",
		bits: [
			{ name: "DOSR", description: "Data Filter Oversample Ratio= DOSR+1", size: "8", shift: "0", mask: "0xFF" },
			{ name: "FEN", description: "Filter Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "AE", description: "Ack Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SST", description: "Data filter Structure (SincFast/1/2/3)", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SDSYNCEN", description: "Data Filter Reset Enable", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "SDDPARM4", description: "Data Parameter Register for Ch4", offset: "0x42",
		bits: [
			{ name: "DR", description: "Data Representation (0/1 = 16/32b 2's complement)", size: "1", shift: "10", mask: "0x400" },
			{ name: "SH", description: "Shift Control (# bits to shift in 16b mode)", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "SDCMPH4", description: "High-level Threshold Register for Ch4", offset: "0x43",
		bits: [
			{ name: "HLT", description: "High-level threshold for the comparator filter output", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCMPL4", description: "Low-level Threshold Register for Ch4", offset: "0x44",
		bits: [
			{ name: "LLT", description: "Low-level threshold for the comparator filter output", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDCPARM4", description: "Comparator Filter Parameter Register for Ch4", offset: "0x45",
		bits: [
			{ name: "COSR", description: "Comparator Oversample Ratio. Actual rate COSR+1", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IEH", description: "High-level Interrupt enable.", size: "1", shift: "5", mask: "0x20" },
			{ name: "IEL", description: "Low-level interrupt enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "CS1_CS0", description: "Comparator Filter Structure (SincFast/1/2/3)", size: "2", shift: "7", mask: "0x180" },
			{ name: "MFIE", description: "Modulator Failure Interrupt enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "HZEN", description: "High level (Z) Threshold crossing output enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "CEN", description: "Comparator Enable", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "SDDATA4", description: "Data Filter Data Register (16 or 32bit) for Ch4", offset: "0x46",
		bits: [
			{ name: "DATA16", description: "Lo-order 16b in 32b mode", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode, 16-bit Data in 16b", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SDDATFIFO4", description: "Filter Data FIFO Output(32b) for Ch4", offset: "0x48",
		bits: [
			{ name: "DATA16", description: "Lo-order 16b in 32b mode", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA32HI", description: "Hi-order 16b in 32b mode, 16-bit Data in 16b", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SDCDATA4", description: "Comparator Filter Data Register (16b) for Ch4", offset: "0x4A",
		bits: [
		]
	},
	{ name: "SDCMPHZ4", description: "High-level (Z) Threshold Register for Ch4", offset: "0x4C",
		bits: [
			{ name: "HLTZ", description: "High-level threshold (Z) for the comparator filter", size: "15", shift: "0", mask: "0x7FFF" },
		]
	},
	{ name: "SDFIFOCTL4", description: "FIFO Control Register for Ch4", offset: "0x4D",
		bits: [
			{ name: "SDFFIL", description: "SDFIFO Interrupt Level", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SDFFST", description: "SDFIFO Status", size: "5", shift: "6", mask: "0x7C0" },
			{ name: "FFIEN", description: "SDFIFO data ready Interrupt Enable", size: "1", shift: "12", mask: "0x1000" },
			{ name: "FFEN", description: "SDFIFO Enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "DRINTSEL", description: "Data-Ready Interrupt Source Select", size: "1", shift: "14", mask: "0x4000" },
			{ name: "OVFIEN", description: "SDFIFO Overflow interrupt enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SDSYNC4", description: "SD Filter Sync control for Ch4", offset: "0x4E",
		bits: [
			{ name: "SYNCSEL", description: "SDSYNC Source Select", size: "6", shift: "0", mask: "0x3F" },
			{ name: "WTSYNCEN", description: "Wait-for-Sync Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "WTSYNFLG", description: "Wait-for-Sync Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "WTSYNCLR", description: "Wait-for-Sync Flag Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "FFSYNCCLREN", description: "FIFO Clear-on-SDSYNC Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "WTSCLREN", description: "WTSYNFLG Clear-on-FIFOINT Enable", size: "1", shift: "10", mask: "0x400" },
		]
	},
];
module.exports = {
	SDFMRegisters: SDFMRegisters,
}
