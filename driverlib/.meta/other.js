let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = "An FSI peripheral is used to translate data between " +
    "the chip and a serial port. The SCI driver simplifies reading " +
    "and writing to any of the UART peripherals on the board, with " +
    "multiple modes of operation and performance. These include " +
    "blocking, non-blocking, and polling, as well as text/binary " +
    "mode, echo and return characters.";

/* Array of CAN configurables that are common across device families */
let config = [
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("OTHER"),
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
    return (Common.typeMatches(component.type, ["OTHER"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var otherModule = {
    peripheralName: "OTHER",
    displayName: "OTHER",
    maxInstances: Common.peripheralCount("OTHER"),
    defaultInstanceName: "myOTHER",
    description: "Other Peripheral",
    filterHardware : filterHardware,
    config: config,
    templates: {
        boardc : "/driverlib/other/other.board.c.xdt",
        boardh : "/driverlib/other/other.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.otherPinmuxRequirements
};


if (otherModule.maxInstances <= 0)
{
    delete otherModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(otherModule)
}

exports = otherModule;