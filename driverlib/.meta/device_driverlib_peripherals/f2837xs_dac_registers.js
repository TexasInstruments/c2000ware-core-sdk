let DACRegisters = [
	{ name: "REV", description: "DAC Revision Register", offset: "0x0",
		bits: [
			{ name: "REV", description: "DAC Revision Register", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "CTL", description: "DAC Control Register", offset: "0x1",
		bits: [
			{ name: "DACREFSEL", description: "DAC Reference Select", size: "1", shift: "0", mask: "0x1" },
			{ name: "LOADMODE", description: "DACVALA Load Mode", size: "1", shift: "2", mask: "0x4" },
			{ name: "SYNCSEL", description: "DAC EPWMSYNCPER Select", size: "4", shift: "4", mask: "0xF0" },
		]
	},
	{ name: "VALA", description: "DAC Value Register - Active", offset: "0x2",
		bits: [
			{ name: "DACVALA", description: "DAC Active Output Code", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "VALS", description: "DAC Value Register - Shadow", offset: "0x3",
		bits: [
			{ name: "DACVALS", description: "DAC Shadow Output Code", size: "12", shift: "0", mask: "0xFFF" },
		]
	},
	{ name: "OUTEN", description: "DAC Output Enable Register", offset: "0x4",
		bits: [
			{ name: "DACOUTEN", description: "DAC Output Code", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "LOCK", description: "DAC Lock Register", offset: "0x5",
		bits: [
			{ name: "DACCTL", description: "DAC Control Register Lock", size: "1", shift: "0", mask: "0x1" },
			{ name: "DACVAL", description: "DAC Value Register Lock", size: "1", shift: "1", mask: "0x2" },
			{ name: "DACOUTEN", description: "DAC Output Enable Register Lock", size: "1", shift: "2", mask: "0x4" },
			{ name: "KEY", description: "DAC Register Lock Key", size: "4", shift: "12", mask: "0xF000" },
		]
	},
	{ name: "TRIM", description: "DAC Trim Register", offset: "0x6",
		bits: [
			{ name: "OFFSET_TRIM", description: "DAC Offset Trim", size: "8", shift: "0", mask: "0xFF" },
		]
	},
];
module.exports = {
	DACRegisters: DACRegisters,
}
