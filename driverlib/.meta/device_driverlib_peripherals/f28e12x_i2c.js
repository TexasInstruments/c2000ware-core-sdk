let I2C_InterruptSource = [
	{ name: "I2C_INTSRC_NONE", displayName: "No interrupt pending" },
	{ name: "I2C_INTSRC_ARB_LOST", displayName: "Arbitration-lost interrupt" },
	{ name: "I2C_INTSRC_NO_ACK", displayName: "NACK interrupt" },
	{ name: "I2C_INTSRC_REG_ACCESS_RDY", displayName: "Register-access-ready interrupt" },
	{ name: "I2C_INTSRC_RX_DATA_RDY", displayName: "Receive-data-ready interrupt" },
	{ name: "I2C_INTSRC_TX_DATA_RDY", displayName: "Transmit-data-ready interrupt" },
	{ name: "I2C_INTSRC_STOP_CONDITION", displayName: "Stop condition detected" },
	{ name: "I2C_INTSRC_ADDR_TARGET", displayName: "Addressed as target interrupt", legacyNames: ["I2C_INTSRC_ADDR_SLAVE"]},
	{ name: "I2C_INTSRC_SCL_ECS", displayName: "Extended Clock Streching interrupt" },
]
let I2C_TxFIFOLevel = [
	{ name: "I2C_FIFO_TXEMPTY", displayName: "Transmit FIFO empty" },
	{ name: "I2C_FIFO_TX0", displayName: "Transmit FIFO empty" },
	{ name: "I2C_FIFO_TX1", displayName: "Transmit FIFO 1/16 full" },
	{ name: "I2C_FIFO_TX2", displayName: "Transmit FIFO 2/16 full" },
	{ name: "I2C_FIFO_TX3", displayName: "Transmit FIFO 3/16 full" },
	{ name: "I2C_FIFO_TX4", displayName: "Transmit FIFO 4/16 full" },
	{ name: "I2C_FIFO_TX5", displayName: "Transmit FIFO 5/16 full" },
	{ name: "I2C_FIFO_TX6", displayName: "Transmit FIFO 6/16 full" },
	{ name: "I2C_FIFO_TX7", displayName: "Transmit FIFO 7/16 full" },
	{ name: "I2C_FIFO_TX8", displayName: "Transmit FIFO 8/16 full" },
	{ name: "I2C_FIFO_TX9", displayName: "Transmit FIFO 9/16 full" },
	{ name: "I2C_FIFO_TX10", displayName: "Transmit FIFO 10/16 full" },
	{ name: "I2C_FIFO_TX11", displayName: "Transmit FIFO 11/16 full" },
	{ name: "I2C_FIFO_TX12", displayName: "Transmit FIFO 12/16 full" },
	{ name: "I2C_FIFO_TX13", displayName: "Transmit FIFO 13/16 full" },
	{ name: "I2C_FIFO_TX14", displayName: "Transmit FIFO 14/16 full" },
	{ name: "I2C_FIFO_TX15", displayName: "Transmit FIFO 15/16 full" },
	{ name: "I2C_FIFO_TX16", displayName: "Transmit FIFO full" },
	{ name: "I2C_FIFO_TXFULL", displayName: "Transmit FIFO full" },
]
let I2C_RxFIFOLevel = [
	{ name: "I2C_FIFO_RXEMPTY", displayName: "Receive FIFO empty" },
	{ name: "I2C_FIFO_RX0", displayName: "Receive FIFO empty" },
	{ name: "I2C_FIFO_RX1", displayName: "Receive FIFO 1/16 full" },
	{ name: "I2C_FIFO_RX2", displayName: "Receive FIFO 2/16 full" },
	{ name: "I2C_FIFO_RX3", displayName: "Receive FIFO 3/16 full" },
	{ name: "I2C_FIFO_RX4", displayName: "Receive FIFO 4/16 full" },
	{ name: "I2C_FIFO_RX5", displayName: "Receive FIFO 5/16 full" },
	{ name: "I2C_FIFO_RX6", displayName: "Receive FIFO 6/16 full" },
	{ name: "I2C_FIFO_RX7", displayName: "Receive FIFO 7/16 full" },
	{ name: "I2C_FIFO_RX8", displayName: "Receive FIFO 8/16 full" },
	{ name: "I2C_FIFO_RX9", displayName: "Receive FIFO 9/16 full" },
	{ name: "I2C_FIFO_RX10", displayName: "Receive FIFO 10/16 full" },
	{ name: "I2C_FIFO_RX11", displayName: "Receive FIFO 11/16 full" },
	{ name: "I2C_FIFO_RX12", displayName: "Receive FIFO 12/16 full" },
	{ name: "I2C_FIFO_RX13", displayName: "Receive FIFO 13/16 full" },
	{ name: "I2C_FIFO_RX14", displayName: "Receive FIFO 14/16 full" },
	{ name: "I2C_FIFO_RX15", displayName: "Receive FIFO 15/16 full" },
	{ name: "I2C_FIFO_RX16", displayName: "Receive FIFO full" },
	{ name: "I2C_FIFO_RXFULL", displayName: "Receive FIFO full" },
]
let I2C_BitCount = [
	{ name: "I2C_BITCOUNT_1", displayName: "1 bit per data byte" },
	{ name: "I2C_BITCOUNT_2", displayName: "2 bits per data byte" },
	{ name: "I2C_BITCOUNT_3", displayName: "3 bits per data byte" },
	{ name: "I2C_BITCOUNT_4", displayName: "4 bits per data byte" },
	{ name: "I2C_BITCOUNT_5", displayName: "5 bits per data byte" },
	{ name: "I2C_BITCOUNT_6", displayName: "6 bits per data byte" },
	{ name: "I2C_BITCOUNT_7", displayName: "7 bits per data byte" },
	{ name: "I2C_BITCOUNT_8", displayName: "8 bits per data byte" },
]
let I2C_AddressMode = [
	{ name: "I2C_ADDR_MODE_7BITS", displayName: "7-bit address" },
	{ name: "I2C_ADDR_MODE_10BITS", displayName: "10-bit address" },
]
let I2C_ExtendedMode = [
	{ name: "I2C_EADDR_MODE_BC", displayName: "Backward compatibility" },
	{ name: "I2C_EADDR_MODE_FWD", displayName: "Forward compatibility" },
]
let I2C_EmulationMode = [
	{ name: "I2C_EMULATION_STOP_SCL_LOW", displayName: "If SCL is low, keep it low. If high, stop when it goes low again." },
	{ name: "I2C_EMULATION_FREE_RUN", displayName: "Continue I2C operation regardless" },
]
let I2C_DutyCycle = [
	{ name: "I2C_DUTYCYCLE_33", displayName: "Clock duty cycle is 33%" },
	{ name: "I2C_DUTYCYCLE_50", displayName: "Clock duty cycle is 55%" },
]
let I2C_STS = [
	{ name: "I2C_STS_ARB_LOST", displayName: "Arbitration-lost" },
	{ name: "I2C_STS_NO_ACK", displayName: "No-acknowledgment (NACK)" },
	{ name: "I2C_STS_REG_ACCESS_RDY", displayName: "Register-access-ready (ARDY)" },
	{ name: "I2C_STS_RX_DATA_RDY", displayName: "Receive-data-ready" },
	{ name: "I2C_STS_TX_DATA_RDY", displayName: "Transmit-data-ready" },
	{ name: "I2C_STS_STOP_CONDITION", displayName: "Stop condition detected" },
	{ name: "I2C_STS_BYTE_SENT", displayName: "Byte transmit complete" },
	{ name: "I2C_STS_ADDR_ZERO", displayName: "Address of all zeros detected" },
	{ name: "I2C_STS_ADDR_TARGET", displayName: "Addressed as target", legacyNames: ["I2C_STS_ADDR_SLAVE"]},
	{ name: "I2C_STS_TX_EMPTY", displayName: "Transmit shift register empty" },
	{ name: "I2C_STS_RX_FULL", displayName: "Receive shift register full" },
	{ name: "I2C_STS_BUS_BUSY", displayName: "Bus busy, wait for STOP or reset" },
	{ name: "I2C_STS_NACK_SENT", displayName: "NACK was sent" },
	{ name: "I2C_STS_TARGET_DIR", displayName: "Addressed as target transmitter", legacyNames: ["I2C_STS_SLAVE_DIR"]},
	{ name: "I2C_STS_SCL_ECS", displayName: "SCL Auto Clock Stretch Status" },
]
let I2C_EMDR_SCLKEY = [
	{ name: "I2C_EMDR_SCLKEY_ENABLE", displayName: "EMDR SCLKEY ENABLE" },
	{ name: "I2C_EMDR_SCLKEY_DISABLE", displayName: "EMDR SCLKEY DISABLE" },
]
module.exports = {
	I2C_InterruptSource: I2C_InterruptSource,
	I2C_TxFIFOLevel: I2C_TxFIFOLevel,
	I2C_RxFIFOLevel: I2C_RxFIFOLevel,
	I2C_BitCount: I2C_BitCount,
	I2C_AddressMode: I2C_AddressMode,
	I2C_ExtendedMode: I2C_ExtendedMode,
	I2C_EmulationMode: I2C_EmulationMode,
	I2C_DutyCycle: I2C_DutyCycle,
	I2C_STS: I2C_STS,
	I2C_EMDR_SCLKEY: I2C_EMDR_SCLKEY,
}
