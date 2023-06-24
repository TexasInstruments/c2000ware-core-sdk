let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = "SSI";

/* Array of CAN configurables that are common across device families */
let config = [
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("SSI"),
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
    return (Common.typeMatches(component.type, ["SSI"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var ssiModule = {
    peripheralName: "SSI",
    displayName: "SSI",
    maxInstances: Common.peripheralCount("SSI"),
    defaultInstanceName: "mySSI",
    description: "SSI Peripheral",
    filterHardware : filterHardware,
    moduleInstances: (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("SSI", inst)
        ownedInstances = ownedInstances.concat(pinmuxQualMods)
    	return ownedInstances;
    },
    config: config,
    templates: {
        boardc : "/driverlib/ssi/ssi.board.c.xdt",
        boardh : "/driverlib/ssi/ssi.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.ssiPinmuxRequirements
};


if (ssiModule.maxInstances <= 0)
{
    delete ssiModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(ssiModule)
    Pinmux.addPinMuxQualGroupToConfig(ssiModule)
}

exports = ssiModule;