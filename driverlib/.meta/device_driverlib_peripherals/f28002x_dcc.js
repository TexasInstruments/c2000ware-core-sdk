let DCC_SingleShotMode = [
	{ name: "DCC_MODE_COUNTER_ZERO", displayName: "Use to stop counting when counter0 and valid0 both reach zero" },
	{ name: "DCC_MODE_COUNTER_ONE", displayName: "Use to stop counting when counter1 reaches zero" },
]
let DCC_Count1ClockSource = [
	{ name: "DCC_COUNT1SRC_PLL", displayName: "PLLRAWCLK Clock Out Source" },
	{ name: "DCC_COUNT1SRC_INTOSC1", displayName: "Internal Oscillator1 Clock Source" },
	{ name: "DCC_COUNT1SRC_INTOSC2", displayName: "Internal Oscillator2 Clock Source" },
	{ name: "DCC_COUNT1SRC_SYSCLK", displayName: "SYSCLK (System Clock) Source" },
	{ name: "DCC_COUNT1SRC_AUXCLKIN", displayName: "AUXCLKIN (Auxiliary Clock) Source" },
	{ name: "DCC_COUNT1SRC_EPWM", displayName: "EPWM Clock Source" },
	{ name: "DCC_COUNT1SRC_ADCCLK", displayName: "ADC Clock Source" },
	{ name: "DCC_COUNT1SRC_WDCLK", displayName: "Watch Dog Clock Source" },
	{ name: "DCC_COUNT1SRC_CANX", displayName: "CANxBIT Clock Source" },
	{ name: "DCC_COUNT1SRC_SYSAPLL_CLK_AUX", displayName: "System APLL Aux Clk" },
]
let DCC_Count0ClockSource = [
	{ name: "DCC_COUNT0SRC_XTAL", displayName: "XTAL Clock Source" },
	{ name: "DCC_COUNT0SRC_INTOSC1", displayName: "Internal Oscillator1 Clock Source" },
	{ name: "DCC_COUNT0SRC_INTOSC2", displayName: "Internal Oscillator2 Clock Source" },
	{ name: "DCC_COUNT0SRC_SYSCLK", displayName: "System Clock Source" },
	{ name: "DCC_COUNT0SRC_AUXCLK", displayName: "AUX Clock Source" },
]
module.exports = {
	DCC_SingleShotMode: DCC_SingleShotMode,
	DCC_Count1ClockSource: DCC_Count1ClockSource,
	DCC_Count0ClockSource: DCC_Count0ClockSource,
}
