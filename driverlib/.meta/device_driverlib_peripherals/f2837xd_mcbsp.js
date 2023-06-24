let McBSP_RxSignExtensionMode = [
	{ name: "MCBSP_RIGHT_JUSTIFY_FILL_ZERO", displayName: "Right justify and" },
	{ name: "MCBSP_RIGHT_JUSTIFY_FILL_SIGN", displayName: "Right justified sign" },
	{ name: "MCBSP_LEFT_JUSTIFY_FILL_ZER0", displayName: "Left justifies LBS" },
]
let McBSP_ClockStopMode = [
	{ name: "MCBSP_CLOCK_MCBSP_MODE", displayName: "Disables clock stop mode." },
	{ name: "MCBSP_CLOCK_SPI_MODE_NO_DELAY", displayName: "Enables clock stop mode." },
	{ name: "MCBSP_CLOCK_SPI_MODE_DELAY", displayName: "Enables clock stop mode" },
]
let McBSP_RxInterruptSource = [
	{ name: "MCBSP_RX_ISR_SOURCE_SERIAL_WORD", displayName: "Interrupt when Rx is ready." },
	{ name: "MCBSP_RX_ISR_SOURCE_END_OF_BLOCK", displayName: "Interrupt at block end." },
	{ name: "MCBSP_RX_ISR_SOURCE_FRAME_SYNC", displayName: "Interrupt when" },
	{ name: "MCBSP_RX_ISR_SOURCE_SYNC_ERROR", displayName: "Interrupt on" },
]
let McBSP_EmulationMode = [
	{ name: "MCBSP_EMULATION_IMMEDIATE_STOP", displayName: "McBSP TX and RX stop when" },
	{ name: "MCBSP_EMULATION_SOFT_STOP", displayName: "McBSP TX stops after" },
	{ name: "MCBSP_EMULATION_FREE_RUN", displayName: "McBSP TX and RX run" },
]
let McBSP_TxInterruptSource = [
	{ name: "MCBSP_TX_ISR_SOURCE_TX_READY", displayName: "Interrupt when Tx Ready." },
	{ name: "MCBSP_TX_ISR_SOURCE_END_OF_BLOCK", displayName: "Interrupt at block end." },
	{ name: "MCBSP_TX_ISR_SOURCE_FRAME_SYNC", displayName: "Interrupt when frame" },
	{ name: "MCBSP_TX_ISR_SOURCE_SYNC_ERROR", displayName: "Interrupt on frame sync" },
]
let McBSP_DataPhaseFrame = [
	{ name: "MCBSP_PHASE_ONE_FRAME", displayName: "Single Phase." },
	{ name: "MCBSP_PHASE_TWO_FRAME", displayName: "Dual Phase." },
]
let McBSP_DataBitsPerWord = [
	{ name: "MCBSP_BITS_PER_WORD_8", displayName: "8 bit word." },
	{ name: "MCBSP_BITS_PER_WORD_12", displayName: "12 bit word." },
	{ name: "MCBSP_BITS_PER_WORD_16", displayName: "16 bit word." },
	{ name: "MCBSP_BITS_PER_WORD_20", displayName: "20 bit word." },
	{ name: "MCBSP_BITS_PER_WORD_24", displayName: "24 bit word." },
	{ name: "MCBSP_BITS_PER_WORD_32", displayName: "32 bit word." },
]
let McBSP_CompandingMode = [
	{ name: "MCBSP_COMPANDING_NONE", displayName: "Disables companding." },
	{ name: "MCBSP_COMPANDING_NONE_LSB_FIRST", displayName: "Disables companding and" },
	{ name: "MCBSP_COMPANDING_U_LAW_SET", displayName: "U-law companding." },
	{ name: "MCBSP_COMPANDING_A_LAW_SET", displayName: "A-law companding." },
]
let McBSP_DataDelayBits = [
	{ name: "MCBSP_DATA_DELAY_BIT_0", displayName: "O bit delay." },
	{ name: "MCBSP_DATA_DELAY_BIT_1", displayName: "1 bit delay." },
	{ name: "MCBSP_DATA_DELAY_BIT_2", displayName: "2 bit delay." },
]
let McBSP_SRGRxClockSource = [
	{ name: "MCBSP_SRG_RX_CLOCK_SOURCE_LSPCLK", displayName: "LSPCLK is SRG clock" },
	{ name: "MCBSP_SRG_RX_CLOCK_SOURCE_MCLKX_PIN", displayName: "MCLKx is SRG clock" },
]
let McBSP_SRGTxClockSource = [
	{ name: "MCBSP_SRG_TX_CLOCK_SOURCE_LSPCLK", displayName: "LSPCLK is SRG clock source." },
	{ name: "MCBSP_SRG_TX_CLOCK_SOURCE_MCLKR_PIN", displayName: "MCLKris SRG clock source." },
]
let McBSP_TxInternalFrameSyncSource = [
	{ name: "MCBSP_TX_INTERNAL_FRAME_SYNC_DATA", displayName: "Data is frame" },
	{ name: "MCBSP_TX_INTERNAL_FRAME_SYNC_SRG", displayName: "SRG is frame" },
]
let McBSP_MultichannelPartition = [
	{ name: "MCBSP_MULTICHANNEL_TWO_PARTITION", displayName: "Two partition." },
	{ name: "MCBSP_MULTICHANNEL_EIGHT_PARTITION", displayName: "Eight partition." },
]
let McBSP_PartitionBlock = [
	{ name: "MCBSP_PARTITION_BLOCK_0", displayName: "Partition block 0." },
	{ name: "MCBSP_PARTITION_BLOCK_1", displayName: "Partition block 1." },
	{ name: "MCBSP_PARTITION_BLOCK_2", displayName: "Partition block 2." },
	{ name: "MCBSP_PARTITION_BLOCK_3", displayName: "Partition block 3." },
	{ name: "MCBSP_PARTITION_BLOCK_4", displayName: "Partition block 4." },
	{ name: "MCBSP_PARTITION_BLOCK_5", displayName: "Partition block 5." },
	{ name: "MCBSP_PARTITION_BLOCK_6", displayName: "Partition block 6." },
	{ name: "MCBSP_PARTITION_BLOCK_7", displayName: "Partition block 7." },
]
let McBSP_RxChannelMode = [
	{ name: "MCBSP_ALL_RX_CHANNELS_ENABLED", displayName: "All Channels are enabled." },
	{ name: "MCBSP_RX_CHANNEL_SELECTION_ENABLED", displayName: "Selected channels enabled." },
]
let McBSP_TxChannelMode = [
	{ name: "MCBSP_ALL_TX_CHANNELS_ENABLED", displayName: "All Channels" },
	{ name: "MCBSP_TX_CHANNEL_SELECTION_ENABLED", displayName: "Selection Enabled." },
	{ name: "MCBSP_ENABLE_MASKED_TX_CHANNEL_SELECTION", displayName: "Masked Tx Channel." },
	{ name: "MCBSP_SYMMERTIC_RX_TX_SELECTION", displayName: "Symmetric Selection." },
]
let McBSP_TxFrameSyncSource = [
	{ name: "MCBSP_TX_EXTERNAL_FRAME_SYNC_SOURCE", displayName: "FSR pin supplies" },
	{ name: "MCBSP_TX_INTERNAL_FRAME_SYNC_SOURCE", displayName: "SRG supplies" },
]
let McBSP_RxFrameSyncSource = [
	{ name: "MCBSP_RX_EXTERNAL_FRAME_SYNC_SOURCE", displayName: "FSR pin supplies" },
	{ name: "MCBSP_RX_INTERNAL_FRAME_SYNC_SOURCE", displayName: "SRG supplies" },
]
let McBSP_TxClockSource = [
	{ name: "MCBSP_EXTERNAL_TX_CLOCK_SOURCE", displayName: "Clock source is external." },
	{ name: "MCBSP_INTERNAL_TX_CLOCK_SOURCE", displayName: "Clock source is internal." },
]
let McBSP_RxClockSource = [
	{ name: "MCBSP_EXTERNAL_RX_CLOCK_SOURCE", displayName: "Clock source is external." },
	{ name: "MCBSP_INTERNAL_RX_CLOCK_SOURCE", displayName: "Clock source is internal." },
]
let McBSP_TxFrameSyncPolarity = [
	{ name: "MCBSP_TX_FRAME_SYNC_POLARITY_HIGH", displayName: "Pulse active high." },
	{ name: "MCBSP_TX_FRAME_SYNC_POLARITY_LOW", displayName: "Pulse active low." },
]
let McBSP_RxFrameSyncPolarity = [
	{ name: "MCBSP_RX_FRAME_SYNC_POLARITY_HIGH", displayName: "Pulse active high." },
	{ name: "MCBSP_RX_FRAME_SYNC_POLARITY_LOW", displayName: "Pulse active low." },
]
let McBSP_TxClockPolarity = [
	{ name: "MCBSP_TX_POLARITY_RISING_EDGE", displayName: "TX data  on rising edge." },
	{ name: "MCBSP_TX_POLARITY_FALLING_EDGE", displayName: "TX data  on falling edge." },
]
let McBSP_RxClockPolarity = [
	{ name: "MCBSP_RX_POLARITY_FALLING_EDGE", displayName: "RX data sampled falling" },
	{ name: "MCBSP_RX_POLARITY_RISING_EDGE", displayName: "RX data sampled rising edge." },
]
let McBSP_CompandingType = [
	{ name: "MCBSP_COMPANDING_U_LAW", displayName: "U-law companding." },
	{ name: "MCBSP_COMPANDING_A_LAW", displayName: "A-law companding." },
]
let MCBSP_RX = [
	{ name: "MCBSP_RX_NO_ERROR", displayName: "No error." },
	{ name: "MCBSP_RX_BUFFER_ERROR", displayName: "Buffer Full." },
	{ name: "MCBSP_RX_FRAME_SYNC_ERROR", displayName: "Frame sync error." },
	{ name: "MCBSP_RX_BUFFER_FRAME_SYNC_ERROR", displayName: "Buffer and frame sync error." },
]
let MCBSP_TX = [
	{ name: "MCBSP_TX_NO_ERROR", displayName: "No error." },
	{ name: "MCBSP_TX_BUFFER_ERROR", displayName: "Buffer overrun." },
	{ name: "MCBSP_TX_FRAME_SYNC_ERROR", displayName: "Frame sync error." },
	{ name: "MCBSP_TX_BUFFER_FRAME_SYNC_ERROR", displayName: "Buffer and frame sync error." },
]
let MCBSP_ERROR = [
	{ name: "MCBSP_ERROR_EXCEEDED_CHANNELS", displayName: "Exceeded number of channels." },
	{ name: "MCBSP_ERROR_2_PARTITION_A", displayName: "Error in 2 partition A setup." },
	{ name: "MCBSP_ERROR_2_PARTITION_B", displayName: "Error in 2 partition B setup." },
	{ name: "MCBSP_ERROR_INVALID_MODE", displayName: "Invalid mode." },
]
module.exports = {
	McBSP_RxSignExtensionMode: McBSP_RxSignExtensionMode,
	McBSP_ClockStopMode: McBSP_ClockStopMode,
	McBSP_RxInterruptSource: McBSP_RxInterruptSource,
	McBSP_EmulationMode: McBSP_EmulationMode,
	McBSP_TxInterruptSource: McBSP_TxInterruptSource,
	McBSP_DataPhaseFrame: McBSP_DataPhaseFrame,
	McBSP_DataBitsPerWord: McBSP_DataBitsPerWord,
	McBSP_CompandingMode: McBSP_CompandingMode,
	McBSP_DataDelayBits: McBSP_DataDelayBits,
	McBSP_SRGRxClockSource: McBSP_SRGRxClockSource,
	McBSP_SRGTxClockSource: McBSP_SRGTxClockSource,
	McBSP_TxInternalFrameSyncSource: McBSP_TxInternalFrameSyncSource,
	McBSP_MultichannelPartition: McBSP_MultichannelPartition,
	McBSP_PartitionBlock: McBSP_PartitionBlock,
	McBSP_RxChannelMode: McBSP_RxChannelMode,
	McBSP_TxChannelMode: McBSP_TxChannelMode,
	McBSP_TxFrameSyncSource: McBSP_TxFrameSyncSource,
	McBSP_RxFrameSyncSource: McBSP_RxFrameSyncSource,
	McBSP_TxClockSource: McBSP_TxClockSource,
	McBSP_RxClockSource: McBSP_RxClockSource,
	McBSP_TxFrameSyncPolarity: McBSP_TxFrameSyncPolarity,
	McBSP_RxFrameSyncPolarity: McBSP_RxFrameSyncPolarity,
	McBSP_TxClockPolarity: McBSP_TxClockPolarity,
	McBSP_RxClockPolarity: McBSP_RxClockPolarity,
	McBSP_CompandingType: McBSP_CompandingType,
	MCBSP_RX: MCBSP_RX,
	MCBSP_TX: MCBSP_TX,
	MCBSP_ERROR: MCBSP_ERROR,
}
