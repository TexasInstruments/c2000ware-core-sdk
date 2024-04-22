//****************************************************************************
//
// Shared RAM management (RAM_management)
//
// This example shows how to assign shared RAM for use by both the cpu2 and
// cpu1 core.
//
// Shared RAM regions are defined in  both the cpu2 and cpu1 linker
// files.
// In the In this example S0 and S1 are assigned to/owned by c2.
//  - c2_r_w_array[] is mapped to shared RAM GS0
//  - c2_r_array[] is mapped to shared RAM GS2
//
//###########################################################################
//
// $Release Date:  $
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

//
// Included Files
//
#include "F28x_Project.h"
#include "F2837xD_Ipc_drivers.h"

//
// Globals
//
uint16_t c2_r_w_array[256];   // mapped to GS1 of shared RAM owned by CPU02
uint16_t c2_r_array[256];     // mapped to GS0 of shared RAM owned by CPU01
#pragma DATA_SECTION(c2_r_array,"SHARERAMGS1");
#pragma DATA_SECTION(c2_r_w_array,"SHARERAMGS0");

extern uint16_t isrfuncLoadStart;
extern uint16_t isrfuncLoadEnd;
extern uint16_t isrfuncRunStart;
extern uint16_t isrfuncLoadSize;

//
// Function Prototypes
//
__interrupt void cpu_timer0_isr(void);
#pragma CODE_SECTION(cpu_timer0_isr,"isrfunc")
void Shared_Ram_dataWrite_c2(void);

//
// Main
//
void main(void)
{
//
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
//
//   InitSysCtrl();

//
// Step 2. Initialize GPIO:
// This example function is found in the F2837xD_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
//
// InitGpio();  // Skipped for this example

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
   DINT;

//
// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
//
   InitPieCtrl();

//
// Disable CPU interrupts and clear all CPU interrupt flags:
//
   IER = 0x0000;
   IFR = 0x0000;

//
// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
   InitPieVectTable();

//
// Wait until Shared RAM is available.
//
   while(!( MemCfgRegs.GSxMSEL.bit.MSEL_GS0 &
            MemCfgRegs.GSxMSEL.bit.MSEL_GS14 ))
   {
   }

//
//  Copy ISR routine to a specified RAM location to determine the size
//
    memcpy(&isrfuncRunStart, &isrfuncLoadStart, (uint32_t)&isrfuncLoadSize);

//
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
//
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.TIMER0_INT = &cpu_timer0_isr;
   EDIS;    // This is needed to disable write to EALLOW protected registers

//
// Step 4. Initialize the Device Peripheral. This function can be
//         found in F2837xD_CpuTimers.c
//
   InitCpuTimers();   // For this example, only initialize the Cpu Timers

//
// Configure CPU-Timer0 to interrupt every second:
// c2_FREQ in MHz, 1 second Period (in uSeconds)
//
   ConfigCpuTimer(&CpuTimer0, 200, 1000000);

//
// To ensure precise timing, use write-only instructions to write to the
// entire register.
//
   CpuTimer0Regs.TCR.all = 0x4000;

//
// Step 5. User specific code, enable interrupts:
//

//
// Enable CPU int1 which is connected to CPU-Timer 0
//
   IER |= M_INT1;

//
// Enable TINT0 in the PIE: Group 1 interrupt 7
//
   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

//
// Enable global Interrupts and higher priority real-time debug events:
//
   EINT;   // Enable Global interrupt INTM
   ERTM;   // Enable Global realtime interrupt DBGM

   while(1)
   {
        if(IPCRtoLFlagBusy(IPC_FLAG10) == 1)
        {
            //
            // Read c2_r_array and modify c2_r_w_array
            //
            Shared_Ram_dataWrite_c2();

            IPCRtoLFlagAcknowledge (IPC_FLAG10);
         }
   }
}

//
// cpu_timer0_isr - CPU Timer0 ISR
//
__interrupt void cpu_timer0_isr(void)
{
   EALLOW;
   CpuTimer0.InterruptCount++;
   GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
   EDIS;

   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// Shared_Ram_dataWrite_c2 - Read data from c2_r_array written by CPU01 and
//                           modify and write into c2_r_w_array
//                           c2_r_array[0] is used to hold the multiplier
//                           value.
//
void Shared_Ram_dataWrite_c2(void)
{
    uint16_t index;
    uint16_t multiplier;

    multiplier = c2_r_array[0];
    c2_r_w_array[0] = multiplier;

    for(index = 1; index < 256; index ++)
    {
        c2_r_w_array[index] = multiplier*c2_r_array[index];
    }
}

//
// End of file
//
