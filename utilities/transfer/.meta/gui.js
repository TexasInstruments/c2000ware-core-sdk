let transferCommon;
if (system.getProducts()[0].name.includes("C2000"))
{ transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else
{ transferCommon = system.getScript("/transfer/transferCommon.js");}


const DEVICE_DIAGNOSTIC_EXPORT_NONE = "none";
const DEVICE_DIAGNOSTIC_EXPORT_XDS = "xds";
const DEVICE_DIAGNOSTIC_EXPORT_EXPORTER = "exporter";

function rtLoggeronChange(inst, ui){
    ui.rtloggerSelection.hidden = true;
    ui.rtloggerJsonFile.hidden = true;
    ui.rtloggerJsonFileRefresh.hidden = true;
    ui.rtloggerJsonData.hidden = true;
    if (inst.rtlogger)
    {
        ui.rtloggerSelection.hidden = false;
        if (inst.rtloggerSelection == "file") {
            ui.rtloggerJsonFile.hidden = false;
            ui.rtloggerJsonFileRefresh.hidden = false;
            ui.rtloggerJsonData.hidden = false;
        }        
    }
}

function dltLoggeronChange(inst, ui){

}

let config = [
    {
        name: "guiProjectName",
        displayName: "GUI Project Name",
        default: "GUI APP"
    },
    {
        name: "deviceDiagnosticExportMode",
        displayName: "Device Diagnostic Export Mode",
        default: DEVICE_DIAGNOSTIC_EXPORT_NONE,
        options: [
            { name: DEVICE_DIAGNOSTIC_EXPORT_NONE, displayName: "No device diagnostic export"},
            { name: DEVICE_DIAGNOSTIC_EXPORT_XDS, displayName: "Use XDS debugger for device diagnostic export"},
            { name: DEVICE_DIAGNOSTIC_EXPORT_EXPORTER, displayName: "Use COMS exporter for device diagnostic export"},
        ],
        hidden: transferCommon.isC2000()
    },
    {
        name: "GRPOUP_FSI_FRAME_LOGGER",
        config: [
            {
                name: "fsilogger",
                displayName: "Enable FSI Frame Logger",
                default: false,
                hidden: (transferCommon.isC29x())
            },
            {
                name: "fsiComsLogger",
                displayName: "Add FSIRX Communication Logger",
                default: false,
                hidden: (transferCommon.isC29x())
            },
        ]
    },
    {
        name: "GRPOUP_CUSTOM_LOGGER",
        config: [
            {
                name: "customlogger",
                displayName: "Enable Custom Export Logger",
                default: false,
                hidden: !transferCommon.isC2000()
            },
        ]
    },
    //
    // Un-hide when ready to launch RTLogger
    //
    {
        name: "GROUP_RT_LOGGER",
        config: [
            {
                name: "rtlogger",
                displayName: "Enable Rapid Time Logger",
                default: false,
                hidden: transferCommon.isC29x(),
                onChange: rtLoggeronChange
            },
            {
                name: "rtloggerSelection",
                displayName: "Message Decode Info",
                default: "file",
                hidden: true,
                onChange: rtLoggeronChange,
                options: (inst) => {
                    let opts = [
                        { name: "file" , displayName: "Selected JSON File"}
                    ]
                    let rtMod = system.modules[transferCommon.getTransferPath() + "rtlog.js"];
                    if (rtMod)
                    {
                        let rtInst = rtMod.$instances[0];
                        opts.push({
                            name: rtInst.$name, displayName: "RT Log " + rtInst.$name + " Message Definitions"
                        });
                    }
                    return opts
                }
            },
            {
                name: "rtloggerJsonFile",
                displayName: "Message Decode rt_log.json",
                default: "",
                hidden: true,
                checkExistence: true,
                fileFilter: ".json",
            },
            {
                name: "rtloggerJsonFileRefresh",
                displayName: "Read Message Decode File",
                buttonText: "Read & Update",
                hidden: true,
                onLaunch: (inst) => {
                    return ({
                        command: transferCommon.getTransferSourcePath() + "/.meta/readFile.bat",
                        args: [inst.rtloggerJsonFile, "$comFile"],
                        initialData: ""
                    });
                },
                onComplete: (inst, ui, result) => {
                    inst["rtloggerJsonData"] = result.data;
                }
            },
            {
               	name: "rtloggerJsonData",
                hidden: true,
                displayName: "Message Decode JSON",
                multiline: true,
                readOnly: false,
                default: "",
            },
        ]
    },

];

function moduleInstances(inst)
{
    var ownedInstances = []
    if ((inst["deviceDiagnosticExportMode"] == DEVICE_DIAGNOSTIC_EXPORT_EXPORTER) ||
        (inst["fsilogger"] || inst["customlogger"])){

        var expModule = {
            name: "exporter",      
            displayName: "Exporter",
            moduleName: transferCommon.getTransferPath() + "exporter.js",
            collapsed: true,
            args: {
                mode: "data",
                exportCustomLog: (inst["customlogger"])
            }
        };

        expModule.requiredArgs = {};
        if (inst["deviceDiagnosticExportMode"] == DEVICE_DIAGNOSTIC_EXPORT_EXPORTER) {
            expModule.requiredArgs.exportMods = true;
        }

        ownedInstances = ownedInstances.concat([expModule]);
    }
    
    if (inst["fsiComsLogger"] && inst["fsilogger"])
    {
        let comsLoggerModule = {
            name: "comsLoggerModule",      
            displayName: "FSI Communication Logger",
            moduleName: transferCommon.getTransferPath() + "comslogger.js",
            collapsed: true,
            args: {

            },
            requiredArgs: {
                comsLink : "fsi"
            },
            group: "GRPOUP_FSI_FRAME_LOGGER"
        };

        ownedInstances = ownedInstances.concat([comsLoggerModule]);
    }
    if (transferCommon.isC29x()){
        if (inst["customlogger"] && inst["dltlogger"])
        {
            let DLTModule = {
                name: "DLTModule",      
                displayName: "DLT Visualization Support",
                moduleName: transferCommon.getTransferPath() + "dltlog.js",
                collapsed: true,
                args: {
    
                },
                group: "GRPOUP_DLT_LOGGER"
            };
    
            ownedInstances = ownedInstances.concat([DLTModule]);
        }
    }
    
    return ownedInstances
}

function onValidate(inst, validation){
    if (inst["rtlogger"] && !inst["fsilogger"])
    {
        validation.logError(
            "FSI Frame Logger must be enabled to use Rapid Time Logger", 
            inst, "rtlogger");
    }
    if ((inst["customlogger"]) && !inst["exporter"]["exportCustomLog"])
    {
        validation.logError(
            "Export logs must be enabled since Custom log has been enabled in the owner GUI", 
            inst.exporter, "exportCustomLog");
    }
	if (inst["dltlogger"] && !inst["customlogger"])
	{
		validation.logError(
            "Custom Export Logger must be enabled to use DLT Logger", 
            inst, "dltlogger");	
	}
}

if(transferCommon.isC29x())
{
    config = config.concat(
    {
        name: "GROUP_DLT_LOGGER",
        config: [
            {
                name: "dltlogger",
                displayName: "Enable DLT Logger",
                default: false,
                onChange: dltLoggeronChange
            },
            {
                name:"dltcpufreq",
                displayName: "CPU Clock Freq",
                default: 200000000,
                hidden: false
            }
        ]
    }
    )
}
var guiModule = {
    displayName: "MCU Mission Control (BETA)",
    maxInstances: 1,
    defaultInstanceName: "myGUI",
    description: "GUI Visualization and Debugging",
    moduleStatic: {
        config          : config,
        moduleInstances : moduleInstances,	
        validate: onValidate
    },
    templates: {
		[transferCommon.getTransferPath() + "gui/assets/icons.svg.xdt"] : "",
		[transferCommon.getTransferPath() + "gui/index.gui.xdt"] : "",
		[transferCommon.getTransferPath() + "gui/index.html.xdt"] : "",
		[transferCommon.getTransferPath() + "gui/index.js.xdt"] : "",
		[transferCommon.getTransferPath() + "gui/index.json.xdt"] : "",
        [transferCommon.getTransferPath() + "gui/codec.js.xdt"] : "",
        [transferCommon.getTransferPath() + "gui/hash_table.json.xdt"] : "",
		[transferCommon.getTransferPath() + "gui/project.json.xdt"] : "",
		[transferCommon.getTransferPath() + "gui/package.json.xdt"] : "",
		[transferCommon.getTransferPath() + "gui_setup.bat.xdt"] : "",
        [transferCommon.getTransferPath() + "transfer.opt.xdt"]: ""
	}
};

exports = guiModule;
