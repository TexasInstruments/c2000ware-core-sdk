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
module.exports = {
	SDFM_OutputThresholdStatus: SDFM_OutputThresholdStatus,
	SDFM_FilterNumber: SDFM_FilterNumber,
	SDFM_FilterType: SDFM_FilterType,
	SDFM_ModulatorClockMode: SDFM_ModulatorClockMode,
	SDFM_OutputDataFormat: SDFM_OutputDataFormat,
}
