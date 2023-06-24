let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = `
**NOTE:** The procedure to enable the internal DC-DC regulator should be completed 
prior to other initialization functions. This is in order for the DC-DC 
initialization to happen during low current operation. \x22DC_DC_init()\x22 
should be called before initialization functions like  \x22Device_init()\x22 or 
\x22Device_enableAllPeripherals()\x22.

**Adding this module does not place \x22DC_DC_init()\x22 in your software, is it left to 
the user to configure this in the main code.**
`;
/* Array of DC-DC configurables that are common across device families */
let config = [
    {
        name        : "enableDCDC",
        displayName : "Enable DC-DC",
        description : 'Whether or not to enable DC-DC.',
        hidden      : false,
        default     : false
    },
    {
        name        : "lockDCDC",
        displayName : "Lock DC-DC Control Register",
        description : 'Whether or not to lock the DC-DC control register.',
        hidden      : false,
        default     : false
    },
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("DC-DC"),
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
    return (Common.typeMatches(component.type, ["DC-DC"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}


var dcdcModule = {
    peripheralName: "DC-DC",
    displayName: "DC-DC",
    maxInstances: Common.peripheralCount("DC-DC"),
    defaultInstanceName: "myDCDC",
    description: "DC-DC Peripheral",
    longDescription: longDescription,
    filterHardware : filterHardware,
    config: config,
    templates: {
        boardc : "/driverlib/dcdc/dcdc.board.c.xdt",
        boardh : "/driverlib/dcdc/dcdc.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.dcdcPinmuxRequirements
};


if (dcdcModule.maxInstances <= 0)
{
    delete dcdcModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(dcdcModule)
}

exports = dcdcModule;