let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_interrupt.js");

/* Intro splash on GUI */
let longDescription = "";

function onChangeInt(inst, ui)
{
    inst["interruptName"] =  inst["int"]
    
    inst["interruptHandler"] = inst["int"] + "_ISR"
    // var interruptInfo = device_driverlib_peripheral.interrupts.find((input) => {
    //     if (input.int_define_name == inst["int"]){
    //         return input
    //     }
    // })
    // if (interruptInfo)
    // {
    //     inst["interruptDescription"] = interruptInfo.int_description;
    //     inst["pieGroup"] = interruptInfo.int_group_number;
    //     inst["pieChannel"] = interruptInfo.int_channel_number;
    // }
}


/* Array of CAN configurables that are common across device families */
let config = [
    {
        name        : "int",
        displayName : "Int",
        description : 'The interrupt name in driverlibs inc/hw_ints',
        hidden      : true,
        readOnly    : false,
        default     : '',
        onChange    : onChangeInt
    },
    {
        name        : "pinmuxPeripheralModule",
        displayName : "PinMux Peripheral Module",
        description : 'The pinmux peripheral module name',
        hidden      : true,
        readOnly    : false,
        default     : ''
    },
    {
        name        : "driverlibInt",
        displayName : "Driverlib Int",
        description : 'The interrupt name in driverlibs inc/hw_ints',
        hidden      : true,
        readOnly    : false,
        default     : ''
    },
    {
        name        : "interruptName",
        displayName : "Interrupt Name",
        description : 'The interrupt name',
        hidden      : false,
        readOnly    : true,
        default     : ''
    },
    {
        name        : "interruptHandler",
        displayName : "Interrupt Handler",
        description : 'The interrupt handler function name',
        hidden      : false,
        readOnly    : false,
        default     : ''
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
    displayName: "INTERRUPT",
    defaultInstanceName: "myInterrupt",
    description: "",
    config: config,
    templates: {
        boardc : "/driverlib/interrupt/interrupt.board.c.xdt",
        boardh : "/driverlib/interrupt/interrupt.board.h.xdt"
    },
    validate    : onValidate,
    uiAdd: "summary"
};

exports = intModule;