let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_lin.js");


let list1to8 = [
    {name:1},
    {name:2},
    {name:3},
    {name:4},
    {name:5},
    {name:6},
    {name:7},
    {name:8},
]

function is_hexadecimal(str)
{
    let regexp = /^[0-9a-fA-F]+$/;
    if (regexp.test(str)) return true;
    else return false;
}

var linAClk = Common.getSYSCLK(), linBClk = Common.getSYSCLK()
var linADivider = 1, linBDivider = 1

let newLINClockDividers = ["F28P55x"/*, "F28P65x"*/];  //add F28P65x once clock tree is modified
let LIN2_Instances = ["F28P65x", "F28002x", "F28003x"];
var linDividers = newLINClockDividers.includes(Common.getDeviceName())
var linBexists = LIN2_Instances.includes(Common.getDeviceName())
let clocktree = Common.getClockTree()

if(clocktree){
    if (linDividers){
        linAClk = clocktree["LINACLKDIV"].in
        linADivider = clocktree["LINACLKDIV"].divideValue
        if(linBexists){
            linBClk = clocktree["LINBCLKDIV"].in
            linBDivider = clocktree["LINBCLKDIV"].divideValue
        }
        else{ 
            //will be hidden
            linBClk = 0
            linBDivider = 0
        }
    }
    else{
        if(clocktree){
            linAClk = clocktree["PERx_SYSCLK_domain"].in
            linBClk = clocktree["PERx_SYSCLK_domain"].in
        }
        else{
            linAClk = Common.getSYSCLK()
            linBClk = Common.getSYSCLK() 
        }

        //will be hidden
        linADivider = 0 
        linBDivider = 0
    }
}


/* Intro splash on GUI */
let longDescription = "LIN is a low cost communication peripheral which" +
    "can be used in place of CAN where performance can be traded off for cost. " +
    "This application provides a simplified interface to configure the different " + 
    "parameters of the peripheral such as LIN/SCI mode, Commander/Responder Mode " + 
    "and test mode etc. ";

function onChangeUseLoopback(inst, ui)
{
    if (inst.enableLoopback) {
        ui.loopbackMode.hidden = false;
        if(inst.loopbackMode == "LIN_TEST_EXTERNAL"){
            ui.loopbackType.hidden = false;
            if(inst.loopbackType = "LIN_LOOPBACK_ANALOG"){
                ui.analogLoopbackPath.hidden = false;
            }
        }
    }
    else {
        ui.loopbackMode.hidden = true;
        ui.loopbackType.hidden = true;
        ui.analogLoopbackPath.hidden = true;
    }
}
function onChangeUseLoopbackMode(inst, ui)
{
    if (inst.enableLoopback && (inst.loopbackMode == "LIN_TEST_EXTERNAL")) {
        ui.loopbackType.hidden = false;
        if(inst.loopbackType = "LIN_LOOPBACK_ANALOG"){
            ui.analogLoopbackPath.hidden = false;
        }
    }
    else {
        ui.loopbackType.hidden = true;
        ui.analogLoopbackPath.hidden = true;
    }
}
function onChangeLinMode(inst, ui)
{
    if (inst.linMode == "LIN_MODE_LIN_RESPONDER") {
        ui.setResponderID.hidden = false;
        ui.autoBaudRate.hidden = false
    }
    else {
        ui.autoBaudRate.hidden = true
        ui.setResponderID.hidden = true;
    }
    onChangeAutoBaud(inst, ui)
    onChangeSetResponderID(inst, ui);
}
function onChangeSetResponderID(inst, ui)
{
    if (inst.linMode == "LIN_MODE_LIN_RESPONDER" && inst.setResponderID) {
        ui.responderIdByte.hidden = false;
    }
    else {
        ui.responderIdByte.hidden = true;
    }
}
function onChangeAutoBaud(inst, ui)
{
    if (inst.opMode == "LIN" && inst.autoBaudRate && inst.linMode == "LIN_MODE_LIN_RESPONDER") {
        ui.mbrVal.hidden = false;
        ui.mbrValActual.hidden = false;
        ui.mbrValErr.hidden = false;
        ui.mbrPrescaler.hidden = false;
        ui.brVal.hidden = true;
        ui.brValActual.hidden = true;
        ui.brValErr.hidden = true;
        ui.brPrescaler.hidden = true;
        ui.brDivider.hidden = true;
    }
    else {
        ui.mbrVal.hidden = true;
        ui.mbrValActual.hidden = true;
        ui.mbrValErr.hidden = true;
        ui.mbrPrescaler.hidden = true;
        ui.brVal.hidden = false;
        ui.brValActual.hidden = false;
        ui.brValErr.hidden = false;
        ui.brPrescaler.hidden = false;
        ui.brDivider.hidden = false;
    }
}
function onChangeUseLoopbackType(inst, ui)
{
    if (inst.enableLoopback && (inst.loopbackType == "LIN_LOOPBACK_ANALOG")) {
        ui.analogLoopbackPath.hidden = false;
    }
    else {
        ui.analogLoopbackPath.hidden = true;
    }
}
function toggleInterrupt(inst, ui){
    inst.registerL0Int = false;
    inst.registerL1Int = false;

    if(inst.enableInterrupt){
        if(inst.opMode == "LIN"){
            ui.interruptFlags.hidden = false;
            ui.interruptLine.hidden = false;

            ui.sciInterruptFlags.hidden = true;
            ui.sciInterruptLine.hidden = true;
            ui.sciInterruptPriorityLine0.hidden = true;
            ui.sciInterruptPriorityLine1.hidden = true;
            if (inst.interruptLine.indexOf(device_driverlib_peripheral.LIN_InterruptLine[0].name) != -1) 
            {
                ui.interruptPriorityLine0.hidden = false;
                ui.registerL0Int.hidden = false;
            }
            else
            {
                ui.interruptPriorityLine0.hidden = true;
                ui.registerL0Int.hidden = true;
            }
            if (inst.interruptLine.indexOf(device_driverlib_peripheral.LIN_InterruptLine[1].name) != -1) 
            {
                ui.interruptPriorityLine1.hidden = false;
                ui.registerL1Int.hidden = false;
            }
            else
            {
                ui.interruptPriorityLine1.hidden = true;
                ui.registerL1Int.hidden = true;
            }
        }
        else{
            ui.sciInterruptFlags.hidden = false;
            ui.sciInterruptLine.hidden = false;

            ui.interruptFlags.hidden = true;
            ui.interruptLine.hidden = true;
            ui.interruptPriorityLine0.hidden = true;
            ui.interruptPriorityLine1.hidden = true;

            if (inst.sciInterruptLine.indexOf(device_driverlib_peripheral.LIN_InterruptLine[0].name) != -1) 
            {
                ui.sciInterruptPriorityLine0.hidden = false;
                ui.registerL0Int.hidden = false;
            }
            else
            {
                ui.sciInterruptPriorityLine0.hidden = true;
                ui.registerL0Int.hidden = true;
            }
            if (inst.sciInterruptLine.indexOf(device_driverlib_peripheral.LIN_InterruptLine[1].name) != -1) 
            {
                ui.sciInterruptPriorityLine1.hidden = false;
                ui.registerL1Int.hidden = false;
            }
            else
            {
                ui.sciInterruptPriorityLine1.hidden = true;
                ui.registerL1Int.hidden = true;
            }
        }
    }
    else{
        ui.interruptFlags.hidden = true;
        ui.interruptLine.hidden = true;
        ui.interruptPriorityLine0.hidden = true;
        ui.interruptPriorityLine1.hidden = true;
        ui.sciInterruptFlags.hidden = true;
        ui.sciInterruptLine.hidden = true;
        ui.sciInterruptPriorityLine0.hidden = true;
        ui.sciInterruptPriorityLine1.hidden = true;
        ui.registerL0Int.hidden = true;
        ui.registerL1Int.hidden = true;
    }
}
function onChangeOpMode(inst, ui)
{
    if (inst.opMode == "LIN") { //LIN Mode
        ui.linMode.hidden = false;
        if(inst.linMode == "LIN_MODE_LIN_RESPONDER"){
            ui.setResponderID.hidden = false;
            ui.autoBaudRate.hidden = false;
            if(inst.setResponderID)
                ui.responderIdByte.hidden = false;
        }
        else{
            ui.setResponderID.hidden = true;
            ui.responderIdByte.hidden = true;
            ui.autoBaudRate.hidden = true;  // LIN commander mode, don't show autobaud option
        }
        ui.linCommMode.hidden = false;
        ui.linDebugMode.hidden = false;
        ui.linChecksumType.hidden = false;
        ui.linMessageFilter.hidden = false;
        ui.enableMultibuffer.hidden = false;
        inst.enableMultibuffer = true;
        ui.enableParity.hidden = false;
        if (inst.autoBaudRate && inst.linMode == "LIN_MODE_LIN_RESPONDER") {
            ui.mbrVal.hidden = false;
            ui.mbrValActual.hidden = false;
            ui.mbrValErr.hidden = false;
            ui.mbrPrescaler.hidden = false;
            ui.brVal.hidden = true;
            ui.brValActual.hidden = true;
            ui.brValErr.hidden = true;
            ui.brPrescaler.hidden = true;
            ui.brDivider.hidden = true;
        }
        else {  
            ui.mbrVal.hidden = true;
            ui.mbrValActual.hidden = true;
            ui.mbrValErr.hidden = true;
            ui.mbrPrescaler.hidden = true;
            ui.brVal.hidden = false;
            ui.brValActual.hidden = false;
            ui.brValErr.hidden = false;
            ui.brPrescaler.hidden = false;
            ui.brDivider.hidden = false;
        }
        ui.linFrameLength.hidden = false;
        ui.syncBreak.hidden = false;
        ui.delimiter.hidden = false;
        ui.txMask.hidden = false;
        ui.rxMask.hidden = false;
        ui.sciCommMode.hidden = true;
        ui.sleepMode.hidden = true;
        ui.sciStopBits.hidden = true;
        ui.enableSCIParity.hidden = true;
        ui.sciFrameLength.hidden = true;
        ui.sciCharLength.hidden = true;
    }
    else {      //SCI Mode
        ui.linMode.hidden = true;
        ui.setResponderID.hidden = true;
        ui.responderIdByte.hidden = true;
        ui.linCommMode.hidden = true;
        ui.linDebugMode.hidden = false;
        ui.linChecksumType.hidden = true;
        ui.linMessageFilter.hidden = true;
        ui.enableParity.hidden = true;
        ui.mbrVal.hidden = true;
        ui.mbrValActual.hidden = true;
        ui.mbrValErr.hidden = true;
        ui.mbrPrescaler.hidden = true;
        ui.brVal.hidden = false;
        ui.brValActual.hidden = false;
        ui.brValErr.hidden = false;
        ui.brPrescaler.hidden = false;
        ui.brDivider.hidden = false;
        ui.linFrameLength.hidden = true;
        ui.syncBreak.hidden = true;
        ui.delimiter.hidden = true;
        ui.txMask.hidden = true;
        ui.rxMask.hidden = true;
        ui.sciCommMode.hidden = false;
        ui.sleepMode.hidden = false;
        ui.sciStopBits.hidden = false;
        ui.enableMultibuffer.hidden = false;
        inst.enableMultibuffer = false;
        ui.autoBaudRate.hidden = true;
        ui.enableSCIParity.hidden = false;
        ui.sciFrameLength.hidden = false;
        ui.sciCharLength.hidden = false;
    }
    toggleInterrupt(inst, ui);
}
function onChangeRegisterInterrupts(inst, ui){
    if(inst.enableInterrupt && inst.registerInterrupts){
        inst.registerL0Int = true;
        inst.registerL1Int = true;
        ui.registerL0Int.hidden = false;
        ui.registerL1Int.hidden = false;
    }
    else{
        inst.registerL0Int = false;
        inst.registerL1Int = false;
        ui.registerL0Int.hidden = true;
        ui.registerL1Int.hidden = true;
    }
}


function onChangeEnableInterrupt(inst, ui)
{
    if (inst.enableInterrupt) {
        ui.interruptFlags.hidden = false;
        ui.interruptLine.hidden = false;
        ui.interruptPriorityLine0.hidden = false;
        ui.interruptPriorityLine1.hidden = false;
    }
    else {
        ui.interruptFlags.hidden = true;
        ui.interruptLine.hidden = true;
        ui.interruptPriorityLine0.hidden = true;
        ui.interruptPriorityLine1.hidden = true;
    }
}

function getUpdatedLINClock(inst){
    let linClock = Common.getSYSCLK();
    let clocktree = Common.getClockTree()
    if(clocktree){
        if(linDividers){
            if(!linBexists){
                linClock = (clocktree["LINACLK"].in)*1000000
            }
            else{
                linClock = (clocktree[inst.lin.$solution.peripheralName+"CLK"].in)*1000000
            }
        }
        else{
            linClock = (clocktree["PERx_SYSCLK_domain"].in)*1000000
        }
    }

    return linClock;
}

let LIN_InterruptFlags = [
    {name: " LIN_INT_WAKEUP", displayName : " Wakeup "},
    {name: " LIN_INT_TO", displayName : " Time out "},
    {name: " LIN_INT_TOAWUS", displayName : " Time out after wakeup signal "},
    {name: " LIN_INT_TOA3WUS", displayName : " Time out after 3 wakeup signals "},
    {name: " LIN_INT_TX", displayName : " Transmit buffer ready "},
    {name: " LIN_INT_RX", displayName : " Receive buffer ready "},
    {name: " LIN_INT_ID", displayName : " Received matching identifier "},
    {name: " LIN_INT_PE", displayName : " Parity error "},
    {name: " LIN_INT_OE", displayName : " Overrun error "},
    {name: " LIN_INT_FE", displayName : " Framing error "},
    {name: " LIN_INT_NRE", displayName : " No response error "},
    {name: " LIN_INT_ISFE", displayName : " Inconsistent sync field error "},
    {name: " LIN_INT_CE", displayName : " Checksum error "},
    {name: " LIN_INT_PBE", displayName : " Physical bus error "},
    {name: " LIN_INT_BE", displayName : " Bit error "},
    {name: " LIN_INT_ALL", displayName : " All interrupts "},
];
/* Array of CAN configurables that are common across device families */
let config = [
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
        {
            name: "opMode",
            displayName : "Protocol",
            description : 'Whether to communicate using a LIN protocol or a UART protocol. Choosing LIN will put the module in LIN mode and choosing UART will put the module in SCI mode.',
            hidden      : false,
            default     : 'LIN',
            options     : [
                {name: "LIN", displayName : "LIN (LIN Mode)"},
                {name: "SCI", displayName : "UART (SCI Mode)"},
            ],
            onChange    : onChangeOpMode,
            
        },
        {
            name        : "enableLoopback",
            displayName : "Enable Loopback",
            description : 'Whether loopback mode to be enabled.',
            hidden      : false,
            onChange    : onChangeUseLoopback,
            default     : false,
        },
        {
            name        : "loopbackMode",
            displayName : "Loopback Mode ",
            description : 'Whether to enable Loopback Mode.',
            hidden      : true,
            onChange    : onChangeUseLoopbackMode,
            default     : "LIN_TEST_INTERNAL",
            options     : [
                {name: "LIN_TEST_INTERNAL", displayName : "Internal Loopback Mode"},
                {name: "LIN_TEST_EXTERNAL", displayName : "External Loopback Mode"},
            ],
        },
        {
            name        : "loopbackType",
            displayName : "Type of LoopBack",
            description : 'Type of LoopBack.',
            onChange    : onChangeUseLoopbackType,
            hidden      : true,
            default     : device_driverlib_peripheral.LIN_LoopbackType[0].name,
            options     : device_driverlib_peripheral.LIN_LoopbackType,
        },
        {
            name        : "analogLoopbackPath",
            displayName : "Loopback path in Analog loopback",
            description : 'Loopback path in Analog loopback.',
            hidden      : true,
            default     : device_driverlib_peripheral.LIN_AnalogLoopback[0].name,
            options     : device_driverlib_peripheral.LIN_AnalogLoopback,
        },
        {
            name        : "linMode",
            displayName : "LIN Mode ",
            description : 'Whether the node is a commander or responder.',
            hidden      : false,
            default     : device_driverlib_peripheral.LIN_LINMode[1].name,
            options     : device_driverlib_peripheral.LIN_LINMode,
            onChange    : onChangeLinMode,
        },
        {
            name        : "linCommMode",
            displayName : "LIN Communication Mode ",
            description : 'LIN Communication Mode. Choose whether to set the length of the LIN frame in the SCIFORMAT register (for LIN 2.0 and newer) or in the ID Byte (for LIN 1.3).',
            hidden      : false,
            default     : device_driverlib_peripheral.LIN_CommMode[0].name,
            options     : device_driverlib_peripheral.LIN_CommMode,
        },
        {
            name        : "linFrameLength",
            displayName : "Frame Length",
            description : 'Number of bytes in the response field.',
            hidden      : false,
            default     : 1,
            options     : list1to8,
        },
        {
            name        : "sciCharLength",
            displayName : "Word Length",
            description : 'Number of bits per character transmitted/received.',
            hidden      : true,
            default     : 8,
            options     : list1to8,
        },
        {
            name        : "sciFrameLength",
            displayName : "Frame Length",
            description : 'Number of characters in response field. Similar to operating in LIN mode, SCI mode can optionally transmit/receive up to 8 characters at a time.',
            hidden      : true,
            default     : 1,
            options     : list1to8,
        },
        {
            name        : "sciStopBits",
            displayName : "Stop Mode",
            description : 'Number of SCI Stop Bits.',
            hidden      : true,
            default     : device_driverlib_peripheral.LIN_SCIStopBits[0].name,
            options     : device_driverlib_peripheral.LIN_SCIStopBits,
        },
        {
            name        : "enableParity",
            displayName : "Enable Parity Check",
            description : 'Enable Parity Check.',
            hidden      : false,
            default     : true,
        },
        {
            name        : "enableMultibuffer",
            displayName : "Enable Multibuffer mode",
            description : 'Whether multibuffer mode should be enabled. Similar to the FIFO/non-FIFO mode in the SCI module, enabling Multibuffer mode can be used to reduce CPU load when transmitting and receiving large amounts of data.',
            hidden      : false,
            default     : true,
        },
        {
            name        : "sciCommMode",
            displayName : "SCI Communication Mode ",
            description : 'SCI Communication Mode for use in multiprocessor communication. Enabling Address-bit mode will add an extra bit to each transmission distinguishing an address byte from a data byte.',
            hidden      : true,
            default     : device_driverlib_peripheral.LIN_SCICommMode[0].name,
            options     : device_driverlib_peripheral.LIN_SCICommMode,
        },
        {
            name        : "sleepMode",
            displayName : "Start in Sleep Mode",
            description : 'Configure SCI to start in Sleep Mode. Similar to the sleep mode of the SCI module, enabling sleep mode allows the module to ignore received frames until software clears the sleep bit.',
            hidden      : true,
            default     : false,
        },
        {
            name        : "linDebugMode",
            displayName : "LIN/SCI Debug Mode ",
            description : 'LIN/SCI Debug Mode.',
            hidden      : false,
            default     : device_driverlib_peripheral.LIN_DebugMode[1].name,
            options     : device_driverlib_peripheral.LIN_DebugMode,
        },
        {
            name        : "linChecksumType",
            displayName : "LIN Checksum Type ",
            description : 'Whether to use Classic or Enhanced Checksum. Classic Checksum is compatible with LIN 1.3 responder nodes and Enhanced Checksum is compatible with LIN 2.0 or newer responder nodes.',
            hidden      : false,
            default     : device_driverlib_peripheral.LIN_ChecksumType[1].name,
            options     : device_driverlib_peripheral.LIN_ChecksumType,
        },
        {
            name        : "linMessageFilter",
            displayName : "LIN Message Filter (HGENCTRL)",
            description : 'LIN Message Filter: Using the ID Byte for filtering will set HGENCTRL = 0. Using the ID Responder Task Byte for filtering will set HGENCTRL = 1.(recomended)',
            hidden      : false,
            default     : device_driverlib_peripheral.LIN_MessageFilter[1].name,
            options     : device_driverlib_peripheral.LIN_MessageFilter,
        },
        {
            name        : "enableSCIParity",
            displayName : "SCI Parity Mode",
            description : 'SCI Parity Mode.',
            hidden      : true,
            default     : "disabled",
            options: [
                {name:"disabled", displayName: "No parity"},
                {name:"LIN_SCI_PAR_ODD", displayName: "Odd parity"},
                {name:"LIN_SCI_PAR_EVEN", displayName: "Even parity"},
            ]
        },
        ]
    },
    {    
        name        : "GROUP_BR_SETTINGS",
        displayName : "Baud Rate Settings",
        collapsed   : false,
        config      : [
            {
                name        : "autoBaudRate",
                displayName : "Enable Automatic Baud Rate",
                description : 'Enable Automatic Baud Rate. With automatic baud rate enabled, the LIN responder can auto-detect the baud rate within 10% of the expected value.',
                hidden      : true,
                default     : false,
                onChange    : onChangeAutoBaud,
            },
            {
                name        : "brVal",
                displayName : "Baud Rate Value",
                description : 'Baud Rate used by LIN/SCI module.',
                hidden      : false,
                default     : 9600,
            },
            {
                name        : "mbrVal",
                displayName : "Expected Baud Rate Value",
                description : 'Baud Rate used by LIN module in Adaptive baud rate mode. This should be set to the expected baud rate. The LIN module can adapt to a baud rate up to 10% faster or 10% slower than the expected baud rate.',
                hidden      : true,
                default     : 20000,
            },
            {
                name        : "mbrValActual",
                displayName : "Actual Baud Rate Value",
                description : 'Actual calculated Baud Rate used by LIN/SCI module in Adaptive baud rate mode.',
                hidden      : true,
                getValue    : (inst) => {
                    let linCLK = getUpdatedLINClock(inst)
                    
                    var baudrt, Pval, Mval, MBRval, baudrtActual;
                    var ret;
                    if(inst.opMode == "LIN" && inst.autoBaudRate && inst.linMode == "LIN_MODE_LIN_RESPONDER"){
                        baudrt      = inst.mbrVal * 1.1;
                        MBRval = Math.round(linCLK/(baudrt));
                        baudrtActual = (linCLK / MBRval);
                        ret =  Math.round(baudrtActual);
                        return ret
                    }
                            
                    return NaN
                },
                default     : 1000000,
            },
            {
                name        : "mbrValErr",
                displayName : "Baud Rate Error Percent",
                description : 'Error percent in Baud Rate used by LIN/SCI module in Adaptive baud rate mode.',
                hidden      : true,
                getValue    : (inst) => {
                    let linCLK = getUpdatedLINClock(inst)

                    var baudrt, Pval, Mval, MBRval, baudrtActual;
                    var ret;
                    if(inst.opMode == "LIN" && inst.autoBaudRate && inst.linMode == "LIN_MODE_LIN_RESPONDER"){
                        baudrt      = inst.mbrVal * 1.1;
                        MBRval = Math.round(linCLK/(baudrt));
                        baudrtActual = (linCLK / MBRval);
                        return Number((Math.abs((baudrtActual-baudrt)/baudrt)*100).toFixed(3));
                    }
                    return NaN;
                },
                default     : 9600,
            },
            {
                name        : "mbrPrescaler",
                displayName : "Baud Rate Prescaler",
                description : '13-bit maximum baud rate prescaler.',
                hidden      : true,
                getValue    : (inst) => {
                    let linCLK = getUpdatedLINClock(inst)

                    var baudrt, Pval, Mval, MBRval, baudrtActual;
                    var ret;
                    if(inst.opMode == "LIN" && inst.autoBaudRate && inst.linMode == "LIN_MODE_LIN_RESPONDER"){
                        baudrt      = inst.mbrVal * 1.1;
                        MBRval = Math.round(linCLK/(baudrt));
                        return MBRval;
                    }
                    return NaN;
                },
                default     : 30,
            },
            {
                name        : "brValActual",
                displayName : "Actual Baud Rate Value",
                description : 'Actual calculated Baud Rate used by LIN/SCI module.',
                hidden      : false,
                getValue    : (inst) => {
                    let linCLK = getUpdatedLINClock(inst)

                    var baudrt, Pval, Mval, MBRval, baudrtActual;
                    var ret;
                    if((inst.opMode == "LIN" && inst.linMode == "LIN_MODE_LIN_COMMANDER") || (inst.opMode == "LIN" && inst.linMode == "LIN_MODE_LIN_RESPONDER" && !inst.autoBaudRate) || inst.opMode == "SCI"){
                        baudrt      = inst.brVal;
                        Pval = Math.floor((linCLK/(16*baudrt)) - 1);
                        Mval = Math.round(((linCLK/(16*baudrt)) - 1 - Pval) * 16);
                        baudrtActual = (linCLK/(16*(Pval + 1 + (Mval/16))));
                        ret =  Math.round(baudrtActual);
                        return ret;
                    }
                    return NaN;
                },
                default     : 9600,
            },
            {
                name        : "brValErr",
                displayName : "Baud Rate Error Percent",
                description : 'Error percent in Baud Rate used by LIN/SCI module.',
                hidden      : false,
                getValue    : (inst) => {
                    let linCLK = getUpdatedLINClock(inst)

                    var baudrt, Pval, Mval, MBRval, baudrtActual;
                    var ret;
                    if((inst.opMode == "LIN" && inst.linMode == "LIN_MODE_LIN_COMMANDER") || (inst.opMode == "LIN" && inst.linMode == "LIN_MODE_LIN_RESPONDER" && !inst.autoBaudRate) || inst.opMode == "SCI"){
                        baudrt      = inst.brVal;
                        var Pval = Math.floor((linCLK/(16*baudrt)) - 1);
                        var Mval = Math.round(((linCLK/(16*baudrt)) - 1 - Pval) * 16);
                        var baudrtActual = (linCLK/(16*(Pval + 1 + (Mval/16))));
                        return Number((Math.abs((baudrtActual-baudrt)/baudrt)*100).toFixed(3));
                    }
                    return NaN;
                },
                default     : 9600,
            },
            {
                name        : "brPrescaler",
                displayName : "Baud Rate Prescaler (P)",
                description : '24-bit baud rate prescaler.',
                hidden      : false,
                getValue    : (inst) => {
                    let linCLK = getUpdatedLINClock(inst)

                    var baudrt, Pval, Mval, MBRval, baudrtActual;
                    var ret;
                    if((inst.opMode == "LIN" && inst.linMode == "LIN_MODE_LIN_COMMANDER") || (inst.opMode == "LIN" && inst.linMode == "LIN_MODE_LIN_RESPONDER" && !inst.autoBaudRate) || inst.opMode == "SCI"){
                        baudrt      = inst.brVal;
                        var Pval = Math.floor((linCLK/(16*baudrt)) - 1);
                        return Pval;
                    }
                    return NaN;
                },
                default     : 96,
            },
            {
                name        : "brDivider",
                displayName : "Baud Rate Fractional Divider (M)",
                description : '4-bit baud rate fractional divider.',
                hidden      : false,
                getValue    : (inst) => {
                    let linCLK = getUpdatedLINClock(inst)

                    var baudrt, Pval, Mval, MBRval, baudrtActual;
                    var ret;
                    if((inst.opMode == "LIN" && inst.linMode == "LIN_MODE_LIN_COMMANDER") || (inst.opMode == "LIN" && inst.linMode == "LIN_MODE_LIN_RESPONDER" && !inst.autoBaudRate) || inst.opMode == "SCI"){
                        baudrt      = inst.brVal;
                        var Pval = Math.floor((linCLK/(16*baudrt)) - 1);
                        var Mval = Math.round(((linCLK/(16*baudrt)) - 1 - Pval) * 16);
                        return Mval;
                    }
                    return NaN;
                },
                default     : 11,
            },
            {
                name        : "linClkValue",
                displayName : "LIN Clock Value",
                description : 'LIN Clock Value',
                hidden      : true,
                getValue    : (inst) => {
                    let linCLK = getUpdatedLINClock(inst)

                    return linCLK;
                },
                default     : 100000000,
            },
        ]
    },
    {    
        name        : "GROUP_SYNC_SETTINGS",
        displayName : "Sync Field Settings",
        collapsed   : false,
        config      : [
            {
                name        : "syncBreak",
                displayName : "Sync Break Extend Bits",
                description : 'The number of additional T-bits in Sync Break.',
                hidden      : true,
                default     : 5,
                options     : [
                    {name:0, displayName: "0 additional T-bits" },
                    {name:1, displayName: "1 additional T-bits" },
                    {name:2, displayName: "2 additional T-bits" },
                    {name:3, displayName: "3 additional T-bits" },
                    {name:4, displayName: "4 additional T-bits" },
                    {name:5, displayName: "5 additional T-bits" },
                    {name:6, displayName: "6 additional T-bits" },
                    {name:7, displayName: "7 additional T-bits" },
                ]
            },
            {
                name        : "delimiter",
                displayName : "Delimiter Bits",
                description : 'The number of T-bits in Delimiter.',
                hidden      : true,
                default     : 3,
                options     : [
                    {name:1, displayName: "1 T-bits" },
                    {name:2, displayName: "2 T-bits" },
                    {name:3, displayName: "3 T-bits" },
                    {name:4, displayName: "4 T-bits" },
                ]
            },
        ]
    },
    {    
        name        : "GROUP_MASK_SETTINGS",
        displayName : "ID and Mask Settings",
        collapsed   : false,
        config      : [
            {
                name        : "setResponderID",
                displayName : "Set Responder ID to Match",
                description : 'Set Responder ID to Match to incoming transmissions.',
                hidden      : true,
                onChange    : onChangeSetResponderID,
                default     : false,
            },
            {
                name        : "responderIdByte",
                displayName : "ID Responder Task Byte (8-bit Hexadecimal)",
                description : 'Identifier to which the received ID of an incoming header will be compared.',
                hidden      : true,
                default     : "00",
            },
            {
                name        : "txMask",
                displayName : "Transmit ID Mask (8-bit Hexadecimal)",
                description : 'Mask used for filtering an incoming ID message to determine if TX ID flag should be set.',
                hidden      : false,
                default     : "FF",
            },
            {
                name        : "rxMask",
                displayName : "Receive ID Mask (8-bit Hexadecimal)",
                description : 'Mask used for filtering an incoming ID message to determine if RX ID flag should be set.',
                hidden      : false,
                default     : "FF",
            },
        ]
    },
    {
        name: "useCase",
        displayName : "Use Case",
        description : 'Peripheral use case',
        hidden      : false,
        default     : 'ALL',
        options     : Pinmux.getPeripheralUseCaseNames("LIN"),
        onChange    : Pinmux.useCaseChanged,
        
    },
    {
        name: "GROUP_ISR",
        displayName: "Interrupt Configuration",
        collapsed: true,
        config: [
            {
                name        : "enableInterrupt",
                displayName : "Enable Interrupt",
                description : 'To Enable LIN/SCI Interrupts.',
                hidden      : false,
                onChange    : toggleInterrupt,
                default     : false,
            },
            {
                name        : "interruptFlags",
                displayName : "Enabled Interrupts",
                description : 'Which LIN Interrupts to enable.',
                hidden      : true,
                minSelections : 0,
                default     : ["LIN_INT_ALL"],
                options     : device_driverlib_peripheral.LIN_INT,
                
            },
            {
                name        : "sciInterruptFlags",
                displayName : "Enabled Interrupts",
                description : 'Which SCI Interrupts to enable.',
                hidden      : true,
                minSelections : 0,
                default     : ["LIN_SCI_INT_ALL"],
                options     : device_driverlib_peripheral.LIN_SCI_INT,
                
            },
            {
                name        : "interruptLine",
                displayName : "Interrupt Line",
                description : 'Which Interrupts line to use.',
                hidden      : true,
                minSelections : 0,
                onChange    : toggleInterrupt,
                default     : [],
                options     : device_driverlib_peripheral.LIN_InterruptLine,
                
            },
            {
                name        : "sciInterruptLine",
                displayName : "Interrupt Line",
                description : 'Which Interrupts line to use.',
                hidden      : true,
                minSelections : 0,
                onChange    : toggleInterrupt,
                default     : [],
                options     : device_driverlib_peripheral.LIN_InterruptLine,
                
            },
            {
                name: "registerL0Int",      
                displayName: "Register Line 0 Interrupt",
                hidden: true,
                default: false,
            },
            {
                name: "registerL1Int",
                displayName: "Register Line 1 Interrupt",
                hidden: true,
                default: false,
            },
            {
                name        : "interruptPriorityLine0",
                displayName : "Interrupt Line 0 triggers",
                description : 'Interrupt Line 0 triggers.',
                hidden      : true,
                minSelections : 0,
                default     : [],
                options     : device_driverlib_peripheral.LIN_INT,
                
            },
            {
                name        : "sciInterruptPriorityLine0",
                displayName : "Interrupt Line 0 triggers",
                description : 'Interrupt Line 0 triggers.',
                hidden      : true,
                minSelections : 0,
                default     :[],
                options     : device_driverlib_peripheral.LIN_SCI_INT,
                
            },
            {
                name        : "interruptPriorityLine1",
                displayName : "Interrupt line 1 triggers",
                description : 'Interrupt line 1 triggers.',
                hidden      : true,
                minSelections : 0,
                default     : [],
                options     : device_driverlib_peripheral.LIN_INT,
                
            },
            {
                name        : "sciInterruptPriorityLine1",
                displayName : "Interrupt line 1 triggers",
                description : 'Interrupt line 1 triggers.',
                hidden      : true,
                minSelections : 0,
                default     : [],
                options     : device_driverlib_peripheral.LIN_SCI_INT,
                
            },
        ]
    },
    {
        name: "GROUP_DMA",
        displayName: "DMA Configuration",
        collapsed: true,
        config: [
            {
                name        : "dmarx",
                displayName : "Use DMA for Receive",
                description : 'Whether or not to use DMA mode for RX.',
                hidden      : false,
                default     : false,
            },
            
            {
                name        : "dmatx",
                displayName : "Use DMA for Transmit",
                description : 'Whether or not to use DMA mode for TX.',
                hidden      : false,
                default     : false,
            },
        ]
    },
];

function onValidate(inst, validation) 
{   
    if (Common.getDeviceName() == "F28P65x" && inst.opMode == "LIN" && inst.linMode == "LIN_MODE_LIN_RESPONDER" && inst.autoBaudRate){
        validation.logError(
        "Adaptive baud rate is not supported on F28P65x for this release of Sysconfig.", 
        inst, "autoBaudRate");       
    }
    if (inst.dmarx)
    {
        validation.logWarning(
            "Must be defined in application code", 
            inst.linRXDMA, "srcAddressLinked");
    }
    if (inst.dmatx)
    {
        validation.logWarning(
            "Must be defined in application code", 
            inst.linTXDMA, "destAddressLinked");
    }
    if(!is_hexadecimal(inst.txMask)){
        validation.logError(
            "Please enter valid hexadecimal number", 
            inst, "txMask");
    }
    let txMaskInt = parseInt(inst.txMask, 16);
    if(txMaskInt < 0 || txMaskInt > 255){
        validation.logError(
            "Mask value must be in range 0x00 to 0xFF", 
            inst, "txMask");
    }

    if(!is_hexadecimal(inst.rxMask)){
        validation.logError(
            "Please enter valid hexadecimal number", 
            inst, "rxMask");
    }
    let rxMaskInt = parseInt(inst.rxMask, 16);
    if(rxMaskInt < 0 || rxMaskInt > 255){
        validation.logError(
            "Mask value must be in range 0x00 to 0xFF", 
            inst, "rxMask");
    }
    if(!is_hexadecimal(inst.responderIdByte)){
        validation.logError(
            "Please enter valid hexadecimal number", 
            inst, "responderIdByte");
    }

    if(inst.opMode == "LIN" && ((inst.linMode == "LIN_MODE_LIN_RESPONDER" && !inst.autoBaudRate) || (inst.linMode == "LIN_MODE_LIN_COMMANDER")) && (inst.brVal > 20000 || inst.brVal < 0)){
        validation.logError(
            "Baud rate must be in range 0-20KHz in LIN mode", 
            inst, "brVal");
    }

    if(inst.opMode == "LIN" && inst.linMode == "LIN_MODE_LIN_RESPONDER" && inst.autoBaudRate && (inst.mbrVal > 20000 || inst.mbrVal < 0)){
        validation.logError(
            "Expected baud rate must be in range 0-20KHz in LIN mode", 
            inst, "mbrVal");
    }

    if(Common.getDeviceName() != "F28P65x" && inst.opMode == "LIN" && inst.linMode == "LIN_MODE_LIN_RESPONDER" && inst.autoBaudRate && inst.mbrPrescaler > 8192){
        validation.logError(
            "Adaptive Baud Rate prescaler is greater than 13-bits. Decrease VCLK frequency or increase expected baud rate.", 
            inst, "mbrPrescaler");        
    }

    if(inst.opMode == "SCI"){
        let linCLK = Common.getSYSCLK();
        let clocktree = Common.getClockTree()
        if(clocktree){
            if(linDividers){
                if(!linBexists){
                    linCLK = parseInt(parseFloat((clocktree["LINACLK"].in)*1000000))
                }
                else{
                    linCLK = parseInt(parseFloat((clocktree[inst.lin.$solution.peripheralName+"CLK"].in)*1000000))
                }
            }
            else{
                linCLK = parseInt(parseFloat((clocktree["PERx_SYSCLK_domain"].in)*1000000))
            }
        }
        if(inst.brVal > linCLK/32 || inst.brVal < 0)
        {validation.logError(
            "Baud rate must be under " + String(linCLK/32) + " in SCI mode", 
            inst, "brVal");
        }
    }

    if (inst.opMode == "LIN" && inst.enableInterrupt && inst.interruptFlags.indexOf(device_driverlib_peripheral.LIN_INT[0].name) == -1 && inst.interruptFlags.indexOf(device_driverlib_peripheral.LIN_INT[1].name) == -1){
        "At least one interrupt should be enabled when 'Enable Interrupts' is checked.", 
        inst, "interruptFlags"
    }
    if (inst.opMode == "SCI" && inst.enableInterrupt && inst.sciInterruptFlags.indexOf(device_driverlib_peripheral.LIN_INT.name) != -1){
        "At least one interrupt should be enabled when 'Enable Interrupts' is checked.", 
        inst, "sciInterruptFlags"
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
    return (Common.typeMatches(component.type, ["LIN"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var linModule = {
    peripheralName: "LIN",
    displayName: "LIN",
    maxInstances: Common.peripheralCount("LIN"),
    defaultInstanceName: "myLIN",
    description: "LIN Peripheral",
    filterHardware : filterHardware,
    moduleInstances : (inst) => {
        var ownedInstances = []
        if (inst.enableInterrupt)
        {
            if(inst.registerL0Int){
                ownedInstances = ownedInstances.concat([{
                    name: "level0Int",      
                    group: "GROUP_ISR",
                    displayName: "Line 0 Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_LINE0_INT",
                        int : "INT_" + inst.$name + "_LINE0",
                        pinmuxPeripheralModule : "lin",
                        driverlibInt: "INT_#_0"
                    }
                }]);
            }
            if(inst.registerL1Int){
                ownedInstances = ownedInstances.concat([{
                    name: "level1Int",
                    group: "GROUP_ISR",    
                    displayName: "Line 1 Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_LINE1_INT",
                        int : "INT_" + inst.$name + "_LINE1",
                        pinmuxPeripheralModule : "lin",
                        driverlibInt: "INT_#_1"
                    }
                }]);
            }
        }
        if (inst.dmarx) {
            ownedInstances = ownedInstances.concat([
                {
                    name: "linRXDMA",
                    displayName: "RX DMA",
                    group: "GROUP_DMA",
                    moduleName: "/driverlib/dma.js",
                    collapsed: true,
                    args: {
                        $name: inst.$name + "_RX_DMA",
                    },
                    requiredArgs: {
                        srcAddressLinked: inst.$name + "_RX_DMA_ADDRESS",
                        peripheralRXLinked: true,
                        triggerSource: "DMA_TRIGGER_LINKED"
                    }
                },
            ])
        }
        if (inst.dmatx) {
            ownedInstances = ownedInstances.concat([
                {
                    name: "linTXDMA",
                    displayName: "TX DMA",
                    group: "GROUP_DMA",
                    moduleName: "/driverlib/dma.js",
                    collapsed: true,
                    args: {
                        $name: inst.$name + "_TX_DMA",
                    },
                    requiredArgs: {
                        destAddressLinked: inst.$name + "_TX_DMA_ADDRESS",
                        peripheralTXLinked: true,
                        triggerSource: "DMA_TRIGGER_LINKED"
                    }
                },
            ])
        }
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("LIN", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.requiredArgs = {
               qualMode : "GPIO_QUAL_ASYNC",
            }
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)

        return ownedInstances;
    },
    config: config,
    validate : onValidate,
    moduleStatic: {
        name: "LinGlobal",
        displayName: "LIN Global",
        config: [
            {
                name: "linAClkDivider",
                displayName: "LIN A Clock Divider (P)",
                description: "LIN A Clock Divider",
                default     : 1,
                hidden : !linDividers,
                getValue    : (inst) => {
                    var clockTree = Common.getClockTree();
                    if(clockTree){
                        if(linDividers){  //newer device
                            return clockTree.LINACLKDIV.divideValue
                        }
                        else{ //old device
                            return clockTree["PERx_SYSCLK_domain"].in
                        }
                    }
                    else{
                        return 0;
                    }
                }
            },
            {
                name: "linAClkGlobal",
                displayName: "LIN A Clock (VCLK) [MHz]",
                description: "LIN A Clock Frequency in Megahertz",
                default     : 100,
                readOnly    : true,
                getValue    : (inst) => {
                    var clockTree = Common.getClockTree();
                    if(clockTree){
                        if(linDividers){
                            return clockTree["LINACLK"].in
                        }
                        else{
                            return clockTree["PERx_SYSCLK_domain"].in
                        }
                    }
                    else{
                        return Common.getSYSCLK();
                    }
                }
            },
            {
                name: "linBClkDivider",
                displayName: "LIN B Clock Divider",
                description: "LIN B Clock Divider",
                default     : 1,
                hidden : !linDividers || !linBexists,
                getValue    : (inst) => {
                    var clockTree = Common.getClockTree();
                    if(clockTree){
                        if(linDividers){
                            if(!linBexists){
                                return 0;
                            }
                            else{
                                return clockTree.LINBCLKDIV.divideValue
                            }
                        }
                        else{
                            return clockTree["PERx_SYSCLK_domain"].in
                        }
                    }
                    else{
                        return 0;
                    }
                }
            },
            {
                name: "linBClkGlobal",
                displayName: "LIN B Clock (VCLK) [MHz]",
                description: "LIN B Clock Frequency in Megahertz",
                default     : 100,
                readOnly    : true,
                hidden : !linBexists,
                getValue    : (inst) => {
                    var clockTree = Common.getClockTree();
                    if(clockTree){
                        if(linDividers){
                            if(!linBexists){
                                return 0;
                            }
                            else{
                                return clockTree["LINBCLK"].in
                            }
                        }
                        else{
                            return clockTree["PERx_SYSCLK_domain"].in
                        }
                    }
                    else{
                        return Common.getSYSCLK();
                    }
                }
            },
        ],
    },
    templates: {
        boardc : "/driverlib/lin/lin.board.c.xdt",
        boardh : "/driverlib/lin/lin.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.linPinmuxRequirements
    
};


if (linModule.maxInstances <= 0)
{
    delete linModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(linModule)
    Pinmux.addPinMuxQualGroupToConfig(linModule)
}

exports = linModule;