let CPUTimer_EmulationMode = [
	{ name: "CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT", displayName: "Denotes that the timer will stop after the next decrement" },
	{ name: "CPUTIMER_EMULATIONMODE_STOPATZERO", displayName: "Denotes that the timer will stop when it reaches zero" },
	{ name: "CPUTIMER_EMULATIONMODE_RUNFREE", displayName: "Denotes that the timer will run free" },
]
let CPUTimer_ClockSource = [
	{ name: "CPUTIMER_CLOCK_SOURCE_SYS", displayName: "System Clock Source" },
	{ name: "CPUTIMER_CLOCK_SOURCE_WROSCDIV8", displayName: "WROSC (Wide Range Oscillator) output clock after the fixed BY8 divider" },
	{ name: "CPUTIMER_CLOCK_SOURCE_SYSOSCDIV4", displayName: "SYSOSC output clock after the fixed BY4 divider" },
	{ name: "CPUTIMER_CLOCK_SOURCE_XTAL", displayName: "CLOCK SOURCE XTAL" },
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
