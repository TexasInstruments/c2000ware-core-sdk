let PGA_GainValue = [
	{ name: "PGA_GAIN_1", displayName: "PGA gain value of 1" },
	{ name: "PGA_GAIN_2", displayName: "PGA gain value of 2 or -1" },
	{ name: "PGA_GAIN_4", displayName: "PGA gain value of 4 or -3" },
	{ name: "PGA_GAIN_8", displayName: "PGA gain value of 8 or -7" },
	{ name: "PGA_GAIN_16", displayName: "PGA gain value of 16 or -15" },
	{ name: "PGA_GAIN_32", displayName: "PGA gain value of 32 or -31" },
	{ name: "PGA_GAIN_64", displayName: "PGA gain value of 64 or -63" },
]
let PGA_LowPassResistorValue = [
	{ name: "PGA_LOW_PASS_FILTER_DISABLED", displayName: "Low pass filter disabled (open circuit)" },
	{ name: "PGA_LOW_PASS_FILTER_RESISTOR_50_OHM", displayName: "Resistor value of 50 Ohm" },
	{ name: "PGA_LOW_PASS_FILTER_RESISTOR_100_OHM", displayName: "Resistor value of 100 Ohm" },
	{ name: "PGA_LOW_PASS_FILTER_RESISTOR_200_OHM", displayName: "Resistor value of 200 Ohm" },
	{ name: "PGA_LOW_PASS_FILTER_RESISTOR_400_OHM", displayName: "Resistor value of 400 Ohm" },
	{ name: "PGA_LOW_PASS_FILTER_RESISTOR_800_OHM", displayName: "Resistor value of 800 Ohm" },
]
let PGA_PMUXInput = [
	{ name: "PGA_PMUX_INP1", displayName: "PGA_INP1 as non-inverting input" },
	{ name: "PGA_PMUX_INP2", displayName: "PGA_INP2 as non-inverting input" },
	{ name: "PGA_PMUX_INP3", displayName: "PGA_INP3 as non-inverting input" },
]
let PGA_NMUXInput = [
	{ name: "PGA_NMUX_RTOP", displayName: "RTOP as inverting input" },
	{ name: "PGA_NMUX_RTAP", displayName: "RTAP as inverting input" },
	{ name: "PGA_NMUX_INM1", displayName: "PGA_INM1 as inverting input" },
	{ name: "PGA_NMUX_INM2", displayName: "PGA_INM2 as inverting input" },
]
let PGA_MMUXInput = [
	{ name: "PGA_MMUX_NAKED_OPAMP", displayName: "Naked op-amp mode" },
	{ name: "PGA_MMUX_NON_INVERTING_GAIN_VSSA", displayName: "VSSA as MMUX input for" },
	{ name: "PGA_MMUX_INVERTING_GAIN_NEG", displayName: "PGA_NEG as MMUX input for" },
	{ name: "PGA_MMUX_INVERTING_GAIN_NEG_SHARED", displayName: "PGA_NEG_SHARED as MMUX input" },
]
let PGA_Chop = [
	{ name: "PGA_CHOP_DISABLE", displayName: "Chopping is disabled" },
	{ name: "PGA_CHOP_REGULAR_INTOSC", displayName: "Regular chopping using INTOSC" },
	{ name: "PGA_CHOP_ADC_ASSISTED_ADCSOC", displayName: "ADC assisted chop using ADCSOC" },
	{ name: "PGA_CHOP_ADC_ASSISTED_EXTCTRL", displayName: "ADC assisted chop using" },
]
let PGA_REGISTER = [
	{ name: "PGA_REGISTER_PGACTL", displayName: "PGA Register PGACTL" },
	{ name: "PGA_REGISTER_MUXSEL", displayName: "PGA Register MUXSEL" },
	{ name: "PGA_REGISTER_OFFSETTRIM", displayName: "PGA Register OFFSETTRIM" },
]
module.exports = {
	PGA_GainValue: PGA_GainValue,
	PGA_LowPassResistorValue: PGA_LowPassResistorValue,
	PGA_PMUXInput: PGA_PMUXInput,
	PGA_NMUXInput: PGA_NMUXInput,
	PGA_MMUXInput: PGA_MMUXInput,
	PGA_Chop: PGA_Chop,
	PGA_REGISTER: PGA_REGISTER,
}
