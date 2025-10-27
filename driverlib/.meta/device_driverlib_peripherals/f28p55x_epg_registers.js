let EPGRegisters = [
	{ name: "GCTL0", description: "EPG Global control register 0", offset: "0x0",
		bits: [
			{ name: "EN", description: "Enable EPG", size: "1", shift: "0", mask: "0x1" },
			{ name: "SIGGEN0_EN", description: "Signal generator enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "SIGGEN1_EN", description: "Signal generator enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "EPGOUT13SEL", description: "EPG output 13 Clock/signal select", size: "1", shift: "8", mask: "0x100" },
			{ name: "EPGOUT15SEL", description: "EPG output 15 Clock/signal select", size: "1", shift: "9", mask: "0x200" },
			{ name: "EPGOUT16SEL", description: "EPG output 16 Clock/signal select", size: "1", shift: "10", mask: "0x400" },
			{ name: "EPGOUT17SEL", description: "EPG output 17 Clock/signal select", size: "1", shift: "11", mask: "0x800" },
			{ name: "EPGOUT20SEL", description: "EPG output 20 Clock/signal select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "EPGOUT21SEL", description: "EPG output 21 Clock/signal select", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EPGOUT22SEL", description: "EPG output 22 Clock/signal select", size: "1", shift: "14", mask: "0x4000" },
			{ name: "EPGOUT23SEL", description: "EPG output 23 Clock/signal select", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "GCTL1", description: "EPG Global control register 1", offset: "0x2",
		bits: [
			{ name: "SIGGEN0_CLKSEL", description: "Clock source select of SIGGEN0", size: "3", shift: "0", mask: "0x7" },
			{ name: "SIGGEN1_CLKSEL", description: "Clock source select of SIGGEN1", size: "3", shift: "4", mask: "0x70" },
		]
	},
	{ name: "GCTL2", description: "EPG Global control register 2", offset: "0x4",
		bits: [
			{ name: "EPGOUT0_CLKOUTSEL", description: "Selects the clock signal source of EPG", size: "3", shift: "0", mask: "0x7" },
			{ name: "EPGOUT1_CLKOUTSEL", description: "Selects the clock signal source of EPG", size: "3", shift: "4", mask: "0x70" },
			{ name: "EPGOUT2_CLKOUTSEL", description: "Selects the clock signal source of EPG", size: "3", shift: "8", mask: "0x700" },
			{ name: "EPGOUT3_CLKOUTSEL", description: "Selects the clock signal source of EPG", size: "3", shift: "12", mask: "0x7000" },
			{ name: "EPGOUT4_CLKOUTSEL", description: "Selects the clock signal source of EPG", size: "3", shift: "16", mask: "0x70000" },
			{ name: "EPGOUT5_CLKOUTSEL", description: "Selects the clock signal source of EPG", size: "3", shift: "20", mask: "0x700000" },
			{ name: "EPGOUT6_CLKOUTSEL", description: "Selects the clock signal source of EPG", size: "3", shift: "24", mask: "0x7000000" },
			{ name: "EPGOUT7_CLKOUTSEL", description: "Selects the clock signal source of EPG", size: "3", shift: "28", mask: "0x70000000" },
		]
	},
	{ name: "GCTL3", description: "EPG Global control register 3", offset: "0x6",
		bits: [
			{ name: "EPGOUT0_SIGOUTSEL", description: "Selects the signal source of EPG output 0.", size: "4", shift: "0", mask: "0xF" },
			{ name: "EPGOUT1_SIGOUTSEL", description: "Selects the signal source of EPG output 1.", size: "4", shift: "4", mask: "0xF0" },
			{ name: "EPGOUT2_SIGOUTSEL", description: "Selects the signal source of EPG output 2.", size: "4", shift: "8", mask: "0xF00" },
			{ name: "EPGOUT3_SIGOUTSEL", description: "Selects the signal source of EPG output 3.", size: "4", shift: "12", mask: "0xF000" },
			{ name: "EPGOUT4_SIGOUTSEL", description: "Selects the signal source of EPG output 4.", size: "4", shift: "16", mask: "0xF0000" },
			{ name: "EPGOUT5_SIGOUTSEL", description: "Selects the signal source of EPG output 5.", size: "4", shift: "20", mask: "0xF00000" },
			{ name: "EPGOUT6_SIGOUTSEL", description: "Selects the signal source of EPG output 6.", size: "4", shift: "24", mask: "0xF000000" },
			{ name: "EPGOUT7_SIGOUTSEL", description: "Selects the signal source of EPG output 7.", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "LOCK", description: "EPG LOCK Register", offset: "0x8",
		bits: [
			{ name: "GCTL0", description: "GCTL0 Lock bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "GCTL1", description: "GCTL1 Lock bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "GCTL2", description: "GCTL2 Lock bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "GCTL3", description: "GCTL3 Lock bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLKDIV0_CTL0", description: "CLKDIV0_CTL0 Lock bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLKDIV1_CTL0", description: "CLKDIV1_CTL0 Lock bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "SIGGEN0_CTL0", description: "SIGGEN0_CTL0 Lock bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "SIGGEN0_CTL1", description: "SIGGEN0_CTL1 Lock bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "SIGGEN1_CTL0", description: "SIGGEN1_CTL0 Lock bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "SIGGEN1_CTL1", description: "SIGGEN1_CTL1 Lock bit", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "COMMIT", description: "EPG COMMIT register", offset: "0xA",
		bits: [
			{ name: "GCTL0", description: "GCTL0 Commit bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "GCTL1", description: "GCTL1 Commit bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "GCTL2", description: "GCTL2 Commit bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "GCTL3", description: "GCTL3 Commit bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "CLKDIV0_CTL0", description: "CLKDIV0_CTL0 Commit bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "CLKDIV1_CTL0", description: "CLKDIV1_CTL0 Commit bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "SIGGEN0_CTL0", description: "SIGGEN0_CTL0 Commit bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "SIGGEN0_CTL1", description: "SIGGEN0_CTL1 Commit bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "SIGGEN1_CTL0", description: "SIGGEN1_CTL0 Commit bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "SIGGEN1_CTL1", description: "SIGGEN1_CTL1 Commit bit", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "GINTSTS", description: "EPG Global interrupt status register.", offset: "0xC",
		bits: [
			{ name: "INT", description: "Global interrupt flag register", size: "1", shift: "0", mask: "0x1" },
			{ name: "SIGGEN0_DONE", description: "SIGGEN0 operation done status", size: "1", shift: "1", mask: "0x2" },
			{ name: "SIGGEN0_FILL", description: "SIGGEN0 data fill status", size: "1", shift: "2", mask: "0x4" },
			{ name: "SIGGEN1_DONE", description: "SIGGEN1 operation done status", size: "1", shift: "3", mask: "0x8" },
			{ name: "SIGGEN1_FILL", description: "SIGGEN1 data fill status", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "GINTEN", description: "EPG Global interrupt enable register.", offset: "0xE",
		bits: [
			{ name: "SIGGEN0_DONE", description: "SIGGEN0 operation done interrupt enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "SIGGEN0_FILL", description: "SIGGEN0 data fill interrupt enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "SIGGEN1_DONE", description: "SIGGEN1 operation done interrupt enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "SIGGEN1_FILL", description: "SIGGEN1 data fill interrupt enable", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "GINTCLR", description: "EPG Global interrupt clear register.", offset: "0x10",
		bits: [
			{ name: "INT", description: "Global interrupt flag clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "SIGGEN0_DONE", description: "SIGGEN0 operation done interrupt flag clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "SIGGEN0_FILL", description: "SIGGEN0 data fill interrupt flag clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "SIGGEN1_DONE", description: "SIGGEN0 data fill interrupt flag clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "SIGGEN1_FILL", description: "SIGGEN1 data fill interrupt flag clear", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "GINTFRC", description: "EPG Global interrupt force register.", offset: "0x12",
		bits: [
			{ name: "SIGGEN0_DONE", description: "SIGGEN0 operation done interrupt flag set", size: "1", shift: "1", mask: "0x2" },
			{ name: "SIGGEN0_FILL", description: "SIGGEN0 data fill interrupt flag set", size: "1", shift: "2", mask: "0x4" },
			{ name: "SIGGEN1_DONE", description: "SIGGEN1 operation done interrupt flag set", size: "1", shift: "3", mask: "0x8" },
			{ name: "SIGGEN1_FILL", description: "SIGGEN1 data fill interrupt flag set", size: "1", shift: "4", mask: "0x10" },
		]
	},
	{ name: "CLKDIV0_CTL0", description: "Clock divider 0's control register 0", offset: "0x18",
		bits: [
			{ name: "PRD", description: "Clock divider value", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "CLKSTOP", description: "Clock Stop Configuration", size: "3", shift: "16", mask: "0x70000" },
		]
	},
	{ name: "CLKDIV0_CLKOFFSET", description: "Clock divider 0's clock offset value", offset: "0x1E",
		bits: [
			{ name: "CLK0OFFSET", description: "Clock output 0 offset delay value.", size: "8", shift: "0", mask: "0xFF" },
			{ name: "CLK1OFFSET", description: "Clock output 0 offset delay value.", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "CLK2OFFSET", description: "Clock output 0 offset delay value.", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "CLK3OFFSET", description: "Clock output 0 offset delay value.", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "CLKDIV1_CTL0", description: "Clock divider 1's control register 0", offset: "0x24",
		bits: [
			{ name: "PRD", description: "Clock divider value", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "CLKSTOP", description: "Clock Stop Configuration", size: "3", shift: "16", mask: "0x70000" },
		]
	},
	{ name: "CLKDIV1_CLKOFFSET", description: "Clock divider 1's clock offset value", offset: "0x2A",
		bits: [
			{ name: "CLK0OFFSET", description: "Clock output 0 offset delay value.", size: "8", shift: "0", mask: "0xFF" },
			{ name: "CLK1OFFSET", description: "Clock output 0 offset delay value.", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "CLK2OFFSET", description: "Clock output 0 offset delay value.", size: "8", shift: "16", mask: "0xFF0000" },
			{ name: "CLK3OFFSET", description: "Clock output 0 offset delay value.", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "SIGGEN0_CTL0", description: "Signal generator 0's control register 0", offset: "0x30",
		bits: [
			{ name: "MODE", description: "Signal generator modes", size: "4", shift: "0", mask: "0xF" },
			{ name: "BRIN", description: "Reverse bits before transform", size: "1", shift: "5", mask: "0x20" },
			{ name: "BROUT", description: "Reverse bits after transform", size: "1", shift: "6", mask: "0x40" },
			{ name: "BITLENGTH", description: "Length of bit stream", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "SIGGEN0_CTL1", description: "Signal generator 0's control register 1", offset: "0x32",
		bits: [
			{ name: "DATA0_INSEL", description: "Select the source of DATA[0] bit.", size: "4", shift: "0", mask: "0xF" },
			{ name: "DATA63_INSEL", description: "Select the source of DATA[63] bit.", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SIGGEN0_DATA0", description: "Signal generator 0's data register 0", offset: "0x38",
		bits: [
		]
	},
	{ name: "SIGGEN0_DATA1", description: "Signal generator 0's data register 1", offset: "0x3A",
		bits: [
		]
	},
	{ name: "SIGGEN0_DATA0_ACTIVE", description: "Signal generator 0's data active register 0", offset: "0x3C",
		bits: [
		]
	},
	{ name: "SIGGEN0_DATA1_ACTIVE", description: "Signal generator 0's data active register 1", offset: "0x3E",
		bits: [
		]
	},
	{ name: "SIGGEN1_CTL0", description: "Signal generator 1's control register 0", offset: "0x40",
		bits: [
			{ name: "MODE", description: "Signal generator modes", size: "4", shift: "0", mask: "0xF" },
			{ name: "BRIN", description: "Reverse bits before transform", size: "1", shift: "5", mask: "0x20" },
			{ name: "BROUT", description: "Reverse bits after transform", size: "1", shift: "6", mask: "0x40" },
			{ name: "BITLENGTH", description: "Length of bit stream", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "SIGGEN1_CTL1", description: "Signal generator 1's control register 1", offset: "0x42",
		bits: [
			{ name: "DATA0_INSEL", description: "Select the source of DATA[0] bit.", size: "4", shift: "0", mask: "0xF" },
			{ name: "DATA63_INSEL", description: "Select the source of DATA[63] bit.", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SIGGEN1_DATA0", description: "Signal generator 1's data register 0", offset: "0x48",
		bits: [
		]
	},
	{ name: "SIGGEN1_DATA1", description: "Signal generator 1's data register 1", offset: "0x4A",
		bits: [
		]
	},
	{ name: "SIGGEN1_DATA0_ACTIVE", description: "Signal generator 1's data active register 0", offset: "0x4C",
		bits: [
		]
	},
	{ name: "SIGGEN1_DATA1_ACTIVE", description: "Signal generator 1's data active register 1", offset: "0x4E",
		bits: [
		]
	},
	{ name: "REVISION", description: "IP Revision tie-off value", offset: "0x50",
		bits: [
			{ name: "MINOR", description: "Minor Revision Number", size: "6", shift: "0", mask: "0x3F" },
			{ name: "CUSTOM", description: "Custom Module Number", size: "2", shift: "6", mask: "0xC0" },
			{ name: "MAJOR", description: "Major Revision Number", size: "3", shift: "8", mask: "0x700" },
			{ name: "FUNC", description: "Functional Release Number", size: "12", shift: "16", mask: "0xFFF0000" },
			{ name: "SCHEME", description: "Defines Scheme for Module", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "MXSEL0", description: "EPG Mux select register 0", offset: "0x0",
		bits: [
			{ name: "SEL0", description: "DATAOUT[0] mux select.", size: "1", shift: "0", mask: "0x1" },
			{ name: "SEL1", description: "DATAOUT[1] mux select.", size: "1", shift: "1", mask: "0x2" },
			{ name: "SEL2", description: "DATAOUT[2] mux select.", size: "1", shift: "2", mask: "0x4" },
			{ name: "SEL3", description: "DATAOUT[3] mux select.", size: "1", shift: "3", mask: "0x8" },
			{ name: "SEL4", description: "DATAOUT[4] mux select.", size: "1", shift: "4", mask: "0x10" },
			{ name: "SEL5", description: "DATAOUT[5] mux select.", size: "1", shift: "5", mask: "0x20" },
			{ name: "SEL6", description: "DATAOUT[6] mux select.", size: "1", shift: "6", mask: "0x40" },
			{ name: "SEL7", description: "DATAOUT[7] mux select.", size: "1", shift: "7", mask: "0x80" },
			{ name: "SEL8", description: "DATAOUT[8] mux select.", size: "1", shift: "8", mask: "0x100" },
			{ name: "SEL9", description: "DATAOUT[9] mux select.", size: "1", shift: "9", mask: "0x200" },
			{ name: "SEL10", description: "DATAOUT[10] mux select.", size: "1", shift: "10", mask: "0x400" },
			{ name: "SEL11", description: "DATAOUT[11] mux select.", size: "1", shift: "11", mask: "0x800" },
			{ name: "SEL12", description: "DATAOUT[12] mux select.", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEL13", description: "DATAOUT[13] mux select.", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SEL14", description: "DATAOUT[14] mux select.", size: "1", shift: "14", mask: "0x4000" },
			{ name: "SEL15", description: "DATAOUT[15] mux select.", size: "1", shift: "15", mask: "0x8000" },
			{ name: "SEL16", description: "DATAOUT[16] mux select.", size: "1", shift: "16", mask: "0x10000" },
			{ name: "SEL17", description: "DATAOUT[17] mux select.", size: "1", shift: "17", mask: "0x20000" },
			{ name: "SEL18", description: "DATAOUT[18] mux select.", size: "1", shift: "18", mask: "0x40000" },
			{ name: "SEL19", description: "DATAOUT[19] mux select.", size: "1", shift: "19", mask: "0x80000" },
			{ name: "SEL20", description: "DATAOUT[20] mux select.", size: "1", shift: "20", mask: "0x100000" },
			{ name: "SEL21", description: "DATAOUT[21] mux select.", size: "1", shift: "21", mask: "0x200000" },
			{ name: "SEL22", description: "DATAOUT[22] mux select.", size: "1", shift: "22", mask: "0x400000" },
			{ name: "SEL23", description: "DATAOUT[23] mux select.", size: "1", shift: "23", mask: "0x800000" },
			{ name: "SEL24", description: "DATAOUT[24] mux select.", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "SEL25", description: "DATAOUT[25] mux select.", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "SEL26", description: "DATAOUT[26] mux select.", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "SEL27", description: "DATAOUT[27] mux select.", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "SEL28", description: "DATAOUT[28] mux select.", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "SEL29", description: "DATAOUT[29] mux select.", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "SEL30", description: "DATAOUT[30] mux select.", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "SEL31", description: "DATAOUT[31] mux select.", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "MXSEL1", description: "EPG Mux select register 1", offset: "0x2",
		bits: [
			{ name: "SEL32", description: "DATAOUT[32] mux select.", size: "1", shift: "0", mask: "0x1" },
			{ name: "SEL33", description: "DATAOUT[33] mux select.", size: "1", shift: "1", mask: "0x2" },
			{ name: "SEL34", description: "DATAOUT[34] mux select.", size: "1", shift: "2", mask: "0x4" },
			{ name: "SEL35", description: "DATAOUT[35] mux select.", size: "1", shift: "3", mask: "0x8" },
			{ name: "SEL36", description: "DATAOUT[36] mux select.", size: "1", shift: "4", mask: "0x10" },
			{ name: "SEL37", description: "DATAOUT[37] mux select.", size: "1", shift: "5", mask: "0x20" },
			{ name: "SEL38", description: "DATAOUT[38] mux select.", size: "1", shift: "6", mask: "0x40" },
			{ name: "SEL39", description: "DATAOUT[39] mux select.", size: "1", shift: "7", mask: "0x80" },
			{ name: "SEL40", description: "DATAOUT[40] mux select.", size: "1", shift: "8", mask: "0x100" },
			{ name: "SEL41", description: "DATAOUT[41] mux select.", size: "1", shift: "9", mask: "0x200" },
			{ name: "SEL42", description: "DATAOUT[42] mux select.", size: "1", shift: "10", mask: "0x400" },
			{ name: "SEL43", description: "DATAOUT[43] mux select.", size: "1", shift: "11", mask: "0x800" },
			{ name: "SEL44", description: "DATAOUT[44] mux select.", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEL45", description: "DATAOUT[45] mux select.", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SEL46", description: "DATAOUT[46] mux select.", size: "1", shift: "14", mask: "0x4000" },
			{ name: "SEL47", description: "DATAOUT[47] mux select.", size: "1", shift: "15", mask: "0x8000" },
			{ name: "SEL48", description: "DATAOUT[48] mux select.", size: "1", shift: "16", mask: "0x10000" },
			{ name: "SEL49", description: "DATAOUT[49] mux select.", size: "1", shift: "17", mask: "0x20000" },
			{ name: "SEL50", description: "DATAOUT[50] mux select.", size: "1", shift: "18", mask: "0x40000" },
			{ name: "SEL51", description: "DATAOUT[51] mux select.", size: "1", shift: "19", mask: "0x80000" },
			{ name: "SEL52", description: "DATAOUT[52] mux select.", size: "1", shift: "20", mask: "0x100000" },
			{ name: "SEL53", description: "DATAOUT[53] mux select.", size: "1", shift: "21", mask: "0x200000" },
			{ name: "SEL54", description: "DATAOUT[54] mux select.", size: "1", shift: "22", mask: "0x400000" },
			{ name: "SEL55", description: "DATAOUT[55] mux select.", size: "1", shift: "23", mask: "0x800000" },
			{ name: "SEL56", description: "DATAOUT[56] mux select.", size: "1", shift: "24", mask: "0x1000000" },
			{ name: "SEL57", description: "DATAOUT[57] mux select.", size: "1", shift: "25", mask: "0x2000000" },
			{ name: "SEL58", description: "DATAOUT[58] mux select.", size: "1", shift: "26", mask: "0x4000000" },
			{ name: "SEL59", description: "DATAOUT[59] mux select.", size: "1", shift: "27", mask: "0x8000000" },
			{ name: "SEL60", description: "DATAOUT[60] mux select.", size: "1", shift: "28", mask: "0x10000000" },
			{ name: "SEL61", description: "DATAOUT[61] mux select.", size: "1", shift: "29", mask: "0x20000000" },
			{ name: "SEL62", description: "DATAOUT[62] mux select.", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "SEL63", description: "DATAOUT[63] mux select.", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "MXSELLOCK", description: "EPG Mux select register lock", offset: "0xC",
		bits: [
			{ name: "EPGMXSEL0", description: "EPGMXSEL0 lock bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EPGMXSEL1", description: "EPGMXSEL1 lock bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "MXSELCOMMIT", description: "EPG Mux select register commit", offset: "0xE",
		bits: [
			{ name: "EPGMXSEL0", description: "EPGMXSEL0 commit bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "EPGMXSEL1", description: "EPGMXSEL1 commit bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
];
module.exports = {
	EPGRegisters: EPGRegisters,
}
