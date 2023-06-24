exports = {
	displayName: "Mux",
	config: [],
	extendConfig: ({ $ipInstance }) => [
	{
		name: "Description",
		displayName: "Description",
		default: $ipInstance.description,
		readOnly: true,
	},
	{
		name: "inputSelect",
		displayName: "Input Select",
		default: $ipInstance.resetValue,
		options: _.map($ipInstance.inPins, ({ name }) => ({ name })),
	}, {
		name: $ipInstance.outPins[0].name,
		default: 0,
		getValue: (inst) => inst[inst.inputSelect],
	}],
};
