let SYSCTLRegisters = [
	{ name: "CLKSEM", description: "Clock Control Semaphore Register", offset: "0x0",
		bits: [
			{ name: "SEM", description: "Semaphore for CLKCFG Ownership by CPU1 or CPU2", size: "2", shift: "0", mask: "0x3" },
			{ name: "KEY", description: "Key Qualifier for writes to this register", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CLKCFGLOCK1", description: "Lock bit for CLKCFG registers", offset: "0x2",
		bits: [
			{ name: "CLKSRCCTL1", description: "Lock bit for CLKSRCCTL1 register", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLKSRCCTL2", description: "Lock bit for CLKSRCCTL2 register", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLKSRCCTL3", description: "Lock bit for CLKSRCCTL3 register", size: "1", shift: "2", mask: "0x4" },
			{ name: "SYSPLLCTL1", description: "Lock bit for SYSPLLCTL1 register", size: "1", shift: "3", mask: "0x8" },
			{ name: "SYSPLLCTL2", description: "Lock bit for SYSPLLCTL2 register", size: "1", shift: "4", mask: "0x10" },
			{ name: "SYSPLLCTL3", description: "Lock bit for SYSPLLCTL3 register", size: "1", shift: "5", mask: "0x20" },
			{ name: "SYSPLLMULT", description: "Lock bit for SYSPLLMULT register", size: "1", shift: "6", mask: "0x40" },
			{ name: "AUXPLLCTL1", description: "Lock bit for AUXPLLCTL1 register", size: "1", shift: "7", mask: "0x80" },
			{ name: "AUXPLLMULT", description: "Lock bit for AUXPLLMULT register", size: "1", shift: "10", mask: "0x400" },
			{ name: "SYSCLKDIVSEL", description: "Lock bit for SYSCLKDIVSEL register", size: "1", shift: "11", mask: "0x800" },
			{ name: "AUXCLKDIVSEL", description: "Lock bit for AUXCLKDIVSEL register", size: "1", shift: "12", mask: "0x1000" },
			{ name: "PERCLKDIVSEL", description: "Lock bit for PERCLKDIVSEL register", size: "1", shift: "13", mask: "0x2000" },
			{ name: "CLBCLKCTL", description: "Lock bit for CLBCLKCTL register", size: "1", shift: "14", mask: "0x4000" },
			{ name: "LOSPCP", description: "Lock bit for LOSPCP register", size: "1", shift: "15", mask: "0x8000" },
			{ name: "XTALCR", description: "Lock bit for XTALCR register", size: "1", shift: "16", mask: "0x10000" },
			{ name: "ETHERCATCLKCTL", description: "Lock bit for ETHERCATCLKCTL register", size: "1", shift: "17", mask: "0x20000" },
			{ name: "CMCLKCTL", description: "Lock bit for CMCLKCTL register", size: "1", shift: "18", mask: "0x40000" },
		]
	},
	{ name: "CLKSRCCTL1", description: "Clock Source Control register-1", offset: "0x8",
		bits: [
			{ name: "OSCCLKSRCSEL", description: "OSCCLK Source Select Bit", size: "2", shift: "0", mask: "0x3" },
			{ name: "INTOSC2OFF_NOTSUPPORTED", description: "Internal Oscillator 2 Off Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "XTALOFF", description: "Crystal (External) Oscillator Off", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "CLKSRCCTL2", description: "Clock Source Control register-2", offset: "0xA",
		bits: [
			{ name: "AUXOSCCLKSRCSEL", description: "AUXOSCCLK Source Select Bit", size: "2", shift: "0", mask: "0x3" },
			{ name: "CANABCLKSEL", description: "CANA Clock Source Select Bit", size: "2", shift: "2", mask: "0xC" },
			{ name: "CANBBCLKSEL", description: "CANB Clock Source Select Bit", size: "2", shift: "4", mask: "0x30" },
			{ name: "MCANABITCLKSEL", description: "MCAN (global) Bit-Clock Source Select Bit", size: "2", shift: "10", mask: "0xC00" },
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
			{ name: "SLIPS_NOTSUPPORTED", description: "SYSPLL Slip Status Bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "AUXPLLCTL1", description: "AUXPLL Control register-1", offset: "0x18",
		bits: [
			{ name: "PLLEN", description: "AUXPLL enable/disable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "PLLCLKEN", description: "AUXPLL bypassed or included in the AUXPLLCLK path", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "AUXPLLMULT", description: "AUXPLL Multiplier register", offset: "0x1E",
		bits: [
			{ name: "IMULT", description: "AUXPLL Integer Multiplier", size: "8", shift: "0", mask: "0xFF" },
			{ name: "ODIV", description: "Output Clock Divider", size: "5", shift: "16", mask: "0x1F0000" },
			{ name: "REFDIV", description: "Reference Clock Divider", size: "5", shift: "24", mask: "0x1F000000" },
		]
	},
	{ name: "AUXPLLSTS", description: "AUXPLL Status register", offset: "0x20",
		bits: [
			{ name: "LOCKS", description: "AUXPLL Lock Status Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SLIPS_NOTSUPPORTED", description: "AUXPLL Slip Status Bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SYSCLKDIVSEL", description: "System Clock Divider Select register", offset: "0x22",
		bits: [
			{ name: "PLLSYSCLKDIV", description: "PLLSYSCLK Divide Select", size: "6", shift: "0", mask: "0x3F" },
		]
	},
	{ name: "AUXCLKDIVSEL", description: "Auxillary Clock Divider Select register", offset: "0x24",
		bits: [
			{ name: "AUXPLLDIV", description: "AUXPLLCLK Divide Select", size: "3", shift: "0", mask: "0x7" },
			{ name: "MCANCLKDIV", description: "Divider between CANFD Source Clock and", size: "5", shift: "8", mask: "0x1F00" },
		]
	},
	{ name: "PERCLKDIVSEL", description: "Peripheral Clock Divider Selet register", offset: "0x26",
		bits: [
			{ name: "EPWMCLKDIV", description: "EPWM Clock Divide Select", size: "2", shift: "0", mask: "0x3" },
			{ name: "EMIF1CLKDIV", description: "EMIF1  Clock Divide Select", size: "1", shift: "4", mask: "0x10" },
			{ name: "EMIF2CLKDIV", description: "EMIF2 Clock Divide Select", size: "1", shift: "6", mask: "0x40" },
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
			{ name: "CLKMODECLB5", description: "Clock mode of CLB5", size: "1", shift: "20", mask: "0x100000" },
			{ name: "CLKMODECLB6", description: "Clock mode of CLB6", size: "1", shift: "21", mask: "0x200000" },
			{ name: "CLKMODECLB7", description: "Clock mode of CLB7", size: "1", shift: "22", mask: "0x400000" },
			{ name: "CLKMODECLB8", description: "Clock mode of CLB8", size: "1", shift: "23", mask: "0x800000" },
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
		]
	},
	{ name: "X1CNT", description: "10-bit Counter on X1 Clock", offset: "0x30",
		bits: [
			{ name: "X1CNT", description: "X1 Counter", size: "10", shift: "0", mask: "0x3FF" },
			{ name: "CLR", description: "X1 Counter Clear", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "XTALCR", description: "XTAL Control Register", offset: "0x32",
		bits: [
			{ name: "OSCOFF", description: "XTAL Oscillator powered-down", size: "1", shift: "0", mask: "0x1" },
			{ name: "SE", description: "XTAL Oscilator in Single-Ended mode", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "ETHERCATCLKCTL", description: "ETHERCATCLKCTL", offset: "0x36",
		bits: [
			{ name: "DIVSRCSEL", description: "Clock source select for the etherCAT clock", size: "1", shift: "0", mask: "0x1" },
			{ name: "ECATDIV", description: "etherCAT clock divider configuration.", size: "3", shift: "1", mask: "0xE" },
			{ name: "PHYCLKEN", description: "etherCAT PHY clock enable", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "CMCLKCTL", description: "CMCLKCTL", offset: "0x38",
		bits: [
			{ name: "CMDIVSRCSEL", description: "Clock source select for the CM clock divider.", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMCLKDIV", description: "CM clock divider configuration.", size: "3", shift: "1", mask: "0xE" },
			{ name: "ETHDIVSRCSEL", description: "Clock source select for the etherNET clock", size: "1", shift: "4", mask: "0x10" },
			{ name: "ETHDIV", description: "Ethernet clock divider configuration", size: "3", shift: "5", mask: "0xE0" },
		]
	},
	{ name: "CPUSYSLOCK1", description: "Lock bit for CPUSYS registers", offset: "0x0",
		bits: [
			{ name: "PIEVERRADDR", description: "Lock bit for PIEVERRADDR Register", size: "1", shift: "2", mask: "0x4" },
			{ name: "PCLKCR0", description: "Lock bit for PCLKCR0 Register", size: "1", shift: "3", mask: "0x8" },
			{ name: "PCLKCR1", description: "Lock bit for PCLKCR1 Register", size: "1", shift: "4", mask: "0x10" },
			{ name: "PCLKCR2", description: "Lock bit for PCLKCR2 Register", size: "1", shift: "5", mask: "0x20" },
			{ name: "PCLKCR3", description: "Lock bit for PCLKCR3 Register", size: "1", shift: "6", mask: "0x40" },
			{ name: "PCLKCR4", description: "Lock bit for PCLKCR4 Register", size: "1", shift: "7", mask: "0x80" },
			{ name: "PCLKCR6", description: "Lock bit for PCLKCR6 Register", size: "1", shift: "9", mask: "0x200" },
			{ name: "PCLKCR7", description: "Lock bit for PCLKCR7 Register", size: "1", shift: "10", mask: "0x400" },
			{ name: "PCLKCR8", description: "Lock bit for PCLKCR8 Register", size: "1", shift: "11", mask: "0x800" },
			{ name: "PCLKCR9", description: "Lock bit for PCLKCR9 Register", size: "1", shift: "12", mask: "0x1000" },
			{ name: "PCLKCR10", description: "Lock bit for PCLKCR10 Register", size: "1", shift: "13", mask: "0x2000" },
			{ name: "PCLKCR11", description: "Lock bit for PCLKCR11 Register", size: "1", shift: "14", mask: "0x4000" },
			{ name: "PCLKCR13", description: "Lock bit for PCLKCR13 Register", size: "1", shift: "16", mask: "0x10000" },
			{ name: "PCLKCR14", description: "Lock bit for PCLKCR14 Register", size: "1", shift: "17", mask: "0x20000" },
			{ name: "PCLKCR16", description: "Lock bit for PCLKCR16 Register", size: "1", shift: "19", mask: "0x80000" },
			{ name: "LPMCR", description: "Lock bit for LPMCR Register", size: "1", shift: "21", mask: "0x200000" },
			{ name: "GPIOLPMSEL0", description: "Lock bit for GPIOLPMSEL0 Register", size: "1", shift: "22", mask: "0x400000" },
			{ name: "GPIOLPMSEL1", description: "Lock bit for GPIOLPMSEL1 Register", size: "1", shift: "23", mask: "0x800000" },
			{ name: "PCLKCR17", description: "Lock bit for PCLKCR17 Register", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "PCLKCR18", description: "Lock bit for PCLKCR18 Register", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "PCLKCR20", description: "Lock bit for PCLKCR20 Register", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "PCLKCR21", description: "Lock bit for PCLKCR21 Register", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "PCLKCR22", description: "Lock bit for PCLKCR22 Register", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "PCLKCR23", description: "Lock bit for PCLKCR23 Register", size: "1", shift: "30", mask: "0x40000000" },
		]
	},
	{ name: "CPUSYSLOCK2", description: "Lock bit for CPUSYS registers", offset: "0x2",
		bits: [
			{ name: "ETHERCATCTL", description: "Lock bit for ETHERCATCTL register", size: "1", shift: "0", mask: "0x1" },
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
			{ name: "GTBCLKSYNC", description: "EPWM Time Base Clock Global sync", size: "1", shift: "19", mask: "0x80000" },
			{ name: "ERAD", description: "ERAD module clock enable", size: "1", shift: "24", mask: "0x1000000" },
		]
	},
	{ name: "PCLKCR1", description: "Peripheral Clock Gating Registers", offset: "0x24",
		bits: [
			{ name: "EMIF1", description: "EMIF1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EMIF2", description: "EMIF2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR2", description: "Peripheral Clock Gating Registers", offset: "0x26",
		bits: [
			{ name: "EPWM1", description: "EPWM1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EPWM2", description: "EPWM2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "EPWM3", description: "EPWM3 Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "EPWM4", description: "EPWM4 Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "EPWM5", description: "EPWM5 Clock Enable bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "EPWM6", description: "EPWM6 Clock Enable bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "EPWM7", description: "EPWM7 Clock Enable bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "EPWM8", description: "EPWM8 Clock Enable bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "EPWM9", description: "EPWM9 Clock Enable bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "EPWM10", description: "EPWM10 Clock Enable bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "EPWM11", description: "EPWM11 Clock Enable bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPWM12", description: "EPWM12 Clock Enable bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "EPWM13", description: "EPWM13 Clock Enable bit", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EPWM14", description: "EPWM14 Clock Enable bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EPWM15", description: "EPWM15 Clock Enable bit", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EPWM16", description: "EPWM16 Clock Enable bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "PCLKCR3", description: "Peripheral Clock Gating Registers", offset: "0x28",
		bits: [
			{ name: "ECAP1", description: "ECAP1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ECAP2", description: "ECAP2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ECAP3", description: "ECAP3 Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "ECAP4", description: "ECAP4 Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "ECAP5", description: "ECAP5 Clock Enable bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "ECAP6", description: "ECAP6 Clock Enable bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "ECAP7", description: "ECAP7 Clock Enable bit", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "PCLKCR4", description: "Peripheral Clock Gating Registers", offset: "0x2A",
		bits: [
			{ name: "EQEP1", description: "EQEP1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EQEP2", description: "EQEP2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "EQEP3", description: "EQEP3 Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "PCLKCR6", description: "Peripheral Clock Gating Registers", offset: "0x2E",
		bits: [
			{ name: "SD1", description: "SD1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SD2", description: "SD2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR7", description: "Peripheral Clock Gating Registers", offset: "0x30",
		bits: [
			{ name: "SCI_A", description: "SCI_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SCI_B", description: "SCI_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SCI_C", description: "SCI_C Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "SCI_D", description: "SCI_D Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "PCLKCR8", description: "Peripheral Clock Gating Registers", offset: "0x32",
		bits: [
			{ name: "SPI_A", description: "SPI_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SPI_B", description: "SPI_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SPI_C", description: "SPI_C Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "SPI_D", description: "SPI_D Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "PCLKCR9", description: "Peripheral Clock Gating Registers", offset: "0x34",
		bits: [
			{ name: "I2C_A", description: "I2C_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "I2C_B", description: "I2C_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR10", description: "Peripheral Clock Gating Registers", offset: "0x36",
		bits: [
			{ name: "CAN_A", description: "CAN_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CAN_B", description: "CAN_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "MCAN_A", description: "MCAN_A Clock Enable bit", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "PCLKCR11", description: "Peripheral Clock Gating Registers", offset: "0x38",
		bits: [
			{ name: "MCBSP_A", description: "McBSP_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "MCBSP_B", description: "McBSP_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "USB_A", description: "USB_A Clock Enable bit", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "PCLKCR13", description: "Peripheral Clock Gating Registers", offset: "0x3C",
		bits: [
			{ name: "ADC_A", description: "ADC_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B", description: "ADC_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADC_C", description: "ADC_C Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADC_D", description: "ADC_D Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "PCLKCR14", description: "Peripheral Clock Gating Registers", offset: "0x3E",
		bits: [
			{ name: "CMPSS1", description: "CMPSS1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPSS2", description: "CMPSS2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMPSS3", description: "CMPSS3 Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMPSS4", description: "CMPSS4 Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMPSS5", description: "CMPSS5 Clock Enable bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMPSS6", description: "CMPSS6 Clock Enable bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMPSS7", description: "CMPSS7 Clock Enable bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "CMPSS8", description: "CMPSS8 Clock Enable bit", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "PCLKCR16", description: "Peripheral Clock Gating Registers", offset: "0x42",
		bits: [
			{ name: "DAC_A", description: "Buffered_DAC12_1 Clock Enable Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DAC_B", description: "Buffered_DAC12_2 Clock Enable Bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DAC_C", description: "Buffered_DAC12_3 Clock Enable Bit", size: "1", shift: "18", mask: "0x40000" },
		]
	},
	{ name: "PCLKCR17", description: "Peripheral Clock Gating Registers", offset: "0x44",
		bits: [
			{ name: "CLB1", description: "CLB1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLB2", description: "CLB2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLB3", description: "CLB3 Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CLB4", description: "CLB4 Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLB5", description: "CLB5 Clock Enable bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLB6", description: "CLB6 Clock Enable bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLB7", description: "CLB7 Clock Enable bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "CLB8", description: "CLB8 Clock Enable bit", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "PCLKCR18", description: "Peripheral Clock Gating Registers", offset: "0x46",
		bits: [
			{ name: "FSITX_A", description: "FSITX_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "FSITX_B", description: "FSITX_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "FSIRX_A", description: "FSIRX_A Clock Enable bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FSIRX_B", description: "FSIRX_B Clock Enable bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "FSIRX_C", description: "FSIRX_C Clock Enable bit", size: "1", shift: "18", mask: "0x40000" },
			{ name: "FSIRX_D", description: "FSIRX_D Clock Enable bit", size: "1", shift: "19", mask: "0x80000" },
			{ name: "FSIRX_E", description: "FSIRX_E Clock Enable bit", size: "1", shift: "20", mask: "0x100000" },
			{ name: "FSIRX_F", description: "FSIRX_F Clock Enable bit", size: "1", shift: "21", mask: "0x200000" },
			{ name: "FSIRX_G", description: "FSIRX_G Clock Enable bit", size: "1", shift: "22", mask: "0x400000" },
			{ name: "FSIRX_H", description: "FSIRX_H Clock Enable bit", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "PCLKCR20", description: "Peripheral Clock Gating Registers", offset: "0x4A",
		bits: [
			{ name: "PMBUS_A", description: "PMBUS_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PCLKCR21", description: "Peripheral Clock Gating Registers", offset: "0x4C",
		bits: [
			{ name: "DCC0", description: "DCC0 Clock Enable Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "DCC1", description: "DCC1 Clock Enable Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "DCC2", description: "DCC2 Clock Enable Bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "PCLKCR22", description: "Peripheral Clock Gating Registers", offset: "0x4E",
		bits: [
			{ name: "MPOSTCLK", description: "MPOSTCLK Clock Enable Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PCLKCR23", description: "Peripheral Clock Gating Registers", offset: "0x50",
		bits: [
			{ name: "ETHERCAT", description: "ETHERCAT Clock Enable Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SIMRESET", description: "Simulated Reset Register", offset: "0x70",
		bits: [
			{ name: "CPU1RSN", description: "Generates a reset to CPU", size: "1", shift: "0", mask: "0x1" },
			{ name: "XRSN", description: "Generates a simulated XRSn", size: "1", shift: "1", mask: "0x2" },
			{ name: "KEY", description: "Key value", size: "16", shift: "16", mask: "0xFFFF0000" },
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
			{ name: "ECAT_RESET_OUT", description: "ECAT_RESET_OUT Reset Cause Indication Bit", size: "1", shift: "9", mask: "0x200" },
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
			{ name: "ECAT_RESET_OUT", description: "ECAT_RESET_OUT Reset Cause Indication Bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "SIMRESET_CPU1RSN", description: "SIMRESET_CPU1RSn Reset Cause Indication Bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "SIMRESET_XRSN", description: "SIMRESET_XRSn Reset Cause Indication Bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "XRSN_PIN_STATUS", description: "XRSN Pin Status", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "TRSTN_PIN_STATUS", description: "TRSTn Status", size: "1", shift: "31", mask: "0x80000000" },
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
	{ name: "DEVCFGLOCK1", description: "Lock bit for DEVCFG registers", offset: "0x0",
		bits: [
			{ name: "CPUSEL0", description: "Lock bit for CPUSEL0 register", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUSEL1", description: "Lock bit for CPUSEL1 register", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUSEL2", description: "Lock bit for CPUSEL2 register", size: "1", shift: "2", mask: "0x4" },
			{ name: "CPUSEL4", description: "Lock bit for CPUSEL4 register", size: "1", shift: "4", mask: "0x10" },
			{ name: "CPUSEL5", description: "Lock bit for CPUSEL5 register", size: "1", shift: "5", mask: "0x20" },
			{ name: "CPUSEL6", description: "Lock bit for CPUSEL6 register", size: "1", shift: "6", mask: "0x40" },
			{ name: "CPUSEL7", description: "Lock bit for CPUSEL7 register", size: "1", shift: "7", mask: "0x80" },
			{ name: "CPUSEL8", description: "Lock bit for CPUSEL8 register", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPUSEL9", description: "Lock bit for CPUSEL9 register", size: "1", shift: "9", mask: "0x200" },
			{ name: "CPUSEL11", description: "Lock bit for CPUSEL11 register", size: "1", shift: "11", mask: "0x800" },
			{ name: "CPUSEL12", description: "Lock bit for CPUSEL12 register", size: "1", shift: "12", mask: "0x1000" },
			{ name: "CPUSEL14", description: "Lock bit for CPUSEL14 register", size: "1", shift: "14", mask: "0x4000" },
			{ name: "CPUSEL15", description: "Lock bit for CPUSEL15 register", size: "1", shift: "15", mask: "0x8000" },
			{ name: "CPUSEL16", description: "Lock bit for CPUSEL16 register", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CPUSEL18", description: "Lock bit for CPUSEL18 register", size: "1", shift: "18", mask: "0x40000" },
			{ name: "CPUSEL25", description: "Lock bit for CPUSEL25 register", size: "1", shift: "25", mask: "0x2000000" },
		]
	},
	{ name: "PARTIDL", description: "Lower 32-bit of Device PART Identification Number", offset: "0x8",
		bits: [
			{ name: "QUAL", description: "Qualification Status", size: "2", shift: "6", mask: "0xC0" },
			{ name: "PIN_COUNT", description: "Device Pin Count", size: "3", shift: "8", mask: "0x700" },
			{ name: "INSTASPIN", description: "Motorware feature set", size: "2", shift: "13", mask: "0x6000" },
			{ name: "FLASH_SIZE", description: "Flash size in KB per CPU", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "PARTID_FORMAT_REVISION", description: "Revision of the PARTID format", size: "4", shift: "28", mask: "0xF0000000" },
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
	{ name: "PERCNF1", description: "Peripheral Configuration register", offset: "0x60",
		bits: [
			{ name: "ADC_A_MODE", description: "ADC Wrapper-1 mode setting bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B_MODE", description: "ADC Wrapper-2 mode setting bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADC_C_MODE", description: "ADC Wrapper-3 mode setting bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADC_D_MODE", description: "ADC Wrapper-4 mode setting bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "USB_A_PHY", description: "USB_A_PHY enable/disable bit", size: "1", shift: "16", mask: "0x10000" },
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
			{ name: "CPU2_CLA1", description: "CPU2_CLA1 software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CPU1_CPUBGCRC", description: "CPUBGCRC Module reset bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "CPU1_CLA1BGCRC", description: "CLA1BGCRC Module reset bit", size: "1", shift: "14", mask: "0x4000" },
			{ name: "CPU2_CPUBGCRC", description: "CPUBGCRC Module reset bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CPU2_CLA1BGCRC", description: "CLA1BGCRC Module reset bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "CPU1_ERAD", description: "ERAD Module reset bit", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "CPU2_ERAD", description: "ERAD Module reset bit", size: "1", shift: "25", mask: "0x2000000" },
		]
	},
	{ name: "SOFTPRES1", description: "EMIF Software Reset register", offset: "0x84",
		bits: [
			{ name: "EMIF1", description: "EMIF1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EMIF2", description: "EMIF2 software reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES2", description: "Peripheral Software Reset register", offset: "0x86",
		bits: [
			{ name: "EPWM1", description: "EPWM1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EPWM2", description: "EPWM2 software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "EPWM3", description: "EPWM3 software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "EPWM4", description: "EPWM4 software reset bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "EPWM5", description: "EPWM5 software reset bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "EPWM6", description: "EPWM6 software reset bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "EPWM7", description: "EPWM7 software reset bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "EPWM8", description: "EPWM8 software reset bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "EPWM9", description: "EPWM9 software reset bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "EPWM10", description: "EPWM10 software reset bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "EPWM11", description: "EPWM11 software reset bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPWM12", description: "EPWM12 software reset bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "EPWM13", description: "EPWM13 software reset bit", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EPWM14", description: "EPWM14 software reset bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EPWM15", description: "EPWM15 software reset bit", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EPWM16", description: "EPWM16 software reset bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SOFTPRES3", description: "Peripheral Software Reset register", offset: "0x88",
		bits: [
			{ name: "ECAP1", description: "ECAP1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ECAP2", description: "ECAP2 software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ECAP3", description: "ECAP3 software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "ECAP4", description: "ECAP4 software reset bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "ECAP5", description: "ECAP5 software reset bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "ECAP6", description: "ECAP6 software reset bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "ECAP7", description: "ECAP7 software reset bit", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "SOFTPRES4", description: "Peripheral Software Reset register", offset: "0x8A",
		bits: [
			{ name: "EQEP1", description: "EQEP1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EQEP2", description: "EQEP2 software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "EQEP3", description: "EQEP3 software reset bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "SOFTPRES6", description: "Peripheral Software Reset register", offset: "0x8E",
		bits: [
			{ name: "SD1", description: "SD1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SD2", description: "SD2 software reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES7", description: "Peripheral Software Reset register", offset: "0x90",
		bits: [
			{ name: "SCI_A", description: "SCI_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SCI_B", description: "SCI_B software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SCI_C", description: "SCI_C software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "SCI_D", description: "SCI_D software reset bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "SOFTPRES8", description: "Peripheral Software Reset register", offset: "0x92",
		bits: [
			{ name: "SPI_A", description: "SPI_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SPI_B", description: "SPI_B software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SPI_C", description: "SPI_C software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "SPI_D", description: "SPI_D software reset bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "SOFTPRES9", description: "Peripheral Software Reset register", offset: "0x94",
		bits: [
			{ name: "I2C_A", description: "I2C_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "I2C_B", description: "I2C_B software reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES10", description: "Peripheral Software Reset register", offset: "0x96",
		bits: [
			{ name: "CAN_A", description: "CAN_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CAN_B", description: "CAN_B software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "MCAN_A", description: "MCAN_A software reset bit", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "SOFTPRES11", description: "Peripheral Software Reset register", offset: "0x98",
		bits: [
			{ name: "MCBSP_A", description: "McBSP_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "MCBSP_B", description: "McBSP_B software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "USB_A", description: "USB_A software reset bit", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "SOFTPRES13", description: "Peripheral Software Reset register", offset: "0x9C",
		bits: [
			{ name: "ADC_A", description: "ADC_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B", description: "ADC_B software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADC_C", description: "ADC_C software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADC_D", description: "ADC_D software reset bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "SOFTPRES14", description: "Peripheral Software Reset register", offset: "0x9E",
		bits: [
			{ name: "CMPSS1", description: "CMPSS1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPSS2", description: "CMPSS2 software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMPSS3", description: "CMPSS3 software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMPSS4", description: "CMPSS4 software reset bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMPSS5", description: "CMPSS5 software reset bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMPSS6", description: "CMPSS6 software reset bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMPSS7", description: "CMPSS7 software reset bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "CMPSS8", description: "CMPSS8 software reset bit", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "SOFTPRES16", description: "Peripheral Software Reset register", offset: "0xA2",
		bits: [
			{ name: "DAC_A", description: "Buffered_DAC12_1 software reset bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DAC_B", description: "Buffered_DAC12_2 software reset bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DAC_C", description: "Buffered_DAC12_3 software reset bit", size: "1", shift: "18", mask: "0x40000" },
		]
	},
	{ name: "SOFTPRES17", description: "Reserved Peripheral Software Reset register", offset: "0xA4",
		bits: [
			{ name: "CLB1", description: "CLB1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLB2", description: "CLB2 software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLB3", description: "CLB3 software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CLB4", description: "CLB4 software reset bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLB5", description: "CLB5 software reset bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLB6", description: "CLB6 software reset bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLB7", description: "CLB7 software reset bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "CLB8", description: "CLB8 software reset bit", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "SOFTPRES18", description: "Reserved Peripheral Software Reset register", offset: "0xA6",
		bits: [
			{ name: "FSITX_A", description: "FSITX_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "FSITX_B", description: "FSITX_B software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "FSIRX_A", description: "FSIRX_A software reset bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FSIRX_B", description: "FSIRX_B software reset bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "FSIRX_C", description: "FSIRX_C software reset bit", size: "1", shift: "18", mask: "0x40000" },
			{ name: "FSIRX_D", description: "FSIRX_D software reset bit", size: "1", shift: "19", mask: "0x80000" },
			{ name: "FSIRX_E", description: "FSIRX_E software reset bit", size: "1", shift: "20", mask: "0x100000" },
			{ name: "FSIRX_F", description: "FSIRX_F software reset bit", size: "1", shift: "21", mask: "0x200000" },
			{ name: "FSIRX_G", description: "FSIRX_G software reset bit", size: "1", shift: "22", mask: "0x400000" },
			{ name: "FSIRX_H", description: "FSIRX_H software reset bit", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "SOFTPRES20", description: "Peripheral Software Reset register", offset: "0xAA",
		bits: [
			{ name: "PMBUS_A", description: "PMBUS_A software reset bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SOFTPRES21", description: "Peripheral Software Reset register", offset: "0xAC",
		bits: [
			{ name: "DCC0", description: "DCC0 Module reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "DCC1", description: "DCC1 Module reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "DCC2", description: "DCC2 Module reset bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "SOFTPRES23", description: "Peripheral Software Reset register", offset: "0xB0",
		bits: [
			{ name: "ETHERCAT", description: "ETHERCAT Module reset bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CPUSEL0", description: "CPU Select register for common peripherals", offset: "0xD6",
		bits: [
			{ name: "EPWM1", description: "EPWM1 CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EPWM2", description: "EPWM2 CPU select bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "EPWM3", description: "EPWM3 CPU select bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "EPWM4", description: "EPWM4 CPU select bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "EPWM5", description: "EPWM5 CPU select bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "EPWM6", description: "EPWM6 CPU select bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "EPWM7", description: "EPWM7 CPU select bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "EPWM8", description: "EPWM8 CPU select bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "EPWM9", description: "EPWM9 CPU select bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "EPWM10", description: "EPWM10 CPU select bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "EPWM11", description: "EPWM11 CPU select bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPWM12", description: "EPWM12 CPU select bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "EPWM13", description: "EPWM13 CPU select bit", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EPWM14", description: "EPWM14 CPU select bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EPWM15", description: "EPWM15 CPU select bit", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EPWM16", description: "EPWM16 CPU select bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CPUSEL1", description: "CPU Select register for common peripherals", offset: "0xD8",
		bits: [
			{ name: "ECAP1", description: "ECAP1 CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ECAP2", description: "ECAP2 CPU select bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ECAP3", description: "ECAP3 CPU select bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "ECAP4", description: "ECAP4 CPU select bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "ECAP5", description: "ECAP5 CPU select bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "ECAP6", description: "ECAP6 CPU select bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "ECAP7", description: "ECAP7 CPU select bit", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "CPUSEL2", description: "CPU Select register for common peripherals", offset: "0xDA",
		bits: [
			{ name: "EQEP1", description: "EQEP1 CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EQEP2", description: "EQEP2 CPU select bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "EQEP3", description: "EQEP3 CPU select bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "CPUSEL4", description: "CPU Select register for common peripherals", offset: "0xDE",
		bits: [
			{ name: "SD1", description: "SD1 CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SD2", description: "SD2 CPU select bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CPUSEL5", description: "CPU Select register for common peripherals", offset: "0xE0",
		bits: [
			{ name: "SCI_A", description: "SCI_A CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SCI_B", description: "SCI_B CPU select bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SCI_C", description: "SCI_C CPU select bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "SCI_D", description: "SCI_D CPU select bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "CPUSEL6", description: "CPU Select register for common peripherals", offset: "0xE2",
		bits: [
			{ name: "SPI_A", description: "SPI_A CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SPI_B", description: "SPI_B CPU select bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SPI_C", description: "SPI_C CPU select bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "SPI_D", description: "SPI_D CPU select bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "CPUSEL7", description: "CPU Select register for common peripherals", offset: "0xE4",
		bits: [
			{ name: "I2C_A", description: "I2C_A CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "I2C_B", description: "I2C_B CPU select bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CPUSEL8", description: "CPU Select register for common peripherals", offset: "0xE6",
		bits: [
			{ name: "CAN_A", description: "CAN_A CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CAN_B", description: "CAN_B CPU select bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "MCAN_A", description: "MCAN_A CPU select bit", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "CPUSEL9", description: "CPU Select register for common peripherals", offset: "0xE8",
		bits: [
			{ name: "MCBSP_A", description: "McBSP_A CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "MCBSP_B", description: "McBSP_B CPU select bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CPUSEL11", description: "CPU Select register for common peripherals", offset: "0xEC",
		bits: [
			{ name: "ADC_A", description: "ADC_A CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B", description: "ADC_B CPU select bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADC_C", description: "ADC_C CPU select bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADC_D", description: "ADC_D CPU select bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "CPUSEL12", description: "CPU Select register for common peripherals", offset: "0xEE",
		bits: [
			{ name: "CMPSS1", description: "CMPSS1 CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPSS2", description: "CMPSS2 CPU select bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMPSS3", description: "CMPSS3 CPU select bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMPSS4", description: "CMPSS4 CPU select bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMPSS5", description: "CMPSS5 CPU select bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMPSS6", description: "CMPSS6 CPU select bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMPSS7", description: "CMPSS7 CPU select bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "CMPSS8", description: "CMPSS8 CPU select bit", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "CPUSEL14", description: "CPU Select register for common peripherals", offset: "0xF2",
		bits: [
			{ name: "DAC_A", description: "Buffered_DAC12_1 CPU select bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DAC_B", description: "Buffered_DAC12_2 CPU select bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DAC_C", description: "Buffered_DAC12_3 CPU select bit", size: "1", shift: "18", mask: "0x40000" },
		]
	},
	{ name: "CPUSEL15", description: "CPU Select register for common peripherals", offset: "0xF4",
		bits: [
			{ name: "CLB1", description: "CLB1 CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLB2", description: "CLB2 CPU select bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLB3", description: "CLB3 CPU select bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CLB4", description: "CLB4 CPU select bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLB5", description: "CLB5 CPU select bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLB6", description: "CLB6 CPU select bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLB7", description: "CLB7 CPU select bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "CLB8", description: "CLB8 CPU select bit", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "CPUSEL16", description: "CPU Select register for common peripherals", offset: "0xF6",
		bits: [
			{ name: "FSITX_A", description: "FSITX_A CPU select bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "FSITX_B", description: "FSITX_B CPU select bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "FSIRX_A", description: "FSIRX_A CPU select bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FSIRX_B", description: "FSIRX_B CPU select bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "FSIRX_C", description: "FSIRX_C CPU select bit", size: "1", shift: "18", mask: "0x40000" },
			{ name: "FSIRX_D", description: "FSIRX_D CPU select bit", size: "1", shift: "19", mask: "0x80000" },
			{ name: "FSIRX_E", description: "FSIRX_E CPU select bit", size: "1", shift: "20", mask: "0x100000" },
			{ name: "FSIRX_F", description: "FSIRX_F CPU select bit", size: "1", shift: "21", mask: "0x200000" },
			{ name: "FSIRX_G", description: "FSIRX_G CPU select bit", size: "1", shift: "22", mask: "0x400000" },
			{ name: "FSIRX_H", description: "FSIRX_H CPU select bit", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "CPUSEL18", description: "CPU Select register for common peripherals", offset: "0xFA",
		bits: [
			{ name: "PMBUS_A", description: "PMBUS_A CPU select bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CPUSEL25", description: "CPU Select register for common peripherals", offset: "0x108",
		bits: [
			{ name: "HRCAL_A", description: "HRCAL CPU select bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CPU2RESCTL", description: "CPU2 Reset Control Register", offset: "0x122",
		bits: [
			{ name: "RESET", description: "CPU2 Reset Control bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Key Qualifier for writes to this register", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "RSTSTAT", description: "Reset Status register for secondary C28x CPUs", offset: "0x124",
		bits: [
			{ name: "CPU2RES", description: "CPU2 Reset Status bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPU2NMIWDRST", description: "Tells whether a CPU2.NMIWD reset was issued to", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPU2HWBISTRST", description: "Tells whether a HWBIST reset was issued to CPU2", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "LPMSTAT", description: "LPM Status Register for secondary C28x CPUs", offset: "0x125",
		bits: [
			{ name: "CPU2LPMSTAT", description: "CPU2 LPM Status", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "USBTYPE", description: "Configures USB Type for the device", offset: "0x19A",
		bits: [
			{ name: "TYPE", description: "Configure USB type", size: "2", shift: "0", mask: "0x3" },
			{ name: "LOCK", description: "Lock bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "ECAPTYPE", description: "Configures ECAP Type for the device", offset: "0x19B",
		bits: [
			{ name: "TYPE", description: "Configure ECAP type", size: "2", shift: "0", mask: "0x3" },
			{ name: "LOCK", description: "Lock bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SDFMTYPE", description: "Configures SDFM Type for the device", offset: "0x19C",
		bits: [
			{ name: "TYPE", description: "Configure SDFM type", size: "2", shift: "0", mask: "0x3" },
			{ name: "LOCK", description: "Lock bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "MEMMAPTYPE", description: "Configures Memory Map Type for the device", offset: "0x19E",
		bits: [
			{ name: "TYPE", description: "Configures system specific features related to", size: "2", shift: "0", mask: "0x3" },
			{ name: "LOCK", description: "Lock bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "ADCA_AC", description: "ADCA Master Access Control Register", offset: "0x0",
		bits: [
			{ name: "CPUX_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ADCB_AC", description: "ADCB Master Access Control Register", offset: "0x2",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ADCC_AC", description: "ADCC Master Access Control Register", offset: "0x4",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ADCD_AC", description: "ADCD Master Access Control Register", offset: "0x6",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CMPSS1_AC", description: "CMPSS1 Master Access Control Register", offset: "0x10",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CMPSS2_AC", description: "CMPSS2 Master Access Control Register", offset: "0x12",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CMPSS3_AC", description: "CMPSS3 Master Access Control Register", offset: "0x14",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CMPSS4_AC", description: "CMPSS4 Master Access Control Register", offset: "0x16",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CMPSS5_AC", description: "CMPSS5 Master Access Control Register", offset: "0x18",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CMPSS6_AC", description: "CMPSS6 Master Access Control Register", offset: "0x1A",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CMPSS7_AC", description: "CMPSS7 Master Access Control Register", offset: "0x1C",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CMPSS8_AC", description: "CMPSS8 Master Access Control Register", offset: "0x1E",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "DACA_AC", description: "DACA Master Access Control Register", offset: "0x28",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "DACB_AC", description: "DACB Master Access Control Register", offset: "0x2A",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "DACC_AC", description: "DACC Master Access Control Register", offset: "0x2C",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM1_AC", description: "EPWM1 Master Access Control Register", offset: "0x48",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM2_AC", description: "EPWM2 Master Access Control Register", offset: "0x4A",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM3_AC", description: "EPWM3 Master Access Control Register", offset: "0x4C",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM4_AC", description: "EPWM4 Master Access Control Register", offset: "0x4E",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM5_AC", description: "EPWM5 Master Access Control Register", offset: "0x50",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM6_AC", description: "EPWM6 Master Access Control Register", offset: "0x52",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM7_AC", description: "EPWM7 Master Access Control Register", offset: "0x54",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM8_AC", description: "EPWM8 Master Access Control Register", offset: "0x56",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM9_AC", description: "EPWM9 Master Access Control Register", offset: "0x58",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM10_AC", description: "EPWM10 Master Access Control Register", offset: "0x5A",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM11_AC", description: "EPWM11 Master Access Control Register", offset: "0x5C",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM12_AC", description: "EPWM12 Master Access Control Register", offset: "0x5E",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM13_AC", description: "EPWM13 Master Access Control Register", offset: "0x60",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM14_AC", description: "EPWM14 Master Access Control Register", offset: "0x62",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM15_AC", description: "EPWM15 Master Access Control Register", offset: "0x64",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM16_AC", description: "EPWM16 Master Access Control Register", offset: "0x66",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EQEP1_AC", description: "EQEP1 Master Access Control Register", offset: "0x70",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EQEP2_AC", description: "EQEP2 Master Access Control Register", offset: "0x72",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EQEP3_AC", description: "EQEP3 Master Access Control Register", offset: "0x74",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ECAP1_AC", description: "ECAP1 Master Access Control Register", offset: "0x80",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ECAP2_AC", description: "ECAP2 Master Access Control Register", offset: "0x82",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ECAP3_AC", description: "ECAP3 Master Access Control Register", offset: "0x84",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ECAP4_AC", description: "ECAP4 Master Access Control Register", offset: "0x86",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ECAP5_AC", description: "ECAP5 Master Access Control Register", offset: "0x88",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ECAP6_AC", description: "ECAP6 Master Access Control Register", offset: "0x8A",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ECAP7_AC", description: "ECAP7 Master Access Control Register", offset: "0x8C",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "SDFM1_AC", description: "SDFM1 Master Access Control Register", offset: "0xA8",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "SDFM2_AC", description: "SDFM2 Master Access Control Register", offset: "0xAA",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CLB1_AC", description: "CLB1 Master Access Control Register", offset: "0xB0",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "CLB2_AC", description: "CLB2 Master Access Control Register", offset: "0xB2",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "CLB3_AC", description: "CLB3 Master Access Control Register", offset: "0xB4",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "CLB4_AC", description: "CLB4 Master Access Control Register", offset: "0xB6",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "CLB5_AC", description: "CLB5 Master Access Control Register", offset: "0xB8",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "CLB6_AC", description: "CLB6 Master Access Control Register", offset: "0xBA",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "CLB7_AC", description: "CLB7 Master Access Control Register", offset: "0xBC",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "CLB8_AC", description: "CLB8 Master Access Control Register", offset: "0xBE",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "SPIA_AC", description: "SPIA Master Access Control Register", offset: "0x110",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "SPIB_AC", description: "SPIB Master Access Control Register", offset: "0x112",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "SPIC_AC", description: "SPIC Master Access Control Register", offset: "0x114",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "SPID_AC", description: "SPID Master Access Control Register", offset: "0x116",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "PMBUS_A_AC", description: "PMBUSA Master Access Control Register", offset: "0x130",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CAN_A_AC", description: "CAN_A Master Access Control Register", offset: "0x140",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CAN_B_AC", description: "CAN_B Master Access Control Register", offset: "0x142",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "MCBSPA_AC", description: "MCBSPA Master Access Control Register", offset: "0x150",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "MCBSPB_AC", description: "MCBSPB Master Access Control Register", offset: "0x152",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "USBA_AC", description: "USBA Master Access Control Register", offset: "0x180",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "HRPWM_AC", description: "HRPWM Master Access Control Register", offset: "0x1A8",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ETHERCAT_AC", description: "ETHERCAT Master Access Control Register", offset: "0x1AA",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSIATX_AC", description: "FSIATX Master Access Control Register", offset: "0x1B0",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSIARX_AC", description: "FSIARX Master Access Control Register", offset: "0x1B2",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSIBTX_AC", description: "FSIBTX Master Access Control Register", offset: "0x1B4",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSIBRX_AC", description: "FSIBRX Master Access Control Register", offset: "0x1B6",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSICRX_AC", description: "FSICRX Master Access Control Register", offset: "0x1BA",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSIDRX_AC", description: "FSIDRX Master Access Control Register", offset: "0x1BE",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSIERX_AC", description: "FSIERX Master Access Control Register", offset: "0x1C2",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSIFRX_AC", description: "FSIFRX Master Access Control Register", offset: "0x1C6",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSIGRX_AC", description: "FSIGRX Master Access Control Register", offset: "0x1CA",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSIHRX_AC", description: "FSIHRX Master Access Control Register", offset: "0x1CE",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "MCANA_AC", description: "MCANA Master Access Control Register", offset: "0x1D0",
		bits: [
			{ name: "CPUX_ACC", description: "CPUx Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "PERIPH_AC_LOCK", description: "Lock Register to stop Write access to peripheral", offset: "0x1FE",
		bits: [
			{ name: "LOCK_AC_WR", description: "Lock control for Access control registers", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CMRESCTL", description: "CM Reset Control Register", offset: "0x0",
		bits: [
			{ name: "RESET", description: "Software reset to CM", size: "1", shift: "0", mask: "0x1" },
			{ name: "RESETSTS", description: "CM Reset status", size: "1", shift: "1", mask: "0x2" },
			{ name: "KEY", description: "Key value", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CMTOCPU1NMICTL", description: "CM To CPU1 NMI Control register", offset: "0x2",
		bits: [
			{ name: "CMNMIWDRST", description: "CMNMIWDRST NMI enable bit, enables nmi", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "CMTOCPU1INTCTL", description: "CM To CPU1 interrupt Control register", offset: "0x4",
		bits: [
			{ name: "VECTRESET", description: "VECTRESET Interrupt enable bit, enables", size: "1", shift: "0", mask: "0x1" },
			{ name: "SYSRESETREQ", description: "SYSRESETREQ Interrupt enable bit, enables", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMNMIWDRST", description: "CMNMIWDRST Interrupt enable bit, enables", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "PALLOCATE0", description: "CM Peripheral Allocation Register.", offset: "0x20",
		bits: [
			{ name: "USB_A", description: "Allocate USB_A to CM", size: "1", shift: "0", mask: "0x1" },
			{ name: "ETHERCAT", description: "Allocate ETHERCAT to CM", size: "1", shift: "1", mask: "0x2" },
			{ name: "CAN_A", description: "Allocate CANA to CM", size: "1", shift: "2", mask: "0x4" },
			{ name: "CAN_B", description: "Allocate CANB to CM", size: "1", shift: "3", mask: "0x8" },
			{ name: "MCAN_A", description: "Allocate MCANA to CM", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "CM_CONF_REGS_LOCK", description: "CM Configuration Registers Lock", offset: "0x3FE",
		bits: [
			{ name: "LOCK", description: "Lock one time CM configuration registers.", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CM_STATUS_INT_FLG", description: "Status of interrupts due to multiple sources of", offset: "0x0",
		bits: [
			{ name: "GINT", description: "Global Interrupt flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMNMIWDRST", description: "CMNMIWDRST caused a reset of CM", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMSYSRESETREQ", description: "CMSYSRESETREQ caused a reset of CM", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMVECTRESET", description: "CMVECTRESET caused a reset of CM", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "CM_STATUS_INT_CLR", description: "CM_STATUS_INT_FLG clear register", offset: "0x2",
		bits: [
			{ name: "GINT", description: "Global Interrupt flag Clear bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMNMIWDRST", description: "CMNMIWDRST interrupt flag clear bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMSYSRESETREQ", description: "CMSYSRESETREQ interrupt flag clear bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMVECTRESET", description: "CMVECTRESET interrupt flag clear bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "CM_STATUS_INT_SET", description: "CM_STATUS_INT_FLG set register", offset: "0x4",
		bits: [
			{ name: "CMNMIWDRST", description: "CMNMIWDRST interrupt flag set bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMSYSRESETREQ", description: "CMSYSRESETREQ interrupt flag set", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMVECTRESET", description: "CMVECTRESET interrupt flag set", size: "1", shift: "3", mask: "0x8" },
			{ name: "KEY", description: "KEY field", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CM_STATUS_MASK", description: "CM_STATUS_MASK register", offset: "0x6",
		bits: [
			{ name: "CMNMIWDRST", description: "CMNMIWDRST flag mask bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMSYSRESETREQ", description: "CMSYSRESETREQ interrupt flag set bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMVECTRESET", description: "CMVECTRESET interrupt flag set bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "KEY", description: "KEY field", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SYS_ERR_INT_FLG", description: "Status of interrupts due to multiple different", offset: "0x10",
		bits: [
			{ name: "GINT", description: "Global Interrupt flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "EMIF_ERR", description: "EMIF error event flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "RAM_CORRECTABLE_ERR", description: "RAM correctable error flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "FLASH_CORRECTABLE_ERR", description: "FLASH correctable error flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "RAM_ACC_VIOL", description: "RAM access vioation flag.", size: "1", shift: "4", mask: "0x10" },
			{ name: "SYS_PLL_SLIP_NOTSUPPORTED", description: "System PLL Slip event flag.", size: "1", shift: "5", mask: "0x20" },
			{ name: "AUX_PLL_SLIP_NOTSUPPORTED", description: "Auxillary PLL Slip event", size: "1", shift: "6", mask: "0x40" },
			{ name: "DCC0", description: "DCC0 Interrupt flag.", size: "1", shift: "7", mask: "0x80" },
			{ name: "DCC1", description: "DCC1 Interrupt flag.", size: "1", shift: "8", mask: "0x100" },
			{ name: "DCC2", description: "DCC2 Interrupt flag.", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "SYS_ERR_INT_CLR", description: "SYS_ERR_INT_FLG clear register", offset: "0x12",
		bits: [
			{ name: "GINT", description: "Global Interrupt flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "EMIF_ERR", description: "EMIF_ERR interrupt flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "RAM_CORRECTABLE_ERR", description: "RAM_CORRECTABLE_ERR", size: "1", shift: "2", mask: "0x4" },
			{ name: "FLASH_CORRECTABLE_ERR", description: "FLASH_CORRECTABLE_ERR", size: "1", shift: "3", mask: "0x8" },
			{ name: "RAM_ACC_VIOL", description: "RAM_ACC_VIOL interrupt flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "SYS_PLL_SLIP_NOTSUPPORTED", description: "SYS_PLL_SLIP interrupt flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "AUX_PLL_SLIP_NOTSUPPORTED", description: "AUX_PLL_SLIP interrupt flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "DCC0", description: "DCC0 interrupt flag clear", size: "1", shift: "7", mask: "0x80" },
			{ name: "DCC1", description: "DCC1 interrupt flag clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "DCC2", description: "DCC2 interrupt flag clear", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "SYS_ERR_INT_SET", description: "SYS_ERR_INT_FLG set register", offset: "0x14",
		bits: [
			{ name: "EMIF_ERR", description: "Reserved", size: "1", shift: "1", mask: "0x2" },
			{ name: "RAM_CORRECTABLE_ERR", description: "RAM_CORRECTABLE_ERR", size: "1", shift: "2", mask: "0x4" },
			{ name: "FLASH_CORRECTABLE_ERR", description: "FLASH_CORRECTABLE_ERR", size: "1", shift: "3", mask: "0x8" },
			{ name: "RAM_ACC_VIOL", description: "RAM_ACC_VIOL interrupt", size: "1", shift: "4", mask: "0x10" },
			{ name: "SYS_PLL_SLIP_NOTSUPPORTED", description: "SYS_PLL_SLIP interrupt", size: "1", shift: "5", mask: "0x20" },
			{ name: "AUX_PLL_SLIP_NOTSUPPORTED", description: "AUX_PLL_SLIP interrupt", size: "1", shift: "6", mask: "0x40" },
			{ name: "DCC0", description: "DCC0 interrupt flag set", size: "1", shift: "7", mask: "0x80" },
			{ name: "DCC1", description: "DCC1 interrupt flag set", size: "1", shift: "8", mask: "0x100" },
			{ name: "DCC2", description: "DCC2 interrupt flag set", size: "1", shift: "9", mask: "0x200" },
			{ name: "KEY", description: "KEY field", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SYS_ERR_MASK", description: "SYS_ERR_MASK register", offset: "0x16",
		bits: [
			{ name: "EMIF_ERR", description: "Reserved", size: "1", shift: "1", mask: "0x2" },
			{ name: "RAM_CORRECTABLE_ERR", description: "RAM_CORRECTABLE_ERR flag mask", size: "1", shift: "2", mask: "0x4" },
			{ name: "FLASH_CORRECTABLE_ERR", description: "FLASH_CORRECTABLE_ERR flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "RAM_ACC_VIOL", description: "RAM_ACC_VIOL flag mask bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "SYS_PLL_SLIP", description: "SYS_PLL_SLIP flag mask bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "AUX_PLL_SLIP", description: "AUX_PLL_SLIP flag mask bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "DCC0", description: "DCC0 flag mask bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "DCC1", description: "DCC1 flag mask bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "DCC2", description: "DCC2 flag mask bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "KEY", description: "KEY field", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "SYNCSELECT", description: "Sync Input and Output Select Register", offset: "0x0",
		bits: [
			{ name: "SYNCOUT", description: "Select Syncout Source", size: "5", shift: "24", mask: "0x1F000000" },
		]
	},
	{ name: "ADCSOCOUTSELECT", description: "External ADC (Off Chip) SOC Select Register", offset: "0x2",
		bits: [
			{ name: "PWM1SOCAEN", description: "PWM1SOCAEN Enable for ADCSOCAOn", size: "1", shift: "0", mask: "0x1" },
			{ name: "PWM2SOCAEN", description: "PWM2SOCAEN Enable for ADCSOCAOn", size: "1", shift: "1", mask: "0x2" },
			{ name: "PWM3SOCAEN", description: "PWM3SOCAEN Enable for ADCSOCAOn", size: "1", shift: "2", mask: "0x4" },
			{ name: "PWM4SOCAEN", description: "PWM4SOCAEN Enable for ADCSOCAOn", size: "1", shift: "3", mask: "0x8" },
			{ name: "PWM5SOCAEN", description: "PWM5SOCAEN Enable for ADCSOCAOn", size: "1", shift: "4", mask: "0x10" },
			{ name: "PWM6SOCAEN", description: "PWM6SOCAEN Enable for ADCSOCAOn", size: "1", shift: "5", mask: "0x20" },
			{ name: "PWM7SOCAEN", description: "PWM7SOCAEN Enable for ADCSOCAOn", size: "1", shift: "6", mask: "0x40" },
			{ name: "PWM8SOCAEN", description: "PWM8SOCAEN Enable for ADCSOCAOn", size: "1", shift: "7", mask: "0x80" },
			{ name: "PWM9SOCAEN", description: "PWM9SOCAEN Enable for ADCSOCAOn", size: "1", shift: "8", mask: "0x100" },
			{ name: "PWM10SOCAEN", description: "PWM10SOCAEN Enable for ADCSOCAOn", size: "1", shift: "9", mask: "0x200" },
			{ name: "PWM11SOCAEN", description: "PWM11SOCAEN Enable for ADCSOCAOn", size: "1", shift: "10", mask: "0x400" },
			{ name: "PWM12SOCAEN", description: "PWM12SOCAEN Enable for ADCSOCAOn", size: "1", shift: "11", mask: "0x800" },
			{ name: "PWM13SOCAEN", description: "PWM13SOCAEN Enable for ADCSOCAOn", size: "1", shift: "12", mask: "0x1000" },
			{ name: "PWM14SOCAEN", description: "PWM14SOCAEN Enable for ADCSOCAOn", size: "1", shift: "13", mask: "0x2000" },
			{ name: "PWM15SOCAEN", description: "PWM15SOCAEN Enable for ADCSOCAOn", size: "1", shift: "14", mask: "0x4000" },
			{ name: "PWM16SOCAEN", description: "PWM16SOCAEN Enable for ADCSOCAOn", size: "1", shift: "15", mask: "0x8000" },
			{ name: "PWM1SOCBEN", description: "PWM1SOCBEN Enable for ADCSOCBOn", size: "1", shift: "16", mask: "0x10000" },
			{ name: "PWM2SOCBEN", description: "PWM2SOCBEN Enable for ADCSOCBOn", size: "1", shift: "17", mask: "0x20000" },
			{ name: "PWM3SOCBEN", description: "PWM3SOCBEN Enable for ADCSOCBOn", size: "1", shift: "18", mask: "0x40000" },
			{ name: "PWM4SOCBEN", description: "PWM4SOCBEN Enable for ADCSOCBOn", size: "1", shift: "19", mask: "0x80000" },
			{ name: "PWM5SOCBEN", description: "PWM5SOCBEN Enable for ADCSOCBOn", size: "1", shift: "20", mask: "0x100000" },
			{ name: "PWM6SOCBEN", description: "PWM6SOCBEN Enable for ADCSOCBOn", size: "1", shift: "21", mask: "0x200000" },
			{ name: "PWM7SOCBEN", description: "PWM7SOCBEN Enable for ADCSOCBOn", size: "1", shift: "22", mask: "0x400000" },
			{ name: "PWM8SOCBEN", description: "PWM8SOCBEN Enable for ADCSOCBOn", size: "1", shift: "23", mask: "0x800000" },
			{ name: "PWM9SOCBEN", description: "PWM9SOCBEN Enable for ADCSOCBOn", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "PWM10SOCBEN", description: "PWM10SOCBEN Enable for ADCSOCBOn", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "PWM11SOCBEN", description: "PWM11SOCBEN Enable for ADCSOCBOn", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "PWM12SOCBEN", description: "PWM12SOCBEN Enable for ADCSOCBOn", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "PWM13SOCBEN", description: "PWM13SOCBEN Enable for ADCSOCBOn", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "PWM14SOCBEN", description: "PWM14SOCBEN Enable for ADCSOCBOn", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "PWM15SOCBEN", description: "PWM15SOCBEN Enable for ADCSOCBOn", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "PWM16SOCBEN", description: "PWM16SOCBEN Enable for ADCSOCBOn", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SYNCSOCLOCK", description: "SYNCSEL and EXTADCSOC Select Lock register", offset: "0x4",
		bits: [
			{ name: "SYNCSELECT", description: "SYNCSEL Register Lock bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCSOCOUTSELECT", description: "ADCSOCOUTSELECT Register Lock bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
];
module.exports = {
	SYSCTLRegisters: SYSCTLRegisters,
}
