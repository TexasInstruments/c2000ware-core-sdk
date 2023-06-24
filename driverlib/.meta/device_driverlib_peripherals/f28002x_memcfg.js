let MemCfg_TestMode = [
	{ name: "MEMCFG_TEST_FUNCTIONAL", displayName: "Functional mode. Test mode is disabled." },
	{ name: "MEMCFG_TEST_WRITE_DATA", displayName: "Writes allowed to data only" },
	{ name: "MEMCFG_TEST_WRITE_ECC", displayName: "Writes allowed to ECC only (for DxRAM/MxRAM)" },
	{ name: "MEMCFG_TEST_WRITE_PARITY", displayName: "Writes allowed to parity only (for LSxRAM and GSxRAM)" },
]
let MEMCFG_SECT = [
	{ name: "MEMCFG_SECT_M0", displayName: "M0 RAM" },
	{ name: "MEMCFG_SECT_M1", displayName: "M1 RAM" },
	{ name: "MEMCFG_SECT_DX_ALL", displayName: "All M and D RAM" },
	{ name: "MEMCFG_SECT_LS4", displayName: "LS4 RAM" },
	{ name: "MEMCFG_SECT_LS5", displayName: "LS5 RAM" },
	{ name: "MEMCFG_SECT_LS6", displayName: "LS6 RAM" },
	{ name: "MEMCFG_SECT_LS7", displayName: "LS7 RAM" },
	{ name: "MEMCFG_SECT_LSX_ALL", displayName: "All LS RAM" },
	{ name: "MEMCFG_SECT_GS0", displayName: "GS0 RAM" },
	{ name: "MEMCFG_SECT_GSX_ALL", displayName: "All GS RAM" },
	{ name: "MEMCFG_SECT_ROMBOOT", displayName: "BOOT ROM" },
	{ name: "MEMCFG_SECT_ROMSECURE", displayName: "Secure ROM" },
	{ name: "MEMCFG_SECT_ROM_ALL", displayName: "All ROMs" },
	{ name: "MEMCFG_SECT_ALL", displayName: "All configurable RAM" },
]
let MEMCFG_PROT = [
	{ name: "MEMCFG_PROT_ALLOWCPUFETCH", displayName: "CPU fetch allowed" },
	{ name: "MEMCFG_PROT_BLOCKCPUFETCH", displayName: "CPU fetch blocked" },
	{ name: "MEMCFG_PROT_ALLOWCPUWRITE", displayName: "CPU write allowed" },
	{ name: "MEMCFG_PROT_BLOCKCPUWRITE", displayName: "CPU write blocked" },
	{ name: "MEMCFG_PROT_ALLOWDMAWRITE", displayName: "DMA write allowed (GSxRAM)" },
	{ name: "MEMCFG_PROT_BLOCKDMAWRITE", displayName: "DMA write blocked (GSxRAM)" },
	{ name: "MEMCFG_PROT_ALLOWHICWRITE", displayName: "HIC write allowed (GSxRAM)" },
	{ name: "MEMCFG_PROT_BLOCKHICWRITE", displayName: "HIC write blocked (GSxRAM)" },
]
let MEMCFG_NMVIOL = [
	{ name: "MEMCFG_NMVIOL_CPUREAD", displayName: "Non-controller CPU read access" },
	{ name: "MEMCFG_NMVIOL_CPUWRITE", displayName: "Non-controller CPU write access" },
	{ name: "MEMCFG_NMVIOL_CPUFETCH", displayName: "Non-controller CPU fetch access" },
	{ name: "MEMCFG_NMVIOL_DMAWRITE", displayName: "Non-controller DMA write access" },
	{ name: "MEMCFG_NMVIOL_DMAREAD", displayName: "Non-controller DMA read access" },
	{ name: "MEMCFG_NMVIOL_HICREAD", displayName: "Non-controller HIC read access" },
	{ name: "MEMCFG_NMVIOL_HICWRITE", displayName: "Non-controller HIC write access" },
]
let MEMCFG_MVIOL = [
	{ name: "MEMCFG_MVIOL_CPUFETCH", displayName: "Controller CPU fetch access" },
	{ name: "MEMCFG_MVIOL_CPUWRITE", displayName: "Controller CPU write access" },
	{ name: "MEMCFG_MVIOL_DMAWRITE", displayName: "Controller DMA write access" },
	{ name: "MEMCFG_MVIOL_HICWRITE", displayName: "Controller HIC write access" },
]
let MEMCFG_CERR_CPUREAD = [
	{ name: "MEMCFG_CERR_CPUREAD", displayName: "Correctable CPU read error" },
]
let MEMCFG_UCERR = [
	{ name: "MEMCFG_UCERR_CPUREAD", displayName: "Uncorrectable CPU read error" },
	{ name: "MEMCFG_UCERR_DMAREAD", displayName: "Uncorrectable DMA read error" },
	{ name: "MEMCFG_UCERR_HICREAD", displayName: "Uncorrectable HIC read error" },
]
module.exports = {
	MemCfg_TestMode: MemCfg_TestMode,
	MEMCFG_SECT: MEMCFG_SECT,
	MEMCFG_PROT: MEMCFG_PROT,
	MEMCFG_NMVIOL: MEMCFG_NMVIOL,
	MEMCFG_MVIOL: MEMCFG_MVIOL,
	MEMCFG_CERR_CPUREAD: MEMCFG_CERR_CPUREAD,
	MEMCFG_UCERR: MEMCFG_UCERR,
}
