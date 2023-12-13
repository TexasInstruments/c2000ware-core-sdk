let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let longDescription = ``
let VEC_FPU32 = [
    {name: "Absolute Value of a Complex Vector",                                                                displayName: "Complex Vector",    description: "void abs_SP_CV(float *y, const complex_float *x, const uint16_t N)",                                                              longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/abs_SP_CV.png)`},
    {name: "Absolute Value of an Even Length Complex Vector",                                                   displayName: "Even Length Complex Vector",    description: "void abs_SP_CV_2(float *y, const complex_float *x, const uint16_t N)",                                                            longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/abs_SP_CV_2.png)`},
    {name: "Absolute Value of a Complex Vector (TMU0)",                                                         displayName: "Complex Vector (TMU0)",    description: "void abs_SP_CV_TMU0(float *y, const complex_float *x, const uint16_t N)",                                                         longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/abs_SP_CV_TMU0.png)`},
    {name: "Addition (Element-Wise) of a Complex Scalar to a Complex Vector",                                   displayName: "(Element-Wise) Complex Scalar to a Complex Vector",    description: "void add_SP_CSxCV(complex_float *y, const complex_float *x, const complex_float c, const uint16_t N)",                            longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/add_SP_CSxCV.png)`},
    {name: "Addition of Two Complex Vectors",                                                                   displayName: "Two Complex Vectors",    description: "void add_SP_CVxCV(complex_float *y, const complex_float *w, const complex_float *x, const uint16_t N)",                           longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/add_SP_CVxCV.png)`},
    {name: "Inverse Absolute Value of a Complex Vector",                                                        displayName: "Complex Vector",    description: "void iabs_SP_CV(float *y, const complex_float *x, const uint16_t N)",                                                             longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/iabs_SP_CV.png)`},
    {name: "Inverse Absolute Value of an Even Length Complex Vector",                                           displayName: "Even Length Complex Vector",    description: "void iabs_SP_CV_2(float *y, const complex_float *x, const uint16_t N)",                                                           longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/iabs_SP_CV_2.png)`},
    {name: "Inverse Absolute Value of a Complex Vector (TMU0)",                                                 displayName: "Complex Vector (TMU0)",    description: "void iabs_SP_CV_TMU0(float *y, const complex_float *x, const uint16_t N)",                                                        longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/iabs_SP_CV_TMU0.png)`},
    {name: "Multiply-and-Accumulate of a Complex Vector and a Complex Vector",                                  displayName: "Complex Vector and a Complex Vector",    description: "complex_float mac_SP_CVxCV(const complex_float *w, const complex_float *x, const uint16_t N)",                                    longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mac_SP_CVxCV.png)`},
    {name: "Multiply-and-Accumulate of a Real Vector and a Complex Vector",                                     displayName: "Real Vector and a Complex Vector",    description: "complex_float mac_SP_RVxCV(const complex_float *w, const float *x, const uint16_t N)",                                            longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mac_SP_RVxCV.png)`},
    {name: "Multiply-and-Accumulate of a 16-bit Integer Real Vector and a Floating Point Complex Vector",       displayName: "16-bit Integer Real Vector and a Floating Point Complex Vector",    description: "complex_float mac_SP_i16RVxCV(const complex_float *w, const int16_t *x, const uint16_t N)",                                       longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mac_SP_i16RVxCV.png)`},
    {name: "Median of a Real Valued Array of Floats (Preserved Inputs)",                                        displayName: "Real Valued Array of Floats (Preserved Inputs)",    description: "float median_noreorder_SP_RV(const float *x, const uint16_t N)",                                                                  longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/median_noreorder_SP_RV.png)`},
    {name: "Median of a Real Array of floats",                                                                  displayName: "Real Array of floats",    description: "float median_SP_RV(float *x, const uint16_t N)",                                                                                  longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/median_SP_RV.png)`},
    {name: "Complex Multiply of Two Floating Point Numbers",                                                    displayName: "(Complex) Two Floating Point Numbers",    description: "complex_float mpy_SP_CSxCS(const complex_float w, const complex_float x)",                                                        longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_SP_CSxCS.png)`},
    {name: "Complex Multiply of Two Complex Vectors",                                                           displayName: "(Complex) Two Complex Vectors",    description: "void mpy_SP_CVxCV(complex_float *y, const complex_float *w, const complex_float *x, const uint16_t N)",                           longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_SP_CVxCV.png)`},
    {name: "Multiplication of a Complex Vector and the Complex Conjugate of Another Vector",                    displayName: "Complex Vector and the Complex Conjugate of Another Vector",    description: "void mpy_SP_CVxCVC(complex_float *y, const complex_float *w, const complex_float *x, const uint16_t N)",                          longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_SP_CVxCVC.png)`},
    {name: "Multiplication of Two Real Matrices",                                                               displayName: "Two Real Matrices",    description: "void mpy_SP_RMxRM(float *y, const float *w, const float *x, const uint16_t m, const uint16_t n, const uint16_t p)",               longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_SP_RMxRM.png)`},
    {name: "Multiplication of Two Real Matrices (n Even)",                                                      displayName: "Two Real Matrices (n Even)",    description: "void mpy_SP_RMxRM_2(float *y, const float *w, const float *x, const uint16_t m, const uint16_t n, const uint16_t p)",             longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_SP_RMxRM_2.png)`},
    {name: "Multiplication of a Real Scalar and a Real Vector",                                                 displayName: "Real Scalar and a Real Vector",    description: "void mpy_SP_RSxRV_2(float *y, const float *x, const float c, const uint16_t N)",                                                  longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_SP_RSxRV_2.png)`},
    {name: "Multiplication of a Real Scalar, a Real Vector, and another Real Vector",                           displayName: "Real Scalar, a Real Vector, and another Real Vector",    description: "void mpy_SP_RSxRVxRV_2(float *y, const float *w, const float *x, const float c, const uint16_t N)",                               longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_SP_RSxRVxRV_2.png)`},
    {name: "Multiplication of a Real Vector and a Complex Vector",                                              displayName: "Real Vector and a Complex Vector",    description: "void mpy_SP_RVxCV(complex_float *y, const complex_float *w, const float *x, const uint16_t N)",                                   longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_SP_RVxCV.png)`},
    {name: "Multiplication of a Real Vector and a Real Vector",                                                 displayName: "Real Vector and a Real Vector",    description: "void mpy_SP_RVxRV_2(float *y, const float *w, const float *x, const uint16_t N)",                                                 longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_SP_RVxRV_2.png)`},
    {name: "Subtraction of a Complex Scalar from a Complex Vector",                                             displayName: "Complex Scalar from a Complex Vector",    description: "void sub_SP_CSxCV(complex_float *y, const complex_float *x, const complex_float c, const uint16_t N)",                            longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/sub_SP_CSxCV.png)`},
    {name: "Subtraction of a Complex Vector and another Complex Vector",                                        displayName: "Complex Vector and another Complex Vector",    description: "void sub_SP_CVxCV(complex_float *y, const complex_float *w, const complex_float *x, const uint16_t N)",                           longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/sub_SP_CVxCV.png)`},
    {name: "Index of Maximum Value of an Even Length Real Array",                                               displayName: "Index of Maximum Value of an Even Length Real Array",    description: "uint16_t maxidx_SP_RV_2(const float *x, const uint16_t N)",                                                                       longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/maxidx_SP_RV_2.png)`},
    {name: "Mean of Real and Imaginary Parts of a Complex Vector",                                              displayName: "Mean of Real and Imaginary Parts of a Complex Vector",    description: "complex_float mean_SP_CV_2(const complex_float *x, const uint16_t N)",                                                            longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mean_SP_CV_2.png)`},
    {name: "Optimized Memory Copy",                                                                             displayName: "Optimized Memory Copy",    description: "void memcpy_fast(void *dst, const void *src, const uint16_t N)",                                                                  longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/memcpy_fast.png)`},
    {name: "Optimized Memory Set",                                                                              displayName: "Optimized Memory Set",    description: "void memset_fast(void* dst, const int16_t value, const uint16_t N)",                                                              longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/memset_fast.png)`},
    {name: "Sort an Array of Floats",                                                                           displayName: "Sort an Array of Floats",    description: "void qsort_SP_RV(void *x, const uint16_t N)",                                                                                     longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/qsort_SP_RV.png)`},
    {name: "Rounding (Unbiased) of a Floating Point Scalar",                                                    displayName: "Rounding (Unbiased) of a Floating Point Scalar",    description: "float rnd_SP_RS(const float x)",                                                                                                  longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/rnd_SP_RS.png)`},
]
let VEC_FPU64 = [
    {name: "Absolute Value of a Complex Vector (Double Precision)",                                             displayName: "Complex Vector",    description: "void abs_DP_CV(float64_t *y, const complexf64_t *x, const uint16_t N)",                                                           longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/abs_DP_CV.png)`},
    {name: "Absolute Value of an Even Length Complex Vector (Double Precision)",                                displayName: "Even Length Complex Vector",    description: "void abs_DP_CV_2(float64_t *y, const complexf64_t *x, const uint16_t N)",                                                         longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/abs_DP_CV_2.png)`},
    {name: "Addition (Element-Wise) of a Complex Scalar to a Complex Vector (Double Precision)",                displayName: "(Element-Wise) Complex Scalar to a Complex Vector",    description: "void add_DP_CSxCV(complexf64_t *y, const complexf64_t *x, const complexf64_t *c, const uint16_t N)",                              longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/add_DP_CSxCV.png)`},
    {name: "Addition of Two Complex Vectors (Double Precision)",                                                displayName: "Two Complex Vectors",    description: "void add_DP_CVxCV(complexf64_t *y, const complexf64_t *w, const complexf64_t *x, const uint16_t N)",                              longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/add_DP_CVxCV.png)`},
    {name: "Inverse Absolute Value of a Complex Vector (Double Precision)",                                     displayName: "Complex Vector",    description: "void iabs_DP_CV(float64_t *y, const complexf64_t *x, const uint16_t N)",                                                          longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/iabs_DP_CV.png)`},
    {name: "Inverse Absolute Value of an Even Length Complex Vector (Double Precision)",                        displayName: "Even Length Complex Vector",    description: "void iabs_DP_CV_2(float64_t *y, const complexf64_t *x, const uint16_t N)",                                                        longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/iabs_DP_CV_2.png)`},
    {name: "Multiply-and-Accumulate of a Real Vector (Integer) and a Complex Vector (Double Precision)",        displayName: "Real Vector (Integer) and a Complex Vector",    description: "complexf64_t mac_DP_i16RVxCV(const complexf64_t *w, const int16_t *x, const uint16_t N)",                                         longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mac_DP_i16RVxCV.png)`},
    {name: "Multiply-and-Accumulate of a Complex Vector and a Complex Vector (Double Precision)",               displayName: "Complex Vector and a Complex Vector",    description: "complexf64_t mac_DP_CVxCV(const complexf64_t *w, const complexf64_t *x, const uint16_t N)",                                       longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mac_DP_CVxCV.png)`},
    {name: "Multiply-and-Accumulate of a Real Vector and a Complex Vector (Double Precision)",                  displayName: "Real Vector and a Complex Vector",    description: "complexf64_t mac_DP_RVxCV(const complexf64_t *w, const float64_t *x, const uint16_t N)",                                          longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mac_DP_RVxCV.png)`},
    {name: "Complex Multiply of Two Double Precision Numbers",                                                  displayName: "(Complex) Two Double Precision Numbers",    description: "complexf64_t mpy_DP_CSxCS(const complexf64_t *w, const complexf64_t *x)",                                                         longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_DP_CSxCS.png)`},
    {name: "Complex Multiply of Two Complex Vectors (Double Precision)",                                        displayName: "(Complex) Two Complex Vectors",    description: "complexf64_t mpy_DP_CSxCS(const complexf64_t *w, const complexf64_t *x)",                                                         longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_DP_CVxCV.png)`},
    {name: "Multiplication of a Complex Vector and the Complex Conjugate of Another Vector (Double Precision)", displayName: "Complex Vector and the Complex Conjugate of Another Vector",    description: "void mpy_DP_CVxCVC(complexf64_t *y, const complexf64_t *w, const complexf64_t *x, const uint16_t N)",                             longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_DP_CVxCVC.png)`},
    {name: "Multiplication of Two Real Matrices (Double Precision)",                                            displayName: "Two Real Matrices",    description: "void mpy_DP_RMxRM(float64_t *y, const float64_t *w, const float64_t *x, const uint16_t m,  const uint16_t n, const uint16_t p)",  longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_DP_RMxRM.png)`},
    {name: "Multiplication of Two Real Matrices (n even, Double Precision)",                                    displayName: "Two Real Matrices (n even)",    description: "void mpy_DP_RMxRM_2(float64_t *y, const float64_t *w, const float64_t *x, const uint16_t m, const uint16_t n, const uint16_t p)", longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_DP_RMxRM_2.png)`},
    {name: "Multiplication of a Real scalar and a Real Vector (Double Precision)",                              displayName: "Real scalar and a Real Vector",    description: "void mpy_DP_RSxRV_2(float64_t *y, const float64_t *x, const float64_t c, const uint16_t N)",                                      longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_DP_RSxRV_2.png)`},
    {name: "Multiplication of a Real Scalar, a Real Vector, and another Real Vector (Double Precision)",        displayName: "Real Scalar, a Real Vector, and another Real Vector",    description: "void mpy_DP_RSxRVxRV_2(float64_t *y, const float64_t *w, const float64_t *x, const float64_t c, const uint16_t N)",               longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_DP_RSxRVxRV_2.png)`},
    {name: "Multiplication of a Real Vector and a Complex Vector (Double Precision)",                           displayName: "Real Vector and a Complex Vector",    description: "void mpy_DP_RVxCV(complexf64_t *y, const complexf64_t *w, const float64_t *x, const uint16_t N)",                                 longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_DP_RVxCV.png)`},
    {name: "Multiplication of a Real Vector and a Real Vector",                                                 displayName: "Real Vector and a Real Vector",    description: "void mpy_DP_RVxRV_2(float64_t *y, const float64_t *w, const float64_t *x, const uint16_t N)",                                     longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mpy_DP_RVxRV_2.png)`},
    {name: "Subtraction of a Complex Scalar from a Complex Vector",                                             displayName: "Complex Scalar from a Complex Vector",    description: "void sub_DP_CSxCV(complexf64_t *y, const complexf64_t *x, const complexf64_t *c, const uint16_t N)",                              longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/sub_DP_CSxCV.png)`},
    {name: "Subtraction of a Complex Vector and another Complex Vector (Double Precision)",                     displayName: "Complex Vector and another Complex Vector",    description: "void sub_DP_CVxCV(complexf64_t *y, const complexf64_t *w, const complexf64_t *x, const uint16_t N)",                              longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/sub_DP_CVxCV.png)`},
    {name: "Index of Maximum Value of an Even Length Real Array (Double Precision)",                            displayName: "Index of Maximum Value of an Even Length Real Array",    description: "uint16_t maxidx_DP_RV_2(const float64_t *x, const uint16_t N)",                                                                   longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/maxidx_DP_RV_2.png)`},
    {name: "Mean of Real and Imaginary Parts of a Complex Vector (Double Precision)",                           displayName: "Mean of Real and Imaginary Parts of a Complex Vector",    description: "complexf64_t mean_DP_CV_2(const complexf64_t *x, const uint16_t N)",                                                              longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/mean_DP_CV_2.png)`},
    {name: "Rounding (Unbiased) of a Floating Point Scalar (Double Precision)",                                 displayName: "Rounding (Unbiased) of a Floating Point Scalar",    description: "float64_t rnd_DP_RS(const float64_t x)",                                                                                          longDescription: `![Image Missing](../../libraries/.meta/dsp/FPU/Vector/references/rnd_DP_RS.png)`},
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


var vec_configs_fpu32_abs = [];
var vec_configs_fpu32_add = [];
var vec_configs_fpu32_inv_abs = [];
var vec_configs_fpu32_mac = [];
var vec_configs_fpu32_med = [];
var vec_configs_fpu32_mult = [];
var vec_configs_fpu32_sub = [];
var vec_configs_fpu32_misc = [];

var vec_configs_fpu64_abs = [];
var vec_configs_fpu64_add = [];
var vec_configs_fpu64_inv_abs = [];
var vec_configs_fpu64_mac = [];
var vec_configs_fpu64_mult = [];
var vec_configs_fpu64_sub = [];
var vec_configs_fpu64_misc = [];
var moduleStatic = {
    name: "fpu",
    displayName: "FPU/TMU Global Settings",
    config: []
}

for(let i = 0; i < 3; i++)
{
    vec_configs_fpu32_abs = vec_configs_fpu32_abs.concat([
        {
            name: "VEC32_" + i,
            displayName     : VEC_FPU32[i].displayName,
            hidden          : false,
            default         : VEC_FPU32[i].description,
            longDescription : VEC_FPU32[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 3; i < 5; i++)
{
    vec_configs_fpu32_add = vec_configs_fpu32_add.concat([
        {
            name: "VEC32_" + i,
            displayName     : VEC_FPU32[i].displayName,
            hidden          : false,
            default         : VEC_FPU32[i].description,
            longDescription : VEC_FPU32[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 5; i < 8; i++)
{
    vec_configs_fpu32_inv_abs = vec_configs_fpu32_inv_abs.concat([
        {
            name: "VEC32_" + i,
            displayName     : VEC_FPU32[i].displayName,
            hidden          : false,
            default         : VEC_FPU32[i].description,
            longDescription : VEC_FPU32[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 8; i < 11; i++)
{
    vec_configs_fpu32_mac = vec_configs_fpu32_mac.concat([
        {
            name: "VEC32_" + i,
            displayName     : VEC_FPU32[i].displayName,
            hidden          : false,
            default         : VEC_FPU32[i].description,
            longDescription : VEC_FPU32[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 11; i < 13; i++)
{
    vec_configs_fpu32_med = vec_configs_fpu32_med.concat([
        {
            name: "VEC32_" + i,
            displayName     : VEC_FPU32[i].displayName,
            hidden          : false,
            default         : VEC_FPU32[i].description,
            longDescription : VEC_FPU32[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 13; i < 22; i++)
{
    vec_configs_fpu32_mult = vec_configs_fpu32_mult.concat([
        {
            name: "VEC32_" + i,
            displayName     : VEC_FPU32[i].displayName,
            hidden          : false,
            default         : VEC_FPU32[i].description,
            longDescription : VEC_FPU32[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 22; i < 24; i++)
{
    vec_configs_fpu32_sub = vec_configs_fpu32_sub.concat([
        {
            name: "VEC32_" + i,
            displayName     : VEC_FPU32[i].displayName,
            hidden          : false,
            default         : VEC_FPU32[i].description,
            longDescription : VEC_FPU32[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 24; i < VEC_FPU32.length; i++)
{
    vec_configs_fpu32_misc = vec_configs_fpu32_misc.concat([
        {
            name: "VEC32_" + i,
            displayName     : VEC_FPU32[i].displayName,
            hidden          : false,
            default         : VEC_FPU32[i].description,
            longDescription : VEC_FPU32[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 0; i < 2; i++)
{
    vec_configs_fpu64_abs = vec_configs_fpu64_abs.concat([
        {
            name: "VEC64_" + i,
            displayName     : VEC_FPU64[i].displayName,
            hidden          : true,
            default         : VEC_FPU64[i].description,
            longDescription : VEC_FPU64[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 2; i < 4; i++)
{
    vec_configs_fpu64_add = vec_configs_fpu64_add.concat([
        {
            name: "VEC64_" + i,
            displayName     : VEC_FPU64[i].displayName,
            hidden          : true,
            default         : VEC_FPU64[i].description,
            longDescription : VEC_FPU64[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 4; i < 6; i++)
{
    vec_configs_fpu64_inv_abs = vec_configs_fpu64_inv_abs.concat([
        {
            name: "VEC64_" + i,
            displayName     : VEC_FPU64[i].displayName,
            hidden          : true,
            default         : VEC_FPU64[i].description,
            longDescription : VEC_FPU64[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 6; i < 9; i++)
{
    vec_configs_fpu64_mac = vec_configs_fpu64_mac.concat([
        {
            name: "VEC64_" + i,
            displayName     : VEC_FPU64[i].displayName,
            hidden          : true,
            default         : VEC_FPU64[i].description,
            longDescription : VEC_FPU64[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 9; i < 18; i++)
{
    vec_configs_fpu64_mult = vec_configs_fpu64_mult.concat([
        {
            name: "VEC64_" + i,
            displayName     : VEC_FPU64[i].displayName,
            hidden          : true,
            default         : VEC_FPU64[i].description,
            longDescription : VEC_FPU64[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 18; i < 20; i++)
{
    vec_configs_fpu64_sub = vec_configs_fpu64_sub.concat([
        {
            name: "VEC64_" + i,
            displayName     : VEC_FPU64[i].displayName,
            hidden          : true,
            default         : VEC_FPU64[i].description,
            longDescription : VEC_FPU64[i].longDescription,
            readOnly        : true
        },
    ])
}
for(let i = 20; i < VEC_FPU64.length; i++)
{
    vec_configs_fpu64_misc = vec_configs_fpu64_misc.concat([
        {
            name: "VEC64_" + i,
            displayName     : VEC_FPU64[i].displayName,
            hidden          : true,
            default         : VEC_FPU64[i].description,
            longDescription : VEC_FPU64[i].longDescription,
            readOnly        : true
        },
    ])
}

let config = [
    {
        name: "fpuType",
        displayName : "FPU Configuration",
        default     : FPU_TYPE[0].name,
        options     : FPU_TYPE,
        onChange    : onChangeFPU
    },
    {
        name        : "fpu32Abs",
        displayName : "Absolute Value Vector Functions",
        config : vec_configs_fpu32_abs
    },
    {
        name        : "fpu32Add",
        displayName : "Addition Vector Functions",
        config : vec_configs_fpu32_add
    },
    {
        name        : "fpu32InvAbs",
        displayName : "Inverse Absolute Value Vector Functions",
        config : vec_configs_fpu32_inv_abs
    },
    {
        name        : "fpu32Mac",
        displayName : "Multiply-and-Accumulate Vector Functions",
        config : vec_configs_fpu32_mac
    },
    {
        name        : "fpu32Med",
        displayName : "Median Vector Functions",
        config : vec_configs_fpu32_med
    },
    {
        name        : "fpu32Mult",
        displayName : "Multiply Vector Functions",
        config : vec_configs_fpu32_mult
    },
    {
        name        : "fpu32Sub",
        displayName : "Subtraction Vector Functions",
        config : vec_configs_fpu32_sub
    },
    {
        name        : "fpu32Misc",
        displayName : "Miscellaneous Vector Functions",
        config : vec_configs_fpu32_misc
    },
    {
        name        : "fpu64Abs",
        displayName : "Absolute Value Vector Functions",
        config : vec_configs_fpu64_abs
    },
    {
        name        : "fpu64Add",
        displayName : "Addition Vector Functions",
        config : vec_configs_fpu64_add
    },
    {
        name        : "fpu64InvAbs",
        displayName : "Inverse Absolute Value Vector Functions",
        config : vec_configs_fpu64_inv_abs
    },
    {
        name        : "fpu64Mac",
        displayName : "Multiply-and-Accumulate Vector Functions",
        config : vec_configs_fpu64_mac
    },
    {
        name        : "fpu64Mult",
        displayName : "Multiply Vector Functions",
        config : vec_configs_fpu64_mult
    },
    {
        name        : "fpu64Sub",
        displayName : "Subtraction Vector Functions",
        config : vec_configs_fpu64_sub
    },
    {
        name        : "fpu64Misc",
        displayName : "Miscellaneous Vector Functions",
        config : vec_configs_fpu64_misc
    },
]

function onChangeFPU(inst, ui)
{
    if(inst.fpuType == FPU_TYPE[0].name)
    {
        for(var i in vec_configs_fpu32_abs)
        {
            ui[vec_configs_fpu32_abs[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu32_add)
        {
            ui[vec_configs_fpu32_add[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu32_inv_abs)
        {
            ui[vec_configs_fpu32_inv_abs[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu32_mac)
        {
            ui[vec_configs_fpu32_mac[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu32_med)
        {
            ui[vec_configs_fpu32_med[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu32_mult)
        {
            ui[vec_configs_fpu32_mult[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu32_sub)
        {
            ui[vec_configs_fpu32_sub[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu32_misc)
        {
            ui[vec_configs_fpu32_misc[i].name].hidden = false;
        }

        for(var i in vec_configs_fpu64_abs)
        {
            ui[vec_configs_fpu64_abs[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu64_add)
        {
            ui[vec_configs_fpu64_add[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu64_inv_abs)
        {
            ui[vec_configs_fpu64_inv_abs[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu64_mac)
        {
            ui[vec_configs_fpu64_mac[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu64_mult)
        {
            ui[vec_configs_fpu64_mult[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu64_sub)
        {
            ui[vec_configs_fpu64_sub[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu64_misc)
        {
            ui[vec_configs_fpu64_misc[i].name].hidden = true;
        }
    }
    else if(((Common.getDeviceName() == "F2838x") || (Common.getDeviceName() == "F28P65x")) && (inst.fpuType == FPU_TYPE[1].name))
    {
        for(var i in vec_configs_fpu32_abs)
        {
            ui[vec_configs_fpu32_abs[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu32_add)
        {
            ui[vec_configs_fpu32_add[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu32_inv_abs)
        {
            ui[vec_configs_fpu32_inv_abs[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu32_mac)
        {
            ui[vec_configs_fpu32_mac[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu32_med)
        {
            ui[vec_configs_fpu32_med[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu32_mult)
        {
            ui[vec_configs_fpu32_mult[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu32_sub)
        {
            ui[vec_configs_fpu32_sub[i].name].hidden = true;
        }
        for(var i in vec_configs_fpu32_misc)
        {
            ui[vec_configs_fpu32_misc[i].name].hidden = true;
        }

        for(var i in vec_configs_fpu64_abs)
        {
            ui[vec_configs_fpu64_abs[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu64_add)
        {
            ui[vec_configs_fpu64_add[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu64_inv_abs)
        {
            ui[vec_configs_fpu64_inv_abs[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu64_mac)
        {
            ui[vec_configs_fpu64_mac[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu64_mult)
        {
            ui[vec_configs_fpu64_mult[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu64_sub)
        {
            ui[vec_configs_fpu64_sub[i].name].hidden = false;
        }
        for(var i in vec_configs_fpu64_misc)
        {
            ui[vec_configs_fpu64_misc[i].name].hidden = false;
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
    return (Common.typeMatches(component.type, ["Vector"]));
}
var vecModule = {
    c2000wareLibraryName: "VECTOR",
    displayName: "Vector",
    defaultInstanceName: "myVEC",
    description: "Vector Operations",
    longDescription: longDescription,
    filterHardware : filterHardware,
    maxInstances   : 1,
    config: config,
    templates: {
        c2000ware_libraries_h           : "/libraries/dsp/FPU/Vector/templates/vector.c2000ware_libraries.h.xdt",
        c2000ware_libraries_opt         : "/libraries/dsp/FPU/Vector/templates/vector.c2000ware_libraries.opt.xdt",
        c2000ware_libraries_cmd_genlibs : "/libraries/dsp/FPU/Vector/templates/vector.c2000ware_libraries.cmd.genlibs.xdt",
    },
    modules: Common.autoForce("fpu", "/libraries/.meta/math/FPU/FPU.js"),
    validate : onValidate
};
exports = vecModule;