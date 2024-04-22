let LIN_LoopbackType = [
	{ name: "LIN_LOOPBACK_DIGITAL", displayName: "Digital Loopback Mode" },
	{ name: "LIN_LOOPBACK_ANALOG", displayName: "Analog Loopback Mode" },
]
let LIN_AnalogLoopback = [
	{ name: "LIN_ANALOG_LOOP_NONE", displayName: "Default path for digital loopback mode" },
	{ name: "LIN_ANALOG_LOOP_TX", displayName: "Analog loopback through transmit pin" },
	{ name: "LIN_ANALOG_LOOP_RX", displayName: "Analog loopback through receive pin" },
]
let LIN_CommMode = [
	{ name: "LIN_COMM_LIN_USELENGTHVAL", displayName: "Use the length indicated in the LENGTH field of the SCIFORMAT register" },
	{ name: "LIN_COMM_LIN_ID4ID5LENCTL", displayName: "Use ID4 and ID5 to convey the length" },
]
let LIN_SCICommMode = [
	{ name: "LIN_COMM_SCI_IDLELINE", displayName: "Idle-line mode is used" },
	{ name: "LIN_COMM_SCI_ADDRBIT", displayName: "Address bit mode is used" },
]
let LIN_LINMode = [
	{ name: "LIN_MODE_LIN_RESPONDER", displayName: "The node is in responder mode", legacyNames: ["LIN_MODE_LIN_SLAVE"]},
	{ name: "LIN_MODE_LIN_COMMANDER", displayName: "The node is in commander mode", legacyNames: ["LIN_MODE_LIN_MASTER"]},
]
let LIN_InterruptLine = [
	{ name: "LIN_INTERRUPT_LINE0", displayName: "Interrupt line 0" },
	{ name: "LIN_INTERRUPT_LINE1", displayName: "Interrupt line 1" },
]
let LIN_MessageFilter = [
	{ name: "LIN_MSG_FILTER_IDBYTE", displayName: "LIN Message ID Byte Filtering" },
	{ name: "LIN_MSG_FILTER_IDRESPONDER", displayName: "ID Responder Task Byte Filtering", legacyNames: ["LIN_MSG_FILTER_IDSLAVE"]},
]
let LIN_ChecksumType = [
	{ name: "LIN_CHECKSUM_CLASSIC", displayName: "Checksum Classic" },
	{ name: "LIN_CHECKSUM_ENHANCED", displayName: "Checksum Enhanced" },
]
let LIN_DebugMode = [
	{ name: "LIN_DEBUG_FROZEN", displayName: "Freeze module during debug" },
	{ name: "LIN_DEBUG_COMPLETE", displayName: "Complete Tx/Rx before Freezing" },
]
let LIN_PinSampleMask = [
	{ name: "LIN_PINMASK_NONE", displayName: "No Pin Mask" },
	{ name: "LIN_PINMASK_CENTER", displayName: "Invert Tx Pin value at T-bit center" },
	{ name: "LIN_PINMASK_CENTER_SCLK", displayName: "Invert Tx Pin value at T-bit center + SCLK" },
	{ name: "LIN_PINMASK_CENTER_2SCLK", displayName: "Invert Tx Pin value at T-bit center + 2 SCLK" },
]
let LIN_SCIParityType = [
	{ name: "LIN_SCI_PAR_ODD", displayName: "Odd parity" },
	{ name: "LIN_SCI_PAR_EVEN", displayName: "Even parity" },
]
let LIN_SCIStopBits = [
	{ name: "LIN_SCI_STOP_ONE", displayName: "Use One Stop bit" },
	{ name: "LIN_SCI_STOP_TWO", displayName: "Use Two Stop bits" },
]
let LIN_PinType = [
	{ name: "LIN_PINTYPE_TX", displayName: "Transmit Pin" },
	{ name: "LIN_PINTYPE_RX", displayName: "Receive Pin" },
]
let LIN_INT = [
	{ name: "LIN_INT_WAKEUP", displayName: "Wakeup" },
	{ name: "LIN_INT_TO", displayName: "Time out" },
	{ name: "LIN_INT_TOAWUS", displayName: "Time out after wakeup signal" },
	{ name: "LIN_INT_TOA3WUS", displayName: "Time out after 3 wakeup signals" },
	{ name: "LIN_INT_TX", displayName: "Transmit buffer ready" },
	{ name: "LIN_INT_RX", displayName: "Receive buffer ready" },
	{ name: "LIN_INT_ID", displayName: "Received matching identifier" },
	{ name: "LIN_INT_PE", displayName: "Parity error" },
	{ name: "LIN_INT_OE", displayName: "Overrun error" },
	{ name: "LIN_INT_FE", displayName: "Framing error" },
	{ name: "LIN_INT_NRE", displayName: "No response error" },
	{ name: "LIN_INT_ISFE", displayName: "Inconsistent sync field error" },
	{ name: "LIN_INT_CE", displayName: "Checksum error" },
	{ name: "LIN_INT_PBE", displayName: "Physical bus error" },
	{ name: "LIN_INT_BE", displayName: "Bit error" },
	{ name: "LIN_INT_ALL", displayName: "All interrupts" },
]
let LIN_FLAG = [
	{ name: "LIN_FLAG_BREAK", displayName: "Break-Detect" },
	{ name: "LIN_FLAG_WAKEUP", displayName: "Wakeup" },
	{ name: "LIN_FLAG_IDLE", displayName: "Bus Idle" },
	{ name: "LIN_FLAG_BUSY", displayName: "Busy" },
	{ name: "LIN_FLAG_TO", displayName: "Time out" },
	{ name: "LIN_FLAG_TOAWUS", displayName: "Time out after wakeup" },
	{ name: "LIN_FLAG_TOA3WUS", displayName: "Time out after 3 wakeup" },
	{ name: "LIN_FLAG_TXRDY", displayName: "Transmit Buffer ready" },
	{ name: "LIN_FLAG_RXRDY", displayName: "Receive Buffer ready" },
	{ name: "LIN_FLAG_TXWAKE", displayName: "Transmitter Wakeup" },
	{ name: "LIN_FLAG_TXEMPTY", displayName: "Transmitter Empty" },
	{ name: "LIN_FLAG_RXWAKE", displayName: "Receiver Wakeup detect" },
	{ name: "LIN_FLAG_TXID", displayName: "ID on Transmit" },
	{ name: "LIN_FLAG_RXID", displayName: "ID on Receive" },
	{ name: "LIN_FLAG_PE", displayName: "Parity Error" },
	{ name: "LIN_FLAG_OE", displayName: "Overrun Error" },
	{ name: "LIN_FLAG_FE", displayName: "Framing Error" },
	{ name: "LIN_FLAG_NRE", displayName: "No-Response Error" },
	{ name: "LIN_FLAG_ISFE", displayName: "Inconsistent Sync Field" },
	{ name: "LIN_FLAG_CE", displayName: "Checksum Error" },
	{ name: "LIN_FLAG_PBE", displayName: "Physical Bus Error" },
	{ name: "LIN_FLAG_BE", displayName: "Bit Error" },
]
let LIN_VECT = [
	{ name: "LIN_VECT_NONE", displayName: "No Interrupt" },
	{ name: "LIN_VECT_WAKEUP", displayName: "Wakeup" },
	{ name: "LIN_VECT_ISFE", displayName: "Inconsistent-sync-field Error" },
	{ name: "LIN_VECT_PE", displayName: "Parity Error" },
	{ name: "LIN_VECT_ID", displayName: "ID Interrupt" },
	{ name: "LIN_VECT_PBE", displayName: "Physical Bus Error" },
	{ name: "LIN_VECT_FE", displayName: "Frame Error" },
	{ name: "LIN_VECT_BREAK", displayName: "Break detect" },
	{ name: "LIN_VECT_CE", displayName: "Checksum Error" },
	{ name: "LIN_VECT_OE", displayName: "Overrun Error" },
	{ name: "LIN_VECT_BE", displayName: "Bit Error" },
	{ name: "LIN_VECT_RX", displayName: "Receive Interrupt" },
	{ name: "LIN_VECT_TX", displayName: "Transmit Interrupt" },
	{ name: "LIN_VECT_NRE", displayName: "No-response Error" },
	{ name: "LIN_VECT_TOAWUS", displayName: "Timeout after wakeup signal" },
	{ name: "LIN_VECT_TOA3WUS", displayName: "Timeout after 3 wakeup signals" },
	{ name: "LIN_VECT_TO", displayName: "Timeout (Bus Idle)" },
]
let LIN_SCI = [
	{ name: "LIN_SCI_ALL_ERRORS", displayName: "All module errors" },
	{ name: "LIN_SCI_FRAME_ERROR", displayName: "Frame Error" },
	{ name: "LIN_SCI_PARITY_ERROR", displayName: "Parity Error" },
	{ name: "LIN_SCI_BREAK_ERROR", displayName: "Break Detect Error" },
]
let LIN_SCI_INT = [
	{ name: "LIN_SCI_INT_BREAK", displayName: "Break Detect" },
	{ name: "LIN_SCI_INT_WAKEUP", displayName: "Wakeup" },
	{ name: "LIN_SCI_INT_TX", displayName: "Transmit Buffer" },
	{ name: "LIN_SCI_INT_RX", displayName: "Receive Buffer" },
	{ name: "LIN_SCI_INT_TX_DMA", displayName: "DMA Transmit" },
	{ name: "LIN_SCI_INT_RX_DMA", displayName: "DMA Receive" },
	{ name: "LIN_SCI_INT_RX_DMA_ALL", displayName: "DMA Receive All" },
	{ name: "LIN_SCI_INT_PARITY", displayName: "Parity Error" },
	{ name: "LIN_SCI_INT_OVERRUN", displayName: "Overrun Error" },
	{ name: "LIN_SCI_INT_FRAME", displayName: "Framing Error" },
	{ name: "LIN_SCI_INT_ALL", displayName: "All Interrupts" },
]
module.exports = {
	LIN_LoopbackType: LIN_LoopbackType,
	LIN_AnalogLoopback: LIN_AnalogLoopback,
	LIN_CommMode: LIN_CommMode,
	LIN_SCICommMode: LIN_SCICommMode,
	LIN_LINMode: LIN_LINMode,
	LIN_InterruptLine: LIN_InterruptLine,
	LIN_MessageFilter: LIN_MessageFilter,
	LIN_ChecksumType: LIN_ChecksumType,
	LIN_DebugMode: LIN_DebugMode,
	LIN_PinSampleMask: LIN_PinSampleMask,
	LIN_SCIParityType: LIN_SCIParityType,
	LIN_SCIStopBits: LIN_SCIStopBits,
	LIN_PinType: LIN_PinType,
	LIN_INT: LIN_INT,
	LIN_FLAG: LIN_FLAG,
	LIN_VECT: LIN_VECT,
	LIN_SCI: LIN_SCI,
	LIN_SCI_INT: LIN_SCI_INT,
}
