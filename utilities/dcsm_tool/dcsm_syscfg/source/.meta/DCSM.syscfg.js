"use strict";
/*global exports, system*/

let Common   = system.getScript("/utilities/dcsm_tool/dcsm_syscfg/source/Common.js");

var OTPModulePath = "/utilities/dcsm_tool/dcsm_syscfg/source/ZONE_OTP_F28X7x";
if (["F28004x", "F28002x", "F2838x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x"].includes(Common.getDeviceName()))
{
    OTPModulePath = "/utilities/dcsm_tool/dcsm_syscfg/source/ZONE_OTP";
}

/* Intro splash on GUI */
let longDescription = `DCSM Tool Configuration

For more information on the tool visit:
*   Application Report: [Tool Overview](https://www.ti.com/lit/spracp8)

`;

function moduleInstances(inst)
{
    var requiredArgs = {}
    if (["F2837xD"].includes(Common.getDeviceName()))
    {
        if (system.context == "CPU2")
        {
            requiredArgs = {
                selectedCPU : "CPU2"
            }
        }
        else
        {
            requiredArgs = {
                selectedCPU : "CPU1"
            }
        }

    }
    let components = [
        {
            moduleName: OTPModulePath,
            name: "ZONE1_OTP",
            displayName: "ZONE1 Header",
            args: { zone : 1 },
            collapsed: true,
            requiredArgs: requiredArgs
        },
        {
            moduleName: "/utilities/dcsm_tool/dcsm_syscfg/source/ZONE",
            name: "ZONE1",
            displayName: "ZONE1 LINKPOINTER + Zone-Select Block",
            args: { zone : 1 },
            collapsed: true
        },        
        {
            moduleName: OTPModulePath,
            name: "ZONE2_OTP",
            displayName: "ZONE2 Header",
            args: { zone : 2 },
            collapsed: true,
            requiredArgs: requiredArgs
        },
        {
            moduleName: "/utilities/dcsm_tool/dcsm_syscfg/source/ZONE",
            name: "ZONE2",
            displayName: "ZONE2 LINKPOINTER + Zone-Select Block",
            args: { zone : 2 },
            collapsed: true
        },
    ];
    // if (["F28004x", "F28002x"].includes(Common.getDeviceName()))
    // {
    //     if (inst["csm"])
    //     {
    //         components[2].args["useZone"] = false;
    //     }
    // }

    return components;
}

var config = [];

// if (["F28004x", "F28002x"].includes(Common.getDeviceName()))
// {
//     config = [
//         {
//             name: "csm",
//             displayName : "CSM Style",
//             hidden      : false,
//             default     : false
//         }
//     ]
// }

// Define the common/portable base Watchdog
exports = {
    displayName         : "DCSM",
    description         : "DCSM",
    defaultInstanceName : "DCSM",
    longDescription     : longDescription,
    maxInstances        : 1,
    moduleInstances     : moduleInstances,
    modules: (inst) => {
        if (inst) {
            return [
                {
                    name: "pullInTemplateASM",
                    moduleName: "/utilities/dcsm_tool/dcsm_syscfg/source/templates/dcsm.asm.dynamic.js",
                },
                {
                    name: "pullInTemplateCMD",
                    moduleName: "/utilities/dcsm_tool/dcsm_syscfg/source/templates/dcsm.cmd.dynamic.js",
                }
            ];  
        }
        return [];
    },
    config              : config
};

// buttonText: "Run Compensation Designer",
//         onLaunch: (inst) => {
//             (console.log(inst["ZONE1_OTP"]));
//             return {
//                 command: "button.bat",
//                 args: []
//             };
//         },
//         onComplete: (inst, ui, result) => {
//             console.log(result);
//         },