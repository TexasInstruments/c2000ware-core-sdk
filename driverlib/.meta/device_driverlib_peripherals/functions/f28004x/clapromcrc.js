let clapromcrc_driverlib = 
{
  "name": "clapromcrc",
  "functions": [
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_isBaseValid",
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
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_setEmulationMode",
      "functionArgs": [
        "base",
        "emulationMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLAPROMCRC_EmulationMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CRC32_CONTROLREG"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_CONTROLREG"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_start",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CRC32_CONTROLREG"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_CONTROLREG"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_halt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CRC32_CONTROLREG"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_CONTROLREG"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_resume",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CRC32_CONTROLREG"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_CONTROLREG"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_setBlockSize",
      "functionArgs": [
        "base",
        "blockSize"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CRC32_CONTROLREG"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_CONTROLREG"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_setStartAddress",
      "functionArgs": [
        "base",
        "startAddress"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CRC32_STARTADDRESS"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_STARTADDRESS"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_setSeed",
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
        "CRC32_SEED"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_SEED"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_getCurrentAddress",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "CRC32_STATUSREG"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_STATUSREG"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_checkStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CRC32_STATUSREG"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_STATUSREG"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_getRunStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CRC32_STATUSREG"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_STATUSREG"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_getResult",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CRC32_CRCRESULT"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_CRCRESULT"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_setGoldenCRC",
      "functionArgs": [
        "base",
        "goldenCRC"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CRC32_GOLDENCRC"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_GOLDENCRC"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_disableDoneInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CRC32_INTEN"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_INTEN"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_enableDoneInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CRC32_INTEN"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_INTEN"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_getInterruptStatus",
      "functionArgs": [
        "base",
        "intFlag"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLAPROMCRC_IntFlag"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CRC32_FLG"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_FLG"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_clearInterruptFlag",
      "functionArgs": [
        "base",
        "intFlag"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLAPROMCRC_IntFlag"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CRC32_CLR"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_CLR"
      ]
    },
    {
      "file": "clapromcrc.h",
      "peripheral": "clapromcrc",
      "functionName": "CLAPROMCRC_forceDoneFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CRC32_FRC"
      ],
      "registersUsedMatchingBifield": [
        "CRC32_FRC"
      ]
    }
  ]
}
module.exports = { 
  clapromcrc_driverlib: clapromcrc_driverlib,
}
