//=============================================================================
// export_mod_fsirx.js - FSI RX Export Module for CDT
//=============================================================================
// Purpose: Expose Fast Serial Interface RX diagnostic information for CDT
// Devices: F28002x, F28003x, F28004x, F2838x, F28P55x, F28P65x
// Reference: driverlib/<device>/driverlib/inc/hw_fsi.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_FSI, DEVICES_WITH_FSI_ERROR_TAG_MATCH, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// Note: ERROR_TAG_MATCH bit not available on F28004x (validated via hw_fsi.h)
// Using centralized DEVICES_WITH_FSI_ERROR_TAG_MATCH from device_constants.js
const DEVICES_WITH_ERROR_TAG_MATCH = DEVICES_WITH_FSI_ERROR_TAG_MATCH;

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
// LED Color Semantics: RED = error condition, GREEN = no error
//-----------------------------------------------------------------------------
let exportsInfo = [
    {
        name: "rxerrtagmatch",
        displayName: "RX Error Tag Match",
        description: "Error tag received from TX matches expected error condition.\nRED = Error tag match detected (TX signaled an error)\nGREEN = No error tag match",
        type: 'led',
        register: "RX_EVT_STS.ERROR_TAG_MATCH",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_ERROR_TAG_MATCH) == FSI_RX_EVT_STS_ERROR_TAG_MATCH)`,
        applicable: (inst) => {
            // ERROR_TAG_MATCH not available on F28004x (validated via hw_fsi.h)
            return DEVICES_WITH_ERROR_TAG_MATCH.includes(deviceName);
        },
    },
    {
        name: "rxframeoverrun",
        displayName: "RX Frame Overrun",
        description: "New frame received before previous frame was processed.\nRED = Frame overrun error (data loss likely)\nGREEN = No frame overrun",
        type: 'led',
        register: "RX_EVT_STS.FRAME_OVERRUN",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_FRAME_OVERRUN) == FSI_RX_EVT_STS_FRAME_OVERRUN)`,
        applicable: (inst) => {
            return DEVICES_WITH_FSI.includes(deviceName);
        },
    },
    {
        name: "rxerrframe",
        displayName: "RX Error Frame",
        description: "Error frame type received from transmitter.\nRED = Error frame received (TX sent error notification)\nGREEN = No error frame received",
        type: 'led',
        register: "RX_EVT_STS.ERR_FRAME",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_ERR_FRAME) == FSI_RX_EVT_STS_ERR_FRAME)`,
        applicable: (inst) => {
            return DEVICES_WITH_FSI.includes(deviceName);
        },
    },
    {
        name: "rxbufunderrun",
        displayName: "RX Buffer Underrun",
        description: "RX buffer read attempted when buffer was empty.\nRED = Buffer underrun error (read before data available)\nGREEN = No buffer underrun",
        type: 'led',
        register: "RX_EVT_STS.BUF_UNDERRUN",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_BUF_UNDERRUN) == FSI_RX_EVT_STS_BUF_UNDERRUN)`,
        applicable: (inst) => {
            return DEVICES_WITH_FSI.includes(deviceName);
        },
    },
    {
        name: "rxbufoverrun",
        displayName: "RX Buffer Overrun",
        description: "RX buffer write attempted when buffer was full.\nRED = Buffer overrun error (data loss - buffer full)\nGREEN = No buffer overrun",
        type: 'led',
        register: "RX_EVT_STS.BUF_OVERRUN",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_BUF_OVERRUN) == FSI_RX_EVT_STS_BUF_OVERRUN)`,
        applicable: (inst) => {
            return DEVICES_WITH_FSI.includes(deviceName);
        },
    },
    {
        name: "rxeoferr",
        displayName: "RX End-of-Frame Error",
        description: "Invalid or missing end-of-frame pattern detected.\nRED = EOF error (frame format/timing issue)\nGREEN = No EOF error",
        type: 'led',
        register: "RX_EVT_STS.EOF_ERR",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_EOF_ERR) == FSI_RX_EVT_STS_EOF_ERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_FSI.includes(deviceName);
        },
    },
    {
        name: "rxtypeerr",
        displayName: "RX Type Error",
        description: "Received frame type does not match expected type.\nRED = Frame type mismatch error\nGREEN = No type error",
        type: 'led',
        register: "RX_EVT_STS.TYPE_ERR",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_TYPE_ERR) == FSI_RX_EVT_STS_TYPE_ERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_FSI.includes(deviceName);
        },
    },
    {
        name: "rxcrcerr",
        displayName: "RX CRC Error",
        description: "CRC check failed on received frame data.\nRED = CRC mismatch (data corruption detected)\nGREEN = CRC valid",
        type: 'led',
        register: "RX_EVT_STS.CRC_ERR",
        bitfieldInstance: "fsiRx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_RX_EVT_STS) & FSI_RX_EVT_STS_CRC_ERR) == FSI_RX_EVT_STS_CRC_ERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_FSI.includes(deviceName);
        },
    },
]

let bitfieldInstanceNames = {
    "default": (instName) => { return "FsiRx"+ instName.toUpperCase() + "Regs" },
    "fsiRx" : (instName) => { return "FsiRx"+ instName.toUpperCase() + "Regs" },
}

//-----------------------------------------------------------------------------
// Registers to Skip (Read-to-Clear, Force, and cross-module registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // RX Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "RX_EVT_CLR", register: "RX_EVT_CLR" },
    // RX Force registers (Write-Only - Force trigger)
    { name: "RX_EVT_FRC", register: "RX_EVT_FRC" },
    // TX registers (not applicable to RX module - skip all TX regs)
    { name: "TX_MASTER_CTRL", register: "TX_MASTER_CTRL" },
    { name: "TX_CLK_CTRL", register: "TX_CLK_CTRL" },
    { name: "TX_OPER_CTRL_LO", register: "TX_OPER_CTRL_LO" },
    { name: "TX_OPER_CTRL_HI", register: "TX_OPER_CTRL_HI" },
    { name: "TX_FRAME_CTRL", register: "TX_FRAME_CTRL" },
    { name: "TX_FRAME_TAG_UDATA", register: "TX_FRAME_TAG_UDATA" },
    { name: "TX_BUF_PTR_LOAD", register: "TX_BUF_PTR_LOAD" },
    { name: "TX_BUF_PTR_STS", register: "TX_BUF_PTR_STS" },
    { name: "TX_PING_CTRL", register: "TX_PING_CTRL" },
    { name: "TX_PING_TAG", register: "TX_PING_TAG" },
    { name: "TX_PING_TO_REF", register: "TX_PING_TO_REF" },
    { name: "TX_PING_TO_CNT", register: "TX_PING_TO_CNT" },
    { name: "TX_INT_CTRL", register: "TX_INT_CTRL" },
    { name: "TX_DMA_CTRL", register: "TX_DMA_CTRL" },
    { name: "TX_LOCK_CTRL", register: "TX_LOCK_CTRL" },
    { name: "TX_EVT_STS", register: "TX_EVT_STS" },
    { name: "TX_EVT_CLR", register: "TX_EVT_CLR" },
    { name: "TX_EVT_FRC", register: "TX_EVT_FRC" },
    { name: "TX_USER_CRC", register: "TX_USER_CRC" },
    { name: "TX_ECC_DATA", register: "TX_ECC_DATA" },
    { name: "TX_ECC_VAL", register: "TX_ECC_VAL" },
    { name: "TX_DLYLINE_CTRL", register: "TX_DLYLINE_CTRL" },
    // Buffer base registers (volatile)
    { name: "TX_BUF_BASE(i)", register: "TX_BUF_BASE(i)" },
    { name: "RX_BUF_BASE(i)", register: "RX_BUF_BASE(i)" },
]

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames : bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
