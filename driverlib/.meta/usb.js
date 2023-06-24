let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = "The USB controller operates as a full-speed function " +
"controller during point-to-point communications with the USB host. " +
"The controller complies with the USB 2.0 standard";

function onValidate(inst, validation)
{
  
}

/* Array of USB configurables that are common across device families */
let config = [
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'PinMux Use Case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("USB"),
        onChange    : Pinmux.useCaseChanged,
    },
    {
        name        : "registerInterrupts",
        displayName : "Register Interrupt Handler",
        description : 'Whether or not to register interrupt handlers in the interrupt module.',
        hidden      : false,
        default     : false
        
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
    return (Common.typeMatches(component.type, ["USB"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var usbModule = {
    peripheralName: "USB",
    displayName: "USB",
    maxInstances: Common.peripheralCount("USB"),
    defaultInstanceName: "myUSB",
    description: "Universal Serial Bus Peripheral",
    longDescription: (Common.getCollateralFindabilityList("USB")),
    filterHardware : filterHardware,
	moduleInstances: (inst) => 
	{
		let ownedInstances = []
		ownedInstances.push(		
	    {
	           name: "usbLib",      
	           displayName: "USB Library",
	           moduleName: "/libraries/communications/usb/usb.js",
	           collapsed: true,
	           args: {
					$name : inst.$name + "_LIB",
	           }
	    })
		if (inst.registerInterrupts)
		{
			ownedInstances.push( {
	           name: "USBInt",      
	           displayName: "USB Interrupt",
	           moduleName: "/driverlib/interrupt.js",
	           collapsed: true,
	           args: {
				   $name : inst.$name + "_INT",
	               int : "INT_" + inst.$name,
	               pinmuxPeripheralModule : "usb",
	               driverlibInt: "INT_USBA"
	           }
	       })
		}
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("USB", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.requiredArgs = {
               qualMode : "GPIO_QUAL_ASYNC",
               padConfig : "STD",
            }
        }
		ownedInstances = ownedInstances.concat(pinmuxQualMods)
		return ownedInstances;
		
	},
    config: config,
    templates: {
        boardc : "/driverlib/usb/usb.board.c.xdt",
        boardh : "/driverlib/usb/usb.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.usbPinmuxRequirements,
	validate : onValidate
};


if (usbModule.maxInstances <= 0)
{
    delete usbModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(usbModule)
    Pinmux.addPinMuxQualGroupToConfig(usbModule)
}


exports = usbModule;