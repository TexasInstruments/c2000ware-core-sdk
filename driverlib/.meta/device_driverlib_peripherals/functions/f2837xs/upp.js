let upp_driverlib = 
{
  "name": "upp",
  "functions": [
    {
      "file": "upp.c",
      "peripheral": "upp",
      "functionName": "UPP_setDMAReadThreshold",
      "functionArgs": [
        "base",
        "channel",
        "size"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_DMAChannel",
        "UPP_ThresholdSize"
      ],
      "returnType": "void",
      "registersUsed": [
        "THCFG"
      ],
      "registersUsedMatchingBifield": [
        "THCFG"
      ]
    },
    {
      "file": "upp.c",
      "peripheral": "upp",
      "functionName": "UPP_setDMADescriptor",
      "functionArgs": [
        "base",
        "channel",
        "desc"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_DMAChannel",
        "constUPP_DMADescriptor*const"
      ],
      "returnType": "void",
      "registersUsed": [
        "CHIDESC0",
        "CHIDESC1",
        "CHIDESC2",
        "CHQDESC0",
        "CHQDESC1",
        "CHQDESC2"
      ],
      "registersUsedMatchingBifield": [
        "CHIDESC0",
        "CHIDESC1",
        "CHIDESC2",
        "CHQDESC0",
        "CHQDESC1",
        "CHQDESC2"
      ]
    },
    {
      "file": "upp.c",
      "peripheral": "upp",
      "functionName": "UPP_getDMAChannelStatus",
      "functionArgs": [
        "base",
        "channel",
        "status"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_DMAChannel",
        "UPP_DMAChannelStatus*const"
      ],
      "returnType": "void",
      "registersUsed": [
        "CHIST0",
        "CHIST1",
        "CHQST0",
        "CHQST1"
      ],
      "registersUsedMatchingBifield": [
        "CHIST0",
        "CHIST1",
        "CHQST0",
        "CHQST1"
      ]
    },
    {
      "file": "upp.c",
      "peripheral": "upp",
      "functionName": "UPP_isDescriptorPending",
      "functionArgs": [
        "base",
        "channel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_DMAChannel"
      ],
      "returnType": "bool",
      "registersUsed": [
        "CHIST2",
        "CHQST2"
      ],
      "registersUsedMatchingBifield": [
        "CHIST2",
        "CHQST2"
      ]
    },
    {
      "file": "upp.c",
      "peripheral": "upp",
      "functionName": "UPP_isDescriptorActive",
      "functionArgs": [
        "base",
        "channel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_DMAChannel"
      ],
      "returnType": "bool",
      "registersUsed": [
        "CHIST2",
        "CHQST2"
      ],
      "registersUsedMatchingBifield": [
        "CHIST2",
        "CHQST2"
      ]
    },
    {
      "file": "upp.c",
      "peripheral": "upp",
      "functionName": "UPP_getDMAFIFOWatermark",
      "functionArgs": [
        "base",
        "channel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_DMAChannel"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "CHIST2",
        "CHQST2"
      ],
      "registersUsedMatchingBifield": [
        "CHIST2",
        "CHQST2"
      ]
    },
    {
      "file": "upp.c",
      "peripheral": "upp",
      "functionName": "UPP_readRxMsgRAM",
      "functionArgs": [
        "rxBase",
        "array[]",
        "length",
        "offset"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "upp.c",
      "peripheral": "upp",
      "functionName": "UPP_writeTxMsgRAM",
      "functionArgs": [
        "txBase",
        "array[]",
        "length",
        "offset"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint16_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_isBaseValid",
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
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_isRxBaseValid",
      "functionArgs": [
        "rxBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef DEBUG  static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_isTxBaseValid",
      "functionArgs": [
        "txBase"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "#ifdef DEBUG  static inline bool",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_isDMAActive",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "PERCTL"
      ],
      "registersUsedMatchingBifield": [
        "PERCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_performSoftReset",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PERCTL"
      ],
      "registersUsedMatchingBifield": [
        "PERCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_enableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PERCTL"
      ],
      "registersUsedMatchingBifield": [
        "PERCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_disableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PERCTL"
      ],
      "registersUsedMatchingBifield": [
        "PERCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_enableEmulationMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PERCTL"
      ],
      "registersUsedMatchingBifield": [
        "PERCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_disableEmulationMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PERCTL"
      ],
      "registersUsedMatchingBifield": [
        "PERCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setEmulationMode",
      "functionArgs": [
        "base",
        "emuMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_EmulationMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PERCTL"
      ],
      "registersUsedMatchingBifield": [
        "PERCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setOperationMode",
      "functionArgs": [
        "base",
        "opMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_OperationMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CHCTL"
      ],
      "registersUsedMatchingBifield": [
        "CHCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setDataRate",
      "functionArgs": [
        "base",
        "dataRate"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_DataRate"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CHCTL"
      ],
      "registersUsedMatchingBifield": [
        "CHCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setTxSDRInterleaveMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_TxSDRInterleaveMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CHCTL"
      ],
      "registersUsedMatchingBifield": [
        "CHCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setDDRDemuxMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_DDRDemuxMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CHCTL"
      ],
      "registersUsedMatchingBifield": [
        "CHCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setControlSignalPolarity",
      "functionArgs": [
        "base",
        "waitPola",
        "enablePola",
        "startPola"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_SignalPolarity",
        "UPP_SignalPolarity",
        "UPP_SignalPolarity"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IFCFG"
      ],
      "registersUsedMatchingBifield": [
        "IFCFG"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setTxControlSignalMode",
      "functionArgs": [
        "base",
        "waitMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_SignalMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IFCFG"
      ],
      "registersUsedMatchingBifield": [
        "IFCFG"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setRxControlSignalMode",
      "functionArgs": [
        "base",
        "enableMode",
        "startMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_SignalMode",
        "UPP_SignalMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IFCFG"
      ],
      "registersUsedMatchingBifield": [
        "IFCFG"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setTxClockDivider",
      "functionArgs": [
        "base",
        "divider"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IFCFG"
      ],
      "registersUsedMatchingBifield": [
        "IFCFG"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setClockPolarity",
      "functionArgs": [
        "base",
        "clkPolarity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_ClockPolarity"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IFCFG"
      ],
      "registersUsedMatchingBifield": [
        "IFCFG"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_configTxIdleDataMode",
      "functionArgs": [
        "base",
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_TxIdleDataMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IFCFG"
      ],
      "registersUsedMatchingBifield": [
        "IFCFG"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setTxIdleValue",
      "functionArgs": [
        "base",
        "idleVal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "IFIVAL"
      ],
      "registersUsedMatchingBifield": [
        "IFIVAL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setTxThreshold",
      "functionArgs": [
        "base",
        "size"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_ThresholdSize"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "THCFG"
      ],
      "registersUsedMatchingBifield": [
        "THCFG"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_enableInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTENSET"
      ],
      "registersUsedMatchingBifield": [
        "INTENSET"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_disableInterrupt",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTENCLR"
      ],
      "registersUsedMatchingBifield": [
        "INTENCLR"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_getInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "ENINTST"
      ],
      "registersUsedMatchingBifield": [
        "ENINTST"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_getRawInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RAWINTST"
      ],
      "registersUsedMatchingBifield": [
        "RAWINTST"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_clearInterruptStatus",
      "functionArgs": [
        "base",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "ENINTST"
      ],
      "registersUsedMatchingBifield": [
        "ENINTST"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_enableGlobalInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GINTEN"
      ],
      "registersUsedMatchingBifield": [
        "GINTEN"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_disableGlobalInterrupt",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GINTEN"
      ],
      "registersUsedMatchingBifield": [
        "GINTEN"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_isInterruptGenerated",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "GINTFLG"
      ],
      "registersUsedMatchingBifield": [
        "GINTFLG"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_clearGlobalInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "GINTCLR"
      ],
      "registersUsedMatchingBifield": [
        "GINTCLR"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_enableInputDelay",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DLYCTL"
      ],
      "registersUsedMatchingBifield": [
        "DLYCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_disableInputDelay",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DLYCTL"
      ],
      "registersUsedMatchingBifield": [
        "DLYCTL"
      ]
    },
    {
      "file": "upp.h",
      "peripheral": "upp",
      "functionName": "UPP_setInputDelay",
      "functionArgs": [
        "base",
        "delay"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "UPP_InputDelay"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "DLYCTL"
      ],
      "registersUsedMatchingBifield": [
        "DLYCTL"
      ]
    }
  ]
}
module.exports = { 
  upp_driverlib: upp_driverlib,
}
