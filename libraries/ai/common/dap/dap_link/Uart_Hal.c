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
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF
 *  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 *  DAMAGE.
 */

#include "Uart_Hal.h"
#include "driverlib.h"
#include "device.h"

/* ========================================================================== */
/*                 Private Definitions                                        */
/* ========================================================================== */

#define UART_HAL_SCI_BASE SCIA_BASE

/* ========================================================================== */
/*                 Private Variables                                          */
/* ========================================================================== */

/* ISR uses this to reach the instance without passing a parameter */
static Uart_Hal_InstanceType *gUartHalInstancePtr = NULL_PTR;

/* ========================================================================== */
/*                 Private Function Declarations                              */
/* ========================================================================== */

__interrupt static void sciaRXFIFOISR(void);

/* ========================================================================== */
/*                 Public Functions                                           */
/* ========================================================================== */

sint32 Uart_Hal_Init(Uart_Hal_InstanceType *instancePtr, const Uart_Hal_InitParamsType *paramsPtr)
{
    if ((instancePtr == NULL_PTR) || (paramsPtr == NULL_PTR))
    {
        return UART_HAL_ERROR_INVALID_PARAMS;
    }

    /* Release SCI from reset, then configure */
    SCI_performSoftwareReset(UART_HAL_SCI_BASE);

    SCI_setConfig(UART_HAL_SCI_BASE, DEVICE_LSPCLK_FREQ, paramsPtr->BaudRateBps,
                  (SCI_CONFIG_WLEN_8 | SCI_CONFIG_STOP_ONE | SCI_CONFIG_PAR_NONE));

    /* 1-byte RX trigger so every received byte fires the ISR */
    SCI_setFIFOInterruptLevel(UART_HAL_SCI_BASE, SCI_FIFO_TX1, SCI_FIFO_RX1);

    SCI_resetChannels(UART_HAL_SCI_BASE);
    SCI_resetRxFIFO(UART_HAL_SCI_BASE);
    SCI_resetTxFIFO(UART_HAL_SCI_BASE);
    SCI_clearInterruptStatus(UART_HAL_SCI_BASE, SCI_INT_RXFF);
    SCI_enableFIFO(UART_HAL_SCI_BASE);
    SCI_enableModule(UART_HAL_SCI_BASE);

    SCI_enableInterrupt(UART_HAL_SCI_BASE, SCI_INT_RXFF);
    SCI_disableInterrupt(UART_HAL_SCI_BASE, SCI_INT_RXERR);

    SCI_performSoftwareReset(UART_HAL_SCI_BASE);

    Interrupt_register(INT_SCIA_RX, sciaRXFIFOISR);
    Interrupt_enable(INT_SCIA_RX);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

    instancePtr->UserArgsPtr            = NULL_PTR;
    instancePtr->TxCurrentState         = UART_HAL_STATE_READY;
    instancePtr->RxCurrentState         = UART_HAL_STATE_READY;
    instancePtr->RxBufferPtr            = NULL_PTR;
    instancePtr->RxSizeInBytes          = 0U;
    instancePtr->RxRemainingSizeInBytes = 0U;

    gUartHalInstancePtr = instancePtr;

    return UART_HAL_ERROR_NONE;
}

sint32 Uart_Hal_TxInterrupt(Uart_Hal_InstanceType *instancePtr, const uint8 *bufferPtr, uint32 sizeInBytes)
{
    Uart_Hal_TxStatusType txStatus;

    if ((instancePtr == NULL_PTR) || (bufferPtr == NULL_PTR) || (sizeInBytes == 0U))
    {
        return UART_HAL_ERROR_INVALID_PARAMS;
    }

    instancePtr->TxCurrentState = UART_HAL_STATE_TRANSMIT;

    /*
     * TX is blocking: SCI_writeCharArray sends all bytes before returning.
     * On C28x uint8 and uint16_t are both 16-bit words, so the cast is safe.
     * Each element's low 8 bits carry the protocol byte; SCI transmits those.
     */
    SCI_writeCharArray(UART_HAL_SCI_BASE, (const uint16_t *)bufferPtr, sizeInBytes);

    instancePtr->TxCurrentState = UART_HAL_STATE_READY;

    txStatus.SizeInBytes          = sizeInBytes;
    txStatus.RemainingSizeInBytes = 0U;
    txStatus.IsTxComplete         = TRUE;
    txStatus.ErrorCodeMask        = 0U;

    Uart_Hal_TxCompleteCallback(instancePtr, &txStatus, instancePtr->UserArgsPtr);

    return UART_HAL_ERROR_NONE;
}

sint32 Uart_Hal_RxInterrupt(Uart_Hal_InstanceType *instancePtr, uint8 *bufferPtr, uint32 sizeInBytes)
{
    if ((instancePtr == NULL_PTR) || (bufferPtr == NULL_PTR) || (sizeInBytes == 0U))
    {
        return UART_HAL_ERROR_INVALID_PARAMS;
    }

    /*
     * Store receive request; the ISR will fill bufferPtr byte-by-byte and
     * call Uart_Hal_RxCompleteCallback when RxRemainingSizeInBytes reaches 0.
     */
    instancePtr->RxBufferPtr            = bufferPtr;
    instancePtr->RxSizeInBytes          = sizeInBytes;
    instancePtr->RxRemainingSizeInBytes = sizeInBytes;
    instancePtr->RxCurrentState         = UART_HAL_STATE_RECEIVE;

    return UART_HAL_ERROR_NONE;
}

sint32 Uart_Hal_RxAbort(Uart_Hal_InstanceType *instancePtr)
{
    if (instancePtr == NULL_PTR)
    {
        return UART_HAL_ERROR_INVALID_INSTANCE;
    }

    instancePtr->RxCurrentState         = UART_HAL_STATE_READY;
    instancePtr->RxBufferPtr            = NULL_PTR;
    instancePtr->RxSizeInBytes          = 0U;
    instancePtr->RxRemainingSizeInBytes = 0U;

    return UART_HAL_ERROR_NONE;
}

sint32 Uart_Hal_TxAbort(Uart_Hal_InstanceType *instancePtr)
{
    /* TX is always blocking so there is nothing to abort */
    if (instancePtr == NULL_PTR)
    {
        return UART_HAL_ERROR_INVALID_INSTANCE;
    }

    return UART_HAL_ERROR_NONE;
}

sint32 Uart_Hal_ClearRxFIFO(const Uart_Hal_InstanceType *instancePtr)
{
    (void)instancePtr;
    SCI_resetRxFIFO(UART_HAL_SCI_BASE);
    return UART_HAL_ERROR_NONE;
}

/* ========================================================================== */
/*                 Private Functions                                          */
/* ========================================================================== */

/*
 * SCI RX FIFO ISR — fires when ≥1 byte is in the FIFO (RX1 trigger level).
 * Reads one byte, stores it, and calls Uart_Hal_RxCompleteCallback when
 * the full count requested by Uart_Hal_RxInterrupt() has been received.
 */
__interrupt static void sciaRXFIFOISR(void)
{
    Uart_Hal_InstanceType *instancePtr = gUartHalInstancePtr;
    uint32                 offset;
    uint16_t               ch;
    Uart_Hal_RxStatusType  rxStatus;

    if ((instancePtr != NULL_PTR) && (instancePtr->RxCurrentState == UART_HAL_STATE_RECEIVE) &&
        (instancePtr->RxRemainingSizeInBytes > 0U))
    {
        ch     = SCI_readCharBlockingFIFO(UART_HAL_SCI_BASE);
        offset = instancePtr->RxSizeInBytes - instancePtr->RxRemainingSizeInBytes;

        instancePtr->RxBufferPtr[offset] = (uint8)ch;
        instancePtr->RxRemainingSizeInBytes--;

        if (instancePtr->RxRemainingSizeInBytes == 0U)
        {
            instancePtr->RxCurrentState = UART_HAL_STATE_READY;

            rxStatus.BufferPtr            = instancePtr->RxBufferPtr;
            rxStatus.SizeInBytes          = instancePtr->RxSizeInBytes;
            rxStatus.RemainingSizeInBytes = 0U;
            rxStatus.IsRxComplete         = TRUE;
            rxStatus.ErrorCodeMask        = 0U;

            /*
             * Dap_ReceiveCallback → Dap_Link_ContinueReceive, which may call
             * Uart_Hal_RxInterrupt() to arm the next receive. That is safe here
             * because it only updates instance fields; no hardware is touched.
             */
            Uart_Hal_RxCompleteCallback(instancePtr, &rxStatus, instancePtr->UserArgsPtr);
        }
    }
    else
    {
        /* Unexpected interrupt — drain one byte to prevent re-entry */
        (void)SCI_readCharBlockingFIFO(UART_HAL_SCI_BASE);
    }

    SCI_clearInterruptStatus(UART_HAL_SCI_BASE, SCI_INT_RXFF);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
