let lin_driverlib = 
{
  "name": "lin",
  "functions": [
    {
      "file": "lin.c",
      "peripheral": "lin",
      "functionName": "LIN_initModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "lin.c",
      "peripheral": "lin",
      "functionName": "LIN_sendData",
      "functionArgs": [
        "base",
        "*data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "SCIFORMAT",
        "TD0"
      ],
      "registersUsedMatchingBifield": [
        "SCIFORMAT",
        "TD0"
      ]
    },
    {
      "file": "lin.c",
      "peripheral": "lin",
      "functionName": "LIN_getData",
      "functionArgs": [
        "base",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t*const"
      ],
      "returnType": "void",
      "registersUsed": [
        "SCIFORMAT",
        "RD0"
      ],
      "registersUsedMatchingBifield": [
        "SCIFORMAT",
        "RD0"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_isBaseValid",
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
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setLINMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_LINMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setMaximumBaudRate",
      "functionArgs": [
        "base",
        "clock"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MBRSR"
      ],
      "registersUsedMatchingBifield": [
        "MBRSR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setMessageFiltering",
      "functionArgs": [
        "base",
        "type"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_MessageFilter"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableParity",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableParity",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_generateParityID",
      "functionArgs": [
        "identifier"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setIDByte",
      "functionArgs": [
        "base",
        "identifier"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ID"
      ],
      "registersUsedMatchingBifield": [
        "ID"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setIDSlaveTask",
      "functionArgs": [
        "base",
        "identifier"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ID"
      ],
      "registersUsedMatchingBifield": [
        "ID"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_sendWakeupSignal",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR2",
        "TD0"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR2",
        "TD0"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enterSleep",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR2"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR2"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_sendChecksum",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR2"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR2"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_triggerChecksumCompare",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR2"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR2"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_isTxReady",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setFrameLength",
      "functionArgs": [
        "base",
        "length"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIFORMAT"
      ],
      "registersUsedMatchingBifield": [
        "SCIFORMAT"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setCommMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_CommMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setTxMask",
      "functionArgs": [
        "base",
        "mask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MASK"
      ],
      "registersUsedMatchingBifield": [
        "MASK"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setRxMask",
      "functionArgs": [
        "base",
        "mask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MASK"
      ],
      "registersUsedMatchingBifield": [
        "MASK"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_getTxMask",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MASK"
      ],
      "registersUsedMatchingBifield": [
        "MASK"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_getRxMask",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MASK"
      ],
      "registersUsedMatchingBifield": [
        "MASK"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_isRxReady",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_getRxIdentifier",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "ID"
      ],
      "registersUsedMatchingBifield": [
        "ID"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_isTxMatch",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_isRxMatch",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableInterrupt",
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
        "SCISETINT"
      ],
      "registersUsedMatchingBifield": [
        "SCISETINT"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableInterrupt",
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
        "SCICLEARINT"
      ],
      "registersUsedMatchingBifield": [
        "SCICLEARINT"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_clearInterruptStatus",
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
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setInterruptLevel0",
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
        "SCICLEARINT",
        "SCICLEARINTLVL"
      ],
      "registersUsedMatchingBifield": [
        "SCICLEARINT",
        "SCICLEARINTLVL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setInterruptLevel1",
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
        "SCISETINT",
        "SCISETINTLVL"
      ],
      "registersUsedMatchingBifield": [
        "SCISETINT",
        "SCISETINTLVL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableModuleErrors",
      "functionArgs": [
        "base",
        "errors"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IODFTCTRL"
      ],
      "registersUsedMatchingBifield": [
        "IODFTCTRL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableModuleErrors",
      "functionArgs": [
        "base",
        "errors"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IODFTCTRL"
      ],
      "registersUsedMatchingBifield": [
        "IODFTCTRL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableAutomaticBaudrate",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableAutomaticBaudrate",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_stopExtendedFrame",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setChecksumType",
      "functionArgs": [
        "base",
        "type"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_ChecksumType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setSyncFields",
      "functionArgs": [
        "base",
        "syncBreak",
        "delimiter"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMP"
      ],
      "registersUsedMatchingBifield": [
        "COMP"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableSCIMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableSCIMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setSCICommMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_SCICommMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableSCIParity",
      "functionArgs": [
        "base",
        "parity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_SCIParityType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableSCIParity",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setSCIStopBits",
      "functionArgs": [
        "base",
        "number"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_SCIStopBits"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableSCISleepMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableSCISleepMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enterSCILowPower",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1",
        "SCIGCR2"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIGCR2"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_exitSCILowPower",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1",
        "SCIGCR2"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIGCR2"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setSCICharLength",
      "functionArgs": [
        "base",
        "numBits"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1",
        "SCIFORMAT"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIFORMAT"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setSCIFrameLength",
      "functionArgs": [
        "base",
        "length"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1",
        "SCIFORMAT"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIFORMAT"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_isSCIDataAvailable",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIGCR1",
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_isSCISpaceAvailable",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIGCR1",
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_readSCICharNonBlocking",
      "functionArgs": [
        "base",
        "emulation"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "SCIGCR1",
        "SCIED",
        "SCIRD"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIED",
        "SCIRD"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_readSCICharBlocking",
      "functionArgs": [
        "base",
        "emulation"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "SCIGCR1",
        "SCIED",
        "SCIRD"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIED",
        "SCIRD"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_writeSCICharNonBlocking",
      "functionArgs": [
        "base",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1",
        "SCITD"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCITD"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_writeSCICharBlocking",
      "functionArgs": [
        "base",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1",
        "SCITD"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCITD"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableSCIModuleErrors",
      "functionArgs": [
        "base",
        "errors"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1",
        "IODFTCTRL"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "IODFTCTRL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableSCIModuleErrors",
      "functionArgs": [
        "base",
        "errors"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1",
        "IODFTCTRL"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "IODFTCTRL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableSCIInterrupt",
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
        "SCIGCR1",
        "SCISETINT"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCISETINT"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableSCIInterrupt",
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
        "SCIGCR1",
        "SCICLEARINT"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCICLEARINT"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_clearSCIInterruptStatus",
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
        "SCIGCR1",
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setSCIInterruptLevel0",
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
        "SCIGCR1",
        "SCICLEARINT",
        "SCICLEARINTLVL"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCICLEARINT",
        "SCICLEARINTLVL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setSCIInterruptLevel1",
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
        "SCIGCR1",
        "SCISETINT",
        "SCISETINTLVL"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCISETINT",
        "SCISETINTLVL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_isSCIReceiverIdle",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIGCR1",
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_getSCITxFrameType",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIGCR1",
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_getSCIRxFrameType",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIGCR1",
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_isSCIBreakDetected",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIGCR1",
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1",
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR0",
        "SCIPIO0"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR0",
        "SCIPIO0"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR0",
        "SCIPIO0"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR0",
        "SCIPIO0"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setBaudRatePrescaler",
      "functionArgs": [
        "base",
        "prescaler",
        "divider"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "BRSR"
      ],
      "registersUsedMatchingBifield": [
        "BRSR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableDataTransmitter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableDataTransmitter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableDataReceiver",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableDataReceiver",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_performSoftwareReset",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enterSoftwareReset",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_exitSoftwareReset",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_isBusBusy",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_isTxBufferEmpty",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableExtLoopback",
      "functionArgs": [
        "base",
        "loopbackType",
        "path"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_LoopbackType",
        "LIN_AnalogLoopback"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IODFTCTRL"
      ],
      "registersUsedMatchingBifield": [
        "IODFTCTRL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableExtLoopback",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IODFTCTRL"
      ],
      "registersUsedMatchingBifield": [
        "IODFTCTRL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableIntLoopback",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableIntLoopback",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_getInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "SCIFLR"
      ],
      "registersUsedMatchingBifield": [
        "SCIFLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_getInterruptLevel",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "SCISETINT",
        "SCISETINTLVL"
      ],
      "registersUsedMatchingBifield": [
        "SCISETINT",
        "SCISETINTLVL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_getInterruptLine0Offset",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "SCIINTVECT0"
      ],
      "registersUsedMatchingBifield": [
        "SCIINTVECT0"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_getInterruptLine1Offset",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "SCIINTVECT1"
      ],
      "registersUsedMatchingBifield": [
        "SCIINTVECT1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableMultibufferMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableMultibufferMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setTransmitDelay",
      "functionArgs": [
        "base",
        "delay"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IODFTCTRL"
      ],
      "registersUsedMatchingBifield": [
        "IODFTCTRL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setPinSampleMask",
      "functionArgs": [
        "base",
        "mask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_PinSampleMask"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IODFTCTRL"
      ],
      "registersUsedMatchingBifield": [
        "IODFTCTRL"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_setDebugSuspendMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_DebugMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCIGCR1"
      ],
      "registersUsedMatchingBifield": [
        "SCIGCR1"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_enableGlobalInterrupt",
      "functionArgs": [
        "base",
        "line"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_InterruptLine"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLB_INT_EN"
      ],
      "registersUsedMatchingBifield": [
        "GLB_INT_EN"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_disableGlobalInterrupt",
      "functionArgs": [
        "base",
        "line"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_InterruptLine"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLB_INT_EN"
      ],
      "registersUsedMatchingBifield": [
        "GLB_INT_EN"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_clearGlobalInterruptStatus",
      "functionArgs": [
        "base",
        "line"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_InterruptLine"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLB_INT_CLR"
      ],
      "registersUsedMatchingBifield": [
        "GLB_INT_CLR"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_getGlobalInterruptStatus",
      "functionArgs": [
        "base",
        "line"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_InterruptLine"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "GLB_INT_FLG"
      ],
      "registersUsedMatchingBifield": [
        "GLB_INT_FLG"
      ]
    },
    {
      "file": "lin.h",
      "peripheral": "lin",
      "functionName": "LIN_getPinStatus",
      "functionArgs": [
        "base",
        "pin"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "LIN_PinType"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCIPIO2"
      ],
      "registersUsedMatchingBifield": [
        "SCIPIO2"
      ]
    }
  ]
}
module.exports = { 
  lin_driverlib: lin_driverlib,
}
