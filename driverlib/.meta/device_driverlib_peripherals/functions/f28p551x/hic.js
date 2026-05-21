let hic_driverlib = 
{
  "name": "hic",
  "functions": [
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getRevision",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "REV"
      ],
      "registersUsedMatchingBifield": [
        "REV"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_enableHostInterface",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCR"
      ],
      "registersUsedMatchingBifield": [
        "GCR"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_enableLock",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOCK"
      ],
      "registersUsedMatchingBifield": [
        "LOCK"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_disableLock",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOCK"
      ],
      "registersUsedMatchingBifield": [
        "LOCK"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_setConfig",
      "functionArgs": [
        "flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MODECR"
      ],
      "registersUsedMatchingBifield": [
        "MODECR"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getConfig",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "MODECR"
      ],
      "registersUsedMatchingBifield": [
        "MODECR"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_setPinPolarity",
      "functionArgs": [
        "flags"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PINPOLCR"
      ],
      "registersUsedMatchingBifield": [
        "PINPOLCR"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getPinPolarity",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "PINPOLCR"
      ],
      "registersUsedMatchingBifield": [
        "PINPOLCR"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_selectBaseAddress",
      "functionArgs": [
        "selectIndex"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "BASESEL"
      ],
      "registersUsedMatchingBifield": [
        "BASESEL"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getSelectedBaseAddressIndex",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "BASESEL"
      ],
      "registersUsedMatchingBifield": [
        "BASESEL"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_configureHostAccessMode",
      "functionArgs": [
        "config"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HOSTCR"
      ],
      "registersUsedMatchingBifield": [
        "HOSTCR"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getHostAccessMode",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "HOSTCR"
      ],
      "registersUsedMatchingBifield": [
        "HOSTCR"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getErrorAddress",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "ERRADDR"
      ],
      "registersUsedMatchingBifield": [
        "ERRADDR"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getH2DToken",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "H2DTOKEN"
      ],
      "registersUsedMatchingBifield": [
        "H2DTOKEN"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_setD2HToken",
      "functionArgs": [
        "token"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "D2HTOKEN"
      ],
      "registersUsedMatchingBifield": [
        "D2HTOKEN"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getD2HToken",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "D2HTOKEN"
      ],
      "registersUsedMatchingBifield": [
        "D2HTOKEN"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_setBaseAddress",
      "functionArgs": [
        "index",
        "baseAddress"
      ],
      "functionArgsTypes": [
        "uint16_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DBADDR0"
      ],
      "registersUsedMatchingBifield": [
        "DBADDR0"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getBaseAddress",
      "functionArgs": [
        "index"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "DBADDR0"
      ],
      "registersUsedMatchingBifield": [
        "DBADDR0"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_enableH2DInterrupt",
      "functionArgs": [
        "flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "H2DINTEN"
      ],
      "registersUsedMatchingBifield": [
        "H2DINTEN"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_disableH2DInterrupt",
      "functionArgs": [
        "flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "H2DINTEN"
      ],
      "registersUsedMatchingBifield": [
        "H2DINTEN"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getH2DInterruptStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "H2DINTFLG"
      ],
      "registersUsedMatchingBifield": [
        "H2DINTFLG"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_clearH2DInterrupt",
      "functionArgs": [
        "flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "H2DINTCLR"
      ],
      "registersUsedMatchingBifield": [
        "H2DINTCLR"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_forceH2DInterrupt",
      "functionArgs": [
        "flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "H2DINTFRC"
      ],
      "registersUsedMatchingBifield": [
        "H2DINTFRC"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_enableD2HInterrupt",
      "functionArgs": [
        "flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "D2HINTEN"
      ],
      "registersUsedMatchingBifield": [
        "D2HINTEN"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_disableD2HInterrupt",
      "functionArgs": [
        "flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "D2HINTEN"
      ],
      "registersUsedMatchingBifield": [
        "D2HINTEN"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getD2HInterruptStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "D2HINTFLG"
      ],
      "registersUsedMatchingBifield": [
        "D2HINTFLG"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_clearD2HInterrupt",
      "functionArgs": [
        "flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "D2HINTCLR"
      ],
      "registersUsedMatchingBifield": [
        "D2HINTCLR"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_forceD2HInterrupt",
      "functionArgs": [
        "flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "D2HINTFRC"
      ],
      "registersUsedMatchingBifield": [
        "D2HINTFRC"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_getAccessViolationAddress",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "ACCVIOADDR"
      ],
      "registersUsedMatchingBifield": [
        "ACCVIOADDR"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_readH2DBuffer",
      "functionArgs": [
        "offset"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "H2D_BUF0"
      ],
      "registersUsedMatchingBifield": [
        "H2D_BUF0"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_writeH2DBuffer",
      "functionArgs": [
        "offset",
        "data"
      ],
      "functionArgsTypes": [
        "uint16_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "H2D_BUF0"
      ],
      "registersUsedMatchingBifield": [
        "H2D_BUF0"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_clearH2DBuffer",
      "functionArgs": [
        "offset"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "H2D_BUF0"
      ],
      "registersUsedMatchingBifield": [
        "H2D_BUF0"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_readD2HBuffer",
      "functionArgs": [
        "offset"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "D2H_BUF0"
      ],
      "registersUsedMatchingBifield": [
        "D2H_BUF0"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_writeD2HBuffer",
      "functionArgs": [
        "offset",
        "data"
      ],
      "functionArgsTypes": [
        "uint16_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "D2H_BUF0"
      ],
      "registersUsedMatchingBifield": [
        "D2H_BUF0"
      ]
    },
    {
      "file": "hic.h",
      "peripheral": "hic",
      "functionName": "HIC_clearD2HBuffer",
      "functionArgs": [
        "offset"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "D2H_BUF0"
      ],
      "registersUsedMatchingBifield": [
        "D2H_BUF0"
      ]
    }
  ]
}
module.exports = { 
  hic_driverlib: hic_driverlib,
}
