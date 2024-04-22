//###########################################################################
//
// FILE:    hw_gpio.h
//
// TITLE:   Definitions for the GPIO registers.
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

#ifndef HW_GPIO_H
#define HW_GPIO_H

//*************************************************************************************************
//
// The following are defines for the GPIO register offsets
//
//*************************************************************************************************
#define GPIO_O_GPACTRL    0x0U     // GPIO A Qualification Sampling Period Control (GPIO0 to 31)
#define GPIO_O_GPAQSEL1   0x2U     // GPIO A Qualifier Select 1 Register (GPIO0 to 15)
#define GPIO_O_GPAQSEL2   0x4U     // GPIO A Qualifier Select 2 Register (GPIO16 to 31)
#define GPIO_O_GPAMUX1    0x6U     // GPIO A Mux 1 Register (GPIO0 to 15)
#define GPIO_O_GPAMUX2    0x8U     // GPIO A Mux 2 Register (GPIO16 to 31)
#define GPIO_O_GPADIR     0xAU     // GPIO A Direction Register (GPIO0 to 31)
#define GPIO_O_GPAPUD     0xCU     // GPIO A Pull Up Disable Register (GPIO0 to 31)
#define GPIO_O_GPAINV     0x10U    // GPIO A Input Polarity Invert Registers (GPIO0 to 31)
#define GPIO_O_GPAODR     0x12U    // GPIO A Open Drain Output Register (GPIO0 to GPIO31)
#define GPIO_O_GPAAMSEL   0x14U    // GPIO A Analog Mode Select register (GPIO0 to GPIO31)
#define GPIO_O_GPAGMUX1   0x20U    // GPIO A Peripheral Group Mux (GPIO0 to 15)
#define GPIO_O_GPAGMUX2   0x22U    // GPIO A Peripheral Group Mux (GPIO16 to 31)
#define GPIO_O_GPACSEL1   0x28U    // GPIO A Core Select Register (GPIO0 to 7)
#define GPIO_O_GPACSEL2   0x2AU    // GPIO A Core Select Register (GPIO8 to 15)
#define GPIO_O_GPACSEL3   0x2CU    // GPIO A Core Select Register (GPIO16 to 23)
#define GPIO_O_GPACSEL4   0x2EU    // GPIO A Core Select Register (GPIO24 to 31)
#define GPIO_O_GPALOCK    0x3CU    // GPIO A Lock Configuration Register (GPIO0 to 31)
#define GPIO_O_GPACR      0x3EU    // GPIO A Lock Commit Register (GPIO0 to 31)
#define GPIO_O_GPBCTRL    0x40U    // GPIO B Qualification Sampling Period Control (GPIO32 to 63)
#define GPIO_O_GPBQSEL1   0x42U    // GPIO B Qualifier Select 1 Register (GPIO32 to 47)
#define GPIO_O_GPBQSEL2   0x44U    // GPIO B Qualifier Select 2 Register (GPIO48 to 63)
#define GPIO_O_GPBMUX1    0x46U    // GPIO B Mux 1 Register (GPIO32 to 47)
#define GPIO_O_GPBMUX2    0x48U    // GPIO B Mux 2 Register (GPIO48 to 63)
#define GPIO_O_GPBDIR     0x4AU    // GPIO B Direction Register (GPIO32 to 63)
#define GPIO_O_GPBPUD     0x4CU    // GPIO B Pull Up Disable Register (GPIO32 to 63)
#define GPIO_O_GPBINV     0x50U    // GPIO B Input Polarity Invert Registers (GPIO32 to 63)
#define GPIO_O_GPBODR     0x52U    // GPIO B Open Drain Output Register (GPIO32 to GPIO63)
#define GPIO_O_GPBAMSEL   0x54U    // GPIO B Analog Mode Select register (GPIO32 to GPIO63)
#define GPIO_O_GPBGMUX1   0x60U    // GPIO B Peripheral Group Mux (GPIO32 to 47)
#define GPIO_O_GPBGMUX2   0x62U    // GPIO B Peripheral Group Mux (GPIO48 to 63)
#define GPIO_O_GPBCSEL1   0x68U    // GPIO B Core Select Register (GPIO32 to 39)
#define GPIO_O_GPBCSEL2   0x6AU    // GPIO B Core Select Register (GPIO40 to 47)
#define GPIO_O_GPBCSEL3   0x6CU    // GPIO B Core Select Register (GPIO48 to 55)
#define GPIO_O_GPBCSEL4   0x6EU    // GPIO B Core Select Register (GPIO56 to 63)
#define GPIO_O_GPBLOCK    0x7CU    // GPIO B Lock Configuration Register (GPIO32 to 63)
#define GPIO_O_GPBCR      0x7EU    // GPIO B Lock Commit Register (GPIO32 to 63)
#define GPIO_O_GPCCTRL    0x80U    // GPIO C Qualification Sampling Period Control (GPIO64 to 95)
#define GPIO_O_GPCQSEL1   0x82U    // GPIO C Qualifier Select 1 Register (GPIO64 to 79)
#define GPIO_O_GPCQSEL2   0x84U    // GPIO C Qualifier Select 2 Register (GPIO80  to 95)
#define GPIO_O_GPCMUX1    0x86U    // GPIO C Mux 1 Register (GPIO64 to 79)
#define GPIO_O_GPCMUX2    0x88U    // GPIO C Mux 2 Register (GPIO80  to 95)
#define GPIO_O_GPCDIR     0x8AU    // GPIO C Direction Register (GPIO64 to 95)
#define GPIO_O_GPCPUD     0x8CU    // GPIO C Pull Up Disable Register (GPIO64 to 95)
#define GPIO_O_GPCINV     0x90U    // GPIO C Input Polarity Invert Registers (GPIO64 to 95)
#define GPIO_O_GPCODR     0x92U    // GPIO C Open Drain Output Register (GPIO64 to GPIO95)
#define GPIO_O_GPCGMUX1   0xA0U    // GPIO C Peripheral Group Mux (GPIO64 to 79)
#define GPIO_O_GPCGMUX2   0xA2U    // GPIO C Peripheral Group Mux (GPIO80  to 95)
#define GPIO_O_GPCCSEL1   0xA8U    // GPIO C Core Select Register (GPIO64 to 71)
#define GPIO_O_GPCCSEL2   0xAAU    // GPIO C Core Select Register (GPIO72 to 79)
#define GPIO_O_GPCCSEL3   0xACU    // GPIO C Core Select Register (GPIO80  to 87)
#define GPIO_O_GPCLOCK    0xBCU    // GPIO C Lock Configuration Register (GPIO64 to 95)
#define GPIO_O_GPCCR      0xBEU    // GPIO C Lock Commit Register (GPIO64 to 95)
#define GPIO_O_GPGCTRL    0x180U   // GPIO G Qualification Sampling Period Control (GPIO192 to 223)
#define GPIO_O_GPGQSEL2   0x184U   // GPIO G Qualifier Select 2 Register (GPIO208 to 223)
#define GPIO_O_GPGMUX2    0x188U   // GPIO G Mux 2 Register (GPIO208 to 223)
#define GPIO_O_GPGDIR     0x18AU   // GPIO G Direction Register (GPIO192 to 223)
#define GPIO_O_GPGPUD     0x18CU   // GPIO G Pull Up Disable Register (GPIO192 to 223)
#define GPIO_O_GPGINV     0x190U   // GPIO G Input Polarity Invert Registers (GPIO192 to 223)
#define GPIO_O_GPGODR     0x192U   // GPIO G Open Drain Output Register (GPIO192 to 223)
#define GPIO_O_GPGAMSEL   0x194U   // GPIO G Analog Mode Select register (GPIO192 to 223)
#define GPIO_O_GPGGMUX2   0x1A2U   // GPIO G Peripheral Group Mux (GPIO208 to 223)
#define GPIO_O_GPGCSEL3   0x1ACU   // GPIO G Core Select Register (GPIO208 to 215)
#define GPIO_O_GPGLOCK    0x1BCU   // GPIO G Lock Configuration Register (GPIO192 to 223)
#define GPIO_O_GPGCR      0x1BEU   // GPIO G Lock Commit Register (GPIO192 to 223)
#define GPIO_O_GPHCTRL    0x1C0U   // GPIO H Qualification Sampling Period Control (GPIO224 to 255)
#define GPIO_O_GPHQSEL1   0x1C2U   // GPIO H Qualifier Select 1 Register (GPIO224 to 239)
#define GPIO_O_GPHQSEL2   0x1C4U   // GPIO H Qualifier Select 2 Register (GPIO240 to 255)
#define GPIO_O_GPHMUX1    0x1C6U   // GPIO H Mux 1 Register (GPIO224 to 239)
#define GPIO_O_GPHMUX2    0x1C8U   // GPIO H Mux 2 Register (GPIO240 to 255)
#define GPIO_O_GPHDIR     0x1CAU   // GPIO H Direction Register (GPIO224 to 255)
#define GPIO_O_GPHPUD     0x1CCU   // GPIO H Pull Up Disable Register (GPIO224 to 255)
#define GPIO_O_GPHINV     0x1D0U   // GPIO H Input Polarity Invert Registers (GPIO224 to 255)
#define GPIO_O_GPHODR     0x1D2U   // GPIO H Open Drain Output Register (GPIO224 to GPIO255)
#define GPIO_O_GPHAMSEL   0x1D4U   // GPIO H Analog Mode Select register (GPIO224 to GPIO255)
#define GPIO_O_GPHGMUX1   0x1E0U   // GPIO H Peripheral Group Mux (GPIO224 to 239)
#define GPIO_O_GPHGMUX2   0x1E2U   // GPIO H Peripheral Group Mux (GPIO240 to 255)
#define GPIO_O_GPHCSEL1   0x1E8U   // GPIO H Core Select Register (GPIO224 to 231)
#define GPIO_O_GPHCSEL2   0x1EAU   // GPIO H Core Select Register (GPIO232 to 239)
#define GPIO_O_GPHCSEL3   0x1ECU   // GPIO H Core Select Register (GPIO240 to 247)
#define GPIO_O_GPHCSEL4   0x1EEU   // GPIO H Core Select Register (GPIO248 to 255)
#define GPIO_O_GPHLOCK    0x1FCU   // GPIO H Lock Configuration Register (GPIO224 to 255)
#define GPIO_O_GPHCR      0x1FEU   // GPIO H Lock Commit Register (GPIO224 to 255)

#define GPIO_O_GPADAT      0x0U    // GPIO A Data Register (GPIO0 to 31)
#define GPIO_O_GPASET      0x2U    // GPIO A Data Set Register (GPIO0 to 31)
#define GPIO_O_GPACLEAR    0x4U    // GPIO A Data Clear Register (GPIO0 to 31)
#define GPIO_O_GPATOGGLE   0x6U    // GPIO A Data Toggle Register (GPIO0 to 31)
#define GPIO_O_GPBDAT      0x8U    // GPIO B Data Register (GPIO32 to 63)
#define GPIO_O_GPBSET      0xAU    // GPIO B Data Set Register (GPIO32 to 63)
#define GPIO_O_GPBCLEAR    0xCU    // GPIO B Data Clear Register (GPIO32 to 63)
#define GPIO_O_GPBTOGGLE   0xEU    // GPIO B Data Toggle Register (GPIO32 to 63)
#define GPIO_O_GPCDAT      0x10U   // GPIO C Data Register (GPIO64 to 95)
#define GPIO_O_GPCSET      0x12U   // GPIO C Data Set Register (GPIO64 to 95)
#define GPIO_O_GPCCLEAR    0x14U   // GPIO C Data Clear Register (GPIO64 to 95)
#define GPIO_O_GPCTOGGLE   0x16U   // GPIO C Data Toggle Register (GPIO64 to 95)
#define GPIO_O_GPGDAT      0x30U   // GPIO G Data Register (GPIO192 to 223)
#define GPIO_O_GPGSET      0x32U   // GPIO G Data Set Register (GPIO192 to 223)
#define GPIO_O_GPGCLEAR    0x34U   // GPIO G Data Clear Register (GPIO192 to 223)
#define GPIO_O_GPGTOGGLE   0x36U   // GPIO G Data Toggle Register (GPIO192 to 223)
#define GPIO_O_GPHDAT      0x38U   // GPIO H Data Register (GPIO224 to 255)
#define GPIO_O_GPHSET      0x3AU   // GPIO H Data Set Register (GPIO224 to 255)
#define GPIO_O_GPHCLEAR    0x3CU   // GPIO H Data Clear Register (GPIO224 to 255)
#define GPIO_O_GPHTOGGLE   0x3EU   // GPIO H Data Toggle Register (GPIO224 to 255)

#define GPIO_O_GPADAT_R   0x0U   // GPIO A Data Read Register
#define GPIO_O_GPBDAT_R   0x2U   // GPIO B Data Read Register
#define GPIO_O_GPCDAT_R   0x4U   // GPIO C Data Read Register
#define GPIO_O_GPGDAT_R   0xCU   // GPIO G Data Read Register
#define GPIO_O_GPHDAT_R   0xEU   // GPIO H Data Read Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACTRL register
//
//*************************************************************************************************
#define GPIO_GPACTRL_QUALPRD0_S   0U
#define GPIO_GPACTRL_QUALPRD0_M   0xFFU         // Qualification sampling period for GPIO0 to GPIO7
#define GPIO_GPACTRL_QUALPRD1_S   8U
#define GPIO_GPACTRL_QUALPRD1_M   0xFF00U       // Qualification sampling period for GPIO8 to
                                                // GPIO15
#define GPIO_GPACTRL_QUALPRD2_S   16U
#define GPIO_GPACTRL_QUALPRD2_M   0xFF0000U     // Qualification sampling period for GPIO16 to
                                                // GPIO23
#define GPIO_GPACTRL_QUALPRD3_S   24U
#define GPIO_GPACTRL_QUALPRD3_M   0xFF000000U   // Qualification sampling period for GPIO24 to
                                                // GPIO31

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAQSEL1 register
//
//*************************************************************************************************
#define GPIO_GPAQSEL1_GPIO0_S    0U
#define GPIO_GPAQSEL1_GPIO0_M    0x3U          // Select input qualification type for GPIO0
#define GPIO_GPAQSEL1_GPIO1_S    2U
#define GPIO_GPAQSEL1_GPIO1_M    0xCU          // Select input qualification type for GPIO1
#define GPIO_GPAQSEL1_GPIO2_S    4U
#define GPIO_GPAQSEL1_GPIO2_M    0x30U         // Select input qualification type for GPIO2
#define GPIO_GPAQSEL1_GPIO3_S    6U
#define GPIO_GPAQSEL1_GPIO3_M    0xC0U         // Select input qualification type for GPIO3
#define GPIO_GPAQSEL1_GPIO4_S    8U
#define GPIO_GPAQSEL1_GPIO4_M    0x300U        // Select input qualification type for GPIO4
#define GPIO_GPAQSEL1_GPIO5_S    10U
#define GPIO_GPAQSEL1_GPIO5_M    0xC00U        // Select input qualification type for GPIO5
#define GPIO_GPAQSEL1_GPIO6_S    12U
#define GPIO_GPAQSEL1_GPIO6_M    0x3000U       // Select input qualification type for GPIO6
#define GPIO_GPAQSEL1_GPIO7_S    14U
#define GPIO_GPAQSEL1_GPIO7_M    0xC000U       // Select input qualification type for GPIO7
#define GPIO_GPAQSEL1_GPIO8_S    16U
#define GPIO_GPAQSEL1_GPIO8_M    0x30000U      // Select input qualification type for GPIO8
#define GPIO_GPAQSEL1_GPIO9_S    18U
#define GPIO_GPAQSEL1_GPIO9_M    0xC0000U      // Select input qualification type for GPIO9
#define GPIO_GPAQSEL1_GPIO10_S   20U
#define GPIO_GPAQSEL1_GPIO10_M   0x300000U     // Select input qualification type for GPIO10
#define GPIO_GPAQSEL1_GPIO11_S   22U
#define GPIO_GPAQSEL1_GPIO11_M   0xC00000U     // Select input qualification type for GPIO11
#define GPIO_GPAQSEL1_GPIO12_S   24U
#define GPIO_GPAQSEL1_GPIO12_M   0x3000000U    // Select input qualification type for GPIO12
#define GPIO_GPAQSEL1_GPIO13_S   26U
#define GPIO_GPAQSEL1_GPIO13_M   0xC000000U    // Select input qualification type for GPIO13
#define GPIO_GPAQSEL1_GPIO14_S   28U
#define GPIO_GPAQSEL1_GPIO14_M   0x30000000U   // Select input qualification type for GPIO14
#define GPIO_GPAQSEL1_GPIO15_S   30U
#define GPIO_GPAQSEL1_GPIO15_M   0xC0000000U   // Select input qualification type for GPIO15

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAQSEL2 register
//
//*************************************************************************************************
#define GPIO_GPAQSEL2_GPIO16_S   0U
#define GPIO_GPAQSEL2_GPIO16_M   0x3U          // Select input qualification type for GPIO16
#define GPIO_GPAQSEL2_GPIO17_S   2U
#define GPIO_GPAQSEL2_GPIO17_M   0xCU          // Select input qualification type for GPIO17
#define GPIO_GPAQSEL2_GPIO18_S   4U
#define GPIO_GPAQSEL2_GPIO18_M   0x30U         // Select input qualification type for GPIO18
#define GPIO_GPAQSEL2_GPIO19_S   6U
#define GPIO_GPAQSEL2_GPIO19_M   0xC0U         // Select input qualification type for GPIO19
#define GPIO_GPAQSEL2_GPIO20_S   8U
#define GPIO_GPAQSEL2_GPIO20_M   0x300U        // Select input qualification type for GPIO20
#define GPIO_GPAQSEL2_GPIO21_S   10U
#define GPIO_GPAQSEL2_GPIO21_M   0xC00U        // Select input qualification type for GPIO21
#define GPIO_GPAQSEL2_GPIO22_S   12U
#define GPIO_GPAQSEL2_GPIO22_M   0x3000U       // Select input qualification type for GPIO22
#define GPIO_GPAQSEL2_GPIO23_S   14U
#define GPIO_GPAQSEL2_GPIO23_M   0xC000U       // Select input qualification type for GPIO23
#define GPIO_GPAQSEL2_GPIO24_S   16U
#define GPIO_GPAQSEL2_GPIO24_M   0x30000U      // Select input qualification type for GPIO24
#define GPIO_GPAQSEL2_GPIO25_S   18U
#define GPIO_GPAQSEL2_GPIO25_M   0xC0000U      // Select input qualification type for GPIO25
#define GPIO_GPAQSEL2_GPIO26_S   20U
#define GPIO_GPAQSEL2_GPIO26_M   0x300000U     // Select input qualification type for GPIO26
#define GPIO_GPAQSEL2_GPIO27_S   22U
#define GPIO_GPAQSEL2_GPIO27_M   0xC00000U     // Select input qualification type for GPIO27
#define GPIO_GPAQSEL2_GPIO28_S   24U
#define GPIO_GPAQSEL2_GPIO28_M   0x3000000U    // Select input qualification type for GPIO28
#define GPIO_GPAQSEL2_GPIO29_S   26U
#define GPIO_GPAQSEL2_GPIO29_M   0xC000000U    // Select input qualification type for GPIO29
#define GPIO_GPAQSEL2_GPIO30_S   28U
#define GPIO_GPAQSEL2_GPIO30_M   0x30000000U   // Select input qualification type for GPIO30
#define GPIO_GPAQSEL2_GPIO31_S   30U
#define GPIO_GPAQSEL2_GPIO31_M   0xC0000000U   // Select input qualification type for GPIO31

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAMUX1 register
//
//*************************************************************************************************
#define GPIO_GPAMUX1_GPIO0_S    0U
#define GPIO_GPAMUX1_GPIO0_M    0x3U          // Defines pin-muxing selection for GPIO0
#define GPIO_GPAMUX1_GPIO1_S    2U
#define GPIO_GPAMUX1_GPIO1_M    0xCU          // Defines pin-muxing selection for GPIO1
#define GPIO_GPAMUX1_GPIO2_S    4U
#define GPIO_GPAMUX1_GPIO2_M    0x30U         // Defines pin-muxing selection for GPIO2
#define GPIO_GPAMUX1_GPIO3_S    6U
#define GPIO_GPAMUX1_GPIO3_M    0xC0U         // Defines pin-muxing selection for GPIO3
#define GPIO_GPAMUX1_GPIO4_S    8U
#define GPIO_GPAMUX1_GPIO4_M    0x300U        // Defines pin-muxing selection for GPIO4
#define GPIO_GPAMUX1_GPIO5_S    10U
#define GPIO_GPAMUX1_GPIO5_M    0xC00U        // Defines pin-muxing selection for GPIO5
#define GPIO_GPAMUX1_GPIO6_S    12U
#define GPIO_GPAMUX1_GPIO6_M    0x3000U       // Defines pin-muxing selection for GPIO6
#define GPIO_GPAMUX1_GPIO7_S    14U
#define GPIO_GPAMUX1_GPIO7_M    0xC000U       // Defines pin-muxing selection for GPIO7
#define GPIO_GPAMUX1_GPIO8_S    16U
#define GPIO_GPAMUX1_GPIO8_M    0x30000U      // Defines pin-muxing selection for GPIO8
#define GPIO_GPAMUX1_GPIO9_S    18U
#define GPIO_GPAMUX1_GPIO9_M    0xC0000U      // Defines pin-muxing selection for GPIO9
#define GPIO_GPAMUX1_GPIO10_S   20U
#define GPIO_GPAMUX1_GPIO10_M   0x300000U     // Defines pin-muxing selection for GPIO10
#define GPIO_GPAMUX1_GPIO11_S   22U
#define GPIO_GPAMUX1_GPIO11_M   0xC00000U     // Defines pin-muxing selection for GPIO11
#define GPIO_GPAMUX1_GPIO12_S   24U
#define GPIO_GPAMUX1_GPIO12_M   0x3000000U    // Defines pin-muxing selection for GPIO12
#define GPIO_GPAMUX1_GPIO13_S   26U
#define GPIO_GPAMUX1_GPIO13_M   0xC000000U    // Defines pin-muxing selection for GPIO13
#define GPIO_GPAMUX1_GPIO14_S   28U
#define GPIO_GPAMUX1_GPIO14_M   0x30000000U   // Defines pin-muxing selection for GPIO14
#define GPIO_GPAMUX1_GPIO15_S   30U
#define GPIO_GPAMUX1_GPIO15_M   0xC0000000U   // Defines pin-muxing selection for GPIO15

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAMUX2 register
//
//*************************************************************************************************
#define GPIO_GPAMUX2_GPIO16_S   0U
#define GPIO_GPAMUX2_GPIO16_M   0x3U          // Defines pin-muxing selection for GPIO16
#define GPIO_GPAMUX2_GPIO17_S   2U
#define GPIO_GPAMUX2_GPIO17_M   0xCU          // Defines pin-muxing selection for GPIO17
#define GPIO_GPAMUX2_GPIO18_S   4U
#define GPIO_GPAMUX2_GPIO18_M   0x30U         // Defines pin-muxing selection for GPIO18
#define GPIO_GPAMUX2_GPIO19_S   6U
#define GPIO_GPAMUX2_GPIO19_M   0xC0U         // Defines pin-muxing selection for GPIO19
#define GPIO_GPAMUX2_GPIO20_S   8U
#define GPIO_GPAMUX2_GPIO20_M   0x300U        // Defines pin-muxing selection for GPIO20
#define GPIO_GPAMUX2_GPIO21_S   10U
#define GPIO_GPAMUX2_GPIO21_M   0xC00U        // Defines pin-muxing selection for GPIO21
#define GPIO_GPAMUX2_GPIO22_S   12U
#define GPIO_GPAMUX2_GPIO22_M   0x3000U       // Defines pin-muxing selection for GPIO22
#define GPIO_GPAMUX2_GPIO23_S   14U
#define GPIO_GPAMUX2_GPIO23_M   0xC000U       // Defines pin-muxing selection for GPIO23
#define GPIO_GPAMUX2_GPIO24_S   16U
#define GPIO_GPAMUX2_GPIO24_M   0x30000U      // Defines pin-muxing selection for GPIO24
#define GPIO_GPAMUX2_GPIO25_S   18U
#define GPIO_GPAMUX2_GPIO25_M   0xC0000U      // Defines pin-muxing selection for GPIO25
#define GPIO_GPAMUX2_GPIO26_S   20U
#define GPIO_GPAMUX2_GPIO26_M   0x300000U     // Defines pin-muxing selection for GPIO26
#define GPIO_GPAMUX2_GPIO27_S   22U
#define GPIO_GPAMUX2_GPIO27_M   0xC00000U     // Defines pin-muxing selection for GPIO27
#define GPIO_GPAMUX2_GPIO28_S   24U
#define GPIO_GPAMUX2_GPIO28_M   0x3000000U    // Defines pin-muxing selection for GPIO28
#define GPIO_GPAMUX2_GPIO29_S   26U
#define GPIO_GPAMUX2_GPIO29_M   0xC000000U    // Defines pin-muxing selection for GPIO29
#define GPIO_GPAMUX2_GPIO30_S   28U
#define GPIO_GPAMUX2_GPIO30_M   0x30000000U   // Defines pin-muxing selection for GPIO30
#define GPIO_GPAMUX2_GPIO31_S   30U
#define GPIO_GPAMUX2_GPIO31_M   0xC0000000U   // Defines pin-muxing selection for GPIO31

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPADIR register
//
//*************************************************************************************************
#define GPIO_GPADIR_GPIO0    0x1U          // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO1    0x2U          // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO2    0x4U          // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO3    0x8U          // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO4    0x10U         // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO5    0x20U         // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO6    0x40U         // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO7    0x80U         // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO8    0x100U        // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO9    0x200U        // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO10   0x400U        // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO11   0x800U        // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO12   0x1000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO13   0x2000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO14   0x4000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO15   0x8000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO16   0x10000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO17   0x20000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO18   0x40000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO19   0x80000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO20   0x100000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO21   0x200000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO22   0x400000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO23   0x800000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO24   0x1000000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO25   0x2000000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO26   0x4000000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO27   0x8000000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO28   0x10000000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO29   0x20000000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO30   0x40000000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPADIR_GPIO31   0x80000000U   // Defines direction for this pin in GPIO mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAPUD register
//
//*************************************************************************************************
#define GPIO_GPAPUD_GPIO0    0x1U          // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO1    0x2U          // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO2    0x4U          // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO3    0x8U          // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO4    0x10U         // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO5    0x20U         // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO6    0x40U         // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO7    0x80U         // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO8    0x100U        // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO9    0x200U        // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO10   0x400U        // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO11   0x800U        // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO12   0x1000U       // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO13   0x2000U       // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO14   0x4000U       // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO15   0x8000U       // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO16   0x10000U      // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO17   0x20000U      // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO18   0x40000U      // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO19   0x80000U      // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO20   0x100000U     // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO21   0x200000U     // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO22   0x400000U     // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO23   0x800000U     // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO24   0x1000000U    // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO25   0x2000000U    // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO26   0x4000000U    // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO27   0x8000000U    // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO28   0x10000000U   // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO29   0x20000000U   // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO30   0x40000000U   // Pull-Up Disable control for this pin
#define GPIO_GPAPUD_GPIO31   0x80000000U   // Pull-Up Disable control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAINV register
//
//*************************************************************************************************
#define GPIO_GPAINV_GPIO0    0x1U          // Input inversion control for this pin
#define GPIO_GPAINV_GPIO1    0x2U          // Input inversion control for this pin
#define GPIO_GPAINV_GPIO2    0x4U          // Input inversion control for this pin
#define GPIO_GPAINV_GPIO3    0x8U          // Input inversion control for this pin
#define GPIO_GPAINV_GPIO4    0x10U         // Input inversion control for this pin
#define GPIO_GPAINV_GPIO5    0x20U         // Input inversion control for this pin
#define GPIO_GPAINV_GPIO6    0x40U         // Input inversion control for this pin
#define GPIO_GPAINV_GPIO7    0x80U         // Input inversion control for this pin
#define GPIO_GPAINV_GPIO8    0x100U        // Input inversion control for this pin
#define GPIO_GPAINV_GPIO9    0x200U        // Input inversion control for this pin
#define GPIO_GPAINV_GPIO10   0x400U        // Input inversion control for this pin
#define GPIO_GPAINV_GPIO11   0x800U        // Input inversion control for this pin
#define GPIO_GPAINV_GPIO12   0x1000U       // Input inversion control for this pin
#define GPIO_GPAINV_GPIO13   0x2000U       // Input inversion control for this pin
#define GPIO_GPAINV_GPIO14   0x4000U       // Input inversion control for this pin
#define GPIO_GPAINV_GPIO15   0x8000U       // Input inversion control for this pin
#define GPIO_GPAINV_GPIO16   0x10000U      // Input inversion control for this pin
#define GPIO_GPAINV_GPIO17   0x20000U      // Input inversion control for this pin
#define GPIO_GPAINV_GPIO18   0x40000U      // Input inversion control for this pin
#define GPIO_GPAINV_GPIO19   0x80000U      // Input inversion control for this pin
#define GPIO_GPAINV_GPIO20   0x100000U     // Input inversion control for this pin
#define GPIO_GPAINV_GPIO21   0x200000U     // Input inversion control for this pin
#define GPIO_GPAINV_GPIO22   0x400000U     // Input inversion control for this pin
#define GPIO_GPAINV_GPIO23   0x800000U     // Input inversion control for this pin
#define GPIO_GPAINV_GPIO24   0x1000000U    // Input inversion control for this pin
#define GPIO_GPAINV_GPIO25   0x2000000U    // Input inversion control for this pin
#define GPIO_GPAINV_GPIO26   0x4000000U    // Input inversion control for this pin
#define GPIO_GPAINV_GPIO27   0x8000000U    // Input inversion control for this pin
#define GPIO_GPAINV_GPIO28   0x10000000U   // Input inversion control for this pin
#define GPIO_GPAINV_GPIO29   0x20000000U   // Input inversion control for this pin
#define GPIO_GPAINV_GPIO30   0x40000000U   // Input inversion control for this pin
#define GPIO_GPAINV_GPIO31   0x80000000U   // Input inversion control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAODR register
//
//*************************************************************************************************
#define GPIO_GPAODR_GPIO0    0x1U          // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO1    0x2U          // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO2    0x4U          // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO3    0x8U          // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO4    0x10U         // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO5    0x20U         // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO6    0x40U         // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO7    0x80U         // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO8    0x100U        // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO9    0x200U        // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO10   0x400U        // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO11   0x800U        // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO12   0x1000U       // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO13   0x2000U       // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO14   0x4000U       // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO15   0x8000U       // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO16   0x10000U      // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO17   0x20000U      // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO18   0x40000U      // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO19   0x80000U      // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO20   0x100000U     // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO21   0x200000U     // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO22   0x400000U     // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO23   0x800000U     // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO24   0x1000000U    // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO25   0x2000000U    // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO26   0x4000000U    // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO27   0x8000000U    // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO28   0x10000000U   // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO29   0x20000000U   // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO30   0x40000000U   // Output Open-Drain control for this pin
#define GPIO_GPAODR_GPIO31   0x80000000U   // Output Open-Drain control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAAMSEL register
//
//*************************************************************************************************
#define GPIO_GPAAMSEL_GPIO11   0x800U        // Analog Mode select for this pin
#define GPIO_GPAAMSEL_GPIO12   0x1000U       // Analog Mode select for this pin
#define GPIO_GPAAMSEL_GPIO13   0x2000U       // Analog Mode select for this pin
#define GPIO_GPAAMSEL_GPIO16   0x10000U      // Analog Mode select for this pin
#define GPIO_GPAAMSEL_GPIO17   0x20000U      // Analog Mode select for this pin
#define GPIO_GPAAMSEL_GPIO20   0x100000U     // Analog Mode select for this pin
#define GPIO_GPAAMSEL_GPIO21   0x200000U     // Analog Mode select for this pin
#define GPIO_GPAAMSEL_GPIO23   0x800000U     // Analog Mode select for this pin
#define GPIO_GPAAMSEL_GPIO24   0x1000000U    // Analog Mode select for this pin
#define GPIO_GPAAMSEL_GPIO28   0x10000000U   // Analog Mode select for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAGMUX1 register
//
//*************************************************************************************************
#define GPIO_GPAGMUX1_GPIO0_S    0U
#define GPIO_GPAGMUX1_GPIO0_M    0x3U          // Defines pin-muxing selection for GPIO0
#define GPIO_GPAGMUX1_GPIO1_S    2U
#define GPIO_GPAGMUX1_GPIO1_M    0xCU          // Defines pin-muxing selection for GPIO1
#define GPIO_GPAGMUX1_GPIO2_S    4U
#define GPIO_GPAGMUX1_GPIO2_M    0x30U         // Defines pin-muxing selection for GPIO2
#define GPIO_GPAGMUX1_GPIO3_S    6U
#define GPIO_GPAGMUX1_GPIO3_M    0xC0U         // Defines pin-muxing selection for GPIO3
#define GPIO_GPAGMUX1_GPIO4_S    8U
#define GPIO_GPAGMUX1_GPIO4_M    0x300U        // Defines pin-muxing selection for GPIO4
#define GPIO_GPAGMUX1_GPIO5_S    10U
#define GPIO_GPAGMUX1_GPIO5_M    0xC00U        // Defines pin-muxing selection for GPIO5
#define GPIO_GPAGMUX1_GPIO6_S    12U
#define GPIO_GPAGMUX1_GPIO6_M    0x3000U       // Defines pin-muxing selection for GPIO6
#define GPIO_GPAGMUX1_GPIO7_S    14U
#define GPIO_GPAGMUX1_GPIO7_M    0xC000U       // Defines pin-muxing selection for GPIO7
#define GPIO_GPAGMUX1_GPIO8_S    16U
#define GPIO_GPAGMUX1_GPIO8_M    0x30000U      // Defines pin-muxing selection for GPIO8
#define GPIO_GPAGMUX1_GPIO9_S    18U
#define GPIO_GPAGMUX1_GPIO9_M    0xC0000U      // Defines pin-muxing selection for GPIO9
#define GPIO_GPAGMUX1_GPIO10_S   20U
#define GPIO_GPAGMUX1_GPIO10_M   0x300000U     // Defines pin-muxing selection for GPIO10
#define GPIO_GPAGMUX1_GPIO11_S   22U
#define GPIO_GPAGMUX1_GPIO11_M   0xC00000U     // Defines pin-muxing selection for GPIO11
#define GPIO_GPAGMUX1_GPIO12_S   24U
#define GPIO_GPAGMUX1_GPIO12_M   0x3000000U    // Defines pin-muxing selection for GPIO12
#define GPIO_GPAGMUX1_GPIO13_S   26U
#define GPIO_GPAGMUX1_GPIO13_M   0xC000000U    // Defines pin-muxing selection for GPIO13
#define GPIO_GPAGMUX1_GPIO14_S   28U
#define GPIO_GPAGMUX1_GPIO14_M   0x30000000U   // Defines pin-muxing selection for GPIO14
#define GPIO_GPAGMUX1_GPIO15_S   30U
#define GPIO_GPAGMUX1_GPIO15_M   0xC0000000U   // Defines pin-muxing selection for GPIO15

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPAGMUX2 register
//
//*************************************************************************************************
#define GPIO_GPAGMUX2_GPIO16_S   0U
#define GPIO_GPAGMUX2_GPIO16_M   0x3U          // Defines pin-muxing selection for GPIO16
#define GPIO_GPAGMUX2_GPIO17_S   2U
#define GPIO_GPAGMUX2_GPIO17_M   0xCU          // Defines pin-muxing selection for GPIO17
#define GPIO_GPAGMUX2_GPIO18_S   4U
#define GPIO_GPAGMUX2_GPIO18_M   0x30U         // Defines pin-muxing selection for GPIO18
#define GPIO_GPAGMUX2_GPIO19_S   6U
#define GPIO_GPAGMUX2_GPIO19_M   0xC0U         // Defines pin-muxing selection for GPIO19
#define GPIO_GPAGMUX2_GPIO20_S   8U
#define GPIO_GPAGMUX2_GPIO20_M   0x300U        // Defines pin-muxing selection for GPIO20
#define GPIO_GPAGMUX2_GPIO21_S   10U
#define GPIO_GPAGMUX2_GPIO21_M   0xC00U        // Defines pin-muxing selection for GPIO21
#define GPIO_GPAGMUX2_GPIO22_S   12U
#define GPIO_GPAGMUX2_GPIO22_M   0x3000U       // Defines pin-muxing selection for GPIO22
#define GPIO_GPAGMUX2_GPIO23_S   14U
#define GPIO_GPAGMUX2_GPIO23_M   0xC000U       // Defines pin-muxing selection for GPIO23
#define GPIO_GPAGMUX2_GPIO24_S   16U
#define GPIO_GPAGMUX2_GPIO24_M   0x30000U      // Defines pin-muxing selection for GPIO24
#define GPIO_GPAGMUX2_GPIO25_S   18U
#define GPIO_GPAGMUX2_GPIO25_M   0xC0000U      // Defines pin-muxing selection for GPIO25
#define GPIO_GPAGMUX2_GPIO26_S   20U
#define GPIO_GPAGMUX2_GPIO26_M   0x300000U     // Defines pin-muxing selection for GPIO26
#define GPIO_GPAGMUX2_GPIO27_S   22U
#define GPIO_GPAGMUX2_GPIO27_M   0xC00000U     // Defines pin-muxing selection for GPIO27
#define GPIO_GPAGMUX2_GPIO28_S   24U
#define GPIO_GPAGMUX2_GPIO28_M   0x3000000U    // Defines pin-muxing selection for GPIO28
#define GPIO_GPAGMUX2_GPIO29_S   26U
#define GPIO_GPAGMUX2_GPIO29_M   0xC000000U    // Defines pin-muxing selection for GPIO29
#define GPIO_GPAGMUX2_GPIO30_S   28U
#define GPIO_GPAGMUX2_GPIO30_M   0x30000000U   // Defines pin-muxing selection for GPIO30
#define GPIO_GPAGMUX2_GPIO31_S   30U
#define GPIO_GPAGMUX2_GPIO31_M   0xC0000000U   // Defines pin-muxing selection for GPIO31

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACSEL1 register
//
//*************************************************************************************************
#define GPIO_GPACSEL1_GPIO0_S   0U
#define GPIO_GPACSEL1_GPIO0_M   0xFU          // GPIO0 Controller CPU Select
#define GPIO_GPACSEL1_GPIO1_S   4U
#define GPIO_GPACSEL1_GPIO1_M   0xF0U         // GPIO1 Controller CPU Select
#define GPIO_GPACSEL1_GPIO2_S   8U
#define GPIO_GPACSEL1_GPIO2_M   0xF00U        // GPIO2 Controller CPU Select
#define GPIO_GPACSEL1_GPIO3_S   12U
#define GPIO_GPACSEL1_GPIO3_M   0xF000U       // GPIO3 Controller CPU Select
#define GPIO_GPACSEL1_GPIO4_S   16U
#define GPIO_GPACSEL1_GPIO4_M   0xF0000U      // GPIO4 Controller CPU Select
#define GPIO_GPACSEL1_GPIO5_S   20U
#define GPIO_GPACSEL1_GPIO5_M   0xF00000U     // GPIO5 Controller CPU Select
#define GPIO_GPACSEL1_GPIO6_S   24U
#define GPIO_GPACSEL1_GPIO6_M   0xF000000U    // GPIO6 Controller CPU Select
#define GPIO_GPACSEL1_GPIO7_S   28U
#define GPIO_GPACSEL1_GPIO7_M   0xF0000000U   // GPIO7 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACSEL2 register
//
//*************************************************************************************************
#define GPIO_GPACSEL2_GPIO8_S    0U
#define GPIO_GPACSEL2_GPIO8_M    0xFU          // GPIO8 Controller CPU Select
#define GPIO_GPACSEL2_GPIO9_S    4U
#define GPIO_GPACSEL2_GPIO9_M    0xF0U         // GPIO9 Controller CPU Select
#define GPIO_GPACSEL2_GPIO10_S   8U
#define GPIO_GPACSEL2_GPIO10_M   0xF00U        // GPIO10 Controller CPU Select
#define GPIO_GPACSEL2_GPIO11_S   12U
#define GPIO_GPACSEL2_GPIO11_M   0xF000U       // GPIO11 Controller CPU Select
#define GPIO_GPACSEL2_GPIO12_S   16U
#define GPIO_GPACSEL2_GPIO12_M   0xF0000U      // GPIO12 Controller CPU Select
#define GPIO_GPACSEL2_GPIO13_S   20U
#define GPIO_GPACSEL2_GPIO13_M   0xF00000U     // GPIO13 Controller CPU Select
#define GPIO_GPACSEL2_GPIO14_S   24U
#define GPIO_GPACSEL2_GPIO14_M   0xF000000U    // GPIO14 Controller CPU Select
#define GPIO_GPACSEL2_GPIO15_S   28U
#define GPIO_GPACSEL2_GPIO15_M   0xF0000000U   // GPIO15 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACSEL3 register
//
//*************************************************************************************************
#define GPIO_GPACSEL3_GPIO16_S   0U
#define GPIO_GPACSEL3_GPIO16_M   0xFU          // GPIO16 Controller CPU Select
#define GPIO_GPACSEL3_GPIO17_S   4U
#define GPIO_GPACSEL3_GPIO17_M   0xF0U         // GPIO17 Controller CPU Select
#define GPIO_GPACSEL3_GPIO18_S   8U
#define GPIO_GPACSEL3_GPIO18_M   0xF00U        // GPIO18 Controller CPU Select
#define GPIO_GPACSEL3_GPIO19_S   12U
#define GPIO_GPACSEL3_GPIO19_M   0xF000U       // GPIO19 Controller CPU Select
#define GPIO_GPACSEL3_GPIO20_S   16U
#define GPIO_GPACSEL3_GPIO20_M   0xF0000U      // GPIO20 Controller CPU Select
#define GPIO_GPACSEL3_GPIO21_S   20U
#define GPIO_GPACSEL3_GPIO21_M   0xF00000U     // GPIO21 Controller CPU Select
#define GPIO_GPACSEL3_GPIO22_S   24U
#define GPIO_GPACSEL3_GPIO22_M   0xF000000U    // GPIO22 Controller CPU Select
#define GPIO_GPACSEL3_GPIO23_S   28U
#define GPIO_GPACSEL3_GPIO23_M   0xF0000000U   // GPIO23 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACSEL4 register
//
//*************************************************************************************************
#define GPIO_GPACSEL4_GPIO24_S   0U
#define GPIO_GPACSEL4_GPIO24_M   0xFU          // GPIO24 Controller CPU Select
#define GPIO_GPACSEL4_GPIO25_S   4U
#define GPIO_GPACSEL4_GPIO25_M   0xF0U         // GPIO25 Controller CPU Select
#define GPIO_GPACSEL4_GPIO26_S   8U
#define GPIO_GPACSEL4_GPIO26_M   0xF00U        // GPIO26 Controller CPU Select
#define GPIO_GPACSEL4_GPIO27_S   12U
#define GPIO_GPACSEL4_GPIO27_M   0xF000U       // GPIO27 Controller CPU Select
#define GPIO_GPACSEL4_GPIO28_S   16U
#define GPIO_GPACSEL4_GPIO28_M   0xF0000U      // GPIO28 Controller CPU Select
#define GPIO_GPACSEL4_GPIO29_S   20U
#define GPIO_GPACSEL4_GPIO29_M   0xF00000U     // GPIO29 Controller CPU Select
#define GPIO_GPACSEL4_GPIO30_S   24U
#define GPIO_GPACSEL4_GPIO30_M   0xF000000U    // GPIO30 Controller CPU Select
#define GPIO_GPACSEL4_GPIO31_S   28U
#define GPIO_GPACSEL4_GPIO31_M   0xF0000000U   // GPIO31 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPALOCK register
//
//*************************************************************************************************
#define GPIO_GPALOCK_GPIO0    0x1U          // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO1    0x2U          // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO2    0x4U          // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO3    0x8U          // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO4    0x10U         // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO5    0x20U         // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO6    0x40U         // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO7    0x80U         // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO8    0x100U        // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO9    0x200U        // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO10   0x400U        // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO11   0x800U        // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO12   0x1000U       // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO13   0x2000U       // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO14   0x4000U       // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO15   0x8000U       // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO16   0x10000U      // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO17   0x20000U      // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO18   0x40000U      // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO19   0x80000U      // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO20   0x100000U     // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO21   0x200000U     // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO22   0x400000U     // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO23   0x800000U     // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO24   0x1000000U    // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO25   0x2000000U    // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO26   0x4000000U    // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO27   0x8000000U    // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO28   0x10000000U   // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO29   0x20000000U   // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO30   0x40000000U   // Configuration Lock bit for this pin
#define GPIO_GPALOCK_GPIO31   0x80000000U   // Configuration Lock bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACR register
//
//*************************************************************************************************
#define GPIO_GPACR_GPIO0    0x1U          // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO1    0x2U          // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO2    0x4U          // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO3    0x8U          // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO4    0x10U         // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO5    0x20U         // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO6    0x40U         // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO7    0x80U         // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO8    0x100U        // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO9    0x200U        // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO10   0x400U        // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO11   0x800U        // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO12   0x1000U       // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO13   0x2000U       // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO14   0x4000U       // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO15   0x8000U       // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO16   0x10000U      // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO17   0x20000U      // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO18   0x40000U      // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO19   0x80000U      // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO20   0x100000U     // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO21   0x200000U     // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO22   0x400000U     // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO23   0x800000U     // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO24   0x1000000U    // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO25   0x2000000U    // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO26   0x4000000U    // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO27   0x8000000U    // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO28   0x10000000U   // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO29   0x20000000U   // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO30   0x40000000U   // Configuration lock commit bit for this pin
#define GPIO_GPACR_GPIO31   0x80000000U   // Configuration lock commit bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCTRL register
//
//*************************************************************************************************
#define GPIO_GPBCTRL_QUALPRD0_S   0U
#define GPIO_GPBCTRL_QUALPRD0_M   0xFFU         // Qualification sampling period for GPIO32 to
                                                // GPIO39
#define GPIO_GPBCTRL_QUALPRD1_S   8U
#define GPIO_GPBCTRL_QUALPRD1_M   0xFF00U       // Qualification sampling period for GPIO40 to
                                                // GPIO47
#define GPIO_GPBCTRL_QUALPRD2_S   16U
#define GPIO_GPBCTRL_QUALPRD2_M   0xFF0000U     // Qualification sampling period for GPIO48 to
                                                // GPIO55
#define GPIO_GPBCTRL_QUALPRD3_S   24U
#define GPIO_GPBCTRL_QUALPRD3_M   0xFF000000U   // Qualification sampling period for GPIO56 to
                                                // GPIO63

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBQSEL1 register
//
//*************************************************************************************************
#define GPIO_GPBQSEL1_GPIO32_S   0U
#define GPIO_GPBQSEL1_GPIO32_M   0x3U          // Select input qualification type for GPIO32
#define GPIO_GPBQSEL1_GPIO33_S   2U
#define GPIO_GPBQSEL1_GPIO33_M   0xCU          // Select input qualification type for GPIO33
#define GPIO_GPBQSEL1_GPIO34_S   4U
#define GPIO_GPBQSEL1_GPIO34_M   0x30U         // Select input qualification type for GPIO34
#define GPIO_GPBQSEL1_GPIO35_S   6U
#define GPIO_GPBQSEL1_GPIO35_M   0xC0U         // Select input qualification type for GPIO35
#define GPIO_GPBQSEL1_GPIO37_S   10U
#define GPIO_GPBQSEL1_GPIO37_M   0xC00U        // Select input qualification type for GPIO37
#define GPIO_GPBQSEL1_GPIO40_S   16U
#define GPIO_GPBQSEL1_GPIO40_M   0x30000U      // Select input qualification type for GPIO40
#define GPIO_GPBQSEL1_GPIO41_S   18U
#define GPIO_GPBQSEL1_GPIO41_M   0xC0000U      // Select input qualification type for GPIO41
#define GPIO_GPBQSEL1_GPIO42_S   20U
#define GPIO_GPBQSEL1_GPIO42_M   0x300000U     // Select input qualification type for GPIO42
#define GPIO_GPBQSEL1_GPIO43_S   22U
#define GPIO_GPBQSEL1_GPIO43_M   0xC00000U     // Select input qualification type for GPIO43
#define GPIO_GPBQSEL1_GPIO44_S   24U
#define GPIO_GPBQSEL1_GPIO44_M   0x3000000U    // Select input qualification type for GPIO44
#define GPIO_GPBQSEL1_GPIO45_S   26U
#define GPIO_GPBQSEL1_GPIO45_M   0xC000000U    // Select input qualification type for GPIO45
#define GPIO_GPBQSEL1_GPIO46_S   28U
#define GPIO_GPBQSEL1_GPIO46_M   0x30000000U   // Select input qualification type for GPIO46
#define GPIO_GPBQSEL1_GPIO47_S   30U
#define GPIO_GPBQSEL1_GPIO47_M   0xC0000000U   // Select input qualification type for GPIO47

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBQSEL2 register
//
//*************************************************************************************************
#define GPIO_GPBQSEL2_GPIO48_S   0U
#define GPIO_GPBQSEL2_GPIO48_M   0x3U          // Select input qualification type for GPIO48
#define GPIO_GPBQSEL2_GPIO49_S   2U
#define GPIO_GPBQSEL2_GPIO49_M   0xCU          // Select input qualification type for GPIO49
#define GPIO_GPBQSEL2_GPIO50_S   4U
#define GPIO_GPBQSEL2_GPIO50_M   0x30U         // Select input qualification type for GPIO50
#define GPIO_GPBQSEL2_GPIO51_S   6U
#define GPIO_GPBQSEL2_GPIO51_M   0xC0U         // Select input qualification type for GPIO51
#define GPIO_GPBQSEL2_GPIO52_S   8U
#define GPIO_GPBQSEL2_GPIO52_M   0x300U        // Select input qualification type for GPIO52
#define GPIO_GPBQSEL2_GPIO53_S   10U
#define GPIO_GPBQSEL2_GPIO53_M   0xC00U        // Select input qualification type for GPIO53
#define GPIO_GPBQSEL2_GPIO54_S   12U
#define GPIO_GPBQSEL2_GPIO54_M   0x3000U       // Select input qualification type for GPIO54
#define GPIO_GPBQSEL2_GPIO55_S   14U
#define GPIO_GPBQSEL2_GPIO55_M   0xC000U       // Select input qualification type for GPIO55
#define GPIO_GPBQSEL2_GPIO56_S   16U
#define GPIO_GPBQSEL2_GPIO56_M   0x30000U      // Select input qualification type for GPIO56
#define GPIO_GPBQSEL2_GPIO57_S   18U
#define GPIO_GPBQSEL2_GPIO57_M   0xC0000U      // Select input qualification type for GPIO57
#define GPIO_GPBQSEL2_GPIO58_S   20U
#define GPIO_GPBQSEL2_GPIO58_M   0x300000U     // Select input qualification type for GPIO58
#define GPIO_GPBQSEL2_GPIO59_S   22U
#define GPIO_GPBQSEL2_GPIO59_M   0xC00000U     // Select input qualification type for GPIO59
#define GPIO_GPBQSEL2_GPIO60_S   24U
#define GPIO_GPBQSEL2_GPIO60_M   0x3000000U    // Select input qualification type for GPIO60
#define GPIO_GPBQSEL2_GPIO61_S   26U
#define GPIO_GPBQSEL2_GPIO61_M   0xC000000U    // Select input qualification type for GPIO61
#define GPIO_GPBQSEL2_GPIO62_S   28U
#define GPIO_GPBQSEL2_GPIO62_M   0x30000000U   // Select input qualification type for GPIO62
#define GPIO_GPBQSEL2_GPIO63_S   30U
#define GPIO_GPBQSEL2_GPIO63_M   0xC0000000U   // Select input qualification type for GPIO63

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBMUX1 register
//
//*************************************************************************************************
#define GPIO_GPBMUX1_GPIO32_S   0U
#define GPIO_GPBMUX1_GPIO32_M   0x3U          // Defines pin-muxing selection for GPIO32
#define GPIO_GPBMUX1_GPIO33_S   2U
#define GPIO_GPBMUX1_GPIO33_M   0xCU          // Defines pin-muxing selection for GPIO33
#define GPIO_GPBMUX1_GPIO34_S   4U
#define GPIO_GPBMUX1_GPIO34_M   0x30U         // Defines pin-muxing selection for GPIO34
#define GPIO_GPBMUX1_GPIO35_S   6U
#define GPIO_GPBMUX1_GPIO35_M   0xC0U         // Defines pin-muxing selection for GPIO35
#define GPIO_GPBMUX1_GPIO37_S   10U
#define GPIO_GPBMUX1_GPIO37_M   0xC00U        // Defines pin-muxing selection for GPIO37
#define GPIO_GPBMUX1_GPIO40_S   16U
#define GPIO_GPBMUX1_GPIO40_M   0x30000U      // Defines pin-muxing selection for GPIO40
#define GPIO_GPBMUX1_GPIO41_S   18U
#define GPIO_GPBMUX1_GPIO41_M   0xC0000U      // Defines pin-muxing selection for GPIO41
#define GPIO_GPBMUX1_GPIO42_S   20U
#define GPIO_GPBMUX1_GPIO42_M   0x300000U     // Defines pin-muxing selection for GPIO42
#define GPIO_GPBMUX1_GPIO43_S   22U
#define GPIO_GPBMUX1_GPIO43_M   0xC00000U     // Defines pin-muxing selection for GPIO43
#define GPIO_GPBMUX1_GPIO44_S   24U
#define GPIO_GPBMUX1_GPIO44_M   0x3000000U    // Defines pin-muxing selection for GPIO44
#define GPIO_GPBMUX1_GPIO45_S   26U
#define GPIO_GPBMUX1_GPIO45_M   0xC000000U    // Defines pin-muxing selection for GPIO45
#define GPIO_GPBMUX1_GPIO46_S   28U
#define GPIO_GPBMUX1_GPIO46_M   0x30000000U   // Defines pin-muxing selection for GPIO46
#define GPIO_GPBMUX1_GPIO47_S   30U
#define GPIO_GPBMUX1_GPIO47_M   0xC0000000U   // Defines pin-muxing selection for GPIO47

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBMUX2 register
//
//*************************************************************************************************
#define GPIO_GPBMUX2_GPIO48_S   0U
#define GPIO_GPBMUX2_GPIO48_M   0x3U          // Defines pin-muxing selection for GPIO48
#define GPIO_GPBMUX2_GPIO49_S   2U
#define GPIO_GPBMUX2_GPIO49_M   0xCU          // Defines pin-muxing selection for GPIO49
#define GPIO_GPBMUX2_GPIO50_S   4U
#define GPIO_GPBMUX2_GPIO50_M   0x30U         // Defines pin-muxing selection for GPIO50
#define GPIO_GPBMUX2_GPIO51_S   6U
#define GPIO_GPBMUX2_GPIO51_M   0xC0U         // Defines pin-muxing selection for GPIO51
#define GPIO_GPBMUX2_GPIO52_S   8U
#define GPIO_GPBMUX2_GPIO52_M   0x300U        // Defines pin-muxing selection for GPIO52
#define GPIO_GPBMUX2_GPIO53_S   10U
#define GPIO_GPBMUX2_GPIO53_M   0xC00U        // Defines pin-muxing selection for GPIO53
#define GPIO_GPBMUX2_GPIO54_S   12U
#define GPIO_GPBMUX2_GPIO54_M   0x3000U       // Defines pin-muxing selection for GPIO54
#define GPIO_GPBMUX2_GPIO55_S   14U
#define GPIO_GPBMUX2_GPIO55_M   0xC000U       // Defines pin-muxing selection for GPIO55
#define GPIO_GPBMUX2_GPIO56_S   16U
#define GPIO_GPBMUX2_GPIO56_M   0x30000U      // Defines pin-muxing selection for GPIO56
#define GPIO_GPBMUX2_GPIO57_S   18U
#define GPIO_GPBMUX2_GPIO57_M   0xC0000U      // Defines pin-muxing selection for GPIO57
#define GPIO_GPBMUX2_GPIO58_S   20U
#define GPIO_GPBMUX2_GPIO58_M   0x300000U     // Defines pin-muxing selection for GPIO58
#define GPIO_GPBMUX2_GPIO59_S   22U
#define GPIO_GPBMUX2_GPIO59_M   0xC00000U     // Defines pin-muxing selection for GPIO59
#define GPIO_GPBMUX2_GPIO60_S   24U
#define GPIO_GPBMUX2_GPIO60_M   0x3000000U    // Defines pin-muxing selection for GPIO60
#define GPIO_GPBMUX2_GPIO61_S   26U
#define GPIO_GPBMUX2_GPIO61_M   0xC000000U    // Defines pin-muxing selection for GPIO61
#define GPIO_GPBMUX2_GPIO62_S   28U
#define GPIO_GPBMUX2_GPIO62_M   0x30000000U   // Defines pin-muxing selection for GPIO62
#define GPIO_GPBMUX2_GPIO63_S   30U
#define GPIO_GPBMUX2_GPIO63_M   0xC0000000U   // Defines pin-muxing selection for GPIO63

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBDIR register
//
//*************************************************************************************************
#define GPIO_GPBDIR_GPIO32   0x1U          // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO33   0x2U          // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO34   0x4U          // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO35   0x8U          // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO37   0x20U         // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO40   0x100U        // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO41   0x200U        // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO42   0x400U        // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO43   0x800U        // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO44   0x1000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO45   0x2000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO46   0x4000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO47   0x8000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO48   0x10000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO49   0x20000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO50   0x40000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO51   0x80000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO52   0x100000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO53   0x200000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO54   0x400000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO55   0x800000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO56   0x1000000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO57   0x2000000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO58   0x4000000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO59   0x8000000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO60   0x10000000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO61   0x20000000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO62   0x40000000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO63   0x80000000U   // Defines direction for this pin in GPIO mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBPUD register
//
//*************************************************************************************************
#define GPIO_GPBPUD_GPIO32   0x1U          // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO33   0x2U          // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO34   0x4U          // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO35   0x8U          // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO37   0x20U         // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO40   0x100U        // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO41   0x200U        // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO42   0x400U        // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO43   0x800U        // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO44   0x1000U       // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO45   0x2000U       // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO46   0x4000U       // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO47   0x8000U       // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO48   0x10000U      // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO49   0x20000U      // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO50   0x40000U      // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO51   0x80000U      // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO52   0x100000U     // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO53   0x200000U     // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO54   0x400000U     // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO55   0x800000U     // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO56   0x1000000U    // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO57   0x2000000U    // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO58   0x4000000U    // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO59   0x8000000U    // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO60   0x10000000U   // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO61   0x20000000U   // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO62   0x40000000U   // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO63   0x80000000U   // Pull-Up Disable control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBINV register
//
//*************************************************************************************************
#define GPIO_GPBINV_GPIO32   0x1U          // Input inversion control for this pin
#define GPIO_GPBINV_GPIO33   0x2U          // Input inversion control for this pin
#define GPIO_GPBINV_GPIO34   0x4U          // Input inversion control for this pin
#define GPIO_GPBINV_GPIO35   0x8U          // Input inversion control for this pin
#define GPIO_GPBINV_GPIO37   0x20U         // Input inversion control for this pin
#define GPIO_GPBINV_GPIO40   0x100U        // Input inversion control for this pin
#define GPIO_GPBINV_GPIO41   0x200U        // Input inversion control for this pin
#define GPIO_GPBINV_GPIO42   0x400U        // Input inversion control for this pin
#define GPIO_GPBINV_GPIO43   0x800U        // Input inversion control for this pin
#define GPIO_GPBINV_GPIO44   0x1000U       // Input inversion control for this pin
#define GPIO_GPBINV_GPIO45   0x2000U       // Input inversion control for this pin
#define GPIO_GPBINV_GPIO46   0x4000U       // Input inversion control for this pin
#define GPIO_GPBINV_GPIO47   0x8000U       // Input inversion control for this pin
#define GPIO_GPBINV_GPIO48   0x10000U      // Input inversion control for this pin
#define GPIO_GPBINV_GPIO49   0x20000U      // Input inversion control for this pin
#define GPIO_GPBINV_GPIO50   0x40000U      // Input inversion control for this pin
#define GPIO_GPBINV_GPIO51   0x80000U      // Input inversion control for this pin
#define GPIO_GPBINV_GPIO52   0x100000U     // Input inversion control for this pin
#define GPIO_GPBINV_GPIO53   0x200000U     // Input inversion control for this pin
#define GPIO_GPBINV_GPIO54   0x400000U     // Input inversion control for this pin
#define GPIO_GPBINV_GPIO55   0x800000U     // Input inversion control for this pin
#define GPIO_GPBINV_GPIO56   0x1000000U    // Input inversion control for this pin
#define GPIO_GPBINV_GPIO57   0x2000000U    // Input inversion control for this pin
#define GPIO_GPBINV_GPIO58   0x4000000U    // Input inversion control for this pin
#define GPIO_GPBINV_GPIO59   0x8000000U    // Input inversion control for this pin
#define GPIO_GPBINV_GPIO60   0x10000000U   // Input inversion control for this pin
#define GPIO_GPBINV_GPIO61   0x20000000U   // Input inversion control for this pin
#define GPIO_GPBINV_GPIO62   0x40000000U   // Input inversion control for this pin
#define GPIO_GPBINV_GPIO63   0x80000000U   // Input inversion control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBODR register
//
//*************************************************************************************************
#define GPIO_GPBODR_GPIO32   0x1U          // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO33   0x2U          // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO34   0x4U          // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO35   0x8U          // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO37   0x20U         // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO40   0x100U        // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO41   0x200U        // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO42   0x400U        // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO43   0x800U        // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO44   0x1000U       // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO45   0x2000U       // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO46   0x4000U       // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO47   0x8000U       // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO48   0x10000U      // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO49   0x20000U      // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO50   0x40000U      // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO51   0x80000U      // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO52   0x100000U     // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO53   0x200000U     // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO54   0x400000U     // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO55   0x800000U     // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO56   0x1000000U    // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO57   0x2000000U    // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO58   0x4000000U    // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO59   0x8000000U    // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO60   0x10000000U   // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO61   0x20000000U   // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO62   0x40000000U   // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO63   0x80000000U   // Output Open-Drain control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBAMSEL register
//
//*************************************************************************************************
#define GPIO_GPBAMSEL_GPIO33   0x2U     // Analog Mode select for this pin
#define GPIO_GPBAMSEL_GPIO41   0x200U   // Analog Mode select for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBGMUX1 register
//
//*************************************************************************************************
#define GPIO_GPBGMUX1_GPIO32_S   0U
#define GPIO_GPBGMUX1_GPIO32_M   0x3U          // Defines pin-muxing selection for GPIO32
#define GPIO_GPBGMUX1_GPIO33_S   2U
#define GPIO_GPBGMUX1_GPIO33_M   0xCU          // Defines pin-muxing selection for GPIO33
#define GPIO_GPBGMUX1_GPIO34_S   4U
#define GPIO_GPBGMUX1_GPIO34_M   0x30U         // Defines pin-muxing selection for GPIO34
#define GPIO_GPBGMUX1_GPIO35_S   6U
#define GPIO_GPBGMUX1_GPIO35_M   0xC0U         // Defines pin-muxing selection for GPIO35
#define GPIO_GPBGMUX1_GPIO37_S   10U
#define GPIO_GPBGMUX1_GPIO37_M   0xC00U        // Defines pin-muxing selection for GPIO37
#define GPIO_GPBGMUX1_GPIO40_S   16U
#define GPIO_GPBGMUX1_GPIO40_M   0x30000U      // Defines pin-muxing selection for GPIO40
#define GPIO_GPBGMUX1_GPIO41_S   18U
#define GPIO_GPBGMUX1_GPIO41_M   0xC0000U      // Defines pin-muxing selection for GPIO41
#define GPIO_GPBGMUX1_GPIO42_S   20U
#define GPIO_GPBGMUX1_GPIO42_M   0x300000U     // Defines pin-muxing selection for GPIO42
#define GPIO_GPBGMUX1_GPIO43_S   22U
#define GPIO_GPBGMUX1_GPIO43_M   0xC00000U     // Defines pin-muxing selection for GPIO43
#define GPIO_GPBGMUX1_GPIO44_S   24U
#define GPIO_GPBGMUX1_GPIO44_M   0x3000000U    // Defines pin-muxing selection for GPIO44
#define GPIO_GPBGMUX1_GPIO45_S   26U
#define GPIO_GPBGMUX1_GPIO45_M   0xC000000U    // Defines pin-muxing selection for GPIO45
#define GPIO_GPBGMUX1_GPIO46_S   28U
#define GPIO_GPBGMUX1_GPIO46_M   0x30000000U   // Defines pin-muxing selection for GPIO46
#define GPIO_GPBGMUX1_GPIO47_S   30U
#define GPIO_GPBGMUX1_GPIO47_M   0xC0000000U   // Defines pin-muxing selection for GPIO47

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBGMUX2 register
//
//*************************************************************************************************
#define GPIO_GPBGMUX2_GPIO48_S   0U
#define GPIO_GPBGMUX2_GPIO48_M   0x3U          // Defines pin-muxing selection for GPIO48
#define GPIO_GPBGMUX2_GPIO49_S   2U
#define GPIO_GPBGMUX2_GPIO49_M   0xCU          // Defines pin-muxing selection for GPIO49
#define GPIO_GPBGMUX2_GPIO50_S   4U
#define GPIO_GPBGMUX2_GPIO50_M   0x30U         // Defines pin-muxing selection for GPIO50
#define GPIO_GPBGMUX2_GPIO51_S   6U
#define GPIO_GPBGMUX2_GPIO51_M   0xC0U         // Defines pin-muxing selection for GPIO51
#define GPIO_GPBGMUX2_GPIO52_S   8U
#define GPIO_GPBGMUX2_GPIO52_M   0x300U        // Defines pin-muxing selection for GPIO52
#define GPIO_GPBGMUX2_GPIO53_S   10U
#define GPIO_GPBGMUX2_GPIO53_M   0xC00U        // Defines pin-muxing selection for GPIO53
#define GPIO_GPBGMUX2_GPIO54_S   12U
#define GPIO_GPBGMUX2_GPIO54_M   0x3000U       // Defines pin-muxing selection for GPIO54
#define GPIO_GPBGMUX2_GPIO55_S   14U
#define GPIO_GPBGMUX2_GPIO55_M   0xC000U       // Defines pin-muxing selection for GPIO55
#define GPIO_GPBGMUX2_GPIO56_S   16U
#define GPIO_GPBGMUX2_GPIO56_M   0x30000U      // Defines pin-muxing selection for GPIO56
#define GPIO_GPBGMUX2_GPIO57_S   18U
#define GPIO_GPBGMUX2_GPIO57_M   0xC0000U      // Defines pin-muxing selection for GPIO57
#define GPIO_GPBGMUX2_GPIO58_S   20U
#define GPIO_GPBGMUX2_GPIO58_M   0x300000U     // Defines pin-muxing selection for GPIO58
#define GPIO_GPBGMUX2_GPIO59_S   22U
#define GPIO_GPBGMUX2_GPIO59_M   0xC00000U     // Defines pin-muxing selection for GPIO59
#define GPIO_GPBGMUX2_GPIO60_S   24U
#define GPIO_GPBGMUX2_GPIO60_M   0x3000000U    // Defines pin-muxing selection for GPIO60
#define GPIO_GPBGMUX2_GPIO61_S   26U
#define GPIO_GPBGMUX2_GPIO61_M   0xC000000U    // Defines pin-muxing selection for GPIO61
#define GPIO_GPBGMUX2_GPIO62_S   28U
#define GPIO_GPBGMUX2_GPIO62_M   0x30000000U   // Defines pin-muxing selection for GPIO62
#define GPIO_GPBGMUX2_GPIO63_S   30U
#define GPIO_GPBGMUX2_GPIO63_M   0xC0000000U   // Defines pin-muxing selection for GPIO63

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL1 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL1_GPIO32_S   0U
#define GPIO_GPBCSEL1_GPIO32_M   0xFU        // GPIO32 Controller CPU Select
#define GPIO_GPBCSEL1_GPIO33_S   4U
#define GPIO_GPBCSEL1_GPIO33_M   0xF0U       // GPIO33 Controller CPU Select
#define GPIO_GPBCSEL1_GPIO34_S   8U
#define GPIO_GPBCSEL1_GPIO34_M   0xF00U      // GPIO34 Controller CPU Select
#define GPIO_GPBCSEL1_GPIO35_S   12U
#define GPIO_GPBCSEL1_GPIO35_M   0xF000U     // GPIO35 Controller CPU Select
#define GPIO_GPBCSEL1_GPIO37_S   20U
#define GPIO_GPBCSEL1_GPIO37_M   0xF00000U   // GPIO37 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL2 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL2_GPIO40_S   0U
#define GPIO_GPBCSEL2_GPIO40_M   0xFU          // GPIO40 Controller CPU Select
#define GPIO_GPBCSEL2_GPIO41_S   4U
#define GPIO_GPBCSEL2_GPIO41_M   0xF0U         // GPIO41 Controller CPU Select
#define GPIO_GPBCSEL2_GPIO42_S   8U
#define GPIO_GPBCSEL2_GPIO42_M   0xF00U        // GPIO42 Controller CPU Select
#define GPIO_GPBCSEL2_GPIO43_S   12U
#define GPIO_GPBCSEL2_GPIO43_M   0xF000U       // GPIO43 Controller CPU Select
#define GPIO_GPBCSEL2_GPIO44_S   16U
#define GPIO_GPBCSEL2_GPIO44_M   0xF0000U      // GPIO44 Controller CPU Select
#define GPIO_GPBCSEL2_GPIO45_S   20U
#define GPIO_GPBCSEL2_GPIO45_M   0xF00000U     // GPIO45 Controller CPU Select
#define GPIO_GPBCSEL2_GPIO46_S   24U
#define GPIO_GPBCSEL2_GPIO46_M   0xF000000U    // GPIO46 Controller CPU Select
#define GPIO_GPBCSEL2_GPIO47_S   28U
#define GPIO_GPBCSEL2_GPIO47_M   0xF0000000U   // GPIO47 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL3 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL3_GPIO48_S   0U
#define GPIO_GPBCSEL3_GPIO48_M   0xFU          // GPIO48 Controller CPU Select
#define GPIO_GPBCSEL3_GPIO49_S   4U
#define GPIO_GPBCSEL3_GPIO49_M   0xF0U         // GPIO49 Controller CPU Select
#define GPIO_GPBCSEL3_GPIO50_S   8U
#define GPIO_GPBCSEL3_GPIO50_M   0xF00U        // GPIO50 Controller CPU Select
#define GPIO_GPBCSEL3_GPIO51_S   12U
#define GPIO_GPBCSEL3_GPIO51_M   0xF000U       // GPIO51 Controller CPU Select
#define GPIO_GPBCSEL3_GPIO52_S   16U
#define GPIO_GPBCSEL3_GPIO52_M   0xF0000U      // GPIO52 Controller CPU Select
#define GPIO_GPBCSEL3_GPIO53_S   20U
#define GPIO_GPBCSEL3_GPIO53_M   0xF00000U     // GPIO53 Controller CPU Select
#define GPIO_GPBCSEL3_GPIO54_S   24U
#define GPIO_GPBCSEL3_GPIO54_M   0xF000000U    // GPIO54 Controller CPU Select
#define GPIO_GPBCSEL3_GPIO55_S   28U
#define GPIO_GPBCSEL3_GPIO55_M   0xF0000000U   // GPIO55 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL4 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL4_GPIO56_S   0U
#define GPIO_GPBCSEL4_GPIO56_M   0xFU          // GPIO56 Controller CPU Select
#define GPIO_GPBCSEL4_GPIO57_S   4U
#define GPIO_GPBCSEL4_GPIO57_M   0xF0U         // GPIO57 Controller CPU Select
#define GPIO_GPBCSEL4_GPIO58_S   8U
#define GPIO_GPBCSEL4_GPIO58_M   0xF00U        // GPIO58 Controller CPU Select
#define GPIO_GPBCSEL4_GPIO59_S   12U
#define GPIO_GPBCSEL4_GPIO59_M   0xF000U       // GPIO59 Controller CPU Select
#define GPIO_GPBCSEL4_GPIO60_S   16U
#define GPIO_GPBCSEL4_GPIO60_M   0xF0000U      // GPIO60 Controller CPU Select
#define GPIO_GPBCSEL4_GPIO61_S   20U
#define GPIO_GPBCSEL4_GPIO61_M   0xF00000U     // GPIO61 Controller CPU Select
#define GPIO_GPBCSEL4_GPIO62_S   24U
#define GPIO_GPBCSEL4_GPIO62_M   0xF000000U    // GPIO62 Controller CPU Select
#define GPIO_GPBCSEL4_GPIO63_S   28U
#define GPIO_GPBCSEL4_GPIO63_M   0xF0000000U   // GPIO63 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBLOCK register
//
//*************************************************************************************************
#define GPIO_GPBLOCK_GPIO32   0x1U          // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO33   0x2U          // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO34   0x4U          // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO35   0x8U          // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO37   0x20U         // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO40   0x100U        // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO41   0x200U        // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO42   0x400U        // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO43   0x800U        // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO44   0x1000U       // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO45   0x2000U       // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO46   0x4000U       // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO47   0x8000U       // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO48   0x10000U      // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO49   0x20000U      // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO50   0x40000U      // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO51   0x80000U      // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO52   0x100000U     // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO53   0x200000U     // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO54   0x400000U     // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO55   0x800000U     // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO56   0x1000000U    // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO57   0x2000000U    // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO58   0x4000000U    // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO59   0x8000000U    // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO60   0x10000000U   // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO61   0x20000000U   // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO62   0x40000000U   // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO63   0x80000000U   // Configuration Lock bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCR register
//
//*************************************************************************************************
#define GPIO_GPBCR_GPIO32   0x1U          // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO33   0x2U          // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO34   0x4U          // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO35   0x8U          // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO37   0x20U         // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO40   0x100U        // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO41   0x200U        // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO42   0x400U        // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO43   0x800U        // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO44   0x1000U       // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO45   0x2000U       // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO46   0x4000U       // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO47   0x8000U       // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO48   0x10000U      // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO49   0x20000U      // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO50   0x40000U      // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO51   0x80000U      // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO52   0x100000U     // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO53   0x200000U     // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO54   0x400000U     // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO55   0x800000U     // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO56   0x1000000U    // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO57   0x2000000U    // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO58   0x4000000U    // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO59   0x8000000U    // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO60   0x10000000U   // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO61   0x20000000U   // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO62   0x40000000U   // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO63   0x80000000U   // Configuration lock commit bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCCTRL register
//
//*************************************************************************************************
#define GPIO_GPCCTRL_QUALPRD0_S   0U
#define GPIO_GPCCTRL_QUALPRD0_M   0xFFU       // Qualification sampling period for GPIO64 to GPIO71
#define GPIO_GPCCTRL_QUALPRD1_S   8U
#define GPIO_GPCCTRL_QUALPRD1_M   0xFF00U     // Qualification sampling period for GPIO72 to GPIO79
#define GPIO_GPCCTRL_QUALPRD2_S   16U
#define GPIO_GPCCTRL_QUALPRD2_M   0xFF0000U   // Qualification sampling period for GPIO80 to GPIO87

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCQSEL1 register
//
//*************************************************************************************************
#define GPIO_GPCQSEL1_GPIO64_S   0U
#define GPIO_GPCQSEL1_GPIO64_M   0x3U          // Select input qualification type for GPIO64
#define GPIO_GPCQSEL1_GPIO65_S   2U
#define GPIO_GPCQSEL1_GPIO65_M   0xCU          // Select input qualification type for GPIO65
#define GPIO_GPCQSEL1_GPIO66_S   4U
#define GPIO_GPCQSEL1_GPIO66_M   0x30U         // Select input qualification type for GPIO66
#define GPIO_GPCQSEL1_GPIO67_S   6U
#define GPIO_GPCQSEL1_GPIO67_M   0xC0U         // Select input qualification type for GPIO67
#define GPIO_GPCQSEL1_GPIO68_S   8U
#define GPIO_GPCQSEL1_GPIO68_M   0x300U        // Select input qualification type for GPIO68
#define GPIO_GPCQSEL1_GPIO69_S   10U
#define GPIO_GPCQSEL1_GPIO69_M   0xC00U        // Select input qualification type for GPIO69
#define GPIO_GPCQSEL1_GPIO70_S   12U
#define GPIO_GPCQSEL1_GPIO70_M   0x3000U       // Select input qualification type for GPIO70
#define GPIO_GPCQSEL1_GPIO71_S   14U
#define GPIO_GPCQSEL1_GPIO71_M   0xC000U       // Select input qualification type for GPIO71
#define GPIO_GPCQSEL1_GPIO72_S   16U
#define GPIO_GPCQSEL1_GPIO72_M   0x30000U      // Select input qualification type for GPIO72
#define GPIO_GPCQSEL1_GPIO73_S   18U
#define GPIO_GPCQSEL1_GPIO73_M   0xC0000U      // Select input qualification type for GPIO73
#define GPIO_GPCQSEL1_GPIO74_S   20U
#define GPIO_GPCQSEL1_GPIO74_M   0x300000U     // Select input qualification type for GPIO74
#define GPIO_GPCQSEL1_GPIO75_S   22U
#define GPIO_GPCQSEL1_GPIO75_M   0xC00000U     // Select input qualification type for GPIO75
#define GPIO_GPCQSEL1_GPIO76_S   24U
#define GPIO_GPCQSEL1_GPIO76_M   0x3000000U    // Select input qualification type for GPIO76
#define GPIO_GPCQSEL1_GPIO77_S   26U
#define GPIO_GPCQSEL1_GPIO77_M   0xC000000U    // Select input qualification type for GPIO77
#define GPIO_GPCQSEL1_GPIO78_S   28U
#define GPIO_GPCQSEL1_GPIO78_M   0x30000000U   // Select input qualification type for GPIO78
#define GPIO_GPCQSEL1_GPIO79_S   30U
#define GPIO_GPCQSEL1_GPIO79_M   0xC0000000U   // Select input qualification type for GPIO79

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCQSEL2 register
//
//*************************************************************************************************
#define GPIO_GPCQSEL2_GPIO80_S   0U
#define GPIO_GPCQSEL2_GPIO80_M   0x3U   // Select input qualification type for GPIO80
#define GPIO_GPCQSEL2_GPIO81_S   2U
#define GPIO_GPCQSEL2_GPIO81_M   0xCU   // Select input qualification type for GPIO81

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCMUX1 register
//
//*************************************************************************************************
#define GPIO_GPCMUX1_GPIO64_S   0U
#define GPIO_GPCMUX1_GPIO64_M   0x3U          // Defines pin-muxing selection for GPIO64
#define GPIO_GPCMUX1_GPIO65_S   2U
#define GPIO_GPCMUX1_GPIO65_M   0xCU          // Defines pin-muxing selection for GPIO65
#define GPIO_GPCMUX1_GPIO66_S   4U
#define GPIO_GPCMUX1_GPIO66_M   0x30U         // Defines pin-muxing selection for GPIO66
#define GPIO_GPCMUX1_GPIO67_S   6U
#define GPIO_GPCMUX1_GPIO67_M   0xC0U         // Defines pin-muxing selection for GPIO67
#define GPIO_GPCMUX1_GPIO68_S   8U
#define GPIO_GPCMUX1_GPIO68_M   0x300U        // Defines pin-muxing selection for GPIO68
#define GPIO_GPCMUX1_GPIO69_S   10U
#define GPIO_GPCMUX1_GPIO69_M   0xC00U        // Defines pin-muxing selection for GPIO69
#define GPIO_GPCMUX1_GPIO70_S   12U
#define GPIO_GPCMUX1_GPIO70_M   0x3000U       // Defines pin-muxing selection for GPIO70
#define GPIO_GPCMUX1_GPIO71_S   14U
#define GPIO_GPCMUX1_GPIO71_M   0xC000U       // Defines pin-muxing selection for GPIO71
#define GPIO_GPCMUX1_GPIO72_S   16U
#define GPIO_GPCMUX1_GPIO72_M   0x30000U      // Defines pin-muxing selection for GPIO72
#define GPIO_GPCMUX1_GPIO73_S   18U
#define GPIO_GPCMUX1_GPIO73_M   0xC0000U      // Defines pin-muxing selection for GPIO73
#define GPIO_GPCMUX1_GPIO74_S   20U
#define GPIO_GPCMUX1_GPIO74_M   0x300000U     // Defines pin-muxing selection for GPIO74
#define GPIO_GPCMUX1_GPIO75_S   22U
#define GPIO_GPCMUX1_GPIO75_M   0xC00000U     // Defines pin-muxing selection for GPIO75
#define GPIO_GPCMUX1_GPIO76_S   24U
#define GPIO_GPCMUX1_GPIO76_M   0x3000000U    // Defines pin-muxing selection for GPIO76
#define GPIO_GPCMUX1_GPIO77_S   26U
#define GPIO_GPCMUX1_GPIO77_M   0xC000000U    // Defines pin-muxing selection for GPIO77
#define GPIO_GPCMUX1_GPIO78_S   28U
#define GPIO_GPCMUX1_GPIO78_M   0x30000000U   // Defines pin-muxing selection for GPIO78
#define GPIO_GPCMUX1_GPIO79_S   30U
#define GPIO_GPCMUX1_GPIO79_M   0xC0000000U   // Defines pin-muxing selection for GPIO79

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCMUX2 register
//
//*************************************************************************************************
#define GPIO_GPCMUX2_GPIO80_S   0U
#define GPIO_GPCMUX2_GPIO80_M   0x3U   // Defines pin-muxing selection for GPIO80
#define GPIO_GPCMUX2_GPIO81_S   2U
#define GPIO_GPCMUX2_GPIO81_M   0xCU   // Defines pin-muxing selection for GPIO81

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCDIR register
//
//*************************************************************************************************
#define GPIO_GPCDIR_GPIO64   0x1U       // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO65   0x2U       // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO66   0x4U       // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO67   0x8U       // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO68   0x10U      // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO69   0x20U      // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO70   0x40U      // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO71   0x80U      // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO72   0x100U     // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO73   0x200U     // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO74   0x400U     // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO75   0x800U     // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO76   0x1000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO77   0x2000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO78   0x4000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO79   0x8000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO80   0x10000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPCDIR_GPIO81   0x20000U   // Defines direction for this pin in GPIO mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCPUD register
//
//*************************************************************************************************
#define GPIO_GPCPUD_GPIO64   0x1U       // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO65   0x2U       // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO66   0x4U       // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO67   0x8U       // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO68   0x10U      // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO69   0x20U      // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO70   0x40U      // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO71   0x80U      // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO72   0x100U     // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO73   0x200U     // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO74   0x400U     // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO75   0x800U     // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO76   0x1000U    // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO77   0x2000U    // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO78   0x4000U    // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO79   0x8000U    // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO80   0x10000U   // Pull-Up Disable control for this pin
#define GPIO_GPCPUD_GPIO81   0x20000U   // Pull-Up Disable control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCINV register
//
//*************************************************************************************************
#define GPIO_GPCINV_GPIO64   0x1U       // Input inversion control for this pin
#define GPIO_GPCINV_GPIO65   0x2U       // Input inversion control for this pin
#define GPIO_GPCINV_GPIO66   0x4U       // Input inversion control for this pin
#define GPIO_GPCINV_GPIO67   0x8U       // Input inversion control for this pin
#define GPIO_GPCINV_GPIO68   0x10U      // Input inversion control for this pin
#define GPIO_GPCINV_GPIO69   0x20U      // Input inversion control for this pin
#define GPIO_GPCINV_GPIO70   0x40U      // Input inversion control for this pin
#define GPIO_GPCINV_GPIO71   0x80U      // Input inversion control for this pin
#define GPIO_GPCINV_GPIO72   0x100U     // Input inversion control for this pin
#define GPIO_GPCINV_GPIO73   0x200U     // Input inversion control for this pin
#define GPIO_GPCINV_GPIO74   0x400U     // Input inversion control for this pin
#define GPIO_GPCINV_GPIO75   0x800U     // Input inversion control for this pin
#define GPIO_GPCINV_GPIO76   0x1000U    // Input inversion control for this pin
#define GPIO_GPCINV_GPIO77   0x2000U    // Input inversion control for this pin
#define GPIO_GPCINV_GPIO78   0x4000U    // Input inversion control for this pin
#define GPIO_GPCINV_GPIO79   0x8000U    // Input inversion control for this pin
#define GPIO_GPCINV_GPIO80   0x10000U   // Input inversion control for this pin
#define GPIO_GPCINV_GPIO81   0x20000U   // Input inversion control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCODR register
//
//*************************************************************************************************
#define GPIO_GPCODR_GPIO64   0x1U       // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO65   0x2U       // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO66   0x4U       // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO67   0x8U       // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO68   0x10U      // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO69   0x20U      // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO70   0x40U      // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO71   0x80U      // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO72   0x100U     // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO73   0x200U     // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO74   0x400U     // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO75   0x800U     // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO76   0x1000U    // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO77   0x2000U    // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO78   0x4000U    // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO79   0x8000U    // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO80   0x10000U   // Output Open-Drain control for this pin
#define GPIO_GPCODR_GPIO81   0x20000U   // Output Open-Drain control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCGMUX1 register
//
//*************************************************************************************************
#define GPIO_GPCGMUX1_GPIO64_S   0U
#define GPIO_GPCGMUX1_GPIO64_M   0x3U          // Defines pin-muxing selection for GPIO64
#define GPIO_GPCGMUX1_GPIO65_S   2U
#define GPIO_GPCGMUX1_GPIO65_M   0xCU          // Defines pin-muxing selection for GPIO65
#define GPIO_GPCGMUX1_GPIO66_S   4U
#define GPIO_GPCGMUX1_GPIO66_M   0x30U         // Defines pin-muxing selection for GPIO66
#define GPIO_GPCGMUX1_GPIO67_S   6U
#define GPIO_GPCGMUX1_GPIO67_M   0xC0U         // Defines pin-muxing selection for GPIO67
#define GPIO_GPCGMUX1_GPIO68_S   8U
#define GPIO_GPCGMUX1_GPIO68_M   0x300U        // Defines pin-muxing selection for GPIO68
#define GPIO_GPCGMUX1_GPIO69_S   10U
#define GPIO_GPCGMUX1_GPIO69_M   0xC00U        // Defines pin-muxing selection for GPIO69
#define GPIO_GPCGMUX1_GPIO70_S   12U
#define GPIO_GPCGMUX1_GPIO70_M   0x3000U       // Defines pin-muxing selection for GPIO70
#define GPIO_GPCGMUX1_GPIO71_S   14U
#define GPIO_GPCGMUX1_GPIO71_M   0xC000U       // Defines pin-muxing selection for GPIO71
#define GPIO_GPCGMUX1_GPIO72_S   16U
#define GPIO_GPCGMUX1_GPIO72_M   0x30000U      // Defines pin-muxing selection for GPIO72
#define GPIO_GPCGMUX1_GPIO73_S   18U
#define GPIO_GPCGMUX1_GPIO73_M   0xC0000U      // Defines pin-muxing selection for GPIO73
#define GPIO_GPCGMUX1_GPIO74_S   20U
#define GPIO_GPCGMUX1_GPIO74_M   0x300000U     // Defines pin-muxing selection for GPIO74
#define GPIO_GPCGMUX1_GPIO75_S   22U
#define GPIO_GPCGMUX1_GPIO75_M   0xC00000U     // Defines pin-muxing selection for GPIO75
#define GPIO_GPCGMUX1_GPIO76_S   24U
#define GPIO_GPCGMUX1_GPIO76_M   0x3000000U    // Defines pin-muxing selection for GPIO76
#define GPIO_GPCGMUX1_GPIO77_S   26U
#define GPIO_GPCGMUX1_GPIO77_M   0xC000000U    // Defines pin-muxing selection for GPIO77
#define GPIO_GPCGMUX1_GPIO78_S   28U
#define GPIO_GPCGMUX1_GPIO78_M   0x30000000U   // Defines pin-muxing selection for GPIO78
#define GPIO_GPCGMUX1_GPIO79_S   30U
#define GPIO_GPCGMUX1_GPIO79_M   0xC0000000U   // Defines pin-muxing selection for GPIO79

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCGMUX2 register
//
//*************************************************************************************************
#define GPIO_GPCGMUX2_GPIO80_S   0U
#define GPIO_GPCGMUX2_GPIO80_M   0x3U   // Defines pin-muxing selection for GPIO80
#define GPIO_GPCGMUX2_GPIO81_S   2U
#define GPIO_GPCGMUX2_GPIO81_M   0xCU   // Defines pin-muxing selection for GPIO81

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCCSEL1 register
//
//*************************************************************************************************
#define GPIO_GPCCSEL1_GPIO64_S   0U
#define GPIO_GPCCSEL1_GPIO64_M   0xFU          // GPIO64 Controller CPU Select
#define GPIO_GPCCSEL1_GPIO65_S   4U
#define GPIO_GPCCSEL1_GPIO65_M   0xF0U         // GPIO65 Controller CPU Select
#define GPIO_GPCCSEL1_GPIO66_S   8U
#define GPIO_GPCCSEL1_GPIO66_M   0xF00U        // GPIO66 Controller CPU Select
#define GPIO_GPCCSEL1_GPIO67_S   12U
#define GPIO_GPCCSEL1_GPIO67_M   0xF000U       // GPIO67 Controller CPU Select
#define GPIO_GPCCSEL1_GPIO68_S   16U
#define GPIO_GPCCSEL1_GPIO68_M   0xF0000U      // GPIO68 Controller CPU Select
#define GPIO_GPCCSEL1_GPIO69_S   20U
#define GPIO_GPCCSEL1_GPIO69_M   0xF00000U     // GPIO69 Controller CPU Select
#define GPIO_GPCCSEL1_GPIO70_S   24U
#define GPIO_GPCCSEL1_GPIO70_M   0xF000000U    // GPIO70 Controller CPU Select
#define GPIO_GPCCSEL1_GPIO71_S   28U
#define GPIO_GPCCSEL1_GPIO71_M   0xF0000000U   // GPIO71 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCCSEL2 register
//
//*************************************************************************************************
#define GPIO_GPCCSEL2_GPIO72_S   0U
#define GPIO_GPCCSEL2_GPIO72_M   0xFU          // GPIO72 Controller CPU Select
#define GPIO_GPCCSEL2_GPIO73_S   4U
#define GPIO_GPCCSEL2_GPIO73_M   0xF0U         // GPIO73 Controller CPU Select
#define GPIO_GPCCSEL2_GPIO74_S   8U
#define GPIO_GPCCSEL2_GPIO74_M   0xF00U        // GPIO74 Controller CPU Select
#define GPIO_GPCCSEL2_GPIO75_S   12U
#define GPIO_GPCCSEL2_GPIO75_M   0xF000U       // GPIO75 Controller CPU Select
#define GPIO_GPCCSEL2_GPIO76_S   16U
#define GPIO_GPCCSEL2_GPIO76_M   0xF0000U      // GPIO76 Controller CPU Select
#define GPIO_GPCCSEL2_GPIO77_S   20U
#define GPIO_GPCCSEL2_GPIO77_M   0xF00000U     // GPIO77 Controller CPU Select
#define GPIO_GPCCSEL2_GPIO78_S   24U
#define GPIO_GPCCSEL2_GPIO78_M   0xF000000U    // GPIO78 Controller CPU Select
#define GPIO_GPCCSEL2_GPIO79_S   28U
#define GPIO_GPCCSEL2_GPIO79_M   0xF0000000U   // GPIO79 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCCSEL3 register
//
//*************************************************************************************************
#define GPIO_GPCCSEL3_GPIO80_S   0U
#define GPIO_GPCCSEL3_GPIO80_M   0xFU    // GPIO80 Controller CPU Select
#define GPIO_GPCCSEL3_GPIO81_S   4U
#define GPIO_GPCCSEL3_GPIO81_M   0xF0U   // GPIO81 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCLOCK register
//
//*************************************************************************************************
#define GPIO_GPCLOCK_GPIO64   0x1U       // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO65   0x2U       // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO66   0x4U       // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO67   0x8U       // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO68   0x10U      // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO69   0x20U      // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO70   0x40U      // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO71   0x80U      // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO72   0x100U     // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO73   0x200U     // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO74   0x400U     // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO75   0x800U     // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO76   0x1000U    // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO77   0x2000U    // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO78   0x4000U    // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO79   0x8000U    // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO80   0x10000U   // Configuration Lock bit for this pin
#define GPIO_GPCLOCK_GPIO81   0x20000U   // Configuration Lock bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCCR register
//
//*************************************************************************************************
#define GPIO_GPCCR_GPIO64   0x1U       // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO65   0x2U       // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO66   0x4U       // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO67   0x8U       // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO68   0x10U      // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO69   0x20U      // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO70   0x40U      // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO71   0x80U      // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO72   0x100U     // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO73   0x200U     // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO74   0x400U     // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO75   0x800U     // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO76   0x1000U    // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO77   0x2000U    // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO78   0x4000U    // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO79   0x8000U    // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO80   0x10000U   // Configuration lock commit bit for this pin
#define GPIO_GPCCR_GPIO81   0x20000U   // Configuration lock commit bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGCTRL register
//
//*************************************************************************************************
#define GPIO_GPGCTRL_QUALPRD2_S   16U
#define GPIO_GPGCTRL_QUALPRD2_M   0xFF0000U   // Qualification sampling period for GPIO208 to
                                              // GPIO215

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGQSEL2 register
//
//*************************************************************************************************
#define GPIO_GPGQSEL2_GPIO208_S   0U
#define GPIO_GPGQSEL2_GPIO208_M   0x3U      // Select input qualification type for GPIO208
#define GPIO_GPGQSEL2_GPIO209_S   2U
#define GPIO_GPGQSEL2_GPIO209_M   0xCU      // Select input qualification type for GPIO209
#define GPIO_GPGQSEL2_GPIO210_S   4U
#define GPIO_GPGQSEL2_GPIO210_M   0x30U     // Select input qualification type for GPIO210
#define GPIO_GPGQSEL2_GPIO211_S   6U
#define GPIO_GPGQSEL2_GPIO211_M   0xC0U     // Select input qualification type for GPIO211
#define GPIO_GPGQSEL2_GPIO212_S   8U
#define GPIO_GPGQSEL2_GPIO212_M   0x300U    // Select input qualification type for GPIO212
#define GPIO_GPGQSEL2_GPIO213_S   10U
#define GPIO_GPGQSEL2_GPIO213_M   0xC00U    // Select input qualification type for GPIO213
#define GPIO_GPGQSEL2_GPIO214_S   12U
#define GPIO_GPGQSEL2_GPIO214_M   0x3000U   // Select input qualification type for GPIO214
#define GPIO_GPGQSEL2_GPIO215_S   14U
#define GPIO_GPGQSEL2_GPIO215_M   0xC000U   // Select input qualification type for GPIO215

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGMUX2 register
//
//*************************************************************************************************
#define GPIO_GPGMUX2_GPIO208_S   0U
#define GPIO_GPGMUX2_GPIO208_M   0x3U      // Defines pin-muxing selection for GPIO208
#define GPIO_GPGMUX2_GPIO209_S   2U
#define GPIO_GPGMUX2_GPIO209_M   0xCU      // Defines pin-muxing selection for GPIO209
#define GPIO_GPGMUX2_GPIO210_S   4U
#define GPIO_GPGMUX2_GPIO210_M   0x30U     // Defines pin-muxing selection for GPIO210
#define GPIO_GPGMUX2_GPIO211_S   6U
#define GPIO_GPGMUX2_GPIO211_M   0xC0U     // Defines pin-muxing selection for GPIO211
#define GPIO_GPGMUX2_GPIO212_S   8U
#define GPIO_GPGMUX2_GPIO212_M   0x300U    // Defines pin-muxing selection for GPIO212
#define GPIO_GPGMUX2_GPIO213_S   10U
#define GPIO_GPGMUX2_GPIO213_M   0xC00U    // Defines pin-muxing selection for GPIO213
#define GPIO_GPGMUX2_GPIO214_S   12U
#define GPIO_GPGMUX2_GPIO214_M   0x3000U   // Defines pin-muxing selection for GPIO214
#define GPIO_GPGMUX2_GPIO215_S   14U
#define GPIO_GPGMUX2_GPIO215_M   0xC000U   // Defines pin-muxing selection for GPIO215

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGDIR register
//
//*************************************************************************************************
#define GPIO_GPGDIR_GPIO208   0x10000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPGDIR_GPIO209   0x20000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPGDIR_GPIO210   0x40000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPGDIR_GPIO211   0x80000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPGDIR_GPIO212   0x100000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPGDIR_GPIO213   0x200000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPGDIR_GPIO214   0x400000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPGDIR_GPIO215   0x800000U   // Defines direction for this pin in GPIO mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGPUD register
//
//*************************************************************************************************
#define GPIO_GPGPUD_GPIO208   0x10000U    // Pull-Up Disable control for this pin
#define GPIO_GPGPUD_GPIO209   0x20000U    // Pull-Up Disable control for this pin
#define GPIO_GPGPUD_GPIO210   0x40000U    // Pull-Up Disable control for this pin
#define GPIO_GPGPUD_GPIO211   0x80000U    // Pull-Up Disable control for this pin
#define GPIO_GPGPUD_GPIO212   0x100000U   // Pull-Up Disable control for this pin
#define GPIO_GPGPUD_GPIO213   0x200000U   // Pull-Up Disable control for this pin
#define GPIO_GPGPUD_GPIO214   0x400000U   // Pull-Up Disable control for this pin
#define GPIO_GPGPUD_GPIO215   0x800000U   // Pull-Up Disable control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGINV register
//
//*************************************************************************************************
#define GPIO_GPGINV_GPIO208   0x10000U    // Input inversion control for this pin
#define GPIO_GPGINV_GPIO209   0x20000U    // Input inversion control for this pin
#define GPIO_GPGINV_GPIO210   0x40000U    // Input inversion control for this pin
#define GPIO_GPGINV_GPIO211   0x80000U    // Input inversion control for this pin
#define GPIO_GPGINV_GPIO212   0x100000U   // Input inversion control for this pin
#define GPIO_GPGINV_GPIO213   0x200000U   // Input inversion control for this pin
#define GPIO_GPGINV_GPIO214   0x400000U   // Input inversion control for this pin
#define GPIO_GPGINV_GPIO215   0x800000U   // Input inversion control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGODR register
//
//*************************************************************************************************
#define GPIO_GPGODR_GPIO208   0x10000U    // Output Open-Drain control for this pin
#define GPIO_GPGODR_GPIO209   0x20000U    // Output Open-Drain control for this pin
#define GPIO_GPGODR_GPIO210   0x40000U    // Output Open-Drain control for this pin
#define GPIO_GPGODR_GPIO211   0x80000U    // Output Open-Drain control for this pin
#define GPIO_GPGODR_GPIO212   0x100000U   // Output Open-Drain control for this pin
#define GPIO_GPGODR_GPIO213   0x200000U   // Output Open-Drain control for this pin
#define GPIO_GPGODR_GPIO214   0x400000U   // Output Open-Drain control for this pin
#define GPIO_GPGODR_GPIO215   0x800000U   // Output Open-Drain control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGAMSEL register
//
//*************************************************************************************************
#define GPIO_GPGAMSEL_GPIO208   0x10000U    // Analog Mode select for this pin
#define GPIO_GPGAMSEL_GPIO209   0x20000U    // Analog Mode select for this pin
#define GPIO_GPGAMSEL_GPIO210   0x40000U    // Analog Mode select for this pin
#define GPIO_GPGAMSEL_GPIO211   0x80000U    // Analog Mode select for this pin
#define GPIO_GPGAMSEL_GPIO212   0x100000U   // Analog Mode select for this pin
#define GPIO_GPGAMSEL_GPIO213   0x200000U   // Analog Mode select for this pin
#define GPIO_GPGAMSEL_GPIO214   0x400000U   // Analog Mode select for this pin
#define GPIO_GPGAMSEL_GPIO215   0x800000U   // Analog Mode select for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGGMUX2 register
//
//*************************************************************************************************
#define GPIO_GPGGMUX2_GPIO208_S   0U
#define GPIO_GPGGMUX2_GPIO208_M   0x3U      // Defines pin-muxing selection for GPIO208
#define GPIO_GPGGMUX2_GPIO209_S   2U
#define GPIO_GPGGMUX2_GPIO209_M   0xCU      // Defines pin-muxing selection for GPIO209
#define GPIO_GPGGMUX2_GPIO210_S   4U
#define GPIO_GPGGMUX2_GPIO210_M   0x30U     // Defines pin-muxing selection for GPIO210
#define GPIO_GPGGMUX2_GPIO211_S   6U
#define GPIO_GPGGMUX2_GPIO211_M   0xC0U     // Defines pin-muxing selection for GPIO211
#define GPIO_GPGGMUX2_GPIO212_S   8U
#define GPIO_GPGGMUX2_GPIO212_M   0x300U    // Defines pin-muxing selection for GPIO212
#define GPIO_GPGGMUX2_GPIO213_S   10U
#define GPIO_GPGGMUX2_GPIO213_M   0xC00U    // Defines pin-muxing selection for GPIO213
#define GPIO_GPGGMUX2_GPIO214_S   12U
#define GPIO_GPGGMUX2_GPIO214_M   0x3000U   // Defines pin-muxing selection for GPIO214
#define GPIO_GPGGMUX2_GPIO215_S   14U
#define GPIO_GPGGMUX2_GPIO215_M   0xC000U   // Defines pin-muxing selection for GPIO215

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGCSEL3 register
//
//*************************************************************************************************
#define GPIO_GPGCSEL3_GPIO208_S   0U
#define GPIO_GPGCSEL3_GPIO208_M   0xFU          // GPIO208 Controller CPU Select
#define GPIO_GPGCSEL3_GPIO209_S   4U
#define GPIO_GPGCSEL3_GPIO209_M   0xF0U         // GPIO209 Controller CPU Select
#define GPIO_GPGCSEL3_GPIO210_S   8U
#define GPIO_GPGCSEL3_GPIO210_M   0xF00U        // GPIO210 Controller CPU Select
#define GPIO_GPGCSEL3_GPIO211_S   12U
#define GPIO_GPGCSEL3_GPIO211_M   0xF000U       // GPIO211 Controller CPU Select
#define GPIO_GPGCSEL3_GPIO212_S   16U
#define GPIO_GPGCSEL3_GPIO212_M   0xF0000U      // GPIO212 Controller CPU Select
#define GPIO_GPGCSEL3_GPIO213_S   20U
#define GPIO_GPGCSEL3_GPIO213_M   0xF00000U     // GPIO213 Controller CPU Select
#define GPIO_GPGCSEL3_GPIO214_S   24U
#define GPIO_GPGCSEL3_GPIO214_M   0xF000000U    // GPIO214 Controller CPU Select
#define GPIO_GPGCSEL3_GPIO215_S   28U
#define GPIO_GPGCSEL3_GPIO215_M   0xF0000000U   // GPIO215 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGLOCK register
//
//*************************************************************************************************
#define GPIO_GPGLOCK_GPIO208   0x10000U    // Configuration Lock bit for this pin
#define GPIO_GPGLOCK_GPIO209   0x20000U    // Configuration Lock bit for this pin
#define GPIO_GPGLOCK_GPIO210   0x40000U    // Configuration Lock bit for this pin
#define GPIO_GPGLOCK_GPIO211   0x80000U    // Configuration Lock bit for this pin
#define GPIO_GPGLOCK_GPIO212   0x100000U   // Configuration Lock bit for this pin
#define GPIO_GPGLOCK_GPIO213   0x200000U   // Configuration Lock bit for this pin
#define GPIO_GPGLOCK_GPIO214   0x400000U   // Configuration Lock bit for this pin
#define GPIO_GPGLOCK_GPIO215   0x800000U   // Configuration Lock bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGCR register
//
//*************************************************************************************************
#define GPIO_GPGCR_GPIO208   0x10000U    // Configuration lock commit bit for this pin
#define GPIO_GPGCR_GPIO209   0x20000U    // Configuration lock commit bit for this pin
#define GPIO_GPGCR_GPIO210   0x40000U    // Configuration lock commit bit for this pin
#define GPIO_GPGCR_GPIO211   0x80000U    // Configuration lock commit bit for this pin
#define GPIO_GPGCR_GPIO212   0x100000U   // Configuration lock commit bit for this pin
#define GPIO_GPGCR_GPIO213   0x200000U   // Configuration lock commit bit for this pin
#define GPIO_GPGCR_GPIO214   0x400000U   // Configuration lock commit bit for this pin
#define GPIO_GPGCR_GPIO215   0x800000U   // Configuration lock commit bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHCTRL register
//
//*************************************************************************************************
#define GPIO_GPHCTRL_QUALPRD0_S   0U
#define GPIO_GPHCTRL_QUALPRD0_M   0xFFU         // Qualification sampling period for GPIO224 to
                                                // GPIO231
#define GPIO_GPHCTRL_QUALPRD1_S   8U
#define GPIO_GPHCTRL_QUALPRD1_M   0xFF00U       // Qualification sampling period for GPIO232 to
                                                // GPIO239
#define GPIO_GPHCTRL_QUALPRD2_S   16U
#define GPIO_GPHCTRL_QUALPRD2_M   0xFF0000U     // Qualification sampling period for GPIO240 to
                                                // GPIO247
#define GPIO_GPHCTRL_QUALPRD3_S   24U
#define GPIO_GPHCTRL_QUALPRD3_M   0xFF000000U   // Qualification sampling period for GPIO248 to
                                                // GPIO255

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHQSEL1 register
//
//*************************************************************************************************
#define GPIO_GPHQSEL1_GPIO224_S   0U
#define GPIO_GPHQSEL1_GPIO224_M   0x3U          // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO225_S   2U
#define GPIO_GPHQSEL1_GPIO225_M   0xCU          // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO226_S   4U
#define GPIO_GPHQSEL1_GPIO226_M   0x30U         // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO227_S   6U
#define GPIO_GPHQSEL1_GPIO227_M   0xC0U         // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO228_S   8U
#define GPIO_GPHQSEL1_GPIO228_M   0x300U        // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO229_S   10U
#define GPIO_GPHQSEL1_GPIO229_M   0xC00U        // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO230_S   12U
#define GPIO_GPHQSEL1_GPIO230_M   0x3000U       // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO231_S   14U
#define GPIO_GPHQSEL1_GPIO231_M   0xC000U       // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO232_S   16U
#define GPIO_GPHQSEL1_GPIO232_M   0x30000U      // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO233_S   18U
#define GPIO_GPHQSEL1_GPIO233_M   0xC0000U      // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO234_S   20U
#define GPIO_GPHQSEL1_GPIO234_M   0x300000U     // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO235_S   22U
#define GPIO_GPHQSEL1_GPIO235_M   0xC00000U     // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO236_S   24U
#define GPIO_GPHQSEL1_GPIO236_M   0x3000000U    // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO237_S   26U
#define GPIO_GPHQSEL1_GPIO237_M   0xC000000U    // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO238_S   28U
#define GPIO_GPHQSEL1_GPIO238_M   0x30000000U   // Select input qualification type for this GPIO
                                                // Pin
#define GPIO_GPHQSEL1_GPIO239_S   30U
#define GPIO_GPHQSEL1_GPIO239_M   0xC0000000U   // Select input qualification type for this GPIO
                                                // Pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHQSEL2 register
//
//*************************************************************************************************
#define GPIO_GPHQSEL2_GPIO240_S   0U
#define GPIO_GPHQSEL2_GPIO240_M   0x3U         // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO241_S   2U
#define GPIO_GPHQSEL2_GPIO241_M   0xCU         // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO242_S   4U
#define GPIO_GPHQSEL2_GPIO242_M   0x30U        // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO244_S   8U
#define GPIO_GPHQSEL2_GPIO244_M   0x300U       // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO245_S   10U
#define GPIO_GPHQSEL2_GPIO245_M   0xC00U       // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO247_S   14U
#define GPIO_GPHQSEL2_GPIO247_M   0xC000U      // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO248_S   16U
#define GPIO_GPHQSEL2_GPIO248_M   0x30000U     // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO249_S   18U
#define GPIO_GPHQSEL2_GPIO249_M   0xC0000U     // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO251_S   22U
#define GPIO_GPHQSEL2_GPIO251_M   0xC00000U    // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO252_S   24U
#define GPIO_GPHQSEL2_GPIO252_M   0x3000000U   // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO253_S   26U
#define GPIO_GPHQSEL2_GPIO253_M   0xC000000U   // Select input qualification type for this GPIO Pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHMUX1 register
//
//*************************************************************************************************
#define GPIO_GPHMUX1_GPIO224_S   0U
#define GPIO_GPHMUX1_GPIO224_M   0x3U          // Defines pin-muxing selection for GPIO224
#define GPIO_GPHMUX1_GPIO225_S   2U
#define GPIO_GPHMUX1_GPIO225_M   0xCU          // Defines pin-muxing selection for GPIO225
#define GPIO_GPHMUX1_GPIO226_S   4U
#define GPIO_GPHMUX1_GPIO226_M   0x30U         // Defines pin-muxing selection for GPIO226
#define GPIO_GPHMUX1_GPIO227_S   6U
#define GPIO_GPHMUX1_GPIO227_M   0xC0U         // Defines pin-muxing selection for GPIO227
#define GPIO_GPHMUX1_GPIO228_S   8U
#define GPIO_GPHMUX1_GPIO228_M   0x300U        // Defines pin-muxing selection for GPIO228
#define GPIO_GPHMUX1_GPIO229_S   10U
#define GPIO_GPHMUX1_GPIO229_M   0xC00U        // Defines pin-muxing selection for GPIO229
#define GPIO_GPHMUX1_GPIO230_S   12U
#define GPIO_GPHMUX1_GPIO230_M   0x3000U       // Defines pin-muxing selection for GPIO230
#define GPIO_GPHMUX1_GPIO231_S   14U
#define GPIO_GPHMUX1_GPIO231_M   0xC000U       // Defines pin-muxing selection for GPIO231
#define GPIO_GPHMUX1_GPIO232_S   16U
#define GPIO_GPHMUX1_GPIO232_M   0x30000U      // Defines pin-muxing selection for GPIO232
#define GPIO_GPHMUX1_GPIO233_S   18U
#define GPIO_GPHMUX1_GPIO233_M   0xC0000U      // Defines pin-muxing selection for GPIO233
#define GPIO_GPHMUX1_GPIO234_S   20U
#define GPIO_GPHMUX1_GPIO234_M   0x300000U     // Defines pin-muxing selection for GPIO234
#define GPIO_GPHMUX1_GPIO235_S   22U
#define GPIO_GPHMUX1_GPIO235_M   0xC00000U     // Defines pin-muxing selection for GPIO235
#define GPIO_GPHMUX1_GPIO236_S   24U
#define GPIO_GPHMUX1_GPIO236_M   0x3000000U    // Defines pin-muxing selection for GPIO236
#define GPIO_GPHMUX1_GPIO237_S   26U
#define GPIO_GPHMUX1_GPIO237_M   0xC000000U    // Defines pin-muxing selection for GPIO237
#define GPIO_GPHMUX1_GPIO238_S   28U
#define GPIO_GPHMUX1_GPIO238_M   0x30000000U   // Defines pin-muxing selection for GPIO238
#define GPIO_GPHMUX1_GPIO239_S   30U
#define GPIO_GPHMUX1_GPIO239_M   0xC0000000U   // Defines pin-muxing selection for GPIO239

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHMUX2 register
//
//*************************************************************************************************
#define GPIO_GPHMUX2_GPIO240_S   0U
#define GPIO_GPHMUX2_GPIO240_M   0x3U         // Defines pin-muxing selection for GPIO240
#define GPIO_GPHMUX2_GPIO241_S   2U
#define GPIO_GPHMUX2_GPIO241_M   0xCU         // Defines pin-muxing selection for GPIO241
#define GPIO_GPHMUX2_GPIO242_S   4U
#define GPIO_GPHMUX2_GPIO242_M   0x30U        // Defines pin-muxing selection for GPIO242
#define GPIO_GPHMUX2_GPIO244_S   8U
#define GPIO_GPHMUX2_GPIO244_M   0x300U       // Defines pin-muxing selection for GPIO244
#define GPIO_GPHMUX2_GPIO245_S   10U
#define GPIO_GPHMUX2_GPIO245_M   0xC00U       // Defines pin-muxing selection for GPIO245
#define GPIO_GPHMUX2_GPIO247_S   14U
#define GPIO_GPHMUX2_GPIO247_M   0xC000U      // Defines pin-muxing selection for GPIO247
#define GPIO_GPHMUX2_GPIO248_S   16U
#define GPIO_GPHMUX2_GPIO248_M   0x30000U     // Defines pin-muxing selection for GPIO248
#define GPIO_GPHMUX2_GPIO249_S   18U
#define GPIO_GPHMUX2_GPIO249_M   0xC0000U     // Defines pin-muxing selection for GPIO249
#define GPIO_GPHMUX2_GPIO251_S   22U
#define GPIO_GPHMUX2_GPIO251_M   0xC00000U    // Defines pin-muxing selection for GPIO251
#define GPIO_GPHMUX2_GPIO252_S   24U
#define GPIO_GPHMUX2_GPIO252_M   0x3000000U   // Defines pin-muxing selection for GPIO252
#define GPIO_GPHMUX2_GPIO253_S   26U
#define GPIO_GPHMUX2_GPIO253_M   0xC000000U   // Defines pin-muxing selection for GPIO253

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHDIR register
//
//*************************************************************************************************
#define GPIO_GPHDIR_GPIO224   0x1U          // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO225   0x2U          // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO226   0x4U          // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO227   0x8U          // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO228   0x10U         // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO229   0x20U         // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO230   0x40U         // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO231   0x80U         // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO232   0x100U        // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO233   0x200U        // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO234   0x400U        // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO235   0x800U        // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO236   0x1000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO237   0x2000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO238   0x4000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO239   0x8000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO240   0x10000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO241   0x20000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO242   0x40000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO244   0x100000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO245   0x200000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO247   0x800000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO248   0x1000000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO249   0x2000000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO251   0x8000000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO252   0x10000000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPHDIR_GPIO253   0x20000000U   // Defines direction for this pin in GPIO mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHPUD register
//
//*************************************************************************************************
#define GPIO_GPHPUD_GPIO224   0x1U          // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO225   0x2U          // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO226   0x4U          // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO227   0x8U          // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO228   0x10U         // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO229   0x20U         // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO230   0x40U         // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO231   0x80U         // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO232   0x100U        // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO233   0x200U        // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO234   0x400U        // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO235   0x800U        // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO236   0x1000U       // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO237   0x2000U       // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO238   0x4000U       // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO239   0x8000U       // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO240   0x10000U      // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO241   0x20000U      // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO242   0x40000U      // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO244   0x100000U     // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO245   0x200000U     // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO247   0x800000U     // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO248   0x1000000U    // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO249   0x2000000U    // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO251   0x8000000U    // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO252   0x10000000U   // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO253   0x20000000U   // Pull-Up Disable control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHINV register
//
//*************************************************************************************************
#define GPIO_GPHINV_GPIO224   0x1U          // Input inversion control for this pin
#define GPIO_GPHINV_GPIO225   0x2U          // Input inversion control for this pin
#define GPIO_GPHINV_GPIO226   0x4U          // Input inversion control for this pin
#define GPIO_GPHINV_GPIO227   0x8U          // Input inversion control for this pin
#define GPIO_GPHINV_GPIO228   0x10U         // Input inversion control for this pin
#define GPIO_GPHINV_GPIO229   0x20U         // Input inversion control for this pin
#define GPIO_GPHINV_GPIO230   0x40U         // Input inversion control for this pin
#define GPIO_GPHINV_GPIO231   0x80U         // Input inversion control for this pin
#define GPIO_GPHINV_GPIO232   0x100U        // Input inversion control for this pin
#define GPIO_GPHINV_GPIO233   0x200U        // Input inversion control for this pin
#define GPIO_GPHINV_GPIO234   0x400U        // Input inversion control for this pin
#define GPIO_GPHINV_GPIO235   0x800U        // Input inversion control for this pin
#define GPIO_GPHINV_GPIO236   0x1000U       // Input inversion control for this pin
#define GPIO_GPHINV_GPIO237   0x2000U       // Input inversion control for this pin
#define GPIO_GPHINV_GPIO238   0x4000U       // Input inversion control for this pin
#define GPIO_GPHINV_GPIO239   0x8000U       // Input inversion control for this pin
#define GPIO_GPHINV_GPIO240   0x10000U      // Input inversion control for this pin
#define GPIO_GPHINV_GPIO241   0x20000U      // Input inversion control for this pin
#define GPIO_GPHINV_GPIO242   0x40000U      // Input inversion control for this pin
#define GPIO_GPHINV_GPIO244   0x100000U     // Input inversion control for this pin
#define GPIO_GPHINV_GPIO245   0x200000U     // Input inversion control for this pin
#define GPIO_GPHINV_GPIO247   0x800000U     // Input inversion control for this pin
#define GPIO_GPHINV_GPIO248   0x1000000U    // Input inversion control for this pin
#define GPIO_GPHINV_GPIO249   0x2000000U    // Input inversion control for this pin
#define GPIO_GPHINV_GPIO251   0x8000000U    // Input inversion control for this pin
#define GPIO_GPHINV_GPIO252   0x10000000U   // Input inversion control for this pin
#define GPIO_GPHINV_GPIO253   0x20000000U   // Input inversion control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHODR register
//
//*************************************************************************************************
#define GPIO_GPHODR_GPIO224   0x1U          // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO225   0x2U          // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO226   0x4U          // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO227   0x8U          // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO228   0x10U         // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO229   0x20U         // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO230   0x40U         // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO231   0x80U         // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO232   0x100U        // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO233   0x200U        // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO234   0x400U        // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO235   0x800U        // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO236   0x1000U       // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO237   0x2000U       // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO238   0x4000U       // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO239   0x8000U       // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO240   0x10000U      // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO241   0x20000U      // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO242   0x40000U      // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO244   0x100000U     // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO245   0x200000U     // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO247   0x800000U     // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO248   0x1000000U    // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO249   0x2000000U    // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO251   0x8000000U    // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO252   0x10000000U   // Output Open-Drain control for this pin
#define GPIO_GPHODR_GPIO253   0x20000000U   // Output Open-Drain control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHAMSEL register
//
//*************************************************************************************************
#define GPIO_GPHAMSEL_GPIO224   0x1U          // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO225   0x2U          // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO226   0x4U          // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO227   0x8U          // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO228   0x10U         // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO229   0x20U         // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO230   0x40U         // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO231   0x80U         // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO232   0x100U        // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO233   0x200U        // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO234   0x400U        // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO235   0x800U        // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO236   0x1000U       // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO237   0x2000U       // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO238   0x4000U       // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO239   0x8000U       // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO240   0x10000U      // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO241   0x20000U      // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO242   0x40000U      // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO244   0x100000U     // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO245   0x200000U     // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO247   0x800000U     // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO248   0x1000000U    // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO249   0x2000000U    // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO251   0x8000000U    // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO252   0x10000000U   // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO253   0x20000000U   // Analog Mode select for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHGMUX1 register
//
//*************************************************************************************************
#define GPIO_GPHGMUX1_GPIO224_S   0U
#define GPIO_GPHGMUX1_GPIO224_M   0x3U          // Defines pin-muxing selection for GPIO224
#define GPIO_GPHGMUX1_GPIO225_S   2U
#define GPIO_GPHGMUX1_GPIO225_M   0xCU          // Defines pin-muxing selection for GPIO225
#define GPIO_GPHGMUX1_GPIO226_S   4U
#define GPIO_GPHGMUX1_GPIO226_M   0x30U         // Defines pin-muxing selection for GPIO226
#define GPIO_GPHGMUX1_GPIO227_S   6U
#define GPIO_GPHGMUX1_GPIO227_M   0xC0U         // Defines pin-muxing selection for GPIO227
#define GPIO_GPHGMUX1_GPIO228_S   8U
#define GPIO_GPHGMUX1_GPIO228_M   0x300U        // Defines pin-muxing selection for GPIO228
#define GPIO_GPHGMUX1_GPIO229_S   10U
#define GPIO_GPHGMUX1_GPIO229_M   0xC00U        // Defines pin-muxing selection for GPIO229
#define GPIO_GPHGMUX1_GPIO230_S   12U
#define GPIO_GPHGMUX1_GPIO230_M   0x3000U       // Defines pin-muxing selection for GPIO230
#define GPIO_GPHGMUX1_GPIO231_S   14U
#define GPIO_GPHGMUX1_GPIO231_M   0xC000U       // Defines pin-muxing selection for GPIO231
#define GPIO_GPHGMUX1_GPIO232_S   16U
#define GPIO_GPHGMUX1_GPIO232_M   0x30000U      // Defines pin-muxing selection for GPIO232
#define GPIO_GPHGMUX1_GPIO233_S   18U
#define GPIO_GPHGMUX1_GPIO233_M   0xC0000U      // Defines pin-muxing selection for GPIO233
#define GPIO_GPHGMUX1_GPIO234_S   20U
#define GPIO_GPHGMUX1_GPIO234_M   0x300000U     // Defines pin-muxing selection for GPIO234
#define GPIO_GPHGMUX1_GPIO235_S   22U
#define GPIO_GPHGMUX1_GPIO235_M   0xC00000U     // Defines pin-muxing selection for GPIO235
#define GPIO_GPHGMUX1_GPIO236_S   24U
#define GPIO_GPHGMUX1_GPIO236_M   0x3000000U    // Defines pin-muxing selection for GPIO236
#define GPIO_GPHGMUX1_GPIO237_S   26U
#define GPIO_GPHGMUX1_GPIO237_M   0xC000000U    // Defines pin-muxing selection for GPIO237
#define GPIO_GPHGMUX1_GPIO238_S   28U
#define GPIO_GPHGMUX1_GPIO238_M   0x30000000U   // Defines pin-muxing selection for GPIO238
#define GPIO_GPHGMUX1_GPIO239_S   30U
#define GPIO_GPHGMUX1_GPIO239_M   0xC0000000U   // Defines pin-muxing selection for GPIO239

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHGMUX2 register
//
//*************************************************************************************************
#define GPIO_GPHGMUX2_GPIO240_S   0U
#define GPIO_GPHGMUX2_GPIO240_M   0x3U         // Defines pin-muxing selection for GPIO240
#define GPIO_GPHGMUX2_GPIO241_S   2U
#define GPIO_GPHGMUX2_GPIO241_M   0xCU         // Defines pin-muxing selection for GPIO241
#define GPIO_GPHGMUX2_GPIO242_S   4U
#define GPIO_GPHGMUX2_GPIO242_M   0x30U        // Defines pin-muxing selection for GPIO242
#define GPIO_GPHGMUX2_GPIO244_S   8U
#define GPIO_GPHGMUX2_GPIO244_M   0x300U       // Defines pin-muxing selection for GPIO244
#define GPIO_GPHGMUX2_GPIO245_S   10U
#define GPIO_GPHGMUX2_GPIO245_M   0xC00U       // Defines pin-muxing selection for GPIO245
#define GPIO_GPHGMUX2_GPIO247_S   14U
#define GPIO_GPHGMUX2_GPIO247_M   0xC000U      // Defines pin-muxing selection for GPIO247
#define GPIO_GPHGMUX2_GPIO248_S   16U
#define GPIO_GPHGMUX2_GPIO248_M   0x30000U     // Defines pin-muxing selection for GPIO248
#define GPIO_GPHGMUX2_GPIO249_S   18U
#define GPIO_GPHGMUX2_GPIO249_M   0xC0000U     // Defines pin-muxing selection for GPIO249
#define GPIO_GPHGMUX2_GPIO251_S   22U
#define GPIO_GPHGMUX2_GPIO251_M   0xC00000U    // Defines pin-muxing selection for GPIO251
#define GPIO_GPHGMUX2_GPIO252_S   24U
#define GPIO_GPHGMUX2_GPIO252_M   0x3000000U   // Defines pin-muxing selection for GPIO252
#define GPIO_GPHGMUX2_GPIO253_S   26U
#define GPIO_GPHGMUX2_GPIO253_M   0xC000000U   // Defines pin-muxing selection for GPIO253

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHCSEL1 register
//
//*************************************************************************************************
#define GPIO_GPHCSEL1_GPIO224_S   0U
#define GPIO_GPHCSEL1_GPIO224_M   0xFU          // GPIO224 Controller CPU Select
#define GPIO_GPHCSEL1_GPIO225_S   4U
#define GPIO_GPHCSEL1_GPIO225_M   0xF0U         // GPIO225 Controller CPU Select
#define GPIO_GPHCSEL1_GPIO226_S   8U
#define GPIO_GPHCSEL1_GPIO226_M   0xF00U        // GPIO226 Controller CPU Select
#define GPIO_GPHCSEL1_GPIO227_S   12U
#define GPIO_GPHCSEL1_GPIO227_M   0xF000U       // GPIO227 Controller CPU Select
#define GPIO_GPHCSEL1_GPIO228_S   16U
#define GPIO_GPHCSEL1_GPIO228_M   0xF0000U      // GPIO228 Controller CPU Select
#define GPIO_GPHCSEL1_GPIO229_S   20U
#define GPIO_GPHCSEL1_GPIO229_M   0xF00000U     // GPIO229 Controller CPU Select
#define GPIO_GPHCSEL1_GPIO230_S   24U
#define GPIO_GPHCSEL1_GPIO230_M   0xF000000U    // GPIO230 Controller CPU Select
#define GPIO_GPHCSEL1_GPIO231_S   28U
#define GPIO_GPHCSEL1_GPIO231_M   0xF0000000U   // GPIO231 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHCSEL2 register
//
//*************************************************************************************************
#define GPIO_GPHCSEL2_GPIO232_S   0U
#define GPIO_GPHCSEL2_GPIO232_M   0xFU          // GPIO232 Controller CPU Select
#define GPIO_GPHCSEL2_GPIO233_S   4U
#define GPIO_GPHCSEL2_GPIO233_M   0xF0U         // GPIO233 Controller CPU Select
#define GPIO_GPHCSEL2_GPIO234_S   8U
#define GPIO_GPHCSEL2_GPIO234_M   0xF00U        // GPIO234 Controller CPU Select
#define GPIO_GPHCSEL2_GPIO235_S   12U
#define GPIO_GPHCSEL2_GPIO235_M   0xF000U       // GPIO235 Controller CPU Select
#define GPIO_GPHCSEL2_GPIO236_S   16U
#define GPIO_GPHCSEL2_GPIO236_M   0xF0000U      // GPIO236 Controller CPU Select
#define GPIO_GPHCSEL2_GPIO237_S   20U
#define GPIO_GPHCSEL2_GPIO237_M   0xF00000U     // GPIO237 Controller CPU Select
#define GPIO_GPHCSEL2_GPIO238_S   24U
#define GPIO_GPHCSEL2_GPIO238_M   0xF000000U    // GPIO238 Controller CPU Select
#define GPIO_GPHCSEL2_GPIO239_S   28U
#define GPIO_GPHCSEL2_GPIO239_M   0xF0000000U   // GPIO239 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHCSEL3 register
//
//*************************************************************************************************
#define GPIO_GPHCSEL3_GPIO240_S   0U
#define GPIO_GPHCSEL3_GPIO240_M   0xFU          // GPIO240 Controller CPU Select
#define GPIO_GPHCSEL3_GPIO241_S   4U
#define GPIO_GPHCSEL3_GPIO241_M   0xF0U         // GPIO241 Controller CPU Select
#define GPIO_GPHCSEL3_GPIO242_S   8U
#define GPIO_GPHCSEL3_GPIO242_M   0xF00U        // GPIO242 Controller CPU Select
#define GPIO_GPHCSEL3_GPIO244_S   16U
#define GPIO_GPHCSEL3_GPIO244_M   0xF0000U      // GPIO244 Controller CPU Select
#define GPIO_GPHCSEL3_GPIO245_S   20U
#define GPIO_GPHCSEL3_GPIO245_M   0xF00000U     // GPIO245 Controller CPU Select
#define GPIO_GPHCSEL3_GPIO247_S   28U
#define GPIO_GPHCSEL3_GPIO247_M   0xF0000000U   // GPIO247 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHCSEL4 register
//
//*************************************************************************************************
#define GPIO_GPHCSEL4_GPIO248_S   0U
#define GPIO_GPHCSEL4_GPIO248_M   0xFU        // GPIO248 Controller CPU Select
#define GPIO_GPHCSEL4_GPIO249_S   4U
#define GPIO_GPHCSEL4_GPIO249_M   0xF0U       // GPIO249 Controller CPU Select
#define GPIO_GPHCSEL4_GPIO251_S   12U
#define GPIO_GPHCSEL4_GPIO251_M   0xF000U     // GPIO251 Controller CPU Select
#define GPIO_GPHCSEL4_GPIO252_S   16U
#define GPIO_GPHCSEL4_GPIO252_M   0xF0000U    // GPIO252 Controller CPU Select
#define GPIO_GPHCSEL4_GPIO253_S   20U
#define GPIO_GPHCSEL4_GPIO253_M   0xF00000U   // GPIO253 Controller CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHLOCK register
//
//*************************************************************************************************
#define GPIO_GPHLOCK_GPIO224   0x1U          // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO225   0x2U          // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO226   0x4U          // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO227   0x8U          // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO228   0x10U         // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO229   0x20U         // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO230   0x40U         // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO231   0x80U         // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO232   0x100U        // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO233   0x200U        // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO234   0x400U        // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO235   0x800U        // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO236   0x1000U       // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO237   0x2000U       // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO238   0x4000U       // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO239   0x8000U       // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO240   0x10000U      // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO241   0x20000U      // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO242   0x40000U      // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO244   0x100000U     // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO245   0x200000U     // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO247   0x800000U     // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO248   0x1000000U    // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO249   0x2000000U    // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO251   0x8000000U    // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO252   0x10000000U   // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO253   0x20000000U   // Configuration Lock bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHCR register
//
//*************************************************************************************************
#define GPIO_GPHCR_GPIO224   0x1U          // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO225   0x2U          // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO226   0x4U          // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO227   0x8U          // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO228   0x10U         // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO229   0x20U         // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO230   0x40U         // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO231   0x80U         // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO232   0x100U        // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO233   0x200U        // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO234   0x400U        // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO235   0x800U        // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO236   0x1000U       // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO237   0x2000U       // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO238   0x4000U       // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO239   0x8000U       // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO240   0x10000U      // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO241   0x20000U      // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO242   0x40000U      // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO244   0x100000U     // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO245   0x200000U     // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO247   0x800000U     // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO248   0x1000000U    // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO249   0x2000000U    // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO251   0x8000000U    // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO252   0x10000000U   // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO253   0x20000000U   // Configuration lock commit bit for this pin


//*************************************************************************************************
//
// The following are defines for the bit fields in the GPADAT register
//
//*************************************************************************************************
#define GPIO_GPADAT_GPIO0    0x1U          // Data Register for this pin
#define GPIO_GPADAT_GPIO1    0x2U          // Data Register for this pin
#define GPIO_GPADAT_GPIO2    0x4U          // Data Register for this pin
#define GPIO_GPADAT_GPIO3    0x8U          // Data Register for this pin
#define GPIO_GPADAT_GPIO4    0x10U         // Data Register for this pin
#define GPIO_GPADAT_GPIO5    0x20U         // Data Register for this pin
#define GPIO_GPADAT_GPIO6    0x40U         // Data Register for this pin
#define GPIO_GPADAT_GPIO7    0x80U         // Data Register for this pin
#define GPIO_GPADAT_GPIO8    0x100U        // Data Register for this pin
#define GPIO_GPADAT_GPIO9    0x200U        // Data Register for this pin
#define GPIO_GPADAT_GPIO10   0x400U        // Data Register for this pin
#define GPIO_GPADAT_GPIO11   0x800U        // Data Register for this pin
#define GPIO_GPADAT_GPIO12   0x1000U       // Data Register for this pin
#define GPIO_GPADAT_GPIO13   0x2000U       // Data Register for this pin
#define GPIO_GPADAT_GPIO14   0x4000U       // Data Register for this pin
#define GPIO_GPADAT_GPIO15   0x8000U       // Data Register for this pin
#define GPIO_GPADAT_GPIO16   0x10000U      // Data Register for this pin
#define GPIO_GPADAT_GPIO17   0x20000U      // Data Register for this pin
#define GPIO_GPADAT_GPIO18   0x40000U      // Data Register for this pin
#define GPIO_GPADAT_GPIO19   0x80000U      // Data Register for this pin
#define GPIO_GPADAT_GPIO20   0x100000U     // Data Register for this pin
#define GPIO_GPADAT_GPIO21   0x200000U     // Data Register for this pin
#define GPIO_GPADAT_GPIO22   0x400000U     // Data Register for this pin
#define GPIO_GPADAT_GPIO23   0x800000U     // Data Register for this pin
#define GPIO_GPADAT_GPIO24   0x1000000U    // Data Register for this pin
#define GPIO_GPADAT_GPIO25   0x2000000U    // Data Register for this pin
#define GPIO_GPADAT_GPIO26   0x4000000U    // Data Register for this pin
#define GPIO_GPADAT_GPIO27   0x8000000U    // Data Register for this pin
#define GPIO_GPADAT_GPIO28   0x10000000U   // Data Register for this pin
#define GPIO_GPADAT_GPIO29   0x20000000U   // Data Register for this pin
#define GPIO_GPADAT_GPIO30   0x40000000U   // Data Register for this pin
#define GPIO_GPADAT_GPIO31   0x80000000U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPASET register
//
//*************************************************************************************************
#define GPIO_GPASET_GPIO0    0x1U          // Output Set bit for this pin
#define GPIO_GPASET_GPIO1    0x2U          // Output Set bit for this pin
#define GPIO_GPASET_GPIO2    0x4U          // Output Set bit for this pin
#define GPIO_GPASET_GPIO3    0x8U          // Output Set bit for this pin
#define GPIO_GPASET_GPIO4    0x10U         // Output Set bit for this pin
#define GPIO_GPASET_GPIO5    0x20U         // Output Set bit for this pin
#define GPIO_GPASET_GPIO6    0x40U         // Output Set bit for this pin
#define GPIO_GPASET_GPIO7    0x80U         // Output Set bit for this pin
#define GPIO_GPASET_GPIO8    0x100U        // Output Set bit for this pin
#define GPIO_GPASET_GPIO9    0x200U        // Output Set bit for this pin
#define GPIO_GPASET_GPIO10   0x400U        // Output Set bit for this pin
#define GPIO_GPASET_GPIO11   0x800U        // Output Set bit for this pin
#define GPIO_GPASET_GPIO12   0x1000U       // Output Set bit for this pin
#define GPIO_GPASET_GPIO13   0x2000U       // Output Set bit for this pin
#define GPIO_GPASET_GPIO14   0x4000U       // Output Set bit for this pin
#define GPIO_GPASET_GPIO15   0x8000U       // Output Set bit for this pin
#define GPIO_GPASET_GPIO16   0x10000U      // Output Set bit for this pin
#define GPIO_GPASET_GPIO17   0x20000U      // Output Set bit for this pin
#define GPIO_GPASET_GPIO18   0x40000U      // Output Set bit for this pin
#define GPIO_GPASET_GPIO19   0x80000U      // Output Set bit for this pin
#define GPIO_GPASET_GPIO20   0x100000U     // Output Set bit for this pin
#define GPIO_GPASET_GPIO21   0x200000U     // Output Set bit for this pin
#define GPIO_GPASET_GPIO22   0x400000U     // Output Set bit for this pin
#define GPIO_GPASET_GPIO23   0x800000U     // Output Set bit for this pin
#define GPIO_GPASET_GPIO24   0x1000000U    // Output Set bit for this pin
#define GPIO_GPASET_GPIO25   0x2000000U    // Output Set bit for this pin
#define GPIO_GPASET_GPIO26   0x4000000U    // Output Set bit for this pin
#define GPIO_GPASET_GPIO27   0x8000000U    // Output Set bit for this pin
#define GPIO_GPASET_GPIO28   0x10000000U   // Output Set bit for this pin
#define GPIO_GPASET_GPIO29   0x20000000U   // Output Set bit for this pin
#define GPIO_GPASET_GPIO30   0x40000000U   // Output Set bit for this pin
#define GPIO_GPASET_GPIO31   0x80000000U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACLEAR register
//
//*************************************************************************************************
#define GPIO_GPACLEAR_GPIO0    0x1U          // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO1    0x2U          // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO2    0x4U          // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO3    0x8U          // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO4    0x10U         // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO5    0x20U         // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO6    0x40U         // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO7    0x80U         // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO8    0x100U        // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO9    0x200U        // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO10   0x400U        // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO11   0x800U        // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO12   0x1000U       // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO13   0x2000U       // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO14   0x4000U       // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO15   0x8000U       // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO16   0x10000U      // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO17   0x20000U      // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO18   0x40000U      // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO19   0x80000U      // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO20   0x100000U     // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO21   0x200000U     // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO22   0x400000U     // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO23   0x800000U     // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO24   0x1000000U    // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO25   0x2000000U    // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO26   0x4000000U    // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO27   0x8000000U    // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO28   0x10000000U   // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO29   0x20000000U   // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO30   0x40000000U   // Output Clear bit for this pin
#define GPIO_GPACLEAR_GPIO31   0x80000000U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPATOGGLE register
//
//*************************************************************************************************
#define GPIO_GPATOGGLE_GPIO0    0x1U          // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO1    0x2U          // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO2    0x4U          // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO3    0x8U          // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO4    0x10U         // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO5    0x20U         // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO6    0x40U         // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO7    0x80U         // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO8    0x100U        // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO9    0x200U        // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO10   0x400U        // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO11   0x800U        // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO12   0x1000U       // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO13   0x2000U       // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO14   0x4000U       // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO15   0x8000U       // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO16   0x10000U      // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO17   0x20000U      // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO18   0x40000U      // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO19   0x80000U      // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO20   0x100000U     // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO21   0x200000U     // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO22   0x400000U     // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO23   0x800000U     // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO24   0x1000000U    // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO25   0x2000000U    // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO26   0x4000000U    // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO27   0x8000000U    // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO28   0x10000000U   // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO29   0x20000000U   // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO30   0x40000000U   // Output Toggle bit for this pin
#define GPIO_GPATOGGLE_GPIO31   0x80000000U   // Output Toggle bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBDAT register
//
//*************************************************************************************************
#define GPIO_GPBDAT_GPIO32   0x1U          // Data Register for this pin
#define GPIO_GPBDAT_GPIO33   0x2U          // Data Register for this pin
#define GPIO_GPBDAT_GPIO34   0x4U          // Data Register for this pin
#define GPIO_GPBDAT_GPIO35   0x8U          // Data Register for this pin
#define GPIO_GPBDAT_GPIO37   0x20U         // Data Register for this pin
#define GPIO_GPBDAT_GPIO40   0x100U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO41   0x200U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO42   0x400U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO43   0x800U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO44   0x1000U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO45   0x2000U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO46   0x4000U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO47   0x8000U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO48   0x10000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO49   0x20000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO50   0x40000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO51   0x80000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO52   0x100000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO53   0x200000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO54   0x400000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO55   0x800000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO56   0x1000000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO57   0x2000000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO58   0x4000000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO59   0x8000000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO60   0x10000000U   // Data Register for this pin
#define GPIO_GPBDAT_GPIO61   0x20000000U   // Data Register for this pin
#define GPIO_GPBDAT_GPIO62   0x40000000U   // Data Register for this pin
#define GPIO_GPBDAT_GPIO63   0x80000000U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBSET register
//
//*************************************************************************************************
#define GPIO_GPBSET_GPIO32   0x1U          // Output Set bit for this pin
#define GPIO_GPBSET_GPIO33   0x2U          // Output Set bit for this pin
#define GPIO_GPBSET_GPIO34   0x4U          // Output Set bit for this pin
#define GPIO_GPBSET_GPIO35   0x8U          // Output Set bit for this pin
#define GPIO_GPBSET_GPIO37   0x20U         // Output Set bit for this pin
#define GPIO_GPBSET_GPIO40   0x100U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO41   0x200U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO42   0x400U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO43   0x800U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO44   0x1000U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO45   0x2000U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO46   0x4000U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO47   0x8000U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO48   0x10000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO49   0x20000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO50   0x40000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO51   0x80000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO52   0x100000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO53   0x200000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO54   0x400000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO55   0x800000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO56   0x1000000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO57   0x2000000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO58   0x4000000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO59   0x8000000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO60   0x10000000U   // Output Set bit for this pin
#define GPIO_GPBSET_GPIO61   0x20000000U   // Output Set bit for this pin
#define GPIO_GPBSET_GPIO62   0x40000000U   // Output Set bit for this pin
#define GPIO_GPBSET_GPIO63   0x80000000U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCLEAR register
//
//*************************************************************************************************
#define GPIO_GPBCLEAR_GPIO32   0x1U          // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO33   0x2U          // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO34   0x4U          // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO35   0x8U          // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO37   0x20U         // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO40   0x100U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO41   0x200U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO42   0x400U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO43   0x800U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO44   0x1000U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO45   0x2000U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO46   0x4000U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO47   0x8000U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO48   0x10000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO49   0x20000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO50   0x40000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO51   0x80000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO52   0x100000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO53   0x200000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO54   0x400000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO55   0x800000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO56   0x1000000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO57   0x2000000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO58   0x4000000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO59   0x8000000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO60   0x10000000U   // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO61   0x20000000U   // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO62   0x40000000U   // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO63   0x80000000U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBTOGGLE register
//
//*************************************************************************************************
#define GPIO_GPBTOGGLE_GPIO32   0x1U          // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO33   0x2U          // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO34   0x4U          // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO35   0x8U          // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO37   0x20U         // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO40   0x100U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO41   0x200U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO42   0x400U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO43   0x800U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO44   0x1000U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO45   0x2000U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO46   0x4000U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO47   0x8000U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO48   0x10000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO49   0x20000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO50   0x40000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO51   0x80000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO52   0x100000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO53   0x200000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO54   0x400000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO55   0x800000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO56   0x1000000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO57   0x2000000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO58   0x4000000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO59   0x8000000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO60   0x10000000U   // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO61   0x20000000U   // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO62   0x40000000U   // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO63   0x80000000U   // Output Toggle bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCDAT register
//
//*************************************************************************************************
#define GPIO_GPCDAT_GPIO64   0x1U       // Data Register for this pin
#define GPIO_GPCDAT_GPIO65   0x2U       // Data Register for this pin
#define GPIO_GPCDAT_GPIO66   0x4U       // Data Register for this pin
#define GPIO_GPCDAT_GPIO67   0x8U       // Data Register for this pin
#define GPIO_GPCDAT_GPIO68   0x10U      // Data Register for this pin
#define GPIO_GPCDAT_GPIO69   0x20U      // Data Register for this pin
#define GPIO_GPCDAT_GPIO70   0x40U      // Data Register for this pin
#define GPIO_GPCDAT_GPIO71   0x80U      // Data Register for this pin
#define GPIO_GPCDAT_GPIO72   0x100U     // Data Register for this pin
#define GPIO_GPCDAT_GPIO73   0x200U     // Data Register for this pin
#define GPIO_GPCDAT_GPIO74   0x400U     // Data Register for this pin
#define GPIO_GPCDAT_GPIO75   0x800U     // Data Register for this pin
#define GPIO_GPCDAT_GPIO76   0x1000U    // Data Register for this pin
#define GPIO_GPCDAT_GPIO77   0x2000U    // Data Register for this pin
#define GPIO_GPCDAT_GPIO78   0x4000U    // Data Register for this pin
#define GPIO_GPCDAT_GPIO79   0x8000U    // Data Register for this pin
#define GPIO_GPCDAT_GPIO80   0x10000U   // Data Register for this pin
#define GPIO_GPCDAT_GPIO81   0x20000U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCSET register
//
//*************************************************************************************************
#define GPIO_GPCSET_GPIO64   0x1U       // Output Set bit for this pin
#define GPIO_GPCSET_GPIO65   0x2U       // Output Set bit for this pin
#define GPIO_GPCSET_GPIO66   0x4U       // Output Set bit for this pin
#define GPIO_GPCSET_GPIO67   0x8U       // Output Set bit for this pin
#define GPIO_GPCSET_GPIO68   0x10U      // Output Set bit for this pin
#define GPIO_GPCSET_GPIO69   0x20U      // Output Set bit for this pin
#define GPIO_GPCSET_GPIO70   0x40U      // Output Set bit for this pin
#define GPIO_GPCSET_GPIO71   0x80U      // Output Set bit for this pin
#define GPIO_GPCSET_GPIO72   0x100U     // Output Set bit for this pin
#define GPIO_GPCSET_GPIO73   0x200U     // Output Set bit for this pin
#define GPIO_GPCSET_GPIO74   0x400U     // Output Set bit for this pin
#define GPIO_GPCSET_GPIO75   0x800U     // Output Set bit for this pin
#define GPIO_GPCSET_GPIO76   0x1000U    // Output Set bit for this pin
#define GPIO_GPCSET_GPIO77   0x2000U    // Output Set bit for this pin
#define GPIO_GPCSET_GPIO78   0x4000U    // Output Set bit for this pin
#define GPIO_GPCSET_GPIO79   0x8000U    // Output Set bit for this pin
#define GPIO_GPCSET_GPIO80   0x10000U   // Output Set bit for this pin
#define GPIO_GPCSET_GPIO81   0x20000U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCCLEAR register
//
//*************************************************************************************************
#define GPIO_GPCCLEAR_GPIO64   0x1U       // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO65   0x2U       // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO66   0x4U       // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO67   0x8U       // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO68   0x10U      // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO69   0x20U      // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO70   0x40U      // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO71   0x80U      // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO72   0x100U     // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO73   0x200U     // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO74   0x400U     // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO75   0x800U     // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO76   0x1000U    // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO77   0x2000U    // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO78   0x4000U    // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO79   0x8000U    // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO80   0x10000U   // Output Clear bit for this pin
#define GPIO_GPCCLEAR_GPIO81   0x20000U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPCTOGGLE register
//
//*************************************************************************************************
#define GPIO_GPCTOGGLE_GPIO64   0x1U       // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO65   0x2U       // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO66   0x4U       // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO67   0x8U       // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO68   0x10U      // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO69   0x20U      // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO70   0x40U      // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO71   0x80U      // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO72   0x100U     // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO73   0x200U     // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO74   0x400U     // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO75   0x800U     // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO76   0x1000U    // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO77   0x2000U    // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO78   0x4000U    // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO79   0x8000U    // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO80   0x10000U   // Output Toggle bit for this pin
#define GPIO_GPCTOGGLE_GPIO81   0x20000U   // Output Toggle bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGDAT register
//
//*************************************************************************************************
#define GPIO_GPGDAT_GPIO208   0x10000U    // Data Register for this pin
#define GPIO_GPGDAT_GPIO209   0x20000U    // Data Register for this pin
#define GPIO_GPGDAT_GPIO210   0x40000U    // Data Register for this pin
#define GPIO_GPGDAT_GPIO211   0x80000U    // Data Register for this pin
#define GPIO_GPGDAT_GPIO212   0x100000U   // Data Register for this pin
#define GPIO_GPGDAT_GPIO213   0x200000U   // Data Register for this pin
#define GPIO_GPGDAT_GPIO214   0x400000U   // Data Register for this pin
#define GPIO_GPGDAT_GPIO215   0x800000U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGSET register
//
//*************************************************************************************************
#define GPIO_GPGSET_GPIO208   0x10000U    // Output Set bit for this pin
#define GPIO_GPGSET_GPIO209   0x20000U    // Output Set bit for this pin
#define GPIO_GPGSET_GPIO210   0x40000U    // Output Set bit for this pin
#define GPIO_GPGSET_GPIO211   0x80000U    // Output Set bit for this pin
#define GPIO_GPGSET_GPIO212   0x100000U   // Output Set bit for this pin
#define GPIO_GPGSET_GPIO213   0x200000U   // Output Set bit for this pin
#define GPIO_GPGSET_GPIO214   0x400000U   // Output Set bit for this pin
#define GPIO_GPGSET_GPIO215   0x800000U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGCLEAR register
//
//*************************************************************************************************
#define GPIO_GPGCLEAR_GPIO208   0x10000U    // Output Clear bit for this pin
#define GPIO_GPGCLEAR_GPIO209   0x20000U    // Output Clear bit for this pin
#define GPIO_GPGCLEAR_GPIO210   0x40000U    // Output Clear bit for this pin
#define GPIO_GPGCLEAR_GPIO211   0x80000U    // Output Clear bit for this pin
#define GPIO_GPGCLEAR_GPIO212   0x100000U   // Output Clear bit for this pin
#define GPIO_GPGCLEAR_GPIO213   0x200000U   // Output Clear bit for this pin
#define GPIO_GPGCLEAR_GPIO214   0x400000U   // Output Clear bit for this pin
#define GPIO_GPGCLEAR_GPIO215   0x800000U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPGTOGGLE register
//
//*************************************************************************************************
#define GPIO_GPGTOGGLE_GPIO208   0x10000U    // Output Toggle bit for this pin
#define GPIO_GPGTOGGLE_GPIO209   0x20000U    // Output Toggle bit for this pin
#define GPIO_GPGTOGGLE_GPIO210   0x40000U    // Output Toggle bit for this pin
#define GPIO_GPGTOGGLE_GPIO211   0x80000U    // Output Toggle bit for this pin
#define GPIO_GPGTOGGLE_GPIO212   0x100000U   // Output Toggle bit for this pin
#define GPIO_GPGTOGGLE_GPIO213   0x200000U   // Output Toggle bit for this pin
#define GPIO_GPGTOGGLE_GPIO214   0x400000U   // Output Toggle bit for this pin
#define GPIO_GPGTOGGLE_GPIO215   0x800000U   // Output Toggle bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHDAT register
//
//*************************************************************************************************
#define GPIO_GPHDAT_GPIO224   0x1U          // Data Register for this pin
#define GPIO_GPHDAT_GPIO225   0x2U          // Data Register for this pin
#define GPIO_GPHDAT_GPIO226   0x4U          // Data Register for this pin
#define GPIO_GPHDAT_GPIO227   0x8U          // Data Register for this pin
#define GPIO_GPHDAT_GPIO228   0x10U         // Data Register for this pin
#define GPIO_GPHDAT_GPIO229   0x20U         // Data Register for this pin
#define GPIO_GPHDAT_GPIO230   0x40U         // Data Register for this pin
#define GPIO_GPHDAT_GPIO231   0x80U         // Data Register for this pin
#define GPIO_GPHDAT_GPIO232   0x100U        // Data Register for this pin
#define GPIO_GPHDAT_GPIO233   0x200U        // Data Register for this pin
#define GPIO_GPHDAT_GPIO234   0x400U        // Data Register for this pin
#define GPIO_GPHDAT_GPIO235   0x800U        // Data Register for this pin
#define GPIO_GPHDAT_GPIO236   0x1000U       // Data Register for this pin
#define GPIO_GPHDAT_GPIO237   0x2000U       // Data Register for this pin
#define GPIO_GPHDAT_GPIO238   0x4000U       // Data Register for this pin
#define GPIO_GPHDAT_GPIO239   0x8000U       // Data Register for this pin
#define GPIO_GPHDAT_GPIO240   0x10000U      // Data Register for this pin
#define GPIO_GPHDAT_GPIO241   0x20000U      // Data Register for this pin
#define GPIO_GPHDAT_GPIO242   0x40000U      // Data Register for this pin
#define GPIO_GPHDAT_GPIO244   0x100000U     // Data Register for this pin
#define GPIO_GPHDAT_GPIO245   0x200000U     // Data Register for this pin
#define GPIO_GPHDAT_GPIO247   0x800000U     // Data Register for this pin
#define GPIO_GPHDAT_GPIO248   0x1000000U    // Data Register for this pin
#define GPIO_GPHDAT_GPIO249   0x2000000U    // Data Register for this pin
#define GPIO_GPHDAT_GPIO251   0x8000000U    // Data Register for this pin
#define GPIO_GPHDAT_GPIO252   0x10000000U   // Data Register for this pin
#define GPIO_GPHDAT_GPIO253   0x20000000U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHSET register
//
//*************************************************************************************************
#define GPIO_GPHSET_GPIO224   0x1U          // Output Set bit for this pin
#define GPIO_GPHSET_GPIO225   0x2U          // Output Set bit for this pin
#define GPIO_GPHSET_GPIO226   0x4U          // Output Set bit for this pin
#define GPIO_GPHSET_GPIO227   0x8U          // Output Set bit for this pin
#define GPIO_GPHSET_GPIO228   0x10U         // Output Set bit for this pin
#define GPIO_GPHSET_GPIO229   0x20U         // Output Set bit for this pin
#define GPIO_GPHSET_GPIO230   0x40U         // Output Set bit for this pin
#define GPIO_GPHSET_GPIO231   0x80U         // Output Set bit for this pin
#define GPIO_GPHSET_GPIO232   0x100U        // Output Set bit for this pin
#define GPIO_GPHSET_GPIO233   0x200U        // Output Set bit for this pin
#define GPIO_GPHSET_GPIO234   0x400U        // Output Set bit for this pin
#define GPIO_GPHSET_GPIO235   0x800U        // Output Set bit for this pin
#define GPIO_GPHSET_GPIO236   0x1000U       // Output Set bit for this pin
#define GPIO_GPHSET_GPIO237   0x2000U       // Output Set bit for this pin
#define GPIO_GPHSET_GPIO238   0x4000U       // Output Set bit for this pin
#define GPIO_GPHSET_GPIO239   0x8000U       // Output Set bit for this pin
#define GPIO_GPHSET_GPIO240   0x10000U      // Output Set bit for this pin
#define GPIO_GPHSET_GPIO241   0x20000U      // Output Set bit for this pin
#define GPIO_GPHSET_GPIO242   0x40000U      // Output Set bit for this pin
#define GPIO_GPHSET_GPIO244   0x100000U     // Output Set bit for this pin
#define GPIO_GPHSET_GPIO245   0x200000U     // Output Set bit for this pin
#define GPIO_GPHSET_GPIO247   0x800000U     // Output Set bit for this pin
#define GPIO_GPHSET_GPIO248   0x1000000U    // Output Set bit for this pin
#define GPIO_GPHSET_GPIO249   0x2000000U    // Output Set bit for this pin
#define GPIO_GPHSET_GPIO251   0x8000000U    // Output Set bit for this pin
#define GPIO_GPHSET_GPIO252   0x10000000U   // Output Set bit for this pin
#define GPIO_GPHSET_GPIO253   0x20000000U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHCLEAR register
//
//*************************************************************************************************
#define GPIO_GPHCLEAR_GPIO224   0x1U          // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO225   0x2U          // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO226   0x4U          // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO227   0x8U          // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO228   0x10U         // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO229   0x20U         // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO230   0x40U         // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO231   0x80U         // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO232   0x100U        // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO233   0x200U        // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO234   0x400U        // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO235   0x800U        // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO236   0x1000U       // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO237   0x2000U       // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO238   0x4000U       // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO239   0x8000U       // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO240   0x10000U      // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO241   0x20000U      // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO242   0x40000U      // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO244   0x100000U     // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO245   0x200000U     // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO247   0x800000U     // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO248   0x1000000U    // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO249   0x2000000U    // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO251   0x8000000U    // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO252   0x10000000U   // Output Clear bit for this pin
#define GPIO_GPHCLEAR_GPIO253   0x20000000U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHTOGGLE register
//
//*************************************************************************************************
#define GPIO_GPHTOGGLE_GPIO224   0x1U          // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO225   0x2U          // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO226   0x4U          // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO227   0x8U          // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO228   0x10U         // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO229   0x20U         // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO230   0x40U         // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO231   0x80U         // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO232   0x100U        // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO233   0x200U        // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO234   0x400U        // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO235   0x800U        // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO236   0x1000U       // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO237   0x2000U       // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO238   0x4000U       // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO239   0x8000U       // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO240   0x10000U      // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO241   0x20000U      // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO242   0x40000U      // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO244   0x100000U     // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO245   0x200000U     // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO247   0x800000U     // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO248   0x1000000U    // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO249   0x2000000U    // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO251   0x8000000U    // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO252   0x10000000U   // Output Toggle bit for this pin
#define GPIO_GPHTOGGLE_GPIO253   0x20000000U   // Output Toggle bit for this pin




#endif
