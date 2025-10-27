let Common   = system.getScript("/driverlib/Common.js");

function onValidate(inst, validation)
{
    if (Common.isContextCPU1() && !Common.isModuleOnThisContext("/driverlib/device_support.js"))
    {
        validation.logWarning("Add the 'Device Support' module in order to use Clock Tree tool and generate device support files. This suggestion can be ignored if not using the Clock Tree tool.", inst, inst.displayName);
    }
}


exports = {
    displayName: "Clock Tree",
    moduleStatic: {
        config: [
            {
                name: "clocktree",
                displayName: "Clock Tree Tool",
                default: true,
                nonSerializable: false
            },
        ],
        validate: onValidate,
    }
};

