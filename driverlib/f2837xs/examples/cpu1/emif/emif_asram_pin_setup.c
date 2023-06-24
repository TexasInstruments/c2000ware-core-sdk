//#############################################################################
//
// FILE:   emif_asram_pin_setup.c
//
// TITLE:  Pin setup for EMIF module accessing ASRAM.
//
// This example configures pins for EMIF in ASYNC mode.
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
void setupEMIF1PinmuxAsync16Bit(void);
void setupEMIF1PinmuxAsync32Bit(void);
void setupEMIF2PinmuxAsync16Bit(void);

#endif

//
// Setup EMIF1 Pinmux Async 16Bit - This function configures pins for 16 bit
// Asynchronous EMIF1.
//
void setupEMIF1PinmuxAsync16Bit(void)
{
    uint16_t i;

    GPIO_setPinConfig(GPIO_28_EM1CS4N);
    GPIO_setPinConfig(GPIO_29_EM1SDCKE);
    GPIO_setPinConfig(GPIO_30_EM1CLK);
    GPIO_setPinConfig(GPIO_31_EM1WEN);
    GPIO_setPinConfig(GPIO_32_EM1CS0N);
    GPIO_setPinConfig(GPIO_33_EM1RNW);
    GPIO_setPinConfig(GPIO_34_EM1CS2N);
    GPIO_setPinConfig(GPIO_35_EM1CS3N);
    GPIO_setPinConfig(GPIO_36_EM1WAIT);
    GPIO_setPinConfig(GPIO_37_EM1OEN);

    //
    // Selecting address lines.
    //
    GPIO_setPinConfig(GPIO_38_EM1A0);
    GPIO_setPinConfig(GPIO_39_EM1A1);
    GPIO_setPinConfig(GPIO_40_EM1A2);
    GPIO_setPinConfig(GPIO_41_EM1A3);
    GPIO_setPinConfig(GPIO_44_EM1A4);
    GPIO_setPinConfig(GPIO_45_EM1A5);
    GPIO_setPinConfig(GPIO_46_EM1A6);
    GPIO_setPinConfig(GPIO_47_EM1A7);
    GPIO_setPinConfig(GPIO_48_EM1A8);
    GPIO_setPinConfig(GPIO_49_EM1A9);
    GPIO_setPinConfig(GPIO_50_EM1A10);
    GPIO_setPinConfig(GPIO_51_EM1A11);
    GPIO_setPinConfig(GPIO_52_EM1A12);
    GPIO_setPinConfig(GPIO_86_EM1A13);
    GPIO_setPinConfig(GPIO_87_EM1A14);

    //
    // Selecting data lines.
    //
    GPIO_setPinConfig(GPIO_63_EM1D21);
    GPIO_setPinConfig(GPIO_64_EM1D20);
    GPIO_setPinConfig(GPIO_65_EM1D19);
    GPIO_setPinConfig(GPIO_66_EM1D18);
    GPIO_setPinConfig(GPIO_67_EM1D17);
    GPIO_setPinConfig(GPIO_68_EM1D16);
    GPIO_setPinConfig(GPIO_69_EM1D15);
    GPIO_setPinConfig(GPIO_70_EM1D14);
    GPIO_setPinConfig(GPIO_71_EM1D13);
    GPIO_setPinConfig(GPIO_72_EM1D12);
    GPIO_setPinConfig(GPIO_73_EM1D11);
    GPIO_setPinConfig(GPIO_74_EM1D10);
    GPIO_setPinConfig(GPIO_75_EM1D9);
    GPIO_setPinConfig(GPIO_76_EM1D8);
    GPIO_setPinConfig(GPIO_77_EM1D7);
    GPIO_setPinConfig(GPIO_78_EM1D6);
    GPIO_setPinConfig(GPIO_79_EM1D5);
    GPIO_setPinConfig(GPIO_80_EM1D4);
    GPIO_setPinConfig(GPIO_81_EM1D3);
    GPIO_setPinConfig(GPIO_82_EM1D2);
    GPIO_setPinConfig(GPIO_83_EM1D1);
    GPIO_setPinConfig(GPIO_85_EM1D0);

    //
    // Setting DQM and Bank Select lines.
    //
    GPIO_setPinConfig(GPIO_88_EM1DQM0);
    GPIO_setPinConfig(GPIO_89_EM1DQM1);
    GPIO_setPinConfig(GPIO_90_EM1DQM2);
    GPIO_setPinConfig(GPIO_91_EM1DQM3);
    GPIO_setPinConfig(GPIO_92_EM1BA1);
    GPIO_setPinConfig(GPIO_93_EM1BA0);
    GPIO_setPinConfig(GPIO_94_EM1A21);

    //
    // Setup async mode and enable pull-ups for Data pins.
    //
    for(i=69; i<=85;i++)
    {
        if(i != 84)
        {
            GPIO_setPadConfig(i, GPIO_PIN_TYPE_PULLUP);
            GPIO_setQualificationMode(i, GPIO_QUAL_ASYNC);
        }
    }
 }

//
// Setup EMIF1 Pinmux Async 32Bit - This function configures pins for 32 bit
// Asynchronous EMIF1.
//
void setupEMIF1PinmuxAsync32Bit(void)
{
    uint16_t i;

    GPIO_setPinConfig(GPIO_28_EM1CS4N);
    GPIO_setPinConfig(GPIO_29_EM1SDCKE);
    GPIO_setPinConfig(GPIO_30_EM1CLK);
    GPIO_setPinConfig(GPIO_31_EM1WEN);
    GPIO_setPinConfig(GPIO_32_EM1CS0N);
    GPIO_setPinConfig(GPIO_33_EM1RNW);
    GPIO_setPinConfig(GPIO_34_EM1CS2N);
    GPIO_setPinConfig(GPIO_35_EM1CS3N);
    GPIO_setPinConfig(GPIO_36_EM1WAIT);
    GPIO_setPinConfig(GPIO_37_EM1OEN);

    //
    // Selecting address lines.
    //
    GPIO_setPinConfig(GPIO_38_EM1A0);
    GPIO_setPinConfig(GPIO_39_EM1A1);
    GPIO_setPinConfig(GPIO_40_EM1A2);
    GPIO_setPinConfig(GPIO_41_EM1A3);
    GPIO_setPinConfig(GPIO_44_EM1A4);
    GPIO_setPinConfig(GPIO_45_EM1A5);
    GPIO_setPinConfig(GPIO_46_EM1A6);
    GPIO_setPinConfig(GPIO_47_EM1A7);
    GPIO_setPinConfig(GPIO_48_EM1A8);
    GPIO_setPinConfig(GPIO_49_EM1A9);
    GPIO_setPinConfig(GPIO_50_EM1A10);
    GPIO_setPinConfig(GPIO_51_EM1A11);
    GPIO_setPinConfig(GPIO_52_EM1A12);
    GPIO_setPinConfig(GPIO_86_EM1A13);
    GPIO_setPinConfig(GPIO_87_EM1A14);

    //
    // Selecting data lines.
    //
    GPIO_setPinConfig(GPIO_53_EM1D31);
    GPIO_setPinConfig(GPIO_54_EM1D30);
    GPIO_setPinConfig(GPIO_55_EM1D29);
    GPIO_setPinConfig(GPIO_56_EM1D28);
    GPIO_setPinConfig(GPIO_57_EM1D27);
    GPIO_setPinConfig(GPIO_58_EM1D26);
    GPIO_setPinConfig(GPIO_59_EM1D25);
    GPIO_setPinConfig(GPIO_60_EM1D24);
    GPIO_setPinConfig(GPIO_61_EM1D23);
    GPIO_setPinConfig(GPIO_62_EM1D22);
    GPIO_setPinConfig(GPIO_63_EM1D21);
    GPIO_setPinConfig(GPIO_64_EM1D20);
    GPIO_setPinConfig(GPIO_65_EM1D19);
    GPIO_setPinConfig(GPIO_66_EM1D18);
    GPIO_setPinConfig(GPIO_67_EM1D17);
    GPIO_setPinConfig(GPIO_68_EM1D16);
    GPIO_setPinConfig(GPIO_69_EM1D15);
    GPIO_setPinConfig(GPIO_70_EM1D14);
    GPIO_setPinConfig(GPIO_71_EM1D13);
    GPIO_setPinConfig(GPIO_72_EM1D12);
    GPIO_setPinConfig(GPIO_73_EM1D11);
    GPIO_setPinConfig(GPIO_74_EM1D10);
    GPIO_setPinConfig(GPIO_75_EM1D9);
    GPIO_setPinConfig(GPIO_76_EM1D8);
    GPIO_setPinConfig(GPIO_77_EM1D7);
    GPIO_setPinConfig(GPIO_78_EM1D6);
    GPIO_setPinConfig(GPIO_79_EM1D5);
    GPIO_setPinConfig(GPIO_80_EM1D4);
    GPIO_setPinConfig(GPIO_81_EM1D3);
    GPIO_setPinConfig(GPIO_82_EM1D2);
    GPIO_setPinConfig(GPIO_83_EM1D1);
    GPIO_setPinConfig(GPIO_85_EM1D0);

    //
    // Setting DQM and Bank Select lines.
    //
    GPIO_setPinConfig(GPIO_88_EM1DQM0);
    GPIO_setPinConfig(GPIO_89_EM1DQM1);
    GPIO_setPinConfig(GPIO_90_EM1DQM2);
    GPIO_setPinConfig(GPIO_91_EM1DQM3);
    GPIO_setPinConfig(GPIO_92_EM1BA1);
    GPIO_setPinConfig(GPIO_93_EM1BA0);
    GPIO_setPinConfig(GPIO_94_EM1A21);

    //
    // Setup Async Mode for Data pins.
    //
    for(i=53; i<=85;i++)
    {
        if(i != 84)
        {
            GPIO_setPadConfig(i, GPIO_PIN_TYPE_PULLUP);
            GPIO_setQualificationMode(i, GPIO_QUAL_ASYNC);
        }
    }
}

//
// Setup EMIF2 Pinmux Async 16Bit - This function configures pins for 16 bit
// Asynchronous EMIF2.
//
void setupEMIF2PinmuxAsync16Bit(void)
{
    uint16_t i;

    GPIO_setPinConfig(GPIO_96_EM2DQM1);
    GPIO_setPinConfig(GPIO_97_EM2DQM0);
    GPIO_setPinConfig(GPIO_98_EM2A0);
    GPIO_setPinConfig(GPIO_99_EM2A1);
    GPIO_setPinConfig(GPIO_100_EM2A2);
    GPIO_setPinConfig(GPIO_101_EM2A3);
    GPIO_setPinConfig(GPIO_102_EM2A4);
    GPIO_setPinConfig(GPIO_103_EM2A5);
    GPIO_setPinConfig(GPIO_104_EM2A6);
    GPIO_setPinConfig(GPIO_105_EM2A7);
    GPIO_setPinConfig(GPIO_106_EM2A8);
    GPIO_setPinConfig(GPIO_107_EM2A9);
    GPIO_setPinConfig(GPIO_108_EM2A10);
    GPIO_setPinConfig(GPIO_109_EM2A11);
    GPIO_setPinConfig(GPIO_110_EM2WAIT);
    GPIO_setPinConfig(GPIO_111_EM2BA0);
    GPIO_setPinConfig(GPIO_112_EM2BA1);
    GPIO_setPinConfig(GPIO_113_EM2CAS);
    GPIO_setPinConfig(GPIO_114_EM2RAS);
    GPIO_setPinConfig(GPIO_115_EM2CS0N);
    GPIO_setPinConfig(GPIO_116_EM2CS2N);
    GPIO_setPinConfig(GPIO_117_EM2SDCKE);
    GPIO_setPinConfig(GPIO_118_EM2CLK);
    GPIO_setPinConfig(GPIO_119_EM2RNW);
    GPIO_setPinConfig(GPIO_120_EM2WEN);
    GPIO_setPinConfig(GPIO_121_EM2OEN);

    //
    // Selecting Data lines.
    //
    GPIO_setPinConfig(GPIO_53_EM2D15);
    GPIO_setPinConfig(GPIO_54_EM2D14);
    GPIO_setPinConfig(GPIO_55_EM2D13);
    GPIO_setPinConfig(GPIO_56_EM2D12);
    GPIO_setPinConfig(GPIO_57_EM2D11);
    GPIO_setPinConfig(GPIO_58_EM2D10);
    GPIO_setPinConfig(GPIO_59_EM2D9);
    GPIO_setPinConfig(GPIO_60_EM2D8);
    GPIO_setPinConfig(GPIO_61_EM2D7);
    GPIO_setPinConfig(GPIO_62_EM2D6);
    GPIO_setPinConfig(GPIO_63_EM2D5);
    GPIO_setPinConfig(GPIO_64_EM2D4);
    GPIO_setPinConfig(GPIO_65_EM2D3);
    GPIO_setPinConfig(GPIO_66_EM2D2);
    GPIO_setPinConfig(GPIO_67_EM2D1);
    GPIO_setPinConfig(GPIO_68_EM2D0);

    //
    // Setup async mode for Data pins.
    //
    for(i=53; i<=68;i++)
    {
        GPIO_setPadConfig(i, GPIO_PIN_TYPE_PULLUP);
        GPIO_setQualificationMode(i, GPIO_QUAL_ASYNC);
    }
}

//
// End of File
//
