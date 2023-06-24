let MEMCFGRegisters = [
	{ name: "DXLOCK", description: "Dedicated RAM Config Lock Register", offset: "0x0",
		bits: [
			{ name: "LOCK_M0", description: "M0 RAM Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOCK_M1", description: "M1 RAM Lock bits", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "DXCOMMIT", description: "Dedicated RAM Config Lock Commit Register", offset: "0x2",
		bits: [
			{ name: "COMMIT_M0", description: "M0 RAM Permanent Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "COMMIT_M1", description: "M1 RAM Permanent Lock bits", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "DXTEST", description: "Dedicated RAM TEST Register", offset: "0x10",
		bits: [
			{ name: "TEST_M0", description: "Selects the different modes for M0 RAM", size: "2", shift: "0", mask: "0x3" },
			{ name: "TEST_M1", description: "Selects the different modes for M1 RAM", size: "2", shift: "2", mask: "0xC" },
		]
	},
	{ name: "DXINIT", description: "Dedicated RAM Init Register", offset: "0x12",
		bits: [
			{ name: "INIT_M0", description: "RAM Initialization control for M0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INIT_M1", description: "RAM Initialization control for M1 RAM.", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "DXINITDONE", description: "Dedicated RAM InitDone Status Register", offset: "0x14",
		bits: [
			{ name: "INITDONE_M0", description: "RAM Initialization status for M0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INITDONE_M1", description: "RAM Initialization status for M1 RAM.", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "DXRAMTEST_LOCK", description: "Lock register to Dx RAM TEST registers", offset: "0x16",
		bits: [
			{ name: "M0", description: "DxTEST.TEST_M0 LOCK", size: "1", shift: "0", mask: "0x1" },
			{ name: "M1", description: "DxTEST.TEST_M1 LOCK", size: "1", shift: "1", mask: "0x2" },
			{ name: "KEY", description: "Key for writing DxRAMTEST_LOCK", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "LSXLOCK", description: "Local Shared RAM Config Lock Register", offset: "0x20",
		bits: [
			{ name: "LOCK_LS4", description: "LS4 RAM Lock bits", size: "1", shift: "4", mask: "0x10" },
			{ name: "LOCK_LS5", description: "LS5 RAM Lock bits", size: "1", shift: "5", mask: "0x20" },
			{ name: "LOCK_LS6", description: "LS6 RAM Lock bits", size: "1", shift: "6", mask: "0x40" },
			{ name: "LOCK_LS7", description: "LS7 RAM Lock bits", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "LSXCOMMIT", description: "Local Shared RAM Config Lock Commit Register", offset: "0x22",
		bits: [
			{ name: "COMMIT_LS4", description: "LS4 RAM Permanent Lock bits", size: "1", shift: "4", mask: "0x10" },
			{ name: "COMMIT_LS5", description: "LS5 RAM Permanent Lock bits", size: "1", shift: "5", mask: "0x20" },
			{ name: "COMMIT_LS6", description: "LS6 RAM Permanent Lock bits", size: "1", shift: "6", mask: "0x40" },
			{ name: "COMMIT_LS7", description: "LS7 RAM Permanent Lock bits", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "LSXACCPROT1", description: "Local Shared RAM Config Register 1", offset: "0x2A",
		bits: [
			{ name: "FETCHPROT_LS4", description: "Fetch Protection For LS4 RAM", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_LS4", description: "CPU WR Protection For LS4 RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "FETCHPROT_LS5", description: "Fetch Protection For LS5 RAM", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPUWRPROT_LS5", description: "CPU WR Protection For LS5 RAM", size: "1", shift: "9", mask: "0x200" },
			{ name: "FETCHPROT_LS6", description: "Fetch Protection For LS6 RAM", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CPUWRPROT_LS6", description: "CPU WR Protection For LS6 RAM", size: "1", shift: "17", mask: "0x20000" },
			{ name: "FETCHPROT_LS7", description: "Fetch Protection For LS7 RAM", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "CPUWRPROT_LS7", description: "CPU WR Protection For LS7 RAM", size: "1", shift: "25", mask: "0x2000000" },
		]
	},
	{ name: "LSXTEST", description: "Local Shared RAM TEST Register", offset: "0x30",
		bits: [
			{ name: "TEST_LS4", description: "Selects the different modes for LS4 RAM", size: "2", shift: "8", mask: "0x300" },
			{ name: "TEST_LS5", description: "Selects the different modes for LS5 RAM", size: "2", shift: "10", mask: "0xC00" },
			{ name: "TEST_LS6", description: "Selects the different modes for LS6 RAM", size: "2", shift: "12", mask: "0x3000" },
			{ name: "TEST_LS7", description: "Selects the different modes for LS7 RAM", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "LSXINIT", description: "Local Shared RAM Init Register", offset: "0x32",
		bits: [
			{ name: "INIT_LS4", description: "RAM Initialization control for LS4 RAM.", size: "1", shift: "4", mask: "0x10" },
			{ name: "INIT_LS5", description: "RAM Initialization control for LS5 RAM.", size: "1", shift: "5", mask: "0x20" },
			{ name: "INIT_LS6", description: "RAM Initialization control for LS6 RAM.", size: "1", shift: "6", mask: "0x40" },
			{ name: "INIT_LS7", description: "RAM Initialization control for LS7 RAM.", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "LSXINITDONE", description: "Local Shared RAM InitDone Status Register", offset: "0x34",
		bits: [
			{ name: "INITDONE_LS4", description: "RAM Initialization status for LS4 RAM.", size: "1", shift: "4", mask: "0x10" },
			{ name: "INITDONE_LS5", description: "RAM Initialization status for LS5 RAM.", size: "1", shift: "5", mask: "0x20" },
			{ name: "INITDONE_LS6", description: "RAM Initialization status for LS6 RAM.", size: "1", shift: "6", mask: "0x40" },
			{ name: "INITDONE_LS7", description: "RAM Initialization status for LS7 RAM.", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "LSXRAMTEST_LOCK", description: "Lock register to LSx RAM TEST registers", offset: "0x36",
		bits: [
			{ name: "LS4", description: "LSxTEST.TEST_LS4 LOCK", size: "1", shift: "4", mask: "0x10" },
			{ name: "LS5", description: "LSxTEST.TEST_LS5 LOCK", size: "1", shift: "5", mask: "0x20" },
			{ name: "LS6", description: "LSxTEST.TEST_LS6 LOCK", size: "1", shift: "6", mask: "0x40" },
			{ name: "LS7", description: "LSxTEST.TEST_LS7 LOCK", size: "1", shift: "7", mask: "0x80" },
			{ name: "KEY", description: "KEY to enable write to lock", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "GSXLOCK", description: "Global Shared RAM Config Lock Register", offset: "0x40",
		bits: [
			{ name: "LOCK_GS0", description: "GS0 RAM Lock bits", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GSXCOMMIT", description: "Global Shared RAM Config Lock Commit Register", offset: "0x42",
		bits: [
			{ name: "COMMIT_GS0", description: "GS0 RAM Permanent Lock bits", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GSXACCPROT0", description: "Global Shared RAM Config Register 0", offset: "0x48",
		bits: [
			{ name: "FETCHPROT_GS0", description: "Fetch Protection For GS0 RAM", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_GS0", description: "CPU WR Protection For GS0 RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRPROT_GS0", description: "DMA WR Protection For GS0 RAM", size: "1", shift: "2", mask: "0x4" },
			{ name: "HICWRPROT_GS0", description: "HIC WR Protection For GS0 RAM", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "GSXTEST", description: "Global Shared RAM TEST Register", offset: "0x50",
		bits: [
			{ name: "TEST_GS0", description: "Selects the different modes for GS0 RAM", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "GSXINIT", description: "Global Shared RAM Init Register", offset: "0x52",
		bits: [
			{ name: "INIT_GS0", description: "RAM Initialization control for GS0 RAM.", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GSXINITDONE", description: "Global Shared RAM InitDone Status Register", offset: "0x54",
		bits: [
			{ name: "INITDONE_GS0", description: "RAM Initialization status for GS0 RAM.", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GSXRAMTEST_LOCK", description: "Lock register to GSx RAM TEST registers", offset: "0x56",
		bits: [
			{ name: "GS0", description: "GSxTEST.TEST_GS0 LOCK", size: "1", shift: "0", mask: "0x1" },
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
	{ name: "NMAVFLG", description: "Non-Master Access Violation Flag Register", offset: "0x0",
		bits: [
			{ name: "CPUREAD", description: "Non Master CPU Read Access Violation Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Master CPU Write Access Violation Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Master CPU Fetch Access Violation Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Master DMA Write Access Violation Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "DMAREAD", description: "Non Master DMA Read Access Violation Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "HICREAD", description: "Non Master HIC Read Access Violation Flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "HICWRITE", description: "Non Master HIC Write Access Violation Flag", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "NMAVSET", description: "Non-Master Access Violation Flag Set Register", offset: "0x2",
		bits: [
			{ name: "CPUREAD", description: "Non Master CPU Read Access Violation Flag Set", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Master CPU Write Access Violation Flag Set", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Master CPU Fetch Access Violation Flag Set", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Master DMA Write Access Violation Flag Set", size: "1", shift: "3", mask: "0x8" },
			{ name: "DMAREAD", description: "Non Master DMA Read Access Violation Flag Set", size: "1", shift: "10", mask: "0x400" },
			{ name: "HICREAD", description: "Non Master HIC Read Access Violation Flag Set", size: "1", shift: "11", mask: "0x800" },
			{ name: "HICWRITE", description: "Non Master HIC Write Access Violation Flag Set", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "NMAVCLR", description: "Non-Master Access Violation Flag Clear Register", offset: "0x4",
		bits: [
			{ name: "CPUREAD", description: "Non Master CPU Read Access Violation Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Master CPU Write Access Violation Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Master CPU Fetch Access Violation Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Master DMA Write Access Violation Flag Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "DMAREAD", description: "Non Master DMA Read Access Violation Flag Clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "HICREAD", description: "Non Master HIC Read Access Violation Flag Clear", size: "1", shift: "11", mask: "0x800" },
			{ name: "HICWRITE", description: "Non Master HIC Write Access Violation Flag Clear", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "NMAVINTEN", description: "Non-Master Access Violation Interrupt Enable Register", offset: "0x6",
		bits: [
			{ name: "CPUREAD", description: "Non Master CPU Read Access Violation Interrupt", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Master CPU Write Access Violation Interrupt", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Master CPU Fetch Access Violation Interrupt", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Master DMA Write Access Violation Interrupt", size: "1", shift: "3", mask: "0x8" },
			{ name: "DMAREAD", description: "Non Master DMA Read Access Violation Interrupt", size: "1", shift: "10", mask: "0x400" },
			{ name: "HICREAD", description: "Non Master HIC Read Access Violation Interrupt", size: "1", shift: "11", mask: "0x800" },
			{ name: "HICWRITE", description: "Non Master HIC Write Access Violation Interrupt", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "NMCPURDAVADDR", description: "Non-Master CPU Read Access Violation Address", offset: "0x8",
		bits: [
		]
	},
	{ name: "NMCPUWRAVADDR", description: "Non-Master CPU Write Access Violation Address", offset: "0xA",
		bits: [
		]
	},
	{ name: "NMCPUFAVADDR", description: "Non-Master CPU Fetch Access Violation Address", offset: "0xC",
		bits: [
		]
	},
	{ name: "NMDMARDAVADDR", description: "Non-Master DMA Read Access Violation Address", offset: "0x1C",
		bits: [
		]
	},
	{ name: "MAVFLG", description: "Master Access Violation Flag Register", offset: "0x20",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Master DMA Write Access Violation Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "HICAWRITE", description: "Master HICA Write Access Violation Flag", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "MAVSET", description: "Master Access Violation Flag Set Register", offset: "0x22",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Flag Set", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Flag Set", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Master DMA Write Access Violation Flag Set", size: "1", shift: "2", mask: "0x4" },
			{ name: "HICAWRITE", description: "Master HICA Write Access Violation Flag Set", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "MAVCLR", description: "Master Access Violation Flag Clear Register", offset: "0x24",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Master DMA Write Access Violation Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "HICAWRITE", description: "Master HICA Write Access Violation Flag Clear", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "MAVINTEN", description: "Master Access Violation Interrupt Enable Register", offset: "0x26",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Interrupt Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Interrupt Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Master DMA Write Access Violation Interrupt Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "HICAWRITE", description: "Master HICA Write Access Violation Interrupt Enable", size: "1", shift: "3", mask: "0x8" },
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
	{ name: "MDMAWRAVADDR", description: "Master  DMA Write Access Violation Address", offset: "0x2C",
		bits: [
		]
	},
	{ name: "MHICWRAVADDR", description: "Master  HIC Write Access Violation Address", offset: "0x2E",
		bits: [
		]
	},
	{ name: "NMHICRDAVADDR", description: "Non-Master HIC Read Access Violation Address", offset: "0x3A",
		bits: [
		]
	},
	{ name: "NMHICWRAVADDR", description: "Non-Master HIC Write Access Violation Address", offset: "0x3C",
		bits: [
		]
	},
	{ name: "UCERRFLG", description: "Uncorrectable Error Flag Register", offset: "0x0",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMARDERR", description: "DMA Uncorrectable Read Error Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "HICARDERR", description: "HICA Uncorrectable Read Error Flag", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "UCERRSET", description: "Uncorrectable Error Flag Set Register", offset: "0x2",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag Set", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMARDERR", description: "DMA Uncorrectable Read Error Flag Set", size: "1", shift: "1", mask: "0x2" },
			{ name: "HICARDERR", description: "HICA Uncorrectable Read Error Flag Set", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "UCERRCLR", description: "Uncorrectable Error Flag Clear Register", offset: "0x4",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMARDERR", description: "DMA Uncorrectable Read Error Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "HICARDERR", description: "HICA Uncorrectable Read Error Flag Clear", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "UCCPUREADDR", description: "Uncorrectable CPU Read Error Address", offset: "0x6",
		bits: [
		]
	},
	{ name: "UCDMAREADDR", description: "Uncorrectable DMA Read Error Address", offset: "0x8",
		bits: [
		]
	},
	{ name: "UCHICAREADDR", description: "Uncorrectable HICA Read Error Address", offset: "0x10",
		bits: [
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
