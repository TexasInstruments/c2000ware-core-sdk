let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_i2c.js");

/* Intro splash on GUI */
let longDescription = "The I2C driver provides a simplified application"
        + " interface to access peripherals on an I2C bus.";

var extended_clock_supported_devices = ['f28p551x','f28p55x','f28e12x'];
var push_pull_pins_support = ['f2838x']
var hide_extended_clock_stretching_options = null; 
var extended_clock_stretching_support_available = null; 
var open_drain_pins = null;
var globalConfig = [

    {
        name: "sysClock",
        displayName: "Device SYSCLK in Hz",
        description : 'Device System Clock Frequency',
        hidden      : false,
        default     : Common.getSYSCLK() * 1e6,
        getValue    : () => {return Common.getSYSCLK()*(1e6)},
        readOnly    : true,
    },
];
function setupFlags()
{
    if (extended_clock_supported_devices.indexOf(Common.getDeviceName().toLowerCase()) === -1) 
    {
        hide_extended_clock_stretching_options = true;
        extended_clock_stretching_support_available = false;
    } 
    else
    {
        hide_extended_clock_stretching_options = false;
        extended_clock_stretching_support_available = true;
    }
    if(push_pull_pins_support.indexOf(Common.getDeviceName().toLowerCase()) === -1) 
    {
        open_drain_pins = true;
    }
    else 
    {
        open_drain_pins = false;
    }
}
setupFlags();

function onChangeMode(inst, ui)
{
    if (inst.mode == "CONTROLLER") {
        ui.loopback.hidden = false;
        ui.bitRate.hidden = false;
        ui.duty.hidden = false;
    }
    else {
        ui.loopback.hidden = true;
        ui.bitRate.hidden = true;
        ui.duty.hidden = true;
    }
}


function onChangeUseInterrupts(inst, ui)
{
    if (inst.useInterrupts)
    {
        ui.enabledInterrupts.hidden = false;
        ui.enabledFIFOInterrupts.hidden = false;
        ui.registerInterrupts.hidden = false;
        
        ui.txFifo.hidden = false;
        ui.rxFifo.hidden = false;
        
        if (!inst.useFifo) {
            ui.enabledFIFOInterrupts.hidden = true;
            ui.txFifo.hidden = true;
            ui.rxFifo.hidden = true;
        }
    }
    else
    {
        ui.enabledInterrupts.hidden = true;
        ui.enabledFIFOInterrupts.hidden = true;
        ui.registerInterrupts.hidden = true;
        
        ui.txFifo.hidden = true;
        ui.rxFifo.hidden = true;
    }

}

function onValidate(inst, validation) 
{   
    var bitRateError = false;
    var targetAddrError = false;
    var ownAddrError = false;
    var maxAddress = (inst.addressMode.includes(10)? 0x3FF: 0x7F);
    var bitRateInt = parseInt(inst.bitRate);
    var customModuleFrequencyInt = parseInt(inst.customModuleFrequency);
    var customModuleFrequencyError = false;
    if(customModuleFrequencyInt < 7000000 || customModuleFrequencyInt > 12000000)
    {
       customModuleFrequencyError = true; 
    }
    if (bitRateInt < 1 || bitRateInt > 400000)
    {
        bitRateError = true;
    }
    var targetAddressInt = parseInt(inst.targetAddress);
    var ownAddressInt = parseInt(inst.ownAddress);

    if (targetAddressInt < 0 || targetAddressInt > maxAddress)
    {
        targetAddrError = true;
    }

    if (ownAddressInt < 0 || ownAddressInt > maxAddress)
    {
        ownAddrError = true;
    }
    if(inst.dataCount > 0xFFFF | inst.dataCount < 0)
    {
        validation.logError(
            "Enter an integer for data count between 0 and 65535!", 
            inst, "dataCount");
    }
    if(bitRateError)
    {
        validation.logError(
            "Enter an integer for bit rates between 1 and 400000!", 
            inst, "bitRate");
    }
    if(targetAddrError && inst.mode == "CONTROLLER")
    {
        validation.logError(
            "Target address must be between 0 and " + maxAddress + "!", 
            inst, "targetAddress");
    }
    if(ownAddrError && inst.mode != "CONTROLLER")
    {
        validation.logError(
            "Own Target address must be between 0 and " + maxAddress + "!", 
            inst, "ownAddress");
    }
    if(customModuleFrequencyError)
    {
        validation.logError(
            "Module Clock Frequency must be between 7 MHz and 12 MHz", 
            inst, "customModuleFrequency");
    }

    var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("I2C", inst)
    for (var pinmuxQualMod of pinmuxQualMods)
    {
        /* if(open_drain_pins === true)
        {
            if (((inst[pinmuxQualMod.name].padConfig.includes("PULLUP")) && !(inst[pinmuxQualMod.name].padConfig.includes("OD"))) || (inst[pinmuxQualMod.name].padConfig.includes("INVERT")))
            {
                validation.logError("The push-pull and inverted pad configurations should not be used for the I2C module.", inst);
            }
        }
        else 
        {
            if (((inst[pinmuxQualMod.name].padConfig.includes("OD")) && !(inst[pinmuxQualMod.name].padConfig.includes("PULLUP"))) || (inst[pinmuxQualMod.name].padConfig.includes("INVERT")))
            {
                validation.logError("The open-drain and inverted pad configurations should not be used for the I2C module.", inst);
            }
        } */
    }
}

function I2C_InterruptList(hide_clock_stretching_option_flag)
{
    let base_interrupt =  [
        {name: "I2C_INT_ARB_LOST", displayName : "Arbitration-lost interrupt"},
        {name: "I2C_INT_NO_ACK", displayName : "NACK interrupt"},
        {name: "I2C_INT_REG_ACCESS_RDY", displayName : "Register-access-ready interrupt"},
        {name: "I2C_INT_RX_DATA_RDY", displayName : "Receive-data-ready interrupt"},
        {name: "I2C_INT_TX_DATA_RDY", displayName : "Transmit-data-ready interrupt"},
        {name: "I2C_INT_STOP_CONDITION", displayName : "Stop condition detected"},
        {name: "I2C_INT_ADDR_TARGET", legacyNames: ["I2C_INT_ADDR_SLAVE"], displayName : "Addressed as target interrupt"}
    ];
    if (hide_clock_stretching_option_flag == false) 
    {
        base_interrupt.push(
	        {name: "I2C_INT_SCL_ECS", displayName: "Extended clock stretching interrupt"}
        )
    }
    return base_interrupt;

}

function onModuleClockChange(inst, ui)
{
    if(inst.useDefaultModuleFrequency)
    {
        ui.customModuleFrequency.hidden = true;
    }
    else 
    {
        ui.customModuleFrequency.hidden = false;
    }
}

/* Array of I2C configurables that are common across device families */
let config = [
    {
        name        : "mode",
        displayName : "I2C Device Mode",
        description : 'I2C device mode: controller/target',
        hidden      : false,
        onChange    : onChangeMode,
        default     : 'CONTROLLER',
        options     : [
            { name: "CONTROLLER", legacyNames : ["MASTER"], displayName : "Controller Mode"},
            { name: "TARGET", legacyNames : ["SLAVE"], displayName : "Target Mode"  },
        ]
    },
    {
        name        : "duty",
        displayName : "Clock Duty Cycle",
        description : 'Clock duty cycle mode',
        hidden      : false,
        default     : device_driverlib_peripheral.I2C_DutyCycle[0].name,
        options     : device_driverlib_peripheral.I2C_DutyCycle
    },
    {
        name        : "bitRate",
        displayName : "Bit Rate",
        description : 'Controller transmitter bitrate',
        hidden      : false,
        default     : 400000,
    },
    {
        name        : "useDefaultModuleFrequency",
        displayName : "Default I2C Module Clock Frequency",
        description : 'Configure Module Clock Frequency',
        hidden      : false,
        default     : true,
        onChange    : onModuleClockChange
    },
    {
        name        : "customModuleFrequency",
        displayName : "I2C Module Clock Frequency",
        description : 'Configure Module Clock Frequency',
        hidden      : true,
        default     : 10000000,
    },
    {
        name        : "initialMode",
        displayName : "Initial Mode",
        description : 'Initial mode, transmitter/receiver',
        hidden      : false,
        default     : 'SEND_MODE',
        options     : [
            { name: "SEND_MODE", displayName : "Transmitter Mode" },
            { name: "RECEIVE_MODE", displayName : "Receiver Mode"  },
        ]
    },
    {
        name        : "bitCount",
        displayName : "Bit Count",
        description : 'Bit count, number of bits per transfer',
        hidden      : false,
        default     : device_driverlib_peripheral.I2C_BitCount[0].name,
        options     : device_driverlib_peripheral.I2C_BitCount
    },
    {
        name        : "dataCount",
        displayName : "Data Count",
        description : 'Set number of bytes to be to transfer or receive when repeat mode is off',
        hidden      : false,
        default     : 1
    },
    {
        name        : "addressMode",
        displayName : "Address Mode",
        description : 'Address mode, 7-bit/8-bit',
        hidden      : false,
        default     : device_driverlib_peripheral.I2C_AddressMode[0].name,
        options     : device_driverlib_peripheral.I2C_AddressMode
    },
    {
        name        : "targetAddress",
        legacyNames : ["slaveAddress"],
        displayName : "Target Address",
        description : 'The target address, 7bit/10bit: 0x00 to 0x7F or 0x3FF',
        hidden      : false,
        displayFormat: "hex",
        default     : 0x00
    },
    {
        name        : "ownAddress",
        legacyNames : ["ownSlaveAddress"],
        displayName : "Own Address",
        description : 'The device\'s own target address, 7bit/10bit: 0x00 to 0x7F or 0x3FF',
        hidden      : false,
        displayFormat: "hex",
        default     : 0x00
    },
    {
        name        : "loopback",
        displayName : "Loopback Mode",
        description : 'loopback mode',
        hidden      : false,
        default     : false,
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
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : I2C_InterruptList(hide_extended_clock_stretching_options), 
        
    },
    {
        name        : "enabledFIFOInterrupts",
        displayName : "Enabled FIFO Interrupts",
        description : 'Which FIFO interrupts to enabled.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : [
            {name: "I2C_INT_RXFF", displayName: "Receive Interrupt"},
            {name: "I2C_INT_TXFF", displayName: "Transmit Interrupt"},
        ],
        
    },
    {
        name        : "useFifo",
        displayName : "FIFO Mode",
        description : 'FIFO mode',
        hidden      : false,
        onChange    : onChangeUseInterrupts,
        default     : true,
    },

    {
        name        : "txFifo",
        displayName : "Transmit FIFO Interrupt Level",
        description : 'Transmit FIFO interrupt level used.',
        hidden      : false,
        default     : device_driverlib_peripheral.I2C_TxFIFOLevel[0].name,
        options     : device_driverlib_peripheral.I2C_TxFIFOLevel
    },

    {
        name        : "rxFifo",
        displayName : "Receive FIFO Interrupt Level",
        description : 'Receive FIFO interrupt level used.',
        hidden      : false,
        default     : device_driverlib_peripheral.I2C_RxFIFOLevel[0].name,
        options     : device_driverlib_peripheral.I2C_RxFIFOLevel
    },

    {
        name        : "emulationMode",
        displayName : "Emulation Mode",
        description : 'Emulation Mode',
        hidden      : false,
        default     : device_driverlib_peripheral.I2C_EmulationMode[0].name,
        options     : device_driverlib_peripheral.I2C_EmulationMode
    },

    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("I2C"),
        onChange    : Pinmux.useCaseChanged,
    },

    {
        name: "useExtendedClockStretching",
        displayName: "Use Automatic Extended Clock Stretching",
        description: "Enables Extended Clock Stretching",
        hidden: hide_extended_clock_stretching_options,
        default: false,
    },

    {
        name: "extendedClockStretchingSupport",
        default: extended_clock_stretching_support_available,
        hidden: true
    }
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
    return (Common.typeMatches(component.type, ["I2C"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}
var i2cModule = {
    peripheralName: "I2C",
    displayName: "I2C",
    maxInstances: Common.peripheralCount("I2C"),
    defaultInstanceName: "myI2C",
    description: "Inter-Integrated Circuit Peripheral",
    longDescription: (Common.getCollateralFindabilityList("I2C")),
    filterHardware : filterHardware,
    config: config,
    moduleInstances: (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("I2C", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.requiredArgs = {
                qualMode : "GPIO_QUAL_ASYNC",
            }
            if(open_drain_pins === true)
            {
                pinmuxQualMod.args.padConfig = "PULLUP";
            } 
            else 
            {
                pinmuxQualMod.args.padConfig = "STD";
            }
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)


        if (inst.useInterrupts && inst.registerInterrupts)
        {
            ownedInstances = ownedInstances.concat([{
                name: "i2cInt",      
                displayName: "I2C Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
            		$name : inst.$name + "_INT",
                    int : "INT_" + inst.$name,
                    pinmuxPeripheralModule : "i2c",
                    driverlibInt: "INT_#",
                    enableInterrupt: true
                }
            }]);
            if(inst.useFifo)
            {
                ownedInstances = ownedInstances.concat([{
                name: "i2cFIFOInt",      
                displayName: "FIFO Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
            		$name : inst.$name + "_FIFO_INT",
                    int : "INT_" + inst.$name + "_FIFO",
                    pinmuxPeripheralModule : "i2c",
                    driverlibInt: "INT_#_FIFO",
                    enableInterrupt: true
                }
            }]);
            }
        }

        return ownedInstances;
    },
    templates: {
        boardc : "/driverlib/i2c/i2c.board.c.xdt",
        boardh : "/driverlib/i2c/i2c.board.h.xdt"
    },
	moduleStatic: {
        name: "I2CGlobal",
        displayName: "I2C Global",
        config: globalConfig,
    },
    pinmuxRequirements    : Pinmux.i2cPinmuxRequirements,
    validate    : onValidate
};


if (i2cModule.maxInstances <= 0)
{
    delete i2cModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(i2cModule)
    Pinmux.addPinMuxQualGroupToConfig(i2cModule)
}


exports = i2cModule;