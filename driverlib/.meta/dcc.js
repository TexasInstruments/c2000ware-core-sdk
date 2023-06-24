let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_dcc.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

/* Intro splash on GUI */
let longDescription = "The dual-clock comparator module is used for evaluating and monitoring the clock" +
                      " input based on a secondclock, which can be a more accurate and reliable version." +
                      "  This instrumentation is used to detect faults in clocksource or clock structures,"+
                      " thereby enhancing the system's safety metrics.";



var DCC_INSTANCE = [];
var dccMemoryMap = device_driverlib_memmap.DCCMemoryMap;
if (!dccMemoryMap)
{
    dccMemoryMap = device_driverlib_memmap.DCC0MemoryMap
}

for (var dcc of dccMemoryMap) {
    DCC_INSTANCE.push({
        name : dcc.name,
        displayName : dcc.displayName
    })
}

function onChangeENABLESSMODE(inst, ui)
{
    if (inst.enableSingleShotMode == true){
       ui.singleShotModeSource.hidden = false;
    }
    else {
      ui.singleShotModeSource.hidden = true;
    }

}
function onChangeEnableInterrupts(inst, ui)
{
    if (inst.enableInterrupts == true){
        ui.registerInterrupts.hidden = false;
        ui.enableErrorSignalInterrupt.hidden = false;
        ui.enableDoneSignalInterrupt.hidden = false;

    }
    else {
        ui.registerInterrupts.hidden = true;
        ui.enableErrorSignalInterrupt.hidden = true;
        ui.enableDoneSignalInterrupt.hidden = true;

    }

}


function AutoCalculate(localDCCerrtol, localFclk1, localFclk0, localFsysclk, localMeasureFclk1, localFreqerrtol)
{
    var localcounter0seed;
    var localvalidcounter0seed;
    var localcounter1seed;
    var totalErr;
    var allowedFreqErr;
    var dccWindow;
    var asyncErr;
    var dccErr;

    if(localFclk1<localFclk0)
    {
        asyncErr = (2*(localFclk0/localFclk1))+(2*(localFsysclk/localFclk0));
    }
    else
    {
        asyncErr = (2+(2*(localFsysclk/localFclk0)));
    }

    dccErr = asyncErr + 8;
    dccWindow = dccErr/(localDCCerrtol*0.01);
    allowedFreqErr = Math.ceil(dccWindow*localFreqerrtol*0.01);
    totalErr = allowedFreqErr+dccErr;

    localcounter0seed = Math.ceil(dccWindow - totalErr);
    localvalidcounter0seed = Math.ceil(2 * totalErr);
    if(localMeasureFclk1 == false)
    {
        localcounter1seed = Math.ceil((localFclk1/localFclk0)*dccWindow);
    }
    else
    {
        localcounter1seed = 1048575;
    }

    return {
        counter0seed: localcounter0seed,
        validcounter0seed : localvalidcounter0seed,
        counter1seed : localcounter1seed
    }
}

var SysClk_MHz = Common.SYSCLK_getMaxMHz();
var fclk0_default = 10;
var fclk1_default = SysClk_MHz;
var dccerrtol_default = 0.25;
var freqerrtol_default = 1.0;
var autoCal_defaults = AutoCalculate(dccerrtol_default, fclk1_default, fclk0_default, SysClk_MHz, false, freqerrtol_default)

function onChangeAutoCalc(inst, ui)
{

    if(inst.counterAutoCalc)
    {
        ui.counter0seed.readOnly = true;
        ui.validCounter0seed.readOnly = true;
        ui.counter1seed.readOnly = true;
        ui.fsysclk.hidden = false;
        ui.fclk0.hidden = false;
        ui.fclk1.hidden = false;
        ui.dccerrtol.hidden = false;
        ui.freqerrtol.hidden = false;
        ui.measureFclk1.hidden = false;
        ui.fsysclk.readOnly = false;
        ui.fclk0.readOnly = false;
        ui.fclk1.readOnly = false;

        // Calculation
        var autoCalResults = AutoCalculate(inst.dccerrtol, inst.fclk1, inst.fclk0, inst.fsysclk, inst.measureFclk1, inst.freqerrtol)
        // End of calculation

        inst.counter0seed = autoCalResults.counter0seed;
        inst.validCounter0seed = autoCalResults.validcounter0seed;
        inst.counter1seed = autoCalResults.counter1seed;
    }
    else
    {
        ui.counter0seed.readOnly = false;
        ui.validCounter0seed.readOnly = false;
        ui.counter1seed.readOnly = false;
        // ui.fsysclk.readOnly = true;
        // ui.fclk0.readOnly = true;
        // ui.fclk1.readOnly = true;
        ui.dccerrtol.hidden = true;
        ui.freqerrtol.hidden = true;
        ui.measureFclk1.hidden = true;

    }
}

/* Array of DCC configurables that are common across device families */
let config = [

     {
        name        : "dccBase",
        displayName : "DCC Instance",
        description : 'Instance of the DCC used.',
        hidden      : false,
        default     : DCC_INSTANCE[0].name,
        options     : DCC_INSTANCE
    },
    {
        name: "GROUP_Clk",
        displayName: "Clock Configuration",
        collapsed: false,
        config: [

            {
                 name        : "counterAutoCalc",
                 displayName : "Auto Calculate Counter Seeds",
                 description : 'Use Calculated Values for Counter Seed',
                 hidden      : false,
                 onChange    : onChangeAutoCalc,
                 default     : true,
            },
            {
                name        : "setCounter0ClkSource",
                displayName : "Set Counter 0 Clock Source",
                description : 'Set Counter 0 Clock Source',
                hidden      : false,
                default     : device_driverlib_peripheral.DCC_Count0ClockSource[0].name,
                options     : device_driverlib_peripheral.DCC_Count0ClockSource
            },
            {
                name        : "setCounter1ClkSource",
                displayName : "Set Counter 1 Clock Source",
                description : 'Set Counter 1 Clock Source',
                hidden      : false,
                default     : device_driverlib_peripheral.DCC_Count1ClockSource[0].name,
                options     : device_driverlib_peripheral.DCC_Count1ClockSource
            },
            /*Nima need to check here on why initial click reverts to initial value*/
            {
                name        : "counter0seed",
                displayName : "Counter 0 seed value",
                description : 'Sets the value for counter 0 seed',
                hidden      : false,
                default     : autoCal_defaults.counter0seed,
                readOnly    : true,
            },
            {
                name        : "validCounter0seed",
                displayName : "Valid duration Counter 0 seed value",
                description : 'Sets the value for the valid duration counter 0 seed',
                hidden      : false,
                default     : autoCal_defaults.validcounter0seed,
                readOnly    : true,
            },
            {
                name        : "counter1seed",
                displayName : "Counter 1 seed value",
                description : 'Sets the value for counter 1 seed',
                hidden      : false,
                default     : autoCal_defaults.counter1seed,
                readOnly    : true,
            },
            /*End of check*/
            {
                 name        : "fsysclk",
                 displayName : "SysClk Frequency/Fsysclk (MHz)",
                 description : 'SysClk Frequency in MegaHertz used when DCC is running',
                 hidden      : false,
                 onChange    : onChangeAutoCalc,
                 default     : Common.SYSCLK_getMaxMHz(),
            },
            {
                 name        : "fclk0",
                 displayName : "Counter 0 Clock/Fclk0 Frequency (MHz)",
                 description : 'DCC Clk0 (Reference clock) If Fclk0 is unknown or to be measured, put some ball park/expected value, DO NOT LEAVE this field blank',
                 hidden      : false,
                 onChange    : onChangeAutoCalc,
                 default     : fclk0_default,
            },
            {
                 name        : "fclk1",
                 displayName : "Counter 1 Clock/Fclk1 Frequency  (MHz)",
                 description : 'DCC Clk1 (Reference clock) If Fclk0 is unknown or to be measured, put some ball park/expected value, DO NOT LEAVE this field blank',
                 hidden      : false,
                 onChange    : onChangeAutoCalc,
                 default     : fclk1_default,
            },
            {
                 name        : "measureFclk1",
                 displayName : "Measure System Clock Frequency (MHz)",
                 description : 'If Fclk1/Fclk0 value is being measured, meaning instead of checking the validity of the ratio, want to measure exact clock frequency value, then type "Yes" in the Value cell.',
                 hidden      : false,
                 onChange    : onChangeAutoCalc,
                 default     : false,
            },
            {
                 name        : "dccerrtol",
                 displayName : "DCC Error Tolerance (%)",
                 description : 'Tolerance allowed due to error in DCC measurement',
                 longDescription: "This is the allowed error tolerance due to the DCC itself.  A smaller value" +
                                " will be more accurate but take longer to converge.  If the entered value is too" +
                                " small, the counter values will be too large and an error will be auto generated",
                 hidden      : false,
                 onChange    : onChangeAutoCalc,
                 default     : dccerrtol_default,
            },
            {
                 name        : "freqerrtol",
                 displayName : "Frequency Error Tolerance (%)",
                 description : 'If Fclk1 is unknown or to be measured, leave this field blank',
                 longDescription: "This is the expected tolerance of the clock under measurement",
                 hidden      : false,
                 onChange    : onChangeAutoCalc,
                 default     : freqerrtol_default,
            },
        ]
    },
    {
        name: "GROUP_ISR",
        displayName: "Interrupt Configuration",
        collapsed: false,
        config: [
            {
                name        : "enableInterrupts",
                displayName : "Enable Interrupts",
                description : 'Enable DCC Interrupts',
                hidden      : false,
                onChange    : onChangeEnableInterrupts,
                default     : false
            },
            {
                name        : "enableErrorSignalInterrupt",
                displayName : "Enable Error Signal Interrupt",
                description : 'Enable Error Signal',
                hidden      : true,
                default     : false
            },
            {
                name        : "enableDoneSignalInterrupt",
                displayName : "Enable Done Signal Interrupt",
                description : 'Enable Done Signal',
                hidden      : true,
                default     : false
            },
            {
                name        : "registerInterrupts",
                displayName : "Register Interrupt Handler",
                description : 'Whether or not to register interrupt handlers in the interrupt module.',
                hidden      : true,
                default     : false
            },
        ]
    },
    {
        name        : "enableSingleShotMode",
        displayName : "Enable Single Shot Mode",
        description : 'Enable Single Shot Mode',
        hidden      : false,
        onChange    : onChangeENABLESSMODE,
        default     : false
    },
    {
        name        : "singleShotModeSource",
        displayName : "Single Shot Mode Source",
        description : 'Single Shot Mode Source',
        hidden      : true,
        default     : device_driverlib_peripheral.DCC_SingleShotMode[0].name,
        options     : device_driverlib_peripheral.DCC_SingleShotMode
    },
    {
        name        : "enableModule",
        displayName : "Start DCC in DCC_init function",
        description : 'Starts the DCC counters',
        hidden      : false,
        default     : false
    },
];

function onValidate(inst, validation)
{
    var usedDCCInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedDCCInsts.push(instance_obj.dccBase);
    }

    var duplicatesResult = Common.findDuplicates(usedDCCInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The DCC Instance used. Duplicates: " + allDuplicates,
            inst, "dccBase");
    }


    if (inst.counter1seed < 0 || inst.counter1seed > 4294967295)
    {
        validation.logError(
            "Enter an integer for counter1 seed between 0 and 4294967295!",
            inst, "counter1seed");
    }
    if (!Number.isInteger(inst.counter1seed))
    {
        validation.logError(
            "counter 1 seed must be an integer",
            inst, "counter1seed");

    }
    if (inst.counter0seed < 0 || inst.counter0seed > 4294967295)
    {
        validation.logError(
            "Enter an integer for counter0 seed between 0 and 4294967295!",
            inst, "counter0seed");
    }
    if (!Number.isInteger(inst.counter0seed))
    {
        validation.logError(
            "counter 0 seed must be an integer",
            inst, "counter0seed");

    }

    if (inst.validCounter0seed < 0 || inst.validCounter0seed > 4294967295)
    {
        validation.logError(
            "Enter an integer for counter1 seed between 0 and 4294967295!",
            inst, "validCounter0seed");
    }
    if (!Number.isInteger(inst.validCounter0seed))
    {
        validation.logError(
            "valid counter 0 seed must be an integer",
            inst, "validCounter0seed");

    }

    if (inst.fsysclk >  SysClk_MHz)
    {
        validation.logError(
            "SysClk cannot be greater than " + SysClk_MHz + " MHz for this device",
            inst, "fsysclk");
    }

    if(['F2838x', 'F28P65x'].includes(Common.getDeviceName()))
    {
        if (inst.enableInterrupts && inst.registerInterrupts)
        {
            if (!inst.sysErrInt["sysErrSource_SYSCTL_STATUS_" + inst.dccBase.replace("_BASE", "")])
            {
                validation.logInfo(
                    "The interrupt is enabled in the corresponding module but it is not enabled in the SYS ERR interrupt!",
                    inst.sysErrInt, "sysErrSource_SYSCTL_STATUS_" + inst.dccBase.replace("_BASE", ""));
            }
        }
    }

    /* This is warning for NMI, can add some NMI integration if needed */
    if(Common.getDeviceName() == 'F28002x' || Common.getDeviceName() == 'F28003x')
    {
        if (inst.enableErrorSignalInterrupt && inst.registerInterrupts)
        {

                validation.logInfo(
                    "The DCC Error interrupt also goes to the system NMI by default, please make changes as neceessary to avoid duplicate ISRs",
                    inst, "enableErrorSignalInterrupt");

        }
    }

    if (Common.getDeviceName() == "F28004x")
    {
        if (inst.enableSingleShotMode)
        {
            validation.logError(
                    "The DCC single shot mode is not supported for this device",
                    inst, "enableSingleShotMode");
        }
    }

}

var sharedModuleInstances = undefined;

if(['f2838x', 'f28p65x'].includes(Common.getDeviceName().toLowerCase()))
{
    sharedModuleInstances = function (inst) {
        if (inst.enableInterrupts && inst.registerInterrupts)
        {
            return (
                [
                    {
                        name: "sysErrInt",
                        displayName: "Sys Error Interrupt",
                        moduleName: "/driverlib/interrupt/interrupt_sys_err.js",
                        collapsed: true,
                    },
                ]
            );
        }
        return []
    }

}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["DCC"]));
}

var dccModule = {
    peripheralName: "DCC",
    displayName: "DCC",
    maxInstances: DCC_INSTANCE.length,
    defaultInstanceName: "myDCC",
    description: "DCC Peripheral",
    longDescription: longDescription,
    filterHardware : filterHardware,
    config: config,
    moduleInstances: (inst) => {
        if (inst.enableInterrupts && inst.registerInterrupts)
        {
            if(Common.getDeviceName().toLowerCase() == 'f28004x')
            {
                return [{
                    name: "dccInt",
                    displayName: "DCC Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_INT",
                        int : "INT_" + inst.$name,
                        pinmuxPeripheralModule : "",
                        driverlibInt: "INT_DCC"
                    }
                }]
            }
            else if (['f28002x', 'f28003x', 'f280013x', 'f280015x'].includes(Common.getDeviceName().toLowerCase()))
            {
                var interruptName = inst.dccBase.replace("_BASE", "");
                return [{
                    name: "dccInt",
                    displayName: "DCC Interrupt",
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
        }
        return [];
    },
    sharedModuleInstances : sharedModuleInstances,
    templates: {
     boardc : "/driverlib/dcc/dcc.board.c.xdt",
     boardh : "/driverlib/dcc/dcc.board.h.xdt"
    },
    validate    : onValidate
};


if (dccModule.maxInstances <= 0)
{
    delete dccModule.pinmuxRequirements;
}

exports = dccModule;