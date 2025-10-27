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
		default: (system.deviceData.gpn == "TMS320F2800132") && ($ipInstance.name == "PLL_ODIV") ? 2 : $ipInstance.resetValue,
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
	}],
	validate: (inst, { $ipInstance, logError, logWarning }) => {
		let sensitive_devices = ["F2838x", "F28P65x", "F2837xD", "F2837xS", "F2807x"];
		let div_value = inst.divideValue;
		let warningMsg1 = "ePWM TZFRC and TZCLR events will sometimes be missed when EPWMCLKDIV is divide by 2. Always program EPWMCLKDIV to divide by 1 if using TZFRC or TZCLR register. ";
		let warningMsg2 = "Please refer to the " + system.deviceData.device + " Silicon Errata for more details.";
		let warningMsg = warningMsg1 + warningMsg2;
		
		if (inst.$ipInstance.name == "EPWMCLKDIV") 
		{
			if (div_value == 2 && sensitive_devices.includes(system.deviceData.device)) 
				{
					logWarning(warningMsg, inst, inst.$ipInstance.outPins[0].name)
				}
		}
	}
};
