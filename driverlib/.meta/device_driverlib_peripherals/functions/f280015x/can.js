let can_driverlib = 
{
  "name": "can",
  "functions": [
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_initModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_setBitRate",
      "functionArgs": [
        "base",
        "clock",
        "bitRate",
        "bitTime"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_setBitTiming",
      "functionArgs": [
        "base",
        "prescaler",
        "prescalerExtension",
        "tSeg1",
        "tSeg2",
        "sjw"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t",
        "uint16_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTL",
        "BTR"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL",
        "CAN_BTR"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_clearInterruptStatus",
      "functionArgs": [
        "base",
        "intClr"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "ES",
        "IF1CMD"
      ],
      "registersUsedMatchingBifield": [
        "CAN_ES",
        "CAN_IF1CMD"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_setupMessageObject",
      "functionArgs": [
        "base",
        "objID",
        "msgID",
        "frame",
        "msgType",
        "msgIDMask",
        "flags",
        "msgLen"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "CAN_MsgFrameType",
        "CAN_MsgObjType",
        "uint32_t",
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IF1CMD",
        "IF1MSK",
        "IF1ARB",
        "IF1MCTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IF1CMD",
        "CAN_IF1MSK",
        "CAN_IF1ARB",
        "CAN_IF1MCTL"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_sendMessage",
      "functionArgs": [
        "base",
        "objID",
        "msgLen",
        "*msgData"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint16_t",
        "constuint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IF1CMD",
        "IF1MCTL",
        "IF1DATA",
        "IF1DATB"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IF1CMD",
        "CAN_IF1MCTL",
        "CAN_IF1DATA",
        "CAN_IF1DATB"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_sendMessage_updateDLC",
      "functionArgs": [
        "base",
        "objID",
        "msgLen",
        "*msgData"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint16_t",
        "constuint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IF1CMD",
        "IF1MCTL",
        "IF1DATA",
        "IF1DATB"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IF1CMD",
        "CAN_IF1MCTL",
        "CAN_IF1DATA",
        "CAN_IF1DATB"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_sendRemoteRequestMessage",
      "functionArgs": [
        "base",
        "objID"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IF1CMD",
        "IF1MCTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IF1CMD",
        "CAN_IF1MCTL"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_readMessage",
      "functionArgs": [
        "base",
        "objID",
        "*msgData"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "bool",
      "registersUsed": [
        "IF2CMD",
        "IF2MCTL",
        "IF2DATA",
        "IF2DATB"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IF2CMD",
        "CAN_IF2MCTL",
        "CAN_IF2DATA",
        "CAN_IF2DATB"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_readMessageWithID",
      "functionArgs": [
        "base",
        "objID",
        "*frameType",
        "*msgID",
        "*msgData"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "CAN_MsgFrameType",
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "bool",
      "registersUsed": [
        "IF2ARB"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IF2ARB"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_transferMessage",
      "functionArgs": [
        "base",
        "interface",
        "objID",
        "direction"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint32_t",
        "bool"
      ],
      "returnType": "void",
      "registersUsed": [
        "IF1CMD",
        "IF2CMD"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IF1CMD",
        "CAN_IF2CMD"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_clearMessage",
      "functionArgs": [
        "base",
        "objID"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IF1CMD",
        "IF1ARB"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IF1CMD",
        "CAN_IF1ARB"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_disableMessageObject",
      "functionArgs": [
        "base",
        "objID"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IF1CMD",
        "IF1ARB"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IF1CMD",
        "CAN_IF1ARB"
      ]
    },
    {
      "file": "can.c",
      "peripheral": "can",
      "functionName": "CAN_disableAllMessageObjects",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IF1CMD",
        "IF1ARB"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IF1CMD",
        "CAN_IF1ARB"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_isBaseValid",
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
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_writeDataReg",
      "functionArgs": [
        "data",
        "address",
        "size"
      ],
      "functionArgsTypes": [
        "constuint16_t*const",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_readDataReg",
      "functionArgs": [
        "*data",
        "address",
        "size"
      ],
      "functionArgsTypes": [
        "uint16_t",
        "constuint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_initRAM",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RAM_INIT"
      ],
      "registersUsedMatchingBifield": [
        "CAN_RAM_INIT"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_selectClockSource",
      "functionArgs": [
        "base",
        "source"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CAN_ClockSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLKSRCCTL2"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL2"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_startModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_enableController",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_disableController",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_enableTestMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL",
        "TEST"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL",
        "CAN_TEST"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_disableTestMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL",
        "TEST"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL",
        "CAN_TEST"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_getBitTiming",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "BTR"
      ],
      "registersUsedMatchingBifield": [
        "CAN_BTR"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_enableMemoryAccessMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TEST"
      ],
      "registersUsedMatchingBifield": [
        "CAN_TEST"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_disableMemoryAccessMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TEST"
      ],
      "registersUsedMatchingBifield": [
        "CAN_TEST"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_setInterruptionDebugMode",
      "functionArgs": [
        "base",
        "enable"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_disableAutoBusOn",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_enableAutoBusOn",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_setAutoBusOnTime",
      "functionArgs": [
        "base",
        "time"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ABOTR"
      ],
      "registersUsedMatchingBifield": [
        "CAN_ABOTR"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_enableInterrupt",
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
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_disableInterrupt",
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
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_getInterruptMux",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "IP_MUX21"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IP_MUX21"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_setInterruptMux",
      "functionArgs": [
        "base",
        "mux"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IP_MUX21"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IP_MUX21"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_enableRetry",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_disableRetry",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_isRetryEnabled",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "CAN_CTL"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_getErrorCount",
      "functionArgs": [
        "base",
        "*rxCount",
        "*txCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "ERRC"
      ],
      "registersUsedMatchingBifield": [
        "CAN_ERRC"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_getStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "ES"
      ],
      "registersUsedMatchingBifield": [
        "CAN_ES"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_getTxRequests",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "TXRQ_21"
      ],
      "registersUsedMatchingBifield": [
        "CAN_TXRQ_21"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_getNewDataFlags",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "NDAT_21"
      ],
      "registersUsedMatchingBifield": [
        "CAN_NDAT_21"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_getValidMessageObjects",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "MVAL_21"
      ],
      "registersUsedMatchingBifield": [
        "CAN_MVAL_21"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_getInterruptCause",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "INT"
      ],
      "registersUsedMatchingBifield": [
        "CAN_INT"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_getInterruptMessageSource",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "IPEN_21"
      ],
      "registersUsedMatchingBifield": [
        "CAN_IPEN_21"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_enableGlobalInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLB_INT_EN"
      ],
      "registersUsedMatchingBifield": [
        "CAN_GLB_INT_EN"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_disableGlobalInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLB_INT_EN"
      ],
      "registersUsedMatchingBifield": [
        "CAN_GLB_INT_EN"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_clearGlobalInterruptStatus",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLB_INT_CLR"
      ],
      "registersUsedMatchingBifield": [
        "CAN_GLB_INT_CLR"
      ]
    },
    {
      "file": "can.h",
      "peripheral": "can",
      "functionName": "CAN_getGlobalInterruptStatus",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "GLB_INT_FLG"
      ],
      "registersUsedMatchingBifield": [
        "CAN_GLB_INT_FLG"
      ]
    }
  ]
}
module.exports = { 
  can_driverlib: can_driverlib,
}
