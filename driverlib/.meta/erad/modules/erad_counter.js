let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_erad.js");

let CTM_MODES = [
    {name: "0", displayName: "Counter Mode"},
    {name: "1", displayName: "Stopwatch Mode"}
];
if(["F2838x", "F28002x", "F28003x"].includes(system.deviceData.deviceId))
{
    CTM_MODES.push({name: "3", displayName: "Cumulative Mode"})
}

let CLOCK_SOURCE = [
    {name: "0", displayName: "CPU Cycles as source"},
    {name: "1", displayName: "External events as source"}
];

let COUNT_MODE= [
    {name: "ERAD_COUNTER_MODE_RISING_EDGE", displayName: "Count Rising Edges"},
    {name: "ERAD_COUNTER_MODE_ACTIVE", displayName: "Count CPU cycles"}
];

let COUNTER_MODES = [
    {name: "true", displayName: "Reset on match"},
    {name: "false", displayName: "Continuous Mode"}
];

let COMMON_SIGNAL_SOURCES = [
    { name: "ERAD_EVENT_HWBP1", displayName: "BUSCOMP1"},
    { name: "ERAD_EVENT_HWBP2", displayName: "BUSCOMP2"},
    { name: "ERAD_EVENT_HWBP3", displayName: "BUSCOMP3"},
    { name: "ERAD_EVENT_HWBP4", displayName: "BUSCOMP4"},
    { name: "ERAD_EVENT_HWBP5", displayName: "BUSCOMP5"},
    { name: "ERAD_EVENT_HWBP6", displayName: "BUSCOMP6"},
    { name: "ERAD_EVENT_HWBP7", displayName: "BUSCOMP7"},
    { name: "ERAD_EVENT_HWBP8", displayName: "BUSCOMP8"},
    { name: "ERAD_EVENT_COUNTER1", displayName: "COUNTER1 EVENT"},
    { name: "ERAD_EVENT_COUNTER2", displayName: "COUNTER2 EVENT"},
    { name: "ERAD_EVENT_COUNTER3", displayName: "COUNTER3 EVENT"},
    { name: "ERAD_EVENT_COUNTER4", displayName: "COUNTER4 EVENT"},
    { name: "ERAD_EVENT_PIE_INT1", displayName: "PIE INT1"},
    { name: "ERAD_EVENT_PIE_INT2", displayName: "PIE INT2"},
    { name: "ERAD_EVENT_PIE_INT3", displayName: "PIE INT3"},
    { name: "ERAD_EVENT_PIE_INT4", displayName: "PIE INT4"},
    { name: "ERAD_EVENT_PIE_INT5", displayName: "PIE INT5"},
    { name: "ERAD_EVENT_PIE_INT6", displayName: "PIE INT6"},
    { name: "ERAD_EVENT_PIE_INT7", displayName: "PIE INT7"},
    { name: "ERAD_EVENT_PIE_INT8", displayName: "PIE INT8"},
    { name: "ERAD_EVENT_PIE_INT9", displayName: "PIE INT9"},
    { name: "ERAD_EVENT_PIE_INT10", displayName: "PIE INT10"},
    { name: "ERAD_EVENT_PIE_INT11", displayName: "PIE INT11"},
    { name: "ERAD_EVENT_PIE_INT12", displayName: "PIE INT12"},
    { name: "ERAD_EVENT_TIMER1_TINT1", displayName: "TIMER1 TINT1"},
    { name: "ERAD_EVENT_TIMER2_TINT2", displayName: "TIMER2 TINT2"},
    { name: "ERAD_EVENT_CLA_INTERRUPT1", displayName: "CLA INTERRUPT1"},
    { name: "ERAD_EVENT_CLA_INTERRUPT2", displayName: "CLA INTERRUPT2"},
    { name: "ERAD_EVENT_CLA_INTERRUPT3", displayName: "CLA INTERRUPT3"},
    { name: "ERAD_EVENT_CLA_INTERRUPT4", displayName: "CLA INTERRUPT4"},
    { name: "ERAD_EVENT_CLA_INTERRUPT5", displayName: "CLA INTERRUPT5"},
    { name: "ERAD_EVENT_CLA_INTERRUPT8", displayName: "CLA INTERRUPT8"}
]

function onChangeCTMMode(inst, ui)
{   
    for (var config_i in stopwatchModeConfig)
    {
        ui[stopwatchModeConfig[config_i].name].hidden = (inst.ctmMode == CTM_MODES[0].name);
    }
    for (var config_i in counterModeConfig)
    {
        ui[counterModeConfig[config_i].name].hidden = !(inst.ctmMode == CTM_MODES[0].name);
    }
}

function onChangeClockSource(inst, ui)
{
    ui.externalClockSource.hidden = (inst.clockSource == CLOCK_SOURCE[0].name);
    ui.countMode.hidden = (inst.clockSource == CLOCK_SOURCE[0].name);
}

function onChangeUseExternalResetSource(inst, ui)
{
    ui.externalResetSource.hidden = !inst.useExternalResetSource;
}

var config = [
    {
        name: "ctmMode",
        displayName : "ERAD CTM Mode",
        description : 'Mode of the CTM Module',
        hidden      : false,
        default     : CTM_MODES[0].name,
        options     : CTM_MODES,
        onChange    : onChangeCTMMode
    }
];

var counterModeConfig = [
    {
        name        : "counterPeriod",
        displayName : "Counter Period",
        description : "The reference value for the counter to count up to!",
        default     : 0 
    },
    {
        name        : "counterMode",
        displayName : "Reset Counter on Match",
        description : "Wether or not to reset the Counter when the COUNT matches the REF value",
        default     : false,
        hidden      : false
    }
]

var stopwatchModeConfig = [
    {
        name        : "swStart",
        displayName : "Start Event Signal",
        description : "The source to start the counter in order to increment on the clock source!",
        default     : device_driverlib_peripheral.ERAD_Counter_Input_Event[0].name,
        options     : device_driverlib_peripheral.ERAD_Counter_Input_Event,
        hidden      : true
    },
    {
        name        : "swStop",
        displayName : "Stop Event Signal",
        description : "The source to stop the counter.",
        default     : device_driverlib_peripheral.ERAD_Counter_Input_Event[0].name,
        options     : device_driverlib_peripheral.ERAD_Counter_Input_Event,
        hidden      : true
    },
    {
        name        : "swReferenceCount",
        displayName : "Reference Counter Value",
        description : "The reference value for the counter to generate a HALT or Interrupt!",
        default     : 0,
        hidden      : true
    },
]

var commonConfig = [
    {
        name        : "clockSource",
        displayName : "Clock Source",
        description : "The clock source used for incrementing the counter",
        default     : CLOCK_SOURCE[0].name,
        options     : CLOCK_SOURCE,
        onChange    : onChangeClockSource
    },
    {
        name        : "externalClockSource",
        displayName : "External Clock Source",
        description : "The clock source used for incrementing the counter from external signals rising edge",
        default     : device_driverlib_peripheral.ERAD_Counter_Input_Event[0].name,
        options     : device_driverlib_peripheral.ERAD_Counter_Input_Event,
        hidden      : true
    },
    {
        name        : "countMode",
        displayName : "Count Mode",
        description : "Choose to count Rising edges or Active duration",
        default     : COUNT_MODE[0].name,
        options     : COUNT_MODE,
        hidden      : true
    },
    {
        name        : "useExternalResetSource",
        displayName : "Use an External Reset Source",
        description : "Whether or not to use an external reset source for the counter",
        default     : false,
        onChange    : onChangeUseExternalResetSource,
        hidden      : false
    },
    {
        name        : "externalResetSource",
        displayName : "External Reset Source",
        description : "The reset source used to set the counter to 0, coming from external signals rising edge",
        default     : device_driverlib_peripheral.ERAD_Counter_Input_Event[0].name,
        options     : device_driverlib_peripheral.ERAD_Counter_Input_Event,
        hidden      : true
    },
    {
        name        : "haltCPU",
        displayName : "Halt CPU on Count Match",
        description : "Wether or not to halt the CPU when the COUNT matches the REF value",
        default     : false
    },
    {
        name        : "rtosInterrupt",
        displayName : "Generate RTOS Interrupt on Count Match",
        description : "Wether or not to generate RTOS interrupt when the COUNT matches the REF value",
        default     : false
    }
]
if(["F2838x", "F28002x", "F28003x"].includes(system.deviceData.deviceId))
{
    commonConfig.push({
        name        : "NMIInterrupt",
        displayName : "Generate NMI Interrupt on Match",
        description : "Wether or not to generate NMI interrupt when the HWBP matches the REF value",
        default     : false})
}

config = config.concat(counterModeConfig);
config = config.concat(stopwatchModeConfig);
config = config.concat(commonConfig);


var eradCTMSubmodule = {
    displayName: "ERAD CTM",
    maxInstances: 4,
    defaultInstanceName: "ERAD_CTM",
    description: "ERAD Counter",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};


exports = eradCTMSubmodule;