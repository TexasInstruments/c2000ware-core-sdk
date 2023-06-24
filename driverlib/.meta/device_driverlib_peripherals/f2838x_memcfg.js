let MemCfg_CLAMemoryType = [
	{ name: "MEMCFG_CLA_MEM_DATA", displayName: "Section is CLA data memory" },
	{ name: "MEMCFG_CLA_MEM_PROGRAM", displayName: "Section is CLA program memory" },
]
let MemCfg_LSRAMControllerSel = [
	{ name: "MEMCFG_LSRAMCONTROLLER_CPU_ONLY", displayName: "CPU is the owner of the section", legacyNames: ["MEMCFG_LSRAMMASTER_CPU_ONLY"]},
	{ name: "MEMCFG_LSRAMCONTROLLER_CPU_CLA1", displayName: "CPU and CLA1 share this section", legacyNames: ["MEMCFG_LSRAMMASTER_CPU_CLA1"]},
]
let MemCfg_GSRAMControllerSel = [
	{ name: "MEMCFG_GSRAMCONTROLLER_CPU1", displayName: "CPU1 is controller of the section", legacyNames: ["MEMCFG_GSRAMMASTER_CPU1"]},
	{ name: "MEMCFG_GSRAMCONTROLLER_CPU2", displayName: "CPU2 is controller of the section", legacyNames: ["MEMCFG_GSRAMMASTER_CPU2"]},
]
let MemCfg_TestMode = [
	{ name: "MEMCFG_TEST_FUNCTIONAL", displayName: "Functional mode. Test mode is disabled." },
	{ name: "MEMCFG_TEST_WRITE_DATA", displayName: "Writes allowed to data only" },
	{ name: "MEMCFG_TEST_WRITE_ECC", displayName: "Writes allowed to ECC only (for DxRAM & LSxRAM)" },
	{ name: "MEMCFG_TEST_WRITE_PARITY", displayName: "Writes allowed to Parity only (for GSxRAM, MSGxRAM & ROM)" },
	{ name: "MEMCFG_TEST_FUNC_DIAG", displayName: "Diagnostic mode, similar to functional mode but NMI is not generated." },
]
let MEMCFG_SECT = [
	{ name: "MEMCFG_SECT_M0", displayName: "M0 RAM" },
	{ name: "MEMCFG_SECT_M1", displayName: "M1 RAM" },
	{ name: "MEMCFG_SECT_D0", displayName: "D0 RAM" },
	{ name: "MEMCFG_SECT_D1", displayName: "D1 RAM" },
	{ name: "MEMCFG_SECT_DX_ALL", displayName: "All M and D RAM" },
	{ name: "MEMCFG_SECT_LS0", displayName: "LS0 RAM" },
	{ name: "MEMCFG_SECT_LS1", displayName: "LS1 RAM" },
	{ name: "MEMCFG_SECT_LS2", displayName: "LS2 RAM" },
	{ name: "MEMCFG_SECT_LS3", displayName: "LS3 RAM" },
	{ name: "MEMCFG_SECT_LS4", displayName: "LS4 RAM" },
	{ name: "MEMCFG_SECT_LS5", displayName: "LS5 RAM" },
	{ name: "MEMCFG_SECT_LS6", displayName: "LS6 RAM" },
	{ name: "MEMCFG_SECT_LS7", displayName: "LS7 RAM" },
	{ name: "MEMCFG_SECT_LSX_ALL", displayName: "All LS RAM" },
	{ name: "MEMCFG_SECT_GS0", displayName: "GS0 RAM" },
	{ name: "MEMCFG_SECT_GS1", displayName: "GS1 RAM" },
	{ name: "MEMCFG_SECT_GS2", displayName: "GS2 RAM" },
	{ name: "MEMCFG_SECT_GS3", displayName: "GS3 RAM" },
	{ name: "MEMCFG_SECT_GS4", displayName: "GS4 RAM" },
	{ name: "MEMCFG_SECT_GS5", displayName: "GS5 RAM" },
	{ name: "MEMCFG_SECT_GS6", displayName: "GS6 RAM" },
	{ name: "MEMCFG_SECT_GS7", displayName: "GS7 RAM" },
	{ name: "MEMCFG_SECT_GS8", displayName: "GS8 RAM" },
	{ name: "MEMCFG_SECT_GS9", displayName: "GS9 RAM" },
	{ name: "MEMCFG_SECT_GS10", displayName: "GS10 RAM" },
	{ name: "MEMCFG_SECT_GS11", displayName: "GS11 RAM" },
	{ name: "MEMCFG_SECT_GS12", displayName: "GS12 RAM" },
	{ name: "MEMCFG_SECT_GS13", displayName: "GS13 RAM" },
	{ name: "MEMCFG_SECT_GS14", displayName: "GS14 RAM" },
	{ name: "MEMCFG_SECT_GS15", displayName: "GS15 RAM" },
	{ name: "MEMCFG_SECT_GSX_ALL", displayName: "All GS RAM" },
	{ name: "MEMCFG_SECT_MSGCPUTOCPU0", displayName: "CPU-to-CPU message RAM0" },
	{ name: "MEMCFG_SECT_MSGCPUTOCLA1", displayName: "CPU-to-CLA1 message RAM" },
	{ name: "MEMCFG_SECT_MSGCLA1TOCPU", displayName: "CLA1-to-CPU message RAM" },
	{ name: "MEMCFG_SECT_MSGCLA1TODMA", displayName: "CLA1-to-DMA message RAM" },
	{ name: "MEMCFG_SECT_MSGDMATOCLA1", displayName: "DMA-to-CLA1 message RAM" },
	{ name: "MEMCFG_SECT_MSGCPUTOCPU1", displayName: "CPU-to-CPU message RAM1" },
	{ name: "MEMCFG_SECT_MSGCPUTOCM0", displayName: "CPU-to-CM message RAM0" },
	{ name: "MEMCFG_SECT_MSGCPUTOCM1", displayName: "CPU-to-CM message RAM1" },
	{ name: "MEMCFG_SECT_MSGX_ALL", displayName: "All message RAM" },
	{ name: "MEMCFG_SECT_ROMBOOT", displayName: "BOOT ROM" },
	{ name: "MEMCFG_SECT_ROMSECURE", displayName: "Secure ROM" },
	{ name: "MEMCFG_SECT_ROMCLADATA", displayName: "CLA Data ROM" },
	{ name: "MEMCFG_SECT_ROM_ALL", displayName: "All ROMs" },
	{ name: "MEMCFG_SECT_PERIMEM_ETHERCAT", displayName: "Ethercat memory" },
	{ name: "MEMCFG_SECT_PERIMEM_ALL", displayName: "All peripheral memories" },
	{ name: "MEMCFG_SECT_ALL", displayName: "All configurable RAM" },
]
let MEMCFG_PROT = [
	{ name: "MEMCFG_PROT_ALLOWCPUFETCH", displayName: "CPU fetch allowed" },
	{ name: "MEMCFG_PROT_BLOCKCPUFETCH", displayName: "CPU fetch blocked" },
	{ name: "MEMCFG_PROT_ALLOWCPUWRITE", displayName: "CPU write allowed" },
	{ name: "MEMCFG_PROT_BLOCKCPUWRITE", displayName: "CPU write blocked" },
	{ name: "MEMCFG_PROT_ALLOWDMAWRITE", displayName: "DMA write allowed (GSxRAM)" },
	{ name: "MEMCFG_PROT_BLOCKDMAWRITE", displayName: "DMA write blocked (GSxRAM)" },
]
let MEMCFG_NMVIOL = [
	{ name: "MEMCFG_NMVIOL_CPUREAD", displayName: "Non-controller CPU read access" },
	{ name: "MEMCFG_NMVIOL_CPUWRITE", displayName: "Non-controller CPU write access" },
	{ name: "MEMCFG_NMVIOL_CPUFETCH", displayName: "Non-controller CPU fetch access" },
	{ name: "MEMCFG_NMVIOL_DMAWRITE", displayName: "Non-controller DMA write access" },
	{ name: "MEMCFG_NMVIOL_CLA1READ", displayName: "Non-controller CLA1 read access" },
	{ name: "MEMCFG_NMVIOL_CLA1WRITE", displayName: "Non-controller CLA1 write access" },
	{ name: "MEMCFG_NMVIOL_CLA1FETCH", displayName: "Non-controller CLA1 fetch access" },
	{ name: "MEMCFG_NMVIOL_DMAREAD", displayName: "Non-controller DMA read access" },
]
let MEMCFG_MVIOL = [
	{ name: "MEMCFG_MVIOL_CPUFETCH", displayName: "Controller CPU fetch access" },
	{ name: "MEMCFG_MVIOL_CPUWRITE", displayName: "Controller CPU write access" },
	{ name: "MEMCFG_MVIOL_DMAWRITE", displayName: "Controller DMA write access" },
]
let MEMCFG_CERR = [
	{ name: "MEMCFG_CERR_CPUREAD", displayName: "Correctable CPU read error" },
	{ name: "MEMCFG_CERR_DMAREAD", displayName: "Correctable DMA read error" },
	{ name: "MEMCFG_CERR_CLA1READ", displayName: "Correctable CLA1 read error" },
]
let MEMCFG_UCERR = [
	{ name: "MEMCFG_UCERR_CPUREAD", displayName: "Uncorrectable CPU read error" },
	{ name: "MEMCFG_UCERR_DMAREAD", displayName: "Uncorrectable DMA read error" },
	{ name: "MEMCFG_UCERR_CLA1READ", displayName: "Uncorrectable CLA1 read error" },
	{ name: "MEMCFG_UCERR_ECATMEMREAD", displayName: "Uncorrectable ECAT RAM read error" },
]
let MEMCFG_DIAGERR = [
	{ name: "MEMCFG_DIAGERR_UNCORR", displayName: "Uncorr error in diag/test mode" },
	{ name: "MEMCFG_DIAGERR_CORR", displayName: "Corr error in diag/test mode" },
]
module.exports = {
	MemCfg_CLAMemoryType: MemCfg_CLAMemoryType,
	MemCfg_LSRAMControllerSel: MemCfg_LSRAMControllerSel,
	MemCfg_GSRAMControllerSel: MemCfg_GSRAMControllerSel,
	MemCfg_TestMode: MemCfg_TestMode,
	MEMCFG_SECT: MEMCFG_SECT,
	MEMCFG_PROT: MEMCFG_PROT,
	MEMCFG_NMVIOL: MEMCFG_NMVIOL,
	MEMCFG_MVIOL: MEMCFG_MVIOL,
	MEMCFG_CERR: MEMCFG_CERR,
	MEMCFG_UCERR: MEMCFG_UCERR,
	MEMCFG_DIAGERR: MEMCFG_DIAGERR,
}
