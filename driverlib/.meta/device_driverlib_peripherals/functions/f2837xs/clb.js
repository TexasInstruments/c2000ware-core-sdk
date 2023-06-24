let clb_driverlib = 
{
  "name": "clb",
  "functions": [
    {
      "file": "clb.c",
      "peripheral": "clb",
      "functionName": "CLB_configCounterLoadMatch",
      "functionArgs": [
        "base",
        "counterID",
        "load",
        "match1",
        "match2"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLB_Counters",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "clb.c",
      "peripheral": "clb",
      "functionName": "CLB_clearFIFOs",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "BUF_PTR",
        "PULL"
      ],
      "registersUsedMatchingBifield": [
        "BUF_PTR",
        "PULL"
      ]
    },
    {
      "file": "clb.c",
      "peripheral": "clb",
      "functionName": "CLB_writeFIFOs",
      "functionArgs": [
        "",
        "pullData[]"
      ],
      "functionArgsTypes": [
        "uint32_tbase",
        "constuint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "PULL"
      ],
      "registersUsedMatchingBifield": [
        "PULL"
      ]
    },
    {
      "file": "clb.c",
      "peripheral": "clb",
      "functionName": "CLB_readFIFOs",
      "functionArgs": [
        "",
        "pushData[]"
      ],
      "functionArgsTypes": [
        "uint32_tbase",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "PUSH"
      ],
      "registersUsedMatchingBifield": [
        "PUSH"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_isBaseValid",
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
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_isAddressValid",
      "functionArgs": [
        "address"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_enableCLB",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOAD_EN"
      ],
      "registersUsedMatchingBifield": [
        "LOAD_EN"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_disableCLB",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOAD_EN"
      ],
      "registersUsedMatchingBifield": [
        "LOAD_EN"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_enableLock",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
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
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_writeInterface",
      "functionArgs": [
        "base",
        "address",
        "value"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOAD_EN",
        "LOAD_ADDR",
        "LOAD_DATA"
      ],
      "registersUsedMatchingBifield": [
        "LOAD_EN",
        "LOAD_ADDR",
        "LOAD_DATA"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_selectInputFilter",
      "functionArgs": [
        "base",
        "inID",
        "filterType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLB_Inputs",
        "CLB_FilterType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INPUT_FILTER"
      ],
      "registersUsedMatchingBifield": [
        "INPUT_FILTER"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_enableSynchronization",
      "functionArgs": [
        "base",
        "inID"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLB_Inputs"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INPUT_FILTER"
      ],
      "registersUsedMatchingBifield": [
        "INPUT_FILTER"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_disableSynchronization",
      "functionArgs": [
        "base",
        "inID"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLB_Inputs"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INPUT_FILTER"
      ],
      "registersUsedMatchingBifield": [
        "INPUT_FILTER"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_configGPInputMux",
      "functionArgs": [
        "base",
        "inID",
        "gpMuxCfg"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLB_Inputs",
        "CLB_GPInputMux"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IN_MUX_SEL_0"
      ],
      "registersUsedMatchingBifield": [
        "IN_MUX_SEL_0"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_setGPREG",
      "functionArgs": [
        "base",
        "gpRegVal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GP_REG"
      ],
      "registersUsedMatchingBifield": [
        "GP_REG"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_getGPREG",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "GP_REG"
      ],
      "registersUsedMatchingBifield": [
        "GP_REG"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_configLocalInputMux",
      "functionArgs": [
        "base",
        "inID",
        "localMuxCfg"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLB_Inputs",
        "CLB_LocalInputMux"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LCL_MUX_SEL_1",
        "LCL_MUX_SEL_2"
      ],
      "registersUsedMatchingBifield": [
        "LCL_MUX_SEL_1",
        "LCL_MUX_SEL_2"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_configGlobalInputMux",
      "functionArgs": [
        "base",
        "inID",
        "globalMuxCfg"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLB_Inputs",
        "CLB_GlobalInputMux"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GLBL_MUX_SEL_1",
        "GLBL_MUX_SEL_2"
      ],
      "registersUsedMatchingBifield": [
        "GLBL_MUX_SEL_1",
        "GLBL_MUX_SEL_2"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_setOutputMask",
      "functionArgs": [
        "base",
        "",
        "enable"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_toutputMask",
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OUT_EN"
      ],
      "registersUsedMatchingBifield": [
        "OUT_EN"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_getInterruptTag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "INTR_TAG_REG"
      ],
      "registersUsedMatchingBifield": [
        "INTR_TAG_REG"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_clearInterruptTag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTR_TAG_REG"
      ],
      "registersUsedMatchingBifield": [
        "INTR_TAG_REG"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_selectLUT4Inputs",
      "functionArgs": [
        "base",
        "lut4In0",
        "lut4In1",
        "lut4In2",
        "lut4In3"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LUT4_IN0",
        "LUT4_IN1",
        "LUT4_IN2",
        "LUT4_IN3"
      ],
      "registersUsedMatchingBifield": [
        "LUT4_IN0",
        "LUT4_IN1",
        "LUT4_IN2",
        "LUT4_IN3"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_configLUT4Function",
      "functionArgs": [
        "base",
        "lut4Fn10",
        "lut4Fn2"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LUT4_FN1_0",
        "LUT4_FN2"
      ],
      "registersUsedMatchingBifield": [
        "LUT4_FN1_0",
        "LUT4_FN2"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_selectFSMInputs",
      "functionArgs": [
        "base",
        "external0",
        "external1",
        "extra0",
        "extra1"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FSM_EXTRA_IN0",
        "FSM_EXTERNAL_IN0",
        "FSM_EXTERNAL_IN1",
        "FSM_EXTRA_IN1"
      ],
      "registersUsedMatchingBifield": [
        "FSM_EXTRA_IN0",
        "FSM_EXTERNAL_IN0",
        "FSM_EXTERNAL_IN1",
        "FSM_EXTRA_IN1"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_configFSMLUTFunction",
      "functionArgs": [
        "base",
        "fsmLutFn10",
        "fsmLutFn2"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FSM_LUT_FN1_0",
        "FSM_LUT_FN2"
      ],
      "registersUsedMatchingBifield": [
        "FSM_LUT_FN1_0",
        "FSM_LUT_FN2"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_configFSMNextState",
      "functionArgs": [
        "base",
        "nextState0",
        "nextState1",
        "nextState2"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FSM_NEXT_STATE_0",
        "FSM_NEXT_STATE_1",
        "FSM_NEXT_STATE_2"
      ],
      "registersUsedMatchingBifield": [
        "FSM_NEXT_STATE_0",
        "FSM_NEXT_STATE_1",
        "FSM_NEXT_STATE_2"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_selectCounterInputs",
      "functionArgs": [
        "base",
        "reset",
        "event",
        "mode0",
        "mode1"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COUNT_RESET",
        "COUNT_MODE_1",
        "COUNT_MODE_0",
        "COUNT_EVENT"
      ],
      "registersUsedMatchingBifield": [
        "COUNT_RESET",
        "COUNT_MODE_1",
        "COUNT_MODE_0",
        "COUNT_EVENT"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_configMiscCtrlModes",
      "functionArgs": [
        "base",
        "miscCtrl"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MISC_CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "MISC_CONTROL"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_configOutputLUT",
      "functionArgs": [
        "base",
        "outID",
        "outputCfg"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLB_Outputs",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OUTPUT_LUT_0",
        "OUTPUT_LUT_1",
        "OUTPUT_LUT_2",
        "OUTPUT_LUT_3",
        "OUTPUT_LUT_4",
        "OUTPUT_LUT_5",
        "OUTPUT_LUT_6",
        "OUTPUT_LUT_7"
      ],
      "registersUsedMatchingBifield": [
        "OUTPUT_LUT_0",
        "OUTPUT_LUT_1",
        "OUTPUT_LUT_2",
        "OUTPUT_LUT_3",
        "OUTPUT_LUT_4",
        "OUTPUT_LUT_5",
        "OUTPUT_LUT_6",
        "OUTPUT_LUT_7"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_configHLCEventSelect",
      "functionArgs": [
        "base",
        "eventSel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HLC_EVENT_SEL"
      ],
      "registersUsedMatchingBifield": [
        "HLC_EVENT_SEL"
      ]
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_programHLCInstruction",
      "functionArgs": [
        "base",
        "instructionNum",
        "instruction"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_setHLCRegisters",
      "functionArgs": [
        "base",
        "r0Init",
        "r1Init",
        "r2Init",
        "r3Init"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_getRegister",
      "functionArgs": [
        "base",
        "registerID"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLB_Register"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "clb.h",
      "peripheral": "clb",
      "functionName": "CLB_getOutputStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "DBG_OUT"
      ],
      "registersUsedMatchingBifield": [
        "DBG_OUT"
      ]
    }
  ]
}
module.exports = { 
  clb_driverlib: clb_driverlib,
}
