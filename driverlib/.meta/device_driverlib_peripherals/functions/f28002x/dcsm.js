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
        "B0_Z1_LINKPOINTER",
        "Z1_CSMKEY0",
        "Z1_CSMKEY1",
        "Z1_CSMKEY2",
        "Z1_CSMKEY3"
      ],
      "registersUsedMatchingBifield": [
        "B0_Z1_LINKPOINTER",
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
        "B0_Z2_LINKPOINTER",
        "Z2_CSMKEY0",
        "Z2_CSMKEY1",
        "Z2_CSMKEY2",
        "Z2_CSMKEY3"
      ],
      "registersUsedMatchingBifield": [
        "B0_Z2_LINKPOINTER",
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
        "sector"
      ],
      "functionArgsTypes": [
        "DCSM_Sector"
      ],
      "returnType": "DCSM_EXEOnlyStatus",
      "registersUsed": [
        "B0_Z1_EXEONLYSECTR"
      ],
      "registersUsedMatchingBifield": [
        "B0_Z1_EXEONLYSECTR"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone1RAMEXEStatus",
      "functionArgs": [
        "module"
      ],
      "functionArgsTypes": [
        "DCSM_RAMModule"
      ],
      "returnType": "DCSM_EXEOnlyStatus",
      "registersUsed": [
        "Z1_EXEONLYRAMR"
      ],
      "registersUsedMatchingBifield": [
        "Z1_EXEONLYRAMR"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone2FlashEXEStatus",
      "functionArgs": [
        "sector"
      ],
      "functionArgsTypes": [
        "DCSM_Sector"
      ],
      "returnType": "DCSM_EXEOnlyStatus",
      "registersUsed": [
        "B0_Z2_EXEONLYSECTR"
      ],
      "registersUsedMatchingBifield": [
        "B0_Z2_EXEONLYSECTR"
      ]
    },
    {
      "file": "dcsm.c",
      "peripheral": "dcsm",
      "functionName": "DCSM_getZone2RAMEXEStatus",
      "functionArgs": [
        "module"
      ],
      "functionArgsTypes": [
        "DCSM_RAMModule"
      ],
      "returnType": "DCSM_EXEOnlyStatus",
      "registersUsed": [
        "Z2_EXEONLYRAMR"
      ],
      "registersUsedMatchingBifield": [
        "Z2_EXEONLYRAMR"
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
        "module"
      ],
      "functionArgsTypes": [
        "DCSM_RAMModule"
      ],
      "returnType": "static inline DCSM_MemoryStatus",
      "registersUsed": [
        "RAMSTAT"
      ],
      "registersUsedMatchingBifield": [
        "RAMSTAT"
      ]
    },
    {
      "file": "dcsm.h",
      "peripheral": "dcsm",
      "functionName": "DCSM_getFlashSectorZone",
      "functionArgs": [
        "sector"
      ],
      "functionArgsTypes": [
        "DCSM_Sector"
      ],
      "returnType": "static inline DCSM_MemoryStatus",
      "registersUsed": [
        "B0_SECTSTAT"
      ],
      "registersUsedMatchingBifield": [
        "B0_SECTSTAT"
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
        "B0_Z1_LINKPOINTER",
        "B0_Z1_LINKPOINTERERR"
      ],
      "registersUsedMatchingBifield": [
        "B0_Z1_LINKPOINTER",
        "B0_Z1_LINKPOINTERERR"
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
        "B0_Z2_LINKPOINTER",
        "B0_Z2_LINKPOINTERERR"
      ],
      "registersUsedMatchingBifield": [
        "B0_Z2_LINKPOINTER",
        "B0_Z2_LINKPOINTERERR"
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
    }
  ]
}
module.exports = { 
  dcsm_driverlib: dcsm_driverlib,
}
