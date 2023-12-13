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
        default     : FPU_TYPE[0].name
    },
    {
        name        : "coeffPtrA",
        displayName : "Denominator Coefficients Pointer",
        default     : ""
    },
    {
        name        : "coeffPtrB",
        displayName : "Numerator Coefficients Pointer",
        default     : ""
    },
    {
        name        : "dBuffPtr",
        displayName : "Delay Buffer Pointer",
        default     : ""
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
        name        : "scalePtr",
        displayName : "Biquad Scale Pointer",
        default     : ""
    },
    {
        name        : "filterOrder",
        displayName : "Order of FIR filter",
        description : "Number of Taps = Order + 1",
        longDescription : "Number of Taps = Order + 1",
        default     : 1
    },
]

function onValidate(inst, validation)
{
    if((inst.filterOrder > 65535) || (inst.filterOrder < 0))
    {
        validation.logError("Filter order must be within range of uint16_t", inst, "filterOrder");
    }
    if((inst.coeffPtrA == "") || (inst.coeffPtrB == "") || (inst.dBuffPtr == "") || (inst.inPtr == "") || (inst.outPtr == "") || (inst.scalePtr == ""))
    {
        validation.logError("All pointers must point to valid arrays", inst);
    }
    if((inst.coeffPtrA == inst.coeffPtrB) || (inst.coeffPtrA == inst.dBuffPtr) || (inst.coeffPtrA == inst.inPtr) || (inst.coeffPtrA == inst.outPtr) || 
        (inst.coeffPtrA == inst.scalePtr) || (inst.coeffPtrB == inst.dBuffPtr) || (inst.coeffPtrB == inst.inPtr) || (inst.coeffPtrB == inst.outPtr) || 
        (inst.coeffPtrB == inst.scalePtr) || (inst.dBuffPtr == inst.inPtr) || (inst.dBuffPtr == inst.outPtr) || (inst.dBuffPtr == inst.scalePtr) || 
        (inst.inPtr == inst.outPtr) || (inst.inPtr == inst.scalePtr) || (inst.outPtr == inst.scalePtr))
    {
        validation.logError("No duplicate names allowed within FFT object", inst);
    }
}

var iirModule = {
    c2000wareLibraryName: "IIR",
    displayName: "IIR",
    defaultInstanceName: "myIIR",
    description: "Infinite Impulse Response",
    config: config,
    validate : onValidate
}
exports = iirModule;