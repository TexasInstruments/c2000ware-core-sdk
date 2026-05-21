//=============================================================================
// export_mod_lin.js - LIN Export Module for CDT
//=============================================================================
// Purpose: Expose LIN diagnostic information for Clinic Diagnostic Tool
// Devices: F280015x, F28002x, F28003x, F28004x, F28P55x, F28P65x
// Reference: driverlib/<device>/driverlib/inc/hw_lin.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// LIN availability (validated against hw_lin.h presence in driverlib)
const DEVICES_WITH_LIN = [
    "F280015x", "F28002x", "F28003x", "F28004x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    //-------------------------------------------------------------------------
    // LIN-Specific Error Flags (LIN mode only)
    //-------------------------------------------------------------------------
    {
        name: "be",
        displayName: "Bit Error",
        description: "LIN bit error detected. RED indicates transmitted bit differs from bus state. Check for bus contention or driver issues.",
        type: 'led',
        register: "SCIFLR.BE",
        updateFunc: (instBase) => `((HWREG(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_BE) == LIN_SCIFLR_BE)`,
        applicable: (inst) => {
            return (DEVICES_WITH_LIN.includes(deviceName) && inst.opMode == "LIN")? true : false;
        },
    },
    {
        name: "pbe",
        displayName: "Physical Bus Error",
        description: "LIN physical bus error. RED indicates bus stuck dominant or recessive. Check transceiver, wiring, and termination.",
        type: 'led',
        register: "SCIFLR.PBE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_PBE) == LIN_SCIFLR_PBE)`,
        applicable: (inst) => {
            return (DEVICES_WITH_LIN.includes(deviceName) && inst.opMode == "LIN") ? true : false;
        }
    },
    {
        name: "ce",
        displayName: "Checksum Error",
        description: "LIN checksum mismatch. RED indicates received data corrupted. Check for noise, baud rate mismatch, or slave issues.",
        type: 'led',
        register: "SCIFLR.CE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_CE) == LIN_SCIFLR_CE)`,
        applicable: (inst) => {
            return (DEVICES_WITH_LIN.includes(deviceName) && inst.opMode == "LIN") ? true : false;
        }
    },
    {
        name: "isfe",
        displayName: "Inconsistent Sync Field Error",
        description: "LIN sync field invalid. RED indicates slave failed to synchronize. Check master baud rate and break field length.",
        type: 'led',
        register: "SCIFLR.ISFE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_ISFE) == LIN_SCIFLR_ISFE)`,
        applicable: (inst) => {
            return (DEVICES_WITH_LIN.includes(deviceName) && inst.opMode == "LIN") ? true : false;
        }
    },
    {
        name: "nre",
        displayName: "No-Response Error",
        description: "LIN slave did not respond. RED indicates expected response frame missing. Check slave power, address ID, and bus connectivity.",
        type: 'led',
        register: "SCIFLR.NRE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_NRE) == LIN_SCIFLR_NRE)`,
        applicable: (inst) => {
            return (DEVICES_WITH_LIN.includes(deviceName) && inst.opMode == "LIN") ? true : false;
        }
    },
    {
        name: "fe",
        displayName: "Framing Error",
        description: "Invalid frame format. RED indicates stop bit not detected. Check baud rate settings and signal integrity.",
        type: 'led',
        register: "SCIFLR.FE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_FE) == LIN_SCIFLR_FE)`,
        applicable: (inst) => {
            return (DEVICES_WITH_LIN.includes(deviceName) && (inst.opMode == "LIN" || inst.opMode == "SCI")) ? true : false;
        }
    },
    {
        name: "oe",
        displayName: "Overrun Error",
        description: "Receive buffer overrun. RED indicates new data arrived before previous was read. Increase read rate or use interrupts.",
        type: 'led',
        register: "SCIFLR.OE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_OE) == LIN_SCIFLR_OE)`,
        applicable: (inst) => {
            return (DEVICES_WITH_LIN.includes(deviceName) && (inst.opMode == "LIN" || inst.opMode == "SCI")) ? true : false;
        }
    },
    {
        name: "pe",
        displayName: "Parity Error",
        description: "Parity check failed. RED indicates data corruption detected by parity bit. Check for noise or baud rate mismatch.",
        type: 'led',
        register: "SCIFLR.PE",
        updateFunc: (instBase) => `((HWREG(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_PE) == LIN_SCIFLR_PE)`,
        applicable: (inst) => {
            return (DEVICES_WITH_LIN.includes(deviceName) && (inst.opMode == "LIN" || inst.opMode == "SCI")) ? true : false;
        }
    },

    //-------------------------------------------------------------------------
    // LIN Timeout Flags (LIN mode only)
    //-------------------------------------------------------------------------
    {
        name: "toawus",
        displayName: "Timeout After Wakeup Signal",
        description: "LIN wakeup timeout. RED indicates no response after sending wakeup. Slave may be in deep sleep or disconnected.",
        type: 'led',
        register: "SCIFLR.TOAWUS",
        updateFunc: (instBase) => `((HWREG(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_TOAWUS) == LIN_SCIFLR_TOAWUS)`,
        applicable: (inst) => {
            return (DEVICES_WITH_LIN.includes(deviceName) && inst.opMode == "LIN") ? true : false;
        }
    },
    {
        name: "toa3wus",
        displayName: "Timeout After 3 Wakeup Signals",
        description: "LIN wakeup failed after 3 attempts. RED indicates slave unresponsive to multiple wakeup requests. Check slave hardware.",
        type: 'led',
        register: "SCIFLR.TOA3WUS",
        updateFunc: (instBase) => `((HWREG(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_TOA3WUS) == LIN_SCIFLR_TOA3WUS)`,
        applicable: (inst) => {
            return (DEVICES_WITH_LIN.includes(deviceName) && inst.opMode == "LIN") ? true : false;
        }
    },
    {
        name: "timeout",
        displayName: "Bus Idle Timeout",
        description: "LIN bus idle timeout. RED indicates no activity for extended period. May indicate bus sleep mode entry condition.",
        type: 'led',
        register: "SCIFLR.TIMEOUT",
        updateFunc: (instBase) => `((HWREG(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_TIMEOUT) == LIN_SCIFLR_TIMEOUT)`,
        applicable: (inst) => {
            return (DEVICES_WITH_LIN.includes(deviceName) && inst.opMode == "LIN") ? true : false;
        }
    },

    //-------------------------------------------------------------------------
    // SCI/LIN Common Status Flags
    //-------------------------------------------------------------------------
    {
        name: "rxrdy",
        displayName: "RX Ready",
        description: "Receive data ready. GREEN indicates data byte available to read. Should toggle during active communication.",
        type: 'led',
        register: "SCIFLR.RXRDY",
        updateFunc: (instBase) => `((HWREG(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_RXRDY) == LIN_SCIFLR_RXRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_LIN.includes(deviceName);
        }
    },
    {
        name: "txrdy",
        displayName: "TX Ready",
        description: "Transmit ready for data. GREEN indicates transmit buffer can accept new data. Write data to continue transmission.",
        type: 'led',
        register: "SCIFLR.TXRDY",
        updateFunc: (instBase) => `((HWREG(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_TXRDY) == LIN_SCIFLR_TXRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_LIN.includes(deviceName);
        }
    },
    {
        name: "busy",
        displayName: "Bus Busy",
        description: "LIN/SCI bus busy. GREEN indicates transmission or reception in progress. Wait for completion before new operation.",
        type: 'led',
        register: "SCIFLR.BUSY",
        updateFunc: (instBase) => `((HWREG(${instBase} + LIN_O_SCIFLR) & LIN_SCIFLR_BUSY) == LIN_SCIFLR_BUSY)`,
        applicable: (inst) => {
            return DEVICES_WITH_LIN.includes(deviceName);
        }
    },
]

let bitfieldInstanceNames = {
    "default": (instName) => { return "Lin"+ instName + "Regs" },
}

//-----------------------------------------------------------------------------
// Registers to Skip (Read-to-Clear and volatile registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "GLB_INT_CLR", register: "LIN_GLB_INT_CLR" },
]

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames : bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
