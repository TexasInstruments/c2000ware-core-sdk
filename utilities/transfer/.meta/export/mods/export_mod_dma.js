//=============================================================================
// export_mod_dma.js - DMA Export Module for CDT
//=============================================================================
// Purpose: Expose DMA diagnostic information for Clinic Diagnostic Tool
// Location: C2000Ware/.../utilities/transfer/.meta/export/mods/
//
// Reference Documents:
//   - Device TRM: DMA chapter
//   - driverlib/<device>/driverlib/dma.h
//   - driverlib/<device>/driverlib/dma.c
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_DMA, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// Note: F280013x and F280015x do NOT have DMA
// Device list imported from device_constants.js via exportCommon

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // DMA Channel Status Flags
    //-------------------------------------------------------------------------
    {
        name: "dmaRunSts",
        displayName: "DMA Running Status",
        type: 'led',
        register: "CONTROL.RUNSTS",
        updateFunc: (instBase) => `((HWREGH(${instBase} + DMA_O_CONTROL) & DMA_CONTROL_RUNSTS) == DMA_CONTROL_RUNSTS)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },
    {
        name: "dmaBurstSts",
        displayName: "DMA Burst Status",
        type: 'led',
        register: "CONTROL.BURSTSTS",
        updateFunc: (instBase) => `((HWREGH(${instBase} + DMA_O_CONTROL) & DMA_CONTROL_BURSTSTS) == DMA_CONTROL_BURSTSTS)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },
    {
        name: "dmaTransferSts",
        displayName: "DMA Transfer Status",
        type: 'led',
        register: "CONTROL.TRANSFERSTS",
        updateFunc: (instBase) => `((HWREGH(${instBase} + DMA_O_CONTROL) & DMA_CONTROL_TRANSFERSTS) == DMA_CONTROL_TRANSFERSTS)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // DMA Error Flags
    //-------------------------------------------------------------------------
    {
        name: "dmaSyncErr",
        displayName: "DMA Peripheral Sync Error",
        type: 'led',
        register: "CONTROL.SYNCERR",
        updateFunc: (instBase) => `((HWREGH(${instBase} + DMA_O_CONTROL) & DMA_CONTROL_SYNCERR) == DMA_CONTROL_SYNCERR)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },
    {
        name: "dmaOvrflw",
        displayName: "DMA Overflow Error",
        type: 'led',
        register: "CONTROL.OVRFLG",
        updateFunc: (instBase) => `((HWREGH(${instBase} + DMA_O_CONTROL) & DMA_CONTROL_OVRFLG) == DMA_CONTROL_OVRFLG)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // DMA Transfer Counts
    //-------------------------------------------------------------------------
    {
        name: "dmaBurstCount",
        displayName: "Current Burst Count",
        type: 'value',
        register: "BURST_COUNT",
        updateFunc: (instBase) => `HWREGH(${instBase} + DMA_O_BURST_COUNT)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },
    {
        name: "dmaTransferCount",
        displayName: "Current Transfer Count",
        type: 'value',
        register: "TRANSFER_COUNT",
        updateFunc: (instBase) => `HWREGH(${instBase} + DMA_O_TRANSFER_COUNT)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // DMA Address Pointers (for debugging)
    //-------------------------------------------------------------------------
    {
        name: "dmaSrcAddrActive",
        displayName: "Active Source Address",
        type: 'value',
        register: "SRC_ADDR_ACTIVE",
        updateFunc: (instBase) => `HWREG(${instBase} + DMA_O_SRC_ADDR_ACTIVE)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },
    {
        name: "dmaDstAddrActive",
        displayName: "Active Destination Address",
        type: 'value',
        register: "DST_ADDR_ACTIVE",
        updateFunc: (instBase) => `HWREG(${instBase} + DMA_O_DST_ADDR_ACTIVE)`,
        applicable: (inst) => {
            return DEVICES_WITH_DMA.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "DmaCh" + instName + "Regs" },
    // For DMA base registers
    "base": (instName) => { return "DmaRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Write-1-to-Clear and control registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Write-1-to-Clear registers
    { name: "PERINTCLR", register: "DMAPERINTCLR" },
    { name: "ERRCLR", register: "DMAERRCLR" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
