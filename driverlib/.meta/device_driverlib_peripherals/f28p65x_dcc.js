let DCC_SingleShotMode = [
	{ name: "DCC_MODE_COUNTER_ZERO", displayName: "Use to stop counting when counter0 and valid0 both reach zero" },
	{ name: "DCC_MODE_COUNTER_ONE", displayName: "Use to stop counting when counter1 reaches zero" },
]
let DCC_Count1ClockSource = [
	{ name: "DCC_COUNT1SRC_PLL", displayName: "PLLRAWCLK Clock Out Source" },
	{ name: "DCC_COUNT1SRC_AUXPLL", displayName: "AUXPLL Clock Out Source" },
	{ name: "DCC_COUNT1SRC_INTOSC1", displayName: "Internal Oscillator1 Clock Source" },
	{ name: "DCC_COUNT1SRC_INTOSC2", displayName: "Internal Oscillator2 Clock Source" },
	{ name: "DCC_COUNT1SRC_ECATPHYCLK", displayName: "Ethercat PHY Clock Source" },
	{ name: "DCC_COUNT1SRC_CPU1SYSCLK", displayName: "CPU1 SYSCLK (System Clock) Source" },
	{ name: "DCC_COUNT1SRC_CPU2SYSCLK", displayName: "CPU2 SYSCLK (System Clock) Source" },
	{ name: "DCC_COUNT1SRC_AUXCLKIN", displayName: "AUXCLK (Auxiliary Clock) Source" },
	{ name: "DCC_COUNT1SRC_EPWM", displayName: "EPWM Clock Source" },
	{ name: "DCC_COUNT1SRC_LSPCLK", displayName: "LSPCLK (Low Speed Clock) Source" },
	{ name: "DCC_COUNT1SRC_ADCCLK", displayName: "ADC Clock Source" },
	{ name: "DCC_COUNT1SRC_WDCLK", displayName: "Watch Dog Clock Source" },
	{ name: "DCC_COUNT1SRC_CANX", displayName: "CANxBIT Clock Source" },
	{ name: "DCC_COUNT1SRC_MCANA", displayName: "CANxBIT Clock Source" },
	{ name: "DCC_COUNT1SRC_MCANB", displayName: "CANxBIT Clock Source" },
	{ name: "DCC_COUNT1SRC_USB", displayName: "USB BIT Clock Source" },
]
let DCC_Count0ClockSource = [
	{ name: "DCC_COUNT0SRC_XTAL", displayName: "XTAL Clock Source" },
	{ name: "DCC_COUNT0SRC_INTOSC1", displayName: "Internal Oscillator1 Clock Source" },
	{ name: "DCC_COUNT0SRC_INTOSC2", displayName: "Internal Oscillator2 Clock Source" },
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
