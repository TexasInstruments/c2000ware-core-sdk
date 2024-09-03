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
		name: "tag",
		displayName: "DLTAG",
		default: 0
	},
	{
		name: "tag16_8bit",
		displayName: "DLTAG Size",
		default: "TAG_8_bit",
		options : [ 
			{name: "TAG_8_bit", displayName	: "8-bit TAG"}, 
			{name: "TAG_16_bit", displayName : "16-bit TAG"}
		]
	},
    {
        name: "varREGType",
        displayName: "Variable DLREG Type",
        default: "uint32_t",
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
            if (sizeOfType[inst["varREGType"]]){
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
            if (sizeOfType[inst["varREGType"]]){
                return sizeOfType[inst["varREGType"]];
            }
            else {
                return sizeOfType[inst["varREGType"].replace("*", "")] * inst["length"];
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

var dltVariableModule = {
    displayName: "DLT Log Variable",
    defaultInstanceName: "myDLTLogVariable",
    description: "DLT Log Variable",
    config          : config,
    moduleInstances : moduleInstances,	
    modules: modules,
    templates: {
	},
    validate: onValidate
};




exports = dltVariableModule;
