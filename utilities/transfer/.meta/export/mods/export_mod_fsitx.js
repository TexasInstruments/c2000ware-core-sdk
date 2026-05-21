//=============================================================================
// export_mod_fsitx.js - FSI TX Export Module for CDT
//=============================================================================
// Purpose: Expose Fast Serial Interface TX diagnostic information for CDT
// Devices: F28002x, F28003x, F28004x, F2838x, F28P55x, F28P65x
// Reference: driverlib/<device>/driverlib/inc/hw_fsi.h
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_FSI, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
// LED Color Semantics: RED = error condition, GREEN = no error
//-----------------------------------------------------------------------------
let exportsInfo = [
    {
        name: "txbufoverrun",
        displayName: "TX Buffer Overrun",
        description: "TX buffer write attempted when buffer was full.\nRED = Buffer overrun error (write discarded - buffer full)\nGREEN = No buffer overrun",
        type: 'led',
        register: "TX_EVT_STS.BUF_OVERRUN",
        bitfieldInstance: "fsiTx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_TX_EVT_STS) & FSI_TX_EVT_STS_BUF_OVERRUN) == FSI_TX_EVT_STS_BUF_OVERRUN)`,
        applicable: (inst) => {
            // All FSI devices have TX status bits (validated via hw_fsi.h)
            return DEVICES_WITH_FSI.includes(deviceName);
        },
    },
    {
        name: "txbufunderrun",
        displayName: "TX Buffer Underrun",
        description: "TX transmission attempted when buffer was empty.\nRED = Buffer underrun error (transmitted invalid/stale data)\nGREEN = No buffer underrun",
        type: 'led',
        register: "TX_EVT_STS.BUF_UNDERRUN",
        bitfieldInstance: "fsiTx",
        updateFunc: (instBase) => `((HWREGH(${instBase} + FSI_O_TX_EVT_STS) & FSI_TX_EVT_STS_BUF_UNDERRUN) == FSI_TX_EVT_STS_BUF_UNDERRUN)`,
        applicable: (inst) => {
            // All FSI devices have TX status bits (validated via hw_fsi.h)
            return DEVICES_WITH_FSI.includes(deviceName);
        },
    },
]

let bitfieldInstanceNames = {
    "default": (instName) => { return "FsiTx"+ instName.toUpperCase() + "Regs" },
    "fsiTx" : (instName) => { return "FsiTx"+ instName.toUpperCase() + "Regs" },
}

//-----------------------------------------------------------------------------
// Registers to Skip (Read-to-Clear, Force, and cross-module registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // TX Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "TX_EVT_CLR", register: "TX_EVT_CLR" },
    // TX Force registers (Write-Only - Force trigger)
    { name: "TX_EVT_FRC", register: "TX_EVT_FRC" },
    // RX registers (not applicable to TX module - skip all RX regs)
    { name: "RX_MASTER_CTRL", register: "RX_MASTER_CTRL" },
    { name: "RX_OPER_CTRL", register: "RX_OPER_CTRL" },
    { name: "RX_FRAME_INFO", register: "RX_FRAME_INFO" },
    { name: "RX_FRAME_TAG_UDATA", register: "RX_FRAME_TAG_UDATA" },
    { name: "RX_DMA_CTRL", register: "RX_DMA_CTRL" },
    { name: "RX_EVT_STS", register: "RX_EVT_STS" },
    { name: "RX_CRC_INFO", register: "RX_CRC_INFO" },
    { name: "RX_EVT_CLR", register: "RX_EVT_CLR" },
    { name: "RX_EVT_FRC", register: "RX_EVT_FRC" },
    { name: "RX_BUF_PTR_LOAD", register: "RX_BUF_PTR_LOAD" },
    { name: "RX_BUF_PTR_STS", register: "RX_BUF_PTR_STS" },
    { name: "RX_FRAME_WD_CTRL", register: "RX_FRAME_WD_CTRL" },
    { name: "RX_FRAME_WD_REF", register: "RX_FRAME_WD_REF" },
    { name: "RX_FRAME_WD_CNT", register: "RX_FRAME_WD_CNT" },
    { name: "RX_PING_WD_CTRL", register: "RX_PING_WD_CTRL" },
    { name: "RX_PING_TAG", register: "RX_PING_TAG" },
    { name: "RX_PING_WD_REF", register: "RX_PING_WD_REF" },
    { name: "RX_PING_WD_CNT", register: "RX_PING_WD_CNT" },
    { name: "RX_INT1_CTRL", register: "RX_INT1_CTRL" },
    { name: "RX_INT2_CTRL", register: "RX_INT2_CTRL" },
    { name: "RX_LOCK_CTRL", register: "RX_LOCK_CTRL" },
    { name: "RX_ECC_DATA", register: "RX_ECC_DATA" },
    { name: "RX_ECC_VAL", register: "RX_ECC_VAL" },
    { name: "RX_ECC_SEC_DATA", register: "RX_ECC_SEC_DATA" },
    { name: "RX_ECC_LOG", register: "RX_ECC_LOG" },
    { name: "RX_FRAME_TAG_CMP", register: "RX_FRAME_TAG_CMP" },
    { name: "RX_PING_TAG_CMP", register: "RX_PING_TAG_CMP" },
    { name: "RX_TRIG_CTRL_0", register: "RX_TRIG_CTRL_0" },
    { name: "RX_TRIG_WIDTH_0", register: "RX_TRIG_WIDTH_0" },
    { name: "RX_DLYLINE_CTRL", register: "RX_DLYLINE_CTRL" },
    { name: "RX_TRIG_CTRL_1", register: "RX_TRIG_CTRL_1" },
    { name: "RX_TRIG_CTRL_2", register: "RX_TRIG_CTRL_2" },
    { name: "RX_TRIG_CTRL_3", register: "RX_TRIG_CTRL_3" },
    { name: "RX_VIS_1", register: "RX_VIS_1" },
    { name: "RX_UDATA_FILTER", register: "RX_UDATA_FILTER" },
    // Buffer base registers (volatile)
    { name: "RX_BUF_BASE(i)", register: "RX_BUF_BASE(i)" },
    { name: "TX_BUF_BASE(i)", register: "TX_BUF_BASE(i)" },
]

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames : bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
