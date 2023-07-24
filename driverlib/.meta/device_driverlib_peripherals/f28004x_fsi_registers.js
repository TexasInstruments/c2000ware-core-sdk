let FSIRegisters = [
	{ name: "TX_MASTER_CTRL", description: "Transmit master control register", offset: "0x0",
		bits: [
			{ name: "CORE_RST", description: "Transmitter Main Core Reset", size: "1", shift: "0", mask: "0x1" },
			{ name: "FLUSH", description: "Flush Operation Start", size: "1", shift: "1", mask: "0x2" },
			{ name: "KEY", description: "Write Key", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "TX_CLK_CTRL", description: "Transmit clock control register", offset: "0x2",
		bits: [
			{ name: "CLK_RST", description: "Soft Reset for the Clock Divider", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLK_EN", description: "Clock Divider Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "PRESCALE_VAL", description: "Prescale value", size: "8", shift: "2", mask: "0x3FC" },
		]
	},
	{ name: "TX_OPER_CTRL_LO", description: "Transmit operation control register low", offset: "0x4",
		bits: [
			{ name: "DATA_WIDTH", description: "Transmit Data width", size: "2", shift: "0", mask: "0x3" },
			{ name: "SPI_MODE", description: "SPI Mode Select", size: "1", shift: "2", mask: "0x4" },
			{ name: "START_MODE", description: "Transmission Start Mode Select", size: "3", shift: "3", mask: "0x38" },
			{ name: "SW_CRC", description: "CRC Source Select", size: "1", shift: "6", mask: "0x40" },
			{ name: "PING_TO_MODE", description: "Ping Counter Reset Mode Select", size: "1", shift: "7", mask: "0x80" },
			{ name: "SEL_PLLCLK", description: "Input Clock Select", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "TX_OPER_CTRL_HI", description: "Transmit operation control register high", offset: "0x5",
		bits: [
			{ name: "EXT_TRIG_SEL", description: "External Trigger Select", size: "5", shift: "0", mask: "0x1F" },
			{ name: "FORCE_ERR", description: "Error Frame Force", size: "1", shift: "5", mask: "0x20" },
			{ name: "ECC_SEL", description: "ECC Data Width Select", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "TX_FRAME_CTRL", description: "Transmit frame control register", offset: "0x6",
		bits: [
			{ name: "FRAME_TYPE", description: "Transmit Frame Type", size: "4", shift: "0", mask: "0xF" },
			{ name: "N_WORDS", description: "Number of Words to be Transmitted", size: "4", shift: "4", mask: "0xF0" },
			{ name: "START", description: "Start Transmission", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "TX_FRAME_TAG_UDATA", description: "Transmit frame tag and user data register", offset: "0x7",
		bits: [
			{ name: "FRAME_TAG", description: "Frame Tag", size: "4", shift: "0", mask: "0xF" },
			{ name: "USER_DATA", description: "User Data", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "TX_BUF_PTR_LOAD", description: "Transmit buffer pointer control load register", offset: "0x8",
		bits: [
			{ name: "BUF_PTR_LOAD", description: "Buffer Pointer Force Load", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "TX_BUF_PTR_STS", description: "Transmit buffer pointer control status", offset: "0x9",
		bits: [
			{ name: "CURR_BUF_PTR", description: "Current Buffer Pointer Index", size: "4", shift: "0", mask: "0xF" },
			{ name: "CURR_WORD_CNT", description: "Remaining Words in Buffer", size: "5", shift: "8", mask: "0x1F00" },
		]
	},
	{ name: "TX_PING_CTRL", description: "Transmit ping control register", offset: "0xA",
		bits: [
			{ name: "CNT_RST", description: "Ping Counter Reset", size: "1", shift: "0", mask: "0x1" },
			{ name: "TIMER_EN", description: "Ping Counter Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "EXT_TRIG_EN", description: "External Trigger Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "EXT_TRIG_SEL", description: "External Trigger Select", size: "5", shift: "3", mask: "0xF8" },
		]
	},
	{ name: "TX_PING_TAG", description: "Transmit ping tag register", offset: "0xB",
		bits: [
			{ name: "TAG", description: "Ping Frame Tag", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "TX_PING_TO_REF", description: "Transmit ping timeout counter reference", offset: "0xC",
		bits: [
		]
	},
	{ name: "TX_PING_TO_CNT", description: "Transmit ping timeout current count", offset: "0xE",
		bits: [
		]
	},
	{ name: "TX_INT_CTRL", description: "Transmit interrupt event control register", offset: "0x10",
		bits: [
			{ name: "INT1_EN_FRAME_DONE", description: "Enable Frame Done Interrupt to INT1", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT1_EN_BUF_UNDERRUN", description: "Enable Buffer Underrun Interrupt to INT1", size: "1", shift: "1", mask: "0x2" },
			{ name: "INT1_EN_BUF_OVERRUN", description: "Enable Buffer Overrun Interrupt to INT1", size: "1", shift: "2", mask: "0x4" },
			{ name: "INT1_EN_PING_TO", description: "Enable Ping Timer Interrupt to INT1", size: "1", shift: "3", mask: "0x8" },
			{ name: "INT2_EN_FRAME_DONE", description: "Enable Frame Done Interrupt to INT2", size: "1", shift: "8", mask: "0x100" },
			{ name: "INT2_EN_BUF_UNDERRUN", description: "Enable Buffer Underrun Interrupt to INT2", size: "1", shift: "9", mask: "0x200" },
			{ name: "INT2_EN_BUF_OVERRUN", description: "Enable Buffer Overrun Interrupt to INT2", size: "1", shift: "10", mask: "0x400" },
			{ name: "INT2_EN_PING_TO", description: "Enable Ping Timer Interrupt to INT2", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "TX_DMA_CTRL", description: "Transmit DMA event control register", offset: "0x11",
		bits: [
			{ name: "DMA_EVT_EN", description: "DMA Event Enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "TX_LOCK_CTRL", description: "Transmit lock control register", offset: "0x12",
		bits: [
			{ name: "LOCK", description: "Control Register Lock Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Write Key", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "TX_EVT_STS", description: "Transmit event and error status flag register", offset: "0x14",
		bits: [
			{ name: "FRAME_DONE", description: "Frame Done Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "BUF_UNDERRUN", description: "Buffer Underrun Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "BUF_OVERRUN", description: "Buffer Overrun Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "PING_TRIGGERED", description: "Ping Frame Triggered Flag", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "TX_EVT_CLR", description: "Transmit event and error clear register", offset: "0x16",
		bits: [
			{ name: "FRAME_DONE", description: "Frame Done Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "BUF_UNDERRUN", description: "Buffer Underrun Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "BUF_OVERRUN", description: "Buffer Overrun Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "PING_TRIGGERED", description: "Ping Frame Triggered Flag Clear", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "TX_EVT_FRC", description: "Transmit event and error flag force register", offset: "0x17",
		bits: [
			{ name: "FRAME_DONE", description: "Frame Done Flag Force", size: "1", shift: "0", mask: "0x1" },
			{ name: "BUF_UNDERRUN", description: "Buffer Underrun Flag Force", size: "1", shift: "1", mask: "0x2" },
			{ name: "BUF_OVERRUN", description: "Buffer Overrun Flag Force", size: "1", shift: "2", mask: "0x4" },
			{ name: "PING_TRIGGERED", description: "Ping Frame Triggered Flag Force", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "TX_USER_CRC", description: "Transmit user-defined CRC register", offset: "0x18",
		bits: [
			{ name: "USER_CRC", description: "User-defined CRC", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "TX_ECC_DATA", description: "Transmit ECC data register", offset: "0x20",
		bits: [
			{ name: "DATA_LOW", description: "ECC Data Lower 16 Bits", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA_HIGH", description: "ECC Data Upper 16 Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "TX_ECC_VAL", description: "Transmit ECC value register", offset: "0x22",
		bits: [
			{ name: "ECC_VAL", description: "Computed ECC Value", size: "7", shift: "0", mask: "0x7F" },
		]
	},
	{ name: "TX_BUF_BASE(i)", description: "(0 <= i < 16) Base address for transmit", offset: "(0x40U + (i))",
		bits: [
		]
	},
	{ name: "RX_MASTER_CTRL", description: "Receive master control register", offset: "0x0",
		bits: [
			{ name: "CORE_RST", description: "Receiver Main Core Reset", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT_LOOPBACK", description: "Internal Loopback Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "SPI_PAIRING", description: "Clock Pairing for SPI-like Behaviour", size: "1", shift: "2", mask: "0x4" },
			{ name: "KEY", description: "Write Key", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "RX_OPER_CTRL", description: "Receive operation control register", offset: "0x4",
		bits: [
			{ name: "DATA_WIDTH", description: "Receive Data Width Select", size: "2", shift: "0", mask: "0x3" },
			{ name: "SPI_MODE", description: "SPI Mode Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "N_WORDS", description: "Number of Words to be Received", size: "4", shift: "3", mask: "0x78" },
			{ name: "ECC_SEL", description: "ECC Data Width Select", size: "1", shift: "7", mask: "0x80" },
			{ name: "PING_WD_RST_MODE", description: "Ping Watchdog Timeout Mode Select", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "RX_FRAME_INFO", description: "Receive frame control register", offset: "0x6",
		bits: [
			{ name: "FRAME_TYPE", description: "Received Frame Type", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "RX_FRAME_TAG_UDATA", description: "Receive frame tag and user data register", offset: "0x7",
		bits: [
			{ name: "FRAME_TAG", description: "Received Frame Tag", size: "4", shift: "1", mask: "0x1E" },
			{ name: "USER_DATA", description: "Received User Data", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "RX_DMA_CTRL", description: "Receive DMA event control register", offset: "0x8",
		bits: [
			{ name: "DMA_EVT_EN", description: "DMA Event Enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "RX_EVT_STS", description: "Receive event and error status flag register", offset: "0xA",
		bits: [
			{ name: "PING_WD_TO", description: "Ping Watchdog Timeout Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "FRAME_WD_TO", description: "Frame Watchdog Timeout Flag.", size: "1", shift: "1", mask: "0x2" },
			{ name: "CRC_ERR", description: "CRC Error Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "TYPE_ERR", description: "Frame Type Error Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "EOF_ERR", description: "End-of-Frame Error Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "BUF_OVERRUN", description: "Receive Buffer Overrun Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "FRAME_DONE", description: "Frame Done Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "BUF_UNDERRUN", description: "Receive Buffer Underrun Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "ERR_FRAME", description: "Error Frame Received Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "PING_FRAME", description: "Ping Frame Received Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "FRAME_OVERRUN", description: "Frame Overrun Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "DATA_FRAME", description: "Data Frame Received Flag", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "RX_CRC_INFO", description: "Receive CRC info of received and computed CRC", offset: "0xB",
		bits: [
			{ name: "RX_CRC", description: "Received CRC Value", size: "8", shift: "0", mask: "0xFF" },
			{ name: "CALC_CRC", description: "Hardware Calculated CRC", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "RX_EVT_CLR", description: "Receive event and error clear register", offset: "0xC",
		bits: [
			{ name: "PING_WD_TO", description: "Ping Watchdog Timeout Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "FRAME_WD_TO", description: "Frame Watchdog Timeout Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "CRC_ERR", description: "CRC Error Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "TYPE_ERR", description: "Frame Type Error Flag Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "EOF_ERR", description: "End-of-Frame Error Flag Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "BUF_OVERRUN", description: "Receive Buffer Overrun Flag Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "FRAME_DONE", description: "Frame Done Flag Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "BUF_UNDERRUN", description: "Receive Buffer Underrun Flag Clear", size: "1", shift: "7", mask: "0x80" },
			{ name: "ERR_FRAME", description: "Error Frame Received Flag Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "PING_FRAME", description: "PING Frame Received Flag Clear", size: "1", shift: "9", mask: "0x200" },
			{ name: "FRAME_OVERRUN", description: "Frame Overrun Flag Clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "DATA_FRAME", description: "Data Frame Received Flag Clear", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "RX_EVT_FRC", description: "Receive event and error flag force register", offset: "0xD",
		bits: [
			{ name: "PING_WD_TO", description: "Ping Watchdog Timeout Flag Force", size: "1", shift: "0", mask: "0x1" },
			{ name: "FRAME_WD_TO", description: "Frame Watchdog Timeout Flag Force", size: "1", shift: "1", mask: "0x2" },
			{ name: "CRC_ERR", description: "CRC Error Flag Force", size: "1", shift: "2", mask: "0x4" },
			{ name: "TYPE_ERR", description: "Frame Type Error Flag Force", size: "1", shift: "3", mask: "0x8" },
			{ name: "EOF_ERR", description: "End-of-Frame Error Flag Force", size: "1", shift: "4", mask: "0x10" },
			{ name: "BUF_OVERRUN", description: "Receive Buffer Overrun Flag Force", size: "1", shift: "5", mask: "0x20" },
			{ name: "FRAME_DONE", description: "Frame Done Flag Force", size: "1", shift: "6", mask: "0x40" },
			{ name: "BUF_UNDERRUN", description: "Receive Buffer Underrun Flag Force", size: "1", shift: "7", mask: "0x80" },
			{ name: "ERR_FRAME", description: "Error Frame Received Flag Force", size: "1", shift: "8", mask: "0x100" },
			{ name: "PING_FRAME", description: "Ping Frame Received Flag Force", size: "1", shift: "9", mask: "0x200" },
			{ name: "FRAME_OVERRUN", description: "Frame Overrun Flag Force", size: "1", shift: "10", mask: "0x400" },
			{ name: "DATA_FRAME", description: "Data Frame Received Flag Force", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "RX_BUF_PTR_LOAD", description: "Receive buffer pointer load register", offset: "0xE",
		bits: [
			{ name: "BUF_PTR_LOAD", description: "Load value for receive buffer pointer", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "RX_BUF_PTR_STS", description: "Receive buffer pointer status register", offset: "0xF",
		bits: [
			{ name: "CURR_BUF_PTR", description: "Current Buffer Pointer Index", size: "4", shift: "0", mask: "0xF" },
			{ name: "CURR_WORD_CNT", description: "Available Words in Buffer", size: "5", shift: "8", mask: "0x1F00" },
		]
	},
	{ name: "RX_FRAME_WD_CTRL", description: "Receive frame watchdog control register", offset: "0x10",
		bits: [
			{ name: "FRAME_WD_CNT_RST", description: "Frame Watchdog Counter Reset", size: "1", shift: "0", mask: "0x1" },
			{ name: "FRAME_WD_EN", description: "Frame Watchdog Counter Enable", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "RX_FRAME_WD_REF", description: "Receive frame watchdog counter reference", offset: "0x12",
		bits: [
		]
	},
	{ name: "RX_FRAME_WD_CNT", description: "Receive frame watchdog current count", offset: "0x14",
		bits: [
		]
	},
	{ name: "RX_PING_WD_CTRL", description: "Receive ping watchdog control register", offset: "0x16",
		bits: [
			{ name: "PING_WD_RST", description: "Ping Watchdog Counter Reset", size: "1", shift: "0", mask: "0x1" },
			{ name: "PING_WD_EN", description: "Ping Watchdog Counter Enable", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "RX_PING_TAG", description: "Receive ping tag register", offset: "0x17",
		bits: [
			{ name: "PING_TAG", description: "Ping Frame Tag", size: "4", shift: "1", mask: "0x1E" },
		]
	},
	{ name: "RX_PING_WD_REF", description: "Receive ping watchdog counter reference", offset: "0x18",
		bits: [
		]
	},
	{ name: "RX_PING_WD_CNT", description: "Receive pingwatchdog current count", offset: "0x1A",
		bits: [
		]
	},
	{ name: "RX_INT1_CTRL", description: "Receive interrupt control register for", offset: "0x1C",
		bits: [
			{ name: "INT1_EN_PING_WD_TO", description: "Enable Ping Watchdog Timeout Interrupt", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT1_EN_FRAME_WD_TO", description: "Enable Frame Watchdog Timeout", size: "1", shift: "1", mask: "0x2" },
			{ name: "INT1_EN_CRC_ERR", description: "Enable CRC Error Interrupt to INT1", size: "1", shift: "2", mask: "0x4" },
			{ name: "INT1_EN_TYPE_ERR", description: "Enable Frame Type Error Interrupt to", size: "1", shift: "3", mask: "0x8" },
			{ name: "INT1_EN_EOF_ERR", description: "Enable End-of-Frame Error Interrupt to", size: "1", shift: "4", mask: "0x10" },
			{ name: "INT1_EN_OVERRUN", description: "Enable Receive Buffer Overrun", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT1_EN_FRAME_DONE", description: "Enable Frame Done Interrupt to INT1", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT1_EN_UNDERRUN", description: "Enable Buffer Underrun Interrupt to", size: "1", shift: "7", mask: "0x80" },
			{ name: "INT1_EN_ERR_FRAME", description: "Enable Error Frame Received Interrupt", size: "1", shift: "8", mask: "0x100" },
			{ name: "INT1_EN_PING_FRAME", description: "Enable Ping Frame Received Interrupt", size: "1", shift: "9", mask: "0x200" },
			{ name: "INT1_EN_FRAME_OVERRUN", description: "Enable Frame Overrun Interrupt to INT1", size: "1", shift: "10", mask: "0x400" },
			{ name: "INT1_EN_DATA_FRAME", description: "Enable Data Frame Received Interrupt", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "RX_INT2_CTRL", description: "Receive interrupt control register for", offset: "0x1D",
		bits: [
			{ name: "INT2_EN_PING_WD_TO", description: "Enable Ping Watchdog Timeout Interrupt", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT2_EN_FRAME_WD_TO", description: "Enable Frame Watchdog Timeout", size: "1", shift: "1", mask: "0x2" },
			{ name: "INT2_EN_CRC_ERR", description: "Enable CRC Errror Interrupt to INT2", size: "1", shift: "2", mask: "0x4" },
			{ name: "INT2_EN_TYPE_ERR", description: "Enable Frame Type Error Interrupt to", size: "1", shift: "3", mask: "0x8" },
			{ name: "INT2_EN_EOF_ERR", description: "Enable End-of-Frame Error Interrupt to", size: "1", shift: "4", mask: "0x10" },
			{ name: "INT2_EN_OVERRUN", description: "Enable Buffer Overrun Interrupt to", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT2_EN_FRAME_DONE", description: "Enable Frame Done Interrupt to INT2", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT2_EN_UNDERRUN", description: "Enable Buffer Underrun Interrupt to", size: "1", shift: "7", mask: "0x80" },
			{ name: "INT2_EN_ERR_FRAME", description: "Enable Error Frame Received Interrupt", size: "1", shift: "8", mask: "0x100" },
			{ name: "INT2_EN_PING_FRAME", description: "Enable Ping Frame Received Interrupt", size: "1", shift: "9", mask: "0x200" },
			{ name: "INT2_EN_FRAME_OVERRUN", description: "Enable Frame Overrun Interrupt to INT2", size: "1", shift: "10", mask: "0x400" },
			{ name: "INT2_EN_DATA_FRAME", description: "Enable Data Frame Received Interrupt", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "RX_LOCK_CTRL", description: "Receive lock control register", offset: "0x1E",
		bits: [
			{ name: "LOCK", description: "Control Register Lock Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Write Key", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "RX_ECC_DATA", description: "Receive ECC data register", offset: "0x20",
		bits: [
			{ name: "DATA_LOW", description: "ECC Data Lower 16 Bits", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DATA_HIGH", description: "ECC Data Upper 16 Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "RX_ECC_VAL", description: "Receive ECC value register", offset: "0x22",
		bits: [
			{ name: "ECC_VAL", description: "Computed ECC Value", size: "7", shift: "0", mask: "0x7F" },
		]
	},
	{ name: "RX_ECC_SEC_DATA", description: "Receive ECC corrected data register", offset: "0x24",
		bits: [
		]
	},
	{ name: "RX_ECC_LOG", description: "Receive ECC log and status register", offset: "0x26",
		bits: [
			{ name: "SBE", description: "Single Bit Error Detected", size: "1", shift: "0", mask: "0x1" },
			{ name: "MBE", description: "Multiple Bit Errors Detected", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "RX_DLYLINE_CTRL", description: "Receive delay line control register", offset: "0x30",
		bits: [
			{ name: "RXCLK_DLY", description: "Delay Line Tap Select for RXCLK", size: "5", shift: "0", mask: "0x1F" },
			{ name: "RXD0_DLY", description: "Delay Line Tap Select for RXD0", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "RXD1_DLY", description: "Delay Line Tap Select for RXD1", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "RX_VIS_1", description: "Receive debug visibility register 1", offset: "0x38",
		bits: [
			{ name: "RX_CORE_STS", description: "Receiver Core Status", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "RX_BUF_BASE(i)", description: "(0 <= i < 16) Base address for receive data", offset: "(0x40U + (i))",
		bits: [
		]
	},
];
module.exports = {
	FSIRegisters: FSIRegisters,
}
