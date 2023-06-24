let i2c_driverlib = 
{
  "name": "i2c",
  "functions": [
    {
      "file": "i2c.c",
      "peripheral": "i2c",
      "functionName": "I2C_initMaster",
      "functionArgs": [
        "base",
        "sysclkHz",
        "bitRate",
        "dutyCycle"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "I2C_DutyCycle"
      ],
      "returnType": "void",
      "registersUsed": [
        "CLKL",
        "CLKH",
        "PSC"
      ],
      "registersUsedMatchingBifield": [
        "CLKL",
        "CLKH",
        "PSC"
      ]
    },
    {
      "file": "i2c.c",
      "peripheral": "i2c",
      "functionName": "I2C_enableInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IER",
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "IER",
        "FFTX",
        "FFRX"
      ]
    },
    {
      "file": "i2c.c",
      "peripheral": "i2c",
      "functionName": "I2C_disableInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IER",
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "IER",
        "FFTX",
        "FFRX"
      ]
    },
    {
      "file": "i2c.c",
      "peripheral": "i2c",
      "functionName": "I2C_getInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "STR",
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "STR",
        "FFTX",
        "FFRX"
      ]
    },
    {
      "file": "i2c.c",
      "peripheral": "i2c",
      "functionName": "I2C_clearInterruptStatus",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "STR",
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "STR",
        "FFTX",
        "FFRX"
      ]
    },
    {
      "file": "i2c.c",
      "peripheral": "i2c",
      "functionName": "I2C_configureModuleFrequency",
      "functionArgs": [
        "base",
        "sysclkHz"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "PSC"
      ],
      "registersUsedMatchingBifield": [
        "PSC"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_isBaseValid",
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
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_enableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_disableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_enableFIFO",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "FFTX",
        "FFRX"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_disableFIFO",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "FFTX",
        "FFRX"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_setFIFOInterruptLevel",
      "functionArgs": [
        "base",
        "txLevel",
        "rxLevel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "I2C_TxFIFOLevel",
        "I2C_RxFIFOLevel"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "FFTX",
        "FFRX"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_getFIFOInterruptLevel",
      "functionArgs": [
        "base",
        "*txLevel",
        "*rxLevel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "I2C_TxFIFOLevel",
        "I2C_RxFIFOLevel"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "FFTX",
        "FFRX"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_getTxFIFOStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline I2C_TxFIFOLevel",
      "registersUsed": [
        "FFTX"
      ],
      "registersUsedMatchingBifield": [
        "FFTX"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_getRxFIFOStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline I2C_RxFIFOLevel",
      "registersUsed": [
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "FFRX"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_getPreScaler",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "PSC"
      ],
      "registersUsedMatchingBifield": [
        "PSC"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_setSlaveAddress",
      "functionArgs": [
        "base",
        "slaveAddr"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SAR"
      ],
      "registersUsedMatchingBifield": [
        "SAR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_setOwnSlaveAddress",
      "functionArgs": [
        "base",
        "slaveAddr"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OAR"
      ],
      "registersUsedMatchingBifield": [
        "OAR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_isBusBusy",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "STR"
      ],
      "registersUsedMatchingBifield": [
        "STR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_getStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "STR"
      ],
      "registersUsedMatchingBifield": [
        "STR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_clearStatus",
      "functionArgs": [
        "base",
        "stsFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "STR"
      ],
      "registersUsedMatchingBifield": [
        "STR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_setConfig",
      "functionArgs": [
        "base",
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_setBitCount",
      "functionArgs": [
        "base",
        "size"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "I2C_BitCount"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_sendStartCondition",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_sendStopCondition",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_sendNACK",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_getData",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "DRR"
      ],
      "registersUsedMatchingBifield": [
        "DRR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_putData",
      "functionArgs": [
        "base",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DXR"
      ],
      "registersUsedMatchingBifield": [
        "DXR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_getStopConditionStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_setDataCount",
      "functionArgs": [
        "base",
        "count"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CNT"
      ],
      "registersUsedMatchingBifield": [
        "CNT"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_setAddressMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "I2C_AddressMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_setEmulationMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "I2C_EmulationMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_enableLoopback",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_disableLoopback",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MDR"
      ],
      "registersUsedMatchingBifield": [
        "MDR"
      ]
    },
    {
      "file": "i2c.h",
      "peripheral": "i2c",
      "functionName": "I2C_getInterruptSource",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline I2C_InterruptSource",
      "registersUsed": [
        "ISRC"
      ],
      "registersUsedMatchingBifield": [
        "ISRC"
      ]
    }
  ]
}
module.exports = { 
  i2c_driverlib: i2c_driverlib,
}
