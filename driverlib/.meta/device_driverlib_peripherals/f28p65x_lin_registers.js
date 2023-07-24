let LINRegisters = [
	{ name: "SCIGCR0", description: "Global Control Register 0", offset: "0x0",
		bits: [
			{ name: "RESET", description: "LIN Module reset bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SCIGCR1", description: "Global Control Register 1", offset: "0x4",
		bits: [
			{ name: "COMMMODE", description: "SCI/LIN communications mode bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "TIMINGMODE", description: "SCI timing mode bit. Should be set to 1 for SCI", size: "1", shift: "1", mask: "0x2" },
			{ name: "PARITYENA", description: "Parity enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "PARITY", description: "SCI parity odd/even selection", size: "1", shift: "3", mask: "0x8" },
			{ name: "STOP", description: "SCI number of stop bits", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLK_COMMANDER", description: "LIN Commander/Responder selection and SCI clock", size: "1", shift: "5", mask: "0x20" },
			{ name: "LINMODE", description: "LIN Mode enable/disable", size: "1", shift: "6", mask: "0x40" },
			{ name: "SWNRST", description: "Software reset", size: "1", shift: "7", mask: "0x80" },
			{ name: "SLEEP", description: "SCI sleep (SCI compatibility mode)", size: "1", shift: "8", mask: "0x100" },
			{ name: "ADAPT", description: "Automatic baudrate adjustment control(LIN mode)", size: "1", shift: "9", mask: "0x200" },
			{ name: "MBUFMODE", description: "Multi-buffer mode", size: "1", shift: "10", mask: "0x400" },
			{ name: "CTYPE", description: "Checksum type (LIN mode)", size: "1", shift: "11", mask: "0x800" },
			{ name: "HGENCTRL", description: "Mask filtering comparison control (LIN mode)", size: "1", shift: "12", mask: "0x1000" },
			{ name: "STOPEXTFRAME", description: "Stop extended frame communication (LIN mode)", size: "1", shift: "13", mask: "0x2000" },
			{ name: "LOOPBACK", description: "Digital loopback mode", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CONT", description: "Continue on suspend", size: "1", shift: "17", mask: "0x20000" },
			{ name: "RXENA", description: "Receive enable", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "TXENA", description: "Transmit enable", size: "1", shift: "25", mask: "0x2000000" },
		]
	},
	{ name: "SCIGCR2", description: "Global Control Register 2", offset: "0x8",
		bits: [
			{ name: "POWERDOWN", description: "Low-power mode PowerDown bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "GENWU", description: "Generate Wakeup", size: "1", shift: "8", mask: "0x100" },
			{ name: "SC", description: "Send Checksum (LIN mode)", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CC", description: "Compare Checksum (LIN mode)", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "SCISETINT", description: "Interrupt Enable Register", offset: "0xC",
		bits: [
			{ name: "SETBRKDTINT", description: "Set Break-detect Interrupt (SCI compatible", size: "1", shift: "0", mask: "0x1" },
			{ name: "SETWAKEUPINT", description: "Set Wake-up Interrupt", size: "1", shift: "1", mask: "0x2" },
			{ name: "SETTIMEOUTINT", description: "Set Timeout Interrupt (LIN only)", size: "1", shift: "4", mask: "0x10" },
			{ name: "SETTOAWUSINT", description: "Set Timeout After Wakeup Signal Interrupt", size: "1", shift: "6", mask: "0x40" },
			{ name: "SETTOA3WUSINT", description: "Set Timeout After 3 Wakeup Signals", size: "1", shift: "7", mask: "0x80" },
			{ name: "SETTXINT", description: "Set Transmitter Interrupt", size: "1", shift: "8", mask: "0x100" },
			{ name: "SETRXINT", description: "Se Receiver Interrupt", size: "1", shift: "9", mask: "0x200" },
			{ name: "SETIDINT", description: "Set Identifier Interrupt (LIN only)", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SET_TX_DMA", description: "Set transmit DMA", size: "1", shift: "16", mask: "0x10000" },
			{ name: "SET_RX_DMA", description: "Set receiver DMA", size: "1", shift: "17", mask: "0x20000" },
			{ name: "SET_RX_DMA_ALL", description: "Set receiver DMA for Address & Data frames", size: "1", shift: "18", mask: "0x40000" },
			{ name: "SETPEINT", description: "Set Parity Interrupt", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "SETOEINT", description: "Set Overrun-Error Interrupt", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "SETFEINT", description: "Set Framing-Error Interrupt", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "SETNREINT", description: "Set No-Response-Error Interrupt (LIN only)", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "SETISFEINT", description: "Set Inconsistent-Sync-Field-Error Interrupt", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "SETCEINT", description: "Set Checksum-error Interrupt (LIN only)", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "SETPBEINT", description: "Set Physical Bus Error Interrupt (LIN only)", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "SETBEINT", description: "Set Bit Error Interrupt (LIN only)", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SCICLEARINT", description: "Interrupt Disable Register", offset: "0x10",
		bits: [
			{ name: "CLRBRKDTINT", description: "Clear Break-detect Interrupt (SCI", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLRWAKEUPINT", description: "Clear Wake-up Interrupt", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLRTIMEOUTINT", description: "Clear Timeout Interrupt (LIN only)", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLRTOAWUSINT", description: "Clear Timeout After Wakeup Signal", size: "1", shift: "6", mask: "0x40" },
			{ name: "CLRTOA3WUSINT", description: "Clear Timeout After 3 Wakeup Signals", size: "1", shift: "7", mask: "0x80" },
			{ name: "CLRTXINT", description: "Clear Transmitter Interrupt", size: "1", shift: "8", mask: "0x100" },
			{ name: "CLRRXINT", description: "Clear Receiver Interrupt", size: "1", shift: "9", mask: "0x200" },
			{ name: "CLRIDINT", description: "Clear Identifier Interrupt (LIN only)", size: "1", shift: "13", mask: "0x2000" },
			{ name: "CLRTXDMA", description: "Clear transmit DMA", size: "1", shift: "16", mask: "0x10000" },
			{ name: "SETRXDMA", description: "Clear receiver DMA", size: "1", shift: "17", mask: "0x20000" },
			{ name: "CLRPEINT", description: "Clear Parity Interrupt", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "CLROEINT", description: "Clear Overrun-Error Interrupt", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "CLRFEINT", description: "Clear Framing-Error Interrupt", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "CLRNREINT", description: "Clear No-Response-Error Interrupt (LIN", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "CLRISFEINT", description: "Clear Inconsistent-Sync-Field-Error", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "CLRCEINT", description: "Clear Checksum-error Interrupt (LIN only)", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "CLRPBEINT", description: "Clear Physical Bus Error Interrupt (LIN", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "CLRBEINT", description: "Clear Bit Error Interrupt (LIN only)", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SCISETINTLVL", description: "Set Interrupt Level Register", offset: "0x14",
		bits: [
			{ name: "SETBRKDTINTLVL", description: "Set Break-detect Interrupt Level (SCI", size: "1", shift: "0", mask: "0x1" },
			{ name: "SETWAKEUPINTLVL", description: "Set Wake-up Interrupt Level", size: "1", shift: "1", mask: "0x2" },
			{ name: "SETTIMEOUTINTLVL", description: "Set Timeout Interrupt Level (LIN only)", size: "1", shift: "4", mask: "0x10" },
			{ name: "SETTOAWUSINTLVL", description: "Set Timeout After Wakeup Signal", size: "1", shift: "6", mask: "0x40" },
			{ name: "SETTOA3WUSINTLVL", description: "Set Timeout After 3 Wakeup Signals", size: "1", shift: "7", mask: "0x80" },
			{ name: "SETTXINTLVL", description: "Set Transmitter Interrupt Level", size: "1", shift: "8", mask: "0x100" },
			{ name: "SETRXINTOVO", description: "Receiver Interrupt Enable Level", size: "1", shift: "9", mask: "0x200" },
			{ name: "SETIDINTLVL", description: "Set Identifier Interrupt Level (LIN", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SETPEINTLVL", description: "Set Parity Interrupt Level", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "SETOEINTLVL", description: "Set Overrun-Error Interrupt Level", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "SETFEINTLVL", description: "Set Framing-Error Interrupt Level", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "SETNREINTLVL", description: "Set No-Response-Error Interrupt Level", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "SETISFEINTLVL", description: "Set Inconsistent-Sync-Field-Error", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "SETCEINTLVL", description: "Set Checksum-error Interrupt Level", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "SETPBEINTLVL", description: "Set Physical Bus Error Interrupt Level", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "SETBEINTLVL", description: "Set Bit Error Interrupt Level (LIN", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SCICLEARINTLVL", description: "Clear Interrupt Level Register", offset: "0x18",
		bits: [
			{ name: "CLRBRKDTINTLVL", description: "Clear Break-detect Interrupt Level", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLRWAKEUPINTLVL", description: "Clear Wake-up Interrupt Level", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLRTIMEOUTINTLVL", description: "Clear Timeout Interrupt Level (LIN", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLRTOAWUSINTLVL", description: "Clear Timeout After Wakeup Signal", size: "1", shift: "6", mask: "0x40" },
			{ name: "CLRTOA3WUSINTLVL", description: "Clear Timeout After 3 Wakeup Signals", size: "1", shift: "7", mask: "0x80" },
			{ name: "CLRTXINTLVL", description: "Clear Transmitter Interrupt Level", size: "1", shift: "8", mask: "0x100" },
			{ name: "CLRRXINTLVL", description: "Clear Receiver interrupt Level.", size: "1", shift: "9", mask: "0x200" },
			{ name: "CLRIDINTLVL", description: "Clear Identifier Interrupt Level", size: "1", shift: "13", mask: "0x2000" },
			{ name: "CLRPEINTLVL", description: "Clear Parity Interrupt Level", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "CLROEINTLVL", description: "Clear Overrun-Error Interrupt Level", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "CLRFEINTLVL", description: "Clear Framing-Error Interrupt Level", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "CLRNREINTLVL", description: "Clear No-Response-Error Interrupt", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "CLRISFEINTLVL", description: "Clear Inconsistent-Sync-Field-Error", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "CLRCEINTLVL", description: "Clear Checksum-error Interrupt Level", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "CLRPBEINTLVL", description: "Clear Physical Bus Error Interrupt", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "CLRBEINTLVL", description: "Clear Bit Error Interrupt Level (LIN", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SCIFLR", description: "Flag Register", offset: "0x1C",
		bits: [
			{ name: "BRKDT", description: "Break-detect Flag (SCI compatible mode)", size: "1", shift: "0", mask: "0x1" },
			{ name: "WAKEUP", description: "Wake-up Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "IDLE", description: "SCI receiver in idle state (SCI compatible mode)", size: "1", shift: "2", mask: "0x4" },
			{ name: "BUSY", description: "Busy Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "TIMEOUT", description: "LIN Bus IDLE timeout Flag (LIN only)", size: "1", shift: "4", mask: "0x10" },
			{ name: "TOAWUS", description: "Timeout After Wakeup Signal Flag (LIN only)", size: "1", shift: "6", mask: "0x40" },
			{ name: "TOA3WUS", description: "Timeout After 3 Wakeup Signals Flag (LIN only)", size: "1", shift: "7", mask: "0x80" },
			{ name: "TXRDY", description: "Transmitter Buffer Ready Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "RXRDY", description: "Receiver Buffer Ready Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "TXWAKE", description: "SCI Transmitter Wakeup Method Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "TXEMPTY", description: "Transmitter Empty Flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "RXWAKE", description: "Receiver Wakeup Detect Flag", size: "1", shift: "12", mask: "0x1000" },
			{ name: "IDTXFLAG", description: "Identifier On Transmit Flag (LIN only)", size: "1", shift: "13", mask: "0x2000" },
			{ name: "IDRXFLAG", description: "Identifier on Receive Flag", size: "1", shift: "14", mask: "0x4000" },
			{ name: "PE", description: "Parity Error Flag", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "OE", description: "Overrun Error Flag", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "FE", description: "Framing Error Flag", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "NRE", description: "No-Response Error Flag (LIN only)", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "ISFE", description: "Inconsistent Sync Field Error Flag (LIN only)", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "CE", description: "Checksum Error Flag (LIN only)", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "PBE", description: "Physical Bus Error Flag (LIN only)", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "BE", description: "Bit Error Flag (LIN only)", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SCIINTVECT0", description: "Interrupt Vector Offset Register 0", offset: "0x20",
		bits: [
			{ name: "INTVECT0", description: "LIN Module reset bit", size: "5", shift: "0", mask: "0x1F" },
		]
	},
	{ name: "SCIINTVECT1", description: "Interrupt Vector Offset Register 1", offset: "0x24",
		bits: [
			{ name: "INTVECT1", description: "LIN Module reset bit", size: "5", shift: "0", mask: "0x1F" },
		]
	},
	{ name: "SCIFORMAT", description: "Length Control Register", offset: "0x28",
		bits: [
			{ name: "CHAR", description: "Character Length Control Bits", size: "3", shift: "0", mask: "0x7" },
			{ name: "LENGTH", description: "Frame Length Control Bits", size: "3", shift: "16", mask: "0x70000" },
		]
	},
	{ name: "BRSR", description: "Baud Rate Selection Register", offset: "0x2C",
		bits: [
			{ name: "SCI_LIN_PSL", description: "24-Bit Integer Prescaler Select (Low Bits)", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SCI_LIN_PSH", description: "24-Bit Integer Prescaler Select (High Bits)", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "M", description: "M 4-bit Fractional Divider selection", size: "4", shift: "24", mask: "0xF000000" },
			{ name: "U", description: "U Superfractional divider Selection", size: "3", shift: "28", mask: "0x70000000" },
		]
	},
	{ name: "SCIED", description: "Emulation buffer Register", offset: "0x30",
		bits: [
			{ name: "ED", description: "Receiver Emulation Data.", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "SCIRD", description: "Receiver data buffer Register", offset: "0x34",
		bits: [
			{ name: "RD", description: "Received Data.", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "SCITD", description: "Transmit data buffer Register", offset: "0x38",
		bits: [
			{ name: "TD", description: "Transmit data", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "SCIPIO0", description: "Pin control Register 0", offset: "0x3C",
		bits: [
			{ name: "RXFUNC", description: "LINRX pin function", size: "1", shift: "1", mask: "0x2" },
			{ name: "TXFUNC", description: "LINTX pin function", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "SCIPIO2", description: "Pin control Register 2", offset: "0x44",
		bits: [
			{ name: "RXIN", description: "SCIRX pin value", size: "1", shift: "1", mask: "0x2" },
			{ name: "TXIN", description: "SCITX pin value", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "COMP", description: "Compare register", offset: "0x60",
		bits: [
			{ name: "SBREAK", description: "Sync Break Extend", size: "3", shift: "0", mask: "0x7" },
			{ name: "SDEL", description: "Sync Delimiter Compare", size: "2", shift: "8", mask: "0x300" },
		]
	},
	{ name: "RD0", description: "Receive data register 0", offset: "0x64",
		bits: [
			{ name: "RD3", description: "Receive Buffer 3", size: "8", shift: "0", mask: "0xFF" },
			{ name: "RD2", description: "Receive Buffer 2", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "RD1", description: "Receive Buffer 1", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "RD0", description: "Receive Buffer 0", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "RD1", description: "Receive data register 1", offset: "0x68",
		bits: [
			{ name: "RD7", description: "Receive Buffer 3", size: "8", shift: "0", mask: "0xFF" },
			{ name: "RD6", description: "Receive Buffer 2", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "RD5", description: "Receive Buffer 1", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "RD4", description: "Receive Buffer 0", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "MASK", description: "Acceptance mask register", offset: "0x6C",
		bits: [
			{ name: "TXIDMASK", description: "TX ID Mask bits (LIN only)", size: "8", shift: "0", mask: "0xFF" },
			{ name: "RXIDMASK", description: "RX ID Mask bits (LIN only)", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "ID", description: "LIN ID Register", offset: "0x70",
		bits: [
			{ name: "IDBYTE", description: "LIN message ID (LIN only)", size: "8", shift: "0", mask: "0xFF" },
			{ name: "IDRESPONDERTASKBYTE", description: "ID  Responder Task byte (LIN only)", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "RECEIVEDID", description: "Current Message ID (LIN only)", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "TD0", description: "Transmit Data Register 0", offset: "0x74",
		bits: [
			{ name: "TD3", description: "TRANSMIT Buffer 3", size: "8", shift: "0", mask: "0xFF" },
			{ name: "TD2", description: "TRANSMIT Buffer 2", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "TD1", description: "TRANSMIT Buffer 1", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "TD0", description: "TRANSMIT Buffer 0", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "TD1", description: "Transmit Data Register 1", offset: "0x78",
		bits: [
			{ name: "TD7", description: "TRANSMIT Buffer 7", size: "8", shift: "0", mask: "0xFF" },
			{ name: "TD6", description: "TRANSMIT Buffer 6", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "TD5", description: "TRANSMIT Buffer 5", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "TD4", description: "TRANSMIT Buffer 4", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "MBRSR", description: "Maximum Baud Rate Selection Register", offset: "0x7C",
		bits: [
			{ name: "MBR", description: "Received Data.", size: "13", shift: "0", mask: "0x1FFF" },
		]
	},
	{ name: "IODFTCTRL", description: "IODFT for LIN", offset: "0x90",
		bits: [
			{ name: "RXPENA", description: "Analog Loopback Via Receive Pin Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "LPBENA", description: "Module Loopback Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "IODFTENA", description: "IO DFT Enable Key", size: "4", shift: "8", mask: "0xF00" },
			{ name: "TXSHIFT", description: "Transmit Delay Shift", size: "3", shift: "16", mask: "0x70000" },
			{ name: "PINSAMPLEMASK", description: "TX Pin Sample Mask", size: "2", shift: "19", mask: "0x180000" },
			{ name: "BRKDTERRENA", description: "Break Detect Error Enable (SCI", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "PERRENA", description: "Parity Error Enable (SCI compatibility", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "FERRENA", description: "Frame Error Enable (SCI compatibility", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "ISFERRENA", description: "Inconsistent Sync Field Error Enable (LIN", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "CERRENA", description: "Checksum Error Enable(LIN mode)", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "PBERRENA", description: "Physical Bus Error Enable (LIN mode)", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "BERRENA", description: "Bit Error Enable (LIN mode)", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "GLB_INT_EN", description: "LIN Global Interrupt Enable Register", offset: "0xE0",
		bits: [
			{ name: "GLBINT0_EN", description: "Global Interrupt Enable for LIN INT0", size: "1", shift: "0", mask: "0x1" },
			{ name: "GLBINT1_EN", description: "Global Interrupt Enable for LIN INT1", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "GLB_INT_FLG", description: "LIN Global Interrupt Flag Register", offset: "0xE4",
		bits: [
			{ name: "INT0_FLG", description: "Global Interrupt Flag for LIN INT0", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT1_FLG", description: "Global Interrupt Flag for LIN INT1", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "GLB_INT_CLR", description: "LIN Global Interrupt Clear Register", offset: "0xE8",
		bits: [
			{ name: "INT0_FLG_CLR", description: "Global Interrupt flag clear for LIN INT0", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT1_FLG_CLR", description: "Global Interrupt flag  clear for LIN INT1", size: "1", shift: "1", mask: "0x2" },
		]
	},
];
module.exports = {
	LINRegisters: LINRegisters,
}
