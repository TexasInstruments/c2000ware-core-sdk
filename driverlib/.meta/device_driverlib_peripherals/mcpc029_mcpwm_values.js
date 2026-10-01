let MCPWM_TimeBaseCountMode = [
	{ name: "MCPWM_COUNTER_MODE_UP", value: 0 },
	{ name: "MCPWM_COUNTER_MODE_UP_DOWN", value: 1 },
	{ name: "MCPWM_COUNTER_MODE_STOP_FREEZE", value: 2 },
]
let MCPWM_ClockDivider = [
	{ name: "MCPWM_CLOCK_DIVIDER_1", value: 0 },
	{ name: "MCPWM_CLOCK_DIVIDER_2", value: 1 },
	{ name: "MCPWM_CLOCK_DIVIDER_4", value: 2 },
	{ name: "MCPWM_CLOCK_DIVIDER_8", value: 3 },
	{ name: "MCPWM_CLOCK_DIVIDER_16", value: 4 },
	{ name: "MCPWM_CLOCK_DIVIDER_32", value: 5 },
	{ name: "MCPWM_CLOCK_DIVIDER_64", value: 6 },
	{ name: "MCPWM_CLOCK_DIVIDER_128", value: 7 },
	{ name: "MCPWM_CLOCK_DIVIDER_256", value: 8 },
	{ name: "MCPWM_CLOCK_DIVIDER_512", value: 9 },
	{ name: "MCPWM_CLOCK_DIVIDER_1024", value: 10 },
	{ name: "MCPWM_CLOCK_DIVIDER_2048", value: 11 },
	{ name: "MCPWM_CLOCK_DIVIDER_4096", value: 12 },
	{ name: "MCPWM_CLOCK_DIVIDER_8192", value: 13 },
	{ name: "MCPWM_CLOCK_DIVIDER_16384", value: 14 },
	{ name: "MCPWM_CLOCK_DIVIDER_32768", value: 15 },
]
let MCPWM_EmulationMode = [
	{ name: "MCPWM_EMULATION_STOP_AFTER_NEXT_TB", value: 0 },
	{ name: "MCPWM_EMULATION_STOP_AFTER_FULL_CYCLE", value: 1 },
	{ name: "MCPWM_EMULATION_FREE_RUN", value: 2 },
]
let MCPWM_PeriodLoadMode = [
	{ name: "MCPWM_PERIOD_SHADOW_LOAD_ENABLE", value: 0 },
	{ name: "MCPWM_PERIOD_SHADOW_LOAD_DISABLE", value: 1 },
]
let MCPWM_SyncCountMode = [
	{ name: "MCPWM_COUNT_MODE_DOWN_AFTER_SYNC", value: 0 },
	{ name: "MCPWM_COUNT_MODE_UP_AFTER_SYNC", value: 1 },
]
let MCPWM_SyncOutPulseMode = [
	{ name: "MCPWM_SYNC_OUT_PULSE_ON_SOFTWARE", value: 0 },
	{ name: "MCPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO", value: 1 },
	{ name: "MCPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_C", value: 2 },
	{ name: "MCPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_D", value: 3 },
	{ name: "MCPWM_SYNC_OUT_PULSE_DISABLED", value: 4 },
]
let MCPWM_SyncPulseSource = [
	{ name: "MCPWM_SYNC_PULSE_DISABLED", value: 0 },
	{ name: "MCPWM_SYNCPERSEL_SOURCE_PERIOD", value: 2 },
	{ name: "MCPWM_SYNCPERSEL_SOURCE_ZERO", value: 3 },
	{ name: "MCPWM_SYNCPERSEL_SOURCE_CMPC_UP", value: 4 },
	{ name: "MCPWM_SYNCPERSEL_SOURCE_CMPC_DOWN", value: 5 },
	{ name: "MCPWM_SYNCPERSEL_SOURCE_CMPD_UP", value: 6 },
	{ name: "MCPWM_SYNCPERSEL_SOURCE_CMPD_DOWN", value: 7 },
]
let MCPWM_SyncInPulseSource = [
	{ name: "MCPWM_SYNC_IN_PULSE_SRC_DISABLE", value: 0x0 },
	{ name: "MCPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT5", value: 0x1 },
	{ name: "MCPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT6", value: 0x2 },
	{ name: "MCPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP1", value: 0x3 },
	{ name: "MCPWM_SYNC_IN_PULSE_SRC_SYNCOUT_MCPWM1", value: 0x5 },
	{ name: "MCPWM_SYNC_IN_PULSE_SRC_SYNCOUT_MCPWM3", value: 0x7	 },
]
let MCPWM_CounterCompareModule = [
	{ name: "MCPWM_COUNTER_COMPARE_1A", value: 0 },
	{ name: "MCPWM_COUNTER_COMPARE_1B", value: 1 },
	{ name: "MCPWM_COUNTER_COMPARE_2A", value: 2 },
	{ name: "MCPWM_COUNTER_COMPARE_2B", value: 3 },
	{ name: "MCPWM_COUNTER_COMPARE_3A", value: 4 },
	{ name: "MCPWM_COUNTER_COMPARE_3B", value: 5 },
	{ name: "MCPWM_COUNTER_COMPARE_C", value: 6 },
	{ name: "MCPWM_COUNTER_COMPARE_D", value: 7 },
]
let MCPWM_CounterCompareLoadMode = [
	{ name: "MCPWM_COMP_LOAD_ON_CNTR_ZERO", value: 0 },
	{ name: "MCPWM_COMP_LOAD_ON_CNTR_PERIOD", value: 1 },
	{ name: "MCPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD", value: 2 },
	{ name: "MCPWM_COMP_LOAD_FREEZE", value: 3 },
]
let MCPWM_ActionQualifierOutputModule = [
	{ name: "MCPWM_AQ_OUTPUT_1A", value: 0 },
	{ name: "MCPWM_AQ_OUTPUT_1B", value: 1 },
	{ name: "MCPWM_AQ_OUTPUT_2A", value: 2 },
	{ name: "MCPWM_AQ_OUTPUT_2B", value: 3 },
	{ name: "MCPWM_AQ_OUTPUT_3A", value: 4 },
	{ name: "MCPWM_AQ_OUTPUT_3B", value: 5 },
]
let MCPWM_ActionQualifierOutput = [
	{ name: "MCPWM_AQ_OUTPUT_NO_CHANGE", value: 0 },
	{ name: "MCPWM_AQ_OUTPUT_LOW", value: 1 },
	{ name: "MCPWM_AQ_OUTPUT_HIGH", value: 2 },
	{ name: "MCPWM_AQ_OUTPUT_TOGGLE", value: 3 },
]
let MCPWM_ActionQualifierSWForceOutput = [
	{ name: "MCPWM_AQ_SW_FORCE_DISABLED", value: 0 },
	{ name: "MCPWM_AQ_SW_CONTINUOUS_LOW", value: 1 },
	{ name: "MCPWM_AQ_SW_CONTINUOUS_HIGH", value: 2 },
	{ name: "MCPWM_AQ_SW_ONE_SHOT_LOW", value: 5 },
	{ name: "MCPWM_AQ_SW_ONE_SHOT_HIGH", value: 6 },
	{ name: "MCPWM_AQ_SW_ONE_SHOT_TOGGLE", value: 7 },
]
let MCPWM_ActionQualifierModule = [
	{ name: "MCPWM_ACTION_QUALIFIER_1A", value: 0 },
	{ name: "MCPWM_ACTION_QUALIFIER_1B", value: 1 },
	{ name: "MCPWM_ACTION_QUALIFIER_2A", value: 2 },
	{ name: "MCPWM_ACTION_QUALIFIER_2B", value: 3 },
	{ name: "MCPWM_ACTION_QUALIFIER_3A", value: 4 },
	{ name: "MCPWM_ACTION_QUALIFIER_3B", value: 5 },
]
let MCPWM_ActionQualifierLoadMode = [
	{ name: "MCPWM_AQ_LOAD_ON_CNTR_ZERO", value: 0 },
	{ name: "MCPWM_AQ_LOAD_ON_CNTR_PERIOD", value: 1 },
	{ name: "MCPWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD", value: 2 },
	{ name: "MCPWM_AQ_LOAD_FREEZE", value: 3 },
]
let MCPWM_ActionQualifierOutputEvent = [
	{ name: "MCPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO", value: MCPWM_PWM1_AQCTLA_ZRO_S },
	{ name: "MCPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD", value: MCPWM_PWM1_AQCTLA_PRD_S },
	{ name: "MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA", value: MCPWM_PWM1_AQCTLA_CA_S },
	{ name: "MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA", value: MCPWM_PWM1_AQCTLA_CAD_S },
	{ name: "MCPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB", value: MCPWM_PWM1_AQCTLA_CB_S },
	{ name: "MCPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB", value: MCPWM_PWM1_AQCTLA_CBD_S },
]
let MCPWM_ActionQualifierEventAction = [
	{ name: "MCPWM_AQ_OUTPUT_NO_CHANGE_ZERO", value: 0x0 },
	{ name: "MCPWM_AQ_OUTPUT_LOW_ZERO", value: 0x1 },
	{ name: "MCPWM_AQ_OUTPUT_HIGH_ZERO", value: 0x2 },
	{ name: "MCPWM_AQ_OUTPUT_TOGGLE_ZERO", value: 0x3 },
	{ name: "MCPWM_AQ_OUTPUT_NO_CHANGE_PERIOD", value: 0x0 },
	{ name: "MCPWM_AQ_OUTPUT_LOW_PERIOD", value: 0x4 },
	{ name: "MCPWM_AQ_OUTPUT_HIGH_PERIOD", value: 0x8 },
	{ name: "MCPWM_AQ_OUTPUT_TOGGLE_PERIOD", value: 0xC },
	{ name: "MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA", value: 0x00 },
	{ name: "MCPWM_AQ_OUTPUT_LOW_UP_CMPA", value: 0x10 },
	{ name: "MCPWM_AQ_OUTPUT_HIGH_UP_CMPA", value: 0x20 },
	{ name: "MCPWM_AQ_OUTPUT_TOGGLE_UP_CMPA", value: 0x30 },
	{ name: "MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA", value: 0x00 },
	{ name: "MCPWM_AQ_OUTPUT_LOW_DOWN_CMPA", value: 0x40 },
	{ name: "MCPWM_AQ_OUTPUT_HIGH_DOWN_CMPA", value: 0x80 },
	{ name: "MCPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPA", value: 0xC0 },
	{ name: "MCPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB", value: 0x000 },
	{ name: "MCPWM_AQ_OUTPUT_LOW_UP_CMPB", value: 0x100 },
	{ name: "MCPWM_AQ_OUTPUT_HIGH_UP_CMPB", value: 0x200 },
	{ name: "MCPWM_AQ_OUTPUT_TOGGLE_UP_CMPB", value: 0x300 },
	{ name: "MCPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB", value: 0x000 },
	{ name: "MCPWM_AQ_OUTPUT_LOW_DOWN_CMPB", value: 0x400 },
	{ name: "MCPWM_AQ_OUTPUT_HIGH_DOWN_CMPB", value: 0x800 },
	{ name: "MCPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPB", value: 0xC00 },
]
let MCPWM_GlobalLoadTrigger = [
	{ name: "MCPWM_GL_LOAD_PULSE_CNTR_ZERO", value: 0x0 },
	{ name: "MCPWM_GL_LOAD_PULSE_CNTR_PERIOD", value: 0x1 },
	{ name: "MCPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD", value: 0x2 },
	{ name: "MCPWM_GL_LOAD_PULSE_GLOBAL_FORCE", value: 0xF },
]
let MCPWM_DeadBandOutput = [
	{ name: "MCPWM_DB_OUTPUT_A", value: 1 },
	{ name: "MCPWM_DB_OUTPUT_B", value: 0 },
]
let MCPWM_DeadBandDelayMode = [
	{ name: "MCPWM_DB_RED", value: 1 },
	{ name: "MCPWM_DB_FED", value: 0 },
]
let MCPWM_DeadBandPolarity = [
	{ name: "MCPWM_DB_POLARITY_ACTIVE_HIGH", value: 0 },
	{ name: "MCPWM_DB_POLARITY_ACTIVE_LOW", value: 1 },
]
let MCPWM_RisingEdgeDelayLoadMode = [
	{ name: "MCPWM_RED_LOAD_ON_CNTR_ZERO", value: 0 },
	{ name: "MCPWM_RED_LOAD_ON_CNTR_PERIOD", value: 1 },
	{ name: "MCPWM_RED_LOAD_ON_CNTR_ZERO_PERIOD", value: 2 },
	{ name: "MCPWM_RED_LOAD_FREEZE", value: 3 },
]
let MCPWM_FallingEdgeDelayLoadMode = [
	{ name: "MCPWM_FED_LOAD_ON_CNTR_ZERO", value: 0 },
	{ name: "MCPWM_FED_LOAD_ON_CNTR_PERIOD", value: 1 },
	{ name: "MCPWM_FED_LOAD_ON_CNTR_ZERO_PERIOD", value: 2 },
	{ name: "MCPWM_FED_LOAD_FREEZE", value: 3 },
]
let MCPWM_TripZoneEvent = [
	{ name: "MCPWM_TZ_ACTION_EVENT_TZA", value: 0 },
	{ name: "MCPWM_TZ_ACTION_EVENT_TZB", value: 1 },
]
let MCPWM_TripZoneAction = [
	{ name: "MCPWM_TZ_ACTION_HIGH_Z", value: 0 },
	{ name: "MCPWM_TZ_ACTION_HIGH", value: 1 },
	{ name: "MCPWM_TZ_ACTION_LOW", value: 2 },
	{ name: "MCPWM_TZ_ACTION_DISABLE", value: 3 },
]
let MCPWM_TripZoneCBCMode = [
	{ name: "MCPWM_TZ_CBC_PULSE_CLR_NONE", value: 0 },
	{ name: "MCPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO", value: 1 },
	{ name: "MCPWM_TZ_CBC_PULSE_CLR_CNTR_PERIOD", value: 2 },
	{ name: "MCPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD", value: 3 },
]
let MCPWM_ADCStartOfConversionType = [
	{ name: "MCPWM_SOC_A", value: 0 },
	{ name: "MCPWM_SOC_B", value: 1 },
	{ name: "MCPWM_SOC_C", value: 2 },
	{ name: "MCPWM_SOC_D", value: 3 },
]
let MCPWM_ADCStartOfConversionSource = [
	{ name: "MCPWM_SOC_DISABLED", value: 0 },
	{ name: "MCPWM_SOC_TBCTR_ZERO", value: 2 },
	{ name: "MCPWM_SOC_TBCTR_PERIOD", value: 3 },
	{ name: "MCPWM_SOC_TBCTR_ZERO_PERIOD", value: 4 },
	{ name: "MCPWM_SOC_TBCTR_U_CMPC", value: 8 },
	{ name: "MCPWM_SOC_TBCTR_U_CMPD", value: 9 },
	{ name: "MCPWM_SOC_TBCTR_U_CMP1A", value: 10 },
	{ name: "MCPWM_SOC_TBCTR_U_CMP1B", value: 11 },
	{ name: "MCPWM_SOC_TBCTR_U_CMP2A", value: 12 },
	{ name: "MCPWM_SOC_TBCTR_U_CMP2B", value: 13 },
	{ name: "MCPWM_SOC_TBCTR_U_CMP3A", value: 14 },
	{ name: "MCPWM_SOC_TBCTR_U_CMP3B", value: 15 },
	{ name: "MCPWM_SOC_TBCTR_D_CMPC", value: 16 },
	{ name: "MCPWM_SOC_TBCTR_D_CMPD", value: 17 },
	{ name: "MCPWM_SOC_TBCTR_D_CMP1A", value: 18 },
	{ name: "MCPWM_SOC_TBCTR_D_CMP1B", value: 19 },
	{ name: "MCPWM_SOC_TBCTR_D_CMP2A", value: 20 },
	{ name: "MCPWM_SOC_TBCTR_D_CMP2B", value: 21 },
	{ name: "MCPWM_SOC_TBCTR_D_CMP3A", value: 22 },
	{ name: "MCPWM_SOC_TBCTR_D_CMP3B", value: 23 },
]
let MCPWM_EventTriggerType = [
	{ name: "MCPWM_ET_1", value: 0 },
	{ name: "MCPWM_ET_2", value: 1 },
]
let MCPWM_EventTriggerSource = [
	{ name: "MCPWM_EVT_DISABLED", value: 0 },
	{ name: "MCPWM_EVT_TBCTR_ZERO", value: 2 },
	{ name: "MCPWM_EVT_TBCTR_PERIOD", value: 3 },
	{ name: "MCPWM_EVT_TBCTR_ZERO_PERIOD", value: 4 },
	{ name: "MCPWM_EVT_TBCTR_U_CMPC", value: 8 },
	{ name: "MCPWM_EVT_TBCTR_U_CMPD", value: 9 },
	{ name: "MCPWM_EVT_TBCTR_U_CMP1A", value: 10 },
	{ name: "MCPWM_EVT_TBCTR_U_CMP1B", value: 11 },
	{ name: "MCPWM_EVT_TBCTR_U_CMP2A", value: 12 },
	{ name: "MCPWM_EVT_TBCTR_U_CMP2B", value: 13 },
	{ name: "MCPWM_EVT_TBCTR_U_CMP3A", value: 14 },
	{ name: "MCPWM_EVT_TBCTR_U_CMP3B", value: 15 },
	{ name: "MCPWM_EVT_TBCTR_D_CMPC", value: 16 },
	{ name: "MCPWM_EVT_TBCTR_D_CMPD", value: 17 },
	{ name: "MCPWM_EVT_TBCTR_D_CMP1A", value: 18 },
	{ name: "MCPWM_EVT_TBCTR_D_CMP1B", value: 19 },
	{ name: "MCPWM_EVT_TBCTR_D_CMP2A", value: 20 },
	{ name: "MCPWM_EVT_TBCTR_D_CMP2B", value: 21 },
	{ name: "MCPWM_EVT_TBCTR_D_CMP3A", value: 22 },
	{ name: "MCPWM_EVT_TBCTR_D_CMP3B", value: 23 },
]
let MCPWM_TIME_BASE_STATUS_COUNT = [
	{ name: "MCPWM_TIME_BASE_STATUS_COUNT_UP", value: 1 },
	{ name: "MCPWM_TIME_BASE_STATUS_COUNT_DOWN", value: 0 },
]
let MCPWM_DB_INPUT = [
	{ name: "MCPWM_DB_INPUT_MCPWMA", value: 0 },
	{ name: "MCPWM_DB_INPUT_MCPWMB", value: 1 },
	{ name: "MCPWM_DB_INPUT_DB_RED", value: 2 },
]
let MCPWM_TZ_SIGNAL = [
	{ name: "MCPWM_TZ_SIGNAL_CBC1", value: "MCPWM_TZSEL_CBC1" },
	{ name: "MCPWM_TZ_SIGNAL_CBC2", value: "MCPWM_TZSEL_CBC2" },
	{ name: "MCPWM_TZ_SIGNAL_CBC3", value: "MCPWM_TZSEL_CBC3" },
	{ name: "MCPWM_TZ_SIGNAL_CBC4", value: "MCPWM_TZSEL_CBC4" },
	{ name: "MCPWM_TZ_SIGNAL_CBC5", value: "MCPWM_TZSEL_CBC5" },
	{ name: "MCPWM_TZ_SIGNAL_CBC6", value: "MCPWM_TZSEL_CBC6" },
	{ name: "MCPWM_TZ_SIGNAL_CBC7", value: "MCPWM_TZSEL_CBC7" },
	{ name: "MCPWM_TZ_SIGNAL_CBC8", value: "MCPWM_TZSEL_CBC8" },
	{ name: "MCPWM_TZ_SIGNAL_OSHT1", value: "MCPWM_TZSEL_OST1" },
	{ name: "MCPWM_TZ_SIGNAL_OSHT2", value: "MCPWM_TZSEL_OST2" },
	{ name: "MCPWM_TZ_SIGNAL_OSHT3", value: "MCPWM_TZSEL_OST3" },
	{ name: "MCPWM_TZ_SIGNAL_OSHT4", value: "MCPWM_TZSEL_OST4" },
	{ name: "MCPWM_TZ_SIGNAL_OSHT5", value: "MCPWM_TZSEL_OST5" },
	{ name: "MCPWM_TZ_SIGNAL_OSHT6", value: "MCPWM_TZSEL_OST6" },
	{ name: "MCPWM_TZ_SIGNAL_OSHT7", value: "MCPWM_TZSEL_OST7" },
	{ name: "MCPWM_TZ_SIGNAL_OSHT8", value: "MCPWM_TZSEL_OST8" },
]
let MCPWM_TZ_FLAG = [
	{ name: "MCPWM_TZ_FLAG_CBC_TZ1", value: "MCPWM_TZCBCOSTFLAG_CBC1" },
	{ name: "MCPWM_TZ_FLAG_CBC_TZ2", value: "MCPWM_TZCBCOSTFLAG_CBC2" },
	{ name: "MCPWM_TZ_FLAG_CBC_TZ3", value: "MCPWM_TZCBCOSTFLAG_CBC3" },
	{ name: "MCPWM_TZ_FLAG_CBC_TZ4", value: "MCPWM_TZCBCOSTFLAG_CBC4" },
	{ name: "MCPWM_TZ_FLAG_CBC_TZ5", value: "MCPWM_TZCBCOSTFLAG_CBC5" },
	{ name: "MCPWM_TZ_FLAG_CBC_TZ6", value: "MCPWM_TZCBCOSTFLAG_CBC6" },
	{ name: "MCPWM_TZ_FLAG_CBC_TZ7", value: "MCPWM_TZCBCOSTFLAG_CBC7" },
	{ name: "MCPWM_TZ_FLAG_CBC_TZ8", value: "MCPWM_TZCBCOSTFLAG_CBC8" },
	{ name: "MCPWM_TZ_FLAG_OST_TZ1", value: "MCPWM_TZCBCOSTFLAG_OST1" },
	{ name: "MCPWM_TZ_FLAG_OST_TZ2", value: "MCPWM_TZCBCOSTFLAG_OST2" },
	{ name: "MCPWM_TZ_FLAG_OST_TZ3", value: "MCPWM_TZCBCOSTFLAG_OST3" },
	{ name: "MCPWM_TZ_FLAG_OST_TZ4", value: "MCPWM_TZCBCOSTFLAG_OST4" },
	{ name: "MCPWM_TZ_FLAG_OST_TZ5", value: "MCPWM_TZCBCOSTFLAG_OST5" },
	{ name: "MCPWM_TZ_FLAG_OST_TZ6", value: "MCPWM_TZCBCOSTFLAG_OST6" },
	{ name: "MCPWM_TZ_FLAG_OST_TZ7", value: "MCPWM_TZCBCOSTFLAG_OST7" },
	{ name: "MCPWM_TZ_FLAG_OST_TZ8", value: "MCPWM_TZCBCOSTFLAG_OST8" },
	{ name: "MCPWM_TZ_FLAG_ALL", value: "(MCPWM_TZ_FLAG_CBC_TZ1" },
]
let MCPWM_INT = [
	{ name: "MCPWM_INT_TZ_CBC", value: "MCPWM_INTFLAG_CBC" },
	{ name: "MCPWM_INT_TZ_OST", value: "MCPWM_INTFLAG_OST" },
	{ name: "MCPWM_INT_ET_1", value: "MCPWM_INTFLAG_ET1" },
	{ name: "MCPWM_INT_ET_2", value: "MCPWM_INTFLAG_ET2" },
	{ name: "MCPWM_INT_TBCTR_OVF", value: "MCPWM_INTFLAG_CNT_OVF" },
	{ name: "MCPWM_INT_SOURCE_ALL", value: "(MCPWM_INT_TZ_CBC" },
]
module.exports = {
	MCPWM_TimeBaseCountMode: MCPWM_TimeBaseCountMode,
	MCPWM_ClockDivider: MCPWM_ClockDivider,
	MCPWM_EmulationMode: MCPWM_EmulationMode,
	MCPWM_PeriodLoadMode: MCPWM_PeriodLoadMode,
	MCPWM_SyncCountMode: MCPWM_SyncCountMode,
	MCPWM_SyncOutPulseMode: MCPWM_SyncOutPulseMode,
	MCPWM_SyncPulseSource: MCPWM_SyncPulseSource,
	MCPWM_SyncInPulseSource: MCPWM_SyncInPulseSource,
	MCPWM_CounterCompareModule: MCPWM_CounterCompareModule,
	MCPWM_CounterCompareLoadMode: MCPWM_CounterCompareLoadMode,
	MCPWM_ActionQualifierOutputModule: MCPWM_ActionQualifierOutputModule,
	MCPWM_ActionQualifierOutput: MCPWM_ActionQualifierOutput,
	MCPWM_ActionQualifierSWForceOutput: MCPWM_ActionQualifierSWForceOutput,
	MCPWM_ActionQualifierModule: MCPWM_ActionQualifierModule,
	MCPWM_ActionQualifierLoadMode: MCPWM_ActionQualifierLoadMode,
	MCPWM_ActionQualifierOutputEvent: MCPWM_ActionQualifierOutputEvent,
	MCPWM_ActionQualifierEventAction: MCPWM_ActionQualifierEventAction,
	MCPWM_GlobalLoadTrigger: MCPWM_GlobalLoadTrigger,
	MCPWM_DeadBandOutput: MCPWM_DeadBandOutput,
	MCPWM_DeadBandDelayMode: MCPWM_DeadBandDelayMode,
	MCPWM_DeadBandPolarity: MCPWM_DeadBandPolarity,
	MCPWM_RisingEdgeDelayLoadMode: MCPWM_RisingEdgeDelayLoadMode,
	MCPWM_FallingEdgeDelayLoadMode: MCPWM_FallingEdgeDelayLoadMode,
	MCPWM_TripZoneEvent: MCPWM_TripZoneEvent,
	MCPWM_TripZoneAction: MCPWM_TripZoneAction,
	MCPWM_TripZoneCBCMode: MCPWM_TripZoneCBCMode,
	MCPWM_ADCStartOfConversionType: MCPWM_ADCStartOfConversionType,
	MCPWM_ADCStartOfConversionSource: MCPWM_ADCStartOfConversionSource,
	MCPWM_EventTriggerType: MCPWM_EventTriggerType,
	MCPWM_EventTriggerSource: MCPWM_EventTriggerSource,
	MCPWM_TIME_BASE_STATUS_COUNT: MCPWM_TIME_BASE_STATUS_COUNT,
	MCPWM_DB_INPUT: MCPWM_DB_INPUT,
	MCPWM_TZ_SIGNAL: MCPWM_TZ_SIGNAL,
	MCPWM_TZ_FLAG: MCPWM_TZ_FLAG,
	MCPWM_INT: MCPWM_INT,
}
