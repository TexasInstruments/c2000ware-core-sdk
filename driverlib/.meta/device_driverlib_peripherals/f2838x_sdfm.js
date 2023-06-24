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
	{ name: "SDFM_SYNC_PWM9_SOCA", displayName: "SDFM sync source is PWM9 SOCA" },
	{ name: "SDFM_SYNC_PWM9_SOCB", displayName: "SDFM sync source is PWM9 SOCB" },
	{ name: "SDFM_SYNC_PWM10_SOCA", displayName: "SDFM sync source is PWM10 SOCA" },
	{ name: "SDFM_SYNC_PWM10_SOCB", displayName: "SDFM sync source is PWM10 SOCB" },
	{ name: "SDFM_SYNC_PWM11_SOCA", displayName: "SDFM sync source is PWM11 SOCA" },
	{ name: "SDFM_SYNC_PWM11_SOCB", displayName: "SDFM sync source is PWM11 SOCB" },
	{ name: "SDFM_SYNC_PWM12_SOCA", displayName: "SDFM sync source is PWM12 SOCA" },
	{ name: "SDFM_SYNC_PWM12_SOCB", displayName: "SDFM sync source is PWM12 SOCB" },
	{ name: "SDFM_SYNC_PWM13_SOCA", displayName: "SDFM sync source is PWM13 SOCA" },
	{ name: "SDFM_SYNC_PWM13_SOCB", displayName: "SDFM sync source is PWM13 SOCB" },
	{ name: "SDFM_SYNC_PWM14_SOCA", displayName: "SDFM sync source is PWM14 SOCA" },
	{ name: "SDFM_SYNC_PWM14_SOCB", displayName: "SDFM sync source is PWM14 SOCB" },
	{ name: "SDFM_SYNC_PWM15_SOCA", displayName: "SDFM sync source is PWM15 SOCA" },
	{ name: "SDFM_SYNC_PWM15_SOCB", displayName: "SDFM sync source is PWM15 SOCB" },
	{ name: "SDFM_SYNC_PWM16_SOCA", displayName: "SDFM sync source is PWM16 SOCA" },
	{ name: "SDFM_SYNC_PWM16_SOCB", displayName: "SDFM sync source is PWM16 SOCB" },
]
let SDFM_FIFOClearSyncMode = [
	{ name: "SDFM_FIFO_NOT_CLEARED_ON_SYNC", displayName: "SDFM FIFO buffer is not cleared on Sync signal" },
	{ name: "SDFM_FIFO_CLEARED_ON_SYNC", displayName: "SDFM FIFO buffer is cleared on Sync signal" },
]
let SDFM_WaitForSyncClearMode = [
	{ name: "SDFM_MANUAL_CLEAR_WAIT_FOR_SYNC", displayName: "Wait for sync cleared using software." },
	{ name: "SDFM_AUTO_CLEAR_WAIT_FOR_SYNC", displayName: "Wait for sync cleared automatically" },
]
let SDFM_CompEventNumber = [
	{ name: "SDFM_COMP_EVENT_1", displayName: "Selects CEVT1" },
	{ name: "SDFM_COMP_EVENT_2", displayName: "Selects CEVT2" },
]
let SDFM_CompEventSource = [
	{ name: "SDFM_COMP_EVENT_SRC_COMPH1", displayName: "COMPH1 event is the source" },
	{ name: "SDFM_COMP_EVENT_SRC_COMPH1_L1", displayName: "Either of COMPH1 or COMPL1 event" },
	{ name: "SDFM_COMP_EVENT_SRC_COMPH2", displayName: "COMPH2 event is the source" },
	{ name: "SDFM_COMP_EVENT_SRC_COMPH2_L2", displayName: "Either of COMPH2 or COMPL2 event" },
	{ name: "SDFM_COMP_EVENT_SRC_COMPL1", displayName: "COMPL1 event is the source" },
	{ name: "SDFM_COMP_EVENT_SRC_COMPL2", displayName: "COMPL2 event is the source" },
]
let SDFM_ClockSource = [
	{ name: "SDFM_CLK_SOURCE_CHANNEL_CLK", displayName: "Source is respective channel clock" },
	{ name: "SDFM_CLK_SOURCE_SD1_CLK", displayName: "Source is SD1 channel clock is the source" },
]
let SDFM_CompEventHighSource = [
	{ name: "SDFM_COMPHOUT_SOURCE_COMPHIN", displayName: "Comparator event high source is unfiltered event" },
	{ name: "SDFM_COMPHOUT_SOURCE_FILTER", displayName: "Comparator event high source is filtered event" },
]
let SDFM_CompEventLowSource = [
	{ name: "SDFM_COMPLOUT_SOURCE_COMPLIN", displayName: "Comparator event low source is unfiltered event" },
	{ name: "SDFM_COMPLOUT_SOURCE_FILTER", displayName: "Comparator event low source is filtered event" },
]
let SDFM_COMPEVT_FILTER_CONFIG_M = [
	{ name: "SDFM_COMPEVT_FILTER_CONFIG_M", displayName: "COMPEVT FILTER CONFIG M" },
]
let SDFM_COMPEVT_FILTER_LOCK_M = [
	{ name: "SDFM_COMPEVT_FILTER_LOCK_M", displayName: "COMPEVT FILTER LOCK M" },
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
	SDFM_CompEventNumber: SDFM_CompEventNumber,
	SDFM_CompEventSource: SDFM_CompEventSource,
	SDFM_ClockSource: SDFM_ClockSource,
	SDFM_CompEventHighSource: SDFM_CompEventHighSource,
	SDFM_CompEventLowSource: SDFM_CompEventLowSource,
	SDFM_COMPEVT_FILTER_CONFIG_M: SDFM_COMPEVT_FILTER_CONFIG_M,
	SDFM_COMPEVT_FILTER_LOCK_M: SDFM_COMPEVT_FILTER_LOCK_M,
}
