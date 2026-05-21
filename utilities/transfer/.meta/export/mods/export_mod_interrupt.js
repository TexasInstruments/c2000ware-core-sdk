//=============================================================================
// export_mod_interrupt.js - Interrupt Diagnostics Export Module for CDT
//=============================================================================
// Purpose: Expose Interrupt diagnostic information for CDT
// Devices: All Gen3 devices
// Reference: driverlib/<device>/driverlib/inc/hw_pie.h, hw_nmi.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, getDeviceName } = exportCommon;

// Devices with PIE Vector Error NMI support
const DEVICES_WITH_PIEVECTERR = [
    "F28002x", "F28004x", "F2838x", "F28P55x", "F28P65x"
];

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // PIE Vector Error
    // NMI flag indicating invalid PIE vector fetch
    //-------------------------------------------------------------------------
    {
        name: "pievecterr",
        displayName: "PIE Vector Error",
        description: "PIE vector fetch error - interrupt vector may be corrupted or misconfigured.",
        type: 'led',
        category: 'nmi_error',
        register: "NMIFLG.PIEVECTERR",
        baseRegister: "NMIFLG",
        bitMask: 0x40,  // Bit 6
        bitfieldInstance: "nmi",
        applicable: (inst) => {
            return DEVICES_WITH_PIEVECTERR.includes(getDeviceName());
        }
    },

    //-------------------------------------------------------------------------
    // PIE ACK Status
    // Shows which PIE groups have pending interrupts
    //-------------------------------------------------------------------------
    {
        name: "pieack",
        displayName: "PIE ACK Pending",
        description: "PIE acknowledgment register - shows groups with pending interrupts awaiting ACK.",
        type: 'led',
        category: 'status',
        register: "PIEACK.all",
        baseRegister: "PIEACK",
        bitMask: 0xFFFF,  // All 12 groups
        bitfieldInstance: "pie",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },

    //-------------------------------------------------------------------------
    // PIE Control Register - ENPIE
    // Indicates if PIE is enabled
    //-------------------------------------------------------------------------
    {
        name: "pieEnable",
        displayName: "PIE Enabled",
        description: "PIE (Peripheral Interrupt Expansion) module enable status.",
        type: 'led',
        category: 'config',
        register: "PIECTRL.ENPIE",
        baseRegister: "PIECTRL",
        bitMask: 0x1,  // Bit 0
        bitfieldInstance: "pie",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },

    //-------------------------------------------------------------------------
    // NMI Watchdog Active
    //-------------------------------------------------------------------------
    {
        name: "nmiwdactive",
        displayName: "NMI Watchdog Active",
        description: "NMI watchdog is counting down. System reset if not cleared in time.",
        type: 'led',
        ledColor: 'warning',  // Orange - indicates active watchdog (caution, not error)
        category: 'nmi_status',
        register: "NMICFG.NMIE",
        baseRegister: "NMICFG",
        bitMask: 0x1,  // Bit 0
        bitfieldInstance: "nmi",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },

    //-------------------------------------------------------------------------
    // NMI Flag - Any NMI pending
    //-------------------------------------------------------------------------
    {
        name: "nmiint",
        displayName: "NMI Pending",
        description: "Non-maskable interrupt flag is set. Check other NMI sources.",
        type: 'led',
        category: 'nmi_status',
        register: "NMIFLG.NMIINT",
        baseRegister: "NMIFLG",
        bitMask: 0x1,  // Bit 0
        bitfieldInstance: "nmi",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "NmiIntruptRegs" },
    "nmi": (instName) => { return "NmiIntruptRegs" },
    "pie": (instName) => { return "PieCtrlRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // NMI flag clear/force registers
    { name: "NMIFLGCLR", register: "NMI_FLGCLR" },
    { name: "NMIFLGFRC", register: "NMI_FLGFRC" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
    DEVICES_WITH_PIEVECTERR: DEVICES_WITH_PIEVECTERR,
};
