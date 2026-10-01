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
 * \file Dap_Link.h
 * \brief DAP Link Layer - Internal header
 *
 * DAP Link layer abstracts UART communication using MCU SDK HAL APIs.
 * The link layer is split into separate Tx and Rx sub-layers to enable
 * independent operation in OS task contexts.
 *
 * Link layer uses DAP_ERROR_* codes from Dap.h for internal error handling.
 * Focuses on hardware-level errors: HW_BUSY, HW_TIMEOUT, BUFFER_OVERFLOW,
 * UNSUPPORTED_MODE.
 *
 * \note This is an internal header file. Applications should use Dap.h instead.
 */

#ifndef DAP_LINK_H
#define DAP_LINK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"
#include "Uart_Hal.h"

/* ========================================================================== */
/*                 Public Definitions and Macros                              */
/* ========================================================================== */

/**
 * \anchor Dap_Link_BufferConfig
 * \name DAP Link buffer configuration
 * @{
 */

/** \brief Default buffer size in bytes */
#define DAP_LINK_BUFFER_SIZE_BYTES  (200U)
/** \brief Buffer alignment for DMA operations */
#define DAP_LINK_BUFFER_ALIGN_BYTES (4U)

/** @} */

/* ========================================================================== */
/*                 Public Typedefs                                            */
/* ========================================================================== */

/**
 * \brief DAP Link operation mode
 *
 * DMA mode is the primary operation mode. Interrupt mode support
 * is reserved for future implementation.
 */
typedef enum
{
    DAP_LINK_MODE_INTERRUPT, /**< Interrupt mode operation */
    DAP_LINK_MODE_DMA,       /**< DMA mode operation */
    DAP_LINK_MODE_MAX        /**< Maximum enum value for bounds checking */
} Dap_Link_ModeType;

/**
 * \brief DAP Link Tx state
 */
typedef enum
{
    DAP_LINK_TX_STATE_IDLE,        /**< Idle, ready for transmission */
    DAP_LINK_TX_STATE_TRANSMITTING /**< Transmitting data */
} Dap_Link_TxStateType;

/**
 * \brief DAP Link Rx state
 */
typedef enum
{
    DAP_LINK_RX_STATE_IDLE,       /**< Idle, waiting for data */
    DAP_LINK_RX_STATE_BUFFERING,  /**< Waiting to receive a complete frame */
    DAP_LINK_RX_STATE_FRAME_READY /**< Frame ready for processing */
} Dap_Link_RxStateType;

/**
 * \brief DAP Frame information structure
 */
typedef struct
{
    /** \brief Data buffer */
    uint8  Buffer[DAP_LINK_BUFFER_SIZE_BYTES];
    /** \brief Total frame length */
    uint32 Len;
} Dap_Link_Frame;

/**
 * \brief DAP Link initialization parameters
 */
typedef struct
{
    /** \brief Pointer to UART HAL instance */
    Uart_Hal_InstanceType *UartInstancePtr;
    /** \brief Link Tx operation mode */
    Dap_Link_ModeType      LinkTxMode;
    /** \brief Link Rx operation mode */
    Dap_Link_ModeType      LinkRxMode;
} Dap_Link_InitParamsType;

/**
 * \brief DAP Link Tx instance structure
 */
typedef struct
{
    /** \brief Operation mode */
    Dap_Link_ModeType             Mode;
    /** \brief Transmit frame */
    Dap_Link_Frame                Frame;
    /** \brief Transmit state */
    volatile Dap_Link_TxStateType State;
} Dap_Link_TxInstanceType;

/**
 * \brief DAP Link Rx instance structure
 */
typedef struct
{
    /** \brief Operation mode */
    Dap_Link_ModeType             Mode;
    /** \brief Receive frame */
    Dap_Link_Frame                Frame;
    /** \brief Receive state */
    volatile Dap_Link_RxStateType State;
    /** \brief Expected total frame length after header decoded */
    uint32                        ExpectedFrameLen;
    /** \brief TRUE when payload length has been decoded from header */
    boolean                       HeaderDecoded;
} Dap_Link_RxInstanceType;

/**
 * \brief DAP Link instance structure (contains both Tx and Rx)
 */
typedef struct Dap_Link_InstanceTag
{
    /** \brief Pointer to UART HAL instance */
    Uart_Hal_InstanceType  *UartInstancePtr;
    /** \brief Transmit instance */
    Dap_Link_TxInstanceType TxInstance;
    /** \brief Receive instance */
    Dap_Link_RxInstanceType RxInstance;
    /** \brief Initialization flag */
    boolean                 IsInitialized;
    /** \brief Last protocol error code sent to host */
    volatile uint32         LastProtocolError;
} Dap_Link_InstanceType;

/* ========================================================================== */
/*                 Public Functions - Common Link APIs                        */
/* ========================================================================== */

/**
 * \brief Set default link initialization parameters
 *
 * \param[out] paramsPtr Pointer to initialization parameters structure
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_InitParamsSetDefault(Dap_Link_InitParamsType *paramsPtr);

/**
 * \brief Initialize link layer and UART hardware
 *
 * This function initializes the UART hardware internally, so the application
 * does not need to call Uart_Hal_Init() separately. The UART configuration
 * is provided via the UartConfig field in the initialization parameters.
 *
 * \note The UART instance pointer provided in paramsPtr must remain valid
 *       for the entire lifetime of the DAP Link instance.
 *
 * \param[out] instancePtr Pointer to link layer instance structure
 * \param[in]  paramsPtr   Pointer to initialization parameters
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_Init(Dap_Link_InstanceType *instancePtr, const Dap_Link_InitParamsType *paramsPtr);

/**
 * \brief De-initialize link layer
 *
 * \param[in] instancePtr Pointer to link layer instance
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_DeInit(Dap_Link_InstanceType *instancePtr);

/* ========================================================================== */
/*                 Public Functions - Convenience Wrappers                    */
/* ========================================================================== */

/**
 * \brief Send data frame
 *
 * Initiates transmission using the data already in the TxInstance Frame buffer.
 * The TxInstance.Frame.Buffer and TxInstance.Frame.Len must be populated before
 * calling this function.
 *
 * \param[in] instancePtr Pointer to link layer instance (TxInstance.Frame must be set)
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_Send(Dap_Link_InstanceType *instancePtr);

/**
 * \brief Send raw bytes from provided buffer
 *
 * Sends raw data directly via UART without using the TX frame buffer.
 * Used for streaming mode where data is sent without per-packet framing.
 * Waits for transmission to complete before returning.
 *
 * \param[in] instancePtr Pointer to link layer instance
 * \param[in] dataPtr     Pointer to data to send
 * \param[in] sizeInBytes Number of bytes to send
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_SendRaw(Dap_Link_InstanceType *instancePtr, uint8 *dataPtr, uint32 sizeInBytes);

/**
 * \brief Start receiving data frame
 *
 * Clears RxInstance Frame buffer and initiates reception.
 * The RxInstance.Frame.Buffer must be allocated before calling this function.
 *
 * \param[in] instancePtr Pointer to link layer instance
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_StartReceive(Dap_Link_InstanceType *instancePtr);

/**
 * \brief Check if transmit is complete
 *
 * \param[in]  instancePtr   Pointer to link layer instance
 * \param[out] isCompletePtr Pointer to store completion status
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_IsTxComplete(Dap_Link_InstanceType *instancePtr, boolean *isCompletePtr);

/**
 * \brief Check if receive is idle
 *
 * \param[in]  instancePtr Pointer to link layer instance
 * \param[out] isIdlePtr   Pointer to store idle status
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_IsRxIdle(Dap_Link_InstanceType *instancePtr, boolean *isIdlePtr);

/**
 * \brief Wait for transmit to be ready
 *
 * When DAP_LINK_CFG_TX_WAIT_FOR_COMPLETE is enabled, this function polls until
 * the previous transmission completes or timeout occurs. Otherwise, it
 * returns immediately with an error if a transmission is in progress.
 *
 * \param[in] instancePtr Pointer to link layer instance
 *
 * \return DAP_ERROR_NONE on success
 * \retval DAP_ERROR_LINK_TIMEOUT if timeout waiting for TX to complete
 * \retval DAP_ERROR_HW_BUSY if TX is busy (when wait is disabled)
 */
sint32 Dap_Link_WaitForTxReady(Dap_Link_InstanceType *instancePtr);

/**
 * \brief Reset receive operation and frame
 *
 * \param[in] instancePtr Pointer to link layer instance
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_ResetRx(Dap_Link_InstanceType *instancePtr);

/**
 * \brief Reset transmit operation and frame
 *
 * \param[in] instancePtr Pointer to link layer instance
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_ResetTx(Dap_Link_InstanceType *instancePtr);

/**
 * \brief Check if a complete frame is ready for processing
 *
 * \param[in]  instancePtr     Pointer to link layer instance
 * \param[out] isFrameReadyPtr Pointer to store frame ready status
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_IsFrameReady(const Dap_Link_InstanceType *instancePtr, boolean *isFrameReadyPtr);

/* ========================================================================== */
/*                 Public Functions - Frame Access APIs                       */
/* ========================================================================== */

/**
 * \brief Get RX frame data (read-only access)
 *
 * Provides const pointer to received frame data for Core layer to process.
 *
 * \param[in]  instancePtr   Pointer to link layer instance
 * \param[out] bufferPtrPtr  Receives const pointer to RX buffer
 * \param[out] lengthPtr     Receives frame length in bytes
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_GetRxFrameData(const Dap_Link_InstanceType *instancePtr, const uint8 **bufferPtrPtr, uint32 *lengthPtr);

/**
 * \brief Get TX frame buffer for writing
 *
 * Provides writable pointer to TX buffer for Core layer to build response.
 * After populating buffer, Core must call Dap_Link_SetTxFrameLength().
 *
 * \param[in]  instancePtr   Pointer to link layer instance
 * \param[out] bufferPtrPtr  Receives pointer to TX buffer (writable)
 * \param[out] maxLengthPtr  Receives maximum buffer size in bytes
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_GetTxFrameBuffer(Dap_Link_InstanceType *instancePtr, uint8 **bufferPtrPtr, uint32 *maxLengthPtr);

/**
 * \brief Set TX frame length after population
 *
 * Core layer calls this after writing data to TX buffer obtained from
 * Dap_Link_GetTxFrameBuffer() to set the actual frame length.
 *
 * \param[in] instancePtr Pointer to link layer instance
 * \param[in] length      Frame length in bytes
 *
 * \return DAP_ERROR_NONE on success, positive error code on failure
 */
sint32 Dap_Link_SetTxFrameLength(Dap_Link_InstanceType *instancePtr, uint32 length);

/**
 * \brief Continue receiving a DAP frame (callback context)
 *
 * This function processes UART RX completion events and manages the
 * frame reception state machine. It is designed to be called from
 * the UART HAL RxComplete callback.
 *
 * \param[in] instancePtr     Pointer to DAP link instance
 * \param[in] uartInstancePtr Pointer to UART HAL instance (from callback)
 * \param[in] statusPtr       Pointer to RX status structure (from callback)
 *
 */
void Dap_Link_ContinueReceive(Dap_Link_InstanceType *instancePtr, Uart_Hal_InstanceType *uartInstancePtr,
                              Uart_Hal_RxStatusType *statusPtr);

/**
 * \brief Update transmit state after completion (callback context)
 *
 * This function updates the DAP link transmit state machine when a
 * UART transmission completes. It is designed to be called from
 * the UART HAL TxComplete callback.
 *
 * \param[in] instancePtr     Pointer to DAP link instance
 * \param[in] uartInstancePtr Pointer to UART HAL instance (from callback)
 * \param[in] statusPtr       Pointer to TX status structure (from callback)
 *
 */
void Dap_Link_ContinueTransmit(Dap_Link_InstanceType *instancePtr, Uart_Hal_InstanceType *uartInstancePtr,
                               Uart_Hal_TxStatusType *statusPtr);

#ifdef __cplusplus
}
#endif

#endif /* DAP_LINK_H */
