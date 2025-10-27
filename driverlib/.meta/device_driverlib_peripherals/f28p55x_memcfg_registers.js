let MEMCFGRegisters = [
	{ name: "DXLOCK", description: "Dedicated RAM Config Lock Register", offset: "0x0",
		bits: [
			{ name: "LOCK_M0", description: "M0 RAM Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOCK_M1", description: "M1 RAM Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "LOCK_PIEVECT", description: "PIEVECT RAM Lock bits", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "DXCOMMIT", description: "Dedicated RAM Config Lock Commit", offset: "0x2",
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
	{ name: "DXINITDONE", description: "Dedicated RAM InitDone Status", offset: "0x14",
		bits: [
			{ name: "INITDONE_M0", description: "RAM Initialization status for M0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INITDONE_M1", description: "RAM Initialization status for M1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INITDONE_PIEVECT", description: "RAM Initialization status for PIEVECT RAM.", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "DXRAMTEST_LOCK", description: "Lock register to Dx RAM TEST", offset: "0x16",
		bits: [
			{ name: "M0", description: "DxTEST.TEST_M0 LOCK", size: "1", shift: "0", mask: "0x1" },
			{ name: "M1", description: "DxTEST.TEST_M1 LOCK", size: "1", shift: "1", mask: "0x2" },
			{ name: "PIEVECT", description: "DxTEST.TEST_PIEVECT LOCK", size: "1", shift: "4", mask: "0x10" },
			{ name: "KEY", description: "Key for writing DxRAMTEST_LOCK", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "LSXLOCK", description: "Local Shared RAM Config Lock", offset: "0x20",
		bits: [
			{ name: "LOCK_LS0", description: "LS0 RAM Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOCK_LS1", description: "LS1 RAM Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "LOCK_LS2", description: "LS2 RAM Lock bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "LOCK_LS3", description: "LS3 RAM Lock bits", size: "1", shift: "3", mask: "0x8" },
			{ name: "LOCK_LS4", description: "LS4 RAM Lock bits", size: "1", shift: "4", mask: "0x10" },
			{ name: "LOCK_LS5", description: "LS5 RAM Lock bits", size: "1", shift: "5", mask: "0x20" },
			{ name: "LOCK_LS6", description: "LS6 RAM Lock bits", size: "1", shift: "6", mask: "0x40" },
			{ name: "LOCK_LS7", description: "LS7 RAM Lock bits", size: "1", shift: "7", mask: "0x80" },
			{ name: "LOCK_LS8", description: "LS8 RAM Lock bits", size: "1", shift: "8", mask: "0x100" },
			{ name: "LOCK_LS9", description: "LS9 RAM Lock bits", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "LSXCOMMIT", description: "Local Shared RAM Config Lock Commit", offset: "0x22",
		bits: [
			{ name: "COMMIT_LS0", description: "LS0 RAM Permanent Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "COMMIT_LS1", description: "LS1 RAM Permanent Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "COMMIT_LS2", description: "LS2 RAM Permanent Lock bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "COMMIT_LS3", description: "LS3 RAM Permanent Lock bits", size: "1", shift: "3", mask: "0x8" },
			{ name: "COMMIT_LS4", description: "LS4 RAM Permanent Lock bits", size: "1", shift: "4", mask: "0x10" },
			{ name: "COMMIT_LS5", description: "LS5 RAM Permanent Lock bits", size: "1", shift: "5", mask: "0x20" },
			{ name: "COMMIT_LS6", description: "LS6 RAM Permanent Lock bits", size: "1", shift: "6", mask: "0x40" },
			{ name: "COMMIT_LS7", description: "LS7 RAM Permanent Lock bits", size: "1", shift: "7", mask: "0x80" },
			{ name: "COMMIT_LS8", description: "LS8 RAM Permanent Lock bits", size: "1", shift: "8", mask: "0x100" },
			{ name: "COMMIT_LS9", description: "LS9 RAM Permanent Lock bits", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "LSXMSEL", description: "Local Shared RAM Controller Sel", offset: "0x24",
		bits: [
			{ name: "MSEL_LS0", description: "Controller Select for LS0 RAM", size: "2", shift: "0", mask: "0x3" },
			{ name: "MSEL_LS1", description: "Controller Select for LS1 RAM", size: "2", shift: "2", mask: "0xC" },
			{ name: "MSEL_LS2", description: "Controller Select for LS2 RAM", size: "2", shift: "4", mask: "0x30" },
			{ name: "MSEL_LS3", description: "Controller Select for LS3 RAM", size: "2", shift: "6", mask: "0xC0" },
			{ name: "MSEL_LS4", description: "Controller Select for LS4 RAM", size: "2", shift: "8", mask: "0x300" },
			{ name: "MSEL_LS5", description: "Controller Select for LS5 RAM", size: "2", shift: "10", mask: "0xC00" },
			{ name: "MSEL_LS6", description: "Controller Select for LS6 RAM", size: "2", shift: "12", mask: "0x3000" },
			{ name: "MSEL_LS7", description: "Controller Select for LS7 RAM", size: "2", shift: "14", mask: "0xC000" },
			{ name: "MSEL_LS8", description: "Controller Select for LS8 RAM", size: "2", shift: "16", mask: "0x30000" },
			{ name: "MSEL_LS9", description: "Controller Select for LS9 RAM", size: "2", shift: "18", mask: "0xC0000" },
		]
	},
	{ name: "LSXCLAPGM", description: "Local Shared RAM Prog/Exe control", offset: "0x26",
		bits: [
			{ name: "CLAPGM_LS0", description: "Selects LS0 RAM as program vs data memory for CLA", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLAPGM_LS1", description: "Selects LS1 RAM as program vs data memory for CLA", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLAPGM_LS2", description: "Selects LS2 RAM as program vs data memory for CLA", size: "1", shift: "2", mask: "0x4" },
			{ name: "CLAPGM_LS3", description: "Selects LS3 RAM as program vs data memory for CLA", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLAPGM_LS4", description: "Selects LS4 RAM as program vs data memory for CLA", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLAPGM_LS5", description: "Selects LS5 RAM as program vs data memory for CLA", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLAPGM_LS6", description: "Selects LS6 RAM as program vs data memory for CLA", size: "1", shift: "6", mask: "0x40" },
			{ name: "CLAPGM_LS7", description: "Selects LS7 RAM as program vs data memory for CLA", size: "1", shift: "7", mask: "0x80" },
			{ name: "CLAPGM_LS8", description: "Selects LS8 RAM as program vs data memory for CLA", size: "1", shift: "8", mask: "0x100" },
			{ name: "CLAPGM_LS9", description: "Selects LS9 RAM as program vs data memory for CLA", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "LSXACCPROT0", description: "Local Shared RAM Config Register 0", offset: "0x28",
		bits: [
			{ name: "FETCHPROT_LS0", description: "Fetch Protection For LS0 RAM", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_LS0", description: "CPU WR Protection For LS0 RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "FETCHPROT_LS1", description: "Fetch Protection For LS1 RAM", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPUWRPROT_LS1", description: "CPU WR Protection For LS1 RAM", size: "1", shift: "9", mask: "0x200" },
			{ name: "FETCHPROT_LS2", description: "Fetch Protection For LS2 RAM", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CPUWRPROT_LS2", description: "CPU WR Protection For LS2 RAM", size: "1", shift: "17", mask: "0x20000" },
			{ name: "FETCHPROT_LS3", description: "Fetch Protection For LS3 RAM", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "CPUWRPROT_LS3", description: "CPU WR Protection For LS3 RAM", size: "1", shift: "25", mask: "0x2000000" },
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
	{ name: "LSXACCPROT2(i)", description: "(0 <= i < 2) Local Shared RAM", offset: "(0x2CU + ((i) * 0x2U))",
		bits: [
		]
	},
	{ name: "LSXTEST", description: "Local Shared RAM TEST Register", offset: "0x30",
		bits: [
			{ name: "TEST_LS0", description: "Selects the different modes for LS0 RAM", size: "2", shift: "0", mask: "0x3" },
			{ name: "TEST_LS1", description: "Selects the different modes for LS1 RAM", size: "2", shift: "2", mask: "0xC" },
			{ name: "TEST_LS2", description: "Selects the different modes for LS2 RAM", size: "2", shift: "4", mask: "0x30" },
			{ name: "TEST_LS3", description: "Selects the different modes for LS3 RAM", size: "2", shift: "6", mask: "0xC0" },
			{ name: "TEST_LS4", description: "Selects the different modes for LS4 RAM", size: "2", shift: "8", mask: "0x300" },
			{ name: "TEST_LS5", description: "Selects the different modes for LS5 RAM", size: "2", shift: "10", mask: "0xC00" },
			{ name: "TEST_LS6", description: "Selects the different modes for LS6 RAM", size: "2", shift: "12", mask: "0x3000" },
			{ name: "TEST_LS7", description: "Selects the different modes for LS7 RAM", size: "2", shift: "14", mask: "0xC000" },
			{ name: "TEST_LS8", description: "Selects the different modes for LS8 RAM", size: "2", shift: "16", mask: "0x30000" },
			{ name: "TEST_LS9", description: "Selects the different modes for LS9 RAM", size: "2", shift: "18", mask: "0xC0000" },
		]
	},
	{ name: "LSXINIT", description: "Local Shared RAM Init Register", offset: "0x32",
		bits: [
			{ name: "INIT_LS0", description: "RAM Initialization control for LS0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INIT_LS1", description: "RAM Initialization control for LS1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INIT_LS2", description: "RAM Initialization control for LS2 RAM.", size: "1", shift: "2", mask: "0x4" },
			{ name: "INIT_LS3", description: "RAM Initialization control for LS3 RAM.", size: "1", shift: "3", mask: "0x8" },
			{ name: "INIT_LS4", description: "RAM Initialization control for LS4 RAM.", size: "1", shift: "4", mask: "0x10" },
			{ name: "INIT_LS5", description: "RAM Initialization control for LS5 RAM.", size: "1", shift: "5", mask: "0x20" },
			{ name: "INIT_LS6", description: "RAM Initialization control for LS6 RAM.", size: "1", shift: "6", mask: "0x40" },
			{ name: "INIT_LS7", description: "RAM Initialization control for LS7 RAM.", size: "1", shift: "7", mask: "0x80" },
			{ name: "INIT_LS8", description: "RAM Initialization control for LS8 RAM.", size: "1", shift: "8", mask: "0x100" },
			{ name: "INIT_LS9", description: "RAM Initialization control for LS9 RAM.", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "LSXINITDONE", description: "Local Shared RAM InitDone Status", offset: "0x34",
		bits: [
			{ name: "INITDONE_LS0", description: "RAM Initialization status for LS0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INITDONE_LS1", description: "RAM Initialization status for LS1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INITDONE_LS2", description: "RAM Initialization status for LS2 RAM.", size: "1", shift: "2", mask: "0x4" },
			{ name: "INITDONE_LS3", description: "RAM Initialization status for LS3 RAM.", size: "1", shift: "3", mask: "0x8" },
			{ name: "INITDONE_LS4", description: "RAM Initialization status for LS4 RAM.", size: "1", shift: "4", mask: "0x10" },
			{ name: "INITDONE_LS5", description: "RAM Initialization status for LS5 RAM.", size: "1", shift: "5", mask: "0x20" },
			{ name: "INITDONE_LS6", description: "RAM Initialization status for LS6 RAM.", size: "1", shift: "6", mask: "0x40" },
			{ name: "INITDONE_LS7", description: "RAM Initialization status for LS7 RAM.", size: "1", shift: "7", mask: "0x80" },
			{ name: "INITDONE_LS8", description: "RAM Initialization status for LS8 RAM.", size: "1", shift: "8", mask: "0x100" },
			{ name: "INITDONE_LS9", description: "RAM Initialization status for LS9 RAM.", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "LSXRAMTEST_LOCK", description: "Lock register to LSx RAM TEST", offset: "0x36",
		bits: [
			{ name: "LS0", description: "LSxTEST.TEST_LS0 LOCK", size: "1", shift: "0", mask: "0x1" },
			{ name: "LS1", description: "LSxTEST.TEST_LS1 LOCK", size: "1", shift: "1", mask: "0x2" },
			{ name: "LS2", description: "LSxTEST.TEST_LS2 LOCK", size: "1", shift: "2", mask: "0x4" },
			{ name: "LS3", description: "LSxTEST.TEST_LS3 LOCK", size: "1", shift: "3", mask: "0x8" },
			{ name: "LS4", description: "LSxTEST.TEST_LS4 LOCK", size: "1", shift: "4", mask: "0x10" },
			{ name: "LS5", description: "LSxTEST.TEST_LS5 LOCK", size: "1", shift: "5", mask: "0x20" },
			{ name: "LS6", description: "LSxTEST.TEST_LS6 LOCK", size: "1", shift: "6", mask: "0x40" },
			{ name: "LS7", description: "LSxTEST.TEST_LS7 LOCK", size: "1", shift: "7", mask: "0x80" },
			{ name: "LS8", description: "LSxTEST.TEST_LS8 LOCK", size: "1", shift: "8", mask: "0x100" },
			{ name: "LS9", description: "LSxTEST.TEST_LS9 LOCK", size: "1", shift: "9", mask: "0x200" },
			{ name: "KEY", description: "KEY to enable write to lock", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "GSXLOCK", description: "Global Shared RAM Config Lock", offset: "0x40",
		bits: [
			{ name: "LOCK_GS0", description: "GS0 RAM Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOCK_GS1", description: "GS1 RAM Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "LOCK_GS2", description: "GS2 RAM Lock bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "LOCK_GS3", description: "GS3 RAM Lock bits", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "GSXCOMMIT", description: "Global Shared RAM Config Lock", offset: "0x42",
		bits: [
			{ name: "COMMIT_GS0", description: "GS0 RAM Permanent Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "COMMIT_GS1", description: "GS1 RAM Permanent Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "COMMIT_GS2", description: "GS2 RAM Permanent Lock bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "COMMIT_GS3", description: "GS3 RAM Permanent Lock bits", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "GSXACCPROT0", description: "Global Shared RAM Config Register 0", offset: "0x48",
		bits: [
			{ name: "FETCHPROT_GS0", description: "Fetch Protection For GS0 RAM", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_GS0", description: "CPU WR Protection For GS0 RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRPROT_GS0", description: "DMA WR Protection For GS0 RAM", size: "1", shift: "2", mask: "0x4" },
			{ name: "NPU_WRPROT_GS0", description: "NPU WR Protection For GS0 RAM", size: "1", shift: "3", mask: "0x8" },
			{ name: "FETCHPROT_GS1", description: "Fetch Protection For GS1 RAM", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPUWRPROT_GS1", description: "CPU WR Protection For GS1 RAM", size: "1", shift: "9", mask: "0x200" },
			{ name: "DMAWRPROT_GS1", description: "DMA WR Protection For GS1 RAM", size: "1", shift: "10", mask: "0x400" },
			{ name: "NPU_WRPROT_GS1", description: "NPU WR Protection For GS1 RAM", size: "1", shift: "11", mask: "0x800" },
			{ name: "FETCHPROT_GS2", description: "Fetch Protection For GS2 RAM", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CPUWRPROT_GS2", description: "CPU WR Protection For GS2 RAM", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DMAWRPROT_GS2", description: "DMA WR Protection For GS2 RAM", size: "1", shift: "18", mask: "0x40000" },
			{ name: "NPU_WRPROT_GS2", description: "NPU WR Protection For GS2 RAM", size: "1", shift: "19", mask: "0x80000" },
			{ name: "FETCHPROT_GS3", description: "Fetch Protection For GS3 RAM", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "CPUWRPROT_GS3", description: "CPU WR Protection For GS3 RAM", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "DMAWRPROT_GS3", description: "DMA WR Protection For GS3 RAM", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "NPU_WRPROT_GS3", description: "NPU WR Protection For GS3 RAM", size: "1", shift: "27", mask: "0x8000000" },
		]
	},
	{ name: "GSXTEST", description: "Global Shared RAM TEST Register", offset: "0x50",
		bits: [
			{ name: "TEST_GS0", description: "Selects the different modes for GS0 RAM", size: "2", shift: "0", mask: "0x3" },
			{ name: "TEST_GS1", description: "Selects the different modes for GS1 RAM", size: "2", shift: "2", mask: "0xC" },
			{ name: "TEST_GS2", description: "Selects the different modes for GS2 RAM", size: "2", shift: "4", mask: "0x30" },
			{ name: "TEST_GS3", description: "Selects the different modes for GS3 RAM", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "GSXINIT", description: "Global Shared RAM Init Register", offset: "0x52",
		bits: [
			{ name: "INIT_GS0", description: "RAM Initialization control for GS0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INIT_GS1", description: "RAM Initialization control for GS1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INIT_GS2", description: "RAM Initialization control for GS2 RAM.", size: "1", shift: "2", mask: "0x4" },
			{ name: "INIT_GS3", description: "RAM Initialization control for GS3 RAM.", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "GSXINITDONE", description: "Global Shared RAM InitDone Status", offset: "0x54",
		bits: [
			{ name: "INITDONE_GS0", description: "RAM Initialization status for GS0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INITDONE_GS1", description: "RAM Initialization status for GS1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INITDONE_GS2", description: "RAM Initialization status for GS2 RAM.", size: "1", shift: "2", mask: "0x4" },
			{ name: "INITDONE_GS3", description: "RAM Initialization status for GS3 RAM.", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "GSXRAMTEST_LOCK", description: "Lock register to GSx RAM TEST", offset: "0x56",
		bits: [
			{ name: "GS0", description: "GSxTEST.TEST_GS0 LOCK", size: "1", shift: "0", mask: "0x1" },
			{ name: "GS1", description: "GSxTEST.TEST_GS1 LOCK", size: "1", shift: "1", mask: "0x2" },
			{ name: "GS2", description: "GSxTEST.TEST_GS2 LOCK", size: "1", shift: "2", mask: "0x4" },
			{ name: "GS3", description: "GSxTEST.TEST_GS3 LOCK", size: "1", shift: "3", mask: "0x8" },
			{ name: "KEY", description: "KEY to enable write to lock", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "MSGXLOCK", description: "Message RAM Config Lock Register", offset: "0x60",
		bits: [
			{ name: "LOCK_CPUTOCLA1", description: "CPUTOCLA1 RAM Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "LOCK_CLA1TOCPU", description: "CLA1TOCPU RAM Lock bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "LOCK_CLA1TODMA", description: "CLA1TODMA RAM control fields lock bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "LOCK_DMATOCLA1", description: "DMATOCLA1 RAM control fields lock bit", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "MSGXCOMMIT", description: "Message RAM Config Lock Commit", offset: "0x62",
		bits: [
			{ name: "COMMIT_CPUTOCLA1", description: "CPUTOCLA1 RAM control fields COMMIT bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "COMMIT_CLA1TOCPU", description: "CLA1TOCPU RAM control fields COMMIT bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "COMMIT_CLA1TODMA", description: "CLA1TODMA RAM control fields COMMIT bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "COMMIT_DMATOCLA1", description: "DMATOCLA1 RAM control fields COMMIT bit", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "MSGXTEST", description: "Message RAM TEST Register", offset: "0x70",
		bits: [
			{ name: "TEST_CPUTOCLA1", description: "CPU to CLA1 MSG RAM Mode Select", size: "2", shift: "2", mask: "0xC" },
			{ name: "TEST_CLA1TOCPU", description: "CLA1 to CPU MSG RAM Mode Select", size: "2", shift: "4", mask: "0x30" },
			{ name: "TEST_CLA1TODMA", description: "CLA1 to DMA MSG RAM Mode Select", size: "2", shift: "10", mask: "0xC00" },
			{ name: "TEST_DMATOCLA1", description: "DMA to CLA1 MSG RAM Mode Select", size: "2", shift: "12", mask: "0x3000" },
		]
	},
	{ name: "MSGXINIT", description: "Message RAM Init Register", offset: "0x72",
		bits: [
			{ name: "INIT_CPUTOCLA1", description: "Initialization control for CPUTOCLA1 MSG RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "INIT_CLA1TOCPU", description: "Initialization control for CLA1TOCPU MSG RAM", size: "1", shift: "2", mask: "0x4" },
			{ name: "INIT_CLA1TODMA", description: "Initialization control for CLA1 to DMA MSG RAM", size: "1", shift: "5", mask: "0x20" },
			{ name: "INIT_DMATOCLA1", description: "Initialization control for DMA to CLA1 MSG RAM", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "MSGXINITDONE", description: "Message RAM InitDone Status", offset: "0x74",
		bits: [
			{ name: "INITDONE_CPUTOCLA1", description: "Initialization status for CPU to CLA1", size: "1", shift: "1", mask: "0x2" },
			{ name: "INITDONE_CLA1TOCPU", description: "Initialization status for CLA1 to CPU", size: "1", shift: "2", mask: "0x4" },
			{ name: "INITDONE_CLA1TODMA", description: "Initialization status for CLA1 to DMA", size: "1", shift: "5", mask: "0x20" },
			{ name: "INITDONE_DMATOCLA1", description: "Initialization status for DMA to CLA1", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "MSGXRAMTEST_LOCK", description: "Lock register for MSGx RAM TEST", offset: "0x76",
		bits: [
			{ name: "CPUTOCLA1", description: "MSGxRAMTEST_LOCK.CPUTOCLA1Lock", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLA1TOCPU", description: "MSGxRAMTEST_LOCK.CLA1TOCPULock", size: "1", shift: "2", mask: "0x4" },
			{ name: "CLA1TODMA", description: "MSGxRAMTEST_LOCK.CLA1TODMALock", size: "1", shift: "5", mask: "0x20" },
			{ name: "DMATOCLA1", description: "MSGxRAMTEST_LOCK.DMATOCLA1Lock", size: "1", shift: "6", mask: "0x40" },
			{ name: "KEY", description: "KEY to enable write to lock", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "ROM_LOCK", description: "ROM Config Lock Register", offset: "0xA0",
		bits: [
			{ name: "LOCK_BOOTROM", description: "BOOTROM Lock bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOCK_SECUREROM", description: "SECUREROM Lock bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "LOCK_CLADATAROM", description: "CLADATAROM Lock bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "KEY", description: "Key for writing ROM LOCK", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "ROM_TEST", description: "ROM  TEST Register", offset: "0xA2",
		bits: [
			{ name: "TEST_BOOTROM", description: "Selects the different modes for BOOTROM", size: "2", shift: "0", mask: "0x3" },
			{ name: "TEST_SECUREROM", description: "Selects the different modes for SECUREROM", size: "2", shift: "2", mask: "0xC" },
			{ name: "TEST_CLADATAROM", description: "Selects the different modes for CLADATAROM", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "ROM_FORCE_ERROR", description: "ROM Force Error register", offset: "0xA4",
		bits: [
			{ name: "FORCE_BOOTROM_ERROR", description: "Force Bootrom Parity Error", size: "1", shift: "0", mask: "0x1" },
			{ name: "FORCE_SECUREROM_ERROR", description: "Force SECUREROM Parity Error", size: "1", shift: "1", mask: "0x2" },
			{ name: "FORCE_CLADATAROM_ERROR", description: "Force CLADATAROM Parity Error", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "NMAVFLG", description: "Non-Controller Access Violation Flag Register", offset: "0x0",
		bits: [
			{ name: "CPUREAD", description: "Non Controller CPU Read Access Violation Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Controller CPU Write Access Violation Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Controller CPU Fetch Access Violation Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Controller DMA Write Access Violation Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLA1READ", description: "Non Controller CLA1 Read Access Violation Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLA1WRITE", description: "Non Controller CLA1 Write Access Violation Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLA1FETCH", description: "Non Controller CLA1 Fetch Access Violation Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "DMAREAD", description: "Non Controller DMA Read Access Violation Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "NPUREAD", description: "Non Controller NPU Read Access Violation Flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "NPUWRITE", description: "Non Controller NPU Write Violation Flag", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "NMAVSET", description: "Non-Controller Access Violation Flag Set Register", offset: "0x2",
		bits: [
			{ name: "CPUREAD", description: "Non Controller CPU Read Access Violation Flag Set", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Controller CPU Write Access Violation Flag Set", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Controller CPU Fetch Access Violation Flag Set", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Controller DMA Write Access Violation Flag Set", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLA1READ", description: "Non Controller CLA1 Read Access Violation Flag Set", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLA1WRITE", description: "Non Controller CLA1 Write Access Violation Flag Set", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLA1FETCH", description: "Non Controller CLA1 Fetch Access Violation Flag Set", size: "1", shift: "6", mask: "0x40" },
			{ name: "DMAREAD", description: "Non Controller DMA Read Access Violation Flag Set", size: "1", shift: "10", mask: "0x400" },
			{ name: "NPUREAD", description: "Non Controller NPU Read Access Violation Flag Set", size: "1", shift: "11", mask: "0x800" },
			{ name: "NPUWRITE", description: "Non Controller NPU Write Access Violation Flag Set", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "NMAVCLR", description: "Non-Controller Access Violation Flag Clear Register", offset: "0x4",
		bits: [
			{ name: "CPUREAD", description: "Non Controller CPU Read Access Violation Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Controller CPU Write Access Violation Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Controller CPU Fetch Access Violation Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Controller DMA Write Access Violation Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLA1READ", description: "Non Controller CLA1 Read Access Violation Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLA1WRITE", description: "Non Controller CLA1 Write Access Violation Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLA1FETCH", description: "Non Controller CLA1 Fetch Access Violation Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "DMAREAD", description: "Non Controller DMA Read Access Violation Flag Clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "NPUREAD", description: "Non Controller NPU Read Access Violation Flag Clear", size: "1", shift: "11", mask: "0x800" },
			{ name: "NPUWRITE", description: "Non Controller NPU Write Access Violation Flag", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "NMAVINTEN", description: "Non-Controller Access Violation Interrupt Enable", offset: "0x6",
		bits: [
			{ name: "CPUREAD", description: "Non Controller CPU Read Access Violation", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Controller CPU Write Access Violation", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Controller CPU Fetch Access Violation", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Controller DMA Write Access Violation", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLA1READ", description: "Non Controller CLA1 Read Access Violation", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLA1WRITE", description: "Non Controller CLA1 Write Access Violation", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLA1FETCH", description: "Non Controller CLA1 Fetch Access Violation", size: "1", shift: "6", mask: "0x40" },
			{ name: "DMAREAD", description: "Non Controller DMA Read Access Violation", size: "1", shift: "10", mask: "0x400" },
			{ name: "NPUREAD", description: "Non Controller NPU Read Access Violation", size: "1", shift: "11", mask: "0x800" },
			{ name: "NPUWRITE", description: "Non Controller NPU Write Violation Interrupt", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "NMCPURDAVADDR", description: "Non-Controller CPU Read Access Violation Address", offset: "0x8",
		bits: [
		]
	},
	{ name: "NMCPUWRAVADDR", description: "Non-Controller CPU Write Access Violation Address", offset: "0xA",
		bits: [
		]
	},
	{ name: "NMCPUFAVADDR", description: "Non-Controller CPU Fetch Access Violation Address", offset: "0xC",
		bits: [
		]
	},
	{ name: "NMDMAWRAVADDR", description: "Non-Controller DMA Write Access Violation Address", offset: "0xE",
		bits: [
		]
	},
	{ name: "NMCLA1RDAVADDR", description: "Non-Controller CLA1 Read Access Violation Address", offset: "0x10",
		bits: [
		]
	},
	{ name: "NMCLA1WRAVADDR", description: "Non-Controller CLA1 Write Access Violation Address", offset: "0x12",
		bits: [
		]
	},
	{ name: "NMCLA1FAVADDR", description: "Non-Controller CLA1 Fetch Access Violation Address", offset: "0x14",
		bits: [
		]
	},
	{ name: "NMDMARDAVADDR", description: "Non-Controller DMA Read Access Violation Address", offset: "0x1C",
		bits: [
		]
	},
	{ name: "MAVFLG", description: "Controller Access Violation Flag Register", offset: "0x20",
		bits: [
			{ name: "CPUFETCH", description: "Controller CPU Fetch Access Violation Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Controller CPU Write Access Violation Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Controller DMA Write Access Violation Flag", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MAVSET", description: "Controller Access Violation Flag Set Register", offset: "0x22",
		bits: [
			{ name: "CPUFETCH", description: "Controller CPU Fetch Access Violation Flag Set", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Controller CPU Write Access Violation Flag Set", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Controller DMA Write Access Violation Flag Set", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MAVCLR", description: "Controller Access Violation Flag Clear Register", offset: "0x24",
		bits: [
			{ name: "CPUFETCH", description: "Controller CPU Fetch Access Violation Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Controller CPU Write Access Violation Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Controller DMA Write Access Violation Flag Clear", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MAVINTEN", description: "Controller Access Violation Interrupt Enable Register", offset: "0x26",
		bits: [
			{ name: "CPUFETCH", description: "Controller CPU Fetch Access Violation Interrupt Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Controller CPU Write Access Violation Interrupt Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Controller DMA Write Access Violation Interrupt Enable", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MCPUFAVADDR", description: "Controller CPU Fetch Access Violation Address", offset: "0x28",
		bits: [
		]
	},
	{ name: "MCPUWRAVADDR", description: "Controller CPU Write Access Violation Address", offset: "0x2A",
		bits: [
		]
	},
	{ name: "MDMAWRAVADDR", description: "Controller  DMA Write Access Violation Address", offset: "0x2C",
		bits: [
		]
	},
	{ name: "NMNPURDAVADDR", description: "Non-Controller NPU Read Access Violation Address", offset: "0x3A",
		bits: [
		]
	},
	{ name: "NMNPUWRAVADDR", description: "Non-Controller NPU Write Access Violation Address", offset: "0x3C",
		bits: [
		]
	},
	{ name: "UCERRFLG", description: "Uncorrectable Error Flag Register", offset: "0x0",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMARDERR", description: "DMA Uncorrectable Read Error Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLA1RDERR", description: "CLA1 Uncorrectable Read Error Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "NPURDERR", description: "NPU Uncorrectable Read Error Flag", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "UCERRSET", description: "Uncorrectable Error Flag Set Register", offset: "0x2",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag Set", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMARDERR", description: "DMA Uncorrectable Read Error Flag Set", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLA1RDERR", description: "CLA1 Uncorrectable Read Error Flag Set", size: "1", shift: "2", mask: "0x4" },
			{ name: "NPURDERR", description: "NPU Uncorrectable Read Error Flag Set", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "UCERRCLR", description: "Uncorrectable Error Flag Clear Register", offset: "0x4",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMARDERR", description: "DMA Uncorrectable Read Error Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLA1RDERR", description: "CLA1 Uncorrectable Read Error Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "NPURDERR", description: "NPU Uncorrectable Read Error Flag Clear", size: "1", shift: "5", mask: "0x20" },
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
	{ name: "UCCLA1READDR", description: "Uncorrectable CLA1 Read Error Address", offset: "0xA",
		bits: [
		]
	},
	{ name: "UCNPUREADDR", description: "Uncorrectable NPU Read Error Address", offset: "0x10",
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
			{ name: "DMARDERR", description: "DMA Correctable Read Error Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLA1RDERR", description: "CLA1 Correctable Read Error Flag", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "CERRSET", description: "Correctable Error Flag Set Register", offset: "0x22",
		bits: [
			{ name: "CPURDERR", description: "CPU Correctable Read Error Flag Set", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMARDERR", description: "DMA Correctable Read Error Flag Set", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLA1RDERR", description: "CLA1 Correctable Read Error Flag Set", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "CERRCLR", description: "Correctable Error Flag Clear Register", offset: "0x24",
		bits: [
			{ name: "CPURDERR", description: "CPU Correctable Read Error Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMARDERR", description: "DMA Correctable Read Error Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLA1RDERR", description: "CLA1 Correctable Read Error Flag Clear", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "CCPUREADDR", description: "Correctable CPU Read Error Address", offset: "0x26",
		bits: [
		]
	},
	{ name: "CDMAREADDR", description: "Correctable DMA Read Error Address", offset: "0x28",
		bits: [
		]
	},
	{ name: "CCLA1READDR", description: "Correctable CLA1 Read Error Address", offset: "0x2A",
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
