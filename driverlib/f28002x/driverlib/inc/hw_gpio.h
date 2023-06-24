//###########################################################################
//
// FILE:    hw_gpio.h
//
// TITLE:   Definitions for the GPIO registers.
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
#define GPIO_O_GPAGMUX1   0x20U    // GPIO A Peripheral Group Mux (GPIO0 to 15)
#define GPIO_O_GPAGMUX2   0x22U    // GPIO A Peripheral Group Mux (GPIO16 to 31)
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
#define GPIO_O_GPBGMUX1   0x60U    // GPIO B Peripheral Group Mux (GPIO32 to 47)
#define GPIO_O_GPBGMUX2   0x62U    // GPIO B Peripheral Group Mux (GPIO48 to 63)
#define GPIO_O_GPBLOCK    0x7CU    // GPIO B Lock Configuration Register (GPIO32 to 63)
#define GPIO_O_GPBCR      0x7EU    // GPIO B Lock Commit Register (GPIO32 to 63)
#define GPIO_O_GPHCTRL    0x1C0U   // GPIO H Qualification Sampling Period Control (GPIO224 to 255)
#define GPIO_O_GPHQSEL1   0x1C2U   // GPIO H Qualifier Select 1 Register (GPIO224 to 239)
#define GPIO_O_GPHQSEL2   0x1C4U   // GPIO H Qualifier Select 2 Register (GPIO240 to 255)
#define GPIO_O_GPHMUX1    0x1C6U   // GPIO H Mux 1 Register (GPIO224 to 239)
#define GPIO_O_GPHMUX2    0x1C8U   // GPIO H Mux 2 Register (GPIO240 to 255)
#define GPIO_O_GPHINV     0x1D0U   // GPIO H Input Polarity Invert Registers (GPIO224 to 255)
#define GPIO_O_GPHAMSEL   0x1D4U   // GPIO H Analog Mode Select register (GPIO224 to GPIO255)
#define GPIO_O_GPHGMUX1   0x1E0U   // GPIO H Peripheral Group Mux (GPIO224 to 239)
#define GPIO_O_GPHGMUX2   0x1E2U   // GPIO H Peripheral Group Mux (GPIO240 to 255)
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
#define GPIO_O_GPHDAT      0x38U   // GPIO H Data Register (GPIO224 to 255)

#define GPIO_O_GPADAT_R   0x0U   // GPIO A Data Read Register
#define GPIO_O_GPBDAT_R   0x2U   // GPIO B Data Read Register
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
#define GPIO_GPAODR_GPIO0    0x1U          // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO1    0x2U          // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO2    0x4U          // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO3    0x8U          // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO4    0x10U         // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO5    0x20U         // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO6    0x40U         // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO7    0x80U         // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO8    0x100U        // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO9    0x200U        // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO10   0x400U        // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO11   0x800U        // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO12   0x1000U       // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO13   0x2000U       // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO14   0x4000U       // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO15   0x8000U       // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO16   0x10000U      // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO17   0x20000U      // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO18   0x40000U      // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO19   0x80000U      // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO22   0x400000U     // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO23   0x800000U     // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO24   0x1000000U    // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO25   0x2000000U    // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO26   0x4000000U    // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO27   0x8000000U    // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO28   0x10000000U   // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO29   0x20000000U   // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO30   0x40000000U   // Outpout Open-Drain control for this pin
#define GPIO_GPAODR_GPIO31   0x80000000U   // Outpout Open-Drain control for this pin

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
#define GPIO_GPBQSEL1_GPIO39_S   14U
#define GPIO_GPBQSEL1_GPIO39_M   0xC000U       // Select input qualification type for GPIO39
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

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBQSEL2 register
//
//*************************************************************************************************
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
#define GPIO_GPBMUX1_GPIO39_S   14U
#define GPIO_GPBMUX1_GPIO39_M   0xC000U       // Defines pin-muxing selection for GPIO39
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

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBMUX2 register
//
//*************************************************************************************************
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
#define GPIO_GPBDIR_GPIO39   0x80U         // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO40   0x100U        // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO41   0x200U        // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO42   0x400U        // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO43   0x800U        // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO44   0x1000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO45   0x2000U       // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO46   0x4000U       // Defines direction for this pin in GPIO mode
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
#define GPIO_GPBPUD_GPIO39   0x80U         // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO40   0x100U        // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO41   0x200U        // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO42   0x400U        // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO43   0x800U        // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO44   0x1000U       // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO45   0x2000U       // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO46   0x4000U       // Pull-Up Disable control for this pin
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
#define GPIO_GPBINV_GPIO39   0x80U         // Input inversion control for this pin
#define GPIO_GPBINV_GPIO40   0x100U        // Input inversion control for this pin
#define GPIO_GPBINV_GPIO41   0x200U        // Input inversion control for this pin
#define GPIO_GPBINV_GPIO42   0x400U        // Input inversion control for this pin
#define GPIO_GPBINV_GPIO43   0x800U        // Input inversion control for this pin
#define GPIO_GPBINV_GPIO44   0x1000U       // Input inversion control for this pin
#define GPIO_GPBINV_GPIO45   0x2000U       // Input inversion control for this pin
#define GPIO_GPBINV_GPIO46   0x4000U       // Input inversion control for this pin
#define GPIO_GPBINV_GPIO61   0x20000000U   // Input inversion control for this pin
#define GPIO_GPBINV_GPIO62   0x40000000U   // Input inversion control for this pin
#define GPIO_GPBINV_GPIO63   0x80000000U   // Input inversion control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBODR register
//
//*************************************************************************************************
#define GPIO_GPBODR_GPIO32   0x1U          // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO33   0x2U          // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO34   0x4U          // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO35   0x8U          // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO37   0x20U         // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO39   0x80U         // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO40   0x100U        // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO41   0x200U        // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO42   0x400U        // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO43   0x800U        // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO44   0x1000U       // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO45   0x2000U       // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO46   0x4000U       // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO61   0x20000000U   // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO62   0x40000000U   // Outpout Open-Drain control for this pin
#define GPIO_GPBODR_GPIO63   0x80000000U   // Outpout Open-Drain control for this pin

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
#define GPIO_GPBGMUX1_GPIO39_S   14U
#define GPIO_GPBGMUX1_GPIO39_M   0xC000U       // Defines pin-muxing selection for GPIO39
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

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBGMUX2 register
//
//*************************************************************************************************
#define GPIO_GPBGMUX2_GPIO61_S   26U
#define GPIO_GPBGMUX2_GPIO61_M   0xC000000U    // Defines pin-muxing selection for GPIO61
#define GPIO_GPBGMUX2_GPIO62_S   28U
#define GPIO_GPBGMUX2_GPIO62_M   0x30000000U   // Defines pin-muxing selection for GPIO62
#define GPIO_GPBGMUX2_GPIO63_S   30U
#define GPIO_GPBGMUX2_GPIO63_M   0xC0000000U   // Defines pin-muxing selection for GPIO63

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
#define GPIO_GPBLOCK_GPIO39   0x80U         // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO40   0x100U        // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO41   0x200U        // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO42   0x400U        // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO43   0x800U        // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO44   0x1000U       // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO45   0x2000U       // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO46   0x4000U       // Configuration Lock bit for this pin
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
#define GPIO_GPBCR_GPIO39   0x80U         // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO40   0x100U        // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO41   0x200U        // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO42   0x400U        // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO43   0x800U        // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO44   0x1000U       // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO45   0x2000U       // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO46   0x4000U       // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO61   0x20000000U   // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO62   0x40000000U   // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO63   0x80000000U   // Configuration lock commit bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHCTRL register
//
//*************************************************************************************************
#define GPIO_GPHCTRL_QUALPRD0_S   0U
#define GPIO_GPHCTRL_QUALPRD0_M   0xFFU       // Qualification sampling period for GPIO224 to
                                              // GPIO231
#define GPIO_GPHCTRL_QUALPRD1_S   8U
#define GPIO_GPHCTRL_QUALPRD1_M   0xFF00U     // Qualification sampling period for GPIO232 to
                                              // GPIO239
#define GPIO_GPHCTRL_QUALPRD2_S   16U
#define GPIO_GPHCTRL_QUALPRD2_M   0xFF0000U   // Qualification sampling period for GPIO240 to
                                              // GPIO247

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
#define GPIO_GPHQSEL2_GPIO241_S   2U
#define GPIO_GPHQSEL2_GPIO241_M   0xCU     // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO242_S   4U
#define GPIO_GPHQSEL2_GPIO242_M   0x30U    // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO244_S   8U
#define GPIO_GPHQSEL2_GPIO244_M   0x300U   // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO245_S   10U
#define GPIO_GPHQSEL2_GPIO245_M   0xC00U   // Select input qualification type for this GPIO Pin

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
#define GPIO_GPHMUX1_GPIO230_S   12U
#define GPIO_GPHMUX1_GPIO230_M   0x3000U       // Defines pin-muxing selection for GPIO230
#define GPIO_GPHMUX1_GPIO231_S   14U
#define GPIO_GPHMUX1_GPIO231_M   0xC000U       // Defines pin-muxing selection for GPIO231
#define GPIO_GPHMUX1_GPIO232_S   16U
#define GPIO_GPHMUX1_GPIO232_M   0x30000U      // Defines pin-muxing selection for GPIO232
#define GPIO_GPHMUX1_GPIO233_S   18U
#define GPIO_GPHMUX1_GPIO233_M   0xC0000U      // Defines pin-muxing selection for GPIO233
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
#define GPIO_GPHMUX2_GPIO241_S   2U
#define GPIO_GPHMUX2_GPIO241_M   0xCU     // Defines pin-muxing selection for GPIO241
#define GPIO_GPHMUX2_GPIO242_S   4U
#define GPIO_GPHMUX2_GPIO242_M   0x30U    // Defines pin-muxing selection for GPIO242
#define GPIO_GPHMUX2_GPIO244_S   8U
#define GPIO_GPHMUX2_GPIO244_M   0x300U   // Defines pin-muxing selection for GPIO244
#define GPIO_GPHMUX2_GPIO245_S   10U
#define GPIO_GPHMUX2_GPIO245_M   0xC00U   // Defines pin-muxing selection for GPIO245

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHINV register
//
//*************************************************************************************************
#define GPIO_GPHINV_GPIO224   0x1U        // Input inversion control for this pin
#define GPIO_GPHINV_GPIO225   0x2U        // Input inversion control for this pin
#define GPIO_GPHINV_GPIO226   0x4U        // Input inversion control for this pin
#define GPIO_GPHINV_GPIO227   0x8U        // Input inversion control for this pin
#define GPIO_GPHINV_GPIO228   0x10U       // Input inversion control for this pin
#define GPIO_GPHINV_GPIO230   0x40U       // Input inversion control for this pin
#define GPIO_GPHINV_GPIO231   0x80U       // Input inversion control for this pin
#define GPIO_GPHINV_GPIO232   0x100U      // Input inversion control for this pin
#define GPIO_GPHINV_GPIO233   0x200U      // Input inversion control for this pin
#define GPIO_GPHINV_GPIO237   0x2000U     // Input inversion control for this pin
#define GPIO_GPHINV_GPIO238   0x4000U     // Input inversion control for this pin
#define GPIO_GPHINV_GPIO239   0x8000U     // Input inversion control for this pin
#define GPIO_GPHINV_GPIO241   0x20000U    // Input inversion control for this pin
#define GPIO_GPHINV_GPIO242   0x40000U    // Input inversion control for this pin
#define GPIO_GPHINV_GPIO244   0x100000U   // Input inversion control for this pin
#define GPIO_GPHINV_GPIO245   0x200000U   // Input inversion control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHAMSEL register
//
//*************************************************************************************************
#define GPIO_GPHAMSEL_GPIO224   0x1U        // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO225   0x2U        // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO226   0x4U        // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO227   0x8U        // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO228   0x10U       // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO230   0x40U       // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO231   0x80U       // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO232   0x100U      // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO233   0x200U      // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO237   0x2000U     // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO238   0x4000U     // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO239   0x8000U     // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO241   0x20000U    // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO242   0x40000U    // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO244   0x100000U   // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO245   0x200000U   // Analog Mode select for this pin

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
#define GPIO_GPHGMUX1_GPIO230_S   12U
#define GPIO_GPHGMUX1_GPIO230_M   0x3000U       // Defines pin-muxing selection for GPIO230
#define GPIO_GPHGMUX1_GPIO231_S   14U
#define GPIO_GPHGMUX1_GPIO231_M   0xC000U       // Defines pin-muxing selection for GPIO231
#define GPIO_GPHGMUX1_GPIO232_S   16U
#define GPIO_GPHGMUX1_GPIO232_M   0x30000U      // Defines pin-muxing selection for GPIO232
#define GPIO_GPHGMUX1_GPIO233_S   18U
#define GPIO_GPHGMUX1_GPIO233_M   0xC0000U      // Defines pin-muxing selection for GPIO233
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
#define GPIO_GPHGMUX2_GPIO241_S   2U
#define GPIO_GPHGMUX2_GPIO241_M   0xCU     // Defines pin-muxing selection for GPIO241
#define GPIO_GPHGMUX2_GPIO242_S   4U
#define GPIO_GPHGMUX2_GPIO242_M   0x30U    // Defines pin-muxing selection for GPIO242
#define GPIO_GPHGMUX2_GPIO244_S   8U
#define GPIO_GPHGMUX2_GPIO244_M   0x300U   // Defines pin-muxing selection for GPIO244
#define GPIO_GPHGMUX2_GPIO245_S   10U
#define GPIO_GPHGMUX2_GPIO245_M   0xC00U   // Defines pin-muxing selection for GPIO245

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHLOCK register
//
//*************************************************************************************************
#define GPIO_GPHLOCK_GPIO224   0x1U        // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO225   0x2U        // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO226   0x4U        // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO227   0x8U        // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO228   0x10U       // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO230   0x40U       // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO231   0x80U       // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO232   0x100U      // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO233   0x200U      // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO237   0x2000U     // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO238   0x4000U     // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO239   0x8000U     // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO241   0x20000U    // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO242   0x40000U    // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO244   0x100000U   // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO245   0x200000U   // Configuration Lock bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHCR register
//
//*************************************************************************************************
#define GPIO_GPHCR_GPIO224   0x1U        // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO225   0x2U        // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO226   0x4U        // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO227   0x8U        // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO228   0x10U       // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO230   0x40U       // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO231   0x80U       // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO232   0x100U      // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO233   0x200U      // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO237   0x2000U     // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO238   0x4000U     // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO239   0x8000U     // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO241   0x20000U    // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO242   0x40000U    // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO244   0x100000U   // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO245   0x200000U   // Configuration lock commit bit for this pin


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
#define GPIO_GPBDAT_GPIO39   0x80U         // Data Register for this pin
#define GPIO_GPBDAT_GPIO40   0x100U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO41   0x200U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO42   0x400U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO43   0x800U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO44   0x1000U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO45   0x2000U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO46   0x4000U       // Data Register for this pin
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
#define GPIO_GPBSET_GPIO39   0x80U         // Output Set bit for this pin
#define GPIO_GPBSET_GPIO40   0x100U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO41   0x200U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO42   0x400U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO43   0x800U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO44   0x1000U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO45   0x2000U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO46   0x4000U       // Output Set bit for this pin
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
#define GPIO_GPBCLEAR_GPIO39   0x80U         // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO40   0x100U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO41   0x200U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO42   0x400U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO43   0x800U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO44   0x1000U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO45   0x2000U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO46   0x4000U       // Output Clear bit for this pin
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
#define GPIO_GPBTOGGLE_GPIO39   0x80U         // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO40   0x100U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO41   0x200U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO42   0x400U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO43   0x800U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO44   0x1000U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO45   0x2000U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO46   0x4000U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO61   0x20000000U   // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO62   0x40000000U   // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO63   0x80000000U   // Output Toggle bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHDAT register
//
//*************************************************************************************************
#define GPIO_GPHDAT_GPIO224   0x1U        // Data Register for this pin
#define GPIO_GPHDAT_GPIO225   0x2U        // Data Register for this pin
#define GPIO_GPHDAT_GPIO226   0x4U        // Data Register for this pin
#define GPIO_GPHDAT_GPIO227   0x8U        // Data Register for this pin
#define GPIO_GPHDAT_GPIO228   0x10U       // Data Register for this pin
#define GPIO_GPHDAT_GPIO230   0x40U       // Data Register for this pin
#define GPIO_GPHDAT_GPIO231   0x80U       // Data Register for this pin
#define GPIO_GPHDAT_GPIO232   0x100U      // Data Register for this pin
#define GPIO_GPHDAT_GPIO233   0x200U      // Data Register for this pin
#define GPIO_GPHDAT_GPIO237   0x2000U     // Data Register for this pin
#define GPIO_GPHDAT_GPIO238   0x4000U     // Data Register for this pin
#define GPIO_GPHDAT_GPIO239   0x8000U     // Data Register for this pin
#define GPIO_GPHDAT_GPIO241   0x20000U    // Data Register for this pin
#define GPIO_GPHDAT_GPIO242   0x40000U    // Data Register for this pin
#define GPIO_GPHDAT_GPIO244   0x100000U   // Data Register for this pin
#define GPIO_GPHDAT_GPIO245   0x200000U   // Data Register for this pin




#endif
