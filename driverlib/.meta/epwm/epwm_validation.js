let Common   = system.getScript("/driverlib/Common.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_epwm.js");

var validation_warning = "warning"
var validation_error = "error"
var validation_info = "info"
var mindb_icl_xbar_map = {
 "XBAR_INPUT1": "EPWM_MINDB_SEL_OUTXBAR_OUT1" ,
 "XBAR_INPUT2": "EPWM_MINDB_SEL_OUTXBAR_OUT2" ,
 "XBAR_INPUT3": "EPWM_MINDB_SEL_OUTXBAR_OUT3" ,
 "XBAR_INPUT4": "EPWM_MINDB_SEL_OUTXBAR_OUT4" ,
 "XBAR_INPUT5": "EPWM_MINDB_SEL_OUTXBAR_OUT5" ,
 "XBAR_INPUT6": "EPWM_MINDB_SEL_OUTXBAR_OUT6" ,
 "XBAR_INPUT7": "EPWM_MINDB_SEL_OUTXBAR_OUT7" ,
 "XBAR_INPUT8": "EPWM_MINDB_SEL_OUTXBAR_OUT8" ,
 "XBAR_INPUT9": "EPWM_MINDB_SEL_OUTXBAR_OUT9" ,
 "XBAR_INPUT10" : "EPWM_MINDB_SEL_OUTXBAR_OUT10" ,
 "XBAR_INPUT11" : "EPWM_MINDB_SEL_OUTXBAR_OUT11" ,
 "XBAR_INPUT12" : "EPWM_MINDB_SEL_OUTXBAR_OUT12" ,
 "XBAR_INPUT13" : "EPWM_MINDB_SEL_OUTXBAR_OUT13" ,
 "XBAR_INPUT14" : "EPWM_MINDB_SEL_OUTXBAR_OUT14" ,
 "XBAR_INPUT15" : "EPWM_MINDB_SEL_OUTXBAR_OUT15" ,
 "EPWM_MINDB_SEL_OUTXBAR_OUT1" : "XBAR_INPUT1",
 "EPWM_MINDB_SEL_OUTXBAR_OUT2" : "XBAR_INPUT2",
 "EPWM_MINDB_SEL_OUTXBAR_OUT3" : "XBAR_INPUT3",
 "EPWM_MINDB_SEL_OUTXBAR_OUT4" : "XBAR_INPUT4",
 "EPWM_MINDB_SEL_OUTXBAR_OUT5" : "XBAR_INPUT5",
 "EPWM_MINDB_SEL_OUTXBAR_OUT6" : "XBAR_INPUT6",
 "EPWM_MINDB_SEL_OUTXBAR_OUT7" : "XBAR_INPUT7",
 "EPWM_MINDB_SEL_OUTXBAR_OUT8" : "XBAR_INPUT8",
 "EPWM_MINDB_SEL_OUTXBAR_OUT9" : "XBAR_INPUT9",
 "EPWM_MINDB_SEL_OUTXBAR_OUT10" : "XBAR_INPUT10",
 "EPWM_MINDB_SEL_OUTXBAR_OUT11" : "XBAR_INPUT11",
 "EPWM_MINDB_SEL_OUTXBAR_OUT12" : "XBAR_INPUT12",
 "EPWM_MINDB_SEL_OUTXBAR_OUT13" : "XBAR_INPUT13",
 "EPWM_MINDB_SEL_OUTXBAR_OUT14" : "XBAR_INPUT14",
 "EPWM_MINDB_SEL_OUTXBAR_OUT15" : "XBAR_INPUT15"
};
var icl_mindb_xbar_map = {
 "XBAR_INPUT1" : "EPWM_MINDB_ICL_XBAR_OUT1",
 "XBAR_INPUT2" : "EPWM_MINDB_ICL_XBAR_OUT2",
 "XBAR_INPUT3" : "EPWM_MINDB_ICL_XBAR_OUT3",
 "XBAR_INPUT4" : "EPWM_MINDB_ICL_XBAR_OUT4",
 "XBAR_INPUT5" : "EPWM_MINDB_ICL_XBAR_OUT5",
 "XBAR_INPUT6" : "EPWM_MINDB_ICL_XBAR_OUT6",
 "XBAR_INPUT7" : "EPWM_MINDB_ICL_XBAR_OUT7",
 "XBAR_INPUT8" : "EPWM_MINDB_ICL_XBAR_OUT8",
 "XBAR_INPUT9" : "EPWM_MINDB_ICL_XBAR_OUT9",
 "XBAR_INPUT10" : "EPWM_MINDB_ICL_XBAR_OUT10",
 "XBAR_INPUT11" : "EPWM_MINDB_ICL_XBAR_OUT11",
 "XBAR_INPUT12" : "EPWM_MINDB_ICL_XBAR_OUT12",
 "XBAR_INPUT13" : "EPWM_MINDB_ICL_XBAR_OUT13",
 "XBAR_INPUT14" : "EPWM_MINDB_ICL_XBAR_OUT14",
 "XBAR_INPUT15" : "EPWM_MINDB_ICL_XBAR_OUT15",
 "XBAR_INPUT16" : "EPWM_MINDB_ICL_XBAR_OUT16",
 "EPWM_MINDB_ICL_XBAR_OUT1" : "XBAR_INPUT1", 
 "EPWM_MINDB_ICL_XBAR_OUT2" : "XBAR_INPUT2", 
 "EPWM_MINDB_ICL_XBAR_OUT3" : "XBAR_INPUT3", 
 "EPWM_MINDB_ICL_XBAR_OUT4" : "XBAR_INPUT4", 
 "EPWM_MINDB_ICL_XBAR_OUT5" : "XBAR_INPUT5", 
 "EPWM_MINDB_ICL_XBAR_OUT6" : "XBAR_INPUT6", 
 "EPWM_MINDB_ICL_XBAR_OUT7" : "XBAR_INPUT7", 
 "EPWM_MINDB_ICL_XBAR_OUT8" : "XBAR_INPUT8", 
 "EPWM_MINDB_ICL_XBAR_OUT9" : "XBAR_INPUT9", 
 "EPWM_MINDB_ICL_XBAR_OUT10" : "XBAR_INPUT10",
 "EPWM_MINDB_ICL_XBAR_OUT11" : "XBAR_INPUT11", 
 "EPWM_MINDB_ICL_XBAR_OUT12" : "XBAR_INPUT12", 
 "EPWM_MINDB_ICL_XBAR_OUT13" : "XBAR_INPUT13", 
 "EPWM_MINDB_ICL_XBAR_OUT14" : "XBAR_INPUT14", 
 "EPWM_MINDB_ICL_XBAR_OUT15" : "XBAR_INPUT15", 
 "EPWM_MINDB_ICL_XBAR_OUT16" : "XBAR_INPUT16" 
};
var epwm_validation = [
	// Validation #1
	{
		type : validation_warning,
		name :  "CMP value is out of range of TBPRD. Refer to table, Behavior if CMPA/CMPB is Greater than the Period, within the TRM",
		func : (inst, validation, name) => {
			if (inst["epwmTimebase_period"] < 
				inst["epwmCounterCompare_cmpA"]) 
			{
				validation.logWarning(name, inst, "epwmCounterCompare_cmpA");
			}
			if (inst["epwmTimebase_period"] < 
				inst["epwmCounterCompare_cmpB"]) 
			{
				validation.logWarning(name, inst, "epwmCounterCompare_cmpB");
			}
			if (inst["epwmTimebase_period"] < 
				inst["epwmCounterCompare_cmpC"]) 
			{
				validation.logWarning(name, inst, "epwmCounterCompare_cmpC");
			}
			if (inst["epwmTimebase_period"] < 
				inst["epwmCounterCompare_cmpD"]) 
			{
				validation.logWarning(name, inst, "epwmCounterCompare_cmpD");
			}
			
		},
			devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"

			]
		},

    // Validation #2
	{
		type : validation_warning,
		name :  "It is recommended to use a non-zero counter compare value when using shadow to active load of action qualifier A/B control register on TBCTR=0 boundary",
		func : (inst, validation, name) => {
			if ((inst["epwmCounterCompare_cmpA"] == 0  || inst["epwmCounterCompare_cmpB"] == 0) 
				&& inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_shadowMode"] == 1 
				&& (inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_shadowEvent"] == "EPWM_AQ_LOAD_ON_CNTR_ZERO" || 
					inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_shadowEvent"] == "EPWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD" ||
					inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_shadowEvent"] == "EPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO" ||
					inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_shadowEvent"] == "EPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO_PERIOD"))
			{
				validation.logWarning(name, inst, "epwmCounterCompare_cmpA");
				validation.logWarning(name, inst, "epwmCounterCompare_cmpB");
			}
			if ((inst["epwmCounterCompare_cmpA"] == 0  || inst["epwmCounterCompare_cmpB"] == 0) 
				&& inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_shadowMode"] == 1 
				&& (inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_shadowEvent"] == "EPWM_AQ_LOAD_ON_CNTR_ZERO" || 
					inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_shadowEvent"] == "EPWM_AQ_LOAD_ON_CNTR_ZERO_PERIOD" ||
					inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_shadowEvent"] == "EPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO" ||
					inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_shadowEvent"] == "EPWM_AQ_LOAD_ON_SYNC_CNTR_ZERO_PERIOD"))
			{
				validation.logWarning(name, inst, "epwmCounterCompare_cmpA");
				validation.logWarning(name, inst, "epwmCounterCompare_cmpB");
			}

		},
			devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #3
	{
		type : validation_warning,
		name :  "Unused action set for out of range event",
		func : (inst, validation, name) => {
			var noChangeOutput = "EPWM_AQ_OUTPUT_NO_CHANGE";
			var epwm_outX = ["A", "B"];
			if (inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_DOWN") 
			{
				for (var epwm_out of epwm_outX)
				{
					if (inst["epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_TIMEBASE_UP_CMPA"]
						!= noChangeOutput)
					{
						validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_TIMEBASE_UP_CMPA");
					}
					if (inst["epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_TIMEBASE_UP_CMPB"]
						!= noChangeOutput)
					{
						validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_TIMEBASE_UP_CMPB");
					}
					if (inst["epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_T1_COUNT_UP"]
						!= noChangeOutput)
					{
						validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_T1_COUNT_UP");
					}
				}
			}
			else if (inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP") 
			{
				for (var epwm_out of epwm_outX)
				{
					if (inst["epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_TIMEBASE_DOWN_CMPA"]
						!= noChangeOutput)
					{
						validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_TIMEBASE_DOWN_CMPA");
					}
					if (inst["epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_TIMEBASE_DOWN_CMPB"]
						!= noChangeOutput)
					{
						validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_TIMEBASE_DOWN_CMPB");
					}
					if (inst["epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_T1_COUNT_DOWN"]
						!= noChangeOutput)
					{
						validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_" + epwm_out + "_ON_T1_COUNT_DOWN");
					}
				}
			}
			
		},
			devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #4
	{
		type : validation_error,
		name :  "Input value is out of range (16-bit value)",
		func : (inst, validation, name) => {
			if (inst["epwmCounterCompare_cmpA"] < 0 ||
				inst["epwmCounterCompare_cmpA"] > 65535) 
			{
				validation.logError(name, inst, "epwmCounterCompare_cmpA");
			}
			if (inst["epwmCounterCompare_cmpB"] < 0 ||
				inst["epwmCounterCompare_cmpB"] > 65535) 
			{
				validation.logError(name, inst, "epwmCounterCompare_cmpB");
			}
			if (inst["epwmCounterCompare_cmpC"] < 0 ||
				inst["epwmCounterCompare_cmpC"] > 65535)  
			{
				validation.logError(name, inst, "epwmCounterCompare_cmpC");
			}
			if (inst["epwmCounterCompare_cmpD"] < 0 ||
				inst["epwmCounterCompare_cmpD"] > 65535) 
			{
				validation.logError(name, inst, "epwmCounterCompare_cmpD");
			}
			// Digital Compare
			if (inst["epwmDigitalCompare_blankingWindowOffset"] < 0 ||
				inst["epwmDigitalCompare_blankingWindowOffset"] > 65535) 
			{
				validation.logError(name, inst, "epwmDigitalCompare_blankingWindowOffset");
			}
			if (inst["epwmDigitalCompare_blankingWindowLength"] < 0 ||
				inst["epwmDigitalCompare_blankingWindowLength"] > 65535) 
			{
				validation.logError(name, inst, "epwmDigitalCompare_blankingWindowLength");
			}
			if (inst["epwmDigitalCompare_SWVDELVAL"] < 0 ||
				inst["epwmDigitalCompare_SWVDELVAL"] > 65535)  
			{
				validation.logError(name, inst, "epwmDigitalCompare_SWVDELVAL");
			}
			// Time Base
			if (inst["epwmTimebase_counterValue"] < 0 ||
				inst["epwmTimebase_counterValue"] > 65535) 
			{
				validation.logError(name, inst, "epwmTimebase_counterValue");
			}
			if (inst["epwmTimebase_period"] < 0 ||
				inst["epwmTimebase_period"] > 65535) 
			{
				validation.logError(name, inst, "epwmTimebase_period");
			}
			if (inst["epwmTimebase_phaseShift"] < 0 ||
				inst["epwmTimebase_phaseShift"] > 65535)  
			{
				validation.logError(name, inst, "epwmTimebase_phaseShift");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

    // Validation #5
	{
		type : validation_error,
		name :  "Input value is out of range (14-bit value)",
		func : (inst, validation, name) => {
			if (inst["epwmDeadband_delayRED"] < 0 ||
				inst["epwmDeadband_delayRED"] > 16384) 
			{
				validation.logError(name, inst, "epwmDeadband_delayRED");
			}
			if (inst["epwmDeadband_delayFED"] < 0 ||
				inst["epwmDeadband_delayFED"] > 16384) 
			{
				validation.logError(name, inst, "epwmDeadband_delayFED");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #6
	{
		type : validation_error,
		name :  "Same event may not be chosen for the DC filter input source and the valley capture signal source",
		func : (inst, validation, name) => {
			if ((inst["epwmDigitalCompare_dcFilterInput"] == "EPWM_DC_WINDOW_SOURCE_DCAEVT1" && inst["epwmDigitalCompare_valleyCaptureSource"] == "EPWM_VALLEY_TRIGGER_EVENT_DCAEVT1") ||
		        (inst["epwmDigitalCompare_dcFilterInput"] == "EPWM_DC_WINDOW_SOURCE_DCAEVT2" && inst["epwmDigitalCompare_valleyCaptureSource"] == "EPWM_VALLEY_TRIGGER_EVENT_DCAEVT2") ||
		        (inst["epwmDigitalCompare_dcFilterInput"] == "EPWM_DC_WINDOW_SOURCE_DCBEVT1" && inst["epwmDigitalCompare_valleyCaptureSource"] == "EPWM_VALLEY_TRIGGER_EVENT_DCBEVT1") ||
		        (inst["epwmDigitalCompare_dcFilterInput"] == "EPWM_DC_WINDOW_SOURCE_DCBEVT2" && inst["epwmDigitalCompare_valleyCaptureSource"] == "EPWM_VALLEY_TRIGGER_EVENT_DCBEVT2"))
		    {
		         validation.logError(name, inst, "epwmDigitalCompare_dcFilterInput");
		         validation.logError(name, inst, "epwmDigitalCompare_valleyCaptureSource");
		    }

		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

    // Validation #7
	{
		type : validation_info,
		name :  "For the condition to remain latched, a minimum of 3*TBCLK sync pulse width is required.",
		func : (inst, validation, name) => {
			if(inst["epwmTripZone_oneShotSource"].length >= 1)
			{
				validation.logInfo(name, inst, "epwmTripZone_oneShotSource");
			}
			if(inst["epwmTripZone_cbcSource"].length >= 1)
			{
				validation.logInfo(name, inst, "epwmTripZone_cbcSource");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #8
	{
		type : validation_info,
		name :  "For the condition to remain latched, a minimum of 3*TBCLK sync pulse width is required.",
		func : (inst, validation, name) => {
			if(inst["epwmDigitalCompare_EPWM_DC_MODULE_A_EPWM_DC_EVENT_1_latchMode"] == "EPWM_DC_CBC_LATCH_ENABLED")
			{
				validation.logInfo(name, inst, "epwmDigitalCompare_EPWM_DC_MODULE_A_EPWM_DC_EVENT_1_latchMode");
			}
			if(inst["epwmDigitalCompare_EPWM_DC_MODULE_A_EPWM_DC_EVENT_2_latchMode"] == "EPWM_DC_CBC_LATCH_ENABLED")
			{
				validation.logInfo(name, inst, "epwmDigitalCompare_EPWM_DC_MODULE_A_EPWM_DC_EVENT_2_latchMode");
			}
			if(inst["epwmDigitalCompare_EPWM_DC_MODULE_B_EPWM_DC_EVENT_1_latchMode"] == "EPWM_DC_CBC_LATCH_ENABLED")
			{
				validation.logInfo(name, inst, "epwmDigitalCompare_EPWM_DC_MODULE_B_EPWM_DC_EVENT_1_latchMode");
			}
			if(inst["epwmDigitalCompare_EPWM_DC_MODULE_B_EPWM_DC_EVENT_2_latchMode"] == "EPWM_DC_CBC_LATCH_ENABLED")
			{
				validation.logInfo(name, inst, "epwmDigitalCompare_EPWM_DC_MODULE_B_EPWM_DC_EVENT_2_latchMode");
			}
		},
		devices : [
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

    // Validation #9
	{
		type : validation_info,
		name :  "If the blanking window crosses the CTR = 0 or CTR = PRD boundary, the next window still starts at the same offset value after the CTR = 0 or CTR = PRD pulse.",
		func : (inst, validation, name) => {
			if (inst["epwmDigitalCompare_useBlankingWindow"] == 1)
			{
		         validation.logInfo(name, inst, "epwmDigitalCompare_blankingWindowOffset");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #10
	{
		type : validation_error,
		name :  "If RED/FED both applied to output B, output A will be invalid unless output A is EPWMxA (S1) or output A is Bpath (S6)",
		func : (inst, validation, name) => {
			if (inst["epwmDeadband_inputFED"] == "EPWM_DB_INPUT_DB_RED" && (inst["epwmDeadband_outputSwapOutA"] != true && inst["epwmDeadband_enableRED"] == true))
			{
		         validation.logError(name, inst, "epwmDeadband_inputFED");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

    // Validation #11
	{
		type : validation_warning,
		name :  "Clearing the phase shift enable will cause the EPWM module to ignore the synchronization input pulse, if any.",
		func : (inst, validation, name) => {
			if (inst["epwmTimebase_phaseEnable"] == 0 && inst["epwmTimebase_phaseShift"] > 0)
			{
		         validation.logWarning(name, inst, "epwmTimebase_phaseShift");
			}

		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

    // Validation #12
	{
		type : validation_info,
		name :  "For perfectly synchronized TBCLKs across multiple EPWM modules, the prescaler bits in the TBCTL register of each EPWM module must be set identically",
		func : (inst, validation, name) => {
		        validation.logInfo(name, inst, "epwmTimebase_clockDiv");

		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

    // Validation #13
	{
		type : validation_info,
		name :  "Shadow to active load event selection bits for individual shadowed registers will be ignored and global load mode takes effect for registers with global load enabled",
		func : (inst, validation, name) => {
			if (inst["epwmGlobalLoad_gld"] == 1)
			{
		        validation.logInfo(name, inst, "epwmGlobalLoad_gld");
		    }

		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #14
	{
		type : validation_warning,
		name :  "The SYNCEVT signal is only propagated through when PHSEN is SET.",
		func : (inst, validation, name) => {
			if (inst["epwmGlobalLoad_gld"] == 1 && (inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC" || inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_ZERO" 
				|| inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_PERIOD" || inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD") && 
				inst["epwmTimebase_phaseEnable"] == 1 && inst["epwmTimebase_phaseShift"] == 0)
			{
		        validation.logWarning(name, inst, "epwmGlobalLoad_gldMode");
		    }

		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #15
	{
		type : validation_info,
		name :  "This counter compare value can only be used to generate an event in the event trigger submodule",
		func : (inst, validation, name) => {
			if (inst["epwmCounterCompare_cmpC"] != 0)
			{
		        validation.logInfo(name, inst, "epwmCounterCompare_cmpC");
		    }
		    if (inst["epwmCounterCompare_cmpD"] != 0)
			{
		        validation.logInfo(name, inst, "epwmCounterCompare_cmpD");
		    }

		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #16
	{
		type : validation_info,
		name :  "When PWMxB is derived from PWMxA using the DEDB_MODE bit and by delaying rising edge and falling edge by the phase shift amount, if the duty cycle value on PWMxA is less than this phase shift amount, PWMxA's falling edge has precedence over the delayed rising edge for PWMxB. It is recommended to make sure the duty cycle value of the current waveform fed to the deadband module is greater than the required phase shift amount.",
		func : (inst, validation, name) => {
			if (inst["epwmDeadband_inputRED"] == "EPWM_DB_INPUT_EPWMA" && inst["epwmDeadband_inputFED"] == "EPWM_DB_INPUT_DB_RED" && inst["epwmDeadband_enableRED"] == 1 && inst["epwmDeadband_delayRED"] != 0)
			{
		        validation.logInfo(name, inst, "epwmDeadband_delayRED");
		    }
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #17
	{
		type : validation_warning,
		name :  "If the CBC interrupt is enabled and DCAEVT2 or DCBEVT2 are selected as CBC trip sources, it is not necessary to also enable the DCAEVT2/DCBEVT2 interrupts.",
		func : (inst, validation, name) => {
			if (((inst["epwmTripZone_cbcSource"].includes("EPWM_TZ_SIGNAL_DCAEVT2") || inst["epwmTripZone_cbcSource"].includes("EPWM_TZ_SIGNAL_DCBEVT2")) && 
				(inst["epwmTripZone_tzInterruptSource"].includes("EPWM_TZ_INTERRUPT_DCAEVT2") || inst["epwmTripZone_tzInterruptSource"].includes("EPWM_TZ_INTERRUPT_DCBEVT2")) && 
				inst["epwmTripZone_tzInterruptSource"].includes("EPWM_TZ_INTERRUPT_CBC")))
			
			{
		        validation.logWarning(name, inst, "epwmTripZone_tzInterruptSource");
		    }
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #18
	{
		type : validation_warning,
		name :  "If the OSHT interrupt is enabled and DCAEVT1 or DCBEVT1 are selected as OSHT trip sources, it is not necessary to also enable the DCAEVT1/DCBEVT1 interrupts.",
		func : (inst, validation, name) => {
			if (((inst["epwmTripZone_oneShotSource"].includes("EPWM_TZ_SIGNAL_DCAEVT1") || inst["epwmTripZone_oneShotSource"].includes("EPWM_TZ_SIGNAL_DCBEVT1")) && 
				(inst["epwmTripZone_tzInterruptSource"].includes("EPWM_TZ_INTERRUPT_DCAEVT1") || inst["epwmTripZone_tzInterruptSource"].includes("EPWM_TZ_INTERRUPT_DCBEVT1")) && 
				inst["epwmTripZone_tzInterruptSource"].includes("EPWM_TZ_INTERRUPT_OST")))
			
			{
		        validation.logWarning(name, inst, "epwmTripZone_tzInterruptSource");
		    }
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #19
	{
		type : validation_error,
		name :  "Count down direction with a phase value of 0 and in up-down counter mode is invalid.",
		func : (inst, validation, name) => {
			if (inst["epwmTimebase_phaseEnable"] == true && inst["epwmTimebase_phaseShift"] == 0 && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP_DOWN" 
				&& inst["epwmTimebase_counterModeAfterSync"] == "EPWM_COUNT_MODE_DOWN_AFTER_SYNC")
			{
		         validation.logError(name, inst, "epwmTimebase_counterMode");
			}

		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #20
	{
		type : validation_info,
		name :  "T1/T2 selection and configuration of a trip/digital-compare event is indpendent of the configuration of that event in the Trip-Zone submodule",
		func : (inst, validation, name) => {
			if (inst["epwmActionQualifier_t1Source"] != "EPWM_AQ_TRIGGER_EVENT_TRIG_EPWM_SYNCIN")
			{
		         validation.logInfo(name, inst, "epwmActionQualifier_t1Source");
			}
			if (inst["epwmActionQualifier_t2Source"] != "EPWM_AQ_TRIGGER_EVENT_TRIG_EPWM_SYNCIN")
			{
		         validation.logInfo(name, inst, "epwmActionQualifier_t2Source");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #21
	{
		type : validation_warning,
		name :  "PWM Chopper will not be enabled when high-resolution dead-band is enabled",
		func : (inst, validation, name) => {
			if (inst["epwmChopper_useChopper"] ==1)
			{
		         validation.logWarning(name, inst, "epwmChopper_useChopper");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #22
	{
		type : validation_info,
		name :  "When DBRED/DBFED active is loaded with a new shadow value while DB counters are counting, the new DBRED / DBFED value only affects the NEXT PWMx edge and not the current edge.",
		func : (inst, validation, name) => {
			if (inst["epwmDeadband_redShadowMode"] ==1)
			{
		         validation.logInfo(name, inst, "epwmDeadband_redShadowMode");
			}
			if (inst["epwmDeadband_fedShadowMode"] ==1)
			{
		         validation.logInfo(name, inst, "epwmDeadband_fedShadowMode");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #23
	{
		type : validation_error,
		name :  "A deadband value of ZERO should not be used when the Global Shadow to Active Load is set to occur at CTR=ZERO",
		func : (inst, validation, name) => {
			if (inst["epwmDeadband_enableRED"] == 1 && inst["epwmDeadband_delayRED"] == 0 && inst["epwmDeadband_redGld"] ==1 
				&& (inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_CNTR_ZERO" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_ZERO" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD"))
			{
		         validation.logError(name, inst, "epwmDeadband_delayRED");
			}
			if (inst["epwmDeadband_enableFED"] == 1 && inst["epwmDeadband_delayFED"] == 0 && inst["epwmDeadband_fedGld"] ==1 
				&& (inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_CNTR_ZERO" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_ZERO" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD"))
			{
		         validation.logError(name, inst, "epwmDeadband_delayFED");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #24
	{
		type : validation_error,
		name :  "A deadband value of PERIOD should not be used when the Global Shadow to Active Load is set to occur at CTR=PRD",
		func : (inst, validation, name) => {
			if (inst["epwmDeadband_enableRED"] == 1 && inst["epwmDeadband_delayRED"] == inst["epwmTimebase_period"] && inst["epwmDeadband_redGld"] ==1 
				&& (inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_CNTR_PERIOD" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_PERIOD" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD"))
			{
		         validation.logError(name, inst, "epwmDeadband_delayRED");
			}
			if (inst["epwmDeadband_enableFED"] == 1 && inst["epwmDeadband_delayFED"] == inst["epwmTimebase_period"] && inst["epwmDeadband_fedGld"] ==1 
				&& (inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_CNTR_PERIOD" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_CNTR_ZERO_PERIOD" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC_OR_CNTR_PERIOD" ||
				inst["epwmGlobalLoad_gldMode"] == "EPWM_GL_LOAD_PULSE_SYNC_CNTR_ZERO_PERIOD"))
			{
		         validation.logError(name, inst, "epwmDeadband_delayFED");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #25
	{
		type : validation_info,
		name :  "The one-shot trip condition must be cleared manually by writing to the TZCLR[OST] bit.",
		func : (inst, validation, name) => {
			if (inst["epwmTripZone_oneShotSource"] !=0)
			{
		         validation.logInfo(name, inst, "epwmTripZone_oneShotSource");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #26
	{
		type : validation_error,
		name :  "The STOPEDGE value must be greater than the STARTEDGE value",
		func : (inst, validation, name) => {
			if (parseInt(inst["epwmDigitalCompare_stopValleyCaptureTriggerCount"]) <  parseInt(inst["epwmDigitalCompare_startValleyCaptureTriggerCount"]))
			{
		         validation.logError(name, inst, "epwmDigitalCompare_stopValleyCaptureTriggerCount");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #27
	{
		type : validation_warning,
		name :  "Errata Advisory: An ePWM glitch can occur if a trip remains active at the end of the Blanking Window",
		func : (inst, validation, name) => {
			if (inst["epwmDigitalCompare_useBlankingWindow"] && (inst["epwmTripZone_oneShotSource"] == "EPWM_TZ_SIGNAL_DCAEVT1" || 
				inst["epwmTripZone_oneShotSource"] == "EPWM_TZ_SIGNAL_DCBEVT1"))
			{
		         validation.logWarning(name, inst, "epwmTripZone_oneShotSource");
			}
			if (inst["epwmDigitalCompare_useBlankingWindow"] && (inst["epwmTripZone_cbcSource"] == "EPWM_TZ_SIGNAL_DCAEVT2" || 
				inst["epwmTripZone_oneShotSource"] == "EPWM_TZ_SIGNAL_DCBEVT2"))
			{
		         validation.logWarning(name, inst, "epwmTripZone_cbcSource");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #28
	{
		type : validation_error,
		name :  "Errata Advisory: ePWM Dead-Band Delay Value Cannot be Set to 0 When Using Shadow Load Mode for RED/FED",
		func : (inst, validation, name) => {
			if (inst["epwmDeadband_enableRED"] && inst["epwmDeadband_delayRED"] == "0" && inst["epwmDeadband_redShadowMode"])
			{
		         validation.logError(name, inst, "epwmDeadband_delayRED");
			}
			if (inst["epwmDeadband_enableFED"] && inst["epwmDeadband_delayFED"] == "0" && inst["epwmDeadband_fedShadowMode"])
			{
		         validation.logError(name, inst, "epwmDeadband_delayFED");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28P65x"
			]
		},

	// Validation #29
	{
		type : validation_warning,
		name :  "Errata Advisory: Trip Events Will Not be Filtered by the Blanking Window for the First 3 Cycles After the Start of a Blanking Window",
		func : (inst, validation, name) => {
			if (inst["epwmDigitalCompare_useBlankingWindow"] == 1)
			{
		         validation.logWarning(name, inst, "epwmDigitalCompare_blankingWindowOffset");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #30
	{
		type : validation_info,
		name :  "Errata Advisory: Event Latch(DCxEVTxLAT) of DC Event-Based CBC Trip May not Extend Trigger Pulse as Expected When Asynchronous Path is Selected",
		func : (inst, validation, name) => {
			if (inst["epwmDigitalCompare_EPWM_DC_MODULE_A_EPWM_DC_EVENT_1_latchMode"] == "EPWM_DC_CBC_LATCH_ENABLED" && inst["epwmDigitalCompare_EPWM_DC_MODULE_A_EPWM_DC_EVENT_1_eventSync"] == "EPWM_DC_EVENT_INPUT_NOT_SYNCED")
			{
				validation.logInfo(name, inst, "epwmDigitalCompare_EPWM_DC_MODULE_A_EPWM_DC_EVENT_1_latchMode");
			}
			if (inst["epwmDigitalCompare_EPWM_DC_MODULE_A_EPWM_DC_EVENT_2_latchMode"] == "EPWM_DC_CBC_LATCH_ENABLED" && inst["epwmDigitalCompare_EPWM_DC_MODULE_A_EPWM_DC_EVENT_2_eventSync"] == "EPWM_DC_EVENT_INPUT_NOT_SYNCED")
			{
				validation.logInfo(name, inst, "epwmDigitalCompare_EPWM_DC_MODULE_A_EPWM_DC_EVENT_2_latchMode");
			}
			if (inst["epwmDigitalCompare_EPWM_DC_MODULE_B_EPWM_DC_EVENT_1_latchMode"] == "EPWM_DC_CBC_LATCH_ENABLED" && inst["epwmDigitalCompare_EPWM_DC_MODULE_B_EPWM_DC_EVENT_1_eventSync"] == "EPWM_DC_EVENT_INPUT_NOT_SYNCED")
			{
				validation.logInfo(name, inst, "epwmDigitalCompare_EPWM_DC_MODULE_B_EPWM_DC_EVENT_1_latchMode");
			}
			if (inst["epwmDigitalCompare_EPWM_DC_MODULE_B_EPWM_DC_EVENT_2_latchMode"] == "EPWM_DC_CBC_LATCH_ENABLED" && inst["epwmDigitalCompare_EPWM_DC_MODULE_B_EPWM_DC_EVENT_2_eventSync"] == "EPWM_DC_EVENT_INPUT_NOT_SYNCED")
			{
				validation.logInfo(name, inst, "epwmDigitalCompare_EPWM_DC_MODULE_B_EPWM_DC_EVENT_2_latchMode");
			}
		},
		devices : [
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #31
	{
		type : validation_info,
		name :  "If the EPWMxSYNCI signal is held HIGH, the sync will NOT continously occur. The EPWMxSYNCI is rising edge activated.",
		func : (inst, validation, name) => {
			if (inst["epwmTimebase_phaseEnable"] == 1 && inst["epwmTimebase_phaseShift"] > 0)
			{
				validation.logInfo(name, inst, "epwmTimebase_phaseEnable");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #32
	{
		type : validation_info,
		name :  "Conflicting actions on the TZCTL, TZCTL2, TZCTLDCA or TZCTLDCB registers. Refer to the TRM for the priority scheme.",
		func : (inst, validation, name) => {
			if (inst["epwmTripZone_useAdvancedEPWMTripZoneActions"] == 0 && (inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_TZA"] != inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_DCAEVT1"] 
				|| inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_TZA"] != inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_DCAEVT2"] || inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_DCAEVT1"] != 
				inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_DCAEVT2"]))
			{
				validation.logInfo(name, inst, "epwmTripZone_EPWM_TZ_ACTION_EVENT_TZA");
			}
			if (inst["epwmTripZone_useAdvancedEPWMTripZoneActions"] == 1 && (inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZA_U"] != inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U_A"] 
				|| inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZA_U"] != inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U_A"] || inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U_A"] != 
				inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U_A"]))
			{
				validation.logInfo(name, inst, "epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZA_U");
			}
			if (inst["epwmTripZone_useAdvancedEPWMTripZoneActions"] == 1 && (inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZA_D"] != inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D_A"] 
				|| inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZA_D"] != inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D_A"] || inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D_A"] != 
				inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D_A"]))
			{
				validation.logInfo(name, inst, "epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZA_D");
			}
			if (inst["epwmTripZone_useAdvancedEPWMTripZoneActions"] == 0 && (inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_TZB"] != inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_DCBEVT1"] 
				|| inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_TZB"] != inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_DCBEVT2"] || inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_DCBEVT1"] != 
				inst["epwmTripZone_EPWM_TZ_ACTION_EVENT_DCBEVT2"]))
			{
				validation.logInfo(name, inst, "epwmTripZone_EPWM_TZ_ACTION_EVENT_TZB");
			}
			if (inst["epwmTripZone_useAdvancedEPWMTripZoneActions"] == 1 && (inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZB_U"] != inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U_B"] 
				|| inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZB_U"] != inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U_B"] || inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_U_B"] != 
				inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_U_B"]))
			{
				validation.logInfo(name, inst, "epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZB_U");
			}
			if (inst["epwmTripZone_useAdvancedEPWMTripZoneActions"] == 1 && (inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZB_D"] != inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D_B"] 
				|| inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZB_D"] != inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D_B"] || inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT1_D_B"] != 
				inst["epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_DCxEVT2_D_B"]))
			{
				validation.logInfo(name, inst, "epwmTripZone_EPWM_TZ_ADV_ACTION_EVENT_TZB_D");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #33
	{
		type : validation_error,
		name :  "Input value is out of range (8-bit value)",
		func : (inst, validation, name) => {
			if (inst["hrpwm_cmpaHR"] < 0 || inst["hrpwm_cmpaHR"] > 256) 
			{
				validation.logError(name, inst, "hrpwm_cmpaHR");
			}
			if (inst["hrpwm_cmpbHR"] < 0 || inst["hrpwm_cmpbHR"] > 256) 
			{
				validation.logError(name, inst, "hrpwm_cmpbHR");
			}
			if (inst["hrpwm_tbprdHR"] < 0 || inst["hrpwm_tbprdHR"] > 256) 
			{
				validation.logError(name, inst, "hrpwm_tbprdHR");
			}
			if (inst["hrpwm_tbphsHR"] < 0 || inst["hrpwm_tbphsHR"] > 256) 
			{
				validation.logError(name, inst, "hrpwm_tbphsHR");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #34
	{
		type : validation_error,
		name :  "Input value is out of range (7-bit value)",
		func : (inst, validation, name) => {
			if (inst["hrpwm_DBredHR"] < 0 || inst["hrpwm_DBredHR"] > 128) 
			{
				validation.logError(name, inst, "hrpwm_DBredHR");
			}
			if (inst["hrpwm_DBfedHR"] < 0 || inst["hrpwm_DBfedHR"] > 128) 
			{
				validation.logError(name, inst, "hrpwm_DBfedHR");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #35
	{
		type : validation_warning,
		name :  "In HR mode, if CTRMODE= up count mode, the DBFEDHR and DBREDHR registers are not supported",
		func : (inst, validation, name) => {
			if (inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP" && inst["hrpwm_enable"] == true) 
			{
				validation.logWarning(name, inst, "hrpwm_edgeModeDB");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #36
	{
		type : validation_error,
		name :  "Auto-conversion must always be enabled for high resolution period mode",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && inst["hrpwm_autoConv"] == false && (inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" || inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL")) 
			{
				validation.logError(name, inst, "hrpwm_periodEnable");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #37
	{
		type : validation_info,
		name :  "The PWM Chopper will not be enabled when high-resolution deadband is enabled",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["epwmChopper_useChopper"] == true && inst["hrpwm_edgeModeDB"] != "HRPWM_DB_MEP_CTRL_DISABLE") 
			{
				validation.logInfo(name, inst, "epwmChopper_useChopper");
				validation.logInfo(name, inst, "hrpwm_edgeModeDB");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #38
	{
		type : validation_error,
		name :  "High-resolution dead-band RED and FED requires Half-Cycle clocking mode (DBCTL[HALFCYCLE] = 1)",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_edgeModeDB"] != "HRPWM_DB_MEP_CTRL_DISABLE" && inst["epwmDeadband_deadbandCounterClockRate"]== "EPWM_DB_COUNTER_CLOCK_FULL_CYCLE") 
			{
				validation.logError(name, inst, "epwmDeadband_deadbandCounterClockRate");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #39
	{
		type : validation_warning,
		name :  "TBPRDHR should not be used with Global load. If high resolution period must be changed in the application, write to the individual period registers from an ePWM ISR (The ISR must be synchronous with the PWM switching period), where the Global Load One-Shot bit is also written to.",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && inst["epwmTimebase_periodGld"] == true && inst["epwmGlobalLoad_gld"] == true) 
			{
				validation.logWarning(name, inst, "epwmTimebase_periodGld");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #40
	{
		type : validation_warning,
		name :  "When high-resolution period control is enabled, on ePWMxA or ePWMxB output only, the non hi-res output will have +/- 1 TBCLK cycle jitter",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP" && ((inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && inst["hrpwm_controlModeB"] == "HRPWM_MEP_PHASE_CTRL") || (inst["hrpwm_controlModeA"] == "HRPWM_MEP_PHASE_CTRL" && inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL"))) 
			{
				validation.logWarning(name, inst, "hrpwm_periodEnable");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #41
	{
		type : validation_warning,
		name :  "When high-resolution period control is enabled, on ePWMxA or ePWMxB output only, the non hi-res output will have +/- 2 TBCLK cycle jitter",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP_DOWN" && ((inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && inst["hrpwm_controlModeB"] == "HRPWM_MEP_PHASE_CTRL") || (inst["hrpwm_controlModeA"] == "HRPWM_MEP_PHASE_CTRL" && inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL"))) 
			{
				validation.logWarning(name, inst, "hrpwm_periodEnable");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #42
	{
		type : validation_error,
		name :  "High-resolution period is not compatible with down-count mode.",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_DOWN" && inst["hrpwm_periodEnable"] == true && (inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" || inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL")) 
			{
				validation.logError(name, inst, "hrpwm_periodEnable");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #43
	{
		type : validation_error,
		name :  "For High Ressolution Period TBPRD must have shadow loading enabled if HRPWM is used",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && (inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" || inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL") && inst["epwmTimebase_periodLoadMode"] != "EPWM_PERIOD_SHADOW_LOAD") 
			{
				validation.logError(name, inst, "hrpwm_periodEnable");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #44
	{
		type : validation_error,
		name :  "For High Resolution Period: CMPA must have shadow loading enabled for when TBCTR=PRD",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP" && inst["hrpwm_edgeModeA"] != "HRPWM_MEP_CTRL_DISABLE" && inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && (inst["epwmCounterCompare_enableShadowLoadModeCMPA"] == false || inst["epwmCounterCompare_shadowLoadModeCMPA"] != "EPWM_COMP_LOAD_ON_CNTR_PERIOD")) 
			{
				validation.logError(name, inst, "hrpwm_edgeModeA");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #45
	{
		type : validation_error,
		name :  "For High Resolution Period: CMPB must have shadow loading enabled for when TBCTR=PRD",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP" && inst["hrpwm_edgeModeB"] != "HRPWM_MEP_CTRL_DISABLE" && inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && (inst["epwmCounterCompare_enableShadowLoadModeCMPB"] == false || inst["epwmCounterCompare_shadowLoadModeCMPB"] != "EPWM_COMP_LOAD_ON_CNTR_PERIOD")) 
			{
				validation.logError(name, inst, "hrpwm_edgeModeB");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #46
	{
		type : validation_error,
		name :  "For High Resolution Period: CMPA must have shadow loading enabled for when TBCTR=0 or PRD",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP_DOWN" && inst["hrpwm_edgeModeA"] != "HRPWM_MEP_CTRL_DISABLE" && inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && (inst["epwmCounterCompare_enableShadowLoadModeCMPA"] == false || inst["epwmCounterCompare_shadowLoadModeCMPA"] != "EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD")) 
			{
				validation.logError(name, inst, "hrpwm_edgeModeA");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #47
	{
		type : validation_error,
		name :  "For High Resolution Period: CMPB must have shadow loading enabled for when TBCTR=0 or PRD",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP_DOWN" && inst["hrpwm_edgeModeB"] != "HRPWM_MEP_CTRL_DISABLE" && inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && (inst["epwmCounterCompare_enableShadowLoadModeCMPB"] == false || inst["epwmCounterCompare_shadowLoadModeCMPB"] != "EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD")) 
			{
				validation.logError(name, inst, "hrpwm_edgeModeB");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #48
	{
		type : validation_warning,
		name :  "For High Resolution Period: Shadow loading of CMPBHR should occur when TBCTR=0 or PRD and MEP should control both edges",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && (inst["hrpwm_HRLoadB"] != "HRPWM_LOAD_ON_CNTR_ZERO_PERIOD" || inst["hrpwm_edgeModeB"] != "HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE"))
			{
				validation.logWarning(name, inst, "hrpwm_edgeModeB");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #49
	{
		type : validation_warning,
		name :  "For High Resolution Period: Shadow loading of CMPAHR should occur when TBCTR=0 or PRD and MEP should control both edges",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && (inst["hrpwm_HRLoadA"] != "HRPWM_LOAD_ON_CNTR_ZERO_PERIOD" || inst["hrpwm_edgeModeA"] != "HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE")) 
			{
				validation.logWarning(name, inst, "hrpwm_edgeModeA");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #50
	{
		type : validation_error,
		name :  "When using HRPWM, the DBRED and DBFED values must be greater than 3 to use hi-res deadband",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_edgeModeDB"] == "HRPWM_DB_MEP_CTRL_DISABLE" && ((inst["epwmDeadband_delayRED"] < 3 && inst["epwmDeadband_enableRED"] == true )|| (inst["epwmDeadband_delayFED"] < 3 && inst["epwmDeadband_enableFED"] == true)))
			{
				validation.logError(name, inst, "epwmDeadband_delayRED");
				validation.logError(name, inst, "epwmDeadband_delayFED");
				validation.logError(name, inst, "hrpwm_DBredHR");
				validation.logError(name, inst, "hrpwm_DBfedHR");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #51
	{
		type : validation_error,
		name :  "When using DBREDHR, DBRED must be greater than or equal to 7",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_edgeModeDB"] == "HRPWM_DB_MEP_CTRL_RED" && inst["hrpwm_DBredHR"] != 0 && inst["epwmDeadband_delayRED"] < 7 && inst["epwmDeadband_enableRED"] == true)
			{
				validation.logError(name, inst, "hrpwm_DBredHR");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #52
	{
		type : validation_error,
		name :  "When using DBFEDHR, DBFED must be greater than or equal to 7",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_edgeModeDB"] == "HRPWM_DB_MEP_CTRL_FED" && inst["hrpwm_DBfedHR"] != 0 && inst["epwmDeadband_delayFED"] < 7 && inst["epwmDeadband_enableFED"] == true)
			{
				validation.logError(name, inst, "hrpwm_DBfedHR");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #53
	{
		type : validation_error,
		name :  "When using DBREDHR and DBFEDHR, DBRED and DBFED must be greater than or equal to 7",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_edgeModeDB"] == "HRPWM_DB_MEP_CTRL_RED_FED" && (inst["hrpwm_DBfedHR"] != 0 || inst["hrpwm_DBredHR"] != 0) && ((inst["epwmDeadband_delayFED"] < 7 && inst["epwmDeadband_enableRED"] == true) || (inst["epwmDeadband_delayRED"] < 7 && inst["epwmDeadband_enableFED"] == true)))
			{
				validation.logError(name, inst, "hrpwm_DBredHR");
				validation.logError(name, inst, "hrpwm_DBfedHR");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #54
	{
		type : validation_error,
		name :  "A CMPAHR value of 0 is not supported",
		func : (inst, validation, name) => {
			if (inst["hrpwm_cmpaHR"] == 0 && inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL") 
			{
				validation.logError(name, inst, "hrpwm_cmpaHR");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #55
	{
		type : validation_error,
		name :  "A CMPBHR value of 0 is not supported",
		func : (inst, validation, name) => {
			if (inst["hrpwm_cmpbHR"] == 0 && inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL") 
			{
				validation.logError(name, inst, "hrpwm_cmpbHR");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #56
	{
		type : validation_warning,
		name :  "If doing complementary signals through deadband, a CMPBHR value is still needed.",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enabled"] == true && (inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" || inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL") && inst["epwmDeadband_inputRED"]== "EPWM_DB_INPUT_EPWMA" && inst["epwmDeadband_inputFED"]== "EPWM_DB_INPUT_EPWMA" && inst["epwmDeadband_polarityRED"]== "EPWM_DB_POLARITY_ACTIVE_HIGH" && inst["epwmDeadband_polarityFED"]== "EPWM_DB_POLARITY_ACTIVE_LOW" && inst["epwmDeadband_enableRED"] == true && inst["epwmDeadband_enableFED"] == true && inst["epwmDeadband_outputSwapOutA"] == false && inst["epwmDeadband_outputSwapOutB"] == false) 
			{
				validation.logWarning(name, inst, "hrpwm_cmpbHR");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},

	// Validation #57
	{
		type : validation_info,
		name :  "MEP becomes operational: â€¢Three EPWMCLK cycles after the period starts when high-resolution period (TBPRDHR) control is not enabled. â€¢ When high resolution period (TBPRDHR) control is enabled via the HRPCTL register â€“ In up-count mode: three EPWMCLK cycles after the period starts until three EPWMCLK cycles before the period ends. â€“ In up-down count mode: when counting up, three cycles after CTR = 0 until three cycles before CTR = PRD, and when counting down, three cycles after CTR = PRD until three cycles before CTR= 0.",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true) 
			{
				validation.logInfo(name, inst, "hrpwm_enable");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #58
	{
		type : validation_warning,
		name :  "For TBPHS:TBPHSHR synchronization with high-resolution period, set both high resolution phase shift load and phase shift load. In up-down count mode these bits must be set to 1 regardless of the contents of TBPHSHR.",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && (inst["hrpwm_controlModeA"] == "HRPWM_MEP_PHASE_CTRL" || inst["hrpwm_controlModeB"] == "HRPWM_MEP_PHASE_CTRL") && (inst["hrpwm_phaseLoadEnable"] != true || inst["epwmTimebase_phaseEnable"] != true)) 
			{
				validation.logWarning(name, inst, "hrpwm_phaseLoadEnable");
				validation.logWarning(name, inst, "epwmTimebase_phaseEnable");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #59
	{
		type : validation_info,
		name :  "When high-resolution period mode is enabled, an EPWMxSYNC pulse will introduce +/- 1 - 2 cycle jitter to the PWM (+/- 1 cycle in up-count mode and +/- 2 cycle in up-down count mode).When the 'Sync Out Pulse' is configured to software, a software synchronization pulse should be issued only once during high-resolution period initialization. If a software sync pulse is applied while the PWM is running, the jitter will appear on the PWM output at the time of the sync pulse.",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["hrpwm_periodEnable"] == true && (inst["hrpwm_controlModeA"] == "HRPWM_MEP_PHASE_CTRL" || inst["hrpwm_controlModeB"] == "HRPWM_MEP_PHASE_CTRL")) 
			{
				validation.logInfo(name, inst, "hrpwm_periodEnable");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #60
	{
		type : validation_warning,
		name :  "If counter mode is up count mode, edge control of both edges is not supported",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP" && inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && inst["hrpwm_edgeModeA"] == "HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE") 
			{
				validation.logWarning(name, inst, "epwmTimebase_counterMode");
				validation.logWarning(name, inst, "hrpwm_controlModeA");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #61
	{
		type : validation_warning,
		name :  "If counter mode is up count mode, edge control of both edges is not supported",
		func : (inst, validation, name) => {
			if (inst["hrpwm_enable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP" && inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && inst["hrpwm_edgeModeB"] == "HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE") 
			{
				validation.logWarning(name, inst, "epwmTimebase_counterMode");
				validation.logWarning(name, inst, "hrpwm_controlModeB");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #62
	{
		type : validation_error,
		name :  "If counter mode is up count mode and if HR mode is enabled then action qualifier settings need to be set on PRD and clear on CMPXU",
		func : (inst, validation, name) => {
			var AQ_A_Period = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_PERIOD"];
			var AQ_A_CMPA = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_UP_CMPA"];
			var AQ_A_CMPB = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_UP_CMPB"];
			if (inst["hrpwm_enable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP" && ((AQ_A_Period != "EPWM_AQ_OUTPUT_HIGH" && AQ_A_Period != "EPWM_AQ_OUTPUT_NO_CHANGE") || (AQ_A_CMPA != "EPWM_AQ_OUTPUT_LOW" && AQ_A_CMPA != "EPWM_AQ_OUTPUT_NO_CHANGE") || (AQ_A_CMPB != "EPWM_AQ_OUTPUT_LOW" && AQ_A_CMPB != "EPWM_AQ_OUTPUT_NO_CHANGE"))) 
			{
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_PERIOD");
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_UP_CMPA");
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_UP_CMPB");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #63
	{
		type : validation_error,
		name :  "If counter mode is up count mode and if HR mode is enabled then action qualifier settings need to be set on PRD and clear on CMPXU",
		func : (inst, validation, name) => {
			var AQ_B_Period = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_PERIOD"];
			var AQ_B_CMPA = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_UP_CMPA"];
			var AQ_B_CMPB = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_UP_CMPB"];
			if (inst["hrpwm_enable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP" && ((AQ_B_Period != "EPWM_AQ_OUTPUT_HIGH" && AQ_B_Period != "EPWM_AQ_OUTPUT_NO_CHANGE") || (AQ_B_CMPA != "EPWM_AQ_OUTPUT_LOW" && AQ_B_CMPA != "EPWM_AQ_OUTPUT_NO_CHANGE") || (AQ_B_CMPB != "EPWM_AQ_OUTPUT_LOW" && AQ_B_CMPB != "EPWM_AQ_OUTPUT_NO_CHANGE"))) 
			{
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_PERIOD");
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_UP_CMPA");
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_UP_CMPB");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #64
	{
		type : validation_error,
		name :  "If in up & down count mode, and doing both edge control then in this case you need to have action qualifer settings as follows: CMPxU = set, CMPXD = clear, no actions on TBCTR= PRD or ZRO",
		func : (inst, validation, name) => {
			var AQ_A_Zero = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_ZERO"];
			var AQ_A_Period = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_ZERO"];
			var AQ_A_CMPAU = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_UP_CMPA"];
			var AQ_A_CMPBU = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_UP_CMPB"];
			var AQ_A_CMPAD = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_DOWN_CMPA"];
			var AQ_A_CMPBD = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_DOWN_CMPB"];
			if (inst["hrpwm_enable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP_DOWN" && inst["hrpwm_controlModeA"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && inst["hrpwm_edgeModeA"] == "HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE" && (AQ_A_Zero != "EPWM_AQ_OUTPUT_NO_CHANGE" || AQ_A_Period != "EPWM_AQ_OUTPUT_NO_CHANGE"  || AQ_A_CMPAU != "EPWM_AQ_OUTPUT_HIGH" || AQ_A_CMPAD!= "EPWM_AQ_OUTPUT_LOW"))
			{
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_ZERO");
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_PERIOD");
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_UP_CMPA");
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_A_ON_TIMEBASE_DOWN_CMPA");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #65
	{
		type : validation_error,
		name :  "If in up & down count mode, and doing both edge control then in this case you need to have action qualifer settings as follows: CMPxU = set, CMPXD = clear, no actions on TBCTR= PRD or ZRO",
		func : (inst, validation, name) => {
			var AQ_B_Zero = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_ZERO"];
			var AQ_B_Period = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_PERIOD"];
			var AQ_B_CMPAU = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_UP_CMPA"];
			var AQ_B_CMPBU = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_UP_CMPB"];
			var AQ_B_CMPAD = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_DOWN_CMPA"];
			var AQ_B_CMPBD = inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_DOWN_CMPB"];
						if (inst["hrpwm_enable"] == true && inst["epwmTimebase_counterMode"] == "EPWM_COUNTER_MODE_UP_DOWN" && inst["hrpwm_controlModeB"] == "HRPWM_MEP_DUTY_PERIOD_CTRL" && inst["hrpwm_edgeModeB"] == "HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE" && (AQ_B_Zero != "EPWM_AQ_OUTPUT_NO_CHANGE" || AQ_B_Period != "EPWM_AQ_OUTPUT_NO_CHANGE"  || AQ_B_CMPBU != "EPWM_AQ_OUTPUT_HIGH" || AQ_B_CMPBD!= "EPWM_AQ_OUTPUT_LOW"))
			{
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_ZERO");
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_PERIOD");
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_UP_CMPB");
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_B_ON_TIMEBASE_DOWN_CMPB");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #66
		{
		type : validation_warning,
		name :  "When global loading is enabled and the one-shot mode feature is used, a one-shot pulse must be declared at the end of initialization in order for the content in the shadow registers to move to the active registers",
		func : (inst, validation, name) => {
			if (inst["epwmGlobalLoad_gld"] == true && inst["epwmGlobalLoad_enableOneShot"] == true && inst["epwmGlobalLoad_oneShotMode"] == false)
			{
				validation.logWarning(name, inst, "epwmGlobalLoad_oneShotMode");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #67
		{
		type : validation_warning,
		name :  "When global loading is enabled and the one-shot mode feature is used, shadow loading for AQCTLx needs to be enabled in order to move initialized content from shadow to active registers",
		func : (inst, validation, name) => {
			if (inst["epwmGlobalLoad_gld"] == true && inst["epwmGlobalLoad_enableOneShot"] == true && (inst["epwmActionQualifier_EPWM_AQ_OUTPUT_A_shadowMode"] == false || inst["epwmActionQualifier_EPWM_AQ_OUTPUT_B_shadowMode"] == false))
			{
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_A_shadowMode");
				validation.logWarning(name, inst, "epwmActionQualifier_EPWM_AQ_OUTPUT_B_shadowMode");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
	// Validation #68
		{
		type : validation_warning,
		name :  "When global loading is enabled, the global load strobe period needs to be specified in order for the global loading to occur",
		func : (inst, validation, name) => {
			if (inst["epwmGlobalLoad_gld"] == true && inst["epwmGlobalLoad_enableOneShot"] == false && inst["epwmGlobalLoad_gldPeriod"] == "0")
			{
				validation.logWarning(name, inst, "epwmGlobalLoad_gldPeriod");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
		// Validation #69
		{
		type : validation_info,
		name :  "The value set for the blanking window offset will not be loaded into its corresponding register (DCFOFFSET) until TBCLKSYNC has been enabled",
		func : (inst, validation, name) => {
			if (inst["epwmDigitalCompare_blankingWindowOffset"] != 0)
			{
				validation.logInfo(name, inst, "epwmDigitalCompare_blankingWindowOffset");
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
		// Validation #70
		{
		type : validation_error,
		name :  "If multiple trip inputs are to be selected then choose the All Trips option",
		func : (inst, validation, name) => {
			for (var dcCompareTypeIndex in device_driverlib_peripheral.EPWM_DigitalCompareType)
			{
    			var dcCompareType = device_driverlib_peripheral.EPWM_DigitalCompareType[dcCompareTypeIndex];
    			var dcTypeName = "epwmDigitalCompare_" + dcCompareType.name
            	var dcTypeNameCombo = "epwmDigitalCompare_" + dcCompareType.name + "_combinationInputConfig"
				if (inst[dcTypeNameCombo].length != 0 && inst[dcTypeName] != "EPWM_DC_TRIP_COMBINATION")
				{
					validation.logError(name, inst, dcTypeName);
				}
			}
		},
		devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
			]
		},
		// Validation #71 change names below
		{
			type : validation_error,
			name :  "When XCMP mode is enabled, EPWM Time Base Counter Mode must be in Up - count mode",
			func : (inst, validation, name) => {
				if (inst["epwmTimebase_counterMode"] != "EPWM_COUNTER_MODE_UP" && inst["epwmTimebase_counterMode"] != "EPWM_COUNTER_MODE_STOP_FREEZE" && inst["epwmXCMP_enable"])
				{
					validation.logError(name, inst, "epwmTimebase_counterMode");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #72
		{
			type : validation_warning,
			name :  "When XCMP mode is enabled, EPWM Time Base Period will be set within XCMP Mode",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"])
				{
					validation.logWarning(name, inst, "epwmTimebase_period");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #73
		{
			type : validation_warning,
			name :  "When XCMP mode is enabled, EPWM Counter Compare A (CMPA) will be set within XCMP Mode",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] && inst["epwmCounterCompare_cmpA"] != 0)
				{
					validation.logWarning(name, inst, "epwmCounterCompare_cmpA");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #74
		{
			type : validation_warning,
			name :  "When XCMP mode is enabled, EPWM Counter Compare B (CMPB) will be set within XCMP Mode",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] && inst["epwmCounterCompare_cmpB"] != 0)
				{
					validation.logWarning(name, inst, "epwmCounterCompare_cmpB");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #75
		{
			type : validation_warning,
			name :  "When XCMP mode is enabled, EPWM Counter Compare C (CMPC) will be set within XCMP Mode",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] && inst["epwmCounterCompare_cmpC"] != 0)
				{
					validation.logWarning(name, inst, "epwmCounterCompare_cmpC");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #76
		{
			type : validation_warning,
			name :  "When XCMP mode is enabled, EPWM Counter Compare D (CMPD) will be set within XCMP Mode",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] && inst["epwmCounterCompare_cmpD"] != 0)
				{
					validation.logWarning(name, inst, "epwmCounterCompare_cmpD");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #77
		{
			type : validation_error,
			name :  "When XCMP mode is enabled, EPWM Counter Compare A Shadow Load Event must be 'Load when counter equals zero'",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] && inst["epwmCounterCompare_shadowLoadModeCMPA"] != "EPWM_COMP_LOAD_ON_CNTR_ZERO")
				{
					validation.logError(name, inst, "epwmCounterCompare_shadowLoadModeCMPA");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #78
		{
			type : validation_error,
			name :  "When XCMP mode is enabled, EPWM Counter Compare A Shadow Load Event must be 'Load when counter equals zero'",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] && inst["epwmCounterCompare_shadowLoadModeCMPB"] != "EPWM_COMP_LOAD_ON_CNTR_ZERO")
				{
					validation.logError(name, inst, "epwmCounterCompare_shadowLoadModeCMPB");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #79
		{
			type : validation_error,
			name :  "When XCMP mode is enabled, EPWM Counter Compare A Shadow Load Event must be 'Load when counter equals period'",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] && inst["epwmCounterCompare_shadowLoadModeCMPC"] != "EPWM_COMP_LOAD_ON_CNTR_PERIOD")
				{
					validation.logError(name, inst, "epwmCounterCompare_shadowLoadModeCMPC");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #80
		{
			type : validation_error,
			name :  "When XCMP mode is enabled, EPWM Counter Compare A Shadow Load Event must be 'Load when counter equals period'",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] && inst["epwmCounterCompare_shadowLoadModeCMPD"] != "EPWM_COMP_LOAD_ON_CNTR_PERIOD")
				{
					validation.logError(name, inst, "epwmCounterCompare_shadowLoadModeCMPD");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #81 
		{
			type : validation_warning,
			name :  "When XCMP mode is enabled, EPWM Action Qualifer ePWMxA Event Output Configuration will be overwritten by EPWM XCMP Mode ePWMxA Event Output Configuration",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"])
				{
					for (var aqOutputIndex in device_driverlib_peripheral.EPWM_ActionQualifierOutputModule)
					{
						var aqOutput = device_driverlib_peripheral.EPWM_ActionQualifierOutputModule[aqOutputIndex];
						for (var aqEventIndex in device_driverlib_peripheral.EPWM_ActionQualifierOutputEvent)
						{
							var aqEvent = device_driverlib_peripheral.EPWM_ActionQualifierOutputEvent[aqEventIndex];
							validation.logWarning(name, inst, "epwmActionQualifier_" + aqOutput.name + "_" + aqEvent.name.replace("EPWM_AQ_OUTPUT_", ""));
						}
					}
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #82
		{
			type : validation_error,
			name :  "When XCMP Mode is split, you cannot allocate XCMP registers 5-8 to CMPA",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] 
					&& (inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_5_CMPA" || inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_6_CMPA"
					|| inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_7_CMPA" || inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_8_CMPA")&& inst.epwmXCMP_RegisterSplit_enable)
				{
					validation.logError(name, inst, "epwmXCMP_selectAllocationXCMPA_NoSplitorSplit");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #82
		{
			type : validation_warning,
			name :  "There is no shadow buffer to load, allocate atleast 1 XCMP register to XCMPA",
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_NONE_CMPA" && inst["epwmXCMP_selectShadowRegisterLevelLoad"] != "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_NULL")
				{
					validation.logWarning(name, inst, "epwmXCMP_selectShadowRegisterLevelLoad");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #83
		{
			type : validation_error,
			name :  "Synchronization is disabled when XCMP Mode is enabled",
			func : (inst, validation, name) => {
				if (inst["epwmTimebase_syncInPulseSource"] != "EPWM_SYNC_IN_PULSE_SRC_DISABLE" && inst["epwmXCMP_enable"])
				{
					validation.logError(name, inst, "epwmTimebase_syncInPulseSource");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #84
		{
			type : validation_error,
			name :  "If you enabled Minimum Deadband, there must be a delay of atleast 1 SYSCLK cycle and you cannot have a negative delay",
			func : (inst, validation, name) => {
				if (inst["epwmMinDeadBand_EnableA"] && inst["epwmMinDeadBand_A_setDelay"] <= 0)
				{
					validation.logError(name, inst, "epwmMinDeadBand_A_setDelay");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #85
		{
			type : validation_error,
			name : "Minimum of 4 cycles difference (including the HR component) between adjacent XCMP values must be maintained to guarantee minimum pulse width",
			func : (inst, validation, name) => {
				var xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(0, 8);
				let reg_names = ["XCMPA", "XCMPB"];
				let xcmp_regs = []
				// Different checks for xcmpa / xcmpb since they have 8 shadow registers
				for(var reg_name_index in reg_names){
					let reg_name = reg_names[reg_name_index];
					for(var xcmp_reg_index = 0; xcmp_reg_index < xcmp_RegArr.length; xcmp_reg_index++)
					{
						var next_xcmp_index = xcmp_reg_index + 1;
						while(next_xcmp_index < xcmp_RegArr.length)
						{
							//console.log(next_xcmp_index)
							if(next_xcmp_index + 1 >= xcmp_RegArr.length)
							{
								break;
							}
							if((Math.abs(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] - 
							  	inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")]) < 4) &&
								(Math.abs(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] - 
							  	inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")]) > 0) &&
								(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] != 0) &&
								(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")] != 0)) 
							{
								validation.logError(name, inst, "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", ""));
							}
							next_xcmp_index++;
						}
					}
				}
				xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(9, 17);
				for(var reg_name_index in reg_names){
					let reg_name = reg_names[reg_name_index];
					for(var xcmp_reg_index = 0; xcmp_reg_index < xcmp_RegArr.length; xcmp_reg_index++)
					{
						var next_xcmp_index = xcmp_reg_index + 1;
						while(next_xcmp_index < xcmp_RegArr.length)
						{
							//console.log(next_xcmp_index)
							if(next_xcmp_index + 1 >= xcmp_RegArr.length)
							{
								break;
							}
							if((Math.abs(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] - 
							  	inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")]) < 4) &&
								(Math.abs(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] - 
							  	inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")]) > 0) &&
								(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] != 0) &&
								(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")] != 0)) 
							{
								validation.logError(name, inst, "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", ""));
							}
							next_xcmp_index++;
						}
					}
				}
				xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(18, 26);
				for(var reg_name_index in reg_names){
					let reg_name = reg_names[reg_name_index];
					for(var xcmp_reg_index = 0; xcmp_reg_index < xcmp_RegArr.length; xcmp_reg_index++)
					{
						var next_xcmp_index = xcmp_reg_index + 1;
						while(next_xcmp_index < xcmp_RegArr.length)
						{
							//console.log(next_xcmp_index)
							if(next_xcmp_index + 1 >= xcmp_RegArr.length)
							{
								break;
							}
							if((Math.abs(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] - 
							  	inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")]) < 4) &&
								(Math.abs(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] - 
							  	inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")]) > 0) &&
								(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] != 0) &&
								(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")] != 0)) 
							{
								validation.logError(name, inst, "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", ""));
							}
							next_xcmp_index++;
						}
					}
				}
				xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(27, 35);
				for(var reg_name_index in reg_names){
					let reg_name = reg_names[reg_name_index];
					for(var xcmp_reg_index = 0; xcmp_reg_index < xcmp_RegArr.length; xcmp_reg_index++)
					{
						var next_xcmp_index = xcmp_reg_index + 1;
						while(next_xcmp_index < xcmp_RegArr.length)
						{
							//console.log(next_xcmp_index)
							if(next_xcmp_index + 1 >= xcmp_RegArr.length)
							{
								break;
							}
							if((Math.abs(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] - 
							  	inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")]) < 4) &&
								(Math.abs(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] - 
							  	inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")]) > 0) &&
								(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", "")] != 0) &&
								(inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[next_xcmp_index].name.replace("EPWM_", "")] != 0)) 
							{
								validation.logError(name, inst, "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_reg_index].name.replace("EPWM_", ""));
							}
							next_xcmp_index++;
						}
					}
				}

			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #86
		{
			type : validation_error,
			name :  "Input value is out of range (8-bit value)",
			func : (inst, validation, name) => {
							// Diode Emulation Reentry Delay 
			if (inst["epwmDiodeEmulation_Reentrycnt"] < 0 ||
			inst["epwmDiodeEmulation_Reentrycnt"] > 255) 
			{
				validation.logError(name, inst, "epwmDiodeEmulation_Reentrycnt");
			}
			// Diode Emulation Monitor Increment / Decrement / Threshold Check
			if (inst["epwmDiodeEmulation_stepIncr"] < 0 ||
				inst["epwmDiodeEmulation_stepIncr"] > 255) 
				{
					validation.logError(name, inst, "epwmDiodeEmulation_stepIncr");
				}
			if (inst["epwmDiodeEmulation_stepDecr"] < 0 ||
				inst["epwmDiodeEmulation_stepDecr"] > 255) 
				{
					validation.logError(name, inst, "epwmDiodeEmulation_stepDecr");
				}
		},
		devices : [
				"F28P65x"
			]
		},
		// Validation #87
		{
			type : validation_warning,
			name :  '"In order to load Shadow Buffer Set 1 select the "SHDW1 and Active registers are available" option',
			func : (inst, validation, name) => {

				if (inst["epwmXCMP_enable"] 
				&& (inst["epwmXCMP_selectNumberShadowRegisterLevels"] == "EPWM_XCMP_XLOADCTL_SHDWLEVEL_0" && 
					inst["epwmXCMP_selectShadowRegisterLevelLoad"] != "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_NULL"))
				{
					validation.logWarning(name, inst, "epwmXCMP_selectNumberShadowRegisterLevels");
				}
				
				
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #88
		{
			type : validation_warning,
			name :  '"In order to load Shadow Buffer Set 2 select the "SHDW2, SHDW1 and Active registers are available" option',
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] 
				&& ((inst["epwmXCMP_selectNumberShadowRegisterLevels"] == "EPWM_XCMP_XLOADCTL_SHDWLEVEL_0" || inst["epwmXCMP_selectNumberShadowRegisterLevelsXCMPA"] == "EPWM_XCMP_XLOADCTL_SHDWLEVEL_1") && 
					inst["epwmXCMP_selectShadowRegisterLevelLoad"] == "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_TWO"))
				{
					validation.logWarning(name, inst, "epwmXCMP_selectNumberShadowRegisterLevels");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #89
		{
			type : validation_warning,
			name :  '"In order to load Shadow Buffer Set 3 select the "SHDW3, SHDW2, SHDW1 and Active registers are available" option',
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] 
				&& ((inst["epwmXCMP_selectNumberShadowRegisterLevels"] == "EPWM_XCMP_XLOADCTL_SHDWLEVEL_0" 
				|| inst["epwmXCMP_selectNumberShadowRegisterLevels"] == "EPWM_XCMP_XLOADCTL_SHDWLEVEL_1" 
				|| inst["epwmXCMP_selectNumberShadowRegisterLevels"] == "EPWM_XCMP_XLOADCTL_SHDWLEVEL_2") && 
					inst["epwmXCMP_selectShadowRegisterLevelLoad"] == "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_THREE"))
				{
					validation.logWarning(name, inst, "epwmXCMP_selectNumberShadowRegisterLevels");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #90
		{
			type : validation_warning,
			name :  'Do not forget to load which shadow buffer set to load',
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] 
				&& ((inst["epwmXCMP_selectNumberShadowRegisterLevels"] == "EPWM_XCMP_XLOADCTL_SHDWLEVEL_3") && 
					inst["epwmXCMP_selectShadowRegisterLevelLoad"] == "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_NULL"))
				{
					validation.logWarning(name, inst, "epwmXCMP_selectShadowRegisterLevelLoad");
				}
				
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #91
		{
			type : validation_error,
			name :  'Must allocate at least 1 XCMP register',
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] 
				&& inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_NONE_CMPA" && 
					(inst["epwmXCMP_selectNumberShadowRegisterLevels"] == "EPWM_XCMP_XLOADCTL_SHDWLEVEL_1"
					|| inst["epwmXCMP_selectNumberShadowRegisterLevels"] == "EPWM_XCMP_XLOADCTL_SHDWLEVEL_2"
					|| inst["epwmXCMP_selectNumberShadowRegisterLevels"] == "EPWM_XCMP_XLOADCTL_SHDWLEVEL_3"))
				{
					validation.logError(name, inst, "epwmXCMP_selectAllocationXCMPA_NoSplitorSplit");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #92
		{
			type : validation_error,
			name :  'Must allocate at least 1 XCMP register',
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] 
				&& inst["epwmXCMP_selectAllocationXCMPA_NoSplitorSplit"] == "EPWM_XCMP_NONE_CMPA" && 
					(inst["epwmXCMP_selectShadowRegisterLevelLoad"] == "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_ONE"
					|| inst["epwmXCMP_selectShadowRegisterLevelLoad"] == "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_TWO"
					|| inst["epwmXCMP_selectShadowRegisterLevelLoad"] == "EPWM_XCMP_XLOADCTL_SHDWBUFPTR_THREE"))
				{
					validation.logError(name, inst, "epwmXCMP_selectShadowRegisterLevelLoad");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #93
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = LOW | MINDBxB = LOW | MINDBxA = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& (!inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC0")  && !inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC0")))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #94
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = LOW | MINDBxB = LOW | MINDBxA = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& !inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC1")  && !inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC1"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #95
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = LOW | MINDBxB = HIGH | MINDBxA = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& !inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC2")  && !inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC2"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #96
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = LOW | MINDBxB = HIGH | MINDBxA = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& !inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC3")  && !inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC3"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #97
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = HIGH | MINDBxB = LOW | MINDBxA = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& !inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC4")  && !inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC4"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #98
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = HIGH | MINDBxB = LOW | MINDBxA = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& !inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC5")  && !inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC5"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #99
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = HIGH | MINDBxB = HIGH | MINDBxA = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& !inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC6")  && !inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC6"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #100
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = HIGH | MINDBxB = HIGH | MINDBxA = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& !inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC7")  && !inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC7"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #101
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = LOW | MINDBxA = LOW | MINDBxB = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& !inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC0")  && !inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC0"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #102
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = LOW | MINDBxA = LOW | MINDBxB = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& !inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC1")  && !inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC1"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #103
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = LOW | MINDBxA = HIGH | MINDBxB = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& !inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC2")  && !inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC2"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #104
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = LOW | MINDBxA = HIGH | MINDBxB = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& !inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC3")  && !inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC3"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #105
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = HIGH | MINDBxA = LOW | MINDBxB = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& !inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC4")  && !inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC4"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #106
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = HIGH | MINDBxA = LOW | MINDBxB = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& !inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC5")  && !inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC5"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #107
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = HIGH | MINDBxA = HIGH | MINDBxB = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& !inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC6")  && !inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC6"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #108
		{
			type : validation_error,
			name :  'Set output for ICLXBAR = HIGH | MINDBxA = HIGH | MINDBxB = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& !inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC7")  && !inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC7"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #109
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = LOW | MINDBxB = LOW | MINDBxA = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC0")  && inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC0"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #110
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = LOW | MINDBxB = LOW | MINDBxA = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC1")  && inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC1"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #111
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = LOW | MINDBxB = HIGH | MINDBxA = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC2")  && inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC2"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #112
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = LOW | MINDBxB = HIGH | MINDBxA = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC3")  && inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC3"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #113
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = HIGH | MINDBxB = LOW | MINDBxA = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC4")  && inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC4"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #114
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = HIGH | MINDBxB = LOW | MINDBxA = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC5")  && inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC5"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #115
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = HIGH | MINDBxB = HIGH | MINDBxA = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC6")  && inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC6"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #116
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = HIGH | MINDBxB = HIGH | MINDBxA = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableA"] 
				&& inst["epwmICL_A_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC7")  && inst["epwmICL_A_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC7"))
				{
					validation.logError(name, inst, "epwmICL_A_OUTHIGH");
					validation.logError(name, inst, "epwmICL_A_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #117
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = LOW | MINDBxA = LOW | MINDBxB = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC0")  && inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC0"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #118
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = LOW | MINDBxA = LOW | MINDBxB = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC1")  && inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC1"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #119
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = LOW | MINDBxA = HIGH | MINDBxB = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC2")  && inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC2"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #120
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = LOW | MINDBxA = HIGH | MINDBxB = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC3")  && inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC3"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #121
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = HIGH | MINDBxA = LOW | MINDBxB = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC4")  && inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC4"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #122
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = HIGH | MINDBxA = LOW | MINDBxB = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC5")  && inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC5"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #123
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = HIGH | MINDBxA = HIGH | MINDBxB = LOW',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC6")  && inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC6"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		// Validation #124
		{
			type : validation_error,
			name :  'Output can either output high or low for ICLXBAR = HIGH | MINDBxA = HIGH | MINDBxB = HIGH',
			func : (inst, validation, name) => {
				if (inst["epwmICL_EnableB"] 
				&& inst["epwmICL_B_OUTLOW"].includes("EPWM_MINDB_ICL_LUT_DEC7")  && inst["epwmICL_B_OUTHIGH"].includes("EPWM_MINDB_ICL_LUT_DEC7"))
				{
					validation.logError(name, inst, "epwmICL_B_OUTHIGH");
					validation.logError(name, inst, "epwmICL_B_OUTLOW");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		{
			type : validation_error,
			name :  'Enable XCMP Mode to use this feature',
			func : (inst, validation, name) => {
				if (inst["epwmDigitalCompare_enableEventDetection"] && !inst["epwmXCMP_enable"])
				{
					validation.logError(name, inst, "epwmXCMP_enable");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		{
			type : validation_warning,
			name :  'Register loads will be controlled by XLOADCTL in XCMP mode ',
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_RegisterLoad_enable"])
				{
					validation.logWarning(name, inst, "epwmGlobalLoad_gld");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		{
			type : validation_info,
			name :  'Configure these read only values within ',
			func : (inst, validation, name) => {
				if (inst["epwmXCMP_enable"] && inst["epwmDigitalCompare_enableEventDetection"])
				{
					validation.logInfo(name + system.getReference(inst ,"epwmXCMP_setRegisters_XMIN") , inst, "epwmXCMP_setRegisters_XMIN_read");
					validation.logInfo(name + system.getReference(inst ,"epwmXCMP_setShadowRegisters1_XMIN") , inst, "epwmXCMP_setShadowRegisters1_XMIN_read");
					validation.logInfo(name + system.getReference(inst ,"epwmXCMP_setShadowRegisters2_XMIN") , inst, "epwmXCMP_setShadowRegisters2_XMIN_read");
					validation.logInfo(name + system.getReference(inst ,"epwmXCMP_setShadowRegisters3_XMIN") , inst, "epwmXCMP_setShadowRegisters3_XMIN_read");
					validation.logInfo(name + system.getReference(inst ,"epwmXCMP_setRegisters_XMAX") , inst, "epwmXCMP_setRegisters_XMAX_read");
					validation.logInfo(name + system.getReference(inst ,"epwmXCMP_setShadowRegisters1_XMAX") , inst, "epwmXCMP_setShadowRegisters1_XMAX_read");
					validation.logInfo(name + system.getReference(inst ,"epwmXCMP_setShadowRegisters2_XMAX") , inst, "epwmXCMP_setShadowRegisters2_XMAX_read");
					validation.logInfo(name + system.getReference(inst ,"epwmXCMP_setShadowRegisters3_XMAX") , inst, "epwmXCMP_setShadowRegisters3_XMAX_read");

				}
			},
			devices : [
				"F28P65x"
				]
		},
		{
			type : validation_error,
			name :  'Go to CPU1 context and add a MINDB XBAR Instance',
			func : (inst, validation, name) => {
				const outputs = ["A", "B"];
				
				if(Common.isModuleOnOtherContext("/driverlib/mindbxbar.js"))
				{
					// check if in multi core view
					
					var module = system.modules['/driverlib/epwm.js'];
					// Stil need to do
					var mindbxbar_instances = system.contexts.CPU1.system.modules["/driverlib/mindbxbar.js"].$instances;
					
					let cpu1_mindbxbar_list = [];
					if(Common.isContextCPU2())
					{

						if(Common.isMultiCoreSysConfig())
						{
							if(mindbxbar_instances)
							{
								// create array of mindxbar instances configured on CPU1
								for(var mindbxbar_instance in mindbxbar_instances)
								{
									var mindbxbar = mindbxbar_instances[mindbxbar_instance].mindbxbarInstance;
									cpu1_mindbxbar_list.push(mindb_icl_xbar_map[mindbxbar]);
								}
							}					
							for(var output in outputs)
							{
								var cpu2_mindxbar_selection = inst["epwmMinDeadBand_" + outputs[output] + "_inputRefSignal"];
								if(cpu2_mindxbar_selection != "EPWM_MINDB_SEL_DEPWM" &&
									!cpu1_mindbxbar_list.includes(cpu2_mindxbar_selection))
								{
									validation.logError(name + ": " + mindb_icl_xbar_map[inst["epwmMinDeadBand_" + outputs[output] + "_inputRefSignal"]], inst, "epwmMinDeadBand_" + outputs[output] + "_inputRefSignal");
								}
							}
						}
					}
				}else
				{
					for(var output in outputs)
					{
						var cpu2_mindxbar_selection = inst["epwmMinDeadBand_" + outputs[output] + "_inputRefSignal"];
						if(Common.isContextCPU2() && cpu2_mindxbar_selection != "EPWM_MINDB_SEL_DEPWM")
						{
							if(Common.isMultiCoreSysConfig())
							{
								validation.logError(name + ": " + mindb_icl_xbar_map[inst["epwmMinDeadBand_" + outputs[output] + "_inputRefSignal"]], inst, "epwmMinDeadBand_" + outputs[output] + "_inputRefSignal");
							}else
							{
								validation.logWarning(name + ": " + mindb_icl_xbar_map[inst["epwmMinDeadBand_" + outputs[output] + "_inputRefSignal"]], inst, "epwmMinDeadBand_" + outputs[output] + "_inputRefSignal");
							}
						}

					}
				}
			},
			devices : [
				"F28P65x"
				]
		},
		{
			type : validation_error,
			name :  'Go to CPU1 context and add an ICL XBAR Instance',
			func : (inst, validation, name) => {
				const outputs = ["A", "B"];
				// check if in multi core view
				if(Common.isModuleOnOtherContext("/driverlib/iclxbar.js"))
				{
					var module = system.modules['/driverlib/epwm.js'];
					var iclxbar_instances = system.contexts.CPU1.system.modules["/driverlib/iclxbar.js"].$instances;
					let cpu1_iclxbar_list = [];
					if(Common.isContextCPU2())
					{

						if(Common.isMultiCoreSysConfig())
						{
							if(iclxbar_instances)
							{
								// create array of mindxbar instances configured on CPU1
								for(var iclxbar_instance in iclxbar_instances)
								{
									var iclxbar = iclxbar_instances[iclxbar_instance].iclxbarInstance;
									cpu1_iclxbar_list.push(icl_mindb_xbar_map[iclxbar]);
								}
							}					
							for(var output in outputs)
							{
								var cpu2_iclxbar_selection = inst["epwmICL_" + outputs[output] + "_selXBAR"];
								if(!cpu1_iclxbar_list.includes(cpu2_iclxbar_selection) && inst["epwmICL_Enable" + outputs[output]])
								{
									validation.logError(name + ": " + icl_mindb_xbar_map[inst["epwmICL_" + outputs[output] + "_selXBAR"]], inst, "epwmICL_" + outputs[output] + "_selXBAR");
								}
							}
						}
					}	
				}else
				{
					for(var output in outputs)
					{
						if(Common.isContextCPU2() && inst["epwmICL_Enable" + outputs[output]])
						{
							if(Common.isMultiCoreSysConfig())
							{
								validation.logError(name + ": "+ icl_mindb_xbar_map[inst["epwmICL_" + outputs[output] + "_selXBAR"]], inst, "epwmICL_" + outputs[output] + "_selXBAR");
							}else
							{
								validation.logWarning(name + ": ", inst, "epwmICL_" + outputs[output] + "_selXBAR");
							}
						}

					}
				}
			},
			devices : [
				"F28P65x"
				]
		},
		{
			type : validation_error,
			name :   "Input value is out of range (16-bit value)",
			func : (inst, validation, name) => {
				// check if in multi core view
				var xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(0, 8);
				let reg_names = ["XCMPA", "XCMPB"];
				// Different checks for xcmpa / xcmpb since they have 8 shadow registers
				for(var reg_name_index in reg_names){
					let reg_name = reg_names[reg_name_index];
					for(var xcmp_Reg_Index in xcmp_RegArr)
					{
						if (inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] < 0 ||
							inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] > 65535) 
							{
								validation.logError(name, inst, "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", ""));
							}
						}
					}
				xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(9, 17);
				for(var reg_name_index in reg_names){
					let reg_name = reg_names[reg_name_index];
					for(var xcmp_Reg_Index in xcmp_RegArr)
					{
						if (inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] < 0 ||
						inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] > 65535)
						{
							validation.logError(name, inst, "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", ""));
						}
					}
				}
				xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(18, 26);
				for(var reg_name_index in reg_names){
					let reg_name = reg_names[reg_name_index];
					for(var xcmp_Reg_Index in xcmp_RegArr)
					{
						if (inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] < 0 ||
						inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] > 65535) 
						{
							validation.logError(name, inst, "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", ""));
						}
					}
				}
				xcmp_RegArr = device_driverlib_peripheral.EPWM_XCMPReg.slice(27, 35);
				for(var reg_name_index in reg_names){
					let reg_name = reg_names[reg_name_index];
					{
						if (inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] < 0 ||
						inst["epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", "")] > 65535) 
						{
							validation.logError(name, inst, "epwmXCMP_set" + reg_name + "_" + xcmp_RegArr[xcmp_Reg_Index].name.replace("EPWM_", ""));

						}
					}
				}
				// XCMPC / XCMPD checks
				reg_names = ["XCMPC", "XCMPD"];		
				for(var reg_name_index in reg_names){						
					let reg_name = reg_names[reg_name_index];
					if (inst["epwmXCMP_set" + reg_name ] < 0 ||
					inst["epwmXCMP_set" + reg_name ] > 65535) 
					{
						validation.logError(name, inst, "epwmXCMP_set" + reg_name);
					}
					if (inst["epwmXCMP_setShadowRegisters1" + reg_name ] < 0 ||
					inst["epwmXCMP_setShadowRegisters1" + reg_name ] > 65535) 
					{
						validation.logError(name, inst, "epwmXCMP_setShadowRegisters1" + reg_name);
					}
					if (inst["epwmXCMP_setShadowRegisters2" + reg_name ] < 0 ||
					inst["epwmXCMP_setShadowRegisters2" + reg_name ] > 65535) 
					{
						validation.logError(name, inst, "epwmXCMP_setShadowRegisters2" + reg_name);
					}
					if (inst["epwmXCMP_setShadowRegisters3" + reg_name ] < 0 ||
					inst["epwmXCMP_setShadowRegisters3" + reg_name ] > 65535) 
					{
						validation.logError(name, inst, "epwmXCMP_setShadowRegisters3" + reg_name);
					}
				}
				
				// XCMP Time Base
				if (inst["epwmXCMP_setRegisters_XTBPRD"] < 0 ||
				inst["epwmXCMP_setRegisters_XTBPRD"] > 65535) 
				{
					validation.logError(name, inst, "epwmXCMP_setRegisters_XTBPRD");
				}
				if (inst["epwmXCMP_setRegisters_XTBPRD"] < 0 ||
					inst["epwmXCMP_setRegisters_XTBPRD"] > 65535) 
				{
					validation.logError(name, inst, "epwmXCMP_setRegisters_XTBPRD");
				}
				if (inst["epwmXCMP_setShadowRegisters1_XTBPRD"] < 0 ||
					inst["epwmXCMP_setShadowRegisters1_XTBPRD"] > 65535)  
				{
					validation.logError(name, inst, "epwmXCMP_setShadowRegisters2_XTBPRD");
				}
				if (inst["epwmXCMP_setShadowRegisters2_XTBPRD"] < 0 ||
					inst["epwmXCMP_setShadowRegisters2_XTBPRD"] > 65535)  
				{
					validation.logError(name, inst, "epwmXCMP_setShadowRegisters2_XTBPRD");
				}
				if (inst["epwmXCMP_setShadowRegisters3_XTBPRD"] < 0 ||
					inst["epwmXCMP_setShadowRegisters3_XTBPRD"] > 65535)  
				{
					validation.logError(name, inst, "epwmXCMP_setShadowRegisters3_XTBPRD");
				}
				//XCMP MinMAx
				if (inst["epwmXCMP_setRegisters_XMIN"] < 0 ||
				inst["epwmXCMP_setRegisters_XMIN"] > 65535) 
				{
					validation.logError(name, inst, "epwmXCMP_setRegisters_XMIN");
				}
				if (inst["epwmXCMP_setShadowRegisters1_XMIN"] < 0 ||
					inst["epwmXCMP_setShadowRegisters1_XMIN"] > 65535) 
				{
					validation.logError(name, inst, "epwmXCMP_setShadowRegisters1_XMIN");
				}
				if (inst["epwmXCMP_setShadowRegisters2_XMIN"] < 0 ||
					inst["epwmXCMP_setShadowRegisters2_XMIN"] > 65535)  
				{
					validation.logError(name, inst, "epwmXCMP_setShadowRegisters2_XMIN");
				}
				if (inst["epwmXCMP_setShadowRegisters3_XMIN"] < 0 ||
					inst["epwmXCMP_setShadowRegisters3_XMIN"] > 65535)  
				{
					validation.logError(name, inst, "epwmXCMP_setShadowRegisters3_XMIN");
				}
				if (inst["epwmXCMP_setRegisters_XMAX"] < 0 ||
				inst["epwmXCMP_setRegisters_XMAX"] > 65535) 
				{
					validation.logError(name, inst, "epwmXCMP_setRegisters_XMAX");
				}
				if (inst["epwmXCMP_setShadowRegisters1_XMAX"] < 0 ||
					inst["epwmXCMP_setShadowRegisters1_XMAX"] > 65535) 
				{
					validation.logError(name, inst, "epwmXCMP_setShadowRegisters1_XMAX");
				}
				if (inst["epwmXCMP_setShadowRegisters2_XMAX"] < 0 ||
					inst["epwmXCMP_setShadowRegisters2_XMAX"] > 65535)  
				{
					validation.logError(name, inst, "epwmXCMP_setShadowRegisters2_XMAX");
				}
				if (inst["epwmXCMP_setShadowRegisters3_XMAX"] < 0 ||
					inst["epwmXCMP_setShadowRegisters3_XMAX"] > 65535)  
				{
					validation.logError(name, inst, "epwmXCMP_setShadowRegisters3_XMAX");
				}
				// Minimum Dead Band delay on outputs
				for (var dbOutputIndex in device_driverlib_peripheral.EPWM_DeadBandOutput)
				{
					var dbOutput = device_driverlib_peripheral.EPWM_DeadBandOutput[dbOutputIndex];
					if (inst["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_setDelay"] < 0 ||
					inst["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_setDelay"] > 65535) 
					{
						validation.logError(name, inst, "epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_setDelay");
					}
				}
				if (inst["epwmDiodeEmulation_stepThreshold"] < 0 ||
					inst["epwmDiodeEmulation_stepThreshold"] > 65535) 
				{
					validation.logError(name, inst, "epwmDiodeEmulation_stepThreshold");
				}
			},
			devices : [
				"F28P65x"
				]
		},
		{
			type : validation_error,
			name :  'MEP Scale Factor should not be greater than 310ps',
			func : (inst, validation, name) => {
				if (inst["hrpwm_scaleFactor"] < 0 || inst["hrpwm_scaleFactor"] > 310 && inst["hrpwm_enableCalculator"])
				{
					validation.logError(name, inst, "hrpwm_scaleFactor");
				}
			},
			devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
				]
		},
		{
			type : validation_warning,
			name :  'DC Counter Capture Re-enable Event and Shadow Load Event and Blanking Window start event must be configured through blanking window settings please enable "Use Blanking Window" and configure the "Blanking Window Start Event" to update this setting',
			func : (inst, validation, name) => {
				if (inst["epwmDigitalCompare_useDCCounterCapture"] && inst["epwmDigitalCompare_dCCounterCaptureShadow"] && !inst["epwmDigitalCompare_useBlankingWindow"])
				{
					validation.logWarning(name, inst, "epwmDigitalCompare_dCCounterCapturePulse");
				}
			},
			devices : [
				"F2807x",
				"F2837xS",
				"F2837xD",
				"F28004x",
				"F28002x",
				"F28003x",
				"F280013x",
				"F280015x",
				"F2838x",
				"F28P55x",
				"F28P65x"
				]
		},
		{
			type : validation_error,
			name :  'When using HRPWM and XCMP, set HRPWM CMPx load on translator event CMPA/B-3 ',
			func : (inst, validation, name) => {
				if (inst.hrpwm_enable && inst.epwmXCMP_enable && inst.hrpwm_HRLoadA != 'HRPWM_LOAD_ON_CMPx_EQ' && inst.hrpwm_edgeModeA != 'HRPWM_MEP_CTRL_DISABLE')
					{   validation.logError(name, inst, "hrpwm_HRLoadA");
						
					}
				if (inst.hrpwm_enable && inst.epwmXCMP_enable && inst.hrpwm_HRLoadA != 'HRPWM_LOAD_ON_CMPx_EQ' && inst.hrpwm_edgeModeB != 'HRPWM_MEP_CTRL_DISABLE')
					{
						validation.logError(name, inst, "hrpwm_HRLoadB");
					}
			},
			devices : [
				
				"F28P65x"
				]
		},
		
]

exports = {
	validation_error : validation_error,
	validation_warning : validation_warning,
	validation_info : validation_info,
	epwm_validation : epwm_validation,
}
