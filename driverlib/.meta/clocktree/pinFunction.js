const { getDefaultValue } = system.getScript("./defaultValue.js");

exports = {
	displayName: "Pin Function",
	config: [],
	validate: (inst, { $ipInstance,logError, logWarning }) => {
		let min = inst.$ipInstance.Min;
		let max = inst.$ipInstance.Max;
		const derivedClock = inst.XTAL_Freq;

		let minMsg = "Configured " + inst.$ipInstance.name + " = " + derivedClock + " MHz. Minimum " + inst.$ipInstance.name + " frequency supported = " + inst.$ipInstance.Min + " MHz";
		let maxMsg = "Configured " + inst.$ipInstance.name + " = " + derivedClock + " MHz. Maximum " + inst.$ipInstance.name + " frequency supported = " + inst.$ipInstance.Max + " MHz";
		
		if (derivedClock < min) 
		{
			if (inst.warning) 
			{
				logWarning(minMsg, inst, inst.$ipInstance.outPins[0].name)
			} 
			else 
			{
				logError(minMsg, inst, inst.$ipInstance.outPins[0].name)
			}
		}
		if (derivedClock > max) 
		{
			if (inst.warning) 
			{
				logWarning(maxMsg + inst.$ipInstance.Max + " MHz", inst, inst.$ipInstance.outPins[0].name)
			} 
			else 
			{
				logError(maxMsg , inst, inst.$ipInstance.outPins[0].name)
			}
		}
},
	extendConfig: ({ $ipInstance }) => {
		if (!_.isEmpty($ipInstance.outPins)) {
			return [
				{
					name: "Description",
					displayName: "Description",
					default: $ipInstance.description,
					readOnly: true
				},
				{
					name: "XTAL_Freq",
					displayName: "XTAL Frequency (in MHz)",
					default: $ipInstance.outputValue,
					readOnly: false
				},
				{
					name: $ipInstance.outPins[0].name,
					default: 0,
					getValue: (inst) => inst.XTAL_Freq,
					readOnly: false,
					hidden: true
				},
				{
					name: "minXTAL",
					displayName: "Min XTAL Frequency supported (in MHz)",
					default: $ipInstance.Min,
					readOnly: true
				},
				{
					name: "maxXTAL",
					displayName: "Max XTAL Frequency supported (in MHz)",
					default: $ipInstance.Max,
					readOnly: true
				}
			];
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
