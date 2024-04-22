"use strict";
/*global exports, system*/

let Common   = system.getScript('/utilities/dcsm_tool/dcsm_syscfg/source/Common.js');

/* Intro splash on GUI */
let longDescription = 'Zone-Select Block configurations can be updated when a new LINKPOINTER from the available LINKPOINTERs is chosen.';


var zoneOptions = Common.getZoneOptions();
var zoneNonEXEOptions = Common.getNonEXEOptions();
var claZoneOptions = Common.getCLAOptions();

let device_ram = Common.getRAMs();
let device_sect = Common.getSECTs();


/* Array of Watchdog configurables that are common across device families */
let claconfig = [
    {
        name        : 'CLA',
        displayName : 'CLA',
        description : 'CLA Zone Selection.',
        default     : "UNSECURE",
        options     : claZoneOptions
    }
];

var dr = device_ram[Common.getDeviceName().toLowerCase() + "_ram"]
dr.forEach(element => {
    if (["F2838x","F28P65x"].includes(Common.getDeviceName()))
    {
        if (element["name"].includes("MSGRAM"))
        {
            element["options"] = zoneNonEXEOptions
        }
        else {
            element["options"] = zoneOptions
        }
    }
    else {
        element["options"] = zoneOptions
    }
});

var ds = device_sect[Common.getDeviceName().toLowerCase() + "_sect"]
ds.forEach(element => {
    element["options"] = zoneOptions
});

function onChangeZone(inst, ui)
{
    if (["F28002x", "F28004x", "F2838x", "F28003x", "F280013x", "F280015x","F28P65x", "F28P55x"].includes(Common.getDeviceName()))
    {
        var zone = inst["zone"]
        if (zone == 1)
        {
            inst["PASSWORD1"] = "0x" + Common.getZone1Password1Mask(
                                        Common.getNextLinkPointerIndex(inst)).mask.toString(16).padStart(8, '0').toUpperCase();
        }
        else if (zone == 2)
        {
            inst["PASSWORD1"] = "0x" + Common.getZone2Password1Mask(
                                        Common.getNextLinkPointerIndex(inst)).mask.toString(16).padStart(8, '0').toUpperCase();
            
            if (["F2838x", "F28003x", "F280013x", "F280015x","F28P65x", "F28P55x"].includes(Common.getDeviceName()))
            {
                ui["JTAGPSWDL0"].hidden = true;
                ui["JTAGPSWDL1"].hidden = true;
            }
            if (["F28P65x", "F28P55x"].includes(Common.getDeviceName()))
            {
                ui["MPOSTENABLE"].hidden = true;
            }
        }
    }
}

function onChangeuseZone(inst, ui)
{
    for(var uiConfigIndex = 1; uiConfigIndex < config.length; uiConfigIndex++)
    {
        var configName = config[uiConfigIndex].name;
        if (configName.includes("GROUP_"))
        {
            for(var g_i = 0; g_i < config[uiConfigIndex]["config"].length; g_i++)
            {
                var g_configName = config[uiConfigIndex]["config"][g_i].name;
                ui[g_configName].hidden = !inst.useZone;
                if (inst.PROGRAM_ZSB == false & !g_configName.includes("LINKPOINTER") & !g_configName.includes("PROGRAM_ZSB"))
                {
                    ui[g_configName].hidden = true
                }
            }
        }
        else
        {
            ui[configName].hidden = !inst.useZone;
            if (inst.PROGRAM_ZSB == false & !configName.includes("LINKPOINTER") & !configName.includes("PROGRAM_ZSB"))
            {
                ui[configName].hidden = true
            }
        }
    }

    ui["zone"].hidden = true;
}




/* Array of Watchdog configurables that are common across device families */
let config = [
    {
        name: "useZone",
        displayName : "Configure this Section",
        description : 'Check this box to configure the Zone Select Block',
        hidden      : false,
        default     : true,
        onChange    : onChangeuseZone
    },
    {
        name        : 'PROGRAM_ZSB',
        displayName : 'Program Zone-Select Block',
        description : 'When this box is checked, no settings in the zone-select block will be configured. ' +
        'Only the value in the "Next LINKPOINTER" field will be programmed, in addition to the Zone Header if it is enabled.',
        hidden      : false,
        default     : true,
        onChange    : onChangeuseZone
    },
    {
        name        : 'PASSWORD0',
        displayName : 'Password 0',
        description : 'CSM Password 0 value',
        hidden      : false,
        default     : '0xFFFFFFFF'
    },
    {
        name        : 'PASSWORD1',
        displayName : 'Password 1',
        description : 'CSM Password 1 value',
        hidden      : false,
        default     : '0xFFFFFFFF'
    },
    {
        name        : 'PASSWORD2',
        displayName : 'Password 2',
        description : 'CSM Password 2 value',
        hidden      : false,
        default     : '0xFFFFFFFF'
    },
    {
        name        : 'PASSWORD3',
        displayName : 'Password 3',
        description : 'CSM Password 3 value',
        hidden      : false,
        default     : '0xFFFFFFFF'
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
    
];

var MPOST_enable_options

if (["F28P65x", "F28P55x"].includes(Common.getDeviceName()))
{
    MPOST_enable_options = [
        {name:0x0 , displayName: "Disable MPOST"},
        {name:0x1 , displayName: "Enable MPOST"}
    ]
}

if (["F28P65x", "F28P55x"].includes(Common.getDeviceName()))
{
    config = config.concat([   
        {
            name        : 'MPOSTENABLE',
            displayName : 'Enable MPOST',
            description : 'This configures the Z1_DIAG register and is used along with the "Run MPOST" feature in the Zone Header (OTP).' +
                          ' Both "Enable MPOST" and "Run MPOST" must be configured to use MPOST.',
            hidden      : false,
            default     : 0,
            options     : MPOST_enable_options
        }
    ])
}
if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x"].includes(Common.getDeviceName()))
{
    config = config.concat([   
        {
            name        : 'JTAGPSWDL0',
            displayName : 'JTAGPSWDL0 (JTAG Password)',
            description : 'JTAG Password Low 0 (bits 0-31). This value can be updated by updating the LINKPOINTER.',
            hidden      : false,
            default     : '0xFFFFFFFF'
        },
        {
            name        : 'JTAGPSWDL1',
            displayName : 'JTAGPSWDL1 (JTAG Password)',
            description : 'JTAG Password Low 1 (bits 32-63). This value can be updated by updating the LINKPOINTER.',
            hidden      : false,
            default     : '0x2BFFFFFF'
        },
    ])
}

if (!(["F28004x", "F28002x", "F2838x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x"].includes(Common.getDeviceName())))
{
    config = config.concat(claconfig)
}

config = config.concat({
    name        : 'SECURE_ALL',
    displayName : 'Secure All Resources',
    description : 'Pressing this button will designate all securable resources as "Secured by this zone".',
    hidden : false,
    buttonText: "SECURE ALL",
    onComplete: (inst) => {
        config.forEach(configName => {
            for(var uiConfigIndex = 1; uiConfigIndex < config.length; uiConfigIndex++)
            {
                var configName = config[uiConfigIndex].name;
                if (configName.includes("GROUP_"))
                {
                    for(var g_i = 0; g_i < config[uiConfigIndex]["config"].length; g_i++)
                    {
                        var g_configName = config[uiConfigIndex]["config"][g_i].name;
                        if ((g_configName.includes("RAM") || g_configName.includes("SECT")) && !g_configName.includes("PROGRAM_ZSB"))
                        {
                            inst[g_configName] = "SECURE"
                        }
                    }
                }
                else
                {
                    if ((configName.includes("RAM") || configName.includes("SECT")) && !configName.includes("PROGRAM_ZSB"))
                    {
                        inst[configName] = "SECURE"
                    }
                }
            }
        })
    }
})

config = config.concat(dr)

var flashBank0MemorySecs = [].concat(ds)
// Deep copy
var flashBank1MemorySecs = JSON.parse(JSON.stringify(ds));
flashBank1MemorySecs.forEach(element => {
    //element = Object.assign({}, element)
    element["name"] = element["name"] + Common.getBankNames(1);
})
// Deep copy
var flashBank2MemorySecs = JSON.parse(JSON.stringify(ds));
flashBank2MemorySecs.forEach(element => {
    //element = Object.assign({}, element)
    element["name"] = element["name"] + Common.getBankNames(2);
})
// Deep copy
var flashBank3MemorySecs = JSON.parse(JSON.stringify(ds));
flashBank3MemorySecs.forEach(element => {
    //element = Object.assign({}, element)
    element["name"] = element["name"] + Common.getBankNames(3);
})
// Deep copy
var flashBank4MemorySecs = JSON.parse(JSON.stringify(ds));
flashBank4MemorySecs.forEach(element => {
    //element = Object.assign({}, element)
    element["name"] = element["name"] + Common.getBankNames(4);
})

if ("F28P55x".includes(Common.getDeviceName()))
{
    var tempFlashBank4MemorySecs = []
    for (var i = 0; i < 5; i++){
        tempFlashBank4MemorySecs = tempFlashBank4MemorySecs.concat(flashBank4MemorySecs[i])
    }
    flashBank4MemorySecs = tempFlashBank4MemorySecs
}

//console.log(flashBank0MemorySecs);
//console.log(flashBank1MemorySecs);
//console.log(flashBank2MemorySecs);
//console.log(flashBank3MemorySecs);
//console.log(flashBank4MemorySecs);

var flashBank0GroupConfig = [{
    name: "GROUP_FLASHBANK0",
    displayName: "Flash Bank 0",
    description: "Flash Bank 0 Configuration",
    longDescription: "Flash Bank 0 configuration options",
    config: flashBank0MemorySecs
}];

var flashBank1GroupConfig = [{
    name: "GROUP_FLASHBANK1",
    displayName: "Flash Bank 1",
    description: "Flash Bank 1 Configuration",
    longDescription: "Flash Bank 1 configuration options",
    config: flashBank1MemorySecs
}];

var flashBank2GroupConfig = [{
    name: "GROUP_FLASHBANK2",
    displayName: "Flash Bank 2",
    description: "Flash Bank 2 Configuration",
    longDescription: "Flash Bank 2 configuration options",
    config: flashBank2MemorySecs
}];
var flashBank3GroupConfig = [{
    name: "GROUP_FLASHBANK3",
    displayName: "Flash Bank 3",
    description: "Flash Bank 3 Configuration",
    longDescription: "Flash Bank 3 configuration options",
    config: flashBank3MemorySecs
}];
var flashBank4GroupConfig = [{
    name: "GROUP_FLASHBANK4",
    displayName: "Flash Bank 4",
    description: "Flash Bank 4 Configuration",
    longDescription: "Flash Bank 4 configuration options",
    config: flashBank4MemorySecs
}];

var linkpointerForBank0Addition = "";
if ("F28004x".includes(Common.getDeviceName()))
{
    linkpointerForBank0Addition = " for Flash Bank 0";
}
var linkPointerBank0GroupConfig = [{
    name: "GROUP_LINKPOINTERBANK0",
    displayName: "LINKPOINTER" + linkpointerForBank0Addition,
    description: "LINKPOINTER" + linkpointerForBank0Addition + " Configuration",
    longDescription: "LINKPOINTER configuration options",
    config: Common.getLinkPointerConfigOptions(0)
}]

var linkPointerBank1GroupConfig = [{
    name: "GROUP_LINKPOINTERBANK1",
    displayName: "LINKPOINTER for Flash Bank 1",
    description: "LINKPOINTER for Flash Bank 1 Configuration",
    longDescription: "LINKPOINTER for Flash Bank 1 configuration options",
    config: Common.getLinkPointerConfigOptions(1)
}]

config = config.concat(flashBank0GroupConfig)
config.splice.apply(config, [1, 0].concat(linkPointerBank0GroupConfig));

if ("F28004x".includes(Common.getDeviceName()))
{
    config.splice.apply(config, [2, 0].concat(linkPointerBank1GroupConfig));
    config = config.concat(flashBank1GroupConfig)
}

if ("F28003x".includes(Common.getDeviceName()))
{
    config = config.concat(flashBank1GroupConfig)
    config = config.concat(flashBank2GroupConfig)
}
if ("F28P65x".includes(Common.getDeviceName()))
{
    config = config.concat(flashBank1GroupConfig)
    config = config.concat(flashBank2GroupConfig)
    config = config.concat(flashBank3GroupConfig)
    config = config.concat(flashBank4GroupConfig)
}
if ("F28P55x".includes(Common.getDeviceName()))
{
    config = config.concat(flashBank1GroupConfig)
    config = config.concat(flashBank2GroupConfig)
    config = config.concat(flashBank3GroupConfig)
    config = config.concat(flashBank4GroupConfig)
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
    if (["F2838x", "F28003x", "F280013x", "F280015x","F28P65x","F28P55x"].includes(Common.getDeviceName()))
    {
        sequenceOf1then0 = new RegExp(/^((0x00003F{0,3}[EC8]{0,1}0{0,3})|(0x00002000))$/i);
    }
    

    var passwords = ["PASSWORD0", "PASSWORD1", "PASSWORD2", "PASSWORD3"];

    for (var password_i in passwords)
    {
        var format8HexResult = format8Hex.test(inst[passwords[password_i]]);
        if (!format8HexResult)
        {
            Common.logError(vo, inst, passwords[password_i], 'Invalid 8 digit hex value');
        }

        if (["F28002x", "F28004x", "F2838x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x"].includes(Common.getDeviceName()))
        {
            if (passwords[password_i] == "PASSWORD1")
            {
                var linkpointerIndex = Common.getNextLinkPointerIndex(inst)
                var linkpointerMask = 0;
                if (inst["zone"] == 1)
                {
                    linkpointerMask = Common.getZone1Password1Mask(linkpointerIndex).mask
                }
                else if (inst["zone"] == 2)
                {
                    linkpointerMask = Common.getZone2Password1Mask(linkpointerIndex).mask
                }
                //console.log(linkpointerMask)
                //console.log(parseInt(inst[passwords[password_i]]))
                //console.log((parseInt(inst[passwords[password_i]]) & linkpointerMask) >>> 0)

                // The >>> 0 is necessary because after the & operation the value becomes a 32bit signed
                // The >>> 0 makes it 64bit unsigned again.
                if (parseInt(inst[passwords[password_i]]) != 
                    ((parseInt(inst[passwords[password_i]]) & linkpointerMask)>>> 0))
                {
                    Common.logError(vo, inst, passwords[password_i], 
                        'This password value has a mask of 0x' + linkpointerMask.toString(16).toUpperCase().replace("0X","0x") + 
                        ". For each bit in the mask that is a 0, the corresponding bit in the password must also be a 0.");
                }
            }
        }
    }
    if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x"].includes(Common.getDeviceName()))
    {
        var jtagpassword = ["JTAGPSWDL0", "JTAGPSWDL1"]
        for (var jtagpassword_i in jtagpassword)
        {
            var format8HexResult = format8Hex.test(inst[jtagpassword[jtagpassword_i]]);
            if (!format8HexResult)
            {
                Common.logError(vo, inst, jtagpassword[jtagpassword_i], 'Invalid 8 digit hex value');
            }

            if (jtagpassword[jtagpassword_i] == "JTAGPSWDL1")
            {
                var linkpointerIndex = Common.getNextLinkPointerIndex(inst)
                var linkpointerMask = 0;
                if (inst["zone"] == 1)
                {
                    linkpointerMask = Common.getDefaultJTAGPSWDL1ValueMask(linkpointerIndex).mask
                    
                    if (parseInt(inst[jtagpassword[jtagpassword_i]]) != 
                    ((parseInt(inst[jtagpassword[jtagpassword_i]]) & linkpointerMask)>>> 0))
                    {
                        Common.logError(vo, inst, jtagpassword[jtagpassword_i], 
                            'This password value has a mask of ' + linkpointerMask.toString(16).toUpperCase().replace("0X","0x") + 
                            ". For each bit in the mask that is a 0, the corresponding bit in the password must also be a 0.");
                    }
                }
            }
        }
    }

    var dr_index = 0;
    for (dr_index in dr)
    {
        var zoneX_instance_obj = inst.$module.$instances[0];
        var zoneY_instance_obj = inst.$module.$instances[1];
        var zoneX_value = zoneX_instance_obj[dr[dr_index].name];
        var zoneY_value = zoneY_instance_obj[dr[dr_index].name];

        if (zoneX_value != "UNSECURE" && zoneY_value != "UNSECURE")
        {
            Common.logError(vo, zoneX_instance_obj, dr[dr_index].name, 'This memory section is assigned to both Zone1 and Zone2');
        }
    }

    
    if (!(["F28002x", "F28004x", "F2838x", "F28003x", "F280013x", "F280015x", "F28P65x", "F28P55x"].includes(Common.getDeviceName())))
    {
        var cla_index = 0;
        for (cla_index in claconfig)
        {
            var zoneX_instance_obj = inst.$module.$instances[0];
            var zoneY_instance_obj = inst.$module.$instances[1];
            var zoneX_value = zoneX_instance_obj[claconfig[cla_index].name];
            var zoneY_value = zoneY_instance_obj[claconfig[cla_index].name];
    
            if (zoneX_value != "UNSECURE" && zoneY_value != "UNSECURE")
            {
                Common.logError(vo, zoneX_instance_obj, claconfig[cla_index].name, 'CLA section is assigned to both Zone1 and Zone2');
            }
        }
    }

    if (["F2807x", "F2837xD", "F2837xS", "F28002x", "F28004x", "F2838x", "F280013x", "F280015x"].includes(Common.getDeviceName()))
    {
        for (var bank_i = 0; bank_i < 2; bank_i++)
        {
            var bankName = Common.getBankNames(bank_i);

            if (inst["CURRENT_LINKPOINTER" + bankName] == undefined)
                continue
            
            var format8HexResult = format8Hex.test(inst["CURRENT_LINKPOINTER" + bankName]);
            var sequenceOf1then0Result = sequenceOf1then0.test(inst["CURRENT_LINKPOINTER" + bankName]);
            
            if (!format8HexResult)
            {
                Common.logError(vo, inst, 'CURRENT_LINKPOINTER' + bankName, 'Invalid 8 digit hex value');
                Common.logError(vo, inst, 'NEXT_LINKPOINTER' + bankName, "Fix the Current LINKPOINTER value");
                Common.logError(vo, inst, 'NEXT_LINKPOINTER_OFFSET' + bankName, "Fix the Current LINKPOINTER value");
            }
            if (!sequenceOf1then0Result)
            {
                Common.logError(vo, inst, 'CURRENT_LINKPOINTER' + bankName, 
                    'The hex value must represent a sequence of 1s followed by a sequence of 0s');
            }

            
            var ds_index = 0;
            for (ds_index in ds)
            {
                var zoneX_instance_obj = inst.$module.$instances[0];
                var zoneY_instance_obj = inst.$module.$instances[1];
                var zoneX_value = zoneX_instance_obj[ds[ds_index].name + bankName];
                var zoneY_value = zoneY_instance_obj[ds[ds_index].name + bankName];

                if (zoneX_value != "UNSECURE" && zoneY_value != "UNSECURE")
                {
                    Common.logError(vo, zoneX_instance_obj, ds[ds_index].name + bankName, 'This memory section is assigned to both Zone1 and Zone2');
                }
            }
        }
    }
    else if(["F28003x"].includes(Common.getDeviceName()))
    {
        for (var bank_i = 0; bank_i < 3; bank_i++)
        {
            var bankName = Common.getBankNames(bank_i);

            if (inst["CURRENT_LINKPOINTER" + bankName] != undefined)
            {
                var format8HexResult = format8Hex.test(inst["CURRENT_LINKPOINTER" + bankName]);
                var sequenceOf1then0Result = sequenceOf1then0.test(inst["CURRENT_LINKPOINTER" + bankName]);
                
                if (!format8HexResult)
                {
                    Common.logError(vo, inst, 'CURRENT_LINKPOINTER' + bankName, 'Invalid 8 digit hex value');
                    Common.logError(vo, inst, 'NEXT_LINKPOINTER' + bankName, "Fix the Current LINKPOINTER value");
                    Common.logError(vo, inst, 'NEXT_LINKPOINTER_OFFSET' + bankName, "Fix the Current LINKPOINTER value");
                }
                if (!sequenceOf1then0Result)
                {
                    Common.logError(vo, inst, 'CURRENT_LINKPOINTER' + bankName, 
                        'The hex value must represent a sequence of 1s followed by a sequence of 0s');
                }
            }

            
            var ds_index = 0;
            for (ds_index in ds)
            {
                var zoneX_instance_obj = inst.$module.$instances[0];
                var zoneY_instance_obj = inst.$module.$instances[1];
                var zoneX_value = zoneX_instance_obj[ds[ds_index].name + bankName];
                var zoneY_value = zoneY_instance_obj[ds[ds_index].name + bankName];

                if (zoneX_value != "UNSECURE" && zoneY_value != "UNSECURE")
                {
                    Common.logError(vo, zoneX_instance_obj, ds[ds_index].name + bankName, 'This memory section is assigned to both Zone1 and Zone2');
                }
            }
        }
    }
    else if(["F28P65x","F28P55x"].includes(Common.getDeviceName()))
    {
        for (var bank_i = 0; bank_i < 5; bank_i++)
        {
            var bankName = Common.getBankNames(bank_i);

            if (inst["CURRENT_LINKPOINTER" + bankName] != undefined)
            {
                var format8HexResult = format8Hex.test(inst["CURRENT_LINKPOINTER" + bankName]);
                var sequenceOf1then0Result = sequenceOf1then0.test(inst["CURRENT_LINKPOINTER" + bankName]);
                
                if (!format8HexResult)
                {
                    Common.logError(vo, inst, 'CURRENT_LINKPOINTER' + bankName, 'Invalid 8 digit hex value');
                    Common.logError(vo, inst, 'NEXT_LINKPOINTER' + bankName, "Fix the Current LINKPOINTER value");
                    Common.logError(vo, inst, 'NEXT_LINKPOINTER_OFFSET' + bankName, "Fix the Current LINKPOINTER value");
                }
                if (!sequenceOf1then0Result)
                {
                    Common.logError(vo, inst, 'CURRENT_LINKPOINTER' + bankName, 
                        'The hex value must represent a sequence of 1s followed by a sequence of 0s');
                }
            }

            
            var ds_index = 0;
            for (ds_index in ds)
            {
                if ("F28P65x".includes(Common.getDeviceName()) | ds_index < 5 | bank_i < 4)
                {
                    var zoneX_instance_obj = inst.$module.$instances[0];
                    var zoneY_instance_obj = inst.$module.$instances[1];
                    var zoneX_value = zoneX_instance_obj[ds[ds_index].name + bankName];
                    var zoneY_value = zoneY_instance_obj[ds[ds_index].name + bankName];

                    if (zoneX_value != "UNSECURE" && zoneY_value != "UNSECURE")
                    {
                        Common.logError(vo, zoneX_instance_obj, ds[ds_index].name + bankName, 'This memory section is assigned to both Zone1 and Zone2');
                    }
                }
            }
        }
    }
}


// Define the common/portable base Watchdog
exports = {
    displayName         : 'ZONE',
    description         : 'ZONE',
    defaultInstanceName : 'ZONE',
    longDescription     : longDescription,
    config              : config,
    validate            : validate
};
