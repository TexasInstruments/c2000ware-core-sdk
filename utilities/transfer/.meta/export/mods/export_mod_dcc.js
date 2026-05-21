//=============================================================================
// export_mod_dcc.js - DCC (Dual Clock Comparator) Export Module for CDT
//=============================================================================
// Purpose: Expose Dual Clock Comparator diagnostic information for CDT
// Devices: F280013x, F280015x, F28002x, F28003x, F28004x, F2838x, F28P55x, F28P65x
// Note: F2807x, F2837xD, F2837xS do NOT have DCC hardware
// Reference: driverlib/<device>/driverlib/inc/hw_dcc.h
//
// Register Offsets (from hw_dcc.h):
//   DCC_O_STATUS   = 0x14 - Status register (ERR, DONE flags)
//   DCC_O_CNT0     = 0x18 - Counter 0 current value
//   DCC_O_VALID0   = 0x1C - Valid counter 0 current value
//   DCC_O_CNT1     = 0x20 - Counter 1 current value
//   DCC_O_CNTSEED0 = 0x08 - Counter 0 seed value
//   DCC_O_CNTSEED1 = 0x10 - Counter 1 seed value
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_DCC, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

let exportsInfo = [
    //-------------------------------------------------------------------------
    // DCC Status Flags (DCC_O_STATUS at offset 0x14)
    //-------------------------------------------------------------------------
    {
        name: "ERR",
        displayName: "DCC Error Status",
        description: "Clock comparison error detected. Indicates the measured clock frequency ratio exceeded the tolerance window. Check clock sources and PLL settings.",
        type: 'led',
        ledType: 'error',  // Error - clock mismatch is a problem
        register: "DCCSTATUS.ERR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + DCC_O_STATUS) & DCC_STATUS_ERR) == DCC_STATUS_ERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCC.includes(deviceName);
        }
    },
    {
        name: "DONE",
        displayName: "DCC Single Shot Done",
        description: "Single-shot measurement complete. Indicates the DCC has finished one measurement cycle. Use with continuous mode disabled.",
        type: 'led',
        ledType: 'status',  // Informational - measurement complete is not an error
        register: "DCCSTATUS.DONE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + DCC_O_STATUS) & DCC_STATUS_DONE) == DCC_STATUS_DONE)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // DCC Counter Values (for clock frequency debugging)
    //-------------------------------------------------------------------------
    {
        name: "cnt0",
        displayName: "Counter 0 Value",
        description: "Current count for Clock Source 0 (reference clock). Decrements from seed value. Use to verify clock frequency ratio: freq0/freq1 ≈ seed0/seed1.",
        type: 'value',
        register: "DCCCNT0.COUNT0",
        updateFunc: (instBase) => `(HWREG(${instBase} + DCC_O_CNT0) & DCC_CNT0_COUNT0_M)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCC.includes(deviceName);
        }
    },
    {
        name: "cnt1",
        displayName: "Counter 1 Value",
        description: "Current count for Clock Source 1 (measured clock). Decrements from seed value. Should reach 0 within the valid window if clocks are correct.",
        type: 'value',
        register: "DCCCNT1.COUNT1",
        updateFunc: (instBase) => `(HWREG(${instBase} + DCC_O_CNT1) & DCC_CNT1_COUNT1_M)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCC.includes(deviceName);
        }
    },
    {
        name: "valid0",
        displayName: "Valid Counter 0 Value",
        description: "Current valid window counter. Defines tolerance for Counter 1 completion. Counter 1 must reach 0 before this counter expires for pass.",
        type: 'value',
        register: "DCCVALID0.VALID0",
        updateFunc: (instBase) => `(HWREGH(${instBase} + DCC_O_VALID0) & DCC_VALID0_VALID0_M)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // DCC Seed Values (configured values for reference)
    //-------------------------------------------------------------------------
    {
        name: "cntseed0",
        displayName: "Counter 0 Seed",
        description: "Configured seed value for Counter 0. Sets measurement period based on reference clock. Formula: seed0 = (freq0 × measurement_time).",
        type: 'value',
        register: "DCCCNTSEED0.COUNTSEED0",
        updateFunc: (instBase) => `(HWREG(${instBase} + DCC_O_CNTSEED0) & DCC_CNTSEED0_COUNTSEED0_M)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCC.includes(deviceName);
        }
    },
    {
        name: "cntseed1",
        displayName: "Counter 1 Seed",
        description: "Configured seed value for Counter 1. Must match expected clock ratio: seed1/seed0 = freq1/freq0 for pass condition.",
        type: 'value',
        register: "DCCCNTSEED1.COUNTSEED1",
        updateFunc: (instBase) => `(HWREG(${instBase} + DCC_O_CNTSEED1) & DCC_CNTSEED1_COUNTSEED1_M)`,
        applicable: (inst) => {
            return DEVICES_WITH_DCC.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "Dcc" + instName + "Regs" },
};

let exportsRegisterSkips = [];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
