let emif_driverlib = 
{
  "name": "emif",
  "functions": [
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_isBaseValid",
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
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_isEMIF1ConfigBaseValid",
      "functionArgs": [
        "configBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef DEBUG  static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_isEMIF2ConfigBaseValid",
      "functionArgs": [
        "configBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef DEBUG  static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_selectMaster",
      "functionArgs": [
        "configBase",
        "select"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EMIF_MasterSelect"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "EMIF1MSEL"
      ],
      "registersUsedMatchingBifield": [
        "EMIF1MSEL"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_setAccessProtection",
      "functionArgs": [
        "configBase",
        "access"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "EMIF1ACCPROT0"
      ],
      "registersUsedMatchingBifield": [
        "EMIF1ACCPROT0"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_commitAccessConfig",
      "functionArgs": [
        "configBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "EMIF1COMMIT"
      ],
      "registersUsedMatchingBifield": [
        "EMIF1COMMIT"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_lockAccessConfig",
      "functionArgs": [
        "configBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "EMIF1LOCK"
      ],
      "registersUsedMatchingBifield": [
        "EMIF1LOCK"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_unlockAccessConfig",
      "functionArgs": [
        "configBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "EMIF1LOCK"
      ],
      "registersUsedMatchingBifield": [
        "EMIF1LOCK"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_setAsyncMode",
      "functionArgs": [
        "base",
        "offset",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EMIF_AsyncCSOffset",
        "EMIF_AsyncMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ASYNC_CS2_CR",
        "ASYNC_CS3_CR",
        "ASYNC_CS4_CR"
      ],
      "registersUsedMatchingBifield": [
        "ASYNC_CS2_CR",
        "ASYNC_CS3_CR",
        "ASYNC_CS4_CR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_enableAsyncExtendedWait",
      "functionArgs": [
        "base",
        "offset"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EMIF_AsyncCSOffset"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ASYNC_CS2_CR",
        "ASYNC_CS3_CR",
        "ASYNC_CS4_CR"
      ],
      "registersUsedMatchingBifield": [
        "ASYNC_CS2_CR",
        "ASYNC_CS3_CR",
        "ASYNC_CS4_CR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_setAsyncWaitPolarity",
      "functionArgs": [
        "base",
        "polarity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EMIF_AsyncWaitPolarity"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ASYNC_WCCR"
      ],
      "registersUsedMatchingBifield": [
        "ASYNC_WCCR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_setAsyncMaximumWaitCycles",
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
        "ASYNC_WCCR"
      ],
      "registersUsedMatchingBifield": [
        "ASYNC_WCCR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_setAsyncTimingParams",
      "functionArgs": [
        "base",
        "offset",
        "*tParam"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EMIF_AsyncCSOffset",
        "constEMIF_AsyncTimingParams"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ASYNC_CS2_CR",
        "ASYNC_CS3_CR",
        "ASYNC_CS4_CR"
      ],
      "registersUsedMatchingBifield": [
        "ASYNC_CS2_CR",
        "ASYNC_CS3_CR",
        "ASYNC_CS4_CR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_setAsyncDataBusWidth",
      "functionArgs": [
        "base",
        "offset",
        "width"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EMIF_AsyncCSOffset",
        "EMIF_AsyncDataWidth"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ASYNC_CS2_CR",
        "ASYNC_CS3_CR",
        "ASYNC_CS4_CR"
      ],
      "registersUsedMatchingBifield": [
        "ASYNC_CS2_CR",
        "ASYNC_CS3_CR",
        "ASYNC_CS4_CR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_enableAsyncInterrupt",
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
        "INT_MSK",
        "INT_MSK_SET"
      ],
      "registersUsedMatchingBifield": [
        "INT_MSK",
        "INT_MSK_SET"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_disableAsyncInterrupt",
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
        "INT_MSK",
        "INT_MSK_CLR"
      ],
      "registersUsedMatchingBifield": [
        "INT_MSK",
        "INT_MSK_CLR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_getAsyncInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "INT_MSK"
      ],
      "registersUsedMatchingBifield": [
        "INT_MSK"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_clearAsyncInterruptStatus",
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
        "INT_MSK"
      ],
      "registersUsedMatchingBifield": [
        "INT_MSK"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_setSyncTimingParams",
      "functionArgs": [
        "base",
        "*tParam"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constEMIF_SyncTimingParams"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SDRAM_TR"
      ],
      "registersUsedMatchingBifield": [
        "SDRAM_TR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_setSyncSelfRefreshExitTmng",
      "functionArgs": [
        "base",
        "tXs"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SDR_EXT_TMNG"
      ],
      "registersUsedMatchingBifield": [
        "SDR_EXT_TMNG"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_setSyncRefreshRate",
      "functionArgs": [
        "base",
        "refRate"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SDRAM_RCR"
      ],
      "registersUsedMatchingBifield": [
        "SDRAM_RCR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_setSyncMemoryConfig",
      "functionArgs": [
        "base",
        "*config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constEMIF_SyncConfig"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SDRAM_CR"
      ],
      "registersUsedMatchingBifield": [
        "SDRAM_CR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_enableSyncSelfRefresh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SDRAM_CR"
      ],
      "registersUsedMatchingBifield": [
        "SDRAM_CR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_disableSyncSelfRefresh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SDRAM_CR"
      ],
      "registersUsedMatchingBifield": [
        "SDRAM_CR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_enableSyncPowerDown",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SDRAM_CR"
      ],
      "registersUsedMatchingBifield": [
        "SDRAM_CR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_disableSyncPowerDown",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SDRAM_CR"
      ],
      "registersUsedMatchingBifield": [
        "SDRAM_CR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_enableSyncRefreshInPowerDown",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SDRAM_CR"
      ],
      "registersUsedMatchingBifield": [
        "SDRAM_CR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_disableSyncRefreshInPowerDown",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SDRAM_CR"
      ],
      "registersUsedMatchingBifield": [
        "SDRAM_CR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_getSyncTotalAccesses",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "TOTAL_SDRAM_AR"
      ],
      "registersUsedMatchingBifield": [
        "TOTAL_SDRAM_AR"
      ]
    },
    {
      "file": "emif.h",
      "peripheral": "emif",
      "functionName": "EMIF_getSyncTotalActivateAccesses",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "TOTAL_SDRAM_ACTR"
      ],
      "registersUsedMatchingBifield": [
        "TOTAL_SDRAM_ACTR"
      ]
    }
  ]
}
module.exports = { 
  emif_driverlib: emif_driverlib,
}
