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

#include "dap_link/Dap_Link.h"
#include "Dap.h"
#include "dap_core/Dap_Core.h"
#include "dap_interface/Dap_Interface.h"

#include "Uart_Hal.h"

/* ========================================================================== */
/*                 Private Definitions and Macros                              */
/* ========================================================================== */

/* STD_ON if Tx operation shoult wait for previous Tx to complete*/
#define DAP_LINK_CFG_TX_WAIT_FOR_COMPLETE (STD_ON)
/* Number to times to loop before wait time out (if enabled) */
#define DAP_LINK_CFG_TX_READY_TIMEOUT     (100000U)

/* ========================================================================== */
/*                 Public Functions - Common Link APIs                        */
/* ========================================================================== */

sint32 Dap_Link_InitParamsSetDefault(Dap_Link_InitParamsType *paramsPtr)
{
    sint32 retVal = DAP_ERROR_NONE;

    if (paramsPtr == NULL_PTR)
    {
        retVal = DAP_ERROR_INVALID_PARAMS;
    }

    if (retVal == DAP_ERROR_NONE)
    {
        paramsPtr->LinkTxMode = DAP_LINK_MODE_INTERRUPT;
        paramsPtr->LinkRxMode = DAP_LINK_MODE_INTERRUPT;
    }

    return retVal;
}

sint32 Dap_Link_Init(Dap_Link_InstanceType *instancePtr, const Dap_Link_InitParamsType *paramsPtr)
{
    sint32 retVal = DAP_ERROR_NONE;

    /* Parameter validation */
    if (instancePtr == NULL_PTR)
    {
        retVal = DAP_ERROR_INVALID_INSTANCE;
    }
    else if (paramsPtr == NULL_PTR)
    {
        retVal = DAP_ERROR_INVALID_PARAMS;
    }
    else if (paramsPtr->UartInstancePtr == NULL_PTR)
    {
        retVal = DAP_ERROR_INVALID_PARAMS;
    }
    else if ((paramsPtr->LinkRxMode >= DAP_LINK_MODE_MAX) || (paramsPtr->LinkTxMode >= DAP_LINK_MODE_MAX))
    {
        retVal = DAP_ERROR_UNSUPPORTED_MODE;
    }
    else
    {
        /* All parameters valid */
    }

    if (retVal == DAP_ERROR_NONE)
    {
        instancePtr->IsInitialized = FALSE;

        instancePtr->UartInstancePtr              = paramsPtr->UartInstancePtr;
        instancePtr->UartInstancePtr->UserArgsPtr = (void *)instancePtr;

        instancePtr->TxInstance.State     = DAP_LINK_TX_STATE_IDLE;
        instancePtr->TxInstance.Mode      = paramsPtr->LinkTxMode;
        instancePtr->TxInstance.Frame.Len = 0U;

        instancePtr->RxInstance.State            = DAP_LINK_RX_STATE_IDLE;
        instancePtr->RxInstance.Mode             = paramsPtr->LinkRxMode;
        instancePtr->RxInstance.Frame.Len        = 0U;
        instancePtr->RxInstance.ExpectedFrameLen = 0U;
        instancePtr->RxInstance.HeaderDecoded    = FALSE;

        instancePtr->LastProtocolError = 0U;

        instancePtr->IsInitialized = TRUE;
    }

    return retVal;
}

sint32 Dap_Link_DeInit(Dap_Link_InstanceType *instancePtr)
{
    sint32 retVal = DAP_ERROR_NONE;

    /* Parameter validation */
    if (instancePtr == NULL_PTR)
    {
        retVal = DAP_ERROR_INVALID_INSTANCE;
    }
    else if (instancePtr->IsInitialized == FALSE)
    {
        retVal = DAP_ERROR_NOT_INITIALIZED;
    }
    else
    {
        /* Instance valid */
    }

    if (retVal == DAP_ERROR_NONE)
    {
        instancePtr->IsInitialized = FALSE;
    }

    return retVal;
}

/* ========================================================================== */
/*                 Public Functions - Tx & Rx Wrappers                        */
/* ========================================================================== */

sint32 Dap_Link_Send(Dap_Link_InstanceType *instancePtr)
{
    sint32                   retVal = DAP_ERROR_NONE;
    Dap_Link_TxInstanceType *txInstancePtr;

    txInstancePtr = &instancePtr->TxInstance;

    if (txInstancePtr->Frame.Len == 0U)
    {
        retVal = DAP_ERROR_INVALID_PARAMS;
    }
    else if (txInstancePtr->Frame.Len > DAP_LINK_BUFFER_SIZE_BYTES)
    {
        retVal = DAP_ERROR_BUFFER_OVERFLOW;
    }
    else
    {
        retVal = Dap_Link_SendRaw(instancePtr, txInstancePtr->Frame.Buffer, txInstancePtr->Frame.Len);
    }

    return retVal;
}

sint32 Dap_Link_SendRaw(Dap_Link_InstanceType *instancePtr, uint8 *dataPtr, uint32 sizeInBytes)
{
    sint32 retVal = DAP_ERROR_NONE;
    sint32 halRetVal;

    if (instancePtr == NULL_PTR)
    {
        retVal = DAP_ERROR_INVALID_INSTANCE;
    }
    else if (dataPtr == NULL_PTR)
    {
        retVal = DAP_ERROR_INVALID_PARAMS;
    }
    else if (sizeInBytes == 0U)
    {
        retVal = DAP_ERROR_INVALID_PARAMS;
    }
    else if (instancePtr->IsInitialized == FALSE)
    {
        retVal = DAP_ERROR_NOT_INITIALIZED;
    }
    else
    {
        /* All parameters valid */
    }

    if (retVal == DAP_ERROR_NONE)
    {
        /* Wait for any previous transmission to complete */
        retVal = Dap_Link_WaitForTxReady(instancePtr);

        if (retVal == DAP_ERROR_NONE)
        {
            if (instancePtr->TxInstance.Mode == DAP_LINK_MODE_INTERRUPT)
            {
                instancePtr->TxInstance.State = DAP_LINK_TX_STATE_TRANSMITTING;

                halRetVal = Uart_Hal_TxInterrupt(instancePtr->UartInstancePtr, dataPtr, sizeInBytes);

                if (halRetVal != UART_HAL_ERROR_NONE)
                {
                    instancePtr->TxInstance.State = DAP_LINK_TX_STATE_IDLE;
                    retVal                        = DAP_ERROR_HW_BUSY;
                }
            }
            else
            {
                retVal = DAP_ERROR_UNSUPPORTED_MODE;
            }
        }
    }

    return retVal;
}

sint32 Dap_Link_StartReceive(Dap_Link_InstanceType *instancePtr)
{
    sint32                   retVal = DAP_ERROR_NONE;
    sint32                   halRetVal;
    Dap_Link_RxInstanceType *rxInstancePtr;

    (void)Dap_Link_ResetRx(instancePtr);

    rxInstancePtr = &instancePtr->RxInstance;

    if (rxInstancePtr->Mode == DAP_LINK_MODE_INTERRUPT)
    {
        rxInstancePtr->State = DAP_LINK_RX_STATE_BUFFERING;

        halRetVal = Uart_Hal_RxInterrupt(instancePtr->UartInstancePtr, rxInstancePtr->Frame.Buffer, 1U);

        if (halRetVal != UART_HAL_ERROR_NONE)
        {
            rxInstancePtr->State = DAP_LINK_RX_STATE_IDLE;
            retVal               = DAP_ERROR_HW_BUSY;
        }
    }
    else
    {
        retVal = DAP_ERROR_UNSUPPORTED_MODE;
    }

    return retVal;
}

sint32 Dap_Link_IsTxComplete(Dap_Link_InstanceType *instancePtr, boolean *isCompletePtr)
{
    sint32                   retVal = DAP_ERROR_NONE;
    Dap_Link_TxInstanceType *txInstancePtr;

    txInstancePtr = &instancePtr->TxInstance;

    if (txInstancePtr->State == DAP_LINK_TX_STATE_IDLE)
    {
        *isCompletePtr = TRUE;
    }
    else
    {
        *isCompletePtr = FALSE;
    }

    return retVal;
}

sint32 Dap_Link_IsRxIdle(Dap_Link_InstanceType *instancePtr, boolean *isIdlePtr)
{
    sint32                   retVal = DAP_ERROR_NONE;
    Dap_Link_RxInstanceType *rxInstancePtr;

    rxInstancePtr = &instancePtr->RxInstance;

    if (rxInstancePtr->State == DAP_LINK_RX_STATE_IDLE)
    {
        *isIdlePtr = TRUE;
    }
    else
    {
        *isIdlePtr = FALSE;
    }

    return retVal;
}

sint32 Dap_Link_WaitForTxReady(Dap_Link_InstanceType *instancePtr)
{
    sint32 retVal = DAP_ERROR_NONE;

#if DAP_LINK_CFG_TX_WAIT_FOR_COMPLETE == STD_ON
    boolean txComplete       = FALSE;
    uint32  txTimeoutCounter = DAP_LINK_CFG_TX_READY_TIMEOUT;

    do
    {
        (void)Dap_Link_IsTxComplete(instancePtr, &txComplete);
        txTimeoutCounter--;
    } while ((txComplete == FALSE) && (txTimeoutCounter > 0U));

    if (txComplete == FALSE)
    {
        retVal = DAP_ERROR_LINK_TIMEOUT;
    }
#else
    if (instancePtr->TxInstance.State == DAP_LINK_TX_STATE_TRANSMITTING)
    {
        retVal = DAP_ERROR_HW_BUSY;
    }
#endif

    return retVal;
}

sint32 Dap_Link_ResetRx(Dap_Link_InstanceType *instancePtr)
{
    Dap_Link_RxInstanceType *rxInstancePtr;

    rxInstancePtr = &instancePtr->RxInstance;

    rxInstancePtr->State = DAP_LINK_RX_STATE_IDLE;

    /* Always abort and clear RX FIFO to ensure UART HAL is in clean state */
    (void)Uart_Hal_RxAbort(instancePtr->UartInstancePtr);
    (void)Uart_Hal_ClearRxFIFO(instancePtr->UartInstancePtr);

    rxInstancePtr->Frame.Len        = 0U;
    rxInstancePtr->ExpectedFrameLen = 0U;
    rxInstancePtr->HeaderDecoded    = FALSE;

    return DAP_ERROR_NONE;
}

sint32 Dap_Link_ResetTx(Dap_Link_InstanceType *instancePtr)
{
    Dap_Link_TxInstanceType *txInstancePtr;

    txInstancePtr = &instancePtr->TxInstance;

    txInstancePtr->State = DAP_LINK_TX_STATE_IDLE;

    /* Always abort to ensure UART HAL is in clean state */
    (void)Uart_Hal_TxAbort(instancePtr->UartInstancePtr);

    txInstancePtr->Frame.Len = 0U;

    return DAP_ERROR_NONE;
}

/* ========================================================================== */
/*                 Public Functions - Frame Access APIs                       */
/* ========================================================================== */

sint32 Dap_Link_GetRxFrameData(const Dap_Link_InstanceType *instancePtr, const uint8 **bufferPtrPtr, uint32 *lengthPtr)
{
    *bufferPtrPtr = instancePtr->RxInstance.Frame.Buffer;
    *lengthPtr    = instancePtr->RxInstance.Frame.Len;

    return DAP_ERROR_NONE;
}

sint32 Dap_Link_GetTxFrameBuffer(Dap_Link_InstanceType *instancePtr, uint8 **bufferPtrPtr, uint32 *maxLengthPtr)
{
    *bufferPtrPtr = instancePtr->TxInstance.Frame.Buffer;
    *maxLengthPtr = DAP_LINK_BUFFER_SIZE_BYTES;

    return DAP_ERROR_NONE;
}

sint32 Dap_Link_SetTxFrameLength(Dap_Link_InstanceType *instancePtr, uint32 length)
{
    instancePtr->TxInstance.Frame.Len = length;

    return DAP_ERROR_NONE;
}

sint32 Dap_Link_IsFrameReady(const Dap_Link_InstanceType *instancePtr, boolean *isFrameReadyPtr)
{
    const Dap_Link_RxInstanceType *rxInstancePtr;

    rxInstancePtr = &instancePtr->RxInstance;

    if (rxInstancePtr->State == DAP_LINK_RX_STATE_FRAME_READY)
    {
        *isFrameReadyPtr = TRUE;
    }
    else
    {
        *isFrameReadyPtr = FALSE;
    }

    return DAP_ERROR_NONE;
}

void Dap_Link_ContinueReceive(Dap_Link_InstanceType *instancePtr, Uart_Hal_InstanceType *uartInstancePtr,
                              Uart_Hal_RxStatusType *statusPtr)
{
    Dap_Link_RxInstanceType *rxInstancePtr;
    uint32                   status;
    uint32                   numberOfBytesReceived;
    uint32                   currentFrameLength;

    rxInstancePtr         = &instancePtr->RxInstance;
    numberOfBytesReceived = statusPtr->SizeInBytes - statusPtr->RemainingSizeInBytes;
    currentFrameLength    = rxInstancePtr->Frame.Len + numberOfBytesReceived;
    status                = DAP_ERROR_NONE;

    if (rxInstancePtr->State == DAP_LINK_RX_STATE_BUFFERING)
    {
        rxInstancePtr->Frame.Len = currentFrameLength;

        if ((currentFrameLength >= 1U) && (rxInstancePtr->Frame.Buffer[DAP_FRAME_OFFSET_START] != DAP_FRAME_START_BYTE))
        {
            status = DAP_ERROR_INVALID_START_BYTE;
        }
        else
        {
            if (rxInstancePtr->HeaderDecoded == FALSE)
            {
                if (currentFrameLength >= DAP_FRAME_MIN_HEADER_DECODE_BYTES)
                {
                    uint32 payloadLen;
                    uint32 headerLen;

                    if (Dap_Core_DecodePayloadLength(&rxInstancePtr->Frame.Buffer[DAP_FRAME_OFFSET_LENGTH],
                                                     currentFrameLength - DAP_FRAME_OFFSET_LENGTH, &payloadLen,
                                                     &headerLen) == DAP_ERROR_NONE)
                    {
                        /* Successfully decoded - calculate expected total frame length */
                        rxInstancePtr->ExpectedFrameLen =
                            DAP_FRAME_HEADER_SIZE_BYTES + headerLen + payloadLen + DAP_FRAME_TRAILER_SIZE_BYTES;

                        if (rxInstancePtr->ExpectedFrameLen > DAP_LINK_BUFFER_SIZE_BYTES)
                        {
                            status = DAP_ERROR_BUFFER_OVERFLOW;
                        }
                        else
                        {
                            rxInstancePtr->HeaderDecoded = TRUE;
                        }
                    }
                }
            }

            if ((status == DAP_ERROR_NONE) && (rxInstancePtr->HeaderDecoded == TRUE) &&
                (currentFrameLength >= rxInstancePtr->ExpectedFrameLen))
            {
                /* Frame complete - ready for processing */
                rxInstancePtr->State = DAP_LINK_RX_STATE_FRAME_READY;
            }
            else if (status == DAP_ERROR_NONE)
            {
                uint32 bytesToReceive;
                if (rxInstancePtr->HeaderDecoded == TRUE)
                {
                    /* Header decoded — Exact # remaining bytes now known */
                    bytesToReceive = rxInstancePtr->ExpectedFrameLen - currentFrameLength;
                }
                else
                {
                    /* Header not decoded — Receive 1 byte at a time */
                    bytesToReceive = 1U;
                }
                (void)Uart_Hal_RxInterrupt(instancePtr->UartInstancePtr,
                                           (rxInstancePtr->Frame.Buffer + currentFrameLength), bytesToReceive);
            }
        }

        if (status != DAP_ERROR_NONE)
        {
            Dap_Link_ResetRx(instancePtr);
        }
    }
}

void Dap_Link_ContinueTransmit(Dap_Link_InstanceType *instancePtr, Uart_Hal_InstanceType *uartInstancePtr,
                               Uart_Hal_TxStatusType *statusPtr)
{
    Dap_Link_ResetTx(instancePtr);
}
