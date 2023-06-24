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
	CMPSS_STS: CMPSS_STS,
}
