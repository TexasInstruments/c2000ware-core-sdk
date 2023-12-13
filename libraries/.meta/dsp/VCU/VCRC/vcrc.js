let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let longDescription = `VCRC - This is the latest version of the VCU module which contains only CRC functionality.
 The module supports computation of fixed polynomial 8-bit, 16-bit, 24-bit, or 32-bit CRCs that exist in VCU2. 
 The VCRC module newly supports user configurable polynomials, flexible both in value and size (1 to 32 bits). 
 It also supports user configurable data sizes (1 to 8 bits). 
 
 The software library c28x_vcrc_library_fpu32 and c28x_vcrc_library_fpu64 provide users with APIs that can be used 
 for CRC computation. Note that the fixed polynomial APIs running on VCU-II will run as is on VCRC and these APIs have been 
 also included in the VCRC libraries mentioned. VCRC library provides APIs for:
        
         > Fixed Polynomial for 8, 16, 24 and 32 bit CRC
         > Configurable Polynomial and Size for 1 to 32 bit polynomial and 1 to 8 bits size \n`;

longDescription += "*   [VCRC User Guide](https://dev.ti.com/tirex/explore/node?node=AOyVY9Rz0NHXU4V88GtEFw__gYkahfz__LATEST)\n"

function onChangeVerification (inst,ui) {
    ui["cRoutine"].hidden = !inst["runVerification"];
    ui["crcTable"].hidden = !inst["runVerification"];
    ui["crcTableInputMode"].hidden = !inst["runVerification"];
}

let INPUT_MODE_PREDEFINED = "PREDEFINED"
let INPUT_MODE_MANUAL = "MANUAL"

let INPUT_MODE = [
    {name: INPUT_MODE_PREDEFINED, displayName: "Predefined Input"},
    {name: INPUT_MODE_MANUAL, displayName: "Manual Input"},
]
var moduleStatic = {
    name: "fpu",
    displayName: "FPU/TMU Global Settings",
    config: []
}

function onChangeInputMode(inst,ui)
{
    if (inst.userPolyInputMode == INPUT_MODE_MANUAL) {
        ui.userPoly.hidden = true
        ui.userPolyManual.hidden = false
    }
    if (inst.userPolyInputMode == INPUT_MODE_PREDEFINED) {
        ui.userPoly.hidden = false
        ui.userPolyManual.hidden = true
    }
    if (inst.crcTableInputMode == INPUT_MODE_MANUAL) {
        ui.crcTable.hidden = true
        ui.crcTableManual.hidden = false
    }
    if (inst.crcTableInputMode == INPUT_MODE_PREDEFINED) {
        ui.crcTable.hidden = false
        ui.crcTableManual.hidden = true
    }
    if (inst.cRoutineInputMode == INPUT_MODE_MANUAL) {
        ui.cRoutine.hidden = true
        ui.cRoutineManual.hidden = false
    }
    if (inst.cRoutineInputMode == INPUT_MODE_PREDEFINED) {
        ui.cRoutine.hidden = false
        ui.cRoutineManual.hidden = true
    }
}
/*
function onChangeHWRun(inst, ui)
{
    if (inst.runHwCRC){
        ui.runVerification.hidden = true
        ui.crcTable.hidden = true
        ui.crcTableInputMode.hidden = true
        ui.crcTableManual.hidden = true
        ui.runPredefRoutine.hidden = true
        ui.cRoutine.hidden = true
    } else{
        ui.runVerification.hidden = false
        ui.crcTable.hidden = false
        ui.crcTableInputMode.hidden = false
        ui.crcTableManual.hidden = false
        ui.runPredefRoutine.hidden = false
        ui.cRoutine.hidden = false
    }
}*/
let FPU_TYPE;
if((Common.getDeviceName() == "F2838x") || (Common.getDeviceName() == "F28P65x"))
{
    FPU_TYPE = [
        {name: "FPU32",     displayName: "FPU32"},
        {name: "FPU64",     displayName: "FPU64"}
    ];
}
else
{
    FPU_TYPE = [
        {name: "FPU32",     displayName: "FPU32"}
    ];
}
let data_sizes = [
    {name: 0, displayName: "CRC_SIZE_1_BITS"},
    {name: 1, displayName: "CRC_SIZE_2_BITS"},
    {name: 2, displayName: "CRC_SIZE_3_BITS"},
    {name: 3, displayName: "CRC_SIZE_4_BITS"},
    {name: 4, displayName: "CRC_SIZE_5_BITS"},
    {name: 5, displayName: "CRC_SIZE_6_BITS"},
    {name: 6, displayName: "CRC_SIZE_7_BITS"},
    {name: 7, displayName: "CRC_SIZE_8_BITS"},
    {name: 8, displayName: "CRC_SIZE_9_BITS"},
    {name: 9, displayName: "CRC_SIZE_10_BITS"},
    {name: 10, displayName: "CRC_SIZE_11_BITS"},
    {name: 11, displayName: "CRC_SIZE_12_BITS"},
    {name: 12, displayName: "CRC_SIZE_13_BITS"},
    {name: 13, displayName: "CRC_SIZE_14_BITS"},
    {name: 14, displayName: "CRC_SIZE_15_BITS"},
    {name: 15, displayName: "CRC_SIZE_16_BITS"},
    {name: 16, displayName: "CRC_SIZE_17_BITS"},
    {name: 17, displayName: "CRC_SIZE_18_BITS"},
    {name: 18, displayName: "CRC_SIZE_19_BITS"},
    {name: 19, displayName: "CRC_SIZE_20_BITS"},
    {name: 20, displayName: "CRC_SIZE_21_BITS"},
    {name: 21, displayName: "CRC_SIZE_22_BITS"},
    {name: 22, displayName: "CRC_SIZE_23_BITS"},
    {name: 23, displayName: "CRC_SIZE_24_BITS"},
    {name: 24, displayName: "CRC_SIZE_25_BITS"},
    {name: 25, displayName: "CRC_SIZE_26_BITS"},
    {name: 26, displayName: "CRC_SIZE_27_BITS"},
    {name: 27, displayName: "CRC_SIZE_28_BITS"},
    {name: 28, displayName: "CRC_SIZE_29_BITS"},
    {name: 29, displayName: "CRC_SIZE_30_BITS"},
    {name: 30, displayName: "CRC_SIZE_31_BITS"},
    {name: 31, displayName: "CRC_SIZE_32_BITS"},
]

let crc_options = [
    {name: "CRC_runConfigPolyBytesReflected", displayName: "CRC_runConfigPolyBytesReflected"},
    {name: "CRC_runConfigPolyBitsReflected" , displayName: "CRC_runConfigPolyBitsReflected"},
    {name: "CRC_runConfigPolyBytes", displayName: "CRC_runConfigPolyBytes"},
    {name: "CRC_runConfigPolyBits" , displayName: "CRC_runConfigPolyBits"}
]

let crc_init = [
    {name: "CRC_init8Bit", displayName: "CRC_init8Bit"},
    {name: "CRC_init16Bit", displayName: "CRC_init16Bit"},
    {name: "CRC_init24Bit", displayName: "CRC_init24Bit"},
    {name: "CRC_init32Bit", displayName: "CRC_init32Bit"},
]

let crc_routines = [
    {name: "CRC_run16BitTableLookupC", displayName: "CRC_run16BitTableLookupC"},
    {name: "CRC_run16BitReflectedTableLookupC", displayName: "CRC_run16BitReflectedTableLookupC"},
    {name: "CRC_run32BitTableLookupC", displayName: "CRC_run32BitTableLookupC"},
    {name: "CRC_run32BitReflectedTableLookupC", displayName: "CRC_run32BitReflectedTableLookupC"},
]

let parity = [
    {name: "CRC_parity_even", displayName: "CRC_parity_even"},
    {name: "CRC_parity_odd", displayName: "CRC_parity_odd"}
]

let polynomial = [
    {name: '0x0003', displayName: '0x0003'},
    {name: '0x0007', displayName: '0x0007'},
    {name: '0x1021', displayName: '0x1021'},
    {name: '0x8005', displayName: '0x8005'},
    {name: '0x04C11DB7', displayName: '0x04C11DB7'},
    {name: '0x1EDC6F41', displayName: '0x1EDC6F41'}
]

let crc_tables = [
    {name: "crc8Table", displayName: "crc8Table"},
    {name: "crc8TableReflected", displayName: "crc8TableReflected"},
    {name: "crc16P1Table", displayName: "crc16P1Table"},
    {name: "crc16P2Table", displayName: "crc16P2Table"},
    {name: "crc16P1TableReflected", displayName: "crc16P1TableReflected"},
    {name: "crc16P2TableReflected", displayName: "crc16P2TableReflected"},
    {name: "crc24Table", displayName: "crc24Table"},
    {name: "crc24TableReflected", displayName: "crc24TableReflected"},
    {name: "crc32P1Table", displayName: "crc32P1Table"},
    {name: "crc32P2Table", displayName: "crc32P2Table"},
    {name: "crc32P1TableReflected", displayName: "crc32P1TableReflected"},
    {name: "crc32P2TableReflected", displayName: "crc32P2TableReflected"}
]

let config = [
    {
        name: "fpuType",
        displayName : "FPU Configuration",
        description : "Choose FPU32 or FPU64 Configuration",
        default     : FPU_TYPE[0].name,
        options     : FPU_TYPE
    },
    {
        name: "crcConfig",
        displayName : "CRC Configuration",
        description : '',
        collapsed   : false,
        config      :[
            {
                name: "seedVal",
                displayName : "Seed Value",
                description : 'Enter the seed value for CRC computation',
                hidden      : false,
                default     : '0x0'
            },
            {
                name: "numMsgBytes",
                displayName : "Number of Bytes",
                description : 'Enter the number of bytes on which the CRC is to be calculated',
                hidden      : false,
                default     : 0
            },
            {
                name: "numMsgBits",
                displayName : "Number of Bits",
                description : 'Enter the number of bits for CRC computation',
                hidden      : false,
                default     : 0
            },
            {
                name: "parity",
                displayName : "Parity",
                description : 'Choose to compute CRC for lower byte or upper byte first ',
                hidden      : false,
                default     : parity[0].name,
                options     : parity
            },
            {
                name: "result",
                displayName : "CRC Result",
                description : 'Variable for storing CRC result',
                hidden      : true,
                default     : 0
            },
            {
                name: "msgBuffer",
                displayName : "Message Buffer Variable",
                description : "Void pointer to function/variable of source address.",
                hidden      : false,
                default     : "testInput",
            },
            {
                name: "userPolyInputMode",
                displayName : "Polynomial Input Type",
                description : 'Type of start address input.',
                hidden      : false,
                default     : INPUT_MODE[0].name,
                options     : INPUT_MODE,
                onChange    : onChangeInputMode
            },
            {
                name: "userPoly",
                displayName : "Predefined Polynomial",
                description : "User polynomial",
                hidden      : false,
                default     : polynomial[0].name,
                options     : polynomial
            },
            {
                name: "userPolyManual",
                displayName : "Manual Polynomial Entry",
                description : 'User polynomial',
                hidden      : true,
                default     : '0x0'
            },
            {
                name: "polySize",
                displayName : "Polynomial Size",
                description : "User polynomial Size",
                hidden      : false,
                default     : data_sizes[3].name,
                options     : data_sizes
            },
            {
                name: "dataSize",
                displayName : "Data Size",
                description : "",
                hidden      : false,
                default     : data_sizes[0].name,
                options     : data_sizes
            },
            {
                name: "reflected",
                displayName : "Reflected",
                description : "Whether the computation is to be done from LSB or MSB",
                hidden      : false,
                default     : false
            },
            {
                name: "crcInit",
                displayName : "CRC Init Routine",
                description : "initialize the CRC routine by context save and context restore calls",
                hidden      : false,
                default     : crc_init[0].name,
                options     : crc_init
            },
        ]
    },
    {
        name: "runConfig",
        displayName : "Hardware CRC Computation",
        description : "",
        collapsed   : false,
        config      : [
            {
                name: "crcRun",
                displayName : "Hardware CRC Functions",
                description : "",
                hidden      : false,
                default     : crc_options[0].name,
                options     : crc_options
            },
        ]
    },
    {
        name: "verificationConfig",
        displayName : "Software CRC Verification (Development Purposes Only)",
        description : "",
        collapsed   : false,
        config      : [
            {
                name: "runVerification",
                displayName : "Use SW CRC for Verification",
                description : "Calculate Golden Value & Run CRC with SW",
                hidden      : false,
                default     : true,
                onChange    : onChangeVerification
            },
            {
                name: "crcTableInputMode",
                displayName : "CRC Table Input Type",
                description : 'Type of input.',
                hidden      : false,
                default     : INPUT_MODE[0].name,
                options     : INPUT_MODE,
                onChange    : onChangeInputMode
            },
            {
                name: "crcTable",
                displayName : "CRC Table",
                description : "Void pointer to function/variable of source address.",
                hidden      : false,
                default     : crc_tables[0].name,
                options     : crc_tables
            },
            {
                name: "crcTableManual",
                displayName : "CRC Table Name",
                description : "Void pointer to function/variable of source address.",
                hidden      : true,
                default     : ''
            },
            {
                name: "cRoutineInputMode",
                displayName : "C Routine Input Type",
                description : 'Type of input.',
                hidden      : false,
                default     : INPUT_MODE[0].name,
                options     : INPUT_MODE,
                onChange    : onChangeInputMode
            },
            {
                name: "cRoutine",
                displayName : "Predefined C Routine",
                description : "Point to the C Routine",
                hidden      : false,
                default     : crc_routines[0].name,
                options     : crc_routines
            },
            {
                name: "cRoutineManual",
                displayName : "C Routine Function Name",
                description : "Void pointer to function/variable of source address.",
                hidden      : true,
                default     : ''
            },
        ],
    },
    {
        name: "runCRC",
        displayName: "Run CRC",
        default: false
    }
]

function onValidate(inst, validation) {
    var fpuMod = system.modules["/libraries/math/FPU/FPU.js"];
    if(fpuMod)
    {
        if(fpuMod.$static.fpuType != inst.fpuType)
        {
            validation.logError(system.getReference(fpuMod.$static, "fpuType") + " must be the same across modules.", inst, "fpuType");
        }
    }

    if (inst.userPolyManual < 0x0 || inst.userPolyManual > 0xFFFFFFFF){
        validation.logError(
            "Please enter a valid 0-32 bit polynomial", 
            inst, "userPolyManual");
    }

    if (inst.seedValue < 0x0 || inst.seedValue > 0xFFFFFFFF){
        validation.logError(
            "Please enter a valid 0-32 bit polynomial", 
            inst, "seedValue");
    }

}

var vcrcModule = {
    c2000wareLibraryName: "VCRC",
    displayName: "VCRC",
    defaultInstanceName: "myVCRC",
    description: "VCRC computation module",
    longDescription: longDescription,
    //moduleInstances: moduleInstances,
    //sharedModuleInstances: sharedModuleInstances,
    modules: Common.autoForce("fpu", "/libraries/.meta/math/FPU/FPU.js"),
    config: config,
    templates: {
        c2000ware_libraries_h           : "/libraries/dsp/VCU/VCRC/templates/vcrc.c2000ware_libraries.h.xdt",
        c2000ware_libraries_c           : "/libraries/dsp/VCU/VCRC/templates/vcrc.c2000ware_libraries.c.xdt",
        c2000ware_libraries_opt         : "/libraries/dsp/VCU/VCRC/templates/vcrc.c2000ware_libraries.opt.xdt",
        c2000ware_libraries_cmd_genlibs : "/libraries/dsp/VCU/VCRC/templates/vcrc.c2000ware_libraries.cmd.genlibs.xdt",
    },
    validate    : onValidate,
};
exports = vcrcModule;