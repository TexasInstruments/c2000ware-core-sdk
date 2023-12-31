let ECAP_EmulationMode = [
	{ name: "ECAP_EMULATION_STOP", displayName: "TSCTR is stopped on emulation suspension" },
	{ name: "ECAP_EMULATION_RUN_TO_ZERO", displayName: "TSCTR runs until 0 before stopping on emulation suspension" },
	{ name: "ECAP_EMULATION_FREE_RUN", displayName: "TSCTR is not affected by emulation suspension" },
]
let ECAP_CaptureMode = [
	{ name: "ECAP_CONTINUOUS_CAPTURE_MODE", displayName: "eCAP operates in continuous capture mode" },
	{ name: "ECAP_ONE_SHOT_CAPTURE_MODE", displayName: "eCAP operates in one shot capture mode" },
]
let ECAP_Events = [
	{ name: "ECAP_EVENT_1", displayName: "eCAP event 1" },
	{ name: "ECAP_EVENT_2", displayName: "eCAP event 2" },
	{ name: "ECAP_EVENT_3", displayName: "eCAP event 3" },
	{ name: "ECAP_EVENT_4", displayName: "eCAP event 4" },
]
let ECAP_SyncOutMode = [
	{ name: "ECAP_SYNC_OUT_SYNCI", displayName: "sync out on the sync in signal and software force" },
	{ name: "ECAP_SYNC_OUT_COUNTER_PRD", displayName: "sync out on counter equals period" },
	{ name: "ECAP_SYNC_OUT_DISABLED", displayName: "Disable sync out signal" },
]
let ECAP_APWMPolarity = [
	{ name: "ECAP_APWM_ACTIVE_HIGH", displayName: "APWM is active high" },
	{ name: "ECAP_APWM_ACTIVE_LOW", displayName: "APWM is active low" },
]
let ECAP_EventPolarity = [
	{ name: "ECAP_EVNT_RISING_EDGE", displayName: "Rising edge polarity" },
	{ name: "ECAP_EVNT_FALLING_EDGE", displayName: "Falling edge polarity" },
]
let ECAP_InputCaptureSignals = [
	{ name: "ECAP_INPUT_INPUTXBAR1", displayName: "GPIO Input Crossbar output signal-1" },
	{ name: "ECAP_INPUT_INPUTXBAR2", displayName: "GPIO Input Crossbar output signal-2" },
	{ name: "ECAP_INPUT_INPUTXBAR3", displayName: "GPIO Input Crossbar output signal-3" },
	{ name: "ECAP_INPUT_INPUTXBAR4", displayName: "GPIO Input Crossbar output signal-4" },
	{ name: "ECAP_INPUT_INPUTXBAR5", displayName: "GPIO Input Crossbar output signal-5" },
	{ name: "ECAP_INPUT_INPUTXBAR6", displayName: "GPIO Input Crossbar output signal-6" },
	{ name: "ECAP_INPUT_INPUTXBAR7", displayName: "GPIO Input Crossbar output signal-7" },
	{ name: "ECAP_INPUT_INPUTXBAR8", displayName: "GPIO Input Crossbar output signal-8" },
	{ name: "ECAP_INPUT_INPUTXBAR9", displayName: "GPIO Input Crossbar output signal-9" },
	{ name: "ECAP_INPUT_INPUTXBAR10", displayName: "GPIO Input Crossbar output signal-10" },
	{ name: "ECAP_INPUT_INPUTXBAR11", displayName: "GPIO Input Crossbar output signal-11" },
	{ name: "ECAP_INPUT_INPUTXBAR12", displayName: "GPIO Input Crossbar output signal-12" },
	{ name: "ECAP_INPUT_INPUTXBAR13", displayName: "GPIO Input Crossbar output signal-13" },
	{ name: "ECAP_INPUT_INPUTXBAR14", displayName: "GPIO Input Crossbar output signal-14" },
	{ name: "ECAP_INPUT_INPUTXBAR15", displayName: "GPIO Input Crossbar output signal-15" },
	{ name: "ECAP_INPUT_INPUTXBAR16", displayName: "GPIO Input Crossbar output signal-16" },
	{ name: "ECAP_INPUT_ECAP1_CLB1_CLBOUT14", displayName: "CLB1 CLBOUT14 input for ECAP1 instance" },
	{ name: "ECAP_INPUT_ECAP2_CLB1_CLBOUT14", displayName: "CLB1 CLBOUT14 input for ECAP2 instance" },
	{ name: "ECAP_INPUT_ECAP3_CLB2_CLBOUT14", displayName: "CLB2 CLBOUT14 input for ECAP3 instance" },
	{ name: "ECAP_INPUT_ECAP4_CLB2_CLBOUT14", displayName: "CLB2 CLBOUT14 input for ECAP4 instance" },
	{ name: "ECAP_INPUT_ECAP5_CLB2_CLBOUT14", displayName: "CLB2 CLBOUT14 input for ECAP5 instance" },
	{ name: "ECAP_INPUT_ECAP6_CLB3_CLBOUT14", displayName: "CLB3 CLBOUT14 input for ECAP6 instance" },
	{ name: "ECAP_INPUT_ECAP7_CLB3_CLBOUT14", displayName: "CLB3 CLBOUT14 input for ECAP7 instance" },
	{ name: "ECAP_INPUT_ECAP1_CLB1_CLBOUT15", displayName: "CLB1 CLBOUT15 input for ECAP1 instance" },
	{ name: "ECAP_INPUT_ECAP2_CLB1_CLBOUT15", displayName: "CLB1 CLBOUT15 input for ECAP2 instance" },
	{ name: "ECAP_INPUT_ECAP3_CLB2_CLBOUT15", displayName: "CLB2 CLBOUT15 input for ECAP3 instance" },
	{ name: "ECAP_INPUT_ECAP4_CLB2_CLBOUT15", displayName: "CLB2 CLBOUT15 input for ECAP4 instance" },
	{ name: "ECAP_INPUT_ECAP5_CLB2_CLBOUT15", displayName: "CLB2 CLBOUT15 input for ECAP5 instance" },
	{ name: "ECAP_INPUT_ECAP6_CLB3_CLBOUT15", displayName: "CLB3 CLBOUT15 input for ECAP6 instance" },
	{ name: "ECAP_INPUT_ECAP7_CLB3_CLBOUT15", displayName: "CLB3 CLBOUT15 input for ECAP7 instance" },
	{ name: "ECAP_INPUT_ECAP1_CLB5_CLBOUT14", displayName: "CLB5 CLBOUT14 input for ECAP1 instance" },
	{ name: "ECAP_INPUT_ECAP2_CLB5_CLBOUT14", displayName: "CLB5 CLBOUT14 input for ECAP2 instance" },
	{ name: "ECAP_INPUT_ECAP3_CLB6_CLBOUT14", displayName: "CLB6 CLBOUT14 input for ECAP3 instance" },
	{ name: "ECAP_INPUT_ECAP4_CLB7_CLBOUT14", displayName: "CLB7 CLBOUT14 input for ECAP4 instance" },
	{ name: "ECAP_INPUT_ECAP5_CLB8_CLBOUT14", displayName: "CLB8 CLBOUT14 input for ECAP5 instance" },
	{ name: "ECAP_INPUT_ECAP6_CLB4_CLBOUT14", displayName: "CLB4 CLBOUT14 input for ECAP6 instance" },
	{ name: "ECAP_INPUT_ECAP7_CLB4_CLBOUT14", displayName: "CLB4 CLBOUT14 input for ECAP7 instance" },
	{ name: "ECAP_INPUT_ECAP1_CLB5_CLBOUT15", displayName: "CLB5 CLBOUT15 input for ECAP1 instance" },
	{ name: "ECAP_INPUT_ECAP2_CLB5_CLBOUT15", displayName: "CLB5 CLBOUT15 input for ECAP2 instance" },
	{ name: "ECAP_INPUT_ECAP3_CLB6_CLBOUT15", displayName: "CLB6 CLBOUT15 input for ECAP3 instance" },
	{ name: "ECAP_INPUT_ECAP4_CLB7_CLBOUT15", displayName: "CLB7 CLBOUT15 input for ECAP4 instance" },
	{ name: "ECAP_INPUT_ECAP5_CLB8_CLBOUT15", displayName: "CLB8 CLBOUT15 input for ECAP5 instance" },
	{ name: "ECAP_INPUT_ECAP6_CLB4_CLBOUT15", displayName: "CLB4 CLBOUT15 input for ECAP6 instance" },
	{ name: "ECAP_INPUT_ECAP7_CLB4_CLBOUT15", displayName: "CLB4 CLBOUT15 input for ECAP7 instance" },
	{ name: "ECAP_INPUT_CANA_INT0", displayName: "CANA INT0 Input" },
	{ name: "ECAP_INPUT_CANB_INT0", displayName: "CANB INT0 Input" },
	{ name: "ECAP_INPUT_ECAP_DELAY_CLOCK", displayName: "Delay clock for measurement" },
	{ name: "ECAP_INPUT_OUTPUTXBAR1", displayName: "Output Xbar Output-1" },
	{ name: "ECAP_INPUT_OUTPUTXBAR2", displayName: "Output Xbar Output-2" },
	{ name: "ECAP_INPUT_OUTPUTXBAR3", displayName: "Output Xbar Output-3" },
	{ name: "ECAP_INPUT_OUTPUTXBAR4", displayName: "Output Xbar Output-4" },
	{ name: "ECAP_INPUT_OUTPUTXBAR5", displayName: "Output Xbar Output-5" },
	{ name: "ECAP_INPUT_OUTPUTXBAR6", displayName: "Output Xbar Output-6" },
	{ name: "ECAP_INPUT_OUTPUTXBAR7", displayName: "Output Xbar Output-7" },
	{ name: "ECAP_INPUT_OUTPUTXBAR8", displayName: "Output Xbar Output-8" },
	{ name: "ECAP_INPUT_ADC_D_EVENT4", displayName: "ADCD Event4" },
	{ name: "ECAP_INPUT_ADC_D_EVENT3", displayName: "ADCD Event3" },
	{ name: "ECAP_INPUT_ADC_D_EVENT2", displayName: "ADCD Event2" },
	{ name: "ECAP_INPUT_ADC_D_EVENT1", displayName: "ADCD Event1" },
	{ name: "ECAP_INPUT_ADC_C_EVENT4", displayName: "ADCC Event4" },
	{ name: "ECAP_INPUT_ADC_C_EVENT3", displayName: "ADCC Event3" },
	{ name: "ECAP_INPUT_ADC_C_EVENT2", displayName: "ADCC Event2" },
	{ name: "ECAP_INPUT_ADC_C_EVENT1", displayName: "ADCC Event1" },
	{ name: "ECAP_INPUT_ADC_B_EVENT4", displayName: "ADCB Event4" },
	{ name: "ECAP_INPUT_ADC_B_EVENT3", displayName: "ADCB Event3" },
	{ name: "ECAP_INPUT_ADC_B_EVENT2", displayName: "ADCB Event2" },
	{ name: "ECAP_INPUT_ADC_B_EVENT1", displayName: "ADCB Event1" },
	{ name: "ECAP_INPUT_ADC_A_EVENT4", displayName: "ADCA Event4" },
	{ name: "ECAP_INPUT_ADC_A_EVENT3", displayName: "ADCA Event3" },
	{ name: "ECAP_INPUT_ADC_A_EVENT2", displayName: "ADCA Event2" },
	{ name: "ECAP_INPUT_ADC_A_EVENT1", displayName: "ADCA Event1" },
	{ name: "ECAP_INPUT_FSIA_RX_MSR_LINE", displayName: "FSIA Rx MSR Line" },
	{ name: "ECAP_INPUT_FSIA_RX_MSR_LINE_RISE", displayName: "FSIA Rx MSR Line Rise" },
	{ name: "ECAP_INPUT_FSIA_RX_MSR_LINE_FALL", displayName: "FSIA Rx MSR Line Fall" },
	{ name: "ECAP_INPUT_FSIB_RX_MSR_LINE", displayName: "FSIB Rx MSR Line" },
	{ name: "ECAP_INPUT_FSIB_RX_MSR_LINE_RISE", displayName: "FSIB Rx MSR Line Rise" },
	{ name: "ECAP_INPUT_FSIB_RX_MSR_LINE_FALL", displayName: "FSIB Rx MSR Line Fall" },
	{ name: "ECAP_INPUT_FSIC_RX_MSR_LINE", displayName: "FSIC Rx MSR Line" },
	{ name: "ECAP_INPUT_FSIC_RX_MSR_LINE_RISE", displayName: "FSIC Rx MSR Line Rise" },
	{ name: "ECAP_INPUT_FSIC_RX_MSR_LINE_FALL", displayName: "FSIC Rx MSR Line Fall" },
	{ name: "ECAP_INPUT_FSID_RX_MSR_LINE", displayName: "FSID Rx MSR Line" },
	{ name: "ECAP_INPUT_FSID_RX_MSR_LINE_RISE", displayName: "FSID Rx MSR Line Rise" },
	{ name: "ECAP_INPUT_FSID_RX_MSR_LINE_FALL", displayName: "FSID Rx MSR Line Fall" },
	{ name: "ECAP_INPUT_SDFM2_FLT1_COMPARE_LOW", displayName: "SDFM-2 Filter-1 Compare Low Trip" },
	{ name: "ECAP_INPUT_SDFM2_FLT2_COMPARE_LOW", displayName: "SDFM-2 Filter-2 Compare Low Trip" },
	{ name: "ECAP_INPUT_SDFM2_FLT3_COMPARE_LOW", displayName: "SDFM-2 Filter-3 Compare Low Trip" },
	{ name: "ECAP_INPUT_SDFM2_FLT4_COMPARE_LOW", displayName: "SDFM-2 Filter-4 Compare Low Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT1_COMPARE_LOW", displayName: "SDFM-1 Filter-1 Compare Low Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT2_COMPARE_LOW", displayName: "SDFM-1 Filter-2 Compare Low Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT3_COMPARE_LOW", displayName: "SDFM-1 Filter-3 Compare Low Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT4_COMPARE_LOW", displayName: "SDFM-1 Filter-4 Compare Low Trip" },
	{ name: "ECAP_INPUT_FSIE_RX_MSR_LINE", displayName: "FSIE Rx MSR Line" },
	{ name: "ECAP_INPUT_FSIE_RX_MSR_LINE_RISE", displayName: "FSIE Rx MSR Line Rise" },
	{ name: "ECAP_INPUT_FSIE_RX_MSR_LINE_FALL", displayName: "FSIE Rx MSR Line Fall" },
	{ name: "ECAP_INPUT_FSIF_RX_MSR_LINE", displayName: "FSIF Rx MSR Line" },
	{ name: "ECAP_INPUT_FSIF_RX_MSR_LINE_RISE", displayName: "FSIF Rx MSR Line Rise" },
	{ name: "ECAP_INPUT_FSIF_RX_MSR_LINE_FALL", displayName: "FSIF Rx MSR Line Fall" },
	{ name: "ECAP_INPUT_ECATSYNC0", displayName: "Ethercat Sync0" },
	{ name: "ECAP_INPUT_ECATSYNC1", displayName: "Ethercat Sync1" },
	{ name: "ECAP_INPUT_SDFM2_FLT1_COMPARE_HIGH", displayName: "SDFM-2 Filter-1 Compare High Trip" },
	{ name: "ECAP_INPUT_SDFM2_FLT2_COMPARE_HIGH", displayName: "SDFM-2 Filter-2 Compare High Trip" },
	{ name: "ECAP_INPUT_SDFM2_FLT3_COMPARE_HIGH", displayName: "SDFM-2 Filter-3 Compare High Trip" },
	{ name: "ECAP_INPUT_SDFM2_FLT4_COMPARE_HIGH", displayName: "SDFM-2 Filter-4 Compare High Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT1_COMPARE_HIGH", displayName: "SDFM-1 Filter-1 Compare High Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT2_COMPARE_HIGH", displayName: "SDFM-1 Filter-2 Compare High Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT3_COMPARE_HIGH", displayName: "SDFM-1 Filter-3 Compare High Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT4_COMPARE_HIGH", displayName: "SDFM-1 Filter-4 Compare High Trip" },
	{ name: "ECAP_INPUT_SDFM2_FLT1_COMPARE_HIGH_OR_LOW", displayName: "SDFM-2 Filter-1 Compare High Trip or Low Trip" },
	{ name: "ECAP_INPUT_SDFM2_FLT2_COMPARE_HIGH_OR_LOW", displayName: "SDFM-2 Filter-2 Compare High Trip or Low Trip" },
	{ name: "ECAP_INPUT_SDFM2_FLT3_COMPARE_HIGH_OR_LOW", displayName: "SDFM-2 Filter-3 Compare High Trip or Low Trip" },
	{ name: "ECAP_INPUT_SDFM2_FLT4_COMPARE_HIGH_OR_LOW", displayName: "SDFM-2 Filter-4 Compare High Trip or Low Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT1_COMPARE_HIGH_OR_LOW", displayName: "SDFM-1 Filter-1 Compare High Trip or Low Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT2_COMPARE_HIGH_OR_LOW", displayName: "SDFM-1 Filter-2 Compare High Trip or Low Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT3_COMPARE_HIGH_OR_LOW", displayName: "SDFM-1 Filter-3 Compare High Trip or Low Trip" },
	{ name: "ECAP_INPUT_SDFM1_FLT4_COMPARE_HIGH_OR_LOW", displayName: "SDFM-1 Filter-4 Compare High Trip or Low Trip" },
	{ name: "ECAP_INPUT_FSIG_RX_MSR_LINE", displayName: "FSIG Rx MSR Line" },
	{ name: "ECAP_INPUT_FSIG_RX_MSR_LINE_RISE", displayName: "FSIG Rx MSR Line Rise" },
	{ name: "ECAP_INPUT_FSIG_RX_MSR_LINE_FALL", displayName: "FSIG Rx MSR Line Fall" },
	{ name: "ECAP_INPUT_CMPSS1_CTRIP_LOW", displayName: "Compare Subsystem-1 Low Trip" },
	{ name: "ECAP_INPUT_CMPSS2_CTRIP_LOW", displayName: "Compare Subsystem-2 Low Trip" },
	{ name: "ECAP_INPUT_CMPSS3_CTRIP_LOW", displayName: "Compare Subsystem-3 Low Trip" },
	{ name: "ECAP_INPUT_CMPSS4_CTRIP_LOW", displayName: "Compare Subsystem-4 Low Trip" },
	{ name: "ECAP_INPUT_CMPSS5_CTRIP_LOW", displayName: "Compare Subsystem-5 Low Trip" },
	{ name: "ECAP_INPUT_CMPSS6_CTRIP_LOW", displayName: "Compare Subsystem-6 Low Trip" },
	{ name: "ECAP_INPUT_CMPSS7_CTRIP_LOW", displayName: "Compare Subsystem-7 Low Trip" },
	{ name: "ECAP_INPUT_FSIH_RX_MSR_LINE", displayName: "FSIH Rx MSR Line" },
	{ name: "ECAP_INPUT_FSIH_RX_MSR_LINE_RISE", displayName: "FSIH Rx MSR Line Rise" },
	{ name: "ECAP_INPUT_FSIH_RX_MSR_LINE_FALL", displayName: "FSIH Rx MSR Line Fall" },
	{ name: "ECAP_INPUT_CMPSS1_CTRIP_HIGH", displayName: "Compare Subsystem-1 High Trip" },
	{ name: "ECAP_INPUT_CMPSS2_CTRIP_HIGH", displayName: "Compare Subsystem-2 High Trip" },
	{ name: "ECAP_INPUT_CMPSS3_CTRIP_HIGH", displayName: "Compare Subsystem-3 High Trip" },
	{ name: "ECAP_INPUT_CMPSS4_CTRIP_HIGH", displayName: "Compare Subsystem-4 High Trip" },
	{ name: "ECAP_INPUT_CMPSS5_CTRIP_HIGH", displayName: "Compare Subsystem-5 High Trip" },
	{ name: "ECAP_INPUT_CMPSS6_CTRIP_HIGH", displayName: "Compare Subsystem-6 High Trip" },
	{ name: "ECAP_INPUT_CMPSS7_CTRIP_HIGH", displayName: "Compare Subsystem-7 High Trip" },
	{ name: "ECAP_INPUT_GPIO8", displayName: "GPIO8" },
	{ name: "ECAP_INPUT_GPIO9", displayName: "GPIO9" },
	{ name: "ECAP_INPUT_GPIO22", displayName: "GPIO22" },
	{ name: "ECAP_INPUT_GPIO23", displayName: "GPIO23" },
	{ name: "ECAP_INPUT_CMPSS1_CTRIP_HIGH_OR_LOW", displayName: "Compare Subsystem-1 High Trip or Low Trip" },
	{ name: "ECAP_INPUT_CMPSS2_CTRIP_HIGH_OR_LOW", displayName: "Compare Subsystem-2 High Trip or Low Trip" },
	{ name: "ECAP_INPUT_CMPSS3_CTRIP_HIGH_OR_LOW", displayName: "Compare Subsystem-3 High Trip or Low Trip" },
	{ name: "ECAP_INPUT_CMPSS4_CTRIP_HIGH_OR_LOW", displayName: "Compare Subsystem-4 High Trip or Low Trip" },
	{ name: "ECAP_INPUT_CMPSS5_CTRIP_HIGH_OR_LOW", displayName: "Compare Subsystem-5 High Trip or Low Trip" },
	{ name: "ECAP_INPUT_CMPSS6_CTRIP_HIGH_OR_LOW", displayName: "Compare Subsystem-6 High Trip or Low Trip" },
	{ name: "ECAP_INPUT_CMPSS7_CTRIP_HIGH_OR_LOW", displayName: "Compare Subsystem-7 High Trip or Low Trip" },
	{ name: "ECAP_INPUT_ECAP1_GPTRIP7", displayName: "GPTRIP7 input for instance ECAP1" },
	{ name: "ECAP_INPUT_ECAP2_GPTRIP8", displayName: "GPTRIP8 input for instance ECAP2" },
	{ name: "ECAP_INPUT_ECAP3_GPTRIP9", displayName: "GPTRIP9 input for instance ECAP3" },
	{ name: "ECAP_INPUT_ECAP4_GPTRIP10", displayName: "GPTRIP10 input for instance ECAP4" },
	{ name: "ECAP_INPUT_ECAP5_GPTRIP11", displayName: "GPTRIP11 input for instance ECAP5" },
	{ name: "ECAP_INPUT_ECAP6_GPTRIP12", displayName: "GPTRIP12 input for instance ECAP6" },
	{ name: "ECAP_INPUT_ECAP7_GPTRIP13", displayName: "GPTRIP13 input for instance ECAP7" },
]
let ECAP_SyncInPulseSource = [
	{ name: "ECAP_SYNC_IN_PULSE_SRC_DISABLE", displayName: "Disable Sync-in" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM1", displayName: "Sync-in source is EPWM1 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM2", displayName: "Sync-in source is EPWM2 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM3", displayName: "Sync-in source is EPWM3 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM4", displayName: "Sync-in source is EPWM4 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM5", displayName: "Sync-in source is EPWM5 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM6", displayName: "Sync-in source is EPWM6 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM7", displayName: "Sync-in source is EPWM7 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM8", displayName: "Sync-in source is EPWM8 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM9", displayName: "Sync-in source is EPWM9 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM10", displayName: "Sync-in source is EPWM10 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM11", displayName: "Sync-in source is EPWM11 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM12", displayName: "Sync-in source is EPWM12 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM13", displayName: "Sync-in source is EPWM13 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM14", displayName: "Sync-in source is EPWM14 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM15", displayName: "Sync-in source is EPWM15 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM16", displayName: "Sync-in source is EPWM16 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP1", displayName: "Sync-in source is ECAP1 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP2", displayName: "Sync-in source is ECAP2 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP3", displayName: "Sync-in source is ECAP3 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP4", displayName: "Sync-in source is ECAP4 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP5", displayName: "Sync-in source is ECAP5 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP6", displayName: "Sync-in source is ECAP6 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP7", displayName: "Sync-in source is ECAP7 sync-out signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT5", displayName: "Sync-in source is Input XBAR out5 signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT6", displayName: "Sync-in source is Input XBAR out6 signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_ETHERCAT_SYNC0", displayName: "Sync-in source is Ethercat sync0 signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_ETHERCAT_SYNC1", displayName: "Sync-in source is Ethercat sync1 signal" },
	{ name: "ECAP_SYNC_IN_PULSE_SRC_FSIRXA_RX_TRIG1", displayName: "Sync-in source is FSI RXA RX signal" },
]
let ECAP_MAX_PRESCALER_VALUE = [
	{ name: "ECAP_MAX_PRESCALER_VALUE", displayName: "Maximum Pre-scaler value" },
]
let ECAP_ISR_SOURCE = [
	{ name: "ECAP_ISR_SOURCE_CAPTURE_EVENT_1", displayName: "Event 1 ISR source" },
	{ name: "ECAP_ISR_SOURCE_CAPTURE_EVENT_2", displayName: "Event 2 ISR source" },
	{ name: "ECAP_ISR_SOURCE_CAPTURE_EVENT_3", displayName: "Event 3 ISR source" },
	{ name: "ECAP_ISR_SOURCE_CAPTURE_EVENT_4", displayName: "Event 4 ISR source" },
	{ name: "ECAP_ISR_SOURCE_COUNTER_OVERFLOW", displayName: "Counter overflow ISR source" },
	{ name: "ECAP_ISR_SOURCE_COUNTER_PERIOD", displayName: "Counter equals period ISR source" },
	{ name: "ECAP_ISR_SOURCE_COUNTER_COMPARE", displayName: "Counter equals compare ISR source" },
]
module.exports = {
	ECAP_EmulationMode: ECAP_EmulationMode,
	ECAP_CaptureMode: ECAP_CaptureMode,
	ECAP_Events: ECAP_Events,
	ECAP_SyncOutMode: ECAP_SyncOutMode,
	ECAP_APWMPolarity: ECAP_APWMPolarity,
	ECAP_EventPolarity: ECAP_EventPolarity,
	ECAP_InputCaptureSignals: ECAP_InputCaptureSignals,
	ECAP_SyncInPulseSource: ECAP_SyncInPulseSource,
	ECAP_MAX_PRESCALER_VALUE: ECAP_MAX_PRESCALER_VALUE,
	ECAP_ISR_SOURCE: ECAP_ISR_SOURCE,
}
