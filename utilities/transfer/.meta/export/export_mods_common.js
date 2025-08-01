let transferCommon;
if (system.getProducts()[0].name.includes("C2000"))
{ transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else
{ transferCommon = system.getScript("/transfer/transferCommon.js");}

function getExporterComsLinkName()
{
    let exporterMod = system.modules[transferCommon.getTransferPath() + "exporter.js"];
    let exporterComsLinkName = "";
    if (exporterMod && exporterMod.$instances.length > 0)
    {
      exporterComsLinkName = exporterMod.$instances[0].comsLinkModule.$name;
    }
    return exporterComsLinkName
}

function getNonExporterInstances(mod) {
    let exporterComsLinkName = getExporterComsLinkName();
    if (mod && mod.$instances.length > 0) {
        return mod.$instances.filter((inst) => inst.$name != exporterComsLinkName);
    }
    return [];
}

function getExportKeyValuesForMod(mod, exportsInfo){
    let exportKeyValues = []
    for (var expInfo of exportsInfo) {
        for (var inst of getNonExporterInstances(mod)) {
            if (isExportModInfoApplicableForInst(inst, expInfo))
            {
                exportKeyValues.push(
                    {
                        name: inst.$name + "_" + expInfo.name,
                        updateFunc: expInfo.updateFunc? expInfo.updateFunc(inst.$name + "_BASE"): undefined,
                    }); 
            }
        }
    }
    return exportKeyValues;
}

function getInstanceExportModsInfo(inst, exportsInfo) {
    return exportsInfo.filter((expInfo) => {
        return isExportModInfoApplicableForInst(inst, expInfo);
    });
}

function getInstanceExportModsInfoWithType(inst, exportsInfo, type) {
    return exportsInfo.filter((expInfo) => {
        return (isExportModInfoApplicableForInst(inst, expInfo) && expInfo.type == type);
    });
}

function getExportModInfoBitfieldRegForInst(inst, modName, bitfiledInstanceNames, expInfo)
{
    let bitfieldInstance = "default";
    if (!expInfo.bitfieldInstance)
    {

    }
    else
    {
        bitfieldInstance = expInfo.bitfieldInstance;
    }
    let bitfiledInstanceFunc = bitfiledInstanceNames[bitfieldInstance];
    if (inst) {
        let pinmuxToolPeripheral = inst[modName].$solution.peripheralName;
        return bitfiledInstanceFunc(pinmuxToolPeripheral.toLowerCase().replace(modName, ""));
    }
    else{
        return bitfiledInstanceFunc();
    }
}

function isExportModInfoApplicableForInst(inst, expInfo)
{
    if (!expInfo.applicable)
    {
        return true;
    }
    return expInfo.applicable(inst);
}

function getExportModModuleNames(){
    let deviceName = transferCommon.getDeviceName();
    let expModuleNames;
    switch(deviceName)
    {
        case "F280013x":
            expModuleNames = ["sci", "spi", "i2c", "eqep", "can"];
            break;
        
        case "F280015x":
            expModuleNames = ["sci", "spi", "i2c", "eqep", "can", "lin"];
            break;
        
        case "F28003x":
            expModuleNames = ["sci", "spi", "i2c", "eqep", "can", "lin", "fsitx", "fsirx"];
            break;
        
        default:
            expModuleNames = ["sci", "spi", "i2c", "eqep", "can"];
            break;
    }
   
   return expModuleNames;
}

function getExportAlwaysModModuleNames(){
    let expModuleNames = ["sysctl"];
    return expModuleNames;
 }

exports = {
    getExporterComsLinkName: getExporterComsLinkName,
    getNonExporterInstances: getNonExporterInstances,
    getExportKeyValuesForMod: getExportKeyValuesForMod,
    getExportModModuleNames: getExportModModuleNames,
    getExportAlwaysModModuleNames : getExportAlwaysModModuleNames,
    getInstanceExportModsInfo: getInstanceExportModsInfo,
    isExportModInfoApplicableForInst: isExportModInfoApplicableForInst,
    getExportModInfoBitfieldRegForInst: getExportModInfoBitfieldRegForInst,
    getInstanceExportModsInfoWithType: getInstanceExportModsInfoWithType
}