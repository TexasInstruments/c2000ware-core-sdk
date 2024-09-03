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

let config = [

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

var dltlogModule = {
    displayName: "Data Logger and Trace (BETA)",
    maxInstances: 1,
    defaultInstanceName: "myDLTLOG",
    description: "DLT Log Module",
    config          : config,
    moduleInstances : moduleInstances,	
    modules: modules,
    templates: {
        [transferCommon.getTransferPath() + "dlt/export_dltpackage.c.xdt"] : "",
        [transferCommon.getTransferPath() + "dlt/export_dltpackage.h.xdt"] : "",
		[transferCommon.getTransferPath() + "dlt/generate_assoc_table_v1.01.00.js.xdt"] : "",

	},
    validate: onValidate
};




exports = dltlogModule;
