"use strict";
/*global exports, system*/
let Common   = system.getScript('/utilities/dcsm_tool/dcsm_syscfg/source/Common.js');


// Device specific options
var pin1Defaults = "GPIO72";
var pin0Defaults = "GPIO84";

/* Intro splash on GUI */
let longDescription = 'ZONE Header can ONLY be programmed once. After they are programmed they cannot be modified. ' + 
                        'This section cannot be modified by using a different LINKPOINTER value.';

var gpioOptions = [];
var gpios = Common.getGPIOs();
for (var gpioIndex = 0; gpioIndex < gpios.length; gpioIndex++)
{
    gpioOptions.push({name: gpios[gpioIndex]});
}


function onChangeuseZone(inst, ui)
{
    for(var uiConfigIndex = 3; uiConfigIndex < config.length; uiConfigIndex++)
    {
        var configName = config[uiConfigIndex].name;
        if (configName == "BOOTModeCPU1")
        {
            ui[configName].hidden = !((inst.selectedCPU == "CPU1") & inst.useZone & inst.configureBoot)
        }
        else if (configName == "BOOTModeCPU2")
        {
            ui[configName].hidden = !((inst.selectedCPU == "CPU2") & inst.useZone & inst.configureBoot)
        }
        else if ([  'BOOTCTRL_PIN0','BOOTCTRL_PIN1',
                    'BOOTCTRL_KEY','BOOTCTRL_MODE'].includes(configName))
        {
            ui[configName].hidden = !(inst.useZone & inst.configureBoot)
        }
        else
        {
            ui[configName].hidden = !inst.useZone;
        }
    }
}

function onChangeSelectedCPU(inst, ui)
{
    onChangeBootMode(inst, ui)
}


function onChangeConfigureBoot(inst, ui)
{
    onChangeuseZone(inst, ui)
}

function onChangeBootMode(inst, ui)
{
    if (inst.selectedCPU == "CPU1")
    {
        var realizedBootMode = inst["BOOTModeCPU1"]

        for(var index = 0; index < REALIZED_BOOT_MODE_CPU1.length; index++)
        {
            if (realizedBootMode == REALIZED_BOOT_MODE_CPU1[index].name)
            {
                inst["BOOTCTRL_KEY"] = KEY_BMODE_CPU1[index].KEY;
                inst["BOOTCTRL_MODE"] = KEY_BMODE_CPU1[index].BMODE;
                break;
            }
        }
    }
    else
    {
    
        var realizedBootMode = inst["BOOTModeCPU2"]

        for(var index = 0; index < REALIZED_BOOT_MODE_CPU2.length; index++)
        {
            if (realizedBootMode == REALIZED_BOOT_MODE_CPU2[index].name)
            {
                inst["BOOTCTRL_KEY"] = KEY_BMODE_CPU2[index].KEY;
                inst["BOOTCTRL_MODE"] = KEY_BMODE_CPU2[index].BMODE;
                break;
            }
        }
    }

}

let KEY_BMODE_CPU1 = [
    //{ KEY:"0xFF", BMODE: "0xFF"}, 
    { KEY:"0x5A", BMODE: "0x0B"}, 

    { KEY:"0x5A", BMODE: "0x00"}, 
    { KEY:"0x5A", BMODE: "0x01"}, 
    { KEY:"0x5A", BMODE: "0x02"}, 
    { KEY:"0x5A", BMODE: "0x04"}, 
    { KEY:"0x5A", BMODE: "0x05"}, 
    { KEY:"0x5A", BMODE: "0x07"}, 
    { KEY:"0x5A", BMODE: "0x0A"}, 
    { KEY:"0x5A", BMODE: "0x0C"}, 
    { KEY:"0x5A", BMODE: "0x81"}, 
    { KEY:"0x5A", BMODE: "0x84"}, 
    { KEY:"0x5A", BMODE: "0x85"}, 
    { KEY:"0x5A", BMODE: "0x87"}, 
    //{ KEY:"0x5A", BMODE: "0x89"}
]

let REALIZED_BOOT_MODE_CPU1 = [
    //{name: "Flash Boot / Wait Boot"},
    {name: "Flash Boot"},

    {name: "Parallel Boot"},
    {name: "SCI Boot 0"},
    {name: "Wait Boot"},
    {name: "SPI Boot 0"},
    {name: "I2C Boot 0"},
    {name: "CAN Boot 0"},
    {name: "RAM Boot"},
    {name: "USB Boot"},
    {name: "SCI Boot 1"},
    {name: "SPI Boot 1"},
    {name: "I2C Boot 1"},
    {name: "CAN Boot 1"},
    //{name: "Flash Boot / Wait Boot"},
]

let KEY_BMODE_CPU2 = [
    //{ KEY:"0xFF", BMODE: "0xFF"}, 
    //{ KEY:"0x5A", BMODE: "0x0A"}, 
    { KEY:"0x5A", BMODE: "0x0B"}, 
    { KEY:"0x5A", BMODE: "0x0C"}, 
]
let REALIZED_BOOT_MODE_CPU2 = [
    //{name: "Wait Boot"},
    //{name: "Wait Boot / RAM Boot"},
    {name: "Flash Boot"},
    {name: "Wait Boot"},
]

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
        name: "selectedCPU",
        displayName : "Selected CPU",
        hidden      : true,
        default     : "CPU1",
        onChange    : onChangeSelectedCPU
    },
    {
        name        : 'zone',
        displayName : 'Zone',
        description : '',
        hidden      : true,
        readOnly    : false,
        default     : 3
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
        name        : 'configureBoot',
        displayName : 'Configure Boot Setting',
        readOnly    : false,
        hidden      : false,
        default     : false,
        onChange    : onChangeConfigureBoot
    },
    {
        name        : 'BOOTCTRL_PIN0',
        displayName : 'Boot Control PIN0 (BOOTCTRL.BOOTPIN0)',
        hidden      : true,
        readOnly    : false,
        default     : pin0Defaults,
        options     : gpioOptions
    },
    {
        name        : 'BOOTCTRL_PIN1',
        displayName : 'Boot Control PIN1 (BOOTCTRL.BOOTPIN1)',
        hidden      : true,
        readOnly    : false,
        default     : pin1Defaults,
        options     : gpioOptions
    },
    {
        name        : 'BOOTModeCPU1',
        displayName : 'Get Mode',
        description : 'Get Mode (Boot mode with PIN0 and PIN1 pulled HIGH)',
        hidden      : true,
        default     : REALIZED_BOOT_MODE_CPU1[0].name,
        options     : REALIZED_BOOT_MODE_CPU1,
        onChange    : onChangeBootMode
    },
    {
        name        : 'BOOTModeCPU2',
        displayName : 'Get Mode',
        description : 'Get Mode (Boot mode with PIN0 and PIN1 pulled HIGH)',
        hidden      : true,
        default     : REALIZED_BOOT_MODE_CPU2[0].name,
        options     : REALIZED_BOOT_MODE_CPU2,
        onChange    : onChangeBootMode
    },
    {
        name        : 'BOOTCTRL_KEY',
        displayName : 'Boot Control Key',
        description : 'Boot Control key value',
		readOnly    : true,
        hidden      : true,
        default     : KEY_BMODE_CPU1[0].KEY
    },
    {
        name        : 'BOOTCTRL_MODE',
        displayName : 'Boot Control Mode (BOOTCTRL.BMODE)',
        description : 'Boot Control BMODE value',
		readOnly    : true,
        hidden      : true,
        default     : KEY_BMODE_CPU1[0].BMODE
    }
];

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
