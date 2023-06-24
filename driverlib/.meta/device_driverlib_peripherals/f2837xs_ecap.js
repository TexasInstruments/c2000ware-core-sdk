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
	ECAP_MAX_PRESCALER_VALUE: ECAP_MAX_PRESCALER_VALUE,
	ECAP_ISR_SOURCE: ECAP_ISR_SOURCE,
}
