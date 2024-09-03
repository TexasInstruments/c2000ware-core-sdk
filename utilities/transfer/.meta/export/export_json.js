let transferCommon;
if (system.getProducts()[0].name.includes("C2000"))
{ transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else
{ transferCommon = system.getScript("/transfer/transferCommon.js");}


exports = {
	moduleStatic: {},
	templates: {
		[transferCommon.getTransferPath() + "export/export_json.c.xdt"] : "",
		[transferCommon.getTransferPath() + "export/export_json.h.xdt"] : "",
	}
};