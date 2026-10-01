/*
 *  Copyright (C) 2026 Texas Instruments Incorporated
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * \internal
 * \file Dap_Core.h
 * \brief DAP Core Layer - Internal header
 *
 * DAP Core layer implements the DAP protocol logic including command parsing,
 * response building, and state machine management.
 *
 * Core layer uses unified DAP_ERROR_* codes from Dap.h.
 * Translates internal errors to DAP_PROTOCOL_ERROR_* codes when building
 * error responses to send to the host.
 *
 * \note This is an internal header file. Applications should use Dap.h instead.
 */

#ifndef DAP_CORE_H
#define DAP_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "dap_link/Dap_Link.h"

/* ========================================================================== */
/*                 Public Definitions and Macros                              */
/* ========================================================================== */

/**
 * \anchor Dap_Core_FrameConstants
 * \name DAP Frame structure constants
 * @{
 */

/** \brief Frame start byte */
#define DAP_FRAME_START_BYTE     (0xEDU)
/** \brief Frame end byte */
#define DAP_FRAME_END_BYTE       (0x9EU)
/** \brief CRC initial value */
#define DAP_FRAME_CRC_INIT_VALUE (0x66U)

/** @} */

/**
 * \anchor Dap_Core_FrameOffsets
 * \name DAP Frame structure byte offsets
 * @{
 */

/** \brief Offset of start byte in frame */
#define DAP_FRAME_OFFSET_START            (0U)
/** \brief Offset of command/response byte in frame */
#define DAP_FRAME_OFFSET_CMD              (1U)
/** \brief Offset of payload length field in frame */
#define DAP_FRAME_OFFSET_LENGTH           (2U)
/** \brief Minimum frame size (start + cmd + len(1) + end) */
#define DAP_FRAME_MIN_SIZE_BYTES          (4U)
/** \brief Frame header size without payload (start + cmd) */
#define DAP_FRAME_HEADER_SIZE_BYTES       (2U)
/** \brief Frame trailer size */
#define DAP_FRAME_TRAILER_SIZE_BYTES      (1U)
/** \brief Fixed bytes in frame (header + trailer) */
#define DAP_FRAME_FIXED_SIZE_BYTES        (DAP_FRAME_HEADER_SIZE_BYTES + DAP_FRAME_TRAILER_SIZE_BYTES)
/** \brief Maximum size of length field */
#define DAP_FRAME_MAX_LENGTH_SIZE_BYTES   (3U)
/** \brief Minimum bytes needed to decode payload length (start + cmd + len) */
#define DAP_FRAME_MIN_HEADER_DECODE_BYTES (3U)

/** @} */

/**
 * \anchor Dap_Core_PayloadLength
 * \name Payload length encoding constants
 * @{
 */

/** \brief 1-byte payload length minimum */
#define DAP_PAYLOAD_1B_MIN    (0U)
/** \brief 1-byte payload length maximum */
#define DAP_PAYLOAD_1B_MAX    (127U)
/** \brief 2-byte payload length minimum */
#define DAP_PAYLOAD_2B_MIN    (128U)
/** \brief 2-byte payload length maximum */
#define DAP_PAYLOAD_2B_MAX    (16383U)
/** \brief 3-byte payload length minimum */
#define DAP_PAYLOAD_3B_MIN    (16384U)
/** \brief 3-byte payload length maximum */
#define DAP_PAYLOAD_3B_MAX    (4194303U)
/** \brief 2-byte payload length offset */
#define DAP_PAYLOAD_2B_OFFSET (0x8000U)
/** \brief 3-byte payload length offset */
#define DAP_PAYLOAD_3B_OFFSET (0xC00000U)

/** @} */

/**
 * \anchor Dap_Core_CommandCodes
 * \name DAP Command codes
 * @{
 */

/** \brief Get capabilities command */
#define DAP_CMD_GET_CAPABILITIES   (0x01U)
/** \brief List sensors command */
#define DAP_CMD_LIST_SENSORS       (0x02U)
/** \brief Configure pipeline command */
#define DAP_CMD_CONFIGURE_PIPELINE (0x03U)
/** \brief List models command */
#define DAP_CMD_LIST_MODELS        (0x04U)
/** \brief Remove model command (not supported) */
#define DAP_CMD_REMOVE_MODEL       (0x05U)
/** \brief Start model upload command (not supported) */
#define DAP_CMD_START_MODEL_UPLOAD (0x06U)
/** \brief End model upload command (not supported) */
#define DAP_CMD_END_MODEL_UPLOAD   (0x07U)
/** \brief Start streaming command */
#define DAP_CMD_START_STREAMING    (0x08U)
/** \brief Stop streaming command */
#define DAP_CMD_STOP_STREAMING     (0x09U)
/** \brief List inferencing values command */
#define DAP_CMD_LIST_INF_VALUES    (0x0AU)
/** \brief Read property command */
#define DAP_CMD_READ_PROPERTY      (0x0CU)
/** \brief Write property command */
#define DAP_CMD_WRITE_PROPERTY     (0x0DU)
/** \brief List properties command */
#define DAP_CMD_LIST_PROPERTIES    (0x0EU)
/** \brief Send data command */
#define DAP_CMD_SEND_DATA          (0x10U)

/** @} */

/**
 * \anchor Dap_Core_ResponseCodes
 * \name DAP Response codes
 * @{
 */

/** \brief Error response */
#define DAP_RESP_ERROR              (0x00U)
/** \brief Get capabilities response */
#define DAP_RESP_GET_CAPABILITIES   (0x01U)
/** \brief List sensors response */
#define DAP_RESP_LIST_SENSORS       (0x02U)
/** \brief Configure pipeline response */
#define DAP_RESP_CONFIGURE_PIPELINE (0x03U)
/** \brief List models response */
#define DAP_RESP_LIST_MODELS        (0x04U)
/** \brief Remove model response */
#define DAP_RESP_REMOVE_MODEL       (0x05U)
/** \brief Start model upload response */
#define DAP_RESP_START_MODEL_UPLOAD (0x06U)
/** \brief End model upload response */
#define DAP_RESP_END_MODEL_UPLOAD   (0x07U)
/** \brief Start streaming response */
#define DAP_RESP_START_STREAMING    (0x08U)
/** \brief Stop streaming response */
#define DAP_RESP_STOP_STREAMING     (0x09U)
/** \brief List inferencing values response */
#define DAP_RESP_LIST_INF_VALUES    (0x0AU)
/** \brief Read property response */
#define DAP_RESP_READ_PROPERTY      (0x0CU)
/** \brief Write property response */
#define DAP_RESP_WRITE_PROPERTY     (0x0DU)
/** \brief List properties response */
#define DAP_RESP_LIST_PROPERTIES    (0x0EU)
/** \brief Receive data response */
#define DAP_RESP_RECEIVE_DATA       (0x10U)

/** @} */

/**
 * \anchor Dap_Core_DataChannels
 * \name DAP Data channel identifiers
 * @{
 */

/** \brief Sensor signal data channel */
#define DAP_CHANNEL_SENSOR_SIGNAL (0x01U)
/** \brief Inference signal data channel */
#define DAP_CHANNEL_INF_SIGNAL    (0x03U)
/** \brief Inference result data channel */
#define DAP_CHANNEL_INF_RESULT    (0x04U)
/** \brief Inference value data channel */
#define DAP_CHANNEL_INF_VALUE     (0x05U)
/** \brief Inference log data channel */
#define DAP_CHANNEL_INF_LOG       (0x06U)

/** @} */

/**
 * \anchor Dap_Core_ProtocolErrors
 * \name DAP Protocol error numbers (sent to host)
 * @{
 */

/** \brief Unsupported command error */
#define DAP_PROTOCOL_ERROR_UNSUPPORTED_CMD    (0x01U)
/** \brief Unknown command error */
#define DAP_PROTOCOL_ERROR_UNKNOWN_CMD        (0x02U)
/** \brief Invalid start byte */
#define DAP_PROTOCOL_ERROR_INVALID_START_BYTE (0x03U)
/** \brief Invalid end byte */
#define DAP_PROTOCOL_ERROR_INVALID_END_BYTE   (0x04U)
/** \brief Invalid payload error */
#define DAP_PROTOCOL_ERROR_INVALID_PAYLOAD    (0x05U)
/** \brief Invalid CRC error */
#define DAP_PROTOCOL_ERROR_INVALID_CRC        (0x06U)

/** @} */

/**
 * \brief Forward declaration of DAP instance type
 */
typedef struct Dap_InstanceTag Dap_InstanceType;

/* ========================================================================== */
/*                 Public Functions                                           */
/* ========================================================================== */

/**
 * \brief Process received frame
 *
 * Validates the received frame, dispatches to the appropriate command
 * handler, and sends the response.
 *
 * \param[in] instancePtr Pointer to DAP instance
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Core_ProcessFrame(Dap_InstanceType *instancePtr);

/**
 * \brief De-initialize core layer
 *
 * \param[in] linkInstancePtr Pointer to DAP link instance
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Core_DeInit(Dap_Link_InstanceType *linkInstancePtr);

/**
 * \brief Decode payload length from variable-length encoding
 *
 * Decodes the payload length field according to DAP protocol:
 * - 1 byte: 0-127 (0x00-0x7F)
 * - 2 bytes: 128-16383 (0x80xx-0xBFxx)
 * - 3 bytes: 16384-4194303 (0xC0xxxx-0xFFFFFF)
 *
 * \param[in]  bufferPtr     Pointer to length field bytes
 * \param[in]  bufferLen     Available bytes in buffer
 * \param[out] payloadLenPtr Decoded payload length
 * \param[out] headerLenPtr  Number of bytes consumed by length field
 *
 * \return DAP_ERROR_NONE on success, DAP_ERROR_INVALID_PARAMS on failure
 */
sint32 Dap_Core_DecodePayloadLength(const uint8 *bufferPtr, uint32 bufferLen, uint32 *payloadLenPtr,
                                    uint32 *headerLenPtr);

/**
 * \brief Send stream header for continuous streaming
 *
 * Sends the stream header: [START] + [CMD] + [TOTAL_LENGTH]
 * Called once at the start of a streaming session.
 *
 * \param[in] linkInstancePtr  Pointer to DAP link instance
 * \param[in] channel          Data channel identifier
 * \param[in] totalPayloadLen  Total expected payload length for entire stream
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Core_SendStreamHeader(Dap_Link_InstanceType *linkInstancePtr, uint8 channel, uint32 totalPayloadLen);

/**
 * \brief Send a raw sample packet during continuous streaming
 *
 * Sends raw bytes without framing: [sensor_id] + [seq] + [data] + [padding]
 *
 * \param[in] linkInstancePtr Pointer to DAP link instance
 * \param[in] packetPtr       Pointer to sample packet data
 * \param[in] packetLenBytes  Length of sample packet in bytes
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Core_SendStreamSample(Dap_Link_InstanceType *linkInstancePtr, uint8 *packetPtr, uint32 packetLenBytes);
/**
 * \brief Send stream end byte
 *
 * Sends the stream termination byte: [END]
 * Called to terminate a streaming session.
 *
 * \param[in] linkInstancePtr Pointer to DAP link instance
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Core_SendStreamEnd(Dap_Link_InstanceType *linkInstancePtr);

#ifdef __cplusplus
}
#endif

#endif /* DAP_CORE_H */
