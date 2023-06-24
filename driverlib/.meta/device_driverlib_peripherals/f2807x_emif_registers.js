let EMIFRegisters = [
	{ name: "RCSR", description: "Revision Code and Status Register", offset: "0x0",
		bits: [
			{ name: "MINOR_REVISION", description: "Minor Revision.", size: "8", shift: "0", mask: "0xFF" },
			{ name: "MAJOR_REVISION", description: "Major Revision.", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "MODULE_ID", description: "EMIF module ID.", size: "14", shift: "16", mask: "0x3FFF0000" },
			{ name: "FR", description: "EMIF is running in full rate or half rate.", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "BE", description: "EMIF endian mode.", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "ASYNC_WCCR", description: "Async Wait Cycle Config Register", offset: "0x2",
		bits: [
			{ name: "MAX_EXT_WAIT", description: "Maximum Extended Wait cycles.", size: "8", shift: "0", mask: "0xFF" },
			{ name: "WP0", description: "Polarity for EMxWAIT.", size: "1", shift: "28", mask: "0x10000000" },
		]
	},
	{ name: "SDRAM_CR", description: "SDRAM (EMxCS0n) Config Register", offset: "0x4",
		bits: [
			{ name: "PAGESIGE", description: "Page Size.", size: "3", shift: "0", mask: "0x7" },
			{ name: "IBANK", description: "Internal Bank setup of SDRAM devices.", size: "3", shift: "4", mask: "0x70" },
			{ name: "BIT_11_9_LOCK", description: "Bits 11 to 9 are writable only if this bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "CL", description: "CAS Latency.", size: "3", shift: "9", mask: "0xE00" },
			{ name: "NM", description: "Narrow Mode.", size: "1", shift: "14", mask: "0x4000" },
			{ name: "PDWR", description: "Perform refreshes during Power Down.", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "PD", description: "Power Down.", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "SR", description: "Self Refresh.", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SDRAM_RCR", description: "SDRAM Refresh Control Register", offset: "0x6",
		bits: [
			{ name: "REFRESH_RATE", description: "Refresh Rate.", size: "13", shift: "0", mask: "0x1FFF" },
		]
	},
	{ name: "ASYNC_CS2_CR", description: "Async 1 (EMxCS2n) Config Register", offset: "0x8",
		bits: [
			{ name: "ASIZE", description: "Asynchronous Memory Size.", size: "2", shift: "0", mask: "0x3" },
			{ name: "TA", description: "Turn Around cycles.", size: "2", shift: "2", mask: "0xC" },
			{ name: "R_HOLD", description: "Read Strobe Hold cycles.", size: "3", shift: "4", mask: "0x70" },
			{ name: "R_STROBE", description: "Read Strobe Duration cycles.", size: "6", shift: "7", mask: "0x1F80" },
			{ name: "R_SETUP", description: "Read Strobe Setup cycles.", size: "4", shift: "13", mask: "0x1E000" },
			{ name: "W_HOLD", description: "Write Strobe Hold cycles.", size: "3", shift: "17", mask: "0xE0000" },
			{ name: "W_STROBE", description: "Write Strobe Duration cycles.", size: "6", shift: "20", mask: "0x3F00000" },
			{ name: "W_SETUP", description: "Write Strobe Setup cycles.", size: "4", shift: "26", mask: "0x3C000000" },
			{ name: "EW", description: "Extend Wait mode.", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "SS", description: "Select Strobe mode.", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "ASYNC_CS3_CR", description: "Async 2 (EMxCS3n) Config Register", offset: "0xA",
		bits: [
			{ name: "ASIZE", description: "Asynchronous Memory Size.", size: "2", shift: "0", mask: "0x3" },
			{ name: "TA", description: "Turn Around cycles.", size: "2", shift: "2", mask: "0xC" },
			{ name: "R_HOLD", description: "Read Strobe Hold cycles.", size: "3", shift: "4", mask: "0x70" },
			{ name: "R_STROBE", description: "Read Strobe Duration cycles.", size: "6", shift: "7", mask: "0x1F80" },
			{ name: "R_SETUP", description: "Read Strobe Setup cycles.", size: "4", shift: "13", mask: "0x1E000" },
			{ name: "W_HOLD", description: "Write Strobe Hold cycles.", size: "3", shift: "17", mask: "0xE0000" },
			{ name: "W_STROBE", description: "Write Strobe Duration cycles.", size: "6", shift: "20", mask: "0x3F00000" },
			{ name: "W_SETUP", description: "Write Strobe Setup cycles.", size: "4", shift: "26", mask: "0x3C000000" },
			{ name: "EW", description: "Extend Wait mode.", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "SS", description: "Select Strobe mode.", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "ASYNC_CS4_CR", description: "Async 3 (EMxCS4n) Config Register", offset: "0xC",
		bits: [
			{ name: "ASIZE", description: "Asynchronous Memory Size.", size: "2", shift: "0", mask: "0x3" },
			{ name: "TA", description: "Turn Around cycles.", size: "2", shift: "2", mask: "0xC" },
			{ name: "R_HOLD", description: "Read Strobe Hold cycles.", size: "3", shift: "4", mask: "0x70" },
			{ name: "R_STROBE", description: "Read Strobe Duration cycles.", size: "6", shift: "7", mask: "0x1F80" },
			{ name: "R_SETUP", description: "Read Strobe Setup cycles.", size: "4", shift: "13", mask: "0x1E000" },
			{ name: "W_HOLD", description: "Write Strobe Hold cycles.", size: "3", shift: "17", mask: "0xE0000" },
			{ name: "W_STROBE", description: "Write Strobe Duration cycles.", size: "6", shift: "20", mask: "0x3F00000" },
			{ name: "W_SETUP", description: "Write Strobe Setup cycles.", size: "4", shift: "26", mask: "0x3C000000" },
			{ name: "EW", description: "Extend Wait mode.", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "SS", description: "Select Strobe mode.", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "SDRAM_TR", description: "SDRAM Timing Register", offset: "0x10",
		bits: [
			{ name: "T_RRD", description: "Activate to Activate timing for different bank.", size: "3", shift: "4", mask: "0x70" },
			{ name: "T_RC", description: "Activate to Activate timing .", size: "4", shift: "8", mask: "0xF00" },
			{ name: "T_RAS", description: "Activate to Precharge timing.", size: "4", shift: "12", mask: "0xF000" },
			{ name: "T_WR", description: "Last Write to Precharge timing.", size: "3", shift: "16", mask: "0x70000" },
			{ name: "T_RCD", description: "Activate to Read/Write timing.", size: "3", shift: "20", mask: "0x700000" },
			{ name: "T_RP", description: "Precharge to Activate/Refresh timing.", size: "3", shift: "24", mask: "0x7000000" },
			{ name: "T_RFC", description: "Refresh/Load Mode to Refresh/Activate timing", size: "5", shift: "27", mask: "0xF8000000" },
		]
	},
	{ name: "TOTAL_SDRAM_AR", description: "Total SDRAM Accesses Register", offset: "0x18",
		bits: [
		]
	},
	{ name: "TOTAL_SDRAM_ACTR", description: "Total SDRAM Activate Register", offset: "0x1A",
		bits: [
		]
	},
	{ name: "SDR_EXT_TMNG", description: "SDRAM SR/PD Exit Timing Register", offset: "0x1E",
		bits: [
			{ name: "T_XS", description: "Self Refresh exit to new command timing.", size: "5", shift: "0", mask: "0x1F" },
		]
	},
	{ name: "INT_RAW", description: "Interrupt Raw Register", offset: "0x20",
		bits: [
			{ name: "AT", description: "Asynchronous Timeout.", size: "1", shift: "0", mask: "0x1" },
			{ name: "LT", description: "Line Trap.", size: "1", shift: "1", mask: "0x2" },
			{ name: "WR", description: "Wait Rise.", size: "4", shift: "2", mask: "0x3C" },
		]
	},
	{ name: "INT_MSK", description: "Interrupt Masked Register", offset: "0x22",
		bits: [
			{ name: "AT_MASKED", description: "Asynchronous Timeout.", size: "1", shift: "0", mask: "0x1" },
			{ name: "LT_MASKED", description: "Line Trap.", size: "1", shift: "1", mask: "0x2" },
			{ name: "WR_MASKED", description: "Wait Rise.", size: "4", shift: "2", mask: "0x3C" },
			{ name: "SET_AT_MASK_SET", description: "Asynchronous Timeout.", size: "1", shift: "0", mask: "0x1" },
			{ name: "SET_LT_MASK_SET", description: "Line Trap.", size: "1", shift: "1", mask: "0x2" },
			{ name: "SET_WR_MASK_SET", description: "Wait Rise.", size: "4", shift: "2", mask: "0x3C" },
			{ name: "CLR_AT_MASK_CLR", description: "Asynchronous Timeout.", size: "1", shift: "0", mask: "0x1" },
			{ name: "CLR_LT_MASK_CLR", description: "Line Trap.", size: "1", shift: "1", mask: "0x2" },
			{ name: "CLR_WR_MASK_CLR", description: "Wait Rise.", size: "4", shift: "2", mask: "0x3C" },
		]
	},
	{ name: "INT_MSK_SET", description: "Interrupt Mask Set Register", offset: "0x24",
		bits: [
			{ name: "AT_MASK_SET", description: "Asynchronous Timeout.", size: "1", shift: "0", mask: "0x1" },
			{ name: "LT_MASK_SET", description: "Line Trap.", size: "1", shift: "1", mask: "0x2" },
			{ name: "WR_MASK_SET", description: "Wait Rise.", size: "4", shift: "2", mask: "0x3C" },
		]
	},
	{ name: "INT_MSK_CLR", description: "Interrupt Mask Clear Register", offset: "0x26",
		bits: [
			{ name: "AT_MASK_CLR", description: "Asynchronous Timeout.", size: "1", shift: "0", mask: "0x1" },
			{ name: "LT_MASK_CLR", description: "Line Trap.", size: "1", shift: "1", mask: "0x2" },
			{ name: "WR_MASK_CLR", description: "Wait Rise.", size: "4", shift: "2", mask: "0x3C" },
		]
	},
];
module.exports = {
	EMIFRegisters: EMIFRegisters,
}
