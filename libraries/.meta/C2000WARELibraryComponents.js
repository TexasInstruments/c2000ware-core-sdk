let Common   = system.getScript("/driverlib/Common.js");
let references = system.getScript("/libraries/C2000WARELibraryReferences.js");

let CATEGORY_FATFS = "FATFS";
let CATEGORY_CALIBRATION = "CALIBRATION"
let CATEGORY_CONTROL = "CONTROL"
let CATEGORY_MATH = "MATH"
let CATEGORY_DSP = "DSP"
let CATEGORY_COMMS = "COMMUNICATIONS"

var supported_modules_fatfs = [];
var supported_modules_calibration = [];
var supported_modules_control = [];
var supported_modules_math = [];
var supported_modules_dsp = [];
var supported_modules_comms = [];

var supported_modules = {};
supported_modules[CATEGORY_FATFS] = supported_modules_fatfs
supported_modules[CATEGORY_CALIBRATION] = supported_modules_calibration
supported_modules[CATEGORY_CONTROL] = supported_modules_control
supported_modules[CATEGORY_MATH] = supported_modules_math
supported_modules[CATEGORY_DSP] = supported_modules_dsp
supported_modules[CATEGORY_COMMS] = supported_modules_comms

var supported_library_moduleFile = [
     { moduleCategory: CATEGORY_FATFS ,  moduleName : "FATFS", moduleFile : "/libraries/fatfs/fatfs.js"},
     { moduleCategory: CATEGORY_CALIBRATION ,  moduleName : "HRPWM SFO", moduleFile : "/libraries/calibration/hrpwm/sfo.js"},
     { moduleCategory: CATEGORY_CONTROL ,  moduleName : "REFGEN", moduleFile : "/libraries/control/dcl/refgen.js"},
     { moduleCategory: CATEGORY_CONTROL ,  moduleName : "LOGGER", moduleFile : "/libraries/control/dcl/logger.js"},
     { moduleCategory: CATEGORY_CONTROL ,  moduleName : "CONTROLLER", moduleFile : "/libraries/control/dcl/controller.js"},
     { moduleCategory: CATEGORY_CONTROL ,  moduleName : "TCM", moduleFile : "/libraries/control/dcl/tcm.js"},
];

var device_specific_modules = [
    { moduleCategory: CATEGORY_DSP ,  moduleName : "FFT", moduleFile : "/libraries/dsp/FPU/FFT/FFT.js",                     devices: ["F28P65x", "F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x"]},
    { moduleCategory: CATEGORY_DSP ,  moduleName : "Filter", moduleFile : "/libraries/dsp/FPU/Filter/Filter.js",            devices: ["F28P65x", "F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x"]},
    { moduleCategory: CATEGORY_DSP ,  moduleName : "Vector", moduleFile : "/libraries/dsp/FPU/Vector/Vector.js",            devices: ["F28P65x", "F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x"]},
    { moduleCategory: CATEGORY_DSP ,  moduleName : "VCU VCRC", moduleFile : "/libraries/dsp/VCU/VCRC/vcrc.js",              devices: ["F28P65x", "F28002x", "F28003x", "F2838x"]},
    { moduleCategory: CATEGORY_MATH ,  moduleName : "FASTINTDIV", moduleFile : "/libraries/math/FASTINTDIV/fastintdiv.js",  devices: ["F28P65x", "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x"]},
    { moduleCategory: CATEGORY_MATH ,  moduleName : "FPUfastRTS", moduleFile : "/libraries/math/FPUfastRTS/FPUfastRTS.js",  devices: ["F28P65x", "F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x"]},
    { moduleCategory: CATEGORY_MATH ,  moduleName : "IQmath", moduleFile : "/libraries/math/IQmath/IQmath.js",              devices: ["F28P65x", "F280013x", "F280015x", "F28002x", "F28003x", "F28004x", "F2807x", "F2837xD", "F2837xS", "F2838x"]},
    { moduleCategory: CATEGORY_COMMS ,  moduleName : "USB", moduleFile : "/libraries/communications/usb/usb.js",              devices: ["F2807x","F2837xD", "F2837xS", "F2838x"]},
]

for (var library_moduleFile in supported_library_moduleFile)
{
    supported_modules[supported_library_moduleFile[library_moduleFile].moduleCategory].
        push(supported_library_moduleFile[library_moduleFile].moduleFile)
}


for (var device_specific_modules_index in device_specific_modules)
{   
    if (device_specific_modules[device_specific_modules_index].
        devices.includes(Common.getDeviceName()))
    {
        supported_modules[device_specific_modules[device_specific_modules_index].moduleCategory].
            push(device_specific_modules[device_specific_modules_index].moduleFile)
    }
}

var categories_filtered= []
categories_filtered.push({
    displayName: CATEGORY_FATFS,
    modules: supported_modules[CATEGORY_FATFS]
})
categories_filtered.push({
    displayName: CATEGORY_CALIBRATION,
    modules: supported_modules[CATEGORY_CALIBRATION]
})
categories_filtered.push({
    displayName: CATEGORY_CONTROL,
    modules: supported_modules[CATEGORY_CONTROL]
})
categories_filtered.push({
    displayName: CATEGORY_MATH,
    modules: supported_modules[CATEGORY_MATH]
})
categories_filtered.push({
    displayName: CATEGORY_DSP,
    modules: supported_modules[CATEGORY_DSP]
})
categories_filtered.push({
    displayName: CATEGORY_COMMS,
    modules: supported_modules[CATEGORY_COMMS]
})

exports = {
    displayName: "C2000Ware Libraries",
    templates: [
    
        {
            name      : "/libraries/c2000ware_libraries.cmd.genlibs.xdt",
            outputPath: "c2000ware_libraries.cmd.genlibs",
            alwaysRun : true
        },
        {
            name      : "/libraries/c2000ware_libraries.opt.xdt",
            outputPath: "c2000ware_libraries.opt",
            alwaysRun : true
        },
        {
            name      : "/libraries/c2000ware_libraries.c.xdt",
            outputPath: "c2000ware_libraries.c",
            alwaysRun : true
        },
        {
            name      : "/libraries/c2000ware_libraries.h.xdt",
            outputPath: "c2000ware_libraries.h",
            alwaysRun : true
        },
		{
            name: "/libraries/communications/usb/templates/usb_structs.c.xdt",
            outputPath: "usb_structs.c",
			alwaysRun : false
        },
		{
            name: "/libraries/communications/usb/templates/usb_structs.h.xdt",
            outputPath: "usb_structs.h",
			alwaysRun : false
        }
    ],
    references: references.componentReferences,
    topModules: [

        {
            displayName: "C2000Ware Libraries",
            description: "C2000Ware Libraries",
            categories: categories_filtered
        },
    ],
    
}