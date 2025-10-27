let ADC_ClkPrescale = [
	{ name: "ADC_CLK_DIV_1_0", displayName: "ADCCLK = (input clock) / 1.0" },
	{ name: "ADC_CLK_DIV_2_0", displayName: "ADCCLK = (input clock) / 2.0" },
	{ name: "ADC_CLK_DIV_2_5", displayName: "ADCCLK = (input clock) / 2.5" },
	{ name: "ADC_CLK_DIV_3_0", displayName: "ADCCLK = (input clock) / 3.0" },
	{ name: "ADC_CLK_DIV_3_5", displayName: "ADCCLK = (input clock) / 3.5" },
	{ name: "ADC_CLK_DIV_4_0", displayName: "ADCCLK = (input clock) / 4.0" },
	{ name: "ADC_CLK_DIV_4_5", displayName: "ADCCLK = (input clock) / 4.5" },
	{ name: "ADC_CLK_DIV_5_0", displayName: "ADCCLK = (input clock) / 5.0" },
	{ name: "ADC_CLK_DIV_5_5", displayName: "ADCCLK = (input clock) / 5.5" },
	{ name: "ADC_CLK_DIV_6_0", displayName: "ADCCLK = (input clock) / 6.0" },
	{ name: "ADC_CLK_DIV_6_5", displayName: "ADCCLK = (input clock) / 6.5" },
	{ name: "ADC_CLK_DIV_7_0", displayName: "ADCCLK = (input clock) / 7.0" },
	{ name: "ADC_CLK_DIV_7_5", displayName: "ADCCLK = (input clock) / 7.5" },
	{ name: "ADC_CLK_DIV_8_0", displayName: "ADCCLK = (input clock) / 8.0" },
	{ name: "ADC_CLK_DIV_8_5", displayName: "ADCCLK = (input clock) / 8.5" },
]
let ADC_Trigger = [
	{ name: "ADC_TRIGGER_SW_ONLY", displayName: "Software only" },
	{ name: "ADC_TRIGGER_CPU1_TINT0", displayName: "CPU1 Timer 0, TINT0" },
	{ name: "ADC_TRIGGER_CPU1_TINT1", displayName: "CPU1 Timer 1, TINT1" },
	{ name: "ADC_TRIGGER_CPU1_TINT2", displayName: "CPU1 Timer 2, TINT2" },
	{ name: "ADC_TRIGGER_GPIO", displayName: "GPIO, ADCEXTSOC" },
	{ name: "ADC_TRIGGER_MCPWM1_SOCA", displayName: "MCPWM1 ADC SOCA" },
	{ name: "ADC_TRIGGER_MCPWM1_SOCB", displayName: "MCPWM1 ADC SOCB" },
	{ name: "ADC_TRIGGER_MCPWM1_SOCC", displayName: "MCPWM1 ADC SOCC" },
	{ name: "ADC_TRIGGER_MCPWM1_SOCD", displayName: "MCPWM1 ADC SOCD" },
	{ name: "ADC_TRIGGER_MCPWM3_SOCA", displayName: "MCPWM3 ADC SOCA" },
	{ name: "ADC_TRIGGER_MCPWM3_SOCB", displayName: "MCPWM3 ADC SOCB" },
	{ name: "ADC_TRIGGER_REPEATER1", displayName: "Repeater 1" },
]
let ADC_Channel = [
	{ name: "ADC_CH_ADCIN0", displayName: "ADCIN0 is converted" },
	{ name: "ADC_CH_ADCIN1", displayName: "ADCIN1 is converted" },
	{ name: "ADC_CH_ADCIN2", displayName: "ADCIN2 is converted" },
	{ name: "ADC_CH_ADCIN3", displayName: "ADCIN3 is converted" },
	{ name: "ADC_CH_ADCIN4", displayName: "ADCIN4 is converted" },
	{ name: "ADC_CH_ADCIN5", displayName: "ADCIN5 is converted" },
	{ name: "ADC_CH_ADCIN6", displayName: "ADCIN6 is converted" },
	{ name: "ADC_CH_ADCIN7", displayName: "ADCIN7 is converted" },
	{ name: "ADC_CH_ADCIN8", displayName: "ADCIN8 is converted" },
	{ name: "ADC_CH_ADCIN9", displayName: "ADCIN9 is converted" },
	{ name: "ADC_CH_ADCIN10", displayName: "ADCIN10 is converted" },
	{ name: "ADC_CH_ADCIN11", displayName: "ADCIN11 is converted" },
	{ name: "ADC_CH_ADCIN12", displayName: "ADCIN12 is converted" },
	{ name: "ADC_CH_ADCIN13", displayName: "ADCIN13 is converted" },
	{ name: "ADC_CH_ADCIN14", displayName: "ADCIN14 is converted" },
	{ name: "ADC_CH_ADCIN15", displayName: "ADCIN15 is converted" },
	{ name: "ADC_CH_ADCIN16", displayName: "ADCIN16 is converted" },
	{ name: "ADC_CH_ADCIN17", displayName: "ADCIN17 is converted" },
	{ name: "ADC_CH_ADCIN18", displayName: "ADCIN18 is converted" },
	{ name: "ADC_CH_ADCIN19", displayName: "ADCIN19 is converted" },
	{ name: "ADC_CH_ADCIN20", displayName: "ADCIN20 is converted" },
	{ name: "ADC_CH_ADCIN21", displayName: "ADCIN21 is converted" },
	{ name: "ADC_CH_ADCIN22", displayName: "ADCIN22 is converted" },
	{ name: "ADC_CH_ADCIN23", displayName: "ADCIN23 is converted" },
	{ name: "ADC_CH_ADCIN24", displayName: "ADCIN24 is converted" },
	{ name: "ADC_CH_ADCIN25", displayName: "ADCIN25 is converted" },
]
let ADC_PulseMode = [
	{ name: "ADC_PULSE_END_OF_ACQ_WIN", displayName: "Occurs at the end of the acquisition window" },
	{ name: "ADC_PULSE_END_OF_CONV", displayName: "Occurs at the end of the conversion" },
]
let ADC_IntNumber = [
	{ name: "ADC_INT_NUMBER1", displayName: "ADCINT1 Interrupt" },
	{ name: "ADC_INT_NUMBER2", displayName: "ADCINT2 Interrupt" },
]
let ADC_PPBNumber = [
	{ name: "ADC_PPB_NUMBER1", displayName: "Post-processing block 1" },
	{ name: "ADC_PPB_NUMBER2", displayName: "Post-processing block 2" },
	{ name: "ADC_PPB_NUMBER3", displayName: "Post-processing block 3" },
]
let ADC_SOCNumber = [
	{ name: "ADC_SOC_NUMBER0", displayName: "SOC/EOC number 0" },
	{ name: "ADC_SOC_NUMBER1", displayName: "SOC/EOC number 1" },
	{ name: "ADC_SOC_NUMBER2", displayName: "SOC/EOC number 2" },
	{ name: "ADC_SOC_NUMBER3", displayName: "SOC/EOC number 3" },
	{ name: "ADC_SOC_NUMBER4", displayName: "SOC/EOC number 4" },
	{ name: "ADC_SOC_NUMBER5", displayName: "SOC/EOC number 5" },
	{ name: "ADC_SOC_NUMBER6", displayName: "SOC/EOC number 6" },
	{ name: "ADC_SOC_NUMBER7", displayName: "SOC/EOC number 7" },
	{ name: "ADC_SOC_NUMBER8", displayName: "SOC/EOC number 8" },
	{ name: "ADC_SOC_NUMBER9", displayName: "SOC/EOC number 9" },
	{ name: "ADC_SOC_NUMBER10", displayName: "SOC/EOC number 10" },
	{ name: "ADC_SOC_NUMBER11", displayName: "SOC/EOC number 11" },
	{ name: "ADC_SOC_NUMBER12", displayName: "SOC/EOC number 12" },
	{ name: "ADC_SOC_NUMBER13", displayName: "SOC/EOC number 13" },
	{ name: "ADC_SOC_NUMBER14", displayName: "SOC/EOC number 14" },
	{ name: "ADC_SOC_NUMBER15", displayName: "SOC/EOC number 15" },
]
let ADC_IntSOCTrigger = [
	{ name: "ADC_INT_SOC_TRIGGER_NONE", displayName: "No ADCINT will trigger the SOC" },
	{ name: "ADC_INT_SOC_TRIGGER_ADCINT1", displayName: "ADCINT1 will trigger the SOC" },
	{ name: "ADC_INT_SOC_TRIGGER_ADCINT2", displayName: "ADCINT2 will trigger the SOC" },
	{ name: "ADC_INT_SOC_TRIGGER_EOC", displayName: "EOC of previous SOC will trigger" },
]
let ADC_PriorityMode = [
	{ name: "ADC_PRI_ALL_ROUND_ROBIN", displayName: "Round robin mode is used for all" },
	{ name: "ADC_PRI_SOC0_HIPRI", displayName: "SOC 0 hi pri, others in round robin" },
	{ name: "ADC_PRI_THRU_SOC1_HIPRI", displayName: "SOC 0-1 hi pri, others in round robin" },
	{ name: "ADC_PRI_THRU_SOC2_HIPRI", displayName: "SOC 0-2 hi pri, others in round robin" },
]
let ADC_SampleCAPResetValue = [
	{ name: "ADC_CAP_RESET_VREFLO", displayName: "Sample Capacitor reset to Vreflo" },
	{ name: "ADC_CAP_RESET_VREFHIBY2", displayName: "Sample Capacitor reset to Vrefhi/2" },
]
let ADC_ReferenceMode = [
	{ name: "ADC_REFERENCE_INTERNAL", displayName: "REFERENCE INTERNAL" },
	{ name: "ADC_REFERENCE_EXTERNAL", displayName: "REFERENCE EXTERNAL" },
]
let ADC_ReferenceVoltage = [
	{ name: "ADC_REFERENCE_3_3V", displayName: "REFERENCE 3 3V" },
	{ name: "ADC_REFERENCE_2_5V", displayName: "REFERENCE 2 5V" },
	{ name: "ADC_REFERENCE_VREFHI", displayName: "This value is valid when ADC reference" },
]
let ADC_SyncInput = [
	{ name: "ADC_SYNCIN_DISABLE", displayName: "ADC Syncin is disabled" },
	{ name: "ADC_SYNCIN_INPUTXBAROUTPUT5", displayName: "ADC Syncin is INPUTXBAROUTPUT5" },
	{ name: "ADC_SYNCIN_INPUTXBAROUTPUT6", displayName: "ADC Syncin is INPUTXBAROUTPUT6" },
	{ name: "ADC_SYNCIN_ECAP1YNCOUT", displayName: "ADC Syncin is ECAP1YNCOUT" },
	{ name: "ADC_SYNCIN_MCPWM1SYNCPER", displayName: "MCPWM1 SYNCPER Signal" },
	{ name: "ADC_SYNCIN_MCPWM3SYNCPER", displayName: "MCPWM3 SYNCPER Signal" },
]
let ADC_PPBIntSrcSelect = [
	{ name: "ADC_PPB_OS_INT_1", displayName: "PCount generates PPB interrupt" },
	{ name: "ADC_PPB_OS_INT_2", displayName: "PCount/Sync generates PPB interrupt" },
]
let ADC_IntTrigger = [
	{ name: "ADC_INT_TRIGGER_EOC0", displayName: "SOC/EOC0" },
	{ name: "ADC_INT_TRIGGER_EOC1", displayName: "SOC/EOC1" },
	{ name: "ADC_INT_TRIGGER_EOC2", displayName: "SOC/EOC2" },
	{ name: "ADC_INT_TRIGGER_EOC3", displayName: "SOC/EOC3" },
	{ name: "ADC_INT_TRIGGER_EOC4", displayName: "SOC/EOC4" },
	{ name: "ADC_INT_TRIGGER_EOC5", displayName: "SOC/EOC5" },
	{ name: "ADC_INT_TRIGGER_EOC6", displayName: "SOC/EOC6" },
	{ name: "ADC_INT_TRIGGER_EOC7", displayName: "SOC/EOC7" },
	{ name: "ADC_INT_TRIGGER_EOC8", displayName: "SOC/EOC8" },
	{ name: "ADC_INT_TRIGGER_EOC9", displayName: "SOC/EOC9" },
	{ name: "ADC_INT_TRIGGER_EOC10", displayName: "SOC/EOC10" },
	{ name: "ADC_INT_TRIGGER_EOC11", displayName: "SOC/EOC11" },
	{ name: "ADC_INT_TRIGGER_EOC12", displayName: "SOC/EOC12" },
	{ name: "ADC_INT_TRIGGER_EOC13", displayName: "SOC/EOC13" },
	{ name: "ADC_INT_TRIGGER_EOC14", displayName: "SOC/EOC14" },
	{ name: "ADC_INT_TRIGGER_EOC15", displayName: "SOC/EOC15" },
	{ name: "ADC_INT_TRIGGER_OSINT1", displayName: "OSINT1" },
]
let ADC_PPBCompSource = [
	{ name: "ADC_PPB_COMPSOURCE_RESULT", displayName: "PPB compare source is ADCRESULT" },
	{ name: "ADC_PPB_COMPSOURCE_SUM", displayName: "PPB compare source is SUM" },
]
let ADC_RepInstance = [
	{ name: "ADC_REPINST1", displayName: "Select ADC repeater instance 1" },
]
let ADC_EVT = [
	{ name: "ADC_EVT_TRIPHI", displayName: "Trip High Event" },
	{ name: "ADC_EVT_TRIPLO", displayName: "Trip Low Event" },
	{ name: "ADC_EVT_ZERO", displayName: "Zero Crossing Event" },
	{ name: "ADC_EVT_NLIMIT", displayName: "Within Trip limit Event" },
]
let ADC_FORCE = [
	{ name: "ADC_FORCE_SOC0", displayName: "SW trigger ADC SOC 0" },
	{ name: "ADC_FORCE_SOC1", displayName: "SW trigger ADC SOC 1" },
	{ name: "ADC_FORCE_SOC2", displayName: "SW trigger ADC SOC 2" },
	{ name: "ADC_FORCE_SOC3", displayName: "SW trigger ADC SOC 3" },
	{ name: "ADC_FORCE_SOC4", displayName: "SW trigger ADC SOC 4" },
	{ name: "ADC_FORCE_SOC5", displayName: "SW trigger ADC SOC 5" },
	{ name: "ADC_FORCE_SOC6", displayName: "SW trigger ADC SOC 6" },
	{ name: "ADC_FORCE_SOC7", displayName: "SW trigger ADC SOC 7" },
	{ name: "ADC_FORCE_SOC8", displayName: "SW trigger ADC SOC 8" },
	{ name: "ADC_FORCE_SOC9", displayName: "SW trigger ADC SOC 9" },
	{ name: "ADC_FORCE_SOC10", displayName: "SW trigger ADC SOC 10" },
	{ name: "ADC_FORCE_SOC11", displayName: "SW trigger ADC SOC 11" },
	{ name: "ADC_FORCE_SOC12", displayName: "SW trigger ADC SOC 12" },
	{ name: "ADC_FORCE_SOC13", displayName: "SW trigger ADC SOC 13" },
	{ name: "ADC_FORCE_SOC14", displayName: "SW trigger ADC SOC 14" },
	{ name: "ADC_FORCE_SOC15", displayName: "SW trigger ADC SOC 15" },
]
let ADC_REPEATER_MODULE_BUSY = [
	{ name: "ADC_REPEATER_MODULE_BUSY", displayName: "REPEATER MODULE BUSY" },
]
let ADC_REP1CTL = [
	{ name: "ADC_REP1CTL_ACTIVEMODE_S", displayName: "REP1CTL ACTIVEMODE S" },
	{ name: "ADC_REP1CTL_MODULEBUSY_S", displayName: "REP1CTL MODULEBUSY S" },
]
let ADC_REPSTATUS_MASK = [
	{ name: "ADC_REPSTATUS_MASK", displayName: "REPSTATUS MASK" },
]
module.exports = {
	ADC_ClkPrescale: ADC_ClkPrescale,
	ADC_Trigger: ADC_Trigger,
	ADC_Channel: ADC_Channel,
	ADC_PulseMode: ADC_PulseMode,
	ADC_IntNumber: ADC_IntNumber,
	ADC_PPBNumber: ADC_PPBNumber,
	ADC_SOCNumber: ADC_SOCNumber,
	ADC_IntSOCTrigger: ADC_IntSOCTrigger,
	ADC_PriorityMode: ADC_PriorityMode,
	ADC_SampleCAPResetValue: ADC_SampleCAPResetValue,
	ADC_ReferenceMode: ADC_ReferenceMode,
	ADC_ReferenceVoltage: ADC_ReferenceVoltage,
	ADC_SyncInput: ADC_SyncInput,
	ADC_PPBIntSrcSelect: ADC_PPBIntSrcSelect,
	ADC_IntTrigger: ADC_IntTrigger,
	ADC_PPBCompSource: ADC_PPBCompSource,
	ADC_RepInstance: ADC_RepInstance,
	ADC_EVT: ADC_EVT,
	ADC_FORCE: ADC_FORCE,
	ADC_REPEATER_MODULE_BUSY: ADC_REPEATER_MODULE_BUSY,
	ADC_REP1CTL: ADC_REP1CTL,
	ADC_REPSTATUS_MASK: ADC_REPSTATUS_MASK,
}
