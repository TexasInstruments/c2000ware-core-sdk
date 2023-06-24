let lcm_driverlib = 
{
  "name": "lcm",
  "functions": [
    {
      "file": "lcm.c",
      "peripheral": "lcm",
      "functionName": "LCM_runSelfTest",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "LCM_Status",
      "registersUsed": [
        "CONTROL",
        "STATUS",
        "STATUS_CLEAR"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL",
        "STATUS",
        "STATUS_CLEAR"
      ]
    },
    {
      "file": "lcm.c",
      "peripheral": "lcm",
      "functionName": "LCM_runComp1ErrorForceTest",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "LCM_Status",
      "registersUsed": [
        "CONTROL",
        "STATUS",
        "STATUS_CLEAR"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL",
        "STATUS",
        "STATUS_CLEAR"
      ]
    },
    {
      "file": "lcm.c",
      "peripheral": "lcm",
      "functionName": "LCM_runComp2ErrorForceTest",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "LCM_Status",
      "registersUsed": [
        "CONTROL",
        "STATUS",
        "STATUS_CLEAR"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL",
        "STATUS",
        "STATUS_CLEAR"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_isBaseValid",
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
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_enableLockstepCompare",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_disableLockstepCompare",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_isLockStepEnabled",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "STATUS"
      ],
      "registersUsedMatchingBifield": [
        "STATUS"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_isDebuggerConnected",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "STATUS"
      ],
      "registersUsedMatchingBifield": [
        "STATUS"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_getLockStepCompareStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline LCM_Status",
      "registersUsed": [
        "STATUS"
      ],
      "registersUsedMatchingBifield": [
        "STATUS"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_getSelfTestStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline LCM_Status",
      "registersUsed": [
        "STATUS"
      ],
      "registersUsedMatchingBifield": [
        "STATUS"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_getComp1ErrForceTestStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline LCM_Status",
      "registersUsed": [
        "STATUS"
      ],
      "registersUsedMatchingBifield": [
        "STATUS"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_getComp2ErrForceTestStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline LCM_Status",
      "registersUsed": [
        "STATUS"
      ],
      "registersUsedMatchingBifield": [
        "STATUS"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_clearFlags",
      "functionArgs": [
        "base",
        "flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline LCM_Status",
      "registersUsed": [
        "STATUS",
        "STATUS_CLEAR"
      ],
      "registersUsedMatchingBifield": [
        "STATUS",
        "STATUS_CLEAR"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_enableParityTest",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PARITY_TEST"
      ],
      "registersUsedMatchingBifield": [
        "PARITY_TEST"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_disableParityTest",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PARITY_TEST"
      ],
      "registersUsedMatchingBifield": [
        "PARITY_TEST"
      ]
    },
    {
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_lockRegister",
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
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_unlockRegister",
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
      "file": "lcm.h",
      "peripheral": "lcm",
      "functionName": "LCM_commitRegister",
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
  lcm_driverlib: lcm_driverlib,
}
