let asysctl_driverlib = 
{
  "name": "asysctl",
  "functions": [
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_enableTemperatureSensor",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TSNSCTL"
      ],
      "registersUsedMatchingBifield": [
        "TSNSCTL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_disableTemperatureSensor",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "TSNSCTL"
      ],
      "registersUsedMatchingBifield": [
        "TSNSCTL"
      ]
    },
    {
      "file": "asysctl.h",
      "peripheral": "asysctl",
      "functionName": "ASysCtl_lockTemperatureSensor",
      "functionArgs": [
        "void"
      ],
      "functionArgsTypes": [
        ""
      ],
      "returnType": "static inline void",
      "registersUsed": [
        "LOCK"
      ],
      "registersUsedMatchingBifield": [
        "LOCK"
      ]
    }
  ]
}
module.exports = { 
  asysctl_driverlib: asysctl_driverlib,
}
