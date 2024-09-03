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
    },

    {
        name        : "GROUP_XINT",
        displayName : "External Interrupts",
        description : 'Connect to an XINT for interrupts',
        config     : [
            {
                name        : "useInterrupt",
                displayName : "Use Interrupts",
                description : 'Connect to an XINT for interrupts',
                hidden      : false,
                default     : false
            },
        ]
    },
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

function moduleInstances(inst)
{
    var ownedMods = []

    if (inst.useInterrupt)
    {
        //GROUP_XINT
        ownedMods.push({
            name: "xint",      
            displayName: "XINT",
            moduleName: "/driverlib/xint.js",
            collapsed: true,
            group: "GROUP_XINT",
            requiredArgs: {
                $name : inst.$name + "_XINT",
            }
        })
    }
    return ownedMods
}

function onValidatePinmux(inst, validation) {
    if (inst.useInterrupt){
        var xint = inst.xint;
        var xintNum = xint.xintNum;
        var inputxbar = xint.inputxbar;

        if (inst.aioPin.$solution)
        {
            var selectedAIOPeripheral = inst.aioPin.$solution.peripheralPinName;
            if (!selectedAIOPeripheral)
            {
                selectedAIOPeripheral = inst.aioPin.$solution.peripheralName
            }
            if (selectedAIOPeripheral != inputxbar["inputxbarGpio"])
            {
                validation.logWarning(
                    "Select " + selectedAIOPeripheral + " which is the selection in your AIO PinMux entry.", 
                    inputxbar, "inputxbarGpio");
            }
        }
        else
        {
            validation.logInfo(
                "Select " + "the same AIO" + " as the one in your AIO PinMux entry.", 
                inputxbar, "inputxbarGpio");
        }
    }
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
    moduleInstances: moduleInstances,
    config: config,
    templates: {
        boardc : "/driverlib/aio/aio.board.c.xdt",
        boardh : "/driverlib/aio/aio.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.aioPinmuxRequirements,
    validatePinmux: onValidatePinmux
};

if (aioModule.maxInstances <= 0)
{
    delete aioModule.pinmuxRequirements;
}

exports = aioModule;