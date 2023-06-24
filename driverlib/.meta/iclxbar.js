let Common   = system.getScript("/driverlib/Common.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_xbar.js");

/* Intro splash on GUI */
let longDescription = "The Illegal Combination Logic X-BAR is used to route signals from the CLB Outputs and Minimum Deadband sub-module to" +
                    " the Illegal Combination Logic sub-module";

var iclXbarCount = 16



/* Array of Input X-bar configurables that are common across device families */
var config = [

];

var inputSignalOptions = []
for (var inputSignal of device_driverlib_peripheral.XBAR_InputSignal)
{
    if (inputSignal.name.indexOf("XBAR_ICL_") != -1)
    {
        inputSignalOptions.push({
            name: inputSignal.name.replace("XBAR_ICL_","")
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

var iclxbarInstanceConfig = {
    name        : "iclxbarInstance",
    displayName : "Instance",
    description : 'The ICL X-Bar Instance',
    hidden      : false,
    default     : instanceNumOptions[0].name,
    options     : instanceNumOptions
}

var iclxbarInputConfig = {
    name        : "iclxbarInput",
    displayName : "Input Selection",
    description : 'Input Selection for this ICL X-Bar Instance',
    hidden      : false,
    default     : inputSignalOptions[0].name,
    options     : inputSignalOptions
}

var iclxbarLOCKConfig = {
    name        : "iclxbarLock",
    displayName : "INPUT Lock",
    description : 'Lock this ICL X-Bar',
    hidden      : false,
    default     : false
}

config.push(iclxbarInstanceConfig);
config.push(iclxbarInputConfig);
config.push(iclxbarLOCKConfig);

function onValidate(inst, validation)
{
    var usedInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedInsts.push(instance_obj.iclxbarInstance);
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
            inst, "iclxbarInstance");
    }
}

var iclxbarModule = {
    peripheralName: "ICLXBAR",
    displayName: "ICL XBAR",
    maxInstances: iclXbarCount,
    defaultInstanceName: "myICLXBARINPUT",
    description: "Illegal Combination Logic X-bar",
    config: config,
    validate  :  onValidate,
    templates: {
        boardc : "/driverlib/iclxbar/iclxbar.board.c.xdt",
        boardh : "/driverlib/iclxbar/iclxbar.board.h.xdt"
    },

};


exports = iclxbarModule;
