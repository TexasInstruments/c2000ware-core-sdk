let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_pmbus.js");

/* Intro splash on GUI */
let longDescription = "The PMBUS driver provides a simplified application"
			+ " interface to access peripherals on an PMBus.";
			
			
var SysClk_MHz = Common.SYSCLK_getMaxMHz();
var SysClk_Hz = SysClk_MHz * 1000000;
var Reserved_addresses=[0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0x28, 0x2C, 0x2D, 0x37, 0x40, 0x41, 0x42, 0x43, 0x44, 0x48, 0x49, 0x4A, 0x4B, 0x61, 0x78, 0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F];  
var globalConfig = [

    {
        name: "sysClock",
        displayName: "Device SYSCLK in MHz",
        description : 'Device System Clock Frequency',
        hidden      : false,
        default     : SysClk_MHz,
        readOnly    : true,
    },
]
var pmbus_fast_plus_supported_devices = ['f28p55x']
var pmbus_fast_supported_devices = ['f28p55x', 'f28p65x', 'f2838x', 'f28002x', 'f28003x', 'f28004x', 'f280015x']
var pmbus_zero_hold_supported_devices = ['f28p55x']

var hide_pmbus_fast_plus_options = null;
var hide_pmbus_fast_options = null;
var hide_pmbus_zero_hold_options = null;
var pmbus_zero_hold_support = null;

function setupFlags()
{
    // FAST_MODE_PLUS option
    if (pmbus_fast_plus_supported_devices.indexOf(Common.getDeviceName().toLowerCase()) === -1)
    {
        hide_pmbus_fast_plus_options = true;
    }
    else 
    {
        hide_pmbus_fast_plus_options = false;
    }

    // FAST_MODE option
    if (pmbus_fast_supported_devices.indexOf(Common.getDeviceName().toLowerCase()) === -1)
    {
        hide_pmbus_fast_options = true;
    }
    else 
    {
        hide_pmbus_fast_options = false;
    }

    // ZERO_HOLD option
    if (pmbus_zero_hold_supported_devices.indexOf(Common.getDeviceName().toLowerCase()) === -1)
    {
        hide_pmbus_zero_hold_options = true;
        pmbus_zero_hold_support = false;
    }
    else 
    {
        hide_pmbus_zero_hold_options = false;
        pmbus_zero_hold_support = true;
    }
}
setupFlags();
function onChangeUseInterrupts(inst, ui)
{
    if (inst.useInterrupts)
    {
        ui.enabledInterrupts.hidden = false;
        ui.registerInterrupts.hidden = false;
    }
    else
    {
        ui.enabledInterrupts.hidden = true;
        ui.registerInterrupts.hidden = true;
    }

}

function setCharAt(str,index,chr) 
{
    if(index > str.length-1) return str;
    return str.substring(0,index) + chr + str.substring(index+1);
}

function calcAddress(inst,ui)
{
	var mask = inst.TargetAddressMask;
	var addr = inst.TargetAddress.toString(2);
	
	if (mask == 0x7F) return addr;
	
	
	for (let i = 0; i < 7; i++)
	{
		if ((mask & (1<<i))==0)
		{
			addr = setCharAt(addr,(6-i),'x');			
		}
	}
	return addr;
}

function onEnablingI2C(inst, ui)
{
	if(inst.enableI2CMode == true)
	{
		ui.ALERT_EN.hidden = true;
		ui.TargetAddressMask.hidden = true;
		ui.configTarget.hidden = true;
	}
	else
	{
		ui.ALERT_EN.hidden = false;
		ui.TargetAddressMask.hidden = false;
		ui.configTarget.hidden = true;
	}
	
}

function onChangeMode(inst, ui)
{
    if (inst.mode == "Controller") 
	{
		ui.configTarget.hidden = true;
		ui.ALERT_EN.hidden = true;
    }
    else 
	{
		ui.configTarget.hidden = false;
		ui.ALERT_EN.hidden = false;
    }
}

function setupBusClock()
{
    let busClockOptions = [
        { name: "PMBUS_CLOCKMODE_STANDARD", displayName : "100 KHz Clock" }
    ];
    if(hide_pmbus_fast_options == false)
    {
        busClockOptions.push(
            { name: "PMBUS_CLOCKMODE_FAST", displayName : "400 KHz Clock"  }
        );
    }
    if(hide_pmbus_fast_plus_options == false)
    {
        busClockOptions.push(
            { name: "PMBUS_CLOCKMODE_FAST_PLUS", displayName : "1 MHz Clock"  },
        );

    }
    return busClockOptions;
}

function onValidate(inst, validation) 
{ 
    var baudRateLow, baudRateHigh, modeLabel;
    if(inst.busClock != "PMBUS_CLOCKMODE_FAST_PLUS") 
    {
        baudRateLow = (Common.SYSCLK_getMaxMHz() * 1000000) / 32;
        baudRateHigh = 10 * 1000000;

        if(inst.busClock == "PMBUS_CLOCKMODE_STANDARD")
        {
            modeLabel = "Standard Mode";
        }
        else 
        {
            modeLabel = "Fast Mode";
        }
    }
    else // inst.busClock == "PMBUS_CLOCKMODE_FAST_PLUS" 
    {
       baudRateLow = 20 * 1000000;
       baudRateHigh = 25 * 1000000; 
       modeLabel = "Fast Plus Mode";
       validation.logInfo("Pinmux options are limited to GPIO supporting high speed mode", inst, "busClock");
    }
	if (inst.BaudRate < baudRateLow || inst.BaudRate > baudRateHigh)
    {
        validation.logError(
            `Enter an integer for Baud Rate between ${baudRateLow} and ${baudRateHigh} for ${modeLabel}!`, 
            inst, "BaudRate");
    }
	if (inst.OwnAddress < 0 || inst.OwnAddress > 0x7F)
    {
        validation.logError(
            "Enter an integer for OwnAddress between 0x0 and 0x7F!", 
            inst, "OwnAddress");
    }
  	if (inst.TargetAddress < 0 || inst.TargetAddress > 0x7F)
    {
        validation.logError(
            "Enter an integer for TargetAddress between 0x0 and 0x7F!", 
            inst, "TargetAddress");
    }
	if (inst.TargetAddressMask < 0 || inst.TargetAddressMask > 0x7F)
    {
        validation.logError(
            "Enter an integer for TargetAddressMask between 0x0 and 0x7F!", 
            inst, "TargetAddressMask");
    }
	if (inst.TargetAddress == inst.OwnAddress)
	{
        validation.logWarning(
            "OwnAddress and TargetAddress cannot be the same!", 
            inst, "OwnAddress");
    }
	if (Reserved_addresses.indexOf(inst.TargetAddress) !== -1)  
	{
		
		validation.logWarning(
            "The address specified is a reserved address", 
            inst, "TargetAddress");
	}
	if (Reserved_addresses.indexOf(inst.OwnAddress) !== -1)  
	{
		
		validation.logWarning(
            "The address specified is a reserved address", 
            inst, "OwnAddress");
	}
    var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("PMBUS", inst)
    for (var pinmuxQualMod of pinmuxQualMods)
    {
        if ((!inst[pinmuxQualMod.name].padConfig.includes("OD")) || (inst[pinmuxQualMod.name].padConfig.includes("INVERT")))
        {
            validation.logError("The push-pull and inverted pad configurations should not be used for the PMBus module.", inst);
        }
    }
}

/* Array of PMBus configurables that are common across device families */
let config = [
   	{
            name        : "BaudRate",
            displayName : "FSM Clock in Hz",
            description : 'desired baud rate' ,
            hidden      : false,
            default     : 10000000,
    },
	{
        name        : "mode",
        displayName : "PMBus Device Mode",
        description : 'PMBus device mode: Controller/Target',
        hidden      : false,
		onChange	: onChangeMode,
        default     : 'Controller',
        options     : [
            { name: "Controller", displayName : "Controller Mode" },
            { name: "Target", displayName : "Target Mode"  },
        ]
    },
	{
        name        : "OwnAddress",
        displayName : "Own Address",
        description : 'The address of the controller',
        hidden      : false,
        displayFormat: "hex",
        default     : 0x1A
    },
	{
        name        : "TargetAddress",
        displayName : "Target Address",
        description : 'The address of the target',
        hidden      : false,
        displayFormat: "hex",
        default     : 0x6A
    },
    {
        name        : "TargetAddressMask",
        displayName : "Target Address Mask",
        description : 'Used in address detection',
        hidden      : false,
        displayFormat: "hex",
        default     : 0x7F
    },
    {
        name        : "maskedAddress",
        displayName : "Masked Address",
        description : 'Used in address detection, the mask enables acknowledgement of multiple device addresses',
        hidden      : false,
        getValue    : calcAddress,
		default     : "0x000000"
    },
    {
		name        : "configTarget",
        displayName : "Target configurations",
        description : 'PMBSC Commands for configuring Target',	
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : [
            {name: "PMBUS_TARGET_ENABLE_MANUAL_ACK", legacyNames: ["PMBUS_SLAVE_ENABLE_MANUAL_ACK"], displayName : "Enable manual target ack mode"},
            {name: "PMBUS_TARGET_ENABLE_PEC_PROCESSING", legacyNames: ["PMBUS_SLAVE_ENABLE_PEC_PROCESSING"], displayName : "Enable PEC byte processing"},
            {name: "PMBUS_TARGET_TRANSMIT_PEC", legacyNames: ["PMBUS_SLAVE_TRANSMIT_PEC"], displayName : "Transmit PEC at end of transaction"},
            {name: "PMBUS_TARGET_ENABLE_MANUAL_CMD_ACK", legacyNames: ["PMBUS_SLAVE_ENABLE_MANUAL_CMD_ACK"], displayName : "issue ACK to continue message"},
            {name: "PMBUS_TARGET_DISABLE_ADDRESS_MASK", legacyNames: ["PMBUS_SLAVE_DISABLE_ADDRESS_MASK"], displayName : "Disable target address mask"},
            {name: "PMBUS_TARGET_AUTO_ACK_1_BYTES", legacyNames: ["PMBUS_SLAVE_AUTO_ACK_1_BYTES"], displayName : "Target will auto acknowledge every received byte"},
            {name: "PMBUS_TARGET_AUTO_ACK_2_BYTES", legacyNames: ["PMBUS_SLAVE_AUTO_ACK_2_BYTES"], displayName : "Target will auto acknowledge every 2 received bytes"},
			{name: "PMBUS_TARGET_AUTO_ACK_3_BYTES", legacyNames: ["PMBUS_SLAVE_AUTO_ACK_3_BYTES"], displayName : "Target will auto acknowledge every 3 received bytes"},
            {name: "PMBUS_TARGET_AUTO_ACK_4_BYTES", legacyNames: ["PMBUS_SLAVE_AUTO_ACK_4_BYTES"], displayName : "Target will auto acknowledge every 4 received bytes"},

        ],
        
    },
	{
		name        : "configController",
        displayName : "Controller Mode configurations",
        description : 'PMBMC Commands for configuring Controller',	
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : [
            {name: "PMBUS_CONTROLLER_ENABLE_PRC_CALL", legacyNames: ["PMBUS_MASTER_ENABLE_PRC_CALL"], displayName : "Enable Process call message"},
            {name: "PMBUS_CONTROLLER_ENABLE_GRP_CMD", legacyNames: ["PMBUS_MASTER_ENABLE_GRP_CMD"], displayName : "Enable Group command message"},
            {name: "PMBUS_CONTROLLER_ENABLE_PEC", legacyNames: ["PMBUS_MASTER_ENABLE_PEC"], displayName : "Enable PEC byte"},
            {name: "PMBUS_CONTROLLER_ENABLE_EXT_CMD", legacyNames: ["PMBUS_MASTER_ENABLE_EXT_CMD"], displayName : "Enable Extended command"},
            {name: "PMBUS_CONTROLLER_ENABLE_CMD", legacyNames: ["PMBUS_MASTER_ENABLE_CMD"], displayName : "Enable Command word"},
            {name: "PMBUS_CONTROLLER_ENABLE_READ", legacyNames: ["PMBUS_MASTER_ENABLE_READ"], displayName : "Enable read"},
          
        ],
    },
	{
        name        : "byteCount",
        displayName : "Number of bytes to be transmitted or read by the Controller",
        description : 'number of bytes transmitted (or read) in the message (up to 255)',
        hidden      : true,
        displayFormat: "hex",
        default     : 0x0
    },
	{
        name        : "ALERT_EN",
        displayName : "Alert the controller by asserting the ALERT line",
        description : 'A target PMBus can alert the controller by pulling the alert line low',
        hidden      : false,
        default     : false
    },
	{
        name        : "enableI2CMode",
        displayName : "Enable I2C mode",
        description : 'Set the PMBus module to work in I2C mode',
        hidden      : false,
		onChange	: onEnablingI2C,
        default     : false
    },
	{
        name: "enablePMBus",
        displayName : "Enable PMBus",
        description : 'Enable the PMBus module',
        hidden      : true,
        default     : true
    },
	{
	    name        : "useInterrupts",
        displayName : "Use Interrupt",
        description : 'Whether or not to use Interrupt mode.',
        hidden      : false,
        onChange    : onChangeUseInterrupts,
        default     : false
        
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
        options     : [
            {name: "PMBUS_INT_BUS_FREE", displayName : "Bus Free Interrupt"},
            {name: "PMBUS_INT_CLK_LOW_TIMEOUT", displayName : "Clock Low Time-out Interrupt"},
            {name: "PMBUS_INT_DATA_READY", displayName : "Data Ready Interrupt"},
            {name: "PMBUS_INT_DATA_REQUEST", displayName : "Data Request Interrupt"},
            {name: "PMBUS_INT_TARGET_ADDR_READY", legacyNames: ["PMBUS_INT_SLAVE_ADDR_READY"], displayName : "Target Address Ready Interrupt"},
            {name: "PMBUS_INT_EOM", displayName : "End of Message Interrupt"},
            {name: "PMBUS_INT_ALERT", displayName : "Alert Detection Interrupt"},
			{name: "PMBUS_INT_CONTROL", displayName : "Control Detection Interrupt"},
            {name: "PMBUS_INT_LOST_ARB", displayName : "Lost Arbitration Interrupt"},
			 {name: "PMBUS_INT_CLK_HIGH_DETECT", displayName : "Clock High Detection Interrupt"},
            {name: "PMBUS_INT_ALL", displayName : "all PMBus interrupts"},
        ],
        
    },
	{
        name: "useCase",
        displayName : "PinMux Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("PMBUS"),
        onChange    : Pinmux.useCaseChanged,
        
    },
    {
        name: "busClock",
        displayName : "PMBus Bus Clock (MHz)",
        description : 'Bus Clock Frequency',
        hidden      : false,
        default     : "PMBUS_CLOCKMODE_STANDARD",
        options     : setupBusClock() 
    },
	{
	    name        : "useZeroHoldSupport",
        displayName : "Use Zero Hold Time Support",
        description : 'Enable Zero hold support instead of standard 300 ns hold',
        hidden      : hide_pmbus_zero_hold_options,
        default     : false
    },
    {
        name        : "zeroHoldSupport",
        default     : pmbus_zero_hold_support,
        hidden      : true,
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
    return (Common.typeMatches(component.type, ["PMBUS"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var pmbusModule = {
    peripheralName: "PMBUS",
    displayName: "PMBUS",
    maxInstances: Common.peripheralCount("PMBUS"),
    defaultInstanceName: "myPMBUS",
    description: "PMBUS Peripheral",
    longDescription: (Common.getCollateralFindabilityList("PMBUS")),
    filterHardware : filterHardware,
    config: config,	
	moduleInstances: (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("PMBUS", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.args.padConfig = "OD_PULLUP";
            pinmuxQualMod.args.qualMode = "GPIO_QUAL_ASYNC";
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)

        if (inst.useInterrupts && inst.registerInterrupts)
        {
	        ownedInstances = ownedInstances.concat([{
                name: "PMBusInt",      
                displayName: "PMBus Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                        $name : inst.$name + "_INT",
                    int : "INT_" + inst.$name,
                    pinmuxPeripheralModule : "pmbus",
                    driverlibInt: "INT_#"
                }
            }])
        }
    	return ownedInstances;
    },
    templates: {
        boardc : "/driverlib/pmbus/pmbus.board.c.xdt",
        boardh : "/driverlib/pmbus/pmbus.board.h.xdt"
    },
	moduleStatic: {
        name: "PMBusGlobal",
        displayName: "PMBus Global",
        config: globalConfig,
    },
    pinmuxRequirements    : Pinmux.pmbusPinmuxRequirements,
    validate    : onValidate	
};


if (pmbusModule.maxInstances <= 0)
{
    delete pmbusModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(pmbusModule)
    Pinmux.addPinMuxQualGroupToConfig(pmbusModule)
}

exports = pmbusModule;
