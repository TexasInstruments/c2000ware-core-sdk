//=============================================================================
// export_mod_hrpwm.js - HRPWM Export Module for CDT
//=============================================================================
// Purpose: Expose High-Resolution PWM diagnostic information for CDT
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: HRPWM chapter
//   - driverlib/<device>/driverlib/hrpwm.h
//   - driverlib/<device>/driverlib/hrpwm.c
//   - SFO Library User Guide
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_HRPWM, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// Note: HRPWM requires SYSCLK >= 60MHz for proper MEP calibration

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // HRPWM Enable Status
    //-------------------------------------------------------------------------
    {
        name: "hrpwmEnabled",
        displayName: "HRPWM Enabled",
        type: 'led',
        register: "HRCNFG.EDGMODE",  // Check if HRPWM is configured
        updateFunc: (instBase) => `((HWREGH(${instBase} + HRPWM_O_HRCNFG) & HRPWM_HRCNFG_EDGMODE_M) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRPWM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // SFO Calibration Status
    // Note: SFO status is typically stored in a global variable, not a register
    //-------------------------------------------------------------------------
    {
        name: "sfoStatus",
        displayName: "SFO Calibration Status",
        type: 'value',
        register: "HRMSTEP (proxy for SFO)",
        // SFO_status is a global variable, cannot read via register
        // Instead, report HRMSTEP value: 0=Not calibrated, >0=Calibrated
        // User must interpret: 0=SFO_INCOMPLETE/ERROR, >0=SFO_COMPLETE
        updateFunc: (instBase) => `((HWREGH(${instBase} + HRPWM_O_HRMSTEP) & HRPWM_HRMSTEP_HRMSTEP_M) > 0 ? 1 : 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRPWM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // MEP Scale Factor
    //-------------------------------------------------------------------------
    {
        name: "mepScaleFactor",
        displayName: "MEP Scale Factor",
        type: 'value',
        register: "HRMSTEP.HRMSTEP",
        updateFunc: (instBase) => `((HWREGH(${instBase} + HRPWM_O_HRMSTEP) & HRPWM_HRMSTEP_HRMSTEP_M))`,
        applicable: (inst) => {
            return DEVICES_WITH_HRPWM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // HR Duty Cycle / Edge Delay Values
    //-------------------------------------------------------------------------
    {
        name: "hrCmpaHr",
        displayName: "CMPA HR Extension",
        type: 'value',
        register: "CMPA.CMPAHR",
        // CMPAHR occupies bits [15:8] of the lower 16-bit half of CMPA.
        // HRPWM_CMPA_CMPAHR_M = 0xFF00, HRPWM_CMPA_CMPAHR_S = 8 (Ref: hw_epwm.h)
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_CMPA) & HRPWM_CMPA_CMPAHR_M) >> HRPWM_CMPA_CMPAHR_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRPWM.includes(deviceName);
        }
    },
    {
        name: "hrCmpbHr",
        displayName: "CMPB HR Extension",
        type: 'value',
        register: "CMPB.CMPBHR",
        // CMPBHR occupies bits [15:8] of the lower 16-bit half of CMPB.
        // HRPWM_CMPB_CMPBHR_M = 0xFF00, HRPWM_CMPB_CMPBHR_S = 8 (Ref: hw_epwm.h)
        updateFunc: (instBase) => `((HWREGH(${instBase} + EPWM_O_CMPB) & HRPWM_CMPB_CMPBHR_M) >> HRPWM_CMPB_CMPBHR_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRPWM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Auto-Conversion Mode Status
    //-------------------------------------------------------------------------
    {
        name: "hrAutoConvEn",
        displayName: "HR Auto-Conversion Enabled",
        type: 'led',
        register: "HRCNFG.AUTOCONV",
        updateFunc: (instBase) => `((HWREGH(${instBase} + HRPWM_O_HRCNFG) & HRPWM_HRCNFG_AUTOCONV) == HRPWM_HRCNFG_AUTOCONV)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRPWM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // HR Edge Mode
    //-------------------------------------------------------------------------
    {
        name: "hrEdgeMode",
        displayName: "HR Edge Mode",
        type: 'value',
        register: "HRCNFG.EDGMODE",
        // 0=Disabled, 1=Rising, 2=Falling, 3=Both
        updateFunc: (instBase) => `((HWREGH(${instBase} + HRPWM_O_HRCNFG) & HRPWM_HRCNFG_EDGMODE_M) >> HRPWM_HRCNFG_EDGMODE_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRPWM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // HR Control Mode
    //-------------------------------------------------------------------------
    {
        name: "hrCtlMode",
        displayName: "HR Control Mode",
        type: 'value',
        register: "HRCNFG.CTLMODE",
        // 0=Duty, 1=Phase
        updateFunc: (instBase) => `((HWREGH(${instBase} + HRPWM_O_HRCNFG) & HRPWM_HRCNFG_CTLMODE) >> 2)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRPWM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // HR Period/Phase Load Status
    //-------------------------------------------------------------------------
    {
        name: "hrPrdLoaded",
        displayName: "HR Phase Load Enabled",
        type: 'led',
        register: "HRPCTL.TBPHSHRLOADE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + HRPWM_O_HRPCTL) & HRPWM_HRPCTL_TBPHSHRLOADE) == HRPWM_HRPCTL_TBPHSHRLOADE)`,
        applicable: (inst) => {
            return DEVICES_WITH_HRPWM.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "EPwm" + instName + "Regs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // None typically needed
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
