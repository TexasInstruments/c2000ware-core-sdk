let PGARegisters = [
	{ name: "CTL", description: "PGA Control Register", offset: "0x0",
		bits: [
			{ name: "PGAEN", description: "PGA Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "FILT_RES_SEL", description: "Filter Resistor Select", size: "3", shift: "1", mask: "0xE" },
			{ name: "GAIN", description: "PGA gain setting", size: "3", shift: "5", mask: "0xE0" },
			{ name: "PGA_OUTENABLE", description: "PGA Output Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "PGA_OUTEN_INTGAIN", description: "PGA Internal Gain Output Enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "CHOP_EXTCTRL", description: "External Chop Signal Control", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "MUXSEL", description: "Mux Selection Register", offset: "0x1",
		bits: [
			{ name: "PMUXSEL", description: "Positive Input Mux Select", size: "2", shift: "0", mask: "0x3" },
			{ name: "NMUXSEL", description: "Negative Input Mux Select", size: "2", shift: "4", mask: "0x30" },
			{ name: "MMUXSEL", description: "M Mux Select", size: "2", shift: "8", mask: "0x300" },
			{ name: "PGA_FBONPIN", description: "Connect PGAOUT to PGA_INM", size: "1", shift: "12", mask: "0x1000" },
			{ name: "PGA_CHOP", description: "Chopper Mode Control", size: "2", shift: "13", mask: "0x6000" },
		]
	},
	{ name: "OFFSETTRIM", description: "Offset Trim Register", offset: "0x2",
		bits: [
			{ name: "PGA_OFFSETTRIMN", description: "OFFSET TRIM value for i/p NMOS pair", size: "8", shift: "0", mask: "0xFF" },
			{ name: "PGA_OFFSETTRIMP", description: "OFFSET TRIM value for i/p PMOS pair", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "TYPE", description: "PGA Type Register", offset: "0x5",
		bits: [
			{ name: "REV", description: "PGA Revision Field", size: "8", shift: "0", mask: "0xFF" },
			{ name: "TYPE", description: "PGA Type Field", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "LOCK", description: "PGA Lock Register", offset: "0x6",
		bits: [
			{ name: "PGACTL", description: "Lock bit for PGACTL.", size: "1", shift: "0", mask: "0x1" },
			{ name: "MUXSEL", description: "Lock bit for MUXSEL", size: "1", shift: "1", mask: "0x2" },
			{ name: "OFFSETTRIM", description: "Lock bit for OFFSET TRIM", size: "1", shift: "2", mask: "0x4" },
			{ name: "PGATMCTL", description: "Lock but for PGATMCTL", size: "1", shift: "3", mask: "0x8" },
		]
	},
];
module.exports = {
	PGARegisters: PGARegisters,
}
