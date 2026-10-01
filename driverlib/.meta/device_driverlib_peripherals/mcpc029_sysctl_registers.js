let SYSCTLRegisters = [
	{ name: "PARTIDL", description: "Lower 32-bit of Device PART Identification", offset: "0x2",
		bits: [
			{ name: "QUAL", description: "Qualification Status", size: "2", shift: "6", mask: "0xC0" },
			{ name: "FLASH_SIZE", description: "FLASH_SIZE", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "PARTID_FORMAT_REV", description: "PARTID_FORMAT_REV", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "PARTIDH", description: "Upper 32-bit of Device PART Identification", offset: "0x4",
		bits: [
			{ name: "FAMILY", description: "Device family", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "PARTNO", description: "Device part number", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "DEVICE_CLASS_ID", description: "Device class ID", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "REVID", description: "Device Revision Number", offset: "0x6",
		bits: [
			{ name: "REVID", description: "Device Revision ID. This is specific to the Device", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "DC_MEMORY", description: "Device Capability: Memory Blocks Customization", offset: "0xE",
		bits: [
			{ name: "BANK0_32KB_1", description: "BANK0_32KB_1 present", size: "1", shift: "0", mask: "0x1" },
			{ name: "BANK0_32KB_2", description: "BANK0_32KB_2 present", size: "1", shift: "1", mask: "0x2" },
			{ name: "BANK0_32KB_3", description: "BANK0_32KB_3 present", size: "1", shift: "2", mask: "0x4" },
			{ name: "BANK0_32KB_4", description: "BANK0_32KB_4 present", size: "1", shift: "3", mask: "0x8" },
			{ name: "BANK0_32KB_5", description: "BANK0_32KB_5 present", size: "1", shift: "4", mask: "0x10" },
			{ name: "BANK0_32KB_6", description: "BANK0_32KB_6 present", size: "1", shift: "5", mask: "0x20" },
			{ name: "BANK0_32KB_7", description: "BANK0_32KB_7 present", size: "1", shift: "6", mask: "0x40" },
			{ name: "BANK0_32KB_8", description: "BANK0_32KB_8 present", size: "1", shift: "7", mask: "0x80" },
			{ name: "BANK1_32KB_1", description: "BANK1_32KB_1 present", size: "1", shift: "8", mask: "0x100" },
			{ name: "BANK1_32KB_2", description: "BANK1_32KB_2 present", size: "1", shift: "9", mask: "0x200" },
			{ name: "BANK1_32KB_3", description: "BANK1_32KB_3 present", size: "1", shift: "10", mask: "0x400" },
			{ name: "BANK1_32KB_4", description: "BANK1_32KB_4 present", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "PERCNF", description: "Peripheral Configuration register - GPIO", offset: "0x10",
		bits: [
			{ name: "GPIO_228_226", description: "GPIO226, GPIO228 Double bond protection", size: "1", shift: "0", mask: "0x1" },
			{ name: "GPIO_230_227", description: "GPIO227, GPIO230 Double bond protection", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "TRIMERRSTS", description: "TRIM Error Status register", offset: "0x12",
		bits: [
			{ name: "LERR", description: "TRIM Load error status", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "SOFTPRES_PROC_INFRA", description: "Processing and Infra Blocks Software Reset", offset: "0x1E",
		bits: [
			{ name: "DCC1", description: "DCC1 soft reset", size: "1", shift: "8", mask: "0x100" },
			{ name: "FLASHA", description: "FLASHA soft reset", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "SOFTPRES_CTRL_PERIPH", description: "Control Peripherals Software Reset register", offset: "0x20",
		bits: [
			{ name: "PWM1", description: "PWM1 soft reset", size: "1", shift: "0", mask: "0x1" },
			{ name: "PWM3", description: "PWM3 soft reset", size: "1", shift: "2", mask: "0x4" },
			{ name: "ECAP1", description: "ECAP1 soft reset", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EQEP1", description: "EQEP1 soft reset", size: "1", shift: "14", mask: "0x4000" },
			{ name: "ADC_A", description: "ADC_A soft reset", size: "1", shift: "15", mask: "0x8000" },
			{ name: "CMPSS1", description: "CMPSS1 soft reset", size: "1", shift: "17", mask: "0x20000" },
			{ name: "CMPSS2", description: "CMPSS2 soft reset", size: "1", shift: "18", mask: "0x40000" },
			{ name: "CMPSS3", description: "CMPSS3 soft reset", size: "1", shift: "19", mask: "0x80000" },
			{ name: "PGA1", description: "PGA1 soft reset", size: "1", shift: "24", mask: "0x1000000" },
		]
	},
	{ name: "SOFTPRES_COMM_PERIPH", description: "Communication Peripherals Software Reset", offset: "0x22",
		bits: [
			{ name: "I2C_A", description: "I2C_A soft reset", size: "1", shift: "0", mask: "0x1" },
			{ name: "SCI_A", description: "SCI_A soft reset", size: "1", shift: "2", mask: "0x4" },
			{ name: "SCI_B", description: "SCI_B soft reset", size: "1", shift: "3", mask: "0x8" },
			{ name: "UART_A", description: "UART_A soft reset", size: "1", shift: "4", mask: "0x10" },
			{ name: "SPI_A", description: "SPI_A soft reset", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "SOFTPRES_JTAG", description: "JTAG Software Reset register", offset: "0x24",
		bits: [
			{ name: "JTAG_NTRST", description: "Multi Bit JTAG nTRST", size: "4", shift: "0", mask: "0xF" },
			{ name: "JTAG_NTRST_KEY", description: "JTAG nTRST Key", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "TAP_STATUS", description: "Status of JTAG State machine & Debugger Connect", offset: "0x28",
		bits: [
			{ name: "TAP_STATE", description: "Present TAP State", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "DCON", description: "Debugger Connect Indication", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "ECAPTYPE", description: "Configures ECAP Type for the device", offset: "0x2A",
		bits: [
			{ name: "TYPE", description: "Configure ECAP type", size: "2", shift: "0", mask: "0x3" },
			{ name: "LOCK", description: "Lock bit for the register", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "TAP_CONTROL", description: "Disable TAP control", offset: "0x2C",
		bits: [
			{ name: "BSCAN_DIS", description: "Disable BSCAN TAP control", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Key value to enable write", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CLKCFGLOCK", description: "Lock bit for CLKCFG registers", offset: "0x0",
		bits: [
			{ name: "ALL", description: "Lock bit for CLKCFG registers", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CLKSRCCTL1", description: "Clock Source Control register-1", offset: "0x2",
		bits: [
			{ name: "OSCCLKSRCSEL", description: "OSCCLK Source Select Bits", size: "2", shift: "0", mask: "0x3" },
			{ name: "SECCLKSRCSEL", description: "SECCLK Source Select Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "WDHALTI", description: "Watchdog HALT Mode Ignore Bit", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "CLKSRCCTL2", description: "Clock Source Control register-2", offset: "0x4",
		bits: [
			{ name: "CANABCLKSEL", description: "CANA Bit Clock Source Select Bit", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "CLKSRCCTL3", description: "Clock Source Control register-3", offset: "0x6",
		bits: [
			{ name: "XCLKOUTSEL", description: "XCLKOUT Source Select Bit", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "SYSPLLCTL", description: "SYSPLL Control register", offset: "0x8",
		bits: [
			{ name: "PLLEN", description: "SYSPLL enable/disable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "PLLCLKEN", description: "SYSPLL bypassed or included in the PLLSYSCLK path", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SYSPLLMULT", description: "SYSPLL Multiplier register", offset: "0xA",
		bits: [
			{ name: "QDIV", description: "SYSPLL Feedback Divider (decides the", size: "7", shift: "0", mask: "0x7F" },
			{ name: "RDIVCLK0", description: "Output Clock Divider", size: "4", shift: "8", mask: "0xF00" },
			{ name: "PDIV", description: "Reference Clock Divider", size: "2", shift: "16", mask: "0x30000" },
		]
	},
	{ name: "SYSPLLSTS", description: "SYSPLL Status register", offset: "0xC",
		bits: [
			{ name: "LOCKS", description: "SYSPLL Lock Status Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SYSCLKDIVSEL", description: "System Clock Divider Select register", offset: "0xE",
		bits: [
			{ name: "PLLSYSCLKDIV", description: "PLLSYSCLK Divide Select", size: "6", shift: "0", mask: "0x3F" },
		]
	},
	{ name: "XCLKOUTDIVSEL", description: "XCLKOUT Divider Select register", offset: "0x12",
		bits: [
			{ name: "XCLKOUTDIV", description: "XCLKOUT Divide Select", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "LOSPCP", description: "Low Speed Clock Source Prescalar", offset: "0x14",
		bits: [
			{ name: "LSPCLKDIV", description: "LSPCLK Divide Select", size: "3", shift: "0", mask: "0x7" },
		]
	},
	{ name: "MCDCR", description: "Missing Clock Detect Control Register", offset: "0x16",
		bits: [
			{ name: "MCLKSTS", description: "Missing Clock Status Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "MCLKCLR", description: "Missing Clock Clear Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "MCLKOFF", description: "Missing Clock Detect Off Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "OSCOFF", description: "Oscillator Clock Off Bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "X1CNT", description: "10-bit Counter on X1 Clock", offset: "0x18",
		bits: [
			{ name: "X1CNT", description: "X1 Counter", size: "11", shift: "0", mask: "0x7FF" },
			{ name: "CLR", description: "X1 Counter Clear", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "XTALCR", description: "XTAL Control Register", offset: "0x1A",
		bits: [
			{ name: "OSCOFF", description: "XTAL Oscillator powered-down", size: "1", shift: "0", mask: "0x1" },
			{ name: "SE", description: "XTAL Oscilator in Single-Ended mode", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "XTALCR2", description: "XTAL Control Register for pad init", offset: "0x1C",
		bits: [
			{ name: "XIF", description: "XI Initial value deposited before XOSC start", size: "1", shift: "0", mask: "0x1" },
			{ name: "XOF", description: "XO Initial value deposited before XOSC start", size: "1", shift: "1", mask: "0x2" },
			{ name: "FEN", description: "XOSC pads initialisation enable", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "CLKFAILCFG", description: "Clock Fail cause Configuration", offset: "0x1E",
		bits: [
			{ name: "DCC0_ERROR_EN", description: "DCC0 Error causes Clock fail NMI, ERROR", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CLKSRCSTS", description: "Clock Source Status", offset: "0x20",
		bits: [
			{ name: "SYSOSC_ENABLED", description: "SYSOSC enabled status", size: "1", shift: "0", mask: "0x1" },
			{ name: "SYSOSC_FCL_DONE", description: "SYSOSC FCL done status", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CPUSYSLOCK", description: "Lock bit for CPUSYS registers", offset: "0x0",
		bits: [
			{ name: "ALL", description: "Lock bit for CPUSYS registers", size: "1", shift: "0", mask: "0x1" },
			{ name: "BROMPATCH", description: "Lock bit for BROMPATCH registers", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PIEVERRADDR", description: "PIE Vector Fetch Error Address register", offset: "0x2",
		bits: [
			{ name: "ADDR", description: "PIE Vector Fetch Error Handler Routine Address", size: "22", shift: "0", mask: "0x3FFFFF" },
		]
	},
	{ name: "SIMRESET", description: "Simulated Reset Register", offset: "0x4",
		bits: [
			{ name: "CPU1RSN", description: "Generates a reset to CPU", size: "1", shift: "0", mask: "0x1" },
			{ name: "XRSN", description: "Generates a simulated XRSn", size: "1", shift: "1", mask: "0x2" },
			{ name: "KEY", description: "Key value to enable write", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "LPMCR", description: "LPM Control Register", offset: "0x8",
		bits: [
			{ name: "LPM", description: "Low Power Mode setting", size: "2", shift: "0", mask: "0x3" },
			{ name: "QUALSTDBY", description: "STANDBY Wakeup Pin Qualification Setting", size: "6", shift: "2", mask: "0xFC" },
			{ name: "WDINTE", description: "Enable for WDINT wakeup from STANDBY", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "GPIOLPMSEL0", description: "GPIO LPM Wakeup select registers", offset: "0xA",
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
	{ name: "GPIOLPMSEL1", description: "GPIO LPM Wakeup select registers", offset: "0xC",
		bits: [
			{ name: "GPIO32", description: "GPIO32 Enable for LPM Wakeup", size: "1", shift: "0", mask: "0x1" },
			{ name: "GPIO33", description: "GPIO33 Enable for LPM Wakeup", size: "1", shift: "1", mask: "0x2" },
			{ name: "GPIO34", description: "GPIO34 Enable for LPM Wakeup", size: "1", shift: "2", mask: "0x4" },
			{ name: "GPIO35", description: "GPIO35 Enable for LPM Wakeup", size: "1", shift: "3", mask: "0x8" },
			{ name: "GPIO36", description: "GPIO36 Enable for LPM Wakeup", size: "1", shift: "4", mask: "0x10" },
			{ name: "GPIO37", description: "GPIO37 Enable for LPM Wakeup", size: "1", shift: "5", mask: "0x20" },
			{ name: "GPIO38", description: "GPIO38 Enable for LPM Wakeup", size: "1", shift: "6", mask: "0x40" },
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
			{ name: "GPIO61", description: "GPIO61 Enable for LPM Wakeup", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "GPIO62", description: "GPIO62 Enable for LPM Wakeup", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "GPIO63", description: "GPIO63 Enable for LPM Wakeup", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "TMR2CLKCTL", description: "Timer2 Clock Measurement functionality control", offset: "0xE",
		bits: [
			{ name: "TMR2CLKSRCSEL", description: "CPU Timer 2 Clock Source Select Bit", size: "3", shift: "0", mask: "0x7" },
			{ name: "TMR2CLKPRESCALE", description: "CPU Timer 2 Clock Pre-Scale Value", size: "3", shift: "3", mask: "0x38" },
		]
	},
	{ name: "RESCCLR", description: "Reset Cause Clear Register", offset: "0x10",
		bits: [
			{ name: "POR", description: "POR Reset Cause Indication Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "XRSN", description: "XRSn Reset Cause Indication Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "WDRSN", description: "WDRSn Reset Cause Indication Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "NMIWDRSN", description: "NMIWDRSn Reset Cause Indication Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "SCCRESETN", description: "SCCRESETn Reset Cause Indication Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "SIMRESET_CPU1RSN", description: "SIMRESET_CPU1RSn Reset Cause Indication Bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "SIMRESET_XRSN", description: "SIMRESET_XRSn Reset Cause Indication Bit", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "RESC", description: "Reset Cause register", offset: "0x12",
		bits: [
			{ name: "POR", description: "POR Reset Cause Indication Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "XRSN", description: "XRSn Reset Cause Indication Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "WDRSN", description: "WDRSn Reset Cause Indication Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "NMIWDRSN", description: "NMIWDRSn Reset Cause Indication Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "SCCRESETN", description: "SCCRESETn Reset Cause Indication Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "SIMRESET_CPU1RSN", description: "SIMRESET_CPU1RSn Reset Cause Indication Bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "SIMRESET_XRSN", description: "SIMRESET_XRSn Reset Cause Indication Bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "XRSN_PIN_STATUS", description: "XRSN Pin Status", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "DCON", description: "Debugger conntion status to C28x", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "CMPSSLPMSEL", description: "CMPSS LPM Wakeup select registers", offset: "0x14",
		bits: [
			{ name: "CMPSS1H", description: "CMPSS1H Enable for LPM Wakeup", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPSS1L", description: "CMPSS1L Enable for LPM Wakeup", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMPSS2H", description: "CMPSS2H Enable for LPM Wakeup", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMPSS2L", description: "CMPSS2L Enable for LPM Wakeup", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMPSS3H", description: "CMPSS3H Enable for LPM Wakeup", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMPSS3L", description: "CMPSS3L Enable for LPM Wakeup", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMPSS4H", description: "CMPSS4H Enable for LPM Wakeup", size: "1", shift: "6", mask: "0x40" },
			{ name: "CMPSS4L", description: "CMPSS4L Enable for LPM Wakeup", size: "1", shift: "7", mask: "0x80" },
			{ name: "CMPSS5H", description: "CMPSS5H Enable for LPM Wakeup", size: "1", shift: "8", mask: "0x100" },
			{ name: "CMPSS5L", description: "CMPSS5L Enable for LPM Wakeup", size: "1", shift: "9", mask: "0x200" },
			{ name: "CMPSS6H", description: "CMPSS6H Enable for LPM Wakeup", size: "1", shift: "10", mask: "0x400" },
			{ name: "CMPSS6L", description: "CMPSS6L Enable for LPM Wakeup", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "CLKSTOPREQ", description: "Peripheral Clock Stop Request Register", offset: "0x16",
		bits: [
			{ name: "CAN_A", description: "CAN_A Clock Stop Request Bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "KEY", description: "Key for register write", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CLKSTOPACK", description: "Peripheral Clock Stop Ackonwledge Register", offset: "0x18",
		bits: [
			{ name: "CAN_A", description: "CAN_A Clock Stop Ack Bit", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "USER_REG1_SYSRSN", description: "Software Configurable registers reset by SYSRSn", offset: "0x1A",
		bits: [
		]
	},
	{ name: "USER_REG2_SYSRSN", description: "Software Configurable registers reset by SYSRSn", offset: "0x1C",
		bits: [
		]
	},
	{ name: "USER_REG1_XRSN", description: "Software Configurable registers reset by XRSn", offset: "0x1E",
		bits: [
		]
	},
	{ name: "USER_REG2_XRSN", description: "Software Configurable registers reset by XRSn", offset: "0x20",
		bits: [
		]
	},
	{ name: "USER_REG1_PORESETN", description: "Software Configurable registers reset by PORESETn", offset: "0x22",
		bits: [
		]
	},
	{ name: "USER_REG2_PORESETN", description: "Software Configurable registers reset by PORESETn", offset: "0x24",
		bits: [
		]
	},
	{ name: "USER_REG3_PORESETN", description: "Software Configurable registers reset by PORESETn", offset: "0x26",
		bits: [
		]
	},
	{ name: "USER_REG4_PORESETN", description: "Software Configurable registers reset by PORESETn", offset: "0x28",
		bits: [
		]
	},
	{ name: "PERCLKCR", description: "Peripheral Clock Control", offset: "0x3C",
		bits: [
			{ name: "TBCLKSYNC", description: "PWM Time Base Clock sync", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SCSR", description: "System Control & Status Register", offset: "0x22",
		bits: [
			{ name: "WDOVERRIDE", description: "WD Override for WDDIS bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "WDENINT", description: "WD Interrupt Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "WDINTS", description: "WD Interrupt Status", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "WDCNTR", description: "Watchdog Counter Register", offset: "0x23",
		bits: [
			{ name: "WDCNTR", description: "WD Counter", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "WDKEY", description: "Watchdog Reset Key Register", offset: "0x25",
		bits: [
			{ name: "WDKEY", description: "Key to pet the watchdog timer.", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "WDCR", description: "Watchdog Control Register", offset: "0x29",
		bits: [
			{ name: "WDPS", description: "WD Clock Prescalar", size: "3", shift: "0", mask: "0x7" },
			{ name: "WDCHK", description: "WD Check Bits", size: "3", shift: "3", mask: "0x38" },
			{ name: "WDDIS", description: "WD Disable", size: "1", shift: "6", mask: "0x40" },
			{ name: "WDPRECLKDIV", description: "WD Pre Clock Divider", size: "4", shift: "8", mask: "0xF00" },
		]
	},
	{ name: "WDWCR", description: "Watchdog Windowed Control Register", offset: "0x2A",
		bits: [
			{ name: "MIN", description: "WD Min Threshold setting for Windowed Watchdog", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "DMACLASRCSELLOCK", description: "DMA/CLA Trigger Source Select Lock Register", offset: "0x0",
		bits: [
			{ name: "ALL", description: "DMACLASRCSEL Registers Lock bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "DMACHSRCSEL1", description: "DMA Channel Trigger Source Select Register-1", offset: "0x2",
		bits: [
			{ name: "CH1", description: "Selects the Trigger and Sync Source CH1 of DMA", size: "6", shift: "0", mask: "0x3F" },
			{ name: "CH2", description: "Selects the Trigger and Sync Source CH2 of DMA", size: "6", shift: "8", mask: "0x3F00" },
		]
	},
	{ name: "SYNCSELECT", description: "Sync Input and Output Select Register", offset: "0x0",
		bits: [
			{ name: "SYNCOUT", description: "Select EXT Syncout Source", size: "5", shift: "24", mask: "0x1F000000" },
		]
	},
	{ name: "ADCSOCOUTSELECT", description: "External ADCSOC Select Register", offset: "0x2",
		bits: [
			{ name: "PWM1SOCAEN", description: "PWM1SOCAEN Enable for ADCSOCAOn", size: "1", shift: "0", mask: "0x1" },
			{ name: "PWM3SOCAEN", description: "PWM3SOCAEN Enable for ADCSOCAOn", size: "1", shift: "2", mask: "0x4" },
			{ name: "PWM1SOCBEN", description: "PWM1SOCBEN Enable for ADCSOCBOn", size: "1", shift: "16", mask: "0x10000" },
			{ name: "PWM3SOCBEN", description: "PWM3SOCBEN Enable for ADCSOCBOn", size: "1", shift: "18", mask: "0x40000" },
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
			{ name: "PIEVECTORSWAP", description: "Swap of pie vector table", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "LFUSTATUS", description: "LFU Configuration Status Register", offset: "0x2",
		bits: [
			{ name: "PIEVECTORSWAP", description: "Indicate the status of PieVectorSwap", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "LFU_LOCK", description: "LFU Lock Configuration", offset: "0x4",
		bits: [
			{ name: "LFUCONFIG", description: "Register lock configuration", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "LFU_COMMIT", description: "LFU Commit Configuration", offset: "0x6",
		bits: [
			{ name: "LFUCONFIG", description: "Register commit configuration", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SYS_ERR_INT_FLG", description: "Status of interrupts due to multiple different errors", offset: "0x0",
		bits: [
			{ name: "GINT", description: "Global Interrupt flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CORRECTABLE_ERR", description: "RAM/Flash correctable error flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "FPU_UFLOW", description: "FPU_UFLOW Interrupt flag.", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FPU_OFLOW", description: "FPU_OFLOW Interrupt flag.", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "SYS_ERR_INT_CLR", description: "SYS_ERR_INT_FLG clear register", offset: "0x2",
		bits: [
			{ name: "GINT", description: "Global Interrupt flag Clear bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CORRECTABLE_ERR", description: "CORRECTABLE_ERR interrupt flag clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "FPU_UFLOW", description: "FPU_UFLOW interrupt flag clear bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FPU_OFLOW", description: "FPU_OFLOW interrupt flag clear bit", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "SYS_ERR_INT_SET", description: "SYS_ERR_INT_FLG set register", offset: "0x4",
		bits: [
			{ name: "CORRECTABLE_ERR", description: "CORRECTABLE_ERR interrupt flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "FPU_UFLOW", description: "FPU_UFLOW interrupt flag set bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FPU_OFLOW", description: "FPU_OFLOW interrupt flag set bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "KEY", description: "KEY field", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "SYS_ERR_MASK", description: "SYS_ERR_MASK register", offset: "0x6",
		bits: [
			{ name: "CORRECTABLE_ERR", description: "CORRECTABLE_ERR flag mask bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "FPU_UFLOW", description: "FPU_UFLOW flag mask bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FPU_OFLOW", description: "FPU_OFLOW flag mask bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "KEY", description: "KEY field", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
];
module.exports = {
	SYSCTLRegisters: SYSCTLRegisters,
}
