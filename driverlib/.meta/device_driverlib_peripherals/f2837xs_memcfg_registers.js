let MEMCFGRegisters = [
	{ name: "DXLOCK", description: "Dedicated RAM Config Lock Register", offset: "0x0",
		bits: [
			{ name: "LOCK_D0", description: "D0 RAM access protection and master select fields lock", size: "1", shift: "2", mask: "0x4" },
			{ name: "LOCK_D1", description: "D1 RAM access protection and master select fields lock", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "DXCOMMIT", description: "Dedicated RAM Config Lock Commit Register", offset: "0x2",
		bits: [
			{ name: "COMMIT_D0", description: "D0 RAM access protection and master select permanent", size: "1", shift: "2", mask: "0x4" },
			{ name: "COMMIT_D1", description: "D1 RAM access protection and master select permanent", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "DXACCPROT0", description: "Dedicated RAM Config Register", offset: "0x8",
		bits: [
			{ name: "FETCHPROT_D0", description: "Fetch Protection For D0 RAM", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CPUWRPROT_D0", description: "CPU WR Protection For D0 RAM", size: "1", shift: "17", mask: "0x20000" },
			{ name: "FETCHPROT_D1", description: "Fetch Protection For D1 RAM", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "CPUWRPROT_D1", description: "CPU WR Protection For D1 RAM", size: "1", shift: "25", mask: "0x2000000" },
		]
	},
	{ name: "DXTEST", description: "Dedicated RAM TEST Register", offset: "0x10",
		bits: [
			{ name: "TEST_M0", description: "Selects the different modes for M0 RAM", size: "2", shift: "0", mask: "0x3" },
			{ name: "TEST_M1", description: "Selects the different modes for M1 RAM", size: "2", shift: "2", mask: "0xC" },
			{ name: "TEST_D0", description: "Selects the different modes for D0 RAM", size: "2", shift: "4", mask: "0x30" },
			{ name: "TEST_D1", description: "Selects the different modes for D1 RAM", size: "2", shift: "6", mask: "0xC0" },
		]
	},
	{ name: "DXINIT", description: "Dedicated RAM Init Register", offset: "0x12",
		bits: [
			{ name: "INIT_M0", description: "RAM Initialization control for M0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INIT_M1", description: "RAM Initialization control for M1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INIT_D0", description: "RAM Initialization control for D0 RAM.", size: "1", shift: "2", mask: "0x4" },
			{ name: "INIT_D1", description: "RAM Initialization control for D1 RAM.", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "DXINITDONE", description: "Dedicated RAM InitDone Status Register", offset: "0x14",
		bits: [
			{ name: "INITDONE_M0", description: "RAM Initialization status for M0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INITDONE_M1", description: "RAM Initialization status for M1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INITDONE_D0", description: "RAM Initialization status for D0 RAM.", size: "1", shift: "2", mask: "0x4" },
			{ name: "INITDONE_D1", description: "RAM Initialization status for D1 RAM.", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "LSXLOCK", description: "Local Shared RAM Config Lock Register", offset: "0x20",
		bits: [
			{ name: "LOCK_LS0", description: "LS0 RAM access protection and master select fields", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOCK_LS1", description: "LS1 RAM access protection and master select fields", size: "1", shift: "1", mask: "0x2" },
			{ name: "LOCK_LS2", description: "LS2 RAM access protection and master select fields", size: "1", shift: "2", mask: "0x4" },
			{ name: "LOCK_LS3", description: "LS3 RAM access protection and master select fields", size: "1", shift: "3", mask: "0x8" },
			{ name: "LOCK_LS4", description: "LS4 RAM access protection and master select fields", size: "1", shift: "4", mask: "0x10" },
			{ name: "LOCK_LS5", description: "LS5 RAM access protection and master select fields", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "LSXCOMMIT", description: "Local Shared RAM Config Lock Commit Register", offset: "0x22",
		bits: [
			{ name: "COMMIT_LS0", description: "LS0 RAM access protection and master select", size: "1", shift: "0", mask: "0x1" },
			{ name: "COMMIT_LS1", description: "LS1 RAM access protection and master select", size: "1", shift: "1", mask: "0x2" },
			{ name: "COMMIT_LS2", description: "LS2 RAM access protection and master select", size: "1", shift: "2", mask: "0x4" },
			{ name: "COMMIT_LS3", description: "LS3 RAM access protection and master select", size: "1", shift: "3", mask: "0x8" },
			{ name: "COMMIT_LS4", description: "LS4 RAM access protection and master select", size: "1", shift: "4", mask: "0x10" },
			{ name: "COMMIT_LS5", description: "LS5 RAM access protection and master select", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "LSXMSEL", description: "Local Shared RAM Master Sel Register", offset: "0x24",
		bits: [
			{ name: "MSEL_LS0", description: "Master Select for LS0 RAM", size: "2", shift: "0", mask: "0x3" },
			{ name: "MSEL_LS1", description: "Master Select for LS1 RAM", size: "2", shift: "2", mask: "0xC" },
			{ name: "MSEL_LS2", description: "Master Select for LS2 RAM", size: "2", shift: "4", mask: "0x30" },
			{ name: "MSEL_LS3", description: "Master Select for LS3 RAM", size: "2", shift: "6", mask: "0xC0" },
			{ name: "MSEL_LS4", description: "Master Select for LS4 RAM", size: "2", shift: "8", mask: "0x300" },
			{ name: "MSEL_LS5", description: "Master Select for LS5 RAM", size: "2", shift: "10", mask: "0xC00" },
		]
	},
	{ name: "LSXCLAPGM", description: "Local Shared RAM Prog/Exe control Register", offset: "0x26",
		bits: [
			{ name: "CLAPGM_LS0", description: "Selects LS0 RAM as program vs data memory for CLA", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLAPGM_LS1", description: "Selects LS1 RAM as program vs data memory for CLA", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLAPGM_LS2", description: "Selects LS2 RAM as program vs data memory for CLA", size: "1", shift: "2", mask: "0x4" },
			{ name: "CLAPGM_LS3", description: "Selects LS3 RAM as program vs data memory for CLA", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLAPGM_LS4", description: "Selects LS4 RAM as program vs data memory for CLA", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLAPGM_LS5", description: "Selects LS5 RAM as program vs data memory for CLA", size: "1", shift: "5", mask: "0x20" },
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
		]
	},
	{ name: "LSXINITDONE", description: "Local Shared RAM InitDone Status Register", offset: "0x34",
		bits: [
			{ name: "INITDONE_LS0", description: "RAM Initialization status for LS0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INITDONE_LS1", description: "RAM Initialization status for LS1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INITDONE_LS2", description: "RAM Initialization status for LS2 RAM.", size: "1", shift: "2", mask: "0x4" },
			{ name: "INITDONE_LS3", description: "RAM Initialization status for LS3 RAM.", size: "1", shift: "3", mask: "0x8" },
			{ name: "INITDONE_LS4", description: "RAM Initialization status for LS4 RAM.", size: "1", shift: "4", mask: "0x10" },
			{ name: "INITDONE_LS5", description: "RAM Initialization status for LS5 RAM.", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "GSXLOCK", description: "Global Shared RAM Config Lock Register", offset: "0x40",
		bits: [
			{ name: "LOCK_GS0", description: "GS0 RAM access protection and master select fields", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOCK_GS1", description: "GS1 RAM access protection and master select fields", size: "1", shift: "1", mask: "0x2" },
			{ name: "LOCK_GS2", description: "GS2 RAM access protection and master select fields", size: "1", shift: "2", mask: "0x4" },
			{ name: "LOCK_GS3", description: "GS3 RAM access protection and master select fields", size: "1", shift: "3", mask: "0x8" },
			{ name: "LOCK_GS4", description: "GS4 RAM access protection and master select fields", size: "1", shift: "4", mask: "0x10" },
			{ name: "LOCK_GS5", description: "GS5 RAM access protection and master select fields", size: "1", shift: "5", mask: "0x20" },
			{ name: "LOCK_GS6", description: "GS6 RAM access protection and master select fields", size: "1", shift: "6", mask: "0x40" },
			{ name: "LOCK_GS7", description: "GS7 RAM access protection and master select fields", size: "1", shift: "7", mask: "0x80" },
			{ name: "LOCK_GS8", description: "GS8 RAM access protection and master select fields", size: "1", shift: "8", mask: "0x100" },
			{ name: "LOCK_GS9", description: "GS9 RAM access protection and master select fields", size: "1", shift: "9", mask: "0x200" },
			{ name: "LOCK_GS10", description: "GS10 RAM access protection and master select fields", size: "1", shift: "10", mask: "0x400" },
			{ name: "LOCK_GS11", description: "GS11 RAM access protection and master select fields", size: "1", shift: "11", mask: "0x800" },
			{ name: "LOCK_GS12", description: "GS12 RAM access protection and master select fields", size: "1", shift: "12", mask: "0x1000" },
			{ name: "LOCK_GS13", description: "GS13 RAM access protection and master select fields", size: "1", shift: "13", mask: "0x2000" },
			{ name: "LOCK_GS14", description: "GS14 RAM access protection and master select fields", size: "1", shift: "14", mask: "0x4000" },
			{ name: "LOCK_GS15", description: "GS15 RAM access protection and master select fields", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "GSXCOMMIT", description: "Global Shared RAM Config Lock Commit Register", offset: "0x42",
		bits: [
			{ name: "COMMIT_GS0", description: "GS0 RAM access protection and master select", size: "1", shift: "0", mask: "0x1" },
			{ name: "COMMIT_GS1", description: "GS1 RAM access protection and master select", size: "1", shift: "1", mask: "0x2" },
			{ name: "COMMIT_GS2", description: "GS2 RAM access protection and master select", size: "1", shift: "2", mask: "0x4" },
			{ name: "COMMIT_GS3", description: "GS3 RAM access protection and master select", size: "1", shift: "3", mask: "0x8" },
			{ name: "COMMIT_GS4", description: "GS4 RAM access protection and master select", size: "1", shift: "4", mask: "0x10" },
			{ name: "COMMIT_GS5", description: "GS5 RAM access protection and master select", size: "1", shift: "5", mask: "0x20" },
			{ name: "COMMIT_GS6", description: "GS6 RAM access protection and master select", size: "1", shift: "6", mask: "0x40" },
			{ name: "COMMIT_GS7", description: "GS7 RAM access protection and master select", size: "1", shift: "7", mask: "0x80" },
			{ name: "COMMIT_GS8", description: "GS8 RAM access protection and master select", size: "1", shift: "8", mask: "0x100" },
			{ name: "COMMIT_GS9", description: "GS9 RAM access protection and master select", size: "1", shift: "9", mask: "0x200" },
			{ name: "COMMIT_GS10", description: "GS10 RAM access protection and master select", size: "1", shift: "10", mask: "0x400" },
			{ name: "COMMIT_GS11", description: "GS11 RAM access protection and master select", size: "1", shift: "11", mask: "0x800" },
			{ name: "COMMIT_GS12", description: "GS12 RAM access protection and master select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "COMMIT_GS13", description: "GS13 RAM access protection and master select", size: "1", shift: "13", mask: "0x2000" },
			{ name: "COMMIT_GS14", description: "GS14 RAM access protection and master select", size: "1", shift: "14", mask: "0x4000" },
			{ name: "COMMIT_GS15", description: "GS15 RAM access protection and master select", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "GSXACCPROT0", description: "Global Shared RAM Config Register 0", offset: "0x48",
		bits: [
			{ name: "FETCHPROT_GS0", description: "Fetch Protection For GS0 RAM", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_GS0", description: "CPU WR Protection For GS0 RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRPROT_GS0", description: "DMA WR Protection For GS0 RAM", size: "1", shift: "2", mask: "0x4" },
			{ name: "FETCHPROT_GS1", description: "Fetch Protection For GS1 RAM", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPUWRPROT_GS1", description: "CPU WR Protection For GS1 RAM", size: "1", shift: "9", mask: "0x200" },
			{ name: "DMAWRPROT_GS1", description: "DMA WR Protection For GS1 RAM", size: "1", shift: "10", mask: "0x400" },
			{ name: "FETCHPROT_GS2", description: "Fetch Protection For GS2 RAM", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CPUWRPROT_GS2", description: "CPU WR Protection For GS2 RAM", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DMAWRPROT_GS2", description: "DMA WR Protection For GS2 RAM", size: "1", shift: "18", mask: "0x40000" },
			{ name: "FETCHPROT_GS3", description: "Fetch Protection For GS3 RAM", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "CPUWRPROT_GS3", description: "CPU WR Protection For GS3 RAM", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "DMAWRPROT_GS3", description: "DMA WR Protection For GS3 RAM", size: "1", shift: "26", mask: "0x4000000" },
		]
	},
	{ name: "GSXACCPROT1", description: "Global Shared RAM Config Register 1", offset: "0x4A",
		bits: [
			{ name: "FETCHPROT_GS4", description: "Fetch Protection For GS4 RAM", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_GS4", description: "CPU WR Protection For GS4 RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRPROT_GS4", description: "DMA WR Protection For GS4 RAM", size: "1", shift: "2", mask: "0x4" },
			{ name: "FETCHPROT_GS5", description: "Fetch Protection For GS5 RAM", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPUWRPROT_GS5", description: "CPU WR Protection For GS5 RAM", size: "1", shift: "9", mask: "0x200" },
			{ name: "DMAWRPROT_GS5", description: "DMA WR Protection For GS5RAM", size: "1", shift: "10", mask: "0x400" },
			{ name: "FETCHPROT_GS6", description: "Fetch Protection For GS6 RAM", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CPUWRPROT_GS6", description: "CPU WR Protection For GS6 RAM", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DMAWRPROT_GS6", description: "DMA WR Protection For GS6RAM", size: "1", shift: "18", mask: "0x40000" },
			{ name: "FETCHPROT_GS7", description: "Fetch Protection For GS7 RAM", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "CPUWRPROT_GS7", description: "CPU WR Protection For GS7 RAM", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "DMAWRPROT_GS7", description: "DMA WR Protection For GS7RAM", size: "1", shift: "26", mask: "0x4000000" },
		]
	},
	{ name: "GSXACCPROT2", description: "Global Shared RAM Config Register 2", offset: "0x4C",
		bits: [
			{ name: "FETCHPROT_GS8", description: "Fetch Protection For GS8 RAM", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_GS8", description: "CPU WR Protection For GS8 RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRPROT_GS8", description: "DMA WR Protection For GS8 RAM", size: "1", shift: "2", mask: "0x4" },
			{ name: "FETCHPROT_GS9", description: "Fetch Protection For GS9 RAM", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPUWRPROT_GS9", description: "CPU WR Protection For GS9 RAM", size: "1", shift: "9", mask: "0x200" },
			{ name: "DMAWRPROT_GS9", description: "DMA WR Protection For GS9RAM", size: "1", shift: "10", mask: "0x400" },
			{ name: "FETCHPROT_GS10", description: "Fetch Protection For GS10 RAM", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CPUWRPROT_GS10", description: "CPU WR Protection For GS10 RAM", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DMAWRPROT_GS10", description: "DMA WR Protection For GS10RAM", size: "1", shift: "18", mask: "0x40000" },
			{ name: "FETCHPROT_GS11", description: "Fetch Protection For GS11 RAM", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "CPUWRPROT_GS11", description: "CPU WR Protection For GS11 RAM", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "DMAWRPROT_GS11", description: "DMA WR Protection For GS11RAM", size: "1", shift: "26", mask: "0x4000000" },
		]
	},
	{ name: "GSXACCPROT3", description: "Global Shared RAM Config Register 3", offset: "0x4E",
		bits: [
			{ name: "FETCHPROT_GS12", description: "Fetch Protection For GS12 RAM", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_GS12", description: "CPU WR Protection For GS12 RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRPROT_GS12", description: "DMA WR Protection For GS12 RAM", size: "1", shift: "2", mask: "0x4" },
			{ name: "FETCHPROT_GS13", description: "Fetch Protection For GS13 RAM", size: "1", shift: "8", mask: "0x100" },
			{ name: "CPUWRPROT_GS13", description: "CPU WR Protection For GS13 RAM", size: "1", shift: "9", mask: "0x200" },
			{ name: "DMAWRPROT_GS13", description: "DMA WR Protection For GS13RAM", size: "1", shift: "10", mask: "0x400" },
			{ name: "FETCHPROT_GS14", description: "Fetch Protection For GS14 RAM", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CPUWRPROT_GS14", description: "CPU WR Protection For GS14 RAM", size: "1", shift: "17", mask: "0x20000" },
			{ name: "DMAWRPROT_GS14", description: "DMA WR Protection For GS14RAM", size: "1", shift: "18", mask: "0x40000" },
			{ name: "FETCHPROT_GS15", description: "Fetch Protection For GS15 RAM", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "CPUWRPROT_GS15", description: "CPU WR Protection For GS15 RAM", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "DMAWRPROT_GS15", description: "DMA WR Protection For GS15RAM", size: "1", shift: "26", mask: "0x4000000" },
		]
	},
	{ name: "GSXTEST", description: "Global Shared RAM TEST Register", offset: "0x50",
		bits: [
			{ name: "TEST_GS0", description: "Selects the different modes for GS0 RAM", size: "2", shift: "0", mask: "0x3" },
			{ name: "TEST_GS1", description: "Selects the different modes for GS1 RAM", size: "2", shift: "2", mask: "0xC" },
			{ name: "TEST_GS2", description: "Selects the different modes for GS2 RAM", size: "2", shift: "4", mask: "0x30" },
			{ name: "TEST_GS3", description: "Selects the different modes for GS3 RAM", size: "2", shift: "6", mask: "0xC0" },
			{ name: "TEST_GS4", description: "Selects the different modes for GS4 RAM", size: "2", shift: "8", mask: "0x300" },
			{ name: "TEST_GS5", description: "Selects the different modes for GS5 RAM", size: "2", shift: "10", mask: "0xC00" },
			{ name: "TEST_GS6", description: "Selects the different modes for GS6 RAM", size: "2", shift: "12", mask: "0x3000" },
			{ name: "TEST_GS7", description: "Selects the different modes for GS7 RAM", size: "2", shift: "14", mask: "0xC000" },
			{ name: "TEST_GS8", description: "Selects the different modes for GS8 RAM", size: "2", shift: "16", mask: "0x30000" },
			{ name: "TEST_GS9", description: "Selects the different modes for GS9 RAM", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "TEST_GS10", description: "Selects the different modes for GS10 RAM", size: "2", shift: "20", mask: "0x300000" },
			{ name: "TEST_GS11", description: "Selects the different modes for GS11 RAM", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "TEST_GS12", description: "Selects the different modes for GS12 RAM", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "TEST_GS13", description: "Selects the different modes for GS13 RAM", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "TEST_GS14", description: "Selects the different modes for GS14 RAM", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "TEST_GS15", description: "Selects the different modes for GS15 RAM", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "GSXINIT", description: "Global Shared RAM Init Register", offset: "0x52",
		bits: [
			{ name: "INIT_GS0", description: "RAM Initialization control for GS0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INIT_GS1", description: "RAM Initialization control for GS1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INIT_GS2", description: "RAM Initialization control for GS2 RAM.", size: "1", shift: "2", mask: "0x4" },
			{ name: "INIT_GS3", description: "RAM Initialization control for GS3 RAM.", size: "1", shift: "3", mask: "0x8" },
			{ name: "INIT_GS4", description: "RAM Initialization control for GS4 RAM.", size: "1", shift: "4", mask: "0x10" },
			{ name: "INIT_GS5", description: "RAM Initialization control for GS5 RAM.", size: "1", shift: "5", mask: "0x20" },
			{ name: "INIT_GS6", description: "RAM Initialization control for GS6 RAM.", size: "1", shift: "6", mask: "0x40" },
			{ name: "INIT_GS7", description: "RAM Initialization control for GS7 RAM.", size: "1", shift: "7", mask: "0x80" },
			{ name: "INIT_GS8", description: "RAM Initialization control for GS8 RAM.", size: "1", shift: "8", mask: "0x100" },
			{ name: "INIT_GS9", description: "RAM Initialization control for GS9 RAM.", size: "1", shift: "9", mask: "0x200" },
			{ name: "INIT_GS10", description: "RAM Initialization control for GS10 RAM.", size: "1", shift: "10", mask: "0x400" },
			{ name: "INIT_GS11", description: "RAM Initialization control for GS11 RAM.", size: "1", shift: "11", mask: "0x800" },
			{ name: "INIT_GS12", description: "RAM Initialization control for GS12 RAM.", size: "1", shift: "12", mask: "0x1000" },
			{ name: "INIT_GS13", description: "RAM Initialization control for GS13 RAM.", size: "1", shift: "13", mask: "0x2000" },
			{ name: "INIT_GS14", description: "RAM Initialization control for GS14 RAM.", size: "1", shift: "14", mask: "0x4000" },
			{ name: "INIT_GS15", description: "RAM Initialization control for GS15 RAM.", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "GSXINITDONE", description: "Global Shared RAM InitDone Status Register", offset: "0x54",
		bits: [
			{ name: "INITDONE_GS0", description: "RAM Initialization status for GS0 RAM.", size: "1", shift: "0", mask: "0x1" },
			{ name: "INITDONE_GS1", description: "RAM Initialization status for GS1 RAM.", size: "1", shift: "1", mask: "0x2" },
			{ name: "INITDONE_GS2", description: "RAM Initialization status for GS2 RAM.", size: "1", shift: "2", mask: "0x4" },
			{ name: "INITDONE_GS3", description: "RAM Initialization status for GS3 RAM.", size: "1", shift: "3", mask: "0x8" },
			{ name: "INITDONE_GS4", description: "RAM Initialization status for GS4 RAM.", size: "1", shift: "4", mask: "0x10" },
			{ name: "INITDONE_GS5", description: "RAM Initialization status for GS5 RAM.", size: "1", shift: "5", mask: "0x20" },
			{ name: "INITDONE_GS6", description: "RAM Initialization status for GS6 RAM.", size: "1", shift: "6", mask: "0x40" },
			{ name: "INITDONE_GS7", description: "RAM Initialization status for GS7 RAM.", size: "1", shift: "7", mask: "0x80" },
			{ name: "INITDONE_GS8", description: "RAM Initialization status for GS8 RAM.", size: "1", shift: "8", mask: "0x100" },
			{ name: "INITDONE_GS9", description: "RAM Initialization status for GS9 RAM.", size: "1", shift: "9", mask: "0x200" },
			{ name: "INITDONE_GS10", description: "RAM Initialization status for GS10 RAM.", size: "1", shift: "10", mask: "0x400" },
			{ name: "INITDONE_GS11", description: "RAM Initialization status for GS11 RAM.", size: "1", shift: "11", mask: "0x800" },
			{ name: "INITDONE_GS12", description: "RAM Initialization status for GS12 RAM.", size: "1", shift: "12", mask: "0x1000" },
			{ name: "INITDONE_GS13", description: "RAM Initialization status for GS13 RAM.", size: "1", shift: "13", mask: "0x2000" },
			{ name: "INITDONE_GS14", description: "RAM Initialization status for GS14 RAM.", size: "1", shift: "14", mask: "0x4000" },
			{ name: "INITDONE_GS15", description: "RAM Initialization status for GS15 RAM.", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "MSGXTEST", description: "Message RAM TEST Register", offset: "0x70",
		bits: [
			{ name: "TEST_CPUTOCPU", description: "CPU to CPU Mode Select", size: "2", shift: "0", mask: "0x3" },
			{ name: "TEST_CPUTOCLA1", description: "CPU to CLA1 MSG RAM Mode Select", size: "2", shift: "2", mask: "0xC" },
			{ name: "TEST_CLA1TOCPU", description: "CLA1 to CPU MSG RAM Mode Select", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "MSGXINIT", description: "Message RAM Init Register", offset: "0x72",
		bits: [
			{ name: "INIT_CPUTOCPU", description: "Initialization control for CPU to CPU MSG RAM", size: "1", shift: "0", mask: "0x1" },
			{ name: "INIT_CPUTOCLA1", description: "Initialization control for CPUTOCLA1 MSG RAM", size: "1", shift: "1", mask: "0x2" },
			{ name: "INIT_CLA1TOCPU", description: "Initialization control for CLA1TOCPU MSG RAM", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MSGXINITDONE", description: "Message RAM InitDone Status Register", offset: "0x74",
		bits: [
			{ name: "INITDONE_CPUTOCPU", description: "Initialization status for CPU to CPU MSG", size: "1", shift: "0", mask: "0x1" },
			{ name: "INITDONE_CPUTOCLA1", description: "Initialization status for CPU to CLA1", size: "1", shift: "1", mask: "0x2" },
			{ name: "INITDONE_CLA1TOCPU", description: "Initialization status for CLA1 to CPU", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "EMIF1LOCK", description: "EMIF1 Config Lock Register", offset: "0x0",
		bits: [
			{ name: "LOCK_EMIF1", description: "EMIF1 access protection and master select fields", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "EMIF1COMMIT", description: "EMIF1 Config Lock Commit Register", offset: "0x2",
		bits: [
			{ name: "COMMIT_EMIF1", description: "EMIF1 access protection and master select", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "EMIF1ACCPROT0", description: "EMIF1 Config Register 0", offset: "0x8",
		bits: [
			{ name: "FETCHPROT_EMIF1", description: "Fetch Protection For EMIF1", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_EMIF1", description: "CPU WR Protection For EMIF1", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRPROT_EMIF1", description: "DMA WR Protection For EMIF1", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "EMIF2LOCK", description: "EMIF2 Config Lock Register", offset: "0x0",
		bits: [
			{ name: "LOCK_EMIF2", description: "EMIF2 access protection and master select permanent", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "EMIF2COMMIT", description: "EMIF2 Config Lock Commit Register", offset: "0x2",
		bits: [
			{ name: "COMMIT_EMIF2", description: "EMIF2 access protection and master select", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "EMIF2ACCPROT0", description: "EMIF2 Config Register 0", offset: "0x8",
		bits: [
			{ name: "FETCHPROT_EMIF2", description: "Fetch Protection For EMIF2", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRPROT_EMIF2", description: "CPU WR Protection For EMIF2", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "NMAVFLG", description: "Non-Master Access Violation Flag Register", offset: "0x0",
		bits: [
			{ name: "CPUREAD", description: "Non Master CPU Read Access Violation Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Master CPU Write Access Violation Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Master CPU Fetch Access Violation Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Master DMA Write Access Violation Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLA1READ", description: "Non Master CLA1 Read Access Violation Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLA1WRITE", description: "Non Master CLA1 Write Access Violation Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLA1FETCH", description: "Non Master CLA1 Fetch Access Violation Flag", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "NMAVSET", description: "Non-Master Access Violation Flag Set Register", offset: "0x2",
		bits: [
			{ name: "CPUREAD", description: "Non Master CPU Read Access Violation Flag Set", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Master CPU Write Access Violation Flag Set", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Master CPU Fetch Access Violation Flag Set", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Master DMA Write Access Violation Flag Set", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLA1READ", description: "Non Master CLA1 Read Access Violation Flag Set", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLA1WRITE", description: "Non Master CLA1 Write Access Violation Flag Set", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLA1FETCH", description: "Non Master CLA1 Fetch Access Violation Flag Set", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "NMAVCLR", description: "Non-Master Access Violation Flag Clear Register", offset: "0x4",
		bits: [
			{ name: "CPUREAD", description: "Non Master CPU Read Access Violation Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Master CPU Write Access Violation Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Master CPU Fetch Access Violation Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Master DMA Write Access Violation Flag Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLA1READ", description: "Non Master CLA1 Read Access Violation Flag Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLA1WRITE", description: "Non Master CLA1 Write Access Violation Flag Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLA1FETCH", description: "Non Master CLA1 Fetch Access Violation Flag Clear", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "NMAVINTEN", description: "Non-Master Access Violation Interrupt Enable Register", offset: "0x6",
		bits: [
			{ name: "CPUREAD", description: "Non Master CPU Read Access Violation Interrupt", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Non Master CPU Write Access Violation Interrupt", size: "1", shift: "1", mask: "0x2" },
			{ name: "CPUFETCH", description: "Non Master CPU Fetch Access Violation Interrupt", size: "1", shift: "2", mask: "0x4" },
			{ name: "DMAWRITE", description: "Non Master DMA Write Access Violation Interrupt", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLA1READ", description: "Non Master CLA1 Read Access Violation Interrupt", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLA1WRITE", description: "Non Master CLA1 Write Access Violation Interrupt", size: "1", shift: "5", mask: "0x20" },
			{ name: "CLA1FETCH", description: "Non Master CLA1 Fetch Access Violation Interrupt", size: "1", shift: "6", mask: "0x40" },
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
	{ name: "NMDMAWRAVADDR", description: "Non-Master DMA Write Access Violation Address", offset: "0xE",
		bits: [
		]
	},
	{ name: "NMCLA1RDAVADDR", description: "Non-Master CLA1 Read Access Violation Address", offset: "0x10",
		bits: [
		]
	},
	{ name: "NMCLA1WRAVADDR", description: "Non-Master CLA1 Write Access Violation Address", offset: "0x12",
		bits: [
		]
	},
	{ name: "NMCLA1FAVADDR", description: "Non-Master CLA1 Fetch Access Violation Address", offset: "0x14",
		bits: [
		]
	},
	{ name: "MAVFLG", description: "Master Access Violation Flag Register", offset: "0x20",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Master DMA Write Access Violation Flag", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MAVSET", description: "Master Access Violation Flag Set Register", offset: "0x22",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Flag Set", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Flag Set", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Master DMA Write Access Violation Flag Set", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MAVCLR", description: "Master Access Violation Flag Clear Register", offset: "0x24",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Master DMA Write Access Violation Flag Clear", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MAVINTEN", description: "Master Access Violation Interrupt Enable Register", offset: "0x26",
		bits: [
			{ name: "CPUFETCH", description: "Master CPU Fetch Access Violation Interrupt Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "CPUWRITE", description: "Master CPU Write Access Violation Interrupt Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAWRITE", description: "Master DMA Write Access Violation Interrupt Enable", size: "1", shift: "2", mask: "0x4" },
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
	{ name: "UCERRFLG", description: "Uncorrectable Error Flag Register", offset: "0x0",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMARDERR", description: "DMA Uncorrectable Read Error Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLA1RDERR", description: "CLA1 Uncorrectable Read Error Flag", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "UCERRSET", description: "Uncorrectable Error Flag Set Register", offset: "0x2",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag Set", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMARDERR", description: "DMA Uncorrectable Read Error Flag Set", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLA1RDERR", description: "CLA1 Uncorrectable Read Error Flag Set", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "UCERRCLR", description: "Uncorrectable Error Flag Clear Register", offset: "0x4",
		bits: [
			{ name: "CPURDERR", description: "CPU Uncorrectable Read Error Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "DMARDERR", description: "DMA Uncorrectable Read Error Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLA1RDERR", description: "CLA1 Uncorrectable Read Error Flag Clear", size: "1", shift: "2", mask: "0x4" },
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
	{ name: "CERRCNT", description: "Correctable Error Count Register", offset: "0x2E",
		bits: [
		]
	},
	{ name: "CERRTHRES", description: "Correctable Error Threshold Value Register", offset: "0x30",
		bits: [
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
	{ name: "ROMWAITSTATE", description: "ROM Wait State Configuration Register", offset: "0x0",
		bits: [
			{ name: "WSDISABLE", description: "C28x ROM Wait State Enable/Disable Control", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "ROMPREFETCH", description: "ROM Prefetch Configuration Register", offset: "0x0",
		bits: [
			{ name: "PFENABLE", description: "ROM Prefetch Enable/Disable Control", size: "1", shift: "0", mask: "0x1" },
		]
	},
];
module.exports = {
	MEMCFGRegisters: MEMCFGRegisters,
}
