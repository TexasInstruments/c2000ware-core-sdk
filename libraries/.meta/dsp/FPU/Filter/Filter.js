let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let longDescription = `
(name)_handle = Filter object handle

FIR 32-bit Functions | Description
---|---
void FIR_f32_setCoefficientsPtr(FIR_f32_Handle fh, const float *pc)     | Set coefficients pointer
float * FIR_f32_getCoefficientsPtr(FIR_f32_Handle fh)                   | Get coefficients pointer
void FIR_f32_setDelayLinePtr(FIR_f32_Handle fh, const float *pdl)       | Set delay line pointer
float * FIR_f32_getDelayLinePtr(FIR_f32_Handle fh)                      | Get delay line pointer
void FIR_f32_setInput(FIR_f32_Handle fh, const float in)                | Set the input
float FIR_f32_getInput(FIR_f32_Handle fh)                               | Get the input
void FIR_f32_setOutput(FIR_f32_Handle fh, const float out)              | Set the output
float FIR_f32_getOutput(FIR_f32_Handle fh)                              | Get the output
void FIR_f32_setOrder(FIR_f32_Handle fh, const uint16_t order)          | Set filter order
uint16_t FIR_f32_getOrder(FIR_f32_Handle fh)                            | Get filter order
void FIR_f32_setInitFunction(FIR_f32_Handle fh, const v_pfn_v pfn)      | Set initialization function
v_pfn_v FIR_f32_getInitFunction(FIR_f32_Handle fh)                      | Get initialization function
void FIR_f32_setCalcFunction(FIR_f32_Handle fh, const v_pfn_v pfn)      | Set calculation function
v_pfn_v FIR_f32_getCalcFunction(FIR_f32_Handle fh)                      | Get calculation function
void FIR_f32_calc(FIR_f32_Handle hndFIR_f32)                            | FIR calculation
void FIR_f32_init(FIR_f32_Handle hndFIR_f32)                            | FIR initialization (zeros out delay line)

*   All the coefficients of all-zero filter are assumed to be less than 1 in magnitude.
*   The delay and coefficients buffer must be aligned to a minimum of 2 x (order + 1) words.
*   To align the buffer, use the DATA_SECTION pragma to assign the buffer to a code section and then align the buffer to the proper offset in the linker
command file. In the code example the buffer is assigned to the firldb section while the coefficients are assigned to the coefffilt section.
*   This routine requires the --c2xlp_src_compatible option to be enabled in the file specific properties

---

FIR 64-bit Functions | Description
---|---
void FIR_f64_setCoefficientsPtr(FIR_f64_Handle fh, const float64_t *pc) | Set coefficients pointer
float64_t * FIR_f64_getCoefficientsPtr(FIR_f64_Handle fh)               | Get coefficients pointer
void FIR_f64_setDelayLinePtr(FIR_f64_Handle fh, const float64_t *pdl)   | Set delay line pointer
float64_t * FIR_f64_getDelayLinePtr(FIR_f64_Handle fh)                  | Get delay line pointer
void FIR_f64_setInputPtr(FIR_f64_Handle fh, const float64_t *pi)        | Set input pointer
float64_t * FIR_f64_getInputPtr(FIR_f64_Handle fh)                      | Get input pointer
void FIR_f64_setOutputPtr(FIR_f64_Handle fh, const float64_t *po)       | Set output pointer
float64_t * FIR_f64_getOutputPtr(FIR_f64_Handle fh)                     | Get output pointer
void FIR_f64_setOrder(FIR_f64_Handle fh, const uint16_t order)          | Set filter order
uint16_t FIR_f64_getOrder(FIR_f64_Handle fh)                            | Get filter order
void FIR_f64_setInitFunction(FIR_f64_Handle fh, const v_pfn_v pfn)      | Set initialization function
v_pfn_v FIR_f64_getInitFunction(FIR_f64_Handle fh)                      | Get initialization function
void FIR_f64_setCalcFunction(FIR_f64_Handle fh, const v_pfn_v pfn)      | Set calculation function
v_pfn_v FIR_f64_getCalcFunction(FIR_f64_Handle fh)                      | Get calculation function
void FIR_f64_calc(FIR_f64_Handle hndFIR_f64)                            | FIR calculation
void FIR_f64_init(FIR_f64_Handle hndFIR_f64)                            | FIR initialization (zeros out delay line)

*   The delay and coefficients buffer must be assigned a minimum of 4 x (order + 1) words.
*   In the code example the buffer is assigned to the .ebss section while the coefficients are assigned to the .econst section.

---

IIR 32-bit Functions | Description
---|---
void IIR_f32_setCoefficientsAPtr(IIR_f32_Handle fh, const float *pca)   | Set denominator coefficients pointer
float * IIR_f32_getCoefficientsAPtr(IIR_f32_Handle fh)                  | Get denominator coefficients pointer
void IIR_f32_setCoefficientsBPtr(IIR_f32_Handle fh, const float *pcb)   | Set numerator coefficients pointer
float * IIR_f32_getCoefficientsBPtr(IIR_f32_Handle fh)                  | Get numerator coefficients pointer
void IIR_f32_setDelayLinePtr(IIR_f32_Handle fh, const float *pdl)       | Set delay line pointer
float * IIR_f32_getDelayLinePtr(IIR_f32_Handle fh)                      | Get delay line pointer
void IIR_f32_setInputPtr(IIR_f32_Handle fh, const float *pi)            | Set input pointer
float * IIR_f32_getInputPtr(IIR_f32_Handle fh)                          | Get input pointer
void IIR_f32_setOutputPtr(IIR_f32_Handle fh, const float *po)           | Set output pointer
float * IIR_f32_getOutputPtr(IIR_f32_Handle fh)                         | Get output pointer
void IIR_f32_setScalePtr(IIR_f32_Handle fh, const float *psv)           | Set scale value pointer
float * IIR_f32_getScalePtr(IIR_f32_Handle fh)                          | Get scale value pointer
void IIR_f32_setOrder(IIR_f32_Handle fh, const uint16_t order)          | Set filter order
uint16_t IIR_f32_getOrder(IIR_f32_Handle fh)                            | Get filter order
void IIR_f32_setInitFunction(IIR_f32_Handle fh, const v_pfn_v pfn)      | Set initialization function
v_pfn_v IIR_f32_getInitFunction(IIR_f32_Handle fh)"},                   | Get initialization function
void IIR_f32_setCalcFunction(IIR_f32_Handle fh, const v_pfn_v pfn)      | Set calculation function
v_pfn_v IIR_f32_getCalcFunction(IIR_f32_Handle fh)                      | Get calculation function
void IIR_f32_calc(IIR_f32_Handle hndIIR_f32)                            | IIR calculation
void IIR_f32_init(IIR_f32_Handle hndIIR_f32)                            | IIR initialization (zeros out delay line)

*   The delay line buffer must be 2*(n_biquads * n_delay_elements_per_biquad), since there are 4 delay elements per biquad that are single precision 
(32-bits) we require a total of 8 * n_biquads words
*   In the code example the buffer is assigned to the .ebss section while the coefficients are assigned to the .econst section.

---

IIR 64-bit Functions | Description
---|---
void IIR_f64_setCoefficientsAPtr(IIR_f64_Handle fh, const float64_t *pca)   | Set denominator coefficients pointer
float64_t * IIR_f64_getCoefficientsAPtr(IIR_f64_Handle fh)                  | Get denominator coefficients pointer
void IIR_f64_setCoefficientsBPtr(IIR_f64_Handle fh, const float64_t *pcb)   | Set numerator coefficients pointer
float64_t * IIR_f64_getCoefficientsBPtr(IIR_f64_Handle fh)                  | Get numerator coefficients pointer
void IIR_f64_setDelayLinePtr(IIR_f64_Handle fh, const float64_t *pdl)       | Set delay line pointer
float64_t * IIR_f64_getDelayLinePtr(IIR_f64_Handle fh)                      | Get delay line pointer
void IIR_f64_setInputPtr(IIR_f64_Handle fh, const float64_t *pi)            | Set input pointer
float64_t * IIR_f64_getInputPtr(IIR_f64_Handle fh)                          | Get input pointer
void IIR_f64_setOutputPtr(IIR_f64_Handle fh, const float64_t *po)           | Set output pointer
float64_t * IIR_f64_getOutputPtr(IIR_f64_Handle fh)                         | Get output pointer
void IIR_f64_setScalePtr(IIR_f64_Handle fh, const float64_t *psv)           | Set scale value pointer
float64_t * IIR_f64_getScalePtr(IIR_f64_Handle fh)                          | Get scale value pointer
void IIR_f64_setOrder(IIR_f64_Handle fh, const uint16_t order)              | Set filter order
uint16_t IIR_f64_getOrder(IIR_f64_Handle fh)                                | Get filter order
void IIR_f64_setInitFunction(IIR_f64_Handle fh, const v_pfn_v pfn)          | Set initialization function
v_pfn_v IIR_f64_getInitFunction(IIR_f64_Handle fh)                          | Get initialization function
void IIR_f64_setCalcFunction(IIR_f64_Handle fh, const v_pfn_v pfn)          | Set calculation function
v_pfn_v IIR_f64_getCalcFunction(IIR_f64_Handle fh)                          | Get calculation function
void IIR_f64_calc(IIR_f64_Handle hndIIR_f64)                                | IIR calculation
void IIR_f64_init(IIR_f64_Handle hndIIR_f64)                                | IIR initialization (zeros out delay line)

*   The delay line buffer must be 4*(n_biquads * n_delay_elements_per_biquad), since there are 4 delay elements per biquad that are double precision 
(64-bits) we require a total of 16 * n_biquads words
*   In the code example the buffer is assigned to the .ebss section while the coefficients are assigned to the .econst section.
`

let FIR_F32_FUNCTIONS_FLOAT = [
    {name: "FIR_f32_setCoefficientsPtr",    longDescription: "void FIR_f32_setCoefficientsPtr(FIR_f32_Handle fh, const float *pc)"},
    {name: "FIR_f32_getCoefficientsPtr",    longDescription: "float * FIR_f32_getCoefficientsPtr(FIR_f32_Handle fh)"},
    {name: "FIR_f32_setDelayLinePtr",       longDescription: "void FIR_f32_setDelayLinePtr(FIR_f32_Handle fh, const float *pdl)"},
    {name: "FIR_f32_getDelayLinePtr",       longDescription: "float * FIR_f32_getDelayLinePtr(FIR_f32_Handle fh)"},
    {name: "FIR_f32_setInput",              longDescription: "void FIR_f32_setInput(FIR_f32_Handle fh, const float in)"},
    {name: "FIR_f32_getInput",              longDescription: "float FIR_f32_getInput(FIR_f32_Handle fh)"},
    {name: "FIR_f32_setOutput",             longDescription: "void FIR_f32_setOutput(FIR_f32_Handle fh, const float out)"},
    {name: "FIR_f32_getOutput",             longDescription: "float FIR_f32_getOutput(FIR_f32_Handle fh)"},
    {name: "FIR_f32_setOrder",              longDescription: "void FIR_f32_setOrder(FIR_f32_Handle fh, const uint16_t order)"},
    {name: "FIR_f32_getOrder",              longDescription: "uint16_t FIR_f32_getOrder(FIR_f32_Handle fh)"},
    {name: "FIR_f32_setInitFunction",       longDescription: "void FIR_f32_setInitFunction(FIR_f32_Handle fh, const v_pfn_v pfn)"},
    {name: "FIR_f32_getInitFunction",       longDescription: "v_pfn_v FIR_f32_getInitFunction(FIR_f32_Handle fh)"},
    {name: "FIR_f32_setCalcFunction",       longDescription: "void FIR_f32_setCalcFunction(FIR_f32_Handle fh, const v_pfn_v pfn)"},
    {name: "FIR_f32_getCalcFunction",       longDescription: "v_pfn_v FIR_f32_getCalcFunction(FIR_f32_Handle fh)"},
    {name: "FIR_f32_calc",                  longDescription: "void FIR_f32_calc(FIR_f32_Handle hndFIR_f32)"},
    {name: "FIR_f32_init",                  longDescription: "void FIR_f32_init(FIR_f32_Handle hndFIR_f32)"}
]
let FIR_F64_FUNCTIONS_FLOAT = [
    {name: "FIR_f64_setCoefficientsPtr",    longDescription: "void FIR_f64_setCoefficientsPtr(FIR_f64_Handle fh, const float64_t *pc)"},
    {name: "FIR_f64_getCoefficientsPtr",    longDescription: "float64_t * FIR_f64_getCoefficientsPtr(FIR_f64_Handle fh)"},
    {name: "FIR_f64_setDelayLinePtr",       longDescription: "void FIR_f64_setDelayLinePtr(FIR_f64_Handle fh, const float64_t *pdl)"},
    {name: "FIR_f64_getDelayLinePtr",       longDescription: "float64_t * FIR_f64_getDelayLinePtr(FIR_f64_Handle fh)"},
    {name: "FIR_f64_setInputPtr",           longDescription: "void FIR_f64_setInputPtr(FIR_f64_Handle fh, const float64_t *pi)"},
    {name: "FIR_f64_getInputPtr",           longDescription: "float64_t * FIR_f64_getInputPtr(FIR_f64_Handle fh)"},
    {name: "FIR_f64_setOutputPtr",          longDescription: "void FIR_f64_setOutputPtr(FIR_f64_Handle fh, const float64_t *po)"},
    {name: "FIR_f64_getOutputPtr",          longDescription: "float64_t * FIR_f64_getOutputPtr(FIR_f64_Handle fh)"},
    {name: "FIR_f64_setOrder",              longDescription: "void FIR_f64_setOrder(FIR_f64_Handle fh, const uint16_t order)"},
    {name: "FIR_f64_getOrder",              longDescription: "uint16_t FIR_f64_getOrder(FIR_f64_Handle fh)"},
    {name: "FIR_f64_setInitFunction",       longDescription: "void FIR_f64_setInitFunction(FIR_f64_Handle fh, const v_pfn_v pfn)"},
    {name: "FIR_f64_getInitFunction",       longDescription: "v_pfn_v FIR_f64_getInitFunction(FIR_f64_Handle fh)"},
    {name: "FIR_f64_setCalcFunction",       longDescription: "void FIR_f64_setCalcFunction(FIR_f64_Handle fh, const v_pfn_v pfn)"},
    {name: "FIR_f64_getCalcFunction",       longDescription: "v_pfn_v FIR_f64_getCalcFunction(FIR_f64_Handle fh)"},
    {name: "FIR_f64_calc",                  longDescription: "void FIR_f64_calc(FIR_f64_Handle hndFIR_f64)"},
    {name: "FIR_f64_init",                  longDescription: "void FIR_f64_init(FIR_f64_Handle hndFIR_f64)"}
]
let IIR_F32_FUNCTIONS_FLOAT = [
    {name: "IIR_f32_setCoefficientsAPtr",   longDescription: "void IIR_f32_setCoefficientsAPtr(IIR_f32_Handle fh, const float *pca)"},
    {name: "IIR_f32_getCoefficientsAPtr",   longDescription: "float * IIR_f32_getCoefficientsAPtr(IIR_f32_Handle fh)"},
    {name: "IIR_f32_setCoefficientsBPtr",   longDescription: "void IIR_f32_setCoefficientsBPtr(IIR_f32_Handle fh, const float *pcb)"},
    {name: "IIR_f32_getCoefficientsBPtr",   longDescription: "float * IIR_f32_getCoefficientsBPtr(IIR_f32_Handle fh)"},
    {name: "IIR_f32_setDelayLinePtr",       longDescription: "void IIR_f32_setDelayLinePtr(IIR_f32_Handle fh, const float *pdl)"},
    {name: "IIR_f32_getDelayLinePtr",       longDescription: "float * IIR_f32_getDelayLinePtr(IIR_f32_Handle fh)"},
    {name: "IIR_f32_setInputPtr",           longDescription: "void IIR_f32_setInputPtr(IIR_f32_Handle fh, const float *pi)"},
    {name: "IIR_f32_getInputPtr",           longDescription: "float * IIR_f32_getInputPtr(IIR_f32_Handle fh)"},
    {name: "IIR_f32_setOutputPtr",          longDescription: "void IIR_f32_setOutputPtr(IIR_f32_Handle fh, const float *po)"},
    {name: "IIR_f32_getOutputPtr",          longDescription: "float * IIR_f32_getOutputPtr(IIR_f32_Handle fh)"},
    {name: "IIR_f32_setScalePtr",           longDescription: "void IIR_f32_setScalePtr(IIR_f32_Handle fh, const float *psv)"},
    {name: "IIR_f32_getScalePtr",           longDescription: "float * IIR_f32_getScalePtr(IIR_f32_Handle fh)"},
    {name: "IIR_f32_setOrder",              longDescription: "void IIR_f32_setOrder(IIR_f32_Handle fh, const uint16_t order)"},
    {name: "IIR_f32_getOrder",              longDescription: "uint16_t IIR_f32_getOrder(IIR_f32_Handle fh)"},
    {name: "IIR_f32_setInitFunction",       longDescription: "void IIR_f32_setInitFunction(IIR_f32_Handle fh, const v_pfn_v pfn)"},
    {name: "IIR_f32_getInitFunction",       longDescription: "v_pfn_v IIR_f32_getInitFunction(IIR_f32_Handle fh)"},
    {name: "IIR_f32_setCalcFunction",       longDescription: "void IIR_f32_setCalcFunction(IIR_f32_Handle fh, const v_pfn_v pfn)"},
    {name: "IIR_f32_getCalcFunction",       longDescription: "v_pfn_v IIR_f32_getCalcFunction(IIR_f32_Handle fh)"},
    {name: "IIR_f32_calc",                  longDescription: "void IIR_f32_calc(IIR_f32_Handle hndIIR_f32)"},
    {name: "IIR_f32_init",                  longDescription: "void IIR_f32_init(IIR_f32_Handle hndIIR_f32)"}
]
let IIR_F64_FUNCTIONS_FLOAT = [
    {name: "IIR_f64_setCoefficientsAPtr",   longDescription: "void IIR_f64_setCoefficientsAPtr(IIR_f64_Handle fh, const float64_t *pca)"},
    {name: "IIR_f64_getCoefficientsAPtr",   longDescription: "float64_t * IIR_f64_getCoefficientsAPtr(IIR_f64_Handle fh)"},
    {name: "IIR_f64_setCoefficientsBPtr",   longDescription: "void IIR_f64_setCoefficientsBPtr(IIR_f64_Handle fh, const float64_t *pcb)"},
    {name: "IIR_f64_getCoefficientsBPtr",   longDescription: "float64_t * IIR_f64_getCoefficientsBPtr(IIR_f64_Handle fh)"},
    {name: "IIR_f64_setDelayLinePtr",       longDescription: "void IIR_f64_setDelayLinePtr(IIR_f64_Handle fh, const float64_t *pdl)"},
    {name: "IIR_f64_getDelayLinePtr",       longDescription: "float64_t * IIR_f64_getDelayLinePtr(IIR_f64_Handle fh)"},
    {name: "IIR_f64_setInputPtr",           longDescription: "void IIR_f64_setInputPtr(IIR_f64_Handle fh, const float64_t *pi)"},
    {name: "IIR_f64_getInputPtr",           longDescription: "float64_t * IIR_f64_getInputPtr(IIR_f64_Handle fh)"},
    {name: "IIR_f64_setOutputPtr",          longDescription: "void IIR_f64_setOutputPtr(IIR_f64_Handle fh, const float64_t *po)"},
    {name: "IIR_f64_getOutputPtr",          longDescription: "float64_t * IIR_f64_getOutputPtr(IIR_f64_Handle fh)"},
    {name: "IIR_f64_setScalePtr",           longDescription: "void IIR_f64_setScalePtr(IIR_f64_Handle fh, const float64_t *psv)"},
    {name: "IIR_f64_getScalePtr",           longDescription: "float64_t * IIR_f64_getScalePtr(IIR_f64_Handle fh)"},
    {name: "IIR_f64_setOrder",              longDescription: "void IIR_f64_setOrder(IIR_f64_Handle fh, const uint16_t order)"},
    {name: "IIR_f64_getOrder",              longDescription: "uint16_t IIR_f64_getOrder(IIR_f64_Handle fh)"},
    {name: "IIR_f64_setInitFunction",       longDescription: "void IIR_f64_setInitFunction(IIR_f64_Handle fh, const v_pfn_v pfn)"},
    {name: "IIR_f64_getInitFunction",       longDescription: "v_pfn_v IIR_f64_getInitFunction(IIR_f64_Handle fh)"},
    {name: "IIR_f64_setCalcFunction",       longDescription: "void IIR_f64_setCalcFunction(IIR_f64_Handle fh, const v_pfn_v pfn)"},
    {name: "IIR_f64_getCalcFunction",       longDescription: "v_pfn_v IIR_f64_getCalcFunction(IIR_f64_Handle fh)"},
    {name: "IIR_f64_calc",                  longDescription: "void IIR_f64_calc(IIR_f64_Handle hndIIR_f64)"},
    {name: "IIR_f64_init",                  longDescription: "void IIR_f64_init(IIR_f64_Handle hndIIR_f64)"}
]

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

var moduleStatic = {
    name: "fpu",
    displayName: "FPU/TMU Global Settings",
    config: []
}

let config = [
    {
        name: "fpuType",
        displayName : "FPU Configuration",
        description : "Choose FPU32 or FPU64 Configuration",
        default     : FPU_TYPE[0].name,
        options     : FPU_TYPE
    }
]

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
var filterModule = {
    c2000wareLibraryName: "FILTER",
    displayName: "FIR/IIR Filter",
    defaultInstanceName: "myFILTER",
    description: "FIR and IIR Filters",
    longDescription: longDescription,
    maxInstances    : 1,
    filterHardware : filterHardware,
    config: config,
    moduleInstances : (inst) => {
        var fftInst = [];

        fftInst.push({
            displayName: "FIR Configurations",
            name: "FIR",
            description: "",
            useArray : true,
            moduleName: "/libraries/dsp/FPU/Filter/FIR.js",
            requiredArgs: {
                fpuType: inst.fpuType
            }
        });
        fftInst.push({
            displayName: "IIR Configurations",
            name: "IIR",
            description: "",
            useArray : true,
            moduleName: "/libraries/dsp/FPU/Filter/IIR.js",
            requiredArgs: {
                fpuType: inst.fpuType
            }
        });
        return (fftInst);
    },
    modules: Common.autoForce("fpu", "/libraries/.meta/math/FPU/FPU.js"),
    templates: {
        c2000ware_libraries_h           : "/libraries/dsp/FPU/Filter/templates/filter.c2000ware_libraries.h.xdt",
        c2000ware_libraries_c           : "/libraries/dsp/FPU/Filter/templates/filter.c2000ware_libraries.c.xdt",
        c2000ware_libraries_opt         : "/libraries/dsp/FPU/Filter/templates/filter.c2000ware_libraries.opt.xdt",
        c2000ware_libraries_cmd_genlibs : "/libraries/dsp/FPU/Filter/templates/filter.c2000ware_libraries.cmd.genlibs.xdt",
    },
    validate : onValidate
};
exports = filterModule;