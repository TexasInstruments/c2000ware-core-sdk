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
        "DXACCPROT0",
        "LSXACCPROT0",
        "GSXACCPROT0",
        "GSXACCPROT1",
        "GSXACCPROT2",
        "GSXACCPROT3"
      ],
      "registersUsedMatchingBifield": [
        "DXACCPROT0",
        "LSXACCPROT0",
        "GSXACCPROT0",
        "GSXACCPROT1",
        "GSXACCPROT2",
        "GSXACCPROT3"
      ]
    },
    {
      "file": "memcfg.c",
      "peripheral": "memcfg",
      "functionName": "MemCfg_setLSRAMMasterSel",
      "functionArgs": [
        "ramSection",
        "masterSel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "MemCfg_LSRAMMasterSel"
      ],
      "returnType": "void",
      "registersUsed": [
        "LSXMSEL"
      ],
      "registersUsedMatchingBifield": [
        "LSXMSEL"
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
        "MSGXTEST"
      ],
      "registersUsedMatchingBifield": [
        "DXTEST",
        "LSXTEST",
        "GSXTEST",
        "MSGXTEST"
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
        "GSXINIT",
        "MSGXINIT"
      ],
      "registersUsedMatchingBifield": [
        "DXINIT",
        "LSXINIT",
        "GSXINIT",
        "MSGXINIT"
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
        "GSXINITDONE",
        "MSGXINIT",
        "MSGXINITDONE"
      ],
      "registersUsedMatchingBifield": [
        "DXINIT",
        "DXINITDONE",
        "LSXINIT",
        "LSXINITDONE",
        "GSXINIT",
        "GSXINITDONE",
        "MSGXINIT",
        "MSGXINITDONE"
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
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_setCLAMemType",
      "functionArgs": [
        "ramSections",
        "claMemType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "MemCfg_CLAMemoryType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LSXCLAPGM"
      ],
      "registersUsedMatchingBifield": [
        "LSXCLAPGM"
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
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_enableROMWaitState",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ROMWAITSTATE"
      ],
      "registersUsedMatchingBifield": [
        "ROMWAITSTATE"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_disableROMWaitState",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ROMWAITSTATE"
      ],
      "registersUsedMatchingBifield": [
        "ROMWAITSTATE"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_enableROMPrefetch",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ROMPREFETCH"
      ],
      "registersUsedMatchingBifield": [
        "ROMPREFETCH"
      ]
    },
    {
      "file": "memcfg.h",
      "peripheral": "memcfg",
      "functionName": "MemCfg_disableROMPrefetch",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ROMPREFETCH"
      ],
      "registersUsedMatchingBifield": [
        "ROMPREFETCH"
      ]
    }
  ]
}
module.exports = { 
  memcfg_driverlib: memcfg_driverlib,
}
