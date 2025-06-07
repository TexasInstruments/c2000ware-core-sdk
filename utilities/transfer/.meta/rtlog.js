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
    {
        name: "comsLink",
        displayName: "Communication Link",
        options: [
            { name: "fsi", displayName: "FSI" },
        ],
        default: "fsi"
    },
    {
        name: "packetLength",
        displayName: "Data Packet Length",
        default: 16,
        readOnly: true,
        hidden: true
    },
];

function moduleInstances(inst)
{
    var ownedInstances = []
    
    if (inst.comsLink == "fsi" && transferCommon.isC2000())
    {
        ownedInstances = ownedInstances.concat([{
            name: "comsLinkModule",      
            displayName: "FSI TX Communication",
            moduleName: "/driverlib/fsitx.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_FSITX",
                clkPres: 8
            },
            requiredArgs: {
                startOfTransmissionMode: "FSI_TX_START_FRAME_CTRL",
                frameType: "FSI_FRAME_TYPE_NWORD_DATA",
                softwareFrameSize: inst.packetLength.toString(),
                // enableInterrupt: false,  
                // userCRC: false,
                // eccComputeWidth: "FSI_32BIT_ECC_COMPUTE",                
                // pingTimeout: false,
                // enableInterrupt        : true,
                // useInterrupts          : ["FSI_INT1"],
                // enabledINT1Interrupts  : ["FSI_TX_EVT_FRAME_DONE"],
                // registerInterruptLine1 : true,
                // fsiTxInt1: {
                //     enableInterrupt : true
                // }
            }
        }]);
    }

    ownedInstances.push({
        name: "logMsgTypes",
        displayName: "Log Message Structure Definitions",
        moduleName: transferCommon.getTransferPath() + "logger/logmsgtype.js",
        useArray: true,
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
    for (let msgType of inst["logMsgTypes"]) {
        if (inst["comsLink"] == "fsi") {
            if (msgType.size > inst.packetLength) {
                validation.logError(
                    "FSI messages cannot exceed 16 words", 
                    msgType, "size");
            }
        }
    }
}

var rtlogModule = {
    displayName: "Rapid Time Logger (BETA)",
    maxInstances: 1,
    defaultInstanceName: "myRTLOG",
    description: "Rapid Log Module",
    config          : config,
    moduleInstances : moduleInstances,	
    modules: modules,
    templates: {
		[transferCommon.getTransferPath() + "logger/rt_log.json.xdt"] : "",
		[transferCommon.getTransferPath() + "logger/rt_log.c.xdt"] : "",
		[transferCommon.getTransferPath() + "logger/rt_log.h.xdt"] : "",
	},
    validate: onValidate
};




exports = rtlogModule;