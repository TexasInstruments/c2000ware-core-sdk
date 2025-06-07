//#############################################################################
//
// FILE:   clb_ex32_ccsi_hal.c
//
// TITLE:  Function definitions for CCSI hardware abstraction layer.
//
//#############################################################################
// $TI Release: $
// 
// 
// C2000Ware v5.05.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include <clb_ex32_ccsi_hal.h>
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "clb_config.h"

// Maximum reads/writes allowed to avoid overrun of TX FIFO
#define CLBFIFOMAXWRITES   4

#define GPREG_TRANSFER_START        1U
#define GPREG_TRANSFER_START_SYNC   6U
#define GPREG_ENABLE_RCVR           3U

// Receive buffer size (must always be a power of 2)
#define RCV_BUF_SIZE    128

// Ring buffer for receiving data
uint32_t clbRxRingBuff[RCV_BUF_SIZE];
uint16_t ringBuffHead, ringBuffTail;

//
// Globals
//
volatile uint16_t clbXmtCount;
volatile uint16_t clbXmtDone;

volatile uint32_t *clbXmtBufPtr;
volatile uint16_t clbXmtXferSize;

uint32_t clbXmtBuffer[MAX_DATA_LENGTH]; //Stores the data bytes to be sent
uint16_t clbRcvBuffer[MAX_DATA_LENGTH]; //Stores the data bytes to be sent

//
// Initializes CLB logic
//
void CCSI_HAL_initClbLogic()
{
    // Setup the CLB Tiles
    initTILE1(CCSI1_RX_TILE_BASE);
    initTILE2(CCSI1_TX_TILE_BASE);

    // Initialize the TX CLB PULL FIFOs to some default/safe value
    HWREG(CCSI1_TX_TILE_BASE + CLB_DATAEXCH + CLB_O_PULL(0)) = 0xFFFFFFFF;
    HWREG(CCSI1_TX_TILE_BASE + CLB_DATAEXCH + CLB_O_PULL(1)) = 0xFFFFFFFF;
    HWREG(CCSI1_TX_TILE_BASE + CLB_DATAEXCH + CLB_O_PULL(2)) = 0xFFFFFFFF;
    HWREG(CCSI1_TX_TILE_BASE + CLB_DATAEXCH + CLB_O_PULL(3)) = 0xFFFFFFFF;

    // Load the TX CLB with some default/safe value
    CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_COUNTER_1_LOAD, 0xFFFFFFFF);

    // Put TX CLB in idle
    CLB_setGPREG(CCSI1_TX_TILE_BASE, 0U << GPREG_TRANSFER_START);

    // Setup receive ring buffer pointers
    ringBuffHead = 0;
    ringBuffTail = 0;

    //
    // Reset the RX CLB PUSH FIFO pointer
    // Note: The register CLB_O_BUF_PTR contains both PUSH and PULL FIFO pointers.
    //       However PULL FIFO pointer is not used, so it's okay to overwrite it.
    //
    HWREG(CCSI1_RX_TILE_BASE + CLB_LOGICCTL + CLB_O_BUF_PTR) = 0U;

    // Clear the RX CLB PUSH FIFO
    HWREG(CCSI1_RX_TILE_BASE + CLB_DATAEXCH + CLB_O_PUSH(0)) = 0x0;
    HWREG(CCSI1_RX_TILE_BASE + CLB_DATAEXCH + CLB_O_PUSH(1)) = 0x0;
    HWREG(CCSI1_RX_TILE_BASE + CLB_DATAEXCH + CLB_O_PUSH(2)) = 0x0;
    HWREG(CCSI1_RX_TILE_BASE + CLB_DATAEXCH + CLB_O_PUSH(3)) = 0x0;

    // Modify source for CLB_SCLK output since single-edge operation needed for LP5891.
    // TX TILE CLB IN4 initialization
    CLB_configGlobalInputMux(CCSI1_TX_TILE_BASE, CLB_IN4, CLB_GLOBAL_IN_MUX_EPWM1A);

    // Enable the CLB logic
    CLB_enableCLB(CCSI1_RX_TILE_BASE);
    CLB_enableCLB(CCSI1_TX_TILE_BASE);

    // Disable receive in CLB RX
    CCSI_HAL_disableClbReceiver();

    // Init globals used for xmit
    clbXmtCount = 0;
    clbXmtDone = 1;

    // Enable TX and RX CLB interrupt
    Interrupt_enable(INT_CCSI1_RX_TILE);
    Interrupt_enable(INT_CCSI1_TX_TILE);
}

//
// Registers CLB interrupts
//
void CCSI_HAL_setupInterrupts()
{
    //
    // CCSI1 & CCSI2 bus interrupts already registered by syscfg.
    // Register additional CCSI bus interrupts if needed.
    //
}

//
// Configures PWM to generate PWM_SCLK and PWM_SCLKX2
//

void CCSI_HAL_startLedClocks()
{
    uint16_t tbPrdVal = 0U;

    //
    // Configure PWM to continue operating even during emulation stop
    //
    EPWM_setEmulationMode(EPWM_CLK_BASE, EPWM_EMULATION_FREE_RUN);

    //
    // Set Time Base counter Clock equal to SYSCLK
    //
    EPWM_setClockPrescaler(EPWM_CLK_BASE, EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Configure Time Base Counter Mode
    //
    EPWM_setTimeBaseCounterMode(EPWM_CLK_BASE, EPWM_COUNTER_MODE_UP_DOWN);

    //
    // Calculate TBPRD value to be configured for achieving desired
    // signal
    // NOTE: Actual output clock frequency can be calculated as:
    //       DEVICE_SYSCLK_FREQ / (2 * tpPrdVal), where tpPrdVal is an integer
    //
    tbPrdVal = (uint16_t)(DEVICE_SYSCLK_FREQ / (2 * SPICLK_FREQ_IN_HZ));

    //
    // Configure TBPRD value
    //
    EPWM_setTimeBasePeriod(EPWM_CLK_BASE, tbPrdVal);

    //
    // Default Configurations.
    //
    EPWM_disablePhaseShiftLoad(EPWM_CLK_BASE);
    EPWM_setPhaseShift(EPWM_CLK_BASE, 0U);
    EPWM_setTimeBaseCounter(EPWM_CLK_BASE, 0U);

    //
    // Setup PWMxA to generate PWM_SCLKX2
    //
    EPWM_setActionQualifierAction(EPWM_CLK_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(EPWM_CLK_BASE,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);

    //
    // Force PWMxB low to ensure it goes high when CTR=Zero
    //
    EPWM_setActionQualifierSWAction(EPWM_CLK_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW);
    EPWM_forceActionQualifierSWAction(EPWM_CLK_BASE,EPWM_AQ_OUTPUT_B);

    //
    // Setup PWMxB to generate PWM_SCLK
    //
    EPWM_setActionQualifierAction(EPWM_CLK_BASE,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_TOGGLE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
}

//
// Transmit and receive data using CLB; function will block execution
// until transfer completes.
//

void CCSI_HAL_clbTransferBlocking(uint32_t *xmtBuffer, uint32_t numXmtWords)
{
    uint16_t i;

    //
    // Initialize variables to keep track of frame progress
    //
    clbXmtCount = 0;
    clbXmtDone = 0;

    clbXmtBufPtr = xmtBuffer;
    clbXmtXferSize = numXmtWords;

    // Load first data value directly to CLB HLC register
    CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_HLC_R1,
                       *(clbXmtBufPtr + clbXmtCount++));

    // Load first 4 data values to CLB PULL FIFO
    for(i=0; i<CLBFIFOMAXWRITES && clbXmtCount<clbXmtXferSize; i++)
        HWREG(CCSI1_TX_TILE_BASE + CLB_DATAEXCH + CLB_O_PULL(i)) =
                *(clbXmtBufPtr + clbXmtCount++);

    // Reset the CLB FIFO PULL pointer
    HWREG(CCSI1_TX_TILE_BASE + CLB_LOGICCTL + CLB_O_BUF_PTR) = 0U;

    // Reset the CLB xmt count & load total number of xmit words
    CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_COUNTER_0_LOAD, 0);
    CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_COUNTER_0_MATCH1,
                       clbXmtXferSize+1);  // +1 to account for START

    // Clear the flag registers in case there is anything pending
    CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_HLC_R2, 0x0);
    CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_HLC_R3, 0x0);

    // Signal CLB to start transmission
    CLB_setGPREG(CCSI1_TX_TILE_BASE, 1U << GPREG_TRANSFER_START);

    //
    // Wait for data transmit to complete
    //
    while(clbXmtDone == 0){}

    // Signal CLB to go to IDLE state
    CLB_setGPREG(CCSI1_TX_TILE_BASE, 0U << GPREG_TRANSFER_START);
}

//
// Transmit and receive data using CLB; function will NOT block execution.
//

void CCSI_HAL_clbTransferNonBlocking(uint32_t *xmtBuffer, uint32_t numXmtWords)
{
    uint16_t i;

    //
    // Initialize variables to keep track of frame progress
    //
    clbXmtCount = 0;
    clbXmtDone = 0;

    clbXmtBufPtr = xmtBuffer;
    clbXmtXferSize = (uint16_t) numXmtWords;

    // Load first data value directly to CLB HLC register
    CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_HLC_R1,
                       *(clbXmtBufPtr + (uint32_t)clbXmtCount++));

    // Load first 4 data values to CLB PULL FIFO
    for(i=0; i<CLBFIFOMAXWRITES && clbXmtCount<clbXmtXferSize; i++)
        HWREG(CCSI1_TX_TILE_BASE + CLB_DATAEXCH + CLB_O_PULL(i)) =
                *(clbXmtBufPtr + (uint32_t)clbXmtCount++);

    // Reset the CLB FIFO PULL pointer
    HWREG(CCSI1_TX_TILE_BASE + CLB_LOGICCTL + CLB_O_BUF_PTR) = 0U;

    // Reset the CLB xmt count & load total number of xmit words
    CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_COUNTER_0_LOAD, 0);
    CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_COUNTER_0_MATCH1,
                       clbXmtXferSize+1);  // +1 to account for START

    // Clear the flag registers in case there is anything pending
    CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_HLC_R2, 0x0);
    CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_HLC_R3, 0x0);

    // Signal CLB to start transmission
    CLB_setGPREG(CCSI1_TX_TILE_BASE, 1U << GPREG_TRANSFER_START);
}

//
// Signal all TX CLBs to start transmit
// NOTE: CSSI1 TX tile acts as master for all TX tiles
// NOTE: Only one TX CLB is supported in this example
//
void CCSI_HAL_clbSyncTransferStart(void)
{
    CLB_setGPREG(CCSI1_TX_TILE_BASE, 1U << GPREG_TRANSFER_START_SYNC);
}

void CCSI_HAL_enableClbReceiver()
{
    uint32_t gpRegVal = CLB_getGPREG(CCSI1_RX_TILE_BASE);

    // First check that receiver is in IDLE state
    while(HWREG(CCSI1_RX_TILE_BASE + CLB_LOGICCTL + CLB_O_DBG_OUT) &
            (CLB_DBG_OUT_FSM0_S1 | CLB_DBG_OUT_FSM0_S0)) {}

    // Enable receiver
    gpRegVal |= (1U << GPREG_ENABLE_RCVR);
    CLB_setGPREG(CCSI1_RX_TILE_BASE, gpRegVal);
}

void CCSI_HAL_disableClbReceiver()
{
    uint32_t gpRegVal = CLB_getGPREG(CCSI1_RX_TILE_BASE);

    // First check that receiver is in IDLE state
    while(HWREG(CCSI1_RX_TILE_BASE + CLB_LOGICCTL + CLB_O_DBG_OUT) &
            (CLB_DBG_OUT_FSM0_S1 | CLB_DBG_OUT_FSM0_S0)) {}

    // Disable receiver
    gpRegVal &= ~(1U << GPREG_ENABLE_RCVR);
    CLB_setGPREG(CCSI1_RX_TILE_BASE, gpRegVal);
}

// Resets the receive ring buffer pointers (trashes data)
void CCSI_HAL_ringBufferReset()
{
    ringBuffHead = 0;
    ringBuffTail = 0;
}

// Checks if ring buffer is empty
uint16_t CCSI_HAL_ringBufferEmpty()
{
    return ((ringBuffHead - ringBuffTail) == 0U) ? 1 : 0;
}

// Checks if ring buffer is full
uint16_t CCSI_HAL_ringBufferFull()
{
    return ((ringBuffHead - ringBuffTail) == RCV_BUF_SIZE) ? 1 : 0;
}

// Reads a single element from the ring buffer
int16_t CCSI_HAL_clbRxRingBuffRead (uint16_t *data)
{
    if(CCSI_HAL_ringBufferEmpty() == 0)
    {
        uint16_t offset = (ringBuffTail & (RCV_BUF_SIZE-1));

        *data =  (uint16_t)(clbRxRingBuff[offset]);
        ringBuffTail++;
        return 0;
    }
    else
    {
        return -1;
    }
}

// Writes a single element to the ring buffer
int16_t CCSI_HAL_clbRxRingBuffWrite (uint32_t *data)
{
    if(CCSI_HAL_ringBufferFull() == 0)
    {
        uint16_t offset = (ringBuffHead & (RCV_BUF_SIZE-1));

        clbRxRingBuff[offset] = *data;
        ringBuffHead++;
        return 0;
    }
    else
    {
        return -1;
    }
}

//
// CCSI1 RX ISR
// Note: RX CLB will generate a receive interrupt when it has received 4 16-bit words.
//       It will also generate an END interrupt when it detects an end of frame. If a
//       a frame is less than 4 words, the RX CLB will generate an END interrupt, but
//       no receive interrupt.
//
//
__interrupt void INT_CCSI1_RX_TILE_ISR(void)
{
    uint32_t chkIntFlag = CLB_getRegister(CCSI1_RX_TILE_BASE, CLB_REG_HLC_R1);
//    uint32_t rcvIntFlag = CLB_getRegister(CCSI1_RX_TILE_BASE, CLB_REG_HLC_R2);
//    uint32_t endIntFlag = CLB_getRegister(CCSI1_RX_TILE_BASE, CLB_REG_HLC_R3);

    uint32_t clbPushFifoPtr = 0;
    uint32_t clbPushFifoData;
    uint16_t i;

    // Check for any data in FIFOs
    clbPushFifoPtr = (HWREG(CCSI1_RX_TILE_BASE + CLB_LOGICCTL + CLB_O_BUF_PTR) >> 16) & 0x00FF;

    //
    // Reset the PUSH FIFO pointer
    // Note: The register CLB_O_BUF_PTR contains both PUSH and PULL FIFO pointers.
    //       However PULL FIFO pointer is not used, so it's okay to overwrite it.
    //
    HWREG(CCSI1_RX_TILE_BASE + CLB_LOGICCTL + CLB_O_BUF_PTR) = 0U;

    // Check for overrun
    if (clbPushFifoPtr > 4)
    {
        ESTOP0;
    }
    else
    {
        // Copy data (if any) from FIFO to receive buffer
        for (i=0; i<clbPushFifoPtr; i++)
        {
            clbPushFifoData = HWREG(CCSI1_RX_TILE_BASE + CLB_DATAEXCH + CLB_O_PUSH(i));
            CCSI_HAL_clbRxRingBuffWrite(&clbPushFifoData);
        }
    }

    // Receive interrupt (not used)
//    if (rcvIntFlag & 0x1)
//    {
//        // Clear the receive interrupt flag register
//        CLB_writeInterface(CCSI1_RX_TILE_BASE, CLB_ADDR_HLC_R2, 0x0);
//    }

    // End interrupt (not used)
//    if (endIntFlag & 0x1)
//    {
//        // Clear the end interrupt flag register
//        CLB_writeInterface(CCSI1_RX_TILE_BASE, CLB_ADDR_HLC_R3, 0x0);
//    }

    // Check error interrupt
    if (chkIntFlag & 0x1)
    {
        // Clear the check error interrupt flag register
        CLB_writeInterface(CCSI1_RX_TILE_BASE, CLB_ADDR_HLC_R1, 0x0);
    }

    Interrupt_clearACKGroup(INT_CCSI1_RX_TILE_INTERRUPT_ACK_GROUP);
}


//
// CCSI1 TX ISR
//
__interrupt void INT_CCSI1_TX_TILE_ISR(void)
{
    uint32_t txIntFlag, doneIntFlag;
    volatile uint16_t clbXmtXferSizeLocal = clbXmtXferSize;
    volatile uint16_t clbXmtCountLocal = clbXmtCount;
    volatile uint32_t *clbXmtBufPtrLocal = clbXmtBufPtr;

    // Read CLB status flags
    txIntFlag = CLB_getRegister(CCSI1_TX_TILE_BASE, CLB_REG_HLC_R3);

    // Transmit interrupt
    if(txIntFlag & 0x1)
    {
        if(clbXmtCountLocal < clbXmtXferSizeLocal)
        {
            // Write the first value
            HWREG(CCSI1_TX_TILE_BASE + CLB_DATAEXCH + CLB_O_PULL(0)) =
                    *(clbXmtBufPtrLocal + clbXmtCountLocal++);

            if(clbXmtCountLocal < clbXmtXferSizeLocal)
            {
                HWREG(CCSI1_TX_TILE_BASE + CLB_DATAEXCH + CLB_O_PULL(1)) =
                        *(clbXmtBufPtrLocal + clbXmtCountLocal++);

                if(clbXmtCountLocal < clbXmtXferSizeLocal)
                {
                    HWREG(CCSI1_TX_TILE_BASE + CLB_DATAEXCH + CLB_O_PULL(2)) =
                            *(clbXmtBufPtrLocal + clbXmtCountLocal++);

                    if(clbXmtCountLocal < clbXmtXferSizeLocal)
                    {
                        HWREG(CCSI1_TX_TILE_BASE + CLB_DATAEXCH + CLB_O_PULL(3)) =
                                *(clbXmtBufPtrLocal + clbXmtCountLocal++);
                    }
                }
            }

            // Clear the flag register
            CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_HLC_R3, 0x0);

            clbXmtCount = clbXmtCountLocal;
        }
    }

    doneIntFlag = CLB_getRegister(CCSI1_TX_TILE_BASE, CLB_REG_HLC_R2);

    // Signal to CPU when CLB is done transmitting payload
    if (doneIntFlag & 0x1)
    {
        // Put TX CLB in idle
        CLB_setGPREG(CCSI1_TX_TILE_BASE, 0U);

        // Clear done flag
        CLB_writeInterface(CCSI1_TX_TILE_BASE, CLB_ADDR_HLC_R2, 0x0);

        // Signal to application the transfer is done
        clbXmtDone = 1;
    }

    Interrupt_clearACKGroup(INT_CCSI1_TX_TILE_INTERRUPT_ACK_GROUP);
}
