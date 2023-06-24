let erad_driverlib = 
{
  "name": "erad",
  "functions": [
    {
      "file": "erad.c",
      "peripheral": "erad",
      "functionName": "ERAD_configBusComp",
      "functionArgs": [
        "base",
        "config_params"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ERAD_BusComp_Config"
      ],
      "returnType": "void",
      "registersUsed": [
        "HWBP_MASK",
        "HWBP_REF",
        "HWBP_CNTL"
      ],
      "registersUsedMatchingBifield": [
        "HWBP_MASK",
        "HWBP_REF",
        "HWBP_CNTL"
      ]
    },
    {
      "file": "erad.c",
      "peripheral": "erad",
      "functionName": "ERAD_configCounterInCountingMode",
      "functionArgs": [
        "base",
        "config_params"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ERAD_Counter_Config"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTM_CNTL",
        "CTM_REF",
        "CTM_INPUT_SEL"
      ],
      "registersUsedMatchingBifield": [
        "CTM_CNTL",
        "CTM_REF",
        "CTM_INPUT_SEL"
      ]
    },
    {
      "file": "erad.c",
      "peripheral": "erad",
      "functionName": "ERAD_configCounterInStartStopMode",
      "functionArgs": [
        "base",
        "config_params",
        "start_event",
        "stop_event"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ERAD_Counter_Config",
        "ERAD_Counter_Input_Event",
        "ERAD_Counter_Input_Event"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTM_CNTL",
        "CTM_REF",
        "CTM_INPUT_SEL"
      ],
      "registersUsedMatchingBifield": [
        "CTM_CNTL",
        "CTM_REF",
        "CTM_INPUT_SEL"
      ]
    },
    {
      "file": "erad.c",
      "peripheral": "erad",
      "functionName": "ERAD_profile",
      "functionArgs": [
        "config_params"
      ],
      "functionArgsTypes": [
        "ERAD_Profile_Params"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "erad.c",
      "peripheral": "erad",
      "functionName": "ERAD_enableInterruptOnAddressHit",
      "functionArgs": [
        "config_params",
        "busComp_base"
      ],
      "functionArgsTypes": [
        "ERAD_AddressHit_Params",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "erad.c",
      "peripheral": "erad",
      "functionName": "ERAD_countAddressHits",
      "functionArgs": [
        "config_params",
        "busComp_base",
        "counter_base"
      ],
      "functionArgsTypes": [
        "ERAD_AddressHit_Params",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_isValidBusCompBase",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_isValidCounterBase",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_getOwnership",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline ERAD_Owner",
      "registersUsed": [
        "GLBL_OWNER"
      ],
      "registersUsedMatchingBifield": [
        "GLBL_OWNER"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_setOwnership",
      "functionArgs": [
        "owner"
      ],
      "functionArgsTypes": [
        "ERAD_Owner"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLBL_OWNER"
      ],
      "registersUsedMatchingBifield": [
        "GLBL_OWNER"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_resetCounter",
      "functionArgs": [
        "instances"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLBL_CTM_RESET"
      ],
      "registersUsedMatchingBifield": [
        "GLBL_CTM_RESET"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_enableModules",
      "functionArgs": [
        "instances"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLBL_ENABLE"
      ],
      "registersUsedMatchingBifield": [
        "GLBL_ENABLE"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_disableModules",
      "functionArgs": [
        "instances"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLBL_ENABLE"
      ],
      "registersUsedMatchingBifield": [
        "GLBL_ENABLE"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_initModule",
      "functionArgs": [
        "owner"
      ],
      "functionArgsTypes": [
        "ERAD_Owner"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_getHaltStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "GLBL_HALT_STAT"
      ],
      "registersUsedMatchingBifield": [
        "GLBL_HALT_STAT"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_getEventStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "GLBL_EVENT_STAT"
      ],
      "registersUsedMatchingBifield": [
        "GLBL_EVENT_STAT"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_getBusCompStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline ERAD_Status",
      "registersUsed": [
        "HWBP_STATUS"
      ],
      "registersUsedMatchingBifield": [
        "HWBP_STATUS"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_clearBusCompEvent",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HWBP_CLEAR"
      ],
      "registersUsedMatchingBifield": [
        "HWBP_CLEAR"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_getCounterStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline ERAD_Status",
      "registersUsed": [
        "CTM_STATUS"
      ],
      "registersUsedMatchingBifield": [
        "CTM_STATUS"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_enableCounterResetInput",
      "functionArgs": [
        "base",
        "reset_event"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ERAD_Counter_Input_Event"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTM_CNTL"
      ],
      "registersUsedMatchingBifield": [
        "CTM_CNTL"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_disableCounterResetInput",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTM_CNTL"
      ],
      "registersUsedMatchingBifield": [
        "CTM_CNTL"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_clearCounterEvent",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTM_CLEAR"
      ],
      "registersUsedMatchingBifield": [
        "CTM_CLEAR"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_clearCounterOverflow",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTM_CLEAR"
      ],
      "registersUsedMatchingBifield": [
        "CTM_CLEAR"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_getCurrentCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CTM_COUNT"
      ],
      "registersUsedMatchingBifield": [
        "CTM_COUNT"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_setCurrentCount",
      "functionArgs": [
        "base",
        "value"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTM_COUNT"
      ],
      "registersUsedMatchingBifield": [
        "CTM_COUNT"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_getMaxCount",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CTM_MAX_COUNT"
      ],
      "registersUsedMatchingBifield": [
        "CTM_MAX_COUNT"
      ]
    },
    {
      "file": "erad.h",
      "peripheral": "erad",
      "functionName": "ERAD_setMaxCount",
      "functionArgs": [
        "base",
        "value"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTM_MAX_COUNT"
      ],
      "registersUsedMatchingBifield": [
        "CTM_MAX_COUNT"
      ]
    }
  ]
}
module.exports = { 
  erad_driverlib: erad_driverlib,
}
