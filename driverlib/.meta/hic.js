let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = "HIC";

/* Array of CAN configurables that are common across device families */
let config = [
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("HIC"),
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
    return (Common.typeMatches(component.type, ["HIC"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var hicModule = {
    peripheralName: "HIC",
    displayName: "HIC",
    maxInstances: Common.peripheralCount("HIC"),
    defaultInstanceName: "myHIC",
    description: "HIC Peripheral",
    longDescription: (Common.getCollateralFindabilityList("HIC")),
    filterHardware : filterHardware,
    moduleInstances : (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("HIC", inst)
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
        boardc : "/driverlib/hic/hic.board.c.xdt",
        boardh : "/driverlib/hic/hic.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.hicPinmuxRequirements
};


if (hicModule.maxInstances <= 0)
{
    delete hicModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(hicModule)
    Pinmux.addPinMuxQualGroupToConfig(hicModule)
}

exports = hicModule;