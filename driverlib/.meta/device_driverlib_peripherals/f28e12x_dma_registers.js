let DMARegisters = [
	{ name: "CTRL", description: "DMA Control Register", offset: "0x0",
		bits: [
			{ name: "HARDRESET", description: "Hard Reset Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "PRIORITYRESET", description: "Priority Reset Bit", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "DEBUGCTRL", description: "Debug Control Register", offset: "0x1",
		bits: [
			{ name: "FREE", description: "Debug Mode Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "PRIORITYCTRL1", description: "Priority Control 1 Register", offset: "0x4",
		bits: [
			{ name: "CH1PRIORITY", description: "Ch1 Priority Bit", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PRIORITYSTAT", description: "Priority Status Register", offset: "0x6",
		bits: [
			{ name: "ACTIVESTS", description: "Active Channel Status Bits", size: "3", shift: "0", mask: "0x7" },
			{ name: "ACTIVESTS_SHADOW", description: "Active Channel Status Shadow Bits", size: "3", shift: "4", mask: "0x70" },
		]
	},
	{ name: "MODE", description: "Mode Register", offset: "0x0",
		bits: [
			{ name: "PERINTSEL", description: "Peripheral Interrupt and Sync Select", size: "5", shift: "0", mask: "0x1F" },
			{ name: "OVRINTE", description: "Overflow Interrupt Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "PERINTE", description: "Peripheral Interrupt Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "CHINTMODE", description: "Channel Interrupt Mode", size: "1", shift: "9", mask: "0x200" },
			{ name: "ONESHOT", description: "One Shot Mode Bit", size: "1", shift: "10", mask: "0x400" },
			{ name: "CONTINUOUS", description: "Continuous Mode Bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "DATASIZE", description: "Data Size Mode Bit", size: "1", shift: "14", mask: "0x4000" },
			{ name: "CHINTE", description: "Channel Interrupt Enable Bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "CONTROL", description: "Control Register", offset: "0x1",
		bits: [
			{ name: "RUN", description: "Run Bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "HALT", description: "Halt Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "SOFTRESET", description: "Soft Reset Bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "PERINTFRC", description: "Interrupt Force Bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "PERINTCLR", description: "Interrupt Clear Bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "ERRCLR", description: "Error Clear Bit", size: "1", shift: "7", mask: "0x80" },
			{ name: "PERINTFLG", description: "Interrupt Flag Bit", size: "1", shift: "8", mask: "0x100" },
			{ name: "TRANSFERSTS", description: "Transfer Status Bit", size: "1", shift: "11", mask: "0x800" },
			{ name: "BURSTSTS", description: "Burst Status Bit", size: "1", shift: "12", mask: "0x1000" },
			{ name: "RUNSTS", description: "Run Status Bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "OVRFLG", description: "Overflow Flag Bit", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "BURST_SIZE", description: "Burst Size Register", offset: "0x2",
		bits: [
			{ name: "BURSTSIZE", description: "Burst Transfer Size", size: "5", shift: "0", mask: "0x1F" },
		]
	},
	{ name: "BURST_COUNT", description: "Burst Count Register", offset: "0x3",
		bits: [
			{ name: "BURSTCOUNT", description: "Burst Transfer Size", size: "5", shift: "0", mask: "0x1F" },
		]
	},
	{ name: "SRC_BURST_STEP", description: "Source Burst Step Register", offset: "0x4",
		bits: [
		]
	},
	{ name: "DST_BURST_STEP", description: "Destination Burst Step Register", offset: "0x5",
		bits: [
		]
	},
	{ name: "TRANSFER_SIZE", description: "Transfer Size Register", offset: "0x6",
		bits: [
			{ name: "TRANSFERSIZE", description: "These bits specify the number of bursts to", size: "9", shift: "0", mask: "0x1FF" },
		]
	},
	{ name: "TRANSFER_COUNT", description: "Transfer Count Register", offset: "0x7",
		bits: [
			{ name: "TRANSFERCOUNT", description: "These bits specify the current transfer", size: "9", shift: "0", mask: "0x1FF" },
		]
	},
	{ name: "SRC_TRANSFER_STEP", description: "Source Transfer Step Register", offset: "0x8",
		bits: [
		]
	},
	{ name: "DST_TRANSFER_STEP", description: "Destination Transfer Step Register", offset: "0x9",
		bits: [
		]
	},
	{ name: "SRC_WRAP_SIZE", description: "Source Wrap Size Register", offset: "0xA",
		bits: [
			{ name: "WRAPSIZE", description: "Number of bursts to transfer before wrapping", size: "9", shift: "0", mask: "0x1FF" },
		]
	},
	{ name: "SRC_WRAP_COUNT", description: "Source Wrap Count Register", offset: "0xB",
		bits: [
			{ name: "WRAPSIZE", description: "These bits indicate the current wrap counter", size: "9", shift: "0", mask: "0x1FF" },
		]
	},
	{ name: "SRC_WRAP_STEP", description: "Source Wrap Step Register", offset: "0xC",
		bits: [
		]
	},
	{ name: "DST_WRAP_SIZE", description: "Destination Wrap Size Register", offset: "0xD",
		bits: [
			{ name: "WRAPSIZE", description: "Number of bursts to transfer before wrapping", size: "9", shift: "0", mask: "0x1FF" },
		]
	},
	{ name: "DST_WRAP_COUNT", description: "Destination Wrap Count Register", offset: "0xE",
		bits: [
			{ name: "WRAPSIZE", description: "These bits indicate the current wrap counter", size: "9", shift: "0", mask: "0x1FF" },
		]
	},
	{ name: "DST_WRAP_STEP", description: "Destination Wrap Step Register", offset: "0xF",
		bits: [
		]
	},
	{ name: "SRC_BEG_ADDR_SHADOW", description: "Source Begin Address Shadow Register", offset: "0x10",
		bits: [
		]
	},
	{ name: "SRC_ADDR_SHADOW", description: "Source Address Shadow Register", offset: "0x12",
		bits: [
		]
	},
	{ name: "SRC_BEG_ADDR_ACTIVE", description: "Source Begin Address Active Register", offset: "0x14",
		bits: [
		]
	},
	{ name: "SRC_ADDR_ACTIVE", description: "Source Address Active Register", offset: "0x16",
		bits: [
		]
	},
	{ name: "DST_BEG_ADDR_SHADOW", description: "Destination Begin Address Shadow Register", offset: "0x18",
		bits: [
		]
	},
	{ name: "DST_ADDR_SHADOW", description: "Destination Address Shadow Register", offset: "0x1A",
		bits: [
		]
	},
	{ name: "DST_BEG_ADDR_ACTIVE", description: "Destination Begin Address Active Register", offset: "0x1C",
		bits: [
		]
	},
	{ name: "DST_ADDR_ACTIVE", description: "Destination Address Active Register", offset: "0x1E",
		bits: [
		]
	},
];
module.exports = {
	DMARegisters: DMARegisters,
}
