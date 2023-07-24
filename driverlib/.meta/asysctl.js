let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_asysctl.js");

function onChangeAnalogRef(inst, ui)
{
    if (["F28004x","F28002x", "F28003x","F280013x", "F280015x", "F28P65x"].includes(Common.getDeviceName())){
        if (inst.analogReference == "INTERNAL"){
            ui.analogReferenceVoltage.hidden = false
        }
        else {
            ui.analogReferenceVoltage.hidden = true
        }
    }
}

/* Array of CAN configurables that are common across device families */
let staticConfig = [
    {
        name: "GROUP_TEMP_CONTROL",
        displayName: "Temperature Control",
        description: "",
        longDescription: "",
        collapsed: false,
        config: [
            // enableTemperatureSensor / disableTemperatureSensor
            {
                name: "enableTemperatureSensor",
                displayName : "Enable Temperature Sensor",
                default: false,
            },
            // lockTemperatureSensor
            {
                name: "lockTemperatureSensor",
                displayName : "Lock Temperature Sensor Control Register",
                default: false,
            },
        ]
    },   
];

//**************************************************************************
// analogReference OPTIONS - choose which device+package combinations have 
// only one reference mode option

var analogReference_opts = [];

// Devices WITHOUT internal reference mode (no VREFHI/VREFLO pins):
// 32pin package for F280013x+F280015x
if ((Common.getDevicePackage() == "32RHB") &&                   // 32pin package
    (["F280013x","F280015x"].includes(Common.getDeviceName()))) // for F280013x/15x
{
    analogReference_opts = [
        {name: "EXTERNAL", displayName: "External"}
    ];
}
// use below else-if statement for future devices that don't have 
// VREFHI/VREFLO, so we don't complicate the logic above
// else if()
// {
// }
// All other device+package combos that have "analogReference" option have 
// both external and internal options
else
{
    analogReference_opts = [
        {name: "INTERNAL", displayName: "Internal"},
        {name: "EXTERNAL", displayName: "External"},
    ];
}

if (["F28004x","F28002x", "F28003x","F280013x","F280015x", "F28P65x"].includes(Common.getDeviceName()))
{
    staticConfig.push(
        {
            name: "GROUP_ANAREF",
            displayName: "Analog Reference",
            description: "",
            longDescription: "",
            collapsed: false,
            config: [
                // setAnalogReferenceInternal / setAnalogReferenceExternal
                {
                    name        : "analogReference",
                    displayName : "Analog Reference",
                    onChange    : onChangeAnalogRef, 
                    default     : "EXTERNAL",
                    options     : analogReference_opts
                },
                // setAnalogReference2P5 / setAnalogReference1P65
                {
                    name        : "analogReferenceVoltage",
                    displayName : "Analog Reference Voltage",
                    hidden      : true, 
                    default     : "2P5",
                    options     : 
                    [
                        {name: "2P5", displayName: "2.5V"},
                        {name: "1P65", displayName: "1.65V"},
                    ]
                },
            ]
        }, 
    );
}
if (["F280013x","F280015x"].includes(Common.getDeviceName()))
{
    staticConfig.push(
        {
            name: "GROUP_COMPLDAC",
            displayName: "External DACL Enable",
            description: "",
            longDescription: "This function disables CMPSSx.COMPL and the associated DAC will act as a general purpose DAC with 11 bit resolution; enables CMPSS external DAC",
            collapsed: false,
            config: [
                {
                    name        : "externalDACLEnable",
                    displayName : "CMPSS DACL Output Enable",
                    default     : false,
                },
            ]
        }, 
    );
}


var sharedModuleInstances = undefined;

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
    return (Common.typeMatches(component.type, ["ASYSCTL"]));
}

var asysctlModule = {
    peripheralName: "ASYSCTL",
    displayName: "ASYSCTL",
    maxInstances: 1,
    defaultInstanceName: "myASYSCTL",
    description: "Analog SysCtl",
    filterHardware : filterHardware,
    moduleStatic : {
        config          : staticConfig,
    },
    //config: config,
    templates: {
        boardc : "/driverlib/asysctl/asysctl.board.c.xdt",
        boardh : "/driverlib/asysctl/asysctl.board.h.xdt"
    },
};
exports = asysctlModule;