let DeviceMemoryMap = [
	{ name: "M0_RAM_BASE", displayName: "M0 RAM", baseAddress: "0x00000000U" },
	{ name: "M1_RAM_BASE", displayName: "M1 RAM", baseAddress: "0x00000400U" },
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
	{ name: "ADCARESULT_BASE", displayName: "ADCARESULT", baseAddress: "0x00001800U" },
	{ name: "ADCBRESULT_BASE", displayName: "ADCBRESULT", baseAddress: "0x00001880U" },
	{ name: "ADCCRESULT_BASE", displayName: "ADCCRESULT", baseAddress: "0x00001900U" },
	{ name: "ADCDRESULT_BASE", displayName: "ADCDRESULT", baseAddress: "0x00001980U" },
	{ name: "ADCERESULT_BASE", displayName: "ADCERESULT", baseAddress: "0x00001A00U" },
	{ name: "CLB1_BASE", displayName: "CLB1", baseAddress: "0x00003000U" },
	{ name: "CLB1_LOGICCFG_BASE", displayName: "CLB1 LOGICCFG", baseAddress: "0x00003000U" },
	{ name: "CLB1_LOGICCTRL_BASE", displayName: "CLB1 LOGICCTRL", baseAddress: "0x00003100U" },
	{ name: "CLB1_DATAEXCH_BASE", displayName: "CLB1 DATAEXCH", baseAddress: "0x00003180U" },
	{ name: "CLB2_BASE", displayName: "CLB2", baseAddress: "0x00003400U" },
	{ name: "CLB2_LOGICCFG_BASE", displayName: "CLB2 LOGICCFG", baseAddress: "0x00003400U" },
	{ name: "CLB2_LOGICCTRL_BASE", displayName: "CLB2 LOGICCTRL", baseAddress: "0x00003500U" },
	{ name: "CLB2_DATAEXCH_BASE", displayName: "CLB2 DATAEXCH", baseAddress: "0x00003580U" },
	{ name: "LS8_RAM_BASE", displayName: "LS8 RAM", baseAddress: "0x00004000U" },
	{ name: "EPWM1_BASE", displayName: "EPWM1", baseAddress: "0x00004000U" },
	{ name: "EPWM2_BASE", displayName: "EPWM2", baseAddress: "0x00004100U" },
	{ name: "EPWM3_BASE", displayName: "EPWM3", baseAddress: "0x00004200U" },
	{ name: "EPWM4_BASE", displayName: "EPWM4", baseAddress: "0x00004300U" },
	{ name: "EPWM5_BASE", displayName: "EPWM5", baseAddress: "0x00004400U" },
	{ name: "EPWM6_BASE", displayName: "EPWM6", baseAddress: "0x00004500U" },
	{ name: "EPWM7_BASE", displayName: "EPWM7", baseAddress: "0x00004600U" },
	{ name: "EPWM8_BASE", displayName: "EPWM8", baseAddress: "0x00004700U" },
	{ name: "EPWM9_BASE", displayName: "EPWM9", baseAddress: "0x00004800U" },
	{ name: "EPWM10_BASE", displayName: "EPWM10", baseAddress: "0x00004900U" },
	{ name: "EPWM11_BASE", displayName: "EPWM11", baseAddress: "0x00004A00U" },
	{ name: "EPWM12_BASE", displayName: "EPWM12", baseAddress: "0x00004B00U" },
	{ name: "EQEP1_BASE", displayName: "EQEP1", baseAddress: "0x00005100U" },
	{ name: "EQEP2_BASE", displayName: "EQEP2", baseAddress: "0x00005140U" },
	{ name: "EQEP3_BASE", displayName: "EQEP3", baseAddress: "0x00005180U" },
	{ name: "ECAP1_BASE", displayName: "ECAP1", baseAddress: "0x00005200U" },
	{ name: "ECAP2_BASE", displayName: "ECAP2", baseAddress: "0x00005240U" },
	{ name: "CMPSS1_BASE", displayName: "CMPSS1", baseAddress: "0x00005500U" },
	{ name: "CMPSS2_BASE", displayName: "CMPSS2", baseAddress: "0x00005540U" },
	{ name: "CMPSS3_BASE", displayName: "CMPSS3", baseAddress: "0x00005580U" },
	{ name: "CMPSS4_BASE", displayName: "CMPSS4", baseAddress: "0x000055C0U" },
	{ name: "PGA1_BASE", displayName: "PGA1", baseAddress: "0x00005B00U" },
	{ name: "PGA2_BASE", displayName: "PGA2", baseAddress: "0x00005B10U" },
	{ name: "PGA3_BASE", displayName: "PGA3", baseAddress: "0x00005B20U" },
	{ name: "DACA_BASE", displayName: "DACA", baseAddress: "0x00005C00U" },
	{ name: "LS9_RAM_BASE", displayName: "LS9 RAM", baseAddress: "0x00006000U" },
	{ name: "SPIA_BASE", displayName: "SPIA", baseAddress: "0x00006100U" },
	{ name: "SPIB_BASE", displayName: "SPIB", baseAddress: "0x00006110U" },
	{ name: "PMBUSA_BASE", displayName: "PMBUSA", baseAddress: "0x00006400U" },
	{ name: "FSITXA_BASE", displayName: "FSITXA", baseAddress: "0x00006600U" },
	{ name: "FSIRXA_BASE", displayName: "FSIRXA", baseAddress: "0x00006680U" },
	{ name: "LINA_BASE", displayName: "LINA", baseAddress: "0x00006800U" },
	{ name: "ADCC_BASE", displayName: "ADCC", baseAddress: "0x00006A00U" },
	{ name: "ADCD_BASE", displayName: "ADCD", baseAddress: "0x00006C00U" },
	{ name: "ADCE_BASE", displayName: "ADCE", baseAddress: "0x00006E00U" },
	{ name: "WD_BASE", displayName: "WD", baseAddress: "0x00007000U" },
	{ name: "NMI_BASE", displayName: "NMI", baseAddress: "0x00007060U" },
	{ name: "XINT_BASE", displayName: "XINT", baseAddress: "0x00007070U" },
	{ name: "SCIA_BASE", displayName: "SCIA", baseAddress: "0x00007200U" },
	{ name: "SCIB_BASE", displayName: "SCIB", baseAddress: "0x00007210U" },
	{ name: "SCIC_BASE", displayName: "SCIC", baseAddress: "0x00007220U" },
	{ name: "I2CA_BASE", displayName: "I2CA", baseAddress: "0x00007300U" },
	{ name: "I2CB_BASE", displayName: "I2CB", baseAddress: "0x00007340U" },
	{ name: "ADCA_BASE", displayName: "ADCA", baseAddress: "0x00007400U" },
	{ name: "ADCB_BASE", displayName: "ADCB", baseAddress: "0x00007600U" },
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
	{ name: "GS1_RAM_BASE", displayName: "GS1 RAM", baseAddress: "0x0000E000U" },
	{ name: "GS2_RAM_BASE", displayName: "GS2 RAM", baseAddress: "0x00010000U" },
	{ name: "GS3_RAM_BASE", displayName: "GS3 RAM", baseAddress: "0x00012000U" },
	{ name: "LS8_RAM_CPU1_BASE", displayName: "LS8 RAM CPU1", baseAddress: "0x00014000U" },
	{ name: "LS9_RAM_CPU1_BASE", displayName: "LS9 RAM CPU1", baseAddress: "0x00016000U" },
	{ name: "USBA_BASE", displayName: "USBA", baseAddress: "0x00040000U" },
	{ name: "AESA_BASE", displayName: "AESA", baseAddress: "0x00042000U" },
	{ name: "AESA_SS_BASE", displayName: "AESA SS", baseAddress: "0x00042C00U" },
	{ name: "EXTEVT_BASE", displayName: "EXTEVT", baseAddress: "0x00054000U" },
	{ name: "EXTGPRCM_BASE", displayName: "EXTGPRCM", baseAddress: "0x0005400AU" },
	{ name: "IPSTANDARD_BASE", displayName: "IPSTANDARD", baseAddress: "0x00054020U" },
	{ name: "IPSPECIFIC_BASE", displayName: "IPSPECIFIC", baseAddress: "0x00054100U" },
	{ name: "DATA_BASE", displayName: "DATA", baseAddress: "0x00054700U" },
	{ name: "ACC_BASE", displayName: "ACC", baseAddress: "0x00054C00U" },
	{ name: "INSTRUCTION_BASE", displayName: "INSTRUCTION", baseAddress: "0x00055000U" },
	{ name: "RFDATA_BASE", displayName: "RFDATA", baseAddress: "0x00055800U" },
	{ name: "MCANA_DRIVER_BASE", displayName: "MCANA DRIVER", baseAddress: "0x00058000U" },
	{ name: "MCANA_MSG_RAM_BASE", displayName: "MCANA MSG RAM", baseAddress: "0x00058000U" },
	{ name: "MCANA_DRIVER_BASE", displayName: "MCANA DRIVER", baseAddress: "0x00058000U" },
	{ name: "MCANA_MSG_RAM_BASE", displayName: "MCANA MSG RAM", baseAddress: "0x00058000U" },
	{ name: "MCANASS_BASE", displayName: "MCANASS", baseAddress: "0x00059400U" },
	{ name: "MCANA_BASE", displayName: "MCANA", baseAddress: "0x00059600U" },
	{ name: "MCANA_ERROR_BASE", displayName: "MCANA ERROR", baseAddress: "0x00059800U" },
	{ name: "MCANB_DRIVER_BASE", displayName: "MCANB DRIVER", baseAddress: "0x0005A000U" },
	{ name: "MCANB_MSG_RAM_BASE", displayName: "MCANB MSG RAM", baseAddress: "0x0005A000U" },
	{ name: "MCANB_DRIVER_BASE", displayName: "MCANB DRIVER", baseAddress: "0x0005A000U" },
	{ name: "MCANB_MSG_RAM_BASE", displayName: "MCANB MSG RAM", baseAddress: "0x0005A000U" },
	{ name: "MCANBSS_BASE", displayName: "MCANBSS", baseAddress: "0x0005B400U" },
	{ name: "MCANB_BASE", displayName: "MCANB", baseAddress: "0x0005B600U" },
	{ name: "MCANB_ERROR_BASE", displayName: "MCANB ERROR", baseAddress: "0x0005B800U" },
	{ name: "DEVCFG_BASE", displayName: "DEVCFG", baseAddress: "0x0005D000U" },
	{ name: "CLKCFG_BASE", displayName: "CLKCFG", baseAddress: "0x0005D200U" },
	{ name: "CPUSYS_BASE", displayName: "CPUSYS", baseAddress: "0x0005D300U" },
	{ name: "SYSSTAT_BASE", displayName: "SYSSTAT", baseAddress: "0x0005D400U" },
	{ name: "PERIPHAC_BASE", displayName: "PERIPHAC", baseAddress: "0x0005D500U" },
	{ name: "ANALOGSUBSYS_BASE", displayName: "ANALOGSUBSYS", baseAddress: "0x0005D700U" },
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
	{ name: "ERAD_PCTRACE_BASE", displayName: "ERAD PCTRACE", baseAddress: "0x0005EAD0U" },
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
	{ name: "ERAD_PCTRACE_BUFFER_BASE", displayName: "ERAD PCTRACE BUFFER", baseAddress: "0x0005FE00U" },
	{ name: "UID_BASE", displayName: "UID", baseAddress: "0x00072172U" },
	{ name: "DCSM_Z1OTP_BASE", displayName: "DCSM Z1OTP", baseAddress: "0x00078000U" },
	{ name: "DCSM_Z2OTP_BASE", displayName: "DCSM Z2OTP", baseAddress: "0x00078200U" },
];
let MxMemoryMap = [
	{ name: "M0_RAM_BASE", displayName: "M0 RAM", baseAddress: "0x00000000U" },
	{ name: "M1_RAM_BASE", displayName: "M1 RAM", baseAddress: "0x00000400U" },
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
let ADCxRESULTMemoryMap = [
	{ name: "ADCARESULT_BASE", displayName: "ADCARESULT", baseAddress: "0x00001800U" },
	{ name: "ADCBRESULT_BASE", displayName: "ADCBRESULT", baseAddress: "0x00001880U" },
	{ name: "ADCCRESULT_BASE", displayName: "ADCCRESULT", baseAddress: "0x00001900U" },
	{ name: "ADCDRESULT_BASE", displayName: "ADCDRESULT", baseAddress: "0x00001980U" },
	{ name: "ADCERESULT_BASE", displayName: "ADCERESULT", baseAddress: "0x00001A00U" },
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
];
let LS8RAMMemoryMap = [
	{ name: "LS8_RAM_BASE", displayName: "LS8 RAM", baseAddress: "0x00004000U" },
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
	{ name: "EPWM9_BASE", displayName: "EPWM9", baseAddress: "0x00004800U" },
	{ name: "EPWM10_BASE", displayName: "EPWM10", baseAddress: "0x00004900U" },
	{ name: "EPWM11_BASE", displayName: "EPWM11", baseAddress: "0x00004A00U" },
	{ name: "EPWM12_BASE", displayName: "EPWM12", baseAddress: "0x00004B00U" },
];
let EQEPMemoryMap = [
	{ name: "EQEP1_BASE", displayName: "EQEP1", baseAddress: "0x00005100U" },
	{ name: "EQEP2_BASE", displayName: "EQEP2", baseAddress: "0x00005140U" },
	{ name: "EQEP3_BASE", displayName: "EQEP3", baseAddress: "0x00005180U" },
];
let ECAPMemoryMap = [
	{ name: "ECAP1_BASE", displayName: "ECAP1", baseAddress: "0x00005200U" },
	{ name: "ECAP2_BASE", displayName: "ECAP2", baseAddress: "0x00005240U" },
];
let CMPSSMemoryMap = [
	{ name: "CMPSS1_BASE", displayName: "CMPSS1", baseAddress: "0x00005500U" },
	{ name: "CMPSS2_BASE", displayName: "CMPSS2", baseAddress: "0x00005540U" },
	{ name: "CMPSS3_BASE", displayName: "CMPSS3", baseAddress: "0x00005580U" },
	{ name: "CMPSS4_BASE", displayName: "CMPSS4", baseAddress: "0x000055C0U" },
];
let PGAMemoryMap = [
	{ name: "PGA1_BASE", displayName: "PGA1", baseAddress: "0x00005B00U" },
	{ name: "PGA2_BASE", displayName: "PGA2", baseAddress: "0x00005B10U" },
	{ name: "PGA3_BASE", displayName: "PGA3", baseAddress: "0x00005B20U" },
];
let DACAMemoryMap = [
	{ name: "DACA_BASE", displayName: "DACA", baseAddress: "0x00005C00U" },
];
let LS9RAMMemoryMap = [
	{ name: "LS9_RAM_BASE", displayName: "LS9 RAM", baseAddress: "0x00006000U" },
];
let SPIMemoryMap = [
	{ name: "SPIA_BASE", displayName: "SPIA", baseAddress: "0x00006100U" },
	{ name: "SPIB_BASE", displayName: "SPIB", baseAddress: "0x00006110U" },
];
let PMBUSAMemoryMap = [
	{ name: "PMBUSA_BASE", displayName: "PMBUSA", baseAddress: "0x00006400U" },
];
let FSIxXAMemoryMap = [
	{ name: "FSITXA_BASE", displayName: "FSITXA", baseAddress: "0x00006600U" },
	{ name: "FSIRXA_BASE", displayName: "FSIRXA", baseAddress: "0x00006680U" },
];
let LINAMemoryMap = [
	{ name: "LINA_BASE", displayName: "LINA", baseAddress: "0x00006800U" },
];
let ADCMemoryMap = [
	{ name: "ADCC_BASE", displayName: "ADCC", baseAddress: "0x00006A00U" },
	{ name: "ADCD_BASE", displayName: "ADCD", baseAddress: "0x00006C00U" },
	{ name: "ADCE_BASE", displayName: "ADCE", baseAddress: "0x00006E00U" },
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
let ADC_OTPMemoryMap = [
	{ name: "ADCA_BASE", displayName: "ADCA", baseAddress: "0x00007400U" },
	{ name: "ADCB_BASE", displayName: "ADCB", baseAddress: "0x00007600U" },
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
	{ name: "GS1_RAM_BASE", displayName: "GS1 RAM", baseAddress: "0x0000E000U" },
	{ name: "GS2_RAM_BASE", displayName: "GS2 RAM", baseAddress: "0x00010000U" },
	{ name: "GS3_RAM_BASE", displayName: "GS3 RAM", baseAddress: "0x00012000U" },
	{ name: "LS8_RAM_CPU1_BASE", displayName: "LS8 RAM CPU1", baseAddress: "0x00014000U" },
	{ name: "LS9_RAM_CPU1_BASE", displayName: "LS9 RAM CPU1", baseAddress: "0x00016000U" },
];
let USBAMemoryMap = [
	{ name: "USBA_BASE", displayName: "USBA", baseAddress: "0x00040000U" },
];
let AESAMemoryMap = [
	{ name: "AESA_BASE", displayName: "AESA", baseAddress: "0x00042000U" },
	{ name: "AESA_SS_BASE", displayName: "AESA SS", baseAddress: "0x00042C00U" },
];
let EXTMemoryMap = [
	{ name: "EXTEVT_BASE", displayName: "EXTEVT", baseAddress: "0x00054000U" },
	{ name: "EXTGPRCM_BASE", displayName: "EXTGPRCM", baseAddress: "0x0005400AU" },
];
let IPSMemoryMap = [
	{ name: "IPSTANDARD_BASE", displayName: "IPSTANDARD", baseAddress: "0x00054020U" },
	{ name: "IPSPECIFIC_BASE", displayName: "IPSPECIFIC", baseAddress: "0x00054100U" },
];
let DATAMemoryMap = [
	{ name: "DATA_BASE", displayName: "DATA", baseAddress: "0x00054700U" },
];
let ACCMemoryMap = [
	{ name: "ACC_BASE", displayName: "ACC", baseAddress: "0x00054C00U" },
];
let INSTRUCTIONMemoryMap = [
	{ name: "INSTRUCTION_BASE", displayName: "INSTRUCTION", baseAddress: "0x00055000U" },
];
let RFDATAMemoryMap = [
	{ name: "RFDATA_BASE", displayName: "RFDATA", baseAddress: "0x00055800U" },
];
let MCANAMemoryMap = [
	{ name: "MCANA_DRIVER_BASE", displayName: "MCANA DRIVER", baseAddress: "0x00058000U" },
	{ name: "MCANA_MSG_RAM_BASE", displayName: "MCANA MSG RAM", baseAddress: "0x00058000U" },
	{ name: "MCANA_DRIVER_BASE", displayName: "MCANA DRIVER", baseAddress: "0x00058000U" },
	{ name: "MCANA_MSG_RAM_BASE", displayName: "MCANA MSG RAM", baseAddress: "0x00058000U" },
	{ name: "MCANASS_BASE", displayName: "MCANASS", baseAddress: "0x00059400U" },
	{ name: "MCANA_BASE", displayName: "MCANA", baseAddress: "0x00059600U" },
	{ name: "MCANA_ERROR_BASE", displayName: "MCANA ERROR", baseAddress: "0x00059800U" },
	{ name: "MCANB_DRIVER_BASE", displayName: "MCANB DRIVER", baseAddress: "0x0005A000U" },
	{ name: "MCANB_MSG_RAM_BASE", displayName: "MCANB MSG RAM", baseAddress: "0x0005A000U" },
	{ name: "MCANB_DRIVER_BASE", displayName: "MCANB DRIVER", baseAddress: "0x0005A000U" },
	{ name: "MCANB_MSG_RAM_BASE", displayName: "MCANB MSG RAM", baseAddress: "0x0005A000U" },
	{ name: "MCANBSS_BASE", displayName: "MCANBSS", baseAddress: "0x0005B400U" },
	{ name: "MCANB_BASE", displayName: "MCANB", baseAddress: "0x0005B600U" },
	{ name: "MCANB_ERROR_BASE", displayName: "MCANB ERROR", baseAddress: "0x0005B800U" },
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
	{ name: "ERAD_PCTRACE_BASE", displayName: "ERAD PCTRACE", baseAddress: "0x0005EAD0U" },
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
let ERADPCTRACEBUFFERMemoryMap = [
	{ name: "ERAD_PCTRACE_BUFFER_BASE", displayName: "ERAD PCTRACE BUFFER", baseAddress: "0x0005FE00U" },
];
let UIDMemoryMap = [
	{ name: "UID_BASE", displayName: "UID", baseAddress: "0x00072172U" },
];
let DCSM_OTPMemoryMap = [
	{ name: "DCSM_Z1OTP_BASE", displayName: "DCSM Z1OTP", baseAddress: "0x00078000U" },
	{ name: "DCSM_Z2OTP_BASE", displayName: "DCSM Z2OTP", baseAddress: "0x00078200U" },
]
module.exports = {
	MxMemoryMap: MxMemoryMap,
	CPUTIMER0MemoryMap: CPUTIMER0MemoryMap,
	CLA1ONLYMemoryMap: CLA1ONLYMemoryMap,
	CPUTIMERMemoryMap: CPUTIMERMemoryMap,
	CLA1SOFTINTMemoryMap: CLA1SOFTINTMemoryMap,
	PIEMemoryMap: PIEMemoryMap,
	DMAMemoryMap: DMAMemoryMap,
	CLAMemoryMap: CLAMemoryMap,
	ADCxRESULTMemoryMap: ADCxRESULTMemoryMap,
	CLBMemoryMap: CLBMemoryMap,
	LS8RAMMemoryMap: LS8RAMMemoryMap,
	EPWMMemoryMap: EPWMMemoryMap,
	EQEPMemoryMap: EQEPMemoryMap,
	ECAPMemoryMap: ECAPMemoryMap,
	CMPSSMemoryMap: CMPSSMemoryMap,
	PGAMemoryMap: PGAMemoryMap,
	DACAMemoryMap: DACAMemoryMap,
	LS9RAMMemoryMap: LS9RAMMemoryMap,
	SPIMemoryMap: SPIMemoryMap,
	PMBUSAMemoryMap: PMBUSAMemoryMap,
	FSIxXAMemoryMap: FSIxXAMemoryMap,
	LINAMemoryMap: LINAMemoryMap,
	ADCMemoryMap: ADCMemoryMap,
	WDMemoryMap: WDMemoryMap,
	NMIMemoryMap: NMIMemoryMap,
	XINTMemoryMap: XINTMemoryMap,
	SCIMemoryMap: SCIMemoryMap,
	I2CMemoryMap: I2CMemoryMap,
	ADC_OTPMemoryMap: ADC_OTPMemoryMap,
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
	USBAMemoryMap: USBAMemoryMap,
	AESAMemoryMap: AESAMemoryMap,
	EXTMemoryMap: EXTMemoryMap,
	IPSMemoryMap: IPSMemoryMap,
	DATAMemoryMap: DATAMemoryMap,
	ACCMemoryMap: ACCMemoryMap,
	INSTRUCTIONMemoryMap: INSTRUCTIONMemoryMap,
	RFDATAMemoryMap: RFDATAMemoryMap,
	MCANAMemoryMap: MCANAMemoryMap,
	DEVCFGMemoryMap: DEVCFGMemoryMap,
	CLKCFGMemoryMap: CLKCFGMemoryMap,
	CPUSYSMemoryMap: CPUSYSMemoryMap,
	SYSSTATMemoryMap: SYSSTATMemoryMap,
	PERIPHACMemoryMap: PERIPHACMemoryMap,
	ANALOGSUBSYSMemoryMap: ANALOGSUBSYSMemoryMap,
	DCCMemoryMap: DCCMemoryMap,
	ERADMemoryMap: ERADMemoryMap,
	EPGMemoryMap: EPGMemoryMap,
	DCSMMemoryMap: DCSMMemoryMap,
	MEMCFGMemoryMap: MEMCFGMemoryMap,
	ACCESSPROTECTIONMemoryMap: ACCESSPROTECTIONMemoryMap,
	MEMORYERRORMemoryMap: MEMORYERRORMemoryMap,
	TESTERRORMemoryMap: TESTERRORMemoryMap,
	FLASH0MemoryMap: FLASH0MemoryMap,
	ERADPCTRACEBUFFERMemoryMap: ERADPCTRACEBUFFERMemoryMap,
	UIDMemoryMap: UIDMemoryMap,
	DCSM_OTPMemoryMap: DCSM_OTPMemoryMap,
	DeviceMemoryMap: DeviceMemoryMap,
}
