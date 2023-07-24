let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let PinmuxAdditionalUseCases   = system.getScript("/driverlib/pinmux/pinmux_additionalUseCases.js");

/* Intro splash on GUI */
let longDescription = "ECAT";

/* Array of CAN configurables that are common across device families */
let config = [
    {
        // 
        // This is needed for locking some options when a HARDWARE is needed
        // Currently we only have EVM connection for ECAT on LaunchPads
        // and controlCARDs
        //
        name: "$hardware",
        onChange: (inst, ui) => {
            if (inst.$hardware)
            {
                var useCaseNames = Pinmux.getPeripheralUseCaseNames("ECAT").map((useCaseOpt) => {
                    return useCaseOpt.name
                    }
                );
                
                useCaseNames = useCaseNames.concat(PinmuxAdditionalUseCases.getAdditionalUseCaseNames("ECAT"));
                if (useCaseNames.includes("EVM"))
                {
                    inst.useCase = "EVM"
                }
            }
        }
    },
];

var useCaseConfig = {
    name: "useCase",
    displayName : "Use Case",
    description : 'Peripheral use case',
    hidden      : false,
    default     : 'ALL',
    options     : Pinmux.getPeripheralUseCaseNames("ECAT"),
    onChange    : Pinmux.useCaseChanged,
}

useCaseConfig.options = useCaseConfig.options.concat(Pinmux.getAdditionalUseCaseNameConfigsNotInDeviceData("ECAT"))
config.push(
    useCaseConfig
)

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
    return (Common.typeMatches(component.type, ["ECAT"]));
}

// if (Common.onlyPinmux())
// {
//     config = [config[config.length - 1]];
// }
// config = [config[config.length - 1]];

var ecatModule = {
    peripheralName: "ECAT",
    displayName: "ECAT",
    maxInstances: Common.peripheralCount("ECAT"),
    defaultInstanceName: "myECAT",
    description: "ECAT Peripheral",
    longDescription: (Common.getCollateralFindabilityList("ECAT")),
    filterHardware : filterHardware,
    moduleInstances : (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("ECAT", inst)
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
        boardc : "/driverlib/ecat/ecat.board.c.xdt",
        boardh : "/driverlib/ecat/ecat.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.ecatPinmuxRequirements
};


if (ecatModule.maxInstances <= 0)
{
    delete ecatModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(ecatModule)
    Pinmux.addPinMuxQualGroupToConfig(ecatModule)
}

exports = ecatModule;