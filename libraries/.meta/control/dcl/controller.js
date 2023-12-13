let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/C2000WARELibraryReferences.js");
let controller_data = system.getScript("/libraries/control/dcl/controller_data.js");

// get the main dropdown lists
var CONTROLLER_CHOICE_LIST  = controller_data.get_dropdown_list('controller');
var PRECISION_LIST          = controller_data.get_dropdown_list('precision');
var ACCELERATOR_LIST        = controller_data.get_dropdown_list('accelerator');

// set the default values for each list
var DEFAULT_CONTROLLER_CHOICE   = CONTROLLER_CHOICE_LIST[0].name;
var DEFAULT_PRECISION           = "F32"; // F32 by default as it is most common
var DEFAULT_ACCELERATOR         = ACCELERATOR_LIST[0].name;

// whenever the controller changes, the list of parameters should change
function onChangeControllerChoice(inst, ui)
{
    // TODO - update terms to zero when changing from PID to DF types
    // everything hidden by default
    for(var i in config) 
    {
        // console.log("ui[config[i].name].hidden=" + ui[config[i].name].hidden)
        ui[config[i].name].hidden = true;
    }
    
    // default is to unhide controller choice, precision, and accelerator
    ui.controllerChoice.hidden          = false;
    ui.controllerPrecision.hidden       = false;
    ui.controllerAccelerator.hidden     = true;
    ui.structDisplay.hidden             = false;

    // get the list of elements for this chosen controller
    var control_struct_entry = controller_data.get_control_struct_entry(inst.structDisplay);
    if (control_struct_entry)
    {
        // unhide the long description for this controller
        var longDescName = control_struct_entry["longDescName"];
        ui["longDesc_" + longDescName].hidden=false;
        
        var config_entries_list = control_struct_entry["config_entries_list"];
        // unhide the given elements in that list
        for(var e of config_entries_list)
        {
            ui[e[0]].hidden = false;
            inst[e[0]] = e[1];
        }
    }

}

let config = [
    {
        name        : "controllerChoice",
        displayName : "Controller/Filter",
        onChange    : onChangeControllerChoice,
        description : 'Choice of Controller. NOTE: Changing controller will change all parameters to default.',
        hidden      : false,
        default     : DEFAULT_CONTROLLER_CHOICE,
        options     : CONTROLLER_CHOICE_LIST,
    },
    {
        name        : "controllerPrecision",
        displayName : "Precision",
        onChange    : onChangeControllerChoice,
        description : 'Choice of Precision. NOTE: Changing precision will change all parameters to default.',
        hidden      : false,
        default     : DEFAULT_PRECISION,
        options     : PRECISION_LIST,
    },
    {
        name        : "controllerAccelerator",
        displayName : "Accelerator",
        description : 'Choice of Accelerator.',
        hidden      : true,
        default     : DEFAULT_ACCELERATOR,
        options     : ACCELERATOR_LIST,
    },
    {
        name        : "structDisplay",
        displayName : "Controller Structure Chosen",
        description : 'Visualization of the chosen DCL structure.',
        hidden      : false,
        getValue    : (inst) => {
            var choices_dict = {
                "controller":inst.controllerChoice,
                "precision":inst.controllerPrecision,
                "accelerator":inst.controllerAccelerator,
            };
            return controller_data.get_struct_options(choices_dict).join();
        },
        default     : ""
    }
]

function isNumber(s)
{
    // remove trailing L or f for longs and floats
    if (s.endsWith("L") || s.endsWith("f"))
    {
        s = s.slice(0,-1);
    }

    // check if the resultant value is a number
    return !isNaN(s);
}

function onValidate(inst, validation) {
    // list the available controlStruct options
    var choices_dict = {
        "controller":inst.controllerChoice,
        "precision":inst.controllerPrecision,
        "accelerator":inst.controllerAccelerator,
    };
    
    var availControlStructs = controller_data.get_struct_options(choices_dict);
    if (availControlStructs.length <= 0)
    {
        validation.logError(
            "Precision not available for this controller, please choose a different precision option.",
            inst, "controllerPrecision");
        // validation.logError(
        //     "Precision and accelerator combination not available for this controller, please choose a different precision/accelerator option.",
        //     inst, "controllerAccelerator");
    }
    var control_struct_entry = controller_data.get_control_struct_entry(inst.structDisplay);
    if (control_struct_entry)
    {
        var config_entries_list = control_struct_entry["config_entries_list"];
        for(var e of config_entries_list)
        {
            // check for empty elements
            if(inst[e[0]] == "")
            {
                validation.logError(
                    "A value must be provided.",
                    inst, e[0]);
            }
            // check if it's an actual number
            if(!isNumber(inst[e[0]]))
            {
                validation.logError(
                    "Value must be a valid number (hex, decimal, float, long, etc.)",
                    inst, e[0]
                );
            }
        }
    }
    // only do this check if one of the floating point precisions are chosen
    if (inst.controllerPrecision == "F32" || inst.controllerPrecision == "F64") {
        // check if controllerPrecision matches the precision being used by FPU.js in the "Other Dependencies" section
        var fpuMod = system.modules["/libraries/math/FPU/FPU.js"];
        if(fpuMod)
        {
            if(fpuMod.$static.fpuType.replace("PU","") != inst.controllerPrecision)
            {
                // when controller precision == F64, and the FPU.js file has FPU32 chosen, then warn the user that performance loss will occur
                if (inst.controllerPrecision == "F64" && fpuMod.$static.fpuType == "FPU32") {
                    // for devices that can actually support F64, tell user that they can fix the issue
                    if (controller_data.fpu64_supported)
                    {
                        validation.logWarning("Double-precision data type chosen with single-precision floating-point processor chosen. Relatively poor cycle performance should be expected. To improve performance, precision can be updated here or in 'Other Dependencies' below.", inst, "controllerPrecision");
                    }
                    // for devices that can't support F64, tell the user that performance loss should be expected
                    else
                    {
                        validation.logWarning("Double-precision data type chosen with single-precision floating-point processor chosen. Relatively poor cycle performance should be expected.", inst, "controllerPrecision");
                    }
                }
                else
                {
                    // when controller precision == F32, and the FPU.js file has FPU64 chosen, there should be no issue as FPU64 is backwards compatible with FPU32 instructions and C code
                }
            }
        }
    }

    // verify that TMU1 is enabled if NLPID is chosen
    if (inst.controllerChoice == "NLPID")
    {
        var fpuMod = system.modules["/libraries/math/FPU/FPU.js"];
        if(fpuMod && fpuMod.$static.tmuType != "TMU1")
        {
            validation.logError("TMU1 must be enabled to use NLPID controller. Update 'Other Dependencies' below to enable TMU1.", inst, "controllerChoice");
        }
    }
}

// Choose which controllerChoice to have its parameters be unhidden by default
controller_data.set_config_entries_default_unhidden(DEFAULT_CONTROLLER_CHOICE)
// add on all the long description config entries for each controller
config = config.concat(controller_data.getLongDescriptionConfigEntries(DEFAULT_CONTROLLER_CHOICE));
// add on all the config_entries from controller_data.js to "config" array
config = config.concat(controller_data.get_config_entries_list());

var longDescription = `The DCL contains the following controller types:
* Linear PID
* Linear PI
* Non-linear PID
* Non-linear PI
* Double Integrator
* Direct Form 1 (first order)
* Direct Form 1 (third order)
* Direct Form 2 (second order)
* Direct Form 2 (third order)

See the DCL User's Guide for details on each controller/compensator and its variables:

[Digital Control Library User's Guide](https://dev.ti.com/tirex/explore/node?node=AKZRbh4oxv98HaO0YKjygQ__gYkahfz__LATEST)`

var controllerModule = {
    c2000wareLibraryName: "CONTROLLER",
    displayName: "CONTROLLER",
    defaultInstanceName: "myCONTROLLER",
    description: "CONTROLLER",
    longDescription: longDescription,
    config: config,
    references : [],
    templates: {
        c2000ware_libraries_c           : "/libraries/control/dcl/templates/controller.c2000ware_libraries.c.xdt",
        c2000ware_libraries_h           : "/libraries/control/dcl/templates/controller.c2000ware_libraries.h.xdt",
    },
    validate : onValidate,
    modules: (inst) => {
        var mods = [];
        var refFilesArr = controller_data.getRefFilesModuleArrFromControlStruct(inst.structDisplay);
        mods = refFilesArr;
        return mods;
    }
};

exports = controllerModule;