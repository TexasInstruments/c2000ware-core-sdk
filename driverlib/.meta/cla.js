let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_cla.js");
let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");
let device_driverlib_int =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_interrupt.js");
let device_driverlib_memcfg =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memcfg.js");

/* Intro splash on GUI */
let longDescription = `The Control Law Accelerator (CLA) extends the capabilities of the C28x CPU by adding parallel processing. Time-critical
control loops serviced by the CLA can achieve low ADC sample to output delay. Thus, the CLA enables
faster system response and higher frequency control loops. Utilizing the CLA for time-critical tasks frees up the
main CPU to perform other system and communication functions concurrently.
`;
var CLA_INSTANCE = [];
CLA_INSTANCE.push({
    name : "CLA1_BASE",
    displayName : "CLA1"
})
 
/*
 * 
 * CLA instance selection UI
 *
 */

let config = [
    {
        name        : "claBase",
        displayName : "CLA Instance",
        description : 'Instance of the CLA used.',
        hidden      : false,
        default     : CLA_INSTANCE[0].name,
        options     : CLA_INSTANCE
    },
];

/*
 *
 * CLA Task configuration UI
 *
 */

// Generate task configuration UI
var clatask_group_config = [];

// Task Enable checkbox for each task
device_driverlib_peripheral.CLA_TaskNumber.
    forEach((element, index) =>
    {
        clatask_group_config = clatask_group_config.concat([
            {
                name            : "enable_"+element.name,
                displayName     : "Enable " + element.displayName,
                default         : true,
                onChange        : onChangeEnableClaTask
            }
        ]);
    });

// Configuration UI for each task
device_driverlib_peripheral.CLA_TaskNumber.
    forEach((element, index) =>
    {
        var clataskindex = element.name[element.name.length-1];
        var clataskname = element.name;
    
        var clatask_config = [];
        clatask_config = clatask_config.concat([
            {
                name        : "mvect_"+clataskname,
                displayName : "Interrupt Vector",
                default     : device_driverlib_peripheral.CLA_MVECTNumber[index].name,
                readOnly    : true,
            },
            {
                name        : "name_"+clataskname,
                displayName : "Interrupt Name",
                default     : "Cla1Task"+clataskindex,
            },
            {
                name        : "trigger_"+clataskname,
                displayName : "Trigger Source",
                default     : device_driverlib_peripheral.CLA_Trigger[0].name,
                options     : device_driverlib_peripheral.CLA_Trigger
            },
        ]);
    
        clatask_group_config = clatask_group_config.concat([
            {
                name            : "group_"+clataskname,
                displayName     : element.displayName,
                description     : "",
                longDescription : "",
                config          : clatask_config
            }
        ]);        
    });



// If device has CLA version 2, add task 8 background task configuration option
var CLA2_device_list = ["f28004x", "f2838x", "f28003x", "f28p65x"];

if (CLA2_device_list.includes(Common.getDeviceName().toLowerCase()))
{
    clatask_group_config[15].config = clatask_group_config[15].config.concat([
        {
            name        : "background_"+device_driverlib_peripheral.CLA_TaskNumber[7].name,
            displayName : "Enable Background Task (CLA Task 8)",
            default     : false,
        }
    ]);
}

// Add the CLA task configuration block to UI
config = config.concat([
    {
        name        : "claTaskGroup",
        displayName : "CLA Task Configuration",
        config      : clatask_group_config,
    },
]);

/*
 *
 * CLA memory allocation UI
 * 
 */
var LSRAM_list = [];
device_driverlib_memcfg.MEMCFG_SECT.
    forEach((element, index) =>
    {
        if ((element.name.includes("MEMCFG_SECT_LS")) && (element.name != "MEMCFG_SECT_LSX_ALL"))
        {
            LSRAM_list.push(element);
        }
    });


/*
 *
 * CLA task CPU interrupt configuration UI
 * 
 */

// Generate CPU interrupt configuration UI
var cpuint_group_config = [];

device_driverlib_peripheral.CLA_TaskNumber.
    forEach((element, index) =>
    {
        cpuint_group_config = cpuint_group_config.concat([
            {
                name            : "cpuint_"+element.name,
                displayName     : "Register Interrupt for " + element.displayName,
                default         : true,
            }
        ]);
    });

// Add the CPU interrupt configuration block to UI
config = config.concat([
    {
        name        : "cpuIntGroup",
        displayName : "C28 Interrupt Register for CLA Task",
        config      : cpuint_group_config,
    },
]);


/*
 *
 * Callback function for enable task
 * 
 */
function onChangeEnableClaTask(inst, ui) {
    //console.log("Changed enable checkbox");
    //console.log(inst);
    //console.log(ui);

    device_driverlib_peripheral.CLA_TaskNumber.
    forEach((element, index) =>
    {
        // Task enabled, show configuration UI
        if (inst["enable_"+element.name])
        {
            ui["mvect_"+element.name].hidden = false;
            ui["name_"+element.name].hidden = false;
            ui["trigger_"+element.name].hidden = false;
            if (element.name[element.name.length-1] == 8 && typeof ui["background_"+element.name] !== 'undefined')
            {
                ui["background_"+element.name].hidden = false;
            }
        }
        else  // Hide configuration UI
        {
            ui["mvect_"+element.name].hidden = true;
            ui["name_"+element.name].hidden = true;
            ui["trigger_"+element.name].hidden = true;
            if (element.name[element.name.length-1] == 8 && typeof ui["background_"+element.name] !== 'undefined')
            {
                ui["background_"+element.name].hidden = true;
            }
        }
    });
}

/*
 *
 * Validate configuration
 * 
 */
function onValidate(inst, validation) {

    //
    // Make sure the BASE address is not duplicated
    //
    var usedCLAInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedCLAInsts.push(instance_obj.claBase);
    }

    var duplicatesResult = Common.findDuplicates(usedCLAInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The CLA Instance used. Duplicates: " + allDuplicates, 
            inst, "claBase");
    }
}


/*
 *
 * Add MemCfg dependency
 * 
 */
var claStatic = {
    name: "claGlobal",
    displayName: "CLA Global",
    modules: Common.autoForce("memcfg", "/driverlib/memcfg.js")
}

/*
 *
 * CLA module
 * 
 */
var claModule = {
    peripheralName: "CLA",
    displayName: "CLA",
    // longDescription : longDescription,
    longDescription : longDescription + "\n" + (Common.getCollateralFindabilityList("CLA")),
    maxInstances: CLA_INSTANCE.length,
    defaultInstanceName: "myCLA",
    description: "Control Law Accelerator",
    config: config,
    moduleStatic: claStatic,
    moduleInstances: (inst) => {
        var intReturn =  [];
        // Loop through all instances of task interrupt
        device_driverlib_peripheral.CLA_TaskNumber.forEach((element, index) =>
        {
            // If CLA task interrupt is enabled then generate interrupt configuration UI
            if (inst["cpuint_"+element.name])
            {
                intReturn.push ({
                    name        : "intconfig_"+element.name,
                    displayName : "C28 Interrupt Configuration for " + element.displayName,
                    moduleName  : "/driverlib/interrupt.js",
                    collapsed   : true,
                    args        : {
                        $name                   : "interrupt_" + element.name,
                        int                     : "INT_" + inst.$name + element.name[element.name.length-1],
                        pinmuxPeripheralModule  : "",
                        driverlibInt            : "INT_CLA1_" + element.name[element.name.length-1],
                        interruptHandler        : "cla1Isr" + element.name[element.name.length-1],
                        enableInterrupt         : true,
                    }
                })
            }
        });
        return intReturn;
    },
    sharedModuleInstances : undefined,
    templates: {
        boardc : "/driverlib/cla/cla.board.c.xdt",
        boardh : "/driverlib/cla/cla.board.h.xdt"
    },
    validate    : onValidate,
};

exports = claModule;