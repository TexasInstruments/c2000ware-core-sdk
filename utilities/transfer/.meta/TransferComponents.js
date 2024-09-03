let transferCommon;
if (system.getProducts()[0].name.includes("C2000"))
{
    transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
}
else
{
    transferCommon = system.getScript("/transfer/transferCommon.js");
}


let references = system.getScript(transferCommon.getTransferPath() + "TransferReferences.js");
var views = []

let templatesExport = [
    //
    // Export
    //
    {
        name: transferCommon.getTransferPath() + "export/export.c.xdt",
        outputPath: "export/export.c",
    },
    {
        name: transferCommon.getTransferPath() + "export/export.h.xdt",
        outputPath: "export/export.h",
    },
    {
        name: transferCommon.getTransferPath() + "export/export_package.c.xdt",
        outputPath: "export/export_package.c",
    },
    {
        name: transferCommon.getTransferPath() + "export/export_package.h.xdt",
        outputPath: "export/export_package.h",
    },
]

let templatesExportMods = [
    {
        name: transferCommon.getTransferPath() + "export/export_mods.c.xdt",
        outputPath: "export/export_mods.c",
    },
    {
        name: transferCommon.getTransferPath() + "export/export_mods.h.xdt",
        outputPath: "export/export_mods.h",
    },
]

let templatesExportLogs = [
    {
        name: transferCommon.getTransferPath() + "export/export_buffer.c.xdt",
        outputPath: "export/export_buffer.c",
    },
    {
        name: transferCommon.getTransferPath() + "export/export_buffer.h.xdt",
        outputPath: "export/export_buffer.h",
    },
    {
        name: transferCommon.getTransferPath() + "export/export_log.c.xdt",
        outputPath: "export/export_log.c",
    },
    {
        name: transferCommon.getTransferPath() + "export/export_log.h.xdt",
        outputPath: "export/export_log.h",
    },
]

let templatesGui = [
    //
    // GUI
    //
    {
        name: transferCommon.getTransferPath() + "gui/assets/icons.svg.xdt",
        outputPath: "gui/assets/icons.svg",
    },
    {
        name: transferCommon.getTransferPath() + "gui/index.gui.xdt",
        outputPath: "gui/index.gui",
    },
    {
        name: transferCommon.getTransferPath() + "gui/index.html.xdt",
        outputPath: "gui/index.html",
    },
    {
        name: transferCommon.getTransferPath() + "gui/index.js.xdt",
        outputPath: "gui/index.js",
    },
    {
        name: transferCommon.getTransferPath() + "gui/codec.js.xdt",
        outputPath: "gui/codec.js",
    },
    {
        name: transferCommon.getTransferPath() + "gui/hash_table.json.xdt",
        outputPath: "gui/hash_table.json",
    },
    {
        name: transferCommon.getTransferPath() + "gui/index.json.xdt",
        outputPath: "gui/index.json",
    },
    {
        name: transferCommon.getTransferPath() + "gui/project.json.xdt",
        outputPath: "gui/project.json",
    },
    {
        name: transferCommon.getTransferPath() + "gui/package.json.xdt",
        outputPath: "gui/package.json",
    },
    {
        name: transferCommon.getTransferPath() + "gui_setup.bat.xdt",
        outputPath: "gui_setup.bat",
    },
]

let templatesTransferBridge = [
    //
    // Transfer Bridge
    //
    {
        name: transferCommon.getTransferPath() + "transferbridge/bridge.c.xdt",
        outputPath: "bridge/bridge.c",
    },
    {
        name: transferCommon.getTransferPath() + "transferbridge/bridge.h.xdt",
        outputPath: "bridge/bridge.h",
    },
]

let templatesComsLogger = [
    //
    // COMS Logger
    // 
    {
        name: transferCommon.getTransferPath() + "logger/coms_logger.c.xdt",
        outputPath: "logger/coms_logger.c",
    },
    {
        name: transferCommon.getTransferPath() + "logger/coms_logger.h.xdt",
        outputPath: "logger/coms_logger.h",
    },
]

let templatesRTLog = [
    //
    // Real-Time Log
    //
    {
        name: transferCommon.getTransferPath() + "logger/realtime_log.json.xdt",
        outputPath: "logger/realtime_log.json",
    },
    {
        name: transferCommon.getTransferPath() + "logger/realtime_log.c.xdt",
        outputPath: "logger/realtime_log.c",
    },
    {
        name: transferCommon.getTransferPath() + "logger/realtime_log.h.xdt",
        outputPath: "logger/realtime_log.h",
    },
]

let templatesDLTLog = [
    //
    // DLT Support
    //
    {
        name: transferCommon.getTransferPath() + "dlt/generate_assoc_table_v1.01.00.js.xdt",
        outputPath: "dlt/generate_assoc_table_v1.01.00.js",
    },
    {
        name: transferCommon.getTransferPath() + "dlt/export_dltpackage.c.xdt",
        outputPath: "dlt/export_dltpackage.c",
    },
    {
        name: transferCommon.getTransferPath() + "dlt/export_dltpackage.h.xdt",
        outputPath: "dlt/export_dltpackage.h",
    },
]

let templates = [
    //
    // Transfer OPTs
    //      
    {
        name: transferCommon.getTransferPath() + "transfer.opt.xdt",
        outputPath: "transfer.opt"
    },
    //
    // Transfer Utils
    //      
    {
        name: transferCommon.getTransferPath() + "transfer_utils.h.xdt",
        outputPath: "transfer_utils.h"
    },   
    {
        name: transferCommon.getTransferPath() + "transfer_utils.c.xdt",
        outputPath: "transfer_utils.c"
    },
]

templates = templates.concat(templatesExport);
templates = templates.concat(templatesGui);
templates = templates.concat(templatesComsLogger);

if (transferCommon.isC2000())
{
    templates = templates.concat(templatesExportMods);
    templates = templates.concat(templatesExportLogs);
    templates = templates.concat(templatesTransferBridge);
    templates = templates.concat(templatesRTLog);
	if(transferCommon.isC29x())
	{
		templates = templates.concat(templatesDLTLog);
	}
}

let modules = [
    transferCommon.getTransferPath() + "exporter.js",
    transferCommon.getTransferPath() + "gui.js",
    transferCommon.getTransferPath() + "comslogger.js",       
]

if (transferCommon.isC2000())
{
    modules.push(transferCommon.getTransferPath() + "transferbridge.js");
    //
    // Need some more time to debug realtimelog.js
    //
    // modules.push(transferCommon.getTransferPath() + "realtimelog.js");
	if(transferCommon.isC29x())
	{
		modules.push(transferCommon.getTransferPath() + "dltlog.js");
	}
}

var transfer_export = {
    displayName: "Transfer",
    templates: templates,
    views: views,
    references: references.componentReferences,
    topModules:
    [
        {
            displayName: "MCU Mission Control and Transfer (BETA)",
            description: "Tranfer data in and out of the device with ease",
            modules: modules
        }
    ]
}

exports = transfer_export
