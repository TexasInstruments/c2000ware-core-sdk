let EPWM_EmulationMode = [
	{ name: "EPWM_EMULATION_STOP_AFTER_NEXT_TB", displayName: "Stop after next Time Base counter increment or decrement" },
	{ name: "EPWM_EMULATION_STOP_AFTER_FULL_CYCLE", displayName: "Stop when counter completes whole cycle" },
	{ name: "EPWM_EMULATION_FREE_RUN", displayName: "Free run" },
]
let EPWM_SyncCountMode = [
	{ name: "EPWM_COUNT_MODE_DOWN_AFTER_SYNC", displayName: "Count down after sync event" },
	{ name: "EPWM_COUNT_MODE_UP_AFTER_SYNC", displayName: "Count up after sync event" },
]
let EPWM_ClockDivider = [
	{ name: "EPWM_CLOCK_DIVIDER_1", displayName: "Divide clock by 1" },
	{ name: "EPWM_CLOCK_DIVIDER_2", displayName: "Divide clock by 2" },
	{ name: "EPWM_CLOCK_DIVIDER_4", displayName: "Divide clock by 4" },
	{ name: "EPWM_CLOCK_DIVIDER_8", displayName: "Divide clock by 8" },
	{ name: "EPWM_CLOCK_DIVIDER_16", displayName: "Divide clock by 16" },
	{ name: "EPWM_CLOCK_DIVIDER_32", displayName: "Divide clock by 32" },
	{ name: "EPWM_CLOCK_DIVIDER_64", displayName: "Divide clock by 64" },
	{ name: "EPWM_CLOCK_DIVIDER_128", displayName: "Divide clock by 128" },
]
let EPWM_HSClockDivider = [
	{ name: "EPWM_HSCLOCK_DIVIDER_1", displayName: "Divide clock by 1" },
	{ name: "EPWM_HSCLOCK_DIVIDER_2", displayName: "Divide clock by 2" },
	{ name: "EPWM_HSCLOCK_DIVIDER_4", displayName: "Divide clock by 4" },
	{ name: "EPWM_HSCLOCK_DIVIDER_6", displayName: "Divide clock by 6" },
	{ name: "EPWM_HSCLOCK_DIVIDER_8", displayName: "Divide clock by 8" },
	{ name: "EPWM_HSCLOCK_DIVIDER_10", displayName: "Divide clock by 10" },
	{ name: "EPWM_HSCLOCK_DIVIDER_12", displayName: "Divide clock by 12" },
	{ name: "EPWM_HSCLOCK_DIVIDER_14", displayName: "Divide clock by 14" },
]
let EPWM_SyncInPulseSource = [
	{ name: "EPWM_SYNC_IN_PULSE_SRC_DISABLE", displayName: "Disable Sync-in" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM1", displayName: "Sync-in source is EPWM1 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM2", displayName: "Sync-in source is EPWM2 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM3", displayName: "Sync-in source is EPWM3 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM4", displayName: "Sync-in source is EPWM4 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM5", displayName: "Sync-in source is EPWM5 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM6", displayName: "Sync-in source is EPWM6 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM7", displayName: "Sync-in source is EPWM7 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM8", displayName: "Sync-in source is EPWM8 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM9", displayName: "Sync-in source is EPWM9 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM10", displayName: "Sync-in source is EPWM10 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM11", displayName: "Sync-in source is EPWM11 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM12", displayName: "Sync-in source is EPWM12 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM13", displayName: "Sync-in source is EPWM13 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM14", displayName: "Sync-in source is EPWM14 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM15", displayName: "Sync-in source is EPWM15 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM16", displayName: "Sync-in source is EPWM16 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP1", displayName: "Sync-in source is ECAP1 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP2", displayName: "Sync-in source is ECAP2 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP3", displayName: "Sync-in source is ECAP3 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP4", displayName: "Sync-in source is ECAP4 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP5", displayName: "Sync-in source is ECAP5 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP6", displayName: "Sync-in source is ECAP6 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_ECAP7", displayName: "Sync-in source is ECAP7 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT5", displayName: "Sync-in source is Input XBAR out5 signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_INPUTXBAR_OUT6", displayName: "Sync-in source is Input XBAR out6 signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_ETHERCAT_SYNC0", displayName: "Sync-in source is Ethercat sync0 signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_ETHERCAT_SYNC1", displayName: "Sync-in source is Ethercat sync1 signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM17", displayName: "Sync-in source is EPWM17 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM18", displayName: "Sync-in source is EPWM18 sync-out signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_FSIRXA_TRIG1", displayName: "Sync-in source is FSI RXA trigger1 signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_FSIRXB_TRIG1", displayName: "Sync-in source is FSI RXB trigger1 signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_FSIRXC_TRIG1", displayName: "Sync-in source is FSI RXC trigger1 signal" },
	{ name: "EPWM_SYNC_IN_PULSE_SRC_FSIRXD_TRIG1", displayName: "Sync-in source is FSI RXD trigger1 signal" },
]
let EPWM_OneShotSyncOutTrigger = [
	{ name: "EPWM_OSHT_SYNC_OUT_TRIG_SYNC", displayName: "Trigger is OSHT sync" },
	{ name: "EPWM_OSHT_SYNC_OUT_TRIG_RELOAD", displayName: "Trigger is OSHT reload" },
]
let EPWM_PeriodLoadMode = [
	{ name: "EPWM_PERIOD_SHADOW_LOAD", displayName: "PWM Period register access is through shadow register" },
	{ name: "EPWM_PERIOD_DIRECT_LOAD", displayName: "PWM Period register access is directly" },
]
let EPWM_TimeBaseCountMode = [
	{ name: "EPWM_COUNTER_MODE_UP", displayName: "Up - count mode" },
	{ name: "EPWM_COUNTER_MODE_DOWN", displayName: "Down - count mode" },
	{ name: "EPWM_COUNTER_MODE_UP_DOWN", displayName: "Up - down - count mode" },
	{ name: "EPWM_COUNTER_MODE_STOP_FREEZE", displayName: "Stop - Freeze counter" },
]
let EPWM_PeriodShadowLoadMode = [
	{ name: "EPWM_SHADOW_LOAD_MODE_COUNTER_ZERO", displayName: "Shadow to active load occurs when time base counter reaches 0" },
	{ name: "EPWM_SHADOW_LOAD_MODE_COUNTER_SYNC", displayName: "Shadow to active load occurs when time base counter reaches 0 and a SYNC occurs" },
	{ name: "EPWM_SHADOW_LOAD_MODE_SYNC", displayName: "Shadow to active load occurs only when a SYNC occurs" },
]
let EPWM_CurrentLink = [
	{ name: "EPWM_LINK_WITH_EPWM_17", displayName: "link current ePWM with ePWM17" },
	{ name: "EPWM_LINK_WITH_EPWM_18", displayName: "link current ePWM with ePWM18" },
	{ name: "EPWM_LINK_WITH_EPWM_1", displayName: "link current ePWM with ePWM1" },
	{ name: "EPWM_LINK_WITH_EPWM_2", displayName: "link current ePWM with ePWM2" },
	{ name: "EPWM_LINK_WITH_EPWM_3", displayName: "link current ePWM with ePWM3" },
	{ name: "EPWM_LINK_WITH_EPWM_4", displayName: "link current ePWM with ePWM4" },
	{ name: "EPWM_LINK_WITH_EPWM_5", displayName: "link current ePWM with ePWM5" },
	{ name: "EPWM_LINK_WITH_EPWM_6", displayName: "link current ePWM with ePWM6" },
	{ name: "EPWM_LINK_WITH_EPWM_7", displayName: "link current ePWM with ePWM7" },
	{ name: "EPWM_LINK_WITH_EPWM_8", displayName: "link current ePWM with ePWM8" },
	{ name: "EPWM_LINK_WITH_EPWM_9", displayName: "link current ePWM with ePWM9" },
	{ name: "EPWM_LINK_WITH_EPWM_10", displayName: "link current ePWM with ePWM10" },
	{ name: "EPWM_LINK_WITH_EPWM_11", displayName: "link current ePWM with ePWM11" },
	{ name: "EPWM_LINK_WITH_EPWM_12", displayName: "link current ePWM with ePWM12" },
	{ name: "EPWM_LINK_WITH_EPWM_13", displayName: "link current ePWM with ePWM13" },
	{ name: "EPWM_LINK_WITH_EPWM_14", displayName: "link current ePWM with ePWM14" },
	{ name: "EPWM_LINK_WITH_EPWM_15", displayName: "link current ePWM with ePWM15" },
	{ name: "EPWM_LINK_WITH_EPWM_16", displayName: "link current ePWM with ePWM16" },
]
let EPWM_LinkComponent = [
	{ name: "EPWM_LINK_TBPRD", displayName: "link TBPRD registers" },
	{ name: "EPWM_LINK_COMP_A", displayName: "link COMPA registers" },
	{ name: "EPWM_LINK_COMP_B", displayName: "link COMPB registers" },
	{ name: "EPWM_LINK_COMP_C", displayName: "link COMPC registers" },
	{ name: "EPWM_LINK_COMP_D", displayName: "link COMPD registers" },
	{ name: "EPWM_LINK_GLDCTL2", displayName: "link GLDCTL2 registers" },
	{ name: "EPWM_LINK_DBRED", displayName: "link DBRED registers" },
	{ name: "EPWM_LINK_DBFED", displayName: "link DBFED registers" },
	{ name: "EPWM_LINK_XLOAD", displayName: "link XLOAD registers" },
]
let EPWM_CounterCompareModule = [
	{ name: "EPWM_COUNTER_COMPARE_A", displayName: "Counter compare A" },
	{ name: "EPWM_COUNTER_COMPARE_B", displayName: "Counter compare B" },
	{ name: "EPWM_COUNTER_COMPARE_C", displayName: "Counter compare C" },
	{ name: "EPWM_COUNTER_COMPARE_D", displayName: "Counter compare D" },
]
let EPWM_CounterCompareLoadMode = [
	{ name: "EPWM_COMP_LOAD_ON_CNTR_ZERO", displayName: "Load when counter equals zero" },
	{ name: "EPWM_COMP_LOAD_ON_CNTR_PERIOD", displayName: "Load when counter equals period" },
	{ name: "EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD", displayName: "Load when counter equals zero or period" },
	{ name: "EPWM_COMP_LOAD_FREEZE", displayName: "Freeze shadow to active load" },
	{ name: "EPWM_COMP_LOAD_ON_SYNC_CNTR_ZERO", displayName: "Load on sync or when counter equals zero" },
	{ name: "EPWM_COMP_LOAD_ON_SYNC_CNTR_PERIOD", displayName: "Load on sync or when counter equals period" },
	{ name: "EPWM_COMP_LOAD_ON_SYNC_CNTR_ZERO_PERIOD", displayName: "Load on sync or when counter equals zero or period" },
	{ name: "EPWM_COMP_LOAD_ON_SYNC_ONLY", displayName: "Load on sync only" },
]
let EPWM_ActionQualifierModule = [
	{ name: "EPWM_ACTION_QUALIFIER_A", displayName: "Action Qualifier A" },
	{ name: "EPWM_ACTION_QUALIFIER_B", displayName: "Action Qualifier B" },
]
let EPWM_ActionQualifierLoadMode = [
	{ name: "EPWM_AQ_LOAD_ON_CNTR_ZERO", displayName: "Load when counter equals zero" },
	{ name: "EPWM_AQ_LOAD_ON_CNTR_PERIOD", displayName: "Load when counter equals period" },
	{ name: "EPWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD", displayName: "Load when counter equals zero or period" },
	{ name: "EPWM_AQ_LOAD_FREEZE", displayName: "Freeze shadow to active load" },
	{ name: "EPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO", displayName: "Load on sync or when counter equals zero" },
	{ name: "EPWM_AQ_LOAD_ON_SYNC_CNTR_PERIOD", displayName: "Load on sync or when counter equals period" },
	{ name: "EPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO_PERIOD", displayName: "Load on sync or when counter equals zero or period" },
	{ name: "EPWM_AQ_LOAD_ON_SYNC_ONLY", displayName: "Load on sync only" },
]
let EPWM_ActionQualifierTriggerSource = [
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_1", displayName: "Digital compare event A 1" },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_DCA_2", displayName: "Digital compare event A 2" },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_DCB_1", displayName: "Digital compare event B 1" },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_DCB_2", displayName: "Digital compare event B 2" },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_TZ_1", displayName: "Trip zone 1" },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_TZ_2", displayName: "Trip zone 2" },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_TZ_3", displayName: "Trip zone 3" },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_EPWM_SYNCIN", displayName: "ePWM sync" },
	{ name: "EPWM_AQ_TRIGGER_EVENT_TRIG_DC_EVTFILT", displayName: "Digital compare filter event" },
]
let EPWM_ActionQualifierOutputEvent = [
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO", displayName: "Time base counter equals zero" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD", displayName: "Time base counter equals period" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA", displayName: "Time base counter up equals COMPA" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA", displayName: "Time base counter down equals COMPA" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB", displayName: "Time base counter up equals COMPB" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB", displayName: "Time base counter down equals COMPB" },
	{ name: "EPWM_AQ_OUTPUT_ON_T1_COUNT_UP", displayName: "T1 event on count up" },
	{ name: "EPWM_AQ_OUTPUT_ON_T1_COUNT_DOWN", displayName: "T1 event on count down" },
	{ name: "EPWM_AQ_OUTPUT_ON_T2_COUNT_UP", displayName: "T2 event on count up" },
	{ name: "EPWM_AQ_OUTPUT_ON_T2_COUNT_DOWN", displayName: "T2 event on count down" },
]
let EPWM_ActionQualifierOutput = [
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE", displayName: "No change in the output pins" },
	{ name: "EPWM_AQ_OUTPUT_LOW", displayName: "Set output pins to low" },
	{ name: "EPWM_AQ_OUTPUT_HIGH", displayName: "Set output pins to High" },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE", displayName: "Toggle the output pins" },
]
let EPWM_ActionQualifierSWOutput = [
	{ name: "EPWM_AQ_SW_DISABLED", displayName: "Software forcing disabled" },
	{ name: "EPWM_AQ_SW_OUTPUT_LOW", displayName: "Set output pins to low" },
	{ name: "EPWM_AQ_SW_OUTPUT_HIGH", displayName: "Set output pins to High" },
]
let EPWM_ActionQualifierEventAction = [
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_ZERO", displayName: "Time base counter equals zero and no change in the output pins" },
	{ name: "EPWM_AQ_OUTPUT_LOW_ZERO", displayName: "Time base counter equals zero and set output pins to low" },
	{ name: "EPWM_AQ_OUTPUT_HIGH_ZERO", displayName: "Time base counter equals zero and set output pins to high" },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_ZERO", displayName: "Time base counter equals zero and toggle the output pins" },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_PERIOD", displayName: "Time base counter equals period and no change in the output pins" },
	{ name: "EPWM_AQ_OUTPUT_LOW_PERIOD", displayName: "Time base counter equals period and set output pins to low" },
	{ name: "EPWM_AQ_OUTPUT_HIGH_PERIOD", displayName: "Time base counter equals period and set output pins to high" },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_PERIOD", displayName: "Time base counter equals period and toggle the output pins" },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPA", displayName: "Time base counter up equals COMPA and no change in the output pins" },
	{ name: "EPWM_AQ_OUTPUT_LOW_UP_CMPA", displayName: "Time base counter up equals COMPA and set output pins to low" },
	{ name: "EPWM_AQ_OUTPUT_HIGH_UP_CMPA", displayName: "Time base counter up equals COMPA and set output pins to high" },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_UP_CMPA", displayName: "Time base counter up equals COMPA and toggle the output pins" },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPA", displayName: "Time base counter down equals COMPA and no change in the output pins" },
	{ name: "EPWM_AQ_OUTPUT_LOW_DOWN_CMPA", displayName: "Time base counter down equals COMPA and set output pins to low" },
	{ name: "EPWM_AQ_OUTPUT_HIGH_DOWN_CMPA", displayName: "Time base counter down equals COMPA and set output pins to high" },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPA", displayName: "Time base counter down equals COMPA and toggle the output pins" },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_UP_CMPB", displayName: "Time base counter up equals COMPB and no change in the output pins" },
	{ name: "EPWM_AQ_OUTPUT_LOW_UP_CMPB", displayName: "Time base counter up equals COMPB and set output pins to low" },
	{ name: "EPWM_AQ_OUTPUT_HIGH_UP_CMPB", displayName: "Time base counter up equals COMPB and set output pins to high" },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_UP_CMPB", displayName: "Time base counter up equals COMPB and toggle the output pins" },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_DOWN_CMPB", displayName: "Time base counter down equals COMPB and no change in the output pins" },
	{ name: "EPWM_AQ_OUTPUT_LOW_DOWN_CMPB", displayName: "Time base counter down equals COMPB and set output pins to low" },
	{ name: "EPWM_AQ_OUTPUT_HIGH_DOWN_CMPB", displayName: "Time base counter down equals COMPB and set output pins to high" },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_DOWN_CMPB", displayName: "Time base counter down equals COMPB and toggle the output pins" },
]
let EPWM_AdditionalActionQualifierEventAction = [
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_UP_T1", displayName: "T1 event on count up and no change in the output pins" },
	{ name: "EPWM_AQ_OUTPUT_LOW_UP_T1", displayName: "T1 event on count up and set output pins to low" },
	{ name: "EPWM_AQ_OUTPUT_HIGH_UP_T1", displayName: "T1 event on count up and set output pins to high" },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_UP_T1", displayName: "T1 event on count up and toggle the output pins" },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_DOWN_T1", displayName: "T1 event on count down and no change in the output pins" },
	{ name: "EPWM_AQ_OUTPUT_LOW_DOWN_T1", displayName: "T1 event on count down and set output pins to low" },
	{ name: "EPWM_AQ_OUTPUT_HIGH_DOWN_T1", displayName: "T1 event on count down and set output pins to high" },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_DOWN_T1", displayName: "T1 event on count down and toggle the output pins" },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_UP_T2", displayName: "T2 event on count up and no change in the output pins" },
	{ name: "EPWM_AQ_OUTPUT_LOW_UP_T2", displayName: "T2 event on count up and set output pins to low" },
	{ name: "EPWM_AQ_OUTPUT_HIGH_UP_T2", displayName: "T2 event on count up and set output pins to high" },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_UP_T2", displayName: "T2 event on count up and toggle the output pins" },
	{ name: "EPWM_AQ_OUTPUT_NO_CHANGE_DOWN_T2", displayName: "T2 event on count down and no change in the output pins" },
	{ name: "EPWM_AQ_OUTPUT_LOW_DOWN_T2", displayName: "T2 event on count down and set output pins to low" },
	{ name: "EPWM_AQ_OUTPUT_HIGH_DOWN_T2", displayName: "T2 event on count down and set output pins to high" },
	{ name: "EPWM_AQ_OUTPUT_TOGGLE_DOWN_T2", displayName: "T2 event on count down and toggle the output pins" },
]
let EPWM_ActionQualifierOutputModule = [
	{ name: "EPWM_AQ_OUTPUT_A", displayName: "ePWMxA output" },
	{ name: "EPWM_AQ_OUTPUT_B", displayName: "ePWMxB output" },
]
let EPWM_ActionQualifierContForce = [
	{ name: "EPWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO", displayName: "Shadow mode load when counter equals zero" },
	{ name: "EPWM_AQ_SW_SH_LOAD_ON_CNTR_PERIOD", displayName: "Shadow mode load when counter equals period" },
	{ name: "EPWM_AQ_SW_SH_LOAD_ON_CNTR_ZERO_PERIOD", displayName: "Shadow mode load when counter equals zero or period" },
	{ name: "EPWM_AQ_SW_IMMEDIATE_LOAD", displayName: "No shadow load mode. Immediate mode only." },
]
let EPWM_DeadBandOutput = [
	{ name: "EPWM_DB_OUTPUT_A", displayName: "DB output is ePWMA" },
	{ name: "EPWM_DB_OUTPUT_B", displayName: "DB output is ePWMB" },
]
let EPWM_DeadBandDelayMode = [
	{ name: "EPWM_DB_RED", displayName: "DB RED (Rising Edge Delay) mode" },
	{ name: "EPWM_DB_FED", displayName: "DB FED (Falling Edge Delay) mode" },
]
let EPWM_DeadBandPolarity = [
	{ name: "EPWM_DB_POLARITY_ACTIVE_HIGH", displayName: "DB polarity is not inverted" },
	{ name: "EPWM_DB_POLARITY_ACTIVE_LOW", displayName: "DB polarity is inverted" },
]
let EPWM_DeadBandControlLoadMode = [
	{ name: "EPWM_DB_LOAD_ON_CNTR_ZERO", displayName: "Load when counter equals zero" },
	{ name: "EPWM_DB_LOAD_ON_CNTR_PERIOD", displayName: "Load when counter equals period" },
	{ name: "EPWM_DB_LOAD_ON_CNTR_ZERO_PERIOD", displayName: "Load when counter equals zero or period" },
	{ name: "EPWM_DB_LOAD_FREEZE", displayName: "Freeze shadow to active load" },
]
let EPWM_RisingEdgeDelayLoadMode = [
	{ name: "EPWM_RED_LOAD_ON_CNTR_ZERO", displayName: "Load when counter equals zero" },
	{ name: "EPWM_RED_LOAD_ON_CNTR_PERIOD", displayName: "Load when counter equals period" },
	{ name: "EPWM_RED_LOAD_ON_CNTR_ZERO_PERIOD", displayName: "Load when counter equals zero or period" },
	{ name: "EPWM_RED_LOAD_FREEZE", displayName: "Freeze shadow to active load" },
]
let EPWM_FallingEdgeDelayLoadMode = [
	{ name: "EPWM_FED_LOAD_ON_CNTR_ZERO", displayName: "Load when counter equals zero" },
	{ name: "EPWM_FED_LOAD_ON_CNTR_PERIOD", displayName: "Load when counter equals period" },
	{ name: "EPWM_FED_LOAD_ON_CNTR_ZERO_PERIOD", displayName: "Load when counter equals zero or period" },
	{ name: "EPWM_FED_LOAD_FREEZE", displayName: "Freeze shadow to active load" },
]
let EPWM_DeadBandClockMode = [
	{ name: "EPWM_DB_COUNTER_CLOCK_FULL_CYCLE", displayName: "Dead band counter runs at TBCLK rate" },
	{ name: "EPWM_DB_COUNTER_CLOCK_HALF_CYCLE", displayName: "Dead band counter runs at 2*TBCLK rate" },
]
let EPWM_TripZoneDigitalCompareOutput = [
	{ name: "EPWM_TZ_DC_OUTPUT_A1", displayName: "Digital Compare output 1 A" },
	{ name: "EPWM_TZ_DC_OUTPUT_A2", displayName: "Digital Compare output 2 A" },
	{ name: "EPWM_TZ_DC_OUTPUT_B1", displayName: "Digital Compare output 1 B" },
	{ name: "EPWM_TZ_DC_OUTPUT_B2", displayName: "Digital Compare output 2 B" },
]
let EPWM_TripZoneDigitalCompareOutputEvent = [
	{ name: "EPWM_TZ_EVENT_DC_DISABLED", displayName: "Event is disabled" },
	{ name: "EPWM_TZ_EVENT_DCXH_LOW", displayName: "Event when DCxH low" },
	{ name: "EPWM_TZ_EVENT_DCXH_HIGH", displayName: "Event when DCxH high" },
	{ name: "EPWM_TZ_EVENT_DCXL_LOW", displayName: "Event when DCxL low" },
	{ name: "EPWM_TZ_EVENT_DCXL_HIGH", displayName: "Event when DCxL high" },
	{ name: "EPWM_TZ_EVENT_DCXL_HIGH_DCXH_LOW", displayName: "Event when DCxL high DCxH low" },
]
let EPWM_TripZoneEvent = [
	{ name: "EPWM_TZ_ACTION_EVENT_TZA", displayName: "TZ1 - TZ6, DCAEVT2, DCAEVT1" },
	{ name: "EPWM_TZ_ACTION_EVENT_TZB", displayName: "TZ1 - TZ6, DCBEVT2, DCBEVT1" },
	{ name: "EPWM_TZ_ACTION_EVENT_DCAEVT1", displayName: "DCAEVT1 (Digital Compare A event 1)" },
	{ name: "EPWM_TZ_ACTION_EVENT_DCAEVT2", displayName: "DCAEVT2 (Digital Compare A event 2)" },
	{ name: "EPWM_TZ_ACTION_EVENT_DCBEVT1", displayName: "DCBEVT1 (Digital Compare B event 1)" },
	{ name: "EPWM_TZ_ACTION_EVENT_DCBEVT2", displayName: "DCBEVT2 (Digital Compare B event 2)" },
]
let EPWM_TripZoneAction = [
	{ name: "EPWM_TZ_ACTION_HIGH_Z", displayName: "High impedance output" },
	{ name: "EPWM_TZ_ACTION_HIGH", displayName: "High voltage state" },
	{ name: "EPWM_TZ_ACTION_LOW", displayName: "Low voltage state" },
	{ name: "EPWM_TZ_ACTION_DISABLE", displayName: "Disable action" },
]
let EPWM_TripZoneAdvancedEvent = [
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_TZB_D", displayName: "TZ1 - TZ6, DCBEVT2, DCBEVT1 while counting down" },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_TZB_U", displayName: "TZ1 - TZ6, DCBEVT2, DCBEVT1 while counting up" },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_TZA_D", displayName: "TZ1 - TZ6, DCAEVT2, DCAEVT1 while counting down" },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_TZA_U", displayName: "TZ1 - TZ6, DCAEVT2, DCAEVT1 while counting up" },
]
let EPWM_TripZoneAdvancedAction = [
	{ name: "EPWM_TZ_ADV_ACTION_HIGH_Z", displayName: "High impedance output" },
	{ name: "EPWM_TZ_ADV_ACTION_HIGH", displayName: "High voltage state" },
	{ name: "EPWM_TZ_ADV_ACTION_LOW", displayName: "Low voltage state" },
	{ name: "EPWM_TZ_ADV_ACTION_TOGGLE", displayName: "Toggle the output" },
	{ name: "EPWM_TZ_ADV_ACTION_DISABLE", displayName: "Disable action" },
]
let EPWM_TripZoneAdvDigitalCompareEvent = [
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U", displayName: "Digital Compare event A/B 1 while counting up" },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D", displayName: "Digital Compare event A/B 1 while counting down" },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U", displayName: "Digital Compare event A/B 2 while counting up" },
	{ name: "EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D", displayName: "Digital Compare event A/B 2 while counting down" },
]
let EPWM_XCMPReg = [
	{ name: "EPWM_XCMP1_ACTIVE", displayName: "XCMP1_ACTIVE" },
	{ name: "EPWM_XCMP2_ACTIVE", displayName: "XCMP2_ACTIVE" },
	{ name: "EPWM_XCMP3_ACTIVE", displayName: "XCMP3_ACTIVE" },
	{ name: "EPWM_XCMP4_ACTIVE", displayName: "XCMP4_ACTIVE" },
	{ name: "EPWM_XCMP5_ACTIVE", displayName: "XCMP5_ACTIVE" },
	{ name: "EPWM_XCMP6_ACTIVE", displayName: "XCMP6_ACTIVE" },
	{ name: "EPWM_XCMP7_ACTIVE", displayName: "XCMP7_ACTIVE" },
	{ name: "EPWM_XCMP8_ACTIVE", displayName: "XCMP8_ACTIVE" },
	{ name: "EPWM_XTBPRD_ACTIVE", displayName: "XTBPRD_ACTIVE" },
	{ name: "EPWM_XCMP1_SHADOW1", displayName: "XCMP1_SHADOW1" },
	{ name: "EPWM_XCMP2_SHADOW1", displayName: "XCMP2_SHADOW1" },
	{ name: "EPWM_XCMP3_SHADOW1", displayName: "XCMP3_SHADOW1" },
	{ name: "EPWM_XCMP4_SHADOW1", displayName: "XCMP4_SHADOW1" },
	{ name: "EPWM_XCMP5_SHADOW1", displayName: "XCMP5_SHADOW1" },
	{ name: "EPWM_XCMP6_SHADOW1", displayName: "XCMP6_SHADOW1" },
	{ name: "EPWM_XCMP7_SHADOW1", displayName: "XCMP7_SHADOW1" },
	{ name: "EPWM_XCMP8_SHADOW1", displayName: "XCMP8_SHADOW1" },
	{ name: "EPWM_XTBPRD_SHADOW1", displayName: "XTBPRD_SHADOW1" },
	{ name: "EPWM_XCMP1_SHADOW2", displayName: "XCMP1_SHADOW2" },
	{ name: "EPWM_XCMP2_SHADOW2", displayName: "XCMP2_SHADOW2" },
	{ name: "EPWM_XCMP3_SHADOW2", displayName: "XCMP3_SHADOW2" },
	{ name: "EPWM_XCMP4_SHADOW2", displayName: "XCMP4_SHADOW2" },
	{ name: "EPWM_XCMP5_SHADOW2", displayName: "XCMP5_SHADOW2" },
	{ name: "EPWM_XCMP6_SHADOW2", displayName: "XCMP6_SHADOW2" },
	{ name: "EPWM_XCMP7_SHADOW2", displayName: "XCMP7_SHADOW2" },
	{ name: "EPWM_XCMP8_SHADOW2", displayName: "XCMP8_SHADOW2" },
	{ name: "EPWM_XTBPRD_SHADOW2", displayName: "XTBPRD_SHADOW2" },
	{ name: "EPWM_XCMP1_SHADOW3", displayName: "XCMP1_SHADOW3" },
	{ name: "EPWM_XCMP2_SHADOW3", displayName: "XCMP2_SHADOW3" },
	{ name: "EPWM_XCMP3_SHADOW3", displayName: "XCMP3_SHADOW3" },
	{ name: "EPWM_XCMP4_SHADOW3", displayName: "XCMP4_SHADOW3" },
	{ name: "EPWM_XCMP5_SHADOW3", displayName: "XCMP5_SHADOW3" },
	{ name: "EPWM_XCMP6_SHADOW3", displayName: "XCMP6_SHADOW3" },
	{ name: "EPWM_XCMP7_SHADOW3", displayName: "XCMP7_SHADOW3" },
	{ name: "EPWM_XCMP8_SHADOW3", displayName: "XCMP8_SHADOW3" },
	{ name: "EPWM_XTBPRD_SHADOW3", displayName: "XTBPRD_SHADOW3" },
]
let EPWM_XCompareReg = [
	{ name: "EPWM_CMPC_SHADOW1", displayName: "CMPC_SHADOW1" },
	{ name: "EPWM_CMPD_SHADOW1", displayName: "CMPD_SHADOW1" },
	{ name: "EPWM_CMPC_SHADOW2", displayName: "CMPC_SHADOW2" },
	{ name: "EPWM_CMPD_SHADOW2", displayName: "CMPD_SHADOW2" },
	{ name: "EPWM_CMPC_SHADOW3", displayName: "CMPC_SHADOW3" },
	{ name: "EPWM_CMPD_SHADOW3", displayName: "CMPD_SHADOW3" },
]
let EPWM_XMinMaxReg = [
	{ name: "EPWM_XMAX_ACTIVE", displayName: "XMAX_ACTIVE" },
	{ name: "EPWM_XMIN_ACTIVE", displayName: "XMIN_ACTIVE" },
	{ name: "EPWM_XMAX_SHADOW1", displayName: "XMAX_SHADOW1" },
	{ name: "EPWM_XMIN_SHADOW1", displayName: "XMIN_SHADOW1" },
	{ name: "EPWM_XMAX_SHADOW2", displayName: "XMAX_SHADOW2" },
	{ name: "EPWM_XMIN_SHADOW2", displayName: "XMIN_SHADOW2" },
	{ name: "EPWM_XMAX_SHADOW3", displayName: "XMAX_SHADOW3" },
	{ name: "EPWM_XMIN_SHADOW3", displayName: "XMIN_SHADOW3" },
]
let EPWM_XCMPActionQualifierOutputEvent = [
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP1", displayName: "Time base counter equals XCMP1" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP2", displayName: "Time base counter equals XCMP2" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP3", displayName: "Time base counter equals XCMP3" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP4", displayName: "Time base counter equals XCMP4" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP5", displayName: "Time base counter equals XCMP5" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP6", displayName: "Time base counter equals XCMP6" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP7", displayName: "Time base counter equals XCMP7" },
	{ name: "EPWM_AQ_OUTPUT_ON_TIMEBASE_XCMP8", displayName: "Time base counter equals XCMP8" },
]
let EPWM_XCMP_ALLOC_CMPA = [
	{ name: "EPWM_XCMP_NONE_CMPA", displayName: "Allocate 0 XCMP registers to CMPA" },
	{ name: "EPWM_XCMP_1_CMPA", displayName: "Allocate XCMP1 register to CMPA" },
	{ name: "EPWM_XCMP_2_CMPA", displayName: "Allocate XCMP1 - XCMP2 registers to CMPA" },
	{ name: "EPWM_XCMP_3_CMPA", displayName: "Allocate XCMP1 - XCMP3 registers to CMPA" },
	{ name: "EPWM_XCMP_4_CMPA", displayName: "Allocate XCMP1 - XCMP4 registers to CMPA" },
	{ name: "EPWM_XCMP_5_CMPA", displayName: "Allocate XCMP1 - XCMP5 registers to CMPA" },
	{ name: "EPWM_XCMP_6_CMPA", displayName: "Allocate XCMP1 - XCMP6 registers to CMPA" },
	{ name: "EPWM_XCMP_7_CMPA", displayName: "Allocate XCMP1 - XCMP7 registers to CMPA" },
	{ name: "EPWM_XCMP_8_CMPA", displayName: "Allocate XCMP1 - XCMP8 registers to CMPA" },
]
let EPWM_XCMP_ALLOC_CMPB = [
	{ name: "EPWM_XCMP_5_CMPB", displayName: "Allocate XCMP5 register to CMPB" },
	{ name: "EPWM_XCMP_6_CMPB", displayName: "Allocate XCMP5 - XCMP6 registers to CMPB" },
	{ name: "EPWM_XCMP_7_CMPB", displayName: "Allocate XCMP5 - XCMP7 registers to CMPB" },
	{ name: "EPWM_XCMP_8_CMPB", displayName: "Allocate XCMP5 - XCMP8 registers to CMPB" },
]
let EPWM_XCMPXloadCtlLoadMode = [
	{ name: "EPWM_XCMP_XLOADCTL_LOADMODE_LOADONCE", displayName: "Load mode is LOADONCE" },
	{ name: "EPWM_XCMP_XLOADCTL_LOADMODE_LOADMULTIPLE", displayName: "Load mode is LOADMULTIPLE" },
]
let EPWM_XCMP_XLOADCTL_SHDWLEVEL = [
	{ name: "EPWM_XCMP_XLOADCTL_SHDWLEVEL_0", displayName: "Only Active register is available" },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWLEVEL_1", displayName: "SHDW1 and Active registers are available" },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWLEVEL_2", displayName: "SHDW2, SHDW1 and Active registers are available" },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWLEVEL_3", displayName: "SHDW3, SHDW2, SHDW1 and Active registers are available" },
]
let EPWM_XCMP_XLOADCTL_SHDWBUFPTR = [
	{ name: "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_NULL", displayName: "No Shadow buffer is in use" },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_ONE", displayName: "Shadow buffer 1 is in use" },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_TWO", displayName: "Shadow buffer 2 is in use" },
	{ name: "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_THREE", displayName: "Shadow buffer 3 is in use" },
]
let EPWM_DiodeEmulationMode = [
	{ name: "EPWM_DIODE_EMULATION_CBC", displayName: "Diode Emulation mode is Cycle by Cycle" },
	{ name: "EPWM_DIODE_EMULATION_OST", displayName: "Diode Emulation mode is One Shot" },
]
let EPWM_DiodeEmulationTripLSource = [
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL1", displayName: "Trip source is CMPSSTRIPL1 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL2", displayName: "Trip source is CMPSSTRIPL2 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL3", displayName: "Trip source is CMPSSTRIPL3 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL4", displayName: "Trip source is CMPSSTRIPL4 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL5", displayName: "Trip source is CMPSSTRIPL5 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL6", displayName: "Trip source is CMPSSTRIPL6 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL7", displayName: "Trip source is CMPSSTRIPL7 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL8", displayName: "Trip source is CMPSSTRIPL8 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL9", displayName: "Trip source is CMPSSTRIPL9 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL10", displayName: "Trip source is CMPSSTRIPL10 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CMPSSTRIPL11", displayName: "Trip source is CMPSSTRIPL11 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT1", displayName: "Trip source is INPUTXBAR out1 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT2", displayName: "Trip source is INPUTXBAR out2 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT3", displayName: "Trip source is INPUTXBAR out3 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT4", displayName: "Trip source is INPUTXBAR out4 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT5", displayName: "Trip source is INPUTXBAR out5 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT6", displayName: "Trip source is INPUTXBAR out6 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT7", displayName: "Trip source is INPUTXBAR out7 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT8", displayName: "Trip source is INPUTXBAR out8 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT9", displayName: "Trip source is INPUTXBAR out9 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT10", displayName: "Trip source is INPUTXBAR out10 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT11", displayName: "Trip source is INPUTXBAR out11 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT12", displayName: "Trip source is INPUTXBAR out12 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT13", displayName: "Trip source is INPUTXBAR out13 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT14", displayName: "Trip source is INPUTXBAR out14 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT15", displayName: "Trip source is INPUTXBAR out15 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_INPUTXBAR_OUT16", displayName: "Trip source is INPUTXBAR out16 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT1", displayName: "Trip source is CLBINPUTXBAR out1 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT2", displayName: "Trip source is CLBINPUTXBAR out2 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT3", displayName: "Trip source is CLBINPUTXBAR out3 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT4", displayName: "Trip source is CLBINPUTXBAR out4 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT5", displayName: "Trip source is CLBINPUTXBAR out5 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT6", displayName: "Trip source is CLBINPUTXBAR out6 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT7", displayName: "Trip source is CLBINPUTXBAR out7 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT8", displayName: "Trip source is CLBINPUTXBAR out8 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT9", displayName: "Trip source is CLBINPUTXBAR out9 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT10", displayName: "Trip source is CLBINPUTXBAR out10 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT11", displayName: "Trip source is CLBINPUTXBAR out11 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT12", displayName: "Trip source is CLBINPUTXBAR out12 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT13", displayName: "Trip source is CLBINPUTXBAR out13 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT14", displayName: "Trip source is CLBINPUTXBAR out14 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT15", displayName: "Trip source is CLBINPUTXBAR out15 signal" },
	{ name: "EPWM_DE_TRIPL_SRC_CLBINPUTXBAR_OUT16", displayName: "Trip source is CLBINPUTXBAR out16 signal" },
]
let EPWM_DiodeEmulationTripHSource = [
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH1", displayName: "Trip source is CMPSSTRIPH1 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH2", displayName: "Trip source is CMPSSTRIPH2 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH3", displayName: "Trip source is CMPSSTRIPH3 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH4", displayName: "Trip source is CMPSSTRIPH4 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH5", displayName: "Trip source is CMPSSTRIPH5 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH6", displayName: "Trip source is CMPSSTRIPH6 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH7", displayName: "Trip source is CMPSSTRIPH7 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH8", displayName: "Trip source is CMPSSTRIPH8 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH9", displayName: "Trip source is CMPSSTRIPH9 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH10", displayName: "Trip source is CMPSSTRIPH10 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CMPSSTRIPH11", displayName: "Trip source is CMPSSTRIPH11 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT1", displayName: "Trip source is INPUTXBAR out1 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT2", displayName: "Trip source is INPUTXBAR out2 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT3", displayName: "Trip source is INPUTXBAR out3 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT4", displayName: "Trip source is INPUTXBAR out4 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT5", displayName: "Trip source is INPUTXBAR out5 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT6", displayName: "Trip source is INPUTXBAR out6 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT7", displayName: "Trip source is INPUTXBAR out7 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT8", displayName: "Trip source is INPUTXBAR out8 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT9", displayName: "Trip source is INPUTXBAR out9 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT10", displayName: "Trip source is INPUTXBAR out10 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT11", displayName: "Trip source is INPUTXBAR out11 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT12", displayName: "Trip source is INPUTXBAR out12 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT13", displayName: "Trip source is INPUTXBAR out13 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT14", displayName: "Trip source is INPUTXBAR out14 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT15", displayName: "Trip source is INPUTXBAR out15 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_INPUTXBAR_OUT16", displayName: "Trip source is INPUTXBAR out16 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT1", displayName: "Trip source is CLBINPUTXBAR out1 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT2", displayName: "Trip source is CLBINPUTXBAR out2 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT3", displayName: "Trip source is CLBINPUTXBAR out3 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT4", displayName: "Trip source is CLBINPUTXBAR out4 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT5", displayName: "Trip source is CLBINPUTXBAR out5 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT6", displayName: "Trip source is CLBINPUTXBAR out6 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT7", displayName: "Trip source is CLBINPUTXBAR out7 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT8", displayName: "Trip source is CLBINPUTXBAR out8 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT9", displayName: "Trip source is CLBINPUTXBAR out9 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT10", displayName: "Trip source is CLBINPUTXBAR out10 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT11", displayName: "Trip source is CLBINPUTXBAR out11 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT12", displayName: "Trip source is CLBINPUTXBAR out12 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT13", displayName: "Trip source is CLBINPUTXBAR out13 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT14", displayName: "Trip source is CLBINPUTXBAR out14 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT15", displayName: "Trip source is CLBINPUTXBAR out15 signal" },
	{ name: "EPWM_DE_TRIPH_SRC_CLBINPUTXBAR_OUT16", displayName: "Trip source is CLBINPUTXBAR out16 signal" },
]
let EPWM_DiodeEmulationSignal = [
	{ name: "EPWM_DE_SYNC_TRIPHorL", displayName: "Synchronized version of TRIPH or TRIPL signal" },
	{ name: "EPWM_DE_SYNC_INV_TRIPHorL", displayName: "Synchronized and inverted version of TRIPH or TRIPL signal" },
	{ name: "EPWM_DE_LOW", displayName: "A constant low signal" },
	{ name: "EPWM_DE_HIGH", displayName: "A constant high signal" },
]
let EPWM_CycleByCycleTripZoneClearMode = [
	{ name: "EPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO", displayName: "Clear CBC pulse when counter equals zero" },
	{ name: "EPWM_TZ_CBC_PULSE_CLR_CNTR_PERIOD", displayName: "Clear CBC pulse when counter equals period" },
	{ name: "EPWM_TZ_CBC_PULSE_CLR_CNTR_ZERO_PERIOD", displayName: "Clear CBC pulse when counter equals zero or period" },
]
let EPWM_selectTripOutSource = [
	{ name: "EPWM_TZ_TRIPOUT_OST", displayName: "OST as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_CBC", displayName: "CBC as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_TZ1", displayName: "TZ1 as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_TZ2", displayName: "TZ2 as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_TZ3", displayName: "TZ3 as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_TZ4", displayName: "TZ4 as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_TZ5", displayName: "TZ5 as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_TZ6", displayName: "TZ6 as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_DCAEVT1", displayName: "DCAEVT1 as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_DCAEVT2", displayName: "DCAEVT2 as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_DCBEVT1", displayName: "DCBEVT1 as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_DCBEVT2", displayName: "DCBEVT2 as TRIPOUT source" },
	{ name: "EPWM_TZ_TRIPOUT_CAPEVT", displayName: "Capture Event as TRIPOUT source" },
]
let EPWM_ADCStartOfConversionType = [
	{ name: "EPWM_SOC_A", displayName: "SOC A" },
	{ name: "EPWM_SOC_B", displayName: "SOC B" },
]
let EPWM_ADCStartOfConversionSource = [
	{ name: "EPWM_SOC_DCxEVT1", displayName: "Event is based on DCxEVT1" },
	{ name: "EPWM_SOC_TBCTR_ZERO", displayName: "Time-base counter equal to zero" },
	{ name: "EPWM_SOC_TBCTR_PERIOD", displayName: "Time-base counter equal to period" },
	{ name: "EPWM_SOC_TBCTR_ETSOCAMIX", displayName: "Time-base counter based on mixed events (ETSOCAMIX)" },
	{ name: "EPWM_SOC_TBCTR_U_CMPA", displayName: "Time-base counter equal to CMPA when the timer is incrementing" },
	{ name: "EPWM_SOC_TBCTR_U_CMPC", displayName: "Time-base counter equal to CMPC when the timer is incrementing" },
	{ name: "EPWM_SOC_TBCTR_D_CMPA", displayName: "Time-base counter equal to CMPA when the timer is decrementing" },
	{ name: "EPWM_SOC_TBCTR_D_CMPC", displayName: "Time-base counter equal to CMPC when the timer is decrementing" },
	{ name: "EPWM_SOC_TBCTR_U_CMPB", displayName: "Time-base counter equal to CMPB when the timer is incrementing" },
	{ name: "EPWM_SOC_TBCTR_U_CMPD", displayName: "Time-base counter equal to CMPD when the timer is incrementing" },
	{ name: "EPWM_SOC_TBCTR_D_CMPB", displayName: "Time-base counter equal to CMPB when the timer is decrementing" },
	{ name: "EPWM_SOC_TBCTR_D_CMPD", displayName: "Time-base counter equal to CMPD when the timer is decrementing" },
]
let EPWM_DigitalCompareType = [
	{ name: "EPWM_DC_TYPE_DCAH", displayName: "Digital Compare A High" },
	{ name: "EPWM_DC_TYPE_DCAL", displayName: "Digital Compare A Low" },
	{ name: "EPWM_DC_TYPE_DCBH", displayName: "Digital Compare B High" },
	{ name: "EPWM_DC_TYPE_DCBL", displayName: "Digital Compare B Low" },
]
let EPWM_DigitalCompareTripInput = [
	{ name: "EPWM_DC_TRIP_TRIPIN1", displayName: "Trip 1" },
	{ name: "EPWM_DC_TRIP_TRIPIN2", displayName: "Trip 2" },
	{ name: "EPWM_DC_TRIP_TRIPIN3", displayName: "Trip 3" },
	{ name: "EPWM_DC_TRIP_TRIPIN4", displayName: "Trip 4" },
	{ name: "EPWM_DC_TRIP_TRIPIN5", displayName: "Trip 5" },
	{ name: "EPWM_DC_TRIP_TRIPIN6", displayName: "Trip 6" },
	{ name: "EPWM_DC_TRIP_TRIPIN7", displayName: "Trip 7" },
	{ name: "EPWM_DC_TRIP_TRIPIN8", displayName: "Trip 8" },
	{ name: "EPWM_DC_TRIP_TRIPIN9", displayName: "Trip 9" },
	{ name: "EPWM_DC_TRIP_TRIPIN10", displayName: "Trip 10" },
	{ name: "EPWM_DC_TRIP_TRIPIN11", displayName: "Trip 11" },
	{ name: "EPWM_DC_TRIP_TRIPIN12", displayName: "Trip 12" },
	{ name: "EPWM_DC_TRIP_TRIPIN14", displayName: "Trip 14" },
	{ name: "EPWM_DC_TRIP_TRIPIN15", displayName: "Trip 15" },
	{ name: "EPWM_DC_TRIP_COMBINATION", displayName: "All Trips (Trip1 - Trip 15) are selected" },
]
let EPWM_DigitalCompareBlankingPulse = [
	{ name: "EPWM_DC_WINDOW_START_TBCTR_PERIOD", displayName: "Time base counter equals period" },
	{ name: "EPWM_DC_WINDOW_START_TBCTR_ZERO", displayName: "Time base counter equals zero" },
	{ name: "EPWM_DC_WINDOW_START_TBCTR_ZERO_PERIOD", displayName: "Time base counter equals zero or period" },
	{ name: "EPWM_DC_WINDOW_START_BLANK_PULSE_MIX", displayName: "Blank pulse mix" },
]
let EPWM_DigitalCompareFilterInput = [
	{ name: "EPWM_DC_WINDOW_SOURCE_DCAEVT1", displayName: "DC filter signal source is DCAEVT1" },
	{ name: "EPWM_DC_WINDOW_SOURCE_DCAEVT2", displayName: "DC filter signal source is DCAEVT2" },
	{ name: "EPWM_DC_WINDOW_SOURCE_DCBEVT1", displayName: "DC filter signal source is DCBEVT1" },
	{ name: "EPWM_DC_WINDOW_SOURCE_DCBEVT2", displayName: "DC filter signal source is DCBEVT2" },
]
let EPWM_DigitalCompareModule = [
	{ name: "EPWM_DC_MODULE_A", displayName: "Digital Compare Module A" },
	{ name: "EPWM_DC_MODULE_B", displayName: "Digital Compare Module B" },
]
let EPWM_DigitalCompareEvent = [
	{ name: "EPWM_DC_EVENT_1", displayName: "Digital Compare Event number 1" },
	{ name: "EPWM_DC_EVENT_2", displayName: "Digital Compare Event number 2" },
]
let EPWM_DigitalCompareEventSource = [
	{ name: "EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL", displayName: "Signal source is unfiltered (DCAEVT1/2)" },
	{ name: "EPWM_DC_EVENT_SOURCE_FILT_SIGNAL", displayName: "Signal source is filtered (DCEVTFILT)" },
]
let EPWM_DigitalCompareSyncMode = [
	{ name: "EPWM_DC_EVENT_INPUT_SYNCED", displayName: "DC input signal is synced with TBCLK" },
	{ name: "EPWM_DC_EVENT_INPUT_NOT_SYNCED", displayName: "DC input signal is not synced with TBCLK" },
]
let EPWM_DigitalCompareCBCLatchMode = [
	{ name: "EPWM_DC_CBC_LATCH_DISABLED", displayName: "DC cycle-by-cycle(CBC) latch is disabled" },
	{ name: "EPWM_DC_CBC_LATCH_ENABLED", displayName: "DC cycle-by-cycle(CBC) latch is enabled" },
]
let EPWM_DigitalCompareCBCLatchClearEvent = [
	{ name: "EPWM_DC_CBC_LATCH_CLR_CNTR_ZERO", displayName: "Clear CBC latch when counter equals zero" },
	{ name: "EPWM_DC_CBC_LATCH_CLR_ON_CNTR_PERIOD", displayName: "Clear CBC latch when counter equals period" },
	{ name: "EPWM_DC_CBC_LATCH_CLR_ON_CNTR_ZERO_PERIOD", displayName: "Clear CBC latch when counter equals zero or period" },
]
let EPWM_selectCaptureGateInputPolarity = [
	{ name: "EPWM_CAPGATE_INPUT_ALWAYS_ON", displayName: "Capture gate is always on" },
	{ name: "EPWM_CAPGATE_INPUT_ALWAYS_OFF", displayName: "Capture gate is always off" },
	{ name: "EPWM_CAPGATE_INPUT_SYNC", displayName: "Capture gate input is CAPGATE.sync" },
	{ name: "EPWM_CAPGATE_INPUT_SYNC_INVERT", displayName: "Capture gate input is CAPGATE.sync inverted" },
]
let EPWM_selectCaptureInputPolarity = [
	{ name: "EPWM_CAPTURE_INPUT_CAPIN_SYNC", displayName: "Capture input is not inverted" },
	{ name: "EPWM_CAPTURE_INPUT_CAPIN_SYNC_INVERT", displayName: "Capture input is inverted" },
]
let EPWM_CaptureInputType = [
	{ name: "EPWM_CAPTURE_GATE", displayName: "Capture Gate" },
	{ name: "EPWM_CAPTURE_INPUT", displayName: "Capture Input" },
]
let EPWM_GlobalLoadTrigger = [
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_ZERO", displayName: "Load when counter is equal to zero" },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_PERIOD", displayName: "Load when counter is equal to period" },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD", displayName: "Load when counter is equal to zero or period" },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC", displayName: "Load on sync event" },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_ZERO", displayName: "Load on sync event or when counter  is equal to zero" },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_PERIOD", displayName: "Load on sync event or when counter  is equal to period" },
	{ name: "EPWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD", displayName: "Load on sync event or when counter is equal to period or zero" },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_U_CMPC", displayName: "Load when counter is equal to CMPC while incrementing" },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_D_CMPC", displayName: "Load when counter is equal to CMPC while decrementing" },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_U_CMPD", displayName: "Load when counter is equal to CMPD while incrementing" },
	{ name: "EPWM_GL_LOAD_PULSE_CNTR_D_CMPD", displayName: "Load when counter is equal to CMPD while decrementing" },
	{ name: "EPWM_GL_LOAD_PULSE_GLOBAL_FORCE", displayName: "Load on global force" },
]
let EPWM_ValleyTriggerSource = [
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_SOFTWARE", displayName: "Valley capture trigged by software" },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_CNTR_ZERO", displayName: "Valley capture trigged by when counter is equal to zero" },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_CNTR_PERIOD", displayName: "Valley capture trigged by when counter is equal period" },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_CNTR_ZERO_PERIOD", displayName: "Valley capture trigged when counter is equal to zero or period" },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_DCAEVT1", displayName: "Valley capture trigged by DCAEVT1 (Digital Compare A event 1)" },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_DCAEVT2", displayName: "Valley capture trigged by DCAEVT2 (Digital Compare A event 2)" },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_DCBEVT1", displayName: "Valley capture trigged by DCBEVT1 (Digital Compare B event 1)" },
	{ name: "EPWM_VALLEY_TRIGGER_EVENT_DCBEVT2", displayName: "Valley capture trigged by DCBEVT2 (Digital Compare B event 2)" },
]
let EPWM_ValleyCounterEdge = [
	{ name: "EPWM_VALLEY_COUNT_START_EDGE", displayName: "Valley count start edge" },
	{ name: "EPWM_VALLEY_COUNT_STOP_EDGE", displayName: "Valley count stop edge" },
]
let EPWM_ValleyDelayMode = [
	{ name: "EPWM_VALLEY_DELAY_MODE_SW_DELAY", displayName: "Delay value equals the offset value defines by software" },
	{ name: "EPWM_VALLEY_DELAY_MODE_VCNT_DELAY_SW_DELAY", displayName: "Delay value equals the sum of the Hardware counter value and the offset value defines by software" },
	{ name: "EPWM_VALLEY_DELAY_MODE_VCNT_DELAY_SHIFT_1_SW_DELAY", displayName: "Delay value equals the the Hardware counter shifted by (1 + the offset value defines by software)" },
	{ name: "EPWM_VALLEY_DELAY_MODE_VCNT_DELAY_SHIFT_2_SW_DELAY", displayName: "Delay value equals the the Hardware counter shifted by (2 + the offset value defines by software)" },
	{ name: "EPWM_VALLEY_DELAY_MODE_VCNT_DELAY_SHIFT_4_SW_DELAY", displayName: "Delay value equals the the Hardware counter shifted by (4 + the offset value defines by software)" },
]
let EPWM_DigitalCompareEdgeFilterMode = [
	{ name: "EPWM_DC_EDGEFILT_MODE_RISING", displayName: "Digital Compare Edge filter low" },
	{ name: "EPWM_DC_EDGEFILT_MODE_FALLING", displayName: "Digital Compare Edge filter high" },
	{ name: "EPWM_DC_EDGEFILT_MODE_BOTH", displayName: "Digital Compare Edge filter both" },
]
let EPWM_DigitalCompareEdgeFilterEdgeCount = [
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_0", displayName: "Digital Compare Edge filter edge" },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_1", displayName: "Digital Compare Edge filter edge" },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_2", displayName: "Digital Compare Edge filter edge" },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_3", displayName: "Digital Compare Edge filter edge" },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_4", displayName: "Digital Compare Edge filter edge" },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_5", displayName: "Digital Compare Edge filter edge" },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_6", displayName: "Digital Compare Edge filter edge" },
	{ name: "EPWM_DC_EDGEFILT_EDGECNT_7", displayName: "Digital Compare Edge filter edge" },
]
let EPWM_ETMixTriggerSource = [
	{ name: "EPWM_ETMIX_TBCTR_ZERO", displayName: "Time-base counter equal to zero" },
	{ name: "EPWM_ETMIX_TBCTR_PERIOD", displayName: "Time-base counter equal to period" },
	{ name: "EPWM_ETMIX_TBCTR_U_CMPA", displayName: "Time-base counter equal to CMPA when the timer is incrementing" },
	{ name: "EPWM_ETMIX_TBCTR_D_CMPA", displayName: "Time-base counter equal to CMPA when the timer is decrementing" },
	{ name: "EPWM_ETMIX_TBCTR_U_CMPB", displayName: "Time-base counter equal to CMPB when the timer is incrementing" },
	{ name: "EPWM_ETMIX_TBCTR_D_CMPB", displayName: "Time-base counter equal to CMPB when the timer is decrementing" },
	{ name: "EPWM_ETMIX_TBCTR_U_CMPC", displayName: "Time-base counter equal to CMPC when the timer is incrementing" },
	{ name: "EPWM_ETMIX_TBCTR_D_CMPC", displayName: "Time-base counter equal to CMPC when the timer is decrementing" },
	{ name: "EPWM_ETMIX_TBCTR_U_CMPD", displayName: "Time-base counter equal to CMPD when the timer is incrementing" },
	{ name: "EPWM_ETMIX_TBCTR_D_CMPD", displayName: "Time-base counter equal to CMPD when the timer is decrementing" },
	{ name: "EPWM_ETMIX_DCAEVT1", displayName: "Event is based on DCAEVT1" },
]
let EPWM_ETMixSignalSelect = [
	{ name: "EPWM_ETMIX_INTERRUPT", displayName: "Mixed ET Interrupt signal" },
	{ name: "EPWM_ETMIX_SOCA", displayName: "Mixed ET SOCA signal" },
	{ name: "EPWM_ETMIX_SOCB", displayName: "Mixed ET SOCB signal" },
]
let EPWM_LockRegisterGroup = [
	{ name: "EPWM_REGISTER_GROUP_GLOBAL_LOAD", displayName: "Global load register group" },
	{ name: "EPWM_REGISTER_GROUP_TRIP_ZONE", displayName: "Trip zone register group" },
	{ name: "EPWM_REGISTER_GROUP_TRIP_ZONE_CLEAR", displayName: "Trip zone clear group" },
	{ name: "EPWM_REGISTER_GROUP_DIGITAL_COMPARE", displayName: "Digital compare group" },
]
let EPWM_O = [
	{ name: "EPWM_O_XCMP", displayName: "O XCMP" },
	{ name: "EPWM_O_DE", displayName: "O DE" },
	{ name: "EPWM_O_MINDB", displayName: "O MINDB" },
]
let EPWM_SYNC_OUT_SOURCE_M = [
	{ name: "EPWM_SYNC_OUT_SOURCE_M", displayName: "SYNC OUT SOURCE M" },
]
let EPWM_SYNC_OUT_PULSE_ON = [
	{ name: "EPWM_SYNC_OUT_PULSE_ON_SOFTWARE", displayName: "Software force generated EPWM sync-out pulse" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO", displayName: "Counter zero event generates EPWM sync-out pulse" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_B", displayName: "Counter equal to CMPB event generates EPWM sync-out pulse" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_C", displayName: "Counter equal to CMPC event generates EPWM sync-out pulse" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_D", displayName: "Counter equal to CMPD event generates EPWM sync-out pulse" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_DCA_EVT1_SYNC", displayName: "DCA Event 1 Sync signal generates EPWM sync-out pulse" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_DCB_EVT1_SYNC", displayName: "DCB Event 1 Sync signal generates EPWM sync-out pulse" },
	{ name: "EPWM_SYNC_OUT_PULSE_ON_ALL", displayName: "Enable all the above sources" },
]
let EPWM_TIME_BASE_STATUS_COUNT = [
	{ name: "EPWM_TIME_BASE_STATUS_COUNT_UP", displayName: "Time base counter is counting up" },
	{ name: "EPWM_TIME_BASE_STATUS_COUNT_DOWN", displayName: "Time base counter is counting down" },
]
let EPWM_DB_INPUT = [
	{ name: "EPWM_DB_INPUT_EPWMA", displayName: "Input signal is ePWMA" },
	{ name: "EPWM_DB_INPUT_EPWMB", displayName: "Input signal is ePWMB" },
	{ name: "EPWM_DB_INPUT_DB_RED", displayName: "Input signal is the output of Rising Edge delay" },
]
let EPWM_TZ_SIGNAL = [
	{ name: "EPWM_TZ_SIGNAL_CBC1", displayName: "TZ1 Cycle By Cycle" },
	{ name: "EPWM_TZ_SIGNAL_CBC2", displayName: "TZ2 Cycle By Cycle" },
	{ name: "EPWM_TZ_SIGNAL_CBC3", displayName: "TZ3 Cycle By Cycle" },
	{ name: "EPWM_TZ_SIGNAL_CBC4", displayName: "TZ4 Cycle By Cycle" },
	{ name: "EPWM_TZ_SIGNAL_CBC5", displayName: "TZ5 Cycle By Cycle" },
	{ name: "EPWM_TZ_SIGNAL_CBC6", displayName: "TZ6 Cycle By Cycle" },
	{ name: "EPWM_TZ_SIGNAL_DCAEVT2", displayName: "DCAEVT2 Cycle By Cycle" },
	{ name: "EPWM_TZ_SIGNAL_DCBEVT2", displayName: "DCBEVT2 Cycle By Cycle" },
	{ name: "EPWM_TZ_SIGNAL_OSHT1", displayName: "One-shot TZ1" },
	{ name: "EPWM_TZ_SIGNAL_OSHT2", displayName: "One-shot TZ2" },
	{ name: "EPWM_TZ_SIGNAL_OSHT3", displayName: "One-shot TZ3" },
	{ name: "EPWM_TZ_SIGNAL_OSHT4", displayName: "One-shot TZ4" },
	{ name: "EPWM_TZ_SIGNAL_OSHT5", displayName: "One-shot TZ5" },
	{ name: "EPWM_TZ_SIGNAL_OSHT6", displayName: "One-shot TZ6" },
	{ name: "EPWM_TZ_SIGNAL_DCAEVT1", displayName: "One-shot DCAEVT1" },
	{ name: "EPWM_TZ_SIGNAL_DCBEVT1", displayName: "One-shot DCBEVT1" },
]
let EPWM_TZ_SIGNAL_CAPEVT = [
	{ name: "EPWM_TZ_SIGNAL_CAPEVT_CBC", displayName: "Cycle by cycle capture event" },
	{ name: "EPWM_TZ_SIGNAL_CAPEVT_OST", displayName: "One-shot Capture event" },
]
let EPWM_XCMP = [
	{ name: "EPWM_XCMP_ACTIVE", displayName: "XCMP set = Active" },
	{ name: "EPWM_XCMP_SHADOW1", displayName: "XCMP set = Shadow 1" },
	{ name: "EPWM_XCMP_SHADOW2", displayName: "XCMP set = Shadow 2" },
	{ name: "EPWM_XCMP_SHADOW3", displayName: "XCMP set = Shadow 3" },
]
let EPWM_MINDB_BLOCK = [
	{ name: "EPWM_MINDB_BLOCK_A", displayName: "Minimum Dead Band Block A" },
	{ name: "EPWM_MINDB_BLOCK_B", displayName: "Minimum Dead Band Block B" },
]
let EPWM_MINDB_REF = [
	{ name: "EPWM_MINDB_REF_SIG", displayName: "Minimum Dead Band don't invert reference signal" },
	{ name: "EPWM_MINDB_REF_SIG_INVERT", displayName: "Minimum Dead invert reference signal" },
]
let EPWM_MINDB_POLSEL = [
	{ name: "EPWM_MINDB_POLSEL_INVERT_LOGICAL_AND", displayName: "Minimum Dead Band Invert and perform logical AND" },
	{ name: "EPWM_MINDB_POLSEL_LOGICAL_OR", displayName: "Minimum Dead Band Block perform logical OR" },
]
let EPWM_MINDB_BLOCKING_SIGNAL = [
	{ name: "EPWM_MINDB_BLOCKING_SIGNAL_BYPASS", displayName: "Minimum Dead Band keep blocking signal" },
	{ name: "EPWM_MINDB_BLOCKING_SIGNAL_SWAPBLOCK", displayName: "Minimum Dead Band swap blocking signal" },
]
let EPWM_MINDB_SEL = [
	{ name: "EPWM_MINDB_SEL_DEPWM", displayName: "Minimum Dead Band Reference signal" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT1", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 1" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT2", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 2" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT3", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 3" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT4", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 4" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT5", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 5" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT6", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 6" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT7", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 7" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT8", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 8" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT9", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 9" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT10", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 10" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT11", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 11" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT12", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 12" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT13", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 13" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT14", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 14" },
	{ name: "EPWM_MINDB_SEL_OUTXBAR_OUT15", displayName: "Minimum Dead Band Reference Signal PWM Output Xbar 15" },
]
let EPWM_MINDB_ICL_XBAR = [
	{ name: "EPWM_MINDB_ICL_XBAR_OUT1", displayName: "ICL Xbar Out 1" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT2", displayName: "ICL Xbar Out 2" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT3", displayName: "ICL Xbar Out 3" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT4", displayName: "ICL Xbar Out 4" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT5", displayName: "ICL Xbar Out 5" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT6", displayName: "ICL Xbar Out 6" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT7", displayName: "ICL Xbar Out 7" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT8", displayName: "ICL Xbar Out 8" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT9", displayName: "ICL Xbar Out 9" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT10", displayName: "ICL Xbar Out 10" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT11", displayName: "ICL Xbar Out 11" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT12", displayName: "ICL Xbar Out 12" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT13", displayName: "ICL Xbar Out 13" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT14", displayName: "ICL Xbar Out 14" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT15", displayName: "ICL Xbar Out 15" },
	{ name: "EPWM_MINDB_ICL_XBAR_OUT16", displayName: "ICL Xbar Out 16" },
]
let EPWM_MINDB_ICL_LUT = [
	{ name: "EPWM_MINDB_ICL_LUT_DEC0", displayName: "LUT output PWMA/B value on decoding 0" },
	{ name: "EPWM_MINDB_ICL_LUT_DEC1", displayName: "LUT output PWMA/B value on decoding 1" },
	{ name: "EPWM_MINDB_ICL_LUT_DEC2", displayName: "LUT output PWMA/B value on decoding 2" },
	{ name: "EPWM_MINDB_ICL_LUT_DEC3", displayName: "LUT output PWMA/B value on decoding 3" },
	{ name: "EPWM_MINDB_ICL_LUT_DEC4", displayName: "LUT output PWMA/B value on decoding 4" },
	{ name: "EPWM_MINDB_ICL_LUT_DEC5", displayName: "LUT output PWMA/B value on decoding 5" },
	{ name: "EPWM_MINDB_ICL_LUT_DEC6", displayName: "LUT output PWMA/B value on decoding 6" },
	{ name: "EPWM_MINDB_ICL_LUT_DEC7", displayName: "LUT output PWMA/B value on decoding 7" },
]
let EPWM_DE_SRC = [
	{ name: "EPWM_DE_SRC_TRIPL", displayName: "Diode emulation Trip L" },
	{ name: "EPWM_DE_SRC_TRIPH", displayName: "Diode emulation Trip H" },
]
let EPWM_DE_CHANNEL = [
	{ name: "EPWM_DE_CHANNEL_A", displayName: "Diode emulation channel A" },
	{ name: "EPWM_DE_CHANNEL_B", displayName: "Diode emulation channel B" },
]
let EPWM_DE_COUNT = [
	{ name: "EPWM_DE_COUNT_UP", displayName: "Diode emulation count up step size" },
	{ name: "EPWM_DE_COUNT_DOWN", displayName: "Diode emulation count down step size" },
]
let EPWM_TZ_INTERRUPT = [
	{ name: "EPWM_TZ_INTERRUPT_CBC", displayName: "Trip Zones Cycle By Cycle interrupt" },
	{ name: "EPWM_TZ_INTERRUPT_OST", displayName: "Trip Zones One Shot interrupt" },
	{ name: "EPWM_TZ_INTERRUPT_DCAEVT1", displayName: "Digital Compare A Event 1 interrupt" },
	{ name: "EPWM_TZ_INTERRUPT_DCAEVT2", displayName: "Digital Compare A Event 2 interrupt" },
	{ name: "EPWM_TZ_INTERRUPT_DCBEVT1", displayName: "Digital Compare B Event 1 interrupt" },
	{ name: "EPWM_TZ_INTERRUPT_DCBEVT2", displayName: "Digital Compare B Event 2 interrupt" },
	{ name: "EPWM_TZ_INTERRUPT_CAPEVT", displayName: "Trip Zones Capture Event interrupt" },
]
let EPWM_TZ_FLAG = [
	{ name: "EPWM_TZ_FLAG_CBC", displayName: "Trip Zones Cycle By Cycle flag" },
	{ name: "EPWM_TZ_FLAG_OST", displayName: "Trip Zones One Shot flag" },
	{ name: "EPWM_TZ_FLAG_DCAEVT1", displayName: "Digital Compare A Event 1 flag" },
	{ name: "EPWM_TZ_FLAG_DCAEVT2", displayName: "Digital Compare A Event 2 flag" },
	{ name: "EPWM_TZ_FLAG_DCBEVT1", displayName: "Digital Compare B Event 1 flag" },
	{ name: "EPWM_TZ_FLAG_DCBEVT2", displayName: "Digital Compare B Event 2 flag" },
	{ name: "EPWM_TZ_FLAG_CAPEVT", displayName: "Trip Zones Capture Event flag" },
]
let EPWM_TZ_CBC_FLAG = [
	{ name: "EPWM_TZ_CBC_FLAG_1", displayName: "CBC flag 1" },
	{ name: "EPWM_TZ_CBC_FLAG_2", displayName: "CBC flag 2" },
	{ name: "EPWM_TZ_CBC_FLAG_3", displayName: "CBC flag 3" },
	{ name: "EPWM_TZ_CBC_FLAG_4", displayName: "CBC flag 4" },
	{ name: "EPWM_TZ_CBC_FLAG_5", displayName: "CBC flag 5" },
	{ name: "EPWM_TZ_CBC_FLAG_6", displayName: "CBC flag 6" },
	{ name: "EPWM_TZ_CBC_FLAG_DCAEVT2", displayName: "CBC flag Digital compare event A2" },
	{ name: "EPWM_TZ_CBC_FLAG_DCBEVT2", displayName: "CBC flag Digital compare event B2" },
	{ name: "EPWM_TZ_CBC_FLAG_CAPEVT", displayName: "CBC flag capture event" },
]
let EPWM_TZ_OST_FLAG = [
	{ name: "EPWM_TZ_OST_FLAG_OST1", displayName: "OST flag OST1" },
	{ name: "EPWM_TZ_OST_FLAG_OST2", displayName: "OST flag OST2" },
	{ name: "EPWM_TZ_OST_FLAG_OST3", displayName: "OST flag OST3" },
	{ name: "EPWM_TZ_OST_FLAG_OST4", displayName: "OST flag OST4" },
	{ name: "EPWM_TZ_OST_FLAG_OST5", displayName: "OST flag OST5" },
	{ name: "EPWM_TZ_OST_FLAG_OST6", displayName: "OST flag OST6" },
	{ name: "EPWM_TZ_OST_FLAG_DCAEVT1", displayName: "OST flag Digital compare event A1" },
	{ name: "EPWM_TZ_OST_FLAG_DCBEVT1", displayName: "OST flag Digital compare event B1" },
	{ name: "EPWM_TZ_OST_FLAG_CAPEVT", displayName: "OST flag capture event" },
]
let EPWM_TZ_FORCE_EVENT = [
	{ name: "EPWM_TZ_FORCE_EVENT_CBC", displayName: "Force Cycle By Cycle trip event" },
	{ name: "EPWM_TZ_FORCE_EVENT_OST", displayName: "Force a One-Shot Trip Event" },
	{ name: "EPWM_TZ_FORCE_EVENT_DCAEVT1", displayName: "Force Digital Compare Output A Event 1" },
	{ name: "EPWM_TZ_FORCE_EVENT_DCAEVT2", displayName: "Force Digital Compare Output A Event 2" },
	{ name: "EPWM_TZ_FORCE_EVENT_DCBEVT1", displayName: "Force Digital Compare Output B Event 1" },
	{ name: "EPWM_TZ_FORCE_EVENT_DCBEVT2", displayName: "Force Digital Compare Output B Event 2" },
	{ name: "EPWM_TZ_FORCE_EVENT_CAPEVT", displayName: "Force a Capture Event" },
]
let EPWM_INT_TBCTR = [
	{ name: "EPWM_INT_TBCTR_DISABLED", displayName: "Time-base counter is disabled" },
	{ name: "EPWM_INT_TBCTR_ZERO", displayName: "Time-base counter equal to zero" },
	{ name: "EPWM_INT_TBCTR_PERIOD", displayName: "Time-base counter equal to period" },
	{ name: "EPWM_INT_TBCTR_ETINTMIX", displayName: "Time-base counter based on mixed events (ETINTMIX)" },
	{ name: "EPWM_INT_TBCTR_U_CMPA", displayName: "time-base counter equal to CMPA when the timer is incrementing" },
	{ name: "EPWM_INT_TBCTR_U_CMPC", displayName: "time-base counter equal to CMPC when the timer is incrementing" },
	{ name: "EPWM_INT_TBCTR_D_CMPA", displayName: "time-base counter equal to CMPA when the timer is decrementing" },
	{ name: "EPWM_INT_TBCTR_D_CMPC", displayName: "time-base counter equal to CMPC when the timer is decrementing" },
	{ name: "EPWM_INT_TBCTR_U_CMPB", displayName: "time-base counter equal to CMPB when the timer is incrementing" },
	{ name: "EPWM_INT_TBCTR_U_CMPD", displayName: "time-base counter equal to CMPD when the timer is incrementing" },
	{ name: "EPWM_INT_TBCTR_D_CMPB", displayName: "time-base counter equal to CMPB when the timer is decrementing" },
	{ name: "EPWM_INT_TBCTR_D_CMPD", displayName: "time-base counter equal to CMPD when the timer is decrementing" },
]
let EPWM_DC_COMBINATIONAL = [
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN1", displayName: "Combinational Trip 1 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN2", displayName: "Combinational Trip 2 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN3", displayName: "Combinational Trip 3 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN4", displayName: "Combinational Trip 4 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN5", displayName: "Combinational Trip 5 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN6", displayName: "Combinational Trip 6 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN7", displayName: "Combinational Trip 7 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN8", displayName: "Combinational Trip 8 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN9", displayName: "Combinational Trip 9 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN10", displayName: "Combinational Trip 10 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN11", displayName: "Combinational Trip 11 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN12", displayName: "Combinational Trip 12 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN14", displayName: "Combinational Trip 14 input" },
	{ name: "EPWM_DC_COMBINATIONAL_TRIPIN15", displayName: "Combinational Trip 15 input" },
]
let EPWM_GL_REGISTER = [
	{ name: "EPWM_GL_REGISTER_TBPRD_TBPRDHR", displayName: "Global load TBPRD:TBPRDHR" },
	{ name: "EPWM_GL_REGISTER_CMPA_CMPAHR", displayName: "Global load CMPA:CMPAHR" },
	{ name: "EPWM_GL_REGISTER_CMPB_CMPBHR", displayName: "Global load CMPB:CMPBHR" },
	{ name: "EPWM_GL_REGISTER_CMPC", displayName: "Global load CMPC" },
	{ name: "EPWM_GL_REGISTER_CMPD", displayName: "Global load CMPD" },
	{ name: "EPWM_GL_REGISTER_DBRED_DBREDHR", displayName: "Global load DBRED:DBREDHR" },
	{ name: "EPWM_GL_REGISTER_DBFED_DBFEDHR", displayName: "Global load DBFED:DBFEDHR" },
	{ name: "EPWM_GL_REGISTER_DBCTL", displayName: "Global load DBCTL" },
	{ name: "EPWM_GL_REGISTER_AQCTLA_AQCTLA2", displayName: "Global load AQCTLA/A2" },
	{ name: "EPWM_GL_REGISTER_AQCTLB_AQCTLB2", displayName: "Global load AQCTLB/B2" },
	{ name: "EPWM_GL_REGISTER_AQCSFRC", displayName: "Global load AQCSFRC" },
]
let EPWM_setSyncPulseSource = [
	{ name: "EPWM_setSyncPulseSource", displayName: "SETSYNCPULSESOURCE" },
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
	EPWM_TZ_SIGNAL_CAPEVT: EPWM_TZ_SIGNAL_CAPEVT,
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
