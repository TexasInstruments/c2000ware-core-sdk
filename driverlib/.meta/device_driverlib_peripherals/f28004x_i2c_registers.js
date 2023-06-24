let I2CRegisters = [
	{ name: "OAR", description: "I2C Own address", offset: "0x0",
		bits: [
			{ name: "OAR", description: "I2C Own address", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "IER", description: "I2C Interrupt Enable", offset: "0x1",
		bits: [
			{ name: "ARBL", description: "Arbitration-lost interrupt enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "NACK", description: "No-acknowledgment interrupt enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "ARDY", description: "Register-access-ready interrupt enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "RRDY", description: "Receive-data-ready interrupt enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "XRDY", description: "Transmit-data-ready interrupt enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "SCD", description: "Stop condition detected interrupt enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "AAS", description: "Addressed as slave interrupt enable", size: "1", shift: "6", mask: "0x40" },
		]
	},
	{ name: "STR", description: "I2C Status", offset: "0x2",
		bits: [
			{ name: "ARBL", description: "Arbitration-lost interrupt flag bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "NACK", description: "No-acknowledgment interrupt flag bit.", size: "1", shift: "1", mask: "0x2" },
			{ name: "ARDY", description: "Register-access-ready interrupt flag bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "RRDY", description: "Receive-data-ready interrupt flag bit.", size: "1", shift: "3", mask: "0x8" },
			{ name: "XRDY", description: "Transmit-data-ready interrupt flag bit.", size: "1", shift: "4", mask: "0x10" },
			{ name: "SCD", description: "Stop condition detected bit.", size: "1", shift: "5", mask: "0x20" },
			{ name: "BYTESENT", description: "Byte transmit over indication", size: "1", shift: "6", mask: "0x40" },
			{ name: "AD0", description: "Address 0 bits", size: "1", shift: "8", mask: "0x100" },
			{ name: "AAS", description: "Addressed-as-slave bit", size: "1", shift: "9", mask: "0x200" },
			{ name: "XSMT", description: "Transmit shift register empty bit.", size: "1", shift: "10", mask: "0x400" },
			{ name: "RSFULL", description: "Receive shift register full bit.", size: "1", shift: "11", mask: "0x800" },
			{ name: "BB", description: "Bus busy bit.", size: "1", shift: "12", mask: "0x1000" },
			{ name: "NACKSNT", description: "NACK sent bit.", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SDIR", description: "Slave direction bit", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "CLKL", description: "I2C Clock low-time divider", offset: "0x3",
		bits: [
		]
	},
	{ name: "CLKH", description: "I2C Clock high-time divider", offset: "0x4",
		bits: [
		]
	},
	{ name: "CNT", description: "I2C Data count", offset: "0x5",
		bits: [
		]
	},
	{ name: "DRR", description: "I2C Data receive", offset: "0x6",
		bits: [
			{ name: "DATA", description: "Receive data", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "SAR", description: "I2C Slave address", offset: "0x7",
		bits: [
			{ name: "SAR", description: "Slave Address", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "DXR", description: "I2C Data Transmit", offset: "0x8",
		bits: [
			{ name: "DATA", description: "Transmit data", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "MDR", description: "I2C Mode", offset: "0x9",
		bits: [
			{ name: "BC", description: "Bit count bits.", size: "3", shift: "0", mask: "0x7" },
			{ name: "FDF", description: "Free Data Format", size: "1", shift: "3", mask: "0x8" },
			{ name: "STB", description: "START Byte Mode", size: "1", shift: "4", mask: "0x10" },
			{ name: "IRS", description: "I2C Module Reset", size: "1", shift: "5", mask: "0x20" },
			{ name: "DLB", description: "Digital Loopback Mode", size: "1", shift: "6", mask: "0x40" },
			{ name: "RM", description: "Repeat Mode", size: "1", shift: "7", mask: "0x80" },
			{ name: "XA", description: "Expanded Address Mode", size: "1", shift: "8", mask: "0x100" },
			{ name: "TRX", description: "Transmitter Mode", size: "1", shift: "9", mask: "0x200" },
			{ name: "MST", description: "Master Mode", size: "1", shift: "10", mask: "0x400" },
			{ name: "STP", description: "STOP Condition", size: "1", shift: "11", mask: "0x800" },
			{ name: "STT", description: "START condition bit", size: "1", shift: "13", mask: "0x2000" },
			{ name: "FREE", description: "Debug Action", size: "1", shift: "14", mask: "0x4000" },
			{ name: "NACKMOD", description: "NACK mode bit", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "ISRC", description: "I2C Interrupt Source", offset: "0xA",
		bits: [
			{ name: "INTCODE", description: "Interrupt code bits.", size: "3", shift: "0", mask: "0x7" },
			{ name: "WRITE_ZEROS", description: "Always write all 0s to this field", size: "4", shift: "8", mask: "0xF00" },
		]
	},
	{ name: "EMDR", description: "I2C Extended Mode", offset: "0xB",
		bits: [
			{ name: "BC", description: "Backwards compatibility mode", size: "1", shift: "0", mask: "0x1" },
			{ name: "FCM", description: "Forward Compatibility for Tx behav in Type1", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PSC", description: "I2C Prescaler", offset: "0xC",
		bits: [
			{ name: "IPSC", description: "I2C Prescaler Divide Down", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "FFTX", description: "I2C FIFO Transmit", offset: "0x20",
		bits: [
			{ name: "TXFFIL", description: "Transmit FIFO Interrupt Level", size: "5", shift: "0", mask: "0x1F" },
			{ name: "TXFFIENA", description: "Transmit FIFO Interrupt Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "TXFFINTCLR", description: "Transmit FIFO Interrupt Flag Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "TXFFINT", description: "Transmit FIFO Interrupt Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "TXFFST", description: "Transmit FIFO Status", size: "5", shift: "8", mask: "0x1F00" },
			{ name: "TXFFRST", description: "Transmit FIFO Reset", size: "1", shift: "13", mask: "0x2000" },
			{ name: "I2CFFEN", description: "Transmit FIFO Enable", size: "1", shift: "14", mask: "0x4000" },
		]
	},
	{ name: "FFRX", description: "I2C FIFO Receive", offset: "0x21",
		bits: [
			{ name: "RXFFIL", description: "Receive FIFO Interrupt Level", size: "5", shift: "0", mask: "0x1F" },
			{ name: "RXFFIENA", description: "Receive FIFO Interrupt Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "RXFFINTCLR", description: "Receive FIFO Interrupt Flag Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "RXFFINT", description: "Receive FIFO Interrupt Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "RXFFST", description: "Receive FIFO Status", size: "5", shift: "8", mask: "0x1F00" },
			{ name: "RXFFRST", description: "Receive FIFO Reset", size: "1", shift: "13", mask: "0x2000" },
		]
	},
];
module.exports = {
	I2CRegisters: I2CRegisters,
}
