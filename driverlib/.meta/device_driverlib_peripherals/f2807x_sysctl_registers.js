let SYSCTLRegisters = [
	{ name: "PARTIDL", description: "Lower 32-bit of Device PART Identification Number", offset: "0x8",
		bits: [
			{ name: "QUAL", description: "Qualification Status", size: "2", shift: "6", mask: "0xC0" },
			{ name: "PIN_COUNT", description: "Device Pin Count", size: "3", shift: "8", mask: "0x700" },
			{ name: "INSTASPIN", description: "Motorware feature set", size: "2", shift: "13", mask: "0x6000" },
			{ name: "FLASH_SIZE", description: "Flash size in KB", size: "8", shift: "16", mask: "0xFF0000" },
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
		]
	},
	{ name: "DC0", description: "Device Capability: Device Information", offset: "0x10",
		bits: [
			{ name: "SINGLE_CORE", description: "Single Core vs Dual Core", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "DC1", description: "Device Capability: Processing Block Customization", offset: "0x12",
		bits: [
			{ name: "CPU1_FPU_TMU", description: "CPU1's FPU1+TMU1", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPU1_VCU", description: "CPU1's VCU", size: "1", shift: "2", mask: "0x4" },
			{ name: "CPU1_CLA1", description: "CPU1.CLA1", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "DC2", description: "Device Capability: EMIF Customization", offset: "0x14",
		bits: [
			{ name: "EMIF1", description: "EMIF1", size: "1", shift: "0", mask: "0x1" },
			{ name: "EMIF2", description: "EMIF2", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "DC3", description: "Device Capability: Peripheral Customization", offset: "0x16",
		bits: [
			{ name: "EPWM1", description: "EPWM1", size: "1", shift: "0", mask: "0x1" },
			{ name: "EPWM2", description: "EPWM2", size: "1", shift: "1", mask: "0x2" },
			{ name: "EPWM3", description: "EPWM3", size: "1", shift: "2", mask: "0x4" },
			{ name: "EPWM4", description: "EPWM4", size: "1", shift: "3", mask: "0x8" },
			{ name: "EPWM5", description: "EPWM5", size: "1", shift: "4", mask: "0x10" },
			{ name: "EPWM6", description: "EPWM6", size: "1", shift: "5", mask: "0x20" },
			{ name: "EPWM7", description: "EPWM7", size: "1", shift: "6", mask: "0x40" },
			{ name: "EPWM8", description: "EPWM8", size: "1", shift: "7", mask: "0x80" },
			{ name: "EPWM9", description: "EPWM9", size: "1", shift: "8", mask: "0x100" },
			{ name: "EPWM10", description: "EPWM10", size: "1", shift: "9", mask: "0x200" },
			{ name: "EPWM11", description: "EPWM11", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPWM12", description: "EPWM12", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "DC4", description: "Device Capability: Peripheral Customization", offset: "0x18",
		bits: [
			{ name: "ECAP1", description: "ECAP1", size: "1", shift: "0", mask: "0x1" },
			{ name: "ECAP2", description: "ECAP2", size: "1", shift: "1", mask: "0x2" },
			{ name: "ECAP3", description: "ECAP3", size: "1", shift: "2", mask: "0x4" },
			{ name: "ECAP4", description: "ECAP4", size: "1", shift: "3", mask: "0x8" },
			{ name: "ECAP5", description: "ECAP5", size: "1", shift: "4", mask: "0x10" },
			{ name: "ECAP6", description: "ECAP6", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "DC5", description: "Device Capability: Peripheral Customization", offset: "0x1A",
		bits: [
			{ name: "EQEP1", description: "EQEP1", size: "1", shift: "0", mask: "0x1" },
			{ name: "EQEP2", description: "EQEP2", size: "1", shift: "1", mask: "0x2" },
			{ name: "EQEP3", description: "EQEP3", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "DC6", description: "Device Capability: Peripheral Customization", offset: "0x1C",
		bits: [
			{ name: "CLB1", description: "CLB1", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLB2", description: "CLB2", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLB3", description: "CLB3", size: "1", shift: "2", mask: "0x4" },
			{ name: "CLB4", description: "CLB4", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "DC7", description: "Device Capability: Peripheral Customization", offset: "0x1E",
		bits: [
			{ name: "SD1", description: "SD1", size: "1", shift: "0", mask: "0x1" },
			{ name: "SD2", description: "SD2", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "DC8", description: "Device Capability: Peripheral Customization", offset: "0x20",
		bits: [
			{ name: "SCI_A", description: "SCI_A", size: "1", shift: "0", mask: "0x1" },
			{ name: "SCI_B", description: "SCI_B", size: "1", shift: "1", mask: "0x2" },
			{ name: "SCI_C", description: "SCI_C", size: "1", shift: "2", mask: "0x4" },
			{ name: "SCI_D", description: "SCI_D", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "DC9", description: "Device Capability: Peripheral Customization", offset: "0x22",
		bits: [
			{ name: "SPI_A", description: "SPI_A", size: "1", shift: "0", mask: "0x1" },
			{ name: "SPI_B", description: "SPI_B", size: "1", shift: "1", mask: "0x2" },
			{ name: "SPI_C", description: "SPI_C", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "DC10", description: "Device Capability: Peripheral Customization", offset: "0x24",
		bits: [
			{ name: "I2C_A", description: "I2C_A", size: "1", shift: "0", mask: "0x1" },
			{ name: "I2C_B", description: "I2C_B", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "DC11", description: "Device Capability: Peripheral Customization", offset: "0x26",
		bits: [
			{ name: "CAN_A", description: "CAN_A", size: "1", shift: "0", mask: "0x1" },
			{ name: "CAN_B", description: "CAN_B", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "DC12", description: "Device Capability: Peripheral Customization", offset: "0x28",
		bits: [
			{ name: "MCBSP_A", description: "McBSP_A", size: "1", shift: "0", mask: "0x1" },
			{ name: "MCBSP_B", description: "McBSP_B", size: "1", shift: "1", mask: "0x2" },
			{ name: "USB_A", description: "Decides the capability of the USB_A Module", size: "2", shift: "16", mask: "0x30000" },
		]
	},
	{ name: "DC13", description: "Device Capability: Peripheral Customization", offset: "0x2A",
		bits: [
			{ name: "UPP_A", description: "uPP_A", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "DC14", description: "Device Capability: Analog Modules Customization", offset: "0x2C",
		bits: [
			{ name: "ADC_A", description: "ADC_A", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B", description: "ADC_B", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADC_C", description: "ADC_C", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADC_D", description: "ADC_D", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "DC15", description: "Device Capability: Analog Modules Customization", offset: "0x2E",
		bits: [
			{ name: "CMPSS1", description: "CMPSS1", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPSS2", description: "CMPSS2", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMPSS3", description: "CMPSS3", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMPSS4", description: "CMPSS4", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMPSS5", description: "CMPSS5", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMPSS6", description: "CMPSS6", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMPSS7", description: "CMPSS7", size: "1", shift: "6", mask: "0x40" },
			{ name: "CMPSS8", description: "CMPSS8", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "DC17", description: "Device Capability: Analog Modules Customization", offset: "0x32",
		bits: [
			{ name: "DAC_A", description: "Buffered-DAC_A", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DAC_B", description: "Buffered-DAC_B", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DAC_C", description: "Buffered-DAC_C", size: "1", shift: "18", mask: "0x40000" },
		]
	},
	{ name: "DC18", description: "Device Capability: CPU1 Lx SRAM Customization", offset: "0x34",
		bits: [
			{ name: "LS0_1", description: "LS0_1", size: "1", shift: "0", mask: "0x1" },
			{ name: "LS1_1", description: "LS1_1", size: "1", shift: "1", mask: "0x2" },
			{ name: "LS2_1", description: "LS2_1", size: "1", shift: "2", mask: "0x4" },
			{ name: "LS3_1", description: "LS3_1", size: "1", shift: "3", mask: "0x8" },
			{ name: "LS4_1", description: "LS4_1", size: "1", shift: "4", mask: "0x10" },
			{ name: "LS5_1", description: "LS5_1", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "DC20", description: "Device Capability: GSx SRAM Customization", offset: "0x38",
		bits: [
			{ name: "GS0", description: "GS0", size: "1", shift: "0", mask: "0x1" },
			{ name: "GS1", description: "GS1", size: "1", shift: "1", mask: "0x2" },
			{ name: "GS2", description: "GS2", size: "1", shift: "2", mask: "0x4" },
			{ name: "GS3", description: "GS3", size: "1", shift: "3", mask: "0x8" },
			{ name: "GS4", description: "GS4", size: "1", shift: "4", mask: "0x10" },
			{ name: "GS5", description: "GS5", size: "1", shift: "5", mask: "0x20" },
			{ name: "GS6", description: "GS6", size: "1", shift: "6", mask: "0x40" },
			{ name: "GS7", description: "GS7", size: "1", shift: "7", mask: "0x80" },
			{ name: "GS8", description: "GS8", size: "1", shift: "8", mask: "0x100" },
			{ name: "GS9", description: "GS9", size: "1", shift: "9", mask: "0x200" },
			{ name: "GS10", description: "GS10", size: "1", shift: "10", mask: "0x400" },
			{ name: "GS11", description: "GS11", size: "1", shift: "11", mask: "0x800" },
			{ name: "GS12", description: "GS12", size: "1", shift: "12", mask: "0x1000" },
			{ name: "GS13", description: "GS13", size: "1", shift: "13", mask: "0x2000" },
			{ name: "GS14", description: "GS14", size: "1", shift: "14", mask: "0x4000" },
			{ name: "GS15", description: "GS15", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "PERCNF1", description: "Peripheral Configuration register", offset: "0x60",
		bits: [
			{ name: "ADC_A_MODE", description: "ADC_A mode setting bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B_MODE", description: "ADC_B mode setting bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADC_D_MODE", description: "ADC_D mode setting bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "USB_A_PHY", description: "USB_A_PHY", size: "1", shift: "16", mask: "0x10000" },
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
		]
	},
	{ name: "SOFTPRES9", description: "Peripheral Software Reset register", offset: "0x94",
		bits: [
			{ name: "I2C_A", description: "I2C_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "I2C_B", description: "I2C_B software reset bit", size: "1", shift: "1", mask: "0x2" },
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
			{ name: "DAC_A", description: "Buffered_DAC_A software reset bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DAC_B", description: "Buffered_DAC_B software reset bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DAC_C", description: "Buffered_DAC_C software reset bit", size: "1", shift: "18", mask: "0x40000" },
		]
	},
	{ name: "SYSDBGCTL", description: "System Debug Control register", offset: "0x12C",
		bits: [
			{ name: "BIT_0", description: "Used in PLL startup. Only reset by POR.", size: "1", shift: "0", mask: "0x1" },
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
			{ name: "LOSPCP", description: "Lock bit for LOSPCP register", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CLKSRCCTL1", description: "Clock Source Control register-1", offset: "0x8",
		bits: [
			{ name: "OSCCLKSRCSEL", description: "OSCCLK Source Select Bit", size: "2", shift: "0", mask: "0x3" },
			{ name: "INTOSC2OFF", description: "Internal Oscillator 2 Off Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "XTALOFF", description: "Crystal (External) Oscillator Off Bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "WDHALTI", description: "Watchdog HALT Mode Ignore Bit", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "CLKSRCCTL2", description: "Clock Source Control register-2", offset: "0xA",
		bits: [
			{ name: "AUXOSCCLKSRCSEL", description: "AUXOSCCLK Source Select Bit", size: "2", shift: "0", mask: "0x3" },
			{ name: "CANABCLKSEL", description: "CANA Bit Clock Source Select Bit", size: "2", shift: "2", mask: "0xC" },
			{ name: "CANBBCLKSEL", description: "CANB Bit Clock Source Select Bit", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CLKSRCCTL3", description: "Clock Source Control register-3", offset: "0xC",
		bits: [
			{ name: "XCLKOUTSEL", description: "XCLKOUT Source Select Bit", size: "3", shift: "0", mask: "0x7" },
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
			{ name: "IMULT", description: "SYSPLL Integer Multiplier", size: "7", shift: "0", mask: "0x7F" },
			{ name: "FMULT", description: "SYSPLL Fractional Multiplier", size: "2", shift: "8", mask: "0x300" },
		]
	},
	{ name: "SYSPLLSTS", description: "SYSPLL Status register", offset: "0x16",
		bits: [
			{ name: "LOCKS", description: "SYSPLL Lock Status Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SLIPS", description: "SYSPLL Slip Status Bit", size: "1", shift: "1", mask: "0x2" },
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
			{ name: "IMULT", description: "AUXPLL Integer Multiplier", size: "7", shift: "0", mask: "0x7F" },
			{ name: "FMULT", description: "AUXPLL Fractional Multiplier", size: "2", shift: "8", mask: "0x300" },
		]
	},
	{ name: "AUXPLLSTS", description: "AUXPLL Status register", offset: "0x20",
		bits: [
			{ name: "LOCKS", description: "AUXPLL Lock Status Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SLIPS", description: "AUXPLL Slip Status Bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SYSCLKDIVSEL", description: "System Clock Divider Select register", offset: "0x22",
		bits: [
			{ name: "PLLSYSCLKDIV", description: "PLLSYSCLK Divide Select", size: "6", shift: "0", mask: "0x3F" },
		]
	},
	{ name: "AUXCLKDIVSEL", description: "Auxillary Clock Divider Select register", offset: "0x24",
		bits: [
			{ name: "AUXPLLDIV", description: "AUXPLLCLK Divide Select", size: "2", shift: "0", mask: "0x3" },
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
		]
	},
	{ name: "CPUSYSLOCK1", description: "Lock bit for CPUSYS registers", offset: "0x0",
		bits: [
			{ name: "HIBBOOTMODE", description: "Lock bit for HIBBOOTMODE register", size: "1", shift: "0", mask: "0x1" },
			{ name: "IORESTOREADDR", description: "Lock bit for IORESTOREADDR Register", size: "1", shift: "1", mask: "0x2" },
			{ name: "PIEVERRADDR", description: "Lock bit for PIEVERRADDR Register", size: "1", shift: "2", mask: "0x4" },
			{ name: "PCLKCR0", description: "Lock bit for PCLKCR0 Register", size: "1", shift: "3", mask: "0x8" },
			{ name: "PCLKCR1", description: "Lock bit for PCLKCR1 Register", size: "1", shift: "4", mask: "0x10" },
			{ name: "PCLKCR2", description: "Lock bit for PCLKCR2 Register", size: "1", shift: "5", mask: "0x20" },
			{ name: "PCLKCR3", description: "Lock bit for PCLKCR3 Register", size: "1", shift: "6", mask: "0x40" },
			{ name: "PCLKCR4", description: "Lock bit for PCLKCR4 Register", size: "1", shift: "7", mask: "0x80" },
			{ name: "PCLKCR5", description: "Lock bit for PCLKCR5 Register", size: "1", shift: "8", mask: "0x100" },
			{ name: "PCLKCR6", description: "Lock bit for PCLKCR6 Register", size: "1", shift: "9", mask: "0x200" },
			{ name: "PCLKCR7", description: "Lock bit for PCLKCR7 Register", size: "1", shift: "10", mask: "0x400" },
			{ name: "PCLKCR8", description: "Lock bit for PCLKCR8 Register", size: "1", shift: "11", mask: "0x800" },
			{ name: "PCLKCR9", description: "Lock bit for PCLKCR9 Register", size: "1", shift: "12", mask: "0x1000" },
			{ name: "PCLKCR10", description: "Lock bit for PCLKCR10 Register", size: "1", shift: "13", mask: "0x2000" },
			{ name: "PCLKCR11", description: "Lock bit for PCLKCR11 Register", size: "1", shift: "14", mask: "0x4000" },
			{ name: "PCLKCR12", description: "Lock bit for PCLKCR12 Register", size: "1", shift: "15", mask: "0x8000" },
			{ name: "PCLKCR13", description: "Lock bit for PCLKCR13 Register", size: "1", shift: "16", mask: "0x10000" },
			{ name: "PCLKCR14", description: "Lock bit for PCLKCR14 Register", size: "1", shift: "17", mask: "0x20000" },
			{ name: "PCLKCR15", description: "Lock bit for PCLKCR15 Register", size: "1", shift: "18", mask: "0x40000" },
			{ name: "PCLKCR16", description: "Lock bit for PCLKCR16 Register", size: "1", shift: "19", mask: "0x80000" },
			{ name: "SECMSEL", description: "Lock bit for SECMSEL Register", size: "1", shift: "20", mask: "0x100000" },
			{ name: "LPMCR", description: "Lock bit for LPMCR Register", size: "1", shift: "21", mask: "0x200000" },
			{ name: "GPIOLPMSEL0", description: "Lock bit for GPIOLPMSEL0 Register", size: "1", shift: "22", mask: "0x400000" },
			{ name: "GPIOLPMSEL1", description: "Lock bit for GPIOLPMSEL1 Register", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "HIBBOOTMODE", description: "HIB Boot Mode Register", offset: "0x6",
		bits: [
		]
	},
	{ name: "IORESTOREADDR", description: "IORestore() routine Address Register", offset: "0x8",
		bits: [
			{ name: "ADDR", description: "restoreIO() routine address", size: "22", shift: "0", mask: "0x3FFFFF" },
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
			{ name: "HRPWM", description: "HRPWM Clock Enable Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "TBCLKSYNC", description: "EPWM Time Base Clock sync", size: "1", shift: "18", mask: "0x40000" },
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
		]
	},
	{ name: "PCLKCR11", description: "Peripheral Clock Gating Registers", offset: "0x38",
		bits: [
			{ name: "MCBSP_A", description: "McBSP_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "MCBSP_B", description: "McBSP_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "USB_A", description: "USB_A Clock Enable bit", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "PCLKCR12", description: "Peripheral Clock Gating Registers", offset: "0x3A",
		bits: [
			{ name: "UPP_A", description: "uPP_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PCLKCR13", description: "Peripheral Clock Gating Registers", offset: "0x3C",
		bits: [
			{ name: "ADC_A", description: "ADC_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B", description: "ADC_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
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
			{ name: "DAC_A", description: "Buffered_DAC_A Clock Enable Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DAC_B", description: "Buffered_DAC_B Clock Enable Bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DAC_C", description: "Buffered_DAC_C Clock Enable Bit", size: "1", shift: "18", mask: "0x40000" },
		]
	},
	{ name: "SECMSEL", description: "Secondary Master Select register for common", offset: "0x74",
		bits: [
			{ name: "PF1SEL", description: "Secondary Master Select for VBUS32_1 Bridge", size: "2", shift: "0", mask: "0x3" },
			{ name: "PF2SEL", description: "Secondary Master Select for VBUS32_2 Bridge", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "LPMCR", description: "LPM Control Register", offset: "0x76",
		bits: [
			{ name: "LPM", description: "Low Power Mode setting", size: "2", shift: "0", mask: "0x3" },
			{ name: "QUALSTDBY", description: "STANDBY Wakeup Pin Qualification Setting", size: "6", shift: "2", mask: "0xFC" },
			{ name: "WDINTE", description: "Enable for WDINT wakeup from STANDBY", size: "1", shift: "15", mask: "0x8000" },
			{ name: "M0M1MODE", description: "Configuration for M0 and M1 mode during HIB", size: "2", shift: "16", mask: "0x30000" },
			{ name: "IOISODIS", description: "IO Isolation Disable", size: "1", shift: "31", mask: "0x80000000" },
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
	{ name: "TMR2CLKCTL", description: "Timer2 Clock Measurement functionality control register", offset: "0x7C",
		bits: [
			{ name: "TMR2CLKSRCSEL", description: "CPU Timer 2 Clock Source Select Bit", size: "3", shift: "0", mask: "0x7" },
			{ name: "TMR2CLKPRESCALE", description: "CPU Timer 2 Clock Pre-Scale Value", size: "3", shift: "3", mask: "0x38" },
		]
	},
	{ name: "RESC", description: "Reset Cause register", offset: "0x80",
		bits: [
			{ name: "POR", description: "POR Reset Cause Indication Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "XRSN", description: "XRSn Reset Cause Indication Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "WDRSN", description: "WDRSn Reset Cause Indication Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "NMIWDRSN", description: "NMIWDRSn Reset Cause Indication Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "HWBISTN", description: "HWBISTn Reset Cause Indication Bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "HIBRESETN", description: "HIBRESETn Reset Cause Indication Bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "SCCRESETN", description: "SCCRESETn Reset Cause Indication Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "XRSN_PIN_STATUS", description: "XRSN Pin Status", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "TRSTN_PIN_STATUS", description: "TRSTn Status", size: "1", shift: "31", mask: "0x80000000" },
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
			{ name: "WDKEY", description: "WD KEY", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "WDCR", description: "Watchdog Control Register", offset: "0x29",
		bits: [
			{ name: "WDPS", description: "WD Clock Prescalar", size: "3", shift: "0", mask: "0x7" },
			{ name: "WDCHK", description: "WD Check Bits", size: "3", shift: "3", mask: "0x38" },
			{ name: "WDDIS", description: "WD Disable", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "WDWCR", description: "Watchdog Windowed Control Register", offset: "0x2A",
		bits: [
			{ name: "MIN", description: "WD Min Threshold setting for Windowed Watchdog", size: "8", shift: "0", mask: "0xFF" },
			{ name: "FIRSTKEY", description: "First Key Detect Flag", size: "1", shift: "8", mask: "0x100" },
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
	{ name: "SYNCSELECT", description: "Sync Input and Output Select Register", offset: "0x0",
		bits: [
			{ name: "EPWM4SYNCIN", description: "Selects Sync Input Source for EPWM4", size: "3", shift: "0", mask: "0x7" },
			{ name: "EPWM7SYNCIN", description: "Selects Sync Input Source for EPWM7", size: "3", shift: "3", mask: "0x38" },
			{ name: "EPWM10SYNCIN", description: "Selects Sync Input Source for EPWM10", size: "3", shift: "6", mask: "0x1C0" },
			{ name: "ECAP1SYNCIN", description: "Selects Sync Input Source for ECAP1", size: "3", shift: "9", mask: "0xE00" },
			{ name: "ECAP4SYNCIN", description: "Selects Sync Input Source for ECAP4", size: "3", shift: "12", mask: "0x7000" },
			{ name: "SYNCOUT", description: "Select Syncout Source", size: "2", shift: "27", mask: "0x18000000" },
		]
	},
	{ name: "ADCSOCOUTSELECT", description: "External ADC (Off Chip) SOC Select Register", offset: "0x2",
		bits: [
			{ name: "PWM1SOCAEN", description: "PWM1SOCAEN Enable for ADCSOCAO", size: "1", shift: "0", mask: "0x1" },
			{ name: "PWM2SOCAEN", description: "PWM2SOCAEN Enable for ADCSOCAO", size: "1", shift: "1", mask: "0x2" },
			{ name: "PWM3SOCAEN", description: "PWM3SOCAEN Enable for ADCSOCAO", size: "1", shift: "2", mask: "0x4" },
			{ name: "PWM4SOCAEN", description: "PWM4SOCAEN Enable for ADCSOCAO", size: "1", shift: "3", mask: "0x8" },
			{ name: "PWM5SOCAEN", description: "PWM5SOCAEN Enable for ADCSOCAO", size: "1", shift: "4", mask: "0x10" },
			{ name: "PWM6SOCAEN", description: "PWM6SOCAEN Enable for ADCSOCAO", size: "1", shift: "5", mask: "0x20" },
			{ name: "PWM7SOCAEN", description: "PWM7SOCAEN Enable for ADCSOCAO", size: "1", shift: "6", mask: "0x40" },
			{ name: "PWM8SOCAEN", description: "PWM8SOCAEN Enable for ADCSOCAO", size: "1", shift: "7", mask: "0x80" },
			{ name: "PWM9SOCAEN", description: "PWM9SOCAEN Enable for ADCSOCAO", size: "1", shift: "8", mask: "0x100" },
			{ name: "PWM10SOCAEN", description: "PWM10SOCAEN Enable for ADCSOCAO", size: "1", shift: "9", mask: "0x200" },
			{ name: "PWM11SOCAEN", description: "PWM11SOCAEN Enable for ADCSOCAO", size: "1", shift: "10", mask: "0x400" },
			{ name: "PWM12SOCAEN", description: "PWM12SOCAEN Enable for ADCSOCAO", size: "1", shift: "11", mask: "0x800" },
			{ name: "PWM1SOCBEN", description: "PWM1SOCBEN Enable for ADCSOCBO", size: "1", shift: "16", mask: "0x10000" },
			{ name: "PWM2SOCBEN", description: "PWM2SOCBEN Enable for ADCSOCBO", size: "1", shift: "17", mask: "0x20000" },
			{ name: "PWM3SOCBEN", description: "PWM3SOCBEN Enable for ADCSOCBO", size: "1", shift: "18", mask: "0x40000" },
			{ name: "PWM4SOCBEN", description: "PWM4SOCBEN Enable for ADCSOCBO", size: "1", shift: "19", mask: "0x80000" },
			{ name: "PWM5SOCBEN", description: "PWM5SOCBEN Enable for ADCSOCBO", size: "1", shift: "20", mask: "0x100000" },
			{ name: "PWM6SOCBEN", description: "PWM6SOCBEN Enable for ADCSOCBO", size: "1", shift: "21", mask: "0x200000" },
			{ name: "PWM7SOCBEN", description: "PWM7SOCBEN Enable for ADCSOCBO", size: "1", shift: "22", mask: "0x400000" },
			{ name: "PWM8SOCBEN", description: "PWM8SOCBEN Enable for ADCSOCBO", size: "1", shift: "23", mask: "0x800000" },
			{ name: "PWM9SOCBEN", description: "PWM9SOCBEN Enable for ADCSOCBO", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "PWM10SOCBEN", description: "PWM10SOCBEN Enable for ADCSOCBO", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "PWM11SOCBEN", description: "PWM11SOCBEN Enable for ADCSOCBO", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "PWM12SOCBEN", description: "PWM12SOCBEN Enable for ADCSOCBO", size: "1", shift: "27", mask: "0x8000000" },
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
