let escss_driverlib = 
{
  "name": "escss",
  "functions": [
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_setRawInterruptStatus",
      "functionArgs": [
        "base",
        "interruptMask",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "INTR_SET"
      ],
      "registersUsedMatchingBifield": [
        "INTR_SET"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_setGPINGroupCaptureTriggerSelect",
      "functionArgs": [
        "base",
        "selectGPIN",
        "triggerCapSelect"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ESCSS_GroupCaptureSelect",
        "ESCSS_CaptureTrigger"
      ],
      "returnType": "void",
      "registersUsed": [
        "GPIN_GRP_CAP_SEL"
      ],
      "registersUsedMatchingBifield": [
        "GPIN_GRP_CAP_SEL"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_setGPOUTGroupCaptureTriggerSelect",
      "functionArgs": [
        "base",
        "selectGPOUT",
        "triggerCapSelect"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ESCSS_GroupCaptureSelect",
        "ESCSS_CaptureTrigger"
      ],
      "returnType": "void",
      "registersUsed": [
        "GPOUT_GRP_CAP_SEL"
      ],
      "registersUsedMatchingBifield": [
        "GPOUT_GRP_CAP_SEL"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableCPUReset",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "RESET_DEST_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "RESET_DEST_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_disableCPUReset",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "RESET_DEST_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "RESET_DEST_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableResetToNMI",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "RESET_DEST_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "RESET_DEST_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_disableResetToNMI",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "RESET_DEST_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "RESET_DEST_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableResetToInterrupt",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "RESET_DEST_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "RESET_DEST_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_disableResetToInterrupt",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "RESET_DEST_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "RESET_DEST_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_configureSync0Connections",
      "functionArgs": [
        "base",
        "connectionInterrupt",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "SYNC0_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "SYNC0_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_configureSync1Connections",
      "functionArgs": [
        "base",
        "connectionInterrupt",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "SYNC1_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "SYNC1_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableConfigurationLock",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "CONFIG_LOCK"
      ],
      "registersUsedMatchingBifield": [
        "CONFIG_LOCK"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableIOConnectionLock",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "CONFIG_LOCK"
      ],
      "registersUsedMatchingBifield": [
        "CONFIG_LOCK"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_disableIOConnectionLock",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "CONFIG_LOCK"
      ],
      "registersUsedMatchingBifield": [
        "CONFIG_LOCK"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableResetInputFromGpioPad",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "MISC_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "MISC_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_disableResetInputFromGpioPad",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "MISC_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "MISC_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableESCEEPROMI2CIoPadConnection",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "MISC_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "MISC_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_disableESCEEPROMI2CIoPadConnection",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "MISC_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "MISC_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_configurePortCount",
      "functionArgs": [
        "base",
        "portConfig",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ESCSS_PortSelection",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "PHY_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "PHY_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableAutoCompensationTxClkIOPad",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "PHY_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "PHY_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_disableAutoCompensationTxClkIOPad",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "PHY_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "PHY_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableSync0GpioMuxConnection",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "SYNC_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "SYNC_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_disableSync0GpioMuxConnection",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "SYNC_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "SYNC_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableSync1GpioMuxConnection",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "SYNC_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "SYNC_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_disableSync1GpioMuxConnection",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "SYNC_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "SYNC_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableLatch0GpioMuxConnection",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "LATCH_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "LATCH_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_disableLatch0GpioMuxConnection",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "LATCH_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "LATCH_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_enableLatch1GpioMuxConnection",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "LATCH_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "LATCH_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_disableLatch1GpioMuxConnection",
      "functionArgs": [
        "base",
        "writeKey"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "LATCH_IO_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "LATCH_IO_CONFIG"
      ]
    },
    {
      "file": "escss.c",
      "peripheral": "escss",
      "functionName": "ESCSS_configureEEPROMSize",
      "functionArgs": [
        "base",
        "eepromSize"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ESCSS_SizeSelect"
      ],
      "returnType": "void",
      "registersUsed": [
        "MISC_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "MISC_CONFIG"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_isBaseValid",
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
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_isConfigBaseValid",
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
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_readIPMinorRevNumber",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "IPREVNUM"
      ],
      "registersUsedMatchingBifield": [
        "IPREVNUM"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_readIPMajorRevNumber",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "IPREVNUM"
      ],
      "registersUsedMatchingBifield": [
        "IPREVNUM"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_readIPRevNumber",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "IPREVNUM"
      ],
      "registersUsedMatchingBifield": [
        "IPREVNUM"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_getRawInterruptStatus",
      "functionArgs": [
        "base",
        "interruptMask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "INTR_RIS"
      ],
      "registersUsedMatchingBifield": [
        "INTR_RIS"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_readRawInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "INTR_RIS"
      ],
      "registersUsedMatchingBifield": [
        "INTR_RIS"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_setMaskedInterruptStatus",
      "functionArgs": [
        "base",
        "interruptMask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTR_MASK"
      ],
      "registersUsedMatchingBifield": [
        "INTR_MASK"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_resetMaskedInterruptStatus",
      "functionArgs": [
        "base",
        "interruptMask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTR_MASK"
      ],
      "registersUsedMatchingBifield": [
        "INTR_MASK"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_getMaskedInterruptStatus",
      "functionArgs": [
        "base",
        "interruptMask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "INTR_MIS"
      ],
      "registersUsedMatchingBifield": [
        "INTR_MIS"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_clearRawInterruptStatus",
      "functionArgs": [
        "base",
        "interruptMask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTR_CLR"
      ],
      "registersUsedMatchingBifield": [
        "INTR_CLR"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_selectLatch0Mux",
      "functionArgs": [
        "base",
        "muxSelectValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ESCSS_LatchTrigger"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LATCH_SEL"
      ],
      "registersUsedMatchingBifield": [
        "LATCH_SEL"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_selectLatch1Mux",
      "functionArgs": [
        "base",
        "muxSelectValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ESCSS_LatchTrigger"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LATCH_SEL"
      ],
      "registersUsedMatchingBifield": [
        "LATCH_SEL"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_configure16BitAsyncAccessWaitState",
      "functionArgs": [
        "base",
        "waitState"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ACCESS_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "ACCESS_CTRL"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_enablePDIAccessTimeOut",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ACCESS_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "ACCESS_CTRL"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_disablePDIAccessTimeOut",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ACCESS_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "ACCESS_CTRL"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_enableDebugAccess",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ACCESS_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "ACCESS_CTRL"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_disableDebugAccess",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ACCESS_CTRL"
      ],
      "registersUsedMatchingBifield": [
        "ACCESS_CTRL"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_readGPINData",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "GPIN_DAT"
      ],
      "registersUsedMatchingBifield": [
        "GPIN_DAT"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_setGPINData",
      "functionArgs": [
        "base",
        "pinValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPIN_DAT"
      ],
      "registersUsedMatchingBifield": [
        "GPIN_DAT"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_resetGPINData",
      "functionArgs": [
        "base",
        "pinValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPIN_DAT"
      ],
      "registersUsedMatchingBifield": [
        "GPIN_DAT"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_enableGPIPipelinedRegCaptureOnEvent",
      "functionArgs": [
        "base",
        "pipelineMask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPIN_PIPE"
      ],
      "registersUsedMatchingBifield": [
        "GPIN_PIPE"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_disableGPIPipelinedRegCaptureOnEvent",
      "functionArgs": [
        "base",
        "pipelineMask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPIN_PIPE"
      ],
      "registersUsedMatchingBifield": [
        "GPIN_PIPE"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_readGPOUTData",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "GPOUT_DAT"
      ],
      "registersUsedMatchingBifield": [
        "GPOUT_DAT"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_enableGPOUTPipelinedRegCaptureOnEvent",
      "functionArgs": [
        "base",
        "pipelineMask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPOUT_PIPE"
      ],
      "registersUsedMatchingBifield": [
        "GPOUT_PIPE"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_disableGPOUTPipelinedRegCaptureOnEvent",
      "functionArgs": [
        "base",
        "pipelineMask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GPOUT_PIPE"
      ],
      "registersUsedMatchingBifield": [
        "GPOUT_PIPE"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_initMemory",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MEM_TEST"
      ],
      "registersUsedMatchingBifield": [
        "MEM_TEST"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_getMemoryInitDoneStatusNonBlocking",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "MEM_TEST"
      ],
      "registersUsedMatchingBifield": [
        "MEM_TEST"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_getMemoryInitDoneStatusBlocking",
      "functionArgs": [
        "base",
        "loopCount"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "MEM_TEST"
      ],
      "registersUsedMatchingBifield": [
        "MEM_TEST"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_isConfigurationLockEnabled",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CONFIG_LOCK"
      ],
      "registersUsedMatchingBifield": [
        "CONFIG_LOCK"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_enableLEDOptions",
      "functionArgs": [
        "base",
        "ledSelectConfig"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "LED_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "LED_CONFIG"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_disableLEDOptions",
      "functionArgs": [
        "base",
        "ledSelectConfig"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "LED_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "LED_CONFIG"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_enableGPIN",
      "functionArgs": [
        "base",
        "selectValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "GPIN_SEL"
      ],
      "registersUsedMatchingBifield": [
        "GPIN_SEL"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_disableGPIN",
      "functionArgs": [
        "base",
        "selectValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "GPIN_SEL"
      ],
      "registersUsedMatchingBifield": [
        "GPIN_SEL"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_enableGPOUT",
      "functionArgs": [
        "base",
        "selectValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "GPOUT_SEL"
      ],
      "registersUsedMatchingBifield": [
        "GPOUT_SEL"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_disableGPOUT",
      "functionArgs": [
        "base",
        "selectValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "GPOUT_SEL"
      ],
      "registersUsedMatchingBifield": [
        "GPOUT_SEL"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_configureTX0ShiftForTxEnaAndTxData",
      "functionArgs": [
        "base",
        "shiftValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MISC_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "MISC_CONFIG"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_configureTX1ShiftForTxEnaAndTxData",
      "functionArgs": [
        "base",
        "shiftValue"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MISC_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "MISC_CONFIG"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_enablePDIEmulation",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MISC_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "MISC_CONFIG"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_disablePDIEmulation",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MISC_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "MISC_CONFIG"
      ]
    },
    {
      "file": "escss.h",
      "peripheral": "escss",
      "functionName": "ESCSS_configurePhyAddressOffset",
      "functionArgs": [
        "base",
        "registerOffset"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MISC_CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "MISC_CONFIG"
      ]
    }
  ]
}
module.exports = { 
  escss_driverlib: escss_driverlib,
}
