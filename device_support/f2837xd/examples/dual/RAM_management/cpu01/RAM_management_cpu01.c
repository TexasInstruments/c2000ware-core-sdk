//###########################################################################
//
// FILE:   RAM_management_cpu01.c
//
// TITLE:  RAM management Example for F2837xD.
//
//! \addtogroup dual_example_list
//! <h1> Shared RAM management (RAM_management) </h1>
//!
//! This example shows how to assign shared RAM for use by both the CPU02 and
//! CPU01 core.
//! Shared RAM regions are defined in  both the CPU02 and CPU01 linker files.
//! In this example GS0 and GS14 are assigned to/owned by CPU02. The remaining
//! shared RAM regions are owned by CPU01.
//! In this example:
//!
//! A pattern is written to c1_r_w_array and then IPC flag is sent to notify
//! CPU02 that data is ready to be read. CPU02 then reads the data from
//! c2_r_array and writes a modified pattern to c2_r_w_array. Once CPU02
//! acknowledges the IPC flag to , CPU01 reads the data from c1_r_array and
//! compares with expected result.
//!
//! A Timed ISR is also serviced in both CPUs. The ISRs are copied into the
//! shared RAM region owned by the respective CPUs. Each ISR toggles a GPIO.
//! Watch GPIO31 and GPIO34 on oscilloscope. If using the control card watch
//! LED1 and LED2 blink at different rates.
//!
//!  - c1_r_w_array[] is mapped to shared RAM GS1
//!  - c1_r_array[]   is mapped to shared RAM GS0
//!  - c2_r_array[]   is mapped to shared RAM GS1
//!  - c2_r_w_array[] is mapped to shared RAM GS0
//!  - cpu_timer0_isr in CPU02 is copied to shared RAM GS14 , toggles GPIO31
//!  - cpu_timer0_isr in CPU01 is copied to shared RAM GS15 , toggles GPIO34
//!
//! \b  Watch \b Variables
//!  - error Indicates that the data written is not correctly received by the
//!    other CPU.
//!
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
uint16_t c1_r_array[256];   // mapped to GS0 of shared RAM owned by CPU02
uint16_t c1_r_w_array[256]; // mapped to GS1 of shared RAM owned by CPU01
#pragma DATA_SECTION(c1_r_array,"SHARERAMGS0");
#pragma DATA_SECTION(c1_r_w_array,"SHARERAMGS1");

uint16_t error;
uint16_t multiplier;

extern uint16_t isrfuncLoadStart;
extern uint16_t isrfuncLoadEnd;
extern uint16_t isrfuncRunStart;
extern uint16_t isrfuncLoadSize;

//
// Function Prototypes
//
__interrupt void cpu_timer0_isr(void);
#pragma CODE_SECTION(cpu_timer0_isr,"isrfunc")

void Shared_Ram_dataRead_c1(void);
void Shared_Ram_dataWrite_c1(void);

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
    InitSysCtrl();

#ifdef _STANDALONE
#ifdef _FLASH
    //
    //  Send boot command to allow the CPU02 application to begin execution
    //
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#else
    //
    //  Send boot command to allow the CPU02 application to begin execution
    //
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_RAM);
#endif
#endif

//
// Step 2. Initialize GPIO:
//
    InitGpio();

//
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
//
    DINT;

//
// Initialize PIE control registers to their default state.
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
// This will populate the entire table, even if the __interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
//
    InitPieVectTable();

//
// Give GPIO31 Control to CPU02
//
    GPIO_SetupPinMux(31,GPIO_MUX_CPU2,0);
    GPIO_SetupPinOptions(31, GPIO_OUTPUT,0);

//
// Give GPIO34 Control to CPU01
//
    GPIO_SetupPinMux(34,GPIO_MUX_CPU1,0);
    GPIO_SetupPinOptions(34, GPIO_OUTPUT,0);

//
// Give Memory Access to GS0/ GS14 SARAM to CPU02
//
    while( !(MemCfgRegs.GSxMSEL.bit.MSEL_GS0 &
             MemCfgRegs.GSxMSEL.bit.MSEL_GS14))
    {
        EALLOW;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS0 = 1;
        MemCfgRegs.GSxMSEL.bit.MSEL_GS14 = 1;
        EDIS;
    }

//
//  Copy ISR routine to a specified RAM location to determine the size
//
    memcpy(&isrfuncRunStart, &isrfuncLoadStart, (uint32_t)&isrfuncLoadSize);

//
// Wait until
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
// c2_FREQ in MHz, 2 second Period (in uSeconds)
//
    ConfigCpuTimer(&CpuTimer0, 200, 2000000);

//
// To ensure precise timing, use write-only instructions to write to the
// entire register.
//
    CpuTimer0Regs.TCR.all = 0x4000;

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

    error = 0;
    multiplier = 0;

    Shared_Ram_dataWrite_c1();
    IPCLtoRFlagSet(IPC_FLAG10);

    while(1)
    {
        //
        // If there is no pending flag
        //
        if(IPCLtoRFlagBusy(IPC_FLAG10) == 0)
        {
            Shared_Ram_dataRead_c1();

            if(multiplier++ > 255)
            {
                multiplier = 0;
            }

            //
            // Write an array to a memory location owned by CPU01
            //
            Shared_Ram_dataWrite_c1();

            //
            // Set a flag to notify CPU02 that data is available
            //
            IPCLtoRFlagSet(IPC_FLAG10);
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
   GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
   EDIS;

   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// Shared_Ram_dataWrite_c1 - Write a pattern to an array in shared RAM
//
void Shared_Ram_dataWrite_c1(void)
{
    uint16_t index;

    //
    // Use first location to write a multiplier.
    //
    c1_r_w_array[0] = multiplier;

    for(index = 1; index < 256; index++)
    {
        c1_r_w_array[index] = index;

        //
        //the following code will attempt to write to a shared RAM
        //assigned to cpu2 and as a result will cause an error.
        //
        //c1_r_array[index] = 1000 + index;
    }
}

//
// Shared_Ram_dataRead_c1 - Read and compare an array from shared RAM
//
void Shared_Ram_dataRead_c1(void)
{
    uint16_t index;

    if(c1_r_array[0] == multiplier)
    {
       for(index = 1; index < 256; index++)
       {
           if(c1_r_array[index] != multiplier*c1_r_w_array[index])
           {
               error = 1;
           }
       }
    }
    else
    {
        error = 1;
    }
}

//
// End of file
//
