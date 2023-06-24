let cmpss_lite_driverlib = 
{
  "name": "cmpss_lite",
  "functions": [
    {
      "file": "cmpss_lite.h",
      "peripheral": "cmpss_lite",
      "functionName": "staticinlinevoidCMPSSLITE_configDAC",
      "functionArgs": [
        "base",
        "config"
      ],
      "functionArgsTypes": [
        "uint32_t",
        "uint16_t"
      ],
      "returnType": "",
      "registersUsed": [
        "COMPDACHCTL"
      ],
      "registersUsedMatchingBifield": [
        "COMPDACHCTL"
      ]
    }
  ]
}
module.exports = { 
  cmpss_lite_driverlib: cmpss_lite_driverlib,
}
