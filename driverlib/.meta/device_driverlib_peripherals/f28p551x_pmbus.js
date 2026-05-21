let PMBus_ClockMode = [
	{ name: "PMBUS_CLOCKMODE_STANDARD", displayName: "Standard mode 100 kHz" },
	{ name: "PMBUS_CLOCKMODE_FAST", displayName: "Fast Mode 400 kHz" },
	{ name: "PMBUS_CLOCKMODE_FAST_PLUS", displayName: "Fast plus Mode 1 MHz" },
]
let PMBus_accessType = [
	{ name: "PMBUS_ACCESSTYPE_WRITE", displayName: "Target last address for write transaction" },
	{ name: "PMBUS_ACCESSTYPE_READ", displayName: "Target last address for read transaction" },
]
let PMBus_intEdge = [
	{ name: "PMBUS_INTEDGE_FALLING", displayName: "Interrupt generated on falling edge" },
	{ name: "PMBUS_INTEDGE_RISING", displayName: "Interrupt generated on rising edge" },
]
let PMBUS_INCLUDE_CRC8_TABLE = [
	{ name: "PMBUS_INCLUDE_CRC8_TABLE", displayName: "Specifies whether to include the CRC8 table in the  library build" },
]
let PMBUS_CONTROLLER_ENABLE = [
	{ name: "PMBUS_CONTROLLER_ENABLE_PRC_CALL", displayName: "Enable Process call message", legacyNames: ["PMBUS_MASTER_ENABLE_PRC_CALL"]},
	{ name: "PMBUS_CONTROLLER_ENABLE_GRP_CMD", displayName: "Enable Group command message", legacyNames: ["PMBUS_MASTER_ENABLE_GRP_CMD"]},
	{ name: "PMBUS_CONTROLLER_ENABLE_PEC", displayName: "Enable PEC byte", legacyNames: ["PMBUS_MASTER_ENABLE_PEC"]},
	{ name: "PMBUS_CONTROLLER_ENABLE_EXT_CMD", displayName: "Enable Extended command", legacyNames: ["PMBUS_MASTER_ENABLE_EXT_CMD"]},
	{ name: "PMBUS_CONTROLLER_ENABLE_CMD", displayName: "Enable Command word", legacyNames: ["PMBUS_MASTER_ENABLE_CMD"]},
	{ name: "PMBUS_CONTROLLER_ENABLE_READ", displayName: "Enable read", legacyNames: ["PMBUS_MASTER_ENABLE_READ"]},
]
let PMBUS_INT = [
	{ name: "PMBUS_INT_BUS_FREE", displayName: "Bus Free Interrupt" },
	{ name: "PMBUS_INT_CLK_LOW_TIMEOUT", displayName: "Clock Low Time-out Interrupt" },
	{ name: "PMBUS_INT_DATA_READY", displayName: "Data Ready Interrupt" },
	{ name: "PMBUS_INT_DATA_REQUEST", displayName: "Data Request Interrupt" },
	{ name: "PMBUS_INT_TARGET_ADDR_READY", displayName: "Target Address Ready Interrupt", legacyNames: ["PMBUS_INT_SLAVE_ADDR_READY"]},
	{ name: "PMBUS_INT_EOM", displayName: "End of Message Interrupt" },
	{ name: "PMBUS_INT_ALERT", displayName: "Alert Detection Interrupt" },
	{ name: "PMBUS_INT_CONTROL", displayName: "Control Detection Interrupt" },
	{ name: "PMBUS_INT_LOST_ARB", displayName: "Lost Arbitration Interrupt" },
	{ name: "PMBUS_INT_CLK_HIGH_DETECT", displayName: "Clock High Detection Interrupt" },
	{ name: "PMBUS_INT_ALL", displayName: "all PMBus interrupts" },
]
let PMBUS_INTSRC = [
	{ name: "PMBUS_INTSRC_BUS_FREE", displayName: "Bus Free Interrupt" },
	{ name: "PMBUS_INTSRC_CLK_LOW_TIMEOUT", displayName: "Clock Low Time-out Interrupt" },
	{ name: "PMBUS_INTSRC_DATA_READY", displayName: "Data Ready Interrupt" },
	{ name: "PMBUS_INTSRC_DATA_REQUEST", displayName: "Data Request Interrupt" },
	{ name: "PMBUS_INTSRC_TARGET_ADDR_READY", displayName: "Target Address Ready Interrupt", legacyNames: ["PMBUS_INTSRC_SLAVE_ADDR_READY"]},
	{ name: "PMBUS_INTSRC_EOM", displayName: "End of Message Interrupt" },
	{ name: "PMBUS_INTSRC_ALERT", displayName: "Alert Detection Interrupt" },
	{ name: "PMBUS_INTSRC_CONTROL", displayName: "Control Detection Interrupt" },
	{ name: "PMBUS_INTSRC_LOST_ARB", displayName: "Lost Arbitration Interrupt" },
	{ name: "PMBUS_INTSRC_CLK_HIGH_DETECT", displayName: "Clock High Detection Interrupt" },
]
let PMBUS_TARGET = [
	{ name: "PMBUS_TARGET_ENABLE_MANUAL_ACK", displayName: "Enable manual target ack modes", legacyNames: ["PMBUS_SLAVE_ENABLE_MANUAL_ACK"]},
	{ name: "PMBUS_TARGET_ENABLE_PEC_PROCESSING", displayName: "Enable PEC byte processing", legacyNames: ["PMBUS_SLAVE_ENABLE_PEC_PROCESSING"]},
	{ name: "PMBUS_TARGET_TRANSMIT_PEC", displayName: "Transmit PEC at end of transaction", legacyNames: ["PMBUS_SLAVE_TRANSMIT_PEC"]},
	{ name: "PMBUS_TARGET_ENABLE_MANUAL_CMD_ACK", displayName: "Data Request flag generated after  receipt of command code, firmware  required to issue ACK to continue message", legacyNames: ["PMBUS_SLAVE_ENABLE_MANUAL_CMD_ACK"]},
	{ name: "PMBUS_TARGET_DISABLE_ADDRESS_MASK", displayName: "any bits cleared in target address mask  make that bit a don't care", legacyNames: ["PMBUS_SLAVE_DISABLE_ADDRESS_MASK"]},
	{ name: "PMBUS_TARGET_AUTO_ACK_1_BYTES", displayName: "Target will auto acknowledge every  received byte", legacyNames: ["PMBUS_SLAVE_AUTO_ACK_1_BYTES"]},
	{ name: "PMBUS_TARGET_AUTO_ACK_2_BYTES", displayName: "Target will auto acknowledge every  2 received bytes", legacyNames: ["PMBUS_SLAVE_AUTO_ACK_2_BYTES"]},
	{ name: "PMBUS_TARGET_AUTO_ACK_3_BYTES", displayName: "Target will auto acknowledge every  3 received bytes", legacyNames: ["PMBUS_SLAVE_AUTO_ACK_3_BYTES"]},
	{ name: "PMBUS_TARGET_AUTO_ACK_4_BYTES", displayName: "Target will auto acknowledge every  4 received bytes", legacyNames: ["PMBUS_SLAVE_AUTO_ACK_4_BYTES"]},
]
module.exports = {
	PMBus_ClockMode: PMBus_ClockMode,
	PMBus_accessType: PMBus_accessType,
	PMBus_intEdge: PMBus_intEdge,
	PMBUS_INCLUDE_CRC8_TABLE: PMBUS_INCLUDE_CRC8_TABLE,
	PMBUS_CONTROLLER_ENABLE: PMBUS_CONTROLLER_ENABLE,
	PMBUS_INT: PMBUS_INT,
	PMBUS_INTSRC: PMBUS_INTSRC,
	PMBUS_TARGET: PMBUS_TARGET,
}
