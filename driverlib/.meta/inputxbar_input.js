let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let InputXbar_DevSpecific  = system.getScript("/driverlib/inputxbar/inputxbar_deviceSpecific.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_xbar.js");

/* Intro splash on GUI */
let longDescription = "The Input X-BAR is used to route signals from a GPIO to many different" +
                    " IP blocks such as the ADC(s), eCAP(s), ePWM(s), and external interrupts";

var inputXbarCount = 16
if (["F2837xD", "F2838xS", "F2807x"].includes(Common.getDeviceName()))
{
    inputXbarCount = 14
}


/* Array of Input X-bar configurables that are common across device families */
var config = [

];

var gpios = Common.getGPIOs();
var aios = Common.getAIOs();
var inputxbarGPIOOptions = InputXbar_DevSpecific.getExtraInputOptions();
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


var inputxbarSelectedSourceConfig = {
    name        : "inputxbarSelectedSource",
    displayName : "Selected Source Of GPIO",
    description : 'Selected GPIO is connected to this signal in the application',
    hidden      : false,
    default     : "",
    getValue    : (inst) => {
        let modNames = Object.keys(system.modules).sort();
        for (var modName of modNames)
        {
            var mod = system.modules[modName]
            var pinmuxRequirementsFunc = mod.pinmuxRequirements;
            if (pinmuxRequirementsFunc)
            {
                for (var modInstance of mod.$instances)
                {
                    var pinmuxRequirements = pinmuxRequirementsFunc(modInstance);
                    //console.log(pinmuxRequirements)
                    for (var pinmuxReq of pinmuxRequirements)
                    {
                        var pinmuxReqName = pinmuxReq.name;
                        //console.log(pinmuxReqName)
                        if (pinmuxReq.resources)
                        {
                            //
                            // Normal Peripheral Other than GPIO
                            //
                            var peripheralName = modInstance[pinmuxReqName].$solution.peripheralName
                            //console.log(peripheralName)
                            for (var pinmuxReqInterface of pinmuxReq.resources)
                            {
                                var pinmuxReqInterfaceName = pinmuxReqInterface.name
                                var devicePinName = modInstance[pinmuxReqName][pinmuxReqInterfaceName].$solution.devicePinName
                                var peripheralPinName = modInstance[pinmuxReqName][pinmuxReqInterfaceName].$solution.peripheralPinName
                                //console.log(peripheralPinName)
                                //console.log(devicePinName)

                                var gpioNames = Pinmux.getGPIOFromDevicePinName(devicePinName)
                                //console.log(gpioNames)

                                if (gpioNames.includes(inst.inputxbarGpio))
                                {
                                    //console.log("Found: " + modInstance.$name + " = " + peripheralPinName)
                                    return (modInstance.$name + " = " + peripheralPinName)
                                }
                            }
                        }
                        else
                        {
                            //
                            // GPIO
                            //
                            var peripheralName = modInstance[pinmuxReqName].$solution.peripheralName
                            var devicePinName = modInstance[pinmuxReqName].$solution.devicePinName
                            var peripheralPinName = modInstance[pinmuxReqName].$solution.peripheralPinName
                            //console.log(peripheralName)
                            //console.log(peripheralPinName)
                            //console.log(devicePinName)
                            if (devicePinName)
                            {
                                //
                                // Normal GPIO, single bonded AGPIO
                                //
                                var gpioNames = Pinmux.getGPIOFromDevicePinName(devicePinName)
                                //console.log(gpioNames)
                                if (gpioNames.includes(inst.inputxbarGpio))
                                {
                                    //console.log("Found: " + modInstance.$name + " = " + peripheralPinName)
                                    return (modInstance.$name + " = " + peripheralPinName)
                                }
                            }
                            else
                            {
                                //
                                // Double bonded AGPIO and AIOs
                                //
                                if (peripheralName == inst.inputxbarGpio)
                                {
                                    //console.log("Found: " + modInstance.$name + " = " + peripheralName)
                                    return (modInstance.$name + " = " + peripheralName)
                                }
                            }
                        }
                    }
                    //console.log(pinmuxRequirementsFunc(modInstance))
                }
            }
        }
        //console.log(system)
        return "This source is not used by any module"
    }
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
config.push(inputxbarSelectedSourceConfig);
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
    return (Common.typeMatches(component.type, ["INPUTXBAR"]));
}

if (Common.onlyPinmux())
{
    //config = [];
}
var inputxbarModule = {
    peripheralName: "INPUTXBAR",
    displayName: "INPUTXBAR INPUT",
    maxInstances: inputXbarCount,
    defaultInstanceName: "myINPUTXBARINPUT",
    description: "Input X-bar",
    filterHardware : filterHardware,
    config: config,
    validate  :  onValidate,
    templates: {
        boardc : "/driverlib/inputxbar/inputxbar_input.board.c.xdt",
        boardh : "/driverlib/inputxbar/inputxbar_input.board.h.xdt"
    },
    //pinmuxRequirements    : Pinmux.inputxbarPinmuxRequirements
};


if (inputxbarModule.maxInstances <= 0)
{
    delete inputxbarModule.pinmuxRequirements;
}


exports = inputxbarModule;
