"use strict";
/*global exports, system*/
let Common   = system.getScript('/utilities/dcsm_tool/dcsm_syscfg/source/Common.js');

var ERRORSTS_options = [
    {name:0 , displayName: "GPIO24"},
    {name:1 , displayName: "GPIO28"},
    {name:2 , displayName: "GPIO29"},
    {name:3 , displayName: "ERRORSTS disabled (Default)"}
];

if ("F28P65x".includes(Common.getDeviceName()))
{
    ERRORSTS_options = [
        {name:0 , displayName: "GPIO224"},
        {name:1 , displayName: "GPIO79"},
        {name:2 , displayName: "GPIO80"},
        {name:3 , displayName: "ERRORSTS disabled (Default)"}
    ];
}

if ("F28P55x".includes(Common.getDeviceName()))
{
    ERRORSTS_options = [
        {name:0, displayName: "GPIO24"},
        {name:1, displayName: "GPIO28"},
        {name:2, displayName: "GPIO29"},
        {name:4, displayName: "GPIO55"},
        {name:5, displayName: "GPIO64"},
        {name:6, displayName: "GPIO73"},
        {name:7, displayName: "ERRORSTS disabled (Default)"}
    ];
}

var MPOST_options

if ("F28002x".includes(Common.getDeviceName()))
{
    MPOST_options = [
        {name:0 , displayName: "Run MPOST using INTOSC2 with PLL disabled (10MHz internal oscillator)"},
        {name:1 , displayName: "Run MPOST with PLL enabled for 95MHz"},
        {name:2 , displayName: "Run MPOST with PLL enabled for 47.5MHz"},
        {name:3 , displayName: "Disable MPOST"}
    ];
}
if ("F2838x".includes(Common.getDeviceName()))
{
    MPOST_options = [
        {name:0x0 , displayName: "MPOST will be run with PLL enabled for high speed (110MHz)"},
        {name:0xC , displayName: "MPOST will be run with PLL enabled for medium speed (80MHz)."},
        {name:0x3 , displayName: "MPOST will be run with PLL enabled for low speed (60MHz)"},
        {name:0x9 , displayName: "MPOST will be run using INTOSC2 with PLL disabled (10MHz)"},
        {name:0x1 , displayName: "Disable MPOST"}
    ];
}
else if ("F28003x".includes(Common.getDeviceName()))
{
    MPOST_options = [
        {name:0x0 , displayName: "MPOST will be run using INTOSC2 with PLL disabled (10MHz)"},
        {name:0x1 , displayName: "MPOST will be run with PLL enabled for high speed (115MHz)"},
        {name:0x2 , displayName: "MPOST will be run with PLL enabled for low speed (57.5MHz)"},
        {name:0x3 , displayName: "Disable MPOST"}
    ];
}
else if ("F280013x".includes(Common.getDeviceName()))
{
    MPOST_options = [
        {name:0x0 , displayName: "MPOST will be run using INTOSC2 with PLL disabled (10MHz)"},
        {name:0x1 , displayName: "MPOST will be run with PLL enabled for high speed (95MHz)"},
        {name:0x2 , displayName: "MPOST will be run with PLL enabled for low speed (47.5MHz)"},
        {name:0x3 , displayName: "Disable MPOST"}
    ];
}
else if ("F280015x".includes(Common.getDeviceName()))
{
    MPOST_options = [
        {name:0x0 , displayName: "MPOST will be run using INTOSC2 with PLL disabled (10MHz)"},
        {name:0x1 , displayName: "MPOST will be run with PLL enabled for high speed (115MHz)"},
        {name:0x2 , displayName: "MPOST will be run with PLL enabled for low speed (57.5MHz)"},
        {name:0x3 , displayName: "Disable MPOST"}
    ];
}
else if ("F28P65x".includes(Common.getDeviceName()))
{
    MPOST_options = [
        {name:0x0 , displayName: "MPOST will be run using INTOSC2 with PLL disabled (10MHz)"},
        {name:0x1 , displayName: "MPOST will be run with PLL enabled for low speed (50MHz)"},
        {name:0x2 , displayName: "MPOST will be run with PLL enabled for high speed (100MHz)"},
        {name:0x3 , displayName: "Do not run MPOST"}
    ];
}
else if ("F28P55x".includes(Common.getDeviceName()))
{
    MPOST_options = [
        {name:0x0 , displayName: "MPOST will be run using INTOSC2 with PLL disabled (10MHz)"},
        {name:0x1 , displayName: "MPOST will be run with PLL enabled for high speed (150MHz)"},
        {name:0x2 , displayName: "MPOST will be run with PLL enabled for low speed (75MHz)"},
        {name:0x3 , displayName: "Do not run MPOST"}
    ];
}




// CJTAGNODEID: Boot ROM takes this values and programs the lower 4 bits of the CJTAGNODEID register

let REALIZED_BOOT_MODE = [
    {name: 0 , displayName:"Parallel IO"},
    {name: 1 , displayName:"SCI / Wait boot"},
    {name: 2 , displayName:"CAN"},
    {name: 3 , displayName:"Flash"},
    {name: 4 , displayName:"Wait"},
    {name: 5 , displayName:"RAM"},
    {name: 6 , displayName:"SPI Master"},
    {name: 7 , displayName:"I2C Master"},
    {name: 8 , displayName:"CAN-FD"},
    {name: 9 , displayName:"USB"},
    {name: 10 , displayName:"Secure Flash"},
    {name: 11 , displayName:"FWU Flash"},
]

var ALL_BOOT_OPTIONS = [];

if ("F28004x".includes(Common.getDeviceName()))
{
    
    
    ALL_BOOT_OPTIONS = Common.getBootOptions().f28004x_boot;
    
    //console.log(ALL_BOOT_OPTIONS);
}
else if ("F28002x".includes(Common.getDeviceName()))
{
    
    
    ALL_BOOT_OPTIONS = Common.getBootOptions().f28002x_boot;
    
    //console.log(ALL_BOOT_OPTIONS);
}
else if ("F2838x".includes(Common.getDeviceName()))
{
    ALL_BOOT_OPTIONS = Common.getBootOptions().f2838x_boot; 

}

else if ("F28003x".includes(Common.getDeviceName()))
{
    ALL_BOOT_OPTIONS = Common.getBootOptions().f28003x_boot;
    
    //console.log(ALL_BOOT_OPTIONS);
}
else if ("F280013x".includes(Common.getDeviceName()))
{
    ALL_BOOT_OPTIONS = Common.getBootOptions().f280013x_boot; 
    
    //console.log(ALL_BOOT_OPTIONS);
} 
else if ("F280015x".includes(Common.getDeviceName()))
{
    ALL_BOOT_OPTIONS = Common.getBootOptions().f280015x_boot; 
    
    //console.log(ALL_BOOT_OPTIONS);
}
else if ("F28P65x".includes(Common.getDeviceName()))
{
    ALL_BOOT_OPTIONS = Common.getBootOptions().f28p65x_boot; 

    //console.log(ALL_BOOT_OPTIONS);
}

else if ("F28P55x".includes(Common.getDeviceName()))
{
    ALL_BOOT_OPTIONS = Common.getBootOptions().f28p55x_boot;

    //console.log(ALL_BOOT_OPTIONS);
}

else if ("F28E12x".includes(Common.getDeviceName()))
{
    ALL_BOOT_OPTIONS = Common.getBootOptions().f28e12x_boot;

    //console.log(ALL_BOOT_OPTIONS);
}

// Device specific options
var pin0Defaults = "GPIO32";
var pin1Defaults = "GPIO24";
if (["F2838x","F28P65x"].includes(Common.getDeviceName()))
{
    pin0Defaults = "GPIO84";
    pin1Defaults = "GPIO72";
}


/* Intro splash on GUI */
let longDescription = 'ZONE Header can ONLY be programmed once. After they are programmed they cannot be modified. ' + 
                        'This section cannot be modified by using a different LINKPOINTER value.';

var gpioOptions = [];
var gpios = Common.getGPIOs();
var unacceptableGPIOs = [];
if ("F28004x".includes(Common.getDeviceName()))
{
    unacceptableGPIOs = ["GPIO20", "GPIO21", 
                         "GPIO22", "GPIO23", 
                         "GPIO36", "GPIO38"]
    for (var i = 60; i <= 223; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
}
if ("F28002x".includes(Common.getDeviceName()))
{
    unacceptableGPIOs = ["GPIO20", "GPIO21", 
                         "GPIO36", "GPIO38"]
    for (var i = 63; i <= 223; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
}

if ("F2838x".includes(Common.getDeviceName()))
{
    unacceptableGPIOs = ["GPIO42", "GPIO43"]
    for (var i = 169; i <= 255; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
}
if ("F28003x".includes(Common.getDeviceName()))
{
    unacceptableGPIOs = ["GPIO36", "GPIO38"]
    for (var i = 62; i <= 223; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
}
if ("F280013x".includes(Common.getDeviceName()))
{
    unacceptableGPIOs = [
        "GPIO14", "GPIO15", "GPIO30", 
        "GPIO31", "GPIO34", "GPIO38"
    ]
    for (var i = 25; i <= 27; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
    for (var i = 42; i <= 58; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
    for (var i = 62; i <= 223; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
}
if ("F280015x".includes(Common.getDeviceName()))
{
    unacceptableGPIOs = [
        "GPIO36", "GPIO38", "GPIO39", 
        "GPIO47",
        "GPIO243", "GPIO225", "GPIO229"
    ]
    for (var i = 50; i <= 223; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
    for (var i = 230; i <= 241; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
    for (var i = 224; i <= 253; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
}
if ("F28P65x".includes(Common.getDeviceName()))
{
    unacceptableGPIOs = [
        "GPIO39", "GPIO60", "GPIO67", 
        "GPIO68",
        "GPIO81", "GPIO219"
    ]
    for (var i = 95; i <= 103; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
    for (var i = 106; i <= 132; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
    for (var i = 134; i <= 197; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
}
if ("F28P55x".includes(Common.getDeviceName()))
{
    unacceptableGPIOs = [
        "GPIO36", "GPIO38", "GPIO39", ,"GPIO225", "GPIO229","GPIO254"
    ]
    for (var i = 82; i <= 210; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
    for (var i = 216; i <= 223; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
    for (var i = 231; i <= 235; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
    for (var i = 237; i <= 241; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
    for (var i = 243; i <= 246; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
    for (var i = 248; i <= 252; i++)
    {
        unacceptableGPIOs.push("GPIO" + i.toString());
    }
}
if ("F28E12x".includes(Common.getDeviceName()))
    {
        unacceptableGPIOs = [
            "GPIO8", "GPIO14", "GPIO15", 
            "GPIO31", "GPIO42", "GPIO44"
        ]
        for (var i = 17; i <= 22; i++)
        {
            unacceptableGPIOs.push("GPIO" + i.toString());
        }
        for (var i = 25; i <= 27; i++)
            {
                unacceptableGPIOs.push("GPIO" + i.toString());
            }
        for (var i = 34; i <= 38; i++)
        {
            unacceptableGPIOs.push("GPIO" + i.toString());
        }
        for (var i = 46; i <= 49; i++)
        {
            unacceptableGPIOs.push("GPIO" + i.toString());
        }
        for (var i = 225; i <= 229; i++)
        {
            unacceptableGPIOs.push("GPIO" + i.toString());
        }
        for (var i = 231; i <= 241; i++)
        {
            unacceptableGPIOs.push("GPIO" + i.toString());
        }
        for (var i = 244; i <= 245; i++)
        {
            unacceptableGPIOs.push("GPIO" + i.toString());
        }
    }

for (var gpioIndex = 0; gpioIndex < gpios.length; gpioIndex++)
{
    if (!unacceptableGPIOs.includes(gpios[gpioIndex]))
    {
        gpioOptions.push({name: gpios[gpioIndex]});
    }
}

function onChangeuseZone(inst, ui)
{
    var bootConfigs = ['bootPinCount','BMSP0',
                        'BMSP1','BMSP2', 'ERRORSTSPIN',
                        'BOOTDEF0','BOOTDEF1','BOOTDEF2',
                        'BOOTDEF3','BOOTDEF4','BOOTDEF5',
                        'BOOTDEF6','BOOTDEF7'];
    if (["F28002x", "F28003x", "F280013x", "F280015x", "F28P65x","F28P55x"].includes(Common.getDeviceName()))
    {
        bootConfigs = bootConfigs.concat(['RUNMPOST', 'CJTAGNODEID']);
    }
    if (["F28E12x"].includes(Common.getDeviceName()))
    {
        bootConfigs = bootConfigs.concat(['CJTAGNODEID']);
    }
    if ("F2838x".includes(Common.getDeviceName()))
    {
        bootConfigs = bootConfigs.concat(['RUNMPOST']);
    }
    if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x","F28P55x", "F28E12x"].includes(Common.getDeviceName()))
    {
        bootConfigs = bootConfigs.concat([
        	'CMACKEY0', 'CMACKEY1', 'CMACKEY2', 'CMACKEY3']);
    }
    if (["F28P55x"].includes(Common.getDeviceName()))
    {

        for (var i = 9; i < 24; i++)
        {
            var lock_sector_name = "write_protect_bit" + i.toString()
            bootConfigs = bootConfigs.concat(lock_sector_name)
        }
    }
    for(var uiConfigIndex = 3; uiConfigIndex < config.length; uiConfigIndex++)
    {
        var configName = config[uiConfigIndex].name;
        if (bootConfigs.includes(configName))
        {
            ui[configName].hidden = !(inst.useZone & inst.configureBoot)
        }
        else
        {
            ui[configName].hidden = !inst.useZone;
        }
        // if (configName.includes("write_protect_bit"))
        // {
        //     ui[configName].hidden = true
        // }
    }
    
    if (inst['bootPinCount'] <= 2)
    {
        ui['BMSP2'].hidden = true;
    }
    if (inst['bootPinCount'] <= 1)
    {
        ui['BMSP1'].hidden = true;
    }
    if (inst['bootPinCount'] <= 0)
    {
        ui['BMSP0'].hidden = true;
    }

    if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x","F28P55x", "F28E12x"].includes(Common.getDeviceName()))
    {
        if (!inst['JTAGLOCK'])
        {
            ui['JTAGPSWDH0'].hidden = true;
            ui['JTAGPSWDH1'].hidden = true;
        }

    }

    for (var i=Math.pow(2, inst["bootPinCount"]); i < 8; i++)
    {
        ui['BOOTDEF' + i.toString()].hidden = true;
    }
    
    if ("F28004x".includes(Common.getDeviceName()))
    {
        if (inst["zone"] == 2)
        {
            ui["configureBoot"].hidden = true;
            for(var i = 0; i < bootConfigs.length; i++)
            {
                var configName = bootConfigs[i];
                ui[configName].hidden = true;
            }
        }
    }
    if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x","F28P55x", "F28E12x"].includes(Common.getDeviceName()))
    {
        if (inst["zone"] == 2)
        {
            ui['JTAGLOCK'].hidden = true;
            ui['JTAGPSWDH0'].hidden = true;
            ui['JTAGPSWDH1'].hidden = true;
            ui['CMACKEY0'].hidden = true; 
            ui['CMACKEY1'].hidden = true; 
            ui['CMACKEY2'].hidden = true; 
            ui['CMACKEY3'].hidden = true;
        }
    }
    if (["F28002x", "F28003x", "F280013x", "F280015x", "F28P65x","F28P55x", "F28E12x"].includes(Common.getDeviceName())){
    	ui['CJTAGNODEID'].hidden = true;
    }
}

function onChangeZone(inst, ui)
{
    onChangeuseZone(inst, ui);
    
}

/* Array of Watchdog configurables that are common across device families */
let config = [
    {
        name: "useZone",
        displayName : "Configure this Section",
        description : 'Check this box to configure the header OTP values for this zone. Once you program these OTP values, you will not be able to change them.',
        hidden      : false,
        default     : true,
        onChange    : onChangeuseZone
    },
    {
        name        : 'zone',
        displayName : 'Zone',
        description : '',
        hidden      : true,
        readOnly    : false,
        default     : 3,
        onChange    : onChangeZone
    },
    {
        name: "selectedCPU",
        displayName : "Selected CPU",
        hidden      : true,
        default     : "CPU1",
        onChange    : onChangeuseZone
    },
    {
        name        : 'PASWDLOCK',
        displayName : 'Password Lock (PSWDLOCK)',
        description : 'When PSWDLOCK is enabled and the Zone is locked, the CSMPSWDs will be secure. When PSWDLOCK is disabled, the CSMPSWDs will always be unsecure.',
        hidden      : false,
        default     : "DISABLE",
        options     : [
            {name: "DISABLE", displayName: "Disable PSWDLOCK"},
            {name: "ENABLE", displayName: "Enable PSWDLOCK permanently"},
        ]
    },
]

if (!["F280013x", "F28E12x"].includes(Common.getDeviceName()))
{
    config = config.concat([
        {
            name        : 'CRCLOCK',
            displayName : 'CRC Lock (CRCLOCK)',
            description : "Enabling this will disable the VCU/VCRC's ability to calculate a CRC value on secure memories",
            hidden      : false,
            default     : "DISABLE",
            options     : [
                {name: "DISABLE", displayName: "Disable CRCLOCK permanently"},
                {name: "ENABLE", displayName: "Enable CRCLOCK permanently"},
            ]
        },
    ])
}

if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x","F28P55x", "F28E12x"].includes(Common.getDeviceName()))
{
    config = config.concat([
        {
            name        : 'JTAGLOCK',
            displayName : 'Enable JTAGLOCK',
            description : "This feature disables JTAG access to the device. Once enabled, this feature cannot be disabled.",
            readOnly    : false,
            hidden      : false,
            default     : false,
            onChange    : onChangeuseZone
        },
        {
            name        : 'JTAGPSWDH0',
            displayName : 'JTAGPSWDH0 (JTAG Password)',
            description : "JTAG Password High 0 (bits 64-95)",
            readOnly    : false,
            hidden      : true,
            default     : "0x4BFFFFFF",
            onChange    : onChangeuseZone
        },
        {
            name        : 'JTAGPSWDH1',
            displayName : 'JTAGPSWDH1 (JTAG Password)',
            description : "JTAG Password High 1 (bits 96-127)",
            readOnly    : false,
            hidden      : true,
            default     : "0x3FFFFFFF",
            onChange    : onChangeuseZone
        },
    ]);
}
if (["F28002x", "F28004x"].includes(Common.getDeviceName()))
{
    config = config.concat([
        {
            name        : 'JTAGLOCK',
            displayName : 'Enable JTAGLOCK',
            description : "This feature disables JTAG access to the device. Once enabled, this feature cannot be disabled.",
            readOnly    : false,
            hidden      : false,
            default     : false,
            onChange    : onChangeuseZone
        }
    ]);
}


config = config.concat([
    {
        name        : 'configureBoot',
        displayName : 'Configure Boot Setting',
        readOnly    : false,
        hidden      : false,
        default     : false,
        onChange    : onChangeuseZone
    },
    {
        name        : 'bootPinCount',
        displayName : 'Number of Boot Pins',
        readOnly    : false,
        hidden      : true,
        default     : 2,
        options     : [
            {name: 0},
            {name: 1},
            {name: 2},
            {name: 3}
        ],
        onChange    : onChangeuseZone
    },
    {
        name        : 'BMSP0',
        displayName : 'Boot Pin 0 (BMSP0)',
        readOnly    : false,
        hidden      : true,
        default     : pin0Defaults,
        options     : gpioOptions,
        onChange    : onChangeuseZone
    },
    {
        name        : 'BMSP1',
        displayName : 'Boot Pin 1 (BMSP1)',
        readOnly    : false,
        hidden      : true,
        default     : pin1Defaults,
        options     : gpioOptions,
        onChange    : onChangeuseZone
    },
    {
        name        : 'BMSP2',
        displayName : 'Boot Pin 2 (BMSP2)',
        readOnly    : false,
        hidden      : true,
        default     : "GPIO0",
        options     : gpioOptions,
        onChange    : onChangeuseZone
    }
]);

if (["F28002x", "F28004x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28E12x"].includes(Common.getDeviceName()))
{
    config = config.concat([{
        name        : 'ERRORSTSPIN',
        displayName : 'ERRORSTS PIN',
        readOnly    : false,
        hidden      : true,
        default     : 3,
        options     : ERRORSTS_options,
        onChange    : onChangeuseZone
    }]);
}
if (["F28P55x"].includes(Common.getDeviceName()))
{
    config = config.concat([{
        name        : 'ERRORSTSPIN',
        displayName : 'ERRORSTS PIN',
        readOnly    : false,
        hidden      : true,
        default     : 7,
        options     : ERRORSTS_options,
        onChange    : onChangeuseZone
    }]);
}

config = config.concat([
    {
        name        : 'BOOTDEF0',
        displayName : 'BOOTDEF0',
        description : "Boot mode when tha value of the GPIOs used for valid BMSP2-BMSP1-BMSP0 are 0b000",
        readOnly    : false,
        hidden      : true,
        default     : "0x00",
        options     : ALL_BOOT_OPTIONS,
        onChange    : onChangeuseZone
    },
    {
        name        : 'BOOTDEF1',
        displayName : 'BOOTDEF1',
        description : "Boot mode when tha value of the GPIOs used for valid BMSP2-BMSP1-BMSP0 are 0b001",
        readOnly    : false,
        hidden      : true,
        default     : "0x00",
        options     : ALL_BOOT_OPTIONS,
        onChange    : onChangeuseZone
    },
    {
        name        : 'BOOTDEF2',
        displayName : 'BOOTDEF2',
        description : "Boot mode when tha value of the GPIOs used for valid BMSP2-BMSP1-BMSP0 are 0b010",
        readOnly    : false,
        hidden      : true,
        default     : "0x00",
        options     : ALL_BOOT_OPTIONS,
        onChange    : onChangeuseZone
    },
    {
        name        : 'BOOTDEF3',
        displayName : 'BOOTDEF3',
        description : "Boot mode when tha value of the GPIOs used for valid BMSP2-BMSP1-BMSP0 are 0b011",
        readOnly    : false,
        hidden      : true,
        default     : "0x00",
        options     : ALL_BOOT_OPTIONS,
        onChange    : onChangeuseZone
    },
    {
        name        : 'BOOTDEF4',
        displayName : 'BOOTDEF4',
        description : "Boot mode when tha value of the GPIOs used for valid BMSP2-BMSP1-BMSP0 are 0b100",
        readOnly    : false,
        hidden      : true,
        default     : "0x00",
        options     : ALL_BOOT_OPTIONS,
        onChange    : onChangeuseZone
    },
    {
        name        : 'BOOTDEF5',
        displayName : 'BOOTDEF5',
        description : "Boot mode when tha value of the GPIOs used for valid BMSP2-BMSP1-BMSP0 are 0b101",
        readOnly    : false,
        hidden      : true,
        default     : "0x00",
        options     : ALL_BOOT_OPTIONS,
        onChange    : onChangeuseZone
    },
    {
        name        : 'BOOTDEF6',
        displayName : 'BOOTDEF6',
        description : "Boot mode when tha value of the GPIOs used for valid BMSP2-BMSP1-BMSP0 are 0b110",
        readOnly    : false,
        hidden      : true,
        default     : "0x00",
        options     : ALL_BOOT_OPTIONS,
        onChange    : onChangeuseZone
    },
    {
        name        : 'BOOTDEF7',
        displayName : 'BOOTDEF7',
        description : "Boot mode when tha value of the GPIOs used for valid BMSP2-BMSP1-BMSP0 are 0b111",
        readOnly    : false,
        hidden      : true,
        default     : "0x00",
        options     : ALL_BOOT_OPTIONS,
        onChange    : onChangeuseZone
    },
    
]);


if (["F2838x"].includes(Common.getDeviceName()))
{
    var mpost_config = [
        {
            name        : 'RUNMPOST',
            displayName : 'Run MPOST',
            readOnly    : false,
            hidden      : true,
            default     : 3,
            options     : MPOST_options,
            onChange    : onChangeuseZone
        },
    ]

    config = config.concat(mpost_config)
}

if (["F28002x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x"].includes(Common.getDeviceName()))
{
    var mpost_cjtagnode_config = [
        {
            name        : 'RUNMPOST',
            displayName : 'Run MPOST',
            readOnly    : false,
            hidden      : true,
            default     : 3,
            options     : MPOST_options,
            onChange    : onChangeuseZone
        },
        {
            name        : 'CJTAGNODEID',
            displayName : 'CJTAG Node ID',
            readOnly    : false,
            hidden      : true,
            default     : 15,
            onChange    : onChangeuseZone
        },

    ]

    config = config.concat(mpost_cjtagnode_config)
}

if (["F28E12x"].includes(Common.getDeviceName()))
    {
        var cjtagnode_config = [
            {
                name        : 'CJTAGNODEID',
                displayName : 'CJTAG Node ID',
                readOnly    : false,
                hidden      : true,
                default     : 15,
                onChange    : onChangeuseZone
            },
    
        ]
    
        config = config.concat(cjtagnode_config)
    }

if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x", "F28E12x"].includes(Common.getDeviceName()))
{
    var cmac_config = [
        {
            name        : 'CMACKEY0',
            displayName : 'CMAC Key0',
            description : 'Only applicable for secure boot',
            readOnly    : false,
            hidden      : true,
            default     : "0x00000000",
            onChange    : onChangeuseZone
        },
        {
            name        : 'CMACKEY1',
            displayName : 'CMAC Key1',
            description : 'Only applicable for secure boot',
            readOnly    : false,
            hidden      : true,
            default     : "0x00000000",
            onChange    : onChangeuseZone
        },
        {
            name        : 'CMACKEY2',
            displayName : 'CMAC Key2',
            description : 'Only applicable for secure boot',
            readOnly    : false,
            hidden      : true,
            default     : "0x00000000",
            onChange    : onChangeuseZone
        },
        {
            name        : 'CMACKEY3',
            displayName : 'CMAC Key3',
            description : 'Only applicable for secure boot',
            readOnly    : false,
            hidden      : true,
            default     : "0x00000000",
            onChange    : onChangeuseZone
        },
    ]

    config = config.concat(cmac_config)
}

if (["F28P55x"].includes(Common.getDeviceName()))
{
    for (var j = 1; j < 3; j++)
    {
        for (var i = 1; i < 9; i++)
        {
            var lock_sect_min = i*4
            if (i == 1){
                lock_sect_min = 0
            }
            var lock_sect_max = i*4 + 3
            var lock_sector_display_name = "Write-Protect Flash Bank " + ((j-1)*2).toString() + " Sectors " + lock_sect_min.toString() + "-" + lock_sect_max.toString()
            var bitnum = j*8+i
            if (bitnum == 16){
                var lock_sector_display_name = "Write-Protect Flash Bank 4 Sectors 0-31"
            }
            if (bitnum < 24 && (system.deviceData.gpn.includes("F28P551") || system.deviceData.gpn.includes("F28P552") || system.deviceData.gpn.includes("F28P558") || bitnum != 16)){
                var lock_sector_name = "write_protect_bit" + bitnum.toString()
                config = config.concat({
                    name        : lock_sector_name,
                    displayName : lock_sector_display_name,
                    description : "Enabling this feature will permanently block erase/program of these sectors.",
                    readOnly    : false,
                    hidden      : true,
                    default     : "1",
                    options     : [
                        {name: "0", displayName: "Yes"},
                        {name: "1", displayName: "No"}
                    ],
                    description : "Enabling this feature will permanently block any write or erase within the corresponding flash sector."
                })
            }
        }
    }
}

/**
 * Validate this module's configuration
 *
 * @param inst       - Watchdog instance to be validated
 * @param validation - Issue reporting object
 */
function validate(inst, vo)
{
    var format8Hex = new RegExp(/^0x[A-F0-9]{8}$/i);
    var sequenceOf1then0 = new RegExp(/^0x1F{0,7}[EC8]{0,1}0{0,7}$/i);
    
    if (inst["zone"] == 1 &&
        inst["useZone"] == true &&
        inst["configureBoot"] == true)
    {

        if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x", "F28E12x"].includes(Common.getDeviceName()))
        {
            var cmackkeys = ["CMACKEY0", "CMACKEY1", "CMACKEY2", "CMACKEY3"]
            for (var cmackkeys_i in cmackkeys)
            {
                var format8HexResult = format8Hex.test(inst[cmackkeys[cmackkeys_i]]);
                if (!format8HexResult)
                {
                    Common.logError(vo, inst, cmackkeys[cmackkeys_i], 'Invalid 8 digit hex value');
                }
            }
        }

        var errGPIO = "";
        if (["F28002x", "F28004x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x", "F28E12x"].includes(Common.getDeviceName()))
        {
            errGPIO = ERRORSTS_options.find(input => {
                return input.name === inst["ERRORSTSPIN"]
            }).displayName;
        }
        
        if (inst["bootPinCount"] > 0)
        {
            if (["F28002x", "F28004x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x", "F28E12x"].includes(Common.getDeviceName())){
                if (inst["BMSP0"] == errGPIO)
                {
                    Common.logError(vo, inst, "BMSP0", 
                        'The BMSP0 pin is conflicting with ERRORSTS pin.');
                }
            }
        }
        if (inst["bootPinCount"] > 1)
        {
            if (["F28002x", "F28004x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x", "F28E12x"].includes(Common.getDeviceName())){
                if (inst["BMSP1"] == errGPIO)
                {
                    Common.logError(vo, inst, "BMSP1", 
                        'The BMSP1 pin is conflicting with ERRORSTS pin.');
                }
            }
            if (inst["BMSP0"] == inst["BMSP1"])
            {
                Common.logError(vo, inst, "BMSP1", 
                    'The BMSP1 pin is conflicting with BMSP0 pin.');
            }
        }
        if (inst["bootPinCount"] > 2)
        {
            if (["F28002x", "F28004x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x", "F28E12x"].includes(Common.getDeviceName())){
                if (inst["BMSP2"] == errGPIO)
                {
                    Common.logError(vo, inst, "BMSP2", 
                        'The BMSP2 pin is conflicting with ERRORSTS pin.');
                }
            }
            if (inst["BMSP0"] == inst["BMSP2"])
            {
                Common.logError(vo, inst, "BMSP2", 
                    'The BMSP2 pin is conflicting with BMSP0 pin.');
            }
            if (inst["BMSP1"] == inst["BMSP2"])
            {
                Common.logError(vo, inst, "BMSP2", 
                    'The BMSP2 pin is conflicting with BMSP1 pin.');
            }
        }
        if (["F28002x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x", "F28E12x"].includes(Common.getDeviceName()))
        {
            if (!(inst["CJTAGNODEID"] >= 0 && inst["CJTAGNODEID"] < 16))
            {
                Common.logError(vo, inst, "CJTAGNODEID", 
                'Enter a valid 4-bit CJTAG NODE ID (0-15).');
            }
        }
    }
    if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x", "F28E12x"].includes(Common.getDeviceName()))
    {
        if (inst["zone"] == 1 &&
            inst["useZone"] == true &&
            inst["JTAGLOCK"] == true)
        {
            var jtagpassword = ["JTAGPSWDH0", "JTAGPSWDH1"]
            for (var jtagpassword_i in jtagpassword)
            {
                var format8HexResult = format8Hex.test(inst[jtagpassword[jtagpassword_i]]);
                if (!format8HexResult)
                {
                    Common.logError(vo, inst, jtagpassword[jtagpassword_i], 'Invalid 8 digit hex value');
                }
                if (inst["zone"] == 1)
                {
                    var mask = Common.getDefaultJTAGPSWDHValueMask(1)[jtagpassword_i]
                    
                    if (parseInt(inst[jtagpassword[jtagpassword_i]]) != 
                    ((parseInt(inst[jtagpassword[jtagpassword_i]]) & mask)>>> 0))
                    {
                        Common.logError(vo, inst, jtagpassword[jtagpassword_i], 
                            'This password value has a mask of ' + mask.toString(16).toUpperCase().replace("0X","0x") + 
                            ". For each bit in the mask that is a 0, the corresponding bit in the password must also be a 0.");
                    }
                }
            }
        }
    }
    //var format8HexResult = format8Hex.test();
    //var sequenceOf1then0Result = sequenceOf1then0.test(); 

}


// Define the common/portable base Watchdog
exports = {
    displayName         : 'ZONE OTP',
    description         : 'ZONE OTP',
    defaultInstanceName : 'ZONE_OTP',
    longDescription     : longDescription,
    config              : config,
    validate            : validate
};
