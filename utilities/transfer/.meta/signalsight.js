let transferCommon;
if (system.getProducts()[0].name.includes("C2000")) {
    transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else { transferCommon = system.getScript("/transfer/transferCommon.js"); }

let Common = system.getScript("/driverlib/Common.js");
let Pinmux = system.getScript("/driverlib/pinmux.js");

let options = [];

let config = [
    {
        name: "$name",
        description: "Name your MCU Signal Sight GUI. This will be the name of the GUI in your CCS window and GUI launcher inside the plugins folder.",
        hidden: false,
    },
    {
        name: "bufferSize",
        displayName: "Target Buffer Size",
        description: "Size of each buffer where sampled data for a plot channel is stored until it is ready to be transmitted to the MCU Signal Sight GUI. Note that this number (multiplied by 4) will decide how many float arrays are allocated. Reduce this size if the device memory is limited.",
        default: 100
    },
    {
        name: "pollingDisabled",
        displayName: "Virtual Oscilloscope Only",
        description: "",
        default: true,
        hidden: true
    },
    {
        name: "pingPongEnable",
        displayName: "Ping Pong Buffering Enable",
        description: "This feature will allow for continous streaming of data. Note that the memory used for buffering will double if this option is selected, so reduce the buffer size as needed.",
        default: true
    },
    // {
    //     name: "bufferingDebugModeEnable",
    //     displayName: "Buffering Debug Mode Enable",
    //     description: "",
    //     default: false,
    //     hidden: false
    // },
    {
        name: "terminalDebugModeEnable",  //implement later
        displayName: "Terminal Debug Mode Enable",
        description: "",
        default: false,
        hidden: true //use for debugging
     },
     {
        name: "validationMode", 
        displayName: "Validation Mode Enable",
        description: "",
        default: false,
        hidden: true //use for debugging in validation mode - custom copy paths in bat and all variables added in header files
     },
     {
        name: "eclipseHardcodedPath",  
        displayName: "Eclipse Path",
        description: "",
        default: "C:\\ti\\ccs1281\\ccs\\eclipse\\dropins-gc\\",
        hidden: true //use for debugging in validation mode - custom copy paths in bat and all variables added in header files
     },
     {
        name: "theiaHardcodedPath",
        displayName: "Theia Path",
        description: "",
        default: "C:\\ti\\ccs2010\\ccs\\theia\\ccs_plugins\\",
        hidden: true //use for debugging in validation mode - custom copy paths in bat and all variables added in header files
     },
];

function modules(inst) {
    var staticOwnedInstances = []

    return staticOwnedInstances
}

function moduleInstances(inst) {
    let ownedInstances = []
    var expModule = {
        name: "exporter",
        displayName: "Exporter",
        moduleName: transferCommon.getTransferPath() + "exporter.js",
        args: {
            $name: inst.$name + "_transferLayer",
        },
        requiredArgs: {
            mode: "dataBidirectional",
            packageMode: "SIGNAL SIGHT",
        }
    };
    var hashModule = {
        name: "hash",
        displayName: "Hash Table",
        //useArray: true,
        moduleName: transferCommon.getTransferPath() + "signalsight/hash/hashTable.js",
        requiredArgs: {
            pollingEnabled: !inst.pollingDisabled
        }
    };
    ownedInstances = ownedInstances.concat([expModule, hashModule])
    return ownedInstances
}

var signalsight = {
    displayName: "MCU Signal Sight (BETA)",
    defaultInstanceName: "myMCUSignalSight",
    maxInstances: 1,
    description: "Signal Sight Module",
    config: config,
    moduleInstances: moduleInstances,
    modules: modules,
    templates: {
        [transferCommon.getTransferPath() + "signalsight/signalsight.c.xdt"]: "",
        [transferCommon.getTransferPath() + "signalsight/signalsight.h.xdt"]: "",
        [transferCommon.getTransferPath() + "signalsight/index.html.xdt"]: "",
        [transferCommon.getTransferPath() + "signalsight/project.json.xdt"]: "",
        [transferCommon.getTransferPath() + "signalsight/package.json.xdt"]: "",
        [transferCommon.getTransferPath() + "gui_setup.bat.xdt"]: "",
    }
};




exports = signalsight;
