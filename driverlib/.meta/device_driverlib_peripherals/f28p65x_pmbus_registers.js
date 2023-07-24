let PMBUSRegisters = [
	{ name: "PMBCCR", description: "PMBUS CONTROLLER Mode Control Register", offset: "0x0",
		bits: [
			{ name: "RW", description: "RnW bit of the Message", size: "1", shift: "0", mask: "0x1" },
			{ name: "TARGET_ADDR", description: "TARGET Address", size: "7", shift: "1", mask: "0xFE" },
			{ name: "BYTE_COUNT", description: "Number of Bytes Transmitted", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "CMD_ENA", description: "CONTROLLER Command Code Enable", size: "1", shift: "16", mask: "0x10000" },
			{ name: "EXT_CMD", description: "CONTROLLER Extended Command Code Enable", size: "1", shift: "17", mask: "0x20000" },
			{ name: "PEC_ENA", description: "CONTROLLER PEC Processing Enable", size: "1", shift: "18", mask: "0x40000" },
			{ name: "GRP_CMD", description: "CONTROLLER Group Command Message Enable", size: "1", shift: "19", mask: "0x80000" },
			{ name: "PRC_CALL", description: "CONTROLLER Process Call Message Enable", size: "1", shift: "20", mask: "0x100000" },
		]
	},
	{ name: "PMBTXBUF", description: "PMBUS Transmit Buffer", offset: "0x2",
		bits: [
		]
	},
	{ name: "PMBRXBUF", description: "PMBUS Receive buffer", offset: "0x4",
		bits: [
		]
	},
	{ name: "PMBACK", description: "PMBUS Acknowledge Register", offset: "0x6",
		bits: [
			{ name: "ACK", description: "Allows firmware to ack/nack received data", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PMBSTS", description: "PMBUS Status Register", offset: "0x8",
		bits: [
			{ name: "RD_BYTE_COUNT", description: "Number of Data Bytes available in Receive", size: "3", shift: "0", mask: "0x7" },
			{ name: "DATA_READY", description: "Data Ready Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "DATA_REQUEST", description: "Data Request Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "EOM", description: "End of Message Indicator", size: "1", shift: "5", mask: "0x20" },
			{ name: "NACK", description: "Not Acknowledge Flag Status", size: "1", shift: "6", mask: "0x40" },
			{ name: "PEC_VALID", description: "PEC Valid Indicator", size: "1", shift: "7", mask: "0x80" },
			{ name: "CLK_LOW_TIMEOUT", description: "Clock Low Timeout Status", size: "1", shift: "8", mask: "0x100" },
			{ name: "CLK_HIGH_DETECTED", description: "Clock High Detection Status", size: "1", shift: "9", mask: "0x200" },
			{ name: "TARGET_ADDR_READY", description: "TARGET Address Ready", size: "1", shift: "10", mask: "0x400" },
			{ name: "RPT_START", description: "Repeated Start Flag", size: "1", shift: "11", mask: "0x800" },
			{ name: "UNIT_BUSY", description: "PMBus Busy Indicator", size: "1", shift: "12", mask: "0x1000" },
			{ name: "BUS_FREE", description: "PMBus Free Indicator", size: "1", shift: "13", mask: "0x2000" },
			{ name: "LOST_ARB", description: "Lost Arbitration Flag", size: "1", shift: "14", mask: "0x4000" },
			{ name: "CONTROLLER", description: "CONTROLLER Indicator", size: "1", shift: "15", mask: "0x8000" },
			{ name: "ALERT_EDGE", description: "Alert Edge Detection Status", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CONTROL_EDGE", description: "Control Edge Detection Status", size: "1", shift: "17", mask: "0x20000" },
			{ name: "ALERT_RAW", description: "Alert Pin Real Time Status", size: "1", shift: "18", mask: "0x40000" },
			{ name: "CONTROL_RAW", description: "Control Pin Real Time Status", size: "1", shift: "19", mask: "0x80000" },
			{ name: "SDA_RAW", description: "PMBus Data Pin Real Time Status", size: "1", shift: "20", mask: "0x100000" },
			{ name: "SCL_RAW", description: "PMBus Clock Pin Real Time Status", size: "1", shift: "21", mask: "0x200000" },
		]
	},
	{ name: "PMBINTM", description: "PMBUS Interrupt Mask Register", offset: "0xA",
		bits: [
			{ name: "BUS_FREE", description: "Bus Free Interrupt Mask", size: "1", shift: "0", mask: "0x1" },
			{ name: "BUS_LOW_TIMEOUT", description: "Clock Low Timeout Interrupt Mask", size: "1", shift: "1", mask: "0x2" },
			{ name: "DATA_READY", description: "Data Ready Interrupt Mask", size: "1", shift: "2", mask: "0x4" },
			{ name: "DATA_REQUEST", description: "Data Request Interrupt Mask", size: "1", shift: "3", mask: "0x8" },
			{ name: "TARGET_ADDR_READY", description: "TARGET Address Ready Interrupt Mask", size: "1", shift: "4", mask: "0x10" },
			{ name: "EOM", description: "End of Message Interrupt Mask", size: "1", shift: "5", mask: "0x20" },
			{ name: "ALERT", description: "Alert Detection Interrupt Mask", size: "1", shift: "6", mask: "0x40" },
			{ name: "CONTROL", description: "Control Detection Interrupt Mask", size: "1", shift: "7", mask: "0x80" },
			{ name: "LOST_ARB", description: "Lost Arbitration Interrupt Mask", size: "1", shift: "8", mask: "0x100" },
			{ name: "CLK_HIGH_DETECT", description: "Clock High Detection Interrupt Mask", size: "1", shift: "9", mask: "0x200" },
		]
	},
	{ name: "PMBTCR", description: "PMBUS TARGET Mode Configuration Register", offset: "0xC",
		bits: [
			{ name: "TARGET_ADDR", description: "Configures the current device address of", size: "7", shift: "0", mask: "0x7F" },
			{ name: "MAN_TARGET_ACK", description: "Manual TARGET Address Acknowledgement Mode", size: "1", shift: "7", mask: "0x80" },
			{ name: "TARGET_MASK", description: "TARGET address mask", size: "7", shift: "8", mask: "0x7F00" },
			{ name: "PEC_ENA", description: "PEC Processing Enable", size: "1", shift: "15", mask: "0x8000" },
			{ name: "TX_COUNT", description: "Number of valid bytes in Transmit Data", size: "3", shift: "16", mask: "0x70000" },
			{ name: "TX_PEC", description: "send a PEC byte at end of message", size: "1", shift: "19", mask: "0x80000" },
			{ name: "MAN_CMD", description: "Manual Command Acknowledgement Mode", size: "1", shift: "20", mask: "0x100000" },
			{ name: "RX_BYTE_ACK_CNT", description: "Number of data bytes to automatically", size: "2", shift: "21", mask: "0x600000" },
		]
	},
	{ name: "PMBHTA", description: "PMBUS Hold TARGET Address Register", offset: "0xE",
		bits: [
			{ name: "TARGET_RW", description: "Stored R/W bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "TARGET_ADDR", description: "Stored device address", size: "7", shift: "1", mask: "0xFE" },
		]
	},
	{ name: "PMBCTRL", description: "PMBUS Control Register", offset: "0x10",
		bits: [
			{ name: "RESET", description: "PMBus Interface Synchronous Reset", size: "1", shift: "0", mask: "0x1" },
			{ name: "ALERT_EN", description: "TARGET Alert Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "BUS_LO_INT_EDGE", description: "Clock Low Timeout Interrupt Edge Select", size: "1", shift: "2", mask: "0x4" },
			{ name: "FAST_MODE", description: "Fast Mode Enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "CNTL_INT_EDGE", description: "Control Interrupt Edge Select", size: "1", shift: "5", mask: "0x20" },
			{ name: "ALERT_MODE", description: "Configures mode of Alert pin", size: "1", shift: "6", mask: "0x40" },
			{ name: "ALERT_VALUE", description: "Configures output value of Alert pin in", size: "1", shift: "7", mask: "0x80" },
			{ name: "ALERT_DIR", description: "Configures direction of Alert pin in GPIO", size: "1", shift: "8", mask: "0x100" },
			{ name: "CNTL_MODE", description: "Configures mode of Control pin", size: "1", shift: "9", mask: "0x200" },
			{ name: "CNTL_VALUE", description: "Configures output value of Control pin in", size: "1", shift: "10", mask: "0x400" },
			{ name: "CNTL_DIR", description: "Configures direction of Control pin in", size: "1", shift: "11", mask: "0x800" },
			{ name: "SDA_MODE", description: "Configures mode of PMBus Data pin", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SDA_VALUE", description: "Configures output value of PMBus data pin", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SDA_DIR", description: "Configures direction of PMBus data pin in", size: "1", shift: "14", mask: "0x4000" },
			{ name: "SCL_MODE", description: "Configures mode of PMBus Clock pin", size: "1", shift: "15", mask: "0x8000" },
			{ name: "SCL_VALUE", description: "Configures output value of PMBus clock pin", size: "1", shift: "16", mask: "0x10000" },
			{ name: "SCL_DIR", description: "Configures direction of PMBus clock pin in", size: "1", shift: "17", mask: "0x20000" },
			{ name: "IBIAS_A_EN", description: "PMBus Current Source A Control", size: "1", shift: "18", mask: "0x40000" },
			{ name: "IBIAS_B_EN", description: "PMBus Current Source B Control", size: "1", shift: "19", mask: "0x80000" },
			{ name: "CLK_LO_DIS", description: "Clock Low Timeout Disable", size: "1", shift: "20", mask: "0x100000" },
			{ name: "TARGET_EN", description: "PMBus TARGET Enable", size: "1", shift: "21", mask: "0x200000" },
			{ name: "CONTROLLER_EN", description: "PMBus CONTROLLER Enable", size: "1", shift: "22", mask: "0x400000" },
			{ name: "CLKDIV", description: "PMBUS Clock Divide Value", size: "5", shift: "23", mask: "0xF800000" },
			{ name: "I2CMODE", description: "Bit to enable I2C mode", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "PMBTIMCTL", description: "PMBUS Timing Control Register", offset: "0x12",
		bits: [
			{ name: "TIM_OVERRIDE", description: "Overide the default settings of the timing", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PMBTIMCLK", description: "PMBUS Clock Timing Register", offset: "0x14",
		bits: [
			{ name: "CLK_HIGH_LIMIT", description: "Determines the PMBUS CONTROLLER clock", size: "8", shift: "0", mask: "0xFF" },
			{ name: "CLK_FREQ", description: "Determines the PMBUS CONTROLLER clock", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "PMBTIMSTSETUP", description: "PMBUS Start Setup Time Register", offset: "0x16",
		bits: [
			{ name: "TSU_STA", description: "Setup time, rise edge of CONTROLLER clock to", size: "8", shift: "0", mask: "0xFF" },
		]
	},
	{ name: "PMBTIMBIDLE", description: "PMBUS Bus Idle Time Register", offset: "0x18",
		bits: [
			{ name: "BUSIDLE", description: "Determines the Bus Idle Limit", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
	{ name: "PMBTIMLOWTIMOUT", description: "PMBUS Clock Low Timeout Value Register", offset: "0x1A",
		bits: [
			{ name: "CLKLOWTIMOUT", description: "Determines the clock low timeout value", size: "20", shift: "0", mask: "0xFFFFF" },
		]
	},
	{ name: "PMBTIMHIGHTIMOUT", description: "PMBUS Clock High Timeout Value Register", offset: "0x1C",
		bits: [
			{ name: "CLKHIGHTIMOUT", description: "Determines the clock high timeout", size: "10", shift: "0", mask: "0x3FF" },
		]
	},
];
module.exports = {
	PMBUSRegisters: PMBUSRegisters,
}
