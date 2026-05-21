let spi_driverlib = 
{
  "name": "spi",
  "functions": [
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_setConfig",
      "functionArgs": [
        "base",
        "lspclkHz",
        "protocol",
        "mode",
        "bitRate",
        "dataWidth"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "SPI_TransferProtocol",
        "SPI_Mode",
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CCR",
        "CTL",
        "BRR"
      ],
      "registersUsedMatchingBifield": [
        "SPICCR",
        "SPICTL",
        "SPIBRR"
      ]
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_setBaudRate",
      "functionArgs": [
        "base",
        "lspclkHz",
        "bitRate"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "BRR"
      ],
      "registersUsedMatchingBifield": [
        "SPIBRR"
      ]
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_enableInterrupt",
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
        "CTL",
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SPICTL",
        "SPIFFTX",
        "SPIFFRX"
      ]
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_disableInterrupt",
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
        "CTL",
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SPICTL",
        "SPIFFTX",
        "SPIFFRX"
      ]
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_getInterruptStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "STS",
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SPISTS",
        "SPIFFTX",
        "SPIFFRX"
      ]
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_clearInterruptStatus",
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
        "CCR",
        "STS",
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SPICCR",
        "SPISTS",
        "SPIFFTX",
        "SPIFFRX"
      ]
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_pollingNonFIFOTransaction",
      "functionArgs": [
        "base",
        "charLength",
        "data"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_pollingFIFOTransaction",
      "functionArgs": [
        "base",
        "charLength",
        "*pTxBuffer",
        "*pRxBuffer",
        "numOfWords",
        "txDelay"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t",
        "uint16_t",
        "uint16_t",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_transmit24Bits",
      "functionArgs": [
        "base",
        "data",
        "txDelay"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_receive16Bits",
      "functionArgs": [
        "base",
        "endianness",
        "dummyData",
        "txDelay"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "SPI_endianess",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_receive24Bits",
      "functionArgs": [
        "base",
        "endianness",
        "dummyData",
        "txDelay"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "SPI_endianess",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_transmit32Bits",
      "functionArgs": [
        "base",
        "data",
        "txDelay"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "void",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "spi.c",
      "peripheral": "spi",
      "functionName": "SPI_receive32Bits",
      "functionArgs": [
        "base",
        "endianness",
        "dummyData",
        "txDelay"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "SPI_endianess",
        "uint16_t",
        "uint16_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_isBaseValid",
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
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_enableModule",
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
        "SPICCR"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_disableModule",
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
        "SPICCR"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_setcharLength",
      "functionArgs": [
        "base",
        "charLength"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CCR"
      ],
      "registersUsedMatchingBifield": [
        "SPICCR"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_enableFIFO",
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
        "SPIFFTX",
        "SPIFFRX"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_disableFIFO",
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
        "SPIFFTX",
        "SPIFFRX"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_resetTxFIFO",
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
        "SPIFFTX"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_resetRxFIFO",
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
        "SPIFFRX"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_setFIFOInterruptLevel",
      "functionArgs": [
        "base",
        "txLevel",
        "rxLevel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "SPI_TxFIFOLevel",
        "SPI_RxFIFOLevel"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SPIFFTX",
        "SPIFFRX"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_getFIFOInterruptLevel",
      "functionArgs": [
        "base",
        "*txLevel",
        "*rxLevel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "SPI_TxFIFOLevel",
        "SPI_RxFIFOLevel"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFTX",
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SPIFFTX",
        "SPIFFRX"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_getTxFIFOStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline SPI_TxFIFOLevel",
      "registersUsed": [
        "FFTX"
      ],
      "registersUsedMatchingBifield": [
        "SPIFFTX"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_getRxFIFOStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline SPI_RxFIFOLevel",
      "registersUsed": [
        "FFRX"
      ],
      "registersUsedMatchingBifield": [
        "SPIFFRX"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_isBusy",
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
        "SPIFFTX"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_writeDataNonBlocking",
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
        "SPITXBUF"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_readDataNonBlocking",
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
        "SPIRXBUF"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_writeDataBlockingFIFO",
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
        "SPITXBUF"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_readDataBlockingFIFO",
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
        "SPIRXBUF"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_writeDataBlockingNonFIFO",
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
        "STS",
        "TXBUF"
      ],
      "registersUsedMatchingBifield": [
        "SPISTS",
        "SPITXBUF"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_readDataBlockingNonFIFO",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "STS",
        "RXBUF"
      ],
      "registersUsedMatchingBifield": [
        "SPISTS",
        "SPIRXBUF"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_enableTriWire",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PRI"
      ],
      "registersUsedMatchingBifield": [
        "SPIPRI"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_disableTriWire",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PRI"
      ],
      "registersUsedMatchingBifield": [
        "SPIPRI"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_enableLoopback",
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
        "SPICCR"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_disableLoopback",
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
        "SPICCR"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_setSTESignalPolarity",
      "functionArgs": [
        "base",
        "polarity"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "SPI_STEPolarity"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PRI"
      ],
      "registersUsedMatchingBifield": [
        "SPIPRI"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_enableHighSpeedMode",
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
        "SPICCR"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_disableHighSpeedMode",
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
        "SPICCR"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_setEmulationMode",
      "functionArgs": [
        "base",
        "mode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "SPI_EmulationMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PRI"
      ],
      "registersUsedMatchingBifield": [
        "SPIPRI"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_setTxFifoTransmitDelay",
      "functionArgs": [
        "base",
        "delay"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "FFCT"
      ],
      "registersUsedMatchingBifield": [
        "SPIFFCT"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_readRxEmulationBuffer",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RXEMU"
      ],
      "registersUsedMatchingBifield": [
        "SPIRXEMU"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_enableTalk",
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
        "SPICTL"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_disableTalk",
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
        "SPICTL"
      ]
    },
    {
      "file": "spi.h",
      "peripheral": "spi",
      "functionName": "SPI_reset",
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
        "SPIFFTX"
      ]
    }
  ]
}
module.exports = { 
  spi_driverlib: spi_driverlib,
}
