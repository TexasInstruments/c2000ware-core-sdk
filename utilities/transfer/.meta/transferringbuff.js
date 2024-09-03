let transferCommon;
if (system.getProducts()[0].name.includes("C2000"))
{ transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else
{ transferCommon = system.getScript("/transfer/transferCommon.js");}

let references = system.getScript(transferCommon.getTransferPath() + "TransferReferences.js");

var config = [
    {
        name: "bufferSize",
        displayName: "Buffer Size",
        default: 20    
    },
    {
        name: "elemPerBuffEntry",
        displayName: "Buffer Entry Size",
        default: 16,
    }
]   


var tringModule = {
    displayName: "Transfer Ring Buffer",
    defaultInstanceName: "myTransferRingBuff",
    description: "Transfer Ring Buffer Module",
    config          : config,
    references : [
        references.getReferencePath("TRANSFER_RING_BUFFER_C"),
    ],
    templates: {
        [transferCommon.getTransferPath() + "transfer.opt.xdt"]: ""
    }
};

exports = tringModule;