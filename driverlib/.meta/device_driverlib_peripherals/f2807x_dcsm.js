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
	{ name: "DCSM_RAMD0", displayName: "RAMD0" },
	{ name: "DCSM_RAMD1", displayName: "RAMD1" },
	{ name: "DCSM_CLA", displayName: "Offset of CLA field in in RAMSTAT divided by two" },
]
let DCSM_Sector = [
	{ name: "DCSM_SECTOR_A", displayName: "Sector A" },
	{ name: "DCSM_SECTOR_B", displayName: "Sector B" },
	{ name: "DCSM_SECTOR_C", displayName: "Sector C" },
	{ name: "DCSM_SECTOR_D", displayName: "Sector D" },
	{ name: "DCSM_SECTOR_E", displayName: "Sector E" },
	{ name: "DCSM_SECTOR_F", displayName: "Sector F" },
	{ name: "DCSM_SECTOR_G", displayName: "Sector G" },
	{ name: "DCSM_SECTOR_H", displayName: "Sector H" },
	{ name: "DCSM_SECTOR_I", displayName: "Sector I" },
	{ name: "DCSM_SECTOR_J", displayName: "Sector J" },
	{ name: "DCSM_SECTOR_K", displayName: "Sector K" },
	{ name: "DCSM_SECTOR_L", displayName: "Sector L" },
	{ name: "DCSM_SECTOR_M", displayName: "Sector M" },
	{ name: "DCSM_SECTOR_N", displayName: "Sector N" },
]
module.exports = {
	DCSM_MemoryStatus: DCSM_MemoryStatus,
	DCSM_SemaphoreZone: DCSM_SemaphoreZone,
	DCSM_SecurityStatus: DCSM_SecurityStatus,
	DCSM_EXEOnlyStatus: DCSM_EXEOnlyStatus,
	DCSM_RAMModule: DCSM_RAMModule,
	DCSM_Sector: DCSM_Sector,
}
