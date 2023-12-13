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
        name        : "coeffPtr",
        displayName : "Filter Coefficients Pointer",
        default     : ""
    },
    {
        name        : "dBuffPtr",
        displayName : "Delay Buffer Pointer",
        default     : ""
    },
    {
        name        : "cbIndex",
        displayName : "Circular Buffer Index",
        default     : 0,
        hidden      : false
    },
    //These two fields are not pointers, need to initialize? No examples, nothing to look at
    /*{
        name        : "input",
        displayName : "Input value",
        default     : 0,
        hidden      : false
    },
    {
        name        : "Output",
        displayName : "Output value",
        default     : 0,
        hidden      : false
    },
    */
    {
        name        : "filterOrder",
        displayName : "Order of FIR filter",
        description : "Number of Taps = Order + 1",
        longDescription : "Number of Taps = Order + 1",
        default     : 1
    },
    
    {
        name        : "inPtr",
        displayName : "Input Buffer Pointer",
        default     : "",
        hidden      : true
    },
    {
        name        : "outPtr",
        displayName : "Output Buffer Pointer",
        default     : "",
        hidden      : true
    },
]

function onChangeFpu(inst, ui)
{
    if(inst.fpuType == FPU_TYPE[0].name)
    {
        ui.inPtr.hidden = true;
        ui.outPtr.hidden = true;
        ui.cbIndex.hidden = false;
    }
    else if(((Common.getDeviceName() == "F2838x") || (Common.getDeviceName() == "F28P65x")) && (inst.fpuType == FPU_TYPE[1].name))
    {
        ui.inPtr.hidden = false;
        ui.outPtr.hidden = false;
        ui.cbIndex.hidden = true;
    }
}
function onValidate(inst, validation)
{
    if((inst.filterOrder > 65535) || (inst.filterOrder < 0))
    {
        validation.logError("Filter order must be within range of uint16_t", inst, "filterOrder");
    }
    if((inst.coeffPtr == "") || (inst.dBuffPtr == "") || ((((Common.getDeviceName() == "F2838x") || (Common.getDeviceName() == "F28P65x")) && (inst.fpuType == FPU_TYPE[1].name)) && ((inst.inPtr == "") || (inst.outPtr == ""))))
    {
        validation.logError("All pointers must point to valid arrays", inst);
    }
    if((inst.coeffPtr == inst.dBuffPtr) || ((((Common.getDeviceName() == "F2838x") || (Common.getDeviceName() == "F28P65x")) && (inst.fpuType == FPU_TYPE[1].name)) && ((inst.inPtr == inst.coeffPtr) || (inst.outPtr == inst.coeffPtr) || (inst.outPtr == inst.inPtr) ||
    (inst.outPtr == inst.dBuffPtr) || (inst.inPtr == inst.dBuffPtr))))
    {
        validation.logError("No duplicate names allowed within FFT object", inst);
    }
}

var firModule = {
    c2000wareLibraryName: "FIR",
    displayName: "FIR",
    defaultInstanceName: "myFIR",
    description: "Finite Impulse Response",
    config: config,
    validate : onValidate
}
exports = firModule;