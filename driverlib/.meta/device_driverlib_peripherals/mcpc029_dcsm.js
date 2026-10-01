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
let DCSM_Sector = [
	{ name: "DCSM_BANK0_SECTOR_0", displayName: "Bank 0 - Sector 0" },
	{ name: "DCSM_BANK0_SECTOR_1", displayName: "Bank 0 - Sector 1" },
	{ name: "DCSM_BANK0_SECTOR_2", displayName: "Bank 0 - Sector 2" },
	{ name: "DCSM_BANK0_SECTOR_3", displayName: "Bank 0 - Sector 3" },
	{ name: "DCSM_BANK0_SECTOR_31_4", displayName: "Bank 0 - Sector 31-4" },
	{ name: "DCSM_BANK0_SECTOR_63_32", displayName: "Bank 0 - Sector 63-32" },
]
let DCSM_OTPLock = [
	{ name: "DCSM_OTPSECLOCK_JTAG", displayName: "JTAG Lock Status" },
	{ name: "DCSM_OTPSECLOCK_PSWDLOCK", displayName: "Zone Password Lock" },
]
let DCSM_PERSem = [
	{ name: "DCSM_GRABWD", displayName: "Grab Watchdog configuration" },
	{ name: "DCSM_GRABNMIWD", displayName: "Grab NMIWD configuration" },
	{ name: "DCSM_GRABTIMER1", displayName: "Grab TIMER1 configuration" },
	{ name: "DCSM_GRABCLKCTL", displayName: "Grab Clock configuration" },
	{ name: "DCSM_GRABRSTCTL", displayName: "Grab Reset configuration" },
]
module.exports = {
	DCSM_MemoryStatus: DCSM_MemoryStatus,
	DCSM_SemaphoreZone: DCSM_SemaphoreZone,
	DCSM_SecurityStatus: DCSM_SecurityStatus,
	DCSM_EXEOnlyStatus: DCSM_EXEOnlyStatus,
	DCSM_Sector: DCSM_Sector,
	DCSM_OTPLock: DCSM_OTPLock,
	DCSM_PERSem: DCSM_PERSem,
}
