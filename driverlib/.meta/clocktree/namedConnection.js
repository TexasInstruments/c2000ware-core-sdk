let Common = system.getScript("/driverlib/Common.js");

exports = {
	displayName: "NamedConnection",
	config: [],
	extendConfig: ({ $ipInstance }) => [
	{
            name: "in",
            displayName: "Frequency",
            default: 0,
            getValue: () => 0,
    },
	{
		name: "Min",
		displayName: "Min",
		default: ($ipInstance.Min??"-1") + " MHz",
		readOnly: true,
	},
	{
		name: "Max",
		displayName: "Max",
		default: ($ipInstance.Max??"-1") + " MHz",
		readOnly: true,
	},	
	{
        name: "out",
        default: 0,
        getValue: (inst) => inst.in,
        hidden: true,
    }],
	validate: (inst, { $ipInstance, logError, logWarning }) => {
			let min = inst.$ipInstance.Min;
			let max = inst.$ipInstance.Max;
			const derivedClock = inst[inst.$ipInstance.inPins[0].name];

			let minMsg = "Configured " + inst.$ipInstance.name + " = " + derivedClock + " MHz. Minimum frequency supported = " + inst.$ipInstance.Min + " MHz";
			let maxMsg = "Configured " + inst.$ipInstance.name + " = " + derivedClock + " MHz. Maximum frequency supported = " + inst.$ipInstance.Max + " MHz";

			if (derivedClock < min) 
			{
				if (inst.warning || Common.getPLLBypass()) 
				{
					logWarning(minMsg, inst, inst.$ipInstance.inPins[0].name)
				} 
				else 
				{
					logError(minMsg, inst, inst.$ipInstance.inPins[0].name)
				}
			}
			if (derivedClock > max) 
			{
				if (inst.warning || Common.getPLLBypass()) 
				{
					logWarning(maxMsg + inst.$ipInstance.Max + " MHz", inst, inst.$ipInstance.outPins[0].name)
				} 
				else 
				{
					logError(maxMsg , inst, inst.$ipInstance.inPins[0].name)
				}
			}
	},
};
