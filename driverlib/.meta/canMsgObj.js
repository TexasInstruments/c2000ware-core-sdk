let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_can.js");

var MaskWrongSettingVal = false;
function onChangeMsgType(inst, ui)
{
    if ((inst.msgType == device_driverlib_peripheral.CAN_MsgObjType[0].name) || inst.msgType == device_driverlib_peripheral.CAN_MsgObjType[1].name) {
        ui.msgIDMask.hidden = true;
    }
    else {
        ui.msgIDMask.hidden = false;
        if ((String(inst.msgType).includes("CAN_MSG_OBJ_TYPE_RXTX_REMOTE"))){
            ui.msgIDMask.readOnly = false;
        }
    }
    if ((inst.msgType == device_driverlib_peripheral.CAN_MsgObjType[2].name)) {
        ui.msgLen.hidden = true;
    }
    else
    {
        ui.msgLen.hidden = false;
    }
    if ((ui.msgIDMask.readOnly == true) && (inst.msgIDMask != 0))
    {
        MaskWrongSettingVal = true;
    }
    else {
        MaskWrongSettingVal = false;
    }
}

function onChangeFlags(inst, ui)
{
    if ((String(inst.flags).includes("CAN_MSG_OBJ_USE_ID_FILTER")) ||(String(inst.flags).includes("CAN_MSG_OBJ_USE_EXT_FILTER")) || (String(inst.msgType).includes("CAN_MSG_OBJ_TYPE_RXTX_REMOTE"))) {
        ui.msgIDMask.readOnly = false;
    }
    else {
        ui.msgIDMask.readOnly = true;
    }
    if ((ui.msgIDMask.readOnly == true) && (inst.msgIDMask != 0))
    {
        MaskWrongSettingVal = true;
    }
    else {
        MaskWrongSettingVal = false;
    }
}

function displayMsgObjConf(inst, ui)
{
    if (inst.msgObjs > 0) {
        ui.msgID.hidden = false;
        ui.flags.hidden = false;
        ui.msgLen.hidden = false;
        ui.msgIDMask.hidden = false;
        ui.msgType.hidden = false;
        ui.frameType.hidden = false;
    }
    else {
        ui.msgID.hidden = true;
        ui.flags.hidden = true;
        ui.msgLen.hidden = true;
        ui.msgIDMask.hidden = true;
        ui.msgType.hidden = true;
        ui.frameType.hidden = true;
    }
}
let config = [
    {
        name        : "frameType",
        displayName : "Type of Frame",
        description : 'Type of Frame',
        hidden      : false,
        default     : device_driverlib_peripheral.CAN_MsgFrameType[0].name,
        options     : device_driverlib_peripheral.CAN_MsgFrameType
    },
    {
        name        : "msgID",
        displayName : "Message Identifier",
        description : 'Message ID of object',
        hidden      : false,
        default     : 0,
    },
    {
        name        : "msgType",
        displayName : "Type of Message",
        description : 'Type of Message',
        hidden      : false,
        onChange    : onChangeMsgType,
        default     : device_driverlib_peripheral.CAN_MsgObjType[2].name,
        options     : device_driverlib_peripheral.CAN_MsgObjType
    },
    {
        name        : "flags",
        displayName : "Flags for Message Object",
        description : 'Flags for Message Object',
        hidden      : false,
        onChange    : onChangeFlags,
        default     : [],
        minSelections: 0,
        options     : [
            {name: "CAN_MSG_OBJ_TX_INT_ENABLE", displayName : "Enable Transmit Interrupts"},
            {name: "CAN_MSG_OBJ_RX_INT_ENABLE", displayName : "Enable Receive Interrupts"},
            {name: "CAN_MSG_OBJ_USE_ID_FILTER", displayName : "Use filtering based on the Message ID"},
            {name: "CAN_MSG_OBJ_USE_EXT_FILTER", displayName : "Use filtering based on the Extended Identifier"},
            {name: "CAN_MSG_OBJ_USE_DIR_FILTER", displayName : "Use filtering based on the direction of the transfer"},
            {name: "CAN_MSG_OBJ_FIFO", displayName : "Message object part of a FIFO and not final message"},
        ],
    },
    {
        name        : "msgIDMask",
        displayName : "Message Identifier Mask",
        description : 'CAN message identifier mask when filtering is enabled',
        hidden      : false,
        readOnly    : true,
        default     : 0,
    },
    {
        name        : "msgLen",
        displayName : "Message data length (0-8)",
        description : 'Number of data bytes in the Message',
        hidden      : true,
        default     : 0,
    },
    {
        name        : "intLine",
        displayName : "Trigger Interrupt on Line",
        description : 'Which Interrupt Line to be asserted when Interrupt occurs',
        hidden      : false,
        default     : "0",
        options     : [
            {name: "0", displayName : "Assert CAN line 0 interrupt for this Mailbox"},
            {name: "1", displayName : "Assert CAN line 1 interrupt for this Mailbox"},
        ],
    },
];


function onValidate(inst, validation) {
    if (inst.frameType == device_driverlib_peripheral.CAN_MsgFrameType[0].name)
    {
        if (inst.msgID < 0 || inst.msgID > 0x7FF)
        {
            validation.logError(
                "The Message ID must be a 11 bit value",
                inst, "msgID");
        }
    }
    else
    {
        if (inst.msgID < 0 || inst.msgID > 0x1FFFFFFF)
        {
            validation.logError(
                "The Message ID must be a 29 bit value",
                inst, "msgID");
        }
    }
    if (inst.msgIDMask < 0 || inst.msgIDMask > 0x1FFFFFFF)
    {
        validation.logError(
            "The Message ID Mask must be a 29 bit value",
            inst, "msgIDMask");
    }
    if (inst.msgLen < 0 || inst.msgLen > 8)
    {
        validation.logError(
            "The Message data length must be between 0 and 8",
            inst, "msgLen");
    }
    if (MaskWrongSettingVal)
    {
        validation.logWarning(
            "The Message ID Mask has a nonzero value but is not used in the current configuration",
            inst, "msgIDMask");
    }

}

var canMsgObj = {
    displayName: "canMsgObj",
    maxInstances: 64,
    defaultInstanceName: "msgObj",
    description: "Message Object",
    config: config,
    validate: onValidate,
};

exports = canMsgObj;
