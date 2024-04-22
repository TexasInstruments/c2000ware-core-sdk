let ADCRegisters = [
	{ name: "CTL1", description: "ADC Control 1 Register", offset: "0x0",
		bits: [
			{ name: "INTPULSEPOS", description: "ADC Interrupt Pulse Position", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADCPWDNZ", description: "ADC Power Down", size: "1", shift: "7", mask: "0x80" },
			{ name: "ADCBSYCHN", description: "ADC Busy Channel", size: "4", shift: "8", mask: "0xF00" },
			{ name: "ADCBSY", description: "ADC Busy", size: "1", shift: "13", mask: "0x2000" },
			{ name: "EXTMUXPRESELECTEN", description: "External Mux Preselect Enable", size: "1", shift: "14", mask: "0x4000" },
			{ name: "TDMAEN", description: "Enable Alternate DMA Timings", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CTL2", description: "ADC Control 2 Register", offset: "0x1",
		bits: [
			{ name: "PRESCALE", description: "ADC Clock Prescaler", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "BURSTCTL", description: "ADC Burst Control Register", offset: "0x6",
		bits: [
			{ name: "BURSTTRIGSEL", description: "SOC Burst Trigger Source Select", size: "7", shift: "0", mask: "0x7F" },
			{ name: "BURSTSIZE", description: "SOC Burst Size Select", size: "4", shift: "8", mask: "0xF00" },
			{ name: "BURSTEN", description: "SOC Burst Mode Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "INTFLG", description: "ADC Interrupt Flag Register", offset: "0x7",
		bits: [
			{ name: "ADCINT1", description: "ADC Interrupt 1 Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2", description: "ADC Interrupt 2 Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCINT3", description: "ADC Interrupt 3 Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADCINT4", description: "ADC Interrupt 4 Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "ADCINT1RESULT", description: "ADC Interrupt 1 Results Ready", size: "1", shift: "4", mask: "0x10" },
			{ name: "ADCINT2RESULT", description: "ADC Interrupt 2 Results Ready", size: "1", shift: "5", mask: "0x20" },
			{ name: "ADCINT3RESULT", description: "ADC Interrupt 3 Results Ready", size: "1", shift: "6", mask: "0x40" },
			{ name: "ADCINT4RESULT", description: "ADC Interrupt 4 Results Ready", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "INTFLGCLR", description: "ADC Interrupt Flag Clear Register", offset: "0x8",
		bits: [
			{ name: "ADCINT1", description: "ADC Interrupt 1 Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2", description: "ADC Interrupt 2 Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCINT3", description: "ADC Interrupt 3 Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADCINT4", description: "ADC Interrupt 4 Flag Clear", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "INTOVF", description: "ADC Interrupt Overflow Register", offset: "0x9",
		bits: [
			{ name: "ADCINT1", description: "ADC Interrupt 1 Overflow Flags", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2", description: "ADC Interrupt 2 Overflow Flags", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCINT3", description: "ADC Interrupt 3 Overflow Flags", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADCINT4", description: "ADC Interrupt 4 Overflow Flags", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "INTOVFCLR", description: "ADC Interrupt Overflow Clear Register", offset: "0xA",
		bits: [
			{ name: "ADCINT1", description: "ADC Interrupt 1 Overflow Clear Bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2", description: "ADC Interrupt 2 Overflow Clear Bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCINT3", description: "ADC Interrupt 3 Overflow Clear Bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADCINT4", description: "ADC Interrupt 4 Overflow Clear Bits", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "INTSEL1N2", description: "ADC Interrupt 1 and 2 Selection Register", offset: "0xB",
		bits: [
			{ name: "INT1SEL", description: "ADCINT1 EOC Source Select", size: "6", shift: "0", mask: "0x3F" },
			{ name: "INT1CONT", description: "ADCINT1 Continue to Interrupt Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT1E", description: "ADCINT1 Interrupt Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "INT2SEL", description: "ADCINT2 EOC Source Select", size: "6", shift: "8", mask: "0x3F00" },
			{ name: "INT2CONT", description: "ADCINT2 Continue to Interrupt Mode", size: "1", shift: "14", mask: "0x4000" },
			{ name: "INT2E", description: "ADCINT2 Interrupt Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "INTSEL3N4", description: "ADC Interrupt 3 and 4 Selection Register", offset: "0xC",
		bits: [
			{ name: "INT3SEL", description: "ADCINT3 EOC Source Select", size: "6", shift: "0", mask: "0x3F" },
			{ name: "INT3CONT", description: "ADCINT3 Continue to Interrupt Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT3E", description: "ADCINT3 Interrupt Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "INT4SEL", description: "ADCINT4 EOC Source Select", size: "6", shift: "8", mask: "0x3F00" },
			{ name: "INT4CONT", description: "ADCINT4 Continue to Interrupt Mode", size: "1", shift: "14", mask: "0x4000" },
			{ name: "INT4E", description: "ADCINT4 Interrupt Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SOCPRICTL", description: "ADC SOC Priority Control Register", offset: "0xD",
		bits: [
			{ name: "SOCPRIORITY", description: "SOC Priority", size: "5", shift: "0", mask: "0x1F" },
			{ name: "RRPOINTER", description: "Round Robin Pointer", size: "5", shift: "6", mask: "0x7C0" },
		]
	},
	{ name: "INTSOCSEL1", description: "ADC Interrupt SOC Selection 1 Register", offset: "0xE",
		bits: [
			{ name: "SOC0", description: "SOC0 ADC Interrupt Trigger Select", size: "2", shift: "0", mask: "0x3" },
			{ name: "SOC1", description: "SOC1 ADC Interrupt Trigger Select", size: "2", shift: "2", mask: "0xC" },
			{ name: "SOC2", description: "SOC2 ADC Interrupt Trigger Select", size: "2", shift: "4", mask: "0x30" },
			{ name: "SOC3", description: "SOC3 ADC Interrupt Trigger Select", size: "2", shift: "6", mask: "0xC0" },
			{ name: "SOC4", description: "SOC4 ADC Interrupt Trigger Select", size: "2", shift: "8", mask: "0x300" },
			{ name: "SOC5", description: "SOC5 ADC Interrupt Trigger Select", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SOC6", description: "SOC6 ADC Interrupt Trigger Select", size: "2", shift: "12", mask: "0x3000" },
			{ name: "SOC7", description: "SOC7 ADC Interrupt Trigger Select", size: "2", shift: "14", mask: "0xC000" },
			{ name: "SOC8", description: "SOC8 ADC Interrupt Trigger Select", size: "2", shift: "16", mask: "0x30000" },
			{ name: "SOC9", description: "SOC9 ADC Interrupt Trigger Select", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "SOC10", description: "SOC10 ADC Interrupt Trigger Select", size: "2", shift: "20", mask: "0x300000" },
			{ name: "SOC11", description: "SOC11 ADC Interrupt Trigger Select", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "SOC12", description: "SOC12 ADC Interrupt Trigger Select", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "SOC13", description: "SOC13 ADC Interrupt Trigger Select", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "SOC14", description: "SOC14 ADC Interrupt Trigger Select", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "SOC15", description: "SOC15 ADC Interrupt Trigger Select", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "SOCFLG1", description: "ADC SOC Flag 1 Register", offset: "0x12",
		bits: [
			{ name: "SOC0", description: "SOC0 Start of Conversion Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOC1", description: "SOC1 Start of Conversion Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "SOC2", description: "SOC2 Start of Conversion Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "SOC3", description: "SOC3 Start of Conversion Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "SOC4", description: "SOC4 Start of Conversion Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "SOC5", description: "SOC5 Start of Conversion Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "SOC6", description: "SOC6 Start of Conversion Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "SOC7", description: "SOC7 Start of Conversion Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "SOC8", description: "SOC8 Start of Conversion Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "SOC9", description: "SOC9 Start of Conversion Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "SOC10", description: "SOC10 Start of Conversion Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "SOC11", description: "SOC11 Start of Conversion Flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "SOC12", description: "SOC12 Start of Conversion Flag", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SOC13", description: "SOC13 Start of Conversion Flag", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SOC14", description: "SOC14 Start of Conversion Flag", size: "1", shift: "14", mask: "0x4000" },
			{ name: "SOC15", description: "SOC15 Start of Conversion Flag", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SOCFRC1", description: "ADC SOC Force 1 Register", offset: "0x14",
		bits: [
			{ name: "SOC0", description: "SOC0 Force Start of Conversion Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOC1", description: "SOC1 Force Start of Conversion Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SOC2", description: "SOC2 Force Start of Conversion Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "SOC3", description: "SOC3 Force Start of Conversion Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "SOC4", description: "SOC4 Force Start of Conversion Bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "SOC5", description: "SOC5 Force Start of Conversion Bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "SOC6", description: "SOC6 Force Start of Conversion Bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "SOC7", description: "SOC7 Force Start of Conversion Bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "SOC8", description: "SOC8 Force Start of Conversion Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "SOC9", description: "SOC9 Force Start of Conversion Bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "SOC10", description: "SOC10 Force Start of Conversion Bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "SOC11", description: "SOC11 Force Start of Conversion Bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "SOC12", description: "SOC12 Force Start of Conversion Bit", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SOC13", description: "SOC13 Force Start of Conversion Bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SOC14", description: "SOC14 Force Start of Conversion Bit", size: "1", shift: "14", mask: "0x4000" },
			{ name: "SOC15", description: "SOC15 Force Start of Conversion Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SOCOVF1", description: "ADC SOC Overflow 1 Register", offset: "0x16",
		bits: [
			{ name: "SOC0", description: "SOC0 Start of Conversion Overflow Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOC1", description: "SOC1 Start of Conversion Overflow Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "SOC2", description: "SOC2 Start of Conversion Overflow Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "SOC3", description: "SOC3 Start of Conversion Overflow Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "SOC4", description: "SOC4 Start of Conversion Overflow Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "SOC5", description: "SOC5 Start of Conversion Overflow Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "SOC6", description: "SOC6 Start of Conversion Overflow Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "SOC7", description: "SOC7 Start of Conversion Overflow Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "SOC8", description: "SOC8 Start of Conversion Overflow Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "SOC9", description: "SOC9 Start of Conversion Overflow Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "SOC10", description: "SOC10 Start of Conversion Overflow Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "SOC11", description: "SOC11 Start of Conversion Overflow Flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "SOC12", description: "SOC12 Start of Conversion Overflow Flag", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SOC13", description: "SOC13 Start of Conversion Overflow Flag", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SOC14", description: "SOC14 Start of Conversion Overflow Flag", size: "1", shift: "14", mask: "0x4000" },
			{ name: "SOC15", description: "SOC15 Start of Conversion Overflow Flag", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SOCOVFCLR1", description: "ADC SOC Overflow Clear 1 Register", offset: "0x18",
		bits: [
			{ name: "SOC0", description: "SOC0 Clear Start of Conversion Overflow Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOC1", description: "SOC1 Clear Start of Conversion Overflow Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SOC2", description: "SOC2 Clear Start of Conversion Overflow Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "SOC3", description: "SOC3 Clear Start of Conversion Overflow Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "SOC4", description: "SOC4 Clear Start of Conversion Overflow Bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "SOC5", description: "SOC5 Clear Start of Conversion Overflow Bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "SOC6", description: "SOC6 Clear Start of Conversion Overflow Bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "SOC7", description: "SOC7 Clear Start of Conversion Overflow Bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "SOC8", description: "SOC8 Clear Start of Conversion Overflow Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "SOC9", description: "SOC9 Clear Start of Conversion Overflow Bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "SOC10", description: "SOC10 Clear Start of Conversion Overflow Bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "SOC11", description: "SOC11 Clear Start of Conversion Overflow Bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "SOC12", description: "SOC12 Clear Start of Conversion Overflow Bit", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SOC13", description: "SOC13 Clear Start of Conversion Overflow Bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SOC14", description: "SOC14 Clear Start of Conversion Overflow Bit", size: "1", shift: "14", mask: "0x4000" },
			{ name: "SOC15", description: "SOC15 Clear Start of Conversion Overflow Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SOC0CTL", description: "ADC SOC0 Control Register", offset: "0x1A",
		bits: [
			{ name: "ACQPS", description: "SOC0 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC0 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC0 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC0 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC0 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC1CTL", description: "ADC SOC1 Control Register", offset: "0x1C",
		bits: [
			{ name: "ACQPS", description: "SOC1 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC1 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC1 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC1 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC1 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC2CTL", description: "ADC SOC2 Control Register", offset: "0x1E",
		bits: [
			{ name: "ACQPS", description: "SOC2 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC2 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC2 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC2 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC2 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC3CTL", description: "ADC SOC3 Control Register", offset: "0x20",
		bits: [
			{ name: "ACQPS", description: "SOC3 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC3 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC3 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC3 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC3 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC4CTL", description: "ADC SOC4 Control Register", offset: "0x22",
		bits: [
			{ name: "ACQPS", description: "SOC4 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC4 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC4 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC4 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC4 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC5CTL", description: "ADC SOC5 Control Register", offset: "0x24",
		bits: [
			{ name: "ACQPS", description: "SOC5 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC5 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC5 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC5 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC5 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC6CTL", description: "ADC SOC6 Control Register", offset: "0x26",
		bits: [
			{ name: "ACQPS", description: "SOC6 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC6 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC6 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC6 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC6 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC7CTL", description: "ADC SOC7 Control Register", offset: "0x28",
		bits: [
			{ name: "ACQPS", description: "SOC7 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC7 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC7 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC7 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC7 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC8CTL", description: "ADC SOC8 Control Register", offset: "0x2A",
		bits: [
			{ name: "ACQPS", description: "SOC8 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC8 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC8 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC8 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC8 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC9CTL", description: "ADC SOC9 Control Register", offset: "0x2C",
		bits: [
			{ name: "ACQPS", description: "SOC9 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC9 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC9 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC9 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC9 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC10CTL", description: "ADC SOC10 Control Register", offset: "0x2E",
		bits: [
			{ name: "ACQPS", description: "SOC10 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC10 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC10 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC10 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC10 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC11CTL", description: "ADC SOC11 Control Register", offset: "0x30",
		bits: [
			{ name: "ACQPS", description: "SOC11 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC11 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC11 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC11 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC11 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC12CTL", description: "ADC SOC12 Control Register", offset: "0x32",
		bits: [
			{ name: "ACQPS", description: "SOC12 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC12 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC12 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC12 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC12 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC13CTL", description: "ADC SOC13 Control Register", offset: "0x34",
		bits: [
			{ name: "ACQPS", description: "SOC13 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC13 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC13 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC13 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC13 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC14CTL", description: "ADC SOC14 Control Register", offset: "0x36",
		bits: [
			{ name: "ACQPS", description: "SOC14 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC14 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC14 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC14 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC14 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC15CTL", description: "ADC SOC15 Control Register", offset: "0x38",
		bits: [
			{ name: "ACQPS", description: "SOC15 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC15 Sample Cap Reset Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHSEL", description: "SOC15 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC15 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC15 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "EVTSTAT", description: "ADC Event Status Register", offset: "0x5A",
		bits: [
			{ name: "PPB1TRIPHI", description: "Post Processing Block 1 Trip High Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "PPB1TRIPLO", description: "Post Processing Block 1 Trip Low Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "PPB1ZERO", description: "Post Processing Block 1 Zero Crossing Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "PPB2TRIPHI", description: "Post Processing Block 2 Trip High Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "PPB2TRIPLO", description: "Post Processing Block 2 Trip Low Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "PPB2ZERO", description: "Post Processing Block 2 Zero Crossing Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "PPB3TRIPHI", description: "Post Processing Block 3 Trip High Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "PPB3TRIPLO", description: "Post Processing Block 3 Trip Low Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "PPB3ZERO", description: "Post Processing Block 3 Zero Crossing Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "PPB4TRIPHI", description: "Post Processing Block 4 Trip High Flag", size: "1", shift: "12", mask: "0x1000" },
			{ name: "PPB4TRIPLO", description: "Post Processing Block 4 Trip Low Flag", size: "1", shift: "13", mask: "0x2000" },
			{ name: "PPB4ZERO", description: "Post Processing Block 4 Zero Crossing Flag", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "EVTCLR", description: "ADC Event Clear Register", offset: "0x5C",
		bits: [
			{ name: "PPB1TRIPHI", description: "Post Processing Block 1 Trip High Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "PPB1TRIPLO", description: "Post Processing Block 1 Trip Low Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "PPB1ZERO", description: "Post Processing Block 1 Zero Crossing Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "PPB2TRIPHI", description: "Post Processing Block 2 Trip High Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "PPB2TRIPLO", description: "Post Processing Block 2 Trip Low Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "PPB2ZERO", description: "Post Processing Block 2 Zero Crossing Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "PPB3TRIPHI", description: "Post Processing Block 3 Trip High Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "PPB3TRIPLO", description: "Post Processing Block 3 Trip Low Clear", size: "1", shift: "9", mask: "0x200" },
			{ name: "PPB3ZERO", description: "Post Processing Block 3 Zero Crossing Clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "PPB4TRIPHI", description: "Post Processing Block 4 Trip High Clear", size: "1", shift: "12", mask: "0x1000" },
			{ name: "PPB4TRIPLO", description: "Post Processing Block 4 Trip Low Clear", size: "1", shift: "13", mask: "0x2000" },
			{ name: "PPB4ZERO", description: "Post Processing Block 4 Zero Crossing Clear", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "EVTSEL", description: "ADC Event Selection Register", offset: "0x5E",
		bits: [
			{ name: "PPB1TRIPHI", description: "Post Processing Block 1 Trip High Event Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "PPB1TRIPLO", description: "Post Processing Block 1 Trip Low Event Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "PPB1ZERO", description: "Post Processing Block 1 Zero Crossing Event Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "PPB2TRIPHI", description: "Post Processing Block 2 Trip High Event Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "PPB2TRIPLO", description: "Post Processing Block 2 Trip Low Event Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "PPB2ZERO", description: "Post Processing Block 2 Zero Crossing Event Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "PPB3TRIPHI", description: "Post Processing Block 3 Trip High Event Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "PPB3TRIPLO", description: "Post Processing Block 3 Trip Low Event Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "PPB3ZERO", description: "Post Processing Block 3 Zero Crossing Event Enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "PPB4TRIPHI", description: "Post Processing Block 4 Trip High Event Enable", size: "1", shift: "12", mask: "0x1000" },
			{ name: "PPB4TRIPLO", description: "Post Processing Block 4 Trip Low Event Enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "PPB4ZERO", description: "Post Processing Block 4 Zero Crossing Event Enable", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "EVTINTSEL", description: "ADC Event Interrupt Selection Register", offset: "0x60",
		bits: [
			{ name: "PPB1TRIPHI", description: "Post Processing Block 1 Trip High Interrupt Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "PPB1TRIPLO", description: "Post Processing Block 1 Trip Low Interrupt Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "PPB1ZERO", description: "Post Processing Block 1 Zero Crossing Interrupt", size: "1", shift: "2", mask: "0x4" },
			{ name: "PPB2TRIPHI", description: "Post Processing Block 2 Trip High Interrupt Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "PPB2TRIPLO", description: "Post Processing Block 2 Trip Low Interrupt Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "PPB2ZERO", description: "Post Processing Block 2 Zero Crossing Interrupt", size: "1", shift: "6", mask: "0x40" },
			{ name: "PPB3TRIPHI", description: "Post Processing Block 3 Trip High Interrupt Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "PPB3TRIPLO", description: "Post Processing Block 3 Trip Low Interrupt Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "PPB3ZERO", description: "Post Processing Block 3 Zero Crossing Interrupt", size: "1", shift: "10", mask: "0x400" },
			{ name: "PPB4TRIPHI", description: "Post Processing Block 4 Trip High Interrupt Enable", size: "1", shift: "12", mask: "0x1000" },
			{ name: "PPB4TRIPLO", description: "Post Processing Block 4 Trip Low Interrupt Enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "PPB4ZERO", description: "Post Processing Block 4 Zero Crossing Interrupt", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "COUNTER", description: "ADC Counter Register", offset: "0x63",
		bits: [
			{ name: "FREECOUNT", description: "ADC Free Running Counter Value", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "REV", description: "ADC Revision Register", offset: "0x64",
		bits: [
			{ name: "TYPE", description: "ADC Type", size: "8", shift: "0", mask: "0xFF" },
			{ name: "REV", description: "ADC Revision", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "OFFTRIM", description: "ADC Offset Trim Register", offset: "0x65",
		bits: [
			{ name: "OFFTRIM", description: "ADC Offset Trim", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "CONFIG2", description: "ADC Config Register Upper 32 bits", offset: "0x66",
		bits: [
			{ name: "TESTANA1_CONFIG", description: "TESTANA1 ADC Configuration", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "PPB1CONFIG", description: "ADC PPB{#} Config Register", offset: "0x6A",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 1 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "ABSEN", description: "ADC Post Processing Block 1 Absolute Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 1 Two's Complement Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "DELTAEN", description: "ADC Post Processing Block 1 Last Sample Delta", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "PPB1STAMP", description: "ADC PPB1 Sample Delay Time Stamp Register", offset: "0x6B",
		bits: [
			{ name: "DLYSTAMP", description: "ADC Post Processing Block 1 Delay Time Stamp", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB1OFFCAL", description: "ADC PPB1 Offset Calibration Register", offset: "0x6C",
		bits: [
			{ name: "OFFCAL", description: "ADC Post Processing Block Offset Correction", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1OFFREF", description: "ADC PPB1 Offset Reference Register", offset: "0x6D",
		bits: [
		]
	},
	{ name: "PPB1TRIPHI", description: "ADC PPB1 Trip High Register", offset: "0x6E",
		bits: [
			{ name: "LIMITHI", description: "ADC Post Processing Block 1 Trip High Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB1TRIPLO", description: "ADC PPB1 Trip Low/Trigger Time Stamp Register", offset: "0x70",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 1 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "LIMITLO2EN", description: "Extended Low Limit 2 Enable", size: "1", shift: "19", mask: "0x80000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 1 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
		]
	},
	{ name: "PPBTRIP1FILCTL", description: "ADCEVT1 Trip High Filter Control Register", offset: "0x72",
		bits: [
			{ name: "FILTHIEN", description: "ADCPPB1 TRIPHI Filter Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "FILTLOEN", description: "ADCPPB1 TRIPLO Filter Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "SAMPWIN", description: "Sample Window", size: "6", shift: "3", mask: "0x1F8" },
			{ name: "THRESH", description: "Majority Voting Threshold", size: "6", shift: "9", mask: "0x7E00" },
			{ name: "FILINIT", description: "Filter Initialization Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "PPBTRIP1FILCLKCTL", description: "ADCEVT1 Trip High Filter Prescale Control Register", offset: "0x74",
		bits: [
			{ name: "CLKPRESCALE", description: "Filter Clock Prescale", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "PPB2CONFIG", description: "ADC PPB{#} Config Register", offset: "0x7A",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 2 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "ABSEN", description: "ADC Post Processing Block 2 Absolute Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 2 Two's Complement Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "DELTAEN", description: "ADC Post Processing Block 2 Last Sample Delta", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "PPB2STAMP", description: "ADC PPB2 Sample Delay Time Stamp Register", offset: "0x7B",
		bits: [
			{ name: "DLYSTAMP", description: "ADC Post Processing Block 2 Delay Time Stamp", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB2OFFCAL", description: "ADC PPB2 Offset Calibration Register", offset: "0x7C",
		bits: [
			{ name: "OFFCAL", description: "ADC Post Processing Block Offset Correction", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2OFFREF", description: "ADC PPB2 Offset Reference Register", offset: "0x7D",
		bits: [
		]
	},
	{ name: "PPB2TRIPHI", description: "ADC PPB2 Trip High Register", offset: "0x7E",
		bits: [
			{ name: "LIMITHI", description: "ADC Post Processing Block 2 Trip High Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB2TRIPLO", description: "ADC PPB2 Trip Low/Trigger Time Stamp Register", offset: "0x80",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 2 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "LIMITLO2EN", description: "Extended Low Limit 2 Enable", size: "1", shift: "19", mask: "0x80000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 2 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
		]
	},
	{ name: "PPBTRIP2FILCTL", description: "ADCEVT2 Trip High Filter Control Register", offset: "0x82",
		bits: [
			{ name: "FILTHIEN", description: "ADCPPB2 TRIPHI Filter Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "FILTLOEN", description: "ADCPPB2 TRIPLO Filter Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "SAMPWIN", description: "Sample Window", size: "6", shift: "3", mask: "0x1F8" },
			{ name: "THRESH", description: "Majority Voting Threshold", size: "6", shift: "9", mask: "0x7E00" },
			{ name: "FILINIT", description: "Filter Initialization Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "PPBTRIP2FILCLKCTL", description: "ADCEVT2 Trip High Filter Prescale Control Register", offset: "0x84",
		bits: [
			{ name: "CLKPRESCALE", description: "Filter Clock Prescale", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "PPB3CONFIG", description: "ADC PPB{#} Config Register", offset: "0x8A",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 3 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "ABSEN", description: "ADC Post Processing Block 3 Absolute Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 3 Two's Complement Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "DELTAEN", description: "ADC Post Processing Block 3 Last Sample Delta", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "PPB3STAMP", description: "ADC PPB3 Sample Delay Time Stamp Register", offset: "0x8B",
		bits: [
			{ name: "DLYSTAMP", description: "ADC Post Processing Block 3 Delay Time Stamp", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB3OFFCAL", description: "ADC PPB3 Offset Calibration Register", offset: "0x8C",
		bits: [
			{ name: "OFFCAL", description: "ADC Post Processing Block Offset Correction", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3OFFREF", description: "ADC PPB3 Offset Reference Register", offset: "0x8D",
		bits: [
		]
	},
	{ name: "PPB3TRIPHI", description: "ADC PPB3 Trip High Register", offset: "0x8E",
		bits: [
			{ name: "LIMITHI", description: "ADC Post Processing Block 3 Trip High Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB3TRIPLO", description: "ADC PPB3 Trip Low/Trigger Time Stamp Register", offset: "0x90",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 3 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "LIMITLO2EN", description: "Extended Low Limit 2 Enable", size: "1", shift: "19", mask: "0x80000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 3 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
		]
	},
	{ name: "PPBTRIP3FILCTL", description: "ADCEVT3 Trip High Filter Control Register", offset: "0x92",
		bits: [
			{ name: "FILTHIEN", description: "ADCPPB3 TRIPHI Filter Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "FILTLOEN", description: "ADCPPB3 TRIPLO Filter Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "SAMPWIN", description: "Sample Window", size: "6", shift: "3", mask: "0x1F8" },
			{ name: "THRESH", description: "Majority Voting Threshold", size: "6", shift: "9", mask: "0x7E00" },
			{ name: "FILINIT", description: "Filter Initialization Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "PPBTRIP3FILCLKCTL", description: "ADCEVT3 Trip High Filter Prescale Control Register", offset: "0x94",
		bits: [
			{ name: "CLKPRESCALE", description: "Filter Clock Prescale", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "PPB4CONFIG", description: "ADC PPB{#} Config Register", offset: "0x9A",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 4 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "ABSEN", description: "ADC Post Processing Block 4 Absolute Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 4 Two's Complement Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "DELTAEN", description: "ADC Post Processing Block 4 Last Sample Delta", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "PPB4STAMP", description: "ADC PPB4 Sample Delay Time Stamp Register", offset: "0x9B",
		bits: [
			{ name: "DLYSTAMP", description: "ADC Post Processing Block 4 Delay Time Stamp", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB4OFFCAL", description: "ADC PPB4 Offset Calibration Register", offset: "0x9C",
		bits: [
			{ name: "OFFCAL", description: "ADC Post Processing Block Offset Correction", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4OFFREF", description: "ADC PPB4 Offset Reference Register", offset: "0x9D",
		bits: [
		]
	},
	{ name: "PPB4TRIPHI", description: "ADC PPB4 Trip High Register", offset: "0x9E",
		bits: [
			{ name: "LIMITHI", description: "ADC Post Processing Block 4 Trip High Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB4TRIPLO", description: "ADC PPB4 Trip Low/Trigger Time Stamp Register", offset: "0xA0",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 4 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "LIMITLO2EN", description: "Extended Low Limit 2 Enable", size: "1", shift: "19", mask: "0x80000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 4 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
		]
	},
	{ name: "PPBTRIP4FILCTL", description: "ADCEVT4 Trip High Filter Control Register", offset: "0xA2",
		bits: [
			{ name: "FILTHIEN", description: "ADCPPB4 TRIPHI Filter Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "FILTLOEN", description: "ADCPPB4 TRIPLO Filter Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "SAMPWIN", description: "Sample Window", size: "6", shift: "3", mask: "0x1F8" },
			{ name: "THRESH", description: "Majority Voting Threshold", size: "6", shift: "9", mask: "0x7E00" },
			{ name: "FILINIT", description: "Filter Initialization Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "PPBTRIP4FILCLKCTL", description: "ADCEVT4 Trip High Filter Prescale Control Register", offset: "0xA4",
		bits: [
			{ name: "CLKPRESCALE", description: "Filter Clock Prescale", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "INTCYCLE", description: "ADC Early Interrupt Generation Cycle", offset: "0xB9",
		bits: [
		]
	},
	{ name: "INLTRIM1", description: "ADC Linearity Trim 1 Register", offset: "0xBA",
		bits: [
		]
	},
	{ name: "INLTRIM2", description: "ADC Linearity Trim 2 Register", offset: "0xBC",
		bits: [
		]
	},
	{ name: "INLTRIM3", description: "ADC Linearity Trim 3 Register", offset: "0xBE",
		bits: [
		]
	},
	{ name: "INLTRIM4", description: "ADC Linearity Trim 4 Register", offset: "0xC0",
		bits: [
		]
	},
	{ name: "INLTRIM5", description: "ADC Linearity Trim 5 Register", offset: "0xC2",
		bits: [
		]
	},
	{ name: "INLTRIM6", description: "ADC Linearity Trim 6 Register", offset: "0xC4",
		bits: [
		]
	},
	{ name: "REV2", description: "ADC Wrapper Revision Register", offset: "0xC7",
		bits: [
			{ name: "WRAPPERTYPE", description: "ADC Wrapper Type", size: "8", shift: "0", mask: "0xFF" },
			{ name: "WRAPPERREV", description: "ADC Wrapper Revision", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "REP1CTL", description: "ADC Trigger Repeater 1 Control Register", offset: "0xCA",
		bits: [
			{ name: "MODE", description: "ADC Trigger Repeater 1 Mode Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "ACTIVEMODE", description: "ADC Trigger Repeater 1 Active Mode", size: "1", shift: "1", mask: "0x2" },
			{ name: "MODULEBUSY", description: "ADC Trigger Repeater 1 Module Busy", size: "1", shift: "3", mask: "0x8" },
			{ name: "PHASEOVF", description: "ADC Trigger Repeater 1 Phase Delay Overflow", size: "1", shift: "6", mask: "0x40" },
			{ name: "TRIGGEROVF", description: "ADC Trigger Repeater 1 Oversampled Trigger", size: "1", shift: "7", mask: "0x80" },
			{ name: "TRIGGER", description: "ADC Trigger Repeater 1 Trigger Select", size: "7", shift: "8", mask: "0x7F00" },
			{ name: "SYNCINSEL", description: "ADC Trigger Repeater 1 Sync. In Select", size: "6", shift: "16", mask: "0x3F0000" },
			{ name: "SWSYNC", description: "ADC Trigger Repeater 1 Software Sync.", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "REP1N", description: "ADC Trigger Repeater 1 N Select Register", offset: "0xCC",
		bits: [
			{ name: "NSEL", description: "ADC Trigger Repeater 1 Trigger Number Selection", size: "7", shift: "0", mask: "0x7F" },
			{ name: "NCOUNT", description: "ADC Trigger Repeater 1 Trigger Counter", size: "7", shift: "16", mask: "0x7F0000" },
		]
	},
	{ name: "REP1PHASE", description: "ADC Trigger Repeater 1 Phase Select Register", offset: "0xCE",
		bits: [
			{ name: "PHASE", description: "ADC Trigger Repeater 1 Phase Delay", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "PHASECOUNT", description: "ADC Trigger Repeater 1 Phase Delay Status", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "REP1SPREAD", description: "ADC Trigger Repeater 1 Spread Select Register", offset: "0xD0",
		bits: [
			{ name: "SPREAD", description: "ADC Trigger Repeater 1 Spread Delay", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SPREADCOUNT", description: "ADC Trigger Repeater 1 Spread Delay Status", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "REP1FRC", description: "ADC Trigger Repeater 1 Software Force Register", offset: "0xD2",
		bits: [
			{ name: "SWFRC", description: "ADC Trigger Repeater 1 Software Force", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "REP2CTL", description: "ADC Trigger Repeater 2 Control Register", offset: "0xDA",
		bits: [
			{ name: "MODE", description: "ADC Trigger Repeater 2 Mode Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "ACTIVEMODE", description: "ADC Trigger Repeater 2 Active Mode", size: "1", shift: "1", mask: "0x2" },
			{ name: "MODULEBUSY", description: "ADC Trigger Repeater 2 Module Busy", size: "1", shift: "3", mask: "0x8" },
			{ name: "PHASEOVF", description: "ADC Trigger Repeater 2 Phase Delay Overflow", size: "1", shift: "6", mask: "0x40" },
			{ name: "TRIGGEROVF", description: "ADC Trigger Repeater 2 Oversampled Trigger", size: "1", shift: "7", mask: "0x80" },
			{ name: "TRIGGER", description: "ADC Trigger Repeater 2 Trigger Select", size: "7", shift: "8", mask: "0x7F00" },
			{ name: "SYNCINSEL", description: "ADC Trigger Repeater 2 Sync. In Select", size: "6", shift: "16", mask: "0x3F0000" },
			{ name: "SWSYNC", description: "ADC Trigger Repeater 2 Software Sync.", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "REP2N", description: "ADC Trigger Repeater 2 N Select Register", offset: "0xDC",
		bits: [
			{ name: "NSEL", description: "ADC Trigger Repeater 2 Trigger Number Selection", size: "7", shift: "0", mask: "0x7F" },
			{ name: "NCOUNT", description: "ADC Trigger Repeater 2 Trigger Counter", size: "7", shift: "16", mask: "0x7F0000" },
		]
	},
	{ name: "REP2PHASE", description: "ADC Trigger Repeater 2 Phase Select Register", offset: "0xDE",
		bits: [
			{ name: "PHASE", description: "ADC Trigger Repeater 2 Phase Delay", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "PHASECOUNT", description: "ADC Trigger Repeater 2 Phase Delay Status", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "REP2SPREAD", description: "ADC Trigger Repeater 2 Spread Select Register", offset: "0xE0",
		bits: [
			{ name: "SPREAD", description: "ADC Trigger Repeater 2 Spread Delay", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SPREADCOUNT", description: "ADC Trigger Repeater 2 Spread Delay Status", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "REP2FRC", description: "ADC Trigger Repeater 2 Software Force Register", offset: "0xE2",
		bits: [
			{ name: "SWFRC", description: "ADC Trigger Repeater 2 Software Force", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PPB1LIMIT", description: "ADC PPB1Conversion Count Limit Register", offset: "0xEA",
		bits: [
			{ name: "LIMIT", description: "Post Processing Block 1 Limit", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPBP1PCOUNT", description: "ADC PPB1 Partial Conversion Count Register", offset: "0xEC",
		bits: [
			{ name: "PCOUNT", description: "Post Processing Block 1 Partial Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1CONFIG2", description: "ADC PPB1 Sum Shift Register", offset: "0xEE",
		bits: [
			{ name: "SHIFT", description: "Post Processing Block 1 Right Shift", size: "4", shift: "0", mask: "0xF" },
			{ name: "SYNCINSEL", description: "Post Processing Block 1 Sync. Input Select", size: "6", shift: "4", mask: "0x3F0" },
			{ name: "SWSYNC", description: "Post Processing Block 1 Software Force Sync.", size: "1", shift: "11", mask: "0x800" },
			{ name: "OSINTSEL", description: "Post Processing Block 1 Interrupt Source Select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "COMPSEL", description: "Post Processing Block 1 Compare Source Select", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "PPB1PSUM", description: "ADC PPB1 Partial Sum Register", offset: "0xF0",
		bits: [
			{ name: "PSUM", description: "Post Processing Block 1 Oversampling Partial Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB1PMAX", description: "ADC PPB1 Partial Max Register", offset: "0xF2",
		bits: [
			{ name: "PMAX", description: "Post Processing Block 1 Oversampling Partial Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB1PMAXI", description: "ADC PPB1 Partial Max Index Register", offset: "0xF4",
		bits: [
			{ name: "PMAXI", description: "Post Processing Block 1 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1PMIN", description: "ADC PPB1 Partial MIN Register", offset: "0xF6",
		bits: [
			{ name: "PMIN", description: "Post Processing Block 1 Oversampling Partial Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB1PMINI", description: "ADC PPB1 Partial Min Index Register", offset: "0xF8",
		bits: [
			{ name: "PMINI", description: "Post Processing Block 1 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1TRIPLO2", description: "ADC PPB1 Extended Trip Low Register", offset: "0xFA",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 1 Trip Low Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB2LIMIT", description: "ADC PPB2Conversion Count Limit Register", offset: "0x104",
		bits: [
			{ name: "LIMIT", description: "Post Processing Block 2 Limit", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPBP2PCOUNT", description: "ADC PPB2 Partial Conversion Count Register", offset: "0x106",
		bits: [
			{ name: "PCOUNT", description: "Post Processing Block 2 Partial Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2CONFIG2", description: "ADC PPB2 Sum Shift Register", offset: "0x108",
		bits: [
			{ name: "SHIFT", description: "Post Processing Block 2 Right Shift", size: "4", shift: "0", mask: "0xF" },
			{ name: "SYNCINSEL", description: "Post Processing Block 2 Sync. Input Select", size: "6", shift: "4", mask: "0x3F0" },
			{ name: "SWSYNC", description: "Post Processing Block 2 Software Force Sync.", size: "1", shift: "11", mask: "0x800" },
			{ name: "OSINTSEL", description: "Post Processing Block 2 Interrupt Source Select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "COMPSEL", description: "Post Processing Block 2 Compare Source Select", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "PPB2PSUM", description: "ADC PPB2 Partial Sum Register", offset: "0x10A",
		bits: [
			{ name: "PSUM", description: "Post Processing Block 2 Oversampling Partial Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB2PMAX", description: "ADC PPB2 Partial Max Register", offset: "0x10C",
		bits: [
			{ name: "PMAX", description: "Post Processing Block 2 Oversampling Partial Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB2PMAXI", description: "ADC PPB2 Partial Max Index Register", offset: "0x10E",
		bits: [
			{ name: "PMAXI", description: "Post Processing Block 2 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2PMIN", description: "ADC PPB2 Partial MIN Register", offset: "0x110",
		bits: [
			{ name: "PMIN", description: "Post Processing Block 2 Oversampling Partial Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB2PMINI", description: "ADC PPB2 Partial Min Index Register", offset: "0x112",
		bits: [
			{ name: "PMINI", description: "Post Processing Block 2 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2TRIPLO2", description: "ADC PPB2 Extended Trip Low Register", offset: "0x114",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 2 Trip Low Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB3LIMIT", description: "ADC PPB3Conversion Count Limit Register", offset: "0x11E",
		bits: [
			{ name: "LIMIT", description: "Post Processing Block 3 Limit", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPBP3PCOUNT", description: "ADC PPB3 Partial Conversion Count Register", offset: "0x120",
		bits: [
			{ name: "PCOUNT", description: "Post Processing Block 3 Partial Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3CONFIG2", description: "ADC PPB3 Sum Shift Register", offset: "0x122",
		bits: [
			{ name: "SHIFT", description: "Post Processing Block 3 Right Shift", size: "4", shift: "0", mask: "0xF" },
			{ name: "SYNCINSEL", description: "Post Processing Block 3 Sync. Input Select", size: "6", shift: "4", mask: "0x3F0" },
			{ name: "SWSYNC", description: "Post Processing Block 3 Software Force Sync.", size: "1", shift: "11", mask: "0x800" },
			{ name: "OSINTSEL", description: "Post Processing Block 3 Interrupt Source Select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "COMPSEL", description: "Post Processing Block 3 Compare Source Select", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "PPB3PSUM", description: "ADC PPB3 Partial Sum Register", offset: "0x124",
		bits: [
			{ name: "PSUM", description: "Post Processing Block 3 Oversampling Partial Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB3PMAX", description: "ADC PPB3 Partial Max Register", offset: "0x126",
		bits: [
			{ name: "PMAX", description: "Post Processing Block 3 Oversampling Partial Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB3PMAXI", description: "ADC PPB3 Partial Max Index Register", offset: "0x128",
		bits: [
			{ name: "PMAXI", description: "Post Processing Block 3 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3PMIN", description: "ADC PPB3 Partial MIN Register", offset: "0x12A",
		bits: [
			{ name: "PMIN", description: "Post Processing Block 3 Oversampling Partial Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB3PMINI", description: "ADC PPB3 Partial Min Index Register", offset: "0x12C",
		bits: [
			{ name: "PMINI", description: "Post Processing Block 3 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3TRIPLO2", description: "ADC PPB3 Extended Trip Low Register", offset: "0x12E",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 3 Trip Low Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB4LIMIT", description: "ADC PPB4Conversion Count Limit Register", offset: "0x138",
		bits: [
			{ name: "LIMIT", description: "Post Processing Block 4 Limit", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPBP4PCOUNT", description: "ADC PPB4 Partial Conversion Count Register", offset: "0x13A",
		bits: [
			{ name: "PCOUNT", description: "Post Processing Block 4 Partial Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4CONFIG2", description: "ADC PPB4 Sum Shift Register", offset: "0x13C",
		bits: [
			{ name: "SHIFT", description: "Post Processing Block 4 Right Shift", size: "4", shift: "0", mask: "0xF" },
			{ name: "SYNCINSEL", description: "Post Processing Block 4 Sync. Input Select", size: "6", shift: "4", mask: "0x3F0" },
			{ name: "SWSYNC", description: "Post Processing Block 4 Software Force Sync.", size: "1", shift: "11", mask: "0x800" },
			{ name: "OSINTSEL", description: "Post Processing Block 4 Interrupt Source Select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "COMPSEL", description: "Post Processing Block 4 Compare Source Select", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "PPB4PSUM", description: "ADC PPB4 Partial Sum Register", offset: "0x13E",
		bits: [
			{ name: "PSUM", description: "Post Processing Block 4 Oversampling Partial Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB4PMAX", description: "ADC PPB4 Partial Max Register", offset: "0x140",
		bits: [
			{ name: "PMAX", description: "Post Processing Block 4 Oversampling Partial Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB4PMAXI", description: "ADC PPB4 Partial Max Index Register", offset: "0x142",
		bits: [
			{ name: "PMAXI", description: "Post Processing Block 4 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4PMIN", description: "ADC PPB4 Partial MIN Register", offset: "0x144",
		bits: [
			{ name: "PMIN", description: "Post Processing Block 4 Oversampling Partial Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB4PMINI", description: "ADC PPB4 Partial Min Index Register", offset: "0x146",
		bits: [
			{ name: "PMINI", description: "Post Processing Block 4 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4TRIPLO2", description: "ADC PPB4 Extended Trip Low Register", offset: "0x148",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 4 Trip Low Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "RESULT0", description: "ADC Result 0 Register", offset: "0x0",
		bits: [
		]
	},
	{ name: "RESULT1", description: "ADC Result 1 Register", offset: "0x1",
		bits: [
		]
	},
	{ name: "RESULT2", description: "ADC Result 2 Register", offset: "0x2",
		bits: [
		]
	},
	{ name: "RESULT3", description: "ADC Result 3 Register", offset: "0x3",
		bits: [
		]
	},
	{ name: "RESULT4", description: "ADC Result 4 Register", offset: "0x4",
		bits: [
		]
	},
	{ name: "RESULT5", description: "ADC Result 5 Register", offset: "0x5",
		bits: [
		]
	},
	{ name: "RESULT6", description: "ADC Result 6 Register", offset: "0x6",
		bits: [
		]
	},
	{ name: "RESULT7", description: "ADC Result 7 Register", offset: "0x7",
		bits: [
		]
	},
	{ name: "RESULT8", description: "ADC Result 8 Register", offset: "0x8",
		bits: [
		]
	},
	{ name: "RESULT9", description: "ADC Result 9 Register", offset: "0x9",
		bits: [
		]
	},
	{ name: "RESULT10", description: "ADC Result 10 Register", offset: "0xA",
		bits: [
		]
	},
	{ name: "RESULT11", description: "ADC Result 11 Register", offset: "0xB",
		bits: [
		]
	},
	{ name: "RESULT12", description: "ADC Result 12 Register", offset: "0xC",
		bits: [
		]
	},
	{ name: "RESULT13", description: "ADC Result 13 Register", offset: "0xD",
		bits: [
		]
	},
	{ name: "RESULT14", description: "ADC Result 14 Register", offset: "0xE",
		bits: [
		]
	},
	{ name: "RESULT15", description: "ADC Result 15 Register", offset: "0xF",
		bits: [
		]
	},
	{ name: "PPB1RESULT", description: "ADC Post Processing Block 1 Result Register", offset: "0x20",
		bits: [
			{ name: "PPBRESULT", description: "ADC Post Processing Block Result", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "PPB2RESULT", description: "ADC Post Processing Block 2 Result Register", offset: "0x22",
		bits: [
			{ name: "PPBRESULT", description: "ADC Post Processing Block Result", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "PPB3RESULT", description: "ADC Post Processing Block 3 Result Register", offset: "0x24",
		bits: [
			{ name: "PPBRESULT", description: "ADC Post Processing Block Result", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "PPB4RESULT", description: "ADC Post Processing Block 4 Result Register", offset: "0x26",
		bits: [
			{ name: "PPBRESULT", description: "ADC Post Processing Block Result", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "PPB1SUM", description: "ADC PPB 1 Final Sum Result Register", offset: "0x28",
		bits: [
			{ name: "SUM", description: "Post Processing Block 1 Oversampling Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB1COUNT", description: "ADC PPB1 Final Conversion Count Register", offset: "0x2A",
		bits: [
			{ name: "COUNT", description: "Post Processing Block 1 Final Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2SUM", description: "ADC PPB 2 Final Sum Result Register", offset: "0x2C",
		bits: [
			{ name: "SUM", description: "Post Processing Block 2 Oversampling Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB2COUNT", description: "ADC PPB2 Final Conversion Count Register", offset: "0x2E",
		bits: [
			{ name: "COUNT", description: "Post Processing Block 2 Final Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3SUM", description: "ADC PPB 3 Final Sum Result Register", offset: "0x30",
		bits: [
			{ name: "SUM", description: "Post Processing Block 3 Oversampling Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB3COUNT", description: "ADC PPB3 Final Conversion Count Register", offset: "0x32",
		bits: [
			{ name: "COUNT", description: "Post Processing Block 3 Final Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4SUM", description: "ADC PPB 4 Final Sum Result Register", offset: "0x34",
		bits: [
			{ name: "SUM", description: "Post Processing Block 4 Oversampling Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB4COUNT", description: "ADC PPB4 Final Conversion Count Register", offset: "0x36",
		bits: [
			{ name: "COUNT", description: "Post Processing Block 4 Final Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1MAX", description: "ADC PPB 1 Final Max Result Register", offset: "0x38",
		bits: [
			{ name: "MAX", description: "Post Processing Block 1 Oversampling Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB1MAXI", description: "ADC PPB 1 Final Max Index Result Register", offset: "0x3A",
		bits: [
			{ name: "MAXI", description: "Post Processing Block 1 Oversampling Index of Max", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1MIN", description: "ADC PPB 1 Final Min Result Register", offset: "0x3C",
		bits: [
			{ name: "MIN", description: "Post Processing Block 1 Oversampling Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB1MINI", description: "ADC PPB 1 Final Min Index Result Register", offset: "0x3E",
		bits: [
			{ name: "MINI", description: "Post Processing Block 1 Oversampling Index of Min", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2MAX", description: "ADC PPB 2 Final Max Result Register", offset: "0x40",
		bits: [
			{ name: "MAX", description: "Post Processing Block 2 Oversampling Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB2MAXI", description: "ADC PPB 2 Final Max Index Result Register", offset: "0x42",
		bits: [
			{ name: "MAXI", description: "Post Processing Block 2 Oversampling Index of Max", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2MIN", description: "ADC PPB 2 Final Min Result Register", offset: "0x44",
		bits: [
			{ name: "MIN", description: "Post Processing Block 2 Oversampling Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB2MINI", description: "ADC PPB 2 Final Min Index Result Register", offset: "0x46",
		bits: [
			{ name: "MINI", description: "Post Processing Block 2 Oversampling Index of Min", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3MAX", description: "ADC PPB 3 Final Max Result Register", offset: "0x48",
		bits: [
			{ name: "MAX", description: "Post Processing Block 3 Oversampling Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB3MAXI", description: "ADC PPB 3 Final Max Index Result Register", offset: "0x4A",
		bits: [
			{ name: "MAXI", description: "Post Processing Block 3 Oversampling Index of Max", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3MIN", description: "ADC PPB 3 Final Min Result Register", offset: "0x4C",
		bits: [
			{ name: "MIN", description: "Post Processing Block 3 Oversampling Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB3MINI", description: "ADC PPB 3 Final Min Index Result Register", offset: "0x4E",
		bits: [
			{ name: "MINI", description: "Post Processing Block 3 Oversampling Index of Min", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4MAX", description: "ADC PPB 4 Final Max Result Register", offset: "0x50",
		bits: [
			{ name: "MAX", description: "Post Processing Block 4 Oversampling Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB4MAXI", description: "ADC PPB 4 Final Max Index Result Register", offset: "0x52",
		bits: [
			{ name: "MAXI", description: "Post Processing Block 4 Oversampling Index of Max", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4MIN", description: "ADC PPB 4 Final Min Result Register", offset: "0x54",
		bits: [
			{ name: "MIN", description: "Post Processing Block 4 Oversampling Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB4MINI", description: "ADC PPB 4 Final Min Index Result Register", offset: "0x56",
		bits: [
			{ name: "MINI", description: "Post Processing Block 4 Oversampling Index of Min", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
];
module.exports = {
	ADCRegisters: ADCRegisters,
}
