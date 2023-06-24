exports = {
	displayName: "Adder",
	config: [{
		name: "type",
		displayName: "Type",
		default: "Adder",
		readOnly: true,
	}],
	extendConfig: ({ $ipInstance }) => [
		{
			name: "Description",
			displayName: "Description",
			default: $ipInstance.description,
			readOnly: true,
		},
		{
			name: "InputValue1",
			displayName: "Input Clock 1 (MHz)",
			default: '',
			getValue: (inst) => {
				const value = inst[$ipInstance.inPins[0].name] + ' MHz';
				return value;
			}
		},
		{
			name: "InputValue2",
			displayName: "Input Clock 2 (MHz)",
			default: '',
			getValue: (inst) => {
				const value = inst[$ipInstance.inPins[1].name] + ' MHz';
				return value;
			}
		},
		{
			name: $ipInstance.outPins[0].name,
			default: 0,
			getValue: (inst) => {
				const value1 = inst[$ipInstance.inPins[0].name];
				const value2 = inst[$ipInstance.inPins[1].name];
				return value1 + value2;
			},
		}
	]
};
