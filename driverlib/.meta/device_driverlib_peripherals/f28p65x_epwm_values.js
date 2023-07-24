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
let EPWM_SyncInPulseSource = [
	{ name: "EPWM_SYNC_IN_PULSE_SRC_DISABLE", value: 0x0 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM1", value: 0x1 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM2", value: 0x2 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM3", value: 0x3 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM4", value: 0x4 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM5", value: 0x5 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM6", value: 0x6 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM7", value: 0x7 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM8", value: 0x8 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM9", value: 0x9 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM10", value: 0xA },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM11", value: 0xB },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM12", value: 0xC },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM13", value: 0xD },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM14", value: 0xE },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM15", value: 0xF },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM16", value: 0x10 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP1", value: 0x11 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP2", value: 0x12 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP3", value: 0x13 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP4", value: 0x14 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP5", value: 0x15 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP6", value: 0x16 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP7", value: 0x17 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT5", value: 0x18 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT6", value: 0x19 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_ETHERCAT_SYNC0", value: 0x1A },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_ETHERCAT_SYNC1", value: 0x1B },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM17", value: 0x1C },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM18", value: 0x1D },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_FSIRXA_TRIG1", value: 0x1E },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_FSIRXB_TRIG1", value: 0x1F },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_FSIRXC_TRIG1", value: 0x20 },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_FSIRXD_TRIG1", value: 0x21 },
]
let EPWM_OneShotSyncOutTrigger = [
	{ name: "EPWM_OSHT_SYNC_OUT_TRIG_SYNC", value: 0x0 },
	{ name: "EPWM_OSHT_SYNC_OUT_TRIG_RELOAD", value: 0x1 },
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
	{ name: "EPWM_LINK_WITH_EPWM_17", value: 16 },
	{ name: "EPWM_LINK_WITH_EPWM_18", value: 17 },
	{ name: "EPWM_LINK_WITH_EPWM_1", value: 0 },
	{ name: "EPWM_LINK_WITH_EPWM_2", value: 1 },
	{ name: "EPWM_LINK_WITH_EPWM_3", value: 2 },
	{ name: "EPWM_LINK_WITH_EPWM_4", value: 3 },
	{ name: "EPWM_LINK_WITH_EPWM_5", value: 4 },
	{ name: "EPWM_LINK_WITH_EPWM_6", value: 5 },
	{ name: "EPWM_LINK_WITH_EPWM_7", value: 6 },
	{ name: "EPWM_LINK_WITH_EPWM_8", value: 7 },
	{ name: "EPWM_LINK_WITH_EPWM_9", value: 8 },
	{ name: "EPWM_LINK_WITH_EPWM_10", value: 9 },
	{ name: "EPWM_LINK_WITH_EPWM_11", value: 10 },
	{ name: "EPWM_LINK_WITH_EPWM_12", value: 11 },
	{ name: "EPWM_LINK_WITH_EPWM_13", value: 12 },
	{ name: "EPWM_LINK_WITH_EPWM_14", value: 13 },
	{ name: "EPWM_LINK_WITH_EPWM_15", value: 14 },
	{ name: "EPWM_LINK_WITH_EPWM_16", value: 15 },
]
let EPWM_LinkComponent = [
	{ name: "EPWM_LINK_TBPRD", value: 0 },
	{ name: "EPWM_LINK_COMP_A", value: 5 },
	{ name: "EPWM_LINK_COMP_B", value: 10 },
	{ name: "EPWM_LINK_COMP_C", value: 16 },
	{ name: "EPWM_LINK_COMP_D", value: 21 },
	{ name: "EPWM_LINK_GLDCTL2", value: 26 },
	{ name: "EPWM_LINK_DBRED", value: 0+32 },
	{ name: "EPWM_LINK_DBFED", value: 5+32 },
	{ name: "EPWM_LINK_XLOAD", value: 0+64 },
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
let EPWM_XCMPReg = [
	{ name: "EPWM_XCMP1_ACTIVE", value: 0x0 },
	{ name: "EPWM_XCMP2_ACTIVE", value: 0x2 },
	{ name: "EPWM_XCMP3_ACTIVE", value: 0x4 },
	{ name: "EPWM_XCMP4_ACTIVE", value: 0x6 },
	{ name: "EPWM_XCMP5_ACTIVE", value: 0x8 },
	{ name: "EPWM_XCMP6_ACTIVE", value: 0xA },
	{ name: "EPWM_XCMP7_ACTIVE", value: 0xC },
	{ name: "EPWM_XCMP8_ACTIVE", value: 0xE },
	{ name: "EPWM_XTBPRD_ACTIVE", value: 0x10 },
	{ name: "EPWM_XCMP1_SHADOW1", value: 0x20 },
	{ name: "EPWM_XCMP2_SHADOW1", value: 0x22 },
	{ name: "EPWM_XCMP3_SHADOW1", value: 0x24 },
	{ name: "EPWM_XCMP4_SHADOW1", value: 0x26 },
	{ name: "EPWM_XCMP5_SHADOW1", value: 0x28 },
	{ name: "EPWM_XCMP6_SHADOW1", value: 0x2A },
	{ name: "EPWM_XCMP7_SHADOW1", value: 0x2C },
	{ name: "EPWM_XCMP8_SHADOW1", value: 0x2E },
	{ name: "EPWM_XTBPRD_SHADOW1", value: 0x30 },
	{ name: "EPWM_XCMP1_SHADOW2", value: 0x40 },
	{ name: "EPWM_XCMP2_SHADOW2", value: 0x42 },
	{ name: "EPWM_XCMP3_SHADOW2", value: 0x44 },
	{ name: "EPWM_XCMP4_SHADOW2", value: 0x46 },
	{ name: "EPWM_XCMP5_SHADOW2", value: 0x48 },
	{ name: "EPWM_XCMP6_SHADOW2", value: 0x4A },
	{ name: "EPWM_XCMP7_SHADOW2", value: 0x4C },
	{ name: "EPWM_XCMP8_SHADOW2", value: 0x4E },
	{ name: "EPWM_XTBPRD_SHADOW2", value: 0x50 },
	{ name: "EPWM_XCMP1_SHADOW3", value: 0x60 },
	{ name: "EPWM_XCMP2_SHADOW3", value: 0x62 },
	{ name: "EPWM_XCMP3_SHADOW3", value: 0x64 },
	{ name: "EPWM_XCMP4_SHADOW3", value: 0x66 },
	{ name: "EPWM_XCMP5_SHADOW3", value: 0x68 },
	{ name: "EPWM_XCMP6_SHADOW3", value: 0x6A },
	{ name: "EPWM_XCMP7_SHADOW3", value: 0x6C },
	{ name: "EPWM_XCMP8_SHADOW3", value: 0x6E },
	{ name: "EPWM_XTBPRD_SHADOW3", value: 0x70 },
]
let EPWM_XCompareReg = [
	{ name: "EPWM_CMPC_SHADOW1", value: 0x0 },
	{ name: "EPWM_CMPD_SHADOW1", value: 0x2 },
	{ name: "EPWM_CMPC_SHADOW2", value: 0x20 },
	{ name: "EPWM_CMPD_SHADOW2", value: 0x22 },
	{ name: "EPWM_CMPC_SHADOW3", value: 0x40 },
	{ name: "EPWM_CMPD_SHADOW3", value: 0x42 },
]
let EPWM_XMinMaxReg = [
	{ name: "EPWM_XMAX_ACTIVE", value: 0x0 },
	{ name: "EPWM_XMIN_ACTIVE", value: 0x1 },
	{ name: "EPWM_XMAX_SHADOW1", value: 0x20 },
	{ name: "EPWM_XMIN_SHADOW1", value: 0x21 },
	{ name: "EPWM_XMAX_SHADOW2", value: 0x40 },
	{ name: "EPWM_XMIN_SHADOW2", value: 0x41 },
	{ name: "EPWM_XMAX_SHADOW3", value: 0x60 },
	{ name: "EPWM_XMIN_SHADOW3", value: 0x61 },
]
let EPWM_XCMPActionQualifierOutputEvent = [
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP1", value: 0 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP2", value: 2 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP3", value: 4 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP4", value: 6 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP5", value: 8 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP6", value: 10 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP7", value: 12 },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP8", value: 14 },
]
let EPWM_XCMP_ALLOC_CMPA = [
	{ name: "EPWM_XCMP_NONE_CMPA", value: 0 },
	{ name: "EPWM_XCMP_1_CMPA", value: 1 },
	{ name: "EPWM_XCMP_2_CMPA", value: 2 },
	{ name: "EPWM_XCMP_3_CMPA", value: 3 },
	{ name: "EPWM_XCMP_4_CMPA", value: 4 },
	{ name: "EPWM_XCMP_5_CMPA", value: 5 },
	{ name: "EPWM_XCMP_6_CMPA", value: 6 },
	{ name: "EPWM_XCMP_7_CMPA", value: 7 },
	{ name: "EPWM_XCMP_8_CMPA", value: 8 },
]
let EPWM_XCMP_ALLOC_CMPB = [
	{ name: "EPWM_XCMP_5_CMPB", value: 5 },
	{ name: "EPWM_XCMP_6_CMPB", value: 6 },
	{ name: "EPWM_XCMP_7_CMPB", value: 7 },
	{ name: "EPWM_XCMP_8_CMPB", value: 8 },
]
let EPWM_XCMPXloadCtlLoadMode = [
	{ name: "EPWM_XCMP_XLOADCTL_LOADMODE_LOADONCE", value: 0 },
	{ name: "EPWM_XCMP_XLOADCTL_LOADMODE_LOADMULTIPLE", value: 1 },
]
let EPWM_XCMP_XLOADCTL_SHDWLEVEL = [
	{ name: "EPWM_XCMP_XLOADCTL_SHDWLEVEL_0", value: 0 },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWLEVEL_1", value: 1 },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWLEVEL_2", value: 2 },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWLEVEL_3", value: 3 },
]
let EPWM_XCMP_XLOADCTL_SHDWBUFPTR = [
	{ name: "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_NULL", value: 0 },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_ONE", value: 1 },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_TWO", value: 2 },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_THREE", value: 3 },
]
let EPWM_DiodeEmulationMode = [
	{ name: "EPWM_DIODE_EMULATION_CBC", value: 0 },
	{ name: "EPWM_DIODE_EMULATION_OST", value: 1 },
]
let EPWM_DiodeEmulationTripLSource = [
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL1", value: 0x00 },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL2", value: 0x01 },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL3", value: 0x02 },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL4", value: 0x03 },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL5", value: 0x04 },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL6", value: 0x05 },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL7", value: 0x06 },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL8", value: 0x07 },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL9", value: 0x08 },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL10", value: 0x09 },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL11", value: 0x0A },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT1", value: 0x10 },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT2", value: 0x11 },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT3", value: 0x12 },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT4", value: 0x13 },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT5", value: 0x14 },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT6", value: 0x15 },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT7", value: 0x16 },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT8", value: 0x17 },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT9", value: 0x18 },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT10", value: 0x19 },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT11", value: 0x1A },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT12", value: 0x1B },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT13", value: 0x1C },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT14", value: 0x1D },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT15", value: 0x1E },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT16", value: 0x1F },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT1", value: 0x20 },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT2", value: 0x21 },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT3", value: 0x22 },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT4", value: 0x23 },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT5", value: 0x24 },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT6", value: 0x25 },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT7", value: 0x26 },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT8", value: 0x27 },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT9", value: 0x28 },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT10", value: 0x29 },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT11", value: 0x2A },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT12", value: 0x2B },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT13", value: 0x2C },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT14", value: 0x2D },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT15", value: 0x2E },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT16", value: 0x2F },
]
let EPWM_DiodeEmulationTripHSource = [
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH1", value: 0x00 },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH2", value: 0x01 },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH3", value: 0x02 },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH4", value: 0x03 },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH5", value: 0x04 },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH6", value: 0x05 },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH7", value: 0x06 },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH8", value: 0x07 },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH9", value: 0x08 },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH10", value: 0x09 },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH11", value: 0x0A },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT1", value: 0x10 },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT2", value: 0x11 },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT3", value: 0x12 },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT4", value: 0x13 },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT5", value: 0x14 },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT6", value: 0x15 },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT7", value: 0x16 },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT8", value: 0x17 },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT9", value: 0x18 },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT10", value: 0x19 },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT11", value: 0x1A },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT12", value: 0x1B },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT13", value: 0x1C },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT14", value: 0x1D },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT15", value: 0x1E },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT16", value: 0x1F },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT1", value: 0x20 },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT2", value: 0x21 },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT3", value: 0x22 },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT4", value: 0x23 },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT5", value: 0x24 },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT6", value: 0x25 },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT7", value: 0x26 },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT8", value: 0x27 },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT9", value: 0x28 },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT10", value: 0x29 },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT11", value: 0x2A },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT12", value: 0x2B },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT13", value: 0x2C },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT14", value: 0x2D },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT15", value: 0x2E },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT16", value: 0x2F },
]
let EPWM_DiodeEmulationSignal = [
	{ name: "EPWM_DE_SYNC_TRIPHorL", value: 0 },
	{ name: "EPWM_DE_SYNC_INV_TRIPHorL", value: 1 },
	{ name: "EPWM_DE_LOW", value: 2 },
	{ name: "EPWM_DE_HIGH", value: 3 },
]
let EPWM_CycleByCycleTripZoneClearMode = [
	{ name: "EPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO", value: 0 },
	{ name: "EPWM_TZ_CBC_PULSE_CLR_CNTR_PERIOD", value: 1 },
	{ name: "EPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD", value: 2 },
]
let EPWM_selectTripOutSource = [
	{ name: "EPWM_TZ_TRIPOUT_OST", value: 0 },
	{ name: "EPWM_TZ_TRIPOUT_CBC", value: 1 },
	{ name: "EPWM_TZ_TRIPOUT_TZ1", value: 2 },
	{ name: "EPWM_TZ_TRIPOUT_TZ2", value: 3 },
	{ name: "EPWM_TZ_TRIPOUT_TZ3", value: 4 },
	{ name: "EPWM_TZ_TRIPOUT_TZ4", value: 5 },
	{ name: "EPWM_TZ_TRIPOUT_TZ5", value: 6 },
	{ name: "EPWM_TZ_TRIPOUT_TZ6", value: 7 },
	{ name: "EPWM_TZ_TRIPOUT_DCAEVT1", value: 8 },
	{ name: "EPWM_TZ_TRIPOUT_DCAEVT2", value: 9 },
	{ name: "EPWM_TZ_TRIPOUT_DCBEVT1", value: 10 },
	{ name: "EPWM_TZ_TRIPOUT_DCBEVT2", value: 11 },
	{ name: "EPWM_TZ_TRIPOUT_CAPEVT", value: 12 },
]
let EPWM_ADCStartOfConversionType = [
	{ name: "EPWM_SOC_A", value: 0 },
	{ name: "EPWM_SOC_B", value: 1 },
]
let EPWM_ADCStartOfConversionSource = [
	{ name: "EPWM_SOC_DCxEVT1", value: 0 },
	{ name: "EPWM_SOC_TBCTR_ZERO", value: 1 },
	{ name: "EPWM_SOC_TBCTR_PERIOD", value: 2 },
	{ name: "EPWM_SOC_TBCTR_ETSOCAMIX", value: 3 },
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
	{ name: "EPWM_DC_WINDOW_START_BLANK_PULSE_MIX", value: 3 },
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
let EPWM_DigitalCompareCBCLatchMode = [
	{ name: "EPWM_DC_CBC_LATCH_DISABLED", value: 0x0 },
	{ name: "EPWM_DC_CBC_LATCH_ENABLED", value: 0x1 },
]
let EPWM_DigitalCompareCBCLatchClearEvent = [
	{ name: "EPWM_DC_CBC_LATCH_CLR_CNTR_ZERO", value: 0x0 },
	{ name: "EPWM_DC_CBC_LATCH_CLR_ON_CNTR_PERIOD", value: 0x1 },
	{ name: "EPWM_DC_CBC_LATCH_CLR_ON_CNTR_ZERO_PERIOD", value: 0x2 },
]
let EPWM_selectCaptureGateInputPolarity = [
	{ name: "EPWM_CAPGATE_INPUT_ALWAYS_ON", value: 0 },
	{ name: "EPWM_CAPGATE_INPUT_ALWAYS_OFF", value: 1 },
	{ name: "EPWM_CAPGATE_INPUT_SYNC", value: 2 },
	{ name: "EPWM_CAPGATE_INPUT_SYNC_INVERT", value: 3 },
]
let EPWM_selectCaptureInputPolarity = [
	{ name: "EPWM_CAPTURE_INPUT_CAPIN_SYNC", value: 0 },
	{ name: "EPWM_CAPTURE_INPUT_CAPIN_SYNC_INVERT", value: 1 },
]
let EPWM_CaptureInputType = [
	{ name: "EPWM_CAPTURE_GATE", value: 1 },
	{ name: "EPWM_CAPTURE_INPUT", value: 0 },
]
let EPWM_GlobalLoadTrigger = [
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_ZERO", value: 0x0 },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_PERIOD", value: 0x1 },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD", value: 0x2 },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC", value: 0x3 },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_ZERO", value: 0x4 },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_PERIOD", value: 0x5 },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD", value: 0x6 },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_U_CMPC", value: 0x8 },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_D_CMPC", value: 0x9 },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_U_CMPD", value: 0xA },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_D_CMPD", value: 0xB },
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
let EPWM_ETMixTriggerSource = [
	{ name: "EPWM_ETMIX_TBCTR_ZERO", value: 0 },
	{ name: "EPWM_ETMIX_TBCTR_PERIOD", value: 1 },
	{ name: "EPWM_ETMIX_TBCTR_U_CMPA", value: 2 },
	{ name: "EPWM_ETMIX_TBCTR_D_CMPA", value: 3 },
	{ name: "EPWM_ETMIX_TBCTR_U_CMPB", value: 4 },
	{ name: "EPWM_ETMIX_TBCTR_D_CMPB", value: 5 },
	{ name: "EPWM_ETMIX_TBCTR_U_CMPC", value: 6 },
	{ name: "EPWM_ETMIX_TBCTR_D_CMPC", value: 7 },
	{ name: "EPWM_ETMIX_TBCTR_U_CMPD", value: 8 },
	{ name: "EPWM_ETMIX_TBCTR_D_CMPD", value: 9 },
	{ name: "EPWM_ETMIX_DCAEVT1", value: 10 },
]
let EPWM_ETMixSignalSelect = [
	{ name: "EPWM_ETMIX_INTERRUPT", value: 0x0 },
	{ name: "EPWM_ETMIX_SOCA", value: 0x2 },
	{ name: "EPWM_ETMIX_SOCB", value: 0x4 },
]
let EPWM_LockRegisterGroup = [
	{ name: "EPWM_REGISTER_GROUP_GLOBAL_LOAD", value: 0x2 },
	{ name: "EPWM_REGISTER_GROUP_TRIP_ZONE", value: 0x4 },
	{ name: "EPWM_REGISTER_GROUP_TRIP_ZONE_CLEAR", value: 0x8 },
	{ name: "EPWM_REGISTER_GROUP_DIGITAL_COMPARE", value: 0x10 },
]
let EPWM_O = [
	{ name: "EPWM_O_XCMP", value: 0x100 },
	{ name: "EPWM_O_DE", value: 0x1c0 },
	{ name: "EPWM_O_MINDB", value: 0x1e0 },
]
let EPWM_SYNC_OUT_SOURCE_M = [
	{ name: "EPWM_SYNC_OUT_SOURCE_M", value: "((uint16_t)EPWM_SYNCOUTEN_SWEN" },
]
let EPWM_SYNC_OUT_PULSE_ON = [
	{ name: "EPWM_SYNC_OUT_PULSE_ON_SOFTWARE", value: "EPWM_SYNCOUTEN_SWEN" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO", value: "EPWM_SYNCOUTEN_ZEROEN" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_B", value: "EPWM_SYNCOUTEN_CMPBEN" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_C", value: "EPWM_SYNCOUTEN_CMPCEN" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_D", value: "EPWM_SYNCOUTEN_CMPDEN" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_DCA_EVT1_SYNC", value: "EPWM_SYNCOUTEN_DCAEVT1EN" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_DCB_EVT1_SYNC", value: "EPWM_SYNCOUTEN_DCBEVT1EN" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_ALL", value: "EPWM_SYNC_OUT_SOURCE_M" },
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
let EPWM_XCMP = [
	{ name: "EPWM_XCMP_ACTIVE", value: 0x0 },
	{ name: "EPWM_XCMP_SHADOW1", value: 0x1 },
	{ name: "EPWM_XCMP_SHADOW2", value: 0x2 },
	{ name: "EPWM_XCMP_SHADOW3", value: 0x3 },
]
let EPWM_MINDB_BLOCK = [
	{ name: "EPWM_MINDB_BLOCK_A", value: 0x0 },
	{ name: "EPWM_MINDB_BLOCK_B", value: 0x1 },
]
let EPWM_MINDB_REF = [
	{ name: "EPWM_MINDB_REF_SIG", value: 0x0 },
	{ name: "EPWM_MINDB_REF_SIG_INVERT", value: 0x1 },
]
let EPWM_MINDB_POLSEL = [
	{ name: "EPWM_MINDB_POLSEL_INVERT_LOGICAL_AND", value: 0x0 },
	{ name: "EPWM_MINDB_POLSEL_LOGICAL_OR", value: 0x1 },
]
let EPWM_MINDB_BLOCKING_SIGNAL = [
	{ name: "EPWM_MINDB_BLOCKING_SIGNAL_BYPASS", value: 0x0 },
	{ name: "EPWM_MINDB_BLOCKING_SIGNAL_SWAPBLOCK", value: 0x1 },
]
let EPWM_MINDB_SEL = [
	{ name: "EPWM_MINDB_SEL_DEPWM", value: 0x0 },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT1", value: 0x1 },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT2", value: 0x2 },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT3", value: 0x3 },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT4", value: 0x4 },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT5", value: 0x5 },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT6", value: 0x6 },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT7", value: 0x7 },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT8", value: 0x8 },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT9", value: 0x9 },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT10", value: 0xa },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT11", value: 0xb },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT12", value: 0xc },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT13", value: 0xd },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT14", value: 0xe },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT15", value: 0xf },
]
let EPWM_MINDB_ICL_XBAR = [
	{ name: "EPWM_MINDB_ICL_XBAR_OUT1", value: 0x0 },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT2", value: 0x1 },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT3", value: 0x2 },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT4", value: 0x3 },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT5", value: 0x4 },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT6", value: 0x5 },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT7", value: 0x6 },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT8", value: 0x7 },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT9", value: 0x8 },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT10", value: 0x9 },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT11", value: 0xa },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT12", value: 0xb },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT13", value: 0xc },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT14", value: 0xd },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT15", value: 0xe },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT16", value: 0xf },
]
let EPWM_MINDB_ICL_LUT = [
	{ name: "EPWM_MINDB_ICL_LUT_DEC0", value: 16 },
	{ name: "EPWM_MINDB_ICL_LUT_DEC1", value: 17 },
	{ name: "EPWM_MINDB_ICL_LUT_DEC2", value: 18 },
	{ name: "EPWM_MINDB_ICL_LUT_DEC3", value: 19 },
	{ name: "EPWM_MINDB_ICL_LUT_DEC4", value: 20 },
	{ name: "EPWM_MINDB_ICL_LUT_DEC5", value: 21 },
	{ name: "EPWM_MINDB_ICL_LUT_DEC6", value: 22 },
	{ name: "EPWM_MINDB_ICL_LUT_DEC7", value: 23 },
]
let EPWM_DE_SRC = [
	{ name: "EPWM_DE_SRC_TRIPL", value: 0x1 },
	{ name: "EPWM_DE_SRC_TRIPH", value: 0x0 },
]
let EPWM_DE_CHANNEL = [
	{ name: "EPWM_DE_CHANNEL_A", value: 0x0 },
	{ name: "EPWM_DE_CHANNEL_B", value: 0x1 },
]
let EPWM_DE_COUNT = [
	{ name: "EPWM_DE_COUNT_UP", value: 0x0 },
	{ name: "EPWM_DE_COUNT_DOWN", value: 0x1 },
]
let EPWM_TZ_INTERRUPT = [
	{ name: "EPWM_TZ_INTERRUPT_CBC", value: 0x2 },
	{ name: "EPWM_TZ_INTERRUPT_OST", value: 0x4 },
	{ name: "EPWM_TZ_INTERRUPT_DCAEVT1", value: 0x8 },
	{ name: "EPWM_TZ_INTERRUPT_DCAEVT2", value: 0x10 },
	{ name: "EPWM_TZ_INTERRUPT_DCBEVT1", value: 0x20 },
	{ name: "EPWM_TZ_INTERRUPT_DCBEVT2", value: 0x40 },
	{ name: "EPWM_TZ_INTERRUPT_CAPEVT", value: 0x80 },
]
let EPWM_TZ_FLAG = [
	{ name: "EPWM_TZ_FLAG_CBC", value: 0x2 },
	{ name: "EPWM_TZ_FLAG_OST", value: 0x4 },
	{ name: "EPWM_TZ_FLAG_DCAEVT1", value: 0x8 },
	{ name: "EPWM_TZ_FLAG_DCAEVT2", value: 0x10 },
	{ name: "EPWM_TZ_FLAG_DCBEVT1", value: 0x20 },
	{ name: "EPWM_TZ_FLAG_DCBEVT2", value: 0x40 },
	{ name: "EPWM_TZ_FLAG_CAPEVT", value: 0x80 },
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
	{ name: "EPWM_TZ_CBC_FLAG_CAPEVT", value: 0x100 },
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
	{ name: "EPWM_TZ_OST_FLAG_CAPEVT", value: 0x100 },
]
let EPWM_TZ_FORCE_EVENT = [
	{ name: "EPWM_TZ_FORCE_EVENT_CBC", value: 0x2 },
	{ name: "EPWM_TZ_FORCE_EVENT_OST", value: 0x4 },
	{ name: "EPWM_TZ_FORCE_EVENT_DCAEVT1", value: 0x8 },
	{ name: "EPWM_TZ_FORCE_EVENT_DCAEVT2", value: 0x10 },
	{ name: "EPWM_TZ_FORCE_EVENT_DCBEVT1", value: 0x20 },
	{ name: "EPWM_TZ_FORCE_EVENT_DCBEVT2", value: 0x40 },
	{ name: "EPWM_TZ_FORCE_EVENT_CAPEVT", value: 0x80 },
]
let EPWM_INT_TBCTR = [
	{ name: "EPWM_INT_TBCTR_DISABLED", value: 0 },
	{ name: "EPWM_INT_TBCTR_ZERO", value: 1 },
	{ name: "EPWM_INT_TBCTR_PERIOD", value: 2 },
	{ name: "EPWM_INT_TBCTR_ETINTMIX", value: 3 },
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
	EPWM_SyncInPulseSource: EPWM_SyncInPulseSource,
	EPWM_OneShotSyncOutTrigger: EPWM_OneShotSyncOutTrigger,
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
	EPWM_XCMPReg: EPWM_XCMPReg,
	EPWM_XCompareReg: EPWM_XCompareReg,
	EPWM_XMinMaxReg: EPWM_XMinMaxReg,
	EPWM_XCMPActionQualifierOutputEvent: EPWM_XCMPActionQualifierOutputEvent,
	EPWM_XCMP_ALLOC_CMPA: EPWM_XCMP_ALLOC_CMPA,
	EPWM_XCMP_ALLOC_CMPB: EPWM_XCMP_ALLOC_CMPB,
	EPWM_XCMPXloadCtlLoadMode: EPWM_XCMPXloadCtlLoadMode,
	EPWM_XCMP_XLOADCTL_SHDWLEVEL: EPWM_XCMP_XLOADCTL_SHDWLEVEL,
	EPWM_XCMP_XLOADCTL_SHDWBUFPTR: EPWM_XCMP_XLOADCTL_SHDWBUFPTR,
	EPWM_DiodeEmulationMode: EPWM_DiodeEmulationMode,
	EPWM_DiodeEmulationTripLSource: EPWM_DiodeEmulationTripLSource,
	EPWM_DiodeEmulationTripHSource: EPWM_DiodeEmulationTripHSource,
	EPWM_DiodeEmulationSignal: EPWM_DiodeEmulationSignal,
	EPWM_CycleByCycleTripZoneClearMode: EPWM_CycleByCycleTripZoneClearMode,
	EPWM_selectTripOutSource: EPWM_selectTripOutSource,
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
	EPWM_DigitalCompareCBCLatchMode: EPWM_DigitalCompareCBCLatchMode,
	EPWM_DigitalCompareCBCLatchClearEvent: EPWM_DigitalCompareCBCLatchClearEvent,
	EPWM_selectCaptureGateInputPolarity: EPWM_selectCaptureGateInputPolarity,
	EPWM_selectCaptureInputPolarity: EPWM_selectCaptureInputPolarity,
	EPWM_CaptureInputType: EPWM_CaptureInputType,
	EPWM_GlobalLoadTrigger: EPWM_GlobalLoadTrigger,
	EPWM_ValleyTriggerSource: EPWM_ValleyTriggerSource,
	EPWM_ValleyCounterEdge: EPWM_ValleyCounterEdge,
	EPWM_ValleyDelayMode: EPWM_ValleyDelayMode,
	EPWM_DigitalCompareEdgeFilterMode: EPWM_DigitalCompareEdgeFilterMode,
	EPWM_DigitalCompareEdgeFilterEdgeCount: EPWM_DigitalCompareEdgeFilterEdgeCount,
	EPWM_ETMixTriggerSource: EPWM_ETMixTriggerSource,
	EPWM_ETMixSignalSelect: EPWM_ETMixSignalSelect,
	EPWM_LockRegisterGroup: EPWM_LockRegisterGroup,
	EPWM_O: EPWM_O,
	EPWM_SYNC_OUT_SOURCE_M: EPWM_SYNC_OUT_SOURCE_M,
	EPWM_SYNC_OUT_PULSE_ON: EPWM_SYNC_OUT_PULSE_ON,
	EPWM_TIME_BASE_STATUS_COUNT: EPWM_TIME_BASE_STATUS_COUNT,
	EPWM_DB_INPUT: EPWM_DB_INPUT,
	EPWM_TZ_SIGNAL: EPWM_TZ_SIGNAL,
	EPWM_XCMP: EPWM_XCMP,
	EPWM_MINDB_BLOCK: EPWM_MINDB_BLOCK,
	EPWM_MINDB_REF: EPWM_MINDB_REF,
	EPWM_MINDB_POLSEL: EPWM_MINDB_POLSEL,
	EPWM_MINDB_BLOCKING_SIGNAL: EPWM_MINDB_BLOCKING_SIGNAL,
	EPWM_MINDB_SEL: EPWM_MINDB_SEL,
	EPWM_MINDB_ICL_XBAR: EPWM_MINDB_ICL_XBAR,
	EPWM_MINDB_ICL_LUT: EPWM_MINDB_ICL_LUT,
	EPWM_DE_SRC: EPWM_DE_SRC,
	EPWM_DE_CHANNEL: EPWM_DE_CHANNEL,
	EPWM_DE_COUNT: EPWM_DE_COUNT,
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
