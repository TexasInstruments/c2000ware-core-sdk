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
    "uint16_t" :    1,
    "int16_t" :     1,
    "uint32_t" :    2,
    "int32_t" :     2,
    "float" :       2,
}

let config = [
    {
        name: "$name",
        hidden: false,
    },
    {
        name: "varType",
        displayName: "Variable Type",
        default: "uint16_t",
        options: [
            { name: "uint16_t", displayName: "16-bit Unsigned Int"},
            { name: "int16_t", displayName: "16-bit Signed Int"},
            { name: "uint32_t", displayName: "32-bit Unsigned Int"},
            { name: "int32_t", displayName: "32-bit signed Int"},
            { name: "float", displayName: "32-bit Floating Point"},

            { name: "uint16_t*", displayName: "Array of 16-bit Unsigned Ints"},
            { name: "int16_t*", displayName: "Array of 16-bit Signed Ints"},
            { name: "uint32_t*", displayName: "Array of 32-bit Unsigned Ints"},
            { name: "int32_t*", displayName: "Array of 32-bit signed Ints"},
            { name: "float*", displayName: "Array of 32-bit Floating Points"},
        ],
        onChange: (inst, ui) => {
            if (sizeOfType[inst["varType"]]){
                ui["length"].hidden = true;
            }
            else {
                ui["length"].hidden = false;
            }
        }
    },
    {
        name: "length",
        displayName: "Length of Array",
        default: 1,
        hidden: true
    },
    {
        name: "size",
        default: 1,
        getValue: (inst) => {
            if (sizeOfType[inst["varType"]]){
                return sizeOfType[inst["varType"]];
            }
            else {
                return sizeOfType[inst["varType"].replace("*", "")] * inst["length"];
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

}

var logVariableModule = {
    displayName: "Log Variable",
    defaultInstanceName: "myLogVariable",
    description: "Log Variable",
    config          : config,
    moduleInstances : moduleInstances,	
    modules: modules,
    templates: {
	},
    validate: onValidate
};




exports = logVariableModule;
