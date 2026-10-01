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
 * \file Uart_Hal.h
 * \brief UART HAL for F28P55x C28x — wraps SCI driverlib
 *
 * Implements the Uart_Hal interface required by Dap_Link.c on the C28x.
 * TX is blocking (SCI_writeCharArray). RX is interrupt-driven with a
 * 1-byte SCI FIFO trigger; the ISR feeds bytes into the buffer set by
 * Uart_Hal_RxInterrupt() and calls Uart_Hal_RxCompleteCallback() when
 * the requested count is satisfied.
 *
 * The SCI peripheral base address (SCIA_BASE) is fixed at compile time.
 * Only BaudRateBps needs to be supplied at init.
 */

#ifndef UART_HAL_H
#define UART_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Std_Types.h"

/* ========================================================================== */
/*                 Public Definitions and Macros                              */
/* ========================================================================== */

/** \brief No error */
#define UART_HAL_ERROR_NONE             (0)
/** \brief Invalid instance pointer */
#define UART_HAL_ERROR_INVALID_INSTANCE (1)
/** \brief Invalid parameters */
#define UART_HAL_ERROR_INVALID_PARAMS   (2)
/** \brief Hardware busy */
#define UART_HAL_ERROR_HW_BUSY          (4)

/* ========================================================================== */
/*                 Public Typedefs                                            */
/* ========================================================================== */

/** \brief UART HAL state */
typedef enum
{
    UART_HAL_STATE_UNCONFIGURED, /**< Not yet initialized */
    UART_HAL_STATE_READY,        /**< Initialized and idle */
    UART_HAL_STATE_TRANSMIT,     /**< Transmitting */
    UART_HAL_STATE_RECEIVE,      /**< Receiving */
} Uart_Hal_StateType;

/** \brief TX transfer status — passed to Uart_Hal_TxCompleteCallback */
typedef struct
{
    /** \brief Total bytes requested */
    uint32  SizeInBytes;
    /** \brief Bytes not yet sent (0 when complete) */
    uint32  RemainingSizeInBytes;
    /** \brief TRUE when TX is complete */
    boolean IsTxComplete;
    /** \brief Error bitmask (0 = no error) */
    uint32  ErrorCodeMask;
} Uart_Hal_TxStatusType;

/** \brief RX transfer status — passed to Uart_Hal_RxCompleteCallback */
typedef struct
{
    /** \brief Destination buffer */
    uint8  *BufferPtr;
    /** \brief Total bytes requested */
    uint32  SizeInBytes;
    /** \brief Bytes not yet received (0 when complete) */
    uint32  RemainingSizeInBytes;
    /** \brief TRUE when RX is complete */
    boolean IsRxComplete;
    /** \brief Error bitmask (0 = no error) */
    uint32  ErrorCodeMask;
} Uart_Hal_RxStatusType;

/**
 * \brief UART HAL initialization parameters
 *
 * SCI base address is fixed at SCIA_BASE; only baud rate is configurable.
 */
typedef struct
{
    /** \brief Desired baud rate in bits per second */
    uint32 BaudRateBps;
} Uart_Hal_InitParamsType;

/**
 * \brief UART HAL instance structure
 *
 * UserArgsPtr is set by Dap_Link_Init() to the Dap_Link instance pointer
 * so that callbacks can route to the correct DAP layer.
 */
typedef struct
{
    /** \brief Opaque user argument forwarded to callbacks */
    void              *UserArgsPtr;
    /** \brief Current TX state */
    Uart_Hal_StateType TxCurrentState;
    /** \brief Current RX state */
    Uart_Hal_StateType RxCurrentState;
    /** \brief Destination buffer for the current RX request */
    uint8             *RxBufferPtr;
    /** \brief Total bytes requested in the current RX transfer */
    uint32             RxSizeInBytes;
    /** \brief Bytes still to be received */
    uint32             RxRemainingSizeInBytes;
} Uart_Hal_InstanceType;

/* ========================================================================== */
/*                 Public Functions                                           */
/* ========================================================================== */

/**
 * \brief Initialize SCI hardware and register the RX FIFO ISR
 *
 * \param[out] instancePtr Pointer to UART HAL instance to initialize
 * \param[in]  paramsPtr   Pointer to initialization parameters
 *
 * \return UART_HAL_ERROR_NONE on success
 */
sint32 Uart_Hal_Init(Uart_Hal_InstanceType *instancePtr, const Uart_Hal_InitParamsType *paramsPtr);

/**
 * \brief Send data via SCI (blocking) then call Uart_Hal_TxCompleteCallback
 *
 * \param[in] instancePtr Pointer to UART HAL instance
 * \param[in] bufferPtr   Data to transmit
 * \param[in] sizeInBytes Number of bytes to send
 *
 * \return UART_HAL_ERROR_NONE on success
 */
sint32 Uart_Hal_TxInterrupt(Uart_Hal_InstanceType *instancePtr, const uint8 *bufferPtr, uint32 sizeInBytes);

/**
 * \brief Arm the RX state machine to receive sizeInBytes bytes into bufferPtr
 *
 * Bytes arrive one at a time via the SCI RX FIFO ISR. When all requested
 * bytes have been received, Uart_Hal_RxCompleteCallback() is called from
 * ISR context.
 *
 * \param[in] instancePtr Pointer to UART HAL instance
 * \param[in] bufferPtr   Destination buffer (must remain valid until callback)
 * \param[in] sizeInBytes Number of bytes to receive
 *
 * \return UART_HAL_ERROR_NONE on success
 */
sint32 Uart_Hal_RxInterrupt(Uart_Hal_InstanceType *instancePtr, uint8 *bufferPtr, uint32 sizeInBytes);

/**
 * \brief Abort an in-progress RX transfer and reset RX state
 *
 * \param[in] instancePtr Pointer to UART HAL instance
 *
 * \return UART_HAL_ERROR_NONE on success
 */
sint32 Uart_Hal_RxAbort(Uart_Hal_InstanceType *instancePtr);

/**
 * \brief Abort an in-progress TX transfer (no-op; TX is always blocking)
 *
 * \param[in] instancePtr Pointer to UART HAL instance
 *
 * \return UART_HAL_ERROR_NONE on success
 */
sint32 Uart_Hal_TxAbort(Uart_Hal_InstanceType *instancePtr);

/**
 * \brief Reset the SCI RX FIFO
 *
 * \param[in] instancePtr Pointer to UART HAL instance (unused; FIFO is global)
 *
 * \return UART_HAL_ERROR_NONE on success
 */
sint32 Uart_Hal_ClearRxFIFO(const Uart_Hal_InstanceType *instancePtr);

/* ========================================================================== */
/*                 Callbacks — implemented by application                     */
/* ========================================================================== */

/**
 * \brief Called after a TX transfer completes
 *
 * In dap_test_main.c this should call Dap_TransmitCallback().
 *
 * \param[in] instancePtr Pointer to UART HAL instance
 * \param[in] statusPtr   TX transfer status
 * \param[in] userArgsPtr Value of instancePtr->UserArgsPtr (DAP Link instance)
 */
void Uart_Hal_TxCompleteCallback(Uart_Hal_InstanceType *instancePtr, Uart_Hal_TxStatusType *statusPtr,
                                 void *userArgsPtr);

/**
 * \brief Called from ISR after an RX transfer completes
 *
 * In dap_test_main.c this should call Dap_ReceiveCallback().
 *
 * \param[in] instancePtr Pointer to UART HAL instance
 * \param[in] statusPtr   RX transfer status
 * \param[in] userArgsPtr Value of instancePtr->UserArgsPtr (DAP Link instance)
 */
void Uart_Hal_RxCompleteCallback(Uart_Hal_InstanceType *instancePtr, Uart_Hal_RxStatusType *statusPtr,
                                 void *userArgsPtr);

#ifdef __cplusplus
}
#endif

#endif /* UART_HAL_H */
