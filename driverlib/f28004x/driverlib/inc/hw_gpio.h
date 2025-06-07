//###########################################################################
//
// FILE:    hw_gpio.h
//
// TITLE:   Definitions for the GPIO registers.
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

#ifndef HW_GPIO_H
#define HW_GPIO_H

//*************************************************************************************************
//
// The following are defines for the GPIO register offsets
//
//*************************************************************************************************
#define GPIO_O_GPACTRL    0x0U     // GPIO A Qualification Sampling Period (GPIO0 to GPIO31)
#define GPIO_O_GPAQSEL1   0x2U     // GPIO A Qualification Type (GPIO0 to GPIO15)
#define GPIO_O_GPAQSEL2   0x4U     // GPIO A Qualification Type (GPIO16 to GPIO31)
#define GPIO_O_GPAMUX1    0x6U     // GPIO A Peripheral Mux (GPIO0 to GPIO15)
#define GPIO_O_GPAMUX2    0x8U     // GPIO A Peripheral Mux (GPIO16 to GPIO31)
#define GPIO_O_GPADIR     0xAU     // GPIO A Direction (GPIO0 to GPIO31)
#define GPIO_O_GPAPUD     0xCU     // GPIO A Pull-Up Disable (GPIO0 to GPIO31)
#define GPIO_O_GPAINV     0x10U    // GPIO A Input Inversion (GPIO0 to GPIO31)
#define GPIO_O_GPAODR     0x12U    // GPIO A Open Drain Output Mode (GPIO0 to GPIO31)
#define GPIO_O_GPAAMSEL   0x14U    // GPIO A Analog Mode Select (GPIO0 to GPIO31)
#define GPIO_O_GPAGMUX1   0x20U    // GPIO A Peripheral Group Mux (GPIO0 to GPIO15)
#define GPIO_O_GPAGMUX2   0x22U    // GPIO A Peripheral Group Mux (GPIO16 to GPIO31)
#define GPIO_O_GPACSEL1   0x28U    // GPIO A Master Core Select (GPIO0 to GPIO7)
#define GPIO_O_GPACSEL2   0x2AU    // GPIO A Master Core Select (GPIO8 to GPIO15)
#define GPIO_O_GPACSEL3   0x2CU    // GPIO A Master Core Select (GPIO16 to GPIO23)
#define GPIO_O_GPACSEL4   0x2EU    // GPIO A Master Core Select (GPIO24 to GPIO31)
#define GPIO_O_GPALOCK    0x3CU    // GPIO A Lock Register (GPIO0 to GPIO31)
#define GPIO_O_GPACR      0x3EU    // GPIO A Lock Commit Register (GPIO0 to GPIO31)
#define GPIO_O_GPBCTRL    0x40U    // GPIO B Qualification Sampling Period (GPIO32 to GPIO63)
#define GPIO_O_GPBQSEL1   0x42U    // GPIO B Qualification Type (GPIO32 to GPIO47)
#define GPIO_O_GPBQSEL2   0x44U    // GPIO B Qualification Type (GPIO48 to GPIO63)
#define GPIO_O_GPBMUX1    0x46U    // GPIO B Peripheral Mux (GPIO32 to GPIO47)
#define GPIO_O_GPBMUX2    0x48U    // GPIO B Peripheral Mux (GPIO48 to GPIO63)
#define GPIO_O_GPBDIR     0x4AU    // GPIO B Direction (GPIO32 to GPIO63)
#define GPIO_O_GPBPUD     0x4CU    // GPIO B Pull-Up Disable (GPIO32 to GPIO63)
#define GPIO_O_GPBINV     0x50U    // GPIO B Input Inversion (GPIO32 to GPIO63)
#define GPIO_O_GPBODR     0x52U    // GPIO B Open Drain Output Mode (GPIO32 to GPIO63)
#define GPIO_O_GPBGMUX1   0x60U    // GPIO B Peripheral Group Mux (GPIO32 to GPIO47)
#define GPIO_O_GPBGMUX2   0x62U    // GPIO B Peripheral Group Mux (GPIO48 to GPIO63)
#define GPIO_O_GPBCSEL1   0x68U    // GPIO B Master Core Select (GPIO32 to GPIO39)
#define GPIO_O_GPBCSEL2   0x6AU    // GPIO B Master Core Select (GPIO40 to GPIO47)
#define GPIO_O_GPBCSEL3   0x6CU    // GPIO B Master Core Select (GPIO48 to GPIO55)
#define GPIO_O_GPBCSEL4   0x6EU    // GPIO B Master Core Select (GPIO56 to GPIO63)
#define GPIO_O_GPBLOCK    0x7CU    // GPIO B Lock Register (GPIO32 to GPIO63)
#define GPIO_O_GPBCR      0x7EU    // GPIO B Lock Commit Register (GPIO32 to GPIO63)
#define GPIO_O_GPHCTRL    0x1C0U   // GPIO H Qualification Sampling Period (GPIO224 to GPIO255)
#define GPIO_O_GPHQSEL1   0x1C2U   // GPIO H Qualification Type (GPIO224 to GPIO239)
#define GPIO_O_GPHQSEL2   0x1C4U   // GPIO H Qualification Type (GPIO240 to GPIO255)
#define GPIO_O_GPHPUD     0x1CCU   // GPIO H Pull-Up Disable (GPIO224 to GPIO255)
#define GPIO_O_GPHINV     0x1D0U   // GPIO H Input Inversion (GPIO224 to GPIO255)
#define GPIO_O_GPHAMSEL   0x1D4U   // GPIO H Analog Mode Select (GPIO224 to GPIO255)
#define GPIO_O_GPHLOCK    0x1FCU   // GPIO H Lock Register (GPIO224 to GPIO255)
#define GPIO_O_GPHCR      0x1FEU   // GPIO H Lock Commit Register (GPIO224 to GPIO255)

#define GPIO_O_GPADAT      0x0U    // GPIO A Data Register (GPIO0 to GPIO31)
#define GPIO_O_GPASET      0x2U    // GPIO A Output Set (GPIO0 to GPIO31)
#define GPIO_O_GPACLEAR    0x4U    // GPIO A Output Clear (GPIO0 to GPIO31)
#define GPIO_O_GPATOGGLE   0x6U    // GPIO A Output Toggle (GPIO0 to GPIO31)
#define GPIO_O_GPBDAT      0x8U    // GPIO B Data Register (GPIO32 to GPIO64)
#define GPIO_O_GPBSET      0xAU    // GPIO B Output Set (GPIO32 to GPIO64)
#define GPIO_O_GPBCLEAR    0xCU    // GPIO B Output Clear (GPIO32 to GPIO64)
#define GPIO_O_GPBTOGGLE   0xEU    // GPIO B Output Toggle (GPIO32 to GPIO64)
#define GPIO_O_GPHDAT      0x38U   // GPIO H Data Register (GPIO0 to GPIO255)


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
#define GPIO_GPAAMSEL_GPIO22   0x400000U   // Analog Mode select for this pin
#define GPIO_GPAAMSEL_GPIO23   0x800000U   // Analog Mode select for this pin

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
#define GPIO_GPACSEL1_GPIO0_M   0xFU          // GPIO0 Master CPU Select
#define GPIO_GPACSEL1_GPIO1_S   4U
#define GPIO_GPACSEL1_GPIO1_M   0xF0U         // GPIO1 Master CPU Select
#define GPIO_GPACSEL1_GPIO2_S   8U
#define GPIO_GPACSEL1_GPIO2_M   0xF00U        // GPIO2 Master CPU Select
#define GPIO_GPACSEL1_GPIO3_S   12U
#define GPIO_GPACSEL1_GPIO3_M   0xF000U       // GPIO3 Master CPU Select
#define GPIO_GPACSEL1_GPIO4_S   16U
#define GPIO_GPACSEL1_GPIO4_M   0xF0000U      // GPIO4 Master CPU Select
#define GPIO_GPACSEL1_GPIO5_S   20U
#define GPIO_GPACSEL1_GPIO5_M   0xF00000U     // GPIO5 Master CPU Select
#define GPIO_GPACSEL1_GPIO6_S   24U
#define GPIO_GPACSEL1_GPIO6_M   0xF000000U    // GPIO6 Master CPU Select
#define GPIO_GPACSEL1_GPIO7_S   28U
#define GPIO_GPACSEL1_GPIO7_M   0xF0000000U   // GPIO7 Master CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACSEL2 register
//
//*************************************************************************************************
#define GPIO_GPACSEL2_GPIO8_S    0U
#define GPIO_GPACSEL2_GPIO8_M    0xFU          // GPIO8 Master CPU Select
#define GPIO_GPACSEL2_GPIO9_S    4U
#define GPIO_GPACSEL2_GPIO9_M    0xF0U         // GPIO9 Master CPU Select
#define GPIO_GPACSEL2_GPIO10_S   8U
#define GPIO_GPACSEL2_GPIO10_M   0xF00U        // GPIO10 Master CPU Select
#define GPIO_GPACSEL2_GPIO11_S   12U
#define GPIO_GPACSEL2_GPIO11_M   0xF000U       // GPIO11 Master CPU Select
#define GPIO_GPACSEL2_GPIO12_S   16U
#define GPIO_GPACSEL2_GPIO12_M   0xF0000U      // GPIO12 Master CPU Select
#define GPIO_GPACSEL2_GPIO13_S   20U
#define GPIO_GPACSEL2_GPIO13_M   0xF00000U     // GPIO13 Master CPU Select
#define GPIO_GPACSEL2_GPIO14_S   24U
#define GPIO_GPACSEL2_GPIO14_M   0xF000000U    // GPIO14 Master CPU Select
#define GPIO_GPACSEL2_GPIO15_S   28U
#define GPIO_GPACSEL2_GPIO15_M   0xF0000000U   // GPIO15 Master CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACSEL3 register
//
//*************************************************************************************************
#define GPIO_GPACSEL3_GPIO16_S   0U
#define GPIO_GPACSEL3_GPIO16_M   0xFU          // GPIO16 Master CPU Select
#define GPIO_GPACSEL3_GPIO17_S   4U
#define GPIO_GPACSEL3_GPIO17_M   0xF0U         // GPIO17 Master CPU Select
#define GPIO_GPACSEL3_GPIO18_S   8U
#define GPIO_GPACSEL3_GPIO18_M   0xF00U        // GPIO18 Master CPU Select
#define GPIO_GPACSEL3_GPIO19_S   12U
#define GPIO_GPACSEL3_GPIO19_M   0xF000U       // GPIO19 Master CPU Select
#define GPIO_GPACSEL3_GPIO20_S   16U
#define GPIO_GPACSEL3_GPIO20_M   0xF0000U      // GPIO20 Master CPU Select
#define GPIO_GPACSEL3_GPIO21_S   20U
#define GPIO_GPACSEL3_GPIO21_M   0xF00000U     // GPIO21 Master CPU Select
#define GPIO_GPACSEL3_GPIO22_S   24U
#define GPIO_GPACSEL3_GPIO22_M   0xF000000U    // GPIO22 Master CPU Select
#define GPIO_GPACSEL3_GPIO23_S   28U
#define GPIO_GPACSEL3_GPIO23_M   0xF0000000U   // GPIO23 Master CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPACSEL4 register
//
//*************************************************************************************************
#define GPIO_GPACSEL4_GPIO24_S   0U
#define GPIO_GPACSEL4_GPIO24_M   0xFU          // GPIO24 Master CPU Select
#define GPIO_GPACSEL4_GPIO25_S   4U
#define GPIO_GPACSEL4_GPIO25_M   0xF0U         // GPIO25 Master CPU Select
#define GPIO_GPACSEL4_GPIO26_S   8U
#define GPIO_GPACSEL4_GPIO26_M   0xF00U        // GPIO26 Master CPU Select
#define GPIO_GPACSEL4_GPIO27_S   12U
#define GPIO_GPACSEL4_GPIO27_M   0xF000U       // GPIO27 Master CPU Select
#define GPIO_GPACSEL4_GPIO28_S   16U
#define GPIO_GPACSEL4_GPIO28_M   0xF0000U      // GPIO28 Master CPU Select
#define GPIO_GPACSEL4_GPIO29_S   20U
#define GPIO_GPACSEL4_GPIO29_M   0xF00000U     // GPIO29 Master CPU Select
#define GPIO_GPACSEL4_GPIO30_S   24U
#define GPIO_GPACSEL4_GPIO30_M   0xF000000U    // GPIO30 Master CPU Select
#define GPIO_GPACSEL4_GPIO31_S   28U
#define GPIO_GPACSEL4_GPIO31_M   0xF0000000U   // GPIO31 Master CPU Select

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
#define GPIO_GPBQSEL1_GPIO47_S   30U
#define GPIO_GPBQSEL1_GPIO47_M   0xC0000000U   // Select input qualification type for GPIO47

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBQSEL2 register
//
//*************************************************************************************************
#define GPIO_GPBQSEL2_GPIO48_S   0U
#define GPIO_GPBQSEL2_GPIO48_M   0x3U        // Select input qualification type for GPIO48
#define GPIO_GPBQSEL2_GPIO49_S   2U
#define GPIO_GPBQSEL2_GPIO49_M   0xCU        // Select input qualification type for GPIO49
#define GPIO_GPBQSEL2_GPIO50_S   4U
#define GPIO_GPBQSEL2_GPIO50_M   0x30U       // Select input qualification type for GPIO50
#define GPIO_GPBQSEL2_GPIO51_S   6U
#define GPIO_GPBQSEL2_GPIO51_M   0xC0U       // Select input qualification type for GPIO51
#define GPIO_GPBQSEL2_GPIO52_S   8U
#define GPIO_GPBQSEL2_GPIO52_M   0x300U      // Select input qualification type for GPIO52
#define GPIO_GPBQSEL2_GPIO53_S   10U
#define GPIO_GPBQSEL2_GPIO53_M   0xC00U      // Select input qualification type for GPIO53
#define GPIO_GPBQSEL2_GPIO54_S   12U
#define GPIO_GPBQSEL2_GPIO54_M   0x3000U     // Select input qualification type for GPIO54
#define GPIO_GPBQSEL2_GPIO55_S   14U
#define GPIO_GPBQSEL2_GPIO55_M   0xC000U     // Select input qualification type for GPIO55
#define GPIO_GPBQSEL2_GPIO56_S   16U
#define GPIO_GPBQSEL2_GPIO56_M   0x30000U    // Select input qualification type for GPIO56
#define GPIO_GPBQSEL2_GPIO57_S   18U
#define GPIO_GPBQSEL2_GPIO57_M   0xC0000U    // Select input qualification type for GPIO57
#define GPIO_GPBQSEL2_GPIO58_S   20U
#define GPIO_GPBQSEL2_GPIO58_M   0x300000U   // Select input qualification type for GPIO58
#define GPIO_GPBQSEL2_GPIO59_S   22U
#define GPIO_GPBQSEL2_GPIO59_M   0xC00000U   // Select input qualification type for GPIO59

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
#define GPIO_GPBMUX1_GPIO47_S   30U
#define GPIO_GPBMUX1_GPIO47_M   0xC0000000U   // Defines pin-muxing selection for GPIO47

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBMUX2 register
//
//*************************************************************************************************
#define GPIO_GPBMUX2_GPIO48_S   0U
#define GPIO_GPBMUX2_GPIO48_M   0x3U        // Defines pin-muxing selection for GPIO48
#define GPIO_GPBMUX2_GPIO49_S   2U
#define GPIO_GPBMUX2_GPIO49_M   0xCU        // Defines pin-muxing selection for GPIO49
#define GPIO_GPBMUX2_GPIO50_S   4U
#define GPIO_GPBMUX2_GPIO50_M   0x30U       // Defines pin-muxing selection for GPIO50
#define GPIO_GPBMUX2_GPIO51_S   6U
#define GPIO_GPBMUX2_GPIO51_M   0xC0U       // Defines pin-muxing selection for GPIO51
#define GPIO_GPBMUX2_GPIO52_S   8U
#define GPIO_GPBMUX2_GPIO52_M   0x300U      // Defines pin-muxing selection for GPIO52
#define GPIO_GPBMUX2_GPIO53_S   10U
#define GPIO_GPBMUX2_GPIO53_M   0xC00U      // Defines pin-muxing selection for GPIO53
#define GPIO_GPBMUX2_GPIO54_S   12U
#define GPIO_GPBMUX2_GPIO54_M   0x3000U     // Defines pin-muxing selection for GPIO54
#define GPIO_GPBMUX2_GPIO55_S   14U
#define GPIO_GPBMUX2_GPIO55_M   0xC000U     // Defines pin-muxing selection for GPIO55
#define GPIO_GPBMUX2_GPIO56_S   16U
#define GPIO_GPBMUX2_GPIO56_M   0x30000U    // Defines pin-muxing selection for GPIO56
#define GPIO_GPBMUX2_GPIO57_S   18U
#define GPIO_GPBMUX2_GPIO57_M   0xC0000U    // Defines pin-muxing selection for GPIO57
#define GPIO_GPBMUX2_GPIO58_S   20U
#define GPIO_GPBMUX2_GPIO58_M   0x300000U   // Defines pin-muxing selection for GPIO58
#define GPIO_GPBMUX2_GPIO59_S   22U
#define GPIO_GPBMUX2_GPIO59_M   0xC00000U   // Defines pin-muxing selection for GPIO59

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBDIR register
//
//*************************************************************************************************
#define GPIO_GPBDIR_GPIO32   0x1U         // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO33   0x2U         // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO34   0x4U         // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO35   0x8U         // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO37   0x20U        // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO39   0x80U        // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO40   0x100U       // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO41   0x200U       // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO42   0x400U       // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO43   0x800U       // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO44   0x1000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO45   0x2000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO46   0x4000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO47   0x8000U      // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO48   0x10000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO49   0x20000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO50   0x40000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO51   0x80000U     // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO52   0x100000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO53   0x200000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO54   0x400000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO55   0x800000U    // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO56   0x1000000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO57   0x2000000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO58   0x4000000U   // Defines direction for this pin in GPIO mode
#define GPIO_GPBDIR_GPIO59   0x8000000U   // Defines direction for this pin in GPIO mode

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBPUD register
//
//*************************************************************************************************
#define GPIO_GPBPUD_GPIO32   0x1U         // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO33   0x2U         // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO34   0x4U         // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO35   0x8U         // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO37   0x20U        // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO39   0x80U        // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO40   0x100U       // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO41   0x200U       // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO42   0x400U       // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO43   0x800U       // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO44   0x1000U      // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO45   0x2000U      // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO46   0x4000U      // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO47   0x8000U      // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO48   0x10000U     // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO49   0x20000U     // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO50   0x40000U     // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO51   0x80000U     // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO52   0x100000U    // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO53   0x200000U    // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO54   0x400000U    // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO55   0x800000U    // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO56   0x1000000U   // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO57   0x2000000U   // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO58   0x4000000U   // Pull-Up Disable control for this pin
#define GPIO_GPBPUD_GPIO59   0x8000000U   // Pull-Up Disable control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBINV register
//
//*************************************************************************************************
#define GPIO_GPBINV_GPIO32   0x1U         // Input inversion control for this pin
#define GPIO_GPBINV_GPIO33   0x2U         // Input inversion control for this pin
#define GPIO_GPBINV_GPIO34   0x4U         // Input inversion control for this pin
#define GPIO_GPBINV_GPIO35   0x8U         // Input inversion control for this pin
#define GPIO_GPBINV_GPIO37   0x20U        // Input inversion control for this pin
#define GPIO_GPBINV_GPIO39   0x80U        // Input inversion control for this pin
#define GPIO_GPBINV_GPIO40   0x100U       // Input inversion control for this pin
#define GPIO_GPBINV_GPIO41   0x200U       // Input inversion control for this pin
#define GPIO_GPBINV_GPIO42   0x400U       // Input inversion control for this pin
#define GPIO_GPBINV_GPIO43   0x800U       // Input inversion control for this pin
#define GPIO_GPBINV_GPIO44   0x1000U      // Input inversion control for this pin
#define GPIO_GPBINV_GPIO45   0x2000U      // Input inversion control for this pin
#define GPIO_GPBINV_GPIO46   0x4000U      // Input inversion control for this pin
#define GPIO_GPBINV_GPIO47   0x8000U      // Input inversion control for this pin
#define GPIO_GPBINV_GPIO48   0x10000U     // Input inversion control for this pin
#define GPIO_GPBINV_GPIO49   0x20000U     // Input inversion control for this pin
#define GPIO_GPBINV_GPIO50   0x40000U     // Input inversion control for this pin
#define GPIO_GPBINV_GPIO51   0x80000U     // Input inversion control for this pin
#define GPIO_GPBINV_GPIO52   0x100000U    // Input inversion control for this pin
#define GPIO_GPBINV_GPIO53   0x200000U    // Input inversion control for this pin
#define GPIO_GPBINV_GPIO54   0x400000U    // Input inversion control for this pin
#define GPIO_GPBINV_GPIO55   0x800000U    // Input inversion control for this pin
#define GPIO_GPBINV_GPIO56   0x1000000U   // Input inversion control for this pin
#define GPIO_GPBINV_GPIO57   0x2000000U   // Input inversion control for this pin
#define GPIO_GPBINV_GPIO58   0x4000000U   // Input inversion control for this pin
#define GPIO_GPBINV_GPIO59   0x8000000U   // Input inversion control for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBODR register
//
//*************************************************************************************************
#define GPIO_GPBODR_GPIO32   0x1U         // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO33   0x2U         // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO34   0x4U         // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO35   0x8U         // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO37   0x20U        // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO39   0x80U        // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO40   0x100U       // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO41   0x200U       // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO42   0x400U       // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO43   0x800U       // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO44   0x1000U      // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO45   0x2000U      // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO46   0x4000U      // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO47   0x8000U      // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO48   0x10000U     // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO49   0x20000U     // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO50   0x40000U     // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO51   0x80000U     // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO52   0x100000U    // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO53   0x200000U    // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO54   0x400000U    // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO55   0x800000U    // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO56   0x1000000U   // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO57   0x2000000U   // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO58   0x4000000U   // Output Open-Drain control for this pin
#define GPIO_GPBODR_GPIO59   0x8000000U   // Output Open-Drain control for this pin

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
#define GPIO_GPBGMUX1_GPIO47_S   30U
#define GPIO_GPBGMUX1_GPIO47_M   0xC0000000U   // Defines pin-muxing selection for GPIO47

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBGMUX2 register
//
//*************************************************************************************************
#define GPIO_GPBGMUX2_GPIO48_S   0U
#define GPIO_GPBGMUX2_GPIO48_M   0x3U        // Defines pin-muxing selection for GPIO48
#define GPIO_GPBGMUX2_GPIO49_S   2U
#define GPIO_GPBGMUX2_GPIO49_M   0xCU        // Defines pin-muxing selection for GPIO49
#define GPIO_GPBGMUX2_GPIO50_S   4U
#define GPIO_GPBGMUX2_GPIO50_M   0x30U       // Defines pin-muxing selection for GPIO50
#define GPIO_GPBGMUX2_GPIO51_S   6U
#define GPIO_GPBGMUX2_GPIO51_M   0xC0U       // Defines pin-muxing selection for GPIO51
#define GPIO_GPBGMUX2_GPIO52_S   8U
#define GPIO_GPBGMUX2_GPIO52_M   0x300U      // Defines pin-muxing selection for GPIO52
#define GPIO_GPBGMUX2_GPIO53_S   10U
#define GPIO_GPBGMUX2_GPIO53_M   0xC00U      // Defines pin-muxing selection for GPIO53
#define GPIO_GPBGMUX2_GPIO54_S   12U
#define GPIO_GPBGMUX2_GPIO54_M   0x3000U     // Defines pin-muxing selection for GPIO54
#define GPIO_GPBGMUX2_GPIO55_S   14U
#define GPIO_GPBGMUX2_GPIO55_M   0xC000U     // Defines pin-muxing selection for GPIO55
#define GPIO_GPBGMUX2_GPIO56_S   16U
#define GPIO_GPBGMUX2_GPIO56_M   0x30000U    // Defines pin-muxing selection for GPIO56
#define GPIO_GPBGMUX2_GPIO57_S   18U
#define GPIO_GPBGMUX2_GPIO57_M   0xC0000U    // Defines pin-muxing selection for GPIO57
#define GPIO_GPBGMUX2_GPIO58_S   20U
#define GPIO_GPBGMUX2_GPIO58_M   0x300000U   // Defines pin-muxing selection for GPIO58
#define GPIO_GPBGMUX2_GPIO59_S   22U
#define GPIO_GPBGMUX2_GPIO59_M   0xC00000U   // Defines pin-muxing selection for GPIO59

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL1 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL1_GPIO32_S   0U
#define GPIO_GPBCSEL1_GPIO32_M   0xFU          // GPIO32 Master CPU Select
#define GPIO_GPBCSEL1_GPIO33_S   4U
#define GPIO_GPBCSEL1_GPIO33_M   0xF0U         // GPIO33 Master CPU Select
#define GPIO_GPBCSEL1_GPIO34_S   8U
#define GPIO_GPBCSEL1_GPIO34_M   0xF00U        // GPIO34 Master CPU Select
#define GPIO_GPBCSEL1_GPIO35_S   12U
#define GPIO_GPBCSEL1_GPIO35_M   0xF000U       // GPIO35 Master CPU Select
#define GPIO_GPBCSEL1_GPIO37_S   20U
#define GPIO_GPBCSEL1_GPIO37_M   0xF00000U     // GPIO37 Master CPU Select
#define GPIO_GPBCSEL1_GPIO39_S   28U
#define GPIO_GPBCSEL1_GPIO39_M   0xF0000000U   // GPIO39 Master CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL2 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL2_GPIO40_S   0U
#define GPIO_GPBCSEL2_GPIO40_M   0xFU          // GPIO40 Master CPU Select
#define GPIO_GPBCSEL2_GPIO41_S   4U
#define GPIO_GPBCSEL2_GPIO41_M   0xF0U         // GPIO41 Master CPU Select
#define GPIO_GPBCSEL2_GPIO42_S   8U
#define GPIO_GPBCSEL2_GPIO42_M   0xF00U        // GPIO42 Master CPU Select
#define GPIO_GPBCSEL2_GPIO43_S   12U
#define GPIO_GPBCSEL2_GPIO43_M   0xF000U       // GPIO43 Master CPU Select
#define GPIO_GPBCSEL2_GPIO44_S   16U
#define GPIO_GPBCSEL2_GPIO44_M   0xF0000U      // GPIO44 Master CPU Select
#define GPIO_GPBCSEL2_GPIO45_S   20U
#define GPIO_GPBCSEL2_GPIO45_M   0xF00000U     // GPIO45 Master CPU Select
#define GPIO_GPBCSEL2_GPIO46_S   24U
#define GPIO_GPBCSEL2_GPIO46_M   0xF000000U    // GPIO46 Master CPU Select
#define GPIO_GPBCSEL2_GPIO47_S   28U
#define GPIO_GPBCSEL2_GPIO47_M   0xF0000000U   // GPIO47 Master CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL3 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL3_GPIO48_S   0U
#define GPIO_GPBCSEL3_GPIO48_M   0xFU          // GPIO48 Master CPU Select
#define GPIO_GPBCSEL3_GPIO49_S   4U
#define GPIO_GPBCSEL3_GPIO49_M   0xF0U         // GPIO49 Master CPU Select
#define GPIO_GPBCSEL3_GPIO50_S   8U
#define GPIO_GPBCSEL3_GPIO50_M   0xF00U        // GPIO50 Master CPU Select
#define GPIO_GPBCSEL3_GPIO51_S   12U
#define GPIO_GPBCSEL3_GPIO51_M   0xF000U       // GPIO51 Master CPU Select
#define GPIO_GPBCSEL3_GPIO52_S   16U
#define GPIO_GPBCSEL3_GPIO52_M   0xF0000U      // GPIO52 Master CPU Select
#define GPIO_GPBCSEL3_GPIO53_S   20U
#define GPIO_GPBCSEL3_GPIO53_M   0xF00000U     // GPIO53 Master CPU Select
#define GPIO_GPBCSEL3_GPIO54_S   24U
#define GPIO_GPBCSEL3_GPIO54_M   0xF000000U    // GPIO54 Master CPU Select
#define GPIO_GPBCSEL3_GPIO55_S   28U
#define GPIO_GPBCSEL3_GPIO55_M   0xF0000000U   // GPIO55 Master CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCSEL4 register
//
//*************************************************************************************************
#define GPIO_GPBCSEL4_GPIO56_S   0U
#define GPIO_GPBCSEL4_GPIO56_M   0xFU      // GPIO56 Master CPU Select
#define GPIO_GPBCSEL4_GPIO57_S   4U
#define GPIO_GPBCSEL4_GPIO57_M   0xF0U     // GPIO57 Master CPU Select
#define GPIO_GPBCSEL4_GPIO58_S   8U
#define GPIO_GPBCSEL4_GPIO58_M   0xF00U    // GPIO58 Master CPU Select
#define GPIO_GPBCSEL4_GPIO59_S   12U
#define GPIO_GPBCSEL4_GPIO59_M   0xF000U   // GPIO59 Master CPU Select

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBLOCK register
//
//*************************************************************************************************
#define GPIO_GPBLOCK_GPIO32   0x1U         // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO33   0x2U         // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO34   0x4U         // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO35   0x8U         // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO37   0x20U        // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO39   0x80U        // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO40   0x100U       // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO41   0x200U       // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO42   0x400U       // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO43   0x800U       // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO44   0x1000U      // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO45   0x2000U      // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO46   0x4000U      // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO47   0x8000U      // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO48   0x10000U     // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO49   0x20000U     // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO50   0x40000U     // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO51   0x80000U     // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO52   0x100000U    // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO53   0x200000U    // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO54   0x400000U    // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO55   0x800000U    // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO56   0x1000000U   // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO57   0x2000000U   // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO58   0x4000000U   // Configuration Lock bit for this pin
#define GPIO_GPBLOCK_GPIO59   0x8000000U   // Configuration Lock bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCR register
//
//*************************************************************************************************
#define GPIO_GPBCR_GPIO32   0x1U         // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO33   0x2U         // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO34   0x4U         // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO35   0x8U         // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO37   0x20U        // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO39   0x80U        // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO40   0x100U       // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO41   0x200U       // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO42   0x400U       // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO43   0x800U       // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO44   0x1000U      // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO45   0x2000U      // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO46   0x4000U      // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO47   0x8000U      // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO48   0x10000U     // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO49   0x20000U     // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO50   0x40000U     // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO51   0x80000U     // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO52   0x100000U    // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO53   0x200000U    // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO54   0x400000U    // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO55   0x800000U    // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO56   0x1000000U   // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO57   0x2000000U   // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO58   0x4000000U   // Configuration lock commit bit for this pin
#define GPIO_GPBCR_GPIO59   0x8000000U   // Configuration lock commit bit for this pin

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
#define GPIO_GPHQSEL2_GPIO240_M   0x3U      // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO241_S   2U
#define GPIO_GPHQSEL2_GPIO241_M   0xCU      // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO242_S   4U
#define GPIO_GPHQSEL2_GPIO242_M   0x30U     // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO243_S   6U
#define GPIO_GPHQSEL2_GPIO243_M   0xC0U     // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO244_S   8U
#define GPIO_GPHQSEL2_GPIO244_M   0x300U    // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO245_S   10U
#define GPIO_GPHQSEL2_GPIO245_M   0xC00U    // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO246_S   12U
#define GPIO_GPHQSEL2_GPIO246_M   0x3000U   // Select input qualification type for this GPIO Pin
#define GPIO_GPHQSEL2_GPIO247_S   14U
#define GPIO_GPHQSEL2_GPIO247_M   0xC000U   // Select input qualification type for this GPIO Pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPHPUD register
//
//*************************************************************************************************
#define GPIO_GPHPUD_GPIO224   0x1U        // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO225   0x2U        // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO226   0x4U        // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO227   0x8U        // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO228   0x10U       // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO229   0x20U       // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO230   0x40U       // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO231   0x80U       // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO232   0x100U      // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO233   0x200U      // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO234   0x400U      // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO235   0x800U      // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO236   0x1000U     // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO237   0x2000U     // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO238   0x4000U     // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO239   0x8000U     // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO240   0x10000U    // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO241   0x20000U    // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO242   0x40000U    // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO243   0x80000U    // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO244   0x100000U   // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO245   0x200000U   // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO246   0x400000U   // Pull-Up Disable control for this pin
#define GPIO_GPHPUD_GPIO247   0x800000U   // Pull-Up Disable control for this pin

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
#define GPIO_GPHINV_GPIO229   0x20U       // Input inversion control for this pin
#define GPIO_GPHINV_GPIO230   0x40U       // Input inversion control for this pin
#define GPIO_GPHINV_GPIO231   0x80U       // Input inversion control for this pin
#define GPIO_GPHINV_GPIO232   0x100U      // Input inversion control for this pin
#define GPIO_GPHINV_GPIO233   0x200U      // Input inversion control for this pin
#define GPIO_GPHINV_GPIO234   0x400U      // Input inversion control for this pin
#define GPIO_GPHINV_GPIO235   0x800U      // Input inversion control for this pin
#define GPIO_GPHINV_GPIO236   0x1000U     // Input inversion control for this pin
#define GPIO_GPHINV_GPIO237   0x2000U     // Input inversion control for this pin
#define GPIO_GPHINV_GPIO238   0x4000U     // Input inversion control for this pin
#define GPIO_GPHINV_GPIO239   0x8000U     // Input inversion control for this pin
#define GPIO_GPHINV_GPIO240   0x10000U    // Input inversion control for this pin
#define GPIO_GPHINV_GPIO241   0x20000U    // Input inversion control for this pin
#define GPIO_GPHINV_GPIO242   0x40000U    // Input inversion control for this pin
#define GPIO_GPHINV_GPIO243   0x80000U    // Input inversion control for this pin
#define GPIO_GPHINV_GPIO244   0x100000U   // Input inversion control for this pin
#define GPIO_GPHINV_GPIO245   0x200000U   // Input inversion control for this pin
#define GPIO_GPHINV_GPIO246   0x400000U   // Input inversion control for this pin
#define GPIO_GPHINV_GPIO247   0x800000U   // Input inversion control for this pin

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
#define GPIO_GPHAMSEL_GPIO229   0x20U       // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO230   0x40U       // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO231   0x80U       // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO232   0x100U      // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO233   0x200U      // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO234   0x400U      // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO235   0x800U      // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO236   0x1000U     // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO237   0x2000U     // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO238   0x4000U     // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO239   0x8000U     // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO240   0x10000U    // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO241   0x20000U    // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO242   0x40000U    // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO243   0x80000U    // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO244   0x100000U   // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO245   0x200000U   // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO246   0x400000U   // Analog Mode select for this pin
#define GPIO_GPHAMSEL_GPIO247   0x800000U   // Analog Mode select for this pin

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
#define GPIO_GPHLOCK_GPIO229   0x20U       // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO230   0x40U       // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO231   0x80U       // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO232   0x100U      // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO233   0x200U      // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO234   0x400U      // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO235   0x800U      // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO236   0x1000U     // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO237   0x2000U     // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO238   0x4000U     // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO239   0x8000U     // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO240   0x10000U    // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO241   0x20000U    // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO242   0x40000U    // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO243   0x80000U    // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO244   0x100000U   // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO245   0x200000U   // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO246   0x400000U   // Configuration Lock bit for this pin
#define GPIO_GPHLOCK_GPIO247   0x800000U   // Configuration Lock bit for this pin

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
#define GPIO_GPHCR_GPIO229   0x20U       // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO230   0x40U       // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO231   0x80U       // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO232   0x100U      // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO233   0x200U      // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO234   0x400U      // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO235   0x800U      // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO236   0x1000U     // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO237   0x2000U     // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO238   0x4000U     // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO239   0x8000U     // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO240   0x10000U    // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO241   0x20000U    // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO242   0x40000U    // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO243   0x80000U    // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO244   0x100000U   // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO245   0x200000U   // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO246   0x400000U   // Configuration lock commit bit for this pin
#define GPIO_GPHCR_GPIO247   0x800000U   // Configuration lock commit bit for this pin


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
#define GPIO_GPBDAT_GPIO32   0x1U         // Data Register for this pin
#define GPIO_GPBDAT_GPIO33   0x2U         // Data Register for this pin
#define GPIO_GPBDAT_GPIO34   0x4U         // Data Register for this pin
#define GPIO_GPBDAT_GPIO35   0x8U         // Data Register for this pin
#define GPIO_GPBDAT_GPIO37   0x20U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO39   0x80U        // Data Register for this pin
#define GPIO_GPBDAT_GPIO40   0x100U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO41   0x200U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO42   0x400U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO43   0x800U       // Data Register for this pin
#define GPIO_GPBDAT_GPIO44   0x1000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO45   0x2000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO46   0x4000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO47   0x8000U      // Data Register for this pin
#define GPIO_GPBDAT_GPIO48   0x10000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO49   0x20000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO50   0x40000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO51   0x80000U     // Data Register for this pin
#define GPIO_GPBDAT_GPIO52   0x100000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO53   0x200000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO54   0x400000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO55   0x800000U    // Data Register for this pin
#define GPIO_GPBDAT_GPIO56   0x1000000U   // Data Register for this pin
#define GPIO_GPBDAT_GPIO57   0x2000000U   // Data Register for this pin
#define GPIO_GPBDAT_GPIO58   0x4000000U   // Data Register for this pin
#define GPIO_GPBDAT_GPIO59   0x8000000U   // Data Register for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBSET register
//
//*************************************************************************************************
#define GPIO_GPBSET_GPIO32   0x1U         // Output Set bit for this pin
#define GPIO_GPBSET_GPIO33   0x2U         // Output Set bit for this pin
#define GPIO_GPBSET_GPIO34   0x4U         // Output Set bit for this pin
#define GPIO_GPBSET_GPIO35   0x8U         // Output Set bit for this pin
#define GPIO_GPBSET_GPIO37   0x20U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO39   0x80U        // Output Set bit for this pin
#define GPIO_GPBSET_GPIO40   0x100U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO41   0x200U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO42   0x400U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO43   0x800U       // Output Set bit for this pin
#define GPIO_GPBSET_GPIO44   0x1000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO45   0x2000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO46   0x4000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO47   0x8000U      // Output Set bit for this pin
#define GPIO_GPBSET_GPIO48   0x10000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO49   0x20000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO50   0x40000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO51   0x80000U     // Output Set bit for this pin
#define GPIO_GPBSET_GPIO52   0x100000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO53   0x200000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO54   0x400000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO55   0x800000U    // Output Set bit for this pin
#define GPIO_GPBSET_GPIO56   0x1000000U   // Output Set bit for this pin
#define GPIO_GPBSET_GPIO57   0x2000000U   // Output Set bit for this pin
#define GPIO_GPBSET_GPIO58   0x4000000U   // Output Set bit for this pin
#define GPIO_GPBSET_GPIO59   0x8000000U   // Output Set bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBCLEAR register
//
//*************************************************************************************************
#define GPIO_GPBCLEAR_GPIO32   0x1U         // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO33   0x2U         // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO34   0x4U         // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO35   0x8U         // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO37   0x20U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO39   0x80U        // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO40   0x100U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO41   0x200U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO42   0x400U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO43   0x800U       // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO44   0x1000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO45   0x2000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO46   0x4000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO47   0x8000U      // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO48   0x10000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO49   0x20000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO50   0x40000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO51   0x80000U     // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO52   0x100000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO53   0x200000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO54   0x400000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO55   0x800000U    // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO56   0x1000000U   // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO57   0x2000000U   // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO58   0x4000000U   // Output Clear bit for this pin
#define GPIO_GPBCLEAR_GPIO59   0x8000000U   // Output Clear bit for this pin

//*************************************************************************************************
//
// The following are defines for the bit fields in the GPBTOGGLE register
//
//*************************************************************************************************
#define GPIO_GPBTOGGLE_GPIO32   0x1U         // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO33   0x2U         // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO34   0x4U         // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO35   0x8U         // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO37   0x20U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO39   0x80U        // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO40   0x100U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO41   0x200U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO42   0x400U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO43   0x800U       // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO44   0x1000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO45   0x2000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO46   0x4000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO47   0x8000U      // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO48   0x10000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO49   0x20000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO50   0x40000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO51   0x80000U     // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO52   0x100000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO53   0x200000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO54   0x400000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO55   0x800000U    // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO56   0x1000000U   // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO57   0x2000000U   // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO58   0x4000000U   // Output Toggle bit for this pin
#define GPIO_GPBTOGGLE_GPIO59   0x8000000U   // Output Toggle bit for this pin

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
#define GPIO_GPHDAT_GPIO229   0x20U       // Data Register for this pin
#define GPIO_GPHDAT_GPIO230   0x40U       // Data Register for this pin
#define GPIO_GPHDAT_GPIO231   0x80U       // Data Register for this pin
#define GPIO_GPHDAT_GPIO232   0x100U      // Data Register for this pin
#define GPIO_GPHDAT_GPIO233   0x200U      // Data Register for this pin
#define GPIO_GPHDAT_GPIO234   0x400U      // Data Register for this pin
#define GPIO_GPHDAT_GPIO235   0x800U      // Data Register for this pin
#define GPIO_GPHDAT_GPIO236   0x1000U     // Data Register for this pin
#define GPIO_GPHDAT_GPIO237   0x2000U     // Data Register for this pin
#define GPIO_GPHDAT_GPIO238   0x4000U     // Data Register for this pin
#define GPIO_GPHDAT_GPIO239   0x8000U     // Data Register for this pin
#define GPIO_GPHDAT_GPIO240   0x10000U    // Data Register for this pin
#define GPIO_GPHDAT_GPIO241   0x20000U    // Data Register for this pin
#define GPIO_GPHDAT_GPIO242   0x40000U    // Data Register for this pin
#define GPIO_GPHDAT_GPIO243   0x80000U    // Data Register for this pin
#define GPIO_GPHDAT_GPIO244   0x100000U   // Data Register for this pin
#define GPIO_GPHDAT_GPIO245   0x200000U   // Data Register for this pin
#define GPIO_GPHDAT_GPIO246   0x400000U   // Data Register for this pin
#define GPIO_GPHDAT_GPIO247   0x800000U   // Data Register for this pin



#endif
