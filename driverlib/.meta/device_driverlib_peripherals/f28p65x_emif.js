let EMIF_AsyncCSOffset = [
	{ name: "EMIF_ASYNC_CS2_OFFSET", displayName: "Async chip select 2 offset" },
	{ name: "EMIF_ASYNC_CS3_OFFSET", displayName: "Async chip select 3 offset" },
	{ name: "EMIF_ASYNC_CS4_OFFSET", displayName: "Async chip select 4 offset" },
]
let EMIF_AsyncDataWidth = [
	{ name: "EMIF_ASYNC_DATA_WIDTH_8", displayName: "ASRAM/FLASH with 8 bit data bus" },
	{ name: "EMIF_ASYNC_DATA_WIDTH_16", displayName: "ASRAM/FLASH with 16 bit data bus" },
	{ name: "EMIF_ASYNC_DATA_WIDTH_32", displayName: "ASRAM/FLASH with 32 bit data bus" },
]
let EMIF_AsyncMode = [
	{ name: "EMIF_ASYNC_STROBE_MODE", displayName: "Enables ASRAM/FLASH strobe mode" },
	{ name: "EMIF_ASYNC_NORMAL_MODE", displayName: "Disables ASRAM/FLASH strobe mode" },
]
let EMIF_AsyncWaitPolarity = [
	{ name: "EMIF_ASYNC_WAIT_POLARITY_LOW", displayName: "EMxWAIT pin polarity is low" },
	{ name: "EMIF_ASYNC_WAIT_POLARITY_HIGH", displayName: "EMxWAIT pin polarity is high" },
]
let EMIF_ControllerSelect = [
	{ name: "EMIF_CONTROLLER_CPU1_NG", displayName: "CPU1 is controller but not grabbed", legacyNames: ["EMIF_MASTER_CPU1_NG"]},
	{ name: "EMIF_CONTROLLER_CPU1_G", displayName: "CPU1 is controller & grabbed", legacyNames: ["EMIF_MASTER_CPU1_G"]},
	{ name: "EMIF_CONTROLLER_CPU2_G", displayName: "CPU2 is controller & grabbed", legacyNames: ["EMIF_MASTER_CPU2_G"]},
	{ name: "EMIF_CONTROLLER_CPU1_NG2", displayName: "CPU1 is controller but not grabbed", legacyNames: ["EMIF_MASTER_CPU1_NG2"]},
]
let EMIF_SyncNarrowMode = [
	{ name: "EMIF_SYNC_NARROW_MODE_TRUE", displayName: "MemBusWidth=SystemBusWidth/2" },
	{ name: "EMIF_SYNC_NARROW_MODE_FALSE", displayName: "MemBusWidth=SystemBusWidth" },
]
let EMIF_SyncBank = [
	{ name: "EMIF_SYNC_BANK_1", displayName: "1 Bank SDRAM device" },
	{ name: "EMIF_SYNC_BANK_2", displayName: "2 Bank SDRAM device" },
	{ name: "EMIF_SYNC_BANK_4", displayName: "4 Bank SDRAM device" },
]
let EMIF_SyncCASLatency = [
	{ name: "EMIF_SYNC_CAS_LAT_2", displayName: "SDRAM with CAS Latency 2" },
	{ name: "EMIF_SYNC_CAS_LAT_3", displayName: "SDRAM with CAS Latency 3" },
]
let EMIF_SyncPageSize = [
	{ name: "EMIF_SYNC_COLUMN_WIDTH_8", displayName: "256-word pages in SDRAM" },
	{ name: "EMIF_SYNC_COLUMN_WIDTH_9", displayName: "512-word pages in SDRAM" },
	{ name: "EMIF_SYNC_COLUMN_WIDTH_10", displayName: "1024-word pages in SDRAM" },
	{ name: "EMIF_SYNC_COLUMN_WIDTH_11", displayName: "2048-word pages in SDRAM" },
]
let EMIF_ACCPROT0 = [
	{ name: "EMIF_ACCPROT0_FETCHPROT", displayName: "This flag is used to specify whether CPU fetches are allowed/blocked  for EMIF." },
	{ name: "EMIF_ACCPROT0_CPUWRPROT", displayName: "This flag is used to specify whether CPU writes are allowed/blocked  for EMIF." },
	{ name: "EMIF_ACCPROT0_DMAWRPROT", displayName: "This flag is used to specify whether DMA writes are allowed/blocked  for EMIF. It is valid only for EMIF1 instance." },
]
let EMIF_ACCPROT0_MASK_EMIF1 = [
	{ name: "EMIF_ACCPROT0_MASK_EMIF1", displayName: "ACCPROT0 MASK EMIF1" },
]
let EMIF_ASYNC_CS_CR_MASK = [
	{ name: "EMIF_ASYNC_CS_CR_MASK", displayName: "ASYNC CS CR MASK" },
]
let EMIF_ASYNC_INT_MASK = [
	{ name: "EMIF_ASYNC_INT_MASK", displayName: "ASYNC INT MASK" },
]
let EMIF_ASYNC_INT = [
	{ name: "EMIF_ASYNC_INT_AT", displayName: "This flag is used to allow/block EMIF to generate Masked Asynchronous  Timeout interrupt." },
	{ name: "EMIF_ASYNC_INT_LT", displayName: "This flag is used to allow/block EMIF to generate Masked Line Trap  interrupt." },
	{ name: "EMIF_ASYNC_INT_WR", displayName: "This flag is used to allow/block EMIF to generate Masked Wait Rise  interrupt." },
]
let EMIF_MSEL_KEY = [
	{ name: "EMIF_MSEL_KEY", displayName: "MSEL KEY" },
]
let EMIF_SYNC_SDRAM_CR_MASK = [
	{ name: "EMIF_SYNC_SDRAM_CR_MASK", displayName: "SYNC SDRAM CR MASK" },
]
let EMIF_SYNC_SDRAM_TR_MASK = [
	{ name: "EMIF_SYNC_SDRAM_TR_MASK", displayName: "SYNC SDRAM TR MASK" },
]
module.exports = {
	EMIF_AsyncCSOffset: EMIF_AsyncCSOffset,
	EMIF_AsyncDataWidth: EMIF_AsyncDataWidth,
	EMIF_AsyncMode: EMIF_AsyncMode,
	EMIF_AsyncWaitPolarity: EMIF_AsyncWaitPolarity,
	EMIF_ControllerSelect: EMIF_ControllerSelect,
	EMIF_SyncNarrowMode: EMIF_SyncNarrowMode,
	EMIF_SyncBank: EMIF_SyncBank,
	EMIF_SyncCASLatency: EMIF_SyncCASLatency,
	EMIF_SyncPageSize: EMIF_SyncPageSize,
	EMIF_ACCPROT0: EMIF_ACCPROT0,
	EMIF_ACCPROT0_MASK_EMIF1: EMIF_ACCPROT0_MASK_EMIF1,
	EMIF_ASYNC_CS_CR_MASK: EMIF_ASYNC_CS_CR_MASK,
	EMIF_ASYNC_INT_MASK: EMIF_ASYNC_INT_MASK,
	EMIF_ASYNC_INT: EMIF_ASYNC_INT,
	EMIF_MSEL_KEY: EMIF_MSEL_KEY,
	EMIF_SYNC_SDRAM_CR_MASK: EMIF_SYNC_SDRAM_CR_MASK,
	EMIF_SYNC_SDRAM_TR_MASK: EMIF_SYNC_SDRAM_TR_MASK,
}
