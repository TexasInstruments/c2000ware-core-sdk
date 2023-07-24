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
			{ name: "RESOLUTION", description: "SOC Conversion Resolution", size: "1", shift: "6", mask: "0x40" },
			{ name: "SIGNALMODE", description: "SOC Signaling Mode", size: "1", shift: "7", mask: "0x80" },
			{ name: "OFFTRIMMODE", description: "Offset Trim Mode", size: "1", shift: "8", mask: "0x100" },
		]
	},
	{ name: "BURSTCTL", description: "ADC Burst Control Register", offset: "0x2",
		bits: [
			{ name: "BURSTTRIGSEL", description: "SOC Burst Trigger Source Select", size: "7", shift: "0", mask: "0x7F" },
			{ name: "BURSTSIZE", description: "SOC Burst Size Select", size: "4", shift: "8", mask: "0xF00" },
			{ name: "BURSTEN", description: "SOC Burst Mode Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "INTFLG", description: "ADC Interrupt Flag Register", offset: "0x3",
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
	{ name: "INTFLGCLR", description: "ADC Interrupt Flag Clear Register", offset: "0x4",
		bits: [
			{ name: "ADCINT1", description: "ADC Interrupt 1 Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2", description: "ADC Interrupt 2 Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCINT3", description: "ADC Interrupt 3 Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADCINT4", description: "ADC Interrupt 4 Flag Clear", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "INTOVF", description: "ADC Interrupt Overflow Register", offset: "0x5",
		bits: [
			{ name: "ADCINT1", description: "ADC Interrupt 1 Overflow Flags", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2", description: "ADC Interrupt 2 Overflow Flags", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCINT3", description: "ADC Interrupt 3 Overflow Flags", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADCINT4", description: "ADC Interrupt 4 Overflow Flags", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "INTOVFCLR", description: "ADC Interrupt Overflow Clear Register", offset: "0x6",
		bits: [
			{ name: "ADCINT1", description: "ADC Interrupt 1 Overflow Clear Bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2", description: "ADC Interrupt 2 Overflow Clear Bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCINT3", description: "ADC Interrupt 3 Overflow Clear Bits", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADCINT4", description: "ADC Interrupt 4 Overflow Clear Bits", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "INTSEL1N2", description: "ADC Interrupt 1 and 2 Selection Register", offset: "0x7",
		bits: [
			{ name: "INT1SEL", description: "ADCINT1 EOC Source Select", size: "5", shift: "0", mask: "0x1F" },
			{ name: "INT1E", description: "ADCINT1 Interrupt Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT1CONT", description: "ADCINT1 Continue to Interrupt Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT2SEL", description: "ADCINT2 EOC Source Select", size: "5", shift: "8", mask: "0x1F00" },
			{ name: "INT2E", description: "ADCINT2 Interrupt Enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "INT2CONT", description: "ADCINT2 Continue to Interrupt Mode", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "INTSEL3N4", description: "ADC Interrupt 3 and 4 Selection Register", offset: "0x8",
		bits: [
			{ name: "INT3SEL", description: "ADCINT3 EOC Source Select", size: "5", shift: "0", mask: "0x1F" },
			{ name: "INT3E", description: "ADCINT3 Interrupt Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT3CONT", description: "ADCINT3 Continue to Interrupt Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT4SEL", description: "ADCINT4 EOC Source Select", size: "5", shift: "8", mask: "0x1F00" },
			{ name: "INT4E", description: "ADCINT4 Interrupt Enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "INT4CONT", description: "ADCINT4 Continue to Interrupt Mode", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "SOCPRICTL", description: "ADC SOC Priority Control Register", offset: "0x9",
		bits: [
			{ name: "SOCPRIORITY", description: "SOC Priority", size: "5", shift: "0", mask: "0x1F" },
			{ name: "RRPOINTER", description: "Round Robin Pointer", size: "5", shift: "5", mask: "0x3E0" },
		]
	},
	{ name: "INTSOCSEL1", description: "ADC Interrupt SOC Selection 1 Register", offset: "0xA",
		bits: [
			{ name: "SOC0", description: "SOC0 ADC Interrupt Trigger Select", size: "2", shift: "0", mask: "0x3" },
			{ name: "SOC1", description: "SOC1 ADC Interrupt Trigger Select", size: "2", shift: "2", mask: "0xC" },
			{ name: "SOC2", description: "SOC2 ADC Interrupt Trigger Select", size: "2", shift: "4", mask: "0x30" },
			{ name: "SOC3", description: "SOC3 ADC Interrupt Trigger Select", size: "2", shift: "6", mask: "0xC0" },
			{ name: "SOC4", description: "SOC4 ADC Interrupt Trigger Select", size: "2", shift: "8", mask: "0x300" },
			{ name: "SOC5", description: "SOC5 ADC Interrupt Trigger Select", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SOC6", description: "SOC6 ADC Interrupt Trigger Select", size: "2", shift: "12", mask: "0x3000" },
			{ name: "SOC7", description: "SOC7 ADC Interrupt Trigger Select", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "INTSOCSEL2", description: "ADC Interrupt SOC Selection 2 Register", offset: "0xB",
		bits: [
			{ name: "SOC8", description: "SOC8 ADC Interrupt Trigger Select", size: "2", shift: "0", mask: "0x3" },
			{ name: "SOC9", description: "SOC9 ADC Interrupt Trigger Select", size: "2", shift: "2", mask: "0xC" },
			{ name: "SOC10", description: "SOC10 ADC Interrupt Trigger Select", size: "2", shift: "4", mask: "0x30" },
			{ name: "SOC11", description: "SOC11 ADC Interrupt Trigger Select", size: "2", shift: "6", mask: "0xC0" },
			{ name: "SOC12", description: "SOC12 ADC Interrupt Trigger Select", size: "2", shift: "8", mask: "0x300" },
			{ name: "SOC13", description: "SOC13 ADC Interrupt Trigger Select", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SOC14", description: "SOC14 ADC Interrupt Trigger Select", size: "2", shift: "12", mask: "0x3000" },
			{ name: "SOC15", description: "SOC15 ADC Interrupt Trigger Select", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "SOCFLG1", description: "ADC SOC Flag 1 Register", offset: "0xC",
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
	{ name: "SOCFRC1", description: "ADC SOC Force 1 Register", offset: "0xD",
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
	{ name: "SOCOVF1", description: "ADC SOC Overflow 1 Register", offset: "0xE",
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
	{ name: "SOCOVFCLR1", description: "ADC SOC Overflow Clear 1 Register", offset: "0xF",
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
	{ name: "SOC0CTL", description: "ADC SOC0 Control Register", offset: "0x10",
		bits: [
			{ name: "ACQPS", description: "SOC0 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC0 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC0 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC0 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC1CTL", description: "ADC SOC1 Control Register", offset: "0x12",
		bits: [
			{ name: "ACQPS", description: "SOC1 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC1 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC1 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC1 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC2CTL", description: "ADC SOC2 Control Register", offset: "0x14",
		bits: [
			{ name: "ACQPS", description: "SOC2 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC2 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC2 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC2 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC3CTL", description: "ADC SOC3 Control Register", offset: "0x16",
		bits: [
			{ name: "ACQPS", description: "SOC3 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC3 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC3 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC3 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC4CTL", description: "ADC SOC4 Control Register", offset: "0x18",
		bits: [
			{ name: "ACQPS", description: "SOC4 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC4 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC4 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC4 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC5CTL", description: "ADC SOC5 Control Register", offset: "0x1A",
		bits: [
			{ name: "ACQPS", description: "SOC5 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC5 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC5 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC5 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC6CTL", description: "ADC SOC6 Control Register", offset: "0x1C",
		bits: [
			{ name: "ACQPS", description: "SOC6 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC6 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC6 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC6 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC7CTL", description: "ADC SOC7 Control Register", offset: "0x1E",
		bits: [
			{ name: "ACQPS", description: "SOC7 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC7 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC7 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC7 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC8CTL", description: "ADC SOC8 Control Register", offset: "0x20",
		bits: [
			{ name: "ACQPS", description: "SOC8 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC8 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC8 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC8 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC9CTL", description: "ADC SOC9 Control Register", offset: "0x22",
		bits: [
			{ name: "ACQPS", description: "SOC9 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC9 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC9 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC9 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC10CTL", description: "ADC SOC10 Control Register", offset: "0x24",
		bits: [
			{ name: "ACQPS", description: "SOC10 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC10 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC10 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC10 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC11CTL", description: "ADC SOC11 Control Register", offset: "0x26",
		bits: [
			{ name: "ACQPS", description: "SOC11 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC11 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC11 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC11 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC12CTL", description: "ADC SOC12 Control Register", offset: "0x28",
		bits: [
			{ name: "ACQPS", description: "SOC12 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC12 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC12 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC12 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC13CTL", description: "ADC SOC13 Control Register", offset: "0x2A",
		bits: [
			{ name: "ACQPS", description: "SOC13 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC13 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC13 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC13 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC14CTL", description: "ADC SOC14 Control Register", offset: "0x2C",
		bits: [
			{ name: "ACQPS", description: "SOC14 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC14 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC14 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC14 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "SOC15CTL", description: "ADC SOC15 Control Register", offset: "0x2E",
		bits: [
			{ name: "ACQPS", description: "SOC15 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC15 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC15 Trigger Source Select", size: "7", shift: "20", mask: "0x7F00000" },
			{ name: "EXTCHSEL", description: "SOC15 External Channel Mux Select", size: "4", shift: "28", mask: "0xF0000000" },
		]
	},
	{ name: "EVTSTAT", description: "ADC Event Status Register", offset: "0x30",
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
	{ name: "EVTCLR", description: "ADC Event Clear Register", offset: "0x32",
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
	{ name: "EVTSEL", description: "ADC Event Selection Register", offset: "0x34",
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
	{ name: "EVTINTSEL", description: "ADC Event Interrupt Selection Register", offset: "0x36",
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
	{ name: "OSDETECT", description: "ADC Open and Shorts Detect Register", offset: "0x38",
		bits: [
			{ name: "DETECTCFG", description: "ADC Opens and Shorts Detect Configuration", size: "3", shift: "0", mask: "0x7" },
		]
	},
	{ name: "COUNTER", description: "ADC Counter Register", offset: "0x39",
		bits: [
			{ name: "FREECOUNT", description: "ADC Free Running Counter Value", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "REV", description: "ADC Revision Register", offset: "0x3A",
		bits: [
			{ name: "TYPE", description: "ADC Type", size: "8", shift: "0", mask: "0xFF" },
			{ name: "REV", description: "ADC Revision", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "OFFTRIM", description: "ADC Offset Trim Register", offset: "0x3B",
		bits: [
			{ name: "OFFTRIM", description: "ADC Offset Trim 12B SE Even", size: "8", shift: "0", mask: "0xFF" },
			{ name: "OFFTRIM12BSEODD", description: "ADC Offset Trim 12B SE Odd", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "OFFTRIM2", description: "ADC Offset Trim Register", offset: "0x3C",
		bits: [
			{ name: "OFFTRIM16BSEEVEN", description: "ADC Offset Trim 16B SE Even", size: "8", shift: "0", mask: "0xFF" },
			{ name: "OFFTRIM16BSEODD", description: "ADC Offset Trim 16B SE Odd", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "OFFTRIM3", description: "ADC Offset Trim Register", offset: "0x3D",
		bits: [
			{ name: "OFFTRIM12BDE", description: "ADC Offset Trim 12B DE", size: "8", shift: "0", mask: "0xFF" },
			{ name: "OFFTRIM16BDE", description: "ADC Offset Trim 16B DE", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "PPB1CONFIG", description: "ADC PPB1 Config Register", offset: "0x40",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 1 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 1 Two's Complement Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "ABSEN", description: "ADC Post Processing Block 1 Absolute Enable", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "PPB1STAMP", description: "ADC PPB1 Sample Delay Time Stamp Register", offset: "0x41",
		bits: [
			{ name: "DLYSTAMP", description: "ADC Post Processing Block 1 Delay Time Stamp", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB1OFFCAL", description: "ADC PPB1 Offset Calibration Register", offset: "0x42",
		bits: [
			{ name: "OFFCAL", description: "ADC Post Processing Block Offset Correction", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1OFFREF", description: "ADC PPB1 Offset Reference Register", offset: "0x43",
		bits: [
		]
	},
	{ name: "PPB1TRIPHI", description: "ADC PPB1 Trip High Register", offset: "0x44",
		bits: [
			{ name: "LIMITHI", description: "ADC Post Processing Block 1 Trip High Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB1TRIPLO", description: "ADC PPB1 Trip Low/Trigger Time Stamp Register", offset: "0x46",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 1 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "LIMITLO2EN", description: "Extended Low Limit 2 Enable", size: "1", shift: "19", mask: "0x80000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 1 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
		]
	},
	{ name: "PPB2CONFIG", description: "ADC PPB2 Config Register", offset: "0x48",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 2 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 2 Two's Complement Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "ABSEN", description: "ADC Post Processing Block 2 Absolute Enable", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "PPB2STAMP", description: "ADC PPB2 Sample Delay Time Stamp Register", offset: "0x49",
		bits: [
			{ name: "DLYSTAMP", description: "ADC Post Processing Block 2 Delay Time Stamp", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB2OFFCAL", description: "ADC PPB2 Offset Calibration Register", offset: "0x4A",
		bits: [
			{ name: "OFFCAL", description: "ADC Post Processing Block Offset Correction", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2OFFREF", description: "ADC PPB2 Offset Reference Register", offset: "0x4B",
		bits: [
		]
	},
	{ name: "PPB2TRIPHI", description: "ADC PPB2 Trip High Register", offset: "0x4C",
		bits: [
			{ name: "LIMITHI", description: "ADC Post Processing Block 2 Trip High Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB2TRIPLO", description: "ADC PPB2 Trip Low/Trigger Time Stamp Register", offset: "0x4E",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 2 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "LIMITLO2EN", description: "Extended Low Limit 2 Enable", size: "1", shift: "19", mask: "0x80000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 2 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
		]
	},
	{ name: "PPB3CONFIG", description: "ADC PPB3 Config Register", offset: "0x50",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 3 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 3 Two's Complement Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "ABSEN", description: "ADC Post Processing Block 3 Absolute Enable", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "PPB3STAMP", description: "ADC PPB3 Sample Delay Time Stamp Register", offset: "0x51",
		bits: [
			{ name: "DLYSTAMP", description: "ADC Post Processing Block 3 Delay Time Stamp", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB3OFFCAL", description: "ADC PPB3 Offset Calibration Register", offset: "0x52",
		bits: [
			{ name: "OFFCAL", description: "ADC Post Processing Block Offset Correction", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3OFFREF", description: "ADC PPB3 Offset Reference Register", offset: "0x53",
		bits: [
		]
	},
	{ name: "PPB3TRIPHI", description: "ADC PPB3 Trip High Register", offset: "0x54",
		bits: [
			{ name: "LIMITHI", description: "ADC Post Processing Block 3 Trip High Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB3TRIPLO", description: "ADC PPB3 Trip Low/Trigger Time Stamp Register", offset: "0x56",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 3 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "LIMITLO2EN", description: "Extended Low Limit 2 Enable", size: "1", shift: "19", mask: "0x80000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 3 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
		]
	},
	{ name: "PPB4CONFIG", description: "ADC PPB4 Config Register", offset: "0x58",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 4 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 4 Two's Complement Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "ABSEN", description: "ADC Post Processing Block 4 Absolute Enable", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "PPB4STAMP", description: "ADC PPB4 Sample Delay Time Stamp Register", offset: "0x59",
		bits: [
			{ name: "DLYSTAMP", description: "ADC Post Processing Block 4 Delay Time Stamp", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB4OFFCAL", description: "ADC PPB4 Offset Calibration Register", offset: "0x5A",
		bits: [
			{ name: "OFFCAL", description: "ADC Post Processing Block Offset Correction", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4OFFREF", description: "ADC PPB4 Offset Reference Register", offset: "0x5B",
		bits: [
		]
	},
	{ name: "PPB4TRIPHI", description: "ADC PPB4 Trip High Register", offset: "0x5C",
		bits: [
			{ name: "LIMITHI", description: "ADC Post Processing Block 4 Trip High Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB4TRIPLO", description: "ADC PPB4 Trip Low/Trigger Time Stamp Register", offset: "0x5E",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 4 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "LIMITLO2EN", description: "Extended Low Limit 2 Enable", size: "1", shift: "19", mask: "0x80000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 4 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
		]
	},
	{ name: "SAFECHECKRESEN", description: "ADC Safe Check Result Enable Register", offset: "0x60",
		bits: [
			{ name: "SOC0CHKEN", description: "ADC SOC0 Safety Checker Result Enable", size: "2", shift: "0", mask: "0x3" },
			{ name: "SOC1CHKEN", description: "ADC SOC1 Safety Checker Result Enable", size: "2", shift: "2", mask: "0xC" },
			{ name: "SOC2CHKEN", description: "ADC SOC2 Safety Checker Result Enable", size: "2", shift: "4", mask: "0x30" },
			{ name: "SOC3CHKEN", description: "ADC SOC3 Safety Checker Result Enable", size: "2", shift: "6", mask: "0xC0" },
			{ name: "SOC4CHKEN", description: "ADC SOC4 Safety Checker Result Enable", size: "2", shift: "8", mask: "0x300" },
			{ name: "SOC5CHKEN", description: "ADC SOC5 Safety Checker Result Enable", size: "2", shift: "10", mask: "0xC00" },
			{ name: "SOC6CHKEN", description: "ADC SOC6 Safety Checker Result Enable", size: "2", shift: "12", mask: "0x3000" },
			{ name: "SOC7CHKEN", description: "ADC SOC7 Safety Checker Result Enable", size: "2", shift: "14", mask: "0xC000" },
			{ name: "SOC8CHKEN", description: "ADC SOC8 Safety Checker Result Enable", size: "2", shift: "16", mask: "0x30000" },
			{ name: "SOC9CHKEN", description: "ADC SOC9 Safety Checker Result Enable", size: "2", shift: "18", mask: "0xC0000" },
			{ name: "SOC10CHKEN", description: "ADC SOC10 Safety Checker Result Enable", size: "2", shift: "20", mask: "0x300000" },
			{ name: "SOC11CHKEN", description: "ADC SOC11 Safety Checker Result Enable", size: "2", shift: "22", mask: "0xC00000" },
			{ name: "SOC12CHKEN", description: "ADC SOC12 Safety Checker Result Enable", size: "2", shift: "24", mask: "0x3000000" },
			{ name: "SOC13CHKEN", description: "ADC SOC13 Safety Checker Result Enable", size: "2", shift: "26", mask: "0xC000000" },
			{ name: "SOC14CHKEN", description: "ADC SOC14 Safety Checker Result Enable", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "SOC15CHKEN", description: "ADC SOC15 Safety Checker Result Enable", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "INTCYCLE", description: "ADC Early Interrupt Generation Cycle", offset: "0x6F",
		bits: [
		]
	},
	{ name: "INLTRIM1", description: "ADC Linearity Trim 1 Register", offset: "0x70",
		bits: [
		]
	},
	{ name: "INLTRIM2", description: "ADC Linearity Trim 2 Register", offset: "0x72",
		bits: [
		]
	},
	{ name: "INLTRIM3", description: "ADC Linearity Trim 3 Register", offset: "0x74",
		bits: [
		]
	},
	{ name: "INLTRIM4", description: "ADC Linearity Trim 4 Register", offset: "0x76",
		bits: [
		]
	},
	{ name: "INLTRIM5", description: "ADC Linearity Trim 5 Register", offset: "0x78",
		bits: [
		]
	},
	{ name: "INLTRIM6", description: "ADC Linearity Trim 6 Register", offset: "0x7A",
		bits: [
		]
	},
	{ name: "REV2", description: "ADC Wrapper Revision Register", offset: "0x7D",
		bits: [
			{ name: "WRAPPERTYPE", description: "ADC Wrapper Type", size: "8", shift: "0", mask: "0xFF" },
			{ name: "WRAPPERREV", description: "ADC Wrapper Revision", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "REP1CTL", description: "ADC Trigger Repeater 1 Control Register", offset: "0x80",
		bits: [
			{ name: "MODE", description: "ADC Trigger Repeater 1 Mode Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "ACTIVEMODE", description: "ADC Trigger Repeater 1 Active Mode", size: "1", shift: "1", mask: "0x2" },
			{ name: "MODULEBUSY", description: "ADC Trigger Repeater 1 Module Busy", size: "1", shift: "3", mask: "0x8" },
			{ name: "PHASEOVF", description: "ADC Trigger Repeater 1 Phase Delay Overflow", size: "1", shift: "6", mask: "0x40" },
			{ name: "TRIGGEROVF", description: "ADC Trigger Repeater 1 Oversampled Trigger", size: "1", shift: "7", mask: "0x80" },
			{ name: "TRIGGER", description: "ADC Trigger Repeater 1 Trigger Select", size: "7", shift: "8", mask: "0x7F00" },
			{ name: "SYNCINSEL", description: "ADC Trigger Repeater 1 Sync. In Select", size: "5", shift: "16", mask: "0x1F0000" },
			{ name: "SWSYNC", description: "ADC Trigger Repeater 1 Software Sync.", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "REP1N", description: "ADC Trigger Repeater 1 N Select Register", offset: "0x82",
		bits: [
			{ name: "NSEL", description: "ADC Trigger Repeater 1 Trigger Number Selection", size: "7", shift: "0", mask: "0x7F" },
			{ name: "NCOUNT", description: "ADC Trigger Repeater 1 Trigger Counter", size: "7", shift: "16", mask: "0x7F0000" },
		]
	},
	{ name: "REP1PHASE", description: "ADC Trigger Repeater 1 Phase Select Register", offset: "0x84",
		bits: [
			{ name: "PHASE", description: "ADC Trigger Repeater 1 Phase Delay", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "PHASECOUNT", description: "ADC Trigger Repeater 1 Phase Delay Status", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "REP1SPREAD", description: "ADC Trigger Repeater 1 Spread Select Register", offset: "0x86",
		bits: [
			{ name: "SPREAD", description: "ADC Trigger Repeater 1 Spread Delay", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SPREADCOUNT", description: "ADC Trigger Repeater 1 Spread Delay Status", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "REP1FRC", description: "ADC Trigger Repeater 1 Software Force Register", offset: "0x88",
		bits: [
			{ name: "SWFRC", description: "ADC Trigger Repeater 1 Software Force", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "REP2CTL", description: "ADC Trigger Repeater 2 Control Register", offset: "0x90",
		bits: [
			{ name: "MODE", description: "ADC Trigger Repeater 2 Mode Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "ACTIVEMODE", description: "ADC Trigger Repeater 2 Active Mode", size: "1", shift: "1", mask: "0x2" },
			{ name: "MODULEBUSY", description: "ADC Trigger Repeater 2 Module Busy", size: "1", shift: "3", mask: "0x8" },
			{ name: "PHASEOVF", description: "ADC Trigger Repeater 2 Phase Delay Overflow", size: "1", shift: "6", mask: "0x40" },
			{ name: "TRIGGEROVF", description: "ADC Trigger Repeater 2 Oversampled Trigger", size: "1", shift: "7", mask: "0x80" },
			{ name: "TRIGGER", description: "ADC Trigger Repeater 2 Trigger Select", size: "7", shift: "8", mask: "0x7F00" },
			{ name: "SYNCINSEL", description: "ADC Trigger Repeater 2 Sync. In Select", size: "5", shift: "16", mask: "0x1F0000" },
			{ name: "SWSYNC", description: "ADC Trigger Repeater 2 Software Sync.", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "REP2N", description: "ADC Trigger Repeater 2 N Select Register", offset: "0x92",
		bits: [
			{ name: "NSEL", description: "ADC Trigger Repeater 2 Trigger Number Selection", size: "7", shift: "0", mask: "0x7F" },
			{ name: "NCOUNT", description: "ADC Trigger Repeater 2 Trigger Counter", size: "7", shift: "16", mask: "0x7F0000" },
		]
	},
	{ name: "REP2PHASE", description: "ADC Trigger Repeater 2 Phase Select Register", offset: "0x94",
		bits: [
			{ name: "PHASE", description: "ADC Trigger Repeater 2 Phase Delay", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "PHASECOUNT", description: "ADC Trigger Repeater 2 Phase Delay Status", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "REP2SPREAD", description: "ADC Trigger Repeater 2 Spread Select Register", offset: "0x96",
		bits: [
			{ name: "SPREAD", description: "ADC Trigger Repeater 2 Spread Delay", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SPREADCOUNT", description: "ADC Trigger Repeater 2 Spread Delay Status", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "REP2FRC", description: "ADC Trigger Repeater 2 Software Force Register", offset: "0x98",
		bits: [
			{ name: "SWFRC", description: "ADC Trigger Repeater 2 Software Force", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PPB1LIMIT", description: "ADC PPB1Conversion Count Limit Register", offset: "0xA0",
		bits: [
			{ name: "LIMIT", description: "Post Processing Block 1 Limit", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPBP1PCOUNT", description: "ADC PPB1 Partial Conversion Count Register", offset: "0xA2",
		bits: [
			{ name: "PCOUNT", description: "Post Processing Block 1 Partial Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1CONFIG2", description: "ADC PPB1 Sum Shift Register", offset: "0xA4",
		bits: [
			{ name: "SHIFT", description: "Post Processing Block 1 Right Shift", size: "4", shift: "0", mask: "0xF" },
			{ name: "SYNCINSEL", description: "Post Processing Block 1 Sync. Input Select", size: "5", shift: "4", mask: "0x1F0" },
			{ name: "SWSYNC", description: "Post Processing Block 1 Software Force Sync.", size: "1", shift: "11", mask: "0x800" },
			{ name: "OSINTSEL", description: "Post Processing Block 1 Interrupt Source Select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "COMPSEL", description: "Post Processing Block 1 Compare Source Select", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "PPB1PSUM", description: "ADC PPB1 Partial Sum Register", offset: "0xA6",
		bits: [
			{ name: "PSUM", description: "Post Processing Block 1 Oversampling Partial Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB1PMAX", description: "ADC PPB1 Partial Max Register", offset: "0xA8",
		bits: [
			{ name: "PMAX", description: "Post Processing Block 1 Oversampling Partial Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB1PMAXI", description: "ADC PPB1 Partial Max Index Register", offset: "0xAA",
		bits: [
			{ name: "PMAXI", description: "Post Processing Block 1 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1PMIN", description: "ADC PPB1 Partial MIN Register", offset: "0xAC",
		bits: [
			{ name: "PMIN", description: "Post Processing Block 1 Oversampling Partial Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB1PMINI", description: "ADC PPB1 Partial Min Index Register", offset: "0xAE",
		bits: [
			{ name: "PMINI", description: "Post Processing Block 1 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1TRIPLO2", description: "ADC PPB1 Extended Trip Low Register", offset: "0xB0",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 1 Trip Low Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB2LIMIT", description: "ADC PPB2Conversion Count Limit Register", offset: "0xBA",
		bits: [
			{ name: "LIMIT", description: "Post Processing Block 2 Limit", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPBP2PCOUNT", description: "ADC PPB2 Partial Conversion Count Register", offset: "0xBC",
		bits: [
			{ name: "PCOUNT", description: "Post Processing Block 2 Partial Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2CONFIG2", description: "ADC PPB2 Sum Shift Register", offset: "0xBE",
		bits: [
			{ name: "SHIFT", description: "Post Processing Block 2 Right Shift", size: "4", shift: "0", mask: "0xF" },
			{ name: "SYNCINSEL", description: "Post Processing Block 2 Sync. Input Select", size: "5", shift: "4", mask: "0x1F0" },
			{ name: "SWSYNC", description: "Post Processing Block 2 Software Force Sync.", size: "1", shift: "11", mask: "0x800" },
			{ name: "OSINTSEL", description: "Post Processing Block 2 Interrupt Source Select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "COMPSEL", description: "Post Processing Block 2 Compare Source Select", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "PPB2PSUM", description: "ADC PPB2 Partial Sum Register", offset: "0xC0",
		bits: [
			{ name: "PSUM", description: "Post Processing Block 2 Oversampling Partial Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB2PMAX", description: "ADC PPB2 Partial Max Register", offset: "0xC2",
		bits: [
			{ name: "PMAX", description: "Post Processing Block 2 Oversampling Partial Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB2PMAXI", description: "ADC PPB2 Partial Max Index Register", offset: "0xC4",
		bits: [
			{ name: "PMAXI", description: "Post Processing Block 2 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2PMIN", description: "ADC PPB2 Partial MIN Register", offset: "0xC6",
		bits: [
			{ name: "PMIN", description: "Post Processing Block 2 Oversampling Partial Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB2PMINI", description: "ADC PPB2 Partial Min Index Register", offset: "0xC8",
		bits: [
			{ name: "PMINI", description: "Post Processing Block 2 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2TRIPLO2", description: "ADC PPB2 Extended Trip Low Register", offset: "0xCA",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 2 Trip Low Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB3LIMIT", description: "ADC PPB3Conversion Count Limit Register", offset: "0xD4",
		bits: [
			{ name: "LIMIT", description: "Post Processing Block 3 Limit", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPBP3PCOUNT", description: "ADC PPB3 Partial Conversion Count Register", offset: "0xD6",
		bits: [
			{ name: "PCOUNT", description: "Post Processing Block 3 Partial Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3CONFIG2", description: "ADC PPB3 Sum Shift Register", offset: "0xD8",
		bits: [
			{ name: "SHIFT", description: "Post Processing Block 3 Right Shift", size: "4", shift: "0", mask: "0xF" },
			{ name: "SYNCINSEL", description: "Post Processing Block 3 Sync. Input Select", size: "5", shift: "4", mask: "0x1F0" },
			{ name: "SWSYNC", description: "Post Processing Block 3 Software Force Sync.", size: "1", shift: "11", mask: "0x800" },
			{ name: "OSINTSEL", description: "Post Processing Block 3 Interrupt Source Select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "COMPSEL", description: "Post Processing Block 3 Compare Source Select", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "PPB3PSUM", description: "ADC PPB3 Partial Sum Register", offset: "0xDA",
		bits: [
			{ name: "PSUM", description: "Post Processing Block 3 Oversampling Partial Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB3PMAX", description: "ADC PPB3 Partial Max Register", offset: "0xDC",
		bits: [
			{ name: "PMAX", description: "Post Processing Block 3 Oversampling Partial Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB3PMAXI", description: "ADC PPB3 Partial Max Index Register", offset: "0xDE",
		bits: [
			{ name: "PMAXI", description: "Post Processing Block 3 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3PMIN", description: "ADC PPB3 Partial MIN Register", offset: "0xE0",
		bits: [
			{ name: "PMIN", description: "Post Processing Block 3 Oversampling Partial Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB3PMINI", description: "ADC PPB3 Partial Min Index Register", offset: "0xE2",
		bits: [
			{ name: "PMINI", description: "Post Processing Block 3 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3TRIPLO2", description: "ADC PPB3 Extended Trip Low Register", offset: "0xE4",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 3 Trip Low Limit", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PPB4LIMIT", description: "ADC PPB4Conversion Count Limit Register", offset: "0xEE",
		bits: [
			{ name: "LIMIT", description: "Post Processing Block 4 Limit", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPBP4PCOUNT", description: "ADC PPB4 Partial Conversion Count Register", offset: "0xF0",
		bits: [
			{ name: "PCOUNT", description: "Post Processing Block 4 Partial Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4CONFIG2", description: "ADC PPB4 Sum Shift Register", offset: "0xF2",
		bits: [
			{ name: "SHIFT", description: "Post Processing Block 4 Right Shift", size: "4", shift: "0", mask: "0xF" },
			{ name: "SYNCINSEL", description: "Post Processing Block 4 Sync. Input Select", size: "5", shift: "4", mask: "0x1F0" },
			{ name: "SWSYNC", description: "Post Processing Block 4 Software Force Sync.", size: "1", shift: "11", mask: "0x800" },
			{ name: "OSINTSEL", description: "Post Processing Block 4 Interrupt Source Select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "COMPSEL", description: "Post Processing Block 4 Compare Source Select", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "PPB4PSUM", description: "ADC PPB4 Partial Sum Register", offset: "0xF4",
		bits: [
			{ name: "PSUM", description: "Post Processing Block 4 Oversampling Partial Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB4PMAX", description: "ADC PPB4 Partial Max Register", offset: "0xF6",
		bits: [
			{ name: "PMAX", description: "Post Processing Block 4 Oversampling Partial Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB4PMAXI", description: "ADC PPB4 Partial Max Index Register", offset: "0xF8",
		bits: [
			{ name: "PMAXI", description: "Post Processing Block 4 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4PMIN", description: "ADC PPB4 Partial MIN Register", offset: "0xFA",
		bits: [
			{ name: "PMIN", description: "Post Processing Block 4 Oversampling Partial Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB4PMINI", description: "ADC PPB4 Partial Min Index Register", offset: "0xFC",
		bits: [
			{ name: "PMINI", description: "Post Processing Block 4 Oversampling Partial Index of", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4TRIPLO2", description: "ADC PPB4 Extended Trip Low Register", offset: "0xFE",
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
	{ name: "PPB1RESULT", description: "ADC Post Processing Block 1 Result Register", offset: "0x10",
		bits: [
			{ name: "PPBRESULT", description: "ADC Post Processing Block Result", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "PPB2RESULT", description: "ADC Post Processing Block 2 Result Register", offset: "0x12",
		bits: [
			{ name: "PPBRESULT", description: "ADC Post Processing Block Result", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "PPB3RESULT", description: "ADC Post Processing Block 3 Result Register", offset: "0x14",
		bits: [
			{ name: "PPBRESULT", description: "ADC Post Processing Block Result", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "PPB4RESULT", description: "ADC Post Processing Block 4 Result Register", offset: "0x16",
		bits: [
			{ name: "PPBRESULT", description: "ADC Post Processing Block Result", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "PPB1SUM", description: "ADC PPB 1 Final Sum Result Register", offset: "0x18",
		bits: [
			{ name: "SUM", description: "Post Processing Block 1 Oversampling Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB1COUNT", description: "ADC PPB1 Final Conversion Count Register", offset: "0x1A",
		bits: [
			{ name: "COUNT", description: "Post Processing Block 1 Final Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2SUM", description: "ADC PPB 2 Final Sum Result Register", offset: "0x1C",
		bits: [
			{ name: "SUM", description: "Post Processing Block 2 Oversampling Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB2COUNT", description: "ADC PPB2 Final Conversion Count Register", offset: "0x1E",
		bits: [
			{ name: "COUNT", description: "Post Processing Block 2 Final Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3SUM", description: "ADC PPB 3 Final Sum Result Register", offset: "0x20",
		bits: [
			{ name: "SUM", description: "Post Processing Block 3 Oversampling Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB3COUNT", description: "ADC PPB3 Final Conversion Count Register", offset: "0x22",
		bits: [
			{ name: "COUNT", description: "Post Processing Block 3 Final Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4SUM", description: "ADC PPB 4 Final Sum Result Register", offset: "0x24",
		bits: [
			{ name: "SUM", description: "Post Processing Block 4 Oversampling Sum", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "8", shift: "24", mask: "0xFF000000" },
		]
	},
	{ name: "PPB4COUNT", description: "ADC PPB4 Final Conversion Count Register", offset: "0x26",
		bits: [
			{ name: "COUNT", description: "Post Processing Block 4 Final Count", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1MAX", description: "ADC PPB 1 Final Max Result Register", offset: "0x28",
		bits: [
			{ name: "MAX", description: "Post Processing Block 1 Oversampling Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB1MAXI", description: "ADC PPB 1 Final Max Index Result Register", offset: "0x2A",
		bits: [
			{ name: "MAXI", description: "Post Processing Block 1 Oversampling Index of Max", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB1MIN", description: "ADC PPB 1 Final Min Result Register", offset: "0x2C",
		bits: [
			{ name: "MIN", description: "Post Processing Block 1 Oversampling Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB1MINI", description: "ADC PPB 1 Final Min Index Result Register", offset: "0x2E",
		bits: [
			{ name: "MINI", description: "Post Processing Block 1 Oversampling Index of Min", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2MAX", description: "ADC PPB 2 Final Max Result Register", offset: "0x30",
		bits: [
			{ name: "MAX", description: "Post Processing Block 2 Oversampling Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB2MAXI", description: "ADC PPB 2 Final Max Index Result Register", offset: "0x32",
		bits: [
			{ name: "MAXI", description: "Post Processing Block 2 Oversampling Index of Max", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB2MIN", description: "ADC PPB 2 Final Min Result Register", offset: "0x34",
		bits: [
			{ name: "MIN", description: "Post Processing Block 2 Oversampling Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB2MINI", description: "ADC PPB 2 Final Min Index Result Register", offset: "0x36",
		bits: [
			{ name: "MINI", description: "Post Processing Block 2 Oversampling Index of Min", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3MAX", description: "ADC PPB 3 Final Max Result Register", offset: "0x38",
		bits: [
			{ name: "MAX", description: "Post Processing Block 3 Oversampling Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB3MAXI", description: "ADC PPB 3 Final Max Index Result Register", offset: "0x3A",
		bits: [
			{ name: "MAXI", description: "Post Processing Block 3 Oversampling Index of Max", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB3MIN", description: "ADC PPB 3 Final Min Result Register", offset: "0x3C",
		bits: [
			{ name: "MIN", description: "Post Processing Block 3 Oversampling Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB3MINI", description: "ADC PPB 3 Final Min Index Result Register", offset: "0x3E",
		bits: [
			{ name: "MINI", description: "Post Processing Block 3 Oversampling Index of Min", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4MAX", description: "ADC PPB 4 Final Max Result Register", offset: "0x40",
		bits: [
			{ name: "MAX", description: "Post Processing Block 4 Oversampling Max", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB4MAXI", description: "ADC PPB 4 Final Max Index Result Register", offset: "0x42",
		bits: [
			{ name: "MAXI", description: "Post Processing Block 4 Oversampling Index of Max", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PPB4MIN", description: "ADC PPB 4 Final Min Result Register", offset: "0x44",
		bits: [
			{ name: "MIN", description: "Post Processing Block 4 Oversampling Min", size: "17", shift: "0", mask: "0x1FFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "15", shift: "17", mask: "0xFFFE0000" },
		]
	},
	{ name: "PPB4MINI", description: "ADC PPB 4 Final Min Index Result Register", offset: "0x46",
		bits: [
			{ name: "MINI", description: "Post Processing Block 4 Oversampling Index of Min", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "CHECKCONFIG", description: "ADC Check Configuration Register", offset: "0x0",
		bits: [
			{ name: "SWSYNC", description: "Result Safe Check SW Force Sync.", size: "1", shift: "6", mask: "0x40" },
			{ name: "CHKEN", description: "Result Safe Check Module Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKSTATUS", description: "ADC Check Status Register", offset: "0x2",
		bits: [
			{ name: "RES1READY", description: "Result Safe Check Result 1 Arrived", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES2READY", description: "Result Safe Check Result 2 Arrived", size: "1", shift: "1", mask: "0x2" },
			{ name: "OOT", description: "Safe Check OOT Flag", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "RESSEL1", description: "ADC Check 1 Select Register", offset: "0x4",
		bits: [
			{ name: "ADCSEL", description: "Result Safe Check ADC Select 1", size: "3", shift: "0", mask: "0x7" },
			{ name: "ADCRESULTSEL", description: "Result Safe Check Result Select 1", size: "6", shift: "4", mask: "0x3F0" },
		]
	},
	{ name: "RESSEL2", description: "ADC Check 2 Select Register", offset: "0x6",
		bits: [
			{ name: "ADCSEL", description: "Result Safe Check ADC Select 2", size: "3", shift: "0", mask: "0x7" },
			{ name: "ADCRESULTSEL", description: "Result Safe Check Result Select 2", size: "6", shift: "4", mask: "0x3F0" },
		]
	},
	{ name: "TOLERANCE", description: "ADC Check Tolerance Register", offset: "0x8",
		bits: [
			{ name: "TOLERANCE", description: "Result Safe Check Tolerance", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "CHECKRESULT1", description: "ADC Check Captured Result 1", offset: "0xC",
		bits: [
			{ name: "RESULT", description: "Result Safe Check Captured Result", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "CHECKRESULT2", description: "ADC Check Captured Result 2", offset: "0xE",
		bits: [
			{ name: "RESULT", description: "Result Safe Check Captured Result", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "OOTFLG", description: "Checker Out-of-Tolerance Flag Register", offset: "0x0",
		bits: [
			{ name: "OOT1", description: "Checker 1 Out-of-Tolerance Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "OOT2", description: "Checker 2 Out-of-Tolerance Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "OOT3", description: "Checker 3 Out-of-Tolerance Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "OOT4", description: "Checker 4 Out-of-Tolerance Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "OOT5", description: "Checker 5 Out-of-Tolerance Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "OOT6", description: "Checker 6 Out-of-Tolerance Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "OOT7", description: "Checker 7 Out-of-Tolerance Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "OOT8", description: "Checker 8 Out-of-Tolerance Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "OOT9", description: "Checker 9 Out-of-Tolerance Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "OOT10", description: "Checker 10 Out-of-Tolerance Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "OOT11", description: "Checker 11 Out-of-Tolerance Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "OOT12", description: "Checker 12 Out-of-Tolerance Flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "OOT13", description: "Checker 13 Out-of-Tolerance Flag", size: "1", shift: "12", mask: "0x1000" },
			{ name: "OOT14", description: "Checker 14 Out-of-Tolerance Flag", size: "1", shift: "13", mask: "0x2000" },
			{ name: "OOT15", description: "Checker 15 Out-of-Tolerance Flag", size: "1", shift: "14", mask: "0x4000" },
			{ name: "OOT16", description: "Checker 16 Out-of-Tolerance Flag", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "OOTFLGCLR", description: "Checker Out-of-Tolerance Flag Clear Register", offset: "0x2",
		bits: [
			{ name: "OOT1", description: "Checker 1 OOT Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "OOT2", description: "Checker 2 OOT Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "OOT3", description: "Checker 3 OOT Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "OOT4", description: "Checker 4 OOT Flag Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "OOT5", description: "Checker 5 OOT Flag Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "OOT6", description: "Checker 6 OOT Flag Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "OOT7", description: "Checker 7 OOT Flag Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "OOT8", description: "Checker 8 OOT Flag Clear", size: "1", shift: "7", mask: "0x80" },
			{ name: "OOT9", description: "Checker 9 OOT Flag Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "OOT10", description: "Checker 10 OOT Flag Clear", size: "1", shift: "9", mask: "0x200" },
			{ name: "OOT11", description: "Checker 11 OOT Flag Clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "OOT12", description: "Checker 12 OOT Flag Clear", size: "1", shift: "11", mask: "0x800" },
			{ name: "OOT13", description: "Checker 13 OOT Flag Clear", size: "1", shift: "12", mask: "0x1000" },
			{ name: "OOT14", description: "Checker 14 OOT Flag Clear", size: "1", shift: "13", mask: "0x2000" },
			{ name: "OOT15", description: "Checker 15 OOT Flag Clear", size: "1", shift: "14", mask: "0x4000" },
			{ name: "OOT16", description: "Checker 16 OOT Flag Clear", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "RES1OVF", description: "Checker Overflow Result 1 Flag Register", offset: "0x4",
		bits: [
			{ name: "RES1OVF1", description: "Checker 1 Result 1 Overflow Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES1OVF2", description: "Checker 2 Result 1 Overflow Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES1OVF3", description: "Checker 3 Result 1 Overflow Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES1OVF4", description: "Checker 4 Result 1 Overflow Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES1OVF5", description: "Checker 5 Result 5 Overflow Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES1OVF6", description: "Checker 6 Result 1 Overflow Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES1OVF7", description: "Checker 7 Result 1 Overflow Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES1OVF8", description: "Checker 8 Result 1 Overflow Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES1OVF9", description: "Checker 9 Result 1 Overflow Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES1OVF10", description: "Checker 10 Result 1 Overflow Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES1OVF11", description: "Checker 11 Result 1 Overflow Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES1OVF12", description: "Checker 12 Result 1 Overflow Flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES1OVF13", description: "Checker 13 Result 5 Overflow Flag", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES1OVF14", description: "Checker 14 Result 1 Overflow Flag", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES1OVF15", description: "Checker 15 Result 1 Overflow Flag", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES1OVF16", description: "Checker 16 Result 1 Overflow Flag", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "RES1OVFCLR", description: "Checker Overflow Result 1 Flag Clear Register", offset: "0x6",
		bits: [
			{ name: "RES1OVF1", description: "Checker 1 Result 1  OVF Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES1OVF2", description: "Checker 2 Result 1 OVF Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES1OVF3", description: "Checker 3 Result 1 OVF Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES1OVF4", description: "Checker 4 Result 1 OVF Flag Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES1OVF5", description: "Checker 5 Result 1  OVF Flag Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES1OVF6", description: "Checker 6 Result 1 OVF Flag Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES1OVF7", description: "Checker 7 Result 1 OVF Flag Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES1OVF8", description: "Checker 8 Result 1 OVF Flag Clear", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES1OVF9", description: "Checker 9 Result 1  OVF Flag Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES1OVF10", description: "Checker 10 Result 1 OVF Flag Clear", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES1OVF11", description: "Checker 11 Result 1 OVF Flag Clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES1OVF12", description: "Checker 12 Result 1 OVF Flag Clear", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES1OVF13", description: "Checker 13 Result 1  OVF Flag Clear", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES1OVF14", description: "Checker 14 Result 1 OVF Flag Clear", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES1OVF15", description: "Checker 15 Result 1 OVF Flag Clear", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES1OVF16", description: "Checker 16 Result 1 OVF Flag Clear", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "RES2OVF", description: "Checker Overflow Result 2 Flag Register", offset: "0x8",
		bits: [
			{ name: "RES2OVF1", description: "Checker 1 Result 2 Overflow Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES2OVF2", description: "Checker 2 Result 2 Overflow Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES2OVF3", description: "Checker 3 Result 2 Overflow Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES2OVF4", description: "Checker 4 Result 2 Overflow Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES2OVF5", description: "Checker 5 Result 2 Overflow Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES2OVF6", description: "Checker 6 Result 2 Overflow Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES2OVF7", description: "Checker 7 Result 2 Overflow Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES2OVF8", description: "Checker 8 Result 2 Overflow Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES2OVF9", description: "Checker 9 Result 2 Overflow Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES2OVF10", description: "Checker 10 Result 2 Overflow Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES2OVF11", description: "Checker 11 Result 2 Overflow Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES2OVF12", description: "Checker 12 Result 2 Overflow Flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES2OVF13", description: "Checker 13 Result 2 Overflow Flag", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES2OVF14", description: "Checker 14 Result 2 Overflow Flag", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES2OVF15", description: "Checker 15 Result 2 Overflow Flag", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES2OVF16", description: "Checker 16 Result 2 Overflow Flag", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "RES2OVFCLR", description: "Checker Overflow Result 2 Flag Clear Register", offset: "0xA",
		bits: [
			{ name: "RES2OVF1", description: "Checker 1 Result 2  OVF Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES2OVF2", description: "Checker 2 Result 2 OVF Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES2OVF3", description: "Checker 3 Result 2 OVF Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES2OVF4", description: "Checker 4 Result 2 OVF Flag Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES2OVF5", description: "Checker 5 Result 2  OVF Flag Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES2OVF6", description: "Checker 6 Result 2 OVF Flag Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES2OVF7", description: "Checker 7 Result 2 OVF Flag Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES2OVF8", description: "Checker 8 Result 2 OVF Flag Clear", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES2OVF9", description: "Checker 9 Result 2  OVF Flag Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES2OVF10", description: "Checker 10 Result 2 OVF Flag Clear", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES2OVF11", description: "Checker 11 Result 2 OVF Flag Clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES2OVF12", description: "Checker 12 Result 2 OVF Flag Clear", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES2OVF13", description: "Checker 13 Result 2  OVF Flag Clear", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES2OVF14", description: "Checker 14 Result 2 OVF Flag Clear", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES2OVF15", description: "Checker 15 Result 2 OVF Flag Clear", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES2OVF16", description: "Checker 16 Result 2 OVF Flag Clear", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKINTFLG", description: "Checker Interrupt Flag Register", offset: "0xC",
		bits: [
			{ name: "CHECKINT", description: "ADC Safety Checker Subsystem Interrupt Flag", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CHECKINTFLGCLR", description: "Checker Interrupt Flag Clear Register", offset: "0xE",
		bits: [
			{ name: "CHECKINTCLR", description: "ADC Safety Checker Subsystem Interrupt Flag", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "CHECKINTSEL1", description: "Checker Interrupt Source Select Register 1", offset: "0x10",
		bits: [
			{ name: "RES1OVF1EN", description: "Overflow Enable from Checker 1 Result 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES1OVF2EN", description: "Overflow Enable from Checker 2 Result 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES1OVF3EN", description: "Overflow Enable from Checker 3 Result 1", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES1OVF4EN", description: "Overflow Enable from Checker 4 Result 1", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES1OVF5EN", description: "Overflow Enable from Checker 5 Result 1", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES1OVF6EN", description: "Overflow Enable from Checker 6 Result 1", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES1OVF7EN", description: "Overflow Enable from Checker 7 Result 1", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES1OVF8EN", description: "Overflow Enable from Checker 8 Result 1", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES1OVF9EN", description: "Overflow Enable from Checker 9 Result 1", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES1OVF10EN", description: "Overflow Enable from Checker 10 Result 1", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES1OVF11EN", description: "Overflow Enable from Checker 11 Result 1", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES1OVF12EN", description: "Overflow Enable from Checker 12 Result 1", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES1OVF13EN", description: "Overflow Enable from Checker 13 Result 1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES1OVF14EN", description: "Overflow Enable from Checker 14 Result 1", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES1OVF15EN", description: "Overflow Enable from Checker 15 Result 1", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES1OVF16EN", description: "Overflow Enable from Checker 16 Result 1", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKINTSEL2", description: "Checker Interrupt Source Select Register 2", offset: "0x12",
		bits: [
			{ name: "RES2OVF1EN", description: "Overflow Enable from Checker 1 Result 2", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES2OVF2EN", description: "Overflow Enable from Checker 2 Result 2", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES2OVF3EN", description: "Overflow Enable from Checker 3 Result 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES2OVF4EN", description: "Overflow Enable from Checker 4 Result 2", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES2OVF5EN", description: "Overflow Enable from Checker 5 Result 2", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES2OVF6EN", description: "Overflow Enable from Checker 6 Result 2", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES2OVF7EN", description: "Overflow Enable from Checker 7 Result 2", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES2OVF8EN", description: "Overflow Enable from Checker 8 Result 2", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES2OVF9EN", description: "Overflow Enable from Checker 9 Result 2", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES2OVF10EN", description: "Overflow Enable from Checker 10 Result 2", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES2OVF11EN", description: "Overflow Enable from Checker 11 Result 2", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES2OVF12EN", description: "Overflow Enable from Checker 12 Result 2", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES2OVF13EN", description: "Overflow Enable from Checker 13 Result 2", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES2OVF14EN", description: "Overflow Enable from Checker 14 Result 2", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES2OVF15EN", description: "Overflow Enable from Checker 15 Result 2", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES2OVF16EN", description: "Overflow Enable from Checker 16 Result 2", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKINTSEL3", description: "Checker Interrupt Source Select Register 3", offset: "0x14",
		bits: [
			{ name: "OOT1EN", description: "Out-of-Tolerance Enable from Checker 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "OOT2EN", description: "Out-of-Tolerance Enable from Checker 2", size: "1", shift: "1", mask: "0x2" },
			{ name: "OOT3EN", description: "Out-of-Tolerance Enable from Checker 3", size: "1", shift: "2", mask: "0x4" },
			{ name: "OOT4EN", description: "Out-of-Tolerance Enable from Checker 4", size: "1", shift: "3", mask: "0x8" },
			{ name: "OOT5EN", description: "Out-of-Tolerance Enable from Checker 5", size: "1", shift: "4", mask: "0x10" },
			{ name: "OOT6EN", description: "Out-of-Tolerance Enable from Checker 6", size: "1", shift: "5", mask: "0x20" },
			{ name: "OOT7EN", description: "Out-of-Tolerance Enable from Checker 7", size: "1", shift: "6", mask: "0x40" },
			{ name: "OOT8EN", description: "Out-of-Tolerance Enable from Checker 8", size: "1", shift: "7", mask: "0x80" },
			{ name: "OOT9EN", description: "Out-of-Tolerance Enable from Checker 9", size: "1", shift: "8", mask: "0x100" },
			{ name: "OOT10EN", description: "Out-of-Tolerance Enable from Checker 10", size: "1", shift: "9", mask: "0x200" },
			{ name: "OOT11EN", description: "Out-of-Tolerance Enable from Checker 11", size: "1", shift: "10", mask: "0x400" },
			{ name: "OOT12EN", description: "Out-of-Tolerance Enable from Checker 12", size: "1", shift: "11", mask: "0x800" },
			{ name: "OOT13EN", description: "Out-of-Tolerance Enable from Checker 13", size: "1", shift: "12", mask: "0x1000" },
			{ name: "OOT14EN", description: "Out-of-Tolerance Enable from Checker 14", size: "1", shift: "13", mask: "0x2000" },
			{ name: "OOT15EN", description: "Out-of-Tolerance Enable from Checker 15", size: "1", shift: "14", mask: "0x4000" },
			{ name: "OOT16EN", description: "Out-of-Tolerance Enable from Checker 16", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT1SEL1", description: "Checker X-Bar EVT1 Source Select Register 1", offset: "0x18",
		bits: [
			{ name: "RES1OVF1EN", description: "Overflow Enable from Checker 1 Result 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES1OVF2EN", description: "Overflow Enable from Checker 2 Result 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES1OVF3EN", description: "Overflow Enable from Checker 3 Result 1", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES1OVF4EN", description: "Overflow Enable from Checker 4 Result 1", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES1OVF5EN", description: "Overflow Enable from Checker 5 Result 1", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES1OVF6EN", description: "Overflow Enable from Checker 6 Result 1", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES1OVF7EN", description: "Overflow Enable from Checker 7 Result 1", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES1OVF8EN", description: "Overflow Enable from Checker 8 Result 1", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES1OVF9EN", description: "Overflow Enable from Checker 9 Result 1", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES1OVF10EN", description: "Overflow Enable from Checker 10 Result 1", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES1OVF11EN", description: "Overflow Enable from Checker 11 Result 1", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES1OVF12EN", description: "Overflow Enable from Checker 12 Result 1", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES1OVF13EN", description: "Overflow Enable from Checker 13 Result 1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES1OVF14EN", description: "Overflow Enable from Checker 14 Result 1", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES1OVF15EN", description: "Overflow Enable from Checker 15 Result 1", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES1OVF16EN", description: "Overflow Enable from Checker 16 Result 1", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT1SEL2", description: "Checker X-Bar EVT1 Source Select Register 2", offset: "0x1A",
		bits: [
			{ name: "RES2OVF1EN", description: "Overflow Enable from Checker 1 Result 2", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES2OVF2EN", description: "Overflow Enable from Checker 2 Result 2", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES2OVF3EN", description: "Overflow Enable from Checker 3 Result 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES2OVF4EN", description: "Overflow Enable from Checker 4 Result 2", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES2OVF5EN", description: "Overflow Enable from Checker 5 Result 2", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES2OVF6EN", description: "Overflow Enable from Checker 6 Result 2", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES2OVF7EN", description: "Overflow Enable from Checker 7 Result 2", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES2OVF8EN", description: "Overflow Enable from Checker 8 Result 2", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES2OVF9EN", description: "Overflow Enable from Checker 9 Result 2", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES2OVF10EN", description: "Overflow Enable from Checker 10 Result 2", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES2OVF11EN", description: "Overflow Enable from Checker 11 Result 2", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES2OVF12EN", description: "Overflow Enable from Checker 12 Result 2", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES2OVF13EN", description: "Overflow Enable from Checker 13 Result 2", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES2OVF14EN", description: "Overflow Enable from Checker 14 Result 2", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES2OVF15EN", description: "Overflow Enable from Checker 15 Result 2", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES2OVF16EN", description: "Overflow Enable from Checker 16 Result 2", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT1SEL3", description: "Checker X-Bar EVT1 Source Select Register 3", offset: "0x1C",
		bits: [
			{ name: "OOT1EN", description: "Out-of-Tolerance Enable from Checker 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "OOT2EN", description: "Out-of-Tolerance Enable from Checker 2", size: "1", shift: "1", mask: "0x2" },
			{ name: "OOT3EN", description: "Out-of-Tolerance Enable from Checker 3", size: "1", shift: "2", mask: "0x4" },
			{ name: "OOT4EN", description: "Out-of-Tolerance Enable from Checker 4", size: "1", shift: "3", mask: "0x8" },
			{ name: "OOT5EN", description: "Out-of-Tolerance Enable from Checker 5", size: "1", shift: "4", mask: "0x10" },
			{ name: "OOT6EN", description: "Out-of-Tolerance Enable from Checker 6", size: "1", shift: "5", mask: "0x20" },
			{ name: "OOT7EN", description: "Out-of-Tolerance Enable from Checker 7", size: "1", shift: "6", mask: "0x40" },
			{ name: "OOT8EN", description: "Out-of-Tolerance Enable from Checker 8", size: "1", shift: "7", mask: "0x80" },
			{ name: "OOT9EN", description: "Out-of-Tolerance Enable from Checker 9", size: "1", shift: "8", mask: "0x100" },
			{ name: "OOT10EN", description: "Out-of-Tolerance Enable from Checker 10", size: "1", shift: "9", mask: "0x200" },
			{ name: "OOT11EN", description: "Out-of-Tolerance Enable from Checker 11", size: "1", shift: "10", mask: "0x400" },
			{ name: "OOT12EN", description: "Out-of-Tolerance Enable from Checker 12", size: "1", shift: "11", mask: "0x800" },
			{ name: "OOT13EN", description: "Out-of-Tolerance Enable from Checker 13", size: "1", shift: "12", mask: "0x1000" },
			{ name: "OOT14EN", description: "Out-of-Tolerance Enable from Checker 14", size: "1", shift: "13", mask: "0x2000" },
			{ name: "OOT15EN", description: "Out-of-Tolerance Enable from Checker 15", size: "1", shift: "14", mask: "0x4000" },
			{ name: "OOT16EN", description: "Out-of-Tolerance Enable from Checker 16", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT2SEL1", description: "Checker X-Bar EVT2 Source Select Register 1", offset: "0x20",
		bits: [
			{ name: "RES1OVF1EN", description: "Overflow Enable from Checker 1 Result 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES1OVF2EN", description: "Overflow Enable from Checker 2 Result 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES1OVF3EN", description: "Overflow Enable from Checker 3 Result 1", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES1OVF4EN", description: "Overflow Enable from Checker 4 Result 1", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES1OVF5EN", description: "Overflow Enable from Checker 5 Result 1", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES1OVF6EN", description: "Overflow Enable from Checker 6 Result 1", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES1OVF7EN", description: "Overflow Enable from Checker 7 Result 1", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES1OVF8EN", description: "Overflow Enable from Checker 8 Result 1", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES1OVF9EN", description: "Overflow Enable from Checker 9 Result 1", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES1OVF10EN", description: "Overflow Enable from Checker 10 Result 1", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES1OVF11EN", description: "Overflow Enable from Checker 11 Result 1", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES1OVF12EN", description: "Overflow Enable from Checker 12 Result 1", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES1OVF13EN", description: "Overflow Enable from Checker 13 Result 1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES1OVF14EN", description: "Overflow Enable from Checker 14 Result 1", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES1OVF15EN", description: "Overflow Enable from Checker 15 Result 1", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES1OVF16EN", description: "Overflow Enable from Checker 16 Result 1", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT2SEL2", description: "Checker X-Bar EVT2 Source Select Register 2", offset: "0x22",
		bits: [
			{ name: "RES2OVF1EN", description: "Overflow Enable from Checker 1 Result 2", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES2OVF2EN", description: "Overflow Enable from Checker 2 Result 2", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES2OVF3EN", description: "Overflow Enable from Checker 3 Result 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES2OVF4EN", description: "Overflow Enable from Checker 4 Result 2", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES2OVF5EN", description: "Overflow Enable from Checker 5 Result 2", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES2OVF6EN", description: "Overflow Enable from Checker 6 Result 2", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES2OVF7EN", description: "Overflow Enable from Checker 7 Result 2", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES2OVF8EN", description: "Overflow Enable from Checker 8 Result 2", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES2OVF9EN", description: "Overflow Enable from Checker 9 Result 2", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES2OVF10EN", description: "Overflow Enable from Checker 10 Result 2", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES2OVF11EN", description: "Overflow Enable from Checker 11 Result 2", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES2OVF12EN", description: "Overflow Enable from Checker 12 Result 2", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES2OVF13EN", description: "Overflow Enable from Checker 13 Result 2", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES2OVF14EN", description: "Overflow Enable from Checker 14 Result 2", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES2OVF15EN", description: "Overflow Enable from Checker 15 Result 2", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES2OVF16EN", description: "Overflow Enable from Checker 16 Result 2", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT2SEL3", description: "Checker X-Bar EVT2 Source Select Register 3", offset: "0x24",
		bits: [
			{ name: "OOT1EN", description: "Out-of-Tolerance Enable from Checker 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "OOT2EN", description: "Out-of-Tolerance Enable from Checker 2", size: "1", shift: "1", mask: "0x2" },
			{ name: "OOT3EN", description: "Out-of-Tolerance Enable from Checker 3", size: "1", shift: "2", mask: "0x4" },
			{ name: "OOT4EN", description: "Out-of-Tolerance Enable from Checker 4", size: "1", shift: "3", mask: "0x8" },
			{ name: "OOT5EN", description: "Out-of-Tolerance Enable from Checker 5", size: "1", shift: "4", mask: "0x10" },
			{ name: "OOT6EN", description: "Out-of-Tolerance Enable from Checker 6", size: "1", shift: "5", mask: "0x20" },
			{ name: "OOT7EN", description: "Out-of-Tolerance Enable from Checker 7", size: "1", shift: "6", mask: "0x40" },
			{ name: "OOT8EN", description: "Out-of-Tolerance Enable from Checker 8", size: "1", shift: "7", mask: "0x80" },
			{ name: "OOT9EN", description: "Out-of-Tolerance Enable from Checker 9", size: "1", shift: "8", mask: "0x100" },
			{ name: "OOT10EN", description: "Out-of-Tolerance Enable from Checker 10", size: "1", shift: "9", mask: "0x200" },
			{ name: "OOT11EN", description: "Out-of-Tolerance Enable from Checker 11", size: "1", shift: "10", mask: "0x400" },
			{ name: "OOT12EN", description: "Out-of-Tolerance Enable from Checker 12", size: "1", shift: "11", mask: "0x800" },
			{ name: "OOT13EN", description: "Out-of-Tolerance Enable from Checker 13", size: "1", shift: "12", mask: "0x1000" },
			{ name: "OOT14EN", description: "Out-of-Tolerance Enable from Checker 14", size: "1", shift: "13", mask: "0x2000" },
			{ name: "OOT15EN", description: "Out-of-Tolerance Enable from Checker 15", size: "1", shift: "14", mask: "0x4000" },
			{ name: "OOT16EN", description: "Out-of-Tolerance Enable from Checker 16", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT3SEL1", description: "Checker X-Bar EVT3 Source Select Register 1", offset: "0x28",
		bits: [
			{ name: "RES1OVF1EN", description: "Overflow Enable from Checker 1 Result 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES1OVF2EN", description: "Overflow Enable from Checker 2 Result 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES1OVF3EN", description: "Overflow Enable from Checker 3 Result 1", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES1OVF4EN", description: "Overflow Enable from Checker 4 Result 1", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES1OVF5EN", description: "Overflow Enable from Checker 5 Result 1", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES1OVF6EN", description: "Overflow Enable from Checker 6 Result 1", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES1OVF7EN", description: "Overflow Enable from Checker 7 Result 1", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES1OVF8EN", description: "Overflow Enable from Checker 8 Result 1", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES1OVF9EN", description: "Overflow Enable from Checker 9 Result 1", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES1OVF10EN", description: "Overflow Enable from Checker 10 Result 1", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES1OVF11EN", description: "Overflow Enable from Checker 11 Result 1", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES1OVF12EN", description: "Overflow Enable from Checker 12 Result 1", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES1OVF13EN", description: "Overflow Enable from Checker 13 Result 1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES1OVF14EN", description: "Overflow Enable from Checker 14 Result 1", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES1OVF15EN", description: "Overflow Enable from Checker 15 Result 1", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES1OVF16EN", description: "Overflow Enable from Checker 16 Result 1", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT3SEL2", description: "Checker X-Bar EVT3 Source Select Register 2", offset: "0x2A",
		bits: [
			{ name: "RES2OVF1EN", description: "Overflow Enable from Checker 1 Result 2", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES2OVF2EN", description: "Overflow Enable from Checker 2 Result 2", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES2OVF3EN", description: "Overflow Enable from Checker 3 Result 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES2OVF4EN", description: "Overflow Enable from Checker 4 Result 2", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES2OVF5EN", description: "Overflow Enable from Checker 5 Result 2", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES2OVF6EN", description: "Overflow Enable from Checker 6 Result 2", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES2OVF7EN", description: "Overflow Enable from Checker 7 Result 2", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES2OVF8EN", description: "Overflow Enable from Checker 8 Result 2", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES2OVF9EN", description: "Overflow Enable from Checker 9 Result 2", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES2OVF10EN", description: "Overflow Enable from Checker 10 Result 2", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES2OVF11EN", description: "Overflow Enable from Checker 11 Result 2", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES2OVF12EN", description: "Overflow Enable from Checker 12 Result 2", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES2OVF13EN", description: "Overflow Enable from Checker 13 Result 2", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES2OVF14EN", description: "Overflow Enable from Checker 14 Result 2", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES2OVF15EN", description: "Overflow Enable from Checker 15 Result 2", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES2OVF16EN", description: "Overflow Enable from Checker 16 Result 2", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT3SEL3", description: "Checker X-Bar EVT3 Source Select Register 3", offset: "0x2C",
		bits: [
			{ name: "OOT1EN", description: "Out-of-Tolerance Enable from Checker 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "OOT2EN", description: "Out-of-Tolerance Enable from Checker 2", size: "1", shift: "1", mask: "0x2" },
			{ name: "OOT3EN", description: "Out-of-Tolerance Enable from Checker 3", size: "1", shift: "2", mask: "0x4" },
			{ name: "OOT4EN", description: "Out-of-Tolerance Enable from Checker 4", size: "1", shift: "3", mask: "0x8" },
			{ name: "OOT5EN", description: "Out-of-Tolerance Enable from Checker 5", size: "1", shift: "4", mask: "0x10" },
			{ name: "OOT6EN", description: "Out-of-Tolerance Enable from Checker 6", size: "1", shift: "5", mask: "0x20" },
			{ name: "OOT7EN", description: "Out-of-Tolerance Enable from Checker 7", size: "1", shift: "6", mask: "0x40" },
			{ name: "OOT8EN", description: "Out-of-Tolerance Enable from Checker 8", size: "1", shift: "7", mask: "0x80" },
			{ name: "OOT9EN", description: "Out-of-Tolerance Enable from Checker 9", size: "1", shift: "8", mask: "0x100" },
			{ name: "OOT10EN", description: "Out-of-Tolerance Enable from Checker 10", size: "1", shift: "9", mask: "0x200" },
			{ name: "OOT11EN", description: "Out-of-Tolerance Enable from Checker 11", size: "1", shift: "10", mask: "0x400" },
			{ name: "OOT12EN", description: "Out-of-Tolerance Enable from Checker 12", size: "1", shift: "11", mask: "0x800" },
			{ name: "OOT13EN", description: "Out-of-Tolerance Enable from Checker 13", size: "1", shift: "12", mask: "0x1000" },
			{ name: "OOT14EN", description: "Out-of-Tolerance Enable from Checker 14", size: "1", shift: "13", mask: "0x2000" },
			{ name: "OOT15EN", description: "Out-of-Tolerance Enable from Checker 15", size: "1", shift: "14", mask: "0x4000" },
			{ name: "OOT16EN", description: "Out-of-Tolerance Enable from Checker 16", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT4SEL1", description: "Checker X-Bar EVT4 Source Select Register 1", offset: "0x30",
		bits: [
			{ name: "RES1OVF1EN", description: "Overflow Enable from Checker 1 Result 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES1OVF2EN", description: "Overflow Enable from Checker 2 Result 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES1OVF3EN", description: "Overflow Enable from Checker 3 Result 1", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES1OVF4EN", description: "Overflow Enable from Checker 4 Result 1", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES1OVF5EN", description: "Overflow Enable from Checker 5 Result 1", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES1OVF6EN", description: "Overflow Enable from Checker 6 Result 1", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES1OVF7EN", description: "Overflow Enable from Checker 7 Result 1", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES1OVF8EN", description: "Overflow Enable from Checker 8 Result 1", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES1OVF9EN", description: "Overflow Enable from Checker 9 Result 1", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES1OVF10EN", description: "Overflow Enable from Checker 10 Result 1", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES1OVF11EN", description: "Overflow Enable from Checker 11 Result 1", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES1OVF12EN", description: "Overflow Enable from Checker 12 Result 1", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES1OVF13EN", description: "Overflow Enable from Checker 13 Result 1", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES1OVF14EN", description: "Overflow Enable from Checker 14 Result 1", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES1OVF15EN", description: "Overflow Enable from Checker 15 Result 1", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES1OVF16EN", description: "Overflow Enable from Checker 16 Result 1", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT4SEL2", description: "Checker X-Bar EVT4 Source Select Register 2", offset: "0x32",
		bits: [
			{ name: "RES2OVF1EN", description: "Overflow Enable from Checker 1 Result 2", size: "1", shift: "0", mask: "0x1" },
			{ name: "RES2OVF2EN", description: "Overflow Enable from Checker 2 Result 2", size: "1", shift: "1", mask: "0x2" },
			{ name: "RES2OVF3EN", description: "Overflow Enable from Checker 3 Result 2", size: "1", shift: "2", mask: "0x4" },
			{ name: "RES2OVF4EN", description: "Overflow Enable from Checker 4 Result 2", size: "1", shift: "3", mask: "0x8" },
			{ name: "RES2OVF5EN", description: "Overflow Enable from Checker 5 Result 2", size: "1", shift: "4", mask: "0x10" },
			{ name: "RES2OVF6EN", description: "Overflow Enable from Checker 6 Result 2", size: "1", shift: "5", mask: "0x20" },
			{ name: "RES2OVF7EN", description: "Overflow Enable from Checker 7 Result 2", size: "1", shift: "6", mask: "0x40" },
			{ name: "RES2OVF8EN", description: "Overflow Enable from Checker 8 Result 2", size: "1", shift: "7", mask: "0x80" },
			{ name: "RES2OVF9EN", description: "Overflow Enable from Checker 9 Result 2", size: "1", shift: "8", mask: "0x100" },
			{ name: "RES2OVF10EN", description: "Overflow Enable from Checker 10 Result 2", size: "1", shift: "9", mask: "0x200" },
			{ name: "RES2OVF11EN", description: "Overflow Enable from Checker 11 Result 2", size: "1", shift: "10", mask: "0x400" },
			{ name: "RES2OVF12EN", description: "Overflow Enable from Checker 12 Result 2", size: "1", shift: "11", mask: "0x800" },
			{ name: "RES2OVF13EN", description: "Overflow Enable from Checker 13 Result 2", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RES2OVF14EN", description: "Overflow Enable from Checker 14 Result 2", size: "1", shift: "13", mask: "0x2000" },
			{ name: "RES2OVF15EN", description: "Overflow Enable from Checker 15 Result 2", size: "1", shift: "14", mask: "0x4000" },
			{ name: "RES2OVF16EN", description: "Overflow Enable from Checker 16 Result 2", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CHECKEVT4SEL3", description: "Checker X-Bar EVT4 Source Select Register 3", offset: "0x34",
		bits: [
			{ name: "OOT1EN", description: "Out-of-Tolerance Enable from Checker 1", size: "1", shift: "0", mask: "0x1" },
			{ name: "OOT2EN", description: "Out-of-Tolerance Enable from Checker 2", size: "1", shift: "1", mask: "0x2" },
			{ name: "OOT3EN", description: "Out-of-Tolerance Enable from Checker 3", size: "1", shift: "2", mask: "0x4" },
			{ name: "OOT4EN", description: "Out-of-Tolerance Enable from Checker 4", size: "1", shift: "3", mask: "0x8" },
			{ name: "OOT5EN", description: "Out-of-Tolerance Enable from Checker 5", size: "1", shift: "4", mask: "0x10" },
			{ name: "OOT6EN", description: "Out-of-Tolerance Enable from Checker 6", size: "1", shift: "5", mask: "0x20" },
			{ name: "OOT7EN", description: "Out-of-Tolerance Enable from Checker 7", size: "1", shift: "6", mask: "0x40" },
			{ name: "OOT8EN", description: "Out-of-Tolerance Enable from Checker 8", size: "1", shift: "7", mask: "0x80" },
			{ name: "OOT9EN", description: "Out-of-Tolerance Enable from Checker 9", size: "1", shift: "8", mask: "0x100" },
			{ name: "OOT10EN", description: "Out-of-Tolerance Enable from Checker 10", size: "1", shift: "9", mask: "0x200" },
			{ name: "OOT11EN", description: "Out-of-Tolerance Enable from Checker 11", size: "1", shift: "10", mask: "0x400" },
			{ name: "OOT12EN", description: "Out-of-Tolerance Enable from Checker 12", size: "1", shift: "11", mask: "0x800" },
			{ name: "OOT13EN", description: "Out-of-Tolerance Enable from Checker 13", size: "1", shift: "12", mask: "0x1000" },
			{ name: "OOT14EN", description: "Out-of-Tolerance Enable from Checker 14", size: "1", shift: "13", mask: "0x2000" },
			{ name: "OOT15EN", description: "Out-of-Tolerance Enable from Checker 15", size: "1", shift: "14", mask: "0x4000" },
			{ name: "OOT16EN", description: "Out-of-Tolerance Enable from Checker 16", size: "1", shift: "15", mask: "0x8000" },
		]
	},
];
module.exports = {
	ADCRegisters: ADCRegisters,
}
