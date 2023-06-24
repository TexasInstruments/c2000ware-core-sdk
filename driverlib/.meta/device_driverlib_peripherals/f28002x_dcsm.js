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
	{ name: "DCSM_RAMLS4", displayName: "RAMLS4" },
	{ name: "DCSM_RAMLS5", displayName: "RAMLS5" },
	{ name: "DCSM_RAMLS6", displayName: "RAMLS6" },
	{ name: "DCSM_RAMLS7", displayName: "RAMLS7" },
]
let DCSM_Sector = [
	{ name: "DCSM_BANK0_SECTOR0", displayName: "Bank 0 - Sector 0" },
	{ name: "DCSM_BANK0_SECTOR1", displayName: "Bank 0 - Sector 1" },
	{ name: "DCSM_BANK0_SECTOR2", displayName: "Bank 0 - Sector 2" },
	{ name: "DCSM_BANK0_SECTOR3", displayName: "Bank 0 - Sector 3" },
	{ name: "DCSM_BANK0_SECTOR4", displayName: "Bank 0 - Sector 4" },
	{ name: "DCSM_BANK0_SECTOR5", displayName: "Bank 0 - Sector 5" },
	{ name: "DCSM_BANK0_SECTOR6", displayName: "Bank 0 - Sector 6" },
	{ name: "DCSM_BANK0_SECTOR7", displayName: "Bank 0 - Sector 7" },
	{ name: "DCSM_BANK0_SECTOR8", displayName: "Bank 0 - Sector 8" },
	{ name: "DCSM_BANK0_SECTOR9", displayName: "Bank 0 - Sector 9" },
	{ name: "DCSM_BANK0_SECTOR10", displayName: "Bank 0 - Sector 10" },
	{ name: "DCSM_BANK0_SECTOR11", displayName: "Bank 0 - Sector 11" },
	{ name: "DCSM_BANK0_SECTOR12", displayName: "Bank 0 - Sector 12" },
	{ name: "DCSM_BANK0_SECTOR13", displayName: "Bank 0 - Sector 13" },
	{ name: "DCSM_BANK0_SECTOR14", displayName: "Bank 0 - Sector 14" },
	{ name: "DCSM_BANK0_SECTOR15", displayName: "Bank 0 - Sector 15" },
]
module.exports = {
	DCSM_MemoryStatus: DCSM_MemoryStatus,
	DCSM_SemaphoreZone: DCSM_SemaphoreZone,
	DCSM_SecurityStatus: DCSM_SecurityStatus,
	DCSM_EXEOnlyStatus: DCSM_EXEOnlyStatus,
	DCSM_RAMModule: DCSM_RAMModule,
	DCSM_Sector: DCSM_Sector,
}
