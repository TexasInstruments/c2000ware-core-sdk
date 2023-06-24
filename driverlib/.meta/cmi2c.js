let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = "CM-I2C";

/* Array of CAN configurables that are common across device families */
let config = [
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("CM-I2C"),
        onChange    : Pinmux.useCaseChanged,
        
    },
];

function onValidate(inst, validation) {
    var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("CM-I2C", inst)
    for (var pinmuxQualMod of pinmuxQualMods)
    {
        if ((inst[pinmuxQualMod.name].padConfig.includes("OD")) || (inst[pinmuxQualMod.name].padConfig.includes("INVERT")))
        {
            validation.logError("The open-drain and inverted pad configurations should not be used for the CM-I2C module.", inst);
        }
    }
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
    return (Common.typeMatches(component.type, ["CM-I2C"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}
config = [config[config.length - 1]];

var cmi2cModule = {
    peripheralName: "CM-I2C",
    displayName: "CM-I2C",
    maxInstances: Common.peripheralCount("CM-I2C"),
    defaultInstanceName: "myCMI2C",
    description: "CM-I2C Peripheral",
    filterHardware : filterHardware,
    moduleInstances : (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("CM-I2C", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.args.padConfig = "PULLUP";
            pinmuxQualMod.args.qualMode = "GPIO_QUAL_ASYNC";
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)
        return ownedInstances;
    },
    config: config,
    templates: {
        boardc : "/driverlib/cmi2c/cmi2c.board.c.xdt",
        boardh : "/driverlib/cmi2c/cmi2c.board.h.xdt"
    },
    validate: onValidate,
    pinmuxRequirements    : Pinmux.cmi2cPinmuxRequirements
};


if (cmi2cModule.maxInstances <= 0)
{
    delete cmi2cModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(cmi2cModule)
    Pinmux.addPinMuxQualGroupToConfig(cmi2cModule)
}

exports = cmi2cModule;