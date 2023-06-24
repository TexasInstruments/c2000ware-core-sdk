let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_epwm.js");
let epwm_json = system.getScript("/driverlib/epwm/epwm.json").epwm;
//console.log(epwm_json);

let OPEN_PAR = "(";
let CLOSE_PAR = ");";
let COMMA = ", ";
let _BASE = "_BASE"


function getCode(inst, inst_submodule, ui_name, commentOut, indicies){
    var output = "";
    var appendArguments = true;
    var showOutput = true;

    // These items have the same function
    var duplicate_inst = ["epwmTimebase_hsClockDiv", "epwmDigitalCompare_stopValleyCaptureTriggerCount"];
    var duplicate_pair = ["epwmTimebase_clockDiv", "epwmDigitalCompare_startValleyCaptureTriggerCount"];

    // console.log("UI Name")
    // console.log(ui_name)

    var info = epwm_json.find(input => {
        return (input.name === ui_name) && input.devices.includes(Common.getDeviceName())
    })

    if (!info){
        //console.log("Missing JSON entry:");
        //console.log(ui_name)
        return "";
    }

    if(inst.hrpwm_enable)
    {
        var uis_with_same_driverlib_function = epwm_json.filter(input => {
            return (input.driverlibFunctionHR === info.driverlibFunctionHR) && input.devices.includes(Common.getDeviceName())
        })
    }
    else
    {
        var uis_with_same_driverlib_function = epwm_json.filter(input => {
            return (input.driverlibFunction === info.driverlibFunction) && input.devices.includes(Common.getDeviceName())
        })
    }

    //console.log("Code Info:");
    //console.log(info);
    //console.log("Other UIs with the same driverlib function:");
    //console.log(uis_with_same_driverlib_function);

    var require_other_ui_names = false;
    var driverlibFunctionArgKeysArray = Object.keys(info.driverlibFunctionArg);
    var outputFunctionArgs = new Array(driverlibFunctionArgKeysArray.length);
    for (var functionArgIndex = 0; functionArgIndex < driverlibFunctionArgKeysArray.length; functionArgIndex++)
    {
        var functionArgName = driverlibFunctionArgKeysArray[functionArgIndex];
        var functionArgValue = info.driverlibFunctionArg[functionArgName];
        if (functionArgName == "base") 
        {
            outputFunctionArgs[functionArgIndex] = inst.$name + _BASE;
        }
        else if (functionArgValue == "this")
        {
            outputFunctionArgs[functionArgIndex] = inst_submodule[ui_name];
        }
        else if (functionArgValue == "")
        {
            require_other_ui_names = true;
            var requried_other_ui = uis_with_same_driverlib_function.find(input => {
                if (input.driverlibFunctionArg[functionArgName] == "this")
                {
                    return input
                }
            });
            outputFunctionArgs[functionArgIndex] = inst_submodule[requried_other_ui.name];
        }
        else
        {
            outputFunctionArgs[functionArgIndex] = functionArgValue;
        }
    }

    // For boolean type UI elements 
    // If it has an alternate driverlib version then it is boolean type
    // Use driverlibFunctionAlt
    // If driverlibFunction or driverlibFunctionAlt is empty then do not include arguments in the output
    //console.log(inst.hrpwm_enable)
    if(inst.hrpwm_enable)
    {
        //console.log(ui_name, inst_submodule[ui_name], info.hasOwnProperty('driverlibFunctionHRAlt'),info.hasOwnProperty('driverlibFunctionHR'))
        if (info.hasOwnProperty('driverlibFunctionHRAlt'))  
        {
            // Check to see if the set value is different from the default value
            if (showOutput)
            {
                if (inst_submodule[ui_name])
                {
                    //console.log("true", ui_name)
                    if (info.driverlibFunctionHR == "")
                    {
                        output = "";
                        appendArguments = false;
                    }
                    else
                    {
                        output = info.driverlibFunctionHR; 
                        appendArguments = true;
                    }
                }
                else
                {
                    //console.log("not true", ui_name)
                    if (info.driverlibFunctionHRAlt == "")
                    {
                        output = "";
                        appendArguments = false;
                        //console.log(ui_name)
                    }
                    else
                    {
                        output = info.driverlibFunctionHRAlt; 
                        appendArguments = true; 
                    }
                    //console.log(inst_submodule[ui_name], output)
                }
            }
            else
            {
                appendArguments = false;
            }
        }
        else
        {
            if (info.hasOwnProperty('driverlibFunctionHR'))  
            {
                output = info.driverlibFunctionHR;
                appendArguments = true;
            }
            else
            {
                output = "";
                appendArguments = false;
            }
        }
    }
    else
    {
        if (info.hasOwnProperty('driverlibFunctionAlt'))  
        {
            // Check to see if the set value is different from the default value
            if (showOutput)
            {
                if (inst_submodule[ui_name])
                {
                    if (info.driverlibFunction == "")
                    {
                        output = "";
                        appendArguments = false;
                    }
                    else
                    {
                        output = info.driverlibFunction; 
                        appendArguments = true;
                    }
                }
                else
                {
                    if (info.driverlibFunctionAlt == "")
                    {
                        output = "";
                        appendArguments = false;
                    }
                    else
                    {
                        output = info.driverlibFunctionAlt; 
                        appendArguments = true; 
                    }
                   
                }
            }
            else
            {
                appendArguments = false;
            }
        }
        else
        {
            if (info.hasOwnProperty('driverlibFunction')) 
            {
                output = info.driverlibFunction;
                appendArguments = true;
            }
            else
            {
                output = "";
                appendArguments = false;
            }
        }
    }

    //console.log(output)
    // Only add arguments to a function if there is a function being outputted
    // This is cross referenced with the code above
    if (appendArguments)
    {
        //console.log(inst_submodule[ui_name], output)
        output += OPEN_PAR;
        //console.log(inst_submodule[ui_name], output)
        for (var outputFunctionArgIndex = 0; outputFunctionArgIndex < outputFunctionArgs.length; outputFunctionArgIndex++)
        {
            // Check to see if the argument belongs to an OR'd input
            if (String(outputFunctionArgs[outputFunctionArgIndex]).indexOf(',') > -1)
            {
                outputFunctionArgs[outputFunctionArgIndex] = String(outputFunctionArgs[outputFunctionArgIndex]).replace(/,/g, " | ")
                //showOutput = true;
            }
            // Check to see if argument is empty (no options of an OR'ed select are selected) and output 0 
            if (String(outputFunctionArgs[outputFunctionArgIndex]) == "")
            {
                // Don't output the code if there is no argument for it
                showOutput = false;
            }

            output += outputFunctionArgs[outputFunctionArgIndex];
            if (outputFunctionArgIndex != outputFunctionArgs.length - 1)
            {
                output += COMMA; 
            }
        }

            output += CLOSE_PAR;
    }
    if (showOutput == false)
    {
       output = ""; 
    }
    if (showOutput == true && commentOut == true && output != "")
    {
        // Handle the special case where multiple sysconfig options have the same output function
        if (duplicate_pair.includes(ui_name))
        {
            var len = indicies.length;
            var duplicateIndex = duplicate_pair.indexOf(ui_name);
            if(len == 2)
            {
                if (inst[duplicate_inst[duplicateIndex]] != inst.$module.config[indicies[0]].config[indicies[1]+1].default)
                {
                    output = output;
                }
                else{output = "//" + output;}
            }
            else if (len == 3)
            {
                if (inst[duplicate_inst[duplicateIndex]] != inst.$module.config[indicies[0]].config[indicies[1]].config[indicies[2]+1].default)
                {
                    output = output;
                }
                else{output = "//" + output;}
            }
            else if (len == 4)
            {
                if (inst[duplicate_inst[duplicateIndex]] != inst.$module.config[indicies[0]].config[indicies[1]].config[indicies[2]].config[indicies[3]+1].default)
                {
                    output = output;
                }
                else{output = "//" + output;}
            }
        }
        else
        {
           output = "//" + output; 
        }

        //if (ui_name == "epwmTimebase_clockDiv" && inst["epwmTimebase_hsClockDiv"] != "EPWM_HSCLOCK_DIVIDER_2")
        //{
        //    output = output;
        //}
        //else if (ui_name == "epwmDigitalCompare_startValleyCaptureTriggerCount" && inst["epwmDigitalCompare_stopValleyCaptureTriggerCount"] != "0")
        //{
        //    output = output;
        //}
        //else
        //{
        //    output = "//" + output;
        //}
    }
    return output;
}

exports = {
    getCode : getCode,
};