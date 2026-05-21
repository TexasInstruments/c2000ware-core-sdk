//=============================================================================
// export_mod_sci.js - SCI (UART) Export Module for CDT
//=============================================================================
// Purpose: Expose Serial Communication Interface diagnostic information for CDT
// Devices: All Gen3 devices have SCI peripheral
// Reference: driverlib/<device>/driverlib/inc/hw_sci.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_GEN3, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// SCI is available on ALL Gen3 devices (re-uses DEVICES_GEN3 from centralized constants)
const DEVICES_WITH_SCI = DEVICES_GEN3;

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
// LED Color Semantics: RED = error/active condition, GREEN = normal/inactive
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // RX Status Register Error Flags
    //-------------------------------------------------------------------------
    {
        name: "fe",
        displayName: "Framing Error",
        description: "Stop bit not detected at expected time.\nRED = Framing error (baud rate mismatch or noise)\nGREEN = No framing error",
        type: 'led',
        register: "SCIRXST.FE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_FE) == SCI_RXST_FE)`,
        applicable: (inst) => {
            return DEVICES_WITH_SCI.includes(deviceName);
        }
    },
    {
        name: "pe",
        displayName: "Parity Error",
        description: "Received parity bit does not match calculated parity.\nRED = Parity error (data corruption or config mismatch)\nGREEN = No parity error",
        type: 'led',
        register: "SCIRXST.PE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_PE) == SCI_RXST_PE)`,
        applicable: (inst) => {
            return DEVICES_WITH_SCI.includes(deviceName);
        }
    },
    {
        name: "oe",
        displayName: "Overrun Error",
        description: "New data received before previous data was read.\nRED = Overrun error (data loss - increase read rate)\nGREEN = No overrun error",
        type: 'led',
        register: "SCIRXST.OE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_OE) == SCI_RXST_OE)`,
        applicable: (inst) => {
            return DEVICES_WITH_SCI.includes(deviceName);
        }
    },
    {
        name: "rxrdy",
        displayName: "Receive Ready",
        description: "Data available in receive buffer.\nRED = Data ready to read (RXBUF contains valid data)\nGREEN = No data available",
        type: 'led',
        register: "SCIRXST.RXRDY",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_RXRDY) == SCI_RXST_RXRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_SCI.includes(deviceName);
        }
    },
    {
        name: "txrdy",
        displayName: "Transmit Ready",
        description: "Transmit buffer ready to accept new data.\nRED = TX buffer ready (can write new data)\nGREEN = TX buffer busy (wait before writing)",
        type: 'led',
        register: "SCICTL2.TXRDY",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_CTL2) & SCI_CTL2_TXRDY) == SCI_CTL2_TXRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_SCI.includes(deviceName);
        }
    },
    {
        name: "brkdt",
        displayName: "Break Detect",
        description: "Break condition detected on RX line.\nRED = Break detected (RX held low for >10 bit times)\nGREEN = No break condition",
        type: 'led',
        register: "SCIRXST.BRKDT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_BRKDT) == SCI_RXST_BRKDT)`,
        applicable: (inst) => {
            return DEVICES_WITH_SCI.includes(deviceName);
        }
    },
    {
        name: "rxffovf",
        displayName: "Receive FIFO Overflow",
        description: "RX FIFO overflow - data lost.\nRED = FIFO overflow (increase FIFO read rate)\nGREEN = No overflow",
        type: 'led',
        register: "SCIFFRX.RXFFOVF",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_FFRX) & SCI_FFRX_RXFFOVF) == SCI_FFRX_RXFFOVF)`,
        applicable: (inst) => {
            return DEVICES_WITH_SCI.includes(deviceName);
        }
    },
    {
        name: "txempty",
        displayName: "Transmitter Empty",
        description: "Transmit buffer and shift register both empty.\nRED = Transmitter idle (all data sent)\nGREEN = Transmission in progress",
        type: 'led',
        register: "SCICTL2.TXEMPTY",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_CTL2) & SCI_CTL2_TXEMPTY) == SCI_CTL2_TXEMPTY)`,
        applicable: (inst) => {
            return DEVICES_WITH_SCI.includes(deviceName);
        }
    },
    {
        name: "rxerror",
        displayName: "Receiver Error (Any)",
        description: "Composite error flag - any RX error condition.\nRED = Error detected (check FE, PE, OE, BRKDT flags)\nGREEN = No errors",
        type: 'led',
        register: "SCIRXST.RXERROR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_RXST) & SCI_RXST_RXERROR) == SCI_RXST_RXERROR)`,
        applicable: (inst) => {
            return DEVICES_WITH_SCI.includes(deviceName);
        }
    },
    //-------------------------------------------------------------------------
    // FIFO Status Values
    //-------------------------------------------------------------------------
    {
        name: "txffst",
        displayName: "TX FIFO Level",
        type: 'value',
        register: "SCIFFTX.TXFFST",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_FFTX) & SCI_FFTX_TXFFST_M) >> SCI_FFTX_TXFFST_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_SCI.includes(deviceName);
        }
    },
    {
        name: "rxffst",
        displayName: "RX FIFO Level",
        type: 'value',
        register: "SCIFFRX.RXFFST",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SCI_O_FFRX) & SCI_FFRX_RXFFST_M) >> SCI_FFRX_RXFFST_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_SCI.includes(deviceName);
        }
    },
]

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
// Maps SysConfig instance names to register struct names
// Example: mySCI_A -> SciaRegs, mySCIA -> SciaRegs, mySCI0 -> SciaRegs
// The "default" lambda handles all letter and number keys correctly
// (e.g., instName="a" → "SciaRegs"). Explicit per-letter entries are kept
// for documentation clarity but are functionally covered by the default.
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "Sci" + instName + "Regs" },
    // Letter-based instance names (case-insensitive handled by toUpperCase in caller)
    "a": (instName) => { return "SciaRegs" },
    "b": (instName) => { return "ScibRegs" },
    "c": (instName) => { return "ScicRegs" },
    "d": (instName) => { return "ScidRegs" },
    // Numeric instance names (0-based to letter mapping)
    "0": (instName) => { return "SciaRegs" },
    "1": (instName) => { return "ScibRegs" },
    "2": (instName) => { return "ScicRegs" },
    "3": (instName) => { return "ScidRegs" },
}

//-----------------------------------------------------------------------------
// Registers to Skip (volatile data and Read-to-Clear registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Data buffer (volatile)
    { name: "RXBUF", register: "SCIRXBUF" },
    // FIFO registers with Write-1-to-Clear bits
    // Note: TXFFINTCLR, RXFFINTCLR, RXFFOVRCLR are W1C bits within FFTX/FFRX
    // These are handled as bitfields, not separate registers
]

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames : bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}