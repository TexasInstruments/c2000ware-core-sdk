let sysctl_driverlib = 
{
  "name": "sysctl",
  "functions": [
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_pollX1Counter",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static void",
      "registersUsed": [
        "X1CNT"
      ],
      "registersUsedMatchingBifield": [
        "X1CNT"
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
      "functionName": "SysCtl_setClock",
      "functionArgs": [
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "bool",
      "registersUsed": [
        "CLKSRCCTL1",
        "SYSPLLCTL1",
        "SYSPLLMULT",
        "SYSPLLSTS",
        "SYSCLKDIVSEL",
        "XTALCR"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1",
        "SYSPLLCTL1",
        "SYSPLLMULT",
        "SYSPLLSTS",
        "SYSCLKDIVSEL",
        "XTALCR"
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
        "CLKSRCCTL1",
        "XTALCR",
        "XTALCR2"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1",
        "XTALCR",
        "XTALCR2"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_selectXTALSingleEnded",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "void",
      "registersUsed": [
        "CLKSRCCTL1",
        "XTALCR"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1",
        "XTALCR"
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
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_isPLLValid",
      "functionArgs": [
        "base",
        "oscSource",
        "pllMultDiv"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "bool",
      "registersUsed": [
        "STATUS"
      ],
      "registersUsedMatchingBifield": [
        "DCCSTATUS"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_configureType",
      "functionArgs": [
        "",
        "config",
        "lock"
      ],
      "functionArgsTypes": [
        "SysCtl_SelTypetype",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "ECAPTYPE"
      ],
      "registersUsedMatchingBifield": [
        "ECAPTYPE"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_isConfigTypeLocked",
      "functionArgs": [
        "type"
      ],
      "functionArgsTypes": [
        "SysCtl_SelType"
      ],
      "returnType": "bool",
      "registersUsed": [
        "ECAPTYPE"
      ],
      "registersUsedMatchingBifield": [
        "ECAPTYPE"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_lockClkConfig",
      "functionArgs": [
        "registerName"
      ],
      "functionArgsTypes": [
        "SysCtl_ClkRegSel"
      ],
      "returnType": "void",
      "registersUsed": [
        "CLKCFGLOCK1"
      ],
      "registersUsedMatchingBifield": [
        "CLKCFGLOCK1"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_lockSysConfig",
      "functionArgs": [
        "registerName"
      ],
      "functionArgsTypes": [
        "SysCtl_CpuRegSel"
      ],
      "returnType": "void",
      "registersUsed": [
        "CPUSYSLOCK1"
      ],
      "registersUsedMatchingBifield": [
        "CPUSYSLOCK1"
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
      "registersUsed": [],
      "registersUsedMatchingBifield": []
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
        "PCLKCR2",
        "PCLKCR3",
        "PCLKCR4",
        "PCLKCR7",
        "PCLKCR8",
        "PCLKCR9",
        "PCLKCR10",
        "PCLKCR13",
        "PCLKCR14"
      ],
      "registersUsedMatchingBifield": [
        "PCLKCR0",
        "PCLKCR2",
        "PCLKCR3",
        "PCLKCR4",
        "PCLKCR7",
        "PCLKCR8",
        "PCLKCR9",
        "PCLKCR10",
        "PCLKCR13",
        "PCLKCR14"
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
        "PCLKCR2",
        "PCLKCR3",
        "PCLKCR4",
        "PCLKCR7",
        "PCLKCR8",
        "PCLKCR9",
        "PCLKCR10",
        "PCLKCR13",
        "PCLKCR14"
      ],
      "registersUsedMatchingBifield": [
        "PCLKCR0",
        "PCLKCR2",
        "PCLKCR3",
        "PCLKCR4",
        "PCLKCR7",
        "PCLKCR8",
        "PCLKCR9",
        "PCLKCR10",
        "PCLKCR13",
        "PCLKCR14"
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
        "RESCCLR",
        "RESC"
      ],
      "registersUsedMatchingBifield": [
        "RESCCLR",
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
      "functionName": "SysCtl_setExternalOscMode",
      "functionArgs": [
        "mode"
      ],
      "functionArgsTypes": [
        "SysCtl_ExternalOscMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "XTALCR"
      ],
      "registersUsedMatchingBifield": [
        "XTALCR"
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
      "functionName": "SysCtl_clearExternalOscCounterValue",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
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
        "XTALCR"
      ],
      "registersUsedMatchingBifield": [
        "XTALCR"
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
        "XTALCR"
      ],
      "registersUsedMatchingBifield": [
        "XTALCR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setIntOSC2_Mode",
      "functionArgs": [
        "mode"
      ],
      "functionArgsTypes": [
        "SysCtl_IntOSC2_Mode"
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
        "LPMCR"
      ],
      "registersUsedMatchingBifield": [
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
      "functionName": "SysCtl_setWatchdogPredivider",
      "functionArgs": [
        "predivider"
      ],
      "functionArgsTypes": [
        "SysCtl_WDPredivider"
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
        "RESCCLR",
        "RESC"
      ],
      "registersUsedMatchingBifield": [
        "RESCCLR",
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
      "functionName": "SysCtl_simulateReset",
      "functionArgs": [
        "rstCauses"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SIMRESET"
      ],
      "registersUsedMatchingBifield": [
        "SIMRESET"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getInterruptStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "SYS_ERR_INT_FLG"
      ],
      "registersUsedMatchingBifield": [
        "SYS_ERR_INT_FLG"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_clearInterruptStatus",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYS_ERR_INT_CLR"
      ],
      "registersUsedMatchingBifield": [
        "SYS_ERR_INT_CLR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setInterruptStatus",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYS_ERR_INT_SET"
      ],
      "registersUsedMatchingBifield": [
        "SYS_ERR_INT_SET"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getInterruptStatusMask",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "SYS_ERR_MASK"
      ],
      "registersUsedMatchingBifield": [
        "SYS_ERR_MASK"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setInterruptStatusMask",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SYS_ERR_MASK"
      ],
      "registersUsedMatchingBifield": [
        "SYS_ERR_MASK"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_isErrorTriggered",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "ERRORSTS"
      ],
      "registersUsedMatchingBifield": [
        "ERRORSTS"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getErrorPinStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "ERRORSTS"
      ],
      "registersUsedMatchingBifield": [
        "ERRORSTS"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_forceError",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ERRORSTS",
        "ERRORSTSFRC"
      ],
      "registersUsedMatchingBifield": [
        "ERRORSTS",
        "ERRORSTSFRC"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_clearError",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ERRORSTS",
        "ERRORSTSCLR"
      ],
      "registersUsedMatchingBifield": [
        "ERRORSTS",
        "ERRORSTSCLR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_selectErrPinPolarity",
      "functionArgs": [
        "pol"
      ],
      "functionArgsTypes": [
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ERRORCTL"
      ],
      "registersUsedMatchingBifield": [
        "ERRORCTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_lockErrControl",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ERRORLOCK"
      ],
      "registersUsedMatchingBifield": [
        "ERRORLOCK"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setUserRegister",
      "functionArgs": [
        "reg",
        "value"
      ],
      "functionArgsTypes": [
        "SysCtl_UserRegister",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "USER_REG1_SYSRSN"
      ],
      "registersUsedMatchingBifield": [
        "USER_REG1_SYSRSN"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getUserRegister",
      "functionArgs": [
        "reg"
      ],
      "functionArgsTypes": [
        "SysCtl_UserRegister"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "USER_REG1_SYSRSN"
      ],
      "registersUsedMatchingBifield": [
        "USER_REG1_SYSRSN"
      ]
    }
  ]
}
module.exports = { 
  sysctl_driverlib: sysctl_driverlib,
}
