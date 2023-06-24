let dcc_driverlib = 
{
  "name": "dcc",
  "functions": [
    {
      "file": "dcc.c",
      "peripheral": "dcc",
      "functionName": "DCC_verifyClockFrequency",
      "functionArgs": [
        "base",
        "clock1",
        "freq1",
        "clock0",
        "freq0",
        "tolerance",
        "freqerr",
        "freq_sysclk"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "DCC_Count1ClockSource",
        "float32_t",
        "DCC_Count0ClockSource",
        "float32_t",
        "float32_t",
        "float32_t",
        "float32_t"
      ],
      "returnType": "bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "dcc.c",
      "peripheral": "dcc",
      "functionName": "DCC_measureClockFrequency",
      "functionArgs": [
        "base",
        "clock1",
        "clock0",
        "freq0",
        "tolerance",
        "freqerr",
        "freq_sysclk"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "DCC_Count1ClockSource",
        "DCC_Count0ClockSource",
        "float32_t",
        "float32_t",
        "float32_t",
        "float32_t"
      ],
      "returnType": "float32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "dcc.c",
      "peripheral": "dcc",
      "functionName": "DCC_continuousMonitor",
      "functionArgs": [
        "base",
        "clock1",
        "freq1",
        "clock0",
        "freq0",
        "tolerance",
        "freqerr",
        "freq_sysclk"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "DCC_Count1ClockSource",
        "float32_t",
        "DCC_Count0ClockSource",
        "float32_t",
        "float32_t",
        "float32_t",
        "float32_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_isBaseValid",
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
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_enableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTRL"
      ],
      "registersUsedMatchingBifield": [
        "DCCGCTRL"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_disableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTRL"
      ],
      "registersUsedMatchingBifield": [
        "DCCGCTRL"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_enableErrorSignal",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTRL"
      ],
      "registersUsedMatchingBifield": [
        "DCCGCTRL"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_enableDoneSignal",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTRL"
      ],
      "registersUsedMatchingBifield": [
        "DCCGCTRL"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_disableErrorSignal",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTRL"
      ],
      "registersUsedMatchingBifield": [
        "DCCGCTRL"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_disableDoneSignal",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTRL"
      ],
      "registersUsedMatchingBifield": [
        "DCCGCTRL"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_enableSingleShotMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "DCC_SingleShotMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTRL"
      ],
      "registersUsedMatchingBifield": [
        "DCCGCTRL"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_disableSingleShotMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTRL"
      ],
      "registersUsedMatchingBifield": [
        "DCCGCTRL"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_getErrorStatus",
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
        "DCCSTATUS"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_getSingleShotStatus",
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
        "DCCSTATUS"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_clearErrorFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "STATUS"
      ],
      "registersUsedMatchingBifield": [
        "DCCSTATUS"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_clearDoneFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "STATUS"
      ],
      "registersUsedMatchingBifield": [
        "DCCSTATUS"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_getCounter0Value",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CNT0"
      ],
      "registersUsedMatchingBifield": [
        "DCCCNT0"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_getValidCounter0Value",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "VALID0"
      ],
      "registersUsedMatchingBifield": [
        "DCCVALID0"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_getCounter1Value",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CNT1"
      ],
      "registersUsedMatchingBifield": [
        "DCCCNT1"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_setCounter1ClkSource",
      "functionArgs": [
        "base",
        "source"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "DCC_Count1ClockSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLKSRC1"
      ],
      "registersUsedMatchingBifield": [
        "DCCCLKSRC1"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_setCounter0ClkSource",
      "functionArgs": [
        "base",
        "source"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "DCC_Count0ClockSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLKSRC0"
      ],
      "registersUsedMatchingBifield": [
        "DCCCLKSRC0"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_getCounter1ClkSource",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "CLKSRC1"
      ],
      "registersUsedMatchingBifield": [
        "DCCCLKSRC1"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_getCounter0ClkSource",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "CLKSRC0"
      ],
      "registersUsedMatchingBifield": [
        "DCCCLKSRC0"
      ]
    },
    {
      "file": "dcc.h",
      "peripheral": "dcc",
      "functionName": "DCC_setCounterSeeds",
      "functionArgs": [
        "base",
        "counter0",
        "validCounter0",
        "counter1"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CNTSEED0",
        "VALIDSEED0",
        "CNTSEED1"
      ],
      "registersUsedMatchingBifield": [
        "DCCCNTSEED0",
        "DCCVALIDSEED0",
        "DCCCNTSEED1"
      ]
    }
  ]
}
module.exports = { 
  dcc_driverlib: dcc_driverlib,
}
