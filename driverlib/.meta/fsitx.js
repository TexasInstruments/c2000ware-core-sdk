let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_fsi.js");

/* Intro splash on GUI */
let longDescription = "The Fast Serial Interface (FSI) module is a serial " +
                    "communication peripheral capable of reliable high-speed " + 
                    "communication across isolation devices.";

function onChangeEnableInterrupt(inst, ui)
{
    if (inst.enableInterrupt) {
        ui.useInterrupts.hidden = false;
        if (inst.useInterrupts.indexOf(device_driverlib_peripheral.FSI_InterruptNum[0].name) != -1) 
        {
            ui.enabledINT1Interrupts.hidden = false;
            ui.registerInterruptLine1.hidden = false;
        }
        else
        {
            ui.enabledINT1Interrupts.hidden = true;
            ui.registerInterruptLine1.hidden = true;
        }
    
        if (inst.useInterrupts.indexOf(device_driverlib_peripheral.FSI_InterruptNum[1].name) != -1) 
        {
            ui.enabledINT2Interrupts.hidden = false;
            ui.registerInterruptLine2.hidden = false;
        }
        else
        {
            ui.enabledINT2Interrupts.hidden = true;
            ui.registerInterruptLine2.hidden = true;
        }
    }
    else {
        ui.useInterrupts.hidden = true;
        ui.enabledINT1Interrupts.hidden = true;
        ui.enabledINT2Interrupts.hidden = true;
        ui.registerInterruptLine1.hidden = true;
        ui.registerInterruptLine2.hidden = true;
    }
}

function onChangeTransmissionMode(inst, ui)
{
    if (inst.startOfTransmissionMode.indexOf(device_driverlib_peripheral.FSI_TxStartMode[1].name) != -1) {
        ui.extTriggerSource.hidden = false;
    }
    else {
        ui.extTriggerSource.hidden = true;
    }
}

function onChangeEnablePingTimeout(inst, ui)
{
    if (inst.pingTimeout) {
        ui.selectPingMode.hidden = false;
        ui.timeoutDelay.hidden = false;
    }
    else {
        ui.selectPingMode.hidden = true;
        ui.timeoutDelay.hidden = true;
    }
}

function onChangeUserCRC(inst, ui)
{
    if (inst.userCRC) {
        ui.valueCRC.hidden = false;
    }
    else {
        ui.valueCRC.hidden = true;
    }
}

/* Array of FSI configurables that are common across device families */
let config = [  
    {
        //
        // This is needed for locking some options when a HARDWARE is needed
        // Currently we only have NO STROB connection for EQEP on launchpads
        //
        name: "$hardware",
        onChange: (inst, ui) => {
            if (inst.$hardware)
            {
                var useCaseNames = Pinmux.getPeripheralUseCaseNames("FSITX").map((useCaseOpt) => {
                      return useCaseOpt.name
                    }
                );

                if (useCaseNames.includes("FSI TX Dual Dataline"))
                {
                    inst.useCase = "FSI TX Dual Dataline"
                }
            }
        }
    },

    {
        name        : "clkPres",
        displayName : "Clock Prescalar",
        description : 'Prescaler for the TX CLK, 50 MHz max.',
        hidden      : false,
        default     : 4
    },

    {
        name: "GROUP_FRAMECFG",
        displayName: "Frame Configuration",
        longDescription: "This section is used for frame configuration " +
                        "for the TX module. The frame tag and frame type " +
                        "are for initial configuration and not for run time.",
        collapsed: false,
        config: [
        {
            name        : "dataWidth",
            displayName : "Data Width",
            description : 'Number of lanes for communication',
            hidden      : false,
            default     : device_driverlib_peripheral.FSI_DataWidth[0].name,
            options     : device_driverlib_peripheral.FSI_DataWidth,
        },

        {
            name        : "startOfTransmissionMode",
            displayName : "Start of Transmission Mode",
            description : 'Mode for the start of transmission',
            hidden      : false,
            onChange    : onChangeTransmissionMode,
            default     : device_driverlib_peripheral.FSI_TxStartMode[0].name,
            options     : device_driverlib_peripheral.FSI_TxStartMode,
        },

        {
            name        : "extTriggerSource",
            displayName : "External Start of Transmission Trigger Source",
            description : 'External Start of Transmission Trigger Source',
            hidden      : true,
            default     : device_driverlib_peripheral.FSI_ExtFrameTriggerSrc[0].name,
            options     : device_driverlib_peripheral.FSI_ExtFrameTriggerSrc,
        },

        {
            name        : "frameType",
            displayName : "Initial frame type",
            description : 'Initial frame type to be sent',
            longDescription: "This configuration is just for the first frame to " +
                            "be sent. The user will have to configure run time updates " +
                            "in the code.",
            hidden      : false,
            default     : device_driverlib_peripheral.FSI_FrameType[0].name,
            options     : device_driverlib_peripheral.FSI_FrameType,
        },

        {
            name        : "frameTag",
            displayName : "Initial frame tag",
            description : 'Initial frame tag to be sent',
            longDescription: "This configuration is just for the first frame to " +
                            "be sent. The user will have to configure run time updates " +
                            "in the code.",
            hidden      : false,
            default     : device_driverlib_peripheral.FSI_FrameTag[0].name,
            options     : device_driverlib_peripheral.FSI_FrameTag,
        },

        {
            name        : "softwareFrameSize",
            displayName : "Software Frame Size",
            description : 'When selecting N-WORD frame type, this determines number of words (N)',
            hidden      : false,
            default     : '8',
            options     : [
                { name: "1" , displayName : "1-Word"},
                { name: "2" , displayName : "2-Word"},
                { name: "3" , displayName : "3-Word"},
                { name: "4" , displayName : "4-Word"},
                { name: "5" , displayName : "5-Word"},
                { name: "6" , displayName : "6-Word"},
                { name: "7" , displayName : "7-Word"},
                { name: "8" , displayName : "8-Word"},
                { name: "9" , displayName : "9-Word"},
                { name: "10" , displayName : "10-Word"},
                { name: "11" , displayName : "11-Word"},
                { name: "12" , displayName : "12-Word"},
                { name: "13" , displayName : "13-Word"},
                { name: "14" , displayName : "14-Word"},
                { name: "15" , displayName : "15-Word"},
                { name: "16" , displayName : "16-Word" }
            ]
        },
    ]
    },

    {
        name: "GROUP_INT",
        displayName: "Interrupts",
        longDescription: "This section is used to configure the interrupts " +
                        "for the TX module.",
        collapsed: false,
        config: [
        {
            name        : "enableInterrupt",
            displayName : "Enable Interrupt",
            description : 'To Enable FSI Interrupts.',
            hidden      : false,
            onChange    : onChangeEnableInterrupt,
            default     : false,
        },
        {
            name        : "useInterrupts",
            displayName : "Use Interrupt",
            description : 'Whether or not to use Interrupt mode.',
            onChange    : onChangeEnableInterrupt,
            hidden      : true,
            default     : [],
            minSelections: 0,
            options     : device_driverlib_peripheral.FSI_InterruptNum
            
        },

        {
            name        : "enabledINT1Interrupts",
            displayName : "Enabled INT1 Interrupts",
            description : 'Which interrupts to be enabled for INT1.',
            hidden      : true,
            default     : [],
            minSelections: 0,
            options     : device_driverlib_peripheral.FSI_TX_EVT,
            
        },

        {
            name        : "enabledINT2Interrupts",
            displayName : "Enabled INT2 Interrupts",
            description : 'Which interrupts to be enabled for INT2.',
            hidden      : true,
            default     : [],
            minSelections: 0,
            options     : device_driverlib_peripheral.FSI_TX_EVT,
            
        },

        {
            name        : "registerInterruptLine1",
            displayName : "Register Interrupt Line1 Handler",
            description : 'Whether or not to register interrupt Line1 handlers in the interrupt module.',
            hidden      : true,
            default     : false
        },
        {
            name        : "registerInterruptLine2",
            displayName : "Register Interrupt Line2 Handler",
            description : 'Whether or not to register interrupt Line2 handlers in the interrupt module.',
            hidden      : true,
            default     : false
        },
    ]
    },

    {
        name: "GROUP_PING",
        displayName: "Ping Timeout",
        longDescription: "This function is meant to set up automatic ping transmission " +
                        "for the TX module. The delay value will be time difference between " +
                        "ping frames sent.",
        collapsed: false,
        config: [
        {
            name        : "pingTimeout",
            displayName : "Enable PING Timeout",
            description : 'Enables the timeout for Ping.',
            hidden      : false,
            onChange    : onChangeEnablePingTimeout,
            default     : false,
        },

        {
            name        : "selectPingMode",
            displayName : "Select PING Timeout Mode",
            description : 'Select the timeout mode for Ping.',
            hidden      : true,
            default     : device_driverlib_peripheral.FSI_PingTimeoutMode[0].name,
            options     : device_driverlib_peripheral.FSI_PingTimeoutMode
        },

        {
            name        : "timeoutDelay",
            displayName : "Select PING Timeout Delay",
            description : 'Enter the timeout value for ping watchdog in integer.',
            hidden      : true,
            default     : 0
        },
    ]
    },

    {
        name: "GROUP_CRCECC",
        displayName: "User CRC and ECC",
        longDescription: "This section allows the user to configure the user CRC " +
                        "and ECC computation width. The CRC option if not enabled " +
                        "will be computed by the hardware. For ECC, the default option " +
                        "is 32 bits wide which can be changed to 16 bits based on requirement.",
        collapsed: false,
        config: [
        {
            name        : "userCRC",
            displayName : "User calculates CRC",
            description : 'Whether the user calculates the CRC or the calculation is done by the CRC hardware',
            hidden      : false,
            onChange    : onChangeUserCRC,
            default     : false
        },

        {
            name        : "valueCRC",
            displayName : "Enter CRC Value",
            description : 'Value to be entered within 7 bits',
            hidden      : true,
            default     : '10'
        },
        
        {
            name        : "eccComputeWidth",
            displayName : "ECC Compute Width Mode",
            description : 'The ECC Compute Width Mode',
            hidden      : false,
            default     : device_driverlib_peripheral.FSI_ECCComputeWidth[0].name,
            options     : device_driverlib_peripheral.FSI_ECCComputeWidth
        },
    ]
    },

    {
        name: "useCase",
        displayName : "PinMux Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("FSITX"),
        onChange    : Pinmux.useCaseChanged,
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
    return (Common.typeMatches(component.type, ["FSITX", "FSI"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var fsitxModule = {
    peripheralName: "FSITX",
    displayName: "FSITX",
    maxInstances: Common.peripheralCount("FSITX"),
    defaultInstanceName: "myFSITX",
    description: "Fast Serial Interface Transmitter Peripheral",
    longDescription: (Common.getCollateralFindabilityList("FSI")),
    filterHardware : filterHardware,
    validate: onValidate,
    moduleInstances: (inst) => {
        var interrupts = []
        var dlibInt1 = "INT_#1";
        var dlibInt2 = "INT_#2";
        if (["F28004x"].includes(Common.getDeviceName()))
        {
            dlibInt1 = "INT_#_INT1"
            dlibInt2 = "INT_#_INT2"
        }

        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("FSITX", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.requiredArgs = {
                qualMode : "GPIO_QUAL_ASYNC",
                padConfig : "STD",
            }
        }
        interrupts = interrupts.concat(pinmuxQualMods)

        if (inst.enableInterrupt && inst.registerInterruptLine1)
        {
            interrupts.push(
                {
                    name: "fsiTxInt1",      
                    displayName: "Tx Interrupt 1",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_INT1",
                        int : "INT_" + inst.$name + "_1",
                        pinmuxPeripheralModule : "fsitx",
                        driverlibInt: dlibInt1
                    }
                }
            )
        }
        if (inst.enableInterrupt && inst.registerInterruptLine2)
        {
            interrupts.push(
                {
                    name: "fsiTxInt2",      
                    displayName: "Tx Interrupt 2",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_INT2",
                        int : "INT_" + inst.$name + "_2",
                        pinmuxPeripheralModule : "fsitx",
                        driverlibInt: dlibInt2
                    }
                }
            )
        }
        return interrupts;
    },
    validate: onValidate,
    config: config,
    templates: {
        boardc : "/driverlib/fsitx/fsitx.board.c.xdt",
        boardh : "/driverlib/fsitx/fsitx.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.fsitxPinmuxRequirements
};

function onValidate(inst, validation) 
{   
    if (inst.clkPres < 0 || inst.clkPres > 0xFF)
    {
        validation.logError(
            "Enter an integer for Clock Prescalar between 0 and 255!", 
            inst, "clkPres");
    }
    if (inst.timeoutDelay < 0 || inst.timeoutDelay > 0xFFFFFFFF)
    {
        validation.logError(
            "Enter integer value for Ping Timeout within 32 bits!", 
            inst, "timeoutDelay");
    }
    if (inst.valueCRC < 0 || inst.valueCRC > 0xFF)
    {
        validation.logError(
            "Enter an integer for User CRC between 0 and 255!", 
            inst, "valueCRC");
    }
    
}


if (fsitxModule.maxInstances <= 0)
{
    delete fsitxModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(fsitxModule)
    Pinmux.addPinMuxQualGroupToConfig(fsitxModule)
}

exports = fsitxModule;