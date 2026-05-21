//=============================================================================
// export_mod_sdfm.js - SDFM Export Module for CDT
//=============================================================================
// Purpose: Expose Sigma-Delta Filter Module diagnostic information for CDT
// Devices: F28003x, F28004x, F2807x, F2837xD/S, F2838x, F28P55x, F28P65x
// Reference: driverlib/<device>/driverlib/inc/hw_sdfm.h
//
// Register Offsets (from hw_sdfm.h):
//   SDFM_O_SDIFLG = 0x0 - Interrupt Flag Register (32-bit)
//     Bits 0-7:   FLTx_FLG_CEVT1/CEVT2 - Comparator events per channel
//     Bits 8-11:  MF1-MF4 - Modulator failure per filter
//     Bits 12-15: AF1-AF4 - Acknowledge flags per filter
//     Bits 16-19: SDFFOVF1-SDFFOVF4 - FIFO overflow per channel
//     Bits 20-23: SDFFINT1-SDFFINT4 - FIFO interrupt per channel
//     Bit 31:     MIF - Master interrupt flag
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_SDFM, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

let exportsInfo = [
    //-------------------------------------------------------------------------
    // Master Interrupt Flag
    //-------------------------------------------------------------------------
    {
        name: "MIF",
        displayName: "Master Interrupt Flag",
        description: "Master interrupt flag aggregating all SDFM interrupt sources. RED indicates one or more SDFM events occurred. Check individual filter flags for specific cause.",
        type: 'led',
        register: "SDIFLG.MIF",
        updateFunc: (instBase) => `((HWREG(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_MIF) == SDFM_SDIFLG_MIF)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Modulator Failure Flags (per filter) - Critical diagnostic
    //-------------------------------------------------------------------------
    {
        name: "MF1",
        displayName: "Filter 1 Modulator Failure",
        description: "Modulator failure on Filter 1. RED indicates SD modulator clock or data signal lost. Check SD-ADC wiring, modulator power, and Manchester encoding if enabled.",
        type: 'led',
        register: "SDIFLG.MF1",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_MF1) == SDFM_SDIFLG_MF1)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "MF2",
        displayName: "Filter 2 Modulator Failure",
        description: "Modulator failure on Filter 2. RED indicates SD modulator clock or data signal lost. Check SD-ADC wiring, modulator power, and Manchester encoding if enabled.",
        type: 'led',
        register: "SDIFLG.MF2",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_MF2) == SDFM_SDIFLG_MF2)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "MF3",
        displayName: "Filter 3 Modulator Failure",
        description: "Modulator failure on Filter 3. RED indicates SD modulator clock or data signal lost. Check SD-ADC wiring, modulator power, and Manchester encoding if enabled.",
        type: 'led',
        register: "SDIFLG.MF3",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_MF3) == SDFM_SDIFLG_MF3)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "MF4",
        displayName: "Filter 4 Modulator Failure",
        description: "Modulator failure on Filter 4. RED indicates SD modulator clock or data signal lost. Check SD-ADC wiring, modulator power, and Manchester encoding if enabled.",
        type: 'led',
        register: "SDIFLG.MF4",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_MF4) == SDFM_SDIFLG_MF4)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // FIFO Overflow Flags (per channel) - Data loss indicator
    //-------------------------------------------------------------------------
    {
        name: "SDFFOVF1",
        displayName: "Filter 1 FIFO Overflow",
        description: "Data FIFO overflow on Filter 1. RED indicates data was lost because FIFO was full. Read data faster or increase filter decimation rate.",
        type: 'led',
        register: "SDIFLG.SDFFOVF1",
        updateFunc: (instBase) => `((HWREG(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_SDFFOVF1) == SDFM_SDIFLG_SDFFOVF1)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "SDFFOVF2",
        displayName: "Filter 2 FIFO Overflow",
        description: "Data FIFO overflow on Filter 2. RED indicates data was lost because FIFO was full. Read data faster or increase filter decimation rate.",
        type: 'led',
        register: "SDIFLG.SDFFOVF2",
        updateFunc: (instBase) => `((HWREG(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_SDFFOVF2) == SDFM_SDIFLG_SDFFOVF2)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "SDFFOVF3",
        displayName: "Filter 3 FIFO Overflow",
        description: "Data FIFO overflow on Filter 3. RED indicates data was lost because FIFO was full. Read data faster or increase filter decimation rate.",
        type: 'led',
        register: "SDIFLG.SDFFOVF3",
        updateFunc: (instBase) => `((HWREG(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_SDFFOVF3) == SDFM_SDIFLG_SDFFOVF3)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "SDFFOVF4",
        displayName: "Filter 4 FIFO Overflow",
        description: "Data FIFO overflow on Filter 4. RED indicates data was lost because FIFO was full. Read data faster or increase filter decimation rate.",
        type: 'led',
        register: "SDIFLG.SDFFOVF4",
        updateFunc: (instBase) => `((HWREG(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_SDFFOVF4) == SDFM_SDIFLG_SDFFOVF4)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Comparator Events (per channel) - Threshold crossing indicators
    //-------------------------------------------------------------------------
    {
        name: "FLT1_CEVT1",
        displayName: "Filter 1 High Comparator Event",
        description: "Filter 1 data exceeded high comparator threshold (CEVT1). RED indicates over-range condition. Use for overcurrent/overvoltage trip detection.",
        type: 'led',
        register: "SDIFLG.FLT1_FLG_CEVT1",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_FLT1_FLG_CEVT1) == SDFM_SDIFLG_FLT1_FLG_CEVT1)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "FLT1_CEVT2",
        displayName: "Filter 1 Low Comparator Event",
        description: "Filter 1 data fell below low comparator threshold (CEVT2). RED indicates under-range condition. Use for undercurrent/undervoltage trip detection.",
        type: 'led',
        register: "SDIFLG.FLT1_FLG_CEVT2",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_FLT1_FLG_CEVT2) == SDFM_SDIFLG_FLT1_FLG_CEVT2)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "FLT2_CEVT1",
        displayName: "Filter 2 High Comparator Event",
        description: "Filter 2 data exceeded high comparator threshold (CEVT1). RED indicates over-range condition. Use for overcurrent/overvoltage trip detection.",
        type: 'led',
        register: "SDIFLG.FLT2_FLG_CEVT1",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_FLT2_FLG_CEVT1) == SDFM_SDIFLG_FLT2_FLG_CEVT1)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "FLT2_CEVT2",
        displayName: "Filter 2 Low Comparator Event",
        description: "Filter 2 data fell below low comparator threshold (CEVT2). RED indicates under-range condition. Use for undercurrent/undervoltage trip detection.",
        type: 'led',
        register: "SDIFLG.FLT2_FLG_CEVT2",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_FLT2_FLG_CEVT2) == SDFM_SDIFLG_FLT2_FLG_CEVT2)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Acknowledge Flags (per filter) - Data ready indicators
    //-------------------------------------------------------------------------
    {
        name: "AF1",
        displayName: "Filter 1 Acknowledge Flag",
        description: "New data available in Filter 1. GREEN indicates fresh filtered data ready to read. Should toggle when filter is actively processing.",
        type: 'led',
        register: "SDIFLG.AF1",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_AF1) == SDFM_SDIFLG_AF1)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "AF2",
        displayName: "Filter 2 Acknowledge Flag",
        description: "New data available in Filter 2. GREEN indicates fresh filtered data ready to read. Should toggle when filter is actively processing.",
        type: 'led',
        register: "SDIFLG.AF2",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_AF2) == SDFM_SDIFLG_AF2)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "AF3",
        displayName: "Filter 3 Acknowledge Flag",
        description: "New data available in Filter 3. GREEN indicates fresh filtered data ready to read. Should toggle when filter is actively processing.",
        type: 'led',
        register: "SDIFLG.AF3",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_AF3) == SDFM_SDIFLG_AF3)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
    {
        name: "AF4",
        displayName: "Filter 4 Acknowledge Flag",
        description: "New data available in Filter 4. GREEN indicates fresh filtered data ready to read. Should toggle when filter is actively processing.",
        type: 'led',
        register: "SDIFLG.AF4",
        updateFunc: (instBase) => `((HWREGH(${instBase} + SDFM_O_SDIFLG) & SDFM_SDIFLG_AF4) == SDFM_SDIFLG_AF4)`,
        applicable: (inst) => {
            return DEVICES_WITH_SDFM.includes(deviceName);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "Sdfm" + instName + "Regs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Read-to-Clear registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "SDIFLGCLR", register: "SDFMSDIFLGCLR" },
];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
