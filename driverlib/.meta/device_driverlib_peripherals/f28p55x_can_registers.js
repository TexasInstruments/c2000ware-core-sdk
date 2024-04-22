let CANRegisters = [
	{ name: "CTL", description: "CAN Control Register", offset: "0x0",
		bits: [
			{ name: "INIT", description: "Initialization", size: "1", shift: "0", mask: "0x1" },
			{ name: "IE0", description: "Interrupt line 0 Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "SIE", description: "Status Change Interrupt Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "EIE", description: "Error Interrupt Enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "DAR", description: "Disable Automatic Retransmission", size: "1", shift: "5", mask: "0x20" },
			{ name: "CCE", description: "Configuration Change Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "TEST", description: "Test Mode Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "IDS", description: "Interruption Debug Support Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "ABO", description: "Auto-Bus-On Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "PMD", description: "Parity on/off", size: "4", shift: "10", mask: "0x3C00" },
			{ name: "SWR", description: "SW Reset Enable", size: "1", shift: "15", mask: "0x8000" },
			{ name: "INITDBG", description: "Debug Mode Status", size: "1", shift: "16", mask: "0x10000" },
			{ name: "IE1", description: "Interrupt line 1 Enable Disabled", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DE1", description: "Enable DMA request line", size: "1", shift: "18", mask: "0x40000" },
			{ name: "DE2", description: "Enable DMA request line", size: "1", shift: "19", mask: "0x80000" },
			{ name: "DE3", description: "Enable DMA request line", size: "1", shift: "20", mask: "0x100000" },
		]
	},
	{ name: "ES", description: "Error and Status Register", offset: "0x4",
		bits: [
			{ name: "LEC", description: "Last Error Code", size: "3", shift: "0", mask: "0x7" },
			{ name: "TXOK", description: "Transmission status", size: "1", shift: "3", mask: "0x8" },
			{ name: "RXOK", description: "Reception status", size: "1", shift: "4", mask: "0x10" },
			{ name: "EPASS", description: "Error Passive State", size: "1", shift: "5", mask: "0x20" },
			{ name: "EWARN", description: "Warning State", size: "1", shift: "6", mask: "0x40" },
			{ name: "BOFF", description: "Bus-Off State", size: "1", shift: "7", mask: "0x80" },
			{ name: "PER", description: "Parity Error Detected", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "ERRC", description: "Error Counter Register", offset: "0x8",
		bits: [
			{ name: "TEC", description: "Transmit Error Counter", size: "8", shift: "0", mask: "0xFF" },
			{ name: "REC", description: "Receive Error Counter", size: "7", shift: "8", mask: "0x7F00" },
			{ name: "RP", description: "Receive Error Passive", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "BTR", description: "Bit Timing Register", offset: "0xC",
		bits: [
			{ name: "BRP", description: "Baud Rate Prescaler", size: "6", shift: "0", mask: "0x3F" },
			{ name: "SJW", description: "Synchronization Jump Width", size: "2", shift: "6", mask: "0xC0" },
			{ name: "TSEG1", description: "Time segment", size: "4", shift: "8", mask: "0xF00" },
			{ name: "TSEG2", description: "Time segment", size: "3", shift: "12", mask: "0x7000" },
			{ name: "BRPE", description: "Baud Rate Prescaler Extension", size: "4", shift: "16", mask: "0xF0000" },
		]
	},
	{ name: "INT", description: "Interrupt Register", offset: "0x10",
		bits: [
			{ name: "INT0ID", description: "Interrupt Identifier", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "INT1ID", description: "Interrupt 1 Identifier", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "TEST", description: "Test Register", offset: "0x14",
		bits: [
			{ name: "SILENT", description: "Silent Mode", size: "1", shift: "3", mask: "0x8" },
			{ name: "LBACK", description: "Loopback Mode", size: "1", shift: "4", mask: "0x10" },
			{ name: "TX", description: "CANTX Pin Control", size: "2", shift: "5", mask: "0x60" },
			{ name: "RX", description: "CANRX Pin Status", size: "1", shift: "7", mask: "0x80" },
			{ name: "EXL", description: "External Loopback Mode", size: "1", shift: "8", mask: "0x100" },
			{ name: "RDA", description: "RAM Direct Access Enable:", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "PERR", description: "CAN Parity Error Code Register", offset: "0x1C",
		bits: [
			{ name: "MSG_NUM", description: "Message Number", size: "8", shift: "0", mask: "0xFF" },
			{ name: "WORD_NUM", description: "Word Number", size: "3", shift: "8", mask: "0x700" },
		]
	},
	{ name: "RAM_INIT", description: "CAN RAM Initialization Register", offset: "0x40",
		bits: [
			{ name: "KEY0", description: "KEY0", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY1", description: "KEY1", size: "1", shift: "1", mask: "0x2" },
			{ name: "KEY2", description: "KEY2", size: "1", shift: "2", mask: "0x4" },
			{ name: "KEY3", description: "KEY3", size: "1", shift: "3", mask: "0x8" },
			{ name: "CAN_RAM_INIT", description: "Initialize CAN Mailbox RAM", size: "1", shift: "4", mask: "0x10" },
			{ name: "RAM_INIT_DONE", description: "CAN RAM initialization complete", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "GLB_INT_EN", description: "CAN Global Interrupt Enable Register", offset: "0x50",
		bits: [
			{ name: "GLBINT0_EN", description: "Global Interrupt Enable for  CANINT0", size: "1", shift: "0", mask: "0x1" },
			{ name: "GLBINT1_EN", description: "Global Interrupt Enable for  CANINT1", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "GLB_INT_FLG", description: "CAN Global Interrupt Flag Register", offset: "0x54",
		bits: [
			{ name: "INT0_FLG", description: "Global Interrupt Flag for CANINT0", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT1_FLG", description: "Global Interrupt Flag for CANINT1", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "GLB_INT_CLR", description: "CAN Global Interrupt Clear Register", offset: "0x58",
		bits: [
			{ name: "INT0_FLG_CLR", description: "Global Interrupt flag clear for CANINT0", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT1_FLG_CLR", description: "Global Interrupt flag clear for CANINT1", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "ABOTR", description: "Auto-Bus-On Time Register", offset: "0x80",
		bits: [
		]
	},
	{ name: "TXRQ_X", description: "CAN Transmission Request Register", offset: "0x84",
		bits: [
			{ name: "TXRQSTREG1", description: "Transmit Request Register 1", size: "2", shift: "0", mask: "0x3" },
			{ name: "TXRQSTREG2", description: "Transmit Request Register 2", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "TXRQ_21", description: "CAN Transmission Request 2_1 Register", offset: "0x88",
		bits: [
		]
	},
	{ name: "NDAT_X", description: "CAN New Data Register", offset: "0x98",
		bits: [
			{ name: "NEWDATREG1", description: "New Data Register 1", size: "2", shift: "0", mask: "0x3" },
			{ name: "NEWDATREG2", description: "New Data Register 2", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "NDAT_21", description: "CAN New Data 2_1 Register", offset: "0x9C",
		bits: [
		]
	},
	{ name: "IPEN_X", description: "CAN Interrupt Pending Register", offset: "0xAC",
		bits: [
			{ name: "INTPNDREG1", description: "Interrupt Pending Register 1", size: "2", shift: "0", mask: "0x3" },
			{ name: "INTPNDREG2", description: "Interrupt Pending Register 2", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "IPEN_21", description: "CAN Interrupt Pending 2_1 Register", offset: "0xB0",
		bits: [
		]
	},
	{ name: "MVAL_X", description: "CAN Message Valid Register", offset: "0xC0",
		bits: [
			{ name: "MSGVALREG1", description: "Message Valid Register 1", size: "2", shift: "0", mask: "0x3" },
			{ name: "MSGVALREG2", description: "Message Valid Register 2", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "MVAL_21", description: "CAN Message Valid 2_1 Register", offset: "0xC4",
		bits: [
		]
	},
	{ name: "IP_MUX21", description: "CAN Interrupt Multiplexer 2_1 Register", offset: "0xD8",
		bits: [
		]
	},
	{ name: "IF1CMD", description: "IF1 Command Register", offset: "0x100",
		bits: [
			{ name: "MSG_NUM", description: "Message Number", size: "8", shift: "0", mask: "0xFF" },
			{ name: "DMAACTIVE", description: "DMA Status", size: "1", shift: "14", mask: "0x4000" },
			{ name: "BUSY", description: "Busy Flag", size: "1", shift: "15", mask: "0x8000" },
			{ name: "DATA_B", description: "Access Data Bytes 4-7", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DATA_A", description: "Access Data Bytes 0-3", size: "1", shift: "17", mask: "0x20000" },
			{ name: "TXRQST", description: "Access Transmission Request Bit", size: "1", shift: "18", mask: "0x40000" },
			{ name: "CLRINTPND", description: "Clear Interrupt Pending Bit", size: "1", shift: "19", mask: "0x80000" },
			{ name: "CONTROL", description: "Access Control Bits", size: "1", shift: "20", mask: "0x100000" },
			{ name: "ARB", description: "Access Arbitration Bits", size: "1", shift: "21", mask: "0x200000" },
			{ name: "MASK", description: "Access Mask Bits", size: "1", shift: "22", mask: "0x400000" },
			{ name: "DIR", description: "Write/Read Direction", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "IF1MSK", description: "IF1 Mask Register", offset: "0x104",
		bits: [
			{ name: "MSK", description: "Identifier Mask", size: "29", shift: "0", mask: "0x1FFFFFFF" },
			{ name: "MDIR", description: "Mask Message Direction", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "MXTD", description: "Mask Extended Identifier", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "IF1ARB", description: "IF1 Arbitration Register", offset: "0x108",
		bits: [
			{ name: "ID", description: "`", size: "29", shift: "0", mask: "0x1FFFFFFF" },
			{ name: "DIR", description: "Message Direction", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "XTD", description: "Extended Identifier", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "MSGVAL", description: "Message Valid", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "IF1MCTL", description: "IF1 Message Control Register", offset: "0x10C",
		bits: [
			{ name: "DLC", description: "Data length code", size: "4", shift: "0", mask: "0xF" },
			{ name: "EOB", description: "End of Block", size: "1", shift: "7", mask: "0x80" },
			{ name: "TXRQST", description: "Transmit Request", size: "1", shift: "8", mask: "0x100" },
			{ name: "RMTEN", description: "Remote Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "RXIE", description: "Receive Interrupt Enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "TXIE", description: "Transmit Interrupt Enable", size: "1", shift: "11", mask: "0x800" },
			{ name: "UMASK", description: "Use Acceptance Mask", size: "1", shift: "12", mask: "0x1000" },
			{ name: "INTPND", description: "Interrupt Pending", size: "1", shift: "13", mask: "0x2000" },
			{ name: "MSGLST", description: "Message Lost", size: "1", shift: "14", mask: "0x4000" },
			{ name: "NEWDAT", description: "New Data", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "IF1DATA", description: "IF1 Data A Register", offset: "0x110",
		bits: [
			{ name: "DATA_0", description: "Data Byte 0", size: "8", shift: "0", mask: "0xFF" },
			{ name: "DATA_1", description: "Data Byte 1", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "DATA_2", description: "Data Byte 2", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "DATA_3", description: "Data Byte 3", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "IF1DATB", description: "IF1 Data B Register", offset: "0x114",
		bits: [
			{ name: "DATA_4", description: "Data Byte 4", size: "8", shift: "0", mask: "0xFF" },
			{ name: "DATA_5", description: "Data Byte 5", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "DATA_6", description: "Data Byte 6", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "DATA_7", description: "Data Byte 7", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "IF2CMD", description: "IF2 Command Register", offset: "0x120",
		bits: [
			{ name: "MSG_NUM", description: "Message Number", size: "8", shift: "0", mask: "0xFF" },
			{ name: "DMAACTIVE", description: "DMA Status", size: "1", shift: "14", mask: "0x4000" },
			{ name: "BUSY", description: "Busy Flag", size: "1", shift: "15", mask: "0x8000" },
			{ name: "DATA_B", description: "Access Data Bytes 4-7", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DATA_A", description: "Access Data Bytes 0-3", size: "1", shift: "17", mask: "0x20000" },
			{ name: "TXRQST", description: "Access Transmission Request Bit", size: "1", shift: "18", mask: "0x40000" },
			{ name: "CLRINTPND", description: "Clear Interrupt Pending Bit", size: "1", shift: "19", mask: "0x80000" },
			{ name: "CONTROL", description: "Access Control Bits", size: "1", shift: "20", mask: "0x100000" },
			{ name: "ARB", description: "Access Arbitration Bits", size: "1", shift: "21", mask: "0x200000" },
			{ name: "MASK", description: "Access Mask Bits", size: "1", shift: "22", mask: "0x400000" },
			{ name: "DIR", description: "Write/Read Direction", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "IF2MSK", description: "IF2 Mask Register", offset: "0x124",
		bits: [
			{ name: "MSK", description: "Identifier Mask", size: "29", shift: "0", mask: "0x1FFFFFFF" },
			{ name: "MDIR", description: "Mask Message Direction", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "MXTD", description: "Mask Extended Identifier", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "IF2ARB", description: "IF2 Arbitration Register", offset: "0x128",
		bits: [
			{ name: "ID", description: "Message  Identifier", size: "29", shift: "0", mask: "0x1FFFFFFF" },
			{ name: "DIR", description: "Message Direction", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "XTD", description: "Extended Identifier", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "MSGVAL", description: "Message Valid", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "IF2MCTL", description: "IF2 Message Control Register", offset: "0x12C",
		bits: [
			{ name: "DLC", description: "Data length code", size: "4", shift: "0", mask: "0xF" },
			{ name: "EOB", description: "End of Block", size: "1", shift: "7", mask: "0x80" },
			{ name: "TXRQST", description: "Transmit Request", size: "1", shift: "8", mask: "0x100" },
			{ name: "RMTEN", description: "Remote Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "RXIE", description: "Receive Interrupt Enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "TXIE", description: "Transmit Interrupt Enable", size: "1", shift: "11", mask: "0x800" },
			{ name: "UMASK", description: "Use Acceptance Mask", size: "1", shift: "12", mask: "0x1000" },
			{ name: "INTPND", description: "Interrupt Pending", size: "1", shift: "13", mask: "0x2000" },
			{ name: "MSGLST", description: "Message Lost", size: "1", shift: "14", mask: "0x4000" },
			{ name: "NEWDAT", description: "New Data", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "IF2DATA", description: "IF2 Data A Register", offset: "0x130",
		bits: [
			{ name: "DATA_0", description: "Data Byte 0", size: "8", shift: "0", mask: "0xFF" },
			{ name: "DATA_1", description: "Data Byte 1", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "DATA_2", description: "Data Byte 2", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "DATA_3", description: "Data Byte 3", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "IF2DATB", description: "IF2 Data B Register", offset: "0x134",
		bits: [
			{ name: "DATA_4", description: "Data Byte 4", size: "8", shift: "0", mask: "0xFF" },
			{ name: "DATA_5", description: "Data Byte 5", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "DATA_6", description: "Data Byte 6", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "DATA_7", description: "Data Byte 7", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "IF3OBS", description: "IF3 Observation Register", offset: "0x140",
		bits: [
			{ name: "MASK", description: "Mask data read observation", size: "1", shift: "0", mask: "0x1" },
			{ name: "ARB", description: "Arbitration data read observation", size: "1", shift: "1", mask: "0x2" },
			{ name: "CTRL", description: "Ctrl read observation", size: "1", shift: "2", mask: "0x4" },
			{ name: "DATA_A", description: "Data A read observation", size: "1", shift: "3", mask: "0x8" },
			{ name: "DATA_B", description: "Data B read observation", size: "1", shift: "4", mask: "0x10" },
			{ name: "IF3SM", description: "IF3 Status of Mask data read access", size: "1", shift: "8", mask: "0x100" },
			{ name: "IF3SA", description: "IF3 Status of Arbitration data read access", size: "1", shift: "9", mask: "0x200" },
			{ name: "IF3SC", description: "IF3 Status of Control bits read access", size: "1", shift: "10", mask: "0x400" },
			{ name: "IF3SDA", description: "IF3 Status of Data A read access", size: "1", shift: "11", mask: "0x800" },
			{ name: "IF3SDB", description: "IF3 Status of Data B read access", size: "1", shift: "12", mask: "0x1000" },
			{ name: "IF3UPD", description: "IF3 Update Data", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "IF3MSK", description: "IF3 Mask Register", offset: "0x144",
		bits: [
			{ name: "MSK", description: "Mask", size: "29", shift: "0", mask: "0x1FFFFFFF" },
			{ name: "MDIR", description: "Mask Message Direction", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "MXTD", description: "Mask Extended Identifier", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "IF3ARB", description: "IF3 Arbitration Register", offset: "0x148",
		bits: [
			{ name: "ID", description: "Message  Identifier", size: "29", shift: "0", mask: "0x1FFFFFFF" },
			{ name: "DIR", description: "Message Direction", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "XTD", description: "Extended Identifier", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "MSGVAL", description: "Message Valid", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "IF3MCTL", description: "IF3 Message Control Register", offset: "0x14C",
		bits: [
			{ name: "DLC", description: "Data length code", size: "4", shift: "0", mask: "0xF" },
			{ name: "EOB", description: "End of Block", size: "1", shift: "7", mask: "0x80" },
			{ name: "TXRQST", description: "Transmit Request", size: "1", shift: "8", mask: "0x100" },
			{ name: "RMTEN", description: "Remote Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "RXIE", description: "Receive Interrupt Enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "TXIE", description: "Transmit Interrupt Enable", size: "1", shift: "11", mask: "0x800" },
			{ name: "UMASK", description: "Use Acceptance Mask", size: "1", shift: "12", mask: "0x1000" },
			{ name: "INTPND", description: "Interrupt Pending", size: "1", shift: "13", mask: "0x2000" },
			{ name: "MSGLST", description: "Message Lost", size: "1", shift: "14", mask: "0x4000" },
			{ name: "NEWDAT", description: "New Data", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "IF3DATA", description: "IF3 Data A Register", offset: "0x150",
		bits: [
			{ name: "DATA_0", description: "Data Byte 0", size: "8", shift: "0", mask: "0xFF" },
			{ name: "DATA_1", description: "Data Byte 1", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "DATA_2", description: "Data Byte 2", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "DATA_3", description: "Data Byte 3", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "IF3DATB", description: "IF3 Data B Register", offset: "0x154",
		bits: [
			{ name: "DATA_4", description: "Data Byte 4", size: "8", shift: "0", mask: "0xFF" },
			{ name: "DATA_5", description: "Data Byte 5", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "DATA_6", description: "Data Byte 6", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "DATA_7", description: "Data Byte 7", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "IF3UPD", description: "IF3 Update Enable Register", offset: "0x160",
		bits: [
		]
	},
];
module.exports = {
	CANRegisters: CANRegisters,
}
