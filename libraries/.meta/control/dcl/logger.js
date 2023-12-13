let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/libraries/C2000WARELibraryReferences.js");
let logger_data = system.getScript("/libraries/control/dcl/logger_data.js");


// whenever the controller changes, the list of parameters should change
function onChangeControllerChoice(inst, ui)
{

}

let config = [
    {
        name        : "loggerPrecision",
        displayName : "Precision",
        description : 'Choice of Precision.',
        hidden      : false,
        default     : "F32",
        options     : [ {name:"FIXED",displayName:"Fixed-Point (32-bit)"}, 
                        {name:"F32",displayName:"Floating-Point (32-bit)"}, 
                        {name:"F64",displayName:"Floating-Point (64-bit)"}],
    },
    {
        name        : "structDisplay",
        displayName : "Logger Structure Chosen",
        description : 'Visualization of the chosen DCL structure.',
        hidden      : false,
        getValue    : (inst) => {
            // choose structure based on precision only
            if      (inst.loggerPrecision == "FIXED"){return "LOG32";}
            else if (inst.loggerPrecision == "F32")  {return "FDLOG";}
            else if (inst.loggerPrecision == "F64")  {return "FDLOG64";}
            else                                     {return "FDLOG";}
        },
        default     : "FDLOG"
    },
    {
        name:"arrName",
        hidden:false,
        default:"",
        displayName:"Re-Name Array Variable",
        description:"Name of the data array for the logger, default name provided if left blank",
        longDescription:"Name of the data array for the logger, default name provided if left blank. If the array already exists in memory, this will be used to point to that array."
    },
    {
        name:"logSize",
        hidden:false,
        default:0x0400,
        displayName:"Size",
        description:"The size of the memory block in words",
        longDescription:"The size of the memory block in words."
    },
    {
        name:"arrEn",
        hidden:false,
        default:true,
        displayName:"Create Array Object",
        description:"Create the array object, for cases where the array does not already exist.",
        longDescription:"Create the array object, for cases where the array does not already exist. NOTE: if this is unchecked the array must exist somewhere in the code, otherwise a compile error will occur."
    },
    {
        name:"linkerEn",
        hidden:false,
        default:false,
        onChange: (inst, ui) => {ui.linkerVal.hidden = ((inst.linkerEn) ? false : true);}, // hide Val when disabled
        displayName:"Enable Linker Location",
        description:"Linker command file used for declaring the array directly",
        longDescription:"This creates a pragma to point to the given location in memory"
    },
    {
        name:"linkerVal",
        hidden:true,
        default:"",
        displayName:"Re-Name Linker Pragma Name",
        description:"Pragma name of the location of the array in the linker command file, default name provided if left blank",
        longDescription:"Pragma name of the location of the array in the linker command file, default name provided if left blank"
    },
    {
        name:"fillEn",
        hidden:false,
        default:false,
        onChange: (inst, ui) => {ui.fillVal.hidden = ((inst.fillEn) ? false : true);}, // hide Val when disabled
        displayName:"Enable Fill",
        description:"Enable filling the buffer with a given data value and resets the data",
        longDescription:"Enable filling the entire array with a given value"
    },
    {
        name:"fillVal",
        hidden:true,
        default:0,
        displayName:"Fill Value",
        description:"Fills the buffer with the given value and resets the data",
        longDescription:"Fills the buffer with the given value and resets the data"
    },
]

function onValidate(inst, validation) {
    // only do this check if one of the floating point precisions are chosen
    if (inst.loggerPrecision == "F32" || inst.loggerPrecision == "F64") {
        // check if loggerPrecision matches the precision being used by FPU.js in the "Other Dependencies" section
        var fpuMod = system.modules["/libraries/math/FPU/FPU.js"];
        if(fpuMod)
        {
            if(fpuMod.$static.fpuType.replace("PU","") != inst.loggerPrecision)
            {
                // when controller precision == F64, and the FPU.js file has FPU32 chosen, then warn the user that performance loss will occur
                if (inst.loggerPrecision == "F64" && fpuMod.$static.fpuType == "FPU32") {
                    // for devices that can actually support F64, tell user that they can fix the issue
                    let fpu_obj = system.getScript("/libraries/.meta/math/FPU/FPU.js").moduleStatic.config;
                    var fpu_types = fpu_obj.filter(fpu_or_tmu_list => fpu_or_tmu_list.name === "fpuType")[0].options;
                    var fpu64_supported = false;
                    if (fpu_types.length >= 2) {
                        // 2 options available means that both FPU32 (all Sysconfig devices) and FPU64 (some Sysconfig devices) are supported
                        fpu64_supported = true;
                    }
                    if (fpu64_supported)
                    {
                        validation.logWarning("Double-precision data type chosen with single-precision floating-point processor chosen. Relatively poor cycle performance should be expected. To improve performance, precision can be updated here or in 'Other Dependencies' below.", inst, "loggerPrecision");
                    }
                    // for devices that can't support F64, tell the user that performance loss should be expected
                    else
                    {
                        validation.logWarning("Double-precision data type chosen with single-precision floating-point processor chosen. Relatively poor cycle performance should be expected.", inst, "loggerPrecision");
                    }
                }
                else
                {
                    // when controller precision == F32, and the FPU.js file has FPU64 chosen, there should be no issue as FPU64 is backwards compatible with FPU32 instructions and C code
                }
            }
        }
    }
}


var longDescription = `# ***Data Logging Functions***
See the DCL User's Guide for more details on the DCL logger:

[Digital Control Library User's Guide](https://dev.ti.com/tirex/explore/node?node=AKZRbh4oxv98HaO0YKjygQ__gYkahfz__LATEST)

NOTE: The Digital Control Library contains support for fixed point data logging comprising a set
of data buffer functions. It is similar to its floating point counterparts, and so the details below are similar for it.

The Digital Control Library includes a general purpose floating-point data logger utility
which is useful when testing and debugging control applications. The intended use of the
data logger utility is to capture a stream of data values in a block of memory for
subsequent analysis. The data logger is supplied in the form of a C header file and one
assembly file, and it may be used on any C2000 device irrespective of whether the DCL is
used. The utility may not be used on the CLA.

The data logger operates with arrays of 32-bit floating-point data. The location, size, and
indexing of each array are defined by three pointers capturing the start address, end
address, and data index address. All three pointers are held in a common C structure
with the data type “FDLOG”, defined as follows:

    typedef volatile struct {
        float *fptr;
        float *lptr;
        float *dptr;
    } FDLOG;

Conceptually, the relationship between the array pointers and the elements of a data
array of length “N” is shown below:

*Figure: Data log pointer allocation*

![](../../libraries/.meta/control/dcl/images/figures_scaled/LOGGER_Data_log_pointer_allocation-Figure34.png)

The data index pointer (dptr) always points to the next address to be written or read, and
advances through the memory block as each new data value is written into the log. On
reaching the end of the log, the pointer is reset to the first address in the log. The data
logger header file contains a set of in-line C functions to access and manipulate data logs.

The log pointers can then be initialized in the user's code such that they reference a
memory block in a specific address range. Thereafter, the code can clear or load the
buffer a specific data value, and then begin writing data into it using the
DCL_writeLog() function. The DF22 example project shows how this is done.

The DCL also contains two functions which perform fast read and write to a data log.
These are assembly coded functions in the source file DCL_frwlog.asm.
`

var controllerModule = {
    c2000wareLibraryName: "LOGGER",
    displayName: "LOGGER",
    defaultInstanceName: "myLOGGER",
    description: "LOGGER",
    longDescription:longDescription,
    config: config,
    references : [],
    templates: {
        c2000ware_libraries_c           : "/libraries/control/dcl/templates/logger.c2000ware_libraries.c.xdt",
        c2000ware_libraries_h           : "/libraries/control/dcl/templates/logger.c2000ware_libraries.h.xdt",
    },
    validate : onValidate,
    modules: (inst) => {
        var mods = [];
        var refFilesArr = logger_data.getRefFilesModuleArrFromControlStruct(inst.structDisplay);
        mods = refFilesArr;
        return mods;
    }
};

exports = controllerModule;