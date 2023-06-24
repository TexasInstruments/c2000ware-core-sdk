let flash_driverlib = 
{
  "name": "flash",
  "functions": [
    {
      "file": "flash.c",
      "peripheral": "flash",
      "functionName": "Flash_initModule",
      "functionArgs": [
        "ctrlBase",
        "eccBase",
        "waitstates"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "#ifdef __cplusplus  #pragma CODE_SECTION(\".TI.ramfunc\");  #endif  void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_isCtrlBaseValid",
      "functionArgs": [
        "ctrlBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef DEBUG  static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_isECCBaseValid",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef DEBUG  static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_setWaitstates",
      "functionArgs": [
        "ctrlBase",
        "waitstates"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "#ifdef __cplusplus  #pragma CODE_SECTION(\".TI.ramfunc\");  #endif  static inline void",
      "registersUsed": [
        "FRDCNTL"
      ],
      "registersUsedMatchingBifield": [
        "FRDCNTL"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_setEngrWaitstates",
      "functionArgs": [
        "ctrlBase",
        "waitstates"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "#ifdef __cplusplus  #pragma CODE_SECTION(\".TI.ramfunc\");  #endif  static inline void",
      "registersUsed": [
        "FRDCNTL"
      ],
      "registersUsedMatchingBifield": [
        "FRDCNTL"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_enablePrefetch",
      "functionArgs": [
        "ctrlBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef __cplusplus  #pragma CODE_SECTION(\".TI.ramfunc\");  #endif  static inline void",
      "registersUsed": [
        "FRD_INTF_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "FRD_INTF_CTRL"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_disablePrefetch",
      "functionArgs": [
        "ctrlBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef __cplusplus  #pragma CODE_SECTION(\".TI.ramfunc\");  #endif  static inline void",
      "registersUsed": [
        "FRD_INTF_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "FRD_INTF_CTRL"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_enableCache",
      "functionArgs": [
        "ctrlBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef __cplusplus  #pragma CODE_SECTION(\".TI.ramfunc\");  #endif  static inline void",
      "registersUsed": [
        "FRD_INTF_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "FRD_INTF_CTRL"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_disableCache",
      "functionArgs": [
        "ctrlBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef __cplusplus  #pragma CODE_SECTION(\".TI.ramfunc\");  #endif  static inline void",
      "registersUsed": [
        "FRD_INTF_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "FRD_INTF_CTRL"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_setKDIV",
      "functionArgs": [
        "ctrlBase",
        "value"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FLCLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "FLCLKCTL"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getKDIV",
      "functionArgs": [
        "ctrlBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "FLCLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "FLCLKCTL"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_enableECC",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef __cplusplus  #pragma CODE_SECTION(\".TI.ramfunc\");  #endif  static inline void",
      "registersUsed": [
        "ECC_ENABLE"
      ],
      "registersUsedMatchingBifield": [
        "ECC_ENABLE"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_disableECC",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ECC_ENABLE"
      ],
      "registersUsedMatchingBifield": [
        "ECC_ENABLE"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_enableSingleBitECCTestMode",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FECC_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "FECC_CTRL"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_enableDoubleBitECCTestMode",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FECC_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "FECC_CTRL"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_disableSingleBitECCTestMode",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FECC_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "FECC_CTRL"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_disableDoubleBitECCTestMode",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FECC_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "FECC_CTRL"
      ]
    }
  ]
}
module.exports = { 
  flash_driverlib: flash_driverlib,
}
