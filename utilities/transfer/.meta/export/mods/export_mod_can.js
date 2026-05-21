//=============================================================================
// export_mod_can.js - DCAN (Legacy CAN) Export Module for CDT
//=============================================================================
// Purpose: Expose DCAN diagnostic information for Clinic Diagnostic Tool
// Devices: F280013x, F280015x, F28002x, F28003x, F28004x, F2807x, F2837xD,
//          F2837xS, F2838x, F28P65x (validated against hw_can.h presence)
// Note: F28P55x does NOT have DCAN - only MCAN (CAN-FD)
// Reference: driverlib/<device>/driverlib/inc/hw_can.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CANA, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// DCAN availability is same as CANA (from device_constants.js)
const DEVICES_WITH_DCAN = DEVICES_WITH_CANA;

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
// Reference: driverlib/<device>/driverlib/inc/hw_can.h
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // Error and Status Register (CAN_O_ES at offset 0x4)
    //-------------------------------------------------------------------------
    {
        name: "BOff",
        displayName: "Bus-Off Status",
        description: "CAN bus-off state. Controller has entered bus-off due to excessive errors (TEC>255). Node cannot transmit or receive until automatic recovery or software reset.",
        type: 'led',
        ledType: 'error',  // Error - bus-off is a critical error
        register: "CAN_ES.BOff",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CAN_O_ES) & CAN_ES_BOFF) == CAN_ES_BOFF)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCAN.includes(deviceName);
        }
    },
    {
        name: "EWarn",
        displayName: "Error Warning Status",
        description: "Error warning threshold exceeded. TEC or REC has reached 96 or higher. Node is approaching error-passive state. Check bus wiring, termination, and bit timing.",
        type: 'led',
        ledType: 'error',  // Error - warning level exceeded
        register: "CAN_ES.EWarn",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CAN_O_ES) & CAN_ES_EWARN) == CAN_ES_EWARN)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCAN.includes(deviceName);
        }
    },
    {
        name: "EPass",
        displayName: "Error-Passive Status",
        description: "CAN error-passive state. TEC or REC has reached 128. Node can still communicate but uses passive error flags. May indicate bus contention or signal quality issues.",
        type: 'led',
        ledType: 'error',  // Error - error-passive is a problem
        register: "CAN_ES.EPass",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CAN_O_ES) & CAN_ES_EPASS) == CAN_ES_EPASS)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCAN.includes(deviceName);
        }
    },
    {
        name: "PER",
        displayName: "Parity Error Detected",
        description: "Message RAM parity error detected. Data corruption in CAN message RAM. This is a critical hardware error - check for EMI issues or memory failure.",
        type: 'led',
        ledType: 'error',  // Error - parity error is critical
        register: "CAN_ES.PER",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CAN_O_ES) & CAN_ES_PER) == CAN_ES_PER)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCAN.includes(deviceName);
        }
    },
    {
        name: "LEC",
        displayName: "Last Error Code",
        type: 'value',
        register: "CAN_ES.LEC",
        // 0=None, 1=Stuff, 2=Form, 3=Ack, 4=Bit1, 5=Bit0, 6=CRC, 7=Unused
        updateFunc: (instBase) => `((HWREGH(${instBase} + CAN_O_ES) & CAN_ES_LEC_M) >> CAN_ES_LEC_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCAN.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Error Counter Register (CAN_O_ERRC at offset 0x8)
    // TEC: bits 0-7, REC: bits 8-14
    //-------------------------------------------------------------------------
    {
        name: "TEC",
        displayName: "Transmit Error Counter",
        type: 'value',
        register: "CAN_ERRC.TEC",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CAN_O_ERRC) & CAN_ERRC_TEC_M) >> CAN_ERRC_TEC_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCAN.includes(deviceName);
        }
    },
    {
        name: "REC",
        displayName: "Receive Error Counter",
        type: 'value',
        register: "CAN_ERRC.REC",
        updateFunc: (instBase) => `((HWREGH(${instBase} + CAN_O_ERRC) & CAN_ERRC_REC_M) >> CAN_ERRC_REC_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCAN.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
// Maps SysConfig instance names to register struct names
// Example: myCAN_A -> CanaRegs, myCANA -> CanaRegs, myCAN0 -> CanaRegs
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "Can"+ instName + "Regs" },
    // Letter-based instance names (case-insensitive handled by toUpperCase in caller)
    "a": (instName) => { return "CanaRegs" },
    "b": (instName) => { return "CanbRegs" },
    // Numeric instance names (0-based to letter mapping)
    "0": (instName) => { return "CanaRegs" },
    "1": (instName) => { return "CanbRegs" },
}

//-----------------------------------------------------------------------------
// Registers to Skip (Read-to-Clear and volatile registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "GLB_INT_CLR", register: "CAN_GLB_INT_CLR" },
]

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}