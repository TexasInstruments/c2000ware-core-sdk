let DCC_SingleShotMode = [
	{ name: "DCC_MODE_COUNTER_ZERO", displayName: "Use to stop counting when counter0 and valid0 both reach zero" },
	{ name: "DCC_MODE_COUNTER_ONE", displayName: "Use to stop counting when counter1 reaches zero" },
]
let DCC_Count1ClockSource = [
	{ name: "DCC_COUNT1SRC_PLL", displayName: "PLLRAWCLK Clock Out Source" },
	{ name: "DCC_COUNT1SRC_WROSCDIV8", displayName: "Wide Range Oscillator (WROSC) output clock after the fixed BY8 divider" },
	{ name: "DCC_COUNT1SRC_SYSOSCDIV4", displayName: "SYSOSC output clock after the fixed BY4 divider" },
	{ name: "DCC_COUNT1SRC_SYSCLK", displayName: "SYSCLK (System Clock) Source" },
	{ name: "DCC_COUNT1SRC_XBAR_IN15", displayName: "Input Crossbar Clock Source" },
	{ name: "DCC_COUNT1SRC_AUXCLKIN", displayName: "AUXCLKIN (Auxiliary Clock) Source" },
	{ name: "DCC_COUNT1SRC_MCPWM", displayName: "MCPWM Clock Source" },
	{ name: "DCC_COUNT1SRC_LSPCLK", displayName: "LSP Clock Source" },
	{ name: "DCC_COUNT1SRC_ADCCLK", displayName: "ADC Clock Source" },
	{ name: "DCC_COUNT1SRC_WDCLK", displayName: "Watch Dog Clock Source" },
	{ name: "DCC_COUNT1SRC_NW_FCLK", displayName: "FCLK (divided clock) output" },
	{ name: "DCC_COUNT1SRC_XBAR1_IN11", displayName: "Input Crossbar1 Clock Source" },
	{ name: "DCC_COUNT1SRC_XBAR1_IN12", displayName: "Input Crossbar1 Clock Source" },
]
let DCC_Count0ClockSource = [
	{ name: "DCC_COUNT0SRC_XTAL", displayName: "XTAL Clock Source" },
	{ name: "DCC_COUNT0SRC_WROSCDIV8", displayName: "Wide Range Oscillator (WROSC) OUTPUT CLOCK AFTER THE FIXED BY-8 DIVIDER" },
	{ name: "DCC_COUNT0SRC_SYSOSCDIV4", displayName: "SYSOSC output clock after the fixed BY4 divider" },
	{ name: "DCC_COUNT0SRC_TCK", displayName: "Preliminary Clock Source" },
	{ name: "DCC_COUNT0SRC_SYSCLK", displayName: "System Clock Source" },
	{ name: "DCC_COUNT0SRC_AUXCLK", displayName: "AUX Clock Source" },
	{ name: "DCC_COUNT0SRC_XBAR", displayName: "Input XBAR Clock Source" },
]
module.exports = {
	DCC_SingleShotMode: DCC_SingleShotMode,
	DCC_Count1ClockSource: DCC_Count1ClockSource,
	DCC_Count0ClockSource: DCC_Count0ClockSource,
}
