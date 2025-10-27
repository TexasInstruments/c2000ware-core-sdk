exports = {
	displayName: "Multiplier",
	config: [],
	extendConfig: ({ $ipInstance }) => [
	{
		name: "Description",
		displayName: "Description",
		default: $ipInstance.description,
		readOnly: true,
	},
	{
		name: "InputValue",
		displayName: "Input Clock (MHz)",
		default: '',
		getValue: (inst) => {
			const value = inst[$ipInstance.inPins[0].name] + ' MHz';
			return value;
		}
	},
	{
		name: "multiplyValue",
		displayName: "Multiply Value",
		default: (system.deviceData.gpn == "TMS320F2800132") && ($ipInstance.name == "PLL_IMULT") ? 40 : $ipInstance.resetValue,
		options: _.map($ipInstance.multiplyValues, (v) => ({ name: v, displayName: `X ${v}` })),
	}, 
	{
		name: $ipInstance.outPins[0].name,
		displayName: "Output Clock",
		default: 0,
		getValue: (inst) => {
			const value = inst[$ipInstance.inPins[0].name];
			return value * inst.multiplyValue;
		},
	}],
};
