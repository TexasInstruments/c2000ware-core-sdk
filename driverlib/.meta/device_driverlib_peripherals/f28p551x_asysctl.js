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
let ASysCtl_AdcInst = [
	{ name: "ASYSCTL_ADCA", displayName: "Select ADCA instance" },
	{ name: "ASYSCTL_ADCB", displayName: "Select ADCB instance" },
	{ name: "ASYSCTL_ADCC", displayName: "Select ADCC instance" },
	{ name: "ASYSCTL_ADCD", displayName: "Select ADCD instance" },
	{ name: "ASYSCTL_ADCE", displayName: "Select ADCE instance" },
]
let ASysCtl_ADCTestMuxMode = [
	{ name: "ASYSCTL_TESTANA0_TESTANA1_DISABLE", displayName: "TESTANA0 and TESTANA1" },
	{ name: "ASYSCTL_TESTANA1_ENABLE", displayName: "TESTANA0 is disabled and" },
	{ name: "ASYSCTL_TESTANA0_ENABLE", displayName: "TESTANA0 is enabled and" },
	{ name: "ASYSCTL_TESTANA0_TESTANA1_ENABLE", displayName: "TESTANA0 and TESTANA1" },
]
let ASysCtl_TestSelect = [
	{ name: "ASYSCTL_TEST_NODE_NO_CONN", displayName: "No Internal Connection" },
	{ name: "ASYSCTL_TEST_NODE_VDDCORE", displayName: "Core VDD (1.2V) voltage" },
	{ name: "ASYSCTL_TEST_NODE_VDDA", displayName: "VDDA voltage" },
	{ name: "ASYSCTL_TEST_NODE_VSSA", displayName: "VSSA - Analog ground pin" },
	{ name: "ASYSCTL_TEST_NODE_VREFLO", displayName: "VREFLO pin voltage" },
	{ name: "ASYSCTL_TEST_NODE_CDAC1H", displayName: "CMPSS1 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC1L", displayName: "CMPSS1 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC2H", displayName: "CMPSS2 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC2L", displayName: "CMPSS2 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC3H", displayName: "CMPSS3 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC3L", displayName: "CMPSS3 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC4H", displayName: "CMPSS4 High DAC output" },
	{ name: "ASYSCTL_TEST_NODE_CDAC4L", displayName: "CMPSS4 Low DAC output" },
	{ name: "ASYSCTL_TEST_NODE_ENZ_CALIB_GAIN_3P3V", displayName: "All ADCs are placed in gain" },
]
let AsysCtl_IO_Drvsel_GPIO = [
	{ name: "ASYSCTL_IO_DRVSEL_GPIO2", displayName: "IO DRVSEL GPIO2" },
	{ name: "ASYSCTL_IO_DRVSEL_GPIO3", displayName: "IO DRVSEL GPIO3" },
	{ name: "ASYSCTL_IO_DRVSEL_GPIO9", displayName: "IO DRVSEL GPIO9" },
	{ name: "ASYSCTL_IO_DRVSEL_GPIO32", displayName: "IO DRVSEL GPIO32" },
]
let AsysCtl_IO_Modesel_GPIO = [
	{ name: "ASYSCTL_IO_MODESEL_GPIO2", displayName: "IO MODESEL GPIO2" },
	{ name: "ASYSCTL_IO_MODESEL_GPIO3", displayName: "IO MODESEL GPIO3" },
	{ name: "ASYSCTL_IO_MODESEL_GPIO9", displayName: "IO MODESEL GPIO9" },
	{ name: "ASYSCTL_IO_MODESEL_GPIO32", displayName: "IO MODESEL GPIO32" },
]
let ASYSCTL_ANAREF_INTREF = [
	{ name: "ASYSCTL_ANAREF_INTREF_ADCA", displayName: "INTREFA" },
	{ name: "ASYSCTL_ANAREF_INTREF_ADCB", displayName: "INTREFB" },
	{ name: "ASYSCTL_ANAREF_INTREF_ADCC", displayName: "INTREFC" },
	{ name: "ASYSCTL_ANAREF_INTREF_ADCD", displayName: "INTREFD" },
	{ name: "ASYSCTL_ANAREF_INTREF_ADCE", displayName: "INTREFE" },
]
let ASYSCTL_ANAREF_VREFHI = [
	{ name: "ASYSCTL_ANAREF_VREFHI_ADCA", displayName: "VREFHIA" },
	{ name: "ASYSCTL_ANAREF_VREFHI_ADCB", displayName: "VREFHIB" },
	{ name: "ASYSCTL_ANAREF_VREFHI_ADCC", displayName: "VREFHIC" },
	{ name: "ASYSCTL_ANAREF_VREFHI_ADCD", displayName: "VREFHID" },
	{ name: "ASYSCTL_ANAREF_VREFHI_ADCE", displayName: "VREFHIE" },
]
let ASYSCTL_ANAREF_VDDA = [
	{ name: "ASYSCTL_ANAREF_VDDA_ADCA", displayName: "VDDAA" },
	{ name: "ASYSCTL_ANAREF_VDDA_ADCB", displayName: "VDDAB" },
	{ name: "ASYSCTL_ANAREF_VDDA_ADCC", displayName: "VDDAC" },
	{ name: "ASYSCTL_ANAREF_VDDA_ADCD", displayName: "VDDAD" },
	{ name: "ASYSCTL_ANAREF_VDDA_ADCE", displayName: "VDDAE" },
]
let ASYSCTL_ANAREF = [
	{ name: "ASYSCTL_ANAREF_ADCA", displayName: "ANAREFA" },
	{ name: "ASYSCTL_ANAREF_ADCB", displayName: "ANAREFB" },
	{ name: "ASYSCTL_ANAREF_ADCC", displayName: "ANAREFC" },
	{ name: "ASYSCTL_ANAREF_ADCD", displayName: "ANAREFD" },
	{ name: "ASYSCTL_ANAREF_ADCE", displayName: "ANAREFE" },
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
	ASysCtl_AdcInst: ASysCtl_AdcInst,
	ASysCtl_ADCTestMuxMode: ASysCtl_ADCTestMuxMode,
	ASysCtl_TestSelect: ASysCtl_TestSelect,
	AsysCtl_IO_Drvsel_GPIO: AsysCtl_IO_Drvsel_GPIO,
	AsysCtl_IO_Modesel_GPIO: AsysCtl_IO_Modesel_GPIO,
	ASYSCTL_ANAREF_INTREF: ASYSCTL_ANAREF_INTREF,
	ASYSCTL_ANAREF_VREFHI: ASYSCTL_ANAREF_VREFHI,
	ASYSCTL_ANAREF_VDDA: ASYSCTL_ANAREF_VDDA,
	ASYSCTL_ANAREF: ASYSCTL_ANAREF,
	ASYSCTL_CMPSS1_DACL: ASYSCTL_CMPSS1_DACL,
	ASYSCTL_CMPHNMUX_SELECT: ASYSCTL_CMPHNMUX_SELECT,
	ASYSCTL_CMPLNMUX_SELECT: ASYSCTL_CMPLNMUX_SELECT,
}
