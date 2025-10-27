let ASysCtl_CMPHPMuxSelect = [
	{ name: "ASYSCTL_CMPHPMUX_SELECT_1", displayName: "CMPHPMUX select 1" },
	{ name: "ASYSCTL_CMPHPMUX_SELECT_2", displayName: "CMPHPMUX select 2" },
	{ name: "ASYSCTL_CMPHPMUX_SELECT_3", displayName: "CMPHPMUX select 3" },
]
let ASysCtl_CMPLPMuxSelect = [
	{ name: "ASYSCTL_CMPLPMUX_SELECT_1", displayName: "CMPLPMUX select 1" },
	{ name: "ASYSCTL_CMPLPMUX_SELECT_2", displayName: "CMPLPMUX select 2" },
	{ name: "ASYSCTL_CMPLPMUX_SELECT_3", displayName: "CMPLPMUX select 3" },
]
let ASysCtl_TestSelect = [
	{ name: "ASYSCTL_TEST_NODE_NO_CONN", displayName: "No Internal Connection" },
	{ name: "ASYSCTL_TEST_NODE_VDDCORE", displayName: "Core VDD (1.2V) voltage" },
	{ name: "ASYSCTL_TEST_NODE_VDDA", displayName: "VDDA voltage" },
	{ name: "ASYSCTL_TEST_NODE_VSSA", displayName: "VSSA - Analog ground pin" },
	{ name: "ASYSCTL_TEST_NODE_VREFLOAC", displayName: "VREFLOAC pin voltage" },
	{ name: "ASYSCTL_TEST_NODE_CDAC1H", displayName: "CMPSS1 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC1L", displayName: "CMPSS1 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC2H", displayName: "CMPSS2 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC2L", displayName: "CMPSS2 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC3H", displayName: "CMPSS3 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC3L", displayName: "CMPSS3 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC4H", displayName: "CMPSS4 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC4L", displayName: "CMPSS4 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CMPSS1", displayName: "CMPSS1 output" },
	{ name: "ASYSCTL_TEST_NODE_ADC", displayName: "ADC output" },
	{ name: "ASYSCTL_TEST_NODE_COMP_DAC_BUF", displayName: "COMP DAC Buffer output" },
	{ name: "ASYSCTL_TEST_NODE_PGA1", displayName: "PGA1 output" },
	{ name: "ASYSCTL_TEST_NODE_ADCCIO", displayName: "ADCCIO output" },
]
let ASYSCTL_CMPSS3_DACL = [
	{ name: "ASYSCTL_CMPSS3_DACL", displayName: "CMPSS3.DACL" },
]
let ASYSCTL_CMPHNMUX_SELECT = [
	{ name: "ASYSCTL_CMPHNMUX_SELECT_1", displayName: "CMPHNMUX select 1" },
	{ name: "ASYSCTL_CMPHNMUX_SELECT_2", displayName: "CMPHNMUX select 2" },
	{ name: "ASYSCTL_CMPHNMUX_SELECT_3", displayName: "CMPHNMUX select 3" },
]
let ASYSCTL_CMPLNMUX_SELECT = [
	{ name: "ASYSCTL_CMPLNMUX_SELECT_1", displayName: "CMPLNMUX select 1" },
	{ name: "ASYSCTL_CMPLNMUX_SELECT_2", displayName: "CMPLNMUX select 2" },
	{ name: "ASYSCTL_CMPLNMUX_SELECT_3", displayName: "CMPLNMUX select 3" },
]
module.exports = {
	ASysCtl_CMPHPMuxSelect: ASysCtl_CMPHPMuxSelect,
	ASysCtl_CMPLPMuxSelect: ASysCtl_CMPLPMuxSelect,
	ASysCtl_TestSelect: ASysCtl_TestSelect,
	ASYSCTL_CMPSS3_DACL: ASYSCTL_CMPSS3_DACL,
	ASYSCTL_CMPHNMUX_SELECT: ASYSCTL_CMPHNMUX_SELECT,
	ASYSCTL_CMPLNMUX_SELECT: ASYSCTL_CMPLNMUX_SELECT,
}
