//#############################################################################
//
// FILE:   mcan_ex2_classic_receive_bitfield.c
//
// TITLE:  MCAN Classic frames receive using Rx Buffer using bit field structures
//
//! \addtogroup bitfield_example_list
//! <h1> MCAN Classic frames receive using Rx Buffer </h1>
//!
//! This simple example shows external communication between the MCAN module
//! and another MCAN node. It shows how to receive classic CAN frames.
//! The GPIOs of MCAN should be connected to a CAN Transceiver.
//! Standard Identifier (STD ID) 0x4 is received with
//! 8 data bytes. Run on LaunchPad with CAN Transceiver.
//! Run with example:mcan_ex1_classic_transmit_bitfield for TX
//!
//! \b Hardware \b Required \n
//!  - A C2000 board with CAN transceiver
//!
//! \b External \b Connections \n
//!  Both nodes should communicate through CAN transceivers.
//!
//!  - MCANTX is on GPIO4, MCANRX is on GPIO5
//!
//! \b Watch \b Variables \n
//!  - rxMsg
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "f28x_project.h"

//
// Defines.
//
//
//  Write HW register
//
#define HW_WR_REG32(reg, val)               (*((volatile uint32_t *)(reg)) = val)
#define HW_RD_REG32(addr)                   (*(volatile uint32_t *) addr)

//
// MCAN config defines
//
#define BF_MCAN_WAKEUPREQEN                 (0U)
#define BF_MCAN_AUTOWAKEUP                  (0U)
#define BF_MCAN_DBGSUSP_FREE                (0U)
#define BF_MCAN_FDOE                        (0U)
#define BF_MCAN_BRSE                        (0U)
#define BF_MCAN_TXP                         (0U)
#define BF_MCAN_EFBI                        (0U)
#define BF_MCAN_PXHD                        (0U)
#define BF_MCAN_DAR                         (0U)
#define BF_MCAN_TDCF                        (0U)
#define BF_MCAN_TDCO                        (0U)
#define BF_MCAN_WDC                         (0U)
#define BF_MCAN_TDC                         (0U)
#define BF_MCAN_NBTP_NSJW                   (0x8U)
#define BF_MCAN_NBTP_NTSEG2                 (0x8U)
#define BF_MCAN_NBTP_NTSEG1                 (0x9U)
#define BF_MCAN_NBTP_NBRP                   (0x3U)
#define BF_MCAN_DBTP_DBRP                   (0x1U)
#define BF_MCAN_DBTP_DSJW                   (0x8U)
#define BF_MCAN_DBTP_DTSEG1                 (0x9U)
#define BF_MCAN_DBTP_DTSEG2                 (0x8U)
#define BF_MCAN_MSG_ID                      (((uint32_t)(0x4)) << 18U)
#define BF_MCAN_MSG_RTR                     (0U)
#define BF_MCAN_MSG_XTD                     (1U)
#define BF_MCAN_MSG_ESI                     (0U)
#define BF_MCAN_MSG_DLC                     (8U) // 8 Bytes max payload
#define BF_MCAN_MSG_BRS                     (0U)
#define BF_MCAN_MSG_FDF                     (0U)
#define BF_MCAN_MSG_EFC                     (0U)
#define BF_MCAN_MSG_MM                      (0xAAU)
#define BF_MCAN_STD_ID_FILT_START_ADDR      (0x0U)
#define BF_MCAN_STD_ID_FILTER_NUM           (1U)
#define BF_MCAN_RX_BUFF_START_ADDR          (BF_MCAN_STD_ID_FILT_START_ADDR + (BF_MCAN_STD_ID_FILTER_NUM * BF_MCANSS_STD_ID_FILTER_SIZE_WORDS * 4U ))//(0x4U)
#define BF_MCAN_RX_BUFF_ELEM_SIZE           (0x0U) //8 Bytes max payload
#define BF_MCANSS_STD_ID_FILTER_SIZE_WORDS     (1U)
#define BF_MCANSS_STD_ID_FILTER_SFID2_SHIFT    (0U)
#define BF_MCANSS_STD_ID_FILTER_SFID1_SHIFT    (16U)
#define BF_MCANSS_STD_ID_FILTER_SFEC_SHIFT     (27U)
#define BF_MCANSS_STD_ID_FILTER_SFT_SHIFT      (30U)
#define BF_MCAN_STD_ID_SFID2                   (0x0U)
#define BF_MCAN_STD_ID_SFID1                   (0x4U)
#define BF_MCAN_STD_ID_SFEC                    (0x7U)
#define BF_MCAN_PAYLOAD                        (8U) // 8 Bytes max payload
#define BF_MCANSS_RX_BUFFER_ELEM_ID_SHIFT      (0U)
#define BF_MCANSS_RX_BUFFER_ELEM_ID_MASK       (0x1FFFFFFFU)
#define BF_MCANSS_RX_BUFFER_ELEM_RTR_SHIFT     (29U)
#define BF_MCANSS_RX_BUFFER_ELEM_RTR_MASK      (0x20000000U)
#define BF_MCANSS_RX_BUFFER_ELEM_XTD_SHIFT     (30U)
#define BF_MCANSS_RX_BUFFER_ELEM_XTD_MASK      (0x40000000U)
#define BF_MCANSS_RX_BUFFER_ELEM_ESI_SHIFT     (31U)
#define BF_MCANSS_RX_BUFFER_ELEM_ESI_MASK      (0x80000000U)
#define BF_MCANSS_RX_BUFFER_ELEM_RXTS_SHIFT    (0U)
#define BF_MCANSS_RX_BUFFER_ELEM_RXTS_MASK     (0x0000FFFFU)
#define BF_MCANSS_RX_BUFFER_ELEM_DLC_SHIFT     (16U)
#define BF_MCANSS_RX_BUFFER_ELEM_DLC_MASK      (0x000F0000U)
#define BF_MCANSS_RX_BUFFER_ELEM_BRS_SHIFT     (20U)
#define BF_MCANSS_RX_BUFFER_ELEM_BRS_MASK      (0x00100000U)
#define BF_MCANSS_RX_BUFFER_ELEM_FDF_SHIFT     (21U)
#define BF_MCANSS_RX_BUFFER_ELEM_FDF_MASK      (0x00200000U)
#define BF_MCANSS_RX_BUFFER_ELEM_FIDX_SHIFT    (24U)
#define BF_MCANSS_RX_BUFFER_ELEM_FIDX_MASK     (0x7F000000U)
#define BF_MCANSS_RX_BUFFER_ELEM_ANMF_SHIFT    (31U)
#define BF_MCANSS_RX_BUFFER_ELEM_ANMF_MASK     (0x80000000U)

//  MCAN RAM base address
//
#define MCANA_MSG_RAM_BASE                  (0x00058000U)

//
// MCAN defines
//
#define MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG (0x00080000U)
#define MCAN_INTR_MASK_ALL                  (0x3FFFFFFFU)


/**
 * \brief  Structure for MCAN new data flag for Rx buffer.
 */
struct MCAN_RxNewDataStatus
{
    uint32_t statusLow;
    /**< New data flag for Rx buffer no. 0 to 31 */
    uint32_t statusHigh;
    /**< New data flag for Rx buffer no. 32 to 63 */
}newData;


struct MCAN_RxBufElement
{
    uint32_t id;
    /**< Identifier */
    uint32_t rtr;
    /**< Remote Transmission Request
     *   0 = Received frame is a data frame
     *   1 = Received frame is a remote frame
     */
    uint32_t xtd;
    /**< Extended Identifier
     *   0 = 11-bit standard identifier
     *   1 = 29-bit extended identifier
     */
    uint32_t esi;
    /**< Error State Indicator
     *   0 = Transmitting node is error active
     *   1 = Transmitting node is error passive
     */
    uint32_t rxts;
    /**< Rx Timestamp */
    uint32_t dlc;
    /**< Data Length Code
     *   0-8  = CAN + CAN FD: received frame has 0-8 data bytes
     *   9-15 = CAN: received frame has 8 data bytes
     *   9-15 = CAN FD: received frame has 12/16/20/24/32/48/64 data bytes
     */
    uint32_t brs;
    /**< Bit Rat Switching
     *   0 = Frame received without bit rate switching
     *   1 = Frame received with bit rate switching
     */
    uint32_t fdf;
    /**< FD Format
     *   0 = Standard frame format
     *   1 = CAN FD frame format (new DLC-coding and CRC)
     */
    uint32_t fidx;
    /**< Filter Index */
    uint32_t anmf;
    /**< Accepted Non-matching Frame
     *   0 = Received frame matching filter index FIDX
     *   1 = Received frame did not match any Rx filter element
     */
    uint16_t  data[BF_MCAN_PAYLOAD];
    /**< Data bytes.
     *   Only first dlc number of bytes are valid.
     */
}rxMsg[1], elem;

//
// Global Variables.
//
//
//  receive message
//
uint16_t bf_mcan_data[BF_MCAN_PAYLOAD];
static uint32_t objSize[8]      = {4, 5, 6, 7, 8, 10, 14, 18};
static uint32_t dataSize[16]    = {0,  1,  2,  3,  4,  5,  6,  7, 8, 8, 8, 8, 8, 8, 8, 8};

//
//  Other variables
//
int32_t loopCnt = 0U, error=0;

//
// Function Prototype.
//
static void MCANConfig(void);
static void MCANIntrConfig(void);
static void MCAN_readMsg(uint32_t           baseAddr,
                         uint32_t           elemAddr,
                         struct MCAN_RxBufElement *elem);
__interrupt void MCANIntr1ISR(void);


void main()
{
    uint32_t cnt            = 0U;
    uint32_t regVal = 0U;

    //
    // Initialize device clock and peripherals
    //
    InitSysCtrl();

    //
    // Initialize GPIO and configure GPIO pins
    //
    //
    // Initialize GPIO
    //
    InitGpio();

    //
    // Configure the divisor for the MCAN bit-clock
    //
    ClkCfgRegs.AUXCLKDIVSEL.bit.MCANCLKDIV = 2U;

    //
    // ISR Configuration.
    //
    MCANIntrConfig();

    //
    // Configuring the GPIOs for MCAN.
    //
    GPIO_SetupPinMux(4U, GPIO_MUX_CPU1, 0x03U);//TX
    GPIO_SetupPinMux(5U, GPIO_MUX_CPU1, 0x05U);//RX

    //
    // Configure the MCAN Module.
    //
    MCANConfig();

    //
    // Initialize message to receive
    //
    rxMsg[loopCnt].id = 0U;
    rxMsg[loopCnt].rtr = 0U;
    rxMsg[loopCnt].xtd = 0U;
    rxMsg[loopCnt].esi = 0U;
    rxMsg[loopCnt].rxts = 0U;   // Rx Timestamp
    rxMsg[loopCnt].dlc = 0U;
    rxMsg[loopCnt].brs = 0U;
    rxMsg[loopCnt].fdf = 0U;
    rxMsg[loopCnt].fidx = 0U;   // Filter Index
                                // (of matching Rx acceptance filter element)
    rxMsg[loopCnt].anmf = 0U;   // Accepted Non-matching Frame

    for(cnt = 0U;cnt < dataSize[BF_MCAN_MSG_DLC];cnt++)
    {
        rxMsg[loopCnt].data[cnt] = 0;
    }


    //
    // Configure the MCAN Module.
    //
    MCANConfig();

    //
    // Enable Interrupts.
    //
    regVal  = McanaRegs.MCAN_IE.all;
    regVal |= MCAN_INTR_MASK_ALL;
    McanaRegs.MCAN_IE.all = regVal;

    //
    // Select Interrupt Line.
    //
    regVal  = McanaRegs.MCAN_ILS.all;
    regVal |= MCAN_INTR_MASK_ALL;
    McanaRegs.MCAN_ILS.all = regVal;

    //
    // Enable Interrupt Line.
    //
    regVal = McanaRegs.MCAN_ILE.all;
    regVal  &= ~((uint32_t) 0x1U << 0x1U);
    regVal  |= (uint32_t) (0x1U << 0x1U);
    McanaRegs.MCAN_ILE.all = regVal;

    while(1)
    {
        //
        //  Wait for message receive
        //
        F28x_usDelay(2000);
    }

}


//
// This function will configure X-BAR for MCAN interrupts.
//
static void MCANIntrConfig(void)
{

    //
     // Disable CPU interrupts
     //
     DINT;

     //
     // Initialize the PIE control registers to their default state.
     // The default state is all PIE interrupts disabled and flags
     // are cleared.
     //
     InitPieCtrl();

     //
     // Disable CPU interrupts and clear all CPU interrupt flags
     //
     IER = 0x0000;
     IFR = 0x0000;

     //
     // Initialize the PIE vector table with pointers to the shell Interrupt
     // Service Routines (ISR)
     //
     InitPieVectTable();

     //
     // Register the interrupt ISR
     //
     EALLOW;  // This is needed to write to EALLOW protected registers
     PieVectTable.MCANA_1_INT = &MCANIntr1ISR;
     EDIS;    // This is needed to disable write to EALLOW protected registers

     //
     // Enable Interrupts
     //
     PieCtrlRegs.PIEIER9.bit.INTx10 = 0x1;   // Enable PIE Group 9 INT10
     IER |= M_INT9;                          // Enable CPU INT9
     EINT;                                   // Enable Global Interrupts

     EnableInterrupts();

}

//
// This is Interrupt Service Routine for MCAN interrupt 1.
//
__interrupt void MCANIntr1ISR(void)
{
    uint32_t intrStatus;
    uint32_t startAddr      = 0U;
    uint32_t elemSize       = 0U;
    uint32_t elemAddr       = 0U;

    intrStatus = McanaRegs.MCAN_IR.all;

    //
    // Clear the interrupt Status.
    //
    McanaRegs.MCAN_IR.all = intrStatus;

    //
    //  Clearing the interrupt lineNum
    //
    McanaSsRegs.MCANSS_EOI.bit.EOI= 0x2;

    //
    //  Check to see if the interrupt is caused by a message being
    //  received in dedicated RX Buffers
    //

    if((MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG & intrStatus) == MCAN_INTR_SRC_DEDICATED_RX_BUFF_MSG)
    {
        //
        // Read the NewData registers
        //
        newData.statusLow = McanaRegs.MCAN_NDAT1.all;
        newData.statusHigh = McanaRegs.MCAN_NDAT2.all;

        //
        //  If message is received in buffer element 0, read payload
        //
        if((newData.statusLow & (1UL << 0U)) != 0)
        {
            startAddr = (uint32_t)(McanaRegs.MCAN_RXBC.bit.RBSA << 2U);
            elemSize    = (objSize[McanaRegs.MCAN_RXESC.bit.RBDS]);
            elemSize *= 4U;
            elemAddr  = startAddr + (elemSize * 0);
            MCAN_readMsg(MCANA_MSG_RAM_BASE, elemAddr, &elem);

            rxMsg[loopCnt] = elem;
        }

        //
        //  Clearing the NewData registers
        //
        McanaRegs.MCAN_NDAT1.all = newData.statusLow;
        McanaRegs.MCAN_NDAT2.all = newData.statusHigh;
    }
    else
    {
        error++;

        //
        //  Interrupt handling for other interrupt sources goes here
        //

    }

    //
    // Clear the current interrupt and enable future interrupts
    //
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}

//
// This function is used to read received message from Message RAM.
//
static void MCAN_readMsg(uint32_t           baseAddr,
                         uint32_t           elemAddr,
                         struct MCAN_RxBufElement *elem)
{
    uint32_t regVal = 0U, loopCnt = 0U;

    regVal   = HW_RD_REG32((baseAddr + elemAddr));

    elem->id = (uint32_t) ((regVal & BF_MCANSS_RX_BUFFER_ELEM_ID_MASK)
                           >> BF_MCANSS_RX_BUFFER_ELEM_ID_SHIFT);
    elem->rtr = (uint32_t) ((regVal & BF_MCANSS_RX_BUFFER_ELEM_RTR_MASK)
                            >> BF_MCANSS_RX_BUFFER_ELEM_RTR_SHIFT);
    elem->xtd = (uint32_t) ((regVal & BF_MCANSS_RX_BUFFER_ELEM_XTD_MASK)
                            >> BF_MCANSS_RX_BUFFER_ELEM_XTD_SHIFT);
    elem->esi = (uint32_t) ((regVal & BF_MCANSS_RX_BUFFER_ELEM_ESI_MASK)
                            >> BF_MCANSS_RX_BUFFER_ELEM_ESI_SHIFT);

    elemAddr  += 4U;
    regVal     = HW_RD_REG32((baseAddr + elemAddr));
    elem->rxts = (uint32_t) ((regVal & BF_MCANSS_RX_BUFFER_ELEM_RXTS_MASK)
                             >> BF_MCANSS_RX_BUFFER_ELEM_RXTS_SHIFT);
    elem->dlc = (uint32_t) ((regVal & BF_MCANSS_RX_BUFFER_ELEM_DLC_MASK)
                            >> BF_MCANSS_RX_BUFFER_ELEM_DLC_SHIFT);
    elem->brs = (uint32_t) ((regVal & BF_MCANSS_RX_BUFFER_ELEM_BRS_MASK)
                            >> BF_MCANSS_RX_BUFFER_ELEM_BRS_SHIFT);
    elem->fdf = (uint32_t) ((regVal & BF_MCANSS_RX_BUFFER_ELEM_FDF_MASK)
                            >> BF_MCANSS_RX_BUFFER_ELEM_FDF_SHIFT);
    elem->fidx = (uint32_t) ((regVal & BF_MCANSS_RX_BUFFER_ELEM_FIDX_MASK)
                             >> BF_MCANSS_RX_BUFFER_ELEM_FIDX_SHIFT);
    elem->anmf = (uint32_t) ((regVal & BF_MCANSS_RX_BUFFER_ELEM_ANMF_MASK)
                             >> BF_MCANSS_RX_BUFFER_ELEM_ANMF_SHIFT);
    elemAddr += 4U;

    loopCnt = 0U;
    /* Reading words from message RAM and forming payload bytes out of it */
    while((4U <= (dataSize[elem->dlc] - loopCnt)) &&
           (0U != (dataSize[elem->dlc] - loopCnt)))
    {
        regVal = HW_RD_REG32((baseAddr + elemAddr));
        elem->data[loopCnt]       = (uint16_t)(regVal & 0x000000FFU);
        elem->data[(loopCnt + 1U)] = (uint16_t)((regVal & 0x0000FF00U) >> 8U);
        elem->data[(loopCnt + 2U)] = (uint16_t)((regVal & 0x00FF0000U) >> 16U);
        elem->data[(loopCnt + 3U)] = (uint16_t)((regVal & 0xFF000000U) >> 24U);
        elemAddr += 4U;
        loopCnt  += 4U;
    }
    /* Reading remaining bytes from message RAM */
    if(0U < (dataSize[elem->dlc] - loopCnt))
    {
        regVal = HW_RD_REG32((baseAddr + elemAddr));
        elem->data[loopCnt]       = (uint16_t)(regVal & 0x000000FFU);
        elem->data[(loopCnt + 1U)] = (uint16_t)((regVal & 0x0000FF00U) >> 8U);
        elem->data[(loopCnt + 2U)] = (uint16_t)((regVal & 0x00FF0000U) >> 16U);
    }

}

//
// Configure the MCAN module
//
static void MCANConfig(void)
{
    uint32_t startAddr      = 0U;
    uint32_t elemAddr       = 0U, regVal=0;

    //
    // Wait for memory initialization to happen.
    //
    while(0U == McanaSsRegs.MCANSS_STAT.bit.MEM_INIT_DONE)
    {
        ;
    }

    //
    // Put MCAN in SW initialization mode.
    //
    McanaRegs.MCAN_CCCR.bit.INIT = 1U;

    //
    // Wait till MCAN is not initialized.
    //
    while(0U == McanaRegs.MCAN_CCCR.bit.INIT)
    {
        ;
    }

    //***************************************************************
    // MCAN init
    //***************************************************************

    //
    //  Configure MCAN wakeup and clock stop controls
    //
    McanaSsRegs.MCANSS_CTRL.bit.WAKEUPREQEN     = BF_MCAN_WAKEUPREQEN;
    McanaSsRegs.MCANSS_CTRL.bit.AUTOWAKEUP      = BF_MCAN_AUTOWAKEUP;
    McanaSsRegs.MCANSS_CTRL.bit.DBGSUSP_FREE    = BF_MCAN_DBGSUSP_FREE;

    //
    //  Unlock write protected registers
    //
    McanaRegs.MCAN_CCCR.bit.CCE     = 1U;

    //
    //  Configure MCAN mode(FD vs Classic CAN operation) and controls
    //
    McanaRegs.MCAN_CCCR.bit.FDOE    = BF_MCAN_FDOE;
    McanaRegs.MCAN_CCCR.bit.BRSE    = BF_MCAN_BRSE;
    McanaRegs.MCAN_CCCR.bit.TXP     = BF_MCAN_TXP;
    McanaRegs.MCAN_CCCR.bit.EFBI    = BF_MCAN_EFBI;
    McanaRegs.MCAN_CCCR.bit.PXHD    = BF_MCAN_PXHD;
    McanaRegs.MCAN_CCCR.bit.DAR     = BF_MCAN_DAR;

    //
    //  Configure Transceiver Delay Compensation
    //
    McanaRegs.MCAN_TDCR.bit.TDCF    = BF_MCAN_TDCF;
    McanaRegs.MCAN_TDCR.bit.TDCO    = BF_MCAN_TDCO;
    McanaRegs.MCAN_RWD.bit.WDC      = BF_MCAN_WDC;
    McanaRegs.MCAN_DBTP.bit.TDC     = BF_MCAN_TDC;

    //***************************************************************
    // MCAN timing configuration
    //***************************************************************

    //
    // Configure Bit timings.
    //
    //
    //  Nominal bit timing
    //
    McanaRegs.MCAN_NBTP.bit.NSJW    = BF_MCAN_NBTP_NSJW;
    McanaRegs.MCAN_NBTP.bit.NTSEG2  = BF_MCAN_NBTP_NTSEG2;
    McanaRegs.MCAN_NBTP.bit.NTSEG1  = BF_MCAN_NBTP_NTSEG1;
    McanaRegs.MCAN_NBTP.bit.NBRP    = BF_MCAN_NBTP_NBRP;

    //
    //  Data bit timing - NOT required for Classic CAN
    //

    //***************************************************************
    // Configure Message RAM Sections
    //***************************************************************

    McanaRegs.MCAN_SIDFC.bit.FLSSA = (BF_MCAN_STD_ID_FILT_START_ADDR >> 2U);
    McanaRegs.MCAN_SIDFC.bit.LSS = BF_MCAN_STD_ID_FILTER_NUM;
    McanaRegs.MCAN_RXBC.bit.RBSA = (BF_MCAN_RX_BUFF_START_ADDR >> 2U);
    McanaRegs.MCAN_RXESC.bit.RBDS = BF_MCAN_RX_BUFF_ELEM_SIZE;


    //
    // Configure Standard ID filter element
    //
    startAddr = McanaRegs.MCAN_SIDFC.bit.FLSSA;
    startAddr = (uint32_t) (startAddr << 2U);
    elemAddr  = startAddr + (0 * BF_MCANSS_STD_ID_FILTER_SIZE_WORDS * 4U);

    regVal  = 0U;
    regVal |= ((uint32_t)BF_MCAN_STD_ID_SFID2 << BF_MCANSS_STD_ID_FILTER_SFID2_SHIFT);
    regVal |= ((uint32_t)BF_MCAN_STD_ID_SFID1 << BF_MCANSS_STD_ID_FILTER_SFID1_SHIFT);
    regVal |= ((uint32_t)BF_MCAN_STD_ID_SFEC << BF_MCANSS_STD_ID_FILTER_SFEC_SHIFT);
    HW_WR_REG32(MCANA_MSG_RAM_BASE + elemAddr, regVal);

    //
    //  Lock write protected registers
    //
    McanaRegs.MCAN_CCCR.bit.CCE     = 0U;

    //
    // Take MCAN out of the SW initialization mode
    //
    McanaRegs.MCAN_CCCR.bit.INIT    = 0U;

    while(1U == McanaRegs.MCAN_CCCR.bit.INIT)
    {
        ;
    }
}
