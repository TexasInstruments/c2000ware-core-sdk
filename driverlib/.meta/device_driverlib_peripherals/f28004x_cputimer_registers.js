let CPUTIMERRegisters = [
	{ name: "TIM", description: "CPU-Timer, Counter Register", offset: "ER_O_TIM    0x0",
		bits: [
			{ name: "LSW", description: "CPU-Timer Counter Registers", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "MSW", description: "CPU-Timer Counter Registers High", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "PRD", description: "CPU-Timer, Period Register", offset: "0x2",
		bits: [
			{ name: "LSW", description: "CPU-Timer Period Registers", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "MSW", description: "CPU-Timer Period Registers High", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "TCR", description: "CPU-Timer, Control Register", offset: "0x4",
		bits: [
			{ name: "TSS", description: "CPU-Timer stop status bit.", size: "1", shift: "4", mask: "0x10" },
			{ name: "TRB", description: "Timer reload", size: "1", shift: "5", mask: "0x20" },
			{ name: "SOFT", description: "Emulation modes", size: "1", shift: "10", mask: "0x400" },
			{ name: "FREE", description: "Emulation modes", size: "1", shift: "11", mask: "0x800" },
			{ name: "TIE", description: "CPU-Timer Interrupt Enable.", size: "1", shift: "14", mask: "0x4000" },
			{ name: "TIF", description: "CPU-Timer Interrupt Flag.", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "TPR", description: "CPU-Timer, Prescale Register", offset: "0x6",
		bits: [
			{ name: "TDDR", description: "CPU-Timer Divide-Down.", size: "8", shift: "0", mask: "0xFF" },
			{ name: "PSC", description: "CPU-Timer Prescale Counter.", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
	{ name: "TPRH", description: "CPU-Timer, Prescale Register High", offset: "0x7",
		bits: [
			{ name: "TDDRH", description: "CPU-Timer Divide-Down.", size: "8", shift: "0", mask: "0xFF" },
			{ name: "PSCH", description: "CPU-Timer Prescale Counter.", size: "8", shift: "8", mask: "0xFF00" },
		]
	},
];
module.exports = {
	CPUTIMERRegisters: CPUTIMERRegisters,
}
