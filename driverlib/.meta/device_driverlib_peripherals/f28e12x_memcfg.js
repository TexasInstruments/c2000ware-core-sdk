let MemCfg_TestMode = [
	{ name: "MEMCFG_TEST_FUNCTIONAL", displayName: "Functional mode. Test mode is disabled." },
	{ name: "MEMCFG_TEST_WRITE_DATA", displayName: "Writes allowed to data only" },
	{ name: "MEMCFG_TEST_WRITE_PARITY", displayName: "Writes allowed to Parity only (for DxRAM/MxRAM/GSxRAM/PIEVECT RAM)" },
	{ name: "MEMCFG_TEST_FUNC_DIAG", displayName: "Diagnostic mode, similar to functional mode but NMI is not generated." },
]
let MEMCFG_SECT = [
	{ name: "MEMCFG_SECT_M0", displayName: "M0 RAM" },
	{ name: "MEMCFG_SECT_M1", displayName: "M1 RAM" },
	{ name: "MEMCFG_SECT_DX_ALL", displayName: "All M and D RAM" },
	{ name: "MEMCFG_SECT_PIEVECT", displayName: "PIEVECT RAM" },
	{ name: "MEMCFG_SECT_GS0", displayName: "GS0 RAM" },
	{ name: "MEMCFG_SECT_GSX_ALL", displayName: "All GS RAM" },
	{ name: "MEMCFG_SECT_ROMBOOT_ROMSECURE", displayName: "BOOT ROM and Secure ROM" },
	{ name: "MEMCFG_SECT_ROM_ALL", displayName: "All ROMs" },
	{ name: "MEMCFG_SECT_ALL", displayName: "All configurable RAM" },
]
let MEMCFG_CERR = [
	{ name: "MEMCFG_CERR_CPUREAD", displayName: "Correctable CPU read error" },
	{ name: "MEMCFG_CERR_DMAREAD", displayName: "Correctable DMA read error" },
]
let MEMCFG_UCERR = [
	{ name: "MEMCFG_UCERR_CPUREAD", displayName: "Uncorrectable CPU read error" },
	{ name: "MEMCFG_UCERR_DMAREAD", displayName: "Uncorrectable DMA read error" },
]
let MEMCFG_DIAGERR = [
	{ name: "MEMCFG_DIAGERR_UNCORR", displayName: "Uncorr error in diag/test mode" },
	{ name: "MEMCFG_DIAGERR_CORR", displayName: "Corr error in diag/test mode" },
]
module.exports = {
	MemCfg_TestMode: MemCfg_TestMode,
	MEMCFG_SECT: MEMCFG_SECT,
	MEMCFG_CERR: MEMCFG_CERR,
	MEMCFG_UCERR: MEMCFG_UCERR,
	MEMCFG_DIAGERR: MEMCFG_DIAGERR,
}
