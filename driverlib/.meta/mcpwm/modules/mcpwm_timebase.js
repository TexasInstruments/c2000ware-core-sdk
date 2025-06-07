let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_mcpwm.js");
// let device_driverlib_hrpwm = 
//     system.getScript("/driverlib/device_driverlib_peripherals/" + 
//         Common.getDeviceName().toLowerCase() + "_hrpwm.js");


function onChangeEnableDisable(inst, ui)
{
    if (inst.mcpwmTimebase_phaseEnable == true)
    {
        ui.mcpwmTimebase_phaseShift.hidden = false;
    }
    else if (inst.mcpwmTimebase_phaseEnable == false)
    {
        ui.mcpwmTimebase_phaseShift.hidden = true;
        inst.mcpwmTimebase_phaseShift = 0; // Set default
    }

    if (inst.mcpwmTimebase_counterMode == "MCPWM_COUNTER_MODE_UP_DOWN")
    {
        ui.mcpwmTimebase_counterModeAfterSync.hidden = false;
    }
    else if (inst.mcpwmTimebase_counterMode == "MCPWM_COUNTER_MODE_UP" || 
        inst.mcpwmTimebase_counterMode =="MCPWM_COUNTER_MODE_DOWN" ||
        inst.mcpwmTimebase_counterMode == "MCPWM_COUNTER_MODE_STOP_FREEZE")
    {
        ui.mcpwmTimebase_counterModeAfterSync.hidden = true;
        inst.mcpwmTimebase_counterModeAfterSync = device_driverlib_peripheral.MCPWM_SyncCountMode[0].name;
    }
}

var config = [
    {
        name        : "mcpwmTimebase_emulationMode",
        displayName : "Emulation Mode",
        description : 'Behavior of the ePWM time-base counter during emulation events',
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_EmulationMode[0].name,
        options     : device_driverlib_peripheral.MCPWM_EmulationMode
    },
    {
        name: "mcpwmTimebase_clockDiv",
        displayName : "Time Base Clock Divider",
        description : 'CLKDIV: These bits select the time base clock pre-scale value, TBCLK = EPWMCLK/(HSPCLKDIV*CLKDIV)',
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_ClockDivider[0].name,
        options     : device_driverlib_peripheral.MCPWM_ClockDivider,
    },
    {
        name: "mcpwmTimebase_periodLoadMode", 
        displayName : "Time Base Period Load Mode",
        description : 'Period load mode for the Time Base Counter Submodule',
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_PeriodLoadMode[0].name,
        options     : device_driverlib_peripheral.MCPWM_PeriodLoadMode,
        onChange    : onChangeEnableDisable
    },
    {
        name: "mcpwmTimebase_period",
        displayName : "Time Base Period",
        description : 'Period for the Time Base Counter Submodule',
        hidden      : false,
        default     : 0,
    },
    {
        name: "mcpwmTimebase_counterMode",
        displayName : "Counter Mode",
        description : 'Mode of the Counter value for the Time Base Counter Submodule',
        hidden      : false,
        default     : "MCPWM_COUNTER_MODE_STOP_FREEZE",
        options     : device_driverlib_peripheral.MCPWM_TimeBaseCountMode,
        onChange    : onChangeEnableDisable
    },
    {
        name: "mcpwmTimebase_counterModeAfterSync",
        displayName : 'Counter Mode After Sync',
        description : 'The direction the time-base counter (TBCTR) will count after a synchronization event occurs',
        hidden      : true,
        default     : device_driverlib_peripheral.MCPWM_SyncCountMode[0].name,
        options     : device_driverlib_peripheral.MCPWM_SyncCountMode,
    },
    {
        name: "mcpwmTimebase_phaseEnable",
        displayName : "Enable Phase Shift Load",
        description : 'Enable phase shift load for the Time Base Counter Submodule',
        hidden      : false,
        default     : false,
        onChange    : onChangeEnableDisable
    },
    {
        name: "mcpwmTimebase_phaseShift",
        displayName : 'Phase Shift Value',
        description : 'Phase Shift Value for the Time Base Counter Submodule',
        hidden      : true,
        default     : 0,
    },
    {
        name: "mcpwmTimebase_forceSyncPulse",
        displayName : 'Force a Sync Pulse',
        description : 'Force a sync pulse for the Time Base Counter Submodule',
        hidden      : false,
        default     : false,
    },
    {
        name: "mcpwmTimebase_syncInPulseSource",
        displayName : "Sync In Pulse Source",
        description : 'Sync in Pulse for the Time Base Counter Submodule',
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_SyncInPulseSource[0].name,
        options     : device_driverlib_peripheral.MCPWM_SyncInPulseSource,
    },
    {
        name: "mcpwmTimebase_syncOutPulseMode",
        displayName : "Sync Out Pulse",
        description : 'Sync Out Pulse for the Time Base Counter Submodule',
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_SyncOutPulseMode[0].name,
        options     : device_driverlib_peripheral.MCPWM_SyncOutPulseMode
    },
    {
        name: "hrpwm_syncSource",
        displayName : "MCPWMxSYNCPER Source Select",
        description : 'Selects the source of the MCPWMSYNCPER signal that goes to the CMPSS and GPDAC',
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_SyncPulseSource[0].name,
        options     : device_driverlib_peripheral.MCPWM_SyncPulseSource
    },
];

var epwmTimebaseSubmodule = {
    displayName: "MCPWM Time Base",
    maxInstances: Common.peripheralCount("mcpwm"),
    defaultInstanceName: "MCPWM_TB",
    description: "Enhanced Pulse Width Modulator Time Base Counter",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};


exports = epwmTimebaseSubmodule;
