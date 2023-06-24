//###########################################################################
//
// FILE:   pin_map.h
//
// TITLE:  Legacy definitions of pin mux info for gpio.c.
//
//###########################################################################
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
#define GPIO_0_SPISTEA                  GPIO_0_SPIA_STE
#define GPIO_0_FSI_RXCLK                GPIO_0_FSIRXA_CLK
#define GPIO_0_HIBASESEL1               GPIO_0_HIC_BASESEL1

#define GPIO_1_EPWM1B                   GPIO_1_EPWM1_B
#define GPIO_1_SCLA                     GPIO_1_I2CA_SCL
#define GPIO_1_SPISOMIA                 GPIO_1_SPIA_SOMI
#define GPIO_1_HIADDR2                  GPIO_1_HIC_A2
#define GPIO_1_FSI_TDM_TX1              GPIO_1_FSITXA_TDM_D1
#define GPIO_1_HIDATA10                 GPIO_1_HIC_D10

#define GPIO_2_EPWM2A                   GPIO_2_EPWM2_A
#define GPIO_2_PMBASDA                  GPIO_2_PMBUSA_SDA
#define GPIO_2_SPISIMOA                 GPIO_2_SPIA_SIMO
#define GPIO_2_SCITXDA                  GPIO_2_SCIA_TX
#define GPIO_2_FSI_RX1                  GPIO_2_FSIRXA_D1
#define GPIO_2_SDAB                     GPIO_2_I2CB_SDA
#define GPIO_2_HIADDR1                  GPIO_2_HIC_A1
#define GPIO_2_CANTXA                   GPIO_2_CANA_TX
#define GPIO_2_HIDATA9                  GPIO_2_HIC_D9

#define GPIO_3_EPWM2B                   GPIO_3_EPWM2_B
#define GPIO_3_PMBASCL                  GPIO_3_PMBUSA_SCL
#define GPIO_3_SPICLKA                  GPIO_3_SPIA_CLK
#define GPIO_3_SCIRXDA                  GPIO_3_SCIA_RX
#define GPIO_3_FSI_RX0                  GPIO_3_FSIRXA_D0
#define GPIO_3_SCLB                     GPIO_3_I2CB_SCL
#define GPIO_3_HINOE                    GPIO_3_HIC_NOE
#define GPIO_3_CANRXA                   GPIO_3_CANA_RX
#define GPIO_3_HIDATA4                  GPIO_3_HIC_D4

#define GPIO_4_EPWM3A                   GPIO_4_EPWM3_A
#define GPIO_4_CANTXA                   GPIO_4_CANA_TX
#define GPIO_4_SPICLKB                  GPIO_4_SPIB_CLK
#define GPIO_4_EQEP2S                   GPIO_4_EQEP2_STROBE
#define GPIO_4_FSI_RXCLK                GPIO_4_FSIRXA_CLK
#define GPIO_4_HIBASESEL2               GPIO_4_HIC_BASESEL2
#define GPIO_4_HINWE                    GPIO_4_HIC_NWE

#define GPIO_5_EPWM3B                   GPIO_5_EPWM3_B
#define GPIO_5_CANRXA                   GPIO_5_CANA_RX
#define GPIO_5_SPISTEA                  GPIO_5_SPIA_STE
#define GPIO_5_FSI_TX1                  GPIO_5_FSITXA_D1
#define GPIO_5_HIADDR7                  GPIO_5_HIC_A7
#define GPIO_5_HIDATA4                  GPIO_5_HIC_D4
#define GPIO_5_HIDATA15                 GPIO_5_HIC_D15

#define GPIO_6_EPWM4A                   GPIO_6_EPWM4_A
#define GPIO_6_EPWMSYNCO                GPIO_6_SYNCOUT
#define GPIO_6_EQEP1A                   GPIO_6_EQEP1_A
#define GPIO_6_SPISOMIB                 GPIO_6_SPIB_SOMI
#define GPIO_6_FSI_TX0                  GPIO_6_FSITXA_D0
#define GPIO_6_FSI_TX1                  GPIO_6_FSITXA_D1
#define GPIO_6_HINBYTEN1                GPIO_6_HIC_NBE1
#define GPIO_6_HIDATA14                 GPIO_6_HIC_D14

#define GPIO_7_EPWM4B                   GPIO_7_EPWM4_B
#define GPIO_7_EQEP1B                   GPIO_7_EQEP1_B
#define GPIO_7_SPISIMOB                 GPIO_7_SPIB_SIMO
#define GPIO_7_FSI_TXCLK                GPIO_7_FSITXA_CLK
#define GPIO_7_HIADDR6                  GPIO_7_HIC_A6
#define GPIO_7_HIDATA14                 GPIO_7_HIC_D14

#define GPIO_8_EPWM5A                   GPIO_8_EPWM5_A
#define GPIO_8_EQEP1S                   GPIO_8_EQEP1_STROBE
#define GPIO_8_SCITXDA                  GPIO_8_SCIA_TX
#define GPIO_8_SPISIMOA                 GPIO_8_SPIA_SIMO
#define GPIO_8_SCLA                     GPIO_8_I2CA_SCL
#define GPIO_8_FSI_TX1                  GPIO_8_FSITXA_D1
#define GPIO_8_HIADDR0                  GPIO_8_HIC_A0
#define GPIO_8_FSI_TDM_CLK              GPIO_8_FSITXA_TDM_CLK
#define GPIO_8_HIDATA8                  GPIO_8_HIC_D8

#define GPIO_9_EPWM5B                   GPIO_9_EPWM5_B
#define GPIO_9_EQEP1I                   GPIO_9_EQEP1_INDEX
#define GPIO_9_SCIRXDA                  GPIO_9_SCIA_RX
#define GPIO_9_SPICLKA                  GPIO_9_SPIA_CLK
#define GPIO_9_FSI_TX0                  GPIO_9_FSITXA_D0
#define GPIO_9_LINRXB                   GPIO_9_LINB_RX
#define GPIO_9_HIBASESEL0               GPIO_9_HIC_BASESEL0
#define GPIO_9_SCLB                     GPIO_9_I2CB_SCL
#define GPIO_9_HINRDY                   GPIO_9_HIC_NRDY

#define GPIO_10_EPWM6A                   GPIO_10_EPWM6_A
#define GPIO_10_EQEP1A                   GPIO_10_EQEP1_A
#define GPIO_10_SPISOMIA                 GPIO_10_SPIA_SOMI
#define GPIO_10_SDAA                     GPIO_10_I2CA_SDA
#define GPIO_10_FSI_TXCLK                GPIO_10_FSITXA_CLK
#define GPIO_10_LINTXB                   GPIO_10_LINB_TX
#define GPIO_10_HINWE                    GPIO_10_HIC_NWE
#define GPIO_10_FSI_TDM_TX0              GPIO_10_FSITXA_TDM_D0

#define GPIO_11_EPWM6B                   GPIO_11_EPWM6_B
#define GPIO_11_EQEP1B                   GPIO_11_EQEP1_B
#define GPIO_11_SPISTEA                  GPIO_11_SPIA_STE
#define GPIO_11_FSI_RX1                  GPIO_11_FSIRXA_D1
#define GPIO_11_LINRXB                   GPIO_11_LINB_RX
#define GPIO_11_EQEP2A                   GPIO_11_EQEP2_A
#define GPIO_11_SPISIMOA                 GPIO_11_SPIA_SIMO
#define GPIO_11_HIDATA6                  GPIO_11_HIC_D6
#define GPIO_11_HINBYTEN0                GPIO_11_HIC_NBE0

#define GPIO_12_EPWM7A                   GPIO_12_EPWM7_A
#define GPIO_12_EQEP1S                   GPIO_12_EQEP1_STROBE
#define GPIO_12_PMBACTL                  GPIO_12_PMBUSA_CTL
#define GPIO_12_FSI_RX0                  GPIO_12_FSIRXA_D0
#define GPIO_12_LINTXB                   GPIO_12_LINB_TX
#define GPIO_12_SPICLKA                  GPIO_12_SPIA_CLK
#define GPIO_12_CANRXA                   GPIO_12_CANA_RX
#define GPIO_12_HIDATA13                 GPIO_12_HIC_D13
#define GPIO_12_HIINT                    GPIO_12_HIC_INT

#define GPIO_13_EPWM7B                   GPIO_13_EPWM7_B
#define GPIO_13_EQEP1I                   GPIO_13_EQEP1_INDEX
#define GPIO_13_PMBAALRT                 GPIO_13_PMBUSA_ALERT
#define GPIO_13_FSI_RXCLK                GPIO_13_FSIRXA_CLK
#define GPIO_13_LINRXB                   GPIO_13_LINB_RX
#define GPIO_13_SPISOMIA                 GPIO_13_SPIA_SOMI
#define GPIO_13_CANTXA                   GPIO_13_CANA_TX
#define GPIO_13_HIDATA11                 GPIO_13_HIC_D11
#define GPIO_13_HIDATA5                  GPIO_13_HIC_D5

#define GPIO_14_SDAB                     GPIO_14_I2CB_SDA
#define GPIO_14_PMBASDA                  GPIO_14_PMBUSA_SDA
#define GPIO_14_SPICLKB                  GPIO_14_SPIB_CLK
#define GPIO_14_EQEP2A                   GPIO_14_EQEP2_A
#define GPIO_14_LINTXB                   GPIO_14_LINB_TX
#define GPIO_14_EPWM3A                   GPIO_14_EPWM3_A
#define GPIO_14_HIDATA15                 GPIO_14_HIC_D15

#define GPIO_15_SCLB                     GPIO_15_I2CB_SCL
#define GPIO_15_PMBASCL                  GPIO_15_PMBUSA_SCL
#define GPIO_15_SPISTEB                  GPIO_15_SPIB_STE
#define GPIO_15_EQEP2B                   GPIO_15_EQEP2_B
#define GPIO_15_LINRXB                   GPIO_15_LINB_RX
#define GPIO_15_EPWM3B                   GPIO_15_EPWM3_B
#define GPIO_15_HIDATA12                 GPIO_15_HIC_D12

#define GPIO_16_SPISIMOA                 GPIO_16_SPIA_SIMO
#define GPIO_16_EPWM5A                   GPIO_16_EPWM5_A
#define GPIO_16_SCITXDA                  GPIO_16_SCIA_TX
#define GPIO_16_EQEP1S                   GPIO_16_EQEP1_STROBE
#define GPIO_16_PMBASCL                  GPIO_16_PMBUSA_SCL
#define GPIO_16_EQEP2B                   GPIO_16_EQEP2_B
#define GPIO_16_SPISOMIB                 GPIO_16_SPIB_SOMI
#define GPIO_16_HIDATA1                  GPIO_16_HIC_D1

#define GPIO_17_SPISOMIA                 GPIO_17_SPIA_SOMI
#define GPIO_17_EPWM5B                   GPIO_17_EPWM5_B
#define GPIO_17_SCIRXDA                  GPIO_17_SCIA_RX
#define GPIO_17_EQEP1I                   GPIO_17_EQEP1_INDEX
#define GPIO_17_PMBASDA                  GPIO_17_PMBUSA_SDA
#define GPIO_17_CANTXA                   GPIO_17_CANA_TX
#define GPIO_17_HIDATA2                  GPIO_17_HIC_D2

#define GPIO_18_SPICLKA                  GPIO_18_SPIA_CLK
#define GPIO_18_CANRXA                   GPIO_18_CANA_RX
#define GPIO_18_EPWM6A                   GPIO_18_EPWM6_A
#define GPIO_18_SCLA                     GPIO_18_I2CA_SCL
#define GPIO_18_EQEP2A                   GPIO_18_EQEP2_A
#define GPIO_18_PMBACTL                  GPIO_18_PMBUSA_CTL
#define GPIO_18_LINTXB                   GPIO_18_LINB_TX
#define GPIO_18_FSI_TDM_CLK              GPIO_18_FSITXA_TDM_CLK
#define GPIO_18_HIINT                    GPIO_18_HIC_INT

#define GPIO_19_SPISTEA                  GPIO_19_SPIA_STE
#define GPIO_19_CANTXA                   GPIO_19_CANA_TX
#define GPIO_19_EPWM6B                   GPIO_19_EPWM6_B
#define GPIO_19_SDAA                     GPIO_19_I2CA_SDA
#define GPIO_19_EQEP2B                   GPIO_19_EQEP2_B
#define GPIO_19_PMBAALRT                 GPIO_19_PMBUSA_ALERT
#define GPIO_19_LINRXB                   GPIO_19_LINB_RX
#define GPIO_19_FSI_TDM_TX0              GPIO_19_FSITXA_TDM_D0
#define GPIO_19_HINBYTEN0                GPIO_19_HIC_NBE0

#define GPIO_22_EQEP1S                   GPIO_22_EQEP1_STROBE
#define GPIO_22_SPICLKB                  GPIO_22_SPIB_CLK
#define GPIO_22_LINTXA                   GPIO_22_LINA_TX
#define GPIO_22_LINTXB                   GPIO_22_LINB_TX
#define GPIO_22_HIADDR5                  GPIO_22_HIC_A5
#define GPIO_22_EPWM4A                   GPIO_22_EPWM4_A
#define GPIO_22_HIDATA13                 GPIO_22_HIC_D13

#define GPIO_23_EQEP1I                   GPIO_23_EQEP1_INDEX
#define GPIO_23_SPISTEB                  GPIO_23_SPIB_STE
#define GPIO_23_LINRXA                   GPIO_23_LINA_RX
#define GPIO_23_LINRXB                   GPIO_23_LINB_RX
#define GPIO_23_HIADDR3                  GPIO_23_HIC_A3
#define GPIO_23_EPWM4B                   GPIO_23_EPWM4_B
#define GPIO_23_HIDATA11                 GPIO_23_HIC_D11

#define GPIO_24_EQEP2A                   GPIO_24_EQEP2_A
#define GPIO_24_SPISIMOB                 GPIO_24_SPIB_SIMO
#define GPIO_24_LINTXB                   GPIO_24_LINB_TX
#define GPIO_24_PMBASCL                  GPIO_24_PMBUSA_SCL
#define GPIO_24_SCITXDA                  GPIO_24_SCIA_TX
#define GPIO_24_HIDATA3                  GPIO_24_HIC_D3

#define GPIO_25_EQEP2B                   GPIO_25_EQEP2_B
#define GPIO_25_EQEP1A                   GPIO_25_EQEP1_A
#define GPIO_25_SPISOMIB                 GPIO_25_SPIB_SOMI
#define GPIO_25_FSI_TX1                  GPIO_25_FSITXA_D1
#define GPIO_25_PMBASDA                  GPIO_25_PMBUSA_SDA
#define GPIO_25_SCIRXDA                  GPIO_25_SCIA_RX
#define GPIO_25_HIBASESEL0               GPIO_25_HIC_BASESEL0

#define GPIO_26_EQEP2I                   GPIO_26_EQEP2_INDEX
#define GPIO_26_SPICLKB                  GPIO_26_SPIB_CLK
#define GPIO_26_FSI_TX0                  GPIO_26_FSITXA_D0
#define GPIO_26_PMBACTL                  GPIO_26_PMBUSA_CTL
#define GPIO_26_SDAA                     GPIO_26_I2CA_SDA
#define GPIO_26_HIDATA0                  GPIO_26_HIC_D0
#define GPIO_26_HIADDR1                  GPIO_26_HIC_A1

#define GPIO_27_EQEP2S                   GPIO_27_EQEP2_STROBE
#define GPIO_27_SPISTEB                  GPIO_27_SPIB_STE
#define GPIO_27_FSI_TXCLK                GPIO_27_FSITXA_CLK
#define GPIO_27_PMBAALRT                 GPIO_27_PMBUSA_ALERT
#define GPIO_27_SCLA                     GPIO_27_I2CA_SCL
#define GPIO_27_HIDATA1                  GPIO_27_HIC_D1
#define GPIO_27_HIADDR4                  GPIO_27_HIC_A4

#define GPIO_28_SCIRXDA                  GPIO_28_SCIA_RX
#define GPIO_28_EPWM7A                   GPIO_28_EPWM7_A
#define GPIO_28_EQEP1A                   GPIO_28_EQEP1_A
#define GPIO_28_EQEP2S                   GPIO_28_EQEP2_STROBE
#define GPIO_28_LINTXA                   GPIO_28_LINA_TX
#define GPIO_28_SPICLKB                  GPIO_28_SPIB_CLK
#define GPIO_28_SDAB                     GPIO_28_I2CB_SDA
#define GPIO_28_HINOE                    GPIO_28_HIC_NOE

#define GPIO_29_SCITXDA                  GPIO_29_SCIA_TX
#define GPIO_29_EPWM7B                   GPIO_29_EPWM7_B
#define GPIO_29_EQEP1B                   GPIO_29_EQEP1_B
#define GPIO_29_EQEP2I                   GPIO_29_EQEP2_INDEX
#define GPIO_29_LINRXA                   GPIO_29_LINA_RX
#define GPIO_29_SPISTEB                  GPIO_29_SPIB_STE
#define GPIO_29_SCLB                     GPIO_29_I2CB_SCL
#define GPIO_29_HINCS                    GPIO_29_HIC_NCS

#define GPIO_30_CANRXA                   GPIO_30_CANA_RX
#define GPIO_30_SPISIMOB                 GPIO_30_SPIB_SIMO
#define GPIO_30_EQEP1S                   GPIO_30_EQEP1_STROBE
#define GPIO_30_FSI_RXCLK                GPIO_30_FSIRXA_CLK
#define GPIO_30_EPWM1A                   GPIO_30_EPWM1_A
#define GPIO_30_HIDATA8                  GPIO_30_HIC_D8

#define GPIO_31_CANTXA                   GPIO_31_CANA_TX
#define GPIO_31_SPISOMIB                 GPIO_31_SPIB_SOMI
#define GPIO_31_EQEP1I                   GPIO_31_EQEP1_INDEX
#define GPIO_31_FSI_RX1                  GPIO_31_FSIRXA_D1
#define GPIO_31_EPWM1B                   GPIO_31_EPWM1_B
#define GPIO_31_HIDATA10                 GPIO_31_HIC_D10

#define GPIO_32_SDAA                     GPIO_32_I2CA_SDA
#define GPIO_32_SPICLKB                  GPIO_32_SPIB_CLK
#define GPIO_32_LINTXA                   GPIO_32_LINA_TX
#define GPIO_32_FSI_RX0                  GPIO_32_FSIRXA_D0
#define GPIO_32_CANTXA                   GPIO_32_CANA_TX
#define GPIO_32_HIINT                    GPIO_32_HIC_INT

#define GPIO_33_SCLA                     GPIO_33_I2CA_SCL
#define GPIO_33_SPISTEB                  GPIO_33_SPIB_STE
#define GPIO_33_LINRXA                   GPIO_33_LINA_RX
#define GPIO_33_FSI_RXCLK                GPIO_33_FSIRXA_CLK
#define GPIO_33_CANRXA                   GPIO_33_CANA_RX
#define GPIO_33_EQEP2B                   GPIO_33_EQEP2_B
#define GPIO_33_HIDATA0                  GPIO_33_HIC_D0

#define GPIO_34_PMBASDA                  GPIO_34_PMBUSA_SDA
#define GPIO_34_HINBYTEN1                GPIO_34_HIC_NBE1
#define GPIO_34_SDAB                     GPIO_34_I2CB_SDA
#define GPIO_34_HIDATA9                  GPIO_34_HIC_D9

#define GPIO_35_SCIRXDA                  GPIO_35_SCIA_RX
#define GPIO_35_SDAA                     GPIO_35_I2CA_SDA
#define GPIO_35_CANRXA                   GPIO_35_CANA_RX
#define GPIO_35_PMBASCL                  GPIO_35_PMBUSA_SCL
#define GPIO_35_LINRXA                   GPIO_35_LINA_RX
#define GPIO_35_EQEP1A                   GPIO_35_EQEP1_A
#define GPIO_35_PMBACTL                  GPIO_35_PMBUSA_CTL
#define GPIO_35_HINWE                    GPIO_35_HIC_NWE

#define GPIO_37_SCLA                     GPIO_37_I2CA_SCL
#define GPIO_37_SCITXDA                  GPIO_37_SCIA_TX
#define GPIO_37_CANTXA                   GPIO_37_CANA_TX
#define GPIO_37_LINTXA                   GPIO_37_LINA_TX
#define GPIO_37_EQEP1B                   GPIO_37_EQEP1_B
#define GPIO_37_PMBAALRT                 GPIO_37_PMBUSA_ALERT
#define GPIO_37_HINRDY                   GPIO_37_HIC_NRDY

#define GPIO_39_FSI_RXCLK                GPIO_39_FSIRXA_CLK
#define GPIO_39_EQEP2I                   GPIO_39_EQEP2_INDEX
#define GPIO_39_EPWMSYNCO                GPIO_39_SYNCOUT
#define GPIO_39_EQEP1I                   GPIO_39_EQEP1_INDEX
#define GPIO_39_HIDATA7                  GPIO_39_HIC_D7

#define GPIO_40_SPISIMOB                 GPIO_40_SPIB_SIMO
#define GPIO_40_EPWM2B                   GPIO_40_EPWM2_B
#define GPIO_40_PMBASDA                  GPIO_40_PMBUSA_SDA
#define GPIO_40_FSI_RX0                  GPIO_40_FSIRXA_D0
#define GPIO_40_EQEP1A                   GPIO_40_EQEP1_A
#define GPIO_40_LINTXB                   GPIO_40_LINB_TX
#define GPIO_40_HINBYTEN1                GPIO_40_HIC_NBE1
#define GPIO_40_HIDATA5                  GPIO_40_HIC_D5

#define GPIO_41_EPWM2A                   GPIO_41_EPWM2_A
#define GPIO_41_PMBASCL                  GPIO_41_PMBUSA_SCL
#define GPIO_41_FSI_RX1                  GPIO_41_FSIRXA_D1
#define GPIO_41_EQEP1B                   GPIO_41_EQEP1_B
#define GPIO_41_LINRXB                   GPIO_41_LINB_RX
#define GPIO_41_HIADDR4                  GPIO_41_HIC_A4
#define GPIO_41_SPISOMIB                 GPIO_41_SPIB_SOMI
#define GPIO_41_HIDATA12                 GPIO_41_HIC_D12

#define GPIO_42_LINRXA                   GPIO_42_LINA_RX
#define GPIO_42_PMBACTL                  GPIO_42_PMBUSA_CTL
#define GPIO_42_SDAA                     GPIO_42_I2CA_SDA
#define GPIO_42_EQEP1S                   GPIO_42_EQEP1_STROBE
#define GPIO_42_HIDATA2                  GPIO_42_HIC_D2
#define GPIO_42_HIADDR6                  GPIO_42_HIC_A6

#define GPIO_43_PMBAALRT                 GPIO_43_PMBUSA_ALERT
#define GPIO_43_SCLA                     GPIO_43_I2CA_SCL
#define GPIO_43_EQEP1I                   GPIO_43_EQEP1_INDEX
#define GPIO_43_HIDATA3                  GPIO_43_HIC_D3
#define GPIO_43_HIADDR7                  GPIO_43_HIC_A7

#define GPIO_44_EQEP1A                   GPIO_44_EQEP1_A
#define GPIO_44_FSI_TXCLK                GPIO_44_FSITXA_CLK
#define GPIO_44_HIDATA7                  GPIO_44_HIC_D7
#define GPIO_44_HIDATA5                  GPIO_44_HIC_D5

#define GPIO_45_FSI_TX0                  GPIO_45_FSITXA_D0
#define GPIO_45_HIDATA6                  GPIO_45_HIC_D6

#define GPIO_46_LINTXA                   GPIO_46_LINA_TX
#define GPIO_46_FSI_TX1                  GPIO_46_FSITXA_D1
#define GPIO_46_HINWE                    GPIO_46_HIC_NWE

#define GPIO_230_HIBASESEL2              GPIO_230_HIC_BASESEL2
#define GPIO_231_HIBASESEL1              GPIO_231_HIC_BASESEL1
#define GPIO_232_HIBASESEL0              GPIO_232_HIC_BASESEL0

#endif // __PIN_MAP_LEGACY_H__
