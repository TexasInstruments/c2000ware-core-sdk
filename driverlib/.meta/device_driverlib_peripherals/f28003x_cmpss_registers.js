let CMPSSRegisters = [
	{ name: "COMPCTL", description: "CMPSS Comparator Control Register", offset: "0x0",
		bits: [
			{ name: "COMPHSOURCE", description: "High Comparator Source Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "COMPHINV", description: "High Comparator Invert Select", size: "1", shift: "1", mask: "0x2" },
			{ name: "CTRIPHSEL", description: "High Comparator Trip Select", size: "2", shift: "2", mask: "0xC" },
			{ name: "CTRIPOUTHSEL", description: "High Comparator Trip Output Select", size: "2", shift: "4", mask: "0x30" },
			{ name: "ASYNCHEN", description: "High Comparator Asynchronous Path Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "COMPLSOURCE", description: "Low Comparator Source Select", size: "1", shift: "8", mask: "0x100" },
			{ name: "COMPLINV", description: "Low Comparator Invert Select", size: "1", shift: "9", mask: "0x200" },
			{ name: "CTRIPLSEL", description: "Low Comparator Trip Select", size: "2", shift: "10", mask: "0xC00" },
			{ name: "CTRIPOUTLSEL", description: "Low Comparator Trip Output Select", size: "2", shift: "12", mask: "0x3000" },
			{ name: "ASYNCLEN", description: "Low Comparator Asynchronous Path Enable", size: "1", shift: "14", mask: "0x4000" },
			{ name: "COMPDACE", description: "Comparator/DAC Enable", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "COMPHYSCTL", description: "CMPSS Comparator Hysteresis Control Register", offset: "0x1",
		bits: [
			{ name: "COMPHYS", description: "Comparator Hysteresis Trim", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "COMPSTS", description: "CMPSS Comparator Status Register", offset: "0x2",
		bits: [
			{ name: "COMPHSTS", description: "High Comparator Status", size: "1", shift: "0", mask: "0x1" },
			{ name: "COMPHLATCH", description: "High Comparator Latched Status", size: "1", shift: "1", mask: "0x2" },
			{ name: "COMPLSTS", description: "Low Comparator Status", size: "1", shift: "8", mask: "0x100" },
			{ name: "COMPLLATCH", description: "Low Comparator Latched Status", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "COMPSTSCLR", description: "CMPSS Comparator Status Clear Register", offset: "0x3",
		bits: [
			{ name: "HLATCHCLR", description: "High Comparator Latched Status Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "HSYNCCLREN", description: "High Comparator EPWMSYNCPER Clear Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "LLATCHCLR", description: "Low Comparator Latched Status Clear", size: "1", shift: "9", mask: "0x200" },
			{ name: "LSYNCCLREN", description: "Low Comparator EPWMSYNCPER Clear Enable", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "COMPDACCTL", description: "CMPSS DAC Control Register", offset: "0x4",
		bits: [
			{ name: "DACSOURCE", description: "DAC Source Control", size: "1", shift: "0", mask: "0x1" },
			{ name: "RAMPSOURCE", description: "Ramp Generator Source Control", size: "4", shift: "1", mask: "0x1E" },
			{ name: "SELREF", description: "DAC Reference Select", size: "1", shift: "5", mask: "0x20" },
			{ name: "RAMPLOADSEL", description: "Ramp Load Select", size: "1", shift: "6", mask: "0x40" },
			{ name: "SWLOADSEL", description: "Software Load Select", size: "1", shift: "7", mask: "0x80" },
			{ name: "BLANKSOURCE", description: "EPWMBLANK Source Select", size: "4", shift: "8", mask: "0xF00" },
			{ name: "BLANKEN", description: "EPWMBLANK Enable", size: "1", shift: "12", mask: "0x1000" },
			{ name: "FREESOFT", description: "Free/Soft Emulation Bits", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "DACHVALS", description: "CMPSS High DAC Value Shadow Register", offset: "0x6",
		bits: [
			{ name: "DACVAL", description: "DAC Value Control", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "DACHVALA", description: "CMPSS High DAC Value Active Register", offset: "0x7",
		bits: [
			{ name: "DACVAL", description: "DAC Value Control", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RAMPMAXREFA", description: "CMPSS Ramp Max Reference Active Register", offset: "0x8",
		bits: [
		]
	},
	{ name: "RAMPMAXREFS", description: "CMPSS Ramp Max Reference Shadow Register", offset: "0xA",
		bits: [
		]
	},
	{ name: "RAMPDECVALA", description: "CMPSS Ramp Decrement Value Active Register", offset: "0xC",
		bits: [
		]
	},
	{ name: "RAMPDECVALS", description: "CMPSS Ramp Decrement Value Shadow Register", offset: "0xE",
		bits: [
		]
	},
	{ name: "RAMPSTS", description: "CMPSS Ramp Status Register", offset: "0x10",
		bits: [
		]
	},
	{ name: "DACLVALS", description: "CMPSS Low DAC Value Shadow Register", offset: "0x12",
		bits: [
			{ name: "DACVAL", description: "DAC Value Control", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "DACLVALA", description: "CMPSS Low DAC Value Active Register", offset: "0x13",
		bits: [
			{ name: "DACVAL", description: "DAC Value Control", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "RAMPDLYA", description: "CMPSS Ramp Delay Active Register", offset: "0x14",
		bits: [
			{ name: "DELAY", description: "Ramp Delay Value", size: "13", shift: "0", mask: "0x1FFF" },
		]
	},
	{ name: "RAMPDLYS", description: "CMPSS Ramp Delay Shadow Register", offset: "0x15",
		bits: [
			{ name: "DELAY", description: "Ramp Delay Value", size: "13", shift: "0", mask: "0x1FFF" },
		]
	},
	{ name: "CTRIPLFILCTL", description: "CTRIPL Filter Control Register", offset: "0x16",
		bits: [
			{ name: "SAMPWIN", description: "Sample Window", size: "5", shift: "4", mask: "0x1F0" },
			{ name: "THRESH", description: "Majority Voting Threshold", size: "5", shift: "9", mask: "0x3E00" },
			{ name: "FILINIT", description: "Filter Initialization Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CTRIPLFILCLKCTL", description: "CTRIPL Filter Clock Control Register", offset: "0x17",
		bits: [
		]
	},
	{ name: "CTRIPHFILCTL", description: "CTRIPH Filter Control Register", offset: "0x18",
		bits: [
			{ name: "SAMPWIN", description: "Sample Window", size: "5", shift: "4", mask: "0x1F0" },
			{ name: "THRESH", description: "Majority Voting Threshold", size: "5", shift: "9", mask: "0x3E00" },
			{ name: "FILINIT", description: "Filter Initialization Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CTRIPHFILCLKCTL", description: "CTRIPH Filter Clock Control Register", offset: "0x19",
		bits: [
		]
	},
	{ name: "COMPLOCK", description: "CMPSS Lock Register", offset: "0x1A",
		bits: [
			{ name: "COMPCTL", description: "COMPCTL Lock", size: "1", shift: "0", mask: "0x1" },
			{ name: "COMPHYSCTL", description: "COMPHYSCTL Lock", size: "1", shift: "1", mask: "0x2" },
			{ name: "DACCTL", description: "DACCTL Lock", size: "1", shift: "2", mask: "0x4" },
			{ name: "CTRIP", description: "CTRIP Lock", size: "1", shift: "3", mask: "0x8" },
		]
	},
];
module.exports = {
	CMPSSRegisters: CMPSSRegisters,
}
