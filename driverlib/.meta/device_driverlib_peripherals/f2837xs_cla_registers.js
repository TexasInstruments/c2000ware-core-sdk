let CLARegisters = [
	{ name: "MVECT1", description: "Task Interrupt Vector", offset: "0x0",
		bits: [
		]
	},
	{ name: "MVECT2", description: "Task Interrupt Vector", offset: "0x1",
		bits: [
		]
	},
	{ name: "MVECT3", description: "Task Interrupt Vector", offset: "0x2",
		bits: [
		]
	},
	{ name: "MVECT4", description: "Task Interrupt Vector", offset: "0x3",
		bits: [
		]
	},
	{ name: "MVECT5", description: "Task Interrupt Vector", offset: "0x4",
		bits: [
		]
	},
	{ name: "MVECT6", description: "Task Interrupt Vector", offset: "0x5",
		bits: [
		]
	},
	{ name: "MVECT7", description: "Task Interrupt Vector", offset: "0x6",
		bits: [
		]
	},
	{ name: "MVECT8", description: "Task Interrupt Vector", offset: "0x7",
		bits: [
		]
	},
	{ name: "MCTL", description: "Control Register", offset: "0x10",
		bits: [
			{ name: "HARDRESET", description: "Hard Reset", size: "1", shift: "0", mask: "0x1" },
			{ name: "SOFTRESET", description: "Soft Reset", size: "1", shift: "1", mask: "0x2" },
			{ name: "IACKE", description: "IACK enable", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MIFR", description: "Interrupt Flag Register", offset: "0x20",
		bits: [
			{ name: "INT1", description: "Task 1 Interrupt Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT2", description: "Task 2 Interrupt Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "INT3", description: "Task 3 Interrupt Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "INT4", description: "Task 4 Interrupt Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "INT5", description: "Task 5 Interrupt Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "INT6", description: "Task 6 Interrupt Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT7", description: "Task 7 Interrupt Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT8", description: "Task 8 Interrupt Flag", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MIOVF", description: "Interrupt Overflow Flag Register", offset: "0x21",
		bits: [
			{ name: "INT1", description: "Task 1 Interrupt Overflow Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT2", description: "Task 2 Interrupt Overflow Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "INT3", description: "Task 3 Interrupt Overflow Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "INT4", description: "Task 4 Interrupt Overflow Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "INT5", description: "Task 5 Interrupt Overflow Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "INT6", description: "Task 6 Interrupt Overflow Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT7", description: "Task 7 Interrupt Overflow Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT8", description: "Task 8 Interrupt Overflow Flag", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MIFRC", description: "Interrupt Force Register", offset: "0x22",
		bits: [
			{ name: "INT1", description: "Task 1 Interrupt Force", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT2", description: "Task 2 Interrupt Force", size: "1", shift: "1", mask: "0x2" },
			{ name: "INT3", description: "Task 3 Interrupt Force", size: "1", shift: "2", mask: "0x4" },
			{ name: "INT4", description: "Task 4 Interrupt Force", size: "1", shift: "3", mask: "0x8" },
			{ name: "INT5", description: "Task 5 Interrupt Force", size: "1", shift: "4", mask: "0x10" },
			{ name: "INT6", description: "Task 6 Interrupt Force", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT7", description: "Task 7 Interrupt Force", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT8", description: "Task 8 Interrupt Force", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MICLR", description: "Interrupt Flag Clear Register", offset: "0x23",
		bits: [
			{ name: "INT1", description: "Task 1 Interrupt Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT2", description: "Task 2 Interrupt Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "INT3", description: "Task 3 Interrupt Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "INT4", description: "Task 4 Interrupt Flag Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "INT5", description: "Task 5 Interrupt Flag Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "INT6", description: "Task 6 Interrupt Flag Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT7", description: "Task 7 Interrupt Flag Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT8", description: "Task 8 Interrupt Flag Clear", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MICLROVF", description: "Interrupt Overflow Flag Clear Register", offset: "0x24",
		bits: [
			{ name: "INT1", description: "Task 1 Interrupt Overflow Flag Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT2", description: "Task 2 Interrupt Overflow Flag Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "INT3", description: "Task 3 Interrupt Overflow Flag Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "INT4", description: "Task 4 Interrupt Overflow Flag Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "INT5", description: "Task 5 Interrupt Overflow Flag Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "INT6", description: "Task 6 Interrupt Overflow Flag Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT7", description: "Task 7 Interrupt Overflow Flag Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT8", description: "Task 8 Interrupt Overflow Flag Clear", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MIER", description: "Interrupt Enable Register", offset: "0x25",
		bits: [
			{ name: "INT1", description: "Task 1 Interrupt Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT2", description: "Task 2 Interrupt Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "INT3", description: "Task 3 Interrupt Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "INT4", description: "Task 4 Interrupt Enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "INT5", description: "Task 5 Interrupt Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "INT6", description: "Task 6 Interrupt Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT7", description: "Task 7 Interrupt Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT8", description: "Task 8 Interrupt Enable", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MIRUN", description: "Interrupt Run Status Register", offset: "0x26",
		bits: [
			{ name: "INT1", description: "Task 1 Run Status", size: "1", shift: "0", mask: "0x1" },
			{ name: "INT2", description: "Task 2 Run Status", size: "1", shift: "1", mask: "0x2" },
			{ name: "INT3", description: "Task 3 Run Status", size: "1", shift: "2", mask: "0x4" },
			{ name: "INT4", description: "Task 4 Run Status", size: "1", shift: "3", mask: "0x8" },
			{ name: "INT5", description: "Task 5 Run Status", size: "1", shift: "4", mask: "0x10" },
			{ name: "INT6", description: "Task 6 Run Status", size: "1", shift: "5", mask: "0x20" },
			{ name: "INT7", description: "Task 7 Run Status", size: "1", shift: "6", mask: "0x40" },
			{ name: "INT8", description: "Task 8 Run Status", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "MPC", description: "CLA Program Counter", offset: "0x28",
		bits: [
		]
	},
	{ name: "MAR0", description: "CLA Auxiliary Register 0", offset: "0x2A",
		bits: [
		]
	},
	{ name: "MAR1", description: "CLA Auxiliary Register 1", offset: "0x2B",
		bits: [
		]
	},
	{ name: "MSTF", description: "CLA Floating-Point Status Register", offset: "0x2E",
		bits: [
			{ name: "LVF", description: "Latched Overflow Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "LUF", description: "Latched Underflow Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "NF", description: "Negative Float Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "ZF", description: "Zero Float Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "TF", description: "Test Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "RNDF32", description: "Round 32-bit Floating-Point Mode", size: "1", shift: "9", mask: "0x200" },
			{ name: "MEALLOW", description: "MEALLOW Status", size: "1", shift: "11", mask: "0x800" },
			{ name: "RPC", description: "Return PC", size: "16", shift: "12", mask: "0xFFFF000" },
		]
	},
	{ name: "MR0", description: "CLA Floating-Point Result Register 0", offset: "0x30",
		bits: [
		]
	},
	{ name: "MR1", description: "CLA Floating-Point Result Register 1", offset: "0x34",
		bits: [
		]
	},
	{ name: "MR2", description: "CLA Floating-Point Result Register 2", offset: "0x38",
		bits: [
		]
	},
	{ name: "MR3", description: "CLA Floating-Point Result Register 3", offset: "0x3C",
		bits: [
		]
	},
	{ name: "SOFTINTEN", description: "CLA Software Interrupt Enable Register", offset: "0x0",
		bits: [
			{ name: "TASK1", description: "Configure Software Interrupt or End of Task interrupt.", size: "1", shift: "0", mask: "0x1" },
			{ name: "TASK2", description: "Configure Software Interrupt or End of Task interrupt.", size: "1", shift: "1", mask: "0x2" },
			{ name: "TASK3", description: "Configure Software Interrupt or End of Task interrupt.", size: "1", shift: "2", mask: "0x4" },
			{ name: "TASK4", description: "Configure Software Interrupt or End of Task interrupt.", size: "1", shift: "3", mask: "0x8" },
			{ name: "TASK5", description: "Configure Software Interrupt or End of Task interrupt.", size: "1", shift: "4", mask: "0x10" },
			{ name: "TASK6", description: "Configure Software Interrupt or End of Task interrupt.", size: "1", shift: "5", mask: "0x20" },
			{ name: "TASK7", description: "Configure Software Interrupt or End of Task interrupt.", size: "1", shift: "6", mask: "0x40" },
			{ name: "TASK8", description: "Configure Software Interrupt or End of Task interrupt.", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "SOFTINTFRC", description: "CLA Software Interrupt Force Register", offset: "0x2",
		bits: [
			{ name: "TASK1", description: "Force CLA software interrupt for the corresponding task.", size: "1", shift: "0", mask: "0x1" },
			{ name: "TASK2", description: "Force CLA software interrupt for the corresponding task.", size: "1", shift: "1", mask: "0x2" },
			{ name: "TASK3", description: "Force CLA software interrupt for the corresponding task.", size: "1", shift: "2", mask: "0x4" },
			{ name: "TASK4", description: "Force CLA software interrupt for the corresponding task.", size: "1", shift: "3", mask: "0x8" },
			{ name: "TASK5", description: "Force CLA software interrupt for the corresponding task.", size: "1", shift: "4", mask: "0x10" },
			{ name: "TASK6", description: "Force CLA software interrupt for the corresponding task.", size: "1", shift: "5", mask: "0x20" },
			{ name: "TASK7", description: "Force CLA software interrupt for the corresponding task.", size: "1", shift: "6", mask: "0x40" },
			{ name: "TASK8", description: "Force CLA software interrupt for the corresponding task.", size: "1", shift: "7", mask: "0x80" },
		]
	},
];
module.exports = {
	CLARegisters: CLARegisters,
}
