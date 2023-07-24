let FLASHRegisters = [
	{ name: "FRDCNTL", description: "Flash Read Control Register", offset: "0x0",
		bits: [
			{ name: "RWAIT", description: "Random Read Waitstate", size: "4", shift: "8", mask: "0xF00" },
		]
	},
	{ name: "FLPROT", description: "Flash program/erase protect register", offset: "0x4",
		bits: [
			{ name: "FLWEPROT", description: "Flash write/erase protect bit.", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "FRD_INTF_CTRL", description: "Flash Read Interface Control Register", offset: "0x180",
		bits: [
			{ name: "PREFETCH_EN", description: "Prefetch Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "DATA_CACHE_EN", description: "Data Cache Enable", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "ECC_ENABLE", description: "ECC Enable", offset: "0x0",
		bits: [
			{ name: "ENABLE", description: "Enable ECC", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "FECC_CTRL", description: "ECC Control", offset: "0x20",
		bits: [
			{ name: "ECC_TEST_EN", description: "Enable ECC Test Logic", size: "2", shift: "0", mask: "0x3" },
		]
	},
];
module.exports = {
	FLASHRegisters: FLASHRegisters,
}
