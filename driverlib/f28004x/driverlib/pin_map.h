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
#define GPIO_0_I2CA_SDA                 0x00060006U

#define GPIO_1_GPIO1                    0x00060200U
#define GPIO_1_EPWM1_B                  0x00060201U
#define GPIO_1_I2CA_SCL                 0x00060206U

#define GPIO_2_GPIO2                    0x00060400U
#define GPIO_2_EPWM2_A                  0x00060401U
#define GPIO_2_OUTPUTXBAR1              0x00060405U
#define GPIO_2_PMBUSA_SDA               0x00060406U
#define GPIO_2_SCIA_TX                  0x00060409U
#define GPIO_2_FSIRXA_D1                0x0006040AU

#define GPIO_3_GPIO3                    0x00060600U
#define GPIO_3_EPWM2_B                  0x00060601U
#define GPIO_3_OUTPUTXBAR2              0x00060602U
#define GPIO_3_PMBUSA_SCL               0x00060606U
#define GPIO_3_SPIA_CLK                 0x00060607U
#define GPIO_3_SCIA_RX                  0x00060609U
#define GPIO_3_FSIRXA_D0                0x0006060AU

#define GPIO_4_GPIO4                    0x00060800U
#define GPIO_4_EPWM3_A                  0x00060801U
#define GPIO_4_OUTPUTXBAR3              0x00060805U
#define GPIO_4_CANA_TX                  0x00060806U
#define GPIO_4_FSIRXA_CLK               0x0006080AU

#define GPIO_5_GPIO5                    0x00060A00U
#define GPIO_5_EPWM3_B                  0x00060A01U
#define GPIO_5_OUTPUTXBAR3              0x00060A03U
#define GPIO_5_CANA_RX                  0x00060A06U
#define GPIO_5_SPIA_STE                 0x00060A07U
#define GPIO_5_FSITXA_D1                0x00060A09U

#define GPIO_6_GPIO6                    0x00060C00U
#define GPIO_6_EPWM4_A                  0x00060C01U
#define GPIO_6_OUTPUTXBAR4              0x00060C02U
#define GPIO_6_SYNCOUT                  0x00060C03U
#define GPIO_6_EQEP1_A                  0x00060C05U
#define GPIO_6_CANB_TX                  0x00060C06U
#define GPIO_6_SPIB_SOMI                0x00060C07U
#define GPIO_6_FSITXA_D0                0x00060C09U

#define GPIO_7_GPIO7                    0x00060E00U
#define GPIO_7_EPWM4_B                  0x00060E01U
#define GPIO_7_OUTPUTXBAR5              0x00060E03U
#define GPIO_7_EQEP1_B                  0x00060E05U
#define GPIO_7_CANB_RX                  0x00060E06U
#define GPIO_7_SPIB_SIMO                0x00060E07U
#define GPIO_7_FSITXA_CLK               0x00060E09U

#define GPIO_8_GPIO8                    0x00061000U
#define GPIO_8_EPWM5_A                  0x00061001U
#define GPIO_8_CANB_TX                  0x00061002U
#define GPIO_8_ADCSOCAO                 0x00061003U
#define GPIO_8_EQEP1_STROBE             0x00061005U
#define GPIO_8_SCIA_TX                  0x00061006U
#define GPIO_8_SPIA_SIMO                0x00061007U
#define GPIO_8_I2CA_SCL                 0x00061009U
#define GPIO_8_FSITXA_D1                0x0006100AU

#define GPIO_9_GPIO9                    0x00061200U
#define GPIO_9_EPWM5_B                  0x00061201U
#define GPIO_9_SCIB_TX                  0x00061202U
#define GPIO_9_OUTPUTXBAR6              0x00061203U
#define GPIO_9_EQEP1_INDEX              0x00061205U
#define GPIO_9_SCIA_RX                  0x00061206U
#define GPIO_9_SPIA_CLK                 0x00061207U
#define GPIO_9_FSITXA_D0                0x0006120AU

#define GPIO_10_GPIO10                  0x00061400U
#define GPIO_10_EPWM6_A                 0x00061401U
#define GPIO_10_CANB_RX                 0x00061402U
#define GPIO_10_ADCSOCBO                0x00061403U
#define GPIO_10_EQEP1_A                 0x00061405U
#define GPIO_10_SCIB_TX                 0x00061406U
#define GPIO_10_SPIA_SOMI               0x00061407U
#define GPIO_10_I2CA_SDA                0x00061409U
#define GPIO_10_FSITXA_CLK              0x0006140AU

#define GPIO_11_GPIO11                  0x00061600U
#define GPIO_11_EPWM6_B                 0x00061601U
#define GPIO_11_SCIB_RX                 0x00061602U
#define GPIO_11_OUTPUTXBAR7             0x00061603U
#define GPIO_11_EQEP1_B                 0x00061605U
#define GPIO_11_SPIA_STE                0x00061607U
#define GPIO_11_FSIRXA_D1               0x00061609U

#define GPIO_12_GPIO12                  0x00061800U
#define GPIO_12_EPWM7_A                 0x00061801U
#define GPIO_12_CANB_TX                 0x00061802U
#define GPIO_12_EQEP1_STROBE            0x00061805U
#define GPIO_12_SCIB_TX                 0x00061806U
#define GPIO_12_PMBUSA_CTL              0x00061807U
#define GPIO_12_FSIRXA_D0               0x00061809U

#define GPIO_13_GPIO13                  0x00061A00U
#define GPIO_13_EPWM7_B                 0x00061A01U
#define GPIO_13_CANB_RX                 0x00061A02U
#define GPIO_13_EQEP1_INDEX             0x00061A05U
#define GPIO_13_SCIB_RX                 0x00061A06U
#define GPIO_13_PMBUSA_ALERT            0x00061A07U
#define GPIO_13_FSIRXA_CLK              0x00061A09U

#define GPIO_14_GPIO14                  0x00061C00U
#define GPIO_14_EPWM8_A                 0x00061C01U
#define GPIO_14_SCIB_TX                 0x00061C02U
#define GPIO_14_OUTPUTXBAR3             0x00061C06U
#define GPIO_14_PMBUSA_SDA              0x00061C07U
#define GPIO_14_SPIB_CLK                0x00061C09U
#define GPIO_14_EQEP2_A                 0x00061C0AU

#define GPIO_15_GPIO15                  0x00061E00U
#define GPIO_15_EPWM8_B                 0x00061E01U
#define GPIO_15_SCIB_RX                 0x00061E02U
#define GPIO_15_OUTPUTXBAR4             0x00061E06U
#define GPIO_15_PMBUSA_SCL              0x00061E07U
#define GPIO_15_SPIB_STE                0x00061E09U
#define GPIO_15_EQEP2_B                 0x00061E0AU

#define GPIO_16_GPIO16                  0x00080000U
#define GPIO_16_SPIA_SIMO               0x00080001U
#define GPIO_16_CANB_TX                 0x00080002U
#define GPIO_16_OUTPUTXBAR7             0x00080003U
#define GPIO_16_EPWM5_A                 0x00080005U
#define GPIO_16_SCIA_TX                 0x00080006U
#define GPIO_16_SD1_D1                  0x00080007U
#define GPIO_16_EQEP1_STROBE            0x00080009U
#define GPIO_16_PMBUSA_SCL              0x0008000AU
#define GPIO_16_XCLKOUT                 0x0008000BU

#define GPIO_17_GPIO17                  0x00080200U
#define GPIO_17_SPIA_SOMI               0x00080201U
#define GPIO_17_CANB_RX                 0x00080202U
#define GPIO_17_OUTPUTXBAR8             0x00080203U
#define GPIO_17_EPWM5_B                 0x00080205U
#define GPIO_17_SCIA_RX                 0x00080206U
#define GPIO_17_SD1_C1                  0x00080207U
#define GPIO_17_EQEP1_INDEX             0x00080209U
#define GPIO_17_PMBUSA_SDA              0x0008020AU

#define GPIO_18_GPIO18_X2               0x00080400U
#define GPIO_18_SPIA_CLK                0x00080401U
#define GPIO_18_SCIB_TX                 0x00080402U
#define GPIO_18_CANA_RX                 0x00080403U
#define GPIO_18_EPWM6_A                 0x00080405U
#define GPIO_18_I2CA_SCL                0x00080406U
#define GPIO_18_SD1_D2                  0x00080407U
#define GPIO_18_EQEP2_A                 0x00080409U
#define GPIO_18_PMBUSA_CTL              0x0008040AU
#define GPIO_18_XCLKOUT                 0x0008040BU

#define GPIO_20_GPIO20                  0x00080800U

#define GPIO_21_GPIO21                  0x00080A00U

#define GPIO_22_GPIO22_VFBSW            0x00080C00U
#define GPIO_22_EQEP1_STROBE            0x00080C01U
#define GPIO_22_SCIB_TX                 0x00080C03U
#define GPIO_22_SPIB_CLK                0x00080C06U
#define GPIO_22_SD1_D4                  0x00080C07U
#define GPIO_22_LINA_TX                 0x00080C09U

#define GPIO_23_GPIO23_VSW              0x00080E00U
#define GPIO_23_GPIO23                  0x00080E04U

#define GPIO_24_GPIO24                  0x00081000U
#define GPIO_24_OUTPUTXBAR1             0x00081001U
#define GPIO_24_EQEP2_A                 0x00081002U
#define GPIO_24_EPWM8_A                 0x00081005U
#define GPIO_24_SPIB_SIMO               0x00081006U
#define GPIO_24_SD1_D1                  0x00081007U
#define GPIO_24_PMBUSA_SCL              0x0008100AU
#define GPIO_24_SCIA_TX                 0x0008100BU
#define GPIO_24_ERRORSTS                0x0008100DU

#define GPIO_25_GPIO25                  0x00081200U
#define GPIO_25_OUTPUTXBAR2             0x00081201U
#define GPIO_25_EQEP2_B                 0x00081202U
#define GPIO_25_SPIB_SOMI               0x00081206U
#define GPIO_25_SD1_C1                  0x00081207U
#define GPIO_25_FSITXA_D1               0x00081209U
#define GPIO_25_PMBUSA_SDA              0x0008120AU
#define GPIO_25_SCIA_RX                 0x0008120BU

#define GPIO_26_GPIO26                  0x00081400U
#define GPIO_26_OUTPUTXBAR3             0x00081401U
#define GPIO_26_EQEP2_INDEX             0x00081402U
#define GPIO_26_SPIB_CLK                0x00081406U
#define GPIO_26_SD1_D2                  0x00081407U
#define GPIO_26_FSITXA_D0               0x00081409U
#define GPIO_26_PMBUSA_CTL              0x0008140AU
#define GPIO_26_I2CA_SDA                0x0008140BU

#define GPIO_27_GPIO27                  0x00081600U
#define GPIO_27_OUTPUTXBAR4             0x00081601U
#define GPIO_27_EQEP2_STROBE            0x00081602U
#define GPIO_27_SPIB_STE                0x00081606U
#define GPIO_27_SD1_C2                  0x00081607U
#define GPIO_27_FSITXA_CLK              0x00081609U
#define GPIO_27_PMBUSA_ALERT            0x0008160AU
#define GPIO_27_I2CA_SCL                0x0008160BU

#define GPIO_28_GPIO28                  0x00081800U
#define GPIO_28_SCIA_RX                 0x00081801U
#define GPIO_28_EPWM7_A                 0x00081803U
#define GPIO_28_OUTPUTXBAR5             0x00081805U
#define GPIO_28_EQEP1_A                 0x00081806U
#define GPIO_28_SD1_D3                  0x00081807U
#define GPIO_28_EQEP2_STROBE            0x00081809U
#define GPIO_28_LINA_TX                 0x0008180AU
#define GPIO_28_SPIB_CLK                0x0008180BU
#define GPIO_28_ERRORSTS                0x0008180DU

#define GPIO_29_GPIO29                  0x00081A00U
#define GPIO_29_SCIA_TX                 0x00081A01U
#define GPIO_29_EPWM7_B                 0x00081A03U
#define GPIO_29_OUTPUTXBAR6             0x00081A05U
#define GPIO_29_EQEP1_B                 0x00081A06U
#define GPIO_29_SD1_C3                  0x00081A07U
#define GPIO_29_EQEP2_INDEX             0x00081A09U
#define GPIO_29_LINA_RX                 0x00081A0AU
#define GPIO_29_SPIB_STE                0x00081A0BU
#define GPIO_29_ERRORSTS                0x00081A0DU

#define GPIO_30_GPIO30                  0x00081C00U
#define GPIO_30_CANA_RX                 0x00081C01U
#define GPIO_30_SPIB_SIMO               0x00081C03U
#define GPIO_30_OUTPUTXBAR7             0x00081C05U
#define GPIO_30_EQEP1_STROBE            0x00081C06U
#define GPIO_30_SD1_D4                  0x00081C07U

#define GPIO_31_GPIO31                  0x00081E00U
#define GPIO_31_CANA_TX                 0x00081E01U
#define GPIO_31_SPIB_SOMI               0x00081E03U
#define GPIO_31_OUTPUTXBAR8             0x00081E05U
#define GPIO_31_EQEP1_INDEX             0x00081E06U
#define GPIO_31_SD1_C4                  0x00081E07U
#define GPIO_31_FSIRXA_D1               0x00081E09U

#define GPIO_32_GPIO32                  0x00460000U
#define GPIO_32_I2CA_SDA                0x00460001U
#define GPIO_32_SPIB_CLK                0x00460003U
#define GPIO_32_EPWM8_B                 0x00460005U
#define GPIO_32_LINA_TX                 0x00460006U
#define GPIO_32_SD1_D3                  0x00460007U
#define GPIO_32_FSIRXA_D0               0x00460009U
#define GPIO_32_CANA_TX                 0x0046000AU

#define GPIO_33_GPIO33                  0x00460200U
#define GPIO_33_I2CA_SCL                0x00460201U
#define GPIO_33_SPIB_STE                0x00460203U
#define GPIO_33_OUTPUTXBAR4             0x00460205U
#define GPIO_33_LINA_RX                 0x00460206U
#define GPIO_33_SD1_C3                  0x00460207U
#define GPIO_33_FSIRXA_CLK              0x00460209U
#define GPIO_33_CANA_RX                 0x0046020AU

#define GPIO_34_GPIO34                  0x00460400U
#define GPIO_34_OUTPUTXBAR1             0x00460401U
#define GPIO_34_PMBUSA_SDA              0x00460406U

#define GPIO_35_GPIO35                  0x00460600U
#define GPIO_35_SCIA_RX                 0x00460601U
#define GPIO_35_I2CA_SDA                0x00460603U
#define GPIO_35_CANA_RX                 0x00460605U
#define GPIO_35_PMBUSA_SCL              0x00460606U
#define GPIO_35_LINA_RX                 0x00460607U
#define GPIO_35_EQEP1_A                 0x00460609U
#define GPIO_35_PMBUSA_CTL              0x0046060AU
#define GPIO_35_TDI                     0x0046060FU

#define GPIO_37_GPIO37                  0x00460A00U
#define GPIO_37_OUTPUTXBAR2             0x00460A01U
#define GPIO_37_I2CA_SCL                0x00460A03U
#define GPIO_37_SCIA_TX                 0x00460A05U
#define GPIO_37_CANA_TX                 0x00460A06U
#define GPIO_37_LINA_TX                 0x00460A07U
#define GPIO_37_EQEP1_B                 0x00460A09U
#define GPIO_37_PMBUSA_ALERT            0x00460A0AU
#define GPIO_37_TDO                     0x00460A0FU

#define GPIO_39_GPIO39                  0x00460E00U
#define GPIO_39_CANB_RX                 0x00460E06U
#define GPIO_39_FSIRXA_CLK              0x00460E07U

#define GPIO_40_GPIO40                  0x00461000U
#define GPIO_40_PMBUSA_SDA              0x00461006U
#define GPIO_40_FSIRXA_D0               0x00461007U
#define GPIO_40_SCIB_TX                 0x00461009U
#define GPIO_40_EQEP1_A                 0x0046100AU

#define GPIO_41_GPIO41                  0x00461200U

#define GPIO_42_GPIO42                  0x00461400U

#define GPIO_43_GPIO43                  0x00461600U

#define GPIO_44_GPIO44                  0x00461800U

#define GPIO_45_GPIO45                  0x00461A00U

#define GPIO_46_GPIO46                  0x00461C00U

#define GPIO_47_GPIO47                  0x00461E00U

#define GPIO_48_GPIO48                  0x00480000U

#define GPIO_49_GPIO49                  0x00480200U

#define GPIO_50_GPIO50                  0x00480400U

#define GPIO_51_GPIO51                  0x00480600U

#define GPIO_52_GPIO52                  0x00480800U

#define GPIO_53_GPIO53                  0x00480A00U

#define GPIO_54_GPIO54                  0x00480C00U

#define GPIO_55_GPIO55                  0x00480E00U

#define GPIO_56_GPIO56                  0x00481000U
#define GPIO_56_SPIA_CLK                0x00481001U
#define GPIO_56_EQEP2_STROBE            0x00481005U
#define GPIO_56_SCIB_TX                 0x00481006U
#define GPIO_56_SD1_D3                  0x00481007U
#define GPIO_56_SPIB_SIMO               0x00481009U
#define GPIO_56_EQEP1_A                 0x0048100BU

#define GPIO_57_GPIO57                  0x00481200U
#define GPIO_57_SPIA_STE                0x00481201U
#define GPIO_57_EQEP2_INDEX             0x00481205U
#define GPIO_57_SCIB_RX                 0x00481206U
#define GPIO_57_SD1_C3                  0x00481207U
#define GPIO_57_SPIB_SOMI               0x00481209U
#define GPIO_57_EQEP1_B                 0x0048120BU

#define GPIO_58_GPIO58                  0x00481400U
#define GPIO_58_OUTPUTXBAR1             0x00481405U
#define GPIO_58_SPIB_CLK                0x00481406U
#define GPIO_58_SD1_D4                  0x00481407U
#define GPIO_58_LINA_TX                 0x00481409U
#define GPIO_58_CANB_TX                 0x0048140AU
#define GPIO_58_EQEP1_STROBE            0x0048140BU

#define GPIO_59_GPIO59                  0x00481600U
#define GPIO_59_OUTPUTXBAR2             0x00481605U
#define GPIO_59_SPIB_STE                0x00481606U
#define GPIO_59_SD1_C4                  0x00481607U
#define GPIO_59_LINA_RX                 0x00481609U
#define GPIO_59_CANB_RX                 0x0048160AU
#define GPIO_59_EQEP1_INDEX             0x0048160BU

#define GPIO_247_GPIO247                0x01C80E00U

#define GPIO_246_GPIO246                0x01C80C00U

#define GPIO_230_GPIO230                0x01C60C00U

#define GPIO_241_GPIO241                0x01C80200U

#define GPIO_242_GPIO242                0x01C80400U

#define GPIO_237_GPIO237                0x01C61A00U

#define GPIO_224_GPIO224                0x01C60000U

#define GPIO_244_GPIO244                0x01C80800U

#define GPIO_226_GPIO226                0x01C60400U

#define GPIO_233_GPIO233                0x01C61200U

#define GPIO_239_GPIO239                0x01C61E00U

#define GPIO_228_GPIO228                0x01C60800U

#define GPIO_232_GPIO232                0x01C61000U

#define GPIO_231_GPIO231                0x01C60E00U

#define GPIO_227_GPIO227                0x01C60600U

#define GPIO_245_GPIO245                0x01C80A00U

#define GPIO_235_GPIO235                0x01C61600U

#define GPIO_236_GPIO236                0x01C61800U

#define GPIO_234_GPIO234                0x01C61400U

#define GPIO_243_GPIO243                0x01C80600U

#define GPIO_225_GPIO225                0x01C60200U

#define GPIO_238_GPIO238                0x01C61C00U

#define GPIO_229_GPIO229                0x01C60A00U

#define GPIO_240_GPIO240                0x01C80000U

#endif // PIN_MAP_H
