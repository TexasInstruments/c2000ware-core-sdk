//=============================================================================
// export_mod_epg.js - EPG Export Module for CDT
//=============================================================================
// Purpose: Expose External Programmable GPIO diagnostic information for CDT
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: EPG chapter
//   - driverlib/<device>/driverlib/epg.h
//   - driverlib/<device>/driverlib/inc/hw_epg.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

//-----------------------------------------------------------------------------
// Device Support Constants
//-----------------------------------------------------------------------------
// EPG available on select devices
const DEVICES_WITH_EPG = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F28P55x", "F28P65x"
];

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // EPG Global Interrupt Status
    //-------------------------------------------------------------------------
    {
        name: "epgGlobalInt",
        displayName: "EPG Global Interrupt",
        type: 'led',
        register: "GINTSTS",
        updateFunc: (instBase) => `(HWREGH(${instBase} + EPG_O_GINTSTS) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_EPG.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // EPG Interrupt Status (individual bits)
    //-------------------------------------------------------------------------
    {
        name: "epgIntStatus",
        displayName: "EPG Interrupt Status",
        type: 'value',
        register: "GINTSTS",
        updateFunc: (instBase) => `HWREGH(${instBase} + EPG_O_GINTSTS)`,
        applicable: (inst) => {
            return DEVICES_WITH_EPG.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // EPG Lock Status
    //-------------------------------------------------------------------------
    {
        name: "epgLocked",
        displayName: "EPG Registers Locked",
        type: 'led',
        register: "LOCK",
        updateFunc: (instBase) => `(HWREG(${instBase} + EPG_O_LOCK) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_EPG.includes(deviceName);
        }
    },
    {
        name: "epgCommitted",
        displayName: "EPG Lock Committed",
        type: 'led',
        register: "COMMIT",
        updateFunc: (instBase) => `(HWREG(${instBase} + EPG_O_COMMIT) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_EPG.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Signal Generator 0 Active Data (for debugging)
    //-------------------------------------------------------------------------
    {
        name: "epgSiggen0Data0Active",
        displayName: "SigGen0 Data0 Active",
        type: 'value',
        register: "SIGGEN0_DATA0_ACTIVE",
        updateFunc: (instBase) => `HWREG(${instBase} + EPG_O_SIGGEN0_DATA0_ACTIVE)`,
        applicable: (inst) => {
            return DEVICES_WITH_EPG.includes(deviceName);
        }
    },
    {
        name: "epgSiggen0Data1Active",
        displayName: "SigGen0 Data1 Active",
        type: 'value',
        register: "SIGGEN0_DATA1_ACTIVE",
        updateFunc: (instBase) => `HWREG(${instBase} + EPG_O_SIGGEN0_DATA1_ACTIVE)`,
        applicable: (inst) => {
            return DEVICES_WITH_EPG.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Clock Divider Configuration (for debugging)
    //-------------------------------------------------------------------------
    {
        name: "epgClkDiv0Ctl",
        displayName: "ClkDiv0 Control",
        type: 'value',
        register: "CLKDIV0_CTL0",
        updateFunc: (instBase) => `HWREG(${instBase} + EPG_O_CLKDIV0_CTL0)`,
        applicable: (inst) => {
            return DEVICES_WITH_EPG.includes(deviceName);
        }
    },
    {
        name: "epgClkDiv1Ctl",
        displayName: "ClkDiv1 Control",
        type: 'value',
        register: "CLKDIV1_CTL0",
        updateFunc: (instBase) => `HWREG(${instBase} + EPG_O_CLKDIV1_CTL0)`,
        applicable: (inst) => {
            return DEVICES_WITH_EPG.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Global Control Registers (for debugging)
    //-------------------------------------------------------------------------
    {
        name: "epgGctl0",
        displayName: "EPG Global Control 0",
        type: 'value',
        register: "GCTL0",
        updateFunc: (instBase) => `HWREG(${instBase} + EPG_O_GCTL0)`,
        applicable: (inst) => {
            return DEVICES_WITH_EPG.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "EpgRegs" },
    "mux": (instName) => { return "EpgMuxRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Clear and Force registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Interrupt Clear (Write-1-to-Clear)
    { name: "GINTCLR", register: "EPG_GINTCLR" },
    // Interrupt Force (Write-Only)
    { name: "GINTFRC", register: "EPG_GINTFRC" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
