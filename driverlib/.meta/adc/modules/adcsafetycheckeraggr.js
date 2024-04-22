let Common   = system.getScript("/driverlib/Common.js");
let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_adc.js");

let device_driverlib_memmap =
system.getScript("/driverlib/device_driverlib_peripherals/" +
    Common.getDeviceName().toLowerCase() + "_memmap.js");

var ADC_SFTYCH_SOURCE =[];

var ADCINTEVT_INSTANCE =[];

if (["F28P65x"].includes(Common.getDeviceName()))
{
    for (var sftychkr in device_driverlib_memmap.ADCSAFETYINTEVTAGGMemoryMap)
    {
        ADCINTEVT_INSTANCE.push(
            { name: device_driverlib_memmap.ADCSAFETYINTEVTAGGMemoryMap[sftychkr].name, 
            displayName: device_driverlib_memmap.ADCSAFETYINTEVTAGGMemoryMap[sftychkr].name.replace("_BASE","")
            }, 
        )     
    }
}

var maxInstances = ADCINTEVT_INSTANCE.length

if (["F28P65x"].includes(Common.getDeviceName()))
{
    for (var sftychkr in device_driverlib_memmap.ADCSAFETYCHKMemoryMap)
    {
        for (var chkrslt in device_driverlib_peripheral.ADC_SafetyCheckResult)
        {
            var currentchkrslt= device_driverlib_memmap.ADCSAFETYCHKMemoryMap[sftychkr].name.replace("_BASE","").replace("ADC","")
            var currentsftychkr = device_driverlib_peripheral.ADC_SafetyCheckResult[chkrslt].name.replace("ADC_SAFETY_CHECK_","")

            ADC_SFTYCH_SOURCE.push(
                { name: device_driverlib_memmap.ADCSAFETYCHKMemoryMap[sftychkr].name.replace("_BASE","").replace("ADC","") + device_driverlib_peripheral.ADC_SafetyCheckResult[chkrslt].name.replace("ADC_SAFETY_CHECK_",""), 
                displayName: device_driverlib_memmap.ADCSAFETYCHKMemoryMap[sftychkr].name.replace("_BASE","").replace("ADCSAFETYCHK","SAFETY_CHECK") + " "+ device_driverlib_peripheral.ADC_SafetyCheckResult[chkrslt].name.replace("ADC_SAFETY_CHECK_","")
                }, 
            )  
        }
        
    }  
}

function onChangeSafetyCheckerEVNTs(inst, ui){
    for(var evntIndex in device_driverlib_peripheral.ADC_SafetyCheckEvent)
    {
        var currentEvnt = device_driverlib_peripheral.ADC_SafetyCheckEvent[evntIndex].name
        var evnti = (currentEvnt).replace(/[^0-9]/g,'')
        var sftyEVNTConfigs = 
            [
                "chkEvent" + evnti.toString() + "Source",
            ]

        if (ui)
        {
            for (var sftyConfig of sftyEVNTConfigs)
            {
                if(inst["enableEvent"].includes(currentEvnt))
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
        if((inst.enableInterrupt)) {
            ui["eventInterruptSource"].hidden = false;
        }
        else {
            ui["eventInterruptSource"].hidden = true;
        }
    }
}
    
var config = [
{
        name        : "adcIntEvtBase",
        displayName : "ADC INTEVT Instance",
        description : 'Instance of the ADC used.',
        hidden      : false,
        default     : ADCINTEVT_INSTANCE[0].name,
        options     : ADCINTEVT_INSTANCE,
    },
    {
        name            : "enableInterrupt",
        displayName     : "Enable Interrupt",
        description     : 'Each ADC result safety checker tile can generate an interrupt signal from out-of-tolerance (OOT) flag and result overflow flags OVF1 and OVF2',
        longDescription : 'Each ADC result safety checker tile generates an interrupt pulse when an enabled out-of-tolerance (OOT) or overflow OVF1 or OVF2 event occurs. No further interrupt pulses will be generated until the interrupt flag is cleared.',
        hidden          : false,
        default         : false,
        onChange        : onChangeSafetyCheckerINTs,
    },
    {
        name            : "eventInterruptSource",
        displayName     : "Select source for interrupt",
        description     : 'Each ADC result safety checker tile can generate an interrupt signal from out-of-tolerance (OOT) flag and result overflow flags OVF1 and OVF2',
        hidden          : true,
        minSelections   : 0,
        default         : [],
        options         : ADC_SFTYCH_SOURCE,
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
    
];

for(var evntIndex in device_driverlib_peripheral.ADC_SafetyCheckEvent)
    {
        var currentEvnt = device_driverlib_peripheral.ADC_SafetyCheckEvent[evntIndex].name
        var evnti = (currentEvnt).replace(/[^0-9]/g,'')
        var sfty_Configs = [
        {
            name: "chkEvent" + evnti.toString() + "Source",
            displayName : "Select Source",
            description : 'Select Source for this event',
            hidden      : true,
            minSelections   : 0,
            default         : [],
            options     : ADC_SFTYCH_SOURCE,   
        },

    ]
    config = config.concat ([{
        name: "GROUP_EVENT" +evnti.toString(),
        displayName: "Safety Check Event " + evnti.toString(),
        description: "",
        longDescription: "",
        config: sfty_Configs
    }])
    }

function onValidate(inst, validation) { 
    //
    // Check duplicate sources  
    //
    var usedADCSCInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedADCSCInsts.push(instance_obj.adcIntEvtBase);
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
                usedADCSCInsts.push(instance_obj.adcIntEvtBase);
            }
        }
    }
    var duplicatesResult = Common.findDuplicates(usedADCSCInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The ADC Safety Checker Aggregator Instance used. Duplicates: " + allDuplicates,
            inst, "adcIntEvtBase");
    }

    if (Common.isContextCPU1()) {
        if (inst["adcIntEvtBase"] == "ADCSAFETYINTEVTAGG2_BASE"){
            validation.logError(
                "ADC Safety INTEVT Aggregator 2 instance can not be used for CPU1", inst, "adcIntEvtBase");
        }
    }
    if (Common.isContextCPU2()) {
        if (inst["adcIntEvtBase"] == "ADCSAFETYINTEVTAGG1_BASE"){
            validation.logError(
                "ADC Safety INTEVT Aggregator 1 instance can not be used for CPU2", inst, "adcIntEvtBase");
        }
    }
}

var adcSCSubmodule = {
    //peripheralName: "ADCSafetyCheckerINTEVT",
    displayName: "ADC SAFETY CHECKER INTEVT",
    defaultInstanceName: "myADCSAFETYCHECKERAGGR",
    description: "ADC Safety Checker Interrupt Event Aggregator",
    maxInstances: maxInstances,
    config: config,
    validate: onValidate,
    templates: {
        // boardc : "",
        // boardh : ""
    },
};


exports = adcSCSubmodule;
