let FLASHRegisters = [
	{ name: "FRDCNTL", description: "Flash Read Control Register", offset: "0x0",
		bits: [
			{ name: "RWAIT", description: "Random Read Waitstate", size: "4", shift: "8", mask: "0xF00" },
		]
	},
	{ name: "FBAC", description: "Flash Bank Access Control Register", offset: "0x1E",
		bits: [
			{ name: "BAGP", description: "Bank Active Grace Period", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "FBFALLBACK", description: "Flash Bank Fallback Power Register", offset: "0x20",
		bits: [
			{ name: "BNKPWR0", description: "Bank Power Mode of BANK0", size: "2", shift: "0", mask: "0x3" },
			{ name: "BNKPWR1", description: "Bank Power Mode of BANK1", size: "2", shift: "2", mask: "0xC" },
			{ name: "BNKPWR2", description: "Bank Power Mode of BANK2", size: "2", shift: "4", mask: "0x30" },
		]
	},
	{ name: "FBPRDY", description: "Flash Bank Pump Ready Register", offset: "0x22",
		bits: [
			{ name: "BANK0RDY", description: "Flash Bank Active Power State", size: "1", shift: "0", mask: "0x1" },
			{ name: "BANK1RDY", description: "Flash Bank Active Power State", size: "1", shift: "1", mask: "0x2" },
			{ name: "BANK2RDY", description: "Flash Bank Active Power State", size: "1", shift: "2", mask: "0x4" },
			{ name: "PUMPRDY", description: "Flash Pump Active Power Mode", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "FPAC1", description: "Flash Pump Access Control Register 1", offset: "0x24",
		bits: [
			{ name: "PMPPWR", description: "Charge Pump Fallback Power Mode", size: "1", shift: "0", mask: "0x1" },
			{ name: "PSLEEP", description: "Pump Sleep Down Count", size: "12", shift: "16", mask: "0xFFF0000" },
		]
	},
	{ name: "FPAC2", description: "Flash Pump Access Control Register 2", offset: "0x26",
		bits: [
			{ name: "PAGP", description: "Pump Active Grace Period", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "FMSTAT", description: "Flash Module Status Register", offset: "0x2A",
		bits: [
			{ name: "PSUSP", description: "Program Suspend.", size: "1", shift: "1", mask: "0x2" },
			{ name: "ESUSP", description: "Erase Suspend.", size: "1", shift: "2", mask: "0x4" },
			{ name: "VOLTSTAT", description: "Flash Pump Power Status", size: "1", shift: "3", mask: "0x8" },
			{ name: "CSTAT", description: "Command Fail Status", size: "1", shift: "4", mask: "0x10" },
			{ name: "INVDAT", description: "Invalid Data", size: "1", shift: "5", mask: "0x20" },
			{ name: "PGM", description: "Program Operation Status", size: "1", shift: "6", mask: "0x40" },
			{ name: "ERS", description: "Erase Operation Status", size: "1", shift: "7", mask: "0x80" },
			{ name: "BUSY", description: "Busy Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "EV", description: "Erase Verify Status", size: "1", shift: "10", mask: "0x400" },
			{ name: "PGV", description: "Programming Verify Status", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "FRD_INTF_CTRL", description: "Flash Read Interface Control Register", offset: "0x180",
		bits: [
			{ name: "PREFETCH_EN", description: "Prefetch Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "DATA_CACHE_EN", description: "Data Cache Enable", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "ECC_ENABLE", description: "ECC Enable", offset: "0x0",
		bits: [
			{ name: "ENABLE", description: "Enable ECC", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "SINGLE_ERR_ADDR_LOW", description: "Single Error Address Low", offset: "0x2",
		bits: [
		]
	},
	{ name: "SINGLE_ERR_ADDR_HIGH", description: "Single Error Address High", offset: "0x4",
		bits: [
		]
	},
	{ name: "UNC_ERR_ADDR_LOW", description: "Uncorrectable Error Address Low", offset: "0x6",
		bits: [
		]
	},
	{ name: "UNC_ERR_ADDR_HIGH", description: "Uncorrectable Error Address High", offset: "0x8",
		bits: [
		]
	},
	{ name: "ERR_STATUS", description: "Error Status", offset: "0xA",
		bits: [
			{ name: "FAIL_0_L", description: "Lower 64bits Single Bit Error Corrected Value 0", size: "1", shift: "0", mask: "0x1" },
			{ name: "FAIL_1_L", description: "Lower 64bits Single Bit Error Corrected Value 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "UNC_ERR_L", description: "Lower 64 bits Uncorrectable error occurred", size: "1", shift: "2", mask: "0x4" },
			{ name: "FAIL_0_H", description: "Upper 64bits Single Bit Error Corrected Value 0", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FAIL_1_H", description: "Upper 64bits Single Bit Error Corrected Value 1", size: "1", shift: "17", mask: "0x20000" },
			{ name: "UNC_ERR_H", description: "Upper 64 bits Uncorrectable error occurred", size: "1", shift: "18", mask: "0x40000" },
			{ name: "CLR_FAIL_0_L_CLR", description: "Lower 64bits Single Bit Error Corrected", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLR_FAIL_1_L_CLR", description: "Lower 64bits Single Bit Error Corrected", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLR_UNC_ERR_L_CLR", description: "Lower 64 bits Uncorrectable error", size: "1", shift: "2", mask: "0x4" },
			{ name: "CLR_FAIL_0_H_CLR", description: "Upper 64bits Single Bit Error Corrected", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CLR_FAIL_1_H_CLR", description: "Upper 64bits Single Bit Error Corrected", size: "1", shift: "17", mask: "0x20000" },
			{ name: "CLR_UNC_ERR_H_CLR", description: "Upper 64 bits Uncorrectable error", size: "1", shift: "18", mask: "0x40000" },
		]
	},
	{ name: "ERR_POS", description: "Error Position", offset: "0xC",
		bits: [
			{ name: "ERR_POS_L", description: "Bit Position of Single bit Error in lower 64", size: "6", shift: "0", mask: "0x3F" },
			{ name: "ERR_TYPE_L", description: "Error Type in lower 64 bits", size: "1", shift: "8", mask: "0x100" },
			{ name: "ERR_POS_H", description: "Bit Position of Single bit Error in upper 64", size: "6", shift: "16", mask: "0x3F0000" },
			{ name: "ERR_TYPE_H", description: "Error Type in upper 64 bits", size: "1", shift: "24", mask: "0x1000000" },
		]
	},
	{ name: "ERR_STATUS_CLR", description: "Error Status Clear", offset: "0xE",
		bits: [
			{ name: "FAIL_0_L_CLR", description: "Lower 64bits Single Bit Error Corrected", size: "1", shift: "0", mask: "0x1" },
			{ name: "FAIL_1_L_CLR", description: "Lower 64bits Single Bit Error Corrected", size: "1", shift: "1", mask: "0x2" },
			{ name: "UNC_ERR_L_CLR", description: "Lower 64 bits Uncorrectable error", size: "1", shift: "2", mask: "0x4" },
			{ name: "FAIL_0_H_CLR", description: "Upper 64bits Single Bit Error Corrected", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FAIL_1_H_CLR", description: "Upper 64bits Single Bit Error Corrected", size: "1", shift: "17", mask: "0x20000" },
			{ name: "UNC_ERR_H_CLR", description: "Upper 64 bits Uncorrectable error", size: "1", shift: "18", mask: "0x40000" },
		]
	},
	{ name: "ERR_CNT", description: "Error Control", offset: "0x10",
		bits: [
			{ name: "ERR_CNT", description: "Error counter", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "ERR_THRESHOLD", description: "Error Threshold", offset: "0x12",
		bits: [
			{ name: "ERR_THRESHOLD", description: "Error Threshold", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "ERR_INTFLG", description: "Error Interrupt Flag", offset: "0x14",
		bits: [
			{ name: "SINGLE_ERR_INTFLG", description: "Single Error Interrupt Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "UNC_ERR_INTFLG", description: "Uncorrectable Interrupt Flag", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "ERR_INTCLR", description: "Error Interrupt Flag Clear", offset: "0x16",
		bits: [
			{ name: "SINGLE_ERR_INTCLR", description: "Single Error Interrupt Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "UNC_ERR_INTCLR", description: "Uncorrectable Interrupt Flag Clear", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "FDATAH_TEST", description: "Data High Test", offset: "0x18",
		bits: [
		]
	},
	{ name: "FDATAL_TEST", description: "Data Low Test", offset: "0x1A",
		bits: [
		]
	},
	{ name: "FADDR_TEST", description: "ECC Test Address", offset: "0x1C",
		bits: [
			{ name: "ADDRL", description: "ECC Address Low", size: "13", shift: "3", mask: "0xFFF8" },
			{ name: "ADDRH", description: "ECC Address High", size: "6", shift: "16", mask: "0x3F0000" },
		]
	},
	{ name: "FECC_TEST", description: "ECC Test Address", offset: "0x1E",
		bits: [
			{ name: "ECC", description: "ECC Control Bits", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "FECC_CTRL", description: "ECC Control", offset: "0x20",
		bits: [
			{ name: "ECC_TEST_EN", description: "Enable ECC Test Logic", size: "1", shift: "0", mask: "0x1" },
			{ name: "ECC_SELECT", description: "ECC Bit Select", size: "1", shift: "1", mask: "0x2" },
			{ name: "DO_ECC_CALC", description: "Enable ECC Calculation", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "FOUTH_TEST", description: "Test Data Out High", offset: "0x22",
		bits: [
		]
	},
	{ name: "FOUTL_TEST", description: "Test Data Out Low", offset: "0x24",
		bits: [
		]
	},
	{ name: "FECC_STATUS", description: "ECC Status", offset: "0x26",
		bits: [
			{ name: "SINGLE_ERR", description: "Test Result is Single Bit Error", size: "1", shift: "0", mask: "0x1" },
			{ name: "UNC_ERR", description: "Test Result is Uncorrectable Error", size: "1", shift: "1", mask: "0x2" },
			{ name: "DATA_ERR_POS", description: "Holds Bit Position of Error", size: "6", shift: "2", mask: "0xFC" },
			{ name: "ERR_TYPE", description: "Holds Bit Position of 8 Check Bits of Error", size: "1", shift: "8", mask: "0x100" },
		]
	},
];
module.exports = {
	FLASHRegisters: FLASHRegisters,
}
