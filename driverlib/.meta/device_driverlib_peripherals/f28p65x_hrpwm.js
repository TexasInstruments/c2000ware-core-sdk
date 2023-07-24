let HRPWM_Channel = [
	{ name: "HRPWM_CHANNEL_A", displayName: "HRPWM A" },
	{ name: "HRPWM_CHANNEL_B", displayName: "HRPWM B" },
]
let HRPWM_MEPEdgeMode = [
	{ name: "HRPWM_MEP_CTRL_DISABLE", displayName: "HRPWM is disabled" },
	{ name: "HRPWM_MEP_CTRL_RISING_EDGE", displayName: "MEP controls rising edge" },
	{ name: "HRPWM_MEP_CTRL_FALLING_EDGE", displayName: "MEP controls falling edge" },
	{ name: "HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE", displayName: "MEP controls both rising and falling edge" },
]
let HRPWM_MEPCtrlMode = [
	{ name: "HRPWM_MEP_DUTY_PERIOD_CTRL", displayName: "CMPAHR/CMPBHR or TBPRDHR controls MEP edge" },
	{ name: "HRPWM_MEP_PHASE_CTRL", displayName: "TBPHSHR controls MEP edge" },
]
let HRPWM_LoadMode = [
	{ name: "HRPWM_LOAD_ON_CNTR_ZERO", displayName: "load when counter equals zero" },
	{ name: "HRPWM_LOAD_ON_CNTR_PERIOD", displayName: "load when counter equals period" },
	{ name: "HRPWM_LOAD_ON_CNTR_ZERO_PERIOD", displayName: "load when counter equals zero or period" },
	{ name: "HRPWM_LOAD_ON_CMPx_EQ", displayName: "load on translator event CMPA/B-3" },
]
let HRPWM_ChannelBOutput = [
	{ name: "HRPWM_OUTPUT_ON_B_NORMAL", displayName: "ePWMxB output is normal." },
	{ name: "HRPWM_OUTPUT_ON_B_INV_A", displayName: "ePWMxB output is inverted" },
]
let HRPWM_SyncPulseSource = [
	{ name: "HRPWM_PWMSYNC_SOURCE_PERIOD", displayName: "Counter equals Period" },
	{ name: "HRPWM_PWMSYNC_SOURCE_ZERO", displayName: "Counter equals zero" },
	{ name: "HRPWM_PWMSYNC_SOURCE_COMPC_UP", displayName: "Counter equals COMPC when counting up" },
	{ name: "HRPWM_PWMSYNC_SOURCE_COMPC_DOWN", displayName: "Counter equals COMPC when counting down" },
	{ name: "HRPWM_PWMSYNC_SOURCE_COMPD_UP", displayName: "Counter equals COMPD when counting up" },
	{ name: "HRPWM_PWMSYNC_SOURCE_COMPD_DOWN", displayName: "Counter equals COMPD when counting down" },
]
let HRPWM_CounterCompareModule = [
	{ name: "HRPWM_COUNTER_COMPARE_A", displayName: "counter compare A" },
	{ name: "HRPWM_COUNTER_COMPARE_B", displayName: "counter compare B" },
]
let HRPWM_MEPDeadBandEdgeMode = [
	{ name: "HRPWM_DB_MEP_CTRL_DISABLE", displayName: "HRPWM is disabled" },
	{ name: "HRPWM_DB_MEP_CTRL_RED", displayName: "MEP controls Rising Edge Delay" },
	{ name: "HRPWM_DB_MEP_CTRL_FED", displayName: "MEP controls Falling Edge Delay" },
	{ name: "HRPWM_DB_MEP_CTRL_RED_FED", displayName: "MEP controls both Falling and Rising edge delay" },
]
let HRPWM_LockRegisterGroup = [
	{ name: "HRPWM_REGISTER_GROUP_HRPWM", displayName: "HRPWM register group" },
	{ name: "HRPWM_REGISTER_GROUP_GLOBAL_LOAD", displayName: "Global load register group" },
	{ name: "HRPWM_REGISTER_GROUP_TRIP_ZONE", displayName: "Trip zone register group" },
	{ name: "HRPWM_REGISTER_GROUP_TRIP_ZONE_CLEAR", displayName: "Trip zone clear group" },
	{ name: "HRPWM_REGISTER_GROUP_DIGITAL_COMPARE", displayName: "Digital compare group" },
]
module.exports = {
	HRPWM_Channel: HRPWM_Channel,
	HRPWM_MEPEdgeMode: HRPWM_MEPEdgeMode,
	HRPWM_MEPCtrlMode: HRPWM_MEPCtrlMode,
	HRPWM_LoadMode: HRPWM_LoadMode,
	HRPWM_ChannelBOutput: HRPWM_ChannelBOutput,
	HRPWM_SyncPulseSource: HRPWM_SyncPulseSource,
	HRPWM_CounterCompareModule: HRPWM_CounterCompareModule,
	HRPWM_MEPDeadBandEdgeMode: HRPWM_MEPDeadBandEdgeMode,
	HRPWM_LockRegisterGroup: HRPWM_LockRegisterGroup,
}
