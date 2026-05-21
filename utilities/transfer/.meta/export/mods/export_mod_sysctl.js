//=============================================================================
// export_mod_sysctl.js - System Control Export Module for CDT
//=============================================================================
// Purpose: Expose System Control diagnostic information for CDT
// Devices: All Gen3 devices
// Reference: driverlib/<device>/driverlib/inc/hw_sysctl.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, getDeviceName } = exportCommon;

//-----------------------------------------------------------------------------
// PartID Lookup Tables
// Source: Device datasheets and TRMs
//-----------------------------------------------------------------------------

// PARTIDL PIN_COUNT field (bits 10:8) - Package pin count
// Encoding confirmed from GUI runtime PARTIZL decode (index.js.xdt PIN_COUNT_MAP).
// The 3-bit field (values 0-7) maps directly to package pin count:
//   0 = Unknown/Reserved
//   1 = 32-pin  (F280013x/F280015x QFN)
//   2 = 48-pin  (F280013x/F280015x/F28002x/F28003x TQFP)
//   3 = 56-pin  (F28004x BGA-56)
//   4 = 64-pin  (F280015x/F28002x/F28003x/F28004x LQFP)
//   5 = 80-pin  (F28002x/F28003x/F28004x LQFP)
//   6 = 100-pin (F28003x/F28004x/F2807x/F2837x LQFP)
//   7 = 176-pin (F2807x/F2837x/F2838x/F28P65x LQFP)
// Note: BGA packages for 337-pin (F2837xD, F2838x) and F28P65x multi-die
//       variants are identified by device family, not PIN_COUNT alone.
const PIN_COUNT_MAP = {
    0: "Unknown",
    1: "32-pin",
    2: "48-pin",
    3: "56-pin",
    4: "64-pin",
    5: "80-pin",
    6: "100-pin",
    7: "176-pin"
};

// PARTIDL QUAL field (bits 7:6) - Qualification status
// Encoding confirmed from GUI runtime PARTIZL decode (index.js.xdt QUAL_MAP).
// IMPORTANT: 3 = Production (TMS), NOT 0. The field increases with qualification level.
//   XS = eXperimental Silicon (prototype / very early sample)
//   XM = eXperimental/Mature (TMX — engineering sample)
//   XP = eXperimental Pre-production (TMP — pre-qualification)
//   TMS = Texas Instruments Mature Silicon (fully production-qualified)
const QUAL_MAP = {
    0: "XS (Prototype)",        // Very early engineering sample
    1: "XM (Experimental)",     // TMX — engineering sample
    2: "XP (Pre-production)",   // TMP — pre-qualification sample
    3: "TMS (Production)"       // Fully qualified production silicon
};

// PARTIDH DEVICE_CLASS_ID field (bits 31:24)
// Note: Values confirmed from silicon readings and GUI runtime decode (index.js.xdt).
// IMPORTANT: F280015x shares CLASS_ID 0x07 with F2807x. They are distinguished
//   by PARTNO field — the GUI uses SysConfig device name to resolve the ambiguity.
// Gen2 devices (0x00-0x04) are present in the field but CDT support added for Gen2.
const DEVICE_CLASS_MAP = {
    // Gen2 (CDT now supported)
    0x00: "F2800x",             // Legacy Piccolo
    0x01: "F2802x/F2803x",      // Legacy Piccolo
    0x02: "F2805x",             // Legacy Piccolo
    0x03: "F2806x",             // Legacy Piccolo
    0x04: "F2833x/F2823x",      // Legacy Delfino
    // Gen3
    0x05: "F2837xS",            // Delfino single-core
    0x06: "F2837xD",            // Delfino dual-core
    0x07: "F2807x/F280015x",    // SHARED: Piccolo F2807x AND Entry F280015x — use PARTNO to distinguish
    0x08: "F28004x",            // Piccolo
    0x09: "F28002x",            // Piccolo
    0x0A: "F2838x",             // Delfino dual-core + CM
    0x0B: "F28003x",            // Piccolo
    0x0C: "F280013x",           // Entry Piccolo
    // 0x0D: Reserved (not assigned to any production device)
    0x0E: "F28P65x",            // Next-gen Delfino
    0x0F: "F28P55x"             // Next-gen Piccolo
};

// PARTIDH FAMILY field (bits 15:8)
// Note: FAMILY encoding is device-specific and may not directly map to marketing names.
// Piccolo = Entry-level (F2802x-F28004x, F280013x-F280015x)
// Delfino = High-performance (F2833x, F2837xD/S, F2838x, F28P65x)
// Values shown are typical but may vary by device revision.
const FAMILY_MAP = {
    0x00: "Piccolo",     // Entry-level C2000
    0x01: "Delfino",     // High-performance C2000
    0x02: "Gen3",        // Latest generation C2000 (F28P55x, F28P65x)
    0x03: "Reserved"
};

//-----------------------------------------------------------------------------
// Device Feature Matrix
// Defines hardware capabilities and register paths for each device family
// This allows the CDT to scale to support future devices
//-----------------------------------------------------------------------------
const DEVICE_FEATURES = {
    //-------------------------------------------------------------------------
    // Gen2 Devices (use SysCtrlRegs for system control)
    //-------------------------------------------------------------------------
    "F2802x":   { dualCore: false, ethercat: false, generation: 2, regStyle: "GEN2" },
    "F2803x":   { dualCore: false, ethercat: false, generation: 2, regStyle: "GEN2" },
    "F2805x":   { dualCore: false, ethercat: false, generation: 2, regStyle: "GEN2" },
    "F2806x":   { dualCore: false, ethercat: false, generation: 2, regStyle: "GEN2" },
    //-------------------------------------------------------------------------
    // Gen3 Devices (use ClkCfgRegs, CpuSysRegs, DevCfgRegs)
    //-------------------------------------------------------------------------
    // Entry-level single-core devices
    "F280013x": { dualCore: false, ethercat: false, generation: 3 },
    "F280015x": { dualCore: false, ethercat: false, generation: 3 },
    "F28002x":  { dualCore: false, ethercat: false, generation: 3 },
    "F28003x":  { dualCore: false, ethercat: false, generation: 3 },
    "F28004x":  { dualCore: false, ethercat: false, generation: 3 },
    "F2807x":   { dualCore: false, ethercat: false, generation: 3 },
    // Single-core Delfino
    "F2837xS":  { dualCore: false, ethercat: false, generation: 3 },
    // Dual-core devices (DC register structure)
    "F2837xD":  { dualCore: true, ethercat: false, generation: 3, regStyle: "DC" },
    "F2838x":   { dualCore: true, ethercat: true,  generation: 3, regStyle: "DC" },
    // Newer devices (MCUCNF register structure)
    "F28P55x":  { dualCore: false, ethercat: false, generation: 3, regStyle: "MCUCNF" },
    "F28P65x":  { dualCore: true, ethercat: true,  generation: 3, regStyle: "MCUCNF" },
};

// Register paths for different device capability features
// Maps feature -> device family -> register path
// If no register path exists for a device, the feature is shown as "hardware present"
const FEATURE_REGISTERS = {
    dualCore: {
        // MCUCNF style (F28P65x) - has runtime configuration register
        "F28P65x": "DevCfgRegs.MCUCNF0.DUAL_CORE",
        // DC style devices (F2837xD, F2838x) are inherently dual-core
        // No runtime register - dual-core is a fixed hardware feature
    },
    ethercat: {
        // MCUCNF style (F28P65x) - has runtime configuration register
        "F28P65x": "DevCfgRegs.MCUCNF2.ETHERCAT",
        // F2838x has EtherCAT as fixed hardware feature - no capability register
        // Could check PCLKCR16.ETHERCAT for clock enable status if needed
    }
};

// Helper to check if device has a feature
function deviceHasFeature(deviceName, feature) {
    const deviceInfo = DEVICE_FEATURES[deviceName];
    return deviceInfo ? deviceInfo[feature] : false;
}

// Helper to get register path for a feature on a device
function getFeatureRegister(deviceName, feature) {
    const featureRegs = FEATURE_REGISTERS[feature];
    return featureRegs ? featureRegs[deviceName] : null;
}

// Devices that support dual-core (hardware capability)
const DEVICES_DUAL_CORE = Object.keys(DEVICE_FEATURES).filter(d => DEVICE_FEATURES[d].dualCore);

// Devices that have EtherCAT (hardware capability)
const DEVICES_WITH_ETHERCAT = Object.keys(DEVICE_FEATURES).filter(d => DEVICE_FEATURES[d].ethercat);

let exportsInfo = [
    //-------------------------------------------------------------------------
    // Device Identification
    // Order: Device, Silicon Rev, Device Info, Debugger Connected, Extended Info, Last Reset
    // Note: Last Reset is positioned last among text entries so it appears just above
    //       Program Execution Location in the System panel
    //-------------------------------------------------------------------------
    {
        name: "partidh",
        displayName: "Device Class",
        description: "C2000 device family/class identifier from PARTIDH register.",
        type: 'text',
        register: "PARTIDH",
        baseRegister: "PARTIDH",
        bitfieldInstance: "devcfg",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
    {
        name: "revid",
        displayName: "Silicon Revision",
        description: "Silicon revision number. Higher values = newer silicon with errata fixes applied.",
        type: 'text',
        register: "REVID",
        baseRegister: "REVID",
        bitfieldInstance: "devcfg",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
    {
        name: "partidl",
        displayName: "Flash/Package",
        description: "Flash memory size (KB) and package pin count from PARTIDL register.",
        type: 'text',
        register: "PARTIDL",
        baseRegister: "PARTIDL",
        bitfieldInstance: "devcfg",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
    {
        name: "tapStatus",
        displayName: "Debugger Connected",
        description: "JTAG/SWD debugger connection status from TAP_STATUS.DCON. Green = Debugger attached.",
        type: 'led',
        register: "TAP_STATUS.DCON",
        baseRegister: "TAP_STATUS",
        bitMask: 0x80000000,  // Bit 31: DCON - Debugger Connect Indication
        bitfieldInstance: "devcfg",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
    // Note: PIE Vector Error moved to export_mod_interrupt.js

    //-------------------------------------------------------------------------
    // Extended Device Information (from PARTIDL/PARTIDH registers)
    //-------------------------------------------------------------------------
    {
        name: "qualStatus",
        displayName: "Silicon Qual",
        description: "Silicon qualification level: XS=Prototype, XM=Experimental, XP=Pre-production, Production=Fully qualified",
        type: 'text',
        register: "PARTIDL.QUAL",
        baseRegister: "PARTIDL",
        bitfieldInstance: "devcfg",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
    {
        name: "deviceFamily",
        displayName: "Device Family",
        description: "C2000 device family: Piccolo (entry-level), Delfino (high-performance), Gen3 (latest generation)",
        type: 'text',
        register: "PARTIDH.FAMILY",
        baseRegister: "PARTIDH",
        bitfieldInstance: "devcfg",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
    {
        name: "partNumber",
        displayName: "Silicon PartNo",
        description: "Exact device part number from silicon PARTIDH register. Maps to TMS320F28xxxx orderable part.",
        type: 'text',
        register: "PARTIDH.PARTNO",
        baseRegister: "PARTIDH",
        bitfieldInstance: "devcfg",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
    {
        name: "resetSource",
        displayName: "Last Reset Cause",
        description: "Most recent reset source: POR=Power-on, XRSn=External pin, WDRSn=Watchdog timeout, NMIWDRSn=NMI Watchdog",
        type: 'text',
        register: "RESC",
        baseRegister: "RESC",
        bitfieldInstance: "cpusys",
        applicable: (inst) => {
            return DEVICES_WITH_CDT_SUPPORT.includes(getDeviceName());
        }
    },
    {
        name: "dualCore",
        displayName: "Dual Core",
        description: "Dual-core device capability. Green = dual-core hardware present.",
        type: 'led',
        ledType: 'feature',  // Green when present, grey when not
        // Register varies by device - handled dynamically in GUI
        getRegister: (deviceName) => getFeatureRegister(deviceName, 'dualCore'),
        bitMask: 0x1,
        bitfieldInstance: "devcfg",
        applicable: (inst) => {
            // Show for all dual-core capable devices
            return deviceHasFeature(getDeviceName(), 'dualCore');
        }
    },
    {
        name: "ethercat",
        displayName: "EtherCAT",
        description: "EtherCAT peripheral availability. Green = EtherCAT hardware present.",
        type: 'led',
        ledType: 'feature',  // Green when present, grey when not
        // Register varies by device - handled dynamically in GUI
        getRegister: (deviceName) => getFeatureRegister(deviceName, 'ethercat'),
        bitMask: 0x1,
        bitfieldInstance: "devcfg",
        applicable: (inst) => {
            // Show for all EtherCAT capable devices
            return deviceHasFeature(getDeviceName(), 'ethercat');
        }
    },
    //-------------------------------------------------------------------------
    // Memory Access Protection Violation Flags
    //-------------------------------------------------------------------------
    {
        name: "cpuwriteviolation",
        displayName: "Master CPU Write Access Violation",
        type: 'led',
        register: "MAVFLG.CPUWRITE",
        bitfieldInstance: "accessprotection",
        updateFunc: (instBase) => `((HWREGH(ACCESSPROTECTION_BASE + MEMCFG_O_MAVFLG) & MEMCFG_MAVFLG_CPUWRITE) == MEMCFG_MAVFLG_CPUWRITE)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(getDeviceName()) ? true : false);
        }
    },
    {
        name: "cpufetchviolation",
        displayName: "Master CPU Fetch Access Violation",
        type: 'led',
        register: "MAVFLG.CPUFETCH",
        bitfieldInstance: "accessprotection",
        updateFunc: (instBase) => `((HWREGH(ACCESSPROTECTION_BASE + MEMCFG_O_MAVFLG) & MEMCFG_MAVFLG_CPUFETCH) == MEMCFG_MAVFLG_CPUFETCH)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(getDeviceName()) ? true : false);
        }
    },
    //-------------------------------------------------------------------------
    // PLL / Clock Status Flags
    //-------------------------------------------------------------------------
    {
        name: "pllreflosts",
        displayName: "SYSPLL 'Reference Lost' Event Occured",
        type: 'led',
        register: "SYSPLLSTS.REF_LOSTS",
        bitfieldInstance: "clkcfg",
        updateFunc: (instBase) => `((HWREGH(CLKCFG_BASE + SYSCTL_O_SYSPLLSTS) & SYSCTL_SYSPLLSTS_REF_LOSTS) == SYSCTL_SYSPLLSTS_REF_LOSTS)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x"].includes(getDeviceName()) ? true : false);
        }
    },
    {
        name: "mclksts",
        displayName: "OSCCLK Detected Missing",
        type: 'led',
        register: "MCDCR.MCLKSTS",
        bitfieldInstance: "clkcfg",
        updateFunc: (instBase) => `((HWREGH(CLKCFG_BASE + SYSCTL_O_MCDCR) & SYSCTL_MCDCR_MCLKSTS) == SYSCTL_MCDCR_MCLKSTS)`,
        applicable: (inst) => {
            return (["F280013x", "F280015x", "F28003x"].includes(getDeviceName()) ? true : false);
        }
    },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "DevCfgRegs" },
    "nmi": (instName) => { return "NmiIntruptRegs" },
    // Gen2 register structures
    "sysctrl": (instName) => { return "SysCtrlRegs" },     // Gen2 system control
    "syspwrctrl": (instName) => { return "SysPwrCtrlRegs" }, // Gen2 power control
    // Gen3 register structures
    "clkcfg": (instName) => { return "ClkCfgRegs" },
    "cpusys": (instName) => { return "CpuSysRegs" },
    "devcfg": (instName) => { return "DevCfgRegs" },
};

let exportsRegisterSkips = [
    // Reset cause clear (Write-1-to-Clear)
    { name: "RESCCLR", register: "SYSCTL_RESCCLR" },
    // System error interrupt clear/set registers
    { name: "SYS_ERR_INT_CLR", register: "SYSCTL_SYS_ERR_INT_CLR" },
    { name: "SYS_ERR_INT_SET", register: "SYSCTL_SYS_ERR_INT_SET" },
    // NMI flag clear/force registers
    { name: "NMIFLGCLR", register: "NMI_FLGCLR" },
    { name: "NMIFLGFRC", register: "NMI_FLGFRC" },
];

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
    PIN_COUNT_MAP: PIN_COUNT_MAP,
    QUAL_MAP: QUAL_MAP,
    DEVICE_CLASS_MAP: DEVICE_CLASS_MAP,
    FAMILY_MAP: FAMILY_MAP,
    // Device feature matrix and helpers for scalable device support
    DEVICE_FEATURES: DEVICE_FEATURES,
    FEATURE_REGISTERS: FEATURE_REGISTERS,
    deviceHasFeature: deviceHasFeature,
    getFeatureRegister: getFeatureRegister,
    DEVICES_DUAL_CORE: DEVICES_DUAL_CORE,
    DEVICES_WITH_ETHERCAT: DEVICES_WITH_ETHERCAT,
};
