let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_interrupt.js");

/* Intro splash on GUI */
let longDescription = "";

var int = "INT_SYS_ERR";
var pinmuxPeripheralModule = "";
var driverlibInt = "INT_SYS_ERR";

/* Array of CAN configurables that are common across device families */
let config = [
    {
        name        : "int",
        displayName : "Int",
        description : 'The interrupt name in driverlibs inc/hw_ints',
        hidden      : true,
        readOnly    : false,
        default     : int,
    },
    {
        name        : "pinmuxPeripheralModule",
        displayName : "PinMux Peripheral Module",
        description : 'The pinmux peripheral module name',
        hidden      : true,
        readOnly    : false,
        default     : pinmuxPeripheralModule
    },
    {
        name        : "driverlibInt",
        displayName : "Driverlib Int",
        description : 'The interrupt name in driverlibs inc/hw_ints',
        hidden      : true,
        readOnly    : false,
        default     : driverlibInt
    },
    {
        name        : "interruptName",
        displayName : "Interrupt Name",
        description : 'The interrupt name',
        hidden      : false,
        readOnly    : true,
        default     : int,
    },
    {
        name        : "interruptHandler",
        displayName : "Interrupt Handler",
        description : 'The interrupt handler function name',
        hidden      : false,
        readOnly    : false,
        default     : int + "_ISR"
    },
    {
        name        : "enableInterrupt",
        displayName : "Enable Interrupt in PIE",
        description : 'Enable the interrupt in the interrupt module',
        hidden      : false,
        readOnly    : false,
        default     : false
    },
];


let device_driverlib_sysctl = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sysctl.js");

var sysErrSources = device_driverlib_sysctl.SYSCTL_STATUS_SYS_ERR
if (sysErrSources)
{
    var sysErrSourcesConfig = [];
    for (var sysErrSourceIndex = 1; sysErrSourceIndex < sysErrSources.length; sysErrSourceIndex++)
    {
        sysErrSourcesConfig.push({
            name: "sysErrSource_" + sysErrSources[sysErrSourceIndex].name,
            displayName: "Enable " + sysErrSources[sysErrSourceIndex].displayName,
            default: false
        })
    }

    config = config.concat([
        {
            name: "GROUP_INT_SOURCES",
            displayName: "Interrupt Sources",
            config : sysErrSourcesConfig
        }
    ])  
}

function onValidate(inst, validation) {
    var usedInterruptInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedInterruptInsts.push(instance_obj.int);
    }

    var duplicatesResult = Common.findDuplicates(usedInterruptInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        if (duplicatesResult.duplicates.includes(inst.int))
        {
            validation.logError(
                "Duplicates: " + allDuplicates, 
                inst, "int");
        }

    }
}


var intModule = {
    peripheralName: "INTERRUPT",
    displayName: "INTERRUPT SYS_ERR",
    maxInstances: 1,
    defaultInstanceName: "myInterruptSysErr",
    description: "",
    config: config,
    templates: {
        boardc : "/driverlib/interrupt/interrupt.board.c.xdt",
        boardh : "/driverlib/interrupt/interrupt.board.h.xdt"
    },
    validate    : onValidate,
};

exports = intModule;