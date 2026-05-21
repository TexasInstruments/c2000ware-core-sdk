//=============================================================================
// export_mod_erad.js - ERAD (Enhanced Real-time Analysis and Diagnostics)
//                      Export Module for CDT
//=============================================================================
// Purpose: Expose ERAD diagnostic information for CDT
// Devices: F28002x, F28003x, F28004x, F2838x, F28P55x, F28P65x
// Reference: driverlib/<device>/driverlib/inc/hw_erad.h
//
// ERAD provides:
// - Hardware breakpoint (HWBP) event detection
// - Counter module (CTM) event detection
// - Debug halt status monitoring
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

//-----------------------------------------------------------------------------
// Device Support Constants
//-----------------------------------------------------------------------------
const DEVICES_WITH_ERAD = [
    "F28002x", "F28003x", "F28004x", "F2838x", "F28P55x", "F28P65x"
];

// Devices with 8 HWBP modules (some have fewer)
const DEVICES_WITH_8_HWBP = [
    "F28003x", "F28004x", "F2838x", "F28P55x", "F28P65x"
];

// Devices with 4 CTM modules
const DEVICES_WITH_4_CTM = [
    "F28002x", "F28003x", "F28004x", "F2838x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    //-------------------------------------------------------------------------
    // Global Event Status Register
    // Shows which HWBP/CTM modules have triggered events
    //-------------------------------------------------------------------------
    {
        name: "eventStatus",
        displayName: "ERAD Event Status",
        type: 'value',
        register: "GLBL_EVENT_STAT",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT)`,
        applicable: (inst) => {
            return DEVICES_WITH_ERAD.includes(deviceName);
        }
    },
    {
        name: "hwbp1Event",
        displayName: "HWBP1 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.HWBP1",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_HWBP1) == ERAD_GLBL_EVENT_STAT_HWBP1)`,
        applicable: (inst) => {
            return DEVICES_WITH_ERAD.includes(deviceName);
        }
    },
    {
        name: "hwbp2Event",
        displayName: "HWBP2 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.HWBP2",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_HWBP2) == ERAD_GLBL_EVENT_STAT_HWBP2)`,
        applicable: (inst) => {
            return DEVICES_WITH_ERAD.includes(deviceName);
        }
    },
    {
        name: "hwbp3Event",
        displayName: "HWBP3 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.HWBP3",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_HWBP3) == ERAD_GLBL_EVENT_STAT_HWBP3)`,
        applicable: (inst) => {
            return DEVICES_WITH_ERAD.includes(deviceName);
        }
    },
    {
        name: "hwbp4Event",
        displayName: "HWBP4 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.HWBP4",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_HWBP4) == ERAD_GLBL_EVENT_STAT_HWBP4)`,
        applicable: (inst) => {
            return DEVICES_WITH_ERAD.includes(deviceName);
        }
    },
    {
        name: "hwbp5Event",
        displayName: "HWBP5 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.HWBP5",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_HWBP5) == ERAD_GLBL_EVENT_STAT_HWBP5)`,
        applicable: (inst) => {
            return DEVICES_WITH_8_HWBP.includes(deviceName);
        }
    },
    {
        name: "hwbp6Event",
        displayName: "HWBP6 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.HWBP6",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_HWBP6) == ERAD_GLBL_EVENT_STAT_HWBP6)`,
        applicable: (inst) => {
            return DEVICES_WITH_8_HWBP.includes(deviceName);
        }
    },
    {
        name: "hwbp7Event",
        displayName: "HWBP7 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.HWBP7",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_HWBP7) == ERAD_GLBL_EVENT_STAT_HWBP7)`,
        applicable: (inst) => {
            return DEVICES_WITH_8_HWBP.includes(deviceName);
        }
    },
    {
        name: "hwbp8Event",
        displayName: "HWBP8 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.HWBP8",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_HWBP8) == ERAD_GLBL_EVENT_STAT_HWBP8)`,
        applicable: (inst) => {
            return DEVICES_WITH_8_HWBP.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Counter Module Events
    //-------------------------------------------------------------------------
    {
        name: "ctm1Event",
        displayName: "CTM1 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.CTM1",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_CTM1) == ERAD_GLBL_EVENT_STAT_CTM1)`,
        applicable: (inst) => {
            return DEVICES_WITH_4_CTM.includes(deviceName);
        }
    },
    {
        name: "ctm2Event",
        displayName: "CTM2 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.CTM2",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_CTM2) == ERAD_GLBL_EVENT_STAT_CTM2)`,
        applicable: (inst) => {
            return DEVICES_WITH_4_CTM.includes(deviceName);
        }
    },
    {
        name: "ctm3Event",
        displayName: "CTM3 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.CTM3",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_CTM3) == ERAD_GLBL_EVENT_STAT_CTM3)`,
        applicable: (inst) => {
            return DEVICES_WITH_4_CTM.includes(deviceName);
        }
    },
    {
        name: "ctm4Event",
        displayName: "CTM4 Event Triggered",
        type: 'led',
        register: "GLBL_EVENT_STAT.CTM4",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_EVENT_STAT) & ERAD_GLBL_EVENT_STAT_CTM4) == ERAD_GLBL_EVENT_STAT_CTM4)`,
        applicable: (inst) => {
            return DEVICES_WITH_4_CTM.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Global Halt Status Register
    // Shows which HWBP/CTM modules have caused a halt
    //-------------------------------------------------------------------------
    {
        name: "haltStatus",
        displayName: "ERAD Halt Status",
        type: 'value',
        register: "GLBL_HALT_STAT",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_HALT_STAT)`,
        applicable: (inst) => {
            return DEVICES_WITH_ERAD.includes(deviceName);
        }
    },
    {
        name: "hwbp1Halt",
        displayName: "HWBP1 Caused Halt",
        type: 'led',
        register: "GLBL_HALT_STAT.HWBP1",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_HALT_STAT) & ERAD_GLBL_HALT_STAT_HWBP1) == ERAD_GLBL_HALT_STAT_HWBP1)`,
        applicable: (inst) => {
            return DEVICES_WITH_ERAD.includes(deviceName);
        }
    },
    {
        name: "hwbp2Halt",
        displayName: "HWBP2 Caused Halt",
        type: 'led',
        register: "GLBL_HALT_STAT.HWBP2",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `((HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_HALT_STAT) & ERAD_GLBL_HALT_STAT_HWBP2) == ERAD_GLBL_HALT_STAT_HWBP2)`,
        applicable: (inst) => {
            return DEVICES_WITH_ERAD.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Global Enable Status
    //-------------------------------------------------------------------------
    {
        name: "enableStatus",
        displayName: "ERAD Enable Status",
        type: 'value',
        register: "GLBL_ENABLE",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_ENABLE)`,
        applicable: (inst) => {
            return DEVICES_WITH_ERAD.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Ownership Status
    //-------------------------------------------------------------------------
    {
        name: "owner",
        displayName: "ERAD Owner",
        type: 'value',
        register: "GLBL_OWNER.OWNER",
        bitfieldInstance: "eradglobal",
        updateFunc: (instBase) => `(HWREGH(ERAD_GLOBAL_BASE + ERAD_O_GLBL_OWNER) & ERAD_GLBL_OWNER_OWNER_M)`,
        applicable: (inst) => {
            return DEVICES_WITH_ERAD.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "EradGlobalRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Reset/Force registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Counter Reset register (Write 1 to reset counter)
    { name: "GLBL_CTM_RESET", register: "ERADGLBL_CTM_RESET" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
