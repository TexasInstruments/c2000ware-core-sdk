let mcbsp_driverlib = 
{
  "name": "mcbsp",
  "functions": [
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_transmit16BitDataNonBlocking",
      "functionArgs": [
        "base",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_transmit16BitDataBlocking",
      "functionArgs": [
        "base",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_transmit32BitDataNonBlocking",
      "functionArgs": [
        "base",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_transmit32BitDataBlocking",
      "functionArgs": [
        "base",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_receive16BitDataNonBlocking",
      "functionArgs": [
        "base",
        "*receiveData"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_receive16BitDataBlocking",
      "functionArgs": [
        "base",
        "*receiveData"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_receive32BitDataNonBlocking",
      "functionArgs": [
        "base",
        "*receiveData"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_receive32BitDataBlocking",
      "functionArgs": [
        "base",
        "*receiveData"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxDataSize",
      "functionArgs": [
        "base",
        "dataFrame",
        "bitsPerWord",
        "wordsPerFrame"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_DataPhaseFrame",
        "constMcBSP_DataBitsPerWord",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "RCR2",
        "RCR1"
      ],
      "registersUsedMatchingBifield": [
        "RCR2",
        "RCR1"
      ]
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxDataSize",
      "functionArgs": [
        "base",
        "dataFrame",
        "bitsPerWord",
        "wordsPerFrame"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_DataPhaseFrame",
        "constMcBSP_DataBitsPerWord",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "XCR2",
        "XCR1"
      ],
      "registersUsedMatchingBifield": [
        "XCR2",
        "XCR1"
      ]
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_disableRxChannel",
      "functionArgs": [
        "base",
        "partition",
        "channel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_MultichannelPartition",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "RCERA",
        "RCERB",
        "RCERC",
        "RCERD",
        "RCERE",
        "RCERF",
        "RCERG",
        "RCERH"
      ],
      "registersUsedMatchingBifield": [
        "RCERA",
        "RCERB",
        "RCERC",
        "RCERD",
        "RCERE",
        "RCERF",
        "RCERG",
        "RCERH"
      ]
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableRxChannel",
      "functionArgs": [
        "base",
        "partition",
        "channel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_MultichannelPartition",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "RCERA",
        "RCERB",
        "RCERC",
        "RCERD",
        "RCERE",
        "RCERF",
        "RCERG",
        "RCERH"
      ],
      "registersUsedMatchingBifield": [
        "RCERA",
        "RCERB",
        "RCERC",
        "RCERD",
        "RCERE",
        "RCERF",
        "RCERG",
        "RCERH"
      ]
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_disableTxChannel",
      "functionArgs": [
        "base",
        "partition",
        "channel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_MultichannelPartition",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "XCERA",
        "XCERB",
        "XCERC",
        "XCERD",
        "XCERE",
        "XCERF",
        "XCERG",
        "XCERH"
      ],
      "registersUsedMatchingBifield": [
        "XCERA",
        "XCERB",
        "XCERC",
        "XCERD",
        "XCERE",
        "XCERF",
        "XCERG",
        "XCERH"
      ]
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableTxChannel",
      "functionArgs": [
        "base",
        "partition",
        "channel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_MultichannelPartition",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "XCERA",
        "XCERB",
        "XCERC",
        "XCERD",
        "XCERE",
        "XCERF",
        "XCERG",
        "XCERH"
      ],
      "registersUsedMatchingBifield": [
        "XCERA",
        "XCERB",
        "XCERC",
        "XCERD",
        "XCERE",
        "XCERF",
        "XCERG",
        "XCERH"
      ]
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_configureTxClock",
      "functionArgs": [
        "base",
        "*ptrClockParams"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_ClockParams"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_configureRxClock",
      "functionArgs": [
        "base",
        "*ptrClockParams"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_ClockParams"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_configureTxFrameSync",
      "functionArgs": [
        "base",
        "*ptrFsyncParams"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_TxFsyncParams"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_configureRxFrameSync",
      "functionArgs": [
        "base",
        "*ptrFsyncParams"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_RxFsyncParams"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_configureTxDataFormat",
      "functionArgs": [
        "base",
        "*ptrDataParams"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_TxDataParams"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_configureRxDataFormat",
      "functionArgs": [
        "base",
        "*ptrDataParams"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_RxDataParams"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_configureTxMultichannel",
      "functionArgs": [
        "base",
        "*ptrMchnParams"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_TxMultichannelParams"
      ],
      "returnType": "uint16_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_configureRxMultichannel",
      "functionArgs": [
        "base",
        "*ptrMchnParams"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_RxMultichannelParams"
      ],
      "returnType": "uint16_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_configureSPIMasterMode",
      "functionArgs": [
        "base",
        "*ptrSPIMasterMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_SPIMasterModeParams"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.c",
      "peripheral": "mcbsp",
      "functionName": "McBSP_configureSPISlaveMode",
      "functionArgs": [
        "base",
        "*ptrSPISlaveMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_SPISlaveModeParams"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_isBaseValid",
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
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_disableLoopback",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableLoopback",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxSignExtension",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_RxSignExtensionMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setClockStopMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_ClockStopMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_disableDxPinDelay",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableDxPinDelay",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxInterruptSource",
      "functionArgs": [
        "base",
        "interruptSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_RxInterruptSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_clearRxFrameSyncError",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_getRxErrorStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_isRxReady",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_resetReceiver",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableReceiver",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR1"
      ],
      "registersUsedMatchingBifield": [
        "SPCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setEmulationMode",
      "functionArgs": [
        "base",
        "emulationMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_EmulationMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR2"
      ],
      "registersUsedMatchingBifield": [
        "SPCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_resetFrameSyncLogic",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR2"
      ],
      "registersUsedMatchingBifield": [
        "SPCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableFrameSyncLogic",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR2"
      ],
      "registersUsedMatchingBifield": [
        "SPCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_resetSampleRateGenerator",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR2"
      ],
      "registersUsedMatchingBifield": [
        "SPCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableSampleRateGenerator",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR2"
      ],
      "registersUsedMatchingBifield": [
        "SPCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxInterruptSource",
      "functionArgs": [
        "base",
        "interruptSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_TxInterruptSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR2"
      ],
      "registersUsedMatchingBifield": [
        "SPCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_getTxErrorStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "SPCR2"
      ],
      "registersUsedMatchingBifield": [
        "SPCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_clearTxFrameSyncError",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR2"
      ],
      "registersUsedMatchingBifield": [
        "SPCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_isTxReady",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SPCR2"
      ],
      "registersUsedMatchingBifield": [
        "SPCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_resetTransmitter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR2"
      ],
      "registersUsedMatchingBifield": [
        "SPCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableTransmitter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SPCR2"
      ],
      "registersUsedMatchingBifield": [
        "SPCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_disableTwoPhaseRx",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RCR2"
      ],
      "registersUsedMatchingBifield": [
        "RCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableTwoPhaseRx",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RCR2"
      ],
      "registersUsedMatchingBifield": [
        "RCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxCompandingMode",
      "functionArgs": [
        "base",
        "compandingMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_CompandingMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RCR2"
      ],
      "registersUsedMatchingBifield": [
        "RCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_disableRxFrameSyncErrorDetection",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RCR2"
      ],
      "registersUsedMatchingBifield": [
        "RCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableRxFrameSyncErrorDetection",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RCR2"
      ],
      "registersUsedMatchingBifield": [
        "RCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxDataDelayBits",
      "functionArgs": [
        "base",
        "delayBits"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_DataDelayBits"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RCR2"
      ],
      "registersUsedMatchingBifield": [
        "RCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_disableTwoPhaseTx",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "XCR2"
      ],
      "registersUsedMatchingBifield": [
        "XCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableTwoPhaseTx",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "XCR2"
      ],
      "registersUsedMatchingBifield": [
        "XCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxCompandingMode",
      "functionArgs": [
        "base",
        "compandingMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_CompandingMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "XCR2"
      ],
      "registersUsedMatchingBifield": [
        "XCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_disableTxFrameSyncErrorDetection",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "XCR2"
      ],
      "registersUsedMatchingBifield": [
        "XCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableTxFrameSyncErrorDetection",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "XCR2"
      ],
      "registersUsedMatchingBifield": [
        "XCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxDataDelayBits",
      "functionArgs": [
        "base",
        "delayBits"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_DataDelayBits"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "XCR2"
      ],
      "registersUsedMatchingBifield": [
        "XCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setFrameSyncPulsePeriod",
      "functionArgs": [
        "base",
        "frameClockDivider"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SRGR2"
      ],
      "registersUsedMatchingBifield": [
        "SRGR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setFrameSyncPulseWidthDivider",
      "functionArgs": [
        "base",
        "pulseWidthDivider"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SRGR1"
      ],
      "registersUsedMatchingBifield": [
        "SRGR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setSRGDataClockDivider",
      "functionArgs": [
        "base",
        "dataClockDivider"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SRGR1"
      ],
      "registersUsedMatchingBifield": [
        "SRGR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_disableSRGSyncFSR",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SRGR2"
      ],
      "registersUsedMatchingBifield": [
        "SRGR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableSRGSyncFSR",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SRGR2"
      ],
      "registersUsedMatchingBifield": [
        "SRGR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxSRGClockSource",
      "functionArgs": [
        "base",
        "srgClockSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_SRGRxClockSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SRGR2",
        "PCR"
      ],
      "registersUsedMatchingBifield": [
        "SRGR2",
        "PCR"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxSRGClockSource",
      "functionArgs": [
        "base",
        "srgClockSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_SRGTxClockSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SRGR2",
        "PCR"
      ],
      "registersUsedMatchingBifield": [
        "SRGR2",
        "PCR"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxInternalFrameSyncSource",
      "functionArgs": [
        "base",
        "syncMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_TxInternalFrameSyncSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SRGR2"
      ],
      "registersUsedMatchingBifield": [
        "SRGR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxMultichannelPartition",
      "functionArgs": [
        "base",
        "partition"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_MultichannelPartition"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCR1"
      ],
      "registersUsedMatchingBifield": [
        "MCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxTwoPartitionBlock",
      "functionArgs": [
        "base",
        "block"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_PartitionBlock"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCR1"
      ],
      "registersUsedMatchingBifield": [
        "MCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_getRxActiveBlock",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MCR1"
      ],
      "registersUsedMatchingBifield": [
        "MCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxChannelMode",
      "functionArgs": [
        "base",
        "channelMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_RxChannelMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCR1"
      ],
      "registersUsedMatchingBifield": [
        "MCR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxMultichannelPartition",
      "functionArgs": [
        "base",
        "partition"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_MultichannelPartition"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCR2"
      ],
      "registersUsedMatchingBifield": [
        "MCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxTwoPartitionBlock",
      "functionArgs": [
        "base",
        "block"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_PartitionBlock"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCR2"
      ],
      "registersUsedMatchingBifield": [
        "MCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_getTxActiveBlock",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MCR2"
      ],
      "registersUsedMatchingBifield": [
        "MCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxChannelMode",
      "functionArgs": [
        "base",
        "channelMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_TxChannelMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCR2"
      ],
      "registersUsedMatchingBifield": [
        "MCR2"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxFrameSyncSource",
      "functionArgs": [
        "base",
        "syncSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_TxFrameSyncSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCR"
      ],
      "registersUsedMatchingBifield": [
        "PCR"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxFrameSyncSource",
      "functionArgs": [
        "base",
        "syncSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_RxFrameSyncSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCR"
      ],
      "registersUsedMatchingBifield": [
        "PCR"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxClockSource",
      "functionArgs": [
        "base",
        "clockSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_TxClockSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCR"
      ],
      "registersUsedMatchingBifield": [
        "PCR"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxClockSource",
      "functionArgs": [
        "base",
        "clockSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_RxClockSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCR"
      ],
      "registersUsedMatchingBifield": [
        "PCR"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxFrameSyncPolarity",
      "functionArgs": [
        "base",
        "syncPolarity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_TxFrameSyncPolarity"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCR"
      ],
      "registersUsedMatchingBifield": [
        "PCR"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxFrameSyncPolarity",
      "functionArgs": [
        "base",
        "syncPolarity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_RxFrameSyncPolarity"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCR"
      ],
      "registersUsedMatchingBifield": [
        "PCR"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setTxClockPolarity",
      "functionArgs": [
        "base",
        "clockPolarity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_TxClockPolarity"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCR"
      ],
      "registersUsedMatchingBifield": [
        "PCR"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_setRxClockPolarity",
      "functionArgs": [
        "base",
        "clockPolarity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constMcBSP_RxClockPolarity"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCR"
      ],
      "registersUsedMatchingBifield": [
        "PCR"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_read16bitData",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline  uint16_t",
      "registersUsed": [
        "DRR1"
      ],
      "registersUsedMatchingBifield": [
        "DRR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_read32bitData",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "DRR2",
        "DRR1"
      ],
      "registersUsedMatchingBifield": [
        "DRR2",
        "DRR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_write16bitData",
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
        "DXR1"
      ],
      "registersUsedMatchingBifield": [
        "DXR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_write32bitData",
      "functionArgs": [
        "base",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DXR2",
        "DXR1"
      ],
      "registersUsedMatchingBifield": [
        "DXR2",
        "DXR1"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_getLeftJustifyData",
      "functionArgs": [
        "data",
        "compandingType"
      ],
      "functionArgsTypes": [
        "uint16_t",
        "constMcBSP_CompandingType"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableRxInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MFFINT"
      ],
      "registersUsedMatchingBifield": [
        "MFFINT"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_disableRxInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MFFINT"
      ],
      "registersUsedMatchingBifield": [
        "MFFINT"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_enableTxInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MFFINT"
      ],
      "registersUsedMatchingBifield": [
        "MFFINT"
      ]
    },
    {
      "file": "mcbsp.h",
      "peripheral": "mcbsp",
      "functionName": "McBSP_disableTxInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MFFINT"
      ],
      "registersUsedMatchingBifield": [
        "MFFINT"
      ]
    }
  ]
}
module.exports = { 
  mcbsp_driverlib: mcbsp_driverlib,
}
