import { GcConsole } from '../../gc-core-assets/lib/GcConsole';
import { GcPromise } from '../../gc-core-assets/lib/GcPromise';
import { EncoderType, NoopDecoderType, AbstractMessageBasedDecoder, CompositeEncoderType, AbstractFrameDecoder } from '../../gc-target-configuration/lib/TargetConfiguration';
import { DEFAULT_MAX_CONSECUTIVE_ERRORS } from '../../gc-target-configuration/lib/ICodecAnalogControllerBaseParams';
import { NamedDataRecord, Uint16, Uint32 } from '../../gc-target-configuration/lib/NamedDataRecord';
import { RegisterModelEncoderType } from '../../gc-model-register/lib/RegisterModel';
import { EventType } from '../../gc-core-assets/lib/Events';

/**
 *  Copyright (c) 2024 Texas Instruments Incorporated
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
const deviceAddressChangedEvent = new EventType('onDeviceAddressChanged');
const console = new GcConsole('gc-codec-pmbus');
var USB2GPIOStatus;
(function (USB2GPIOStatus) {
    USB2GPIOStatus[USB2GPIOStatus["STAT_OK"] = 0] = "STAT_OK";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_SUCCESS"] = 0] = "USB2GPIO_SUCCESS";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_RX_OVERFLOW"] = -1] = "USB2GPIO_ERR_SYS_COM_RX_OVERFLOW";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_RX_BUF_EMPTY"] = -2] = "USB2GPIO_ERR_SYS_COM_RX_BUF_EMPTY";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_TX_BUF_FULL"] = -3] = "USB2GPIO_ERR_SYS_COM_TX_BUF_FULL";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_TX_STALLED"] = -4] = "USB2GPIO_ERR_SYS_COM_TX_STALLED";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_TX_FAILED"] = -5] = "USB2GPIO_ERR_SYS_COM_TX_FAILED";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_INVALID_PORT"] = -6] = "USB2GPIO_ERR_SYS_COM_INVALID_PORT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_OPEN_FAILED"] = -7] = "USB2GPIO_ERR_SYS_COM_OPEN_FAILED";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_PORT_NOT_OPEN"] = -8] = "USB2GPIO_ERR_SYS_COM_PORT_NOT_OPEN";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_PORT_IS_OPEN"] = -9] = "USB2GPIO_ERR_SYS_COM_PORT_IS_OPEN";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_READ_TIMEOUT"] = -10] = "USB2GPIO_ERR_SYS_COM_READ_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_READ_ERROR"] = -11] = "USB2GPIO_ERR_SYS_COM_READ_ERROR";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COM_WRITE_ERROR"] = -12] = "USB2GPIO_ERR_SYS_COM_WRITE_ERROR";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_INVALID_HANDLE"] = -13] = "USB2GPIO_ERR_SYS_INVALID_HANDLE";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_BAD_PACKET_SIZE"] = -14] = "USB2GPIO_ERR_SYS_BAD_PACKET_SIZE";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_PACKET_OUT_OF_SEQUENCE"] = -15] = "USB2GPIO_ERR_SYS_PACKET_OUT_OF_SEQUENCE";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_INVALID_PACKET_HEADER"] = -16] = "USB2GPIO_ERR_SYS_INVALID_PACKET_HEADER";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_UNSUPPORTED_FIRMWARE"] = -17] = "USB2GPIO_ERR_SYS_UNSUPPORTED_FIRMWARE";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_NO_EVM"] = -18] = "USB2GPIO_ERR_SYS_NO_EVM";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_INVALID_INTERFACE"] = -19] = "USB2GPIO_ERR_SYS_INVALID_INTERFACE";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_UNKNOWN_STATUS"] = -20] = "USB2GPIO_ERR_SYS_UNKNOWN_STATUS";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_BAD_COMPOSITE_ERROR"] = -21] = "USB2GPIO_ERR_SYS_BAD_COMPOSITE_ERROR";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_OPERATION_FAILED"] = -129] = "USB2GPIO_ERR_OPERATION_FAILED";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_PARAM_OUT_OF_RANGE"] = -130] = "USB2GPIO_ERR_PARAM_OUT_OF_RANGE";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_INVALID_FUNCTION_CODE"] = -131] = "USB2GPIO_ERR_INVALID_FUNCTION_CODE";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_UNIMPLEMENTED_FUNCTION"] = -132] = "USB2GPIO_ERR_UNIMPLEMENTED_FUNCTION";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_NOT_ENABLED"] = -133] = "USB2GPIO_ERR_NOT_ENABLED";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_RESOURCE_CONFLICT"] = -134] = "USB2GPIO_ERR_RESOURCE_CONFLICT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_DEVICE_NOT_FOUND"] = -135] = "USB2GPIO_ERR_DEVICE_NOT_FOUND";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_INVALID_DEVICE"] = -136] = "USB2GPIO_ERR_INVALID_DEVICE";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_COMMAND_BUSY"] = -137] = "USB2GPIO_ERR_COMMAND_BUSY";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_TIMEOUT"] = -138] = "USB2GPIO_ERR_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_DATA_CRC_FAILED"] = -139] = "USB2GPIO_ERR_DATA_CRC_FAILED";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_BUFFER_TOO_SMALL"] = -140] = "USB2GPIO_ERR_BUFFER_TOO_SMALL";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_TOO_MUCH_DATA"] = -141] = "USB2GPIO_ERR_TOO_MUCH_DATA";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_NO_DATA"] = -142] = "USB2GPIO_ERR_NO_DATA";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_DATA_WRITE_ERROR"] = -143] = "USB2GPIO_ERR_DATA_WRITE_ERROR";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_DATA_READ_ERROR"] = -144] = "USB2GPIO_ERR_DATA_READ_ERROR";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_PACKET_SEND"] = -145] = "USB2GPIO_ERR_PACKET_SEND";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_NOT_CONFIGURED"] = -146] = "USB2GPIO_ERR_NOT_CONFIGURED";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_RESOURCE_ACCESS"] = -147] = "USB2GPIO_ERR_RESOURCE_ACCESS";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_RTOS_OP_FAILED"] = -148] = "USB2GPIO_ERR_RTOS_OP_FAILED";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_ALREADY_ENABLED"] = -149] = "USB2GPIO_ERR_ALREADY_ENABLED";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_NOT_ENOUGH_DATA"] = -150] = "USB2GPIO_ERR_NOT_ENOUGH_DATA";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_PARM_WRONG"] = -151] = "USB2GPIO_ERR_PARM_WRONG";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C"] = -768] = "USB2GPIO_ERR_I2C";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_INIT_ERROR"] = -769] = "USB2GPIO_ERR_I2C_INIT_ERROR";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_READ_ERROR"] = -770] = "USB2GPIO_ERR_I2C_READ_ERROR";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_WRITE_ERROR"] = -771] = "USB2GPIO_ERR_I2C_WRITE_ERROR";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_BUSY"] = -772] = "USB2GPIO_ERR_I2C_BUSY";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_DATA_SIZE"] = -773] = "USB2GPIO_ERR_I2C_DATA_SIZE";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_ADDR_NAK"] = -774] = "USB2GPIO_ERR_I2C_ADDR_NAK";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_DATA_NAK"] = -775] = "USB2GPIO_ERR_I2C_DATA_NAK";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_CLOCK_LOW_TIMEOUT"] = -776] = "USB2GPIO_ERR_I2C_CLOCK_LOW_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_READ_TIMEOUT"] = -777] = "USB2GPIO_ERR_I2C_READ_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_READ_DATA_TIMEOUT"] = -778] = "USB2GPIO_ERR_I2C_READ_DATA_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_READ_COMP_TIMEOUT"] = -779] = "USB2GPIO_ERR_I2C_READ_COMP_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_WRITE_TIMEOUT"] = -780] = "USB2GPIO_ERR_I2C_WRITE_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_WRITE_DATA_TIMEOUT"] = -781] = "USB2GPIO_ERR_I2C_WRITE_DATA_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_WRITE_COMP_TIMEOUT"] = -782] = "USB2GPIO_ERR_I2C_WRITE_COMP_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_NOT_MASTER"] = -783] = "USB2GPIO_ERR_I2C_NOT_MASTER";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_ARBITRATION_LOST"] = -784] = "USB2GPIO_ERR_I2C_ARBITRATION_LOST";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_NO_PULLUP_POWER"] = -785] = "USB2GPIO_ERR_I2C_NO_PULLUP_POWER";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_BAD_SLAVE_ADDRESS"] = -786] = "USB2GPIO_ERR_I2C_BAD_SLAVE_ADDRESS";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_I2C_NO_PULLUPS"] = -787] = "USB2GPIO_ERR_I2C_NO_PULLUPS";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_FLASH"] = -1024] = "USB2GPIO_ERR_FLASH";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_FLASH_ERASE_ERROR"] = -1025] = "USB2GPIO_ERR_FLASH_ERASE_ERROR";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_FLASH_WRITE_ERROR"] = -1026] = "USB2GPIO_ERR_FLASH_WRITE_ERROR";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SYS_COMMAND"] = -1280] = "USB2GPIO_ERR_SYS_COMMAND";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS"] = -2304] = "USB2GPIO_ERR_SMBUS";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_INVALID_BUSSPEED"] = -2305] = "USB2GPIO_ERR_SMBUS_INVALID_BUSSPEED";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_INVALID_CLKLOW_TIMEOUT"] = -2306] = "USB2GPIO_ERR_SMBUS_INVALID_CLKLOW_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_INVALID_DATA"] = -2307] = "USB2GPIO_ERR_SMBUS_INVALID_DATA";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_DATA_SIZE"] = -2308] = "USB2GPIO_ERR_SMBUS_DATA_SIZE";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_INVALID_PEC"] = -2309] = "USB2GPIO_ERR_SMBUS_INVALID_PEC";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_TIMEOUT"] = -2310] = "USB2GPIO_ERR_SMBUS_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_MASTER_ARBLOST"] = -2311] = "USB2GPIO_ERR_SMBUS_MASTER_ARBLOST";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_MASTER_ADDR_NACK"] = -2312] = "USB2GPIO_ERR_SMBUS_MASTER_ADDR_NACK";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_MASTER_CMDID_NACK"] = -2313] = "USB2GPIO_ERR_SMBUS_MASTER_CMDID_NACK";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_MASTER_DATA_NACK"] = -2314] = "USB2GPIO_ERR_SMBUS_MASTER_DATA_NACK";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_MASTER_CLKLOW_TIMEOUT"] = -2315] = "USB2GPIO_ERR_SMBUS_MASTER_CLKLOW_TIMEOUT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_MASTER_ERROR"] = -2316] = "USB2GPIO_ERR_SMBUS_MASTER_ERROR";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SMBUS_STATE_UNKNOWN"] = -2317] = "USB2GPIO_ERR_SMBUS_STATE_UNKNOWN";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_PMBUS"] = -4096] = "USB2GPIO_ERR_PMBUS";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SCRIPT"] = -5632] = "USB2GPIO_ERR_SCRIPT";
    USB2GPIOStatus[USB2GPIOStatus["USB2GPIO_ERR_SCRIPT_PARAM_ERROR"] = -5633] = "USB2GPIO_ERR_SCRIPT_PARAM_ERROR";
})(USB2GPIOStatus || (USB2GPIOStatus = {}));
var PACKET_TYPE;
(function (PACKET_TYPE) {
    PACKET_TYPE[PACKET_TYPE["COMMAND"] = 1] = "COMMAND";
    PACKET_TYPE[PACKET_TYPE["DATA"] = 2] = "DATA";
    PACKET_TYPE[PACKET_TYPE["STATUS"] = 3] = "STATUS";
    PACKET_TYPE[PACKET_TYPE["INTERRUPT"] = 4] = "INTERRUPT";
    PACKET_TYPE[PACKET_TYPE["SCRIPT_DATA"] = 5] = "SCRIPT_DATA";
    PACKET_TYPE[PACKET_TYPE["SCRIPT_INTERRUPT"] = 7] = "SCRIPT_INTERRUPT";
})(PACKET_TYPE || (PACKET_TYPE = {}));
var COMMANDS;
(function (COMMANDS) {
    COMMANDS[COMMANDS["USB2GPIO_SYS_FIRMWARE_ID"] = 257] = "USB2GPIO_SYS_FIRMWARE_ID";
    COMMANDS[COMMANDS["USB2GPIO_SYS_SET_BOARDNAME"] = 258] = "USB2GPIO_SYS_SET_BOARDNAME";
    COMMANDS[COMMANDS["USB2GPIO_SYS_GET_BOARDNAME"] = 259] = "USB2GPIO_SYS_GET_BOARDNAME";
    COMMANDS[COMMANDS["USB2GPIO_SYS_BSL"] = 260] = "USB2GPIO_SYS_BSL";
    COMMANDS[COMMANDS["USB2GPIO_SYS_ERASE_FLASH"] = 261] = "USB2GPIO_SYS_ERASE_FLASH";
    COMMANDS[COMMANDS["USB2GPIO_SYS_SET_PULL_UP_RES_SELECT"] = 262] = "USB2GPIO_SYS_SET_PULL_UP_RES_SELECT";
    COMMANDS[COMMANDS["USB2GPIO_SYS_GET_PULL_UP_RES_SELECT"] = 263] = "USB2GPIO_SYS_GET_PULL_UP_RES_SELECT";
    COMMANDS[COMMANDS["USB2GPIO_SYS_SAVE_CURRENTCONFIG2FLASH"] = 264] = "USB2GPIO_SYS_SAVE_CURRENTCONFIG2FLASH";
    COMMANDS[COMMANDS["USB2GPIO_SYS_GET_CONFIGFROMFLASH"] = 265] = "USB2GPIO_SYS_GET_CONFIGFROMFLASH";
    COMMANDS[COMMANDS["USB2GPIO_SYS_ENABLE_PAMB_BSL"] = 266] = "USB2GPIO_SYS_ENABLE_PAMB_BSL";
    COMMANDS[COMMANDS["SMBUS_SET_BUSSPEED"] = 513] = "SMBUS_SET_BUSSPEED";
    COMMANDS[COMMANDS["SMBUS_GET_BUSSPEED"] = 514] = "SMBUS_GET_BUSSPEED";
    COMMANDS[COMMANDS["SMBUS_SET_CLOCK_LOW_TIMEOUT"] = 515] = "SMBUS_SET_CLOCK_LOW_TIMEOUT";
    COMMANDS[COMMANDS["SMBUS_GET_CLOCK_LOW_TIMEOUT"] = 516] = "SMBUS_GET_CLOCK_LOW_TIMEOUT";
    COMMANDS[COMMANDS["SMBUS_ENABLE_PEC"] = 517] = "SMBUS_ENABLE_PEC";
    COMMANDS[COMMANDS["SMBUS_GET_PEC_STATUS"] = 518] = "SMBUS_GET_PEC_STATUS";
    COMMANDS[COMMANDS["SMBUS_QUICK_COMMAND"] = 519] = "SMBUS_QUICK_COMMAND";
    COMMANDS[COMMANDS["SMBUS_SEND_BYTE"] = 520] = "SMBUS_SEND_BYTE";
    COMMANDS[COMMANDS["SMBUS_RECEIVE_BYTE"] = 521] = "SMBUS_RECEIVE_BYTE";
    COMMANDS[COMMANDS["SMBUS_WRITE_BYTE"] = 522] = "SMBUS_WRITE_BYTE";
    COMMANDS[COMMANDS["SMBUS_READ_BYTE"] = 523] = "SMBUS_READ_BYTE";
    COMMANDS[COMMANDS["SMBUS_WRITE_WORD"] = 524] = "SMBUS_WRITE_WORD";
    COMMANDS[COMMANDS["SMBUS_READ_WORD"] = 525] = "SMBUS_READ_WORD";
    COMMANDS[COMMANDS["SMBUS_WRITE_32"] = 526] = "SMBUS_WRITE_32";
    COMMANDS[COMMANDS["SMBUS_READ_32"] = 527] = "SMBUS_READ_32";
    COMMANDS[COMMANDS["SMBUS_WRITE_64"] = 528] = "SMBUS_WRITE_64";
    COMMANDS[COMMANDS["SMBUS_READ_64"] = 529] = "SMBUS_READ_64";
    COMMANDS[COMMANDS["SMBUS_WRITE_BLOCK"] = 530] = "SMBUS_WRITE_BLOCK";
    COMMANDS[COMMANDS["SMBUS_READ_BLOCK"] = 531] = "SMBUS_READ_BLOCK";
    COMMANDS[COMMANDS["SMBUS_PROCESS_CALL"] = 532] = "SMBUS_PROCESS_CALL";
    COMMANDS[COMMANDS["SMBUS_PROCESS_CALL_BLOCK"] = 533] = "SMBUS_PROCESS_CALL_BLOCK";
    COMMANDS[COMMANDS["SMBUS_READ_BUS_STATE"] = 534] = "SMBUS_READ_BUS_STATE";
    COMMANDS[COMMANDS["SMBUS_SIMULATE_CLOCK_LOW_TIMEOUT"] = 535] = "SMBUS_SIMULATE_CLOCK_LOW_TIMEOUT";
    COMMANDS[COMMANDS["PMBUS_ENABLE_ALERT_INT"] = 769] = "PMBUS_ENABLE_ALERT_INT";
    COMMANDS[COMMANDS["PMBUS_IS_ALERT_ENABLED"] = 770] = "PMBUS_IS_ALERT_ENABLED";
    COMMANDS[COMMANDS["PMBUS_GET_ALERT_PIN_STATUS"] = 771] = "PMBUS_GET_ALERT_PIN_STATUS";
    COMMANDS[COMMANDS["PMBUS_GET_ARA"] = 772] = "PMBUS_GET_ARA";
    COMMANDS[COMMANDS["PMBUS_SET_CONTROL"] = 773] = "PMBUS_SET_CONTROL";
    COMMANDS[COMMANDS["PMBUS_GET_CONTROL"] = 774] = "PMBUS_GET_CONTROL";
    COMMANDS[COMMANDS["PMBUS_EXTENDED_WRITE_BYTE"] = 775] = "PMBUS_EXTENDED_WRITE_BYTE";
    COMMANDS[COMMANDS["PMBUS_EXTENDED_READ_BYTE"] = 776] = "PMBUS_EXTENDED_READ_BYTE";
    COMMANDS[COMMANDS["PMBUS_EXTENDED_WRITE_WORD"] = 777] = "PMBUS_EXTENDED_WRITE_WORD";
    COMMANDS[COMMANDS["PMBUS_EXTENDED_READ_WORD"] = 778] = "PMBUS_EXTENDED_READ_WORD";
    COMMANDS[COMMANDS["PMBUS_GROUP_COMMAND"] = 779] = "PMBUS_GROUP_COMMAND";
    COMMANDS[COMMANDS["PMBUS_ZONE_READ_BYTE"] = 780] = "PMBUS_ZONE_READ_BYTE";
    COMMANDS[COMMANDS["PMBUS_ZONE_READ_WORD"] = 781] = "PMBUS_ZONE_READ_WORD";
    COMMANDS[COMMANDS["I2C_WRITE"] = 1025] = "I2C_WRITE";
    COMMANDS[COMMANDS["I2C_READ"] = 1026] = "I2C_READ";
    COMMANDS[COMMANDS["I2C_WRITE_READ"] = 1027] = "I2C_WRITE_READ";
    COMMANDS[COMMANDS["BURST_I2C_WRITE"] = 1028] = "BURST_I2C_WRITE";
    COMMANDS[COMMANDS["BURST_I2C_READ"] = 1029] = "BURST_I2C_READ";
    COMMANDS[COMMANDS["BURST_I2C_WRITE_READ"] = 1030] = "BURST_I2C_WRITE_READ";
    COMMANDS[COMMANDS["SCRIPT_START_EXECUTION"] = 1281] = "SCRIPT_START_EXECUTION";
    COMMANDS[COMMANDS["SCRIPT_RESUME_EXECUTION"] = 1282] = "SCRIPT_RESUME_EXECUTION";
    COMMANDS[COMMANDS["SCRIPT_RESUME_FROM_NEXTFRAME"] = 1283] = "SCRIPT_RESUME_FROM_NEXTFRAME";
    COMMANDS[COMMANDS["SCRIPT_STOP_EXECUTION"] = 1284] = "SCRIPT_STOP_EXECUTION";
    COMMANDS[COMMANDS["SCRIPT_GET_EXECUTION_STATUS"] = 1285] = "SCRIPT_GET_EXECUTION_STATUS";
    COMMANDS[COMMANDS["SCRIPT_SET_SCRIPT_NAME"] = 1286] = "SCRIPT_SET_SCRIPT_NAME";
    COMMANDS[COMMANDS["SCRIPT_GET_SCRIPT_NAME"] = 1287] = "SCRIPT_GET_SCRIPT_NAME";
    COMMANDS[COMMANDS["SCRIPT_BUFFER_WRITE"] = 1288] = "SCRIPT_BUFFER_WRITE";
    COMMANDS[COMMANDS["SCRIPT_BUFFER_READ_PLAIN"] = 1289] = "SCRIPT_BUFFER_READ_PLAIN";
    COMMANDS[COMMANDS["SCRIPT_BUFFER_READ_FIFO"] = 1290] = "SCRIPT_BUFFER_READ_FIFO";
    COMMANDS[COMMANDS["SCRIPT_BUFFER_RESET"] = 1291] = "SCRIPT_BUFFER_RESET";
    COMMANDS[COMMANDS["SCRIPT_BUFFER_SIZE_MODIFY"] = 1292] = "SCRIPT_BUFFER_SIZE_MODIFY";
    COMMANDS[COMMANDS["SCRIPT_BUFFER_SIZE_READ"] = 1293] = "SCRIPT_BUFFER_SIZE_READ";
    COMMANDS[COMMANDS["SCRIPT_IF_READ_BYTE_STORE"] = 1536] = "SCRIPT_IF_READ_BYTE_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_READ_BYTE"] = 1537] = "SCRIPT_IF_READ_BYTE";
    COMMANDS[COMMANDS["SCRIPT_IF_READ_WORD_STORE"] = 1538] = "SCRIPT_IF_READ_WORD_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_READ_WORD"] = 1539] = "SCRIPT_IF_READ_WORD";
    COMMANDS[COMMANDS["SCRIPT_IF_READ_32_STORE"] = 1540] = "SCRIPT_IF_READ_32_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_READ_32"] = 1541] = "SCRIPT_IF_READ_32";
    COMMANDS[COMMANDS["SCRIPT_IF_READ_64_STORE"] = 1542] = "SCRIPT_IF_READ_64_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_READ_64"] = 1543] = "SCRIPT_IF_READ_64";
    COMMANDS[COMMANDS["SCRIPT_IF_READ_BLOCK_STORE"] = 1544] = "SCRIPT_IF_READ_BLOCK_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_READ_BLOCK"] = 1545] = "SCRIPT_IF_READ_BLOCK";
    COMMANDS[COMMANDS["SCRIPT_IF_PROCESS_CALL_HEADER_STORE"] = 1546] = "SCRIPT_IF_PROCESS_CALL_HEADER_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_PROCESS_CALL_HEADER"] = 1547] = "SCRIPT_IF_PROCESS_CALL_HEADER";
    COMMANDS[COMMANDS["SCRIPT_IF_PROCESS_CALL_BUFFER_STORE"] = 1548] = "SCRIPT_IF_PROCESS_CALL_BUFFER_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_PROCESS_CALL_BUFFER"] = 1549] = "SCRIPT_IF_PROCESS_CALL_BUFFER";
    COMMANDS[COMMANDS["SCRIPT_IF_PROCESS_CALL_BLOCK_HEADER_STORE"] = 1550] = "SCRIPT_IF_PROCESS_CALL_BLOCK_HEADER_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_PROCESS_CALL_BLOCK_HEADER"] = 1551] = "SCRIPT_IF_PROCESS_CALL_BLOCK_HEADER";
    COMMANDS[COMMANDS["SCRIPT_IF_PROCESS_CALL_BLOCK_BUFFER_STORE"] = 1552] = "SCRIPT_IF_PROCESS_CALL_BLOCK_BUFFER_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_PROCESS_CALL_BLOCK_BUFFER"] = 1553] = "SCRIPT_IF_PROCESS_CALL_BLOCK_BUFFER";
    COMMANDS[COMMANDS["SCRIPT_IF_I2C_READ_STORE"] = 1554] = "SCRIPT_IF_I2C_READ_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_I2C_READ"] = 1555] = "SCRIPT_IF_I2C_READ";
    COMMANDS[COMMANDS["SCRIPT_IF_I2C_WRITE_READ_HEADER_STORE"] = 1556] = "SCRIPT_IF_I2C_WRITE_READ_HEADER_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_I2C_WRITE_READ_HEADER"] = 1557] = "SCRIPT_IF_I2C_WRITE_READ_HEADER";
    COMMANDS[COMMANDS["SCRIPT_IF_I2C_WRITE_READ_BUFFER_STORE"] = 1558] = "SCRIPT_IF_I2C_WRITE_READ_BUFFER_STORE";
    COMMANDS[COMMANDS["SCRIPT_IF_I2C_WRITE_READ_BUFFER"] = 1559] = "SCRIPT_IF_I2C_WRITE_READ_BUFFER";
    COMMANDS[COMMANDS["SCRIPT_MISC_SET_SLAVEADDRESS"] = 1793] = "SCRIPT_MISC_SET_SLAVEADDRESS";
    COMMANDS[COMMANDS["SCRIPT_MISC_SET_TX_OFFSET"] = 1794] = "SCRIPT_MISC_SET_TX_OFFSET";
    COMMANDS[COMMANDS["SCRIPT_MISC_SET_FAILURE_RETRY_COUNT"] = 1795] = "SCRIPT_MISC_SET_FAILURE_RETRY_COUNT";
    //! is used upon failure of the frame
    COMMANDS[COMMANDS["SCRIPT_MISC_DELAY_US"] = 1796] = "SCRIPT_MISC_DELAY_US";
    COMMANDS[COMMANDS["SCRIPT_MISC_CLEAR_RX_FIFO"] = 1797] = "SCRIPT_MISC_CLEAR_RX_FIFO";
    COMMANDS[COMMANDS["SCRIPT_MISC_PUSH_RX_FIFO_TO_PC"] = 1798] = "SCRIPT_MISC_PUSH_RX_FIFO_TO_PC";
    //! interrupt packet
    COMMANDS[COMMANDS["SCRIPT_MISC_STOP_SCRIPT"] = 1799] = "SCRIPT_MISC_STOP_SCRIPT";
    COMMANDS[COMMANDS["SCRIPT_MISC_SETGLOBALPTR_ADDRNACK"] = 1800] = "SCRIPT_MISC_SETGLOBALPTR_ADDRNACK";
    COMMANDS[COMMANDS["SCRIPT_MISC_SETGLOBALPTR_CMDIDNACK"] = 1801] = "SCRIPT_MISC_SETGLOBALPTR_CMDIDNACK";
    COMMANDS[COMMANDS["SCRIPT_MISC_SETGLOBALPTR_DATANACK"] = 1802] = "SCRIPT_MISC_SETGLOBALPTR_DATANACK";
    COMMANDS[COMMANDS["SCRIPT_MISC_SETGLOBALPTR_PECNACK"] = 1803] = "SCRIPT_MISC_SETGLOBALPTR_PECNACK";
    COMMANDS[COMMANDS["I2CBUSMON_START"] = 2049] = "I2CBUSMON_START";
    COMMANDS[COMMANDS["I2CBUSMON_GET_FIFO_INFO"] = 2050] = "I2CBUSMON_GET_FIFO_INFO";
    COMMANDS[COMMANDS["I2CBUSMON_GET_DATA_FROM_FIFO"] = 2051] = "I2CBUSMON_GET_DATA_FROM_FIFO";
    COMMANDS[COMMANDS["I2CBUSMON_STOP"] = 2052] = "I2CBUSMON_STOP";
})(COMMANDS || (COMMANDS = {}));
const PUllUpResistorOptions = [
    'Open Drain',
    '499 Ω',
    '1 kΩ',
    '333 Ω',
    '2.2 kΩ',
    '407 Ω',
    '688 Ω',
    '289 Ω'
];
var ResistorMask;
(function (ResistorMask) {
    ResistorMask[ResistorMask["Data"] = 7] = "Data";
    ResistorMask[ResistorMask["Clock"] = 112] = "Clock";
    ResistorMask[ResistorMask["Alert"] = 128] = "Alert";
})(ResistorMask || (ResistorMask = {}));
var ResistorValue;
(function (ResistorValue) {
    ResistorValue[ResistorValue["OpenDrain"] = 0] = "OpenDrain";
    ResistorValue[ResistorValue["Ohm499"] = 1] = "Ohm499";
    ResistorValue[ResistorValue["Ohm1000"] = 2] = "Ohm1000";
    ResistorValue[ResistorValue["Ohm333"] = 3] = "Ohm333";
    ResistorValue[ResistorValue["Ohm2200"] = 4] = "Ohm2200";
    ResistorValue[ResistorValue["Ohm407"] = 5] = "Ohm407";
    ResistorValue[ResistorValue["Ohm688"] = 6] = "Ohm688";
    ResistorValue[ResistorValue["Ohm289"] = 7] = "Ohm289";
})(ResistorValue || (ResistorValue = {}));
const RESISTOR_VALUE_MASK = 0x7;
class PMBusCommandHeader extends NamedDataRecord {
    constructor() {
        super(...arguments);
        this.littleEndian = true;
    }
}
PMBusCommandHeader.fieldDescriptors = [
    ['signature', Uint16],
    ['packetType', Uint16],
    ['status', Uint32],
    ['packetLength', Uint32],
    ['sequenceNumber', Uint16],
    ['payloadLength', Uint16],
    ['interfaceUnitType', Uint16],
    ['command', Uint16]
];
const SIGNATURE = 0xd402;
const PACKET_IDENTIFIER = SIGNATURE & 0xff;
const PACKET_IDENTIFIER2 = (SIGNATURE >> 8) & 0xff;
const PACKET_HEADER_SIZE = PMBusCommandHeader.getSize();
const MAX_PACKET_SIZE = 512;
const HID_RESERVED = 2;
const MAX_PAYLOAD = MAX_PACKET_SIZE - PACKET_HEADER_SIZE - HID_RESERVED;
const MIN_FIRMWARE_REQUIRED = '2.1';
const PMBusEncoderType = new EncoderType('pmBusPacket');
class NullPMBusEncoder {
    constructor() {
        this.noop = async () => {
            return;
        };
        this.error = async () => {
            throw Error('Method not implemented');
        };
        this.id = 'nullPMBusEncoder';
        this.encoderInputType = PMBusEncoderType;
        this.encoderOutputType = NoopDecoderType;
        this.sendByte = this.noop;
        this.writeByte = this.noop;
        this.writeWord = this.noop;
        this.writeBlock = this.noop;
        this.receiveByte = this.error;
        this.readByte = this.error;
        this.readWord = this.error;
        this.readBlock = this.error;
        this.getAlertPinStatus = this.error;
    }
    addChildDecoder(child) {
    }
    dispose() {
    }
}
const nullPMBusEncoder = new NullPMBusEncoder();
/**
 * Codec connecting the register model, or a custom codec, to the USB Interface Adapter (USB2GPIO2), for reading and writing
 * registers over PMBus or SMBus.
 */
class PMBusCodec extends AbstractMessageBasedDecoder {
    constructor(params) {
        super(params.id || 'pmbus', console, params.maxOutstandingCommands);
        this.params = params;
        this.isConnected = false;
        this.packetErrorCount = 0;
        this.consecutiveErrorLimit = DEFAULT_MAX_CONSECUTIVE_ERRORS;
        this.txPacketSeqNum = 1;
        this.packetHeader = PMBusCommandHeader.create();
        this.encoderInputType = new CompositeEncoderType(PMBusEncoderType, RegisterModelEncoderType);
        this.encoderOutputType = NoopDecoderType;
        this.frameDecoder = new (class extends AbstractFrameDecoder {
            constructor(packetDecoder) {
                super('pmbusPacketFrameDecoder', PACKET_IDENTIFIER, PACKET_IDENTIFIER2);
                this.packetDecoder = packetDecoder;
                this.params = {};
            }
            getPacketLength(buffer, offset) {
                if (buffer.length - offset < PACKET_HEADER_SIZE) {
                    return 0; // need more data to determine the length
                }
                const header = PMBusCommandHeader.create(buffer.slice(offset, offset + PACKET_HEADER_SIZE));
                return header.payloadLength + PACKET_HEADER_SIZE;
            }
            decodePacket(packet) {
                return this.packetDecoder.decodePacket(packet);
            }
        })(this);
        this.supportedBusSpeeds = [100, 400, 1000, 3400];
        this.packetHeader.signature = SIGNATURE;
        this.packetHeader.packetType = PACKET_TYPE.COMMAND;
    }
    async readValue(info) {
        const deviceAddress = this.targetDecoder?.getDeviceAddressForRegister(info);
        const wordSize = info.nBytes * 8;
        if (wordSize === 16 || wordSize === 32) {
            return await this.readWord(info.addr, { wordSize, deviceAddress });
        }
        if (wordSize === 8) {
            return await this.readByte(info.addr, { deviceAddress });
        }
        throw Error(`Invalid register info: ${wordSize} bit register reads are not supported.`);
    }
    async writeValue(info, value) {
        const deviceAddress = this.targetDecoder?.getDeviceAddressForRegister(info);
        const wordSize = info.nBytes * 8;
        if (wordSize === 16 || wordSize === 32) {
            return await this.writeWord(info.addr, value, { wordSize, deviceAddress });
        }
        if (wordSize === 8) {
            return await this.writeByte(info.addr, value, { deviceAddress });
        }
        throw Error(`Invalid register info: ${wordSize} bit register writes are not supported.`);
    }
    /**
     * @hidden
     */
    addChildDecoder(child) {
        if (child.getDeviceAddressForRegister) {
            this.targetDecoder = child;
        }
    }
    /**
     * @hidden
     */
    async onConnect(transport) {
        this.frameDecoder.deconfigure();
        this.deviceAddress = this.params.deviceAddress;
        this.transport = transport;
        this.consecutiveErrorLimit = this.params.maxConsecutiveErrors ?? DEFAULT_MAX_CONSECUTIVE_ERRORS;
        this.isConnected = true;
        const timeout = this.params.connectTimeout ?? 250;
        try {
            const version = await GcPromise.timeout(this.getVersion(), timeout * 600, 'Timeout waiting for the first response from the USB Interface Adapter');
            // Let the logic compare version, prompt user and wait for user's decision, and update firmware if needed. Hence there is no timeout.
            await this.checkFirmware({ detectedFirmwareVersion: version, modelID: this.params.id, codec: this, controller: 'pmBus' }, this.params.firmwareCheck);
            if (versionToDWord(version) < versionToDWord(MIN_FIRMWARE_REQUIRED)) {
                throw Error(`Firmware v${version} of the USB Interface Adapter is not supported.  It needs to be at least v${MIN_FIRMWARE_REQUIRED}`);
            }
            await GcPromise.timeout(Promise.all([
                this.setPullUpResistor(ResistorMask.Alert, parseResistorValue(this.params.alertPullUpResistor ?? 0)),
                this.setPullUpResistor(ResistorMask.Clock, parseResistorValue(this.params.clockPullUpResistor ?? 0)),
                this.setPullUpResistor(ResistorMask.Data, parseResistorValue(this.params.dataPullUpResistor ?? 0)),
                this.setBusSpeed(this.params.busSpeed ?? 100),
                this.enablePec(this.params.pecEnabled ?? false),
                this.params.clockTimeout ? this.setClockTimeout(this.params.clockTimeout) : Promise.resolve()
            ]), timeout, 'Timeout initializing the USB Interface Adapter');
            if (this.params.verifyCommandCode) {
                const scanAddresses = this.params.scanDeviceAddresses || (typeof this.deviceAddress === 'number' ? `0x${this.deviceAddress.toString(16)}` : undefined);
                if (scanAddresses) {
                    const devices = await this.scanForDevices(scanAddresses);
                    if (devices.length < 1) {
                        throw Error(`Failed to verify a suitable device at the following address(es)=${scanAddresses}`);
                    }
                    // use the first one found, if more that one device detected.  This way the order
                    // deviceAddress ranges to be scanned matters, even though we don't stop scanning when
                    // first one is found.
                    if (this.deviceAddress !== devices[0]) {
                        this.deviceAddress = devices[0];
                        this.fireEvent(deviceAddressChangedEvent, { deviceAddress: this.deviceAddress });
                    }
                }
                else {
                    throw Error('Missing property scanDeviceAddresses or deviceAddress, one of which is required if verifyCommandCode is specified.');
                }
            }
        }
        catch (error) {
            this.isConnected = false;
            console.log(error.message || error.toString());
            throw error;
        }
    }
    /**
     * @hidden
     */
    async onDisconnect() {
        this.isConnected = false;
        await super.onDisconnect();
        this.txPacketSeqNum = 1;
        this.packetErrorCount = 0;
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
                throw Error('Invalid packet size');
            }
            const header = PMBusCommandHeader.create(rawData.slice(0, PACKET_HEADER_SIZE));
            if (header.signature !== SIGNATURE || header.payloadLength > MAX_PAYLOAD) {
                throw Error('Invalid packet header');
            }
            const payload = rawData.slice(PACKET_HEADER_SIZE);
            if (header.payloadLength !== payload.length) {
                throw Error('Invalid packet size');
            }
            switch (header.packetType) {
                case PACKET_TYPE.STATUS:
                    if (header.status === USB2GPIOStatus.STAT_OK) {
                        this.addResponse(payload, header.command, header.sequenceNumber);
                    }
                    else {
                        const status = String.fromCharCode(...payload);
                        this.addErrorResponse(status, header.command, header.sequenceNumber);
                    }
                    break;
                case PACKET_TYPE.DATA:
                    this.addResponse(payload, header.command, header.sequenceNumber);
                    break;
                default:
                    throw Error(`Unsupported packet type ${header.packetType} received.`);
            }
            return true;
        }
        catch (e) {
            throw Error('PMBus error: ' + e);
        }
    }
    addErrorResponse(errorMsg, command, sequenceNumber) {
        super.addErrorResponse(errorMsg, command, sequenceNumber);
        if (this.transport?.isConnected && this.consecutiveErrorLimit >= 0 && this.packetErrorCount++ >= this.consecutiveErrorLimit) {
            throw errorMsg; // this will force a disconnect from the transport.
        }
        console.warning(`PMBus packet error received: ${errorMsg}`);
    }
    async sendCommandPacket(cmd, payload, retryCount = 0) {
        if (!this.isConnected) {
            throw Error('This operation is not supported when the target is not connected.');
        }
        if (payload.length > MAX_PAYLOAD) {
            throw Error('Too much payload data for a single packet.');
        }
        this.packetHeader.command = cmd;
        this.packetHeader.payloadLength = payload.length;
        this.packetHeader.packetLength = payload.length + PACKET_HEADER_SIZE;
        this.txPacketSeqNum++;
        if (this.txPacketSeqNum > 255) {
            this.txPacketSeqNum = 1; // 0 is reserved for asynchronous packets
        }
        this.packetHeader.sequenceNumber = this.txPacketSeqNum;
        this.encode([...this.packetHeader.asUint8Array, ...payload]);
        try {
            return await this.addCommand(cmd, this.txPacketSeqNum);
        }
        catch (err) {
            if (!this.isConnected || retryCount > 0) {
                throw err;
            }
            let errorMsg = err.message || err.toString();
            const MISSING_RESPONSE = 'missing response';
            if (errorMsg.includes(MISSING_RESPONSE)) {
                errorMsg = MISSING_RESPONSE;
            }
            // retry one time
            console.log(`Retrying command due to ${errorMsg} for command ${cmd}`);
            return this.sendCommandPacket(cmd, payload, retryCount + 1);
        }
    }
    async sendByte(value, options = {}) {
        await this.sendCommandPacket(COMMANDS.SMBUS_SEND_BYTE, [
            +(options.deviceAddress ?? this.deviceAddress ?? 0),
            value
        ]);
    }
    async writeByte(commandCode, value, options = {}) {
        await this.sendCommandPacket(COMMANDS.SMBUS_WRITE_BYTE, [
            +(options.deviceAddress ?? this.deviceAddress ?? 0),
            commandCode,
            value & 0xFF
        ]);
    }
    async writeWord(commandCode, value, options = {}) {
        const wordSize = options.wordSize ?? this.params.wordSize ?? 16;
        const buffer = new Uint8Array(wordSize / 8);
        const data = new DataView(buffer.buffer);
        const littleEndian = (options.dataEndian ?? 'little') === 'little';
        let operation = COMMANDS.SMBUS_WRITE_WORD;
        if (wordSize === 16) {
            data.setUint16(0, value, littleEndian);
        }
        else if (wordSize === 32) {
            operation = COMMANDS.SMBUS_WRITE_32;
            data.setUint32(0, value, littleEndian);
        }
        else {
            throw Error(`Invalid parameter.  ${wordSize} bit writes are not supported.`);
        }
        await this.sendCommandPacket(operation, [
            +(options.deviceAddress ?? this.deviceAddress ?? 0),
            commandCode,
            ...buffer
        ]);
    }
    async writeBlock(commandCode, value, options = {}) {
        await this.sendCommandPacket(COMMANDS.SMBUS_WRITE_BLOCK, [
            +(options.deviceAddress ?? this.deviceAddress ?? 0),
            commandCode,
            value.length,
            ...value
        ]);
    }
    async receiveByte(options = {}) {
        const payload = await this.sendCommandPacket(COMMANDS.SMBUS_RECEIVE_BYTE, [
            +(options.deviceAddress ?? this.deviceAddress ?? 0)
        ]);
        return payload[1];
    }
    async readByte(commandCode, options = {}) {
        const payload = await this.sendCommandPacket(COMMANDS.SMBUS_READ_BYTE, [
            +(options.deviceAddress ?? this.deviceAddress ?? 0),
            commandCode
        ]);
        return payload[2];
    }
    async readWord(commandCode, options = {}) {
        const wordSize = options.wordSize ?? this.params.wordSize ?? 16;
        if (wordSize !== 16 && wordSize !== 32) {
            throw Error(`Invalid parameter:  ${wordSize} bit reads are not supported.`);
        }
        const operation = wordSize === 16 ? COMMANDS.SMBUS_READ_WORD : COMMANDS.SMBUS_READ_32;
        const payload = await this.sendCommandPacket(operation, [
            +(options.deviceAddress ?? this.deviceAddress ?? 0),
            commandCode
        ]);
        const data = new DataView((new Uint8Array(payload)).buffer);
        const littleEndian = (options.dataEndian ?? 'little') === 'little';
        return wordSize === 16 ? data.getUint16(2, littleEndian) : data.getUint32(2, littleEndian);
    }
    async readBlock(commandCode, options = {}) {
        const payload = await this.sendCommandPacket(COMMANDS.SMBUS_READ_BLOCK, [
            +(options.deviceAddress ?? this.deviceAddress ?? 0),
            commandCode
        ]);
        return payload.slice(1, 1 + payload[0]);
    }
    async getAlertPinStatus() {
        const payload = await this.sendCommandPacket(COMMANDS.PMBUS_GET_ALERT_PIN_STATUS, []);
        return payload[0] === 1;
    }
    /**
     * Change wether packet encoding (PEC) is used or not.
     *
     * @param isEnable true to enable PEC, and false to disable PEC.
     */
    async enablePec(isEnable) {
        await this.sendCommandPacket(COMMANDS.SMBUS_ENABLE_PEC, [isEnable ? 1 : 0]);
    }
    /**
     * Get the state for packet encoding (PEC) is enabled or not.
     *
     * @returns a promise that resolves to true if PEC is enabled, and false otherwise.
     */
    async getPecStatus() {
        const payload = await this.sendCommandPacket(COMMANDS.SMBUS_GET_PEC_STATUS, []);
        return payload[0] === 1;
    }
    /**
     * Change the bus speed.
     *
     * @param busSpeed seed of the bus in KHz.
     */
    async setBusSpeed(busSpeed) {
        const busSpeedIndex = this.supportedBusSpeeds.findIndex(speed => speed === busSpeed) ?? -1;
        if (busSpeedIndex === -1) {
            throw Error(`Invalid argument.  Bus speed = ${busSpeed} is not supported.`);
        }
        await this.sendCommandPacket(COMMANDS.SMBUS_SET_BUSSPEED, [busSpeedIndex]);
    }
    /**
     * Retrieve the bus speed.
     *
     * @returns a promise resolving to the speed of the bus in KHz.
     */
    async getBusSpeed() {
        const payload = await this.sendCommandPacket(COMMANDS.SMBUS_GET_BUSSPEED, []);
        return this.supportedBusSpeeds[payload[0]];
    }
    async ping() {
        await super.ping();
        await GcPromise.timeout(this.getBusSpeed(), 250, `Ping failure: no response of get bus speed read from ${this.id}`);
    }
    /**
     * Retrieve the firmware version of the USB Interface Adapter (USB2GPIO2).
     *
     * @returns a promise resolving to the firmware version.
     */
    async getVersion() {
        const result = await this.sendCommandPacket(COMMANDS.USB2GPIO_SYS_FIRMWARE_ID, []);
        let message = String.fromCharCode(...result);
        message = message.split('\0')[0];
        const version = message.match(/^(?:\w*\s+)?(?:v)?((?:\d+\.)+\d+)$/)?.[1] ?? '';
        return version;
    }
    /**
     * Retrieve the board name of the USB Interface Adapter.
     *
     * @returns a promise resolving to the name of the board.
     */
    async getBoardName() {
        const result = await this.sendCommandPacket(COMMANDS.USB2GPIO_SYS_GET_BOARDNAME, []);
        const boardName = String.fromCharCode(...result);
        return boardName;
    }
    /**
     * Retrieve the pull-up resistor value for the Alert, Clock, or Data line.
     *
     * @param resistorMask which Alert, Clock, or Data line to get the pull-up resistor value for.
     * @returns the pull-up resistor value.
     */
    async getPullUpResistor(resistorMask) {
        const result = (await this.sendCommandPacket(COMMANDS.USB2GPIO_SYS_GET_PULL_UP_RES_SELECT, [resistorMask]))[1] ^ resistorMask;
        switch (resistorMask) {
            case ResistorMask.Alert:
                return (result >> 5) & RESISTOR_VALUE_MASK;
            case ResistorMask.Clock:
                return (result >> 4) & RESISTOR_VALUE_MASK;
            default:
                return result & RESISTOR_VALUE_MASK;
        }
    }
    /**
     * Change the pull-up resistor value for the Alert, Clock, or Data line.
     *
     * @params resistorMask which Alert, Clock, or Data line to set the resistor for.
     * @params the resistor value to use.
     */
    async setPullUpResistor(resistorMask, resistorValue) {
        if (resistorValue > RESISTOR_VALUE_MASK || resistorValue < 0) {
            throw Error(`Invalid Argument: resistorValue = ${resistorValue} must be between 0 and ${RESISTOR_VALUE_MASK}.`);
        }
        if (resistorMask === ResistorMask.Alert && resistorValue !== ResistorValue.Ohm2200 && resistorValue !== ResistorValue.OpenDrain) {
            throw Error(`Invalid Argument: resistorValue = ${resistorValue} must be either 0 or ${ResistorValue.Ohm2200}.`);
        }
        let value = resistorValue;
        switch (resistorMask) {
            case ResistorMask.Alert:
                value = resistorValue << 5;
                break;
            case ResistorMask.Clock:
                value = resistorValue << 4;
                break;
        }
        await this.sendCommandPacket(COMMANDS.USB2GPIO_SYS_SET_PULL_UP_RES_SELECT, [resistorMask, value ^ resistorMask]);
    }
    /**
     * Retrieve the clock timeout for the bus.
     *
     * @returns the clock timeout of the bus.
     */
    async getClockTimeout() {
        return (await this.sendCommandPacket(COMMANDS.SMBUS_GET_CLOCK_LOW_TIMEOUT, []))[0];
    }
    /**
     * Change the bus clock timeout value
     *
     * @params timeoutInMilliseconds new clock timeout in milliseconds (ms).
     */
    async setClockTimeout(timeoutInMilliseconds) {
        if (timeoutInMilliseconds < 0 || timeoutInMilliseconds > 255) {
            throw Error('Invalid argument: timeout (in ms) must be between 0 and 255.');
        }
        await this.sendCommandPacket(COMMANDS.SMBUS_SET_CLOCK_LOW_TIMEOUT, [timeoutInMilliseconds]);
    }
    /**
     * Scan the bus to find suitable devices.  A range of devices addresses are specified as a
     * start device address and an end device address delimited by two dots (..) and is inclusive.
     * The deviceAddress parameter is a comma delimited list of singled device address, and/or ranges.
     * For example, the deviceAddress="0x1,3..0x10,0x15,0x20..37" represent address 1, 3 to 16, 21,
     * 32 to 37 inclusive. Device addresses specified in hex must be prefixed with '0x'.
     *
     * @param deviceAddresses the address ranges to scan to find suitable devices.
     * @param verifyOptions the options for verifying a suitable device.
     * @returns a list of device addresses where suitable devices were found.
     */
    async scanForDevices(deviceAddresses, verifyOptions = {}) {
        const originalConsecutiveErrorLimit = this.consecutiveErrorLimit;
        this.consecutiveErrorLimit = -1; // temporarily suppress consecutive errors from causing disconnect
        try {
            const options = {
                verifyReadOption: 'block',
                verifyCommandCode: 0xAD,
                ...this.params,
                ...verifyOptions
            };
            const deviceAddressList = convertRangesToList(deviceAddresses);
            let promises = [];
            const verifyFalse = () => {
                return false;
            };
            if (options.verifyReadOption === 'block') {
                let verifyFunction = (result) => true;
                if (options.verifyResult) {
                    if (typeof options.verifyResult !== 'string') {
                        throw Error('Invalid argument: verifyResult must be a string for block read verification.');
                    }
                    if (options.verifyResult.startsWith('0x')) {
                        const value = BigInt(options.verifyResult);
                        if (options.verifyMask) {
                            if (typeof options.verifyMask !== 'string' || options.verifyMask.length !== options.verifyResult.length) {
                                throw Error('Invalid argument: verifyMask must be a string with the same length as verifyResult');
                            }
                        }
                        const mask = options.verifyMask ? BigInt(options.verifyMask) : -1n;
                        verifyFunction = (result) => {
                            const resultValue = result.reduce((value, byte) => value << 8n | BigInt(byte), 0n);
                            return (resultValue & mask) === value;
                        };
                    }
                    else {
                        const verifyRegEx = new RegExp(options.verifyResult);
                        verifyFunction = (result) => {
                            const message = String.fromCharCode(...result);
                            const ok = message.match(verifyRegEx);
                            return ok !== null;
                        };
                    }
                }
                promises = deviceAddressList.map(deviceAddress => this.readBlock(options.verifyCommandCode, { deviceAddress }).then(verifyFunction).catch(verifyFalse));
            }
            else {
                let verifyNumber = (result) => true;
                if (options.verifyResult) {
                    if (isNaN(+options.verifyResult)) {
                        throw Error(`Invalid argument: verifyResult ${options.verifyResult} is not a number`);
                    }
                    if (isNaN(+(options.verifyMask ?? 0))) {
                        throw Error(`Invalid argument: verifyMask ${options.verifyMask} is not a number`);
                    }
                    const mask = +(options.verifyMask ?? -1);
                    const value = +options.verifyResult & mask;
                    verifyNumber = (result) => {
                        return (result & mask) === value;
                    };
                }
                switch (options.verifyReadOption) {
                    case 'byte':
                        promises = deviceAddressList.map(deviceAddress => this.readByte(options.verifyCommandCode, { deviceAddress }).then(verifyNumber).catch(verifyFalse));
                        break;
                    case 'word':
                        promises = deviceAddressList.map(deviceAddress => this.readWord(options.verifyCommandCode, { ...options, deviceAddress }).then(verifyNumber).catch(verifyFalse));
                        break;
                }
            }
            const results = await Promise.all(promises);
            return deviceAddressList.filter((_, i) => results[i]);
        }
        finally {
            this.consecutiveErrorLimit = originalConsecutiveErrorLimit;
        }
    }
}
// Convert a string containing comma delimited ranges; for example, '0x01..0x15,0x17,0x20..0x30', into a single list of values.
function convertRangesToList(ranges) {
    return ranges.split(',').map(range => {
        range = range.trim();
        // test for required hex digit (1 to 3 digits only) optionally followed by .. and another hex digit.
        const limits = range.match(/^((?:0x)?[0-9a-fA-F]+)(?:\.\.((?:0x)?[0-9a-fA-F]+))?$/);
        if (limits === null) {
            throw Error(`Invalid argument: ${range} is not a valid device address or range of device addresses`);
        }
        return { from: +limits[1], to: +(limits[2] ?? limits[1]) };
    }).reduce((result, range) => {
        if (range.from > 127 || range.to > 127) {
            throw Error(`Invalid argument: scanning for device address from 0x${range.from.toString(16)} to 0x${range.to.toString(16)} is out of range.`);
        }
        const increment = range.from > range.to ? -1 : 1;
        const count = Math.abs(range.from - range.to) + 1;
        result.push(...new Array(count).fill(range.from).map((start, i) => start + increment * i));
        return result;
    }, []);
}
const VERSION_SIZE_IN_BYTES = 4;
function versionToDWord(version) {
    let result = 0;
    const segments = version.split('.');
    for (let i = 0; i < VERSION_SIZE_IN_BYTES; i++) {
        result = (result << 8) | +(segments[i] ?? 0);
    }
    return result;
}
function parseResistorValue(resistorValue) {
    let value = resistorValue;
    if (!value) {
        // value is undefined, null, '', or 0
        return ResistorValue.OpenDrain;
    }
    if (typeof value === 'number') {
        if (value > 1000) {
            value = value / 1000;
        }
        value = value.toString(10) + (value < 10 ? ' kΩ' : ' Ω');
    }
    if (typeof value === 'string') {
        const index = PUllUpResistorOptions.findIndex((label) => label === value);
        if (index >= 0) {
            return index;
        }
    }
    throw Error(`Invalid property value=${resistorValue} for a pull-up resistor.`);
}

export { PMBusCodec, PMBusEncoderType, ResistorMask, ResistorValue, deviceAddressChangedEvent, nullPMBusEncoder };
//# sourceMappingURL=PMBusCodec.js.map
