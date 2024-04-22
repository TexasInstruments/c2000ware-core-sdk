let ERADRegisters = [
	{ name: "GLBL_EVENT_STAT", description: "Global Event Status Register", offset: "0x0",
		bits: [
			{ name: "HWBP1", description: "Enhanced Bus Comparator (EBC) Module Event Status", size: "1", shift: "0", mask: "0x1" },
			{ name: "HWBP2", description: "Enhanced Bus Comparator (EBC) Module Event Status", size: "1", shift: "1", mask: "0x2" },
			{ name: "HWBP3", description: "Enhanced Bus Comparator (EBC) Module Event Status", size: "1", shift: "2", mask: "0x4" },
			{ name: "HWBP4", description: "Enhanced Bus Comparator (EBC) Module Event Status", size: "1", shift: "3", mask: "0x8" },
			{ name: "HWBP5", description: "Enhanced Bus Comparator (EBC) Module Event Status", size: "1", shift: "4", mask: "0x10" },
			{ name: "HWBP6", description: "Enhanced Bus Comparator (EBC) Module Event Status", size: "1", shift: "5", mask: "0x20" },
			{ name: "HWBP7", description: "Enhanced Bus Comparator (EBC) Module Event Status", size: "1", shift: "6", mask: "0x40" },
			{ name: "HWBP8", description: "Enhanced Bus Comparator (EBC) Module Event Status", size: "1", shift: "7", mask: "0x80" },
			{ name: "CTM1", description: "Counter Module Event Status", size: "1", shift: "8", mask: "0x100" },
			{ name: "CTM2", description: "Counter Module Event Status", size: "1", shift: "9", mask: "0x200" },
			{ name: "CTM3", description: "Counter Module Event Status", size: "1", shift: "10", mask: "0x400" },
			{ name: "CTM4", description: "Counter Module Event Status", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "GLBL_HALT_STAT", description: "Global Halt Status Register", offset: "0x2",
		bits: [
			{ name: "HWBP1", description: "Enhanced Bus Comparator (EBC) Module Halt Status", size: "1", shift: "0", mask: "0x1" },
			{ name: "HWBP2", description: "Enhanced Bus Comparator (EBC) Module Halt Status", size: "1", shift: "1", mask: "0x2" },
			{ name: "HWBP3", description: "Enhanced Bus Comparator (EBC) Module Halt Status", size: "1", shift: "2", mask: "0x4" },
			{ name: "HWBP4", description: "Enhanced Bus Comparator (EBC) Module Halt Status", size: "1", shift: "3", mask: "0x8" },
			{ name: "HWBP5", description: "Enhanced Bus Comparator (EBC) Module Halt Status", size: "1", shift: "4", mask: "0x10" },
			{ name: "HWBP6", description: "Enhanced Bus Comparator (EBC) Module Halt Status", size: "1", shift: "5", mask: "0x20" },
			{ name: "HWBP7", description: "Enhanced Bus Comparator (EBC) Module Halt Status", size: "1", shift: "6", mask: "0x40" },
			{ name: "HWBP8", description: "Enhanced Bus Comparator (EBC) Module Halt Status", size: "1", shift: "7", mask: "0x80" },
			{ name: "CTM1", description: "Counter Module Halt Status", size: "1", shift: "8", mask: "0x100" },
			{ name: "CTM2", description: "Counter Module Halt Status", size: "1", shift: "9", mask: "0x200" },
			{ name: "CTM3", description: "Counter Module Halt Status", size: "1", shift: "10", mask: "0x400" },
			{ name: "CTM4", description: "Counter Module Halt Status", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "GLBL_ENABLE", description: "Global Enable Register", offset: "0x4",
		bits: [
			{ name: "HWBP1", description: "Enhanced Bus Comparator (EBC) Module Global Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "HWBP2", description: "Enhanced Bus Comparator (EBC) Module Global Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "HWBP3", description: "Enhanced Bus Comparator (EBC) Module Global Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "HWBP4", description: "Enhanced Bus Comparator (EBC) Module Global Enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "HWBP5", description: "Enhanced Bus Comparator (EBC) Module Global Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "HWBP6", description: "Enhanced Bus Comparator (EBC) Module Global Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "HWBP7", description: "Enhanced Bus Comparator (EBC) Module Global Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "HWBP8", description: "Enhanced Bus Comparator (EBC) Module Global Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "CTM1", description: "Counter Module Global Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "CTM2", description: "Counter Module Global Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "CTM3", description: "Counter Module Global Enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "CTM4", description: "Counter Module Global Enable", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "GLBL_CTM_RESET", description: "Global Counter Reset", offset: "0x6",
		bits: [
			{ name: "CTM1", description: "Global Reset for the counters", size: "1", shift: "0", mask: "0x1" },
			{ name: "CTM2", description: "Global Reset for the counters", size: "1", shift: "1", mask: "0x2" },
			{ name: "CTM3", description: "Global Reset for the counters", size: "1", shift: "2", mask: "0x4" },
			{ name: "CTM4", description: "Global Reset for the counters", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "GLBL_NMI_CTL", description: "Global Debug NMI control", offset: "0x8",
		bits: [
			{ name: "HWBP1", description: "Enhanced Bus Comparator (EBC) non-maskable interrupt", size: "1", shift: "0", mask: "0x1" },
			{ name: "HWBP2", description: "Enhanced Bus Comparator (EBC) non-maskable interrupt", size: "1", shift: "1", mask: "0x2" },
			{ name: "HWBP3", description: "Enhanced Bus Comparator (EBC) non-maskable interrupt", size: "1", shift: "2", mask: "0x4" },
			{ name: "HWBP4", description: "Enhanced Bus Comparator (EBC) non-maskable interrupt", size: "1", shift: "3", mask: "0x8" },
			{ name: "HWBP5", description: "Enhanced Bus Comparator (EBC) non-maskable interrupt", size: "1", shift: "4", mask: "0x10" },
			{ name: "HWBP6", description: "Enhanced Bus Comparator (EBC) non-maskable interrupt", size: "1", shift: "5", mask: "0x20" },
			{ name: "HWBP7", description: "Enhanced Bus Comparator (EBC) non-maskable interrupt", size: "1", shift: "6", mask: "0x40" },
			{ name: "HWBP8", description: "Enhanced Bus Comparator (EBC) non-maskable interrupt", size: "1", shift: "7", mask: "0x80" },
			{ name: "CTM1", description: "Counter  non-maskable interrupt enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "CTM2", description: "Counter  non-maskable interrupt enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "CTM3", description: "Counter  non-maskable interrupt enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "CTM4", description: "Counter  non-maskable interrupt enable", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "GLBL_OWNER", description: "Global Ownership", offset: "0xA",
		bits: [
			{ name: "OWNER", description: "Global Ownership Bits", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "GLBL_EVENT_AND_MASK", description: "Global Bus Comparator Event AND Mask Register", offset: "0xC",
		bits: [
			{ name: "MASK1_HWBP1", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "0", mask: "0x1" },
			{ name: "MASK1_HWBP2", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "1", mask: "0x2" },
			{ name: "MASK1_HWBP3", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "2", mask: "0x4" },
			{ name: "MASK1_HWBP4", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "3", mask: "0x8" },
			{ name: "MASK1_HWBP5", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "4", mask: "0x10" },
			{ name: "MASK1_HWBP6", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "5", mask: "0x20" },
			{ name: "MASK1_HWBP7", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "6", mask: "0x40" },
			{ name: "MASK1_HWBP8", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "7", mask: "0x80" },
			{ name: "MASK2_HWBP1", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "8", mask: "0x100" },
			{ name: "MASK2_HWBP2", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "9", mask: "0x200" },
			{ name: "MASK2_HWBP3", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "10", mask: "0x400" },
			{ name: "MASK2_HWBP4", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "11", mask: "0x800" },
			{ name: "MASK2_HWBP5", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "12", mask: "0x1000" },
			{ name: "MASK2_HWBP6", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "13", mask: "0x2000" },
			{ name: "MASK2_HWBP7", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "14", mask: "0x4000" },
			{ name: "MASK2_HWBP8", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "15", mask: "0x8000" },
			{ name: "MASK3_HWBP1", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "16", mask: "0x10000" },
			{ name: "MASK3_HWBP2", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "17", mask: "0x20000" },
			{ name: "MASK3_HWBP3", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "18", mask: "0x40000" },
			{ name: "MASK3_HWBP4", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "19", mask: "0x80000" },
			{ name: "MASK3_HWBP5", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "20", mask: "0x100000" },
			{ name: "MASK3_HWBP6", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "21", mask: "0x200000" },
			{ name: "MASK3_HWBP7", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "22", mask: "0x400000" },
			{ name: "MASK3_HWBP8", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "23", mask: "0x800000" },
			{ name: "MASK4_HWBP1", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "MASK4_HWBP2", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "MASK4_HWBP3", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "MASK4_HWBP4", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "MASK4_HWBP5", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "MASK4_HWBP6", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "MASK4_HWBP7", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "MASK4_HWBP8", description: "Enhanced Bus Comparator (EBC) AND", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "GLBL_EVENT_OR_MASK", description: "Global Bus Comparator Event OR Mask Register", offset: "0xE",
		bits: [
			{ name: "MASK1_HWBP1", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "0", mask: "0x1" },
			{ name: "MASK1_HWBP2", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "1", mask: "0x2" },
			{ name: "MASK1_HWBP3", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "2", mask: "0x4" },
			{ name: "MASK1_HWBP4", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "3", mask: "0x8" },
			{ name: "MASK1_HWBP5", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "4", mask: "0x10" },
			{ name: "MASK1_HWBP6", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "5", mask: "0x20" },
			{ name: "MASK1_HWBP7", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "6", mask: "0x40" },
			{ name: "MASK1_HWBP8", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "7", mask: "0x80" },
			{ name: "MASK2_HWBP1", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "8", mask: "0x100" },
			{ name: "MASK2_HWBP2", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "9", mask: "0x200" },
			{ name: "MASK2_HWBP3", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "10", mask: "0x400" },
			{ name: "MASK2_HWBP4", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "11", mask: "0x800" },
			{ name: "MASK2_HWBP5", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "12", mask: "0x1000" },
			{ name: "MASK2_HWBP6", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "13", mask: "0x2000" },
			{ name: "MASK2_HWBP7", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "14", mask: "0x4000" },
			{ name: "MASK2_HWBP8", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "15", mask: "0x8000" },
			{ name: "MASK3_HWBP1", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "16", mask: "0x10000" },
			{ name: "MASK3_HWBP2", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "17", mask: "0x20000" },
			{ name: "MASK3_HWBP3", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "18", mask: "0x40000" },
			{ name: "MASK3_HWBP4", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "19", mask: "0x80000" },
			{ name: "MASK3_HWBP5", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "20", mask: "0x100000" },
			{ name: "MASK3_HWBP6", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "21", mask: "0x200000" },
			{ name: "MASK3_HWBP7", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "22", mask: "0x400000" },
			{ name: "MASK3_HWBP8", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "23", mask: "0x800000" },
			{ name: "MASK4_HWBP1", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "MASK4_HWBP2", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "MASK4_HWBP3", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "MASK4_HWBP4", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "MASK4_HWBP5", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "MASK4_HWBP6", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "MASK4_HWBP7", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "MASK4_HWBP8", description: "Enhanced Bus Comparator (EBC) OR", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "GLBL_AND_EVENT_INT_MASK", description: "Global AND Event Interrupt Mask Register", offset: "0x10",
		bits: [
			{ name: "RTOSINT_MASK1", description: "RTOSINT generation mask for global", size: "1", shift: "0", mask: "0x1" },
			{ name: "RTOSINT_MASK2", description: "RTOSINT generation mask for global", size: "1", shift: "1", mask: "0x2" },
			{ name: "RTOSINT_MASK3", description: "RTOSINT generation mask for global", size: "1", shift: "2", mask: "0x4" },
			{ name: "RTOSINT_MASK4", description: "RTOSINT generation mask for global", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "GLBL_OR_EVENT_INT_MASK", description: "Global OR Event Interrupt Mask Register", offset: "0x12",
		bits: [
			{ name: "RTOSINT_MASK1", description: "RTOSINT generation mask for global OR", size: "1", shift: "0", mask: "0x1" },
			{ name: "RTOSINT_MASK2", description: "RTOSINT generation mask for global OR", size: "1", shift: "1", mask: "0x2" },
			{ name: "RTOSINT_MASK3", description: "RTOSINT generation mask for global OR", size: "1", shift: "2", mask: "0x4" },
			{ name: "RTOSINT_MASK4", description: "RTOSINT generation mask for global OR", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "HWBP_MASK", description: "HWBP (EBC) Mask Register", offset: "0x0",
		bits: [
		]
	},
	{ name: "HWBP_REF", description: "HWBP (EBC) Reference Register", offset: "0x2",
		bits: [
		]
	},
	{ name: "HWBP_CLEAR", description: "HWBP (EBC) Clear Register", offset: "0x4",
		bits: [
			{ name: "EVENT_CLR", description: "Event Clear register", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "HWBP_CNTL", description: "HWBP (EBC) Control Register", offset: "0x6",
		bits: [
			{ name: "BUS_SEL", description: "Bus select bits", size: "4", shift: "1", mask: "0x1E" },
			{ name: "STOP", description: "Stop bit (Halt/No Halt of CPU)", size: "1", shift: "5", mask: "0x20" },
			{ name: "RTOSINT", description: "RTOSINT bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "COMP_MODE", description: "Compare mode", size: "3", shift: "7", mask: "0x380" },
		]
	},
	{ name: "HWBP_STATUS", description: "HWBP (EBC) Status Register", offset: "0x7",
		bits: [
			{ name: "EVENT_FIRED", description: "HWBP (EBC) Event Fired bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "MODULE_ID", description: "Identification bits", size: "6", shift: "8", mask: "0x3F00" },
			{ name: "STATUS", description: "Status bits", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "CTM_CNTL", description: "Counter Control Register", offset: "0x0",
		bits: [
			{ name: "START_STOP_MODE", description: "Start_stop mode bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "EVENT_MODE", description: "Event mode bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "RST_ON_MATCH", description: "Reset_on_match bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "STOP", description: "Stop bit (Halt/No Halt of CPU)", size: "1", shift: "6", mask: "0x40" },
			{ name: "RTOSINT", description: "RTOSINT bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "START_STOP_CUMULATIVE", description: "Start stop cumulative bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "RST_EN", description: "Enable Reset", size: "1", shift: "10", mask: "0x400" },
			{ name: "CNT_INP_SEL_EN", description: "Counter Input Select Enable", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "CTM_STATUS", description: "Counter Status Register", offset: "0x1",
		bits: [
			{ name: "EVENT_FIRED", description: "Counter Event Fired bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "OVERFLOW", description: "Counter Overflowed", size: "1", shift: "1", mask: "0x2" },
			{ name: "MODULE_ID", description: "Identification bits", size: "10", shift: "2", mask: "0xFFC" },
			{ name: "STATUS", description: "Status bits", size: "4", shift: "12", mask: "0xF000" },
		]
	},
	{ name: "CTM_REF", description: "Counter Reference Register", offset: "0x2",
		bits: [
		]
	},
	{ name: "CTM_COUNT", description: "Counter Current Value Register", offset: "0x4",
		bits: [
		]
	},
	{ name: "CTM_MAX_COUNT", description: "Counter Max Count Value Register", offset: "0x6",
		bits: [
		]
	},
	{ name: "CTM_INPUT_SEL", description: "Counter Input Select Register", offset: "0x8",
		bits: [
			{ name: "CNT_INP_SEL", description: "Counter Input Select", size: "8", shift: "0", mask: "0xFF" },
			{ name: "STA_INP_SEL", description: "Counter Sart Input Select", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "2_STO_INP_SEL", description: "Counter Stop Input Select", size: "8", shift: "0", mask: "0xFF" },
			{ name: "2_RST_INP_SEL", description: "Counter Reset input Select", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "CTM_CLEAR", description: "Counter Clear Register", offset: "0x9",
		bits: [
			{ name: "EVENT_CLEAR", description: "Clear EVENT_FIRED", size: "1", shift: "0", mask: "0x1" },
			{ name: "OVERFLOW_CLEAR", description: "Clear OVERFLOW", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "CTM_INPUT_SEL_2", description: "Counter Input Select Extension Register", offset: "0xA",
		bits: [
			{ name: "STO_INP_SEL", description: "Counter Stop Input Select", size: "8", shift: "0", mask: "0xFF" },
			{ name: "RST_INP_SEL", description: "Counter Reset input Select", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "CTM_INPUT_COND", description: "Counter Input Conditioning Register", offset: "0xB",
		bits: [
			{ name: "CTM_INP_INV", description: "Counter Input Invert", size: "1", shift: "0", mask: "0x1" },
			{ name: "CTM_INP_SYNCH", description: "Counter input synchronizer enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "STA_INP_INV", description: "Start input Invert", size: "1", shift: "4", mask: "0x10" },
			{ name: "STA_INP_SYNCH", description: "Start input synchronizer enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "STO_INP_INV", description: "Stop input Invert", size: "1", shift: "8", mask: "0x100" },
			{ name: "STO_INP_SYNCH", description: "Stop input synchronizer enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "RST_INP_INV", description: "Reset input Invert", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RST_INP_SYNCH", description: "Reset input synchronizer enable", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "CRC_GLOBAL_CTRL", description: "CRC_GLOBAL_CRTL", offset: "0x0",
		bits: [
			{ name: "CRC1_INIT", description: "Initialize CRC Module 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "CRC2_INIT", description: "Initialize CRC Module 2", size: "1", shift: "1", mask: "0x2" },
			{ name: "CRC3_INIT", description: "Initialize CRC Module 3", size: "1", shift: "2", mask: "0x4" },
			{ name: "CRC4_INIT", description: "Initialize CRC Module 4", size: "1", shift: "3", mask: "0x8" },
			{ name: "CRC5_INIT", description: "Initialize CRC Module 5", size: "1", shift: "4", mask: "0x10" },
			{ name: "CRC6_INIT", description: "Initialize CRC Module 6", size: "1", shift: "5", mask: "0x20" },
			{ name: "CRC7_INIT", description: "Initialize CRC Module 7", size: "1", shift: "6", mask: "0x40" },
			{ name: "CRC8_INIT", description: "Initialize CRC Module 8", size: "1", shift: "7", mask: "0x80" },
			{ name: "CRC1_EN", description: "Enable CRC Module 1", size: "1", shift: "8", mask: "0x100" },
			{ name: "CRC2_EN", description: "Enable CRC Module 2", size: "1", shift: "9", mask: "0x200" },
			{ name: "CRC3_EN", description: "Enable CRC Module 3", size: "1", shift: "10", mask: "0x400" },
			{ name: "CRC4_EN", description: "Enable CRC Module 4", size: "1", shift: "11", mask: "0x800" },
			{ name: "CRC5_EN", description: "Enable CRC Module 5", size: "1", shift: "12", mask: "0x1000" },
			{ name: "CRC6_EN", description: "Enable CRC Module 6", size: "1", shift: "13", mask: "0x2000" },
			{ name: "CRC7_EN", description: "Enable CRC Module 7", size: "1", shift: "14", mask: "0x4000" },
			{ name: "CRC8_EN", description: "Enable CRC Module 8", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CRC_CURRENT", description: "CRC_CURRENT", offset: "0x0",
		bits: [
		]
	},
	{ name: "CRC_SEED", description: "CRC SEED value", offset: "0x2",
		bits: [
		]
	},
	{ name: "CRC_QUALIFIER", description: "CRC_QUALIFIER", offset: "0x4",
		bits: [
			{ name: "CRC_QUALIFIER", description: "CRC Qualifier Register", size: "5", shift: "0", mask: "0x1F" },
		]
	},
	{ name: "PCTRACE_GLOBAL", description: "PCTRACE_GLOBAL", offset: "0x0",
		bits: [
			{ name: "EN", description: "Enable PC  trace", size: "1", shift: "0", mask: "0x1" },
			{ name: "INIT", description: "Initialize the PC Trace and buffer pointer", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "PCTRACE_BUFFER", description: "PCTRACE_BUFFER", offset: "0x1",
		bits: [
			{ name: "PTR", description: "Trace Buffer Pointer", size: "10", shift: "0", mask: "0x3FF" },
			{ name: "BUFFER_FULL", description: "Trace Buffer Full", size: "1", shift: "15", mask: "0x8000" },
			{ name: "BASE_PROGRAM_COUNTER", description: "Program Counter", size: "22", shift: "0", mask: "0x3FFFFF" },
			{ name: "BASE_BLOCKED", description: "Access blocked due to security", size: "1", shift: "22", mask: "0x400000" },
		]
	},
	{ name: "PCTRACE_QUAL1", description: "PCTRACE_QUAL1", offset: "0x2",
		bits: [
			{ name: "WINDOWED_INP_SEL", description: "Windowed trace qualifier", size: "8", shift: "0", mask: "0xFF" },
			{ name: "TRACE_MODE", description: "Trace qualifier mode", size: "2", shift: "16", mask: "0x30000" },
			{ name: "WINDOWED_INP_INV", description: "Windowed trace Input Invert", size: "1", shift: "18", mask: "0x40000" },
			{ name: "WINDOWED_INP_SYNCH", description: "Windowed trace input synchronizer", size: "1", shift: "19", mask: "0x80000" },
			{ name: "START_INP_INV", description: "Start input Invert", size: "1", shift: "20", mask: "0x100000" },
			{ name: "START_INP_SYNCH", description: "Start input synchronizer enable", size: "1", shift: "21", mask: "0x200000" },
			{ name: "STOP_INP_INV", description: "Stop input Invert", size: "1", shift: "22", mask: "0x400000" },
			{ name: "STOP_INP_SYNCH", description: "Stop input synchronizer enable", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "PCTRACE_QUAL2", description: "PCTRACE_QUAL2", offset: "0x4",
		bits: [
			{ name: "START_INP_SEL", description: "Trace Start event select", size: "8", shift: "0", mask: "0xFF" },
			{ name: "STOP_INP_SEL", description: "Trace Stop event select", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "PCTRACE_LOGPC_SOFTENABLE", description: "PCTRACE_LOGPC_SOFTENABLE", offset: "0x6",
		bits: [
			{ name: "PC_SOFTENABLE", description: "PC when PC Trace was last", size: "22", shift: "0", mask: "0x3FFFFF" },
		]
	},
	{ name: "PCTRACE_LOGPC_SOFTDISABLE", description: "PCTRACE_LOGPC_SOFTDISABLE", offset: "0x8",
		bits: [
			{ name: "PC_SOFTDISABLE", description: "PC when PC Trace was last", size: "22", shift: "0", mask: "0x3FFFFF" },
		]
	},
	{ name: "PCTRACE_BUFFER_BASE(i)", description: "(0 <= i < 1024)", offset: "(0x0U + ((i) * 0x2U))",
		bits: [
		]
	},
];
module.exports = {
	ERADRegisters: ERADRegisters,
}
