let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_mcpwm.js");

function onChangeCMPXShadowLoadMode(inst, ui)
{
    // CMPA
    if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPA == true)
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPA.hidden = false;
    }
    else if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPA == false)    
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPA.hidden = true;
        inst.mcpwmCounterCompare_shadowLoadModeCMPA = device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name; 
    }
    if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPA_pwm2 == true)
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPA_pwm2.hidden = false;
    }
    else if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPA_pwm2 == false)    
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPA_pwm2.hidden = true;
        inst.mcpwmCounterCompare_shadowLoadModeCMPA_pwm2 = device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name; 
    }
    if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPA_pwm3 == true)
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPA_pwm3.hidden = false;
    }
    else if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPA_pwm3 == false)    
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPA_pwm3.hidden = true;
        inst.mcpwmCounterCompare_shadowLoadModeCMPA_pwm3 = device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name; 
    }
    

    // CMPB
    if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPB == true)
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPB.hidden = false;
    }
    else if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPB == false)    
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPB.hidden = true;
        inst.mcpwmCounterCompare_shadowLoadModeCMPB = device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name; 
    }
    if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPB_pwm2 == true)
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPB_pwm2.hidden = false;
    }
    else if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPB_pwm2 == false)    
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPB_pwm2.hidden = true;
        inst.mcpwmCounterCompare_shadowLoadModeCMPB_pwm2 = device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name; 
    }
    if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPB_pwm3 == true)
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPB_pwm3.hidden = false;
    }
    else if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPB_pwm3 == false)    
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPB_pwm3.hidden = true;
        inst.mcpwmCounterCompare_shadowLoadModeCMPB_pwm3 = device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name; 
    }

    // CMPC
    if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPC == true)
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPC.hidden = false;
    }
    else if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPC == false)    
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPC.hidden = true;
        inst.mcpwmCounterCompare_shadowLoadModeCMPC = device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name;
    }

    // CMPD
    if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPD == true)
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPD.hidden = false;
    }
    else if (inst.mcpwmCounterCompare_enableShadowLoadModeCMPD == false)    
    {
        ui.mcpwmCounterCompare_shadowLoadModeCMPD.hidden = true;
        inst.mcpwmCounterCompare_shadowLoadModeCMPD = device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name;
    }

}

/* Array of CAN configurables that are common across device families */
var config = [
    {
        name: "GROUP_CMPA_PWM1",
        displayName: "CMPA PWM1",
        description: "",
        longDescription: "",
        config: [
            {
                name: "mcpwmCounterCompare_cmpA",
                displayName : "Counter Compare A (CMPA)",
                description : 'Counter Compare A (CMPA) value',
                hidden      : false,
                default     : 0,
            },
            // {
            //     name: "mcpwmCounterCompare_cmpAGld",
            //     displayName : "Enable Counter Compare A (CMPA) Global Load",
            //     description : 'Use global load configuration for CMPA',
            //     hidden      : false,
            //     default     : false,
            // },
            {
                name: "mcpwmCounterCompare_enableShadowLoadModeCMPA",
                displayName : "Enable Shadow Counter Compare A (CMPA)",
                description : 'Enable Shadow Counter Compare A (CMPA) value',
                hidden      : false,
                default     : true,
                onChange    : onChangeCMPXShadowLoadMode
            },
            {
                name: "mcpwmCounterCompare_shadowLoadModeCMPA",
                displayName : "Counter Compare A Shadow Load Event",
                description : 'Counter Compare A Shadow Load Event',
                hidden      : false,
                default     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name,
                options     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode,
            },
            // {
            //     name: "mcpwmCounterCompare_cmpALink",
            //     displayName : "Counter Compare A (CMPA) Link",
            //     description : 'Simultaneous write to the current ePWM module CMPA register',
            //     hidden      : false,
            //     default     : device_driverlib_peripheral.MCPWM_CurrentLink[0].name,
            //     options     : device_driverlib_peripheral.MCPWM_CurrentLink,
            // }
        ]
    },
    {
        name: "GROUP_CMPB_PWM1",
        displayName: "CMPB PWM1",
        description: "",
        longDescription: "",
        config: [
            {
                name: "mcpwmCounterCompare_cmpB",
                displayName : "Counter Compare B (CMPB)",
                description : 'Counter Compare B (CMPB) value',
                hidden      : false,
                default     : 0,
            },
            // {
            //     name: "mcpwmCounterCompare_cmpBGld",
            //     displayName : "Enable Counter Compare B (CMPB) Global Load",
            //     description : 'Use global load configuration for CMPB',
            //     hidden      : false,
            //     default     : false,
            // },
            {
                name: "mcpwmCounterCompare_enableShadowLoadModeCMPB",
                displayName : "Enable Shadow Counter Compare B (CMPB)",
                description : 'Enable Shadow Counter Compare B (CMPB) value',
                hidden      : false,
                default     : true,
                onChange    : onChangeCMPXShadowLoadMode
            },
            {
                name: "mcpwmCounterCompare_shadowLoadModeCMPB",
                displayName : "Counter Compare B Shadow Load Event",
                description : 'Counter Compare B Shadow Load Event',
                hidden      : false,
                default     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name,
                options     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode,
            },
            // {
            //     name: "mcpwmCounterCompare_cmpBLink",
            //     displayName : "Counter Compare B (CMPB) Link",
            //     description : 'Simultaneous write to the current ePWM module CMPB register',
            //     hidden      : false,
            //     default     : device_driverlib_peripheral.MCPWM_CurrentLink[0].name,
            //     options     : device_driverlib_peripheral.MCPWM_CurrentLink,
            // }
        ]
    },
    {
        name: "GROUP_CMPA_PWM2",
        displayName: "CMPA PWM2",
        description: "",
        longDescription: "",
        config: [
            {
                name: "mcpwmCounterCompare_cmpA_pwm2",
                displayName : "Counter Compare A (CMPA)",
                description : 'Counter Compare A (CMPA) value',
                hidden      : false,
                default     : 0,
            },
            {
                name: "mcpwmCounterCompare_enableShadowLoadModeCMPA_pwm2",
                displayName : "Enable Shadow Counter Compare A (CMPA)",
                description : 'Enable Shadow Counter Compare A (CMPA) value',
                hidden      : false,
                default     : true,
                onChange    : onChangeCMPXShadowLoadMode
            },
            {
                name: "mcpwmCounterCompare_shadowLoadModeCMPA_pwm2",
                displayName : "Counter Compare A Shadow Load Event",
                description : 'Counter Compare A Shadow Load Event',
                hidden      : false,
                default     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name,
                options     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode,
            },
        ]
    },
    {
        name: "GROUP_CMPB_PWM2",
        displayName: "CMPB PWM2",
        description: "",
        longDescription: "",
        config: [
            {
                name: "mcpwmCounterCompare_cmpB_pwm2",
                displayName : "Counter Compare A (CMPB)",
                description : 'Counter Compare A (CMPB) value',
                hidden      : false,
                default     : 0,
            },
            {
                name: "mcpwmCounterCompare_enableShadowLoadModeCMPB_pwm2",
                displayName : "Enable Shadow Counter Compare A (CMPB)",
                description : 'Enable Shadow Counter Compare A (CMPB) value',
                hidden      : false,
                default     : true,
                onChange    : onChangeCMPXShadowLoadMode
            },
            {
                name: "mcpwmCounterCompare_shadowLoadModeCMPB_pwm2",
                displayName : "Counter Compare B Shadow Load Event",
                description : 'Counter Compare B Shadow Load Event',
                hidden      : false,
                default     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name,
                options     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode,
            },
        ]
    },  
    {
        name: "GROUP_CMPA_PWM3",
        displayName: "CMPA PWM3",
        description: "",
        longDescription: "",
        config: [
            {
                name: "mcpwmCounterCompare_cmpA_pwm3",
                displayName : "Counter Compare A (CMPA)",
                description : 'Counter Compare A (CMPA) value',
                hidden      : false,
                default     : 0,
            },
            {
                name: "mcpwmCounterCompare_enableShadowLoadModeCMPA_pwm3",
                displayName : "Enable Shadow Counter Compare A (CMPA)",
                description : 'Enable Shadow Counter Compare A (CMPA) value',
                hidden      : false,
                default     : true,
                onChange    : onChangeCMPXShadowLoadMode
            },
            {
                name: "mcpwmCounterCompare_shadowLoadModeCMPA_pwm3",
                displayName : "Counter Compare A Shadow Load Event",
                description : 'Counter Compare A Shadow Load Event',
                hidden      : false,
                default     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name,
                options     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode,
            },
        ]
    },
    {
        name: "GROUP_CMPB_PWM3",
        displayName: "CMPB PWM3",
        description: "",
        longDescription: "",
        config: [
            {
                name: "mcpwmCounterCompare_cmpB_pwm3",
                displayName : "Counter Compare A (CMPB)",
                description : 'Counter Compare A (CMPB) value',
                hidden      : false,
                default     : 0,
            },
            {
                name: "mcpwmCounterCompare_enableShadowLoadModeCMPB_pwm3",
                displayName : "Enable Shadow Counter Compare A (CMPB)",
                description : 'Enable Shadow Counter Compare A (CMPB) value',
                hidden      : false,
                default     : true,
                onChange    : onChangeCMPXShadowLoadMode
            },
            {
                name: "mcpwmCounterCompare_shadowLoadModeCMPB_pwm3",
                displayName : "Counter Compare B Shadow Load Event",
                description : 'Counter Compare B Shadow Load Event',
                hidden      : false,
                default     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name,
                options     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode,
            },
        ]
    },   
    {
        name: "GROUP_CMPC",
        displayName: "CMPC",
        description: "",
        longDescription: "",
        config: [
            {
                name: "mcpwmCounterCompare_cmpC",
                displayName : "Counter Compare C (CMPC)",
                description : 'Counter Compare C (CMPC) value',
                hidden      : false,
                default     : 0,
            },
            // {
            //     name: "mcpwmCounterCompare_cmpCGld",
            //     displayName : "Enable Counter Compare C (CMPC) Global Load",
            //     description : 'Use global load configuration for CMPC',
            //     hidden      : false,
            //     default     : false,
            // },
            {
                name: "mcpwmCounterCompare_enableShadowLoadModeCMPC",
                displayName : "Enable Shadow Counter Compare C (CMPC)",
                description : 'Enable Shadow Counter Compare C (CMPC) value',
                hidden      : false,
                default     : true,
                onChange    : onChangeCMPXShadowLoadMode
            },
            {
                name: "mcpwmCounterCompare_shadowLoadModeCMPC",
                displayName : "Counter Compare C Shadow Load Event",
                description : 'Counter Compare C Shadow Load Event',
                hidden      : false,
                default     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name,
                options     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode,
            },
            // {
            //     name: "mcpwmCounterCompare_cmpCLink",
            //     displayName : "Counter Compare C (CMPC) Link",
            //     description : 'Simultaneous write to the current ePWM module CMPC register',
            //     hidden      : false,
            //     default     : device_driverlib_peripheral.MCPWM_CurrentLink[0].name,
            //     options     : device_driverlib_peripheral.MCPWM_CurrentLink,
            // }
        ]
    },
    {
        name: "GROUP_CMPD",
        displayName: "CMPD",
        description: "",
        longDescription: "",
        config: [
            {
                name: "mcpwmCounterCompare_cmpD",
                displayName : "Counter Compare D (CMPD)",
                description : 'Counter Compare D (CMPD) value',
                hidden      : false,
                default     : 0,
            },
            // {
            //     name: "mcpwmCounterCompare_cmpDGld",
            //     displayName : "Enable Counter Compare D (CMPD) Global Load",
            //     description : 'Use global load configuration for CMPD',
            //     hidden      : false,
            //     default     : false,
            // },
            {
                name: "mcpwmCounterCompare_enableShadowLoadModeCMPD",
                displayName : "Enable Shadow Counter Compare D (CMPD)",
                description : 'Enable Shadow Counter Compare D (CMPD) value',
                hidden      : false,
                default     : true,
                onChange    : onChangeCMPXShadowLoadMode
            },
            {
                name: "mcpwmCounterCompare_shadowLoadModeCMPD",
                displayName : "Counter Compare D Shadow Load Event",
                description : 'Counter Compare D Shadow Load Event',
                hidden      : false,
                default     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode[0].name,
                options     : device_driverlib_peripheral.MCPWM_CounterCompareLoadMode,
            },
            // {
            //     name: "mcpwmCounterCompare_cmpDLink",
            //     displayName : "Counter Compare D (CMPD) Link",
            //     description : 'Simultaneous write to the current ePWM module CMPD register',
            //     hidden      : false,
            //     default     : device_driverlib_peripheral.MCPWM_CurrentLink[0].name,
            //     options     : device_driverlib_peripheral.MCPWM_CurrentLink,
            // }
        ]
    },
];



var epwmCCSubmodule = {
    displayName: "MCPWM Counter Compare",
    maxInstances: Common.peripheralCount("mcpwm"),
    defaultInstanceName: "mcpwm_CC",
    description: "Enhanced Pulse Width Modulator Counter Compare",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};


exports = epwmCCSubmodule;