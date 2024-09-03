let transferCommon;
if (system.getProducts()[0].name.includes("C2000"))
{ transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else
{ transferCommon = system.getScript("/transfer/transferCommon.js");}

let config = [
    {
        name: "packetLength",
        displayName: "Data Packet Length",
        default: 16,
        readOnly: true,
        hidden: true
    },
    {
        name: "comsLink",
        displayName: "Communication Link",
        hidden: false,
        options: [
            { name: "fsi", displayName: "FSI" },
            { name: "spi", displayName: "SPI" },
            { name: "can", displayName: "CAN" },
        ],
        getDisabledOptions: (inst) => {
            return [
                { name: "can", reason: "Not yet implemented" },
            ]
        },
        default: "fsi"
    },
    {
        name: "comsLinkBuffer",
        displayName: "Buffer Received Data",
        default: true,
        hidden: true,
    },
    {
        name: "comsLinkErrorHandler",
        displayName: "Add Error Handler",
        default: false,
    },
];

function moduleInstances(inst)
{
    let ownedInstances = []

    if (inst.comsLink == "fsi")
    {
        let fsiLinkModInst;
        if (transferCommon.isC2000()) {
            fsiLinkModInst = {
                name: "comsLinkModule",      
                displayName: "FSI RX Communication Link",
                moduleName: "/driverlib/fsirx.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_FSIRX",
                },
                requiredArgs: {
                    softwareFrameSize: inst.packetLength.toString(),
                    // enableLoopback: false,
                    enableTagMatching: false,
                    enableInterrupt: true,
                    useInterrupts: ["FSI_INT1"],
                    enabledINT1Interrupts: ["FSI_RX_EVT_FRAME_DONE"],
                    registerInterruptLine1: true,
                    pingTimeout: false,
                    fsiRxInt1 : {
                        enableInterrupt: true
                    }
                }
            }

            if (inst.comsLinkErrorHandler)
            {
                fsiLinkModInst.requiredArgs.useInterrupts = ["FSI_INT1", "FSI_INT2"];
                fsiLinkModInst.requiredArgs = {
                    ...fsiLinkModInst.requiredArgs, 
                    ...{
                        enabledINT2Interrupts: [
                            "FSI_RX_EVT_CRC_ERR",
                            "FSI_RX_EVT_TYPE_ERR", 
                            "FSI_RX_EVT_EOF_ERR",  
                            "FSI_RX_EVT_OVERRUN",  
                            "FSI_RX_EVT_UNDERRUN", 
                            "FSI_RX_EVT_ERR_FRAME",
                            "FSI_RX_EVT_FRAME_OVERRUN"
                        ],
                        registerInterruptLine2: true,
                        fsiRxInt2 : {
                            enableInterrupt: true
                        }
                    }
                }
            }
        }
        else {
            fsiLinkModInst = {
                name: "comsLinkModule",      
                displayName: "FSI RX Communication Link",
                moduleName: "/drivers/fsi_rx/fsi_rx",
                collapsed: true,
                args: {
                    $name : inst.$name + "_FSIRX",
                },
                requiredArgs: {
                    intrEnable: true
                }
            }
            
        }
        ownedInstances = ownedInstances.concat([fsiLinkModInst]);
        
    }
    if (inst.comsLink == "spi")
    {
        let spiLinkModInst;
        if (transferCommon.isC2000()) {
            spiLinkModInst = {
                name: "comsLinkModule",      
                displayName: "SPI Communication Link",
                moduleName: "/driverlib/spi.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_SPI",
                },
                requiredArgs: {
                    mode: "SPI_MODE_PERIPHERAL",
                    ptePolarity: "SPI_PTE_ACTIVE_LOW",
                    useFifo: true,
                    useInterrupts: true,
                    registerInterrupts: true,
                    enabledFIFOInterrupts: ["SPI_INT_RXFF"],
                    rxFifo: "SPI_FIFO_RX8",
                    spiRXInt : {
                        enableInterrupt: true
                    }
                }
            }
        }
        ownedInstances = ownedInstances.concat([spiLinkModInst]);
    }
    if (inst.comsLinkBuffer)
    {
        ownedInstances = ownedInstances.concat([{
            name: "comsLinkBufferModule",      
            displayName: "Communication Link Buffer",
            moduleName: transferCommon.getTransferPath() + "transferringbuff.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_ringBuff",
            },
            requiredArgs: {
                elemPerBuffEntry: inst.packetLength
            }
        }]);
    }
    return ownedInstances
}

function modules(inst)
{
    var staticOwnedInstances = []

    return staticOwnedInstances
}

var comsloggerModule = {
    displayName: "Communication Logger (BETA)",
    maxInstances: 1,
    defaultInstanceName: "myCOMSLogger",
    description: "Communication Logger",
    config          : config,
    moduleInstances : moduleInstances,	
    modules: modules,
    templates: {
		[transferCommon.getTransferPath() + "logger/coms_logger.c.xdt"] : "",
		[transferCommon.getTransferPath() + "logger/coms_logger.h.xdt"] : "",
	}
};




exports = comsloggerModule;