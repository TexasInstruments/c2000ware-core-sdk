let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_epwm.js");

var TzEventConfigNames = [];
var TzAdvEventConfigNames = [];

function onChangeUseAdvancedEPWMTripZoneActions(inst, ui)
{
    for (var tzEventConfigNameIndex in TzEventConfigNames)
    {
        var tzEventConfigName = TzEventConfigNames[tzEventConfigNameIndex];
        //ui[tzEventConfigName].hidden = inst.epwmTripZone_useAdvancedEPWMTripZoneActions;
        if (inst.epwmTripZone_useAdvancedEPWMTripZoneActions)
        {
            ui[tzEventConfigName].hidden = true;
        }
        else
        {
            ui[tzEventConfigName].hidden = false;
            inst[tzEventConfigName] = device_driverlib_peripheral.EPWM_TripZoneAction[0].name; // Set to default
        }
    }
    for (var tzAdvEventConfigNameIndex in TzAdvEventConfigNames)
    {
        var tzAdvEventConfigName = TzAdvEventConfigNames[tzAdvEventConfigNameIndex];
        //ui[tzAdvEventConfigName].hidden = !inst.epwmTripZone_useAdvancedEPWMTripZoneActions;
        if (!inst.epwmTripZone_useAdvancedEPWMTripZoneActions)
        {
            ui[tzAdvEventConfigName].hidden = true;
            inst[tzAdvEventConfigName] = device_driverlib_peripheral.EPWM_TripZoneAdvancedAction[0].name; // Set to default
        }
        else
        {
            ui[tzAdvEventConfigName].hidden = false;
        }
        
    }
    
}

/* Array of configurables that are common across device families */
var config = [
    {
        name: "epwmTripZone_useAdvancedEPWMTripZoneActions",
        displayName : "Use Advanced EPWM Trip Zone Actions",
        description : 'Check this to use Advanced EPWM trip zone actions. Uncheck to use legacy (TZCTL2[ETZE])',
        hidden      : false,
        default     : false,
        onChange    : onChangeUseAdvancedEPWMTripZoneActions
    },

];

for (var tzEventIndex in device_driverlib_peripheral.EPWM_TripZoneEvent)
{
    var tzEvent = device_driverlib_peripheral.EPWM_TripZoneEvent[tzEventIndex];
    var tzEventName = tzEvent.name.replace("EPWM_TZ_ACTION_EVENT_", "");
    var tzEventConfig = {
        name: "epwmTripZone_" + tzEvent.name,
        displayName : tzEventName + " Event",
        description : 'The action to take on ' + tzEvent.name + ". " + "(" + tzEvent.displayName + ")",
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_TripZoneAction[0].name,
        options     : device_driverlib_peripheral.EPWM_TripZoneAction
    }
    config.push(tzEventConfig);
    TzEventConfigNames.push(tzEventConfig.name);
}


for (var tzEventIndex in device_driverlib_peripheral.EPWM_TripZoneAdvancedEvent)
{
    var tzEvent = device_driverlib_peripheral.EPWM_TripZoneAdvancedEvent[tzEventIndex];
    var tzEventName = tzEvent.name.replace("EPWM_TZ_ADV_ACTION_EVENT_", "");
    var tzEventConfig = {
        name: "epwmTripZone_" + tzEvent.name,
        displayName : tzEventName + " Event (Adv)",
        description : 'The action to take on ' + tzEvent.name + ". " + "(" + tzEvent.displayName + ")",
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_TripZoneAdvancedAction[0].name,
        options     : device_driverlib_peripheral.EPWM_TripZoneAdvancedAction
    }
    config.push(tzEventConfig);
    TzAdvEventConfigNames.push(tzEventConfig.name);
}

for (var epwmX of ["A", "B"])
{
    for (var tzEventIndex in device_driverlib_peripheral.EPWM_TripZoneAdvDigitalCompareEvent)
    {
        var tzEvent = device_driverlib_peripheral.EPWM_TripZoneAdvDigitalCompareEvent[tzEventIndex];
        var tzEventName = tzEvent.name.replace("EPWM_TZ_ADV_ACTION_EVENT_", "").replace("DCx", "DC" + epwmX);
        var tzEventConfig = {
            name: "epwmTripZone_" + tzEvent.name + "_" + epwmX,
            displayName : tzEventName + " Event (Adv)",
            description : 'For EPWMx' + epwmX + ' ,the action to take on ' + tzEvent.name + ". " + "(" + tzEvent.displayName + ")",
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_TripZoneAdvancedAction[0].name,
            options     : device_driverlib_peripheral.EPWM_TripZoneAdvancedAction
        }
        config.push(tzEventConfig);
        TzAdvEventConfigNames.push(tzEventConfig.name);
    }
}

var oneShotConfig = [
    {
        name: "epwmTripZone_oneShotSource",
        displayName : "One-Shot Source",
        description : 'Check to enable the source to the One-Shot OR gate',
        hidden      : false,
        minSelections : 0,
        default     : [],
        options     : device_driverlib_peripheral.EPWM_TZ_SIGNAL.slice(8,16)
    },

];

if(["F28P65x"].includes(Common.getDeviceName()))
{
    oneShotConfig.push(
        {
            name: "epwmTripZone_oneShotSourceAdditional",
            displayName : "Additional One-Shot Source",
            description : 'Check to enable the source to the One-Shot OR gate',
            hidden      : false,
            minSelections : 0,
            default     : [],
            options     : [{ name: "EPWM_TZ_SIGNAL_CAPEVT_OST", displayName: "One-shot Capture event" }],
        },     
    )
}

var cbcConfig = [
    {
        name: "epwmTripZone_cbcSource",
        displayName : "CBC Source",
        description : 'Check to enable the source to the CBC OR gate',
        hidden      : false,
        minSelections : 0,
        default     : [],
        options     : device_driverlib_peripheral.EPWM_TZ_SIGNAL.slice(0,8)
    },
    {
        name: "epwmTripZone_cbcPulse",
        displayName : "CBC Latch Clear Signal",
        description : 'Select the CBC Trip Zone Latch Clear Signal (TZCLR[CBCPULSE])',
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_CycleByCycleTripZoneClearMode[0].name,
        options     : device_driverlib_peripheral.EPWM_CycleByCycleTripZoneClearMode
    },

];

if(["F28P65x"].includes(Common.getDeviceName()))
{
    cbcConfig.push(
        {
            name: "epwmTripZone_cbcSourceAdditional",
            displayName : "Additional CBC Source",
            description : 'Check to enable the source to the CBC OR gate',
            hidden      : false,
            minSelections : 0,
            default     : [],
            options     : [{ name: "EPWM_TZ_SIGNAL_CAPEVT_OST", displayName: "One-shot Capture event" }],
        },
    )
}


var interruptConfig = [
    {
        name: "epwmTripZone_tzInterruptSource",
        displayName : "TZ Interrupt Source (ORed)",
        description : 'Select the all the signals which should be enabled to generate a TZINT.',
        hidden      : false,
        minSelections : 0,
        default     : [],
        options     : device_driverlib_peripheral.EPWM_TZ_INTERRUPT
    },
    {
        name        : "epwmTripZone_registerInterrupts",
        displayName : "Register Interrupt Handler",
        description : 'Whether or not to register interrupt handlers in the interrupt module.',
        hidden      : false,
        default     : false
        
    },

]

if(["F28P65x"].includes(Common.getDeviceName()))
{
    var tripOutConfig = [
        {
            name: "epwmTripZone_tripOut",
            displayName : "TRIPOUT Source",
            description : 'Check to enable the source to the TRIPOUT Mux',
            hidden      : false,
            minSelections : 0,
            default     : [],
            options     : device_driverlib_peripheral.EPWM_selectTripOutSource
        },

    ];
}

config = config.concat(oneShotConfig);
config = config.concat(cbcConfig);
config = config.concat(interruptConfig);
if(["F28P65x"].includes(Common.getDeviceName()))
{
    config = config.concat(tripOutConfig);
}


var epwmTripZoneSubmodule = {
    displayName: "EPWM Trip Zone",
    maxInstances: Common.peripheralCount("EPWM"),
    defaultInstanceName: "EPWM_TZ",
    description: "Enhanced Pulse Width Modulator Trip Zone",
    config: config,
    moduleInstances: (inst) => {
        if (inst.epwmTripZone_registerInterrupts)
        {
            return [{
                name: "epwmTZInt",      
                displayName: "EPWM TZ Interrupt ",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
            		$name : inst.$name + "_TZ_INT",
                    int : "INT_" + inst.$name,
                    pinmuxPeripheralModule : "epwm",
                    driverlibInt: "INT_#_TZ"
                }
            }]
        }
        return [];
    },
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};


exports = epwmTripZoneSubmodule;