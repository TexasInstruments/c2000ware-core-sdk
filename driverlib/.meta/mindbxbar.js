let Common   = system.getScript("/driverlib/Common.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_xbar.js");

/* Intro splash on GUI */
let longDescription = "The Minimum Dead-band X-BAR is used to route signals from the CLB Outputs and EPWM module to" +
                    " the Minimum Dead-band sub-module";

var mindbXbarCount = 16



/* Array of Input X-bar configurables that are common across device families */
var config = [

];

var inputSignalOptions = []
for (var inputSignal of device_driverlib_peripheral.XBAR_InputSignal)
{
    if (inputSignal.name.indexOf("XBAR_MINDB_") != -1)
    {
        inputSignalOptions.push({
            name: inputSignal.name.replace("XBAR_MINDB_","")
        })
    }
}

var instanceNumOptions = []
for (var instanceNum of device_driverlib_peripheral.XBAR_InputNum)
{
    instanceNumOptions.push({
        name: instanceNum.name
    })
}

var mindbxbarInstanceConfig = {
    name        : "mindbxbarInstance",
    displayName : "Instance",
    description : 'The MINDB X-Bar Instance',
    hidden      : false,
    default     : instanceNumOptions[0].name,
    options     : instanceNumOptions
}

var mindbxbarInputConfig = {
    name        : "mindbxbarInput",
    displayName : "Input Selection",
    description : 'Input Selection for this MINDB X-Bar Instance',
    hidden      : false,
    default     : inputSignalOptions[0].name,
    options     : inputSignalOptions
}

var mindbxbarLOCKConfig = {
    name        : "mindbxbarLock",
    displayName : "INPUT Lock",
    description : 'Lock this MINDB X-Bar',
    hidden      : false,
    default     : false
}

config.push(mindbxbarInstanceConfig);
config.push(mindbxbarInputConfig);
config.push(mindbxbarLOCKConfig);

function onValidate(inst, validation)
{
    var usedInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedInsts.push(instance_obj.mindbxbarInstance);
    }
    
    var duplicatesResult = Common.findDuplicates(usedInsts)
    
    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "This instance is already in use! Duplicates: " + allDuplicates,
            inst, "mindbxbarInstance");
    }
}

var mindbxbarModule = {
    peripheralName: "MINDBXBAR",
    displayName: "MINDB XBAR",
    maxInstances: mindbXbarCount,
    defaultInstanceName: "myMINDBXBARINPUT",
    description: "Minimum Dead-band X-bar",
    config: config,
    validate  :  onValidate,
    templates: {
        boardc : "/driverlib/mindbxbar/mindbxbar.board.c.xdt",
        boardh : "/driverlib/mindbxbar/mindbxbar.board.h.xdt"
    },

};


exports = mindbxbarModule;
