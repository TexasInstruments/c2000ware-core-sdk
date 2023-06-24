let DeviceMemoryMap = [
	{ name: "M0_RAM_BASE", displayName: "M0 RAM", baseAddress: "0x00000000U" },
	{ name: "M1_RAM_BASE", displayName: "M1 RAM", baseAddress: "0x00000400U" },
	{ name: "ADCARESULT_BASE", displayName: "ADCARESULT", baseAddress: "0x00000B00U" },
	{ name: "ADCBRESULT_BASE", displayName: "ADCBRESULT", baseAddress: "0x00000B20U" },
	{ name: "ADCCRESULT_BASE", displayName: "ADCCRESULT", baseAddress: "0x00000B40U" },
	{ name: "CPUTIMER0_BASE", displayName: "CPUTIMER0", baseAddress: "0x00000C00U" },
	{ name: "CLA1_ONLY_BASE", displayName: "CLA1 ONLY", baseAddress: "0x00000C00U" },
	{ name: "CPUTIMER1_BASE", displayName: "CPUTIMER1", baseAddress: "0x00000C08U" },
	{ name: "CPUTIMER2_BASE", displayName: "CPUTIMER2", baseAddress: "0x00000C10U" },
	{ name: "CLA1_SOFTINT_BASE", displayName: "CLA1 SOFTINT", baseAddress: "0x00000CE0U" },
	{ name: "PIECTRL_BASE", displayName: "PIECTRL", baseAddress: "0x00000CE0U" },
	{ name: "PIEVECTTABLE_BASE", displayName: "PIEVECTTABLE", baseAddress: "0x00000D00U" },
	{ name: "DMA_BASE", displayName: "DMA", baseAddress: "0x00001000U" },
	{ name: "DMA_CH1_BASE", displayName: "DMA CH1", baseAddress: "0x00001020U" },
	{ name: "DMA_CH2_BASE", displayName: "DMA CH2", baseAddress: "0x00001040U" },
	{ name: "DMA_CH3_BASE", displayName: "DMA CH3", baseAddress: "0x00001060U" },
	{ name: "DMA_CH4_BASE", displayName: "DMA CH4", baseAddress: "0x00001080U" },
	{ name: "DMA_CH5_BASE", displayName: "DMA CH5", baseAddress: "0x000010A0U" },
	{ name: "DMA_CH6_BASE", displayName: "DMA CH6", baseAddress: "0x000010C0U" },
	{ name: "CLA1_BASE", displayName: "CLA1", baseAddress: "0x00001400U" },
	{ name: "CLB1_BASE", displayName: "CLB1", baseAddress: "0x00003000U" },
	{ name: "CLB1_LOGICCFG_BASE", displayName: "CLB1 LOGICCFG", baseAddress: "0x00003000U" },
	{ name: "CLB1_LOGICCTRL_BASE", displayName: "CLB1 LOGICCTRL", baseAddress: "0x00003100U" },
	{ name: "CLB1_DATAEXCH_BASE", displayName: "CLB1 DATAEXCH", baseAddress: "0x00003180U" },
	{ name: "CLB2_BASE", displayName: "CLB2", baseAddress: "0x00003400U" },
	{ name: "CLB2_LOGICCFG_BASE", displayName: "CLB2 LOGICCFG", baseAddress: "0x00003400U" },
	{ name: "CLB2_LOGICCTRL_BASE", displayName: "CLB2 LOGICCTRL", baseAddress: "0x00003500U" },
	{ name: "CLB2_DATAEXCH_BASE", displayName: "CLB2 DATAEXCH", baseAddress: "0x00003580U" },
	{ name: "CLB3_BASE", displayName: "CLB3", baseAddress: "0x00003800U" },
	{ name: "CLB3_LOGICCFG_BASE", displayName: "CLB3 LOGICCFG", baseAddress: "0x00003800U" },
	{ name: "CLB3_LOGICCTRL_BASE", displayName: "CLB3 LOGICCTRL", baseAddress: "0x00003900U" },
	{ name: "CLB3_DATAEXCH_BASE", displayName: "CLB3 DATAEXCH", baseAddress: "0x00003980U" },
	{ name: "CLB4_BASE", displayName: "CLB4", baseAddress: "0x00003C00U" },
	{ name: "CLB4_LOGICCFG_BASE", displayName: "CLB4 LOGICCFG", baseAddress: "0x00003C00U" },
	{ name: "CLB4_LOGICCTRL_BASE", displayName: "CLB4 LOGICCTRL", baseAddress: "0x00003D00U" },
	{ name: "CLB4_DATAEXCH_BASE", displayName: "CLB4 DATAEXCH", baseAddress: "0x00003D80U" },
	{ name: "EPWM1_BASE", displayName: "EPWM1", baseAddress: "0x00004000U" },
	{ name: "EPWM2_BASE", displayName: "EPWM2", baseAddress: "0x00004100U" },
	{ name: "EPWM3_BASE", displayName: "EPWM3", baseAddress: "0x00004200U" },
	{ name: "EPWM4_BASE", displayName: "EPWM4", baseAddress: "0x00004300U" },
	{ name: "EPWM5_BASE", displayName: "EPWM5", baseAddress: "0x00004400U" },
	{ name: "EPWM6_BASE", displayName: "EPWM6", baseAddress: "0x00004500U" },
	{ name: "EPWM7_BASE", displayName: "EPWM7", baseAddress: "0x00004600U" },
	{ name: "EPWM8_BASE", displayName: "EPWM8", baseAddress: "0x00004700U" },
	{ name: "EQEP1_BASE", displayName: "EQEP1", baseAddress: "0x00005100U" },
	{ name: "EQEP2_BASE", displayName: "EQEP2", baseAddress: "0x00005140U" },
	{ name: "ECAP1_BASE", displayName: "ECAP1", baseAddress: "0x00005200U" },
	{ name: "ECAP2_BASE", displayName: "ECAP2", baseAddress: "0x00005240U" },
	{ name: "ECAP3_BASE", displayName: "ECAP3", baseAddress: "0x00005280U" },
	{ name: "HRCAP3_BASE", displayName: "HRCAP3", baseAddress: "0x000052A0U" },
	{ name: "DACA_BASE", displayName: "DACA", baseAddress: "0x00005C00U" },
	{ name: "DACB_BASE", displayName: "DACB", baseAddress: "0x00005C10U" },
	{ name: "CMPSS1_BASE", displayName: "CMPSS1", baseAddress: "0x00005C80U" },
	{ name: "CMPSS2_BASE", displayName: "CMPSS2", baseAddress: "0x00005CA0U" },
	{ name: "CMPSS3_BASE", displayName: "CMPSS3", baseAddress: "0x00005CC0U" },
	{ name: "CMPSS4_BASE", displayName: "CMPSS4", baseAddress: "0x00005CE0U" },
	{ name: "SDFM1_BASE", displayName: "SDFM1", baseAddress: "0x00005E00U" },
	{ name: "SDFM2_BASE", displayName: "SDFM2", baseAddress: "0x00005E80U" },
	{ name: "SPIA_BASE", displayName: "SPIA", baseAddress: "0x00006100U" },
	{ name: "SPIB_BASE", displayName: "SPIB", baseAddress: "0x00006110U" },
	{ name: "BGCRC_CPU_BASE", displayName: "BGCRC CPU", baseAddress: "0x00006340U" },
	{ name: "BGCRC_CLA1_BASE", displayName: "BGCRC CLA1", baseAddress: "0x00006380U" },
	{ name: "PMBUSA_BASE", displayName: "PMBUSA", baseAddress: "0x00006400U" },
	{ name: "HIC_BASE", displayName: "HIC", baseAddress: "0x00006500U" },
	{ name: "FSITXA_BASE", displayName: "FSITXA", baseAddress: "0x00006600U" },
	{ name: "FSIRXA_BASE", displayName: "FSIRXA", baseAddress: "0x00006680U" },
	{ name: "LINA_BASE", displayName: "LINA", baseAddress: "0x00006A00U" },
	{ name: "LINB_BASE", displayName: "LINB", baseAddress: "0x00006B00U" },
	{ name: "WD_BASE", displayName: "WD", baseAddress: "0x00007000U" },
	{ name: "NMI_BASE", displayName: "NMI", baseAddress: "0x00007060U" },
	{ name: "XINT_BASE", displayName: "XINT", baseAddress: "0x00007070U" },
	{ name: "SCIA_BASE", displayName: "SCIA", baseAddress: "0x00007200U" },
	{ name: "SCIB_BASE", displayName: "SCIB", baseAddress: "0x00007210U" },
	{ name: "I2CA_BASE", displayName: "I2CA", baseAddress: "0x00007300U" },
	{ name: "I2CB_BASE", displayName: "I2CB", baseAddress: "0x00007340U" },
	{ name: "ADCA_BASE", displayName: "ADCA", baseAddress: "0x00007400U" },
	{ name: "ADCB_BASE", displayName: "ADCB", baseAddress: "0x00007480U" },
	{ name: "ADCC_BASE", displayName: "ADCC", baseAddress: "0x00007500U" },
	{ name: "INPUTXBAR_BASE", displayName: "INPUTXBAR", baseAddress: "0x00007900U" },
	{ name: "XBAR_BASE", displayName: "XBAR", baseAddress: "0x00007920U" },
	{ name: "SYNCSOC_BASE", displayName: "SYNCSOC", baseAddress: "0x00007940U" },
	{ name: "CLBINPUTXBAR_BASE", displayName: "CLBINPUTXBAR", baseAddress: "0x00007960U" },
	{ name: "DMACLASRCSEL_BASE", displayName: "DMACLASRCSEL", baseAddress: "0x00007980U" },
	{ name: "EPWMXBAR_BASE", displayName: "EPWMXBAR", baseAddress: "0x00007A00U" },
	{ name: "CLBXBAR_BASE", displayName: "CLBXBAR", baseAddress: "0x00007A40U" },
	{ name: "OUTPUTXBAR_BASE", displayName: "OUTPUTXBAR", baseAddress: "0x00007A80U" },
	{ name: "CLBOUTPUTXBAR_BASE", displayName: "CLBOUTPUTXBAR", baseAddress: "0x00007BC0U" },
	{ name: "GPIOCTRL_BASE", displayName: "GPIOCTRL", baseAddress: "0x00007C00U" },
	{ name: "GPIODATA_BASE", displayName: "GPIODATA", baseAddress: "0x00007F00U" },
	{ name: "GPIODATAREAD_BASE", displayName: "GPIODATAREAD", baseAddress: "0x00007F80U" },
	{ name: "LFU_BASE", displayName: "LFU", baseAddress: "0x00007FE0U" },
	{ name: "LS0_RAM_BASE", displayName: "LS0 RAM", baseAddress: "0x00008000U" },
	{ name: "LS1_RAM_BASE", displayName: "LS1 RAM", baseAddress: "0x00008800U" },
	{ name: "LS2_RAM_BASE", displayName: "LS2 RAM", baseAddress: "0x00009000U" },
	{ name: "LS3_RAM_BASE", displayName: "LS3 RAM", baseAddress: "0x00009800U" },
	{ name: "LS4_RAM_BASE", displayName: "LS4 RAM", baseAddress: "0x0000A000U" },
	{ name: "LS5_RAM_BASE", displayName: "LS5 RAM", baseAddress: "0x0000A800U" },
	{ name: "LS6_RAM_BASE", displayName: "LS6 RAM", baseAddress: "0x0000B000U" },
	{ name: "LS7_RAM_BASE", displayName: "LS7 RAM", baseAddress: "0x0000B800U" },
	{ name: "GS0_RAM_BASE", displayName: "GS0 RAM", baseAddress: "0x0000C000U" },
	{ name: "GS1_RAM_BASE", displayName: "GS1 RAM", baseAddress: "0x0000D000U" },
	{ name: "GS2_RAM_BASE", displayName: "GS2 RAM", baseAddress: "0x0000E000U" },
	{ name: "GS3_RAM_BASE", displayName: "GS3 RAM", baseAddress: "0x0000F000U" },
	{ name: "AESA_BASE", displayName: "AESA", baseAddress: "0x00042000U" },
	{ name: "AESA_SS_BASE", displayName: "AESA SS", baseAddress: "0x00042C00U" },
	{ name: "CANA_BASE", displayName: "CANA", baseAddress: "0x00048000U" },
	{ name: "CANA_MSG_RAM_BASE", displayName: "CANA MSG RAM", baseAddress: "0x00049000U" },
	{ name: "MCANA_DRIVER_BASE", displayName: "MCANA DRIVER", baseAddress: "0x00058000U" },
	{ name: "MCANA_MSG_RAM_BASE", displayName: "MCANA MSG RAM", baseAddress: "0x00058000U" },
	{ name: "MCANASS_BASE", displayName: "MCANASS", baseAddress: "0x0005C400U" },
	{ name: "MCANA_BASE", displayName: "MCANA", baseAddress: "0x0005C600U" },
	{ name: "MCANA_ERROR_BASE", displayName: "MCANA ERROR", baseAddress: "0x0005C800U" },
	{ name: "DEVCFG_BASE", displayName: "DEVCFG", baseAddress: "0x0005D000U" },
	{ name: "CLKCFG_BASE", displayName: "CLKCFG", baseAddress: "0x0005D200U" },
	{ name: "CPUSYS_BASE", displayName: "CPUSYS", baseAddress: "0x0005D300U" },
	{ name: "SYSSTAT_BASE", displayName: "SYSSTAT", baseAddress: "0x0005D400U" },
	{ name: "PERIPHAC_BASE", displayName: "PERIPHAC", baseAddress: "0x0005D500U" },
	{ name: "ANALOGSUBSYS_BASE", displayName: "ANALOGSUBSYS", baseAddress: "0x0005D700U" },
	{ name: "HWBIST_BASE", displayName: "HWBIST", baseAddress: "0x0005E000U" },
	{ name: "MPOST_BASE", displayName: "MPOST", baseAddress: "0x0005E200U" },
	{ name: "DCC0_BASE", displayName: "DCC0", baseAddress: "0x0005E700U" },
	{ name: "DCC1_BASE", displayName: "DCC1", baseAddress: "0x0005E740U" },
	{ name: "ERAD_GLOBAL_BASE", displayName: "ERAD GLOBAL", baseAddress: "0x0005E800U" },
	{ name: "ERAD_HWBP1_BASE", displayName: "ERAD HWBP1", baseAddress: "0x0005E900U" },
	{ name: "ERAD_HWBP2_BASE", displayName: "ERAD HWBP2", baseAddress: "0x0005E908U" },
	{ name: "ERAD_HWBP3_BASE", displayName: "ERAD HWBP3", baseAddress: "0x0005E910U" },
	{ name: "ERAD_HWBP4_BASE", displayName: "ERAD HWBP4", baseAddress: "0x0005E918U" },
	{ name: "ERAD_HWBP5_BASE", displayName: "ERAD HWBP5", baseAddress: "0x0005E920U" },
	{ name: "ERAD_HWBP6_BASE", displayName: "ERAD HWBP6", baseAddress: "0x0005E928U" },
	{ name: "ERAD_HWBP7_BASE", displayName: "ERAD HWBP7", baseAddress: "0x0005E930U" },
	{ name: "ERAD_HWBP8_BASE", displayName: "ERAD HWBP8", baseAddress: "0x0005E938U" },
	{ name: "ERAD_COUNTER1_BASE", displayName: "ERAD COUNTER1", baseAddress: "0x0005E980U" },
	{ name: "ERAD_COUNTER2_BASE", displayName: "ERAD COUNTER2", baseAddress: "0x0005E990U" },
	{ name: "ERAD_COUNTER3_BASE", displayName: "ERAD COUNTER3", baseAddress: "0x0005E9A0U" },
	{ name: "ERAD_COUNTER4_BASE", displayName: "ERAD COUNTER4", baseAddress: "0x0005E9B0U" },
	{ name: "ERAD_CRC_GLOBAL_BASE", displayName: "ERAD CRC GLOBAL", baseAddress: "0x0005EA00U" },
	{ name: "ERAD_CRC1_BASE", displayName: "ERAD CRC1", baseAddress: "0x0005EA10U" },
	{ name: "ERAD_CRC2_BASE", displayName: "ERAD CRC2", baseAddress: "0x0005EA20U" },
	{ name: "ERAD_CRC3_BASE", displayName: "ERAD CRC3", baseAddress: "0x0005EA30U" },
	{ name: "ERAD_CRC4_BASE", displayName: "ERAD CRC4", baseAddress: "0x0005EA40U" },
	{ name: "ERAD_CRC5_BASE", displayName: "ERAD CRC5", baseAddress: "0x0005EA50U" },
	{ name: "ERAD_CRC6_BASE", displayName: "ERAD CRC6", baseAddress: "0x0005EA60U" },
	{ name: "ERAD_CRC7_BASE", displayName: "ERAD CRC7", baseAddress: "0x0005EA70U" },
	{ name: "ERAD_CRC8_BASE", displayName: "ERAD CRC8", baseAddress: "0x0005EA80U" },
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
	{ name: "UID_BASE", displayName: "UID", baseAddress: "0x00070200U" },
	{ name: "DCSM_Z1OTP_BASE", displayName: "DCSM Z1OTP", baseAddress: "0x00078000U" },
	{ name: "DCSM_Z2OTP_BASE", displayName: "DCSM Z2OTP", baseAddress: "0x00078200U" },
];
let MxMemoryMap = [
	{ name: "M0_RAM_BASE", displayName: "M0 RAM", baseAddress: "0x00000000U" },
	{ name: "M1_RAM_BASE", displayName: "M1 RAM", baseAddress: "0x00000400U" },
];
let ADCxRESULTMemoryMap = [
	{ name: "ADCARESULT_BASE", displayName: "ADCARESULT", baseAddress: "0x00000B00U" },
	{ name: "ADCBRESULT_BASE", displayName: "ADCBRESULT", baseAddress: "0x00000B20U" },
	{ name: "ADCCRESULT_BASE", displayName: "ADCCRESULT", baseAddress: "0x00000B40U" },
];
let CPUTIMER0MemoryMap = [
	{ name: "CPUTIMER0_BASE", displayName: "CPUTIMER0", baseAddress: "0x00000C00U" },
];
let CLA1ONLYMemoryMap = [
	{ name: "CLA1_ONLY_BASE", displayName: "CLA1 ONLY", baseAddress: "0x00000C00U" },
];
let CPUTIMERMemoryMap = [
	{ name: "CPUTIMER1_BASE", displayName: "CPUTIMER1", baseAddress: "0x00000C08U" },
	{ name: "CPUTIMER2_BASE", displayName: "CPUTIMER2", baseAddress: "0x00000C10U" },
];
let CLA1SOFTINTMemoryMap = [
	{ name: "CLA1_SOFTINT_BASE", displayName: "CLA1 SOFTINT", baseAddress: "0x00000CE0U" },
];
let PIEMemoryMap = [
	{ name: "PIECTRL_BASE", displayName: "PIECTRL", baseAddress: "0x00000CE0U" },
	{ name: "PIEVECTTABLE_BASE", displayName: "PIEVECTTABLE", baseAddress: "0x00000D00U" },
];
let DMAMemoryMap = [
	{ name: "DMA_BASE", displayName: "DMA", baseAddress: "0x00001000U" },
	{ name: "DMA_CH1_BASE", displayName: "DMA CH1", baseAddress: "0x00001020U" },
	{ name: "DMA_CH2_BASE", displayName: "DMA CH2", baseAddress: "0x00001040U" },
	{ name: "DMA_CH3_BASE", displayName: "DMA CH3", baseAddress: "0x00001060U" },
	{ name: "DMA_CH4_BASE", displayName: "DMA CH4", baseAddress: "0x00001080U" },
	{ name: "DMA_CH5_BASE", displayName: "DMA CH5", baseAddress: "0x000010A0U" },
	{ name: "DMA_CH6_BASE", displayName: "DMA CH6", baseAddress: "0x000010C0U" },
];
let CLAMemoryMap = [
	{ name: "CLA1_BASE", displayName: "CLA1", baseAddress: "0x00001400U" },
];
let CLBMemoryMap = [
	{ name: "CLB1_BASE", displayName: "CLB1", baseAddress: "0x00003000U" },
	{ name: "CLB1_LOGICCFG_BASE", displayName: "CLB1 LOGICCFG", baseAddress: "0x00003000U" },
	{ name: "CLB1_LOGICCTRL_BASE", displayName: "CLB1 LOGICCTRL", baseAddress: "0x00003100U" },
	{ name: "CLB1_DATAEXCH_BASE", displayName: "CLB1 DATAEXCH", baseAddress: "0x00003180U" },
	{ name: "CLB2_BASE", displayName: "CLB2", baseAddress: "0x00003400U" },
	{ name: "CLB2_LOGICCFG_BASE", displayName: "CLB2 LOGICCFG", baseAddress: "0x00003400U" },
	{ name: "CLB2_LOGICCTRL_BASE", displayName: "CLB2 LOGICCTRL", baseAddress: "0x00003500U" },
	{ name: "CLB2_DATAEXCH_BASE", displayName: "CLB2 DATAEXCH", baseAddress: "0x00003580U" },
	{ name: "CLB3_BASE", displayName: "CLB3", baseAddress: "0x00003800U" },
	{ name: "CLB3_LOGICCFG_BASE", displayName: "CLB3 LOGICCFG", baseAddress: "0x00003800U" },
	{ name: "CLB3_LOGICCTRL_BASE", displayName: "CLB3 LOGICCTRL", baseAddress: "0x00003900U" },
	{ name: "CLB3_DATAEXCH_BASE", displayName: "CLB3 DATAEXCH", baseAddress: "0x00003980U" },
	{ name: "CLB4_BASE", displayName: "CLB4", baseAddress: "0x00003C00U" },
	{ name: "CLB4_LOGICCFG_BASE", displayName: "CLB4 LOGICCFG", baseAddress: "0x00003C00U" },
	{ name: "CLB4_LOGICCTRL_BASE", displayName: "CLB4 LOGICCTRL", baseAddress: "0x00003D00U" },
	{ name: "CLB4_DATAEXCH_BASE", displayName: "CLB4 DATAEXCH", baseAddress: "0x00003D80U" },
];
let EPWMMemoryMap = [
	{ name: "EPWM1_BASE", displayName: "EPWM1", baseAddress: "0x00004000U" },
	{ name: "EPWM2_BASE", displayName: "EPWM2", baseAddress: "0x00004100U" },
	{ name: "EPWM3_BASE", displayName: "EPWM3", baseAddress: "0x00004200U" },
	{ name: "EPWM4_BASE", displayName: "EPWM4", baseAddress: "0x00004300U" },
	{ name: "EPWM5_BASE", displayName: "EPWM5", baseAddress: "0x00004400U" },
	{ name: "EPWM6_BASE", displayName: "EPWM6", baseAddress: "0x00004500U" },
	{ name: "EPWM7_BASE", displayName: "EPWM7", baseAddress: "0x00004600U" },
	{ name: "EPWM8_BASE", displayName: "EPWM8", baseAddress: "0x00004700U" },
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
let HRCAP3MemoryMap = [
	{ name: "HRCAP3_BASE", displayName: "HRCAP3", baseAddress: "0x000052A0U" },
];
let DACMemoryMap = [
	{ name: "DACA_BASE", displayName: "DACA", baseAddress: "0x00005C00U" },
	{ name: "DACB_BASE", displayName: "DACB", baseAddress: "0x00005C10U" },
];
let CMPSSMemoryMap = [
	{ name: "CMPSS1_BASE", displayName: "CMPSS1", baseAddress: "0x00005C80U" },
	{ name: "CMPSS2_BASE", displayName: "CMPSS2", baseAddress: "0x00005CA0U" },
	{ name: "CMPSS3_BASE", displayName: "CMPSS3", baseAddress: "0x00005CC0U" },
	{ name: "CMPSS4_BASE", displayName: "CMPSS4", baseAddress: "0x00005CE0U" },
];
let SDFMMemoryMap = [
	{ name: "SDFM1_BASE", displayName: "SDFM1", baseAddress: "0x00005E00U" },
	{ name: "SDFM2_BASE", displayName: "SDFM2", baseAddress: "0x00005E80U" },
];
let SPIMemoryMap = [
	{ name: "SPIA_BASE", displayName: "SPIA", baseAddress: "0x00006100U" },
	{ name: "SPIB_BASE", displayName: "SPIB", baseAddress: "0x00006110U" },
];
let BGCRCMemoryMap = [
	{ name: "BGCRC_CPU_BASE", displayName: "BGCRC CPU", baseAddress: "0x00006340U" },
	{ name: "BGCRC_CLA1_BASE", displayName: "BGCRC CLA1", baseAddress: "0x00006380U" },
];
let PMBUSAMemoryMap = [
	{ name: "PMBUSA_BASE", displayName: "PMBUSA", baseAddress: "0x00006400U" },
];
let HICMemoryMap = [
	{ name: "HIC_BASE", displayName: "HIC", baseAddress: "0x00006500U" },
];
let FSIxXAMemoryMap = [
	{ name: "FSITXA_BASE", displayName: "FSITXA", baseAddress: "0x00006600U" },
	{ name: "FSIRXA_BASE", displayName: "FSIRXA", baseAddress: "0x00006680U" },
];
let LINMemoryMap = [
	{ name: "LINA_BASE", displayName: "LINA", baseAddress: "0x00006A00U" },
	{ name: "LINB_BASE", displayName: "LINB", baseAddress: "0x00006B00U" },
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
];
let I2CMemoryMap = [
	{ name: "I2CA_BASE", displayName: "I2CA", baseAddress: "0x00007300U" },
	{ name: "I2CB_BASE", displayName: "I2CB", baseAddress: "0x00007340U" },
];
let ADCMemoryMap = [
	{ name: "ADCA_BASE", displayName: "ADCA", baseAddress: "0x00007400U" },
	{ name: "ADCB_BASE", displayName: "ADCB", baseAddress: "0x00007480U" },
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
let CLBINPUTXBARMemoryMap = [
	{ name: "CLBINPUTXBAR_BASE", displayName: "CLBINPUTXBAR", baseAddress: "0x00007960U" },
];
let DMACLASRCSELMemoryMap = [
	{ name: "DMACLASRCSEL_BASE", displayName: "DMACLASRCSEL", baseAddress: "0x00007980U" },
];
let EPWMXBARMemoryMap = [
	{ name: "EPWMXBAR_BASE", displayName: "EPWMXBAR", baseAddress: "0x00007A00U" },
];
let CLBXBARMemoryMap = [
	{ name: "CLBXBAR_BASE", displayName: "CLBXBAR", baseAddress: "0x00007A40U" },
];
let UTMemoryMap = [
	{ name: "OUTPUTXBAR_BASE", displayName: "OUTPUTXBAR", baseAddress: "0x00007A80U" },
	{ name: "CLBOUTPUTXBAR_BASE", displayName: "CLBOUTPUTXBAR", baseAddress: "0x00007BC0U" },
];
let GPIOMemoryMap = [
	{ name: "GPIOCTRL_BASE", displayName: "GPIOCTRL", baseAddress: "0x00007C00U" },
	{ name: "GPIODATA_BASE", displayName: "GPIODATA", baseAddress: "0x00007F00U" },
	{ name: "GPIODATAREAD_BASE", displayName: "GPIODATAREAD", baseAddress: "0x00007F80U" },
];
let LFUMemoryMap = [
	{ name: "LFU_BASE", displayName: "LFU", baseAddress: "0x00007FE0U" },
];
let LSxMemoryMap = [
	{ name: "LS0_RAM_BASE", displayName: "LS0 RAM", baseAddress: "0x00008000U" },
	{ name: "LS1_RAM_BASE", displayName: "LS1 RAM", baseAddress: "0x00008800U" },
	{ name: "LS2_RAM_BASE", displayName: "LS2 RAM", baseAddress: "0x00009000U" },
	{ name: "LS3_RAM_BASE", displayName: "LS3 RAM", baseAddress: "0x00009800U" },
	{ name: "LS4_RAM_BASE", displayName: "LS4 RAM", baseAddress: "0x0000A000U" },
	{ name: "LS5_RAM_BASE", displayName: "LS5 RAM", baseAddress: "0x0000A800U" },
	{ name: "LS6_RAM_BASE", displayName: "LS6 RAM", baseAddress: "0x0000B000U" },
	{ name: "LS7_RAM_BASE", displayName: "LS7 RAM", baseAddress: "0x0000B800U" },
];
let GSxMemoryMap = [
	{ name: "GS0_RAM_BASE", displayName: "GS0 RAM", baseAddress: "0x0000C000U" },
	{ name: "GS1_RAM_BASE", displayName: "GS1 RAM", baseAddress: "0x0000D000U" },
	{ name: "GS2_RAM_BASE", displayName: "GS2 RAM", baseAddress: "0x0000E000U" },
	{ name: "GS3_RAM_BASE", displayName: "GS3 RAM", baseAddress: "0x0000F000U" },
];
let AESAMemoryMap = [
	{ name: "AESA_BASE", displayName: "AESA", baseAddress: "0x00042000U" },
	{ name: "AESA_SS_BASE", displayName: "AESA SS", baseAddress: "0x00042C00U" },
];
let CANAMemoryMap = [
	{ name: "CANA_BASE", displayName: "CANA", baseAddress: "0x00048000U" },
	{ name: "CANA_MSG_RAM_BASE", displayName: "CANA MSG RAM", baseAddress: "0x00049000U" },
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
let PERIPHACMemoryMap = [
	{ name: "PERIPHAC_BASE", displayName: "PERIPHAC", baseAddress: "0x0005D500U" },
];
let ANALOGSUBSYSMemoryMap = [
	{ name: "ANALOGSUBSYS_BASE", displayName: "ANALOGSUBSYS", baseAddress: "0x0005D700U" },
];
let HWBISTMemoryMap = [
	{ name: "HWBIST_BASE", displayName: "HWBIST", baseAddress: "0x0005E000U" },
];
let MPOSTMemoryMap = [
	{ name: "MPOST_BASE", displayName: "MPOST", baseAddress: "0x0005E200U" },
];
let DCCMemoryMap = [
	{ name: "DCC0_BASE", displayName: "DCC0", baseAddress: "0x0005E700U" },
	{ name: "DCC1_BASE", displayName: "DCC1", baseAddress: "0x0005E740U" },
];
let ERADMemoryMap = [
	{ name: "ERAD_GLOBAL_BASE", displayName: "ERAD GLOBAL", baseAddress: "0x0005E800U" },
	{ name: "ERAD_HWBP1_BASE", displayName: "ERAD HWBP1", baseAddress: "0x0005E900U" },
	{ name: "ERAD_HWBP2_BASE", displayName: "ERAD HWBP2", baseAddress: "0x0005E908U" },
	{ name: "ERAD_HWBP3_BASE", displayName: "ERAD HWBP3", baseAddress: "0x0005E910U" },
	{ name: "ERAD_HWBP4_BASE", displayName: "ERAD HWBP4", baseAddress: "0x0005E918U" },
	{ name: "ERAD_HWBP5_BASE", displayName: "ERAD HWBP5", baseAddress: "0x0005E920U" },
	{ name: "ERAD_HWBP6_BASE", displayName: "ERAD HWBP6", baseAddress: "0x0005E928U" },
	{ name: "ERAD_HWBP7_BASE", displayName: "ERAD HWBP7", baseAddress: "0x0005E930U" },
	{ name: "ERAD_HWBP8_BASE", displayName: "ERAD HWBP8", baseAddress: "0x0005E938U" },
	{ name: "ERAD_COUNTER1_BASE", displayName: "ERAD COUNTER1", baseAddress: "0x0005E980U" },
	{ name: "ERAD_COUNTER2_BASE", displayName: "ERAD COUNTER2", baseAddress: "0x0005E990U" },
	{ name: "ERAD_COUNTER3_BASE", displayName: "ERAD COUNTER3", baseAddress: "0x0005E9A0U" },
	{ name: "ERAD_COUNTER4_BASE", displayName: "ERAD COUNTER4", baseAddress: "0x0005E9B0U" },
	{ name: "ERAD_CRC_GLOBAL_BASE", displayName: "ERAD CRC GLOBAL", baseAddress: "0x0005EA00U" },
	{ name: "ERAD_CRC1_BASE", displayName: "ERAD CRC1", baseAddress: "0x0005EA10U" },
	{ name: "ERAD_CRC2_BASE", displayName: "ERAD CRC2", baseAddress: "0x0005EA20U" },
	{ name: "ERAD_CRC3_BASE", displayName: "ERAD CRC3", baseAddress: "0x0005EA30U" },
	{ name: "ERAD_CRC4_BASE", displayName: "ERAD CRC4", baseAddress: "0x0005EA40U" },
	{ name: "ERAD_CRC5_BASE", displayName: "ERAD CRC5", baseAddress: "0x0005EA50U" },
	{ name: "ERAD_CRC6_BASE", displayName: "ERAD CRC6", baseAddress: "0x0005EA60U" },
	{ name: "ERAD_CRC7_BASE", displayName: "ERAD CRC7", baseAddress: "0x0005EA70U" },
	{ name: "ERAD_CRC8_BASE", displayName: "ERAD CRC8", baseAddress: "0x0005EA80U" },
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
	{ name: "UID_BASE", displayName: "UID", baseAddress: "0x00070200U" },
];
let DCSM_OTPMemoryMap = [
	{ name: "DCSM_Z1OTP_BASE", displayName: "DCSM Z1OTP", baseAddress: "0x00078000U" },
	{ name: "DCSM_Z2OTP_BASE", displayName: "DCSM Z2OTP", baseAddress: "0x00078200U" },
]
module.exports = {
	MxMemoryMap: MxMemoryMap,
	ADCxRESULTMemoryMap: ADCxRESULTMemoryMap,
	CPUTIMER0MemoryMap: CPUTIMER0MemoryMap,
	CLA1ONLYMemoryMap: CLA1ONLYMemoryMap,
	CPUTIMERMemoryMap: CPUTIMERMemoryMap,
	CLA1SOFTINTMemoryMap: CLA1SOFTINTMemoryMap,
	PIEMemoryMap: PIEMemoryMap,
	DMAMemoryMap: DMAMemoryMap,
	CLAMemoryMap: CLAMemoryMap,
	CLBMemoryMap: CLBMemoryMap,
	EPWMMemoryMap: EPWMMemoryMap,
	EQEPMemoryMap: EQEPMemoryMap,
	ECAPMemoryMap: ECAPMemoryMap,
	HRCAP3MemoryMap: HRCAP3MemoryMap,
	DACMemoryMap: DACMemoryMap,
	CMPSSMemoryMap: CMPSSMemoryMap,
	SDFMMemoryMap: SDFMMemoryMap,
	SPIMemoryMap: SPIMemoryMap,
	BGCRCMemoryMap: BGCRCMemoryMap,
	PMBUSAMemoryMap: PMBUSAMemoryMap,
	HICMemoryMap: HICMemoryMap,
	FSIxXAMemoryMap: FSIxXAMemoryMap,
	LINMemoryMap: LINMemoryMap,
	WDMemoryMap: WDMemoryMap,
	NMIMemoryMap: NMIMemoryMap,
	XINTMemoryMap: XINTMemoryMap,
	SCIMemoryMap: SCIMemoryMap,
	I2CMemoryMap: I2CMemoryMap,
	ADCMemoryMap: ADCMemoryMap,
	INPUTXBARMemoryMap: INPUTXBARMemoryMap,
	XBARMemoryMap: XBARMemoryMap,
	SYNCSOCMemoryMap: SYNCSOCMemoryMap,
	CLBINPUTXBARMemoryMap: CLBINPUTXBARMemoryMap,
	DMACLASRCSELMemoryMap: DMACLASRCSELMemoryMap,
	EPWMXBARMemoryMap: EPWMXBARMemoryMap,
	CLBXBARMemoryMap: CLBXBARMemoryMap,
	UTMemoryMap: UTMemoryMap,
	GPIOMemoryMap: GPIOMemoryMap,
	LFUMemoryMap: LFUMemoryMap,
	LSxMemoryMap: LSxMemoryMap,
	GSxMemoryMap: GSxMemoryMap,
	AESAMemoryMap: AESAMemoryMap,
	CANAMemoryMap: CANAMemoryMap,
	MCANAMemoryMap: MCANAMemoryMap,
	DEVCFGMemoryMap: DEVCFGMemoryMap,
	CLKCFGMemoryMap: CLKCFGMemoryMap,
	CPUSYSMemoryMap: CPUSYSMemoryMap,
	SYSSTATMemoryMap: SYSSTATMemoryMap,
	PERIPHACMemoryMap: PERIPHACMemoryMap,
	ANALOGSUBSYSMemoryMap: ANALOGSUBSYSMemoryMap,
	HWBISTMemoryMap: HWBISTMemoryMap,
	MPOSTMemoryMap: MPOSTMemoryMap,
	DCCMemoryMap: DCCMemoryMap,
	ERADMemoryMap: ERADMemoryMap,
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
