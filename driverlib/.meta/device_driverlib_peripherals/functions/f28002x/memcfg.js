let memcfg_driverlib = 
{
  "name": "memcfg",
  "functions": [
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_lockConfig",
      "functionArgs": [
        "memSections"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "DXLOCK",
        "LSXLOCK",
        "GSXLOCK"
      ],
      "registersUsedMatchingBifield": [
        "DXLOCK",
        "LSXLOCK",
        "GSXLOCK"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_unlockConfig",
      "functionArgs": [
        "memSections"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "DXLOCK",
        "LSXLOCK",
        "GSXLOCK"
      ],
      "registersUsedMatchingBifield": [
        "DXLOCK",
        "LSXLOCK",
        "GSXLOCK"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_commitConfig",
      "functionArgs": [
        "memSections"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "DXCOMMIT",
        "LSXCOMMIT",
        "GSXCOMMIT"
      ],
      "registersUsedMatchingBifield": [
        "DXCOMMIT",
        "LSXCOMMIT",
        "GSXCOMMIT"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_setProtection",
      "functionArgs": [
        "memSection",
        "protectMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "GSXACCPROT0"
      ],
      "registersUsedMatchingBifield": [
        "GSXACCPROT0"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_lockTestConfig",
      "functionArgs": [
        "memSections"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "DXRAMTEST_LOCK",
        "LSXRAMTEST_LOCK",
        "GSXRAMTEST_LOCK",
        "ROM_LOCK"
      ],
      "registersUsedMatchingBifield": [
        "DXRAMTEST_LOCK",
        "LSXRAMTEST_LOCK",
        "GSXRAMTEST_LOCK",
        "ROM_LOCK"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_unlockTestConfig",
      "functionArgs": [
        "memSections"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "DXRAMTEST_LOCK",
        "LSXRAMTEST_LOCK",
        "GSXRAMTEST_LOCK",
        "ROM_LOCK"
      ],
      "registersUsedMatchingBifield": [
        "DXRAMTEST_LOCK",
        "LSXRAMTEST_LOCK",
        "GSXRAMTEST_LOCK",
        "ROM_LOCK"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_setTestMode",
      "functionArgs": [
        "memSection",
        "testMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "MemCfg_TestMode"
      ],
      "returnType": "void",
      "registersUsed": [
        "DXTEST",
        "LSXTEST",
        "GSXTEST",
        "ROM_TEST"
      ],
      "registersUsedMatchingBifield": [
        "DXTEST",
        "LSXTEST",
        "GSXTEST",
        "ROM_TEST"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_initSections",
      "functionArgs": [
        "ramSections"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "DXINIT",
        "LSXINIT",
        "GSXINIT"
      ],
      "registersUsedMatchingBifield": [
        "DXINIT",
        "LSXINIT",
        "GSXINIT"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_getInitStatus",
      "functionArgs": [
        "ramSections"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "bool",
      "registersUsed": [
        "DXINIT",
        "DXINITDONE",
        "LSXINIT",
        "LSXINITDONE",
        "GSXINIT",
        "GSXINITDONE"
      ],
      "registersUsedMatchingBifield": [
        "DXINIT",
        "DXINITDONE",
        "LSXINIT",
        "LSXINITDONE",
        "GSXINIT",
        "GSXINITDONE"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_getViolationAddress",
      "functionArgs": [
        "intFlag"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "NMCPURDAVADDR",
        "NMCPUWRAVADDR",
        "MCPUFAVADDR"
      ],
      "registersUsedMatchingBifield": [
        "NMCPURDAVADDR",
        "NMCPUWRAVADDR",
        "MCPUFAVADDR"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_getCorrErrorAddress",
      "functionArgs": [
        "stsFlag"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "CCPUREADDR"
      ],
      "registersUsedMatchingBifield": [
        "CCPUREADDR"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_getUncorrErrorAddress",
      "functionArgs": [
        "stsFlag"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "UCCPUREADDR",
        "UCDMAREADDR"
      ],
      "registersUsedMatchingBifield": [
        "UCCPUREADDR",
        "UCDMAREADDR"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_forceMemError",
      "functionArgs": [
        "memSections"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "ROM_FORCE_ERROR"
      ],
      "registersUsedMatchingBifield": [
        "ROM_FORCE_ERROR"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_enableViolationInterrupt",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "NMAVINTEN",
        "MAVINTEN"
      ],
      "registersUsedMatchingBifield": [
        "NMAVINTEN",
        "MAVINTEN"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_disableViolationInterrupt",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "NMAVINTEN",
        "MAVINTEN"
      ],
      "registersUsedMatchingBifield": [
        "NMAVINTEN",
        "MAVINTEN"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_getViolationInterruptStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "NMAVFLG",
        "MAVFLG"
      ],
      "registersUsedMatchingBifield": [
        "NMAVFLG",
        "MAVFLG"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_forceViolationInterrupt",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "NMAVSET",
        "MAVSET"
      ],
      "registersUsedMatchingBifield": [
        "NMAVSET",
        "MAVSET"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_clearViolationInterruptStatus",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "NMAVCLR",
        "MAVCLR"
      ],
      "registersUsedMatchingBifield": [
        "NMAVCLR",
        "MAVCLR"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_setCorrErrorThreshold",
      "functionArgs": [
        "threshold"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CERRTHRES"
      ],
      "registersUsedMatchingBifield": [
        "CERRTHRES"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_getCorrErrorCount",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CERRCNT"
      ],
      "registersUsedMatchingBifield": [
        "CERRCNT"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_enableCorrErrorInterrupt",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CEINTEN"
      ],
      "registersUsedMatchingBifield": [
        "CEINTEN"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_disableCorrErrorInterrupt",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CEINTEN"
      ],
      "registersUsedMatchingBifield": [
        "CEINTEN"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_getCorrErrorInterruptStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CEINTFLG"
      ],
      "registersUsedMatchingBifield": [
        "CEINTFLG"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_forceCorrErrorInterrupt",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CEINTSET"
      ],
      "registersUsedMatchingBifield": [
        "CEINTSET"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_clearCorrErrorInterruptStatus",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CEINTCLR"
      ],
      "registersUsedMatchingBifield": [
        "CEINTCLR"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_getCorrErrorStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CERRFLG"
      ],
      "registersUsedMatchingBifield": [
        "CERRFLG"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_getUncorrErrorStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "UCERRFLG"
      ],
      "registersUsedMatchingBifield": [
        "UCERRFLG"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_forceCorrErrorStatus",
      "functionArgs": [
        "stsFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CERRSET"
      ],
      "registersUsedMatchingBifield": [
        "CERRSET"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_forceUncorrErrorStatus",
      "functionArgs": [
        "stsFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "UCERRSET"
      ],
      "registersUsedMatchingBifield": [
        "UCERRSET"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_clearCorrErrorStatus",
      "functionArgs": [
        "stsFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CERRCLR"
      ],
      "registersUsedMatchingBifield": [
        "CERRCLR"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_clearUncorrErrorStatus",
      "functionArgs": [
        "stsFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "UCERRCLR"
      ],
      "registersUsedMatchingBifield": [
        "UCERRCLR"
      ]
    }
  ]
}
module.exports = { 
  memcfg_driverlib: memcfg_driverlib,
}
