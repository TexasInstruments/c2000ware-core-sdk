let MemCfg_TestMode = [
	{ name: "MEMCFG_TEST_FUNCTIONAL", displayName: "Functional mode. Test mode is disabled." },
	{ name: "MEMCFG_TEST_WRITE_DATA", displayName: "Writes allowed to data only" },
	{ name: "MEMCFG_TEST_WRITE_ECC", displayName: "Writes allowed to ECC only (for DxRAM/MxRAM and PIEVECT RAM)" },
	{ name: "MEMCFG_TEST_WRITE_PARITY", displayName: "Writes allowed to Parity only (for LSxRAM)" },
	{ name: "MEMCFG_TEST_FUNC_DIAG", displayName: "Diagnostic mode, similar to functional mode but NMI is not generated." },
]
let MEMCFG_SECT = [
	{ name: "MEMCFG_SECT_M0", displayName: "M0 RAM" },
	{ name: "MEMCFG_SECT_M1", displayName: "M1 RAM" },
	{ name: "MEMCFG_SECT_DX_ALL", displayName: "All M and D RAM" },
	{ name: "MEMCFG_SECT_PIEVECT", displayName: "PIEVECT RAM" },
	{ name: "MEMCFG_SECT_LS0", displayName: "LS0 RAM" },
	{ name: "MEMCFG_SECT_LS1", displayName: "LS1 RAM" },
	{ name: "MEMCFG_SECT_LSX_ALL", displayName: "All LS RAM" },
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
]
let MEMCFG_MVIOL = [
	{ name: "MEMCFG_MVIOL_CPUFETCH", displayName: "Controller CPU fetch access" },
	{ name: "MEMCFG_MVIOL_CPUWRITE", displayName: "Controller CPU write access" },
]
let MEMCFG_CERR_CPUREAD = [
	{ name: "MEMCFG_CERR_CPUREAD", displayName: "Correctable CPU read error" },
]
let MEMCFG_UCERR_CPUREAD = [
	{ name: "MEMCFG_UCERR_CPUREAD", displayName: "Uncorrectable CPU read error" },
]
let MEMCFG_DIAGERR = [
	{ name: "MEMCFG_DIAGERR_UNCORR", displayName: "Uncorr error in diag/test mode" },
	{ name: "MEMCFG_DIAGERR_CORR", displayName: "Corr error in diag/test mode" },
]
module.exports = {
	MemCfg_TestMode: MemCfg_TestMode,
	MEMCFG_SECT: MEMCFG_SECT,
	MEMCFG_PROT: MEMCFG_PROT,
	MEMCFG_MVIOL: MEMCFG_MVIOL,
	MEMCFG_CERR_CPUREAD: MEMCFG_CERR_CPUREAD,
	MEMCFG_UCERR_CPUREAD: MEMCFG_UCERR_CPUREAD,
	MEMCFG_DIAGERR: MEMCFG_DIAGERR,
}
