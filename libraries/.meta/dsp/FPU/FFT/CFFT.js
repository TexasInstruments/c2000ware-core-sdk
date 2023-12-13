let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

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

let CALC_TYPES = [
    {name: "CFFT_f64", displayName : "CFFT64 Memory Aligned"},
    {name: "CFFT_f64u", displayName : "CFFT64 Memory Unaligned"},
    {name: "ICFFT_f64", displayName : "Inverse CFFT64 Memory Aligned"},
    {name: "ICFFT_f64u", displayName : "Inverse CFFT64 Memory Unaligned"},
]
let MAG_TYPES = [
    {name: "CFFT_f64_mag", displayName : "CFFT64 Magnitude"},
    {name: "CFFT_f64s_mag", displayName : "CFFT64 Magnitude (Scaled)"},
]


let config = [
    {
        name: "$name",
        hidden : false
    },
    {
        name: "fpuType",
        displayName : "FPU Configuration",
        description : "Choose FPU32 or FPU64 Configuration",
        default     : FPU_TYPE[0].name,
        onChange    : onChangeFpu
    },
    {
        name        : "inPtr",
        displayName : "Input Buffer Pointer",
        default     : ""
    },
    {
        name        : "outPtr",
        displayName : "Output Buffer Pointer",
        default     : ""
    },
    {
        name        : "numStages",
        displayName : "Number of FFT Stages",
        longDescription :   "The number of stages must be log base 2 of FFTSize",
        default     : 5
    },
    {
        name        : "fftSize",
        displayName : "FFT Size",
        longDescription : "FFT size must be a power of 2; the size must be at least 32 and at most 1024; input/output/current input/current output pointers are FFT Size in length",
        default     : 32,
        getValue    : (inst) => {
            return Math.pow(2, inst.numStages);
        }
    },
    {
        name : "sincosFunction",
        displayName : "Use Predefined Twiddle Factors",
        longDescription : "NOTE: When using pre-generated twiddle factors (e.g. this option is true), use a function with a 't' after the CFFT_f32",
        default     : true,
        hidden      : false,
        onChange    : onChangeTwiddle
    },
    {
        name        : "coeffPtr",
        displayName : "Twiddle Factors Pointer",
        default     : "",
        hidden      : true
    },
    {
        name        : "calcFunction",
        displayName : "Calculation Functions",
        longDescription : "Choose a specific calculation function, and do <name>_handle->calc(<name>_handle); to run the calculation function. This can be changed during runtime",
        default     : CALC_TYPES[0].name,
        options     : CALC_TYPES,
        hidden      : true
    },
    {
        name        : "magFunction",
        displayName : "Magnitude Functions",
        longDescription : "Choose a specific magnitude function, and do <name>_handle->mag(<name>_handle); to run the calculation function. This can be changed during runtime",
        default     : MAG_TYPES[0].name,
        options     : MAG_TYPES,
        hidden      : true
    },
]

function onChangeFpu(inst, ui)
{
    if(inst.fpuType == FPU_TYPE[0].name)
    {
        ui.coeffPtr.hidden = false;
        ui.sincosFunction.hidden = false;
        ui.coeffPtr.hidden = inst.sincosFunction;
        ui.calcFunction.hidden = true;
        ui.magFunction.hidden = true;
    }
    else if(((Common.getDeviceName() == "F2838x") || (Common.getDeviceName() == "F28P65x")) && (inst.fpuType == FPU_TYPE[1].name))
    {
        ui.coeffPtr.hidden = true;
        ui.sincosFunction.hidden = true;
        ui.calcFunction.hidden = false;
        ui.magFunction.hidden = false;
    }
}
function onChangeTwiddle(inst, ui)
{
    ui.coeffPtr.hidden = inst.sincosFunction;
}
function onValidate(inst, validation)
{
    if(inst.fftSize < 32)
    {
        validation.logError("FFT size must be at least 32", inst, "fftSize");
    }
    if(inst.fftSize > 1024)
    {
        validation.logError("FFT size cannot be more than 1024", inst, "fftSize");
    }
    if((inst.inPtr == "") || (inst.outPtr == "") || ((inst.fpuType == FPU_TYPE[0].name) && (inst.coeffPtr == "") && (inst.sincosFunction == false)))
    {
        validation.logError("All pointers must point to valid arrays", inst);
    }
    if((inst.inPtr == inst.outPtr) || ((inst.fpuType == FPU_TYPE[0].name) && ((inst.inPtr == inst.coeffPtr) || (inst.outPtr == inst.coeffPtr))))
    {
        validation.logError("No duplicate names allowed within FFT object", inst);
    }
}

var cfftModule = {
    c2000wareLibraryName: "CFFT",
    displayName: "CFFT",
    defaultInstanceName: "myCFFT",
    description: "Complex FFT",
    config: config,
    validate : onValidate
}
exports = cfftModule;