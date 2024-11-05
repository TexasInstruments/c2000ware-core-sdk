//#############################################################################
//
// FILE:   emif_asram_pin_setup.c
//
//! \addtogroup driver_example_list
//! <h1> Pin setup for EMIF module accessing ASRAM. </h1>
//!
//! This example configures pins for EMIF in ASYNC mode.
//!
//!
//#############################################################################
//
//
// 
// C2000Ware v5.04.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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

    GPIO_setPinConfig(GPIO_28_EMIF1_CS4N);
    GPIO_setPinConfig(GPIO_29_EMIF1_SDCKE);
    GPIO_setPinConfig(GPIO_30_EMIF1_CLK);
    GPIO_setPinConfig(GPIO_31_EMIF1_WEN);
    GPIO_setPinConfig(GPIO_32_EMIF1_CS0N);
    GPIO_setPinConfig(GPIO_33_EMIF1_RNW);
    GPIO_setPinConfig(GPIO_34_EMIF1_CS2N);
    GPIO_setPinConfig(GPIO_35_EMIF1_CS3N);
    GPIO_setPinConfig(GPIO_36_EMIF1_WAIT);
    GPIO_setPinConfig(GPIO_37_EMIF1_OEN);

    //
    // Selecting address lines.
    //
    GPIO_setPinConfig(GPIO_38_EMIF1_A0);
    GPIO_setPinConfig(GPIO_39_EMIF1_A1);
    GPIO_setPinConfig(GPIO_40_EMIF1_A2);
    GPIO_setPinConfig(GPIO_41_EMIF1_A3);
    GPIO_setPinConfig(GPIO_44_EMIF1_A4);
    GPIO_setPinConfig(GPIO_45_EMIF1_A5);
    GPIO_setPinConfig(GPIO_46_EMIF1_A6);
    GPIO_setPinConfig(GPIO_47_EMIF1_A7);
    GPIO_setPinConfig(GPIO_48_EMIF1_A8);
    GPIO_setPinConfig(GPIO_49_EMIF1_A9);
    GPIO_setPinConfig(GPIO_50_EMIF1_A10);
    GPIO_setPinConfig(GPIO_51_EMIF1_A11);
    GPIO_setPinConfig(GPIO_52_EMIF1_A12);
    GPIO_setPinConfig(GPIO_86_EMIF1_A13);
    GPIO_setPinConfig(GPIO_87_EMIF1_A14);

    //
    // Selecting data lines.
    //
    GPIO_setPinConfig(GPIO_63_EMIF1_D21);
    GPIO_setPinConfig(GPIO_64_EMIF1_D20);
    GPIO_setPinConfig(GPIO_65_EMIF1_D19);
    GPIO_setPinConfig(GPIO_66_EMIF1_D18);
    GPIO_setPinConfig(GPIO_67_EMIF1_D17);
    GPIO_setPinConfig(GPIO_68_EMIF1_D16);
    GPIO_setPinConfig(GPIO_69_EMIF1_D15);
    GPIO_setPinConfig(GPIO_70_EMIF1_D14);
    GPIO_setPinConfig(GPIO_71_EMIF1_D13);
    GPIO_setPinConfig(GPIO_72_EMIF1_D12);
    GPIO_setPinConfig(GPIO_73_EMIF1_D11);
    GPIO_setPinConfig(GPIO_74_EMIF1_D10);
    GPIO_setPinConfig(GPIO_75_EMIF1_D9);
    GPIO_setPinConfig(GPIO_76_EMIF1_D8);
    GPIO_setPinConfig(GPIO_77_EMIF1_D7);
    GPIO_setPinConfig(GPIO_78_EMIF1_D6);
    GPIO_setPinConfig(GPIO_79_EMIF1_D5);
    GPIO_setPinConfig(GPIO_80_EMIF1_D4);
    GPIO_setPinConfig(GPIO_81_EMIF1_D3);
    GPIO_setPinConfig(GPIO_82_EMIF1_D2);
    GPIO_setPinConfig(GPIO_83_EMIF1_D1);
    GPIO_setPinConfig(GPIO_85_EMIF1_D0);

    //
    // Setting DQM and Bank Select lines.
    //
    GPIO_setPinConfig(GPIO_88_EMIF1_DQM0);
    GPIO_setPinConfig(GPIO_89_EMIF1_DQM1);
    GPIO_setPinConfig(GPIO_90_EMIF1_DQM2);
    GPIO_setPinConfig(GPIO_91_EMIF1_DQM3);
    GPIO_setPinConfig(GPIO_92_EMIF1_BA1);
    GPIO_setPinConfig(GPIO_93_EMIF1_BA0);

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

    GPIO_setPinConfig(GPIO_28_EMIF1_CS4N);
    GPIO_setPinConfig(GPIO_29_EMIF1_SDCKE);
    GPIO_setPinConfig(GPIO_30_EMIF1_CLK);
    GPIO_setPinConfig(GPIO_31_EMIF1_WEN);
    GPIO_setPinConfig(GPIO_32_EMIF1_CS0N);
    GPIO_setPinConfig(GPIO_33_EMIF1_RNW);
    GPIO_setPinConfig(GPIO_34_EMIF1_CS2N);
    GPIO_setPinConfig(GPIO_35_EMIF1_CS3N);
    GPIO_setPinConfig(GPIO_36_EMIF1_WAIT);
    GPIO_setPinConfig(GPIO_37_EMIF1_OEN);

    //
    // Selecting address lines.
    //
    GPIO_setPinConfig(GPIO_38_EMIF1_A0);
    GPIO_setPinConfig(GPIO_39_EMIF1_A1);
    GPIO_setPinConfig(GPIO_40_EMIF1_A2);
    GPIO_setPinConfig(GPIO_41_EMIF1_A3);
    GPIO_setPinConfig(GPIO_44_EMIF1_A4);
    GPIO_setPinConfig(GPIO_45_EMIF1_A5);
    GPIO_setPinConfig(GPIO_46_EMIF1_A6);
    GPIO_setPinConfig(GPIO_47_EMIF1_A7);
    GPIO_setPinConfig(GPIO_48_EMIF1_A8);
    GPIO_setPinConfig(GPIO_49_EMIF1_A9);
    GPIO_setPinConfig(GPIO_50_EMIF1_A10);
    GPIO_setPinConfig(GPIO_51_EMIF1_A11);
    GPIO_setPinConfig(GPIO_52_EMIF1_A12);
    GPIO_setPinConfig(GPIO_86_EMIF1_A13);
    GPIO_setPinConfig(GPIO_87_EMIF1_A14);

    //
    // Selecting data lines.
    //
    GPIO_setPinConfig(GPIO_53_EMIF1_D31);
    GPIO_setPinConfig(GPIO_54_EMIF1_D30);
    GPIO_setPinConfig(GPIO_55_EMIF1_D29);
    GPIO_setPinConfig(GPIO_56_EMIF1_D28);
    GPIO_setPinConfig(GPIO_57_EMIF1_D27);
    GPIO_setPinConfig(GPIO_58_EMIF1_D26);
    GPIO_setPinConfig(GPIO_59_EMIF1_D25);
    GPIO_setPinConfig(GPIO_60_EMIF1_D24);
    GPIO_setPinConfig(GPIO_61_EMIF1_D23);
    GPIO_setPinConfig(GPIO_62_EMIF1_D22);
    GPIO_setPinConfig(GPIO_63_EMIF1_D21);
    GPIO_setPinConfig(GPIO_64_EMIF1_D20);
    GPIO_setPinConfig(GPIO_65_EMIF1_D19);
    GPIO_setPinConfig(GPIO_66_EMIF1_D18);
    GPIO_setPinConfig(GPIO_67_EMIF1_D17);
    GPIO_setPinConfig(GPIO_68_EMIF1_D16);
    GPIO_setPinConfig(GPIO_69_EMIF1_D15);
    GPIO_setPinConfig(GPIO_70_EMIF1_D14);
    GPIO_setPinConfig(GPIO_71_EMIF1_D13);
    GPIO_setPinConfig(GPIO_72_EMIF1_D12);
    GPIO_setPinConfig(GPIO_73_EMIF1_D11);
    GPIO_setPinConfig(GPIO_74_EMIF1_D10);
    GPIO_setPinConfig(GPIO_75_EMIF1_D9);
    GPIO_setPinConfig(GPIO_76_EMIF1_D8);
    GPIO_setPinConfig(GPIO_77_EMIF1_D7);
    GPIO_setPinConfig(GPIO_78_EMIF1_D6);
    GPIO_setPinConfig(GPIO_79_EMIF1_D5);
    GPIO_setPinConfig(GPIO_80_EMIF1_D4);
    GPIO_setPinConfig(GPIO_81_EMIF1_D3);
    GPIO_setPinConfig(GPIO_82_EMIF1_D2);
    GPIO_setPinConfig(GPIO_83_EMIF1_D1);
    GPIO_setPinConfig(GPIO_85_EMIF1_D0);

    //
    // Setting DQM and Bank Select lines.
    //
    GPIO_setPinConfig(GPIO_88_EMIF1_DQM0);
    GPIO_setPinConfig(GPIO_89_EMIF1_DQM1);
    GPIO_setPinConfig(GPIO_90_EMIF1_DQM2);
    GPIO_setPinConfig(GPIO_91_EMIF1_DQM3);
    GPIO_setPinConfig(GPIO_92_EMIF1_BA1);
    GPIO_setPinConfig(GPIO_93_EMIF1_BA0);

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

    GPIO_setPinConfig(GPIO_96_EMIF2_DQM1);
    GPIO_setPinConfig(GPIO_97_EMIF2_DQM0);
    GPIO_setPinConfig(GPIO_98_EMIF2_A0);
    GPIO_setPinConfig(GPIO_99_EMIF2_A1);
    GPIO_setPinConfig(GPIO_100_EMIF2_A2);
    GPIO_setPinConfig(GPIO_101_EMIF2_A3);
    GPIO_setPinConfig(GPIO_102_EMIF2_A4);
    GPIO_setPinConfig(GPIO_103_EMIF2_A5);
    GPIO_setPinConfig(GPIO_104_EMIF2_A6);
    GPIO_setPinConfig(GPIO_105_EMIF2_A7);
    GPIO_setPinConfig(GPIO_106_EMIF2_A8);
    GPIO_setPinConfig(GPIO_107_EMIF2_A9);
    GPIO_setPinConfig(GPIO_108_EMIF2_A10);
    GPIO_setPinConfig(GPIO_109_EMIF2_A11);
    GPIO_setPinConfig(GPIO_110_EMIF2_WAIT);
    GPIO_setPinConfig(GPIO_111_EMIF2_BA0);
    GPIO_setPinConfig(GPIO_112_EMIF2_BA1);
    GPIO_setPinConfig(GPIO_113_EMIF2_CAS);
    GPIO_setPinConfig(GPIO_114_EMIF2_RAS);
    GPIO_setPinConfig(GPIO_115_EMIF2_CS0N);
    GPIO_setPinConfig(GPIO_116_EMIF2_CS2N);
    GPIO_setPinConfig(GPIO_117_EMIF2_SDCKE);
    GPIO_setPinConfig(GPIO_118_EMIF2_CLK);
    GPIO_setPinConfig(GPIO_119_EMIF2_RNW);
    GPIO_setPinConfig(GPIO_120_EMIF2_WEN);
    GPIO_setPinConfig(GPIO_121_EMIF2_OEN);

    //
    // Selecting Data lines.
    //
    GPIO_setPinConfig(GPIO_53_EMIF2_D15);
    GPIO_setPinConfig(GPIO_54_EMIF2_D14);
    GPIO_setPinConfig(GPIO_55_EMIF2_D13);
    GPIO_setPinConfig(GPIO_56_EMIF2_D12);
    GPIO_setPinConfig(GPIO_57_EMIF2_D11);
    GPIO_setPinConfig(GPIO_58_EMIF2_D10);
    GPIO_setPinConfig(GPIO_59_EMIF2_D9);
    GPIO_setPinConfig(GPIO_60_EMIF2_D8);
    GPIO_setPinConfig(GPIO_61_EMIF2_D7);
    GPIO_setPinConfig(GPIO_62_EMIF2_D6);
    GPIO_setPinConfig(GPIO_63_EMIF2_D5);
    GPIO_setPinConfig(GPIO_64_EMIF2_D4);
    GPIO_setPinConfig(GPIO_65_EMIF2_D3);
    GPIO_setPinConfig(GPIO_66_EMIF2_D2);
    GPIO_setPinConfig(GPIO_67_EMIF2_D1);
    GPIO_setPinConfig(GPIO_68_EMIF2_D0);

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
