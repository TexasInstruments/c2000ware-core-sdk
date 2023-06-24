let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = "Analog PinMux configuration";

/* Array of CAN configurables that are common across device families */
let config = [
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("ANALOG"),
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
    return (Common.typeMatches(component.type, ["ANALOG"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var analogModule = {
    peripheralName: "ANALOG",
    displayName: "ANALOG PinMux",
    maxInstances: Common.peripheralCount("ANALOG"),
    defaultInstanceName: "myANALOGPinMux",
    description: "Analog Configuration",
    filterHardware : filterHardware,
    config: config,
    templates: {
        boardc : "/driverlib/analog/analog.board.c.xdt",
        boardh : "/driverlib/analog/analog.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.analogPinmuxRequirements
};


if (analogModule.maxInstances <= 0)
{
    delete analogModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(analogModule)
}

exports = analogModule;