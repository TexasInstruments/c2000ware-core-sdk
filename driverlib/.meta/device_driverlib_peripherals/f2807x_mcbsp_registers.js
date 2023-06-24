let MCBSPRegisters = [
	{ name: "DRR2", description: "Data receive register bits 31-16", offset: "0x0",
		bits: [
			{ name: "HWLB", description: "High word low byte", size: "8", shift: "0", mask: "0xFF" },
			{ name: "HWHB", description: "High word high byte", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "DRR1", description: "Data receive register bits 15-0", offset: "0x1",
		bits: [
			{ name: "LWLB", description: "Low word low byte", size: "8", shift: "0", mask: "0xFF" },
			{ name: "LWHB", description: "Low word high byte", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "DXR2", description: "Data transmit register bits 31-16", offset: "0x2",
		bits: [
			{ name: "HWLB", description: "High word low byte", size: "8", shift: "0", mask: "0xFF" },
			{ name: "HWHB", description: "High word high byte", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "DXR1", description: "Data transmit register bits 15-0", offset: "0x3",
		bits: [
			{ name: "LWLB", description: "Low word low byte", size: "8", shift: "0", mask: "0xFF" },
			{ name: "LWHB", description: "Low word high byte", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "SPCR2", description: "Serial port control register 2", offset: "0x4",
		bits: [
			{ name: "XRST", description: "Transmitter reset", size: "1", shift: "0", mask: "0x1" },
			{ name: "XRDY", description: "Transmitter ready", size: "1", shift: "1", mask: "0x2" },
			{ name: "XEMPTY", description: "Transmitter empty", size: "1", shift: "2", mask: "0x4" },
			{ name: "XSYNCERR", description: "Transmit sync error INT flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "XINTM", description: "Transmit Interupt mode bits", size: "2", shift: "4", mask: "0x30" },
			{ name: "GRST", description: "Sample rate generator reset", size: "1", shift: "6", mask: "0x40" },
			{ name: "FRST", description: "Frame sync logic reset", size: "1", shift: "7", mask: "0x80" },
			{ name: "SOFT", description: "SOFT bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "FREE", description: "FREE bit", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "SPCR1", description: "Serial port control register 1", offset: "0x5",
		bits: [
			{ name: "RRST", description: "Receiver reset", size: "1", shift: "0", mask: "0x1" },
			{ name: "RRDY", description: "Receiver ready", size: "1", shift: "1", mask: "0x2" },
			{ name: "RFULL", description: "Receiver full", size: "1", shift: "2", mask: "0x4" },
			{ name: "RSYNCERR", description: "Receive sync error INT flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "RINTM", description: "Receive Interupt mode bits", size: "2", shift: "4", mask: "0x30" },
			{ name: "DXENA", description: "DX delay enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "CLKSTP", description: "Clock stop mode", size: "2", shift: "11", mask: "0x1800" },
			{ name: "RJUST", description: "Rx sign extension and justification mode", size: "2", shift: "13", mask: "0x6000" },
			{ name: "DLB", description: "Digital loopback", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "RCR2", description: "Receive Control register 2", offset: "0x6",
		bits: [
			{ name: "RDATDLY", description: "Receive data delay", size: "2", shift: "0", mask: "0x3" },
			{ name: "RFIG", description: "Receive frame sync ignore", size: "1", shift: "2", mask: "0x4" },
			{ name: "RCOMPAND", description: "Receive Companding Mode selects", size: "2", shift: "3", mask: "0x18" },
			{ name: "RWDLEN2", description: "Receive word length 2", size: "3", shift: "5", mask: "0xE0" },
			{ name: "RFRLEN2", description: "Receive Frame length 2", size: "7", shift: "8", mask: "0x7F00" },
			{ name: "RPHASE", description: "Receive Phase", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "RCR1", description: "Receive Control register 1", offset: "0x7",
		bits: [
			{ name: "RWDLEN1", description: "Receive word length 1", size: "3", shift: "5", mask: "0xE0" },
			{ name: "RFRLEN1", description: "Receive Frame length 1", size: "7", shift: "8", mask: "0x7F00" },
		]
	},
	{ name: "XCR2", description: "Transmit Control register 2", offset: "0x8",
		bits: [
			{ name: "XDATDLY", description: "Transmit data delay", size: "2", shift: "0", mask: "0x3" },
			{ name: "XFIG", description: "Transmit frame sync ignore", size: "1", shift: "2", mask: "0x4" },
			{ name: "XCOMPAND", description: "Transmit Companding Mode selects", size: "2", shift: "3", mask: "0x18" },
			{ name: "XWDLEN2", description: "Transmit word length 2", size: "3", shift: "5", mask: "0xE0" },
			{ name: "XFRLEN2", description: "Transmit Frame length 2", size: "7", shift: "8", mask: "0x7F00" },
			{ name: "XPHASE", description: "Transmit Phase", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "XCR1", description: "Transmit Control register 1", offset: "0x9",
		bits: [
			{ name: "XWDLEN1", description: "Transmit word length 1", size: "3", shift: "5", mask: "0xE0" },
			{ name: "XFRLEN1", description: "Transmit Frame length 1", size: "7", shift: "8", mask: "0x7F00" },
		]
	},
	{ name: "SRGR2", description: "Sample rate generator register 2", offset: "0xA",
		bits: [
			{ name: "FPER", description: "Frame-sync period", size: "12", shift: "0", mask: "0xFFF" },
			{ name: "FSGM", description: "Frame sync generator mode", size: "1", shift: "12", mask: "0x1000" },
			{ name: "CLKSM", description: "Sample rate generator mode", size: "1", shift: "13", mask: "0x2000" },
			{ name: "GSYNC", description: "CLKG sync", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SRGR1", description: "Sample rate generator register 1", offset: "0xB",
		bits: [
			{ name: "CLKGDV", description: "CLKG divider", size: "8", shift: "0", mask: "0xFF" },
			{ name: "FWID", description: "Frame width", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "MCR2", description: "Multi-channel control register 2", offset: "0xC",
		bits: [
			{ name: "XMCM", description: "Transmit data delay", size: "2", shift: "0", mask: "0x3" },
			{ name: "XCBLK", description: "Transmit frame sync ignore", size: "3", shift: "2", mask: "0x1C" },
			{ name: "XPABLK", description: "Transmit Companding Mode selects", size: "2", shift: "5", mask: "0x60" },
			{ name: "XPBBLK", description: "Transmit word length 2", size: "2", shift: "7", mask: "0x180" },
			{ name: "XMCME", description: "Transmit Frame length 2", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "MCR1", description: "Multi-channel control register 1", offset: "0xD",
		bits: [
			{ name: "RMCM", description: "Receive multichannel mode", size: "1", shift: "0", mask: "0x1" },
			{ name: "RCBLK", description: "eceive current block", size: "3", shift: "2", mask: "0x1C" },
			{ name: "RPABLK", description: "Receive partition A Block", size: "2", shift: "5", mask: "0x60" },
			{ name: "RPBBLK", description: "Receive partition B Block", size: "2", shift: "7", mask: "0x180" },
			{ name: "RMCME", description: "Receive multi-channel enhance mode", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "RCERA", description: "Receive channel enable partition A", offset: "0xE",
		bits: [
		]
	},
	{ name: "RCERB", description: "Receive channel enable partition B", offset: "0xF",
		bits: [
		]
	},
	{ name: "XCERA", description: "Transmit channel enable partition A", offset: "0x10",
		bits: [
		]
	},
	{ name: "XCERB", description: "Transmit channel enable partition B", offset: "0x11",
		bits: [
		]
	},
	{ name: "PCR", description: "Pin Control register", offset: "0x12",
		bits: [
			{ name: "CLKRP", description: "Receive Clock polarity", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLKXP", description: "Transmit clock polarity", size: "1", shift: "1", mask: "0x2" },
			{ name: "FSRP", description: "Receive Frame synchronization polarity", size: "1", shift: "2", mask: "0x4" },
			{ name: "FSXP", description: "Transmit Frame synchronization polarity", size: "1", shift: "3", mask: "0x8" },
			{ name: "SCLKME", description: "Sample clock mode selection", size: "1", shift: "7", mask: "0x80" },
			{ name: "CLKRM", description: "Receiver Clock Mode", size: "1", shift: "8", mask: "0x100" },
			{ name: "CLKXM", description: "Transmit Clock Mode.", size: "1", shift: "9", mask: "0x200" },
			{ name: "FSRM", description: "Receive Frame Synchronization Mode", size: "1", shift: "10", mask: "0x400" },
			{ name: "FSXM", description: "Transmit Frame Synchronization Mode", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "RCERC", description: "Receive channel enable partition C", offset: "0x13",
		bits: [
		]
	},
	{ name: "RCERD", description: "Receive channel enable partition D", offset: "0x14",
		bits: [
		]
	},
	{ name: "XCERC", description: "Transmit channel enable partition C", offset: "0x15",
		bits: [
		]
	},
	{ name: "XCERD", description: "Transmit channel enable partition D", offset: "0x16",
		bits: [
		]
	},
	{ name: "RCERE", description: "Receive channel enable partition E", offset: "0x17",
		bits: [
		]
	},
	{ name: "RCERF", description: "Receive channel enable partition F", offset: "0x18",
		bits: [
		]
	},
	{ name: "XCERE", description: "Transmit channel enable partition E", offset: "0x19",
		bits: [
		]
	},
	{ name: "XCERF", description: "Transmit channel enable partition F", offset: "0x1A",
		bits: [
		]
	},
	{ name: "RCERG", description: "Receive channel enable partition G", offset: "0x1B",
		bits: [
		]
	},
	{ name: "RCERH", description: "Receive channel enable partition H", offset: "0x1C",
		bits: [
		]
	},
	{ name: "XCERG", description: "Transmit channel enable partition G", offset: "0x1D",
		bits: [
		]
	},
	{ name: "XCERH", description: "Transmit channel enable partition H", offset: "0x1E",
		bits: [
		]
	},
	{ name: "MFFINT", description: "Interrupt enable", offset: "0x23",
		bits: [
			{ name: "XINT", description: "Enable for Receive Interrupt", size: "1", shift: "0", mask: "0x1" },
			{ name: "RINT", description: "Enable for transmit Interrupt", size: "1", shift: "2", mask: "0x4" },
		]
	},
];
module.exports = {
	MCBSPRegisters: MCBSPRegisters,
}
