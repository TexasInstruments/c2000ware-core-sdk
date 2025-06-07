let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_mcpwm.js");

var TzEventConfigNames = [];

/* Array of configurables that are common across device families */
var config = [];

for (var tzEventIndex in device_driverlib_peripheral.MCPWM_TripZoneEvent)
{
    var tzEvent = device_driverlib_peripheral.MCPWM_TripZoneEvent[tzEventIndex];
    var tzEventName = tzEvent.name.replace("MCPWM_TZ_ACTION_EVENT_", "");
    var tzEventConfig = {
        name: "mcpwmTripZone_" + tzEvent.name,
        displayName : tzEventName + " Event",
        description : 'The action to take on ' + tzEvent.name + ". " + "(" + tzEvent.displayName + ")",
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_TripZoneAction[0].name,
        options     : device_driverlib_peripheral.MCPWM_TripZoneAction
    }
    config.push(tzEventConfig);
    TzEventConfigNames.push(tzEventConfig.name);
}

var oneShotConfig = [
    {
        name: "mcpwmTripZone_oneShotSource",
        displayName : "One-Shot Source",
        description : 'Check to enable the source to the One-Shot OR gate',
        hidden      : false,
        minSelections : 0,
        default     : [],
        options     : ()=>{
                        let opt = [];
                        let tz_signal_list = device_driverlib_peripheral.MCPWM_TZ_SIGNAL;
                        for(let option of tz_signal_list){
                            if(option.name.includes("OSHT")){
                                opt.push(option)
                            }
                        }
                        return opt;
                    }
    },

];

var cbcConfig = [
    {
        name: "mcpwmTripZone_cbcSource",
        displayName : "CBC Source",
        description : 'Check to enable the source to the CBC OR gate',
        hidden      : false,
        minSelections : 0,
        default     : [],
        options     : ()=>{
            let opt = [];
            let tz_signal_list = device_driverlib_peripheral.MCPWM_TZ_SIGNAL;
            for(let option of tz_signal_list){
                if(option.name.includes("CBC")){
                    opt.push(option)
                }
            }
            return opt;
        }
    },
    {
        name: "mcpwmTripZone_cbcPulse",
        displayName : "CBC Latch Clear Signal",
        description : 'Select the CBC Trip Zone Latch Clear Signal (TZCLR[CBCPULSE])',
        hidden      : false,
        default     : device_driverlib_peripheral.MCPWM_TripZoneCBCMode[0].name,
        options     : device_driverlib_peripheral.MCPWM_TripZoneCBCMode
    },

];

config = config.concat(oneShotConfig);
config = config.concat(cbcConfig);

var epwmTripZoneSubmodule = {
    displayName: "MCPWM Trip Zone",
    maxInstances: Common.peripheralCount("mcpwm"),
    defaultInstanceName: "MCPWM_TZ",
    description: "Enhanced Pulse Width Modulator Trip Zone",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};


exports = epwmTripZoneSubmodule;