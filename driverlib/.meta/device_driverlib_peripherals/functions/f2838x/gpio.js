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
        "GPCDIR",
        "GPDDIR",
        "GPEDIR",
        "GPFDIR"
      ],
      "registersUsedMatchingBifield": [
        "GPADIR",
        "GPBDIR",
        "GPCDIR",
        "GPDDIR",
        "GPEDIR",
        "GPFDIR"
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
        "GPCDIR",
        "GPDDIR",
        "GPEDIR",
        "GPFDIR"
      ],
      "registersUsedMatchingBifield": [
        "GPADIR",
        "GPBDIR",
        "GPCDIR",
        "GPDDIR",
        "GPEDIR",
        "GPFDIR"
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
        "GPCPUD",
        "GPDPUD",
        "GPEPUD",
        "GPFPUD",
        "GPAINV",
        "GPBINV",
        "GPCINV",
        "GPDINV",
        "GPEINV",
        "GPFINV",
        "GPAODR",
        "GPBODR",
        "GPCODR",
        "GPDODR",
        "GPEODR",
        "GPFODR"
      ],
      "registersUsedMatchingBifield": [
        "GPAPUD",
        "GPBPUD",
        "GPCPUD",
        "GPDPUD",
        "GPEPUD",
        "GPFPUD",
        "GPAINV",
        "GPBINV",
        "GPCINV",
        "GPDINV",
        "GPEINV",
        "GPFINV",
        "GPAODR",
        "GPBODR",
        "GPCODR",
        "GPDODR",
        "GPEODR",
        "GPFODR"
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
        "GPCPUD",
        "GPDPUD",
        "GPEPUD",
        "GPFPUD",
        "GPAINV",
        "GPBINV",
        "GPCINV",
        "GPDINV",
        "GPEINV",
        "GPFINV",
        "GPAODR",
        "GPBODR",
        "GPCODR",
        "GPDODR",
        "GPEODR",
        "GPFODR"
      ],
      "registersUsedMatchingBifield": [
        "GPAPUD",
        "GPBPUD",
        "GPCPUD",
        "GPDPUD",
        "GPEPUD",
        "GPFPUD",
        "GPAINV",
        "GPBINV",
        "GPCINV",
        "GPDINV",
        "GPEINV",
        "GPFINV",
        "GPAODR",
        "GPBODR",
        "GPCODR",
        "GPDODR",
        "GPEODR",
        "GPFODR"
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
        "GPBQSEL2",
        "GPCQSEL1",
        "GPCQSEL2",
        "GPDQSEL1",
        "GPDQSEL2",
        "GPEQSEL1",
        "GPEQSEL2",
        "GPFQSEL1"
      ],
      "registersUsedMatchingBifield": [
        "GPAQSEL1",
        "GPAQSEL2",
        "GPBQSEL1",
        "GPBQSEL2",
        "GPCQSEL1",
        "GPCQSEL2",
        "GPDQSEL1",
        "GPDQSEL2",
        "GPEQSEL1",
        "GPEQSEL2",
        "GPFQSEL1"
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
        "GPBQSEL2",
        "GPCQSEL1",
        "GPCQSEL2",
        "GPDQSEL1",
        "GPDQSEL2",
        "GPEQSEL1",
        "GPEQSEL2",
        "GPFQSEL1"
      ],
      "registersUsedMatchingBifield": [
        "GPAQSEL1",
        "GPAQSEL2",
        "GPBQSEL1",
        "GPBQSEL2",
        "GPCQSEL1",
        "GPCQSEL2",
        "GPDQSEL1",
        "GPDQSEL2",
        "GPEQSEL1",
        "GPEQSEL2",
        "GPFQSEL1"
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
        "GPCCTRL",
        "GPDCTRL",
        "GPECTRL",
        "GPFCTRL"
      ],
      "registersUsedMatchingBifield": [
        "GPACTRL",
        "GPBCTRL",
        "GPCCTRL",
        "GPDCTRL",
        "GPECTRL",
        "GPFCTRL"
      ]
    },
    {
      "file": "gpio.c",
      "peripheral": "gpio",
      "functionName": "GPIO_setMasterCore",
      "functionArgs": [
        "pin",
        "core"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "GPIO_CoreSelect"
      ],
      "returnType": "void",
      "registersUsed": [
        "GPACSEL1",
        "GPACSEL2",
        "GPACSEL3",
        "GPACSEL4",
        "GPBCSEL1",
        "GPBCSEL2",
        "GPBCSEL3",
        "GPBCSEL4",
        "GPCCSEL1",
        "GPCCSEL2",
        "GPCCSEL3",
        "GPCCSEL4",
        "GPDCSEL1",
        "GPDCSEL2",
        "GPDCSEL3",
        "GPDCSEL4",
        "GPECSEL1",
        "GPECSEL2",
        "GPECSEL3",
        "GPECSEL4",
        "GPFCSEL1",
        "GPFCSEL2"
      ],
      "registersUsedMatchingBifield": [
        "GPACSEL1",
        "GPACSEL2",
        "GPACSEL3",
        "GPACSEL4",
        "GPBCSEL1",
        "GPBCSEL2",
        "GPBCSEL3",
        "GPBCSEL4",
        "GPCCSEL1",
        "GPCCSEL2",
        "GPCCSEL3",
        "GPCCSEL4",
        "GPDCSEL1",
        "GPDCSEL2",
        "GPDCSEL3",
        "GPDCSEL4",
        "GPECSEL1",
        "GPECSEL2",
        "GPECSEL3",
        "GPECSEL4",
        "GPFCSEL1",
        "GPFCSEL2"
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
        "GPBAMSEL"
      ],
      "registersUsedMatchingBifield": [
        "GPBAMSEL"
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
        "GPBMUX2",
        "GPCMUX1",
        "GPCMUX2",
        "GPDMUX1",
        "GPDMUX2",
        "GPEMUX1",
        "GPEMUX2",
        "GPFMUX1",
        "GPAGMUX1",
        "GPAGMUX2",
        "GPBGMUX1",
        "GPBGMUX2",
        "GPCGMUX1",
        "GPCGMUX2",
        "GPDGMUX1",
        "GPDGMUX2",
        "GPEGMUX1",
        "GPEGMUX2",
        "GPFGMUX1"
      ],
      "registersUsedMatchingBifield": [
        "GPAMUX1",
        "GPAMUX2",
        "GPBMUX1",
        "GPBMUX2",
        "GPCMUX1",
        "GPCMUX2",
        "GPDMUX1",
        "GPDMUX2",
        "GPEMUX1",
        "GPEMUX2",
        "GPFMUX1",
        "GPAGMUX1",
        "GPAGMUX2",
        "GPBGMUX1",
        "GPBGMUX2",
        "GPCGMUX1",
        "GPCGMUX2",
        "GPDGMUX1",
        "GPDGMUX2",
        "GPEGMUX1",
        "GPEGMUX2",
        "GPFGMUX1"
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
        "GPCDAT",
        "GPDDAT",
        "GPEDAT",
        "GPFDAT"
      ],
      "registersUsedMatchingBifield": [
        "GPADAT",
        "GPBDAT",
        "GPCDAT",
        "GPDDAT",
        "GPEDAT",
        "GPFDAT"
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
        "GPCSET",
        "GPDSET",
        "GPESET",
        "GPFSET",
        "GPACLEAR",
        "GPBCLEAR",
        "GPCCLEAR",
        "GPDCLEAR",
        "GPECLEAR",
        "GPFCLEAR"
      ],
      "registersUsedMatchingBifield": [
        "GPASET",
        "GPBSET",
        "GPCSET",
        "GPDSET",
        "GPESET",
        "GPFSET",
        "GPACLEAR",
        "GPBCLEAR",
        "GPCCLEAR",
        "GPDCLEAR",
        "GPECLEAR",
        "GPFCLEAR"
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
        "GPCTOGGLE",
        "GPDTOGGLE",
        "GPETOGGLE",
        "GPFTOGGLE"
      ],
      "registersUsedMatchingBifield": [
        "GPATOGGLE",
        "GPBTOGGLE",
        "GPCTOGGLE",
        "GPDTOGGLE",
        "GPETOGGLE",
        "GPFTOGGLE"
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
        "GPCDAT",
        "GPDDAT",
        "GPEDAT",
        "GPFDAT"
      ],
      "registersUsedMatchingBifield": [
        "GPADAT",
        "GPBDAT",
        "GPCDAT",
        "GPDDAT",
        "GPEDAT",
        "GPFDAT"
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
        "GPCDAT",
        "GPDDAT",
        "GPEDAT",
        "GPFDAT"
      ],
      "registersUsedMatchingBifield": [
        "GPADAT",
        "GPBDAT",
        "GPCDAT",
        "GPDDAT",
        "GPEDAT",
        "GPFDAT"
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
        "GPCSET",
        "GPDSET",
        "GPESET",
        "GPFSET"
      ],
      "registersUsedMatchingBifield": [
        "GPASET",
        "GPBSET",
        "GPCSET",
        "GPDSET",
        "GPESET",
        "GPFSET"
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
        "GPCCLEAR",
        "GPDCLEAR",
        "GPECLEAR",
        "GPFCLEAR"
      ],
      "registersUsedMatchingBifield": [
        "GPACLEAR",
        "GPBCLEAR",
        "GPCCLEAR",
        "GPDCLEAR",
        "GPECLEAR",
        "GPFCLEAR"
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
        "GPCTOGGLE",
        "GPDTOGGLE",
        "GPETOGGLE",
        "GPFTOGGLE"
      ],
      "registersUsedMatchingBifield": [
        "GPATOGGLE",
        "GPBTOGGLE",
        "GPCTOGGLE",
        "GPDTOGGLE",
        "GPETOGGLE",
        "GPFTOGGLE"
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
        "GPCLOCK",
        "GPDLOCK",
        "GPELOCK",
        "GPFLOCK"
      ],
      "registersUsedMatchingBifield": [
        "GPALOCK",
        "GPBLOCK",
        "GPCLOCK",
        "GPDLOCK",
        "GPELOCK",
        "GPFLOCK"
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
        "GPCLOCK",
        "GPDLOCK",
        "GPELOCK",
        "GPFLOCK"
      ],
      "registersUsedMatchingBifield": [
        "GPALOCK",
        "GPBLOCK",
        "GPCLOCK",
        "GPDLOCK",
        "GPELOCK",
        "GPFLOCK"
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
        "GPCCR",
        "GPDCR",
        "GPECR",
        "GPFCR"
      ],
      "registersUsedMatchingBifield": [
        "GPACR",
        "GPBCR",
        "GPCCR",
        "GPDCR",
        "GPECR",
        "GPFCR"
      ]
    }
  ]
}
module.exports = { 
  gpio_driverlib: gpio_driverlib,
}
