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
      "functionName": "SysCtl_setAuxClock",
      "functionArgs": [
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CLKSRCCTL2",
        "AUXPLLCTL1",
        "AUXPLLMULT",
        "AUXPLLSTS",
        "AUXCLKDIVSEL",
        "XTALCR"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL2",
        "AUXPLLCTL1",
        "AUXPLLMULT",
        "AUXPLLSTS",
        "AUXCLKDIVSEL",
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
        "CLKSRCCTL2",
        "XTALCR"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1",
        "CLKSRCCTL2",
        "XTALCR"
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
        "pllclk",
        "pllMultDiv"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "SysCtl_PLLClockSource",
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
      "functionName": "SysCtl_controlCPU2Reset",
      "functionArgs": [
        "control"
      ],
      "functionArgsTypes": [
        "SysCtl_CoreReset"
      ],
      "returnType": "void",
      "registersUsed": [
        "CPU2RESCTL"
      ],
      "registersUsedMatchingBifield": [
        "CPU2RESCTL"
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
        "USBTYPE",
        "ECAPTYPE",
        "SDFMTYPE",
        "MEMMAPTYPE"
      ],
      "registersUsedMatchingBifield": [
        "USBTYPE",
        "ECAPTYPE",
        "SDFMTYPE",
        "MEMMAPTYPE"
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
        "USBTYPE",
        "ECAPTYPE",
        "SDFMTYPE",
        "MEMMAPTYPE"
      ],
      "registersUsedMatchingBifield": [
        "USBTYPE",
        "ECAPTYPE",
        "SDFMTYPE",
        "MEMMAPTYPE"
      ]
    },
    {
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setSemOwner",
      "functionArgs": [
        "cpuInst"
      ],
      "functionArgsTypes": [
        "SysCtl_CPUSel"
      ],
      "returnType": "void",
      "registersUsed": [
        "CLKSEM"
      ],
      "registersUsedMatchingBifield": [
        "CLKSEM"
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
      "file": "sysctl.c",
      "peripheral": "sysctl",
      "functionName": "SysCtl_controlCMReset",
      "functionArgs": [
        "control"
      ],
      "functionArgsTypes": [
        "SysCtl_CoreReset"
      ],
      "returnType": "void",
      "registersUsed": [
        "CMRESCTL"
      ],
      "registersUsedMatchingBifield": [
        "CMRESCTL"
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
        "SOFTPRES10",
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
        "SOFTPRES10",
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
        "CLKSRCCTL1",
        "XTALCR"
      ],
      "registersUsedMatchingBifield": [
        "CLKSRCCTL1",
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
      "functionName": "SysCtl_lockAccessControlRegs",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PERIPH_AC_LOCK"
      ],
      "registersUsedMatchingBifield": [
        "PERIPH_AC_LOCK"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setPeripheralAccessControl",
      "functionArgs": [
        "peripheral",
        "master",
        "permission"
      ],
      "functionArgsTypes": [
        "SysCtl_AccessPeripheral",
        "SysCtl_AccessMaster",
        "SysCtl_AccessPermission"
      ],
      "returnType": "static inline void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getPeripheralAccessControl",
      "functionArgs": [
        "peripheral",
        "master"
      ],
      "functionArgsTypes": [
        "SysCtl_AccessPeripheral",
        "SysCtl_AccessMaster"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
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
      "functionName": "SysCtl_selectCPUForPeripheralInstance",
      "functionArgs": [
        "peripheral",
        "cpuInst"
      ],
      "functionArgsTypes": [
        "SysCtl_CPUSelPeriphInstance",
        "SysCtl_CPUSel"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CPUSEL0",
        "CPUSEL1",
        "CPUSEL2",
        "CPUSEL4",
        "CPUSEL5",
        "CPUSEL6",
        "CPUSEL7",
        "CPUSEL8",
        "CPUSEL9",
        "CPUSEL11",
        "CPUSEL12",
        "CPUSEL14",
        "CPUSEL15",
        "CPUSEL16"
      ],
      "registersUsedMatchingBifield": [
        "CPUSEL0",
        "CPUSEL1",
        "CPUSEL2",
        "CPUSEL4",
        "CPUSEL5",
        "CPUSEL6",
        "CPUSEL7",
        "CPUSEL8",
        "CPUSEL9",
        "CPUSEL11",
        "CPUSEL12",
        "CPUSEL14",
        "CPUSEL15",
        "CPUSEL16"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_selectCPUForPeripheral",
      "functionArgs": [
        "peripheral",
        "peripheralInst",
        "cpuInst"
      ],
      "functionArgsTypes": [
        "SysCtl_CPUSelPeripheral",
        "uint16_t",
        "SysCtl_CPUSel"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CPUSEL0",
        "CPUSEL1",
        "CPUSEL2",
        "CPUSEL4",
        "CPUSEL5",
        "CPUSEL6",
        "CPUSEL7",
        "CPUSEL8",
        "CPUSEL9",
        "CPUSEL11",
        "CPUSEL12",
        "CPUSEL14",
        "CPUSEL15",
        "CPUSEL16"
      ],
      "registersUsedMatchingBifield": [
        "CPUSEL0",
        "CPUSEL1",
        "CPUSEL2",
        "CPUSEL4",
        "CPUSEL5",
        "CPUSEL6",
        "CPUSEL7",
        "CPUSEL8",
        "CPUSEL9",
        "CPUSEL11",
        "CPUSEL12",
        "CPUSEL14",
        "CPUSEL15",
        "CPUSEL16"
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
      "functionName": "SysCtl_lockCPUSelectRegs",
      "functionArgs": [
        "peripheral"
      ],
      "functionArgsTypes": [
        "SysCtl_CPUSelPeripheral"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DEVCFGLOCK1"
      ],
      "registersUsedMatchingBifield": [
        "DEVCFGLOCK1"
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
      "functionName": "SysCtl_readADCWrapper",
      "functionArgs": [
        "peripheral"
      ],
      "functionArgsTypes": [
        "SysCtl_SelADC"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "PERCNF1"
      ],
      "registersUsedMatchingBifield": [
        "PERCNF1"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_isCPU2Reset",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "RSTSTAT"
      ],
      "registersUsedMatchingBifield": [
        "RSTSTAT"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getCPU2ResetStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RSTSTAT"
      ],
      "registersUsedMatchingBifield": [
        "RSTSTAT"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_clearCPU2ResetStatus",
      "functionArgs": [
        ""
      ],
      "functionArgsTypes": [
        "uint16_trstCauses"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "RSTSTAT"
      ],
      "registersUsedMatchingBifield": [
        "RSTSTAT"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getCPU2LPMStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "LPMSTAT"
      ],
      "registersUsedMatchingBifield": [
        "LPMSTAT"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getSemOwner",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "CLKSEM"
      ],
      "registersUsedMatchingBifield": [
        "CLKSEM"
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
      "functionName": "SysCtl_setCMClk",
      "functionArgs": [
        "divider",
        "source"
      ],
      "functionArgsTypes": [
        "SysCtl_CMClkDivider",
        "SysCtl_PLLClockSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMCLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "CMCLKCTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setEnetClk",
      "functionArgs": [
        "divider",
        "source"
      ],
      "functionArgsTypes": [
        "SysCtl_EnetClkDivider",
        "SysCtl_PLLClockSource"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMCLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "CMCLKCTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setECatClk",
      "functionArgs": [
        "divider",
        "source",
        "enable"
      ],
      "functionArgsTypes": [
        "SysCtl_ECatClkDivider",
        "SysCtl_PLLClockSource",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ETHERCATCLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "ETHERCATCLKCTL"
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
      "functionName": "SysCtl_setMCANClk",
      "functionArgs": [
        "divider"
      ],
      "functionArgsTypes": [
        "SysCtl_MCANClkDivider"
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
      "functionName": "SysCtl_isCMReset",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CMRESCTL"
      ],
      "registersUsedMatchingBifield": [
        "CMRESCTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enableCMtoCPUNMI",
      "functionArgs": [
        "Flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMTOCPU1NMICTL"
      ],
      "registersUsedMatchingBifield": [
        "CMTOCPU1NMICTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_disableCMtoCPUNMI",
      "functionArgs": [
        "Flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMTOCPU1NMICTL"
      ],
      "registersUsedMatchingBifield": [
        "CMTOCPU1NMICTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getCMtoCPUNMI",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "CMTOCPU1NMICTL"
      ],
      "registersUsedMatchingBifield": [
        "CMTOCPU1NMICTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_enableCMtoCPUInterrupt",
      "functionArgs": [
        "Flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMTOCPU1INTCTL"
      ],
      "registersUsedMatchingBifield": [
        "CMTOCPU1INTCTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_disableCMtoCPUInterrupt",
      "functionArgs": [
        "Flags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CMTOCPU1INTCTL"
      ],
      "registersUsedMatchingBifield": [
        "CMTOCPU1INTCTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getCMtoCPUInterrupt",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "CMTOCPU1INTCTL"
      ],
      "registersUsedMatchingBifield": [
        "CMTOCPU1INTCTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_allocateSharedPeripheral",
      "functionArgs": [
        "peripheral",
        "allocate"
      ],
      "functionArgsTypes": [
        "SysCtl_SharedPeripheral",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PALLOCATE0"
      ],
      "registersUsedMatchingBifield": [
        "PALLOCATE0"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_lockCMConfig",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CM_CONF_REGS_LOCK"
      ],
      "registersUsedMatchingBifield": [
        "CM_CONF_REGS_LOCK"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getCMInterruptStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CM_STATUS_INT_FLG"
      ],
      "registersUsedMatchingBifield": [
        "CM_STATUS_INT_FLG"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_clearCMInterruptStatus",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CM_STATUS_INT_CLR"
      ],
      "registersUsedMatchingBifield": [
        "CM_STATUS_INT_CLR"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setCMInterruptStatus",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CM_STATUS_INT_SET"
      ],
      "registersUsedMatchingBifield": [
        "CM_STATUS_INT_SET"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_getCMInterruptStatusMask",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "CM_STATUS_MASK"
      ],
      "registersUsedMatchingBifield": [
        "CM_STATUS_MASK"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setCMInterruptStatusMask",
      "functionArgs": [
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CM_STATUS_MASK"
      ],
      "registersUsedMatchingBifield": [
        "CM_STATUS_MASK"
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
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setCLBClk",
      "functionArgs": [
        "divider",
        "tdivider",
        "inst",
        "config"
      ],
      "functionArgsTypes": [
        "SysCtl_CLBClkDivider",
        "SysCtl_CLBTClkDivider",
        "SysCtl_CLBInst",
        "SysCtl_CLBClkm"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLBCLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "CLBCLKCTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_setCLBClkDivider",
      "functionArgs": [
        "divider",
        "tdivider"
      ],
      "functionArgsTypes": [
        "SysCtl_CLBClkDivider",
        "SysCtl_CLBTClkDivider"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLBCLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "CLBCLKCTL"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_CLBClkConfig",
      "functionArgs": [
        "inst",
        "config"
      ],
      "functionArgsTypes": [
        "SysCtl_CLBInst",
        "SysCtl_CLBClkm"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CLBCLKCTL"
      ],
      "registersUsedMatchingBifield": [
        "CLBCLKCTL"
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
      "functionName": "SysCtl_isMCANWakeStatusSet",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "MCANWAKESTATUS"
      ],
      "registersUsedMatchingBifield": [
        "MCANWAKESTATUS"
      ]
    },
    {
      "file": "sysctl.h",
      "peripheral": "sysctl",
      "functionName": "SysCtl_clearMCANWakeStatus",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCANWAKESTATUS",
        "MCANWAKESTATUSCLR"
      ],
      "registersUsedMatchingBifield": [
        "MCANWAKESTATUS",
        "MCANWAKESTATUSCLR"
      ]
    }
  ]
}
module.exports = { 
  sysctl_driverlib: sysctl_driverlib,
}
