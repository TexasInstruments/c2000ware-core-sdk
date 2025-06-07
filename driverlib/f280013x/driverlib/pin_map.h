//###########################################################################
//
// FILE:   pin_map.h
//
// TITLE:  Definitions of pin mux info for gpio.c.
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
#define GPIO_0_CANA_RX                  0x00060002U
#define GPIO_0_OUTPUTXBAR7              0x00060003U
#define GPIO_0_SCIA_RX                  0x00060005U
#define GPIO_0_I2CA_SDA                 0x00060006U
#define GPIO_0_SPIA_STE                 0x00060007U
#define GPIO_0_EQEP1_INDEX              0x0006000DU
#define GPIO_0_EPWM3_A                  0x0006000FU

#define GPIO_1_GPIO1                    0x00060200U
#define GPIO_1_EPWM1_B                  0x00060201U
#define GPIO_1_SCIA_TX                  0x00060205U
#define GPIO_1_I2CA_SCL                 0x00060206U
#define GPIO_1_SPIA_SOMI                0x00060207U
#define GPIO_1_EQEP1_STROBE             0x00060209U
#define GPIO_1_EPWM3_B                  0x0006020FU

#define GPIO_2_GPIO2                    0x00060400U
#define GPIO_2_EPWM2_A                  0x00060401U
#define GPIO_2_OUTPUTXBAR1              0x00060405U
#define GPIO_2_SPIA_SIMO                0x00060407U
#define GPIO_2_SCIA_TX                  0x00060409U
#define GPIO_2_I2CB_SDA                 0x0006040BU
#define GPIO_2_CANA_TX                  0x0006040EU
#define GPIO_2_EPWM4_A                  0x0006040FU

#define GPIO_3_GPIO3                    0x00060600U
#define GPIO_3_EPWM2_B                  0x00060601U
#define GPIO_3_OUTPUTXBAR2              0x00060602U
#define GPIO_3_SPIA_CLK                 0x00060607U
#define GPIO_3_SCIA_RX                  0x00060609U
#define GPIO_3_I2CB_SCL                 0x0006060BU
#define GPIO_3_CANA_RX                  0x0006060EU
#define GPIO_3_EPWM4_B                  0x0006060FU

#define GPIO_4_GPIO4                    0x00060800U
#define GPIO_4_EPWM3_A                  0x00060801U
#define GPIO_4_I2CA_SCL                 0x00060802U
#define GPIO_4_OUTPUTXBAR3              0x00060805U
#define GPIO_4_CANA_TX                  0x00060806U
#define GPIO_4_SPIA_SOMI                0x0006080EU
#define GPIO_4_EPWM1_A                  0x0006080FU

#define GPIO_5_GPIO5                    0x00060A00U
#define GPIO_5_EPWM3_B                  0x00060A01U
#define GPIO_5_I2CA_SDA                 0x00060A02U
#define GPIO_5_OUTPUTXBAR3              0x00060A03U
#define GPIO_5_CANA_RX                  0x00060A06U
#define GPIO_5_SPIA_STE                 0x00060A07U
#define GPIO_5_SCIA_RX                  0x00060A0BU
#define GPIO_5_EPWM1_B                  0x00060A0FU

#define GPIO_6_GPIO6                    0x00060C00U
#define GPIO_6_EPWM4_A                  0x00060C01U
#define GPIO_6_OUTPUTXBAR4              0x00060C02U
#define GPIO_6_SYNCOUT                  0x00060C03U
#define GPIO_6_EQEP1_A                  0x00060C05U
#define GPIO_6_EPWM2_A                  0x00060C0FU

#define GPIO_7_GPIO7                    0x00060E00U
#define GPIO_7_EPWM4_B                  0x00060E01U
#define GPIO_7_EPWM2_A                  0x00060E02U
#define GPIO_7_OUTPUTXBAR5              0x00060E03U
#define GPIO_7_EQEP1_B                  0x00060E05U
#define GPIO_7_SPIA_SIMO                0x00060E07U
#define GPIO_7_SCIA_TX                  0x00060E0BU
#define GPIO_7_CANA_TX                  0x00060E0EU
#define GPIO_7_EPWM2_B                  0x00060E0FU

#define GPIO_8_GPIO8                    0x00061000U
#define GPIO_8_EPWM5_A                  0x00061001U
#define GPIO_8_ADCSOCAO                 0x00061003U
#define GPIO_8_EQEP1_STROBE             0x00061005U
#define GPIO_8_SCIA_TX                  0x00061006U
#define GPIO_8_SPIA_SIMO                0x00061007U
#define GPIO_8_I2CA_SCL                 0x00061009U

#define GPIO_9_GPIO9                    0x00061200U
#define GPIO_9_EPWM5_B                  0x00061201U
#define GPIO_9_SCIB_TX                  0x00061202U
#define GPIO_9_OUTPUTXBAR6              0x00061203U
#define GPIO_9_EQEP1_INDEX              0x00061205U
#define GPIO_9_SCIA_RX                  0x00061206U
#define GPIO_9_SPIA_CLK                 0x00061207U
#define GPIO_9_I2CB_SCL                 0x0006120EU

#define GPIO_10_GPIO10                  0x00061400U
#define GPIO_10_EPWM6_A                 0x00061401U
#define GPIO_10_ADCSOCBO                0x00061403U
#define GPIO_10_EQEP1_A                 0x00061405U
#define GPIO_10_SCIB_TX                 0x00061406U
#define GPIO_10_SPIA_SOMI               0x00061407U
#define GPIO_10_I2CA_SDA                0x00061409U

#define GPIO_11_GPIO11                  0x00061600U
#define GPIO_11_EPWM6_B                 0x00061601U
#define GPIO_11_CANA_RX                 0x00061602U
#define GPIO_11_OUTPUTXBAR7             0x00061603U
#define GPIO_11_EQEP1_B                 0x00061605U
#define GPIO_11_SCIB_RX                 0x00061606U
#define GPIO_11_SPIA_STE                0x00061607U
#define GPIO_11_SPIA_SIMO               0x0006160DU

#define GPIO_12_GPIO12                  0x00061800U
#define GPIO_12_EPWM7_A                 0x00061801U
#define GPIO_12_EQEP1_STROBE            0x00061805U
#define GPIO_12_SCIB_TX                 0x00061806U
#define GPIO_12_SPIA_CLK                0x0006180BU
#define GPIO_12_CANA_RX                 0x0006180DU

#define GPIO_13_GPIO13                  0x00061A00U
#define GPIO_13_EPWM7_B                 0x00061A01U
#define GPIO_13_EQEP1_INDEX             0x00061A05U
#define GPIO_13_SCIB_RX                 0x00061A06U
#define GPIO_13_SPIA_SOMI               0x00061A0BU
#define GPIO_13_CANA_TX                 0x00061A0DU

#define GPIO_16_GPIO16                  0x00080000U
#define GPIO_16_SPIA_SIMO               0x00080001U
#define GPIO_16_OUTPUTXBAR7             0x00080003U
#define GPIO_16_EPWM5_A                 0x00080005U
#define GPIO_16_SCIA_TX                 0x00080006U
#define GPIO_16_EQEP1_STROBE            0x00080009U
#define GPIO_16_XCLKOUT                 0x0008000BU

#define GPIO_17_GPIO17                  0x00080200U
#define GPIO_17_SPIA_SOMI               0x00080201U
#define GPIO_17_OUTPUTXBAR8             0x00080203U
#define GPIO_17_EPWM5_B                 0x00080205U
#define GPIO_17_SCIA_RX                 0x00080206U
#define GPIO_17_EQEP1_INDEX             0x00080209U
#define GPIO_17_CANA_TX                 0x0008020BU
#define GPIO_17_EPWM6_A                 0x0008020EU

#define GPIO_18_GPIO18                  0x00080400U
#define GPIO_18_SPIA_CLK                0x00080401U
#define GPIO_18_SCIB_TX                 0x00080402U
#define GPIO_18_CANA_RX                 0x00080403U
#define GPIO_18_EPWM6_A                 0x00080405U
#define GPIO_18_I2CA_SCL                0x00080406U
#define GPIO_18_XCLKOUT                 0x0008040BU

#define GPIO_19_GPIO19                  0x00080600U
#define GPIO_19_SPIA_STE                0x00080601U
#define GPIO_19_SCIB_RX                 0x00080602U
#define GPIO_19_CANA_TX                 0x00080603U
#define GPIO_19_EPWM6_B                 0x00080605U
#define GPIO_19_I2CA_SDA                0x00080606U

#define GPIO_20_GPIO20                  0x00080800U
#define GPIO_20_EQEP1_A                 0x00080801U
#define GPIO_20_CANA_TX                 0x00080803U
#define GPIO_20_SPIA_SIMO               0x00080806U
#define GPIO_20_I2CA_SCL                0x0008080BU
#define GPIO_20_SCIC_TX                 0x0008080FU

#define GPIO_21_GPIO21                  0x00080A00U
#define GPIO_21_EQEP1_B                 0x00080A01U
#define GPIO_21_CANA_RX                 0x00080A03U
#define GPIO_21_SPIA_SOMI               0x00080A06U
#define GPIO_21_I2CA_SDA                0x00080A0BU
#define GPIO_21_SCIC_RX                 0x00080A0FU

#define GPIO_22_GPIO22                  0x00080C00U
#define GPIO_22_EQEP1_STROBE            0x00080C01U
#define GPIO_22_SCIB_TX                 0x00080C03U
#define GPIO_22_SCIC_TX                 0x00080C09U
#define GPIO_22_EPWM4_A                 0x00080C0EU

#define GPIO_23_GPIO23                  0x00080E00U
#define GPIO_23_EQEP1_INDEX             0x00080E01U
#define GPIO_23_SCIB_RX                 0x00080E03U
#define GPIO_23_SCIC_RX                 0x00080E09U
#define GPIO_23_EPWM4_B                 0x00080E0EU

#define GPIO_24_GPIO24                  0x00081000U
#define GPIO_24_OUTPUTXBAR1             0x00081001U
#define GPIO_24_SPIA_STE                0x00081003U
#define GPIO_24_EPWM4_A                 0x00081005U
#define GPIO_24_SPIA_SIMO               0x00081006U
#define GPIO_24_SCIA_TX                 0x0008100BU
#define GPIO_24_ERRORSTS                0x0008100DU

#define GPIO_28_GPIO28                  0x00081800U
#define GPIO_28_SCIA_RX                 0x00081801U
#define GPIO_28_EPWM7_A                 0x00081803U
#define GPIO_28_OUTPUTXBAR5             0x00081805U
#define GPIO_28_EQEP1_A                 0x00081806U
#define GPIO_28_SCIC_TX                 0x0008180AU
#define GPIO_28_SPIA_CLK                0x0008180BU
#define GPIO_28_ERRORSTS                0x0008180DU
#define GPIO_28_I2CB_SDA                0x0008180EU

#define GPIO_29_GPIO29                  0x00081A00U
#define GPIO_29_SCIA_TX                 0x00081A01U
#define GPIO_29_EPWM7_B                 0x00081A03U
#define GPIO_29_OUTPUTXBAR6             0x00081A05U
#define GPIO_29_EQEP1_B                 0x00081A06U
#define GPIO_29_SCIC_RX                 0x00081A0AU
#define GPIO_29_SPIA_STE                0x00081A0BU
#define GPIO_29_ERRORSTS                0x00081A0DU
#define GPIO_29_I2CB_SCL                0x00081A0EU

#define GPIO_32_GPIO32                  0x00460000U
#define GPIO_32_I2CA_SDA                0x00460001U
#define GPIO_32_EQEP1_INDEX             0x00460002U
#define GPIO_32_SPIA_CLK                0x00460003U
#define GPIO_32_EPWM4_B                 0x00460005U
#define GPIO_32_SCIC_TX                 0x00460006U
#define GPIO_32_CANA_TX                 0x0046000AU
#define GPIO_32_ADCSOCBO                0x0046000DU

#define GPIO_33_GPIO33                  0x00460200U
#define GPIO_33_I2CA_SCL                0x00460201U
#define GPIO_33_OUTPUTXBAR4             0x00460205U
#define GPIO_33_SCIC_RX                 0x00460206U
#define GPIO_33_CANA_RX                 0x0046020AU
#define GPIO_33_ADCSOCAO                0x0046020DU

#define GPIO_35_GPIO35                  0x00460600U
#define GPIO_35_SCIA_RX                 0x00460601U
#define GPIO_35_SPIA_SOMI               0x00460602U
#define GPIO_35_I2CA_SDA                0x00460603U
#define GPIO_35_CANA_RX                 0x00460605U
#define GPIO_35_SCIC_RX                 0x00460607U
#define GPIO_35_EQEP1_A                 0x00460609U
#define GPIO_35_EPWM5_B                 0x0046060BU
#define GPIO_35_TDI                     0x0046060FU

#define GPIO_37_GPIO37                  0x00460A00U
#define GPIO_37_OUTPUTXBAR2             0x00460A01U
#define GPIO_37_SPIA_STE                0x00460A02U
#define GPIO_37_I2CA_SCL                0x00460A03U
#define GPIO_37_SCIA_TX                 0x00460A05U
#define GPIO_37_CANA_TX                 0x00460A06U
#define GPIO_37_SCIC_TX                 0x00460A07U
#define GPIO_37_EQEP1_B                 0x00460A09U
#define GPIO_37_EPWM5_A                 0x00460A0BU
#define GPIO_37_TDO                     0x00460A0FU

#define GPIO_39_GPIO39                  0x00460E00U
#define GPIO_39_SYNCOUT                 0x00460E0DU
#define GPIO_39_EQEP1_INDEX             0x00460E0EU

#define GPIO_40_GPIO40                  0x00461000U
#define GPIO_40_EPWM2_B                 0x00461005U
#define GPIO_40_SCIB_TX                 0x00461009U
#define GPIO_40_EQEP1_A                 0x0046100AU

#define GPIO_41_GPIO41                  0x00461200U
#define GPIO_41_EPWM7_A                 0x00461201U
#define GPIO_41_EPWM2_A                 0x00461205U
#define GPIO_41_SCIB_RX                 0x00461209U
#define GPIO_41_EQEP1_B                 0x0046120AU

#define GPIO_224_GPIO224                0x01C60000U
#define GPIO_224_OUTPUTXBAR3            0x01C60005U
#define GPIO_224_SPIA_SIMO              0x01C60006U
#define GPIO_224_EPWM1_A                0x01C60009U
#define GPIO_224_CANA_TX                0x01C6000AU
#define GPIO_224_EQEP1_A                0x01C6000BU
#define GPIO_224_SCIC_TX                0x01C6000EU

#define GPIO_225_GPIO225                0x01C60200U

#define GPIO_226_GPIO226                0x01C60400U
#define GPIO_226_EPWM6_A                0x01C60405U
#define GPIO_226_SPIA_CLK               0x01C60406U
#define GPIO_226_EPWM1_B                0x01C60409U
#define GPIO_226_EQEP1_STROBE           0x01C6040BU
#define GPIO_226_SCIC_RX                0x01C6040EU

#define GPIO_227_GPIO227                0x01C60600U
#define GPIO_227_I2CB_SCL               0x01C60601U
#define GPIO_227_EPWM3_A                0x01C60603U
#define GPIO_227_OUTPUTXBAR1            0x01C60605U
#define GPIO_227_EPWM2_B                0x01C60606U

#define GPIO_228_GPIO228                0x01C60800U
#define GPIO_228_ADCSOCAO               0x01C60803U
#define GPIO_228_CANA_TX                0x01C60805U
#define GPIO_228_SPIA_SOMI              0x01C60806U
#define GPIO_228_EPWM2_B                0x01C60809U
#define GPIO_228_EQEP1_B                0x01C6080BU

#define GPIO_230_GPIO230                0x01C60C00U
#define GPIO_230_I2CB_SDA               0x01C60C01U
#define GPIO_230_EPWM3_B                0x01C60C03U
#define GPIO_230_CANA_RX                0x01C60C05U
#define GPIO_230_EPWM2_A                0x01C60C06U
#define GPIO_230_I2CA_SDA               0x01C60C07U

#define GPIO_231_GPIO231                0x01C60E00U

#define GPIO_232_GPIO232                0x01C61000U

#define GPIO_233_GPIO233                0x01C61200U

#define GPIO_237_GPIO237                0x01C61A00U

#define GPIO_238_GPIO238                0x01C61C00U

#define GPIO_239_GPIO239                0x01C61E00U

#define GPIO_241_GPIO241                0x01C80200U

#define GPIO_242_GPIO242                0x01C80400U
#define GPIO_242_OUTPUTXBAR2            0x01C80405U
#define GPIO_242_SPIA_STE               0x01C80406U
#define GPIO_242_EPWM4_A                0x01C80409U
#define GPIO_242_CANA_RX                0x01C8040AU
#define GPIO_242_EQEP1_INDEX            0x01C8040BU

#define GPIO_244_GPIO244                0x01C80800U

#define GPIO_245_GPIO245                0x01C80A00U

#endif // PIN_MAP_H
