//=============================================================================
// export_mod_mcan.js - MCAN (CAN-FD) Export Module for CDT
//=============================================================================
// Purpose: Expose MCAN diagnostic information for Clinic Diagnostic Tool
// Devices: F28003x, F2838x, F28P55x, F28P65x (devices with MCAN peripheral)
//
// IMPORTANT: MCAN MSG_RAM requires 32-bit access (HWREG), NOT 16-bit (HWREGH)
//
// Reference Documents:
//   - Device TRM: MCAN chapter
//   - driverlib/<device>/driverlib/mcan.h
//   - driverlib/<device>/driverlib/inc/hw_mcan.h
//   - Bosch M_CAN User Manual
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_MCAN, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

// Devices with MCAN ECC Error Aggregator (same as MCAN devices)
const DEVICES_WITH_MCAN_ECC = DEVICES_WITH_MCAN;

//-----------------------------------------------------------------------------
// Export Information - Diagnostic Indicators
// NOTE: LED polarity - RED (lit) indicates error/warning condition
//-----------------------------------------------------------------------------
let exportsInfo = [
    //-------------------------------------------------------------------------
    // Protocol Status - Error Indicators
    //-------------------------------------------------------------------------
    {
        name: "BO",
        displayName: "Bus Off State",
        description: "MCAN bus-off state. RED indicates controller entered bus-off due to excessive errors. Node cannot transmit or receive until recovery sequence completes.",
        type: 'led',
        register: "MCAN_PSR.BO",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCAN_PSR) & MCAN_PSR_BO) == MCAN_PSR_BO)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN.includes(deviceName);
        }
    },
    {
        name: "EW",
        displayName: "Error Warning Status",
        description: "Error warning threshold exceeded. RED indicates TEC or REC >= 96. Node approaching error-passive state. Check bus wiring and termination.",
        type: 'led',
        register: "MCAN_PSR.EW",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCAN_PSR) & MCAN_PSR_EW) == MCAN_PSR_EW)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN.includes(deviceName);
        }
    },
    {
        name: "EP",
        displayName: "Error Passive Status",
        description: "MCAN error-passive state. RED indicates TEC or REC >= 128. Node can communicate but uses passive error flags. May indicate signal integrity issues.",
        type: 'led',
        register: "MCAN_PSR.EP",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCAN_PSR) & MCAN_PSR_EP) == MCAN_PSR_EP)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // RX FIFO Status
    //-------------------------------------------------------------------------
    {
        name: "RF0L",
        displayName: "RX FIFO 0 Message Lost",
        description: "RX FIFO 0 message lost. RED indicates new message arrived when FIFO was full, causing data loss. Increase FIFO size or process messages faster.",
        type: 'led',
        register: "MCAN_IR.RF0L",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCAN_IR) & MCAN_IR_RF0L) == MCAN_IR_RF0L)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN.includes(deviceName);
        }
    },
    {
        name: "RF1L",
        displayName: "RX FIFO 1 Message Lost",
        description: "RX FIFO 1 message lost. RED indicates new message arrived when FIFO was full, causing data loss. Increase FIFO size or process messages faster.",
        type: 'led',
        register: "MCAN_IR.RF1L",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCAN_IR) & MCAN_IR_RF1L) == MCAN_IR_RF1L)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Message RAM Access Failure
    //-------------------------------------------------------------------------
    {
        name: "MRAF",
        displayName: "Message RAM Access Failure",
        description: "Message RAM access failure. RED indicates hardware configuration error in message RAM. Check TX buffer, RX FIFO, and filter element settings.",
        type: 'led',
        register: "MCAN_IR.MRAF",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCAN_IR) & MCAN_IR_MRAF) == MCAN_IR_MRAF)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // Error Counters (Value exports)
    //-------------------------------------------------------------------------
    {
        name: "TEC",
        displayName: "TX Error Counter",
        type: 'value',
        register: "MCAN_ECR.TEC",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCAN_ECR) & MCAN_ECR_TEC_M) >> MCAN_ECR_TEC_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN.includes(deviceName);
        }
    },
    {
        name: "REC",
        displayName: "RX Error Counter",
        type: 'value',
        register: "MCAN_ECR.REC",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCAN_ECR) & MCAN_ECR_REC_M) >> MCAN_ECR_REC_S)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN.includes(deviceName);
        }
    },

    //-------------------------------------------------------------------------
    // ECC Error Status (MCAN Error Aggregator)
    // Reference: MCAN_ERROR_REGS in targetdb
    // NOTE: These are error flags - RED indicates errors were detected
    //-------------------------------------------------------------------------
    {
        name: "eccSec",
        displayName: "ECC Single-Bit Error Corrected",
        description: "Single-bit ECC error detected in message RAM and auto-corrected. RED indicates memory errors are occurring. Monitor for escalation to double-bit errors.",
        type: 'led',
        register: "MCANERR_ERR_STAT1.ECC_SEC",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCANERR_O_ERR_STAT1) & MCANERR_ERR_STAT1_ECC_SEC_M) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN_ECC.includes(deviceName);
        }
    },
    {
        name: "eccDed",
        displayName: "ECC Double-Bit Error Detected",
        description: "CRITICAL: Double-bit ECC error detected in message RAM (uncorrectable). RED indicates data corruption. Check for EMI, power supply issues, or hardware failure.",
        type: 'led',
        register: "MCANERR_ERR_STAT1.ECC_DED",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCANERR_O_ERR_STAT1) & MCANERR_ERR_STAT1_ECC_DED_M) != 0)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN_ECC.includes(deviceName);
        }
    },
    {
        name: "eccOther",
        displayName: "ECC SEC During Writeback",
        description: "Single-bit error occurred during ECC writeback operation. RED indicates ECC correction was interrupted. May require clearing error status.",
        type: 'led',
        register: "MCANERR_ERR_STAT1.ECC_OTHER",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCANERR_O_ERR_STAT1) & MCANERR_ERR_STAT1_ECC_OTHER) == MCANERR_ERR_STAT1_ECC_OTHER)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN_ECC.includes(deviceName);
        }
    },
    {
        name: "ctrlRegError",
        displayName: "Control Register Error",
        description: "MCAN control register parity or comparison error. RED indicates critical configuration error. May require module reset.",
        type: 'led',
        register: "MCANERR_ERR_STAT1.CTRL_REG_ERROR",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCANERR_O_ERR_STAT1) & MCANERR_ERR_STAT1_CTRL_REG_ERROR) == MCANERR_ERR_STAT1_CTRL_REG_ERROR)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN_ECC.includes(deviceName);
        }
    },
    {
        name: "eccErrRow",
        displayName: "ECC Error Row Address",
        description: "Row address in message RAM where last ECC error was detected. Use to identify failing memory location.",
        type: 'value',
        register: "MCANERR_ERR_STAT2.ECC_ROW",
        updateFunc: (instBase) => `HWREG(${instBase} + MCANERR_O_ERR_STAT2)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN_ECC.includes(deviceName);
        }
    },
    {
        name: "svbusTimeout",
        displayName: "SVBUS Timeout Error",
        description: "System VBUS timeout during MCAN memory access. RED indicates bus arbitration or clock issue. Check system interconnect configuration.",
        type: 'led',
        register: "MCANERR_ERR_STAT3.SVBUS_TIMEOUT",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCANERR_O_ERR_STAT3) & MCANERR_ERR_STAT3_SVBUS_TIMEOUT) == MCANERR_ERR_STAT3_SVBUS_TIMEOUT)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN_ECC.includes(deviceName);
        }
    },
    {
        name: "wbPending",
        displayName: "Writeback Pending",
        description: "ECC writeback operation in progress. GREEN indicates ECC correction writeback is pending. This is a status indicator, not an error.",
        type: 'led',
        register: "MCANERR_ERR_STAT3.WB_PEND",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCANERR_O_ERR_STAT3) & MCANERR_ERR_STAT3_WB_PEND) == MCANERR_ERR_STAT3_WB_PEND)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN_ECC.includes(deviceName);
        }
    },
    {
        name: "secIntPending",
        displayName: "SEC Interrupt Pending",
        description: "Single-bit ECC correction interrupt pending. RED indicates unserviced SEC interrupt. Service interrupt and clear status.",
        type: 'led',
        register: "MCANERR_SEC_STATUS.MSGMEM_PEND",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCANERR_O_SEC_STATUS) & MCANERR_SEC_STATUS_MSGMEM_PEND) == MCANERR_SEC_STATUS_MSGMEM_PEND)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN_ECC.includes(deviceName);
        }
    },
    {
        name: "dedIntPending",
        displayName: "DED Interrupt Pending",
        description: "CRITICAL: Double-bit ECC error interrupt pending. RED indicates unserviced DED interrupt - data corruption has occurred. Immediate attention required.",
        type: 'led',
        register: "MCANERR_DED_STATUS.MSGMEM_PEND",
        updateFunc: (instBase) => `((HWREG(${instBase} + MCANERR_O_DED_STATUS) & MCANERR_DED_STATUS_MSGMEM_PEND) == MCANERR_DED_STATUS_MSGMEM_PEND)`,
        applicable: (inst) => {
            return DEVICES_WITH_MCAN_ECC.includes(deviceName);
        }
    },
];

//-----------------------------------------------------------------------------
// Bitfield Instance Name Mapping
// Maps SysConfig instance names to register struct names
// Example: myMCAN_A -> McanaRegs, myMCANA -> McanaRegs, myMCAN0 -> McanaRegs
//-----------------------------------------------------------------------------
let bitfieldInstanceNames = {
    "default": (instName) => { return "Mcan" + instName + "Regs" },
    // Letter-based instance names (case-insensitive handled by toUpperCase in caller)
    "a": (instName) => { return "McanaRegs" },
    "b": (instName) => { return "McanbRegs" },
    // Numeric instance names (0-based to letter mapping)
    "0": (instName) => { return "McanaRegs" },
    "1": (instName) => { return "McanbRegs" },
};

//-----------------------------------------------------------------------------
// Registers to Skip (Read-to-Clear and volatile registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Message RAM contents should not be exported directly
    // Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "ERR_SEC_ENABLE_CLR", register: "MCAN_ERR_SEC_ENABLE_CLR" },
    { name: "ERR_DED_ENABLE_CLR", register: "MCAN_ERR_DED_ENABLE_CLR" },
    { name: "ERR_AGGR_ENABLE_CLR", register: "MCAN_ERR_AGGR_ENABLE_CLR" },
    { name: "ERR_AGGR_STATUS_CLR", register: "MCAN_ERR_AGGR_STATUS_CLR" },
    // ECC Error Status clear bits are embedded in ERR_STAT1/ERR_STAT3
    // CLR_ECC_SEC, CLR_ECC_DED, CLR_ECC_OTHER, CLR_CTRL_REG_ERROR in ERR_STAT1
    // CLR_SVBUS_TIMEOUT in ERR_STAT3
    // SEC/DED End of Interrupt registers
    { name: "SEC_EOI", register: "MCANERR_SEC_EOI" },
    { name: "DED_EOI", register: "MCANERR_DED_EOI" },
];

//-----------------------------------------------------------------------------
// Module Exports
//-----------------------------------------------------------------------------
exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames: bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
