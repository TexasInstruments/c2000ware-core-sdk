let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let longDescription = `
**NOTE: The IQmath module is included for backwards compatibility. Although it can be used otherwise, the FPU is faster and more precise.**

The 'N' attached to certain data types and functions in IQmath indicates the range and precision of the data type, as shown in the table below:

![Image Missing](../../libraries/.meta/math/IQmath/references/range_and_resolution.png)

**Please refer to the [user guide](https://dev.ti.com/tirex/explore/node?node=AGkVld9Wc1hSJJ2ueeKPTg__gYkahfz__LATEST) for more details**
`

let FORMAT_CONVERSIONS = [
    {name: "_IQ",               displayName: "Floating point to IQ value",                              longDescription: "_iq _IQ(float F)"},
    {name: "_IQN",              displayName: "Floating point to IQ value (N=1:30)",                     longDescription: "_iqN _IQN(float F)"},
    {name: "_IQtoF",            displayName: "IQ value to floating point",                              longDescription: "float _IQtoF(_iq A)"},
    {name: "_IQNtoF",           displayName: "IQ value to floating point (N=1:30)",                     longDescription: "float _IQNtoF(_iqN A)"},
    {name: "_atoIQ",            displayName: "Float ASCII string to IQ",                                longDescription: "_iq _atoIQ(char *S)"},
    {name: "_atoIQN",           displayName: "Float ASCII string to IQ (N=1:30)",                       longDescription: "_iqN _atoIQN(char *S)"},
    {name: "_IQtoa",            displayName: "IQ to ASCII string",                                      longDescription: "int _IQtoa(char *S, const *format, long x)"},
    {name: "_IQNtoa",           displayName: "IQ to ASCII string (N=1:30)",                             longDescription: "int _IQNtoa(char *S, const *format, long x)"},
    {name: "_IQint",            displayName: "Extract integer portion of IQ",                           longDescription: "long _IQint(_iq A)"},
    {name: "_IQNint",           displayName: "Extract integer portion of IQ (N=1:30)",                  longDescription: "long _IQNint(_iqN A)"},
    {name: "_IQfrac",           displayName: "Extract fractional portion of IQ",                        longDescription: "_iq _IQfrac(_iq A)"},
    {name: "_IQNfrac",          displayName: "Extract fractional portion of IQ (N=1:30)",               longDescription: "_iqN _IQNfrac(_iqN A)"},
    {name: "_IQtoIQN",          displayName: "Convert IQ number to IQN number (32-bit)",                longDescription: "_iqN _IQtoIQN(_iq A)"},
    {name: "_IQNtoIQ",          displayName: "Convert IQN (32-bit) number to IQ number (N=1:30)",       longDescription: "_iq _IQNtoIQ(_iqN A)"},
    {name: "_IQtoQN",           displayName: "Convert IQ number to QN number (16-bit)",                 longDescription: "int _IQtoQN(_iq A)"},
    {name: "_QNtoIQ",           displayName: "Convert QN (16-bit) number to IQ number (N=1:30)",        longDescription: "_iq _QNtoIQ(int A)"}
]
let MULT_DIV_FUNCTIONS = [
    {name: "_IQmpy2",           displayName: "Multiply by 2 by using a left shift by 1",                longDescription: "_iq _IQmpy2(_Iq A)"},
    {name: "_IQmpy4",           displayName: "Multiply by 4 by using a left shift by 2",                longDescription: "_iq _IQmpy4(_Iq A)"},
    {name: "_IQmpy8",           displayName: "Multiply by 8 by using a left shift by 3",                longDescription: "_iq _IQmpy8(_Iq A)"},
    {name: "_IQmpy16",          displayName: "Multiply by 16 by using a left shift by 4",               longDescription: "_iq _IQmpy16(_Iq A)"},
    {name: "_IQmpy32",          displayName: "Multiply by 32 by using a left shift by 5",               longDescription: "_iq _IQmpy32(_Iq A)"},
    {name: "_IQmpy64",          displayName: "Multiply by 64 by using a left shift by 6",               longDescription: "_iq _IQmpy64(_Iq A)"},
    {name: "_IQdiv2",           displayName: "Division by 2 by using a right shift by 1",               longDescription: "_iq _IQdiv2(_Iq A)"},
    {name: "_IQdiv4",           displayName: "Division by 4 by using a right shift by 2",               longDescription: "_iq _IQdiv4(_Iq A)"},
    {name: "_IQdiv8",           displayName: "Division by 8 by using a right shift by 3",               longDescription: "_iq _IQdiv8(_Iq A)"},
    {name: "_IQdiv16",          displayName: "Division by 16 by using a right shift by 4",              longDescription: "_iq _IQdiv16(_Iq A)"},
    {name: "_IQdiv32",          displayName: "Division by 32 by using a right shift by 5",              longDescription: "_iq _IQdiv32(_Iq A)"},
    {name: "_IQdiv64",          displayName: "Division by 64 by using a right shift by 6",              longDescription: "_iq _IQdiv64(_Iq A)"},
]
let ARITHMETIC_FUNCTIONS = [
    {name: "_IQmpy",            displayName: "IQ Multiplication",                                       longDescription: "_iq _IQmpy(_iq A, _iq B)"},
    {name: "_IQNmpy",           displayName: "IQ Multiplication (N=1:30)",                              longDescription: "_iqN _IQNmpy(_iqN A, _iqN B)"},
    {name: "_IQrmpy",           displayName: "IQ Multiplication with rounding",                         longDescription: "_iq _IQrmpy(_iq A, _iq B)"},
    {name: "_IQNrmpy",          displayName: "IQ Multiplication with rounding (N=1:30)",                longDescription: "_iqN _IQNrmpy(_iqN A, _iqN B)"},
    {name: "_IQrsmpy",          displayName: "IQ multiplication with rounding & saturation",            longDescription: "_iq _IQrsmpy(_iq A, _iq B)"},
    {name: "_IQNrsmpy",         displayName: "IQ multiplication with rounding & saturation (N=1:30)",   longDescription: "_iqN _IQNrsmpy(_iqN A, _iqN B)"},
    {name: "_IQmpyI32",         displayName: "Multiply IQ with 'long' integer",                         longDescription: "_iq _IQmpyI32(_iq A, long B)"},
    {name: "_IQNmpyI32",        displayName: "Multiply IQ with 'long' integer (N=1:30)",                longDescription: "_iqN _IQNmpyI32(_iqN A, long B)"},
    {name: "_IQmpyI32int",      displayName: "Multiply IQ with 'long', return integer part",            longDescription: "long _IQmpyI32int(_iq A, long B)"},
    {name: "_IQNmpyI32int",     displayName: "Multiply IQ with 'long', return integer part (N=1:30)",   longDescription: "long _IQNmpyI32int(_iqN A, long B)"},
    {name: "_IQmpyI32frac",     displayName: "Multiply IQ with 'long', return fraction part",           longDescription: "long _IQmpyI32frac(_iq A, long B)"},
    {name: "_IQNmpyI32frac",    displayName: "Multiply IQ with 'long', return fraction part (N=1:30)",  longDescription: "long _IQNmpyI32frac(_iqN A, long B)"},
    {name: "_IQmpyIQX",         displayName: "Multiply two 2-different IQ number",                      longDescription: "_iq _IQmpyIQX(_iqN1 A, N1, _iqN2 B, N2)"},
    {name: "N_IQmpyIQX",         displayName: "Multiply two 2-different IQ number (N=1:30)",             longDescription: "_iqN _IQmpyIQX(_iqN1 A, N1, _iqN2 B, N2)"},
    {name: "_IQdiv",            displayName: "Fixed point division",                                    longDescription: "_iq _IQdiv(_iq A, _iq B)"},
    {name: "_IQNdiv",           displayName: "Fixed point division (N=1:30)",                           longDescription: "_iqN _IQNdiv(_iqN A, _iqN B)"}
]
let TRIGONOMETRIC_FUNCTIONS = [
    {name: "_IQasin",           displayName: "High precision ASIN (output in radians)",                 longDescription: "_iq _IQasin(_iq A)"},
    {name: "_IQNasin",          displayName: "High precision ASIN (output in radians) (N=1:30)",        longDescription: "_iqN _IQNasin(_iqN A)"},
    {name: "_IQsin",            displayName: "High precision SIN (input in radians)",                   longDescription: "_iq _IQsin(_iq A)"},
    {name: "_IQNsin",           displayName: "High precision SIN (input in radians) (N=1:30)",          longDescription: "_iqN _IQNsin(_iqN A)"},
    {name: "_IQsinPU",          displayName: "High precision SIN (input in per-unit)",                  longDescription: "_iq _IQsinPU(_iq A)"},
    {name: "_IQNsinPU",         displayName: "High precision SIN (input in per-unit) (N=1:30)",         longDescription: "_iqN _IQNsinPU(_iqN A)"},
    {name: "_IQacos",           displayName: "High precision ACOS (output in radians)",                 longDescription: "_iq _IQacos(_iq A)"},
    {name: "_IQNacos",          displayName: "High precision ACOS (output in radians) (N=1:30)",        longDescription: "_iqN _IQNacos(_iqN A)"},
    {name: "_IQcos",            displayName: "High precision COS (Input in radians)",                   longDescription: "_iq _IQcos(_iq A)"},
    {name: "_IQNcos",           displayName: "High precision COS (Input in radians) (N=1:30)",          longDescription: "_iqN _IQNcos(_iqN A)"},
    {name: "_IQcosPU",          displayName: "High precision COS (input in per-unit)",                  longDescription: "_iq _IQcosPU(_iq A)"},
    {name: "_IQNcosPU",         displayName: "High precision COS (input in per-unit) (N=1:30)",         longDescription: "_iqN _IQNcosPU(_iqN A)"},
    {name: "_IQatan2",          displayName: "4-quadrant ATAN (output in radians)",                     longDescription: "_iq _IQatan2(_iq A, _iq B)"},
    {name: "_IQNatan2",         displayName: "4-quadrant ATAN (output in radians) (N=1:30)",            longDescription: "_iqN _IQNatan2(_iqN A, _iqN B)"},
    {name: "_IQatan2PU",        displayName: "4-quadrant ATAN (output in per-unit)",                    longDescription: "_iq _IQatan2PU(_iq A, _iq B)"},
    {name: "_IQNatanPU",        displayName: "4-quadrant ATAN (output in per-unit) (N=1:30)",           longDescription: "_iqN _IQNatanPU(_iqN A, _iqN B)"},
    {name: "_IQatan",           displayName: "Arctangent",                                              longDescription: "_iq _IQatan(_iq A)"},
    {name: "N_IQatan",           displayName: "Arctangent (N=1:30)",                                     longDescription: "_iqN _IQatan(_iqN A)"}
]
let MATHEMATICAL_FUNCTIONS = [
    {name: "_IQexp",            displayName: "High precision e raised to the A power",                  longDescription: "_iq _IQexp( _iq A)"},
    {name: "_IQNexp",           displayName: "High precision e raised to the A power (N=1:30)",         longDescription: "_iqN _IQNexp( _iqN A)"},
    {name: "_IQlog",            displayName: "IQ Natural Logarithmic Math Function",                    longDescription: "_iq _IQlog( _iq A)"},
    {name: "_IQNlog",           displayName: "IQ Natural Logarithmic Math Function (N=1:30)",           longDescription: "_iqN _IQNlog( _iqN A)"},
    {name: "_IQsqrt",           displayName: "High precision square root",                              longDescription: "_iq _IQsqrt( _iq A)"},
    {name: "_IQNsqrt",          displayName: "High precision square root (N=1:30)",                     longDescription: "_iqN _IQNsqrt( _iqN A)"},
    {name: "_IQisqrt",          displayName: "High precision inverse square root",                      longDescription: "_iq _IQisqrt( _iq A)"},
    {name: "_IQNisqrt",         displayName: "High precision inverse square root (N=1:30)",             longDescription: "_iqN _IQNisqrt( _iqN A)"},
    {name: "_IQmag",            displayName: "Magnitude Square: sqrt(A^2 + B^2)",                       longDescription: "_iq _IQmag( _iq A, _iq B)"},
    {name: "_IQNmag",           displayName: "Magnitude Square: sqrt(A^2 + B^2) (N=1:30)",              longDescription: "_iqN _IQNmag( _iqN A, _iqN B)"}
]
let MISC_FUNCTIONS = [
    {name: "_IQsat",            displayName: "Saturate the IQ number",                                  longDescription: "_iq _IQsat( _iq A, long P, long N)"},
    {name: "_IQabs",            displayName: "Absolute value of IQ number",                             longDescription: "_iq _IQabs( _iq A)"}
]

var format_configs = [];
var mult_div_configs = [];
var arith_configs = [];
var trig_configs = [];
var math_configs = [];
var misc_configs = [];
var moduleStatic = {
    name: "fpu",
    displayName: "FPU/TMU Global Settings",
    config: [],
}

for(let i = 0; i < FORMAT_CONVERSIONS.length; i++)
{
    format_configs = format_configs.concat([
        {
            name: FORMAT_CONVERSIONS[i].name,
            displayName     : FORMAT_CONVERSIONS[i].displayName,
            default         : FORMAT_CONVERSIONS[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 0; i < MULT_DIV_FUNCTIONS.length; i++)
{
    mult_div_configs = mult_div_configs.concat([
        {
            name: MULT_DIV_FUNCTIONS[i].name,
            displayName     : MULT_DIV_FUNCTIONS[i].displayName,
            default         : MULT_DIV_FUNCTIONS[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 0; i < ARITHMETIC_FUNCTIONS.length; i++)
{
    arith_configs = arith_configs.concat([
        {
            name: ARITHMETIC_FUNCTIONS[i].name,
            displayName     : ARITHMETIC_FUNCTIONS[i].displayName,
            default         : ARITHMETIC_FUNCTIONS[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 0; i < TRIGONOMETRIC_FUNCTIONS.length; i++)
{
    trig_configs = trig_configs.concat([
        {
            name: TRIGONOMETRIC_FUNCTIONS[i].name,
            displayName     : TRIGONOMETRIC_FUNCTIONS[i].displayName,
            default         : TRIGONOMETRIC_FUNCTIONS[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 0; i < MATHEMATICAL_FUNCTIONS.length; i++)
{
    math_configs = math_configs.concat([
        {
            name: MATHEMATICAL_FUNCTIONS[i].name,
            displayName     : MATHEMATICAL_FUNCTIONS[i].displayName,
            default         : MATHEMATICAL_FUNCTIONS[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 0; i < MISC_FUNCTIONS.length; i++)
{
    misc_configs = misc_configs.concat([
        {
            name: MISC_FUNCTIONS[i].name,
            displayName     : MISC_FUNCTIONS[i].displayName,
            default         : MISC_FUNCTIONS[i].longDescription,
            readOnly        : true
        },
    ])
}

let config = [
    {
        name        : "formatOptions",
        displayName : "Format Conversion Functions",
        config : format_configs
    },
    {
        name        : "mult_divOptions",
        displayName : "Multiply/Division Functions",
        config : mult_div_configs
    },
    {
        name        : "arithOptions",
        displayName : "Arithmetic Functions",
        config      : arith_configs
    },
    {
        name        : "trigOptions",
        displayName : "Trigonometric Functions",
        config : trig_configs
    },
    {
        name        : "mathOptions",
        displayName : "Mathematical Functions",
        config : math_configs
    },
    {
        name        : "miscOptions",
        displayName : "Miscellaneous Functions",
        config      : misc_configs
    },
]

function onValidate(inst, validation){
    var fpuMod = system.modules["/libraries/math/FPU/FPU.js"];
    if(fpuMod)
    {
        if(fpuMod.$static.fpuType == "FPU64")
        {
            validation.logError(system.getReference(fpuMod.$static, "fpuType") + " option not allowed for IQmath.", inst);
        }
    }
}
function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["IQmath"]));
}
var IQMModule = {
    c2000wareLibraryName: "IQmath",
    displayName: "IQmath",
    defaultInstanceName: "myIQmath",
    description: "Virtual Floating Point Engine",
    longDescription: longDescription,
    filterHardware : filterHardware,
    maxInstances   : 1,
    config: config,
    templates: {
        c2000ware_libraries_h           : "/libraries/math/IQmath/templates/IQmath.c2000ware_libraries.h.xdt",
        c2000ware_libraries_c           : "/libraries/math/IQmath/templates/IQmath.c2000ware_libraries.c.xdt",
        c2000ware_libraries_opt         : "/libraries/math/IQmath/templates/IQmath.c2000ware_libraries.opt.xdt",
        c2000ware_libraries_cmd_genlibs : "/libraries/math/IQmath/templates/IQmath.c2000ware_libraries.cmd.genlibs.xdt",
    },
    modules: Common.autoForce("fpu", "/libraries/.meta/math/FPU/FPU.js"),
    validate : onValidate
};
exports = IQMModule;