let SYSCTLRegisters = [
	{ name: "PARTIDL", description: "Lower 32-bit of Device PART Identification Number", offset: "0x8",
		bits: [
			{ name: "QUAL", description: "Qualification Status", size: "2", shift: "6", mask: "0xC0" },
			{ name: "PIN_COUNT", description: "Device Pin Count", size: "3", shift: "8", mask: "0x700" },
			{ name: "INSTASPIN", description: "Instaspin feature set", size: "2", shift: "13", mask: "0x6000" },
			{ name: "FLASH_SIZE", description: "FLASH_SIZE", size: "8", shift: "16", mask: "0xFF0000" },
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
			{ name: "REVID", description: "Device Revision ID. This is specific to the Device", size: "8", shift: "0", mask: "0xFF" },
			{ name: "REVID_EXT", description: "Device Revision ID Extension", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "TRIMERRSTS", description: "TRIM Error Status register", offset: "0x74",
		bits: [
			{ name: "LERR", description: "TRIM Load error status", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "SOFTPRES0", description: "Processing Block Software Reset register", offset: "0x82",
		bits: [
			{ name: "CPU1_CLA1", description: "CPU1_CLA1 software reset bit", size: "1", shift: "0", mask: "0x1" },
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
			{ name: "EPWM9", description: "EPWM9 software reset bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "EPWM10", description: "EPWM10 software reset bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "EPWM11", description: "EPWM11 software reset bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPWM12", description: "EPWM12 software reset bit", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "SOFTPRES3", description: "ECAP Software Reset register", offset: "0x88",
		bits: [
			{ name: "ECAP1", description: "ECAP1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ECAP2", description: "ECAP2 software reset bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SOFTPRES4", description: "EQEP Software Reset register", offset: "0x8A",
		bits: [
			{ name: "EQEP1", description: "EQEP1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EQEP2", description: "EQEP2 software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "EQEP3", description: "EQEP3 software reset bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "SOFTPRES7", description: "SCI Software Reset register", offset: "0x90",
		bits: [
			{ name: "SCI_A", description: "SCI_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SCI_B", description: "SCI_B software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SCI_C", description: "SCI_C software reset bit", size: "1", shift: "2", mask: "0x4" },
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
			{ name: "MCAN_A", description: "MCAN_A  software reset bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "MCAN_B", description: "MCAN_B  software reset bit", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "SOFTPRES11", description: "McBSP/USB Software Reset register", offset: "0x98",
		bits: [
			{ name: "USB_A", description: "USB_A software reset bit", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "SOFTPRES13", description: "ADC Software Reset register", offset: "0x9C",
		bits: [
			{ name: "ADC_A", description: "ADC_A software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B", description: "ADC_B software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADC_C", description: "ADC_C software reset bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADC_D", description: "ADC_D software reset bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "ADC_E", description: "ADC_E software reset bit", size: "1", shift: "4", mask: "0x10" },
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
	{ name: "SOFTPRES15", description: "PGA Software Reset register", offset: "0xA0",
		bits: [
			{ name: "PGA1", description: "PGA1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "PGA2", description: "PGA2 software reset bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "PGA3", description: "PGA3 software reset bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "SOFTPRES16", description: "DAC Software Reset register", offset: "0xA2",
		bits: [
			{ name: "DAC_A", description: "Buffered_DAC_A software reset bit", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "SOFTPRES17", description: "CLB Software Reset register", offset: "0xA4",
		bits: [
			{ name: "CLB1", description: "CLB1 software reset bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLB2", description: "CLB2 software reset bit", size: "1", shift: "1", mask: "0x2" },
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
	{ name: "SOFTPRES28", description: "Flash Software Reset register", offset: "0xBA",
		bits: [
			{ name: "FLASHA", description: "Flash Wrapper Module Reset Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "SOFTPRES30", description: "NPU Software reset register", offset: "0xBE",
		bits: [
			{ name: "NPU", description: "NPU Module Reset Bit", size: "1", shift: "0", mask: "0x1" },
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
	{ name: "TAP_CONTROL", description: "Disable TAP control", offset: "0x132",
		bits: [
			{ name: "BSCAN_DIS", description: "Disable BSCAN TAP control", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Key value to enable write", size: "16", shift: "16", mask: "0xFFFF0000" },
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
			{ name: "LOCK", description: "Lock bit for the register", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "MCUCNF3", description: "MCU Configuration: ETPWM", offset: "0x1A6",
		bits: [
			{ name: "EPWM1", description: "EPWM1 Present", size: "1", shift: "0", mask: "0x1" },
			{ name: "EPWM2", description: "EPWM2 Present", size: "1", shift: "1", mask: "0x2" },
			{ name: "EPWM3", description: "EPWM3 Present", size: "1", shift: "2", mask: "0x4" },
			{ name: "EPWM4", description: "EPWM4 Present", size: "1", shift: "3", mask: "0x8" },
			{ name: "EPWM5", description: "EPWM5 Present", size: "1", shift: "4", mask: "0x10" },
			{ name: "EPWM6", description: "EPWM6 Present", size: "1", shift: "5", mask: "0x20" },
			{ name: "EPWM7", description: "EPWM7 Present", size: "1", shift: "6", mask: "0x40" },
			{ name: "EPWM8", description: "EPWM8 Present", size: "1", shift: "7", mask: "0x80" },
			{ name: "EPWM9", description: "EPWM9  Present", size: "1", shift: "8", mask: "0x100" },
			{ name: "EPWM10", description: "EPWM10  Present", size: "1", shift: "9", mask: "0x200" },
			{ name: "EPWM11", description: "EPWM11  Present", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPWM12", description: "EPWM12  Present", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "MCUCNF8", description: "MCU Configuration: SCI", offset: "0x1B0",
		bits: [
			{ name: "SCI_A", description: "SCI_A  Present", size: "1", shift: "0", mask: "0x1" },
			{ name: "SCI_B", description: "SCI_B  Present", size: "1", shift: "1", mask: "0x2" },
			{ name: "SCI_C", description: "SCI_C  Present", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MCUCNF11", description: "MCU Configuration: CAN", offset: "0x1B6",
		bits: [
			{ name: "MCAN_A", description: "MCAN_A  Present", size: "1", shift: "4", mask: "0x10" },
			{ name: "MCAN_B", description: "MCAN_B  Present", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "MCUCNF12", description: "MCU Configuration: McBSP_USB", offset: "0x1B8",
		bits: [
			{ name: "USB_A", description: "Decides the capability of the USB_A Module", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "MCUCNF14", description: "MCU Configuration: ADC", offset: "0x1BC",
		bits: [
			{ name: "ADC_A", description: "ADC_A Present", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B", description: "ADC_B Present", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADC_C", description: "ADC_C Present", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADC_D", description: "ADC_D Present", size: "1", shift: "3", mask: "0x8" },
			{ name: "ADC_E", description: "ADC_E Present", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "MCUCNF16", description: "MCU Configuration: PGA", offset: "0x1C0",
		bits: [
			{ name: "PGA1", description: "PGA1  Present", size: "1", shift: "0", mask: "0x1" },
			{ name: "PGA2", description: "PGA2 Present", size: "1", shift: "1", mask: "0x2" },
			{ name: "PGA3", description: "PGA3 Present", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MCUCNF18", description: "MCU Configuration: Lx.1 SRAM Customization", offset: "0x1C4",
		bits: [
			{ name: "LS0_1", description: "LS0_1 Present", size: "1", shift: "0", mask: "0x1" },
			{ name: "LS1_1", description: "LS1_1  Present", size: "1", shift: "1", mask: "0x2" },
			{ name: "LS2_1", description: "LS2_1  Present", size: "1", shift: "2", mask: "0x4" },
			{ name: "LS3_1", description: "LS3_1  Present", size: "1", shift: "3", mask: "0x8" },
			{ name: "LS4_1", description: "LS4_1  Present", size: "1", shift: "4", mask: "0x10" },
			{ name: "LS5_1", description: "LS5_1  Present", size: "1", shift: "5", mask: "0x20" },
			{ name: "LS6_1", description: "LS6_1 Present", size: "1", shift: "6", mask: "0x40" },
			{ name: "LS7_1", description: "LS7_1 Present", size: "1", shift: "7", mask: "0x80" },
			{ name: "LS8_1", description: "LS8_1 Present", size: "1", shift: "8", mask: "0x100" },
			{ name: "LS9_1", description: "LS9_1 Present", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "MCUCNF20", description: "MCU Configuration: GSx SRAM Customization", offset: "0x1C8",
		bits: [
			{ name: "GS0", description: "GS0  Present", size: "1", shift: "0", mask: "0x1" },
			{ name: "GS1", description: "GS1  Present", size: "1", shift: "1", mask: "0x2" },
			{ name: "GS2", description: "GS2  Present", size: "1", shift: "2", mask: "0x4" },
			{ name: "GS3", description: "GS3  Present", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "MCUCNF21", description: "MCU Configuration: CLB", offset: "0x1CA",
		bits: [
			{ name: "CLB1", description: "CLB1 Present", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLB2", description: "CLB2 Present", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "MCUCNF23", description: "MCU Configuration: LIN", offset: "0x1CE",
		bits: [
			{ name: "LIN_A", description: "LIN_A  Present", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "MCUCNF31", description: "MCU Configuration: Flash Bank0", offset: "0x1DE",
		bits: [
			{ name: "SECT15_0", description: "Flash sectors 15_0 present", size: "1", shift: "0", mask: "0x1" },
			{ name: "SECT31_16", description: "Flash sectors 31_16 present", size: "1", shift: "1", mask: "0x2" },
			{ name: "SECT47_32", description: "Flash sectors 47_32 present", size: "1", shift: "2", mask: "0x4" },
			{ name: "SECT63_48", description: "Flash sectors 63_48 present", size: "1", shift: "3", mask: "0x8" },
			{ name: "SECT79_64", description: "Flash sectors 79_64 present", size: "1", shift: "4", mask: "0x10" },
			{ name: "SECT95_80", description: "Flash sectors 95_80 present", size: "1", shift: "5", mask: "0x20" },
			{ name: "SECT111_96", description: "Flash sectors 111_96 present", size: "1", shift: "6", mask: "0x40" },
			{ name: "SECT127_112", description: "Flash sectors 127_112 present", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MCUCNF32", description: "MCU Configuration: Flash Bank1", offset: "0x1E0",
		bits: [
			{ name: "SECT15_0", description: "Flash sectors 15_0 present", size: "1", shift: "0", mask: "0x1" },
			{ name: "SECT31_16", description: "Flash sectors 31_16 present", size: "1", shift: "1", mask: "0x2" },
			{ name: "SECT47_32", description: "Flash sectors 47_32 present", size: "1", shift: "2", mask: "0x4" },
			{ name: "SECT63_48", description: "Flash sectors 63_48 present", size: "1", shift: "3", mask: "0x8" },
			{ name: "SECT79_64", description: "Flash sectors 79_64 present", size: "1", shift: "4", mask: "0x10" },
			{ name: "SECT95_80", description: "Flash sectors 95_80 present", size: "1", shift: "5", mask: "0x20" },
			{ name: "SECT111_96", description: "Flash sectors 111_96 present", size: "1", shift: "6", mask: "0x40" },
			{ name: "SECT127_112", description: "Flash sectors 127_112 present", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MCUCNF33", description: "MCU Configuration: Flash Bank2", offset: "0x1E2",
		bits: [
			{ name: "SECT15_0", description: "Flash sectors 15_0 present", size: "1", shift: "0", mask: "0x1" },
			{ name: "SECT31_16", description: "Flash sectors 31_16 present", size: "1", shift: "1", mask: "0x2" },
			{ name: "SECT47_32", description: "Flash sectors 47_32 present", size: "1", shift: "2", mask: "0x4" },
			{ name: "SECT63_48", description: "Flash sectors 63_48 present", size: "1", shift: "3", mask: "0x8" },
			{ name: "SECT79_64", description: "Flash sectors 79_64 present", size: "1", shift: "4", mask: "0x10" },
			{ name: "SECT95_80", description: "Flash sectors 95_80 present", size: "1", shift: "5", mask: "0x20" },
			{ name: "SECT111_96", description: "Flash sectors 111_96 present", size: "1", shift: "6", mask: "0x40" },
			{ name: "SECT127_112", description: "Flash sectors 127_112 present", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MCUCNF34", description: "MCU Configuration: Flash Bank3", offset: "0x1E4",
		bits: [
			{ name: "SECT15_0", description: "Flash sectors 15_0 present", size: "1", shift: "0", mask: "0x1" },
			{ name: "SECT31_16", description: "Flash sectors 31_16 present", size: "1", shift: "1", mask: "0x2" },
			{ name: "SECT47_32", description: "Flash sectors 47_32 present", size: "1", shift: "2", mask: "0x4" },
			{ name: "SECT63_48", description: "Flash sectors 63_48 present", size: "1", shift: "3", mask: "0x8" },
			{ name: "SECT79_64", description: "Flash sectors 79_64 present", size: "1", shift: "4", mask: "0x10" },
			{ name: "SECT95_80", description: "Flash sectors 95_80 present", size: "1", shift: "5", mask: "0x20" },
			{ name: "SECT111_96", description: "Flash sectors 111_96 present", size: "1", shift: "6", mask: "0x40" },
			{ name: "SECT127_112", description: "Flash sectors 127_112 present", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MCUCNF35", description: "MCU Configuration: Flash Bank4", offset: "0x1E6",
		bits: [
			{ name: "SECT15_0", description: "Flash sectors 15_0 present", size: "1", shift: "0", mask: "0x1" },
			{ name: "SECT31_16", description: "Flash sectors 31_16 present", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "MCUCNFLOCK", description: "Lock bit for MCUCNFx registers", offset: "0x1F8",
		bits: [
			{ name: "MCUCNFLOCK", description: "Lock bit for MCUCNF registers", size: "1", shift: "0", mask: "0x1" },
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
			{ name: "PERCLKDIVSEL", description: "Lock bit for PERCLKDIVSEL register", size: "1", shift: "13", mask: "0x2000" },
			{ name: "CLBCLKCTL", description: "Lock bit for CLBCLKCTL register", size: "1", shift: "14", mask: "0x4000" },
			{ name: "LOSPCP", description: "Lock bit for LOSPCP register", size: "1", shift: "15", mask: "0x8000" },
			{ name: "XTALCR", description: "Lock bit for XTALCR  & XTALCR2 register", size: "1", shift: "16", mask: "0x10000" },
			{ name: "EXTRFLTDET", description: "Lockbit for EXTRFLTDET register", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "CLKSRCCTL1", description: "Clock Source Control register-1", offset: "0x8",
		bits: [
			{ name: "OSCCLKSRCSEL", description: "OSCCLK Source Select Bit", size: "2", shift: "0", mask: "0x3" },
			{ name: "WDHALTI", description: "Watchdog HALT Mode Ignore Bit", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "CLKSRCCTL2", description: "Clock Source Control register-2", offset: "0xA",
		bits: [
			{ name: "MCANABCLKSEL", description: "MCANA Bit Clock Source Select Bit", size: "2", shift: "10", mask: "0xC00" },
			{ name: "MCANBBCLKSEL", description: "MCANB Bit Clock Source Select Bit", size: "2", shift: "12", mask: "0x3000" },
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
			{ name: "REF_LOSTS", description: "SYSPLL Reference  Lost Status Bit", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "SYSCLKDIVSEL", description: "System Clock Divider Select register", offset: "0x22",
		bits: [
			{ name: "PLLSYSCLKDIV", description: "PLLSYSCLK Divide Select", size: "6", shift: "0", mask: "0x3F" },
			{ name: "PLLSYSCLKDIV_LSB", description: "Reserved", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "AUXCLKDIVSEL", description: "Auxillary Clock Divider Select register", offset: "0x24",
		bits: [
			{ name: "MCANACLKDIV", description: "Divider between MCANA Source Clock and", size: "5", shift: "8", mask: "0x1F00" },
			{ name: "MCANBCLKDIV", description: "Divider between MCANB Source Clock and", size: "5", shift: "13", mask: "0x3E000" },
		]
	},
	{ name: "PERCLKDIVSEL", description: "Peripheral Clock Divider Select register", offset: "0x26",
		bits: [
			{ name: "USBCLKDIV", description: "USB Clock Divide select", size: "3", shift: "7", mask: "0x380" },
			{ name: "LINACLKDIV", description: "LINA Clock Divide Select", size: "6", shift: "10", mask: "0xFC00" },
			{ name: "NPUCLKDIV", description: "NPU Clock Divide Select", size: "1", shift: "16", mask: "0x10000" },
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
			{ name: "PCLKCR26", description: "Lock bit for PCLKCR26 Register", size: "1", shift: "2", mask: "0x4" },
			{ name: "PCLKCR27", description: "Lock bit for PCLKCR27 Register", size: "1", shift: "3", mask: "0x8" },
			{ name: "LSEN", description: "Lock bit for LSEN Register", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMPSSLPMSEL", description: "Lock bit for CMPSSLPMSEL register", size: "1", shift: "5", mask: "0x20" },
			{ name: "USER_REG1_SYSRSN", description: "Lock bit for USER_REG1_SYSRSn", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "USER_REG2_SYSRSN", description: "Lock bit for USER_REG2_SYSRSn", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "USER_REG1_XRSN", description: "Lock bit for USER_REG1_XRSn", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "USER_REG2_XRSN", description: "Lock bit for USER_REG2_XRSn", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "USER_REG1_PORESETN", description: "Lock bit for USER_REG1_PORESETn", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "USER_REG2_PORESETN", description: "Lock bit for USER_REG2_PORESETn", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "USER_REG3_PORESETN", description: "Lock bit for USER_REG3_PORESETn", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "USER_REG4_PORESETN", description: "Lock bit for USER_REG4_PORESETn", size: "1", shift: "31", mask: "0x80000000" },
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
			{ name: "EPWM9", description: "EPWM9 Clock Enable bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "EPWM10", description: "EPWM10 Clock Enable bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "EPWM11", description: "EPWM11 Clock Enable bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPWM12", description: "EPWM12 Clock Enable bit", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "PCLKCR3", description: "Peripheral Clock Gating Register - ECAP", offset: "0x28",
		bits: [
			{ name: "ECAP1", description: "ECAP1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ECAP2", description: "ECAP2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PCLKCR4", description: "Peripheral Clock Gating Register - EQEP", offset: "0x2A",
		bits: [
			{ name: "EQEP1", description: "EQEP1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EQEP2", description: "EQEP2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "EQEP3", description: "EQEP3 Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "PCLKCR7", description: "Peripheral Clock Gating Register - SCI", offset: "0x30",
		bits: [
			{ name: "SCI_A", description: "SCI_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SCI_B", description: "SCI_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SCI_C", description: "SCI_C Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
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
			{ name: "MCAN_A", description: "MCAN_A Clock Enable bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "MCAN_B", description: "MCAN_B Clock Enable bit", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "PCLKCR11", description: "Peripheral Clock Gating Register - McBSP_USB", offset: "0x38",
		bits: [
			{ name: "USB_A", description: "USB_A Clock Enable bit", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "PCLKCR12", description: "Peripheral Clock Gating Register - Upp", offset: "0x3A",
		bits: [
			{ name: "NPU", description: "NPU Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PCLKCR13", description: "Peripheral Clock Gating Register - ADC", offset: "0x3C",
		bits: [
			{ name: "ADC_A", description: "ADC_A Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADC_B", description: "ADC_B Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADC_C", description: "ADC_C Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADC_D", description: "ADC_D Clock Enable bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "ADC_E", description: "ADC_E Clock Enable bit", size: "1", shift: "4", mask: "0x10" },
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
	{ name: "PCLKCR15", description: "Peripheral Clock Gating Register - PGA", offset: "0x40",
		bits: [
			{ name: "PGA1", description: "PGA1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "PGA2", description: "PGA2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "PGA3", description: "PGA3 Clock Enable bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "PCLKCR16", description: "Peripheral Clock Gating Register Buf_DAC", offset: "0x42",
		bits: [
			{ name: "DAC_A", description: "Buffered_DAC_A Clock Enable Bit", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "PCLKCR17", description: "Peripheral Clock Gating Register - CLB", offset: "0x44",
		bits: [
			{ name: "CLB1", description: "CLB1 Clock Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLB2", description: "CLB2 Clock Enable bit", size: "1", shift: "1", mask: "0x2" },
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
			{ name: "SCCRESETN", description: "SCCRESETn Reset Cause Indication Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "SIMRESET_CPU1RSN", description: "SIMRESET_CPU1RSn Reset Cause Indication Bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "SIMRESET_XRSN", description: "SIMRESET_XRSn Reset Cause Indication Bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "XRSN_PIN_STATUS", description: "XRSN Pin Status", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "DCON", description: "Debugger conntion status to C28x", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "CMPSSLPMSEL", description: "CMPSS LPM Wakeup select registers", offset: "0x84",
		bits: [
			{ name: "CMPSS1H", description: "CMPSS1H Enable for LPM Wakeup", size: "1", shift: "0", mask: "0x1" },
			{ name: "CMPSS1L", description: "CMPSS1L Enable for LPM Wakeup", size: "1", shift: "1", mask: "0x2" },
			{ name: "CMPSS2H", description: "CMPSS2H Enable for LPM Wakeup", size: "1", shift: "2", mask: "0x4" },
			{ name: "CMPSS2L", description: "CMPSS2L Enable for LPM Wakeup", size: "1", shift: "3", mask: "0x8" },
			{ name: "CMPSS3H", description: "CMPSS3H Enable for LPM Wakeup", size: "1", shift: "4", mask: "0x10" },
			{ name: "CMPSS3L", description: "CMPSS3L Enable for LPM Wakeup", size: "1", shift: "5", mask: "0x20" },
			{ name: "CMPSS4H", description: "CMPSS4H Enable for LPM Wakeup", size: "1", shift: "6", mask: "0x40" },
			{ name: "CMPSS4L", description: "CMPSS4L Enable for LPM Wakeup", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MCANRAMACC", description: "MCAN RAM access control Register", offset: "0x90",
		bits: [
			{ name: "MCAN_A_RAMACC", description: "MCAN_A_RAMACC Message RAM access control Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "MCAN_B_RAMACC", description: "MCAN_B_RAMACC Message RAM access control Bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "MCANWAKESTATUS", description: "MCAN Wake Status Register", offset: "0x98",
		bits: [
			{ name: "WAKE_MCANA", description: "MCANA Wake Status", size: "1", shift: "0", mask: "0x1" },
			{ name: "WAKE_MCANB", description: "MCANB Wake Status", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "MCANWAKESTATUSCLR", description: "MCAN Wake Status Clear Register", offset: "0x9A",
		bits: [
			{ name: "WAKE_MCANA", description: "Cear bit for MCANWAKESTATUS.WAKE_MCANA bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "WAKE_MCANB", description: "Cear bit for MCANWAKESTATUS.WAKE_MCANB bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CLKSTOPREQ", description: "Peripheral Clock Stop Request Register", offset: "0x9C",
		bits: [
			{ name: "MCAN_A", description: "MCAN_A Clock Stop Request Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "MCAN_B", description: "MCAN_B Clock Stop Request Bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "KEY", description: "Key for register write", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "CLKSTOPACK", description: "Peripheral Clock Stop Ackonwledge Register", offset: "0x9E",
		bits: [
			{ name: "MCAN_A", description: "MCAN_A Clock Stop Ack Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "MCAN_B", description: "MCAN_B Clock Stop Ack Bit", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "USER_REG1_SYSRSN", description: "Software Configurable registers reset by SYSRSn", offset: "0xA0",
		bits: [
		]
	},
	{ name: "USER_REG2_SYSRSN", description: "Software Configurable registers reset by SYSRSn", offset: "0xA2",
		bits: [
		]
	},
	{ name: "USER_REG1_XRSN", description: "Software Configurable registers reset by XRSn", offset: "0xA4",
		bits: [
		]
	},
	{ name: "USER_REG2_XRSN", description: "Software Configurable registers reset by XRSn", offset: "0xA6",
		bits: [
		]
	},
	{ name: "USER_REG1_PORESETN", description: "Software Configurable registers reset by PORESETn", offset: "0xA8",
		bits: [
		]
	},
	{ name: "USER_REG2_PORESETN", description: "Software Configurable registers reset by PORESETn", offset: "0xAA",
		bits: [
		]
	},
	{ name: "USER_REG3_PORESETN", description: "Software Configurable registers reset by PORESETn", offset: "0xAC",
		bits: [
		]
	},
	{ name: "USER_REG4_PORESETN", description: "Software Configurable registers reset by PORESETn", offset: "0xAE",
		bits: [
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
	{ name: "ADCA_AC", description: "ADCA Controller Access Control Register", offset: "0x0",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "ADCB_AC", description: "ADCB Controller Access Control Register", offset: "0x2",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "ADCC_AC", description: "ADCC Controller Access Control Register", offset: "0x4",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "ADCD_AC", description: "ADCD Controller Access Control Register", offset: "0x6",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "ADCE_AC", description: "ADCE Controller Access Control Register", offset: "0x8",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "CMPSS1_AC", description: "CMPSS1 Controller Access Control Register", offset: "0x10",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CMPSS2_AC", description: "CMPSS2 Controller Access Control Register", offset: "0x12",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CMPSS3_AC", description: "CMPSS3 Controller Access Control Register", offset: "0x14",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CMPSS4_AC", description: "CMPSS4 Controller Access Control Register", offset: "0x16",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "DACA_AC", description: "DACA Controller Access Control Register", offset: "0x28",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "PGA1_AC", description: "PGAA Controller Access Control Register", offset: "0x38",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "PGA2_AC", description: "PGAB Controller Access Control Register", offset: "0x3A",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "PGA3_AC", description: "PGAC Controller Access Control Register", offset: "0x3C",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM1_AC", description: "EPWM1 Controller Access Control Register", offset: "0x48",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM2_AC", description: "EPWM2 Controller Access Control Register", offset: "0x4A",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM3_AC", description: "EPWM3 Controller Access Control Register", offset: "0x4C",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM4_AC", description: "EPWM4 Controller Access Control Register", offset: "0x4E",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM5_AC", description: "EPWM5 Controller Access Control Register", offset: "0x50",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM6_AC", description: "EPWM6 Controller Access Control Register", offset: "0x52",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM7_AC", description: "EPWM7 Controller Access Control Register", offset: "0x54",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM8_AC", description: "EPWM8 Controller Access Control Register", offset: "0x56",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM9_AC", description: "EPWM9 Controller Access Control Register", offset: "0x58",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM10_AC", description: "EPWM10 Controller Access Control Register", offset: "0x5A",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM11_AC", description: "EPWM11 Controller Access Control Register", offset: "0x5C",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EPWM12_AC", description: "EPWM12 Controller Access Control Register", offset: "0x5E",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EQEP1_AC", description: "EQEP1 Controller Access Control Register", offset: "0x70",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EQEP2_AC", description: "EQEP2 Controller Access Control Register", offset: "0x72",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "EQEP3_AC", description: "EQEP3 Controller Access Control Register", offset: "0x74",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ECAP1_AC", description: "ECAP1 Controller Access Control Register", offset: "0x80",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ECAP2_AC", description: "ECAP2 Controller Access Control Register", offset: "0x82",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "CLB1_AC", description: "CLB1 Controller Access Control Register", offset: "0xB0",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "CLB2_AC", description: "CLB2 Controller Access Control Register", offset: "0xB2",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "SCIA_AC", description: "SCIA Controller Access Control Register", offset: "0x100",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "SCIB_AC", description: "SCIB Controller Access Control Register", offset: "0x102",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "SCIC_AC", description: "SCIC Controller Access Control Register", offset: "0x104",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "SPIA_AC", description: "SPIA Controller Access Control Register", offset: "0x110",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "SPIB_AC", description: "SPIB Controller Access Control Register", offset: "0x112",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "I2CA_AC", description: "I2CA Controller Access Control Register", offset: "0x120",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "I2CB_AC", description: "I2CB Controller Access Control Register", offset: "0x122",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "PMBUS_A_AC", description: "PMBUSA Controller Access Control Register", offset: "0x130",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "LIN_A_AC", description: "LINA Controller Access Control Register", offset: "0x138",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "MCANA_AC", description: "MCANA Controller Access Control Register", offset: "0x148",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "MCANB_AC", description: "MCANB Controller Access Control Register", offset: "0x14A",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSIATX_AC", description: "FSIA Controller Access Control Register", offset: "0x158",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FSIARX_AC", description: "FSIB Controller Access Control Register", offset: "0x15A",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "USBA_AC", description: "USBA Controller Access Control Register", offset: "0x182",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "HRPWM_A_AC", description: "HRPWM Controller Access Control Register", offset: "0x1AA",
		bits: [
			{ name: "CPU1_ACC", description: "CPU1 Access conditions to peripheral", size: "2", shift: "0", mask: "0x3" },
			{ name: "CLA1_ACC", description: "CLA1 Access Conditions to Peripheral", size: "2", shift: "2", mask: "0xC" },
			{ name: "DMA1_ACC", description: "DMA1 Access Conditions to Peripheral", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "AESA_AC", description: "AES Controller Access Control Register", offset: "0x1AE",
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
			{ name: "PWM9SOCAEN", description: "PWM9SOCAEN Enable for ADCSOCAOn", size: "1", shift: "8", mask: "0x100" },
			{ name: "PWM10SOCAEN", description: "PWM10SOCAEN Enable for ADCSOCAOn", size: "1", shift: "9", mask: "0x200" },
			{ name: "PWM11SOCAEN", description: "PWM11SOCAEN Enable for ADCSOCAOn", size: "1", shift: "10", mask: "0x400" },
			{ name: "PWM12SOCAEN", description: "PWM12SOCAEN Enable for ADCSOCAOn", size: "1", shift: "11", mask: "0x800" },
			{ name: "PWM1SOCBEN", description: "PWM1SOCBEN Enable for ADCSOCBOn", size: "1", shift: "16", mask: "0x10000" },
			{ name: "PWM2SOCBEN", description: "PWM2SOCBEN Enable for ADCSOCBOn", size: "1", shift: "17", mask: "0x20000" },
			{ name: "PWM3SOCBEN", description: "PWM3SOCBEN Enable for ADCSOCBOn", size: "1", shift: "18", mask: "0x40000" },
			{ name: "PWM4SOCBEN", description: "PWM4SOCBEN Enable for ADCSOCBOn", size: "1", shift: "19", mask: "0x80000" },
			{ name: "PWM5SOCBEN", description: "PWM5SOCBEN Enable for ADCSOCBOn", size: "1", shift: "20", mask: "0x100000" },
			{ name: "PWM6SOCBEN", description: "PWM6SOCBEN Enable for ADCSOCBOn", size: "1", shift: "21", mask: "0x200000" },
			{ name: "PWM7SOCBEN", description: "PWM7SOCBEN Enable for ADCSOCBOn", size: "1", shift: "22", mask: "0x400000" },
			{ name: "PWM8SOCBEN", description: "PWM8SOCBEN Enable for ADCSOCBOn", size: "1", shift: "23", mask: "0x800000" },
			{ name: "PWM9SOCBEN", description: "PWM9SOCBEN Enable for ADCSOCBOn", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "PWM10SOBAEN", description: "PWM10SOBAEN Enable for ADCSOCBOn", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "PWM11SOBAEN", description: "PWM11SOBAEN Enable for ADCSOCBOn", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "PWM12SOBAEN", description: "PWM12SOBAEN Enable for ADCSOCBOn", size: "1", shift: "27", mask: "0x8000000" },
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
			{ name: "LS01SWAP", description: "Swap LS0 and LS1 memory", size: "1", shift: "20", mask: "0x100000" },
		]
	},
	{ name: "LFUSTATUS", description: "LFU Configuration Status Register", offset: "0x2",
		bits: [
			{ name: "PIEVECTORSWAP", description: "Indicate the status of PieVectorSwap", size: "1", shift: "12", mask: "0x1000" },
			{ name: "LS01SWAP", description: "Indicate the status of LS0/LS1 memory swap", size: "1", shift: "20", mask: "0x100000" },
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
			{ name: "CORRECTABLE_ERR", description: "RAM/Flash correctable error flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "RAM_ACC_VIOL", description: "A RAM access vioation flag.", size: "1", shift: "4", mask: "0x10" },
			{ name: "AES_BUS_ERROR", description: "AES_BUS_ERROR Interrupt flag.", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPG1_INT", description: "EPG1_INT Interrupt flag.", size: "1", shift: "11", mask: "0x800" },
			{ name: "FPU_UFLOW", description: "FPU_UFLOW Interrupt flag.", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FPU_OFLOW", description: "FPU_OFLOW Interrupt flag.", size: "1", shift: "17", mask: "0x20000" },
			{ name: "CLA_UFLOW", description: "CLA_UFLOW Interrupt flag.", size: "1", shift: "18", mask: "0x40000" },
			{ name: "CLA_OFLOW", description: "CLA_OFLOW Interrupt flag.", size: "1", shift: "19", mask: "0x80000" },
		]
	},
	{ name: "SYS_ERR_INT_CLR", description: "SYS_ERR_INT_FLG clear register", offset: "0x12",
		bits: [
			{ name: "GINT", description: "Global Interrupt flag Clear bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CORRECTABLE_ERR", description: "CORRECTABLE_ERR interrupt flag clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "RAM_ACC_VIOL", description: "RAM_ACC_VIOL interrupt flag clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "AES_BUS_ERROR", description: "AES_BUS_ERROR interrupt flag clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPG1_INT", description: "EPG1_INT interrupt flag clear bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "FPU_UFLOW", description: "FPU_UFLOW interrupt flag clear bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FPU_OFLOW", description: "FPU_OFLOW interrupt flag clear bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "CLA_UFLOW", description: "CLA_UFLOW interrupt flag clear bit", size: "1", shift: "18", mask: "0x40000" },
			{ name: "CLA_OFLOW", description: "CLA_OFLOW interrupt flag clear bit", size: "1", shift: "19", mask: "0x80000" },
		]
	},
	{ name: "SYS_ERR_INT_SET", description: "SYS_ERR_INT_FLG set register", offset: "0x14",
		bits: [
			{ name: "CORRECTABLE_ERR", description: "CORRECTABLE_ERR interrupt flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "RAM_ACC_VIOL", description: "RAM_ACC_VIOL interrupt flag set", size: "1", shift: "4", mask: "0x10" },
			{ name: "AES_BUS_ERROR", description: "AES_BUS_ERROR interrupt flag set", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPG1_INT", description: "EPG1_INT interrupt flag set bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "FPU_UFLOW", description: "FPU_UFLOW interrupt flag set bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FPU_OFLOW", description: "FPU_OFLOW interrupt flag set bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "CLA_UFLOW", description: "CLA_UFLOW interrupt flag set bit", size: "1", shift: "18", mask: "0x40000" },
			{ name: "CLA_OFLOW", description: "CLA_OFLOW interrupt flag set bit", size: "1", shift: "19", mask: "0x80000" },
			{ name: "KEY", description: "KEY field", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "SYS_ERR_MASK", description: "SYS_ERR_MASK register", offset: "0x16",
		bits: [
			{ name: "CORRECTABLE_ERR", description: "CORRECTABLE_ERR flag mask bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "RAM_ACC_VIOL", description: "RAM_ACC_VIOL flag mask bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "AES_BUS_ERROR", description: "AES_BUS_ERROR flag mask bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPG1_INT", description: "EPG1_INT flag mask bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "FPU_UFLOW", description: "FPU_UFLOW flag mask bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FPU_OFLOW", description: "FPU_OFLOW flag mask bit", size: "1", shift: "17", mask: "0x20000" },
			{ name: "CLA_UFLOW", description: "CLA_UFLOW flag mask bit", size: "1", shift: "18", mask: "0x40000" },
			{ name: "CLA_OFLOW", description: "CLA_OFLOW flag mask bit", size: "1", shift: "19", mask: "0x80000" },
			{ name: "KEY", description: "KEY field", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
];
module.exports = {
	SYSCTLRegisters: SYSCTLRegisters,
}
