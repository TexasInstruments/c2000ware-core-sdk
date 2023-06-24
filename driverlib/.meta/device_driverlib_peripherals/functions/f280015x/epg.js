let epg_driverlib = 
{
  "name": "epg",
  "functions": [
    {
      "file": "epg.c",
      "peripheral": "epg",
      "functionName": "EPG_selectEPGDataOut",
      "functionArgs": [
        "muxbase",
        "dataIn",
        "dataOutSel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_DataIn",
        "EPG_DataOutSel"
      ],
      "returnType": "void",
      "registersUsed": [
        "MXSEL0",
        "MXSEL1"
      ],
      "registersUsedMatchingBifield": [
        "MXSEL0",
        "MXSEL1"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_isBaseValid",
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
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_isMUXBaseValid",
      "functionArgs": [
        "muxbase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef DEBUG  static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_enableGlobal",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTL0"
      ],
      "registersUsedMatchingBifield": [
        "GCTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_disableGlobal",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTL0"
      ],
      "registersUsedMatchingBifield": [
        "GCTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_selectEPGOutput",
      "functionArgs": [
        "base",
        "gPinNum",
        "gPinOutSel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_OUT",
        "EPG_OutputSelect"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTL0"
      ],
      "registersUsedMatchingBifield": [
        "GCTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_selectSignalOutput",
      "functionArgs": [
        "base",
        "gPinNum",
        "sigGenOutput"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_OUT",
        "EPG_SignalGenOut"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTL3"
      ],
      "registersUsedMatchingBifield": [
        "GCTL3"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_selectClkOutput",
      "functionArgs": [
        "base",
        "gPinNum",
        "clkGenOutput"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_OUT",
        "EPG_ClockGenOut"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTL2"
      ],
      "registersUsedMatchingBifield": [
        "GCTL2"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_selectSigGenClkSource",
      "functionArgs": [
        "base",
        "sigGenNum",
        "clkGenOutput"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN",
        "EPG_ClockGenGclkOut"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GCTL1"
      ],
      "registersUsedMatchingBifield": [
        "GCTL1"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_setClkGenPeriod",
      "functionArgs": [
        "base",
        "clkGenNum",
        "periodValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_CLKGEN",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLKDIV0_CTL0",
        "CLKDIV1_CTL0"
      ],
      "registersUsedMatchingBifield": [
        "CLKDIV0_CTL0",
        "CLKDIV1_CTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_setClkGenStopEdge",
      "functionArgs": [
        "base",
        "clkGenNum",
        "stopEdge"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_CLKGEN",
        "EPG_ClockStopEdge"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLKDIV0_CTL0",
        "CLKDIV1_CTL0"
      ],
      "registersUsedMatchingBifield": [
        "CLKDIV0_CTL0",
        "CLKDIV1_CTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_setClkGenOffset",
      "functionArgs": [
        "base",
        "clkGenNum",
        "clkGenOutputNum",
        "offsetValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_CLKGEN",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLKDIV0_CLKOFFSET",
        "CLKDIV1_CLKOFFSET"
      ],
      "registersUsedMatchingBifield": [
        "CLKDIV0_CLKOFFSET",
        "CLKDIV1_CLKOFFSET"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_enableSignalGen",
      "functionArgs": [
        "base",
        "sigGenNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_CTL0"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_CTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_disableSignalGen",
      "functionArgs": [
        "base",
        "sigGenNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_CTL0"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_CTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_setSignalGenMode",
      "functionArgs": [
        "base",
        "sigGenNum",
        "sigGenMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN",
        "EPG_SignalGenMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_CTL0"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_CTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_enableBitRevOnDataIn",
      "functionArgs": [
        "base",
        "sigGenNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_CTL0"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_CTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_disableBitRevOnDataIn",
      "functionArgs": [
        "base",
        "sigGenNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_CTL0"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_CTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_enableBitRevOnDataOut",
      "functionArgs": [
        "base",
        "sigGenNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_CTL0"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_CTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_disableBitRevOnDataOut",
      "functionArgs": [
        "base",
        "sigGenNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_CTL0"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_CTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_setDataBitLen",
      "functionArgs": [
        "base",
        "sigGenNum",
        "bitLength"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_CTL0"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_CTL0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_setData0In",
      "functionArgs": [
        "base",
        "sigGenNum",
        "data0Input"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN",
        "EPG_SignalGenData0In"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_CTL1"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_CTL1"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_setData63In",
      "functionArgs": [
        "base",
        "sigGenNum",
        "data63Input"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN",
        "EPG_SignalGenData63In"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_CTL1"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_CTL1"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_setData0Word",
      "functionArgs": [
        "base",
        "sigGenNum",
        "data0"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_DATA0"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_DATA0"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_setData1Word",
      "functionArgs": [
        "base",
        "sigGenNum",
        "data1"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIGGEN0_DATA1"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_DATA1"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_getData0ActiveReg",
      "functionArgs": [
        "base",
        "sigGenNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "SIGGEN0_DATA0",
        "SIGGEN0_DATA0_ACTIVE"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_DATA0",
        "SIGGEN0_DATA0_ACTIVE"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_getData1ActiveReg",
      "functionArgs": [
        "base",
        "sigGenNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "EPG_SIGGEN"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "SIGGEN0_DATA1",
        "SIGGEN0_DATA1_ACTIVE"
      ],
      "registersUsedMatchingBifield": [
        "SIGGEN0_DATA1",
        "SIGGEN0_DATA1_ACTIVE"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_enableInterruptFlag",
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
        "GINTEN"
      ],
      "registersUsedMatchingBifield": [
        "GINTEN"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_disableInterruptFlag",
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
        "GINTEN"
      ],
      "registersUsedMatchingBifield": [
        "GINTEN"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_getInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "GINTSTS"
      ],
      "registersUsedMatchingBifield": [
        "GINTSTS"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_clearInterruptFlag",
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
        "GINTCLR"
      ],
      "registersUsedMatchingBifield": [
        "GINTCLR"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_forceInterruptFlag",
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
        "GINTFRC"
      ],
      "registersUsedMatchingBifield": [
        "GINTFRC"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_lockReg",
      "functionArgs": [
        "base",
        "regFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
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
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_releaseLockReg",
      "functionArgs": [
        "base",
        "regFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
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
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_commitRegLock",
      "functionArgs": [
        "base",
        "regFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "COMMIT"
      ],
      "registersUsedMatchingBifield": [
        "COMMIT"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_lockMXSelReg",
      "functionArgs": [
        "muxbase",
        "regFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MXSELLOCK"
      ],
      "registersUsedMatchingBifield": [
        "MXSELLOCK"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_releaseLockMXSelReg",
      "functionArgs": [
        "muxbase",
        "regFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MXSELLOCK"
      ],
      "registersUsedMatchingBifield": [
        "MXSELLOCK"
      ]
    },
    {
      "file": "epg.h",
      "peripheral": "epg",
      "functionName": "EPG_commitMXSelRegLock",
      "functionArgs": [
        "muxbase",
        "regFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MXSELCOMMIT"
      ],
      "registersUsedMatchingBifield": [
        "MXSELCOMMIT"
      ]
    }
  ]
}
module.exports = { 
  epg_driverlib: epg_driverlib,
}
