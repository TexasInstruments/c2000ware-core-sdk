let ADCRegisters = [
	{ name: "CTL1", description: "ADC Control 1 Register", offset: "0x0",
		bits: [
			{ name: "INTPULSEPOS", description: "ADC Interrupt Pulse Position", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADCPWDNZ", description: "ADC Power Down", size: "1", shift: "7", mask: "0x80" },
			{ name: "ADCBSYCHN", description: "ADC Busy Channel", size: "4", shift: "8", mask: "0xF00" },
			{ name: "ADCBSY", description: "ADC Busy", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "CTL2", description: "ADC Control 2 Register", offset: "0x1",
		bits: [
			{ name: "PRESCALE", description: "ADC Clock Prescaler", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "BURSTCTL", description: "ADC Burst Control Register", offset: "0x2",
		bits: [
			{ name: "BURSTTRIGSEL", description: "SOC Burst Trigger Source Select", size: "6", shift: "0", mask: "0x3F" },
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
			{ name: "INT1SEL", description: "ADCINT1 EOC Source Select", size: "4", shift: "0", mask: "0xF" },
			{ name: "INT1E", description: "ADCINT1 Interrupt Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT1CONT", description: "ADCINT1 Continue to Interrupt Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT2SEL", description: "ADCINT2 EOC Source Select", size: "4", shift: "8", mask: "0xF00" },
			{ name: "INT2E", description: "ADCINT2 Interrupt Enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "INT2CONT", description: "ADCINT2 Continue to Interrupt Mode", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "INTSEL3N4", description: "ADC Interrupt 3 and 4 Selection Register", offset: "0x8",
		bits: [
			{ name: "INT3SEL", description: "ADCINT3 EOC Source Select", size: "4", shift: "0", mask: "0xF" },
			{ name: "INT3E", description: "ADCINT3 Interrupt Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT3CONT", description: "ADCINT3 Continue to Interrupt Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT4SEL", description: "ADCINT4 EOC Source Select", size: "4", shift: "8", mask: "0xF00" },
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
			{ name: "CHSEL", description: "SOC0 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC0 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC1CTL", description: "ADC SOC1 Control Register", offset: "0x12",
		bits: [
			{ name: "ACQPS", description: "SOC1 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC1 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC1 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC2CTL", description: "ADC SOC2 Control Register", offset: "0x14",
		bits: [
			{ name: "ACQPS", description: "SOC2 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC2 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC2 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC3CTL", description: "ADC SOC3 Control Register", offset: "0x16",
		bits: [
			{ name: "ACQPS", description: "SOC3 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC3 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC3 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC4CTL", description: "ADC SOC4 Control Register", offset: "0x18",
		bits: [
			{ name: "ACQPS", description: "SOC4 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC4 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC4 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC5CTL", description: "ADC SOC5 Control Register", offset: "0x1A",
		bits: [
			{ name: "ACQPS", description: "SOC5 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC5 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC5 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC6CTL", description: "ADC SOC6 Control Register", offset: "0x1C",
		bits: [
			{ name: "ACQPS", description: "SOC6 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC6 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC6 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC7CTL", description: "ADC SOC7 Control Register", offset: "0x1E",
		bits: [
			{ name: "ACQPS", description: "SOC7 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC7 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC7 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC8CTL", description: "ADC SOC8 Control Register", offset: "0x20",
		bits: [
			{ name: "ACQPS", description: "SOC8 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC8 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC8 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC9CTL", description: "ADC SOC9 Control Register", offset: "0x22",
		bits: [
			{ name: "ACQPS", description: "SOC9 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC9 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC9 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC10CTL", description: "ADC SOC10 Control Register", offset: "0x24",
		bits: [
			{ name: "ACQPS", description: "SOC10 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC10 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC10 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC11CTL", description: "ADC SOC11 Control Register", offset: "0x26",
		bits: [
			{ name: "ACQPS", description: "SOC11 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC11 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC11 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC12CTL", description: "ADC SOC12 Control Register", offset: "0x28",
		bits: [
			{ name: "ACQPS", description: "SOC12 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC12 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC12 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC13CTL", description: "ADC SOC13 Control Register", offset: "0x2A",
		bits: [
			{ name: "ACQPS", description: "SOC13 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC13 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC13 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC14CTL", description: "ADC SOC14 Control Register", offset: "0x2C",
		bits: [
			{ name: "ACQPS", description: "SOC14 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC14 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC14 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC15CTL", description: "ADC SOC15 Control Register", offset: "0x2E",
		bits: [
			{ name: "ACQPS", description: "SOC15 Acquisition Prescale", size: "9", shift: "0", mask: "0x1FF" },
			{ name: "CHSEL", description: "SOC15 Channel Select", size: "4", shift: "15", mask: "0x78000" },
			{ name: "TRIGSEL", description: "SOC15 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
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
			{ name: "OFFTRIM", description: "ADC Offset Trim", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PPB1CONFIG", description: "ADC PPB1 Config Register", offset: "0x40",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 1 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 1 Two's Complement Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
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
			{ name: "LIMITHI", description: "ADC Post Processing Block 1 Trip High Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "HSIGN", description: "High Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "PPB1TRIPLO", description: "ADC PPB1 Trip Low/Trigger Time Stamp Register", offset: "0x46",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 1 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 1 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
		]
	},
	{ name: "PPB2CONFIG", description: "ADC PPB2 Config Register", offset: "0x48",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 2 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 2 Two's Complement Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
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
			{ name: "LIMITHI", description: "ADC Post Processing Block 2 Trip High Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "HSIGN", description: "High Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "PPB2TRIPLO", description: "ADC PPB2 Trip Low/Trigger Time Stamp Register", offset: "0x4E",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 2 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 2 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
		]
	},
	{ name: "PPB3CONFIG", description: "ADC PPB3 Config Register", offset: "0x50",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 3 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 3 Two's Complement Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
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
			{ name: "LIMITHI", description: "ADC Post Processing Block 3 Trip High Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "HSIGN", description: "High Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "PPB3TRIPLO", description: "ADC PPB3 Trip Low/Trigger Time Stamp Register", offset: "0x56",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 3 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 3 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
		]
	},
	{ name: "PPB4CONFIG", description: "ADC PPB4 Config Register", offset: "0x58",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block 4 Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block 4 Two's Complement Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
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
			{ name: "LIMITHI", description: "ADC Post Processing Block 4 Trip High Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "HSIGN", description: "High Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "PPB4TRIPLO", description: "ADC PPB4 Trip Low/Trigger Time Stamp Register", offset: "0x5E",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 4 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "LSIGN", description: "Low Limit Sign Bit", size: "1", shift: "16", mask: "0x10000" },
			{ name: "REQSTAMP", description: "ADC Post Processing Block 4 Request Time Stamp", size: "12", shift: "20", mask: "0xFFF00000" },
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
];
module.exports = {
	ADCRegisters: ADCRegisters,
}
