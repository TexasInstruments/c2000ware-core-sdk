//=============================================================================
// export_mod_aes.js - AES Export Module for CDT
//=============================================================================
// Purpose: Expose AES encryption diagnostic information for CDT
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: AES chapter
//   - driverlib/<device>/driverlib/aes.h
//   - driverlib/<device>/driverlib/inc/hw_aes.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { getDeviceName } = exportCommon;
const deviceName = getDeviceName();

//-----------------------------------------------------------------------------
// Device Support Constants
//-----------------------------------------------------------------------------
// AES module available on select devices
const DEVICES_WITH_AES = [
    "F28003x", "F28P55x", "F28P65x"
];

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // AES Reset Status
    //-------------------------------------------------------------------------
    {
        name: "aesResetDone",
        displayName: "AES Reset Done",
        type: 'led',
        register: "SYSSTATUS.RESETDONE",
        updateFunc: (instBase) => `((HWREGH(${instBase} + AES_O_SYSSTATUS) & AES_SYSSTATUS_RESETDONE) == AES_SYSSTATUS_RESETDONE)`,
        applicable: (inst) => {
            return DEVICES_WITH_AES.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // AES Interrupt Status Flags
    //-------------------------------------------------------------------------
    {
        name: "aesContextInReady",
        displayName: "Context In Ready",
        type: 'led',
        register: "IRQSTATUS.CONTEXT_IN",
        updateFunc: (instBase) => `((HWREGH(${instBase} + AES_O_IRQSTATUS) & AES_IRQSTATUS_CONTEXT_IN) == AES_IRQSTATUS_CONTEXT_IN)`,
        applicable: (inst) => {
            return DEVICES_WITH_AES.includes(deviceName);
        }
    },
    {
        name: "aesDataInReady",
        displayName: "Data In Ready",
        type: 'led',
        register: "IRQSTATUS.DATA_IN",
        updateFunc: (instBase) => `((HWREGH(${instBase} + AES_O_IRQSTATUS) & AES_IRQSTATUS_DATA_IN) == AES_IRQSTATUS_DATA_IN)`,
        applicable: (inst) => {
            return DEVICES_WITH_AES.includes(deviceName);
        }
    },
    {
        name: "aesDataOutReady",
        displayName: "Data Out Ready",
        type: 'led',
        register: "IRQSTATUS.DATA_OUT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + AES_O_IRQSTATUS) & AES_IRQSTATUS_DATA_OUT) == AES_IRQSTATUS_DATA_OUT)`,
        applicable: (inst) => {
            return DEVICES_WITH_AES.includes(deviceName);
        }
    },
    {
        name: "aesContextOutReady",
        displayName: "Context Out Ready",
        type: 'led',
        register: "IRQSTATUS.CONTEXT_OUT",
        updateFunc: (instBase) => `((HWREGH(${instBase} + AES_O_IRQSTATUS) & AES_IRQSTATUS_CONTEXT_OUT) == AES_IRQSTATUS_CONTEXT_OUT)`,
        applicable: (inst) => {
            return DEVICES_WITH_AES.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // AES Dirty Bits (shows which registers have been accessed)
    //-------------------------------------------------------------------------
    {
        name: "aesDirtyBits",
        displayName: "AES Dirty Bits",
        type: 'value',
        register: "DIRTY_BITS",
        updateFunc: (instBase) => `HWREG(${instBase} + AES_O_DIRTY_BITS)`,
        applicable: (inst) => {
            return DEVICES_WITH_AES.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // AES Module Revision
    //-------------------------------------------------------------------------
    {
        name: "aesRevision",
        displayName: "AES Module Revision",
        type: 'value',
        register: "REV",
        updateFunc: (instBase) => `HWREG(${instBase} + AES_O_REV)`,
        applicable: (inst) => {
            return DEVICES_WITH_AES.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // AES Crypto Data Length (for operation tracking)
    //-------------------------------------------------------------------------
    {
        name: "aesCryptoLength",
        displayName: "Crypto Data Length",
        type: 'value',
        register: "C_LENGTH_0",
        updateFunc: (instBase) => `HWREG(${instBase} + AES_O_C_LENGTH_0)`,
        applicable: (inst) => {
            return DEVICES_WITH_AES.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // AES Authentication Length (for AAD tracking)
    //-------------------------------------------------------------------------
    {
        name: "aesAuthLength",
        displayName: "Auth Data Length (AAD)",
        type: 'value',
        register: "AUTH_LENGTH",
        updateFunc: (instBase) => `HWREG(${instBase} + AES_O_AUTH_LENGTH)`,
        applicable: (inst) => {
            return DEVICES_WITH_AES.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "AesRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Key registers should not be read for security)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Key registers - DO NOT READ (security sensitive)
    { name: "KEY1_0", register: "AES_KEY1_0" },
    { name: "KEY1_1", register: "AES_KEY1_1" },
    { name: "KEY1_2", register: "AES_KEY1_2" },
    { name: "KEY1_3", register: "AES_KEY1_3" },
    { name: "KEY1_4", register: "AES_KEY1_4" },
    { name: "KEY1_5", register: "AES_KEY1_5" },
    { name: "KEY1_6", register: "AES_KEY1_6" },
    { name: "KEY1_7", register: "AES_KEY1_7" },
    { name: "KEY2_0", register: "AES_KEY2_0" },
    { name: "KEY2_1", register: "AES_KEY2_1" },
    { name: "KEY2_2", register: "AES_KEY2_2" },
    { name: "KEY2_3", register: "AES_KEY2_3" },
    { name: "KEY2_4", register: "AES_KEY2_4" },
    { name: "KEY2_5", register: "AES_KEY2_5" },
    { name: "KEY2_6", register: "AES_KEY2_6" },
    { name: "KEY2_7", register: "AES_KEY2_7" },
    // IV registers - security sensitive
    { name: "IV_IN_OUT_0", register: "AES_IV_IN_OUT_0" },
    { name: "IV_IN_OUT_1", register: "AES_IV_IN_OUT_1" },
    { name: "IV_IN_OUT_2", register: "AES_IV_IN_OUT_2" },
    { name: "IV_IN_OUT_3", register: "AES_IV_IN_OUT_3" },
    // Data registers - may contain sensitive data
    { name: "DATA_IN_OUT_0", register: "AES_DATA_IN_OUT_0" },
    { name: "DATA_IN_OUT_1", register: "AES_DATA_IN_OUT_1" },
    { name: "DATA_IN_OUT_2", register: "AES_DATA_IN_OUT_2" },
    { name: "DATA_IN_OUT_3", register: "AES_DATA_IN_OUT_3" },
    // Tag/Hash output - security sensitive
    { name: "TAG_OUT_0", register: "AES_TAG_OUT_0" },
    { name: "TAG_OUT_1", register: "AES_TAG_OUT_1" },
    { name: "TAG_OUT_2", register: "AES_TAG_OUT_2" },
    { name: "TAG_OUT_3", register: "AES_TAG_OUT_3" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
