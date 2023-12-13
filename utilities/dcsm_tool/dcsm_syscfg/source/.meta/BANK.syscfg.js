"use strict";

let Common   = system.getScript('/utilities/dcsm_tool/dcsm_syscfg/source/Common.js');
var zoneOptions = Common.getZoneOptions();
let device_sect = Common.getSECTs();
var ds = device_sect[Common.getDeviceName().toLowerCase() + "_sect"]


/* Intro splash on GUI */
let longDescription = 'ZONE flash bank.';

let config = [
    
]

config = config.concat(Common.getLinkPointerConfigOptions())
config = config.concat(ds)


// Define the common/portable base Watchdog
exports = {
    displayName         : 'BANK',
    description         : 'Flash Bank',
    defaultInstanceName : 'BANK',
    longDescription     : longDescription,
    config              : config
};