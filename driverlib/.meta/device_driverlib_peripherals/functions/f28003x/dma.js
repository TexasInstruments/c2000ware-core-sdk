let dma_driverlib = 
{
  "name": "dma",
  "functions": [
    {
      "file": "dma.c",
      "peripheral": "dma",
      "functionName": "DMA_configAddresses",
      "functionArgs": [
        "base",
        "*destAddr",
        "*srcAddr"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constvoid",
        "constvoid"
      ],
      "returnType": "void",
      "registersUsed": [
        "SRC_BEG_ADDR_SHADOW",
        "SRC_ADDR_SHADOW",
        "DST_BEG_ADDR_SHADOW",
        "DST_ADDR_SHADOW"
      ],
      "registersUsedMatchingBifield": [
        "SRC_BEG_ADDR_SHADOW",
        "SRC_ADDR_SHADOW",
        "DST_BEG_ADDR_SHADOW",
        "DST_ADDR_SHADOW"
      ]
    },
    {
      "file": "dma.c",
      "peripheral": "dma",
      "functionName": "DMA_configBurst",
      "functionArgs": [
        "base",
        "size",
        "srcStep",
        "destStep"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "int16_t",
        "int16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "BURST_SIZE",
        "SRC_BURST_STEP",
        "DST_BURST_STEP"
      ],
      "registersUsedMatchingBifield": [
        "BURST_SIZE",
        "SRC_BURST_STEP",
        "DST_BURST_STEP"
      ]
    },
    {
      "file": "dma.c",
      "peripheral": "dma",
      "functionName": "DMA_configTransfer",
      "functionArgs": [
        "base",
        "transferSize",
        "srcStep",
        "destStep"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "int16_t",
        "int16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TRANSFER_SIZE",
        "SRC_TRANSFER_STEP",
        "DST_TRANSFER_STEP"
      ],
      "registersUsedMatchingBifield": [
        "TRANSFER_SIZE",
        "SRC_TRANSFER_STEP",
        "DST_TRANSFER_STEP"
      ]
    },
    {
      "file": "dma.c",
      "peripheral": "dma",
      "functionName": "DMA_configWrap",
      "functionArgs": [
        "base",
        "srcWrapSize",
        "srcStep",
        "destWrapSize",
        "destStep"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "int16_t",
        "uint32_t",
        "int16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "SRC_WRAP_SIZE",
        "SRC_WRAP_STEP",
        "DST_WRAP_SIZE",
        "DST_WRAP_STEP"
      ],
      "registersUsedMatchingBifield": [
        "SRC_WRAP_SIZE",
        "SRC_WRAP_STEP",
        "DST_WRAP_SIZE",
        "DST_WRAP_STEP"
      ]
    },
    {
      "file": "dma.c",
      "peripheral": "dma",
      "functionName": "DMA_configMode",
      "functionArgs": [
        "base",
        "trigger",
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "DMA_Trigger",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "MODE",
        "DMACHSRCSEL1",
        "DMACHSRCSEL2"
      ],
      "registersUsedMatchingBifield": [
        "MODE",
        "DMACHSRCSEL1",
        "DMACHSRCSEL2"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_isBaseValid",
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
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_initController",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTRL"
      ],
      "registersUsedMatchingBifield": [
        "CTRL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_triggerSoftReset",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_setEmulationMode",
      "functionArgs": [
        "mode"
      ],
      "functionArgsTypes": [
        "DMA_EmulationMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DEBUGCTRL"
      ],
      "registersUsedMatchingBifield": [
        "DEBUGCTRL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_enableTrigger",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MODE"
      ],
      "registersUsedMatchingBifield": [
        "MODE"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_disableTrigger",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MODE"
      ],
      "registersUsedMatchingBifield": [
        "MODE"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_forceTrigger",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_clearTriggerFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_getTransferStatusFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_getBurstStatusFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_getRunStatusFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_getOverflowFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_getTriggerFlagStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_startChannel",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_stopChannel",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_enableInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MODE"
      ],
      "registersUsedMatchingBifield": [
        "MODE"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_disableInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MODE"
      ],
      "registersUsedMatchingBifield": [
        "MODE"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_enableOverrunInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MODE"
      ],
      "registersUsedMatchingBifield": [
        "MODE"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_disableOverrunInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MODE"
      ],
      "registersUsedMatchingBifield": [
        "MODE"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_clearErrorFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CONTROL"
      ],
      "registersUsedMatchingBifield": [
        "CONTROL"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_setInterruptMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "DMA_InterruptMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MODE"
      ],
      "registersUsedMatchingBifield": [
        "MODE"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_setPriorityMode",
      "functionArgs": [
        "ch1IsHighPri"
      ],
      "functionArgsTypes": [
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PRIORITYCTRL1"
      ],
      "registersUsedMatchingBifield": [
        "PRIORITYCTRL1"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_configSourceAddress",
      "functionArgs": [
        "base",
        "*srcAddr"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constvoid"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SRC_BEG_ADDR_SHADOW",
        "SRC_ADDR_SHADOW"
      ],
      "registersUsedMatchingBifield": [
        "SRC_BEG_ADDR_SHADOW",
        "SRC_ADDR_SHADOW"
      ]
    },
    {
      "file": "dma.h",
      "peripheral": "dma",
      "functionName": "DMA_configDestAddress",
      "functionArgs": [
        "base",
        "*destAddr"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constvoid"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DST_BEG_ADDR_SHADOW",
        "DST_ADDR_SHADOW"
      ],
      "registersUsedMatchingBifield": [
        "DST_BEG_ADDR_SHADOW",
        "DST_ADDR_SHADOW"
      ]
    }
  ]
}
module.exports = { 
  dma_driverlib: dma_driverlib,
}
