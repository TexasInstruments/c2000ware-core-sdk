let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_xbar.js");

/* Intro splash on GUI */
let longDescription = "The CLB X-BAR takes signals from inside " + 
                        "the device and brings them to the CLB AUXSIGx inputs.";

function findDuplicates(arrayToCheck)
{
    const count = arrayToCheck =>
      arrayToCheck.reduce((a, b) => ({ ...a,
        [b]: (a[b] || 0) + 1
      }), {}) // don't forget to initialize the accumulator

    const duplicates = dict =>
      Object.keys(dict).filter((a) => dict[a] > 1)

    //console.log(count(arrayToCheck)) // { Mike: 1, Matt: 1, Nancy: 2, Adam: 1, Jenny: 1, Carl: 1 }
    //console.log(duplicates(count(arrayToCheck)))

    return {count: count(arrayToCheck), duplicates: duplicates(count(arrayToCheck))};
}

function onChangeauxInput(inst, ui)
{
    //console.log(inst.$module.$instances);
    
}

function onValidate(inst, validation) {

    var usedAuxs = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedAuxs.push(instance_obj.auxInput);
    }

    var duplicatesResult = findDuplicates(usedAuxs)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The AUXSIG Inputs cannot be same for multiple modules. Duplicates: " + allDuplicates, 
            inst, "auxInput");
    }
    
    var optionNamePrepend = "XBAR_MUX"
    if (inst["useSourceSelect"])
    {
        var muxes = []
        for (var sourceSignal of inst.sourceSignals)
        {
            var mux = muxOptionToMuxNumber[sourceSignal]
            if (muxes.includes(optionNamePrepend + mux)){
                validation.logError(
                    "There are multiple signals selected for MUX" + mux + ". Only one is allowed at a time per MUX. Signal: " + sourceSignal, 
                    inst, "sourceSignals");
            }
            else {
                muxes.push(optionNamePrepend + mux)
            }
        }
    }
}

function onChangeMuxesUsed(inst, ui)
{
    var optionNamePrepend = "XBAR_MUX"
    var muxSource = {}
    ui["sourceSignals"].hidden = !inst["useSourceSelect"]
    if (inst["useSourceSelect"])
    {
        var muxes = []
        for (var sourceSignal of inst.sourceSignals)
        {
            var mux = muxOptionToMuxNumber[sourceSignal]
            muxSource[mux] = sourceSignal
            if (!muxes.includes(optionNamePrepend + mux)){
                muxes.push(optionNamePrepend + mux)
            }
        }
        inst.muxesUsed = muxes;
        ui.muxesUsed.readOnly = true;
    }
    else {
        ui.muxesUsed.readOnly = false;
    }
    var muxesUsed = inst.muxesUsed;
    for (var muxConfigIndex in muxConfigs)
    {
        var muxConfigName = muxConfigs[muxConfigIndex];
        var muxNumber = parseInt(muxConfigName.replace("mux", "").replace("Config", ""))
        var turnOnMux = false
        for (var muxesUsedIndex in muxesUsed)
        {
            var usedMuxName = muxesUsed[muxesUsedIndex]
            var usedMuxNumberString = usedMuxName.replace("XBAR_MUX", "")
            var usedMuxNumber = parseInt(usedMuxName.replace("XBAR_MUX", ""))
            //console.log("used: " + usedMuxNumber)
            //console.log("checking: " + muxNumber)
            var turnOnMux = true;

            if (usedMuxNumber == muxNumber)
            {
                turnOnMux = true;                
                if (inst["useSourceSelect"])
                {
                    inst[muxConfigName] = "XBAR_CLB_MUX" + usedMuxNumberString + "_" + muxSource[usedMuxNumberString]
                }
                break;
            }
            else
            {
                turnOnMux = false;
            }
            
        }
        if (turnOnMux)
        {
            ui[muxConfigName].hidden = false;
        }
        else
        {
            ui[muxConfigName].hidden = true;
        }
        ui[muxConfigName].readOnly = inst["useSourceSelect"];
    }
}

var config = [];
var latchModeConfig = {
    name        : "latchMode",
    displayName : "Latch Mode",
    description : 'Whether the output is latched or not',
    hidden      : false,
    default     : false
};

var invertConfig = {
    name        : "invertMode",
    displayName : "Invert Mode",
    description : 'Whether the output is inverted or not',
    hidden      : false,
    default     : false
    };

var muxesUsed = {
        name        : "muxesUsed",
        displayName : "MUXes to be used",
        description : 'Which MUXes are be to use from the CLB X-BAR.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        onChange    : onChangeMuxesUsed,
        options     : device_driverlib_peripheral.XBAR_MUXES
        
}

var auxInput = {
        name        : "auxInput",
        displayName : "Aux Signal Input",
        description : 'Which Aux Signal is configured to be sourced from the muxes.',
        hidden      : false,
        default     : device_driverlib_peripheral.XBAR_AuxSigNum[0].name,
        onChange    : onChangeauxInput,
        options     : device_driverlib_peripheral.XBAR_AuxSigNum,
        
}


config.push(auxInput);
//config.push(latchModeConfig);
config.push(invertConfig);

config.push({
    name: "useSourceSelect",
    displayName: "Auto Enable Mux Setting From Source",
    description: "Select your source and have the muxes used get autocalculated",
    longDescription: "Instead of selecting the muxes to be used and then selecting your source signals, select your source signals and \
    and have the muxes to be used auto calculated",
    default : false,
    onChange: onChangeMuxesUsed,
})



var muxSelectConfig = []
var muxConfigs = []
var allMuxOptions = []
var muxOptionToMuxNumber = {}

for (var mux_number_index in device_driverlib_peripheral.XBAR_CLBMuxConfig_All_MUXES)
{

    var muxSpecificOptions = device_driverlib_peripheral.XBAR_CLBMuxConfig_All_MUXES[mux_number_index]
    if (muxSpecificOptions[0] != undefined)
    {
        var noMuxNumOptions = muxSpecificOptions.map(element => {
            var elementName = element.name.replace(/XBAR_CLB_MUX[0-9][0-9]_/g, "")
            var elementMux = element.name.substring("XBAR_CLB_MUX".length, "XBAR_CLB_MUX".length + 2)
            muxOptionToMuxNumber[elementName] = elementMux
            return { name: elementName, displayName: element.displayName+" (MUX "+ elementMux + ")" }
        });


        var muxOptions = {
            name        : "mux" + mux_number_index + "Config",
            displayName : "MUX  " + mux_number_index + " Config",
            description : 'Mux Configuration for CLB XBAR\'s MUX number ' + mux_number_index,
            hidden      : true,
            default     : muxSpecificOptions[0].name,
            options     : muxSpecificOptions
        };

        muxConfigs.push(muxOptions.name)

        muxSelectConfig.push(muxOptions)

        allMuxOptions = allMuxOptions.concat(noMuxNumOptions)
    }
}

var sourceSignals = {
    name        : "sourceSignals",
    displayName : "Source Signals",
    description : 'Which signals to use for this output.',
    hidden      : true,
    default     : [],
    minSelections: 0,
    options     : allMuxOptions,
    onChange: onChangeMuxesUsed,    
}

config.push(sourceSignals)
config.push(
    {
        name: "GROUP_MUXSELECT",
        displayName: "Mux Selection Method",
        config : muxSelectConfig
    }
)
muxSelectConfig.unshift(muxesUsed);

var clbxbarModule = {
    peripheralName: "CLBXBAR",
    displayName: "CLBXBAR",
    maxInstances: 8,
    defaultInstanceName: "myCLBXBAR",
    description: "CLB X-bar",
    config: config,
    templates: {
        boardc : "/driverlib/clbxbar/clbxbar.board.c.xdt",
        boardh : "/driverlib/clbxbar/clbxbar.board.h.xdt"
    },
    validate    : onValidate,
};

exports = clbxbarModule;