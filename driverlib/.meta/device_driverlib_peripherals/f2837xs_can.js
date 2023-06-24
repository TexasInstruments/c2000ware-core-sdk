let CAN_MsgFrameType = [
	{ name: "CAN_MSG_FRAME_STD", displayName: "Set the message ID frame to standard." },
	{ name: "CAN_MSG_FRAME_EXT", displayName: "Set the message ID frame to extended." },
]
let CAN_MsgObjType = [
	{ name: "CAN_MSG_OBJ_TYPE_TX", displayName: "Transmit message object." },
	{ name: "CAN_MSG_OBJ_TYPE_TX_REMOTE", displayName: "Transmit remote request message object" },
	{ name: "CAN_MSG_OBJ_TYPE_RX", displayName: "Receive message object." },
	{ name: "CAN_MSG_OBJ_TYPE_RXTX_REMOTE", displayName: "Remote frame receive remote, with auto-transmit message object." },
]
let CAN_ClockSource = [
	{ name: "CAN_CLOCK_SOURCE_SYS", displayName: "Peripheral System Clock Source" },
	{ name: "CAN_CLOCK_SOURCE_XTAL", displayName: "External Oscillator Clock Source" },
	{ name: "CAN_CLOCK_SOURCE_AUX", displayName: "Auxiliary Clock Input Source" },
]
let CAN_MSG_OBJ = [
	{ name: "CAN_MSG_OBJ_TX_INT_ENABLE", displayName: "This indicates that transmit interrupts should be enabled, or are enabled." },
	{ name: "CAN_MSG_OBJ_RX_INT_ENABLE", displayName: "This indicates that receive interrupts should be enabled, or are  enabled." },
	{ name: "CAN_MSG_OBJ_USE_ID_FILTER", displayName: "This indicates that a message object will use or is using filtering  based on the object's message identifier." },
	{ name: "CAN_MSG_OBJ_USE_DIR_FILTER", displayName: "This indicates that a message object will use or is using filtering  based on the direction of the transfer." },
	{ name: "CAN_MSG_OBJ_USE_EXT_FILTER", displayName: "This indicates that a message object will use or is using message  identifier filtering based on the extended identifier." },
	{ name: "CAN_MSG_OBJ_FIFO", displayName: "This indicates that this message object is part of a FIFO structure and  not the final message object in a FIFO." },
	{ name: "CAN_MSG_OBJ_NO_FLAGS", displayName: "This indicates that a message object has no flags set." },
]
let CAN_INT = [
	{ name: "CAN_INT_ERROR", displayName: "This flag is used to allow a CAN controller to generate error  interrupts." },
	{ name: "CAN_INT_STATUS", displayName: "This flag is used to allow a CAN controller to generate status  interrupts." },
	{ name: "CAN_INT_IE0", displayName: "This flag is used to allow a CAN controller to generate interrupts  on interrupt line 0" },
	{ name: "CAN_INT_IE1", displayName: "This flag is used to allow a CAN controller to generate interrupts  on interrupt line 1" },
]
let CAN_STATUS = [
	{ name: "CAN_STATUS_PERR", displayName: "CAN controller has detected a parity error." },
	{ name: "CAN_STATUS_BUS_OFF", displayName: "CAN controller has entered a Bus Off state." },
	{ name: "CAN_STATUS_EWARN", displayName: "CAN controller error level has reached warning level." },
	{ name: "CAN_STATUS_EPASS", displayName: "CAN controller error level has reached error passive level." },
	{ name: "CAN_STATUS_RXOK", displayName: "A message was received successfully since the last read of this status." },
	{ name: "CAN_STATUS_TXOK", displayName: "A message was transmitted successfully since the last read of this  status." },
	{ name: "CAN_STATUS_LEC_MSK", displayName: "This is the mask for the last error code field." },
	{ name: "CAN_STATUS_LEC_NONE", displayName: "There was no error." },
	{ name: "CAN_STATUS_LEC_STUFF", displayName: "A bit stuffing error has occurred." },
	{ name: "CAN_STATUS_LEC_FORM", displayName: "A formatting error has occurred." },
	{ name: "CAN_STATUS_LEC_ACK", displayName: "An acknowledge error has occurred." },
	{ name: "CAN_STATUS_LEC_BIT1", displayName: "The bus remained a bit level of 1 for longer than is allowed." },
	{ name: "CAN_STATUS_LEC_BIT0", displayName: "The bus remained a bit level of 0 for longer than is allowed." },
	{ name: "CAN_STATUS_LEC_CRC", displayName: "A CRC error has occurred." },
]
let CAN_GLOBAL_INT = [
	{ name: "CAN_GLOBAL_INT_CANINT0", displayName: "CANINT0 global interrupt bit" },
	{ name: "CAN_GLOBAL_INT_CANINT1", displayName: "CANINT1 global interrupt bit" },
]
module.exports = {
	CAN_MsgFrameType: CAN_MsgFrameType,
	CAN_MsgObjType: CAN_MsgObjType,
	CAN_ClockSource: CAN_ClockSource,
	CAN_MSG_OBJ: CAN_MSG_OBJ,
	CAN_INT: CAN_INT,
	CAN_STATUS: CAN_STATUS,
	CAN_GLOBAL_INT: CAN_GLOBAL_INT,
}
