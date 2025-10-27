let DMA_Trigger = [
	{ name: "DMA_TRIGGER_SOFTWARE", displayName: "TRIGGER SOFTWARE" },
	{ name: "DMA_TRIGGER_ADCA1", displayName: "TRIGGER ADCA1" },
	{ name: "DMA_TRIGGER_ADCA2", displayName: "TRIGGER ADCA2" },
	{ name: "DMA_TRIGGER_ADCAEVT", displayName: "TRIGGER ADCAEVT" },
	{ name: "DMA_TRIGGER_XINT1", displayName: "TRIGGER XINT1" },
	{ name: "DMA_TRIGGER_XINT2", displayName: "TRIGGER XINT2" },
	{ name: "DMA_TRIGGER_XINT3", displayName: "TRIGGER XINT3" },
	{ name: "DMA_TRIGGER_XINT4", displayName: "TRIGGER XINT4" },
	{ name: "DMA_TRIGGER_XINT5", displayName: "TRIGGER XINT5" },
	{ name: "DMA_TRIGGER_MCPWM1SOCA", displayName: "TRIGGER MCPWM1SOCA" },
	{ name: "DMA_TRIGGER_MCPWM1SOCB", displayName: "TRIGGER MCPWM1SOCB" },
	{ name: "DMA_TRIGGER_MCPWM1SOCC", displayName: "TRIGGER MCPWM1SOCC" },
	{ name: "DMA_TRIGGER_MCPWM1SOCD", displayName: "TRIGGER MCPWM1SOCD" },
	{ name: "DMA_TRIGGER_MCPWM3SOCA", displayName: "TRIGGER MCPWM3SOCA" },
	{ name: "DMA_TRIGGER_MCPWM3SOCB", displayName: "TRIGGER MCPWM3SOCB" },
	{ name: "DMA_TRIGGER_TINT0", displayName: "TRIGGER TINT0" },
	{ name: "DMA_TRIGGER_TINT1", displayName: "TRIGGER TINT1" },
	{ name: "DMA_TRIGGER_TINT2", displayName: "TRIGGER TINT2" },
	{ name: "DMA_TRIGGER_ECAP1", displayName: "TRIGGER ECAP1" },
	{ name: "DMA_TRIGGER_SPIATX", displayName: "TRIGGER SPIATX" },
	{ name: "DMA_TRIGGER_SPIARX", displayName: "TRIGGER SPIARX" },
	{ name: "DMA_TRIGGER_UARTARX", displayName: "TRIGGER UARTARX" },
	{ name: "DMA_TRIGGER_UARTATX", displayName: "TRIGGER UARTATX" },
]
let DMA_InterruptMode = [
	{ name: "DMA_INT_AT_BEGINNING", displayName: "DMA interrupt is generated at the beginning of a transfer" },
	{ name: "DMA_INT_AT_END", displayName: "DMA interrupt is generated at the end of a transfer" },
]
let DMA_EmulationMode = [
	{ name: "DMA_EMULATION_STOP", displayName: "Transmission stops after current read-write access is completed" },
	{ name: "DMA_EMULATION_FREE_RUN", displayName: "Continue DMA operation regardless of emulation suspend" },
]
let DMA_CFG = [
	{ name: "DMA_CFG_ONESHOT_DISABLE", displayName: "Only one burst transfer performed per trigger." },
	{ name: "DMA_CFG_ONESHOT_ENABLE", displayName: "Burst transfers occur without additional event triggers after the first." },
	{ name: "DMA_CFG_CONTINUOUS_DISABLE", displayName: "DMA channel will be disabled at the end of a transfer." },
	{ name: "DMA_CFG_CONTINUOUS_ENABLE", displayName: "DMA reinitializes when the transfer count is zero and waits for a trigger." },
	{ name: "DMA_CFG_SIZE_16BIT", displayName: "DMA transfers 16 bits at a time." },
	{ name: "DMA_CFG_SIZE_32BIT", displayName: "DMA transfers 32 bits at a time." },
]
module.exports = {
	DMA_Trigger: DMA_Trigger,
	DMA_InterruptMode: DMA_InterruptMode,
	DMA_EmulationMode: DMA_EmulationMode,
	DMA_CFG: DMA_CFG,
}
