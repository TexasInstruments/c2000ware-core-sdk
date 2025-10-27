let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_spi.js");

var pteOption = device_driverlib_peripheral.SPI_PTEPolarity;
if(!pteOption)
{
    pteOption = device_driverlib_peripheral.SPI_STEPolarity;
}

/* Intro splash on GUI */
let longDescription = "The Serial Peripheral Interface (SPI) "
    + "driver is a generic, full-duplex driver that transmits "
    + "and receives data on a SPI bus. SPI is sometimes called SSI "
    + "(Synchronous Serial Interface). The SPI protocol defines "
    + "the format of a data transfer over the SPI bus, but it "
    + "leaves flow control, data formatting, and handshaking "
    + "mechanisms to higher-level software layers."


function onChangeUseFIFO(inst, ui)
{
    onChangeUseInterrupts(inst, ui);
}


function onValidate(inst, validation) 
{   
    var bitRateError = false;
    var bitRateInt;

    try{
        bitRateInt = parseInt(inst.bitRate);
        let clockTree = Common.getClockTree();
        let lspClk = (Common.SYSCLK_getMaxMHz()*1000000)/4;
        if(clockTree){
            lspClk = parseInt(parseFloat(clockTree["LSPCLK"].in)*1000000);
        }
        if (bitRateInt < lspClk/128 || bitRateInt > lspClk/4)
        {
            bitRateError = true;
        }
    }
    catch (ex){
        bitRateError = true;
    }
    if(bitRateError)
    {
        validation.logError(
            "Enter an integer for bit rates between LSPCLK/128 and LSPCLK/4!", 
            inst, "bitRate");
    }

    if(bitRateInt >= 12500000 && !inst.useHSMode && !bitRateError){
        validation.logInfo(
            "Use High Speed mode for maximum performance", 
            inst, "bitRate");
    }

    if(bitRateInt < 12500000 && inst.useHSMode && !bitRateError){
        validation.logInfo(
            "Consider disabling High Speed mode", 
            inst, "bitRate");
    }

    if(inst.useHSMode){
        validation.logInfo(
            "Pinmux options are limited to GPIO supporting high speed mode", 
            inst, "useHSMode");
    }

    if (inst.useDMARX && inst.spiRXDMA.databusWidthConfig == "DMA_CFG_SIZE_32BIT") {
        validation.logError("32 bit databus width is not valid while linked to SPI!", inst.spiRXDMA, "databusWidthConfig");   
    }

    if (inst.useDMATX && inst.spiTXDMA.databusWidthConfig == "DMA_CFG_SIZE_32BIT") {
        validation.logError("32 bit databus width is not valid while linked to SPI!", inst.spiTXDMA, "databusWidthConfig");   
    }

    if ((inst.useDMATX || inst.useDMARX) && !inst.useFifo) {
        validation.logError("FIFO must be enabled for DMA linking!", inst, "useFifo");   
    }

    var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("SPI", inst)
    for (var pinmuxQualMod of pinmuxQualMods)
    {
        if (inst[pinmuxQualMod.name].padConfig.includes("OD"))
        {
            validation.logError("The open-drain pad configuration should not be used for the SPI module.", inst);
        }
    }
}


function onChangeUseInterrupts(inst, ui)
{
    if (inst.useInterrupts)
    {
        ui.registerInterrupts.hidden = false;
        if (inst.useFifo)
        {
            ui.enabledFIFOInterrupts.hidden = false;
            ui.enabledInterrupts.hidden = true;

            ui.txFifo.hidden = false;
            ui.rxFifo.hidden = false;
        }
        else
        {
            ui.enabledFIFOInterrupts.hidden = true;
            ui.enabledInterrupts.hidden = false;

            ui.txFifo.hidden = true;
            ui.rxFifo.hidden = true;
        }
        
    }
    else
    {
        ui.registerInterrupts.hidden = true;

        ui.enabledFIFOInterrupts.hidden = true;
        ui.enabledInterrupts.hidden = true;
        
        ui.txFifo.hidden = true;
        ui.rxFifo.hidden = true;
    }

}

/* Array of SPI configurables that are common across device families */
let config = [
    
    {
        name        : "transferProtocol",
        displayName : "Transfer Protocol",
        description : 'Mode for transfer protocol',
        hidden      : false,
        default     : device_driverlib_peripheral.SPI_TransferProtocol[0].name,
        options     : device_driverlib_peripheral.SPI_TransferProtocol
    },

    {
        name        : "mode",
        displayName : "Mode",
        description : 'Mode for device',
        hidden      : false,
        default     : device_driverlib_peripheral.SPI_Mode[0].name,
        options     : device_driverlib_peripheral.SPI_Mode
    },

    {
        name        : "ptePolarity",
        legacyNames : ["stePolarity"],
        displayName : "PTE Polarity",
        description : 'Polarity of the PTE Pin',
        hidden      : false,
        default     : pteOption[0].name,
        options     : pteOption
    },

    {
        name        : "emulationMode",
        displayName : "Emulation Mode",
        description : 'Emulation Mode',
        hidden      : false,
        default     : device_driverlib_peripheral.SPI_EmulationMode[0].name,
        options     : device_driverlib_peripheral.SPI_EmulationMode
    },

    {
        name        : "bitRate",
        displayName : "Bit Rate (Hz)",
        description : 'Bit rate for device in (Hz). Cannot exceed LSPCLK/4',
        hidden      : false,
        default     : 1000000
    },

    {
        name        : "useHSMode",
        displayName : "Enable High Speed Mode",
        description : 'Whether or not to use SPI in High Speed mode.',
        hidden      : false,
        default     : false
        
    },

    {
        name        : "dataWidth",
        displayName : "Data Width",
        description : 'Data width used for transmission',
        hidden      : false,
        default     : '16',
        options     : [
            {name: "1"},
            {name: "2"},
            {name: "3"},
            {name: "4"},
            {name: "5"},
            {name: "6"},
            {name: "7"},
            {name: "8"},
            {name: "9"},
            {name: "10"},
            {name: "11"},
            {name: "12"},
            {name: "13"},
            {name: "14"},
            {name: "15"},
            {name: "16"}
        ]
    },
    
    {
        name        : "useFifo",
        displayName : "Use FIFO",
        description : 'Whether or not to use FIFO mode.',
        hidden      : false,
        onChange    : onChangeUseFIFO,
        default     : true
        
    },

    {
        name        : "useInterrupts",
        displayName : "Use Interrupt",
        description : 'Whether or not to use Interrupt mode.',
        hidden      : false,
        onChange    : onChangeUseInterrupts,
        default     : true
        
    },
    {
        name        : "registerInterrupts",
        displayName : "Register Interrupt Handler",
        description : 'Whether or not to register interrupt handlers in the interrupt module.',
        hidden      : false,
        default     : false
        
    },

    {
        name        : "enabledInterrupts",
        displayName : "Enabled Interrupts",
        description : 'Which interrupts to enabled.',
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : [
            {name: "SPI_INT_RX_DATA_TX_EMPTY", displayName: "Receive Interrupt"},
            {name: "SPI_INT_RX_OVERRUN", displayName: "Receive Overrun Interrupt"},
        ],
        
    },

    {
        name        : "enabledFIFOInterrupts",
        displayName : "Enabled FIFO Interrupts",
        description : 'Which FIFO interrupts to enabled.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : [
            {name: "SPI_INT_RXFF", displayName: "Receive Interrupt"},
            {name: "SPI_INT_RXFF_OVERFLOW", displayName: "Receive Overflow Interrupt"},
            {name: "SPI_INT_TXFF", displayName: "Transmit Interrupt"},
        ],
        
    },

    {
        name        : "txFifo",
        displayName : "Transmit FIFO Interrupt Level",
        description : 'Transmit FIFO interrupt level used.',
        hidden      : false,
        default     : device_driverlib_peripheral.SPI_TxFIFOLevel[0].name,
        options     : device_driverlib_peripheral.SPI_TxFIFOLevel
    },

    {
        name        : "rxFifo",
        displayName : "Receive FIFO Interrupt Level",
        description : 'Receive FIFO interrupt level used.',
        hidden      : false,
        default     : device_driverlib_peripheral.SPI_RxFIFOLevel[0].name,
        options     : device_driverlib_peripheral.SPI_RxFIFOLevel
    },

    {
        name        : "loopback",
        displayName : "Use Loopback Mode",
        description : 'Whether or not to use loopback mode.',
        hidden      : false,
        default     : false
        
    },
    
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("SPI"),
        onChange    : Pinmux.useCaseChanged,
    },
];

if (["F28002x", "F28003x", "F28004x", "F2807x", "F2837xS", "F2837xD", "F2838x", "F28P65x","F28P55x","F28P551x","F28E12x"].includes(Common.getDeviceName())){
    config = config.concat([
        {
            name        : "useDMARX",
            displayName : "Use DMA for Receive",
            description : 'Whether or not to use DMA mode for RX.',
            hidden      : false,
            default     : false
        },
    
        {
            name        : "useDMATX",
            displayName : "Use DMA for Transmit",
            description : 'Whether or not to use DMA mode for TX.',
            hidden      : false,
            default     : false
        },
    ])
}

/*
 *  ======== filterHardware ========
 *  Control RX, TX Pin usage by the user specified dataDirection.
 *
 *  param component - hardware object describing signals and
 *                     resources they're attached to
 *
 *  returns Boolean indicating whether or not to allow the component to
 *           be assigned to an instance's $hardware config
 */
function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["SPI"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var spiModule = {
    peripheralName: "SPI",
    displayName: "SPI",
    maxInstances: Common.peripheralCount("SPI"),
    defaultInstanceName: "mySPI",
    description: "Serial Peripheral Interface Peripheral",
    filterHardware : filterHardware,
    config: config,
    moduleInstances: (inst) => {
        var submodules = []

        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("SPI", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.args = {
                qualMode : "GPIO_QUAL_ASYNC",
            }
            pinmuxQualMod.args.padConfig = "STD";
        }
        submodules = submodules.concat(pinmuxQualMods)
        
        if (inst.useInterrupts && inst.registerInterrupts)
        {
            submodules = submodules.concat([{
                name: "spiRXInt",      
                displayName: "RX Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_RX_INT",
                    int : "INT_" + inst.$name + "_RX",
                    pinmuxPeripheralModule : "spi",
                    driverlibInt: "INT_#_RX"
                }
            },
            {
                name: "spiTXInt",      
                displayName: "TX Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_TX_INT",
                    int : "INT_" + inst.$name + "_TX",
                    pinmuxPeripheralModule : "spi",
                    driverlibInt: "INT_#_TX"
                }
            }])
        }

        if (inst.useDMARX)
        {
            submodules = submodules.concat([
                {
                    name: "spiRXDMA",      
                    displayName: "RX DMA",
                    moduleName: "/driverlib/dma.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_RX_DMA",
                    },
                    requiredArgs: {
                        srcAddressLinked: inst.$name + "_RX_DMA_ADDRESS",
                        peripheralRXLinked: true,
                        databusWidthConfig: "DMA_CFG_SIZE_16BIT",
                        triggerSource: "DMA_TRIGGER_LINKED"
                    }
                },
            ])
        }

        if (inst.useDMATX) {
            submodules = submodules.concat([
                {
                    name: "spiTXDMA",
                    displayName: "TX DMA",
                    moduleName: "/driverlib/dma.js",
                    collapsed: true,
                    args: {
                        $name: inst.$name + "_TX_DMA",
                    },
                    requiredArgs: {
                        destAddressLinked: inst.$name + "_TX_DMA_ADDRESS",
                        peripheralTXLinked: true,
                        databusWidthConfig: "DMA_CFG_SIZE_16BIT",
                        triggerSource: "DMA_TRIGGER_LINKED"
                    }
                },
            ])
        }
        return submodules;
    },
    templates: {
        boardc : "/driverlib/spi/spi.board.c.xdt",
        boardh : "/driverlib/spi/spi.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.spiPinmuxRequirements,
    validate    : onValidate
};


if (spiModule.maxInstances <= 0)
{
    delete spiModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(spiModule)
    Pinmux.addPinMuxQualGroupToConfig(spiModule)
}


exports = spiModule;