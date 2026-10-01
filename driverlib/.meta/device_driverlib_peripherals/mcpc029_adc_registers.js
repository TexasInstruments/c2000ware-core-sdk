let ADCRegisters = [
	{ name: "CTL1", description: "ADC Control 1 Register", offset: "0x0",
		bits: [
			{ name: "INTPULSEPOS", description: "ADC Interrupt Pulse Position", size: "1", shift: "2", mask: "0x4" },
			{ name: "ADCPWDNZ", description: "ADC Power Down", size: "1", shift: "7", mask: "0x80" },
			{ name: "ADCBSYCHN", description: "ADC Busy Channel", size: "4", shift: "8", mask: "0xF00" },
			{ name: "ADCBSY", description: "ADC Busy", size: "1", shift: "13", mask: "0x2000" },
		]
	},
	{ name: "CTL2", description: "ADC Control 2 Register", offset: "0x2",
		bits: [
			{ name: "PRESCALE", description: "ADC Clock Prescaler", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "INTSEL", description: "ADC Interrupt 1, 2, 3 and 4 Selection Register", offset: "0x8",
		bits: [
			{ name: "INT1SEL", description: "ADCINT1 EOC Source Select", size: "6", shift: "0", mask: "0x3F" },
			{ name: "INT1CONT", description: "ADCINT1 Continue to Interrupt Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT1E", description: "ADCINT1 Interrupt Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "INT2SEL", description: "ADCINT2 EOC Source Select", size: "6", shift: "8", mask: "0x3F00" },
			{ name: "INT2CONT", description: "ADCINT2 Continue to Interrupt Mode", size: "1", shift: "14", mask: "0x4000" },
			{ name: "INT2E", description: "ADCINT2 Interrupt Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "DMAINTSEL", description: "ADC DMA Interrupt 1, 2, 3 and 4 Selection Register", offset: "0xA",
		bits: [
			{ name: "DMAINT1SEL", description: "ADCDMAINT1 EOC Source Select", size: "6", shift: "0", mask: "0x3F" },
			{ name: "DMAINT1CONT", description: "ADCDMAINT1 Continue to Interrupt Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "DMAINT1E", description: "ADCDMAINT1 Interrupt Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "DMAINT2SEL", description: "ADCDMAINT2 EOC Source Select", size: "6", shift: "8", mask: "0x3F00" },
			{ name: "DMAINT2CONT", description: "ADCDMAINT2 Continue to Interrupt Mode", size: "1", shift: "14", mask: "0x4000" },
			{ name: "DMAINT2E", description: "ADCDMAINT2 Interrupt Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "RAWINTFLG", description: "ADC Raw Interrupt Flag Register", offset: "0xC",
		bits: [
			{ name: "ADCRAWINT1", description: "ADC Raw Interrupt 1 Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCRAWINT2", description: "ADC Raw Interrupt 2 Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCDMARAWINT1", description: "ADC DMA Raw Interrupt 1 Flag", size: "1", shift: "16", mask: "0x10000" },
			{ name: "ADCDMARAWINT2", description: "ADC DMA Raw Interrupt 2 Flag", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "INTFLG", description: "ADC Interrupt Flag Register", offset: "0xE",
		bits: [
			{ name: "ADCINT1", description: "ADC Interrupt 1 Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2", description: "ADC Interrupt 2 Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCINT1RESULT", description: "ADC Interrupt 1 Results Ready", size: "1", shift: "8", mask: "0x100" },
			{ name: "ADCINT2RESULT", description: "ADC Interrupt 2 Results Ready", size: "1", shift: "9", mask: "0x200" },
			{ name: "ADCDMAINT1", description: "ADC DMA Interrupt 1 Flag", size: "1", shift: "16", mask: "0x10000" },
			{ name: "ADCDMAINT2", description: "ADC DMA Interrupt 2 Flag", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "INTFLGFRC", description: "ADC Interrupt Flag Force Register", offset: "0x10",
		bits: [
			{ name: "ADCINT1", description: "ADC Interrupt 1 Flag Force", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2", description: "ADC Interrupt 2 Flag Force", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCDMAINT1", description: "ADC DMA Interrupt 1 Flag Force", size: "1", shift: "16", mask: "0x10000" },
			{ name: "ADCDMAINT2", description: "ADC DMA Interrupt 2 Flag Force", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "INTFLGCLR", description: "ADC Interrupt Flag Clear Register", offset: "0x12",
		bits: [
			{ name: "ADCINT1", description: "ADC Interrupt 1 Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2", description: "ADC Interrupt 2 Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCDMAINT1", description: "ADC DMA Interrupt 1 Flag Clear", size: "1", shift: "16", mask: "0x10000" },
			{ name: "ADCDMAINT2", description: "ADC DMA Interrupt 2 Flag Clear", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "INTOVF", description: "ADC Interrupt Overflow Register", offset: "0x14",
		bits: [
			{ name: "ADCINT1OVF", description: "ADC Interrupt 1 Overflow Flags", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2OVF", description: "ADC Interrupt 2 Overflow Flags", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCDMAINT1OVF", description: "ADC DMA Interrupt 1 Overflow Flags", size: "1", shift: "16", mask: "0x10000" },
			{ name: "ADCDMAINT2OVF", description: "ADC DMA Interrupt 2 Overflow Flags", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "INTOVFCLR", description: "ADC Interrupt Overflow Clear Register", offset: "0x16",
		bits: [
			{ name: "ADCINT1OVF", description: "ADC Interrupt 1 Overflow Clear Bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "ADCINT2OVF", description: "ADC Interrupt 2 Overflow Clear Bits", size: "1", shift: "1", mask: "0x2" },
			{ name: "ADCDMAINT1OVF", description: "ADC DMA Interrupt 1 Overflow Clear Bits", size: "1", shift: "16", mask: "0x10000" },
			{ name: "ADCDMAINT2OVF", description: "ADC DMA Interrupt 2 Overflow Clear Bits", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "SOCPRICTL", description: "ADC SOC Priority Control Register", offset: "0x18",
		bits: [
			{ name: "SOCPRIORITY", description: "SOC Priority", size: "2", shift: "0", mask: "0x3" },
			{ name: "RRPOINTER", description: "Round Robin Pointer", size: "5", shift: "6", mask: "0x7C0" },
		]
	},
	{ name: "INTSOCSEL1", description: "ADC Interrupt SOC Selection 1 Register", offset: "0x1A",
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
	{ name: "SOCFLG1", description: "ADC SOC Flag 1 Register", offset: "0x1E",
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
	{ name: "SOCFRC1", description: "ADC SOC Force 1 Register", offset: "0x20",
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
	{ name: "SOCOVF1", description: "ADC SOC Overflow 1 Register", offset: "0x22",
		bits: [
			{ name: "SOC0OVF", description: "SOC0 Start of Conversion Overflow Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOC1OVF", description: "SOC1 Start of Conversion Overflow Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "SOC2OVF", description: "SOC2 Start of Conversion Overflow Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "SOC3OVF", description: "SOC3 Start of Conversion Overflow Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "SOC4OVF", description: "SOC4 Start of Conversion Overflow Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "SOC5OVF", description: "SOC5 Start of Conversion Overflow Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "SOC6OVF", description: "SOC6 Start of Conversion Overflow Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "SOC7OVF", description: "SOC7 Start of Conversion Overflow Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "SOC8OVF", description: "SOC8 Start of Conversion Overflow Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "SOC9OVF", description: "SOC9 Start of Conversion Overflow Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "SOC10OVF", description: "SOC10 Start of Conversion Overflow Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "SOC11OVF", description: "SOC11 Start of Conversion Overflow Flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "SOC12OVF", description: "SOC12 Start of Conversion Overflow Flag", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SOC13OVF", description: "SOC13 Start of Conversion Overflow Flag", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SOC14OVF", description: "SOC14 Start of Conversion Overflow Flag", size: "1", shift: "14", mask: "0x4000" },
			{ name: "SOC15OVF", description: "SOC15 Start of Conversion Overflow Flag", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SOCOVFCLR1", description: "ADC SOC Overflow Clear 1 Register", offset: "0x24",
		bits: [
			{ name: "SOC0OVF", description: "SOC0 Clear Start of Conversion Overflow Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOC1OVF", description: "SOC1 Clear Start of Conversion Overflow Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SOC2OVF", description: "SOC2 Clear Start of Conversion Overflow Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "SOC3OVF", description: "SOC3 Clear Start of Conversion Overflow Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "SOC4OVF", description: "SOC4 Clear Start of Conversion Overflow Bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "SOC5OVF", description: "SOC5 Clear Start of Conversion Overflow Bit", size: "1", shift: "5", mask: "0x20" },
			{ name: "SOC6OVF", description: "SOC6 Clear Start of Conversion Overflow Bit", size: "1", shift: "6", mask: "0x40" },
			{ name: "SOC7OVF", description: "SOC7 Clear Start of Conversion Overflow Bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "SOC8OVF", description: "SOC8 Clear Start of Conversion Overflow Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "SOC9OVF", description: "SOC9 Clear Start of Conversion Overflow Bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "SOC10OVF", description: "SOC10 Clear Start of Conversion Overflow Bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "SOC11OVF", description: "SOC11 Clear Start of Conversion Overflow Bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "SOC12OVF", description: "SOC12 Clear Start of Conversion Overflow Bit", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SOC13OVF", description: "SOC13 Clear Start of Conversion Overflow Bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SOC14OVF", description: "SOC14 Clear Start of Conversion Overflow Bit", size: "1", shift: "14", mask: "0x4000" },
			{ name: "SOC15OVF", description: "SOC15 Clear Start of Conversion Overflow Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "SOC0CTL", description: "ADC SOC0 Control Register", offset: "0x26",
		bits: [
			{ name: "ACQPS", description: "SOC0 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC0 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC0 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC0 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC0 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC1CTL", description: "ADC SOC1 Control Register", offset: "0x28",
		bits: [
			{ name: "ACQPS", description: "SOC1 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC1 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC1 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC1 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC1 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC2CTL", description: "ADC SOC2 Control Register", offset: "0x2A",
		bits: [
			{ name: "ACQPS", description: "SOC2 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC2 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC2 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC2 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC2 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC3CTL", description: "ADC SOC3 Control Register", offset: "0x2C",
		bits: [
			{ name: "ACQPS", description: "SOC3 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC3 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC3 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC3 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC3 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC4CTL", description: "ADC SOC4 Control Register", offset: "0x2E",
		bits: [
			{ name: "ACQPS", description: "SOC4 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC4 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC4 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC4 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC4 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC5CTL", description: "ADC SOC5 Control Register", offset: "0x30",
		bits: [
			{ name: "ACQPS", description: "SOC5 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC5 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC5 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC5 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC5 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC6CTL", description: "ADC SOC6 Control Register", offset: "0x32",
		bits: [
			{ name: "ACQPS", description: "SOC6 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC6 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC6 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC6 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC6 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC7CTL", description: "ADC SOC7 Control Register", offset: "0x34",
		bits: [
			{ name: "ACQPS", description: "SOC7 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC7 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC7 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC7 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC7 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC8CTL", description: "ADC SOC8 Control Register", offset: "0x36",
		bits: [
			{ name: "ACQPS", description: "SOC8 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC8 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC8 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC8 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC8 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC9CTL", description: "ADC SOC9 Control Register", offset: "0x38",
		bits: [
			{ name: "ACQPS", description: "SOC9 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC9 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC9 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC9 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC9 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC10CTL", description: "ADC SOC10 Control Register", offset: "0x3A",
		bits: [
			{ name: "ACQPS", description: "SOC10 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC10 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC10 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC10 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC10 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC11CTL", description: "ADC SOC11 Control Register", offset: "0x3C",
		bits: [
			{ name: "ACQPS", description: "SOC11 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC11 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC11 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC11 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC11 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC12CTL", description: "ADC SOC12 Control Register", offset: "0x3E",
		bits: [
			{ name: "ACQPS", description: "SOC12 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC12 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC12 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC12 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC12 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC13CTL", description: "ADC SOC13 Control Register", offset: "0x40",
		bits: [
			{ name: "ACQPS", description: "SOC13 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC13 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC13 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC13 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC13 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC14CTL", description: "ADC SOC14 Control Register", offset: "0x42",
		bits: [
			{ name: "ACQPS", description: "SOC14 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC14 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC14 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC14 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC14 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "SOC15CTL", description: "ADC SOC15 Control Register", offset: "0x44",
		bits: [
			{ name: "ACQPS", description: "SOC15 Acquisition Prescale", size: "8", shift: "0", mask: "0xFF" },
			{ name: "SAMPCAPRESETDISABLE", description: "SOC15 Sample Cap Reset Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "SAMPCAPRESETSEL", description: "SOC15 Sample Cap Reset Select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CHSEL", description: "SOC15 Channel Select", size: "5", shift: "15", mask: "0xF8000" },
			{ name: "TRIGSEL", description: "SOC15 Trigger Source Select", size: "5", shift: "20", mask: "0x1F00000" },
		]
	},
	{ name: "EVTSTAT", description: "ADC Event Status Register", offset: "0x66",
		bits: [
			{ name: "PPB1TRIPHI", description: "Post Processing Block 1 Trip High Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "PPB1TRIPLO", description: "Post Processing Block 1 Trip Low Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "PPB1ZERO", description: "Post Processing Block 1 Zero Crossing Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "PPB1INLIMIT", description: "Post Processing Block 1 Within trip limit Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "PPB2TRIPHI", description: "Post Processing Block 2 Trip High Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "PPB2TRIPLO", description: "Post Processing Block 2 Trip Low Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "PPB2ZERO", description: "Post Processing Block 2 Zero Crossing Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "PPB2INLIMIT", description: "Post Processing Block 2 Within trip limit Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "PPB3TRIPHI", description: "Post Processing Block 3 Trip High Flag", size: "1", shift: "8", mask: "0x100" },
			{ name: "PPB3TRIPLO", description: "Post Processing Block 3 Trip Low Flag", size: "1", shift: "9", mask: "0x200" },
			{ name: "PPB3ZERO", description: "Post Processing Block 3 Zero Crossing Flag", size: "1", shift: "10", mask: "0x400" },
			{ name: "PPB3INLIMIT", description: "Post Processing Block 3 Within trip limit Flag", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "EVTCLR", description: "ADC Event Clear Register", offset: "0x68",
		bits: [
			{ name: "PPB1TRIPHI", description: "Post Processing Block 1 Trip High Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "PPB1TRIPLO", description: "Post Processing Block 1 Trip Low Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "PPB1ZERO", description: "Post Processing Block 1 Zero Crossing Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "PPB1INLIMIT", description: "Post Processing Block 1 Within trip limit flag Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "PPB2TRIPHI", description: "Post Processing Block 2 Trip High Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "PPB2TRIPLO", description: "Post Processing Block 2 Trip Low Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "PPB2ZERO", description: "Post Processing Block 2 Zero Crossing Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "PPB2INLIMIT", description: "Post Processing Block 2 Within trip limit flag Clear", size: "1", shift: "7", mask: "0x80" },
			{ name: "PPB3TRIPHI", description: "Post Processing Block 3 Trip High Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "PPB3TRIPLO", description: "Post Processing Block 3 Trip Low Clear", size: "1", shift: "9", mask: "0x200" },
			{ name: "PPB3ZERO", description: "Post Processing Block 3 Zero Crossing Clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "PPB3INLIMIT", description: "Post Processing Block 3 Within trip limit flag Clear", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "EVTSEL", description: "ADC Event Selection Register", offset: "0x6A",
		bits: [
			{ name: "PPB1TRIPHI", description: "Post Processing Block 1 Trip High Event Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "PPB1TRIPLO", description: "Post Processing Block 1 Trip Low Event Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "PPB1ZERO", description: "Post Processing Block 1 Zero Crossing Event Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "PPB1INLIMIT", description: "Post Processing Block 1 Within trip limit event enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "PPB2TRIPHI", description: "Post Processing Block 2 Trip High Event Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "PPB2TRIPLO", description: "Post Processing Block 2 Trip Low Event Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "PPB2ZERO", description: "Post Processing Block 2 Zero Crossing Event Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "PPB2INLIMIT", description: "Post Processing Block 2 Within trip limit event enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "PPB3TRIPHI", description: "Post Processing Block 3 Trip High Event Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "PPB3TRIPLO", description: "Post Processing Block 3 Trip Low Event Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "PPB3ZERO", description: "Post Processing Block 3 Zero Crossing Event Enable", size: "1", shift: "10", mask: "0x400" },
			{ name: "PPB3INLIMIT", description: "Post Processing Block 3 Within trip limit event enable", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "EVTINTSEL", description: "ADC Event Interrupt Selection Register", offset: "0x6C",
		bits: [
			{ name: "PPB1TRIPHI", description: "Post Processing Block 1 Trip High Interrupt Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "PPB1TRIPLO", description: "Post Processing Block 1 Trip Low Interrupt Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "PPB1ZERO", description: "Post Processing Block 1 Zero Crossing Interrupt", size: "1", shift: "2", mask: "0x4" },
			{ name: "PPB1INLIMIT", description: "Post Processing Block 1 Within trip limit interrupt", size: "1", shift: "3", mask: "0x8" },
			{ name: "PPB2TRIPHI", description: "Post Processing Block 2 Trip High Interrupt Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "PPB2TRIPLO", description: "Post Processing Block 2 Trip Low Interrupt Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "PPB2ZERO", description: "Post Processing Block 2 Zero Crossing Interrupt", size: "1", shift: "6", mask: "0x40" },
			{ name: "PPB2INLIMIT", description: "Post Processing Block 2 Within trip limit interrupt", size: "1", shift: "7", mask: "0x80" },
			{ name: "PPB3TRIPHI", description: "Post Processing Block 3 Trip High Interrupt Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "PPB3TRIPLO", description: "Post Processing Block 3 Trip Low Interrupt Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "PPB3ZERO", description: "Post Processing Block 3 Zero Crossing Interrupt", size: "1", shift: "10", mask: "0x400" },
			{ name: "PPB3INLIMIT", description: "Post Processing Block 3 Within trip limit interrupt", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "REV", description: "ADC Revision Register", offset: "0x72",
		bits: [
			{ name: "TYPE", description: "ADC Type", size: "8", shift: "0", mask: "0xFF" },
			{ name: "REV", description: "ADC Revision", size: "24", shift: "8", mask: "0xFFFFFF00" },
		]
	},
	{ name: "OFFTRIM", description: "ADC Offset Trim Register 1", offset: "0x74",
		bits: [
			{ name: "OFFTRIM", description: "ADC Offset Trim", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PPB1CONFIG", description: "ADC PPB{#} Config Register", offset: "0x80",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block {#} Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block {#} Two's Complement", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "PPB1OFFCAL", description: "ADC PPB1 Offset Calibration Register", offset: "0x84",
		bits: [
			{ name: "OFFCAL", description: "ADC Post Processing Block Offset Correction", size: "6", shift: "0", mask: "0x3F" },
		]
	},
	{ name: "PPB1OFFREF", description: "ADC PPB1 Offset Reference Register", offset: "0x86",
		bits: [
			{ name: "OFFREF", description: "ADC Post Processing Block 1 Offset Reference", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB1TRIPHI", description: "ADC PPB1 Trip High Register", offset: "0x88",
		bits: [
			{ name: "LIMITHI", description: "ADC Post Processing Block 1 Trip High Limit", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "PPB1TRIPLO", description: "ADC PPB1 Trip Low/Trigger Time Stamp Register", offset: "0x8A",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 1 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "PPB2CONFIG", description: "ADC PPB{#} Config Register", offset: "0x90",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block {#} Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block {#} Two's Complement", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "PPB2OFFCAL", description: "ADC PPB2 Offset Calibration Register", offset: "0x94",
		bits: [
			{ name: "OFFCAL", description: "ADC Post Processing Block Offset Correction", size: "6", shift: "0", mask: "0x3F" },
		]
	},
	{ name: "PPB2OFFREF", description: "ADC PPB2 Offset Reference Register", offset: "0x96",
		bits: [
			{ name: "OFFREF", description: "ADC Post Processing Block 2 Offset Reference", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB2TRIPHI", description: "ADC PPB2 Trip High Register", offset: "0x98",
		bits: [
			{ name: "LIMITHI", description: "ADC Post Processing Block 2 Trip High Limit", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "PPB2TRIPLO", description: "ADC PPB2 Trip Low/Trigger Time Stamp Register", offset: "0x9A",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 2 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "PPB3CONFIG", description: "ADC PPB{#} Config Register", offset: "0xA0",
		bits: [
			{ name: "CONFIG", description: "ADC Post Processing Block {#} Configuration", size: "4", shift: "0", mask: "0xF" },
			{ name: "CBCEN", description: "Cycle By Cycle Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "TWOSCOMPEN", description: "ADC Post Processing Block {#} Two's Complement", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "PPB3OFFCAL", description: "ADC PPB3 Offset Calibration Register", offset: "0xA4",
		bits: [
			{ name: "OFFCAL", description: "ADC Post Processing Block Offset Correction", size: "6", shift: "0", mask: "0x3F" },
		]
	},
	{ name: "PPB3OFFREF", description: "ADC PPB3 Offset Reference Register", offset: "0xA6",
		bits: [
			{ name: "OFFREF", description: "ADC Post Processing Block 3 Offset Reference", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB3TRIPHI", description: "ADC PPB3 Trip High Register", offset: "0xA8",
		bits: [
			{ name: "LIMITHI", description: "ADC Post Processing Block 3 Trip High Limit", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "PPB3TRIPLO", description: "ADC PPB3 Trip Low/Trigger Time Stamp Register", offset: "0xAA",
		bits: [
			{ name: "LIMITLO", description: "ADC Post Processing Block 3 Trip Low Limit", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "INTCYCLE", description: "ADC Early Interrupt Generation Cycle", offset: "0xC0",
		bits: [
			{ name: "DELAY", description: "Delay from ADCSOC fall edge to early interrupt", size: "6", shift: "0", mask: "0x3F" },
		]
	},
	{ name: "INLTRIM1", description: "ADC Linearity Trim 1 Register", offset: "0xC2",
		bits: [
		]
	},
	{ name: "INLTRIM2", description: "ADC Linearity Trim 2 Register", offset: "0xC4",
		bits: [
		]
	},
	{ name: "REV2", description: "ADC Wrapper Revision Register", offset: "0xCE",
		bits: [
			{ name: "WRAPPERTYPE", description: "ADC Wrapper Type", size: "8", shift: "0", mask: "0xFF" },
			{ name: "WRAPPERREV", description: "ADC Wrapper Revision", size: "24", shift: "8", mask: "0xFFFFFF00" },
		]
	},
	{ name: "REP1CTL", description: "ADC Trigger Repeater 1 Control Register", offset: "0xE0",
		bits: [
			{ name: "MODULEBUSY", description: "ADC Trigger Repeater 1 Module Busy", size: "1", shift: "3", mask: "0x8" },
			{ name: "TRIGGEROVF", description: "ADC Trigger Repeater 1 Oversampled Trigger", size: "1", shift: "7", mask: "0x80" },
			{ name: "TRIGGER", description: "ADC Trigger Repeater 1 Trigger Select", size: "5", shift: "8", mask: "0x1F00" },
			{ name: "SYNCINSEL", description: "ADC Trigger Repeater 1 Sync. In Select", size: "3", shift: "16", mask: "0x70000" },
			{ name: "SWSYNC", description: "ADC Trigger Repeater 1 Software Sync.", size: "1", shift: "23", mask: "0x800000" },
		]
	},
	{ name: "REP1N", description: "ADC Trigger Repeater 1 N Select Register", offset: "0xE2",
		bits: [
			{ name: "NSEL", description: "ADC Trigger Repeater 1 Trigger Number Selection", size: "2", shift: "0", mask: "0x3" },
			{ name: "NCOUNT", description: "ADC Trigger Repeater 1 Trigger Counter", size: "3", shift: "16", mask: "0x70000" },
		]
	},
	{ name: "REP1SPREAD", description: "ADC Trigger Repeater 1 Spread Select Register", offset: "0xE6",
		bits: [
			{ name: "SPREAD", description: "ADC Trigger Repeater 1 Spread Delay", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SPREADCOUNT", description: "ADC Trigger Repeater 1 Spread Delay Status", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "REP1FRC", description: "ADC Trigger Repeater 1 Software Force Register", offset: "0xE8",
		bits: [
			{ name: "SWFRC", description: "ADC Trigger Repeater 1 Software Force", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PPB1LIMIT", description: "ADC PPB1Conversion Count Limit Register", offset: "0x100",
		bits: [
			{ name: "LIMIT", description: "Post Processing Block 1 Limit", size: "2", shift: "0", mask: "0x3" },
		]
	},
	{ name: "PPBP1PCOUNT", description: "ADC PPB1 Partial Conversion Count Register", offset: "0x102",
		bits: [
			{ name: "PCOUNT", description: "Post Processing Block 1 Partial Count", size: "3", shift: "0", mask: "0x7" },
		]
	},
	{ name: "PPB1CONFIG2", description: "ADC PPB1 Sum Shift Register", offset: "0x104",
		bits: [
			{ name: "SHIFT", description: "Post Processing Block 1 Right Shift", size: "3", shift: "0", mask: "0x7" },
			{ name: "SYNCINSEL", description: "Post Processing Block 1 Sync. Input Select", size: "3", shift: "4", mask: "0x70" },
			{ name: "SWSYNC", description: "Post Processing Block 1 Software Force Sync.", size: "1", shift: "11", mask: "0x800" },
			{ name: "OSINTSEL", description: "Post Processing Block 1 Interrupt Source Select", size: "1", shift: "12", mask: "0x1000" },
			{ name: "COMPSEL", description: "Post Processing Block 1 Compare Source Select", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "PPB1PSUM", description: "ADC PPB1 Partial Sum Register", offset: "0x106",
		bits: [
			{ name: "PSUM", description: "Post Processing Block 1 Oversampling Partial Sum", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "RESULT0", description: "ADC Result 0 Register", offset: "0x0",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT1", description: "ADC Result 1 Register", offset: "0x1",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT2", description: "ADC Result 2 Register", offset: "0x2",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT3", description: "ADC Result 3 Register", offset: "0x3",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT4", description: "ADC Result 4 Register", offset: "0x4",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT5", description: "ADC Result 5 Register", offset: "0x5",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT6", description: "ADC Result 6 Register", offset: "0x6",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT7", description: "ADC Result 7 Register", offset: "0x7",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT8", description: "ADC Result 8 Register", offset: "0x8",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT9", description: "ADC Result 9 Register", offset: "0x9",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT10", description: "ADC Result 10 Register", offset: "0xA",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT11", description: "ADC Result 11 Register", offset: "0xB",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT12", description: "ADC Result 12 Register", offset: "0xC",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT13", description: "ADC Result 13 Register", offset: "0xD",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT14", description: "ADC Result 14 Register", offset: "0xE",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RESULT15", description: "ADC Result 15 Register", offset: "0xF",
		bits: [
			{ name: "RESULT", description: "ADC Result", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "PPB1RESULT", description: "ADC Post Processing Block 1 Result Register", offset: "0x20",
		bits: [
			{ name: "PPBRESULT", description: "ADC Post Processing Block Result", size: "13", shift: "0", mask: "0x1FFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "19", shift: "13", mask: "0xFFFFE000" },
		]
	},
	{ name: "PPB2RESULT", description: "ADC Post Processing Block 2 Result Register", offset: "0x22",
		bits: [
			{ name: "PPBRESULT", description: "ADC Post Processing Block Result", size: "13", shift: "0", mask: "0x1FFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "19", shift: "13", mask: "0xFFFFE000" },
		]
	},
	{ name: "PPB3RESULT", description: "ADC Post Processing Block 3 Result Register", offset: "0x24",
		bits: [
			{ name: "PPBRESULT", description: "ADC Post Processing Block Result", size: "13", shift: "0", mask: "0x1FFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "19", shift: "13", mask: "0xFFFFE000" },
		]
	},
	{ name: "PPB1SUM", description: "ADC PPB 1 Final Sum Result Register", offset: "0x28",
		bits: [
			{ name: "SUM", description: "Post Processing Block 1 Oversampling Sum", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SIGN", description: "Sign Extended Bits", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "PPB1COUNT", description: "ADC PPB1 Final Conversion Count Register", offset: "0x2A",
		bits: [
			{ name: "COUNT", description: "Post Processing Block 1 Final Count", size: "4", shift: "0", mask: "0xF" },
		]
	},
];
module.exports = {
	ADCRegisters: ADCRegisters,
}
