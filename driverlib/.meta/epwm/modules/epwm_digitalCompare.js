let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_epwm.js");
var DCCompareTypeConfigNames_CombinationNames = []
var DCAConfigs = [];
var DCBConfigs = [];

function onChangeEventDetection(inst, ui)
{
    if(inst.epwmDigitalCompare_enableEventDetection)
    {
        ui.epwmDigitalCompare_CAPGATETripInput.hidden = false;
        ui.epwmDigitalCompare_CAPGATE_combinationInputConfig.hidden = false;
        ui.epwmDigitalCompare_configCAPGATE.hidden = false;
        ui.epwmDigitalCompare_CAPINTripInput.hidden = false;
        ui.epwmDigitalCompare_CAPIN_combinationInputConfig.hidden = false;
        ui.epwmDigitalCompare_invertCAPIN.hidden = false;
        ui.epwmXCMP_setRegisters_XMIN_read.hidden = false;
        ui.epwmXCMP_setShadowRegisters1_XMIN_read.hidden = false;
        ui.epwmXCMP_setShadowRegisters2_XMIN_read.hidden = false;
        ui.epwmXCMP_setShadowRegisters3_XMIN_read.hidden = false;
        ui.epwmXCMP_setRegisters_XMAX_read.hidden = false;
        ui.epwmXCMP_setShadowRegisters1_XMAX_read.hidden = false;
        ui.epwmXCMP_setShadowRegisters2_XMAX_read.hidden = false;
        ui.epwmXCMP_setShadowRegisters3_XMAX_read.hidden = false;


    }else
    {
        ui.epwmDigitalCompare_CAPGATETripInput.hidden = true;
        ui.epwmDigitalCompare_CAPGATE_combinationInputConfig.hidden = true;
        ui.epwmDigitalCompare_configCAPGATE.hidden = true;
        ui.epwmDigitalCompare_CAPINTripInput.hidden = true;
        ui.epwmDigitalCompare_CAPIN_combinationInputConfig.hidden = true;
        ui.epwmDigitalCompare_invertCAPIN.hidden = true;
        ui.epwmXCMP_setRegisters_XMIN_read.hidden = true;
        ui.epwmXCMP_setRegisters_XMIN_read.hidden = true;
        ui.epwmXCMP_setShadowRegisters1_XMIN_read.hidden = true;
        ui.epwmXCMP_setShadowRegisters2_XMIN_read.hidden = true;
        ui.epwmXCMP_setShadowRegisters3_XMIN_read.hidden = true;
        ui.epwmXCMP_setRegisters_XMAX_read.hidden = true;
        ui.epwmXCMP_setShadowRegisters1_XMAX_read.hidden = true;
        ui.epwmXCMP_setShadowRegisters2_XMAX_read.hidden = true;
        ui.epwmXCMP_setShadowRegisters3_XMAX_read.hidden = true;

        inst.epwmDigitalCompare_CAPGATETripInput = device_driverlib_peripheral.EPWM_DigitalCompareTripInput[0].name;
        inst.epwmDigitalCompare_CAPGATE_combinationInputConfig = [];
        inst.epwmDigitalCompare_configCAPGATE = device_driverlib_peripheral.EPWM_selectCaptureGateInputPolarity[0].name;
        inst.epwmDigitalCompare_CAPINTripInput = device_driverlib_peripheral.EPWM_DigitalCompareTripInput[0].name;
        inst.epwmDigitalCompare_CAPIN_combinationInputConfig = [];
        inst.epwmDigitalCompare_invertCAPIN = "EPWM_CAPTURE_INPUT_CAPIN_SYNC";
        
    }
}

function pulseSelChanged(inst, ui)
{
    inst.epwmDigitalCompare_dCCounterCapturePulse = inst.epwmDigitalCompare_blankingWindowEvent;
}

function onChangeDCCounterCapture(inst, ui)
{
    if (inst.epwmDigitalCompare_useDCCounterCapture == true)
    {
        ui.epwmDigitalCompare_dCCounterCaptureShadow.hidden = false;
        ui.epwmDigitalCompare_dCCounterCapturePulse.hidden = false;
        if(["F28P65x"].includes(Common.getDeviceName())){
            ui.epwmDigitalCompare_dCCounterCapturePulseLogic.hidden = false;
        }
    }
    else if (inst.epwmDigitalCompare_useDCCounterCapture == false)
    {
        ui.epwmDigitalCompare_dCCounterCaptureShadow.hidden = true;
        ui.epwmDigitalCompare_dCCounterCapturePulse.hidden = true;
        ui.epwmDigitalCompare_dCCounterCapturePulseLogic.hidden = true;
        // Set to defaults
        inst.epwmDigitalCompare_dCCounterCaptureShadow = false;
        inst.epwmDigitalCompare_dCCounterCapturePulseLogic = false;
        inst.epwmDigitalCompare_dCCounterCapturePulse = device_driverlib_peripheral.EPWM_DigitalCompareBlankingPulse[0].name;

    }
}

function onChangeBlankingWindow(inst, ui)
{
    if (inst.epwmDigitalCompare_useBlankingWindow == true)
    {
        ui.epwmDigitalCompare_blankingWindowEvent.hidden = false;
        ui.epwmDigitalCompare_blankingWindowOffset.hidden = false;
        ui.epwmDigitalCompare_blankingWindowLength.hidden = false;
        ui.epwmDigitalCompare_invertBlankingWindow.hidden = false;
    }
    else if (inst.epwmDigitalCompare_useBlankingWindow == false)
    {
       ui.epwmDigitalCompare_blankingWindowEvent.hidden = true;
       ui.epwmDigitalCompare_blankingWindowOffset.hidden = true;
       ui.epwmDigitalCompare_blankingWindowLength.hidden = true;
       ui.epwmDigitalCompare_invertBlankingWindow.hidden = true; 
       // Set everything to its default state
       inst.epwmDigitalCompare_blankingWindowEvent = device_driverlib_peripheral.EPWM_DigitalCompareBlankingPulse[0].name;
       inst.epwmDigitalCompare_blankingWindowOffset = 0;
       inst.epwmDigitalCompare_blankingWindowLength= 0;
       inst.epwmDigitalCompare_invertBlankingWindow = false; 

    }
}

function onChangeEdgeFilter(inst, ui)
{
    if (inst.epwmDigitalCompare_useEdgeFilter == true)
    {
        ui.epwmDigitalCompare_edgeFilterMode.hidden = false;
        ui.epwmDigitalCompare_valleyCaptureSource.hidden = false;
        ui.epwmDigitalCompare_edgeFilterEdgeCount.hidden = false;
        ui.epwmDigitalCompare_enableValleyCapture.hidden = false;
        ui.epwmDigitalCompare_startValleyCapture.hidden = false;
        ui.epwmDigitalCompare_startValleyCaptureTriggerCount.hidden = false;
        ui.epwmDigitalCompare_stopValleyCaptureTriggerCount.hidden = false;
        ui.epwmDigitalCompare_enableEdgeFilterDelay.hidden = false;
        ui.epwmDigitalCompare_SWVDELVAL.hidden = false;
        ui.epwmDigitalCompare_valleyDelayDivider.hidden = false;

        if (inst.epwmDigitalCompare_enableValleyCapture == true){
            ui.epwmDigitalCompare_valleyCaptureSource.hidden = false;
            if (inst.epwmDigitalCompare_valleyCaptureSource == device_driverlib_peripheral.EPWM_ValleyTriggerSource[0].name)
            {
                ui.epwmDigitalCompare_startValleyCapture.hidden = false;
            }
            else
            {
                ui.epwmDigitalCompare_startValleyCapture.hidden = true;
            }
            ui.epwmDigitalCompare_startValleyCaptureTriggerCount.hidden = false;
            ui.epwmDigitalCompare_stopValleyCaptureTriggerCount.hidden = false;
        }
        else if (inst.epwmDigitalCompare_enableValleyCapture == false)
        {
            ui.epwmDigitalCompare_valleyCaptureSource.hidden = true;
            ui.epwmDigitalCompare_startValleyCapture.hidden = true;
            ui.epwmDigitalCompare_startValleyCaptureTriggerCount.hidden = true;
            ui.epwmDigitalCompare_stopValleyCaptureTriggerCount.hidden = true;
            // Set everything to its defaults
            inst.epwmDigitalCompare_valleyCaptureSource = device_driverlib_peripheral.EPWM_ValleyTriggerSource[0].name;
            inst.epwmDigitalCompare_startValleyCapture = false;
            inst.epwmDigitalCompare_startValleyCaptureTriggerCount = "0";
            inst.epwmDigitalCompare_stopValleyCaptureTriggerCount = "0";
        }

        if (inst.epwmDigitalCompare_enableEdgeFilterDelay == true)
        {
            ui.epwmDigitalCompare_SWVDELVAL.hidden = false;
            ui.epwmDigitalCompare_valleyDelayDivider.hidden = false;
        } 
        else if (inst.epwmDigitalCompare_enableEdgeFilterDelay == false)
        {
            ui.epwmDigitalCompare_SWVDELVAL.hidden = true;
            ui.epwmDigitalCompare_valleyDelayDivider.hidden = true;
            // Set to defaults
            inst.epwmDigitalCompare_SWVDELVAL= 0;
            inst.epwmDigitalCompare_valleyDelayDivider = device_driverlib_peripheral.EPWM_ValleyDelayMode[0].name;
        } 
    }
    else if (inst.epwmDigitalCompare_useEdgeFilter == false)
    {
        ui.epwmDigitalCompare_edgeFilterMode.hidden = true;
        ui.epwmDigitalCompare_valleyCaptureSource.hidden = true;
        ui.epwmDigitalCompare_edgeFilterEdgeCount.hidden = true;
        ui.epwmDigitalCompare_enableValleyCapture.hidden = true;
        ui.epwmDigitalCompare_startValleyCapture.hidden = true;
        ui.epwmDigitalCompare_startValleyCaptureTriggerCount.hidden = true;
        ui.epwmDigitalCompare_stopValleyCaptureTriggerCount.hidden = true;
        ui.epwmDigitalCompare_enableEdgeFilterDelay.hidden = true;
        ui.epwmDigitalCompare_SWVDELVAL.hidden = true;
        ui.epwmDigitalCompare_valleyDelayDivider.hidden = true;

        // Set everything to its default state
        inst.epwmDigitalCompare_edgeFilterMode = device_driverlib_peripheral.EPWM_DigitalCompareEdgeFilterMode[0].name;
        inst.epwmDigitalCompare_valleyCaptureSource = device_driverlib_peripheral.EPWM_ValleyTriggerSource[0].name;
        inst.epwmDigitalCompare_edgeFilterEdgeCount = "EPWM_DC_EDGEFILT_EDGECNT_0";
        inst.epwmDigitalCompare_enableValleyCapture = false;
        inst.epwmDigitalCompare_startValleyCapture = false;
        inst.epwmDigitalCompare_startValleyCaptureTriggerCount = "0";
        inst.epwmDigitalCompare_stopValleyCaptureTriggerCount = "0";
        inst.epwmDigitalCompare_enableEdgeFilterDelay = false;
        inst.epwmDigitalCompare_SWVDELVAL = 0;
        inst.epwmDigitalCompare_valleyDelayDivider = device_driverlib_peripheral.EPWM_ValleyDelayMode[0].name;

    }
}

function onChangeComboInputs (inst, ui)
{
    for (var dcCompareTypeIndex in device_driverlib_peripheral.EPWM_DigitalCompareType)
    {
        var dcCompareType = device_driverlib_peripheral.EPWM_DigitalCompareType[dcCompareTypeIndex];
        if (inst["epwmDigitalCompare_" + dcCompareType.name] == "EPWM_DC_TRIP_COMBINATION")
        {
            ui["epwmDigitalCompare_" + dcCompareType.name + "_combinationInputConfig"].hidden = false;
        }
        else
        {
            ui["epwmDigitalCompare_" + dcCompareType.name + "_combinationInputConfig"].hidden = true;
        }
    }
}

for (var dcCompareTypeIndex in device_driverlib_peripheral.EPWM_DigitalCompareType)
{
    var dcCompareType = device_driverlib_peripheral.EPWM_DigitalCompareType[dcCompareTypeIndex];

    var dcCompareTypeConfig = {
        name: "epwmDigitalCompare_" + dcCompareType.name,
        displayName : dcCompareType.displayName,
        description : "Trip input to the " +  dcCompareType.displayName,
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_DigitalCompareTripInput[0].name,
        options     : device_driverlib_peripheral.EPWM_DigitalCompareTripInput,
        //onChange    : onChangeComboInputs,
    };


    var dcCombinationConfig = {
        name: "epwmDigitalCompare_" + dcCompareType.name + "_combinationInputConfig",
        displayName : "Combination Input Sources (" + dcCompareType.displayName + ")",
        description : "Select the sources to include in the Combination input sources",
        hidden      : false,
        minSelections: 0,
        default     : [],
        options     : device_driverlib_peripheral.EPWM_DC_COMBINATIONAL
    };

    DCCompareTypeConfigNames_CombinationNames.push(
        {
            CompareTypeName : dcCompareTypeConfig.name,
            CombinationName : dcCombinationConfig.name
        }
    );

    if (dcCompareType.name.indexOf("DCA") != -1)
    {
        DCAConfigs.push(dcCompareTypeConfig);
        DCAConfigs.push(dcCombinationConfig);
    }
    else
    {
        DCBConfigs.push(dcCompareTypeConfig);
        DCBConfigs.push(dcCombinationConfig);
    }
}

for (var dcCompareOutputIndex in device_driverlib_peripheral.EPWM_TripZoneDigitalCompareOutput)
{
    var dcCompareOutput = device_driverlib_peripheral.EPWM_TripZoneDigitalCompareOutput[dcCompareOutputIndex];

    var dcCompareOutputConfig = {
        name: "epwmDigitalCompare_" + dcCompareOutput.name,
        displayName : "Condition For " + dcCompareOutput.displayName,
        description : "Select the Condition for " +  dcCompareOutput.displayName + " for which the EVENT is generated.",
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_TripZoneDigitalCompareOutputEvent[0].name,
        options     : device_driverlib_peripheral.EPWM_TripZoneDigitalCompareOutputEvent,
    }

    if (dcCompareOutput.name.indexOf("OUTPUT_A") != -1)
    {
        DCAConfigs.push(dcCompareOutputConfig);
    }
    else
    {
        DCBConfigs.push(dcCompareOutputConfig);
    }
}

for (var dcCompareModuleIndex in device_driverlib_peripheral.EPWM_DigitalCompareModule)
{
    for (var dcCompareEventIndex in device_driverlib_peripheral.EPWM_DigitalCompareEvent)
    {
        var dcCompareModule = device_driverlib_peripheral.EPWM_DigitalCompareModule[dcCompareModuleIndex];
        var dcCompareEvent = device_driverlib_peripheral.EPWM_DigitalCompareEvent[dcCompareEventIndex];

        var dcxevty = "DC" + dcCompareModule.name.replace("EPWM_DC_MODULE_","") + "EVT" + dcCompareEvent.name.replace("EPWM_DC_EVENT_","")

        var dcCompareEventSyncConfig = {
            name: "epwmDigitalCompare_" + dcCompareModule.name + "_" + dcCompareEvent.name + "_eventSync",
            displayName : "Synch Mode (" + dcxevty + ")",
            description : "Select the Sync Mode for " +  dcCompareModule.displayName + " " + dcCompareEvent.displayName,
            hidden      : false,
            default     : device_driverlib_peripheral.EPWM_DigitalCompareSyncMode[0].name,
            options     : device_driverlib_peripheral.EPWM_DigitalCompareSyncMode,
        }

        var dcCompareEventSourceConfig = {
            name: "epwmDigitalCompare_" + dcCompareModule.name + "_" + dcCompareEvent.name + "_eventSource",
            displayName : "Signal Source (" + dcxevty + ")",
            description : "Select the Signal Source for " +  dcCompareModule.displayName + " " + dcCompareEvent.displayName,
            hidden      : false,
            default     : device_driverlib_peripheral.EPWM_DigitalCompareEventSource[0].name,
            options     : device_driverlib_peripheral.EPWM_DigitalCompareEventSource,
        }

        var dcCompareEventCBCLatchModeConfig = null;
        var dcCompareEventCBCLatchClearEventConfig = null;

        if (!["F2807x", "F2837xD", "F2837xS", "F28004x"].includes(Common.getDeviceName()))
        {
            dcCompareEventCBCLatchModeConfig = {
                name: "epwmDigitalCompare_" + dcCompareModule.name + "_" + dcCompareEvent.name + "_latchMode",
                displayName : "CBC Latch Mode (" + dcxevty + ")",
                description : "Select the CBC latch mode for " +  dcCompareModule.displayName + " " + dcCompareEvent.displayName,
                hidden      : false,
                default     : device_driverlib_peripheral.EPWM_DigitalCompareCBCLatchMode[0].name,
                options     : device_driverlib_peripheral.EPWM_DigitalCompareCBCLatchMode,
            }

            dcCompareEventCBCLatchClearEventConfig = {
                name: "epwmDigitalCompare_" + dcCompareModule.name + "_" + dcCompareEvent.name + "_latchClearEvent",
                displayName : "CBC Latch Clear Event (" + dcxevty + ")",
                description : "Select the CBC latch clear event for " +  dcCompareModule.displayName + " " + dcCompareEvent.displayName,
                hidden      : false,
                default     : device_driverlib_peripheral.EPWM_DigitalCompareCBCLatchClearEvent[0].name,
                options     : device_driverlib_peripheral.EPWM_DigitalCompareCBCLatchClearEvent,
            }
        }
        

        if (dcCompareEvent.name == "EPWM_DC_EVENT_1")
        {
            var dcCompareGenerateADCTriggerConfig = {
                name: "epwmDigitalCompare_" + dcCompareModule.name + "_" + dcCompareEvent.name + "_adcTrig",
                displayName : "Generate ADC SOC (" + dcxevty + ")",
                description : "Enable/disable generation of ADC SOC Event for " +  dcCompareModule.displayName + " " + dcCompareEvent.displayName,
                hidden      : false,
                default     : false,
            }

            var dcCompareGenerateSyncTriggerConfig = {
                name: "epwmDigitalCompare_" + dcCompareModule.name + "_" + dcCompareEvent.name + "_syncTrig",
                displayName : "Generate SYNCOUT (" + dcxevty + ")",
                description : "Enable/disable generation of SYNCOUTEvent for " +  dcCompareModule.displayName + " " + dcCompareEvent.displayName,
                hidden      : false,
                default     : false,
            }

            if (dcCompareModule.name.indexOf("MODULE_A") != -1)
            {
                DCAConfigs.push(dcCompareGenerateADCTriggerConfig);
                DCAConfigs.push(dcCompareGenerateSyncTriggerConfig);
            }
            else
            {
                DCBConfigs.push(dcCompareGenerateADCTriggerConfig);
                DCBConfigs.push(dcCompareGenerateSyncTriggerConfig);
            }
        }

        if (dcCompareModule.name.indexOf("MODULE_A") != -1)
        {
            DCAConfigs.push(dcCompareEventSyncConfig);
            DCAConfigs.push(dcCompareEventSourceConfig);
            if (dcCompareEventCBCLatchModeConfig){
                DCAConfigs.push(dcCompareEventCBCLatchModeConfig);
                DCAConfigs.push(dcCompareEventCBCLatchClearEventConfig);
            }
        }
        else
        {
            DCBConfigs.push(dcCompareEventSyncConfig);
            DCBConfigs.push(dcCompareEventSourceConfig);
            if (dcCompareEventCBCLatchModeConfig){
                DCBConfigs.push(dcCompareEventCBCLatchModeConfig);
                DCBConfigs.push(dcCompareEventCBCLatchClearEventConfig);
            }
        }
    }
}


var config = [
        {
            name: "GROUP_DCA",
            displayName: "DCAEVT1 and DCAEVT2",
            description: "",
            longDescription: "",
            config: DCAConfigs
        },
        {
            name: "GROUP_DCB",
            displayName: "DCBEVT1 and DCBEVT2",
            description: "",
            longDescription: "",
            config: DCBConfigs
        },
    {
        name: "epwmDigitalCompare_dcFilterInput",
        displayName : "Digital Compare Filter Input (DCEVTFILT event source)",
        description : 'Select the event source for the DCEVTFILT signal',
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_DigitalCompareFilterInput[0].name,
        options     : device_driverlib_peripheral.EPWM_DigitalCompareFilterInput,
    },

    // Blanking window
    {
        name: "epwmDigitalCompare_useBlankingWindow",
        displayName : "Use Blanking Window",
        description : 'Use blanking window to blank the DCEVTFILT signal',
        hidden      : false,
        default     : false,
        onChange    : onChangeBlankingWindow
    },
    {
        name: "epwmDigitalCompare_blankingWindowEvent",
        displayName : "Blanking Window Start Event",
        description : 'Select the event source that starts the blanking window counter (And resets the counter)',
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_DigitalCompareBlankingPulse[0].name,
        options     : device_driverlib_peripheral.EPWM_DigitalCompareBlankingPulse,
        onChange    : pulseSelChanged
    },
    {
        name: "epwmDigitalCompare_blankingWindowOffset",
        displayName : "Blanking Window Offset from the Start Event",
        description : 'Set the offset of the blanking window (TBCLK count)',
        hidden      : true,
        default     : 0,
    },
    {
        name: "epwmDigitalCompare_blankingWindowLength",
        displayName : "Blanking Window Length",
        description : 'Set the length of the blanking window (TBCLK count)',
        hidden      : true,
        default     : 0,
    },
    {
        name: "epwmDigitalCompare_invertBlankingWindow",
        displayName : "Invert Blanking Window",
        description : 'Invert the blanking window signal',
        hidden      : true,
        default     : false
    },

    // DCCAP

    {
        name: "epwmDigitalCompare_useDCCounterCapture", 
        displayName : "Use DC Counter Capture",
        description : 'Use the DC Counter Capture feature to capture the TBCTR value at the selected event.',
        hidden      : false,
        default     : false,
        onChange    : onChangeDCCounterCapture
    },
    {
        name: "epwmDigitalCompare_dCCounterCaptureShadow",
        displayName : "Enable DC Counter Capture Shadow Mode",
        description : 'Use the DC Counter Capture feature in shadow mode.',
        hidden      : true,
        default     : false
    },
    {
        name: "epwmDigitalCompare_dCCounterCapturePulse",
        displayName : "DC Counter Capture Re-Enable Event\\Shadow Load Event (Blanking Window Start Event)",
        description : 'This is detemined by the Blanking Window Start Event and re-enables the TBCTR capture.',
        hidden      : true,
        readOnly    : true,
        default     : device_driverlib_peripheral.EPWM_DigitalCompareBlankingPulse[0].name,
        options     : device_driverlib_peripheral.EPWM_DigitalCompareBlankingPulse,
    },
    {
        name: "epwmDigitalCompare_dCCounterCapturePulseLogic",
        displayName : "DC Counter Capture Independent Pulse Selection",
        description : 'Pulse Selection between digital compare capture or digital compare blanking signal',
        hidden      : true,
        default     : false,
    },
    

    // Edge Filter Valley Switching
    {
        name: "epwmDigitalCompare_useEdgeFilter",
        displayName : "Use Edge Filter",
        description : 'The DCEVTFILT signal and DCCAP (Counter Capture) will use the output of the edge filter',
        hidden      : false,
        default     : false,
        onChange    : onChangeEdgeFilter
    },
    {
        name: "epwmDigitalCompare_edgeFilterMode", 
        displayName : "Edge Filter Mode",
        description : 'Sets the Digital Compare Event edge filter mode',
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_DigitalCompareEdgeFilterMode[0].name,
        options     : device_driverlib_peripheral.EPWM_DigitalCompareEdgeFilterMode,
    },
    
    {
        name: "epwmDigitalCompare_edgeFilterEdgeCount",
        displayName : "Edge Filter Edge Count",
        description : 'Sets the number of edges detected by the Digital Compare Event edge filter to generate an event',
        hidden      : true,
        default     : "EPWM_DC_EDGEFILT_EDGECNT_0",
        options     : [
            { name: "EPWM_DC_EDGEFILT_EDGECNT_0", displayName: "No edge is required to generate event"},
            { name: "EPWM_DC_EDGEFILT_EDGECNT_1", displayName: "1 edge is required for event generation" },
            { name: "EPWM_DC_EDGEFILT_EDGECNT_2", displayName: "2 edges are required for event generation" },
            { name: "EPWM_DC_EDGEFILT_EDGECNT_3", displayName: "3 edges are required for event generation" },
            { name: "EPWM_DC_EDGEFILT_EDGECNT_4", displayName: "4 edges are required for event generation" },
            { name: "EPWM_DC_EDGEFILT_EDGECNT_5", displayName: "5 edges are required for event generation" },
            { name: "EPWM_DC_EDGEFILT_EDGECNT_6", displayName: "6 edges are required for event generation" },
            { name: "EPWM_DC_EDGEFILT_EDGECNT_7", displayName: "7 edges are required for event generation" },
        ],
    },
    {
        name: "epwmDigitalCompare_enableValleyCapture", 
        displayName : "Enable Edge Filter Reset/Enable Valley Capture",
        description : 'This will enable valley capturing feature/allows the input signal selected for valley capturing to reset the edge filter counter',
        hidden      : true,
        default     : false,
        onChange    : onChangeEdgeFilter
    },
    
    {
        name: "epwmDigitalCompare_valleyCaptureSource",
        displayName : "Edge Filter Counter Reset/Valley Capture Signal Source",
        description : 'Sets the signal source for valley capture and edge filter counter reset',
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_ValleyTriggerSource[0].name,
        options     : device_driverlib_peripheral.EPWM_ValleyTriggerSource,
        onChange    : onChangeEdgeFilter
    },
    {
        name: "epwmDigitalCompare_startValleyCapture", 
        displayName : "Start Valley Capture Logic",
        description : 'Start the valley capture logic',
        hidden      : true,
        default     : false
    },
    {
        name: "epwmDigitalCompare_startValleyCaptureTriggerCount", 
        displayName : "Start Valley Capture",
        description : 'The number of trigger events required to start the valley capture count',
        hidden      : true,
        default     : "0",
        options     : [
            { displayName: "0 Event (Prevent from starting)", name : "0" },
            { displayName: "1 Events",  name : "1" },
            { displayName: "2 Events",  name : "2" },
            { displayName: "3 Events",  name : "3" },
            { displayName: "4 Events",  name : "4" },
            { displayName: "5 Events",  name : "5" },
            { displayName: "6 Events",  name : "6" },
            { displayName: "7 Events",  name : "7" },
            { displayName: "8 Events",  name : "8" },
            { displayName: "9 Events",  name : "9" },
            { displayName: "10 Events", name : "10"},
            { displayName: "11 Events", name : "11"},
            { displayName: "12 Events", name : "12"},
            { displayName: "14 Events", name : "14"},
            { displayName: "15 Events", name : "15"},
        ]
    },
    {
        name: "epwmDigitalCompare_stopValleyCaptureTriggerCount",
        displayName : "Stop Valley Capture",
        description : 'The number of trigger events required to stop the valley capture count',
        hidden      : true,
        default     : "0",
        options     : [
            { displayName: "0 Event (Prevent from stopping)", name : "0" },
            { displayName: "1 Events",  name : "1" },
            { displayName: "2 Events",  name : "2" },
            { displayName: "3 Events",  name : "3" },
            { displayName: "4 Events",  name : "4" },
            { displayName: "5 Events",  name : "5" },
            { displayName: "6 Events",  name : "6" },
            { displayName: "7 Events",  name : "7" },
            { displayName: "8 Events",  name : "8" },
            { displayName: "9 Events",  name : "9" },
            { displayName: "10 Events", name : "10"},
            { displayName: "11 Events", name : "11"},
            { displayName: "12 Events", name : "12"},
            { displayName: "14 Events", name : "14"},
            { displayName: "15 Events", name : "15"},
        ]
    },
    {
        name: "epwmDigitalCompare_enableEdgeFilterDelay", 
        displayName : "Select the delayed output (by HWDELVAL) of the Edge Filter",
        description : 'Start the valley capture logic',
        hidden      : true,
        default     : false,
        onChange    : onChangeEdgeFilter
    },
    {
        name: "epwmDigitalCompare_SWVDELVAL",
        displayName : "SWVDELVAL (software valley delay value)",
        description : 'Set SWVDELVAL (software valley delay value). This value along with the valley delay divider will be used to calculate the HWDELVAL',
        hidden      : true,
        default     : 0
    },
    {
        name: "epwmDigitalCompare_valleyDelayDivider",
        displayName : "Valley Delay Divider",
        description : 'The delay divider along with SWVDELVAL will be used to calculate the HWDELVAL',
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_ValleyDelayMode[0].name,
        options     : device_driverlib_peripheral.EPWM_ValleyDelayMode,
    }
];

if(["F28P65x"].includes(Common.getDeviceName()))
{
    config = config.concat(    
        {
            name: "epwmDigitalCompare_enableEventDetection",
            displayName : "Use Event Detection",
            description : "Use the DC Event Detection to determine occurrence of a trip event in a configured time window",
            hidden      : false,
            default     : false,
            onChange    : onChangeEventDetection
        },
        {
            name: "epwmDigitalCompare_CAPINTripInput",
            displayName : "Capture Input",
            description : "Trip input on which edge detection logic is performed",
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_DigitalCompareTripInput[0].name,
            options     : device_driverlib_peripheral.EPWM_DigitalCompareTripInput,
        },
        {
            name: "epwmDigitalCompare_CAPIN_combinationInputConfig",
            displayName : "Combination Capture Input Sources",
            description : "Select the sources to include in the Combination input sources",
            hidden      : true,
            minSelections: 0,
            default     : [],
            options     : device_driverlib_peripheral.EPWM_DC_COMBINATIONAL
        },
        {
            name: "epwmDigitalCompare_invertCAPIN", 
            displayName : "Invert Capture Input polarity",
            description : 'Selects the input polarity for capture',
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_selectCaptureInputPolarity[0].name,
            options     : device_driverlib_peripheral.EPWM_selectCaptureInputPolarity,
        },
        {
            name: "epwmDigitalCompare_CAPGATETripInput",
            displayName : "Capture Gate",
            description : "Trip input gating the min/max logic",
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_DigitalCompareTripInput[0].name,
            options     : device_driverlib_peripheral.EPWM_DigitalCompareTripInput,
        },
        {
            name: "epwmDigitalCompare_CAPGATE_combinationInputConfig",
            displayName : "Combination Capture Gate Input Sources",
            description : "Select the sources to include in the Combination input sources",
            hidden      : true,
            minSelections: 0,
            default     : [],
            options     : device_driverlib_peripheral.EPWM_DC_COMBINATIONAL
        },
        {
            name: "epwmDigitalCompare_configCAPGATE", 
            displayName : "Capture Gate Polarity Select",
            description : 'Capture Gate selection of the input polarity',
            hidden      : true,
            default     : device_driverlib_peripheral.EPWM_selectCaptureGateInputPolarity[0].name,
            options     : device_driverlib_peripheral.EPWM_selectCaptureGateInputPolarity
        },
        {
            name: "epwmXCMP_setRegisters_XMIN_read",
            displayName: "XMIN",
            hidden: true,
            getValue: (inst) => inst.epwmXCMP_setRegisters_XMIN,
            default: 0,
        },
        {
            name: "epwmXCMP_setShadowRegisters1_XMIN_read",
            displayName: "XMIN Shadow 1",
            hidden: true,
            getValue: (inst) => inst.epwmXCMP_setShadowRegisters1_XMIN,
            default: 0,
        },
        {
            name: "epwmXCMP_setShadowRegisters2_XMIN_read",
            displayName: "XMIN Shadow 2",
            hidden: true,
            getValue: (inst) => inst.epwmXCMP_setShadowRegisters2_XMIN,
            default: 0,
        },
        {
            name: "epwmXCMP_setShadowRegisters3_XMIN_read",
            displayName: "XMIN Shadow 3",
            hidden: true,
            getValue: (inst) => inst.epwmXCMP_setShadowRegisters3_XMIN,
            default: 0,
        },
        {
            name: "epwmXCMP_setRegisters_XMAX_read",
            displayName: "XMAX",
            hidden: true,
            getValue: (inst) => inst.epwmXCMP_setRegisters_XMAX,
            default: 0,
        },  
        {
            name: "epwmXCMP_setShadowRegisters1_XMAX_read",
            displayName: "XMAX Shadow 1",
            hidden: true,
            getValue: (inst) => inst.epwmXCMP_setShadowRegisters1_XMAX,
            default: 0,
        },     
        {
            name: "epwmXCMP_setShadowRegisters2_XMAX_read",
            displayName: "XMAX Shadow 2",
            hidden: true,
            getValue: (inst) => inst.epwmXCMP_setShadowRegisters2_XMAX,
            default: 0,
        },
        {
            name: "epwmXCMP_setShadowRegisters3_XMAX_read",
            displayName: "XMAX Shadow 3",
            hidden: true,
            getValue: (inst) => inst.epwmXCMP_setShadowRegisters3_XMAX,
            default: 0,
        }
    )
}

var epwmDigitalCompareSubmodule = {
    displayName: "EPWM Digital Compare",
    maxInstances: Common.peripheralCount("EPWM"),
    defaultInstanceName: "EPWM_DC",
    description: "Enhanced Pulse Width Modulator Digital Compare",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};


exports = epwmDigitalCompareSubmodule;