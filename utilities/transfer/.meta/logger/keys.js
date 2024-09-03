let transferCommon;
if (system.getProducts()[0].name.includes("C2000"))
{ transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else
{ transferCommon = system.getScript("/transfer/transferCommon.js");}

let Common;
if (transferCommon.isC2000())
{
    Common = system.getScript("/driverlib/Common.js");
}

let sizeOfType = {
    "uint8_t" :       1,
    "uint16_t" :    2,
    "int16_t" :     2,
    "uint32_t" :    4,
    "int32_t" :     4,
    "float" :       4,
    "bool" :       2,
    "uint8_t_array" : 1,
    "uint16_t_array" :    2,
    "int16_t_array" :     2,
    "uint32_t_array" :    4,
    "int32_t_array" :     4,
    "float_array" :       4,
    "bool_array" :       2,
}


let config = [
    {
        name: "$name",
        hidden: false,
    },
    {
        name: "group",
        hidden: true,
        default: "",

    },
    {
        name: "lengthToggle",
        displayName: "Define Values",
        description: "Designate if the amount of values used in a message for this key is predefined (ex. exporting registers) or if it is a variable length (ex. exporting Debugging messages).",
        readOnly: false,
        default: "Predefine Message Length",
        hidden: false,
        options: [
            { name: "Predefine Message Length" },
            { name: "Variable Message Length" },
        ],
        onChange: (inst, ui) => {
            if (inst.lengthToggle == "Predefine Message Length"){
                ui["length"].hidden = false;
                ui["lengthMax"].hidden = true;
            }
            else {
                ui["length"].hidden = true;
                ui["lengthMax"].hidden = false;
            }
        },
    },
    {
        name: "length",
        displayName: "Number of Array Values",
        default: 0,
        hidden: false,
        readOnly: false,
    },
    {
        name: "lengthMax",
        displayName: "Max Length of Value Array",
        description: "Maximum number of values in a frame based on Max TX Length Inputted",
        readOnly: true,
        default: 0,
        hidden: true,
        getValue: (inst) => {
            let bytesPerValue = sizeOfType[inst["valType"]];
            if(system.modules[transferCommon.getTransferPath() + "exporter.js"] != undefined){
                if(inst.group == "txKeyValuePairs"){
                    return Math.floor((system.modules[transferCommon.getTransferPath() + "exporter.js"].$instances[0].txLengthAvailable)/bytesPerValue);
                }
                else if(inst.group == "rxKeyValuePairs"){
                    return Math.floor((system.modules[transferCommon.getTransferPath() + "exporter.js"].$instances[0].rxLengthAvailable)/bytesPerValue);
                }
            }
        }
    },
    {
        name: "lengthValid",
        displayName: "Length Valid?",
        default: true,
        readOnly: true,
        hidden: true,
        getValue: (inst) => {
            if(system.modules[transferCommon.getTransferPath() + "exporter.js"] != undefined){
                if(inst.group == "txKeyValuePairs"){
                    let maxLength = system.modules[transferCommon.getTransferPath() + "exporter.js"].$instances[0].txLengthAvailable;
                    if(inst.size > maxLength){
                        return false;
                    }
                    else{
                        return true;
                    }
                }
                else if(inst.group == "rxKeyValuePairs"){
                    let maxLength = system.modules[transferCommon.getTransferPath() + "exporter.js"].$instances[0].rxLengthAvailable;
                    if(inst.size > maxLength){
                        return false;
                    }
                    else{
                        return true;
                    }
                }
            }
            else{
                return true;
            }
        }
    },
    {
        name: "valType",
        displayName: "Value(s) Type",
        description: "Define the data type of the values exported with this key.",
        default: "uint16_t_array",
        onChange: (inst, ui) => {
            if (inst.valType.includes("array")){
                inst.lengthToggle == "Predefine Message Length";
                ui["lengthToggle"].hidden = false;
                ui["length"].readOnly = false;
            }
            else {  //one element in message
                ui["lengthToggle"].hidden = true;
                ui["lengthMax"].hidden = true;
                ui["length"].hidden = false;
                ui["length"].readOnly = true;
                inst.length = 1;
            }
        },
        options: [
            { name: "uint8_t", displayName: "8-bit Character"},
            { name: "uint16_t", displayName: "16-bit Unsigned Int"},
            { name: "int16_t", displayName: "16-bit Signed Int"},
            { name: "bool", displayName: "16-bit Boolean"},
            { name: "uint32_t", displayName: "32-bit Unsigned Int"},
            { name: "int32_t", displayName: "32-bit Signed Int"},
            { name: "float", displayName: "32-bit Floating Point"},
            { name: "uint8_t_array", displayName: "8-bit Character Array"},
            { name: "uint16_t_array", displayName: "16-bit Unsigned Int Array"},
            { name: "int16_t_array", displayName: "16-bit Signed Int Array"},
            { name: "bool_array", displayName: "16-bit Boolean Array"},
            { name: "uint32_t_array", displayName: "32-bit Unsigned Int Array"},
            { name: "int32_t_array", displayName: "32-bit Signed Int Array"},
            { name: "float_array", displayName: "32-bit Floating Point Array"},
        ],
    },
    {
        name: "keyValueID",
        displayName: "Hash Table ID",
        readOnly: false,
        default: 0,
        hidden: false,
        // getValue: (inst) => {
        //     //Common.printDebugObject(inst)
        //     //console.log(inst.$ownedBy)\          
        //     return system.modules[transferCommon.getTransferPath() + "logger/keys.js"].$instances.filter(i => (i.group == inst.group)).findIndex(i => (i == inst))
        // }
    },
    {
        name: "size",
        displayName: "Payload Length (in Bytes)",
        default: 1,
        hidden: true,
        getValue: (inst) => {
            if(inst.lengthToggle == "Predefine Message Length"){
                let bytesPerValue = sizeOfType[inst["valType"]];
                return bytesPerValue*inst.length;
            }
            else{
                return -1; //length is variable -> undefined
            }
        }
    }
];

function moduleInstances(inst)
{
    var ownedInstances = []

    return ownedInstances
}

function modules(inst)
{
    var staticOwnedInstances = []
    
    return staticOwnedInstances
}

function onValidate(inst, validation){
    if(inst.lengthToggle == "Predefine Message Length" && !inst.lengthValid){
        validation.logError(
            "Invalid Predefined Length - Exceeds Max Frame Length defined",
            inst, "length");
    }
}

var logVariableModule = {
    displayName: "Key Value Pair",
    defaultInstanceName: "myKeyValuePair",
    description: "Log Variable",
    config          : config,
    moduleInstances : moduleInstances,	
    modules: modules,
    templates: {
	},
    validate: onValidate
};




exports = logVariableModule;
