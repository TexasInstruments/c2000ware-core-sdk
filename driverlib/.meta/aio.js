let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_gpio.js");

/* Intro splash on GUI */
let longDescription = "A AIO peripheral is used to translate data between " +
    "the chip and a serial port. The SCI driver simplifies reading " +
    "and writing to any of the UART peripherals on the board, with " +
    "multiple modes of operation and performance. These include " +
    "blocking, non-blocking, and polling, as well as text/binary " +
    "mode, echo and return characters.";

/* Array of SCI configurables that are common across device families */
let config = [

    {
        name        : "direction",
        displayName : "AIO Direction",
        description : 'Only supports input.',
        hidden      : false,
        default     : 'IN',
        options     : [
            { name: "IN" }
        ]
    },
    
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
    }
];

if (!["F28002x", "F280013x", "F280015x"].includes(Common.getDeviceName()))
{
    var coreSelectConfig = {
        name        : "controllerCore",
        legacyNames : ["masterCore"],
        displayName : "Core Select",
        description : 'Who owns the GPIO.',
        hidden      : false,
        default     : device_driverlib_peripheral.GPIO_CoreSelect[0].name,
        options     : device_driverlib_peripheral.GPIO_CoreSelect
    };
    config.push(coreSelectConfig)
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
    return (Common.typeMatches(component.type, ["AIO"]));
}

if (Common.onlyPinmux())
{
    config = [];
}
var aioModule = {
    peripheralName: "AIO",
    displayName: "AIO",
    maxInstances: Common.peripheralCount("AIO"),
    defaultInstanceName: "myAIO",
    description: "Analog IO Interface Peripheral",
    filterHardware : filterHardware,
    config: config,
    templates: {
        boardc : "/driverlib/aio/aio.board.c.xdt",
        boardh : "/driverlib/aio/aio.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.aioPinmuxRequirements
};

if (aioModule.maxInstances <= 0)
{
    delete aioModule.pinmuxRequirements;
}

exports = aioModule;