import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { GcPromise } from '../../gc-core-assets/lib/GcPromise';
import { EncoderType, NoopDecoderType, AbstractMessageBasedDecoder, AbstractFrameDecoder } from '../../gc-target-configuration/lib/TargetConfiguration';
import { DEFAULT_MAX_CONSECUTIVE_ERRORS, receivePayloadEventType, receiveInterruptEventType } from '../../gc-target-configuration/lib/ICodecAnalogControllerBaseParams';
import { Events } from '../../gc-core-assets/lib/Events';

/**
 *  Copyright (c) 2020, 2024 Texas Instruments Incorporated
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  *   Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the distribution.
 *  *   Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 *  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 *  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
const console = new GcConsole('gc-codec-usb2any');
// packet types
const COMMAND_PACKET = 1;
const REPLY_PACKET = 2;
const ERROR_PACKET = 3;
const PAYLOAD_PACKET = 4;
const INTERRUPT_PACKET = 5;
// packet flags
const FLAG_MOREDATA = 1;
const PACKET_IDENTIFIER = 'T'.charCodeAt(0);
const PACKET_ID = 0;
const PACKET_PEC = 1;
const PACKET_PAYLOAD_LEN = 2;
const PACKET_TYPE = 3;
const PACKET_FLAGS = 4;
const PACKET_SEQ_NUM = 5;
const PACKET_STATUS = 6;
const PACKET_COMMAND = 7;
const PACKET_PAYLOAD = 8;
const MAX_PACKET_SIZE = 62; // size, in bytes, of a USB packet
const PACKET_HEADER_SIZE = PACKET_PAYLOAD;
const MAX_PAYLOAD = MAX_PACKET_SIZE - PACKET_HEADER_SIZE;
var Command;
(function (Command) {
    Command[Command["Cmd_LoopPacket"] = 0] = "Cmd_LoopPacket";
    Command[Command["Cmd_I2C_Control"] = 1] = "Cmd_I2C_Control";
    Command[Command["Cmd_I2C_Write"] = 2] = "Cmd_I2C_Write";
    Command[Command["Cmd_I2C_Read"] = 3] = "Cmd_I2C_Read";
    Command[Command["Cmd_I2CRead_WithAddress"] = 4] = "Cmd_I2CRead_WithAddress";
    Command[Command["Cmd_GPIO_Write_Control"] = 5] = "Cmd_GPIO_Write_Control";
    Command[Command["Cmd_GPIO_Write_States"] = 6] = "Cmd_GPIO_Write_States";
    Command[Command["Cmd_GPIO_Read_States"] = 7] = "Cmd_GPIO_Read_States";
    Command[Command["Cmd_SPI_Control"] = 8] = "Cmd_SPI_Control";
    Command[Command["Cmd_SPI_WriteAndRead"] = 9] = "Cmd_SPI_WriteAndRead";
    Command[Command["Cmd_FirmwareVersion_Read"] = 10] = "Cmd_FirmwareVersion_Read";
    Command[Command["Cmd_MSP430_WordWrite"] = 11] = "Cmd_MSP430_WordWrite";
    Command[Command["Cmd_MSP430_WordRead"] = 12] = "Cmd_MSP430_WordRead";
    Command[Command["Cmd_MSP430_ByteWrite"] = 13] = "Cmd_MSP430_ByteWrite";
    Command[Command["Cmd_MSP430_ByteRead"] = 14] = "Cmd_MSP430_ByteRead";
    Command[Command["Cmd_UART_Control"] = 15] = "Cmd_UART_Control";
    Command[Command["Cmd_MSP430_MemoryWrite"] = 16] = "Cmd_MSP430_MemoryWrite";
    Command[Command["Cmd_MSP430_MemoryRead"] = 17] = "Cmd_MSP430_MemoryRead";
    Command[Command["Cmd_UART_Write"] = 18] = "Cmd_UART_Write";
    Command[Command["Cmd_UART_SetMode"] = 19] = "Cmd_UART_SetMode";
    Command[Command["Cmd_UART_Read"] = 20] = "Cmd_UART_Read";
    Command[Command["Cmd_Local_I2C_Write"] = 21] = "Cmd_Local_I2C_Write";
    Command[Command["Cmd_PWM_Write_Control"] = 22] = "Cmd_PWM_Write_Control";
    Command[Command["Cmd_Power_WriteControl"] = 23] = "Cmd_Power_WriteControl";
    Command[Command["Cmd_Power_ReadStatus"] = 24] = "Cmd_Power_ReadStatus";
    Command[Command["Cmd_ADC_Control"] = 25] = "Cmd_ADC_Control";
    Command[Command["Cmd_ADC_ConvertAndRead"] = 26] = "Cmd_ADC_ConvertAndRead";
    Command[Command["Cmd_LED_Control"] = 27] = "Cmd_LED_Control";
    Command[Command["Cmd_Clock_Control"] = 28] = "Cmd_Clock_Control";
    Command[Command["Cmd_FEC_Control"] = 29] = "Cmd_FEC_Control";
    Command[Command["Cmd_FEC_CountAndRead"] = 30] = "Cmd_FEC_CountAndRead";
    Command[Command["Cmd_Interrupt_Control"] = 31] = "Cmd_Interrupt_Control";
    Command[Command["Cmd_Interrupt_Received"] = 32] = "Cmd_Interrupt_Received";
    Command[Command["Cmd_EasyScale_Control"] = 33] = "Cmd_EasyScale_Control";
    Command[Command["Cmd_EasyScale_Write"] = 34] = "Cmd_EasyScale_Write";
    Command[Command["Cmd_EasyScale_Read"] = 35] = "Cmd_EasyScale_Read";
    Command[Command["Cmd_EasyScale_ACK_Received"] = 36] = "Cmd_EasyScale_ACK_Received";
    Command[Command["Cmd_GPIO_SetPort"] = 37] = "Cmd_GPIO_SetPort";
    Command[Command["Cmd_GPIO_WritePort"] = 38] = "Cmd_GPIO_WritePort";
    Command[Command["Cmd_GPIO_ReadPort"] = 39] = "Cmd_GPIO_ReadPort";
    Command[Command["Cmd_Reserved_40"] = 40] = "Cmd_Reserved_40";
    Command[Command["Cmd_Reserved_41"] = 41] = "Cmd_Reserved_41";
    Command[Command["Cmd_Reserved_42"] = 42] = "Cmd_Reserved_42";
    Command[Command["Cmd_Reserved_43"] = 43] = "Cmd_Reserved_43";
    Command[Command["Cmd_Reserved_44"] = 44] = "Cmd_Reserved_44";
    Command[Command["Cmd_Reserved_45"] = 45] = "Cmd_Reserved_45";
    Command[Command["Cmd_Reserved_46"] = 46] = "Cmd_Reserved_46";
    Command[Command["Cmd_Reserved_47"] = 47] = "Cmd_Reserved_47";
    Command[Command["Cmd_Reserved_48"] = 48] = "Cmd_Reserved_48";
    Command[Command["Cmd_Reserved_49"] = 49] = "Cmd_Reserved_49";
    Command[Command["Cmd_SMBUS_SendByte"] = 50] = "Cmd_SMBUS_SendByte";
    Command[Command["Cmd_SMBUS_WriteByte"] = 51] = "Cmd_SMBUS_WriteByte";
    Command[Command["Cmd_SMBUS_WriteWord"] = 52] = "Cmd_SMBUS_WriteWord";
    Command[Command["Cmd_SMBUS_WriteBlock"] = 53] = "Cmd_SMBUS_WriteBlock";
    Command[Command["Cmd_SMBUS_ReceiveByte"] = 54] = "Cmd_SMBUS_ReceiveByte";
    Command[Command["Cmd_SMBUS_ReadByte"] = 55] = "Cmd_SMBUS_ReadByte";
    Command[Command["Cmd_SMBUS_ReadWord"] = 56] = "Cmd_SMBUS_ReadWord";
    Command[Command["Cmd_SMBUS_ReadBlock"] = 57] = "Cmd_SMBUS_ReadBlock";
    Command[Command["Cmd_SMBUS_ProcessCall"] = 58] = "Cmd_SMBUS_ProcessCall";
    Command[Command["Cmd_SMBUS_BWBRProcessCall"] = 59] = "Cmd_SMBUS_BWBRProcessCall";
    Command[Command["Cmd_SMBUS_Control"] = 60] = "Cmd_SMBUS_Control";
    Command[Command["Cmd_SMBUS_GetEchoBuffer"] = 61] = "Cmd_SMBUS_GetEchoBuffer";
    Command[Command["Cmd_RFFE_RegZeroWrite"] = 62] = "Cmd_RFFE_RegZeroWrite";
    Command[Command["Cmd_RFFE_RegWrite"] = 63] = "Cmd_RFFE_RegWrite";
    Command[Command["Cmd_RFFE_ExtRegWrite"] = 64] = "Cmd_RFFE_ExtRegWrite";
    Command[Command["Cmd_RFFE_ExtRegWriteLong"] = 65] = "Cmd_RFFE_ExtRegWriteLong";
    Command[Command["Cmd_RFFE_RegRead"] = 66] = "Cmd_RFFE_RegRead";
    Command[Command["Cmd_RFFE_ExtRegRead"] = 67] = "Cmd_RFFE_ExtRegRead";
    Command[Command["Cmd_RFFE_ExtRegReadLong"] = 68] = "Cmd_RFFE_ExtRegReadLong";
    Command[Command["Cmd_OneWire_SetMode"] = 69] = "Cmd_OneWire_SetMode";
    Command[Command["Cmd_OneWire_PulseSetup"] = 70] = "Cmd_OneWire_PulseSetup";
    Command[Command["Cmd_OneWire_PulseWrite"] = 71] = "Cmd_OneWire_PulseWrite";
    Command[Command["Cmd_OneWire_SetState"] = 72] = "Cmd_OneWire_SetState";
    Command[Command["Cmd_Reserved_73"] = 73] = "Cmd_Reserved_73";
    Command[Command["Cmd_Reserved_74"] = 74] = "Cmd_Reserved_74";
    Command[Command["Cmd_Reserved_75"] = 75] = "Cmd_Reserved_75";
    Command[Command["Cmd_Reserved_76"] = 76] = "Cmd_Reserved_76";
    Command[Command["Cmd_Reserved_77"] = 77] = "Cmd_Reserved_77";
    Command[Command["Cmd_Reserved_78"] = 78] = "Cmd_Reserved_78";
    Command[Command["Cmd_Reserved_79"] = 79] = "Cmd_Reserved_79";
    Command[Command["Cmd_Reserved_80"] = 80] = "Cmd_Reserved_80";
    Command[Command["Cmd_Reserved_81"] = 81] = "Cmd_Reserved_81";
    Command[Command["Cmd_Reserved_82"] = 82] = "Cmd_Reserved_82";
    Command[Command["Cmd_Reserved_83"] = 83] = "Cmd_Reserved_83";
    Command[Command["Cmd_Packet"] = 84] = "Cmd_Packet";
    Command[Command["Cmd_GPIO_SetCustomPort"] = 85] = "Cmd_GPIO_SetCustomPort";
    Command[Command["Cmd_GPIO_WriteCustomPort"] = 86] = "Cmd_GPIO_WriteCustomPort";
    Command[Command["Cmd_GPIO_ReadCustomPort"] = 87] = "Cmd_GPIO_ReadCustomPort";
    Command[Command["Cmd_GPIO_WritePulse"] = 88] = "Cmd_GPIO_WritePulse";
    Command[Command["Cmd_Reserved_89"] = 89] = "Cmd_Reserved_89";
    Command[Command["Cmd_Reserved_90"] = 90] = "Cmd_Reserved_90";
    Command[Command["Cmd_Reserved_91"] = 91] = "Cmd_Reserved_91";
    Command[Command["Cmd_Reserved_92"] = 92] = "Cmd_Reserved_92";
    Command[Command["Cmd_Reserved_93"] = 93] = "Cmd_Reserved_93";
    Command[Command["Cmd_Reserved_94"] = 94] = "Cmd_Reserved_94";
    Command[Command["Cmd_Reserved_95"] = 95] = "Cmd_Reserved_95";
    Command[Command["Cmd_I2C_BlkWriteBlkRead"] = 96] = "Cmd_I2C_BlkWriteBlkRead";
    Command[Command["Cmd_InvokeBSL"] = 97] = "Cmd_InvokeBSL";
    Command[Command["Cmd_FirmwareDebugMode"] = 98] = "Cmd_FirmwareDebugMode";
    Command[Command["Cmd_Restart"] = 99] = "Cmd_Restart";
    Command[Command["Cmd_I2C_ReadWithAddress"] = 100] = "Cmd_I2C_ReadWithAddress";
    Command[Command["Cmd_I2C_ReadInternal"] = 101] = "Cmd_I2C_ReadInternal";
    Command[Command["Cmd_I2C_WriteInternal"] = 102] = "Cmd_I2C_WriteInternal";
    Command[Command["Cmd_GetErrorList"] = 103] = "Cmd_GetErrorList";
    Command[Command["Cmd_LED_SetState"] = 104] = "Cmd_LED_SetState";
    Command[Command["Cmd_Power_SetVoltageRef"] = 105] = "Cmd_Power_SetVoltageRef";
    Command[Command["Cmd_Status_GetControllerType"] = 106] = "Cmd_Status_GetControllerType";
    Command[Command["Cmd_Power_Enable"] = 107] = "Cmd_Power_Enable";
    Command[Command["Cmd_ADC_Enable"] = 108] = "Cmd_ADC_Enable";
    Command[Command["Cmd_ADC_Acquire"] = 109] = "Cmd_ADC_Acquire";
    Command[Command["Cmd_ADC_GetData"] = 110] = "Cmd_ADC_GetData";
    Command[Command["Cmd_ADC_GetStatus"] = 111] = "Cmd_ADC_GetStatus";
    Command[Command["Cmd_ADC_SetReference"] = 112] = "Cmd_ADC_SetReference";
    Command[Command["Cmd_Status_GetBoardRevision"] = 113] = "Cmd_Status_GetBoardRevision";
    Command[Command["Cmd_Status_EVMDetect"] = 114] = "Cmd_Status_EVMDetect";
    Command[Command["Cmd_ADC_AcquireTriggered"] = 115] = "Cmd_ADC_AcquireTriggered";
    Command[Command["Cmd_Power_Notify"] = 116] = "Cmd_Power_Notify";
    Command[Command["Cmd_Digital_Capture"] = 117] = "Cmd_Digital_Capture";
    Command[Command["Cmd_Digital_GetData"] = 118] = "Cmd_Digital_GetData";
    Command[Command["Cmd_Digital_GetStatus"] = 119] = "Cmd_Digital_GetStatus";
    Command[Command["Cmd_EasyScale_WriteAndRead"] = 120] = "Cmd_EasyScale_WriteAndRead";
    Command[Command["Cmd_DisplayScale_Set"] = 121] = "Cmd_DisplayScale_Set";
    Command[Command["Cmd_DisplayScale_WriteReg"] = 122] = "Cmd_DisplayScale_WriteReg";
    Command[Command["Cmd_DisplayScale_ReadReg"] = 123] = "Cmd_DisplayScale_ReadReg";
    Command[Command["Cmd_DisplayScale_WriteAndRead"] = 124] = "Cmd_DisplayScale_WriteAndRead";
    Command[Command["Cmd_Reserved_125"] = 125] = "Cmd_Reserved_125";
    Command[Command["Cmd_Reserved_126"] = 126] = "Cmd_Reserved_126";
    Command[Command["Cmd_Invalid"] = 127] = "Cmd_Invalid";
    Command[Command["Cmd_Stream_Start"] = 128] = "Cmd_Stream_Start";
    Command[Command["Cmd_Stream_Stop"] = 129] = "Cmd_Stream_Stop";
    Command[Command["Cmd_Stream_Status"] = 130] = "Cmd_Stream_Status";
    Command[Command["Cmd_Stream_GetData"] = 131] = "Cmd_Stream_GetData";
    Command[Command["Cmd_Stream_Execute"] = 132] = "Cmd_Stream_Execute";
    Command[Command["Cmd_SPI_StreamOut"] = 133] = "Cmd_SPI_StreamOut";
    Command[Command["Cmd_SPI_StreamStop"] = 134] = "Cmd_SPI_StreamStop";
    Command[Command["Cmd_SPI_WriteAndReadEx"] = 135] = "Cmd_SPI_WriteAndReadEx";
    Command[Command["Cmd_Reserved_136"] = 136] = "Cmd_Reserved_136";
    Command[Command["Cmd_Reserved_137"] = 137] = "Cmd_Reserved_137";
    Command[Command["Cmd_Pegasus_Test"] = 138] = "Cmd_Pegasus_Test";
    Command[Command["Cmd_Reserved_139"] = 139] = "Cmd_Reserved_139";
    Command[Command["Cmd_Port_Setup"] = 140] = "Cmd_Port_Setup";
    Command[Command["Cmd_Port_Read"] = 141] = "Cmd_Port_Read";
    Command[Command["Cmd_Port_Write"] = 142] = "Cmd_Port_Write";
    Command[Command["Cmd_Port_WritePulse"] = 143] = "Cmd_Port_WritePulse";
    Command[Command["Cmd_END"] = 144] = "Cmd_END";
    // 0x90
    // ** = UNUSED COMMAND
})(Command || (Command = {}));
const szCommandName = [
    'Cmd_LoopPacket',
    'Cmd_I2C_Control',
    'Cmd_I2C_Write',
    'Cmd_I2C_Read',
    'Cmd_I2CRead_WithAddress',
    'Cmd_GPIO_Write_Control',
    'Cmd_GPIO_Write_States',
    'Cmd_GPIO_Read_States',
    'Cmd_SPI_Control',
    'Cmd_SPI_WriteAndRead',
    'Cmd_FirmwareVersion_Read',
    'Cmd_MSP430_WordWrite',
    'Cmd_MSP430_WordRead',
    'Cmd_MSP430_ByteWrite',
    'Cmd_MSP430_ByteRead',
    'Cmd_UART_Control',
    'Cmd_Reserved_16',
    'Cmd_Reserved_17',
    'Cmd_UART_Write',
    'Cmd_UART_SetMode',
    'Cmd_UART_Read',
    'Cmd_Local_I2C_Write',
    'Cmd_PWM_Write_Control',
    'Cmd_Power_WriteControl',
    'Cmd_Power_ReadStatus',
    'Cmd_ADC_Control',
    'Cmd_ADC_ConvertAndRead',
    'Cmd_LED_Control',
    'Cmd_Clock_Control',
    'Cmd_FEC_Control',
    'Cmd_FEC_CountAndRead',
    'Cmd_Interrupt_Control',
    'Cmd_Interrupt_Received',
    'Cmd_EasyScale_Control',
    'Cmd_EasyScale_Write',
    'Cmd_EasyScale_Read',
    'Cmd_EasyScale_ACK_Received',
    'Cmd_GPIO_SetPort',
    'Cmd_GPIO_WritePort',
    'Cmd_GPIO_ReadPort',
    'Cmd_Reserved_40',
    'Cmd_Reserved_41',
    'Cmd_Reserved_42',
    'Cmd_Reserved_43',
    'Cmd_Reserved_44',
    'Cmd_Reserved_45',
    'Cmd_Reserved_46',
    'Cmd_Reserved_47',
    'Cmd_Reserved_48',
    'Cmd_Reserved_49',
    'Cmd_SMBUS_SendByte',
    'Cmd_SMBUS_WriteByte',
    'Cmd_SMBUS_WriteWord',
    'Cmd_SMBUS_WriteBlock',
    'Cmd_SMBUS_ReceiveByte',
    'Cmd_SMBUS_ReadByte',
    'Cmd_SMBUS_ReadWord',
    'Cmd_SMBUS_ReadBlock',
    'Cmd_SMBUS_ProcessCall',
    'Cmd_SMBUS_BWBRProcessCall',
    'Cmd_SMBUS_Control',
    'Cmd_SMBUS_GetEchoBuffer',
    'Cmd_RFFE_RegZeroWrite',
    'Cmd_RFFE_RegWrite',
    'Cmd_RFFE_ExtRegWrite',
    'Cmd_RFFE_ExtRegWriteLong',
    'Cmd_RFFE_RegRead',
    'Cmd_RFFE_ExtRegRead',
    'Cmd_RFFE_ExtRegReadLong',
    'Cmd_OneWire_SetMode',
    'Cmd_OneWire_PulseSetup',
    'Cmd_OneWire_PulseWrite',
    'Cmd_OneWire_SetState',
    'Cmd_Reserved_73',
    'Cmd_Reserved_74',
    'Cmd_Reserved_75',
    'Cmd_Reserved_76',
    'Cmd_Reserved_77',
    'Cmd_Reserved_78',
    'Cmd_Reserved_79',
    'Cmd_Reserved_80',
    'Cmd_Reserved_81',
    'Cmd_Reserved_82',
    'Cmd_Reserved_83',
    'Cmd_Packet',
    'Cmd_GPIO_SetCustomPort',
    'Cmd_GPIO_WriteCustomPort',
    'Cmd_GPIO_ReadCustomPort',
    'Cmd_GPIO_WritePulse',
    'Cmd_Reserved_89',
    'Cmd_Reserved_90',
    'Cmd_Reserved_91',
    'Cmd_Reserved_92',
    'Cmd_Reserved_93',
    'Cmd_Reserved_94',
    'Cmd_Reserved_95',
    'Cmd_I2C_BlkWriteBlkRead',
    'Cmd_InvokeBSL',
    'Cmd_FirmwareDebugMode',
    'Cmd_Restart',
    'Cmd_I2C_ReadWithAddress',
    'Cmd_I2C_ReadInternal',
    'Cmd_I2C_WriteInternal',
    'Cmd_GetErrorList',
    'Cmd_LED_SetState',
    'Cmd_Power_SetVoltageRef',
    'Cmd_Status_GetControllerType',
    'Cmd_Power_Enable',
    'Cmd_ADC_Enable',
    'Cmd_ADC_Acquire',
    'Cmd_ADC_GetData',
    'Cmd_ADC_GetStatus',
    'Cmd_ADC_SetReference',
    'Cmd_Status_GetBoardRevision',
    'Cmd_Status_EVMDetect',
    'Cmd_ADC_AcquireTriggered',
    'Cmd_Power_Notify',
    'Cmd_Digital_Capture',
    'Cmd_Digital_GetData',
    'Cmd_Digital_GetStatus',
    'Cmd_EasyScale_WriteAndRead',
    'Cmd_DisplayScale_Set',
    'Cmd_DisplayScale_WriteReg',
    'Cmd_DisplayScale_ReadReg',
    'Cmd_DisplayScale_WriteAndRead',
    'Cmd_Reserved_125',
    'Cmd_Reserved_126',
    'Cmd_Invalid',
    'Cmd_Stream_Start',
    'Cmd_Stream_Stop',
    'Cmd_Stream_Status',
    'Cmd_Stream_GetData',
    'Cmd_Stream_Execute',
    'Cmd_SPI_StreamOut',
    'Cmd_SPI_StreamStop',
    'Cmd_SPI_WriteAndReadEx',
    'Cmd_Reserved_136',
    'Cmd_Reserved_137',
    'Cmd_Pegasus_Test',
    'Cmd_Reserved_139',
    'Cmd_Port_Setup',
    'Cmd_Port_Read',
    'Cmd_Port_Write',
    'Cmd_Port_ReadMultiple',
    'Cmd_END',
    '' // for loop control
];
// error code constants
const ERR_OK = 0;
const ERR_COM_RX_OVERFLOW = -1;
const ERR_COM_RX_BUF_EMPTY = -2;
const ERR_COM_TX_BUF_FULL = -3;
const ERR_COM_TX_STALLED = -4;
const ERR_COM_TX_FAILED = -5;
const ERR_COM_OPEN_FAILED = -6;
const ERR_COM_PORT_NOT_OPEN = -7;
const ERR_COM_PORT_IS_OPEN = -8;
const ERR_COM_READ_TIMEOUT = -9;
const ERR_COM_READ_ERROR = -10;
const ERR_COM_WRITE_ERROR = -11;
const ERR_DEVICE_NOT_FOUND = -12;
const ERR_COM_CRC_FAILED = -13;
const ERR_INVALID_PORT = -20;
const ERR_ADDRESS_OUT_OF_RANGE = -21;
const ERR_INVALID_FUNCTION_CODE = -22;
const ERR_BAD_PACKET_SIZE = -23;
const ERR_INVALID_HANDLE = -24;
const ERR_OPERATION_FAILED = -25;
const ERR_PARAM_OUT_OF_RANGE = -26;
const ERR_PACKET_OUT_OF_SEQUENCE = -27;
const ERR_INVALID_PACKET_HEADER = -28;
const ERR_UNIMPLEMENTED_FUNCTION = -29;
const ERR_TOO_MUCH_DATA = -30;
const ERR_INVALID_DEVICE = -31;
const ERR_UNSUPPORTED_FIRMWARE = -32;
const ERR_BUFFER_TOO_SMALL = -33;
const ERR_NO_DATA = -34;
const ERR_RESOURCE_CONFLICT = -35;
const ERR_NO_EVM = -36;
const ERR_COMMAND_BUSY = -37;
const ERR_ADJ_POWER_FAIL = -38;
const ERR_NOT_ENABLED = -39;
const ERR_I2C_INIT_ERROR = -40;
const ERR_I2C_READ_ERROR = -41;
const ERR_I2C_WRITE_ERROR = -42;
const ERR_I2C_BUSY = -43;
const ERR_I2C_ADDR_NAK = -44;
const ERR_I2C_DATA_NAK = -45;
const ERR_I2C_READ_TIMEOUT = -46;
const ERR_I2C_READ_DATA_TIMEOUT = -47;
const ERR_I2C_READ_COMP_TIMEOUT = -48;
const ERR_I2C_WRITE_TIMEOUT = -49;
const ERR_I2C_WRITE_DATA_TIMEOUT = -50;
const ERR_I2C_WRITE_COMP_TIMEOUT = -51;
const ERR_I2C_NOT_MASTER = -52;
const ERR_I2C_ARBITRATION_LOST = -53;
const ERR_I2C_NO_PULLUP_POWER = -54;
const ERR_SPI_INIT_ERROR = -60;
const ERR_SPI_WRITE_READ_ERROR = -61;
const ERR_DATA_WRITE_ERROR = -70;
const ERR_DATA_READ_ERROR = -71;
const ERR_TIMEOUT = -72;
const ERR_DATA_CRC_FAILED = -73;
const ERR_INVALID_PARAMETER = -74;
const ERR_NOT_INITIALIZED = -75;
const getErrorString = function (code) {
    switch (code) {
        case ERR_OK: return 'No error'; //  0
        case ERR_COM_RX_OVERFLOW: return 'Receiver overflowed'; // -1
        case ERR_COM_RX_BUF_EMPTY: return 'Receive buffer is empty'; // -2
        case ERR_COM_TX_BUF_FULL: return 'Transmit buffer is full'; // -3
        case ERR_COM_TX_STALLED: return 'Transmit is stalled'; // -4
        case ERR_COM_TX_FAILED: return 'Transmit failed'; // -5
        case ERR_COM_OPEN_FAILED: return 'Failed to open communications port'; // -6
        case ERR_COM_PORT_NOT_OPEN: return 'Communications port is not open'; // -7
        case ERR_COM_PORT_IS_OPEN: return 'Communications port is open'; // -8
        case ERR_COM_READ_TIMEOUT: return 'Receive timeout'; // -9
        case ERR_COM_READ_ERROR: return 'Communications port read error'; // -10
        case ERR_COM_WRITE_ERROR: return 'Communications port write error'; // -11
        case ERR_DEVICE_NOT_FOUND: return 'Communications device not found'; // -12
        case ERR_COM_CRC_FAILED: return 'Communications CRC failed'; // -13
        case ERR_INVALID_PORT: return 'Invalid port'; // -20
        case ERR_ADDRESS_OUT_OF_RANGE: return 'Address is out of accepted range'; // -21
        case ERR_INVALID_FUNCTION_CODE: return 'Invalid function code'; // -22
        case ERR_BAD_PACKET_SIZE: return 'Invalid packet size'; // -23
        case ERR_INVALID_HANDLE: return 'Invalid handle'; // -24
        case ERR_OPERATION_FAILED: return 'Operation failed'; // -25
        case ERR_PARAM_OUT_OF_RANGE: return 'Parameter is out of range'; // -26
        case ERR_PACKET_OUT_OF_SEQUENCE: return 'Packet is out of sequence'; // -27
        case ERR_INVALID_PACKET_HEADER: return 'Invalid packet header'; // -28
        case ERR_UNIMPLEMENTED_FUNCTION: return 'Function not implemented'; // -29
        case ERR_TOO_MUCH_DATA: return 'Too much data'; // -30
        case ERR_INVALID_DEVICE: return 'Invalid device'; // -31
        case ERR_UNSUPPORTED_FIRMWARE: return 'Unsupported firmware version'; // -32
        case ERR_BUFFER_TOO_SMALL: return 'Buffer is too small'; // -33
        case ERR_NO_DATA: return 'No data available'; // -34
        case ERR_RESOURCE_CONFLICT: return 'Resource conflict'; // -35
        case ERR_NO_EVM: return 'EVM is required for external power'; // -36
        case ERR_COMMAND_BUSY: return 'Command is busy'; // -37
        case ERR_ADJ_POWER_FAIL: return 'Adjustable power supply failure'; // -38
        case ERR_NOT_ENABLED: return 'Not enabled'; // -39
        case ERR_I2C_INIT_ERROR: return 'I2C initialization failed'; // -40
        case ERR_I2C_READ_ERROR: return 'I2C read error'; // -41
        case ERR_I2C_WRITE_ERROR: return 'I2C write error'; // -42
        case ERR_I2C_BUSY: return 'I2C busy (transfer is pending)'; // -43
        case ERR_I2C_ADDR_NAK: return 'Address not acknowledged (NAK)'; // -44
        case ERR_I2C_DATA_NAK: return 'Data not acknowledged (NAK)'; // -45
        case ERR_I2C_READ_TIMEOUT: return 'Read timeout'; // -46
        case ERR_I2C_READ_DATA_TIMEOUT: return 'Read data timeout'; // -47
        case ERR_I2C_READ_COMP_TIMEOUT: return 'Timeout waiting for read complete'; // -48
        case ERR_I2C_WRITE_TIMEOUT: return 'Write timeout'; // -49
        case ERR_I2C_WRITE_DATA_TIMEOUT: return 'Write data timeout'; // -50
        case ERR_I2C_WRITE_COMP_TIMEOUT: return 'Timeout waiting for write complete'; // -51
        case ERR_I2C_NOT_MASTER: return 'I2C not in Master mode'; // -52
        case ERR_I2C_ARBITRATION_LOST: return 'I2C arbitration lost'; // -53
        case ERR_I2C_NO_PULLUP_POWER: return 'I2C pullups require 3.3V power'; // -54
        case ERR_SPI_INIT_ERROR: return 'SPI initialization failed'; // -60
        case ERR_SPI_WRITE_READ_ERROR: return 'SPI write/read error'; // -61
        case ERR_DATA_WRITE_ERROR: return 'Data write error'; // -70
        case ERR_DATA_READ_ERROR: return 'Data read error'; // -71
        case ERR_TIMEOUT: return 'Operation timeout'; // -72
        case ERR_DATA_CRC_FAILED: return 'Data CRC failed'; // -73
        default:
            if (code > 0) {
                return 'Success'; // any positive value
            }
            break;
    }
};
const INTERRUPT_INT0 = 0; // Interrupt pin INT0
const INTERRUPT_INT1 = 1; // Interrupt pin INT1
const INTERRUPT_INT2 = 2; // Interrupt pin INT2
const INTERRUPT_INT3 = 3; // Interrupt pin INT3
const INTERRUPT_EVM = 4; // Interrupt pin EVM_DETECT
const INTERRUPT_POWER = 5; // Interrupt for power event
const INTERRUPT_ADC = 6; // Interrupt for ADC event
const INTERRUPT_DIGITAL = 7; // Interrupt for Digital Capture event
const INTERRUPT_ASYNC_IO = 8; // Interrupt for asynchronous I/O
const INTERRUPT_CALLBACK_101 = 9; // Callback for Cmd_I2C_ReadInternal
const INTERRUPT_CALLBACK_102 = 10; // Callback for Cmd_I2C_WriteInternal
const INTERRUPT_SOURCES = 11; // Total number of interrupt sources
// Controller Type constants
const CTRLR_UNKNOWN = 0x0000;
const CTRLR_USB2ANY = 0x0001;
const CTRLR_ONEDEMO = 0x0002;
const CTRLR_UNSUPPORTED = 0x0004;
const VERSION_SIZE_IN_BYTES = 4;
const VERSION_TO_DWORD = function (packet, offset) {
    let version = 0;
    for (let i = 0; i < VERSION_SIZE_IN_BYTES; i++) {
        version = (version << 8) | packet[offset + i];
    }
    return version;
};
const MIN_FIRMWARE_REQUIRED = VERSION_TO_DWORD([2, 6, 2, 20], 0);
const CRC8TABLE = [
    0x00, 0x07, 0x0E, 0x09, 0x1C, 0x1B, 0x12, 0x15, 0x38, 0x3F, 0x36, 0x31, 0x24, 0x23, 0x2A, 0x2D, 0x70, 0x77, 0x7E, 0x79, 0x6C, 0x6B, 0x62, 0x65, 0x48, 0x4F, 0x46, 0x41, 0x54, 0x53, 0x5A, 0x5D, 0xE0, 0xE7, 0xEE, 0xE9, 0xFC, 0xFB, 0xF2, 0xF5, 0xD8, 0xDF, 0xD6, 0xD1, 0xC4, 0xC3, 0xCA, 0xCD, 0x90, 0x97, 0x9E,
    0x99, 0x8C, 0x8B, 0x82, 0x85, 0xA8, 0xAF, 0xA6, 0xA1, 0xB4, 0xB3, 0xBA, 0xBD, 0xC7, 0xC0, 0xC9, 0xCE, 0xDB, 0xDC, 0xD5, 0xD2, 0xFF, 0xF8, 0xF1, 0xF6, 0xE3, 0xE4, 0xED, 0xEA, 0xB7, 0xB0, 0xB9, 0xBE, 0xAB, 0xAC, 0xA5, 0xA2, 0x8F, 0x88, 0x81, 0x86, 0x93, 0x94, 0x9D, 0x9A, 0x27, 0x20, 0x29, 0x2E, 0x3B, 0x3C,
    0x35, 0x32, 0x1F, 0x18, 0x11, 0x16, 0x03, 0x04, 0x0D, 0x0A, 0x57, 0x50, 0x59, 0x5E, 0x4B, 0x4C, 0x45, 0x42, 0x6F, 0x68, 0x61, 0x66, 0x73, 0x74, 0x7D, 0x7A, 0x89, 0x8E, 0x87, 0x80, 0x95, 0x92, 0x9B, 0x9C, 0xB1, 0xB6, 0xBF, 0xB8, 0xAD, 0xAA, 0xA3, 0xA4, 0xF9, 0xFE, 0xF7, 0xF0, 0xE5, 0xE2, 0xEB, 0xEC, 0xC1,
    0xC6, 0xCF, 0xC8, 0xDD, 0xDA, 0xD3, 0xD4, 0x69, 0x6E, 0x67, 0x60, 0x75, 0x72, 0x7B, 0x7C, 0x51, 0x56, 0x5F, 0x58, 0x4D, 0x4A, 0x43, 0x44, 0x19, 0x1E, 0x17, 0x10, 0x05, 0x02, 0x0B, 0x0C, 0x21, 0x26, 0x2F, 0x28, 0x3D, 0x3A, 0x33, 0x34, 0x4E, 0x49, 0x40, 0x47, 0x52, 0x55, 0x5C, 0x5B, 0x76, 0x71, 0x78, 0x7F,
    0x6A, 0x6D, 0x64, 0x63, 0x3E, 0x39, 0x30, 0x37, 0x22, 0x25, 0x2C, 0x2B, 0x06, 0x01, 0x08, 0x0F, 0x1A, 0x1D, 0x14, 0x13, 0xAE, 0xA9, 0xA0, 0xA7, 0xB2, 0xB5, 0xBC, 0xBB, 0x96, 0x91, 0x98, 0x9F, 0x8A, 0x8D, 0x84, 0x83, 0xDE, 0xD9, 0xD0, 0xD7, 0xC2, 0xC5, 0xCC, 0xCB, 0xE6, 0xE1, 0xE8, 0xEF, 0xFA, 0xFD, 0xF4,
    0xF3
];
const calculateCRC = function (buf, offset, len) {
    let crc = 0;
    len = len || buf.length;
    for (let i = offset; i < len; i++) {
        crc = CRC8TABLE[buf[i] ^ crc];
    }
    return crc;
};
const concatenateResults = function (result) {
    return Array.prototype.concat.apply([], result);
};
const getResult = function (array) {
    let result = 0;
    const size = PACKET_PAYLOAD + (array[PACKET_PAYLOAD_LEN] || 0);
    for (let i = PACKET_PAYLOAD; i < size; i++) {
        result = (result << 8) | (array[i] & 0xff);
    }
    return result;
};
const getResultLSB = function (array) {
    // little endian
    let result = 0;
    const size = PACKET_PAYLOAD + (array[PACKET_PAYLOAD_LEN] || 0);
    for (let i = size - 1; i >= PACKET_PAYLOAD; i--) {
        result = (result << 8) | (array[i] & 0xff);
    }
    return result;
};
const getPayload = function (array) {
    return array.slice(PACKET_PAYLOAD, PACKET_PAYLOAD + (array[PACKET_PAYLOAD_LEN] || 0));
};
const IUsb2anyEncoderType = new EncoderType('u2aPacket');
class NullUsb2anyEncoder extends Events {
    constructor() {
        super(...arguments);
        this.id = 'nullUsb2anyEncoder';
        this.encoderInputType = IUsb2anyEncoderType;
        this.encoderOutputType = NoopDecoderType;
        this.connectTimeout = 250;
    }
    sendCommandPacket(cmd, payload) {
        throw Error('Null encoder is called.');
    }
    readResponse(forPacket) {
        throw Error('Null encoder is called.');
    }
    addChildDecoder(child) {
    }
    dispose() {
    }
}
const nullUsb2anyEncoder = new NullUsb2anyEncoder();
class Usb2anyCodec extends AbstractMessageBasedDecoder {
    constructor(params) {
        super(params.id || 'u2a', console);
        this.params = params;
        this.isConnected = false;
        this.numPacketsReceived = 0;
        this.packetErrorCount = 0;
        this.consecutiveErrorLimit = DEFAULT_MAX_CONSECUTIVE_ERRORS;
        this.txPacketSeqNum = 1;
        this.rxReceivedPacketSeqNo = 0;
        this.nControllerType = CTRLR_UNKNOWN;
        this.dwFirmwareVersion = 0;
        this.version = '';
        this.controllerName = '';
        this.encoderInputType = IUsb2anyEncoderType;
        this.encoderOutputType = NoopDecoderType;
        this.frameDecoder = new (class extends AbstractFrameDecoder {
            constructor(packetDecoder) {
                super('u2aPacketFrameDecoder', PACKET_IDENTIFIER);
                this.packetDecoder = packetDecoder;
                this.params = {};
            }
            getPacketLength(buffer, offset) {
                return buffer.length - offset < PACKET_HEADER_SIZE ? 0 : buffer[offset + PACKET_PAYLOAD_LEN] + PACKET_HEADER_SIZE;
            }
            decodePacket(packet) {
                return this.packetDecoder.decodePacket(packet);
            }
        })(this);
    }
    get connectTimeout() {
        return this.params.connectTimeout ?? 250;
    }
    /**
     * @hidden
     */
    addChildDecoder(child) {
        // called by CodecRegistry, after deconfigure but before connect
    }
    /**
     * @hidden
     */
    async onConnect(transport) {
        this.transport = transport;
        this.frameDecoder.deconfigure();
        // Since checkFirmware will wait for user's input, it should have no timeout. Hence u2aOpen has one timeout,
        // and the sequence of Interface(s).control has another timeout.
        this.consecutiveErrorLimit = this.params.maxConsecutiveErrors ?? DEFAULT_MAX_CONSECUTIVE_ERRORS;
        this.isConnected = true;
        try {
            await GcPromise.timeout(this.u2aOpen(), this.connectTimeout, 'No response from USB2ANY controller.');
            // Let the logic compare version, prompt user and wait for user's decision, and update firmware if needed. Hence there is no timeout.
            await this.checkFirmware({ detectedFirmwareVersion: this.version, modelID: this.params.id || 'u2a', codec: this, controller: 'usb2any' }, this.params.firmwareCheck);
            return GcPromise.timeout(this.readResponse(this.sendCommandPacket(Command.Cmd_LED_SetState, [2, 0])), this.connectTimeout, 'USB2ANY configure timeout');
        }
        catch (error) {
            this.isConnected = false;
            console.log(error);
            throw error;
        }
    }
    /**
     * @hidden
     */
    async onDisconnect() {
        this.isConnected = false;
        await super.onDisconnect();
        this.rxReceivedPacketSeqNo = 0;
        this.txPacketSeqNum = 1;
        this.packetErrorCount = 0;
        this.nControllerType = CTRLR_UNKNOWN;
        this.transport = undefined;
    }
    decode(data) {
        return this.frameDecoder.detectPackets(data);
    }
    decodePacket(rawData) {
        super.decode(rawData); // must call AbstractMessagedBasedCodec to deal with pending transmissions
        try {
            const nRead = rawData.length;
            if (nRead < PACKET_HEADER_SIZE) {
                this.packetErrorCount++;
                throw Error(getErrorString(ERR_BAD_PACKET_SIZE));
            }
            if (rawData[PACKET_ID] !== PACKET_IDENTIFIER || rawData[PACKET_PAYLOAD_LEN] > MAX_PAYLOAD) {
                // Possible firmware bug causing garbage data to send instead of the expected status packet
                // indicating ADC data is ready. Check if we are using ADC interface before throwing error.
                // TODO we ignore error for a certain case in v2. So far v3 has no idea of adcInterface, what to do here.
                // if (this.adcInterface) {
                // ignore error
                // } else {
                throw Error(getErrorString(ERR_INVALID_PACKET_HEADER));
                // }
            }
            const crc = calculateCRC(rawData, PACKET_PAYLOAD_LEN, rawData[PACKET_PAYLOAD_LEN] + PACKET_HEADER_SIZE);
            if (rawData[PACKET_PEC] !== crc) {
                console.warning('ignoring USB2ANY error: ' + getErrorString(ERR_COM_CRC_FAILED));
                return true;
            }
            const type = rawData[PACKET_TYPE];
            if (type === PAYLOAD_PACKET) {
                this.fireEvent(receivePayloadEventType, { payload: getPayload(rawData) });
            }
            else if (type === INTERRUPT_PACKET) {
                this.fireEvent(receiveInterruptEventType, { payload: getPayload(rawData) });
            }
            else if (type === REPLY_PACKET) {
                this.packetErrorCount = 0;
                this.rxReceivedPacketSeqNo = rawData[PACKET_SEQ_NUM] || this.rxReceivedPacketSeqNo;
                this.addResponse(rawData, rawData[PACKET_COMMAND], rawData[PACKET_SEQ_NUM]);
            }
            else if (type === ERROR_PACKET) {
                const errorCode = rawData[PACKET_STATUS];
                const errorMsg = getErrorString(errorCode - 256) || '';
                this.rxReceivedPacketSeqNo = rawData[PACKET_SEQ_NUM] || this.rxReceivedPacketSeqNo;
                this.addErrorResponse(errorMsg, rawData[PACKET_COMMAND], rawData[PACKET_SEQ_NUM]);
                if (this.transport?.isConnected && this.consecutiveErrorLimit >= 0 && this.packetErrorCount++ >= this.consecutiveErrorLimit) {
                    throw errorMsg;
                }
                console.warning(`USB2ANY error packet received: ${errorMsg} for command ${rawData[PACKET_COMMAND]}, seq# ${rawData[PACKET_SEQ_NUM]}`);
            }
            this.numPacketsReceived++;
            return true;
        }
        catch (e) {
            throw Error('USB2ANY error: ' + e);
        }
    }
    sendCommandPacket(cmd, payload) {
        if (payload.length > MAX_PAYLOAD) {
            throw Error('Too much payload data for a single packet.');
        }
        if (this.txPacketSeqNum === 255) {
            this.txPacketSeqNum = 1; // 0 is reserved for asynchronous packets
        }
        let packet = [
            PACKET_IDENTIFIER, 0, payload.length, COMMAND_PACKET, 0, this.txPacketSeqNum++, 0, cmd
        ];
        packet = packet.concat(payload);
        packet[PACKET_PEC] = calculateCRC(packet, PACKET_PAYLOAD_LEN);
        this.encode(packet);
        return packet;
    }
    async readResponse(forPacket) {
        try {
            return await this.addCommand(forPacket[PACKET_COMMAND], forPacket[PACKET_SEQ_NUM]);
        }
        catch (err) {
            if (!this.isConnected) {
                throw err;
            }
            let errorMsg = err.message || err.toString();
            const MISSING_RESPONSE = 'missing response';
            if (errorMsg.includes(MISSING_RESPONSE)) {
                errorMsg = MISSING_RESPONSE;
            }
            // retry one time
            console.log(`Retrying command due to ${errorMsg} for command ${forPacket[PACKET_COMMAND]}, seq# ${forPacket[PACKET_SEQ_NUM]}`);
            const retryPacket = this.sendCommandPacket(forPacket[PACKET_COMMAND], forPacket.slice(PACKET_PAYLOAD));
            return await this.addCommand(retryPacket[PACKET_COMMAND], retryPacket[PACKET_SEQ_NUM]);
        }
    }
    invokeBSL() {
        return this.readResponse(this.sendCommandPacket(Command.Cmd_InvokeBSL, []));
    }
    async u2aOpen() {
        const controllerTypeResponse = await this.readResponse(this.sendCommandPacket(Command.Cmd_Status_GetControllerType, [0, 0, 0, 0]));
        const responsePacket = await this.readResponse(this.sendCommandPacket(Command.Cmd_FirmwareVersion_Read, [0, 0, 0, 0]));
        const nReceived = responsePacket[PACKET_PAYLOAD_LEN];
        if (nReceived !== VERSION_SIZE_IN_BYTES) {
            this.dwFirmwareVersion = 0;
            this.version = 'UNKNOWN';
        }
        else {
            this.dwFirmwareVersion = VERSION_TO_DWORD(responsePacket, PACKET_PAYLOAD);
            this.version = responsePacket[PACKET_PAYLOAD] + '.' + responsePacket[PACKET_PAYLOAD + 1] + '.' + responsePacket[PACKET_PAYLOAD + 2] + '.' + responsePacket[PACKET_PAYLOAD + 3];
        }
        this.nControllerType = controllerTypeResponse[PACKET_PAYLOAD];
        switch (this.nControllerType) {
            case CTRLR_USB2ANY:
                this.controllerName = 'USB2ANY';
                break;
            case CTRLR_ONEDEMO:
                this.controllerName = 'OneDemo';
                break;
            default:
                this.nControllerType = this.dwFirmwareVersion === 0 ? CTRLR_UNKNOWN : CTRLR_USB2ANY;
                this.controllerName = this.dwFirmwareVersion === 0 ? '<unknown device>' : 'USB2ANY';
                break;
        }
        if (this.dwFirmwareVersion < MIN_FIRMWARE_REQUIRED) {
            this.nControllerType = CTRLR_UNSUPPORTED;
            throw Error('Unsupported USB2ANY controller');
        }
    }
    async ping() {
        await super.ping();
        const pingPromise = this.readResponse(this.sendCommandPacket(Command.Cmd_FirmwareVersion_Read, [0, 0, 0, 0]));
        await GcPromise.timeout(pingPromise, 250, 'Ping failure: no response of firmware version read from ' + this.id);
    }
    /**
     * @hidden
     */
    shouldPauseTransmission(txPacket) {
        const seqNo = txPacket[PACKET_SEQ_NUM];
        if (seqNo) { // non zero sequence number
            let diff = seqNo - this.rxReceivedPacketSeqNo;
            if (diff < 0) {
                diff += 255;
            }
            return diff > (this.params.maxOutstandingCommands || 30); // 0 will block all transmissions, so use default of 30.
        }
        return false;
    }
}

export { Command, IUsb2anyEncoderType, MAX_PAYLOAD, PACKET_COMMAND, PACKET_PAYLOAD, Usb2anyCodec, calculateCRC, concatenateResults, getPayload, getResult, getResultLSB, nullUsb2anyEncoder };
//# sourceMappingURL=Usb2anyCodec.js.map
