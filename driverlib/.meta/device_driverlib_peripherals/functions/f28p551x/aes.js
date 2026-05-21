let aes_driverlib = 
{
  "name": "aes",
  "functions": [
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_configureModule",
      "functionArgs": [
        "base",
        "*config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constAES_ConfigParams"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTRL"
      ],
      "registersUsedMatchingBifield": [
        "CTRL"
      ]
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_setKey1",
      "functionArgs": [
        "base",
        "key[]",
        "keySize"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint32_t",
        "AES_KeySize"
      ],
      "returnType": "void",
      "registersUsed": [
        "KEY1_6",
        "KEY1_7",
        "KEY1_4",
        "KEY1_5",
        "KEY1_2",
        "KEY1_3",
        "KEY1_0",
        "KEY1_1"
      ],
      "registersUsedMatchingBifield": [
        "KEY1_6",
        "KEY1_7",
        "KEY1_4",
        "KEY1_5",
        "KEY1_2",
        "KEY1_3",
        "KEY1_0",
        "KEY1_1"
      ]
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_setKey2",
      "functionArgs": [
        "base",
        "key[]",
        "keySize"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint32_t",
        "AES_KeySize"
      ],
      "returnType": "void",
      "registersUsed": [
        "KEY2_6",
        "KEY2_7",
        "KEY2_4",
        "KEY2_5",
        "KEY2_2",
        "KEY2_3",
        "KEY2_0",
        "KEY2_1"
      ],
      "registersUsedMatchingBifield": [
        "KEY2_6",
        "KEY2_7",
        "KEY2_4",
        "KEY2_5",
        "KEY2_2",
        "KEY2_3",
        "KEY2_0",
        "KEY2_1"
      ]
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_setKey3",
      "functionArgs": [
        "base",
        "key[]"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "KEY2_6",
        "KEY2_7",
        "KEY2_4",
        "KEY2_5"
      ],
      "registersUsedMatchingBifield": [
        "KEY2_6",
        "KEY2_7",
        "KEY2_4",
        "KEY2_5"
      ]
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_setInitializationVector",
      "functionArgs": [
        "base",
        "iniVector[]"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IV_IN_OUT_0",
        "IV_IN_OUT_1",
        "IV_IN_OUT_2",
        "IV_IN_OUT_3"
      ],
      "registersUsedMatchingBifield": [
        "IV_IN_OUT_0",
        "IV_IN_OUT_1",
        "IV_IN_OUT_2",
        "IV_IN_OUT_3"
      ]
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_readInitializationVector",
      "functionArgs": [
        "base",
        "iniVector[]"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IV_IN_OUT_0",
        "IV_IN_OUT_1",
        "IV_IN_OUT_2",
        "IV_IN_OUT_3"
      ],
      "registersUsedMatchingBifield": [
        "IV_IN_OUT_0",
        "IV_IN_OUT_1",
        "IV_IN_OUT_2",
        "IV_IN_OUT_3"
      ]
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_readTag",
      "functionArgs": [
        "base",
        "tagData[]"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTRL",
        "TAG_OUT_0",
        "TAG_OUT_1",
        "TAG_OUT_2",
        "TAG_OUT_3"
      ],
      "registersUsedMatchingBifield": [
        "CTRL",
        "TAG_OUT_0",
        "TAG_OUT_1",
        "TAG_OUT_2",
        "TAG_OUT_3"
      ]
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_readDataNonBlocking",
      "functionArgs": [
        "base",
        "destArray[]"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "bool",
      "registersUsed": [
        "CTRL",
        "DATA_IN_OUT_0",
        "DATA_IN_OUT_1",
        "DATA_IN_OUT_2",
        "DATA_IN_OUT_3"
      ],
      "registersUsedMatchingBifield": [
        "CTRL",
        "DATA_IN_OUT_0",
        "DATA_IN_OUT_1",
        "DATA_IN_OUT_2",
        "DATA_IN_OUT_3"
      ]
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_readDataBlocking",
      "functionArgs": [
        "base",
        "destArray[]"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTRL",
        "DATA_IN_OUT_0",
        "DATA_IN_OUT_1",
        "DATA_IN_OUT_2",
        "DATA_IN_OUT_3"
      ],
      "registersUsedMatchingBifield": [
        "CTRL",
        "DATA_IN_OUT_0",
        "DATA_IN_OUT_1",
        "DATA_IN_OUT_2",
        "DATA_IN_OUT_3"
      ]
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_writeDataNonBlocking",
      "functionArgs": [
        "base",
        "srcArray[]"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint32_t"
      ],
      "returnType": "bool",
      "registersUsed": [
        "CTRL",
        "DATA_IN_OUT_0",
        "DATA_IN_OUT_1",
        "DATA_IN_OUT_2",
        "DATA_IN_OUT_3"
      ],
      "registersUsedMatchingBifield": [
        "CTRL",
        "DATA_IN_OUT_0",
        "DATA_IN_OUT_1",
        "DATA_IN_OUT_2",
        "DATA_IN_OUT_3"
      ]
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_writeDataBlocking",
      "functionArgs": [
        "base",
        "srcArray[]"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTRL",
        "DATA_IN_OUT_0",
        "DATA_IN_OUT_1",
        "DATA_IN_OUT_2",
        "DATA_IN_OUT_3"
      ],
      "registersUsedMatchingBifield": [
        "CTRL",
        "DATA_IN_OUT_0",
        "DATA_IN_OUT_1",
        "DATA_IN_OUT_2",
        "DATA_IN_OUT_3"
      ]
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_processData",
      "functionArgs": [
        "base",
        "srcArray[]",
        "destArray[]",
        "dataLength"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint32_t",
        "uint32_t",
        "uint64_t"
      ],
      "returnType": "bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_authenticateData",
      "functionArgs": [
        "base",
        "srcArray[]",
        "dataLength",
        "tagArray[]"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint32_t",
        "uint64_t",
        "uint32_t"
      ],
      "returnType": "bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_processDatainAuthMode",
      "functionArgs": [
        "base",
        "srcArray[]",
        "destArray[]",
        "dataLength",
        "authDataArray[]",
        "authDataLength",
        "tagArray[]"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint32_t",
        "uint32_t",
        "uint64_t",
        "constuint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "aes.c",
      "peripheral": "aes",
      "functionName": "AES_getInterruptStatus",
      "functionArgs": [
        "base",
        "intMask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "IRQSTATUS",
        "IRQENABLE"
      ],
      "registersUsedMatchingBifield": [
        "IRQSTATUS",
        "IRQENABLE"
      ]
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_isBaseValid",
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
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_isWrapperBaseValid",
      "functionArgs": [
        "wrapperBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef DEBUG  static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_performSoftReset",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYSCONFIG",
        "SYSSTATUS"
      ],
      "registersUsedMatchingBifield": [
        "SYSCONFIG",
        "SYSSTATUS"
      ]
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_setDataLength",
      "functionArgs": [
        "base",
        "length"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint64_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "C_LENGTH_0",
        "C_LENGTH_1"
      ],
      "registersUsedMatchingBifield": [
        "C_LENGTH_0",
        "C_LENGTH_1"
      ]
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_setAuthDataLength",
      "functionArgs": [
        "base",
        "authLength"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AUTH_LENGTH"
      ],
      "registersUsedMatchingBifield": [
        "AUTH_LENGTH"
      ]
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_enableInterrupt",
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
        "IRQENABLE"
      ],
      "registersUsedMatchingBifield": [
        "IRQENABLE"
      ]
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_disableInterrupt",
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
        "IRQENABLE"
      ],
      "registersUsedMatchingBifield": [
        "IRQENABLE"
      ]
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_enableGlobalInterrupt",
      "functionArgs": [
        "wrapperBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AES_GLB_INT_FLG"
      ],
      "registersUsedMatchingBifield": [
        "AES_GLB_INT_FLG"
      ]
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_disableGlobalInterrupt",
      "functionArgs": [
        "wrapperBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AES_GLB_INT_FLG"
      ],
      "registersUsedMatchingBifield": [
        "AES_GLB_INT_FLG"
      ]
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_clearGlobalInterrupt",
      "functionArgs": [
        "wrapperBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AES_GLB_INT_CLR"
      ],
      "registersUsedMatchingBifield": [
        "AES_GLB_INT_CLR"
      ]
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_getGlobalInterruptStatus",
      "functionArgs": [
        "wrapperBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "AES_GLB_INT_FLG"
      ],
      "registersUsedMatchingBifield": [
        "AES_GLB_INT_FLG"
      ]
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_registerInterrupt",
      "functionArgs": [
        "void)"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_unregisterInterrupt",
      "functionArgs": [
        "intNum"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_enableDMARequest",
      "functionArgs": [
        "base",
        "reqFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYSCONFIG"
      ],
      "registersUsedMatchingBifield": [
        "SYSCONFIG"
      ]
    },
    {
      "file": "aes.h",
      "peripheral": "aes",
      "functionName": "AES_disableDMARequest",
      "functionArgs": [
        "base",
        "reqFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYSCONFIG"
      ],
      "registersUsedMatchingBifield": [
        "SYSCONFIG"
      ]
    }
  ]
}
module.exports = { 
  aes_driverlib: aes_driverlib,
}
