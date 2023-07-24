let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let ComparatorInputs = system.getScript("/driverlib/cmpss/cmpss_inputSignals.js")

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_cmpss.js");

var numberOfInstance = {
    "F28004x"   : 7,
    "F28003x"   : 4,
    "F280013x"  : 1,
	"F280015x"  : 1,
    "F28002x"   : 4,
    "F2838x"    : 8,
    "F2807x"    : 8,
    "F2837xS"   : 8,
    "F2837xD"   : 8,
    "F28P65x"   : 11,
    "F28P55x"   : 4
}

var clkDivs = [
    {name: "CMPSS_RAMP_CLOCK_DIV1", displayName: "Divide SYSCLK by 1"},
    {name: "CMPSS_RAMP_CLOCK_DIV2", displayName: "Divide SYSCLK by 2"},
    {name: "CMPSS_RAMP_CLOCK_DIV3", displayName: "Divide SYSCLK by 3"},
    {name: "CMPSS_RAMP_CLOCK_DIV4", displayName: "Divide SYSCLK by 4"},
    {name: "CMPSS_RAMP_CLOCK_DIV5", displayName: "Divide SYSCLK by 5"},
    {name: "CMPSS_RAMP_CLOCK_DIV6", displayName: "Divide SYSCLK by 6"},
    {name: "CMPSS_RAMP_CLOCK_DIV7", displayName: "Divide SYSCLK by 7"},
    {name: "CMPSS_RAMP_CLOCK_DIV8", displayName: "Divide SYSCLK by 8"},
    {name: "CMPSS_RAMP_CLOCK_DIV9", displayName: "Divide SYSCLK by 9"},
    {name: "CMPSS_RAMP_CLOCK_DIV10", displayName: "Divide SYSCLK by 10"},
    {name: "CMPSS_RAMP_CLOCK_DIV11", displayName: "Divide SYSCLK by 11"},
    {name: "CMPSS_RAMP_CLOCK_DIV12", displayName: "Divide SYSCLK by 12"},
    {name: "CMPSS_RAMP_CLOCK_DIV13", displayName: "Divide SYSCLK by 13"},
    {name: "CMPSS_RAMP_CLOCK_DIV14", displayName: "Divide SYSCLK by 14"},
    {name: "CMPSS_RAMP_CLOCK_DIV15", displayName: "Divide SYSCLK by 15"},
    {name: "CMPSS_RAMP_CLOCK_DIV16", displayName: "Divide SYSCLK by 16"}
]

var rampDirections = [
    {name: "CMPSS_RAMP_DIR_DOWN", displayName: "Count Down"},
    {name: "CMPSS_RAMP_DIR_UP", displayName: "Count Up"}
]

var deviceNumberOfInstances = numberOfInstance[Common.getDeviceName()];
var CMPSS_INSTANCE = []

for (var instanceIndex = 1; instanceIndex <= deviceNumberOfInstances; instanceIndex++)
{
    CMPSS_INSTANCE.push(
        {
            name: "CMPSS" + instanceIndex.toString() + "_BASE",
            displayName: "CMPSS" + instanceIndex.toString()
        }
    );
}

if (["F28004x","F28002x","F28003x","F28P55x","F280013x", "F280015x", "F28P65x"].includes(Common.getDeviceName())){
    var defaultCMPSSPinInfos = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()]["CMPSS1_BASE"][0].displayName.split("/")[0]));

    var defaultCMPSSNegPinInfos = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(ComparatorInputs.CMPSS_comparatorNegInputSignals[Common.getDeviceName()]["CMPSS1_BASE"][1].displayName.split("/")[0]));
}

function calculateDevicePinNameHigh(inst,ui){
    if (["F28P65x"].includes(Common.getDeviceName())){
        if(((inst.cmpssBase == "CMPSS9_BASE") || (inst.cmpssBase == "CMPSS10_BASE") || (inst.cmpssBase == "CMPSS11_BASE")) && (inst.asysCMPHPMXSELValue == 3))
        {
            var tempPinInfoDesc = "No Device Pin Found"
            return tempPinInfoDesc
        }
        else
        {
            var tempPinName = ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPHPMXSELValue].displayName
            var tempPinInfo = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))
            var tempPinInfoDesc = Pinmux.getDevicePinInfoDescription(tempPinInfo)
            if(tempPinInfo.length == 0)     //SysConfig was unable to find any pins with this name, even though it exists as an input; remove error detection
            {
                if(tempPinName.includes("TempSensor"))
                {
                    return "Temperature Sensor";
                }
                else if(tempPinName.includes("VREF"))
                {
                    return tempPinName
                }
            }
            else
            {
                return tempPinInfoDesc
            }
        }
    }
    else
    {
        var tempPinName = ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPHPMXSELValue].displayName
        var tempPinInfo = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))
        var tempPinInfoDesc = Pinmux.getDevicePinInfoDescription(tempPinInfo)
        if ((["F28004x"].includes(Common.getDeviceName())) && (tempPinInfoDesc == Pinmux.NO_DEVICE_PIN_FOUND) && (inst.asysCMPHPMXSELValue == 4)){
            return "PGA"+(inst.cmpssBase.match(/\d+/)[0])+"_OUT"
        }
        else{
            return tempPinInfoDesc
        }
    }
}

function calculateDevicePinNameHighNeg(inst,ui){
    var tempPinName = ComparatorInputs.CMPSS_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPHNMXSELValue].displayName
    var tempPinInfo = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))
    var tempPinInfoDesc = Pinmux.getDevicePinInfoDescription(tempPinInfo)
    if ((["F28004x"].includes(Common.getDeviceName())) && (tempPinInfoDesc == Pinmux.NO_DEVICE_PIN_FOUND) && (inst.asysCMPHNMXSELValue == 4)){
        return "PGA"+(inst.cmpssBase.match(/\d+/)[0])+"_OUT"
    }
    else{
        return tempPinInfoDesc
    }
}

function calculateDevicePinNameLow(inst,ui){
    if(["F28P65x"].includes(Common.getDeviceName()))
    {
        if(((inst.cmpssBase == "CMPSS9_BASE") || (inst.cmpssBase == "CMPSS10_BASE") || (inst.cmpssBase == "CMPSS11_BASE")) && (inst.asysCMPLPMXSELValue == 3))
        {
            var tempPinInfoDesc = "No Device Pin Found"
            return tempPinInfoDesc
        }
        else
        {
            var tempPinName = ComparatorInputs.CMPSS_comparatorLowPositiveInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPLPMXSELValue].displayName
            var tempPinInfo = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))
            var tempPinInfoDesc = Pinmux.getDevicePinInfoDescription(tempPinInfo)
            if((tempPinInfo.length == 0) && tempPinName.includes("VREF"))     //SysConfig was unable to find any pins with this name, even though it exists as an input; remove error detection
            {
                return tempPinName
            }
            else
            {
                return tempPinInfoDesc
            }
        }
    }
    else
    {
        var tempPinName = ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPLPMXSELValue].displayName
        var tempPinInfo = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))
        var tempPinInfoDesc = Pinmux.getDevicePinInfoDescription(tempPinInfo)
        if ((["F28004x"].includes(Common.getDeviceName())) && (tempPinInfoDesc == Pinmux.NO_DEVICE_PIN_FOUND) && (inst.asysCMPLPMXSELValue == 4)){
            return "PGA"+(inst.cmpssBase.match(/\d+/)[0])+"_OUT"
        }
        else{
            return tempPinInfoDesc
        }
    }
}

function calculateDevicePinNameLowNeg(inst,ui){
    var tempPinName = ComparatorInputs.CMPSS_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPLNMXSELValue].displayName
    var tempPinInfo = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))
    var tempPinInfoDesc = Pinmux.getDevicePinInfoDescription(tempPinInfo)
    if ((["F28004x"].includes(Common.getDeviceName())) && (tempPinInfoDesc == Pinmux.NO_DEVICE_PIN_FOUND) && (inst.asysCMPLNMXSELValue == 4)){
        return "PGA"+(inst.cmpssBase.match(/\d+/)[0])+"_OUT"
    }
    else{
        return tempPinInfoDesc
    }
}

/* Array of possible ePWM sync signals */
var ePWMInstances = Common.peripheralCount("EPWM")
var ePWMArraySync = [];
var ePWMArrayBlank = [];
for(var i = 0; i < ePWMInstances; i++) {
    ePWMArraySync.push()
    ePWMArraySync.push({ name: ""+(i+1), displayName: "EPWM"+(i+1)+"SYNCPER" })
    ePWMArrayBlank.push()
    ePWMArrayBlank.push({ name: ""+(i+1), displayName: "EPWM"+(i+1)+"BLANK" })
}

/*Generate array for input signals*/
var numberOfPosInputSignals = 0
var numberOfNegInputSignals = 0
var asysPosSignalOptions = []
var asysNegSignalOptions = []
if (["F28002x","F28004x", "F280013x", "F280015x"].includes(Common.getDeviceName())){
    numberOfPosInputSignals = 5
}
else if (["F28003x","F28P55x"].includes(Common.getDeviceName())){
    numberOfPosInputSignals = 6
}
else if (["F28P65x"].includes(Common.getDeviceName())){
    numberOfPosInputSignals = 4
}

numberOfNegInputSignals = 2

for(var i=0;i<numberOfPosInputSignals;i++){
    asysPosSignalOptions.push(
        {name:""+i,displayName:"Input Signal "+i},
    )
}

for(var i=0;i<numberOfNegInputSignals;i++){
    asysNegSignalOptions.push(
        {name:""+i,displayName:"Input Signal "+i},
    )
}


var highConfig =[
    // configHighComparator: Sets the configuration for the high comparator.
    {
        name: "cmpssHighName",
        displayName : "Name",
        description : 'Select the CMPSS name for High Comparator',
        hidden      : false,
        default     : ""
    },
    {
        name        : "highCompNegative",
        displayName : "Negative input source",
        description : 'Specify high comparator negative input source',
        hidden      : false,
        default     : "CMPSS_INSRC_DAC",
        options     : [
            {name: "CMPSS_INSRC_DAC", displayName: "Input driven by internal DAC"},
            {name: "CMPSS_INSRC_PIN", displayName: "Input driven by external pin"},
        ],
        onChange    : onChangeHighCompDAC
    },
    {
        name        : "highCompInvert",
        displayName : "Output is inverted",
        description : 'High comparator output is inverted',
        hidden      : false,
        default     : false
    },
    {
        name        : "highCompAsynch",
        displayName : "Asynch OR Latch",
        description : 'Asynchronous high comparator output should be fed into an OR gate with the latched digital filter output before it is made available for CTRIPH or CTRIPOUTH.',
        hidden      : false,
        default     : false
    },
    // configOutputsHigh
    {
        name        : "highCTRIPOUT",
        displayName : "Signal driving CTRIPOUTH",
        description : 'Specify which signal drives CTRIPOUTH',
        hidden      : false,
        default     : "CMPSS_TRIPOUT_ASYNC_COMP",
        options     : [
            {name: "CMPSS_TRIPOUT_ASYNC_COMP",  displayName: "Asynchronous comparator output drives CTRIPOUT"},
            {name: "CMPSS_TRIPOUT_SYNC_COMP",   displayName: "Synchronous comparator output drives CTRIPOUT"},
            {name: "CMPSS_TRIPOUT_FILTER",      displayName: "Filter output drives CTRIPOUT"},
            {name: "CMPSS_TRIPOUT_LATCH",       displayName: "Latched filter output drives CTRIPOUT"},
        ],
    },
    {
        name        : "highCTRIP",
        displayName : "Signal driving CTRIPH",
        description : 'Specify which signal drives CTRIPH',
        hidden      : false,
        default     : "CMPSS_TRIP_ASYNC_COMP",
        options     : [
            {name: "CMPSS_TRIP_ASYNC_COMP",     displayName: "Asynchronous comparator output drives CTRIP"},
            {name: "CMPSS_TRIP_SYNC_COMP",      displayName: "Synchronous comparator output drives CTRIP"},
            {name: "CMPSS_TRIP_FILTER",         displayName: "Filter output drives CTRIP"},
            {name: "CMPSS_TRIP_LATCH",          displayName: "Latched filter output drives CTRIP"},
        ],
    },
    // setDACValueHigh
    {
        name        : "dacValHigh",
        displayName : "Set high comparator DAC value",
        description : 'Sets the value of the internal DAC of the high comparator.',
        hidden      : false,
        default     : 0
    },
    {
        name: "GROUP_HIGH_DIGITAL_FILTER",
        displayName: "Digital Filter Configuration",
        description: "",
        longDescription: "",
        collapsed: false,
        config: [
            // initFilterHigh
            {
                name        : "initFilterHigh",
                displayName : "Initialize Digital Filter",
                description : 'Initializes the digital filter of the high comparator.',
                hidden      : false,
                default     : false
            },
            // clearFilterLatchHigh
            {
                name        : "clearFilterLatchHigh",
                displayName : "Clear Filter Latch",
                description : 'Causes a software reset of the high comparator digital filter output latch.',
                hidden      : false,
                default     : false
            },
            // enableLatchResetOnPWSYNCHigh / disableLatchResetOnPWMSYNCHigh
            {
                name        : "latchResetHigh",
                displayName : "Reset output latch on EPWMSYNCPER",
                description : 'Enables reset of HIGH comparator digital filter output latch on EPWMSYNCPER',
                hidden      : false,
                default     : false
            },
            // configFilterHigh
            {
                name        : "samplePrescaleHigh",
                displayName : "Digital Filter Sample Prescale",
                description : 'The number of system clock cycles between samples.',
                hidden      : false,
                default     : 0
            },
            {
                name        : "sampleWindowHigh",
                displayName : "Digital Filter Sample Window",
                description : 'The number of FIFO samples to monitor.',
                hidden      : false,
                default     : 1
            },
            {
                name        : "thresholdHigh",
                displayName : "Digital Filter Threshold",
                description : 'The majority threshold of samples to change state.',
                hidden      : false,
                default     : 1
            },
            // configLatchOnPWMSYNC
            {
                name        : "configLatchHigh",
                displayName : "Reset Digital Filter Latch",
                description : 'Configures whether or not the digital filter latches are reset by EPWMSYNCPER in the high comparator.',
                hidden      : false,
                default     : false
            },
        ]
    },
]

if (["F280015x", "F28P65x"].includes(Common.getDeviceName()))
{
    highConfig = highConfig.concat([
        {
            name: "GROUP_RAMP_GENERATOR",
            displayName: "Ramp Generator Configuration",
            description: "",
            longDescription: "",
            collapsed: false,
            config: [
                // -rampHighDir
                {
                    name        : "rampHighDir",
                    displayName : "Ramp Direction",
                    description : "Sets the ramp direction for the high comparator",
                    hidden      : false,
                    default     : rampDirections[0].name,
                    options     : rampDirections
                },
                // -setMaxRampValue
                {
                    name        : "maxRampVal",
                    displayName : "Max Ramp Generator Reference Value",
                    description : 'Sets the ramp generator maximum reference value.',
                    hidden      : false,
                    default     : 0
                },
                // -setRampDecValue
                {
                    name        : "ramDecVal",
                    displayName : "Ramp Generator Decrement Value",
                    description : 'Sets the ramp generator decrement value.',
                    hidden      : false,
                    default     : 0
                },
                // -setRampDelayValue
                {
                    name        : "rampDelayVal",
                    displayName : "Ramp Generator Delay Value",
                    description : 'Sets the ramp generator delay value.',
                    hidden      : false,
                    default     : 0
                },
                // -CMPSS_setRampClockDividerHigh/CMPSS_setRampClockDividerLow
                {
                    name        : "rampClkDiv",
                    displayName : "Ramp Generator Clock Divider Value",
                    description : 'Sets the divider value to slow down the ramp clock; this increases the periods between steps. RAMPCLK = SYSCLK/(RAMPCLKDIV+1), where RAMPCLKDIV = {0...15}.',
                    hidden      : false,
                    default     : clkDivs[0].name,
                    options     : clkDivs
                },
                {
                    name: "rampClkFreq",
                    displayName : "Ramp Clock Frequency [MHz]",
                    getValue    : (inst) => {
                        if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV1")
                        {
                            return (Common.getSYSCLK() / 1);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV2")
                        {
                            return (Common.getSYSCLK() / 2);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV3")
                        {
                            return (Common.getSYSCLK() / 3);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV4")
                        {
                            return (Common.getSYSCLK() / 4);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV5")
                        {
                            return (Common.getSYSCLK() / 5);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV6")
                        {
                            return (Common.getSYSCLK() / 6);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV7")
                        {
                            return (Common.getSYSCLK() / 7);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV8")
                        {
                            return (Common.getSYSCLK() / 8);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV9")
                        {
                            return (Common.getSYSCLK() / 9);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV10")
                        {
                            return (Common.getSYSCLK() / 10);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV11")
                        {
                            return (Common.getSYSCLK() / 11);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV12")
                        {
                            return (Common.getSYSCLK() / 12);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV13")
                        {
                            return (Common.getSYSCLK() / 13);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV14")
                        {
                            return (Common.getSYSCLK() / 14);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV15")
                        {
                            return (Common.getSYSCLK() / 15);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV16")
                        {
                            return (Common.getSYSCLK() / 16);
                        }
                    },
                    default : Common.SYSCLK_getMaxMHz(),
                },
                {
                    name        : "pwmSyncSrc",
                    displayName : "EPWMSYNCPER source number",
                    description : 'Specify the number of the EPWMSYNCPER source',
                    hidden      : false,
                    default     : ePWMArraySync[0].name,
                    options     : ePWMArraySync
                },
                {
                    name        : "useRampValShdw",
                    displayName : "Ramp Generator Reset",
                    description : 'Indicate whether the ramp generator should reset with the value from the ramp max reference value shadow register or with the latched ramp max reference value',
                    hidden      : false,
                    default     : "true",
                    options     : [
                        {name: "true",  displayName: "load the ramp generator from the shadow register"},
                        {name: "false", displayName: "load the ramp generator from the latched value."},
                    ],
                },
            ]
        },
    ])
}
else
{
    highConfig = highConfig.concat([
        {
            name: "GROUP_RAMP_GENERATOR",
            displayName: "Ramp Generator Configuration",
            description: "",
            longDescription: "",
            collapsed: false,
            config: [
                // -setMaxRampValue
                {
                    name        : "maxRampVal",
                    displayName : "Max Ramp Generator Reference Value",
                    description : 'Sets the ramp generator maximum reference value.',
                    hidden      : false,
                    default     : 0
                },
                // -setRampDecValue
                {
                    name        : "ramDecVal",
                    displayName : "Ramp Generator Decrement Value",
                    description : 'Sets the ramp generator decrement value.',
                    hidden      : false,
                    default     : 0
                },
                // -setRampDelayValue
                {
                    name        : "rampDelayVal",
                    displayName : "Ramp Generator Delay Value",
                    description : 'Sets the ramp generator delay value.',
                    hidden      : false,
                    default     : 0
                },
                // -CMPSS_setRampClockDividerHigh/CMPSS_setRampClockDividerLow
                {
                    name        : "rampClkDiv",
                    displayName : "Ramp Generator Clock Divider Value",
                    description : 'Sets the divider value to slow down the ramp clock; this increases the periods between steps. RAMPCLK = SYSCLK/(RAMPCLKDIV+1), where RAMPCLKDIV = {0...15}.',
                    hidden      : false,
                    default     : clkDivs[0].name,
                    options     : clkDivs
                },
                {
                    name: "rampClkFreq",
                    displayName : "Ramp Clock Frequency [MHz]",
                    getValue    : (inst) => {
                        if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV1")
                        {
                            return (Common.getSYSCLK() / 1);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV2")
                        {
                            return (Common.getSYSCLK() / 2);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV3")
                        {
                            return (Common.getSYSCLK() / 3);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV4")
                        {
                            return (Common.getSYSCLK() / 4);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV5")
                        {
                            return (Common.getSYSCLK() / 5);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV6")
                        {
                            return (Common.getSYSCLK() / 6);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV7")
                        {
                            return (Common.getSYSCLK() / 7);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV8")
                        {
                            return (Common.getSYSCLK() / 8);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV9")
                        {
                            return (Common.getSYSCLK() / 9);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV10")
                        {
                            return (Common.getSYSCLK() / 10);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV11")
                        {
                            return (Common.getSYSCLK() / 11);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV12")
                        {
                            return (Common.getSYSCLK() / 12);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV13")
                        {
                            return (Common.getSYSCLK() / 13);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV14")
                        {
                            return (Common.getSYSCLK() / 14);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV15")
                        {
                            return (Common.getSYSCLK() / 15);
                        }
                        else if(inst.rampClkDiv == "CMPSS_RAMP_CLOCK_DIV16")
                        {
                            return (Common.getSYSCLK() / 16);
                        }
                    },
                    default : Common.SYSCLK_getMaxMHz(),
                },
                {
                    name        : "pwmSyncSrc",
                    displayName : "EPWMSYNCPER source number",
                    description : 'Specify the number of the EPWMSYNCPER source',
                    hidden      : false,
                    default     : ePWMArraySync[0].name,
                    options     : ePWMArraySync
                },
                {
                    name        : "useRampValShdw",
                    displayName : "Ramp Generator Reset",
                    description : 'Indicate whether the ramp generator should reset with the value from the ramp max reference value shadow register or with the latched ramp max reference value',
                    hidden      : false,
                    default     : "true",
                    options     : [
                        {name: "true",  displayName: "load the ramp generator from the shadow register"},
                        {name: "false", displayName: "load the ramp generator from the latched value."},
                    ],
                },
            ]
        },
    ])
}

if (["F28002x","F28003x","F28P55x","F280013x","F280015x","F28004x", "F28P65x"].includes(Common.getDeviceName())){
    highConfig = highConfig.concat([
        {
            name: "GROUP_CMPSS_MUX_HIGH",
            displayName: "CMPSS MUX Select",
            description: "",
            longDescription: "",
            collapsed: false,
            config: [
                // ASysCtl_selectCMPHPMux : options vary per device
                {
                    name        : "asysCMPHPMXSELValue",
                    displayName : "CMPHPMXSEL",
                    description : 'Select the value for CMPHPMXSEL.',
                    hidden      : false,
                    default     : asysPosSignalOptions[0].name,
                    options     : asysPosSignalOptions
                },
                {
                    name        : "asysCMPHPMXSELPinInfo",
                    displayName : "Selected MUX Signal for HP input",
                    description : 'Pin Number and Name for selected HP signal.',
                    hidden      : false,
                    default     : Pinmux.getDevicePinInfoDescription(defaultCMPSSPinInfos),
                    getValue    : calculateDevicePinNameHigh
                },

                // ASysCtl_selectCMPHNMux : options vary per device
                {
                    name        : "asysCMPHNMXSELValue",
                    displayName : "CMPHNMXSEL",
                    description : 'Select the value for CMPHNMXSEL.',
                    hidden      : true,
                    default     : asysNegSignalOptions[1].name,
                    options     : asysNegSignalOptions
                },
                {
                    name        : "asysCMPHNMXSELPinInfo",
                    displayName : "Selected MUX Signal for HN input",
                    description : 'Pin Number and Name for selected HN signal.',
                    hidden      : true,
                    default     : Pinmux.getDevicePinInfoDescription(defaultCMPSSNegPinInfos),
                    getValue    : calculateDevicePinNameHighNeg
                },
            ]
        },
    ])
}
var lowConfig =[
    // configLowComparator: Sets the configuration for the low comparator.
    {
        name: "cmpssLowName",
        displayName : "Name",
        description : 'Select the CMPSS name for Low Comparator',
        hidden      : false,
        default     : ""
    },
    {
        name        : "lowCompNegative",
        displayName : "Negative input source",
        description : 'Specify the high comparator negative input source',
        hidden      : false,
        default     : "CMPSS_INSRC_DAC",
        options     : [
            {name: "CMPSS_INSRC_DAC", displayName: "Input driven by internal DAC"},
            {name: "CMPSS_INSRC_PIN", displayName: "Input driven by external pin"},
        ],
        onChange    : onChangeLowCompDAC
    },
    {
        name        : "lowCompInvert",
        displayName : "Output is inverted",
        description : 'Low comparator output is inverted',
        hidden      : false,
        default     : false
    },
    {
        name        : "lowCompAsynch",
        displayName : "Asynch OR Latch",
        description : 'Asynchronous low comparator output should be fed into an OR gate with the latched digital filter output before it is made available for CTRIPH or CTRIPOUTH.',
        hidden      : false,
        default     : false
    },
    // configOutputsLow
    {
        name        : "lowCTRIPOUT",
        displayName : "Signal driving CTRIPOUTL",
        description : 'Specify which signal drives CTRIPOUTL',
        hidden      : false,
        default     : "CMPSS_TRIPOUT_ASYNC_COMP",
        options     : [
            {name: "CMPSS_TRIPOUT_ASYNC_COMP",  displayName: "Asynchronous comparator output drives CTRIPOUT"},
            {name: "CMPSS_TRIPOUT_SYNC_COMP",   displayName: "Synchronous comparator output drives CTRIPOUT"},
            {name: "CMPSS_TRIPOUT_FILTER",      displayName: "Filter output drives CTRIPOUT"},
            {name: "CMPSS_TRIPOUT_LATCH",       displayName: "Latched filter output drives CTRIPOUT"},
        ],
    },
    {
        name        : "lowCTRIP",
        displayName : "Signal driving CTRIPL",
        description : 'Specify which signal drives CTRIPL',
        hidden      : false,
        default     : "CMPSS_TRIP_ASYNC_COMP",
        options     : [
            {name: "CMPSS_TRIP_ASYNC_COMP",     displayName: "Asynchronous comparator output drives CTRIP"},
            {name: "CMPSS_TRIP_SYNC_COMP",      displayName: "Synchronous comparator output drives CTRIP"},
            {name: "CMPSS_TRIP_FILTER",         displayName: "Filter output drives CTRIP"},
            {name: "CMPSS_TRIP_LATCH",          displayName: "Latched filter output drives CTRIP"},
        ],
    },
    // setDACValueLow
    {
        name        : "dacValLow",
        displayName : "Set low comparator DAC value",
        description : 'Sets the value of the internal DAC of the low comparator.',
        hidden      : false,
        default     : 0
    },
    {
        name: "GROUP_LOW_DIGITAL_FILTER",
        displayName: "Digital Filter Configuration",
        description: "",
        longDescription: "",
        collapsed: false,
        config: [
            // initFilterLow
            {
                name        : "initFilterLow",
                displayName : "Initialize Digital Filter",
                description : 'Initializes the digital filter of the low comparator.',
                hidden      : false,
                default     : false
            },
            // clearFilterLatchLow
            {
                name        : "clearFilterLatchLow",
                displayName : "Clear Filter Latch",
                description : 'Causes a software reset of the low comparator digital filter output latch.',
                hidden      : false,
                default     : false
            },
            // enableLatchResetOnPWMSYNCLow / enableLatchResetOnPWMSYNCLow
            {
                name        : "latchResetLow",
                displayName : "Reset output latch on EPWMSYNCPER",
                description : 'Enables reset of LOW comparator digital filter output latch on EPWMSYNCPER',
                hidden      : false,
                default     : false
            },
            // configFilterLow
            {
                name        : "samplePrescaleLow",
                displayName : "Digital Filter Sample Prescale",
                description : 'The number of system clock cycles between samples.',
                hidden      : false,
                default     : 0
            },
            {
                name        : "sampleWindowLow",
                displayName : "Digital Filter Sample Window",
                description : 'The number of FIFO samples to monitor.',
                hidden      : false,
                default     : 1
            },
            {
                name        : "thresholdLow",
                displayName : "Digital Filter Threshold",
                description : 'The majority threshold of samples to change state.',
                hidden      : false,
                default     : 1
            },
            // configLatchOnPWMSYNC
            {
                name        : "configLatchLow",
                displayName : "Reset Digital Filter Latch",
                description : 'Configures whether or not the digital filter latches are reset by EPWMSYNCPER in the low comparator.',
                hidden      : false,
                default     : false
            },
        ]
    },
]

if (["F280015x", "F28P65x"].includes(Common.getDeviceName())){
    lowConfig = lowConfig.concat([
        {
            name: "GROUP_RAMP_GENERATOR_LOW",
            displayName: "Ramp Generator Configuration",
            description: "",
            longDescription: "",
            collapsed: false,
            config: [
                // -rampLowDir
                {
                    name        : "rampLowDir",
                    displayName : "Ramp Direction",
                    description : "Sets the ramp direction for the low comparator",
                    hidden      : false,
                    default     : rampDirections[0].name,
                    options     : rampDirections
                },
                // -setMaxRampValue
                {
                    name        : "maxRampValLow",
                    displayName : "Max Ramp Generator Reference Value",
                    description : 'Sets the ramp generator maximum reference value.',
                    hidden      : false,
                    default     : 0
                },
                // -setRampDecValue
                {
                    name        : "ramDecValLow",
                    displayName : "Ramp Generator Decrement Value",
                    description : 'Sets the ramp generator decrement value.',
                    hidden      : false,
                    default     : 0
                },
                // -setRampDelayValue
                {
                    name        : "rampDelayValLow",
                    displayName : "Ramp Generator Delay Value",
                    description : 'Sets the ramp generator delay value.',
                    hidden      : false,
                    default     : 0
                },
                // -CMPSS_setRampClockDividerHigh/CMPSS_setRampClockDividerLow
                {
                    name        : "rampClkDivLow",
                    displayName : "Ramp Generator Clock Divider Value",
                    description : 'Sets the divider value to slow down the ramp clock; this increases the periods between steps. RAMPCLK = SYSCLK/(RAMPCLKDIV+1), where RAMPCLKDIV = {0...15}.',
                    hidden      : false,
                    default     : clkDivs[0].name,
                    options     : clkDivs
                },
                {
                    name: "rampClkFreqLow",
                    displayName : "Ramp Clock Frequency [MHz]",
                    getValue    : (inst) => {
                        if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV1")
                        {
                            return (Common.getSYSCLK() / 1);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV2")
                        {
                            return (Common.getSYSCLK() / 2);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV3")
                        {
                            return (Common.getSYSCLK() / 3);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV4")
                        {
                            return (Common.getSYSCLK() / 4);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV5")
                        {
                            return (Common.getSYSCLK() / 5);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV6")
                        {
                            return (Common.getSYSCLK() / 6);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV7")
                        {
                            return (Common.getSYSCLK() / 7);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV8")
                        {
                            return (Common.getSYSCLK() / 8);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV9")
                        {
                            return (Common.getSYSCLK() / 9);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV10")
                        {
                            return (Common.getSYSCLK() / 10);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV11")
                        {
                            return (Common.getSYSCLK() / 11);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV12")
                        {
                            return (Common.getSYSCLK() / 12);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV13")
                        {
                            return (Common.getSYSCLK() / 13);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV14")
                        {
                            return (Common.getSYSCLK() / 14);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV15")
                        {
                            return (Common.getSYSCLK() / 15);
                        }
                        else if(inst.rampClkDivLow == "CMPSS_RAMP_CLOCK_DIV16")
                        {
                            return (Common.getSYSCLK() / 16);
                        }
                    },
                    default : Common.SYSCLK_getMaxMHz(),
                },
                {
                    name        : "pwmSyncSrcLow",
                    displayName : "EPWMSYNCPER source number",
                    description : 'Specify the number of the EPWMSYNCPER source',
                    hidden      : false,
                    default     : ePWMArraySync[0].name,
                    options     : ePWMArraySync
                },
                {
                    name        : "useRampValShdwLow",
                    displayName : "Ramp Generator Reset",
                    description : 'Indicate whether the ramp generator should reset with the value from the ramp max reference value shadow register or with the latched ramp max reference value',
                    hidden      : false,
                    default     : "true",
                    options     : [
                        {name: "true",  displayName: "load the ramp generator from the shadow register"},
                        {name: "false", displayName: "load the ramp generator from the latched value."},
                    ],
                },
            ]
        },
    ])
}

if (["F28002x","F28003x","F28P55x","F280013x","F280015x","F28004x", "F28P65x"].includes(Common.getDeviceName())){
    lowConfig = lowConfig.concat([
        {
            name: "GROUP_CMPSS_MUX_LOW",
            displayName: "CMPSS MUX Select",
            description: "",
            longDescription: "",
            collapsed: false,
            config: [
                // ASysCtl_selectCMPLPMux  : options vary per device
                {
                    name        : "asysCMPLPMXSELValue",
                    displayName : "CMPLPMXSEL",
                    description : 'Select the value for CMPLPMXSEL.',
                    hidden      : false,
                    default     : asysPosSignalOptions[0].name,
                    options     : asysPosSignalOptions
                },
                {
                    name        : "asysCMPLPMXSELPinInfo",
                    displayName : "Selected MUX Signal for LP input",
                    description : 'Pin Number and Name for selected LP signal.',
                    hidden      : false,
                    default     : Pinmux.getDevicePinInfoDescription(defaultCMPSSPinInfos),
                    getValue    : calculateDevicePinNameLow
                },

                // ASysCtl_selectCMPLNMux  : options vary per device
                {
                    name        : "asysCMPLNMXSELValue",
                    displayName : "CMPLNMXSEL",
                    description : 'Select the value for CMPLNMXSEL.',
                    hidden      : true,
                    default     : asysNegSignalOptions[1].name,
                    options     : asysNegSignalOptions
                },
                {
                    name        : "asysCMPLNMXSELPinInfo",
                    displayName : "Selected MUX Signal for LN input",
                    description : 'Pin Number and Name for selected LN signal.',
                    hidden      : true,
                    default     : Pinmux.getDevicePinInfoDescription(defaultCMPSSNegPinInfos),
                    getValue    : calculateDevicePinNameLowNeg
                },
            ]
        },
    ])
}

/* Array of CAN configurables that are common across device families */
let config = [
    {
        name        : "cmpssBase",
        displayName : "CMPSS Instance",
        description : 'Instance of the CMPSS used.',
        hidden      : false,
        default     : CMPSS_INSTANCE[0].name,
        options     : CMPSS_INSTANCE,
    },
    // enableModule / disableModule
    {
        name        : "enableModule",
        displayName : "Enable module",
        description : 'Enables the CMPSS module.',
        hidden      : false,
        default     : false
    },
    // Group for High Comparator Configuration Functions
    {
        name: "GROUP_HIGH_COMPARATOR",
        displayName: "High Comparator Configuration",
        description: "",
        longDescription: "",
        config: highConfig
    },
    // Group for Low Comparator Configuration Functions
    {
        name: "GROUP_LOW_COMPARATOR",
        displayName: "Low Comparator Configuration",
        description: "",
        longDescription: "",
        config: lowConfig
    },
];

// configDAC
var cmpss_dac_config = [
    {
        name        : "dacValLoad",
        displayName : "High DAC value load",
        description : 'When is DAC value loaded from shadow register',
        hidden      : false,
        default     : "CMPSS_DACVAL_SYSCLK",
        options     : [
            {name: "CMPSS_DACVAL_SYSCLK", displayName: "DAC value updated from SYSCLK"},
            {name: "CMPSS_DACVAL_PWMSYNC", displayName: "DAC value updated from EPWMSYNCPER"},
        ],
    },
]
if (!["F280013x", "F280015x", "F28P65x"].includes(Common.getDeviceName())){
    cmpss_dac_config.push(
        {
            name        : "dacRefVoltage",
            displayName : "High DAC reference voltage",
            description : 'Specify DAC reference voltage',
            hidden      : false,
            default     : "CMPSS_DACREF_VDDA",
            options     : [
                {name: "CMPSS_DACREF_VDDA", displayName: "VDDA is the voltage reference"},
                {name: "CMPSS_DACREF_VDAC", displayName: "VDAC is the voltage reference"},
            ],
        },
    );
}
cmpss_dac_config.push(
    {
        name        : "dacValSource",
        displayName : "High DAC value source",
        description : 'Specify DAC value source',
        hidden      : false,
        default     : "CMPSS_DACSRC_SHDW",
        options     : [
            {name: "CMPSS_DACSRC_SHDW", displayName: "DAC value updated from shadow register"},
            {name: "CMPSS_DACSRC_RAMP", displayName: "DAC value is updated from the ramp register"},
        ],
    },
)
config = config.concat([
    // DAC Group
    {
        name: "GROUP_CMP_DAC",
        displayName: "DAC Configuration",
        description: "",
        longDescription: "",
        collapsed: false,
        config: cmpss_dac_config
    },
]);
if (["F280015x", "F28P65x"].includes(Common.getDeviceName())){
    // configDACLow
    var cmpss_dac_lowConfig = [
        {
            name        : "lowDacValSource",
            displayName : "Low DAC value source",
            description : 'Specify Low DAC value source',
            hidden      : false,
            default     : "CMPSS_DACSRC_SHDW",
            options     : [
                {name: "CMPSS_DACSRC_SHDW", displayName: "DAC value updated from shadow register"},
                {name: "CMPSS_DACSRC_RAMP", displayName: "DAC value is updated from the ramp register"},
            ],
        },
    ]
    config = config.concat([
        // DAC Group
        {
            name: "GROUP_CMP_DAC",
            displayName: "Low DAC Configuration",
            description: "",
            longDescription: "",
            collapsed: false,
            config: cmpss_dac_lowConfig
        },
    ]);
}
if (["F28P65x"].includes(Common.getDeviceName())){
    // configDE
    var cmpss_de_config = [
        {
            name        : "deEnable",
            displayName : "Enable Diode Emulation Support",
            longDescription : "Using Diode Emulation allows a PWMSYNC signal to determine when to use different threshold register for the DAC values; this threshold can be made to have a tighter limit.",
            hidden      : false,
            default     : false
        },
        {
            name        : "deDACValHigh",
            displayName : "Set high comparator DAC value in Diode Emulation",
            description : 'Sets the value of the internal DAC of the high comparator when using Diode Emulation.',
            hidden      : false,
            default     : 0
        },
        {
            name        : "deDACValLow",
            displayName : "Set low comparator DAC value in Diode Emulation",
            description : 'Sets the value of the internal DAC of the low comparator when using Diode Emulation.',
            hidden      : false,
            default     : 0
        },
        {
            name        : "deactiveSel",
            displayName : "Select Input for Diode Emulation",
            description : 'Selects the Diode Emulation Active signal from the ePWM.',
            hidden      : false,
            default     : device_driverlib_peripheral.CMPSS_DEActiveSelect[0].name,
            options     : device_driverlib_peripheral.CMPSS_DEActiveSelect
        },
    ]

    config = config.concat([
        // Diode Emulation Group
        {
            name: "GROUP_CMP_DE",
            displayName: "Diode Emulation Support Configuration",
            collapsed: false,
            config: cmpss_de_config
        },
    ]);
}

config = config.concat([
    // setHysteresis
    {
        name        : "hysteresisVal",
        displayName : "Hysteresis",
        description : 'Sets the the amount of hysteresis on the comparator inputs.',
        hidden      : false,
        default     : "0",
        options: [
            {name:"0",displayName:"None"},
            {name:"1",displayName:"1x"},
            {name:"2",displayName:"2x"},
            {name:"3",displayName:"3x"},
            {name:"4",displayName:"4x"},
        ]
    },
]);


if (["F28002x","F28003x","F28P55x","F280013x","F280015x","F28004x","F2838x", "F28P65x"].includes(Common.getDeviceName())){
    config = config.concat([
        // configBlanking
        {
            name        : "configBlanking",
            displayName : "Blanking Signal",
            description : 'Sets the ePWM module blanking signal that holds trip in reset.',
            hidden      : false,
            default     : ePWMArrayBlank[0].name,
            options     : ePWMArrayBlank
        },
        // enableBlanking / disableBlanking
        {
            name        : "enableBlanking",
            displayName : "Enable Blanking Signal",
            description : 'Enables an ePWM blanking signal to hold trip in reset.',
            hidden      : false,
            default     : false
        },
    ]);
}

function onChangeHighCompDAC(inst, ui)
{
    if((ui.asysCMPHNMXSELValue) && (ui.asysCMPHNMXSELPinInfo) && (inst.highCompNegative == "CMPSS_INSRC_DAC"))
    {
        ui.asysCMPHNMXSELValue.hidden = true;
        ui.asysCMPHNMXSELPinInfo.hidden = true;
    }
    else if((ui.asysCMPHNMXSELValue) && (ui.asysCMPHNMXSELPinInfo))
    {
        ui.asysCMPHNMXSELValue.hidden = false;
        ui.asysCMPHNMXSELPinInfo.hidden = false;
    }
}

function onChangeLowCompDAC(inst, ui)
{
    if((ui.asysCMPLNMXSELValue) && (ui.asysCMPLNMXSELPinInfo) && (inst.lowCompNegative == "CMPSS_INSRC_DAC"))
    {
        ui.asysCMPLNMXSELValue.hidden = true;
        ui.asysCMPLNMXSELPinInfo.hidden = true;
    }
    else if((ui.asysCMPLNMXSELValue) && (ui.asysCMPLNMXSELPinInfo))
    {
        ui.asysCMPLNMXSELValue.hidden = false;
        ui.asysCMPLNMXSELPinInfo.hidden = false;
    }
}

function onValidate(inst, validation) {
    //
    // Check Multicontext
    //
    if (Common.isContextCPU2()) {
        if (Common.isMultiCoreSysConfig()) {
            //
            // Check if the analog module is added on CPU1 if the current context is CPU2
            //
            if (Common.isModuleOnOtherContext("/driverlib/analog.js") == false) {
                validation.logError(
                    "The ANALOG PinMux module needs to be added on CPU1 when a CMPSS instance is added on CPU2",inst,"cmpssBase");
            }
        } 
        else {
            validation.logWarning(
                "The ANALOG PinMux module needs to be added on CPU1 when a CMPSS instance is added on CPU2",inst,"cmpssBase");
        } 
    }
    var usedCMPSSInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedCMPSSInsts.push(instance_obj.cmpssBase);
    }

    var otherContexts = Common.getOtherContextNames()
    for (var cntx of otherContexts)
    {
        var onOtherCntx = Common.getModuleForCore(inst.$module.$name, cntx);
        if (onOtherCntx)
        {
            for (var instance_index in onOtherCntx.$instances)
            {
                var instance_obj = onOtherCntx.$instances[instance_index];
                usedCMPSSInsts.push(instance_obj.cmpssBase);
            }
        }
    }

    var duplicatesResult = Common.findDuplicates(usedCMPSSInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The CMPSS Instance used. Duplicates: " + allDuplicates,
            inst, "cmpssBase");
    }

    if (inst.dacValHigh < 0 || inst.dacValHigh > 4095)
    {
        validation.logError(
            "Enter an integer for high comparator DAC value between 0 and 4,095!",
            inst, "dacValHigh");
    }
    if (!Number.isInteger(inst.dacValHigh))
    {
        validation.logError(
            "High comparator DAC value must be an integer",
            inst, "dacValHigh");
    }

    if (inst.dacValLow < 0 || inst.dacValLow > 4095)
    {
        validation.logError(
            "Enter an integer for low comparator DAC value between 0 and 4,095!",
            inst, "dacValLow");
    }
    if (!Number.isInteger(inst.dacValLow))
    {
        validation.logError(
            "Low comparator DAC value must be an integer",
            inst, "dacValLow");
    }
    if((["F28P65x"].includes(Common.getDeviceName())))
    {
        if(inst.asysCMPHPMXSELValue == "No Device Pin Found")
        {
            validation.logError("There is no connection for the selected input!", inst, "asysCMPHPMXSELValue");
        }
        if(inst.asysCMPLPMXSELValue == "No Device Pin Found")
        {
            validation.logError("There is no connection for the selected input!", inst, "asysCMPLPMXSELValue");
        }
        if (inst.deDACValLow < 0 || inst.deDACValLow > 4095)
        {
            validation.logError(
                "Enter an integer for low comparator DAC value between 0 and 4,095!",
                inst, "deDACValLow");
        }
        if (!Number.isInteger(inst.deDACValLow))
        {
            validation.logError(
                "Low comparator DAC value must be an integer",
                inst, "deDACValLow");
        }
        if (inst.deDACValHigh < 0 || inst.deDACValHigh > 4095)
        {
            validation.logError(
                "Enter an integer for low comparator DAC value between 0 and 4,095!",
                inst, "deDACValHigh");
        }
        if (!Number.isInteger(inst.deDACValHigh))
        {
            validation.logError(
                "Low comparator DAC value must be an integer",
                inst, "deDACValHigh");
        }
    }

    if (inst.maxRampVal < 0 || inst.maxRampVal > 65535)
    {
        validation.logError(
            "Enter an integer for Max Ramp Generator Reference Value between 0 and 65,535!",
            inst, "maxRampVal");
    }
    if (!Number.isInteger(inst.maxRampVal))
    {
        validation.logError(
            "Max Ramp Generator Reference Value must be an integer",
            inst, "maxRampVal");
    }

    if (inst.ramDecVal < 0 || inst.ramDecVal > 8191)
    {
        validation.logError(
            "Enter an integer for Ramp Generator Decrement Value between 0 and 8,191!",
            inst, "ramDecVal");
    }
    if (!Number.isInteger(inst.ramDecVal))
    {
        validation.logError(
            "Ramp Generator Decrement Value must be an integer",
            inst, "ramDecVal");
    }

    if (inst.rampDelayVal < 0 || inst.rampDelayVal > 8191)
    {
        validation.logError(
            "Enter an integer for Ramp Generator Delay Value between 0 and 8,191!",
            inst, "rampDelayVal");
    }
    if (!Number.isInteger(inst.rampDelayVal))
    {
        validation.logError(
            "Ramp Generator Delay Value must be an integer",
            inst, "rampDelayVal");
    }

    if((["F28P65x"].includes(Common.getDeviceName())) && (inst.deEnable == false))
    {
        validation.logInfo("Diode Emulation support is not enabled; the settings can be configured and then Diode Emulation can be enabled at any point", inst, "deEnable");
    }

    if(["F280015x", "F28P65x"].includes(Common.getDeviceName()))
    {
        if (inst.maxRampValLow < 0 || inst.maxRampValLow > 65535)
        {
            validation.logError(
                "Enter an integer for Max Ramp Generator Reference Value between 0 and 65,535!",
                inst, "maxRampValLow");
        }
        if (!Number.isInteger(inst.maxRampValLow))
        {
            validation.logError(
                "Max Ramp Generator Reference Value must be an integer",
                inst, "maxRampValLow");
        }
    
        if (inst.ramDecValLow < 0 || inst.ramDecValLow > 8191)
        {
            validation.logError(
                "Enter an integer for Ramp Generator Decrement Value between 0 and 8,191!",
                inst, "ramDecValLow");
        }
        if (!Number.isInteger(inst.ramDecValLow))
        {
            validation.logError(
                "Ramp Generator Decrement Value must be an integer",
                inst, "ramDecValLow");
        }
    
        if (inst.rampDelayValLow < 0 || inst.rampDelayValLow > 8191)
        {
            validation.logError(
                "Enter an integer for Ramp Generator Delay Value between 0 and 8,191!",
                inst, "rampDelayValLow");
        }
        if (!Number.isInteger(inst.rampDelayValLow))
        {
            validation.logError(
                "Ramp Generator Delay Value must be an integer",
                inst, "rampDelayValLow");
        }
    
        if ((inst.pwmSyncSrcLow < 0 || inst.pwmSyncSrcLow > 16) && !(["F28P65x"].includes(Common.getDeviceName())))
        {
            validation.logError(
                "Enter an integer for Ramp EPWMSYNCPER source number between 1 and 16!",
                inst, "pwmSyncSrcLow");
        }
    }

    if (["F28002x","F28003x","F28P55x","F280013x","F280015x","F28004x","F2838x", "F28P65x"].includes(Common.getDeviceName())){
        if (inst.configBlanking < 1 || inst.configBlanking > 16)
        {
            validation.logError(
                "Enter an integer for VALUE_NAME between 1 and 16!",
                inst, "configBlanking");
        }
    }
    if (["F28P65x"].includes(Common.getDeviceName()))
    {
        if (inst.samplePrescaleHigh < 0 || inst.samplePrescaleHigh > 16777215)
        {
            validation.logError(
                "Enter an integer for Digital Filter Sample Prescale between 0 and 16,777,215!",
                inst, "samplePrescaleHigh");
        }
    }
    else if (["F28003x","F28P55x","F280013x","F280015x"].includes(Common.getDeviceName()))
    {
        if (inst.samplePrescaleHigh < 0 || inst.samplePrescaleHigh > 65535)
        {
            validation.logError(
                "Enter an integer for Digital Filter Sample Prescale between 0 and 65,535!",
                inst, "samplePrescaleHigh");
        }
    }
    else{
        if (inst.samplePrescaleHigh < 0 || inst.samplePrescaleHigh > 1023)
        {
            validation.logError(
                "Enter an integer for Digital Filter Sample Prescale between 0 and 1,023!",
                inst, "samplePrescaleHigh");
        }
    }
    if (!Number.isInteger(inst.samplePrescaleHigh))
    {
        validation.logError(
            "Digital Filter Sample Prescale must be an integer",
            inst, "samplePrescaleHigh");
    }

    if (inst.sampleWindowHigh < 1 || inst.sampleWindowHigh > 32)
    {
        validation.logError(
            "Enter an integer for Digital Filter Sample Window between 1 and 32!",
            inst, "sampleWindowHigh");
    }
    if (!Number.isInteger(inst.sampleWindowHigh))
    {
        validation.logError(
            "Digital Filter Sample Window must be an integer",
            inst, "sampleWindowHigh");
    }

    if (!(inst.thresholdHigh > (inst.sampleWindowHigh/2)) || !(inst.thresholdHigh <= inst.sampleWindowHigh))
    {
        validation.logError(
            "Enter an integer for Digital Filter Threshold between "+Math.ceil((inst.sampleWindowHigh + 1)/2)+" and "+inst.sampleWindowHigh,
            inst, "thresholdHigh");
    }
    if (!Number.isInteger(inst.thresholdHigh))
    {
        validation.logError(
            "Digital Filter Threshold must be an integer",
            inst, "thresholdHigh");
    }

    if (["F28P65x"].includes(Common.getDeviceName()))
    {
        if(inst.samplePrescaleLow < 0 || inst.samplePrescaleLow > 16777215)
        {
            validation.logError(
                "Enter an integer for Digital Filter Sample Prescale between 0 and 16,777,215!",
                inst, "samplePrescaleLow");
        }
    }
    else if (["F28003x","F28P55x","F280013x","F280015x"].includes(Common.getDeviceName()))
    {
        if (inst.samplePrescaleLow < 0 || inst.samplePrescaleLow > 65535)
        {
            validation.logError(
                "Enter an integer for Digital Filter Sample Prescale between 0 and 65,535!",
                inst, "samplePrescaleLow");
        }
    }
    else if (inst.samplePrescaleLow < 0 || inst.samplePrescaleLow > 1023)
    {
        validation.logError(
            "Enter an integer for Digital Filter Sample Prescale between 0 and 1,023!",
            inst, "samplePrescaleLow");
    }
    if (!Number.isInteger(inst.samplePrescaleLow))
    {
        validation.logError(
            "Digital Filter Sample Prescale must be an integer",
            inst, "samplePrescaleLow");
    }

    if (inst.sampleWindowLow < 1 || inst.sampleWindowLow > 32)
    {
        validation.logError(
            "Enter an integer for Digital Filter Sample Window between 1 and 32!",
            inst, "sampleWindowLow");
    }
    if (!Number.isInteger(inst.sampleWindowLow))
    {
        validation.logError(
            "Digital Filter Sample Window must be an integer",
            inst, "sampleWindowLow");
    }

    if (!(inst.thresholdLow > (inst.sampleWindowLow/2)) || (!(inst.thresholdLow <= inst.sampleWindowLow)))
    {
        validation.logError(
            "Enter an integer for Digital Filter Threshold between "+Math.ceil((inst.sampleWindowLow + 1)/2)+" and "+inst.sampleWindowLow,
            inst, "thresholdLow");
    }
    if (!Number.isInteger(inst.thresholdLow))
    {
        validation.logError(
            "Digital Filter Threshold must be an integer",
            inst, "thresholdLow");
    }

    if ((inst.pwmSyncSrc < 0 || inst.pwmSyncSrc > 16) && !(["F28P65x"].includes(Common.getDeviceName())))
    {
        validation.logError(
            "Enter an integer for Ramp EPWMSYNCPER source number between 1 and 16!",
            inst, "pwmSyncSrc");
    }


    var selectedInterfaces = null;
    var allInterfaces = null;
    if (Common.isContextCPU1()) {
        if (Common.peripheralCount("ANALOG") > 0)
        {
            selectedInterfaces = Pinmux.getPeripheralUseCaseInterfaces(inst.analog, "ANALOG", inst.analog.useCase);
            allInterfaces = Pinmux.getPeripheralUseCaseInterfaces(inst.analog, "ANALOG", "ALL");
        }
    }
    if (["F28002x","F28003x","F28P55x","F280013x","F280015x","F28004x", "F28P65x"].includes(Common.getDeviceName())){
        if (inst.asysCMPHPMXSELPinInfo == Pinmux.NO_DEVICE_PIN_FOUND)
        {
            validation.logError(
                "Signal not available for this device, select a valid signal!",
                inst, "asysCMPHPMXSELValue");
        }
        else
        {
            var tempPinName = ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPHPMXSELValue].displayName
            var tempPinNameH = ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPHPMXSELValue].displayName
            var tempPinInfoH = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))

            var allPinsMustBeConfigured = true;

            if ((tempPinName == "B5" || tempPinName == "B11") && Common.getDevicePart() == "F28003x_100PZ")
            {
                validation.logInfo(
                    "For 100PZ package on F28003x, only one of the pins can be used and setup for this channel.",
                    inst, "asysCMPHPMXSELValue");
                allPinsMustBeConfigured = false;
            }

            //
            // Check for Pin Usage in analog
            //
            if (Common.isContextCPU1()) {
                if (Common.peripheralCount("ANALOG") > 0)
                {

                    var configurationStatus = [];
                    var finalFail = true;

                    for (var apinfo of tempPinInfoH){
                        var pinSelected = apinfo.PinDesignSignalName;

                        configurationStatus.push(
                            {
                                fail: (!selectedInterfaces.includes(pinSelected) && allInterfaces.includes(pinSelected)),
                                pinSelected: pinSelected
                            }
                        )
                    }
                    for (var cstat of configurationStatus){finalFail &= cstat.fail}


                    if (allPinsMustBeConfigured)
                    {
                        for (var cstat of configurationStatus)
                        {
                            if (cstat.fail)
                            {
                                validation.logError(
                                    "The pin " + cstat.pinSelected + " is not selected in the ANALOG PinMux module." +
                                    " Add this pin to the 'Pins Used' or change the 'Use Case'",
                                    inst, "asysCMPHPMXSELValue");
                            }
                        }
                    }
                    else
                    {
                        if (finalFail)
                        {
                            validation.logError(
                                "At least one of the following ANALOG PinMux pins must be selected.",
                                inst,"asysCMPHPMXSELValue");

                            for (var cstat of configurationStatus)
                            {
                                if (cstat.fail)
                                {
                                    validation.logError(
                                        "The pin " + cstat.pinSelected + " is not selected in the ANALOG PinMux module." +
                                        " Add this pin to the 'Pins Used' or change the 'Use Case'",
                                        inst, "asysCMPHPMXSELValue");
                                }
                            }
                        }
                    }
                }
            }
        }

        if((inst.highCompNegative != "CMPSS_INSRC_DAC") && (inst.asysCMPHNMXSELPinInfo == Pinmux.NO_DEVICE_PIN_FOUND))
        {
            validation.logError(
                "Signal not available for this device, select a valid signal!",
                inst, "asysCMPHNMXSELValue");
        }
        else
        {
            var tempPinNameN = ComparatorInputs.CMPSS_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPHNMXSELValue].displayName
            var tempPinNameNH = ComparatorInputs.CMPSS_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPHNMXSELValue].displayName
            var tempPinInfoNH = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinNameN.split("/")[0]))

            var allPinsMustBeConfigured = true;

            if ((inst.highCompNegative != "CMPSS_INSRC_DAC") && (tempPinNameN == "B5" || tempPinNameN == "B11") && Common.getDevicePart() == "F28003x_100PZ")
            {
                validation.logInfo(
                    "For 100PZ package on F28003x, only one of the pins can be used and setup for this channel.",
                    inst, "asysCMPHNMXSELValue");
                allPinsMustBeConfigured = false;
            }

            //
            // Check for Pin Usage in analog
            //
            if(inst.highCompNegative != "CMPSS_INSRC_DAC")
            {
                if (Common.isContextCPU1()) {
                    if (Common.peripheralCount("ANALOG") > 0)
                    {
        
                        var configurationStatus = [];
                        var finalFail = true;
        
                        for (var apinfo of tempPinInfoNH){
                            var pinSelected = apinfo.PinDesignSignalName;
        
                            configurationStatus.push(
                                {
                                    fail: (!selectedInterfaces.includes(pinSelected) && allInterfaces.includes(pinSelected)),
                                    pinSelected: pinSelected
                                }
                            )
                        }
                        for (var cstat of configurationStatus){finalFail &= cstat.fail}
        
                        if (allPinsMustBeConfigured)
                        {
                            for (var cstat of configurationStatus)
                            {
                                if (cstat.fail)
                                {
                                    validation.logError(
                                        "The pin " + cstat.pinSelected + " is not selected in the ANALOG PinMux module." +
                                        " Add this pin to the 'Pins Used' or change the 'Use Case'",
                                        inst, "asysCMPHNMXSELValue");
                                }
                            }
                        }
                        else
                        {
                            if (finalFail)
                            {
                                validation.logError(
                                    "At least one of the following ANALOG PinMux pins must be selected.",
                                    inst,"asysCMPHNMXSELValue");
        
                                for (var cstat of configurationStatus)
                                {
                                    if (cstat.fail)
                                    {
                                        validation.logError(
                                            "The pin " + cstat.pinSelected + " is not selected in the ANALOG PinMux module." +
                                            " Add this pin to the 'Pins Used' or change the 'Use Case'",
                                            inst, "asysCMPHNMXSELValue");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        if (inst.asysCMPLPMXSELPinInfo == Pinmux.NO_DEVICE_PIN_FOUND)
        {
            if((["F28P65x"].includes(Common.getDeviceName())))
            {
                if(ComparatorInputs.CMPSS_comparatorLowPositiveInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPLPMXSELValue])
                {
                    var tempPinNameLowPos = ComparatorInputs.CMPSS_comparatorLowPositiveInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPLPMXSELValue].displayName
                    if(tempPinNameLowPos.includes("VREF"))
                    {
                        //Do nothing, this is a valid connection for F28P65x
                    }
                }
                else
                {
                    validation.logError(
                        "Signal not available for this device, select a valid signal!",
                        inst, "asysCMPLPMXSELValue");
                }
            }
            else
            {
                validation.logError(
                    "Signal not available for this device, select a valid signal!",
                    inst, "asysCMPLPMXSELValue");
            }
        }
        else
        {
            var tempPinName = ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPLPMXSELValue].displayName
            var tempPinNameL = ComparatorInputs.CMPSS_comparatorInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPLPMXSELValue].displayName
            var tempPinInfoL = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))

            var allPinsMustBeConfigured = true;

            if ((tempPinName == "B5" || tempPinName == "B11") && Common.getDevicePart() == "F28003x_100PZ")
            {
                validation.logInfo(
                    "For 100PZ package on F28003x, only one of the pins can be used and setup for this channel.",
                    inst, "asysCMPLPMXSELValue");
                allPinsMustBeConfigured = false;
            }

            //
            // Check for Pin Usage in analog
            //
            if (Common.isContextCPU1()) {
                if (Common.peripheralCount("ANALOG") > 0)
                {

                    var configurationStatus = [];
                    var finalFail = true;

                    for (var apinfo of tempPinInfoL){
                        var pinSelected = apinfo.PinDesignSignalName;

                        configurationStatus.push(
                            {
                                fail: (!selectedInterfaces.includes(pinSelected) && allInterfaces.includes(pinSelected)),
                                pinSelected: pinSelected
                            }
                        )
                    }
                    for (var cstat of configurationStatus){finalFail &= cstat.fail}


                    if (allPinsMustBeConfigured)
                    {
                        for (var cstat of configurationStatus)
                        {
                            if (cstat.fail)
                            {
                                validation.logError(
                                    "The pin " + cstat.pinSelected + " is not selected in the ANALOG PinMux module." +
                                    " Add this pin to the 'Pins Used' or change the 'Use Case'",
                                    inst, "asysCMPLPMXSELValue");
                            }
                        }
                    }
                    else
                    {
                        if (finalFail)
                        {
                            validation.logError(
                                "At least one of the following ANALOG PinMux pins must be selected.",
                                inst,"asysCMPLPMXSELValue");

                            for (var cstat of configurationStatus)
                            {
                                if (cstat.fail)
                                {
                                    validation.logError(
                                        "The pin " + cstat.pinSelected + " is not selected in the ANALOG PinMux module." +
                                        " Add this pin to the 'Pins Used' or change the 'Use Case'",
                                        inst, "asysCMPLPMXSELValue");
                                }
                            }
                        }
                    }
                }
            }
        }

        if((inst.lowCompNegative != "CMPSS_INSRC_DAC") && (inst.asysCMPLNMXSELPinInfo == Pinmux.NO_DEVICE_PIN_FOUND))
        {
            validation.logError(
                "Signal not available for this device, select a valid signal!",
                inst, "asysCMPLNMXSELValue");
        }
        else
        {
            var tempPinNameN = ComparatorInputs.CMPSS_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPLNMXSELValue].displayName
            var tempPinNameLN = ComparatorInputs.CMPSS_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssBase][inst.asysCMPLNMXSELValue].displayName
            var tempPinInfoLN = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinNameN.split("/")[0]))

            var allPinsMustBeConfigured = true;

            if ((inst.lowCompNegative != "CMPSS_INSRC_DAC") && (tempPinNameN == "B5" || tempPinNameN == "B11") && Common.getDevicePart() == "F28003x_100PZ")
            {
                validation.logInfo(
                    "For 100PZ package on F28003x, only one of the pins can be used and setup for this channel.",
                    inst, "asysCMPLNMXSELValue");
                allPinsMustBeConfigured = false;
            }

            //
            // Check for Pin Usage in analog
            //
            if(inst.lowCompNegative != "CMPSS_INSRC_DAC")
            {
                if (Common.isContextCPU1()) {
                    if (Common.peripheralCount("ANALOG") > 0)
                    {
        
                        var configurationStatus = [];
                        var finalFail = true;
        
                        for (var apinfo of tempPinInfoLN){
                            var pinSelected = apinfo.PinDesignSignalName;
        
                            configurationStatus.push(
                                {
                                    fail: (!selectedInterfaces.includes(pinSelected) && allInterfaces.includes(pinSelected)),
                                    pinSelected: pinSelected
                                }
                            )
                        }
                        for (var cstat of configurationStatus){finalFail &= cstat.fail}
        
        
                        if (allPinsMustBeConfigured)
                        {
                            for (var cstat of configurationStatus)
                            {
                                if (cstat.fail)
                                {
                                    validation.logError(
                                        "The pin " + cstat.pinSelected + " is not selected in the ANALOG PinMux module." +
                                        " Add this pin to the 'Pins Used' or change the 'Use Case'",
                                        inst, "asysCMPLNMXSELValue");
                                }
                            }
                        }
                        else
                        {
                            if (finalFail)
                            {
                                validation.logError(
                                    "At least one of the following ANALOG PinMux pins must be selected.",
                                    inst,"asysCMPLNMXSELValue");
        
                                for (var cstat of configurationStatus)
                                {
                                    if (cstat.fail)
                                    {
                                        validation.logError(
                                            "The pin " + cstat.pinSelected + " is not selected in the ANALOG PinMux module." +
                                            " Add this pin to the 'Pins Used' or change the 'Use Case'",
                                            inst, "asysCMPLNMXSELValue");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //Add validation for DE support with ePWM
}

/*
 *  ======== filterHardware ========
 *  Control RX, TX Pin usage by the user specified dataDirection.
 *
 *  param component - hardware object describing signals and
 *                     resources they're attached to
 *
 *  returns Boolean indicating whether or not to allow the component to
 *           be assigned to an instance's $hardware config
 */
function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["CMPSS"]));
}


var sharedModuleInstances = undefined;
if (Common.isContextCPU1()) {
    if (Common.peripheralCount("ANALOG") > 0) {
        sharedModuleInstances = function () {
                return (
                    [
                        {
                            name: "analog",
                            displayName: "Analog PinMux",
                            moduleName: "/driverlib/analog.js"
                        },
                    ]
                );
            }
    }
}


var cmpssModule = {
    peripheralName      : "CMPSS",
    displayName         : "CMPSS",
    maxInstances        : deviceNumberOfInstances,
    defaultInstanceName : "myCMPSS",
    description         : "Comparator Subsystem",
    longDescription: (Common.getCollateralFindabilityList("CMPSS")),
    filterHardware      : filterHardware,
    config              : config,
    sharedModuleInstances : sharedModuleInstances,
    templates: {
        boardc : "/driverlib/cmpss/cmpss.board.c.xdt",
        boardh : "/driverlib/cmpss/cmpss.board.h.xdt"
    },
    validate            : onValidate,
};

exports = cmpssModule;
