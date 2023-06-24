let bgcrc_driverlib = 
{
  "name": "bgcrc",
  "functions": [
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_isBaseValid",
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
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_setConfig",
      "functionArgs": [
        "base",
        "nmiConfig",
        "emuCtrl"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTRL1"
      ],
      "registersUsedMatchingBifield": [
        "CTRL1"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_enableWatchdog",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WD_CFG"
      ],
      "registersUsedMatchingBifield": [
        "WD_CFG"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_disableWatchdog",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WD_CFG"
      ],
      "registersUsedMatchingBifield": [
        "WD_CFG"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_setWatchdogWindow",
      "functionArgs": [
        "base",
        "min",
        "max"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WD_MIN",
        "WD_MAX"
      ],
      "registersUsedMatchingBifield": [
        "WD_MIN",
        "WD_MAX"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_setRegion",
      "functionArgs": [
        "base",
        "startAddr",
        "blockSize",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTRL2",
        "START_ADDR"
      ],
      "registersUsedMatchingBifield": [
        "CTRL2",
        "START_ADDR"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_getWatchdogCounterValue",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "WD_CNT"
      ],
      "registersUsedMatchingBifield": [
        "WD_CNT"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_enableInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTEN"
      ],
      "registersUsedMatchingBifield": [
        "INTEN"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_disableInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTEN"
      ],
      "registersUsedMatchingBifield": [
        "INTEN"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_getInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "INTFLG"
      ],
      "registersUsedMatchingBifield": [
        "INTFLG"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_clearInterruptStatus",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTCLR"
      ],
      "registersUsedMatchingBifield": [
        "INTCLR"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_forceInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTFRC"
      ],
      "registersUsedMatchingBifield": [
        "INTFRC"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_getNMIStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "NMIFLG"
      ],
      "registersUsedMatchingBifield": [
        "NMIFLG"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_clearNMIStatus",
      "functionArgs": [
        "base",
        "nmiFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "NMICLR"
      ],
      "registersUsedMatchingBifield": [
        "NMICLR"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_forceNMI",
      "functionArgs": [
        "base",
        "nmiFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "NMIFRC"
      ],
      "registersUsedMatchingBifield": [
        "NMIFRC"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_setGoldenCRCValue",
      "functionArgs": [
        "base",
        "crcVal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GOLDEN"
      ],
      "registersUsedMatchingBifield": [
        "GOLDEN"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_start",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "EN"
      ],
      "registersUsedMatchingBifield": [
        "EN"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_halt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTRL2"
      ],
      "registersUsedMatchingBifield": [
        "CTRL2"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_resume",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTRL2"
      ],
      "registersUsedMatchingBifield": [
        "CTRL2"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_getRunStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "EN"
      ],
      "registersUsedMatchingBifield": [
        "EN"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_setSeedValue",
      "functionArgs": [
        "base",
        "seed"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SEED"
      ],
      "registersUsedMatchingBifield": [
        "SEED"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_getResult",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "RESULT"
      ],
      "registersUsedMatchingBifield": [
        "RESULT"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_getCurrentAddress",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CURR_ADDR"
      ],
      "registersUsedMatchingBifield": [
        "CURR_ADDR"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_lockRegister",
      "functionArgs": [
        "base",
        "regs"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOCK"
      ],
      "registersUsedMatchingBifield": [
        "LOCK"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_unlockRegister",
      "functionArgs": [
        "base",
        "regs"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOCK"
      ],
      "registersUsedMatchingBifield": [
        "LOCK"
      ]
    },
    {
      "file": "bgcrc.h",
      "peripheral": "bgcrc",
      "functionName": "BGCRC_commitRegisterLock",
      "functionArgs": [
        "base",
        "regs"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMMIT"
      ],
      "registersUsedMatchingBifield": [
        "COMMIT"
      ]
    }
  ]
}
module.exports = { 
  bgcrc_driverlib: bgcrc_driverlib,
}
