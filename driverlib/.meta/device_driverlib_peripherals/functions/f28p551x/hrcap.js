let hrcap_driverlib = 
{
  "name": "hrcap",
  "functions": [
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_isBaseValid",
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
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_enableHighResolution",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRCTL"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_disableHighResolution",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRCTL"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_enableHighResolutionClock",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRCTL"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_disbleHighResolutionClock",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRCTL"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_startCalibration",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRCTL"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_setCalibrationMode",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRCTL"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_enableCalibrationInterrupt",
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
        "HRINTEN"
      ],
      "registersUsedMatchingBifield": [
        "HRINTEN"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_disableCalibrationInterrupt",
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
        "HRINTEN"
      ],
      "registersUsedMatchingBifield": [
        "HRINTEN"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_getCalibrationFlags",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "HRFLG"
      ],
      "registersUsedMatchingBifield": [
        "HRFLG"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_clearCalibrationFlags",
      "functionArgs": [
        "base",
        "flags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCLR"
      ],
      "registersUsedMatchingBifield": [
        "HRCLR"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_isCalibrationBusy",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "HRCTL"
      ],
      "registersUsedMatchingBifield": [
        "HRCTL"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_forceCalibrationFlags",
      "functionArgs": [
        "base",
        "flag"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRFRC"
      ],
      "registersUsedMatchingBifield": [
        "HRFRC"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_setCalibrationPeriod",
      "functionArgs": [
        "base",
        "sysclkHz"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "HRCALPRD"
      ],
      "registersUsedMatchingBifield": [
        "HRCALPRD"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_getCalibrationClockPeriod",
      "functionArgs": [
        "base",
        "clockSource"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "HRCAP_CalibrationClockSource"
      ],
      "returnType": "static inline uint32_t",
      "registersUsed": [
        "HRSYSCLKCAP",
        "HRCLKCAP"
      ],
      "registersUsedMatchingBifield": [
        "HRSYSCLKCAP",
        "HRCLKCAP"
      ]
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_getScaleFactor",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline float32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    },
    {
      "file": "hrcap.h",
      "peripheral": "hrcap",
      "functionName": "HRCAP_convertEventTimeStampNanoseconds",
      "functionArgs": [
        "timeStamp",
        "scaleFactor"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "float32_t"
      ],
      "returnType": "static inline float32_t",
      "registersUsed": [],
      "registersUsedMatchingBifield": []
    }
  ]
}
module.exports = { 
  hrcap_driverlib: hrcap_driverlib,
}
