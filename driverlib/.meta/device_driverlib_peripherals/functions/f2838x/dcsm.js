let dcsm_driverlib = 
{
  "name": "dcsm",
  "functions": [
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_unlockZone1CSM",
      "functionArgs": [
        "psCMDKey"
      ],
      "functionArgsTypes": [
        "constDCSM_CSMPasswordKey*const"
      ],
      "returnType": "void",
      "registersUsed": [
        "Z1_LINKPOINTER",
        "Z1_CSMKEY0",
        "Z1_CSMKEY1",
        "Z1_CSMKEY2",
        "Z1_CSMKEY3"
      ],
      "registersUsedMatchingBifield": [
        "Z1_LINKPOINTER",
        "Z1_CSMKEY0",
        "Z1_CSMKEY1",
        "Z1_CSMKEY2",
        "Z1_CSMKEY3"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_unlockZone2CSM",
      "functionArgs": [
        "psCMDKey"
      ],
      "functionArgsTypes": [
        "constDCSM_CSMPasswordKey*const"
      ],
      "returnType": "void",
      "registersUsed": [
        "Z2_LINKPOINTER",
        "Z2_CSMKEY0",
        "Z2_CSMKEY1",
        "Z2_CSMKEY2",
        "Z2_CSMKEY3"
      ],
      "registersUsedMatchingBifield": [
        "Z2_LINKPOINTER",
        "Z2_CSMKEY0",
        "Z2_CSMKEY1",
        "Z2_CSMKEY2",
        "Z2_CSMKEY3"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_writeZone1CSM",
      "functionArgs": [
        "psCMDKey"
      ],
      "functionArgsTypes": [
        "constDCSM_CSMPasswordKey*const"
      ],
      "returnType": "void",
      "registersUsed": [
        "Z1_CSMKEY0",
        "Z1_CSMKEY1",
        "Z1_CSMKEY2",
        "Z1_CSMKEY3"
      ],
      "registersUsedMatchingBifield": [
        "Z1_CSMKEY0",
        "Z1_CSMKEY1",
        "Z1_CSMKEY2",
        "Z1_CSMKEY3"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_writeZone2CSM",
      "functionArgs": [
        "psCMDKey"
      ],
      "functionArgsTypes": [
        "constDCSM_CSMPasswordKey*const"
      ],
      "returnType": "void",
      "registersUsed": [
        "Z2_CSMKEY0",
        "Z2_CSMKEY1",
        "Z2_CSMKEY2",
        "Z2_CSMKEY3"
      ],
      "registersUsedMatchingBifield": [
        "Z2_CSMKEY0",
        "Z2_CSMKEY1",
        "Z2_CSMKEY2",
        "Z2_CSMKEY3"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone1FlashEXEStatus",
      "functionArgs": [
        "sector",
        "cpuInst"
      ],
      "functionArgsTypes": [
        "DCSM_Sector",
        "DCSM_CPUSel"
      ],
      "returnType": "DCSM_EXEOnlyStatus",
      "registersUsed": [
        "Z1_EXEONLYSECT1R",
        "Z1_EXEONLYSECT2R"
      ],
      "registersUsedMatchingBifield": [
        "Z1_EXEONLYSECT1R",
        "Z1_EXEONLYSECT2R"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone1RAMEXEStatus",
      "functionArgs": [
        "module",
        "cpuInst"
      ],
      "functionArgsTypes": [
        "DCSM_RAMModule",
        "DCSM_CPUSel"
      ],
      "returnType": "DCSM_EXEOnlyStatus",
      "registersUsed": [
        "Z1_EXEONLYRAM1R"
      ],
      "registersUsedMatchingBifield": [
        "Z1_EXEONLYRAM1R"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone2FlashEXEStatus",
      "functionArgs": [
        "sector",
        "cpuInst"
      ],
      "functionArgsTypes": [
        "DCSM_Sector",
        "DCSM_CPUSel"
      ],
      "returnType": "DCSM_EXEOnlyStatus",
      "registersUsed": [
        "Z2_EXEONLYSECT1R",
        "Z2_EXEONLYSECT2R"
      ],
      "registersUsedMatchingBifield": [
        "Z2_EXEONLYSECT1R",
        "Z2_EXEONLYSECT2R"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone2RAMEXEStatus",
      "functionArgs": [
        "module",
        "cpuInst"
      ],
      "functionArgsTypes": [
        "DCSM_RAMModule",
        "DCSM_CPUSel"
      ],
      "returnType": "DCSM_EXEOnlyStatus",
      "registersUsed": [
        "Z2_EXEONLYRAM1R"
      ],
      "registersUsedMatchingBifield": [
        "Z2_EXEONLYRAM1R"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_claimZoneSemaphore",
      "functionArgs": [
        "zone"
      ],
      "functionArgsTypes": [
        "DCSM_SemaphoreZone"
      ],
      "returnType": "bool",
      "registersUsed": [
        "FLSEM"
      ],
      "registersUsedMatchingBifield": [
        "FLSEM"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_releaseZoneSemaphore",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "bool",
      "registersUsed": [
        "FLSEM"
      ],
      "registersUsedMatchingBifield": [
        "FLSEM"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_readZone1CSMPwd",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "void",
      "registersUsed": [
        "Z1_LINKPOINTER"
      ],
      "registersUsedMatchingBifield": [
        "Z1_LINKPOINTER"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_readZone2CSMPwd",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "void",
      "registersUsed": [
        "Z2_LINKPOINTER"
      ],
      "registersUsedMatchingBifield": [
        "Z2_LINKPOINTER"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_secureZone1",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "Z1_CR"
      ],
      "registersUsedMatchingBifield": [
        "Z1_CR"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_secureZone2",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "Z2_CR"
      ],
      "registersUsedMatchingBifield": [
        "Z2_CR"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone1CSMSecurityStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline DCSM_SecurityStatus",
      "registersUsed": [
        "Z1_CR"
      ],
      "registersUsedMatchingBifield": [
        "Z1_CR"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone2CSMSecurityStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline DCSM_SecurityStatus",
      "registersUsed": [
        "Z2_CR"
      ],
      "registersUsedMatchingBifield": [
        "Z2_CR"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone1ControlStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "Z1_CR"
      ],
      "registersUsedMatchingBifield": [
        "Z1_CR"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone2ControlStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "Z2_CR"
      ],
      "registersUsedMatchingBifield": [
        "Z2_CR"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getRAMZone",
      "functionArgs": [
        "module",
        "cpuInst"
      ],
      "functionArgsTypes": [
        "DCSM_RAMModule",
        "DCSM_CPUSel"
      ],
      "returnType": "static inline DCSM_MemoryStatus",
      "registersUsed": [
        "RAMSTAT1"
      ],
      "registersUsedMatchingBifield": [
        "RAMSTAT1"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getFlashSectorZone",
      "functionArgs": [
        "sector",
        "cpuInst"
      ],
      "functionArgsTypes": [
        "DCSM_Sector",
        "DCSM_CPUSel"
      ],
      "returnType": "static inline DCSM_MemoryStatus",
      "registersUsed": [
        "SECTSTAT1"
      ],
      "registersUsedMatchingBifield": [
        "SECTSTAT1"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone1LinkPointerError",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "Z1_LINKPOINTER",
        "Z1_LINKPOINTERERR"
      ],
      "registersUsedMatchingBifield": [
        "Z1_LINKPOINTER",
        "Z1_LINKPOINTERERR"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone2LinkPointerError",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "Z2_LINKPOINTER",
        "Z2_LINKPOINTERERR"
      ],
      "registersUsedMatchingBifield": [
        "Z2_LINKPOINTER",
        "Z2_LINKPOINTERERR"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getFlashErrorStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SECERRSTAT"
      ],
      "registersUsedMatchingBifield": [
        "SECERRSTAT"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_clearFlashErrorStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SECERRCLR"
      ],
      "registersUsedMatchingBifield": [
        "SECERRCLR"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_forceFlashErrorStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SECERRFRC"
      ],
      "registersUsedMatchingBifield": [
        "SECERRFRC"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone1OTPSecureLockStatus",
      "functionArgs": [
        "lockType"
      ],
      "functionArgsTypes": [
        "DCSM_OTPLock"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "Z1_OTPSECLOCK"
      ],
      "registersUsedMatchingBifield": [
        "Z1_OTPSECLOCK"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone2OTPSecureLockStatus",
      "functionArgs": [
        "lockType"
      ],
      "functionArgsTypes": [
        "DCSM_OTPLock"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "Z2_OTPSECLOCK"
      ],
      "registersUsedMatchingBifield": [
        "Z2_OTPSECLOCK"
      ]
    }
  ]
}
module.exports = { 
  dcsm_driverlib: dcsm_driverlib,
}
