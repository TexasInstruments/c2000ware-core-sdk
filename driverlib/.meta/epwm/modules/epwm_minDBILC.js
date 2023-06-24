let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_epwm.js");
// input 1 is the channel's output, input 2 is other channel's output
let EPWM_MINDB_ICL_LUT_A = [
    { name: "EPWM_MINDB_ICL_LUT_DEC0", displayName: "ICLXBAR = LOW | MINDBxB = LOW | MINDBxA = LOW" },
    { name: "EPWM_MINDB_ICL_LUT_DEC1", displayName: "ICLXBAR = LOW | MINDBxB = LOW | MINDBxA = HIGH" },
    { name: "EPWM_MINDB_ICL_LUT_DEC2", displayName: "ICLXBAR = LOW | MINDBxB = HIGH | MINDBxA = LOW" },
    { name: "EPWM_MINDB_ICL_LUT_DEC3", displayName: "ICLXBAR = LOW | MINDBxB = HIGH | MINDBxA = HIGH" },
    { name: "EPWM_MINDB_ICL_LUT_DEC4", displayName: "ICLXBAR = HIGH | MINDBxB = LOW | MINDBxA = LOW" },
    { name: "EPWM_MINDB_ICL_LUT_DEC5", displayName: "ICLXBAR = HIGH | MINDBxB = LOW | MINDBxA = HIGH" },
    { name: "EPWM_MINDB_ICL_LUT_DEC6", displayName: "ICLXBAR = HIGH | MINDBxB = HIGH | MINDBxA = LOW" },
    { name: "EPWM_MINDB_ICL_LUT_DEC7", displayName: "ICLXBAR = HIGH | MINDBxB = HIGH | MINDBxA = HIGH" },
]

let EPWM_MINDB_ICL_LUT_B = [
    { name: "EPWM_MINDB_ICL_LUT_DEC0", displayName: "ICLXBAR = LOW | MINDBxA = LOW | MINDBxB = LOW" },
    { name: "EPWM_MINDB_ICL_LUT_DEC1", displayName: "ICLXBAR = LOW | MINDBxA = LOW | MINDBxB = HIGH" },
    { name: "EPWM_MINDB_ICL_LUT_DEC2", displayName: "ICLXBAR = LOW | MINDBxA = HIGH | MINDBxB = HIGH" },
    { name: "EPWM_MINDB_ICL_LUT_DEC3", displayName: "ICLXBAR = LOW | MINDBxA = HIGH | MINDBxB = HIGH" },
    { name: "EPWM_MINDB_ICL_LUT_DEC4", displayName: "ICLXBAR = HIGH | MINDBxA = LOW | MINDBxB = LOW" },
    { name: "EPWM_MINDB_ICL_LUT_DEC5", displayName: "ICLXBAR = HIGH | MINDBxA = LOW | MINDBxB = HIGH" },
    { name: "EPWM_MINDB_ICL_LUT_DEC6", displayName: "ICLXBAR = HIGH | MINDBxA = HIGH | MINDBxB = LOW" },
    { name: "EPWM_MINDB_ICL_LUT_DEC7", displayName: "ICLXBAR = HIGH | MINDBxA = HIGH | MINDBxB = HIGH" },
]

function set_LUT_table(inst, ui, dbOutput, reset)
{
    var output_LUT_high = inst["epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTHIGH"];
    var output_LUT_low = inst["epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTLOW"];
    var output_high = "1";
    var output_low = "0";
    
    if(reset)
    {
        // inst["epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTHIGH"].;
        // inst["epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTLOW"];

    }else
    {
        for(var index_high_options in output_LUT_high)
        {
            switch(output_LUT_high[index_high_options]) 
            {
                case "EPWM_MINDB_ICL_LUT_DEC0":
                    inst["epwmICL_LUT0" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_high;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC1":
                    inst["epwmICL_LUT1" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_high;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC2":
                    inst["epwmICL_LUT2" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_high;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC3":
                    inst["epwmICL_LUT3" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_high;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC4":
                    inst["epwmICL_LUT4" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_high;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC5":
                    inst["epwmICL_LUT5" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_high;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC6":
                    inst["epwmICL_LUT6" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_high;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC7":
                    inst["epwmICL_LUT7" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_high;
                    break;
            }
        }
    
        for(var index_low_options in output_LUT_low)
        {
            // check if LUT high does not have LUT low option and set that defautl to low
            switch(output_LUT_low[index_low_options]) 
            {
                case "EPWM_MINDB_ICL_LUT_DEC0":
                    inst["epwmICL_LUT0" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_low;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC1":
                    inst["epwmICL_LUT1" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_low;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC2":
                    inst["epwmICL_LUT2" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_low;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC3":
                    inst["epwmICL_LUT3" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_low;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC4":
                    inst["epwmICL_LUT4" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_low;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC5":
                    inst["epwmICL_LUT5" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_low;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC6":
                    inst["epwmICL_LUT6" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_low;
                    break;
                case "EPWM_MINDB_ICL_LUT_DEC7":
                    inst["epwmICL_LUT7" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = output_low;
                    break;
            }
        }
    }
    
}

function onChangeEnableDisable(inst, ui)
{
    for (var dbOutputIndex in device_driverlib_peripheral.EPWM_DeadBandOutput)
    {
        var dbOutput = device_driverlib_peripheral.EPWM_DeadBandOutput[dbOutputIndex];
        if(inst["epwmMinDeadBand_Enable" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] === true)
        {
            ui["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_inputRefSignal"].hidden = false;
            ui["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_invertInput"].hidden = false;
            ui["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_setDelay"].hidden = false;
            ui["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_configBlockSignal"].hidden = false;
            ui["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_configANDOR"].hidden = false;
        }else
        {
            ui["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_inputRefSignal"].hidden = true;
            ui["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_invertInput"].hidden = true;
            ui["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_setDelay"].hidden = true;
            ui["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_configBlockSignal"].hidden = true;
            ui["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_configANDOR"].hidden = true;
            inst["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_inputRefSignal"] = "EPWM_MINDB_SEL_DEPWM";
            inst["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_invertInput"] = "EPWM_MINDB_REF_SIG";
            inst["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_setDelay"] = 1;
            inst["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_configBlockSignal"] = "EPWM_MINDB_BLOCKING_SIGNAL_BYPASS";
            inst["epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_configANDOR"] = "EPWM_MINDB_POLSEL_INVERT_LOGICAL_AND";
        }
        if(inst["epwmICL_Enable" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] === true)
        {
            ui["epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_selXBAR"].hidden = false;
            ui["epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTHIGH"].hidden = false;
            ui["epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTLOW"].hidden = false;
            set_LUT_table(inst, ui, dbOutput, 0);
        }else
        {
            ui["epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_selXBAR"].hidden = true;
            ui["epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTHIGH"].hidden = true;
            ui["epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTLOW"].hidden = true;
            inst["epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_selXBAR"] = "EPWM_MINDB_ICL_XBAR_OUT0";
            inst["epwmICL_LUT0" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = "0";
            inst["epwmICL_LUT1" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = "0";
            inst["epwmICL_LUT2" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = "0";
            inst["epwmICL_LUT3" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = "0";
            inst["epwmICL_LUT4" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = "0";
            inst["epwmICL_LUT5" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = "0";
            inst["epwmICL_LUT6" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = "0";
            inst["epwmICL_LUT7" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "")] = "0";

        }
        
    }
}

var config = [

];

var mindbLongDesc = `
Enhanced Pulse Width Modulator Minimum Deadband and Illegal Combo Logic Configuration

The input into the MINDB module can be a signal from the MINDB X-BAR or the diode emulation output (without high resolution).
The third input into the LUT for the ICL module is selected from one of the ICL X-BAR outputs.
![an offline image](../../driverlib/.meta/epwm/docs/MINDB_ICL_block_diagram.png "MINDB and ICL Block Diagram")
`;


for (var dbOutputIndex in device_driverlib_peripheral.EPWM_DeadBandOutput)
{
    var dbOutput = device_driverlib_peripheral.EPWM_DeadBandOutput[dbOutputIndex];
    var dbOutput_Configs = [
        {
            name: "epwmMinDeadBand_Enable" + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""),
            displayName : "Enable Minimum Dead-Band for " + dbOutput.displayName.replace("DB output is", ""),
            description : 'Enable dead-band output for' + dbOutput.displayName.replace("DB output is", ""),
            hidden      : false,
            default     : false,
            onChange    : onChangeEnableDisable
        },
        {
            name: "epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_inputRefSignal",
            displayName : "Input Reference Signal for" + dbOutput.displayName.replace("DB output is", ""),
            description : 'Select reference signal for minimum deadband output' + dbOutput.displayName.replace("DB output is", ""),
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_MINDB_SEL[0].name,
            options     : device_driverlib_peripheral.EPWM_MINDB_SEL,
		},
        {
            name: "epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_invertInput", 
            displayName : "Invert Input Reference Signal",
            description : 'Invert input reference signal to the Minimum Dead-Band Logic',
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_MINDB_REF[0].name ,
            options     : device_driverlib_peripheral.EPWM_MINDB_REF
        },
        {
            name: "epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_setDelay",
            displayName : "Minimum Dead-Band Delay for" + dbOutput.displayName.replace("DB output is", "") + " (SYSCLK Cycles)",
            description : 'Set minimum dead-band delay applied to reference signal',
            hidden      : true,
            default     : 1            
        },
        {
            name: "epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_configBlockSignal",
            displayName : "Blocking Signal for" + dbOutput.displayName.replace("DB output is", ""),
            description : 'Select blocking signal for' + dbOutput.displayName.replace("DB output is", ""),
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_MINDB_BLOCKING_SIGNAL[0].name,
            options     : device_driverlib_peripheral.EPWM_MINDB_BLOCKING_SIGNAL    
        },
        {
            name: "epwmMinDeadBand_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_configANDOR",
            displayName : "AND OR Logic for Blocking Signal with " + dbOutput.displayName.replace("DB output is", ""),
            description : 'Select signal for the AND OR logic of' + dbOutput.displayName.replace("DB output is", ""),
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_MINDB_POLSEL[0].name,
            options     : device_driverlib_peripheral.EPWM_MINDB_POLSEL
        },

    ]

    config = config.concat([{
            name:  "GROUP_MINDB_Output_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""),
            displayName: dbOutput.displayName.replace("DB output is", "MINDB").replace("PWM", "PWMx") + " Output Configuration",
            description: "",
            longDescription: "",
            config: dbOutput_Configs
    }]);

}

for (var dbOutputIndex in device_driverlib_peripheral.EPWM_DeadBandOutput)
{
    var dbOutput = device_driverlib_peripheral.EPWM_DeadBandOutput[dbOutputIndex];
    var dbOutput_Configs = [
        {
            name: "epwmICL_Enable" + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""),
            displayName : "Enable Illegal Combo Logic for" + dbOutput.displayName.replace("DB output is", ""),
            description : 'Enable Illegal Combo Logic for' + dbOutput.displayName.replace("DB output is", ""),
            hidden      : false,
            default     : false,
            onChange    : onChangeEnableDisable
        },
        {
            name: "epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_selXBAR", 
            displayName : "Input XBAR Reference Signal",
            description : 'Select input XBAR signal to the Illegal Combo Logic',
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_MINDB_ICL_XBAR[0].name ,
            options     : device_driverlib_peripheral.EPWM_MINDB_ICL_XBAR
        },
        {
            name: "epwmICL_LUT0" + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""),
            displayName : "Backend",
            description : 'Select input XBAR signal to the Illegal Combo Logic',
            hidden      : true,
            default     : "0" ,
        },
        {
            name: "epwmICL_LUT1" + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""), 
            displayName : "Backend",
            description : 'Select input XBAR signal to the Illegal Combo Logic',
            hidden      : true,
            default     : "0" ,
        },
        {
            name: "epwmICL_LUT2" + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""), 
            displayName : "Backend",
            description : 'Select input XBAR signal to the Illegal Combo Logic',
            hidden      : true,
            default     : "0" ,
        },
        {
            name: "epwmICL_LUT3" + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""), 
            displayName : "Backend",
	    description : 'Select input XBAR signal to the Illegal Combo Logic', 
	    hidden      : true,
            default     : "0" ,
        },
        {
            name: "epwmICL_LUT4" + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""), 
            displayName : "Backend",
            description : 'Select input XBAR signal to the Illegal Combo Logic',
            hidden      : true,
            default     : "0" ,
        },
        {
            name: "epwmICL_LUT5" + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""), 
            displayName : "Backend",
            description : 'Select input XBAR signal to the Illegal Combo Logic',
            hidden      : true,
            default     : "0" ,
        },
        {
            name: "epwmICL_LUT6" + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""), 
            displayName : "Backend",
            description : 'Select input XBAR signal to the Illegal Combo Logic',
            hidden      : true,
            default     : "0" ,
        },
        {
            name: "epwmICL_LUT7" + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""), 
            displayName : "Backend",
            description : 'Select input XBAR signal to the Illegal Combo Logic',
            hidden      : true,
            default     : "0" ,
        },
    ]
    if(dbOutput.name.replace("EPWM_DB_OUTPUT_", "")== "A")
    {
        dbOutput_Configs = dbOutput_Configs.concat([{
            name: "epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTHIGH", 
            displayName : "Output High",
            description : 'Select which combinations of inputs to output high',
            hidden      : true,
            default     : [],
            minSelections: 0,
            options     : EPWM_MINDB_ICL_LUT_A,
            onChange    : onChangeEnableDisable

        },
        {
            name: "epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTLOW", 
            displayName : "Output Low",
            description : 'Select which combinations of inputs to output low',
            hidden      : true,
            default     : ["EPWM_MINDB_ICL_LUT_DEC0",
                            "EPWM_MINDB_ICL_LUT_DEC1",
                            "EPWM_MINDB_ICL_LUT_DEC2",
                            "EPWM_MINDB_ICL_LUT_DEC3",
                            "EPWM_MINDB_ICL_LUT_DEC4",
                            "EPWM_MINDB_ICL_LUT_DEC5",
                            "EPWM_MINDB_ICL_LUT_DEC6",
                            "EPWM_MINDB_ICL_LUT_DEC7"],
            minSelections: 0,
            options     : EPWM_MINDB_ICL_LUT_A,
            onChange    : onChangeEnableDisable

        }]);
    }else
    {
        dbOutput_Configs = dbOutput_Configs.concat([{
            name: "epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTHIGH", 
            displayName : "Output High",
            description : 'Select which combinations of inputs to output high',
            hidden      : true,
            default     : [],
            minSelections: 0,
            options     : EPWM_MINDB_ICL_LUT_B,
            onChange    : onChangeEnableDisable

        },
        {
            name: "epwmICL_" + dbOutput.name.replace("EPWM_DB_OUTPUT_", "") + "_OUTLOW", 
            displayName : "Output Low",
            description : 'Select which combinations of inputs to output low',
            hidden      : true,
            default     : ["EPWM_MINDB_ICL_LUT_DEC0",
                            "EPWM_MINDB_ICL_LUT_DEC1",
                            "EPWM_MINDB_ICL_LUT_DEC2",
                            "EPWM_MINDB_ICL_LUT_DEC3",
                            "EPWM_MINDB_ICL_LUT_DEC4",
                            "EPWM_MINDB_ICL_LUT_DEC5",
                            "EPWM_MINDB_ICL_LUT_DEC6",
                            "EPWM_MINDB_ICL_LUT_DEC7"],
            minSelections: 0,
            options     : EPWM_MINDB_ICL_LUT_B,
            onChange    : onChangeEnableDisable

        }]);
    }
    for (var ilcOutputIndex in device_driverlib_peripheral.EPWM_MINDB_ICL_LUT)
    {
        var ilcOutput = device_driverlib_peripheral.EPWM_MINDB_ICL_LUT[ilcOutputIndex];
        // change LUT output value output low -> Output low
        dbOutput_Configs = dbOutput_Configs.concat([
            {
                name:  ilcOutput.name + dbOutput.name.replace("EPWM_DB_OUTPUT_", ""),
                displayName: ilcOutput.displayName.replace("PWMA/B", dbOutput.displayName.replace("DB output is ePWM", "")).replace("output", "Output").replace("value","Value").replace("on", "On").replace("decoding", "Decoding"),
                description: "",
                hidden: true,
                default: device_driverlib_peripheral.EPWM_MINDB_ICL_XBAR[0].name.replace("A/B", dbOutput.displayName.replace("DB output is ePWM", "")),
                options: device_driverlib_peripheral.EPWM_MINDB_ICL_XBAR
            }
            
]);
    } 
    config = config.concat([{
            name:  "GROUP_ICL_" +dbOutput.name.replace("EPWM_DB_OUTPUT_", ""),
            displayName: "ICL Channel " + dbOutput.name.replace("EPWM_DB_OUTPUT_", "").replace("EPWM_DB_OUTPUT_", ""),
            description: "",
            longDescription: "",
            config: dbOutput_Configs
    }]);

}
var epwmMinimumDeadbandIllegalComboLogicSubmodule = {
    displayName: "EPWM Minimum Deadband and Illegal Combo Logic",
    maxInstances: Common.peripheralCount("EPWM"),
    defaultInstanceName: "EPWM_MINDB",
    description: mindbLongDesc,
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};
        

exports = epwmMinimumDeadbandIllegalComboLogicSubmodule;
