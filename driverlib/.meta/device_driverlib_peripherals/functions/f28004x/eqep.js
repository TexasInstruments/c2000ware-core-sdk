let eqep_driverlib = 
{
  "name": "eqep",
  "functions": [
    {
      "file": "eqep.c",
      "peripheral": "eqep",
      "functionName": "EQEP_setCompareConfig",
      "functionArgs": [
        "base",
        "config",
        "compareValue",
        "cycles"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "QPOSCMP",
        "QDECCTL",
        "QPOSCTL"
      ],
      "registersUsedMatchingBifield": [
        "QPOSCMP",
        "QDECCTL",
        "QPOSCTL"
      ]
    },
    {
      "file": "eqep.c",
      "peripheral": "eqep",
      "functionName": "EQEP_setInputPolarity",
      "functionArgs": [
        "base",
        "invertQEPA",
        "invertQEPB",
        "invertIndex",
        "invertStrobe"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool",
        "bool",
        "bool",
        "bool"
      ],
      "returnType": "void",
      "registersUsed": [
        "QDECCTL"
      ],
      "registersUsedMatchingBifield": [
        "QDECCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_isBaseValid",
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
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_enableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QEPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QEPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_disableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QEPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QEPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setDecoderConfig",
      "functionArgs": [
        "base",
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QDECCTL"
      ],
      "registersUsedMatchingBifield": [
        "QDECCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setPositionCounterConfig",
      "functionArgs": [
        "base",
        "mode",
        "maxPosition"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EQEP_PositionResetMode",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QPOSMAX",
        "QEPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QPOSMAX",
        "QEPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getPosition",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "QPOSCNT"
      ],
      "registersUsedMatchingBifield": [
        "QPOSCNT"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setPosition",
      "functionArgs": [
        "base",
        "position"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QPOSCNT"
      ],
      "registersUsedMatchingBifield": [
        "QPOSCNT"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getDirection",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline int16_t",
      "registersUsed": [
        "QEPSTS"
      ],
      "registersUsedMatchingBifield": [
        "QEPSTS"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_enableInterrupt",
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
        "QEINT"
      ],
      "registersUsedMatchingBifield": [
        "QEINT"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_disableInterrupt",
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
        "QEINT"
      ],
      "registersUsedMatchingBifield": [
        "QEINT"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "QFLG"
      ],
      "registersUsedMatchingBifield": [
        "QFLG"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_clearInterruptStatus",
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
        "QCLR"
      ],
      "registersUsedMatchingBifield": [
        "QCLR"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_forceInterrupt",
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
        "QFRC"
      ],
      "registersUsedMatchingBifield": [
        "QFRC"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getError",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "QFLG"
      ],
      "registersUsedMatchingBifield": [
        "QFLG"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "QEPSTS"
      ],
      "registersUsedMatchingBifield": [
        "QEPSTS"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_clearStatus",
      "functionArgs": [
        "base",
        "statusFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QEPSTS"
      ],
      "registersUsedMatchingBifield": [
        "QEPSTS"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setCaptureConfig",
      "functionArgs": [
        "base",
        "capPrescale",
        "evntPrescale"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EQEP_CAPCLKPrescale",
        "EQEP_UPEVNTPrescale"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QCAPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QCAPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_enableCapture",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QCAPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QCAPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_disableCapture",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QCAPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QCAPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getCapturePeriod",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "QCPRD"
      ],
      "registersUsedMatchingBifield": [
        "QCPRD"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getCaptureTimer",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "QCTMR"
      ],
      "registersUsedMatchingBifield": [
        "QCTMR"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_enableCompare",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QPOSCTL"
      ],
      "registersUsedMatchingBifield": [
        "QPOSCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_disableCompare",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QPOSCTL"
      ],
      "registersUsedMatchingBifield": [
        "QPOSCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setComparePulseWidth",
      "functionArgs": [
        "base",
        "cycles"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QPOSCTL"
      ],
      "registersUsedMatchingBifield": [
        "QPOSCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_loadUnitTimer",
      "functionArgs": [
        "base",
        "period"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QUPRD"
      ],
      "registersUsedMatchingBifield": [
        "QUPRD"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_enableUnitTimer",
      "functionArgs": [
        "base",
        "period"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QUPRD",
        "QEPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QUPRD",
        "QEPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_disableUnitTimer",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QEPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QEPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_enableWatchdog",
      "functionArgs": [
        "base",
        "period"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QWDPRD",
        "QEPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QWDPRD",
        "QEPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_disableWatchdog",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QEPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QEPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setWatchdogTimerValue",
      "functionArgs": [
        "base",
        "value"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QWDTMR"
      ],
      "registersUsedMatchingBifield": [
        "QWDTMR"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getWatchdogTimerValue",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "QWDTMR"
      ],
      "registersUsedMatchingBifield": [
        "QWDTMR"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setPositionInitMode",
      "functionArgs": [
        "base",
        "initMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QEPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QEPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setSWPositionInit",
      "functionArgs": [
        "base",
        "initialize"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QEPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QEPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setInitialPosition",
      "functionArgs": [
        "base",
        "position"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QPOSINIT"
      ],
      "registersUsedMatchingBifield": [
        "QPOSINIT"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setLatchMode",
      "functionArgs": [
        "base",
        "latchMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QEPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QEPCTL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getIndexPositionLatch",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "QPOSILAT"
      ],
      "registersUsedMatchingBifield": [
        "QPOSILAT"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getStrobePositionLatch",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "QPOSSLAT"
      ],
      "registersUsedMatchingBifield": [
        "QPOSSLAT"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getPositionLatch",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "QPOSLAT"
      ],
      "registersUsedMatchingBifield": [
        "QPOSLAT"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getCaptureTimerLatch",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "QCTMR",
        "QCTMRLAT"
      ],
      "registersUsedMatchingBifield": [
        "QCTMR",
        "QCTMRLAT"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_getCapturePeriodLatch",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "QCPRD",
        "QCPRDLAT"
      ],
      "registersUsedMatchingBifield": [
        "QCPRD",
        "QCPRDLAT"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setQMAModuleMode",
      "functionArgs": [
        "base",
        "qmaMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EQEP_QMAMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QMACTRL"
      ],
      "registersUsedMatchingBifield": [
        "QMACTRL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setStrobeSource",
      "functionArgs": [
        "base",
        "strobeSrc"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EQEP_StrobeSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QEPSTROBESEL"
      ],
      "registersUsedMatchingBifield": [
        "QEPSTROBESEL"
      ]
    },
    {
      "file": "eqep.h",
      "peripheral": "eqep",
      "functionName": "EQEP_setEmulationMode",
      "functionArgs": [
        "base",
        "emuMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EQEP_EmulationMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "QEPCTL"
      ],
      "registersUsedMatchingBifield": [
        "QEPCTL"
      ]
    }
  ]
}
module.exports = { 
  eqep_driverlib: eqep_driverlib,
}
