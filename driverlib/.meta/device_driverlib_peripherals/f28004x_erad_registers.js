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
	{ name: "GLBL_OWNER", description: "Global Ownership", offset: "0xA",
		bits: [
			{ name: "OWNER", description: "Global Ownership Bits", size: "2", shift: "0", mask: "0x3" },
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
			{ name: "BUS_SEL", description: "Bus select bits", size: "3", shift: "2", mask: "0x1C" },
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
			{ name: "RST_EN", description: "Enable Reset", size: "1", shift: "10", mask: "0x400" },
			{ name: "RST_INP_SEL", description: "Reset Input select", size: "5", shift: "11", mask: "0xF800" },
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
			{ name: "CTM_INP_SEL_EN", description: "Count input select enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "CNT_INP_SEL", description: "Count input select", size: "5", shift: "1", mask: "0x3E" },
			{ name: "STA_INP_SEL", description: "Start input select", size: "5", shift: "6", mask: "0x7C0" },
			{ name: "STO_INP_SEL", description: "Stop input select", size: "5", shift: "11", mask: "0xF800" },
		]
	},
	{ name: "CTM_CLEAR", description: "Counter Clear Register", offset: "0x9",
		bits: [
			{ name: "EVENT_CLEAR", description: "Clear EVENT_FIRED", size: "1", shift: "0", mask: "0x1" },
			{ name: "OVERFLOW_CLEAR", description: "Clear OVERFLOW", size: "1", shift: "1", mask: "0x2" },
		]
	},
];
module.exports = {
	ERADRegisters: ERADRegisters,
}
