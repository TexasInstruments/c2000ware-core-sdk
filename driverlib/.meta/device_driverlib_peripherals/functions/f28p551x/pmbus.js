let pmbus_driverlib = 
{
  "name": "pmbus",
  "functions": [
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_getInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "PMBSTS"
      ],
      "registersUsedMatchingBifield": [
        "PMBSTS"
      ]
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_initSlaveMode",
      "functionArgs": [
        "base",
        "address",
        "mask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "PMBINTM",
        "PMBSC",
        "PMBCTRL"
      ],
      "registersUsedMatchingBifield": [
        "PMBINTM",
        "PMBSC",
        "PMBCTRL"
      ]
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_configSlave",
      "functionArgs": [
        "base",
        "configWord"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "PMBINTM",
        "PMBSC"
      ],
      "registersUsedMatchingBifield": [
        "PMBINTM",
        "PMBSC"
      ]
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_putSlaveData",
      "functionArgs": [
        "base",
        "*buffer",
        "nBytes",
        "txPEC"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t",
        "bool"
      ],
      "returnType": "void",
      "registersUsed": [
        "PMBTXBUF",
        "PMBSC"
      ],
      "registersUsedMatchingBifield": [
        "PMBTXBUF",
        "PMBSC"
      ]
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_ackAddress",
      "functionArgs": [
        "base",
        "address",
        "status",
        "*buffer"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "PMBACK",
        "PMBSC"
      ],
      "registersUsedMatchingBifield": [
        "PMBACK",
        "PMBSC"
      ]
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_ackCommand",
      "functionArgs": [
        "base",
        "command",
        "status",
        "*buffer"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "PMBACK",
        "PMBSC"
      ],
      "registersUsedMatchingBifield": [
        "PMBACK",
        "PMBSC"
      ]
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_initMasterMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "PMBINTM",
        "PMBCTRL"
      ],
      "registersUsedMatchingBifield": [
        "PMBINTM",
        "PMBCTRL"
      ]
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_generateCRCTable",
      "functionArgs": [
        "*crcTable"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_verifyPEC",
      "functionArgs": [
        "base",
        "*buffer",
        "*crcTable",
        "byteCount",
        "pec"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "constuint16_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "bool",
      "registersUsed": [
        "PMBHSA"
      ],
      "registersUsedMatchingBifield": [
        "PMBHSA"
      ]
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_getData",
      "functionArgs": [
        "base",
        "*buffer",
        "status"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint32_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "PMBRXBUF"
      ],
      "registersUsedMatchingBifield": [
        "PMBRXBUF"
      ]
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_putMasterData",
      "functionArgs": [
        "base",
        "*buffer",
        "nBytes"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "PMBTXBUF"
      ],
      "registersUsedMatchingBifield": [
        "PMBTXBUF"
      ]
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_configModuleClock",
      "functionArgs": [
        "base",
        "moduleFrequency",
        "sysFrequency"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "PMBINTM",
        "PMBCTRL"
      ],
      "registersUsedMatchingBifield": [
        "PMBINTM",
        "PMBCTRL"
      ]
    },
    {
      "file": "pmbus.c",
      "peripheral": "pmbus",
      "functionName": "PMBus_configBusClock",
      "functionArgs": [
        "base",
        "mode",
        "moduleFrequency"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "PMBus_ClockMode",
        "uint32_t"
      ],
      "returnType": "bool",
      "registersUsed": [
        "PMBINTM",
        "PMBCTRL",
        "PMBTIMCTL",
        "PMBTIMCLK",
        "PMBTIMSTSETUP",
        "PMBTIMBIDLE",
        "PMBTIMLOWTIMOUT",
        "PMBTIMHIGHTIMOUT"
      ],
      "registersUsedMatchingBifield": [
        "PMBINTM",
        "PMBCTRL",
        "PMBTIMCTL",
        "PMBTIMCLK",
        "PMBTIMSTSETUP",
        "PMBTIMBIDLE",
        "PMBTIMLOWTIMOUT",
        "PMBTIMHIGHTIMOUT"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_isBaseValid",
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
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_disableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBCTRL"
      ],
      "registersUsedMatchingBifield": [
        "PMBCTRL"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_enableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBCTRL"
      ],
      "registersUsedMatchingBifield": [
        "PMBCTRL"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_enableInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBINTM"
      ],
      "registersUsedMatchingBifield": [
        "PMBINTM"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_disableInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBINTM"
      ],
      "registersUsedMatchingBifield": [
        "PMBINTM"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_isBusBusy",
      "functionArgs": [
        "status"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_isPECValid",
      "functionArgs": [
        "status"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_enableI2CMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBINTM",
        "PMBCTRL"
      ],
      "registersUsedMatchingBifield": [
        "PMBINTM",
        "PMBCTRL"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_disableI2CMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBINTM",
        "PMBCTRL"
      ],
      "registersUsedMatchingBifield": [
        "PMBINTM",
        "PMBCTRL"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_getStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "PMBSTS"
      ],
      "registersUsedMatchingBifield": [
        "PMBSTS"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_ackTransaction",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBACK"
      ],
      "registersUsedMatchingBifield": [
        "PMBACK"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_nackTransaction",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBACK"
      ],
      "registersUsedMatchingBifield": [
        "PMBACK"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_assertAlertLine",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBCTRL"
      ],
      "registersUsedMatchingBifield": [
        "PMBCTRL"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_deassertAlertLine",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBCTRL"
      ],
      "registersUsedMatchingBifield": [
        "PMBCTRL"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_configMaster",
      "functionArgs": [
        "base",
        "slaveAddress",
        "byteCount",
        "configWord"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBMC"
      ],
      "registersUsedMatchingBifield": [
        "PMBMC"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_getOwnAddress",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "PMBHSA"
      ],
      "registersUsedMatchingBifield": [
        "PMBHSA"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_setOwnAddress",
      "functionArgs": [
        "base",
        "Ownaddress"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBSC"
      ],
      "registersUsedMatchingBifield": [
        "PMBSC"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_setSlaveAddress",
      "functionArgs": [
        "base",
        "slaveAddress"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBMC"
      ],
      "registersUsedMatchingBifield": [
        "PMBMC"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_getCurrentAccessType",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline PMBus_accessType",
      "registersUsed": [
        "PMBHSA"
      ],
      "registersUsedMatchingBifield": [
        "PMBHSA"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_setCtrlIntEdge",
      "functionArgs": [
        "base",
        "intEdge"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "PMBus_intEdge"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PMBCTRL"
      ],
      "registersUsedMatchingBifield": [
        "PMBCTRL"
      ]
    },
    {
      "file": "pmbus.h",
      "peripheral": "pmbus",
      "functionName": "PMBus_setClkLowTimeoutIntEdge",
      "functionArgs": [
        "base",
        "intEdge"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "PMBus_intEdge"
      ],
      "returnType": "static inline  void",
      "registersUsed": [
        "PMBCTRL"
      ],
      "registersUsedMatchingBifield": [
        "PMBCTRL"
      ]
    }
  ]
}
module.exports = { 
  pmbus_driverlib: pmbus_driverlib,
}
