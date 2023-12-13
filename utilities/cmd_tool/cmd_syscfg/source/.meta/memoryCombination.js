"use strict";
/*global exports, system*/
let meminfo   = system.getScript("/utilities/cmd_tool/cmd_syscfg/source/" + system.deviceData.device.toLowerCase() + "_memoryInfo.js");
let CMDCommon = system.getScript("/utilities/cmd_tool/cmd_syscfg/source/CMDCommon.js");


var memoryInfo = meminfo.memoryInfo;


var config = [
    {
        name: "$name",
        hidden: false,
    },
    {
        name: "group",
        displayName: "Memory Group",
        default: "",
    },
    {
        name: "combination",
        default: [],
        options: (inst) => {
            var memInfoGroup = CMDCommon.getDeviceMemoryRanges().filter(
                function(element, index) {
                    if (element.group == inst.group)
                    {
                        return element
                    }
                }
            );

            var memoryOptions = []
            for (var memInfo of memInfoGroup){
                memoryOptions.push({
                    name: memInfo.name
                })
            }

            return memoryOptions
        }
    }
];


function onValidate(inst, validation) {
    
}

// Define the common/portable base Watchdog
exports = {
    displayName         : "Memory Combination",
    defaultInstanceName : "memCombination",
    config              : config,
    validate            : onValidate
};
