exports = {
	displayName: "Divider",
	config: [],
	extendConfig: ({ $ipInstance }) => [
	{
		name: "Description",
		displayName: "Description",
		default: $ipInstance.description,
		readOnly: true
	},
	{
		name: "InputValue",
		displayName: "Input Clock",
		default: '',
		getValue: (inst) => {
			const value = inst[$ipInstance.inPins[0].name] + ' MHz';
			return value;
		}
	},		
	{
		name: "divideValue",
		displayName: "Divide Value",
		default: $ipInstance.resetValue,
		options: _.map($ipInstance.divideValues, (v) => ({ name: v, displayName: `/ ${v}` })),
	}, 
	{
		name: $ipInstance.outPins[0].name,
		default: [0, 0],
		getValue: (inst) => {
			const value = inst[$ipInstance.inPins[0].name];
			if (_.isArray(value)) {
				return _.map(value, (v) => v / inst.divideValue);
			}
			return value / inst.divideValue;
		},
	}]
};
