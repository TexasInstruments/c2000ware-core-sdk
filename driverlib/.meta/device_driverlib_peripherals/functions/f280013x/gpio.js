let gpio_driverlib = 
{
  "name": "gpio",
  "functions": [
    {
      "file": "gpio.c",
      "peripheral": "gpio",
      "functionName": "GPIO_setDirectionMode",
      "functionArgs": [
        "pin",
        "pinIO"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "GPIO_Direction"
      ],
      "returnType": "void",
      "registersUsed": [
        "GPADIR",
        "GPBDIR",
        "GPHDIR"
      ],
      "registersUsedMatchingBifield": [
        "GPADIR",
        "GPBDIR",
        "GPHDIR"
      ]
    },
    {
      "file": "gpio.c",
      "peripheral": "gpio",
      "functionName": "GPIO_getDirectionMode",
      "functionArgs": [
        "pin"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "GPIO_Direction",
      "registersUsed": [
        "GPADIR",
        "GPBDIR",
        "GPHDIR"
      ],
      "registersUsedMatchingBifield": [
        "GPADIR",
        "GPBDIR",
        "GPHDIR"
      ]
    },
    {
      "file": "gpio.c",
      "peripheral": "gpio",
      "functionName": "GPIO_setInterruptPin",
      "functionArgs": [
        "pin",
        "extIntNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "GPIO_ExternalIntNum"
      ],
      "returnType": "void",
      "registersUsed": [
        "1CR"
      ],
      "registersUsedMatchingBifield": [
        "1CR"
      ]
    },
    {
      "file": "gpio.c",
      "peripheral": "gpio",
      "functionName": "GPIO_setPadConfig",
      "functionArgs": [
        "pin",
        "pinType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "GPAPUD",
        "GPBPUD",
        "GPHPUD",
        "GPAINV",
        "GPBINV",
        "GPHINV",
        "GPAODR",
        "GPBODR",
        "GPHODR"
      ],
      "registersUsedMatchingBifield": [
        "GPAPUD",
        "GPBPUD",
        "GPHPUD",
        "GPAINV",
        "GPBINV",
        "GPHINV",
        "GPAODR",
        "GPBODR",
        "GPHODR"
      ]
    },
    {
      "file": "gpio.c",
      "peripheral": "gpio",
      "functionName": "GPIO_getPadConfig",
      "functionArgs": [
        "pin"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "GPAPUD",
        "GPBPUD",
        "GPHPUD",
        "GPAINV",
        "GPBINV",
        "GPHINV",
        "GPAODR",
        "GPBODR",
        "GPHODR"
      ],
      "registersUsedMatchingBifield": [
        "GPAPUD",
        "GPBPUD",
        "GPHPUD",
        "GPAINV",
        "GPBINV",
        "GPHINV",
        "GPAODR",
        "GPBODR",
        "GPHODR"
      ]
    },
    {
      "file": "gpio.c",
      "peripheral": "gpio",
      "functionName": "GPIO_setQualificationMode",
      "functionArgs": [
        "pin",
        "qualification"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "GPIO_QualificationMode"
      ],
      "returnType": "void",
      "registersUsed": [
        "GPAQSEL1",
        "GPAQSEL2",
        "GPBQSEL1",
        "GPHQSEL1",
        "GPHQSEL2"
      ],
      "registersUsedMatchingBifield": [
        "GPAQSEL1",
        "GPAQSEL2",
        "GPBQSEL1",
        "GPHQSEL1",
        "GPHQSEL2"
      ]
    },
    {
      "file": "gpio.c",
      "peripheral": "gpio",
      "functionName": "GPIO_getQualificationMode",
      "functionArgs": [
        "pin"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "GPIO_QualificationMode",
      "registersUsed": [
        "GPAQSEL1",
        "GPAQSEL2",
        "GPBQSEL1",
        "GPHQSEL1",
        "GPHQSEL2"
      ],
      "registersUsedMatchingBifield": [
        "GPAQSEL1",
        "GPAQSEL2",
        "GPBQSEL1",
        "GPHQSEL1",
        "GPHQSEL2"
      ]
    },
    {
      "file": "gpio.c",
      "peripheral": "gpio",
      "functionName": "GPIO_setQualificationPeriod",
      "functionArgs": [
        "pin",
        "divider"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "GPACTRL",
        "GPBCTRL",
        "GPHCTRL"
      ],
      "registersUsedMatchingBifield": [
        "GPACTRL",
        "GPBCTRL",
        "GPHCTRL"
      ]
    },
    {
      "file": "gpio.c",
      "peripheral": "gpio",
      "functionName": "GPIO_setAnalogMode",
      "functionArgs": [
        "pin",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "GPIO_AnalogMode"
      ],
      "returnType": "void",
      "registersUsed": [
        "AGPIOCTRLA"
      ],
      "registersUsedMatchingBifield": [
        "AGPIOCTRLA"
      ]
    },
    {
      "file": "gpio.c",
      "peripheral": "gpio",
      "functionName": "GPIO_setPinConfig",
      "functionArgs": [
        "pinConfig"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "GPAMUX1",
        "GPAMUX2",
        "GPBMUX1",
        "GPHMUX1",
        "GPHMUX2",
        "GPAGMUX1",
        "GPAGMUX2",
        "GPBGMUX1",
        "GPHGMUX1",
        "GPHGMUX2"
      ],
      "registersUsedMatchingBifield": [
        "GPAMUX1",
        "GPAMUX2",
        "GPBMUX1",
        "GPHMUX1",
        "GPHMUX2",
        "GPAGMUX1",
        "GPAGMUX2",
        "GPBGMUX1",
        "GPHGMUX1",
        "GPHGMUX2"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_isPinValid",
      "functionArgs": [
        "pin"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef DEBUG  static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_setInterruptType",
      "functionArgs": [
        "extIntNum",
        "intType"
      ],
      "functionArgsTypes": [
        "GPIO_ExternalIntNum",
        "GPIO_IntType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "1CR"
      ],
      "registersUsedMatchingBifield": [
        "1CR"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_getInterruptType",
      "functionArgs": [
        "extIntNum"
      ],
      "functionArgsTypes": [
        "GPIO_ExternalIntNum"
      ],
      "returnType": "static inline GPIO_IntType",
      "registersUsed": [
        "1CR"
      ],
      "registersUsedMatchingBifield": [
        "1CR"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_enableInterrupt",
      "functionArgs": [
        "extIntNum"
      ],
      "functionArgsTypes": [
        "GPIO_ExternalIntNum"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "1CR"
      ],
      "registersUsedMatchingBifield": [
        "1CR"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_disableInterrupt",
      "functionArgs": [
        "extIntNum"
      ],
      "functionArgsTypes": [
        "GPIO_ExternalIntNum"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "1CR"
      ],
      "registersUsedMatchingBifield": [
        "1CR"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_getInterruptCounter",
      "functionArgs": [
        "extIntNum"
      ],
      "functionArgsTypes": [
        "GPIO_ExternalIntNum"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "1CR",
        "1CTR"
      ],
      "registersUsedMatchingBifield": [
        "1CR",
        "1CTR"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_readPin",
      "functionArgs": [
        "pin"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "GPADAT",
        "GPBDAT",
        "GPHDAT"
      ],
      "registersUsedMatchingBifield": [
        "GPADAT",
        "GPBDAT",
        "GPHDAT"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_readPinDataRegister",
      "functionArgs": [
        "pin"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_writePin",
      "functionArgs": [
        "pin",
        "outVal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPASET",
        "GPBSET",
        "GPHSET",
        "GPACLEAR",
        "GPBCLEAR",
        "GPHCLEAR"
      ],
      "registersUsedMatchingBifield": [
        "GPASET",
        "GPBSET",
        "GPHSET",
        "GPACLEAR",
        "GPBCLEAR",
        "GPHCLEAR"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_togglePin",
      "functionArgs": [
        "pin"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPATOGGLE",
        "GPBTOGGLE",
        "GPHTOGGLE"
      ],
      "registersUsedMatchingBifield": [
        "GPATOGGLE",
        "GPBTOGGLE",
        "GPHTOGGLE"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_readPortData",
      "functionArgs": [
        "port"
      ],
      "functionArgsTypes": [
        "GPIO_Port"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "GPADAT",
        "GPBDAT",
        "GPHDAT"
      ],
      "registersUsedMatchingBifield": [
        "GPADAT",
        "GPBDAT",
        "GPHDAT"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_readPortDataRegister",
      "functionArgs": [
        "port"
      ],
      "functionArgsTypes": [
        "GPIO_Port"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_writePortData",
      "functionArgs": [
        "port",
        "outVal"
      ],
      "functionArgsTypes": [
        "GPIO_Port",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPADAT",
        "GPBDAT",
        "GPHDAT"
      ],
      "registersUsedMatchingBifield": [
        "GPADAT",
        "GPBDAT",
        "GPHDAT"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_setPortPins",
      "functionArgs": [
        "port",
        "pinMask"
      ],
      "functionArgsTypes": [
        "GPIO_Port",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPASET",
        "GPBSET",
        "GPHSET"
      ],
      "registersUsedMatchingBifield": [
        "GPASET",
        "GPBSET",
        "GPHSET"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_clearPortPins",
      "functionArgs": [
        "port",
        "pinMask"
      ],
      "functionArgsTypes": [
        "GPIO_Port",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPACLEAR",
        "GPBCLEAR",
        "GPHCLEAR"
      ],
      "registersUsedMatchingBifield": [
        "GPACLEAR",
        "GPBCLEAR",
        "GPHCLEAR"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_togglePortPins",
      "functionArgs": [
        "port",
        "pinMask"
      ],
      "functionArgsTypes": [
        "GPIO_Port",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPATOGGLE",
        "GPBTOGGLE",
        "GPHTOGGLE"
      ],
      "registersUsedMatchingBifield": [
        "GPATOGGLE",
        "GPBTOGGLE",
        "GPHTOGGLE"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_lockPortConfig",
      "functionArgs": [
        "port",
        "pinMask"
      ],
      "functionArgsTypes": [
        "GPIO_Port",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPALOCK",
        "GPBLOCK",
        "GPHLOCK"
      ],
      "registersUsedMatchingBifield": [
        "GPALOCK",
        "GPBLOCK",
        "GPHLOCK"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_unlockPortConfig",
      "functionArgs": [
        "port",
        "pinMask"
      ],
      "functionArgsTypes": [
        "GPIO_Port",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPALOCK",
        "GPBLOCK",
        "GPHLOCK"
      ],
      "registersUsedMatchingBifield": [
        "GPALOCK",
        "GPBLOCK",
        "GPHLOCK"
      ]
    },
    {
      "file": "gpio.h",
      "peripheral": "gpio",
      "functionName": "GPIO_commitPortConfig",
      "functionArgs": [
        "port",
        "pinMask"
      ],
      "functionArgsTypes": [
        "GPIO_Port",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPACR",
        "GPBCR",
        "GPHCR"
      ],
      "registersUsedMatchingBifield": [
        "GPACR",
        "GPBCR",
        "GPHCR"
      ]
    }
  ]
}
module.exports = { 
  gpio_driverlib: gpio_driverlib,
}
