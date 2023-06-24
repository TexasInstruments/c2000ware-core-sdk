let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = "ETHERNET";

/* Array of CAN configurables that are common across device families */
let config = [
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("ETHERNET"),
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
    return (Common.typeMatches(component.type, ["ETHERNET"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}
config = [config[config.length - 1]];

var ethernetModule = {
    peripheralName: "ETHERNET",
    displayName: "ETHERNET",
    maxInstances: Common.peripheralCount("ETHERNET"),
    defaultInstanceName: "myETHERNET",
    description: "ETHERNET Peripheral",
    filterHardware : filterHardware,
    moduleInstances: (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("ETHERNET", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.requiredArgs = {
               qualMode : "GPIO_QUAL_ASYNC",
            }
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)
    	return ownedInstances;
    },
    config: config,
    templates: {
        boardc : "/driverlib/ethernet/ethernet.board.c.xdt",
        boardh : "/driverlib/ethernet/ethernet.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.ethernetPinmuxRequirements
};


if (ethernetModule.maxInstances <= 0)
{
    delete ethernetModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(ethernetModule)
    Pinmux.addPinMuxQualGroupToConfig(ethernetModule)
}

exports = ethernetModule;