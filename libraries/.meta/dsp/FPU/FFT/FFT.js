let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let LinkerDefineFix = system.getScript("/libraries/LinkerDefineFix.js")

let longDescription = LinkerDefineFix.errorFix;
longDescription += `
**Please refer to the [user guide](https://dev.ti.com/tirex/explore/node?node=AOZ6OU09-AcytWQVSYjfkA__gYkahfz__LATEST) for more information**

Globals for FFT (available for CFFT and RFFT, when included):
Complex Fast-Fourier Transform:
*   (name)_CFFT_NUM_STAGES = Number of stages for CFFT
*   (name)_CFFT_SIZE = Size of CFFT input (number of elements)
*   (name)_handle = Handle for CFFT object

Real Fast-Fourier Transform:
*   (name)_RFFT_NUM_STAGES = Number of stages for RFFT
*   (name)_RFFT_SIZE = Size of RFFT input (number of elements)
*   (name)_handle = Handle for RFFT object
*   (name)_adc_handle = Handle for RFFT object when ADC mode is enabled

Methods of Increasing Performance:
*   Aligning buffers to memory addresses as described in the user guide
*   Enabling the TMU (TMU0 or TMU1) for phase and magnitude calculations
*   Utilizing twiddle factors 

**NOTE: When using pre-generated twiddle factors (e.g. this option is true), use a function with a 't' after the CFFT_f32 or RFFT_f32**

---

**32-bit Complex Fast Fourier Transform Setters and Getters**

Function | Description
--- |---
void CFFT_f32_setInputPtr(CFFT_F32_STRUCT_Handle fh, const float *pi)           | Sets input pointer
float * CFFT_f32_getInputPtr(CFFT_F32_STRUCT_Handle fh)                         | Gets input pointer
void CFFT_f32_setOutputPtr(CFFT_F32_STRUCT_Handle fh, const float *po)          | Sets output pointer
float * CFFT_f32_getOutputPtr(CFFT_F32_STRUCT_Handle fh)                        | Gets output pointer
void CFFT_f32_setTwiddlesPtr(CFFT_F32_STRUCT_Handle fh, const float *pc)        | Sets twiddle factors pointer (speed up FFT)
float * CFFT_f32_getTwiddlesPtr(CFFT_F32_STRUCT_Handle fh)                      | Gets twiddle factors pointer
void CFFT_f32_setCurrInputPtr(CFFT_F32_STRUCT_Handle fh, const float *pi)       | Sets current input pointer
float * CFFT_f32_getCurrInputPtr(CFFT_F32_STRUCT_Handle fh)                     | Gets current input pointer
void CFFT_f32_setCurrOutputPtr(CFFT_F32_STRUCT_Handle fh, const float *po)      | Sets current output pointer
float * CFFT_f32_getCurrOutputPtr(CFFT_F32_STRUCT_Handle fh)                    | Gets current output pointer
void CFFT_f32_setStages(CFFT_F32_STRUCT_Handle fh, const uint16_t st)           | Sets number of stages
uint16_t CFFT_f32_getStages(CFFT_F32_STRUCT_Handle fh)                          | Gets number of stages
void CFFT_f32_setFFTSize(CFFT_F32_STRUCT_Handle fh, const uint16_t sz)          | Sets the FFT size
uint16_t CFFT_f32_getFFTSize(CFFT_F32_STRUCT_Handle fh)                         | Gets the FFT size

**32-bit Complex Fast Fourier Transform Functions**

Function | Description
--- |---
void CFFT_f32(CFFT_F32_STRUCT_Handle hndCFFT_F32)                                   | Computes CFFT, requires memory alignment for buffer(s)
void CFFT_f32_brev(CFFT_F32_STRUCT_Handle hndCFFT_F32)                              | Reorder data set in bit reverse order (can be run in-place); mainly used prior to calling in-place FFT
void CFFT_f32i(CFFT_F32_STRUCT_Handle hndCFFT_F32)                                  | Computes CFFT in-place (must call CFFT_f32_brev prior), requires memory alignment for buffer(s)
void CFFT_f32t(CFFT_F32_STRUCT_Handle hndCFFT_F32)                                  | Computes CFFT using pre-generated Twiddle Factors table, requires memory alignment for buffer(s)
void CFFT_f32it(CFFT_F32_STRUCT_Handle hndCFFT_F32)                                 | Computes CFFT in-place using pre-generated Twiddle Factors table, requires memory alignment for buffer(s)
void CFFT_f32u(CFFT_F32_STRUCT_Handle hndCFFT_F32)                                  | Computes CFFT, memory alignment not required
void CFFT_f32ut(CFFT_F32_STRUCT_Handle hndCFFT_F32)                                 | Computes CFFT using statically generated Twiddle Factors table, memory alignment not required
void CFFT_f32_sincostable(CFFT_F32_STRUCT_Handle hndCFFT_F32)                       | Generates Twiddle Factors for CFFT
void CFFT_f32_win(float *pBuffer, const float *pWindow, const uint16_t size)        | Performs windowing function on the real component of the buffer
void CFFT_f32_win_dual(float *pBuffer, const float *pWindow, const uint16_t size)   | Performs windowing function on the real and imaginary component of the buffer
void CFFT_f32_mag(CFFT_F32_STRUCT_Handle hndCFFT_F32)                               | Computes the CFFT magnitude (no memory alignment needed); stored in CurrentOutPtr
void CFFT_f32s_mag(CFFT_F32_STRUCT_Handle hndCFFT_F32)                              | Computes the scaled CFFT magnitude (no memory alignment needed); stored in CurrentOutPtr
void CFFT_f32_phase(CFFT_F32_STRUCT_Handle hndCFFT_F32)                             | Computes the CFFT phase (no memory alignment needed); stored in CurrentOutPtr
void CFFT_f32_unpack(CFFT_F32_STRUCT_Handle hndCFFT_F32)                            | Unpacks N-point CFFT output to get CFFT of 2N-point real sequence, the output is written to buffer pointed to by CurrentOutPtr; only use CFFT_f32t version with this function
void CFFT_f32_pack(CFFT_F32_STRUCT_Handle hndCFFT_F32)                              | Packs N/2-point CFFT output to get N-point real sequence, the output is written to buffer pointed to by CurrentOutPtr; only use CFFT_f32t version with this function
void CFFT_f32_mag_TMU0(CFFT_F32_STRUCT_Handle hndCFFT_F32)                          | Computes the CFFT magnitude (no memory alignment needed) using TMU0 module; stored in CurrentOutPtr
void CFFT_f32s_mag_TMU0(CFFT_F32_STRUCT_Handle hndCFFT_F32)                         | Computes the scaled CFFT magnitude (no memory alignment needed) using TMU0 module; stored in CurrentOutPtr
void CFFT_f32_phase_TMU0(CFFT_F32_STRUCT_Handle hndCFFT_F32)                        | Computes the CFFT phase (no memory alignment needed) using TMU0 module; stored in CurrentOutPtr
void ICFFT_f32(CFFT_F32_STRUCT_Handle hndCFFT_F32)                                  | Computes the inverse CFFT, requires memory alignment for buffer(s)
void ICFFT_f32t(CFFT_F32_STRUCT_Handle hndCFFT_F32)                                 | Computes the inverse CFFT using statically generated Twiddle Factors table, requires memory alignment for buffer(s)

---

**32-bit Real Fast Fourier Transform Setters and Getters**

Function | Description
--- |---
void RFFT_f32_setInputPtr(RFFT_F32_STRUCT_Handle fh, const float *pi)               | Sets input pointer
float * RFFT_f32_getInputPtr(RFFT_F32_STRUCT_Handle fh)                             | Gets input pointer
void RFFT_f32_setOutputPtr(RFFT_F32_STRUCT_Handle fh, const float *po)              | Sets output pointer
float * RFFT_f32_getOutputPtr(RFFT_F32_STRUCT_Handle fh)                            | Gets output pointer
void RFFT_f32_setTwiddlesPtr(RFFT_F32_STRUCT_Handle fh, const float *pc)            | Sets twiddle factors pointer
float * RFFT_f32_getTwiddlesPtr(RFFT_F32_STRUCT_Handle fh)                          | Gets twiddle factors pointer
void RFFT_f32_setMagnitudePtr(RFFT_F32_STRUCT_Handle fh, const float *pm)           | Sets magnitude pointer
float * RFFT_f32_getMagnitudePtr(RFFT_F32_STRUCT_Handle fh)                         | Gets magnitude pointer
void RFFT_f32_setPhasePtr(RFFT_F32_STRUCT_Handle fh, const float *pp)               | Sets phase pointer
float * RFFT_f32_getPhasePtr(RFFT_F32_STRUCT_Handle fh)                             | Gets phase pointer
void RFFT_f32_setStages(RFFT_F32_STRUCT_Handle fh, const uint16_t st)               | Sets number of stages
uint16_t RFFT_f32_getStages(RFFT_F32_STRUCT_Handle fh)                              | Gets number of stages
void RFFT_f32_setFFTSize(RFFT_F32_STRUCT_Handle fh, const uint16_t sz)              | Sets the FFT size
uint16_t RFFT_f32_getFFTSize(RFFT_F32_STRUCT_Handle fh)                             | Gets the FFT size
void RFFT_ADC_f32_setInBufPtr(RFFT_ADC_F32_STRUCT_Handle fh, const uint16_t * pi)   | Sets ADC input buffer pointer
uint16_t *RFFT_ADC_f32_getInBufPtr(RFFT_ADC_F32_STRUCT_Handle fh)                   | Gets ADC input buffer pointer
void RFFT_ADC_f32_setTailPtr(RFFT_ADC_F32_STRUCT_Handle fh, const void * pt)        | Sets ADC tail pointer
void *RFFT_ADC_f32_getTailPtr(RFFT_ADC_F32_STRUCT_Handle fh)                        | Gets ADC tail pointer

**32-bit Real Fast Fourier Transform Functions**

Function | Description
--- |---
void RFFT_f32(RFFT_F32_STRUCT_Handle hndRFFT_F32)                                       | Computes RFFT, requires memory alignment for buffer(s)
void RFFT_f32u(RFFT_F32_STRUCT_Handle hndRFFT_F32)                                      | Computes RFFT, memory alignment not required
void RFFT_adc_f32(RFFT_ADC_F32_STRUCT_Handle hndRFFT_ADC_F32)                           | Computes RFFT with ADC input; input of uint16_t and output of float32_t, requires memory alignment for buffer(s)
void RFFT_adc_f32u(RFFT_ADC_F32_STRUCT_Handle hndRFFT_ADC_F32)                          | Computes RFFT with ADC input; input of uint16_t and output of float32_t, memory alignment not required
void RFFT_f32_win(float *pBuffer, const float *pWindow, const uint16_t size)            | Performs windowing function on the real buffer
void RFFT_adc_f32_win(uint16_t *pBuffer, const uint16_t *pWindow, const uint16_t size)  | Performs windowing function on the real ADC input buffer (uint16_t type)
void RFFT_f32_mag(RFFT_F32_STRUCT_Handle hndRFFT_F32)                                   | Computes the RFFT magnitude (no memory alignment needed); stored in MagBuf
void RFFT_f32s_mag(RFFT_F32_STRUCT_Handle hndRFFT_F32)                                  | Computes the scaled RFFT magnitude (no memory alignment needed); stored in MagBuf
void RFFT_f32_phase(RFFT_F32_STRUCT_Handle hndRFFT_F32)                                 | Computes the RFFT phase (no memory alignment needed); stored in PhaseBuf
void RFFT_f32_mag_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32)                              | Computes the RFFT magnitude (no memory alignment needed) using TMU0 module; stored in MagBuf
void RFFT_f32s_mag_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32)                             | Computes the scaled RFFT magnitude (no memory alignment needed) using TMU0 module; stored in MagBuf
void RFFT_f32_phase_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32)                            | Computes the RFFT phase (no memory alignment needed) using TMU0 module; stored in PhaseBuf
void RFFT_f32_sincostable(RFFT_F32_STRUCT_Handle hndRFFT_F32)                           | Generates Twiddle Factors for RFFT

---

**64-bit Complex Fast Fourier Transform Setters and Getters**

Function | Description
--- |---
void CFFT_f64_setInputPtr(CFFT_f64_Handle fh, const float64_t *pi)              | Sets input pointer
float64_t * CFFT_f64_getInputPtr(CFFT_f64_Handle fh)                            | Gets input pointer
void CFFT_f64_setOutputPtr(CFFT_f64_Handle fh, const float64_t *po)             | Sets output pointer
float64_t * CFFT_f64_getOutputPtr(CFFT_f64_Handle fh)                           | Gets output pointer
void CFFT_f64_setTwiddlesPtr(CFFT_f64_Handle fh, const float64_t *pc)           | Sets twiddle factors pointer
float64_t * CFFT_f64_getTwiddlesPtr(CFFT_f64_Handle fh)                         | Gets twiddle factors pointer
void CFFT_f64_setCurrInputPtr(CFFT_f64_Handle fh, const float64_t *pi)          | Sets current input pointer
float64_t * CFFT_f64_getCurrInputPtr(CFFT_f64_Handle fh)                        | Gets current input pointer
void CFFT_f64_setCurrOutputPtr(CFFT_f64_Handle fh, const float64_t *po)         | Sets current output pointer
float64_t * CFFT_f64_getCurrOutputPtr(CFFT_f64_Handle fh)                       | Gets current output pointer
void CFFT_f64_setStages(CFFT_f64_Handle fh, const uint16_t st)                  | Sets number of stages
uint16_t CFFT_f64_getStages(CFFT_f64_Handle fh)                                 | Gets number of stages
void CFFT_f64_setFFTSize(CFFT_f64_Handle fh, const uint16_t sz)                 | Sets the FFT size
uint16_t CFFT_f64_getFFTSize(CFFT_f64_Handle fh)                                | Gets the FFT size
void CFFT_f64_setInitFunction(CFFT_f64_Handle fh, const v_pfn_v pfn)            | Sets the initialization function pointer
v_pfn_v CFFT_f64_getInitFunction(CFFT_f64_Handle fh)                            | Gets the initialization function pointer
void CFFT_f64_setCalcFunction(CFFT_f64_Handle fh, const v_pfn_v pfn)            | Sets the calculation function pointer
v_pfn_v CFFT_f64_getCalcFunction(CFFT_f64_Handle fh)                            | Gets the calculation function pointer
void CFFT_f64_setMagFunction(CFFT_f64_Handle fh, const v_pfn_v pfn)             | Sets magnitude function pointer
v_pfn_v CFFT_f64_getMagFunction(CFFT_f64_Handle fh)                             | Gets magnitude function pointer
void CFFT_f64_setPhaseFunction(CFFT_f64_Handle fh, const v_pfn_v pfn)           | Sets phase function pointer
v_pfn_v CFFT_f64_getPhaseFunction(CFFT_f64_Handle fh)                           | Gets phase function pointer
void CFFT_f64_setWinFunction(CFFT_f64_Handle fh, const v_pfn_v pfn)             | Sets the window function pointer
v_pfn_v CFFT_f64_getWinFunction(CFFT_f64_Handle fh)                             | Gets the window function pointer
void CFFT_ADC_f64_setInBufPtr(CFFT_ADC_f64_Handle fh, const uint16_t * pi)      | Sets ADC input buffer pointer
uint16_t *CFFT_ADC_f64_getInBufPtr(CFFT_ADC_f64_Handle fh)                      | Gets ADC input buffer pointer
void CFFT_ADC_f64_setTailPtr(CFFT_ADC_f64_Handle fh, const void * pt)           | Sets ADC tail pointer
void *CFFT_ADC_f64_getTailPtr(CFFT_ADC_f64_Handle fh)                           | Gets ADC tail pointer


**64-bit Complex Fast Fourier Transform Functions**

Function | Description
--- |---
void CFFT_f64(CFFT_f64_Handle hndCFFT_f64)                                      | Computes CFFT, requires memory alignment for buffer(s)
void CFFT_f64u(CFFT_f64_Handle hndCFFT_f64)                                     | Computes CFFT, memory alignment not required
void CFFT_f64_mag(CFFT_f64_Handle hndCFFT_f64)                                  | Computes the CFFT magnitude (no memory alignment needed); stored in CurrentOutPtr
void CFFT_f64s_mag(CFFT_f64_Handle hndCFFT_f64)                                 | Computes the scaled CFFT magnitude (no memory alignment needed); stored in CurrentOutPtr
void CFFT_f64_phase(CFFT_f64_Handle hndCFFT_f64)                                | Computes the CFFT phase (no memory alignment needed); stored in CurrentOutPtr
void CFFT_f64_unpack(CFFT_f64_Handle hndCFFT_f64)                               | Unpacks N-point CFFT output to get CFFT of 2N-point real sequence, the output is written to buffer pointed to by p_currOutput
void CFFT_f64_pack(CFFT_f64_Handle hndCFFT_f64)                                 | Packs N/2-point CFFT output to get N-point real sequence, the output is written to buffer pointed to by p_currOutput
void ICFFT_f64(CFFT_f64_Handle hndCFFT_f64)                                     | Computes the inverse CFFT, requires memory alignment for buffer(s)
void ICFFT_f64u(CFFT_f64_Handle hndCFFT_f64)                                    | Computes the inverse CFFT, memory alignment not required

---

**64-bit Real Fast Fourier Transform Functions**

*NOTE: The 64-bit RFFT does not have setter and getter functions because these fields are shared using the CFFT_f64_Handle*

Function | Description
--- |---
void RFFT_f64(CFFT_f64_Handle hndCFFT_f64)                                              | Computes RFFT, requires memory alignment for buffer(s)
void RFFT_f64u(CFFT_f64_Handle hndCFFT_f64)                                             | Computes RFFT, memory alignment not required
void RFFT_adc_f64(CFFT_ADC_f64_Handle hndCFFT_ADC_f64)                                  | Computes RFFT with ADC input; input of uint16_t and output of float64_t, requires memory alignment for buffer(s)
void RFFT_adc_f64u(CFFT_ADC_f64_Handle hndCFFT_ADC_f64)                                 | Computes RFFT with ADC input; input of uint16_t and output of float64_t, memory alignment not required
void RFFT_adc_f64_win(uint16_t *pBuffer, const uint16_t *pWindow, const uint16_t size)  | Performs windowing function on the real ADC input buffer (uint16_t type)
void RFFT_f64_mag(CFFT_f64_Handle hndCFFT_f64)                                          | Computes the RFFT magnitude (no memory alignment needed); stored in CurrentOutPtr
void RFFT_f64s_mag(CFFT_f64_Handle hndCFFT_f64)                                         | Computes the scaled RFFT magnitude (no memory alignment needed); stored in CurrentOutPtr
void RFFT_f64_phase(CFFT_f64_Handle hndCFFT_f64)                                        | Computes the CFFT phase (no memory alignment needed); stored in CurrentOutPtr
`

let longWindDescription = `
**The below macros contain arrays of floating point values that apply the corresponding window, each of which range from 32 to 4096. For example: the Barthann 
Window has #define macros of arrays for BARTHANN32, BARTHANN64, BARTHANN128, ... , BARTHANN4096**

**Windowing**

Windowing Type | Example of Given Macro
---|---
Barthann            | #define BARTHANN64
Bartlett            | #define BARTLETT64
Blackman            | #define BLACKMAN64
Blackman-Harris     | #define BLACKMAN_HARRIS64
Bohman              | #define BOHMAN64
Cheb                | #define CHEB64
Flat Top            | #define FLAT_TOP64
Gaussian            | #define GAUSSIAN64
Hamming             | #define HAMMING64
Hann                | #define HANN64
Kaiser              | #define KAISER64
Nuttall             | #define NUTTALL64
Parzen              | #define PARZEN64
Rectangular         | #define RECTANGULAR64
Taylor              | #define TAYLOR64
Triangle            | #define TRIANGLE64
Turkey              | #define TURKEY64
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

let WIND_TYPE = [
    {name: "Barthann", displayName: ""},
    {name: "Bartlett", displayName: ""},
    {name: "Blackman", displayName: ""},
    {name: "Blackman-Harris", displayName: ""},
    {name: "Bohman", displayName: ""},
    {name: "Cheb", displayName: ""},
    {name: "Flat Top", displayName: ""},
    {name: "Gaussian", displayName: ""},
    {name: "Hamming", displayName: ""},
    {name: "Hann", displayName: ""},
    {name: "Kaiser", displayName: ""},
    {name: "Nuttall", displayName: ""},
    {name: "Parzen", displayName: ""},
    {name: "Rectangular", displayName: ""},
    {name: "Taylor", displayName: ""},
    {name: "Triangle", displayName: ""},
    {name: "Turkey", displayName: ""}
]
var moduleStatic = {
    name: "fpu",
    displayName: "FPU/TMU Global Settings",
    config: []
}
var window_configs = [];

for(let i = 0; i < WIND_TYPE.length; i++)
{
    window_configs = window_configs.concat([
        {
            name: "WIN_" + i,
            displayName     : WIND_TYPE[i].name,
            hidden          : true,
            default         : false
        },
    ])
}

let config = [
    {
        name: "fpuType",
        displayName : "FPU Configuration",
        description : "Choose FPU32 or FPU64 Configuration",
        default     : FPU_TYPE[0].name,
        options     : FPU_TYPE
    },
    {
        name: "windEnable",
        displayName: "Windowing Enable",
        description: "Includes arrays of different types of windowing",
        default : false,
        onChange : onChangeWindow
    },
    {
        name        : "windOptions",
        displayName : "Windowing Options",
        description : 'Choose what type(s) of windowing to include.',
        longDescription : longWindDescription,
        config      : window_configs
    },
]

function onChangeWindow(inst, ui)
{
    if(inst.windEnable == true)
    {
        for(let i = 0; i < WIND_TYPE.length; i++)
        {
            ui[window_configs[i].name].hidden = false;
        }
    }
    else if(inst.windEnable == false)
    {
        for(let i = 0; i < WIND_TYPE.length; i++)
        {
            ui[window_configs[i].name].hidden = true;
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
    return (Common.typeMatches(component.type, ["FFT"]));
}
var fftModule = {
    c2000wareLibraryName: "FFT",
    displayName: "FFT",
    defaultInstanceName: "myFFT",
    description: "Fast Fourier Transform",
    longDescription: longDescription,
    maxInstances    : 1,
    filterHardware : filterHardware,
    config: config,
    moduleInstances : (inst) => {
        var fftInst = [];

        fftInst.push({
            displayName: "CFFT Configurations",
            name: "CFFT",
            description: "",
            useArray : true,
            moduleName: "/libraries/dsp/FPU/FFT/CFFT.js",
            requiredArgs: {
                fpuType: inst.fpuType
            }
        });
        fftInst.push({
            displayName: "RFFT Configurations",
            name: "RFFT",
            description: "",
            useArray : true,
            moduleName: "/libraries/dsp/FPU/FFT/RFFT.js",
            requiredArgs: {
                fpuType: inst.fpuType
            }
        });
        return (fftInst);
    },
    modules: Common.autoForce("fpu", "/libraries/.meta/math/FPU/FPU.js"),
    templates: {
        c2000ware_libraries_h           : "/libraries/dsp/FPU/FFT/templates/fft.c2000ware_libraries.h.xdt",
        c2000ware_libraries_c           : "/libraries/dsp/FPU/FFT/templates/fft.c2000ware_libraries.c.xdt",
        c2000ware_libraries_opt         : "/libraries/dsp/FPU/FFT/templates/fft.c2000ware_libraries.opt.xdt",
        c2000ware_libraries_cmd_genlibs : "/libraries/dsp/FPU/FFT/templates/fft.c2000ware_libraries.cmd.genlibs.xdt",
    },
    validate : onValidate
};
exports = fftModule;