//#############################################################################
//
// FILE:   boot_ex2_customBootConfig.c
//
// TITLE:  Customized Boot Configuration Example
//
//! \addtogroup driver_example_list
//! <h1> Customized Boot Configuration Example </h1>
//!
//! The example implements a custom boot configuration according
//! to the CCS build configuration selected: 0 boot mode select pins
//! (ZERO_BMSPS), 1 boot mode select pin (ONE_BMSP), or 3 boot mode
//! select pins (THREE_BMSPS).
//!
//!
//! Select the build configuration and run the
//! program. To test a specific boot mode: pause the program, apply
//! appropriate voltages to BMSPs as necessary, perform a reset through
//! Scripts -> Realtime Emulation Control -> Run_Realtime_with_Reset.
//! If more than one specific boot mode is to be tested, reset the debugger
//! and run the program before following the steps above; this ensures that
//! the device is not executing 'non-debuggable' code from the previous boot mode
//! and the emulation-equivalent Boot ROM registers contain the appropriate
//! values. Do not power-cycle the device in order to perform a reset; values in the
//! emulation-equivalent Boot ROM registers may change if the device is power-cycled.
//!
//!
//! By default, the example will configure the boot mode
//! select pins and boot mode options for the emulation boot process to
//! be executed.
//!
//! The following constants can be changed in the header:
//!
//! - STANDALONE_BOOT - Determines if the standalone boot or emulation
//!                     boot process is to be emulated when the device is reset
//!                     (while the emulator is connected). WARNING: the
//!                     standalone boot process requires the user-configurable
//!                     DCSM OTP (one-time programmable) registers to be programmed.
//!                     Please ensure the DCSM OTP registers are programmed before
//!                     choosing to emulate the standalone boot process. OTP registers can
//!                     only be programmed once and cannot be erased.
//!
//! - BOOTPIN_CONFIG_BMSP2 - Boot mode select pin 2, default is GPIO2
//! - BOOTPIN_CONFIG_BMSP1 - Boot mode select pin 1, default is GPIO1
//! - BOOTPIN_CONFIG_BMSP0 - Boot mode select pin 0, default is GPIO0
//!
//!  The BOOTDEF options can also be changed as necessary. Default
//!  options for the example are in accordance with the build
//!  configurations described below.
//!
//!   ZERO_BMSPS:   Boot Mode Number BMSP2 BMSP1 BMSP0  Boot Mode
//!                      0            N/A   N/A   N/A   Flash Boot
//!
//!   ONE_BMSP:          0            N/A   N/A   0     Flash Boot
//!                      1            N/A   N/A   1     SCI Boot
//!
//!   THREE_BMSPS        0            0      0    0     Flash Boot
//!                      1            0      0    1     SCI Boot
//!                      2            0      1    0     Flash Boot Alt.1
//!                      3            0      1    1     SCI Boot Alt.1
//!                      4            1      0    0     CAN Boot
//!                      5            1      0    1     SPI Boot
//!                      6            1      1    0     RAM Boot
//!                      7            1      1    1     I2C Boot
//!
//!
//!  Watch the addresses below in the memory browser when running the
//!  emulation boot configuration:
//! - 0xD00 and 0xD01 for EMU BOOTPIN CONFIG
//! - 0xD04 and 0xD05 for EMU BOOTDEF LOW
//! - 0xD06 and 0xD07 for EMU BOOTDEF HIGH
//!
//!  Watch the address below in the memory browser when STANDALONE_BOOT
//!  constant is set to a non-zero value:
//! - 0xD00 for EMU BOOTPIN CONFIG
//!
//! \b External \b Connections \n
//!  - Connect 3V or GND to BMSP2 as appropriate
//!  - Connect 3V or GND to BMSP1 as appropriate
//!  - Connect 3V or GND to BMSP0 as appropriate
//!
//! \b Watch \b Variables \n
//!  - None
//!
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "driverlib.h"
#include "device.h"
#include "boot_ex2_customBootConfig.h"

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    #if STANDALONE_BOOT

        //
        // Enable writing to the EALLOW protected registers
        //
        EALLOW;

        //
        // Write a value of 0xA5 to the emulation equivalent
        // of Z1_OTP_BOOTPIN_CONFIG in order to emulate
        // the standalone boot flow
        //
        HWREG(EMU_BOOTPIN_CONFIG) = (EMU_STANDALONE_KEYVAL  << 24);

        //
        // Disable writing to the EALLOW protected registers
        //
        EDIS;

    #else

        //
        // If the ZERO_BMSPS build configuration is selected, set up a custom
        // boot table that uses 0 BMSPs
        //
        #ifdef ZERO_BMSPS

            configBMSPS0();

        #endif

        //
        // If the ONE_BMSP build configuration is selected, set up a custom
        // boot table that uses 1 BMSP
        //
        #ifdef ONE_BMSP

            configBMSPS1();

        #endif

        //
        // If the THREE_BMSPS build configuration is selected, set up a custom
        // boot table that uses 3 BMSPs
        //
        #ifdef THREE_BMSPS

            configBMSPS3();

        #endif

    #endif

    //
    // Loop Forever
    //
    for(;;)
    {
        //
        // Do nothing. NOP == No Operation
        //
        asm("    NOP");
    }
}

//
// Functions
//

//
// configBMSPS0 - Configures a custom boot EMU configuration when zero boot mode
//                select pins are being used
//
//                Boot Mode Number                          Boot Mode
//                      0                                   Flash Boot
//
void configBMSPS0(void)
{
    //
    // Enable writing to the EALLOW protected registers
    //
    EALLOW;

    //
    // Write a value of 0x5A to the Key field of
    // EMU_BOOTPIN_CONFIG in order to execute
    // a custom boot process. Write the values of
    // BMSPs to be used.
    //
    HWREG(EMU_BOOTPIN_CONFIG) = (BOOTPIN_CONFIG_KEY  << 24) + 
                                (BOOTPIN_CONFIG_BMSPDISABLE << 16) + 
                                (BOOTPIN_CONFIG_BMSPDISABLE << 8) + 
                                (BOOTPIN_CONFIG_BMSPDISABLE);

    //
    // Write boot mode option 0 to the EMU_BOOTDEF_LOW register
    //
    HWREG(EMU_BOOTDEF_LOW) = BOOTDEF_LOW_0;

    //
    // Disable writing to the EALLOW protected registers
    //
    EDIS;
}

//
// configBMSPS1 - Configures a custom EMU boot configuration when 1 boot mode
//                select pin is being used.
//
//                Boot Mode Number     BMSP0          Boot Mode
//                      0                0            Flash Boot
//                      1                1            SCI Boot
//
void configBMSPS1(void)
{
    //
    // Enable writing to the EALLOW protected registers
    //
    EALLOW;

    //
    // Write a value of 0x5A to the Key field of
    // EMU_BOOTPIN_CONFIG in order to execute
    // a custom boot process. Write the values of
    // BMSPs to be used.
    //
    HWREG(EMU_BOOTPIN_CONFIG) = (BOOTPIN_CONFIG_KEY  << 24) + 
                                (BOOTPIN_CONFIG_BMSPDISABLE << 16) + 
                                (BOOTPIN_CONFIG_BMSPDISABLE << 8) + 
                                (BOOTPIN_CONFIG_BMSP0);

    //
    // Write boot mode options 1 and 0 to the EMU_BOOTDEF_LOW register
    //
    HWREG(EMU_BOOTDEF_LOW) = (BOOTDEF_LOW_1 << 8) + BOOTDEF_LOW_0;

    //
    // Disable writing to the EALLOW protected registers
    //
    EDIS;
}

//
// configBMSPS3 - Configures a custom EMU boot configuration when 3 boot
//                mode select pins are used.
//
//                Boot Mode Number  BMSP2  BMSP1  BMSP0    Boot Mode
//                     0              0      0      0      Flash Boot
//                     1              0      0      1      SCI Boot
//                     2              0      1      0      Flash Boot Alt.1
//                     3              0      1      1      SCI Boot Alt.1
//                     4              1      0      0      CAN Boot
//                     5              1      0      1      SPI Boot
//                     6              1      1      0      RAM Boot
//                     7              1      1      1      I2C Boot
//
void configBMSPS3(void)
{
    //
    // Enable writing to the EALLOW protected registers
    //
    EALLOW;

    //
    // Write a value of 0x5A to the Key field of
    // EMU_BOOTPIN_CONFIG in order to execute
    // a custom boot process. Write the values of
    // BMSPs to be used.
    //
    HWREG(EMU_BOOTPIN_CONFIG) = (BOOTPIN_CONFIG_KEY  << 24) +
                                (BOOTPIN_CONFIG_BMSP2 << 16) + 
                                (BOOTPIN_CONFIG_BMSP1 << 8) + 
                                (BOOTPIN_CONFIG_BMSP0);

    //
    // Write boot mode options 3, 2, 1, and 0 to the EMU_BOOTDEF_LOW register
    //
    HWREG(EMU_BOOTDEF_LOW) = (BOOTDEF_LOW_3 << 24) + (BOOTDEF_LOW_2 << 16) + 
                             (BOOTDEF_LOW_1 << 8) + BOOTDEF_LOW_0;

    //
    // Write boot mode options 7, 6, 5, and 4 to the EMU_BOOTDEF_HIGH register
    //
    HWREG(EMU_BOOTDEF_HIGH) = (BOOTDEF_HIGH_7 << 24) + (BOOTDEF_HIGH_6 << 16)
                              + (BOOTDEF_HIGH_5 << 8) + BOOTDEF_HIGH_4;

    //
    // Disable writing to the EALLOW protected registers
    //
    EDIS;
}

// 
// End of File 
//
