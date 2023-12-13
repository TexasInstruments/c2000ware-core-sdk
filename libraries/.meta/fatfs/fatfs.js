let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let config = [
    {
        name: "driveNumber",
        displayName: "Drive Number",
        default: 0,
    },
]

function onValidate(inst, validation) {
    var acceptableDriveNumbers = [0,1,2,3]
    if (acceptableDriveNumbers.indexOf(inst.driveNumber) == -1)
    {
        validation.logError(
            "The drive number must be one of the following values: " + acceptableDriveNumbers.toString(), 
            inst, "driveNumber");
    }
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        if ((inst != instance_obj) && (inst.driveNumber == instance_obj.driveNumber)) {
            validation.logError(
                "The drive number must be unique across all SD FATFS modules.", 
                inst, "driveNumber");
        }
    }

}

function moduleInstances(inst)
{
    
    var csInstance;
    csInstance = {
        displayName: "CS GPIO",
        name: "csgpio",
        description: "The GPIO module driving the CHIP SELECT line",
        moduleName: "/driverlib/gpio.js",
        args: {
            $name: inst.$name + "_CS_GPIO"
        },
        requiredArgs: {
            direction : "GPIO_DIR_MODE_OUT",
            writeInitialValue :true,
            initialValue      :1,
            direction         :"GPIO_DIR_MODE_OUT",
        }
    };

    return ([csInstance]);
}

function sharedModuleInstances (inst)
{
    
    var spiInstance;
    spiInstance = {
        displayName: "SPI",
        name: "spi",
        description: "The SPI module driving the PICO/COPI",
        moduleName: "/driverlib/spi.js",
        // args: {
        //     $name: inst.$name + "_SPI",
        //     bitRate          : 1000000,
        //     emulationMode    : "SPI_EMULATION_STOP_AFTER_TRANSMIT",
        // },
        requiredArgs: {
            useInterrupts    : false,
            mode             : "SPI_MODE_CONTROLLER",
            dataWidth        : "8",
            transferProtocol : "SPI_PROT_POL0PHA1",
        }
    };

    return [spiInstance]
}



var fatfsModule = {
    c2000wareLibraryName: "FATFS",
    displayName: "SDCARD FATFS",
    defaultInstanceName: "myFATFS",
    description: "SD Card FATFS",
    moduleInstances: moduleInstances,
    sharedModuleInstances: sharedModuleInstances,
    config: config,
    templates: {
        c2000ware_libraries_h           : "/libraries/fatfs/templates/fatfs.c2000ware_libraries.h.xdt",
        c2000ware_libraries_c           : "/libraries/fatfs/templates/fatfs.c2000ware_libraries.c.xdt",
        c2000ware_libraries_opt         : "/libraries/fatfs/templates/fatfs.c2000ware_libraries.opt.xdt",
        c2000ware_libraries_cmd_genlibs : "/libraries/fatfs/templates/fatfs.c2000ware_libraries.cmd.genlibs.xdt",
    },
    validate    : onValidate,
};




exports = fatfsModule;