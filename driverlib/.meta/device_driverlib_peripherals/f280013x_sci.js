let SCI_ParityType = [
	{ name: "SCI_CONFIG_PAR_NONE", displayName: "No parity" },
	{ name: "SCI_CONFIG_PAR_EVEN", displayName: "Even parity" },
	{ name: "SCI_CONFIG_PAR_ODD", displayName: "Odd parity" },
]
let SCI_TxFIFOLevel = [
	{ name: "SCI_FIFO_TX0", displayName: "Transmit interrupt empty" },
	{ name: "SCI_FIFO_TX1", displayName: "Transmit interrupt 1/16 full" },
	{ name: "SCI_FIFO_TX2", displayName: "Transmit interrupt 2/16 full" },
	{ name: "SCI_FIFO_TX3", displayName: "Transmit interrupt 3/16 full" },
	{ name: "SCI_FIFO_TX4", displayName: "Transmit interrupt 4/16 full" },
	{ name: "SCI_FIFO_TX5", displayName: "Transmit interrupt 5/16 full" },
	{ name: "SCI_FIFO_TX6", displayName: "Transmit interrupt 6/16 full" },
	{ name: "SCI_FIFO_TX7", displayName: "Transmit interrupt 7/16 full" },
	{ name: "SCI_FIFO_TX8", displayName: "Transmit interrupt 8/16 full" },
	{ name: "SCI_FIFO_TX9", displayName: "Transmit interrupt 9/16 full" },
	{ name: "SCI_FIFO_TX10", displayName: "Transmit interrupt 10/16 full" },
	{ name: "SCI_FIFO_TX11", displayName: "Transmit interrupt 11/16 full" },
	{ name: "SCI_FIFO_TX12", displayName: "Transmit interrupt 12/16 full" },
	{ name: "SCI_FIFO_TX13", displayName: "Transmit interrupt 13/16 full" },
	{ name: "SCI_FIFO_TX14", displayName: "Transmit interrupt 14/16 full" },
	{ name: "SCI_FIFO_TX15", displayName: "Transmit interrupt 15/16 full" },
	{ name: "SCI_FIFO_TX16", displayName: "Transmit interrupt full" },
]
let SCI_RxFIFOLevel = [
	{ name: "SCI_FIFO_RX0", displayName: "Receive interrupt empty" },
	{ name: "SCI_FIFO_RX1", displayName: "Receive interrupt 1/16 full" },
	{ name: "SCI_FIFO_RX2", displayName: "Receive interrupt 2/16 full" },
	{ name: "SCI_FIFO_RX3", displayName: "Receive interrupt 3/16 full" },
	{ name: "SCI_FIFO_RX4", displayName: "Receive interrupt 4/16 full" },
	{ name: "SCI_FIFO_RX5", displayName: "Receive interrupt 5/16 full" },
	{ name: "SCI_FIFO_RX6", displayName: "Receive interrupt 6/16 full" },
	{ name: "SCI_FIFO_RX7", displayName: "Receive interrupt 7/16 full" },
	{ name: "SCI_FIFO_RX8", displayName: "Receive interrupt 8/16 full" },
	{ name: "SCI_FIFO_RX9", displayName: "Receive interrupt 9/16 full" },
	{ name: "SCI_FIFO_RX10", displayName: "Receive interrupt 10/16 full" },
	{ name: "SCI_FIFO_RX11", displayName: "Receive interrupt 11/16 full" },
	{ name: "SCI_FIFO_RX12", displayName: "Receive interrupt 12/16 full" },
	{ name: "SCI_FIFO_RX13", displayName: "Receive interrupt 13/16 full" },
	{ name: "SCI_FIFO_RX14", displayName: "Receive interrupt 14/16 full" },
	{ name: "SCI_FIFO_RX15", displayName: "Receive interrupt 15/16 full" },
	{ name: "SCI_FIFO_RX16", displayName: "Receive interrupt full" },
]
let SCI_INT = [
	{ name: "SCI_INT_RXERR", displayName: "RXERR interrupt" },
	{ name: "SCI_INT_RXRDY_BRKDT", displayName: "RXRDY interrupt" },
	{ name: "SCI_INT_TXRDY", displayName: "TXRDY interrupt" },
	{ name: "SCI_INT_TXFF", displayName: "TX FIFO level interrupt" },
	{ name: "SCI_INT_RXFF", displayName: "RX FIFO level interrupt" },
	{ name: "SCI_INT_FE", displayName: "Frame Error" },
	{ name: "SCI_INT_OE", displayName: "Overrun Error" },
	{ name: "SCI_INT_PE", displayName: "Parity Error" },
]
let SCI_CONFIG = [
	{ name: "SCI_CONFIG_WLEN_MASK", displayName: "Mask for extracting word length" },
	{ name: "SCI_CONFIG_WLEN_8", displayName: "8 bit data" },
	{ name: "SCI_CONFIG_WLEN_7", displayName: "7 bit data" },
	{ name: "SCI_CONFIG_WLEN_6", displayName: "6 bit data" },
	{ name: "SCI_CONFIG_WLEN_5", displayName: "5 bit data" },
	{ name: "SCI_CONFIG_WLEN_4", displayName: "4 bit data" },
	{ name: "SCI_CONFIG_WLEN_3", displayName: "3 bit data" },
	{ name: "SCI_CONFIG_WLEN_2", displayName: "2 bit data" },
	{ name: "SCI_CONFIG_WLEN_1", displayName: "1 bit data" },
	{ name: "SCI_CONFIG_STOP_MASK", displayName: "Mask for extracting stop bits" },
	{ name: "SCI_CONFIG_STOP_ONE", displayName: "One stop bit" },
	{ name: "SCI_CONFIG_STOP_TWO", displayName: "Two stop bits" },
	{ name: "SCI_CONFIG_PAR_MASK", displayName: "Parity Mask" },
]
let SCI_RXSTATUS = [
	{ name: "SCI_RXSTATUS_WAKE", displayName: "Receiver wake up detect" },
	{ name: "SCI_RXSTATUS_PARITY", displayName: "Parity error" },
	{ name: "SCI_RXSTATUS_OVERRUN", displayName: "Overrun error" },
	{ name: "SCI_RXSTATUS_FRAMING", displayName: "Framing error" },
	{ name: "SCI_RXSTATUS_BREAK", displayName: "Break detect" },
	{ name: "SCI_RXSTATUS_READY", displayName: "Receiver ready" },
	{ name: "SCI_RXSTATUS_ERROR", displayName: "Receiver error" },
]
module.exports = {
	SCI_ParityType: SCI_ParityType,
	SCI_TxFIFOLevel: SCI_TxFIFOLevel,
	SCI_RxFIFOLevel: SCI_RxFIFOLevel,
	SCI_INT: SCI_INT,
	SCI_CONFIG: SCI_CONFIG,
	SCI_RXSTATUS: SCI_RXSTATUS,
}