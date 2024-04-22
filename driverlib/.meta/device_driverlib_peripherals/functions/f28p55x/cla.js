let cla_driverlib = 
{
  "name": "cla",
  "functions": [
    {
      "file": "cla.c",
      "peripheral": "cla",
      "functionName": "CLA_setTriggerSource",
      "functionArgs": [
        "taskNumber",
        "trigger"
      ],
      "functionArgsTypes": [
        "CLA_TaskNumber",
        "CLA_Trigger"
      ],
      "returnType": "void",
      "registersUsed": [
        "CLA1TASKSRCSEL1",
        "CLA1TASKSRCSEL2"
      ],
      "registersUsedMatchingBifield": [
        "CLA1TASKSRCSEL1",
        "CLA1TASKSRCSEL2"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_isBaseValid",
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
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_mapTaskVector",
      "functionArgs": [
        "base",
        "claIntVect",
        "claTaskAddr"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLA_MVECTNumber",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MVECT1",
        "MVECT2",
        "MVECT3",
        "MVECT4",
        "MVECT5",
        "MVECT6",
        "MVECT7",
        "MVECT8"
      ],
      "registersUsedMatchingBifield": [
        "MVECT1",
        "MVECT2",
        "MVECT3",
        "MVECT4",
        "MVECT5",
        "MVECT6",
        "MVECT7",
        "MVECT8"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_performHardReset",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCTL"
      ],
      "registersUsedMatchingBifield": [
        "MCTL"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_performSoftReset",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCTL"
      ],
      "registersUsedMatchingBifield": [
        "MCTL"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_enableIACK",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCTL"
      ],
      "registersUsedMatchingBifield": [
        "MCTL"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_disableIACK",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCTL"
      ],
      "registersUsedMatchingBifield": [
        "MCTL"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_getPendingTaskFlag",
      "functionArgs": [
        "base",
        "taskNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLA_TaskNumber"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "MIFR"
      ],
      "registersUsedMatchingBifield": [
        "MIFR"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_getAllPendingTaskFlags",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MIFR"
      ],
      "registersUsedMatchingBifield": [
        "MIFR"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_getTaskOverflowFlag",
      "functionArgs": [
        "base",
        "taskNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLA_TaskNumber"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "MIOVF"
      ],
      "registersUsedMatchingBifield": [
        "MIOVF"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_getAllTaskOverflowFlags",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MIOVF"
      ],
      "registersUsedMatchingBifield": [
        "MIOVF"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_clearTaskFlags",
      "functionArgs": [
        "base",
        "taskFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MICLR"
      ],
      "registersUsedMatchingBifield": [
        "MICLR"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_forceTasks",
      "functionArgs": [
        "base",
        "taskFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MIFR",
        "MIFRC"
      ],
      "registersUsedMatchingBifield": [
        "MIFR",
        "MIFRC"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_enableTasks",
      "functionArgs": [
        "base",
        "taskFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MIER"
      ],
      "registersUsedMatchingBifield": [
        "MIER"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_disableTasks",
      "functionArgs": [
        "base",
        "taskFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MIER"
      ],
      "registersUsedMatchingBifield": [
        "MIER"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_getTaskRunStatus",
      "functionArgs": [
        "base",
        "taskNumber"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLA_TaskNumber"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "MIRUN"
      ],
      "registersUsedMatchingBifield": [
        "MIRUN"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_getAllTaskRunStatus",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MIRUN"
      ],
      "registersUsedMatchingBifield": [
        "MIRUN"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_getBackgroundActiveVector",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline uint16_t",
      "registersUsed": [
        "MVECTBGRNDACTIVE",
        "MVECTBGRND",
        "MVECTBGRNDACTIVE"
      ],
      "registersUsedMatchingBifield": [
        "MVECTBGRNDACTIVE",
        "MVECTBGRND",
        "MVECTBGRNDACTIVE"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_enableBackgroundTask",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCTL",
        "MCTLBGRND"
      ],
      "registersUsedMatchingBifield": [
        "MCTL",
        "MCTLBGRND"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_disableBackgroundTask",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCTL",
        "MCTLBGRND"
      ],
      "registersUsedMatchingBifield": [
        "MCTL",
        "MCTLBGRND"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_startBackgroundTask",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCTL",
        "MCTLBGRND"
      ],
      "registersUsedMatchingBifield": [
        "MCTL",
        "MCTLBGRND"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_enableHardwareTrigger",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCTL",
        "MCTLBGRND"
      ],
      "registersUsedMatchingBifield": [
        "MCTL",
        "MCTLBGRND"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_disableHardwareTrigger",
      "functionArgs": [
        "base"
      ],
      "functionArgsTypes": [
        "uint32_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MCTL",
        "MCTLBGRND"
      ],
      "registersUsedMatchingBifield": [
        "MCTL",
        "MCTLBGRND"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_mapBackgroundTaskVector",
      "functionArgs": [
        "base",
        "claTaskAddr"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "MVECTBGRND"
      ],
      "registersUsedMatchingBifield": [
        "MVECTBGRND"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_getBackgroundTaskStatus",
      "functionArgs": [
        "base",
        "stsFlag"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "CLA_BGTaskStatus"
      ],
      "returnType": "static inline bool",
      "registersUsed": [
        "MSTSBGRND"
      ],
      "registersUsedMatchingBifield": [
        "MSTSBGRND"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_enableSoftwareInterrupt",
      "functionArgs": [
        "base",
        "taskFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SOFTINTEN",
        "SOFTINTEN"
      ],
      "registersUsedMatchingBifield": [
        "SOFTINTEN",
        "SOFTINTEN"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_disableSoftwareInterrupt",
      "functionArgs": [
        "base",
        "taskFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SOFTINTEN",
        "SOFTINTEN"
      ],
      "registersUsedMatchingBifield": [
        "SOFTINTEN",
        "SOFTINTEN"
      ]
    },
    {
      "file": "cla.h",
      "peripheral": "cla",
      "functionName": "CLA_forceSoftwareInterrupt",
      "functionArgs": [
        "base",
        "taskFlags"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "SOFTINTFRC"
      ],
      "registersUsedMatchingBifield": [
        "SOFTINTFRC"
      ]
    }
  ]
}
module.exports = { 
  cla_driverlib: cla_driverlib,
}
