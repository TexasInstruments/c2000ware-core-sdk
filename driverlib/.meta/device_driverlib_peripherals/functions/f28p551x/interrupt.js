let interrupt_driverlib = 
{
  "name": "interrupt",
  "functions": [
    {
      "file": "interrupt.c",
      "peripheral": "interrupt",
      "functionName": "Interrupt_clearIFR",
      "functionArgs": [
        "group"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "interrupt.c",
      "peripheral": "interrupt",
      "functionName": "Interrupt_initModule",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "void",
      "registersUsed": [
        "CTRL",
        "IER1",
        "IFR1",
        "IER2",
        "IFR2",
        "IER3",
        "IFR3",
        "IER4",
        "IFR4",
        "IER5",
        "IFR5",
        "IER6",
        "IFR6",
        "IER7",
        "IFR7",
        "IER8",
        "IFR8",
        "IER9",
        "IFR9",
        "IER10",
        "IFR10",
        "IER11",
        "IFR11",
        "IER12",
        "IFR12"
      ],
      "registersUsedMatchingBifield": [
        "CTRL",
        "IER1",
        "IFR1",
        "IER2",
        "IFR2",
        "IER3",
        "IFR3",
        "IER4",
        "IFR4",
        "IER5",
        "IFR5",
        "IER6",
        "IFR6",
        "IER7",
        "IFR7",
        "IER8",
        "IFR8",
        "IER9",
        "IFR9",
        "IER10",
        "IFR10",
        "IER11",
        "IFR11",
        "IER12",
        "IFR12"
      ]
    },
    {
      "file": "interrupt.c",
      "peripheral": "interrupt",
      "functionName": "Interrupt_initVectorTable",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "interrupt.c",
      "peripheral": "interrupt",
      "functionName": "Interrupt_enable",
      "functionArgs": [
        "interruptNumber"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IER1"
      ],
      "registersUsedMatchingBifield": [
        "IER1"
      ]
    },
    {
      "file": "interrupt.c",
      "peripheral": "interrupt",
      "functionName": "Interrupt_disable",
      "functionArgs": [
        "interruptNumber"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "ACK",
        "IER1"
      ],
      "registersUsedMatchingBifield": [
        "ACK",
        "IER1"
      ]
    },
    {
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_defaultHandler",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static void",
      "registersUsed": [
        "CTRL"
      ],
      "registersUsedMatchingBifield": [
        "CTRL"
      ]
    },
    {
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_illegalOperationHandler",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_nmiHandler",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_enableMaster",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_disableMaster",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_register",
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
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_unregister",
      "functionArgs": [
        "interruptNumber"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_enableInCPU",
      "functionArgs": [
        "cpuInterrupt"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_disableInCPU",
      "functionArgs": [
        "cpuInterrupt"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_clearACKGroup",
      "functionArgs": [
        "group"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ACK"
      ],
      "registersUsedMatchingBifield": [
        "ACK"
      ]
    },
    {
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_enablePIE",
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
      "file": "interrupt.h",
      "peripheral": "interrupt",
      "functionName": "Interrupt_disablePIE",
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
    }
  ]
}
module.exports = { 
  interrupt_driverlib: interrupt_driverlib,
}
