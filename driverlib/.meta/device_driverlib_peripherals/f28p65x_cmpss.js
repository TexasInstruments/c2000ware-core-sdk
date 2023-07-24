let CMPSS_FilterInput = [
	{ name: "CMPSS_FILTIN_COMPOUT", displayName: "Filter input driven by comp output" },
	{ name: "CMPSS_FILTIN_EXT_H1", displayName: "Filter input driven by EXT_FILTIN_H[1]" },
	{ name: "CMPSS_FILTIN_EXT_H2", displayName: "Filter input driven by EXT_FILTIN_H[2]" },
	{ name: "CMPSS_FILTIN_EXT_H3", displayName: "Filter input driven by EXT_FILTIN_H[3]" },
	{ name: "CMPSS_FILTIN_EXT_H4", displayName: "Filter input driven by EXT_FILTIN_H[4]" },
	{ name: "CMPSS_FILTIN_EXT_H5", displayName: "Filter input driven by EXT_FILTIN_H[5]" },
	{ name: "CMPSS_FILTIN_EXT_H6", displayName: "Filter input driven by EXT_FILTIN_H[6]" },
	{ name: "CMPSS_FILTIN_EXT_H7", displayName: "Filter input driven by EXT_FILTIN_H[7]" },
]
let CMPSS_RampDirection = [
	{ name: "CMPSS_RAMP_DIR_DOWN", displayName: "Decrementing Ramp" },
	{ name: "CMPSS_RAMP_DIR_UP", displayName: "Incrementing Ramp" },
]
let CMPSS_RampXTrigger = [
	{ name: "CMPSS_RAMP_XTRIGGER_DISABLE", displayName: "RAMPH & RAMPL SOR trigger is" },
	{ name: "CMPSS_RAMP_XTRIGGER_RAMPH_EOR", displayName: "RAMPH SOR trigger is the" },
	{ name: "CMPSS_RAMP_XTRIGGER_RAMPL_EOR", displayName: "RAMPL SOR trigger is the" },
]
let CMPSS_DEActiveSelect = [
	{ name: "CMPSS_DEACTIVE_EPWM1", displayName: "EPWM1 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM2", displayName: "EPWM2 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM3", displayName: "EPWM3 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM4", displayName: "EPWM4 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM5", displayName: "EPWM5 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM6", displayName: "EPWM6 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM7", displayName: "EPWM7 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM8", displayName: "EPWM8 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM9", displayName: "EPWM9 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM10", displayName: "EPWM10 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM11", displayName: "EPWM11 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM12", displayName: "EPWM12 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM13", displayName: "EPWM13 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM14", displayName: "EPWM14 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM15", displayName: "EPWM15 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM16", displayName: "EPWM16 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM17", displayName: "EPWM17 DEACTIVE" },
	{ name: "CMPSS_DEACTIVE_EPWM18", displayName: "EPWM18 DEACTIVE" },
]
let CMPSS_RampClockDiv = [
	{ name: "CMPSS_RAMP_CLOCK_DIV1", displayName: "RAMPCLK = SYSCLK/1" },
	{ name: "CMPSS_RAMP_CLOCK_DIV2", displayName: "RAMPCLK = SYSCLK/2" },
	{ name: "CMPSS_RAMP_CLOCK_DIV3", displayName: "RAMPCLK = SYSCLK/3" },
	{ name: "CMPSS_RAMP_CLOCK_DIV4", displayName: "RAMPCLK = SYSCLK/4" },
	{ name: "CMPSS_RAMP_CLOCK_DIV5", displayName: "RAMPCLK = SYSCLK/5" },
	{ name: "CMPSS_RAMP_CLOCK_DIV6", displayName: "RAMPCLK = SYSCLK/6" },
	{ name: "CMPSS_RAMP_CLOCK_DIV7", displayName: "RAMPCLK = SYSCLK/7" },
	{ name: "CMPSS_RAMP_CLOCK_DIV8", displayName: "RAMPCLK = SYSCLK/8" },
	{ name: "CMPSS_RAMP_CLOCK_DIV9", displayName: "RAMPCLK = SYSCLK/9" },
	{ name: "CMPSS_RAMP_CLOCK_DIV10", displayName: "RAMPCLK = SYSCLK/10" },
	{ name: "CMPSS_RAMP_CLOCK_DIV11", displayName: "RAMPCLK = SYSCLK/11" },
	{ name: "CMPSS_RAMP_CLOCK_DIV12", displayName: "RAMPCLK = SYSCLK/12" },
	{ name: "CMPSS_RAMP_CLOCK_DIV13", displayName: "RAMPCLK = SYSCLK/13" },
	{ name: "CMPSS_RAMP_CLOCK_DIV14", displayName: "RAMPCLK = SYSCLK/14" },
	{ name: "CMPSS_RAMP_CLOCK_DIV15", displayName: "RAMPCLK = SYSCLK/15" },
	{ name: "CMPSS_RAMP_CLOCK_DIV16", displayName: "RAMPCLK = SYSCLK/16" },
]
let CMPSS_EPWMGroup = [
	{ name: "CMPSS_EPWM_GROUP_0TO15", displayName: "Select EPWM0-EPWM15 group" },
	{ name: "CMPSS_EPWM_GROUP_16TO31", displayName: "Select EPWM16-EPWM31 group" },
]
let CMPSS_STS = [
	{ name: "CMPSS_STS_HI_FILTOUT", displayName: "High digital filter output" },
	{ name: "CMPSS_STS_HI_LATCHFILTOUT", displayName: "Latched value of high digital filter output" },
	{ name: "CMPSS_STS_LO_FILTOUT", displayName: "Low digital filter output" },
	{ name: "CMPSS_STS_LO_LATCHFILTOUT", displayName: "Latched value of low digital filter output" },
]
module.exports = {
	CMPSS_FilterInput: CMPSS_FilterInput,
	CMPSS_RampDirection: CMPSS_RampDirection,
	CMPSS_RampXTrigger: CMPSS_RampXTrigger,
	CMPSS_DEActiveSelect: CMPSS_DEActiveSelect,
	CMPSS_RampClockDiv: CMPSS_RampClockDiv,
	CMPSS_EPWMGroup: CMPSS_EPWMGroup,
	CMPSS_STS: CMPSS_STS,
}
