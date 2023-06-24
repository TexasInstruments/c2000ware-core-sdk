let Flash_BankNumber = [
	{ name: "FLASH_BANK", displayName: "Bank" },
]
let Flash_PumpOwnership = [
	{ name: "FLASH_BANK0_WRAPPER", displayName: "Bank 0 Wrapper" },
	{ name: "FLASH_BANK1_WRAPPER", displayName: "Bank 1 Wrapper" },
]
let Flash_BankPowerMode = [
	{ name: "FLASH_BANK_PWR_SLEEP", displayName: "Sleep fallback mode" },
	{ name: "FLASH_BANK_PWR_STANDBY", displayName: "Standby fallback mode" },
	{ name: "FLASH_BANK_PWR_ACTIVE", displayName: "Active fallback mode" },
]
let Flash_PumpPowerMode = [
	{ name: "FLASH_PUMP_PWR_SLEEP", displayName: "Sleep fallback mode" },
	{ name: "FLASH_PUMP_PWR_ACTIVE", displayName: "Active fallback mode" },
]
let Flash_ErrorStatus = [
	{ name: "FLASH_NO_ERR", displayName: "No error" },
	{ name: "FLASH_FAIL_0", displayName: "Fail on 0" },
	{ name: "FLASH_FAIL_1", displayName: "Fail on 1" },
	{ name: "FLASH_UNC_ERR", displayName: "Uncorrectable error" },
]
let Flash_ErrorType = [
	{ name: "FLASH_DATA_ERR", displayName: "Data error" },
	{ name: "FLASH_ECC_ERR", displayName: "ECC error" },
]
let Flash_SingleBitErrorIndicator = [
	{ name: "FLASH_DATA_BITS", displayName: "Data bits" },
	{ name: "FLASH_CHECK_BITS", displayName: "ECC bits" },
]
let FLASH_DELAY_CONFIG = [
	{ name: "FLASH_DELAY_CONFIG", displayName: "DELAY CONFIG" },
]
let FLASH_PUMP_KEY = [
	{ name: "FLASH_PUMP_KEY", displayName: "Pump semaphore key" },
]
module.exports = {
	Flash_BankNumber: Flash_BankNumber,
	Flash_PumpOwnership: Flash_PumpOwnership,
	Flash_BankPowerMode: Flash_BankPowerMode,
	Flash_PumpPowerMode: Flash_PumpPowerMode,
	Flash_ErrorStatus: Flash_ErrorStatus,
	Flash_ErrorType: Flash_ErrorType,
	Flash_SingleBitErrorIndicator: Flash_SingleBitErrorIndicator,
	FLASH_DELAY_CONFIG: FLASH_DELAY_CONFIG,
	FLASH_PUMP_KEY: FLASH_PUMP_KEY,
}
