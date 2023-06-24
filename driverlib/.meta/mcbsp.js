let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_mcbsp.js");

/* Intro splash on GUI */
let longDescription = "A MCBSP peripheral is used to translate data between " +
    "the chip and a serial port. The SCI driver simplifies reading " +
    "and writing to any of the UART peripherals on the board, with " +
    "multiple modes of operation and performance. These include " +
    "blocking, non-blocking, and polling, as well as text/binary " +
    "mode, echo and return characters.";

function onChangeFrameSyncLogic(inst, ui) {
    if (inst.enableFrameSyncLogic == true) {
        ui.frameSyncPulsePeriodDivider.hidden = false
        ui.frameSyncPulseWidthDivider.hidden = false
        ui.rxFrameSyncSource.hidden = false
        ui.rxFrameSyncPolarity.hidden = false
        ui.txFrameSyncSource.hidden = false
        ui.txInternalFrameSyncSource.hidden = false
        ui.txFrameSyncPolarity.hidden = false
    }
    else {
        ui.frameSyncPulsePeriodDivider.hidden = true
        ui.frameSyncPulseWidthDivider.hidden = true
        ui.rxFrameSyncSource.hidden = true
        ui.rxFrameSyncPolarity.hidden = true
        ui.txFrameSyncSource.hidden = true
        ui.txInternalFrameSyncSource.hidden = true
        ui.txFrameSyncPolarity.hidden = true
    }
}

function onChangeSampleRateGenerator(inst, ui) {
    if (inst.enableSampleRateGenerator == true) {
        ui.srgDataClockDivider.hidden = false
        ui.enableSRGSyncFSR.hidden = false
        ui.rxSRGClockSource.hidden = false
        ui.txSRGClockSource.hidden = false
    }
    else {
        ui.srgDataClockDivider.hidden = true
        ui.enableSRGSyncFSR.hidden = true
        ui.rxSRGClockSource.hidden = true
        ui.txSRGClockSource.hidden = true
    }
}


function onChangeChannelMode(inst,ui)
{
    if (inst.rxChannelMode == "MCBSP_RX_CHANNEL_SELECTION_ENABLED") {
        ui.rxChannelSelect.hidden = false
        ui.rxMultichannelPartition.hidden = false
    }

    if (inst.rxChannelMode == "MCBSP_ALL_RX_CHANNELS_ENABLED") {
        ui.rxChannelSelect.hidden = true
        ui.rxMultichannelPartition.hidden = true
    }

    if (inst.txChannelMode == "MCBSP_TX_CHANNEL_SELECTION_ENABLED") {
        ui.txChannelSelect.hidden = false
        ui.txMultichannelPartition.hidden = false
    }

    if (inst.txChannelMode == "MCBSP_ALL_TX_CHANNELS_ENABLED") {
        ui.txChannelSelect.hidden = true
        ui.txMultichannelPartition.hidden = true
    }

    if (inst.txChannelMode == "MCBSP_ENABLE_MASKED_TX_CHANNEL_SELECTION") {
        //TODO
    }

    if (inst.txChannelMode == "MCBSP_SYMMERTIC_RX_TX_SELECTION") {
        //TODO
    }
}



function onChangeEnableSPIController(inst, ui)
{
    if (inst.enableSPIController) {
        inst.txClockSource = "MCBSP_INTERNAL_TX_CLOCK_SOURCE";
        inst.txSRGClockSource = "MCBSP_SRG_TX_CLOCK_SOURCE_LSPCLK";
        inst.txFrameSyncSource = "MCBSP_TX_INTERNAL_FRAME_SYNC_SOURCE";
        inst.txInternalFrameSyncSource = "MCBSP_TX_INTERNAL_FRAME_SYNC_DATA";
        inst.txFrameSyncPolarity = "MCBSP_TX_FRAME_SYNC_POLARITY_LOW";
        inst.enableTwoPhaseTX = false;
        inst.txDataDelayBits = "MCBSP_DATA_DELAY_BIT_1";
        inst.rxDataDelayBits = "MCBSP_DATA_DELAY_BIT_1";

        ui.txClockSource.readOnly = true;
        ui.txSRGClockSource.readOnly = true;
        ui.txFrameSyncSource.readOnly = true;
        ui.txInternalFrameSyncSource.readOnly = true;
        ui.txFrameSyncPolarity.readOnly = true;
        ui.enableTwoPhaseTX.readOnly = true;
        ui.txDataDelayBits.readOnly = true;
        ui.rxDataDelayBits.readOnly = true;

        inst.clockStopMode = device_driverlib_peripheral.McBSP_ClockStopMode[1].name;
    }

    else {
        ui.txClockSource.readOnly = false;
        ui.txSRGClockSource.readOnly = false;
        ui.txFrameSyncSource.readOnly = false;
        ui.txInternalFrameSyncSource.readOnly = false;
        ui.txFrameSyncPolarity.readOnly = false;
        ui.enableTwoPhaseTX.readOnly = false;
        ui.txDataDelayBits.readOnly = false;
        ui.rxDataDelayBits.readOnly = false;
    }
}

function onChangeEnableSPIPeripheral(inst, ui)
{
    if (inst.enableSPIPeripheral) {
        inst.txClockSource = "MCBSP_EXTERNAL_TX_CLOCK_SOURCE";
        inst.enableSampleRateGenerator = true;
        inst.rxSRGClockSource = "MCBSP_SRG_RX_CLOCK_SOURCE_LSPCLK";
        inst.srgDataClockDivider = 1;
        inst.txFrameSyncSource = "MCBSP_TX_EXTERNAL_FRAME_SYNC_SOURCE";
        inst.txFrameSyncPolarity = "MCBSP_TX_FRAME_SYNC_POLARITY_LOW";
        inst.enableTwoPhaseTX = false;
        inst.txDataDelayBits = "MCBSP_DATA_DELAY_BIT_0";
        inst.rxDataDelayBits = "MCBSP_DATA_DELAY_BIT_0";

        ui.txClockSource.readOnly = true;
        ui.enableSampleRateGenerator.readOnly = true;
        ui.rxSRGClockSource.readOnly = true;
        ui.srgDataClockDivider.hidden = false;
        ui.enableSRGSyncFSR.hidden = false;
        ui.srgDataClockDivider.readOnly = true;
        ui.txFrameSyncSource.readOnly = true;
        ui.txFrameSyncPolarity.readOnly = true;
        ui.enableTwoPhaseTX.readOnly = true;
        ui.txDataDelayBits.readOnly = true;
        ui.rxDataDelayBits.readOnly = true;

        inst.clockStopMode = device_driverlib_peripheral.McBSP_ClockStopMode[1].name;
    }

    else {
        ui.txClockSource.readOnly = false;
        ui.enableSampleRateGenerator.readOnly = false;
        ui.rxSRGClockSource.readOnly = false;
        ui.srgDataClockDivider.readOnly = false;
        ui.txFrameSyncSource.readOnly = false;
        ui.txFrameSyncPolarity.readOnly = false;
        ui.enableTwoPhaseTX.readOnly = false;
        ui.txDataDelayBits.readOnly = false;
        ui.rxDataDelayBits.readOnly = false;
    }
}

function onChangeEnableTwoPhaseRX(inst, ui)
{
    if (inst.enableTwoPhaseRX) {
        ui.rxDataBitsPerWordPhase2.hidden = false;
        ui.rxWordsPerFramePhase2.hidden = false;
    }
    else {
        ui.rxDataBitsPerWordPhase2.hidden = true;
        ui.rxWordsPerFramePhase2.hidden = true;
    }
}

function onChangeEnableTwoPhaseTX(inst, ui)
{
    if (inst.enableTwoPhaseTX) {
        ui.txDataBitsPerWordPhase2.hidden = false;
        ui.txWordsPerFramePhase2.hidden = false;
    }
    else {
        ui.txDataBitsPerWordPhase2.hidden = true;
        ui.txWordsPerFramePhase2.hidden = true;
    }
}

function onChangeEnableRxInterrupts(inst, ui)
{
    if (inst.enableRxInterrupt == true ){
        ui.registerRxInterrupts.hidden = false;
       
        
    }
    else {
        ui.registerRxInterrupts.hidden = true;
       

    }
}	
function onChangeEnableTxInterrupts(inst, ui)
{
    if (inst.enableTxInterrupt == true ){
        ui.registerTxInterrupts.hidden = false;
       
        
    }
    else {
        ui.registerTxInterrupts.hidden = true;
       

    }	
 
} 

function calculatePartitionsUsed(channelSelectArray)
{
    //Block A: Partitions 0, 2, 4, 6 -> Channels 0-15; 32-47; 64-79; 96-111
    //Block B: Partitions 1, 3, 5, 7 -> Channels 16-31; 48-63; 80-95; 112-127 
    let partitionsUsed = 0;
    let p0 = 0;
    let p1 = 0;
    let p2 = 0;
    let p3 = 0;
    let p4 = 0;
    let p5 = 0;
    let p6 = 0;
    let p7 = 0;
    for (let i = 0; i < channelSelectArray.length; i++) {
        if (channelSelectArray[i] >= 0 && channelSelectArray[i] <= 15) {
            p0 = 1;
        }
        if (channelSelectArray[i] >= 16 && channelSelectArray[i] <= 31) {
            p1 = 1;
        }
        if (channelSelectArray[i] >= 32 && channelSelectArray[i] <= 47) {
            p2 = 1;
        }
        if (channelSelectArray[i] >= 48 && channelSelectArray[i] <= 63) {
            p3 = 1;
        }
        if (channelSelectArray[i] >= 64 && channelSelectArray[i] <= 79) {
            p4 = 1;
        }
        if (channelSelectArray[i] >= 80 && channelSelectArray[i] <= 95) {
            p5 = 1;
        }
        if (channelSelectArray[i] >= 96 && channelSelectArray[i] <= 111) {
            p6 = 1;
        }
        if (channelSelectArray[i] >= 112 && channelSelectArray[i] <= 127) {
            p7 = 1;
        }
    }
    return partitionsUsed = p0+p1+p2+p3+p4+p5+p6+p7;
}

let channelArray = [];
for (let i = 0; i < 128; i++) {
    channelArray.push({ name: i.toString(), displayName: i.toString()});
}


let config = [
   
    {
        name: "useCase",
        displayName : "Pinmux Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("MCBSP"),
        onChange    : Pinmux.useCaseChanged,
    },

    {
        name        : "enableLoopback",
        displayName : "Enable Loopback",
        description : "Enable loopback on the selected peripheral.",
        hidden      : false,
        default     : false,
    },

    {
        name        : "enableSPIController",
        displayName : "Enable SPI Controller Mode",
        description : "Enable SPI Controller Mode.",
        hidden      : false,
        default     : false,
        onChange    : onChangeEnableSPIController,
    },

    {
        name        : "enableSPIPeripheral",
        displayName : "Enable SPI Peripheral Mode",
        description : "Enable SPI Peripheral Mode.",
        hidden      : false,
        default     : false,
        onChange    : onChangeEnableSPIPeripheral,
    },

    {
        name        : "clockStopMode",
        displayName : "Clock Stop Mode",
        description : "Set clock stop mode.",
        hidden      : false,
        default     : device_driverlib_peripheral.McBSP_ClockStopMode[0].name,
        options     : device_driverlib_peripheral.McBSP_ClockStopMode
    },

    {
        name        : "enableDxPinDelay",
        displayName : "Enable Dx Pin Delay",
        description : "Whether or not to enable Dx pin delay.",
        hidden      : false,
        default     : false,
    },

    {
        name        : "emulationMode",
        displayName : "Emulation Mode",
        description : "Set emulation mode.",
        hidden      : false,
        default     : device_driverlib_peripheral.McBSP_EmulationMode[0].name,
        options     : device_driverlib_peripheral.McBSP_EmulationMode
    },

    {
        name        : "enableFrameSyncLogic",
        displayName : "Configure Frame Sync Logic",
        description : "Enable Frame Sync Logic.",
        hidden      : false,
        default     : false,
        onChange    : onChangeFrameSyncLogic
    },

    {
        name        : "frameSyncPulsePeriodDivider",
        displayName : "Frame Sync Pulse Period Divider",
        description : "Frame Sync Pulse Period Divider.",
        hidden      : true,
        default     : 0,
    },

    {
        name        : "frameSyncPulseWidthDivider",
        displayName : "Frame Sync Pulse Width Divider",
        description : "Frame Sync Pulse Width Divider.",
        hidden      : true,
        default     : 0,
    },

    {
        name        : "enableSampleRateGenerator",
        displayName : "Configure Sample Rate Generator",
        description : "Enable Sample Rate Generator.",
        hidden      : false,
        default     : false,
        onChange    : onChangeSampleRateGenerator
    },

    {
        name        : "srgDataClockDivider",
        displayName : "SRG Data Clock Divider",
        description : "SRG Data Clock Divider.",
        hidden      : true,
        default     : 0,
    },

    {
        name        : "enableSRGSyncFSR",
        displayName : "Enable SRG Sync FSR",
        description : "Enable SRG Sync FSR.",
        hidden      : true,
        default     : false,
    },
	
	

];

config = config.concat([{
    name: "GROUP_RECEIVER",
    displayName: "Receiver Setup",
    description: "Receiver setup options",
    longDescription: "",
    config: [
        {
            name        : "enableReceiver",
            displayName : "Configure Receiver",
            description : "Setup the reciever on the peripheral.",
            hidden      : false,
            default     : false,
        },

        {
            name        : "enableRxInterrupt",
            displayName : "Enable RX Interrupt",
            description : "Enable RX Interrupt.",
            hidden      : false,
            default     : false,
			onChange    : onChangeEnableRxInterrupts,
        },
		{
            name        : "registerRxInterrupts",
            displayName : "Register Rx Interrupt Handler",
            description : 'Whether or not to register interrupt handlers in the interrupt module.',
            hidden      : true,
            default     : false,       
        },
        
        {
            name        : "rxInterruptSource",
            displayName : "RX Interrupt Source",
            description : "RX Interrupt Source.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_RxInterruptSource[0].name,
            options     : device_driverlib_peripheral.McBSP_RxInterruptSource,
			
        },
    
        {
            name        : "rxSignExtension",
            displayName : "RX Sign Extension Mode",
            description : "Set sign extension mode for recieve.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_RxSignExtensionMode[0].name,
            options     : device_driverlib_peripheral.McBSP_RxSignExtensionMode
        },
    
        {
            name        : "rxCompandingMode",
            displayName : "RX Companding Mode",
            description : "Set RX Companding Mode.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_CompandingMode[0].name,
            options     : device_driverlib_peripheral.McBSP_CompandingMode
        },
    
        {
            name        : "rxDataDelayBits",
            displayName : "RX Data Delay Bits",
            description : "Set RX Data Delay Bits.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_DataDelayBits[0].name,
            options     : device_driverlib_peripheral.McBSP_DataDelayBits
        },

        {
            name        : "rxClockSource",
            displayName : "RX Clock Source",
            description : "Set RX Clock Source.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_RxClockSource[0].name,
            options     : device_driverlib_peripheral.McBSP_RxClockSource
        },

        {
            name        : "rxClockPolarity",
            displayName : "RX Clock Polarity",
            description : "Set Clock Polarity.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_RxClockPolarity[0].name,
            options     : device_driverlib_peripheral.McBSP_RxClockPolarity
        },

        {
            name        : "rxFrameSyncSource",
            displayName : "RX Frame Sync Source",
            description : "Set Frame Sync Source.",
            hidden      : true,
            default     : device_driverlib_peripheral.McBSP_RxFrameSyncSource[0].name,
            options     : device_driverlib_peripheral.McBSP_RxFrameSyncSource
        },

        {
            name        : "rxFrameSyncPolarity",
            displayName : "RX Frame Sync Polarity",
            description : "Set Frame Sync Polarity.",
            hidden      : true,
            default     : device_driverlib_peripheral.McBSP_RxFrameSyncPolarity[0].name,
            options     : device_driverlib_peripheral.McBSP_RxFrameSyncPolarity
        },

        {
            name        : "enableRxFrameSyncErrorDetection",
            displayName : "Enable RX Frame Sync Error Detection",
            description : "Enable RX Frame Sync Error Detection.",
            hidden      : false,
            default     : false,
        },

        {
            name        : "rxSRGClockSource",
            displayName : "RX SRG Clock Source",
            description : "Set RX SRG Clock Source.",
            hidden      : true,
            default     : device_driverlib_peripheral.McBSP_SRGRxClockSource[0].name,
            options     : device_driverlib_peripheral.McBSP_SRGRxClockSource
        },

        {
            name        : "rxChannelMode",
            displayName : "RX Channel Mode",
            description : "Set Channel Mode.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_RxChannelMode[0].name,
            options     : device_driverlib_peripheral.McBSP_RxChannelMode,
            onChange    : onChangeChannelMode
        },

        {
            name        : "rxMultichannelPartition",
            displayName : "RX Multichannel Partition",
            description : "Set RX Multichannel Partition.",
            hidden      : true,
            default     : device_driverlib_peripheral.McBSP_MultichannelPartition[0].name,
            options     : device_driverlib_peripheral.McBSP_MultichannelPartition,
           
        },

        {
            name        : "rxChannelSelect",
            displayName : "RX Channel Select",
            description : "RX Channel Select.",
            hidden      : true,
            default     : [],
            minSelections: 0,
            options     : channelArray,
        },

        {
            name        : "enableTwoPhaseRX",
            displayName : "Enable Two Phase Receive",
            description : "Enable Two Phase Receive.",
            hidden      : false,
            default     : false,
            onChange    : onChangeEnableTwoPhaseRX,
        },

        {
            name        : "rxDataBitsPerWordPhase1",
            displayName : "RX Data Bits Per Word (Phase 1)",
            description : "Set Data Bits Per Word (Phase 1).",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_DataBitsPerWord[0].name,
            options     : device_driverlib_peripheral.McBSP_DataBitsPerWord
        },

        {
            name        : "rxWordsPerFramePhase1",
            displayName : "RX Words Per Frame (Phase 1)",
            description : "RX Words Per Frame (Phase 1).",
            hidden      : false,
            default     : 0,
        },

        {
            name        : "rxDataBitsPerWordPhase2",
            displayName : "RX Data Bits Per Word (Phase 2)",
            description : "Set Data Bits Per Word (Phase 2).",
            hidden      : true,
            default     : device_driverlib_peripheral.McBSP_DataBitsPerWord[0].name,
            options     : device_driverlib_peripheral.McBSP_DataBitsPerWord
        },

        {
            name        : "rxWordsPerFramePhase2",
            displayName : "RX Words Per Frame (Phase 2)",
            description : "RX Words Per Frame (Phase 2).",
            hidden      : true,
            default     : 0,
        },
    ]
}]);

config = config.concat([{
    name: "GROUP_TRANSMITTER",
    displayName: "Transmitter Setup",
    description: "Transmitter setup options",
    longDescription: "",
    config: [
        {
            name        : "enableTransmitter",
            displayName : "Configure Transmitter",
            description : "Setup the transmitter on the peripheral.",
            hidden      : false,
            default     : false,
        },

        {
            name        : "enableTxInterrupt",
            displayName : "Enable TX Interrupt",
            description : "Enable TX Interrupt.",
            hidden      : false,
            default     : false,
			onChange    : onChangeEnableTxInterrupts,
        },
        {
            name        : "registerTxInterrupts",
            displayName : "Register Tx Interrupt Handler",
            description : 'Whether or not to register interrupt handlers in the interrupt module.',
            hidden      : true,
            default     : false,       
        },
        {
            name        : "txInterruptSource",
            displayName : "TX Interrupt Source",
            description : "Set clock stop mode.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_TxInterruptSource[0].name,
            options     : device_driverlib_peripheral.McBSP_TxInterruptSource
        },
    
        {
            name        : "txCompandingMode",
            displayName : "TX Companding Mode",
            description : "Set TX Companding Mode.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_CompandingMode[0].name,
            options     : device_driverlib_peripheral.McBSP_CompandingMode
        },
    
        {
            name        : "txDataDelayBits",
            displayName : "TX Data Delay Bits",
            description : "Set TX Data Delay Bits.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_DataDelayBits[0].name,
            options     : device_driverlib_peripheral.McBSP_DataDelayBits
        },

        {
            name        : "txClockSource",
            displayName : "TX Clock Source",
            description : "Set TX Clock Source.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_TxClockSource[0].name,
            options     : device_driverlib_peripheral.McBSP_TxClockSource
        },

        {
            name        : "txClockPolarity",
            displayName : "TX Clock Polarity",
            description : "Set Clock Polarity.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_TxClockPolarity[0].name,
            options     : device_driverlib_peripheral.McBSP_TxClockPolarity
        },

        {
            name        : "txFrameSyncSource",
            displayName : "TX Frame Sync Source",
            description : "Set Frame Sync Source.",
            hidden      : true,
            default     : device_driverlib_peripheral.McBSP_TxFrameSyncSource[0].name,
            options     : device_driverlib_peripheral.McBSP_TxFrameSyncSource
        },

        {
            name        : "txInternalFrameSyncSource",
            displayName : "TX Internal Frame Sync Source",
            description : "Set TX Internal Frame Sync Source.",
            hidden      : true,
            default     : device_driverlib_peripheral.McBSP_TxInternalFrameSyncSource[0].name,
            options     : device_driverlib_peripheral.McBSP_TxInternalFrameSyncSource
        },

        {
            name        : "txFrameSyncPolarity",
            displayName : "TX Frame Sync Polarity",
            description : "Set Frame Sync Polarity.",
            hidden      : true,
            default     : device_driverlib_peripheral.McBSP_TxFrameSyncPolarity[0].name,
            options     : device_driverlib_peripheral.McBSP_TxFrameSyncPolarity
        },

        {
            name        : "enableTxFrameSyncErrorDetection",
            displayName : "Enable TX Frame Sync Error Detection",
            description : "Enable TX Frame Sync Error Detection.",
            hidden      : false,
            default     : false,
        },

        {
            name        : "txSRGClockSource",
            displayName : "TX SRG Clock Source",
            description : "Set TX SRG Clock Source.",
            hidden      : true,
            default     : device_driverlib_peripheral.McBSP_SRGTxClockSource[0].name,
            options     : device_driverlib_peripheral.McBSP_SRGTxClockSource
        },

        {
            name        : "txChannelMode",
            displayName : "TX Channel Mode",
            description : "Set Channel Mode.",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_TxChannelMode[0].name,
            options     : device_driverlib_peripheral.McBSP_TxChannelMode,
            onChange    : onChangeChannelMode
        },

        {
            name        : "txMultichannelPartition",
            displayName : "TX Multichannel Partition",
            description : "Set TX Multichannel Partition.",
            hidden      : true,
            default     : device_driverlib_peripheral.McBSP_MultichannelPartition[0].name,
            options     : device_driverlib_peripheral.McBSP_MultichannelPartition,
            
        },

        {
            name        : "txChannelSelect",
            displayName : "TX Channel Select",
            description : "TX Channel Select.",
            hidden      : true,
            default     : [],
            minSelections: 0,
            options     : channelArray,
        },

        {
            name        : "enableTwoPhaseTX",
            displayName : "Enable Two Phase Transmit",                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
            description : "Enable Two Phase Transmit.",
            hidden      : false,
            default     : false,
            onChange    : onChangeEnableTwoPhaseTX,
        },

        {
            name        : "txDataBitsPerWordPhase1",
            displayName : "TX Data Bits Per Word (Phase 1)",
            description : "Set Data Bits Per Word (Phase 1).",
            hidden      : false,
            default     : device_driverlib_peripheral.McBSP_DataBitsPerWord[0].name,
            options     : device_driverlib_peripheral.McBSP_DataBitsPerWord
        },

        {
            name        : "txWordsPerFramePhase1",
            displayName : "TX Words Per Frame (Phase 1)",
            description : "TX Words Per Frame (Phase 1).",
            hidden      : false,
            default     : 0,
        },

        {
            name        : "txDataBitsPerWordPhase2",
            displayName : "TX Data Bits Per Word (Phase 2)",
            description : "Set Data Bits Per Word (Phase 2).",
            hidden      : true,
            default     : device_driverlib_peripheral.McBSP_DataBitsPerWord[0].name,
            options     : device_driverlib_peripheral.McBSP_DataBitsPerWord
        },

        {
            name        : "txWordsPerFramePhase2",
            displayName : "TX Words Per Frame (Phase 2)",
            description : "TX Words Per Frame (Phase 2).",
            hidden      : true,
            default     : 0,
        },
    ]
}]);

function onValidate(inst, validation)
{
    if (inst.frameSyncPulsePeriodDivider > 4096 || inst.frameSyncPulsePeriodDivider < 0 || !Number.isInteger(inst.frameSyncPulsePeriodDivider)) {
        validation.logError("Frame sync pulse period divider must be an integer between 0 and 4096!", inst, "frameSyncPulsePeriodDivider");
    }
    
    if (inst.frameSyncPulseWidthDivider > 256 || inst.frameSyncPulseWidthDivider < 0 || !Number.isInteger(inst.frameSyncPulseWidthDivider)) {
        validation.logError("Pulse width divider must be an integer between 0 and 256!", inst, "frameSyncPulseWidthDivider");
    }

    if (inst.srgDataClockDivider > 256 || inst.srgDataClockDivider < 0 || !Number.isInteger(inst.srgDataClockDivider)) {
        validation.logError("SRG data clock divider must be an integer between 0 and 256!", inst, "srgDataClockDivider");
    }

    if (inst.txWordsPerFramePhase1 > 128 || inst.txWordsPerFramePhase1 < 0 || !Number.isInteger(inst.txWordsPerFramePhase1)) {
        validation.logError("Words per frame must be an integer between 0 and 128!", inst, "txWordsPerFramePhase1");
    }

    if (inst.txWordsPerFramePhase2 > 128 || inst.txWordsPerFramePhase2 < 0 || !Number.isInteger(inst.txWordsPerFramePhase2)) {
        validation.logError("Words per frame must be an integer between 0 and 128!", inst, "txWordsPerFramePhase2");
    }

    if (inst.rxWordsPerFramePhase1 > 128 || inst.rxWordsPerFramePhase1 < 0 || !Number.isInteger(inst.rxWordsPerFramePhase1)) {
        validation.logError("Words per frame must be an integer between 0 and 128!", inst, "rxWordsPerFramePhase1");
    }

    if (inst.rxWordsPerFramePhase2 > 128 || inst.rxWordsPerFramePhase2 < 0 || !Number.isInteger(inst.rxWordsPerFramePhase2)) {
        validation.logError("Words per frame must be an integer between 0 and 128!", inst, "rxWordsPerFramePhase2");
    }

    if ((inst.rxCompandingMode == "MCBSP_COMPANDING_U_LAW_SET" || inst.rxCompandingMode == "MCBSP_COMPANDING_A_LAW_SET") && inst.rxDataBitsPerWordPhase1 != "MCBSP_BITS_PER_WORD_8") {
        validation.logError("To use companding, word length must be 8 bits!", inst, "rxDataBitsPerWordPhase1");
    }

    if ((inst.rxCompandingMode == "MCBSP_COMPANDING_U_LAW_SET" || inst.rxCompandingMode == "MCBSP_COMPANDING_A_LAW_SET") && inst.rxDataBitsPerWordPhase2 != "MCBSP_BITS_PER_WORD_8") {
        validation.logError("To use companding, word length must be 8 bits!", inst, "rxDataBitsPerWordPhase2");
    }

    if ((inst.txCompandingMode == "MCBSP_COMPANDING_U_LAW_SET" || inst.txCompandingMode == "MCBSP_COMPANDING_A_LAW_SET") && inst.txDataBitsPerWordPhase1 != "MCBSP_BITS_PER_WORD_8") {
        validation.logError("To use companding, word length must be 8 bits!", inst, "txDataBitsPerWordPhase1");
    }

    if ((inst.txCompandingMode == "MCBSP_COMPANDING_U_LAW_SET" || inst.txCompandingMode == "MCBSP_COMPANDING_A_LAW_SET") && inst.txDataBitsPerWordPhase2 != "MCBSP_BITS_PER_WORD_8") {
        validation.logError("To use companding, word length must be 8 bits!", inst, "txDataBitsPerWordPhase2");
    }

    if (inst.enableSPIController && inst.enableSPIPeripheral) {
        validation.logError("Cannot be SPI Controller and Peripheral at same time!", inst, "enableSPIPeripheral");
    }

    if (inst.rxMultichannelPartition == "MCBSP_MULTICHANNEL_TWO_PARTITION" && calculatePartitionsUsed(inst.rxChannelSelect) > 2) {
        validation.logError("More than 2 channel partitions in use!", inst, "rxChannelSelect");
    }

    if (inst.txMultichannelPartition == "MCBSP_MULTICHANNEL_TWO_PARTITION" && calculatePartitionsUsed(inst.txChannelSelect) > 2) {
        validation.logError("More than 2 channel partitions in use!", inst, "txChannelSelect");
    }

    if ((inst.enableSPIController || inst.enableSPIPeripheral) && inst.clockStopMode == "MCBSP_CLOCK_MCBSP_MODE") {
        validation.logError("Clock stop mode must be enabled in SPI modes!", inst, "clockStopMode");
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
    return (Common.typeMatches(component.type, ["MCBSP"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var mcbspModule = {
    peripheralName: "MCBSP",
    displayName: "MCBSP",
    maxInstances: Common.peripheralCount("MCBSP"),
    defaultInstanceName: "myMCBSP",
    description: "Multichannel Buffered Serial Port Peripheral",
    longDescription: (Common.getCollateralFindabilityList("MCBSP")),
    filterHardware : filterHardware,
    moduleInstances: (inst) => {
    	var regInterrupts = []

        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("MCBSP", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.requiredArgs = {
                qualMode : "GPIO_QUAL_ASYNC",
            }
        }
        regInterrupts = regInterrupts.concat(pinmuxQualMods)

		if (inst.registerRxInterrupts)
    	{
	        regInterrupts.push({
	            name: "mcbspRXInt",      
	            displayName: "RX Interrupt",
	            moduleName: "/driverlib/interrupt.js",
	            collapsed: true,
	            args: {
            		$name : inst.$name + "_RX_INT",
	                int : "INT_" + inst.$name + "_RX",
	                pinmuxPeripheralModule : "mcbsp",
	                driverlibInt: "INT_#_RX"
	            }
	        
			})    			
		}
        if (inst.registerTxInterrupts)
		{
            regInterrupts.push({
                name: "mcbspTXInt",      
	            displayName: "TX Interrupt",
	            moduleName: "/driverlib/interrupt.js",
	            collapsed: true,
	            args: {
            		$name : inst.$name + "_TX_INT",
	                int : "INT_" + inst.$name + "_TX",
	                pinmuxPeripheralModule : "mcbsp",
	                driverlibInt: "INT_#_TX"
	            }
	        })
    	}
    	return regInterrupts;
    },
	
	config: config,
    templates: {
        boardc : "/driverlib/mcbsp/mcbsp.board.c.xdt",
        boardh : "/driverlib/mcbsp/mcbsp.board.h.xdt"
    },
    validate : onValidate,
    pinmuxRequirements    : Pinmux.mcbspPinmuxRequirements
};

if (mcbspModule.maxInstances <= 0)
{
    delete mcbspModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(mcbspModule)
    Pinmux.addPinMuxQualGroupToConfig(mcbspModule)
}

exports = mcbspModule;