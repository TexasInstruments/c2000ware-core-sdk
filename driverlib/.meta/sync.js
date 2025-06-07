let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sysctl.js");

/* Array of CAN configurables that are common across device families */
let staticConfig = [
    {
        name: "syncOutSource",
        displayName : "SYNCOUT (EXTSYNCOUT) Source",
        description : 'Source for the SYNCOUT (EXTSYNCOUT) signal',
        hidden      : false,
        default     : device_driverlib_peripheral.SysCtl_SyncOutputSource[0].name,
        options     : device_driverlib_peripheral.SysCtl_SyncOutputSource
    },
];

if (["F2837xD", "F2837xS", "F2807x", "F28004x"].includes(Common.getDeviceName()))
{
    staticConfig = staticConfig.concat([    
        //
        // Sync
        //
        {
            name: "epwm1SyncInSource",
            displayName : "EPWM1 Sync In Source",
            description : 'Sync In Source for the Time Base Counter Submodule',
            hidden      : false,
            default     : "SYSCTL_SYNC_IN_SRC_EXTSYNCIN1",
            options     : [
                {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN1", displayName: "SYNC IN SRC EXTSYNCIN1"}
            ],
        },
        {
            name: "epwm4SyncInSource",
            displayName : "EPWM4 Sync In Source",
            description : 'Sync In Source for the Time Base Counter Submodule',
            hidden      : false,
            default     : "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT",
            options     : [
                {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN1", displayName: "SYNC IN SRC EXTSYNCIN1"},
                {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN2", displayName: "SYNC IN SRC EXTSYNCIN2"},
                { name: "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT", displayName: "SYNC IN SRC EPWM1SYNCOUT" },
            ],
        },
        {
            name: "epwm7SyncInSource",
            displayName : "EPWM7 Sync In Source",
            description : 'Sync In Source for the Time Base Counter Submodule',
            hidden      : false,
            default     : "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT",
            options     : [
                {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN1", displayName: "SYNC IN SRC EXTSYNCIN1"},
                {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN2", displayName: "SYNC IN SRC EXTSYNCIN2"},
                { name: "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT", displayName: "SYNC IN SRC EPWM1SYNCOUT" },
                { name: "SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT", displayName: "SYNC IN SRC EPWM4SYNCOUT" },
            ],
        },
    ]);

    if (["F2807x", "F2837xS", "F2837xD"].includes(Common.getDeviceName()))
    {
        staticConfig = staticConfig.concat([
            {
                name: "epwm10SyncInSource",
                displayName : "EPWM10 Sync In Source",
                description : 'Sync In Source for the Time Base Counter Submodule',
                hidden      : false,
                default     : "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT",
                options     : [
                    {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN1", displayName: "SYNC IN SRC EXTSYNCIN1"},
                    {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN2", displayName: "SYNC IN SRC EXTSYNCIN2"},
                    { name: "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT", displayName: "SYNC IN SRC EPWM1SYNCOUT" },
                    { name: "SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT", displayName: "SYNC IN SRC EPWM4SYNCOUT" },
                    { name: "SYSCTL_SYNC_IN_SRC_EPWM7SYNCOUT", displayName: "SYNC IN SRC EPWM7SYNCOUT" },
                ],
            },
        ])
    }

    staticConfig = staticConfig.concat([    
        //
        // Sync
        //
        {
            name: "ecap1SyncInSource",
            displayName : "ECAP1 Sync In Source",
            description : 'Sync In Source for the ECAP1 module',
            hidden      : false,
            default     : "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT",
            options     : [
                {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN1", displayName: "SYNC IN SRC EXTSYNCIN1"},
                {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN2", displayName: "SYNC IN SRC EXTSYNCIN2"},
                { name: "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT", displayName: "SYNC IN SRC EPWM1SYNCOUT" },
                { name: "SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT", displayName: "SYNC IN SRC EPWM4SYNCOUT" },
                { name: "SYSCTL_SYNC_IN_SRC_EPWM7SYNCOUT", displayName: "SYNC IN SRC EPWM7SYNCOUT" },
                { name: "SYSCTL_SYNC_IN_SRC_EPWM10SYNCOUT", displayName: "SYNC IN SRC EPWM10SYNCOUT" },
            ]
        },
        {
            name: "ecap4SyncInSource",
            displayName : "ECAP4 Sync In Source",
            description : 'Sync In Source for the ECAP4 module',
            hidden      : false,
            default     : "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT",
            options     : [
                {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN1", displayName: "SYNC IN SRC EXTSYNCIN1"},
                {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN2", displayName: "SYNC IN SRC EXTSYNCIN2"},
                { name: "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT", displayName: "SYNC IN SRC EPWM1SYNCOUT" },
                { name: "SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT", displayName: "SYNC IN SRC EPWM4SYNCOUT" },
                { name: "SYSCTL_SYNC_IN_SRC_EPWM7SYNCOUT", displayName: "SYNC IN SRC EPWM7SYNCOUT" },
                { name: "SYSCTL_SYNC_IN_SRC_EPWM10SYNCOUT", displayName: "SYNC IN SRC EPWM10SYNCOUT" },
                { name: "SYSCTL_SYNC_IN_SRC_ECAP1SYNCOUT", displayName: "SYNC IN SRC ECAP1SYNCOUT" },
            ]
        },
    ]);

    if (["F28004x"].includes(Common.getDeviceName()))
    {
        staticConfig = staticConfig.concat([
            {
                name: "ecap6SyncInSource",
	            displayName : "ECAP6 Sync In Source",
	            description : 'Sync In Source for the ECAP6 module',
	            hidden      : false,
	            default     : "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT",
	            options     : [
	                {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN1", displayName: "SYNC IN SRC EXTSYNCIN1"},
	                {name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN2", displayName: "SYNC IN SRC EXTSYNCIN2"},
	                { name: "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT", displayName: "SYNC IN SRC EPWM1SYNCOUT" },
	                { name: "SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT", displayName: "SYNC IN SRC EPWM4SYNCOUT" },
	                { name: "SYSCTL_SYNC_IN_SRC_EPWM7SYNCOUT", displayName: "SYNC IN SRC EPWM7SYNCOUT" },
	                { name: "SYSCTL_SYNC_IN_SRC_EPWM10SYNCOUT", displayName: "SYNC IN SRC EPWM10SYNCOUT" },
	                { name: "SYSCTL_SYNC_IN_SRC_ECAP1SYNCOUT", displayName: "SYNC IN SRC ECAP1SYNCOUT" },
	                { name: "SYSCTL_SYNC_IN_SRC_ECAP4SYNCOUT", displayName: "SYNC IN SRC ECAP4SYNCOUT" },
                ]
	        },
        ])
    }
}

var ePWMInstances = Common.peripheralCount("EPWM")
var mcpwmInstances = Common.peripheralNames("MCPWM")
var enable_ADCSOCA = [];
var enable_ADCSOCB = [];
for(var i = 0; i < ePWMInstances; i++) {
    enable_ADCSOCA.push({ name: "SYSCTL_ADCSOC_SRC_PWM" + (i+1) + "SOC" + "A", displayName: "Enable EPWM"+ (i+1) + " ADC SOCA" });
    enable_ADCSOCB.push({ name: "SYSCTL_ADCSOC_SRC_PWM" + (i+1) + "SOC" + "B", displayName: "Enable EPWM"+ (i+1) + " ADC SOCB" });
}

for (let i of mcpwmInstances){
    console.log(i)
    enable_ADCSOCA.push({ name: "SYSCTL_ADCSOC_SRC_PWM" + (i.name.replace("MCPWM","")) + "SOC" + "A", displayName: "Enable "+ (i.name) + " ADC SOCA" });
    enable_ADCSOCB.push({ name: "SYSCTL_ADCSOC_SRC_PWM" + (i.name.replace("MCPWM","")) + "SOC" + "B", displayName: "Enable "+ (i.name) + " ADC SOCB" }); 
}


staticConfig = staticConfig.concat([
    {
        name: "ADCSOCAOutputSelect",
        displayName : "ADC SOCA Output Enable (ADCSOCAO)",
        description : 'Enable all sources for the ADC SOCA external output',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : enable_ADCSOCA
    },
    {
        name: "ADCSOCBOutputSelect",
        displayName : "ADC SOCB Output Enable (ADCSOCBO)",
        description : 'Enable all sources for the ADC SOCB external output',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : enable_ADCSOCB
    },
])

staticConfig = staticConfig.concat([
    {
        name: "ADCSOCOutputLock",
        displayName : "ADC SOCA/B Output Lock",
        description : 'Prevent changes to the ADCSOCAO and ADCSOCBO source',
        hidden      : false,
        default     : false,
    },
    {
        name: "syncOutLock",
        displayName : "EPWM External SYNCOUT Lock",
        description : 'Prevent changes to the SYNCOUT source',
        hidden      : false,
        default     : false,
    },
])



/*
 *  ======== filterHardware ========
 *  Control RX, TX Pin usage by the user specified dataDirection.
 *
 *  param component - hardware object describing signals and
 *                     resources they're attached to
 *
 *  returns Boolean indicating whether or not to allow the component to
 *           be assigned to an instance's $hardware config
 */
function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["SYNC"]));
}

var syncModule = {
    peripheralName: "SYNC",
    displayName: "SYNC",
    maxInstances: 1,
    defaultInstanceName: "mySYNC",
    description: "Synchronization",
    filterHardware : filterHardware,
    moduleStatic : {
        config          : staticConfig,
    },
    //config: config,
    templates: {
        boardc : "/driverlib/sync/sync.board.c.xdt",
        boardh : "/driverlib/sync/sync.board.h.xdt"
    },
};




exports = syncModule;