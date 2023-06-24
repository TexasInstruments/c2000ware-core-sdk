let sci_driverlib = 
{
  "name": "sci",
  "functions": [
    {
      "file": "sci.c",
      "peripheral": "sci",
      "functionName": "SCI_setConfig",
      "functionArgs": [
        "base",
        "lspclkHz",
        "baud",
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CCR",
        "HBAUD",
        "LBAUD"
      ],
      "registersUsedMatchingBifield": [
        "SCICCR",
        "SCIHBAUD",
        "SCILBAUD"
      ]
    },
    {
      "file": "sci.c",
      "peripheral": "sci",
      "functionName": "SCI_writeCharArray",
      "functionArgs": [
        "base",
        "array",
        "length"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "constuint16_t*const",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXBUF"
      ],
      "registersUsedMatchingBifield": [
        "SCITXBUF"
      ]
    },
    {
      "file": "sci.c",
      "peripheral": "sci",
      "functionName": "SCI_readCharArray",
      "functionArgs": [
        "base",
        "array",
        "length"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t*const",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "RXBUF"
      ],
      "registersUsedMatchingBifield": [
        "SCIRXBUF"
      ]
    },
    {
      "file": "sci.c",
      "peripheral": "sci",
      "functionName": "SCI_enableInterrupt",
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
        "CTL1",
        "CTL2",
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SCICTL1",
        "SCICTL2",
        "SCIFFTX",
        "SCIFFRX"
      ]
    },
    {
      "file": "sci.c",
      "peripheral": "sci",
      "functionName": "SCI_disableInterrupt",
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
        "CTL1",
        "CTL2",
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SCICTL1",
        "SCICTL2",
        "SCIFFTX",
        "SCIFFRX"
      ]
    },
    {
      "file": "sci.c",
      "peripheral": "sci",
      "functionName": "SCI_getInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "CTL2",
        "RXST",
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SCICTL2",
        "SCIRXST",
        "SCIFFTX",
        "SCIFFRX"
      ]
    },
    {
      "file": "sci.c",
      "peripheral": "sci",
      "functionName": "SCI_clearInterruptStatus",
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
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFTX",
        "SCIFFRX"
      ]
    },
    {
      "file": "sci.c",
      "peripheral": "sci",
      "functionName": "SCI_setBaud",
      "functionArgs": [
        "base",
        "lspclkHz",
        "baud"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "HBAUD",
        "LBAUD"
      ],
      "registersUsedMatchingBifield": [
        "SCIHBAUD",
        "SCILBAUD"
      ]
    },
    {
      "file": "sci.c",
      "peripheral": "sci",
      "functionName": "SCI_setWakeFlag",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTL1"
      ],
      "registersUsedMatchingBifield": [
        "SCICTL1"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_isBaseValid",
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
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_setParityMode",
      "functionArgs": [
        "base",
        "parity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "SCI_ParityType"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CCR"
      ],
      "registersUsedMatchingBifield": [
        "SCICCR"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_getParityMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline SCI_ParityType",
      "registersUsed": [
        "CCR"
      ],
      "registersUsedMatchingBifield": [
        "SCICCR"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_setAddrMultiProcessorMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CCR"
      ],
      "registersUsedMatchingBifield": [
        "SCICCR"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_setIdleMultiProcessorMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CCR"
      ],
      "registersUsedMatchingBifield": [
        "SCICCR"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_lockAutobaud",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HBAUD",
        "LBAUD",
        "FFCT"
      ],
      "registersUsedMatchingBifield": [
        "SCIHBAUD",
        "SCILBAUD",
        "SCIFFCT"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_setFIFOInterruptLevel",
      "functionArgs": [
        "base",
        "txLevel",
        "rxLevel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "SCI_TxFIFOLevel",
        "SCI_RxFIFOLevel"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFTX",
        "SCIFFRX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_getFIFOInterruptLevel",
      "functionArgs": [
        "base",
        "*txLevel",
        "*rxLevel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "SCI_TxFIFOLevel",
        "SCI_RxFIFOLevel"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFTX",
        "SCIFFRX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_getConfig",
      "functionArgs": [
        "base",
        "lspclkHz",
        "*baud",
        "*config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CCR",
        "HBAUD",
        "LBAUD"
      ],
      "registersUsedMatchingBifield": [
        "SCICCR",
        "SCIHBAUD",
        "SCILBAUD"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_enableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL1"
      ],
      "registersUsedMatchingBifield": [
        "SCICTL1"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_disableModule",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL1",
        "FFTX"
      ],
      "registersUsedMatchingBifield": [
        "SCICTL1",
        "SCIFFTX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_enableFIFO",
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
        "SCIFFTX",
        "SCIFFRX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_disableFIFO",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFTX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFTX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_isFIFOEnabled",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "FFTX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFTX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_resetRxFIFO",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFRX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_resetTxFIFO",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFTX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFTX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_resetChannels",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFTX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFTX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_isDataAvailableNonFIFO",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "RXST"
      ],
      "registersUsedMatchingBifield": [
        "SCIRXST"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_isSpaceAvailableNonFIFO",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CTL2"
      ],
      "registersUsedMatchingBifield": [
        "SCICTL2"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_getTxFIFOStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline SCI_TxFIFOLevel",
      "registersUsed": [
        "FFTX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFTX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_getRxFIFOStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline SCI_RxFIFOLevel",
      "registersUsed": [
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFRX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_isTransmitterBusy",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CTL2",
        "FFTX"
      ],
      "registersUsedMatchingBifield": [
        "SCICTL2",
        "SCIFFTX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_writeCharBlockingFIFO",
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
        "TXBUF"
      ],
      "registersUsedMatchingBifield": [
        "SCITXBUF"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_writeCharBlockingNonFIFO",
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
        "TXBUF"
      ],
      "registersUsedMatchingBifield": [
        "SCITXBUF"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_writeCharNonBlocking",
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
        "TXBUF"
      ],
      "registersUsedMatchingBifield": [
        "SCITXBUF"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_getRxStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RXST"
      ],
      "registersUsedMatchingBifield": [
        "SCIRXST"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_readCharBlockingFIFO",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RXBUF"
      ],
      "registersUsedMatchingBifield": [
        "SCIRXBUF"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_readCharBlockingNonFIFO",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RXBUF"
      ],
      "registersUsedMatchingBifield": [
        "SCIRXBUF"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_readCharNonBlocking",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RXBUF"
      ],
      "registersUsedMatchingBifield": [
        "SCIRXBUF"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_performSoftwareReset",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL1"
      ],
      "registersUsedMatchingBifield": [
        "SCICTL1"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_enableLoopback",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CCR"
      ],
      "registersUsedMatchingBifield": [
        "SCICCR"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_disableLoopback",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CCR"
      ],
      "registersUsedMatchingBifield": [
        "SCICCR"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_getOverflowStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFRX"
      ]
    },
    {
      "file": "sci.h",
      "peripheral": "sci",
      "functionName": "SCI_clearOverflowStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SCIFFRX"
      ]
    }
  ]
}
module.exports = { 
  sci_driverlib: sci_driverlib,
}
