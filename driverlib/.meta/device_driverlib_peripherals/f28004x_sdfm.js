let SDFM_OutputThresholdStatus = [
	{ name: "SDFM_OUTPUT_WITHIN_THRESHOLD", displayName: "SDFM output is within threshold" },
	{ name: "SDFM_OUTPUT_ABOVE_THRESHOLD", displayName: "SDFM output is above threshold" },
	{ name: "SDFM_OUTPUT_BELOW_THRESHOLD", displayName: "SDFM output is below threshold" },
]
let SDFM_FilterNumber = [
	{ name: "SDFM_FILTER_1", displayName: "Digital filter 1" },
	{ name: "SDFM_FILTER_2", displayName: "Digital filter 2" },
	{ name: "SDFM_FILTER_3", displayName: "Digital filter 3" },
	{ name: "SDFM_FILTER_4", displayName: "Digital filter 4" },
]
let SDFM_FilterType = [
	{ name: "SDFM_FILTER_SINC_FAST", displayName: "Digital filter with SincFast structure." },
	{ name: "SDFM_FILTER_SINC_1", displayName: "Digital filter with Sinc1 structure" },
	{ name: "SDFM_FILTER_SINC_2", displayName: "Digital filter with Sinc3 structure." },
	{ name: "SDFM_FILTER_SINC_3", displayName: "Digital filter with Sinc4 structure." },
]
let SDFM_ModulatorClockMode = [
	{ name: "SDFM_MODULATOR_CLK_EQUAL_DATA_RATE", displayName: "Modulator clock is identical to the data rate" },
	{ name: "SDFM_MODULATOR_CLK_HALF_DATA_RATE", displayName: "Modulator clock is half the data rate" },
	{ name: "SDFM_MODULATOR_CLK_OFF", displayName: "Modulator clock is off. Data is Manchester coded." },
	{ name: "SDFM_MODULATOR_CLK_DOUBLE_DATA_RATE", displayName: "Modulator clock is double the data rate." },
]
let SDFM_OutputDataFormat = [
	{ name: "SDFM_DATA_FORMAT_16_BIT", displayName: "Filter output is in 16 bits 2's complement format." },
	{ name: "SDFM_DATA_FORMAT_32_BIT", displayName: "Filter output is in 32 bits 2's complement format." },
]
let SDFM_DataReadyInterruptSource = [
	{ name: "SDFM_DATA_READY_SOURCE_DIRECT", displayName: "Data ready interrupt source is direct (non -FIFO)." },
	{ name: "SDFM_DATA_READY_SOURCE_FIFO", displayName: "Data ready interrupt source is FIFO." },
]
let SDFM_PWMSyncSource = [
	{ name: "SDFM_SYNC_PWM1_SOCA", displayName: "SDFM sync source is PWM1 SOCA" },
	{ name: "SDFM_SYNC_PWM1_SOCB", displayName: "SDFM sync source is PWM1 SOCB" },
	{ name: "SDFM_SYNC_PWM2_SOCA", displayName: "SDFM sync source is PWM2 SOCA" },
	{ name: "SDFM_SYNC_PWM2_SOCB", displayName: "SDFM sync source is PWM2 SOCB" },
	{ name: "SDFM_SYNC_PWM3_SOCA", displayName: "SDFM sync source is PWM3 SOCA" },
	{ name: "SDFM_SYNC_PWM3_SOCB", displayName: "SDFM sync source is PWM3 SOCB" },
	{ name: "SDFM_SYNC_PWM4_SOCA", displayName: "SDFM sync source is PWM4 SOCA" },
	{ name: "SDFM_SYNC_PWM4_SOCB", displayName: "SDFM sync source is PWM4 SOCB" },
	{ name: "SDFM_SYNC_PWM5_SOCA", displayName: "SDFM sync source is PWM5 SOCA" },
	{ name: "SDFM_SYNC_PWM5_SOCB", displayName: "SDFM sync source is PWM5 SOCB" },
	{ name: "SDFM_SYNC_PWM6_SOCA", displayName: "SDFM sync source is PWM6 SOCA" },
	{ name: "SDFM_SYNC_PWM6_SOCB", displayName: "SDFM sync source is PWM6 SOCB" },
	{ name: "SDFM_SYNC_PWM7_SOCA", displayName: "SDFM sync source is PWM7 SOCA" },
	{ name: "SDFM_SYNC_PWM7_SOCB", displayName: "SDFM sync source is PWM7 SOCB" },
	{ name: "SDFM_SYNC_PWM8_SOCA", displayName: "SDFM sync source is PWM8 SOCA" },
	{ name: "SDFM_SYNC_PWM8_SOCB", displayName: "SDFM sync source is PWM8 SOCB" },
]
let SDFM_FIFOClearSyncMode = [
	{ name: "SDFM_FIFO_NOT_CLEARED_ON_SYNC", displayName: "SDFM FIFO buffer is not cleared on Sync signal" },
	{ name: "SDFM_FIFO_CLEARED_ON_SYNC", displayName: "SDFM FIFO buffer is cleared on Sync signal" },
]
let SDFM_WaitForSyncClearMode = [
	{ name: "SDFM_MANUAL_CLEAR_WAIT_FOR_SYNC", displayName: "Wait for sync cleared using software." },
	{ name: "SDFM_AUTO_CLEAR_WAIT_FOR_SYNC", displayName: "Wait for sync cleared automatically" },
]
module.exports = {
	SDFM_OutputThresholdStatus: SDFM_OutputThresholdStatus,
	SDFM_FilterNumber: SDFM_FilterNumber,
	SDFM_FilterType: SDFM_FilterType,
	SDFM_ModulatorClockMode: SDFM_ModulatorClockMode,
	SDFM_OutputDataFormat: SDFM_OutputDataFormat,
	SDFM_DataReadyInterruptSource: SDFM_DataReadyInterruptSource,
	SDFM_PWMSyncSource: SDFM_PWMSyncSource,
	SDFM_FIFOClearSyncMode: SDFM_FIFOClearSyncMode,
	SDFM_WaitForSyncClearMode: SDFM_WaitForSyncClearMode,
}
