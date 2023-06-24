let ecap_driverlib = 
{
  "name": "ecap",
  "functions": [
    {
      "file": "ecap.c",
      "peripheral": "ecap",
      "functionName": "ECAP_setEmulationMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ECAP_EmulationMode"
      ],
      "returnType": "void",
      "registersUsed": [
        "ECCTL1"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL1"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_isBaseValid",
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
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_setEventPrescaler",
      "functionArgs": [
        "base",
        "preScalerValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL1"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL1"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_setEventPolarity",
      "functionArgs": [
        "base",
        "event",
        "polarity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ECAP_Events",
        "ECAP_EventPolarity"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL1"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL1"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_setCaptureMode",
      "functionArgs": [
        "base",
        "mode",
        "event"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ECAP_CaptureMode",
        "ECAP_Events"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL2"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_reArm",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL2"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_enableInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECEINT"
      ],
      "registersUsedMatchingBifield": [
        "ECEINT"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_disableInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECEINT"
      ],
      "registersUsedMatchingBifield": [
        "ECEINT"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_getInterruptSource",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "ECFLG"
      ],
      "registersUsedMatchingBifield": [
        "ECFLG"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_getGlobalInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "ECFLG"
      ],
      "registersUsedMatchingBifield": [
        "ECFLG"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_clearInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCLR"
      ],
      "registersUsedMatchingBifield": [
        "ECCLR"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_clearGlobalInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCLR"
      ],
      "registersUsedMatchingBifield": [
        "ECCLR"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_forceInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECFRC"
      ],
      "registersUsedMatchingBifield": [
        "ECFRC"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_enableCaptureMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL2"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_enableAPWMMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL2"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_enableCounterResetOnEvent",
      "functionArgs": [
        "base",
        "event"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ECAP_Events"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL1"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL1"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_disableCounterResetOnEvent",
      "functionArgs": [
        "base",
        "event"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ECAP_Events"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL1"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL1"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_enableTimeStampCapture",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL1"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL1"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_disableTimeStampCapture",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL1"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL1"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_setPhaseShiftCount",
      "functionArgs": [
        "base",
        "shiftCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTRPHS"
      ],
      "registersUsedMatchingBifield": [
        "CTRPHS"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_enableLoadCounter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL2"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_disableLoadCounter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL2"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_loadCounter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL2"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_setSyncOutMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ECAP_SyncOutMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL2"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_stopCounter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL2"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_startCounter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL2"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_setAPWMPolarity",
      "functionArgs": [
        "base",
        "polarity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ECAP_APWMPolarity"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECCTL2"
      ],
      "registersUsedMatchingBifield": [
        "ECCTL2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_setAPWMPeriod",
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
        "CAP1"
      ],
      "registersUsedMatchingBifield": [
        "CAP1"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_setAPWMCompare",
      "functionArgs": [
        "base",
        "compareCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CAP2"
      ],
      "registersUsedMatchingBifield": [
        "CAP2"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_setAPWMShadowPeriod",
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
        "CAP3"
      ],
      "registersUsedMatchingBifield": [
        "CAP3"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_setAPWMShadowCompare",
      "functionArgs": [
        "base",
        "compareCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CAP4"
      ],
      "registersUsedMatchingBifield": [
        "CAP4"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_getTimeBaseCounter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "TSCTR"
      ],
      "registersUsedMatchingBifield": [
        "TSCTR"
      ]
    },
    {
      "file": "ecap.h",
      "peripheral": "ecap",
      "functionName": "ECAP_getEventTimeStamp",
      "functionArgs": [
        "base",
        "event"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ECAP_Events"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CAP1",
        "CAP2",
        "CAP3",
        "CAP4"
      ],
      "registersUsedMatchingBifield": [
        "CAP1",
        "CAP2",
        "CAP3",
        "CAP4"
      ]
    }
  ]
}
module.exports = { 
  ecap_driverlib: ecap_driverlib,
}
