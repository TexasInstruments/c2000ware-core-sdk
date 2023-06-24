let hrpwm_driverlib = 
{
  "name": "hrpwm",
  "functions": [
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_isBaseValid",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef DEBUG  static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setPhaseShift",
      "functionArgs": [
        "base",
        "phaseCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBPHS"
      ],
      "registersUsedMatchingBifield": [
        "TBPHS"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setHiResPhaseShiftOnly",
      "functionArgs": [
        "base",
        "hrPhaseCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBPHS"
      ],
      "registersUsedMatchingBifield": [
        "TBPHS"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setTimeBasePeriod",
      "functionArgs": [
        "base",
        "periodCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBPRDHR",
        "TBPRD"
      ],
      "registersUsedMatchingBifield": [
        "TBPRDHR",
        "TBPRD"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setHiResTimeBasePeriodOnly",
      "functionArgs": [
        "base",
        "hrPeriodCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBPRDHR",
        "TBPRD"
      ],
      "registersUsedMatchingBifield": [
        "TBPRDHR",
        "TBPRD"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_getTimeBasePeriod",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "TBPRDHR",
        "TBPRD"
      ],
      "registersUsedMatchingBifield": [
        "TBPRDHR",
        "TBPRD"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_getHiResTimeBasePeriodOnly",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TBPRDHR",
        "TBPRD"
      ],
      "registersUsedMatchingBifield": [
        "TBPRDHR",
        "TBPRD"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setMEPEdgeSelect",
      "functionArgs": [
        "base",
        "channel",
        "mepEdgeMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_Channel",
        "HRPWM_MEPEdgeMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCNFG"
      ],
      "registersUsedMatchingBifield": [
        "HRCNFG"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setMEPControlMode",
      "functionArgs": [
        "base",
        "channel",
        "mepCtrlMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_Channel",
        "HRPWM_MEPCtrlMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCNFG"
      ],
      "registersUsedMatchingBifield": [
        "HRCNFG"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setCounterCompareShadowLoadEvent",
      "functionArgs": [
        "base",
        "channel",
        "loadEvent"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_Channel",
        "HRPWM_LoadMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCNFG"
      ],
      "registersUsedMatchingBifield": [
        "HRCNFG"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setOutputSwapMode",
      "functionArgs": [
        "base",
        "enableOutputSwap"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCNFG"
      ],
      "registersUsedMatchingBifield": [
        "HRCNFG"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setChannelBOutputPath",
      "functionArgs": [
        "base",
        "outputOnB"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_ChannelBOutput"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCNFG"
      ],
      "registersUsedMatchingBifield": [
        "HRCNFG"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_enableAutoConversion",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCNFG"
      ],
      "registersUsedMatchingBifield": [
        "HRCNFG"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_disableAutoConversion",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCNFG"
      ],
      "registersUsedMatchingBifield": [
        "HRCNFG"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_enablePeriodControl",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRPCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRPCTL"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_disablePeriodControl",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRPCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRPCTL"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_enablePhaseShiftLoad",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRPCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRPCTL"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_disablePhaseShiftLoad",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRPCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRPCTL"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setSyncPulseSource",
      "functionArgs": [
        "base",
        "syncPulseSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_SyncPulseSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRPCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRPCTL"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setTranslatorRemainder",
      "functionArgs": [
        "base",
        "trremVal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TRREM"
      ],
      "registersUsedMatchingBifield": [
        "TRREM"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setCounterCompareValue",
      "functionArgs": [
        "base",
        "compModule",
        "compCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_CounterCompareModule",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMPA",
        "CMPB"
      ],
      "registersUsedMatchingBifield": [
        "CMPA",
        "CMPB"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setHiResCounterCompareValueOnly",
      "functionArgs": [
        "base",
        "compModule",
        "hrCompCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_CounterCompareModule",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMPA",
        "CMPB"
      ],
      "registersUsedMatchingBifield": [
        "CMPA",
        "CMPB"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_getCounterCompareValue",
      "functionArgs": [
        "base",
        "compModule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_CounterCompareModule"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CMPA",
        "CMPB"
      ],
      "registersUsedMatchingBifield": [
        "CMPA",
        "CMPB"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_getHiResCounterCompareValueOnly",
      "functionArgs": [
        "base",
        "compModule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_CounterCompareModule"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "CMPA",
        "CMPB"
      ],
      "registersUsedMatchingBifield": [
        "CMPA",
        "CMPB"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setRisingEdgeDelay",
      "functionArgs": [
        "base",
        "redCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBREDHR",
        "DBRED"
      ],
      "registersUsedMatchingBifield": [
        "DBREDHR",
        "DBRED"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setHiResRisingEdgeDelayOnly",
      "functionArgs": [
        "base",
        "hrRedCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBREDHR",
        "DBRED"
      ],
      "registersUsedMatchingBifield": [
        "DBREDHR",
        "DBRED"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setFallingEdgeDelay",
      "functionArgs": [
        "base",
        "fedCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBFEDHR",
        "DBFED"
      ],
      "registersUsedMatchingBifield": [
        "DBFEDHR",
        "DBFED"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setHiResFallingEdgeDelayOnly",
      "functionArgs": [
        "base",
        "hrFedCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBFEDHR",
        "DBFED"
      ],
      "registersUsedMatchingBifield": [
        "DBFEDHR",
        "DBFED"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setMEPStep",
      "functionArgs": [
        "base",
        "mepCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRMSTEP"
      ],
      "registersUsedMatchingBifield": [
        "HRMSTEP"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setDeadbandMEPEdgeSelect",
      "functionArgs": [
        "base",
        "mepDBEdge"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_MEPDeadBandEdgeMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCNFG",
        "HRCNFG2"
      ],
      "registersUsedMatchingBifield": [
        "HRCNFG",
        "HRCNFG2"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setRisingEdgeDelayLoadMode",
      "functionArgs": [
        "base",
        "loadEvent"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_LoadMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCNFG",
        "HRCNFG2"
      ],
      "registersUsedMatchingBifield": [
        "HRCNFG",
        "HRCNFG2"
      ]
    },
    {
      "file": "hrpwm.h",
      "peripheral": "hrpwm",
      "functionName": "HRPWM_setFallingEdgeDelayLoadMode",
      "functionArgs": [
        "base",
        "loadEvent"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRPWM_LoadMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCNFG",
        "HRCNFG2"
      ],
      "registersUsedMatchingBifield": [
        "HRCNFG",
        "HRCNFG2"
      ]
    }
  ]
}
module.exports = { 
  hrpwm_driverlib: hrpwm_driverlib,
}
