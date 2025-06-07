let Common   = system.getScript("/driverlib/Common.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_mcpwm.js");

var validation_warning = "warning"
var validation_error = "error"
var validation_info = "info"

var mcpwm_validation = [
	// Validation #0
	{
		type : validation_warning,
		name : "Code Generation is using Shadow Registers, Please enable the Local Load or Global Load settings.",
		func : (inst, validation, name) => {
			let configs_list = [
				"mcpwmTimebase_periodLoadMode",
				"mcpwmCounterCompare_shadowLoadModeCMPA",
				"mcpwmCounterCompare_shadowLoadModeCMPB",
				"mcpwmCounterCompare_shadowLoadModeCMPA_pwm2",
				"mcpwmCounterCompare_shadowLoadModeCMPB_pwm2",
				"mcpwmCounterCompare_shadowLoadModeCMPA_pwm3",
				"mcpwmCounterCompare_shadowLoadModeCMPB_pwm3",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1A_shadowEvent",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1B_shadowEvent",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2A_shadowEvent",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2B_shadowEvent",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3A_shadowEvent",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3B_shadowEvent",
				"mcpwmDeadband_redShadowLoadEvent",
				"mcpwmDeadband_fedShadowLoadEvent"
			]
			let enable_config_list = [
				"mcpwmCounterCompare_enableShadowLoadModeCMPA",
				"mcpwmCounterCompare_enableShadowLoadModeCMPB",
				"mcpwmCounterCompare_enableShadowLoadModeCMPA_pwm2",
				"mcpwmCounterCompare_enableShadowLoadModeCMPB_pwm2",
				"mcpwmCounterCompare_enableShadowLoadModeCMPA_pwm3",
				"mcpwmCounterCompare_shadowLoadModeCMPB_pwm3",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1A_shadowMode",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1B_shadowMode",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2A_shadowMode",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2B_shadowMode",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3A_shadowMode",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3B_shadowMode",
				"mcpwmDeadband_redShadowMode",
				"mcpwmDeadband_fedShadowMode"
			]
			for (let config of configs_list){
				if(true == inst.mcpwm_useShdwRegForCodeGen){
					if((false == inst.mcpwmGlobalLoad_gld) && (inst[config].includes("DISABLE") || inst[config].includes("FREEZE"))){
						validation.logWarning(name, inst, config)
					}
				}
			}
			for (let config of enable_config_list){
				if(true == inst.mcpwm_useShdwRegForCodeGen){
					if((false == inst.mcpwmGlobalLoad_gld) && (inst[config] == false)){
						validation.logWarning(name, inst, config)
					}
				}
			}
		},
		devices : ["F28E12x"],
	},
	// Validation #0a
	{
		type : validation_warning,
		name : "Code Generation is using Active Registers, Please disable the Local Load or Global Load settings to avoid overwrites.",
		func : (inst, validation, name) => {
			let configs_list = [
				"mcpwmTimebase_periodLoadMode",
				"mcpwmCounterCompare_shadowLoadModeCMPA",
				"mcpwmCounterCompare_shadowLoadModeCMPB",
				"mcpwmCounterCompare_shadowLoadModeCMPA_pwm2",
				"mcpwmCounterCompare_shadowLoadModeCMPB_pwm2",
				"mcpwmCounterCompare_shadowLoadModeCMPA_pwm3",
				"mcpwmCounterCompare_shadowLoadModeCMPB_pwm3",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1A_shadowEvent",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1B_shadowEvent",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2A_shadowEvent",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2B_shadowEvent",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3A_shadowEvent",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3B_shadowEvent",
				"mcpwmDeadband_redShadowLoadEvent",
				"mcpwmDeadband_fedShadowLoadEvent"
			]
			let enable_config_list = [
				"mcpwmCounterCompare_enableShadowLoadModeCMPA",
				"mcpwmCounterCompare_enableShadowLoadModeCMPB",
				"mcpwmCounterCompare_enableShadowLoadModeCMPA_pwm2",
				"mcpwmCounterCompare_enableShadowLoadModeCMPB_pwm2",
				"mcpwmCounterCompare_enableShadowLoadModeCMPA_pwm3",
				"mcpwmCounterCompare_shadowLoadModeCMPB_pwm3",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1A_shadowMode",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1B_shadowMode",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2A_shadowMode",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2B_shadowMode",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3A_shadowMode",
				"mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3B_shadowMode",
				"mcpwmDeadband_redShadowMode",
				"mcpwmDeadband_fedShadowMode"
			]
			for (let config of configs_list){
				if(false == inst.mcpwm_useShdwRegForCodeGen){
					if((false == inst.mcpwmGlobalLoad_gld) && (inst[config].includes("DISABLE") || inst[config].includes("FREEZE"))){

					}else{
						validation.logWarning(name, inst, config)
					}
				}
			}
			for (let config of enable_config_list){
				if(false == inst.mcpwm_useShdwRegForCodeGen){
					if((false == inst.mcpwmGlobalLoad_gld) && (inst[config] == false)){

					}else{
						validation.logWarning(name, inst, config)
					}
				}
			}
		},
		devices : ["F28E12x"],
	},
	// Validation #1
	{
		type : validation_warning,
		name :  "CMP value is out of range of TBPRD. Refer to table, Behavior if CMPA/CMPB is Greater than the Period, within the TRM",
		func : (inst, validation, name) => {
			if (inst["mcpwmTimebase_period"] < 
				inst["mcpwmCounterCompare_cmpA"]) 
			{
				validation.logWarning(name, inst, "mcpwmCounterCompare_cmpA");
			}
			if (inst["mcpwmTimebase_period"] < 
				inst["mcpwmCounterCompare_cmpB"]) 
			{
				validation.logWarning(name, inst, "mcpwmCounterCompare_cmpB");
			}
			if (inst["mcpwmTimebase_period"] < 
				inst["mcpwmCounterCompare_cmpA_pwm2"]) 
			{
				validation.logWarning(name, inst, "mcpwmCounterCompare_cmpA_pwm2");
			}
			if (inst["mcpwmTimebase_period"] < 
				inst["mcpwmCounterCompare_cmpB_pwm2"]) 
			{
				validation.logWarning(name, inst, "mcpwmCounterCompare_cmpB_pwm2");
			}
			if (inst["mcpwmTimebase_period"] < 
				inst["mcpwmCounterCompare_cmpA_pwm3"]) 
			{
				validation.logWarning(name, inst, "mcpwmCounterCompare_cmpA_pwm3");
			}
			if (inst["mcpwmTimebase_period"] < 
				inst["mcpwmCounterCompare_cmpB_pwm3"]) 
			{
				validation.logWarning(name, inst, "mcpwmCounterCompare_cmpB_pwm3");
			}
			if (inst["mcpwmTimebase_period"] < 
				inst["mcpwmCounterCompare_cmpC"]) 
			{
				validation.logWarning(name, inst, "mcpwmCounterCompare_cmpC");
			}
			if (inst["mcpwmTimebase_period"] < 
				inst["mcpwmCounterCompare_cmpD"]) 
			{
				validation.logWarning(name, inst, "mcpwmCounterCompare_cmpD");
			}
			
		},
			devices : ["F28E12x"]
		},

    // Validation #2
	// {
	// 	type : validation_warning,
	// 	name :  "It is recommended to use a non-zero counter compare value when using shadow to active load of action qualifier A/B control register on TBCTR=0 boundary",
	// 	func : (inst, validation, name) => {
	// 		if ((inst["mcpwmCounterCompare_cmpA"] == 0  || inst["mcpwmCounterCompare_cmpB"] == 0) 
	// 			&& 
	// 			(inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1A_shadowMode"] == true 
	// 			&& (inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1A_shadowEvent"] != "MCPWM_AQ_LOAD_FREEZE"))
	// 			||
	// 			(inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1B_shadowMode"] == true 
	// 			&& (inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1B_shadowEvent"] != "MCPWM_AQ_LOAD_FREEZE")))
	// 		{
	// 			validation.logWarning(name, inst, "mcpwmCounterCompare_cmpA");
	// 			validation.logWarning(name, inst, "mcpwmCounterCompare_cmpB");
	// 		}
			
	// 		if ((inst["mcpwmCounterCompare_cmpA_pwm2"] == 0  || inst["mcpwmCounterCompare_cmpB_pwm2"] == 0) 
	// 			&& 
	// 			(inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2A_shadowMode"] == true 
	// 			&& (inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2A_shadowEvent"] != "MCPWM_AQ_LOAD_FREEZE"))
	// 			||
	// 			(inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2B_shadowMode"] == true 
	// 			&& (inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2B_shadowEvent"] != "MCPWM_AQ_LOAD_FREEZE")))
	// 		{
	// 			validation.logWarning(name, inst, "mcpwmCounterCompare_cmpA_pwm2");
	// 			validation.logWarning(name, inst, "mcpwmCounterCompare_cmpB_pwm2");
	// 		}

	// 		if ((inst["mcpwmCounterCompare_cmpA_pwm3"] == 0  || inst["mcpwmCounterCompare_cmpB_pwm3"] == 0) 
	// 			&& 
	// 			(inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3A_shadowMode"] == true 
	// 			&& (inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3A_shadowEvent"] != "MCPWM_AQ_LOAD_FREEZE"))
	// 			||
	// 			(inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3B_shadowMode"] == true 
	// 			&& (inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3B_shadowEvent"] != "MCPWM_AQ_LOAD_FREEZE")))
	// 		{
	// 			validation.logWarning(name, inst, "mcpwmCounterCompare_cmpA_pwm3");
	// 			validation.logWarning(name, inst, "mcpwmCounterCompare_cmpB_pwm3");
	// 		}

	// 	},
	// 		devices : ["F28E12x"]
	// 	},

	// Validation #3
	{
		type : validation_warning,
		name :  "Unused action set for out of range event",
		func : (inst, validation, name) => {
			var noChangeOutput = "MCPWM_AQ_OUTPUT_NO_CHANGE";
			var mcpwm_outX = ["1A", "1B", "2A", "2B", "3A", "3B"];
			if (inst["mcpwmTimebase_counterMode"] == "MCPWM_COUNTER_MODE_DOWN") 
			{
				for (var mcpwm_out of mcpwm_outX)
				{
					if (inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_" + mcpwm_out + "_ON_TIMEBASE_UP_CMPA"]
						!= noChangeOutput)
					{
						validation.logWarning(name, inst, "mcpwmActionQualifier_MCPWM_AQ_OUTPUT_" + mcpwm_out + "_ON_TIMEBASE_UP_CMPA");
					}
					if (inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_" + mcpwm_out + "_ON_TIMEBASE_UP_CMPB"]
						!= noChangeOutput)
					{
						validation.logWarning(name, inst, "mcpwmActionQualifier_MCPWM_AQ_OUTPUT_" + mcpwm_out + "_ON_TIMEBASE_UP_CMPB");
					}
				}
			}
			else if (inst["mcpwmTimebase_counterMode"] == "MCPWM_COUNTER_MODE_UP") 
			{
				for (var mcpwm_out of mcpwm_outX)
				{
					if (inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_" + mcpwm_out + "_ON_TIMEBASE_DOWN_CMPA"]
						!= noChangeOutput)
					{
						validation.logWarning(name, inst, "mcpwmActionQualifier_MCPWM_AQ_OUTPUT_" + mcpwm_out + "_ON_TIMEBASE_DOWN_CMPA");
					}
					if (inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_" + mcpwm_out + "_ON_TIMEBASE_DOWN_CMPB"]
						!= noChangeOutput)
					{
						validation.logWarning(name, inst, "mcpwmActionQualifier_MCPWM_AQ_OUTPUT_" + mcpwm_out + "_ON_TIMEBASE_DOWN_CMPB");
					}
				}
			}
			
		},
			devices : ["F28E12x"]
		},

	// Validation #4
	{
		type : validation_error,
		name :  "Input value is out of range (16-bit value)",
		func : (inst, validation, name) => {
			if (inst["mcpwmCounterCompare_cmpA"] < 0 ||
				inst["mcpwmCounterCompare_cmpA"] > 65535) 
			{
				validation.logError(name, inst, "mcpwmCounterCompare_cmpA");
			}
			if (inst["mcpwmCounterCompare_cmpB"] < 0 ||
				inst["mcpwmCounterCompare_cmpB"] > 65535) 
			{
				validation.logError(name, inst, "mcpwmCounterCompare_cmpB");
			}
			if (inst["mcpwmCounterCompare_cmpA_pwm2"] < 0 ||
				inst["mcpwmCounterCompare_cmpA_pwm2"] > 65535) 
			{
				validation.logError(name, inst, "mcpwmCounterCompare_cmpA_pwm2");
			}
			if (inst["mcpwmCounterCompare_cmpB_pwm2"] < 0 ||
				inst["mcpwmCounterCompare_cmpB_pwm2"] > 65535) 
			{
				validation.logError(name, inst, "mcpwmCounterCompare_cmpB_pwm2");
			}
			if (inst["mcpwmCounterCompare_cmpA_pwm3"] < 0 ||
				inst["mcpwmCounterCompare_cmpA_pwm3"] > 65535) 
			{
				validation.logError(name, inst, "mcpwmCounterCompare_cmpA_pwm3");
			}
			if (inst["mcpwmCounterCompare_cmpB_pwm3"] < 0 ||
				inst["mcpwmCounterCompare_cmpB_pwm3"] > 65535) 
			{
				validation.logError(name, inst, "mcpwmCounterCompare_cmpB_pwm3");
			}
			if (inst["mcpwmCounterCompare_cmpC"] < 0 ||
				inst["mcpwmCounterCompare_cmpC"] > 65535)  
			{
				validation.logError(name, inst, "mcpwmCounterCompare_cmpC");
			}
			if (inst["mcpwmCounterCompare_cmpD"] < 0 ||
				inst["mcpwmCounterCompare_cmpD"] > 65535) 
			{
				validation.logError(name, inst, "mcpwmCounterCompare_cmpD");
			}
			// Time Base
			if (inst["mcpwmTimebase_period"] < 0 ||
				inst["mcpwmTimebase_period"] > 65535) 
			{
				validation.logError(name, inst, "mcpwmTimebase_period");
			}
			if (inst["mcpwmTimebase_phaseShift"] < 0 ||
				inst["mcpwmTimebase_phaseShift"] > 65535)  
			{
				validation.logError(name, inst, "mcpwmTimebase_phaseShift");
			}
		},
		devices : ["F28E12x"]
		},

    // Validation #5
	{
		type : validation_error,
		name :  "Input value is out of range (14-bit value)",
		func : (inst, validation, name) => {
			if (inst["mcpwmDeadband_delayRED"] < 0 ||
				inst["mcpwmDeadband_delayRED"] > 16384) 
			{
				validation.logError(name, inst, "mcpwmDeadband_delayRED");
			}
			if (inst["mcpwmDeadband_delayFED"] < 0 ||
				inst["mcpwmDeadband_delayFED"] > 16384) 
			{
				validation.logError(name, inst, "mcpwmDeadband_delayFED");
			}
		},
		devices : ["F28E12x"]
		},

    // Validation #7
	{
		type : validation_info,
		name :  "For the condition to remain latched, a minimum of 3*TBCLK sync pulse width is required.",
		func : (inst, validation, name) => {
			if(inst["mcpwmTripZone_oneShotSource"].length >= 1)
			{
				validation.logInfo(name, inst, "mcpwmTripZone_oneShotSource");
			}
			if(inst["mcpwmTripZone_cbcSource"].length >= 1)
			{
				validation.logInfo(name, inst, "mcpwmTripZone_cbcSource");
			}
		},
		devices : ["F28E12x"]
		},

	// Validation #10
	{
		type : validation_error,
		name :  "If RED/FED both applied to output B, output A will be invalid unless output A is MCPWMxA (S1) or output A is Bpath (S6)",
		func : (inst, validation, name) => {
			if (inst["mcpwmDeadband_inputFED"] == "MCPWM_DB_INPUT_DB_RED" && (inst["mcpwmDeadband_outputSwapOutA"] != true && inst["mcpwmDeadband_enableRED"] == true))
			{
		         validation.logError(name, inst, "mcpwmDeadband_inputFED");
			}
		},
		devices : ["F28E12x"]
		},

    // Validation #11
	{
		type : validation_warning,
		name :  "Clearing the phase shift enable will cause the MCPWM module to ignore the synchronization input pulse, if any.",
		func : (inst, validation, name) => {
			if (inst["mcpwmTimebase_phaseEnable"] == 0 && inst["mcpwmTimebase_phaseShift"] > 0)
			{
		         validation.logWarning(name, inst, "mcpwmTimebase_phaseShift");
			}

		},
		devices : ["F28E12x"]
		},

    // Validation #12
	{
		type : validation_info,
		name :  "For perfectly synchronized TBCLKs across multiple MCPWM modules, the prescaler bits in the TBCTL register of each MCPWM module must be set identically",
		func : (inst, validation, name) => {
		        validation.logInfo(name, inst, "mcpwmTimebase_clockDiv");

		},
		devices : ["F28E12x"]
		},

    // Validation #13
	{
		type : validation_info,
		name :  "Shadow to active load event selection bits for individual shadowed registers will be ignored and global load mode takes effect for registers with global load enabled",
		func : (inst, validation, name) => {
			if (inst["mcpwmGlobalLoad_gld"] == 1)
			{
		        validation.logInfo(name, inst, "mcpwmGlobalLoad_gld");
		    }

		},
		devices : ["F28E12x"]
		},

	// Validation #14
	{
		type : validation_warning,
		name :  "The SYNCEVT signal is only propagated through when PHSEN is SET.",
		func : (inst, validation, name) => {
			if (inst["mcpwmGlobalLoad_gld"] == 1 && (inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_SYNC" || inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_ZERO" 
				|| inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_PERIOD" || inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD") && 
				inst["mcpwmTimebase_phaseEnable"] == 1 && inst["mcpwmTimebase_phaseShift"] == 0)
			{
		        validation.logWarning(name, inst, "mcpwmGlobalLoad_gldMode");
		    }

		},
		devices : ["F28E12x"]
		},

	// Validation #16
	{
		type : validation_info,
		name :  "When PWMxB is derived from PWMxA using the DEDB_MODE bit and by delaying rising edge and falling edge by the phase shift amount, if the duty cycle value on PWMxA is less than this phase shift amount, PWMxA's falling edge has precedence over the delayed rising edge for PWMxB. It is recommended to make sure the duty cycle value of the current waveform fed to the deadband module is greater than the required phase shift amount.",
		func : (inst, validation, name) => {
			if (inst["mcpwmDeadband_inputRED"] == "MCPWM_DB_INPUT_MCPWMA" && inst["mcpwmDeadband_inputFED"] == "MCPWM_DB_INPUT_DB_RED" && inst["mcpwmDeadband_enableRED"] == 1 && inst["mcpwmDeadband_delayRED"] != 0)
			{
		        validation.logInfo(name, inst, "mcpwmDeadband_delayRED");
		    }
		},
		devices : ["F28E12x"]
		},

	// Validation #19
	{
		type : validation_error,
		name :  "Count down direction with a phase value of 0 and in up-down counter mode is invalid.",
		func : (inst, validation, name) => {
			if (inst["mcpwmTimebase_phaseEnable"] == true && inst["mcpwmTimebase_phaseShift"] == 0 && inst["mcpwmTimebase_counterMode"] == "MCPWM_COUNTER_MODE_UP_DOWN" 
				&& inst["mcpwmTimebase_counterModeAfterSync"] == "MCPWM_COUNT_MODE_DOWN_AFTER_SYNC")
			{
		         validation.logError(name, inst, "mcpwmTimebase_counterMode");
			}

		},
		devices : ["F28E12x"]
		},

	// Validation #22
	{
		type : validation_info,
		name :  "When DBRED/DBFED active is loaded with a new shadow value while DB counters are counting, the new DBRED / DBFED value only affects the NEXT PWMx edge and not the current edge.",
		func : (inst, validation, name) => {
			if (inst["mcpwmDeadband_redShadowMode"] ==1)
			{
		         validation.logInfo(name, inst, "mcpwmDeadband_redShadowMode");
			}
			if (inst["mcpwmDeadband_fedShadowMode"] ==1)
			{
		         validation.logInfo(name, inst, "mcpwmDeadband_fedShadowMode");
			}
		},
		devices : ["F28E12x"]
		},

	// Validation #23
	{
		type : validation_error,
		name :  "A deadband value of ZERO should not be used when the Global Shadow to Active Load is set to occur at CTR=ZERO",
		func : (inst, validation, name) => {
			
			if (inst["mcpwmDeadband_enableRED"] == 1 && inst["mcpwmDeadband_delayRED"] == 0 && inst["mcpwmGlobalLoad_gld"] ==1 
				&& (inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_CNTR_ZERO" ||
				inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD" ||
				inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD"))
			{
		         validation.logError(name, inst, "mcpwmDeadband_delayRED");
			}
			if (inst["mcpwmDeadband_enableFED"] == 1 && inst["mcpwmDeadband_delayFED"] == 0 && inst["mcpwmGlobalLoad_gld"] ==1 
				&& (inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_CNTR_ZERO" ||
				inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD" ||
				inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD"))
			{
		         validation.logError(name, inst, "mcpwmDeadband_delayFED");
			}
		},
		devices : ["F28E12x"]
		},

	// Validation #24
	{
		type : validation_error,
		name :  "A deadband value of PERIOD should not be used when the Global Shadow to Active Load is set to occur at CTR=PRD",
		func : (inst, validation, name) => {
			if (inst["mcpwmDeadband_enableRED"] == 1 && inst["mcpwmDeadband_delayRED"] == inst["mcpwmTimebase_period"] && inst["mcpwmGlobalLoad_gld"] ==1 
				&& (inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_CNTR_PERIOD" ||
				inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD"))
			{
		         validation.logError(name, inst, "mcpwmDeadband_delayRED");
			}
			if (inst["mcpwmDeadband_enableFED"] == 1 && inst["mcpwmDeadband_delayFED"] == inst["mcpwmTimebase_period"] && inst["mcpwmGlobalLoad_gld"] ==1 
				&& (inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_CNTR_PERIOD" ||
				inst["mcpwmGlobalLoad_gldMode"] == "MCPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD"))
			{
		         validation.logError(name, inst, "mcpwmDeadband_delayFED");
			}
		},
		devices : ["F28E12x"]
		},

	// Validation #25
	{
		type : validation_info,
		name :  "The one-shot trip condition must be cleared manually by writing to the TZCBCOSTCLR[OSTx] bit.",
		func : (inst, validation, name) => {
			if (inst["mcpwmTripZone_oneShotSource"] !=0)
			{
		         validation.logInfo(name, inst, "mcpwmTripZone_oneShotSource");
			}
		},
		devices : ["F28E12x"]
		},

	// Validation #31
	{
		type : validation_info,
		name :  "If the MCPWMxSYNCI signal is held HIGH, the sync will NOT continously occur. The MCPWMxSYNCI is rising edge activated.",
		func : (inst, validation, name) => {
			if (inst["mcpwmTimebase_phaseEnable"] == 1 && inst["mcpwmTimebase_phaseShift"] > 0)
			{
				validation.logInfo(name, inst, "mcpwmTimebase_phaseEnable");
			}
		},
		devices : ["F28E12x"]
		},

	// Validation #66
		{
		type : validation_warning,
		name :  "When global loading is enabled and the one-shot mode feature is used, a one-shot pulse must be declared at the end of initialization in order for the content in the shadow registers to move to the active registers",
		func : (inst, validation, name) => {
			if (inst["mcpwmGlobalLoad_gld"] == true && inst["mcpwmGlobalLoad_enableOneShot"] == true && inst["mcpwmGlobalLoad_oneShotMode"] == false)
			{
				validation.logWarning(name, inst, "mcpwmGlobalLoad_oneShotMode");
			}
		},
		devices : ["F28E12x"]
		},
	// Validation #67
		{
		type : validation_warning,
		name :  "When global loading is enabled and the one-shot mode feature is used, shadow loading for AQCTLx needs to be enabled in order to move initialized content from shadow to active registers",
		func : (inst, validation, name) => {
			if (inst["mcpwmGlobalLoad_gld"] == true && inst["mcpwmGlobalLoad_enableOneShot"] == true && 
			(inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1A_shadowMode"] == false || 
	 		 inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1B_shadowMode"] == false || 
			 inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2A_shadowMode"] == false || 
			 inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2B_shadowMode"] == false || 
			 inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3A_shadowMode"] == false || 
			 inst["mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3B_shadowMode"] == false))
			{
				validation.logWarning(name, inst, "mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1A_shadowMode");
				validation.logWarning(name, inst, "mcpwmActionQualifier_MCPWM_AQ_OUTPUT_1B_shadowMode");
				validation.logWarning(name, inst, "mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2A_shadowMode");
				validation.logWarning(name, inst, "mcpwmActionQualifier_MCPWM_AQ_OUTPUT_2B_shadowMode");
				validation.logWarning(name, inst, "mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3A_shadowMode");
				validation.logWarning(name, inst, "mcpwmActionQualifier_MCPWM_AQ_OUTPUT_3B_shadowMode");
			}
		},
		devices : ["F28E12x"]
		},
	// Validation #68
		{
		type : validation_warning,
		name :  "When global loading is enabled, the global load strobe period needs to be specified in order for the global loading to occur",
		func : (inst, validation, name) => {
			if (inst["mcpwmGlobalLoad_gld"] == true && inst["mcpwmGlobalLoad_enableOneShot"] == false && inst["mcpwmGlobalLoad_gldPeriod"] == "0")
			{
				validation.logWarning(name, inst, "mcpwmGlobalLoad_gldPeriod");
			}
		},
		devices : ["F28E12x"]
		},
]

exports = {
	validation_error : validation_error,
	validation_warning : validation_warning,
	validation_info : validation_info,
	mcpwm_validation : mcpwm_validation,
}
