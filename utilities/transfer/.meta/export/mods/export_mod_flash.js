//=============================================================================
// export_mod_flash.js - Flash Export Module for CDT
//=============================================================================
// Purpose: Expose Flash diagnostic information for Clinic Diagnostic Tool
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: Flash chapter
//   - driverlib/<device>/driverlib/flash.h
//   - driverlib/<device>/driverlib/flash.c
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// ECC support varies by device
const DEVICES_WITH_ECC = DEVICES_WITH_CDT_SUPPORT;  // All Gen3 have ECC

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // Flash Error Status
    //-------------------------------------------------------------------------
    {
        name: "flashUncErr",
        displayName: "Flash Uncorrectable Error",
        type: 'led',
        register: "ERR_STATUS.UNC_ERR_L/H",
        updateFunc: (instBase) => `((HWREG(FLASH0ECC_BASE + FLASH_O_ERR_STATUS) & (FLASH_ERR_STATUS_UNC_ERR_L | FLASH_ERR_STATUS_UNC_ERR_H)) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "flashCorrErr",
        displayName: "Flash Correctable Error",
        type: 'led',
        register: "ERR_INTFLG.SINGLE_ERR_INTFLG",
        updateFunc: (instBase) => `((HWREGH(FLASH0ECC_BASE + FLASH_O_ERR_INTFLG) & FLASH_ERR_INTFLG_SINGLE_ERR_INTFLG) == FLASH_ERR_INTFLG_SINGLE_ERR_INTFLG)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Flash Pump Status
    //-------------------------------------------------------------------------
    {
        name: "flashPumpReady",
        displayName: "Flash Pump Ready",
        type: 'led',
        register: "FBPRDY.PUMPRDY",
        updateFunc: (instBase) => `((HWREGH(FLASH0CTRL_BASE + FLASH_O_FBPRDY) & FLASH_FBPRDY_PUMPRDY) == FLASH_FBPRDY_PUMPRDY)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Flash Wait States Configuration
    //-------------------------------------------------------------------------
    {
        name: "flashWaitStates",
        displayName: "Flash Random Wait States",
        type: 'value',
        register: "FRDCNTL.RWAIT",
        updateFunc: (instBase) => `((HWREGH(FLASH0CTRL_BASE + FLASH_O_FRDCNTL) & FLASH_FRDCNTL_RWAIT_M) >> FLASH_FRDCNTL_RWAIT_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Flash Bank Power Mode
    //-------------------------------------------------------------------------
    {
        name: "flashBankPwrMode",
        displayName: "Flash Bank Power Mode",
        type: 'value',
        register: "FBFALLBACK.BNKPWR0",
        // Returns 0=Sleep, 1=Standby, 2=Reserved, 3=Active
        updateFunc: (instBase) => `((HWREGH(FLASH0CTRL_BASE + FLASH_O_FBFALLBACK) & FLASH_FBFALLBACK_BNKPWR0_M) >> FLASH_FBFALLBACK_BNKPWR0_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Flash Prefetch Configuration
    //-------------------------------------------------------------------------
    {
        name: "flashPrefetchEn",
        displayName: "Flash Prefetch Enabled",
        type: 'led',
        register: "FRD_INTF_CTRL.PREFETCH_EN",
        updateFunc: (instBase) => `((HWREGH(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) & FLASH_FRD_INTF_CTRL_PREFETCH_EN) == FLASH_FRD_INTF_CTRL_PREFETCH_EN)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
    {
        name: "flashDataCacheEn",
        displayName: "Flash Data Cache Enabled",
        type: 'led',
        register: "FRD_INTF_CTRL.DATA_CACHE_EN",
        updateFunc: (instBase) => `((HWREGH(FLASH0CTRL_BASE + FLASH_O_FRD_INTF_CTRL) & FLASH_FRD_INTF_CTRL_DATA_CACHE_EN) == FLASH_FRD_INTF_CTRL_DATA_CACHE_EN)`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // ECC Status
    //-------------------------------------------------------------------------
    {
        name: "eccSingleBitErr",
        displayName: "ECC Single-Bit Error (Corrected)",
        type: 'led',
        register: "ERR_STATUS.FAIL_0_L/FAIL_1_L/H",
        updateFunc: (instBase) => `((HWREG(FLASH0ECC_BASE + FLASH_O_ERR_STATUS) & (FLASH_ERR_STATUS_FAIL_0_L | FLASH_ERR_STATUS_FAIL_1_L | FLASH_ERR_STATUS_FAIL_0_H | FLASH_ERR_STATUS_FAIL_1_H)) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_ECC.includes(deviceName);
        }
    },
    {
        name: "eccDoubleBitErr",
        displayName: "ECC Double-Bit Error (Fatal)",
        type: 'led',
        register: "ERR_INTFLG.UNC_ERR_INTFLG",
        updateFunc: (instBase) => `((HWREGH(FLASH0ECC_BASE + FLASH_O_ERR_INTFLG) & FLASH_ERR_INTFLG_UNC_ERR_INTFLG) == FLASH_ERR_INTFLG_UNC_ERR_INTFLG)`,
        applicable: (inst) => {
            return DEVICES_WITH_ECC.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // OTP/Security Status (read-only)
    //-------------------------------------------------------------------------
    {
        name: "otpSecured",
        displayName: "Device Secured (OTP)",
        type: 'led',
        register: "DCSM_Z1_CR.ARMED && !UNSECURE",
        // Secured = ARMED is set AND UNSECURE is not set
        updateFunc: (instBase) => `(((HWREG(DCSM_Z1_BASE + DCSM_O_Z1_CR) & DCSM_Z1_CR_ARMED) != 0) && ((HWREG(DCSM_Z1_BASE + DCSM_O_Z1_CR) & DCSM_Z1_CR_UNSECURE) == 0))`,
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "Flash0CtrlRegs" },
    "ecc": (instName) => { return "Flash0EccRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Write-1-to-Clear registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // ECC error clear registers (Write-1-to-Clear)
    { name: "ERR_STATUS_CLR", register: "FLASHERR_STATUS_CLR" },
    { name: "ERR_INTCLR", register: "FLASHERR_INTCLR" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
