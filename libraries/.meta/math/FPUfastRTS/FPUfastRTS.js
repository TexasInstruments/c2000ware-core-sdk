let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
//Even though lack of letter at end indicates unsigned truncation, not the case for floating point FID
/*
sincosf | Takes in floating point radian as first parameter, and then pointers for sine and cosine as next parameters, respectively; void function, edits pointer values | 44
sincos | Takes in floating point radian as first parameter, and then pointers for sine and cosine as next parameters, respectively; void function, edits pointer values | 73
    {name: "sincosf",                                   displayName: "Sine and Cosine Function",        longDescription: "void sincosf(float32_t radian, float32_t *PtrSin, float32_t *PtrCos)"},
    {name: "sincos",                                    displayName: "Sine and Cosine Function",        longDescription: "void sincos(float64u_t radian, float64u_t *PtrSin, float64u_t *PtrCos)"},
*/
let longDescription = `
Note: All trigonometric functions are in radians, and all fast integer division functions use pointers.

FID Parameter Format:

Parameter 1: Numerator upon input, remainder upon return

Parameter 2: Denominator upon input, quotient upon return

NOTE: CORDIC functions use the struct float64u_t as the input parameter for the angle theta (in radians).

NOTE: FID functions missing an underscore with a letter at the end of the name are unsigned truncated types (meaning even if they're with signed values, they return unsigned)

**Please refer to the [user guide](https://dev.ti.com/tirex/explore/node?node=AAXq6WkxDehegG05qPHc.Q__gYkahfz__LATEST) for more details regarding function return types and parameters**
`
let longDescriptionFPU32 = `
**Arc tangent calculates within range -90 to 90 degrees, and arc tangent 2 calculates within range -180 to 180 degrees**

Function | Description | Approx. Cycles
--- | --- | ---
acosf | Takes in floating point value for parameter, returns floating point value in radians (within range of negative pi to positive pi) | 30
asinf | Takes in floating point value for parameter, returns floating point value in radians (within range of negative pi to positive pi) | 30
atanf | Takes in floating point value for parameter, returns floating point value in radians (within range of negative pi to positive pi) | 49
atan2f | Takes in floating point value for parameter, returns floating point value of 4-quadrant arctangent in radians (within range of negative pi to positive pi) | 50
cosf | Takes in floating point value in radians for parameter, returns cosine in floating point value | 38
FS$$DIV (use '/' operator for division) | Takes in floating point value for parameters, returns first parameter divided by second parameter in floating point (quotient only); has special cases | 25
expf | Takes in floating point value for parameter, returns exponent of value in floating point (input domain is limited to +/-log(FLT_MAX) (< +/-89)) | 61
isqrtf | Takes in floating point value for parameter, returns (1.0 / square root of value) in floating point | 26
logf | Takes in floating point value for parameter, returns natural logarithm of value in floating point (input >= 1.0) | 57
powf | Takes in floating point parameters, where the first parameter is the base and the second is the exponent, returns power in floating point (first input >= 1.0) | 109
sinf | Takes in floating point value in radians for parameter, returns sine in floating point value | 38
sqrtf | Takes in floating point value for parameter, returns square root of value in floating point | 29
`
let longDescriptionFPU64 = `
**Arc tangent calculates within range -90 to 90 degrees, and arc tangent 2 calculates within range -180 to 180 degrees**

Function | Description | Approx. Cycles
--- | --- | ---
atan | Takes in floating point value for parameter, returns floating point value in radians (within range of negative pi to positive pi) | 78
atan2 | Takes in floating point value for parameter, returns floating point value of 4-quadrant arctangent in radians (within range of negative pi to positive pi) | 81
cos | Takes in floating point value in radians for parameter, returns cosine in floating point value | 63
CORDIC_F64_cos | Takes in struct of CORDIC_F64 (see c2000ware_libraries.h header file for details) and theta value in float64u_t structure form in F64 field, returns as float64u_t in F64 field | 2735*
FS$$DIV (use '/' operator for division) | Takes in floating point value for parameters, returns first parameter divided by second parameter in floating point (quotient only); has special cases | 51
FID Functions | [See long description under Fast Integer Division section below] | (see FID section)
isqrt | Takes in floating point value for parameter, returns (1.0 / square root of value) in floating point | 59
sin | Takes in floating point value in radians for parameter, returns sine in floating point value | 63
CORDIC_F64_sin | Takes in struct of CORDIC_F64 (see c2000ware_libraries.h header file for details) and theta value in float64u_t structure form in F64 field, returns as float64u_t in F64 field | 2736*
sqrt | Takes in floating point value for parameter, returns square root of value in floating point | 63

*The CORDIC functions trade off speed for accuracy of results
CORDIC Globals:
<name>_N_ITERATIONS = Number of Iterations
<name>_handle = Handle for the CORDIC object (of type CORDIC_F64_Handle)
`
let longDescriptionFID = `
Functions take parameters in format of: (int16_t *p_num_rem, int16_t *p_den_quo), where the first parameter is numerator upon input and remainder upon output,
and the second parameter is the denominator upon input and quotient upon output

**NOTE:** Exception to this format is the F64 by F63 function (first in the table below), which has the parameters: (double *p_num, double *p_den, double *p_quo),
where *p_num is the numerator, *p_den is the denominator, and *p_quo is the quotient result

Function | Description | Approx. Cycles
--- | --- | ---
FID_f64byf64      | Performs 64-bit floating point division, floating point quotient in parameter pointer         | 36
FID_i16byi16_e    | Performs signed integer euclidean division (signed 16-bit by signed signed 16-bit)            | 26
FID_i16byi16_m    | Performs signed integer modulo division (signed 16-bit by signed signed 16-bit)               | 26
FID_i16byi16_t    | Performs signed integer truncated division (signed 16-bit by signed 16-bit)                   | 26
FID_i32byi16_e    | Performs signed integer euclidean division (signed 32-bit by signed 16-bit)                   | 28
FID_i32byi16_m    | Performs signed integer modulo division (signed 32-bit by signed 16-bit)                      | 28
FID_i32byi16_t    | Performs signed integer truncated division (signed 32-bit by signed 16-bit)                   | 28
FID_i32byi32_e    | Performs signed integer euclidean division (signed 32-bit by signed 32-bit)                   | 24
FID_i32byi32_m    | Performs signed integer modulo division (signed 32-bit by signed 32-bit)                      | 24
FID_i32byi32_t    | Performs signed integer truncated division (signed 32-bit by signed 32-bit)                   | 24
FID_i32byui32     | Performs signed integer, unsigned truncated division (signed 32-bit by unsigned 32-bit)       | 24
FID_i64byi32_e    | Performs signed integer euclidean division (signed 64-bit by signed 16-bit)                   | 36
FID_i64byi32_m    | Performs signed integer modulo division (signed 64-bit by signed 16-bit)                      | 36
FID_i64byi32_t    | Performs signed integer truncated division (signed 64-bit by signed 16-bit)                   | 36
FID_i64byi64_e    | Performs signed integer euclidean division (signed 64-bit by signed 16-bit)                   | 51
FID_i64byi64_m    | Performs signed integer modulo division (signed 64-bit by signed 16-bit)                      | 51
FID_i64byi64_t    | Performs signed integer truncated division (signed 64-bit by signed 16-bit)                   | 51
FID_i64byui32     | Performs signed integer, unsigned truncated division (signed 64-bit by unsigned 32-bit)       | 38
FID_ui16byui16    | Performs unsigned integer, unsigned truncated division (unsigned 16-bit by unsigned 16-bit)   | 24
FID_ui32byui16    | Performs unsigned integer, unsigned truncated division (unsigned 32-bit by unsigned 16-bit)   | 26
FID_ui32byui32    | Performs unsigned integer, unsigned truncated division (unsigned 32-bit by unsigned 32-bit)   | 23
FID_ui64byui32    | Performs unsigned integer, unsigned truncated division (unsigned 64-bit by unsigned 32-bit)   | 35
FID_i64byui64     | Performs signed integer, unsigned truncated division (signed 64-bit by unsigned 64-bit)       | 52
FID_ui64byui64    | Performs unsigned integer, unsigned truncated division (unsigned 64-bit by unsigned 64-bit)   | 51
`

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

let TMU_TYPE = [
    {name: "NONE",     displayName: "NONE"},
    {name: "TMU0",     displayName: "TMU0"},
    {name: "TMU1",     displayName: "TMU1"}
]
let FPU32_FUNCTIONS = [
    {name: "acosf",                                     displayName: "Arc Cosine (TMU support)",        longDescription: "float32_t acosf(float32_t X)"},
    {name: "asinf",                                     displayName: "Arc Sine (TMU support)",          longDescription: "float32_t asinf(float32_t X)"},
    {name: "atanf",                                     displayName: "Arc Tangent",                     longDescription: "float32_t atanf(float32_t X)"},
    {name: "atan2f",                                    displayName: "Arc Tangent 2",                   longDescription: "float32_t atan2f(float32_t Y, float32_t X)"},
    {name: "cosf",                                      displayName: "Cosine",                          longDescription: "float32_t cosf(float32_t X)"},
    {name: "FS$$DIV (use '/' operator for division)",   displayName: "Divide",                          longDescription: "float32_t FS$$DIV(float32_t X, float32_t Y); use '/' operator"},
    {name: "expf",                                      displayName: "Exponential",                     longDescription: "float32_t expf(float32_t X)"},
    {name: "isqrtf",                                    displayName: "Inverse Square Root",             longDescription: "float32_t isqrtf(float32_t X)"},
    {name: "logf",                                      displayName: "Natural Logarithm",               longDescription: "float32_t logf(float32_t X)"},
    {name: "powf",                                      displayName: "Power",                           longDescription: "float32_t powf(float32_t X, float32_t Y)"},
    {name: "sinf",                                      displayName: "Sine",                            longDescription: "float32_t sinf(float32_t X)"},
    {name: "sqrtf",                                     displayName: "Square Root",                     longDescription: "float32_t sqrtf(float32_t X)"}
]
let FPU64_FUNCTIONS = [
    {name: "atan",                                      displayName: "Arc Tangent",                     longDescription: "float64u_t atan(float64u_t X)"},
    {name: "atan2",                                     displayName: "Arc Tangent 2",                   longDescription: "float64u_t atan2(float64u_t Y, float64u_t X)"},
    {name: "cos",                                       displayName: "Cosine",                          longDescription: "float64u_t cos(float64u_t X)"},
    {name: "CORDIC_F64_cos",                            displayName: "Cosine (CORDIC rotation)",        longDescription: "float64u_t CORDIC_F64_cos(CORDIC_F64_Handle hC, float64u_t theta)"},
    {name: "FS$$DIV (use '/' operator)",                displayName: "Divide (COFF)",                   longDescription: "float64_t FD$$DIV(float64_t , float64_t) for COFF"},
    {name: "__c28xabi_div (use '/' operator)",          displayName: "Divide (EABI)",                   longDescription: "float64u_t __c28xabi_div(float64u_t X, float64u_t Y) for EABI"},
    {name: "isqrt",                                     displayName: "Inverse Square Root",             longDescription: "float64u_t isqrt(float64u_t X)"},
    {name: "sin",                                       displayName: "Sine",                            longDescription: "float64u_t sin(float64u_t X)"},
    {name: "CORDIC_F64_sin",                            displayName: "Sine (CORDIC Rotation)",          longDescription: "float64u_t CORDIC_F64_sin(CORDIC_F64_Handle hC, float64u_t theta)"},
    {name: "sqrt",                                      displayName: "Square Root",                     longDescription: "float64u_t sqrt(float64u_t X)"}
]
let FID_TYPES = [
    {name: "FID_f64byf64 (COFF)",   longDescription: "Float 64 / Float 64 (COFF)",                                                  displayName: "void FID_f64byf64(long double *p_num, long double *p_den, long double *p_quo)"},
    {name: "FID_f64byf64 (EABI)",   longDescription: "Float 64 / Float 64 (EABI)",                                                  displayName: "void FID_f64byf64(double *p_num, double *p_den, double *p_quo)"},
    {name: "FID_i16byi16_e",        longDescription: "Integer 16 / Integer 16 Euclidean",                                           displayName: "void FID_i16byi16_e(int16_t *p_num_rem, int16_t *p_den_quo)"},
    {name: "FID_i16byi16_m",        longDescription: "Integer 16 / Integer 16 Modulo",                                              displayName: "void FID_i16byi16_m(int16_t *p_num_rem, int16_t *p_den_quo)"},
    {name: "FID_i16byi16_t",        longDescription: "Integer 16 / Integer 16 Truncated",                                           displayName: "void FID_i16byi16_t(int16_t *p_num_rem, int16_t *p_den_quo)"},
    {name: "FID_i32byi16_e",        longDescription: "Integer 32 / Integer 16 Euclidean",                                           displayName: "void FID_i32byi16_e(int32_t *p_num_rem, int32_t *p_den_quo)"},
    {name: "FID_i32byi16_m",        longDescription: "Integer 32 / Integer 16 Modulo",                                              displayName: "void FID_i32byi16_m(int32_t *p_num_rem, int32_t *p_den_quo)"},
    {name: "FID_i32byi16_t",        longDescription: "Integer 32 / Integer 16 Truncated",                                           displayName: "void FID_i32byi16_t(int32_t *p_num_rem, int32_t *p_den_quo)"},
    {name: "FID_i32byi32_e",        longDescription: "Integer 32 / Integer 32 Euclidean",                                           displayName: "void FID_i32byi32_e(int32_t *p_num_rem, int32_t *p_den_quo)"},
    {name: "FID_i32byi32_m",        longDescription: "Integer 32 / Integer 32 Modulo",                                              displayName: "void FID_i32byi32_m(int32_t *p_num_rem, int32_t *p_den_quo)"},
    {name: "FID_i32byi32_t",        longDescription: "Integer 32 / Integer 32 Truncated",                                           displayName: "void FID_i32byi32_t(int32_t *p_num_rem, int32_t *p_den_quo)"},
    {name: "FID_i32byui32",         longDescription: "Integer 32 / Unsigned Integer 32, Unsigned Truncated Division",               displayName: "void FID_i32byui32(int32_t *p_num_rem, int32_t *p_den_quo)"},
    {name: "FID_i64byi32_e",        longDescription: "Integer 64 / Integer 32 Euclidean",                                           displayName: "void FID_i64byi32_e(int64_t *p_num_rem, int64_t *p_den_quo)"},
    {name: "FID_i64byi32_m",        longDescription: "Integer 64 / Integer 32 Modulo",                                              displayName: "void FID_i64byi32_m(int64_t *p_num_rem, int64_t *p_den_quo)"},
    {name: "FID_i64byi32_t",        longDescription: "Integer 64 / Integer 32 Truncated",                                           displayName: "void FID_i64byi32_t(int64_t *p_num_rem, int64_t *p_den_quo)"},
    {name: "FID_i64byi64_e",        longDescription: "Integer 64 / Integer 64 Euclidean",                                           displayName: "void FID_i64byi64_e(int64_t *p_num_rem, int64_t *p_den_quo)"},
    {name: "FID_i64byi64_m",        longDescription: "Integer 64 / Integer 64 Modulo",                                              displayName: "void FID_i64byi64_m(int64_t *p_num_rem, int64_t *p_den_quo)"},
    {name: "FID_i64byi64_t",        longDescription: "Integer 64 / Integer 64 Truncated",                                           displayName: "void FID_i64byi64_t(int64_t *p_num_rem, int64_t *p_den_quo)"},
    {name: "FID_i64byui32",         longDescription: "Integer 64 / Unsigned Integer 32, Unsigned Truncated Division",               displayName: "void FID_i64byui32(int64_t *p_num_rem, int64_t *p_den_quo)"},
    {name: "FID_ui16byui16",        longDescription: "Unsigned Integer 16 / Unsigned Integer 16, Unsigned Truncated Division",      displayName: "void FID_ui16byui16(uint16_t *p_num_rem, uint16_t *p_den_quo)"},
    {name: "FID_ui32byui16",        longDescription: "Unsigned Integer 32 / Unsigned Integer 16, Unsigned Truncated Division",      displayName: "void FID_ui32byui16(uint32_t *p_num_rem, uint32_t *p_den_quo)"},
    {name: "FID_ui32byui32",        longDescription: "Unsigned Integer 32 / Unsigned Integer 32, Unsigned Truncated Division",      displayName: "void FID_ui32byui32(uint32_t *p_num_rem, uint32_t *p_den_quo)"},
    {name: "FID_ui64byui32",        longDescription: "Unsigned Integer 64 / Unsigned Integer 32, Unsigned Truncated Division",      displayName: "void FID_ui64byui32(uint64_t *p_num_rem, uint64_t *p_den_quo)"},
    {name: "FID_i64byui64",         longDescription: "Integer 64 / Unsigned Integer 64, Unsigned Truncated Division",               displayName: "void FID_i64byui64(int64_t *p_num_rem, int64_t *p_den_quo)"},
    {name: "FID_ui64byui64",        longDescription: "Unsigned Integer 64 / Unsigned Integer 64, Unsigned Truncated Division",      displayName: "void FID_ui64byui64(uint64_t *p_num_rem, uint64_t *p_den_quo)"}
]

var fpu32_configs = [];
var fpu64_configs = [];
var fid_configs = [];
var moduleStatic = {
    name: "fpu",
    displayName: "FPU/TMU Global Settings",
    config: [],
    modules: Common.autoForce("fpu", "/libraries/.meta/math/FPU/FPU.js")
}

for(let i = 0; i < FPU32_FUNCTIONS.length; i++)
{
    fpu32_configs = fpu32_configs.concat([
        {
            name: FPU32_FUNCTIONS[i].name,
            displayName     : FPU32_FUNCTIONS[i].displayName,
            hidden          : false,
            default         : FPU32_FUNCTIONS[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 0; i < FPU64_FUNCTIONS.length; i++)
{
    fpu64_configs = fpu64_configs.concat([
        {
            name: FPU64_FUNCTIONS[i].name,
            displayName     : FPU64_FUNCTIONS[i].displayName,
            hidden          : true,
            default         : FPU64_FUNCTIONS[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 0; i < FID_TYPES.length; i++)
{
    fid_configs = fid_configs.concat([
        {
            name: FID_TYPES[i].name,
            displayName     : FID_TYPES[i].longDescription,
            hidden          : true,
            default         : FID_TYPES[i].displayName,
            readOnly        : true
        },
    ])
}

let config = [
    {
        name: "fpuType",
        displayName : "FPU Configuration",
        description : "Choose FPU32 or FPU64 Configuration",
        default     : FPU_TYPE[0].name,
        options     : FPU_TYPE,
        onChange    : onChangeFPU
    },
    {
        name: "tmuType",
        displayName : "TMU Configuration",
        description : "Choose to Enable TMU",
        default     : "NONE",
        getValue    : (inst) => {
            return system.modules["/libraries/math/FPU/FPU.js"].$static.tmuType;
        }
    },
    {
        name        : "fpu32Options",
        displayName : "FPU32 Functions",
        description : "Available functions for the FPU32 configuration",
        longDescription : longDescriptionFPU32,
        config : fpu32_configs
    },
    {
        name        : "fpu64Options",
        displayName : "FPU64 Functions",
        description : "Available functions for the FPU64 configuration",
        longDescription : longDescriptionFPU64,
        config : fpu64_configs
    },
    {
        name        : "fidOptions",
        displayName : "Fast Integer Division Options",
        description : 'Choose a type of fast integer division function.',
        longDescription : longDescriptionFID,
        config      : fid_configs
    },
]

function onCalculateFpu(inst)
{
    return system.modules["/libraries/math/FPU/FPU.js"].$static.fpuType;
}
function onChangeFPU(inst, ui)
{
    if(inst.fpuType == FPU_TYPE[0].name)
    {
        for(let i = 0; i < FPU32_FUNCTIONS.length; i++)
        {
            ui[fpu32_configs[i].name].hidden = false;
        }
        for(let i = 0; i < FPU64_FUNCTIONS.length; i++)
        {
            ui[fpu64_configs[i].name].hidden = true;
        }
        for(let i = 0; i < FID_TYPES.length; i++)
        {
            ui[fid_configs[i].name].hidden = true;
        }
        for(let i = 0; i < FID_TYPES.length; i++)
        {
            ui[fid_configs[i].name].hidden = true;
        }
    }
    else if(((Common.getDeviceName() == "F2838x") || (Common.getDeviceName() == "F28P65x")) && (inst.fpuType == FPU_TYPE[1].name))
    {
        for(let i = 0; i < FPU32_FUNCTIONS.length; i++)
        {
            ui[fpu32_configs[i].name].hidden = true;
        }
        for(let i = 0; i < FPU64_FUNCTIONS.length; i++)
        {
            ui[fpu64_configs[i].name].hidden = false;
        }
        for(let i = 0; i < FID_TYPES.length; i++)
        {
            ui[fid_configs[i].name].hidden = false;
        }
    }
}
function onValidate(inst, validation){
    var fpuMod = system.modules["/libraries/math/FPU/FPU.js"];
    if(fpuMod)
    {
        if(fpuMod.$static.fpuType != inst.fpuType)
        {
            validation.logError(system.getReference(fpuMod.$static, "fpuType") + " must be the same across modules.", inst, "fpuType");
        }
    }
}
function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["FPUfastRTS"]));
}
var ffrModule = {
    c2000wareLibraryName: "FFR",
    displayName: "FPUfastRTS",
    defaultInstanceName: "myFFR",
    description: "Floating Point Unit Fast Run Time Support",
    longDescription: longDescription,
    filterHardware : filterHardware,
    maxInstances   : 1,
    config: config,
    moduleInstances : (inst) => {
        var cordicInstance = [];

        if(((Common.getDeviceName() == "F2838x") || (Common.getDeviceName() == "F28P65x")) && (inst.fpuType == FPU_TYPE[1].name))
        {
            cordicInstance.push({
                displayName: "CORDIC Configurations",
                name: "cordic",
                description: "",
                useArray : true,
                moduleName: "/libraries/math/FPUfastRTS/cordic.js",
            });
        }
        return (cordicInstance);
    },
    templates: {
        c2000ware_libraries_h           : "/libraries/math/FPUfastRTS/templates/FPUfastRTS.c2000ware_libraries.h.xdt",
        c2000ware_libraries_c           : "/libraries/math/FPUfastRTS/templates/FPUfastRTS.c2000ware_libraries.c.xdt",
        c2000ware_libraries_opt         : "/libraries/math/FPUfastRTS/templates/FPUfastRTS.c2000ware_libraries.opt.xdt",
        c2000ware_libraries_cmd_genlibs : "/libraries/math/FPUfastRTS/templates/FPUfastRTS.c2000ware_libraries.cmd.genlibs.xdt",
    },
    //moduleStatic: moduleStatic,
    modules: Common.autoForce("fpu", "/libraries/.meta/math/FPU/FPU.js"),
    validate : onValidate
};
exports = ffrModule;
