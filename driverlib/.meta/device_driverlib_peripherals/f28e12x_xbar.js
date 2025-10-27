let XBAR_MUXES = [
	{ name: "XBAR_MUX00", displayName:"MUX 00" },
	{ name: "XBAR_MUX01", displayName:"MUX 01" },
	{ name: "XBAR_MUX02", displayName:"MUX 02" },
	{ name: "XBAR_MUX03", displayName:"MUX 03" },
	{ name: "XBAR_MUX04", displayName:"MUX 04" },
	{ name: "XBAR_MUX05", displayName:"MUX 05" },
	{ name: "XBAR_MUX06", displayName:"MUX 06" },
	{ name: "XBAR_MUX07", displayName:"MUX 07" },
	{ name: "XBAR_MUX08", displayName:"MUX 08" },
	{ name: "XBAR_MUX09", displayName:"MUX 09" },
	{ name: "XBAR_MUX10", displayName:"MUX 10" },
	{ name: "XBAR_MUX11", displayName:"MUX 11" },
	{ name: "XBAR_MUX12", displayName:"MUX 12" },
	{ name: "XBAR_MUX13", displayName:"MUX 13" },
	{ name: "XBAR_MUX14", displayName:"MUX 14" },
	{ name: "XBAR_MUX15", displayName:"MUX 15" },
	{ name: "XBAR_MUX16", displayName:"MUX 16" },
	{ name: "XBAR_MUX17", displayName:"MUX 17" },
	{ name: "XBAR_MUX18", displayName:"MUX 18" },
	{ name: "XBAR_MUX19", displayName:"MUX 19" },
	{ name: "XBAR_MUX20", displayName:"MUX 20" },
	{ name: "XBAR_MUX21", displayName:"MUX 21" },
	{ name: "XBAR_MUX22", displayName:"MUX 22" },
	{ name: "XBAR_MUX23", displayName:"MUX 23" },
	{ name: "XBAR_MUX24", displayName:"MUX 24" },
	{ name: "XBAR_MUX25", displayName:"MUX 25" },
	{ name: "XBAR_MUX26", displayName:"MUX 26" },
	{ name: "XBAR_MUX27", displayName:"MUX 27" },
	{ name: "XBAR_MUX28", displayName:"MUX 28" },
	{ name: "XBAR_MUX29", displayName:"MUX 29" },
	{ name: "XBAR_MUX30", displayName:"MUX 30" },
	{ name: "XBAR_MUX31", displayName:"MUX 31" },
]
let XBAR_OutputNum = [
	{ name: "XBAR_OUTPUT1", displayName: "OUTPUT1 of the Output X-BAR" },
	{ name: "XBAR_OUTPUT2", displayName: "OUTPUT2 of the Output X-BAR" },
	{ name: "XBAR_OUTPUT3", displayName: "OUTPUT3 of the Output X-BAR" },
	{ name: "XBAR_OUTPUT4", displayName: "OUTPUT4 of the Output X-BAR" },
	{ name: "XBAR_OUTPUT5", displayName: "OUTPUT5 of the Output X-BAR" },
	{ name: "XBAR_OUTPUT6", displayName: "OUTPUT6 of the Output X-BAR" },
	{ name: "XBAR_OUTPUT7", displayName: "OUTPUT7 of the Output X-BAR" },
	{ name: "XBAR_OUTPUT8", displayName: "OUTPUT8 of the Output X-BAR" },
]
let XBAR_TripNum = [
	{ name: "XBAR_TRIP1", displayName: "TRIP1 of the PWM X-BAR" },
	{ name: "XBAR_TRIP2", displayName: "TRIP2 of the PWM X-BAR" },
	{ name: "XBAR_TRIP3", displayName: "TRIP3 of the PWM X-BAR" },
	{ name: "XBAR_TRIP4", displayName: "TRIP4 of the PWM X-BAR" },
	{ name: "XBAR_TRIP5", displayName: "TRIP5 of the PWM X-BAR" },
	{ name: "XBAR_TRIP6", displayName: "TRIP6 of the PWM X-BAR" },
	{ name: "XBAR_TRIP7", displayName: "TRIP7 of the PWM X-BAR" },
	{ name: "XBAR_TRIP8", displayName: "TRIP8 of the PWM X-BAR" },
]
let XBAR_AuxSigNum = [
	{ name: "XBAR_AUXSIG0", displayName: "AUXSIG0" },
	{ name: "XBAR_AUXSIG1", displayName: "AUXSIG1" },
	{ name: "XBAR_AUXSIG2", displayName: "AUXSIG2" },
	{ name: "XBAR_AUXSIG3", displayName: "AUXSIG3" },
	{ name: "XBAR_AUXSIG4", displayName: "AUXSIG4" },
	{ name: "XBAR_AUXSIG5", displayName: "AUXSIG5" },
	{ name: "XBAR_AUXSIG6", displayName: "AUXSIG6" },
	{ name: "XBAR_AUXSIG7", displayName: "AUXSIG7" },
]
let XBAR_InputNum = [
	{ name: "XBAR_INPUT1", displayName: "ECAP, X-BARs, OUTPUT XBAR" },
	{ name: "XBAR_INPUT2", displayName: "ECAP, X-BARs, OUTPUT XBAR" },
	{ name: "XBAR_INPUT3", displayName: "ECAP, X-BARs, OUTPUT XBAR" },
	{ name: "XBAR_INPUT4", displayName: "ECAP, X-BARs, OUTPUT XBAR, CPU XINT[XINT1]" },
	{ name: "XBAR_INPUT5", displayName: "ECAP, X-BARs, OUTPUT XBAR, CPU XINT[XINT2], ADC START OF CONVERSION[ADCEXTSOC], MCPWM / ECAP SYNC[EXTSYNCIN1]" },
	{ name: "XBAR_INPUT6", displayName: "ECAP, X-BARs, OUTPUT XBAR, CPU XINT[XINT3], MCPWM / ECAP SYNC[EXTSYNCIN2]" },
	{ name: "XBAR_INPUT7", displayName: "ECAP, X-BARs, CMPSS[CMPSS1_EXT_FILTIN_H[1] / CMPSS3_EXT_FILTIN_H[1]]" },
	{ name: "XBAR_INPUT8", displayName: "ECAP, X-BARs, CMPSS[CMPSS1_EXT_FILTIN_L[1] / CMPSS3_EXT_FILTIN_L[1]]" },
	{ name: "XBAR_INPUT9", displayName: "ECAP, X-BARs, CMPSS[CMPSS2_EXT_FILTIN_H[1]]" },
	{ name: "XBAR_INPUT10", displayName: "ECAP, X-BARs, CMPSS[CMPSS2_EXT_FILTIN_L[1]]" },
	{ name: "XBAR_INPUT11", displayName: "ECAP, X-BARs, DCCx[CLK1]" },
	{ name: "XBAR_INPUT12", displayName: "ECAP, X-BARs, DCCx[CLK1]" },
	{ name: "XBAR_INPUT13", displayName: "ECAP, X-BARs, CPU XINT[XINT4]" },
	{ name: "XBAR_INPUT14", displayName: "ECAP, X-BARs, CPU XINT[XINT5]" },
	{ name: "XBAR_INPUT15", displayName: "ECAP, DCCx[CLK1]" },
	{ name: "XBAR_INPUT16", displayName: "ECAP DCCx[CLK0]" },
]
let XBAR_OutputMuxConfig = [
	{ name: "XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH", displayName: "CMPSS1 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH_OR_L", displayName: "CMPSS1 CTRIPOUTH OR CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX00_ADCAEVT1", displayName: "ADCAEVT1" },
	{ name: "XBAR_OUT_MUX00_ECAP1_OUT", displayName: "ECAP1 OUT" },
	{ name: "XBAR_OUT_MUX01_CMPSS1_CTRIPOUTL", displayName: "CMPSS1 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX01_INPUTXBAR1", displayName: "INPUTXBAR1" },
	{ name: "XBAR_OUT_MUX02_CMPSS2_CTRIPOUTH", displayName: "CMPSS2 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX02_CMPSS2_CTRIPOUTH_OR_L", displayName: "CMPSS2 CTRIPOUTH OR CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX02_ADCAEVT2", displayName: "ADCAEVT2" },
	{ name: "XBAR_OUT_MUX02_ECAP2_OUT", displayName: "ECAP2 OUT" },
	{ name: "XBAR_OUT_MUX03_CMPSS2_CTRIPOUTL", displayName: "CMPSS2 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX03_INPUTXBAR2", displayName: "INPUTXBAR" },
	{ name: "XBAR_OUT_MUX04_CMPSS3_CTRIPOUTH", displayName: "CMPSS3 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX04_CMPSS3_CTRIPOUTH_OR_L", displayName: "CMPSS3 CTRIPOUTH OR CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX04_ADCAEVT3", displayName: "ADCAEVT3" },
	{ name: "XBAR_OUT_MUX05_CMPSS3_CTRIPOUTL", displayName: "CMPSS3 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX05_INPUTXBAR3", displayName: "INPUTXBAR3" },
	{ name: "XBAR_OUT_MUX07_INPUTXBAR4", displayName: "INPUTXBAR4" },
	{ name: "XBAR_OUT_MUX08_INPUTXBAR5", displayName: "INPUTXBAR5" },
	{ name: "XBAR_OUT_MUX08_ADCSOCA", displayName: "ADCSOCA" },
	{ name: "XBAR_OUT_MUX09_EXTSYNCOUT", displayName: "EXTSYNCOUT" },
	{ name: "XBAR_OUT_MUX10_INPUTXBAR6", displayName: "INPUTXBAR6" },
	{ name: "XBAR_OUT_MUX10_ADCSOCB", displayName: "ADCSOCB" },
	{ name: "XBAR_OUT_MUX11_ERRORSTS", displayName: "ERRORSTS" },
]
let XBAR_PWMMuxConfig = [
	{ name: "XBAR_PWM_MUX00_CMPSS1_CTRIPH", displayName: "CMPSS1 CTRIPH" },
	{ name: "XBAR_PWM_MUX00_CMPSS1_CTRIPH_OR_L", displayName: "CMPSS1 CTRIPH OR L" },
	{ name: "XBAR_PWM_MUX00_ADCAEVT1", displayName: "ADCAEVT1" },
	{ name: "XBAR_PWM_MUX00_ECAP1_OUT", displayName: "ECAP1 OUT" },
	{ name: "XBAR_PWM_MUX01_CMPSS1_CTRIPL", displayName: "CMPSS1 CTRIPL" },
	{ name: "XBAR_PWM_MUX01_INPUTXBAR_INPUT1", displayName: "INPUTXBAR INPUT1" },
	{ name: "XBAR_PWM_MUX02_CMPSS2_CTRIPH", displayName: "CMPSS2 CTRIPH" },
	{ name: "XBAR_PWM_MUX02_CMPSS2_CTRIPH_OR_L", displayName: "CMPSS2 CTRIPH OR L" },
	{ name: "XBAR_PWM_MUX02_ADCAEVT2", displayName: "ADCAEVT2" },
	{ name: "XBAR_PWM_MUX02_ECAP2_OUT", displayName: "ECAP2 OUT" },
	{ name: "XBAR_PWM_MUX03_CMPSS2_CTRIPL", displayName: "CMPSS2 CTRIPL" },
	{ name: "XBAR_PWM_MUX03_INPUTXBAR_INPUT2", displayName: "INPUTXBAR INPUT2" },
	{ name: "XBAR_PWM_MUX04_CMPSS3_CTRIPH", displayName: "CMPSS3 CTRIPH" },
	{ name: "XBAR_PWM_MUX04_CMPSS3_CTRIPH_OR_L", displayName: "CMPSS3 CTRIPH OR L" },
	{ name: "XBAR_PWM_MUX04_ADCAEVT3", displayName: "ADCAEVT3" },
	{ name: "XBAR_PWM_MUX05_CMPSS3_CTRIPL", displayName: "CMPSS3 CTRIPL" },
	{ name: "XBAR_PWM_MUX05_INPUTXBAR_INPUT3", displayName: "INPUTXBAR INPUT3" },
	{ name: "XBAR_PWM_MUX07_INPUTXBAR_INPUT4", displayName: "INPUTXBAR INPUT4" },
	{ name: "XBAR_PWM_MUX08_INPUTXBAR_INPUT5", displayName: "INPUTXBAR INPUT5" },
	{ name: "XBAR_PWM_MUX09_INPUTXBAR_INPUT6", displayName: "INPUTXBAR INPUT6" },
	{ name: "XBAR_PWM_MUX09_EMU_STOP", displayName: "EMU STOP signal" },
	{ name: "XBAR_PWM_MUX10_INPUTXBAR_INPUT7", displayName: "INPUTXBAR INPUT7" },
	{ name: "XBAR_PWM_MUX10_ADCSOCA", displayName: "ADCSOCA" },
	{ name: "XBAR_PWM_MUX11_INPUTXBAR_INPUT8", displayName: "INPUTXBAR INPUT8" },
	{ name: "XBAR_PWM_MUX11_EXTSYNCOUT", displayName: "EXTSYNCOUT" },
	{ name: "XBAR_PWM_MUX12_INPUTXBAR_INPUT9", displayName: "INPUTXBAR INPUT9" },
	{ name: "XBAR_PWM_MUX12_ADCSOCB", displayName: "ADCSOCB" },
	{ name: "XBAR_PWM_MUX13_INPUTXBAR_INPUT10", displayName: "INPUTXBAR INPUT10" },
	{ name: "XBAR_PWM_MUX13_EQEP1_ERROR", displayName: "EQEP Error Signal" },
	{ name: "XBAR_PWM_MUX14_INPUTXBAR_INPUT11", displayName: "INPUTXBAR INPUT11" },
	{ name: "XBAR_PWM_MUX14_CLOCKFAIL", displayName: "Missing Clock Detect Signal" },
	{ name: "XBAR_PWM_MUX15_INPUTXBAR_INPUT12", displayName: "INPUTXBAR INPUT12" },
	{ name: "XBAR_PWM_MUX15_ECCDBLERR", displayName: "ECCDBLERR" },
	{ name: "XBAR_PWM_MUX16_INPUTXBAR_INPUT13", displayName: "INPUTXBAR INPUT13" },
	{ name: "XBAR_PWM_MUX16_PIEERR", displayName: "PIE Error Signal" },
	{ name: "XBAR_PWM_MUX17_INPUTXBAR_INPUT14", displayName: "INPUTXBAR INPUT14" },
	{ name: "XBAR_PWM_MUX17_ERRORSTS", displayName: "ERRORSTS" },
]
let XBAR_InputFlag = [
	{ name: "XBAR_INPUT_FLG_CMPSS1_CTRIPL", displayName: "INPUT FLG CMPSS1 CTRIPL" },
	{ name: "XBAR_INPUT_FLG_CMPSS1_CTRIPH", displayName: "INPUT FLG CMPSS1 CTRIPH" },
	{ name: "XBAR_INPUT_FLG_CMPSS2_CTRIPL", displayName: "INPUT FLG CMPSS2 CTRIPL" },
	{ name: "XBAR_INPUT_FLG_CMPSS2_CTRIPH", displayName: "INPUT FLG CMPSS2 CTRIPH" },
	{ name: "XBAR_INPUT_FLG_CMPSS3_CTRIPL", displayName: "INPUT FLG CMPSS3 CTRIPL" },
	{ name: "XBAR_INPUT_FLG_CMPSS3_CTRIPH", displayName: "INPUT FLG CMPSS3 CTRIPH" },
	{ name: "XBAR_INPUT_FLG_CMPSS4_CTRIPL", displayName: "INPUT FLG CMPSS4 CTRIPL" },
	{ name: "XBAR_INPUT_FLG_CMPSS4_CTRIPH", displayName: "INPUT FLG CMPSS4 CTRIPH" },
	{ name: "XBAR_INPUT_FLG_CMPSS1_CTRIPOUTL", displayName: "INPUT FLG CMPSS1 CTRIPOUTL" },
	{ name: "XBAR_INPUT_FLG_CMPSS1_CTRIPOUTH", displayName: "INPUT FLG CMPSS1 CTRIPOUTH" },
	{ name: "XBAR_INPUT_FLG_CMPSS2_CTRIPOUTL", displayName: "INPUT FLG CMPSS2 CTRIPOUTL" },
	{ name: "XBAR_INPUT_FLG_CMPSS2_CTRIPOUTH", displayName: "INPUT FLG CMPSS2 CTRIPOUTH" },
	{ name: "XBAR_INPUT_FLG_CMPSS3_CTRIPOUTL", displayName: "INPUT FLG CMPSS3 CTRIPOUTL" },
	{ name: "XBAR_INPUT_FLG_CMPSS3_CTRIPOUTH", displayName: "INPUT FLG CMPSS3 CTRIPOUTH" },
	{ name: "XBAR_INPUT_FLG_CMPSS4_CTRIPOUTL", displayName: "INPUT FLG CMPSS4 CTRIPOUTL" },
	{ name: "XBAR_INPUT_FLG_CMPSS4_CTRIPOUTH", displayName: "INPUT FLG CMPSS4 CTRIPOUTH" },
	{ name: "XBAR_INPUT_FLG_INPUT1", displayName: "INPUT FLG INPUT1" },
	{ name: "XBAR_INPUT_FLG_INPUT2", displayName: "INPUT FLG INPUT2" },
	{ name: "XBAR_INPUT_FLG_INPUT3", displayName: "INPUT FLG INPUT3" },
	{ name: "XBAR_INPUT_FLG_INPUT4", displayName: "INPUT FLG INPUT4" },
	{ name: "XBAR_INPUT_FLG_INPUT5", displayName: "INPUT FLG INPUT5" },
	{ name: "XBAR_INPUT_FLG_INPUT6", displayName: "INPUT FLG INPUT6" },
	{ name: "XBAR_INPUT_FLG_ADCSOCA", displayName: "INPUT FLG ADCSOCA" },
	{ name: "XBAR_INPUT_FLG_ADCSOCB", displayName: "INPUT FLG ADCSOCB" },
	{ name: "XBAR_INPUT_FLG_INPUT7", displayName: "INPUT FLG INPUT7" },
	{ name: "XBAR_INPUT_FLG_INPUT8", displayName: "INPUT FLG INPUT8" },
	{ name: "XBAR_INPUT_FLG_INPUT9", displayName: "INPUT FLG INPUT9" },
	{ name: "XBAR_INPUT_FLG_INPUT10", displayName: "INPUT FLG INPUT10" },
	{ name: "XBAR_INPUT_FLG_INPUT11", displayName: "INPUT FLG INPUT11" },
	{ name: "XBAR_INPUT_FLG_INPUT12", displayName: "INPUT FLG INPUT12" },
	{ name: "XBAR_INPUT_FLG_INPUT13", displayName: "INPUT FLG INPUT13" },
	{ name: "XBAR_INPUT_FLG_INPUT14", displayName: "INPUT FLG INPUT14" },
	{ name: "XBAR_INPUT_FLG_ECAP1_OUT", displayName: "INPUT FLG ECAP1 OUT" },
	{ name: "XBAR_INPUT_FLG_ECAP2_OUT", displayName: "INPUT FLG ECAP2 OUT" },
	{ name: "XBAR_INPUT_FLG_EXTSYNCOUT", displayName: "INPUT FLG EXTSYNCOUT" },
	{ name: "XBAR_INPUT_FLG_ADCAEVT1", displayName: "INPUT FLG ADCAEVT1" },
	{ name: "XBAR_INPUT_FLG_ADCAEVT2", displayName: "INPUT FLG ADCAEVT2" },
	{ name: "XBAR_INPUT_FLG_ADCAEVT3", displayName: "INPUT FLG ADCAEVT3" },
	{ name: "XBAR_INPUT_FLG_ADCCEVT1", displayName: "INPUT FLG ADCCEVT1" },
	{ name: "XBAR_INPUT_FLG_ADCCEVT2", displayName: "INPUT FLG ADCCEVT2" },
	{ name: "XBAR_INPUT_FLG_ADCCEVT3", displayName: "INPUT FLG ADCCEVT3" },
	{ name: "XBAR_INPUT_FLG_ERRORSTS_ERROR", displayName: "INPUT FLG ERRORSTS ERROR" },
	{ name: "XBAR_INPUT_FLG_EMUSTOP", displayName: "INPUT FLG EMUSTOP" },
	{ name: "XBAR_INPUT_FLG_EQEP1ERR", displayName: "INPUT FLG EQEP1ERR" },
	{ name: "XBAR_INPUT_FLG_CLOCKFAIL", displayName: "INPUT FLG CLOCKFAIL" },
	{ name: "XBAR_INPUT_FLG_ECCDBLERR", displayName: "INPUT FLG ECCDBLERR" },
	{ name: "XBAR_INPUT_FLG_PIEERR", displayName: "INPUT FLG PIEERR" },
]

// MUX Specific Configs
let XBAR_OutputMuxConfig_MUX00 = [
	{ name: "XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH", displayName: "CMPSS1 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH_OR_L", displayName: "CMPSS1 CTRIPOUTH OR CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX00_ADCAEVT1", displayName: "ADCAEVT1" },
	{ name: "XBAR_OUT_MUX00_ECAP1_OUT", displayName: "ECAP1 OUT" },
]
let XBAR_OutputMuxConfig_MUX01 = [
	{ name: "XBAR_OUT_MUX01_CMPSS1_CTRIPOUTL", displayName: "CMPSS1 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX01_INPUTXBAR1", displayName: "INPUTXBAR1" },
]
let XBAR_OutputMuxConfig_MUX02 = [
	{ name: "XBAR_OUT_MUX02_CMPSS2_CTRIPOUTH", displayName: "CMPSS2 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX02_CMPSS2_CTRIPOUTH_OR_L", displayName: "CMPSS2 CTRIPOUTH OR CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX02_ADCAEVT2", displayName: "ADCAEVT2" },
	{ name: "XBAR_OUT_MUX02_ECAP2_OUT", displayName: "ECAP2 OUT" },
]
let XBAR_OutputMuxConfig_MUX03 = [
	{ name: "XBAR_OUT_MUX03_CMPSS2_CTRIPOUTL", displayName: "CMPSS2 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX03_INPUTXBAR2", displayName: "INPUTXBAR" },
]
let XBAR_OutputMuxConfig_MUX04 = [
	{ name: "XBAR_OUT_MUX04_CMPSS3_CTRIPOUTH", displayName: "CMPSS3 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX04_CMPSS3_CTRIPOUTH_OR_L", displayName: "CMPSS3 CTRIPOUTH OR CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX04_ADCAEVT3", displayName: "ADCAEVT3" },
]
let XBAR_OutputMuxConfig_MUX05 = [
	{ name: "XBAR_OUT_MUX05_CMPSS3_CTRIPOUTL", displayName: "CMPSS3 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX05_INPUTXBAR3", displayName: "INPUTXBAR3" },
]
let XBAR_OutputMuxConfig_MUX06 = [
]
let XBAR_OutputMuxConfig_MUX07 = [
	{ name: "XBAR_OUT_MUX07_INPUTXBAR4", displayName: "INPUTXBAR4" },
]
let XBAR_OutputMuxConfig_MUX08 = [
	{ name: "XBAR_OUT_MUX08_INPUTXBAR5", displayName: "INPUTXBAR5" },
	{ name: "XBAR_OUT_MUX08_ADCSOCA", displayName: "ADCSOCA" },
]
let XBAR_OutputMuxConfig_MUX09 = [
	{ name: "XBAR_OUT_MUX09_EXTSYNCOUT", displayName: "EXTSYNCOUT" },
]
let XBAR_OutputMuxConfig_MUX10 = [
	{ name: "XBAR_OUT_MUX10_INPUTXBAR6", displayName: "INPUTXBAR6" },
	{ name: "XBAR_OUT_MUX10_ADCSOCB", displayName: "ADCSOCB" },
]
let XBAR_OutputMuxConfig_MUX11 = [
	{ name: "XBAR_OUT_MUX11_ERRORSTS", displayName: "ERRORSTS" },
]
let XBAR_OutputMuxConfig_MUX12 = [
]
let XBAR_OutputMuxConfig_MUX13 = [
]
let XBAR_OutputMuxConfig_MUX14 = [
]
let XBAR_OutputMuxConfig_MUX15 = [
]
let XBAR_OutputMuxConfig_MUX16 = [
]
let XBAR_OutputMuxConfig_MUX17 = [
]
let XBAR_OutputMuxConfig_MUX18 = [
]
let XBAR_OutputMuxConfig_MUX19 = [
]
let XBAR_OutputMuxConfig_MUX20 = [
]
let XBAR_OutputMuxConfig_MUX21 = [
]
let XBAR_OutputMuxConfig_MUX22 = [
]
let XBAR_OutputMuxConfig_MUX23 = [
]
let XBAR_OutputMuxConfig_MUX24 = [
]
let XBAR_OutputMuxConfig_MUX25 = [
]
let XBAR_OutputMuxConfig_MUX26 = [
]
let XBAR_OutputMuxConfig_MUX27 = [
]
let XBAR_OutputMuxConfig_MUX28 = [
]
let XBAR_OutputMuxConfig_MUX29 = [
]
let XBAR_OutputMuxConfig_MUX30 = [
]
let XBAR_OutputMuxConfig_MUX31 = [
]
let XBAR_OutputMuxConfig_All_MUXES = [
	XBAR_OutputMuxConfig_MUX00,
	XBAR_OutputMuxConfig_MUX01,
	XBAR_OutputMuxConfig_MUX02,
	XBAR_OutputMuxConfig_MUX03,
	XBAR_OutputMuxConfig_MUX04,
	XBAR_OutputMuxConfig_MUX05,
	XBAR_OutputMuxConfig_MUX06,
	XBAR_OutputMuxConfig_MUX07,
	XBAR_OutputMuxConfig_MUX08,
	XBAR_OutputMuxConfig_MUX09,
	XBAR_OutputMuxConfig_MUX10,
	XBAR_OutputMuxConfig_MUX11,
	XBAR_OutputMuxConfig_MUX12,
	XBAR_OutputMuxConfig_MUX13,
	XBAR_OutputMuxConfig_MUX14,
	XBAR_OutputMuxConfig_MUX15,
	XBAR_OutputMuxConfig_MUX16,
	XBAR_OutputMuxConfig_MUX17,
	XBAR_OutputMuxConfig_MUX18,
	XBAR_OutputMuxConfig_MUX19,
	XBAR_OutputMuxConfig_MUX20,
	XBAR_OutputMuxConfig_MUX21,
	XBAR_OutputMuxConfig_MUX22,
	XBAR_OutputMuxConfig_MUX23,
	XBAR_OutputMuxConfig_MUX24,
	XBAR_OutputMuxConfig_MUX25,
	XBAR_OutputMuxConfig_MUX26,
	XBAR_OutputMuxConfig_MUX27,
	XBAR_OutputMuxConfig_MUX28,
	XBAR_OutputMuxConfig_MUX29,
	XBAR_OutputMuxConfig_MUX30,
	XBAR_OutputMuxConfig_MUX31,
]
let XBAR_PWMMuxConfig_MUX00 = [
	{ name: "XBAR_PWM_MUX00_CMPSS1_CTRIPH", displayName: "CMPSS1 CTRIPH" },
	{ name: "XBAR_PWM_MUX00_CMPSS1_CTRIPH_OR_L", displayName: "CMPSS1 CTRIPH OR L" },
	{ name: "XBAR_PWM_MUX00_ADCAEVT1", displayName: "ADCAEVT1" },
	{ name: "XBAR_PWM_MUX00_ECAP1_OUT", displayName: "ECAP1 OUT" },
]
let XBAR_PWMMuxConfig_MUX01 = [
	{ name: "XBAR_PWM_MUX01_CMPSS1_CTRIPL", displayName: "CMPSS1 CTRIPL" },
	{ name: "XBAR_PWM_MUX01_INPUTXBAR_INPUT1", displayName: "INPUTXBAR INPUT1" },
]
let XBAR_PWMMuxConfig_MUX02 = [
	{ name: "XBAR_PWM_MUX02_CMPSS2_CTRIPH", displayName: "CMPSS2 CTRIPH" },
	{ name: "XBAR_PWM_MUX02_CMPSS2_CTRIPH_OR_L", displayName: "CMPSS2 CTRIPH OR L" },
	{ name: "XBAR_PWM_MUX02_ADCAEVT2", displayName: "ADCAEVT2" },
	{ name: "XBAR_PWM_MUX02_ECAP2_OUT", displayName: "ECAP2 OUT" },
]
let XBAR_PWMMuxConfig_MUX03 = [
	{ name: "XBAR_PWM_MUX03_CMPSS2_CTRIPL", displayName: "CMPSS2 CTRIPL" },
	{ name: "XBAR_PWM_MUX03_INPUTXBAR_INPUT2", displayName: "INPUTXBAR INPUT2" },
]
let XBAR_PWMMuxConfig_MUX04 = [
	{ name: "XBAR_PWM_MUX04_CMPSS3_CTRIPH", displayName: "CMPSS3 CTRIPH" },
	{ name: "XBAR_PWM_MUX04_CMPSS3_CTRIPH_OR_L", displayName: "CMPSS3 CTRIPH OR L" },
	{ name: "XBAR_PWM_MUX04_ADCAEVT3", displayName: "ADCAEVT3" },
]
let XBAR_PWMMuxConfig_MUX05 = [
	{ name: "XBAR_PWM_MUX05_CMPSS3_CTRIPL", displayName: "CMPSS3 CTRIPL" },
	{ name: "XBAR_PWM_MUX05_INPUTXBAR_INPUT3", displayName: "INPUTXBAR INPUT3" },
]
let XBAR_PWMMuxConfig_MUX06 = [
]
let XBAR_PWMMuxConfig_MUX07 = [
	{ name: "XBAR_PWM_MUX07_INPUTXBAR_INPUT4", displayName: "INPUTXBAR INPUT4" },
]
let XBAR_PWMMuxConfig_MUX08 = [
	{ name: "XBAR_PWM_MUX08_INPUTXBAR_INPUT5", displayName: "INPUTXBAR INPUT5" },
]
let XBAR_PWMMuxConfig_MUX09 = [
	{ name: "XBAR_PWM_MUX09_INPUTXBAR_INPUT6", displayName: "INPUTXBAR INPUT6" },
	{ name: "XBAR_PWM_MUX09_EMU_STOP", displayName: "EMU STOP signal" },
]
let XBAR_PWMMuxConfig_MUX10 = [
	{ name: "XBAR_PWM_MUX10_INPUTXBAR_INPUT7", displayName: "INPUTXBAR INPUT7" },
	{ name: "XBAR_PWM_MUX10_ADCSOCA", displayName: "ADCSOCA" },
]
let XBAR_PWMMuxConfig_MUX11 = [
	{ name: "XBAR_PWM_MUX11_INPUTXBAR_INPUT8", displayName: "INPUTXBAR INPUT8" },
	{ name: "XBAR_PWM_MUX11_EXTSYNCOUT", displayName: "EXTSYNCOUT" },
]
let XBAR_PWMMuxConfig_MUX12 = [
	{ name: "XBAR_PWM_MUX12_INPUTXBAR_INPUT9", displayName: "INPUTXBAR INPUT9" },
	{ name: "XBAR_PWM_MUX12_ADCSOCB", displayName: "ADCSOCB" },
]
let XBAR_PWMMuxConfig_MUX13 = [
	{ name: "XBAR_PWM_MUX13_INPUTXBAR_INPUT10", displayName: "INPUTXBAR INPUT10" },
	{ name: "XBAR_PWM_MUX13_EQEP1_ERROR", displayName: "EQEP Error Signal" },
]
let XBAR_PWMMuxConfig_MUX14 = [
	{ name: "XBAR_PWM_MUX14_INPUTXBAR_INPUT11", displayName: "INPUTXBAR INPUT11" },
	{ name: "XBAR_PWM_MUX14_CLOCKFAIL", displayName: "Missing Clock Detect Signal" },
]
let XBAR_PWMMuxConfig_MUX15 = [
	{ name: "XBAR_PWM_MUX15_INPUTXBAR_INPUT12", displayName: "INPUTXBAR INPUT12" },
	{ name: "XBAR_PWM_MUX15_ECCDBLERR", displayName: "ECCDBLERR" },
]
let XBAR_PWMMuxConfig_MUX16 = [
	{ name: "XBAR_PWM_MUX16_INPUTXBAR_INPUT13", displayName: "INPUTXBAR INPUT13" },
	{ name: "XBAR_PWM_MUX16_PIEERR", displayName: "PIE Error Signal" },
]
let XBAR_PWMMuxConfig_MUX17 = [
	{ name: "XBAR_PWM_MUX17_INPUTXBAR_INPUT14", displayName: "INPUTXBAR INPUT14" },
	{ name: "XBAR_PWM_MUX17_ERRORSTS", displayName: "ERRORSTS" },
]
let XBAR_PWMMuxConfig_MUX18 = [
]
let XBAR_PWMMuxConfig_MUX19 = [
]
let XBAR_PWMMuxConfig_MUX20 = [
]
let XBAR_PWMMuxConfig_MUX21 = [
]
let XBAR_PWMMuxConfig_MUX22 = [
]
let XBAR_PWMMuxConfig_MUX23 = [
]
let XBAR_PWMMuxConfig_MUX24 = [
]
let XBAR_PWMMuxConfig_MUX25 = [
]
let XBAR_PWMMuxConfig_MUX26 = [
]
let XBAR_PWMMuxConfig_MUX27 = [
]
let XBAR_PWMMuxConfig_MUX28 = [
]
let XBAR_PWMMuxConfig_MUX29 = [
]
let XBAR_PWMMuxConfig_MUX30 = [
]
let XBAR_PWMMuxConfig_MUX31 = [
]
let XBAR_PWMMuxConfig_All_MUXES = [
	XBAR_PWMMuxConfig_MUX00,
	XBAR_PWMMuxConfig_MUX01,
	XBAR_PWMMuxConfig_MUX02,
	XBAR_PWMMuxConfig_MUX03,
	XBAR_PWMMuxConfig_MUX04,
	XBAR_PWMMuxConfig_MUX05,
	XBAR_PWMMuxConfig_MUX06,
	XBAR_PWMMuxConfig_MUX07,
	XBAR_PWMMuxConfig_MUX08,
	XBAR_PWMMuxConfig_MUX09,
	XBAR_PWMMuxConfig_MUX10,
	XBAR_PWMMuxConfig_MUX11,
	XBAR_PWMMuxConfig_MUX12,
	XBAR_PWMMuxConfig_MUX13,
	XBAR_PWMMuxConfig_MUX14,
	XBAR_PWMMuxConfig_MUX15,
	XBAR_PWMMuxConfig_MUX16,
	XBAR_PWMMuxConfig_MUX17,
	XBAR_PWMMuxConfig_MUX18,
	XBAR_PWMMuxConfig_MUX19,
	XBAR_PWMMuxConfig_MUX20,
	XBAR_PWMMuxConfig_MUX21,
	XBAR_PWMMuxConfig_MUX22,
	XBAR_PWMMuxConfig_MUX23,
	XBAR_PWMMuxConfig_MUX24,
	XBAR_PWMMuxConfig_MUX25,
	XBAR_PWMMuxConfig_MUX26,
	XBAR_PWMMuxConfig_MUX27,
	XBAR_PWMMuxConfig_MUX28,
	XBAR_PWMMuxConfig_MUX29,
	XBAR_PWMMuxConfig_MUX30,
	XBAR_PWMMuxConfig_MUX31,
]
module.exports = {
	XBAR_MUXES: XBAR_MUXES,
	XBAR_OutputNum: XBAR_OutputNum,
	XBAR_TripNum: XBAR_TripNum,
	XBAR_AuxSigNum: XBAR_AuxSigNum,
	XBAR_InputNum: XBAR_InputNum,
	XBAR_OutputMuxConfig: XBAR_OutputMuxConfig,
	XBAR_PWMMuxConfig: XBAR_PWMMuxConfig,
	XBAR_InputFlag: XBAR_InputFlag,
	XBAR_OutputMuxConfig_All_MUXES: XBAR_OutputMuxConfig_All_MUXES,
	XBAR_PWMMuxConfig_All_MUXES: XBAR_PWMMuxConfig_All_MUXES,
}
