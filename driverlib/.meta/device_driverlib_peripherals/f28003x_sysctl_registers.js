let SYSCTLRegisters = [
	{ name: "PARTIDL", description: "Lower 32-bit of Device PART Identification Number", offset: "0x8",
		bits: [
			{ name: "QUAL", description: "Qualification Status", size: "2", shift: "6", mask: "0xC0" },
			{ name: "PIN_COUNT", description: "Device Pin Count", size: "3", shift: "8", mask: "0x700" },
			{ name: "INSTASPIN", description: "Instaspin feature set", size: "2", shift: "13", mask: "0x6000" },
			{ name: "FLASH_SIZE", description: "Flash size in KB", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "PARTIDH", description: "Upper 32-bit of Device PART Identification Number", offset: "0xA",
		bits: [
			{ name: "FAMILY", description: "Device family", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "PARTNO", description: "Device part number", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "DEVICE_CLASS_ID", description: "Device class ID", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "REVID", description: "Device Revision Number", offset: "0xC",
		bits: [
			{ name: "REVID", description: "Device Revision ID. This is specific to the Device", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "FUSEERR", description: "e-Fuse error Status register", offset: "0x74",
		bits: [
			{ name: "ALERR", description: "Efuse Autoload Error Status", size: "5", shift: "0", mask: "0x1F" },
			{ name: "ERR", description: "Efuse Self Test Error Status", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "SOFTPRES0", description: "Processing Block Software Reset register", offset: "0x82",
		bits: [
			{ name: "CPU1_CLA1", description: "CPU1_CLA1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPU1_CPUBGCRC", description: "CPUBGCRC Module reset bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "CPU1_CLA1BGCRC", description: "CLA1BGCRC Module reset bit", size: "1", shift: "14", mask: "0x4000" },
			{ name: "CPU1_ERAD", description: "ERAD Module reset bit", size: "1", shift: "24", mask: "0x1000000" },
		]
	},
	{ name: "SOFTPRES2", description: "EPWM Software Reset register", offset: "0x86",
		bits: [
			{ name: "EPWM1", description: "EPWM1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EPWM2", description: "EPWM2 software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "EPWM3", description: "EPWM3 software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "EPWM4", description: "EPWM4 software reset bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "EPWM5", description: "EPWM5 software reset bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "EPWM6", description: "EPWM6 software reset bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "EPWM7", description: "EPWM7 software reset bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "EPWM8", description: "EPWM8 software reset bit", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "SOFTPRES3", description: "ECAP Software Reset register", offset: "0x88",
		bits: [
			{ name: "ECAP1", description: "ECAP1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ECAP2", description: "ECAP2 software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ECAP3", description: "ECAP3 software reset bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "SOFTPRES4", description: "EQEP Software Reset register", offset: "0x8A",
		bits: [
			{ name: "EQEP1", description: "EQEP1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EQEP2", description: "EQEP2 software reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES6", description: "Sigma Delta Software Reset register", offset: "0x8E",
		bits: [
			{ name: "SD1", description: "SD1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SD2", description: "SD2 software reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES7", description: "SCI Software Reset register", offset: "0x90",
		bits: [
			{ name: "SCI_A", description: "SCI_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SCI_B", description: "SCI_B software reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES8", description: "SPI Software Reset register", offset: "0x92",
		bits: [
			{ name: "SPI_A", description: "SPI_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SPI_B", description: "SPI_B software reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES9", description: "I2C Software Reset register", offset: "0x94",
		bits: [
			{ name: "I2C_A", description: "I2C_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "I2C_B", description: "I2C_B software reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES10", description: "CAN Software Reset register", offset: "0x96",
		bits: [
			{ name: "CAN_A", description: "CAN_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "MCAN_A", description: "MCAN_A  software reset bit", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "SOFTPRES13", description: "ADC Software Reset register", offset: "0x9C",
		bits: [
			{ name: "ADC_A", description: "ADC_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B", description: "ADC_B software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADC_C", description: "ADC_C software reset bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "SOFTPRES14", description: "CMPSS Software Reset register", offset: "0x9E",
		bits: [
			{ name: "CMPSS1", description: "CMPSS1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPSS2", description: "CMPSS2 software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMPSS3", description: "CMPSS3 software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMPSS4", description: "CMPSS4 software reset bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "SOFTPRES16", description: "DAC Software Reset register", offset: "0xA2",
		bits: [
			{ name: "DAC_A", description: "Buffered_DAC_A software reset bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DAC_B", description: "Buffered_DAC_B software reset bit", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "SOFTPRES17", description: "CLB Software Reset register", offset: "0xA4",
		bits: [
			{ name: "CLB1", description: "CLB1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLB2", description: "CLB2 software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLB3", description: "CLB3 software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CLB4", description: "CLB4 software reset bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "SOFTPRES18", description: "FSI Software Reset register", offset: "0xA6",
		bits: [
			{ name: "FSITX_A", description: "FSITX_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "FSIRX_A", description: "FSIRX_A software reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES19", description: "LIN Software Reset register", offset: "0xA8",
		bits: [
			{ name: "LIN_A", description: "LIN_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "LIN_B", description: "LIN_B software reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES20", description: "PMBUS Software Reset register", offset: "0xAA",
		bits: [
			{ name: "PMBUS_A", description: "PMBUS_A software reset bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SOFTPRES21", description: "DCC Software Reset register", offset: "0xAC",
		bits: [
			{ name: "DCC0", description: "DCC Module reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "DCC1", description: "DCC Module reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES25", description: "HIC Software Reset register", offset: "0xB4",
		bits: [
			{ name: "HIC_A", description: "HIC Slave & Host controller Reset Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SOFTPRES26", description: "AES Software Reset register", offset: "0xB6",
		bits: [
			{ name: "AESA", description: "AES Module Reset Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SOFTPRES27", description: "EPG Software Reset register", offset: "0xB8",
		bits: [
			{ name: "EPG1", description: "EPG Module Reset Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SOFTPRES40", description: "Peripheral Software Reset register", offset: "0xD2",
		bits: [
			{ name: "JTAG_NTRST", description: "Multi Bit JTAG nTRST", size: "4", shift: "0", mask: "0xF" },
			{ name: "JTAG_NTRST_KEY", description: "JTAG nTRST Key", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "TAP_STATUS", description: "Status of JTAG State machine & Debugger Connect", offset: "0x130",
		bits: [
			{ name: "TAP_STATE", description: "Present TAP State", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DCON", description: "Debugger Connect Indication", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "ECAPTYPE", description: "Configures ECAP Type for the device", offset: "0x19B",
		bits: [
			{ name: "TYPE", description: "Configure ECAP type", size: "2", shift: "0", mask: "0x3" },
			{ name: "LOCK", description: "Lock bit for the register", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SDFMTYPE", description: "Configures SDFM Type for the device", offset: "0x19C",
		bits: [
			{ name: "TYPE", description: "Configure SDFM type", size: "2", shift: "0", mask: "0x3" },
			{ name: "LOCK", description: "Lock bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CLKCFGLOCK1", description: "Lock bit for CLKCFG registers", offset: "0x2",
		bits: [
			{ name: "CLKSRCCTL1", description: "Lock bit for CLKSRCCTL1 register", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLKSRCCTL2", description: "Lock bit for CLKSRCCTL2 register", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLKSRCCTL3", description: "Lock bit for CLKSRCCTL3 register", size: "1", shift: "2", mask: "0x4" },
			{ name: "SYSPLLCTL1", description: "Lock bit for SYSPLLCTL1 register", size: "1", shift: "3", mask: "0x8" },
			{ name: "SYSPLLMULT", description: "Lock bit for SYSPLLMULT register", size: "1", shift: "6", mask: "0x40" },
			{ name: "SYSCLKDIVSEL", description: "Lock bit for SYSCLKDIVSEL register", size: "1", shift: "11", mask: "0x800" },
			{ name: "AUXCLKDIVSEL", description: "Lock bit for AUXCLKDIVSEL register", size: "1", shift: "12", mask: "0x1000" },
			{ name: "CLBCLKCTL", description: "Lock bit for CLBCLKCTL register", size: "1", shift: "14", mask: "0x4000" },
			{ name: "LOSPCP", description: "Lock bit for LOSPCP register", size: "1", shift: "15", mask: "0x8000" },
			{ name: "XTALCR", description: "Lock bit for XTALCR  & XTALCR2 register", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "CLKSRCCTL1", description: "Clock Source Control register-1", offset: "0x8",
		bits: [
			{ name: "OSCCLKSRCSEL", description: "OSCCLK Source Select Bit", size: "2", shift: "0", mask: "0x3" },
			{ name: "INTOSC2OFF", description: "Internal Oscillator 2 Off Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "WDHALTI", description: "Watchdog HALT Mode Ignore Bit", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "CLKSRCCTL2", description: "Clock Source Control register-2", offset: "0xA",
		bits: [
			{ name: "CANABCLKSEL", description: "CANA Bit Clock Source Select Bit", size: "2", shift: "2", mask: "0xC" },
			{ name: "MCANABCLKSEL", description: "MCANA Bit Clock Source Select Bit", size: "2", shift: "10", mask: "0xC00" },
		]
	},
	{ name: "CLKSRCCTL3", description: "Clock Source Control register-3", offset: "0xC",
		bits: [
			{ name: "XCLKOUTSEL", description: "XCLKOUT Source Select Bit", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "SYSPLLCTL1", description: "SYSPLL Control register-1", offset: "0xE",
		bits: [
			{ name: "PLLEN", description: "SYSPLL enable/disable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "PLLCLKEN", description: "SYSPLL bypassed or included in the PLLSYSCLK path", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SYSPLLMULT", description: "SYSPLL Multiplier register", offset: "0x14",
		bits: [
			{ name: "IMULT", description: "SYSPLL Integer Multiplier", size: "8", shift: "0", mask: "0xFF" },
			{ name: "ODIV", description: "Output Clock Divider", size: "5", shift: "16", mask: "0x1F0000" },
			{ name: "REFDIV", description: "Reference Clock Divider", size: "5", shift: "24", mask: "0x1F000000" },
		]
	},
	{ name: "SYSPLLSTS", description: "SYSPLL Status register", offset: "0x16",
		bits: [
			{ name: "LOCKS", description: "SYSPLL Lock Status Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SLIPS", description: "SYSPLL Slip Status Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "REF_LOSTS", description: "SYSPLL Reference  Lost Status Bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "SYSCLKDIVSEL", description: "System Clock Divider Select register", offset: "0x22",
		bits: [
			{ name: "PLLSYSCLKDIV", description: "PLLSYSCLK Divide Select", size: "6", shift: "0", mask: "0x3F" },
			{ name: "PLLSYSCLKDIV_LSB", description: "This bit allows the odd division for the", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "AUXCLKDIVSEL", description: "Auxillary Clock Divider Select register", offset: "0x24",
		bits: [
			{ name: "MCANCLKDIV", description: "Divider between CANFD Source Clock and", size: "5", shift: "8", mask: "0x1F00" },
		]
	},
	{ name: "XCLKOUTDIVSEL", description: "XCLKOUT Divider Select register", offset: "0x28",
		bits: [
			{ name: "XCLKOUTDIV", description: "XCLKOUT Divide Select", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "CLBCLKCTL", description: "CLB Clocking Control Register", offset: "0x2A",
		bits: [
			{ name: "CLBCLKDIV", description: "CLB clock divider configuration.", size: "3", shift: "0", mask: "0x7" },
			{ name: "TILECLKDIV", description: "CLB Tile clock divider configuration.", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLKMODECLB1", description: "Clock mode of CLB1", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CLKMODECLB2", description: "Clock mode of CLB2", size: "1", shift: "17", mask: "0x20000" },
			{ name: "CLKMODECLB3", description: "Clock mode of CLB3", size: "1", shift: "18", mask: "0x40000" },
			{ name: "CLKMODECLB4", description: "Clock mode of CLB4", size: "1", shift: "19", mask: "0x80000" },
		]
	},
	{ name: "LOSPCP", description: "Low Speed Clock Source Prescalar", offset: "0x2C",
		bits: [
			{ name: "LSPCLKDIV", description: "LSPCLK Divide Select", size: "3", shift: "0", mask: "0x7" },
		]
	},
	{ name: "MCDCR", description: "Missing Clock Detect Control Register", offset: "0x2E",
		bits: [
			{ name: "MCLKSTS", description: "Missing Clock Status Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "MCLKCLR", description: "Missing Clock Clear Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "MCLKOFF", description: "Missing Clock Detect Off Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "OSCOFF", description: "Oscillator Clock Off Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "SYSREF_LOSTS", description: "SYSPLL Reference  Lost Status Bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "SYSREF_LOSTSCLR", description: "Clear for Ref clock lost status", size: "1", shift: "5", mask: "0x20" },
			{ name: "SYSREF_LOST_MCD_EN", description: "Enable for PLL REF_CLK_LOST as MCD cause", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "X1CNT", description: "10-bit Counter on X1 Clock", offset: "0x30",
		bits: [
			{ name: "X1CNT", description: "X1 Counter", size: "11", shift: "0", mask: "0x7FF" },
			{ name: "CLR", description: "X1 Counter Clear", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "XTALCR", description: "XTAL Control Register", offset: "0x32",
		bits: [
			{ name: "OSCOFF", description: "XTAL Oscillator powered-down", size: "1", shift: "0", mask: "0x1" },
			{ name: "SE", description: "XTAL Oscilator in Single-Ended mode", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "XTALCR2", description: "XTAL Control Register for pad init", offset: "0x3A",
		bits: [
			{ name: "XIF", description: "XI Initial value deposited before XOSC start", size: "1", shift: "0", mask: "0x1" },
			{ name: "XOF", description: "XO Initial value deposited before XOSC start", size: "1", shift: "1", mask: "0x2" },
			{ name: "FEN", description: "XOSC pads initialisation enable", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "CLKFAILCFG", description: "Clock Fail cause Configuration", offset: "0x3C",
		bits: [
			{ name: "DCC0_ERROR_EN", description: "DCC0 Error causes Clock fail NMI, ERROR", size: "1", shift: "0", mask: "0x1" },
			{ name: "DCC1_ERROR_EN", description: "DCC1 Error causes Clock fail NMI, ERROR", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CPUSYSLOCK1", description: "Lock bit for CPUSYS registers", offset: "0x0",
		bits: [
			{ name: "PIEVERRADDR", description: "Lock bit for PIEVERRADDR Register", size: "1", shift: "2", mask: "0x4" },
			{ name: "PCLKCR0", description: "Lock bit for PCLKCR0 Register", size: "1", shift: "3", mask: "0x8" },
			{ name: "PCLKCR2", description: "Lock bit for PCLKCR2 Register", size: "1", shift: "5", mask: "0x20" },
			{ name: "PCLKCR3", description: "Lock bit for PCLKCR3 Register", size: "1", shift: "6", mask: "0x40" },
			{ name: "PCLKCR4", description: "Lock bit for PCLKCR4 Register", size: "1", shift: "7", mask: "0x80" },
			{ name: "PCLKCR6", description: "Lock bit for PCLKCR6 Register", size: "1", shift: "9", mask: "0x200" },
			{ name: "PCLKCR7", description: "Lock bit for PCLKCR7 Register", size: "1", shift: "10", mask: "0x400" },
			{ name: "PCLKCR8", description: "Lock bit for PCLKCR8 Register", size: "1", shift: "11", mask: "0x800" },
			{ name: "PCLKCR9", description: "Lock bit for PCLKCR9 Register", size: "1", shift: "12", mask: "0x1000" },
			{ name: "PCLKCR10", description: "Lock bit for PCLKCR10 Register", size: "1", shift: "13", mask: "0x2000" },
			{ name: "PCLKCR13", description: "Lock bit for PCLKCR13 Register", size: "1", shift: "16", mask: "0x10000" },
			{ name: "PCLKCR14", description: "Lock bit for PCLKCR14 Register", size: "1", shift: "17", mask: "0x20000" },
			{ name: "PCLKCR16", description: "Lock bit for PCLKCR16 Register", size: "1", shift: "19", mask: "0x80000" },
			{ name: "LPMCR", description: "Lock bit for LPMCR Register", size: "1", shift: "21", mask: "0x200000" },
			{ name: "GPIOLPMSEL0", description: "Lock bit for GPIOLPMSEL0 Register", size: "1", shift: "22", mask: "0x400000" },
			{ name: "GPIOLPMSEL1", description: "Lock bit for GPIOLPMSEL1 Register", size: "1", shift: "23", mask: "0x800000" },
			{ name: "PCLKCR17", description: "Lock bit for PCLKCR17 Register", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "PCLKCR18", description: "Lock bit for PCLKCR18 Register", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "PCLKCR19", description: "Lock bit for PCLKCR19 Register", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "PCLKCR20", description: "Lock bit for PCLKCR20 Register", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "PCLKCR21", description: "Lock bit for PCLKCR21 Register", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "PCLKCR22", description: "Lock bit for PCLKCR22 Register", size: "1", shift: "29", mask: "0x20000000" },
		]
	},
	{ name: "CPUSYSLOCK2", description: "Lock bit for CPUSYS registers", offset: "0x2",
		bits: [
			{ name: "PCLKCR25", description: "Lock bit for PCLKCR25 Register", size: "1", shift: "1", mask: "0x2" },
			{ name: "PCLKCR26", description: "Lock bit for PCLKCR26 Register", size: "1", shift: "2", mask: "0x4" },
			{ name: "PCLKCR27", description: "Lock bit for PCLKCR27 Register", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "PIEVERRADDR", description: "PIE Vector Fetch Error Address register", offset: "0xA",
		bits: [
			{ name: "ADDR", description: "PIE Vector Fetch Error Handler Routine Address", size: "22", shift: "0", mask: "0x3FFFFF" },
		]
	},
	{ name: "PCLKCR0", description: "Peripheral Clock Gating Registers", offset: "0x22",
		bits: [
			{ name: "CLA1", description: "CLA1 Clock Enable Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMA", description: "DMA Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CPUTIMER0", description: "CPUTIMER0 Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "CPUTIMER1", description: "CPUTIMER1 Clock Enable bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "CPUTIMER2", description: "CPUTIMER2 Clock Enable bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "CPUBGCRC", description: "CPUBGCRC Clock Enable Bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "CLA1BGCRC", description: "CLA1BGCRC Clock Enable Bit", size: "1", shift: "14", mask: "0x4000" },
			{ name: "HRCAL", description: "HRCAL Clock Enable Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "TBCLKSYNC", description: "EPWM Time Base Clock sync", size: "1", shift: "18", mask: "0x40000" },
			{ name: "ERAD", description: "ERAD module clock enable", size: "1", shift: "24", mask: "0x1000000" },
		]
	},
	{ name: "PCLKCR2", description: "Peripheral Clock Gating Register - ETPWM", offset: "0x26",
		bits: [
			{ name: "EPWM1", description: "EPWM1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EPWM2", description: "EPWM2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "EPWM3", description: "EPWM3 Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "EPWM4", description: "EPWM4 Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "EPWM5", description: "EPWM5 Clock Enable bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "EPWM6", description: "EPWM6 Clock Enable bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "EPWM7", description: "EPWM7 Clock Enable bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "EPWM8", description: "EPWM8 Clock Enable bit", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "PCLKCR3", description: "Peripheral Clock Gating Register - ECAP", offset: "0x28",
		bits: [
			{ name: "ECAP1", description: "ECAP1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ECAP2", description: "ECAP2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ECAP3", description: "ECAP3 Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "PCLKCR4", description: "Peripheral Clock Gating Register - EQEP", offset: "0x2A",
		bits: [
			{ name: "EQEP1", description: "EQEP1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EQEP2", description: "EQEP2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR6", description: "Peripheral Clock Gating Register - SDFM", offset: "0x2E",
		bits: [
			{ name: "SD1", description: "SD1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SD2", description: "SD2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR7", description: "Peripheral Clock Gating Register - SCI", offset: "0x30",
		bits: [
			{ name: "SCI_A", description: "SCI_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SCI_B", description: "SCI_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR8", description: "Peripheral Clock Gating Register - SPI", offset: "0x32",
		bits: [
			{ name: "SPI_A", description: "SPI_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SPI_B", description: "SPI_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR9", description: "Peripheral Clock Gating Register - I2C", offset: "0x34",
		bits: [
			{ name: "I2C_A", description: "I2C_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "I2C_B", description: "I2C_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR10", description: "Peripheral Clock Gating Register - CAN", offset: "0x36",
		bits: [
			{ name: "CAN_A", description: "CAN_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "MCAN_A", description: "MCAN_A Clock Enable bit", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "PCLKCR13", description: "Peripheral Clock Gating Register - ADC", offset: "0x3C",
		bits: [
			{ name: "ADC_A", description: "ADC_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B", description: "ADC_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADC_C", description: "ADC_C Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "PCLKCR14", description: "Peripheral Clock Gating Register - CMPSS", offset: "0x3E",
		bits: [
			{ name: "CMPSS1", description: "CMPSS1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPSS2", description: "CMPSS2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMPSS3", description: "CMPSS3 Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMPSS4", description: "CMPSS4 Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "PCLKCR16", description: "Peripheral Clock Gating Register Buf_DAC", offset: "0x42",
		bits: [
			{ name: "DAC_A", description: "Buffered_DAC_A Clock Enable Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DAC_B", description: "Buffered_DAC_B Clock Enable Bit", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "PCLKCR17", description: "Peripheral Clock Gating Register - CLB", offset: "0x44",
		bits: [
			{ name: "CLB1", description: "CLB1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLB2", description: "CLB2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLB3", description: "CLB3 Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CLB4", description: "CLB4 Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "PCLKCR18", description: "Peripheral Clock Gating Register - FSI", offset: "0x46",
		bits: [
			{ name: "FSITX_A", description: "FSITX_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "FSIRX_A", description: "FSIRX_A Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR19", description: "Peripheral Clock Gating Register - LIN", offset: "0x48",
		bits: [
			{ name: "LIN_A", description: "LIN_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "LIN_B", description: "LIN_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR20", description: "Peripheral Clock Gating Register - PMBUS", offset: "0x4A",
		bits: [
			{ name: "PMBUS_A", description: "PMBUS_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PCLKCR21", description: "Peripheral Clock Gating Register - DCC", offset: "0x4C",
		bits: [
			{ name: "DCC0", description: "DCC0 Clock Enable Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "DCC1", description: "DCC1 Clock Enable Bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR25", description: "Peripheral Clock Gating Register - HIC", offset: "0x54",
		bits: [
			{ name: "HICA", description: "HICA Clock Enable Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PCLKCR26", description: "Peripheral Clock Gating Register - AES", offset: "0x56",
		bits: [
			{ name: "AESA", description: "AESA Clock Enable Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PCLKCR27", description: "Peripheral Clock Gating Register - EPG", offset: "0x58",
		bits: [
			{ name: "EPG1", description: "EPG1 Clock Enable Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SIMRESET", description: "Simulated Reset Register", offset: "0x70",
		bits: [
			{ name: "CPU1RSN", description: "Generates a reset to CPU", size: "1", shift: "0", mask: "0x1" },
			{ name: "XRSN", description: "Generates a simulated XRSn", size: "1", shift: "1", mask: "0x2" },
			{ name: "KEY", description: "Key value to enable write", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "LPMCR", description: "LPM Control Register", offset: "0x76",
		bits: [
			{ name: "LPM", description: "Low Power Mode setting", size: "2", shift: "0", mask: "0x3" },
			{ name: "QUALSTDBY", description: "STANDBY Wakeup Pin Qualification Setting", size: "6", shift: "2", mask: "0xFC" },
			{ name: "WDINTE", description: "Enable for WDINT wakeup from STANDBY", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "GPIOLPMSEL0", description: "GPIO LPM Wakeup select registers", offset: "0x78",
		bits: [
			{ name: "GPIO0", description: "GPIO0 Enable for LPM Wakeup", size: "1", shift: "0", mask: "0x1" },
			{ name: "GPIO1", description: "GPIO1 Enable for LPM Wakeup", size: "1", shift: "1", mask: "0x2" },
			{ name: "GPIO2", description: "GPIO2 Enable for LPM Wakeup", size: "1", shift: "2", mask: "0x4" },
			{ name: "GPIO3", description: "GPIO3 Enable for LPM Wakeup", size: "1", shift: "3", mask: "0x8" },
			{ name: "GPIO4", description: "GPIO4 Enable for LPM Wakeup", size: "1", shift: "4", mask: "0x10" },
			{ name: "GPIO5", description: "GPIO5 Enable for LPM Wakeup", size: "1", shift: "5", mask: "0x20" },
			{ name: "GPIO6", description: "GPIO6 Enable for LPM Wakeup", size: "1", shift: "6", mask: "0x40" },
			{ name: "GPIO7", description: "GPIO7 Enable for LPM Wakeup", size: "1", shift: "7", mask: "0x80" },
			{ name: "GPIO8", description: "GPIO8 Enable for LPM Wakeup", size: "1", shift: "8", mask: "0x100" },
			{ name: "GPIO9", description: "GPIO9 Enable for LPM Wakeup", size: "1", shift: "9", mask: "0x200" },
			{ name: "GPIO10", description: "GPIO10 Enable for LPM Wakeup", size: "1", shift: "10", mask: "0x400" },
			{ name: "GPIO11", description: "GPIO11 Enable for LPM Wakeup", size: "1", shift: "11", mask: "0x800" },
			{ name: "GPIO12", description: "GPIO12 Enable for LPM Wakeup", size: "1", shift: "12", mask: "0x1000" },
			{ name: "GPIO13", description: "GPIO13 Enable for LPM Wakeup", size: "1", shift: "13", mask: "0x2000" },
			{ name: "GPIO14", description: "GPIO14 Enable for LPM Wakeup", size: "1", shift: "14", mask: "0x4000" },
			{ name: "GPIO15", description: "GPIO15 Enable for LPM Wakeup", size: "1", shift: "15", mask: "0x8000" },
			{ name: "GPIO16", description: "GPIO16 Enable for LPM Wakeup", size: "1", shift: "16", mask: "0x10000" },
			{ name: "GPIO17", description: "GPIO17 Enable for LPM Wakeup", size: "1", shift: "17", mask: "0x20000" },
			{ name: "GPIO18", description: "GPIO18 Enable for LPM Wakeup", size: "1", shift: "18", mask: "0x40000" },
			{ name: "GPIO19", description: "GPIO19 Enable for LPM Wakeup", size: "1", shift: "19", mask: "0x80000" },
			{ name: "GPIO20", description: "GPIO20 Enable for LPM Wakeup", size: "1", shift: "20", mask: "0x100000" },
			{ name: "GPIO21", description: "GPIO21 Enable for LPM Wakeup", size: "1", shift: "21", mask: "0x200000" },
			{ name: "GPIO22", description: "GPIO22 Enable for LPM Wakeup", size: "1", shift: "22", mask: "0x400000" },
			{ name: "GPIO23", description: "GPIO23 Enable for LPM Wakeup", size: "1", shift: "23", mask: "0x800000" },
			{ name: "GPIO24", description: "GPIO24 Enable for LPM Wakeup", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "GPIO25", description: "GPIO25 Enable for LPM Wakeup", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "GPIO26", description: "GPIO26 Enable for LPM Wakeup", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "GPIO27", description: "GPIO27 Enable for LPM Wakeup", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "GPIO28", description: "GPIO28 Enable for LPM Wakeup", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "GPIO29", description: "GPIO29 Enable for LPM Wakeup", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "GPIO30", description: "GPIO30 Enable for LPM Wakeup", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "GPIO31", description: "GPIO31 Enable for LPM Wakeup", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "GPIOLPMSEL1", description: "GPIO LPM Wakeup select registers", offset: "0x7A",
		bits: [
			{ name: "GPIO32", description: "GPIO32 Enable for LPM Wakeup", size: "1", shift: "0", mask: "0x1" },
			{ name: "GPIO33", description: "GPIO33 Enable for LPM Wakeup", size: "1", shift: "1", mask: "0x2" },
			{ name: "GPIO34", description: "GPIO34 Enable for LPM Wakeup", size: "1", shift: "2", mask: "0x4" },
			{ name: "GPIO35", description: "GPIO35 Enable for LPM Wakeup", size: "1", shift: "3", mask: "0x8" },
			{ name: "GPIO37", description: "GPIO37 Enable for LPM Wakeup", size: "1", shift: "5", mask: "0x20" },
			{ name: "GPIO39", description: "GPIO39 Enable for LPM Wakeup", size: "1", shift: "7", mask: "0x80" },
			{ name: "GPIO40", description: "GPIO40 Enable for LPM Wakeup", size: "1", shift: "8", mask: "0x100" },
			{ name: "GPIO41", description: "GPIO41 Enable for LPM Wakeup", size: "1", shift: "9", mask: "0x200" },
			{ name: "GPIO42", description: "GPIO42 Enable for LPM Wakeup", size: "1", shift: "10", mask: "0x400" },
			{ name: "GPIO43", description: "GPIO43 Enable for LPM Wakeup", size: "1", shift: "11", mask: "0x800" },
			{ name: "GPIO44", description: "GPIO44 Enable for LPM Wakeup", size: "1", shift: "12", mask: "0x1000" },
			{ name: "GPIO45", description: "GPIO45 Enable for LPM Wakeup", size: "1", shift: "13", mask: "0x2000" },
			{ name: "GPIO46", description: "GPIO46 Enable for LPM Wakeup", size: "1", shift: "14", mask: "0x4000" },
			{ name: "GPIO47", description: "GPIO47 Enable for LPM Wakeup", size: "1", shift: "15", mask: "0x8000" },
			{ name: "GPIO48", description: "GPIO48 Enable for LPM Wakeup", size: "1", shift: "16", mask: "0x10000" },
			{ name: "GPIO49", description: "GPIO49 Enable for LPM Wakeup", size: "1", shift: "17", mask: "0x20000" },
			{ name: "GPIO50", description: "GPIO50 Enable for LPM Wakeup", size: "1", shift: "18", mask: "0x40000" },
			{ name: "GPIO51", description: "GPIO51 Enable for LPM Wakeup", size: "1", shift: "19", mask: "0x80000" },
			{ name: "GPIO52", description: "GPIO52 Enable for LPM Wakeup", size: "1", shift: "20", mask: "0x100000" },
			{ name: "GPIO53", description: "GPIO53 Enable for LPM Wakeup", size: "1", shift: "21", mask: "0x200000" },
			{ name: "GPIO54", description: "GPIO54 Enable for LPM Wakeup", size: "1", shift: "22", mask: "0x400000" },
			{ name: "GPIO55", description: "GPIO55 Enable for LPM Wakeup", size: "1", shift: "23", mask: "0x800000" },
			{ name: "GPIO56", description: "GPIO56 Enable for LPM Wakeup", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "GPIO57", description: "GPIO57 Enable for LPM Wakeup", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "GPIO58", description: "GPIO58 Enable for LPM Wakeup", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "GPIO59", description: "GPIO59 Enable for LPM Wakeup", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "GPIO60", description: "GPIO60 Enable for LPM Wakeup", size: "1", shift: "28", mask: "0x10000000" },
		]
	},
	{ name: "TMR2CLKCTL", description: "Timer2 Clock Measurement functionality control", offset: "0x7C",
		bits: [
			{ name: "TMR2CLKSRCSEL", description: "CPU Timer 2 Clock Source Select Bit", size: "3", shift: "0", mask: "0x7" },
			{ name: "TMR2CLKPRESCALE", description: "CPU Timer 2 Clock Pre-Scale Value", size: "3", shift: "3", mask: "0x38" },
		]
	},
	{ name: "RESCCLR", description: "Reset Cause Clear Register", offset: "0x7E",
		bits: [
			{ name: "POR", description: "POR Reset Cause Indication Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "XRSN", description: "XRSn Reset Cause Indication Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "WDRSN", description: "WDRSn Reset Cause Indication Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "NMIWDRSN", description: "NMIWDRSn Reset Cause Indication Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "HWBISTN", description: "HWBISTn Reset Cause Indication Bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "SCCRESETN", description: "SCCRESETn Reset Cause Indication Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "SIMRESET_CPU1RSN", description: "SIMRESET_CPU1RSn Reset Cause Indication Bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "SIMRESET_XRSN", description: "SIMRESET_XRSn Reset Cause Indication Bit", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "RESC", description: "Reset Cause register", offset: "0x80",
		bits: [
			{ name: "POR", description: "POR Reset Cause Indication Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "XRSN", description: "XRSn Reset Cause Indication Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "WDRSN", description: "WDRSn Reset Cause Indication Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "NMIWDRSN", description: "NMIWDRSn Reset Cause Indication Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "HWBISTN", description: "HWBISTn Reset Cause Indication Bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "SCCRESETN", description: "SCCRESETn Reset Cause Indication Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "SIMRESET_CPU1RSN", description: "SIMRESET_CPU1RSn Reset Cause Indication Bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "SIMRESET_XRSN", description: "SIMRESET_XRSn Reset Cause Indication Bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "XRSN_PIN_STATUS", description: "XRSN Pin Status", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "DCON", description: "Debugger conntion status to C28x", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "MCANWAKESTATUS", description: "MCAN Wake Status Register", offset: "0x98",
		bits: [
			{ name: "WAKE", description: "MCAN Wake Status", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "MCANWAKESTATUSCLR", description: "MCAN Wake Status Clear Register", offset: "0x9A",
		bits: [
			{ name: "WAKE", description: "Cear bit for MCANWAKESTATUS.WAKE bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CLKSTOPREQ", description: "Peripheral Clock Stop Request Register", offset: "0x9C",
		bits: [
			{ name: "MCAN_A", description: "MCAN_A Clock Stop Request Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "KEY", description: "Key for register write", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CLKSTOPACK", description: "Peripheral Clock Stop Ackonwledge Register", offset: "0x9E",
		bits: [
			{ name: "MCAN_A", description: "MCAN_A Clock Stop Ack Bit", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "CLA1TASKSRCSELLOCK", description: "CLA1 Task Trigger Source Select Lock Register", offset: "0x0",
		bits: [
			{ name: "CLA1TASKSRCSEL1", description: "CLA1TASKSRCSEL1 Register Lock bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLA1TASKSRCSEL2", description: "CLA1TASKSRCSEL2 Register Lock bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "DMACHSRCSELLOCK", description: "DMA Channel Triger Source Select Lock Register", offset: "0x4",
		bits: [
			{ name: "DMACHSRCSEL1", description: "DMACHSRCSEL1 Register Lock bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMACHSRCSEL2", description: "DMACHSRCSEL2 Register Lock bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CLA1TASKSRCSEL1", description: "CLA1 Task Trigger Source Select Register-1", offset: "0x6",
		bits: [
			{ name: "TASK1", description: "Selects the Trigger Source for TASK1 of", size: "8", shift: "0", mask: "0xFF" },
			{ name: "TASK2", description: "Selects the Trigger Source for TASK2 of", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "TASK3", description: "Selects the Trigger Source for TASK3 of", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "TASK4", description: "Selects the Trigger Source for TASK4 of", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "CLA1TASKSRCSEL2", description: "CLA1 Task Trigger Source Select Register-2", offset: "0x8",
		bits: [
			{ name: "TASK5", description: "Selects the Trigger Source for TASK5 of", size: "8", shift: "0", mask: "0xFF" },
			{ name: "TASK6", description: "Selects the Trigger Source for TASK6 of", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "TASK7", description: "Selects the Trigger Source for TASK7 of", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "TASK8", description: "Selects the Trigger Source for TASK8 of", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "DMACHSRCSEL1", description: "DMA Channel Trigger Source Select Register-1", offset: "0x16",
		bits: [
			{ name: "CH1", description: "Selects the Trigger and Sync Source CH1 of DMA", size: "8", shift: "0", mask: "0xFF" },
			{ name: "CH2", description: "Selects the Trigger and Sync Source CH2 of DMA", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "CH3", description: "Selects the Trigger and Sync Source CH3 of DMA", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "CH4", description: "Selects the Trigger and Sync Source CH4 of DMA", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "DMACHSRCSEL2", description: "DMA Channel Trigger Source Select Register-2", offset: "0x18",
		bits: [
			{ name: "CH5", description: "Selects the Trigger and Sync Source CH5 of DMA", size: "8", shift: "0", mask: "0xFF" },
			{ name: "CH6", description: "Selects the Trigger and Sync Source CH6 of DMA", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "ADCA_AC", description: "ADCA Master Access Control Register", offset: "0x0",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "ADCB_AC", description: "ADCB Master Access Control Register", offset: "0x2",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "ADCC_AC", description: "ADCC Master Access Control Register", offset: "0x4",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "CMPSS1_AC", description: "CMPSS1 Master Access Control Register", offset: "0x10",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "CMPSS2_AC", description: "CMPSS2 Master Access Control Register", offset: "0x12",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "CMPSS3_AC", description: "CMPSS3 Master Access Control Register", offset: "0x14",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "CMPSS4_AC", description: "CMPSS4 Master Access Control Register", offset: "0x16",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "DACA_AC", description: "DACA Master Access Control Register", offset: "0x28",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "DACB_AC", description: "DACB Master Access Control Register", offset: "0x2A",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "EPWM1_AC", description: "EPWM1 Master Access Control Register", offset: "0x48",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "EPWM2_AC", description: "EPWM2 Master Access Control Register", offset: "0x4A",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "EPWM3_AC", description: "EPWM3 Master Access Control Register", offset: "0x4C",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "EPWM4_AC", description: "EPWM4 Master Access Control Register", offset: "0x4E",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "EPWM5_AC", description: "EPWM5 Master Access Control Register", offset: "0x50",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "EPWM6_AC", description: "EPWM6 Master Access Control Register", offset: "0x52",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "EPWM7_AC", description: "EPWM7 Master Access Control Register", offset: "0x54",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "EPWM8_AC", description: "EPWM8 Master Access Control Register", offset: "0x56",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "EQEP1_AC", description: "EQEP1 Master Access Control Register", offset: "0x70",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "EQEP2_AC", description: "EQEP2 Master Access Control Register", offset: "0x72",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "ECAP1_AC", description: "ECAP1 Master Access Control Register", offset: "0x80",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "ECAP2_AC", description: "ECAP2 Master Access Control Register", offset: "0x82",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "ECAP3_AC", description: "ECAP3 Master Access Control Register", offset: "0x84",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "SDFM1_AC", description: "SDFM1 Master Access Control Register", offset: "0xA8",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "SDFM2_AC", description: "SDFM2 Master Access Control Register", offset: "0xAA",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "CLB1_AC", description: "CLB1 Master Access Control Register", offset: "0xB0",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "CLB2_AC", description: "CLB2 Master Access Control Register", offset: "0xB2",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "CLB3_AC", description: "CLB3 Master Access Control Register", offset: "0xB4",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "CLB4_AC", description: "CLB4 Master Access Control Register", offset: "0xB6",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "SCIA_AC", description: "SCIA Master Access Control Register", offset: "0x100",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "SCIB_AC", description: "SCIB Master Access Control Register", offset: "0x102",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "SPIA_AC", description: "SPIA Master Access Control Register", offset: "0x110",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "SPIB_AC", description: "SPIB Master Access Control Register", offset: "0x112",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "I2CA_AC", description: "I2CA Master Access Control Register", offset: "0x120",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "I2CB_AC", description: "I2CB Master Access Control Register", offset: "0x122",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "PMBUS_A_AC", description: "PMBUSA Master Access Control Register", offset: "0x130",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "LIN_A_AC", description: "LINA Master Access Control Register", offset: "0x138",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "LIN_B_AC", description: "LINB Master Access Control Register", offset: "0x13A",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "DCANA_AC", description: "DCANA Master Access Control Register", offset: "0x140",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "MCANA_AC", description: "MCANA Master Access Control Register", offset: "0x148",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "FSIATX_AC", description: "FSIA Master Access Control Register", offset: "0x158",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "FSIARX_AC", description: "FSIB Master Access Control Register", offset: "0x15A",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "HRPWM_A_AC", description: "HRPWM Master Access Control Register", offset: "0x1AA",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
			{ name: "HICA_ACC", description: "HICA Access Contions to Peripheral", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "HIC_A_AC", description: "HIC Master Access Control Register", offset: "0x1AC",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "AESA_AC", description: "AES Master Access Control Register", offset: "0x1AE",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "PERIPH_AC_LOCK", description: "Lock Register to stop Write access to peripheral", offset: "0x1FE",
		bits: [
			{ name: "LOCK_AC_WR", description: "Lock control for Access control registers", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SYNCSELECT", description: "Sync Input and Output Select Register", offset: "0x0",
		bits: [
			{ name: "SYNCOUT", description: "Select Syncout Source", size: "5", shift: "24", mask: "0x1F000000" },
		]
	},
	{ name: "ADCSOCOUTSELECT", description: "External ADCSOC Select Register", offset: "0x2",
		bits: [
			{ name: "PWM1SOCAEN", description: "PWM1SOCAEN Enable for ADCSOCAOn", size: "1", shift: "0", mask: "0x1" },
			{ name: "PWM2SOCAEN", description: "PWM2SOCAEN Enable for ADCSOCAOn", size: "1", shift: "1", mask: "0x2" },
			{ name: "PWM3SOCAEN", description: "PWM3SOCAEN Enable for ADCSOCAOn", size: "1", shift: "2", mask: "0x4" },
			{ name: "PWM4SOCAEN", description: "PWM4SOCAEN Enable for ADCSOCAOn", size: "1", shift: "3", mask: "0x8" },
			{ name: "PWM5SOCAEN", description: "PWM5SOCAEN Enable for ADCSOCAOn", size: "1", shift: "4", mask: "0x10" },
			{ name: "PWM6SOCAEN", description: "PWM6SOCAEN Enable for ADCSOCAOn", size: "1", shift: "5", mask: "0x20" },
			{ name: "PWM7SOCAEN", description: "PWM7SOCAEN Enable for ADCSOCAOn", size: "1", shift: "6", mask: "0x40" },
			{ name: "PWM8SOCAEN", description: "PWM8SOCAEN Enable for ADCSOCAOn", size: "1", shift: "7", mask: "0x80" },
			{ name: "PWM1SOCBEN", description: "PWM1SOCBEN Enable for ADCSOCBOn", size: "1", shift: "16", mask: "0x10000" },
			{ name: "PWM2SOCBEN", description: "PWM2SOCBEN Enable for ADCSOCBOn", size: "1", shift: "17", mask: "0x20000" },
			{ name: "PWM3SOCBEN", description: "PWM3SOCBEN Enable for ADCSOCBOn", size: "1", shift: "18", mask: "0x40000" },
			{ name: "PWM4SOCBEN", description: "PWM4SOCBEN Enable for ADCSOCBOn", size: "1", shift: "19", mask: "0x80000" },
			{ name: "PWM5SOCBEN", description: "PWM5SOCBEN Enable for ADCSOCBOn", size: "1", shift: "20", mask: "0x100000" },
			{ name: "PWM6SOCBEN", description: "PWM6SOCBEN Enable for ADCSOCBOn", size: "1", shift: "21", mask: "0x200000" },
			{ name: "PWM7SOCBEN", description: "PWM7SOCBEN Enable for ADCSOCBOn", size: "1", shift: "22", mask: "0x400000" },
			{ name: "PWM8SOCBEN", description: "PWM8SOCBEN Enable for ADCSOCBOn", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "SYNCSOCLOCK", description: "SYNCSEL and EXTADCSOC Select Lock register", offset: "0x4",
		bits: [
			{ name: "SYNCSELECT", description: "SYNCSEL Register Lock bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCSOCOUTSELECT", description: "ADCSOCOUTSELECT Register Lock bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "LFUCONFIG", description: "LFU configuration Register", offset: "0x0",
		bits: [
			{ name: "LFU_CPU", description: "SW configuration to implement LFU", size: "1", shift: "0", mask: "0x1" },
			{ name: "LFU_CLA1", description: "SW configuration to implement LFU", size: "1", shift: "4", mask: "0x10" },
			{ name: "PIEVECTORSWAP", description: "Swap of pie vector table", size: "1", shift: "12", mask: "0x1000" },
			{ name: "LS01SWAP", description: "Swap LS0 and LS1 memory", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "LFUSTATUS", description: "LFU Configuration Status Register", offset: "0x2",
		bits: [
			{ name: "PIEVECTORSWAP", description: "Indicate the status of PieVectorSwap", size: "1", shift: "12", mask: "0x1000" },
			{ name: "LS01SWAP", description: "Indicate the status of LS0/LS1 memory swap", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "SWCONFIG1_SYSRSN", description: "Spare registers reset by SYSRSn", offset: "0x10",
		bits: [
		]
	},
	{ name: "SWCONFIG2_SYSRSN", description: "Spare registers reset by SYSRSn", offset: "0x12",
		bits: [
		]
	},
	{ name: "SWCONFIG1_XRSN", description: "Spare registers reset by XRSn", offset: "0x14",
		bits: [
		]
	},
	{ name: "SWCONFIG2_XRSN", description: "Spare registers reset by XRSn", offset: "0x16",
		bits: [
		]
	},
	{ name: "SWCONFIG1_PORESETN", description: "Spare registers reset by PORESETn", offset: "0x18",
		bits: [
		]
	},
	{ name: "SWCONFIG2_PORESETN", description: "Spare registers reset by PORESETn", offset: "0x1A",
		bits: [
		]
	},
	{ name: "LFU_LOCK", description: "LFU Lock Configuration", offset: "0x1C",
		bits: [
			{ name: "LFUCONFIG", description: "Register lock configuration", size: "1", shift: "0", mask: "0x1" },
			{ name: "SWCONFIG1_SYSRSN", description: "Register lock configuration", size: "1", shift: "8", mask: "0x100" },
			{ name: "SWCONFIG2_SYSRSN", description: "Register lock configuration", size: "1", shift: "9", mask: "0x200" },
			{ name: "SWCONFIG1_XRSN", description: "Register lock configuration", size: "1", shift: "10", mask: "0x400" },
			{ name: "SWCONFIG2_XRSN", description: "Register lock configuration", size: "1", shift: "11", mask: "0x800" },
			{ name: "SWCONFIG1_PORESETN", description: "Register lock configuration", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SWCONFIG2_PORESETN", description: "Register lock configuration", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "LFU_COMMIT", description: "LFU Commit Configuration", offset: "0x1E",
		bits: [
			{ name: "LFUCONFIG", description: "Register commit configuration", size: "1", shift: "0", mask: "0x1" },
			{ name: "SWCONFIG1_SYSRSN", description: "Register commit configuration", size: "1", shift: "8", mask: "0x100" },
			{ name: "SWCONFIG2_SYSRSN", description: "Register commit configuration", size: "1", shift: "9", mask: "0x200" },
			{ name: "SWCONFIG1_XRSN", description: "Register commit configuration", size: "1", shift: "10", mask: "0x400" },
			{ name: "SWCONFIG2_XRSN", description: "Register commit configuration", size: "1", shift: "11", mask: "0x800" },
			{ name: "SWCONFIG1_PORESETN", description: "Register commit configuration", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SWCONFIG2_PORESETN", description: "Register commit configuration", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "SYS_ERR_INT_FLG", description: "Status of interrupts due to multiple different errors", offset: "0x10",
		bits: [
			{ name: "GINT", description: "Global Interrupt flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "AES_BUS_ERROR", description: "AES_BUS_ERROR Interrupt flag.", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPG1_INT", description: "EPG1_INT Interrupt flag.", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "SYS_ERR_INT_CLR", description: "SYS_ERR_INT_FLG clear register", offset: "0x12",
		bits: [
			{ name: "GINT", description: "Global Interrupt flag Clear bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "AES_BUS_ERROR", description: "AES_BUS_ERROR interrupt flag clear bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPG1_INT", description: "EPG1_INT interrupt flag clear bit", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "SYS_ERR_INT_SET", description: "SYS_ERR_INT_FLG set register", offset: "0x14",
		bits: [
			{ name: "AES_BUS_ERROR", description: "AES_BUS_ERROR interrupt flag set", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPG1_INT", description: "EPG1_INT interrupt flag set bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "KEY", description: "KEY field", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "SYS_ERR_MASK", description: "SYS_ERR_MASK register", offset: "0x16",
		bits: [
			{ name: "AES_BUS_ERROR", description: "AES_BUS_ERROR flag mask bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPG1_INT", description: "EPG1_INT flag mask bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "KEY", description: "KEY field", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
];
module.exports = {
	SYSCTLRegisters: SYSCTLRegisters,
}
