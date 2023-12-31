let SysCtl_PeripheralPCLOCKCR = [
	{ name: "SYSCTL_PERIPH_CLK_CLA1", displayName: "CLA1 clock" },
	{ name: "SYSCTL_PERIPH_CLK_DMA", displayName: "DMA clock" },
	{ name: "SYSCTL_PERIPH_CLK_TIMER0", displayName: "CPUTIMER0 clock" },
	{ name: "SYSCTL_PERIPH_CLK_TIMER1", displayName: "CPUTIMER1 clock" },
	{ name: "SYSCTL_PERIPH_CLK_TIMER2", displayName: "CPUTIMER2 clock" },
	{ name: "SYSCTL_PERIPH_CLK_HRPWM", displayName: "HRPWM clock" },
	{ name: "SYSCTL_PERIPH_CLK_TBCLKSYNC", displayName: "TBCLKSYNC clock" },
	{ name: "SYSCTL_PERIPH_CLK_EPWM1", displayName: "EPWM1 clock" },
	{ name: "SYSCTL_PERIPH_CLK_EPWM2", displayName: "EPWM2 clock" },
	{ name: "SYSCTL_PERIPH_CLK_EPWM3", displayName: "EPWM3 clock" },
	{ name: "SYSCTL_PERIPH_CLK_EPWM4", displayName: "EPWM4 clock" },
	{ name: "SYSCTL_PERIPH_CLK_EPWM5", displayName: "EPWM5 clock" },
	{ name: "SYSCTL_PERIPH_CLK_EPWM6", displayName: "EPWM6 clock" },
	{ name: "SYSCTL_PERIPH_CLK_EPWM7", displayName: "EPWM7 clock" },
	{ name: "SYSCTL_PERIPH_CLK_EPWM8", displayName: "EPWM8 clock" },
	{ name: "SYSCTL_PERIPH_CLK_ECAP1", displayName: "ECAP1 clock" },
	{ name: "SYSCTL_PERIPH_CLK_ECAP2", displayName: "ECAP2 clock" },
	{ name: "SYSCTL_PERIPH_CLK_ECAP3", displayName: "ECAP3 clock" },
	{ name: "SYSCTL_PERIPH_CLK_ECAP4", displayName: "ECAP4 clock" },
	{ name: "SYSCTL_PERIPH_CLK_ECAP5", displayName: "ECAP5 clock" },
	{ name: "SYSCTL_PERIPH_CLK_ECAP6", displayName: "ECAP6 clock" },
	{ name: "SYSCTL_PERIPH_CLK_ECAP7", displayName: "ECAP7 clock" },
	{ name: "SYSCTL_PERIPH_CLK_EQEP1", displayName: "EQEP1 clock" },
	{ name: "SYSCTL_PERIPH_CLK_EQEP2", displayName: "EQEP2 clock" },
	{ name: "SYSCTL_PERIPH_CLK_SD1", displayName: "SD1 clock" },
	{ name: "SYSCTL_PERIPH_CLK_SCIA", displayName: "SCI_A clock" },
	{ name: "SYSCTL_PERIPH_CLK_SCIB", displayName: "SCI_B clock" },
	{ name: "SYSCTL_PERIPH_CLK_SPIA", displayName: "SPI_A clock" },
	{ name: "SYSCTL_PERIPH_CLK_SPIB", displayName: "SPI_B clock" },
	{ name: "SYSCTL_PERIPH_CLK_I2CA", displayName: "I2C_A clock" },
	{ name: "SYSCTL_PERIPH_CLK_CANA", displayName: "CAN_A clock" },
	{ name: "SYSCTL_PERIPH_CLK_CANB", displayName: "CAN_B clock" },
	{ name: "SYSCTL_PERIPH_CLK_ADCA", displayName: "ADC_A clock" },
	{ name: "SYSCTL_PERIPH_CLK_ADCB", displayName: "ADC_B clock" },
	{ name: "SYSCTL_PERIPH_CLK_ADCC", displayName: "ADC_C clock" },
	{ name: "SYSCTL_PERIPH_CLK_CMPSS1", displayName: "CMPSS1 clock" },
	{ name: "SYSCTL_PERIPH_CLK_CMPSS2", displayName: "CMPSS2 clock" },
	{ name: "SYSCTL_PERIPH_CLK_CMPSS3", displayName: "CMPSS3 clock" },
	{ name: "SYSCTL_PERIPH_CLK_CMPSS4", displayName: "CMPSS4 clock" },
	{ name: "SYSCTL_PERIPH_CLK_CMPSS5", displayName: "CMPSS5 clock" },
	{ name: "SYSCTL_PERIPH_CLK_CMPSS6", displayName: "CMPSS6 clock" },
	{ name: "SYSCTL_PERIPH_CLK_CMPSS7", displayName: "CMPSS7 clock" },
	{ name: "SYSCTL_PERIPH_CLK_PGA1", displayName: "PGA1 clock" },
	{ name: "SYSCTL_PERIPH_CLK_PGA2", displayName: "PGA2 clock" },
	{ name: "SYSCTL_PERIPH_CLK_PGA3", displayName: "PGA3 clock" },
	{ name: "SYSCTL_PERIPH_CLK_PGA4", displayName: "PGA4 clock" },
	{ name: "SYSCTL_PERIPH_CLK_PGA5", displayName: "PGA5 clock" },
	{ name: "SYSCTL_PERIPH_CLK_PGA6", displayName: "PGA6 clock" },
	{ name: "SYSCTL_PERIPH_CLK_PGA7", displayName: "PGA7 clock" },
	{ name: "SYSCTL_PERIPH_CLK_DACA", displayName: "DAC_A clock" },
	{ name: "SYSCTL_PERIPH_CLK_DACB", displayName: "DAC_B clock" },
	{ name: "SYSCTL_PERIPH_CLK_CLB1", displayName: "CLB1 clock" },
	{ name: "SYSCTL_PERIPH_CLK_CLB2", displayName: "CLB2 clock" },
	{ name: "SYSCTL_PERIPH_CLK_CLB3", displayName: "CLB3 clock" },
	{ name: "SYSCTL_PERIPH_CLK_CLB4", displayName: "CLB4 clock" },
	{ name: "SYSCTL_PERIPH_CLK_FSITXA", displayName: "FSITX_A clock" },
	{ name: "SYSCTL_PERIPH_CLK_FSIRXA", displayName: "FSIRX_A clock" },
	{ name: "SYSCTL_PERIPH_CLK_LINA", displayName: "LIN_A clock" },
	{ name: "SYSCTL_PERIPH_CLK_PMBUSA", displayName: "PMBUS_A clock" },
	{ name: "SYSCTL_PERIPH_CLK_DCC0", displayName: "DCC_0 clock" },
]
let SysCtl_PeripheralSOFTPRES = [
	{ name: "SYSCTL_PERIPH_RES_CPU1CLA1", displayName: "Reset CPU1_CLA1 clock" },
	{ name: "SYSCTL_PERIPH_RES_EPWM1", displayName: "Reset EPWM1 clock" },
	{ name: "SYSCTL_PERIPH_RES_EPWM2", displayName: "Reset EPWM2 clock" },
	{ name: "SYSCTL_PERIPH_RES_EPWM3", displayName: "Reset EPWM3 clock" },
	{ name: "SYSCTL_PERIPH_RES_EPWM4", displayName: "Reset EPWM4 clock" },
	{ name: "SYSCTL_PERIPH_RES_EPWM5", displayName: "Reset EPWM5 clock" },
	{ name: "SYSCTL_PERIPH_RES_EPWM6", displayName: "Reset EPWM6 clock" },
	{ name: "SYSCTL_PERIPH_RES_EPWM7", displayName: "Reset EPWM7 clock" },
	{ name: "SYSCTL_PERIPH_RES_EPWM8", displayName: "Reset EPWM8 clock" },
	{ name: "SYSCTL_PERIPH_RES_ECAP1", displayName: "Reset ECAP1 clock" },
	{ name: "SYSCTL_PERIPH_RES_ECAP2", displayName: "Reset ECAP2 clock" },
	{ name: "SYSCTL_PERIPH_RES_ECAP3", displayName: "Reset ECAP3 clock" },
	{ name: "SYSCTL_PERIPH_RES_ECAP4", displayName: "Reset ECAP4 clock" },
	{ name: "SYSCTL_PERIPH_RES_ECAP5", displayName: "Reset ECAP5 clock" },
	{ name: "SYSCTL_PERIPH_RES_ECAP6", displayName: "Reset ECAP6 clock" },
	{ name: "SYSCTL_PERIPH_RES_ECAP7", displayName: "Reset ECAP7 clock" },
	{ name: "SYSCTL_PERIPH_RES_EQEP1", displayName: "Reset EQEP1 clock" },
	{ name: "SYSCTL_PERIPH_RES_EQEP2", displayName: "Reset EQEP2 clock" },
	{ name: "SYSCTL_PERIPH_RES_SD1", displayName: "Reset SD1 clock" },
	{ name: "SYSCTL_PERIPH_RES_SCIA", displayName: "Reset SCI_A clock" },
	{ name: "SYSCTL_PERIPH_RES_SCIB", displayName: "Reset SCI_B clock" },
	{ name: "SYSCTL_PERIPH_RES_SPIA", displayName: "Reset SPI_A clock" },
	{ name: "SYSCTL_PERIPH_RES_SPIB", displayName: "Reset SPI_B clock" },
	{ name: "SYSCTL_PERIPH_RES_I2CA", displayName: "Reset I2C_A clock" },
	{ name: "SYSCTL_PERIPH_RES_CANA", displayName: "Reset CAN_A clock" },
	{ name: "SYSCTL_PERIPH_RES_CANB", displayName: "Reset CAN_B clock" },
	{ name: "SYSCTL_PERIPH_RES_ADCA", displayName: "Reset ADC_A clock" },
	{ name: "SYSCTL_PERIPH_RES_ADCB", displayName: "Reset ADC_B clock" },
	{ name: "SYSCTL_PERIPH_RES_ADCC", displayName: "Reset ADC_C clock" },
	{ name: "SYSCTL_PERIPH_RES_CMPSS1", displayName: "Reset CMPSS1 clock" },
	{ name: "SYSCTL_PERIPH_RES_CMPSS2", displayName: "Reset CMPSS2 clock" },
	{ name: "SYSCTL_PERIPH_RES_CMPSS3", displayName: "Reset CMPSS3 clock" },
	{ name: "SYSCTL_PERIPH_RES_CMPSS4", displayName: "Reset CMPSS4 clock" },
	{ name: "SYSCTL_PERIPH_RES_CMPSS5", displayName: "Reset CMPSS5 clock" },
	{ name: "SYSCTL_PERIPH_RES_CMPSS6", displayName: "Reset CMPSS6 clock" },
	{ name: "SYSCTL_PERIPH_RES_CMPSS7", displayName: "Reset CMPSS7 clock" },
	{ name: "SYSCTL_PERIPH_RES_PGA1", displayName: "Reset PGA1 clock" },
	{ name: "SYSCTL_PERIPH_RES_PGA2", displayName: "Reset PGA2 clock" },
	{ name: "SYSCTL_PERIPH_RES_PGA3", displayName: "Reset PGA3 clock" },
	{ name: "SYSCTL_PERIPH_RES_PGA4", displayName: "Reset PGA4 clock" },
	{ name: "SYSCTL_PERIPH_RES_PGA5", displayName: "Reset PGA5 clock" },
	{ name: "SYSCTL_PERIPH_RES_PGA6", displayName: "Reset PGA6 clock" },
	{ name: "SYSCTL_PERIPH_RES_PGA7", displayName: "Reset PGA7 clock" },
	{ name: "SYSCTL_PERIPH_RES_DACA", displayName: "Reset DAC_A clock" },
	{ name: "SYSCTL_PERIPH_RES_DACB", displayName: "Reset DAC_B clock" },
	{ name: "SYSCTL_PERIPH_RES_CLB1", displayName: "Reset CLB1 clock" },
	{ name: "SYSCTL_PERIPH_RES_CLB2", displayName: "Reset CLB2 clock" },
	{ name: "SYSCTL_PERIPH_RES_CLB3", displayName: "Reset CLB3 clock" },
	{ name: "SYSCTL_PERIPH_RES_CLB4", displayName: "Reset CLB4 clock" },
	{ name: "SYSCTL_PERIPH_RES_LINA", displayName: "Reset LIN_A clock" },
	{ name: "SYSCTL_PERIPH_RES_PMBUSA", displayName: "Reset PMBUS_A clock" },
]
let SysCtl_WDPredivider = [
	{ name: "SYSCTL_WD_PREDIV_2", displayName: "PREDIVCLK = INTOSC1 / 2" },
	{ name: "SYSCTL_WD_PREDIV_4", displayName: "PREDIVCLK = INTOSC1 / 4" },
	{ name: "SYSCTL_WD_PREDIV_8", displayName: "PREDIVCLK = INTOSC1 / 8" },
	{ name: "SYSCTL_WD_PREDIV_16", displayName: "PREDIVCLK = INTOSC1 / 16" },
	{ name: "SYSCTL_WD_PREDIV_32", displayName: "PREDIVCLK = INTOSC1 / 32" },
	{ name: "SYSCTL_WD_PREDIV_64", displayName: "PREDIVCLK = INTOSC1 / 64" },
	{ name: "SYSCTL_WD_PREDIV_128", displayName: "PREDIVCLK = INTOSC1 / 128" },
	{ name: "SYSCTL_WD_PREDIV_256", displayName: "PREDIVCLK = INTOSC1 / 256" },
	{ name: "SYSCTL_WD_PREDIV_512", displayName: "PREDIVCLK = INTOSC1 / 512" },
	{ name: "SYSCTL_WD_PREDIV_1024", displayName: "PREDIVCLK = INTOSC1 / 1024" },
	{ name: "SYSCTL_WD_PREDIV_2048", displayName: "PREDIVCLK = INTOSC1 / 2048" },
	{ name: "SYSCTL_WD_PREDIV_4096", displayName: "PREDIVCLK = INTOSC1 / 4096" },
]
let SysCtl_WDPrescaler = [
	{ name: "SYSCTL_WD_PRESCALE_1", displayName: "WDCLK = PREDIVCLK / 1" },
	{ name: "SYSCTL_WD_PRESCALE_2", displayName: "WDCLK = PREDIVCLK / 2" },
	{ name: "SYSCTL_WD_PRESCALE_4", displayName: "WDCLK = PREDIVCLK / 4" },
	{ name: "SYSCTL_WD_PRESCALE_8", displayName: "WDCLK = PREDIVCLK / 8" },
	{ name: "SYSCTL_WD_PRESCALE_16", displayName: "WDCLK = PREDIVCLK / 16" },
	{ name: "SYSCTL_WD_PRESCALE_32", displayName: "WDCLK = PREDIVCLK / 32" },
	{ name: "SYSCTL_WD_PRESCALE_64", displayName: "WDCLK = PREDIVCLK / 64" },
]
let SysCtl_WDMode = [
	{ name: "SYSCTL_WD_MODE_RESET", displayName: "Watchdog can generate a reset signal" },
	{ name: "SYSCTL_WD_MODE_INTERRUPT", displayName: "Watchdog can generate an interrupt signal; reset signal is disabled" },
]
let SysCtl_LSPCLKPrescaler = [
	{ name: "SYSCTL_LSPCLK_PRESCALE_1", displayName: "LSPCLK = SYSCLK / 1" },
	{ name: "SYSCTL_LSPCLK_PRESCALE_2", displayName: "LSPCLK = SYSCLK / 2" },
	{ name: "SYSCTL_LSPCLK_PRESCALE_4", displayName: "LSPCLK = SYSCLK / 4 (default)" },
	{ name: "SYSCTL_LSPCLK_PRESCALE_6", displayName: "LSPCLK = SYSCLK / 6" },
	{ name: "SYSCTL_LSPCLK_PRESCALE_8", displayName: "LSPCLK = SYSCLK / 8" },
	{ name: "SYSCTL_LSPCLK_PRESCALE_10", displayName: "LSPCLK = SYSCLK / 10" },
	{ name: "SYSCTL_LSPCLK_PRESCALE_12", displayName: "LSPCLK = SYSCLK / 12" },
	{ name: "SYSCTL_LSPCLK_PRESCALE_14", displayName: "LSPCLK = SYSCLK / 14" },
]
let SysCtl_AccessPeripheral = [
	{ name: "SYSCTL_ACCESS_ADCA", displayName: "ADCA access" },
	{ name: "SYSCTL_ACCESS_ADCB", displayName: "ADCB access" },
	{ name: "SYSCTL_ACCESS_ADCC", displayName: "ADCC access" },
	{ name: "SYSCTL_ACCESS_CMPSS1", displayName: "CMPSS1 access" },
	{ name: "SYSCTL_ACCESS_CMPSS2", displayName: "CMPSS2 access" },
	{ name: "SYSCTL_ACCESS_CMPSS3", displayName: "CMPSS3 access" },
	{ name: "SYSCTL_ACCESS_CMPSS4", displayName: "CMPSS4 access" },
	{ name: "SYSCTL_ACCESS_CMPSS5", displayName: "CMPSS5 access" },
	{ name: "SYSCTL_ACCESS_CMPSS6", displayName: "CMPSS6 access" },
	{ name: "SYSCTL_ACCESS_CMPSS7", displayName: "CMPSS7 access" },
	{ name: "SYSCTL_ACCESS_DACA", displayName: "DACA access" },
	{ name: "SYSCTL_ACCESS_DACB", displayName: "DACB access" },
	{ name: "SYSCTL_ACCESS_PGA1", displayName: "PGA1 access" },
	{ name: "SYSCTL_ACCESS_PGA2", displayName: "PGA2 access" },
	{ name: "SYSCTL_ACCESS_PGA3", displayName: "PGA3 access" },
	{ name: "SYSCTL_ACCESS_PGA4", displayName: "PGA4 access" },
	{ name: "SYSCTL_ACCESS_PGA5", displayName: "PGA5 access" },
	{ name: "SYSCTL_ACCESS_PGA6", displayName: "PGA6 access" },
	{ name: "SYSCTL_ACCESS_PGA7", displayName: "PGA7 access" },
	{ name: "SYSCTL_ACCESS_EPWM1", displayName: "EPWM1 access" },
	{ name: "SYSCTL_ACCESS_EPWM2", displayName: "EPWM2 access" },
	{ name: "SYSCTL_ACCESS_EPWM3", displayName: "EPWM3 access" },
	{ name: "SYSCTL_ACCESS_EPWM4", displayName: "EPWM4 access" },
	{ name: "SYSCTL_ACCESS_EPWM5", displayName: "EPWM5 access" },
	{ name: "SYSCTL_ACCESS_EPWM6", displayName: "EPWM6 access" },
	{ name: "SYSCTL_ACCESS_EPWM7", displayName: "EPWM7 access" },
	{ name: "SYSCTL_ACCESS_EPWM8", displayName: "EPWM8 access" },
	{ name: "SYSCTL_ACCESS_EQEP1", displayName: "EQEP1 access" },
	{ name: "SYSCTL_ACCESS_EQEP2", displayName: "EQEP2 access" },
	{ name: "SYSCTL_ACCESS_ECAP1", displayName: "ECAP1 access" },
	{ name: "SYSCTL_ACCESS_ECAP2", displayName: "ECAP2 access" },
	{ name: "SYSCTL_ACCESS_ECAP3", displayName: "ECAP3 access" },
	{ name: "SYSCTL_ACCESS_ECAP4", displayName: "ECAP4 access" },
	{ name: "SYSCTL_ACCESS_ECAP5", displayName: "ECAP5 access" },
	{ name: "SYSCTL_ACCESS_ECAP6", displayName: "ECAP6 access" },
	{ name: "SYSCTL_ACCESS_ECAP7", displayName: "ECAP7 access" },
	{ name: "SYSCTL_ACCESS_SDFM1", displayName: "SDFM1 access" },
	{ name: "SYSCTL_ACCESS_CLB1", displayName: "CLB1 access" },
	{ name: "SYSCTL_ACCESS_CLB2", displayName: "CLB2 access" },
	{ name: "SYSCTL_ACCESS_CLB3", displayName: "CLB3 access" },
	{ name: "SYSCTL_ACCESS_CLB4", displayName: "CLB4 access" },
	{ name: "SYSCTL_ACCESS_CLA1PROMCRC", displayName: "CLA1PROMCRC access" },
	{ name: "SYSCTL_ACCESS_SPIA", displayName: "SPIA access" },
	{ name: "SYSCTL_ACCESS_SPIB", displayName: "SPIB access" },
	{ name: "SYSCTL_ACCESS_PMBUSA", displayName: "PMBUS_A access" },
	{ name: "SYSCTL_ACCESS_LINA", displayName: "LIN_A access" },
	{ name: "SYSCTL_ACCESS_CANA", displayName: "DCANA access" },
	{ name: "SYSCTL_ACCESS_CANB", displayName: "DCANB access" },
	{ name: "SYSCTL_ACCESS_FSIATX", displayName: "FSIATX access" },
	{ name: "SYSCTL_ACCESS_FSIARX", displayName: "FSIARX access" },
	{ name: "SYSCTL_ACCESS_HRPWMA", displayName: "HRPWM_A access" },
]
let SysCtl_AccessController = [
	{ name: "SYSCTL_ACCESS_CPU1", displayName: "CPU access to the peripheral" },
	{ name: "SYSCTL_ACCESS_CLA1", displayName: "CLA1 access to the peripheral" },
	{ name: "SYSCTL_ACCESS_DMA1", displayName: "DMA access to the peripheral" },
]
let SysCtl_AccessPermission = [
	{ name: "SYSCTL_ACCESS_FULL", displayName: "Full Access for both read and write." },
	{ name: "SYSCTL_ACCESS_PROTECTED", displayName: "Protected RD access such that FIFOs. Clear on read, registers are not changed and no write access." },
	{ name: "SYSCTL_ACCESS_NONE", displayName: "No read or write access." },
]
let SysCtl_ClockOut = [
	{ name: "SYSCTL_CLOCKOUT_PLLSYS", displayName: "PLL System Clock post SYSCLKDIV" },
	{ name: "SYSCTL_CLOCKOUT_PLLRAW", displayName: "PLL Raw Clock" },
	{ name: "SYSCTL_CLOCKOUT_SYSCLK", displayName: "CPU System Clock" },
	{ name: "SYSCTL_CLOCKOUT_INTOSC1", displayName: "Internal Oscillator 1" },
	{ name: "SYSCTL_CLOCKOUT_INTOSC2", displayName: "Internal Oscillator 2" },
	{ name: "SYSCTL_CLOCKOUT_XTALOSC", displayName: "External Oscillator" },
]
let SysCtl_ExternalOscMode = [
	{ name: "SYSCTL_XTALMODE_CRYSTAL", displayName: "XTAL Oscillator Crystal Mode" },
	{ name: "SYSCTL_XTALMODE_SINGLE", displayName: "XTAL Oscillator Single-Ended Mode" },
]
let SysCtl_SyncInput = [
	{ name: "SYSCTL_SYNC_IN_EPWM4", displayName: "Sync input to EPWM4" },
	{ name: "SYSCTL_SYNC_IN_EPWM7", displayName: "Sync input to EPWM7" },
	{ name: "SYSCTL_SYNC_IN_ECAP1", displayName: "Sync input to ECAP1" },
	{ name: "SYSCTL_SYNC_IN_ECAP4", displayName: "Sync input to ECAP4" },
	{ name: "SYSCTL_SYNC_IN_ECAP6", displayName: "Sync input to ECAP6" },
	{ name: "SYSCTL_SYNC_IN_EPWM1", displayName: "Sync input to EPWM1" },
]
let SysCtl_SyncInputSource = [
	{ name: "SYSCTL_SYNC_IN_SRC_EPWM1SYNCOUT", displayName: "EPWM1SYNCOUT" },
	{ name: "SYSCTL_SYNC_IN_SRC_EPWM4SYNCOUT", displayName: "EPWM4SYNCOUT" },
	{ name: "SYSCTL_SYNC_IN_SRC_EPWM7SYNCOUT", displayName: "EPWM7SYNCOUT" },
	{ name: "SYSCTL_SYNC_IN_SRC_ECAP1SYNCOUT", displayName: "ECAP1SYNCOUT" },
	{ name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN1", displayName: "EXTSYNCIN1--Valid for all values of syncInput" },
	{ name: "SYSCTL_SYNC_IN_SRC_EXTSYNCIN2", displayName: "EXTSYNCIN2--Valid for all values of syncInput" },
]
let SysCtl_SyncOutputSource = [
	{ name: "SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT", displayName: "EPWM1SYNCOUT --> EXTSYNCOUT" },
	{ name: "SYSCTL_SYNC_OUT_SRC_EPWM4SYNCOUT", displayName: "EPWM4SYNCOUT --> EXTSYNCOUT" },
	{ name: "SYSCTL_SYNC_OUT_SRC_EPWM7SYNCOUT", displayName: "EPWM7SYNCOUT --> EXTSYNCOUT" },
]
let SysCtl_DeviceParametric = [
	{ name: "SYSCTL_DEVICE_QUAL", displayName: "Device Qualification Status" },
	{ name: "SYSCTL_DEVICE_PINCOUNT", displayName: "Device Pin Count" },
	{ name: "SYSCTL_DEVICE_INSTASPIN", displayName: "Device InstaSPIN Feature Set" },
	{ name: "SYSCTL_DEVICE_FLASH", displayName: "Device Flash size (KB)" },
	{ name: "SYSCTL_DEVICE_FAMILY", displayName: "Device Family" },
	{ name: "SYSCTL_DEVICE_PARTNO", displayName: "Device Part Number" },
	{ name: "SYSCTL_DEVICE_CLASSID", displayName: "Device Class ID" },
]
let SysCtl_XClkDivider = [
	{ name: "SYSCTL_XCLKOUT_DIV_1", displayName: "XCLKOUT =  XCLKOUT / 1" },
	{ name: "SYSCTL_XCLKOUT_DIV_2", displayName: "XCLKOUT =  XCLKOUT / 2" },
	{ name: "SYSCTL_XCLKOUT_DIV_4", displayName: "XCLKOUT =  XCLKOUT / 4" },
	{ name: "SYSCTL_XCLKOUT_DIV_8", displayName: "XCLKOUT =  XCLKOUT / 8" },
]
let SysCtl_Cputimer2ClkDivider = [
	{ name: "SYSCTL_TMR2CLKPRESCALE_1", displayName: "Cputimer2 clock =  Cputimer2 clock / 1" },
	{ name: "SYSCTL_TMR2CLKPRESCALE_2", displayName: "Cputimer2 clock =  Cputimer2 clock / 2" },
	{ name: "SYSCTL_TMR2CLKPRESCALE_4", displayName: "Cputimer2 clock =  Cputimer2 clock / 4" },
	{ name: "SYSCTL_TMR2CLKPRESCALE_8", displayName: "Cputimer2 clock =  Cputimer2 clock / 8" },
	{ name: "SYSCTL_TMR2CLKPRESCALE_16", displayName: "Cputimer2 clock =  Cputimer2 clock / 16" },
]
let SysCtl_Cputimer2ClkSource = [
	{ name: "SYSCTL_TMR2CLKSRCSEL_SYSCLK", displayName: "System Clock" },
	{ name: "SYSCTL_TMR2CLKSRCSEL_INTOSC1", displayName: "Internal Oscillator 1" },
	{ name: "SYSCTL_TMR2CLKSRCSEL_INTOSC2", displayName: "Internal Oscillator 2" },
	{ name: "SYSCTL_TMR2CLKSRCSEL_XTAL", displayName: "Crystal oscillator" },
	{ name: "SYSCTL_TMR2CLKSRCSEL_AUXPLLCLK", displayName: "Aux PLL CLock" },
]
let SYSCTL_NMI = [
	{ name: "SYSCTL_NMI_NMIINT", displayName: "NMI Interrupt Flag" },
	{ name: "SYSCTL_NMI_CLOCKFAIL", displayName: "Clock Fail Interrupt Flag" },
	{ name: "SYSCTL_NMI_RAMUNCERR", displayName: "RAM Uncorrectable Error NMI Flag" },
	{ name: "SYSCTL_NMI_FLUNCERR", displayName: "Flash Uncorrectable Error NMI Flag" },
	{ name: "SYSCTL_NMI_PIEVECTERR", displayName: "PIE Vector Fetch Error Flag" },
	{ name: "SYSCTL_NMI_CLBNMI", displayName: "Configurable Logic Block NMI Flag" },
	{ name: "SYSCTL_NMI_SWERR", displayName: "SW Error Force NMI Flag" },
]
let SYSCTL_CAUSE = [
	{ name: "SYSCTL_CAUSE_POR", displayName: "Power-on reset" },
	{ name: "SYSCTL_CAUSE_XRS", displayName: "External reset pin" },
	{ name: "SYSCTL_CAUSE_WDRS", displayName: "Watchdog reset" },
	{ name: "SYSCTL_CAUSE_NMIWDRS", displayName: "NMI watchdog reset" },
	{ name: "SYSCTL_CAUSE_SCCRESET", displayName: "SCCRESETn by DCSM" },
]
let SYSCTL_ADCSOC_SRC = [
	{ name: "SYSCTL_ADCSOC_SRC_PWM1SOCA", displayName: "ePWM1 SOCA for ADCSOCAO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM2SOCA", displayName: "ePWM2 SOCA for ADCSOCAO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM3SOCA", displayName: "ePWM3 SOCA for ADCSOCAO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM4SOCA", displayName: "ePWM4 SOCA for ADCSOCAO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM5SOCA", displayName: "ePWM5 SOCA for ADCSOCAO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM6SOCA", displayName: "ePWM6 SOCA for ADCSOCAO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM7SOCA", displayName: "ePWM7 SOCA for ADCSOCAO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM8SOCA", displayName: "ePWM8 SOCA for ADCSOCAO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM1SOCB", displayName: "ePWM1 SOCB for ADCSOCBO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM2SOCB", displayName: "ePWM2 SOCB for ADCSOCBO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM3SOCB", displayName: "ePWM3 SOCB for ADCSOCBO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM4SOCB", displayName: "ePWM4 SOCB for ADCSOCBO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM5SOCB", displayName: "ePWM5 SOCB for ADCSOCBO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM6SOCB", displayName: "ePWM6 SOCB for ADCSOCBO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM7SOCB", displayName: "ePWM7 SOCB for ADCSOCBO" },
	{ name: "SYSCTL_ADCSOC_SRC_PWM8SOCB", displayName: "ePWM8 SOCB for ADCSOCBO" },
]
module.exports = {
	SysCtl_PeripheralPCLOCKCR: SysCtl_PeripheralPCLOCKCR,
	SysCtl_PeripheralSOFTPRES: SysCtl_PeripheralSOFTPRES,
	SysCtl_WDPredivider: SysCtl_WDPredivider,
	SysCtl_WDPrescaler: SysCtl_WDPrescaler,
	SysCtl_WDMode: SysCtl_WDMode,
	SysCtl_LSPCLKPrescaler: SysCtl_LSPCLKPrescaler,
	SysCtl_AccessPeripheral: SysCtl_AccessPeripheral,
	SysCtl_AccessController: SysCtl_AccessController,
	SysCtl_AccessPermission: SysCtl_AccessPermission,
	SysCtl_ClockOut: SysCtl_ClockOut,
	SysCtl_ExternalOscMode: SysCtl_ExternalOscMode,
	SysCtl_SyncInput: SysCtl_SyncInput,
	SysCtl_SyncInputSource: SysCtl_SyncInputSource,
	SysCtl_SyncOutputSource: SysCtl_SyncOutputSource,
	SysCtl_DeviceParametric: SysCtl_DeviceParametric,
	SysCtl_XClkDivider: SysCtl_XClkDivider,
	SysCtl_Cputimer2ClkDivider: SysCtl_Cputimer2ClkDivider,
	SysCtl_Cputimer2ClkSource: SysCtl_Cputimer2ClkSource,
	SYSCTL_NMI: SYSCTL_NMI,
	SYSCTL_CAUSE: SYSCTL_CAUSE,
	SYSCTL_ADCSOC_SRC: SYSCTL_ADCSOC_SRC,
}
