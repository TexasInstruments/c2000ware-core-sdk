let PGARegisters = [
	{ name: "CTL", description: "PGA Control Register", offset: "0x0",
		bits: [
			{ name: "PGAEN", description: "PGA Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "FILTRESSEL", description: "Filter Resistor Select", size: "4", shift: "1", mask: "0x1E" },
			{ name: "GAIN", description: "PGA gain setting", size: "3", shift: "5", mask: "0xE0" },
		]
	},
	{ name: "LOCK", description: "PGA Lock Register", offset: "0x2",
		bits: [
			{ name: "PGACTL", description: "Lock bit for PGACTL.", size: "1", shift: "0", mask: "0x1" },
			{ name: "PGAGAIN3TRIM", description: "Lock bit for PGAGAIN3TRIM.", size: "1", shift: "2", mask: "0x4" },
			{ name: "PGAGAIN6TRIM", description: "Lock bit for PGAGAIN6TRIM.", size: "1", shift: "3", mask: "0x8" },
			{ name: "PGAGAIN12TRIM", description: "Lock bit for PGAGAIN12TRIM.", size: "1", shift: "4", mask: "0x10" },
			{ name: "PGAGAIN24TRIM", description: "Lock bit for PGAGAIN24TRIM.", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "GAIN3TRIM", description: "PGA Gain Trim Register for a gain setting of 3", offset: "0x4",
		bits: [
			{ name: "GAINTRIM", description: "Gain TRIM value, when gain setting is 3", size: "8", shift: "0", mask: "0xFF" },
			{ name: "OFFSETTRIM", description: "OFFSET TRIM value, when Gain setting is 3", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "GAIN6TRIM", description: "PGA Gain Trim Register for a gain setting of 6", offset: "0x5",
		bits: [
			{ name: "GAINTRIM", description: "Gain TRIM value, when gain setting is 6", size: "8", shift: "0", mask: "0xFF" },
			{ name: "OFFSETTRIM", description: "OFFSET TRIM value, when Gain setting is 6", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "GAIN12TRIM", description: "PGA Gain Trim Register for a gain setting of 12", offset: "0x6",
		bits: [
			{ name: "GAINTRIM", description: "Gain TRIM value, when gain setting is 12", size: "8", shift: "0", mask: "0xFF" },
			{ name: "OFFSETTRIM", description: "OFFSET TRIM value, when Gain setting is 12", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "GAIN24TRIM", description: "PGA Gain Trim Register for a gain setting of 24", offset: "0x7",
		bits: [
			{ name: "GAINTRIM", description: "Gain TRIM value, when gain setting is 24", size: "8", shift: "0", mask: "0xFF" },
			{ name: "OFFSETTRIM", description: "OFFSET TRIM value, when Gain setting is 24", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "TYPE", description: "PGA Type Register", offset: "0x8",
		bits: [
			{ name: "REV", description: "PGA Revision Field", size: "8", shift: "0", mask: "0xFF" },
			{ name: "TYPE", description: "PGA Type Field", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
];
module.exports = {
	PGARegisters: PGARegisters,
}
