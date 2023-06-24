let EPWM_EmulationMode = [
	{ name: "EPWM_EMULATION_STOP_AFTER_NEXT_TB", value: 0 },
	{ name: "EPWM_EMULATION_STOP_AFTER_FULL_CYCLE", value: 1 },
	{ name: "EPWM_EMULATION_FREE_RUN", value: 2 },
]
let EPWM_SyncCountMode = [
	{ name: "EPWM_COUNT_MODE_DOWN_AFTER_SYNC", value: 0 },
	{ name: "EPWM_COUNT_MODE_UP_AFTER_SYNC", value: 1 },
]
let EPWM_ClockDivider = [
	{ name: "EPWM_CLOCK_DIVIDER_1", value: 0 },
	{ name: "EPWM_CLOCK_DIVIDER_2", value: 1 },
	{ name: "EPWM_CLOCK_DIVIDER_4", value: 2 },
	{ name: "EPWM_CLOCK_DIVIDER_8", value: 3 },
	{ name: "EPWM_CLOCK_DIVIDER_16", value: 4 },
	{ name: "EPWM_CLOCK_DIVIDER_32", value: 5 },
	{ name: "EPWM_CLOCK_DIVIDER_64", value: 6 },
	{ name: "EPWM_CLOCK_DIVIDER_128", value: 7 },
]
let EPWM_HSClockDivider = [
	{ name: "EPWM_HSCLOCK_DIVIDER_1", value: 0 },
	{ name: "EPWM_HSCLOCK_DIVIDER_2", value: 1 },
	{ name: "EPWM_HSCLOCK_DIVIDER_4", value: 2 },
	{ name: "EPWM_HSCLOCK_DIVIDER_6", value: 3 },
	{ name: "EPWM_HSCLOCK_DIVIDER_8", value: 4 },
	{ name: "EPWM_HSCLOCK_DIVIDER_10", value: 5 },
	{ name: "EPWM_HSCLOCK_DIVIDER_12", value: 6 },
	{ name: "EPWM_HSCLOCK_DIVIDER_14", value: 7 },
]
let EPWM_SyncOutPulseMode = [
	{ name: "EPWM_SYNC_OUT_PULSE_ON_SOFTWARE", value: 0 },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN", value: 0 },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO", value: 1 },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_B", value: 2 },
	{ name: "EPWM_SYNC_OUT_PULSE_DISABLED", value: 4 },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_C", value: 5 },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_COUNTER_COMPARE_D", value: 6 },
]
let EPWM_PeriodLoadMode = [
	{ name: "EPWM_PERIOD_SHADOW_LOAD", value: 0 },
	{ name: "EPWM_PERIOD_DIRECT_LOAD", value: 1 },
]
let EPWM_TimeBaseCountMode = [
	{ name: "EPWM_COUNTER_MODE_UP", value: 0 },
	{ name: "EPWM_COUNTER_MODE_DOWN", value: 1 },
	{ name: "EPWM_COUNTER_MODE_UP_DOWN", value: 2 },
	{ name: "EPWM_COUNTER_MODE_STOP_FREEZE", value: 3 },
]
let EPWM_PeriodShadowLoadMode = [
	{ name: "EPWM_SHADOW_LOAD_MODE_COUNTER_ZERO", value: 0 },
	{ name: "EPWM_SHADOW_LOAD_MODE_COUNTER_SYNC", value: 1 },
	{ name: "EPWM_SHADOW_LOAD_MODE_SYNC", value: 2 },
]
let EPWM_CurrentLink = [
	{ name: "EPWM_LINK_WITH_EPWM_1", value: 0 },
	{ name: "EPWM_LINK_WITH_EPWM_2", value: 1 },
	{ name: "EPWM_LINK_WITH_EPWM_3", value: 2 },
	{ name: "EPWM_LINK_WITH_EPWM_4", value: 3 },
	{ name: "EPWM_LINK_WITH_EPWM_5", value: 4 },
	{ name: "EPWM_LINK_WITH_EPWM_6", value: 5 },
	{ name: "EPWM_LINK_WITH_EPWM_7", value: 6 },
	{ name: "EPWM_LINK_WITH_EPWM_8", value: 7 },
]
let EPWM_LinkComponent = [
	{ name: "EPWM_LINK_TBPRD", value: 0 },
	{ name: "EPWM_LINK_COMP_A", value: 4 },
	{ name: "EPWM_LINK_COMP_B", value: 8 },
	{ name: "EPWM_LINK_COMP_C", value: 12 },
	{ name: "EPWM_LINK_COMP_D", value: 16 },
	{ name: "EPWM_LINK_GLDCTL2", value: 28 },
]
let EPWM_CounterCompareModule = [
	{ name: "EPWM_COUNTER_COMPARE_A", value: 0 },
	{ name: "EPWM_COUNTER_COMPARE_B", value: 2 },
	{ name: "EPWM_COUNTER_COMPARE_C", value: 5 },
	{ name: "EPWM_COUNTER_COMPARE_D", value: 7 },
]
let EPWM_CounterCompareLoadMode = [
	{ name: "EPWM_COMP_LOAD_ON_CNTR_ZERO", value: 0 },
	{ name: "EPWM_COMP_LOAD_ON_CNTR_PERIOD", value: 1 },
	{ name: "EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD", value: 2 },
	{ name: "EPWM_COMP_LOAD_FREEZE", value: 3 },
	{ name: "EPWM_COMP_LOAD_ON_SYNC_CNTR_ZERO", value: 4 },
	{ name: "EPWM_COMP_LOAD_ON_SYNC_CNTR_PERIOD", value: 5 },
	{ name: "EPWM_COMP_LOAD_ON_SYNC_CNTR_ZERO_PERIOD", value: 6 },
	{ name: "EPWM_COMP_LOAD_ON_SYNC_ONLY", value: 8 },
]
let EPWM_ActionQualifierModule = [
	{ name: "EPWM_ACTION_QUALIFIER_A", value: 0 },
	{ name: "EPWM_ACTION_QUALIFIER_B", value: 2 },
]
let EPWM_ActionQualifierLoadMode = [
	{ name: "EPWM_AQ_LOAD_ON_CNTR_ZERO", value: 0 },
	{ name: "EPWM_AQ_LOAD_ON_CNTR_PERIOD", value: 1 },
	{ name: "EPWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD", value: 2 },
	{ name: "EPWM_AQ_LOAD_FREEZE", value: 3 },
	{ name: "EPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO", value: 4 },
	{ name: "EPWM_AQ_LOAD_ON_SYNC_CNTR_PERIOD", value: 5 },
	{ name: "EPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO_PERIOD", value: 6 },
	{ name: "EPWM_AQ_LOAD_ON_SYNC_ONLY", value: 8 },
]
let EPWM_ActionQualifierTriggerSource = [
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_1", value: 0 },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_2", value: 1 },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_DCB_1", value: 2 },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_DCB_2", value: 3 },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_TZ_1", value: 4 },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_TZ_2", value: 5 },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_TZ_3", value: 6 },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_EPWM_SYNCIN", value: 7 },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_DC_EVTFILT", value: 8 },
]
let EPWM_ActionQualifierOutputEvent = [
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO", value: 0 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD", value: 2 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA", value: 4 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA", value: 6 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB", value: 8 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB", value: 10 },
	{ name: "EPWM_AQ_OUTPUT_ON_T1_COUNT_UP", value: 1 },
	{ name: "EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN", value: 3 },
	{ name: "EPWM_AQ_OUTPUT_ON_T2_COUNT_UP", value: 5 },
	{ name: "EPWM_AQ_OUTPUT_ON_T2_COUNT_DOWN", value: 7 },
]
let EPWM_ActionQualifierOutput = [
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE", value: 0 },
	{ name: "EPWM_AQ_OUTPUT_LOW", value: 1 },
	{ name: "EPWM_AQ_OUTPUT_HIGH", value: 2 },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE", value: 3 },
]
let EPWM_ActionQualifierSWOutput = [
	{ name: "EPWM_AQ_SW_DISABLED", value: 0 },
	{ name: "EPWM_AQ_SW_OUTPUT_LOW", value: 1 },
	{ name: "EPWM_AQ_SW_OUTPUT_HIGH", value: 2 },
]
let EPWM_ActionQualifierEventAction = [
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_ZERO", value: 0x0 },
	{ name: "EPWM_AQ_OUTPUT_LOW_ZERO", value: 0x1 },
	{ name: "EPWM_AQ_OUTPUT_HIGH_ZERO", value: 0x2 },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_ZERO", value: 0x3 },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_PERIOD", value: 0x0 },
	{ name: "EPWM_AQ_OUTPUT_LOW_PERIOD", value: 0x4 },
	{ name: "EPWM_AQ_OUTPUT_HIGH_PERIOD", value: 0x8 },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_PERIOD", value: 0xC },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA", value: 0x00 },
	{ name: "EPWM_AQ_OUTPUT_LOW_UP_CMPA", value: 0x10 },
	{ name: "EPWM_AQ_OUTPUT_HIGH_UP_CMPA", value: 0x20 },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_UP_CMPA", value: 0x30 },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA", value: 0x00 },
	{ name: "EPWM_AQ_OUTPUT_LOW_DOWN_CMPA", value: 0x40 },
	{ name: "EPWM_AQ_OUTPUT_HIGH_DOWN_CMPA", value: 0x80 },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPA", value: 0xC0 },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB", value: 0x000 },
	{ name: "EPWM_AQ_OUTPUT_LOW_UP_CMPB", value: 0x100 },
	{ name: "EPWM_AQ_OUTPUT_HIGH_UP_CMPB", value: 0x200 },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_UP_CMPB", value: 0x300 },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB", value: 0x000 },
	{ name: "EPWM_AQ_OUTPUT_LOW_DOWN_CMPB", value: 0x400 },
	{ name: "EPWM_AQ_OUTPUT_HIGH_DOWN_CMPB", value: 0x800 },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPB", value: 0xC00 },
]
let EPWM_AdditionalActionQualifierEventAction = [
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_UP_T1", value: 0x0 },
	{ name: "EPWM_AQ_OUTPUT_LOW_UP_T1", value: 0x1 },
	{ name: "EPWM_AQ_OUTPUT_HIGH_UP_T1", value: 0x2 },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_UP_T1", value: 0x3 },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_DOWN_T1", value: 0x0 },
	{ name: "EPWM_AQ_OUTPUT_LOW_DOWN_T1", value: 0x4 },
	{ name: "EPWM_AQ_OUTPUT_HIGH_DOWN_T1", value: 0x8 },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_DOWN_T1", value: 0xC },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_UP_T2", value: 0x00 },
	{ name: "EPWM_AQ_OUTPUT_LOW_UP_T2", value: 0x10 },
	{ name: "EPWM_AQ_OUTPUT_HIGH_UP_T2", value: 0x20 },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_UP_T2", value: 0x30 },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_DOWN_T2", value: 0x00 },
	{ name: "EPWM_AQ_OUTPUT_LOW_DOWN_T2", value: 0x40 },
	{ name: "EPWM_AQ_OUTPUT_HIGH_DOWN_T2", value: 0x80 },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_DOWN_T2", value: 0xC0 },
]
let EPWM_ActionQualifierOutputModule = [
	{ name: "EPWM_AQ_OUTPUT_A", value: 0 },
	{ name: "EPWM_AQ_OUTPUT_B", value: 2 },
]
let EPWM_ActionQualifierContForce = [
	{ name: "EPWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO", value: 0 },
	{ name: "EPWM_AQ_SW_SH_LOAD_ON_CNTR_PERIOD", value: 1 },
	{ name: "EPWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO_PERIOD", value: 2 },
	{ name: "EPWM_AQ_SW_IMMEDIATE_LOAD", value: 3 },
]
let EPWM_DeadBandOutput = [
	{ name: "EPWM_DB_OUTPUT_A", value: 1 },
	{ name: "EPWM_DB_OUTPUT_B", value: 0 },
]
let EPWM_DeadBandDelayMode = [
	{ name: "EPWM_DB_RED", value: 1 },
	{ name: "EPWM_DB_FED", value: 0 },
]
let EPWM_DeadBandPolarity = [
	{ name: "EPWM_DB_POLARITY_ACTIVE_HIGH", value: 0 },
	{ name: "EPWM_DB_POLARITY_ACTIVE_LOW", value: 1 },
]
let EPWM_DeadBandControlLoadMode = [
	{ name: "EPWM_DB_LOAD_ON_CNTR_ZERO", value: 0 },
	{ name: "EPWM_DB_LOAD_ON_CNTR_PERIOD", value: 1 },
	{ name: "EPWM_DB_LOAD_ON_CNTR_ZERO_PERIOD", value: 2 },
	{ name: "EPWM_DB_LOAD_FREEZE", value: 3 },
]
let EPWM_RisingEdgeDelayLoadMode = [
	{ name: "EPWM_RED_LOAD_ON_CNTR_ZERO", value: 0 },
	{ name: "EPWM_RED_LOAD_ON_CNTR_PERIOD", value: 1 },
	{ name: "EPWM_RED_LOAD_ON_CNTR_ZERO_PERIOD", value: 2 },
	{ name: "EPWM_RED_LOAD_FREEZE", value: 3 },
]
let EPWM_FallingEdgeDelayLoadMode = [
	{ name: "EPWM_FED_LOAD_ON_CNTR_ZERO", value: 0 },
	{ name: "EPWM_FED_LOAD_ON_CNTR_PERIOD", value: 1 },
	{ name: "EPWM_FED_LOAD_ON_CNTR_ZERO_PERIOD", value: 2 },
	{ name: "EPWM_FED_LOAD_FREEZE", value: 3 },
]
let EPWM_DeadBandClockMode = [
	{ name: "EPWM_DB_COUNTER_CLOCK_FULL_CYCLE", value: 0 },
	{ name: "EPWM_DB_COUNTER_CLOCK_HALF_CYCLE", value: 1 },
]
let EPWM_TripZoneDigitalCompareOutput = [
	{ name: "EPWM_TZ_DC_OUTPUT_A1", value: 0 },
	{ name: "EPWM_TZ_DC_OUTPUT_A2", value: 3 },
	{ name: "EPWM_TZ_DC_OUTPUT_B1", value: 6 },
	{ name: "EPWM_TZ_DC_OUTPUT_B2", value: 9 },
]
let EPWM_TripZoneDigitalCompareOutputEvent = [
	{ name: "EPWM_TZ_EVENT_DC_DISABLED", value: 0 },
	{ name: "EPWM_TZ_EVENT_DCXH_LOW", value: 1 },
	{ name: "EPWM_TZ_EVENT_DCXH_HIGH", value: 2 },
	{ name: "EPWM_TZ_EVENT_DCXL_LOW", value: 3 },
	{ name: "EPWM_TZ_EVENT_DCXL_HIGH", value: 4 },
	{ name: "EPWM_TZ_EVENT_DCXL_HIGH_DCXH_LOW", value: 5 },
]
let EPWM_TripZoneEvent = [
	{ name: "EPWM_TZ_ACTION_EVENT_TZA", value: 0 },
	{ name: "EPWM_TZ_ACTION_EVENT_TZB", value: 2 },
	{ name: "EPWM_TZ_ACTION_EVENT_DCAEVT1", value: 4 },
	{ name: "EPWM_TZ_ACTION_EVENT_DCAEVT2", value: 6 },
	{ name: "EPWM_TZ_ACTION_EVENT_DCBEVT1", value: 8 },
	{ name: "EPWM_TZ_ACTION_EVENT_DCBEVT2", value: 10 },
]
let EPWM_TripZoneAction = [
	{ name: "EPWM_TZ_ACTION_HIGH_Z", value: 0 },
	{ name: "EPWM_TZ_ACTION_HIGH", value: 1 },
	{ name: "EPWM_TZ_ACTION_LOW", value: 2 },
	{ name: "EPWM_TZ_ACTION_DISABLE", value: 3 },
]
let EPWM_TripZoneAdvancedEvent = [
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_TZB_D", value: 9 },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_TZB_U", value: 6 },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_TZA_D", value: 3 },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_TZA_U", value: 0 },
]
let EPWM_TripZoneAdvancedAction = [
	{ name: "EPWM_TZ_ADV_ACTION_HIGH_Z", value: 0 },
	{ name: "EPWM_TZ_ADV_ACTION_HIGH", value: 1 },
	{ name: "EPWM_TZ_ADV_ACTION_LOW", value: 2 },
	{ name: "EPWM_TZ_ADV_ACTION_TOGGLE", value: 3 },
	{ name: "EPWM_TZ_ADV_ACTION_DISABLE", value: 7 },
]
let EPWM_TripZoneAdvDigitalCompareEvent = [
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U", value: 0 },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D", value: 3 },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U", value: 6 },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D", value: 9 },
]
let EPWM_CycleByCycleTripZoneClearMode = [
	{ name: "EPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO", value: 0 },
	{ name: "EPWM_TZ_CBC_PULSE_CLR_CNTR_PERIOD", value: 1 },
	{ name: "EPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD", value: 2 },
]
let EPWM_ADCStartOfConversionType = [
	{ name: "EPWM_SOC_A", value: 0 },
	{ name: "EPWM_SOC_B", value: 1 },
]
let EPWM_ADCStartOfConversionSource = [
	{ name: "EPWM_SOC_DCxEVT1", value: 0 },
	{ name: "EPWM_SOC_TBCTR_ZERO", value: 1 },
	{ name: "EPWM_SOC_TBCTR_PERIOD", value: 2 },
	{ name: "EPWM_SOC_TBCTR_ZERO_OR_PERIOD", value: 3 },
	{ name: "EPWM_SOC_TBCTR_U_CMPA", value: 4 },
	{ name: "EPWM_SOC_TBCTR_U_CMPC", value: 8 },
	{ name: "EPWM_SOC_TBCTR_D_CMPA", value: 5 },
	{ name: "EPWM_SOC_TBCTR_D_CMPC", value: 10 },
	{ name: "EPWM_SOC_TBCTR_U_CMPB", value: 6 },
	{ name: "EPWM_SOC_TBCTR_U_CMPD", value: 12 },
	{ name: "EPWM_SOC_TBCTR_D_CMPB", value: 7 },
	{ name: "EPWM_SOC_TBCTR_D_CMPD", value: 14 },
]
let EPWM_DigitalCompareType = [
	{ name: "EPWM_DC_TYPE_DCAH", value: 0 },
	{ name: "EPWM_DC_TYPE_DCAL", value: 1 },
	{ name: "EPWM_DC_TYPE_DCBH", value: 2 },
	{ name: "EPWM_DC_TYPE_DCBL", value: 3 },
]
let EPWM_DigitalCompareTripInput = [
	{ name: "EPWM_DC_TRIP_TRIPIN1", value: 0 },
	{ name: "EPWM_DC_TRIP_TRIPIN2", value: 1 },
	{ name: "EPWM_DC_TRIP_TRIPIN3", value: 2 },
	{ name: "EPWM_DC_TRIP_TRIPIN4", value: 3 },
	{ name: "EPWM_DC_TRIP_TRIPIN5", value: 4 },
	{ name: "EPWM_DC_TRIP_TRIPIN6", value: 5 },
	{ name: "EPWM_DC_TRIP_TRIPIN7", value: 6 },
	{ name: "EPWM_DC_TRIP_TRIPIN8", value: 7 },
	{ name: "EPWM_DC_TRIP_TRIPIN9", value: 8 },
	{ name: "EPWM_DC_TRIP_TRIPIN10", value: 9 },
	{ name: "EPWM_DC_TRIP_TRIPIN11", value: 10 },
	{ name: "EPWM_DC_TRIP_TRIPIN12", value: 11 },
	{ name: "EPWM_DC_TRIP_TRIPIN14", value: 13 },
	{ name: "EPWM_DC_TRIP_TRIPIN15", value: 14 },
	{ name: "EPWM_DC_TRIP_COMBINATION", value: 15 },
]
let EPWM_DigitalCompareBlankingPulse = [
	{ name: "EPWM_DC_WINDOW_START_TBCTR_PERIOD", value: 0 },
	{ name: "EPWM_DC_WINDOW_START_TBCTR_ZERO", value: 1 },
	{ name: "EPWM_DC_WINDOW_START_TBCTR_ZERO_PERIOD", value: 2 },
]
let EPWM_DigitalCompareFilterInput = [
	{ name: "EPWM_DC_WINDOW_SOURCE_DCAEVT1", value: 0 },
	{ name: "EPWM_DC_WINDOW_SOURCE_DCAEVT2", value: 1 },
	{ name: "EPWM_DC_WINDOW_SOURCE_DCBEVT1", value: 2 },
	{ name: "EPWM_DC_WINDOW_SOURCE_DCBEVT2", value: 3 },
]
let EPWM_DigitalCompareModule = [
	{ name: "EPWM_DC_MODULE_A", value: 0 },
	{ name: "EPWM_DC_MODULE_B", value: 1 },
]
let EPWM_DigitalCompareEvent = [
	{ name: "EPWM_DC_EVENT_1", value: 0 },
	{ name: "EPWM_DC_EVENT_2", value: 1 },
]
let EPWM_DigitalCompareEventSource = [
	{ name: "EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL", value: 0 },
	{ name: "EPWM_DC_EVENT_SOURCE_FILT_SIGNAL", value: 1 },
]
let EPWM_DigitalCompareSyncMode = [
	{ name: "EPWM_DC_EVENT_INPUT_SYNCED", value: 0 },
	{ name: "EPWM_DC_EVENT_INPUT_NOT_SYNCED", value: 1 },
]
let EPWM_GlobalLoadTrigger = [
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_ZERO", value: 0x0 },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_PERIOD", value: 0x1 },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD", value: 0x2 },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC", value: 0x3 },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_ZERO", value: 0x4 },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_PERIOD", value: 0x5 },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD", value: 0x6 },
	{ name: "EPWM_GL_LOAD_PULSE_GLOBAL_FORCE", value: 0xF },
]
let EPWM_ValleyTriggerSource = [
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_SOFTWARE", value: 0 },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_CNTR_ZERO", value: 1 },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_CNTR_PERIOD", value: 2 },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_CNTR_ZERO_PERIOD", value: 3 },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_DCAEVT1", value: 4 },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_DCAEVT2", value: 5 },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_DCBEVT1", value: 6 },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_DCBEVT2", value: 7 },
]
let EPWM_ValleyCounterEdge = [
	{ name: "EPWM_VALLEY_COUNT_START_EDGE", value: 0 },
	{ name: "EPWM_VALLEY_COUNT_STOP_EDGE", value: 1 },
]
let EPWM_ValleyDelayMode = [
	{ name: "EPWM_VALLEY_DELAY_MODE_SW_DELAY", value: 0 },
	{ name: "EPWM_VALLEY_DELAY_MODE_VCNT_DELAY_SW_DELAY", value: 1 },
	{ name: "EPWM_VALLEY_DELAY_MODE_VCNT_DELAY_SHIFT_1_SW_DELAY", value: 2 },
	{ name: "EPWM_VALLEY_DELAY_MODE_VCNT_DELAY_SHIFT_2_SW_DELAY", value: 3 },
	{ name: "EPWM_VALLEY_DELAY_MODE_VCNT_DELAY_SHIFT_4_SW_DELAY", value: 4 },
]
let EPWM_DigitalCompareEdgeFilterMode = [
	{ name: "EPWM_DC_EDGEFILT_MODE_RISING", value: 0 },
	{ name: "EPWM_DC_EDGEFILT_MODE_FALLING", value: 1 },
	{ name: "EPWM_DC_EDGEFILT_MODE_BOTH", value: 2 },
]
let EPWM_DigitalCompareEdgeFilterEdgeCount = [
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_0", value: 0 },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_1", value: 1 },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_2", value: 2 },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_3", value: 3 },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_4", value: 4 },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_5", value: 5 },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_6", value: 6 },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_7", value: 7 },
]
let EPWM_LockRegisterGroup = [
	{ name: "EPWM_REGISTER_GROUP_GLOBAL_LOAD", value: 0x2 },
	{ name: "EPWM_REGISTER_GROUP_TRIP_ZONE", value: 0x4 },
	{ name: "EPWM_REGISTER_GROUP_TRIP_ZONE_CLEAR", value: 0x8 },
	{ name: "EPWM_REGISTER_GROUP_DIGITAL_COMPARE", value: 0x10 },
]
let EPWM_TIME_BASE_STATUS_COUNT = [
	{ name: "EPWM_TIME_BASE_STATUS_COUNT_UP", value: 1 },
	{ name: "EPWM_TIME_BASE_STATUS_COUNT_DOWN", value: 0 },
]
let EPWM_DB_INPUT = [
	{ name: "EPWM_DB_INPUT_EPWMA", value: 0 },
	{ name: "EPWM_DB_INPUT_EPWMB", value: 1 },
	{ name: "EPWM_DB_INPUT_DB_RED", value: 2 },
]
let EPWM_TZ_SIGNAL = [
	{ name: "EPWM_TZ_SIGNAL_CBC1", value: 0x1 },
	{ name: "EPWM_TZ_SIGNAL_CBC2", value: 0x2 },
	{ name: "EPWM_TZ_SIGNAL_CBC3", value: 0x4 },
	{ name: "EPWM_TZ_SIGNAL_CBC4", value: 0x8 },
	{ name: "EPWM_TZ_SIGNAL_CBC5", value: 0x10 },
	{ name: "EPWM_TZ_SIGNAL_CBC6", value: 0x20 },
	{ name: "EPWM_TZ_SIGNAL_DCAEVT2", value: 0x40 },
	{ name: "EPWM_TZ_SIGNAL_DCBEVT2", value: 0x80 },
	{ name: "EPWM_TZ_SIGNAL_OSHT1", value: 0x100 },
	{ name: "EPWM_TZ_SIGNAL_OSHT2", value: 0x200 },
	{ name: "EPWM_TZ_SIGNAL_OSHT3", value: 0x400 },
	{ name: "EPWM_TZ_SIGNAL_OSHT4", value: 0x800 },
	{ name: "EPWM_TZ_SIGNAL_OSHT5", value: 0x1000 },
	{ name: "EPWM_TZ_SIGNAL_OSHT6", value: 0x2000 },
	{ name: "EPWM_TZ_SIGNAL_DCAEVT1", value: 0x4000 },
	{ name: "EPWM_TZ_SIGNAL_DCBEVT1", value: 0x8000 },
]
let EPWM_TZ_INTERRUPT = [
	{ name: "EPWM_TZ_INTERRUPT_CBC", value: 0x2 },
	{ name: "EPWM_TZ_INTERRUPT_OST", value: 0x4 },
	{ name: "EPWM_TZ_INTERRUPT_DCAEVT1", value: 0x8 },
	{ name: "EPWM_TZ_INTERRUPT_DCAEVT2", value: 0x10 },
	{ name: "EPWM_TZ_INTERRUPT_DCBEVT1", value: 0x20 },
	{ name: "EPWM_TZ_INTERRUPT_DCBEVT2", value: 0x40 },
]
let EPWM_TZ_FLAG = [
	{ name: "EPWM_TZ_FLAG_CBC", value: 0x2 },
	{ name: "EPWM_TZ_FLAG_OST", value: 0x4 },
	{ name: "EPWM_TZ_FLAG_DCAEVT1", value: 0x8 },
	{ name: "EPWM_TZ_FLAG_DCAEVT2", value: 0x10 },
	{ name: "EPWM_TZ_FLAG_DCBEVT1", value: 0x20 },
	{ name: "EPWM_TZ_FLAG_DCBEVT2", value: 0x40 },
]
let EPWM_TZ_CBC_FLAG = [
	{ name: "EPWM_TZ_CBC_FLAG_1", value: 0x1 },
	{ name: "EPWM_TZ_CBC_FLAG_2", value: 0x2 },
	{ name: "EPWM_TZ_CBC_FLAG_3", value: 0x4 },
	{ name: "EPWM_TZ_CBC_FLAG_4", value: 0x8 },
	{ name: "EPWM_TZ_CBC_FLAG_5", value: 0x10 },
	{ name: "EPWM_TZ_CBC_FLAG_6", value: 0x20 },
	{ name: "EPWM_TZ_CBC_FLAG_DCAEVT2", value: 0x40 },
	{ name: "EPWM_TZ_CBC_FLAG_DCBEVT2", value: 0x80 },
]
let EPWM_TZ_OST_FLAG = [
	{ name: "EPWM_TZ_OST_FLAG_OST1", value: 0x1 },
	{ name: "EPWM_TZ_OST_FLAG_OST2", value: 0x2 },
	{ name: "EPWM_TZ_OST_FLAG_OST3", value: 0x4 },
	{ name: "EPWM_TZ_OST_FLAG_OST4", value: 0x8 },
	{ name: "EPWM_TZ_OST_FLAG_OST5", value: 0x10 },
	{ name: "EPWM_TZ_OST_FLAG_OST6", value: 0x20 },
	{ name: "EPWM_TZ_OST_FLAG_DCAEVT1", value: 0x40 },
	{ name: "EPWM_TZ_OST_FLAG_DCBEVT1", value: 0x80 },
]
let EPWM_TZ_FORCE_EVENT = [
	{ name: "EPWM_TZ_FORCE_EVENT_CBC", value: 0x2 },
	{ name: "EPWM_TZ_FORCE_EVENT_OST", value: 0x4 },
	{ name: "EPWM_TZ_FORCE_EVENT_DCAEVT1", value: 0x8 },
	{ name: "EPWM_TZ_FORCE_EVENT_DCAEVT2", value: 0x10 },
	{ name: "EPWM_TZ_FORCE_EVENT_DCBEVT1", value: 0x20 },
	{ name: "EPWM_TZ_FORCE_EVENT_DCBEVT2", value: 0x40 },
]
let EPWM_INT_TBCTR = [
	{ name: "EPWM_INT_TBCTR_DISABLED", value: 0 },
	{ name: "EPWM_INT_TBCTR_ZERO", value: 1 },
	{ name: "EPWM_INT_TBCTR_PERIOD", value: 2 },
	{ name: "EPWM_INT_TBCTR_ZERO_OR_PERIOD", value: 3 },
	{ name: "EPWM_INT_TBCTR_U_CMPA", value: 4 },
	{ name: "EPWM_INT_TBCTR_U_CMPC", value: 8 },
	{ name: "EPWM_INT_TBCTR_D_CMPA", value: 5 },
	{ name: "EPWM_INT_TBCTR_D_CMPC", value: 10 },
	{ name: "EPWM_INT_TBCTR_U_CMPB", value: 6 },
	{ name: "EPWM_INT_TBCTR_U_CMPD", value: 12 },
	{ name: "EPWM_INT_TBCTR_D_CMPB", value: 7 },
	{ name: "EPWM_INT_TBCTR_D_CMPD", value: 14 },
]
let EPWM_DC_COMBINATIONAL = [
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN1", value: 0x1 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN2", value: 0x2 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN3", value: 0x4 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN4", value: 0x8 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN5", value: 0x10 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN6", value: 0x20 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN7", value: 0x40 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN8", value: 0x80 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN9", value: 0x100 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN10", value: 0x200 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN11", value: 0x400 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN12", value: 0x800 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN14", value: 0x2000 },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN15", value: 0x4000 },
]
let EPWM_GL_REGISTER = [
	{ name: "EPWM_GL_REGISTER_TBPRD_TBPRDHR", value: 0x1 },
	{ name: "EPWM_GL_REGISTER_CMPA_CMPAHR", value: 0x2 },
	{ name: "EPWM_GL_REGISTER_CMPB_CMPBHR", value: 0x4 },
	{ name: "EPWM_GL_REGISTER_CMPC", value: 0x8 },
	{ name: "EPWM_GL_REGISTER_CMPD", value: 0x10 },
	{ name: "EPWM_GL_REGISTER_DBRED_DBREDHR", value: 0x20 },
	{ name: "EPWM_GL_REGISTER_DBFED_DBFEDHR", value: 0x40 },
	{ name: "EPWM_GL_REGISTER_DBCTL", value: 0x80 },
	{ name: "EPWM_GL_REGISTER_AQCTLA_AQCTLA2", value: 0x100 },
	{ name: "EPWM_GL_REGISTER_AQCTLB_AQCTLB2", value: 0x200 },
	{ name: "EPWM_GL_REGISTER_AQCSFRC", value: 0x400 },
]
let EPWM_setSyncPulseSource = [
	{ name: "EPWM_setSyncPulseSource", value: "HRPWM_setSyncPulseSource" },
]
module.exports = {
	EPWM_EmulationMode: EPWM_EmulationMode,
	EPWM_SyncCountMode: EPWM_SyncCountMode,
	EPWM_ClockDivider: EPWM_ClockDivider,
	EPWM_HSClockDivider: EPWM_HSClockDivider,
	EPWM_SyncOutPulseMode: EPWM_SyncOutPulseMode,
	EPWM_PeriodLoadMode: EPWM_PeriodLoadMode,
	EPWM_TimeBaseCountMode: EPWM_TimeBaseCountMode,
	EPWM_PeriodShadowLoadMode: EPWM_PeriodShadowLoadMode,
	EPWM_CurrentLink: EPWM_CurrentLink,
	EPWM_LinkComponent: EPWM_LinkComponent,
	EPWM_CounterCompareModule: EPWM_CounterCompareModule,
	EPWM_CounterCompareLoadMode: EPWM_CounterCompareLoadMode,
	EPWM_ActionQualifierModule: EPWM_ActionQualifierModule,
	EPWM_ActionQualifierLoadMode: EPWM_ActionQualifierLoadMode,
	EPWM_ActionQualifierTriggerSource: EPWM_ActionQualifierTriggerSource,
	EPWM_ActionQualifierOutputEvent: EPWM_ActionQualifierOutputEvent,
	EPWM_ActionQualifierOutput: EPWM_ActionQualifierOutput,
	EPWM_ActionQualifierSWOutput: EPWM_ActionQualifierSWOutput,
	EPWM_ActionQualifierEventAction: EPWM_ActionQualifierEventAction,
	EPWM_AdditionalActionQualifierEventAction: EPWM_AdditionalActionQualifierEventAction,
	EPWM_ActionQualifierOutputModule: EPWM_ActionQualifierOutputModule,
	EPWM_ActionQualifierContForce: EPWM_ActionQualifierContForce,
	EPWM_DeadBandOutput: EPWM_DeadBandOutput,
	EPWM_DeadBandDelayMode: EPWM_DeadBandDelayMode,
	EPWM_DeadBandPolarity: EPWM_DeadBandPolarity,
	EPWM_DeadBandControlLoadMode: EPWM_DeadBandControlLoadMode,
	EPWM_RisingEdgeDelayLoadMode: EPWM_RisingEdgeDelayLoadMode,
	EPWM_FallingEdgeDelayLoadMode: EPWM_FallingEdgeDelayLoadMode,
	EPWM_DeadBandClockMode: EPWM_DeadBandClockMode,
	EPWM_TripZoneDigitalCompareOutput: EPWM_TripZoneDigitalCompareOutput,
	EPWM_TripZoneDigitalCompareOutputEvent: EPWM_TripZoneDigitalCompareOutputEvent,
	EPWM_TripZoneEvent: EPWM_TripZoneEvent,
	EPWM_TripZoneAction: EPWM_TripZoneAction,
	EPWM_TripZoneAdvancedEvent: EPWM_TripZoneAdvancedEvent,
	EPWM_TripZoneAdvancedAction: EPWM_TripZoneAdvancedAction,
	EPWM_TripZoneAdvDigitalCompareEvent: EPWM_TripZoneAdvDigitalCompareEvent,
	EPWM_CycleByCycleTripZoneClearMode: EPWM_CycleByCycleTripZoneClearMode,
	EPWM_ADCStartOfConversionType: EPWM_ADCStartOfConversionType,
	EPWM_ADCStartOfConversionSource: EPWM_ADCStartOfConversionSource,
	EPWM_DigitalCompareType: EPWM_DigitalCompareType,
	EPWM_DigitalCompareTripInput: EPWM_DigitalCompareTripInput,
	EPWM_DigitalCompareBlankingPulse: EPWM_DigitalCompareBlankingPulse,
	EPWM_DigitalCompareFilterInput: EPWM_DigitalCompareFilterInput,
	EPWM_DigitalCompareModule: EPWM_DigitalCompareModule,
	EPWM_DigitalCompareEvent: EPWM_DigitalCompareEvent,
	EPWM_DigitalCompareEventSource: EPWM_DigitalCompareEventSource,
	EPWM_DigitalCompareSyncMode: EPWM_DigitalCompareSyncMode,
	EPWM_GlobalLoadTrigger: EPWM_GlobalLoadTrigger,
	EPWM_ValleyTriggerSource: EPWM_ValleyTriggerSource,
	EPWM_ValleyCounterEdge: EPWM_ValleyCounterEdge,
	EPWM_ValleyDelayMode: EPWM_ValleyDelayMode,
	EPWM_DigitalCompareEdgeFilterMode: EPWM_DigitalCompareEdgeFilterMode,
	EPWM_DigitalCompareEdgeFilterEdgeCount: EPWM_DigitalCompareEdgeFilterEdgeCount,
	EPWM_LockRegisterGroup: EPWM_LockRegisterGroup,
	EPWM_TIME_BASE_STATUS_COUNT: EPWM_TIME_BASE_STATUS_COUNT,
	EPWM_DB_INPUT: EPWM_DB_INPUT,
	EPWM_TZ_SIGNAL: EPWM_TZ_SIGNAL,
	EPWM_TZ_INTERRUPT: EPWM_TZ_INTERRUPT,
	EPWM_TZ_FLAG: EPWM_TZ_FLAG,
	EPWM_TZ_CBC_FLAG: EPWM_TZ_CBC_FLAG,
	EPWM_TZ_OST_FLAG: EPWM_TZ_OST_FLAG,
	EPWM_TZ_FORCE_EVENT: EPWM_TZ_FORCE_EVENT,
	EPWM_INT_TBCTR: EPWM_INT_TBCTR,
	EPWM_DC_COMBINATIONAL: EPWM_DC_COMBINATIONAL,
	EPWM_GL_REGISTER: EPWM_GL_REGISTER,
	EPWM_setSyncPulseSource: EPWM_setSyncPulseSource,
}
