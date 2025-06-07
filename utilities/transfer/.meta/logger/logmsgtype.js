let transferCommon;
if (system.getProducts()[0].name.includes("C2000"))
{ transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else
{ transferCommon = system.getScript("/transfer/transferCommon.js");}


let config = [
    {
        name: "$name",
        hidden: false
    },
    {
        name: "id",
        displayName: "ID",
        default: 0
    },
    {
        name: "size",
        default: 0,
        getValue: (inst) => {
            let size = 0;
            for (let logVar of inst["logVariables"]) {
                size += logVar.size;
            }
            return size;
        }
    }
];

function moduleInstances(inst)
{
    var ownedInstances = []

    ownedInstances.push({
        name: "logVariables",
        displayName: "Log Variables",
        moduleName: transferCommon.getTransferPath() + "logger/logvariable.js",
        useArray: true,
        defaultInstanceCount: 1,
        collapsed: true,
    })

    return ownedInstances
}

function modules(inst)
{
    var staticOwnedInstances = []
    
    return staticOwnedInstances
}

function onValidate(inst, validation){
    if (inst.size == 0)
    {
        validation.logError(
            "Empty messages are not allowed", 
            inst, "size");
    }
    for (let otherInst of inst.$module.$instances){
        if ((inst != otherInst) && (inst.id === otherInst.id))
        {
            validation.logError(
                "IDs must be unique across all message types - same as " + otherInst.$name, 
                inst, "id");
        }
    }
}

var logMsgTypeModule = {
    displayName: "Log Message Type",
    maxInstances: 256,
    defaultInstanceName: "myLogMsgType",
    description: "Log Message Type",
    config          : config,
    moduleInstances : moduleInstances,	
    modules: modules,
    templates: {
	},
    validate: onValidate
};

exports = logMsgTypeModule;
