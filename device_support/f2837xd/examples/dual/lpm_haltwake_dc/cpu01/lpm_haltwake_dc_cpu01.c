//###########################################################################
//
// FILE:   lpm_haltwake_dc_cpu01.c
//
// TITLE:  Halt entry and Exit Example for F2837xD CPU1.
//
//!  <h1>Low Power Modes: Halt Mode and Wakeup (lpm_haltwake)</h1>
//!
//!  This example puts the device into HALT mode. If the lowest
//!  possible current consumption in HALT mode is desired, the
//!  JTAG connector must be removed from the device board while
//!  the device is in HALT mode.
//!
//!  The example then wakes up the device from HALT using GPIO10.
//!  GPIO10 wakes the device from HALT mode when a high-to-low
//!  signal is detected on the pin. This pin must be pulsed by
//!  an external agent for wakeup.
//!
//!  The wakeup process begins as soon as GPIO10 is held low for the
//!  time indicated in the device datasheet. After the
//!  device wakes up, GPIO11 can be observed to go low.
//!
//!  GPIO10 is configured as the LPM wakeup pin to trigger a
//!  WAKEINT interrupt upon detection of a low pulse.
//!  Initially, pull GPIO10 high externally.
//!
//!     GPIO12 is assigned to CPU2 as a monitor pin for CPU2. CPU2 will be
//!  put into IDLE mode before CPU1 puts the device into HALT mode.
//!
//!  To observe when device wakes from HALT mode, monitor
//!  GPIO11 and GPIO12 with an oscilloscope (Cleared to 0 in WAKEINT ISR)
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

#ifdef _FLASH
//
// These are defined by the linker (see device linker command file)
//
extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadSize;
extern Uint16 RamfuncsRunStart;
#endif

//
// Defines
//
// Define if the INTOSC0/1 will be enabled during HALT
//
//#define HALT_OSCON    1        // OSC ON
#define HALT_OSCON    0        // OSC OFF

//
// Function Prototypes
//
__interrupt void local_WAKE_ISR(void);

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
    // Send boot command to allow the CPU2 application to begin execution
    //
    IPCBootCPU2(C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH);
#endif
#endif

    //
    // Step 2. Initialize GPIO:
    // This example function is found in the F2837xD_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    InitGpio();

    //
    // configure Gpios for this example
    //

    //
    // GPIO10 is the external wake-up source
    //
    GPIO_SetupPinMux(10,GPIO_MUX_CPU1,0);
    GPIO_SetupPinOptions(10,GPIO_INPUT,GPIO_PULLUP|GPIO_ASYNC);

    //
    // GPIO11 is an output
    //
    GPIO_SetupPinMux(11,GPIO_MUX_CPU1,0);
    GPIO_SetupPinOptions(11,GPIO_OUTPUT,0);

    //
    // GPU12 is an output and control given to CPU2
    //
    GPIO_SetupPinMux(12,GPIO_MUX_CPU2,0);
    GPIO_SetupPinOptions(12,GPIO_OUTPUT,0);

    EALLOW;
    //
    // Use GPIO10 to wake the CPU from Halt
    //
    CpuSysRegs.GPIOLPMSEL0.bit.GPIO10 = 1;
    EDIS;

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
    // Interrupts that are used in this example are re-mapped to
    // ISR functions found within this file.
    //
    EALLOW;  // This is needed to write to EALLOW protected registers
    PieVectTable.WAKE_INT = &local_WAKE_ISR;
    EDIS;

    //
    // Step 4. Initialize all the Device Peripherals:
    //
    // Not applicable for this example.

    //
    // Step 5. User specific code, enable interrupts:
    //

    //
    // Enable CPU INT1 which is connected to WakeInt:
    //
    IER |= M_INT1;

    //
    // Enable WAKEINT in the PIE: Group 1 interrupt 4
    //
    PieCtrlRegs.PIEIER1.bit.INTx8 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    //
    // Enable global Interrupts:
    //
    EINT;   // Enable Global interrupt INTM

    //
    // Set if the Oscillators will be on or off
    //
    if(HALT_OSCON)
    {
        //
        // WD is functional in HALT
        //
        EALLOW;
        CpuSysRegs.LPMCR.bit.WDINTE = 1;
        ClkCfgRegs.CLKSRCCTL1.bit.WDHALTI = 1;
        EDIS;

        //
        // Reset WD. Uncomment this section
        // if WD wakeup is desired.
        //
//        ServiceDog();
//        // Enable the watchdog to wake the device from HALT
//        EALLOW;
//        WdRegs.WDCR.all = 0x0028;
//        EDIS;
    }
    else
    {
        //
        // WD is not functional in HALT
        //
        EALLOW;
        CpuSysRegs.LPMCR.bit.WDINTE = 0;
        ClkCfgRegs.CLKSRCCTL1.bit.WDHALTI = 0;
        EDIS;
    }

    //
    // Sync CPU1 and CPU2 before entering HALT mode
    //
    IpcSync(5);

    //
    // Ensure there are no subsequent flash accesses to wake up the pump and
    // bank. Power down the flash bank and pump
    //
    SeizeFlashPump();
    FlashOff();
    ReleaseFlashPump();

    GpioDataRegs.GPASET.bit.GPIO11 = 1;    // GPIO11 is Set high before
                                           // entering HALT
    HALT();                                // enter enter HALT mode

    //
    // Reconfigure PLL after waking from HALT
    //

    //
    // PLLSYSCLK = 20MHz(XTAL_OSC) * 20 (IMULT) * 1 (FMULT) /  2 (PLLCLK_BY_2)
    //
    InitSysPll(XTAL_OSC,IMULT_20,FMULT_0,PLLCLK_BY_2);
    ESTOP0;

    //
    // loop forever
    //
    while(1);
}

//
// local_WAKE_ISR - Wake up ISR
//
interrupt void local_WAKE_ISR(void)
{
   GpioDataRegs.GPACLEAR.bit.GPIO11 = 1; // GPIO11 is cleared upon exiting HALT
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

//
// End of file
//
