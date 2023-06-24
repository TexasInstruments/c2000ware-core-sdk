let EQEPRegisters = [
	{ name: "QPOSCNT", description: "Position Counter", offset: "0x0",
		bits: [
		]
	},
	{ name: "QPOSINIT", description: "Position Counter Init", offset: "0x2",
		bits: [
		]
	},
	{ name: "QPOSMAX", description: "Maximum Position Count", offset: "0x4",
		bits: [
		]
	},
	{ name: "QPOSCMP", description: "Position Compare", offset: "0x6",
		bits: [
		]
	},
	{ name: "QPOSILAT", description: "Index Position Latch", offset: "0x8",
		bits: [
		]
	},
	{ name: "QPOSSLAT", description: "Strobe Position Latch", offset: "0xA",
		bits: [
		]
	},
	{ name: "QPOSLAT", description: "Position Latch", offset: "0xC",
		bits: [
		]
	},
	{ name: "QUTMR", description: "QEP Unit Timer", offset: "0xE",
		bits: [
		]
	},
	{ name: "QUPRD", description: "QEP Unit Period", offset: "0x10",
		bits: [
		]
	},
	{ name: "QWDTMR", description: "QEP Watchdog Timer", offset: "0x12",
		bits: [
		]
	},
	{ name: "QWDPRD", description: "QEP Watchdog Period", offset: "0x13",
		bits: [
		]
	},
	{ name: "QDECCTL", description: "Quadrature Decoder Control", offset: "0x14",
		bits: [
			{ name: "QSP", description: "QEPS input polarity", size: "1", shift: "5", mask: "0x20" },
			{ name: "QIP", description: "QEPI input polarity", size: "1", shift: "6", mask: "0x40" },
			{ name: "QBP", description: "QEPB input polarity", size: "1", shift: "7", mask: "0x80" },
			{ name: "QAP", description: "QEPA input polarity", size: "1", shift: "8", mask: "0x100" },
			{ name: "IGATE", description: "Index pulse gating option", size: "1", shift: "9", mask: "0x200" },
			{ name: "SWAP", description: "CLK/DIR Signal Source for Position Counter", size: "1", shift: "10", mask: "0x400" },
			{ name: "XCR", description: "External Clock Rate", size: "1", shift: "11", mask: "0x800" },
			{ name: "SPSEL", description: "Sync output pin selection", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SOEN", description: "Sync output-enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "QSRC", description: "Position-counter source selection", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "QEPCTL", description: "QEP Control", offset: "0x15",
		bits: [
			{ name: "WDE", description: "QEP watchdog enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "UTE", description: "QEP unit timer enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "QCLM", description: "QEP capture latch mode", size: "1", shift: "2", mask: "0x4" },
			{ name: "QPEN", description: "Quadrature postotion counter enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "IEL", description: "Index event latch", size: "2", shift: "4", mask: "0x30" },
			{ name: "SEL", description: "Strobe event latch", size: "1", shift: "6", mask: "0x40" },
			{ name: "SWI", description: "Software init position counter", size: "1", shift: "7", mask: "0x80" },
			{ name: "IEI", description: "Index event init of position count", size: "2", shift: "8", mask: "0x300" },
			{ name: "SEI", description: "Strobe event init", size: "2", shift: "10", mask: "0xC00" },
			{ name: "PCRM", description: "Postion counter reset", size: "2", shift: "12", mask: "0x3000" },
			{ name: "FREE_SOFT", description: "Emulation mode", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "QCAPCTL", description: "Qaudrature Capture Control", offset: "0x16",
		bits: [
			{ name: "UPPS", description: "Unit position event prescaler", size: "4", shift: "0", mask: "0xF" },
			{ name: "CCPS", description: "eQEP capture timer clock prescaler", size: "3", shift: "4", mask: "0x70" },
			{ name: "CEN", description: "Enable eQEP capture", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "QPOSCTL", description: "Position Compare Control", offset: "0x17",
		bits: [
			{ name: "PCSPW", description: "Position compare sync pulse width", size: "12", shift: "0", mask: "0xFFF" },
			{ name: "PCE", description: "Position compare enable/disable", size: "1", shift: "12", mask: "0x1000" },
			{ name: "PCPOL", description: "Polarity of sync output", size: "1", shift: "13", mask: "0x2000" },
			{ name: "PCLOAD", description: "Position compare of shadow load", size: "1", shift: "14", mask: "0x4000" },
			{ name: "PCSHDW", description: "Position compare of shadow enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "QEINT", description: "QEP Interrupt Control", offset: "0x18",
		bits: [
			{ name: "PCE", description: "Position counter error interrupt enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "QPE", description: "Quadrature phase error interrupt enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "QDC", description: "Quadrature direction change interrupt enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "WTO", description: "Watchdog time out interrupt enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "PCU", description: "Position counter underflow interrupt enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "PCO", description: "Position counter overflow interrupt enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "PCR", description: "Position-compare ready interrupt enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "PCM", description: "Position-compare match interrupt enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "SEL", description: "Strobe event latch interrupt enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "IEL", description: "Index event latch interrupt enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "UTO", description: "Unit time out interrupt enable", size: "1", shift: "11", mask: "0x800" },
			{ name: "QMAE", description: "QMA error interrupt enable", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "QFLG", description: "QEP Interrupt Flag", offset: "0x19",
		bits: [
			{ name: "INT", description: "Global interrupt status flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "PCE", description: "Position counter error interrupt flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "PHE", description: "Quadrature phase error interrupt flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "QDC", description: "Quadrature direction change interrupt flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "WTO", description: "Watchdog timeout interrupt flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "PCU", description: "Position counter underflow interrupt flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "PCO", description: "Position counter overflow interrupt flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "PCR", description: "Position-compare ready interrupt flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "PCM", description: "eQEP compare match event interrupt flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "SEL", description: "Strobe event latch interrupt flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "IEL", description: "Index event latch interrupt flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "UTO", description: "Unit time out interrupt flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "QMAE", description: "QMA error interrupt flag", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "QCLR", description: "QEP Interrupt Clear", offset: "0x1A",
		bits: [
			{ name: "INT", description: "Global interrupt clear flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "PCE", description: "Clear position counter error interrupt flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "PHE", description: "Clear quadrature phase error interrupt flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "QDC", description: "Clear quadrature direction change interrupt flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "WTO", description: "Clear watchdog timeout interrupt flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "PCU", description: "Clear position counter underflow interrupt flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "PCO", description: "Clear position counter overflow interrupt flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "PCR", description: "Clear position-compare ready interrupt flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "PCM", description: "Clear eQEP compare match event interrupt flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "SEL", description: "Clear strobe event latch interrupt flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "IEL", description: "Clear index event latch interrupt flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "UTO", description: "Clear unit time out interrupt flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "QMAE", description: "Clear QMA error interrupt flag", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "QFRC", description: "QEP Interrupt Force", offset: "0x1B",
		bits: [
			{ name: "PCE", description: "Force position counter error interrupt", size: "1", shift: "1", mask: "0x2" },
			{ name: "PHE", description: "Force quadrature phase error interrupt", size: "1", shift: "2", mask: "0x4" },
			{ name: "QDC", description: "Force quadrature direction change interrupt", size: "1", shift: "3", mask: "0x8" },
			{ name: "WTO", description: "Force watchdog time out interrupt", size: "1", shift: "4", mask: "0x10" },
			{ name: "PCU", description: "Force position counter underflow interrupt", size: "1", shift: "5", mask: "0x20" },
			{ name: "PCO", description: "Force position counter overflow interrupt", size: "1", shift: "6", mask: "0x40" },
			{ name: "PCR", description: "Force position-compare ready interrupt", size: "1", shift: "7", mask: "0x80" },
			{ name: "PCM", description: "Force position-compare match interrupt", size: "1", shift: "8", mask: "0x100" },
			{ name: "SEL", description: "Force strobe event latch interrupt", size: "1", shift: "9", mask: "0x200" },
			{ name: "IEL", description: "Force index event latch interrupt", size: "1", shift: "10", mask: "0x400" },
			{ name: "UTO", description: "Force unit time out interrupt", size: "1", shift: "11", mask: "0x800" },
			{ name: "QMAE", description: "Force QMA error interrupt", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "QEPSTS", description: "QEP Status", offset: "0x1C",
		bits: [
			{ name: "PCEF", description: "Position counter error flag.", size: "1", shift: "0", mask: "0x1" },
			{ name: "FIMF", description: "First index marker flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "CDEF", description: "Capture direction error flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "COEF", description: "Capture overflow error flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "QDLF", description: "eQEP direction latch flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "QDF", description: "Quadrature direction flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "FIDF", description: "The first index marker", size: "1", shift: "6", mask: "0x40" },
			{ name: "UPEVNT", description: "Unit position event flag", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "QCTMR", description: "QEP Capture Timer", offset: "0x1D",
		bits: [
		]
	},
	{ name: "QCPRD", description: "QEP Capture Period", offset: "0x1E",
		bits: [
		]
	},
	{ name: "QCTMRLAT", description: "QEP Capture Latch", offset: "0x1F",
		bits: [
		]
	},
	{ name: "QCPRDLAT", description: "QEP Capture Period Latch", offset: "0x20",
		bits: [
		]
	},
	{ name: "REV", description: "QEP Revision Number", offset: "0x30",
		bits: [
			{ name: "MAJOR", description: "Major Revision Number", size: "3", shift: "0", mask: "0x7" },
			{ name: "MINOR", description: "Minor Revision Number", size: "3", shift: "3", mask: "0x38" },
		]
	},
	{ name: "QEPSTROBESEL", description: "QEP Strobe select register", offset: "0x32",
		bits: [
			{ name: "STROBESEL", description: "QMA Mode Select", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "QMACTRL", description: "QMA Control register", offset: "0x34",
		bits: [
			{ name: "MODE", description: "QMA Mode Select", size: "3", shift: "0", mask: "0x7" },
		]
	},
];
module.exports = {
	EQEPRegisters: EQEPRegisters,
}
