let Common   = system.getScript("/driverlib/Common.js");

var clb_export = {}

if ([ "F2837xD",
      "F2837xS",
      "F2807x",
      "F28004x",
      "F28003x",
      "F2838x",
      "F28002x",
      "F28P65x",
      "F28P55x",
      "F29H85x"].includes(Common.getDeviceName()))
{
    clb_export = {
        displayName: "C2000 CLB Configuration Tool",
        templates:
        [
        
            {
                name      : "/utilities/clb_tool/clb_syscfg/source/templates/hfile/clb.h.xdt",
                outputPath: "clb_config.h"
            },
            {
                name      : "/utilities/clb_tool/clb_syscfg/source/templates/cfile/clb.c.xdt",
                outputPath: "clb_config.c"
            },
            {
                name      : "/utilities/clb_tool/clb_syscfg/source/templates/dot/clb.dot.xdt",
                outputPath: "clb.dot"
            },
            {
                name      : "/utilities/clb_tool/clb_syscfg/source/templates/systemc/clb.sim.xdt",
                outputPath: "clb_sim.cpp"
            }
        ],

        topModules:
        [
            {
                displayName: "Configurable Logic Block",
                description: "Configure instances of CLB tiles.",
                modules:
                [
                    "/utilities/clb_tool/clb_syscfg/source/TILE",            
                ]
            }
        ],
    }
    if(system.getOS().includes("win"))
    {
        clb_export.templates.push({
            name      : "/utilities/clb_tool/clb_syscfg/source/templates/script/clb_simulation.bat.xdt",
            outputPath: "clb_simulation.bat"
        });            
    }
    else
    {
        clb_export.templates.push({
            name      : "/utilities/clb_tool/clb_syscfg/source/templates/script/clb_simulation.sh.xdt",
            outputPath: "clb_simulation.sh"
        })
    }
}

exports = clb_export