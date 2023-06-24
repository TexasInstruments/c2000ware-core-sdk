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
	{ name: "XBAR_TRIP4", displayName: "TRIP4 of the ePWM X-BAR" },
	{ name: "XBAR_TRIP5", displayName: "TRIP5 of the ePWM X-BAR" },
	{ name: "XBAR_TRIP7", displayName: "TRIP7 of the ePWM X-BAR" },
	{ name: "XBAR_TRIP8", displayName: "TRIP8 of the ePWM X-BAR" },
	{ name: "XBAR_TRIP9", displayName: "TRIP9 of the ePWM X-BAR" },
	{ name: "XBAR_TRIP10", displayName: "TRIP10 of the ePWM X-BAR" },
	{ name: "XBAR_TRIP11", displayName: "TRIP11 of the ePWM X-BAR" },
	{ name: "XBAR_TRIP12", displayName: "TRIP12 of the ePWM X-BAR" },
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
	{ name: "XBAR_INPUT1", displayName: "ePWM[TZ1], ePWM[TRIP1], X-BARs, eCAPs" },
	{ name: "XBAR_INPUT2", displayName: "ePWM[TZ2], ePWM[TRIP2], X-BARs, eCAPs" },
	{ name: "XBAR_INPUT3", displayName: "ePWM[TZ3], ePWM[TRIP3], X-BARs, eCAPs" },
	{ name: "XBAR_INPUT4", displayName: "ADC wrappers, X-BARs, XINT1, eCAPs" },
	{ name: "XBAR_INPUT5", displayName: "EXTSYNCIN1, X-BARs, XINT2, eCAPs" },
	{ name: "XBAR_INPUT6", displayName: "EXTSYNCIN2, ePWM[TRIP6], X-BARs, XINT3, eCAPs" },
	{ name: "XBAR_INPUT7", displayName: "X-BARs, eCAPs" },
	{ name: "XBAR_INPUT8", displayName: "X-BARs, eCAPs" },
	{ name: "XBAR_INPUT9", displayName: "X-BARs, eCAPs" },
	{ name: "XBAR_INPUT10", displayName: "X-BARs, eCAPs" },
	{ name: "XBAR_INPUT11", displayName: "X-BARs, eCAPs" },
	{ name: "XBAR_INPUT12", displayName: "X-BARs, eCAPs" },
	{ name: "XBAR_INPUT13", displayName: "XINT4, X-BARs, eCAPs" },
	{ name: "XBAR_INPUT14", displayName: "XINT5, X-BARs, eCAPs" },
	{ name: "XBAR_INPUT15", displayName: "eCAPs" },
	{ name: "XBAR_INPUT16", displayName: "eCAPs" },
]
let XBAR_OutputMuxConfig = [
	{ name: "XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH", displayName: "OUT MUX00 CMPSS1 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH_OR_L", displayName: "OUT MUX00 CMPSS1 CTRIPOUTH OR L" },
	{ name: "XBAR_OUT_MUX00_ADCAEVT1", displayName: "OUT MUX00 ADCAEVT1" },
	{ name: "XBAR_OUT_MUX00_ECAP1_OUT", displayName: "OUT MUX00 ECAP1 OUT" },
	{ name: "XBAR_OUT_MUX01_CMPSS1_CTRIPOUTL", displayName: "OUT MUX01 CMPSS1 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX01_INPUTXBAR1", displayName: "OUT MUX01 INPUTXBAR1" },
	{ name: "XBAR_OUT_MUX01_CLB1_OUT4", displayName: "OUT MUX01 CLB1 OUT4" },
	{ name: "XBAR_OUT_MUX01_ADCCEVT1", displayName: "OUT MUX01 ADCCEVT1" },
	{ name: "XBAR_OUT_MUX02_CMPSS2_CTRIPOUTH", displayName: "OUT MUX02 CMPSS2 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX02_CMPSS2_CTRIPOUTH_OR_L", displayName: "OUT MUX02 CMPSS2 CTRIPOUTH OR L" },
	{ name: "XBAR_OUT_MUX02_ADCAEVT2", displayName: "OUT MUX02 ADCAEVT2" },
	{ name: "XBAR_OUT_MUX02_ECAP2_OUT", displayName: "OUT MUX02 ECAP2 OUT" },
	{ name: "XBAR_OUT_MUX03_CMPSS2_CTRIPOUTL", displayName: "OUT MUX03 CMPSS2 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX03_INPUTXBAR2", displayName: "OUT MUX03 INPUTXBAR2" },
	{ name: "XBAR_OUT_MUX03_CLB1_OUT5", displayName: "OUT MUX03 CLB1 OUT5" },
	{ name: "XBAR_OUT_MUX03_ADCCEVT2", displayName: "OUT MUX03 ADCCEVT2" },
	{ name: "XBAR_OUT_MUX04_CMPSS3_CTRIPOUTH", displayName: "OUT MUX04 CMPSS3 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX04_CMPSS3_CTRIPOUTH_OR_L", displayName: "OUT MUX04 CMPSS3 CTRIPOUTH OR L" },
	{ name: "XBAR_OUT_MUX04_ADCAEVT3", displayName: "OUT MUX04 ADCAEVT3" },
	{ name: "XBAR_OUT_MUX04_ECAP3_OUT", displayName: "OUT MUX04 ECAP3 OUT" },
	{ name: "XBAR_OUT_MUX05_CMPSS3_CTRIPOUTL", displayName: "OUT MUX05 CMPSS3 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX05_INPUTXBAR3", displayName: "OUT MUX05 INPUTXBAR3" },
	{ name: "XBAR_OUT_MUX05_CLB2_OUT4", displayName: "OUT MUX05 CLB2 OUT4" },
	{ name: "XBAR_OUT_MUX05_ADCCEVT3", displayName: "OUT MUX05 ADCCEVT3" },
	{ name: "XBAR_OUT_MUX06_CMPSS4_CTRIPOUTH", displayName: "OUT MUX06 CMPSS4 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX06_CMPSS4_CTRIPOUTH_OR_L", displayName: "OUT MUX06 CMPSS4 CTRIPOUTH OR L" },
	{ name: "XBAR_OUT_MUX06_ADCAEVT4", displayName: "OUT MUX06 ADCAEVT4" },
	{ name: "XBAR_OUT_MUX07_CMPSS4_CTRIPOUTL", displayName: "OUT MUX07 CMPSS4 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX07_INPUTXBAR4", displayName: "OUT MUX07 INPUTXBAR4" },
	{ name: "XBAR_OUT_MUX07_CLB2_OUT5", displayName: "OUT MUX07 CLB2 OUT5" },
	{ name: "XBAR_OUT_MUX07_ADCCEVT4", displayName: "OUT MUX07 ADCCEVT4" },
	{ name: "XBAR_OUT_MUX09_INPUTXBAR5", displayName: "OUT MUX09 INPUTXBAR5" },
	{ name: "XBAR_OUT_MUX11_INPUTXBAR6", displayName: "OUT MUX11 INPUTXBAR6" },
	{ name: "XBAR_OUT_MUX14_EXTSYNCOUT", displayName: "OUT MUX14 EXTSYNCOUT" },
	{ name: "XBAR_OUT_MUX13_ADCSOCA", displayName: "OUT MUX13 ADCSOCA" },
	{ name: "XBAR_OUT_MUX15_ADCSOCB", displayName: "OUT MUX15 ADCSOCB" },
	{ name: "XBAR_OUT_MUX00_CLB1_OUT0", displayName: "OUT MUX00 CLB1 OUT0" },
	{ name: "XBAR_OUT_MUX01_CLB1_OUT1", displayName: "OUT MUX01 CLB1 OUT1" },
	{ name: "XBAR_OUT_MUX02_CLB1_OUT2", displayName: "OUT MUX02 CLB1 OUT2" },
	{ name: "XBAR_OUT_MUX03_CLB1_OUT3", displayName: "OUT MUX03 CLB1 OUT3" },
	{ name: "XBAR_OUT_MUX04_CLB1_OUT4", displayName: "OUT MUX04 CLB1 OUT4" },
	{ name: "XBAR_OUT_MUX05_CLB1_OUT5", displayName: "OUT MUX05 CLB1 OUT5" },
	{ name: "XBAR_OUT_MUX06_CLB1_OUT6", displayName: "OUT MUX06 CLB1 OUT6" },
	{ name: "XBAR_OUT_MUX07_CLB1_OUT7", displayName: "OUT MUX07 CLB1 OUT7" },
	{ name: "XBAR_OUT_MUX08_CLB2_OUT0", displayName: "OUT MUX08 CLB2 OUT0" },
	{ name: "XBAR_OUT_MUX09_CLB2_OUT1", displayName: "OUT MUX09 CLB2 OUT1" },
	{ name: "XBAR_OUT_MUX10_CLB2_OUT2", displayName: "OUT MUX10 CLB2 OUT2" },
	{ name: "XBAR_OUT_MUX11_CLB2_OUT3", displayName: "OUT MUX11 CLB2 OUT3" },
	{ name: "XBAR_OUT_MUX12_CLB2_OUT4", displayName: "OUT MUX12 CLB2 OUT4" },
	{ name: "XBAR_OUT_MUX13_CLB2_OUT5", displayName: "OUT MUX13 CLB2 OUT5" },
	{ name: "XBAR_OUT_MUX14_CLB2_OUT6", displayName: "OUT MUX14 CLB2 OUT6" },
	{ name: "XBAR_OUT_MUX15_CLB2_OUT7", displayName: "OUT MUX15 CLB2 OUT7" },
]
let XBAR_EPWMMuxConfig = [
	{ name: "XBAR_EPWM_MUX00_CMPSS1_CTRIPH", displayName: "EPWM MUX00 CMPSS1 CTRIPH" },
	{ name: "XBAR_EPWM_MUX00_CMPSS1_CTRIPH_OR_L", displayName: "EPWM MUX00 CMPSS1 CTRIPH OR L" },
	{ name: "XBAR_EPWM_MUX00_ADCAEVT1", displayName: "EPWM MUX00 ADCAEVT1" },
	{ name: "XBAR_EPWM_MUX00_ECAP1_OUT", displayName: "EPWM MUX00 ECAP1 OUT" },
	{ name: "XBAR_EPWM_MUX01_CMPSS1_CTRIPL", displayName: "EPWM MUX01 CMPSS1 CTRIPL" },
	{ name: "XBAR_EPWM_MUX01_INPUTXBAR1", displayName: "EPWM MUX01 INPUTXBAR1" },
	{ name: "XBAR_EPWM_MUX01_CLB1_OUT4", displayName: "EPWM MUX01 CLB1 OUT4" },
	{ name: "XBAR_EPWM_MUX01_ADCCEVT1", displayName: "EPWM MUX01 ADCCEVT1" },
	{ name: "XBAR_EPWM_MUX02_CMPSS2_CTRIPH", displayName: "EPWM MUX02 CMPSS2 CTRIPH" },
	{ name: "XBAR_EPWM_MUX02_CMPSS2_CTRIPH_OR_L", displayName: "EPWM MUX02 CMPSS2 CTRIPH OR L" },
	{ name: "XBAR_EPWM_MUX02_ADCAEVT2", displayName: "EPWM MUX02 ADCAEVT2" },
	{ name: "XBAR_EPWM_MUX02_ECAP2_OUT", displayName: "EPWM MUX02 ECAP2 OUT" },
	{ name: "XBAR_EPWM_MUX03_CMPSS2_CTRIPL", displayName: "EPWM MUX03 CMPSS2 CTRIPL" },
	{ name: "XBAR_EPWM_MUX03_INPUTXBAR2", displayName: "EPWM MUX03 INPUTXBAR2" },
	{ name: "XBAR_EPWM_MUX03_CLB1_OUT5", displayName: "EPWM MUX03 CLB1 OUT5" },
	{ name: "XBAR_EPWM_MUX03_ADCCEVT2", displayName: "EPWM MUX03 ADCCEVT2" },
	{ name: "XBAR_EPWM_MUX04_CMPSS3_CTRIPH", displayName: "EPWM MUX04 CMPSS3 CTRIPH" },
	{ name: "XBAR_EPWM_MUX04_CMPSS3_CTRIPH_OR_L", displayName: "EPWM MUX04 CMPSS3 CTRIPH OR L" },
	{ name: "XBAR_EPWM_MUX04_ADCAEVT3", displayName: "EPWM MUX04 ADCAEVT3" },
	{ name: "XBAR_EPWM_MUX04_ECAP3_OUT", displayName: "EPWM MUX04 ECAP3 OUT" },
	{ name: "XBAR_EPWM_MUX05_CMPSS3_CTRIPL", displayName: "EPWM MUX05 CMPSS3 CTRIPL" },
	{ name: "XBAR_EPWM_MUX05_INPUTXBAR3", displayName: "EPWM MUX05 INPUTXBAR3" },
	{ name: "XBAR_EPWM_MUX05_CLB2_OUT4", displayName: "EPWM MUX05 CLB2 OUT4" },
	{ name: "XBAR_EPWM_MUX05_ADCCEVT3", displayName: "EPWM MUX05 ADCCEVT3" },
	{ name: "XBAR_EPWM_MUX06_CMPSS4_CTRIPH", displayName: "EPWM MUX06 CMPSS4 CTRIPH" },
	{ name: "XBAR_EPWM_MUX06_CMPSS4_CTRIPH_OR_L", displayName: "EPWM MUX06 CMPSS4 CTRIPH OR L" },
	{ name: "XBAR_EPWM_MUX06_ADCAEVT4", displayName: "EPWM MUX06 ADCAEVT4" },
	{ name: "XBAR_EPWM_MUX07_CMPSS4_CTRIPL", displayName: "EPWM MUX07 CMPSS4 CTRIPL" },
	{ name: "XBAR_EPWM_MUX07_INPUTXBAR4", displayName: "EPWM MUX07 INPUTXBAR4" },
	{ name: "XBAR_EPWM_MUX07_CLB2_OUT5", displayName: "EPWM MUX07 CLB2 OUT5" },
	{ name: "XBAR_EPWM_MUX07_ADCCEVT4", displayName: "EPWM MUX07 ADCCEVT4" },
	{ name: "XBAR_EPWM_MUX09_INPUTXBAR5", displayName: "EPWM MUX09 INPUTXBAR5" },
	{ name: "XBAR_EPWM_MUX11_INPUTXBAR6", displayName: "EPWM MUX11 INPUTXBAR6" },
	{ name: "XBAR_EPWM_MUX13_ADCSOCA", displayName: "EPWM MUX13 ADCSOCA" },
	{ name: "XBAR_EPWM_MUX14_EXTSYNCOUT", displayName: "EPWM MUX14 EXTSYNCOUT" },
	{ name: "XBAR_EPWM_MUX15_ADCSOCB", displayName: "EPWM MUX15 ADCSOCB" },
	{ name: "XBAR_EPWM_MUX17_INPUTXBAR7", displayName: "EPWM MUX17 INPUTXBAR7" },
	{ name: "XBAR_EPWM_MUX19_INPUTXBAR8", displayName: "EPWM MUX19 INPUTXBAR8" },
	{ name: "XBAR_EPWM_MUX21_INPUTXBAR9", displayName: "EPWM MUX21 INPUTXBAR9" },
	{ name: "XBAR_EPWM_MUX23_INPUTXBAR10", displayName: "EPWM MUX23 INPUTXBAR10" },
	{ name: "XBAR_EPWM_MUX25_INPUTXBAR11", displayName: "EPWM MUX25 INPUTXBAR11" },
	{ name: "XBAR_EPWM_MUX27_INPUTXBAR12", displayName: "EPWM MUX27 INPUTXBAR12" },
	{ name: "XBAR_EPWM_MUX29_INPUTXBAR13", displayName: "EPWM MUX29 INPUTXBAR13" },
	{ name: "XBAR_EPWM_MUX31_INPUTXBAR14", displayName: "EPWM MUX31 INPUTXBAR14" },
]
let XBAR_CLBMuxConfig = [
	{ name: "XBAR_CLB_MUX00_CMPSS1_CTRIPH", displayName: "CLB MUX00 CMPSS1 CTRIPH" },
	{ name: "XBAR_CLB_MUX00_CMPSS1_CTRIPH_OR_L", displayName: "CLB MUX00 CMPSS1 CTRIPH OR L" },
	{ name: "XBAR_CLB_MUX00_ADCAEVT1", displayName: "CLB MUX00 ADCAEVT1" },
	{ name: "XBAR_CLB_MUX00_ECAP1_OUT", displayName: "CLB MUX00 ECAP1 OUT" },
	{ name: "XBAR_CLB_MUX01_CMPSS1_CTRIPL", displayName: "CLB MUX01 CMPSS1 CTRIPL" },
	{ name: "XBAR_CLB_MUX01_INPUTXBAR1", displayName: "CLB MUX01 INPUTXBAR1" },
	{ name: "XBAR_CLB_MUX01_CLB1_OUT4", displayName: "CLB MUX01 CLB1 OUT4" },
	{ name: "XBAR_CLB_MUX01_ADCCEVT1", displayName: "CLB MUX01 ADCCEVT1" },
	{ name: "XBAR_CLB_MUX02_CMPSS2_CTRIPH", displayName: "CLB MUX02 CMPSS2 CTRIPH" },
	{ name: "XBAR_CLB_MUX02_CMPSS2_CTRIPH_OR_L", displayName: "CLB MUX02 CMPSS2 CTRIPH OR L" },
	{ name: "XBAR_CLB_MUX02_ADCAEVT2", displayName: "CLB MUX02 ADCAEVT2" },
	{ name: "XBAR_CLB_MUX02_ECAP2_OUT", displayName: "CLB MUX02 ECAP2 OUT" },
	{ name: "XBAR_CLB_MUX03_CMPSS2_CTRIPL", displayName: "CLB MUX03 CMPSS2 CTRIPL" },
	{ name: "XBAR_CLB_MUX03_INPUTXBAR2", displayName: "CLB MUX03 INPUTXBAR2" },
	{ name: "XBAR_CLB_MUX03_CLB1_OUT5", displayName: "CLB MUX03 CLB1 OUT5" },
	{ name: "XBAR_CLB_MUX03_ADCCEVT2", displayName: "CLB MUX03 ADCCEVT2" },
	{ name: "XBAR_CLB_MUX04_CMPSS3_CTRIPH", displayName: "CLB MUX04 CMPSS3 CTRIPH" },
	{ name: "XBAR_CLB_MUX04_CMPSS3_CTRIPH_OR_L", displayName: "CLB MUX04 CMPSS3 CTRIPH OR L" },
	{ name: "XBAR_CLB_MUX04_ADCAEVT3", displayName: "CLB MUX04 ADCAEVT3" },
	{ name: "XBAR_CLB_MUX04_ECAP3_OUT", displayName: "CLB MUX04 ECAP3 OUT" },
	{ name: "XBAR_CLB_MUX05_CMPSS3_CTRIPL", displayName: "CLB MUX05 CMPSS3 CTRIPL" },
	{ name: "XBAR_CLB_MUX05_INPUTXBAR3", displayName: "CLB MUX05 INPUTXBAR3" },
	{ name: "XBAR_CLB_MUX05_CLB2_OUT4", displayName: "CLB MUX05 CLB2 OUT4" },
	{ name: "XBAR_CLB_MUX05_ADCCEVT3", displayName: "CLB MUX05 ADCCEVT3" },
	{ name: "XBAR_CLB_MUX06_CMPSS4_CTRIPH", displayName: "CLB MUX06 CMPSS4 CTRIPH" },
	{ name: "XBAR_CLB_MUX06_CMPSS4_CTRIPH_OR_L", displayName: "CLB MUX06 CMPSS4 CTRIPH OR L" },
	{ name: "XBAR_CLB_MUX06_ADCAEVT4", displayName: "CLB MUX06 ADCAEVT4" },
	{ name: "XBAR_CLB_MUX07_CMPSS4_CTRIPL", displayName: "CLB MUX07 CMPSS4 CTRIPL" },
	{ name: "XBAR_CLB_MUX07_INPUTXBAR4", displayName: "CLB MUX07 INPUTXBAR4" },
	{ name: "XBAR_CLB_MUX07_CLB2_OUT5", displayName: "CLB MUX07 CLB2 OUT5" },
	{ name: "XBAR_CLB_MUX07_ADCCEVT4", displayName: "CLB MUX07 ADCCEVT4" },
	{ name: "XBAR_CLB_MUX09_INPUTXBAR5", displayName: "CLB MUX09 INPUTXBAR5" },
	{ name: "XBAR_CLB_MUX11_INPUTXBAR6", displayName: "CLB MUX11 INPUTXBAR6" },
	{ name: "XBAR_CLB_MUX13_ADCSOCA", displayName: "CLB MUX13 ADCSOCA" },
	{ name: "XBAR_CLB_MUX14_EXTSYNCOUT", displayName: "CLB MUX14 EXTSYNCOUT" },
	{ name: "XBAR_CLB_MUX15_ADCSOCB", displayName: "CLB MUX15 ADCSOCB" },
	{ name: "XBAR_CLB_MUX17_INPUTXBAR7", displayName: "CLB MUX17 INPUTXBAR7" },
	{ name: "XBAR_CLB_MUX19_INPUTXBAR8", displayName: "CLB MUX19 INPUTXBAR8" },
	{ name: "XBAR_CLB_MUX21_INPUTXBAR9", displayName: "CLB MUX21 INPUTXBAR9" },
	{ name: "XBAR_CLB_MUX23_INPUTXBAR10", displayName: "CLB MUX23 INPUTXBAR10" },
	{ name: "XBAR_CLB_MUX25_INPUTXBAR11", displayName: "CLB MUX25 INPUTXBAR11" },
	{ name: "XBAR_CLB_MUX27_INPUTXBAR12", displayName: "CLB MUX27 INPUTXBAR12" },
	{ name: "XBAR_CLB_MUX29_INPUTXBAR13", displayName: "CLB MUX29 INPUTXBAR13" },
	{ name: "XBAR_CLB_MUX31_INPUTXBAR14", displayName: "CLB MUX31 INPUTXBAR14" },
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
	{ name: "XBAR_INPUT_FLG_ECAP3_OUT", displayName: "INPUT FLG ECAP3 OUT" },
	{ name: "XBAR_INPUT_FLG_EXTSYNCOUT", displayName: "INPUT FLG EXTSYNCOUT" },
	{ name: "XBAR_INPUT_FLG_ADCAEVT1", displayName: "INPUT FLG ADCAEVT1" },
	{ name: "XBAR_INPUT_FLG_ADCAEVT2", displayName: "INPUT FLG ADCAEVT2" },
	{ name: "XBAR_INPUT_FLG_ADCAEVT3", displayName: "INPUT FLG ADCAEVT3" },
	{ name: "XBAR_INPUT_FLG_ADCAEVT4", displayName: "INPUT FLG ADCAEVT4" },
	{ name: "XBAR_INPUT_FLG_ADCCEVT1", displayName: "INPUT FLG ADCCEVT1" },
	{ name: "XBAR_INPUT_FLG_ADCCEVT2", displayName: "INPUT FLG ADCCEVT2" },
	{ name: "XBAR_INPUT_FLG_ADCCEVT3", displayName: "INPUT FLG ADCCEVT3" },
	{ name: "XBAR_INPUT_FLG_ADCCEVT4", displayName: "INPUT FLG ADCCEVT4" },
	{ name: "XBAR_INPUT_FLG_CLB1_OUT4", displayName: "INPUT FLG CLB1 OUT4" },
	{ name: "XBAR_INPUT_FLG_CLB1_OUT5", displayName: "INPUT FLG CLB1 OUT5" },
	{ name: "XBAR_INPUT_FLG_CLB2_OUT4", displayName: "INPUT FLG CLB2 OUT4" },
	{ name: "XBAR_INPUT_FLG_CLB2_OUT5", displayName: "INPUT FLG CLB2 OUT5" },
]

// MUX Specific Configs
let XBAR_OutputMuxConfig_MUX00 = [
	{ name: "XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH", displayName: "CMPSS1 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX00_CMPSS1_CTRIPOUTH_OR_L", displayName: "CMPSS1 CTRIPOUTH OR L" },
	{ name: "XBAR_OUT_MUX00_ADCAEVT1", displayName: "ADCAEVT1" },
	{ name: "XBAR_OUT_MUX00_ECAP1_OUT", displayName: "ECAP1 OUT" },
	{ name: "XBAR_OUT_MUX00_CLB1_OUT0", displayName: "CLB1 OUT0" },
]
let XBAR_OutputMuxConfig_MUX01 = [
	{ name: "XBAR_OUT_MUX01_CMPSS1_CTRIPOUTL", displayName: "CMPSS1 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX01_INPUTXBAR1", displayName: "INPUTXBAR1" },
	{ name: "XBAR_OUT_MUX01_CLB1_OUT4", displayName: "CLB1 OUT4" },
	{ name: "XBAR_OUT_MUX01_ADCCEVT1", displayName: "ADCCEVT1" },
	{ name: "XBAR_OUT_MUX01_CLB1_OUT1", displayName: "CLB1 OUT1" },
]
let XBAR_OutputMuxConfig_MUX02 = [
	{ name: "XBAR_OUT_MUX02_CMPSS2_CTRIPOUTH", displayName: "CMPSS2 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX02_CMPSS2_CTRIPOUTH_OR_L", displayName: "CMPSS2 CTRIPOUTH OR L" },
	{ name: "XBAR_OUT_MUX02_ADCAEVT2", displayName: "ADCAEVT2" },
	{ name: "XBAR_OUT_MUX02_ECAP2_OUT", displayName: "ECAP2 OUT" },
	{ name: "XBAR_OUT_MUX02_CLB1_OUT2", displayName: "CLB1 OUT2" },
]
let XBAR_OutputMuxConfig_MUX03 = [
	{ name: "XBAR_OUT_MUX03_CMPSS2_CTRIPOUTL", displayName: "CMPSS2 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX03_INPUTXBAR2", displayName: "INPUTXBAR2" },
	{ name: "XBAR_OUT_MUX03_CLB1_OUT5", displayName: "CLB1 OUT5" },
	{ name: "XBAR_OUT_MUX03_ADCCEVT2", displayName: "ADCCEVT2" },
	{ name: "XBAR_OUT_MUX03_CLB1_OUT3", displayName: "CLB1 OUT3" },
]
let XBAR_OutputMuxConfig_MUX04 = [
	{ name: "XBAR_OUT_MUX04_CMPSS3_CTRIPOUTH", displayName: "CMPSS3 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX04_CMPSS3_CTRIPOUTH_OR_L", displayName: "CMPSS3 CTRIPOUTH OR L" },
	{ name: "XBAR_OUT_MUX04_ADCAEVT3", displayName: "ADCAEVT3" },
	{ name: "XBAR_OUT_MUX04_ECAP3_OUT", displayName: "ECAP3 OUT" },
	{ name: "XBAR_OUT_MUX04_CLB1_OUT4", displayName: "CLB1 OUT4" },
]
let XBAR_OutputMuxConfig_MUX05 = [
	{ name: "XBAR_OUT_MUX05_CMPSS3_CTRIPOUTL", displayName: "CMPSS3 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX05_INPUTXBAR3", displayName: "INPUTXBAR3" },
	{ name: "XBAR_OUT_MUX05_CLB2_OUT4", displayName: "CLB2 OUT4" },
	{ name: "XBAR_OUT_MUX05_ADCCEVT3", displayName: "ADCCEVT3" },
	{ name: "XBAR_OUT_MUX05_CLB1_OUT5", displayName: "CLB1 OUT5" },
]
let XBAR_OutputMuxConfig_MUX06 = [
	{ name: "XBAR_OUT_MUX06_CMPSS4_CTRIPOUTH", displayName: "CMPSS4 CTRIPOUTH" },
	{ name: "XBAR_OUT_MUX06_CMPSS4_CTRIPOUTH_OR_L", displayName: "CMPSS4 CTRIPOUTH OR L" },
	{ name: "XBAR_OUT_MUX06_ADCAEVT4", displayName: "ADCAEVT4" },
	{ name: "XBAR_OUT_MUX06_CLB1_OUT6", displayName: "CLB1 OUT6" },
]
let XBAR_OutputMuxConfig_MUX07 = [
	{ name: "XBAR_OUT_MUX07_CMPSS4_CTRIPOUTL", displayName: "CMPSS4 CTRIPOUTL" },
	{ name: "XBAR_OUT_MUX07_INPUTXBAR4", displayName: "INPUTXBAR4" },
	{ name: "XBAR_OUT_MUX07_CLB2_OUT5", displayName: "CLB2 OUT5" },
	{ name: "XBAR_OUT_MUX07_ADCCEVT4", displayName: "ADCCEVT4" },
	{ name: "XBAR_OUT_MUX07_CLB1_OUT7", displayName: "CLB1 OUT7" },
]
let XBAR_OutputMuxConfig_MUX08 = [
	{ name: "XBAR_OUT_MUX08_CLB2_OUT0", displayName: "CLB2 OUT0" },
]
let XBAR_OutputMuxConfig_MUX09 = [
	{ name: "XBAR_OUT_MUX09_INPUTXBAR5", displayName: "INPUTXBAR5" },
	{ name: "XBAR_OUT_MUX09_CLB2_OUT1", displayName: "CLB2 OUT1" },
]
let XBAR_OutputMuxConfig_MUX10 = [
	{ name: "XBAR_OUT_MUX10_CLB2_OUT2", displayName: "CLB2 OUT2" },
]
let XBAR_OutputMuxConfig_MUX11 = [
	{ name: "XBAR_OUT_MUX11_INPUTXBAR6", displayName: "INPUTXBAR6" },
	{ name: "XBAR_OUT_MUX11_CLB2_OUT3", displayName: "CLB2 OUT3" },
]
let XBAR_OutputMuxConfig_MUX12 = [
	{ name: "XBAR_OUT_MUX12_CLB2_OUT4", displayName: "CLB2 OUT4" },
]
let XBAR_OutputMuxConfig_MUX13 = [
	{ name: "XBAR_OUT_MUX13_ADCSOCA", displayName: "ADCSOCA" },
	{ name: "XBAR_OUT_MUX13_CLB2_OUT5", displayName: "CLB2 OUT5" },
]
let XBAR_OutputMuxConfig_MUX14 = [
	{ name: "XBAR_OUT_MUX14_EXTSYNCOUT", displayName: "EXTSYNCOUT" },
	{ name: "XBAR_OUT_MUX14_CLB2_OUT6", displayName: "CLB2 OUT6" },
]
let XBAR_OutputMuxConfig_MUX15 = [
	{ name: "XBAR_OUT_MUX15_ADCSOCB", displayName: "ADCSOCB" },
	{ name: "XBAR_OUT_MUX15_CLB2_OUT7", displayName: "CLB2 OUT7" },
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
let XBAR_EPWMMuxConfig_MUX00 = [
	{ name: "XBAR_EPWM_MUX00_CMPSS1_CTRIPH", displayName: "CMPSS1 CTRIPH" },
	{ name: "XBAR_EPWM_MUX00_CMPSS1_CTRIPH_OR_L", displayName: "CMPSS1 CTRIPH OR L" },
	{ name: "XBAR_EPWM_MUX00_ADCAEVT1", displayName: "ADCAEVT1" },
	{ name: "XBAR_EPWM_MUX00_ECAP1_OUT", displayName: "ECAP1 OUT" },
]
let XBAR_EPWMMuxConfig_MUX01 = [
	{ name: "XBAR_EPWM_MUX01_CMPSS1_CTRIPL", displayName: "CMPSS1 CTRIPL" },
	{ name: "XBAR_EPWM_MUX01_INPUTXBAR1", displayName: "INPUTXBAR1" },
	{ name: "XBAR_EPWM_MUX01_CLB1_OUT4", displayName: "CLB1 OUT4" },
	{ name: "XBAR_EPWM_MUX01_ADCCEVT1", displayName: "ADCCEVT1" },
]
let XBAR_EPWMMuxConfig_MUX02 = [
	{ name: "XBAR_EPWM_MUX02_CMPSS2_CTRIPH", displayName: "CMPSS2 CTRIPH" },
	{ name: "XBAR_EPWM_MUX02_CMPSS2_CTRIPH_OR_L", displayName: "CMPSS2 CTRIPH OR L" },
	{ name: "XBAR_EPWM_MUX02_ADCAEVT2", displayName: "ADCAEVT2" },
	{ name: "XBAR_EPWM_MUX02_ECAP2_OUT", displayName: "ECAP2 OUT" },
]
let XBAR_EPWMMuxConfig_MUX03 = [
	{ name: "XBAR_EPWM_MUX03_CMPSS2_CTRIPL", displayName: "CMPSS2 CTRIPL" },
	{ name: "XBAR_EPWM_MUX03_INPUTXBAR2", displayName: "INPUTXBAR2" },
	{ name: "XBAR_EPWM_MUX03_CLB1_OUT5", displayName: "CLB1 OUT5" },
	{ name: "XBAR_EPWM_MUX03_ADCCEVT2", displayName: "ADCCEVT2" },
]
let XBAR_EPWMMuxConfig_MUX04 = [
	{ name: "XBAR_EPWM_MUX04_CMPSS3_CTRIPH", displayName: "CMPSS3 CTRIPH" },
	{ name: "XBAR_EPWM_MUX04_CMPSS3_CTRIPH_OR_L", displayName: "CMPSS3 CTRIPH OR L" },
	{ name: "XBAR_EPWM_MUX04_ADCAEVT3", displayName: "ADCAEVT3" },
	{ name: "XBAR_EPWM_MUX04_ECAP3_OUT", displayName: "ECAP3 OUT" },
]
let XBAR_EPWMMuxConfig_MUX05 = [
	{ name: "XBAR_EPWM_MUX05_CMPSS3_CTRIPL", displayName: "CMPSS3 CTRIPL" },
	{ name: "XBAR_EPWM_MUX05_INPUTXBAR3", displayName: "INPUTXBAR3" },
	{ name: "XBAR_EPWM_MUX05_CLB2_OUT4", displayName: "CLB2 OUT4" },
	{ name: "XBAR_EPWM_MUX05_ADCCEVT3", displayName: "ADCCEVT3" },
]
let XBAR_EPWMMuxConfig_MUX06 = [
	{ name: "XBAR_EPWM_MUX06_CMPSS4_CTRIPH", displayName: "CMPSS4 CTRIPH" },
	{ name: "XBAR_EPWM_MUX06_CMPSS4_CTRIPH_OR_L", displayName: "CMPSS4 CTRIPH OR L" },
	{ name: "XBAR_EPWM_MUX06_ADCAEVT4", displayName: "ADCAEVT4" },
]
let XBAR_EPWMMuxConfig_MUX07 = [
	{ name: "XBAR_EPWM_MUX07_CMPSS4_CTRIPL", displayName: "CMPSS4 CTRIPL" },
	{ name: "XBAR_EPWM_MUX07_INPUTXBAR4", displayName: "INPUTXBAR4" },
	{ name: "XBAR_EPWM_MUX07_CLB2_OUT5", displayName: "CLB2 OUT5" },
	{ name: "XBAR_EPWM_MUX07_ADCCEVT4", displayName: "ADCCEVT4" },
]
let XBAR_EPWMMuxConfig_MUX08 = [
]
let XBAR_EPWMMuxConfig_MUX09 = [
	{ name: "XBAR_EPWM_MUX09_INPUTXBAR5", displayName: "INPUTXBAR5" },
]
let XBAR_EPWMMuxConfig_MUX10 = [
]
let XBAR_EPWMMuxConfig_MUX11 = [
	{ name: "XBAR_EPWM_MUX11_INPUTXBAR6", displayName: "INPUTXBAR6" },
]
let XBAR_EPWMMuxConfig_MUX12 = [
]
let XBAR_EPWMMuxConfig_MUX13 = [
	{ name: "XBAR_EPWM_MUX13_ADCSOCA", displayName: "ADCSOCA" },
]
let XBAR_EPWMMuxConfig_MUX14 = [
	{ name: "XBAR_EPWM_MUX14_EXTSYNCOUT", displayName: "EXTSYNCOUT" },
]
let XBAR_EPWMMuxConfig_MUX15 = [
	{ name: "XBAR_EPWM_MUX15_ADCSOCB", displayName: "ADCSOCB" },
]
let XBAR_EPWMMuxConfig_MUX16 = [
]
let XBAR_EPWMMuxConfig_MUX17 = [
	{ name: "XBAR_EPWM_MUX17_INPUTXBAR7", displayName: "INPUTXBAR7" },
]
let XBAR_EPWMMuxConfig_MUX18 = [
]
let XBAR_EPWMMuxConfig_MUX19 = [
	{ name: "XBAR_EPWM_MUX19_INPUTXBAR8", displayName: "INPUTXBAR8" },
]
let XBAR_EPWMMuxConfig_MUX20 = [
]
let XBAR_EPWMMuxConfig_MUX21 = [
	{ name: "XBAR_EPWM_MUX21_INPUTXBAR9", displayName: "INPUTXBAR9" },
]
let XBAR_EPWMMuxConfig_MUX22 = [
]
let XBAR_EPWMMuxConfig_MUX23 = [
	{ name: "XBAR_EPWM_MUX23_INPUTXBAR10", displayName: "INPUTXBAR10" },
]
let XBAR_EPWMMuxConfig_MUX24 = [
]
let XBAR_EPWMMuxConfig_MUX25 = [
	{ name: "XBAR_EPWM_MUX25_INPUTXBAR11", displayName: "INPUTXBAR11" },
]
let XBAR_EPWMMuxConfig_MUX26 = [
]
let XBAR_EPWMMuxConfig_MUX27 = [
	{ name: "XBAR_EPWM_MUX27_INPUTXBAR12", displayName: "INPUTXBAR12" },
]
let XBAR_EPWMMuxConfig_MUX28 = [
]
let XBAR_EPWMMuxConfig_MUX29 = [
	{ name: "XBAR_EPWM_MUX29_INPUTXBAR13", displayName: "INPUTXBAR13" },
]
let XBAR_EPWMMuxConfig_MUX30 = [
]
let XBAR_EPWMMuxConfig_MUX31 = [
	{ name: "XBAR_EPWM_MUX31_INPUTXBAR14", displayName: "INPUTXBAR14" },
]
let XBAR_EPWMMuxConfig_All_MUXES = [
	XBAR_EPWMMuxConfig_MUX00,
	XBAR_EPWMMuxConfig_MUX01,
	XBAR_EPWMMuxConfig_MUX02,
	XBAR_EPWMMuxConfig_MUX03,
	XBAR_EPWMMuxConfig_MUX04,
	XBAR_EPWMMuxConfig_MUX05,
	XBAR_EPWMMuxConfig_MUX06,
	XBAR_EPWMMuxConfig_MUX07,
	XBAR_EPWMMuxConfig_MUX08,
	XBAR_EPWMMuxConfig_MUX09,
	XBAR_EPWMMuxConfig_MUX10,
	XBAR_EPWMMuxConfig_MUX11,
	XBAR_EPWMMuxConfig_MUX12,
	XBAR_EPWMMuxConfig_MUX13,
	XBAR_EPWMMuxConfig_MUX14,
	XBAR_EPWMMuxConfig_MUX15,
	XBAR_EPWMMuxConfig_MUX16,
	XBAR_EPWMMuxConfig_MUX17,
	XBAR_EPWMMuxConfig_MUX18,
	XBAR_EPWMMuxConfig_MUX19,
	XBAR_EPWMMuxConfig_MUX20,
	XBAR_EPWMMuxConfig_MUX21,
	XBAR_EPWMMuxConfig_MUX22,
	XBAR_EPWMMuxConfig_MUX23,
	XBAR_EPWMMuxConfig_MUX24,
	XBAR_EPWMMuxConfig_MUX25,
	XBAR_EPWMMuxConfig_MUX26,
	XBAR_EPWMMuxConfig_MUX27,
	XBAR_EPWMMuxConfig_MUX28,
	XBAR_EPWMMuxConfig_MUX29,
	XBAR_EPWMMuxConfig_MUX30,
	XBAR_EPWMMuxConfig_MUX31,
]
let XBAR_CLBMuxConfig_MUX00 = [
	{ name: "XBAR_CLB_MUX00_CMPSS1_CTRIPH", displayName: "CMPSS1 CTRIPH" },
	{ name: "XBAR_CLB_MUX00_CMPSS1_CTRIPH_OR_L", displayName: "CMPSS1 CTRIPH OR L" },
	{ name: "XBAR_CLB_MUX00_ADCAEVT1", displayName: "ADCAEVT1" },
	{ name: "XBAR_CLB_MUX00_ECAP1_OUT", displayName: "ECAP1 OUT" },
]
let XBAR_CLBMuxConfig_MUX01 = [
	{ name: "XBAR_CLB_MUX01_CMPSS1_CTRIPL", displayName: "CMPSS1 CTRIPL" },
	{ name: "XBAR_CLB_MUX01_INPUTXBAR1", displayName: "INPUTXBAR1" },
	{ name: "XBAR_CLB_MUX01_CLB1_OUT4", displayName: "CLB1 OUT4" },
	{ name: "XBAR_CLB_MUX01_ADCCEVT1", displayName: "ADCCEVT1" },
]
let XBAR_CLBMuxConfig_MUX02 = [
	{ name: "XBAR_CLB_MUX02_CMPSS2_CTRIPH", displayName: "CMPSS2 CTRIPH" },
	{ name: "XBAR_CLB_MUX02_CMPSS2_CTRIPH_OR_L", displayName: "CMPSS2 CTRIPH OR L" },
	{ name: "XBAR_CLB_MUX02_ADCAEVT2", displayName: "ADCAEVT2" },
	{ name: "XBAR_CLB_MUX02_ECAP2_OUT", displayName: "ECAP2 OUT" },
]
let XBAR_CLBMuxConfig_MUX03 = [
	{ name: "XBAR_CLB_MUX03_CMPSS2_CTRIPL", displayName: "CMPSS2 CTRIPL" },
	{ name: "XBAR_CLB_MUX03_INPUTXBAR2", displayName: "INPUTXBAR2" },
	{ name: "XBAR_CLB_MUX03_CLB1_OUT5", displayName: "CLB1 OUT5" },
	{ name: "XBAR_CLB_MUX03_ADCCEVT2", displayName: "ADCCEVT2" },
]
let XBAR_CLBMuxConfig_MUX04 = [
	{ name: "XBAR_CLB_MUX04_CMPSS3_CTRIPH", displayName: "CMPSS3 CTRIPH" },
	{ name: "XBAR_CLB_MUX04_CMPSS3_CTRIPH_OR_L", displayName: "CMPSS3 CTRIPH OR L" },
	{ name: "XBAR_CLB_MUX04_ADCAEVT3", displayName: "ADCAEVT3" },
	{ name: "XBAR_CLB_MUX04_ECAP3_OUT", displayName: "ECAP3 OUT" },
]
let XBAR_CLBMuxConfig_MUX05 = [
	{ name: "XBAR_CLB_MUX05_CMPSS3_CTRIPL", displayName: "CMPSS3 CTRIPL" },
	{ name: "XBAR_CLB_MUX05_INPUTXBAR3", displayName: "INPUTXBAR3" },
	{ name: "XBAR_CLB_MUX05_CLB2_OUT4", displayName: "CLB2 OUT4" },
	{ name: "XBAR_CLB_MUX05_ADCCEVT3", displayName: "ADCCEVT3" },
]
let XBAR_CLBMuxConfig_MUX06 = [
	{ name: "XBAR_CLB_MUX06_CMPSS4_CTRIPH", displayName: "CMPSS4 CTRIPH" },
	{ name: "XBAR_CLB_MUX06_CMPSS4_CTRIPH_OR_L", displayName: "CMPSS4 CTRIPH OR L" },
	{ name: "XBAR_CLB_MUX06_ADCAEVT4", displayName: "ADCAEVT4" },
]
let XBAR_CLBMuxConfig_MUX07 = [
	{ name: "XBAR_CLB_MUX07_CMPSS4_CTRIPL", displayName: "CMPSS4 CTRIPL" },
	{ name: "XBAR_CLB_MUX07_INPUTXBAR4", displayName: "INPUTXBAR4" },
	{ name: "XBAR_CLB_MUX07_CLB2_OUT5", displayName: "CLB2 OUT5" },
	{ name: "XBAR_CLB_MUX07_ADCCEVT4", displayName: "ADCCEVT4" },
]
let XBAR_CLBMuxConfig_MUX08 = [
]
let XBAR_CLBMuxConfig_MUX09 = [
	{ name: "XBAR_CLB_MUX09_INPUTXBAR5", displayName: "INPUTXBAR5" },
]
let XBAR_CLBMuxConfig_MUX10 = [
]
let XBAR_CLBMuxConfig_MUX11 = [
	{ name: "XBAR_CLB_MUX11_INPUTXBAR6", displayName: "INPUTXBAR6" },
]
let XBAR_CLBMuxConfig_MUX12 = [
]
let XBAR_CLBMuxConfig_MUX13 = [
	{ name: "XBAR_CLB_MUX13_ADCSOCA", displayName: "ADCSOCA" },
]
let XBAR_CLBMuxConfig_MUX14 = [
	{ name: "XBAR_CLB_MUX14_EXTSYNCOUT", displayName: "EXTSYNCOUT" },
]
let XBAR_CLBMuxConfig_MUX15 = [
	{ name: "XBAR_CLB_MUX15_ADCSOCB", displayName: "ADCSOCB" },
]
let XBAR_CLBMuxConfig_MUX16 = [
]
let XBAR_CLBMuxConfig_MUX17 = [
	{ name: "XBAR_CLB_MUX17_INPUTXBAR7", displayName: "INPUTXBAR7" },
]
let XBAR_CLBMuxConfig_MUX18 = [
]
let XBAR_CLBMuxConfig_MUX19 = [
	{ name: "XBAR_CLB_MUX19_INPUTXBAR8", displayName: "INPUTXBAR8" },
]
let XBAR_CLBMuxConfig_MUX20 = [
]
let XBAR_CLBMuxConfig_MUX21 = [
	{ name: "XBAR_CLB_MUX21_INPUTXBAR9", displayName: "INPUTXBAR9" },
]
let XBAR_CLBMuxConfig_MUX22 = [
]
let XBAR_CLBMuxConfig_MUX23 = [
	{ name: "XBAR_CLB_MUX23_INPUTXBAR10", displayName: "INPUTXBAR10" },
]
let XBAR_CLBMuxConfig_MUX24 = [
]
let XBAR_CLBMuxConfig_MUX25 = [
	{ name: "XBAR_CLB_MUX25_INPUTXBAR11", displayName: "INPUTXBAR11" },
]
let XBAR_CLBMuxConfig_MUX26 = [
]
let XBAR_CLBMuxConfig_MUX27 = [
	{ name: "XBAR_CLB_MUX27_INPUTXBAR12", displayName: "INPUTXBAR12" },
]
let XBAR_CLBMuxConfig_MUX28 = [
]
let XBAR_CLBMuxConfig_MUX29 = [
	{ name: "XBAR_CLB_MUX29_INPUTXBAR13", displayName: "INPUTXBAR13" },
]
let XBAR_CLBMuxConfig_MUX30 = [
]
let XBAR_CLBMuxConfig_MUX31 = [
	{ name: "XBAR_CLB_MUX31_INPUTXBAR14", displayName: "INPUTXBAR14" },
]
let XBAR_CLBMuxConfig_All_MUXES = [
	XBAR_CLBMuxConfig_MUX00,
	XBAR_CLBMuxConfig_MUX01,
	XBAR_CLBMuxConfig_MUX02,
	XBAR_CLBMuxConfig_MUX03,
	XBAR_CLBMuxConfig_MUX04,
	XBAR_CLBMuxConfig_MUX05,
	XBAR_CLBMuxConfig_MUX06,
	XBAR_CLBMuxConfig_MUX07,
	XBAR_CLBMuxConfig_MUX08,
	XBAR_CLBMuxConfig_MUX09,
	XBAR_CLBMuxConfig_MUX10,
	XBAR_CLBMuxConfig_MUX11,
	XBAR_CLBMuxConfig_MUX12,
	XBAR_CLBMuxConfig_MUX13,
	XBAR_CLBMuxConfig_MUX14,
	XBAR_CLBMuxConfig_MUX15,
	XBAR_CLBMuxConfig_MUX16,
	XBAR_CLBMuxConfig_MUX17,
	XBAR_CLBMuxConfig_MUX18,
	XBAR_CLBMuxConfig_MUX19,
	XBAR_CLBMuxConfig_MUX20,
	XBAR_CLBMuxConfig_MUX21,
	XBAR_CLBMuxConfig_MUX22,
	XBAR_CLBMuxConfig_MUX23,
	XBAR_CLBMuxConfig_MUX24,
	XBAR_CLBMuxConfig_MUX25,
	XBAR_CLBMuxConfig_MUX26,
	XBAR_CLBMuxConfig_MUX27,
	XBAR_CLBMuxConfig_MUX28,
	XBAR_CLBMuxConfig_MUX29,
	XBAR_CLBMuxConfig_MUX30,
	XBAR_CLBMuxConfig_MUX31,
]
module.exports = {
	XBAR_MUXES: XBAR_MUXES,
	XBAR_OutputNum: XBAR_OutputNum,
	XBAR_TripNum: XBAR_TripNum,
	XBAR_AuxSigNum: XBAR_AuxSigNum,
	XBAR_InputNum: XBAR_InputNum,
	XBAR_OutputMuxConfig: XBAR_OutputMuxConfig,
	XBAR_EPWMMuxConfig: XBAR_EPWMMuxConfig,
	XBAR_CLBMuxConfig: XBAR_CLBMuxConfig,
	XBAR_InputFlag: XBAR_InputFlag,
	XBAR_OutputMuxConfig_All_MUXES: XBAR_OutputMuxConfig_All_MUXES,
	XBAR_EPWMMuxConfig_All_MUXES: XBAR_EPWMMuxConfig_All_MUXES,
	XBAR_CLBMuxConfig_All_MUXES: XBAR_CLBMuxConfig_All_MUXES,
}
