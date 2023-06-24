let Common   = system.getScript("/driverlib/Common.js");

let InternalConnections = system.getScript("/driverlib/adc/adc_internalConnections.js")

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_adc.js");

function onChangeSafetyCheckerEVNTs(inst, ui){
    for(var sftyIndex in device_driverlib_peripheral.ADC_SafetyCheckEvent)
    {
        var currentSFTY = device_driverlib_peripheral.ADC_SafetyCheckEvent[sftyIndex].name
        var sftyi = (currentSFTY).replace(/[^0-9]/g,'')
        var sftyEVNTConfigs = 
            [
                "chkEvent" + sftyi.toString() + "Checker",
                "chk" + sftyi.toString() + "CheckResult",
            ]

        if (ui)
        {
            for (var sftyConfig of sftyEVNTConfigs)
            {
                if(inst["enableEvent"].includes(currentSFTY))
                {
                    ui[sftyConfig].hidden = false;
                }
                else
                {
                    ui[sftyConfig].hidden = true;
                }
            }  
        }
    }
}
function onChangeSafetyCheckerINTs(inst, ui) {  
    if (ui) {
        if((inst["enableInterrupt"])=="safetyCheckerEventInt") {
            ui["eventInterruptChecker"].hidden = false;
            ui["eventInterruptResult"].hidden = false;
        }
        else {
            ui["eventInterruptChecker"].hidden = true;
            ui["eventInterruptResult"].hidden = true;
        }
    }
}

let config = [
    {
        name: "GROUP_ADC_CHECKER_TILES",
        config: [],
    }
];
var sftyINT_configs =[];
sftyINT_configs = sftyINT_configs.concat([
    {
        name            : "enableInterrupt",
        displayName     : "Enable Interrupt",
        description     : 'Each ADC result safety checker tile can generate an interrupt signal from out-of-tolerance (OOT) flag and result overflow flags OVF1 and OVF2',
        longDescription : 'Each ADC result safety checker tile generates an interrupt pulse when an enabled out-of-tolerance (OOT) or overflow OVF1 or OVF2 event occurs. No further interrupt pulses will be generated until the interrupt flag is cleared.',
        hidden          : false,
        minSelections   : 0,
        default         : [],
        options         : [{name: "safetyCheckerEventInt", displayName: "Interrupt Number 1"},],
        onChange        : onChangeSafetyCheckerINTs,
  
    },
    {
        name            : "eventInterruptChecker",
        displayName     : "Select checker for interrupt",
        description     : 'Each ADC result safety checker tile can generate an interrupt signal from out-of-tolerance (OOT) flag and result overflow flags OVF1 and OVF2',
        hidden          : true,
        default         : device_driverlib_peripheral.ADC_Checker[0].name,
        options         : device_driverlib_peripheral.ADC_Checker,
        onChange        : onChangeSafetyCheckerINTs,

    },
    {
        name            : "eventInterruptResult",
        displayName     : "Select result for interrupt",
        description     : 'Out-of-tolerance (OOT) flag and result overflow flags OVF1 and OVF2 are available results for each ADC result safety checker tile',
        hidden          : true,
        default         : device_driverlib_peripheral.ADC_SafetyCheckResult[0].name,
        options         : device_driverlib_peripheral.ADC_SafetyCheckResult,
        onChange        : onChangeSafetyCheckerINTs,

    },
    {
        name            : "enableEvent",
        displayName     : "Enable Event",
        description     : 'safety checker tiles can generate events that can be sent to the X-BAR, so that automatic hardware actions such as an ePWM trip can be generated',
        longDescription : '',
        hidden          : false,
        minSelections   : 0,
        default         : [],
        options         :device_driverlib_peripheral.ADC_SafetyCheckEvent, 
        onChange        : onChangeSafetyCheckerEVNTs,
    },
    
])
for(var sftyIndex in device_driverlib_peripheral.ADC_SafetyCheckEvent)
    {
        var currentSFTY = device_driverlib_peripheral.ADC_SafetyCheckEvent[sftyIndex].name
        var sftyi = (currentSFTY).replace(/[^0-9]/g,'')
        var sfty_Configs = [
        {
            name: "chkEvent" + sftyi.toString() + "Checker",
            displayName : "Select Checker",
            description : 'Select checker for this event',
            hidden      : true,
            default     : device_driverlib_peripheral.ADC_Checker[0].name,
            options     : device_driverlib_peripheral.ADC_Checker,   
        },
        {
            name: "chk" + sftyi.toString() + "CheckResult",
            displayName : "Select Result",
            description : 'Out-of-tolerance (OOT) flag and result overflow flags OVF1 and OVF2 are available results for each ADC result safety checker tile',
            hidden      : true,
            default     : device_driverlib_peripheral.ADC_SafetyCheckResult[0].name,
            options     : device_driverlib_peripheral.ADC_SafetyCheckResult,
        },
    ]
    sftyINT_configs= sftyINT_configs.concat ([{
        name: "GROUP_EVENT" +sftyi.toString(),
        displayName: "Safety Checker Event " + sftyi.toString(),
        description: "",
        longDescription: "",
        config: sfty_Configs
    }])
    }

config= config.concat ([
    {
        name: "GROUP_INT",
        displayName: "Interrupt/Event Configuration",
        description: "Interrupt/Event Configuration",
        longDescription: "",
        config: sftyINT_configs
    },
])

function onValidateStatic(mod, stat)
{
    // console.log("stat");
    // Common.printDebugObject(stat);
    // console.log("mod");
    // Common.printDebugObject(mod);
}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["ADC"]));
}


function onValidate(inst, validation) {
}

var adcscModule = {
    peripheralName: "ADCSafetyChecker",
    displayName: "ADC SAFETY CHECKER",
    maxInstances: 1,
    defaultInstanceName: "myADCSafetyChecker",
    description: "ADC Safety Checker Module",
    longDescription: (Common.getCollateralFindabilityList("ADC")),
    filterHardware : filterHardware,
  
    templates: {
        
    },
    
    moduleStatic: {
        name: "adcSafety",
        displayName: "ADC Safetyy Checker",
        config: config,
     moduleInstances: (inst) =>
     {
        return [{
        name: "safetyCheckerTiles",
        displayName: "Safety Checker Tiles",
        moduleName: "/driverlib/adcsafetycheckertile.js",
        useArray: true,
        collapsed: false,
        group: "GROUP_ADC_CHECKER_TILES",
        }] 
     }
    },
    validate    : onValidate,
};

exports = adcscModule;