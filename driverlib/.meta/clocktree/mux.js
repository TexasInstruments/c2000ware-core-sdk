function onValidate (inst, { $ipInstance, logInfo, logWarning }) 
{
	var sysctl = system.modules['/driverlib/sysctl.js']
	if (sysctl)
	{
		if (inst.cpu_sel_mux)
		{
			logInfo("For enabling peripherals, use the " + system.getReference(sysctl.$static, "enable_SYSCTL_PERIPH_CLK_TIMER0"), inst, "cpu_sel_mux")
		}
	}

	if (inst.inputSelect == "WROSCDIV8" && system.deviceData.device == "F28E12x") 
	{
		const derivedClock = inst[inst.$ipInstance.outPins[0].name];
		let infoMsg = "When using " + inst.inputSelect + ", " + derivedClock + " MHz is not guaranteed and can range from 2.5 MHz to 8.75 MHz on every device.";
		logInfo(infoMsg, inst, inst.$ipInstance.outPins[0].name)
	}
	if (inst.inputSelect == "OSCCLK" && inst.$ipInstance.name == "SYSPLLCTL1") 
	{
		let infoMsg = "When bypassing the SYSPLL, the system clock is directly sourced from " + inst.inputSelect + ". The functional impact of PLL bypass mode on the device clocking will need to be considered.";
		logWarning(infoMsg, inst, inst.$ipInstance.outPins[0].name)
	} 
}

exports = {
	displayName: "Mux",
	config: [],
	extendConfig: ({ $ipInstance }) => {
		var pinConfig = [];
		pinConfig.push({
			name: "Description",
			displayName: "Description",
			default: $ipInstance.description,
			readOnly: true,
		})
		pinConfig.push({
			name: "inputSelect",
			displayName: "Input Select",
			default: $ipInstance.resetValue,
			options: _.map($ipInstance.inPins, ({ name }) => ({ name })),
		})
		pinConfig.push({
			name: $ipInstance.outPins[0].name,
			default: 0,
			getValue: (inst) => inst[inst.inputSelect],
		})
		if ($ipInstance.name == "CPUSELx")
		{
				pinConfig.push({
				name: "cpu_sel_mux", 
				displayName: "CPU Select Mux", 
				default: "Click the hyper link for SYSCLK GATES", 
				getValue: (inst) => { return "Click the hyper link for SYSCLK GATES" },
			})
		}
		return pinConfig;
	},
	validate: onValidate,
};