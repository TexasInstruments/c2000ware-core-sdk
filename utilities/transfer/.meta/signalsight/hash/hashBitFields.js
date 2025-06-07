
let transferCommon;
if (system.getProducts()[0].name.includes("C2000")) {
    transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else { transferCommon = system.getScript("/transfer/transferCommon.js"); }

let Common;
if (transferCommon.isC2000()) {
    Common = system.getScript("/driverlib/Common.js");
}
let list0to15 = [
    { name: 0 },
    { name: 1 },
    { name: 2 },
    { name: 3 },
    { name: 4 },
    { name: 5 },
    { name: 6 },
    { name: 7 },
    { name: 8 },
    { name: 9 },
    { name: 10 },
    { name: 11 },
    { name: 12 },
    { name: 13 },
    { name: 14 },
    { name: 15 },
]

let list0to31 = [
    { name: 0 },
    { name: 1 },
    { name: 2 },
    { name: 3 },
    { name: 4 },
    { name: 5 },
    { name: 6 },
    { name: 7 },
    { name: 8 },
    { name: 9 },
    { name: 10 },
    { name: 11 },
    { name: 12 },
    { name: 13 },
    { name: 14 },
    { name: 15 },
    { name: 16 },
    { name: 17 },
    { name: 18 },
    { name: 19 },
    { name: 20 },
    { name: 21 },
    { name: 22 },
    { name: 23 },
    { name: 24 },
    { name: 25 },
    { name: 26 },
    { name: 27 },
    { name: 28 },
    { name: 29 },
    { name: 30 },
    { name: 31 },
]

function onChangeUI(inst, ui) {
    if (inst.variableType == "uint16_t" || inst.variableType == "int16_t" || inst.variableType == "boolean") {
        if (inst.singleBit) {
            ui["sixteenBitOptionsEnd"].hidden = true;
        }
        else {
            ui["sixteenBitOptionsEnd"].hidden = false;
        }
        ui["thirtytwoBitOptionsEnd"].hidden = true;
        ui["sixteenBitOptionsStart"].hidden = false;
        ui["thirtytwoBitOptionsStart"].hidden = true;
    }
    else {
        if (inst.singleBit) {
            ui["thirtytwoBitOptionsEnd"].hidden = true;
        }
        else {
            ui["thirtytwoBitOptionsEnd"].hidden = false;
        }
        ui["sixteenBitOptionsStart"].hidden = true;
        ui["sixteenBitOptionsEnd"].hidden = true;
        ui["thirtytwoBitOptionsStart"].hidden = false;
    }
}
let config = [
    {
        name: "$name",
        hidden: false,
    },
    {
        name: "hashTable",
        hidden: true,
        default: "",

    },
    {
        name: "hashElement",
        hidden: true,
        default: "",

    },
    {
        name: "variableType",
        displayName: "Variable Type",
        hidden: true,
        default: "float",
        options: [
            { name: "uint16_t", displayName: "16-bit Unsigned Int" },
            { name: "uint32_t", displayName: "32-bit Unsigned Int" },
            { name: "int16_t", displayName: "16-bit Signed Int" },
            { name: "int32_t", displayName: "32-bit Signed Int" },
            { name: "bool", displayName: "16-bit Boolean" },
            { name: "float", displayName: "32-bit Floating Point" }
        ],
        onChange: onChangeUI
    },
    {
        name: "singleBit",
        displayName: "Single Bit",
        hidden: false,
        default: true,
        onChange: onChangeUI

    },
    {
        name: "sixteenBitOptionsStart",
        displayName: "Start Bit Index",
        hidden: true,
        default: 0,
        options: list0to15,
    },
    {
        name: "sixteenBitOptionsEnd",
        displayName: "End Bit Index",
        hidden: true,
        default: 0,
        options: list0to15,
    },
    {
        name: "thirtytwoBitOptionsStart",
        displayName: "Start Bit Index",
        hidden: false,
        default: 0,
        options: list0to31,
    },
    {
        name: "thirtytwoBitOptionsEnd",
        displayName: "End Bit Index",
        hidden: true,
        default: 0,
        options: list0to31,
    },

];

function moduleInstances(inst) {
    var ownedInstances = []

    return ownedInstances
}

function modules(inst) {
    var staticOwnedInstances = []

    return staticOwnedInstances
}

function onValidate(inst, validation) {
    /*if (inst.streamable && inst.variableType != "float") {
        validation.logError(
            "Only variables with a float type can be streamed.",
            inst, "streamable");
    }*/
}

var hashBitfieldModule = {
    displayName: "Hash Variable BitField",
    defaultInstanceName: "myHashVariableBitField",
    description: "Hash Variable BitField Definition",
    config: config,
    moduleInstances: moduleInstances,
    modules: modules,
    templates: {
    },
    validate: onValidate
};




exports = hashBitfieldModule;
