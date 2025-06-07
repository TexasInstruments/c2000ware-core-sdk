//#############################################################################
//
// FILE:   upp_sdr_tx_cpu01.c
//
// TITLE:  upp transmit example for F2837xD
//
//! \addtogroup cpu01_example_list
//! <h1> UPP Single Data Rate Transmit (upp_sdr_tx) </h1>
//!
//! This example sets up the F2837xD board's UPP with the single-data-rate(SDR)
//! interface as a transmitter.
//!
//! \b Important: In order to run this example, two F2837xD boards are required.
//! All the UPP pins from one board to the other must be connected with common
//! ground. One board must be loaded with this example code and the other board
//! must be loaded with the "upp_sdr_rx" example.
//!
//! \b Instructions:
//! # Load the "upp_sdr_tx" on board 1
//! # Load the "upp_sdr_rx" on board 2
//! # Run the "upp_sdr_rx" code on board 2 (Needs to be run before the tx code)
//! # Run the "upp_sdr_tx" code on board 1
//!
//! \b Watch \b Variables: \n
//! - \b TEST_STATUS - Equivalent to \b TEST_PASS if test finished correctly,
//!                    else the value is set to \b TEST_FAIL
//! - \b ErrCount - Error counter
//!
//
//
//      |-----------|               |-----------|
//      |           |=====D0-D7=====|           |
//      |  Device   |-----CLK-------|   Device  |
//      |  Board-1  |               |   Board-2 |
//      |    TX     |-----ENABLE----|     RX    |
//      |           |-----START-----|           |
//      |-----------|               |-----------|
//
//#############################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2025 Texas Instruments Incorporated - http://www.ti.com/
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
#include "F28x_Project.h"
#include "F2837xD_Upp_defines.h"

//
// Defines
//
#define TEST_PASS      0xABCDABCD
#define TEST_FAIL      0xDEADDEAD
#define LINE_CNT       4
#define BYTE_CNT       64
#define WIN_CNT        8
#define WIN_BYTE_CNT   256
#define WIN_WORD_CNT   128

//
// Globals
//
volatile long int ErrCount;
volatile long int TEST_STATUS = TEST_FAIL;
volatile long int eow_int_cnt = 0;
volatile long int eol_int_cnt = 0;
volatile long int RdValue = 0;
volatile long int WrValue = 0;
volatile int InitTxMsgRam = 0;

//
// Function Prototypes
//
extern void InitUpp1Gpio(void);
extern void SoftResetUpp(void);
interrupt void local_UPPA_ISR(void);

//
// Main
//
void main(void)
{
   int i;
   TEST_STATUS = TEST_FAIL;
   ErrCount = 0x0;

//
// Initialize System Control
//
   InitSysCtrl();

   DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flaLS
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
   InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
   EALLOW;
   IER = 0x0000;
   IFR = 0x0000;
   EDIS;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// LService Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
   InitPieVectTable();

   EALLOW;
   PieVectTable.UPPA_INT = &local_UPPA_ISR;

//
// Enable the Interrupt No 8.
//
   IER = M_INT8 ;

//
// Enable Interrupt for UPPA Interrupt.
//
   PieCtrlRegs.PIEIER8.bit.INTx15=1;

//
// Enable PIE & CPU level Interrupts.
//
   EnableInterrupts();

//
// Issue Soft Reset (internal) to uPP.
//
   SoftResetUpp();

//
// Configure the GPIO muxing for uPP pins.
//
   InitUpp1Gpio();

//
// Initialize the TX MSG RAM.
//
   for (i = 0; i < uPP_TX_MSGRAM_SIZE/2 ; i+=2)
   {
       WrValue = WrValue + 0x12345678;
       *(Uint32 *)(uPP_TX_MSGRAM_ADDR + i) = WrValue;
   }

//
// Configure uPP for TX
//
   UppRegs.IFCFG.bit.CLKDIVA = 0x4;      // Div8.
   UppRegs.IFCFG.bit.CLKINVA = 1;
   UppRegs.CHCTL.bit.MODE = uPP_TX_MODE; // Setup for TX.
   UppRegs.CHCTL.bit.DRA = uPP_SDR;      // SDR mode
   UppRegs.IFIVAL.all = 0x0000;          //Idle Value

//
// Enable EOL/EOW interrupt
//
   UppRegs.INTENSET.bit.EOLI = 1;
   UppRegs.INTENSET.bit.EOWI = 1;
   UppRegs.GINTEN.bit.GINTEN = 1;

//
// Enable the uPP module
//
   UppRegs.PERCTL.bit.PEREN = 1;

//
// Setup DMA channel
//
   UppRegs.CHIDESC0 = uPP_TX_MSGRAM_ADDR;
   UppRegs.CHIDESC1.bit.LCNT = LINE_CNT;
   UppRegs.CHIDESC1.bit.BCNT = BYTE_CNT;
   UppRegs.CHIDESC2.all = BYTE_CNT;

   while (eow_int_cnt < WIN_CNT);

//
// Disable the uPP to stop transmission after expected window count is done.
//
   UppRegs.PERCTL.bit.PEREN = 0;

//
// Determine example test status
//
   if (ErrCount == 0x0)
   {
      TEST_STATUS = TEST_PASS;
   }

//
// Example done
//
   asm("          ESTOP0");
   for(;;);
}

//
// local_UPPA_ISR - UPPA Interrupt Service Routine (ISR)
//
interrupt void local_UPPA_ISR(void)
{
   //
   // To receive more interrupts from this PIE group, acknowledge this
   // interrupt
   //
   int i;
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;

   if (UppRegs.GINTFLG.all != 0x0)
   {
         if(UppRegs.ENINTST.bit.EOWI == 0x1) //Check for EOW Interrupt flag
         {
            eow_int_cnt++;
            if (eow_int_cnt < (WIN_CNT - 1))
            {
             InitTxMsgRam = 1;
            }

            //
            //Enable EOL interrupt
            //
            UppRegs.INTENSET.bit.EOLI = 1;

            //
            //Clear the Status for EOW Interrupt
            //
            UppRegs.ENINTST.all = uPP_INT_EOWI;
            if (UppRegs.ENINTST.bit.EOWI != 0)
            {
                ErrCount++;
                asm ("      ESTOP0");
                for(;;);
            }
         }
         if(UppRegs.ENINTST.bit.EOLI == 0x1) // Check for EOL Interrupt Flag
         {
            eol_int_cnt++;

            //
            // Disable EOL Interrupt.
            //
            UppRegs.ENINTST.all = uPP_INT_EOLI;
            if (UppRegs.ENINTST.bit.EOLI != 0)
            {
                ErrCount++;
                asm ("      ESTOP0");
                for(;;);
            }
            UppRegs.INTENCLR.all = uPP_INT_EOLI;
            if (UppRegs.INTENSET.bit.EOLI != 0)
            {
                ErrCount++;
                asm ("      ESTOP0");
                for(;;);
            }

            //
            // Initialize the Channel Descriptor for Next window transfer.
            //
            if (eow_int_cnt < (WIN_CNT -1))
            {
                if (eow_int_cnt%2)
                {
                    if(InitTxMsgRam == 1)
                    {
                         for (i = 0; i < WIN_WORD_CNT ; i+=2)
                         {
                            WrValue = WrValue + 0x12345678;
                            *(Uint32 *)(uPP_TX_MSGRAM_ADDR + i) = WrValue;
                         }
                         InitTxMsgRam = 0;
                    }
                     UppRegs.CHIDESC0 = uPP_TX_MSGRAM_ADDR;
                     UppRegs.CHIDESC1.bit.LCNT = LINE_CNT;
                     UppRegs.CHIDESC1.bit.BCNT = BYTE_CNT;
                     UppRegs.CHIDESC2.all = BYTE_CNT;
                }
                else
                {
                    if(InitTxMsgRam == 1)
                    {
                        for (i = 0; i < WIN_WORD_CNT ; i+=2)
                        {
                            WrValue = WrValue + 0x12345678;
                            *(Uint32 *)((uPP_TX_MSGRAM_ADDR +
                                         WIN_WORD_CNT) + i) = WrValue;
                        }
                        InitTxMsgRam = 0;
                    }
                    UppRegs.CHIDESC0 = uPP_TX_MSGRAM_ADDR + (LINE_CNT *
                                                             BYTE_CNT);
                    UppRegs.CHIDESC1.bit.LCNT = LINE_CNT;
                    UppRegs.CHIDESC1.bit.BCNT = BYTE_CNT;
                    UppRegs.CHIDESC2.all = BYTE_CNT;
                }
            }
         }

      //
      // Clear Global Interrupt.
      //
      RdValue = UppRegs.ENINTST.all;
      UppRegs.GINTCLR.bit.GINTCLR = 1;
      if (UppRegs.GINTFLG.all != 0x0)
      {
          ErrCount++;
          asm ("      ESTOP0");
          for(;;);
      }
   }
}

//
// End of file
//
