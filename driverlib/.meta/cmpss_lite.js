let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let ComparatorInputs = system.getScript("/driverlib/cmpss_lite/cmpss_lite_inputSignals.js")

let device_driverlib_peripheral =
    system.getScript("/driverlib/cmpss_lite/" +
        Common.getDeviceName().toLowerCase() + "_cmpss_lite.js");

let device_driverlib_memmap =
system.getScript("/driverlib/device_driverlib_peripherals/" +
    Common.getDeviceName().toLowerCase() + "_memmap.js");

if(["F280013x", "F280015x"].includes(Common.getDeviceName())){
    var deviceNumberOfInstances = device_driverlib_memmap.CMPSSMemoryMap.length
    var CMPSSLITE_INSTANCE = device_driverlib_memmap.CMPSSMemoryMap;
    CMPSSLITE_INSTANCE = CMPSSLITE_INSTANCE.filter(module => module.name != "CMPSS1_BASE");
    CMPSSLITE_INSTANCE = CMPSSLITE_INSTANCE.map(({baseAddress, ...rest}) => {
    return rest;
    });
}
else {
    var deviceNumberOfInstances = device_driverlib_memmap.CMPSSLITEMemoryMap.length
    var CMPSSLITE_INSTANCE = device_driverlib_memmap.CMPSSLITEMemoryMap;

}
CMPSSLITE_INSTANCE = CMPSSLITE_INSTANCE.map(({baseAddress, ...rest}) => {
    return rest;
});

var CMPSS_TRIPOUT = [
    {name: "CMPSS_TRIPOUT_ASYNC_COMP",  displayName: "Asynchronous comparator output drives CTRIPOUT"},
    {name: "CMPSS_TRIPOUT_SYNC_COMP",   displayName: "Synchronous comparator output drives CTRIPOUT"},
    {name: "CMPSS_TRIPOUT_FILTER",      displayName: "Filter output drives CTRIPOUT"},
    {name: "CMPSS_TRIPOUT_LATCH",       displayName: "Latched filter output drives CTRIPOUT"},
];

var CMPSS_TRIP = [
    {name: "CMPSS_TRIP_ASYNC_COMP",     displayName: "Asynchronous comparator output drives CTRIP"},
    {name: "CMPSS_TRIP_SYNC_COMP",      displayName: "Synchronous comparator output drives CTRIP"},
    {name: "CMPSS_TRIP_FILTER",         displayName: "Filter output drives CTRIP"},
    {name: "CMPSS_TRIP_LATCH",          displayName: "Latched filter output drives CTRIP"},
];

if (["F280013x", "F280015x"].includes(Common.getDeviceName())){
    var defaultCMPSSLITEPinInfos = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(ComparatorInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()]["CMPSSLITE2_BASE"][0].displayName.split("/")[0]));
    var defaultCMPSSLITENegPinInfos = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(ComparatorInputs.CMPSSLITE_comparatorNegInputSignals[Common.getDeviceName()]["CMPSSLITE2_BASE"][1].displayName.split("/")[0]));
}
if (["F28E12x"].includes(Common.getDeviceName())){
    var defaultCMPSSLITEPinInfos = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(ComparatorInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()]["CMPSSLITE1_BASE"][0].displayName.split("/")[0]));
    var defaultCMPSSLITENegPinInfos = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(ComparatorInputs.CMPSSLITE_comparatorNegInputSignals[Common.getDeviceName()]["CMPSSLITE1_BASE"][1].displayName.split("/")[0]));
}

function calculateDevicePinNameHigh(inst,ui){
    var tempPinName = ComparatorInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPHPMXSELValue].displayName
    var tempPinInfo = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))
    var tempPinInfoDesc = Pinmux.getDevicePinInfoDescription(tempPinInfo)
    if(["F28E12x"].includes(Common.getDeviceName()) && (inst.asysCMPHPMXSELValue == 6) && (inst.cmpssLiteBase == "CMPSSLITE2_BASE") && (tempPinInfoDesc == Pinmux.NO_DEVICE_PIN_FOUND)){
            return ComparatorInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPHPMXSELValue].displayName
        }
    else{
        return tempPinInfoDesc
    }
}

function calculateDevicePinNameHighNeg(inst,ui){
    var tempPinName = ComparatorInputs.CMPSSLITE_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPHNMXSELValue].displayName
    var tempPinInfo = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))
    var tempPinInfoDesc = Pinmux.getDevicePinInfoDescription(tempPinInfo)
    return tempPinInfoDesc
}

function calculateDevicePinNameLow(inst,ui){
    var tempPinName = ComparatorInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPLPMXSELValue].displayName
    var tempPinInfo = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))
    var tempPinInfoDesc = Pinmux.getDevicePinInfoDescription(tempPinInfo)
    if(["F28E12x"].includes(Common.getDeviceName()) && (inst.asysCMPHPMXSELValue == 6) && (inst.cmpssLiteBase == "CMPSSLITE2_BASE") && (tempPinInfoDesc == Pinmux.NO_DEVICE_PIN_FOUND)){
        return ComparatorInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPLPMXSELValue].displayName
    }
    else{
        return tempPinInfoDesc
    }
}

function calculateDevicePinNameLowNeg(inst,ui){
    var tempPinName = ComparatorInputs.CMPSSLITE_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPLNMXSELValue].displayName
    var tempPinInfo = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinName.split("/")[0]))
    var tempPinInfoDesc = Pinmux.getDevicePinInfoDescription(tempPinInfo)
    return tempPinInfoDesc
}

/* Array of possible ePWM sync signals */
if (["F280013x", "F280015x"].includes(Common.getDeviceName())){
var ePWMInstances = Common.peripheralCount("EPWM")
var ePWMArraySync = [];
var ePWMArrayBlank = [];
for(var i = 0; i < ePWMInstances; i++) {
    ePWMArraySync.push()
    ePWMArraySync.push({ name: ""+(i+1), displayName: "EPWM"+(i+1)+"SYNCPER" })
    ePWMArrayBlank.push()
    ePWMArrayBlank.push({ name: ""+(i+1), displayName: "EPWM"+(i+1)+"BLANK" })
}
}
if (["F28E12x"].includes(Common.getDeviceName())){
    var ePWMInstances = Common.peripheralCount("MCPWM")
    var ePWMArraySync = [];
    for(var i = 0; i < ePWMInstances; i++) {
        ePWMArraySync.push()
        ePWMArraySync.push({ name: ""+(i+1), displayName: "MCPWM"+(i+1)+"SYNCPER" })
    }
}
/*Generate array for input signals*/
var numberOfPosInputSignals = 0
var numberOfNegInputSignals = 0
var asysLitePosSignalOptions = []
var asysLiteNegSignalOptions = []
if (["F280013x", "F280015x"].includes(Common.getDeviceName())){
    numberOfPosInputSignals = 5
    numberOfNegInputSignals = 2
}
if (["F28E12x"].includes(Common.getDeviceName())){
    numberOfPosInputSignals = 7
    numberOfNegInputSignals = 2
}

for(var i=0;i<numberOfPosInputSignals;i++){
    asysLitePosSignalOptions.push(
        {name:""+i,displayName:"Input Signal "+i},
    )
}

for(var i=0;i<numberOfNegInputSignals;i++){
    asysLiteNegSignalOptions.push(
        {name:""+i,displayName:"Input Signal "+i},
    )
}

var highConfig =[
    // configHighComparator: Sets the configuration for the high comparator.
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
        default     : CMPSS_TRIPOUT[0].name,
        options     : CMPSS_TRIPOUT,
    },
    {
        name        : "highCTRIP",
        displayName : "Signal driving CTRIPH",
        description : 'Specify which signal drives CTRIPH',
        hidden      : false,
        default     : CMPSS_TRIP[0].name,
        options     : CMPSS_TRIP,
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
    {
        name: "GROUP_SYNC_SOURCE", // old Ramp gen config
        displayName: "Select Sync Source",
        description: "",
        longDescription: "",
        collapsed: false,
        config: [
            {
                name        : "pwmSyncSrc",
                displayName : "EPWMSYNCPER source number",
                description : 'Specify the number of the EPWMSYNCPER source',
                hidden      : false,
                default     : ePWMArraySync[0].name,
                options     : ePWMArraySync
            },
        ]
    },
]

if (["F280013x","F280015x","F28E12x"].includes(Common.getDeviceName())){
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
                    default     : asysLitePosSignalOptions[0].name,
                    options     : asysLitePosSignalOptions
                },
                {
                    name        : "asysCMPHPMXSELPinInfo",
                    displayName : "Selected MUX Signal for HP input",
                    description : 'Pin Number and Name for selected HP signal.',
                    hidden      : false,
                    default     : Pinmux.getDevicePinInfoDescription(defaultCMPSSLITEPinInfos),
                    getValue    : calculateDevicePinNameHigh
                },

                // ASysCtl_selectCMPHNMux : options vary per device
                {
                    name        : "asysCMPHNMXSELValue",
                    displayName : "CMPHNMXSEL",
                    description : 'Select the value for CMPHNMXSEL.',
                    hidden      : true,
                    default     : asysLiteNegSignalOptions[1].name,
                    options     : asysLiteNegSignalOptions
                },
                {
                    name        : "asysCMPHNMXSELPinInfo",
                    displayName : "Selected MUX Signal for HN input",
                    description : 'Pin Number and Name for selected HN signal.',
                    hidden      : true,
                    default     : Pinmux.getDevicePinInfoDescription(defaultCMPSSLITENegPinInfos),
                    getValue    : calculateDevicePinNameHighNeg
                },
            ]
        },
    ])
}
var lowConfig =[
    // configLowComparator: Sets the configuration for the low comparator.
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
        default     : CMPSS_TRIPOUT[0].name,
        options     : CMPSS_TRIPOUT,
    },
    {
        name        : "lowCTRIP",
        displayName : "Signal driving CTRIPL",
        description : 'Specify which signal drives CTRIPL',
        hidden      : false,
        default     : CMPSS_TRIP[0].name,
        options     : CMPSS_TRIP,
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
if (["F280013x", "F280015x","F28E12x"].includes(Common.getDeviceName())){
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
                    default     : asysLitePosSignalOptions[0].name,
                    options     : asysLitePosSignalOptions
                },
                {
                    name        : "asysCMPLPMXSELPinInfo",
                    displayName : "Selected MUX Signal for LP input",
                    description : 'Pin Number and Name for selected LP signal.',
                    hidden      : false,
                    default     : Pinmux.getDevicePinInfoDescription(defaultCMPSSLITEPinInfos),
                    getValue    : calculateDevicePinNameLow
                },

                // ASysCtl_selectCMPLNMux  : options vary per device
                {
                    name        : "asysCMPLNMXSELValue",
                    displayName : "CMPLNMXSEL",
                    description : 'Select the value for CMPLNMXSEL.',
                    hidden      : true,
                    default     : asysLiteNegSignalOptions[1].name,
                    options     : asysLiteNegSignalOptions
                },
                {
                    name        : "asysCMPLNMXSELPinInfo",
                    displayName : "Selected MUX Signal for LN input",
                    description : 'Pin Number and Name for selected LN signal.',
                    hidden      : true,
                    default     : Pinmux.getDevicePinInfoDescription(defaultCMPSSLITENegPinInfos),
                    getValue    : calculateDevicePinNameLowNeg
                },
            ]
        },
    ])
}
/* Array of CAN configurables that are common across device families */
let config = [
    {
        name        : "cmpssLiteBase",
        displayName : "CMPSSLITE Instance",
        description : 'Instance of the CMPSSLITE used.',
        hidden      : false,
        default     : CMPSSLITE_INSTANCE[0].name,
        options     : CMPSSLITE_INSTANCE,
    },
    // enableModule / disableModule
    {
        name        : "enableModule",
        displayName : "Enable module",
        description : 'Enables the CMPSSLITE module.',
        hidden      : false,
        default     : false
    },
];
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
if (["F280013x","F280015x"].includes(Common.getDeviceName())){
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

config = config.concat([
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
]);

// configDAC
var cmpss_dac_config = [
    {
        name        : "dacValLoad",
        displayName : "DAC value load",
        description : 'When is DAC value loaded from shadow register',
        hidden      : false,
        default     : "CMPSS_DACVAL_SYSCLK",
        options     : [
            {name: "CMPSS_DACVAL_SYSCLK", displayName: "DAC value updated from SYSCLK"},
            {name: "CMPSS_DACVAL_PWMSYNC", displayName: "DAC value updated from EPWMSYNCPER"},
        ],
    },
]
if (!["F280013x", "F280015x", "F28E12x"].includes(Common.getDeviceName())){
    cmpss_dac_config.push(
        {
            name        : "dacRefVoltage",
            displayName : "DAC reference voltage",
            description : 'Specify DAC reference voltage',
            hidden      : false,
            default     : "CMPSS_DACREF_VDDA",
            options     : [
                {name: "CMPSS_DACREF_VDDA", displayName: "VDDA is the voltage reference"},
                {name: "CMPSS_DACREF_VDAC", displayName: "VDAC is the voltage reference"},
            ],
        },
    );

    cmpss_dac_config.push(
        {
            name        : "dacValSource",
            displayName : "DAC value source",
            description : 'Specify DAC value source',
            hidden      : false,
            default     : "CMPSS_DACSRC_SHDW",
            options     : [
                {name: "CMPSS_DACSRC_SHDW", displayName: "DAC value updated from shadow register"},
                {name: "CMPSS_DACSRC_RAMP", displayName: "DAC value is updated from the ramp register"},
            ],
        },
    );
}

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

    var usedCMPSSInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedCMPSSInsts.push(instance_obj.cmpssLiteBase);
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
            inst, "cmpssLiteBase");
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

    if (["F280013x","F280015x"].includes(Common.getDeviceName())){
        if (inst.configBlanking < 1 || inst.configBlanking > 16)
        {
            validation.logError(
                "Enter an integer for VALUE_NAME between 1 and 16!",
                inst, "configBlanking");
        }
    }

    if (["F280013x","F280015x"].includes(Common.getDeviceName()))
    {
        if (inst.samplePrescaleHigh < 0 || inst.samplePrescaleHigh > 65535)
        {
            validation.logError(
                "Enter an integer for Digital Filter Sample Prescale between 0 and 65,535!",
                inst, "samplePrescaleHigh");
        }
    }
    else if (["F28E12x"].includes(Common.getDeviceName()))
    {
        if (inst.samplePrescaleHigh < 0 || inst.samplePrescaleHigh > 16777215)
        {
            validation.logError(
                "Enter an integer for Digital Filter Sample Prescale between 0 and 16,777,215!",
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

    if (inst.samplePrescaleLow < 0 || inst.samplePrescaleLow > 1023)
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

    if (inst.pwmSyncSrc < 0 || inst.pwmSyncSrc > 16)
    {
        validation.logError(
            "Enter an integer for Ramp EPWMSYNCPER source number between 1 and 16!",
            inst, "pwmSyncSrc");
    }


    var selectedInterfaces = null;
    var allInterfaces = null;
    if (Common.peripheralCount("ANALOG") > 0)
    {
        selectedInterfaces = Pinmux.getPeripheralUseCaseInterfaces(inst.analog, "ANALOG", inst.analog.useCase);
        allInterfaces = Pinmux.getPeripheralUseCaseInterfaces(inst.analog, "ANALOG", "ALL");
    }

    if (["F280013x","F280015x", "F28E12x"].includes(Common.getDeviceName())){
        if (inst.asysCMPHPMXSELPinInfo == Pinmux.NO_DEVICE_PIN_FOUND)
        {
            validation.logError(
                "Signal not available for this device, select a valid signal!",
                inst, "asysCMPHPMXSELValue");
        }
        else
        {
            var tempPinName = ComparatorInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPHPMXSELValue].displayName
            var tempPinNameH = ComparatorInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPHPMXSELValue].displayName
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

        if (inst.asysCMPHNMXSELPinInfo == Pinmux.NO_DEVICE_PIN_FOUND)
        {
            validation.logError(
                "Signal not available for this device, select a valid signal!",
                inst, "asysCMPHNMXSELValue");
        }
        else
        {
            var tempPinNameN = ComparatorInputs.CMPSSLITE_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPHNMXSELValue].displayName
            var tempPinNameNH = ComparatorInputs.CMPSSLITE_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPHNMXSELValue].displayName
            var tempPinInfoNH = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinNameN.split("/")[0]))

            var allPinsMustBeConfigured = true;

            if ((tempPinNameN == "B5" || tempPinNameN == "B11") && Common.getDevicePart() == "F28003x_100PZ")
            {
                validation.logInfo(
                    "For 100PZ package on F28003x, only one of the pins can be used and setup for this channel.",
                    inst, "asysCMPHNMXSELValue");
                allPinsMustBeConfigured = false;
            }

            //
            // Check for Pin Usage in analog
            //
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

        if (inst.asysCMPLPMXSELPinInfo == Pinmux.NO_DEVICE_PIN_FOUND)
        {
            validation.logError(
                "Signal not available for this device, select a valid signal!",
                inst, "asysCMPLPMXSELValue");
        }
        else
        {
            var tempPinName = ComparatorInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPLPMXSELValue].displayName
            var tempPinNameL = ComparatorInputs.CMPSSLITE_comparatorInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPLPMXSELValue].displayName
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

        if (inst.asysCMPLNMXSELPinInfo == Pinmux.NO_DEVICE_PIN_FOUND)
        {
            validation.logError(
                "Signal not available for this device, select a valid signal!",
                inst, "asysCMPLNMXSELValue");
        }
        else
        {
            var tempPinNameN = ComparatorInputs.CMPSSLITE_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPLNMXSELValue].displayName
            var tempPinNameLN = ComparatorInputs.CMPSSLITE_comparatorNegInputSignals[Common.getDeviceName()][inst.cmpssLiteBase][inst.asysCMPLNMXSELValue].displayName
            var tempPinInfoLN = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(tempPinNameN.split("/")[0]))

            var allPinsMustBeConfigured = true;

            if ((tempPinNameN == "B5" || tempPinNameN == "B11") && Common.getDevicePart() == "F28003x_100PZ")
            {
                validation.logInfo(
                    "For 100PZ package on F28003x, only one of the pins can be used and setup for this channel.",
                    inst, "asysCMPLNMXSELValue");
                allPinsMustBeConfigured = false;
            }

            //
            // Check for Pin Usage in analog
            //
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
    return (Common.typeMatches(component.type, ["CMPSSLITE"]));
}


var sharedModuleInstances = undefined;
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


var cmpssliteModule = {
    peripheralName      : "CMPSSLITE",
    displayName         : "CMPSSLITE",
    maxInstances        : deviceNumberOfInstances,
    defaultInstanceName : "myCMPSSLite",
    description         : "Comparator Subsystem Lite",
    filterHardware      : filterHardware,
    config              : config,
    sharedModuleInstances : sharedModuleInstances,
    templates: {
        boardc : "/driverlib/cmpss_lite/cmpss_lite.board.c.xdt",
        boardh : "/driverlib/cmpss_lite/cmpss_lite.board.h.xdt"
    },
    validate            : onValidate,
};
exports = cmpssliteModule;