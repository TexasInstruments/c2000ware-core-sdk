let MEMCFGRegisters = [
	{ name: "DXLOCK", description: "Dedicated RAM Config Lock Register", offset: "0x0",
		bits: [
			{ name: "LOCK_M0", description: "M0 RAM Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOCK_M1", description: "M1 RAM Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "LOCK_PIEVECT", description: "PIEVECT RAM Lock bits", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "DXCOMMIT", description: "Dedicated RAM Config Lock Commit Register", offset: "0x2",
		bits: [
			{ name: "COMMIT_M0", description: "M0 RAM Permanent Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "COMMIT_M1", description: "M1 RAM Permanent Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "COMMIT_PIEVECT", description: "PIEVECT RAM Permanent Lock bits", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "DXACCPROT0", description: "Dedicated RAM Config Register", offset: "0x8",
		bits: [
			{ name: "FETCHPROT_M0", description: "Fetch Protection For M0 RAM", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_M0", description: "CPU WR Protection For M0 RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "FETCHPROT_M1", description: "Fetch Protection For M1 RAM", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPUWRPROT_M1", description: "CPU WR Protection For M1 RAM", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "DXACCPROT1", description: "Dedicated RAM Config Register", offset: "0xA",
		bits: [
			{ name: "CPUWRPROT_PIEVECT", description: "CPU WR Protection For PIEVECT RAM", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "DXTEST", description: "Dedicated RAM TEST Register", offset: "0x10",
		bits: [
			{ name: "TEST_M0", description: "Selects the different modes for M0 RAM", size: "2", shift: "0", mask: "0x3" },
			{ name: "TEST_M1", description: "Selects the different modes for M1 RAM", size: "2", shift: "2", mask: "0xC" },
			{ name: "TEST_PIEVECT", description: "Selects the different modes for PIEVECT RAM", size: "2", shift: "8", mask: "0x300" },
		]
	},
	{ name: "DXINIT", description: "Dedicated RAM Init Register", offset: "0x12",
		bits: [
			{ name: "INIT_M0", description: "RAM Initialization control for M0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INIT_M1", description: "RAM Initialization control for M1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INIT_PIEVECT", description: "RAM Initialization control for PIEVECT RAM.", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "DXINITDONE", description: "Dedicated RAM InitDone Status Register", offset: "0x14",
		bits: [
			{ name: "INITDONE_M0", description: "RAM Initialization status for M0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INITDONE_M1", description: "RAM Initialization status for M1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INITDONE_PIEVECT", description: "RAM Initialization status for PIEVECT RAM.", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "DXRAMTEST_LOCK", description: "Lock register to Dx RAM TEST registers", offset: "0x16",
		bits: [
			{ name: "M0", description: "DxTEST.TEST_M0 LOCK", size: "1", shift: "0", mask: "0x1" },
			{ name: "M1", description: "DxTEST.TEST_M1 LOCK", size: "1", shift: "1", mask: "0x2" },
			{ name: "PIEVECT", description: "DxTEST.TEST_PIEVECT LOCK", size: "1", shift: "4", mask: "0x10" },
			{ name: "KEY", description: "Key for writing DxRAMTEST_LOCK", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "LSXLOCK", description: "Local Shared RAM Config Lock Register", offset: "0x20",
		bits: [
			{ name: "LOCK_LS0", description: "LS0 RAM Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOCK_LS1", description: "LS1 RAM Lock bits", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "LSXCOMMIT", description: "Local Shared RAM Config Lock Commit Register", offset: "0x22",
		bits: [
			{ name: "COMMIT_LS0", description: "LS0 RAM Permanent Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "COMMIT_LS1", description: "LS1 RAM Permanent Lock bits", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "LSXACCPROT0", description: "Local Shared RAM Config Register 0", offset: "0x28",
		bits: [
			{ name: "FETCHPROT_LS0", description: "Fetch Protection For LS0 RAM", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_LS0", description: "CPU WR Protection For LS0 RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "FETCHPROT_LS1", description: "Fetch Protection For LS1 RAM", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPUWRPROT_LS1", description: "CPU WR Protection For LS1 RAM", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "LSXTEST", description: "Local Shared RAM TEST Register", offset: "0x30",
		bits: [
			{ name: "TEST_LS0", description: "Selects the different modes for LS0 RAM", size: "2", shift: "0", mask: "0x3" },
			{ name: "TEST_LS1", description: "Selects the different modes for LS1 RAM", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "LSXINIT", description: "Local Shared RAM Init Register", offset: "0x32",
		bits: [
			{ name: "INIT_LS0", description: "RAM Initialization control for LS0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INIT_LS1", description: "RAM Initialization control for LS1 RAM.", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "LSXINITDONE", description: "Local Shared RAM InitDone Status Register", offset: "0x34",
		bits: [
			{ name: "INITDONE_LS0", description: "RAM Initialization status for LS0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INITDONE_LS1", description: "RAM Initialization status for LS1 RAM.", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "LSXRAMTEST_LOCK", description: "Lock register to LSx RAM TEST registers", offset: "0x36",
		bits: [
			{ name: "LS0", description: "LSxTEST.TEST_LS0 LOCK", size: "1", shift: "0", mask: "0x1" },
			{ name: "LS1", description: "LSxTEST.TEST_LS1 LOCK", size: "1", shift: "1", mask: "0x2" },
			{ name: "KEY", description: "KEY to enable write to lock", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "ROM_LOCK", description: "ROM Config Lock Register", offset: "0xA0",
		bits: [
			{ name: "LOCK_BOOTROM", description: "BOOTROM Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOCK_SECUREROM", description: "SECUREROM Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "KEY", description: "Key for writing ROM LOCK", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "ROM_TEST", description: "ROM  TEST Register", offset: "0xA2",
		bits: [
			{ name: "TEST_BOOTROM", description: "Selects the different modes for BOOTROM", size: "2", shift: "0", mask: "0x3" },
			{ name: "TEST_SECUREROM", description: "Selects the different modes for SECUREROM", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "ROM_FORCE_ERROR", description: "ROM Force Error register", offset: "0xA4",
		bits: [
			{ name: "FORCE_BOOTROM_ERROR", description: "Force Bootrom Parity Error", size: "1", shift: "0", mask: "0x1" },
			{ name: "FORCE_SECUREROM_ERROR", description: "Force SECUREROM Parity Error", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "MAVFLG", description: "Master Access Violation Flag Register", offset: "0x20",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Flag", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "MAVSET", description: "Master Access Violation Flag Set Register", offset: "0x22",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Flag Set", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Flag Set", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "MAVCLR", description: "Master Access Violation Flag Clear Register", offset: "0x24",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Flag Clear", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "MAVINTEN", description: "Master Access Violation Interrupt Enable Register", offset: "0x26",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Interrupt Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Interrupt Enable", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "MCPUFAVADDR", description: "Master CPU Fetch Access Violation Address", offset: "0x28",
		bits: [
		]
	},
	{ name: "MCPUWRAVADDR", description: "Master CPU Write Access Violation Address", offset: "0x2A",
		bits: [
		]
	},
	{ name: "UCERRFLG", description: "Uncorrectable Error Flag Register", offset: "0x0",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "UCERRSET", description: "Uncorrectable Error Flag Set Register", offset: "0x2",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag Set", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "UCERRCLR", description: "Uncorrectable Error Flag Clear Register", offset: "0x4",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag Clear", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "UCCPUREADDR", description: "Uncorrectable CPU Read Error Address", offset: "0x6",
		bits: [
		]
	},
	{ name: "FLUCERRSTATUS", description: "Flash read uncorrectable ecc err status", offset: "0x1C",
		bits: [
			{ name: "UNC_ERR_L", description: "Lower 64 bits Uncorrectable error occurred", size: "1", shift: "0", mask: "0x1" },
			{ name: "DIAG_L_FAIL", description: "Diagnostics of ECC on lower 64 bits.", size: "1", shift: "1", mask: "0x2" },
			{ name: "UNC_ERR_H", description: "Upper 64 bits Uncorrectable error occurred", size: "1", shift: "8", mask: "0x100" },
			{ name: "DIAG_H_FAIL", description: "Diagnostics of ECC on upper 64 bits.", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "FLCERRSTATUS", description: "Flash read correctable ecc err status", offset: "0x1E",
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
			{ name: "CPURDERR", description: "CPU Correctable Read Error Flag", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CERRSET", description: "Correctable Error Flag Set Register", offset: "0x22",
		bits: [
			{ name: "CPURDERR", description: "CPU Correctable Read Error Flag Set", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CERRCLR", description: "Correctable Error Flag Clear Register", offset: "0x24",
		bits: [
			{ name: "CPURDERR", description: "CPU Correctable Read Error Flag Clear", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CCPUREADDR", description: "Correctable CPU Read Error Address", offset: "0x26",
		bits: [
		]
	},
	{ name: "CERRCNT", description: "Correctable Error Count Register", offset: "0x2E",
		bits: [
		]
	},
	{ name: "CERRTHRES", description: "Correctable Error Threshold Value Register", offset: "0x30",
		bits: [
			{ name: "CERRTHRES", description: "Correctable error threshold.", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "CEINTFLG", description: "Correctable Error Interrupt Flag Status Register", offset: "0x32",
		bits: [
			{ name: "CEINTFLAG", description: "Total corrected error count exceeded threshold flag.", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CEINTCLR", description: "Correctable Error Interrupt Flag Clear Register", offset: "0x34",
		bits: [
			{ name: "CEINTCLR", description: "CPU Corrected Error Threshold Exceeded Error Clear.", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CEINTSET", description: "Correctable Error Interrupt Flag Set Register", offset: "0x36",
		bits: [
			{ name: "CEINTSET", description: "Total corrected error count exceeded flag set.", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CEINTEN", description: "Correctable Error Interrupt Enable Register", offset: "0x38",
		bits: [
			{ name: "CEINTEN", description: "CPU/DMA Correctable Error Interrupt Enable.", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CPU_RAM_TEST_ERROR_STS", description: "Ram Test: Error Status Register", offset: "0x0",
		bits: [
			{ name: "COR_ERROR", description: "COR_ERROR flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "UNC_ERROR", description: "UNC_ERROR flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLR_COR_ERROR", description: "COR_ERROR flag clear bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLR_UNC_ERROR", description: "UNC_ERROR flag clear bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CPU_RAM_TEST_ERROR_STS_CLR", description: "Ram Test: Error Status Clear Register", offset: "0x2",
		bits: [
			{ name: "COR_ERROR", description: "COR_ERROR flag clear bit", size: "1", shift: "0", mask: "0x1" },
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
