let cmpss_driverlib = 
{
  "name": "cmpss",
  "functions": [
    {
      "file": "cmpss.c",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configFilterHigh",
      "functionArgs": [
        "base",
        "samplePrescale",
        "sampleWindow",
        "threshold"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTRIPHFILCTL",
        "CTRIPHFILCLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "CTRIPHFILCTL",
        "CTRIPHFILCLKCTL"
      ]
    },
    {
      "file": "cmpss.c",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configFilterLow",
      "functionArgs": [
        "base",
        "samplePrescale",
        "sampleWindow",
        "threshold"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTRIPLFILCTL",
        "CTRIPLFILCLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "CTRIPLFILCTL",
        "CTRIPLFILCLKCTL"
      ]
    },
    {
      "file": "cmpss.c",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configLatchOnPWMSYNC",
      "functionArgs": [
        "base",
        "highEnable",
        "lowEnable"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool",
        "bool"
      ],
      "returnType": "void",
      "registersUsed": [
        "COMPSTS",
        "COMPSTSCLR"
      ],
      "registersUsedMatchingBifield": [
        "COMPSTS",
        "COMPSTSCLR"
      ]
    },
    {
      "file": "cmpss.c",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configRamp",
      "functionArgs": [
        "base",
        "maxRampVal",
        "decrementVal",
        "delayVal",
        "pwmSyncSrc",
        "useRampValShdw"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t",
        "uint16_t",
        "uint16_t",
        "bool"
      ],
      "returnType": "void",
      "registersUsed": [
        "COMPDACCTL",
        "RAMPMAXREFS",
        "RAMPDECVALS",
        "RAMPDLYS"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACCTL",
        "RAMPMAXREFS",
        "RAMPDECVALS",
        "RAMPDLYS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_isBaseValid",
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
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_enableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_disableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configHighComparator",
      "functionArgs": [
        "base",
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configLowComparator",
      "functionArgs": [
        "base",
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configOutputsHigh",
      "functionArgs": [
        "base",
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configOutputsLow",
      "functionArgs": [
        "base",
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "COMPSTS"
      ],
      "registersUsedMatchingBifield": [
        "COMPSTS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configDAC",
      "functionArgs": [
        "base",
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setDACValueHigh",
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
        "DACHVALS"
      ],
      "registersUsedMatchingBifield": [
        "DACHVALS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setDACValueLow",
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
        "DACLVALS"
      ],
      "registersUsedMatchingBifield": [
        "DACLVALS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_initFilterHigh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTRIPHFILCTL"
      ],
      "registersUsedMatchingBifield": [
        "CTRIPHFILCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_initFilterLow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTRIPLFILCTL"
      ],
      "registersUsedMatchingBifield": [
        "CTRIPLFILCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getDACValueHigh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "DACHVALA"
      ],
      "registersUsedMatchingBifield": [
        "DACHVALA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getDACValueLow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "DACLVALA"
      ],
      "registersUsedMatchingBifield": [
        "DACLVALA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_clearFilterLatchHigh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPSTS",
        "COMPSTSCLR"
      ],
      "registersUsedMatchingBifield": [
        "COMPSTS",
        "COMPSTSCLR"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_clearFilterLatchLow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPSTS",
        "COMPSTSCLR"
      ],
      "registersUsedMatchingBifield": [
        "COMPSTS",
        "COMPSTSCLR"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setMaxRampValue",
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
        "RAMPMAXREFS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPMAXREFS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getMaxRampValue",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RAMPMAXREFA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPMAXREFA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setRampDecValue",
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
        "RAMPDECVALS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPDECVALS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getRampDecValue",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RAMPDECVALA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPDECVALA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setRampDelayValue",
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
        "RAMPDLYS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPDLYS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getRampDelayValue",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RAMPDLYA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPDLYA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setHysteresis",
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
        "COMPHYSCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPHYSCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_enableLatchResetOnPWMSYNCHigh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPSTS",
        "COMPSTSCLR"
      ],
      "registersUsedMatchingBifield": [
        "COMPSTS",
        "COMPSTSCLR"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_disableLatchResetOnPWMSYNCHigh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPSTS",
        "COMPSTSCLR"
      ],
      "registersUsedMatchingBifield": [
        "COMPSTS",
        "COMPSTSCLR"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_enableLatchResetOnPWMSYNCLow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPSTS",
        "COMPSTSCLR"
      ],
      "registersUsedMatchingBifield": [
        "COMPSTS",
        "COMPSTSCLR"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_disableLatchResetOnPWMSYNCLow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPSTS",
        "COMPSTSCLR"
      ],
      "registersUsedMatchingBifield": [
        "COMPSTS",
        "COMPSTSCLR"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configBlanking",
      "functionArgs": [
        "base",
        "pwmBlankSrc"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_enableBlanking",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_disableBlanking",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACCTL"
      ]
    }
  ]
}
module.exports = { 
  cmpss_driverlib: cmpss_driverlib,
}
