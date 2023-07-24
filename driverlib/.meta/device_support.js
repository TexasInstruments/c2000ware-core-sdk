let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let references = system.getScript("/driverlib/PeripheralComponentsReferences.js");

var staticConfig = []

staticConfig.push(
    {
        name: "build",
        displayName : "Driverlib Build",
        options: [
            { name: "Debug", displayName: "Debug"     },
            { name: "Release", displayName: "Release" }
        ],
        default: "Debug"
    },
    {
        name: "useStandardCodeStartBranch",
        displayName: "Use Standard Code Start Branch",
        default: true
    }
)



function modules(inst)
{
    var mods = []
    mods = [
        {
            name: "sysctl",
            moduleName: "/driverlib/sysctl.js",
        }
    ];  

    if (inst.useStandardCodeStartBranch)
    {
        mods.push({
            name: "codestartbranch",
            moduleName: "/driverlib/codestartbranch.dynamic.js",
        })
    }

    return mods

}

function onValidate(inst, validation) 
{    
    if ((!Common.isMultiCoreSysConfig()) && (Common.isContextCPU2())){
        validation.logWarning("You will not be able to use clocking functions, unless both CPU1 and CPU2 are open in SysConfig", inst, "useStandardCodeStartBranch");
    }
}

var mod = {
    displayName: "Device Support",
    maxInstances: 1,
    defaultInstanceName: "myDEVICESUPPORT",
    description: "Device Support",
    longDescription: "",
    moduleStatic : {
        config          : staticConfig,
        modules         : modules,
        validate      : onValidate,
    },
    references : [
        //references.getReferencePath("driverlib_h"),
    ],
    templates: {
        "/driverlib/device/device.c.xdt" : "",
        "/driverlib/device/device.h.xdt" : "",
    }

};




exports = mod;