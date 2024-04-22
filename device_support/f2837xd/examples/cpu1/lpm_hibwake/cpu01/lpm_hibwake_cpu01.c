//###########################################################################
//
// FILE:   lpm_hibwake_cpu01.c
//
// TITLE:  HIB entry and Exit Example for F2837xD.
//
//! \addtogroup cpu01_example_list
//!  <h1>Low Power Modes: HIB Mode and Wakeup (lpm_hibwake)</h1>
//!
//!  This example puts the device into HIB mode. This is the lowest
//!  possible power configuration of the device. To realize the
//!  lowest possible current consumption in HIB mode, The JTAG connector
//!  should be removed from the device board while the device is in HIB mode.
//!
//!  This example will configure the IoRestore Address, Memory Retention,
//!  and then enter HIB mode. After wake-up, the example will reconfigure
//!  the GPIOs, disable IO isolation and then re-enter main.
//!
//!  GPIOHIBWAKEn(GPIO41) wakes the device from HIB mode when
//!  a high->low->high signal is detected on the pin. This pin must be
//!  pulsed by an external agent for wakeup.
//!
//!  GPIO10 and GPIO11 are configured as outputs for status indicators
//!  to the outside world. Connect GPIO10 to an external agent to notify
//!  that the device has entered HIB mode. View both GPIO10 and GPIO11
//!  on an oscilloscope to view the device status. \n
//!  GPIO10 = 1, GPIO11 = 1: Device is in HIB mode \n
//!  GPIO10 = 1, GPIO11 = 0: Code execution is in IoRestore, IO isolation
//!                          has been disabled \n
//!  GPIO10 = 0, GPIO11 = 0: Code execution is in main. \n
//!
//!  The wakeup process begins after GPIOHIBWAKEn is held low for the
//!  time indicated in the device datasheet and then brought high again
//!  After the device wakes up, GPIO11 can be observed to go low in
//!  IoRestore and GPIO10 will go low when the program has re-entered main.
//!
//!  If M0M1 memory retention is not desired, set RETAINM0M1 to 0.
//!
//
//###########################################################################
//
// 
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
#define RANDOM_SEED    0x000034A9L
#define FAIL_LOG       ((Uint32 *)0xC000)
#define HIBWAKE        0x00001000L
#define STARTUP        0x0000B000L
#define C1BROM_STS     ((volatile Uint32 *)0x0000002C)

//
// Select if M0/M1 retention will be used.
//
//#define RETAINM0M1        1        // Retain M0M1 across HIB
#define RETAINM0M1         0        // Do not retain M0M1

//
// Globals
//
#if RETAINM0M1
// Define some data sections to fill to be retained.
// Because new sections must be aligned, two sections are created.
#pragma DATA_SECTION(M01DAT, "m0m1");
Uint16 M01DAT[0x6C0];
#pragma DATA_SECTION(hibstate, "hibstate");
Uint16 hibstate[0x1C];
#endif

//
// Function Prototypes
//
void IoRestore();
void GpioCfg();
void FillMem();
void ClearMem();
Uint16 VerifyMem();
void error() {ESTOP0;}

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

    //
    // If this is is not a HIB wake up, configure the GPIOs
    //
    if((*C1BROM_STS & HIBWAKE) != HIBWAKE)
    {
        //
        // Step 2. Initialize and configure GPIOs
        //
        GpioCfg();
    }
    else // This is a HIB wake.
    {
        //
        // Check HIBBOOTMODE for the value set in IoRestore
        //
        if((CpuSysRegs.HIBBOOTMODE & 0xFFFF0000) == 0x11110000)
        {
            //
            // Clear the second monitor pin to notify that the
            // example has completed executing
            //
            GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;

            //
            // End the test.
            //
            ESTOP0;

            //
            // loop forever
            //
            while(1);
        }
        else
        {
            //
            // The HIBBOOTMODE value was not what was set
            // inside of IoRestore()
            //
            error();
        }
    }

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
    // Step 4. Initialize all the Device Peripherals:
    //
    // None used in this example.

    //
    // Step 5. User specific code:
    //

    //
    // Use the upper 16 bits of HIBBOOTMODE as a custom flag that
    // IoRestore will check to verify that HIB was entered from main
    //
    EALLOW;
    CpuSysRegs.HIBBOOTMODE = 0xABCD0000;
    EDIS;

    //
    // Configure M0M1 memory Retention.
    //
#if RETAINM0M1
    EALLOW;
    CpuSysRegs.LPMCR.bit.M0M1MODE = 1;        // M0M1 Retention
    EDIS;

    //
    // Clear the memories and then fill them with known values.
    //
    ClearMem();
    FillMem();
#else
    EALLOW;
    CpuSysRegs.LPMCR.bit.M0M1MODE = 0;        // No M0M1 Retention
    EDIS;
#endif

    //
    // Provide IORESTOREADDR with IoRestore location
    //
    EALLOW;
    CpuSysRegs.IORESTOREADDR.all = (Uint32)&IoRestore;
    EDIS;

    //
    // Ensure there are no subsequent flash accesses to wake up the pump and
    // bank Power down the flash bank and pump
    //
    SeizeFlashPump();
    FlashOff();
    ReleaseFlashPump();

    //
    // Set GPIO10 and GPIO11 high just before entering HIB.
    // - View these on an oscilloscope.
    //
    GpioDataRegs.GPASET.bit.GPIO10 = 1;
    GpioDataRegs.GPASET.bit.GPIO11 = 1;

    //
    // Enter HIB
    //
    HIB();

    //
    // Loop forever. Code should never reach here.
    //
    while(1);
}

//
// GpioCfg - Setup the GPIOs used in this example
//
void GpioCfg()
{
    //
    // This example function is found in the F2837xD_Gpio.c file and
    // illustrates how to set the GPIO to it's default state.
    //
    InitGpio();

    //
    //Set up GPIOHIBWAKEn
    //
    GPIO_SetupPinMux(41, GPIO_MUX_CPU1, 0x00);
    GPIO_SetupPinOptions(41, GPIO_INPUT, GPIO_PULLUP | GPIO_ASYNC);

    //
    // Monitor pin 1 for IoRestore execution
    //
    GPIO_SetupPinMux(10, GPIO_MUX_CPU1, 0x00);
    GPIO_SetupPinOptions(10, GPIO_OUTPUT, 0x0);

    //
    // Monitor pin 2 for complete HIB wake
    //
    GPIO_SetupPinMux(11, GPIO_MUX_CPU1, 0x00);
    GPIO_SetupPinOptions(11, GPIO_OUTPUT, 0x0);
}

//
// IoRestore - This function can restore the GPIOs to their previous state,
//             Test the RAM integrity to verify that nothing was overwritten
//             when entering or exiting HIB. This function will complete
//             and then return to BOOTROM to execute BOOT to FLASH
//             continuing on to re-enter main.
//
void IoRestore()
{
    volatile int fail = 0;

    //
    // Configure Gpios for when we disable IO isolation
    // In a real application, the user would save the IO status in M0M1,
    // using this data to reconfig IOs to their pre-hib state.
    // Since this is just an example, the GPIO's will be reconfigured
    // the same way as after POR.
    //
    GpioCfg();

    //
    // Infinite loop to allow the debugger to connect after reaching IoRestore
    // Be sure to use a Target config without a GEL File
    // Uncomment this line if IORestore Debug is required.
    //
//    while(1);

    //
    //The integrity of IORESTOREADDR and HIBBOOTMODE are implicitly tested by
    //using them as status indicators across wake-ups.
    //
    if ((*C1BROM_STS & HIBWAKE) == HIBWAKE)
    {
        if((CpuSysRegs.HIBBOOTMODE & 0xFFFF0000) == 0xABCD0000)
        {
            //
            // Set up HIBBOOTMODE with Boot to Flash + key
            // use custom flag in upper 16 bits. Main will read
            // this value and then end the example.
            //
            EALLOW;
            CpuSysRegs.HIBBOOTMODE = 0x11110B5A;
            EDIS;
        }
        else
        {
            //
            // There was an error: HIBBOOTMODE is not what was expected.
            //
            error();
        }

        //
        // Restore the state of GPIO10 to pre-HIB value.
        //
        GpioDataRegs.GPASET.bit.GPIO10 = 1;

        //
        // Clear GPIO11 to 0. This will be seen when IO isolation is disabled.
        //
        GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;

        //
        // Disable IO isolation to propagate the GPIO change
        // This is automatically done in BootROM immediately after
        // IoRestore completes. This shows that there is no glitch
        // on GPIO10 (will be HIGH),
        //
        EALLOW;
        CpuSysRegs.LPMCR.bit.IOISODIS = 1;
        EDIS;

#if RETAINM0M1
        //
        // Verify the RAM integrity
        //
        fail = VerifyMem();

        if(!fail)
        {
            //
            // If the RAM is intact, we are done. Execution will return
            // from IoRestore, and continue boot ROM, then to main.
            //
            return;
        }
        else
        {
            //
            // There was an error: Failed RAM integrity check
            //
            while(1)
            {
                error();
            }
        }
#endif
    }
    else
    {
        //
        // There was an error: Failed C1BROM_STS check
        //
        while(1)
        {
            error();
        }
    }
}

#if RETAINM0M1
//
// FillMem - Fill both memory sections with pseudo-random data
//
void FillMem()
{
    Uint32 temp, seed, c;

    //
    //Use a pseudo number generator to fill the hibstate
    //with irregular data.
    //
    temp = seed = RANDOM_SEED;
    for(c = 0; c < sizeof(hibstate); c++)
    {
        hibstate[c] = (Uint16)temp;
        temp *= seed;
        temp = ((temp >> 16) + temp) & 0xFFFF;
    }

    //
    //Use a pseudo number generator to fill the M01DAT
    //with irregular data.
    //
    temp = seed = RANDOM_SEED;
    for(c = 0; c < sizeof(M01DAT); c++)
    {
        M01DAT[c] = (Uint16)temp;
        temp *= seed;
        temp = ((temp >> 16) + temp) & 0xFFFF;
    }
}

//
// ClearMem - Clear the memory to a known state
//
void ClearMem()
{
    Uint32 c;
    for(c = 0; c < sizeof(hibstate); c++)
    {
        hibstate[c] = 0;
    }

    for(c = 0; c < sizeof(M01DAT); c++)
    {
        M01DAT[c] = 0;
    }
}

//
// VerifyMem - Verify that the saved M0 and M1 RAM data is intact
//
Uint16 VerifyMem()
{
    Uint32 temp, seed;
    Uint16 c;

    //
    //Check hibstate against the expected values. Fail if
    //data is corrupted
    //
    temp = seed = RANDOM_SEED;
    for (c = 0; c < sizeof(hibstate); c++)
    {
        if(hibstate[c] != (Uint16)temp)
        {
            FAIL_LOG[0] = c;
            FAIL_LOG[1] = hibstate[c];
            FAIL_LOG[2] = (Uint16)temp;
            return 0x2;
        }

        hibstate[c] = (Uint16)temp;
        temp *= seed;
        temp = ((temp >> 16) + temp) & 0xFFFF;
    }

    //
    //Check M01DAT against the expected values. Fail if
    //data is corrupted
    //
    temp = seed = RANDOM_SEED;
    for (c = 0; c < sizeof(M01DAT); c++)
    {
        if(M01DAT[c] != (Uint16)temp)
        {
            FAIL_LOG[0] = c;
            FAIL_LOG[1] = M01DAT[c];
            FAIL_LOG[2] = (Uint16)temp;
            return 0x2;
        }
        M01DAT[c] = (Uint16)temp;
        temp *= seed;
        temp = ((temp >> 16) + temp) & 0xFFFF;
    }

    //
    //All data is intact, so return a pass
    //
    return 0x0;
}
#endif

//
// End of file
//
