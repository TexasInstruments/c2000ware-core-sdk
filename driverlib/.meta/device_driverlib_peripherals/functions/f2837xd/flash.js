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
      "file": "flash.c",
      "peripheral": "flash",
      "functionName": "Flash_powerDown",
      "functionArgs": [
        "ctrlBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef __cplusplus  #pragma CODE_SECTION(\".TI.ramfunc\");  #endif  void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "flash.c",
      "peripheral": "flash",
      "functionName": "Flash_wakeFromLPM",
      "functionArgs": [
        "ctrlBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
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
      "functionName": "Flash_isPumpSemBaseValid",
      "functionArgs": [
        "pumpSemBase"
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
      "functionName": "Flash_setBankPowerMode",
      "functionArgs": [
        "ctrlBase",
        "bank",
        "powerMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "Flash_BankNumber",
        "Flash_BankPowerMode"
      ],
      "returnType": "#ifdef __cplusplus  #pragma CODE_SECTION(\".TI.ramfunc\");  #endif  static inline void",
      "registersUsed": [
        "FBFALLBACK"
      ],
      "registersUsedMatchingBifield": [
        "FBFALLBACK"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_setPumpPowerMode",
      "functionArgs": [
        "ctrlBase",
        "powerMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "Flash_PumpPowerMode"
      ],
      "returnType": "#ifdef __cplusplus  #pragma CODE_SECTION(\".TI.ramfunc\");  #endif  static inline void",
      "registersUsed": [
        "FPAC1"
      ],
      "registersUsedMatchingBifield": [
        "FPAC1"
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
      "functionName": "Flash_setBankPowerUpDelay",
      "functionArgs": [
        "ctrlBase",
        "delay"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FBAC"
      ],
      "registersUsedMatchingBifield": [
        "FBAC"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_setPumpWakeupTime",
      "functionArgs": [
        "ctrlBase",
        "sysclkCycles"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FPAC1"
      ],
      "registersUsedMatchingBifield": [
        "FPAC1"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_isBankReady",
      "functionArgs": [
        "ctrlBase",
        "bank"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "Flash_BankNumber"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "FBPRDY"
      ],
      "registersUsedMatchingBifield": [
        "FBPRDY"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_isPumpReady",
      "functionArgs": [
        "ctrlBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "FBPRDY"
      ],
      "registersUsedMatchingBifield": [
        "FBPRDY"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getSingleBitErrorAddressLow",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "SINGLE_ERR_ADDR_LOW"
      ],
      "registersUsedMatchingBifield": [
        "SINGLE_ERR_ADDR_LOW"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getSingleBitErrorAddressHigh",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "SINGLE_ERR_ADDR_HIGH"
      ],
      "registersUsedMatchingBifield": [
        "SINGLE_ERR_ADDR_HIGH"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getUncorrectableErrorAddressLow",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "UNC_ERR_ADDR_LOW"
      ],
      "registersUsedMatchingBifield": [
        "UNC_ERR_ADDR_LOW"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getUncorrectableErrorAddressHigh",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "UNC_ERR_ADDR_HIGH"
      ],
      "registersUsedMatchingBifield": [
        "UNC_ERR_ADDR_HIGH"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getLowErrorStatus",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline Flash_ErrorStatus",
      "registersUsed": [
        "ERR_STATUS"
      ],
      "registersUsedMatchingBifield": [
        "ERR_STATUS"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getHighErrorStatus",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline Flash_ErrorStatus",
      "registersUsed": [
        "ERR_STATUS"
      ],
      "registersUsedMatchingBifield": [
        "ERR_STATUS"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getLowErrorPosition",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "ERR_POS"
      ],
      "registersUsedMatchingBifield": [
        "ERR_POS"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getHighErrorPosition",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "ERR_POS"
      ],
      "registersUsedMatchingBifield": [
        "ERR_POS"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getLowErrorType",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline Flash_ErrorType",
      "registersUsed": [
        "ERR_POS"
      ],
      "registersUsedMatchingBifield": [
        "ERR_POS"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getHighErrorType",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline Flash_ErrorType",
      "registersUsed": [
        "ERR_POS"
      ],
      "registersUsedMatchingBifield": [
        "ERR_POS"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_clearLowErrorStatus",
      "functionArgs": [
        "eccBase",
        "errorStatus"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ERR_STATUS",
        "ERR_STATUS_CLR"
      ],
      "registersUsedMatchingBifield": [
        "ERR_STATUS",
        "ERR_STATUS_CLR"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_clearHighErrorStatus",
      "functionArgs": [
        "eccBase",
        "errorStatus"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ERR_STATUS",
        "ERR_STATUS_CLR"
      ],
      "registersUsedMatchingBifield": [
        "ERR_STATUS",
        "ERR_STATUS_CLR"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getErrorCount",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "ERR_CNT"
      ],
      "registersUsedMatchingBifield": [
        "ERR_CNT"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_setErrorThreshold",
      "functionArgs": [
        "eccBase",
        "threshold"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ERR_THRESHOLD"
      ],
      "registersUsedMatchingBifield": [
        "ERR_THRESHOLD"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getInterruptFlag",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "ERR_INTFLG"
      ],
      "registersUsedMatchingBifield": [
        "ERR_INTFLG"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_clearSingleErrorInterruptFlag",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ERR_INTCLR"
      ],
      "registersUsedMatchingBifield": [
        "ERR_INTCLR"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_clearUncorrectableInterruptFlag",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ERR_INTCLR"
      ],
      "registersUsedMatchingBifield": [
        "ERR_INTCLR"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_setDataLowECCTest",
      "functionArgs": [
        "eccBase",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FDATAL_TEST"
      ],
      "registersUsedMatchingBifield": [
        "FDATAL_TEST"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_setDataHighECCTest",
      "functionArgs": [
        "eccBase",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FDATAH_TEST"
      ],
      "registersUsedMatchingBifield": [
        "FDATAH_TEST"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_setECCTestAddress",
      "functionArgs": [
        "eccBase",
        "address"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FADDR_TEST"
      ],
      "registersUsedMatchingBifield": [
        "FADDR_TEST"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_setECCTestECCBits",
      "functionArgs": [
        "eccBase",
        "ecc"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FECC_TEST"
      ],
      "registersUsedMatchingBifield": [
        "FECC_TEST"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_enableECCTestMode",
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
      "functionName": "Flash_disableECCTestMode",
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
      "functionName": "Flash_selectLowECCBlock",
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
      "functionName": "Flash_selectHighECCBlock",
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
      "functionName": "Flash_performECCCalculation",
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
      "functionName": "Flash_getTestDataOutHigh",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "FOUTH_TEST"
      ],
      "registersUsedMatchingBifield": [
        "FOUTH_TEST"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getTestDataOutLow",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "FOUTL_TEST"
      ],
      "registersUsedMatchingBifield": [
        "FOUTL_TEST"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getECCTestStatus",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "FECC_STATUS"
      ],
      "registersUsedMatchingBifield": [
        "FECC_STATUS"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getECCTestErrorPosition",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "FECC_STATUS"
      ],
      "registersUsedMatchingBifield": [
        "FECC_STATUS"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_getECCTestSingleBitErrorType",
      "functionArgs": [
        "eccBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline Flash_SingleBitErrorIndicator",
      "registersUsed": [
        "FECC_STATUS"
      ],
      "registersUsedMatchingBifield": [
        "FECC_STATUS"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_claimPumpSemaphore",
      "functionArgs": [
        "pumpSemBase",
        "wrapper"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "Flash_PumpOwnership"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PUMPREQUEST"
      ],
      "registersUsedMatchingBifield": [
        "PUMPREQUEST"
      ]
    },
    {
      "file": "flash.h",
      "peripheral": "flash",
      "functionName": "Flash_releasePumpSemaphore",
      "functionArgs": [
        "pumpSemBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PUMPREQUEST"
      ],
      "registersUsedMatchingBifield": [
        "PUMPREQUEST"
      ]
    }
  ]
}
module.exports = { 
  flash_driverlib: flash_driverlib,
}
