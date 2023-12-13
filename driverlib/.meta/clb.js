let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let CLBSignals   = system.getScript("/driverlib/clb/clbSignals.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_clb.js");

/* Intro splash on GUI */
let longDescription = `The Configurable Logic Block (CLB) is a collection of configurable blocks that may be inter-connected using software to implement custom digital logic functions.`

let longDescriptionCLBInput = `
The input type for the CLB can be from the local mux, the global mux, or the GPREG. For CLB type 1 and
type 2 (on devices F2807x, F2837xS, F2837xD, and F28004x), the pipelining option which adds an additional 
flop for synchronized inputs is not included.

Note: The synchronizer will add a delay of 2-3 cycles to the input path (the exact value of the 
delay is 2 to 3 cycles, it is not predictable which delay value it will be).

![Image Missing](../../driverlib/.meta/clb/references/CLB_Input.png)
`

let longDescriptionSPI = `
Export CLB data through SPI buffer. Data is HLC R0 regiter

![Image Missing](../../driverlib/.meta/clb/references/SPI_Buffer.png)
`

var MAX_OUTPUTS = 16;
if (Common.CLB_isType1())
{
    MAX_OUTPUTS = 24;
}
else if (Common.CLB_isType2())
{
    MAX_OUTPUTS = 32;
}

var staticSwitchOptions = [
    { name: 0	, displayName: 'Zero'                   },
    { name: 8	, displayName: 'One'                    },
    { name: 24	, displayName: 'Boundary input 0'       },
    { name: 25	, displayName: 'Boundary input 1'       },
    { name: 26	, displayName: 'Boundary input 2'       },
    { name: 27	, displayName: 'Boundary input 3'       },
    { name: 28	, displayName: 'Boundary input 4'       },
    { name: 29	, displayName: 'Boundary input 5'       },
    { name: 30	, displayName: 'Boundary input 6'       },
    { name: 31	, displayName: 'Boundary input 7'       },
    { name: 7	, displayName: 'LUT 0 Output'           },
    { name: 15	, displayName: 'LUT 1 Output'           },
    { name: 23	, displayName: 'LUT 2 Output'           },
    { name: 6	, displayName: 'FSM 0 Output'           },
    { name: 4	, displayName: 'FSM 0 State 0 Value'    },
    { name: 5	, displayName: 'FSM 0 State 1 Value'    },
    { name: 14	, displayName: 'FSM 1 Output'           },
    { name: 12	, displayName: 'FSM 1 State 0 Value'    },
    { name: 13	, displayName: 'FSM 1 State 1 Value'    },
    { name: 22	, displayName: 'FSM 2 Output'           },
    { name: 20	, displayName: 'FSM 2 State 0 Value'    },
    { name: 21	, displayName: 'FSM 2 State 1 Value'    },
    { name: 2	, displayName: 'Counter 0 Equals Zero'   },
    { name: 3	, displayName: 'Counter 0 Equals Match 1' },
    { name: 1	, displayName: 'Counter 0 Equals Match 2' },
    { name: 10	, displayName: 'Counter 1 Equals Zero'   },
    { name: 11	, displayName: 'Counter 1 Equals Match 1' },
    { name: 9	, displayName: 'Counter 1 Equals Match 2' },
    { name: 18	, displayName: 'COUNTER 2 Equals Zero'   },
    { name: 19	, displayName: 'Counter 2 Equals Match 1' },
    { name: 1	, displayName: 'Counter 2 Equals Match 2' },
];

var totatCLBOutputs = [];
for (var i = 0; i < MAX_OUTPUTS; i++)
{
    totatCLBOutputs.push({
        name: "CLB_OUT" + i.toString(), displayName: "Output " + i.toString(),
    })
}

var CLB_INSTANCE = [
    { name: "CLB1_BASE", displayName: "CLB1"},
    { name: "CLB2_BASE", displayName: "CLB2"},
    { name: "CLB3_BASE", displayName: "CLB3"},
    { name: "CLB4_BASE", displayName: "CLB4"}
]

var numberOfCLBs = 4;

if (Common.getDeviceName().includes("F28002x"))
{
    CLB_INSTANCE = [
        { name: "CLB1_BASE", displayName: "CLB1"},
        { name: "CLB2_BASE", displayName: "CLB2"}
    ];
    numberOfCLBs = 2;
}
else if (Common.getDeviceName().includes("F2838x"))
{
    CLB_INSTANCE = [
        { name: "CLB1_BASE", displayName: "CLB1"},
        { name: "CLB2_BASE", displayName: "CLB2"},
        { name: "CLB3_BASE", displayName: "CLB3"},
        { name: "CLB4_BASE", displayName: "CLB4"},
        { name: "CLB5_BASE", displayName: "CLB5"},
        { name: "CLB6_BASE", displayName: "CLB6"},
        { name: "CLB7_BASE", displayName: "CLB7"},
        { name: "CLB8_BASE", displayName: "CLB8"}
    ]
    numberOfCLBs = 8;
}
else if (Common.getDeviceName().includes("F28P65x"))
{
    CLB_INSTANCE = [
        { name: "CLB1_BASE", displayName: "CLB1"},
        { name: "CLB2_BASE", displayName: "CLB2"},
        { name: "CLB3_BASE", displayName: "CLB3"},
        { name: "CLB4_BASE", displayName: "CLB4"},
        { name: "CLB5_BASE", displayName: "CLB5"},
        { name: "CLB6_BASE", displayName: "CLB6"}
    ]
    numberOfCLBs = 6;
}

else if (Common.getDeviceName().includes("F28P55x"))
{
    CLB_INSTANCE = [
        { name: "CLB1_BASE", displayName: "CLB1"},
        { name: "CLB2_BASE", displayName: "CLB2"}
    ];
    numberOfCLBs = 2;
}

let INPUT_TYPES = [
    {name: "GP", displayName: "Use Memory Mapped GPREG BIT"},
    {name: "GLOBAL", displayName: "Use Global Mux"},
    {name: "LOCAL", displayName: "Use Local Mux"}
]

function onChangeCLBBase(inst, ui){
    if (Common.CLB_isType2())
    {
    	var clb_with_spi_supprt = ["CLB1_BASE", "CLB2_BASE", "CLB3_BASE", "CLB4_BASE"];
    	if (["F28003x", "F28P55x"].includes(Common.getDeviceName()))
    	{
			clb_with_spi_supprt = ["CLB1_BASE", "CLB2_BASE"];
    	}
        if (clb_with_spi_supprt.includes(inst.clbBase)){
            ui["spiBufferAccess"].hidden = false;
            ui["spiBufferLoadTriggerSignal"].hidden = false;
            ui["spiBufferR0Shift"].hidden = false;
        }
        else
        {
            ui["spiBufferAccess"].hidden = true;
            ui["spiBufferLoadTriggerSignal"].hidden = true;
            ui["spiBufferR0Shift"].hidden = true;
        }
    }
}

function onChangeInputType(inst, ui)
{
    for (var clb_input_i in device_driverlib_peripheral.CLB_Inputs)
    {
        var clbInputName = device_driverlib_peripheral.CLB_Inputs[clb_input_i].name

        if (inst.inputsUsed.includes(clbInputName))
        {
            if (inst["inputType" + clbInputName] == "GP")
            {
                ui["synchronize" + clbInputName].hidden = true;
                ui["localConfig" + clbInputName].hidden = true;
                ui["globalConfig" + clbInputName].hidden = true;
                ui["gpStartValueConfig" + clbInputName].hidden = false;
            }
            else if (inst["inputType" + clbInputName] == "GLOBAL")
            {
                ui["synchronize" + clbInputName].hidden = false;
                ui["localConfig" + clbInputName].hidden = true;
                ui["globalConfig" + clbInputName].hidden = false;
                ui["gpStartValueConfig" + clbInputName].hidden = true;
            }
            else if (inst["inputType" + clbInputName] == "LOCAL")
            {
                ui["synchronize" + clbInputName].hidden = false;
                ui["localConfig" + clbInputName].hidden = false;
                ui["globalConfig" + clbInputName].hidden = true;
                ui["gpStartValueConfig" + clbInputName].hidden = true;
            }
        }
        else
        {
            ui["synchronize" + clbInputName].hidden = true;
            ui["localConfig" + clbInputName].hidden = true;
            ui["globalConfig" + clbInputName].hidden = true;
            ui["gpStartValueConfig" + clbInputName].hidden = true;
        }

        ui["inputType" + clbInputName].hidden = !inst.inputsUsed.includes(clbInputName);
        ui["filterConfig" + clbInputName].hidden = !inst.inputsUsed.includes(clbInputName);
        if (Common.CLB_isType2()){
            ui["inputPipelineConfig" + clbInputName].hidden = !inst.inputsUsed.includes(clbInputName);
        }
    }
}


/* Array of CAN configurables that are common across device families */
let config = [
    {
        name        : "clbBase",
        displayName : "CLB Instance",
        description : 'Instance of the CLB used.',
        onChange    : onChangeCLBBase,
        hidden      : false,
        default     : CLB_INSTANCE[0].name,
        options     : CLB_INSTANCE
    },
    {
        name: "enableCLB",
        displayName : "Enable CLB",
        description : 'Enable the CLB',
        hidden      : false,
        default     : false
    },
    {
        name: "outputsToOverridePeripheral",
        displayName : "Overriding Outputs",
        description : 'Outputs from the CLB which will intersect the peripheral signals',
        hidden      : false,
        default     : [],
        minSelections : 0,
        options     : totatCLBOutputs
    },
];

if (Common.CLB_isType2())
{
    config = config.concat([
        {
            name: "lockOutputsToOverridePeripheral",
            displayName : "Lock Overriding Outputs Setting",
            description : 'Lock the setting for outputs from the CLB which will intersect the peripheral signals',
            hidden      : false,
            default     : false
        }
    ]);
}

if (Common.CLB_isType1_Type2())
{
    config = config.concat([
        {
            name: "hlcNMI",
            displayName : "HLC Generates NMI",
            description : 'The HLC interrupts are not maskable',
            hidden      : false,
            default     : false
        }
    ]);

    config = config.concat([{
        name: "GROUP_PRESCALAR",
        displayName: "Clock Prescalar",
        description: "CLB input prescalar configuration",
        longDescription: "The prescaled version of the CLB clock which can be used a CLB input",
        config: [
            {
                name: "clken",
                displayName : "Enable Prescalar",
                description : 'Enable the clock prescalar',
                hidden      : false,
                default     : false
            },
            {
                name: "strb",
                displayName : "Enable Strobe Mode",
                description : 'Enable the strobe mode. When disabled, a strobe output will be sent out whenever' + 
                              ' the prescale counter value matches the Prescale Value.' +  
                              ' When enabled, the output is the prescale counter register bit position as selected by ' +
                              'TAP Select Bit.',
                hidden      : false,
                default     : false
            },
            {
                name: "tap",
                displayName : "Tap Select Bit",
                description : 'The prescaler Tap Select Bit in Strobe Mode.',
                hidden      : false,
                default     : 0,
                options     : Common.zero_to_15
            },
            {
                name: "prescale",
                displayName : "Prescale Value",
                description : 'The prescale value for the clock.',
                hidden      : false,
                default     : 1
            }
        ]
    }]);
}

if (Common.CLB_isType2())
{
    config = config.concat([{
        name: "GROUP_SPIDATAEXPORT",
        displayName: "Data Exporting Through SPI Buffer",
        description: "",
        longDescription: longDescriptionSPI,
        config: [
            {
                name: "spiBufferAccess",
                displayName : "Enable SPI Buffer Access",
                description : 'Enable CLB data exporting through SPI buffer.',
                hidden      : false,
                default     : false
            },
            {
                name: "spiBufferLoadTriggerSignal",
                displayName : "SPI Buffer Load Trigger Signal",
                description : 'SPI buffer load trigger signal.',
                hidden      : false,
                default     : staticSwitchOptions[0].name,
                options     : staticSwitchOptions
            },
            {
                name: "spiBufferR0Shift",
                displayName : "HLC R0 Register Shift Value",
                description : 'HLC R0 register shift value.',
                hidden      : false,
                default     : Common.zero_to_16[0].name,
                options     : Common.zero_to_16
            }
        ]
    }]);
}

config = config.concat([
    {
        name: "inputsUsed",
        displayName : "Inputs Used",
        description : 'Used inputs for the CLB',
        longDescription : longDescriptionCLBInput,
        hidden      : false,
        default     : [],
        minSelections : 0,
        options     : device_driverlib_peripheral.CLB_Inputs,
        onChange    : onChangeInputType
    }
]);

for (var clb_input_i in device_driverlib_peripheral.CLB_Inputs)
{
    var clbInputName = device_driverlib_peripheral.CLB_Inputs[clb_input_i].name
    var clbInputDisplayName = device_driverlib_peripheral.CLB_Inputs[clb_input_i].displayName

    var inputTypeConfig = {
        name: "inputType" + clbInputName,
        displayName : "Input Type " + clbInputDisplayName,
        description : 'Input type for the CLB input',
        hidden      : true,
        default     : INPUT_TYPES[0].name,
        options     : INPUT_TYPES,
        onChange    : onChangeInputType
    }

    var synchronizeConfig = {
        name: "synchronize" + clbInputName,
        displayName : "Enable Sync " + clbInputDisplayName,
        description : 'Enable the CLB input synchronization',
        hidden      : true,
        default     : false
    }

    var localConfig = {
        name: "localConfig" + clbInputName,
        displayName : "Local Mux " + clbInputDisplayName,
        description : 'Local Mux input for CLB',
        hidden      : true,
        default     : device_driverlib_peripheral.CLB_LocalInputMux[0].name,
        options     : device_driverlib_peripheral.CLB_LocalInputMux
    }
    
    var globalConfig = {
        name: "globalConfig" + clbInputName,
        displayName : "Global Mux " + clbInputDisplayName,
        description : 'Global Mux input for CLB',
        hidden      : true,
        default     : device_driverlib_peripheral.CLB_GlobalInputMux[0].name,
        options     : device_driverlib_peripheral.CLB_GlobalInputMux
    }
    
    var gpStartValueConfig = {
        name: "gpStartValueConfig" + clbInputName,
        displayName : "GPREG Initial Value " + clbInputDisplayName,
        description : 'GPREG Initial Value for ' + clbInputDisplayName,
        hidden      : true,
        default     : 0,
        options     : [
            { name : 0 },
            { name : 1 }
        ]
    }

    var filterConfig = {
        name: "filterConfig" + clbInputName,
        displayName : "Input Filter " + clbInputDisplayName,
        description : 'Input filter for ' + clbInputDisplayName,
        hidden      : true,
        default     : device_driverlib_peripheral.CLB_FilterType[0].name,
        options     : device_driverlib_peripheral.CLB_FilterType
    }

    var inputConfigs = [
        inputTypeConfig,
        localConfig,
        globalConfig,
        synchronizeConfig,
        filterConfig,
        gpStartValueConfig,
    ]

    if (Common.CLB_isType2())
    {
        var inputPipelineModeConfig = {
            name: "inputPipelineConfig" + clbInputName,
            displayName : "Input Pipeline " + clbInputDisplayName,
            description : 'Enable Input Pipeline for ' + clbInputDisplayName,
            hidden      : true,
            default     : false
        }

        inputConfigs.push(inputPipelineModeConfig);
    }

    
    var clbInputGroupConfig = [{
        name: "GROUP_" + clbInputName,
        displayName: "CLB " + clbInputDisplayName,
        description: "CLB Input Configuration " + clbInputDisplayName,
        longDescription: "",
        config: inputConfigs
    }];

    config = config.concat(clbInputGroupConfig);
    
}

config = config.concat([
    {
        name        : "registerInterrupts",
        displayName : "Register Interrupt Handler",
        description : 'Whether or not to register interrupt handlers in the interrupt module.',
        hidden      : false,
        default     : false
        
    },
    {
        name        : "attachTile",
        displayName : "Attach a TILE Config to this CLB",
        description : 'Whether or not to connect one of the TILE modules to this CLB module.',
        hidden      : false,
        default     : false,
        onChange    : (inst, ui)=> {
            ui["initTile"].hidden = !inst.attachTile;
        }
    },
    {
        name        : "initTile",
        displayName : "Initialize TILE",
        description : 'Whether or not to initialize the TILE within CLB_init function.',
        hidden      : true,
        default     : false,
    },
]);

function findDuplicates(arrayToCheck)
{
    const count = arrayToCheck =>
      arrayToCheck.reduce((a, b) => ({ ...a,
        [b]: (a[b] || 0) + 1
      }), {})

    const duplicates = dict =>
      Object.keys(dict).filter((a) => dict[a] > 1)

    return {count: count(arrayToCheck), duplicates: duplicates(count(arrayToCheck))};
}

function onValidate(inst, validation) {
    var usedCLBInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedCLBInsts.push(instance_obj.clbBase);
    }
    var otherContexts = Common.getOtherContextNames()
    for (var cntx of otherContexts)
    {
        var onOtherCntx = Common.getModuleForCore(inst.$module.$name, cntx);
        if (onOtherCntx)
        {
            for (var instance_index in onOtherCntx.$instances)
            {
                var instance_obj = onOtherCntx.$instances[instance_index];
                usedCLBInsts.push(instance_obj.clbBase);
            }
        }
    }

    var duplicatesResult = findDuplicates(usedCLBInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The CLB Instance used. Duplicates: " + allDuplicates, 
            inst, "clbBase");
    }

    if (inst.prescale < 0 || inst.prescale > 0xFFFF)
    {
        validation.logError(
            "The CLB prescale value must be a valid 16-bit number", 
            inst, "prescale");
    }

    var base = inst["clbBase"];
    var clb_1to4 = false;
    var clb_1 = false;
    if (["CLB1_BASE", 
        "CLB2_BASE", 
        "CLB3_BASE", 
        "CLB4_BASE", ].includes(base))
    {
        clb_1to4 = true;
    }
    if ("CLB1_BASE" == base)
    {
        clb_1 = true;
    }

    var F2838x = Common.getDeviceName().includes("F2838x");
    var F28002x = Common.getDeviceName().includes("F28002x");

    // Check global and local sources
    var i = 0;
    for (var clb_input_i in device_driverlib_peripheral.CLB_Inputs)
    {
        var clbInputName = device_driverlib_peripheral.CLB_Inputs[clb_input_i].name
        var clbSyncCheck = CLBSignals.CLBInputSignals[Common.getDeviceName()]

        if (inst.inputsUsed.includes(clbInputName))
        {
            var global_or_local = false;
            var config_pre = "";
            var enum_name = "";
            if (inst["inputType" + clbInputName] == "GLOBAL")
            {
                global_or_local = true;
                config_pre = "globalConfig";
                enum_name = "CLB_GlobalInputMux"
                clbSyncCheck = clbSyncCheck["GLOBAL_MUX"][inst["globalConfigCLB_IN" + i]];
            }
            else if (inst["inputType" + clbInputName] == "LOCAL")
            {
                global_or_local = true; 
                config_pre = "localConfig";
                enum_name = "CLB_LocalInputMux"
                clbSyncCheck = clbSyncCheck["LOCAL_MUX"][inst["localConfigCLB_IN" + i]];
            }

            //clbSyncCheck (from clbSignals.js) states whether synchronization is required
            if((clbSyncCheck == true) && (inst["synchronizeCLB_IN" + i] == false))  //When synchronization is required but not enabled, throw a warning
            {
                validation.logWarning(
                    "Synchronization is required for this signal to prevent metastability; this metastability can cause errors dependent on voltage, temperature, and wafer fab process (adds 2-3 cycle delay to input)", 
                    inst, "synchronize" + clbInputName);
            }
            else if((clbSyncCheck == false) && (inst["inputPipelineConfigCLB_IN" + i] == false))  //When input pipeline is required but not enabled, throw a warning
            {
                validation.logWarning(
                    "Pipelining is required for synchronous signals (adds 1 cycle delay to input)", 
                    inst, "inputPipelineConfig" + clbInputName);
            }
            else if((config_pre != "") && (inst["synchronizeCLB_IN" + i] == false) && (inst["inputPipelineConfigCLB_IN" + i] == false))
            {
                validation.logWarning(
                    "Having both synchronization and pipeline disabled results in a purely asynchronous signal", 
                    inst, config_pre + clbInputName);
            }
            else if((config_pre != "") && (inst["synchronizeCLB_IN" + i] == true) && (inst["inputPipelineConfigCLB_IN" + i] == true))
            {
                validation.logWarning(
                    "Having both synchronization and pipeline enabled results in a 3-4 cycle delay on the input", 
                    inst, config_pre + clbInputName);
            }

            if (global_or_local)
            {
                var result = device_driverlib_peripheral[enum_name].find(input => {
                    return input.name === inst[config_pre + clbInputName]
                })
                var diplayName = result.displayName.replace(/ /g, "")

                if (F2838x &&
                    diplayName.includes("(CLB5") &&
                    clb_1to4)
                {
                    validation.logError(
                        "This CLB input is only applicable for CLB 5-8", 
                        inst, config_pre + clbInputName);
                }
                if (F2838x &&
                    diplayName.includes("(CLB1") &&
                    !clb_1to4)
                {
                    validation.logError(
                        "This CLB input is only applicable for CLB 1-4", 
                        inst, config_pre + clbInputName);
                }
    
                if (F28002x &&
                    diplayName.includes("(CLB2") &&
                    clb_1)
                {
                    validation.logError(
                        "This CLB input is only applicable for CLB 2", 
                        inst, config_pre + clbInputName);
                }
                if (F28002x &&
                    diplayName.includes("(CLB1") &&
                    !clb_1)
                {
                    validation.logError(
                        "This CLB input is only applicable for CLB 1", 
                        inst, config_pre + clbInputName);
                }
            }
        }
        i++;
    }

    var temp_arr = [];

    for(var n = 0; n < MAX_OUTPUTS; n++)
    {
        if(inst.outputsToOverridePeripheral[n])
        {
            if(CLBSignals.CLBInputSignals[Common.getDeviceName()]["OUT_OVERRIDE"][inst.clbBase.replace("_BASE", "")][inst.outputsToOverridePeripheral[n]])
            {
                var clbOutputNum = parseInt(inst.outputsToOverridePeripheral[n].replace("CLB_OUT", ""), 10);
                var textOutput = "CLB Output " + clbOutputNum + " is overriding the " + CLBSignals.CLBInputSignals[Common.getDeviceName()]["OUT_OVERRIDE"][inst.clbBase.replace("_BASE", "")][inst.outputsToOverridePeripheral[n]] + " signal.";
                temp_arr.push(
                    {clbOutputNum, textOutput}
                );
            }
        }
    }
    
    temp_arr.sort((s1, s2) => {
        return s1.clbOutputNum - s2.clbOutputNum;
    });

    for(var n = 0; n < temp_arr.length; n++)
    {
        if(temp_arr[n].textOutput.includes("does not override"))
        {
            validation.logInfo("CLB output does not override a signal", inst, "outputsToOverridePeripheral");
        }
        else
        {
            validation.logInfo(temp_arr[n].textOutput, inst, "outputsToOverridePeripheral");
        }
    }
}

var sharedModuleInstances = undefined;

sharedModuleInstances = function (inst) {
    if (inst.attachTile)
    {
        return (
            [
                {
                    name: "tile",      
                    displayName: "TILE Configuration",
                    moduleName: "/utilities/clb_tool/clb_syscfg/source/TILE.syscfg.js",
                    collapsed: true,
                },
            ]
        );
    }
    return []
}


var clbModule = {
    peripheralName: "CLB",
    displayName: "CLB",
    // longDescription : longDescription,
    longDescription: longDescription + "\n" + (Common.getCollateralFindabilityList("CLB")),
    maxInstances: numberOfCLBs,
    defaultInstanceName: "myCLB",
    description: "Configurable Logic Block",
    config: config,
    moduleInstances: (inst) => {
        if (inst.registerInterrupts)
        {
            return [{
                name: "clbInt",      
                displayName: "CLB Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
            		$name : inst.$name + "_INT",
                    int : "INT_" + inst.$name,
                    pinmuxPeripheralModule : "",
                    driverlibInt: "INT_" + inst.clbBase.replace("_BASE", "")
                }
            }]
        }
        return []
    },
    sharedModuleInstances : sharedModuleInstances,
    templates: {
        boardc : "/driverlib/clb/clb.board.c.xdt",
        boardh : "/driverlib/clb/clb.board.h.xdt"
    },
    validate    : onValidate,
};

exports = clbModule;