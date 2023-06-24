//###########################################################################
//
// FILE:   pin_map.h
//
// TITLE:  Definitions of pin mux info for gpio.c.
//
//###########################################################################
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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
#define GPIO_0_EPWM1A                   0x00060001U
#define GPIO_0_SDAA                     0x00060006U

#define GPIO_1_GPIO1                    0x00060200U
#define GPIO_1_EPWM1B                   0x00060201U
#define GPIO_1_MFSRB                    0x00060203U
#define GPIO_1_SCLA                     0x00060206U

#define GPIO_2_GPIO2                    0x00060400U
#define GPIO_2_EPWM2A                   0x00060401U
#define GPIO_2_OUTPUTXBAR1              0x00060405U
#define GPIO_2_SDAB                     0x00060406U

#define GPIO_3_GPIO3                    0x00060600U
#define GPIO_3_EPWM2B                   0x00060601U
#define GPIO_3_OUTPUTXBAR2              0x00060602U
#define GPIO_3_MCLKRB                   0x00060603U
#define GPIO_3_SCLB                     0x00060606U

#define GPIO_4_GPIO4                    0x00060800U
#define GPIO_4_EPWM3A                   0x00060801U
#define GPIO_4_OUTPUTXBAR3              0x00060805U
#define GPIO_4_CANTXA                   0x00060806U

#define GPIO_5_GPIO5                    0x00060A00U
#define GPIO_5_EPWM3B                   0x00060A01U
#define GPIO_5_MFSRA                    0x00060A02U
#define GPIO_5_OUTPUTXBAR3              0x00060A03U
#define GPIO_5_CANRXA                   0x00060A06U

#define GPIO_6_GPIO6                    0x00060C00U
#define GPIO_6_EPWM4A                   0x00060C01U
#define GPIO_6_OUTPUTXBAR4              0x00060C02U
#define GPIO_6_EPWMSYNCO                0x00060C03U
#define GPIO_6_EQEP3A                   0x00060C05U
#define GPIO_6_CANTXB                   0x00060C06U

#define GPIO_7_GPIO7                    0x00060E00U
#define GPIO_7_EPWM4B                   0x00060E01U
#define GPIO_7_MCLKRA                   0x00060E02U
#define GPIO_7_OUTPUTXBAR5              0x00060E03U
#define GPIO_7_EQEP3B                   0x00060E05U
#define GPIO_7_CANRXB                   0x00060E06U

#define GPIO_8_GPIO8                    0x00061000U
#define GPIO_8_EPWM5A                   0x00061001U
#define GPIO_8_CANTXB                   0x00061002U
#define GPIO_8_ADCSOCAO                 0x00061003U
#define GPIO_8_EQEP3S                   0x00061005U
#define GPIO_8_SCITXDA                  0x00061006U

#define GPIO_9_GPIO9                    0x00061200U
#define GPIO_9_EPWM5B                   0x00061201U
#define GPIO_9_SCITXDB                  0x00061202U
#define GPIO_9_OUTPUTXBAR6              0x00061203U
#define GPIO_9_EQEP3I                   0x00061205U
#define GPIO_9_SCIRXDA                  0x00061206U

#define GPIO_10_GPIO10                  0x00061400U
#define GPIO_10_EPWM6A                  0x00061401U
#define GPIO_10_CANRXB                  0x00061402U
#define GPIO_10_ADCSOCBO                0x00061403U
#define GPIO_10_EQEP1A                  0x00061405U
#define GPIO_10_SCITXDB                 0x00061406U

#define GPIO_11_GPIO11                  0x00061600U
#define GPIO_11_EPWM6B                  0x00061601U
#define GPIO_11_SCIRXDB                 0x00061602U
#define GPIO_11_OUTPUTXBAR7             0x00061603U
#define GPIO_11_EQEP1B                  0x00061605U

#define GPIO_12_GPIO12                  0x00061800U
#define GPIO_12_EPWM7A                  0x00061801U
#define GPIO_12_CANTXB                  0x00061802U
#define GPIO_12_MDXB                    0x00061803U
#define GPIO_12_EQEP1S                  0x00061805U
#define GPIO_12_SCITXDC                 0x00061806U

#define GPIO_13_GPIO13                  0x00061A00U
#define GPIO_13_EPWM7B                  0x00061A01U
#define GPIO_13_CANRXB                  0x00061A02U
#define GPIO_13_MDRB                    0x00061A03U
#define GPIO_13_EQEP1I                  0x00061A05U
#define GPIO_13_SCIRXDC                 0x00061A06U

#define GPIO_14_GPIO14                  0x00061C00U
#define GPIO_14_EPWM8A                  0x00061C01U
#define GPIO_14_SCITXDB                 0x00061C02U
#define GPIO_14_MCLKXB                  0x00061C03U
#define GPIO_14_OUTPUTXBAR3             0x00061C06U

#define GPIO_15_GPIO15                  0x00061E00U
#define GPIO_15_EPWM8B                  0x00061E01U
#define GPIO_15_SCIRXDB                 0x00061E02U
#define GPIO_15_MFSXB                   0x00061E03U
#define GPIO_15_OUTPUTXBAR4             0x00061E06U

#define GPIO_16_GPIO16                  0x00080000U
#define GPIO_16_SPISIMOA                0x00080001U
#define GPIO_16_CANTXB                  0x00080002U
#define GPIO_16_OUTPUTXBAR7             0x00080003U
#define GPIO_16_EPWM9A                  0x00080005U
#define GPIO_16_SD1_D1                  0x00080007U

#define GPIO_17_GPIO17                  0x00080200U
#define GPIO_17_SPISOMIA                0x00080201U
#define GPIO_17_CANRXB                  0x00080202U
#define GPIO_17_OUTPUTXBAR8             0x00080203U
#define GPIO_17_EPWM9B                  0x00080205U
#define GPIO_17_SD1_C1                  0x00080207U

#define GPIO_18_GPIO18                  0x00080400U
#define GPIO_18_SPICLKA                 0x00080401U
#define GPIO_18_SCITXDB                 0x00080402U
#define GPIO_18_CANRXA                  0x00080403U
#define GPIO_18_EPWM10A                 0x00080405U
#define GPIO_18_SD1_D2                  0x00080407U

#define GPIO_19_GPIO19                  0x00080600U
#define GPIO_19_SPISTEA                 0x00080601U
#define GPIO_19_SCIRXDB                 0x00080602U
#define GPIO_19_CANTXA                  0x00080603U
#define GPIO_19_EPWM10B                 0x00080605U
#define GPIO_19_SD1_C2                  0x00080607U

#define GPIO_20_GPIO20                  0x00080800U
#define GPIO_20_EQEP1A                  0x00080801U
#define GPIO_20_MDXA                    0x00080802U
#define GPIO_20_CANTXB                  0x00080803U
#define GPIO_20_EPWM11A                 0x00080805U
#define GPIO_20_SD1_D3                  0x00080807U

#define GPIO_21_GPIO21                  0x00080A00U
#define GPIO_21_EQEP1B                  0x00080A01U
#define GPIO_21_MDRA                    0x00080A02U
#define GPIO_21_CANRXB                  0x00080A03U
#define GPIO_21_EPWM11B                 0x00080A05U
#define GPIO_21_SD1_C3                  0x00080A07U

#define GPIO_22_GPIO22                  0x00080C00U
#define GPIO_22_EQEP1S                  0x00080C01U
#define GPIO_22_MCLKXA                  0x00080C02U
#define GPIO_22_SCITXDB                 0x00080C03U
#define GPIO_22_EPWM12A                 0x00080C05U
#define GPIO_22_SPICLKB                 0x00080C06U
#define GPIO_22_SD1_D4                  0x00080C07U

#define GPIO_23_GPIO23                  0x00080E00U
#define GPIO_23_EQEP1I                  0x00080E01U
#define GPIO_23_MFSXA                   0x00080E02U
#define GPIO_23_SCIRXDB                 0x00080E03U
#define GPIO_23_EPWM12B                 0x00080E05U
#define GPIO_23_SPISTEB                 0x00080E06U
#define GPIO_23_SD1_C4                  0x00080E07U

#define GPIO_24_GPIO24                  0x00081000U
#define GPIO_24_OUTPUTXBAR1             0x00081001U
#define GPIO_24_EQEP2A                  0x00081002U
#define GPIO_24_MDXB                    0x00081003U
#define GPIO_24_SPISIMOB                0x00081006U
#define GPIO_24_SD2_D1                  0x00081007U

#define GPIO_25_GPIO25                  0x00081200U
#define GPIO_25_OUTPUTXBAR2             0x00081201U
#define GPIO_25_EQEP2B                  0x00081202U
#define GPIO_25_MDRB                    0x00081203U
#define GPIO_25_SPISOMIB                0x00081206U
#define GPIO_25_SD2_C1                  0x00081207U

#define GPIO_26_GPIO26                  0x00081400U
#define GPIO_26_OUTPUTXBAR3             0x00081401U
#define GPIO_26_EQEP2I                  0x00081402U
#define GPIO_26_MCLKXB                  0x00081403U
#define GPIO_26_SPICLKB                 0x00081406U
#define GPIO_26_SD2_D2                  0x00081407U

#define GPIO_27_GPIO27                  0x00081600U
#define GPIO_27_OUTPUTXBAR4             0x00081601U
#define GPIO_27_EQEP2S                  0x00081602U
#define GPIO_27_MFSXB                   0x00081603U
#define GPIO_27_SPISTEB                 0x00081606U
#define GPIO_27_SD2_C2                  0x00081607U

#define GPIO_28_GPIO28                  0x00081800U
#define GPIO_28_SCIRXDA                 0x00081801U
#define GPIO_28_EM1CS4N                 0x00081802U
#define GPIO_28_OUTPUTXBAR5             0x00081805U
#define GPIO_28_EQEP3A                  0x00081806U
#define GPIO_28_SD2_D3                  0x00081807U

#define GPIO_29_GPIO29                  0x00081A00U
#define GPIO_29_SCITXDA                 0x00081A01U
#define GPIO_29_EM1SDCKE                0x00081A02U
#define GPIO_29_OUTPUTXBAR6             0x00081A05U
#define GPIO_29_EQEP3B                  0x00081A06U
#define GPIO_29_SD2_C3                  0x00081A07U

#define GPIO_30_GPIO30                  0x00081C00U
#define GPIO_30_CANRXA                  0x00081C01U
#define GPIO_30_EM1CLK                  0x00081C02U
#define GPIO_30_OUTPUTXBAR7             0x00081C05U
#define GPIO_30_EQEP3S                  0x00081C06U
#define GPIO_30_SD2_D4                  0x00081C07U

#define GPIO_31_GPIO31                  0x00081E00U
#define GPIO_31_CANTXA                  0x00081E01U
#define GPIO_31_EM1WEN                  0x00081E02U
#define GPIO_31_OUTPUTXBAR8             0x00081E05U
#define GPIO_31_EQEP3I                  0x00081E06U
#define GPIO_31_SD2_C4                  0x00081E07U

#define GPIO_32_GPIO32                  0x00460000U
#define GPIO_32_SDAA                    0x00460001U
#define GPIO_32_EM1CS0N                 0x00460002U

#define GPIO_33_GPIO33                  0x00460200U
#define GPIO_33_SCLA                    0x00460201U
#define GPIO_33_EM1RNW                  0x00460202U

#define GPIO_34_GPIO34                  0x00460400U
#define GPIO_34_OUTPUTXBAR1             0x00460401U
#define GPIO_34_EM1CS2N                 0x00460402U
#define GPIO_34_SDAB                    0x00460406U
#define GPIO_34_OFSD_2_N                0x0046040FU

#define GPIO_35_GPIO35                  0x00460600U
#define GPIO_35_SCIRXDA                 0x00460601U
#define GPIO_35_EM1CS3N                 0x00460602U
#define GPIO_35_SCLB                    0x00460606U
#define GPIO_35_IID                     0x0046060FU

#define GPIO_36_GPIO36                  0x00460800U
#define GPIO_36_SCITXDA                 0x00460801U
#define GPIO_36_EM1WAIT                 0x00460802U
#define GPIO_36_CANRXA                  0x00460806U
#define GPIO_36_ISESSEND                0x0046080FU

#define GPIO_37_GPIO37                  0x00460A00U
#define GPIO_37_OUTPUTXBAR2             0x00460A01U
#define GPIO_37_EM1OEN                  0x00460A02U
#define GPIO_37_CANTXA                  0x00460A06U
#define GPIO_37_IAVALID                 0x00460A0FU

#define GPIO_38_GPIO38                  0x00460C00U
#define GPIO_38_EM1A0                   0x00460C02U
#define GPIO_38_SCITXDC                 0x00460C05U
#define GPIO_38_CANTXB                  0x00460C06U

#define GPIO_39_GPIO39                  0x00460E00U
#define GPIO_39_EM1A1                   0x00460E02U
#define GPIO_39_SCIRXDC                 0x00460E05U
#define GPIO_39_CANRXB                  0x00460E06U

#define GPIO_40_GPIO40                  0x00461000U
#define GPIO_40_EM1A2                   0x00461002U
#define GPIO_40_SDAB                    0x00461006U

#define GPIO_41_GPIO41                  0x00461200U
#define GPIO_41_EM1A3                   0x00461202U
#define GPIO_41_EMU1                    0x00461203U
#define GPIO_41_SCLB                    0x00461206U

#define GPIO_42_GPIO42                  0x00461400U
#define GPIO_42_SDAA                    0x00461406U
#define GPIO_42_SCITXDA                 0x0046140FU

#define GPIO_43_GPIO43                  0x00461600U
#define GPIO_43_SCLA                    0x00461606U
#define GPIO_43_SCIRXDA                 0x0046160FU

#define GPIO_44_GPIO44                  0x00461800U
#define GPIO_44_EM1A4                   0x00461802U
#define GPIO_44_IXRCV                   0x0046180FU

#define GPIO_45_GPIO45                  0x00461A00U
#define GPIO_45_EM1A5                   0x00461A02U
#define GPIO_45_IDM                     0x00461A0FU

#define GPIO_46_GPIO46                  0x00461C00U
#define GPIO_46_EM1A6                   0x00461C02U
#define GPIO_46_SCIRXDD                 0x00461C06U
#define GPIO_46_IDP                     0x00461C0FU

#define GPIO_47_GPIO47                  0x00461E00U
#define GPIO_47_EM1A7                   0x00461E02U
#define GPIO_47_SCITXDD                 0x00461E06U
#define GPIO_47_OFSD_1_N                0x00461E0FU

#define GPIO_48_GPIO48                  0x00480000U
#define GPIO_48_OUTPUTXBAR3             0x00480001U
#define GPIO_48_EM1A8                   0x00480002U
#define GPIO_48_SCITXDA                 0x00480006U
#define GPIO_48_SD1_D1                  0x00480007U

#define GPIO_49_GPIO49                  0x00480200U
#define GPIO_49_OUTPUTXBAR4             0x00480201U
#define GPIO_49_EM1A9                   0x00480202U
#define GPIO_49_SCIRXDA                 0x00480206U
#define GPIO_49_SD1_C1                  0x00480207U

#define GPIO_50_GPIO50                  0x00480400U
#define GPIO_50_EQEP1A                  0x00480401U
#define GPIO_50_EM1A10                  0x00480402U
#define GPIO_50_SPISIMOC                0x00480406U
#define GPIO_50_SD1_D2                  0x00480407U

#define GPIO_51_GPIO51                  0x00480600U
#define GPIO_51_EQEP1B                  0x00480601U
#define GPIO_51_EM1A11                  0x00480602U
#define GPIO_51_SPISOMIC                0x00480606U
#define GPIO_51_SD1_C2                  0x00480607U

#define GPIO_52_GPIO52                  0x00480800U
#define GPIO_52_EQEP1S                  0x00480801U
#define GPIO_52_EM1A12                  0x00480802U
#define GPIO_52_SPICLKC                 0x00480806U
#define GPIO_52_SD1_D3                  0x00480807U

#define GPIO_53_GPIO53                  0x00480A00U
#define GPIO_53_EQEP1I                  0x00480A01U
#define GPIO_53_EM1D31                  0x00480A02U
#define GPIO_53_SPISTEC                 0x00480A06U
#define GPIO_53_SD1_C3                  0x00480A07U

#define GPIO_54_GPIO54                  0x00480C00U
#define GPIO_54_SPISIMOA                0x00480C01U
#define GPIO_54_EM1D30                  0x00480C02U
#define GPIO_54_EQEP2A                  0x00480C05U
#define GPIO_54_SCITXDB                 0x00480C06U
#define GPIO_54_SD1_D4                  0x00480C07U

#define GPIO_55_GPIO55                  0x00480E00U
#define GPIO_55_SPISOMIA                0x00480E01U
#define GPIO_55_EM1D29                  0x00480E02U
#define GPIO_55_EQEP2B                  0x00480E05U
#define GPIO_55_SCIRXDB                 0x00480E06U
#define GPIO_55_SD1_C4                  0x00480E07U

#define GPIO_56_GPIO56                  0x00481000U
#define GPIO_56_SPICLKA                 0x00481001U
#define GPIO_56_EM1D28                  0x00481002U
#define GPIO_56_EQEP2S                  0x00481005U
#define GPIO_56_SCITXDC                 0x00481006U
#define GPIO_56_SD2_D1                  0x00481007U

#define GPIO_57_GPIO57                  0x00481200U
#define GPIO_57_SPISTEA                 0x00481201U
#define GPIO_57_EM1D27                  0x00481202U
#define GPIO_57_EQEP2I                  0x00481205U
#define GPIO_57_SCIRXDC                 0x00481206U
#define GPIO_57_SD2_C1                  0x00481207U

#define GPIO_58_GPIO58                  0x00481400U
#define GPIO_58_MCLKRA                  0x00481401U
#define GPIO_58_EM1D26                  0x00481402U
#define GPIO_58_OUTPUTXBAR1             0x00481405U
#define GPIO_58_SPICLKB                 0x00481406U
#define GPIO_58_SD2_D2                  0x00481407U
#define GPIO_58_SPISIMOA                0x0048140FU

#define GPIO_59_GPIO59                  0x00481600U
#define GPIO_59_MFSRA                   0x00481601U
#define GPIO_59_EM1D25                  0x00481602U
#define GPIO_59_OUTPUTXBAR2             0x00481605U
#define GPIO_59_SPISTEB                 0x00481606U
#define GPIO_59_SD2_C2                  0x00481607U
#define GPIO_59_SPISOMIA                0x0048160FU

#define GPIO_60_GPIO60                  0x00481800U
#define GPIO_60_MCLKRB                  0x00481801U
#define GPIO_60_EM1D24                  0x00481802U
#define GPIO_60_OUTPUTXBAR3             0x00481805U
#define GPIO_60_SPISIMOB                0x00481806U
#define GPIO_60_SD2_D3                  0x00481807U
#define GPIO_60_SPICLKA                 0x0048180FU

#define GPIO_61_GPIO61                  0x00481A00U
#define GPIO_61_MFSRB                   0x00481A01U
#define GPIO_61_EM1D23                  0x00481A02U
#define GPIO_61_OUTPUTXBAR4             0x00481A05U
#define GPIO_61_SPISOMIB                0x00481A06U
#define GPIO_61_SD2_C3                  0x00481A07U
#define GPIO_61_SPISTEA                 0x00481A0FU

#define GPIO_62_GPIO62                  0x00481C00U
#define GPIO_62_SCIRXDC                 0x00481C01U
#define GPIO_62_EM1D22                  0x00481C02U
#define GPIO_62_EQEP3A                  0x00481C05U
#define GPIO_62_CANRXA                  0x00481C06U
#define GPIO_62_SD2_D4                  0x00481C07U

#define GPIO_63_GPIO63                  0x00481E00U
#define GPIO_63_SCITXDC                 0x00481E01U
#define GPIO_63_EM1D21                  0x00481E02U
#define GPIO_63_EQEP3B                  0x00481E05U
#define GPIO_63_CANTXA                  0x00481E06U
#define GPIO_63_SD2_C4                  0x00481E07U
#define GPIO_63_SPISIMOB                0x00481E0FU

#define GPIO_64_GPIO64                  0x00860000U
#define GPIO_64_EM1D20                  0x00860002U
#define GPIO_64_EQEP3S                  0x00860005U
#define GPIO_64_SCIRXDA                 0x00860006U
#define GPIO_64_SPISOMIB                0x0086000FU

#define GPIO_65_GPIO65                  0x00860200U
#define GPIO_65_EM1D19                  0x00860202U
#define GPIO_65_EQEP3I                  0x00860205U
#define GPIO_65_SCITXDA                 0x00860206U
#define GPIO_65_SPICLKB                 0x0086020FU

#define GPIO_66_GPIO66                  0x00860400U
#define GPIO_66_EM1D18                  0x00860402U
#define GPIO_66_SDAB                    0x00860406U
#define GPIO_66_SPISTEB                 0x0086040FU

#define GPIO_67_GPIO67                  0x00860600U
#define GPIO_67_EM1D17                  0x00860602U

#define GPIO_68_GPIO68                  0x00860800U
#define GPIO_68_EM1D16                  0x00860802U

#define GPIO_69_GPIO69                  0x00860A00U
#define GPIO_69_EM1D15                  0x00860A02U
#define GPIO_69_EMU0                    0x00860A03U
#define GPIO_69_SCLB                    0x00860A06U
#define GPIO_69_SPISIMOC                0x00860A0FU

#define GPIO_70_GPIO70                  0x00860C00U
#define GPIO_70_EM1D14                  0x00860C02U
#define GPIO_70_EMU0                    0x00860C03U
#define GPIO_70_CANRXA                  0x00860C05U
#define GPIO_70_SCITXDB                 0x00860C06U
#define GPIO_70_SPISOMIC                0x00860C0FU

#define GPIO_71_GPIO71                  0x00860E00U
#define GPIO_71_EM1D13                  0x00860E02U
#define GPIO_71_EMU1                    0x00860E03U
#define GPIO_71_CANTXA                  0x00860E05U
#define GPIO_71_SCIRXDB                 0x00860E06U
#define GPIO_71_SPICLKC                 0x00860E0FU

#define GPIO_72_GPIO72                  0x00861000U
#define GPIO_72_EM1D12                  0x00861002U
#define GPIO_72_CANTXB                  0x00861005U
#define GPIO_72_SCITXDC                 0x00861006U
#define GPIO_72_SPISTEC                 0x0086100FU

#define GPIO_73_GPIO73                  0x00861200U
#define GPIO_73_EM1D11                  0x00861202U
#define GPIO_73_XCLKOUT                 0x00861203U
#define GPIO_73_CANRXB                  0x00861205U
#define GPIO_73_SCIRXDC                 0x00861206U

#define GPIO_74_GPIO74                  0x00861400U
#define GPIO_74_EM1D10                  0x00861402U

#define GPIO_75_GPIO75                  0x00861600U
#define GPIO_75_EM1D9                   0x00861602U

#define GPIO_76_GPIO76                  0x00861800U
#define GPIO_76_EM1D8                   0x00861802U
#define GPIO_76_SCITXDD                 0x00861806U

#define GPIO_77_GPIO77                  0x00861A00U
#define GPIO_77_EM1D7                   0x00861A02U
#define GPIO_77_SCIRXDD                 0x00861A06U

#define GPIO_78_GPIO78                  0x00861C00U
#define GPIO_78_EM1D6                   0x00861C02U
#define GPIO_78_EQEP2A                  0x00861C06U

#define GPIO_79_GPIO79                  0x00861E00U
#define GPIO_79_EM1D5                   0x00861E02U
#define GPIO_79_EQEP2B                  0x00861E06U

#define GPIO_80_GPIO80                  0x00880000U
#define GPIO_80_EM1D4                   0x00880002U
#define GPIO_80_EQEP2S                  0x00880006U

#define GPIO_81_GPIO81                  0x00880200U
#define GPIO_81_EM1D3                   0x00880202U
#define GPIO_81_EQEP2I                  0x00880206U

#define GPIO_82_GPIO82                  0x00880400U
#define GPIO_82_EM1D2                   0x00880402U

#define GPIO_83_GPIO83                  0x00880600U
#define GPIO_83_EM1D1                   0x00880602U

#define GPIO_84_GPIO84                  0x00880800U
#define GPIO_84_SCITXDA                 0x00880805U
#define GPIO_84_MDXB                    0x00880806U
#define GPIO_84_MDXA                    0x0088080FU

#define GPIO_85_GPIO85                  0x00880A00U
#define GPIO_85_EM1D0                   0x00880A02U
#define GPIO_85_SCIRXDA                 0x00880A05U
#define GPIO_85_MDRB                    0x00880A06U
#define GPIO_85_MDRA                    0x00880A0FU

#define GPIO_86_GPIO86                  0x00880C00U
#define GPIO_86_EM1A13                  0x00880C02U
#define GPIO_86_EM1CAS                  0x00880C03U
#define GPIO_86_SCITXDB                 0x00880C05U
#define GPIO_86_MCLKXB                  0x00880C06U
#define GPIO_86_MCLKXA                  0x00880C0FU

#define GPIO_87_GPIO87                  0x00880E00U
#define GPIO_87_EM1A14                  0x00880E02U
#define GPIO_87_EM1RAS                  0x00880E03U
#define GPIO_87_SCIRXDB                 0x00880E05U
#define GPIO_87_MFSXB                   0x00880E06U
#define GPIO_87_MFSXA                   0x00880E0FU

#define GPIO_88_GPIO88                  0x00881000U
#define GPIO_88_EM1A15                  0x00881002U
#define GPIO_88_EM1DQM0                 0x00881003U

#define GPIO_89_GPIO89                  0x00881200U
#define GPIO_89_EM1A16                  0x00881202U
#define GPIO_89_EM1DQM1                 0x00881203U
#define GPIO_89_SCITXDC                 0x00881206U

#define GPIO_90_GPIO90                  0x00881400U
#define GPIO_90_EM1A17                  0x00881402U
#define GPIO_90_EM1DQM2                 0x00881403U
#define GPIO_90_SCIRXDC                 0x00881406U

#define GPIO_91_GPIO91                  0x00881600U
#define GPIO_91_EM1A18                  0x00881602U
#define GPIO_91_EM1DQM3                 0x00881603U
#define GPIO_91_SDAA                    0x00881606U

#define GPIO_92_GPIO92                  0x00881800U
#define GPIO_92_EM1A19                  0x00881802U
#define GPIO_92_EM1BA1                  0x00881803U
#define GPIO_92_SCLA                    0x00881806U

#define GPIO_93_GPIO93                  0x00881A00U
#define GPIO_93_EM1A20                  0x00881A02U
#define GPIO_93_EM1BA0                  0x00881A03U
#define GPIO_93_SCITXDD                 0x00881A06U

#define GPIO_94_GPIO94                  0x00881C00U
#define GPIO_94_EM1A21                  0x00881C02U
#define GPIO_94_SCIRXDD                 0x00881C06U

#define GPIO_99_GPIO99                  0x00C60600U
#define GPIO_99_EQEP1I                  0x00C60605U

#define GPIO_133_GPIO133                0x01060A00U
#define GPIO_133_SD2_C2                 0x01060A07U
#define GPIO_133_ODPDAT                 0x01060A0FU

#endif // PIN_MAP_H
