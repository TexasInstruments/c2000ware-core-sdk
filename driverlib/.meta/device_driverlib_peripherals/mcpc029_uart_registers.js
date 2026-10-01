let UARTRegisters = [
	{ name: "DR", description: "UART Data", offset: "0x0",
		bits: [
			{ name: "DATA", description: "Data Transmitted or Received", size: "8", shift: "0", mask: "0xFF" },
			{ name: "FE", description: "UART Framing Error", size: "1", shift: "8", mask: "0x100" },
			{ name: "PE", description: "UART Parity Error", size: "1", shift: "9", mask: "0x200" },
			{ name: "BE", description: "UART Break Error", size: "1", shift: "10", mask: "0x400" },
			{ name: "OE", description: "UART Overrun Error", size: "1", shift: "11", mask: "0x800" },
		]
	},
	{ name: "RSR", description: "UART Receive Status/Error Clear", offset: "0x2",
		bits: [
			{ name: "FE", description: "UART Framing Error", size: "1", shift: "0", mask: "0x1" },
			{ name: "PE", description: "UART Parity Error", size: "1", shift: "1", mask: "0x2" },
			{ name: "BE", description: "UART Break Error", size: "1", shift: "2", mask: "0x4" },
			{ name: "OE", description: "UART Overrun Error", size: "1", shift: "3", mask: "0x8" },
		]
	},
	{ name: "FR", description: "UART Flag", offset: "0xC",
		bits: [
			{ name: "BUSY", description: "UART Busy", size: "1", shift: "3", mask: "0x8" },
			{ name: "RXFE", description: "UART Receive FIFO Empty", size: "1", shift: "4", mask: "0x10" },
			{ name: "TXFF", description: "UART Transmit FIFO Full", size: "1", shift: "5", mask: "0x20" },
			{ name: "RXFF", description: "UART Receive FIFO Full", size: "1", shift: "6", mask: "0x40" },
			{ name: "TXFE", description: "UART Transmit FIFO Empty", size: "1", shift: "7", mask: "0x80" },
			{ name: "RXFIFOLVL", description: "UART Receive FIFO Level", size: "5", shift: "16", mask: "0x1F0000" },
			{ name: "TXFIFOLVL", description: "UART Transmit FIFO Level", size: "5", shift: "24", mask: "0x1F000000" },
		]
	},
	{ name: "ILPR", description: "UART IrDA Low-Power Register", offset: "0x10",
		bits: [
			{ name: "ILPDVSR", description: "IrDA Low-Power Divisor", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "IBRD", description: "UART Integer Baud-Rate Divisor", offset: "0x12",
		bits: [
			{ name: "DIVINT", description: "Integer Baud-Rate Divisor", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "FBRD", description: "UART Fractional Baud-Rate Divisor", offset: "0x14",
		bits: [
			{ name: "DIVFRAC", description: "Fractional Baud-Rate Divisor", size: "6", shift: "0", mask: "0x3F" },
		]
	},
	{ name: "LCRH", description: "UART Line Control", offset: "0x16",
		bits: [
			{ name: "BRK", description: "UART Send Break", size: "1", shift: "0", mask: "0x1" },
			{ name: "PEN", description: "UART Parity Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "EPS", description: "UART Even Parity Select", size: "1", shift: "2", mask: "0x4" },
			{ name: "STP2", description: "UART Two Stop Bits Select", size: "1", shift: "3", mask: "0x8" },
			{ name: "FEN", description: "UART Enable FIFOs", size: "1", shift: "4", mask: "0x10" },
			{ name: "WLEN", description: "UART Word Length", size: "2", shift: "5", mask: "0x60" },
			{ name: "SPS", description: "UART Stick Parity Select", size: "1", shift: "7", mask: "0x80" },
		]
	},
	{ name: "CTL", description: "UART Control", offset: "0x18",
		bits: [
			{ name: "UARTEN", description: "UART Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "SIREN", description: "UART SIR Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "SIRLP", description: "UART SIR Low-Power Mode", size: "1", shift: "2", mask: "0x4" },
			{ name: "EOT", description: "End of Transmission", size: "1", shift: "4", mask: "0x10" },
			{ name: "HSE", description: "High-Speed Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "LBE", description: "UART Loop Back Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "TXE", description: "UART Transmit Enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "RXE", description: "UART Receive Enable", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "IFLS", description: "UART Interrupt FIFO Level Select", offset: "0x1A",
		bits: [
			{ name: "TXIFLSEL", description: "UART Transmit Interrupt FIFO Level Select", size: "3", shift: "0", mask: "0x7" },
			{ name: "RXIFLSEL", description: "UART Receive Interrupt FIFO Level Select", size: "3", shift: "3", mask: "0x38" },
			{ name: "TXIFLSEL_FINE", description: "UART Transmit Interrupt Fine-grained FIFO Level", size: "4", shift: "8", mask: "0xF00" },
			{ name: "RXIFLSEL_FINE", description: "UART Receive Interrupt Fine-grained FIFO Level", size: "4", shift: "16", mask: "0xF0000" },
		]
	},
	{ name: "IM", description: "UART Interrupt Mask", offset: "0x1C",
		bits: [
			{ name: "RXIM", description: "UART Receive Interrupt Mask", size: "1", shift: "4", mask: "0x10" },
			{ name: "TXIM", description: "UART Transmit Interrupt Mask", size: "1", shift: "5", mask: "0x20" },
			{ name: "RTIM", description: "UART Receive Time-Out Interrupt Mask", size: "1", shift: "6", mask: "0x40" },
			{ name: "FEIM", description: "UART Framing Error Interrupt Mask", size: "1", shift: "7", mask: "0x80" },
			{ name: "PEIM", description: "UART Parity Error Interrupt Mask", size: "1", shift: "8", mask: "0x100" },
			{ name: "BEIM", description: "UART Break Error Interrupt Mask", size: "1", shift: "9", mask: "0x200" },
			{ name: "OEIM", description: "UART Overrun Error Interrupt Mask", size: "1", shift: "10", mask: "0x400" },
			{ name: "9BITIM", description: "9-Bit Mode Interrupt Mask", size: "1", shift: "12", mask: "0x1000" },
			{ name: "DMARXIM", description: "Receive DMA Interrupt Mask", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DMATXIM", description: "Transmit DMA Interrupt Mask", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "RIS", description: "UART Raw Interrupt Status", offset: "0x1E",
		bits: [
			{ name: "RXRIS", description: "UART Receive Raw Interrupt Status", size: "1", shift: "4", mask: "0x10" },
			{ name: "TXRIS", description: "UART Transmit Raw Interrupt Status", size: "1", shift: "5", mask: "0x20" },
			{ name: "RTRIS", description: "UART Receive Time-Out Raw Interrupt Status", size: "1", shift: "6", mask: "0x40" },
			{ name: "FERIS", description: "UART Framing Error Raw Interrupt Status", size: "1", shift: "7", mask: "0x80" },
			{ name: "PERIS", description: "UART Parity Error Raw Interrupt Status", size: "1", shift: "8", mask: "0x100" },
			{ name: "BERIS", description: "UART Break Error Raw Interrupt Status", size: "1", shift: "9", mask: "0x200" },
			{ name: "OERIS", description: "UART Overrun Error Raw Interrupt Status", size: "1", shift: "10", mask: "0x400" },
			{ name: "9BITRIS", description: "9-Bit Mode Raw Interrupt Status", size: "1", shift: "12", mask: "0x1000" },
			{ name: "DMARXRIS", description: "Receive DMA Raw Interrupt Status", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DMATXRIS", description: "Transmit DMA Raw Interrupt Status", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "MIS", description: "UART Masked Interrupt Status", offset: "0x20",
		bits: [
			{ name: "RXMIS", description: "UART Receive Masked Interrupt Status", size: "1", shift: "4", mask: "0x10" },
			{ name: "TXMIS", description: "UART Transmit Masked Interrupt Status", size: "1", shift: "5", mask: "0x20" },
			{ name: "RTMIS", description: "UART Receive Time-Out Masked Interrupt Status", size: "1", shift: "6", mask: "0x40" },
			{ name: "FEMIS", description: "UART Framing Error Masked Interrupt Status", size: "1", shift: "7", mask: "0x80" },
			{ name: "PEMIS", description: "UART Parity Error Masked Interrupt Status", size: "1", shift: "8", mask: "0x100" },
			{ name: "BEMIS", description: "UART Break Error Masked Interrupt Status", size: "1", shift: "9", mask: "0x200" },
			{ name: "OEMIS", description: "UART Overrun Error Masked Interrupt Status", size: "1", shift: "10", mask: "0x400" },
			{ name: "9BITMIS", description: "9-Bit Mode Masked Interrupt Status", size: "1", shift: "12", mask: "0x1000" },
			{ name: "DMARXMIS", description: "Receive DMA Masked Interrupt Status", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DMATXMIS", description: "Transmit DMA Masked Interrupt Status", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "ICR", description: "UART Interrupt Clear", offset: "0x22",
		bits: [
			{ name: "RXIC", description: "Receive Interrupt Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "TXIC", description: "Transmit Interrupt Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "RTIC", description: "Receive Time-Out Interrupt Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "FEIC", description: "Framing Error Interrupt Clear", size: "1", shift: "7", mask: "0x80" },
			{ name: "PEIC", description: "Parity Error Interrupt Clear", size: "1", shift: "8", mask: "0x100" },
			{ name: "BEIC", description: "Break Error Interrupt Clear", size: "1", shift: "9", mask: "0x200" },
			{ name: "OEIC", description: "Overrun Error Interrupt Clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "9BITIC", description: "9-Bit Mode Interrupt Clear", size: "1", shift: "12", mask: "0x1000" },
			{ name: "DMARXIC", description: "Receive DMA Interrupt Clear", size: "1", shift: "16", mask: "0x10000" },
			{ name: "DMATXIC", description: "Transmit DMA Interrupt Clear", size: "1", shift: "17", mask: "0x20000" },
		]
	},
	{ name: "DMACTL", description: "UART DMA Control", offset: "0x24",
		bits: [
			{ name: "RXDMAE", description: "Receive DMA Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "TXDMAE", description: "Transmit DMA Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "DMAERR", description: "DMA on Error", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "GLB_INT_FLG", description: "UART Global Interrupt Flag Register", offset: "0x42",
		bits: [
			{ name: "INT_FLG", description: "Global Interrupt Flag for UART Interrupt", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GLB_INT_CLR", description: "UART Global Interrupt Clear Register", offset: "0x44",
		bits: [
			{ name: "INT_FLG_CLR", description: "Global Interrupt flag clear for UART Interrupt", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "9BITADDR", description: "UART 9-Bit Self Address", offset: "0x52",
		bits: [
			{ name: "ADDR", description: "Self Address for 9-Bit Mode", size: "8", shift: "0", mask: "0xFF" },
			{ name: "9BITEN", description: "Enable 9-Bit Mode", size: "1", shift: "15", mask: "0x8000" },
		]
	},
	{ name: "9BITAMASK", description: "UART 9-Bit Self Address Mask", offset: "0x54",
		bits: [
			{ name: "MASK", description: "Self Address Mask for 9-Bit Mode", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PP", description: "UART Peripheral Properties", offset: "0x7E0",
		bits: [
			{ name: "SC", description: "Smart Card Support", size: "1", shift: "0", mask: "0x1" },
			{ name: "NB", description: "9-Bit Support", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "PERIPHID4", description: "UART Peripheral Identification 4", offset: "0x7E8",
		bits: [
			{ name: "PID4", description: "UART Peripheral ID Register [7:0]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PERIPHID5", description: "UART Peripheral Identification 5", offset: "0x7EA",
		bits: [
			{ name: "PID5", description: "UART Peripheral ID Register [15:8]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PERIPHID6", description: "UART Peripheral Identification 6", offset: "0x7EC",
		bits: [
			{ name: "PID6", description: "UART Peripheral ID Register [23:16]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PERIPHID7", description: "UART Peripheral Identification 7", offset: "0x7EE",
		bits: [
			{ name: "PID7", description: "UART Peripheral ID Register [31:24]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PERIPHID0", description: "UART Peripheral Identification 0", offset: "0x7F0",
		bits: [
			{ name: "PID0", description: "UART Peripheral ID Register [7:0]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PERIPHID1", description: "UART Peripheral Identification 1", offset: "0x7F2",
		bits: [
			{ name: "PID1", description: "UART Peripheral ID Register [15:8]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PERIPHID2", description: "UART Peripheral Identification 2", offset: "0x7F4",
		bits: [
			{ name: "PID2", description: "UART Peripheral ID Register [23:16]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PERIPHID3", description: "UART Peripheral Identification 3", offset: "0x7F6",
		bits: [
			{ name: "PID3", description: "UART Peripheral ID Register [31:24]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PCELLID0", description: "UART PrimeCell Identification 0", offset: "0x7F8",
		bits: [
			{ name: "CID0", description: "UART PrimeCell ID Register [7:0]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PCELLID1", description: "UART PrimeCell Identification 1", offset: "0x7FA",
		bits: [
			{ name: "CID1", description: "UART PrimeCell ID Register [15:8]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PCELLID2", description: "UART PrimeCell Identification 2", offset: "0x7FC",
		bits: [
			{ name: "CID2", description: "UART PrimeCell ID Register [23:16]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PCELLID3", description: "UART PrimeCell Identification 3", offset: "0x7FE",
		bits: [
			{ name: "CID3", description: "UART PrimeCell ID Register [31:24]", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "ECR", description: "UART Error Clear", offset: "0x2",
		bits: [
			{ name: "DATA", description: "Error Clear", size: "8", shift: "0", mask: "0xFF" },
		]
	},
];
module.exports = {
	UARTRegisters: UARTRegisters,
}
