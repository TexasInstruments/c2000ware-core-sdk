let CLBRegisters = [
	{ name: "COUNT_RESET", description: "Counter Block RESET", offset: "0x2",
		bits: [
			{ name: "SEL_0", description: "Count Reset Select 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "Count Reset Select 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "Count Reset Select 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "COUNT_MODE_1", description: "Counter Block MODE_1", offset: "0x4",
		bits: [
			{ name: "SEL_0", description: "Counter mode 1 select 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "Counter mode 1 select 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "Counter mode 1 select 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "COUNT_MODE_0", description: "Counter Block MODE_0", offset: "0x6",
		bits: [
			{ name: "SEL_0", description: "Counter mode 0 select 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "Counter mode 0 select 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "Counter mode 0 select 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "COUNT_EVENT", description: "Counter Block EVENT", offset: "0x8",
		bits: [
			{ name: "SEL_0", description: "Counter event select 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "Counter event select 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "Counter event select 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "FSM_EXTRA_IN0", description: "FSM Extra EXT_IN0", offset: "0xA",
		bits: [
			{ name: "SEL_0", description: "FSM extra ext input select 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "FSM extra ext input select 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "FSM extra ext input select 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "FSM_EXTERNAL_IN0", description: "FSM EXT_IN0", offset: "0xC",
		bits: [
			{ name: "SEL_0", description: "FSM EXT_IN0 select input for unit 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "FSM EXT_IN0 select input for unit 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "FSM EXT_IN0 select input for unit 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "FSM_EXTERNAL_IN1", description: "FSM_EXT_IN1", offset: "0xE",
		bits: [
			{ name: "SEL_0", description: "FSM EXT_IN1 select input for unit 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "FSM EXT_IN1 select input for unit 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "FSM EXT_IN1 select input for unit 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "FSM_EXTRA_IN1", description: "FSM Extra_EXT_IN1", offset: "0x10",
		bits: [
			{ name: "SEL_0", description: "FSM extra ext input select 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "FSM extra ext input select 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "FSM extra ext input select 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "LUT4_IN0", description: "LUT4_0/1/2 IN0 input source", offset: "0x12",
		bits: [
			{ name: "SEL_0", description: "Select inputs for unit 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "Select inputs for unit 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "Select inputs for unit 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "LUT4_IN1", description: "LUT4_0/1/2 IN1 input source", offset: "0x14",
		bits: [
			{ name: "SEL_0", description: "Select inputs for unit 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "Select inputs for unit 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "Select inputs for unit 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "LUT4_IN2", description: "LUT4_0/1/2 IN2 input source", offset: "0x16",
		bits: [
			{ name: "SEL_0", description: "Select inputs for unit 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "Select inputs for unit 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "Select inputs for unit 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "LUT4_IN3", description: "LUT4_0/1/2 IN3 input source", offset: "0x18",
		bits: [
			{ name: "SEL_0", description: "Select inputs for unit 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "SEL_1", description: "Select inputs for unit 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "SEL_2", description: "Select inputs for unit 2", size: "5", shift: "10", mask: "0x7C00" },
		]
	},
	{ name: "FSM_LUT_FN1_0", description: "LUT function for FSM Unit 1 and Unit 0", offset: "0x1C",
		bits: [
			{ name: "FN0", description: "FSM LUT output function for unit 0", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "FN1", description: "FSM LUT output function for unit 1", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "FSM_LUT_FN2", description: "LUT function for FSM Unit 2", offset: "0x1E",
		bits: [
			{ name: "FN1", description: "FSM LUT output function for unit 2", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "LUT4_FN1_0", description: "LUT function for LUT4 block of Unit 1 and 0", offset: "0x20",
		bits: [
			{ name: "FN0", description: "LUT4 output function for unit 0", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "FN1", description: "LUT4 output function for unit 1", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "LUT4_FN2", description: "LUT function for LUT4 block of Unit 2", offset: "0x22",
		bits: [
			{ name: "FN1", description: "LUT4 output function for unit 2", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "FSM_NEXT_STATE_0", description: "FSM Next state equations for Unit 0", offset: "0x24",
		bits: [
			{ name: "S0", description: "FSM next state function for S0", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "S1", description: "FSM next state function for S1", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "FSM_NEXT_STATE_1", description: "FSM Next state equations for Unit 1", offset: "0x26",
		bits: [
			{ name: "S0", description: "FSM next state function for S0", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "S1", description: "FSM next state function for S1", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "FSM_NEXT_STATE_2", description: "FSM Next state equations for Unit 2", offset: "0x28",
		bits: [
			{ name: "S0", description: "FSM next state function for S0", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "S1", description: "FSM next state function for S1", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "MISC_CONTROL", description: "Static controls for Ctr,FSM", offset: "0x2A",
		bits: [
			{ name: "COUNT_ADD_SHIFT_0", description: "Add/Shift for counter 0", size: "1", shift: "0", mask: "0x1" },
			{ name: "COUNT_DIR_0", description: "Direction for counter 0", size: "1", shift: "1", mask: "0x2" },
			{ name: "COUNT_EVENT_CTRL_0", description: "Event control for counter 0", size: "1", shift: "2", mask: "0x4" },
			{ name: "COUNT_ADD_SHIFT_1", description: "Add/Shift for counter 1", size: "1", shift: "3", mask: "0x8" },
			{ name: "COUNT_DIR_1", description: "Direction for counter 1", size: "1", shift: "4", mask: "0x10" },
			{ name: "COUNT_EVENT_CTRL_1", description: "Event control for counter 1", size: "1", shift: "5", mask: "0x20" },
			{ name: "COUNT_ADD_SHIFT_2", description: "Add/Shift for counter 2", size: "1", shift: "6", mask: "0x40" },
			{ name: "COUNT_DIR_2", description: "Direction for counter 2", size: "1", shift: "7", mask: "0x80" },
			{ name: "COUNT_EVENT_CTRL_2", description: "Event control for counter 2", size: "1", shift: "8", mask: "0x100" },
			{ name: "COUNT_SERIALIZER_0", description: "Serializer enable 0", size: "1", shift: "9", mask: "0x200" },
			{ name: "COUNT_SERIALIZER_1", description: "Serializer enable 1", size: "1", shift: "10", mask: "0x400" },
			{ name: "COUNT_SERIALIZER_2", description: "Serializer enable 2", size: "1", shift: "11", mask: "0x800" },
			{ name: "FSM_EXTRA_SEL0_0", description: "FSM extra_sel0 for 0", size: "1", shift: "12", mask: "0x1000" },
			{ name: "FSM_EXTRA_SEL1_0", description: "FSM extra_sel1 for 0", size: "1", shift: "13", mask: "0x2000" },
			{ name: "FSM_EXTRA_SEL0_1", description: "FSM extra_sel0 for 1", size: "1", shift: "14", mask: "0x4000" },
			{ name: "FSM_EXTRA_SEL1_1", description: "FSM extra_sel1 for 1", size: "1", shift: "15", mask: "0x8000" },
			{ name: "FSM_EXTRA_SEL0_2", description: "FSM extra_sel0 for 2", size: "1", shift: "16", mask: "0x10000" },
			{ name: "FSM_EXTRA_SEL1_2", description: "FSM extra_sel1 for 2", size: "1", shift: "17", mask: "0x20000" },
			{ name: "COUNT0_MATCH1_TAP_EN", description: "Match1 Tap Enable for Counter 0", size: "1", shift: "18", mask: "0x40000" },
			{ name: "COUNT1_MATCH1_TAP_EN", description: "Match1 Tap Enable for Counter 1", size: "1", shift: "19", mask: "0x80000" },
			{ name: "COUNT2_MATCH1_TAP_EN", description: "Match1 Tap Enable for Counter 2", size: "1", shift: "20", mask: "0x100000" },
			{ name: "COUNT0_MATCH2_TAP_EN", description: "Match2 Tap Enable for Counter 0", size: "1", shift: "21", mask: "0x200000" },
			{ name: "COUNT1_MATCH2_TAP_EN", description: "Match2 Tap Enable for Counter 1", size: "1", shift: "22", mask: "0x400000" },
			{ name: "COUNT2_MATCH2_TAP_EN", description: "Match2 Tap Enable for Counter 2", size: "1", shift: "23", mask: "0x800000" },
			{ name: "COUNT0_LFSR_EN", description: "Enable LFSR mode for Counter 0", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "COUNT1_LFSR_EN", description: "Enable LFSR mode for Counter 1", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "COUNT2_LFSR_EN", description: "Enable LFSR mode for Counter 2", size: "1", shift: "26", mask: "0x4000000" },
		]
	},
	{ name: "OUTPUT_LUT_0", description: "Inp Sel, LUT fns for Out0", offset: "0x2C",
		bits: [
			{ name: "IN0", description: "Select value for IN0 of output LUT", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IN1", description: "Select value for IN1 of output LUT", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "IN2", description: "Select value for IN2 of output LUT", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "FN", description: "Output function for output LUT", size: "8", shift: "15", mask: "0x7F8000" },
		]
	},
	{ name: "OUTPUT_LUT_1", description: "Inp Sel, LUT fns for Out1", offset: "0x2E",
		bits: [
			{ name: "IN0", description: "Select value for IN0 of output LUT", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IN1", description: "Select value for IN1 of output LUT", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "IN2", description: "Select value for IN2 of output LUT", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "FN", description: "Output function for output LUT", size: "8", shift: "15", mask: "0x7F8000" },
		]
	},
	{ name: "OUTPUT_LUT_2", description: "Inp Sel, LUT fns for Out2", offset: "0x30",
		bits: [
			{ name: "IN0", description: "Select value for IN0 of output LUT", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IN1", description: "Select value for IN1 of output LUT", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "IN2", description: "Select value for IN2 of output LUT", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "FN", description: "Output function for output LUT", size: "8", shift: "15", mask: "0x7F8000" },
		]
	},
	{ name: "OUTPUT_LUT_3", description: "Inp Sel, LUT fns for Out3", offset: "0x32",
		bits: [
			{ name: "IN0", description: "Select value for IN0 of output LUT", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IN1", description: "Select value for IN1 of output LUT", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "IN2", description: "Select value for IN2 of output LUT", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "FN", description: "Output function for output LUT", size: "8", shift: "15", mask: "0x7F8000" },
		]
	},
	{ name: "OUTPUT_LUT_4", description: "Inp Sel, LUT fns for Out4", offset: "0x34",
		bits: [
			{ name: "IN0", description: "Select value for IN0 of output LUT", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IN1", description: "Select value for IN1 of output LUT", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "IN2", description: "Select value for IN2 of output LUT", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "FN", description: "Output function for output LUT", size: "8", shift: "15", mask: "0x7F8000" },
		]
	},
	{ name: "OUTPUT_LUT_5", description: "Inp Sel, LUT fns for Out5", offset: "0x36",
		bits: [
			{ name: "IN0", description: "Select value for IN0 of output LUT", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IN1", description: "Select value for IN1 of output LUT", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "IN2", description: "Select value for IN2 of output LUT", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "FN", description: "Output function for output LUT", size: "8", shift: "15", mask: "0x7F8000" },
		]
	},
	{ name: "OUTPUT_LUT_6", description: "Inp Sel, LUT fns for Out6", offset: "0x38",
		bits: [
			{ name: "IN0", description: "Select value for IN0 of output LUT", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IN1", description: "Select value for IN1 of output LUT", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "IN2", description: "Select value for IN2 of output LUT", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "FN", description: "Output function for output LUT", size: "8", shift: "15", mask: "0x7F8000" },
		]
	},
	{ name: "OUTPUT_LUT_7", description: "Inp Sel, LUT fns for Out7", offset: "0x3A",
		bits: [
			{ name: "IN0", description: "Select value for IN0 of output LUT", size: "5", shift: "0", mask: "0x1F" },
			{ name: "IN1", description: "Select value for IN1 of output LUT", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "IN2", description: "Select value for IN2 of output LUT", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "FN", description: "Output function for output LUT", size: "8", shift: "15", mask: "0x7F8000" },
		]
	},
	{ name: "HLC_EVENT_SEL", description: "Event Selector register for the High Level", offset: "0x3C",
		bits: [
			{ name: "EVENT0_SEL", description: "Event Select 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "EVENT1_SEL", description: "Event Select 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "EVENT2_SEL", description: "Event Select 2", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "EVENT3_SEL", description: "Event Select 3", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "ALT_EVENT0_SEL", description: "Event Select 3", size: "1", shift: "20", mask: "0x100000" },
			{ name: "ALT_EVENT1_SEL", description: "Event Select 3", size: "1", shift: "21", mask: "0x200000" },
			{ name: "ALT_EVENT2_SEL", description: "Event Select 3", size: "1", shift: "22", mask: "0x400000" },
			{ name: "ALT_EVENT3_SEL", description: "Event Select 3", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "COUNT_MATCH_TAP_SEL", description: "Counter tap values for match1 and match2 outputs", offset: "0x3E",
		bits: [
			{ name: "COUNT0_MATCH1", description: "Match1 tap select for Counter 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "COUNT1_MATCH1", description: "Match1 tap select for Counter 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "COUNT2_MATCH1", description: "Match1 tap select for Counter 2", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "COUNT0_MATCH2", description: "Match2 tap select for Counter 0", size: "5", shift: "16", mask: "0x1F0000" },
			{ name: "COUNT1_MATCH2", description: "Match2 tap select for Counter 1", size: "5", shift: "21", mask: "0x3E00000" },
			{ name: "COUNT2_MATCH2", description: "Match2 tap select for Counter 2", size: "5", shift: "26", mask: "0x7C000000" },
		]
	},
	{ name: "OUTPUT_COND_CTRL_0", description: "Output conditioning control for output 0", offset: "0x40",
		bits: [
			{ name: "LEVEL_1_SEL", description: "Level 1 Mux Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "LEVEL_2_SEL", description: "Level 2 Mux Select", size: "2", shift: "1", mask: "0x6" },
			{ name: "LEVEL_3_SEL", description: "Level 3 Mux Select", size: "2", shift: "3", mask: "0x18" },
			{ name: "SEL_GATING_CTRL", description: "Gating control mux select", size: "3", shift: "5", mask: "0xE0" },
			{ name: "SEL_RELEASE_CTRL", description: "Releast control mux select", size: "3", shift: "8", mask: "0x700" },
			{ name: "HW_GATING_CTRL_SEL", description: "Select HW for gating control", size: "1", shift: "11", mask: "0x800" },
			{ name: "HW_RLS_CTRL_SEL", description: "Select HW for release control", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEL_RAW_IN", description: "Select input mode for the CLB AOC", size: "1", shift: "13", mask: "0x2000" },
			{ name: "ASYNC_COND_EN", description: "Enable for conditioning", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "OUTPUT_COND_CTRL_1", description: "Output conditioning control for output 1", offset: "0x42",
		bits: [
			{ name: "LEVEL_1_SEL", description: "Level 1 Mux Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "LEVEL_2_SEL", description: "Level 2 Mux Select", size: "2", shift: "1", mask: "0x6" },
			{ name: "LEVEL_3_SEL", description: "Level 3 Mux Select", size: "2", shift: "3", mask: "0x18" },
			{ name: "SEL_GATING_CTRL", description: "Gating control mux select", size: "3", shift: "5", mask: "0xE0" },
			{ name: "SEL_RELEASE_CTRL", description: "Releast control mux select", size: "3", shift: "8", mask: "0x700" },
			{ name: "HW_GATING_CTRL_SEL", description: "Select HW for gating control", size: "1", shift: "11", mask: "0x800" },
			{ name: "HW_RLS_CTRL_SEL", description: "Select HW for release control", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEL_RAW_IN", description: "Select input mode for the CLB AOC", size: "1", shift: "13", mask: "0x2000" },
			{ name: "ASYNC_COND_EN", description: "Enable for conditioning", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "OUTPUT_COND_CTRL_2", description: "Output conditioning control for output 2", offset: "0x44",
		bits: [
			{ name: "LEVEL_1_SEL", description: "Level 1 Mux Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "LEVEL_2_SEL", description: "Level 2 Mux Select", size: "2", shift: "1", mask: "0x6" },
			{ name: "LEVEL_3_SEL", description: "Level 3 Mux Select", size: "2", shift: "3", mask: "0x18" },
			{ name: "SEL_GATING_CTRL", description: "Gating control mux select", size: "3", shift: "5", mask: "0xE0" },
			{ name: "SEL_RELEASE_CTRL", description: "Releast control mux select", size: "3", shift: "8", mask: "0x700" },
			{ name: "HW_GATING_CTRL_SEL", description: "Select HW for gating control", size: "1", shift: "11", mask: "0x800" },
			{ name: "HW_RLS_CTRL_SEL", description: "Select HW for release control", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEL_RAW_IN", description: "Select input mode for the CLB AOC", size: "1", shift: "13", mask: "0x2000" },
			{ name: "ASYNC_COND_EN", description: "Enable for conditioning", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "OUTPUT_COND_CTRL_3", description: "Output conditioning control for output 3", offset: "0x46",
		bits: [
			{ name: "LEVEL_1_SEL", description: "Level 1 Mux Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "LEVEL_2_SEL", description: "Level 2 Mux Select", size: "2", shift: "1", mask: "0x6" },
			{ name: "LEVEL_3_SEL", description: "Level 3 Mux Select", size: "2", shift: "3", mask: "0x18" },
			{ name: "SEL_GATING_CTRL", description: "Gating control mux select", size: "3", shift: "5", mask: "0xE0" },
			{ name: "SEL_RELEASE_CTRL", description: "Releast control mux select", size: "3", shift: "8", mask: "0x700" },
			{ name: "HW_GATING_CTRL_SEL", description: "Select HW for gating control", size: "1", shift: "11", mask: "0x800" },
			{ name: "HW_RLS_CTRL_SEL", description: "Select HW for release control", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEL_RAW_IN", description: "Select input mode for the CLB AOC", size: "1", shift: "13", mask: "0x2000" },
			{ name: "ASYNC_COND_EN", description: "Enable for conditioning", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "OUTPUT_COND_CTRL_4", description: "Output conditioning control for output 4", offset: "0x48",
		bits: [
			{ name: "LEVEL_1_SEL", description: "Level 1 Mux Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "LEVEL_2_SEL", description: "Level 2 Mux Select", size: "2", shift: "1", mask: "0x6" },
			{ name: "LEVEL_3_SEL", description: "Level 3 Mux Select", size: "2", shift: "3", mask: "0x18" },
			{ name: "SEL_GATING_CTRL", description: "Gating control mux select", size: "3", shift: "5", mask: "0xE0" },
			{ name: "SEL_RELEASE_CTRL", description: "Releast control mux select", size: "3", shift: "8", mask: "0x700" },
			{ name: "HW_GATING_CTRL_SEL", description: "Select HW for gating control", size: "1", shift: "11", mask: "0x800" },
			{ name: "HW_RLS_CTRL_SEL", description: "Select HW for release control", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEL_RAW_IN", description: "Select input mode for the CLB AOC", size: "1", shift: "13", mask: "0x2000" },
			{ name: "ASYNC_COND_EN", description: "Enable for conditioning", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "OUTPUT_COND_CTRL_5", description: "Output conditioning control for output 5", offset: "0x4A",
		bits: [
			{ name: "LEVEL_1_SEL", description: "Level 1 Mux Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "LEVEL_2_SEL", description: "Level 2 Mux Select", size: "2", shift: "1", mask: "0x6" },
			{ name: "LEVEL_3_SEL", description: "Level 3 Mux Select", size: "2", shift: "3", mask: "0x18" },
			{ name: "SEL_GATING_CTRL", description: "Gating control mux select", size: "3", shift: "5", mask: "0xE0" },
			{ name: "SEL_RELEASE_CTRL", description: "Releast control mux select", size: "3", shift: "8", mask: "0x700" },
			{ name: "HW_GATING_CTRL_SEL", description: "Select HW for gating control", size: "1", shift: "11", mask: "0x800" },
			{ name: "HW_RLS_CTRL_SEL", description: "Select HW for release control", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEL_RAW_IN", description: "Select input mode for the CLB AOC", size: "1", shift: "13", mask: "0x2000" },
			{ name: "ASYNC_COND_EN", description: "Enable for conditioning", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "OUTPUT_COND_CTRL_6", description: "Output conditioning control for output 6", offset: "0x4C",
		bits: [
			{ name: "LEVEL_1_SEL", description: "Level 1 Mux Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "LEVEL_2_SEL", description: "Level 2 Mux Select", size: "2", shift: "1", mask: "0x6" },
			{ name: "LEVEL_3_SEL", description: "Level 3 Mux Select", size: "2", shift: "3", mask: "0x18" },
			{ name: "SEL_GATING_CTRL", description: "Gating control mux select", size: "3", shift: "5", mask: "0xE0" },
			{ name: "SEL_RELEASE_CTRL", description: "Releast control mux select", size: "3", shift: "8", mask: "0x700" },
			{ name: "HW_GATING_CTRL_SEL", description: "Select HW for gating control", size: "1", shift: "11", mask: "0x800" },
			{ name: "HW_RLS_CTRL_SEL", description: "Select HW for release control", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEL_RAW_IN", description: "Select input mode for the CLB AOC", size: "1", shift: "13", mask: "0x2000" },
			{ name: "ASYNC_COND_EN", description: "Enable for conditioning", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "OUTPUT_COND_CTRL_7", description: "Output conditioning control for output 7", offset: "0x4E",
		bits: [
			{ name: "LEVEL_1_SEL", description: "Level 1 Mux Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "LEVEL_2_SEL", description: "Level 2 Mux Select", size: "2", shift: "1", mask: "0x6" },
			{ name: "LEVEL_3_SEL", description: "Level 3 Mux Select", size: "2", shift: "3", mask: "0x18" },
			{ name: "SEL_GATING_CTRL", description: "Gating control mux select", size: "3", shift: "5", mask: "0xE0" },
			{ name: "SEL_RELEASE_CTRL", description: "Releast control mux select", size: "3", shift: "8", mask: "0x700" },
			{ name: "HW_GATING_CTRL_SEL", description: "Select HW for gating control", size: "1", shift: "11", mask: "0x800" },
			{ name: "HW_RLS_CTRL_SEL", description: "Select HW for release control", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEL_RAW_IN", description: "Select input mode for the CLB AOC", size: "1", shift: "13", mask: "0x2000" },
			{ name: "ASYNC_COND_EN", description: "Enable for conditioning", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "LOAD_EN", description: "Global enable & indirect load enable control", offset: "0x0",
		bits: [
			{ name: "LOAD_EN", description: "Load Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "GLOBAL_EN", description: "Global Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "STOP", description: "Debug stop control", size: "1", shift: "2", mask: "0x4" },
			{ name: "NMI_EN", description: "NMI output enable", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "LOAD_ADDR", description: "Indirect address", offset: "0x2",
		bits: [
			{ name: "ADDR", description: "Indirect Address", size: "6", shift: "0", mask: "0x3F" },
		]
	},
	{ name: "LOAD_DATA", description: "Data for indirect loads", offset: "0x4",
		bits: [
		]
	},
	{ name: "INPUT_FILTER", description: "Input filter selection for both edge detection and", offset: "0x6",
		bits: [
			{ name: "FIN0", description: "Input filter control 0", size: "2", shift: "0", mask: "0x3" },
			{ name: "FIN1", description: "Input filter control 1", size: "2", shift: "2", mask: "0xC" },
			{ name: "FIN2", description: "Input filter control 2", size: "2", shift: "4", mask: "0x30" },
			{ name: "FIN3", description: "Input filter control 3", size: "2", shift: "6", mask: "0xC0" },
			{ name: "FIN4", description: "Input filter control 4", size: "2", shift: "8", mask: "0x300" },
			{ name: "FIN5", description: "Input filter control 5", size: "2", shift: "10", mask: "0xC00" },
			{ name: "FIN6", description: "Input filter control 6", size: "2", shift: "12", mask: "0x3000" },
			{ name: "FIN7", description: "Input filter control 7", size: "2", shift: "14", mask: "0xC000" },
			{ name: "SYNC0", description: "Synchronizer control 0", size: "1", shift: "16", mask: "0x10000" },
			{ name: "SYNC1", description: "Synchronizer control 1", size: "1", shift: "17", mask: "0x20000" },
			{ name: "SYNC2", description: "Synchronizer control 2", size: "1", shift: "18", mask: "0x40000" },
			{ name: "SYNC3", description: "Synchronizer control 3", size: "1", shift: "19", mask: "0x80000" },
			{ name: "SYNC4", description: "Synchronizer control 4", size: "1", shift: "20", mask: "0x100000" },
			{ name: "SYNC5", description: "Synchronizer control 5", size: "1", shift: "21", mask: "0x200000" },
			{ name: "SYNC6", description: "Synchronizer control 6", size: "1", shift: "22", mask: "0x400000" },
			{ name: "SYNC7", description: "Synchronizer control 7", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "IN_MUX_SEL_0", description: "Input selection to decide between Signals and GP register", offset: "0x8",
		bits: [
			{ name: "SEL_GP_IN_0", description: "Select GP register 0", size: "1", shift: "0", mask: "0x1" },
			{ name: "SEL_GP_IN_1", description: "Select GP register 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "SEL_GP_IN_2", description: "Select GP register 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "SEL_GP_IN_3", description: "Select GP register 3", size: "1", shift: "3", mask: "0x8" },
			{ name: "SEL_GP_IN_4", description: "Select GP register 4", size: "1", shift: "4", mask: "0x10" },
			{ name: "SEL_GP_IN_5", description: "Select GP register 5", size: "1", shift: "5", mask: "0x20" },
			{ name: "SEL_GP_IN_6", description: "Select GP register 6", size: "1", shift: "6", mask: "0x40" },
			{ name: "SEL_GP_IN_7", description: "Select GP register 7", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "LCL_MUX_SEL_1", description: "Input Mux selection for local mux", offset: "0xA",
		bits: [
			{ name: "LCL_MUX_SEL_IN_0", description: "Local Mux select 0", size: "5", shift: "0", mask: "0x1F" },
			{ name: "LCL_MUX_SEL_IN_1", description: "Local Mux select 1", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "LCL_MUX_SEL_IN_2", description: "Local Mux select 2", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "LCL_MUX_SEL_IN_3", description: "Local Mux select 3", size: "5", shift: "15", mask: "0xF8000" },
		]
	},
	{ name: "LCL_MUX_SEL_2", description: "Input Mux selection for local mux", offset: "0xC",
		bits: [
			{ name: "LCL_MUX_SEL_IN_4", description: "Local Mux select 4", size: "5", shift: "0", mask: "0x1F" },
			{ name: "LCL_MUX_SEL_IN_5", description: "Local Mux select 5", size: "5", shift: "5", mask: "0x3E0" },
			{ name: "LCL_MUX_SEL_IN_6", description: "Local Mux select 6", size: "5", shift: "10", mask: "0x7C00" },
			{ name: "LCL_MUX_SEL_IN_7", description: "Local Mux select 7", size: "5", shift: "15", mask: "0xF8000" },
		]
	},
	{ name: "BUF_PTR", description: "PUSH and PULL pointers", offset: "0xE",
		bits: [
			{ name: "PULL", description: "Data pointer for pull", size: "8", shift: "0", mask: "0xFF" },
			{ name: "PUSH", description: "Data pointer for pull", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "GP_REG", description: "General purpose register for CELL inputs", offset: "0x10",
		bits: [
			{ name: "REG", description: "General Purpose bit register", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SW_GATING_CTRL_0", description: "Software gating control 0", size: "1", shift: "16", mask: "0x10000" },
			{ name: "SW_GATING_CTRL_1", description: "Software gating control 1", size: "1", shift: "17", mask: "0x20000" },
			{ name: "SW_GATING_CTRL_2", description: "Software gating control 2", size: "1", shift: "18", mask: "0x40000" },
			{ name: "SW_GATING_CTRL_3", description: "Software gating control 3", size: "1", shift: "19", mask: "0x80000" },
			{ name: "SW_GATING_CTRL_4", description: "Software gating control 4", size: "1", shift: "20", mask: "0x100000" },
			{ name: "SW_GATING_CTRL_5", description: "Software gating control 5", size: "1", shift: "21", mask: "0x200000" },
			{ name: "SW_GATING_CTRL_6", description: "Software gating control 6", size: "1", shift: "22", mask: "0x400000" },
			{ name: "SW_GATING_CTRL_7", description: "Software gating control 7", size: "1", shift: "23", mask: "0x800000" },
			{ name: "SW_RLS_CTRL_0", description: "Software release control 0", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "SW_RLS_CTRL_1", description: "Software release control 1", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "SW_RLS_CTRL_2", description: "Software release control 2", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "SW_RLS_CTRL_3", description: "Software release control 3", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "SW_RLS_CTRL_4", description: "Software release control 4", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "SW_RLS_CTRL_5", description: "Software release control 5", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "SW_RLS_CTRL_6", description: "Software release control 6", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "SW_RLS_CTRL_7", description: "Software release control 7", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "OUT_EN", description: "CELL output enable register", offset: "0x12",
		bits: [
		]
	},
	{ name: "GLBL_MUX_SEL_1", description: "Global Mux select for CELL inputs", offset: "0x14",
		bits: [
			{ name: "GLBL_MUX_SEL_IN_0", description: "Global Mux select 0", size: "7", shift: "0", mask: "0x7F" },
			{ name: "GLBL_MUX_SEL_IN_1", description: "Global Mux select 1", size: "7", shift: "7", mask: "0x3F80" },
			{ name: "GLBL_MUX_SEL_IN_2", description: "Global Mux select 2", size: "7", shift: "14", mask: "0x1FC000" },
			{ name: "GLBL_MUX_SEL_IN_3", description: "Global Mux select 3", size: "7", shift: "21", mask: "0xFE00000" },
		]
	},
	{ name: "GLBL_MUX_SEL_2", description: "Global Mux select for CELL inputs", offset: "0x16",
		bits: [
			{ name: "GLBL_MUX_SEL_IN_4", description: "Global Mux select 4", size: "7", shift: "0", mask: "0x7F" },
			{ name: "GLBL_MUX_SEL_IN_5", description: "Global Mux select 5", size: "7", shift: "7", mask: "0x3F80" },
			{ name: "GLBL_MUX_SEL_IN_6", description: "Global Mux select 6", size: "7", shift: "14", mask: "0x1FC000" },
			{ name: "GLBL_MUX_SEL_IN_7", description: "Global Mux select 7", size: "7", shift: "21", mask: "0xFE00000" },
		]
	},
	{ name: "PRESCALE_CTRL", description: "Prescaler register control", offset: "0x18",
		bits: [
			{ name: "CLKEN", description: "Enable the prescale clock generator", size: "1", shift: "0", mask: "0x1" },
			{ name: "STRB", description: "Enable the Strobe mode of operation", size: "1", shift: "1", mask: "0x2" },
			{ name: "TAP", description: "TAP Select value", size: "4", shift: "2", mask: "0x3C" },
			{ name: "PRESCALE", description: "Value of prescale register", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "INTR_TAG_REG", description: "Interrupt Tag register", offset: "0x20",
		bits: [
			{ name: "TAG", description: "Interrupt tag", size: "6", shift: "0", mask: "0x3F" },
		]
	},
	{ name: "LOCK", description: "Lock control register", offset: "0x22",
		bits: [
			{ name: "LOCK", description: "LOCK enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "KEY", description: "Key for enabling write", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "DBG_OUT_2", description: "Visibility for CLB inputs and final  asynchronous outputs", offset: "0x2E",
		bits: [
			{ name: "OUT", description: "Outputs of CLB Async block", size: "8", shift: "0", mask: "0xFF" },
			{ name: "IN", description: "CLB CELL Inputs", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "DBG_R0", description: "R0 of High level Controller", offset: "0x30",
		bits: [
		]
	},
	{ name: "DBG_R1", description: "R1 of High level Controller", offset: "0x32",
		bits: [
		]
	},
	{ name: "DBG_R2", description: "R2 of High level Controller", offset: "0x34",
		bits: [
		]
	},
	{ name: "DBG_R3", description: "R3 of High level Controller", offset: "0x36",
		bits: [
		]
	},
	{ name: "DBG_C0", description: "Count of Unit 0", offset: "0x38",
		bits: [
		]
	},
	{ name: "DBG_C1", description: "Count of Unit 1", offset: "0x3A",
		bits: [
		]
	},
	{ name: "DBG_C2", description: "Count of Unit 2", offset: "0x3C",
		bits: [
		]
	},
	{ name: "DBG_OUT", description: "Outputs of various units in the Cell", offset: "0x3E",
		bits: [
			{ name: "2_OUT", description: "Outputs of CLB Async block", size: "8", shift: "0", mask: "0xFF" },
			{ name: "2_IN", description: "CLB CELL Inputs", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "COUNT0_MATCH2", description: "COUNT_MATCH2 UNIT 0", size: "1", shift: "1", mask: "0x2" },
			{ name: "COUNT0_ZERO", description: "COUNT_ZERO UNIT 0", size: "1", shift: "2", mask: "0x4" },
			{ name: "COUNT0_MATCH1", description: "COUNT_MATCH1 UNIT 0", size: "1", shift: "3", mask: "0x8" },
			{ name: "FSM0_S0", description: "FSM_S0 UNIT 0", size: "1", shift: "4", mask: "0x10" },
			{ name: "FSM0_S1", description: "FSM_S1 UNIT 0", size: "1", shift: "5", mask: "0x20" },
			{ name: "FSM0_LUTOUT", description: "FSM_LUT_OUT UNIT 0", size: "1", shift: "6", mask: "0x40" },
			{ name: "LUT40_OUT", description: "LUT4_OUT UNIT 0", size: "1", shift: "7", mask: "0x80" },
			{ name: "COUNT1_MATCH2", description: "COUNT_MATCH2 UNIT 1", size: "1", shift: "9", mask: "0x200" },
			{ name: "COUNT1_ZERO", description: "COUNT_ZERO UNIT 1", size: "1", shift: "10", mask: "0x400" },
			{ name: "COUNT1_MATCH1", description: "COUNT_MATCH1 UNIT 1", size: "1", shift: "11", mask: "0x800" },
			{ name: "FSM1_S0", description: "FSM_S0 UNIT 1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "FSM1_S1", description: "FSM_S1 UNIT 1", size: "1", shift: "13", mask: "0x2000" },
			{ name: "FSM1_LUTOUT", description: "FSM_LUT_OUT UNIT 1", size: "1", shift: "14", mask: "0x4000" },
			{ name: "LUT41_OUT", description: "LUT4_OUT UNIT 1", size: "1", shift: "15", mask: "0x8000" },
			{ name: "COUNT2_MATCH2", description: "COUNT_MATCH2 UNIT 2", size: "1", shift: "17", mask: "0x20000" },
			{ name: "COUNT2_ZERO", description: "COUNT_ZERO UNIT 2", size: "1", shift: "18", mask: "0x40000" },
			{ name: "COUNT2_MATCH1", description: "COUNT_MATCH1 UNIT 2", size: "1", shift: "19", mask: "0x80000" },
			{ name: "FSM2_S0", description: "FSM_S0 UNIT 2", size: "1", shift: "20", mask: "0x100000" },
			{ name: "FSM2_S1", description: "FSM_S1 UNIT 2", size: "1", shift: "21", mask: "0x200000" },
			{ name: "FSM2_LUTOUT", description: "FSM_LUT_OUT UNIT 2", size: "1", shift: "22", mask: "0x400000" },
			{ name: "LUT42_OUT", description: "LUT4_OUT UNIT 2", size: "1", shift: "23", mask: "0x800000" },
			{ name: "OUT0", description: "CELL Output 0", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "OUT1", description: "CELL Output 1", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "OUT2", description: "CELL Output 2", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "OUT3", description: "CELL Output 3", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "OUT4", description: "CELL Output 4", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "OUT5", description: "CELL Output 5", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "OUT6", description: "CELL Output 6", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "OUT7", description: "CELL Output 7", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "PUSH(i)", description: "(0 <= i < 4) CLB_PUSH FIFO Registers (from", offset: "(0x0U + ((i) * 0x2U))",
		bits: [
		]
	},
	{ name: "PULL(i)", description: "(0 <= i < 4) CLB_PULL FIFO Registers (TO HLC)", offset: "(0x100U + ((i) * 0x2U))",
		bits: [
		]
	},
];
module.exports = {
	CLBRegisters: CLBRegisters,
}
