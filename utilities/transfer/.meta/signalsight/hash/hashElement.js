
let transferCommon;
if (system.getProducts()[0].name.includes("C2000")) {
    transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else { transferCommon = system.getScript("/transfer/transferCommon.js"); }

let Common;
if (transferCommon.isC2000()) {
    Common = system.getScript("/driverlib/Common.js");
}

function onChangePollingFunctionality(inst, ui) {
    if (!inst["pollingEnabled"]) {
        ui["streamable"].readOnly = true;
        ui["permissions"].readOnly = true;
        ui["variableType"].readOnly = true;
        ui["bitfieldEnable"].hidden = true;
        inst["streamable"] = true;
        inst['permissions'] = "R";
        inst["variableType"] = "float"
        inst["bitfieldEnable"] = false;
        ui["streamable"].hidden = true;
        ui["permissions"].hidden = true;
    }
    else {
        ui["streamable"].readOnly = false;
        ui["permissions"].readOnly = false;
        ui["variableType"].readOnly = false
        ui["bitfieldEnable"].hidden = false;
        ui["streamable"].hidden = false;
        ui["permissions"].hidden = false;
    }
}

let config = [
    {
        name: "$name",
        hidden: false,
    },
    {
        name: "pollingEnabled",
        displayName: "GUI Polling Functionality Enabled",
        hidden: true,
        default: true,
        onChange: onChangePollingFunctionality,
    },
    {
        name: "useDifferentName",
        displayName: "Variable Name Uses Structures",
        hidden: true,  //make visible later
        default: false,
        onChange: (inst, ui) => {
            if (inst.useDifferentName) {
                ui["diffName"].hidden = false;
            }
            else {
                ui["diffName"].hidden = true;
            }
        },
    },
    {
        name: "diffName",
        displayName: "Variable Target Name",
        description: "Variable will display in the GUI as the entry for 'Name'",
        hidden: true,
        default: ""
    },
    {
        name: "hashTable",
        hidden: true,
        default: "",
    },
    {
        name: "displayNameEnable",
        displayName: "Add Display Name",
        hidden: true, //make visible later
        default: false,  
        onChange: (inst, ui) => {
            ui.displayName.hidden = !inst.displayNameEnable;
        },
    },
    {
        name: "displayName",
        displayName: "Display Name",
        hidden: true,
        default: "",
    },
    {
        name: "variableType",
        displayName: "Variable Type",
        hidden: false,
        default: "float",
        options: [
            { name: "uint16_t", displayName: "16-bit Unsigned Int" },
            { name: "uint32_t", displayName: "32-bit Unsigned Int" },
            { name: "int16_t", displayName: "16-bit Signed Int" },
            { name: "int32_t", displayName: "32-bit Signed Int" },
            { name: "bool", displayName: "16-bit Boolean" },
            { name: "float", displayName: "32-bit Floating Point" }
        ],
    },
    {
        name: "hashIndex",
        displayName: "Hash Table Index",
        hidden: true,
        readOnly: true,
        default: 0,
    },
    {
        name: "permissions",
        displayName: "GUI Permissions",
        hidden: false,
        default: "R",
        options: [
            { name: "RW", displayName: "Read & Write Permissions" },
            { name: "R", displayName: "Read Only Permissions" },
            { name: "W", displayName: "Write Only Permissions" },
        ],
    },
    {
        name: "streamable",
        displayName: "Streamability",
        hidden: false,
        default: true,
    },
    {
        name: "bitfieldEnable",
        displayName: "Define Bitfields?",
        hidden: false,
        default: false,
    },
    {
        name: "totalPagesForTable",
        displayName: "Total Pages",
        hidden: true,
        default: 0,
        onChange: (inst, ui) => {
            ui["pollingPage1"].hidden = !(inst.totalPagesForTable === 1);
            ui["pollingPage2"].hidden = !(inst.totalPagesForTable === 2);
            ui["pollingPage3"].hidden = !(inst.totalPagesForTable === 3);
            ui["pollingPage4"].hidden = !(inst.totalPagesForTable === 4);
            ui["pollingPage5"].hidden = !(inst.totalPagesForTable === 5);
            ui["pollingPage6"].hidden = !(inst.totalPagesForTable === 6);
            ui["pollingPage7"].hidden = !(inst.totalPagesForTable === 7);
            ui["pollingPage8"].hidden = !(inst.totalPagesForTable === 8);
            ui["pollingPage9"].hidden = !(inst.totalPagesForTable === 9);
            ui["pollingPage10"].hidden = !(inst.totalPagesForTable === 10);

            /*ui["streamable"].readOnly = (inst.totalPagesForTable === 0);
            ui["permissions"].readOnly = (inst.totalPagesForTable === 0);
            ui["variableType"].readOnly = (inst.totalPagesForTable === 0);
            ui["bitfieldEnable"].hidden = (inst.totalPagesForTable === 0);

            if (inst.totalPagesForTable === 0) {
                inst["streamable"] = true;
                inst['permissions'] = "R";
                inst["variableType"] = "float"
                inst["bitfieldEnable"] = false;
            }*/
        }
    },
    {
        name: "pollingPage1",
        displayName: "Enable Variable Update on Pages:",
        hidden: true,
        minSelections: 0,
        default: [],
        options: [
            { name: "polling0", displayName: "Enable Polling on Page 0" },
        ],
    },
    {
        name: "pollingPage2",
        displayName: "Enable Variable Update on Pages:",
        hidden: true,
        minSelections: 0,
        default: [],
        options: [
            { name: "polling0", displayName: "Enable Polling on Page 0" },
            { name: "polling1", displayName: "Enable Polling on Page 1" },
        ],
    },
    {
        name: "pollingPage3",
        displayName: "Enable Variable Update on Pages:",
        hidden: true,
        minSelections: 0,
        default: [],
        options: [
            { name: "polling0", displayName: "Enable Polling on Page 0" },
            { name: "polling1", displayName: "Enable Polling on Page 1" },
            { name: "polling2", displayName: "Enable Polling on Page 2" },
        ],
    },
    {
        name: "pollingPage4",
        displayName: "Enable Variable Update on Pages:",
        hidden: true,
        minSelections: 0,
        default: [],
        options: [
            { name: "polling0", displayName: "Enable Polling on Page 0" },
            { name: "polling1", displayName: "Enable Polling on Page 1" },
            { name: "polling2", displayName: "Enable Polling on Page 2" },
            { name: "polling3", displayName: "Enable Polling on Page 3" },
        ],
    },
    {
        name: "pollingPage5",
        displayName: "Enable Variable Update on Pages:",
        hidden: true,
        minSelections: 0,
        default: [],
        options: [
            { name: "polling0", displayName: "Enable Polling on Page 0" },
            { name: "polling1", displayName: "Enable Polling on Page 1" },
            { name: "polling2", displayName: "Enable Polling on Page 2" },
            { name: "polling3", displayName: "Enable Polling on Page 3" },
            { name: "polling4", displayName: "Enable Polling on Page 4" },
        ],
    },
    {
        name: "pollingPage6",
        displayName: "Enable Variable Update on Pages:",
        hidden: true,
        minSelections: 0,
        default: [],
        options: [
            { name: "polling0", displayName: "Enable Polling on Page 0" },
            { name: "polling1", displayName: "Enable Polling on Page 1" },
            { name: "polling2", displayName: "Enable Polling on Page 2" },
            { name: "polling3", displayName: "Enable Polling on Page 3" },
            { name: "polling4", displayName: "Enable Polling on Page 4" },
            { name: "polling5", displayName: "Enable Polling on Page 5" },
        ],
    },
    {
        name: "pollingPage7",
        displayName: "Enable Variable Update on Pages:",
        hidden: true,
        minSelections: 0,
        default: [],
        options: [
            { name: "polling0", displayName: "Enable Polling on Page 0" },
            { name: "polling1", displayName: "Enable Polling on Page 1" },
            { name: "polling2", displayName: "Enable Polling on Page 2" },
            { name: "polling3", displayName: "Enable Polling on Page 3" },
            { name: "polling4", displayName: "Enable Polling on Page 4" },
            { name: "polling5", displayName: "Enable Polling on Page 5" },
            { name: "polling6", displayName: "Enable Polling on Page 6" },
        ],
    },
    {
        name: "pollingPage8",
        displayName: "Enable Variable Update on Pages:",
        hidden: true,
        minSelections: 0,
        default: [],
        options: [
            { name: "polling0", displayName: "Enable Polling on Page 0" },
            { name: "polling1", displayName: "Enable Polling on Page 1" },
            { name: "polling2", displayName: "Enable Polling on Page 2" },
            { name: "polling3", displayName: "Enable Polling on Page 3" },
            { name: "polling4", displayName: "Enable Polling on Page 4" },
            { name: "polling5", displayName: "Enable Polling on Page 5" },
            { name: "polling6", displayName: "Enable Polling on Page 6" },
            { name: "polling7", displayName: "Enable Polling on Page 7" },
        ],
    },
    {
        name: "pollingPage9",
        displayName: "Enable Variable Update on Pages:",
        hidden: true,
        minSelections: 0,
        default: [],
        options: [
            { name: "polling0", displayName: "Enable Polling on Page 0" },
            { name: "polling1", displayName: "Enable Polling on Page 1" },
            { name: "polling2", displayName: "Enable Polling on Page 2" },
            { name: "polling3", displayName: "Enable Polling on Page 3" },
            { name: "polling4", displayName: "Enable Polling on Page 4" },
            { name: "polling5", displayName: "Enable Polling on Page 5" },
            { name: "polling6", displayName: "Enable Polling on Page 6" },
            { name: "polling7", displayName: "Enable Polling on Page 7" },
            { name: "polling8", displayName: "Enable Polling on Page 8" },
        ],
    },
    {
        name: "pollingPage10",
        displayName: "Enable Variable Update on Pages:",
        hidden: true,
        minSelections: 0,
        default: [],
        options: [
            { name: "polling0", displayName: "Enable Polling on Page 0" },
            { name: "polling1", displayName: "Enable Polling on Page 1" },
            { name: "polling2", displayName: "Enable Polling on Page 2" },
            { name: "polling3", displayName: "Enable Polling on Page 3" },
            { name: "polling4", displayName: "Enable Polling on Page 4" },
            { name: "polling5", displayName: "Enable Polling on Page 5" },
            { name: "polling6", displayName: "Enable Polling on Page 6" },
            { name: "polling7", displayName: "Enable Polling on Page 7" },
            { name: "polling8", displayName: "Enable Polling on Page 8" },
            { name: "polling9", displayName: "Enable Polling on Page 9" },
        ],
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
    if (inst.bitfieldEnable) {
        ownedInstances.push({
            name: "hashBitfields",
            displayName: " Hash Table Element Bitfields ",
            moduleName: transferCommon.getTransferPath() + "signalsight/hash/hashBitFields.js",
            useArray: true,
            minInstanceCount: Object.keys(JSON.parse(inst.hiddenTextFieldForInstanceAdderArgs)).length,
            collapsed: true,
            fixedArgs: JSON.parse(inst.hiddenTextFieldForInstanceAdderArgs),
            requiredArgs: {
                hashTable: inst.hashTable,
                hashElement: inst.$name,
                variableType: inst.variableType
            }
        })
    }
    return ownedInstances
}

function modules(inst) {
    var staticOwnedInstances = []

    return staticOwnedInstances
}

function onValidate(inst, validation) {
    if (inst.streamable && inst.variableType != "float") {
        validation.logError(
            "Only variables with a float type can be streamed.",
            inst, "streamable");
    }
}

var hashElementModule = {
    displayName: "Hash Variable",
    defaultInstanceName: "myHashVariable",
    description: "Hash Variable",
    config: config,
    moduleInstances: moduleInstances,
    modules: modules,
    templates: {
    },
    validate: onValidate
};




exports = hashElementModule;
