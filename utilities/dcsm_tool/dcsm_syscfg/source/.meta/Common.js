
function logError(vo, inst, field, msg)
{
    if (typeof(field) === 'string') {
        vo[field].errors.push(msg);
    }
    else {
        for (let i = 0; i < field.length; i++) {
            vo[field[i]].errors.push(msg);
        }
    }
}

function logWarning(vo, inst, field, msg)
{
    if (typeof(field) === 'string') {
        vo[field].warnings.push(msg);
    }
    else {
        for (let i = 0; i < field.length; i++) {
            vo[field[i]].warnings.push(msg);
        }
    }
}

function findDuplicates(arrayToCheck)
{
    const count = arrayToCheck =>
      arrayToCheck.reduce((a, b) => ({ ...a,
        [b]: (a[b] || 0) + 1
      }), {}) // don't forget to initialize the accumulator

    const duplicates = dict =>
      Object.keys(dict).filter((a) => dict[a] > 1)

    //console.log(count(arrayToCheck)) // { Mike: 1, Matt: 1, Nancy: 2, Adam: 1, Jenny: 1, Carl: 1 }
    //console.log(duplicates(count(arrayToCheck)))

    return {count: count(arrayToCheck), duplicates: duplicates(count(arrayToCheck))};
}

function getDeviceName()
{
    var deviceName = system.deviceData.device;
    return deviceName
}

function stringOrEmpty(stringToCheck, stringToAdd)
{
    if (stringToCheck != "")
    {
        return stringToAdd;
    }
    return "";
}

function getGPIOs()
{
    var allGpioNames = [];
    let gpio = system.deviceData.interfaces.GPIO;
    if (gpio != null)
    {
        for (var i = 0; i < gpio.peripherals.length; i++)
        {
            var gpioperiph = gpio.peripherals[i];
            allGpioNames.push(gpioperiph.name);
        }
    }
    return allGpioNames
}

function getZoneOptions(){
    return [
        {name: "SECURE", displayName: "Secured by this zone"},
        {name: "SECUREEXEONLY", displayName: "Secured by this zone (EXEONLY)"},
        {name: "UNSECURE", displayName: "Unsecure (or secured by other zone)"}
    ];
}

function getNonEXEOptions(){
    return [
        {name: "SECURE", displayName: "Secured by this zone"},
        {name: "UNSECURE", displayName: "Unsecure (or secured by other zone)"}
    ];
}

function getCLAOptions(){
    return [
        {name: "SECURE", displayName: "Secured by this zone"},
        {name: "UNSECURE", displayName: "Unsecure (or secured by other zone)"}
    ];
}

function getRAMs(){
    return system.getScript("/utilities/dcsm_tool/dcsm_syscfg/source/ram_sect_info/" + 
        getDeviceName().toLowerCase() + "_ram.js");
}

function getSECTs(){
    return system.getScript("/utilities/dcsm_tool/dcsm_syscfg/source/ram_sect_info/" + 
        getDeviceName().toLowerCase() + "_sect.js");
}

function getBankNames(bank){
    let BANK_NAMES = ["", "_BANK1", "_BANK2", "_BANK3", "_BANK4"];
    return BANK_NAMES[bank];
} 

function getLinkPointerInfo()
{
    if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x"].includes(getDeviceName()))
    {
        return {
            startValue: "0x00003FFF",
            startValueHex: 0x00003FFF,
            startValueCaps: "0X00003FFF",
            zsbSize: 0x20,
            endZsbOffset: "0x1E0",
            endZsbOffsetHex: 0x1E0
        }
    }
    else
    {
        return {
            startValue: "0x1FFFFFFF",
            startValueHex: 0x1FFFFFFF,
            startValueCaps: "0X1FFFFFFF",
            zsbSize: 0x10,
            endZsbOffset: "0x1F0",
            endZsbOffsetHex: 0x1F0
        }
    }
}

function onChangeCurrentLinkPointer(inst, ui)
{
    for (var bank_i = 0; bank_i < 2; bank_i++)
    {
        var bankName = getBankNames(bank_i);
        if (inst["CURRENT_LINKPOINTER" + bankName] == undefined)
            continue
        
        if(inst["CURRENT_LINKPOINTER" + bankName].toUpperCase() == getLinkPointerInfo().startValueCaps)
        {
            ui["UPDATE_LINKPOINTER" + bankName].readOnly = false;
        }
        else
        {
            ui["UPDATE_LINKPOINTER" + bankName].readOnly = true;
            inst["UPDATE_LINKPOINTER" + bankName] = true;
        }

        var nextLinkPointer = inst["CURRENT_LINKPOINTER" + bankName].toUpperCase()
        if (inst["CURRENT_LINKPOINTER" + bankName].toUpperCase() == getLinkPointerInfo().startValueCaps && inst["UPDATE_LINKPOINTER" + bankName] != true)
        {
            inst["NEXT_LINKPOINTER" + bankName] = getLinkPointerInfo().startValue;
            inst["NEXT_LINKPOINTER_OFFSET" + bankName] = "0x20";
        }
        else
        {
            nextLinkPointer = (parseInt(nextLinkPointer) << 1) & getLinkPointerInfo().startValueHex;
            inst["NEXT_LINKPOINTER" + bankName] = "0x" + nextLinkPointer.toString(16).padStart(8, '0').toUpperCase();
            var binaryNextLinkPointer = nextLinkPointer.toString(2)
            var outOf12 = 0;
            if (binaryNextLinkPointer.indexOf(0) != -1)
            {
                outOf12 = binaryNextLinkPointer.length - binaryNextLinkPointer.indexOf(0)
                inst["NEXT_LINKPOINTER_OFFSET" + bankName] = "0x" + (0x20 + getLinkPointerInfo().zsbSize*(outOf12)).toString(16).toUpperCase();
                if (binaryNextLinkPointer == 0)
                {
                    inst["NEXT_LINKPOINTER_OFFSET" + bankName] = getLinkPointerInfo().endZsbOffset;
                }
            }

        }
    }

}

function getLinkPointerConfigOptions(bank)
{
    var bankName = getBankNames(bank);
    var dispBankName = bankName.replace("_", " ");
    var linkPointerAddressZone1 = "0x78000";
    var linkPointerAddressZone2 = "0x78200";
    if (bank == 1)
    {
        if (["F28004x", "F28002x"].includes(getDeviceName()))
        {
            linkPointerAddressZone1 = "0x78400";
            linkPointerAddressZone2 = "0x78600";
        }
    }

    return [
        {
            name        : 'CURRENT_LINKPOINTER' + bankName,
            displayName : 'Current LINKPOINTER' + dispBankName,
            description : 'Please input the current LINKPOINTER value available'+
                            ' at address ' + linkPointerAddressZone1 + ' for Zone1 and ' + linkPointerAddressZone2 + ' for Zone2 of the device memory.',
            hidden      : false,
            default     : getLinkPointerInfo().startValue,
            onChange    : onChangeCurrentLinkPointer
        },
    
        {
            name        : 'UPDATE_LINKPOINTER' + bankName,
            displayName : 'Update the LINKPOINTER' + dispBankName,
            description : 'Checkbox only available when the current LINKPOINTER is set to the default value.' +
                          ' This increments the next LINKPOINTER, or leaves the default for' +
                          ' first time programming. Uncheck this box if the LINKPOINTER value in the device memory is' + 
                          ' set to the default value and you have not ever programmed the OTP in this device.',
            hidden      : false,
            default     : false,
            onChange    : onChangeCurrentLinkPointer
    
        },
    
        {
            name        : 'NEXT_LINKPOINTER' + bankName,
            readOnly    : true,
            displayName : 'Next LINKPOINTER' + dispBankName,
            description : 'The LINKPOINTER value which will be used with this update.',
            hidden      : false,
            default     : getLinkPointerInfo().startValue
        },
        
        {
            name        : 'NEXT_LINKPOINTER_OFFSET' + bankName,
            readOnly    : true,
            displayName : 'Zone Select Block (ZSB) Offset' + dispBankName,
            description : 'The Zone Select Block (ZSB) value which will be used with this update.',
            hidden      : false,
            default     : '0x20'
        },
    ]
}

function getNextLinkPointerIndex(inst)
{
    var next_linkpointer_offset = parseInt(inst["NEXT_LINKPOINTER_OFFSET"]);
    var next_linkpointer_index = (next_linkpointer_offset - 0x20)/getLinkPointerInfo().zsbSize;

    return next_linkpointer_index
}

function getZone2Password1Mask(zsb_index){
    var DEFAULT_ZONE2_PASSWORD_MASK = [];

    if (["F28004x", "F28002x"].includes(getDeviceName()))
    {
        DEFAULT_ZONE2_PASSWORD_MASK =
        [
            { zsb: 0x00078220, mask: 0xe3ffffff },
            { zsb: 0x00078230, mask: 0x977fffff },
            { zsb: 0x00078240, mask: 0xf1ffffff },
            { zsb: 0x00078250, mask: 0x9b7fffff },
            { zsb: 0x00078260, mask: 0x5b7fffff },
            { zsb: 0x00078270, mask: 0x2fffffff },
            { zsb: 0x00078280, mask: 0x1fffffff },
            { zsb: 0x00078290, mask: 0x6b7fffff },
            { zsb: 0x000782a0, mask: 0xab7fffff },
            { zsb: 0x000782b0, mask: 0x37ffffff },
            { zsb: 0x000782c0, mask: 0x4f7fffff },
            { zsb: 0x000782d0, mask: 0x3bffffff },
            { zsb: 0x000782e0, mask: 0xe5ffffff },
            { zsb: 0x000782f0, mask: 0x8f7fffff },
            { zsb: 0x00078300, mask: 0x2fffffff },
            { zsb: 0x00078310, mask: 0x5b7fffff },
            { zsb: 0x00078320, mask: 0x9b7fffff },
            { zsb: 0x00078330, mask: 0xf1ffffff },
            { zsb: 0x00078340, mask: 0x977fffff },
            { zsb: 0x00078350, mask: 0xe3ffffff },
            { zsb: 0x00078360, mask: 0xcbffffff },
            { zsb: 0x00078370, mask: 0x577fffff },
            { zsb: 0x00078380, mask: 0x8f7fffff },
            { zsb: 0x00078390, mask: 0xe5ffffff },
            { zsb: 0x000783a0, mask: 0x3bffffff },
            { zsb: 0x000783b0, mask: 0x4f7fffff },
            { zsb: 0x000783c0, mask: 0x37ffffff },
            { zsb: 0x000783d0, mask: 0xab7fffff },
            { zsb: 0x000783e0, mask: 0x6b7fffff },
            { zsb: 0x000783f0, mask: 0x1fffffff },
        ]
    }
    else if (["F2838x", "F28003x", "F280013x", "F280015x","F28P65x"].includes(getDeviceName()))
    {
        DEFAULT_ZONE2_PASSWORD_MASK =
        [
            { zsb: 0x00078220, mask: 0x1f7fffff },
            { zsb: 0x00078240, mask: 0xe57fffff },
            { zsb: 0x00078260, mask: 0x4fffffff },
            { zsb: 0x00078280, mask: 0xe37fffff },
            { zsb: 0x000782a0, mask: 0x57ffffff },
            { zsb: 0x000782c0, mask: 0x5bffffff },
            { zsb: 0x000782e0, mask: 0xf17fffff },
            { zsb: 0x00078300, mask: 0x3b7fffff },
            { zsb: 0x00078320, mask: 0x8fffffff },
            { zsb: 0x00078340, mask: 0x6bffffff },
            { zsb: 0x00078360, mask: 0x377fffff },
            { zsb: 0x00078380, mask: 0x9bffffff },
            { zsb: 0x000783a0, mask: 0x2f7fffff },
            { zsb: 0x000783c0, mask: 0xcb7fffff },
            { zsb: 0x000783e0, mask: 0x97ffffff },
        ]
    }

    return DEFAULT_ZONE2_PASSWORD_MASK[zsb_index]
}

function getZone1Password1Mask(zsb_index){
    var DEFAULT_ZONE1_PASSWORD_MASK = [];
    
    if (["F28004x", "F28002x"].includes(getDeviceName()))
    {
        DEFAULT_ZONE1_PASSWORD_MASK = [
            { zsb: 0x00078020, mask: 0x47ffffff },
            { zsb: 0x00078030, mask: 0xdb7fffff },
            { zsb: 0x00078040, mask: 0x4bffffff },
            { zsb: 0x00078050, mask: 0x3f7fffff },
            { zsb: 0x00078060, mask: 0xcfbfffff },
            { zsb: 0x00078070, mask: 0x8bffffff },
            { zsb: 0x00078080, mask: 0x53ffffff },
            { zsb: 0x00078090, mask: 0xcf7fffff },
            { zsb: 0x000780a0, mask: 0xe77fffff },
            { zsb: 0x000780b0, mask: 0x93ffffff },
            { zsb: 0x000780c0, mask: 0xeb7fffff },
            { zsb: 0x000780d0, mask: 0x69ffffff },
            { zsb: 0x000780e0, mask: 0xa9ffffff },
            { zsb: 0x000780f0, mask: 0xdd7fffff },
            { zsb: 0x00078100, mask: 0x8bffffff },
            { zsb: 0x00078110, mask: 0xcfbfffff },
            { zsb: 0x00078120, mask: 0x3f7fffff },
            { zsb: 0x00078130, mask: 0x4bffffff },
            { zsb: 0x00078140, mask: 0xdb7fffff },
            { zsb: 0x00078150, mask: 0x47ffffff },
            { zsb: 0x00078160, mask: 0x87ffffff },
            { zsb: 0x00078170, mask: 0xf37fffff },
            { zsb: 0x00078180, mask: 0xdd7fffff },
            { zsb: 0x00078190, mask: 0xa9ffffff },
            { zsb: 0x000781a0, mask: 0x69ffffff },
            { zsb: 0x000781b0, mask: 0xeb7fffff },
            { zsb: 0x000781c0, mask: 0x93ffffff },
            { zsb: 0x000781d0, mask: 0xe77fffff },
            { zsb: 0x000781e0, mask: 0xcf7fffff },
            { zsb: 0x000781f0, mask: 0x53ffffff },
        ]
    }
    else if (["F2838x", "F28003x", "F280013x", "F280015x","F28P65x"].includes(getDeviceName()))
    {
        DEFAULT_ZONE1_PASSWORD_MASK = [
            { zsb: 0x00078020, mask: 0x4d7fffff },
            { zsb: 0x00078040, mask: 0x5f7fffff },
            { zsb: 0x00078060, mask: 0x1dffffff },
            { zsb: 0x00078080, mask: 0xaf7fffff },
            { zsb: 0x000780a0, mask: 0x1bffffff },
            { zsb: 0x000780c0, mask: 0x17ffffff },
            { zsb: 0x000780e0, mask: 0xbd7fffff },
            { zsb: 0x00078100, mask: 0x9f7fffff },
            { zsb: 0x00078120, mask: 0x2bffffff },
            { zsb: 0x00078140, mask: 0x27ffffff },
            { zsb: 0x00078160, mask: 0x7b7fffff },
            { zsb: 0x00078180, mask: 0xc9ffffff },
            { zsb: 0x000781a0, mask: 0x7d7fffff },
            { zsb: 0x000781c0, mask: 0x6f7fffff },
            { zsb: 0x000781e0, mask: 0x33ffffff },
        ]
    }

    return DEFAULT_ZONE1_PASSWORD_MASK[zsb_index]
}

function getDefaultPASSWORDLOCKValueMask(zone){
    var DEFAULT_ZONE1_PASSWORDLOCK_LSW = "0xFFFFFFFF";
    var DEFAULT_ZONE2_PASSWORDLOCK_LSW = "0xFFFFFFFF";
    var DEFAULT_ZONE1_PASSWORDLOCK_MSW = "0xFFFFFFFF";
    var DEFAULT_ZONE2_PASSWORDLOCK_MSW = "0xFFFFFFFF";

    if (["F28004x", "F28002x"].includes(getDeviceName()))
    {
        DEFAULT_ZONE1_PASSWORDLOCK_LSW = "0xFB7FFFFF";
        DEFAULT_ZONE2_PASSWORDLOCK_LSW = "0xBF7FFFFF";
        DEFAULT_ZONE1_PASSWORDLOCK_MSW = "0x7FFFFFFF";
        DEFAULT_ZONE2_PASSWORDLOCK_MSW = "0x77FFFFFF";
    }
    else if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x"].includes(getDeviceName()))
    {
        DEFAULT_ZONE1_PASSWORDLOCK_LSW = "0xFB7FFFFF";
        DEFAULT_ZONE2_PASSWORDLOCK_LSW = "0x1F7FFFFF";
    }

    if (zone == 1)
    {
        return [DEFAULT_ZONE1_PASSWORDLOCK_LSW, DEFAULT_ZONE1_PASSWORDLOCK_MSW]
    }
    else if (zone == 2)
    {
        return [DEFAULT_ZONE2_PASSWORDLOCK_LSW, DEFAULT_ZONE2_PASSWORDLOCK_MSW]
    }
}

function getDefaultJTAGLOCKValueMask(zone){
    var DEFAULT_ZONE1_JTAGLOCK = "0xFFFF000F";
    return [DEFAULT_ZONE1_JTAGLOCK]
}

function getDefaultJTAGPSWDHValueMask(zone){
    var DEFAULT_ZONE1_JTAGPSWDH0 = "0x4BFFFFFF";
    var DEFAULT_ZONE1_JTAGPSWDH1 = "0x3FFFFFFF";
    return [DEFAULT_ZONE1_JTAGPSWDH0, DEFAULT_ZONE1_JTAGPSWDH1]
}

function getDefaultJTAGPSWDL1ValueMask(zsb_index){
    var DEFAULT_ZONE1_JTAGPSWDL1_MASK = "0x2BFFFFFF";

    if (["F2838x", "F28003x", "F280013x", "F280015x", "F28P65x"].includes(getDeviceName()))
    {
        DEFAULT_ZONE1_JTAGPSWDL1_MASK = [
            { zsb: 0x00078020, mask: 0x2bffffff },
            { zsb: 0x00078040, mask: 0x27ffffff },
            { zsb: 0x00078060, mask: 0x7b7fffff },
            { zsb: 0x00078080, mask: 0xc9ffffff },
            { zsb: 0x000780a0, mask: 0x7d7fffff },
            { zsb: 0x000780c0, mask: 0x6f7fffff },
            { zsb: 0x000780e0, mask: 0x33ffffff },
            { zsb: 0x00078100, mask: 0x0fffffff },
            { zsb: 0x00078120, mask: 0xbb7fffff },
            { zsb: 0x00078140, mask: 0x5f7fffff },
            { zsb: 0x00078160, mask: 0x1dffffff },
            { zsb: 0x00078180, mask: 0xaf7fffff },
            { zsb: 0x000781a0, mask: 0x1bffffff },
            { zsb: 0x000781c0, mask: 0x17ffffff },
            { zsb: 0x000781e0, mask: 0xbd7fffff },
        ]
    }

    return DEFAULT_ZONE1_JTAGPSWDL1_MASK[zsb_index]
}

function getDefaultCRCLOCKValueMask(zone){
    var DEFAULT_ZONE1_CRCLOCK_LSW = "0xFFFFFFFF";
    var DEFAULT_ZONE2_CRCLOCK_LSW = "0xFFFFFFFF";
    var DEFAULT_ZONE1_CRCLOCK_MSW = "0xFFFFFFFF";
    var DEFAULT_ZONE2_CRCLOCK_MSW = "0xFFFFFFFF";

    if (["F28004x", "F28002x"].includes(getDeviceName()))
    {
        DEFAULT_ZONE1_CRCLOCK_LSW = "0x4BFFFFFF";
        DEFAULT_ZONE2_CRCLOCK_LSW = "0x0FFFFFFF";
        DEFAULT_ZONE1_CRCLOCK_MSW = "0x3FFFFFFF";
        DEFAULT_ZONE2_CRCLOCK_MSW = "0x37FFFFFF";
    }
    else if (["F2838x", "F28003x", "F280013x", "F280015x","F28P65x"].includes(getDeviceName()))
    {
        DEFAULT_ZONE1_CRCLOCK_LSW = "0x7FFFFFFF";
        DEFAULT_ZONE2_CRCLOCK_LSW = "0x3FFFFFFF";
    }
    
    if (zone == 1)
    {
        return [DEFAULT_ZONE1_CRCLOCK_LSW, DEFAULT_ZONE1_CRCLOCK_MSW]
    }
    else if (zone == 2)
    {
        return [DEFAULT_ZONE2_CRCLOCK_LSW, DEFAULT_ZONE2_CRCLOCK_MSW]
    }
}

exports = {
    findDuplicates: findDuplicates,
    stringOrEmpty: stringOrEmpty,
    getDeviceName : getDeviceName,
    getGPIOs : getGPIOs,
    logError : logError,
    logWarning : logWarning,
    getZoneOptions : getZoneOptions,
    getCLAOptions : getCLAOptions,
    getRAMs : getRAMs,
    getSECTs : getSECTs,
    onChangeCurrentLinkPointer : onChangeCurrentLinkPointer,
    getLinkPointerConfigOptions : getLinkPointerConfigOptions,
    getBankNames : getBankNames,
    getNextLinkPointerIndex : getNextLinkPointerIndex,
    getZone1Password1Mask : getZone1Password1Mask,
    getZone2Password1Mask : getZone2Password1Mask,
    getDefaultPASSWORDLOCKValueMask : getDefaultPASSWORDLOCKValueMask,
    getDefaultCRCLOCKValueMask : getDefaultCRCLOCKValueMask,
    getDefaultJTAGLOCKValueMask : getDefaultJTAGLOCKValueMask,
    getDefaultJTAGPSWDHValueMask : getDefaultJTAGPSWDHValueMask,
    getDefaultJTAGPSWDL1ValueMask : getDefaultJTAGPSWDL1ValueMask,
    getNonEXEOptions : getNonEXEOptions,
};