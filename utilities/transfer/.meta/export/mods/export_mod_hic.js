//=============================================================================
// export_mod_hic.js - HIC Export Module for CDT
//=============================================================================
// Purpose: Expose Host Interface Controller diagnostic information for CDT
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: HIC chapter
//   - driverlib/<device>/driverlib/hic.h
//   - driverlib/<device>/driverlib/inc/hw_hic.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

//-----------------------------------------------------------------------------
// Device Support Constants
//-----------------------------------------------------------------------------
// HIC available on select devices
const DEVICES_WITH_HIC = [
    "F28003x", "F28P55x", "F28P65x"
];

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // Host to Device Interrupt Flags
    //-------------------------------------------------------------------------
    {
        name: "hicH2DInt",
        displayName: "H2D Interrupt Flag",
        type: 'led',
        register: "H2DINTFLG",
        updateFunc: (instBase) => `(HWREGH(${instBase} + HIC_O_H2DINTFLG) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Device to Host Interrupt Flags
    //-------------------------------------------------------------------------
    {
        name: "hicD2HInt",
        displayName: "D2H Interrupt Flag",
        type: 'led',
        register: "D2HINTFLG",
        updateFunc: (instBase) => `(HWREGH(${instBase} + HIC_O_D2HINTFLG) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Access Violation Status
    //-------------------------------------------------------------------------
    {
        name: "hicAccViolation",
        displayName: "Access Violation Occurred",
        type: 'led',
        register: "ACCVIOADDR (non-zero)",
        updateFunc: (instBase) => `(HWREG(${instBase} + HIC_O_ACCVIOADDR) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },
    {
        name: "hicAccVioAddr",
        displayName: "Access Violation Address",
        type: 'value',
        register: "ACCVIOADDR",
        updateFunc: (instBase) => `HWREG(${instBase} + HIC_O_ACCVIOADDR)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Error Address
    //-------------------------------------------------------------------------
    {
        name: "hicErrAddr",
        displayName: "Host Error Address",
        type: 'value',
        register: "ERRADDR",
        updateFunc: (instBase) => `HWREG(${instBase} + HIC_O_ERRADDR)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Token Registers (for host/device communication)
    //-------------------------------------------------------------------------
    {
        name: "hicH2DToken",
        displayName: "Host to Device Token",
        type: 'value',
        register: "H2DTOKEN",
        updateFunc: (instBase) => `HWREG(${instBase} + HIC_O_H2DTOKEN)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },
    {
        name: "hicD2HToken",
        displayName: "Device to Host Token",
        type: 'value',
        register: "D2HTOKEN",
        updateFunc: (instBase) => `HWREG(${instBase} + HIC_O_D2HTOKEN)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Module Revision
    //-------------------------------------------------------------------------
    {
        name: "hicRevision",
        displayName: "HIC Module Revision",
        type: 'value',
        register: "REV",
        updateFunc: (instBase) => `HWREG(${instBase} + HIC_O_REV)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Mode Configuration (for debugging)
    //-------------------------------------------------------------------------
    {
        name: "hicModeCr",
        displayName: "HIC Mode Config",
        type: 'value',
        register: "MODECR",
        updateFunc: (instBase) => `HWREG(${instBase} + HIC_O_MODECR)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Lock Status
    //-------------------------------------------------------------------------
    {
        name: "hicLocked",
        displayName: "HIC Registers Locked",
        type: 'led',
        register: "LOCK",
        updateFunc: (instBase) => `(HWREG(${instBase} + HIC_O_LOCK) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },
    {
        name: "hicCommitted",
        displayName: "HIC Lock Committed",
        type: 'led',
        register: "COMMIT",
        updateFunc: (instBase) => `(HWREG(${instBase} + HIC_O_COMMIT) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_HIC.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "HicRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Clear and Force registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // H2D Interrupt Clear (Write-1-to-Clear)
    { name: "H2DINTCLR", register: "HIC_H2DINTCLR" },
    // H2D Interrupt Force (Write-Only)
    { name: "H2DINTFRC", register: "HIC_H2DINTFRC" },
    // D2H Interrupt Clear (Write-1-to-Clear)
    { name: "D2HINTCLR", register: "HIC_D2HINTCLR" },
    // D2H Interrupt Force (Write-Only)
    { name: "D2HINTFRC", register: "HIC_D2HINTFRC" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
