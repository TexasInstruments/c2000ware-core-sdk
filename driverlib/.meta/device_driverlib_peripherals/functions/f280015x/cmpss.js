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
        "uint32_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTRIPHFILCTL",
        "CTRIPHFILCLKCTL",
        "CTRIPHFILCLKCTL2"
      ],
      "registersUsedMatchingBifield": [
        "CTRIPHFILCTL",
        "CTRIPHFILCLKCTL",
        "CTRIPHFILCLKCTL2"
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
        "uint32_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTRIPLFILCTL",
        "CTRIPLFILCLKCTL",
        "CTRIPLFILCLKCTL2"
      ],
      "registersUsedMatchingBifield": [
        "CTRIPLFILCTL",
        "CTRIPLFILCLKCTL",
        "CTRIPLFILCLKCTL2"
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
        "COMPDACHCTL",
        "RAMPHREFS",
        "RAMPHSTEPVALS",
        "RAMPHDLYS"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL",
        "RAMPHREFS",
        "RAMPHSTEPVALS",
        "RAMPHDLYS"
      ]
    },
    {
      "file": "cmpss.c",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configRampHigh",
      "functionArgs": [
        "base",
        "rampDir",
        "rampRef",
        "stepVal",
        "delayVal",
        "pwmSyncSrc",
        "useRampValShdw"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CMPSS_RampDirection",
        "uint16_t",
        "uint16_t",
        "uint16_t",
        "uint16_t",
        "bool"
      ],
      "returnType": "void",
      "registersUsed": [
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
      ]
    },
    {
      "file": "cmpss.c",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configRampLow",
      "functionArgs": [
        "base",
        "rampDir",
        "rampRef",
        "stepVal",
        "delayVal",
        "pwmSyncSrc",
        "useRampValShdw"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CMPSS_RampDirection",
        "uint16_t",
        "uint16_t",
        "uint16_t",
        "uint16_t",
        "bool"
      ],
      "returnType": "void",
      "registersUsed": [
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
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
      "functionName": "CMPSS_isLiteBaseValid",
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
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configDACHigh",
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
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configDACLow",
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
        "COMPDACLCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACLCTL"
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
      "functionName": "CMPSS_configureFilterInputHigh",
      "functionArgs": [
        "base",
        "filtInput"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CMPSS_FilterInput"
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
      "functionName": "CMPSS_configureFilterInputLow",
      "functionArgs": [
        "base",
        "filtInput"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CMPSS_FilterInput"
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
        "RAMPHREFS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHREFS"
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
        "RAMPHREFA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHREFA"
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
        "RAMPHSTEPVALS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHSTEPVALS"
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
        "RAMPHSTEPVALA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHSTEPVALA"
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
        "RAMPHDLYS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHDLYS"
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
        "RAMPHDLYA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHDLYA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setRampDirectionHigh",
      "functionArgs": [
        "base",
        "dir"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CMPSS_RampDirection"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setRampReferenceHigh",
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
        "RAMPHREFS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHREFS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getRampReferenceHigh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RAMPHREFA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHREFA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setRampStepHigh",
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
        "RAMPHSTEPVALS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHSTEPVALS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getRampStepHigh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RAMPHSTEPVALA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHSTEPVALA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setRampDelayHigh",
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
        "RAMPHDLYS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHDLYS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getRampDelayHigh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RAMPHDLYA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPHDLYA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setRampDirectionLow",
      "functionArgs": [
        "base",
        "dir"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CMPSS_RampDirection"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACLCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACLCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setRampReferenceLow",
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
        "RAMPLREFS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPLREFS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getRampReferenceLow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RAMPLREFA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPLREFA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setRampStepLow",
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
        "RAMPLSTEPVALS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPLSTEPVALS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getRampStepLow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RAMPLSTEPVALA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPLSTEPVALA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_setRampDelayLow",
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
        "RAMPLDLYS"
      ],
      "registersUsedMatchingBifield": [
        "RAMPLDLYS"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_getRampDelayLow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RAMPLDLYA"
      ],
      "registersUsedMatchingBifield": [
        "RAMPLDLYA"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configureRampXTriggerHigh",
      "functionArgs": [
        "base",
        "trigger"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CMPSS_RampXTrigger"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACHCTL",
        "COMPDACHCTL2"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL",
        "COMPDACHCTL2"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configureSyncSourceHigh",
      "functionArgs": [
        "base",
        "syncSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configureSyncSourceLow",
      "functionArgs": [
        "base",
        "syncSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACLCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACLCTL"
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
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
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
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
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
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configBlankingSourceHigh",
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
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_enableBlankingHigh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_disableBlankingHigh",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_configBlankingSourceLow",
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
        "COMPDACLCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACLCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_enableBlankingLow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACLCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACLCTL"
      ]
    },
    {
      "file": "cmpss.h",
      "peripheral": "cmpss",
      "functionName": "CMPSS_disableBlankingLow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMPDACLCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACLCTL"
      ]
    }
  ]
}
module.exports = { 
  cmpss_driverlib: cmpss_driverlib,
}
