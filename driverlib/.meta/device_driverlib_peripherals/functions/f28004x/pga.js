let pga_driverlib = 
{
  "name": "pga",
  "functions": [
    {
      "file": "pga.h",
      "peripheral": "pga",
      "functionName": "PGA_isBaseValid",
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
      "file": "pga.h",
      "peripheral": "pga",
      "functionName": "PGA_enable",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "PGACTL"
      ]
    },
    {
      "file": "pga.h",
      "peripheral": "pga",
      "functionName": "PGA_disable",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "PGACTL"
      ]
    },
    {
      "file": "pga.h",
      "peripheral": "pga",
      "functionName": "PGA_setGain",
      "functionArgs": [
        "base",
        "gainValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "PGA_GainValue"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "PGACTL"
      ]
    },
    {
      "file": "pga.h",
      "peripheral": "pga",
      "functionName": "PGA_setFilterResistor",
      "functionArgs": [
        "base",
        "resistorValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "PGA_LowPassResistorValue"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL"
      ],
      "registersUsedMatchingBifield": [
        "PGACTL"
      ]
    },
    {
      "file": "pga.h",
      "peripheral": "pga",
      "functionName": "PGA_getPGARevision",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TYPE"
      ],
      "registersUsedMatchingBifield": [
        "PGATYPE"
      ]
    },
    {
      "file": "pga.h",
      "peripheral": "pga",
      "functionName": "PGA_getPGAType",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "TYPE"
      ],
      "registersUsedMatchingBifield": [
        "PGATYPE"
      ]
    },
    {
      "file": "pga.h",
      "peripheral": "pga",
      "functionName": "PGA_lockRegisters",
      "functionArgs": [
        "base",
        "registerType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOCK"
      ],
      "registersUsedMatchingBifield": [
        "PGALOCK"
      ]
    }
  ]
}
module.exports = { 
  pga_driverlib: pga_driverlib,
}
