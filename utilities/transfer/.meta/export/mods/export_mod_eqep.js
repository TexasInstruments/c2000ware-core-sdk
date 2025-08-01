var deviceName = system.deviceData.device;
let exportsInfo = [
  {
    name: "PCE",
    displayName: "Position Counter Error Flag",
    type: 'led',
    register: "QFLG.PCE",
    updateFunc: (instBase) => `((HWREGH(${instBase} + QEP_O_QFLG) & QEP_QFLG_PCE) == QEP_QFLG_PCE)`,
    applicable: (inst) => {
       return ["F280013x", "F280015x"].includes(deviceName) && inst.enableInterrupt && inst.interruptSources.includes("EQEP_INT_POS_CNT_ERROR")
    }
  },
  {
    name: "PHE",
    displayName: "Quadrature Phase Error Flag",
    type: 'led',
    register: "QFLG.PHE",
    updateFunc: (instBase) => `((HWREGH(${instBase} + QEP_O_QFLG) & QEP_QFLG_PHE) == QEP_QFLG_PHE)`,
    applicable: (inst) => {
       return ["F280013x","F280015x", "F28003x"].includes(deviceName) && inst.enableInterrupt && inst.interruptSources.includes("EQEP_INT_PHASE_ERROR")
    }
  },
  {
    name: "QMAE",
    displayName: "QMA Error Interrupt Flag",
    type: 'led',
    register: "QFLG.QMAE",
    updateFunc: (instBase) => `((HWREGH(${instBase} + QEP_O_QFLG) & QEP_QFLG_QMAE) == QEP_QFLG_QMAE)`,
    applicable: (inst) => {
       return ["F280013x","F280015x", "F28003x"].includes(deviceName) && inst.enableInterrupt && inst.interruptSources.includes("EQEP_INT_QMA_ERROR")
    }
  },
  {
    name: "COEF",
    displayName: "Capture Overflow Error Flag",
    type: 'led',
    register: "QEPSTS.COEF",
    updateFunc: (instBase) => `((HWREGH(${instBase} + QEP_O_QEPSTS) & QEP_QEPSTS_COEF) !== 0)`,
    applicable: (inst) => {
            return (["F280013x","F280015x", "F28003x"].includes(deviceName)? true: false);
    } 
  },
  {
    name: "CDEF",
    displayName: "Capture Direction Error Flag",
    type: 'led',
    register: "QEPSTS.CDEF",
    updateFunc: (instBase) => `((HWREGH(${instBase} + QEP_O_QEPSTS) & QEP_QEPSTS_CDEF) !== 0)`,
    applicable: (inst) => {
            return (["F280013x","F280015x", "F28003x"].includes(deviceName)? true: false);
    } 
  },
  
];

let bitfiledInstanceNames = {
    "default": (instName) => { return "EQep"+ instName + "Regs" },
}

let exportsRegisterSkips = [
  
   
]

exports = {
    exportsInfo: exportsInfo,
    bitfiledInstanceNames : bitfiledInstanceNames,
    exportsRegisterSkips: exportsRegisterSkips,
}