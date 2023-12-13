var cmd_export = {}

if ([ "F2837xD",
      "F2837xS",
      "F2807x",
      "F28004x",
      "F28003x",
      "F2838x",
      "F28002x",
      "F280013x",
      "F280015x",
      "F28P65x",
      "F28P55x"
    ].includes(system.deviceData.deviceId))
{

    var views = []
    views.push(
        {
            "name": "/utilities/cmd_tool/cmd_syscfg/source/templates/memoryConfig.xdt",
            "displayName": "Linker Memory Configuration Info",
            "viewType": "markdown"
        },
    )

    cmd_export = {
        displayName: "Linker CMD Tool",
        templates:
        [
            {
                name      : "/utilities/cmd_tool/cmd_syscfg/source/templates/device_cmd.cmd.xdt",
                //description : "Device Linker Command File",
                outputPath: "device_cmd.cmd"
            },
            {
                name      : "/utilities/cmd_tool/cmd_syscfg/source/templates/device_cmd.c.xdt",
                //description : "Device Linker Command File Memory Initialization",
                outputPath: "device_cmd.c"
            },
            {
                name      : "/utilities/cmd_tool/cmd_syscfg/source/templates/device_cmd.h.xdt",
                //description : "Device Linker Command File Memory Initialization",
                outputPath: "device_cmd.h"
            },
            {
                name      : "/utilities/cmd_tool/cmd_syscfg/source/templates/device_cmd.opt.xdt",
                //description : "Device Linker Command File Memory Initialization",
                outputPath: "device_cmd.opt"
            },
            {
                name      : "/utilities/cmd_tool/cmd_syscfg/source/templates/device_cmd.cmd.genlibs.xdt",
                //description : "Device Linker Command File Memory Initialization",
                outputPath: "device_cmd.cmd.genlibs"
            }
        ],
        views: views,
        topModules:
        [
            {
                displayName: "Linker Command File Configuration",
                description: "Configure linker CMD file.",
                modules:
                [
                    "/utilities/cmd_tool/cmd_syscfg/source/CMD",            
                ]
            }
        ]
    }
}

exports = cmd_export