let UART_TxFIFOLevelFine = [
	{ name: "UART_FIFO_TXEMPTY", displayName: "Transmit interrupt empty" },
	{ name: "UART_FIFO_TX0", displayName: "Transmit interrupt 0/16 full" },
	{ name: "UART_FIFO_TX1", displayName: "Transmit interrupt 1/16 full" },
	{ name: "UART_FIFO_TX2", displayName: "Transmit interrupt 2/16 full" },
	{ name: "UART_FIFO_TX3", displayName: "Transmit interrupt 3/16 full" },
	{ name: "UART_FIFO_TX4", displayName: "Transmit interrupt 4/16 full" },
	{ name: "UART_FIFO_TX5", displayName: "Transmit interrupt 5/16 full" },
	{ name: "UART_FIFO_TX6", displayName: "Transmit interrupt 6/16 full" },
	{ name: "UART_FIFO_TX7", displayName: "Transmit interrupt 7/16 full" },
	{ name: "UART_FIFO_TX8", displayName: "Transmit interrupt 8/16 full" },
	{ name: "UART_FIFO_TX9", displayName: "Transmit interrupt 9/16 full" },
	{ name: "UART_FIFO_TX10", displayName: "Transmit interrupt 10/16 full" },
	{ name: "UART_FIFO_TX11", displayName: "Transmit interrupt 11/16 full" },
	{ name: "UART_FIFO_TX12", displayName: "Transmit interrupt 12/16 full" },
	{ name: "UART_FIFO_TX13", displayName: "Transmit interrupt 13/16 full" },
	{ name: "UART_FIFO_TX14", displayName: "Transmit interrupt 14/16 full" },
	{ name: "UART_FIFO_TX15", displayName: "Transmit interrupt 15/16 full" },
]
let UART_RxFIFOLevelFine = [
	{ name: "UART_FIFO_RXFULL", displayName: "Receive interrupt full" },
	{ name: "UART_FIFO_RX0", displayName: "Receive interrupt 16/16 full" },
	{ name: "UART_FIFO_RX1", displayName: "Receive interrupt 1/16 full" },
	{ name: "UART_FIFO_RX2", displayName: "Receive interrupt 2/16 full" },
	{ name: "UART_FIFO_RX3", displayName: "Receive interrupt 3/16 full" },
	{ name: "UART_FIFO_RX4", displayName: "Receive interrupt 4/16 full" },
	{ name: "UART_FIFO_RX5", displayName: "Receive interrupt 5/16 full" },
	{ name: "UART_FIFO_RX6", displayName: "Receive interrupt 6/16 full" },
	{ name: "UART_FIFO_RX7", displayName: "Receive interrupt 7/16 full" },
	{ name: "UART_FIFO_RX8", displayName: "Receive interrupt 8/16 full" },
	{ name: "UART_FIFO_RX9", displayName: "Receive interrupt 9/16 full" },
	{ name: "UART_FIFO_RX10", displayName: "Receive interrupt 10/16 full" },
	{ name: "UART_FIFO_RX11", displayName: "Receive interrupt 11/16 full" },
	{ name: "UART_FIFO_RX12", displayName: "Receive interrupt 12/16 full" },
	{ name: "UART_FIFO_RX13", displayName: "Receive interrupt 13/16 full" },
	{ name: "UART_FIFO_RX14", displayName: "Receive interrupt 14/16 full" },
	{ name: "UART_FIFO_RX15", displayName: "Receive interrupt 15/16 full" },
]
let UART_INT = [
	{ name: "UART_INT_DMATX", displayName: "DMA TX interrupt" },
	{ name: "UART_INT_DMARX", displayName: "DMA RX interrupt" },
	{ name: "UART_INT_9BIT", displayName: "9-bit address match interrupt" },
	{ name: "UART_INT_EOT", displayName: "Receive Interrupt Mask" },
	{ name: "UART_INT_OE", displayName: "Overrun Error Interrupt Mask" },
	{ name: "UART_INT_BE", displayName: "Break Error Interrupt Mask" },
	{ name: "UART_INT_PE", displayName: "Parity Error Interrupt Mask" },
	{ name: "UART_INT_FE", displayName: "Framing Error Interrupt Mask" },
	{ name: "UART_INT_RT", displayName: "Receive Timeout Interrupt Mask" },
	{ name: "UART_INT_TX", displayName: "Transmit Interrupt Mask" },
	{ name: "UART_INT_RX", displayName: "Receive Interrupt Mask" },
]
let UART_CONFIG = [
	{ name: "UART_CONFIG_WLEN_MASK", displayName: "Mask for extracting wordlength" },
	{ name: "UART_CONFIG_WLEN_8", displayName: "8 bit data" },
	{ name: "UART_CONFIG_WLEN_7", displayName: "7 bit data" },
	{ name: "UART_CONFIG_WLEN_6", displayName: "6 bit data" },
	{ name: "UART_CONFIG_WLEN_5", displayName: "5 bit data" },
	{ name: "UART_CONFIG_STOP_MASK", displayName: "Mask for extracting stop bits" },
	{ name: "UART_CONFIG_STOP_ONE", displayName: "One stop bit" },
	{ name: "UART_CONFIG_STOP_TWO", displayName: "Two stop bits" },
	{ name: "UART_CONFIG_PAR_MASK", displayName: "Mask for extracting parity" },
	{ name: "UART_CONFIG_PAR_NONE", displayName: "No parity" },
	{ name: "UART_CONFIG_PAR_EVEN", displayName: "Even parity" },
	{ name: "UART_CONFIG_PAR_ODD", displayName: "Odd parity" },
	{ name: "UART_CONFIG_PAR_ONE", displayName: "Parity bit is one" },
	{ name: "UART_CONFIG_PAR_ZERO", displayName: "Parity bit is zero" },
]
let UART_DMA = [
	{ name: "UART_DMA_ERR_RXSTOP", displayName: "Stop DMA receive if UART error" },
	{ name: "UART_DMA_TX", displayName: "Enable DMA for transmit" },
	{ name: "UART_DMA_RX", displayName: "Enable DMA for receive" },
]
let UART_RXERROR = [
	{ name: "UART_RXERROR_OVERRUN", displayName: "RXERROR OVERRUN" },
	{ name: "UART_RXERROR_BREAK", displayName: "RXERROR BREAK" },
	{ name: "UART_RXERROR_PARITY", displayName: "RXERROR PARITY" },
	{ name: "UART_RXERROR_FRAMING", displayName: "RXERROR FRAMING" },
]
let UART_TXINT_MODE = [
	{ name: "UART_TXINT_MODE_FIFO", displayName: "trigger based on tx FIFOlevel" },
	{ name: "UART_TXINT_MODE_EOT", displayName: "trigger when transmitter idle" },
]
let UART_CLK_DIVIDER = [
	{ name: "UART_CLK_DIVIDER", displayName: "CLK DIVIDER" },
]
let UART_CLK_IRLPBAUD16 = [
	{ name: "UART_CLK_IRLPBAUD16", displayName: "CLK IRLPBAUD16" },
]
let UART_SIR_LOWPOWER = [
	{ name: "UART_SIR_LOWPOWER_DISABLE", displayName: "raw interrupt" },
	{ name: "UART_SIR_LOWPOWER_ENABLE", displayName: "masked interrupt" },
]
let UART_FIFO = [
	{ name: "UART_FIFO_TX1_8", displayName: "Transmit interrupt at 1/8 Full" },
	{ name: "UART_FIFO_TX2_8", displayName: "Transmit interrupt at 1/4 Full" },
	{ name: "UART_FIFO_TX4_8", displayName: "Transmit interrupt at 1/2 Full" },
	{ name: "UART_FIFO_TX6_8", displayName: "Transmit interrupt at 3/4 Full" },
	{ name: "UART_FIFO_TX7_8", displayName: "Transmit interrupt at 7/8 Full" },
]
let UART_CUSTOM_FIFO_LEVEL_KEY = [
	{ name: "UART_CUSTOM_FIFO_LEVEL_KEY", displayName: "CUSTOM FIFO LEVEL KEY" },
]
module.exports = {
	UART_TxFIFOLevelFine: UART_TxFIFOLevelFine,
	UART_RxFIFOLevelFine: UART_RxFIFOLevelFine,
	UART_INT: UART_INT,
	UART_CONFIG: UART_CONFIG,
	UART_DMA: UART_DMA,
	UART_RXERROR: UART_RXERROR,
	UART_TXINT_MODE: UART_TXINT_MODE,
	UART_CLK_DIVIDER: UART_CLK_DIVIDER,
	UART_CLK_IRLPBAUD16: UART_CLK_IRLPBAUD16,
	UART_SIR_LOWPOWER: UART_SIR_LOWPOWER,
	UART_FIFO: UART_FIFO,
	UART_CUSTOM_FIFO_LEVEL_KEY: UART_CUSTOM_FIFO_LEVEL_KEY,
}
