let transferCommon;
if (system.getProducts()[0].name.includes("C2000")) {
    transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else { transferCommon = system.getScript("/transfer/transferCommon.js"); }

let Common;
if (transferCommon.isC2000()) {
    Common = system.getScript("/driverlib/Common.js");
}

let signalSight = system.modules[transferCommon.getTransferPath() + 'signalsight.js'];
let hashElements = system.modules[transferCommon.getTransferPath() + 'signalsight/hash/hashElement.js'];


let hashTablesToBuild = transferCommon.getNumberHashTableInstances();
let build = hashTablesToBuild > 0

function onChangePollingFunctionality(inst, ui) {
    ui["numberOfPollingPages"].hidden = !(inst["pollingEnabled"]);
    inst["numberOfPollingPages"] = !(inst["pollingEnabled"]) ? 0 : 1;
}

let config = [
    {
        name: "$name",
        hidden: false,
        description: "Name your hash table. Support for more than one table (corresponding to different application builds) will be added in future releases of the tool."
    },
    {
        name: "pollingEnabled",
        displayName: "GUI Polling Functionality Enabled",
        hidden: true,
        default: true,
        onChange: onChangePollingFunctionality,
    },
    {
        name: "enableBitfieldTypes",
        displayName: "Enable Bitfield Types",
        hidden: true,
        default: false,
    },
    {
        name: "buildEnable",
        displayName: "Enable Hash Table Build",
        hidden: true,  //make visible later
        default: true,
    },
    {
        name: "indexType",
        displayName: "Index Type",
        hidden: true,
        default: "stringKey",
        options: [
            { name: "stringKey", displayName: "Index by Name" },
            { name: "indexKey", displayName: "Index by Numerical ID" },
        ],
    },
    {
        name: "numberOfPollingPages",  //max is 10
        displayName: "Number of GUI Tabs",
        description: "Number of tabs present in the main tab container of the GUI. Maximum is 10.",
        hidden: false,
        default: 1,
    },
    {
        name: "hiddenTextFieldForInstanceAdderArgs",
        displayName: "Instance Adder Arguments (JSON)",
        hidden: true,
        default: JSON.stringify([]),
    },
];

function moduleInstances(inst) {
    var ownedInstances = []
    ownedInstances.push({
        name: "hashElements",
        displayName: " Hash Table Elements ",
        longDescription: "Add a Hash Table Element for each global variable from the application to plot in the MCU Signal Sight virtual oscilloscope. Input the name of the Hash Table Element as it appears in your application. More than four variables can be added here, but only four at a time can be simultaneously plotted in the MCU Signal Sight GUI. Note that currently only variables with a float type are supported for plotting.",
        moduleName: transferCommon.getTransferPath() + "signalsight/hash/hashElement.js",
        useArray: true,
        minInstanceCount: Object.keys(JSON.parse(inst.hiddenTextFieldForInstanceAdderArgs)).length,
        collapsed: false,
        fixedRequiredArgs: JSON.parse(inst.hiddenTextFieldForInstanceAdderArgs),
        requiredArgs: {
            hashTable: inst.$name,
            totalPagesForTable: inst.numberOfPollingPages,
            pollingEnabled: inst.pollingEnabled,
        }
    })
    return ownedInstances
}

function modules(inst) {
    var staticOwnedInstances = []

    return staticOwnedInstances
}

function onValidate(inst, validation) {
    let hashTables = system.modules[transferCommon.getTransferPath() + 'signalsight/hash/hashTable.js'];
    hashTablesToBuild = 0;
    if (hashTables) {
        for (let i = 0; i < hashTables.$instances.length; i++) {
            if (hashTables.$instances[i].buildEnable) {
                hashTablesToBuild++;
            }
        }
    }
    if (hashTablesToBuild > 1) {
        validation.logError(
            "Cannot Build more than one hash table at once - please only select 'Enable Hash Table Build' for one instance",
            inst, "buildEnable");
    }
    if (inst.numberOfPollingPages > 10) {
        validation.logError(
            "Signal Sight supports a maximum of 10 polling pages.",
            inst, "numberOfPollingPages");
    }
}

var tableModule = {
    displayName: "Hash Table",
    maxInstances: 1,
    defaultInstanceName: "myHashTable",
    description: "Hash Table Generator",
    config: config,
    moduleInstances: moduleInstances,
    modules: modules,
    templates: {
        [transferCommon.getTransferPath() + "signalsight/hash/target/signalsight_hash.c.xdt"]: "",
        [transferCommon.getTransferPath() + "signalsight/hash/target/signalsight_hash.h.xdt"]: "",
        [transferCommon.getTransferPath() + "signalsight/hash/host/signalsight_hash.json.xdt"]: "",
    },
    validate: onValidate
};




exports = tableModule;
