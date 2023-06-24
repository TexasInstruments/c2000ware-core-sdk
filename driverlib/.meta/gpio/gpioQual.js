let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_gpio.js");


/* Intro splash on GUI */
let longDescription = "The GPIO QUAL module allows you to setup your qualification settings";

let config = [
    {
        name        : "padConfig",
        displayName : "Pin Type",
        description : 'Type of pin is driving the gpio.',
        hidden      : false,
        default     : 'STD',
        options     : [
            { name: "STD", displayName : "Push-pull output/floating input" },
            { name: "PULLUP", displayName : "Push-pull output/pull-up enabled on input"  },
            { name: "INVERT", displayName : "Push-pull output/floating INVERTED polarity on an input"  },
            { name: "PULLUP_INVERT", displayName : "Push-pull output/pull-up enabled on INVERTED input"  },
            { name: "OD", displayName : "Open-drain output/floating input" },
            { name: "OD_PULLUP", displayName : "Open-drain output with pull-up enabled output and input" },
            { name: "OD_INVERT", displayName : "Open-drain output/floating inverted input" },
            { name: "OD_PULLUP_INVERT", displayName : "Open-drain output with pull-up enabled output and INVERTED input" }
        ]
    },
    {
        name        : "qualMode",
        displayName : "Qualification Mode",
        description : 'The type of qualification done on the pin.',
        hidden      : false,
        default     : device_driverlib_peripheral.GPIO_QualificationMode[0].name,
        options     : device_driverlib_peripheral.GPIO_QualificationMode
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
    return (Common.typeMatches(component.type, ["GPIOQUAL"]));
}

function onValidate(inst, validation)
{
    
}

function onValidatePinmux(inst, validation) {

}

var gpioQualModule = {
    displayName: "GPIO Qualification",
    defaultInstanceName: "myGPIOQUAL",
    description: "General Purpose IO Qualification and Pad Settings",
    filterHardware : filterHardware,
    validate: onValidate,
    config: config,
    templates: {
        boardc : "",
        boardh : ""
    },
    validatePinmux: onValidatePinmux
};



exports = gpioQualModule;