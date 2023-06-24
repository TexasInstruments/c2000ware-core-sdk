let DeviceMemoryMap = [
	{ name: "M0_RAM_BASE", displayName: "M0 RAM", baseAddress: "0x00000000U" },
	{ name: "M1_RAM_BASE", displayName: "M1 RAM", baseAddress: "0x00000400U" },
	{ name: "ADCARESULT_BASE", displayName: "ADCARESULT", baseAddress: "0x00000B00U" },
	{ name: "ADCBRESULT_BASE", displayName: "ADCBRESULT", baseAddress: "0x00000B20U" },
	{ name: "ADCDRESULT_BASE", displayName: "ADCDRESULT", baseAddress: "0x00000B60U" },
	{ name: "CPUTIMER0_BASE", displayName: "CPUTIMER0", baseAddress: "0x00000C00U" },
	{ name: "CPUTIMER1_BASE", displayName: "CPUTIMER1", baseAddress: "0x00000C08U" },
	{ name: "CPUTIMER2_BASE", displayName: "CPUTIMER2", baseAddress: "0x00000C10U" },
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
	{ name: "CLATOCPU_RAM_BASE", displayName: "CLATOCPU RAM", baseAddress: "0x00001480U" },
	{ name: "CPUTOCLA_RAM_BASE", displayName: "CPUTOCLA RAM", baseAddress: "0x00001500U" },
	{ name: "CLB1_BASE", displayName: "CLB1", baseAddress: "0x00003000U" },
	{ name: "CLB1_LOGICCFG_BASE", displayName: "CLB1 LOGICCFG", baseAddress: "0x00003000U" },
	{ name: "CLB1_LOGICCTL_BASE", displayName: "CLB1 LOGICCTL", baseAddress: "0x00003100U" },
	{ name: "CLB1_DATAEXCH_BASE", displayName: "CLB1 DATAEXCH", baseAddress: "0x00003200U" },
	{ name: "CLB2_BASE", displayName: "CLB2", baseAddress: "0x00003400U" },
	{ name: "CLB2_LOGICCFG_BASE", displayName: "CLB2 LOGICCFG", baseAddress: "0x00003400U" },
	{ name: "CLB2_LOGICCTL_BASE", displayName: "CLB2 LOGICCTL", baseAddress: "0x00003500U" },
	{ name: "CLB2_DATAEXCH_BASE", displayName: "CLB2 DATAEXCH", baseAddress: "0x00003600U" },
	{ name: "CLB3_BASE", displayName: "CLB3", baseAddress: "0x00003800U" },
	{ name: "CLB3_LOGICCFG_BASE", displayName: "CLB3 LOGICCFG", baseAddress: "0x00003800U" },
	{ name: "CLB3_LOGICCTL_BASE", displayName: "CLB3 LOGICCTL", baseAddress: "0x00003900U" },
	{ name: "CLB3_DATAEXCH_BASE", displayName: "CLB3 DATAEXCH", baseAddress: "0x00003A00U" },
	{ name: "CLB4_BASE", displayName: "CLB4", baseAddress: "0x00003C00U" },
	{ name: "CLB4_LOGICCFG_BASE", displayName: "CLB4 LOGICCFG", baseAddress: "0x00003C00U" },
	{ name: "CLB4_LOGICCTL_BASE", displayName: "CLB4 LOGICCTL", baseAddress: "0x00003D00U" },
	{ name: "CLB4_DATAEXCH_BASE", displayName: "CLB4 DATAEXCH", baseAddress: "0x00003E00U" },
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
	{ name: "ECAP1_BASE", displayName: "ECAP1", baseAddress: "0x00005000U" },
	{ name: "ECAP2_BASE", displayName: "ECAP2", baseAddress: "0x00005020U" },
	{ name: "ECAP3_BASE", displayName: "ECAP3", baseAddress: "0x00005040U" },
	{ name: "ECAP4_BASE", displayName: "ECAP4", baseAddress: "0x00005060U" },
	{ name: "ECAP5_BASE", displayName: "ECAP5", baseAddress: "0x00005080U" },
	{ name: "ECAP6_BASE", displayName: "ECAP6", baseAddress: "0x000050A0U" },
	{ name: "EQEP1_BASE", displayName: "EQEP1", baseAddress: "0x00005100U" },
	{ name: "EQEP2_BASE", displayName: "EQEP2", baseAddress: "0x00005140U" },
	{ name: "EQEP3_BASE", displayName: "EQEP3", baseAddress: "0x00005180U" },
	{ name: "DACA_BASE", displayName: "DACA", baseAddress: "0x00005C00U" },
	{ name: "DACB_BASE", displayName: "DACB", baseAddress: "0x00005C10U" },
	{ name: "DACC_BASE", displayName: "DACC", baseAddress: "0x00005C20U" },
	{ name: "CMPSS1_BASE", displayName: "CMPSS1", baseAddress: "0x00005C80U" },
	{ name: "CMPSS2_BASE", displayName: "CMPSS2", baseAddress: "0x00005CA0U" },
	{ name: "CMPSS3_BASE", displayName: "CMPSS3", baseAddress: "0x00005CC0U" },
	{ name: "CMPSS4_BASE", displayName: "CMPSS4", baseAddress: "0x00005CE0U" },
	{ name: "CMPSS5_BASE", displayName: "CMPSS5", baseAddress: "0x00005D00U" },
	{ name: "CMPSS6_BASE", displayName: "CMPSS6", baseAddress: "0x00005D20U" },
	{ name: "CMPSS7_BASE", displayName: "CMPSS7", baseAddress: "0x00005D40U" },
	{ name: "CMPSS8_BASE", displayName: "CMPSS8", baseAddress: "0x00005D60U" },
	{ name: "SDFM1_BASE", displayName: "SDFM1", baseAddress: "0x00005E00U" },
	{ name: "SDFM2_BASE", displayName: "SDFM2", baseAddress: "0x00005E80U" },
	{ name: "MCBSPA_BASE", displayName: "MCBSPA", baseAddress: "0x00006000U" },
	{ name: "MCBSPB_BASE", displayName: "MCBSPB", baseAddress: "0x00006040U" },
	{ name: "SPIA_BASE", displayName: "SPIA", baseAddress: "0x00006100U" },
	{ name: "SPIB_BASE", displayName: "SPIB", baseAddress: "0x00006110U" },
	{ name: "SPIC_BASE", displayName: "SPIC", baseAddress: "0x00006120U" },
	{ name: "WD_BASE", displayName: "WD", baseAddress: "0x00007000U" },
	{ name: "NMI_BASE", displayName: "NMI", baseAddress: "0x00007060U" },
	{ name: "XINT_BASE", displayName: "XINT", baseAddress: "0x00007070U" },
	{ name: "SCIA_BASE", displayName: "SCIA", baseAddress: "0x00007200U" },
	{ name: "SCIB_BASE", displayName: "SCIB", baseAddress: "0x00007210U" },
	{ name: "SCIC_BASE", displayName: "SCIC", baseAddress: "0x00007220U" },
	{ name: "SCID_BASE", displayName: "SCID", baseAddress: "0x00007230U" },
	{ name: "I2CA_BASE", displayName: "I2CA", baseAddress: "0x00007300U" },
	{ name: "I2CB_BASE", displayName: "I2CB", baseAddress: "0x00007340U" },
	{ name: "ADCA_BASE", displayName: "ADCA", baseAddress: "0x00007400U" },
	{ name: "ADCB_BASE", displayName: "ADCB", baseAddress: "0x00007480U" },
	{ name: "ADCD_BASE", displayName: "ADCD", baseAddress: "0x00007580U" },
	{ name: "INPUTXBAR_BASE", displayName: "INPUTXBAR", baseAddress: "0x00007900U" },
	{ name: "XBAR_BASE", displayName: "XBAR", baseAddress: "0x00007920U" },
	{ name: "SYNCSOC_BASE", displayName: "SYNCSOC", baseAddress: "0x00007940U" },
	{ name: "DMACLASRCSEL_BASE", displayName: "DMACLASRCSEL", baseAddress: "0x00007980U" },
	{ name: "EPWMXBAR_BASE", displayName: "EPWMXBAR", baseAddress: "0x00007A00U" },
	{ name: "CLBXBAR_BASE", displayName: "CLBXBAR", baseAddress: "0x00007A40U" },
	{ name: "OUTPUTXBAR_BASE", displayName: "OUTPUTXBAR", baseAddress: "0x00007A80U" },
	{ name: "GPIOCTRL_BASE", displayName: "GPIOCTRL", baseAddress: "0x00007C00U" },
	{ name: "GPIODATA_BASE", displayName: "GPIODATA", baseAddress: "0x00007F00U" },
	{ name: "LS0_RAM_BASE", displayName: "LS0 RAM", baseAddress: "0x00008000U" },
	{ name: "LS1_RAM_BASE", displayName: "LS1 RAM", baseAddress: "0x00008800U" },
	{ name: "LS2_RAM_BASE", displayName: "LS2 RAM", baseAddress: "0x00009000U" },
	{ name: "LS3_RAM_BASE", displayName: "LS3 RAM", baseAddress: "0x00009800U" },
	{ name: "LS4_RAM_BASE", displayName: "LS4 RAM", baseAddress: "0x0000A000U" },
	{ name: "LS5_RAM_BASE", displayName: "LS5 RAM", baseAddress: "0x0000A800U" },
	{ name: "D0_RAM_BASE", displayName: "D0 RAM", baseAddress: "0x0000B000U" },
	{ name: "D1_RAM_BASE", displayName: "D1 RAM", baseAddress: "0x0000B800U" },
	{ name: "GS0_RAM_BASE", displayName: "GS0 RAM", baseAddress: "0x0000C000U" },
	{ name: "GS1_RAM_BASE", displayName: "GS1 RAM", baseAddress: "0x0000D000U" },
	{ name: "GS2_RAM_BASE", displayName: "GS2 RAM", baseAddress: "0x0000E000U" },
	{ name: "GS3_RAM_BASE", displayName: "GS3 RAM", baseAddress: "0x0000F000U" },
	{ name: "GS4_RAM_BASE", displayName: "GS4 RAM", baseAddress: "0x00010000U" },
	{ name: "GS5_RAM_BASE", displayName: "GS5 RAM", baseAddress: "0x00011000U" },
	{ name: "GS6_RAM_BASE", displayName: "GS6 RAM", baseAddress: "0x00012000U" },
	{ name: "GS7_RAM_BASE", displayName: "GS7 RAM", baseAddress: "0x00013000U" },
	{ name: "USBA_BASE", displayName: "USBA", baseAddress: "0x00040000U" },
	{ name: "EMIF1_BASE", displayName: "EMIF1", baseAddress: "0x00047000U" },
	{ name: "CANA_BASE", displayName: "CANA", baseAddress: "0x00048000U" },
	{ name: "CANA_MSG_RAM_BASE", displayName: "CANA MSG RAM", baseAddress: "0x00049000U" },
	{ name: "CANB_BASE", displayName: "CANB", baseAddress: "0x0004A000U" },
	{ name: "CANB_MSG_RAM_BASE", displayName: "CANB MSG RAM", baseAddress: "0x0004B000U" },
	{ name: "DEVCFG_BASE", displayName: "DEVCFG", baseAddress: "0x0005D000U" },
	{ name: "ANALOGSUBSYS_BASE", displayName: "ANALOGSUBSYS", baseAddress: "0x0005D180U" },
	{ name: "CLKCFG_BASE", displayName: "CLKCFG", baseAddress: "0x0005D200U" },
	{ name: "CPUSYS_BASE", displayName: "CPUSYS", baseAddress: "0x0005D300U" },
	{ name: "ROMPREFETCH_BASE", displayName: "ROMPREFETCH", baseAddress: "0x0005E608U" },
	{ name: "DCSM_Z1_BASE", displayName: "DCSM Z1", baseAddress: "0x0005F000U" },
	{ name: "DCSM_Z2_BASE", displayName: "DCSM Z2", baseAddress: "0x0005F040U" },
	{ name: "DCSMCOMMON_BASE", displayName: "DCSMCOMMON", baseAddress: "0x0005F070U" },
	{ name: "MEMCFG_BASE", displayName: "MEMCFG", baseAddress: "0x0005F400U" },
	{ name: "EMIF1CONFIG_BASE", displayName: "EMIF1CONFIG", baseAddress: "0x0005F480U" },
	{ name: "ACCESSPROTECTION_BASE", displayName: "ACCESSPROTECTION", baseAddress: "0x0005F4C0U" },
	{ name: "MEMORYERROR_BASE", displayName: "MEMORYERROR", baseAddress: "0x0005F500U" },
	{ name: "ROMWAITSTATE_BASE", displayName: "ROMWAITSTATE", baseAddress: "0x0005F540U" },
	{ name: "FLASH0CTRL_BASE", displayName: "FLASH0CTRL", baseAddress: "0x0005F800U" },
	{ name: "FLASH0ECC_BASE", displayName: "FLASH0ECC", baseAddress: "0x0005FB00U" },
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
	{ name: "ADCDRESULT_BASE", displayName: "ADCDRESULT", baseAddress: "0x00000B60U" },
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
	{ name: "CLATOCPU_RAM_BASE", displayName: "CLATOCPU RAM", baseAddress: "0x00001480U" },
	{ name: "CPUTOCLA_RAM_BASE", displayName: "CPUTOCLA RAM", baseAddress: "0x00001500U" },
];
let CLBMemoryMap = [
	{ name: "CLB1_BASE", displayName: "CLB1", baseAddress: "0x00003000U" },
	{ name: "CLB1_LOGICCFG_BASE", displayName: "CLB1 LOGICCFG", baseAddress: "0x00003000U" },
	{ name: "CLB1_LOGICCTL_BASE", displayName: "CLB1 LOGICCTL", baseAddress: "0x00003100U" },
	{ name: "CLB1_DATAEXCH_BASE", displayName: "CLB1 DATAEXCH", baseAddress: "0x00003200U" },
	{ name: "CLB2_BASE", displayName: "CLB2", baseAddress: "0x00003400U" },
	{ name: "CLB2_LOGICCFG_BASE", displayName: "CLB2 LOGICCFG", baseAddress: "0x00003400U" },
	{ name: "CLB2_LOGICCTL_BASE", displayName: "CLB2 LOGICCTL", baseAddress: "0x00003500U" },
	{ name: "CLB2_DATAEXCH_BASE", displayName: "CLB2 DATAEXCH", baseAddress: "0x00003600U" },
	{ name: "CLB3_BASE", displayName: "CLB3", baseAddress: "0x00003800U" },
	{ name: "CLB3_LOGICCFG_BASE", displayName: "CLB3 LOGICCFG", baseAddress: "0x00003800U" },
	{ name: "CLB3_LOGICCTL_BASE", displayName: "CLB3 LOGICCTL", baseAddress: "0x00003900U" },
	{ name: "CLB3_DATAEXCH_BASE", displayName: "CLB3 DATAEXCH", baseAddress: "0x00003A00U" },
	{ name: "CLB4_BASE", displayName: "CLB4", baseAddress: "0x00003C00U" },
	{ name: "CLB4_LOGICCFG_BASE", displayName: "CLB4 LOGICCFG", baseAddress: "0x00003C00U" },
	{ name: "CLB4_LOGICCTL_BASE", displayName: "CLB4 LOGICCTL", baseAddress: "0x00003D00U" },
	{ name: "CLB4_DATAEXCH_BASE", displayName: "CLB4 DATAEXCH", baseAddress: "0x00003E00U" },
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
let ECAPMemoryMap = [
	{ name: "ECAP1_BASE", displayName: "ECAP1", baseAddress: "0x00005000U" },
	{ name: "ECAP2_BASE", displayName: "ECAP2", baseAddress: "0x00005020U" },
	{ name: "ECAP3_BASE", displayName: "ECAP3", baseAddress: "0x00005040U" },
	{ name: "ECAP4_BASE", displayName: "ECAP4", baseAddress: "0x00005060U" },
	{ name: "ECAP5_BASE", displayName: "ECAP5", baseAddress: "0x00005080U" },
	{ name: "ECAP6_BASE", displayName: "ECAP6", baseAddress: "0x000050A0U" },
];
let EQEPMemoryMap = [
	{ name: "EQEP1_BASE", displayName: "EQEP1", baseAddress: "0x00005100U" },
	{ name: "EQEP2_BASE", displayName: "EQEP2", baseAddress: "0x00005140U" },
	{ name: "EQEP3_BASE", displayName: "EQEP3", baseAddress: "0x00005180U" },
];
let DACMemoryMap = [
	{ name: "DACA_BASE", displayName: "DACA", baseAddress: "0x00005C00U" },
	{ name: "DACB_BASE", displayName: "DACB", baseAddress: "0x00005C10U" },
	{ name: "DACC_BASE", displayName: "DACC", baseAddress: "0x00005C20U" },
];
let CMPSSMemoryMap = [
	{ name: "CMPSS1_BASE", displayName: "CMPSS1", baseAddress: "0x00005C80U" },
	{ name: "CMPSS2_BASE", displayName: "CMPSS2", baseAddress: "0x00005CA0U" },
	{ name: "CMPSS3_BASE", displayName: "CMPSS3", baseAddress: "0x00005CC0U" },
	{ name: "CMPSS4_BASE", displayName: "CMPSS4", baseAddress: "0x00005CE0U" },
	{ name: "CMPSS5_BASE", displayName: "CMPSS5", baseAddress: "0x00005D00U" },
	{ name: "CMPSS6_BASE", displayName: "CMPSS6", baseAddress: "0x00005D20U" },
	{ name: "CMPSS7_BASE", displayName: "CMPSS7", baseAddress: "0x00005D40U" },
	{ name: "CMPSS8_BASE", displayName: "CMPSS8", baseAddress: "0x00005D60U" },
];
let SDFMMemoryMap = [
	{ name: "SDFM1_BASE", displayName: "SDFM1", baseAddress: "0x00005E00U" },
	{ name: "SDFM2_BASE", displayName: "SDFM2", baseAddress: "0x00005E80U" },
];
let MCBSPMemoryMap = [
	{ name: "MCBSPA_BASE", displayName: "MCBSPA", baseAddress: "0x00006000U" },
	{ name: "MCBSPB_BASE", displayName: "MCBSPB", baseAddress: "0x00006040U" },
];
let SPIMemoryMap = [
	{ name: "SPIA_BASE", displayName: "SPIA", baseAddress: "0x00006100U" },
	{ name: "SPIB_BASE", displayName: "SPIB", baseAddress: "0x00006110U" },
	{ name: "SPIC_BASE", displayName: "SPIC", baseAddress: "0x00006120U" },
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
	{ name: "SCID_BASE", displayName: "SCID", baseAddress: "0x00007230U" },
];
let I2CMemoryMap = [
	{ name: "I2CA_BASE", displayName: "I2CA", baseAddress: "0x00007300U" },
	{ name: "I2CB_BASE", displayName: "I2CB", baseAddress: "0x00007340U" },
];
let ADCMemoryMap = [
	{ name: "ADCA_BASE", displayName: "ADCA", baseAddress: "0x00007400U" },
	{ name: "ADCB_BASE", displayName: "ADCB", baseAddress: "0x00007480U" },
	{ name: "ADCD_BASE", displayName: "ADCD", baseAddress: "0x00007580U" },
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
let DMACLASRCSELMemoryMap = [
	{ name: "DMACLASRCSEL_BASE", displayName: "DMACLASRCSEL", baseAddress: "0x00007980U" },
];
let EPWMXBARMemoryMap = [
	{ name: "EPWMXBAR_BASE", displayName: "EPWMXBAR", baseAddress: "0x00007A00U" },
];
let CLBXBARMemoryMap = [
	{ name: "CLBXBAR_BASE", displayName: "CLBXBAR", baseAddress: "0x00007A40U" },
];
let OUTPUTXBARMemoryMap = [
	{ name: "OUTPUTXBAR_BASE", displayName: "OUTPUTXBAR", baseAddress: "0x00007A80U" },
];
let GPIOMemoryMap = [
	{ name: "GPIOCTRL_BASE", displayName: "GPIOCTRL", baseAddress: "0x00007C00U" },
	{ name: "GPIODATA_BASE", displayName: "GPIODATA", baseAddress: "0x00007F00U" },
];
let LSxMemoryMap = [
	{ name: "LS0_RAM_BASE", displayName: "LS0 RAM", baseAddress: "0x00008000U" },
	{ name: "LS1_RAM_BASE", displayName: "LS1 RAM", baseAddress: "0x00008800U" },
	{ name: "LS2_RAM_BASE", displayName: "LS2 RAM", baseAddress: "0x00009000U" },
	{ name: "LS3_RAM_BASE", displayName: "LS3 RAM", baseAddress: "0x00009800U" },
	{ name: "LS4_RAM_BASE", displayName: "LS4 RAM", baseAddress: "0x0000A000U" },
	{ name: "LS5_RAM_BASE", displayName: "LS5 RAM", baseAddress: "0x0000A800U" },
];
let DxMemoryMap = [
	{ name: "D0_RAM_BASE", displayName: "D0 RAM", baseAddress: "0x0000B000U" },
	{ name: "D1_RAM_BASE", displayName: "D1 RAM", baseAddress: "0x0000B800U" },
];
let GSxMemoryMap = [
	{ name: "GS0_RAM_BASE", displayName: "GS0 RAM", baseAddress: "0x0000C000U" },
	{ name: "GS1_RAM_BASE", displayName: "GS1 RAM", baseAddress: "0x0000D000U" },
	{ name: "GS2_RAM_BASE", displayName: "GS2 RAM", baseAddress: "0x0000E000U" },
	{ name: "GS3_RAM_BASE", displayName: "GS3 RAM", baseAddress: "0x0000F000U" },
	{ name: "GS4_RAM_BASE", displayName: "GS4 RAM", baseAddress: "0x00010000U" },
	{ name: "GS5_RAM_BASE", displayName: "GS5 RAM", baseAddress: "0x00011000U" },
	{ name: "GS6_RAM_BASE", displayName: "GS6 RAM", baseAddress: "0x00012000U" },
	{ name: "GS7_RAM_BASE", displayName: "GS7 RAM", baseAddress: "0x00013000U" },
];
let USBAMemoryMap = [
	{ name: "USBA_BASE", displayName: "USBA", baseAddress: "0x00040000U" },
];
let EMIFMemoryMap = [
	{ name: "EMIF1_BASE", displayName: "EMIF1", baseAddress: "0x00047000U" },
];
let CANAMemoryMap = [
	{ name: "CANA_BASE", displayName: "CANA", baseAddress: "0x00048000U" },
	{ name: "CANA_MSG_RAM_BASE", displayName: "CANA MSG RAM", baseAddress: "0x00049000U" },
	{ name: "CANB_BASE", displayName: "CANB", baseAddress: "0x0004A000U" },
	{ name: "CANB_MSG_RAM_BASE", displayName: "CANB MSG RAM", baseAddress: "0x0004B000U" },
];
let DEVCFGMemoryMap = [
	{ name: "DEVCFG_BASE", displayName: "DEVCFG", baseAddress: "0x0005D000U" },
];
let ANALOGSUBSYSMemoryMap = [
	{ name: "ANALOGSUBSYS_BASE", displayName: "ANALOGSUBSYS", baseAddress: "0x0005D180U" },
];
let CLKCFGMemoryMap = [
	{ name: "CLKCFG_BASE", displayName: "CLKCFG", baseAddress: "0x0005D200U" },
];
let CPUSYSMemoryMap = [
	{ name: "CPUSYS_BASE", displayName: "CPUSYS", baseAddress: "0x0005D300U" },
];
let ROMPREFETCHMemoryMap = [
	{ name: "ROMPREFETCH_BASE", displayName: "ROMPREFETCH", baseAddress: "0x0005E608U" },
];
let DCSMMemoryMap = [
	{ name: "DCSM_Z1_BASE", displayName: "DCSM Z1", baseAddress: "0x0005F000U" },
	{ name: "DCSM_Z2_BASE", displayName: "DCSM Z2", baseAddress: "0x0005F040U" },
	{ name: "DCSMCOMMON_BASE", displayName: "DCSMCOMMON", baseAddress: "0x0005F070U" },
];
let MEMCFGMemoryMap = [
	{ name: "MEMCFG_BASE", displayName: "MEMCFG", baseAddress: "0x0005F400U" },
];
let EMIF1CONFIGMemoryMap = [
	{ name: "EMIF1CONFIG_BASE", displayName: "EMIF1CONFIG", baseAddress: "0x0005F480U" },
];
let ACCESSPROTECTIONMemoryMap = [
	{ name: "ACCESSPROTECTION_BASE", displayName: "ACCESSPROTECTION", baseAddress: "0x0005F4C0U" },
];
let MEMORYERRORMemoryMap = [
	{ name: "MEMORYERROR_BASE", displayName: "MEMORYERROR", baseAddress: "0x0005F500U" },
];
let ROMWAITSTATEMemoryMap = [
	{ name: "ROMWAITSTATE_BASE", displayName: "ROMWAITSTATE", baseAddress: "0x0005F540U" },
];
let FLASH0MemoryMap = [
	{ name: "FLASH0CTRL_BASE", displayName: "FLASH0CTRL", baseAddress: "0x0005F800U" },
	{ name: "FLASH0ECC_BASE", displayName: "FLASH0ECC", baseAddress: "0x0005FB00U" },
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
	DMAMemoryMap: DMAMemoryMap,
	CLAMemoryMap: CLAMemoryMap,
	CLBMemoryMap: CLBMemoryMap,
	EPWMMemoryMap: EPWMMemoryMap,
	ECAPMemoryMap: ECAPMemoryMap,
	EQEPMemoryMap: EQEPMemoryMap,
	DACMemoryMap: DACMemoryMap,
	CMPSSMemoryMap: CMPSSMemoryMap,
	SDFMMemoryMap: SDFMMemoryMap,
	MCBSPMemoryMap: MCBSPMemoryMap,
	SPIMemoryMap: SPIMemoryMap,
	WDMemoryMap: WDMemoryMap,
	NMIMemoryMap: NMIMemoryMap,
	XINTMemoryMap: XINTMemoryMap,
	SCIMemoryMap: SCIMemoryMap,
	I2CMemoryMap: I2CMemoryMap,
	ADCMemoryMap: ADCMemoryMap,
	INPUTXBARMemoryMap: INPUTXBARMemoryMap,
	XBARMemoryMap: XBARMemoryMap,
	SYNCSOCMemoryMap: SYNCSOCMemoryMap,
	DMACLASRCSELMemoryMap: DMACLASRCSELMemoryMap,
	EPWMXBARMemoryMap: EPWMXBARMemoryMap,
	CLBXBARMemoryMap: CLBXBARMemoryMap,
	OUTPUTXBARMemoryMap: OUTPUTXBARMemoryMap,
	GPIOMemoryMap: GPIOMemoryMap,
	LSxMemoryMap: LSxMemoryMap,
	DxMemoryMap: DxMemoryMap,
	GSxMemoryMap: GSxMemoryMap,
	USBAMemoryMap: USBAMemoryMap,
	EMIFMemoryMap: EMIFMemoryMap,
	CANAMemoryMap: CANAMemoryMap,
	DEVCFGMemoryMap: DEVCFGMemoryMap,
	ANALOGSUBSYSMemoryMap: ANALOGSUBSYSMemoryMap,
	CLKCFGMemoryMap: CLKCFGMemoryMap,
	CPUSYSMemoryMap: CPUSYSMemoryMap,
	ROMPREFETCHMemoryMap: ROMPREFETCHMemoryMap,
	DCSMMemoryMap: DCSMMemoryMap,
	MEMCFGMemoryMap: MEMCFGMemoryMap,
	EMIF1CONFIGMemoryMap: EMIF1CONFIGMemoryMap,
	ACCESSPROTECTIONMemoryMap: ACCESSPROTECTIONMemoryMap,
	MEMORYERRORMemoryMap: MEMORYERRORMemoryMap,
	ROMWAITSTATEMemoryMap: ROMWAITSTATEMemoryMap,
	FLASH0MemoryMap: FLASH0MemoryMap,
	DCSM_OTPMemoryMap: DCSM_OTPMemoryMap,
	DeviceMemoryMap: DeviceMemoryMap,
}
