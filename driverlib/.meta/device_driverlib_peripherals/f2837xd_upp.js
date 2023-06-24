let UPP_EmulationMode = [
	{ name: "UPP_EMULATIONMODE_HARDSTOP", displayName: "uPP stops immediately" },
	{ name: "UPP_EMULATIONMODE_RUNFREE", displayName: "uPP unaffected by suspend" },
	{ name: "UPP_EMULATIONMODE_SOFTSTOP", displayName: "uPP stops at DMA transaction finish" },
]
let UPP_OperationMode = [
	{ name: "UPP_RECEIVE_MODE", displayName: "uPP to be configured as Receiver" },
	{ name: "UPP_TRANSMIT_MODE", displayName: "uPP to be configured as Transmitter" },
]
let UPP_DataRate = [
	{ name: "UPP_DATA_RATE_SDR", displayName: "uPP to operate in Single Data Rate Mode" },
	{ name: "UPP_DATA_RATE_DDR", displayName: "uPP to operate in Double Data Rate Mode" },
]
let UPP_TxSDRInterleaveMode = [
	{ name: "UPP_TX_SDR_INTERLEAVE_DISABLE", displayName: "Interleaving disabled in Tx SDR" },
	{ name: "UPP_TX_SDR_INTERLEAVE_ENABLE", displayName: "Interleaving enabled in Tx SDR" },
]
let UPP_DDRDemuxMode = [
	{ name: "UPP_DDR_DEMUX_DISABLE", displayName: "Demultiplexing disabled in DDR mode" },
	{ name: "UPP_DDR_DEMUX_ENABLE", displayName: "Demultiplexing enabled in DDR mode" },
]
let UPP_SignalPolarity = [
	{ name: "UPP_SIGNAL_POLARITY_HIGH", displayName: "Signal polarity is active high" },
	{ name: "UPP_SIGNAL_POLARITY_LOW", displayName: "Signal polarity is active low" },
]
let UPP_SignalMode = [
	{ name: "UPP_SIGNAL_DISABLE", displayName: "Control Signal is disabled for uPP" },
	{ name: "UPP_SIGNAL_ENABLE", displayName: "Control Signal is enabled for uPP" },
]
let UPP_ClockPolarity = [
	{ name: "UPP_CLK_NOT_INVERTED", displayName: "uPP Clock is not inverted" },
	{ name: "UPP_CLK_INVERTED", displayName: "uPP clock is inverted" },
]
let UPP_TxIdleDataMode = [
	{ name: "UPP_TX_IDLE_DATA_IDLE", displayName: "Data lines will drive idle val" },
	{ name: "UPP_TX_IDLE_DATA_TRISTATED", displayName: "Data lines will be tristated" },
]
let UPP_DMAChannel = [
	{ name: "UPP_DMA_CHANNEL_I", displayName: "uPP internal DMA channel I" },
	{ name: "UPP_DMA_CHANNEL_Q", displayName: "uPP internal DMA channel Q" },
]
let UPP_ThresholdSize = [
	{ name: "UPP_THR_SIZE_64BYTE", displayName: "Tx threshold size is 64 bytes" },
	{ name: "UPP_THR_SIZE_128BYTE", displayName: "Tx threshold size is 128 bytes" },
	{ name: "UPP_THR_SIZE_256BYTE", displayName: "Tx threshold size is 256 bytes" },
]
let UPP_InputDelay = [
	{ name: "UPP_INPUT_DLY_4", displayName: "4 cycle delay for data & control pins" },
	{ name: "UPP_INPUT_DLY_6", displayName: "6 cycle delay for data & control pins" },
	{ name: "UPP_INPUT_DLY_9", displayName: "9 cycle delay for data & control pins" },
	{ name: "UPP_INPUT_DLY_14", displayName: "14 cycle delay for data & control pins" },
]
let UPP_DMA = [
	{ name: "UPP_DMA_TX_MSGRAM_STARTADDR", displayName: "DMA TX MSGRAM STARTADDR" },
	{ name: "UPP_DMA_RX_MSGRAM_STARTADDR", displayName: "DMA RX MSGRAM STARTADDR" },
]
let UPP_CPU = [
	{ name: "UPP_CPU_TX_MSGRAM_STARTADDR", displayName: "CPU TX MSGRAM STARTADDR" },
	{ name: "UPP_CPU_RX_MSGRAM_STARTADDR", displayName: "CPU RX MSGRAM STARTADDR" },
]
let UPP_32_CYCLE_NOP = [
	{ name: "UPP_32_CYCLE_NOP", displayName: "32 CYCLE NOP" },
]
let UPP_SOFT_FREE_M = [
	{ name: "UPP_SOFT_FREE_M", displayName: "SOFT FREE M" },
]
let UPP_SIGNAL_POLARITY_M = [
	{ name: "UPP_SIGNAL_POLARITY_M", displayName: "SIGNAL POLARITY M" },
]
let UPP_INT_M = [
	{ name: "UPP_INT_M", displayName: "INT M" },
]
let UPP_INT = [
	{ name: "UPP_INT_CHI_DMA_PROG_ERR", displayName: "DMA Channel I Programming Error" },
	{ name: "UPP_INT_CHI_UNDER_OVER_RUN", displayName: "DMA Channel I Underrun/Overrun" },
	{ name: "UPP_INT_CHI_END_OF_WINDOW", displayName: "DMA Channel I EndOfWindow Event" },
	{ name: "UPP_INT_CHI_END_OF_LINE", displayName: "DMA Channel I EndOfLine Event" },
	{ name: "UPP_INT_CHQ_DMA_PROG_ERR", displayName: "DMA Channel Q Programming Error" },
	{ name: "UPP_INT_CHQ_UNDER_OVER_RUN", displayName: "DMA Channel Q Underrun/Overrun" },
	{ name: "UPP_INT_CHQ_END_OF_WINDOW", displayName: "DMA Channel Q EndOfWindow Event" },
	{ name: "UPP_INT_CHQ_END_OF_LINE", displayName: "DMA Channel Q EndOfLine Event" },
]
module.exports = {
	UPP_EmulationMode: UPP_EmulationMode,
	UPP_OperationMode: UPP_OperationMode,
	UPP_DataRate: UPP_DataRate,
	UPP_TxSDRInterleaveMode: UPP_TxSDRInterleaveMode,
	UPP_DDRDemuxMode: UPP_DDRDemuxMode,
	UPP_SignalPolarity: UPP_SignalPolarity,
	UPP_SignalMode: UPP_SignalMode,
	UPP_ClockPolarity: UPP_ClockPolarity,
	UPP_TxIdleDataMode: UPP_TxIdleDataMode,
	UPP_DMAChannel: UPP_DMAChannel,
	UPP_ThresholdSize: UPP_ThresholdSize,
	UPP_InputDelay: UPP_InputDelay,
	UPP_DMA: UPP_DMA,
	UPP_CPU: UPP_CPU,
	UPP_32_CYCLE_NOP: UPP_32_CYCLE_NOP,
	UPP_SOFT_FREE_M: UPP_SOFT_FREE_M,
	UPP_SIGNAL_POLARITY_M: UPP_SIGNAL_POLARITY_M,
	UPP_INT_M: UPP_INT_M,
	UPP_INT: UPP_INT,
}
