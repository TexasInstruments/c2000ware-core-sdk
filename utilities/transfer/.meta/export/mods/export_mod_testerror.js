//=============================================================================
// export_mod_testerror.js - Test Error Export Module for CDT
//=============================================================================
// Purpose: Expose CPU RAM Test Error diagnostic information for CDT
// Devices: F28003x, F2838x (devices with TEST_ERROR_REGS)
// Reference: driverlib/<device>/driverlib/inc/hw_memcfg.h
//
// Test Error registers provide:
// - RAM test error status (correctable/uncorrectable)
// - Error address information from RAM testing
//
// NOTE: These registers are primarily used during BIST/MBIST testing
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

//-----------------------------------------------------------------------------
// Device Support Constants
//-----------------------------------------------------------------------------
const DEVICES_WITH_TEST_ERROR = [
    "F280013x", "F280015x", "F28002x", "F28003x", "F2838x", "F28P55x", "F28P65x"
];

let exportsInfo = [
    //-------------------------------------------------------------------------
    // CPU RAM Test Error Status
    //-------------------------------------------------------------------------
    {
        name: "ramTestErrSts",
        displayName: "RAM Test Error Status",
        type: 'value',
        register: "CPU_RAM_TEST_ERROR_STS",
        bitfieldInstance: "testerror",
        updateFunc: (instBase) => `HWREG(TESTERROR_BASE + MEMCFG_O_CPU_RAM_TEST_ERROR_STS)`,
        applicable: (inst) => {
            return DEVICES_WITH_TEST_ERROR.includes(deviceName);
        }
    },
    {
        name: "ramTestCorrErr",
        displayName: "RAM Test Correctable Error",
        type: 'led',
        register: "CPU_RAM_TEST_ERROR_STS.COR_ERROR",
        bitfieldInstance: "testerror",
        updateFunc: (instBase) => `((HWREG(TESTERROR_BASE + MEMCFG_O_CPU_RAM_TEST_ERROR_STS) & MEMCFG_CPU_RAM_TEST_ERROR_STS_COR_ERROR) == MEMCFG_CPU_RAM_TEST_ERROR_STS_COR_ERROR)`,
        applicable: (inst) => {
            return DEVICES_WITH_TEST_ERROR.includes(deviceName);
        }
    },
    {
        name: "ramTestUncorrErr",
        displayName: "RAM Test Uncorrectable Error",
        type: 'led',
        register: "CPU_RAM_TEST_ERROR_STS.UNC_ERROR",
        bitfieldInstance: "testerror",
        updateFunc: (instBase) => `((HWREG(TESTERROR_BASE + MEMCFG_O_CPU_RAM_TEST_ERROR_STS) & MEMCFG_CPU_RAM_TEST_ERROR_STS_UNC_ERROR) == MEMCFG_CPU_RAM_TEST_ERROR_STS_UNC_ERROR)`,
        applicable: (inst) => {
            return DEVICES_WITH_TEST_ERROR.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // CPU RAM Test Error Address
    //-------------------------------------------------------------------------
    {
        name: "ramTestErrAddr",
        displayName: "RAM Test Error Address",
        type: 'value',
        register: "CPU_RAM_TEST_ERROR_ADDR",
        bitfieldInstance: "testerror",
        updateFunc: (instBase) => `HWREG(TESTERROR_BASE + MEMCFG_O_CPU_RAM_TEST_ERROR_ADDR)`,
        applicable: (inst) => {
            return DEVICES_WITH_TEST_ERROR.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "TestErrorRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (R/W1C Clear registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // RAM Test Error Status Clear (R/W1C - Write 1 to Clear)
    { name: "CPU_RAM_TEST_ERROR_STS_CLR", register: "MEMCFG_CPU_RAM_TEST_ERROR_STS_CLR" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
