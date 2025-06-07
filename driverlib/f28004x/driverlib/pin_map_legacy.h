//###########################################################################
//
// FILE:   pin_map.h
//
// TITLE:  Legacy definitions of pin mux info for gpio.c.
//
//###########################################################################
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
//###########################################################################

#ifndef __PIN_MAP_LEGACY_H__
#define __PIN_MAP_LEGACY_H__


#include "pin_map.h"

//*****************************************************************************
// Legacy pinmuxing MACROS - Retained for portability across devices ONLY
// Not recommended for new users
//*****************************************************************************
#define GPIO_0_EPWM1A                   GPIO_0_EPWM1_A
#define GPIO_0_SDAA                     GPIO_0_I2CA_SDA

#define GPIO_1_EPWM1B                   GPIO_1_EPWM1_B
#define GPIO_1_SCLA                     GPIO_1_I2CA_SCL

#define GPIO_2_EPWM2A                   GPIO_2_EPWM2_A
#define GPIO_2_PMBASDA                  GPIO_2_PMBUSA_SDA
#define GPIO_2_SCITXDA                  GPIO_2_SCIA_TX
#define GPIO_2_FSI_RX1                  GPIO_2_FSIRXA_D1

#define GPIO_3_EPWM2B                   GPIO_3_EPWM2_B
#define GPIO_3_PMBASCL                  GPIO_3_PMBUSA_SCL
#define GPIO_3_SPICLKA                  GPIO_3_SPIA_CLK
#define GPIO_3_SCIRXDA                  GPIO_3_SCIA_RX
#define GPIO_3_FSI_RX0                  GPIO_3_FSIRXA_D0

#define GPIO_4_EPWM3A                   GPIO_4_EPWM3_A
#define GPIO_4_CANTXA                   GPIO_4_CANA_TX
#define GPIO_4_FSI_RXCLK                GPIO_4_FSIRXA_CLK

#define GPIO_5_EPWM3B                   GPIO_5_EPWM3_B
#define GPIO_5_CANRXA                   GPIO_5_CANA_RX
#define GPIO_5_SPISTEA                  GPIO_5_SPIA_STE
#define GPIO_5_FSI_TX1                  GPIO_5_FSITXA_D1

#define GPIO_6_EPWM4A                   GPIO_6_EPWM4_A
#define GPIO_6_EPWMSYNCO                GPIO_6_SYNCOUT
#define GPIO_6_EQEP1A                   GPIO_6_EQEP1_A
#define GPIO_6_CANTXB                   GPIO_6_CANB_TX
#define GPIO_6_SPISOMIB                 GPIO_6_SPIB_SOMI
#define GPIO_6_FSI_TX0                  GPIO_6_FSITXA_D0

#define GPIO_7_EPWM4B                   GPIO_7_EPWM4_B
#define GPIO_7_EQEP1B                   GPIO_7_EQEP1_B
#define GPIO_7_CANRXB                   GPIO_7_CANB_RX
#define GPIO_7_SPISIMOB                 GPIO_7_SPIB_SIMO
#define GPIO_7_FSI_TXCLK                GPIO_7_FSITXA_CLK

#define GPIO_8_EPWM5A                   GPIO_8_EPWM5_A
#define GPIO_8_CANTXB                   GPIO_8_CANB_TX
#define GPIO_8_EQEP1S                   GPIO_8_EQEP1_STROBE
#define GPIO_8_SCITXDA                  GPIO_8_SCIA_TX
#define GPIO_8_SPISIMOA                 GPIO_8_SPIA_SIMO
#define GPIO_8_SCLA                     GPIO_8_I2CA_SCL
#define GPIO_8_FSI_TX1                  GPIO_8_FSITXA_D1

#define GPIO_9_EPWM5B                   GPIO_9_EPWM5_B
#define GPIO_9_SCITXDB                  GPIO_9_SCIB_TX
#define GPIO_9_EQEP1I                   GPIO_9_EQEP1_INDEX
#define GPIO_9_SCIRXDA                  GPIO_9_SCIA_RX
#define GPIO_9_SPICLKA                  GPIO_9_SPIA_CLK
#define GPIO_9_FSI_TX0                  GPIO_9_FSITXA_D0

#define GPIO_10_EPWM6A                   GPIO_10_EPWM6_A
#define GPIO_10_CANRXB                   GPIO_10_CANB_RX
#define GPIO_10_EQEP1A                   GPIO_10_EQEP1_A
#define GPIO_10_SCITXDB                  GPIO_10_SCIB_TX
#define GPIO_10_SPISOMIA                 GPIO_10_SPIA_SOMI
#define GPIO_10_SDAA                     GPIO_10_I2CA_SDA
#define GPIO_10_FSI_TXCLK                GPIO_10_FSITXA_CLK

#define GPIO_11_EPWM6B                   GPIO_11_EPWM6_B
#define GPIO_11_SCIRXDB                  GPIO_11_SCIB_RX
#define GPIO_11_EQEP1B                   GPIO_11_EQEP1_B
#define GPIO_11_SPISTEA                  GPIO_11_SPIA_STE
#define GPIO_11_FSI_RX1                  GPIO_11_FSIRXA_D1

#define GPIO_12_EPWM7A                   GPIO_12_EPWM7_A
#define GPIO_12_CANTXB                   GPIO_12_CANB_TX
#define GPIO_12_EQEP1S                   GPIO_12_EQEP1_STROBE
#define GPIO_12_SCITXDB                  GPIO_12_SCIB_TX
#define GPIO_12_PMBACTL                  GPIO_12_PMBUSA_CTL
#define GPIO_12_FSI_RX0                  GPIO_12_FSIRXA_D0

#define GPIO_13_EPWM7B                   GPIO_13_EPWM7_B
#define GPIO_13_CANRXB                   GPIO_13_CANB_RX
#define GPIO_13_EQEP1I                   GPIO_13_EQEP1_INDEX
#define GPIO_13_SCIRXDB                  GPIO_13_SCIB_RX
#define GPIO_13_PMBAALRT                 GPIO_13_PMBUSA_ALERT
#define GPIO_13_FSI_RXCLK                GPIO_13_FSIRXA_CLK

#define GPIO_14_EPWM8A                   GPIO_14_EPWM8_A
#define GPIO_14_SCITXDB                  GPIO_14_SCIB_TX
#define GPIO_14_PMBASDA                  GPIO_14_PMBUSA_SDA
#define GPIO_14_SPICLKB                  GPIO_14_SPIB_CLK
#define GPIO_14_EQEP2A                   GPIO_14_EQEP2_A

#define GPIO_15_EPWM8B                   GPIO_15_EPWM8_B
#define GPIO_15_SCIRXDB                  GPIO_15_SCIB_RX
#define GPIO_15_PMBASCL                  GPIO_15_PMBUSA_SCL
#define GPIO_15_SPISTEB                  GPIO_15_SPIB_STE
#define GPIO_15_EQEP2B                   GPIO_15_EQEP2_B

#define GPIO_16_SPISIMOA                 GPIO_16_SPIA_SIMO
#define GPIO_16_CANTXB                   GPIO_16_CANB_TX
#define GPIO_16_EPWM5A                   GPIO_16_EPWM5_A
#define GPIO_16_SCITXDA                  GPIO_16_SCIA_TX
#define GPIO_16_SD_D1                    GPIO_16_SD1_D1
#define GPIO_16_EQEP1S                   GPIO_16_EQEP1_STROBE
#define GPIO_16_PMBASCL                  GPIO_16_PMBUSA_SCL

#define GPIO_17_SPISOMIA                 GPIO_17_SPIA_SOMI
#define GPIO_17_CANRXB                   GPIO_17_CANB_RX
#define GPIO_17_EPWM5B                   GPIO_17_EPWM5_B
#define GPIO_17_SCIRXDA                  GPIO_17_SCIA_RX
#define GPIO_17_SD_C1                    GPIO_17_SD1_C1
#define GPIO_17_EQEP1I                   GPIO_17_EQEP1_INDEX
#define GPIO_17_PMBASDA                  GPIO_17_PMBUSA_SDA

#define GPIO_18_GPIO18                   GPIO_18_GPIO18_X2
#define GPIO_18_SPICLKA                  GPIO_18_SPIA_CLK
#define GPIO_18_SCITXDB                  GPIO_18_SCIB_TX
#define GPIO_18_CANRXA                   GPIO_18_CANA_RX
#define GPIO_18_EPWM6A                   GPIO_18_EPWM6_A
#define GPIO_18_SCLA                     GPIO_18_I2CA_SCL
#define GPIO_18_SD_D2                    GPIO_18_SD1_D2
#define GPIO_18_EQEP2A                   GPIO_18_EQEP2_A
#define GPIO_18_PMBACTL                  GPIO_18_PMBUSA_CTL

#define GPIO_22_GPIO22                   GPIO_22_GPIO22_VFBSW
#define GPIO_22_EQEP1S                   GPIO_22_EQEP1_STROBE
#define GPIO_22_SCITXDB                  GPIO_22_SCIB_TX
#define GPIO_22_SPICLKB                  GPIO_22_SPIB_CLK
#define GPIO_22_SD_D4                    GPIO_22_SD1_D4
#define GPIO_22_LINTXA                   GPIO_22_LINA_TX

#define GPIO_24_EQEP2A                   GPIO_24_EQEP2_A
#define GPIO_24_EPWM8A                   GPIO_24_EPWM8_A
#define GPIO_24_SPISIMOB                 GPIO_24_SPIB_SIMO
#define GPIO_24_SD_D1                    GPIO_24_SD1_D1
#define GPIO_24_PMBASCL                  GPIO_24_PMBUSA_SCL
#define GPIO_24_SCITXDA                  GPIO_24_SCIA_TX
#define GPIO_24_ERROR_STS                GPIO_24_ERRORSTS

#define GPIO_25_EQEP2B                   GPIO_25_EQEP2_B
#define GPIO_25_SPISOMIB                 GPIO_25_SPIB_SOMI
#define GPIO_25_SD_C1                    GPIO_25_SD1_C1
#define GPIO_25_FSI_TX1                  GPIO_25_FSITXA_D1
#define GPIO_25_PMBASDA                  GPIO_25_PMBUSA_SDA
#define GPIO_25_SCIRXDA                  GPIO_25_SCIA_RX

#define GPIO_26_EQEP2I                   GPIO_26_EQEP2_INDEX
#define GPIO_26_SPICLKB                  GPIO_26_SPIB_CLK
#define GPIO_26_SD_D2                    GPIO_26_SD1_D2
#define GPIO_26_FSI_TX0                  GPIO_26_FSITXA_D0
#define GPIO_26_PMBACTL                  GPIO_26_PMBUSA_CTL
#define GPIO_26_SDAA                     GPIO_26_I2CA_SDA

#define GPIO_27_EQEP2S                   GPIO_27_EQEP2_STROBE
#define GPIO_27_SPISTEB                  GPIO_27_SPIB_STE
#define GPIO_27_SD_C2                    GPIO_27_SD1_C2
#define GPIO_27_FSI_TXCLK                GPIO_27_FSITXA_CLK
#define GPIO_27_PMBAALRT                 GPIO_27_PMBUSA_ALERT
#define GPIO_27_SCLA                     GPIO_27_I2CA_SCL

#define GPIO_28_SCIRXDA                  GPIO_28_SCIA_RX
#define GPIO_28_EPWM7A                   GPIO_28_EPWM7_A
#define GPIO_28_EQEP1A                   GPIO_28_EQEP1_A
#define GPIO_28_SD_D3                    GPIO_28_SD1_D3
#define GPIO_28_EQEP2S                   GPIO_28_EQEP2_STROBE
#define GPIO_28_LINTXA                   GPIO_28_LINA_TX
#define GPIO_28_SPICLKB                  GPIO_28_SPIB_CLK
#define GPIO_28_ERROR_STS                GPIO_28_ERRORSTS

#define GPIO_29_SCITXDA                  GPIO_29_SCIA_TX
#define GPIO_29_EPWM7B                   GPIO_29_EPWM7_B
#define GPIO_29_EQEP1B                   GPIO_29_EQEP1_B
#define GPIO_29_SD_C3                    GPIO_29_SD1_C3
#define GPIO_29_EQEP2I                   GPIO_29_EQEP2_INDEX
#define GPIO_29_LINRXA                   GPIO_29_LINA_RX
#define GPIO_29_SPISTEB                  GPIO_29_SPIB_STE
#define GPIO_29_ERROR_STS                GPIO_29_ERRORSTS

#define GPIO_30_CANRXA                   GPIO_30_CANA_RX
#define GPIO_30_SPISIMOB                 GPIO_30_SPIB_SIMO
#define GPIO_30_EQEP1S                   GPIO_30_EQEP1_STROBE
#define GPIO_30_SD_D4                    GPIO_30_SD1_D4

#define GPIO_31_CANTXA                   GPIO_31_CANA_TX
#define GPIO_31_SPISOMIB                 GPIO_31_SPIB_SOMI
#define GPIO_31_EQEP1I                   GPIO_31_EQEP1_INDEX
#define GPIO_31_SD_C4                    GPIO_31_SD1_C4
#define GPIO_31_FSI_RX1                  GPIO_31_FSIRXA_D1

#define GPIO_32_SDAA                     GPIO_32_I2CA_SDA
#define GPIO_32_SPICLKB                  GPIO_32_SPIB_CLK
#define GPIO_32_EPWM8B                   GPIO_32_EPWM8_B
#define GPIO_32_LINTXA                   GPIO_32_LINA_TX
#define GPIO_32_SD_D3                    GPIO_32_SD1_D3
#define GPIO_32_FSI_RX0                  GPIO_32_FSIRXA_D0
#define GPIO_32_CANTXA                   GPIO_32_CANA_TX

#define GPIO_33_SCLA                     GPIO_33_I2CA_SCL
#define GPIO_33_SPISTEB                  GPIO_33_SPIB_STE
#define GPIO_33_LINRXA                   GPIO_33_LINA_RX
#define GPIO_33_SD_C3                    GPIO_33_SD1_C3
#define GPIO_33_FSI_RXCLK                GPIO_33_FSIRXA_CLK
#define GPIO_33_CANRXA                   GPIO_33_CANA_RX

#define GPIO_34_PMBASDA                  GPIO_34_PMBUSA_SDA

#define GPIO_35_SCIRXDA                  GPIO_35_SCIA_RX
#define GPIO_35_SDAA                     GPIO_35_I2CA_SDA
#define GPIO_35_CANRXA                   GPIO_35_CANA_RX
#define GPIO_35_PMBASCL                  GPIO_35_PMBUSA_SCL
#define GPIO_35_LINRXA                   GPIO_35_LINA_RX
#define GPIO_35_EQEP1A                   GPIO_35_EQEP1_A
#define GPIO_35_PMBACTL                  GPIO_35_PMBUSA_CTL

#define GPIO_37_SCLA                     GPIO_37_I2CA_SCL
#define GPIO_37_SCITXDA                  GPIO_37_SCIA_TX
#define GPIO_37_CANTXA                   GPIO_37_CANA_TX
#define GPIO_37_LINTXA                   GPIO_37_LINA_TX
#define GPIO_37_EQEP1B                   GPIO_37_EQEP1_B
#define GPIO_37_PMBAALRT                 GPIO_37_PMBUSA_ALERT

#define GPIO_39_CANRXB                   GPIO_39_CANB_RX
#define GPIO_39_FSI_RXCLK                GPIO_39_FSIRXA_CLK

#define GPIO_40_PMBASDA                  GPIO_40_PMBUSA_SDA
#define GPIO_40_FSI_RX0                  GPIO_40_FSIRXA_D0
#define GPIO_40_SCITXDB                  GPIO_40_SCIB_TX
#define GPIO_40_EQEP1A                   GPIO_40_EQEP1_A

#define GPIO_56_SPICLKA                  GPIO_56_SPIA_CLK
#define GPIO_56_EQEP2S                   GPIO_56_EQEP2_STROBE
#define GPIO_56_SCITXDB                  GPIO_56_SCIB_TX
#define GPIO_56_SD_D3                    GPIO_56_SD1_D3
#define GPIO_56_SPISIMOB                 GPIO_56_SPIB_SIMO
#define GPIO_56_EQEP1A                   GPIO_56_EQEP1_A

#define GPIO_57_SPISTEA                  GPIO_57_SPIA_STE
#define GPIO_57_EQEP2I                   GPIO_57_EQEP2_INDEX
#define GPIO_57_SCIRXDB                  GPIO_57_SCIB_RX
#define GPIO_57_SD_C3                    GPIO_57_SD1_C3
#define GPIO_57_SPISOMIB                 GPIO_57_SPIB_SOMI
#define GPIO_57_EQEP1B                   GPIO_57_EQEP1_B

#define GPIO_58_SPICLKB                  GPIO_58_SPIB_CLK
#define GPIO_58_SD_D4                    GPIO_58_SD1_D4
#define GPIO_58_LINTXA                   GPIO_58_LINA_TX
#define GPIO_58_CANTXB                   GPIO_58_CANB_TX
#define GPIO_58_EQEP1S                   GPIO_58_EQEP1_STROBE

#define GPIO_59_SPISTEB                  GPIO_59_SPIB_STE
#define GPIO_59_SD_C4                    GPIO_59_SD1_C4
#define GPIO_59_LINRXA                   GPIO_59_LINA_RX
#define GPIO_59_CANRXB                   GPIO_59_CANB_RX
#define GPIO_59_EQEP1I                   GPIO_59_EQEP1_INDEX

#endif // __PIN_MAP_LEGACY_H__
