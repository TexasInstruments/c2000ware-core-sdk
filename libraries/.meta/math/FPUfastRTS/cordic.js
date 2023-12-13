let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let CORDIC_FUNCTIONS = [
    {name: "CORDIC_F64_setx_i",             longDescription: "void CORDIC_F64_setx_i(CORDIC_F64_Handle hc, int64_t *x_i)"},
    {name: "CORDIC_F64_getx_i",             longDescription: "int64_t * CORDIC_F64_getx_i(CORDIC_F64_Handle hc)"},
    {name: "CORDIC_F64_sety_i",             longDescription: "void CORDIC_F64_sety_i(CORDIC_F64_Handle hc, int64_t *y_i)"},
    {name: "CORDIC_F64_gety_i",             longDescription: "int64_t * CORDIC_F64_gety_i(CORDIC_F64_Handle hc)"},
    {name: "CORDIC_F64_setz_i",             longDescription: "void CORDIC_F64_setz_i(CORDIC_F64_Handle hc, int64_t *z_i)"},
    {name: "CORDIC_F64_getz_i",             longDescription: "int64_t * CORDIC_F64_getz_i(CORDIC_F64_Handle hc)"},
    {name: "CORDIC_F64_setN",               longDescription: "void CORDIC_F64_setN(CORDIC_F64_Handle hc, const uint16_t N)"},
    {name: "CORDIC_F64_getN",               longDescription: "uint16_t CORDIC_F64_getN(CORDIC_F64_Handle hc)"},
    {name: "CORDIC_F64_setAtanTblPtr",      longDescription: "void CORDIC_F64_setAtanTblPtr(CORDIC_F64_Handle hc, const int64_t *p_at)"},
    {name: "CORDIC_F64_getAtanTblPtr",      longDescription: "const int64_t * CORDIC_F64_getAtanTblPtr(CORDIC_F64_Handle hc)"},
    {name: "CORDIC_F64_setRunKernelPtr",    longDescription: "void CORDIC_F64_setRunKernelPtr(CORDIC_F64_Handle hc, const v_pfn_v pfn)"},
    {name: "CORDIC_F64_getRunKernelPtr",    longDescription: "v_pfn_v CORDIC_F64_getRunKernelPtr(CORDIC_F64_Handle hc)"},
    {name: "CORDIC_F64_rotationKernel",     longDescription: "void CORDIC_F64_rotationKernel(CORDIC_F64_Handle hC)"},
    {name: "CORDIC_F64_sin",                longDescription: "float64u_t CORDIC_F64_sin(CORDIC_F64_Handle hC, float64u_t theta)"},
    {name: "CORDIC_F64_cos",                longDescription: "float64u_t CORDIC_F64_cos(CORDIC_F64_Handle hC, float64u_t theta)"}
]
var cordic_configs = [];

for(let i = 0; i < CORDIC_FUNCTIONS.length; i++)
{
    cordic_configs = cordic_configs.concat([
        {
            name: "cordic_" + i,
            longDescription : CORDIC_FUNCTIONS[i].longDescription,
            default     : CORDIC_FUNCTIONS[i].name,
            readOnly    : true
        },
    ])
}
let config = [
    {
        name : "$name",
        hidden : false
    },
    {
        name        : "numIter",
        displayName : "Number of Iterations",
        description : "Number of CORDIC Itreations",
        longDescription : `An increase in N iterations increases the accuracy of the result, up to a maximum of 64`,
        default : 1
    },
]

function onValidate(inst, validation)
{
    if(inst.numIter > 64)
    {
        validation.logError("Maximum of 64 iterations", inst, "numIter");
    }
    else if(inst.numIter <= 0)
    {
        validation.logError("Must have more than 0 iterations", inst, "numIter");
    }
}

var cordicModule = {
    c2000wareLibraryName: "CORDIC",
    displayName: "CORDIC",
    defaultInstanceName: "myCOR",
    description: "CORDIC",
    config: config,
    validate : onValidate
}
exports = cordicModule;