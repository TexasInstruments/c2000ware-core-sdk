//###########################################################################
//
// FILE:   pin_map.h
//
// TITLE:  Definitions of pin mux info for gpio.c.
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

#ifndef __PIN_MAP_H__
#define __PIN_MAP_H__

//*****************************************************************************
// 0x00000003 = MUX register value
// 0x0000000C = GMUX register value
// 0x0000FF00 = Shift amount within mux registers
// 0xFFFF0000 = Offset of MUX register
//*****************************************************************************


#define GPIO_0_GPIO0                    0x00060000U
#define GPIO_0_EPWM1_A                  0x00060001U
#define GPIO_0_I2CA_SDA                 0x00060006U
#define GPIO_0_SPIA_STE                 0x00060007U
#define GPIO_0_FSIRXA_CLK               0x00060009U
#define GPIO_0_CLB_OUTPUTXBAR8          0x0006000BU
#define GPIO_0_HIC_BASESEL1             0x0006000FU

#define GPIO_1_GPIO1                    0x00060200U
#define GPIO_1_EPWM1_B                  0x00060201U
#define GPIO_1_I2CA_SCL                 0x00060206U
#define GPIO_1_SPIA_SOMI                0x00060207U
#define GPIO_1_CLB_OUTPUTXBAR7          0x0006020BU
#define GPIO_1_HIC_A2                   0x0006020DU
#define GPIO_1_FSITXA_TDM_D1            0x0006020EU
#define GPIO_1_HIC_D10                  0x0006020FU

#define GPIO_2_GPIO2                    0x00060400U
#define GPIO_2_EPWM2_A                  0x00060401U
#define GPIO_2_OUTPUTXBAR1              0x00060405U
#define GPIO_2_PMBUSA_SDA               0x00060406U
#define GPIO_2_SPIA_SIMO                0x00060407U
#define GPIO_2_SCIA_TX                  0x00060409U
#define GPIO_2_FSIRXA_D1                0x0006040AU
#define GPIO_2_I2CB_SDA                 0x0006040BU
#define GPIO_2_HIC_A1                   0x0006040DU
#define GPIO_2_CANA_TX                  0x0006040EU
#define GPIO_2_HIC_D9                   0x0006040FU

#define GPIO_3_GPIO3                    0x00060600U
#define GPIO_3_EPWM2_B                  0x00060601U
#define GPIO_3_OUTPUTXBAR2              0x00060602U
#define GPIO_3_PMBUSA_SCL               0x00060606U
#define GPIO_3_SPIA_CLK                 0x00060607U
#define GPIO_3_SCIA_RX                  0x00060609U
#define GPIO_3_FSIRXA_D0                0x0006060AU
#define GPIO_3_I2CB_SCL                 0x0006060BU
#define GPIO_3_HIC_NOE                  0x0006060DU
#define GPIO_3_CANA_RX                  0x0006060EU
#define GPIO_3_HIC_D4                   0x0006060FU

#define GPIO_4_GPIO4                    0x00060800U
#define GPIO_4_EPWM3_A                  0x00060801U
#define GPIO_4_OUTPUTXBAR3              0x00060805U
#define GPIO_4_CANA_TX                  0x00060806U
#define GPIO_4_SPIB_CLK                 0x00060807U
#define GPIO_4_EQEP2_STROBE             0x00060809U
#define GPIO_4_FSIRXA_CLK               0x0006080AU
#define GPIO_4_CLB_OUTPUTXBAR6          0x0006080BU
#define GPIO_4_HIC_BASESEL2             0x0006080DU
#define GPIO_4_HIC_NWE                  0x0006080FU

#define GPIO_5_GPIO5                    0x00060A00U
#define GPIO_5_EPWM3_B                  0x00060A01U
#define GPIO_5_OUTPUTXBAR3              0x00060A03U
#define GPIO_5_CANA_RX                  0x00060A06U
#define GPIO_5_SPIA_STE                 0x00060A07U
#define GPIO_5_FSITXA_D1                0x00060A09U
#define GPIO_5_CLB_OUTPUTXBAR5          0x00060A0AU
#define GPIO_5_HIC_A7                   0x00060A0DU
#define GPIO_5_HIC_D4                   0x00060A0EU
#define GPIO_5_HIC_D15                  0x00060A0FU

#define GPIO_6_GPIO6                    0x00060C00U
#define GPIO_6_EPWM4_A                  0x00060C01U
#define GPIO_6_OUTPUTXBAR4              0x00060C02U
#define GPIO_6_SYNCOUT                  0x00060C03U
#define GPIO_6_EQEP1_A                  0x00060C05U
#define GPIO_6_SPIB_SOMI                0x00060C07U
#define GPIO_6_FSITXA_D0                0x00060C09U
#define GPIO_6_FSITXA_D1                0x00060C0BU
#define GPIO_6_HIC_NBE1                 0x00060C0DU
#define GPIO_6_CLB_OUTPUTXBAR8          0x00060C0EU
#define GPIO_6_HIC_D14                  0x00060C0FU

#define GPIO_7_GPIO7                    0x00060E00U
#define GPIO_7_EPWM4_B                  0x00060E01U
#define GPIO_7_OUTPUTXBAR5              0x00060E03U
#define GPIO_7_EQEP1_B                  0x00060E05U
#define GPIO_7_SPIB_SIMO                0x00060E07U
#define GPIO_7_FSITXA_CLK               0x00060E09U
#define GPIO_7_CLB_OUTPUTXBAR2          0x00060E0AU
#define GPIO_7_HIC_A6                   0x00060E0DU
#define GPIO_7_HIC_D14                  0x00060E0FU

#define GPIO_8_GPIO8                    0x00061000U
#define GPIO_8_EPWM5_A                  0x00061001U
#define GPIO_8_ADCSOCAO                 0x00061003U
#define GPIO_8_EQEP1_STROBE             0x00061005U
#define GPIO_8_SCIA_TX                  0x00061006U
#define GPIO_8_SPIA_SIMO                0x00061007U
#define GPIO_8_I2CA_SCL                 0x00061009U
#define GPIO_8_FSITXA_D1                0x0006100AU
#define GPIO_8_CLB_OUTPUTXBAR5          0x0006100BU
#define GPIO_8_HIC_A0                   0x0006100DU
#define GPIO_8_FSITXA_TDM_CLK           0x0006100EU
#define GPIO_8_HIC_D8                   0x0006100FU

#define GPIO_9_GPIO9                    0x00061200U
#define GPIO_9_EPWM5_B                  0x00061201U
#define GPIO_9_OUTPUTXBAR6              0x00061203U
#define GPIO_9_EQEP1_INDEX              0x00061205U
#define GPIO_9_SCIA_RX                  0x00061206U
#define GPIO_9_SPIA_CLK                 0x00061207U
#define GPIO_9_FSITXA_D0                0x0006120AU
#define GPIO_9_LINB_RX                  0x0006120BU
#define GPIO_9_HIC_BASESEL0             0x0006120DU
#define GPIO_9_I2CB_SCL                 0x0006120EU
#define GPIO_9_HIC_NRDY                 0x0006120FU

#define GPIO_10_GPIO10                  0x00061400U
#define GPIO_10_EPWM6_A                 0x00061401U
#define GPIO_10_ADCSOCBO                0x00061403U
#define GPIO_10_EQEP1_A                 0x00061405U
#define GPIO_10_SPIA_SOMI               0x00061407U
#define GPIO_10_I2CA_SDA                0x00061409U
#define GPIO_10_FSITXA_CLK              0x0006140AU
#define GPIO_10_LINB_TX                 0x0006140BU
#define GPIO_10_HIC_NWE                 0x0006140DU
#define GPIO_10_FSITXA_TDM_D0           0x0006140EU

#define GPIO_11_GPIO11                  0x00061600U
#define GPIO_11_EPWM6_B                 0x00061601U
#define GPIO_11_OUTPUTXBAR7             0x00061603U
#define GPIO_11_EQEP1_B                 0x00061605U
#define GPIO_11_SPIA_STE                0x00061607U
#define GPIO_11_FSIRXA_D1               0x00061609U
#define GPIO_11_LINB_RX                 0x0006160AU
#define GPIO_11_EQEP2_A                 0x0006160BU
#define GPIO_11_SPIA_SIMO               0x0006160DU
#define GPIO_11_HIC_D6                  0x0006160EU
#define GPIO_11_HIC_NBE0                0x0006160FU

#define GPIO_12_GPIO12                  0x00061800U
#define GPIO_12_EPWM7_A                 0x00061801U
#define GPIO_12_EQEP1_STROBE            0x00061805U
#define GPIO_12_PMBUSA_CTL              0x00061807U
#define GPIO_12_FSIRXA_D0               0x00061809U
#define GPIO_12_LINB_TX                 0x0006180AU
#define GPIO_12_SPIA_CLK                0x0006180BU
#define GPIO_12_CANA_RX                 0x0006180DU
#define GPIO_12_HIC_D13                 0x0006180EU
#define GPIO_12_HIC_INT                 0x0006180FU

#define GPIO_13_GPIO13                  0x00061A00U
#define GPIO_13_EPWM7_B                 0x00061A01U
#define GPIO_13_EQEP1_INDEX             0x00061A05U
#define GPIO_13_PMBUSA_ALERT            0x00061A07U
#define GPIO_13_FSIRXA_CLK              0x00061A09U
#define GPIO_13_LINB_RX                 0x00061A0AU
#define GPIO_13_SPIA_SOMI               0x00061A0BU
#define GPIO_13_CANA_TX                 0x00061A0DU
#define GPIO_13_HIC_D11                 0x00061A0EU
#define GPIO_13_HIC_D5                  0x00061A0FU

#define GPIO_14_GPIO14                  0x00061C00U
#define GPIO_14_I2CB_SDA                0x00061C05U
#define GPIO_14_OUTPUTXBAR3             0x00061C06U
#define GPIO_14_PMBUSA_SDA              0x00061C07U
#define GPIO_14_SPIB_CLK                0x00061C09U
#define GPIO_14_EQEP2_A                 0x00061C0AU
#define GPIO_14_LINB_TX                 0x00061C0BU
#define GPIO_14_EPWM3_A                 0x00061C0DU
#define GPIO_14_CLB_OUTPUTXBAR7         0x00061C0EU
#define GPIO_14_HIC_D15                 0x00061C0FU

#define GPIO_15_GPIO15                  0x00061E00U
#define GPIO_15_I2CB_SCL                0x00061E05U
#define GPIO_15_OUTPUTXBAR4             0x00061E06U
#define GPIO_15_PMBUSA_SCL              0x00061E07U
#define GPIO_15_SPIB_STE                0x00061E09U
#define GPIO_15_EQEP2_B                 0x00061E0AU
#define GPIO_15_LINB_RX                 0x00061E0BU
#define GPIO_15_EPWM3_B                 0x00061E0DU
#define GPIO_15_CLB_OUTPUTXBAR6         0x00061E0EU
#define GPIO_15_HIC_D12                 0x00061E0FU

#define GPIO_16_GPIO16                  0x00080000U
#define GPIO_16_SPIA_SIMO               0x00080001U
#define GPIO_16_OUTPUTXBAR7             0x00080003U
#define GPIO_16_EPWM5_A                 0x00080005U
#define GPIO_16_SCIA_TX                 0x00080006U
#define GPIO_16_EQEP1_STROBE            0x00080009U
#define GPIO_16_PMBUSA_SCL              0x0008000AU
#define GPIO_16_XCLKOUT                 0x0008000BU
#define GPIO_16_EQEP2_B                 0x0008000DU
#define GPIO_16_SPIB_SOMI               0x0008000EU
#define GPIO_16_HIC_D1                  0x0008000FU

#define GPIO_17_GPIO17                  0x00080200U
#define GPIO_17_SPIA_SOMI               0x00080201U
#define GPIO_17_OUTPUTXBAR8             0x00080203U
#define GPIO_17_EPWM5_B                 0x00080205U
#define GPIO_17_SCIA_RX                 0x00080206U
#define GPIO_17_EQEP1_INDEX             0x00080209U
#define GPIO_17_PMBUSA_SDA              0x0008020AU
#define GPIO_17_CANA_TX                 0x0008020BU
#define GPIO_17_HIC_D2                  0x0008020FU

#define GPIO_18_GPIO18_X2               0x00080400U
#define GPIO_18_SPIA_CLK                0x00080401U
#define GPIO_18_CANA_RX                 0x00080403U
#define GPIO_18_EPWM6_A                 0x00080405U
#define GPIO_18_I2CA_SCL                0x00080406U
#define GPIO_18_EQEP2_A                 0x00080409U
#define GPIO_18_PMBUSA_CTL              0x0008040AU
#define GPIO_18_XCLKOUT                 0x0008040BU
#define GPIO_18_LINB_TX                 0x0008040DU
#define GPIO_18_FSITXA_TDM_CLK          0x0008040EU
#define GPIO_18_HIC_INT                 0x0008040FU

#define GPIO_19_GPIO19_X1               0x00080600U
#define GPIO_19_SPIA_STE                0x00080601U
#define GPIO_19_CANA_TX                 0x00080603U
#define GPIO_19_EPWM6_B                 0x00080605U
#define GPIO_19_I2CA_SDA                0x00080606U
#define GPIO_19_EQEP2_B                 0x00080609U
#define GPIO_19_PMBUSA_ALERT            0x0008060AU
#define GPIO_19_CLB_OUTPUTXBAR1         0x0008060BU
#define GPIO_19_LINB_RX                 0x0008060DU
#define GPIO_19_FSITXA_TDM_D0           0x0008060EU
#define GPIO_19_HIC_NBE0                0x0008060FU

#define GPIO_22_GPIO22                  0x00080C00U
#define GPIO_22_EQEP1_STROBE            0x00080C01U
#define GPIO_22_SPIB_CLK                0x00080C06U
#define GPIO_22_LINA_TX                 0x00080C09U
#define GPIO_22_CLB_OUTPUTXBAR1         0x00080C0AU
#define GPIO_22_LINB_TX                 0x00080C0BU
#define GPIO_22_HIC_A5                  0x00080C0DU
#define GPIO_22_EPWM4_A                 0x00080C0EU
#define GPIO_22_HIC_D13                 0x00080C0FU

#define GPIO_23_GPIO23                  0x00080E00U
#define GPIO_23_EQEP1_INDEX             0x00080E01U
#define GPIO_23_SPIB_STE                0x00080E06U
#define GPIO_23_LINA_RX                 0x00080E09U
#define GPIO_23_LINB_RX                 0x00080E0BU
#define GPIO_23_HIC_A3                  0x00080E0DU
#define GPIO_23_EPWM4_B                 0x00080E0EU
#define GPIO_23_HIC_D11                 0x00080E0FU

#define GPIO_24_GPIO24                  0x00081000U
#define GPIO_24_OUTPUTXBAR1             0x00081001U
#define GPIO_24_EQEP2_A                 0x00081002U
#define GPIO_24_SPIB_SIMO               0x00081006U
#define GPIO_24_LINB_TX                 0x00081009U
#define GPIO_24_PMBUSA_SCL              0x0008100AU
#define GPIO_24_SCIA_TX                 0x0008100BU
#define GPIO_24_ERRORSTS                0x0008100DU
#define GPIO_24_HIC_D3                  0x0008100FU

#define GPIO_25_GPIO25                  0x00081200U
#define GPIO_25_OUTPUTXBAR2             0x00081201U
#define GPIO_25_EQEP2_B                 0x00081202U
#define GPIO_25_EQEP1_A                 0x00081205U
#define GPIO_25_SPIB_SOMI               0x00081206U
#define GPIO_25_FSITXA_D1               0x00081209U
#define GPIO_25_PMBUSA_SDA              0x0008120AU
#define GPIO_25_SCIA_RX                 0x0008120BU
#define GPIO_25_HIC_BASESEL0            0x0008120EU

#define GPIO_26_GPIO26                  0x00081400U
#define GPIO_26_OUTPUTXBAR3             0x00081401U
#define GPIO_26_EQEP2_INDEX             0x00081402U
#define GPIO_26_SPIB_CLK                0x00081406U
#define GPIO_26_FSITXA_D0               0x00081409U
#define GPIO_26_PMBUSA_CTL              0x0008140AU
#define GPIO_26_I2CA_SDA                0x0008140BU
#define GPIO_26_HIC_D0                  0x0008140EU
#define GPIO_26_HIC_A1                  0x0008140FU

#define GPIO_27_GPIO27                  0x00081600U
#define GPIO_27_OUTPUTXBAR4             0x00081601U
#define GPIO_27_EQEP2_STROBE            0x00081602U
#define GPIO_27_SPIB_STE                0x00081606U
#define GPIO_27_FSITXA_CLK              0x00081609U
#define GPIO_27_PMBUSA_ALERT            0x0008160AU
#define GPIO_27_I2CA_SCL                0x0008160BU
#define GPIO_27_HIC_D1                  0x0008160EU
#define GPIO_27_HIC_A4                  0x0008160FU

#define GPIO_28_GPIO28                  0x00081800U
#define GPIO_28_SCIA_RX                 0x00081801U
#define GPIO_28_EPWM7_A                 0x00081803U
#define GPIO_28_OUTPUTXBAR5             0x00081805U
#define GPIO_28_EQEP1_A                 0x00081806U
#define GPIO_28_EQEP2_STROBE            0x00081809U
#define GPIO_28_LINA_TX                 0x0008180AU
#define GPIO_28_SPIB_CLK                0x0008180BU
#define GPIO_28_ERRORSTS                0x0008180DU
#define GPIO_28_I2CB_SDA                0x0008180EU
#define GPIO_28_HIC_NOE                 0x0008180FU

#define GPIO_29_GPIO29                  0x00081A00U
#define GPIO_29_SCIA_TX                 0x00081A01U
#define GPIO_29_EPWM7_B                 0x00081A03U
#define GPIO_29_OUTPUTXBAR6             0x00081A05U
#define GPIO_29_EQEP1_B                 0x00081A06U
#define GPIO_29_EQEP2_INDEX             0x00081A09U
#define GPIO_29_LINA_RX                 0x00081A0AU
#define GPIO_29_SPIB_STE                0x00081A0BU
#define GPIO_29_ERRORSTS                0x00081A0DU
#define GPIO_29_I2CB_SCL                0x00081A0EU
#define GPIO_29_HIC_NCS                 0x00081A0FU

#define GPIO_30_GPIO30                  0x00081C00U
#define GPIO_30_CANA_RX                 0x00081C01U
#define GPIO_30_SPIB_SIMO               0x00081C03U
#define GPIO_30_OUTPUTXBAR7             0x00081C05U
#define GPIO_30_EQEP1_STROBE            0x00081C06U
#define GPIO_30_FSIRXA_CLK              0x00081C09U
#define GPIO_30_EPWM1_A                 0x00081C0BU
#define GPIO_30_HIC_D8                  0x00081C0EU

#define GPIO_31_GPIO31                  0x00081E00U
#define GPIO_31_CANA_TX                 0x00081E01U
#define GPIO_31_SPIB_SOMI               0x00081E03U
#define GPIO_31_OUTPUTXBAR8             0x00081E05U
#define GPIO_31_EQEP1_INDEX             0x00081E06U
#define GPIO_31_FSIRXA_D1               0x00081E09U
#define GPIO_31_EPWM1_B                 0x00081E0BU
#define GPIO_31_HIC_D10                 0x00081E0EU

#define GPIO_32_GPIO32                  0x00460000U
#define GPIO_32_I2CA_SDA                0x00460001U
#define GPIO_32_SPIB_CLK                0x00460003U
#define GPIO_32_LINA_TX                 0x00460006U
#define GPIO_32_FSIRXA_D0               0x00460009U
#define GPIO_32_CANA_TX                 0x0046000AU
#define GPIO_32_ADCSOCBO                0x0046000DU
#define GPIO_32_HIC_INT                 0x0046000FU

#define GPIO_33_GPIO33                  0x00460200U
#define GPIO_33_I2CA_SCL                0x00460201U
#define GPIO_33_SPIB_STE                0x00460203U
#define GPIO_33_OUTPUTXBAR4             0x00460205U
#define GPIO_33_LINA_RX                 0x00460206U
#define GPIO_33_FSIRXA_CLK              0x00460209U
#define GPIO_33_CANA_RX                 0x0046020AU
#define GPIO_33_EQEP2_B                 0x0046020BU
#define GPIO_33_ADCSOCAO                0x0046020DU
#define GPIO_33_HIC_D0                  0x0046020FU

#define GPIO_34_GPIO34                  0x00460400U
#define GPIO_34_OUTPUTXBAR1             0x00460401U
#define GPIO_34_PMBUSA_SDA              0x00460406U
#define GPIO_34_HIC_NBE1                0x0046040DU
#define GPIO_34_I2CB_SDA                0x0046040EU
#define GPIO_34_HIC_D9                  0x0046040FU

#define GPIO_35_GPIO35                  0x00460600U
#define GPIO_35_SCIA_RX                 0x00460601U
#define GPIO_35_I2CA_SDA                0x00460603U
#define GPIO_35_CANA_RX                 0x00460605U
#define GPIO_35_PMBUSA_SCL              0x00460606U
#define GPIO_35_LINA_RX                 0x00460607U
#define GPIO_35_EQEP1_A                 0x00460609U
#define GPIO_35_PMBUSA_CTL              0x0046060AU
#define GPIO_35_HIC_NWE                 0x0046060EU
#define GPIO_35_TDI                     0x0046060FU

#define GPIO_37_GPIO37                  0x00460A00U
#define GPIO_37_OUTPUTXBAR2             0x00460A01U
#define GPIO_37_I2CA_SCL                0x00460A03U
#define GPIO_37_SCIA_TX                 0x00460A05U
#define GPIO_37_CANA_TX                 0x00460A06U
#define GPIO_37_LINA_TX                 0x00460A07U
#define GPIO_37_EQEP1_B                 0x00460A09U
#define GPIO_37_PMBUSA_ALERT            0x00460A0AU
#define GPIO_37_HIC_NRDY                0x00460A0EU
#define GPIO_37_TDO                     0x00460A0FU

#define GPIO_39_GPIO39                  0x00460E00U
#define GPIO_39_FSIRXA_CLK              0x00460E07U
#define GPIO_39_EQEP2_INDEX             0x00460E09U
#define GPIO_39_CLB_OUTPUTXBAR2         0x00460E0BU
#define GPIO_39_SYNCOUT                 0x00460E0DU
#define GPIO_39_EQEP1_INDEX             0x00460E0EU
#define GPIO_39_HIC_D7                  0x00460E0FU

#define GPIO_40_GPIO40                  0x00461000U
#define GPIO_40_SPIB_SIMO               0x00461001U
#define GPIO_40_EPWM2_B                 0x00461005U
#define GPIO_40_PMBUSA_SDA              0x00461006U
#define GPIO_40_FSIRXA_D0               0x00461007U
#define GPIO_40_EQEP1_A                 0x0046100AU
#define GPIO_40_LINB_TX                 0x0046100BU
#define GPIO_40_HIC_NBE1                0x0046100EU
#define GPIO_40_HIC_D5                  0x0046100FU

#define GPIO_41_GPIO41                  0x00461200U
#define GPIO_41_EPWM2_A                 0x00461205U
#define GPIO_41_PMBUSA_SCL              0x00461206U
#define GPIO_41_FSIRXA_D1               0x00461207U
#define GPIO_41_EQEP1_B                 0x0046120AU
#define GPIO_41_LINB_RX                 0x0046120BU
#define GPIO_41_HIC_A4                  0x0046120DU
#define GPIO_41_SPIB_SOMI               0x0046120EU
#define GPIO_41_HIC_D12                 0x0046120FU

#define GPIO_42_GPIO42                  0x00461400U
#define GPIO_42_LINA_RX                 0x00461402U
#define GPIO_42_OUTPUTXBAR5             0x00461403U
#define GPIO_42_PMBUSA_CTL              0x00461405U
#define GPIO_42_I2CA_SDA                0x00461406U
#define GPIO_42_EQEP1_STROBE            0x0046140AU
#define GPIO_42_CLB_OUTPUTXBAR3         0x0046140BU
#define GPIO_42_HIC_D2                  0x0046140EU
#define GPIO_42_HIC_A6                  0x0046140FU

#define GPIO_43_GPIO43                  0x00461600U
#define GPIO_43_OUTPUTXBAR6             0x00461603U
#define GPIO_43_PMBUSA_ALERT            0x00461605U
#define GPIO_43_I2CA_SCL                0x00461606U
#define GPIO_43_EQEP1_INDEX             0x0046160AU
#define GPIO_43_CLB_OUTPUTXBAR4         0x0046160BU
#define GPIO_43_HIC_D3                  0x0046160EU
#define GPIO_43_HIC_A7                  0x0046160FU

#define GPIO_44_GPIO44                  0x00461800U
#define GPIO_44_OUTPUTXBAR7             0x00461803U
#define GPIO_44_EQEP1_A                 0x00461805U
#define GPIO_44_FSITXA_CLK              0x00461807U
#define GPIO_44_CLB_OUTPUTXBAR3         0x0046180AU
#define GPIO_44_HIC_D7                  0x0046180DU
#define GPIO_44_HIC_D5                  0x0046180FU

#define GPIO_45_GPIO45                  0x00461A00U
#define GPIO_45_OUTPUTXBAR8             0x00461A03U
#define GPIO_45_FSITXA_D0               0x00461A07U
#define GPIO_45_CLB_OUTPUTXBAR4         0x00461A0AU
#define GPIO_45_HIC_D6                  0x00461A0FU

#define GPIO_46_GPIO46                  0x00461C00U
#define GPIO_46_LINA_TX                 0x00461C03U
#define GPIO_46_FSITXA_D1               0x00461C07U
#define GPIO_46_HIC_NWE                 0x00461C0FU

#define GPIO_61_GPIO61                  0x00481A00U

#define GPIO_62_GPIO62                  0x00481C00U

#define GPIO_63_GPIO63                  0x00481E00U

#define GPIO_224_GPIO224                0x01C60000U
#define GPIO_224_HIC_A3                 0x01C6000FU

#define GPIO_225_GPIO225                0x01C60200U
#define GPIO_225_HIC_NWE                0x01C6020FU

#define GPIO_226_GPIO226                0x01C60400U
#define GPIO_226_HIC_A1                 0x01C6040FU

#define GPIO_227_GPIO227                0x01C60600U
#define GPIO_227_HIC_NBE0               0x01C6060FU

#define GPIO_228_GPIO228                0x01C60800U
#define GPIO_228_HIC_A0                 0x01C6080FU

#define GPIO_230_GPIO230                0x01C60C00U
#define GPIO_230_HIC_BASESEL2           0x01C60C0FU

#define GPIO_231_GPIO231                0x01C60E00U
#define GPIO_231_HIC_BASESEL1           0x01C60E0FU

#define GPIO_232_GPIO232                0x01C61000U
#define GPIO_232_HIC_BASESEL0           0x01C6100FU

#define GPIO_233_GPIO233                0x01C61200U
#define GPIO_233_HIC_A4                 0x01C6120FU

#define GPIO_237_GPIO237                0x01C61A00U
#define GPIO_237_HIC_A6                 0x01C61A0FU

#define GPIO_238_GPIO238                0x01C61C00U
#define GPIO_238_HIC_NCS                0x01C61C0FU

#define GPIO_239_GPIO239                0x01C61E00U
#define GPIO_239_HIC_A5                 0x01C61E0FU

#define GPIO_241_GPIO241                0x01C80200U
#define GPIO_241_HIC_NBE1               0x01C8020FU

#define GPIO_242_GPIO242                0x01C80400U
#define GPIO_242_HIC_A2                 0x01C8040FU

#define GPIO_244_GPIO244                0x01C80800U
#define GPIO_244_HIC_A7                 0x01C8080FU

#define GPIO_245_GPIO245                0x01C80A00U
#define GPIO_245_HIC_NOE                0x01C80A0FU

#endif // PIN_MAP_H
