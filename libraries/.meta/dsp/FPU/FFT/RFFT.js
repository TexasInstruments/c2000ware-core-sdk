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
    {name: "RFFT_f64", displayName : "RFFT64 Memory Aligned"},
    {name: "RFFT_f64u", displayName : "RFFT64 Memory Unaligned"},
]
let MAG_TYPES = [
    {name: "RFFT_f64_mag", displayName : "RFFT64 Magnitude"},
    {name: "RFFT_f64s_mag", displayName : "RFFT64 Magnitude (Scaled)"},
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
        name        : "magPtr",
        displayName : "Magnitude Buffer Pointer",
        default     : ""
    },
    {
        name        : "phasPtr",
        displayName : "Phase Buffer Pointer",
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
        longDescription : "NOTE: When using pre-generated twiddle factors (e.g. this option is true), use a function with a 't' after the RFFT_f32",
        default : true,
        onChange : onChangeTwiddle
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
    {
        name : "adcEnable",
        displayName : "RFFT ADC: Enable RFFT ADC",
        description : "Requires an RFFT module to utilize RFFT ADC struct",
        default : false,
        hidden  : true,                                                     //FIXME: Remove once RFFT ADC example is working
        onChange : onChangeAdc
    },
    {
        name : "inAdcPtr",
        displayName : "RFFT ADC: Input Pointer (ADC)",
        description : "Pointer to input buffer",
        default : "",
        hidden  : true
    }
]

function onChangeFpu(inst, ui)
{
    if(inst.fpuType == FPU_TYPE[0].name)
    {
        ui.magPtr.hidden = false;
        ui.phasPtr.hidden = false;
        ui.sincosFunction.hidden = false;
        ui.coeffPtr.hidden = inst.sincosFunction;
        ui.calcFunction.hidden = true;
        ui.magFunction.hidden = true;
    }
    else if(((Common.getDeviceName() == "F2838x") || (Common.getDeviceName() == "F28P65x")) && (inst.fpuType == FPU_TYPE[1].name))
    {
        ui.magPtr.hidden = true;
        ui.phasPtr.hidden = true;
        ui.sincosFunction.hidden = true;
        ui.coeffPtr.hidden = true;
        ui.calcFunction.hidden = false;
        ui.magFunction.hidden = false;
    }
}
function onChangeTwiddle(inst, ui)
{
    ui.coeffPtr.hidden = inst.sincosFunction;
}
function onChangeAdc(inst, ui)
{
    ui.inAdcPtr.hidden = !inst.adcEnable;
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
    if((inst.inPtr == "") || (inst.outPtr == "") || ((inst.adcEnable == true) && ((inst.inAdcPtr == ""))) || ((inst.fpuType == FPU_TYPE[0].name) &&
        (inst.sincosFunction == false) && (inst.coeffPtr == "")))
    {
        //Since magnitude and phase are optionally used, error logging not included for them
        validation.logError("All pointers must point to valid arrays", inst);
    }
    if((inst.inPtr == inst.outPtr) || ((inst.fpuType == FPU_TYPE[0].name) && ( 
        (inst.inPtr == inst.magPtr) || (inst.inPtr == inst.phasPtr) || (inst.inPtr == inst.coeffPtr) || (inst.outPtr == inst.magPtr) || 
        (inst.outPtr == inst.phasPtr) || (inst.outPtr == inst.coeffPtr) || (inst.coeffPtr == inst.magPtr) || (inst.coeffPtr == inst.phasPtr) || (inst.magPtr == inst.phasPtr))))
    {
        validation.logError("No duplicate names allowed within FFT object", inst);
    }
    if((inst.adcEnable == true) && ((inst.inAdcPtr == inst.outPtr) || (inst.inAdcPtr == inst.inPtr) || ((inst.fpuType == FPU_TYPE[0].name) && ( 
        (inst.inAdcPtr == inst.magPtr) || (inst.inAdcPtr == inst.phasPtr) || ((inst.sincosFunction == false) && (inst.inAdcPtr == inst.coeffPtr)) || (inst.inAdcPtr == inst.magPtr)))))
    {
        validation.logError("No duplicate names allowed within FFT object", inst);
    }
}

var rfftModule = {
    c2000wareLibraryName: "RFFT",
    displayName: "RFFT",
    defaultInstanceName: "myRFFT",
    description: "Real FFT",
    config: config,
    validate : onValidate
}
exports = rfftModule;