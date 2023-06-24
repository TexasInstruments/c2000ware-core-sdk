let xbar_driverlib = 
{
  "name": "xbar",
  "functions": [
    {
      "file": "xbar.c",
      "peripheral": "xbar",
      "functionName": "XBAR_setOutputMuxConfig",
      "functionArgs": [
        "output",
        "muxConfig"
      ],
      "functionArgsTypes": [
        "XBAR_OutputNum",
        "XBAR_OutputMuxConfig"
      ],
      "returnType": "void",
      "registersUsed": [
        "OUTPUT1MUX0TO15CFG",
        "OUTPUT1MUX16TO31CFG"
      ],
      "registersUsedMatchingBifield": [
        "OUTPUT1MUX0TO15CFG",
        "OUTPUT1MUX16TO31CFG"
      ]
    },
    {
      "file": "xbar.c",
      "peripheral": "xbar",
      "functionName": "XBAR_setEPWMMuxConfig",
      "functionArgs": [
        "trip",
        "muxConfig"
      ],
      "functionArgsTypes": [
        "XBAR_TripNum",
        "XBAR_EPWMMuxConfig"
      ],
      "returnType": "void",
      "registersUsed": [
        "TRIP4MUX0TO15CFG",
        "TRIP4MUX16TO31CFG"
      ],
      "registersUsedMatchingBifield": [
        "TRIP4MUX0TO15CFG",
        "TRIP4MUX16TO31CFG"
      ]
    },
    {
      "file": "xbar.c",
      "peripheral": "xbar",
      "functionName": "XBAR_setCLBMuxConfig",
      "functionArgs": [
        "auxSignal",
        "muxConfig"
      ],
      "functionArgsTypes": [
        "XBAR_AuxSigNum",
        "XBAR_CLBMuxConfig"
      ],
      "returnType": "void",
      "registersUsed": [
        "AUXSIG0MUX0TO15CFG",
        "AUXSIG0MUX16TO31CFG"
      ],
      "registersUsedMatchingBifield": [
        "AUXSIG0MUX0TO15CFG",
        "AUXSIG0MUX16TO31CFG"
      ]
    },
    {
      "file": "xbar.c",
      "peripheral": "xbar",
      "functionName": "XBAR_getInputFlagStatus",
      "functionArgs": [
        "inputFlag"
      ],
      "functionArgsTypes": [
        "XBAR_InputFlag"
      ],
      "returnType": "bool",
      "registersUsed": [
        "FLG1",
        "FLG2",
        "FLG3",
        "FLG4"
      ],
      "registersUsedMatchingBifield": [
        "FLG1",
        "FLG2",
        "FLG3",
        "FLG4"
      ]
    },
    {
      "file": "xbar.c",
      "peripheral": "xbar",
      "functionName": "XBAR_clearInputFlag",
      "functionArgs": [
        "inputFlag"
      ],
      "functionArgsTypes": [
        "XBAR_InputFlag"
      ],
      "returnType": "void",
      "registersUsed": [
        "CLR1",
        "CLR2",
        "CLR3",
        "CLR4"
      ],
      "registersUsedMatchingBifield": [
        "CLR1",
        "CLR2",
        "CLR3",
        "CLR4"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_enableOutputMux",
      "functionArgs": [
        "output",
        "muxes"
      ],
      "functionArgsTypes": [
        "XBAR_OutputNum",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OUTPUT1MUXENABLE"
      ],
      "registersUsedMatchingBifield": [
        "OUTPUT1MUXENABLE"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_disableOutputMux",
      "functionArgs": [
        "output",
        "muxes"
      ],
      "functionArgsTypes": [
        "XBAR_OutputNum",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OUTPUT1MUXENABLE"
      ],
      "registersUsedMatchingBifield": [
        "OUTPUT1MUXENABLE"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_setOutputLatchMode",
      "functionArgs": [
        "output",
        "enable"
      ],
      "functionArgsTypes": [
        "XBAR_OutputNum",
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OUTPUTLATCH",
        "OUTPUTLATCHENABLE"
      ],
      "registersUsedMatchingBifield": [
        "OUTPUTLATCH",
        "OUTPUTLATCHENABLE"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_getOutputLatchStatus",
      "functionArgs": [
        "output"
      ],
      "functionArgsTypes": [
        "XBAR_OutputNum"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "OUTPUTLATCH"
      ],
      "registersUsedMatchingBifield": [
        "OUTPUTLATCH"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_clearOutputLatch",
      "functionArgs": [
        "output"
      ],
      "functionArgsTypes": [
        "XBAR_OutputNum"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OUTPUTLATCH",
        "OUTPUTLATCHCLR"
      ],
      "registersUsedMatchingBifield": [
        "OUTPUTLATCH",
        "OUTPUTLATCHCLR"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_forceOutputLatch",
      "functionArgs": [
        "output"
      ],
      "functionArgsTypes": [
        "XBAR_OutputNum"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OUTPUTLATCH",
        "OUTPUTLATCHFRC"
      ],
      "registersUsedMatchingBifield": [
        "OUTPUTLATCH",
        "OUTPUTLATCHFRC"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_invertOutputSignal",
      "functionArgs": [
        "output",
        "invert"
      ],
      "functionArgsTypes": [
        "XBAR_OutputNum",
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OUTPUTINV"
      ],
      "registersUsedMatchingBifield": [
        "OUTPUTINV"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_enableEPWMMux",
      "functionArgs": [
        "trip",
        "muxes"
      ],
      "functionArgsTypes": [
        "XBAR_TripNum",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TRIP4MUXENABLE"
      ],
      "registersUsedMatchingBifield": [
        "TRIP4MUXENABLE"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_disableEPWMMux",
      "functionArgs": [
        "trip",
        "muxes"
      ],
      "functionArgsTypes": [
        "XBAR_TripNum",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TRIP4MUXENABLE"
      ],
      "registersUsedMatchingBifield": [
        "TRIP4MUXENABLE"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_invertEPWMSignal",
      "functionArgs": [
        "trip",
        "invert"
      ],
      "functionArgsTypes": [
        "XBAR_TripNum",
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TRIPOUTINV"
      ],
      "registersUsedMatchingBifield": [
        "TRIPOUTINV"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_setInputPin",
      "functionArgs": [
        "input",
        "pin"
      ],
      "functionArgsTypes": [
        "XBAR_InputNum",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INPUT1SELECT"
      ],
      "registersUsedMatchingBifield": [
        "INPUT1SELECT"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_lockInput",
      "functionArgs": [
        "input"
      ],
      "functionArgsTypes": [
        "XBAR_InputNum"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INPUTSELECTLOCK"
      ],
      "registersUsedMatchingBifield": [
        "INPUTSELECTLOCK"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_lockOutput",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OUTPUTLOCK"
      ],
      "registersUsedMatchingBifield": [
        "OUTPUTLOCK"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_lockEPWM",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TRIPLOCK"
      ],
      "registersUsedMatchingBifield": [
        "TRIPLOCK"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_enableCLBMux",
      "functionArgs": [
        "auxSignal",
        "muxes"
      ],
      "functionArgsTypes": [
        "XBAR_AuxSigNum",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AUXSIG0MUXENABLE"
      ],
      "registersUsedMatchingBifield": [
        "AUXSIG0MUXENABLE"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_disableCLBMux",
      "functionArgs": [
        "auxSignal",
        "muxes"
      ],
      "functionArgsTypes": [
        "XBAR_AuxSigNum",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AUXSIG0MUXENABLE"
      ],
      "registersUsedMatchingBifield": [
        "AUXSIG0MUXENABLE"
      ]
    },
    {
      "file": "xbar.h",
      "peripheral": "xbar",
      "functionName": "XBAR_invertCLBSignal",
      "functionArgs": [
        "auxSignal",
        "invert"
      ],
      "functionArgsTypes": [
        "XBAR_AuxSigNum",
        "bool"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AUXSIGOUTINV"
      ],
      "registersUsedMatchingBifield": [
        "AUXSIGOUTINV"
      ]
    }
  ]
}
module.exports = { 
  xbar_driverlib: xbar_driverlib,
}
