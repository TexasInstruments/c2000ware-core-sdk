//=============================================================================
// export_mod_eqep.js - EQEP Export Module for CDT
//=============================================================================
// Purpose: Expose Enhanced Quadrature Encoder Pulse diagnostic information
// Devices: All Gen3 devices
// Reference: driverlib/<device>/driverlib/inc/hw_eqep.h
//
// Key Registers:
//   EQEP_O_QFLG    = 0x19 - Interrupt Flag Register
//   EQEP_O_QEPSTS  = 0x1C - Status Register
//   EQEP_O_QPOSCNT = 0x0  - Position Counter
//=============================================================================

const exportCommon = system.getScript("/utilities/transfer/export/export_mods_common.js");
const { DEVICES_WITH_CDT_SUPPORT, DEVICES_WITH_QMAE, getDeviceName } = exportCommon;
const deviceName = getDeviceName();

let exportsInfo = [
  //-------------------------------------------------------------------------
  // QFLG Register - Interrupt Flags (error conditions)
  //-------------------------------------------------------------------------
  {
    name: "PCE",
    displayName: "Position Counter Error Flag",
    description: "Position counter error detected. RED indicates encoder count mismatch or index pulse missed. Check encoder wiring and alignment.",
    type: 'led',
    register: "QFLG.PCE",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QFLG) & EQEP_QFLG_PCE) == EQEP_QFLG_PCE)`,
    applicable: (inst) => {
       // PCE exists on all Gen3 devices
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName) && inst.enableInterrupt && inst.interruptSources.includes("EQEP_INT_POS_CNT_ERROR")
    }
  },
  {
    name: "PHE",
    displayName: "Quadrature Phase Error Flag",
    description: "Quadrature phase error detected. RED indicates invalid A/B signal sequence (both changed simultaneously). Check encoder signal integrity and shielding.",
    type: 'led',
    register: "QFLG.PHE",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QFLG) & EQEP_QFLG_PHE) == EQEP_QFLG_PHE)`,
    applicable: (inst) => {
       // PHE exists on all Gen3 devices
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName) && inst.enableInterrupt && inst.interruptSources.includes("EQEP_INT_PHASE_ERROR")
    }
  },
  {
    name: "QDC",
    displayName: "Quadrature Direction Change Flag",
    description: "Encoder direction changed. GREEN indicates motor reversed direction since last clear. Normal during servo operation, unexpected in constant-speed applications.",
    type: 'led',
    register: "QFLG.QDC",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QFLG) & EQEP_QFLG_QDC) == EQEP_QFLG_QDC)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "WTO",
    displayName: "Watchdog Timeout Flag",
    description: "Encoder watchdog timeout. RED indicates no encoder pulses received within timeout period. Motor may be stopped or encoder disconnected.",
    type: 'led',
    register: "QFLG.WTO",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QFLG) & EQEP_QFLG_WTO) == EQEP_QFLG_WTO)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "PCU",
    displayName: "Position Counter Underflow Flag",
    description: "Position counter underflowed (wrapped from 0 to QPOSMAX). GREEN indicates counter rollover during reverse motion. Normal in continuous rotation.",
    type: 'led',
    register: "QFLG.PCU",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QFLG) & EQEP_QFLG_PCU) == EQEP_QFLG_PCU)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "PCO",
    displayName: "Position Counter Overflow Flag",
    description: "Position counter overflowed (wrapped from QPOSMAX to 0). GREEN indicates counter rollover during forward motion. Normal in continuous rotation.",
    type: 'led',
    register: "QFLG.PCO",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QFLG) & EQEP_QFLG_PCO) == EQEP_QFLG_PCO)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "IEL",
    displayName: "Index Event Latch Flag",
    description: "Index pulse detected and position latched. GREEN indicates encoder completed one revolution. Use for position calibration and homing.",
    type: 'led',
    register: "QFLG.IEL",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QFLG) & EQEP_QFLG_IEL) == EQEP_QFLG_IEL)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "SEL",
    displayName: "Strobe Event Latch Flag",
    description: "Strobe input event detected. GREEN indicates external strobe signal triggered position capture. Used for synchronization with external events.",
    type: 'led',
    register: "QFLG.SEL",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QFLG) & EQEP_QFLG_SEL) == EQEP_QFLG_SEL)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "UTO",
    displayName: "Unit Time Out Flag",
    description: "Unit timer period elapsed. GREEN indicates velocity measurement period complete. Used for speed calculation timing.",
    type: 'led',
    register: "QFLG.UTO",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QFLG) & EQEP_QFLG_UTO) == EQEP_QFLG_UTO)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "QMAE",
    displayName: "QMA Error Interrupt Flag",
    description: "QMA mode error detected. RED indicates invalid signal pattern in QMA (Quadrature Motor Adapter) mode. Check resolver/encoder interface.",
    type: 'led',
    register: "QFLG.QMAE",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QFLG) & EQEP_QFLG_QMAE) == EQEP_QFLG_QMAE)`,
    applicable: (inst) => {
       // QMAE only exists on specific devices (NOT F2807x, F2837xD, F2837xS)
       return DEVICES_WITH_QMAE.includes(deviceName) && inst.enableInterrupt && inst.interruptSources.includes("EQEP_INT_QMA_ERROR")
    }
  },

  //-------------------------------------------------------------------------
  // QEPSTS Register - Status Flags
  //-------------------------------------------------------------------------
  {
    name: "PCEF",
    displayName: "Position Counter Error Status",
    description: "Position counter error status (latched). RED indicates position count error occurred at some point. Clear flag and monitor for recurrence.",
    type: 'led',
    register: "QEPSTS.PCEF",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QEPSTS) & EQEP_QEPSTS_PCEF) != 0)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "COEF",
    displayName: "Capture Overflow Error Flag",
    description: "Capture timer overflow. RED indicates encoder speed too slow for capture mode settings. Increase capture prescaler or use different speed measurement mode.",
    type: 'led',
    register: "QEPSTS.COEF",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QEPSTS) & EQEP_QEPSTS_COEF) != 0)`,
    applicable: (inst) => {
       // COEF exists on all Gen3 devices
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "CDEF",
    displayName: "Capture Direction Error Flag",
    description: "Direction changed during capture. RED indicates direction reversal between capture edges. May cause inaccurate speed measurement.",
    type: 'led',
    register: "QEPSTS.CDEF",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QEPSTS) & EQEP_QEPSTS_CDEF) != 0)`,
    applicable: (inst) => {
       // CDEF exists on all Gen3 devices
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "QDF",
    displayName: "Quadrature Direction Flag",
    description: "Current rotation direction. GREEN = clockwise (forward), OFF = counter-clockwise (reverse). Real-time direction indicator.",
    type: 'led',
    register: "QEPSTS.QDF",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QEPSTS) & EQEP_QEPSTS_QDF) != 0)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "FIMF",
    displayName: "First Index Marker Flag",
    description: "First index pulse received since reset. GREEN indicates encoder homing reference established. Used to validate position calibration.",
    type: 'led',
    register: "QEPSTS.FIMF",
    updateFunc: (instBase) => `((HWREGH(${instBase} + EQEP_O_QEPSTS) & EQEP_QEPSTS_FIMF) != 0)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },

  //-------------------------------------------------------------------------
  // Position Counter Value
  //-------------------------------------------------------------------------
  {
    name: "QPOSCNT",
    displayName: "Position Counter Value",
    description: "Current encoder position count (0 to QPOSMAX). Updates in real-time as encoder rotates. Divide by counts/revolution for mechanical position.",
    type: 'value',
    register: "QPOSCNT",
    updateFunc: (instBase) => `HWREG(${instBase} + EQEP_O_QPOSCNT)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
  {
    name: "QPOSMAX",
    displayName: "Position Counter Max",
    description: "Maximum position counter value before rollover. Typically set to (encoder_counts_per_rev - 1) or (4x line count - 1) for quadrature mode.",
    type: 'value',
    register: "QPOSMAX",
    updateFunc: (instBase) => `HWREG(${instBase} + EQEP_O_QPOSMAX)`,
    applicable: (inst) => {
       return DEVICES_WITH_CDT_SUPPORT.includes(deviceName);
    }
  },
];

let bitfieldInstanceNames = {
    "default": (instName) => { return "EQep"+ instName + "Regs" },
}

//-----------------------------------------------------------------------------
// Registers to Skip (Read-to-Clear and Force registers)
//-----------------------------------------------------------------------------
let exportsRegisterSkips = [
    // Read-to-Clear registers (R/W1C - Write 1 to Clear)
    { name: "QCLR", register: "EQEPQCLR" },
    // Force registers (Write-Only - Force trigger)
    { name: "QFRC", register: "EQEPQFRC" },
]

exports = {
    exportsInfo: exportsInfo,
    bitfieldInstanceNames : bitfieldInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}
