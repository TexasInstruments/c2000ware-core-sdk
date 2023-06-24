let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_lin.js");

/* Intro splash on GUI */
let longDescription = "LIN is a low cost communication peripheral which" +
    "can be used in place of CAN where performance can be traded off for cost. " +
    "This applicatoin provides a simplified interface to configure the different " + 
    "parameters of the peripheral such as LIN/SCI mode, Commander/Responder Mode " + 
    "and test mode etc. ";

function onChangeUseLoopback(inst, ui)
{
    if (inst.enableLoopback) {
        ui.loopbackMode.hidden = false;
    }
    else {
        ui.loopbackMode.hidden = true;
        ui.loopbackType.hidden = true;
        ui.analogLoopbackPath.hidden = true;
    }
}
function onChangeUseLoopbackMode(inst, ui)
{
    if (inst.enableLoopback && (inst.loopbackMode == "LIN_TEST_EXTERNAL")) {
        ui.loopbackType.hidden = false;
    }
    else {
        ui.loopbackType.hidden = true;
        ui.analogLoopbackPath.hidden = true;
    }
}
function onChangeUseLoopbackType(inst, ui)
{
    if (inst.enableLoopback && (inst.loopbackType == "LIN_LOOPBACK_ANALOG")) {
        ui.analogLoopbackPath.hidden = false;
    }
    else {
        ui.analogLoopbackPath.hidden = true;
    }
}
function onChangeEnableInterrupt(inst, ui)
{
    if (inst.enableInterrupt) {
        ui.interruptFlags.hidden = false;
        ui.interruptLine.hidden = false;
        ui.interruptPriorityLine0.hidden = false;
        ui.interruptPriorityLine1.hidden = false;
    }
    else {
        ui.interruptFlags.hidden = true;
        ui.interruptLine.hidden = true;
        ui.interruptPriorityLine0.hidden = true;
        ui.interruptPriorityLine1.hidden = true;
    }
}

function onChangeLinConfig(inst, ui)
{
    if (inst.useDefaultLin) {
        ui.linMode.hidden = true;
        ui.linCommMode.hidden = true;
        ui.linDebugMode.hidden = true;
        ui.linChecksumType.hidden = true;
        ui.linMessageFilter.hidden = true;
        ui.enableParity.hidden = true;
    }
    else {
        ui.linMode.hidden = false;
        ui.linCommMode.hidden = false;
        ui.linDebugMode.hidden = false;
        ui.linChecksumType.hidden = false;
        ui.linMessageFilter.hidden = false;
        ui.enableParity.hidden = false;
    }
}

let LIN_InterruptFlags = [
    {name: " LIN_INT_WAKEUP", displayName : " Wakeup "},
    {name: " LIN_INT_TO", displayName : " Time out "},
    {name: " LIN_INT_TOAWUS", displayName : " Time out after wakeup signal "},
    {name: " LIN_INT_TOA3WUS", displayName : " Time out after 3 wakeup signals "},
    {name: " LIN_INT_TX", displayName : " Transmit buffer ready "},
    {name: " LIN_INT_RX", displayName : " Receive buffer ready "},
    {name: " LIN_INT_ID", displayName : " Received matching identifier "},
    {name: " LIN_INT_PE", displayName : " Parity error "},
    {name: " LIN_INT_OE", displayName : " Overrun error "},
    {name: " LIN_INT_FE", displayName : " Framing error "},
    {name: " LIN_INT_NRE", displayName : " No response error "},
    {name: " LIN_INT_ISFE", displayName : " Inconsistent sync field error "},
    {name: " LIN_INT_CE", displayName : " Checksum error "},
    {name: " LIN_INT_PBE", displayName : " Physical bus error "},
    {name: " LIN_INT_BE", displayName : " Bit error "},
    {name: " LIN_INT_ALL", displayName : " All interrupts "},
];
/* Array of CAN configurables that are common across device families */
let config = [
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("LIN"),
        onChange    : Pinmux.useCaseChanged,
        
    },
    {
        name        : "enableLoopback",
        displayName : "Enable Loopback",
        description : 'Whether loopback mode to be enabled.',
        hidden      : false,
        onChange    : onChangeUseLoopback,
        default     : false,
    },
    {
        name        : "loopbackMode",
        displayName : "Loopback Mode ",
        description : 'Loopback Mode ',
        hidden      : true,
        onChange    : onChangeUseLoopbackMode,
        default     : "LIN_TEST_INTERNAL",
        options     : [
            {name: "LIN_TEST_INTERNAL", displayName : "Internal Loopback Mode"},
            {name: "LIN_TEST_EXTERNAL", displayName : "External Loopback Mode"},
        ],
    },
    {
        name        : "loopbackType",
        displayName : "Type of LoopBack",
        description : 'Type of LoopBack',
        onChange    : onChangeUseLoopbackType,
        hidden      : true,
        default     : device_driverlib_peripheral.LIN_LoopbackType[0].name,
        options     : device_driverlib_peripheral.LIN_LoopbackType,
    },
    {
        name        : "analogLoopbackPath",
        displayName : "Loopback path in Analog loopback",
        description : 'Loopback path in Analog loopback',
        hidden      : true,
        default     : device_driverlib_peripheral.LIN_AnalogLoopback[0].name,
        options     : device_driverlib_peripheral.LIN_AnalogLoopback,
    },
    {
        name        : "enableInterrupt",
        displayName : "Enable Interrupt",
        description : 'To Enable LIN Interrupts.',
        hidden      : false,
        onChange    : onChangeEnableInterrupt,
        default     : false,
    },
    {
        name        : "interruptFlags",
        displayName : "Interrupt Flags",
        description : 'Which Interrupts to enable.',
        hidden      : true,
        minSelections : 0,
        default     : [],
        options     : LIN_InterruptFlags,
        
    },
    {
        name        : "interruptLine",
        displayName : "Interrupt Line",
        description : 'Which Interrupts line to use.',
        hidden      : true,
        minSelections : 0,
        default     : [],
        options     : device_driverlib_peripheral.LIN_InterruptLine,
        
    },
    {
        name        : "interruptPriorityLine0",
        displayName : "Interrupt line 0 triggers",
        description : 'Interrupt line 0 triggers',
        hidden      : true,
        minSelections : 0,
        default     : [],
        options     : LIN_InterruptFlags,
        
    },
    {
        name        : "interruptPriorityLine1",
        displayName : "Interrupt line 1 triggers",
        description : 'Interrupt line 1 triggers',
        hidden      : true,
        minSelections : 0,
        default     : [],
        options     : LIN_InterruptFlags,
        
    },
    {
        name        : "useDefaultLin",
        displayName : "Use Default LIN Configuration",
        description : 'Use Default LIN Configuration',
        hidden      : false,
        onChange    : onChangeLinConfig,
        default     : true,
    },
    {
        name        : "linMode",
        displayName : "LIN Mode ",
        description : 'LIN Mode ',
        hidden      : true,
        default     : device_driverlib_peripheral.LIN_LINMode[1].name,
        options     : device_driverlib_peripheral.LIN_LINMode,
    },
    {
        name        : "linCommMode",
        displayName : "LIN Communication Mode ",
        description : 'LIN Communication Mode ',
        hidden      : true,
        default     : device_driverlib_peripheral.LIN_CommMode[0].name,
        options     : device_driverlib_peripheral.LIN_CommMode,
    },
    {
        name        : "linDebugMode",
        displayName : "LIN Debug Mode ",
        description : 'LIN Debug Mode ',
        hidden      : true,
        default     : device_driverlib_peripheral.LIN_DebugMode[1].name,
        options     : device_driverlib_peripheral.LIN_DebugMode,
    },
    {
        name        : "linChecksumType",
        displayName : "LIN Checksum Type ",
        description : 'LIN Checksum Type ',
        hidden      : true,
        default     : device_driverlib_peripheral.LIN_ChecksumType[1].name,
        options     : device_driverlib_peripheral.LIN_ChecksumType,
    },
    {
        name        : "linMessageFilter",
        displayName : "LIN Message Filter ",
        description : 'LIN Message Filter ',
        hidden      : true,
        default     : device_driverlib_peripheral.LIN_MessageFilter[1].name,
        options     : device_driverlib_peripheral.LIN_MessageFilter,
    },
    {
        name        : "enableParity",
        displayName : "Enable Parity Check",
        description : 'Enable Parity Check.',
        hidden      : true,
        default     : true,
    },
];


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
    return (Common.typeMatches(component.type, ["LIN"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var linModule = {
    peripheralName: "LIN",
    displayName: "LIN",
    maxInstances: Common.peripheralCount("LIN"),
    defaultInstanceName: "myLIN",
    description: "LIN Peripheral",
    filterHardware : filterHardware,
    moduleInstances : (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("LIN", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.requiredArgs = {
               qualMode : "GPIO_QUAL_ASYNC",
            }
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)
        return ownedInstances;
    },
    config: config,
    templates: {
        boardc : "/driverlib/lin/lin.board.c.xdt",
        boardh : "/driverlib/lin/lin.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.linPinmuxRequirements
};


if (linModule.maxInstances <= 0)
{
    delete linModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(linModule)
    Pinmux.addPinMuxQualGroupToConfig(linModule)
}

exports = linModule;