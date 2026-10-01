let MEMCFGRegisters = [
	{ name: "DXLOCK", description: "Dedicated RAM config Lock Register", offset: "0x0",
		bits: [
			{ name: "LOCK_M0", description: "M0 RAM Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOCK_M1", description: "M1 RAM Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "LOCK_PIEVECT", description: "PIEVECT RAM Lock bits", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "DXCOMMIT", description: "Dedicated RAM config Lock Commit Register", offset: "0x2",
		bits: [
			{ name: "COMMIT_M0", description: "M0 RAM Permanent Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "COMMIT_M1", description: "M1 RAM Permanent Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "COMMIT_PIEVECT", description: "PIEVECT RAM Permanent Lock bits", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "DXTEST", description: "Dedicated RAM TEST Register", offset: "0x4",
		bits: [
			{ name: "TEST_M0", description: "Selects the different modes for M0 RAM", size: "2", shift: "0", mask: "0x3" },
			{ name: "TEST_M1", description: "Selects the different modes for M1 RAM", size: "2", shift: "2", mask: "0xC" },
			{ name: "TEST_PIEVECT", description: "Selects the different modes for PIEVECT RAM", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "DXINIT", description: "Dedicated RAM Init Register", offset: "0x6",
		bits: [
			{ name: "INIT_M0", description: "RAM Initialization control for M0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INIT_M1", description: "RAM Initialization control for M1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INIT_PIEVECT", description: "RAM Initialization control for PIEVECT RAM.", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "DXINITDONE", description: "Dedicated RAM InitDone Status Register", offset: "0x8",
		bits: [
			{ name: "INITDONE_M0", description: "RAM Initialization status for M0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INITDONE_M1", description: "RAM Initialization status for M1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INITDONE_PIEVECT", description: "RAM Initialization status for PIEVECT RAM.", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "DXRAMTEST_LOCK", description: "Dedicated RAM TEST Lock Register", offset: "0xA",
		bits: [
			{ name: "M0_TEST", description: "M0_TEST_LOCK", size: "1", shift: "0", mask: "0x1" },
			{ name: "M1_TEST", description: "M1_TEST_LOCK", size: "1", shift: "1", mask: "0x2" },
			{ name: "PIEVECT_TEST", description: "PIEVECT_TEST_LOCK", size: "1", shift: "2", mask: "0x4" },
			{ name: "KEY", description: "Key for writing DxRAMTEST lock", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "GSXLOCK", description: "Global Shared RAM Config Lock Register", offset: "0x20",
		bits: [
			{ name: "LOCK_GS0", description: "GS0 RAM Lock bits", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GSXCOMMIT", description: "Global Shared RAM conffig Lock Commit Register", offset: "0x22",
		bits: [
			{ name: "COMMIT_GS0", description: "GS0 RAM Permanent Lock bits", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GSXTEST", description: "Global Shared RAM TEST Register", offset: "0x24",
		bits: [
			{ name: "TEST_GS0", description: "Selects the different modes for GS0 RAM", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "GSXINIT", description: "Global Shared RAM Init Register", offset: "0x26",
		bits: [
			{ name: "INIT_GS0", description: "RAM Initialization control for GS0 RAM.", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GSXINITDONE", description: "Global Shared RAM InitDone Status Register", offset: "0x28",
		bits: [
			{ name: "INITDONE_GS0", description: "RAM Initialization status for GS0 RAM.", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GSXRAMTEST_LOCK", description: "Global Shared  RAM TEST Lock Register", offset: "0x2A",
		bits: [
			{ name: "GS0_TEST", description: "GS0_TEST_LOCK", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Key for writing GSxRAMTEST lock", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "ROM_LOCK", description: "Rom configuration lock register", offset: "0x30",
		bits: [
			{ name: "LOCK_BOOTROM_SECUREROM", description: "BOOTROM and SECURE ROM lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Key for writing ROM LOCK", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "ROM_TEST", description: "ROM  TEST Register", offset: "0x32",
		bits: [
			{ name: "TEST_BOOTROM_SECUREROM", description: "Selects the different modes for", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "ROM_FORCE_ERROR", description: "ROM Force Error register", offset: "0x34",
		bits: [
			{ name: "FORCE_BOOTROM_SECUREROM_ERROR", description: "Force Bootrom_SECUREROM", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "UCERRFLG", description: "Uncorrectable Error Flag Register", offset: "0x0",
		bits: [
			{ name: "CPU_READ_ERR", description: "CPU  Uncorrectable Read Error Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMA_READ_ERR", description: "DMA  Uncorrectable Read Error Flag", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "UCERRSET", description: "Uncorrectable Error Flag Set Register", offset: "0x2",
		bits: [
			{ name: "CPU_READ_ERR", description: "CPU  Uncorrectable Read Error Flag  set", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMA_READ_ERR", description: "DMA  Uncorrectable Read Error Flag set", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "UCERRCLR", description: "Uncorrectable Error Flag Clear Register", offset: "0x4",
		bits: [
			{ name: "CPU_READ_ERR", description: "CPU  Uncorrectable Read Error Flag  clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMA_READ_ERR", description: "DMA  Uncorrectable Read Error Flag clear", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "UCCPUREADDR", description: "Uncorrectable CPU Error Address", offset: "0x6",
		bits: [
		]
	},
	{ name: "UCDMAREADDR", description: "Uncorrectable DMA Error Address", offset: "0x8",
		bits: [
		]
	},
	{ name: "FLUCERRSTATUS", description: "Flash read uncorrectable ecc err status", offset: "0x10",
		bits: [
			{ name: "UNC_ERR_L", description: "Lower 64 bits Uncorrectable error occurred", size: "1", shift: "0", mask: "0x1" },
			{ name: "DIAG_L_FAIL", description: "Diagnostics of ECC on lower 64 bits.", size: "1", shift: "1", mask: "0x2" },
			{ name: "UNC_ERR_H", description: "Upper 64 bits Uncorrectable error occurred", size: "1", shift: "8", mask: "0x100" },
			{ name: "DIAG_H_FAIL", description: "Diagnostics of ECC on upper 64 bits.", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "FLCERRSTATUS", description: "Flash read correctable ecc err status", offset: "0x12",
		bits: [
			{ name: "FAIL_0_L", description: "Lower 64bits Single Bit Error Corrected", size: "1", shift: "0", mask: "0x1" },
			{ name: "FAIL_1_L", description: "Lower 64bits Single Bit Error Corrected", size: "1", shift: "1", mask: "0x2" },
			{ name: "FAIL_0_H", description: "Upper 64bits Single Bit Error Corrected", size: "1", shift: "3", mask: "0x8" },
			{ name: "FAIL_1_H", description: "Upper 64bits Single Bit Error Corrected", size: "1", shift: "4", mask: "0x10" },
			{ name: "ERR_POS_L", description: "Bit Position of Single bit Error in", size: "6", shift: "16", mask: "0x3F0000" },
			{ name: "ERR_TYPE_L", description: "Error Type in lower 64 bits", size: "1", shift: "22", mask: "0x400000" },
			{ name: "ERR_POS_H", description: "Bit Position of Single bit Error in", size: "6", shift: "23", mask: "0x1F800000" },
			{ name: "ERR_TYPE_H", description: "Error Type in upper 64 bits", size: "1", shift: "29", mask: "0x20000000" },
		]
	},
	{ name: "CERRFLG", description: "Correctable Error Flag Register", offset: "0x20",
		bits: [
			{ name: "CPU_READ_ERR", description: "CPU  correctable Read Error Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMA_READ_ERR", description: "DMA  correctable Read Error Flag", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CERRSET", description: "Correctable Error Flag Set Register", offset: "0x22",
		bits: [
			{ name: "CPU_READ_ERR_SET", description: "CPU  correctable Read Error Flag  set", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMA_READ_ERR_SET", description: "DMA  correctable Read Error Flag set", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CERRCLR", description: "Correctable Error Flag Clear Register", offset: "0x24",
		bits: [
			{ name: "CPU_READ_ERR_CLR", description: "CPU correctable Read Error Flag  clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMA_READ_ERR_CLR", description: "DMA  correctable Read Error Flag clear", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CCPUREADDR", description: "Correctable CPU  Error Address", offset: "0x26",
		bits: [
		]
	},
	{ name: "CDMAREADDR", description: "Correctable DMA Error Address", offset: "0x28",
		bits: [
		]
	},
	{ name: "CERRCNT", description: "Correctable Error Count Register", offset: "0x30",
		bits: [
		]
	},
	{ name: "CERRTHRES", description: "Correctable Error Threshold Value Register", offset: "0x32",
		bits: [
			{ name: "CERRTHRES", description: "Correctable error threshold", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "CEINTFLG", description: "Correctable Error Interrupt Flag Status Register", offset: "0x34",
		bits: [
			{ name: "CEINTFLAG", description: "Total corrected error count exceeded threshold flag.", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CEINTCLR", description: "Correctable Error Interrupt Flag Clear Register", offset: "0x36",
		bits: [
			{ name: "CEINTCLR", description: "Total corrected error count exceeded flag clear", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CEINTSET", description: "Correctable Error Interrupt Flag Set Register", offset: "0x38",
		bits: [
			{ name: "CEINTSET", description: "Total corrected error count exceeded flag set", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CEINTEN", description: "Correctable Error Interrupt Enable Register", offset: "0x3A",
		bits: [
			{ name: "CEINTEN", description: "Total corrected error count exceeded flag enable", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "ROMWAITSTATE", description: "ROM Wait State Configuration Register", offset: "0x0",
		bits: [
			{ name: "WSDISABLE", description: "ROM Wait State Enable/Disable Control", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CPU_RAM_TEST_ERROR_STS", description: "Ram Test: Error Status Register", offset: "0x0",
		bits: [
			{ name: "UNC_ERROR", description: "UNC_ERROR flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLR_UNC_ERROR", description: "UNC_ERROR flag clear bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CPU_RAM_TEST_ERROR_STS_CLR", description: "Ram Test: Error Status Clear Register", offset: "0x2",
		bits: [
			{ name: "UNC_ERROR", description: "UNC_ERROR flag clear bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CPU_RAM_TEST_ERROR_ADDR", description: "Ram Test: Error address register", offset: "0x4",
		bits: [
		]
	},
];
module.exports = {
	MEMCFGRegisters: MEMCFGRegisters,
}
