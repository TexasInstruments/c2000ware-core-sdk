let PGA_GainValue = [
	{ name: "PGA_GAIN_3", displayName: "PGA gain value of 3" },
	{ name: "PGA_GAIN_6", displayName: "PGA gain value of 6" },
	{ name: "PGA_GAIN_12", displayName: "PGA gain value of 12" },
	{ name: "PGA_GAIN_24", displayName: "PGA gain value of 24" },
]
let PGA_LowPassResistorValue = [
	{ name: "PGA_LOW_PASS_FILTER_DISABLED", displayName: "Low pass filter disabled (open circuit)" },
	{ name: "PGA_LOW_PASS_FILTER_RESISTOR_200_OHM", displayName: "Resistor value of 200 Ohm" },
	{ name: "PGA_LOW_PASS_FILTER_RESISTOR_160_OHM", displayName: "Resistor value of 160 Ohm" },
	{ name: "PGA_LOW_PASS_FILTER_RESISTOR_130_OHM", displayName: "Resistor value of 130 Ohm" },
	{ name: "PGA_LOW_PASS_FILTER_RESISTOR_100_OHM", displayName: "Resistor value of 100 Ohm" },
	{ name: "PGA_LOW_PASS_FILTER_RESISTOR_80_OHM", displayName: "Resistor value of 80 Ohm" },
	{ name: "PGA_LOW_PASS_FILTER_RESISTOR_50_OHM", displayName: "Resistor value of 50 Ohm" },
]
let PGA_REGISTER = [
	{ name: "PGA_REGISTER_PGACTL", displayName: "PGA Register PGACTL" },
	{ name: "PGA_REGISTER_GAIN3TRIM", displayName: "PGA Register GAIN3TRIM" },
	{ name: "PGA_REGISTER_GAIN6TRIM", displayName: "PGA Register GAIN6TRIM" },
	{ name: "PGA_REGISTER_GAIN12TRIM", displayName: "PGA Register GAIN12TRIM" },
	{ name: "PGA_REGISTER_GAIN24TRIM", displayName: "PGA Register GAIN24TRIM" },
]
module.exports = {
	PGA_GainValue: PGA_GainValue,
	PGA_LowPassResistorValue: PGA_LowPassResistorValue,
	PGA_REGISTER: PGA_REGISTER,
}
