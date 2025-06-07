let ASysCtl_CMPHPMuxSelect = [
	{ name: "ASYSCTL_CMPHPMUX_SELECT_1", displayName: "CMPHPMUX select 1" },
	{ name: "ASYSCTL_CMPHPMUX_SELECT_2", displayName: "CMPHPMUX select 2" },
	{ name: "ASYSCTL_CMPHPMUX_SELECT_3", displayName: "CMPHPMUX select 3" },
	{ name: "ASYSCTL_CMPHPMUX_SELECT_4", displayName: "CMPHPMUX select 4" },
]
let ASysCtl_CMPLPMuxSelect = [
	{ name: "ASYSCTL_CMPLPMUX_SELECT_1", displayName: "CMPLPMUX select 1" },
	{ name: "ASYSCTL_CMPLPMUX_SELECT_2", displayName: "CMPLPMUX select 2" },
	{ name: "ASYSCTL_CMPLPMUX_SELECT_3", displayName: "CMPLPMUX select 3" },
	{ name: "ASYSCTL_CMPLPMUX_SELECT_4", displayName: "CMPLPMUX select 4" },
]
let ASysCtl_TestSelect = [
	{ name: "ASYSCTL_TEST_NODE_NO_CONN", displayName: "No Internal Connection" },
	{ name: "ASYSCTL_TEST_NODE_VDDCORE", displayName: "Core VDD (1.2V) voltage" },
	{ name: "ASYSCTL_TEST_NODE_VREFLO", displayName: "VREFLO pin voltage" },
	{ name: "ASYSCTL_TEST_NODE_CDAC1H", displayName: "CMPSS1 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC1L", displayName: "CMPSS1 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC2H", displayName: "CMPSS2 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC2L", displayName: "CMPSS2 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC3H", displayName: "CMPSS3 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC3L", displayName: "CMPSS3 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC4H", displayName: "CMPSS4 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC4L", displayName: "CMPSS4 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_VDDA", displayName: "VDDA voltage" },
	{ name: "ASYSCTL_TEST_NODE_VSSA", displayName: "VSSA - Analog ground pin" },
	{ name: "ASYSCTL_TEST_NODE_ENZ_CALIB_GAIN_3P3V", displayName: "All ADCs are placed in gain" },
]
let ASYSCTL_VREFHI = [
	{ name: "ASYSCTL_VREFHI", displayName: "VREFHI" },
]
let ASYSCTL_CMPSS1_DACL = [
	{ name: "ASYSCTL_CMPSS1_DACL", displayName: "CMPSS1.DACL" },
]
let ASYSCTL_CMPHNMUX_SELECT = [
	{ name: "ASYSCTL_CMPHNMUX_SELECT_1", displayName: "CMPHNMUX select 1" },
	{ name: "ASYSCTL_CMPHNMUX_SELECT_2", displayName: "CMPHNMUX select 2" },
	{ name: "ASYSCTL_CMPHNMUX_SELECT_3", displayName: "CMPHNMUX select 3" },
	{ name: "ASYSCTL_CMPHNMUX_SELECT_4", displayName: "CMPHNMUX select 4" },
]
let ASYSCTL_CMPLNMUX_SELECT = [
	{ name: "ASYSCTL_CMPLNMUX_SELECT_1", displayName: "CMPLNMUX select 1" },
	{ name: "ASYSCTL_CMPLNMUX_SELECT_2", displayName: "CMPLNMUX select 2" },
	{ name: "ASYSCTL_CMPLNMUX_SELECT_3", displayName: "CMPLNMUX select 3" },
	{ name: "ASYSCTL_CMPLNMUX_SELECT_4", displayName: "CMPLNMUX select 4" },
]
module.exports = {
	ASysCtl_CMPHPMuxSelect: ASysCtl_CMPHPMuxSelect,
	ASysCtl_CMPLPMuxSelect: ASysCtl_CMPLPMuxSelect,
	ASysCtl_TestSelect: ASysCtl_TestSelect,
	ASYSCTL_VREFHI: ASYSCTL_VREFHI,
	ASYSCTL_CMPSS1_DACL: ASYSCTL_CMPSS1_DACL,
	ASYSCTL_CMPHNMUX_SELECT: ASYSCTL_CMPHNMUX_SELECT,
	ASYSCTL_CMPLNMUX_SELECT: ASYSCTL_CMPLNMUX_SELECT,
}
