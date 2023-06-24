let usb_driverlib = 
{
  "name": "usb",
  "functions": [
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBIndexWrite",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32IndexedReg",
        "ui32Value",
        "ui32Size"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static void  _",
      "registersUsed": [
        "EPIDX"
      ],
      "registersUsedMatchingBifield": [
        "EPIDX"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBIndexRead",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32IndexedReg",
        "ui32Size"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static uint32_t  _",
      "registersUsed": [
        "EPIDX"
      ],
      "registersUsedMatchingBifield": [
        "EPIDX"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostSuspend",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "POWER"
      ],
      "registersUsedMatchingBifield": [
        "POWER"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostReset",
      "functionArgs": [
        "ui32Base",
        "bStart"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool"
      ],
      "returnType": "void",
      "registersUsed": [
        "POWER"
      ],
      "registersUsedMatchingBifield": [
        "POWER"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostResume",
      "functionArgs": [
        "ui32Base",
        "bStart"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool"
      ],
      "returnType": "void",
      "registersUsed": [
        "POWER"
      ],
      "registersUsedMatchingBifield": [
        "POWER"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostSpeedGet",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "DEVCTL"
      ],
      "registersUsedMatchingBifield": [
        "DEVCTL"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBIntDisableControl",
      "functionArgs": [
        "ui32Base",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IE",
        "EPC",
        "EPCIM",
        "IDVIM"
      ],
      "registersUsedMatchingBifield": [
        "IE",
        "EPC",
        "EPCIM",
        "IDVIM"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBIntEnableControl",
      "functionArgs": [
        "ui32Base",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "IE",
        "EPC",
        "EPCIM",
        "IDVIM"
      ],
      "registersUsedMatchingBifield": [
        "IE",
        "EPC",
        "EPCIM",
        "IDVIM"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBIntStatus",
      "functionArgs": [
        "ui32Base",
        "*pui32IntStatusEP"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "TXIS",
        "RXIS",
        "IS",
        "EPC",
        "EPCISC",
        "IDVISC"
      ],
      "registersUsedMatchingBifield": [
        "TXIS",
        "RXIS",
        "IS",
        "EPC",
        "EPCISC",
        "IDVISC"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBIntStatusControl",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "IS",
        "EPC",
        "EPCISC",
        "IDVISC"
      ],
      "registersUsedMatchingBifield": [
        "IS",
        "EPC",
        "EPCISC",
        "IDVISC"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBIntDisableEndpoint",
      "functionArgs": [
        "ui32Base",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXIE",
        "RXIE"
      ],
      "registersUsedMatchingBifield": [
        "TXIE",
        "RXIE"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBIntEnableEndpoint",
      "functionArgs": [
        "ui32Base",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXIE",
        "RXIE"
      ],
      "registersUsedMatchingBifield": [
        "TXIE",
        "RXIE"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBIntStatusEndpoint",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "TXIS",
        "RXIS"
      ],
      "registersUsedMatchingBifield": [
        "TXIS",
        "RXIS"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEndpointStatus",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "TXCSRL1",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "TXCSRL1",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostEndpointStatusClear",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CSRL0",
        "TXCSRL1",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0",
        "TXCSRL1",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDevEndpointStatusClear",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CSRL0",
        "TXCSRL1",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0",
        "TXCSRL1",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostEndpointDataToggle",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "bDataToggle",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "bool",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CSRH0",
        "TXCSRH1",
        "RXCSRH1"
      ],
      "registersUsedMatchingBifield": [
        "CSRH0",
        "TXCSRH1",
        "RXCSRH1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEndpointDataToggleClear",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXCSRL1",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "TXCSRL1",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDevEndpointStall",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CSRL0",
        "TXCSRL1",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0",
        "TXCSRL1",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDevEndpointStallClear",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CSRL0",
        "TXCSRL1",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0",
        "TXCSRL1",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDevConnect",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "POWER"
      ],
      "registersUsedMatchingBifield": [
        "POWER"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDevDisconnect",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "POWER"
      ],
      "registersUsedMatchingBifield": [
        "POWER"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDevAddrSet",
      "functionArgs": [
        "ui32Base",
        "ui32Address"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "FADDR"
      ],
      "registersUsedMatchingBifield": [
        "FADDR"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDevAddrGet",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "FADDR"
      ],
      "registersUsedMatchingBifield": [
        "FADDR"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostEndpointConfig",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32MaxPayload",
        "ui32NAKPollInterval",
        "ui32TargetEndpoint",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TYPE0",
        "NAKLMT",
        "TXMAXP1",
        "TXCSRH1",
        "RXMAXP1",
        "RXCSRH1",
        "TXTYPE1",
        "TXINTERVAL1",
        "RXTYPE1",
        "RXINTERVAL1"
      ],
      "registersUsedMatchingBifield": [
        "TYPE0",
        "NAKLMT",
        "TXMAXP1",
        "TXCSRH1",
        "RXMAXP1",
        "RXCSRH1",
        "TXTYPE1",
        "TXINTERVAL1",
        "RXTYPE1",
        "RXINTERVAL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDevEndpointConfigSet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32MaxPacketSize",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXMAXP1",
        "TXCSRL1",
        "TXCSRH1",
        "RXMAXP1",
        "RXCSRL1",
        "RXCSRH1"
      ],
      "registersUsedMatchingBifield": [
        "TXMAXP1",
        "TXCSRL1",
        "TXCSRH1",
        "RXMAXP1",
        "RXCSRL1",
        "RXCSRH1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDevEndpointConfigGet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "*pui32MaxPacketSize",
        "*pui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXMAXP1",
        "TXCSRH1",
        "RXMAXP1",
        "RXCSRH1"
      ],
      "registersUsedMatchingBifield": [
        "TXMAXP1",
        "TXCSRH1",
        "RXMAXP1",
        "RXCSRH1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBFIFOConfigSet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32FIFOAddress",
        "ui32FIFOSize",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXFIFOSZ",
        "RXFIFOSZ",
        "TXFIFOADD",
        "RXFIFOADD"
      ],
      "registersUsedMatchingBifield": [
        "TXFIFOSZ",
        "RXFIFOSZ",
        "TXFIFOADD",
        "RXFIFOADD"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBFIFOConfigGet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "*pui32FIFOAddress",
        "*pui32FIFOSize",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXFIFOSZ",
        "RXFIFOSZ",
        "TXFIFOADD",
        "RXFIFOADD"
      ],
      "registersUsedMatchingBifield": [
        "TXFIFOSZ",
        "RXFIFOSZ",
        "TXFIFOADD",
        "RXFIFOADD"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEndpointDMAConfigSet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXCSRH1",
        "RXCSRH1"
      ],
      "registersUsedMatchingBifield": [
        "TXCSRH1",
        "RXCSRH1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEndpointDMAEnable",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXCSRH1",
        "RXCSRH1"
      ],
      "registersUsedMatchingBifield": [
        "TXCSRH1",
        "RXCSRH1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEndpointDMADisable",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXCSRH1",
        "RXCSRH1"
      ],
      "registersUsedMatchingBifield": [
        "TXCSRH1",
        "RXCSRH1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEndpointDataAvail",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "CSRL0",
        "COUNT0",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0",
        "COUNT0",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEndpointDataGet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "*pui8Data",
        "*pui32Size"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint8_t",
        "uint32_t"
      ],
      "returnType": "int32_t",
      "registersUsed": [
        "FIFO0",
        "CSRL0",
        "COUNT0",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "FIFO0",
        "CSRL0",
        "COUNT0",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDevEndpointDataAck",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "bIsLastPacket"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "bool"
      ],
      "returnType": "void",
      "registersUsed": [
        "CSRL0",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostEndpointDataAck",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CSRL0",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEndpointDataPut",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "*pui8Data",
        "ui32Size"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint8_t",
        "uint32_t"
      ],
      "returnType": "int32_t",
      "registersUsed": [
        "FIFO0",
        "CSRL0"
      ],
      "registersUsedMatchingBifield": [
        "FIFO0",
        "CSRL0"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEndpointDataSend",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32TransType"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "int32_t",
      "registersUsed": [
        "CSRL0"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBFIFOFlush",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CSRL0",
        "CSRH0",
        "TXCSRL1",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0",
        "CSRH0",
        "TXCSRL1",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostRequestIN",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CSRL0",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostRequestINClear",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CSRL0",
        "RXCSRL1"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0",
        "RXCSRL1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostRequestStatus",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CSRL0"
      ],
      "registersUsedMatchingBifield": [
        "CSRL0"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostAddrSet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Addr",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXFUNCADDR0"
      ],
      "registersUsedMatchingBifield": [
        "TXFUNCADDR0"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostAddrGet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "TXFUNCADDR0"
      ],
      "registersUsedMatchingBifield": [
        "TXFUNCADDR0"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostHubAddrSet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Addr",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "TXHUBADDR0",
        "TYPE0"
      ],
      "registersUsedMatchingBifield": [
        "TXHUBADDR0",
        "TYPE0"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostHubAddrGet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "TXHUBADDR0"
      ],
      "registersUsedMatchingBifield": [
        "TXHUBADDR0"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostPwrConfig",
      "functionArgs": [
        "ui32Base",
        "ui32Flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "EPC",
        "VDC"
      ],
      "registersUsedMatchingBifield": [
        "EPC",
        "VDC"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostPwrFaultEnable",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "EPC"
      ],
      "registersUsedMatchingBifield": [
        "EPC"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostPwrFaultDisable",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "EPC"
      ],
      "registersUsedMatchingBifield": [
        "EPC"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostPwrEnable",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "EPC"
      ],
      "registersUsedMatchingBifield": [
        "EPC"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostPwrDisable",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "EPC"
      ],
      "registersUsedMatchingBifield": [
        "EPC"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBFrameNumberGet",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "FRAME"
      ],
      "registersUsedMatchingBifield": [
        "FRAME"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBOTGSessionRequest",
      "functionArgs": [
        "ui32Base",
        "bStart"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "bool"
      ],
      "returnType": "void",
      "registersUsed": [
        "DEVCTL"
      ],
      "registersUsedMatchingBifield": [
        "DEVCTL"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBFIFOAddrGet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "FIFO0"
      ],
      "registersUsedMatchingBifield": [
        "FIFO0"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBModeGet",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [
        "DEVCTL"
      ],
      "registersUsedMatchingBifield": [
        "DEVCTL"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEndpointDMAChannel",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Channel"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "DMASEL"
      ],
      "registersUsedMatchingBifield": [
        "DMASEL"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBHostMode",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "GPCS"
      ],
      "registersUsedMatchingBifield": [
        "GPCS"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDevMode",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "GPCS"
      ],
      "registersUsedMatchingBifield": [
        "GPCS"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBOTGMode",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "GPCS"
      ],
      "registersUsedMatchingBifield": [
        "GPCS"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBPHYPowerOff",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "POWER"
      ],
      "registersUsedMatchingBifield": [
        "POWER"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBPHYPowerOn",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "POWER"
      ],
      "registersUsedMatchingBifield": [
        "POWER"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEndpointPacketCountSet",
      "functionArgs": [
        "ui32Base",
        "ui32Endpoint",
        "ui32Count"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "RQPKTCOUNT1"
      ],
      "registersUsedMatchingBifield": [
        "RQPKTCOUNT1"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBNumEndpointsGet",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBEnableGlobalInterrupt",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "GLBINTEN"
      ],
      "registersUsedMatchingBifield": [
        "GLBINTEN"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBDisableGlobalInterrupt",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "GLBINTEN"
      ],
      "registersUsedMatchingBifield": [
        "GLBINTEN"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBGlobalInterruptFlagStatus",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "uint16_t",
      "registersUsed": [
        "GLBINTFLG"
      ],
      "registersUsedMatchingBifield": [
        "GLBINTFLG"
      ]
    },
    {
      "file": "usb.c",
      "peripheral": "usb",
      "functionName": "USBClearGlobalInterruptFlag",
      "functionArgs": [
        "ui32Base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "GLBINTFLG",
        "GLBINTFLGCL"
      ],
      "registersUsedMatchingBifield": [
        "GLBINTFLG",
        "GLBINTFLGCL"
      ]
    }
  ]
}
module.exports = { 
  usb_driverlib: usb_driverlib,
}
