let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_xbar.js");

/* Intro splash on GUI */
let longDescription = "The CLB Input X-BAR is used to route signals from a GPIO to many different" +
                    " IP blocks such as the ADC(s), eCAP(s), ePWM(s), and external interrupts";


function onChangeInputsUsed(inst, ui)
{
    var usedInputs = inst.inputsUsed;
    for (var uiInputXbarNameIndex in uiInputXbarNames)
    {
        var uiName = uiInputXbarNames[uiInputXbarNameIndex];
        //console.log(uiName);
        ui[uiName].hidden = true;

        uiName = uiInputXbarLockNames[uiInputXbarNameIndex];
        //console.log(uiName);
        ui[uiName].hidden = true;
    }
    for (var usedInputIndex in usedInputs)
    {
        var usedInput = usedInputs[usedInputIndex];
        for (uiInputXbarNameIndex in uiInputXbarNames)
        {
            var uiName = uiInputXbarNames[uiInputXbarNameIndex];
            //console.log("ui Name:" + uiName)
            //console.log("used input name:" + usedInput)
            if (usedInput == uiName)
            {
                //console.log("Name match")
                //console.log(uiName);
                ui[uiName].hidden = false;

                uiName = uiInputXbarLockNames[uiInputXbarNameIndex];
                //console.log(uiName);
                ui[uiName].hidden = false;
            }
        }
    }
}

/* Array of Input X-bar configurables that are common across device families */
var config = [
/*
    {
        name        : "bitRate",
        displayName : "Bit Rate",
        description : 'Bit rate for device',
        hidden      : false,
        default     : '400'
    }
*/
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


var interfaceNames = []
var uiInputXbarNames = []
var uiInputXbarLockNames = []
for (var clb_inputxbar_index = 1; clb_inputxbar_index <= 16; clb_inputxbar_index++)
{
    

    var uiInputXbarName = "CLB_INPUTXBAR" + clb_inputxbar_index.toString() + "Gpio"
    var uiInputXbarLockName = "CLB_INPUTXBAR" + clb_inputxbar_index.toString() + "Lock"

    uiInputXbarNames.push(uiInputXbarName)
    uiInputXbarLockNames.push(uiInputXbarLockName)


    interfaceNames.push({name: uiInputXbarName, displayName: "CLB_INPUTXBAR" + clb_inputxbar_index.toString()})

    var inputxbarGPIOConfig = {
        name        : uiInputXbarName,
        displayName : "CLB_INPUTXBAR" + clb_inputxbar_index.toString(),
        description : 'GPIO for this Input X-Bar',
        hidden      : true,
        default     : inputxbarGPIOOptions[0].name,
        options     : inputxbarGPIOOptions,
        deprecated  : true,
    }

    var inputxbarLOCKConfig = {
        name        : uiInputXbarLockName,
        displayName : "CLB_INPUTXBAR" + clb_inputxbar_index.toString() + " Lock",
        description : 'Lock this Input X-Bar',
        hidden      : true,
        default     : false,
        deprecated  : true,
    }

    config.push(inputxbarGPIOConfig);
    config.push(inputxbarLOCKConfig);
}

config.unshift(
{
    name        : "inputsUsed",
    displayName : "INPUTs to be used",
    description : 'Which inputs to use from the CLB INPUT X-BAR.',
    hidden      : false,
    default     : [],
    minSelections: 0,
    //onChange    : onChangeInputsUsed,
    options     :  interfaceNames,
    deprecated  : true,
    
})



var clb_inputxbarModule = {
    displayName: "CLB INPUTXBAR",
    maxInstances: 1,
    defaultInstanceName: "myCLBINPUTXBAR",
    description: "CLB Input X-bar",
    config: config,
    templates: {
        boardc : "",
        boardh : ""
    },
    migrateLegacyConfiguration : (inst) => {
        for (var input of inst.inputsUsed)
        {
            var inputxbar_input_inst = scripting.addModule("/driverlib/clb_inputxbar_input.js").addInstance();
            var inputNum = input.replace("Gpio", "").replace("CLB_INPUTXBAR", "")
            var inputLock = inst["CLB_INPUTXBAR" + inputNum + "Lock"] 
            var inputSource = inst[input]
            inputxbar_input_inst.inputxbarInput = "XBAR_INPUT" + inputNum;
            inputxbar_input_inst.inputxbarGpio = inputSource;
            inputxbar_input_inst.inputxbarLock = inputLock;
        }
    },
    //pinmuxRequirements    : Pinmux.inputxbarPinmuxRequirements
};


if (clb_inputxbarModule.maxInstances <= 0)
{
    delete clb_inputxbarModule.pinmuxRequirements;
}


exports = clb_inputxbarModule;