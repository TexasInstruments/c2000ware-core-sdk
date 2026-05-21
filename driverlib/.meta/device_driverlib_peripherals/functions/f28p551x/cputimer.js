let cputimer_driverlib = 
{
  "name": "cputimer",
  "functions": [
    {
      "file": "cputimer.c",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_setEmulationMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CPUTimer_EmulationMode"
      ],
      "returnType": "void",
      "registersUsed": [
        "TCR"
      ],
      "registersUsedMatchingBifield": [
        "TCR"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_isBaseValid",
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
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_clearOverflowFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TCR"
      ],
      "registersUsedMatchingBifield": [
        "TCR"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_disableInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TCR"
      ],
      "registersUsedMatchingBifield": [
        "TCR"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_enableInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TCR"
      ],
      "registersUsedMatchingBifield": [
        "TCR"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_reloadTimerCounter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TCR"
      ],
      "registersUsedMatchingBifield": [
        "TCR"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_stopTimer",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TCR"
      ],
      "registersUsedMatchingBifield": [
        "TCR"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_resumeTimer",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TCR"
      ],
      "registersUsedMatchingBifield": [
        "TCR"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_startTimer",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TCR"
      ],
      "registersUsedMatchingBifield": [
        "TCR"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_setPeriod",
      "functionArgs": [
        "base",
        "periodCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PRD"
      ],
      "registersUsedMatchingBifield": [
        "PRD"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_getTimerCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "TIM"
      ],
      "registersUsedMatchingBifield": [
        "TIM"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_setPreScaler",
      "functionArgs": [
        "base",
        "prescaler"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TPR",
        "TPRH"
      ],
      "registersUsedMatchingBifield": [
        "TPR",
        "TPRH"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_getTimerOverflowStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "TCR"
      ],
      "registersUsedMatchingBifield": [
        "TCR"
      ]
    },
    {
      "file": "cputimer.h",
      "peripheral": "cputimer",
      "functionName": "CPUTimer_selectClockSource",
      "functionArgs": [
        "base",
        "source",
        "prescaler"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CPUTimer_ClockSource",
        "CPUTimer_Prescaler"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TMR2CLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "TMR2CLKCTL"
      ]
    }
  ]
}
module.exports = { 
  cputimer_driverlib: cputimer_driverlib,
}
