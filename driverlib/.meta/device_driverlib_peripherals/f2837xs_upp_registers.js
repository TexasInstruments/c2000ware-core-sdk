let UPPRegisters = [
	{ name: "PID", description: "Peripheral ID Register", offset: "0x0",
		bits: [
		]
	},
	{ name: "PERCTL", description: "Peripheral Control Register", offset: "0x2",
		bits: [
			{ name: "FREE", description: "Emulation control.", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOFT", description: "Emulation control.", size: "1", shift: "1", mask: "0x2" },
			{ name: "RTEMU", description: "Realtime emulation control.", size: "1", shift: "2", mask: "0x4" },
			{ name: "PEREN", description: "Peripheral Enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "SOFTRST", description: "Software Reset", size: "1", shift: "4", mask: "0x10" },
			{ name: "DMAST", description: "DMA Burst transaction status", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "CHCTL", description: "General Control Register", offset: "0x8",
		bits: [
			{ name: "MODE", description: "Operating mode", size: "2", shift: "0", mask: "0x3" },
			{ name: "SDRTXILA", description: "SDR TX Interleve mode", size: "1", shift: "3", mask: "0x8" },
			{ name: "DEMUXA", description: "DDR de-multiplexing mode", size: "1", shift: "4", mask: "0x10" },
			{ name: "DRA", description: "Data rate", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "IFCFG", description: "Interface Configuration Register", offset: "0xA",
		bits: [
			{ name: "STARTPOLA", description: "Polarity of START(SELECT) signal", size: "1", shift: "0", mask: "0x1" },
			{ name: "ENAPOLA", description: "Polarity of ENABLE(WRITE) signal", size: "1", shift: "1", mask: "0x2" },
			{ name: "WAITPOLA", description: "Polarity of WAIT signal.", size: "1", shift: "2", mask: "0x4" },
			{ name: "STARTA", description: "Enable Usage of START (SELECT) signal", size: "1", shift: "3", mask: "0x8" },
			{ name: "ENAA", description: "Enable Usage of ENABLE (WRITE) signal", size: "1", shift: "4", mask: "0x10" },
			{ name: "WAITA", description: "Enable Usage of WAIT signal", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLKDIVA", description: "Clock divider for tx mode", size: "4", shift: "8", mask: "0xF00" },
			{ name: "CLKINVA", description: "Clock inversion", size: "1", shift: "12", mask: "0x1000" },
			{ name: "TRISENA", description: "Pin Tri-state Control", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "IFIVAL", description: "Interface Idle Value Register", offset: "0xC",
		bits: [
			{ name: "VALA", description: "Idle Value", size: "9", shift: "0", mask: "0x1FF" },
		]
	},
	{ name: "THCFG", description: "Threshold Configuration Register", offset: "0xE",
		bits: [
			{ name: "RDSIZEI", description: "DMA Read Threshold for DMA Channel I", size: "2", shift: "0", mask: "0x3" },
			{ name: "RDSIZEQ", description: "DMA Read Threshold for DMA Channel Q", size: "2", shift: "8", mask: "0x300" },
			{ name: "TXSIZEA", description: "I/O Transmit Threshold Value", size: "2", shift: "16", mask: "0x30000" },
		]
	},
	{ name: "RAWINTST", description: "Raw Interrupt Status Register", offset: "0x10",
		bits: [
			{ name: "DPEI", description: "Interrupt raw status for DMA programming error", size: "1", shift: "0", mask: "0x1" },
			{ name: "UOEI", description: "Interrupt raw status for DMA under-run or over-run", size: "1", shift: "1", mask: "0x2" },
			{ name: "EOWI", description: "Interrupt raw status for end-of window condition", size: "1", shift: "3", mask: "0x8" },
			{ name: "EOLI", description: "Interrupt raw status for end-of-line condition", size: "1", shift: "4", mask: "0x10" },
			{ name: "DPEQ", description: "Interrupt raw status for DMA programming error", size: "1", shift: "8", mask: "0x100" },
			{ name: "UOEQ", description: "Interrupt raw status for DMA under-run or over-run", size: "1", shift: "9", mask: "0x200" },
			{ name: "EOWQ", description: "Interrupt raw status for end-of window condition", size: "1", shift: "11", mask: "0x800" },
			{ name: "EOLQ", description: "Interrupt raw status for end-of-line condition", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "ENINTST", description: "Enable Interrupt Status Register", offset: "0x12",
		bits: [
			{ name: "DPEI", description: "Interrupt enable status for DMA programming error", size: "1", shift: "0", mask: "0x1" },
			{ name: "UOEI", description: "Interrupt enable status for DMA under-run or over-run", size: "1", shift: "1", mask: "0x2" },
			{ name: "EOWI", description: "Interrupt enable status for end-of window condition", size: "1", shift: "3", mask: "0x8" },
			{ name: "EOLI", description: "Interrupt enable status for end-of-line condition", size: "1", shift: "4", mask: "0x10" },
			{ name: "DPEQ", description: "Interrupt enable status for DMA programming error", size: "1", shift: "8", mask: "0x100" },
			{ name: "UOEQ", description: "Interrupt enable status for DMA under-run or over-run", size: "1", shift: "9", mask: "0x200" },
			{ name: "EOWQ", description: "Interrupt enable status for end-of window condition", size: "1", shift: "11", mask: "0x800" },
			{ name: "EOLQ", description: "Interrupt enable status for end-of-line condition", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "INTENSET", description: "Interrupt Enable Set Register", offset: "0x14",
		bits: [
			{ name: "DPEI", description: "Interrupt enable for DMA programming error", size: "1", shift: "0", mask: "0x1" },
			{ name: "UOEI", description: "Interrupt enable for DMA under-run or over-run", size: "1", shift: "1", mask: "0x2" },
			{ name: "EOWI", description: "Interrupt enable for end-of window condition", size: "1", shift: "3", mask: "0x8" },
			{ name: "EOLI", description: "Interrupt enable for end-of-line condition", size: "1", shift: "4", mask: "0x10" },
			{ name: "DPEQ", description: "Interrupt enable for DMA programming error", size: "1", shift: "8", mask: "0x100" },
			{ name: "UOEQ", description: "Interrupt enable for DMA under-run or over-run", size: "1", shift: "9", mask: "0x200" },
			{ name: "EOWQ", description: "Interrupt enable for end-of window condition", size: "1", shift: "11", mask: "0x800" },
			{ name: "EOLQ", description: "Interrupt enable for end-of-line condition", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "INTENCLR", description: "Interrupt Enable Clear Register", offset: "0x16",
		bits: [
			{ name: "DPEI", description: "Interrupt clear for DMA programming error", size: "1", shift: "0", mask: "0x1" },
			{ name: "UOEI", description: "Interrupt clear for DMA under-run or over-run", size: "1", shift: "1", mask: "0x2" },
			{ name: "EOWI", description: "Interrupt clear for end-of window condition", size: "1", shift: "3", mask: "0x8" },
			{ name: "EOLI", description: "Interrupt clear for end-of-line condition", size: "1", shift: "4", mask: "0x10" },
			{ name: "DPEQ", description: "Interrupt clear for DMA programming error", size: "1", shift: "8", mask: "0x100" },
			{ name: "UOEQ", description: "Interrupt clear for DMA under-run or over-run", size: "1", shift: "9", mask: "0x200" },
			{ name: "EOWQ", description: "Interrupt clear for end-of window condition", size: "1", shift: "11", mask: "0x800" },
			{ name: "EOLQ", description: "Interrupt clear for end-of-line condition", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "CHIDESC0", description: "DMA Channel I Descriptor 0 Register", offset: "0x20",
		bits: [
		]
	},
	{ name: "CHIDESC1", description: "DMA Channel I Descriptor 1 Register", offset: "0x22",
		bits: [
			{ name: "BCNT", description: "Number of bytes in a line for DMA Channel I", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LCNT", description: "Number of lines in a window for DMA Channel I", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CHIDESC2", description: "DMA Channel I Descriptor 2 Register", offset: "0x24",
		bits: [
			{ name: "LOFFSET", description: "Current start address to next start address offset.", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "CHIST0", description: "DMA Channel I Status 0 Register", offset: "0x28",
		bits: [
		]
	},
	{ name: "CHIST1", description: "DMA Channel I Status 1 Register", offset: "0x2A",
		bits: [
			{ name: "BCNT", description: "Current byte number.", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LCNT", description: "Current line number.", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CHIST2", description: "DMA Channel I Status 2 Register", offset: "0x2C",
		bits: [
			{ name: "ACT", description: "Status of DMA descriptor.", size: "1", shift: "0", mask: "0x1" },
			{ name: "PEND", description: "Status of DMA.", size: "1", shift: "1", mask: "0x2" },
			{ name: "WM", description: "Watermark for FIFO block count for DMA Channel I tranfer.", size: "4", shift: "4", mask: "0xF0" },
		]
	},
	{ name: "CHQDESC0", description: "DMA Channel Q Descriptor 0 Register", offset: "0x30",
		bits: [
		]
	},
	{ name: "CHQDESC1", description: "DMA Channel Q Descriptor 1 Register", offset: "0x32",
		bits: [
			{ name: "BCNT", description: "Number of bytes in a line for DMA Channel Q", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LCNT", description: "Number of lines in a window for DMA Channel Q", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CHQDESC2", description: "DMA Channel Q Descriptor 2 Register", offset: "0x34",
		bits: [
			{ name: "LOFFSET", description: "Current start address to next start address offset.", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "CHQST0", description: "DMA Channel Q Status 0 Register", offset: "0x38",
		bits: [
		]
	},
	{ name: "CHQST1", description: "DMA Channel Q Status 1 Register", offset: "0x3A",
		bits: [
			{ name: "BCNT", description: "Current byte number.", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LCNT", description: "Current line number.", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CHQST2", description: "DMA Channel Q Status 2 Register", offset: "0x3C",
		bits: [
			{ name: "ACT", description: "Status of DMA descriptor.", size: "1", shift: "0", mask: "0x1" },
			{ name: "PEND", description: "Status of DMA.", size: "1", shift: "1", mask: "0x2" },
			{ name: "WM", description: "Watermark for FIFO block count for DMA Channel Q tranfer.", size: "4", shift: "4", mask: "0xF0" },
		]
	},
	{ name: "GINTEN", description: "Global Peripheral Interrupt Enable Register", offset: "0x40",
		bits: [
			{ name: "GINTEN", description: "Global Interrupt Enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GINTFLG", description: "Global Peripheral Interrupt Flag Register", offset: "0x42",
		bits: [
			{ name: "GINTFLG", description: "Global Interrupt Flag", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GINTCLR", description: "Global Peripheral Interrupt Clear Register", offset: "0x44",
		bits: [
			{ name: "GINTCLR", description: "Global Interrupt Clear", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "DLYCTL", description: "IO clock data skew control Register", offset: "0x46",
		bits: [
			{ name: "DLYDIS", description: "IO dealy control disable.", size: "1", shift: "0", mask: "0x1" },
			{ name: "DLYCTL", description: "IO delay control.", size: "2", shift: "1", mask: "0x6" },
		]
	},
];
module.exports = {
	UPPRegisters: UPPRegisters,
}
