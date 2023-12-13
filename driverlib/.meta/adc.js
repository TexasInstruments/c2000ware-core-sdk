let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let InternalConnections = system.getScript("/driverlib/adc/adc_internalConnections.js")

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_adc.js");
let device_adc_char =
    system.getScript("/driverlib/adc/adc_char.js");

var device_adc_Ron = device_adc_char.Ron[Common.getDeviceName()]
var device_adc_Cp = device_adc_char.Cp[Common.getDeviceName()]
var device_adc_Ch = device_adc_char.Ch[Common.getDeviceName()]	

var ESTIMATED_CP = 10.00001;
var ADC_SysClk_MHz = Common.SYSCLK_getMaxMHz();
var ADC_SampleTime_SysClk_ns = 1000/ADC_SysClk_MHz;

var longDescriptionSocTriggers = `
![an offline image](../../driverlib/.meta/adc/docs/adcSocTrigger.png "SOC Triggers")
`

var longDescriptionSocSamplingTimeCalculator = `
An approximation of the required settling time can be determined using an RC settling model. The time constant
for the model is given by the equation:

![an offline image](../../driverlib/.meta/adc/docs/sampleTimeEq1.jpg "SOC Triggers")

And the number of time constants needed is given by the equation:

![an offline image](../../driverlib/.meta/adc/docs/sampleTimeEq2.jpg "SOC Triggers")

So the total S+H time should be set to at least:

![an offline image](../../driverlib/.meta/adc/docs/sampleTimeEq3.jpg "SOC Triggers")

Where the following parameters are provided by the ADC input model in the device data manual:
*	n = ADC resolution (in bits)
*	Ron = ADC sampling switch resistance (in Ohms)
*	Ch = ADC sampling capacitor (in pF)
*	Cp = ADC channel parasitic input capacitance (in pF)

And the following parameters are dependent on the application design:
*	Settling error = tolerable settling error (in LSBs)
*	Rs = ADC driving circuit source impedance (in Ohms)
*	Cs = capacitance on ADC input pin (in pF)
`

var DO_NOT_COPY_configNames = [
    "adcBase",
    "copyUse",
    "copyFrom",
    "copyPerform",
    "recalculateSampleTimes"
];

function extChanOnChange (inst, ui){
    if (ui){
        if (inst.enableEXTMUX){
                ui["extTiming"].hidden=false;
            }
            else {
                ui["extTiming"].hidden=true;
            }
            if (inst.enableEXTMUX){
                ui["adcNumExtPins"].hidden=false;
            }
            else{
                ui["adcNumExtPins"].hidden=true;
            }
        for (var xbari=0; xbari< 4; xbari++)
        {
            // ui["extchannel"+ xbari+" pin"].hidden=true;
            if (inst.enableEXTMUX && xbari<inst["adcNumExtPins"]){
                ui["extchannel"+ xbari+" pin"].hidden=false;
            }
            else{
                ui["extchannel"+ xbari+" pin"].hidden=true;
            }
        }
    }
}

function calculateModuleChannelName(inst,sociX){
    return Pinmux.calculateADCPinInfo(inst,sociX).adcInputs
}

function calculateDevicePinName(inst,sociX){
    var pinInfo = Pinmux.calculateADCPinInfo(inst,sociX)
    if(pinInfo.adcPinInfosDescriptions == Pinmux.NO_DEVICE_PIN_FOUND){
        var internalSignals = InternalConnections.ADC_internalSignals[Common.getDeviceName()][pinInfo.adcInputs]
        if(internalSignals){
            return internalSignals;
        }
        else{
            return pinInfo.adcPinInfosDescriptions;
        }
    }
    else{
        return pinInfo.adcPinInfosDescriptions;
    }
}

function calculateParasiticCapacitance(inst,sociX){
    var adcInput = Pinmux.calculateADCPinInfo(inst,sociX).adcInput
    var inputCp = device_adc_Cp["ADCIN" + adcInput];
    if (!inputCp)
    {
        inputCp = { CMP_DIS: ESTIMATED_CP, CMP_EN: ESTIMATED_CP }
    }
    return inputCp.CMP_EN;
}

function calculateSampleTime(inst,sociX){
    var n = 12;
    if (["F2837xD", "F2837xS" ,"F2838x","F28P65x"].includes(Common.getDeviceName()))
    {
        if (inst["adcResolutionMode"] == "ADC_RESOLUTION_16BIT")
        {
            n = 16
        }
    }
    if (inst["soc" + sociX.toString() + "UseSampleTimeCalculator"])
    {
        var Rs = inst["soc" + sociX.toString() + "InputResistance"];
        var Ron = inst["soc" + sociX.toString() + "ADCSwitchResistance"];
        var Ch = inst["soc" + sociX.toString() + "ADCSampleCapacitance"];
        var Cp = inst["soc" + sociX.toString() + "ADCParasiticCapacitance"];
        var settling_error = inst["soc" + sociX.toString() + "SettlingError"];
        var Cs = inst["soc" + sociX.toString() + "InputCapacitance"];
        var k = Math.log(Math.pow(2, n)/settling_error) -
                Math.log((Cs + Cp)/Ch)
        var tau = (Rs + Ron)*Ch + Rs*(Cs + Cp);
        var t = k*tau / 1000;

       return Math.round(t * 100) / 100;
    }

    //
    // Must return something... cannot be undefined
    //
    return 0;
}

function calculateChosenSampleTime(inst,sociX){
    var sysclk_for_this_core = Common.getSYSCLK()
    var sysclk_ns = 1000/sysclk_for_this_core;
    if (inst["soc" + sociX.toString() + "UseCalculatedSampleTime"] &&
        inst["soc" + sociX.toString() + "UseSampleTimeCalculator"])
        {
            return inst["soc" + sociX.toString() + "CalculatedSampleTime"];
        }
        else
        {
            return sysclk_ns * inst["soc" + sociX.toString() + "SampleWindow"]
        }
}

// function performCopy(inst, ui)
// {
//     for (var instance_index in inst.$module.$instances)
//     {
//         var instance_obj = inst.$module.$instances[instance_index];
//         if (instance_obj != inst) {
//             //console.log(instance_obj)
//             if (instance_obj.$name == inst.copyFrom)
//             {
//                 copyAllSettings(inst, instance_obj);
//                 onChangeADC(inst, ui)
//             }
//         }
//     }
// }

// function copyAllSettings(inst_copy_to, inst_copy_from)
// {
//     var configNames = Common.getConfigNameRecursive(inst_copy_from.$module.config);
//     for (var configOptionIndex = 0; configOptionIndex<configNames.length; configOptionIndex++)
//     {
//         var configName = configNames[configOptionIndex];
//         if (DO_NOT_COPY_configNames.includes(configName))
//         {
//             continue;
//         }
//         //console.log(configName)
//         inst_copy_to[configName] = inst_copy_from[configName];
//     }
// }

function onChangeEnabledSOCs(inst, ui){
    for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
        var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
        var soci = (currentSOC).replace(/[^0-9]/g,'')
        var socConfigs = [
            "soc" + soci.toString() + "Name",
            "soc" + soci.toString() + "IndependentNameMode", 
            "soc" + soci.toString() + "Channel",
            "soc" + soci.toString() + "ModuleChannelName",
            "soc" + soci.toString() + "DevicePinName",
            "soc" + soci.toString() + "Trigger",
            "soc" + soci.toString() + "InterruptTrigger",
            "soc" + soci.toString() + "UseSampleTimeCalculator",
            "soc" + soci.toString() + "SampleTime",
        ]
        if ([ "F28P65x", "F28P55x"].includes(Common.getDeviceName())){
            socConfigs.push(   
                "soc" + soci.toString() + "Triggermode",
                "soc" + soci.toString() + "ExtChannel",
            )
        }

       
        var sampleCalculatorConfigs = [
            "soc" + soci.toString() + "InputCapacitance",
            "soc" + soci.toString() + "InputResistance",
            "soc" + soci.toString() + "CalculatedSampleTime",
            "soc" + soci.toString() + "UseCalculatedSampleTime",
            "soc" + soci.toString() + "ADCSwitchResistance",
            "soc" + soci.toString() + "ADCSampleCapacitance",
            "soc" + soci.toString() + "ADCParasiticCapacitance",
            "soc" + soci.toString() + "SettlingError"
        ];

        if (ui)
        {
            for (var socConfig of socConfigs)
            {
                if((inst.enabledSOCs).includes(currentSOC))
                {
                    ui[socConfig].hidden = false;
                }
                else
                {
                    ui[socConfig].hidden = true;
                }
            }

            // if(((inst.enabledSOCs).includes(currentSOC))&& (inst.enableEXTMUX))
            // {
            //     ui["soc" + soci.toString() + "ExtChannel"].hidden = false;
            // }
            // else
            // {
            //     ui["soc" + soci.toString() + "ExtChannel"].hidden = true;
            // }
           
            
            for (var sampCalcConfig of sampleCalculatorConfigs)
            {
                if (((inst.enabledSOCs).includes(currentSOC))&&(inst["soc" + soci.toString() + "UseSampleTimeCalculator"]))
                {
                    ui[sampCalcConfig].hidden = false;
                }
                else
                {
                    ui[sampCalcConfig].hidden = true;
                }
            }
            if (((inst.enabledSOCs).includes(currentSOC)))
            {
                if(inst["soc" + soci.toString() + "UseCalculatedSampleTime"] &&
                   inst["soc" + soci.toString() + "UseSampleTimeCalculator"]){
                    ui["soc" + soci.toString() + "SampleWindow"].hidden = true;
                    ui["soc" + soci.toString() + "SampleWindowCalculated"].hidden = false;
                }
                else{
                    ui["soc" + soci.toString() + "SampleWindow"].hidden = false;
                    ui["soc" + soci.toString() + "SampleWindowCalculated"].hidden = true;
                }
            }
            else
            {
                ui["soc" + soci.toString() + "SampleWindow"].hidden = true;
                ui["soc" + soci.toString() + "SampleWindowCalculated"].hidden = true;
            }
        }
    }
}

function onChangeEnabledInts(inst, ui){
    for(var intIndex in device_driverlib_peripheral.ADC_IntNumber){ 
        var currentINT = device_driverlib_peripheral.ADC_IntNumber[intIndex].name
        var inti = (currentINT).replace(/[^0-9]/g,'')
        var intConfigs = [
            "enableInterrupt" + inti.toString(),
            "interrupt" + inti.toString() + "SOCSource",
            "enableInterrupt" + inti.toString() + "ContinuousMode",
        ]

        if (ui)
        {
            for (var intConfig of intConfigs)
            {
                if((inst.enabledInts).includes(currentINT))
                {
                    ui[intConfig].hidden = false;
                }
                else
                {
                    ui[intConfig].hidden = true;
                }
            }
        }
    }
}

function onChangeEnabledPPBs(inst, ui){
    for(var ppbIndex in device_driverlib_peripheral.ADC_PPBNumber)
    {
        var currentPPB = device_driverlib_peripheral.ADC_PPBNumber[ppbIndex].name
        var ppbi = (currentPPB).replace(/[^0-9]/g,'')
        var ppbConfigs = [
            "ppb" + ppbi.toString() + "Name",
            "ppb" + ppbi.toString() + "IndependentNameMode",
            "ppb" + ppbi.toString() + "SOCNumber",
            "ppb" + ppbi.toString() + "EventEnable",
            "ppb" + ppbi.toString() + "EventInterruptEnable",
            "ppb" + ppbi.toString() + "CalibrationOffset",
            "ppb" + ppbi.toString() + "ReferenceOffset",
            "ppb" + ppbi.toString() + "EnableTwosComplement",
            "ppb" + ppbi.toString() + "HighTripLimit",
            "ppb" + ppbi.toString() + "LowTripLimit",
        ]

        if ([ "F28P65x", "F28P55x"].includes(Common.getDeviceName())){
            ppbConfigs.push(   
            "ppb" + ppbi.toString() + "CompSource", 
            "ppb" + ppbi.toString() + "SyncInput", 
            "ppb" + ppbi.toString() + "Rightshift", 
            "ppb" + ppbi.toString() + "AccumulationLimit",
            "ppb" + ppbi.toString() + "SelectOSINTSource",
            "ppb" + ppbi.toString() + "AbsValue",        
            )
        }
        if (!["F2807x", "F2837xS", "F2837xD"].includes(Common.getDeviceName())){
            ppbConfigs.push("ppb" + ppbi.toString() + "EnablePPBEventCBCClear",)
        }
        if (ui)
        {
            for (var ppbConfig of ppbConfigs)
            {
                if((inst.enabledPPBs).includes(currentPPB))
                {
                    ui[ppbConfig].hidden = false;
                }
                else
                {
                    ui[ppbConfig].hidden = true;
                }
            }
        }
    }
}

function onChangeSampleTimeCalculator(inst, ui){
    // TODO: will likely be removed, done by the getValue function for CalculatedSampleTime
    // var n = 12;
    // if (["F2837xD", "F2837xS" ,"F2838x"].includes(Common.getDeviceName()))
    // {
    //     if (inst["adcResolutionMode"] == "ADC_RESOLUTION_16BIT")
    //     {
    //         n = 16
    //     }
    // }
    for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
        var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
        var soci = (currentSOC).replace(/[^0-9]/g,'')
        var sampleCalculatorConfigs = [
            "soc" + soci.toString() + "InputCapacitance",
            "soc" + soci.toString() + "InputResistance",
            "soc" + soci.toString() + "CalculatedSampleTime",
            "soc" + soci.toString() + "UseCalculatedSampleTime",
            "soc" + soci.toString() + "ADCSwitchResistance",
            "soc" + soci.toString() + "ADCSampleCapacitance",
            "soc" + soci.toString() + "ADCParasiticCapacitance",
            "soc" + soci.toString() + "SettlingError"
        ];

        if (ui)
        {
            for (var sampCalcConfig of sampleCalculatorConfigs)
            {
                if (inst["soc" + soci.toString() + "UseSampleTimeCalculator"])
                {
                    ui[sampCalcConfig].hidden = false;
                }
                else
                {
                    ui[sampCalcConfig].hidden = true;
                }
            }
        }

// TODO: will likely be removed, done by the getValue function for CalculatedSampleTime
        
        // if (inst["soc" + soci.toString() + "UseSampleTimeCalculator"])
        // {
        //     var Rs = inst["soc" + soci.toString() + "InputResistance"];
        //     var Ron = inst["soc" + soci.toString() + "ADCSwitchResistance"];
        //     var Ch = inst["soc" + soci.toString() + "ADCSampleCapacitance"];
        //     var Cp = inst["soc" + soci.toString() + "ADCParasiticCapacitance"];
        //     var settling_error = inst["soc" + soci.toString() + "SettlingError"];
        //     var Cs = inst["soc" + soci.toString() + "InputCapacitance"];
        //     var k = Math.log(Math.pow(2, n)/settling_error) -
        //             Math.log((Cs + Cp)/Ch)
        //     var tau = (Rs + Ron)*Ch + Rs*(Cs + Cp);
        //     var t = k*tau / 1000;

        //     inst["soc" + soci.toString() + "CalculatedSampleTime"] = Math.round(t * 100) / 100;
        // }

        if (inst["soc" + soci.toString() + "UseCalculatedSampleTime"] &&
            inst["soc" + soci.toString() + "UseSampleTimeCalculator"])
        {
            if (ui)
            {
                if((inst.enabledSOCs).includes(currentSOC)){
                    ui["soc" + soci.toString() + "SampleWindow"].hidden = true;
                    ui["soc" + soci.toString() + "SampleWindowCalculated"].hidden = false;
                }
            }

            
        }
        else
        {
            if (ui)
            {
                if((inst.enabledSOCs).includes(currentSOC)){
                    ui["soc" + soci.toString() + "SampleWindow"].hidden = false;
                    ui["soc" + soci.toString() + "SampleWindowCalculated"].hidden = true;
                }
            }
           
        }

    }
}

function calculateSampleWindow(inst, sociX){
    var sysclk_for_this_core = Common.getSYSCLK()
    var sysclk_ns = 1000/sysclk_for_this_core;
    return Math.round(inst["soc" + sociX.toString() + "SampleTime"]/sysclk_ns);
}

function onChangeHighPriorityMode(inst, ui){

}

var DEVICES_ADC_INSTANCES = {
    F2807x : [
        { name: "ADCA_BASE", displayName: "ADCA"},
        { name: "ADCB_BASE", displayName: "ADCB"},
        { name: "ADCD_BASE", displayName: "ADCD"},
    ],
    F2837xS : [
        { name: "ADCA_BASE", displayName: "ADCA"},
        { name: "ADCB_BASE", displayName: "ADCB"},
        { name: "ADCC_BASE", displayName: "ADCC"},
        { name: "ADCD_BASE", displayName: "ADCD"},
    ],
    F2837xD : [
        { name: "ADCA_BASE", displayName: "ADCA"},
        { name: "ADCB_BASE", displayName: "ADCB"},
        { name: "ADCC_BASE", displayName: "ADCC"},
        { name: "ADCD_BASE", displayName: "ADCD"},
    ],
    F28004x : [
        { name: "ADCA_BASE", displayName: "ADCA"},
        { name: "ADCB_BASE", displayName: "ADCB"},
        { name: "ADCC_BASE", displayName: "ADCC"},
    ],
    F2838x : [
        { name: "ADCA_BASE", displayName: "ADCA"},
        { name: "ADCB_BASE", displayName: "ADCB"},
        { name: "ADCC_BASE", displayName: "ADCC"},
        { name: "ADCD_BASE", displayName: "ADCD"},
    ],
    F28002x : [
        { name: "ADCA_BASE", displayName: "ADCA"},
        { name: "ADCC_BASE", displayName: "ADCC"},
    ],
    F28003x : [
        { name: "ADCA_BASE", displayName: "ADCA"},
        { name: "ADCB_BASE", displayName: "ADCB"},
        { name: "ADCC_BASE", displayName: "ADCC"},
    ],
    F280013x : [
        { name: "ADCA_BASE", displayName: "ADCA"},
        { name: "ADCC_BASE", displayName: "ADCC"},
    ],
    F280015x : [
        { name: "ADCA_BASE", displayName: "ADCA"},
        { name: "ADCC_BASE", displayName: "ADCC"},
    ],
    F28P55x : [
        { name: "ADCA_BASE", displayName: "ADCA"},
        { name: "ADCB_BASE", displayName: "ADCB"},
        { name: "ADCC_BASE", displayName: "ADCC"},
        { name: "ADCD_BASE", displayName: "ADCD"},
        { name: "ADCE_BASE", displayName: "ADCE"},
    ],
    F28P65x : [
        { name: "ADCA_BASE", displayName: "ADCA"},
        { name: "ADCB_BASE", displayName: "ADCB"},
        { name: "ADCC_BASE", displayName: "ADCC"},
    ],
}

var ADC_INSTANCE = DEVICES_ADC_INSTANCES[Common.getDeviceName()]
var maxInstances = ADC_INSTANCE.length

/* Array of ADC configurables that are common across device families */
let config = [
    {
        name        : "adcBase",
        displayName : "ADC Instance",
        description : 'Instance of the ADC used.',
        hidden      : false,
        default     : ADC_INSTANCE[0].name,
        options     : ADC_INSTANCE,
        // TODO: decide if total or partial removal of onChangeADC
        // onChange    : onChangeADC
    },
    // {
    //     name: "GROUP_COPY",
    //     displayName: "Copy Settings",
    //     description: "",
    //     longDescription: "",
    //     config: [
    //         {
    //             name: "copyUse",
    //             displayName : "Use Copy Feature",
    //             description : '',
    //             hidden      : false,
    //             default     : false,
    //             onChange    : (inst, ui) => {
    //                 ui.copyFrom.hidden = !inst.copyUse;
    //                 ui.copyPerform.hidden = !inst.copyUse;
    //             }
    //         },
    //         {
    //             name: "copyFrom",
    //             displayName : "Copy From",
    //             description : 'The SysConfig name for the EPWM to copy from',
    //             hidden      : true,
    //             default     : ""
    //         },
    //         {
    //             name: "copyPerform",
    //             displayName : "One-shot Copy",
    //             description : '',
    //             hidden      : true,
    //             buttonText: "Copy ADC Configuration",
    //             onLaunch: (inst) => {
    //                 return ({
    //                     command: "../driverlib/.meta/epwm/epwmMemory.bat",
    //                     args: ["", "$comFile"],
    //                     initialData: "",
    //                 });
    //             },
    //             onComplete: (inst, ui, result) => {
    //                 performCopy(inst, ui)
    //             },
    //         },
    //     ]
    // },
    // ADC_setPrescaler()
    {
        name        : "adcClockPrescaler",
        displayName : "ADC Clock Prescaler",
        description : 'Clock prescaler for ADC.',
        hidden      : false,
        default     : device_driverlib_peripheral.ADC_ClkPrescale[0].name,
        options     : device_driverlib_peripheral.ADC_ClkPrescale,
    },
    // {
    //     name        : "oSDetectMode",
    //     displayName : "Open/Shorts Detection Circuit Mode",
    //     description : 'Select the open/short circuit detection mode.',
    //     hidden      : false,
    //     default     : device_driverlib_peripheral.ADC_OSDetectMode[0].name,
    //     options     : device_driverlib_peripheral.ADC_OSDetectMode,
    // },

];

if (["F2837xD", "F2837xS" ,"F2838x","F28P65x"].includes(Common.getDeviceName()))
{
    // ADC_setMode()
    config = config.concat([
        {
            name: "adcResolutionMode",
            displayName : "ADC Resolution Mode",
            description : 'Select the ADC resolution mode.',
            hidden      : false,
            default     : device_driverlib_peripheral.ADC_Resolution[0].name,
            options     : device_driverlib_peripheral.ADC_Resolution,
        },
        {
            name: "adcSignalMode",
            displayName : "ADC Signal Mode",
            description : 'Select the ADC signal mode.',
            hidden      : false,
            default     : device_driverlib_peripheral.ADC_SignalMode[0].name,
            options     : device_driverlib_peripheral.ADC_SignalMode,
        },
        
    ]);
}

let channels = [
    {name: "0" , displayName: "0" },
    {name: "1" , displayName: "1" },
    {name: "2" , displayName: "2" },
    {name: "3" , displayName: "3" },
    {name: "4" , displayName: "4" },
    {name: "5" , displayName: "5" },
    {name: "6" , displayName: "6" },
    {name: "7" , displayName: "7" },
    {name: "8" , displayName: "8" },
    {name: "9" , displayName: "9" },
    {name: "10", displayName: "10"},
    {name: "11", displayName: "11"},
    {name: "12", displayName: "12"},
    {name: "13", displayName: "13"},
    {name: "14", displayName: "14"},
    {name: "15", displayName: "15"},
]

var defaultADCPinInfos = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName("A0"));
var defaultPinCp = device_adc_Cp["ADCINA0"]
var defaultPinCPValue = ESTIMATED_CP
if (defaultPinCp)
{
    defaultPinCPValue = defaultPinCp.CMP_EN
}

var soc_configs = [
    {
        name        : "enabledSOCs",
        displayName : "Enable SOCs",
        description : 'Select which SOCs to enable.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : device_driverlib_peripheral.ADC_SOCNumber,
        onChange    : onChangeEnabledSOCs
    },
]

function addSOCGroup(soci){
    var eachSocConfig = [
        // ADC_setupSOC(), channel
        {
            name: "soc" + soci.toString() + "Name",
            displayName : "SOC" + soci.toString() + " Name",
            description : 'Select the application name of the channel for this SOC',
            hidden      : true,
            default     : "SOC" + soci.toString(),
        },
        {
            name: "soc" + soci.toString() + "IndependentNameMode",
            displayName : "SOC" + soci.toString() + " Independent Name Mode",
            description : 'Select the application name of the channel for this SOC and do not append the ADC instance name.',
            longDescription : 'When this option is checked, the #define generated for this SOC name will not include the ADC instance name prepend. Instead it will be a unique name. ' +
                              'Also it will trigger the generation of a new #define for the BASE of this SOC following the format "SOCx Name"_BASE ',
            hidden      : true,
            default     : false,
        },
        {
            name: "soc" + soci.toString() + "Channel",
            displayName : "SOC" + soci.toString() + " Channel",
            description : 'Select the channel for this SOC',
            hidden      : true,
            default     : device_driverlib_peripheral.ADC_Channel[0].name,
            options     : device_driverlib_peripheral.ADC_Channel,
            // TODO: decide if total or partial removal of onChangeADC
            // onChange    : onChangeADC,
        },
       
        {
            name: "soc" + soci.toString() + "ModuleChannelName",
            displayName : "SOC" + soci.toString() + " Module Channel Name",
            description : 'The ADC module\'s channel name',
            hidden      : true,
            //getValue    : calculateModuleChannelName,
            getValue    : (inst) => calculateModuleChannelName(inst, soci),
            default     : "A0"
        },
        {
            name: "soc" + soci.toString() + "DevicePinName",
            displayName : "SOC" + soci.toString() + " Device Pin Name",
            description : 'The device pin name and the signal name for that pin',
            hidden      : true,
            //getValue    : calculateDevicePinName,
            getValue    : (inst) => calculateDevicePinName(inst,soci),
            default     : Pinmux.getDevicePinInfoDescription(defaultADCPinInfos)
        },
    ]
    if (["F28P65x", "F28P55x"].includes(Common.getDeviceName())){
        eachSocConfig = eachSocConfig.concat(
        [
            {
                name: "soc" + soci.toString() + "ExtChannel",
                displayName : "SOC" + soci.toString() + " External Channel Selected via MUX",
                description : 'Select the channel associated to external MUX for this SOC. To use the external channel, you must first enable External MUX',
                hidden      : true,
                default     : device_driverlib_peripheral.ADC_ExtChannel[0].name,
                options     : (inst) => 
                    {
                        var numberofpins = inst["adcNumExtPins"];
                        var numberofchannel = Math.pow(2, numberofpins);
                        let channel=[]
                        if ((inst.enableEXTMUX)) {
                            for (var option of device_driverlib_peripheral.ADC_ExtChannel) {
                                var number_mux_channel = option.name.replace(/[^0-9]/g,'');
                                if (number_mux_channel < numberofchannel) {
                                    channel.push({name:option.name, displayName: option.displayName})
                                }
                            
                            }
                            return channel;
                        }
                        return channel;
                    },
               
            },
        ])
    }
    eachSocConfig = eachSocConfig.concat([
        {
            name: "GROUP_SOC" + soci.toString() + "_TRIGS",
            displayName: "SOC Triggers",
            longDescription: longDescriptionSocTriggers,
            config : SOCTrigger_configs 
        }, 
        {
            name        : "GROUP_SOC" + soci.toString() + "_SAMPLE_TIME_CALCULATOR",
            displayName : "Sample Time Calculator",
            longDescription : longDescriptionSocSamplingTimeCalculator,
            config      : [
                {
                    name: "soc" + soci.toString() + "UseSampleTimeCalculator",
                    displayName: "Use Sample Time Calculator",
                    hidden: true,
                    default: false,
                    onChange: onChangeSampleTimeCalculator,
                },
                {
                    name: "soc" + soci.toString() + "ADCSwitchResistance",
                    displayName: "Ron ADC Sampling Switch Resistance [Ohms]",
                    hidden: true,
                    readOnly: true,
                    default: device_adc_Ron.REF,
                },
                {
                    name: "soc" + soci.toString() + "ADCSampleCapacitance",
                    displayName: "Ch ADC Sampling Capacitance [pF]",
                    hidden: true,
                    readOnly: true,
                    default: device_adc_Ch.REF,
                },
                {
                    name: "soc" + soci.toString() + "ADCParasiticCapacitance",
                    displayName: "Cp ADC Channel Parasitic Capacitance [pF]",
                    hidden: true,
                    //getValue: calculateParasiticCapacitance,
                    getValue: (inst) => calculateParasiticCapacitance(inst,soci),
                    default: defaultPinCPValue,
                },
                {
                    name: "soc" + soci.toString() + "InputCapacitance",
                    displayName: "Cs Input Capacitance [pF]",
                    hidden: true,
                    default: 0,
                },
                {
                    name: "soc" + soci.toString() + "InputResistance",
                    displayName: "Rs Input Resistance [Ohms]",
                    hidden: true,
                    default: 0,
                },
                {
                    name: "soc" + soci.toString() + "SettlingError",
                    displayName: "Settling Error [LSB]",
                    hidden: true,
                    readOnly: false,
                    default: 0.5,
                },
                {
                    name: "soc" + soci.toString() + "CalculatedSampleTime",
                    displayName: "Calculated Sample Time [ns]",
                    hidden: true,
                    //readOnly: true,
                    getValue: (inst) => calculateSampleTime(inst,soci),
                    default: 0,
                },
                {
                    name: "soc" + soci.toString() + "UseCalculatedSampleTime",
                    displayName: "Use Calculated Sample Time for this SOC",
                    hidden: true,
                    default: false,
                    onChange: onChangeSampleTimeCalculator,
                }

            ]
        },
        // ADC_setupSOC(), sampleWindow
        {
            name: "soc" + soci.toString() + "SampleWindow",
            displayName : "SOC" + soci.toString() + " Sample Window [SYSCLK counts]",
            description : 'Select the sample window (1-512) for this SOC',
            hidden      : true,
            default     : 1,
            onChange: onChangeSampleTimeCalculator,
        },
        {
            name: "soc" + soci.toString() + "SampleWindowCalculated",
            displayName : "SOC" + soci.toString() + " Sample Window [SYSCLK counts]",
            description : 'Select the sample window (1-512) for this SOC',
            hidden      : true,
            getValue    : (inst) => calculateSampleWindow(inst,soci),
            default     : 1,
        },
        {
            name: "soc" + soci.toString() + "SampleTime",
            displayName : "SOC" + soci.toString() + " Sample Time [ns]",
            description : 'Selected the sample time in ns for this SOC',
            hidden      : true,
            getValue    : (inst) => calculateChosenSampleTime(inst,soci),
            default     : ADC_SampleTime_SysClk_ns
        },
    ])
    soc_configs = soc_configs.concat([{
        name: "GROUP_SOC" + soci.toString(),
        displayName: "SOC" + soci.toString(),
        description: "Start of Conversion " + soci.toString(),
        longDescription: "",
        config: eachSocConfig
    }
]);
}

for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
    var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
    var soci = (currentSOC).replace(/[^0-9]/g,'')
    var SOCTrigger_configs =[]
    if (["F28P65x", "F28P55x"].includes(Common.getDeviceName())){
    SOCTrigger_configs = SOCTrigger_configs.concat([
        // Trigger mode
        {
            name: "soc" + soci.toString() + "Triggermode",
            displayName: "Trigger Mode",
            description : 'Single trigger or repeater mode can be selected as trigger source for this SOC',
            hidden: true,
            default: "singlemode",
            options: [
                {name:"singlemode", displayName:"Single Trigger"},
                {name:"repeatermode", displayName:"Use Repeater Trigger"},
            ],  
        },
    ])
    }
    SOCTrigger_configs = SOCTrigger_configs.concat([
        // ADC_setupSOC(), trigger
       {
            name: "soc" + soci.toString() + "Trigger",
            displayName : "SOC" + soci.toString() + " Trigger",
            description : 'Select the trigger source for this SOC',
            hidden      : true,
            default     : device_driverlib_peripheral.ADC_Trigger[0].name,
            options     : device_driverlib_peripheral.ADC_Trigger,
        },

        // ADC_setInterruptSOCTrigger(), trigger
        {
            name: "soc" + soci.toString() + "InterruptTrigger",
            displayName : "SOC" + soci.toString() + " Interrupt Trigger",
            description : 'Select the interrupt trigger source for this SOC. This signal is ORed with the SOC Trigger',
            hidden      : true,
            default     : device_driverlib_peripheral.ADC_IntSOCTrigger[0].name,
            options     : device_driverlib_peripheral.ADC_IntSOCTrigger,
        },
    ])

addSOCGroup(soci);
}

if (["F28P65x", "F28P55x"].includes(Common.getDeviceName()))
{
    // ADC_setMode()
    config = config.concat([
        {
            name        : "enableTDMA",
            displayName : "Enable alternate timings (tDMA)",
            longDescription : 'This option enables the alternate timings (tDMA) for DMA trigger. When enabled the DMA is always triggered at tDMA regardless of whether the ADC is in early interrupt mode or late interrupt mode.',
            hidden      : false,
            default     : true,
        },
        {
            name        : "enableEXTMUX",
            displayName : "Use External MUX",
            description : 'This option enables using the external mux by configuring the external channel pin via OUTPUTXBAR for an SOC.',
            hidden      : false,
            default     : false,
            onChange: extChanOnChange,
            
        },
        {
            name        : "extTiming",
            displayName : "Timing Mode",
            longDescription : 'External MUX Selection Timing Mode allows the next SOC to be sent out as soon as the current SOC finishes converting, instead of waiting for the SOC to start. Since mux switching time adds to the sample+hold requirement, pre-selecting the mux this way would help negate that impact and maintain throughput.',
            hidden      : true,
            default     : "Normal",
            options:[
                {name: "Normal", displayName:"Normal",},
                {name: "Preselection", displayName:"External MUX Timing",},
            ],
            onChange: extChanOnChange,
        },
        
    ]);
}

config = config.concat([
        // ADC_setSOCPriority, priMode
    {
        name        : "socHighPriorityMode",
        displayName : "High Priority Mode SOCs",
        description : 'Select the range of high priority SOCs.',
        hidden      : false,
        default     : device_driverlib_peripheral.ADC_PriorityMode[0].name,
        options     : device_driverlib_peripheral.ADC_PriorityMode,
        onChange    : onChangeHighPriorityMode
    },
])

if (["F28P65x", "F28P55x"].includes(Common.getDeviceName()))
{
var adcextmuxdescription = `
The External MUX Selected Channel field in each SOC can be used to automatically control an external mux via digital output pins indicated by OUTPUTXBAR. 

This allows the user the flexibility to increase the ADC channel count via an external mux with minimal SW overhead. The External Channel pins are made available by mapping them to GPIO mux positions just like any other peripheral.  This could include AIO pins if the device allows peripherals to be muxed onto these pins and the AIOs support output mode.  The user also does not need to mux out all 4 pins if they have a small mux. To select a specific muxed channel, the user sets an SOC to use the SOC Channel that the mux output is connected to along with the SOC External MUX Selected Channel value that will select the desired channel. 

There are a variety of potential mux topologies the customer could use.  The most basic would be a single external mux connected to a single ADC input channel. 

•	To select ADCIN0.4, the user configures the SOC with Channel = 0 and External MUX Selected Channel = 4.

•	To select ADCIN3, the user configures the SOC with Channel = 3 and SOC External MUX Selected Channel = (don’t care).

![an offline image](../../driverlib/.meta/adc/docs/adcextmux.png)
`
var adcextchConfigs =
        [
            {
                name:"adcNumExtPins",
                displayName: "Number of ADC External Mux Pins",
                longDescription:' The external channel select pins are made available by mapping them to the output X-BAR.',
                hidden: true,
                default: 0,
                options:
                [ 
                {
                    name: 0
                },
                {
                    name: 1
                },
                {
                    name: 2
                },
                {
                    name: 3
                },
                {
                    name: 4
                }
                ],
                onChange : extChanOnChange,
            },
        ]
            // {
            //     name: "extchannel0pin",
            //     displayName: "External Channel Pin",
            //     default: "",
                
            //     getValue: (inst) =>
            //     {
            //         /*for (var xbari=0; xbari< inst["adcNumExtPins"]; xbari++)*/
                    
            //             if (inst.adcextchan0) 
            //             {
            //                 Common.printDebugObject(inst.adcextchan0.outputxbar.outputxbarPin.$solution.devicePinName)
                            
            //                 return inst.adcextchan0.outputxbar.outputxbarPin.$solution.devicePinName.toString()
            //             }
                        
            //             return ""
                    
                    
            //     }
            // },
            
        for (let xbari=0; xbari< 4; xbari++){
            adcextchConfigs= adcextchConfigs.concat([
                {
                    name        : "extchannel"+ xbari+" pin",
                    displayName : "External Channel " + xbari+ " Pin",
                    default     : "",
                    hidden      : true,
                    getValue    : (inst)=>
                    
                    {
                        if (Common.isContextCPU1()) {
                            if (inst["adcextchan"+xbari]) 
                            { 
                                if (inst["adcextchan"+xbari].outputxbar.outputxbarPin.$solution.devicePinName){
                                    return inst["adcextchan"+xbari].outputxbar.outputxbarPin.$solution.devicePinName.toString()
                                }
                                else {
                                    return ""
                                }   
                            }
                            return ""
                        }
                        if (Common.isContextCPU2()) {
                            if (Common.isMultiCoreSysConfig())
                            {
                                let outputxbar = system.contexts.CPU1.system.modules["/driverlib/outputxbar.js"];
                                if (outputxbar!=null) {
                                        
                                    var selectedoutputxbarinstance = null
                                    for ( var outputxbar_inst of outputxbar.$instances) {
                                        if ((outputxbar_inst.sourceSignals).includes(inst.adcBase.replace("_BASE", "_EXTMUXSEL") + xbari)) 
                                        {
                                            selectedoutputxbarinstance = outputxbar_inst
                                            break    
                                        }
                                        if (selectedoutputxbarinstance != null) {
                                            
                                            return selectedoutputxbarinstance.outputxbar.outputxbarPin.$solution.devicePinName.toString() 
                                        }          
                                    }
    
                                    if (selectedoutputxbarinstance != null) 
                                    {
                                        return selectedoutputxbarinstance.outputxbar.outputxbarPin.$solution.devicePinName.toString()
                                        
                                    }
                                    if (selectedoutputxbarinstance == null) 
                                    {
                                        return""
                                    }
                                                
                                }
                                else {
                                    return ""
                                }
                            }
                            else{
                                return ""
                            }
                        }
                                        
                    }
                }
            ])  
        }


    config = config.concat([
        {
            name: "GROUP_ADC_EXT_CHAN",
            displayName: "ADC External Mux Channel",
            longDescription: adcextmuxdescription,
            config: adcextchConfigs,    
        },
    ])
}
config = config.concat([
{
    name: "GROUP_SOC",
    displayName: "SOC Configurations",
    description: "Start of Conversion Configurations",
    longDescription: "",
    config: soc_configs
},
])
// TODO: remember to point out we switched to having default Enable. remove this comment later.
// ADC_enableConverter() / ADC_disableConverter()
config = config.concat([
    {
        name        : "enableConverter",
        displayName : "Enable ADC Converter",
        description : 'Enable the ADC Converter',
        hidden      : true,
        default     : true,
    },

])

if (["F28P65x", "F28P55x"].includes(Common.getDeviceName()))
{
    var repeatermoduledescription ='The ADC contains two trigger repeater modules. These modules can select any of the regular ADC triggers that are selectable by Trigger, and generate a number of repeat pulses as configured in Count field. Each repeater module can apply four types of trigger modifications: oversampling, undersampling, phase delay and re-trigger spread.The ADC trigger repeater module is shown here: ![an offline image](../../driverlib/.meta/adc/docs/adcrepeater.png)'
    var repeatermodedescription ='In oversampling mode, the repeater module passes the initial trigger through to the output. As soon as all SOCs configured to receive the trigger are in progress or completed, it issues the trigger again. The process repeats until the configured number of trigger pulses (NSEL + 1) have been issued.In undersampling mode, the repeater module passes the initial trigger through to the output, and then blocks subsequent triggers until it has received the configured number of trigger pulses (NSEL + 1). The result is that only 1 in every (NSEL + 1) pulses passes through to the output.'
    var repeaterphasedescription = 'The repeater module can delay the initial trigger by a specified number of SYSCLK cycles. The phase delay does not affect the timing between subsequent repeated oversampled triggers—it only delays the initial trigger.'
    var repeaterspreaddescription = 'If additional time between samples is desired, the application may configure SPREAD equal to the number of SYSCLK cycles desired between samples.'
    var repeaterConfigs=[]
    for(var rptrIndex in device_driverlib_peripheral.ADC_RepInstance)
    { 
        var currentRPTR = device_driverlib_peripheral.ADC_RepInstance[rptrIndex].name
        let rptri = (currentRPTR).replace(/[^0-9]/g,'')
        repeaterConfigs= repeaterConfigs.concat
        ([
            {
                name:"repeater"+ rptri.toString(), 
                displayName: "Repeater Module"+ rptri.toString(),
                longDescription: repeatermoduledescription,
                collapsed: true,
                config:
                [ 
                    {
                        name: "repeater" + rptri.toString()+ " Mode",
                        displayName :  "Mode",
                        longDescription : repeatermodedescription,
                        default     : device_driverlib_peripheral.ADC_RepMode[0].name,
                        options     : device_driverlib_peripheral.ADC_RepMode,   
                    },
                    {
                        name: "repeater" + rptri.toString()+ " Trigger",
                        displayName :  "Trigger",
                        description : 'Select the trigger source for this Repeater',
                        default     : "ADC_TRIGGER_SW_ONLY",
                        options     : /*device_driverlib_peripheral.ADC_Trigger,*/ (inst)=> 
                        {
                            var triggeroptions=[]
                            for (var option of device_driverlib_peripheral.ADC_Trigger)
                            {
                                if (!["ADC_TRIGGER_REPEATER1","ADC_TRIGGER_REPEATER2",].includes(option.name))
                                {
                                    triggeroptions.push({name:option.name, displayName: option.displayName})
                                }
                            }
                            return triggeroptions;                       
                        }, 
                        
                    },
                    {
                        name: "repeater" + rptri.toString()+ " SyncInput",
                        displayName : "Sync Input Source",
                        description : 'Select the Sync source for this Repeater',
                        default     : device_driverlib_peripheral.ADC_SyncInput[0].name,
                        options     : device_driverlib_peripheral.ADC_SyncInput
                        
        
                    },
                    {
                        name: "repeater" + rptri.toString()+ " Count",
                        displayName : "Trigger Count",
                        description : 'Select the count for this Repeater',
                        default     : 1,
                        
        
                    },
                    {
                        name: "repeater"  + rptri.toString()+ " Phase",
                        displayName : "Trigger Phase Delay in SYSCLK Cycles",
                        longDescription : repeaterphasedescription,
                        default     : 0,
        
        
                    },
                    {
                        name: "repeater" + rptri.toString()+ " Spread",
                        displayName : "Trigger Spread in SYSCLK Cycles",
                        longDescription : repeaterspreaddescription,
                        default     : 0,
        
                    },
                    {
                        name: "repeater" + rptri.toString()+ " SelectedSocs",
                        displayName : "Selected SOCs",
                        description : 'Selected SOCs for this repeater',
                        default     : "",
                        getValue: (inst)=> 
                        {
                            var selectedsocs= ""
                            for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber)
                            { 
                                var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
                                var soci = (currentSOC).replace(/[^0-9]/g,'')
                                if(((inst.enabledSOCs).includes(currentSOC)) && ((inst["soc" + soci.toString() + "Trigger"]) == ("ADC_TRIGGER_REPEATER"+rptri.toString())))
                                { 
                                    selectedsocs += (selectedsocs != "")?", ": "";
                                    selectedsocs+= "SOC " + soci.toString();                                    
                                }
                            }
                            return selectedsocs;
                        }
                    },
                ]
            },
        ])  
    }
    config = config.concat
    ([
        { 
            name: "GROUP_REPEATER_MODULE",
            displayName: "ADC Repeater Module",
            config: repeaterConfigs
         },
    ])  
}

var ppb_configs = []

ppb_configs = ppb_configs.concat([
    {
        name        : "enabledPPBs",
        displayName : "Enable PPBs",
        description : 'Select which PPBs to enable.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : device_driverlib_peripheral.ADC_PPBNumber,
        onChange    : onChangeEnabledPPBs
    },
])

for(var ppbIndex in device_driverlib_peripheral.ADC_PPBNumber)
{
    var currentPPB = device_driverlib_peripheral.ADC_PPBNumber[ppbIndex].name
    var ppbi = (currentPPB).replace(/[^0-9]/g,'')
    var ppbx_configs = [
        {
            name: "ppb" + ppbi.toString() + "Name",
            displayName : "Name",
            description : 'Select the PPB name for this PPB',
            hidden      : true,
            default     : "PPB" + ppbi.toString()
        },
        {
            name: "ppb" + ppbi.toString() + "IndependentNameMode",
            displayName : "Independent Name Mode",
            description : 'Select the application name of the PPB and do not append the ADC instance name.',
            longDescription : 'When this option is checked, the #define generated for this PPB name will not include the ADC instance name prepend. Instead it will be a unique name. ' +
                              'Also it will trigger the generation of a new #define for the SOC of this PPB following the format',
            hidden      : true,
            default     : false,
        },
        // ADC_setupPPB(), socNumber
        {
            name: "ppb" + ppbi.toString() + "SOCNumber",
            displayName : "SOC Number",
            description : 'Select the SOC for this PPB',
            hidden      : true,
            default     : device_driverlib_peripheral.ADC_SOCNumber[0].name,
            options     : device_driverlib_peripheral.ADC_SOCNumber,
        },
        
        // ADC_enablePPBEvent() / ADC_disablePPBEvent, evtFlags
        {
            name: "ppb" + ppbi.toString() + "EventEnable",
            displayName :  "Enable Events",
            description : 'Select the EVENTs to enable for this PPB',
            hidden      : true,
            minSelections: 0,
            default     : [],
            options     : [
                {name: "ADC_EVT_TRIPHI", displayName: "ADC Event TRIP HIGH"},
                {name: "ADC_EVT_TRIPLO", displayName: "ADC Event TRIP LOW"},
                {name: "ADC_EVT_ZERO", displayName: "ADC Event ZERO CROSSING"},
            ],
        },
        // ADC_enablePPBEventInterrupt() / ADC_disablePPBEventInterrupt(), intFlags
        {
            name: "ppb" + ppbi.toString() + "EventInterruptEnable",
            displayName : "Enable Interrupt Events",
            description : 'Select the Interrupt EVENTs to enable for this PPB',
            hidden      : true,
            minSelections: 0,
            default     : [],
            options     : [
                {name: "ADC_EVT_TRIPHI", displayName: "ADC Event TRIP HIGH"},
                {name: "ADC_EVT_TRIPLO", displayName: "ADC Event TRIP LOW"},
                {name: "ADC_EVT_ZERO", displayName: "ADC Event ZERO CROSSING"},
            ],
        },
        // ADC_setPPBCalibrationOffset(), offset
        {
            name: "ppb" + ppbi.toString() + "CalibrationOffset",
            displayName : "Calibration Offset",
            description : 'Calibration offset applied to this PPB',
            hidden      : true,
            default     : 0
        },
        // ADC_setPPBReferenceOffset(), offset
        {
            name: "ppb" + ppbi.toString() + "ReferenceOffset",
            displayName : "Reference Offset",
            description : 'Reference offset applied to this PPB',
            hidden      : true,
            default     : 0
        },
        // ADC_enablePPBTwosComplement() / ADC_disablePPBTwosComplement()
        {
            name: "ppb" + ppbi.toString() + "EnableTwosComplement",
            displayName : "Invert Output (Enable Two's Complement)",
            description : 'Select to enable the Two\'s complement mode for this PPB',
            hidden      : true,
            default     : false
        },
        // ADC_setPPBTripLimits(), tripHiLimit
        {
            name: "ppb" + ppbi.toString() + "HighTripLimit",
            displayName : "High Trip Limit",
            description : 'High Trip limit for this PPB',
            hidden      : true,
            default     : 0
        },
        // ADC_setPPBTripLimits() , tripLoLimit
        {
            name: "ppb" + ppbi.toString() + "LowTripLimit",
            displayName : "Low Trip Limit",
            description : 'Low Trip limit for this PPB',
            hidden      : true,
            default     : 0
        },   
    ]
    if (["F28P65x", "F28P55x"].includes(Common.getDeviceName())) {
        ppbx_configs = ppbx_configs.concat([
            //ADC_PPBIntSrcSelect(), osIntSrc
            {
                name: "ppb" + ppbi.toString() + "SelectOSINTSource",
                displayName: "OSINT Source",
                description: "Select source to generate over-sampling interrupt (OSINT)",
                longDescription: "The oversampling interrupt can be generated if either the sample count limit defined in Accumulation Limit is reached, an external hardware sync event occurs, or the software forces a sync event.",
                hidden: true,
                default: device_driverlib_peripheral.ADC_PPBIntSrcSelect[0].name,
                options: device_driverlib_peripheral.ADC_PPBIntSrcSelect,
            },
            //ADC_setPPBCountLimit(), limit
            {
                name: "ppb" + ppbi.toString() + "AccumulationLimit",
                displayName: "Accumulation Limit",
                description:
                "Select target sample counts to generate over-sampling interrupt",
                longDescription: "Accumulation Limit defines the number of ADC conversions to accumulate before partial sum is automatically loaded to the sum registers. When the partial conversion count equals the Accumulation Limit, the PPB loads the values of the respective partial result registers into the final result registers and generates an oversampling event interrupt",
                hidden: true,
                default: 0,
            },
            //ADC_selectPPBSyncInput(), SyncInput
            {
                name: "ppb" + ppbi.toString() + "SyncInput",
                displayName: "Sync Source",
                description: "Select the Sync source  for this PPB",
                longDescription: "This option configures desired sync event to transfer partial registers to final registers and reset the partial registers.",
                hidden: true,
                default: device_driverlib_peripheral.ADC_SyncInput[0].name,
                options: device_driverlib_peripheral.ADC_SyncInput,
            },
            //ADC_selectPPBCompareSource(), compSrc
            {
                name: "ppb" + ppbi.toString() + "CompSource",
                displayName: "Compare Source",
                description: "Select the compare source for this PPB",
                hidden: true,
                default: device_driverlib_peripheral.ADC_PPBCompSource[0].name,
                options: device_driverlib_peripheral.ADC_PPBCompSource,
            },
            // ADC_setPPBShiftValue, shiftVal
            {
                name: "ppb" + ppbi.toString() + "Rightshift",
                displayName: "Number of Bits to Right Shift PSUM",
                description: "Select number of bits to right shift PSUM before loading to final PPB SUM",
                hidden: true,
                default: 0,
            },
            // ADC_enablePPBAbsoluteValue, AbsVal
            {
                name: "ppb" + ppbi.toString() + "AbsValue",
                displayName: "Calculate absolute value",
                description: "This function enables absolute value capability in the PPB",
                hidden: true,
                default: false,
            },
        ]);
    }

    if (!["F2807x", "F2837xS", "F2837xD"].includes(Common.getDeviceName()))
    // ADC_enablePPBEventCBCClear() / ADC_disablePPBEventCBCClear(), ppbNumber
    {
        ppbx_configs = ppbx_configs.concat([
            {
                name        : "ppb" + ppbi.toString() + "EnablePPBEventCBCClear",
                displayName : "Enable PPB Event CBC Clear",
                description : 'Enables the automatic cycle-by-cycle clear of ADC PPB event' +
                ' flags. When enabled, the desired PPB event flags are automatically cleared' +
                ' on the next PPBxRESULT load, unless a ppbx_configschangeonset condition is also occurring at' +
                ' the same time, in which case the set takes precedence',
                hidden      : true,
                default     : false
            }
        ]);
    }

    ppb_configs = ppb_configs.concat([{
        name: "GROUP_PPB" + ppbi.toString(),
        displayName: "PPB" + ppbi.toString(),
        description: "Post Processing Block " + ppbi.toString(),
        longDescription: "",
        config: ppbx_configs
    }])

}

var int_configs = [
    // ADC_setInterruptPulseMode(), pulseMode
    {
        name        : "interruptPulseMode",
        displayName : "ADC Interrupt Pulse Mode",
        description : 'Interrupt Pulse Mode for ADC EOC (end of conversion).',
        hidden      : false,
        default     : device_driverlib_peripheral.ADC_PulseMode[0].name,
        options     : device_driverlib_peripheral.ADC_PulseMode,
        onChange    : (inst, ui) => {
            if (!["F2807x", "F2837xS", "F2837xD"].includes(Common.getDeviceName()))
            {
                if (inst["interruptPulseMode"] == "ADC_PULSE_END_OF_ACQ_WIN")
                {
                    ui["interruptCycleOffset"].hidden = false
                }
                else
                {
                    ui["interruptCycleOffset"].hidden = true
                }
            }
        }
    }
]

if (!["F2807x", "F2837xS", "F2837xD"].includes(Common.getDeviceName()))
{
    // ADC_setInterruptCycleOffset(), cycleOffset
    int_configs = int_configs.concat([
        {
            name        : "interruptCycleOffset",
            displayName : "ADC Interrupt Cycle Offset",
            description : 'Cycle offset between the negative edge of a sample ' +
                          'pulse and an early interrupt pulse being generated.',
            hidden      : false,
            default     : 0
        }
    ]);
}

int_configs = int_configs.concat([
    {
        name        : "enabledInts",
        displayName : "Enable ADC Interrupts",
        description : 'Select which INTs to enable.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : device_driverlib_peripheral.ADC_IntNumber,
        onChange    : onChangeEnabledInts
    },
])
var interruptSourceOption = device_driverlib_peripheral.ADC_SOCNumber;
if (["F28P65x", "F28P55x"].includes(Common.getDeviceName())){
    interruptSourceOption = device_driverlib_peripheral.ADC_IntTrigger;
}
    for(var intIndex in device_driverlib_peripheral.ADC_IntNumber){ 
        var currentINT = device_driverlib_peripheral.ADC_IntNumber[intIndex].name
        var inti = (currentINT).replace(/[^0-9]/g,'')
        int_configs = int_configs.concat([
            {
                name: "GROUP_INT" + inti.toString(),
                displayName: "INT" + inti.toString(),
                description: "ADC Interrupt " + inti.toString(),
                longDescription: "",
                config: [
                    // ADC_enableInterrupt() / ADC_disableInterrupt(), adcIntNum
                    {
                        name: "enableInterrupt" + inti.toString(),
                        displayName : "Enable ADC Interrupt " + inti.toString(),
                        description : 'Enable the interrupt' + inti.toString() + ' for this ADC',
                        hidden      : true,
                        default     : false
                    },
                    // ADC_setInterruptSource(), socNumber
                    {
                        name: "interrupt" + inti.toString() + "SOCSource",
                        displayName : "Interrupt " + inti.toString() + " SOC Source",
                        description : 'Select the source for interrupt' + inti.toString() + ' of this ADC',
                        hidden      : true,
                        default     : interruptSourceOption[0].name,
                        options     : interruptSourceOption,
                    },
                    // ADC_enableContinuousMode()
                    {
                        name: "enableInterrupt" + inti.toString() + "ContinuousMode",
                        displayName : "Continuous Interrupt Mode",
                        description : 'When this is enabled, every EOC signal generates an interrupt regardless of whether the interrupt flag has been cleared or not. When this is disabled, interrupts are suppressed while there is an existing interrupt flag.',
                        hidden      : true,
                        default     : false
                    },
                ]
            }
        ])
    }

config = config.concat([
    {
        name: "GROUP_INT",
        displayName: "ADC INT Configurations",
        description: "Interrupt Configurations",
        longDescription: "",
        config: int_configs
    }
])

var registerIntLongDesc = `
Each ADC module has 4 configurable ADC interrupts. These interrupts can be triggered by any of the 16 EOC
signals. The flag bit for each ADCINT can be read directly to determine if the associated SOC is complete or the
interrupt can be passed on to the PIE.

![an offline image](../../driverlib/.meta/adc/docs/adcEocInts.png "ADC EOC Interrupts")

One PIE interrupt is shared between all the PPBs for a given ADC module.

![an offline image](../../driverlib/.meta/adc/docs/adcPPBInt.png "ADC PPB Interrupt Event")

`;

config = config.concat([
    
              
    {
        name: "GROUP_PPB",
        displayName: "PPB Configurations",
        description: "Post Processing Blocks Configurations",
        longDescription: "",
        config: ppb_configs
    },
    {
        name: "GROUP_BURST",
        displayName: "Burst Mode",
        description: "ADC Burst Mode",
        longDescription: "",
        config: [
             // ADC_enableBurstMode() / ADC_disableBurstMode()
             {
                name        : "enableBurstMode",
                displayName : "Enable Burst Mode",
                description : 'Enable ADC burst mode.',
                hidden      : false,
                default     : false,
            },
            // ADC_setBurstModeConfig(), trigger
            {
                name        : "burstTrigger",
                displayName : "Burst Mode Trigger Signal",
                description : 'The trigger signal for the ADC burst mode.',
                hidden      : false,
                default     : device_driverlib_peripheral.ADC_Trigger[0].name,
                options     : device_driverlib_peripheral.ADC_Trigger,
            },
            // ADC_setBurstModeConfig(), burstSize
            {
                name        : "burstSize",
                displayName : "Burst Size",
                description : 'The size of the burst for the ADC burst mode.',
                hidden      : false,
                default     : 0,
                options     :
                [
                    { name : 0, displayName: "Conversion bursts are 1 SOC long" },
                    { name : 1, displayName: "Conversion bursts are 2 SOC long" },
                    { name : 2, displayName: "Conversion bursts are 3 SOC long" },
                    { name : 3, displayName: "Conversion bursts are 4 SOC long" },
                    { name : 4, displayName: "Conversion bursts are 5 SOC long" },
                    { name : 5, displayName: "Conversion bursts are 6 SOC long" },
                    { name : 6, displayName: "Conversion bursts are 7 SOC long" },
                    { name : 7, displayName: "Conversion bursts are 8 SOC long" },
                    { name : 8, displayName: "Conversion bursts are 9 SOC long" },
                    { name : 9, displayName:  "Conversion bursts are 10 SOC long" },
                    { name : 10, displayName: "Conversion bursts are 11 SOC long" },
                    { name : 11, displayName: "Conversion bursts are 12 SOC long" },
                    { name : 12, displayName: "Conversion bursts are 13 SOC long" },
                    { name : 13, displayName: "Conversion bursts are 14 SOC long" },
                    { name : 14, displayName: "Conversion bursts are 15 SOC long" },
                    { name : 15, displayName: "Conversion bursts are 16 SOC long" },
                ],
            },
        ]
    },
    {
        name: "GROUP_REGISTER_INT",
        displayName: "Register PIE Interrupt Handlers",
        description: "",
        longDescription: registerIntLongDesc,
        collapsed: true,
        config: [
            // use & register interrupts
            {
                name        : "useInterrupts",
                displayName : "Use Interrupt",
                onChange    : onChangeUseInterrupts,
                description : 'Whether or not to use Interrupt mode.',
                hidden      : false,
                default     : true
            },
            {
                name        : "registerInterrupts",
                displayName : "Register Interrupts",
                description : 'Whether or not to register interrupt handlers in the interrupt module.',
                hidden      : false,
                default     : [],
                minSelections: 0,
                options     : [
                    {name: "1", displayName: "Interrupt 1"},
                    {name: "2", displayName: "Interrupt 2"},
                    {name: "3", displayName: "Interrupt 3"},
                    {name: "4", displayName: "Interrupt 4"},
                    {name: "5", displayName: "Event Interrupt"},
                ],
            },
        ]
    },
])

var globalConfig = [

    {
        name: "sampleWindowSYSCLK",
        deprecated: true,
        displayName: "SYSCLK [MHz] for Sample Window Calculation",
        description: "This is the SYSCLK value assumed for sample window calculation and block diagram generation",
        default: ADC_SysClk_MHz,
        onChange : (inst, ui) => {
            
        }
    },
    {
        name: "synchronousModeCheck",
        displayName: "Check for Valid Synchronous Mode",
        description: "Check to see if all SOCs configured for the same trigger have the same sample window",
        default: false
    }
]

function onChangeUseInterrupts(inst, ui){
    if (inst.useInterrupts){
        ui.registerInterrupts.hidden = false
    }
    else{
        ui.registerInterrupts.hidden = true
    }
}

function onChangeADC(inst, ui){
    var adcMod = inst.adcBase.replace("_BASE", "").replace("ADC", "");

    for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
        var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
        var soci = (currentSOC).replace(/[^0-9]/g,'')
        var sociChannel = inst["soc" + soci.toString() + "Channel"].replace("ADC_CH_ADCIN", "").replace("ADCIN", "");
        var sociChannels = sociChannel.split("_");
        var adcInputs = "";
        var adcPinInfosDescriptions = "";
        for (sociChannel of sociChannels)
        {
            var adcInput = adcMod + sociChannel;

            adcInputs += (adcInputs != "")?", ": "";
            adcInputs += adcInput;

            var adcPinInfos = Pinmux.findAllAnalogPin(Pinmux.getDeviceADCName(adcInput));
            if (["14", "15"].includes(sociChannel))
            {
                if (adcPinInfos.length <= 0)
                {
                    adcPinInfos = Pinmux.findAllAnalogPin("ADCIN" + sociChannel);
                }
            }


            adcPinInfosDescriptions += (adcPinInfosDescriptions != "")?", ": "";
            adcPinInfosDescriptions += Pinmux.getDevicePinInfoDescription(adcPinInfos);
        }

        //inst["soc" + soci.toString() + "ModuleChannelName"] = adcInputs;
        if(adcPinInfosDescriptions == Pinmux.NO_DEVICE_PIN_FOUND){
            var internalSignals = InternalConnections.ADC_internalSignals[Common.getDeviceName()][adcInputs]
            if(internalSignals){
                //inst["soc" + soci.toString() + "DevicePinName"] = internalSignals;
            }
            else{
                //inst["soc" + soci.toString() + "DevicePinName"] = adcPinInfosDescriptions;
            }
        }
        else{
            //inst["soc" + soci.toString() + "DevicePinName"] = adcPinInfosDescriptions;
        }

        var inputCp = device_adc_Cp["ADCIN" + adcInput];
        if (!inputCp)
        {
            inputCp = { CMP_DIS: ESTIMATED_CP, CMP_EN: ESTIMATED_CP }
        }
        //inst["soc" + soci.toString() + "ADCParasiticCapacitance"] = inputCp.CMP_EN;
    }
}

function onValidateStatic(mod, stat){
    // console.log("stat");
    // Common.printDebugObject(stat);
    // console.log("mod");
    // Common.printDebugObject(mod);
}

function onValidate(inst, validation) {
  
    if (Common.isContextCPU2()) {
        if (Common.isMultiCoreSysConfig()) {
            //
            // Check if the asysctl module is added on CPU1 if the current context is CPU2
            //
            if (Common.isModuleOnOtherContext("/driverlib/asysctl.js") == false) {
                validation.logError(
                    "The ASYSCTL module needs to be added on CPU1 when an ADC instance is added on CPU2",inst,"adcBase");
            }
            //
            // Check if the analog module is added on CPU1 if the current context is CPU2
            //
            if (Common.isModuleOnOtherContext("/driverlib/analog.js") == false) {
                validation.logError(
                    "The ANALOG PinMux module needs to be added on CPU1 when an ADC instance is added on CPU2",inst,"adcBase");
            }
            //
            // Check if the OUTPUTXBAR module is added on CPU1 if the current context is CPU2
            //
            if (inst.enableEXTMUX) {
                if (Common.isModuleOnOtherContext("/driverlib/outputxbar.js") == false)
                {
                    for (let xbari=0; xbari< inst["adcNumExtPins"]; xbari++){ 
                        validation.logError(
                            "The OUTPUTXBAR module needs to be added on CPU1 when an external MUX is added on CPU2",inst,"enableEXTMUX");
                    }
                }
                else{
                    let outputxbar = system.contexts.CPU1.system.modules["/driverlib/outputxbar.js"];
                    if (outputxbar!=null)
                    {
                        
                        for (let xbari=0; xbari< inst["adcNumExtPins"]; xbari++) { 
                            var selectedoutputxbarinstance = null
                            for ( var outputxbar_inst of outputxbar.$instances) {

                                if ((outputxbar_inst.sourceSignals).includes(inst.adcBase.replace("_BASE", "_EXTMUXSEL") + xbari)) 
                                {
                                    selectedoutputxbarinstance = outputxbar_inst
                                    break
                                } 
                            }
                            if (selectedoutputxbarinstance == null) {
                                validation.logError(
                                    "OUTPUTXBAR module needs to be added on CPU1 when an external MUX is added on CPU2", inst, "extchannel"+ xbari+" pin");
                            }  
                        } 
                    } 
                }
            }
        } 
        else {
            if (inst.enableEXTMUX)
            {
                validation.logWarning(
                    "The OUTPUTXBAR module needs to be added on CPU1 when an external MUX is added on CPU2",inst,"enableEXTMUX");
            }
            validation.logWarning(
                "The ASYSCTL module needs to be added on CPU1 when an ADC instance is added on CPU2",inst,"adcBase");
            validation.logWarning(
                "The ANALOG PinMux module needs to be added on CPU1 when an ADC instance is added on CPU2",inst,"adcBase");
        } 
    }

    //
    // Synchronous Mode
    //

    if (inst.$module.$static["synchronousModeCheck"])
    {
        //
        // Run this once
        //
        var triggers_for_adc_socs = {};

        var runStaticValidation = false;
        if (inst.$module.$instances.length > 0)
        {
            if (inst == inst.$module.$instances[0])
            {
                runStaticValidation = true;
            }
        }

        if (runStaticValidation)
        {
            var synchronousModeErrorFound = false;
            for (var instance_index in inst.$module.$instances)
            {
                var instance_obj = inst.$module.$instances[instance_index];

                if (instance_obj["adcClockPrescaler"] != inst["adcClockPrescaler"])
                {
                    validation.logError(
                        "In synchronous mode all clock prescalers must match! " + inst.$name + " and " + instance_obj.$name +
                        " do not match!",
                        instance_obj, "adcClockPrescaler");
                    synchronousModeErrorFound = true;
                }
                if (inst["adcResolutionMode"])
                {
                    if (instance_obj["adcResolutionMode"] != inst["adcResolutionMode"])
                    {
                        validation.logError(
                            "In synchronous mode all ADC resolutions must match! " + inst.$name + " and " + instance_obj.$name +
                            " do not match!",
                            instance_obj, "adcResolutionMode");
                        synchronousModeErrorFound = true;
                    }
                }
                if (instance_obj["socHighPriorityMode"] != inst["socHighPriorityMode"])
                {
                    validation.logError(
                        "In synchronous mode all ADC high priority modes must match! " + inst.$name + " and " + instance_obj.$name +
                        " do not match!",
                        instance_obj, "socHighPriorityMode");
                    synchronousModeErrorFound = true;
                }
                if (instance_obj["enableBurstMode"] != inst["enableBurstMode"])
                {
                    validation.logError(
                        "In synchronous mode all burst modes must match! " + inst.$name + " and " + instance_obj.$name +
                        " do not match!",
                        instance_obj, "enableBurstMode");
                    synchronousModeErrorFound = true;
                }
                if (instance_obj["enableBurstMode"] && inst["enableBurstMode"])
                {
                    if (instance_obj["burstSize"] != inst["burstSize"])
                    {
                        validation.logError(
                            "In synchronous mode all burst sizes must match! " + inst.$name + " and " + instance_obj.$name +
                            " do not match!",
                            instance_obj, "burstSize");
                        synchronousModeErrorFound = true;
                    }
                    if (instance_obj["burstTrigger"] != inst["burstTrigger"])
                    {
                        validation.logError(
                            "In synchronous mode all burst triggers must match! " + inst.$name + " and " + instance_obj.$name +
                            " do not match!",
                            instance_obj, "burstTrigger");
                        synchronousModeErrorFound = true;
                    }
                }

            }

            if (!synchronousModeErrorFound)
            {
                for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
                    var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
                    var soci = (currentSOC).replace(/[^0-9]/g,'')
                    if((inst.enabledSOCs).includes(currentSOC)){
                        var socTriggers = [];
                        var socTriggerOwners = [];
                        var socSampleWindows = [];
                        for (var instance_index in inst.$module.$instances)
                        {
                            var instance_obj = inst.$module.$instances[instance_index];
                            var highPri = instance_obj.socHighPriorityMode;
                            var number_highpri_socs = device_driverlib_peripheral.ADC_PriorityMode.findIndex(x => x.name == highPri);

                            if (soci < number_highpri_socs)
                            {
                                socTriggers.push(instance_obj["soc" + soci.toString() + "Trigger"])
                                socTriggerOwners.push("soc" + soci.toString() + "Trigger");
                                if (inst["soc" + soci.toString() + "UseCalculatedSampleTime"] &&
                                inst["soc" + soci.toString() + "UseSampleTimeCalculator"])
                                {
                                    socSampleWindows.push(instance_obj["soc" + soci.toString() + "SampleWindowCalculated"]);
                                }
                                else{
                                    socSampleWindows.push(instance_obj["soc" + soci.toString() + "SampleWindow"]);
                                }
                            }
                            else
                            {
                                if (instance_obj.enableBurstMode)
                                {
                                    socTriggers.push(instance_obj["burstTrigger"])
                                    socTriggerOwners.push("burstTrigger");
                                    if (inst["soc" + soci.toString() + "UseCalculatedSampleTime"] &&
                                    inst["soc" + soci.toString() + "UseSampleTimeCalculator"])
                                    {
                                        socSampleWindows.push(instance_obj["soc" + soci.toString() + "SampleWindowCalculated"]);
                                    }
                                    else{
                                        socSampleWindows.push(instance_obj["soc" + soci.toString() + "SampleWindow"]);
                                    }
                                }
                                else
                                {
                                    socTriggers.push(instance_obj["soc" + soci.toString() + "Trigger"])
                                    socTriggerOwners.push("soc" + soci.toString() + "Trigger");
                                    if (inst["soc" + soci.toString() + "UseCalculatedSampleTime"] &&
                                    inst["soc" + soci.toString() + "UseSampleTimeCalculator"])
                                    {
                                        socSampleWindows.push(instance_obj["soc" + soci.toString() + "SampleWindowCalculated"]);
                                    }
                                    else{
                                        socSampleWindows.push(instance_obj["soc" + soci.toString() + "SampleWindow"]);
                                    }
                                }
                            }
                        }
                        var maxWindow = Math.max.apply(null, socSampleWindows);
                        for (var instance_index in inst.$module.$instances)
                        {
                            var instance_obj = inst.$module.$instances[instance_index];
                            for (var instance_indexCompare in inst.$module.$instances)
                            {
                                var instance_objCompare = inst.$module.$instances[instance_index];
                                if (socTriggers[instance_index] != socTriggers[instance_indexCompare])
                                {
                                    validation.logError(
                                        "In synchronous mode the triggers for the same SOC numbers must match across different ADCs! " + instance_objCompare.$name + " and " + instance_obj.$name +
                                        " do not match!",
                                        instance_obj, socTriggerOwners[instance_index]);
                                }
                                if (socSampleWindows[instance_index] != socSampleWindows[instance_indexCompare])
                                {
                                    if (inst["soc" + soci.toString() + "UseCalculatedSampleTime"] &&
                                    inst["soc" + soci.toString() + "UseSampleTimeCalculator"])
                                    {
                                        validation.logError(
                                            "In synchronous mode the sampling window of the same SOC numbers must match across different ADCs! " + instance_objCompare.$name + " and " + instance_obj.$name +
                                            " do not match!" + " The maximum value found is " + maxWindow.toString(),
                                            instance_obj, "soc" + soci.toString() + "SampleWindowCalculated");
                                    }
                                    else{
                                        validation.logError(
                                            "In synchronous mode the sampling window of the same SOC numbers must match across different ADCs! " + instance_objCompare.$name + " and " + instance_obj.$name +
                                            " do not match!" + " The maximum value found is " + maxWindow.toString(),
                                            instance_obj, "soc" + soci.toString() + "SampleWindow");
                                    }
                                    
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    //
    // End Synchronous Mode
    //

    //
    // Copy Check Start
    //
    // var validCopyName = false;
    // if (inst.copyUse)
    // {
    //     for (var instance_index in inst.$module.$instances)
    //     {
    //         var instance_obj = inst.$module.$instances[instance_index];
    //         if (instance_obj != inst) {
    //             if (instance_obj.$name == inst.copyFrom)
    //             {
    //                 validCopyName = true;
    //             }
    //         }
    //     }

    //     if (!validCopyName)
    //     {
    //         validation.logError(
    //             "The copy from name is not a valid ADC name",
    //             inst, "copyFrom");
    //     }
    // }

    //
    // Copy Check End
    //

    var usedADCInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedADCInsts.push(instance_obj.adcBase);
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
                usedADCInsts.push(instance_obj.adcBase);
            }
        }
    }
    var duplicatesResult = Common.findDuplicates(usedADCInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The ADC Instance used. Duplicates: " + allDuplicates,
            inst, "adcBase");
    }

    //
    //Check Clock Prescaler
    //
    var prescalefactor = inst["adcClockPrescaler"].replace("ADC_CLK_DIV_","").split("_")[0]
    if (["F2837xD", "F2837xS", "F2838x"].includes(Common.getDeviceName()))
    {
        if ( prescalefactor < 4)
        {
            validation.logWarning(
                "The maximum frequency of ADC for this device is 50MHz. ADC Clock Prescaler should be selected accordingly.",
                inst, "adcClockPrescaler");
        }
    }
    if (["F28P55x"].includes(Common.getDeviceName()))
    {
        if ( prescalefactor < 2)
        {
            validation.logWarning(
                "The maximum frequency of ADC for this device is 75MHz. ADC Clock Prescaler should be selected accordingly.",
                inst, "adcClockPrescaler");
        }
    }
    if (["F28P65x"].includes(Common.getDeviceName()))
    {
        if (( prescalefactor < 4) & (inst["adcClockPrescaler"]!="ADC_CLK_DIV_3_5"))
        {
            validation.logWarning(
                "The maximum frequency of ADC for this device is 60MHz. ADC Clock Prescaler should be selected accordingly.",
                inst, "adcClockPrescaler");
        }
    }
    if (["F28002x", "F28004x"].includes(Common.getDeviceName()))
    {
        if ( prescalefactor < 2)
        {
            validation.logWarning(
                "The maximum frequency of ADC for this device is 50MHz. ADC Clock Prescaler should be selected accordingly.",
                inst, "adcClockPrescaler");
        }
    }
    if (["F2807x", "F280013x","F280015x"].includes(Common.getDeviceName()))
    {
        if ( prescalefactor <= 2)
        {
            validation.logWarning(
                "The maximum frequency of ADC for this device is 50MHz. ADC Clock Prescaler should be selected accordingly.",
                inst, "adcClockPrescaler");
        }
    }
    if (["F28003x"].includes(Common.getDeviceName()))
    {
        if ( prescalefactor < 2)
        {
            validation.logWarning(
                "The maximum frequency of ADC for this device is 60MHz. ADC Clock Prescaler should be selected accordingly.",
                inst, "adcClockPrescaler");
        }
    }

    //
    // Differential Mode/Resolution
    //
    if (["F2837xD", "F2837xS", "F2838x"].includes(Common.getDeviceName()))
    {
        if (inst["adcResolutionMode"] == "ADC_RESOLUTION_12BIT")
        {
            if (inst["adcSignalMode"] == "ADC_MODE_SINGLE_ENDED")
            {
                // Acceptable 12bit resolution with single ended mode
            }
            else
            {
                validation.logError(
                    "The ADC 12-bit resolution is not supported with ADC differential mode",
                    inst, "adcSignalMode");
            }
        }
        else
        {
            if (["F2837xD", "F2837xS"].includes(Common.getDeviceName()))
            {
                if (inst["adcSignalMode"] == "ADC_MODE_SINGLE_ENDED")
                {
                    validation.logError(
                        "The ADC 16-bit resolution is not supported with ADC single ended mode",
                        inst, "adcSignalMode");
                }
                else
                {
                    // Acceptable 16bit resolution with differential mode
                }
            }
        }

        for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
            var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
            var soci = (currentSOC).replace(/[^0-9]/g,'')
            if((inst.enabledSOCs).includes(currentSOC)){
                var channel = inst["soc" + soci.toString() + "Channel"]
                var channel_numbers = channel.replace("ADC_CH_", "")
                var channels = channel_numbers.split("_")
                if (inst["adcSignalMode"] == "ADC_MODE_SINGLE_ENDED")
                {
                    if (channels.length > 1)
                    {
                        validation.logError(
                            "SOC" + soci.toString() + " cannot use a differential input channel" +
                            " when the ADC module is in single ended mode",
                            inst, "soc" + soci.toString() + "Channel");
                    }
                }
                else
                {
                    if (channels.length < 2)
                    {
                        validation.logError(
                            "SOC" + soci.toString() + " cannot use a single-ended input channel" +
                            " when the ADC module is in differential mode",
                            inst, "soc" + soci.toString() + "Channel");
                    }
                }
            }
        }
    }

    //
    // Burst Trigger warnings
    //

    var highPri = inst.socHighPriorityMode;
    var number_highpri_socs = device_driverlib_peripheral.ADC_PriorityMode.findIndex(x => x.name == highPri);
    for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
        var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
        var soci = (currentSOC).replace(/[^0-9]/g,'')
        if((inst.enabledSOCs).includes(currentSOC)){
            if (soci < number_highpri_socs)
            {

            }
            else
            {
                if (inst.enableBurstMode)
                {
                    if (inst.burstTrigger != inst["soc" + soci.toString() + "Trigger"])
                    {
                        validation.logWarning(
                            "SOC" + soci.toString() + " is configured for Round Robin. With burst mode enabled, the " +
                            " burst mode trigger will override the selected trigger for this SOC",
                            inst, "soc" + soci.toString() + "Trigger");
                    }
                }
            }
        }
    }

    //
    // SOC Name
    //
    var validSocNames = []
    for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
        var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
        var soci = (currentSOC).replace(/[^0-9]/g,'')
        if((inst.enabledSOCs).includes(currentSOC))
        {
            var soc_name = inst["soc" + soci.toString() + "Name"].replace(/\s/g, '')
            if (soc_name != "")
            {
                validSocNames.push(soc_name)
            }
        }
    }

    var duplicateSocNames = Common.findDuplicates(validSocNames)

    if (duplicateSocNames.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateSocNamesIndex in duplicateSocNames.duplicates)
        {
            var duplicateSocName = duplicateSocNames.duplicates[duplicateSocNamesIndex];

            for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
                var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
                var soci = (currentSOC).replace(/[^0-9]/g,'')
                if((inst.enabledSOCs).includes(currentSOC))
                {
                    var soc_name = inst["soc" + soci.toString() + "Name"].replace(/\s/g, '')
                    if (soc_name == duplicateSocName)
                    {
                        //
                        // Duplicate SOC name
                        //
                        validation.logError(
                            "SOC" + soci.toString() + " application name must be unique.",
                            inst, "soc" + soci.toString() + "Name");

                    }
                }
            }
        }
    }

  //
  // repeater module
  //

  if (["F28P65x", "F28P55x"].includes(Common.getDeviceName()))
        {
            for(var rptrIndex in device_driverlib_peripheral.ADC_RepInstance){ 
                var currentRPTR = device_driverlib_peripheral.ADC_RepInstance[rptrIndex].name
                let rptri = (currentRPTR).replace(/[^0-9]/g,'')
                if (inst["repeater" + rptri.toString()+ " Count"] <= 0)
                {
                    validation.logError(
                        "Number of repeater trigger counts must be larger than 0",
                        inst, "repeater" + rptri.toString()+ " Count");
                }
                if (!Number.isInteger(inst["repeater" + rptri.toString()+ " Count"]))
                {
                    validation.logError(
                        "Trigger count must be an integer value.",
                        inst, "repeater" + rptri.toString()+ " Count");
                } 
                if (inst["repeater"  + rptri.toString()+ " Phase"] < 0)
                {
                    validation.logError(
                        "Phase delay  must be larger than 0",
                        inst, "repeater"  + rptri.toString()+ " Phase");
                }  
                if (inst["repeater" + rptri.toString()+ " Spread"] < 0)
                {
                    validation.logError(
                        "Spread value must be larger than 0",
                        inst,"repeater" + rptri.toString()+ " Spread");
                }  
            }
            //
            //Loginfo for Oversampling Interrupt OSINT
            //
            for(var intIndex in device_driverlib_peripheral.ADC_IntNumber){ 
                var currentINT = device_driverlib_peripheral.ADC_IntNumber[intIndex].name
                var inti = (currentINT).replace(/[^0-9]/g,'')
                for(var ppbIndex in device_driverlib_peripheral.ADC_PPBNumber){
                    var currentPPB = device_driverlib_peripheral.ADC_PPBNumber[ppbIndex].name
                    var ppbi = (currentPPB).replace(/[^0-9]/g,'')
                    if (inst.enabledPPBs.includes(currentPPB) &&
                        inst.enabledInts.includes(currentINT) &&
                        inst["interrupt" + inti.toString() + "SOCSource"] =="ADC_INT_TRIGGER_OSINT" + ppbi.toString()) {
                        {
                            validation.logInfo(
                            "To generate an oversampling interrupt (OSINT), you need to configure OSINT source via" +
                            ": " + system.getReference(inst,"ppb" + ppbi.toString() + "SelectOSINTSource"),
                            inst,"interrupt" + inti.toString() + "SOCSource");
                        }
                    }
                }
            }
            if(inst.enableEXTMUX)
            {
                for (var xbari=0; xbari< inst["adcNumExtPins"]; xbari++){
                    if(inst["adcextchan"+xbari])
                    {
                        validation.logInfo(
                                "You can change GPIO selection for this pin via" +  ": " + system.getReference(inst["adcextchan"+xbari].outputxbar,"outputxbarPin"),
                                inst, "extchannel"+ xbari+" pin");
                    }
                }
            }  
        } 

    for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
        var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
        var soci = (currentSOC).replace(/[^0-9]/g,'')
        if((inst.enabledSOCs).includes(currentSOC))
        {
            //
            //Information for setting up the repeater modules if repeater mode is selected for trigger
            //
            if (["F28P65x", "F28P55x"].includes(Common.getDeviceName())) 
            {
                if(((inst["soc" + soci.toString() + "Triggermode"]) == "repeatermode")&& 
                ((inst["soc" + soci.toString() + "Trigger"]) == ("ADC_TRIGGER_REPEATER1")))
                {
                    validation.logInfo(
                        "Repeater Module 1 should be configured for SOC" + soci.toString()+ ": " + system.getReference(inst,"repeater1 Mode"),
                        inst, "soc" + soci.toString() + "Triggermode");
                }
                if(((inst["soc" + soci.toString() + "Triggermode"]) == "repeatermode")&&
                ((inst["soc" + soci.toString() + "Trigger"]) == ("ADC_TRIGGER_REPEATER2")))
                {
                    validation.logInfo(
                        "Repeater Module 2 should be configured for SOC" + soci.toString()+ ": " + system.getReference(inst,"repeater2 Mode"),
                        inst, "soc" + soci.toString() + "Triggermode");
                }
                // validation.logInfo(
                //     "To use the external channel, you must first enable external MUX for this SOC via" + soci.toString()+ ": " + system.getReference(inst,"enableEXTMUX"),
                //     inst, "soc" + soci.toString() + "ExtChannel");  
            }
            if (inst["soc" + soci.toString() + "UseCalculatedSampleTime"] &&
            inst["soc" + soci.toString() + "UseSampleTimeCalculator"])
            {
                if (["F2837xD", "F2837xS" ,"F2838x","F28P65x"].includes(Common.getDeviceName()))
                {
                    if (inst["adcResolutionMode"] == "ADC_RESOLUTION_16BIT")
                    {
                        if (inst["soc" + soci.toString() + "SampleWindowCalculated"] <= 63 && 
                        inst["soc" + soci.toString() + "SampleWindowCalculated"] > 0)
                        {
                            validation.logWarning(
                                "SOC" + soci.toString() + " sample window must be at least 64",
                                inst, "soc" + soci.toString() + "SampleWindowCalculated");
                        }
                    }
                    else
                    {
                        if (inst["soc" + soci.toString() + "SampleWindowCalculated"] <= 14 && 
                        inst["soc" + soci.toString() + "SampleWindowCalculated"] > 0)
                        {
                            validation.logWarning(
                                "SOC" + soci.toString() + " sample window must be at least 15",
                                inst, "soc" + soci.toString() + "SampleWindowCalculated");
                        }
                    }
                }
                else if (["F28003x", "F280013x" ,"F280015x","F2807x"].includes(Common.getDeviceName()))
                {
                    if (inst["soc" + soci.toString() + "SampleWindowCalculated"] <= 8 && 
                    inst["soc" + soci.toString() + "SampleWindowCalculated"] > 0)
                    {
                        validation.logWarning(
                            "SOC" + soci.toString() + " sample window must be at least 9",
                            inst, "soc" + soci.toString() + "SampleWindowCalculated");
                    }
                }
                else if(["F28P55x"].includes(Common.getDeviceName()))
                {
                    if (inst["soc" + soci.toString() + "SampleWindowCalculated"] <= 9 &&
                    inst["soc" + soci.toString() + "SampleWindowCalculated"] > 0)
                    {
                        validation.logWarning(
                            "SOC" + soci.toString() + " sample window must be at least 10",
                            inst, "soc" + soci.toString() + "SampleWindowCalculated");                        
                    }
                }
                else
                {
                    if (inst["soc" + soci.toString() + "SampleWindowCalculated"] <= 7 && 
                    inst["soc" + soci.toString() + "SampleWindowCalculated"] > 0)
                    {
                        validation.logWarning(
                            "SOC" + soci.toString() + " sample window must be at least 8",
                            inst, "soc" + soci.toString() + "SampleWindowCalculated");
                    }
                }

                if (inst["soc" + soci.toString() + "SampleWindowCalculated"] <= 0 ||
                    inst["soc" + soci.toString() + "SampleWindowCalculated"] > 512)
                {
                    validation.logError(
                        "SOC" + soci.toString() + " sample window must be between 1 and 512",
                        inst, "soc" + soci.toString() + "SampleWindowCalculated");
                }
                if (!Number.isInteger(inst["soc" + soci.toString() + "SampleWindowCalculated"]))
                {
                    validation.logError(
                        "SOC" + soci.toString() + " sample window must be an integer value.",
                        inst, "soc" + soci.toString() + "SampleWindowCalculated");
                }
            }
            else{
                if (["F2837xD", "F2837xS" ,"F2838x","F28P65x"].includes(Common.getDeviceName()))
                {
                    if (inst["adcResolutionMode"] == "ADC_RESOLUTION_16BIT")
                    {
                        if (inst["soc" + soci.toString() + "SampleWindow"] <= 63 && 
                        inst["soc" + soci.toString() + "SampleWindow"] > 0)
                        {
                            validation.logWarning(
                                "SOC" + soci.toString() + " sample window must be at least 64",
                                inst, "soc" + soci.toString() + "SampleWindow");
                        }
                    }
                    else
                    {
                        if (inst["soc" + soci.toString() + "SampleWindow"] <= 14 && 
                        inst["soc" + soci.toString() + "SampleWindow"] > 0)
                        {
                            validation.logWarning(
                                "SOC" + soci.toString() + " sample window must be at least 15",
                                inst, "soc" + soci.toString() + "SampleWindow");
                        }
                    }
                }
                else if (["F28003x", "F280013x" ,"F280015x","F2807x"].includes(Common.getDeviceName()))
                {
                    if (inst["soc" + soci.toString() + "SampleWindow"] <= 8 && 
                    inst["soc" + soci.toString() + "SampleWindow"] > 0)
                    {
                        validation.logWarning(
                            "SOC" + soci.toString() + " sample window must be at least 9",
                            inst, "soc" + soci.toString() + "SampleWindow");
                    }
                }
                else if(["F28P55x"].includes(Common.getDeviceName()))
                {
                    if (inst["soc" + soci.toString() + "SampleWindow"] <= 9 &&
                    inst["soc" + soci.toString() + "SampleWindow"] > 0)
                    {
                        validation.logWarning(
                            "SOC" + soci.toString() + " sample window must be at least 10",
                            inst, "soc" + soci.toString() + "SampleWindow");                        
                    }
                }
                else
                {
                    if (inst["soc" + soci.toString() + "SampleWindow"] <= 7 && 
                    inst["soc" + soci.toString() + "SampleWindow"] > 0)
                    {
                        validation.logWarning(
                            "SOC" + soci.toString() + " sample window must be at least 8",
                            inst, "soc" + soci.toString() + "SampleWindow");
                    }
                }
                if (inst["soc" + soci.toString() + "SampleWindow"] <= 0 ||
                    inst["soc" + soci.toString() + "SampleWindow"] > 512)
                {
                    validation.logError(
                        "SOC" + soci.toString() + " sample window must be between 1 and 512",
                        inst, "soc" + soci.toString() + "SampleWindow");
                } 
                if (!Number.isInteger(inst["soc" + soci.toString() + "SampleWindow"]))
                {
                    validation.logError(
                        "SOC" + soci.toString() + " sample window must be an integer value.",
                        inst, "soc" + soci.toString() + "SampleWindow");
                }
            }
            if (inst["soc" + soci.toString() + "UseSampleTimeCalculator"])
            {
                if (inst["soc" + soci.toString() + "SettlingError"] <= 0)
                {
                    validation.logError(
                        "SOC" + soci.toString() + " settling time must be larger than 0",
                        inst, "soc" + soci.toString() + "SettlingError");
                }
                if (inst["soc" + soci.toString() + "InputResistance"] < 0)
                {
                    validation.logError(
                        "SOC" + soci.toString() + " input resistance must be equal or larger than 0",
                        inst, "soc" + soci.toString() + "InputResistance");
                }
                if (inst["soc" + soci.toString() + "InputCapacitance"] < 0)
                {
                    validation.logError(
                        "SOC" + soci.toString() + " input capacitance must be equal or larger than 0",
                        inst, "soc" + soci.toString() + "InputCapacitance");
                }
                if (inst["soc" + soci.toString() + "ADCParasiticCapacitance"] == ESTIMATED_CP)
                {
                    validation.logWarning(
                        "SOC" + soci.toString() + " Cp is estimated since the information for this input is not available",
                        inst, "soc" + soci.toString() + "ADCParasiticCapacitance");
                }
            }
            // TODO: delete this comment later, using as marker for new validation (switched to warning)
            // -- need to determine is WARNING or ERROR
            if(inst["soc" + soci.toString() + "DevicePinName"] == Pinmux.NO_DEVICE_PIN_FOUND){
                validation.logWarning(
                    "SOC" + soci.toString() + " Channel selected has no device pin found.",
                    inst, "soc" + soci.toString() + "Channel");
            }
            // Error for trigger of Repeater modules
            if (["F28P65x", "F28P55x"].includes(Common.getDeviceName()))
            {
                if((inst["soc" + soci.toString() + "Triggermode"]) == "singlemode") 
                {
                    if ((((inst["soc" + soci.toString() + "Trigger"])== "ADC_TRIGGER_REPEATER1") || ((inst["soc" + soci.toString() + "Trigger"])== "ADC_TRIGGER_REPEATER2"))) 
                    validation.logError(
                        "Repeater Module 1 and Repeater Module 2 can not be selected as Tigger source for SOC" + soci.toString()+ ". If you want to use repeater modules, you need to select Use Repeater Trigger in Trigger mode",
                        inst, "soc" + soci.toString() + "Trigger");
                }
                if((inst["soc" + soci.toString() + "Triggermode"]) == "repeatermode") 
                {
                    if ((((inst["soc" + soci.toString() + "Trigger"])!= "ADC_TRIGGER_REPEATER1") && ((inst["soc" + soci.toString() + "Trigger"])!= "ADC_TRIGGER_REPEATER2"))) 
                    validation.logError(
                        "Repeater Module 1 or Repeater Module 2 should be selected as Tigger source for SOC"+ soci.toString(),
                        inst, "soc" + soci.toString() + "Trigger");
                } 
            }    
        }     
    }

    //
    // Cycle Offset
    //

    if (!["F2807x", "F2837xS", "F2837xD"].includes(Common.getDeviceName()))
    {
        if (inst["interruptPulseMode"] == "ADC_PULSE_END_OF_ACQ_WIN")
        {
            if (inst["interruptCycleOffset"] < 0 || inst["interruptCycleOffset"] > 0xFFFF)
            {
                validation.logError(
                    "Interupt cycle offset must be between 0 and 0xFFFF",
                    inst, "interruptCycleOffset");
            }
            if (!Number.isInteger(inst["interruptCycleOffset"]))
            {
                validation.logError(
                    "Interupt cycle offset must be an integer",
                    inst, "interruptCycleOffset");
            }
        }
    }

    //
    // PPB Check
    //

    for(var ppbIndex in device_driverlib_peripheral.ADC_PPBNumber)
    {
        var currentPPB = device_driverlib_peripheral.ADC_PPBNumber[ppbIndex].name
        var ppbi = (currentPPB).replace(/[^0-9]/g,'')
        if((inst.enabledPPBs).includes(currentPPB)){
            if (inst["ppb" + ppbi.toString() + "CalibrationOffset"] < -512 ||
                inst["ppb" + ppbi.toString() + "CalibrationOffset"] > 511)
            {
                validation.logError(
                    "The calibration offset value must be between -512 and 511",
                    inst,"ppb" + ppbi.toString() +  "CalibrationOffset");
            }
            if (!Number.isInteger(inst["ppb" + ppbi.toString() + "CalibrationOffset"]))
            {
                validation.logError(
                    "The calibration offset value must be an integer",
                    inst,"ppb" + ppbi.toString() +  "CalibrationOffset");
            }

            if (inst["ppb" + ppbi.toString() + "ReferenceOffset"] < 0 ||
                inst["ppb" + ppbi.toString() + "CalibrationOffset"] > 0xFFFF)
            {
                validation.logError(
                    "The reference offset value must be between 0 and 0xFFFF",
                    inst,"ppb" + ppbi.toString() +  "CalibrationOffset");
            }
            if (!Number.isInteger(inst["ppb" + ppbi.toString() + "ReferenceOffset"]))
            {
                validation.logError(
                    "The reference offset value must be an integer",
                    inst,"ppb" + ppbi.toString() +  "CalibrationOffset");
            }

            if (!["F28P65X", "F28P55x"].includes(Common.getDeviceName()))
            {
                if (inst["ppb" + ppbi.toString() + "HighTripLimit"] > 65535 ||
                    inst["ppb" + ppbi.toString() + "HighTripLimit"] < -65536)
                {
                    validation.logError(
                        "The high trip limit value must be between 65535 and -65536",
                        inst,"ppb" + ppbi.toString() +  "HighTripLimit");
                }

                if (inst["ppb" + ppbi.toString() + "LowTripLimit"] > 65535 ||
                inst["ppb" + ppbi.toString() + "LowTripLimit"] < -65536)
                {
                    validation.logError(
                        "The low trip limit value must be between 65535 and -65536",
                        inst,"ppb" + ppbi.toString() +  "LowTripLimit");
                }
            }
            else
            {
                if (inst["ppb" + ppbi.toString() + "HighTripLimit"] > 8388607 ||
                    inst["ppb" + ppbi.toString() + "HighTripLimit"] < -8388607)
                {
                    validation.logError(
                        "The high trip limit value must be between 8388607 and -8388607",
                        inst,"ppb" + ppbi.toString() +  "HighTripLimit");
                }

                if (inst["ppb" + ppbi.toString() + "LowTripLimit"] > 8388607 ||
                inst["ppb" + ppbi.toString() + "LowTripLimit"] < -8388607)
                {
                    validation.logError(
                        "The low trip limit value must be between 8388607 and -8388607",
                        inst,"ppb" + ppbi.toString() +  "LowTripLimit");
                }                
            }

            if (!Number.isInteger(inst["ppb" + ppbi.toString() + "HighTripLimit"]))
            {
                validation.logError(
                    "The high trip limit value must be an integer",
                    inst,"ppb" + ppbi.toString() +  "HighTripLimit");
            }

            if (!Number.isInteger(inst["ppb" + ppbi.toString() + "LowTripLimit"]))
            {
                validation.logError(
                    "The low trip limit value must be an integer",
                    inst,"ppb" + ppbi.toString() +  "LowTripLimit");
            }
        }
    }

    //
    // Check for Pin Usage in analog
    //
    if (Common.isContextCPU1()) {
        if (Common.peripheralCount("ANALOG") > 0)
        {
            for(var socIndex in device_driverlib_peripheral.ADC_SOCNumber){ 
                var currentSOC = device_driverlib_peripheral.ADC_SOCNumber[socIndex].name
                var soci = (currentSOC).replace(/[^0-9]/g,'')
                if((inst.enabledSOCs).includes(currentSOC)){
                    var pinInfo = Pinmux.calculateADCPinInfo(inst,soci);
                    var pinSelectedArray = pinInfo.adcPinInfosArray;
                    var channelArray = pinInfo.adcChannelArray;
                    var devicePinNameInfo = inst["soc" + soci.toString() + "DevicePinName"]
                    if (Common.isMultiCoreSysConfig()){
                        let analog_inst = system.contexts.CPU1.system.modules["/driverlib/analog.js"];
                        var selectedInterfaces = Pinmux.getPeripheralUseCaseInterfaces(analog_inst,"ANALOG",analog_inst.useCase);
                        var allInterfaces = Pinmux.getPeripheralUseCaseInterfaces(analog_inst, "ANALOG", "ALL");
                    }
                    else{
                        var selectedInterfaces = Pinmux.getPeripheralUseCaseInterfaces(inst.analog,"ANALOG",inst.analog.useCase);
                        var allInterfaces = Pinmux.getPeripheralUseCaseInterfaces(inst.analog, "ANALOG", "ALL");
                    }   

                    var allPinsMustBeConfigured = true;
    
                    if ((channelArray.includes("B5") || channelArray.includes("B11")) && Common.getDevicePart() == "F28003x_100PZ")
                    {
                        validation.logInfo(
                            "For 100PZ package on F28003x, only one of the pins can be used and setup for this channel. For example if both 'Bx' and " +
                            " 'Bx, GPIOy' are selected in the ANALOG PinMux, only the 'Bx, GPIOy' pin will be connected to the ADC module.",
                            inst,"soc" + soci.toString() + "DevicePinName");
                        allPinsMustBeConfigured = false;
                    }
    
                    var configurationStatus = [];
                    var finalFail = true;
                    
                    for (var pinSelected of pinSelectedArray)
                    {
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
                                    inst,"soc" + soci.toString() + "DevicePinName");
                            }
                        }
                    }
                    else
                    {
                        if (finalFail)
                        {
                            validation.logError(
                                "At least one of the following ANALOG PinMux pins must be selected.",
                                inst,"soc" + soci.toString() + "DevicePinName");
    
                            for (var cstat of configurationStatus)
                            {
                                if (cstat.fail)
                                {
                                    validation.logError(
                                        "The pin " + cstat.pinSelected + " is not selected in the ANALOG PinMux module." +
                                        " Add this pin to the 'Pins Used' or change the 'Use Case'",
                                        inst,"soc" + soci.toString() + "DevicePinName");
                                }
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
function filterHardware(component) {
  return Common.typeMatches(component.type, ["ADC"]);
}

function modules(inst){
    if (inst) {
        return [
            {
                name: "adcPullInTemplateDot",
                moduleName: "/driverlib/adc/templates/adc.dot.dynamic.js",
            }
        ];
    }
    return [];
}

var moduleStaticModules = undefined;
var sharedModuleInstances = undefined;
if (!["F2807x", "F2837xD", "F2837xS", "F2838x"].includes(Common.getDeviceName())) {
    if (Common.isContextCPU1()) {
        if (Common.peripheralCount("ANALOG") > 0) {
            moduleStaticModules = Common.autoForceMultiple([
                {
                    name: "asysctl",
                    moduleName: "/driverlib/asysctl.js",
                    hidden: false,
                },
            ]
            );
            sharedModuleInstances = function () {
                return [
                    {
                        name: "analog",
                        displayName: "Analog PinMux",
                        moduleName: "/driverlib/analog.js",
                    },
                ];
            };
        } 
        else {
            moduleStaticModules = Common.autoForceMultiple([
                {
                    name: "asysctl",
                    moduleName: "/driverlib/asysctl.js",
                    hidden: false,
                },
            ]
            );
        }  
    }
}

var adcModule = {
    peripheralName: "ADC",
    displayName: "ADC",
    maxInstances: maxInstances,
    defaultInstanceName: "myADC",
    description: "Analog Digital Converter",
    longDescription: (Common.getCollateralFindabilityList("ADC")),
    filterHardware : filterHardware,
    config: config,
    moduleInstances: (inst) => {
        
        var intReturn =  []

        if (Common.isContextCPU1() &&
        ["F28P65x", "F28P55x"].includes(Common.getDeviceName())) {
            if (inst.enableEXTMUX) {
                for (var xbari = 0; xbari < inst["adcNumExtPins"]; xbari++) {
                    intReturn.push({
                        name: "adcextchan" + xbari,
                        displayName: "External Channel " + xbari + " (OUTPUTXBAR)",
                        moduleName: "/driverlib/outputxbar.js",
                        collapsed: true,
                        group: "GROUP_ADC_EXT_CHAN",
                        args: {
                        $name: inst.$name + "_ADCEXT" + xbari,
                        useSourceSelect: true,
                        },
                        requiredArgs: {
                            useSourceSelect: true,
                            sourceSignals: [inst.adcBase.replace("_BASE", "_EXTMUXSEL") + xbari,],
                        },
                    }
                    );
                }
            }
        }

        if (inst.useInterrupts && ((inst.registerInterrupts).includes("1")))
        {
            intReturn.push ({
                name: "adcInt1",
                displayName: inst.adcBase.replace("_BASE", "")+" Interrupt 1",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                group: "GROUP_REGISTER_INT",
                args: {
            		$name : inst.$name + "1_INT",
                    int : "INT_" + inst.$name+"_1",
                    pinmuxPeripheralModule :"",
                    driverlibInt: "INT_" + inst.adcBase.replace("_BASE", "") + "1"
                }
            }
            )
        }
        if (inst.useInterrupts && ((inst.registerInterrupts).includes("2")))
        {
            intReturn.push({
                name: "adcInt2",
                displayName: inst.adcBase.replace("_BASE", "")+" Interrupt 2",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                group: "GROUP_REGISTER_INT",
                args: {
            		$name : inst.$name + "2_INT",
                    int : "INT_" + inst.$name+"_2",
                    pinmuxPeripheralModule :"",
                    driverlibInt: "INT_" + inst.adcBase.replace("_BASE", "") + "2"
                }
            }
            )
        }
        if (inst.useInterrupts && ((inst.registerInterrupts).includes("3")))
        {
            intReturn.push({
                name: "adcInt3",
                displayName: inst.adcBase.replace("_BASE", "")+" Interrupt 3",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                group: "GROUP_REGISTER_INT",
                args: {
            		$name : inst.$name + "3_INT",
                    int : "INT_" + inst.$name+"_3",
                    pinmuxPeripheralModule :"",
                    driverlibInt: "INT_" + inst.adcBase.replace("_BASE", "") + "3"
                }
            }
            )
        }
        if (inst.useInterrupts && ((inst.registerInterrupts).includes("4")))
        {
            intReturn.push({
                name: "adcInt4",
                displayName: inst.adcBase.replace("_BASE", "")+" Interrupt 4",
                moduleName: "/driverlib/interrupt.js",
                group: "GROUP_REGISTER_INT",
                collapsed: true,
                args: {
            		$name : inst.$name + "4_INT",
                    int : "INT_" + inst.$name+"_4",
                    pinmuxPeripheralModule :"",
                    driverlibInt: "INT_" + inst.adcBase.replace("_BASE", "") + "4"
                }
            }
            )
        }
        if (inst.useInterrupts && ((inst.registerInterrupts).includes("5")))
        {
            intReturn.push({
                name: "adcIntEvent",
                displayName: inst.adcBase.replace("_BASE", "")+" Event Interrupt",
                moduleName: "/driverlib/interrupt.js",
                group: "GROUP_REGISTER_INT",
                collapsed: true,
                args: {
            		$name : inst.$name + "_EVT_INT",
                    int : "INT_" + inst.$name+"_EVT",
                    pinmuxPeripheralModule :"",
                    driverlibInt: "INT_" + inst.adcBase.replace("_BASE", "") + "_EVT"
                }
            }
            )
        }
        return intReturn;
    },
    templates: {
        boardc : "/driverlib/adc/adc.board.c.xdt",
        boardh : "/driverlib/adc/adc.board.h.xdt"
    },
    moduleStatic: {
        name: "adcGlobal",
        displayName: "ADC Global",
        config: globalConfig,
        modules: moduleStaticModules,
        validate : onValidateStatic
    },
    modules: modules,
    sharedModuleInstances: sharedModuleInstances,
    validate    : onValidate,
};


exports = adcModule;