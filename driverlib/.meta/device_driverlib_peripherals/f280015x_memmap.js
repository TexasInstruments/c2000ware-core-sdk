let DeviceMemoryMap = [
	{ name: "M0_RAM_BASE", displayName: "M0 RAM", baseAddress: "0x00000000U" },
	{ name: "M1_RAM_BASE", displayName: "M1 RAM", baseAddress: "0x00000400U" },
	{ name: "ADCARESULT_BASE", displayName: "ADCARESULT", baseAddress: "0x00000B00U" },
	{ name: "ADCCRESULT_BASE", displayName: "ADCCRESULT", baseAddress: "0x00000B40U" },
	{ name: "CPUTIMER0_BASE", displayName: "CPUTIMER0", baseAddress: "0x00000C00U" },
	{ name: "CPUTIMER1_BASE", displayName: "CPUTIMER1", baseAddress: "0x00000C08U" },
	{ name: "CPUTIMER2_BASE", displayName: "CPUTIMER2", baseAddress: "0x00000C10U" },
	{ name: "PIECTRL_BASE", displayName: "PIECTRL", baseAddress: "0x00000CE0U" },
	{ name: "PIEVECTTABLE_BASE", displayName: "PIEVECTTABLE", baseAddress: "0x00000D00U" },
	{ name: "EPWM1_BASE", displayName: "EPWM1", baseAddress: "0x00004000U" },
	{ name: "EPWM2_BASE", displayName: "EPWM2", baseAddress: "0x00004100U" },
	{ name: "EPWM3_BASE", displayName: "EPWM3", baseAddress: "0x00004200U" },
	{ name: "EPWM4_BASE", displayName: "EPWM4", baseAddress: "0x00004300U" },
	{ name: "EPWM5_BASE", displayName: "EPWM5", baseAddress: "0x00004400U" },
	{ name: "EPWM6_BASE", displayName: "EPWM6", baseAddress: "0x00004500U" },
	{ name: "EPWM7_BASE", displayName: "EPWM7", baseAddress: "0x00004600U" },
	{ name: "EQEP1_BASE", displayName: "EQEP1", baseAddress: "0x00005100U" },
	{ name: "EQEP2_BASE", displayName: "EQEP2", baseAddress: "0x00005140U" },
	{ name: "ECAP1_BASE", displayName: "ECAP1", baseAddress: "0x00005200U" },
	{ name: "ECAP2_BASE", displayName: "ECAP2", baseAddress: "0x00005240U" },
	{ name: "ECAP3_BASE", displayName: "ECAP3", baseAddress: "0x00005280U" },
	{ name: "CMPSS1_BASE", displayName: "CMPSS1", baseAddress: "0x00005500U" },
	{ name: "CMPSSLITE2_BASE", displayName: "CMPSSLITE2", baseAddress: "0x00005540U" },
	{ name: "CMPSSLITE3_BASE", displayName: "CMPSSLITE3", baseAddress: "0x00005580U" },
	{ name: "CMPSSLITE4_BASE", displayName: "CMPSSLITE4", baseAddress: "0x000055C0U" },
	{ name: "SPIA_BASE", displayName: "SPIA", baseAddress: "0x00006100U" },
	{ name: "PMBUSA_BASE", displayName: "PMBUSA", baseAddress: "0x00006400U" },
	{ name: "LINA_BASE", displayName: "LINA", baseAddress: "0x00006A00U" },
	{ name: "WD_BASE", displayName: "WD", baseAddress: "0x00007000U" },
	{ name: "NMI_BASE", displayName: "NMI", baseAddress: "0x00007060U" },
	{ name: "XINT_BASE", displayName: "XINT", baseAddress: "0x00007070U" },
	{ name: "SCIA_BASE", displayName: "SCIA", baseAddress: "0x00007200U" },
	{ name: "SCIB_BASE", displayName: "SCIB", baseAddress: "0x00007210U" },
	{ name: "SCIC_BASE", displayName: "SCIC", baseAddress: "0x00007220U" },
	{ name: "I2CA_BASE", displayName: "I2CA", baseAddress: "0x00007300U" },
	{ name: "I2CB_BASE", displayName: "I2CB", baseAddress: "0x00007340U" },
	{ name: "ADCA_BASE", displayName: "ADCA", baseAddress: "0x00007400U" },
	{ name: "ADCC_BASE", displayName: "ADCC", baseAddress: "0x00007500U" },
	{ name: "INPUTXBAR_BASE", displayName: "INPUTXBAR", baseAddress: "0x00007900U" },
	{ name: "XBAR_BASE", displayName: "XBAR", baseAddress: "0x00007920U" },
	{ name: "SYNCSOC_BASE", displayName: "SYNCSOC", baseAddress: "0x00007940U" },
	{ name: "EPWMXBAR_BASE", displayName: "EPWMXBAR", baseAddress: "0x00007A00U" },
	{ name: "OUTPUTXBAR_BASE", displayName: "OUTPUTXBAR", baseAddress: "0x00007A80U" },
	{ name: "GPIOCTRL_BASE", displayName: "GPIOCTRL", baseAddress: "0x00007C00U" },
	{ name: "GPIODATA_BASE", displayName: "GPIODATA", baseAddress: "0x00007F00U" },
	{ name: "GPIODATAREAD_BASE", displayName: "GPIODATAREAD", baseAddress: "0x00007F80U" },
	{ name: "LS0_RAM_BASE", displayName: "LS0 RAM", baseAddress: "0x00008000U" },
	{ name: "LS1_RAM_BASE", displayName: "LS1 RAM", baseAddress: "0x0000A000U" },
	{ name: "CANA_BASE", displayName: "CANA", baseAddress: "0x00048000U" },
	{ name: "CANA_MSG_RAM_BASE", displayName: "CANA MSG RAM", baseAddress: "0x00049000U" },
	{ name: "LCM_CPU1_BASE", displayName: "LCM CPU1", baseAddress: "0x0004C000U" },
	{ name: "MCANA_DRIVER_BASE", displayName: "MCANA DRIVER", baseAddress: "0x00058000U" },
	{ name: "MCANA_MSG_RAM_BASE", displayName: "MCANA MSG RAM", baseAddress: "0x00058000U" },
	{ name: "MCANASS_BASE", displayName: "MCANASS", baseAddress: "0x0005C400U" },
	{ name: "MCANA_BASE", displayName: "MCANA", baseAddress: "0x0005C600U" },
	{ name: "MCANA_ERROR_BASE", displayName: "MCANA ERROR", baseAddress: "0x0005C800U" },
	{ name: "DEVCFG_BASE", displayName: "DEVCFG", baseAddress: "0x0005D000U" },
	{ name: "CLKCFG_BASE", displayName: "CLKCFG", baseAddress: "0x0005D200U" },
	{ name: "CPUSYS_BASE", displayName: "CPUSYS", baseAddress: "0x0005D300U" },
	{ name: "SYSSTAT_BASE", displayName: "SYSSTAT", baseAddress: "0x0005D400U" },
	{ name: "ANALOGSUBSYS_BASE", displayName: "ANALOGSUBSYS", baseAddress: "0x0005D700U" },
	{ name: "MPOST_BASE", displayName: "MPOST", baseAddress: "0x0005E200U" },
	{ name: "DCC0_BASE", displayName: "DCC0", baseAddress: "0x0005E700U" },
	{ name: "EPG1_BASE", displayName: "EPG1", baseAddress: "0x0005EC00U" },
	{ name: "EPG1MUX_BASE", displayName: "EPG1MUX", baseAddress: "0x0005ECD0U" },
	{ name: "DCSM_Z1_BASE", displayName: "DCSM Z1", baseAddress: "0x0005F000U" },
	{ name: "DCSM_Z2_BASE", displayName: "DCSM Z2", baseAddress: "0x0005F080U" },
	{ name: "DCSMCOMMON_BASE", displayName: "DCSMCOMMON", baseAddress: "0x0005F0C0U" },
	{ name: "MEMCFG_BASE", displayName: "MEMCFG", baseAddress: "0x0005F400U" },
	{ name: "ACCESSPROTECTION_BASE", displayName: "ACCESSPROTECTION", baseAddress: "0x0005F500U" },
	{ name: "MEMORYERROR_BASE", displayName: "MEMORYERROR", baseAddress: "0x0005F540U" },
	{ name: "TESTERROR_BASE", displayName: "TESTERROR", baseAddress: "0x0005F590U" },
	{ name: "FLASH0CTRL_BASE", displayName: "FLASH0CTRL", baseAddress: "0x0005F800U" },
	{ name: "FLASH0ECC_BASE", displayName: "FLASH0ECC", baseAddress: "0x0005FB00U" },
	{ name: "UID_BASE", displayName: "UID", baseAddress: "0x00071140U" },
	{ name: "DCSM_Z1OTP_BASE", displayName: "DCSM Z1OTP", baseAddress: "0x00078000U" },
	{ name: "DCSM_Z2OTP_BASE", displayName: "DCSM Z2OTP", baseAddress: "0x00078200U" },
];
let MxMemoryMap = [
	{ name: "M0_RAM_BASE", displayName: "M0 RAM", baseAddress: "0x00000000U" },
	{ name: "M1_RAM_BASE", displayName: "M1 RAM", baseAddress: "0x00000400U" },
];
let ADCxRESULTMemoryMap = [
	{ name: "ADCARESULT_BASE", displayName: "ADCARESULT", baseAddress: "0x00000B00U" },
	{ name: "ADCCRESULT_BASE", displayName: "ADCCRESULT", baseAddress: "0x00000B40U" },
];
let CPUTIMERMemoryMap = [
	{ name: "CPUTIMER0_BASE", displayName: "CPUTIMER0", baseAddress: "0x00000C00U" },
	{ name: "CPUTIMER1_BASE", displayName: "CPUTIMER1", baseAddress: "0x00000C08U" },
	{ name: "CPUTIMER2_BASE", displayName: "CPUTIMER2", baseAddress: "0x00000C10U" },
];
let PIEMemoryMap = [
	{ name: "PIECTRL_BASE", displayName: "PIECTRL", baseAddress: "0x00000CE0U" },
	{ name: "PIEVECTTABLE_BASE", displayName: "PIEVECTTABLE", baseAddress: "0x00000D00U" },
];
let EPWMMemoryMap = [
	{ name: "EPWM1_BASE", displayName: "EPWM1", baseAddress: "0x00004000U" },
	{ name: "EPWM2_BASE", displayName: "EPWM2", baseAddress: "0x00004100U" },
	{ name: "EPWM3_BASE", displayName: "EPWM3", baseAddress: "0x00004200U" },
	{ name: "EPWM4_BASE", displayName: "EPWM4", baseAddress: "0x00004300U" },
	{ name: "EPWM5_BASE", displayName: "EPWM5", baseAddress: "0x00004400U" },
	{ name: "EPWM6_BASE", displayName: "EPWM6", baseAddress: "0x00004500U" },
	{ name: "EPWM7_BASE", displayName: "EPWM7", baseAddress: "0x00004600U" },
];
let EQEPMemoryMap = [
	{ name: "EQEP1_BASE", displayName: "EQEP1", baseAddress: "0x00005100U" },
	{ name: "EQEP2_BASE", displayName: "EQEP2", baseAddress: "0x00005140U" },
];
let ECAPMemoryMap = [
	{ name: "ECAP1_BASE", displayName: "ECAP1", baseAddress: "0x00005200U" },
	{ name: "ECAP2_BASE", displayName: "ECAP2", baseAddress: "0x00005240U" },
	{ name: "ECAP3_BASE", displayName: "ECAP3", baseAddress: "0x00005280U" },
];
let CMPSSMemoryMap = [
	{ name: "CMPSS1_BASE", displayName: "CMPSS1", baseAddress: "0x00005500U" },
	{ name: "CMPSSLITE2_BASE", displayName: "CMPSSLITE2", baseAddress: "0x00005540U" },
	{ name: "CMPSSLITE3_BASE", displayName: "CMPSSLITE3", baseAddress: "0x00005580U" },
	{ name: "CMPSSLITE4_BASE", displayName: "CMPSSLITE4", baseAddress: "0x000055C0U" },
];
let SPIAMemoryMap = [
	{ name: "SPIA_BASE", displayName: "SPIA", baseAddress: "0x00006100U" },
];
let PMBUSAMemoryMap = [
	{ name: "PMBUSA_BASE", displayName: "PMBUSA", baseAddress: "0x00006400U" },
];
let LINAMemoryMap = [
	{ name: "LINA_BASE", displayName: "LINA", baseAddress: "0x00006A00U" },
];
let WDMemoryMap = [
	{ name: "WD_BASE", displayName: "WD", baseAddress: "0x00007000U" },
];
let NMIMemoryMap = [
	{ name: "NMI_BASE", displayName: "NMI", baseAddress: "0x00007060U" },
];
let XINTMemoryMap = [
	{ name: "XINT_BASE", displayName: "XINT", baseAddress: "0x00007070U" },
];
let SCIMemoryMap = [
	{ name: "SCIA_BASE", displayName: "SCIA", baseAddress: "0x00007200U" },
	{ name: "SCIB_BASE", displayName: "SCIB", baseAddress: "0x00007210U" },
	{ name: "SCIC_BASE", displayName: "SCIC", baseAddress: "0x00007220U" },
];
let I2CMemoryMap = [
	{ name: "I2CA_BASE", displayName: "I2CA", baseAddress: "0x00007300U" },
	{ name: "I2CB_BASE", displayName: "I2CB", baseAddress: "0x00007340U" },
];
let ADCMemoryMap = [
	{ name: "ADCA_BASE", displayName: "ADCA", baseAddress: "0x00007400U" },
	{ name: "ADCC_BASE", displayName: "ADCC", baseAddress: "0x00007500U" },
];
let INPUTXBARMemoryMap = [
	{ name: "INPUTXBAR_BASE", displayName: "INPUTXBAR", baseAddress: "0x00007900U" },
];
let XBARMemoryMap = [
	{ name: "XBAR_BASE", displayName: "XBAR", baseAddress: "0x00007920U" },
];
let SYNCSOCMemoryMap = [
	{ name: "SYNCSOC_BASE", displayName: "SYNCSOC", baseAddress: "0x00007940U" },
];
let EPWMXBARMemoryMap = [
	{ name: "EPWMXBAR_BASE", displayName: "EPWMXBAR", baseAddress: "0x00007A00U" },
];
let OUTPUTXBARMemoryMap = [
	{ name: "OUTPUTXBAR_BASE", displayName: "OUTPUTXBAR", baseAddress: "0x00007A80U" },
];
let GPIOMemoryMap = [
	{ name: "GPIOCTRL_BASE", displayName: "GPIOCTRL", baseAddress: "0x00007C00U" },
	{ name: "GPIODATA_BASE", displayName: "GPIODATA", baseAddress: "0x00007F00U" },
	{ name: "GPIODATAREAD_BASE", displayName: "GPIODATAREAD", baseAddress: "0x00007F80U" },
];
let LSxMemoryMap = [
	{ name: "LS0_RAM_BASE", displayName: "LS0 RAM", baseAddress: "0x00008000U" },
	{ name: "LS1_RAM_BASE", displayName: "LS1 RAM", baseAddress: "0x0000A000U" },
];
let CANAMemoryMap = [
	{ name: "CANA_BASE", displayName: "CANA", baseAddress: "0x00048000U" },
	{ name: "CANA_MSG_RAM_BASE", displayName: "CANA MSG RAM", baseAddress: "0x00049000U" },
];
let LCMCPUMemoryMap = [
	{ name: "LCM_CPU1_BASE", displayName: "LCM CPU1", baseAddress: "0x0004C000U" },
];
let MCANAMemoryMap = [
	{ name: "MCANA_DRIVER_BASE", displayName: "MCANA DRIVER", baseAddress: "0x00058000U" },
	{ name: "MCANA_MSG_RAM_BASE", displayName: "MCANA MSG RAM", baseAddress: "0x00058000U" },
	{ name: "MCANASS_BASE", displayName: "MCANASS", baseAddress: "0x0005C400U" },
	{ name: "MCANA_BASE", displayName: "MCANA", baseAddress: "0x0005C600U" },
	{ name: "MCANA_ERROR_BASE", displayName: "MCANA ERROR", baseAddress: "0x0005C800U" },
];
let DEVCFGMemoryMap = [
	{ name: "DEVCFG_BASE", displayName: "DEVCFG", baseAddress: "0x0005D000U" },
];
let CLKCFGMemoryMap = [
	{ name: "CLKCFG_BASE", displayName: "CLKCFG", baseAddress: "0x0005D200U" },
];
let CPUSYSMemoryMap = [
	{ name: "CPUSYS_BASE", displayName: "CPUSYS", baseAddress: "0x0005D300U" },
];
let SYSSTATMemoryMap = [
	{ name: "SYSSTAT_BASE", displayName: "SYSSTAT", baseAddress: "0x0005D400U" },
];
let ANALOGSUBSYSMemoryMap = [
	{ name: "ANALOGSUBSYS_BASE", displayName: "ANALOGSUBSYS", baseAddress: "0x0005D700U" },
];
let MPOSTMemoryMap = [
	{ name: "MPOST_BASE", displayName: "MPOST", baseAddress: "0x0005E200U" },
];
let DCC0MemoryMap = [
	{ name: "DCC0_BASE", displayName: "DCC0", baseAddress: "0x0005E700U" },
];
let EPGMemoryMap = [
	{ name: "EPG1_BASE", displayName: "EPG1", baseAddress: "0x0005EC00U" },
	{ name: "EPG1MUX_BASE", displayName: "EPG1MUX", baseAddress: "0x0005ECD0U" },
];
let DCSMMemoryMap = [
	{ name: "DCSM_Z1_BASE", displayName: "DCSM Z1", baseAddress: "0x0005F000U" },
	{ name: "DCSM_Z2_BASE", displayName: "DCSM Z2", baseAddress: "0x0005F080U" },
	{ name: "DCSMCOMMON_BASE", displayName: "DCSMCOMMON", baseAddress: "0x0005F0C0U" },
];
let MEMCFGMemoryMap = [
	{ name: "MEMCFG_BASE", displayName: "MEMCFG", baseAddress: "0x0005F400U" },
];
let ACCESSPROTECTIONMemoryMap = [
	{ name: "ACCESSPROTECTION_BASE", displayName: "ACCESSPROTECTION", baseAddress: "0x0005F500U" },
];
let MEMORYERRORMemoryMap = [
	{ name: "MEMORYERROR_BASE", displayName: "MEMORYERROR", baseAddress: "0x0005F540U" },
];
let TESTERRORMemoryMap = [
	{ name: "TESTERROR_BASE", displayName: "TESTERROR", baseAddress: "0x0005F590U" },
];
let FLASH0MemoryMap = [
	{ name: "FLASH0CTRL_BASE", displayName: "FLASH0CTRL", baseAddress: "0x0005F800U" },
	{ name: "FLASH0ECC_BASE", displayName: "FLASH0ECC", baseAddress: "0x0005FB00U" },
];
let UIDMemoryMap = [
	{ name: "UID_BASE", displayName: "UID", baseAddress: "0x00071140U" },
];
let DCSM_OTPMemoryMap = [
	{ name: "DCSM_Z1OTP_BASE", displayName: "DCSM Z1OTP", baseAddress: "0x00078000U" },
	{ name: "DCSM_Z2OTP_BASE", displayName: "DCSM Z2OTP", baseAddress: "0x00078200U" },
]
module.exports = {
	MxMemoryMap: MxMemoryMap,
	ADCxRESULTMemoryMap: ADCxRESULTMemoryMap,
	CPUTIMERMemoryMap: CPUTIMERMemoryMap,
	PIEMemoryMap: PIEMemoryMap,
	EPWMMemoryMap: EPWMMemoryMap,
	EQEPMemoryMap: EQEPMemoryMap,
	ECAPMemoryMap: ECAPMemoryMap,
	CMPSSMemoryMap: CMPSSMemoryMap,
	SPIAMemoryMap: SPIAMemoryMap,
	PMBUSAMemoryMap: PMBUSAMemoryMap,
	LINAMemoryMap: LINAMemoryMap,
	WDMemoryMap: WDMemoryMap,
	NMIMemoryMap: NMIMemoryMap,
	XINTMemoryMap: XINTMemoryMap,
	SCIMemoryMap: SCIMemoryMap,
	I2CMemoryMap: I2CMemoryMap,
	ADCMemoryMap: ADCMemoryMap,
	INPUTXBARMemoryMap: INPUTXBARMemoryMap,
	XBARMemoryMap: XBARMemoryMap,
	SYNCSOCMemoryMap: SYNCSOCMemoryMap,
	EPWMXBARMemoryMap: EPWMXBARMemoryMap,
	OUTPUTXBARMemoryMap: OUTPUTXBARMemoryMap,
	GPIOMemoryMap: GPIOMemoryMap,
	LSxMemoryMap: LSxMemoryMap,
	CANAMemoryMap: CANAMemoryMap,
	LCMCPUMemoryMap: LCMCPUMemoryMap,
	MCANAMemoryMap: MCANAMemoryMap,
	DEVCFGMemoryMap: DEVCFGMemoryMap,
	CLKCFGMemoryMap: CLKCFGMemoryMap,
	CPUSYSMemoryMap: CPUSYSMemoryMap,
	SYSSTATMemoryMap: SYSSTATMemoryMap,
	ANALOGSUBSYSMemoryMap: ANALOGSUBSYSMemoryMap,
	MPOSTMemoryMap: MPOSTMemoryMap,
	DCC0MemoryMap: DCC0MemoryMap,
	EPGMemoryMap: EPGMemoryMap,
	DCSMMemoryMap: DCSMMemoryMap,
	MEMCFGMemoryMap: MEMCFGMemoryMap,
	ACCESSPROTECTIONMemoryMap: ACCESSPROTECTIONMemoryMap,
	MEMORYERRORMemoryMap: MEMORYERRORMemoryMap,
	TESTERRORMemoryMap: TESTERRORMemoryMap,
	FLASH0MemoryMap: FLASH0MemoryMap,
	UIDMemoryMap: UIDMemoryMap,
	DCSM_OTPMemoryMap: DCSM_OTPMemoryMap,
	DeviceMemoryMap: DeviceMemoryMap,
}
