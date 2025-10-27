let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_ecap.js");

function onChangeECAPInstance(inst, ui)
{
    if (["F2807x","F2837xD","F2837xS"].includes(Common.getDeviceName())){
        if (inst.ecapBase == "ECAP1_BASE"){
            inst.ecapInputReadOnly = "ECAP_INPUT_INPUTXBAR7"
        }
        else if (inst.ecapBase == "ECAP2_BASE"){
            inst.ecapInputReadOnly = "ECAP_INPUT_INPUTXBAR8"
        }
        else if (inst.ecapBase == "ECAP3_BASE"){
            inst.ecapInputReadOnly = "ECAP_INPUT_INPUTXBAR9"
        }
        else if (inst.ecapBase == "ECAP4_BASE"){
            inst.ecapInputReadOnly = "ECAP_INPUT_INPUTXBAR10"
        }
        else if (inst.ecapBase == "ECAP5_BASE"){
            inst.ecapInputReadOnly = "ECAP_INPUT_INPUTXBAR11"
        }
        else if (inst.ecapBase == "ECAP6_BASE"){
            inst.ecapInputReadOnly = "ECAP_INPUT_INPUTXBAR12"
        }
    }
}

function onChangeECAPMode(inst, ui)
{
    if (inst.ecapMode == "CAPTURE"){
        //CAPTURE Options
        ui.eventPrescaler.hidden = false
        ui.eventOnePolarity.hidden = false
        ui.eventTwoPolarity.hidden = false
        ui.eventThreePolarity.hidden = false
        ui.eventFourPolarity.hidden = false
        ui.captureMode.hidden = false
        if (inst.useInterrupts){       
            ui.interruptSourceCapture.hidden = false
            ui.interruptSourceAPWM.hidden = true
        }
        ui.eventStop.hidden = false
        ui.counterResetOnEvent.hidden = false
        ui.reArm.hidden = false
        if (["F28004x","F28002x","F28003x","F280013x","F280015x","F2838x","F28P65x", "F28P55x","F28P551x","F28E12x"].includes(Common.getDeviceName())){
            ui.ecapInput.hidden = false
            ui.resetCounters.hidden = false
			if (!["F280013x","F280015x"].includes(Common.getDeviceName()))
			{
				ui.useDMA.hidden = false
				ui.dmaSource.hidden = false
			}
        }
        //Signal Monitoring Unit
        if (["F28P65x"].includes(Common.getDeviceName())){
            ui.trip_selection_signalMunit.hidden = false
            ui.global_strobe_selection_signalMunit.hidden = false
            for (var rptrIndex in device_driverlib_peripheral.ECAP_MONITORING_UNIT)
            {
                var currentRPTR = device_driverlib_peripheral.ECAP_MONITORING_UNIT[rptrIndex].name
                let rptri = (currentRPTR).replace(/[^0-9]/g,'')
                ui["enable_monitorunit"+ rptri.toString()].hidden = false;
            }
        }

        //APWM options
        ui.apwmPolarity.hidden = true
        ui.apwmPeriod.hidden = true
        ui.apwmCompare.hidden = true
    }
    else if(inst.ecapMode == "APWM"){
        //CAPTURE options
        ui.eventPrescaler.hidden = true
        ui.eventOnePolarity.hidden = true
        ui.eventTwoPolarity.hidden = true
        ui.eventThreePolarity.hidden = true
        ui.eventFourPolarity.hidden = true
        ui.captureMode.hidden = true
        if (inst.useInterrupts){
            ui.interruptSourceCapture.hidden = true
            ui.interruptSourceAPWM.hidden = false
        }
        ui.eventStop.hidden = true
        ui.counterResetOnEvent.hidden = true
        ui.reArm.hidden = true
        if (["F28004x","F28002x","F28003x","F280013x","F280015x","F2838x","F28P65x", "F28P55x","F28P551x","F28E12x"].includes(Common.getDeviceName())){
            ui.ecapInput.hidden = true
            ui.resetCounters.hidden = true
			if (!["F280013x","F280015x"].includes(Common.getDeviceName()))
			{
				ui.useDMA.hidden = true
				ui.dmaSource.hidden = true
			}
        }

        //Signal Monitoring Unit
        if (["F28P65x"].includes(Common.getDeviceName())){
            ui.trip_selection_signalMunit.hidden = false
            ui.global_strobe_selection_signalMunit.hidden = false
            for (var rptrIndex in device_driverlib_peripheral.ECAP_MONITORING_UNIT)
            {
                var currentRPTR = device_driverlib_peripheral.ECAP_MONITORING_UNIT[rptrIndex].name
                let rptri = (currentRPTR).replace(/[^0-9]/g,'')

                ui["enable_monitorunit"+ rptri.toString()].hidden = true;            
                ui["monitorSelect_"+ rptri.toString()].hidden = true;
                ui["minValue_"+ rptri.toString()].hidden = true;
                ui["maxValue_"+ rptri.toString()].hidden = true;
                ui["enableSyncIn_"+ rptri.toString()].hidden = true;
                ui["forceload_"+ rptri.toString()].hidden = true;
                ui["loadmode_"+ rptri.toString()].hidden = true;
                ui["shadowMinValue_"+ rptri.toString()].hidden = true;
                ui["shadowMaxValue_"+ rptri.toString()].hidden = true;
                ui["enableDebug_"+ rptri.toString()].hidden = true;
            }
        }

        //APWM options
        ui.apwmPeriod.hidden = false
        ui.apwmPolarity.hidden = false
        ui.apwmCompare.hidden = false
    }
}

function onChangeUseInterrupts(inst, ui)
{
    if (inst.useInterrupts){
        ui.enableInterrupt.hidden = false
        ui.registerInterrupts.hidden = false
        if(inst.ecapMode == "CAPTURE"){
            ui.interruptSourceCapture.hidden = false
            ui.interruptSourceAPWM.hidden = true
        }
        else if(inst.ecapMode == "APWM"){
            ui.interruptSourceCapture.hidden = true
            ui.interruptSourceAPWM.hidden = false
        }
        
    }
    else{
        ui.enableInterrupt.hidden = true
        ui.registerInterrupts.hidden = true
        ui.interruptSourceCapture.hidden = true
        ui.interruptSourceAPWM.hidden = true
    }
}

function onChangeMonitorUnit(inst, ui)
{
    for (var rptrIndex in device_driverlib_peripheral.ECAP_MONITORING_UNIT)
    {
        var currentRPTR = device_driverlib_peripheral.ECAP_MONITORING_UNIT[rptrIndex].name
        let rptri = (currentRPTR).replace(/[^0-9]/g,'')
        if(inst["enable_monitorunit"+ rptri.toString()])
        {
            ui["monitorSelect_"+ rptri.toString()].hidden = false;
            ui["minValue_"+ rptri.toString()].hidden = false;
            ui["maxValue_"+ rptri.toString()].hidden = false;
            ui["enableSyncIn_"+ rptri.toString()].hidden = false;
            ui["enableDebug_"+ rptri.toString()].hidden = false;
        }
        else
        {
            ui["monitorSelect_"+ rptri.toString()].hidden = true;
            ui["minValue_"+ rptri.toString()].hidden = true;
            ui["maxValue_"+ rptri.toString()].hidden = true;
            ui["enableSyncIn_"+ rptri.toString()].hidden = true;
            ui["forceload_"+ rptri.toString()].hidden = true;
            ui["loadmode_"+ rptri.toString()].hidden = true;
            ui["shadowMinValue_"+ rptri.toString()].hidden = true;
            ui["shadowMaxValue_"+ rptri.toString()].hidden = true;
            ui["enableDebug_"+ rptri.toString()].hidden = true;

            // Reset values to their defaults

            inst["monitorSelect_"+ rptri.toString()] = device_driverlib_peripheral.ECAP_MonitoringTypeSelect[0].name;
            inst["minValue_"+ rptri.toString()] = 0;
            inst["maxValue_"+ rptri.toString()] = 0;
            inst["enableSyncIn_"+ rptri.toString()] = false;
            inst["forceload_"+ rptri.toString()] = false;
            inst["loadmode_"+ rptri.toString()] = "ECAP_ACTIVE_LOAD_SYNC_EVT";
            inst["shadowMinValue_"+ rptri.toString()] = 0;
            inst["shadowMaxValue_"+ rptri.toString()] = 0;
            inst["enableDebug_"+ rptri.toString()] = false;
        }
    }
}

function onChangeSyncIn(inst, ui)
{
    for (var rptrIndex in device_driverlib_peripheral.ECAP_MONITORING_UNIT)
    {
        var currentRPTR = device_driverlib_peripheral.ECAP_MONITORING_UNIT[rptrIndex].name
        let rptri = (currentRPTR).replace(/[^0-9]/g,'')
        if(inst["enableSyncIn_"+ rptri.toString()])
        {
            ui["forceload_"+ rptri.toString()].hidden = false;
            ui["loadmode_"+ rptri.toString()].hidden = false;
            ui["shadowMinValue_"+ rptri.toString()].hidden = false;
            ui["shadowMaxValue_"+ rptri.toString()].hidden = false;
        }
        else
        {
            ui["forceload_"+ rptri.toString()].hidden = true;
            ui["loadmode_"+ rptri.toString()].hidden = true;
            ui["shadowMinValue_"+ rptri.toString()].hidden = true;
            ui["shadowMaxValue_"+ rptri.toString()].hidden = true;

            // Reset values to their defaults

            inst["forceload_"+ rptri.toString()] = false;
            inst["loadmode_"+ rptri.toString()] = "ECAP_ACTIVE_LOAD_SYNC_EVT";
            inst["shadowMinValue_"+ rptri.toString()] = 0;
            inst["shadowMaxValue_"+ rptri.toString()] = 0;
        }
    }
}

var ECAP_INSTANCE = [
    { name: "ECAP1_BASE", displayName: "ECAP1"},
    { name: "ECAP2_BASE", displayName: "ECAP2"},
    { name: "ECAP3_BASE", displayName: "ECAP3"},
    { name: "ECAP4_BASE", displayName: "ECAP4"},
    { name: "ECAP5_BASE", displayName: "ECAP5"},
    { name: "ECAP6_BASE", displayName: "ECAP6"},
]

var numberOfECAPs = 6;

var ECAP_INSTANCES_WITH_HRCAP = [];

/* determine number of instances */
if (["F28004x","F2838x", "F28P65x"].includes(Common.getDeviceName()))
{
    ECAP_INSTANCE = [
        { name: "ECAP1_BASE", displayName: "ECAP1"},
        { name: "ECAP2_BASE", displayName: "ECAP2"},
        { name: "ECAP3_BASE", displayName: "ECAP3"},
        { name: "ECAP4_BASE", displayName: "ECAP4"},
        { name: "ECAP5_BASE", displayName: "ECAP5"},
        { name: "ECAP6_BASE", displayName: "ECAP6"},
        { name: "ECAP7_BASE", displayName: "ECAP7"},
    ];
    numberOfECAPs = 7;
    ECAP_INSTANCES_WITH_HRCAP = ["ECAP6_BASE","ECAP7_BASE"];
}
else if (["F28002x","F28003x"].includes(Common.getDeviceName()))
{
    ECAP_INSTANCE = [
        { name: "ECAP1_BASE", displayName: "ECAP1"},
        { name: "ECAP2_BASE", displayName: "ECAP2"},
        { name: "ECAP3_BASE", displayName: "ECAP3"},
    ]
    numberOfECAPs = 3;
    ECAP_INSTANCES_WITH_HRCAP = ["ECAP3_BASE"];
}
else if (["F280013x", "F28P55x","F28P551x"].includes(Common.getDeviceName()))
{
    ECAP_INSTANCE = [
        { name: "ECAP1_BASE", displayName: "ECAP1"},
        { name: "ECAP2_BASE", displayName: "ECAP2"},
    ]
    numberOfECAPs = 2;
    ECAP_INSTANCES_WITH_HRCAP = [];
}
else if (["F280015x"].includes(Common.getDeviceName()))
{
    ECAP_INSTANCE = [
        { name: "ECAP1_BASE", displayName: "ECAP1"},
        { name: "ECAP2_BASE", displayName: "ECAP2"},
        { name: "ECAP3_BASE", displayName: "ECAP3"},
    ]
    numberOfECAPs = 3;
    ECAP_INSTANCES_WITH_HRCAP = [];
}
else if (["F28E12x"].includes(Common.getDeviceName()))
{
    ECAP_INSTANCE = [
        { name: "ECAP1_BASE", displayName: "ECAP1"},
    ]
    numberOfECAPs = 1;
    ECAP_INSTANCES_WITH_HRCAP = [];
}
var globalConfig = [
    {
        name: "chosenSYSCLK",
        displayName: "SYSCLK [MHz] for Sample Window Calculation",
        description: "This is the SYSCLK value assumed for sample window calculation and block diagram generation",
        default: Common.SYSCLK_getMaxMHz(),
    }
]

let capIntSrc = []
let apwmIntSrc = []
for (let i of device_driverlib_peripheral.ECAP_ISR_SOURCE){
    if ((i.name).includes("PERIOD") || (i.name).includes("COMPARE")){
        apwmIntSrc.push(i)
    }else if ((i.name).includes("OVERFLOW")){
        apwmIntSrc.push(i)
        capIntSrc.push(i)
    }else{
        capIntSrc.push(i)
    }
} 

var ecapStatic = undefined;

/* determine static module dependency */
if (["F2838x","F28002x","F28003x","F280013x","F280015x", "F28P65x", "F28P55x","F28P551x","F28E12x"].includes(Common.getDeviceName()))
{
    if (ECAP_INSTANCES_WITH_HRCAP.length > 0){
        ecapStatic = {
            name: "ecapGlobal",
            displayName: "ECAP Global",
            config: globalConfig, // chosenSYSCLK needed for all devices with HRCAP
            modules: undefined // no sync modules needed for these 4 devices
        }
    }
    else {
        ecapStatic = undefined; // leave undefined if not an HRCAP-equipped device
    }
}
else{
    if (ECAP_INSTANCES_WITH_HRCAP.length > 0){
        ecapStatic = {
            name: "ecapGlobal",
            displayName: "ECAP Global",
            //config: [{name:"a", default:false}],
            config: globalConfig, // chosenSYSCLK needed for all devices
            modules: Common.autoForce("sync", "/driverlib/sync.js") // add the sync module for this device
        }
    }
    else {
        ecapStatic = {
            name: "ecapGlobal",
            displayName: "ECAP Global",
            //config: [{name:"a", default:false}], 
            // don't add a config for chosenSYSCLK if HRCAP is not available
            modules: Common.autoForce("sync", "/driverlib/sync.js") // add the sync module for this device
        }
    }
}

function onChangeHRCAPEnable(inst, ui)
{
    // checkbox checked
    if (inst.hrcapEnable == true){

        // unhide the calibration enable checkbox
        ui.hrcapCalibrationEnable.hidden = false

        // unhide the calibration PERIOD and INTERRUPTS here if calibration was enabled previously
        if (inst.hrcapCalibrationEnable == true){
            ui.hrcapCalibrationPeriod.hidden = false
            ui.enabledCalibrationInterrupts.hidden = false
        }
    }
    // checkbox unchecked
    else if (inst.hrcapEnable == false){

        // if hrcap gets disabled, turn off everything calibration related too
        ui.hrcapCalibrationEnable.hidden = true
        ui.hrcapCalibrationPeriod.hidden = true
        ui.enabledCalibrationInterrupts.hidden = true
    }
}

function onChangeHRCAPCalEnable(inst, ui)
{
    if (inst.hrcapCalibrationEnable == true){
        ui.hrcapCalibrationPeriod.hidden = false
        ui.enabledCalibrationInterrupts.hidden = false
    }
    else if (inst.hrcapCalibrationEnable == false){
        ui.hrcapCalibrationPeriod.hidden = true
        ui.enabledCalibrationInterrupts.hidden = true
    }
}

var calibrationPerLongDesc = `
This calibration period in milliseconds assumes a sysclk of ` + Common.SYSCLK_getMaxMHz() +` MHz. 
Please change the SYSCLK value in the "Global Parameters" tab above for the appropriate MHz value of your system.

Calibration period is recommended to be 1.6ms.

The calibration is stopped when HRSYSCLKCNT is equal to the value in this register.
Register value is (SYSCLK frequency * Calibration Period).
`
var calibrationEnableLongDesc = `
Calibration is only required to be enabled for time-converted measurements.
Calibration for relative-time measurements is not required.

All values captured by the HRCAP submodule are in number of HRCLK cycles.
The HRCLK speed varies widely with temperature and voltage, thus a scale factor is required to convert the capture value to the SYSCLK domain.
For the same reason, it is required to periodically recalculate the scale factor. 
The HRCAP submodule has a calibration block to reduce software overhead when calculating a scale factor between HRCLK and SYSCLK.
`

var hrcap_configs = [
    {
        name        : "hrcapEnable",
        displayName : "Enable HRCAP",
        description : 'Enable HRCAP functionality on supported ECAP Modules.',
        hidden      : false,
        default     : false,
        onChange    : onChangeHRCAPEnable
    },
    {
        name        : "hrcapCalibrationEnable",
        displayName : "Enable HRCAP Calibration",
        description : 'Enable calibration, for determining a ScaleFactor to be used to calibrate the HRCAP resultant data every Calibration Period (HRCALIBPERIOD) cycles.',
        longDescription: calibrationEnableLongDesc,
        hidden      : true,
        default     : true,
        onChange    : onChangeHRCAPCalEnable
    },
    {
        name        : "hrcapCalibrationPeriod",
        displayName : "Calibration Period (ms)",
        description : 'Calibration period in milliseconds.',
        longDescription: calibrationPerLongDesc,
        hidden      : true,
        default     : 1.6 // 4194303 from register reset value, chose recommended 1.6ms based on 100Mhz SYSCLK
    },
    {
        name        : "enabledCalibrationInterrupts",
        displayName : "Enable Calibration Interrupts",
        description : 'Select which Calibration Interrupts to enable.',
        hidden      : true,
        default     : ["HRCAP_CALIBRATION_DONE","HRCAP_CALIBRATION_PERIOD_OVERFLOW"],
        minSelections: 0,
        options     : [
            {name: "HRCAP_CALIBRATION_DONE", displayName: "Calibration done flag"},
            {name: "HRCAP_CALIBRATION_PERIOD_OVERFLOW", displayName: "Calibration period overflow flag"},
        ]
    }
]

/* Array of ECAP configurables that are common across device families */
let config = [
    {
        name        : "ecapBase",
        displayName : "eCAP Instance",
        onChange    : onChangeECAPInstance, 
        description : 'Instance of the ECAP used.',
        hidden      : false,
        default     : ECAP_INSTANCE[0].name,
        options     : ECAP_INSTANCE
    },
    {
        name        : "emulationMode",
        displayName : "Emulation Mode",
        description : 'Configures emulation mode.',
        hidden      : false,
        default     : device_driverlib_peripheral.ECAP_EmulationMode[0].name,
        options     : device_driverlib_peripheral.ECAP_EmulationMode
    },
    {
        name        : "ecapMode",
        displayName : "eCAP Mode",
        onChange    : onChangeECAPMode, 
        default     : "CAPTURE",
        options     : 
        [
            {name: "CAPTURE", displayName: "Capture"},
            {name: "APWM", displayName: "APWM"},
        ]
    },
    {
        name        : "captureMode",
        displayName : "Capture Mode",
        description : 'Sets the capture mode.',
        hidden      : false,
        default     : device_driverlib_peripheral.ECAP_CaptureMode[0].name,
        options     : device_driverlib_peripheral.ECAP_CaptureMode
    },
    {
        name        : "eventStop",
        displayName : "Capture Stops at Event",
        description : 'Select the event number at which the counter stops or wraps',
        hidden      : false,
        default     : device_driverlib_peripheral.ECAP_Events[0].name,
        options     : device_driverlib_peripheral.ECAP_Events
    },
    {
        name        : "eventPrescaler",
        displayName : "Event Prescaler",
        description : 'Sets the input prescaler.',
        hidden      : false,
        default     : 0
    },
    {
        name        : "eventOnePolarity",
        displayName : "Event 1 Polarity",
        description : 'Sets the Capture event polarity for Event 1.',
        hidden      : false,
        default     : device_driverlib_peripheral.ECAP_EventPolarity[0].name,
        options     : device_driverlib_peripheral.ECAP_EventPolarity
    },
    {
        name        : "eventTwoPolarity",
        displayName : "Event 2 Polarity",
        description : 'Sets the Capture event polarity for Event 2.',
        hidden      : false,
        default     : device_driverlib_peripheral.ECAP_EventPolarity[0].name,
        options     : device_driverlib_peripheral.ECAP_EventPolarity
    },
    {
        name        : "eventThreePolarity",
        displayName : "Event 3 Polarity",
        description : 'Sets the Capture event polarity for Event 3.',
        hidden      : false,
        default     : device_driverlib_peripheral.ECAP_EventPolarity[0].name,
        options     : device_driverlib_peripheral.ECAP_EventPolarity
    },
    {
        name        : "eventFourPolarity",
        displayName : "Event 4 Polarity",
        description : 'Sets the Capture event polarity for Event 4.',
        hidden      : false,
        default     : device_driverlib_peripheral.ECAP_EventPolarity[0].name,
        options     : device_driverlib_peripheral.ECAP_EventPolarity
    },
    {
        name        : "useInterrupts",
        displayName : "Use Interrupt",
        onChange    : onChangeUseInterrupts,
        description : 'Whether or not to use Interrupt mode.',
        hidden      : false,
        default     : true
    },
    {
        name        : "registerInterrupts",
        displayName : "Register Interrupt Handler",
        description : 'Whether or not to register interrupt handlers in the interrupt module.',
        hidden      : false,
        default     : false
    },
    {
        name        : "enableInterrupt",
        displayName : "Enable Interrupt",
        description : 'Enables interrupt source.',
        hidden      : false,
        default     : false
    },
    {
        name        : "interruptSourceCapture",
        displayName : "Interrupt Source",
        description : 'Select interrupt source.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : capIntSrc
    },
    {
        name        : "interruptSourceAPWM",
        displayName : "Interrupt Source",
        description : 'Select interrupt source.',
        hidden      : true,
        default     : [],
        minSelections: 0,
        options     : apwmIntSrc
    },
    {
        name        : "counterResetOnEvent",
        displayName : "Enable Counter Reset",
        description : 'Enables counter reset on an event.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : device_driverlib_peripheral.ECAP_Events
    },
    {
        name        : "phaseShiftCount",
        displayName : "Phase Shift Count",
        description : 'Sets a phase shift value count.',
        hidden      : false,
        default     : 0
    },
    {
        name        : "enableLoadCounter",
        displayName : "Enable Load Counter",
        description : 'Enable counter loading with phase shift value.',
        hidden      : false,
        default     : false
    },
    {
        name        : "loadCounter",
        displayName : "Load Counter",
        description : 'Load the time stamp counter with phase shift value.',
        hidden      : false,
        default     : false
    },
    {
        name        : "syncOutMode",
        displayName : "Sync Out Mode",
        description : 'Configures Sync out signal mode.',
        hidden      : false,
        default     : device_driverlib_peripheral.ECAP_SyncOutMode[0].name,
        options     : device_driverlib_peripheral.ECAP_SyncOutMode
    },
    {
        name        : "apwmPolarity",
        displayName : "APWM Polarity",
        description : 'Set eCAP APWM polarity.',
        hidden      : true,
        default     : device_driverlib_peripheral.ECAP_APWMPolarity[0].name,
        options     : device_driverlib_peripheral.ECAP_APWMPolarity
    },
    {
        name        : "apwmPeriod",
        displayName : "APWM Period",
        description : 'Set eCAP APWM period.',
        hidden      : true,
        default     : 0
    },
    {
        name        : "apwmCompare",
        displayName : "APWM Compare",
        description : 'Set eCAP APWM on or off time count.',
        hidden      : true,
        default     : 0
    },
];
if (["F2837xD","F2837xS","F2807x"].includes(Common.getDeviceName())){
    config.push(
        {
            name        : "ecapInputReadOnly",
            displayName : "eCAP Input",
            description : 'Select eCAP input.',
            hidden      : false,
            default     : "ECAP_INPUT_INPUTXBAR7",
            readOnly    : true,
            options     : 
            [
                { name: "ECAP_INPUT_INPUTXBAR7", displayName: "GPIO Input Crossbar output signal-7" },
                { name: "ECAP_INPUT_INPUTXBAR8", displayName: "GPIO Input Crossbar output signal-8" },
                { name: "ECAP_INPUT_INPUTXBAR9", displayName: "GPIO Input Crossbar output signal-9" },
                { name: "ECAP_INPUT_INPUTXBAR10", displayName: "GPIO Input Crossbar output signal-10" },
                { name: "ECAP_INPUT_INPUTXBAR11", displayName: "GPIO Input Crossbar output signal-11" },
                { name: "ECAP_INPUT_INPUTXBAR12", displayName: "GPIO Input Crossbar output signal-12" },
            ]
        },
    )
}
//TODO: only for F28004x, default value (this will throw WARNING) temp solotion. 
// TODO: followup, remove this once the new option is added on driverlib!! already in development. 
if (["F28004x"].includes(Common.getDeviceName())){
    device_driverlib_peripheral.ECAP_InputCaptureSignals.push(
        {name:"127",displayName:"RESERVED"}
    )
}
var defaultInput = ""
if (["F28002x","F28003x","F280013x","F280015x","F2838x","F28P65x", "F28P55x","F28P551x"].includes(Common.getDeviceName())){
    defaultInput = "ECAP_INPUT_ECAP1_GPTRIP7"
}
else if (["F28004x"].includes(Common.getDeviceName())){
    defaultInput = "127"
}
if (["F28004x","F28002x","F28003x","F280013x","F280015x","F2838x","F28P65x", "F28P55x","F28P551x"].includes(Common.getDeviceName())){
    config.push(
        {
            name        : "ecapInput",
            displayName : "eCAP Input",
            description : 'Select eCAP input.',
            hidden      : false,
            default     : defaultInput,
            options     : device_driverlib_peripheral.ECAP_InputCaptureSignals
        },
        {
            name        : "resetCounters",
            displayName : "Reset Counters",
            description : 'Resets eCAP counters and flags.',
            hidden      : false,
            default     : false
        },
    )
}
if (["F28E12x"].includes(Common.getDeviceName())){
    defaultInput = "ECAP_INPUT_INPUTXBAR1"
    config.push(
        {
            name        : "ecapInput",
            displayName : "eCAP Input",
            description : 'Select eCAP input.',
            hidden      : false,
            default     : defaultInput,
            options     : device_driverlib_peripheral.ECAP_InputCaptureSignals
        },
        {
            name        : "resetCounters",
            displayName : "Reset Counters",
            description : 'Resets eCAP counters and flags.',
            hidden      : false,
            default     : false
        },
    )
}
if (["F28004x","F28002x","F28003x","F2838x","F28P65x", "F28P55x","F28P551x","F28E12x"].includes(Common.getDeviceName())){
    config.push(
        {
            name        : "useDMA",
            displayName : "Use DMA Source",
            description : 'Enables use of DMA Source.',
            hidden      : false,
            default     : false
        },
        {
            name        : "dmaSource",
            displayName : "DMA Source",
            description : 'Sets the eCAP DMA source.',
            hidden      : false,
            default     : device_driverlib_peripheral.ECAP_Events[0].name,
            options     : device_driverlib_peripheral.ECAP_Events
        },
    )
}
if (["F28002x","F28003x","F280013x","F280015x","F2838x","F28P65x", "F28P55x","F28P551x","F28E12x"].includes(Common.getDeviceName())){
    config.push(
        {
            name        : "syncInPulseSource",
            displayName : "Sync-In Pulse Source",
            description : 'Set up the source for sync-in pulse.',
            hidden      : false,
            default     : device_driverlib_peripheral.ECAP_SyncInPulseSource[0].name,
            options     : device_driverlib_peripheral.ECAP_SyncInPulseSource
        },
    )
}

config.push(
    {
        name        : "reArm",
        displayName : "Re-arm eCAP",
        description : 'Re-arms the eCAP module for myECAP0.',
        hidden      : false,
        default     : true
    },
)

let signal_monitoring_unit_config = [];

if (["F28P65x"].includes(Common.getDeviceName()))
{
    let signal_monitoring_common_config =
    [
        {
            name: "trip_selection_signalMunit",
            displayName: "Trip Selection",
            description : 'Select trip source signal to enable/ disable/ no effect signal monitoring unit',
            default: 0,
            default: device_driverlib_peripheral.ECAP_MunitTripInputSelect[0].name,
            options: device_driverlib_peripheral.ECAP_MunitTripInputSelect
        },
        {
            name: "global_strobe_selection_signalMunit",
            displayName: "Global Load Strobe",
            description : 'Select global load strobe to enable shadow to active loading',
            default: device_driverlib_peripheral.ECAP_MunitTripInputSelect[0].name,
            options: device_driverlib_peripheral.ECAP_MunitTripInputSelect
        }
    ]

    for (var rptrIndex in device_driverlib_peripheral.ECAP_MONITORING_UNIT)
    {
        var currentRPTR = device_driverlib_peripheral.ECAP_MONITORING_UNIT[rptrIndex].name
        let rptri = (currentRPTR).replace(/[^0-9]/g,'')
        signal_monitoring_unit_config =  signal_monitoring_unit_config.concat ([
            {
                name:"signalMonitoringUnit"+ rptri.toString(), 
                displayName: "Signal Monitoring Unit"+ rptri.toString(),
                config:
            [
                {
                    name: "enable_monitorunit"+ rptri.toString(),
                    displayName: "Enable Monitor Unit",
                    description : 'Enable signal monitoring unit ' + rptri.toString(),
                    default: false,
                    onChange: onChangeMonitorUnit
                },
                {
                    name: "monitorSelect_"+ rptri.toString(),
                    displayName: "Select Monitoring Type Of MUNIT",
                    description : 'Select Monitoring Type of MUNIT ' + rptri.toString(),
                    hidden:  true,
                    default: device_driverlib_peripheral.ECAP_MonitoringTypeSelect[0].name,
                    options: device_driverlib_peripheral.ECAP_MonitoringTypeSelect
                },
                {
                    name: "minValue_"+ rptri.toString(),
                    displayName: "Minimum Value For Monitoring",
                    description : 'Minimum Value For Monitoring of ' + rptri.toString(),
                    hidden:  true,
                    default: 0,
                },
                {
                    name: "maxValue_"+ rptri.toString(),
                    displayName: "Maximum Value For Monitoring",
                    description : 'Maximum Value For Monitoring of ' + rptri.toString(),
                    hidden:  true,
                    default: 0,
                },
                {
                    name: "enableSyncIn_"+ rptri.toString(),
                    displayName: "Enable SyncIn",
                    description : 'Enable SyncIn for ' + rptri.toString(),
                    hidden:  true,
                    default: false,
                    onChange: onChangeSyncIn
                },
                {
                    name: "forceload_"+ rptri.toString(),
                    displayName: "Force Copy From Shadow",
                    description : 'Force Copy from Shadow ' + rptri.toString(),
                    hidden:  true,
                    default: false,
                },
                {
                    name: "loadmode_"+ rptri.toString(),
                    displayName: "Select Shadow Load Mode",
                    description : 'Select Shadow Load Mode for ' + rptri.toString(),
                    hidden:  true,
                    default: "ECAP_ACTIVE_LOAD_SYNC_EVT",
                    options     :
                    [
                        {name: "ECAP_ACTIVE_LOAD_SYNC_EVT",         displayName: "Load on next sync event"},
                        {name: "ECAP_ACTIVE_LOAD_GLDLCSTRB_EVT",    displayName: "Load on EPWM GLDLCSTRB event"},
                    ]
                },
                {
                    name: "shadowMinValue_"+ rptri.toString(),
                    displayName: "Shadow Minimum Value For Monitoring",
                    description : 'Shadow Minimum Value For Monitoring of ' + rptri.toString(),
                    hidden:  true,
                    default: 0,
                },
                {
                    name: "shadowMaxValue_"+ rptri.toString(),
                    displayName: "Shadow Maximum Value For Monitoring",
                    description : 'Shadow Maximum Value For Monitoring of ' + rptri.toString(),
                    hidden:  true,
                    default: 0,
                },
                {
                    name: "enableDebug_"+ rptri.toString(),
                    displayName: "Enable Debug Mode",
                    description : 'Enable Debug Mode  for ' + rptri.toString(),
                    hidden:  true,
                    default: false,
                },
        ]}
        ])
    }

    let signal_monitoring_total = signal_monitoring_common_config;
    signal_monitoring_total = signal_monitoring_total.concat(signal_monitoring_unit_config);

    config = config.concat([
        {
            name: "GROUP_SIGNAL_MONITORING_UNIT",
            displayName: "Signal Monitoring Unit",
            description: "",
            config : signal_monitoring_total
        }
    ])
}

// only add HRCAP section for devices that have HRCAP available
if (ECAP_INSTANCES_WITH_HRCAP.length > 0){
    config.push(
        {
            name        : "GROUP_HRCAP",
            displayName : "HRCAP Configurations",
            description : "High Resolution Capture Configurations",
            longDescription: "",
            config      : hrcap_configs
        },
    )
}

function onValidate(inst, validation) {

    var usedECAPInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedECAPInsts.push(instance_obj.ecapBase);
    }

    var otherContexts = Common.getOtherContextNames()
    for (var cntx of otherContexts)
    {
        var onOtherCntx = Common.getModuleForCore(inst.$module.$name, cntx);
        if (onOtherCntx)
        {
            for (var instance_index in onOtherCntx.$instances)
            {
                var instance_obj = onOtherCntx.$instances[instance_index];
                usedECAPInsts.push(instance_obj.ecapBase);
            }
        }
    }

    var duplicatesResult = Common.findDuplicates(usedECAPInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The ECAP Instance used. Duplicates: " + allDuplicates, 
            inst, "ecapBase");
    }

    /* Validate Event Prescaler up to 16 bit unsigned int */
    if (inst.eventPrescaler < 0 || inst.eventPrescaler > 65535)
    {
        validation.logError(
            "Enter an integer for Event Prescaler between 0 and 65,535!", 
            inst, "eventPrescaler");
    }
    if (!Number.isInteger(inst.eventPrescaler))
    {
        validation.logError(
            "Event Prescaler must be an integer", 
            inst, "eventPrescaler");
    }

    /* Validate Phase Shift Count up to 32 bit unsigned int */
    if (inst.phaseShiftCount < 0 || inst.phaseShiftCount > 4294967295)
    {
        validation.logError(
            "Enter an integer for Phase Shift Count between 0 and 4,294,967,295!", 
            inst, "phaseShiftCount");
    }
    if (!Number.isInteger(inst.phaseShiftCount))
    {
        validation.logError(
            "Phase Shift Count must be an integer", 
            inst, "phaseShiftCount");
    }

    /* Validate APWM Period up to 32 bit unsigned int */
    if (inst.apwmPeriod < 0 || inst.apwmPeriod > 4294967295)
    {
        validation.logError(
            "Enter an integer for APWM Period between 0 and 4,294,967,295!", 
            inst, "apwmPeriod");
    }
    if (!Number.isInteger(inst.apwmPeriod))
    {
        validation.logError(
            "APWM Period must be an integer", 
            inst, "apwmPeriod");
    }

    /* Validate APWM Compare up to 32 bit unsigned int */
    if (inst.apwmCompare < 0 || inst.apwmCompare > 4294967295)
    {
        validation.logError(
            "Enter an integer for APWM Compare between 0 and 4,294,967,295!", 
            inst, "apwmCompare");
    }
    if (!Number.isInteger(inst.apwmCompare))
    {
        validation.logError(
            "APWM Compare must be an integer", 
            inst, "apwmCompare");
    }

    /* Warn user if attempting to Load Counter without Enabling Load Counter */
    if ((inst.enableLoadCounter == false) && (inst.loadCounter == true)){
        validation.logWarning(
            "Enable Load Counter option is not set, code won't be generated for Load Counter.",
            inst, "loadCounter")
    }

    //Signal Monitoring Unit Validation
    for (var rptrIndex in device_driverlib_peripheral.ECAP_MONITORING_UNIT)
    {
        var currentRPTR = device_driverlib_peripheral.ECAP_MONITORING_UNIT[rptrIndex].name
        let rptri = (currentRPTR).replace(/[^0-9]/g,'')
        /* Validate APWM Compare up to 32 bit unsigned int */
        if (inst["minValue_"+rptri.toString()]< 0 || inst["minValue_"+rptri.toString()] > 4294967295)
        {
            validation.logError(
                "Enter an integer for Minimum Value For Monitoring between 0 and 4,294,967,295!",
                inst, "minValue_"+rptri.toString());
        }
        if (inst["maxValue_"+rptri.toString()]< 0 || inst["maxValue_"+rptri.toString()] > 4294967295)
        {
            validation.logError(
                "Enter an integer for Maximum Value For Monitoring between 0 and 4,294,967,295!",
                inst, "maxValue_"+rptri.toString());
        }
        if (inst["shadowMinValue_"+rptri.toString()]< 0 || inst["shadowMinValue_"+rptri.toString()] > 4294967295)
        {
            validation.logError(
                "Enter an integer for Shadow Minimum Value For Monitoring between 0 and 4,294,967,295!",
                inst, "shadowMinValue_"+rptri.toString());
        }
        if (inst["shadowMaxValue_"+rptri.toString()]< 0 || inst["shadowMaxValue_"+rptri.toString()] > 4294967295)
        {
            validation.logError(
                "Enter an integer for Shadow Maximum Value For Monitoring between 0 and 4,294,967,295!",
                inst, "shadowMaxValue_"+rptri.toString());
        }
    }

    // HRCAP calibration validation
    if (inst.hrcapCalibrationEnable==true && inst.hrcapEnable==true)
    {
        // Warn the user if the calibration period is out of bounds (32 bit
        // unsigned int counter)
        var calculatedHrcapCalibrationValue = inst.$module.$static["chosenSYSCLK"] * (inst.hrcapCalibrationPeriod/1000);
        if ((calculatedHrcapCalibrationValue < 0) || (calculatedHrcapCalibrationValue > 4294967295))
        {
            
            var minHrcapCalibrationValue = (0/inst.$module.$static["chosenSYSCLK"])*1000;
            var maxHrcapCalibrationValue = (4294967295/inst.$module.$static["chosenSYSCLK"])*1000 - 1;

            validation.logError(
                "Enter an integer for Calibration Period between "+minHrcapCalibrationValue+" and "+maxHrcapCalibrationValue+"!",
                inst, "hrcapCalibrationPeriod"
            );
        }
    }

    // if the user enabled HRCAP and the current ECAP instance is NOT capable of HRCAP, flag an error on the ECAP instance
    if ((inst.hrcapEnable == true) && !(ECAP_INSTANCES_WITH_HRCAP.includes(inst.ecapBase)))
    {
        validation.logError(
            "HRCAP is enabled, but is not available on this ECAP. Please choose one of the following ECAP instances: " + ECAP_INSTANCES_WITH_HRCAP.join(", ").replaceAll("_BASE",""),
            inst, "ecapBase"
        );
    }

}

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
    return (Common.typeMatches(component.type, ["ECAP"]));
}
let longDescription = `The Enhanced Capture (eCAP) module is essential in systems where accurate timing of external events is
important. Uses for eCAP include:
*   Speed measurements of rotating machinery (for example, toothed sprockets sensed via Hall sensors)
*   Elapsed time measurements between position sensor triggers
*   Period and duty cycle measurements of pulse train signals
*   Decoding current or voltage amplitude derived from duty cycle encoded current/voltage sensors
`
//module static on a variable, null if not needed, otherwise the object we have now. 
var ecapModule = {
    peripheralName: "ECAP",
    displayName: "ECAP",
    maxInstances: numberOfECAPs,
    defaultInstanceName: "myECAP",
    description: "Enhanced Capture",
    longDescription: longDescription + "\n" + (Common.getCollateralFindabilityList("ECAP")),
    filterHardware : filterHardware,
    config: config,
    moduleInstances: (inst) => {
        var intReturn = [];
        if (inst.useInterrupts && inst.registerInterrupts)
        {
            intReturn.push({
                name: "ecapInt",      
                displayName: "eCAP Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
            		$name : inst.$name + "_INT",
                    int : "INT_" + inst.$name,
                    pinmuxPeripheralModule :"",
                    driverlibInt: "INT_" + inst.ecapBase.replace("_BASE", "")
                }
            });
        }
        // add in the calibration interrupts if at least one is enabled, and registerInterrupts is checked
        if (inst.registerInterrupts && inst.hrcapEnable && inst.hrcapCalibrationEnable && inst.enabledCalibrationInterrupts.length > 0)
        {
            intReturn.push({
                name: "hrcapCalibrationInt",      
                displayName: "HRCAP Calibration Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
            		$name : inst.$name + "_INT_HR",
                    int : "INT_" + inst.$name + "_HR",
                    pinmuxPeripheralModule :"",
                    // HRCAP interrupt is called "INT_ECAP#_2" in f2838x_interrupt.js file (and other device files)
                    driverlibInt: "INT_" + inst.ecapBase.replace("_BASE", "") + "_2"
                }
            });
        }
        
        return intReturn;
    },
    templates: {
        boardc : "/driverlib/ecap/ecap.board.c.xdt",
        boardh : "/driverlib/ecap/ecap.board.h.xdt"
    },
    moduleStatic: ecapStatic,
    validate    : onValidate,
};



exports = ecapModule;