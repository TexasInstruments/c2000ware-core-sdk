let DeviceMemoryMap = [
	{ name: "M0_RAM_BASE", displayName: "M0 RAM", baseAddress: "0x00000000U" },
	{ name: "M1_RAM_BASE", displayName: "M1 RAM", baseAddress: "0x00000400U" },
	{ name: "ADCARESULT_BASE", displayName: "ADCARESULT", baseAddress: "0x00000A00U" },
	{ name: "ADCBRESULT_BASE", displayName: "ADCBRESULT", baseAddress: "0x00000A80U" },
	{ name: "ADCCRESULT_BASE", displayName: "ADCCRESULT", baseAddress: "0x00000B00U" },
	{ name: "CPUTIMER0_BASE", displayName: "CPUTIMER0", baseAddress: "0x00000C00U" },
	{ name: "CLA1_ONLY_BASE", displayName: "CLA1 ONLY", baseAddress: "0x00000C00U" },
	{ name: "CPUTIMER1_BASE", displayName: "CPUTIMER1", baseAddress: "0x00000C08U" },
	{ name: "CPUTIMER2_BASE", displayName: "CPUTIMER2", baseAddress: "0x00000C10U" },
	{ name: "CLA1_SOFTINT_BASE", displayName: "CLA1 SOFTINT", baseAddress: "0x00000CE0U" },
	{ name: "PIECTRL_BASE", displayName: "PIECTRL", baseAddress: "0x00000CE0U" },
	{ name: "PIEVECTTABLEMAIN_BASE", displayName: "PIEVECTTABLEMAIN", baseAddress: "0x00000D00U" },
	{ name: "PIEVECTTABLEEXTENSION_BASE 0x00000E00", displayName: "PIEVECTTABLEEXTENSION", baseAddress: "0x00000E00U" },
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
	{ name: "CLATODMA_RAM_BASE", displayName: "CLATODMA RAM", baseAddress: "0x00001680U" },
	{ name: "DMATOCLA_RAM_BASE", displayName: "DMATOCLA RAM", baseAddress: "0x00001700U" },
	{ name: "CLB1_BASE", displayName: "CLB1", baseAddress: "0x00002000U" },
	{ name: "CLB1_LOGICCFG_BASE", displayName: "CLB1 LOGICCFG", baseAddress: "0x00002000U" },
	{ name: "CLB1_LOGICCTRL_BASE", displayName: "CLB1 LOGICCTRL", baseAddress: "0x00002100U" },
	{ name: "CLB1_DATAEXCH_BASE", displayName: "CLB1 DATAEXCH", baseAddress: "0x00002180U" },
	{ name: "CLB2_BASE", displayName: "CLB2", baseAddress: "0x00002200U" },
	{ name: "CLB2_LOGICCFG_BASE", displayName: "CLB2 LOGICCFG", baseAddress: "0x00002200U" },
	{ name: "CLB2_LOGICCTRL_BASE", displayName: "CLB2 LOGICCTRL", baseAddress: "0x00002300U" },
	{ name: "CLB2_DATAEXCH_BASE", displayName: "CLB2 DATAEXCH", baseAddress: "0x00002380U" },
	{ name: "CLB3_BASE", displayName: "CLB3", baseAddress: "0x00002400U" },
	{ name: "CLB3_LOGICCFG_BASE", displayName: "CLB3 LOGICCFG", baseAddress: "0x00002400U" },
	{ name: "CLB3_LOGICCTRL_BASE", displayName: "CLB3 LOGICCTRL", baseAddress: "0x00002500U" },
	{ name: "CLB3_DATAEXCH_BASE", displayName: "CLB3 DATAEXCH", baseAddress: "0x00002580U" },
	{ name: "CLB4_BASE", displayName: "CLB4", baseAddress: "0x00002600U" },
	{ name: "CLB4_LOGICCFG_BASE", displayName: "CLB4 LOGICCFG", baseAddress: "0x00002600U" },
	{ name: "CLB4_LOGICCTRL_BASE", displayName: "CLB4 LOGICCTRL", baseAddress: "0x00002700U" },
	{ name: "CLB4_DATAEXCH_BASE", displayName: "CLB4 DATAEXCH", baseAddress: "0x00002780U" },
	{ name: "CLB5_BASE", displayName: "CLB5", baseAddress: "0x00002800U" },
	{ name: "CLB5_LOGICCFG_BASE", displayName: "CLB5 LOGICCFG", baseAddress: "0x00002800U" },
	{ name: "CLB5_LOGICCTRL_BASE", displayName: "CLB5 LOGICCTRL", baseAddress: "0x00002900U" },
	{ name: "CLB5_DATAEXCH_BASE", displayName: "CLB5 DATAEXCH", baseAddress: "0x00002980U" },
	{ name: "CLB6_BASE", displayName: "CLB6", baseAddress: "0x00002A00U" },
	{ name: "CLB6_LOGICCFG_BASE", displayName: "CLB6 LOGICCFG", baseAddress: "0x00002A00U" },
	{ name: "CLB6_LOGICCTRL_BASE", displayName: "CLB6 LOGICCTRL", baseAddress: "0x00002B00U" },
	{ name: "CLB6_DATAEXCH_BASE", displayName: "CLB6 DATAEXCH", baseAddress: "0x00002B80U" },
	{ name: "EPWM17_BASE", displayName: "EPWM17", baseAddress: "0x00002C00U" },
	{ name: "EPWM18_BASE", displayName: "EPWM18", baseAddress: "0x00002E00U" },
	{ name: "EPWM1_BASE", displayName: "EPWM1", baseAddress: "0x00003000U" },
	{ name: "EPWM2_BASE", displayName: "EPWM2", baseAddress: "0x00003200U" },
	{ name: "EPWM3_BASE", displayName: "EPWM3", baseAddress: "0x00003400U" },
	{ name: "EPWM4_BASE", displayName: "EPWM4", baseAddress: "0x00003600U" },
	{ name: "EPWM5_BASE", displayName: "EPWM5", baseAddress: "0x00003800U" },
	{ name: "EPWM6_BASE", displayName: "EPWM6", baseAddress: "0x00003A00U" },
	{ name: "EPWM7_BASE", displayName: "EPWM7", baseAddress: "0x00003C00U" },
	{ name: "EPWM8_BASE", displayName: "EPWM8", baseAddress: "0x00003E00U" },
	{ name: "EPWM9_BASE", displayName: "EPWM9", baseAddress: "0x00004000U" },
	{ name: "LS8_RAM_BASE", displayName: "LS8 RAM", baseAddress: "0x00004000U" },
	{ name: "EPWM10_BASE", displayName: "EPWM10", baseAddress: "0x00004200U" },
	{ name: "EPWM11_BASE", displayName: "EPWM11", baseAddress: "0x00004400U" },
	{ name: "EPWM12_BASE", displayName: "EPWM12", baseAddress: "0x00004600U" },
	{ name: "EPWM13_BASE", displayName: "EPWM13", baseAddress: "0x00004800U" },
	{ name: "EPWM14_BASE", displayName: "EPWM14", baseAddress: "0x00004A00U" },
	{ name: "EPWM15_BASE", displayName: "EPWM15", baseAddress: "0x00004C00U" },
	{ name: "EPWM16_BASE", displayName: "EPWM16", baseAddress: "0x00004E00U" },
	{ name: "EQEP1_BASE", displayName: "EQEP1", baseAddress: "0x00005080U" },
	{ name: "EQEP2_BASE", displayName: "EQEP2", baseAddress: "0x000050C0U" },
	{ name: "EQEP3_BASE", displayName: "EQEP3", baseAddress: "0x00005100U" },
	{ name: "EQEP4_BASE", displayName: "EQEP4", baseAddress: "0x00005140U" },
	{ name: "EQEP5_BASE", displayName: "EQEP5", baseAddress: "0x00005180U" },
	{ name: "EQEP6_BASE", displayName: "EQEP6", baseAddress: "0x000051C0U" },
	{ name: "ECAP1_BASE", displayName: "ECAP1", baseAddress: "0x00005200U" },
	{ name: "ECAP1SIGNALMONITORING_BASE 0x00005240", displayName: "ECAP1SIGNALMONITORING", baseAddress: "0x00005240U" },
	{ name: "ECAP2_BASE", displayName: "ECAP2", baseAddress: "0x00005300U" },
	{ name: "ECAP2SIGNALMONITORING_BASE 0x00005340", displayName: "ECAP2SIGNALMONITORING", baseAddress: "0x00005340U" },
	{ name: "ECAP3_BASE", displayName: "ECAP3", baseAddress: "0x00005400U" },
	{ name: "ECAP3SIGNALMONITORING_BASE 0x00005440", displayName: "ECAP3SIGNALMONITORING", baseAddress: "0x00005440U" },
	{ name: "ECAP4_BASE", displayName: "ECAP4", baseAddress: "0x00005500U" },
	{ name: "ECAP4SIGNALMONITORING_BASE 0x00005540", displayName: "ECAP4SIGNALMONITORING", baseAddress: "0x00005540U" },
	{ name: "ECAP5_BASE", displayName: "ECAP5", baseAddress: "0x00005600U" },
	{ name: "ECAP5SIGNALMONITORING_BASE 0x00005640", displayName: "ECAP5SIGNALMONITORING", baseAddress: "0x00005640U" },
	{ name: "ECAP6_BASE", displayName: "ECAP6", baseAddress: "0x00005700U" },
	{ name: "HRCAP6_BASE", displayName: "HRCAP6", baseAddress: "0x00005720U" },
	{ name: "ECAP6SIGNALMONITORING_BASE 0x00005740", displayName: "ECAP6SIGNALMONITORING", baseAddress: "0x00005740U" },
	{ name: "ECAP7_BASE", displayName: "ECAP7", baseAddress: "0x00005800U" },
	{ name: "HRCAP7_BASE", displayName: "HRCAP7", baseAddress: "0x00005820U" },
	{ name: "ECAP7SIGNALMONITORING_BASE 0x00005840", displayName: "ECAP7SIGNALMONITORING", baseAddress: "0x00005840U" },
	{ name: "CMPSS1_BASE", displayName: "CMPSS1", baseAddress: "0x00005900U" },
	{ name: "CMPSS2_BASE", displayName: "CMPSS2", baseAddress: "0x00005940U" },
	{ name: "CMPSS3_BASE", displayName: "CMPSS3", baseAddress: "0x00005980U" },
	{ name: "CMPSS4_BASE", displayName: "CMPSS4", baseAddress: "0x000059C0U" },
	{ name: "CMPSS5_BASE", displayName: "CMPSS5", baseAddress: "0x00005A00U" },
	{ name: "CMPSS6_BASE", displayName: "CMPSS6", baseAddress: "0x00005A40U" },
	{ name: "CMPSS7_BASE", displayName: "CMPSS7", baseAddress: "0x00005A80U" },
	{ name: "CMPSS8_BASE", displayName: "CMPSS8", baseAddress: "0x00005AC0U" },
	{ name: "CMPSS9_BASE", displayName: "CMPSS9", baseAddress: "0x00005B00U" },
	{ name: "CMPSS10_BASE", displayName: "CMPSS10", baseAddress: "0x00005B40U" },
	{ name: "CMPSS11_BASE", displayName: "CMPSS11", baseAddress: "0x00005B80U" },
	{ name: "DACA_BASE", displayName: "DACA", baseAddress: "0x00005C00U" },
	{ name: "DACC_BASE", displayName: "DACC", baseAddress: "0x00005C20U" },
	{ name: "HRPWMCAL1_BASE", displayName: "HRPWMCAL1", baseAddress: "0x00005C80U" },
	{ name: "HRPWMCAL2_BASE", displayName: "HRPWMCAL2", baseAddress: "0x00005CC0U" },
	{ name: "HRPWMCAL3_BASE", displayName: "HRPWMCAL3", baseAddress: "0x00005D00U" },
	{ name: "SDFM1_BASE", displayName: "SDFM1", baseAddress: "0x00005E00U" },
	{ name: "SDFM2_BASE", displayName: "SDFM2", baseAddress: "0x00005E80U" },
	{ name: "SDFM3_BASE", displayName: "SDFM3", baseAddress: "0x00005F00U" },
	{ name: "SDFM4_BASE", displayName: "SDFM4", baseAddress: "0x00005F80U" },
	{ name: "LS9_RAM_BASE", displayName: "LS9 RAM", baseAddress: "0x00006000U" },
	{ name: "SPIA_BASE", displayName: "SPIA", baseAddress: "0x00006100U" },
	{ name: "SPIB_BASE", displayName: "SPIB", baseAddress: "0x00006110U" },
	{ name: "SPIC_BASE", displayName: "SPIC", baseAddress: "0x00006120U" },
	{ name: "SPID_BASE", displayName: "SPID", baseAddress: "0x00006130U" },
	{ name: "BGCRC_CPU_BASE", displayName: "BGCRC CPU", baseAddress: "0x00006340U" },
	{ name: "BGCRC_CLA1_BASE", displayName: "BGCRC CLA1", baseAddress: "0x00006380U" },
	{ name: "PMBUSA_BASE", displayName: "PMBUSA", baseAddress: "0x00006400U" },
	{ name: "FSITXA_BASE", displayName: "FSITXA", baseAddress: "0x00006600U" },
	{ name: "FSIRXA_BASE", displayName: "FSIRXA", baseAddress: "0x00006680U" },
	{ name: "FSITXB_BASE", displayName: "FSITXB", baseAddress: "0x00006700U" },
	{ name: "FSIRXB_BASE", displayName: "FSIRXB", baseAddress: "0x00006780U" },
	{ name: "FSIRXC_BASE", displayName: "FSIRXC", baseAddress: "0x00006880U" },
	{ name: "FSIRXD_BASE", displayName: "FSIRXD", baseAddress: "0x00006980U" },
	{ name: "LINA_BASE", displayName: "LINA", baseAddress: "0x00006E00U" },
	{ name: "LINB_BASE", displayName: "LINB", baseAddress: "0x00006F00U" },
	{ name: "WD_BASE", displayName: "WD", baseAddress: "0x00007000U" },
	{ name: "NMI_BASE", displayName: "NMI", baseAddress: "0x00007060U" },
	{ name: "XINT_BASE", displayName: "XINT", baseAddress: "0x00007070U" },
	{ name: "SCIA_BASE", displayName: "SCIA", baseAddress: "0x00007200U" },
	{ name: "SCIB_BASE", displayName: "SCIB", baseAddress: "0x00007210U" },
	{ name: "I2CA_BASE", displayName: "I2CA", baseAddress: "0x00007300U" },
	{ name: "I2CB_BASE", displayName: "I2CB", baseAddress: "0x00007340U" },
	{ name: "ADCA_BASE", displayName: "ADCA", baseAddress: "0x00007400U" },
	{ name: "ADCB_BASE", displayName: "ADCB", baseAddress: "0x00007500U" },
	{ name: "ADCC_BASE", displayName: "ADCC", baseAddress: "0x00007600U" },
	{ name: "EPWMXBARB_BASE", displayName: "EPWMXBARB", baseAddress: "0x00007800U" },
	{ name: "SYNCSOC_BASE", displayName: "SYNCSOC", baseAddress: "0x000078F8U" },
	{ name: "INPUTXBAR_BASE", displayName: "INPUTXBAR", baseAddress: "0x00007900U" },
	{ name: "XBAR_BASE", displayName: "XBAR", baseAddress: "0x00007920U" },
	{ name: "CLBINPUTXBAR_BASE", displayName: "CLBINPUTXBAR", baseAddress: "0x00007960U" },
	{ name: "DMACLASRCSEL_BASE", displayName: "DMACLASRCSEL", baseAddress: "0x00007980U" },
	{ name: "MINDBXBAR_BASE", displayName: "MINDBXBAR", baseAddress: "0x000079C0U" },
	{ name: "ICLXBAR_BASE", displayName: "ICLXBAR", baseAddress: "0x000079E0U" },
	{ name: "EPWMXBARA_BASE", displayName: "EPWMXBARA", baseAddress: "0x00007A00U" },
	{ name: "CLBXBAR_BASE", displayName: "CLBXBAR", baseAddress: "0x00007A80U" },
	{ name: "OUTPUTXBAR_BASE", displayName: "OUTPUTXBAR", baseAddress: "0x00007B00U" },
	{ name: "CLBOUTPUTXBAR_BASE", displayName: "CLBOUTPUTXBAR", baseAddress: "0x00007B80U" },
	{ name: "GPIOCTRL_BASE", displayName: "GPIOCTRL", baseAddress: "0x00007C00U" },
	{ name: "GPIODATA_BASE", displayName: "GPIODATA", baseAddress: "0x00007F00U" },
	{ name: "GPIODATAREAD_BASE", displayName: "GPIODATAREAD", baseAddress: "0x00007F80U" },
	{ name: "LFU_BASE", displayName: "LFU", baseAddress: "0x00007FE0U" },
	{ name: "D2_RAM_CPU2_BASE", displayName: "D2 RAM CPU2", baseAddress: "0x00008000U" },
	{ name: "LS0_RAM_BASE", displayName: "LS0 RAM", baseAddress: "0x00008000U" },
	{ name: "LS1_RAM_BASE", displayName: "LS1 RAM", baseAddress: "0x00008800U" },
	{ name: "LS2_RAM_BASE", displayName: "LS2 RAM", baseAddress: "0x00009000U" },
	{ name: "LS3_RAM_BASE", displayName: "LS3 RAM", baseAddress: "0x00009800U" },
	{ name: "LS4_RAM_BASE", displayName: "LS4 RAM", baseAddress: "0x0000A000U" },
	{ name: "D3_RAM_CPU2_BASE", displayName: "D3 RAM CPU2", baseAddress: "0x0000A000U" },
	{ name: "LS5_RAM_BASE", displayName: "LS5 RAM", baseAddress: "0x0000A800U" },
	{ name: "LS6_RAM_BASE", displayName: "LS6 RAM", baseAddress: "0x0000B000U" },
	{ name: "LS7_RAM_BASE", displayName: "LS7 RAM", baseAddress: "0x0000B800U" },
	{ name: "D4_RAM_CPU2_BASE", displayName: "D4 RAM CPU2", baseAddress: "0x0000C000U" },
	{ name: "D0_RAM_BASE", displayName: "D0 RAM", baseAddress: "0x0000C000U" },
	{ name: "D5_RAM_CPU2_BASE", displayName: "D5 RAM CPU2", baseAddress: "0x0000E000U" },
	{ name: "D1_RAM_BASE", displayName: "D1 RAM", baseAddress: "0x0000E000U" },
	{ name: "GS0_RAM_BASE", displayName: "GS0 RAM", baseAddress: "0x00010000U" },
	{ name: "GS1_RAM_BASE", displayName: "GS1 RAM", baseAddress: "0x00012000U" },
	{ name: "GS2_RAM_BASE", displayName: "GS2 RAM", baseAddress: "0x00014000U" },
	{ name: "GS3_RAM_BASE", displayName: "GS3 RAM", baseAddress: "0x00016000U" },
	{ name: "GS4_RAM_BASE", displayName: "GS4 RAM", baseAddress: "0x00018000U" },
	{ name: "D2_RAM_CPU1_BASE", displayName: "D2 RAM CPU1", baseAddress: "0x0001A000U" },
	{ name: "D3_RAM_CPU1_BASE", displayName: "D3 RAM CPU1", baseAddress: "0x0001C000U" },
	{ name: "D4_RAM_CPU1_BASE", displayName: "D4 RAM CPU1", baseAddress: "0x0001E000U" },
	{ name: "D5_RAM_CPU1_BASE", displayName: "D5 RAM CPU1", baseAddress: "0x00020000U" },
	{ name: "LS8_RAM_CPU1_BASE", displayName: "LS8 RAM CPU1", baseAddress: "0x00022000U" },
	{ name: "LS9_RAM_CPU1_BASE", displayName: "LS9 RAM CPU1", baseAddress: "0x00024000U" },
	{ name: "CPU1TOCPU2MSGRAM0_BASE", displayName: "CPU1TOCPU2MSGRAM0", baseAddress: "0x0003A000U" },
	{ name: "CPU2TOCPU1MSGRAM0_BASE", displayName: "CPU2TOCPU1MSGRAM0", baseAddress: "0x0003B000U" },
	{ name: "USBA_BASE", displayName: "USBA", baseAddress: "0x00040000U" },
	{ name: "AESA_BASE", displayName: "AESA", baseAddress: "0x00042000U" },
	{ name: "AESA_SS_BASE", displayName: "AESA SS", baseAddress: "0x00042C00U" },
	{ name: "EMIF1_BASE", displayName: "EMIF1", baseAddress: "0x00047000U" },
	{ name: "CANA_BASE", displayName: "CANA", baseAddress: "0x00048000U" },
	{ name: "CANA_MSG_RAM_BASE", displayName: "CANA MSG RAM", baseAddress: "0x00049000U" },
	{ name: "LCM_CPU2_BASE", displayName: "LCM CPU2", baseAddress: "0x0004C800U" },
	{ name: "LCM_CPU2_DMA1_BASE", displayName: "LCM CPU2 DMA1", baseAddress: "0x0004E800U" },
	{ name: "ESC_SS_BASE", displayName: "ESC SS", baseAddress: "0x00057E00U" },
	{ name: "ESC_SS_CONFIG_BASE", displayName: "ESC SS CONFIG", baseAddress: "0x00057F00U" },
	{ name: "FLASH0CMD_BASE", displayName: "FLASH0CMD", baseAddress: "0x00058000U" },
	{ name: "MCANA_DRIVER_BASE", displayName: "MCANA DRIVER", baseAddress: "0x00059000U" },
	{ name: "MCANA_MSG_RAM_BASE", displayName: "MCANA MSG RAM", baseAddress: "0x00059000U" },
	{ name: "MCANASS_BASE", displayName: "MCANASS", baseAddress: "0x0005A400U" },
	{ name: "MCANA_BASE", displayName: "MCANA", baseAddress: "0x0005A600U" },
	{ name: "MCANA_ERROR_BASE", displayName: "MCANA ERROR", baseAddress: "0x0005A800U" },
	{ name: "MCANB_DRIVER_BASE", displayName: "MCANB DRIVER", baseAddress: "0x0005B000U" },
	{ name: "MCANB_MSG_RAM_BASE", displayName: "MCANB MSG RAM", baseAddress: "0x0005B000U" },
	{ name: "MCANBSS_BASE", displayName: "MCANBSS", baseAddress: "0x0005C400U" },
	{ name: "MCANB_BASE", displayName: "MCANB", baseAddress: "0x0005C600U" },
	{ name: "MCANB_ERROR_BASE", displayName: "MCANB ERROR", baseAddress: "0x0005C800U" },
	{ name: "IPC_CPUXTOCPUX_BASE", displayName: "IPC CPUXTOCPUX", baseAddress: "0x0005CE00U" },
	{ name: "IPC_CPUXTOCPUX_BASE", displayName: "IPC CPUXTOCPUX", baseAddress: "0x0005CE00U" },
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
	{ name: "DCC2_BASE", displayName: "DCC2", baseAddress: "0x0005E780U" },
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
	{ name: "ADCSAFETYINTEVTAGG1_BASE", displayName: "ADCSAFETYINTEVTAGG1", baseAddress: "0x0005EE00U" },
	{ name: "ADCSAFETYINTEVTAGG2_BASE", displayName: "ADCSAFETYINTEVTAGG2", baseAddress: "0x0005EE40U" },
	{ name: "ADCSAFETYCHK1_BASE", displayName: "ADCSAFETYCHK1", baseAddress: "0x0005EE80U" },
	{ name: "ADCSAFETYCHK2_BASE", displayName: "ADCSAFETYCHK2", baseAddress: "0x0005EE90U" },
	{ name: "ADCSAFETYCHK3_BASE", displayName: "ADCSAFETYCHK3", baseAddress: "0x0005EEA0U" },
	{ name: "ADCSAFETYCHK4_BASE", displayName: "ADCSAFETYCHK4", baseAddress: "0x0005EEB0U" },
	{ name: "ADCSAFETYCHK5_BASE", displayName: "ADCSAFETYCHK5", baseAddress: "0x0005EEC0U" },
	{ name: "ADCSAFETYCHK6_BASE", displayName: "ADCSAFETYCHK6", baseAddress: "0x0005EED0U" },
	{ name: "ADCSAFETYCHK7_BASE", displayName: "ADCSAFETYCHK7", baseAddress: "0x0005EEE0U" },
	{ name: "ADCSAFETYCHK8_BASE", displayName: "ADCSAFETYCHK8", baseAddress: "0x0005EEF0U" },
	{ name: "DCSM_Z1_BASE", displayName: "DCSM Z1", baseAddress: "0x0005F000U" },
	{ name: "DCSM_Z2_BASE", displayName: "DCSM Z2", baseAddress: "0x0005F080U" },
	{ name: "DCSMCOMMON_BASE", displayName: "DCSMCOMMON", baseAddress: "0x0005F0C0U" },
	{ name: "MEMCFG_BASE", displayName: "MEMCFG", baseAddress: "0x0005F400U" },
	{ name: "EMIF1CONFIG_BASE", displayName: "EMIF1CONFIG", baseAddress: "0x0005F4C0U" },
	{ name: "ACCESSPROTECTION_BASE", displayName: "ACCESSPROTECTION", baseAddress: "0x0005F500U" },
	{ name: "MEMORYERROR_BASE", displayName: "MEMORYERROR", baseAddress: "0x0005F540U" },
	{ name: "ROMWAITSTATE_BASE", displayName: "ROMWAITSTATE", baseAddress: "0x0005F580U" },
	{ name: "ROMPREFETCH_BASE", displayName: "ROMPREFETCH", baseAddress: "0x0005F588U" },
	{ name: "TESTERROR_BASE", displayName: "TESTERROR", baseAddress: "0x0005F590U" },
	{ name: "FLASH0CTRL_BASE", displayName: "FLASH0CTRL", baseAddress: "0x0005F800U" },
	{ name: "FLASH0ECC_BASE", displayName: "FLASH0ECC", baseAddress: "0x0005FB00U" },
	{ name: "ERAD_PCTRACE_CPU_BASE", displayName: "ERAD PCTRACE CPU", baseAddress: "0x0005FE00U" },
	{ name: "UARTA_BASE", displayName: "UARTA", baseAddress: "0x0006A000U" },
	{ name: "UARTB_BASE", displayName: "UARTB", baseAddress: "0x0006A800U" },
	{ name: "UID_BASE", displayName: "UID", baseAddress: "0x00072172U" },
	{ name: "DCSMBANK0_Z1OTP_BASE", displayName: "DCSMBANK0 Z1OTP", baseAddress: "0x00078000U" },
	{ name: "DCSMBANK0_Z2OTP_BASE", displayName: "DCSMBANK0 Z2OTP", baseAddress: "0x00078200U" },
];
let MxMemoryMap = [
	{ name: "M0_RAM_BASE", displayName: "M0 RAM", baseAddress: "0x00000000U" },
	{ name: "M1_RAM_BASE", displayName: "M1 RAM", baseAddress: "0x00000400U" },
];
let ADCxRESULTMemoryMap = [
	{ name: "ADCARESULT_BASE", displayName: "ADCARESULT", baseAddress: "0x00000A00U" },
	{ name: "ADCBRESULT_BASE", displayName: "ADCBRESULT", baseAddress: "0x00000A80U" },
	{ name: "ADCCRESULT_BASE", displayName: "ADCCRESULT", baseAddress: "0x00000B00U" },
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
	{ name: "PIEVECTTABLEMAIN_BASE", displayName: "PIEVECTTABLEMAIN", baseAddress: "0x00000D00U" },
	{ name: "PIEVECTTABLEEXTENSION_BASE 0x00000E00", displayName: "PIEVECTTABLEEXTENSION", baseAddress: "0x00000E00U" },
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
	{ name: "CLATODMA_RAM_BASE", displayName: "CLATODMA RAM", baseAddress: "0x00001680U" },
	{ name: "DMATOCLA_RAM_BASE", displayName: "DMATOCLA RAM", baseAddress: "0x00001700U" },
];
let CLBMemoryMap = [
	{ name: "CLB1_BASE", displayName: "CLB1", baseAddress: "0x00002000U" },
	{ name: "CLB1_LOGICCFG_BASE", displayName: "CLB1 LOGICCFG", baseAddress: "0x00002000U" },
	{ name: "CLB1_LOGICCTRL_BASE", displayName: "CLB1 LOGICCTRL", baseAddress: "0x00002100U" },
	{ name: "CLB1_DATAEXCH_BASE", displayName: "CLB1 DATAEXCH", baseAddress: "0x00002180U" },
	{ name: "CLB2_BASE", displayName: "CLB2", baseAddress: "0x00002200U" },
	{ name: "CLB2_LOGICCFG_BASE", displayName: "CLB2 LOGICCFG", baseAddress: "0x00002200U" },
	{ name: "CLB2_LOGICCTRL_BASE", displayName: "CLB2 LOGICCTRL", baseAddress: "0x00002300U" },
	{ name: "CLB2_DATAEXCH_BASE", displayName: "CLB2 DATAEXCH", baseAddress: "0x00002380U" },
	{ name: "CLB3_BASE", displayName: "CLB3", baseAddress: "0x00002400U" },
	{ name: "CLB3_LOGICCFG_BASE", displayName: "CLB3 LOGICCFG", baseAddress: "0x00002400U" },
	{ name: "CLB3_LOGICCTRL_BASE", displayName: "CLB3 LOGICCTRL", baseAddress: "0x00002500U" },
	{ name: "CLB3_DATAEXCH_BASE", displayName: "CLB3 DATAEXCH", baseAddress: "0x00002580U" },
	{ name: "CLB4_BASE", displayName: "CLB4", baseAddress: "0x00002600U" },
	{ name: "CLB4_LOGICCFG_BASE", displayName: "CLB4 LOGICCFG", baseAddress: "0x00002600U" },
	{ name: "CLB4_LOGICCTRL_BASE", displayName: "CLB4 LOGICCTRL", baseAddress: "0x00002700U" },
	{ name: "CLB4_DATAEXCH_BASE", displayName: "CLB4 DATAEXCH", baseAddress: "0x00002780U" },
	{ name: "CLB5_BASE", displayName: "CLB5", baseAddress: "0x00002800U" },
	{ name: "CLB5_LOGICCFG_BASE", displayName: "CLB5 LOGICCFG", baseAddress: "0x00002800U" },
	{ name: "CLB5_LOGICCTRL_BASE", displayName: "CLB5 LOGICCTRL", baseAddress: "0x00002900U" },
	{ name: "CLB5_DATAEXCH_BASE", displayName: "CLB5 DATAEXCH", baseAddress: "0x00002980U" },
	{ name: "CLB6_BASE", displayName: "CLB6", baseAddress: "0x00002A00U" },
	{ name: "CLB6_LOGICCFG_BASE", displayName: "CLB6 LOGICCFG", baseAddress: "0x00002A00U" },
	{ name: "CLB6_LOGICCTRL_BASE", displayName: "CLB6 LOGICCTRL", baseAddress: "0x00002B00U" },
	{ name: "CLB6_DATAEXCH_BASE", displayName: "CLB6 DATAEXCH", baseAddress: "0x00002B80U" },
];
let EPWMMemoryMap = [
	{ name: "EPWM17_BASE", displayName: "EPWM17", baseAddress: "0x00002C00U" },
	{ name: "EPWM18_BASE", displayName: "EPWM18", baseAddress: "0x00002E00U" },
	{ name: "EPWM1_BASE", displayName: "EPWM1", baseAddress: "0x00003000U" },
	{ name: "EPWM2_BASE", displayName: "EPWM2", baseAddress: "0x00003200U" },
	{ name: "EPWM3_BASE", displayName: "EPWM3", baseAddress: "0x00003400U" },
	{ name: "EPWM4_BASE", displayName: "EPWM4", baseAddress: "0x00003600U" },
	{ name: "EPWM5_BASE", displayName: "EPWM5", baseAddress: "0x00003800U" },
	{ name: "EPWM6_BASE", displayName: "EPWM6", baseAddress: "0x00003A00U" },
	{ name: "EPWM7_BASE", displayName: "EPWM7", baseAddress: "0x00003C00U" },
	{ name: "EPWM8_BASE", displayName: "EPWM8", baseAddress: "0x00003E00U" },
	{ name: "EPWM9_BASE", displayName: "EPWM9", baseAddress: "0x00004000U" },
];
let LS8RAMMemoryMap = [
	{ name: "LS8_RAM_BASE", displayName: "LS8 RAM", baseAddress: "0x00004000U" },
];
let EPWM_OTPMemoryMap = [
	{ name: "EPWM10_BASE", displayName: "EPWM10", baseAddress: "0x00004200U" },
	{ name: "EPWM11_BASE", displayName: "EPWM11", baseAddress: "0x00004400U" },
	{ name: "EPWM12_BASE", displayName: "EPWM12", baseAddress: "0x00004600U" },
	{ name: "EPWM13_BASE", displayName: "EPWM13", baseAddress: "0x00004800U" },
	{ name: "EPWM14_BASE", displayName: "EPWM14", baseAddress: "0x00004A00U" },
	{ name: "EPWM15_BASE", displayName: "EPWM15", baseAddress: "0x00004C00U" },
	{ name: "EPWM16_BASE", displayName: "EPWM16", baseAddress: "0x00004E00U" },
];
let EQEPMemoryMap = [
	{ name: "EQEP1_BASE", displayName: "EQEP1", baseAddress: "0x00005080U" },
	{ name: "EQEP2_BASE", displayName: "EQEP2", baseAddress: "0x000050C0U" },
	{ name: "EQEP3_BASE", displayName: "EQEP3", baseAddress: "0x00005100U" },
	{ name: "EQEP4_BASE", displayName: "EQEP4", baseAddress: "0x00005140U" },
	{ name: "EQEP5_BASE", displayName: "EQEP5", baseAddress: "0x00005180U" },
	{ name: "EQEP6_BASE", displayName: "EQEP6", baseAddress: "0x000051C0U" },
];
let ECAPMemoryMap = [
	{ name: "ECAP1_BASE", displayName: "ECAP1", baseAddress: "0x00005200U" },
	{ name: "ECAP1SIGNALMONITORING_BASE 0x00005240", displayName: "ECAP1SIGNALMONITORING", baseAddress: "0x00005240U" },
	{ name: "ECAP2_BASE", displayName: "ECAP2", baseAddress: "0x00005300U" },
	{ name: "ECAP2SIGNALMONITORING_BASE 0x00005340", displayName: "ECAP2SIGNALMONITORING", baseAddress: "0x00005340U" },
	{ name: "ECAP3_BASE", displayName: "ECAP3", baseAddress: "0x00005400U" },
	{ name: "ECAP3SIGNALMONITORING_BASE 0x00005440", displayName: "ECAP3SIGNALMONITORING", baseAddress: "0x00005440U" },
	{ name: "ECAP4_BASE", displayName: "ECAP4", baseAddress: "0x00005500U" },
	{ name: "ECAP4SIGNALMONITORING_BASE 0x00005540", displayName: "ECAP4SIGNALMONITORING", baseAddress: "0x00005540U" },
	{ name: "ECAP5_BASE", displayName: "ECAP5", baseAddress: "0x00005600U" },
	{ name: "ECAP5SIGNALMONITORING_BASE 0x00005640", displayName: "ECAP5SIGNALMONITORING", baseAddress: "0x00005640U" },
	{ name: "ECAP6_BASE", displayName: "ECAP6", baseAddress: "0x00005700U" },
];
let HRCAP6MemoryMap = [
	{ name: "HRCAP6_BASE", displayName: "HRCAP6", baseAddress: "0x00005720U" },
];
let ECAP_OTPMemoryMap = [
	{ name: "ECAP6SIGNALMONITORING_BASE 0x00005740", displayName: "ECAP6SIGNALMONITORING", baseAddress: "0x00005740U" },
	{ name: "ECAP7_BASE", displayName: "ECAP7", baseAddress: "0x00005800U" },
];
let HRCAP7MemoryMap = [
	{ name: "HRCAP7_BASE", displayName: "HRCAP7", baseAddress: "0x00005820U" },
];
let ECAP7SIGNALMONITORINGMemoryMap = [
	{ name: "ECAP7SIGNALMONITORING_BASE 0x00005840", displayName: "ECAP7SIGNALMONITORING", baseAddress: "0x00005840U" },
];
let CMPSSMemoryMap = [
	{ name: "CMPSS1_BASE", displayName: "CMPSS1", baseAddress: "0x00005900U" },
	{ name: "CMPSS2_BASE", displayName: "CMPSS2", baseAddress: "0x00005940U" },
	{ name: "CMPSS3_BASE", displayName: "CMPSS3", baseAddress: "0x00005980U" },
	{ name: "CMPSS4_BASE", displayName: "CMPSS4", baseAddress: "0x000059C0U" },
	{ name: "CMPSS5_BASE", displayName: "CMPSS5", baseAddress: "0x00005A00U" },
	{ name: "CMPSS6_BASE", displayName: "CMPSS6", baseAddress: "0x00005A40U" },
	{ name: "CMPSS7_BASE", displayName: "CMPSS7", baseAddress: "0x00005A80U" },
	{ name: "CMPSS8_BASE", displayName: "CMPSS8", baseAddress: "0x00005AC0U" },
	{ name: "CMPSS9_BASE", displayName: "CMPSS9", baseAddress: "0x00005B00U" },
	{ name: "CMPSS10_BASE", displayName: "CMPSS10", baseAddress: "0x00005B40U" },
	{ name: "CMPSS11_BASE", displayName: "CMPSS11", baseAddress: "0x00005B80U" },
];
let DACMemoryMap = [
	{ name: "DACA_BASE", displayName: "DACA", baseAddress: "0x00005C00U" },
	{ name: "DACC_BASE", displayName: "DACC", baseAddress: "0x00005C20U" },
];
let HRPWMCALMemoryMap = [
	{ name: "HRPWMCAL1_BASE", displayName: "HRPWMCAL1", baseAddress: "0x00005C80U" },
	{ name: "HRPWMCAL2_BASE", displayName: "HRPWMCAL2", baseAddress: "0x00005CC0U" },
	{ name: "HRPWMCAL3_BASE", displayName: "HRPWMCAL3", baseAddress: "0x00005D00U" },
];
let SDFMMemoryMap = [
	{ name: "SDFM1_BASE", displayName: "SDFM1", baseAddress: "0x00005E00U" },
	{ name: "SDFM2_BASE", displayName: "SDFM2", baseAddress: "0x00005E80U" },
	{ name: "SDFM3_BASE", displayName: "SDFM3", baseAddress: "0x00005F00U" },
	{ name: "SDFM4_BASE", displayName: "SDFM4", baseAddress: "0x00005F80U" },
];
let LS9RAMMemoryMap = [
	{ name: "LS9_RAM_BASE", displayName: "LS9 RAM", baseAddress: "0x00006000U" },
];
let SPIMemoryMap = [
	{ name: "SPIA_BASE", displayName: "SPIA", baseAddress: "0x00006100U" },
	{ name: "SPIB_BASE", displayName: "SPIB", baseAddress: "0x00006110U" },
	{ name: "SPIC_BASE", displayName: "SPIC", baseAddress: "0x00006120U" },
	{ name: "SPID_BASE", displayName: "SPID", baseAddress: "0x00006130U" },
];
let BGCRCMemoryMap = [
	{ name: "BGCRC_CPU_BASE", displayName: "BGCRC CPU", baseAddress: "0x00006340U" },
	{ name: "BGCRC_CLA1_BASE", displayName: "BGCRC CLA1", baseAddress: "0x00006380U" },
];
let PMBUSAMemoryMap = [
	{ name: "PMBUSA_BASE", displayName: "PMBUSA", baseAddress: "0x00006400U" },
];
let FSIxXAMemoryMap = [
	{ name: "FSITXA_BASE", displayName: "FSITXA", baseAddress: "0x00006600U" },
	{ name: "FSIRXA_BASE", displayName: "FSIRXA", baseAddress: "0x00006680U" },
	{ name: "FSITXB_BASE", displayName: "FSITXB", baseAddress: "0x00006700U" },
	{ name: "FSIRXB_BASE", displayName: "FSIRXB", baseAddress: "0x00006780U" },
	{ name: "FSIRXC_BASE", displayName: "FSIRXC", baseAddress: "0x00006880U" },
	{ name: "FSIRXD_BASE", displayName: "FSIRXD", baseAddress: "0x00006980U" },
];
let LINMemoryMap = [
	{ name: "LINA_BASE", displayName: "LINA", baseAddress: "0x00006E00U" },
	{ name: "LINB_BASE", displayName: "LINB", baseAddress: "0x00006F00U" },
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
	{ name: "ADCB_BASE", displayName: "ADCB", baseAddress: "0x00007500U" },
	{ name: "ADCC_BASE", displayName: "ADCC", baseAddress: "0x00007600U" },
];
let EPWMXBARBMemoryMap = [
	{ name: "EPWMXBARB_BASE", displayName: "EPWMXBARB", baseAddress: "0x00007800U" },
];
let SYNCSOCMemoryMap = [
	{ name: "SYNCSOC_BASE", displayName: "SYNCSOC", baseAddress: "0x000078F8U" },
];
let INPUTXBARMemoryMap = [
	{ name: "INPUTXBAR_BASE", displayName: "INPUTXBAR", baseAddress: "0x00007900U" },
];
let XBARMemoryMap = [
	{ name: "XBAR_BASE", displayName: "XBAR", baseAddress: "0x00007920U" },
];
let CLBINPUTXBARMemoryMap = [
	{ name: "CLBINPUTXBAR_BASE", displayName: "CLBINPUTXBAR", baseAddress: "0x00007960U" },
];
let DMACLASRCSELMemoryMap = [
	{ name: "DMACLASRCSEL_BASE", displayName: "DMACLASRCSEL", baseAddress: "0x00007980U" },
];
let MINDBXBARMemoryMap = [
	{ name: "MINDBXBAR_BASE", displayName: "MINDBXBAR", baseAddress: "0x000079C0U" },
];
let ICLXBARMemoryMap = [
	{ name: "ICLXBAR_BASE", displayName: "ICLXBAR", baseAddress: "0x000079E0U" },
];
let EPWMXBARAMemoryMap = [
	{ name: "EPWMXBARA_BASE", displayName: "EPWMXBARA", baseAddress: "0x00007A00U" },
];
let CLBXBARMemoryMap = [
	{ name: "CLBXBAR_BASE", displayName: "CLBXBAR", baseAddress: "0x00007A80U" },
];
let UTMemoryMap = [
	{ name: "OUTPUTXBAR_BASE", displayName: "OUTPUTXBAR", baseAddress: "0x00007B00U" },
	{ name: "CLBOUTPUTXBAR_BASE", displayName: "CLBOUTPUTXBAR", baseAddress: "0x00007B80U" },
];
let GPIOMemoryMap = [
	{ name: "GPIOCTRL_BASE", displayName: "GPIOCTRL", baseAddress: "0x00007C00U" },
	{ name: "GPIODATA_BASE", displayName: "GPIODATA", baseAddress: "0x00007F00U" },
	{ name: "GPIODATAREAD_BASE", displayName: "GPIODATAREAD", baseAddress: "0x00007F80U" },
];
let LFUMemoryMap = [
	{ name: "LFU_BASE", displayName: "LFU", baseAddress: "0x00007FE0U" },
];
let D2RAMCPU2MemoryMap = [
	{ name: "D2_RAM_CPU2_BASE", displayName: "D2 RAM CPU2", baseAddress: "0x00008000U" },
];
let LSxMemoryMap = [
	{ name: "LS0_RAM_BASE", displayName: "LS0 RAM", baseAddress: "0x00008000U" },
	{ name: "LS1_RAM_BASE", displayName: "LS1 RAM", baseAddress: "0x00008800U" },
	{ name: "LS2_RAM_BASE", displayName: "LS2 RAM", baseAddress: "0x00009000U" },
	{ name: "LS3_RAM_BASE", displayName: "LS3 RAM", baseAddress: "0x00009800U" },
	{ name: "LS4_RAM_BASE", displayName: "LS4 RAM", baseAddress: "0x0000A000U" },
];
let D3RAMCPU2MemoryMap = [
	{ name: "D3_RAM_CPU2_BASE", displayName: "D3 RAM CPU2", baseAddress: "0x0000A000U" },
];
let LSx_OTPMemoryMap = [
	{ name: "LS5_RAM_BASE", displayName: "LS5 RAM", baseAddress: "0x0000A800U" },
	{ name: "LS6_RAM_BASE", displayName: "LS6 RAM", baseAddress: "0x0000B000U" },
	{ name: "LS7_RAM_BASE", displayName: "LS7 RAM", baseAddress: "0x0000B800U" },
];
let DxMemoryMap = [
	{ name: "D4_RAM_CPU2_BASE", displayName: "D4 RAM CPU2", baseAddress: "0x0000C000U" },
	{ name: "D0_RAM_BASE", displayName: "D0 RAM", baseAddress: "0x0000C000U" },
	{ name: "D5_RAM_CPU2_BASE", displayName: "D5 RAM CPU2", baseAddress: "0x0000E000U" },
	{ name: "D1_RAM_BASE", displayName: "D1 RAM", baseAddress: "0x0000E000U" },
];
let GSxMemoryMap = [
	{ name: "GS0_RAM_BASE", displayName: "GS0 RAM", baseAddress: "0x00010000U" },
	{ name: "GS1_RAM_BASE", displayName: "GS1 RAM", baseAddress: "0x00012000U" },
	{ name: "GS2_RAM_BASE", displayName: "GS2 RAM", baseAddress: "0x00014000U" },
	{ name: "GS3_RAM_BASE", displayName: "GS3 RAM", baseAddress: "0x00016000U" },
	{ name: "GS4_RAM_BASE", displayName: "GS4 RAM", baseAddress: "0x00018000U" },
];
let Dx_OTPMemoryMap = [
	{ name: "D2_RAM_CPU1_BASE", displayName: "D2 RAM CPU1", baseAddress: "0x0001A000U" },
	{ name: "D3_RAM_CPU1_BASE", displayName: "D3 RAM CPU1", baseAddress: "0x0001C000U" },
	{ name: "D4_RAM_CPU1_BASE", displayName: "D4 RAM CPU1", baseAddress: "0x0001E000U" },
	{ name: "D5_RAM_CPU1_BASE", displayName: "D5 RAM CPU1", baseAddress: "0x00020000U" },
	{ name: "LS8_RAM_CPU1_BASE", displayName: "LS8 RAM CPU1", baseAddress: "0x00022000U" },
	{ name: "LS9_RAM_CPU1_BASE", displayName: "LS9 RAM CPU1", baseAddress: "0x00024000U" },
];
let TOCPUMemoryMap = [
	{ name: "CPU1TOCPU2MSGRAM0_BASE", displayName: "CPU1TOCPU2MSGRAM0", baseAddress: "0x0003A000U" },
	{ name: "CPU2TOCPU1MSGRAM0_BASE", displayName: "CPU2TOCPU1MSGRAM0", baseAddress: "0x0003B000U" },
];
let USBAMemoryMap = [
	{ name: "USBA_BASE", displayName: "USBA", baseAddress: "0x00040000U" },
];
let AESAMemoryMap = [
	{ name: "AESA_BASE", displayName: "AESA", baseAddress: "0x00042000U" },
	{ name: "AESA_SS_BASE", displayName: "AESA SS", baseAddress: "0x00042C00U" },
];
let EMIFMemoryMap = [
	{ name: "EMIF1_BASE", displayName: "EMIF1", baseAddress: "0x00047000U" },
];
let CANAMemoryMap = [
	{ name: "CANA_BASE", displayName: "CANA", baseAddress: "0x00048000U" },
	{ name: "CANA_MSG_RAM_BASE", displayName: "CANA MSG RAM", baseAddress: "0x00049000U" },
];
let LCMMemoryMap = [
	{ name: "LCM_CPU2_BASE", displayName: "LCM CPU2", baseAddress: "0x0004C800U" },
	{ name: "LCM_CPU2_DMA1_BASE", displayName: "LCM CPU2 DMA1", baseAddress: "0x0004E800U" },
];
let ESCMemoryMap = [
	{ name: "ESC_SS_BASE", displayName: "ESC SS", baseAddress: "0x00057E00U" },
	{ name: "ESC_SS_CONFIG_BASE", displayName: "ESC SS CONFIG", baseAddress: "0x00057F00U" },
];
let FLASH0CMDMemoryMap = [
	{ name: "FLASH0CMD_BASE", displayName: "FLASH0CMD", baseAddress: "0x00058000U" },
];
let MCANAMemoryMap = [
	{ name: "MCANA_DRIVER_BASE", displayName: "MCANA DRIVER", baseAddress: "0x00059000U" },
	{ name: "MCANA_MSG_RAM_BASE", displayName: "MCANA MSG RAM", baseAddress: "0x00059000U" },
	{ name: "MCANASS_BASE", displayName: "MCANASS", baseAddress: "0x0005A400U" },
	{ name: "MCANA_BASE", displayName: "MCANA", baseAddress: "0x0005A600U" },
	{ name: "MCANA_ERROR_BASE", displayName: "MCANA ERROR", baseAddress: "0x0005A800U" },
	{ name: "MCANB_DRIVER_BASE", displayName: "MCANB DRIVER", baseAddress: "0x0005B000U" },
	{ name: "MCANB_MSG_RAM_BASE", displayName: "MCANB MSG RAM", baseAddress: "0x0005B000U" },
	{ name: "MCANBSS_BASE", displayName: "MCANBSS", baseAddress: "0x0005C400U" },
	{ name: "MCANB_BASE", displayName: "MCANB", baseAddress: "0x0005C600U" },
	{ name: "MCANB_ERROR_BASE", displayName: "MCANB ERROR", baseAddress: "0x0005C800U" },
];
let IPCMemoryMap = [
	{ name: "IPC_CPUXTOCPUX_BASE", displayName: "IPC CPUXTOCPUX", baseAddress: "0x0005CE00U" },
	{ name: "IPC_CPUXTOCPUX_BASE", displayName: "IPC CPUXTOCPUX", baseAddress: "0x0005CE00U" },
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
	{ name: "DCC2_BASE", displayName: "DCC2", baseAddress: "0x0005E780U" },
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
let ADCSAFETYINTEVTAGGMemoryMap = [
	{ name: "ADCSAFETYINTEVTAGG1_BASE", displayName: "ADCSAFETYINTEVTAGG1", baseAddress: "0x0005EE00U" },
	{ name: "ADCSAFETYINTEVTAGG2_BASE", displayName: "ADCSAFETYINTEVTAGG2", baseAddress: "0x0005EE40U" },
];
let ADCSAFETYCHKMemoryMap = [
	{ name: "ADCSAFETYCHK1_BASE", displayName: "ADCSAFETYCHK1", baseAddress: "0x0005EE80U" },
	{ name: "ADCSAFETYCHK2_BASE", displayName: "ADCSAFETYCHK2", baseAddress: "0x0005EE90U" },
	{ name: "ADCSAFETYCHK3_BASE", displayName: "ADCSAFETYCHK3", baseAddress: "0x0005EEA0U" },
	{ name: "ADCSAFETYCHK4_BASE", displayName: "ADCSAFETYCHK4", baseAddress: "0x0005EEB0U" },
	{ name: "ADCSAFETYCHK5_BASE", displayName: "ADCSAFETYCHK5", baseAddress: "0x0005EEC0U" },
	{ name: "ADCSAFETYCHK6_BASE", displayName: "ADCSAFETYCHK6", baseAddress: "0x0005EED0U" },
	{ name: "ADCSAFETYCHK7_BASE", displayName: "ADCSAFETYCHK7", baseAddress: "0x0005EEE0U" },
	{ name: "ADCSAFETYCHK8_BASE", displayName: "ADCSAFETYCHK8", baseAddress: "0x0005EEF0U" },
];
let DCSMMemoryMap = [
	{ name: "DCSM_Z1_BASE", displayName: "DCSM Z1", baseAddress: "0x0005F000U" },
	{ name: "DCSM_Z2_BASE", displayName: "DCSM Z2", baseAddress: "0x0005F080U" },
	{ name: "DCSMCOMMON_BASE", displayName: "DCSMCOMMON", baseAddress: "0x0005F0C0U" },
];
let MEMCFGMemoryMap = [
	{ name: "MEMCFG_BASE", displayName: "MEMCFG", baseAddress: "0x0005F400U" },
];
let EMIF1CONFIGMemoryMap = [
	{ name: "EMIF1CONFIG_BASE", displayName: "EMIF1CONFIG", baseAddress: "0x0005F4C0U" },
];
let ACCESSPROTECTIONMemoryMap = [
	{ name: "ACCESSPROTECTION_BASE", displayName: "ACCESSPROTECTION", baseAddress: "0x0005F500U" },
];
let MEMORYERRORMemoryMap = [
	{ name: "MEMORYERROR_BASE", displayName: "MEMORYERROR", baseAddress: "0x0005F540U" },
];
let ROMMemoryMap = [
	{ name: "ROMWAITSTATE_BASE", displayName: "ROMWAITSTATE", baseAddress: "0x0005F580U" },
	{ name: "ROMPREFETCH_BASE", displayName: "ROMPREFETCH", baseAddress: "0x0005F588U" },
];
let TESTERRORMemoryMap = [
	{ name: "TESTERROR_BASE", displayName: "TESTERROR", baseAddress: "0x0005F590U" },
];
let FLASH0MemoryMap = [
	{ name: "FLASH0CTRL_BASE", displayName: "FLASH0CTRL", baseAddress: "0x0005F800U" },
	{ name: "FLASH0ECC_BASE", displayName: "FLASH0ECC", baseAddress: "0x0005FB00U" },
];
let ERADPCTRACECPUMemoryMap = [
	{ name: "ERAD_PCTRACE_CPU_BASE", displayName: "ERAD PCTRACE CPU", baseAddress: "0x0005FE00U" },
];
let UARTMemoryMap = [
	{ name: "UARTA_BASE", displayName: "UARTA", baseAddress: "0x0006A000U" },
	{ name: "UARTB_BASE", displayName: "UARTB", baseAddress: "0x0006A800U" },
];
let UIDMemoryMap = [
	{ name: "UID_BASE", displayName: "UID", baseAddress: "0x00072172U" },
];
let DCSMBANK0MemoryMap = [
	{ name: "DCSMBANK0_Z1OTP_BASE", displayName: "DCSMBANK0 Z1OTP", baseAddress: "0x00078000U" },
	{ name: "DCSMBANK0_Z2OTP_BASE", displayName: "DCSMBANK0 Z2OTP", baseAddress: "0x00078200U" },
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
	LS8RAMMemoryMap: LS8RAMMemoryMap,
	EPWM_OTPMemoryMap: EPWM_OTPMemoryMap,
	EQEPMemoryMap: EQEPMemoryMap,
	ECAPMemoryMap: ECAPMemoryMap,
	HRCAP6MemoryMap: HRCAP6MemoryMap,
	ECAP_OTPMemoryMap: ECAP_OTPMemoryMap,
	HRCAP7MemoryMap: HRCAP7MemoryMap,
	ECAP7SIGNALMONITORINGMemoryMap: ECAP7SIGNALMONITORINGMemoryMap,
	CMPSSMemoryMap: CMPSSMemoryMap,
	DACMemoryMap: DACMemoryMap,
	HRPWMCALMemoryMap: HRPWMCALMemoryMap,
	SDFMMemoryMap: SDFMMemoryMap,
	LS9RAMMemoryMap: LS9RAMMemoryMap,
	SPIMemoryMap: SPIMemoryMap,
	BGCRCMemoryMap: BGCRCMemoryMap,
	PMBUSAMemoryMap: PMBUSAMemoryMap,
	FSIxXAMemoryMap: FSIxXAMemoryMap,
	LINMemoryMap: LINMemoryMap,
	WDMemoryMap: WDMemoryMap,
	NMIMemoryMap: NMIMemoryMap,
	XINTMemoryMap: XINTMemoryMap,
	SCIMemoryMap: SCIMemoryMap,
	I2CMemoryMap: I2CMemoryMap,
	ADCMemoryMap: ADCMemoryMap,
	EPWMXBARBMemoryMap: EPWMXBARBMemoryMap,
	SYNCSOCMemoryMap: SYNCSOCMemoryMap,
	INPUTXBARMemoryMap: INPUTXBARMemoryMap,
	XBARMemoryMap: XBARMemoryMap,
	CLBINPUTXBARMemoryMap: CLBINPUTXBARMemoryMap,
	DMACLASRCSELMemoryMap: DMACLASRCSELMemoryMap,
	MINDBXBARMemoryMap: MINDBXBARMemoryMap,
	ICLXBARMemoryMap: ICLXBARMemoryMap,
	EPWMXBARAMemoryMap: EPWMXBARAMemoryMap,
	CLBXBARMemoryMap: CLBXBARMemoryMap,
	UTMemoryMap: UTMemoryMap,
	GPIOMemoryMap: GPIOMemoryMap,
	LFUMemoryMap: LFUMemoryMap,
	D2RAMCPU2MemoryMap: D2RAMCPU2MemoryMap,
	LSxMemoryMap: LSxMemoryMap,
	D3RAMCPU2MemoryMap: D3RAMCPU2MemoryMap,
	LSx_OTPMemoryMap: LSx_OTPMemoryMap,
	DxMemoryMap: DxMemoryMap,
	GSxMemoryMap: GSxMemoryMap,
	Dx_OTPMemoryMap: Dx_OTPMemoryMap,
	TOCPUMemoryMap: TOCPUMemoryMap,
	USBAMemoryMap: USBAMemoryMap,
	AESAMemoryMap: AESAMemoryMap,
	EMIFMemoryMap: EMIFMemoryMap,
	CANAMemoryMap: CANAMemoryMap,
	LCMMemoryMap: LCMMemoryMap,
	ESCMemoryMap: ESCMemoryMap,
	FLASH0CMDMemoryMap: FLASH0CMDMemoryMap,
	MCANAMemoryMap: MCANAMemoryMap,
	IPCMemoryMap: IPCMemoryMap,
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
	ADCSAFETYINTEVTAGGMemoryMap: ADCSAFETYINTEVTAGGMemoryMap,
	ADCSAFETYCHKMemoryMap: ADCSAFETYCHKMemoryMap,
	DCSMMemoryMap: DCSMMemoryMap,
	MEMCFGMemoryMap: MEMCFGMemoryMap,
	EMIF1CONFIGMemoryMap: EMIF1CONFIGMemoryMap,
	ACCESSPROTECTIONMemoryMap: ACCESSPROTECTIONMemoryMap,
	MEMORYERRORMemoryMap: MEMORYERRORMemoryMap,
	ROMMemoryMap: ROMMemoryMap,
	TESTERRORMemoryMap: TESTERRORMemoryMap,
	FLASH0MemoryMap: FLASH0MemoryMap,
	ERADPCTRACECPUMemoryMap: ERADPCTRACECPUMemoryMap,
	UARTMemoryMap: UARTMemoryMap,
	UIDMemoryMap: UIDMemoryMap,
	DCSMBANK0MemoryMap: DCSMBANK0MemoryMap,
	DeviceMemoryMap: DeviceMemoryMap,
}
