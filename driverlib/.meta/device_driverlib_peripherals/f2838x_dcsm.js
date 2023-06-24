let DCSM_MemoryStatus = [
	{ name: "DCSM_MEMORY_INACCESSIBLE", displayName: "Inaccessible" },
	{ name: "DCSM_MEMORY_ZONE1", displayName: "Zone 1" },
	{ name: "DCSM_MEMORY_ZONE2", displayName: "Zone 2" },
	{ name: "DCSM_MEMORY_FULL_ACCESS", displayName: "Full access" },
]
let DCSM_SemaphoreZone = [
	{ name: "DCSM_FLSEM_ZONE1", displayName: "Flash semaphore Zone 1" },
	{ name: "DCSM_FLSEM_ZONE2", displayName: "Flash semaphore Zone 2" },
]
let DCSM_SecurityStatus = [
	{ name: "DCSM_STATUS_SECURE", displayName: "Secure" },
	{ name: "DCSM_STATUS_UNSECURE", displayName: "Unsecure" },
	{ name: "DCSM_STATUS_LOCKED", displayName: "Locked" },
	{ name: "DCSM_STATUS_BLOCKED", displayName: "Blocked" },
]
let DCSM_EXEOnlyStatus = [
	{ name: "DCSM_PROTECTED", displayName: "Protected" },
	{ name: "DCSM_UNPROTECTED", displayName: "Unprotected" },
	{ name: "DCSM_INCORRECT_ZONE", displayName: "Incorrect Zone" },
]
let DCSM_RAMModule = [
	{ name: "DCSM_RAMLS0", displayName: "RAMLS0" },
	{ name: "DCSM_RAMLS1", displayName: "RAMLS1" },
	{ name: "DCSM_RAMLS2", displayName: "RAMLS2" },
	{ name: "DCSM_RAMLS3", displayName: "RAMLS3" },
	{ name: "DCSM_RAMLS4", displayName: "RAMLS4" },
	{ name: "DCSM_RAMLS5", displayName: "RAMLS5" },
	{ name: "DCSM_RAMLS6", displayName: "RAMLS6" },
	{ name: "DCSM_RAMLS7", displayName: "RAMLS7" },
	{ name: "DCSM_RAMD0", displayName: "RAMD0" },
	{ name: "DCSM_RAMD1", displayName: "RAMD1" },
	{ name: "DCSM_C28_RAM_END", displayName: "C28 RAM END" },
	{ name: "DCSM_RAM_CM_C0", displayName: "RAM CM C0" },
	{ name: "DCSM_RAM_CM_C1", displayName: "RAM CM C1" },
	{ name: "DCSM_RAM1_CPU1_CM", displayName: "CPU1 to CM Message RAM 1" },
	{ name: "DCSM_RAM2_CPU1_CM", displayName: "CPU1 to CM Message RAM 2" },
	{ name: "DCSM_RAM1_CM_CPU1", displayName: "CM to CPU1 Message RAM 1" },
	{ name: "DCSM_RAM2_CM_CPU1", displayName: "CM to CPU1 Message RAM 2" },
	{ name: "DCSM_RAM1_CPU2_CM", displayName: "CPU2 to CM Message RAM 1" },
	{ name: "DCSM_RAM2_CPU2_CM", displayName: "CPU2 to CM Message RAM 2" },
	{ name: "DCSM_RAM1_CM_CPU2", displayName: "CM to CPU2 Message RAM 1" },
	{ name: "DCSM_RAM2_CM_CPU2", displayName: "CM to CPU2 Message RAM 2" },
	{ name: "DCSM_RAM1_CPU1_CPU2", displayName: "CPU1 to CPU2 Message RAM 1" },
	{ name: "DCSM_RAM2_CPU1_CPU2", displayName: "CPU1 to CPU2 Message RAM 2" },
	{ name: "DCSM_RAM1_CPU2_CPU1", displayName: "CPU2 to CPU1 Message RAM 1" },
	{ name: "DCSM_RAM2_CPU2_CPU1", displayName: "CPU2 to CPU1 Message RAM 2" },
	{ name: "DCSM_CM_RAM_END", displayName: "CM RAM END" },
]
let DCSM_Sector = [
	{ name: "DCSM_SECTOR_0", displayName: "Sector 0" },
	{ name: "DCSM_SECTOR_1", displayName: "Sector 1" },
	{ name: "DCSM_SECTOR_2", displayName: "Sector 2" },
	{ name: "DCSM_SECTOR_3", displayName: "Sector 3" },
	{ name: "DCSM_SECTOR_4", displayName: "Sector 4" },
	{ name: "DCSM_SECTOR_5", displayName: "Sector 5" },
	{ name: "DCSM_SECTOR_6", displayName: "Sector 6" },
	{ name: "DCSM_SECTOR_7", displayName: "Sector 7" },
	{ name: "DCSM_SECTOR_8", displayName: "Sector 8" },
	{ name: "DCSM_SECTOR_9", displayName: "Sector 9" },
	{ name: "DCSM_SECTOR_10", displayName: "Sector 10" },
	{ name: "DCSM_SECTOR_11", displayName: "Sector 11" },
	{ name: "DCSM_SECTOR_12", displayName: "Sector 12" },
	{ name: "DCSM_SECTOR_13", displayName: "Sector 13" },
]
let DCSM_CPUSel = [
	{ name: "DCSM_CPUSEL_CPU1", displayName: "To access CPU1 Memory" },
	{ name: "DCSM_CPUSEL_CPU2", displayName: "To access CPU2 Memory" },
	{ name: "DCSM_CPUSEL_CM", displayName: "To access CM Memory" },
]
let DCSM_OTPLock = [
	{ name: "DCSM_OTPSECLOCK_JTAG", displayName: "JTAG Lock Status" },
	{ name: "DCSM_OTPSECLOCK_PSWDLOCK", displayName: "Zone Password Lock" },
	{ name: "DCSM_OTPSECLOCK_CRCLOCK", displayName: "Zone CRC Lock" },
]
module.exports = {
	DCSM_MemoryStatus: DCSM_MemoryStatus,
	DCSM_SemaphoreZone: DCSM_SemaphoreZone,
	DCSM_SecurityStatus: DCSM_SecurityStatus,
	DCSM_EXEOnlyStatus: DCSM_EXEOnlyStatus,
	DCSM_RAMModule: DCSM_RAMModule,
	DCSM_Sector: DCSM_Sector,
	DCSM_CPUSel: DCSM_CPUSel,
	DCSM_OTPLock: DCSM_OTPLock,
}
