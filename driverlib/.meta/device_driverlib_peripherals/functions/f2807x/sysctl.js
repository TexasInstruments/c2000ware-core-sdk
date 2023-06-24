let sysctl_driverlib = 
{
  "name": "sysctl",
  "functions": [
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_pollCpuTimer",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "SYSCTL_DELAY;      static void",
      "registersUsed": [
        "SYSPLLCTL1"
      ],
      "registersUsedMatchingBifield": [
        "SYSPLLCTL1"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getClock",
      "functionArgs": [
        "clockInHz"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "CLKSRCCTL1",
        "SYSPLLCTL1",
        "SYSPLLMULT",
        "SYSCLKDIVSEL"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1",
        "SYSPLLCTL1",
        "SYSPLLMULT",
        "SYSCLKDIVSEL"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getAuxClock",
      "functionArgs": [
        "clockInHz"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "CLKSRCCTL2",
        "AUXPLLCTL1",
        "AUXPLLMULT",
        "AUXCLKDIVSEL"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL2",
        "AUXPLLCTL1",
        "AUXPLLMULT",
        "AUXCLKDIVSEL"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setClock",
      "functionArgs": [
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "bool",
      "registersUsed": [
        "TIM",
        "PRD",
        "TCR",
        "TPR",
        "TPRH",
        "SYSDBGCTL",
        "SYSPLLCTL1",
        "SYSPLLMULT",
        "SYSPLLSTS",
        "SYSCLKDIVSEL",
        "TMR2CLKCTL",
        "SCSR",
        "WDCR",
        "WDWCR"
      ],
      "registersUsedMatchingBifield": [
        "TIM",
        "PRD",
        "TCR",
        "TPR",
        "TPRH",
        "SYSDBGCTL",
        "SYSPLLCTL1",
        "SYSPLLMULT",
        "SYSPLLSTS",
        "SYSCLKDIVSEL",
        "TMR2CLKCTL",
        "SCSR",
        "WDCR",
        "WDWCR"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setAuxClock",
      "functionArgs": [
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "PRD",
        "TCR",
        "TPR",
        "TPRH",
        "AUXPLLCTL1",
        "AUXPLLMULT",
        "AUXPLLSTS",
        "AUXCLKDIVSEL",
        "TMR2CLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "PRD",
        "TCR",
        "TPR",
        "TPRH",
        "AUXPLLCTL1",
        "AUXPLLMULT",
        "AUXPLLSTS",
        "AUXCLKDIVSEL",
        "TMR2CLKCTL"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_selectXTAL",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "void",
      "registersUsed": [
        "PRD",
        "TCR",
        "TPR",
        "TPRH",
        "CLKSRCCTL1",
        "TMR2CLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "PRD",
        "TCR",
        "TPR",
        "TPRH",
        "CLKSRCCTL1",
        "TMR2CLKCTL"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_selectOscSource",
      "functionArgs": [
        "oscSource"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CLKSRCCTL1"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_selectOscSourceAuxPLL",
      "functionArgs": [
        "oscSource"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CLKSRCCTL1",
        "CLKSRCCTL2"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1",
        "CLKSRCCTL2"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getLowSpeedClock",
      "functionArgs": [
        "clockInHz"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "LOSPCP"
      ],
      "registersUsedMatchingBifield": [
        "LOSPCP"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getDeviceParametric",
      "functionArgs": [
        "parametric"
      ],
      "functionArgsTypes": [
        "SysCtl_DeviceParametric"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "PARTIDL",
        "PARTIDH"
      ],
      "registersUsedMatchingBifield": [
        "PARTIDL",
        "PARTIDH"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_deviceCal",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_resetPeripheral",
      "functionArgs": [
        "peripheral"
      ],
      "functionArgsTypes": [
        "SysCtl_PeripheralSOFTPRES"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SOFTPRES0",
        "SOFTPRES1",
        "SOFTPRES2",
        "SOFTPRES3",
        "SOFTPRES4",
        "SOFTPRES6",
        "SOFTPRES7",
        "SOFTPRES8",
        "SOFTPRES9",
        "SOFTPRES11",
        "SOFTPRES13",
        "SOFTPRES14",
        "SOFTPRES16"
      ],
      "registersUsedMatchingBifield": [
        "SOFTPRES0",
        "SOFTPRES1",
        "SOFTPRES2",
        "SOFTPRES3",
        "SOFTPRES4",
        "SOFTPRES6",
        "SOFTPRES7",
        "SOFTPRES8",
        "SOFTPRES9",
        "SOFTPRES11",
        "SOFTPRES13",
        "SOFTPRES14",
        "SOFTPRES16"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enablePeripheral",
      "functionArgs": [
        "peripheral"
      ],
      "functionArgsTypes": [
        "SysCtl_PeripheralPCLOCKCR"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCLKCR0",
        "PCLKCR1",
        "PCLKCR2",
        "PCLKCR3",
        "PCLKCR4",
        "PCLKCR6",
        "PCLKCR7",
        "PCLKCR8",
        "PCLKCR9",
        "PCLKCR10",
        "PCLKCR11",
        "PCLKCR12",
        "PCLKCR13",
        "PCLKCR14",
        "PCLKCR16"
      ],
      "registersUsedMatchingBifield": [
        "PCLKCR0",
        "PCLKCR1",
        "PCLKCR2",
        "PCLKCR3",
        "PCLKCR4",
        "PCLKCR6",
        "PCLKCR7",
        "PCLKCR8",
        "PCLKCR9",
        "PCLKCR10",
        "PCLKCR11",
        "PCLKCR12",
        "PCLKCR13",
        "PCLKCR14",
        "PCLKCR16"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_disablePeripheral",
      "functionArgs": [
        "peripheral"
      ],
      "functionArgsTypes": [
        "SysCtl_PeripheralPCLOCKCR"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PCLKCR0",
        "PCLKCR1",
        "PCLKCR2",
        "PCLKCR3",
        "PCLKCR4",
        "PCLKCR6",
        "PCLKCR7",
        "PCLKCR8",
        "PCLKCR9",
        "PCLKCR10",
        "PCLKCR11",
        "PCLKCR12",
        "PCLKCR13",
        "PCLKCR14",
        "PCLKCR16"
      ],
      "registersUsedMatchingBifield": [
        "PCLKCR0",
        "PCLKCR1",
        "PCLKCR2",
        "PCLKCR3",
        "PCLKCR4",
        "PCLKCR6",
        "PCLKCR7",
        "PCLKCR8",
        "PCLKCR9",
        "PCLKCR10",
        "PCLKCR11",
        "PCLKCR12",
        "PCLKCR13",
        "PCLKCR14",
        "PCLKCR16"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_resetDevice",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WDCR"
      ],
      "registersUsedMatchingBifield": [
        "WDCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getResetCause",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "RESC"
      ],
      "registersUsedMatchingBifield": [
        "RESC"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_clearResetCause",
      "functionArgs": [
        "rstCauses"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RESC"
      ],
      "registersUsedMatchingBifield": [
        "RESC"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setLowSpeedClock",
      "functionArgs": [
        "prescaler"
      ],
      "functionArgsTypes": [
        "SysCtl_LSPCLKPrescaler"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOSPCP"
      ],
      "registersUsedMatchingBifield": [
        "LOSPCP"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setEPWMClockDivider",
      "functionArgs": [
        "divider"
      ],
      "functionArgsTypes": [
        "SysCtl_EPWMCLKDivider"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PERCLKDIVSEL"
      ],
      "registersUsedMatchingBifield": [
        "PERCLKDIVSEL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setEMIF1ClockDivider",
      "functionArgs": [
        "divider"
      ],
      "functionArgsTypes": [
        "SysCtl_EMIF1CLKDivider"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PERCLKDIVSEL"
      ],
      "registersUsedMatchingBifield": [
        "PERCLKDIVSEL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setEMIF2ClockDivider",
      "functionArgs": [
        "divider"
      ],
      "functionArgsTypes": [
        "SysCtl_EMIF2CLKDivider"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PERCLKDIVSEL"
      ],
      "registersUsedMatchingBifield": [
        "PERCLKDIVSEL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_selectClockOutSource",
      "functionArgs": [
        "source"
      ],
      "functionArgsTypes": [
        "SysCtl_ClockOut"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLKSRCCTL3"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL3"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getExternalOscCounterValue",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "X1CNT"
      ],
      "registersUsedMatchingBifield": [
        "X1CNT"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_turnOnOsc",
      "functionArgs": [
        "oscSource"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLKSRCCTL1"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_turnOffOsc",
      "functionArgs": [
        "oscSource"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLKSRCCTL1"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enterIdleMode",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LPMCR"
      ],
      "registersUsedMatchingBifield": [
        "LPMCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enterStandbyMode",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LPMCR"
      ],
      "registersUsedMatchingBifield": [
        "LPMCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enterHaltMode",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYSPLLCTL1",
        "LPMCR"
      ],
      "registersUsedMatchingBifield": [
        "SYSPLLCTL1",
        "LPMCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enterHibernateMode",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYSPLLCTL1",
        "LPMCR"
      ],
      "registersUsedMatchingBifield": [
        "SYSPLLCTL1",
        "LPMCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enableLPMWakeupPin",
      "functionArgs": [
        "pin"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPIOLPMSEL0",
        "GPIOLPMSEL1"
      ],
      "registersUsedMatchingBifield": [
        "GPIOLPMSEL0",
        "GPIOLPMSEL1"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_disableLPMWakeupPin",
      "functionArgs": [
        "pin"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPIOLPMSEL0",
        "GPIOLPMSEL1"
      ],
      "registersUsedMatchingBifield": [
        "GPIOLPMSEL0",
        "GPIOLPMSEL1"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setStandbyQualificationPeriod",
      "functionArgs": [
        "cycles"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LPMCR"
      ],
      "registersUsedMatchingBifield": [
        "LPMCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enableWatchdogStandbyWakeup",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LPMCR"
      ],
      "registersUsedMatchingBifield": [
        "LPMCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_disableWatchdogStandbyWakeup",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LPMCR"
      ],
      "registersUsedMatchingBifield": [
        "LPMCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enableWatchdogInHalt",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLKSRCCTL1"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_disableWatchdogInHalt",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLKSRCCTL1"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setWatchdogMode",
      "functionArgs": [
        "mode"
      ],
      "functionArgsTypes": [
        "SysCtl_WDMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCSR"
      ],
      "registersUsedMatchingBifield": [
        "SCSR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_isWatchdogInterruptActive",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SCSR"
      ],
      "registersUsedMatchingBifield": [
        "SCSR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_disableWatchdog",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WDCR"
      ],
      "registersUsedMatchingBifield": [
        "WDCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enableWatchdog",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WDCR"
      ],
      "registersUsedMatchingBifield": [
        "WDCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_serviceWatchdog",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WDKEY"
      ],
      "registersUsedMatchingBifield": [
        "WDKEY"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enableWatchdogReset",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WDKEY"
      ],
      "registersUsedMatchingBifield": [
        "WDKEY"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_resetWatchdog",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WDKEY"
      ],
      "registersUsedMatchingBifield": [
        "WDKEY"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setWatchdogPrescaler",
      "functionArgs": [
        "prescaler"
      ],
      "functionArgsTypes": [
        "SysCtl_WDPrescaler"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WDCR"
      ],
      "registersUsedMatchingBifield": [
        "WDCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getWatchdogCounterValue",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "WDCNTR"
      ],
      "registersUsedMatchingBifield": [
        "WDCNTR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getWatchdogResetStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "RESC"
      ],
      "registersUsedMatchingBifield": [
        "RESC"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_clearWatchdogResetStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RESC"
      ],
      "registersUsedMatchingBifield": [
        "RESC"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setWatchdogWindowValue",
      "functionArgs": [
        "value"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WDWCR"
      ],
      "registersUsedMatchingBifield": [
        "WDWCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_clearWatchdogOverride",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SCSR"
      ],
      "registersUsedMatchingBifield": [
        "SCSR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enableNMIGlobalInterrupt",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CFG"
      ],
      "registersUsedMatchingBifield": [
        "CFG"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getNMIStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "FLG"
      ],
      "registersUsedMatchingBifield": [
        "FLG"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getNMIFlagStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "FLG"
      ],
      "registersUsedMatchingBifield": [
        "FLG"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_isNMIFlagSet",
      "functionArgs": [
        "nmiFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "FLG"
      ],
      "registersUsedMatchingBifield": [
        "FLG"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_clearNMIStatus",
      "functionArgs": [
        "nmiFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FLG",
        "FLGCLR"
      ],
      "registersUsedMatchingBifield": [
        "FLG",
        "FLGCLR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_clearAllNMIFlags",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FLG",
        "FLGCLR"
      ],
      "registersUsedMatchingBifield": [
        "FLG",
        "FLGCLR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_forceNMIFlags",
      "functionArgs": [
        "nmiFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FLG",
        "FLGFRC"
      ],
      "registersUsedMatchingBifield": [
        "FLG",
        "FLGFRC"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getNMIWatchdogCounter",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "WDCNT"
      ],
      "registersUsedMatchingBifield": [
        "WDCNT"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setNMIWatchdogPeriod",
      "functionArgs": [
        "wdPeriod"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "WDPRD"
      ],
      "registersUsedMatchingBifield": [
        "WDPRD"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getNMIWatchdogPeriod",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "WDPRD"
      ],
      "registersUsedMatchingBifield": [
        "WDPRD"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getNMIShadowFlagStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "SHDFLG"
      ],
      "registersUsedMatchingBifield": [
        "SHDFLG"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_isNMIShadowFlagSet",
      "functionArgs": [
        "nmiFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "SHDFLG"
      ],
      "registersUsedMatchingBifield": [
        "SHDFLG"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enableMCD",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCDCR"
      ],
      "registersUsedMatchingBifield": [
        "MCDCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_disableMCD",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCDCR"
      ],
      "registersUsedMatchingBifield": [
        "MCDCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_isMCDClockFailureDetected",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "MCDCR"
      ],
      "registersUsedMatchingBifield": [
        "MCDCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_resetMCD",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCDCR"
      ],
      "registersUsedMatchingBifield": [
        "MCDCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_connectMCDClockSource",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCDCR"
      ],
      "registersUsedMatchingBifield": [
        "MCDCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_disconnectMCDClockSource",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCDCR"
      ],
      "registersUsedMatchingBifield": [
        "MCDCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setSyncInputConfig",
      "functionArgs": [
        "syncInput",
        "syncSrc"
      ],
      "functionArgsTypes": [
        "SysCtl_SyncInput",
        "SysCtl_SyncInputSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYNCSELECT"
      ],
      "registersUsedMatchingBifield": [
        "SYNCSELECT"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setSyncOutputConfig",
      "functionArgs": [
        "syncSrc"
      ],
      "functionArgsTypes": [
        "SysCtl_SyncOutputSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYNCSELECT"
      ],
      "registersUsedMatchingBifield": [
        "SYNCSELECT"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enableExtADCSOCSource",
      "functionArgs": [
        "adcsocSrc"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ADCSOCOUTSELECT"
      ],
      "registersUsedMatchingBifield": [
        "ADCSOCOUTSELECT"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_disableExtADCSOCSource",
      "functionArgs": [
        "adcsocSrc"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ADCSOCOUTSELECT"
      ],
      "registersUsedMatchingBifield": [
        "ADCSOCOUTSELECT"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_lockExtADCSOCSelect",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYNCSOCLOCK"
      ],
      "registersUsedMatchingBifield": [
        "SYNCSOCLOCK"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_selectSecMaster",
      "functionArgs": [
        "periFrame1Config",
        "periFrame2Config"
      ],
      "functionArgsTypes": [
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SECMSEL"
      ],
      "registersUsedMatchingBifield": [
        "SECMSEL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_lockSyncSelect",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYNCSOCLOCK"
      ],
      "registersUsedMatchingBifield": [
        "SYNCSOCLOCK"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getDeviceRevision",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "REVID"
      ],
      "registersUsedMatchingBifield": [
        "REVID"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getEfuseError",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "FUSEERR"
      ],
      "registersUsedMatchingBifield": [
        "FUSEERR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setXClk",
      "functionArgs": [
        "divider"
      ],
      "functionArgsTypes": [
        "SysCtl_XClkDivider"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "XCLKOUTDIVSEL"
      ],
      "registersUsedMatchingBifield": [
        "XCLKOUTDIVSEL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setPLLSysClk",
      "functionArgs": [
        "divider"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYSCLKDIVSEL"
      ],
      "registersUsedMatchingBifield": [
        "SYSCLKDIVSEL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setAuxPLLClk",
      "functionArgs": [
        "divider"
      ],
      "functionArgsTypes": [
        "SysCtl_AuxPLLClkDivider"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "AUXCLKDIVSEL"
      ],
      "registersUsedMatchingBifield": [
        "AUXCLKDIVSEL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setCputimer2Clk",
      "functionArgs": [
        "divider",
        "source"
      ],
      "functionArgsTypes": [
        "SysCtl_Cputimer2ClkDivider",
        "SysCtl_Cputimer2ClkSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TMR2CLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "TMR2CLKCTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getPIEVErrAddr",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "PIEVERRADDR"
      ],
      "registersUsedMatchingBifield": [
        "PIEVERRADDR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_isPresentUSBPHY",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "PERCNF1"
      ],
      "registersUsedMatchingBifield": [
        "PERCNF1"
      ]
    }
  ]
}
module.exports = { 
  sysctl_driverlib: sysctl_driverlib,
}
