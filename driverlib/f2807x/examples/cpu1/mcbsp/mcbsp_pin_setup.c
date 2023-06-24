//#############################################################################
//
// FILE:   mcbsp_pin_setup.c
//
// TITLE:  Pin Setup for McBSP module.
//
// This file contains functions to configures pins for McBSPA and McBSPB.
//
//
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include <stdint.h>
#include "device.h"
#include "driverlib.h"

#ifdef CPU1

//
// Function Prototypes
//
void setupMcBSPAPinmux(void);
void setupMcBSPBPinmux(void);

#endif

//
// Setup McBSPA Pinmux - This function configures pins for McBSPA instance.
//
void setupMcBSPAPinmux(void)
{
    //
    // This specifies which of the possible GPIO pins will be McBSPA functional
    // pins. Comment out unwanted connections. Set qualification for selected
    // input pins to asynchronous only. This will select asynchronous (no
    // qualification) for the selected pins.
    //

    //
    // MDXA pin - GPIO20 or GPIO84
    //
    GPIO_setPinConfig(GPIO_20_MDXA);
    GPIO_setQualificationMode(20, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_84_MDXA);
    //GPIO_setQualificationMode(84, GPIO_QUAL_ASYNC);

    //
    // MDRA pin - GPIO21 or GPIO85
    //
    GPIO_setPinConfig(GPIO_21_MDRA);
    GPIO_setQualificationMode(21, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_85_MDRA);
    //GPIO_setQualificationMode(85, GPIO_QUAL_ASYNC);

    //
    // MCLKXA - GPIO22 or GPIO86
    //
    GPIO_setPinConfig(GPIO_22_MCLKXA);
    GPIO_setQualificationMode(22, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_86_MCLKXA);
    //GPIO_setQualificationMode(86, GPIO_QUAL_ASYNC);

    //
    // MCLKRA - GPIO7 or GPIO58
    //
    GPIO_setPinConfig(GPIO_7_MCLKRA);
    GPIO_setQualificationMode(7, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_58_MCLKRA);
    //GPIO_setQualificationMode(58, GPIO_QUAL_ASYNC);

    //
    // MFSXA - GPIO23 or GPIO87
    //
    GPIO_setPinConfig(GPIO_23_MFSXA);
    GPIO_setQualificationMode(23, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_87_MFSXA);
    //GPIO_setQualificationMode(87, GPIO_QUAL_ASYNC);

    //
    // MFSRA - GPIO5 or GPIO59
    //
    GPIO_setPinConfig(GPIO_5_MFSRA);
    GPIO_setQualificationMode(5, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_59_MFSRA);
    //GPIO_setQualificationMode(59, GPIO_QUAL_ASYNC);

}

//
// Setup McBSPB Pinmux - This function configures pins for McBSPB instance.
//
void setupMcBSPBPinmux(void)
{
    //
    // This specifies which of the possible GPIO pins will be McBSPB functional
    // pins. Comment out unwanted connections. Set qualification for selected
    // input pins to asynchronous only. This will select asynchronous (no
    // qualification) for the selected pins.
    //

    //
    // MDXB pin - GPIO24 or GPIO84
    //
    GPIO_setPinConfig(GPIO_24_MDXB);
    GPIO_setQualificationMode(24, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_84_MDXB);
    //GPIO_setQualificationMode(84, GPIO_QUAL_ASYNC);

    //
    // MDRB pin - GPIO13 or GPIO25 or GPIO85
    //
    //GPIO_setPinConfig(GPIO_13_MDRB);
    //GPIO_setQualificationMode(13, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_25_MDRB);
    GPIO_setQualificationMode(25, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_85_MDRA);
    //GPIO_setQualificationMode(85, GPIO_QUAL_ASYNC);

    //
    // MCLKXB - GPIO14 or GPIO26 or GPIO86
    //
    //GPIO_setPinConfig(GPIO_14_MCLKXB);
    //GPIO_setQualificationMode(14, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_26_MCLKXB);
    GPIO_setQualificationMode(26, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_86_MCLKXA);
    //GPIO_setQualificationMode(86, GPIO_QUAL_ASYNC);

    //
    // MCLKRB - GPIO3 or GPIO60
    //
    GPIO_setPinConfig(GPIO_3_MCLKRB);
    GPIO_setQualificationMode(3, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_60_MCLKRB);
    //GPIO_setQualificationMode(60, GPIO_QUAL_ASYNC);

    //
    // MFSXB - GPIO15 or GPIO27 or GPIO87
    //
    //GPIO_setPinConfig(GPIO_15_MFSXB);
    //GPIO_setQualificationMode(15, GPIO_QUAL_ASYNC);
    GPIO_setPinConfig(GPIO_27_MFSXB);
    GPIO_setQualificationMode(27, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_87_MFSXA);
    //GPIO_setQualificationMode(87, GPIO_QUAL_ASYNC);

    //
    // MFSRB - GPIO1 or GPIO61
    //
    GPIO_setPinConfig(GPIO_1_MFSRB);
    GPIO_setQualificationMode(1, GPIO_QUAL_ASYNC);
    //GPIO_setPinConfig(GPIO_61_MFSRB);
    //GPIO_setQualificationMode(61, GPIO_QUAL_ASYNC);
}

//
// End of File
//
