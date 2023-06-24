let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_xbar.js");

/* Intro splash on GUI */
let longDescription = "The GPIO Output X-BAR takes signals from inside " + 
                        "the device and brings them out to a GPIO.";

let outputxbar_enum = device_driverlib_peripheral.XBAR_OutputMuxConfig;

var index_of_clbxbar = outputxbar_enum.length;
var clboutputxbar_only = [];
var start_of_clboutputxbar_only = false;
for (var i = 0; i < outputxbar_enum.length; i++){
    if (outputxbar_enum[i].name == "XBAR_OUT_MUX00_CLB1_OUT0")
    {
        start_of_clboutputxbar_only = true;
    }
    if (start_of_clboutputxbar_only)
    {
        clboutputxbar_only.push(outputxbar_enum[i].name)
    }
}
//console.log(clboutputxbar_only);


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
                    inst[muxConfigName] = "XBAR_OUT_MUX" + usedMuxNumberString + "_" + muxSource[usedMuxNumberString]
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
        description : 'Which MUXes are be to use from the OUTPUT X-BAR.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        onChange    : onChangeMuxesUsed,
        options     : device_driverlib_peripheral.XBAR_MUXES
        
}


config.push(latchModeConfig);
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

for (var mux_number_index in device_driverlib_peripheral.XBAR_OutputMuxConfig_All_MUXES)
{
    var muxSpecificOptions = device_driverlib_peripheral.XBAR_OutputMuxConfig_All_MUXES[mux_number_index]
    if (muxSpecificOptions[0] != undefined)
    {
        var removedclbxbar = muxSpecificOptions.filter(muxoption => {
            //console.log(muxoption.name)
            //console.log(!clboutputxbar_only.includes(muxoption.name))
            return !clboutputxbar_only.includes(muxoption.name);
        });

        var noMuxNumOptions = removedclbxbar.map(element => {
            var elementName = element.name.replace(/XBAR_OUT_MUX[0-9][0-9]_/g, "")
            var elementMux = element.name.substring("XBAR_OUT_MUX".length, "XBAR_OUT_MUX".length + 2)
            muxOptionToMuxNumber[elementName] = elementMux
            return { name: elementName, displayName: element.displayName+" (MUX "+ elementMux + ")" }
        });
        //console.log(removedclbxbar);
        if (removedclbxbar.length > 0)
        {
            var muxOptions = {
                name        : "mux" + mux_number_index + "Config",
                displayName : "MUX  " + mux_number_index + " Config",
                description : 'Mux Configuration for OUTPUT XBAR\'s MUX number ' + mux_number_index,
                hidden      : true,
                default     : removedclbxbar[0].name,
                options     : removedclbxbar
            };
            muxConfigs.push(muxOptions.name)

            muxSelectConfig.push(muxOptions)

            allMuxOptions = allMuxOptions.concat(noMuxNumOptions)
        }
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

function onValidate(inst, validation) {
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
    return (Common.typeMatches(component.type, ["OUTPUTXBAR"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var outputxbarModule = {
    peripheralName: "OUTPUTXBAR",
    displayName: "OUTPUTXBAR",
    maxInstances: Common.peripheralCount("OUTPUTXBAR"),
    defaultInstanceName: "myOUTPUTXBAR",
    description: "Output X-bar",
    filterHardware : filterHardware,
    config: config,
    templates: {
        boardc : "/driverlib/outputxbar/outputxbar.board.c.xdt",
        boardh : "/driverlib/outputxbar/outputxbar.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.outputxbarPinmuxRequirements,
    validate : onValidate,
};


if (outputxbarModule.maxInstances <= 0)
{
    delete outputxbarModule.pinmuxRequirements;
}

exports = outputxbarModule;