let CLAPROMCRC_EmulationMode = [
	{ name: "CLAPROMCRC_MODE_SOFT", displayName: "Soft Mode" },
	{ name: "CLAPROMCRC_MODE_FREE", displayName: "Free Mode" },
]
let CLAPROMCRC_IntFlag = [
	{ name: "CLAPROMCRC_INT_FLG", displayName: "Global Interrupt Flag" },
	{ name: "CLAPROMCRC_CRCDONE_FLG", displayName: "CRCDONE Interrupt Flag" },
]
module.exports = {
	CLAPROMCRC_EmulationMode: CLAPROMCRC_EmulationMode,
	CLAPROMCRC_IntFlag: CLAPROMCRC_IntFlag,
}
