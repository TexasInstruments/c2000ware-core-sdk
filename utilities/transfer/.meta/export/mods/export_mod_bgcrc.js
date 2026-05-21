//=============================================================================
// export_mod_bgcrc.js - BGCRC Export Module for CDT
//=============================================================================
// Purpose: Expose Background CRC diagnostic information for CDT
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: BGCRC chapter
//   - driverlib/<device>/driverlib/bgcrc.h
//   - driverlib/<device>/driverlib/inc/hw_bgcrc.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

//-----------------------------------------------------------------------------
// Device Support Constants (validated against hw_bgcrc.h presence in driverlib)
//-----------------------------------------------------------------------------
// BGCRC available on: F28002x, F28003x, F2838x, F28P65x
const DEVICES_WITH_BGCRC = [
    "F28002x", "F28003x", "F2838x", "F28P65x"
];

// Devices with BGCRC CPU module
const DEVICES_WITH_BGCRC_CPU = DEVICES_WITH_BGCRC;

// Devices with BGCRC CLA module (CLA devices that also have BGCRC)
const DEVICES_WITH_BGCRC_CLA = [
    "F28003x", "F2838x", "F28P65x"
];

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // BGCRC Running Status
    //-------------------------------------------------------------------------
    {
        name: "bgcrcRunning",
        displayName: "BGCRC Running",
        type: 'led',
        register: "EN.RUN_STS",
        updateFunc: (instBase) => `((HWREG(${instBase} + BGCRC_O_EN) & BGCRC_EN_RUN_STS) == BGCRC_EN_RUN_STS)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // CRC Mismatch / Fail Flags (NMI)
    //-------------------------------------------------------------------------
    {
        name: "bgcrcCrcFail",
        displayName: "CRC Mismatch (NMI)",
        type: 'led',
        register: "NMIFLG.CRC_FAIL",
        updateFunc: (instBase) => `((HWREGH(${instBase} + BGCRC_O_NMIFLG) & BGCRC_NMIFLG_CRC_FAIL) == BGCRC_NMIFLG_CRC_FAIL)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },
    {
        name: "bgcrcUncorrErr",
        displayName: "Uncorrectable ECC Error (NMI)",
        type: 'led',
        register: "NMIFLG.UNCORRECTABLE_ERR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + BGCRC_O_NMIFLG) & BGCRC_NMIFLG_UNCORRECTABLE_ERR) == BGCRC_NMIFLG_UNCORRECTABLE_ERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },
    {
        name: "bgcrcCorrErr",
        displayName: "Correctable ECC Error (NMI)",
        type: 'led',
        register: "NMIFLG.CORRECTABLE_ERR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + BGCRC_O_NMIFLG) & BGCRC_NMIFLG_CORRECTABLE_ERR) == BGCRC_NMIFLG_CORRECTABLE_ERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Watchdog Status Flags (NMI)
    //-------------------------------------------------------------------------
    {
        name: "bgcrcWdUnderflow",
        displayName: "Watchdog Underflow (NMI)",
        type: 'led',
        register: "NMIFLG.WD_UNDERFLOW",
        updateFunc: (instBase) => `((HWREGH(${instBase} + BGCRC_O_NMIFLG) & BGCRC_NMIFLG_WD_UNDERFLOW) == BGCRC_NMIFLG_WD_UNDERFLOW)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },
    {
        name: "bgcrcWdOverflow",
        displayName: "Watchdog Overflow (NMI)",
        type: 'led',
        register: "NMIFLG.WD_OVERFLOW",
        updateFunc: (instBase) => `((HWREGH(${instBase} + BGCRC_O_NMIFLG) & BGCRC_NMIFLG_WD_OVERFLOW) == BGCRC_NMIFLG_WD_OVERFLOW)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Interrupt Flags
    //-------------------------------------------------------------------------
    {
        name: "bgcrcTestDone",
        displayName: "CRC Test Done",
        type: 'led',
        register: "INTFLG.TEST_DONE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + BGCRC_O_INTFLG) & BGCRC_INTFLG_TEST_DONE) == BGCRC_INTFLG_TEST_DONE)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },
    {
        name: "bgcrcIntCrcFail",
        displayName: "CRC Fail Interrupt Flag",
        type: 'led',
        register: "INTFLG.CRC_FAIL",
        updateFunc: (instBase) => `((HWREGH(${instBase} + BGCRC_O_INTFLG) & BGCRC_INTFLG_CRC_FAIL) == BGCRC_INTFLG_CRC_FAIL)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // CRC Values
    //-------------------------------------------------------------------------
    {
        name: "bgcrcResult",
        displayName: "CRC Result",
        type: 'value',
        register: "RESULT",
        updateFunc: (instBase) => `HWREG(${instBase} + BGCRC_O_RESULT)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },
    {
        name: "bgcrcGolden",
        displayName: "CRC Golden Value",
        type: 'value',
        register: "GOLDEN",
        updateFunc: (instBase) => `HWREG(${instBase} + BGCRC_O_GOLDEN)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Address Tracking
    //-------------------------------------------------------------------------
    {
        name: "bgcrcCurrAddr",
        displayName: "Current Address",
        type: 'value',
        register: "CURR_ADDR",
        updateFunc: (instBase) => `HWREG(${instBase} + BGCRC_O_CURR_ADDR)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Watchdog Counter
    //-------------------------------------------------------------------------
    {
        name: "bgcrcWdCnt",
        displayName: "Watchdog Counter",
        type: 'value',
        register: "WD_CNT",
        updateFunc: (instBase) => `HWREG(${instBase} + BGCRC_O_WD_CNT)`,
        applicable: (inst) => {
            return DEVICES_WITH_BGCRC.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "BgcrcCpuRegs" },
    "cla": (instName) => { return "BgcrcClaRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Write-1-to-Clear and Force registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // NMI Clear registers (Write-1-to-Clear)
    { name: "NMICLR", register: "BGCRC_NMICLR" },
    // NMI Force registers (Write-Only)
    { name: "NMIFRC", register: "BGCRC_NMIFRC" },
    // Interrupt Clear registers (Write-1-to-Clear)
    { name: "INTCLR", register: "BGCRC_INTCLR" },
    // Interrupt Force registers (Write-Only)
    { name: "INTFRC", register: "BGCRC_INTFRC" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
