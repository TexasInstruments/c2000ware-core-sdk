let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
//Object.getOwnPropertyNames(inst)
//Common.printDebugObject()

let longDescription = `For additional information regarding return types, look in the c2000ware_libraries.c file.

**NOTE:** Some return types are preceded by TWO underscores.

**NOTE:** Traditional here means truncated.

For details regarding the different types of division: [**Fast Integer Division Document**](https://www.ti.com/lit/an/spracn6/spracn6.pdf?ts=1648654973770&ref_url=https%253A%252F%252Fwww.google.com%252F)

CPU Cycles for FASTINTDIV:

Function | CPU Cycles
--- | ---
FID_COMP_I16_BY_I16_T      | 16 cycles
FID_COMP_U16_BY_U16_T      | 14 cycles
FID_COMP_I32_BY_I32_T      | 13 cycles
FID_COMP_I32_BY_U32_T      | 14 cycles
FID_COMP_U32_BY_U32_T      | 12 cycles
FID_COMP_I64_BY_I64_T      | 42 cycles
FID_COMP_I64_BY_U64_T      | 42 cycles
FID_COMP_U64_BY_U64_T      | 42 cycles
FID_COMP_I32_BY_I16_T      | 18 cycles
FID_COMP_U32_BY_U16_T      | 13 cycles
FID_COMP_I64_BY_I32_T      | 27 cycles
FID_COMP_I64_BY_U32_T      | 30 cycles
FID_COMP_U64_BY_U32_T      | 26 cycles
FID_COMP_I16_BY_I16_M      | 14 cycles
FID_COMP_I32_BY_I32_M      | 14 cycles
FID_COMP_I32_BY_U32_M      | 14 cycles
FID_COMP_I64_BY_I64_M      | 42 cycles
FID_COMP_I64_BY_U64_M      | 42 cycles
FID_COMP_I32_BY_I16_M      | 16 cycles
FID_COMP_I64_BY_I32_M      | 27 cycles
FID_COMP_I64_BY_U32_M      | 29 cycles
FID_COMP_I16_BY_I16_E      | 14 cycles
FID_COMP_I32_BY_I32_E      | 14 cycles
FID_COMP_I64_BY_I64_E      | 42 cycles
FID_COMP_I64_BY_U64_E      | 42 cycles
FID_COMP_I32_BY_I16_E      | 16 cycles
FID_COMP_I64_BY_I32_E      | 29 cycles
FID_COMP_I64_BY_U32_E      | 29 cycles
`
/* 
FID_COMP_I64_BY_I32_T      | 27 cycles
FID_COMP_I64_BY_U32_T      | 30 cycles
FID_COMP_U64_BY_U32_T      | 26 cycles
FID_COMP_I64_BY_I32_M      | 27 cycles
FID_COMP_I64_BY_U32_M      | 29 cycles
FID_COMP_I64_BY_I32_E      | 29 cycles
FID_COMP_I64_BY_U32_E      | 29 cycles
Numbers were obtained from repeated testing using functions in CCS; tested against given values for other functions,
and those matched the benchmarks, so the values obtained are very likely as accurate as my testing will be
*/

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

let FID_TYPES = [
    {name: "FID_COMP_I16_BY_I16_T",    displayName: "Traditional: int16_t / int16_t"},
    {name: "FID_COMP_U16_BY_U16_T",    displayName: "Traditional: uint16_t / uint16_t"},
    {name: "FID_COMP_I32_BY_I32_T",    displayName: "Traditional: int32_t / int32_t"},
    {name: "FID_COMP_I32_BY_U32_T",    displayName: "Traditional: int32_t / uint32_t"},
    {name: "FID_COMP_U32_BY_U32_T",    displayName: "Traditional: uint32_t / uint32_t"},
    {name: "FID_COMP_I64_BY_I64_T",    displayName: "Traditional: int64_t / int64_t"},
    {name: "FID_COMP_I64_BY_U64_T",    displayName: "Traditional: int64_t / uint64_t"},
    {name: "FID_COMP_U64_BY_U64_T",    displayName: "Traditional: uint64_t / uint64_t"},
    {name: "FID_COMP_I32_BY_I16_T",    displayName: "Traditional: int32_t / int16_t"},
    {name: "FID_COMP_U32_BY_U16_T",    displayName: "Traditional: uint32_t / uint16_t"},
    {name: "FID_COMP_I64_BY_I32_T",    displayName: "Traditional: int64_t / int32_t"},
    {name: "FID_COMP_I64_BY_U32_T",    displayName: "Traditional: int64_t / uint32_t"},
    {name: "FID_COMP_U64_BY_U32_T",    displayName: "Traditional: uint64_t / uint32_t"},
    {name: "FID_COMP_I16_BY_I16_M",    displayName: "Modulo:      int16_t % int16_t"},
    {name: "FID_COMP_I32_BY_I32_M",    displayName: "Modulo:      int32_t % int32_t"},
    {name: "FID_COMP_I32_BY_U32_M",    displayName: "Modulo:      int32_t % uint32_t"},
    {name: "FID_COMP_I64_BY_I64_M",    displayName: "Modulo:      int64_t % int64_t"},
    {name: "FID_COMP_I64_BY_U64_M",    displayName: "Modulo:      int64_t % uint64_t"},
    {name: "FID_COMP_I32_BY_I16_M",    displayName: "Modulo:      int32_t % int16_t"},
    {name: "FID_COMP_I64_BY_I32_M",    displayName: "Modulo:      int64_t % int32_t"},
    {name: "FID_COMP_I64_BY_U32_M",    displayName: "Modulo:      int64_t % uint32_t"},
    {name: "FID_COMP_I16_BY_I16_E",    displayName: "Euclidean:   int16_t / int16_t"},
    {name: "FID_COMP_I32_BY_I32_E",    displayName: "Euclidean:   int32_t / int32_t"},
    {name: "FID_COMP_I64_BY_I64_E",    displayName: "Euclidean:   int64_t / int64_t"},
    {name: "FID_COMP_I64_BY_U64_E",    displayName: "Euclidean:   int64_t / uint64_t"},
    {name: "FID_COMP_I32_BY_I16_E",    displayName: "Euclidean:   int32_t / int16_t"},
    {name: "FID_COMP_I64_BY_I32_E",    displayName: "Euclidean:   int64_t / int32_t"},
    {name: "FID_COMP_I64_BY_U32_E",    displayName: "Euclidean:   int64_t / uint32_t"},
]
let fid_configs = [];
var moduleStatic = {
    name: "fpu",
    displayName: "FPU/TMU Global Settings",
    config: [],
    modules: Common.autoForce("fpu", "/libraries/.meta/math/FPU/FPU.js")
}

for(let i = 0; i < FID_TYPES.length; i++)
{
    fid_configs = fid_configs.concat([
        {
            name: "fid_" + i,
            displayName : FID_TYPES[i].displayName,
            default     : FID_TYPES[i].name,
            readOnly    : true
        },
    ])
}
let config = [
    {
        name: "fpuType",
        displayName : "FPU Configuration",
        default     : FPU_TYPE[0].name,
        getValue    : (inst) => {
            return system.modules["/libraries/math/FPU/FPU.js"].$static.fpuType;
        }
    },
    {
        name: "funcOps",
        displayName : "Function Options",
        config : fid_configs
    }
];

function onValidate(inst, validation){}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["FASTINTDIV"]));
}
var fidModule = {
    c2000wareLibraryName: "FID",
    displayName: "FASTINTDIV",
    defaultInstanceName: "myFID",
    description: "Fast Integer Division",
    longDescription: longDescription,
    filterHardware : filterHardware,
    maxInstances : 1,
    config: config,
    templates: {
        c2000ware_libraries_h           : "/libraries/math/FASTINTDIV/templates/fid.c2000ware_libraries.h.xdt",
        c2000ware_libraries_opt         : "/libraries/math/FASTINTDIV/templates/fid.c2000ware_libraries.opt.xdt",
    },
    moduleStatic: moduleStatic,
    validate : onValidate
};
exports = fidModule;