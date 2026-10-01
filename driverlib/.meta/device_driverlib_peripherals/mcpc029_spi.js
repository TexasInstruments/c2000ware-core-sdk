let SPI_TransferProtocol = [
	{ name: "SPI_PROT_POL0PHA0", displayName: "Mode 0. Polarity 0, phase 0. Rising edge without delay." },
	{ name: "SPI_PROT_POL0PHA1", displayName: "Mode 1. Polarity 0, phase 1. Rising edge with delay." },
	{ name: "SPI_PROT_POL1PHA0", displayName: "Mode 2. Polarity 1, phase 0. Falling edge without delay." },
	{ name: "SPI_PROT_POL1PHA1", displayName: "Mode 3. Polarity 1, phase 1. Falling edge with delay." },
]
let SPI_Mode = [
	{ name: "SPI_MODE_PERIPHERAL", displayName: "SPI peripheral", legacyNames: ["SPI_MODE_SLAVE"]},
	{ name: "SPI_MODE_CONTROLLER", displayName: "SPI controller", legacyNames: ["SPI_MODE_MASTER"]},
	{ name: "SPI_MODE_PERIPHERAL_OD", displayName: "SPI peripheral w/ output disabled", legacyNames: ["SPI_MODE_SLAVE_OD"]},
	{ name: "SPI_MODE_CONTROLLER_OD", displayName: "SPI controller w/ output disabled", legacyNames: ["SPI_MODE_MASTER_OD"]},
]
let SPI_TxFIFOLevel = [
	{ name: "SPI_FIFO_TXEMPTY", displayName: "Transmit FIFO empty" },
	{ name: "SPI_FIFO_TX0", displayName: "Transmit FIFO empty" },
	{ name: "SPI_FIFO_TX1", displayName: "Transmit FIFO 1/16 full" },
	{ name: "SPI_FIFO_TX2", displayName: "Transmit FIFO 2/16 full" },
	{ name: "SPI_FIFO_TX3", displayName: "Transmit FIFO 3/16 full" },
	{ name: "SPI_FIFO_TX4", displayName: "Transmit FIFO 4/16 full" },
	{ name: "SPI_FIFO_TX5", displayName: "Transmit FIFO 5/16 full" },
	{ name: "SPI_FIFO_TX6", displayName: "Transmit FIFO 6/16 full" },
	{ name: "SPI_FIFO_TX7", displayName: "Transmit FIFO 7/16 full" },
	{ name: "SPI_FIFO_TX8", displayName: "Transmit FIFO 8/16 full" },
	{ name: "SPI_FIFO_TX9", displayName: "Transmit FIFO 9/16 full" },
	{ name: "SPI_FIFO_TX10", displayName: "Transmit FIFO 10/16 full" },
	{ name: "SPI_FIFO_TX11", displayName: "Transmit FIFO 11/16 full" },
	{ name: "SPI_FIFO_TX12", displayName: "Transmit FIFO 12/16 full" },
	{ name: "SPI_FIFO_TX13", displayName: "Transmit FIFO 13/16 full" },
	{ name: "SPI_FIFO_TX14", displayName: "Transmit FIFO 14/16 full" },
	{ name: "SPI_FIFO_TX15", displayName: "Transmit FIFO 15/16 full" },
	{ name: "SPI_FIFO_TX16", displayName: "Transmit FIFO full" },
	{ name: "SPI_FIFO_TXFULL", displayName: "Transmit FIFO full" },
]
let SPI_RxFIFOLevel = [
	{ name: "SPI_FIFO_RXEMPTY", displayName: "Receive FIFO empty" },
	{ name: "SPI_FIFO_RX0", displayName: "Receive FIFO empty" },
	{ name: "SPI_FIFO_RX1", displayName: "Receive FIFO 1/16 full" },
	{ name: "SPI_FIFO_RX2", displayName: "Receive FIFO 2/16 full" },
	{ name: "SPI_FIFO_RX3", displayName: "Receive FIFO 3/16 full" },
	{ name: "SPI_FIFO_RX4", displayName: "Receive FIFO 4/16 full" },
	{ name: "SPI_FIFO_RX5", displayName: "Receive FIFO 5/16 full" },
	{ name: "SPI_FIFO_RX6", displayName: "Receive FIFO 6/16 full" },
	{ name: "SPI_FIFO_RX7", displayName: "Receive FIFO 7/16 full" },
	{ name: "SPI_FIFO_RX8", displayName: "Receive FIFO 8/16 full" },
	{ name: "SPI_FIFO_RX9", displayName: "Receive FIFO 9/16 full" },
	{ name: "SPI_FIFO_RX10", displayName: "Receive FIFO 10/16 full" },
	{ name: "SPI_FIFO_RX11", displayName: "Receive FIFO 11/16 full" },
	{ name: "SPI_FIFO_RX12", displayName: "Receive FIFO 12/16 full" },
	{ name: "SPI_FIFO_RX13", displayName: "Receive FIFO 13/16 full" },
	{ name: "SPI_FIFO_RX14", displayName: "Receive FIFO 14/16 full" },
	{ name: "SPI_FIFO_RX15", displayName: "Receive FIFO 15/16 full" },
	{ name: "SPI_FIFO_RX16", displayName: "Receive FIFO full" },
	{ name: "SPI_FIFO_RXFULL", displayName: "Receive FIFO full" },
	{ name: "SPI_FIFO_RXDEFAULT", displayName: "To prevent interrupt at reset" },
]
let SPI_EmulationMode = [
	{ name: "SPI_EMULATION_STOP_MIDWAY", displayName: "Transmission stops after midway in the bit stream" },
	{ name: "SPI_EMULATION_FREE_RUN", displayName: "Continue SPI operation regardless" },
	{ name: "SPI_EMULATION_STOP_AFTER_TRANSMIT", displayName: "Transmission will stop after a started transmission completes" },
]
let SPI_PTEPolarity = [
	{ name: "SPI_PTE_ACTIVE_LOW", displayName: "SPIPTE is active low (normal)", legacyNames: ["SPI_STE_ACTIVE_LOW"]},
	{ name: "SPI_PTE_ACTIVE_HIGH", displayName: "SPIPTE is active high (inverted)", legacyNames: ["SPI_STE_ACTIVE_HIGH"]},
]
let SPI_endianess = [
	{ name: "SPI_DATA_LITTLE_ENDIAN", displayName: "LITTLE ENDIAN" },
	{ name: "SPI_DATA_BIG_ENDIAN", displayName: "BIG ENDIAN" },
]
let SPI_INT = [
	{ name: "SPI_INT_RX_OVERRUN", displayName: "Receive overrun interrupt" },
	{ name: "SPI_INT_RX_DATA_TX_EMPTY", displayName: "Data received, transmit empty" },
	{ name: "SPI_INT_RXFF", displayName: "RX FIFO level interrupt" },
	{ name: "SPI_INT_TXFF", displayName: "TX FIFO level interrupt" },
	{ name: "SPI_INT_RXFF_OVERFLOW", displayName: "RX FIFO overflow" },
]
module.exports = {
	SPI_TransferProtocol: SPI_TransferProtocol,
	SPI_Mode: SPI_Mode,
	SPI_TxFIFOLevel: SPI_TxFIFOLevel,
	SPI_RxFIFOLevel: SPI_RxFIFOLevel,
	SPI_EmulationMode: SPI_EmulationMode,
	SPI_PTEPolarity: SPI_PTEPolarity,
	SPI_endianess: SPI_endianess,
	SPI_INT: SPI_INT,
}
