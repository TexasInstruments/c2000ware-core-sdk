let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let InputXbar_DevSpecific  = system.getScript("/driverlib/inputxbar/inputxbar_deviceSpecific.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_xbar.js");


/* Intro splash on GUI */
let longDescription = "The CLB Input X-BAR is used to route signals from a GPIO to many different" +
                    " IP blocks such as the ADC(s), eCAP(s), ePWM(s), and external interrupts";

var inputXbarCount = 16


/* Array of Input X-bar configurables that are common across device families */
var config = [

];

var gpios = Common.getGPIOs();
var aios = Common.getAIOs();
var inputxbarGPIOOptions = [];
for (var gpioIndex = 0; gpioIndex < gpios.length; gpioIndex++)
{
    inputxbarGPIOOptions.push({name: gpios[gpioIndex]});
}
for (var aioIndex = 0; aioIndex < aios.length; aioIndex++)
{
    inputxbarGPIOOptions.push({name: aios[aioIndex]});
}

var inputNumOptions = []
for (var inputNum of device_driverlib_peripheral.XBAR_InputNum)
{
    inputNumOptions.push({
        name: inputNum.name
    })
}

var inputxbarINPUTConfig = {
    name        : "inputxbarInput",
    displayName : "INPUT",
    description : 'The INPUT number for Input X-Bar',
    hidden      : false,
    default     : inputNumOptions[0].name,
    options     : inputNumOptions
}

var inputxbarGPIOConfig = {
    name        : "inputxbarGpio",
    displayName : "INPUT Source",
    description : 'GPIO for this Input X-Bar',
    hidden      : false,
    default     : inputxbarGPIOOptions[0].name,
    options     : inputxbarGPIOOptions
}

var inputxbarLOCKConfig = {
    name        : "inputxbarLock",
    displayName : "INPUT Lock",
    description : 'Lock this Input X-Bar',
    hidden      : false,
    default     : false
}

config.push(inputxbarINPUTConfig);
config.push(inputxbarGPIOConfig);
config.push(inputxbarLOCKConfig);

 
function onValidate(inst, validation)
{
    var usedInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedInsts.push(instance_obj.inputxbarInput);
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
            inst, "inputxbarInput");
    }
}

var clb_inputxbarModule = {
    peripheralName: "CLB_INPUTXBAR",
    displayName: "CLB INPUTXBAR INPUT",
    maxInstances: inputXbarCount,
    defaultInstanceName: "myCLBINPUTXBARINPUT",
    description: "CLB Input X-bar",
    config: config,
    templates: {
        boardc : "/driverlib/clb_inputxbar/clb_inputxbar_input.board.c.xdt",
        boardh : "/driverlib/clb_inputxbar/clb_inputxbar_input.board.h.xdt"
    },
    validate  :  onValidate,
    
};


if (clb_inputxbarModule.maxInstances <= 0)
{
    delete clb_inputxbarModule.pinmuxRequirements;
}


exports = clb_inputxbarModule;