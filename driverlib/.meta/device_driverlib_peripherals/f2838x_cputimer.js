let CPUTimer_EmulationMode = [
	{ name: "CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT", displayName: "Denotes that the timer will stop after the next decrement" },
	{ name: "CPUTIMER_EMULATIONMODE_STOPATZERO", displayName: "Denotes that the timer will stop when it reaches zero" },
	{ name: "CPUTIMER_EMULATIONMODE_RUNFREE", displayName: "Denotes that the timer will run free" },
]
let CPUTimer_ClockSource = [
	{ name: "CPUTIMER_CLOCK_SOURCE_SYS", displayName: "System Clock Source" },
	{ name: "CPUTIMER_CLOCK_SOURCE_INTOSC1", displayName: "Internal Oscillator 1 Clock Source" },
	{ name: "CPUTIMER_CLOCK_SOURCE_INTOSC2", displayName: "Internal Oscillator 2 Clock Source" },
	{ name: "CPUTIMER_CLOCK_SOURCE_XTAL", displayName: "External Clock Source" },
	{ name: "CPUTIMER_CLOCK_SOURCE_AUX", displayName: "Auxiliary PLL Clock Source" },
]
let CPUTimer_Prescaler = [
	{ name: "CPUTIMER_CLOCK_PRESCALER_1", displayName: "Prescaler value of / 1" },
	{ name: "CPUTIMER_CLOCK_PRESCALER_2", displayName: "Prescaler value of / 2" },
	{ name: "CPUTIMER_CLOCK_PRESCALER_4", displayName: "Prescaler value of / 4" },
	{ name: "CPUTIMER_CLOCK_PRESCALER_8", displayName: "Prescaler value of / 8" },
	{ name: "CPUTIMER_CLOCK_PRESCALER_16", displayName: "Prescaler value of / 16" },
]
module.exports = {
	CPUTimer_EmulationMode: CPUTimer_EmulationMode,
	CPUTimer_ClockSource: CPUTimer_ClockSource,
	CPUTimer_Prescaler: CPUTimer_Prescaler,
}
