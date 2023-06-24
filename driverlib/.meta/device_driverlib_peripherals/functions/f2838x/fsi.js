let fsi_driverlib = 
{
  "name": "fsi",
  "functions": [
    {
      "file": "fsi.c",
      "peripheral": "fsi",
      "functionName": "FSI_delayWait",
      "functionArgs": [
        "n"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "fsi.c",
      "peripheral": "fsi",
      "functionName": "FSI_resetTxModule",
      "functionArgs": [
        "base",
        "submodule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_TxSubmoduleInReset"
      ],
      "returnType": "void",
      "registersUsed": [
        "TX_MASTER_CTRL",
        "TX_CLK_CTRL",
        "TX_PING_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_MASTER_CTRL",
        "TX_CLK_CTRL",
        "TX_PING_CTRL"
      ]
    },
    {
      "file": "fsi.c",
      "peripheral": "fsi",
      "functionName": "FSI_clearTxModuleReset",
      "functionArgs": [
        "base",
        "submodule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_TxSubmoduleInReset"
      ],
      "returnType": "void",
      "registersUsed": [
        "TX_MASTER_CTRL",
        "TX_CLK_CTRL",
        "TX_PING_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_MASTER_CTRL",
        "TX_CLK_CTRL",
        "TX_PING_CTRL"
      ]
    },
    {
      "file": "fsi.c",
      "peripheral": "fsi",
      "functionName": "FSI_writeTxBuffer",
      "functionArgs": [
        "base",
        "array[]",
        "length",
        "bufOffset"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint16_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TX_BUF_BASE"
      ],
      "registersUsedMatchingBifield": [
        "TX_BUF_BASE"
      ]
    },
    {
      "file": "fsi.c",
      "peripheral": "fsi",
      "functionName": "FSI_resetRxModule",
      "functionArgs": [
        "base",
        "submodule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_RxSubmoduleInReset"
      ],
      "returnType": "void",
      "registersUsed": [
        "RX_MASTER_CTRL",
        "RX_FRAME_WD_CTRL",
        "RX_PING_WD_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_MASTER_CTRL",
        "RX_FRAME_WD_CTRL",
        "RX_PING_WD_CTRL"
      ]
    },
    {
      "file": "fsi.c",
      "peripheral": "fsi",
      "functionName": "FSI_clearRxModuleReset",
      "functionArgs": [
        "base",
        "submodule"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_RxSubmoduleInReset"
      ],
      "returnType": "void",
      "registersUsed": [
        "RX_MASTER_CTRL",
        "RX_FRAME_WD_CTRL",
        "RX_PING_WD_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_MASTER_CTRL",
        "RX_FRAME_WD_CTRL",
        "RX_PING_WD_CTRL"
      ]
    },
    {
      "file": "fsi.c",
      "peripheral": "fsi",
      "functionName": "FSI_readRxBuffer",
      "functionArgs": [
        "base",
        "array[]",
        "length",
        "bufOffset"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "RX_BUF_BASE"
      ],
      "registersUsedMatchingBifield": [
        "RX_BUF_BASE"
      ]
    },
    {
      "file": "fsi.c",
      "peripheral": "fsi",
      "functionName": "FSI_configRxDelayLine",
      "functionArgs": [
        "base",
        "delayTapType",
        "tapValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_RxDelayTapType",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "RX_DLYLINE_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_DLYLINE_CTRL"
      ]
    },
    {
      "file": "fsi.c",
      "peripheral": "fsi",
      "functionName": "FSI_performTxInitialization",
      "functionArgs": [
        "base",
        "prescalar"
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
      "file": "fsi.c",
      "peripheral": "fsi",
      "functionName": "FSI_performRxInitialization",
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
      "file": "fsi.c",
      "peripheral": "fsi",
      "functionName": "FSI_executeTxFlushSequence",
      "functionArgs": [
        "base",
        "prescalar"
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
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_isTxBaseValid",
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
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_sendTxFlush",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_MASTER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_MASTER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_stopTxFlush",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_MASTER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_MASTER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_selectTxPLLClock",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_LO"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_LO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableTxClock",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_CLK_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_CLK_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableTxClock",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_CLK_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_CLK_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_configPrescalar",
      "functionArgs": [
        "base",
        "preScaleValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_CLK_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_CLK_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxDataWidth",
      "functionArgs": [
        "base",
        "dataWidth"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_DataWidth"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_LO"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_LO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableTxSPIMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_LO"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_LO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableTxSPIMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_LO"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_LO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxStartMode",
      "functionArgs": [
        "base",
        "txStartMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_TxStartMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_LO"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_LO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxPingTimeoutMode",
      "functionArgs": [
        "base",
        "pingTimeoutMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_PingTimeoutMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_LO"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_LO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableTxTDMMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_LO"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_LO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableTxTDMMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_LO"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_LO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxExtFrameTrigger",
      "functionArgs": [
        "base",
        "extInputNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_HI"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_HI"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableTxCRCForceError",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_HI"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_HI"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableTxCRCForceError",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_HI"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_HI"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxECCComputeWidth",
      "functionArgs": [
        "base",
        "eccComputeWidth"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_ECCComputeWidth"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_HI"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_HI"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxFrameType",
      "functionArgs": [
        "base",
        "frameType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_FrameType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_FRAME_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_FRAME_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxSoftwareFrameSize",
      "functionArgs": [
        "base",
        "nWords"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_FRAME_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_FRAME_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_startTxTransmit",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_FRAME_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_FRAME_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxFrameTag",
      "functionArgs": [
        "base",
        "frameTag"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_FrameTag"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_FRAME_TAG_UDATA"
      ],
      "registersUsedMatchingBifield": [
        "TX_FRAME_TAG_UDATA"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxUserDefinedData",
      "functionArgs": [
        "base",
        "userDefData"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_FRAME_TAG_UDATA"
      ],
      "registersUsedMatchingBifield": [
        "TX_FRAME_TAG_UDATA"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxBufferPtr",
      "functionArgs": [
        "base",
        "bufPtrOff"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_BUF_PTR_LOAD"
      ],
      "registersUsedMatchingBifield": [
        "TX_BUF_PTR_LOAD"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getTxBufferPtr",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TX_BUF_PTR_STS"
      ],
      "registersUsedMatchingBifield": [
        "TX_BUF_PTR_STS"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getTxWordCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TX_BUF_PTR_STS"
      ],
      "registersUsedMatchingBifield": [
        "TX_BUF_PTR_STS"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableTxPingTimer",
      "functionArgs": [
        "base",
        "refValue",
        "pingFrameTag"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "FSI_FrameTag"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_PING_CTRL",
        "TX_PING_TAG",
        "TX_PING_TO_REF"
      ],
      "registersUsedMatchingBifield": [
        "TX_PING_CTRL",
        "TX_PING_TAG",
        "TX_PING_TO_REF"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxPingTag",
      "functionArgs": [
        "base",
        "frameTag"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_FrameTag"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_PING_TAG"
      ],
      "registersUsedMatchingBifield": [
        "TX_PING_TAG"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableTxPingTimer",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_PING_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_PING_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableTxExtPingTrigger",
      "functionArgs": [
        "base",
        "extTrigSel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_PING_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_PING_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableTxExtPingTrigger",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_PING_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_PING_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getTxCurrentPingTimeoutCounter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "TX_PING_TO_CNT"
      ],
      "registersUsedMatchingBifield": [
        "TX_PING_TO_CNT"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableTxDMAEvent",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_DMA_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_DMA_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableTxDMAEvent",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_DMA_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_DMA_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_lockTxCtrl",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_LOCK_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_LOCK_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getTxEventStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TX_EVT_STS"
      ],
      "registersUsedMatchingBifield": [
        "TX_EVT_STS"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_forceTxEvents",
      "functionArgs": [
        "base",
        "evtFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_EVT_FRC"
      ],
      "registersUsedMatchingBifield": [
        "TX_EVT_FRC"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_clearTxEvents",
      "functionArgs": [
        "base",
        "evtFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_EVT_CLR"
      ],
      "registersUsedMatchingBifield": [
        "TX_EVT_CLR"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableTxUserCRC",
      "functionArgs": [
        "base",
        "userCRCValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_LO",
        "TX_USER_CRC"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_LO",
        "TX_USER_CRC"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableTxUserCRC",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_OPER_CTRL_LO"
      ],
      "registersUsedMatchingBifield": [
        "TX_OPER_CTRL_LO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setTxECCdata",
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
        "TX_ECC_DATA"
      ],
      "registersUsedMatchingBifield": [
        "TX_ECC_DATA"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getTxECCValue",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TX_ECC_VAL"
      ],
      "registersUsedMatchingBifield": [
        "TX_ECC_VAL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableTxInterrupt",
      "functionArgs": [
        "base",
        "intNum",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_InterruptNum",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_INT_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_INT_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableTxInterrupt",
      "functionArgs": [
        "base",
        "intNum",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_InterruptNum",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TX_INT_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "TX_INT_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getTxBufferAddress",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "TX_BUF_BASE"
      ],
      "registersUsedMatchingBifield": [
        "TX_BUF_BASE"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_isRxBaseValid",
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
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableRxInternalLoopback",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_MASTER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_MASTER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableRxInternalLoopback",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_MASTER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_MASTER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableRxSPIPairing",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_MASTER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_MASTER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableRxSPIPairing",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_MASTER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_MASTER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setRxDataWidth",
      "functionArgs": [
        "base",
        "dataWidth"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_DataWidth"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_OPER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_OPER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableRxSPIMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_OPER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_OPER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableRxSPIMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_OPER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_OPER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setRxSoftwareFrameSize",
      "functionArgs": [
        "base",
        "nWords"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_OPER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_OPER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setRxECCComputeWidth",
      "functionArgs": [
        "base",
        "eccComputeWidth"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_ECCComputeWidth"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_OPER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_OPER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setRxPingTimeoutMode",
      "functionArgs": [
        "base",
        "pingTimeoutMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_PingTimeoutMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_OPER_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_OPER_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxFrameType",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline FSI_FrameType",
      "registersUsed": [
        "RX_FRAME_INFO"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_INFO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableRxDMAEvent",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_DMA_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_DMA_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableRxDMAEvent",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_DMA_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_DMA_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxFrameTag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_FRAME_TAG_UDATA"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_TAG_UDATA"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxUserDefinedData",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_FRAME_TAG_UDATA"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_TAG_UDATA"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxEventStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_EVT_STS"
      ],
      "registersUsedMatchingBifield": [
        "RX_EVT_STS"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_forceRxEvents",
      "functionArgs": [
        "base",
        "evtFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_EVT_FRC"
      ],
      "registersUsedMatchingBifield": [
        "RX_EVT_FRC"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_clearRxEvents",
      "functionArgs": [
        "base",
        "evtFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_EVT_CLR"
      ],
      "registersUsedMatchingBifield": [
        "RX_EVT_CLR"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxReceivedCRC",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_CRC_INFO"
      ],
      "registersUsedMatchingBifield": [
        "RX_CRC_INFO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxComputedCRC",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_CRC_INFO"
      ],
      "registersUsedMatchingBifield": [
        "RX_CRC_INFO"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setRxBufferPtr",
      "functionArgs": [
        "base",
        "bufPtrOff"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_BUF_PTR_LOAD"
      ],
      "registersUsedMatchingBifield": [
        "RX_BUF_PTR_LOAD"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxBufferPtr",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_BUF_PTR_STS"
      ],
      "registersUsedMatchingBifield": [
        "RX_BUF_PTR_STS"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxWordCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_BUF_PTR_STS"
      ],
      "registersUsedMatchingBifield": [
        "RX_BUF_PTR_STS"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableRxFrameWatchdog",
      "functionArgs": [
        "base",
        "wdRef"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_FRAME_WD_CTRL",
        "RX_FRAME_WD_REF"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_WD_CTRL",
        "RX_FRAME_WD_REF"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableRxFrameWatchdog",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_FRAME_WD_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_WD_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxFrameWatchdogCounter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "RX_FRAME_WD_CNT"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_WD_CNT"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableRxPingWatchdog",
      "functionArgs": [
        "base",
        "wdRef"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_PING_WD_CTRL",
        "RX_PING_WD_REF"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_WD_CTRL",
        "RX_PING_WD_REF"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableRxPingWatchdog",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_PING_WD_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_WD_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxPingWatchdogCounter",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "RX_PING_WD_CNT"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_WD_CNT"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxPingTag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_PING_TAG"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_TAG"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_lockRxCtrl",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_LOCK_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_LOCK_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setRxECCData",
      "functionArgs": [
        "base",
        "rxECCdata"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_ECC_DATA"
      ],
      "registersUsedMatchingBifield": [
        "RX_ECC_DATA"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setRxReceivedECCValue",
      "functionArgs": [
        "base",
        "rxECCvalue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_ECC_VAL"
      ],
      "registersUsedMatchingBifield": [
        "RX_ECC_VAL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxECCCorrectedData",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "RX_ECC_SEC_DATA"
      ],
      "registersUsedMatchingBifield": [
        "RX_ECC_SEC_DATA"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxECCLog",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_ECC_LOG"
      ],
      "registersUsedMatchingBifield": [
        "RX_ECC_LOG"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableRxInterrupt",
      "functionArgs": [
        "base",
        "intNum",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_InterruptNum",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_INT1_CTRL",
        "RX_INT2_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_INT1_CTRL",
        "RX_INT2_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableRxInterrupt",
      "functionArgs": [
        "base",
        "intNum",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "FSI_InterruptNum",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_INT1_CTRL",
        "RX_INT2_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "RX_INT1_CTRL",
        "RX_INT2_CTRL"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxBufferAddress",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "RX_BUF_BASE"
      ],
      "registersUsedMatchingBifield": [
        "RX_BUF_BASE"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setRxFrameTagRef",
      "functionArgs": [
        "base",
        "refVal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_FRAME_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxFrameTagRef",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_FRAME_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setRxFrameTagMask",
      "functionArgs": [
        "base",
        "maskVal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_FRAME_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxFrameTagMask",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_FRAME_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableRxFrameTagCompare",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_FRAME_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableRxFrameTagCompare",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_FRAME_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableRxFrameBroadcast",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_FRAME_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableRxFrameBroadcast",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_FRAME_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_FRAME_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setRxPingTagRef",
      "functionArgs": [
        "base",
        "refVal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxPingTagRef",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_setRxPingTagMask",
      "functionArgs": [
        "base",
        "maskVal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_getRxPingTagMask",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableRxPingTagCompare",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableRxPingTagCompare",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_enableRxPingBroadcast",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ]
    },
    {
      "file": "fsi.h",
      "peripheral": "fsi",
      "functionName": "FSI_disableRxPingBroadcast",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ],
      "registersUsedMatchingBifield": [
        "RX_PING_TAG",
        "RX_PING_TAG_CMP"
      ]
    }
  ]
}
module.exports = { 
  fsi_driverlib: fsi_driverlib,
}
