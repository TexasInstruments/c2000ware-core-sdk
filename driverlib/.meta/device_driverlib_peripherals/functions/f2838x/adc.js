let adc_driverlib = 
{
  "name": "adc",
  "functions": [
    {
      "file": "adc.c",
      "peripheral": "adc",
      "functionName": "ADC_setMode",
      "functionArgs": [
        "base",
        "resolution",
        "signalMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_Resolution",
        "ADC_SignalMode"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTL2"
      ],
      "registersUsedMatchingBifield": [
        "ADCCTL2"
      ]
    },
    {
      "file": "adc.c",
      "peripheral": "adc",
      "functionName": "ADC_setINLTrim",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTL2",
        "INLTRIM1",
        "INLTRIM2",
        "INLTRIM4",
        "INLTRIM5"
      ],
      "registersUsedMatchingBifield": [
        "ADCCTL2",
        "ADCINLTRIM1",
        "ADCINLTRIM2",
        "ADCINLTRIM4",
        "ADCINLTRIM5"
      ]
    },
    {
      "file": "adc.c",
      "peripheral": "adc",
      "functionName": "ADC_setOffsetTrim",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "CTL2",
        "OFFTRIM"
      ],
      "registersUsedMatchingBifield": [
        "ADCCTL2",
        "ADCOFFTRIM"
      ]
    },
    {
      "file": "adc.c",
      "peripheral": "adc",
      "functionName": "ADC_setPPBTripLimits",
      "functionArgs": [
        "base",
        "ppbNumber",
        "tripHiLimit",
        "tripLoLimit"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber",
        "int32_t",
        "int32_t"
      ],
      "returnType": "void",
      "registersUsed": [
        "PPB1TRIPHI",
        "PPB2TRIPHI",
        "PPB3TRIPHI",
        "PPB4TRIPHI",
        "PPB1TRIPLO",
        "PPB2TRIPLO",
        "PPB3TRIPLO",
        "PPB4TRIPLO"
      ],
      "registersUsedMatchingBifield": [
        "ADCPPB1TRIPHI",
        "ADCPPB2TRIPHI",
        "ADCPPB3TRIPHI",
        "ADCPPB4TRIPHI",
        "ADCPPB1TRIPLO",
        "ADCPPB2TRIPLO",
        "ADCPPB3TRIPLO",
        "ADCPPB4TRIPLO"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_isBaseValid",
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
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_setPrescaler",
      "functionArgs": [
        "base",
        "clkPrescale"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_ClkPrescale"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL2"
      ],
      "registersUsedMatchingBifield": [
        "ADCCTL2"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_setupSOC",
      "functionArgs": [
        "base",
        "socNumber",
        "trigger",
        "channel",
        "sampleWindow"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_SOCNumber",
        "ADC_Trigger",
        "ADC_Channel",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SOC0CTL",
        "SOC1CTL",
        "SOC2CTL",
        "SOC3CTL",
        "SOC4CTL",
        "SOC5CTL",
        "SOC6CTL",
        "SOC7CTL",
        "SOC8CTL",
        "SOC9CTL",
        "SOC10CTL",
        "SOC11CTL",
        "SOC12CTL",
        "SOC13CTL",
        "SOC14CTL",
        "SOC15CTL"
      ],
      "registersUsedMatchingBifield": [
        "ADCSOC0CTL",
        "ADCSOC1CTL",
        "ADCSOC2CTL",
        "ADCSOC3CTL",
        "ADCSOC4CTL",
        "ADCSOC5CTL",
        "ADCSOC6CTL",
        "ADCSOC7CTL",
        "ADCSOC8CTL",
        "ADCSOC9CTL",
        "ADCSOC10CTL",
        "ADCSOC11CTL",
        "ADCSOC12CTL",
        "ADCSOC13CTL",
        "ADCSOC14CTL",
        "ADCSOC15CTL"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_setInterruptSOCTrigger",
      "functionArgs": [
        "base",
        "socNumber",
        "trigger"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_SOCNumber",
        "ADC_IntSOCTrigger"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTSOCSEL1",
        "INTSOCSEL2"
      ],
      "registersUsedMatchingBifield": [
        "ADCINTSOCSEL1",
        "ADCINTSOCSEL2"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_setInterruptPulseMode",
      "functionArgs": [
        "base",
        "pulseMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PulseMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "CTL1"
      ],
      "registersUsedMatchingBifield": [
        "ADCCTL1"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_setInterruptCycleOffset",
      "functionArgs": [
        "base",
        "cycleOffset"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTCYCLE"
      ],
      "registersUsedMatchingBifield": [
        "ADCINTCYCLE"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_enableConverter",
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
        "ADCCTL1"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_disableConverter",
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
        "ADCCTL1"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_forceSOC",
      "functionArgs": [
        "base",
        "socNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_SOCNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SOCFRC1"
      ],
      "registersUsedMatchingBifield": [
        "ADCSOCFRC1"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_forceMultipleSOC",
      "functionArgs": [
        "base",
        "socMask"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SOCFRC1"
      ],
      "registersUsedMatchingBifield": [
        "ADCSOCFRC1"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_getInterruptStatus",
      "functionArgs": [
        "base",
        "adcIntNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_IntNumber"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "INTFLG"
      ],
      "registersUsedMatchingBifield": [
        "ADCINTFLG"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_clearInterruptStatus",
      "functionArgs": [
        "base",
        "adcIntNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_IntNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTFLG",
        "INTFLGCLR"
      ],
      "registersUsedMatchingBifield": [
        "ADCINTFLG",
        "ADCINTFLGCLR"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_getInterruptOverflowStatus",
      "functionArgs": [
        "base",
        "adcIntNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_IntNumber"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "INTOVF"
      ],
      "registersUsedMatchingBifield": [
        "ADCINTOVF"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_clearInterruptOverflowStatus",
      "functionArgs": [
        "base",
        "adcIntNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_IntNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTOVF",
        "INTOVFCLR"
      ],
      "registersUsedMatchingBifield": [
        "ADCINTOVF",
        "ADCINTOVFCLR"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_readResult",
      "functionArgs": [
        "resultBase",
        "socNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_SOCNumber"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "RESULT0",
        "RESULT1",
        "RESULT2",
        "RESULT3",
        "RESULT4",
        "RESULT5",
        "RESULT6",
        "RESULT7",
        "RESULT8",
        "RESULT9",
        "RESULT10",
        "RESULT11",
        "RESULT12",
        "RESULT13",
        "RESULT14",
        "RESULT15"
      ],
      "registersUsedMatchingBifield": [
        "ADCRESULT0",
        "ADCRESULT1",
        "ADCRESULT2",
        "ADCRESULT3",
        "ADCRESULT4",
        "ADCRESULT5",
        "ADCRESULT6",
        "ADCRESULT7",
        "ADCRESULT8",
        "ADCRESULT9",
        "ADCRESULT10",
        "ADCRESULT11",
        "ADCRESULT12",
        "ADCRESULT13",
        "ADCRESULT14",
        "ADCRESULT15"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_isBusy",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "CTL1"
      ],
      "registersUsedMatchingBifield": [
        "ADCCTL1"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_setBurstModeConfig",
      "functionArgs": [
        "base",
        "trigger",
        "burstSize"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_Trigger",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "BURSTCTL"
      ],
      "registersUsedMatchingBifield": [
        "ADCBURSTCTL"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_enableBurstMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "BURSTCTL"
      ],
      "registersUsedMatchingBifield": [
        "ADCBURSTCTL"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_disableBurstMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "BURSTCTL"
      ],
      "registersUsedMatchingBifield": [
        "ADCBURSTCTL"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_setSOCPriority",
      "functionArgs": [
        "base",
        "priMode"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PriorityMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SOCPRICTL"
      ],
      "registersUsedMatchingBifield": [
        "ADCSOCPRICTL"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_configOSDetectMode",
      "functionArgs": [
        "base",
        "modeVal"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_OSDetectMode"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "OSDETECT"
      ],
      "registersUsedMatchingBifield": [
        "ADCOSDETECT"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_setupPPB",
      "functionArgs": [
        "base",
        "ppbNumber",
        "socNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber",
        "ADC_SOCNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PPB1CONFIG",
        "PPB2CONFIG",
        "PPB3CONFIG",
        "PPB4CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "ADCPPB1CONFIG",
        "ADCPPB2CONFIG",
        "ADCPPB3CONFIG",
        "ADCPPB4CONFIG"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_enablePPBEvent",
      "functionArgs": [
        "base",
        "ppbNumber",
        "evtFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "EVTSEL"
      ],
      "registersUsedMatchingBifield": [
        "ADCEVTSEL"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_disablePPBEvent",
      "functionArgs": [
        "base",
        "ppbNumber",
        "evtFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "EVTSEL"
      ],
      "registersUsedMatchingBifield": [
        "ADCEVTSEL"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_enablePPBEventInterrupt",
      "functionArgs": [
        "base",
        "ppbNumber",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "EVTINTSEL"
      ],
      "registersUsedMatchingBifield": [
        "ADCEVTINTSEL"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_disablePPBEventInterrupt",
      "functionArgs": [
        "base",
        "ppbNumber",
        "intFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "EVTINTSEL"
      ],
      "registersUsedMatchingBifield": [
        "ADCEVTINTSEL"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_getPPBEventStatus",
      "functionArgs": [
        "base",
        "ppbNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "EVTSTAT"
      ],
      "registersUsedMatchingBifield": [
        "ADCEVTSTAT"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_clearPPBEventStatus",
      "functionArgs": [
        "base",
        "ppbNumber",
        "evtFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "EVTCLR"
      ],
      "registersUsedMatchingBifield": [
        "ADCEVTCLR"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_enablePPBEventCBCClear",
      "functionArgs": [
        "base",
        "ppbNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PPB1CONFIG",
        "PPB2CONFIG",
        "PPB3CONFIG",
        "PPB4CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "ADCPPB1CONFIG",
        "ADCPPB2CONFIG",
        "ADCPPB3CONFIG",
        "ADCPPB4CONFIG"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_disablePPBEventCBCClear",
      "functionArgs": [
        "base",
        "ppbNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PPB1CONFIG",
        "PPB2CONFIG",
        "PPB3CONFIG",
        "PPB4CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "ADCPPB1CONFIG",
        "ADCPPB2CONFIG",
        "ADCPPB3CONFIG",
        "ADCPPB4CONFIG"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_readPPBResult",
      "functionArgs": [
        "resultBase",
        "ppbNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber"
      ],
      "returnType": "static inline int32_t",
      "registersUsed": [
        "PPB1RESULT",
        "PPB2RESULT",
        "PPB3RESULT",
        "PPB4RESULT"
      ],
      "registersUsedMatchingBifield": [
        "ADCPPB1RESULT",
        "ADCPPB2RESULT",
        "ADCPPB3RESULT",
        "ADCPPB4RESULT"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_getPPBDelayTimeStamp",
      "functionArgs": [
        "base",
        "ppbNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "PPB1STAMP",
        "PPB2STAMP",
        "PPB3STAMP",
        "PPB4STAMP"
      ],
      "registersUsedMatchingBifield": [
        "ADCPPB1STAMP",
        "ADCPPB2STAMP",
        "ADCPPB3STAMP",
        "ADCPPB4STAMP"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_setPPBCalibrationOffset",
      "functionArgs": [
        "base",
        "ppbNumber",
        "offset"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber",
        "int16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PPB1OFFCAL",
        "PPB2OFFCAL",
        "PPB3OFFCAL",
        "PPB4OFFCAL"
      ],
      "registersUsedMatchingBifield": [
        "ADCPPB1OFFCAL",
        "ADCPPB2OFFCAL",
        "ADCPPB3OFFCAL",
        "ADCPPB4OFFCAL"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_setPPBReferenceOffset",
      "functionArgs": [
        "base",
        "ppbNumber",
        "offset"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PPB1OFFREF",
        "PPB2OFFREF",
        "PPB3OFFREF",
        "PPB4OFFREF"
      ],
      "registersUsedMatchingBifield": [
        "ADCPPB1OFFREF",
        "ADCPPB2OFFREF",
        "ADCPPB3OFFREF",
        "ADCPPB4OFFREF"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_enablePPBTwosComplement",
      "functionArgs": [
        "base",
        "ppbNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PPB1CONFIG",
        "PPB2CONFIG",
        "PPB3CONFIG",
        "PPB4CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "ADCPPB1CONFIG",
        "ADCPPB2CONFIG",
        "ADCPPB3CONFIG",
        "ADCPPB4CONFIG"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_disablePPBTwosComplement",
      "functionArgs": [
        "base",
        "ppbNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_PPBNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "PPB1CONFIG",
        "PPB2CONFIG",
        "PPB3CONFIG",
        "PPB4CONFIG"
      ],
      "registersUsedMatchingBifield": [
        "ADCPPB1CONFIG",
        "ADCPPB2CONFIG",
        "ADCPPB3CONFIG",
        "ADCPPB4CONFIG"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_enableInterrupt",
      "functionArgs": [
        "base",
        "adcIntNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_IntNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTSEL1N2",
        "INTSEL3N4"
      ],
      "registersUsedMatchingBifield": [
        "ADCINTSEL1N2",
        "ADCINTSEL3N4"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_disableInterrupt",
      "functionArgs": [
        "base",
        "adcIntNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_IntNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTSEL1N2",
        "INTSEL3N4"
      ],
      "registersUsedMatchingBifield": [
        "ADCINTSEL1N2",
        "ADCINTSEL3N4"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_setInterruptSource",
      "functionArgs": [
        "base",
        "adcIntNum",
        "socNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_IntNumber",
        "ADC_SOCNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTSEL1N2",
        "INTSEL3N4"
      ],
      "registersUsedMatchingBifield": [
        "ADCINTSEL1N2",
        "ADCINTSEL3N4"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_enableContinuousMode",
      "functionArgs": [
        "base",
        "adcIntNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_IntNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTSEL1N2",
        "INTSEL3N4"
      ],
      "registersUsedMatchingBifield": [
        "ADCINTSEL1N2",
        "ADCINTSEL3N4"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_disableContinuousMode",
      "functionArgs": [
        "base",
        "adcIntNum"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "ADC_IntNumber"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "INTSEL1N2",
        "INTSEL3N4"
      ],
      "registersUsedMatchingBifield": [
        "ADCINTSEL1N2",
        "ADCINTSEL3N4"
      ]
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_getTemperatureC",
      "functionArgs": [
        "tempResult",
        "vref"
      ],
      "functionArgsTypes": [
        "uint16_t",
        "float32_t"
      ],
      "returnType": "static inline int16_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "adc.h",
      "peripheral": "adc",
      "functionName": "ADC_getTemperatureK",
      "functionArgs": [
        "tempResult",
        "vref"
      ],
      "functionArgsTypes": [
        "uint16_t",
        "float32_t"
      ],
      "returnType": "static inline int16_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    }
  ]
}
module.exports = { 
  adc_driverlib: adc_driverlib,
}
