let transferCommon;
if (system.getProducts()[0].name.includes("C2000"))
{ transferCommon = system.getScript("/utilities/transfer/transferCommon.js");
} else
{ transferCommon = system.getScript("/transfer/transferCommon.js");}

let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let options = [];


/* Intro splash on GUI */
let longDescription = "The Transfer Bridge module provides a software layer to receive and (optionally) buffer messages with one communication peripheral and directly transmit the payload via another communication peripheral. " +
"Messages are received using Communication Link B, (optionally buffered), and transmitted by Communication Link A.";

let config = [
    {
        name: "mode",
        displayName: "Mode of Operation",
        options: [
            { name: "bridgeBidirectional", displayName: "Bridge Mode - Bidirectional"},
            { name: "bridge", displayName: "Bridge Mode"},
        ],
        default: "bridge",
        onChange: (inst, ui) => {
            ui["packetLength"].hidden = !(inst["mode"].includes("Bidirectional"))
        }
    },
    {
        name: "packetLength",
        displayName: "Data Packet Length",
        default: 16,
        readOnly: true,
        hidden: true
    },
    {
        name: "GROUP_COMS_LINK_A",
        config: [
            {
                name: "comsLinkA",
                displayName: "Communication Link A",
                options: [
                    { name: "sci", displayName: "SCI" },
                    { name: "usb", displayName: "USB" },
                    { name: "fsi", displayName: "FSI" },
                    { name: "spi", displayName: "SPI"}
                ],
                getDisabledOptions: (inst) => {
                    return [
                        { name: "fsi", reason: "Not yet implemented" },
                    ]
                },
                default: "sci"
            },
        ]
    },
    {
        name: "GROUP_COMS_LINK_B",
        config: [
            {
                name: "comsLinkB",
                displayName: "Communication Link B",
                hidden: false,
                options: [
                    { name: "sci", displayName: "SCI" },
                    { name: "spi", displayName: "SPI"},
                    { name: "fsi", displayName: "FSI" },
                    { name: "can", displayName: "CAN" },
                ],
                getDisabledOptions: (inst) => {
                    let disOpts = [
                        { name: "can", reason: "Not yet implemented" },
                    ]
                    if (!transferCommon.hasFSISupport())
                    {
                        disOpts.push({ name: "fsi", reason: "Not yet implemented"});
                    }
                    return disOpts;
                },
                default: transferCommon.hasFSISupport()?"fsi":"sci"
            },
            {
                name: "comsLinkBBuffer",
                displayName: "Buffer Received Data",
                default: false,
            },
            {
                name: "comsLinkBErrorHandler",
                displayName: "Add Error Handler",
                default: false,
            },
        ]
    }
    
];

function moduleInstances(inst)
{
    let ownedInstances = []
    if (inst.comsLinkA == "sci")
    {
        let sciModInst = {
            name: "comsLinkAModule",      
            displayName: "SCI Communication Link A",
            moduleName: "/driverlib/sci.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_SCI_LINKA",
            },
            requiredArgs: {
                wordLenght: '8',
                stop: 'ONE',
                parity: 'SCI_CONFIG_PAR_NONE',
                useFifo: true,
                loopback: false,
                useCase: "ALL"
            },
            group: "GROUP_COMS_LINK_A"
        }

        if (inst.mode.includes("Bidirectional"))
        {
            sciModInst.requiredArgs = {
                ...sciModInst.requiredArgs, 
                ...{
                    useInterrupts: true,
                    registerInterrupts: true,
                    rxFifo: "SCI_FIFO_RX" + inst.packetLength,
                    txFifo: "SCI_FIFO_TX0",
                    selectRegisteredInterrupts : ["registerRxInt", "registerTxInt"],
                    enabledFIFOInterrupts: ["SCI_INT_RXFF"],
                    sciRXInt : {
                        enableInterrupt: true
                    },
                    sciTXInt : {
                        enableInterrupt: false
                    }
                }
            }
        }
        else
        {
            sciModInst.requiredArgs = {
                ...sciModInst.requiredArgs, 
                ...{
                    useInterrupts: false,
                    registerInterrupts: false,
                }
            }
        }

        ownedInstances = ownedInstances.concat([sciModInst]);
    }
    if (inst.comsLinkA == "spi")
    {
        let spiModInst = {
            name: "comsLinkAModule",      
            displayName: "SPI Communication Link A",
            moduleName: "/driverlib/spi.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_SPI_LINKA",
            },
            requiredArgs: {
                dataWidth: '8',
                useFifo: true,
            },
            group: "GROUP_COMS_LINK_A"
        }

        spiModInst.requiredArgs = {
            ...spiModInst.requiredArgs, 
            ...{
                useInterrupts: false,
                registerInterrupts: false,
            }
        }

        ownedInstances = ownedInstances.concat([spiModInst]);
    }
    if (inst.comsLinkA == "usb")
    {
        let usbModInst = {
            name: "comsLinkAModule",      
            displayName: "USB Communication Link A",
            moduleName: "/driverlib/usb.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_USB_LINKA",
                usbLib: {
                    $name: inst.$name + "_USB_LINKA_LIB"
                }
            },
            requiredArgs: {
                useCase: "ALL",
                registerInterrupts: true,
                usbLib: {
                    usb_mode: "Device",
                    deviceClasses: "CDC"
                },
                USBInt: {
                    enableInterrupt: true
                }
            },
            group: "GROUP_COMS_LINK_A"
        }

        ownedInstances = ownedInstances.concat([usbModInst]);
    }
    
    if (inst.comsLinkB == "fsi")
    {
        let fsiLinkBModInst = {}
        if(transferCommon.getDeviceName() != "F28004x"){
            fsiLinkBModInst = {
                name: "comsLinkBModule",      
                displayName: "FSI RX Communication Link B",
                moduleName: "/driverlib/fsirx.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_FSIRX_LINKB",
                },
                requiredArgs: {
                    softwareFrameSize: inst.packetLength.toString(),
                    enableLoopback: false,
                    enableTagMatching: false,
                    enableInterrupt: true,
                    useInterrupts: ["FSI_INT1"],
                    enabledINT1Interrupts: ["FSI_RX_EVT_FRAME_DONE"],
                    registerInterruptLine1: true,
                    pingTimeout: false,
                    fsiRxInt1 : {
                        enableInterrupt: true
                    }
                },
                group: "GROUP_COMS_LINK_B"
            }
        }
        else{
            fsiLinkBModInst = {
                name: "comsLinkBModule",      
                displayName: "FSI RX Communication Link B",
                moduleName: "/driverlib/fsirx.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_FSIRX_LINKB",
                },
                requiredArgs: {
                    softwareFrameSize: inst.packetLength.toString(),
                    enableLoopback: false,
                    enableInterrupt: true,
                    useInterrupts: ["FSI_INT1"],
                    enabledINT1Interrupts: ["FSI_RX_EVT_FRAME_DONE"],
                    registerInterruptLine1: true,
                    pingTimeout: false,
                    fsiRxInt1 : {
                        enableInterrupt: true
                    }
                },
                group: "GROUP_COMS_LINK_B"
            }
        }
        

        if (inst.comsLinkBErrorHandler)
        {
            fsiLinkBModInst.requiredArgs.useInterrupts = ["FSI_INT1", "FSI_INT2"];
            fsiLinkBModInst.requiredArgs = {
                ...fsiLinkBModInst.requiredArgs, 
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
        
        ownedInstances = ownedInstances.concat([fsiLinkBModInst]);

        if (inst.mode.includes("Bidirectional"))
        {
            ownedInstances = ownedInstances.concat([{
                name: "comsLinkBModuleAlt",      
                displayName: "FSI TX Communication Link B",
                moduleName: "/driverlib/fsitx.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_FSITX_LINKB",
                    clkPres: 8
                },
                requiredArgs: {
                    startOfTransmissionMode: "FSI_TX_START_FRAME_CTRL",
                    frameType: "FSI_FRAME_TYPE_NWORD_DATA",
                    softwareFrameSize: inst.packetLength.toString(),
                    enableInterrupt: false,  
                    userCRC: false,
                    eccComputeWidth: "FSI_32BIT_ECC_COMPUTE",                
                    pingTimeout: false,
                    enableInterrupt        : true,
                    useInterrupts          : ["FSI_INT1"],
                    enabledINT1Interrupts  : ["FSI_TX_EVT_FRAME_DONE"],
                    registerInterruptLine1 : true,
                    fsiTxInt1: {
                        enableInterrupt : true
                    }
                },
                group: "GROUP_COMS_LINK_B"
            }]);
        }
    }
    if (inst.comsLinkB == "can")
    {
        ownedInstances = ownedInstances.concat([{
            name: "comsLinkBModule",      
            displayName: "CAN Communication Link B",
            moduleName: "/driverlib/can.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_CAN_LINKB",
            },
            group: "GROUP_COMS_LINK_B"
        }]);
    }
    if (inst.comsLinkB == "sci")
    {
        let sciBridgeModInst = {
            name: "comsLinkBModule",      
            displayName: "SCI Communication Link B",
            moduleName: "/driverlib/sci.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_SCI_LINKB",
            },
            requiredArgs: {
                wordLenght: '8',
                stop: 'ONE',
                parity: 'SCI_CONFIG_PAR_NONE',
                useFifo: true,
                loopback: false,
                useCase: "ALL"
            },
            group: "GROUP_COMS_LINK_B"
        }

        sciBridgeModInst.requiredArgs = {
            ...sciBridgeModInst.requiredArgs, 
            ...{
                useInterrupts: true,
                registerInterrupts: true,
                selectRegisteredInterrupts: ["registerRxInt", "registerTxInt"],
                rxFifo: "SCI_FIFO_RX" + inst.packetLength,
                txFifo: "SCI_FIFO_TX0",
                enabledFIFOInterrupts: ["SCI_INT_RXFF"],
                sciRXInt : {
                    enableInterrupt: true
                },
                sciTXInt : {
                    enableInterrupt: false
                }
            }
        }  

        ownedInstances = ownedInstances.concat([sciBridgeModInst]);
    }

    if (inst.comsLinkB == "spi")
    {
        let spiBridgeModInst = {
            name: "comsLinkBModule",      
            displayName: "SPI Communication Link B",
            moduleName: "/driverlib/spi.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_SPI_LINKB",
                bitRate: 1000000
            },
            requiredArgs: {
                dataWidth: '8',
                useFifo: true,
                loopback: false,
            },
            group: "GROUP_COMS_LINK_B"
        }

        spiBridgeModInst.requiredArgs = {
            ...spiBridgeModInst.requiredArgs, 
            ...{
                useInterrupts: true,
                registerInterrupts: true,
                rxFifo: "SPI_FIFO_RX" + (inst.packetLength / 2),
                txFifo: "SPI_FIFO_TX0",
                enabledFIFOInterrupts: ["SPI_INT_RXFF"],
                spiRXInt : {
                    enableInterrupt: true
                },
                spiTXInt : {
                    enableInterrupt: false
                }
            }
        }
            
        ownedInstances = ownedInstances.concat([spiBridgeModInst]);

    }

    if (inst.comsLinkBBuffer)
    {
        ownedInstances = ownedInstances.concat([{
            name: "comsLinkBBufferModule",      
            displayName: "Communication Link B Buffer",
            moduleName: transferCommon.getTransferPath() + "transferringbuff.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_ringBuff",
            },
            requiredArgs: {
                elemPerBuffEntry: inst.packetLength
            },
            group: "GROUP_COMS_LINK_B"
        }]);
    }
    return ownedInstances
}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["BRIDGE"]));
}

function modules(inst)
{
    var staticOwnedInstances = []

    return staticOwnedInstances
}

var bridgeModule = {
    displayName: "Transfer Bridge (BETA)",
    maxInstances: 1,
    defaultInstanceName: "myBridge",
    description: "Transfer Bridge Module",
    filterHardware : filterHardware,
    config          : config,
    moduleInstances : moduleInstances,	
    modules: modules,
    longDescription: longDescription,
    templates: {
		[transferCommon.getTransferPath() + "transferbridge/bridge.c.xdt"] : "",
		[transferCommon.getTransferPath() + "transferbridge/bridge.h.xdt"] : "",
        [transferCommon.getTransferPath() + "transfer.opt.xdt"] : ""
	}
};




exports = bridgeModule;