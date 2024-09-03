let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

/* Intro splash on GUI */
let longDescription = "MCAN";

var longDescriptionNomBitTimeParam = `
Below Parameters define the length of individual segments of Nominal Bit Time finally governing the nominal bit rate.\n
MCANBitClk = SYSCLK/MCANCLKDIV\n

NominalbitTime (Tq) = (NTSEG1 + 1) + (NTSEG2 + 1) + 1\n
NominalBRP =  (NBRP+1)\n
FinalNominalBaudRate = MCANBitClk/( NominalBRP * NominalbitTime)\n`

var longDescriptionDataBitTimeParam = `
Below Parameters define the length of individual segments of Data Bit Time finally governing the data bit rate.\n
MCANBitClk = SYSCLK/MCANCLKDIV\n

DatabitTime = (DTSEG1 + 1) + (DTSEG2 + 1) + 1\n
DataBRP =  (DBRP+1)\n
FinalDataBaudRate = MCANBitClk/( DataBRP * DatabitTime)\n
`
var FileDescription = `The MCAN bit timing Calculator takes input as desired Nominal Bit Rate (kbps), Data Bit Rate (mbps), Bus length (m), System clock frequency (
MHz) and gives the bit time parameters as output based on best oscillator tollerance.\n
The file can be found at location C2000Ware/device_support/f2838x/docs/MCAN_BitTimingCalculator.xls\n
The outputs include\n
Nominal Time segment before/after sample point at Cell C49 (NTSEG1), C50 (NTSEG2) \n
Nominal Baud Rate Pre-scaler (NBRP) at Cell C52\n
Nominal (Re)Synchronization Jump Width Range (NSJW) at Cell C51\n
Data Time segment before/after sample point at Cell C58 (DTSEG1), C59 (DTSEG2) \n
Data Baud Rate Pre-scaler (DBRP) at Cell C61\n
Data (Re)Synchronization Jump Width Range (DSJW) at Cell C60\n
`

var Line0IntName = "INT_MCANA_0";
var Line1IntName = "INT_MCANA_1";
if ((["F28006x"].includes(Common.getDeviceName())) || (["F28P55x"].includes(Common.getDeviceName()))){
    Line0IntName = "INT_#_0";
    Line1IntName = "INT_#_1";
}

var stdFiltCountConfig = []
for (var stdFiltCount = 0; stdFiltCount < 128; stdFiltCount++)
{
    stdFiltCountConfig.push(
        {
            name: stdFiltCount ,
            displayName: stdFiltCount.toString()
        }
    );
}

function onChangeUseTdc(inst, ui)
{
    if (inst.tdcEnable) {
        ui.tdcConfig_tdcf.hidden = false;
        ui.tdcConfig_tdco.hidden = false;
    }
    else {
        ui.tdcConfig_tdcf.hidden = true;
        ui.tdcConfig_tdco.hidden = true;
    }
}
function onChangeEnableInterrupt(inst, ui)
{
    if (inst.enableInterrupt) {
        ui.interruptFlags.hidden = false;
        ui.interruptLine.hidden = false;
        ui.interruptLine0Flag.hidden = false;
        ui.interruptLine1Flag.hidden = false;
    }
    else {
        ui.interruptFlags.hidden = true;
        ui.interruptLine.hidden = true;
        ui.interruptLine0Flag.hidden = true;
        ui.interruptLine1Flag.hidden = true;

    }
}
function onChangeUseAddCon(inst, ui)
{
    if (inst.additionalCoreConfig) {
        ui.monEnable.hidden = false;
        ui.asmEnable.hidden = false;
        ui.tsPrescalar.hidden = false;
        ui.tsSelect.hidden = false;
        ui.timeoutSelect.hidden = false;
        ui.timeoutPreload.hidden = false;
        ui.timeoutCntEnable.hidden = false;
        ui.rrfs.hidden = false;
        ui.rrfe.hidden = false;
        ui.anfe.hidden = false;
        ui.anfs.hidden = false;
    }
    else {
        ui.monEnable.hidden = true;
        ui.asmEnable.hidden = true;
        ui.tsPrescalar.hidden = true;
        ui.tsSelect.hidden = true;
        ui.timeoutSelect.hidden = true;
        ui.timeoutPreload.hidden = true;
        ui.timeoutCntEnable.hidden = true;
        ui.rrfs.hidden = true;
        ui.rrfe.hidden = true;
        ui.anfe.hidden = true;
        ui.anfs.hidden = true;
    }
}
function onChangeMsgRamConfig(inst, ui)
{
    if (inst.msgRamConfig) {
        ui.flssa.hidden = false;
        ui.lss.hidden = false;
        ui.flesa.hidden = false;
        ui.lse.hidden = false;
        ui.txStartAddr.hidden = false;
        ui.txBufNum.hidden = false;
        ui.txFIFOSize.hidden = false;
        ui.txBufMode.hidden = false;
        ui.txBufElemSize.hidden = false;
        ui.txEventFIFOStartAddr.hidden = false;
        ui.txEventFIFOWaterMark.hidden = false;
        ui.rxFIFO0startAddr.hidden = false;
        ui.rxFIFO0size.hidden = false;
        ui.rxFIFO0waterMark.hidden = false;
        ui.rxFIFO0OpMode.hidden = false;
        ui.rxFIFO1startAddr.hidden = false;
        ui.rxFIFO1size.hidden = false;
        ui.rxFIFO1waterMark.hidden = false;
        ui.rxFIFO1OpMode.hidden = false;
        ui.rxBufStartAddr.hidden = false;
        ui.rxBufElemSize.hidden = false;
        ui.rxFIFO0ElemSize.hidden = false;
        ui.rxFIFO1ElemSize.hidden = false;
    }
    else {
        ui.flssa.hidden = true;
        ui.lss.hidden = true;
        ui.flesa.hidden = true;
        ui.lse.hidden = true;
        ui.txStartAddr.hidden = true;
        ui.txBufNum.hidden = true;
        ui.txFIFOSize.hidden = true;
        ui.txBufMode.hidden = true;
        ui.txBufElemSize.hidden = true;
        ui.txEventFIFOStartAddr.hidden = true;
        ui.txEventFIFOWaterMark.hidden = true;
        ui.rxFIFO0startAddr.hidden = true;
        ui.rxFIFO0size.hidden = true;
        ui.rxFIFO0waterMark.hidden = true;
        ui.rxFIFO0OpMode.hidden = true;
        ui.rxFIFO1startAddr.hidden = true;
        ui.rxFIFO1size.hidden = true;
        ui.rxFIFO1waterMark.hidden = true;
        ui.rxFIFO1OpMode.hidden = true;
        ui.rxBufStartAddr.hidden = true;
        ui.rxBufElemSize.hidden = true;
        ui.rxFIFO0ElemSize.hidden = true;
        ui.rxFIFO1ElemSize.hidden = true;
    }
}
var flssa, flesa;
var lss, lse; 
var rxFIFO0startAddr, rxFIFO1startAddr, rxBufStartAddr;
var rxFIFO0size, rxFIFO1size, rxBufNum;
var rxFIFO0ElemSize, rxFIFO1ElemSize, rxBufElemSize;
var txStartAddr, txEventFIFOStartAddr;
var txBufNum, txFIFOSize, txBufElemSize;
const objSize = [4, 5, 6, 7, 8, 10, 14, 18];
function calcStartingAddress()
{
    flssa = 0;
    flesa = lss * 4;
    rxFIFO0startAddr = flesa + lse * 8;
    rxFIFO1startAddr = rxFIFO0startAddr + rxFIFO0size * objSize[rxFIFO0ElemSize] * 4;
    rxBufStartAddr = rxFIFO1startAddr + rxFIFO1size * objSize[rxFIFO1ElemSize] * 4;
    txStartAddr = rxBufStartAddr + rxBufNum * objSize[rxBufElemSize] * 4;
    txEventFIFOStartAddr = txStartAddr + (txBufNum + txFIFOSize) * objSize[txBufElemSize] * 4;
}

function onChangeUseCalcStartingAddress(inst, ui)
{
    if(inst.useCalcStartingAddress){
        lss = inst.lss;
        lse = inst.lse;
        rxFIFO0size = inst.rxFIFO0size;
        rxFIFO1size = inst.rxFIFO1size;
        rxBufNum = inst.rxBufNum;
        txBufNum = inst.txBufNum;
        txFIFOSize = inst.txFIFOSize;
        rxFIFO0size = inst.rxFIFO0size;
        rxFIFO1size = inst.rxFIFO1size;
        rxFIFO0ElemSize = inst.rxFIFO0ElemSize;
        rxFIFO1ElemSize = inst.rxFIFO1ElemSize;
        rxBufElemSize = inst.rxBufElemSize;
        txBufElemSize = inst.txBufElemSize;
        calcStartingAddress();
        inst.flssa = flssa;
        inst.flesa = flesa;
        inst.rxFIFO0startAddr = rxFIFO0startAddr;
        inst.rxFIFO1startAddr = rxFIFO1startAddr;
        inst.rxBufStartAddr = rxBufStartAddr;
        inst.txStartAddr = txStartAddr;
        inst.txEventFIFOStartAddr = txEventFIFOStartAddr;
    }
        
}

let MCAN_InterruptFlags = [
        {name: "MCAN_INTR_MASK_ALL", displayName : "Enable All Interrupts "},
        {name: "MCAN_IR_RF0N_MASK", displayName : "Rx FIFO 0 New Message interrupt "},
        {name: "MCAN_IR_RF0W_MASK", displayName : "Rx FIFO 0 Watermark Reached interrupt"},
        {name: "MCAN_IR_RF0F_MASK", displayName : "Rx FIFO 0 Full interrupt"},
        {name: "MCAN_IR_RF0L_MASK", displayName : "Rx FIFO 0 Message Lost interrupt"},
        {name: "MCAN_IR_RF1N_MASK", displayName : "Rx FIFO 1 New Message interrupt "},
        {name: "MCAN_IR_RF1W_MASK", displayName : "Rx FIFO 1 Watermark Reached interrupt"},
        {name: "MCAN_IR_RF1F_MASK", displayName : "Rx FIFO 1 Full interrupt"},
        {name: "MCAN_IR_RF1L_MASK", displayName : "Rx FIFO 1 Message Lost interrupt"},
        {name: "MCAN_IR_HPM_MASK", displayName : "High Priority Message interrupt "},
        {name: "MCAN_IR_TC_MASK", displayName : "Transmission Completed interrupt"},
        {name: "MCAN_IR_TCF_MASK", displayName : "Transmission Cancellation Finished interrupt"},
        {name: "MCAN_IR_TFE_MASK", displayName : "Tx FIFO Empty interrupt"},
        {name: "MCAN_IR_TEFN_MASK", displayName : "Tx Event FIFO New Entry interrupt "},
        {name: "MCAN_IR_TEFW_MASK", displayName : "Tx Event FIFO Watermark Reached interrupt"},
        {name: "MCAN_IR_TEFF_MASK", displayName : "Tx Event FIFO Full interrupt"},
        {name: "MCAN_IR_TEFL_MASK", displayName : "Tx Event FIFO Element Lost interrupt"},
        {name: "MCAN_IR_TSW_MASK", displayName : "Timestamp Wraparound interrupt"},
        {name: "MCAN_IR_MRAF_MASK", displayName : "Message RAM Access Failure interrupt"},
        {name: "MCAN_IR_TOO_MASK", displayName : "Timeout Occurred interrupt"},
        {name: "MCAN_IR_DRX_MASK", displayName : "Message stored to Dedicated Rx Buffer interrupt "},
        {name: "MCAN_IR_BEC_MASK", displayName : "Bit Error Corrected interrupt"},
        {name: "MCAN_IR_BEU_MASK", displayName : "Bit Error Uncorrected interrupt"},
        {name: "MCAN_IR_ELO_MASK", displayName : "Error Logging Overflow interrupt"},
        {name: "MCAN_IR_EP_MASK", displayName : "Error Passive interrupt"},
        {name: "MCAN_IR_EW_MASK", displayName : "Warning Status interrupt"},
        {name: "MCAN_IR_BO_MASK", displayName : "Bus_Off Status interrupt "},
        {name: "MCAN_IR_WDI_MASK", displayName : "Watchdog Interrupt interrupt"},
        {name: "MCAN_IR_PEA_MASK", displayName : "Protocol Error in Arbitration Phase interrupt"},
        {name: "MCAN_IR_PED_MASK", displayName : "Protocol Error in Data Phase interrupt"},
        {name: "MCAN_IR_ARA_MASK", displayName : "Access to Reserved Address interrupt"},
];

let MCAN_elemSize = [
        {name: "0", displayName : "8 byte data field "},
        {name: "1", displayName : "12 byte data field "},
        {name: "2", displayName : "16 byte data field"},
        {name: "3", displayName : "20 byte data field"},
        {name: "4", displayName : "24 byte data field "},
        {name: "5", displayName : "32 byte data field "},
        {name: "6", displayName : "48 byte data field "},
        {name: "7", displayName : "64 byte data field"},
];

let MCAN_fifoOPMode = [
        {name: "0", displayName : "FIFO blocking mode "},
        {name: "1", displayName : "FIFO overwrite mode"},
];
/* Array of CAN configurables that are common across device families */
let config = [
    {
        name        : "fdMode",
        displayName : "Enable CAN FD Mode",
        description : 'Whether CAN flexible data mode to be enabled.',
        hidden      : false,
        default     : true,
    },
    {
        name        : "brsEnable",
        displayName : "Enable Bit Rate Switching",
        description : 'Whether Bit Rate Switching to be enabled.',
        hidden      : false,
        default     : true,
    },
    {
        name        : "loopbackMode",
        displayName : "Enable Loopback Mode",
        description : 'Enable Loopback Mode.',
        hidden      : false,
        default     : true,
    },
    {
        name        : "txpEnable",
        displayName : "Enable Transmit pause",
        description : 'Enable Transmit pause.',
        hidden      : false,
        default     : false,
    },
    {
        name        : "efbi",
        displayName : "Enable Edge filtering",
        description : 'Enable Edge filtering.',
        hidden      : false,
        default     : false,
    },
    {
        name        : "pxhddisable",
        displayName : "Enable Protocol exception handling",
        description : 'Enable Protocol exception handling',
        hidden      : false,
        default     : false,
    },
    {
        name        : "darEnable",
        displayName : "Disable Automatic retransmission of message",
        description : 'Disable Automatic retransmission of message.',
        hidden      : false,
        default     : false,
    },
    {
        name        : "wkupReqEnable",
        displayName : "Enable Wakeup request",
        description : 'Enable Wakeup request.',
        hidden      : false,
        default     : false,
    },
    {
        name        : "autoWkupEnable",
        displayName : "Enable Auto-Wakeup",
        description : 'Enable Auto-Wakeup.',
        hidden      : false,
        default     : false,
    },
    {
        name        : "emulationEnable",
        displayName : "Enable Emulation/Debug Suspend",
        description : 'Enable Emulation/Debug Suspend.',
        hidden      : false,
        default     : false,
    },
    {
        name: "GROUP_TDC",
        displayName: "Transmitter Delay Compensation",
        config: [
            {
                name        : "tdcEnable",
                displayName : "Enable Transmitter Delay Compensation",
                description : 'Enable Transmitter Delay Compensation.',
                hidden      : false,
                onChange    : onChangeUseTdc,
                default     : false,
            },
            {
                name        : "tdcConfig_tdcf",
                displayName : "Transmitter Delay Compensation Filter Window Length (CAN Module Clk Cycles)",
                description : 'Transmitter Delay Compensation Filter Window Length (CAN Module Clk Cycles).',
                hidden      : true,
                default     : 0xA,
            },
            {
                name        : "tdcConfig_tdco",
                displayName : "Transmitter Delay Compensation Offset (CAN Module Clk Cycles)",
                description : 'Transmitter Delay Compensation Offset (CAN Module Clk Cycles).',
                hidden      : true,
                default     : 0x6,
            },
        ]
    },
    {
        name        : "wdcPreload",
        displayName : "Message RAM Watchdog Counter preload Value",
        description : 'Message RAM Watchdog Counter preload Value.',
        hidden      : false,
        default     : 0xFF,
    },
    {
        name: "Bit Timing Parameters",
        displayName: "Bit Timing Parameters",
        longDescription : FileDescription + longDescriptionNomBitTimeParam + longDescriptionDataBitTimeParam,
        config: [
            {
                name: "canBitTimeFile",
                displayName: "MCAN Bit timing Calculator File",
                default: "C:/ti/c2000/C2000Ware_4_00_00_00/device_support/f2838x/docs/MCAN_BitTimingCalculator.xls",
                deprecated: true,
                //fileFilter: ".* ",
            },
            {
                name: "canBitTimeFileOpen",
                displayName: "Open MCAN Bit Timing Calculator",
                description : 'Open MCAN Bit Timing Calculator',
                buttonText: "Open",
                onLaunch: (inst) => {
                    var currnetSDKProductPath = system.getProducts()[0].path
                    var sdkPath = system.utils.path.join(currnetSDKProductPath + "../../../")
                    sdkPath = sdkPath.replace(new RegExp('\\' + system.utils.path.sep, 'g'), '/')
                    sdkPath = sdkPath + "device_support/f2838x/docs/MCAN_BitTimingCalculator.xls"
                    //console.log(sdkPath)
                    return ({
                        command: "../driverlib/.meta/mcan/mcanBitTimeCalc.bat",
                        args: [sdkPath],
                        initialData: "",
                    });
                },
                onComplete: (inst, ui, result) => {
                    return result;
                },
            },
            {
                name: "Nominal Bit Timing Parameters",
                displayName: "Nominal Bit Timing Parameters",
                longDescription : longDescriptionNomBitTimeParam,
                config: [
                    {
                        name        : "nomRatePrescalar",
                        displayName : "Nominal Baud Rate Pre-scaler (NBRP)",
                        description : 'Nominal Baud Rate Pre-scaler (NBRP)',
                        hidden      : false,
                        default     : 0x7,
                    },
                    {
                        name        : "nomTimeSeg1",
                        displayName : "Nominal Time segment before sample point (NTSEG1 Tq)",
                        description : 'Nominal Time segment before sample point (NTSEG1 Tq)',
                        hidden      : false,
                        default     : 0x4,
                    },
                    {
                        name        : "nomTimeSeg2",
                        displayName : "Nominal Time segment after sample point (NTSEG2 Tq)",
                        description : 'Nominal Time segment after sample point (NTSEG2 Tq)',
                        hidden      : false,
                        default     : 0x3,
                    },
                    {
                        name        : "nomSynchJumpWidth",
                        displayName : "Nominal (Re)Synchronization Jump Width Range (NSJW Tq)",
                        description : 'Nominal (Re)Synchronization Jump Width Range (NSJW Tq)',
                        hidden      : false,
                        default     : 0x3,
                    },
                ]
            },
            {
                name: "Data Bit Timing Parameters",
                displayName: "Data Bit Timing Parameters",
                longDescription : longDescriptionDataBitTimeParam,
                config: [
                    {
                        name        : "dataRatePrescalar",
                        displayName : "Data Baud Rate Pre-scaler (DBRP)",
                        description : 'Data Baud Rate Pre-scaler (DBRP)',
                        hidden      : false,
                        default     : 0x3,
                    },
                    {
                        name        : "dataTimeSeg1",
                        displayName : "Data Time segment before sample point (DTSEG1 Tq)",
                        description : 'Data Time segment before sample point (DTSEG1 Tq)',
                        hidden      : false,
                        default     : 0x4,
                    },
                    {
                        name        : "dataTimeSeg2",
                        displayName : "Data Time segment after sample point (DTSEG2 Tq)",
                        description : 'Data Time segment after sample point (DTSEG2 Tq)',
                        hidden      : false,
                        default     : 0x3,
                    },
                    {
                        name        : "dataSynchJumpWidth",
                        displayName : "Data (Re)Synchronization Jump Width (DSJW Tq)",
                        description : 'Data (Re)Synchronization Jump Width (DSJW Tq)',
                        hidden      : false,
                        default     : 0x3,
                    },
                ]
            },
        ]
    },
    {
        name: "GROUP_INT",
        displayName: "Interrupts",
        config: [
            {
                name        : "enableInterrupt",
                displayName : "Enable Interrupt",
                description : 'To Enable CAN Interrupts.',
                hidden      : false,
                onChange    : onChangeEnableInterrupt,
                default     : false,
            },
            {
                name        : "interruptFlags",
                displayName : "Enable Interrupts",
                description : 'Which Interrupts to enable.',
                hidden      : true,
                minSelections : 0,
                default     : [],
                options     : MCAN_InterruptFlags,
            },
            {
                name        : "interruptLine",
                displayName : "Enable Interrupt Line",
                description : 'Which Interrupts line to use.',
                hidden      : true,
                minSelections : 0,
                default     : [],
                options     : [
                    {name: "MCAN_INTR_LINE_NUM_0", displayName : "Enable MCAN interrupt line 0"},
                    {name: "MCAN_INTR_LINE_NUM_1", displayName : "Enable MCAN interrupt line 1"},
                ],

            },
            {
                name        : "interruptLine0Flag",
                displayName : "Interrupts to Trigger in Line0",
                description : 'Interrupts to Trigger in Line0.',
                hidden      : true,
                minSelections : 0,
                default     : [],
                options     : MCAN_InterruptFlags,

            },
            {
                name        : "interruptLine1Flag",
                displayName : "Interrupts to Trigger in Line1",
                description : 'Interrupts to Trigger in Line1.',
                hidden      : true,
                minSelections : 0,
                default     : [],
                options     : MCAN_InterruptFlags,

            },
            {
                name        : "registerInterruptLine0",
                displayName : "Register Interrupt Line0 Handler",
                description : 'Whether or not to register interrupt Line0 handlers in the interrupt module.',
                hidden      : false,
                default     : false
            },
            {
                name        : "registerInterruptLine1",
                displayName : "Register Interrupt Line1 Handler",
                description : 'Whether or not to register interrupt Line1 handlers in the interrupt module.',
                hidden      : false,
                default     : false
            },
        ]
    },
    {
        name: "GROUP_CORECONFIG",
        displayName: "Additional Core Configuration",
        config: [
            {
                name        : "additionalCoreConfig",
                displayName : "Enable Additional Core Configuration",
                description : 'Enable Additional Core Configuration.',
                hidden      : false,
                onChange    : onChangeUseAddCon,
                default     : false,
            },
            {
                name        : "monEnable",
                displayName : "Enable Bus Monitoring Mode",
                description : 'Enable Bus Monitoring Mode.',
                hidden      : true,
                default     : false,
            },
            {
                name        : "asmEnable",
                displayName : "Enable Restricted Operation Mode",
                description : 'Enable Restricted Operation Mode',
                hidden      : true,
                default     : false,
            },
            {
                name        : "tsPrescalar",
                displayName : "Time stamp Prescaler Value",
                description : 'Time stamp Prescaler Value.',
                hidden      : true,
                default     : 0xF,
            },
            {
                name        : "tsSelect",
                displayName : "Timestamp counter value",
                description : 'Timestamp counter value.',
                hidden      : true,
                default     : "0",
                options     : [
                    {name: "0", displayName : "Timestamp counter value always 0x0000"},
                    {name: "1", displayName : "Timestamp counter value incremented according to tsPrescalar"},
                    {name: "2", displayName : "External timestamp counter value used"},
                ],
            },
            {
                name        : "timeoutSelect",
                displayName : "Time-out counter source select",
                description : 'Time-out counter source select.',
                hidden      : true,
                default     : "MCAN_TIMEOUT_SELECT_CONT",
                options     : [
                    {name: "MCAN_TIMEOUT_SELECT_CONT", displayName : "Continuous operation Mode"},
                    {name: "MCAN_TIMEOUT_SELECT_TX_EVENT_FIFO", displayName : "Timeout controlled by Tx Event FIFO"},
                    {name: "MCAN_TIMEOUT_SELECT_RX_FIFO0", displayName : "Timeout controlled by Rx FIFO 0"},
                    {name: "MCAN_TIMEOUT_SELECT_RX_FIFO1", displayName : "Timeout controlled by Rx FIFO 1"},
                ],
            },
            {
                name        : "timeoutPreload",
                displayName : "Start value of the Timeout Counter",
                description : 'Start value of the Timeout Counter.',
                hidden      : true,
                default     : 0xFFFF,
            },
            {
                name        : "timeoutCntEnable",
                displayName : "Enable Time-out Counter",
                description : 'Enable Time-out Counter.',
                hidden      : true,
                default     : false,
            },
            {
                name        : "rrfe",
                displayName : "Reject Remote Frames Extended",
                description : 'Reject Remote Frames Extended.',
                hidden      : true,
                default     : false,
            },
            {
                name        : "rrfs",
                displayName : "Reject Remote Frames Standard",
                description : 'Reject Remote Frames Standard.',
                hidden      : true,
                default     : false,
            },
            {
                name        : "anfe",
                displayName : "Accept Non-matching Frames Extended",
                description : 'Accept Non-matching Frames Extended.',
                hidden      : true,
                default     : "0",
                options     : [
                    {name: "0", displayName : "Accept in Rx FIFO 0"},
                    {name: "1", displayName : "Accept in Rx FIFO 1"},
                    {name: "2", displayName : "Reject"},
                ],
            },
            {
                name        : "anfs",
                displayName : "Accept Non-matching Frames Standard",
                description : 'Accept Non-matching Frames Standard.',
                hidden      : true,
                default     : "0",
                options     : [
                    {name: "0", displayName : "Accept in Rx FIFO 0"},
                    {name: "1", displayName : "Accept in Rx FIFO 1"},
                    {name: "2", displayName : "Reject"},
                ],
            },
        ]
    },
    {
        name: "GROUP_MSGRAMCONFIG",
        displayName: "Message RAM Configuration",
        longDescription: "These parameters configure the MCAN Message RAM for multiple sections. Make sure that none of the sections are overlapping by comparing their start address and end address with each other.",
        config: [
            {
                name        : "msgRamConfig",
                displayName : "Enable Message RAM Configuration",
                description : 'Enable Message RAM Configuration.',
                hidden      : true,
                onChange    : onChangeMsgRamConfig,
                default     : true,
            },
            {
                name        : "useCalcStartingAddress",
                displayName : "Use Calculated Starting Addresses",
                description : 'Use Calculated Starting Addresses',
                hidden      : false,
                onChange    : onChangeUseCalcStartingAddress,
                default     : false,
            },
            {
                name        : "flssa",
                displayName : "Standard ID Filter List Start Address",
                description : 'Standard ID Filter List Start Address.',
                hidden      : false,
                default     : 0x0,
            },
            {
                name        : "lss",
                displayName : "No of Standard ID Filters",
                description : 'No of Standard ID Filters.',
                hidden      : false,
                default     : 0x1,
            },
            {
                name        : "flesa",
                displayName : "Extended ID Filter List Start Address",
                description : 'Extended ID Filter List Start Address.',
                hidden      : false,
                default     : 48,
            },
            {
                name        : "lse",
                displayName : "No of Extended ID Filters",
                description : 'No of Extended ID Filters.',
                hidden      : false,
                default     : 1,
            },
            {
                name: "GROUP_MSGRAMCONFIG_TX",
                displayName: "TX MSG RAM",
                config : [
                    {
                        name        : "txStartAddr",
                        displayName : "Tx Buffers Start Address",
                        description : 'Tx Buffers Start Address.',
                        hidden      : false,
                        default     : 148,
                    },
                    {
                        name        : "txBufNum",
                        displayName : "Number of Dedicated Transmit Buffers",
                        description : 'Number of Dedicated Transmit Buffers.',
                        hidden      : false,
                        default     : 0,
                    },
                    {
                        name        : "txFIFOSize",
                        displayName : "No of Tx FIFO / Tx Queue Elements",
                        description : 'No of Tx FIFO / Tx Queue Elements.',
                        hidden      : false,
                        default     : 0,
                    },
                    {
                        name        : "txBufMode",
                        displayName : "Tx FIFO operation Mode",
                        description : 'Tx FIFO operation Mode.',
                        hidden      : false,
                        default     : "0",
                        options     : [
                            {name: "0", displayName : "Tx FIFO operation"},
                            {name: "1", displayName : "Tx Queue operation"},
                        ],
                    },
                    {
                        name        : "txBufElemSize",
                        displayName : "Tx Buffer Element Size",
                        description : 'Tx Buffer Element Size.',
                        hidden      : false,
                        default     : MCAN_elemSize[7].name,
                        options     : MCAN_elemSize,
                    },
                    {
                        name        : "txEventFIFOStartAddr",
                        displayName : "Tx Event FIFO Start Address",
                        description : 'Tx Event FIFO Start Address.',
                        hidden      : false,
                        default     : 0xFF,
                    },
                    {
                        name        : "txEventFIFOSize",
                        displayName : "Tx Event FIFO Size",
                        description : 'Tx Event FIFO Size.',
                        hidden      : false,
                        default     : 0,
                    },
                    {
                        name        : "txEventFIFOWaterMark",
                        displayName : "Level for Tx Event FIFO watermark interrupt",
                        description : 'Level for Tx Event FIFO watermark interrupt.',
                        hidden      : false,
                        default     : 0,
                    },
                ]
            },
            {
                name: "GROUP_MSGRAMCONFIG_RX",
                displayName: "RX MSG RAM",
                config : [
                    {
                        name        : "rxFIFO0startAddr",
                        displayName : "Rx FIFO0 Start Address",
                        description : 'Rx FIFO0 Start Address.',
                        hidden      : false,
                        default     : 548,
                    },
                    {
                        name        : "rxFIFO0size",
                        displayName : "Number of Rx FIFO0 elements",
                        description : 'Number of Rx FIFO0 elements.',
                        hidden      : false,
                        default     : 0,
                    },
                    {
                        name        : "rxFIFO0waterMark",
                        displayName : "Rx FIFO0 Watermark",
                        description : 'Rx FIFO0 Watermark.',
                        hidden      : false,
                        default     : 0,
                    },
                    {
                        name        : "rxFIFO0OpMode",
                        displayName : "FIFO0 operation mode",
                        description : 'FIFO0 operation mode.',
                        hidden      : false,
                        default     : MCAN_fifoOPMode[0].name,
                        options     : MCAN_fifoOPMode,
                    },
                    {
                        name        : "rxFIFO1startAddr",
                        displayName : "Rx FIFO1 Start Address",
                        description : 'Rx FIFO1 Start Address.',
                        hidden      : false,
                        default     : 748,
                    },
                    {
                        name        : "rxFIFO1size",
                        displayName : "Number of Rx FIFO1 elements",
                        description : 'Number of Rx FIFO1 elements.',
                        hidden      : false,
                        default     : 0,
                    },
                    {
                        name        : "rxFIFO1waterMark",
                        displayName : "Rx FIFO1 Watermark",
                        description : 'Rx FIFO1 Watermark.',
                        hidden      : false,
                        default     : 0,
                    },
                    {
                        name        : "rxFIFO1OpMode",
                        displayName : "FIFO1 operation mode",
                        description : 'FIFO1 operation mode.',
                        hidden      : false,
                        default     : MCAN_fifoOPMode[0].name,
                        options     : MCAN_fifoOPMode,
                    },
                    {
                        name        : "rxBufStartAddr",
                        displayName : "Rx Buffer Start Address",
                        description : 'Rx Buffer Start Address.',
                        hidden      : false,
                        default     : 948,
                    },
                    {
                        name        : "rxBufNum",
                        displayName : "Rx Buffer Size (number of elements)",
                        description : 'Rx Buffer Size (number of elements)',
                        hidden      : false,
                        default     : 0,
                    },
                    {
                        name        : "rxBufElemSize",
                        displayName : "Rx Buffer Element Size",
                        description : 'Rx Buffer Element Size.',
                        hidden      : false,
                        default     : MCAN_elemSize[7].name,
                        options     : MCAN_elemSize,
                    },
                    {
                        name        : "rxFIFO0ElemSize",
                        displayName : "Rx FIFO0 Element Size",
                        description : 'Rx FIFO0 Element Size.',
                        hidden      : false,
                        default     : MCAN_elemSize[7].name,
                        options     : MCAN_elemSize,
                    },
                    {
                        name        : "rxFIFO1ElemSize",
                        displayName : "Rx FIFO1 Element Size",
                        description : 'Rx FIFO1 Element Size.',
                        hidden      : false,
                        default     : MCAN_elemSize[7].name,
                        options     : MCAN_elemSize,
                    },
                ]
            },

        ]
    },
    {
        name        : "stdFilts",
        displayName : "Standard Filter Elements",
        description : 'Standard Filter Elements need to be configured',
        hidden      : false,
        default     : 0,
        onChange    : (inst, ui) => {
            var convertedArray = []
            for (var mO = 1; mO <= inst["stdFilts"]; mO++)
            {
                convertedArray.push(mO);
            }
            inst["stdFiltsUsed"] = convertedArray;
        }
    },
    {
        name        : "stdFiltsUsed",
        displayName : "Standard Filter Elements used (0-127)",
        description : 'Standard Filter Elements need to be configured',
        hidden      : false,
        minSelections : 0,
        default     : [],
        options     : stdFiltCountConfig
    },
    {
        name: "useCase",
        displayName : "PinMux Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("MCAN"),
        onChange    : Pinmux.useCaseChanged,

    },
];

function moduleInstances(inst,ui) {
    var components = []

    var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("MCAN", inst)
    for (var pinmuxQualMod of pinmuxQualMods)
    {
        pinmuxQualMod.requiredArgs = {
          qualMode : "GPIO_QUAL_ASYNC",
        }
    }
    components = components.concat(pinmuxQualMods)

    for(var i in inst.stdFiltsUsed)
    {
        components = components.concat([
        {
            moduleName : "/driverlib/mcanStdFilt.js",
            name : "stdFilt"+inst.stdFiltsUsed[i],
            displayName: "Standard Filter Element "+inst.stdFiltsUsed[i],
            collapsed : true,
        },
        ]);
    }

    if (inst.registerInterruptLine0)
    {
        components = components.concat([(
            {
                name: "mcanInt0",
                displayName: "MCAN Interrupt0",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_INT0",
                    int : "INT_" + inst.$name + "_0",
                    pinmuxPeripheralModule : "mcan",
                    driverlibInt: Line0IntName
                  }
            }
        )])
    }
    if (inst.registerInterruptLine1)
    {
        components = components.concat([(
            {
                name: "mcanInt1",
                displayName: "MCAN Interrupt1",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                    $name : inst.$name + "_INT1",
                    int : "INT_" + inst.$name + "_1",
                    pinmuxPeripheralModule : "mcan",
                    driverlibInt: Line1IntName
                }
            }
        )])
    }
    return components;
}

function onValidate(inst, validation) {
    if (inst.tdcConfig_tdcf < 0 || inst.tdcConfig_tdcf > 0x7F)
    {
        validation.logError(
            "The TDC Filter Window Length must be between 0x0-0x7F",
            inst, "tdcConfig_tdcf");
    }
    if (inst.tdcConfig_tdco < 0 || inst.tdcConfig_tdco > 0x7F)
    {
        validation.logError(
            "The TDC Offset must be between 0x0-0x7F",
            inst, "tdcConfig_tdco");
    }
    if (inst.wdcPreload < 0 || inst.wdcPreload > 0xFF)
    {
        validation.logError(
            "Message RAM Watchdog Counter preload Value must be between 0x0-0xFF",
            inst, "wdcPreload");
    }
    if (inst.nomRatePrescalar < 0 || inst.nomRatePrescalar > 0x1FF)
    {
        validation.logError(
            "Nominal Baud Rate Pre-scaler must be between 0x0-0x1FF",
            inst, "nomRatePrescalar");
    }
    if (inst.nomTimeSeg1 < 0 || inst.nomTimeSeg1 > 0xFF)
    {
        validation.logError(
            "Nominal Time segment before sample point must be between 0x0-0xFF",
            inst, "nomTimeSeg1");
    }
    if (inst.nomTimeSeg2 < 0 || inst.nomTimeSeg2 > 0x7F)
    {
        validation.logError(
            "Nominal Time segment after sample point must be between 0x0-0x7F",
            inst, "nomTimeSeg2");
    }
    if (inst.nomSynchJumpWidth < 0 || inst.nomSynchJumpWidth > 0x7F)
    {
        validation.logError(
            "Nominal (Re)Synchronization Jump Width Range must be between 0x0-0x7F",
            inst, "nomSynchJumpWidth");
    }
    if (inst.dataRatePrescalar < 0 || inst.dataRatePrescalar > 0x1F)
    {
        validation.logError(
            "Data Baud Rate Pre-scaler must be between 0x0-0x1F",
            inst, "dataRatePrescalar");
    }
    if (inst.dataTimeSeg1 < 0 || inst.dataTimeSeg1 > 0x1F)
    {
        validation.logError(
            "Data Time segment before sample point must be between 0x0-0x1F",
            inst, "dataTimeSeg1");
    }
    if (inst.dataTimeSeg2 < 0 || inst.dataTimeSeg2 > 0xF)
    {
        validation.logError(
            "Data Time segment after sample point must be between 0x0-0xF",
            inst, "dataTimeSeg2");
    }
    if (inst.dataSynchJumpWidth < 0 || inst.dataSynchJumpWidth > 0xF)
    {
        validation.logError(
            "Data (Re)Synchronization Jump Width must be between 0x0-0xF",
            inst, "dataSynchJumpWidth");
    }
    if (inst.tsPrescalar < 0 || inst.tsPrescalar > 0xF)
    {
        validation.logError(
            "Time stamp Prescaler Value must be between 0x0-0xF",
            inst, "tsPrescalar");
    }
    if (inst.timeoutPreload < 0 || inst.timeoutPreload > 0xFFFF)
    {
        validation.logError(
            "Start value of the Timeout Counter must be between 0x0-0xFFFF",
            inst, "timeoutPreload");
    }
    if (String(inst.interruptFlags).includes("MCAN_INTR_MASK_ALL"))
    {
        if(inst.interruptFlags.length > 1)
        {
            validation.logWarning(
            "Enable All Interrupts is marked, other flags are redundant",
            inst, "interruptFlags");
        }
    }
    if (String(inst.interruptLine0Flag).includes("MCAN_INTR_MASK_ALL"))
    {
        if(inst.interruptLine0Flag.length > 1)
        {
            validation.logWarning(
            "Enable All Interrupts is marked, other flags are redundant",
            inst, "interruptLine0Flag");
        }
    }
    if (String(inst.interruptLine1Flag).includes("MCAN_INTR_MASK_ALL"))
    {
        if(inst.interruptLine1Flag.length > 1)
        {
            validation.logWarning(
            "Enable All Interrupts is marked, other flags are redundant",
            inst, "interruptLine1Flag");
        }
    }
    if (["F2838x"].includes(Common.getDeviceName())){
        if (inst.flssa < 0 || inst.flssa > 4352)
        {
            validation.logError(
                "Standard ID Filter List Start Address must be between 0 and 4352",
                inst, "flssa");
        }
        if (inst.lss < 0 || inst.lss > 128)
        {
            validation.logError(
                "No of Standard ID Filters must be between 0 and 128",
                inst, "lss");
        }
        if (inst.flesa < 0 || inst.flesa > 4352)
        {
            validation.logError(
                "Extended ID Filter List Start Address must be between 0 and 4352",
                inst, "flesa");
        }
        if (inst.lse < 0 || inst.lse > 64)
        {
            validation.logError(
                "No of Extended ID Filters must be between 0 and 64",
                inst, "lse");
        }
        if (inst.txStartAddr < 0 || inst.txStartAddr > 4352)
        {
            validation.logError(
                "Tx Buffers Start Address must be between 0 and 4352",
                inst, "txStartAddr");
        }
        if (inst.txBufNum < 0 || inst.txBufNum > 32)
        {
            validation.logError(
                "Number of Dedicated Transmit Buffers must be between 0 and 32",
                inst, "txBufNum");
        }
        if (inst.txFIFOSize < 0 || inst.txFIFOSize > 64)
        {
            validation.logError(
                "No of Tx FIFO Elements must be between 0 and 32",
                inst, "txFIFOSize");
        }
        if (inst.txEventFIFOSize < 0 || inst.txEventFIFOSize > 32)
        {
            validation.logError(
                "Tx Event FIFO Size must be between 0 and 32",
                inst, "txEventFIFOSize");
        }
        if (inst.rxFIFO0startAddr < 0 || inst.rxFIFO0startAddr > 4352)
        {
            validation.logError(
                "Rx FIFO0 Start Address must be between 0 and 4352",
                inst, "rxFIFO0startAddr");
        }
        if (inst.rxFIFO0size < 0 || inst.rxFIFO0size > 64)
        {
            validation.logError(
                "Number of Rx FIFO0 elements must be between 0 and 64",
                inst, "rxFIFO0size");
        }
        if (inst.rxFIFO1startAddr < 0 || inst.rxFIFO1startAddr > 4352)
        {
            validation.logError(
                "Rx FIFO1 Start Address must be between 0 and 4352",
                inst, "rxFIFO1startAddr");
        }
        if (inst.rxFIFO1size < 0 || inst.rxFIFO1size > 64)
        {
            validation.logError(
                "Number of Rx FIFO1 elements must be between 0 and 64",
                inst, "rxFIFO1size");
        }
        if (inst.rxFIFO0waterMark < 0 || inst.rxFIFO0waterMark > 64)
        {
            validation.logError(
                "Rx FIFO0 Watermark must be between 0 and 64",
                inst, "rxFIFO0waterMark");
        }
        if (inst.rxFIFO1waterMark < 0 || inst.rxFIFO1waterMark > 64)
        {
            validation.logError(
                "Rx FIFO1 Watermark must be between 0 and 64",
                inst, "rxFIFO1waterMark");
        }
        if (inst.rxBufStartAddr < 0 || inst.rxBufStartAddr > 4352)
        {
            validation.logError(
                "Rx Buffer Start Address must be between 0 and 4352",
                inst, "rxBufStartAddr");
        }
    }
    validation.logInfo("Recheck the box after ALL Message RAM Configuration related changes have been made ", inst, "useCalcStartingAddress");

    if(inst.txBufNum + inst.txFIFOSize > 32)
    {
        validation.logError(
            "Sum of TX Buffers and TX FIFO size must be between 0 and 32",
            inst, "txFIFOSize");
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
    return (Common.typeMatches(component.type, ["MCAN"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var mcanModule = {
    peripheralName: "MCAN",
    displayName: "MCAN",
    maxInstances: Common.peripheralCount("MCAN"),
    defaultInstanceName: "myMCAN",
    description: "MCAN Peripheral",
    longDescription: (Common.getCollateralFindabilityList("MCAN")),
    filterHardware : filterHardware,
    config: config,
    validate: onValidate,
    moduleInstances: moduleInstances,
    validate    : onValidate,
    templates: {
        boardc : "/driverlib/mcan/mcan.board.c.xdt",
        boardh : "/driverlib/mcan/mcan.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.mcanPinmuxRequirements
};


if (mcanModule.maxInstances <= 0)
{
    delete mcanModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(mcanModule)
    Pinmux.addPinMuxQualGroupToConfig(mcanModule)
}

exports = mcanModule;
