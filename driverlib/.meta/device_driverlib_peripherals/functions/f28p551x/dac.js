let dac_driverlib = 
{
  "name": "dac",
  "functions": [
    {
      "file": "dac.c",
      "peripheral": "dac",
      "functionName": "DAC_tuneOffsetTrim",
      "functionArgs": [
        "base",
        "referenceVoltage"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "float32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TRIM"
      ],
      "registersUsedMatchingBifield": [
        "DACTRIM"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_isBaseValid",
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
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_getRevision",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "REV"
      ],
      "registersUsedMatchingBifield": [
        "DACREV"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_setReferenceVoltage",
      "functionArgs": [
        "base",
        "source"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "DAC_ReferenceVoltage"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "DACCTL"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_setGainMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "DAC_GainMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "DACCTL"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_setLoadMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "DAC_LoadMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "DACCTL"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_setPWMSyncSignal",
      "functionArgs": [
        "base",
        "signal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "DACCTL"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_getActiveValue",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "VALA"
      ],
      "registersUsedMatchingBifield": [
        "DACVALA"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_setShadowValue",
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
        "VALS"
      ],
      "registersUsedMatchingBifield": [
        "DACVALS"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_getShadowValue",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "VALS"
      ],
      "registersUsedMatchingBifield": [
        "DACVALS"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_enableOutput",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OUTEN"
      ],
      "registersUsedMatchingBifield": [
        "DACOUTEN"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_disableOutput",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OUTEN"
      ],
      "registersUsedMatchingBifield": [
        "DACOUTEN"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_setOffsetTrim",
      "functionArgs": [
        "base",
        "offset"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "int16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TRIM"
      ],
      "registersUsedMatchingBifield": [
        "DACTRIM"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_getOffsetTrim",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline int16_t",
      "registersUsed": [
        "TRIM"
      ],
      "registersUsedMatchingBifield": [
        "DACTRIM"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_lockRegister",
      "functionArgs": [
        "base",
        "reg"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOCK"
      ],
      "registersUsedMatchingBifield": [
        "DACLOCK"
      ]
    },
    {
      "file": "dac.h",
      "peripheral": "dac",
      "functionName": "DAC_isRegisterLocked",
      "functionArgs": [
        "base",
        "reg"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "LOCK"
      ],
      "registersUsedMatchingBifield": [
        "DACLOCK"
      ]
    }
  ]
}
module.exports = { 
  dac_driverlib: dac_driverlib,
}
