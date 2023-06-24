let DCC_SingleShotMode = [
	{ name: "DCC_MODE_COUNTER_ZERO", displayName: "Use to stop counting when counter0 and valid0 both reach zero" },
	{ name: "DCC_MODE_COUNTER_ONE", displayName: "Use to stop counting when counter1 reaches zero" },
]
let DCC_RevisionNumber = [
	{ name: "DCC_REVISION_MINOR", displayName: "The module minor revision number" },
	{ name: "DCC_REVISION_MAJOR", displayName: "The module major revision number" },
]
let DCC_Count1ClockSource = [
	{ name: "DCC_COUNT1SRC_PLL", displayName: "PLLRAWCLK Clock Out Source" },
	{ name: "DCC_COUNT1SRC_INTOSC1", displayName: "Internal Oscillator1 Clock Source" },
	{ name: "DCC_COUNT1SRC_INTOSC2", displayName: "Internal Oscillator2 Clock Source" },
]
let DCC_Count0ClockSource = [
	{ name: "DCC_COUNT0SRC_XTAL", displayName: "XTAL Clock Source" },
	{ name: "DCC_COUNT0SRC_INTOSC1", displayName: "Internal Oscillator1 Clock Source" },
	{ name: "DCC_COUNT0SRC_INTOSC2", displayName: "Internal Oscillator2 Clock Source" },
]
module.exports = {
	DCC_SingleShotMode: DCC_SingleShotMode,
	DCC_RevisionNumber: DCC_RevisionNumber,
	DCC_Count1ClockSource: DCC_Count1ClockSource,
	DCC_Count0ClockSource: DCC_Count0ClockSource,
}
