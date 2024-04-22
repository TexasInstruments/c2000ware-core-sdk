let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = "UART";
let pinmuxOnlyDevices = ["F2838x"];

function burstSizeMapping(fifoLevel, inst){
    if(inst.fen == false){
        return 1;
    }
    switch(fifoLevel) {
        case "UART_FIFO_TX7_8":
        case "UART_FIFO_RX1_8":
            return 2;
        case "UART_FIFO_TX6_8":
        case "UART_FIFO_RX2_8":
            return 4;
        case "UART_FIFO_TX4_8":
        case "UART_FIFO_RX4_8":
            return 8;
        case "UART_FIFO_TX2_8":
        case "UART_FIFO_RX6_8":
            return 12;
        case "UART_FIFO_TX1_8":
        case "UART_FIFO_RX7_8":
            return 14;
        default:
          return 1;
    }
}

function onChangeFIFOInterrupts(inst, ui)
{
    // if interrupt enabled, unhide everything, let later if-statements re-
    // hide necessary items
    if (inst.enInterrupt) 
    {
        ui.registerInterrupts.hidden = false;
        ui.enabledInterrupts.hidden = false;
        ui.txiflsel.hidden = false;
        ui.rxiflsel.hidden = false;
    }
    else
    {
        ui.registerInterrupts.hidden = true;
        ui.enabledInterrupts.hidden = true;
        ui.txiflsel.hidden = true;
        ui.rxiflsel.hidden = true;
    }
    // hide fifo-related interrupts based on fen
    if (inst.enInterrupt && inst.fen)
    {
        ui.txiflsel.hidden = false;
        ui.rxiflsel.hidden = false;
    }
    else
    {
        ui.txiflsel.hidden = true;
        ui.rxiflsel.hidden = true;
    }
}

function onChangeParity(inst, ui)
{
    // if parity is enabled, unhide everything, let later if-statements re-
    // hide necessary items
    if (inst.pen)
    {
        ui.eps.hidden = false;
        ui.sps.hidden = false;
        ui.stickParityVal.hidden = false;
    }
    else
    {
        ui.eps.hidden = true;
        ui.sps.hidden = true;
        ui.stickParityVal.hidden = true;
    }
    // hide/unhide stickParityVal as necessary, based on stick parity select
    if (inst.pen && inst.sps)
    {
        ui.stickParityVal.hidden = false;
    }
    else
    {
        ui.stickParityVal.hidden = true;
    }
}


function onValidate(inst, validation)
{
    // only do validation for devices that have more than pinmux
    if (pinmuxOnlyDevices.includes(Common.getDeviceName()))
    {
        validation.logWarning(
            "No Sysconfig support for CM core", 
            inst, "useCase");
        return;
    }

    if ((inst.enInterrupt) && (inst.enabledInterrupts.length <= 0) && (inst.txiflsel != "EOT"))
    {
        validation.logWarning(
            "At least one interrupt should be enabled when 'Enable Interrupts' is checked. Either choose one here, or Enable FIFO and choose Transmit FIFO Interrupt Level 'End of Transmission'.", 
            inst, "enabledInterrupts");
    }

    // baud rate checks
    // min  = (max 16 bit integer+((max 6 bit fractional)/64))*16 low speed mode
    //      = (2^16+((2^6)/64)*16
    //      = 1048592
    var minBaud = inst.$module.$static["baudSYSCLK"]/(1048592);
    var maxBaud = inst.$module.$static["baudSYSCLK"]/8;
    if (inst.baud > maxBaud)
    {
        validation.logError(
            "Baud rate out of range, max baud rate given current UART source clock is " + String(maxBaud),
            inst, "baud");
    }
    
    else if (inst.baud < minBaud)
    {
        validation.logError(
            "Baud rate out of range, min baud rate given current UART source clock is " + String(minBaud),
            inst, "baud");
    }

    //Validate UART+DMA settings
    //Add filters for F2838x, F28P65x, and F29H65x in the future if IP is updated
    if ((inst.dmarx || inst.dmatx) && !inst.fen) {
        validation.logError("FIFO must be enabled for DMA linking!", inst, "fen");   
    }
    if(inst.dmarx && (inst.uartRXDMA.burstSize != burstSizeMapping(inst.rxiflsel, inst)))
    {
        validation.logWarning(
            "Burst size is not equal to RX FIFO size", inst.uartRXDMA, "burstSize");
    }
    if(inst.dmatx && (inst.uartTXDMA.burstSize != burstSizeMapping(inst.txiflsel, inst)))
    {
        validation.logWarning(
            "Burst size is not equal to TX FIFO size", inst.uartTXDMA, "burstSize");
    }

    if (inst.dmarx && (inst.uartRXDMA.numberWordsToTransfer)%2 !== 0){
        validation.logWarning(
            "Total number of bytes to receive must be even", inst.uartRXDMA, "numberWordsToTransfer");            
    }
    if (inst.dmatx && (inst.uartTXDMA.numberWordsToTransfer)%2 !== 0){
        validation.logWarning(
            "Total number of bytes to transmit must be even", inst.uartTXDMA, "numberWordsToTransfer");
    }
    if ((inst.dmatx && inst.uartTXDMA.oneShotConfig == "DMA_CFG_ONESHOT_ENABLE") && (inst.uartTXDMA.numberWordsToTransfer > 16)){
        validation.logWarning(
            "Enabling one-shot mode when transferring a total number of bytes greater than the TX FIFO depth (16) will cause data loss", inst.uartTXDMA, "oneShotConfig");
    }
    if ((inst.dmarx && inst.uartRXDMA.oneShotConfig == "DMA_CFG_ONESHOT_ENABLE") && (inst.uartRXDMA.numberWordsToTransfer > 16)){
        validation.logWarning(
            "Enabling one-shot mode when transferring a total number of bytes greater than the RX FIFO depth (16) will cause data loss", inst.uartRXDMA, "oneShotConfig");
    }
}

/* Array of CAN configurables that are common across device families */
let config = [
    //**********************************************************************
    // Baud Settings
    {
        name        : "baud",
        displayName : "Baud Rate",
        description : 'The set of baud rates that are used by this instance. '
                      + 'On some devices, these rates are used to pre-compute '
                      + 'a table of clock dividers necessary for each rate.',
        hidden      : false,
        default     : 115200,
    },
    {
        name        : "baudVal",
        displayName : "Actual Baud Rate Value",
        description : 'Actual baud rate value based on requested input and programmable values.',
        hidden      : false,
        getValue    : (inst) => {
            var baudrt      = inst.baud;
            var baudrtDiv   = inst.baud;
            //
            // Half the supplied baud rate to compensate for enabling high speed
            // mode. This allows the following code to be common to both cases.
            //
            if ((baudrtDiv * 16) > inst.$module.$static["baudSYSCLK"])
            {
                baudrtDiv = baudrtDiv/2;
            }
            var div = parseInt((((inst.$module.$static["baudSYSCLK"] * 8) / baudrtDiv) + 1) / 2);
            
            // high speed mode (source clock /8) if needed for this baud
            var ClkDiv = ((baudrt * 16) > inst.$module.$static["baudSYSCLK"] ? 8 : 16)

            // get the values that would get stored into the regs
            var integerBaudRateDivider = parseInt(div / 64);
            var fractionalBaudRateDivider = parseInt(div % 64);
            
            // compute the resultant baud rate of the values that got put
            // into the registers
            var baudActual = (inst.$module.$static["baudSYSCLK"]/((integerBaudRateDivider + (fractionalBaudRateDivider/64))*ClkDiv));
            return Math.round(baudActual);
        },
        default     : 115200,
    },
    {
        name        : "baudErr",
        displayName : "Baud Rate Error Percent",
        description : 'Error percentage of actual vs set baud rate.',
        hidden      : false,
        getValue    : (inst) => {
            var baudrt      = inst.baud;
            var baudrtDiv   = inst.baud;
            //
            // Half the supplied baud rate to compensate for enabling high speed
            // mode. This allows the following code to be common to both cases.
            //
            if ((baudrtDiv * 16) > inst.$module.$static["baudSYSCLK"])
            {
                baudrtDiv = baudrtDiv/2;
            }
            var div = parseInt((((inst.$module.$static["baudSYSCLK"] * 8) / baudrtDiv) + 1) / 2);
            
            // high speed mode (source clock /8) if needed for this baud
            var ClkDiv = ((baudrt * 16) > inst.$module.$static["baudSYSCLK"] ? 8 : 16)

            // get the values that would get stored into the regs
            var integerBaudRateDivider = parseInt(div / 64);
            var fractionalBaudRateDivider = parseInt(div % 64);
            
            // compute the resultant baud rate of the values that got put
            // into the registers
            var baudActual = (inst.$module.$static["baudSYSCLK"]/((integerBaudRateDivider + (fractionalBaudRateDivider/64))*ClkDiv));
            return +(Math.abs((baudActual-baudrt)/baudrt)*100).toFixed(3);
        },
        default     : 115200,
    },
    //**********************************************************************
    // Word Settings
    {    
        name        : "GROUP_WORD_SETTINGS",
        displayName : "Word Settings",
        collapsed   : false,
        config      : [
            {
                name        : "wlen",
                displayName : "Word Length",
                description : 'The number of data bits transmitted or received in a frame.',
                hidden      : false,
                default     : 'UART_CONFIG_WLEN_8',
                options     : [
                    { name: "UART_CONFIG_WLEN_5", displayName:"5" },
                    { name: "UART_CONFIG_WLEN_6", displayName:"6" },
                    { name: "UART_CONFIG_WLEN_7", displayName:"7" },
                    { name: "UART_CONFIG_WLEN_8", displayName:"8" }
                ]
            },
            {
                name        : "stp2",
                displayName : "Stop Bits",
                description : 'Number of stop bits transmitted at end of a frame. The receive logic does not check for two stop bits being received.',
                hidden      : false,
                default     : 'UART_CONFIG_STOP_ONE',
                options     : [
                    { name: "UART_CONFIG_STOP_ONE", displayName: "1" },
                    { name: "UART_CONFIG_STOP_TWO", displayName: "2" }
                ]
            },
            //**********************************************************************
            // Parity
            // parity enable
            {
                name        : "pen",
                displayName : "Parity Enable",
                description : 'Parity enable.',
                hidden      : false,
                default     : false,
                onChange    : onChangeParity,
            },
            // even parity select
            {
                name        : "eps",
                displayName : "Parity Select",
                description : 'Choose even or odd parity.',
                hidden      : true,
                default     : 'UART_CONFIG_PAR_ODD',
                options     : [
                    { name: "UART_CONFIG_PAR_ODD",  displayName: "Odd Parity" },
                    { name: "UART_CONFIG_PAR_EVEN", displayName: "Even Parity" }
                ],
            },
            // stick parity select
            {
                name        : "sps",
                displayName : "Stick Parity",
                description : 'Force parity bit to be a certain value regardless of word sent.',
                hidden      : true,
                default     : false,
                onChange    : onChangeParity,
            },
            // output a value to user to know what the stick parity value will be, 
            // based on PEN, EPS, and SPS bits of UARTLCRH
            {
                name        : "stickParityVal",
                displayName : "Stick Parity Value",
                description : 'When stick parity is enabled the parity bit is transmitted and checked as this value. This is based on even/odd parity selection.',
                hidden      : true,
                getValue    : (inst) => {
                    if (    inst.pen == true    &&  // parity enabled
                            inst.sps == true    &&  // stick parity enabled
                            inst.eps == "UART_CONFIG_PAR_EVEN")     // even parity selected
                        
                    {
                        return "0"; // always output 0 for even stick parity
                    }
                    else if (   inst.pen == true    &&  // parity enabled
                                inst.sps == true    &&  // stick parity enabled
                                inst.eps == "UART_CONFIG_PAR_ODD")      // odd parity selected
                    {
                        return "1"; // always output 1 for odd stick parity
                    }
                    return "X"
                },
                default     : "X",
            },
        ]
    },
    //**********************************************************************
    // General Interrupts Settings
    {
        name        : "GROUP_INTERRUPT_SETTINGS",
        displayName : "Interrupt Settings",
        collapsed   : false,
        config      : [
            {
                name        : "enInterrupt",
                displayName : "Enable Interrupts",
                description : 'Choose whether or not to use interrupts.',
                hidden      : false,
                default     : true,
                onChange    : onChangeFIFOInterrupts,
                
            },
            {
                name        : "registerInterrupts",
                displayName : "Register Interrupt Handler",
                description : 'Whether or not to register interrupt handlers in the interrupt module.',
                hidden      : false,
                default     : false,
                
            },
            {
                name        : "enabledInterrupts",
                displayName : "Enabled Interrupts",
                description : 'Choose interrupts to enable.',
                hidden      : false,
                default     : ["UART_INT_TX","UART_INT_RX",],
                minSelections: 0,
                options     : [
                    // {name: "UART_INT_DMATX",    displayName: "DMA TX interrupt"},
                    // {name: "UART_INT_DMARX",    displayName: "DMA RX interrupt"},
                    // moved UART_INT_EOT to txiflsel because it is mutually exlcusive with those bits
                    // {name: "UART_INT_EOT",      displayName: "End of Transmission Interrupt"},
                    {name: "UART_INT_TX",       displayName: "Transmit Interrupt"},
                    {name: "UART_INT_RX",       displayName: "Receive Interrupt"},
                    {name: "UART_INT_OE",       displayName: "Overrun Error Interrupt"},
                    {name: "UART_INT_BE",       displayName: "Break Error Interrupt"},
                    {name: "UART_INT_PE",       displayName: "Parity Error Interrupt"},
                    {name: "UART_INT_FE",       displayName: "Framing Error Interrupt"},
                    {name: "UART_INT_RT",       displayName: "Receive Timeout Interrupt"},
                    {name: "UART_INT_9BIT",     displayName: "9-bit Address Match Interrupt"},
                ],
                
            },
        ]
    },
    //**********************************************************************
    // FIFO settings
    {
        name        : "GROUP_FIFO_SETTINGS",
        displayName : "FIFO Settings",
        collapsed   : false,
        config      : [
            {
                name        : "fen",
                displayName : "Enable FIFO",
                description : 'Whether or not to use FIFO mode.',
                hidden      : false,
                onChange    : onChangeFIFOInterrupts,
                default     : false
            },
            {
                name        : "txiflsel",
                displayName : "Transmit FIFO Interrupt Level",
                description : 'Transmit FIFO interrupt level used. If End of Transmission (EOT) is chosen, then TXRIS bit and interrupt is set only after all transmitted data, including stop bits, have cleared the serializer.',
                hidden      : true,
                default     : "UART_FIFO_TX4_8",
                options     : [
                    {name: "EOT", displayName: "End of Transmission"},
                    {name: "UART_FIFO_TX1_8", displayName: "2 or Less Words in TX-FIFO"},
                    {name: "UART_FIFO_TX2_8", displayName: "4 or Less Words in TX-FIFO"},
                    {name: "UART_FIFO_TX4_8", displayName: "8 or Less Words in TX-FIFO"},
                    {name: "UART_FIFO_TX6_8", displayName: "12 or Less Words in TX-FIFO"},
                    {name: "UART_FIFO_TX7_8", displayName: "14 or Less Words in TX-FIFO"},
                ]
            },
            {
                name        : "rxiflsel",
                displayName : "Receive FIFO Interrupt Level",
                description : 'Receive FIFO interrupt level used.',
                hidden      : true,
                default     : "UART_FIFO_RX4_8",
                options     : [
                    {name: "UART_FIFO_RX1_8", displayName: "2 or More Words in RX-FIFO"},
                    {name: "UART_FIFO_RX2_8", displayName: "4 or More Words in RX-FIFO"},
                    {name: "UART_FIFO_RX4_8", displayName: "8 or More Words in RX-FIFO"},
                    {name: "UART_FIFO_RX6_8", displayName: "12 or More Words in RX-FIFO"},
                    {name: "UART_FIFO_RX7_8", displayName: "14 or More Words in RX-FIFO"},
                ]
            },
        ]
    },
    //**********************************************************************
    // Debug
    {
        name        : "loopback",
        displayName : "Enable Loopback Mode",
        description : 'Internal loopback mode for diagnostic or debug work.',
        hidden      : false,
        default     : false
        
    },
    //**********************************************************************
    // Pinmux
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("UART"),
        onChange    : Pinmux.useCaseChanged,
        
    },

    //**********************************************************************
    // DMA settings
    {
        name        : "GROUP_DMA_SETTINGS",
        displayName : "DMA Settings",
        collapsed   : false,
        config      : [
                //**********************************************************************
        // DMA RX
        {
            name: "dmarx",
            displayName : "Use DMA for Receive",
            description : 'Use a DMA channel to transfer data from the RX FIFO',
            hidden      : false,
            default     : false,
        },
        //**********************************************************************
        // DMA TX
        {
            name: "dmatx",
            displayName : "Use DMA for Transmit",
            description : 'Use a DMA channel to transfer data to the TX FIFO',
            hidden      : false,
            default     : false,
        },  
        ]
    },
  
];

// for F2838x, only include the Pinmux portion (no CM support)
if (pinmuxOnlyDevices.includes(Common.getDeviceName()))
{
    config = [
        //**********************************************************************
        // Pinmux
        {
            name: "useCase",
            displayName : "Use Case",
            description : 'Peripheral use case',
            hidden      : false,
            default     : 'ALL',
            options     : Pinmux.getPeripheralUseCaseNames("UART"),
            onChange    : Pinmux.useCaseChanged,
            
        },
    ];
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
    return (Common.typeMatches(component.type, ["UART"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var uartModule = {
    peripheralName: "UART",
    displayName: "UART",
    maxInstances: Common.peripheralCount("UART"),
    defaultInstanceName: "myUART",
    description: "UART Peripheral",
    filterHardware : filterHardware,
    moduleInstances: (inst) => {
        var ownedInstances = []
        
        // pinmux qualification
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("UART", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            if(pinmuxQualMod.name.includes("rx"))
            {
                pinmuxQualMod.requiredArgs = {
                    padConfig : "PULLUP",
                    qualMode : "GPIO_QUAL_ASYNC",
                }
            }
            else
            {
                pinmuxQualMod.requiredArgs = {
                    padConfig : "STD",
                    qualMode : "GPIO_QUAL_ASYNC",
                }
            }
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)

        // interrupts
        if (inst.enInterrupt && inst.registerInterrupts)
    	{
	        ownedInstances = ownedInstances.concat([{
	            name: "uartInt",      
	            displayName: "UART Interrupt",
	            moduleName: "/driverlib/interrupt.js",
	            collapsed: true,
	            args: {
            		$name : inst.$name + "_UART_INT",
	                int : "INT_" + inst.$name,
	                pinmuxPeripheralModule : "uart",
	                driverlibInt: "INT_#"
	            }
	        }])
    	}

        if (inst.dmarx) {
            ownedInstances = ownedInstances.concat([
                {
                    name: "uartRXDMA",
                    displayName: "RX DMA",
                    moduleName: "/driverlib/dma.js",
                    group: "GROUP_DMA_SETTINGS",
                    collapsed: true,
                    args: {
                        $name: inst.$name + "_RX_DMA",
                    },
                    requiredArgs: {
                        srcAddressLinked: inst.$name + "_RX_DMA_ADDRESS",
                        peripheralRXLinked: true,
                        triggerSource: "DMA_TRIGGER_LINKED"
                    }
                },
            ])
        }
        if (inst.dmatx) {
            ownedInstances = ownedInstances.concat([
                {
                    name: "uartTXDMA",
                    displayName: "TX DMA",
                    moduleName: "/driverlib/dma.js",
                    group: "GROUP_DMA_SETTINGS",
                    collapsed: true,
                    args: {
                        $name: inst.$name + "_TX_DMA",
                    },
                    requiredArgs: {
                        destAddressLinked: inst.$name + "_TX_DMA_ADDRESS",
                        peripheralTXLinked: true,
                        triggerSource: "DMA_TRIGGER_LINKED"
                    }
                },
            ])
        }

    	return ownedInstances;
    },
    config: config,
    templates: {
        boardc : "/driverlib/uart/uart.board.c.xdt",
        boardh : "/driverlib/uart/uart.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.uartPinmuxRequirements,
    validate : onValidate,

    // static module for all instances to hold SYSCLK for baud calculation
    moduleStatic: {
        name: "UartGlobal",
        displayName: "UART Global",
        config: [
            {
                name: "baudSYSCLK",
                displayName: "SYSCLK [Hz] for Baud Rate",
                description: "This is the SYSCLK value used for baud rate calculation",
                default: 100000000,
                getValue: (inst) => {return Common.getSYSCLK()*(1e6);},
                readOnly: true
            },
        ],
        modules: undefined,
    },
};


if (uartModule.maxInstances <= 0)
{
    delete uartModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(uartModule)
    Pinmux.addPinMuxQualGroupToConfig(uartModule)
}

exports = uartModule;