const { getDefaultValue } = system.getScript("./defaultValue.js");

exports = {
	displayName: "Internal Oscillators",
	config: [{
		name: "type",
		displayName: "Type",
		default: "Internal Oscillators",
		readOnly: true,
	}, ],
	extendConfig: ({ $ipInstance }) => {
		if (!_.isEmpty($ipInstance.outPins)) {
			return [{
				name: $ipInstance.outPins[0].name,
				default: 10,
				getValue: (inst) => $ipInstance.outputValue,
				readOnly: false
			}];
		} else {
			// Override the input pin so it's visible with a tool tip
			return [{
				name: $ipInstance.description,
				default: 0,
				description: "Custom tool tip",
				hidden: false,
				getValue: () => { } // Tool will update
			}]
		}
	},

	

};
