let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_cputimer.js");

/* Intro splash on GUI */
let longDescription = "";

var CPUTIMER_INSTANCE = [
    { name: "CPUTIMER0_BASE", displayName: "CPUTIMER0"},
    { name: "CPUTIMER1_BASE", displayName: "CPUTIMER1"},
    { name: "CPUTIMER2_BASE", displayName: "CPUTIMER2"},
]

function onChangeCPUTIMERBase(inst, ui)
{
    if (inst.cputimerBase == "CPUTIMER2_BASE"){
        ui.clockSource.hidden = false;
        ui.clockPrescaler.hidden = false;
    }
    else {
        ui.clockSource.hidden = true;
        ui.clockPrescaler.hidden = true;
    }
}

/* Array of CPUTIMER configurables that are common across device families */
let config = [
    {
        name        : "cputimerBase",
        displayName : "CPUTIMER Instance",
        description : 'Instance of the CPUTIMER used.',
        hidden      : false,
        onChange    : onChangeCPUTIMERBase,
        default     : CPUTIMER_INSTANCE[0].name,
        options     : CPUTIMER_INSTANCE
    },
    {
        name        : "emulationMode",
        displayName : "Emulation Mode",
        description : 'Emulation Mode',
        hidden      : false,
        default     : device_driverlib_peripheral.CPUTimer_EmulationMode[0].name,
        options     : device_driverlib_peripheral.CPUTimer_EmulationMode
    },

    {
        name        : "clockSource",
        displayName : "Clock Source",
        description : 'CPUTIMER input clock source',
        hidden      : true,
        default     : device_driverlib_peripheral.CPUTimer_ClockSource[0].name,
        options     : device_driverlib_peripheral.CPUTimer_ClockSource
    },

    {
        name        : "clockPrescaler",
        displayName : "Clock Prescaler",
        description : 'CPUTIMER input clock prescaler',
        hidden      : true,
        default     : device_driverlib_peripheral.CPUTimer_Prescaler[0].name,
        options     : device_driverlib_peripheral.CPUTimer_Prescaler
    },

    {
        name        : "timerPrescaler",
        displayName : "Timer Prescaler",
        description : 'Sets the CPUTIMER timer prescaler.',
        hidden      : false,
        default     : 0
    },
    {
        name        : "timerPeriod",
        displayName : "Timer Period",
        description : 'Sets the CPUTIMER period.',
        hidden      : false,
        default     : 0
    },
    {
        name        : "enableInterrupt",
        displayName : "Enable Interrupt",
        description : 'Whether or not to enable interrupts.',
        hidden      : false,
        default     : false
    },
    {
        name        : "registerInterrupts",
        displayName : "Register Interrupt Handler",
        description : 'Whether or not to register interrupt handlers in the interrupt module.',
        hidden      : false,
        default     : false
        
    },
    {
        name        : "startTimer",
        displayName : "Start Timer",
        description : 'Whether or not to start the timer.',
        hidden      : false,
        default     : false
    },
];


function onValidate(inst, validation) 
{   
    var usedCPUTIMERInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedCPUTIMERInsts.push(instance_obj.cputimerBase);
    }

    var duplicatesResult = Common.findDuplicates(usedCPUTIMERInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The CPUTIMER Instance used. Duplicates: " + allDuplicates, 
            inst, "cputimerBase");
    }


    if (inst.timerPrescaler < 0 || inst.timerPrescaler > 65535)
    {
        validation.logError(
            "Enter an integer for Timer Prescaler between 0 and 65535!", 
            inst, "timerPrescaler");
    }
    if (!Number.isInteger(inst.timerPrescaler))
    {
        validation.logError(
            "Timer Prescaler must be an integer", 
            inst, "timerPrescaler");
    }
    if (inst.timerPeriod < 0 || inst.timerPeriod > 4294967295)
    {
        validation.logError(
            "Enter an integer for Timer Period between 0 and 4294967295!", 
            inst, "timerPeriod");
    }
    if (!Number.isInteger(inst.timerPeriod))
    {
        validation.logError(
            "Timer Period must be an integer", 
            inst, "timerPeriod");
    }
    if (inst.timerPeriod == 0)
    {
        validation.logWarning(
            "Timer Period is currently set to 0", 
            inst, "timerPeriod");
    }
    
}


function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["CPUTIMER"]));
}

var cputimerModule = {
    peripheralName: "CPUTIMER",
    displayName: "CPUTIMER",
    maxInstances: 3,
    defaultInstanceName: "myCPUTIMER",
    description: "CPUTIMER Peripheral",
    filterHardware : filterHardware,
    config: config,
    moduleInstances: (inst) => {
        if (inst.registerInterrupts)
        {
            var interruptName = inst.cputimerBase.replace("CPU", "").replace("_BASE", "");
            return [{
                name: "timerInt",      
                displayName: "Timer Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_INT",
                    int : "INT_" + inst.$name,
                    pinmuxPeripheralModule : "",
                    driverlibInt: "INT_" + interruptName
                }
            }]
        }
        return [];
    },
    templates: {
        boardc : "/driverlib/cputimer/cputimer.board.c.xdt",
        boardh : "/driverlib/cputimer/cputimer.board.h.xdt"
    },
    validate    : onValidate
};


if (cputimerModule.maxInstances <= 0)
{
    delete cputimerModule.pinmuxRequirements;
}

exports = cputimerModule;