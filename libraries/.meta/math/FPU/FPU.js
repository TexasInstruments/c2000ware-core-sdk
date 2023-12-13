let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let longDescription = `FPU Processor Configuration Manager`

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

let TMU_TYPE;
if((Common.getDeviceName() == "F2807x") || (Common.getDeviceName() == "F28004x") || (Common.getDeviceName() == "F2837xD") || (Common.getDeviceName() == "F2837xS") || 
(Common.getDeviceName() == "F2838x") || (Common.getDeviceName() == "F280013x") || (Common.getDeviceName() == "F280015x"))
{
    TMU_TYPE = [
        {name: "NONE",     displayName: "NONE"},
        {name: "TMU0",     displayName: "TMU0"},
    ];
}
else if((Common.getDeviceName() == "F28002x") || (Common.getDeviceName() == "F28003x") || (Common.getDeviceName() == "F28P55x") || (Common.getDeviceName() == "F28P65x"))
{
    TMU_TYPE = [
        {name: "NONE",     displayName: "NONE"},
        {name: "TMU1",     displayName: "TMU1"},
    ];
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
        name: "tmuType",
        displayName : "TMU Configuration",
        description : "Choose to Enable TMU",
        default     : TMU_TYPE[1].name,
        options     : TMU_TYPE
    }
];

function onValidate(inst, validation){
    //In OTHER libraries that use FPU support, check this module to make sure it matches current configuration:
    /*var fpuMod = system.modules["/libraries/math/FPU/FPU.js"];
    if(fpuMod)
    {
        if(fpuMod.$static.fpuType != inst.fpuType)
        {
            validation.logError("FPU Options must be the same across modules.", inst, "fpuType");
        }
    }*/
}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["FPU"]));
}
var fpuModule = {
    c2000wareLibraryName: "FPU",
    displayName: "FPU",
    defaultInstanceName: "myFPU",
    description: "Floating-Point Unit",
    longDescription: longDescription,
    filterHardware : filterHardware,
    maxInstances : 1,
    moduleStatic : {
        config: config
    },
    templates: {
        c2000ware_libraries_opt         : "/libraries/math/FPU/templates/fpu.c2000ware_libraries.opt.xdt",
    },
    validate : onValidate
};
exports = fpuModule;