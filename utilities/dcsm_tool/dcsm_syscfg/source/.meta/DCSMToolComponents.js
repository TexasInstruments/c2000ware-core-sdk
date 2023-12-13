let Common   = system.getScript("/driverlib/Common.js");

var dcsm_export = {}

if ([ "F2837xD",
      "F2837xS",
      "F2807x",
      "F28004x",
      "F28003x",
      "F2838x",
      "F28002x",
      "F280013x",
      "F280015x",
      "F28P65x",].includes(Common.getDeviceName()))
{

    dcsm_export = {
        displayName: "DCSM Tool",
        templates:
        [
        
            {
                name      : "/utilities/dcsm_tool/dcsm_syscfg/source/templates/dcsm.asm.xdt",
                outputPath: "dcsm.asm"
            },
            {
                name      : "/utilities/dcsm_tool/dcsm_syscfg/source/templates/dcsm.cmd.xdt",
                outputPath: "dcsm.cmd"
            }
        ],

        topModules:
        [
            {
                displayName: "DCSM Configuration",
                description: "Configure secure zones.",
                modules:
                [
                    "/utilities/dcsm_tool/dcsm_syscfg/source/DCSM",            
                ]
            }
        ]
    }

    if ((system.context == "CPU2") && !["F2837xD"].includes(Common.getDeviceName()))
    {
        dcsm_export = {}
    }
    
}

exports = dcsm_export