let asysctl_driverlib = 
{
  "name": "asysctl",
  "functions": [
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_enableTemperatureSensor",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TSNSCTL"
      ],
      "registersUsedMatchingBifield": [
        "TSNSCTL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_disableTemperatureSensor",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TSNSCTL"
      ],
      "registersUsedMatchingBifield": [
        "TSNSCTL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_setAnalogReferenceInternal",
      "functionArgs": [
        "reference"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ANAREFCTL"
      ],
      "registersUsedMatchingBifield": [
        "ANAREFCTL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_setAnalogReferenceExternal",
      "functionArgs": [
        "reference"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ANAREFCTL"
      ],
      "registersUsedMatchingBifield": [
        "ANAREFCTL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_setAnalogReference2P5",
      "functionArgs": [
        "reference"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ANAREFCTL"
      ],
      "registersUsedMatchingBifield": [
        "ANAREFCTL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_setAnalogReference1P65",
      "functionArgs": [
        "reference"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ANAREFCTL"
      ],
      "registersUsedMatchingBifield": [
        "ANAREFCTL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_selectCMPHNMux",
      "functionArgs": [
        "select"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMPHNMXSEL"
      ],
      "registersUsedMatchingBifield": [
        "CMPHNMXSEL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_selectCMPHNMuxValue",
      "functionArgs": [
        "select",
        "value"
      ],
      "functionArgsTypes": [
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMPHNMXSEL"
      ],
      "registersUsedMatchingBifield": [
        "CMPHNMXSEL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_selectCMPLNMux",
      "functionArgs": [
        "select"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMPLNMXSEL"
      ],
      "registersUsedMatchingBifield": [
        "CMPLNMXSEL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_selectCMPLNMuxValue",
      "functionArgs": [
        "select",
        "value"
      ],
      "functionArgsTypes": [
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMPLNMXSEL"
      ],
      "registersUsedMatchingBifield": [
        "CMPLNMXSEL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_selectCMPHPMux",
      "functionArgs": [
        "select",
        "value"
      ],
      "functionArgsTypes": [
        "ASysCtl_CMPHPMuxSelect",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMPHPMXSEL"
      ],
      "registersUsedMatchingBifield": [
        "CMPHPMXSEL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_selectCMPLPMux",
      "functionArgs": [
        "select",
        "value"
      ],
      "functionArgsTypes": [
        "ASysCtl_CMPLPMuxSelect",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMPLPMXSEL"
      ],
      "registersUsedMatchingBifield": [
        "CMPLPMXSEL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_lockTemperatureSensor",
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
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_lockANAREF",
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
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_lockVMON",
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
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_lockCMPHPMux",
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
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_lockCMPLPMux",
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
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_lockCMPHNMux",
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
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_lockCMPLNMux",
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
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_lockVREG",
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
    }
  ]
}
module.exports = { 
  asysctl_driverlib: asysctl_driverlib,
}
