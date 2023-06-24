let ipc_driverlib = 
{
  "name": "ipc",
  "functions": [
    {
      "file": "ipc.c",
      "peripheral": "ipc",
      "functionName": "IPC_sendCommand",
      "functionArgs": [
        "ipcType",
        "flags",
        "addrCorrEnable",
        "command",
        "addr",
        "data"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t",
        "bool",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.c",
      "peripheral": "ipc",
      "functionName": "IPC_readCommand",
      "functionArgs": [
        "ipcType",
        "flags",
        "addrCorrEnable",
        "*command",
        "*addr",
        "*data"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t",
        "bool",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.c",
      "peripheral": "ipc",
      "functionName": "IPC_Type_tipcType,uint32_tipcInt,void",
      "functionArgs": [
        "void)"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "void IPC_registerInterrupt(",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.c",
      "peripheral": "ipc",
      "functionName": "IPC_unregisterInterrupt",
      "functionArgs": [
        "ipcType",
        "ipcInt"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.c",
      "peripheral": "ipc",
      "functionName": "IPC_initMessageQueue",
      "functionArgs": [
        "ipcType",
        "*msgQueue",
        "ipcInt_L",
        "ipcInt_R"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "volatileIPC_MessageQueue_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.c",
      "peripheral": "ipc",
      "functionName": "IPC_sendMessageToQueue",
      "functionArgs": [
        "ipcType",
        "*msgQueue",
        "addrCorrEnable",
        "*msg",
        "block"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "volatileIPC_MessageQueue_t",
        "bool",
        "IPC_Message_t",
        "bool"
      ],
      "returnType": "bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.c",
      "peripheral": "ipc",
      "functionName": "IPC_readMessageFromQueue",
      "functionArgs": [
        "ipcType",
        "*msgQueue",
        "addrCorrEnable",
        "*msg",
        "block"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "volatileIPC_MessageQueue_t",
        "bool",
        "IPC_Message_t",
        "bool"
      ],
      "returnType": "bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_setFlagLtoR",
      "functionArgs": [
        "ipcType",
        "flags"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_clearFlagLtoR",
      "functionArgs": [
        "ipcType",
        "flags"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_ackFlagRtoL",
      "functionArgs": [
        "ipcType",
        "flags"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_isFlagBusyLtoR",
      "functionArgs": [
        "ipcType",
        "flags"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_isFlagBusyRtoL",
      "functionArgs": [
        "ipcType",
        "flags"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_waitForFlag",
      "functionArgs": [
        "ipcType",
        "flag"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_waitForAck",
      "functionArgs": [
        "ipcType",
        "flag"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_sync",
      "functionArgs": [
        "ipcType",
        "flag"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_init",
      "functionArgs": [
        "ipcType"
      ],
      "functionArgsTypes": [
        "IPC_Type_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_sendResponse",
      "functionArgs": [
        "ipcType",
        "data"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_getResponse",
      "functionArgs": [
        "ipcType"
      ],
      "functionArgsTypes": [
        "IPC_Type_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_setBootMode",
      "functionArgs": [
        "ipcType",
        "mode"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_getBootMode",
      "functionArgs": [
        "ipcType"
      ],
      "functionArgsTypes": [
        "IPC_Type_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_setBootStatus",
      "functionArgs": [
        "ipcType",
        "status"
      ],
      "functionArgsTypes": [
        "IPC_Type_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_getBootStatus",
      "functionArgs": [
        "ipcType"
      ],
      "functionArgsTypes": [
        "IPC_Type_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "ipc.h",
      "peripheral": "ipc",
      "functionName": "IPC_getCounter",
      "functionArgs": [
        "ipcType"
      ],
      "functionArgsTypes": [
        "IPC_Type_t"
      ],
      "returnType": "static inline uint64_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    }
  ]
}
module.exports = { 
  ipc_driverlib: ipc_driverlib,
}
