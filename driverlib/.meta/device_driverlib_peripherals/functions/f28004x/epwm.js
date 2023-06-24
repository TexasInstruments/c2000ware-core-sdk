let epwm_driverlib = 
{
  "name": "epwm",
  "functions": [
    {
      "file": "epwm.c",
      "peripheral": "epwm",
      "functionName": "EPWM_setEmulationMode",
      "functionArgs": [
        "base",
        "emulationMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_EmulationMode"
      ],
      "returnType": "void",
      "registersUsed": [
        "TBCTL"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL"
      ]
    },
    {
      "file": "epwm.c",
      "peripheral": "epwm",
      "functionName": "EPWM_configureSignal",
      "functionArgs": [
        "base",
        "*signalParams"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constEPWM_SignalParams"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_isBaseValid",
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
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setTimeBaseCounter",
      "functionArgs": [
        "base",
        "count"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTR"
      ],
      "registersUsedMatchingBifield": [
        "TBCTR"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setCountModeAfterSync",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_SyncCountMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setClockPrescaler",
      "functionArgs": [
        "base",
        "prescaler",
        "highSpeedPrescaler"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ClockDivider",
        "EPWM_HSClockDivider"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_forceSyncPulse",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setSyncOutPulseMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_SyncOutPulseMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL",
        "TBCTL2"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL",
        "TBCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setPeriodLoadMode",
      "functionArgs": [
        "base",
        "loadMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_PeriodLoadMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enablePhaseShiftLoad",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disablePhaseShiftLoad",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setTimeBaseCounterMode",
      "functionArgs": [
        "base",
        "counterMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_TimeBaseCountMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_selectPeriodLoadEvent",
      "functionArgs": [
        "base",
        "shadowLoadMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_PeriodShadowLoadMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL",
        "TBCTL2"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL",
        "TBCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableOneShotSync",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL",
        "TBCTL2"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL",
        "TBCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableOneShotSync",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL",
        "TBCTL2"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL",
        "TBCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_startOneShotSync",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBCTL",
        "TBCTL2"
      ],
      "registersUsedMatchingBifield": [
        "TBCTL",
        "TBCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getTimeBaseCounterValue",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TBCTR"
      ],
      "registersUsedMatchingBifield": [
        "TBCTR"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getTimeBaseCounterOverflowStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "TBSTS"
      ],
      "registersUsedMatchingBifield": [
        "TBSTS"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_clearTimeBaseCounterOverflowEvent",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBSTS"
      ],
      "registersUsedMatchingBifield": [
        "TBSTS"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getSyncStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "TBSTS"
      ],
      "registersUsedMatchingBifield": [
        "TBSTS"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_clearSyncEvent",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBSTS"
      ],
      "registersUsedMatchingBifield": [
        "TBSTS"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getTimeBaseCounterDirection",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TBSTS"
      ],
      "registersUsedMatchingBifield": [
        "TBSTS"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setPhaseShift",
      "functionArgs": [
        "base",
        "phaseCount"
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
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setTimeBasePeriod",
      "functionArgs": [
        "base",
        "periodCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TBPRD"
      ],
      "registersUsedMatchingBifield": [
        "TBPRD"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getTimeBasePeriod",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TBPRD"
      ],
      "registersUsedMatchingBifield": [
        "TBPRD"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setupEPWMLinks",
      "functionArgs": [
        "base",
        "epwmLink",
        "linkComp"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_CurrentLink",
        "EPWM_LinkComponent"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "XLINK"
      ],
      "registersUsedMatchingBifield": [
        "XLINK"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setCounterCompareShadowLoadMode",
      "functionArgs": [
        "base",
        "compModule",
        "loadMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_CounterCompareModule",
        "EPWM_CounterCompareLoadMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMPCTL",
        "CMPCTL2",
        "CMPC",
        "CMPD"
      ],
      "registersUsedMatchingBifield": [
        "CMPCTL",
        "CMPCTL2",
        "CMPC",
        "CMPD"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableCounterCompareShadowLoadMode",
      "functionArgs": [
        "base",
        "compModule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_CounterCompareModule"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMPCTL",
        "CMPCTL2",
        "CMPC",
        "CMPD"
      ],
      "registersUsedMatchingBifield": [
        "CMPCTL",
        "CMPCTL2",
        "CMPC",
        "CMPD"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setCounterCompareValue",
      "functionArgs": [
        "base",
        "compModule",
        "compCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_CounterCompareModule",
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
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getCounterCompareValue",
      "functionArgs": [
        "base",
        "compModule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_CounterCompareModule"
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
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getCounterCompareShadowStatus",
      "functionArgs": [
        "base",
        "compModule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_CounterCompareModule"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CMPCTL",
        "CMPC",
        "CMPD"
      ],
      "registersUsedMatchingBifield": [
        "CMPCTL",
        "CMPC",
        "CMPD"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setActionQualifierShadowLoadMode",
      "functionArgs": [
        "base",
        "aqModule",
        "loadMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ActionQualifierModule",
        "EPWM_ActionQualifierLoadMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AQCTL"
      ],
      "registersUsedMatchingBifield": [
        "AQCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableActionQualifierShadowLoadMode",
      "functionArgs": [
        "base",
        "aqModule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ActionQualifierModule"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AQCTL"
      ],
      "registersUsedMatchingBifield": [
        "AQCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setActionQualifierT1TriggerSource",
      "functionArgs": [
        "base",
        "trigger"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ActionQualifierTriggerSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AQTSRCSEL"
      ],
      "registersUsedMatchingBifield": [
        "AQTSRCSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setActionQualifierT2TriggerSource",
      "functionArgs": [
        "base",
        "trigger"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ActionQualifierTriggerSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AQTSRCSEL"
      ],
      "registersUsedMatchingBifield": [
        "AQTSRCSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setActionQualifierAction",
      "functionArgs": [
        "base",
        "epwmOutput",
        "output",
        "event"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ActionQualifierOutputModule",
        "EPWM_ActionQualifierOutput",
        "EPWM_ActionQualifierOutputEvent"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AQCTL",
        "AQCTLA",
        "AQCTLB",
        "AQCTLA2",
        "AQCTLB2"
      ],
      "registersUsedMatchingBifield": [
        "AQCTL",
        "AQCTLA",
        "AQCTLB",
        "AQCTLA2",
        "AQCTLB2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setActionQualifierActionComplete",
      "functionArgs": [
        "base",
        "epwmOutput",
        "action"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ActionQualifierOutputModule",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AQCTL",
        "AQCTLA",
        "AQCTLB"
      ],
      "registersUsedMatchingBifield": [
        "AQCTL",
        "AQCTLA",
        "AQCTLB"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setAdditionalActionQualifierActionComplete",
      "functionArgs": [
        "base",
        "epwmOutput",
        "action"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ActionQualifierOutputModule",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AQCTL",
        "AQCTLA",
        "AQCTLB",
        "AQCTLA2",
        "AQCTLB2"
      ],
      "registersUsedMatchingBifield": [
        "AQCTL",
        "AQCTLA",
        "AQCTLB",
        "AQCTLA2",
        "AQCTLB2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setActionQualifierContSWForceShadowMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ActionQualifierContForce"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AQSFRC"
      ],
      "registersUsedMatchingBifield": [
        "AQSFRC"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setActionQualifierContSWForceAction",
      "functionArgs": [
        "base",
        "epwmOutput",
        "output"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ActionQualifierOutputModule",
        "EPWM_ActionQualifierSWOutput"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AQCSFRC"
      ],
      "registersUsedMatchingBifield": [
        "AQCSFRC"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setActionQualifierSWAction",
      "functionArgs": [
        "base",
        "epwmOutput",
        "output"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ActionQualifierOutputModule",
        "EPWM_ActionQualifierOutput"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AQSFRC"
      ],
      "registersUsedMatchingBifield": [
        "AQSFRC"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_forceActionQualifierSWAction",
      "functionArgs": [
        "base",
        "epwmOutput"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ActionQualifierOutputModule"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AQSFRC"
      ],
      "registersUsedMatchingBifield": [
        "AQSFRC"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDeadBandOutputSwapMode",
      "functionArgs": [
        "base",
        "output",
        "enableSwapMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DeadBandOutput",
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDeadBandDelayMode",
      "functionArgs": [
        "base",
        "delayMode",
        "enableDelayMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DeadBandDelayMode",
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDeadBandDelayPolarity",
      "functionArgs": [
        "base",
        "delayMode",
        "polarity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DeadBandDelayMode",
        "EPWM_DeadBandPolarity"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setRisingEdgeDeadBandDelayInput",
      "functionArgs": [
        "base",
        "input"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setFallingEdgeDeadBandDelayInput",
      "functionArgs": [
        "base",
        "input"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDeadBandControlShadowLoadMode",
      "functionArgs": [
        "base",
        "loadMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DeadBandControlLoadMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL",
        "DBCTL2"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL",
        "DBCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableDeadBandControlShadowLoadMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL",
        "DBCTL2"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL",
        "DBCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setRisingEdgeDelayCountShadowLoadMode",
      "functionArgs": [
        "base",
        "loadMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_RisingEdgeDelayLoadMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableRisingEdgeDelayCountShadowLoadMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setFallingEdgeDelayCountShadowLoadMode",
      "functionArgs": [
        "base",
        "loadMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_FallingEdgeDelayLoadMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableFallingEdgeDelayCountShadowLoadMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDeadBandCounterClock",
      "functionArgs": [
        "base",
        "clockMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DeadBandClockMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setRisingEdgeDelayCount",
      "functionArgs": [
        "base",
        "redCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBRED"
      ],
      "registersUsedMatchingBifield": [
        "DBRED"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setFallingEdgeDelayCount",
      "functionArgs": [
        "base",
        "fedCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBFED"
      ],
      "registersUsedMatchingBifield": [
        "DBFED"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableChopper",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCCTL"
      ],
      "registersUsedMatchingBifield": [
        "PCCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableChopper",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCCTL"
      ],
      "registersUsedMatchingBifield": [
        "PCCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setChopperDutyCycle",
      "functionArgs": [
        "base",
        "dutyCycleCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCCTL"
      ],
      "registersUsedMatchingBifield": [
        "PCCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setChopperFreq",
      "functionArgs": [
        "base",
        "freqDiv"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCCTL"
      ],
      "registersUsedMatchingBifield": [
        "PCCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setChopperFirstPulseWidth",
      "functionArgs": [
        "base",
        "firstPulseWidth"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCCTL"
      ],
      "registersUsedMatchingBifield": [
        "PCCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableTripZoneSignals",
      "functionArgs": [
        "base",
        "tzSignal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZSEL"
      ],
      "registersUsedMatchingBifield": [
        "TZSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableTripZoneSignals",
      "functionArgs": [
        "base",
        "tzSignal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZSEL"
      ],
      "registersUsedMatchingBifield": [
        "TZSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setTripZoneDigitalCompareEventCondition",
      "functionArgs": [
        "base",
        "dcType",
        "dcEvent"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_TripZoneDigitalCompareOutput",
        "EPWM_TripZoneDigitalCompareOutputEvent"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZDCSEL"
      ],
      "registersUsedMatchingBifield": [
        "TZDCSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableTripZoneAdvAction",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZCTL",
        "TZCTL2"
      ],
      "registersUsedMatchingBifield": [
        "TZCTL",
        "TZCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableTripZoneAdvAction",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZCTL",
        "TZCTL2"
      ],
      "registersUsedMatchingBifield": [
        "TZCTL",
        "TZCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setTripZoneAction",
      "functionArgs": [
        "base",
        "tzEvent",
        "tzAction"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_TripZoneEvent",
        "EPWM_TripZoneAction"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZCTL"
      ],
      "registersUsedMatchingBifield": [
        "TZCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setTripZoneAdvAction",
      "functionArgs": [
        "base",
        "tzAdvEvent",
        "tzAdvAction"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_TripZoneAdvancedEvent",
        "EPWM_TripZoneAdvancedAction"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZCTL",
        "TZCTL2"
      ],
      "registersUsedMatchingBifield": [
        "TZCTL",
        "TZCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setTripZoneAdvDigitalCompareActionA",
      "functionArgs": [
        "base",
        "tzAdvDCEvent",
        "tzAdvDCAction"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_TripZoneAdvDigitalCompareEvent",
        "EPWM_TripZoneAdvancedAction"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZCTL",
        "TZCTL2",
        "TZCTLDCA"
      ],
      "registersUsedMatchingBifield": [
        "TZCTL",
        "TZCTL2",
        "TZCTLDCA"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setTripZoneAdvDigitalCompareActionB",
      "functionArgs": [
        "base",
        "tzAdvDCEvent",
        "tzAdvDCAction"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_TripZoneAdvDigitalCompareEvent",
        "EPWM_TripZoneAdvancedAction"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZCTL",
        "TZCTL2",
        "TZCTLDCB"
      ],
      "registersUsedMatchingBifield": [
        "TZCTL",
        "TZCTL2",
        "TZCTLDCB"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableTripZoneInterrupt",
      "functionArgs": [
        "base",
        "tzInterrupt"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZEINT"
      ],
      "registersUsedMatchingBifield": [
        "TZEINT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableTripZoneInterrupt",
      "functionArgs": [
        "base",
        "tzInterrupt"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZEINT"
      ],
      "registersUsedMatchingBifield": [
        "TZEINT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getTripZoneFlagStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TZFLG"
      ],
      "registersUsedMatchingBifield": [
        "TZFLG"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getCycleByCycleTripZoneFlagStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TZCBCFLG"
      ],
      "registersUsedMatchingBifield": [
        "TZCBCFLG"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getOneShotTripZoneFlagStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TZOSTFLG"
      ],
      "registersUsedMatchingBifield": [
        "TZOSTFLG"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_selectCycleByCycleTripZoneClearEvent",
      "functionArgs": [
        "base",
        "clearEvent"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_CycleByCycleTripZoneClearMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZCLR"
      ],
      "registersUsedMatchingBifield": [
        "TZCLR"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_clearTripZoneFlag",
      "functionArgs": [
        "base",
        "tzFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZCLR"
      ],
      "registersUsedMatchingBifield": [
        "TZCLR"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_clearCycleByCycleTripZoneFlag",
      "functionArgs": [
        "base",
        "tzCBCFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZCBCCLR"
      ],
      "registersUsedMatchingBifield": [
        "TZCBCCLR"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_clearOneShotTripZoneFlag",
      "functionArgs": [
        "base",
        "tzOSTFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZOSTCLR"
      ],
      "registersUsedMatchingBifield": [
        "TZOSTCLR"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_forceTripZoneEvent",
      "functionArgs": [
        "base",
        "tzForceEvent"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TZFRC"
      ],
      "registersUsedMatchingBifield": [
        "TZFRC"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETSEL"
      ],
      "registersUsedMatchingBifield": [
        "ETSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETSEL"
      ],
      "registersUsedMatchingBifield": [
        "ETSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setInterruptSource",
      "functionArgs": [
        "base",
        "interruptSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETSEL"
      ],
      "registersUsedMatchingBifield": [
        "ETSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setInterruptEventCount",
      "functionArgs": [
        "base",
        "eventCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETPS",
        "ETINTPS"
      ],
      "registersUsedMatchingBifield": [
        "ETPS",
        "ETINTPS"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getEventTriggerInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "ETFLG"
      ],
      "registersUsedMatchingBifield": [
        "ETFLG"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_clearEventTriggerInterruptFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETCLR"
      ],
      "registersUsedMatchingBifield": [
        "ETCLR"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableInterruptEventCountInit",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ],
      "registersUsedMatchingBifield": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableInterruptEventCountInit",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ],
      "registersUsedMatchingBifield": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_forceInterruptEventCountInit",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ],
      "registersUsedMatchingBifield": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setInterruptEventCountInitValue",
      "functionArgs": [
        "base",
        "eventCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETCNTINIT"
      ],
      "registersUsedMatchingBifield": [
        "ETCNTINIT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getInterruptEventCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "ETINTPS"
      ],
      "registersUsedMatchingBifield": [
        "ETINTPS"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_forceEventTriggerInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETFRC"
      ],
      "registersUsedMatchingBifield": [
        "ETFRC"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableADCTrigger",
      "functionArgs": [
        "base",
        "adcSOCType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETSEL"
      ],
      "registersUsedMatchingBifield": [
        "ETSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableADCTrigger",
      "functionArgs": [
        "base",
        "adcSOCType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETSEL"
      ],
      "registersUsedMatchingBifield": [
        "ETSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setADCTriggerSource",
      "functionArgs": [
        "base",
        "adcSOCType",
        "socSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType",
        "EPWM_ADCStartOfConversionSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETSEL"
      ],
      "registersUsedMatchingBifield": [
        "ETSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setADCTriggerEventPrescale",
      "functionArgs": [
        "base",
        "adcSOCType",
        "preScaleCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETPS",
        "ETSOCPS"
      ],
      "registersUsedMatchingBifield": [
        "ETPS",
        "ETSOCPS"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getADCTriggerFlagStatus",
      "functionArgs": [
        "base",
        "adcSOCType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "ETFLG"
      ],
      "registersUsedMatchingBifield": [
        "ETFLG"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_clearADCTriggerFlag",
      "functionArgs": [
        "base",
        "adcSOCType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETCLR"
      ],
      "registersUsedMatchingBifield": [
        "ETCLR"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableADCTriggerEventCountInit",
      "functionArgs": [
        "base",
        "adcSOCType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ],
      "registersUsedMatchingBifield": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableADCTriggerEventCountInit",
      "functionArgs": [
        "base",
        "adcSOCType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ],
      "registersUsedMatchingBifield": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_forceADCTriggerEventCountInit",
      "functionArgs": [
        "base",
        "adcSOCType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ],
      "registersUsedMatchingBifield": [
        "ETCNTINITCTL",
        "ETCNTINIT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setADCTriggerEventCountInitValue",
      "functionArgs": [
        "base",
        "adcSOCType",
        "eventCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETCNTINIT"
      ],
      "registersUsedMatchingBifield": [
        "ETCNTINIT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getADCTriggerEventCount",
      "functionArgs": [
        "base",
        "adcSOCType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "ETSOCPS"
      ],
      "registersUsedMatchingBifield": [
        "ETSOCPS"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_forceADCTrigger",
      "functionArgs": [
        "base",
        "adcSOCType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ADCStartOfConversionType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETFRC"
      ],
      "registersUsedMatchingBifield": [
        "ETFRC"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_selectDigitalCompareTripInput",
      "functionArgs": [
        "base",
        "tripSource",
        "dcType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DigitalCompareTripInput",
        "EPWM_DigitalCompareType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCTRIPSEL"
      ],
      "registersUsedMatchingBifield": [
        "DCTRIPSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableDigitalCompareBlankingWindow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableDigitalCompareBlankingWindow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableDigitalCompareWindowInverseMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableDigitalCompareWindowInverseMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDigitalCompareBlankingEvent",
      "functionArgs": [
        "base",
        "blankingPulse"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DigitalCompareBlankingPulse"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDigitalCompareFilterInput",
      "functionArgs": [
        "base",
        "filterInput"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DigitalCompareFilterInput"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableDigitalCompareEdgeFilter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableDigitalCompareEdgeFilter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDigitalCompareEdgeFilterMode",
      "functionArgs": [
        "base",
        "edgeMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DigitalCompareEdgeFilterMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDigitalCompareEdgeFilterEdgeCount",
      "functionArgs": [
        "base",
        "edgeCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getDigitalCompareEdgeFilterEdgeCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getDigitalCompareEdgeFilterEdgeStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "DCFCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCFCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDigitalCompareWindowOffset",
      "functionArgs": [
        "base",
        "windowOffsetCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFOFFSET"
      ],
      "registersUsedMatchingBifield": [
        "DCFOFFSET"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDigitalCompareWindowLength",
      "functionArgs": [
        "base",
        "windowLengthCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCFWINDOW"
      ],
      "registersUsedMatchingBifield": [
        "DCFWINDOW"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getDigitalCompareBlankingWindowOffsetCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "DCFOFFSET",
        "DCFOFFSETCNT"
      ],
      "registersUsedMatchingBifield": [
        "DCFOFFSET",
        "DCFOFFSETCNT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getDigitalCompareBlankingWindowLengthCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "DCFWINDOW",
        "DCFWINDOWCNT"
      ],
      "registersUsedMatchingBifield": [
        "DCFWINDOW",
        "DCFWINDOWCNT"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDigitalCompareEventSource",
      "functionArgs": [
        "base",
        "dcModule",
        "dcEvent",
        "dcEventSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DigitalCompareModule",
        "EPWM_DigitalCompareEvent",
        "EPWM_DigitalCompareEventSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCACTL",
        "DCBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCACTL",
        "DCBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDigitalCompareEventSyncMode",
      "functionArgs": [
        "base",
        "dcModule",
        "dcEvent",
        "syncMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DigitalCompareModule",
        "EPWM_DigitalCompareEvent",
        "EPWM_DigitalCompareSyncMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCACTL",
        "DCBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCACTL",
        "DCBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableDigitalCompareADCTrigger",
      "functionArgs": [
        "base",
        "dcModule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DigitalCompareModule"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCACTL",
        "DCBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCACTL",
        "DCBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableDigitalCompareADCTrigger",
      "functionArgs": [
        "base",
        "dcModule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DigitalCompareModule"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCACTL",
        "DCBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCACTL",
        "DCBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableDigitalCompareSyncEvent",
      "functionArgs": [
        "base",
        "dcModule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DigitalCompareModule"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCACTL",
        "DCBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCACTL",
        "DCBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableDigitalCompareSyncEvent",
      "functionArgs": [
        "base",
        "dcModule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_DigitalCompareModule"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCACTL",
        "DCBCTL"
      ],
      "registersUsedMatchingBifield": [
        "DCACTL",
        "DCBCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableDigitalCompareCounterCapture",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCCAPCTL",
        "DCCAP"
      ],
      "registersUsedMatchingBifield": [
        "DCCAPCTL",
        "DCCAP"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableDigitalCompareCounterCapture",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCCAPCTL",
        "DCCAP"
      ],
      "registersUsedMatchingBifield": [
        "DCCAPCTL",
        "DCCAP"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setDigitalCompareCounterShadowMode",
      "functionArgs": [
        "base",
        "enableShadowMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCCAPCTL",
        "DCCAP"
      ],
      "registersUsedMatchingBifield": [
        "DCCAPCTL",
        "DCCAP"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getDigitalCompareCaptureStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "DCCAPCTL",
        "DCCAP"
      ],
      "registersUsedMatchingBifield": [
        "DCCAPCTL",
        "DCCAP"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getDigitalCompareCaptureCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "DCCAP"
      ],
      "registersUsedMatchingBifield": [
        "DCCAP"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableDigitalCompareTripCombinationInput",
      "functionArgs": [
        "base",
        "tripInput",
        "dcType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "EPWM_DigitalCompareType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCTRIPSEL",
        "DCAHTRIPSEL",
        "DCALTRIPSEL",
        "DCBHTRIPSEL",
        "DCBLTRIPSEL"
      ],
      "registersUsedMatchingBifield": [
        "DCTRIPSEL",
        "DCAHTRIPSEL",
        "DCALTRIPSEL",
        "DCBHTRIPSEL",
        "DCBLTRIPSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableDigitalCompareTripCombinationInput",
      "functionArgs": [
        "base",
        "tripInput",
        "dcType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "EPWM_DigitalCompareType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DCAHTRIPSEL",
        "DCALTRIPSEL",
        "DCBHTRIPSEL",
        "DCBLTRIPSEL"
      ],
      "registersUsedMatchingBifield": [
        "DCAHTRIPSEL",
        "DCALTRIPSEL",
        "DCBHTRIPSEL",
        "DCBLTRIPSEL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableValleyCapture",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "VCAPCTL"
      ],
      "registersUsedMatchingBifield": [
        "VCAPCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableValleyCapture",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "VCAPCTL"
      ],
      "registersUsedMatchingBifield": [
        "VCAPCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_startValleyCapture",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "VCAPCTL"
      ],
      "registersUsedMatchingBifield": [
        "VCAPCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setValleyTriggerSource",
      "functionArgs": [
        "base",
        "trigger"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ValleyTriggerSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "VCAPCTL"
      ],
      "registersUsedMatchingBifield": [
        "VCAPCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setValleyTriggerEdgeCounts",
      "functionArgs": [
        "base",
        "startCount",
        "stopCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "VCNTCFG"
      ],
      "registersUsedMatchingBifield": [
        "VCNTCFG"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableValleyHWDelay",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "VCAPCTL"
      ],
      "registersUsedMatchingBifield": [
        "VCAPCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableValleyHWDelay",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "VCAPCTL"
      ],
      "registersUsedMatchingBifield": [
        "VCAPCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setValleySWDelayValue",
      "functionArgs": [
        "base",
        "delayOffsetValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SWVDELVAL"
      ],
      "registersUsedMatchingBifield": [
        "SWVDELVAL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setValleyDelayDivider",
      "functionArgs": [
        "base",
        "delayMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ValleyDelayMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "VCAPCTL"
      ],
      "registersUsedMatchingBifield": [
        "VCAPCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getValleyEdgeStatus",
      "functionArgs": [
        "base",
        "edge"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_ValleyCounterEdge"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "VCNTCFG"
      ],
      "registersUsedMatchingBifield": [
        "VCNTCFG"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getValleyCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "VCNTVAL"
      ],
      "registersUsedMatchingBifield": [
        "VCNTVAL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getValleyHWDelay",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "HWVDELVAL"
      ],
      "registersUsedMatchingBifield": [
        "HWVDELVAL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableGlobalLoad",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLDCTL"
      ],
      "registersUsedMatchingBifield": [
        "GLDCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableGlobalLoad",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLDCTL"
      ],
      "registersUsedMatchingBifield": [
        "GLDCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setGlobalLoadTrigger",
      "functionArgs": [
        "base",
        "loadTrigger"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_GlobalLoadTrigger"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLDCTL"
      ],
      "registersUsedMatchingBifield": [
        "GLDCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setGlobalLoadEventPrescale",
      "functionArgs": [
        "base",
        "prescalePulseCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLDCTL"
      ],
      "registersUsedMatchingBifield": [
        "GLDCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_getGlobalLoadEventCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "GLDCTL"
      ],
      "registersUsedMatchingBifield": [
        "GLDCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableGlobalLoadOneShotMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLDCTL"
      ],
      "registersUsedMatchingBifield": [
        "GLDCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableGlobalLoadOneShotMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLDCTL"
      ],
      "registersUsedMatchingBifield": [
        "GLDCTL"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_setGlobalLoadOneShotLatch",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLDCTL",
        "GLDCTL2"
      ],
      "registersUsedMatchingBifield": [
        "GLDCTL",
        "GLDCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_forceGlobalLoadOneShotEvent",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLDCTL",
        "GLDCTL2"
      ],
      "registersUsedMatchingBifield": [
        "GLDCTL",
        "GLDCTL2"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_enableGlobalLoadRegisters",
      "functionArgs": [
        "base",
        "loadRegister"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLDCFG"
      ],
      "registersUsedMatchingBifield": [
        "GLDCFG"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_disableGlobalLoadRegisters",
      "functionArgs": [
        "base",
        "loadRegister"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLDCFG"
      ],
      "registersUsedMatchingBifield": [
        "GLDCFG"
      ]
    },
    {
      "file": "epwm.h",
      "peripheral": "epwm",
      "functionName": "EPWM_lockRegisters",
      "functionArgs": [
        "base",
        "registerGroup"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPWM_LockRegisterGroup"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOCK"
      ],
      "registersUsedMatchingBifield": [
        "LOCK"
      ]
    }
  ]
}
module.exports = { 
  epwm_driverlib: epwm_driverlib,
}
