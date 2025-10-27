//#############################################################################
//
// FILE:   mcan_ex15_timestamp.c
//
// TITLE:   MCAN Timestamping Example
//
//! \addtogroup driver_example_c28x_list
//! <h1> MCAN Internal Loopback with Interrupt </h1>
//!
//! This example demonstrates the MCAN Timestamping functionality.
//! When the TRANSMIT define is selected, the CAN Controller acts as a
//! Transmitter and sends data to the second CAN Controller connected
//! externally. If TRANMSIT is not defined the CAN Controller acts as a Receiver
//! and waits for message to be transmitted by the External CAN Controller.
//!
//! \b External \b Connections \n
//!  - None.
//!
//! \b Watch \b Variables \n
//!  - a_txts - Array that stores Tx Timestamp values read from the Tx Event FIFO
//!  - a_rxts - Array that stores Rx Timestamp values read from Rx FIFO 1
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
// Include Files
//
#include "driverlib.h"
#include "device.h"
#include "inc/stw_dataTypes.h"
#include "inc/stw_types.h"
#include <string.h>

//
// Defines
//
#define MCAN_STD_ID_FILTER_NUM          (5U)
#define MCAN_EXT_ID_FILTER_NUM          (0U)
#define MCAN_FIFO_0_NUM                 (0U)
#define MCAN_FIFO_0_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_FIFO_1_NUM                 (20U)
#define MCAN_FIFO_1_ELEM_SIZE           (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_RX_BUFF_NUM                (0U)
#define MCAN_RX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_BUFF_SIZE               (15U)
#define MCAN_TX_FQ_SIZE                 (0U)
#define MCAN_TX_BUFF_ELEM_SIZE          (MCAN_ELEM_SIZE_64BYTES)
#define MCAN_TX_EVENT_SIZE              (15U)
#define MCAN_EXT_ID_AND_MASK            (0x1FFFFFFFU)
#define MCAN_MSG_INT                    (0x81200)

//
//  Defining Starting Addresses for Message RAM Sections,
//  (Calculated from Macros based on User defined configuration above)
//
#define MCAN_STD_ID_FILT_START_ADDR     (0x0U)
#define MCAN_EXT_ID_FILT_START_ADDR     (MCAN_STD_ID_FILT_START_ADDR + ((MCAN_STD_ID_FILTER_NUM * MCANSS_STD_ID_FILTER_SIZE_WORDS * 4U)))
#define MCAN_FIFO_0_START_ADDR          (MCAN_EXT_ID_FILT_START_ADDR + ((MCAN_EXT_ID_FILTER_NUM * MCANSS_EXT_ID_FILTER_SIZE_WORDS * 4U)))
#define MCAN_FIFO_1_START_ADDR          (MCAN_FIFO_0_START_ADDR + (MCAN_getMsgObjSize(MCAN_FIFO_0_ELEM_SIZE) * 4U * MCAN_FIFO_0_NUM))
#define MCAN_RX_BUFF_START_ADDR         (MCAN_FIFO_1_START_ADDR + (MCAN_getMsgObjSize(MCAN_FIFO_1_ELEM_SIZE) * 4U * MCAN_FIFO_1_NUM))
#define MCAN_TX_BUFF_START_ADDR         (MCAN_RX_BUFF_START_ADDR + (MCAN_getMsgObjSize(MCAN_RX_BUFF_ELEM_SIZE) * 4U * MCAN_RX_BUFF_NUM))
#define MCAN_TX_EVENT_START_ADDR        (MCAN_TX_BUFF_START_ADDR + (MCAN_getMsgObjSize(MCAN_TX_BUFF_ELEM_SIZE) * 4U * (MCAN_TX_BUFF_SIZE + MCAN_TX_FQ_SIZE)))

//
// Application Defines
//
#define NUM_OF_MSG                  (10U)
#define MCAN_TS_PRESCALAR           (0xBFF0)                        // Configures Prescaler for External Counter used for Timestamping

//
// Comment out to make the CAN Controller work as a receiver
//
#define TRANSMIT

//
// Global Variables.
//
volatile unsigned long tsInterruptCntr = 0;
volatile unsigned long error = 0;
#ifdef TRANSMIT
MCAN_TxBufElement txMsg[NUM_OF_MSG];
MCAN_TxEventFIFOStatus TxEFS;
MCAN_TxEventFIFOElement TxEvent, TxEventArray[NUM_OF_MSG];
uint32_t a_txts[NUM_OF_MSG], a_txCounter[NUM_OF_MSG];
volatile uint32_t isrIntr0Flag = 1U;
#else 
MCAN_RxBufElement rxMsg[NUM_OF_MSG], rxMsg1;
MCAN_RxFIFOStatus RxFS;
uint32_t a_rxts[NUM_OF_MSG], a_rxCounter[NUM_OF_MSG];
volatile uint32_t isrIntr1Flag = 1U;
#endif 
int32_t	loopCnt = 0U, i = 0U, j = 0U;
uint32_t msgCount = 0U;

//
// Function Prototype.
//
static void MCANConfig(void);
static void MCANIntrConfig(void);
__interrupt void MCANTSIntrISR(void);
#ifdef TRANSMIT
__interrupt void MCANIntr0ISR(void);
#else 
__interrupt void MCANIntr1ISR(void);
#endif 

//
// Main
//
void main(void)
{
    uint32_t numOfMsg = NUM_OF_MSG;

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Initialize GPIO and unlock the GPIO configuration registers
    //
    Device_initGPIO();

    //
    // Configuring the GPIOs for MCAN.
    //
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_MCANTXA);

    //
    // Configure the divisor for the MCAN bit-clock
    //
    SysCtl_setMCANClk(SYSCTL_MCANA, SYSCTL_MCANCLK_DIV_5);

    //
    // CrossBar and ISR Configuration.
    //
    MCANIntrConfig();

    //
    // Initialize message to transmit.
    //
    uint32_t dataBytes = 64;

#ifdef TRANSMIT
    for(loopCnt = 0U ; loopCnt < numOfMsg ; loopCnt++)
    {
		txMsg[loopCnt].id       = ((uint32_t)(0x4)) << 18U;
		txMsg[loopCnt].id       |= (0xFF);
		txMsg[loopCnt].rtr      = 0U;
		txMsg[loopCnt].xtd      = 0U;
		txMsg[loopCnt].esi      = 0U;
		txMsg[loopCnt].dlc      = 15U;
		txMsg[loopCnt].brs      = 1U;
		txMsg[loopCnt].fdf      = 1U;
		txMsg[loopCnt].efc      = 1U;
		txMsg[loopCnt].mm       = 0xA0U + (uint32_t)loopCnt;        
        //Message Marker is used to associate the Tx Message with the corresponding Tx Event FIFO element
	    txMsg[loopCnt].data[i]  = 0x1;
	    for(i = 1; i < dataBytes; i++)
	    {
	    	txMsg[loopCnt].data[i]  = txMsg[loopCnt].data[i-1] + 1;
	    }
	    i = 0;
    }
#else  
    for(loopCnt = 0U ; loopCnt < numOfMsg ; loopCnt++)
    {
        rxMsg[loopCnt].id = 0U;
        rxMsg[loopCnt].rtr = 0U;
        rxMsg[loopCnt].xtd = 0U;
        rxMsg[loopCnt].esi = 0U;
        rxMsg[loopCnt].rxts = 0U;
        rxMsg[loopCnt].dlc = 0U;
        rxMsg[loopCnt].brs = 0U;
        rxMsg[loopCnt].fdf = 0U;
        rxMsg[loopCnt].fidx = 0U;
        rxMsg[loopCnt].anmf = 0U;
        for(i = 0; i < dataBytes; i++)
        {
        	rxMsg[loopCnt].data[i]  = 0;
        }
    }
#endif  

#ifdef TRANSMIT
    for(loopCnt = 0; loopCnt < NUM_OF_MSG; loopCnt++)
    {
        //
        // Initializing Tx Timestamp Array
        //
        a_txts[loopCnt] = 0x0U;
    }
#else  
    for(loopCnt = 0; loopCnt < NUM_OF_MSG; loopCnt++)
    {
        //
        // Initializing Rx Timestamp Array
        //
        a_rxts[loopCnt] = 0x0U;
    }  
#endif      

    //
    // Configure MCAN.
    //
    MCANConfig();

#ifdef TRANSMIT
    //
    // Enable Interrupts.
    //
    MCAN_enableIntr(MCANA_DRIVER_BASE, MCAN_IR_TC_MASK | MCAN_IR_TEFW_MASK, 1U);

    //
    // Select Interrupt Line.
    //
    MCAN_selectIntrLine(MCANA_DRIVER_BASE, MCAN_INTR_MASK_ALL, MCAN_INTR_LINE_NUM_0);

    //
    // Enable Interrupt Line.
    //
    MCAN_enableIntrLine(MCANA_DRIVER_BASE, MCAN_INTR_LINE_NUM_0, 1U);
#else
    //
    // Enable Interrupts.
    //
    MCAN_enableIntr(MCANA_DRIVER_BASE, MCAN_IR_RF1N_MASK | MCAN_IR_RF1W_MASK, 1U);

    //
    // Select Interrupt Line.
    //
    MCAN_selectIntrLine(MCANA_DRIVER_BASE, MCAN_INTR_MASK_ALL, MCAN_INTR_LINE_NUM_1);

    //
    // Enable Interrupt Line.
    //
    MCAN_enableIntrLine(MCANA_DRIVER_BASE, MCAN_INTR_LINE_NUM_1, 1U);
#endif

#ifdef TRANSMIT
    for(loopCnt = 0U ; loopCnt < numOfMsg ; loopCnt++)
    {
        //
        // Enable Transmission Interrupt (One time configuration)
        //
        MCAN_txBufTransIntrEnable(MCANA_DRIVER_BASE, loopCnt, 1U);
    }

    for(loopCnt = 0U ; loopCnt < numOfMsg ; loopCnt++)
    {
        //
        // Write Tx Message to the Message RAM.
        //
        MCAN_writeMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_BUF, loopCnt, &txMsg[loopCnt]);

        //
        // Add request for transmission.
        //
        MCAN_txBufAddReq(MCANA_DRIVER_BASE, loopCnt);

        //
        // Wait for the isrIntr0Flag to be reset. (for transmission to be completed)
        //
        while(isrIntr0Flag)
        {
        }

        //
        // Reset the isrIntr0Flag
        //
        isrIntr0Flag = 1U;

        DEVICE_DELAY_US(500000);
    }
#endif    

    while(1)
    {
        //
        // Application code goes here
        //

    }

    //
    // Stop Application.
    //
    asm(" ESTOP0");
}

//
// This function will configure MCAN module.
//
static void MCANConfig(void)
{
    MCAN_RevisionId revId;
    MCAN_InitParams initParams;
    MCAN_ConfigParams configParams;
    MCAN_MsgRAMConfigParams    msgRAMConfigParams;
    MCAN_StdMsgIDFilterElement stdFiltelem;
    MCAN_BitTimingParams       bitTimes;

    //
    //  Initializing all structs to zero to prevent stray values
    //
    memset(&initParams, 0, sizeof(initParams));
    memset(&configParams, 0, sizeof(configParams));
    memset(&msgRAMConfigParams, 0, sizeof(msgRAMConfigParams));
    memset(&stdFiltelem, 0, sizeof(stdFiltelem));
    memset(&bitTimes, 0, sizeof(bitTimes));

    //
    // Initialize MCAN Init parameters.
    //
    initParams.fdMode            = 0x1U; // FD operation enabled.
    initParams.brsEnable         = 0x1U; // Bit rate switching for
                                         // transmissions enabled.
    initParams.txpEnable         = 0x0U; // Transmit pause disabled.
    initParams.efbi              = 0x0U; // Edge filtering disabled.
    initParams.pxhddisable       = 0x0U; // Protocol exception handling enabled
    initParams.darEnable         = 0x0U; // Enable Automatic retransmission of
                                       // messages not transmitted successfully
    initParams.wkupReqEnable     = 0x1U; // Wakeup request is enabled.
    initParams.autoWkupEnable    = 0x1U; // Auto-Wakeup is enabled.
    initParams.emulationEnable   = 0x1U; // Emulation/Debug Suspend is enabled.
    initParams.tdcEnable         = 0x1U; // Transmitter Delay Compensation is
                                         // enabled.
    initParams.wdcPreload        = 0xFFU; // Start value of the Message RAM
                                          // Watchdog Counter preload.

    //
    // Transmitter Delay Compensation parameters.
    //
    initParams.tdcConfig.tdcf    = 0xAU;
    initParams.tdcConfig.tdco    = 0x6U;

    //
    // Initialize MCAN Config parameters.
    //
    configParams.monEnable         = 0x0U; // Bus Monitoring Mode is disabled
    configParams.asmEnable         = 0x0U;  // Normal CAN operation.
    configParams.tsPrescalar       = 0xFU;  // Prescaler Value.
    configParams.tsSelect          = 0x2U;  // External Timestamp counter value used.
    configParams.timeoutSelect     = MCAN_TIMEOUT_SELECT_CONT;
    // Time-out counter source select.
    configParams.timeoutPreload    = 0xFFFFU; // Start value of the Timeout
                                              // Counter.
    configParams.timeoutCntEnable  = 0x0U; // Time-out Counter is disabled.
    configParams.filterConfig.anfe = 0x1U; // Accept in Rx FIFO 1.
    configParams.filterConfig.anfs = 0x1U; // Accept in Rx FIFO 1.

    configParams.filterConfig.rrfe = 0x0U; // Filter remote frames with
                                           // 29-bit extended IDs.
    configParams.filterConfig.rrfs = 0x0U; // Filter all remote frames with
                                           // 11-bit standard IDs.

    //
    // Initialize Message RAM Sections Configuration Parameters.
    //
    msgRAMConfigParams.flssa                = MCAN_STD_ID_FILT_START_ADDR;
    // Standard ID Filter List Start Address.
    msgRAMConfigParams.lss                  = MCAN_STD_ID_FILTER_NUM;
    // List Size: Standard ID.
    msgRAMConfigParams.flesa                = MCAN_EXT_ID_FILT_START_ADDR;
    // Extended ID Filter List Start Address.
    msgRAMConfigParams.lse                  = MCAN_EXT_ID_FILTER_NUM;
    // List Size: Extended ID.
    msgRAMConfigParams.txStartAddr          = MCAN_TX_BUFF_START_ADDR;
    // Tx Buffers Start Address.
    msgRAMConfigParams.txBufNum             = MCAN_TX_BUFF_SIZE;
    // Number of Dedicated Transmit Buffers.
    msgRAMConfigParams.txFIFOSize           = MCAN_TX_FQ_SIZE; 
    // Number of Tx FIFO or Tx Queue Elements
    msgRAMConfigParams.txBufMode            = 0U; //Tx FIFO operation
    msgRAMConfigParams.txBufElemSize        = MCAN_TX_BUFF_ELEM_SIZE;
    // Tx Buffer Element Size.
    msgRAMConfigParams.txEventFIFOStartAddr = MCAN_TX_EVENT_START_ADDR;
    // Tx Event FIFO Start Address.
    msgRAMConfigParams.txEventFIFOSize      = MCAN_TX_BUFF_SIZE;
    // Event FIFO Size.
    msgRAMConfigParams.txEventFIFOWaterMark = NUM_OF_MSG;
    // Level for Tx Event FIFO watermark interrupt.
    msgRAMConfigParams.rxFIFO0startAddr     = MCAN_FIFO_0_START_ADDR;
    // Rx FIFO0 Start Address.
    msgRAMConfigParams.rxFIFO0size          = MCAN_FIFO_0_NUM;
    // Number of Rx FIFO elements.
    msgRAMConfigParams.rxFIFO0waterMark     = 3U; // Rx FIFO0 Watermark.
    msgRAMConfigParams.rxFIFO0OpMode        = 0U; // FIFO blocking mode.
    msgRAMConfigParams.rxFIFO1startAddr     = MCAN_FIFO_1_START_ADDR;
    // Rx FIFO1 Start Address.
    msgRAMConfigParams.rxFIFO1size          = MCAN_FIFO_1_NUM;
    // Number of Rx FIFO elements.
    msgRAMConfigParams.rxFIFO1waterMark     = NUM_OF_MSG; // Level for Rx FIFO 1
                                                  // watermark interrupt.
    msgRAMConfigParams.rxFIFO1OpMode        = 0U; // FIFO blocking mode.
    msgRAMConfigParams.rxBufStartAddr       = MCAN_RX_BUFF_START_ADDR;
    // Rx Buffer Start Address.
    msgRAMConfigParams.rxBufElemSize        = MCAN_RX_BUFF_ELEM_SIZE;
    // Rx Buffer Element Size.
    msgRAMConfigParams.rxFIFO0ElemSize      = MCAN_FIFO_0_ELEM_SIZE;
    // Rx FIFO0 Element Size.
    msgRAMConfigParams.rxFIFO1ElemSize      = MCAN_FIFO_1_ELEM_SIZE;
    // Rx FIFO1 Element Size.

    //
    // Initialize Rx Buffer Configuration parameters.
    //
    stdFiltelem.sfid2              = 0xFU; // Standard Filter ID 2.
    stdFiltelem.sfid1              = 0x4U; // Standard Filter ID 1.
    stdFiltelem.sfec               = 0x2U; // Store into Rx FIFO 1
    stdFiltelem.sft                = 0x0U; // Range filter from SFID1 to SFID2

    //
    // Initialize bit timings.
    //
    bitTimes.nomRatePrescalar   = 0x3U; // Nominal Baud Rate Pre-scaler
    bitTimes.nomTimeSeg1        = 0x9U; // Nominal Time segment before SP
    bitTimes.nomTimeSeg2        = 0x8U; // Nominal Time segment after SP
    bitTimes.nomSynchJumpWidth  = 0x8U; // Nominal SJW
    bitTimes.dataRatePrescalar  = 0x1U; // Data Baud Rate Pre-scaler
    bitTimes.dataTimeSeg1       = 0x9U; // Data Time segment before SP
    bitTimes.dataTimeSeg2       = 0x8U; // Data Time segment after SP
    bitTimes.dataSynchJumpWidth = 0x8U; // Data SJW

    //
    // Get MCANSS Revision ID.
    //
    MCAN_getRevisionId(MCANA_DRIVER_BASE, &revId);

    //
    // Wait for Memory initialization to be completed.
    //
    while(FALSE == MCAN_isMemInitDone(MCANA_DRIVER_BASE));

    //
    // Put MCAN in SW initialization mode.
    //
    MCAN_setOpMode(MCANA_DRIVER_BASE, MCAN_OPERATION_MODE_SW_INIT);

    //
    // Wait till MCAN is not initialized.
    //
    while (MCAN_OPERATION_MODE_SW_INIT != MCAN_getOpMode(MCANA_DRIVER_BASE));

    //
    // Initialize MCAN module.
    //
    MCAN_init(MCANA_DRIVER_BASE, &initParams);

    //
    // Configure MCAN module.
    //
    MCAN_config(MCANA_DRIVER_BASE, &configParams);

    //
    // Configure Bit timings.
    //
    MCAN_setBitTime(MCANA_DRIVER_BASE, &bitTimes);

    //
    // Configure Message RAM Sections
    //
    MCAN_msgRAMConfig(MCANA_DRIVER_BASE, &msgRAMConfigParams);

    //
    // Configure Standard ID filter element
    //
    MCAN_addStdMsgIDFilter(MCANA_DRIVER_BASE, 0U, &stdFiltelem);

    //
    // Enable External timeStamp overflow interrupt
    //
    MCAN_extTSEnableIntr(MCANA_DRIVER_BASE, 1);

    //
    // Configure Timestamp Counter
    //
    MCAN_extTSCounterConfig(MCANA_DRIVER_BASE, MCAN_TS_PRESCALAR);

    //
    // Enable External Timestamp Counter
    //
    MCAN_extTSCounterEnable(MCANA_DRIVER_BASE, 1U);

    //
    // Take MCAN out of the SW initialization mode
    //
    MCAN_setOpMode(MCANA_DRIVER_BASE, MCAN_OPERATION_MODE_NORMAL);

    while (MCAN_OPERATION_MODE_NORMAL != MCAN_getOpMode(MCANA_DRIVER_BASE));
}

//
// This function will configure X-BAR for MCAN interrupts.
//
static void MCANIntrConfig(void)
{

    Interrupt_initModule();
    Interrupt_initVectorTable();

#ifdef TRANSMIT
    Interrupt_register(INT_MCANA_0,&MCANIntr0ISR);
    Interrupt_enable(INT_MCANA_0);
#else    
    Interrupt_register(INT_MCANA_1,&MCANIntr1ISR);
    Interrupt_enable(INT_MCANA_1);
#endif    
    Interrupt_register(INT_MCANA_WAKE,&MCANTSIntrISR);
    Interrupt_enable(INT_MCANA_WAKE);

    Interrupt_enableGlobal();

}

#ifdef TRANSMIT
//
// This is Interrupt Service Routine for MCAN interrupt 0.
//
__interrupt void MCANIntr0ISR(void)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(MCANA_DRIVER_BASE);
    if (MCAN_MSG_INT != intrStatus)
    {
        error++;
    }

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(MCANA_DRIVER_BASE, intrStatus);

    //
    //  Clearing the interrupt lineNum
    //
    MCAN_clearInterrupt(MCANA_DRIVER_BASE, 0x1U);

    //
    //  Check to see if the interrupt is caused by a message being
    //  received in dedicated RX Buffers
    //
    if((MCAN_INTR_SRC_TRANS_COMPLETE & intrStatus) == MCAN_INTR_SRC_TRANS_COMPLETE)
    {
        isrIntr0Flag = 0;

        msgCount++;
    }
    if((MCAN_INTR_SRC_TX_EVT_FIFO_WATERMARK & intrStatus) == MCAN_INTR_SRC_TX_EVT_FIFO_WATERMARK)
    {
        //
        // Read Tx Event FIFO Status
        //
        MCAN_getTxEventFIFOStatus(MCANA_DRIVER_BASE, &TxEFS);

        //
        // Read all Tx Event FIFO Elements once the
        // watermark is hit, so that the FIFO is empty again
        //
        while(TxEFS.fillLvl)
        {
            //
            // Read Tx Event FIFO Element Data from Message RAM
            //
            MCAN_readTxEventFIFO(MCANA_DRIVER_BASE, &TxEvent);

            //
            // Store Tx FIFO Element information into predefined array
            //
            TxEventArray[j] = TxEvent;

            //
            // Store Tx Timestamps into predefined array
            //
            a_txts[j] = TxEvent.txts;
            j++;

            //
            // Write Acknowledge to increment Get Index
            // which will point to the next element in the FIFO
            //
            MCAN_writeTxEventFIFOAck(MCANA_DRIVER_BASE, TxEFS.getIdx);

            //
            // Read FIFO Status to check Fill Level
            //
            MCAN_getTxEventFIFOStatus(MCANA_DRIVER_BASE, &TxEFS);
        }
    }

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
#endif

#ifndef TRANSMIT
//
// This is Interrupt Service Routine for MCAN interrupt 1.
//
__interrupt void MCANIntr1ISR(void)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(MCANA_DRIVER_BASE);
    if (MCAN_MSG_INT != intrStatus)
    {
        error++;
    }

    error++;

    //
    // Clear the interrupt Status.
    //
    MCAN_clearIntrStatus(MCANA_DRIVER_BASE, intrStatus);

    //
    //  Clearing the interrupt lineNum
    //
    MCAN_clearInterrupt(MCANA_DRIVER_BASE, 0x2U);

    if((intrStatus & MCAN_INTR_SRC_RX_FIFO1_WATERMARK) == MCAN_INTR_SRC_RX_FIFO1_WATERMARK)
    {
        RxFS.num = MCAN_RX_FIFO_NUM_1;
        MCAN_getRxFIFOStatus(MCANA_DRIVER_BASE, &RxFS);

        while(RxFS.fillLvl)
        {
            MCAN_readMsgRam(MCANA_DRIVER_BASE, MCAN_MEM_TYPE_FIFO, 0U,
                            MCAN_RX_FIFO_NUM_1, &rxMsg1);

            rxMsg[j] = rxMsg1;
            a_rxts[j] = rxMsg1.rxts;
            j++;

            MCAN_writeRxFIFOAck(MCANA_DRIVER_BASE, MCAN_RX_FIFO_NUM_1,
                                RxFS.getIdx);

            MCAN_getRxFIFOStatus(MCANA_DRIVER_BASE, &RxFS);                    
        }
    }

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}
#endif 

interrupt void MCANTSIntrISR(void)
{
    uint32_t intrStatus;

    intrStatus = MCAN_getIntrStatus(MCANA_DRIVER_BASE);

    //
    // Clear the External Counter Overflow Interrupt Bit to decrement the interrupt counter
    //
    MCAN_extTSClearRawStatus(MCANA_DRIVER_BASE);

    //
    // Clear the interrupt status.
    //
    MCAN_clearIntrStatus(MCANA_DRIVER_BASE, intrStatus);

    //
    // Clear External Counter Interrupt
    //
    MCAN_extTSWriteEOI(MCANA_DRIVER_BASE);

    if (MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND == (intrStatus & MCAN_INTR_SRC_TIMESTAMP_WRAPAROUND))
    {
    	tsInterruptCntr++ ;
    }
    else
    {
    	error++;
    }

    //
    // Clearing the interrupt Line
    //
    MCAN_clearInterrupt(MCANA_DRIVER_BASE, 0x0);

    //
    // Acknowledge this interrupt located in group 9
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

}
