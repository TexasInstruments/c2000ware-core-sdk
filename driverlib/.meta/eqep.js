let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let PinmuxAdditionalUseCases   = system.getScript("/driverlib/pinmux/pinmux_additionalUseCases.js");

/* Intro splash on GUI */
let longDescription = `The Enhanced Quadrature Encoder Pulse (eQEP) module is used for direct interface with a linear or rotary
incremental encoder to get position, direction, and speed information from a rotating machine for use in a
high-performance motion and position-control system.
`

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_eqep.js");

function onChangeUseInterrupts(inst, ui)
{
    if (inst.useInterrupts){
        ui.enableInterrupt.hidden = false
        ui.registerInterrupts.hidden = false
        ui.interruptSources.hidden = false
    }
    else{
        ui.enableInterrupt.hidden = true
        ui.registerInterrupts.hidden = true
        ui.interruptSources.hidden = true
    }
}

/* Array of CAN configurables that are common across device families */
let config = [
    {
        //
        // This is needed for locking some options when a HARDWARE is needed
        // Currently we only have NO STROB connection for EQEP on launchpads
        //
        name: "$hardware",
        onChange: (inst, ui) => {
            if (inst.$hardware)
            {
                var useCaseNames = Pinmux.getPeripheralUseCaseNames("EQEP").map((useCaseOpt) => {
                      return useCaseOpt.name
                    }
                );
                useCaseNames = useCaseNames.concat(PinmuxAdditionalUseCases.getAdditionalUseCaseNames("EQEP"));

                if (useCaseNames.includes("NO STROBE"))
                {
                    inst.useCase = "NO STROBE"
                }
            }
        }
    }
];
let conditionalConfig = [];
conditionalConfig = conditionalConfig.concat([
    // setInputPolarity
    {
        name         : "inputPolarity",
        displayName  : "Input Polarity",
        description  : "Sets the polarity of the eQEP module's input signals.",
        hidden       : false,
        default      : [],
        minSelections: 0,
        options      :
        [
            {name: "invertQEPA", displayName: "Invert QEPA"},
            {name: "invertQEPB", displayName: "Invert QEPB"},
            {name: "invertIndex", displayName: "Invert Index"},
            {name: "invertStrobe", displayName: "Invert Strobe"},
        ]
    },
    // setDecoderConfig
    {
        name        : "eqepOperationMode",
        displayName : "Position Counter Source (QSRC)",
        description : `Specify if quadrature signals are being provided on QEPA and QEPB,
                        if a direction signal and a clock are being provided, or if the direction
                        should be hard-wired for a single direction with QEPA used for input.`,
        hidden      : false,
        default     : "EQEP_CONFIG_QUADRATURE",
        options     : 
        [
            {name: "EQEP_CONFIG_QUADRATURE",    displayName: "Quadrature-clock mode"},
            {name: "EQEP_CONFIG_CLOCK_DIR",     displayName: "Direction-count mode"},
            {name: "EQEP_CONFIG_UP_COUNT",      displayName: "Up-count mode, QDIR = 1"},
            {name: "EQEP_CONFIG_DOWN_COUNT",    displayName: "Down-count mode, QDIR = 0"},
        ]
    },
    {
        name        : "eqepResolution",
        displayName : "Resolution",
        description : "Specify if both rising and falling edges should be counted or just rising edges",
        hidden      : false,
        default     : "EQEP_CONFIG_2X_RESOLUTION",
        options     : 
        [
            {name: "EQEP_CONFIG_2X_RESOLUTION", displayName: "2X Resolution: Count rising and falling edge"},
            {name: "EQEP_CONFIG_1X_RESOLUTION", displayName: "1X Resolution: Count rising edge only"},
        ]
    },
    {
        name        : "eqepSwap",
        displayName : "Swap QEPA and QEPB",
        description : `Specify if the signals provided on QEPA and QEPB should be swapped 
                        before being processed.`,
        hidden      : false,
        default     : "EQEP_CONFIG_NO_SWAP",
        options     :
        [
            {name: "EQEP_CONFIG_NO_SWAP",   displayName: "Do not swap QEPA and QEPB"},
            {name: "EQEP_CONFIG_SWAP",      displayName: "Swap QEPA and QEPB"},
        ]
    },
    {
        name        : "eqepIGATE",
        displayName : "Index Pulse Gating",
        description : `Specify if the gating of the index pulse should be enabled or disabled.`,
        hidden      : false,
        default     : "EQEP_CONFIG_IGATE_DISABLE",
        options     :
        [
            {name: "EQEP_CONFIG_IGATE_DISABLE", displayName: "Disable gating of Index pulse"},
            {name: "EQEP_CONFIG_IGATE_ENABLE",  displayName: "Gate the index pin with strobe"},
        ]
    },
])
if (["F28002x","F28003x","F280013x","F280015x","F2838x", "F28P65x", "F28P55x","F28P551x","F28E12x"].includes(Common.getDeviceName())){
    conditionalConfig = conditionalConfig.concat([
        // enableDirectionChangeDuringIndex /disableDirectionChangeDuringIndex
        {
            name        : "enableDirectionChange",
            displayName : "Enable Direction Change During Index",
            description : 'Enables the index direction enhancement mode of the eQEP module.',
            hidden      : false,
            default     : false
        },
    ])
}
config = config.concat([
    {
        name            : "GROUP_DECODER",
        displayName     : "Quadrature Decoder Unit",
        description     : "",
        longDescription : "",
        config          : conditionalConfig
    },
    {
        name            : "GROUP_POSITION",
        displayName     : "Position Counter and Control Unit",
        description     : "",
        longDescription : "",
        config          : [
            // setPositionCounterConfig
            {
                name        : "positionCounterMode",
                displayName : "Position Counter Mode",
                description : "Configuration for the eQEP module position counter.",
                hidden      : false,
                default     : device_driverlib_peripheral.EQEP_PositionResetMode[0].name,
                options     : device_driverlib_peripheral.EQEP_PositionResetMode
            },
            {
                name        : "positionCounterMax",
                displayName : "Maximum Position",
                description : "Specifies the maximum position value.",
                hidden      : false,
                default     : 0
            },
            // setPosition
            {
                name        : "setPosition",
                displayName : "Position Counter (QPOSCNT)",
                description : "Sets the current encoder position.",
                hidden      : false,
                default     : 0
            },
            {
                name: "GROUP_LATCH",
                displayName: "Latch Mode",
                description: "",
                longDescription: "",
                collapsed: false,
                config: [
                    // setLatchMode
                    {
                        name        : "latchPositionCounter",
                        displayName : "QEP Capture Latch Mode (QCLM)",
                        description : "Specify the event that latches the position counter.",
                        hidden      : false,
                        default     : "EQEP_LATCH_CNT_READ_BY_CPU",
                        options     :
                        [
                            {name: "EQEP_LATCH_CNT_READ_BY_CPU",    displayName: "On position counter read"},
                            {name: "EQEP_LATCH_UNIT_TIME_OUT",      displayName: "On unit time-out event"},
                        ]
                    },
                    {
                        name        : "latchStrobePosition",
                        displayName : "Strobe Event Latch (SEL)",
                        description : "Specify which strobe event will latch the position counter into the strobe position latch register. ",
                        hidden      : false,
                        default     : "EQEP_LATCH_RISING_STROBE",
                        options     :
                        [
                            {name: "EQEP_LATCH_RISING_STROBE",      displayName: "On rising edge of strobe"},
                            {name: "EQEP_LATCH_EDGE_DIR_STROBE",    displayName: "On rising edge when clockwise, on falling when counter clockwise"},
                        ]
                    },
                    {
                        name        : "latchIndexPosition",
                        displayName : "Index Event Latch (IEL)",
                        description : "Specify which index event will latch the position counter into the index position latch register.",
                        hidden      : false,
                        default     : "EQEP_LATCH_RISING_INDEX",
                        options     :
                        [
                            {name: "EQEP_LATCH_RISING_INDEX",       displayName: "On rising edge of index"},
                            {name: "EQEP_LATCH_FALLING_INDEX",      displayName: "On falling edge of index"},
                            {name: "EQEP_LATCH_SW_INDEX_MARKER",    displayName: "On software index marker"},
                        ]
                    },
                ]
            }, 
            // setPositionInitMode
            {
                name        : "positionStrobeEvents",
                displayName : "Position Strobe Events (SEI)",
                description : "Specify which strobe event will initialize the position counter.",
                hidden      : false,
                default     : "EQEP_INIT_DO_NOTHING",
                options     :
                [
                    {name: "EQEP_INIT_DO_NOTHING",   displayName: "Action is disabled"},
                    {name: "EQEP_INIT_RISING_STROBE",   displayName: "On rising edge of strobe"},
                    {name: "EQEP_INIT_EDGE_DIR_STROBE",   displayName: "On rising edge when clockwise, on falling when counter clockwise"},
                ]
            },
            {
                name        : "positionIndexEvents",
                displayName : "Position Index Events (IEI)",
                description : "Specify which index event will initialize the position counter.",
                hidden      : false,
                default     : "EQEP_INIT_DO_NOTHING",
                options     :
                [
                    {name: "EQEP_INIT_DO_NOTHING",   displayName: "Action is disabled"},
                    {name: "EQEP_INIT_RISING_INDEX",   displayName: "On rising edge of index"},
                    {name: "EQEP_INIT_FALLING_INDEX",   displayName: "On falling edge of index"},
                ]
            },
            // setSWPositionInit
            {
                name        : "swPositionInit",
                displayName : " Set Software Initialization Position Counter",
                description : 'Sets the software initialization of the encoder position counter.',
                hidden      : false,
                default     : false
            },
            // setInitialPosition
            {
                name        : "initialPosition",
                displayName : "Position Counter Initialization Value",
                description : 'Sets the init value for the encoder position counter.',
                hidden      : false,
                default     : 0
            },
            // enableModule / disableModule
            {
                name        : "enableModule",
                displayName : "Enable Position Counter",
                description : 'Enables the eQEP module.',
                hidden      : false,
                default     : false
            },
            {
                name: "GROUP_COMPARE",
                displayName: "Compare Configuration",
                description: "",
                longDescription: "",
                collapsed: false,
                config: [
                    // setCompareConfig [do we have a boolean to determine if we do this?]
                    {
                        name        : "compareConfig",
                        displayName : "Configure Position-Compare Unit",
                        description : 'Enables configuration of eQEP module position-compare unit.',
                        hidden      : false,
                        default     : false
                    },
                    {
                        name        : "compareSyncPulsePin",
                        displayName : "Sync Output Pin Selection (SPSEL)",
                        description : "Specify if there is a sync output pulse and which pin should be used.",
                        hidden      : false,
                        default     : "EQEP_COMPARE_NO_SYNC_OUT",
                        options     :
                        [
                            {name: "EQEP_COMPARE_NO_SYNC_OUT",      displayName: "Disable sync output"},
                            {name: "EQEP_COMPARE_IDX_SYNC_OUT",     displayName: "Sync output on index pin"},
                            {name: "EQEP_COMPARE_STROBE_SYNC_OUT",  displayName: "Sync output on strobe pin"},
                        ]
                    },
                    {
                        name        : "compareShadowRegisterUse",
                        displayName : "Position Compare of Shadow Load (PCLOAD)",
                        description : "Specify if a shadow is enabled and when should the load should occur.",
                        hidden      : false,
                        default     : "EQEP_COMPARE_NO_SHADOW",
                        options     :
                        [
                            {name: "EQEP_COMPARE_NO_SHADOW",        displayName: "Disable shadow of QPOSCMP"},
                            {name: "EQEP_COMPARE_LOAD_ON_ZERO",     displayName: "Load on QPOSCNT = 0"},
                            {name: "EQEP_COMPARE_LOAD_ON_MATCH",    displayName: "Load on QPOSCNT = QPOSCMP"},
                        ]
                    },
                    {
                        name        : "compareValue",
                        displayName : "Compare Value",
                        description : 'The value to which the position count value is compared for a position-compare event.',
                        hidden      : false,
                        default     : 0
                    },
                    {
                        name        : "compareCycles",
                        displayName : "Compare Cycles",
                        description : 'The width of the pulse that can be generated on a position-compare event.  It is in units of 4 SYSCLKOUT cycles.',
                        hidden      : false,
                        default     : 0
                    },
                    // enableCompare / disableCompare
                    {
                        name        : "enableCompare",
                        displayName : "Enable Position-Compare Unit",
                        description : 'Enables the eQEP module position-compare unit.',
                        hidden      : false,
                        default     : false
                    },
                ]
            }, 
        ]
    },
    {
        name            : "GROUP_EDGE_CAPTURE",
        displayName     : "Edge Capture Unit",
        description     : "",
        longDescription : "",
        config          : [
            // setCaptureConfig [do we have a boolean to determine if we do this?]
            {
                name        : "captureConfig",
                displayName : "Configure Edge-Capture Unit",
                description : 'Enables configuration of eQEP module edge-capture unit.',
                hidden      : false,
                default     : false
            },
            {
                name        : "capPrescale",
                displayName : "Capture Prescaler (QC Timer)",
                description : "Prescaler setting of the eQEP capture timer clk.",
                hidden      : false,
                default     : device_driverlib_peripheral.EQEP_CAPCLKPrescale[0].name,
                options     : device_driverlib_peripheral.EQEP_CAPCLKPrescale
            },
            {
                name: "qcTimeFreq",
                displayName : "QC Timer Frequency [MHz]",
                getValue    : (inst) => {
                    if(inst.capPrescale == "EQEP_CAPTURE_CLK_DIV_1")
                    {
                        return (Common.getSYSCLK() / 1);
                    }
                    else if(inst.capPrescale == "EQEP_CAPTURE_CLK_DIV_2")
                    {
                        return (Common.getSYSCLK() / 2);
                    }
                    else if(inst.capPrescale == "EQEP_CAPTURE_CLK_DIV_4")
                    {
                        return (Common.getSYSCLK() / 4);
                    }
                    else if(inst.capPrescale == "EQEP_CAPTURE_CLK_DIV_8")
                    {
                        return (Common.getSYSCLK() / 8);
                    }
                    else if(inst.capPrescale == "EQEP_CAPTURE_CLK_DIV_16")
                    {
                        return (Common.getSYSCLK() / 16);
                    }
                    else if(inst.capPrescale == "EQEP_CAPTURE_CLK_DIV_32")
                    {
                        return (Common.getSYSCLK() / 32);
                    }
                    else if(inst.capPrescale == "EQEP_CAPTURE_CLK_DIV_64")
                    {
                        return (Common.getSYSCLK() / 64);
                    }
                    else if(inst.capPrescale == "EQEP_CAPTURE_CLK_DIV_128")
                    {
                        return (Common.getSYSCLK() / 128);
                    }
                },
                default : Common.getSYSCLK(),
            },
            {
                name        : "evntPrescale",
                displayName : "Unit Position Event Prescaler",
                description : "Prescaler setting of the unit position event.",
                hidden      : false,
                default     : device_driverlib_peripheral.EQEP_UPEVNTPrescale[0].name,
                options     : device_driverlib_peripheral.EQEP_UPEVNTPrescale
            },
            // enableCapture / disableCapture
            {
                name        : "enableCapture",
                displayName : "Enable Edge-Capture Unit",
                description : 'Enables the eQEP module edge-capture unit.',
                hidden      : false,
                default     : false
            },
            // enableUnitTimer / disableUnitTimer
            {
                name        : "enableUnitTimer",
                displayName : "Enable Unit Timer",
                description : 'Enables the eQEP module unit timer.',
                hidden      : false,
                default     : false
            },
            {
                name        : "unitTimerPeriod",
                displayName : "Unit Timer Period",
                description : "Period value at which a unit time-out interrupt is set.",
                hidden      : false,
                default     : 0
            },
            {
                name        : "unitTimerValNS",
                displayName : "Unit Timer Period [ns]",
                description : "Value of Unit Timer in nanoseconds.",
                getValue    : (inst) => 
                {
                    return ((inst.unitTimerPeriod / Common.getSYSCLK()) * 1000);
                },
                default     : 0
            },
        ]
    },
    
    {
        name            : "GROUP_WATCHDOG",
        displayName     : "EQEP Watchdog Timer",
        description     : "",
        longDescription : "",
        config          : [
            // enableWatchDog / disableWatchdog
            {
                name        : "enableWatchdog",
                displayName : "Enable EQEP Watchdog",
                description : "Enables the eQEP module watchdog timer.",
                hidden      : false,
                default     : false
            },
            {
                name        : "watchdogTimerPeriod",
                displayName : "EQEP Watchdog Timer Period",
                description : "Watchdog period value at which a time-out will occur if no quadrature-clock event is detected.",
                hidden      : false,
                default     : 0
            },
            // setWatchdogTimerValue
            {
                name        : "watchdogTimerValue",
                displayName : "EQEP Watchdog Timer Value",
                description : "Sets the eQEP module watchdog timer value.",
                hidden      : false,
                default     : 0
            },
            {
                name        : "watchdogTimerValueNS",
                displayName : "EQEP Watchdog Timer Value [ns]",
                description : "Value of EQEP Watchdog Timer in nanoseconds.",
                getValue    : (inst) => 
                {
                    return ((1 / Common.getSYSCLK()) * 1000);
                },
                default     : 0
            },
        ]
    },
    {
        name            : "GROUP_INTERRUPTS",
        displayName     : "Interrupts",
        description     : "",
        longDescription : "",
        config          : [
            // use & register interrupt
            {
                name        : "useInterrupts",
                displayName : "Use Interrupt",
                onChange    : onChangeUseInterrupts,
                description : 'Whether or not to use Interrupt mode.',
                hidden      : false,
                default     : true
            },
            {
                name        : "registerInterrupts",
                displayName : "Register Interrupt Handler",
                description : 'Whether or not to register interrupt handlers in the interrupt module.',
                hidden      : false,
                default     : false
            },
            // enableInterrupt / disableInterrupt
            {
                name        : "enableInterrupt",
                displayName : "Enable Interrupt",
                description : 'Enables interrupt source.',
                hidden      : false,
                default     : false
            },
            {
                name        : "interruptSources",
                displayName : "Interrupt Sources",
                description : "The interrupt sources to be enabled.",
                hidden      : false,
                default     : [],
                minSelections: 0,
                options     : device_driverlib_peripheral.EQEP_INT 
            },
        ]
    },
    
    // setEmulationMode
    {
        name        : "emulationMode",
        displayName : "Emulation Mode",
        description : "Set the emulation mode of the eQEP module.",
        hidden      : false,
        default     : device_driverlib_peripheral.EQEP_EmulationMode[0].name,
        options     : device_driverlib_peripheral.EQEP_EmulationMode
    },
]);
if (device_driverlib_peripheral.EQEP_QMAMode){
//(["F28004x","F28002x","F28003x","F280013x","F280015x","F2838x", "F28P65x"].includes(Common.getDeviceName())){ //Replace to make generic
    config.push(
        // setQMAModuleMode
        {
            name        : "qmaModuleMode",
            displayName : "QMA Module Mode",
            description : "Set the quadrature mode adapter (QMA) module mode.",
            hidden      : false,
            default     : device_driverlib_peripheral.EQEP_QMAMode[0].name,
            options     : device_driverlib_peripheral.EQEP_QMAMode
        },
    )
}
if (device_driverlib_peripheral.EQEP_Source){
//(["F28002x","F28003x","F280013x","F280015x","F2838x", "F28P65x"].includes(Common.getDeviceName())){
    config.push(
        
        // selectSource
        {
            name        : "selectSourceA",
            displayName : "QEPA Source",
            description : "Selects the source for QEPA signal.",
            hidden      : false,
            default     : device_driverlib_peripheral.EQEP_Source[0].name,
            options     : device_driverlib_peripheral.EQEP_Source
        },
        {
            name        : "selectSourceB",
            displayName : "QEPB Source",
            description : "Selects the source for QEPB signal.",
            hidden      : false,
            default     : device_driverlib_peripheral.EQEP_Source[0].name,
            options     : device_driverlib_peripheral.EQEP_Source
        },
        {
            name        : "selectSourceIndex",
            displayName : "QEPI/Index Source",
            description : "Selects the source for Index signal.",
            hidden      : false,
            default     : device_driverlib_peripheral.EQEP_Source[0].name,
            options     : device_driverlib_peripheral.EQEP_Source
        },
    )
}
if (device_driverlib_peripheral.EQEP_StrobeSource){
    //(["F28004x","F28002x","F28003x","F280013x","F280015x","F2838x", "F28P65x"].includes(Common.getDeviceName())){
   config.push(
       // setStrobeSource
       {
        name        : "strobeSource",
        displayName : "Strobe Source",
        description : "Set the strobe input source of the eQEP module.",
        hidden      : false,
        default     : device_driverlib_peripheral.EQEP_StrobeSource[0].name,
        options     : device_driverlib_peripheral.EQEP_StrobeSource
    },
   )
}

var useCaseConfig = {
    name: "useCase",
    displayName : "Pinmux Use Case",
    description : 'Peripheral use case',
    hidden      : false,
    default     : 'ALL',
    options     : Pinmux.getPeripheralUseCaseNames("EQEP"),
    onChange    : Pinmux.useCaseChanged,
}

useCaseConfig.options = useCaseConfig.options.concat(Pinmux.getAdditionalUseCaseNameConfigsNotInDeviceData("EQEP"))

config.push(
    useCaseConfig
)

function onValidate(inst, validation) {
    /* Validate Position Counter Max up to 32 bit unsigned int */
    if (inst.positionCounterMax < 0 || inst.positionCounterMax > 4294967295)
    {
        validation.logError(
            "Enter an integer for Position Counter Maximum between 0 and 4,294,967,295!", 
            inst, "positionCounterMax");
    }
    if (!Number.isInteger(inst.positionCounterMax))
    {
        validation.logError(
            "Position Counter Maximum must be an integer", 
            inst, "positionCounterMax");
    }

    /* Validate Position Counter Initialization Value up to 32 bit unsigned int */
    if (inst.initialPosition < 0 || inst.initialPosition > 4294967295)
    {
        validation.logError(
            "Enter an integer for Position Counter Initialization Value between 0 and 4,294,967,295!", 
            inst, "initialPosition");
    }
    if (!Number.isInteger(inst.initialPosition))
    {
        validation.logError(
            "Position Counter Initialization Value must be an integer", 
            inst, "initialPosition");
    }
    
    /* Validate Unit Timer Period up to 32 bit unsigned int */
    if (inst.unitTimerPeriod < 0 || inst.unitTimerPeriod > 4294967295)
    {
        validation.logError(
            "Enter an integer for Unit Timer Period between 0 and 4,294,967,295!", 
            inst, "unitTimerPeriod");
    }
    if (!Number.isInteger(inst.unitTimerPeriod))
    {
        validation.logError(
            "Unit Timer Period must be an integer", 
            inst, "unitTimerPeriod");
    }

    /* Validate Encoder Position up to 32 bit unsigned int */
    if (inst.setPosition < 0 || inst.setPosition > 4294967295)
    {
        validation.logError(
            "Enter an integer for Encoder Position between 0 and 4,294,967,295!", 
            inst, "setPosition");
    }
    if (!Number.isInteger(inst.setPosition))
    {
        validation.logError(
            "Encoder Position must be an integer", 
            inst, "setPosition");
    }
    
    /* Validate Watchdog Timer Period up to 16 bit unsigned int */
    if (inst.watchdogTimerPeriod < 0 || inst.watchdogTimerPeriod > 65535)
    {
        validation.logError(
            "Enter an integer for EQEP Watchdog Timer Period between 0 and 65,535!", 
            inst, "watchdogTimerPeriod");
    }
    if (!Number.isInteger(inst.watchdogTimerPeriod))
    {
        validation.logError(
            "EQEP Watchdog Timer Period must be an integer", 
            inst, "watchdogTimerPeriod");
    }
    
    /* Validate Watchdog Timer Value up to 16 bit unsigned int */
    if (inst.watchdogTimerValue < 0 || inst.watchdogTimerValue > 65535)
    {
        validation.logError(
            "Enter an integer for EQEP Watchdog Timer Value between 0 and 65,535!", 
            inst, "watchdogTimerValue");
    }
    if (!Number.isInteger(inst.watchdogTimerValue))
    {
        validation.logError(
            "EQEP Watchdog Timer Value must be an integer", 
            inst, "watchdogTimerValue");
    }

    /* Validate Compare Value up to 32 bit unsigned int */
    if (inst.compareValue < 0 || inst.compareValue > 4294967295)
    {
        validation.logError(
            "Enter an integer for Compare Value between 0 and 4,294,967,295!", 
            inst, "compareValue");
    }
    if (!Number.isInteger(inst.compareValue))
    {
        validation.logError(
            "Compare Value between must be an integer", 
            inst, "compareValue");
    }

    /* Validate Compare Cycles up to 16 bit unsigned int */
    if (inst.compareCycles < 0 || inst.compareCycles > 65535)
    {
        validation.logError(
            "Enter an integer for Compare Cycles between 0 and 65,535!", 
            inst, "compareCycles");
    }
    if (!Number.isInteger(inst.compareCycles))
    {
        validation.logError(
            "Compare Cycles must be an integer", 
            inst, "compareCycles");
    }

    var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("EQEP", inst)
    for (var pinmuxQualMod of pinmuxQualMods)
    {
        if (inst[pinmuxQualMod.name].qualMode == "GPIO_QUAL_ASYNC")
        {
            validation.logError("The asynchronous mode should not be used for eQEP input pins.", inst);
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
    return (Common.typeMatches(component.type, ["EQEP"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var eqepModule = {
    peripheralName: "EQEP",
    displayName: "EQEP",
    maxInstances: Common.peripheralCount("EQEP"),
    defaultInstanceName: "myEQEP",
    description: "Enhanced Quadrature Encoder Peripheral",
    // longDescription: longDescription,
    longDescription: longDescription + "\n" + (Common.getCollateralFindabilityList("EQEP")),
    filterHardware : filterHardware,
    config: config,
    moduleInstances: (inst) => {
        var ownedInstances = []
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("EQEP", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.args.qualMode = "GPIO_QUAL_SYNC";
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)
        
        if (inst.useInterrupts && inst.registerInterrupts)
        {
	        ownedInstances = ownedInstances.concat([{
                name: "eqepInt",      
                displayName: "EQEP Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
            		$name : inst.$name + "_INT",
                    int : "INT_" + inst.$name,
                    pinmuxPeripheralModule : "eqep",
                    driverlibInt: "INT_#"
                }
            }])
        }
    	return ownedInstances;
    },
    templates: {
        boardc : "/driverlib/eqep/eqep.board.c.xdt",
        boardh : "/driverlib/eqep/eqep.board.h.xdt"
    },
    validate    : onValidate,
    pinmuxRequirements    : Pinmux.eqepPinmuxRequirements
};


if (eqepModule.maxInstances <= 0)
{
    delete eqepModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(eqepModule)
    Pinmux.addPinMuxQualGroupToConfig(eqepModule)
}


exports = eqepModule;