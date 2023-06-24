//###########################################################################
//
// FILE:    hw_nvic.h
//
// TITLE:   Definitions for the NVIC registers.
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

#ifndef HW_NVIC_H
#define HW_NVIC_H

//*************************************************************************************************
//
// The following are defines for the NVIC register offsets
//
//*************************************************************************************************
#define NVIC_O_ISER0   0x100U   // NVIC Interrupt Set Enable Register 0
#define NVIC_O_ISER1   0x104U   // NVIC Interrupt Set Enable Register 1
#define NVIC_O_ICER0   0x180U   // NVIC Interrupt Clear Enable Register 0
#define NVIC_O_ICER1   0x184U   // NVIC Interrupt Clear Enable Register 1
#define NVIC_O_ISPR0   0x200U   // NVIC Interrupt Set Pending Register 0
#define NVIC_O_ISPR1   0x204U   // NVIC Interrupt Set Pending Register 1
#define NVIC_O_ISPR2   0x208U   // NVIC Interrupt Set Pending Register 2
#define NVIC_O_ICPR0   0x280U   // NVIC Interrupt Clear Pending Register 0
#define NVIC_O_ICPR1   0x284U   // NVIC Interrupt Clear Pending Register 1
#define NVIC_O_IABR0   0x300U   // NVIC Interrupt Active Bit Register 0
#define NVIC_O_IABR1   0x304U   // NVIC Interrupt Active Bit Register 1
#define NVIC_O_IPR0    0x400U   // NVIC Interrupt Priority Register 0
#define NVIC_O_IPR1    0x404U   // NVIC Interrupt Priority Register 1
#define NVIC_O_IPR2    0x408U   // NVIC Interrupt Priority Register 2
#define NVIC_O_IPR3    0x40CU   // NVIC Interrupt Priority Register 3
#define NVIC_O_IPR4    0x410U   // NVIC Interrupt Priority Register 4
#define NVIC_O_IPR5    0x414U   // NVIC Interrupt Priority Register 5
#define NVIC_O_IPR6    0x418U   // NVIC Interrupt Priority Register 6
#define NVIC_O_IPR7    0x41CU   // NVIC Interrupt Priority Register 7
#define NVIC_O_IPR8    0x420U   // NVIC Interrupt Priority Register 8
#define NVIC_O_IPR9    0x424U   // NVIC Interrupt Priority Register 9
#define NVIC_O_IPR10   0x428U   // NVIC Interrupt Priority Register 10
#define NVIC_O_IPR11   0x42CU   // NVIC Interrupt Priority Register 11
#define NVIC_O_IPR12   0x430U   // NVIC Interrupt Priority Register 12
#define NVIC_O_IPR13   0x434U   // NVIC Interrupt Priority Register 13
#define NVIC_O_IPR14   0x438U   // NVIC Interrupt Priority Register 14
#define NVIC_O_IPR15   0x43CU   // NVIC Interrupt Priority Register 15
#define NVIC_O_STIR    0xF00U   // Software Trigger Interrupt Register

#define NVIC_O_ACTLR    0x8U     // Auxiliary Control Register
#define NVIC_O_CPUID    0xD00U   // CPUID Base Register
#define NVIC_O_ICSR     0xD04U   // Interrupt Control and State Register
#define NVIC_O_VTOR     0xD08U   // Vector Table Offset Register
#define NVIC_O_AIRCR    0xD0CU   // Application Interrupt and Reset Control Register
#define NVIC_O_SCR      0xD10U   // System Control Register
#define NVIC_O_CCR      0xD14U   // Configuration and Control Register
#define NVIC_O_SHPR1    0xD18U   // System Handler Priority Register 1
#define NVIC_O_SHPR2    0xD1CU   // System Handler Priority Register 2
#define NVIC_O_SHPR3    0xD20U   // System Handler Priority Register 3
#define NVIC_O_SHCSRS   0xD24U   // System Handler Control and State Register
#define NVIC_O_CFSR     0xD28U   // Configurable Fault Status Register
#define NVIC_O_HFSR     0xD2CU   // HardFault Status Register
#define NVIC_O_MMFAR    0xD34U   // MemManage Fault Address Register
#define NVIC_O_BFAR     0xD38U   // BusFault Address Register
#define NVIC_O_AFSR     0xD3CU   // Auxiliary Fault Status Register

#define NVIC_O_MMSR   0xD28U   // MemManage Fault Status Register
#define NVIC_O_BFSR   0xD29U   // BusFault Status Register
#define NVIC_O_UFSR   0xD2AU   // UsageFault Status Register

#define NVIC_O_SYST_CSR     0x10U   // Privileged a SysTick Control and Status Register
#define NVIC_O_SYST_RVR     0x14U   // Privileged Unknown SysTick Reload Value Register
#define NVIC_O_SYST_CVR     0x18U   // Privileged Unknown SysTick Current Value Register
#define NVIC_O_SYST_CALIB   0x1CU   // Privileged -a SysTick Calibration Value Register

#define NVIC_O_MPU_TYPE      0xD90U   // MPU Type Register
#define NVIC_O_MPU_CTRL      0xD94U   // MPU Control Register
#define NVIC_O_MPU_RNR       0xD98U   // MPU Region Number Register
#define NVIC_O_MPU_RBAR      0xD9CU   // MPU Region Base Address Register
#define NVIC_O_MPU_RASR      0xDA0U   // MPU Region Attribute and Size Register
#define NVIC_O_MPU_RBAR_A1   0xDA4U   // Alias of RBAR
#define NVIC_O_MPU_RASR_A1   0xDA8U   // Alias of RASR
#define NVIC_O_MPU_RBAR_A2   0xDACU   // Alias of RBAR
#define NVIC_O_MPU_RASR_A2   0xDB0U   // Alias of RASR
#define NVIC_O_MPU_RBAR_A3   0xDB4U   // Alias of RBAR
#define NVIC_O_MPU_RASR_A3   0xDB8U   // Alias of RASR


//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_ISER0 register
//
//*************************************************************************************************
#define NVIC_ISER0_SETENA0    0x1U          // Set INTR0 Enable
#define NVIC_ISER0_SETENA1    0x2U          // Set INTR1 Enable
#define NVIC_ISER0_SETENA2    0x4U          // Set INTR2 Enable
#define NVIC_ISER0_SETENA3    0x8U          // Set INTR3 Enable
#define NVIC_ISER0_SETENA4    0x10U         // Set INTR4 Enable
#define NVIC_ISER0_SETENA5    0x20U         // Set INTR5 Enable
#define NVIC_ISER0_SETENA6    0x40U         // Set INTR6 Enable
#define NVIC_ISER0_SETENA7    0x80U         // Set INTR7 Enable
#define NVIC_ISER0_SETENA8    0x100U        // Set INTR8 Enable
#define NVIC_ISER0_SETENA9    0x200U        // Set INTR9 Enable
#define NVIC_ISER0_SETENA10   0x400U        // Set INTR10 Enable
#define NVIC_ISER0_SETENA11   0x800U        // Set INTR11 Enable
#define NVIC_ISER0_SETENA12   0x1000U       // Set INTR12 Enable
#define NVIC_ISER0_SETENA13   0x2000U       // Set INTR13 Enable
#define NVIC_ISER0_SETENA14   0x4000U       // Set INTR14 Enable
#define NVIC_ISER0_SETENA15   0x8000U       // Set INTR15 Enable
#define NVIC_ISER0_SETENA16   0x10000U      // Set INTR16 Enable
#define NVIC_ISER0_SETENA17   0x20000U      // Set INTR17 Enable
#define NVIC_ISER0_SETENA18   0x40000U      // Set INTR18 Enable
#define NVIC_ISER0_SETENA19   0x80000U      // Set INTR19 Enable
#define NVIC_ISER0_SETENA20   0x100000U     // Set INTR20 Enable
#define NVIC_ISER0_SETENA21   0x200000U     // Set INTR21 Enable
#define NVIC_ISER0_SETENA22   0x400000U     // Set INTR22 Enable
#define NVIC_ISER0_SETENA23   0x800000U     // Set INTR23 Enable
#define NVIC_ISER0_SETENA24   0x1000000U    // Set INTR24 Enable
#define NVIC_ISER0_SETENA25   0x2000000U    // Set INTR25 Enable
#define NVIC_ISER0_SETENA26   0x4000000U    // Set INTR26 Enable
#define NVIC_ISER0_SETENA27   0x8000000U    // Set INTR27 Enable
#define NVIC_ISER0_SETENA28   0x10000000U   // Set INTR28 Enable
#define NVIC_ISER0_SETENA29   0x20000000U   // Set INTR29 Enable
#define NVIC_ISER0_SETENA30   0x40000000U   // Set INTR30 Enable
#define NVIC_ISER0_SETENA31   0x80000000U   // Set INTR31 Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_ISER1 register
//
//*************************************************************************************************
#define NVIC_ISER1_SETENA32   0x1U          // Set INTR32 Enable
#define NVIC_ISER1_SETENA33   0x2U          // Set INTR33 Enable
#define NVIC_ISER1_SETENA34   0x4U          // Set INTR34 Enable
#define NVIC_ISER1_SETENA35   0x8U          // Set INTR35 Enable
#define NVIC_ISER1_SETENA36   0x10U         // Set INTR36 Enable
#define NVIC_ISER1_SETENA37   0x20U         // Set INTR37 Enable
#define NVIC_ISER1_SETENA38   0x40U         // Set INTR38 Enable
#define NVIC_ISER1_SETENA39   0x80U         // Set INTR39 Enable
#define NVIC_ISER1_SETENA40   0x100U        // Set INTR40 Enable
#define NVIC_ISER1_SETENA41   0x200U        // Set INTR41 Enable
#define NVIC_ISER1_SETENA42   0x400U        // Set INTR42 Enable
#define NVIC_ISER1_SETENA43   0x800U        // Set INTR43 Enable
#define NVIC_ISER1_SETENA44   0x1000U       // Set INTR44 Enable
#define NVIC_ISER1_SETENA45   0x2000U       // Set INTR45 Enable
#define NVIC_ISER1_SETENA46   0x4000U       // Set INTR46 Enable
#define NVIC_ISER1_SETENA47   0x8000U       // Set INTR47 Enable
#define NVIC_ISER1_SETENA48   0x10000U      // Set INTR48 Enable
#define NVIC_ISER1_SETENA49   0x20000U      // Set INTR49 Enable
#define NVIC_ISER1_SETENA50   0x40000U      // Set INTR50 Enable
#define NVIC_ISER1_SETENA51   0x80000U      // Set INTR51 Enable
#define NVIC_ISER1_SETENA52   0x100000U     // Set INTR52 Enable
#define NVIC_ISER1_SETENA53   0x200000U     // Set INTR53 Enable
#define NVIC_ISER1_SETENA54   0x400000U     // Set INTR54 Enable
#define NVIC_ISER1_SETENA55   0x800000U     // Set INTR55 Enable
#define NVIC_ISER1_SETENA56   0x1000000U    // Set INTR56 Enable
#define NVIC_ISER1_SETENA57   0x2000000U    // Set INTR57 Enable
#define NVIC_ISER1_SETENA58   0x4000000U    // Set INTR58 Enable
#define NVIC_ISER1_SETENA59   0x8000000U    // Set INTR59 Enable
#define NVIC_ISER1_SETENA60   0x10000000U   // Set INTR60 Enable
#define NVIC_ISER1_SETENA61   0x20000000U   // Set INTR61 Enable
#define NVIC_ISER1_SETENA62   0x40000000U   // Set INTR62 Enable
#define NVIC_ISER1_SETENA63   0x80000000U   // Set INTR63 Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_ICER0 register
//
//*************************************************************************************************
#define NVIC_ICER0_CLRENA0    0x1U          // Clear INTR0 Enable
#define NVIC_ICER0_CLRENA1    0x2U          // Clear INTR1 Enable
#define NVIC_ICER0_CLRENA2    0x4U          // Clear INTR2 Enable
#define NVIC_ICER0_CLRENA3    0x8U          // Clear INTR3 Enable
#define NVIC_ICER0_CLRENA4    0x10U         // Clear INTR4 Enable
#define NVIC_ICER0_CLRENA5    0x20U         // Clear INTR5 Enable
#define NVIC_ICER0_CLRENA6    0x40U         // Clear INTR6 Enable
#define NVIC_ICER0_CLRENA7    0x80U         // Clear INTR7 Enable
#define NVIC_ICER0_CLRENA8    0x100U        // Clear INTR8 Enable
#define NVIC_ICER0_CLRENA9    0x200U        // Clear INTR9 Enable
#define NVIC_ICER0_CLRENA10   0x400U        // Clear INTR10 Enable
#define NVIC_ICER0_CLRENA11   0x800U        // Clear INTR11 Enable
#define NVIC_ICER0_CLRENA12   0x1000U       // Clear INTR12 Enable
#define NVIC_ICER0_CLRENA13   0x2000U       // Clear INTR13 Enable
#define NVIC_ICER0_CLRENA14   0x4000U       // Clear INTR14 Enable
#define NVIC_ICER0_CLRENA15   0x8000U       // Clear INTR15 Enable
#define NVIC_ICER0_CLRENA16   0x10000U      // Clear INTR16 Enable
#define NVIC_ICER0_CLRENA17   0x20000U      // Clear INTR17 Enable
#define NVIC_ICER0_CLRENA18   0x40000U      // Clear INTR18 Enable
#define NVIC_ICER0_CLRENA19   0x80000U      // Clear INTR19 Enable
#define NVIC_ICER0_CLRENA20   0x100000U     // Clear INTR20 Enable
#define NVIC_ICER0_CLRENA21   0x200000U     // Clear INTR21 Enable
#define NVIC_ICER0_CLRENA22   0x400000U     // Clear INTR22 Enable
#define NVIC_ICER0_CLRENA23   0x800000U     // Clear INTR23 Enable
#define NVIC_ICER0_CLRENA24   0x1000000U    // Clear INTR24 Enable
#define NVIC_ICER0_CLRENA25   0x2000000U    // Clear INTR25 Enable
#define NVIC_ICER0_CLRENA26   0x4000000U    // Clear INTR26 Enable
#define NVIC_ICER0_CLRENA27   0x8000000U    // Clear INTR27 Enable
#define NVIC_ICER0_CLRENA28   0x10000000U   // Clear INTR28 Enable
#define NVIC_ICER0_CLRENA29   0x20000000U   // Clear INTR29 Enable
#define NVIC_ICER0_CLRENA30   0x40000000U   // Clear INTR30 Enable
#define NVIC_ICER0_CLRENA31   0x80000000U   // Clear INTR31 Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_ICER1 register
//
//*************************************************************************************************
#define NVIC_ICER1_CLRENA32   0x1U          // Clear INTR32 Enable
#define NVIC_ICER1_CLRENA33   0x2U          // Clear INTR33 Enable
#define NVIC_ICER1_CLRENA34   0x4U          // Clear INTR34 Enable
#define NVIC_ICER1_CLRENA35   0x8U          // Clear INTR35 Enable
#define NVIC_ICER1_CLRENA36   0x10U         // Clear INTR36 Enable
#define NVIC_ICER1_CLRENA37   0x20U         // Clear INTR37 Enable
#define NVIC_ICER1_CLRENA38   0x40U         // Clear INTR38 Enable
#define NVIC_ICER1_CLRENA39   0x80U         // Clear INTR39 Enable
#define NVIC_ICER1_CLRENA40   0x100U        // Clear INTR40 Enable
#define NVIC_ICER1_CLRENA41   0x200U        // Clear INTR41 Enable
#define NVIC_ICER1_CLRENA42   0x400U        // Clear INTR42 Enable
#define NVIC_ICER1_CLRENA43   0x800U        // Clear INTR43 Enable
#define NVIC_ICER1_CLRENA44   0x1000U       // Clear INTR44 Enable
#define NVIC_ICER1_CLRENA45   0x2000U       // Clear INTR45 Enable
#define NVIC_ICER1_CLRENA46   0x4000U       // Clear INTR46 Enable
#define NVIC_ICER1_CLRENA47   0x8000U       // Clear INTR47 Enable
#define NVIC_ICER1_CLRENA48   0x10000U      // Clear INTR48 Enable
#define NVIC_ICER1_CLRENA49   0x20000U      // Clear INTR49 Enable
#define NVIC_ICER1_CLRENA50   0x40000U      // Clear INTR50 Enable
#define NVIC_ICER1_CLRENA51   0x80000U      // Clear INTR51 Enable
#define NVIC_ICER1_CLRENA52   0x100000U     // Clear INTR52 Enable
#define NVIC_ICER1_CLRENA53   0x200000U     // Clear INTR53 Enable
#define NVIC_ICER1_CLRENA54   0x400000U     // Clear INTR54 Enable
#define NVIC_ICER1_CLRENA55   0x800000U     // Clear INTR55 Enable
#define NVIC_ICER1_CLRENA56   0x1000000U    // Clear INTR56 Enable
#define NVIC_ICER1_CLRENA57   0x2000000U    // Clear INTR57 Enable
#define NVIC_ICER1_CLRENA58   0x4000000U    // Clear INTR58 Enable
#define NVIC_ICER1_CLRENA59   0x8000000U    // Clear INTR59 Enable
#define NVIC_ICER1_CLRENA60   0x10000000U   // Clear INTR60 Enable
#define NVIC_ICER1_CLRENA61   0x20000000U   // Clear INTR61 Enable
#define NVIC_ICER1_CLRENA62   0x40000000U   // Clear INTR62 Enable
#define NVIC_ICER1_CLRENA63   0x80000000U   // Clear INTR63 Enable

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_ISPR0 register
//
//*************************************************************************************************
#define NVIC_ISPR0_SETPEND0    0x1U          // Set INTR0 Pending
#define NVIC_ISPR0_SETPEND1    0x2U          // Set INTR1 Pending
#define NVIC_ISPR0_SETPEND2    0x4U          // Set INTR2 Pending
#define NVIC_ISPR0_SETPEND3    0x8U          // Set INTR3 Pending
#define NVIC_ISPR0_SETPEND4    0x10U         // Set INTR4 Pending
#define NVIC_ISPR0_SETPEND5    0x20U         // Set INTR5 Pending
#define NVIC_ISPR0_SETPEND6    0x40U         // Set INTR6 Pending
#define NVIC_ISPR0_SETPEND7    0x80U         // Set INTR7 Pending
#define NVIC_ISPR0_SETPEND8    0x100U        // Set INTR8 Pending
#define NVIC_ISPR0_SETPEND9    0x200U        // Set INTR9 Pending
#define NVIC_ISPR0_SETPEND10   0x400U        // Set INTR10 Pending
#define NVIC_ISPR0_SETPEND11   0x800U        // Set INTR11 Pending
#define NVIC_ISPR0_SETPEND12   0x1000U       // Set INTR12 Pending
#define NVIC_ISPR0_SETPEND13   0x2000U       // Set INTR13 Pending
#define NVIC_ISPR0_SETPEND14   0x4000U       // Set INTR14 Pending
#define NVIC_ISPR0_SETPEND15   0x8000U       // Set INTR15 Pending
#define NVIC_ISPR0_SETPEND16   0x10000U      // Set INTR16 Pending
#define NVIC_ISPR0_SETPEND17   0x20000U      // Set INTR17 Pending
#define NVIC_ISPR0_SETPEND18   0x40000U      // Set INTR18 Pending
#define NVIC_ISPR0_SETPEND19   0x80000U      // Set INTR19 Pending
#define NVIC_ISPR0_SETPEND20   0x100000U     // Set INTR20 Pending
#define NVIC_ISPR0_SETPEND21   0x200000U     // Set INTR21 Pending
#define NVIC_ISPR0_SETPEND22   0x400000U     // Set INTR22 Pending
#define NVIC_ISPR0_SETPEND23   0x800000U     // Set INTR23 Pending
#define NVIC_ISPR0_SETPEND24   0x1000000U    // Set INTR24 Pending
#define NVIC_ISPR0_SETPEND25   0x2000000U    // Set INTR25 Pending
#define NVIC_ISPR0_SETPEND26   0x4000000U    // Set INTR26 Pending
#define NVIC_ISPR0_SETPEND27   0x8000000U    // Set INTR27 Pending
#define NVIC_ISPR0_SETPEND28   0x10000000U   // Set INTR28 Pending
#define NVIC_ISPR0_SETPEND29   0x20000000U   // Set INTR29 Pending
#define NVIC_ISPR0_SETPEND30   0x40000000U   // Set INTR30 Pending
#define NVIC_ISPR0_SETPEND31   0x80000000U   // Set INTR31 Pending

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_ISPR1 register
//
//*************************************************************************************************
#define NVIC_ISPR1_SETPEND32   0x1U          // Set INTR32 Pending
#define NVIC_ISPR1_SETPEND33   0x2U          // Set INTR33 Pending
#define NVIC_ISPR1_SETPEND34   0x4U          // Set INTR34 Pending
#define NVIC_ISPR1_SETPEND35   0x8U          // Set INTR35 Pending
#define NVIC_ISPR1_SETPEND36   0x10U         // Set INTR36 Pending
#define NVIC_ISPR1_SETPEND37   0x20U         // Set INTR37 Pending
#define NVIC_ISPR1_SETPEND38   0x40U         // Set INTR38 Pending
#define NVIC_ISPR1_SETPEND39   0x80U         // Set INTR39 Pending
#define NVIC_ISPR1_SETPEND40   0x100U        // Set INTR40 Pending
#define NVIC_ISPR1_SETPEND41   0x200U        // Set INTR41 Pending
#define NVIC_ISPR1_SETPEND42   0x400U        // Set INTR42 Pending
#define NVIC_ISPR1_SETPEND43   0x800U        // Set INTR43 Pending
#define NVIC_ISPR1_SETPEND44   0x1000U       // Set INTR44 Pending
#define NVIC_ISPR1_SETPEND45   0x2000U       // Set INTR45 Pending
#define NVIC_ISPR1_SETPEND46   0x4000U       // Set INTR46 Pending
#define NVIC_ISPR1_SETPEND47   0x8000U       // Set INTR47 Pending
#define NVIC_ISPR1_SETPEND48   0x10000U      // Set INTR48 Pending
#define NVIC_ISPR1_SETPEND49   0x20000U      // Set INTR49 Pending
#define NVIC_ISPR1_SETPEND50   0x40000U      // Set INTR50 Pending
#define NVIC_ISPR1_SETPEND51   0x80000U      // Set INTR51 Pending
#define NVIC_ISPR1_SETPEND52   0x100000U     // Set INTR52 Pending
#define NVIC_ISPR1_SETPEND53   0x200000U     // Set INTR53 Pending
#define NVIC_ISPR1_SETPEND54   0x400000U     // Set INTR54 Pending
#define NVIC_ISPR1_SETPEND55   0x800000U     // Set INTR55 Pending
#define NVIC_ISPR1_SETPEND56   0x1000000U    // Set INTR56 Pending
#define NVIC_ISPR1_SETPEND57   0x2000000U    // Set INTR57 Pending
#define NVIC_ISPR1_SETPEND58   0x4000000U    // Set INTR58 Pending
#define NVIC_ISPR1_SETPEND59   0x8000000U    // Set INTR59 Pending
#define NVIC_ISPR1_SETPEND60   0x10000000U   // Set INTR60 Pending
#define NVIC_ISPR1_SETPEND61   0x20000000U   // Set INTR61 Pending
#define NVIC_ISPR1_SETPEND62   0x40000000U   // Set INTR62 Pending
#define NVIC_ISPR1_SETPEND63   0x80000000U   // Set INTR63 Pending

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_ISPR2 register
//
//*************************************************************************************************
#define NVIC_ISPR2_SETPEND64   0x1U          // Set INTR64 Pending
#define NVIC_ISPR2_SETPEND65   0x2U          // Set INTR65 Pending
#define NVIC_ISPR2_SETPEND66   0x4U          // Set INTR66 Pending
#define NVIC_ISPR2_SETPEND67   0x8U          // Set INTR67 Pending
#define NVIC_ISPR2_SETPEND68   0x10U         // Set INTR68 Pending
#define NVIC_ISPR2_SETPEND69   0x20U         // Set INTR69 Pending
#define NVIC_ISPR2_SETPEND70   0x40U         // Set INTR70 Pending
#define NVIC_ISPR2_SETPEND71   0x80U         // Set INTR71 Pending
#define NVIC_ISPR2_SETPEND72   0x100U        // Set INTR72 Pending
#define NVIC_ISPR2_SETPEND73   0x200U        // Set INTR73 Pending
#define NVIC_ISPR2_SETPEND74   0x400U        // Set INTR74 Pending
#define NVIC_ISPR2_SETPEND75   0x800U        // Set INTR75 Pending
#define NVIC_ISPR2_SETPEND76   0x1000U       // Set INTR76 Pending
#define NVIC_ISPR2_SETPEND77   0x2000U       // Set INTR77 Pending
#define NVIC_ISPR2_SETPEND78   0x4000U       // Set INTR78 Pending
#define NVIC_ISPR2_SETPEND79   0x8000U       // Set INTR79 Pending
#define NVIC_ISPR2_SETPEND80   0x10000U      // Set INTR80 Pending
#define NVIC_ISPR2_SETPEND81   0x20000U      // Set INTR81 Pending
#define NVIC_ISPR2_SETPEND82   0x40000U      // Set INTR82 Pending
#define NVIC_ISPR2_SETPEND83   0x80000U      // Set INTR83 Pending
#define NVIC_ISPR2_SETPEND84   0x100000U     // Set INTR84 Pending
#define NVIC_ISPR2_SETPEND85   0x200000U     // Set INTR85 Pending
#define NVIC_ISPR2_SETPEND86   0x400000U     // Set INTR86 Pending
#define NVIC_ISPR2_SETPEND87   0x800000U     // Set INTR87 Pending
#define NVIC_ISPR2_SETPEND88   0x1000000U    // Set INTR88 Pending
#define NVIC_ISPR2_SETPEND89   0x2000000U    // Set INTR89 Pending
#define NVIC_ISPR2_SETPEND90   0x4000000U    // Set INTR90 Pending
#define NVIC_ISPR2_SETPEND91   0x8000000U    // Set INTR91 Pending
#define NVIC_ISPR2_SETPEND92   0x10000000U   // Set INTR92 Pending
#define NVIC_ISPR2_SETPEND93   0x20000000U   // Set INTR93 Pending
#define NVIC_ISPR2_SETPEND94   0x40000000U   // Set INTR94 Pending
#define NVIC_ISPR2_SETPEND95   0x80000000U   // Set INTR95 Pending

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_ICPR0 register
//
//*************************************************************************************************
#define NVIC_ICPR0_CLRPEND0    0x1U          // Clear INTR0 Pending
#define NVIC_ICPR0_CLRPEND1    0x2U          // Clear INTR1 Pending
#define NVIC_ICPR0_CLRPEND2    0x4U          // Clear INTR2 Pending
#define NVIC_ICPR0_CLRPEND3    0x8U          // Clear INTR3 Pending
#define NVIC_ICPR0_CLRPEND4    0x10U         // Clear INTR4 Pending
#define NVIC_ICPR0_CLRPEND5    0x20U         // Clear INTR5 Pending
#define NVIC_ICPR0_CLRPEND6    0x40U         // Clear INTR6 Pending
#define NVIC_ICPR0_CLRPEND7    0x80U         // Clear INTR7 Pending
#define NVIC_ICPR0_CLRPEND8    0x100U        // Clear INTR8 Pending
#define NVIC_ICPR0_CLRPEND9    0x200U        // Clear INTR9 Pending
#define NVIC_ICPR0_CLRPEND10   0x400U        // Clear INTR10 Pending
#define NVIC_ICPR0_CLRPEND11   0x800U        // Clear INTR11 Pending
#define NVIC_ICPR0_CLRPEND12   0x1000U       // Clear INTR12 Pending
#define NVIC_ICPR0_CLRPEND13   0x2000U       // Clear INTR13 Pending
#define NVIC_ICPR0_CLRPEND14   0x4000U       // Clear INTR14 Pending
#define NVIC_ICPR0_CLRPEND15   0x8000U       // Clear INTR15 Pending
#define NVIC_ICPR0_CLRPEND16   0x10000U      // Clear INTR16 Pending
#define NVIC_ICPR0_CLRPEND17   0x20000U      // Clear INTR17 Pending
#define NVIC_ICPR0_CLRPEND18   0x40000U      // Clear INTR18 Pending
#define NVIC_ICPR0_CLRPEND19   0x80000U      // Clear INTR19 Pending
#define NVIC_ICPR0_CLRPEND20   0x100000U     // Clear INTR20 Pending
#define NVIC_ICPR0_CLRPEND21   0x200000U     // Clear INTR21 Pending
#define NVIC_ICPR0_CLRPEND22   0x400000U     // Clear INTR22 Pending
#define NVIC_ICPR0_CLRPEND23   0x800000U     // Clear INTR23 Pending
#define NVIC_ICPR0_CLRPEND24   0x1000000U    // Clear INTR24 Pending
#define NVIC_ICPR0_CLRPEND25   0x2000000U    // Clear INTR25 Pending
#define NVIC_ICPR0_CLRPEND26   0x4000000U    // Clear INTR26 Pending
#define NVIC_ICPR0_CLRPEND27   0x8000000U    // Clear INTR27 Pending
#define NVIC_ICPR0_CLRPEND28   0x10000000U   // Clear INTR28 Pending
#define NVIC_ICPR0_CLRPEND29   0x20000000U   // Clear INTR29 Pending
#define NVIC_ICPR0_CLRPEND30   0x40000000U   // Clear INTR30 Pending
#define NVIC_ICPR0_CLRPEND31   0x80000000U   // Clear INTR31 Pending

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_ICPR1 register
//
//*************************************************************************************************
#define NVIC_ICPR1_CLRPEND32   0x1U          // Clear INTR32 Pending
#define NVIC_ICPR1_CLRPEND33   0x2U          // Clear INTR33 Pending
#define NVIC_ICPR1_CLRPEND34   0x4U          // Clear INTR34 Pending
#define NVIC_ICPR1_CLRPEND35   0x8U          // Clear INTR35 Pending
#define NVIC_ICPR1_CLRPEND36   0x10U         // Clear INTR36 Pending
#define NVIC_ICPR1_CLRPEND37   0x20U         // Clear INTR37 Pending
#define NVIC_ICPR1_CLRPEND38   0x40U         // Clear INTR38 Pending
#define NVIC_ICPR1_CLRPEND39   0x80U         // Clear INTR39 Pending
#define NVIC_ICPR1_CLRPEND40   0x100U        // Clear INTR40 Pending
#define NVIC_ICPR1_CLRPEND41   0x200U        // Clear INTR41 Pending
#define NVIC_ICPR1_CLRPEND42   0x400U        // Clear INTR42 Pending
#define NVIC_ICPR1_CLRPEND43   0x800U        // Clear INTR43 Pending
#define NVIC_ICPR1_CLRPEND44   0x1000U       // Clear INTR44 Pending
#define NVIC_ICPR1_CLRPEND45   0x2000U       // Clear INTR45 Pending
#define NVIC_ICPR1_CLRPEND46   0x4000U       // Clear INTR46 Pending
#define NVIC_ICPR1_CLRPEND47   0x8000U       // Clear INTR47 Pending
#define NVIC_ICPR1_CLRPEND48   0x10000U      // Clear INTR48 Pending
#define NVIC_ICPR1_CLRPEND49   0x20000U      // Clear INTR49 Pending
#define NVIC_ICPR1_CLRPEND50   0x40000U      // Clear INTR50 Pending
#define NVIC_ICPR1_CLRPEND51   0x80000U      // Clear INTR51 Pending
#define NVIC_ICPR1_CLRPEND52   0x100000U     // Clear INTR52 Pending
#define NVIC_ICPR1_CLRPEND53   0x200000U     // Clear INTR53 Pending
#define NVIC_ICPR1_CLRPEND54   0x400000U     // Clear INTR54 Pending
#define NVIC_ICPR1_CLRPEND55   0x800000U     // Clear INTR55 Pending
#define NVIC_ICPR1_CLRPEND56   0x1000000U    // Clear INTR56 Pending
#define NVIC_ICPR1_CLRPEND57   0x2000000U    // Clear INTR57 Pending
#define NVIC_ICPR1_CLRPEND58   0x4000000U    // Clear INTR58 Pending
#define NVIC_ICPR1_CLRPEND59   0x8000000U    // Clear INTR59 Pending
#define NVIC_ICPR1_CLRPEND60   0x10000000U   // Clear INTR60 Pending
#define NVIC_ICPR1_CLRPEND61   0x20000000U   // Clear INTR61 Pending
#define NVIC_ICPR1_CLRPEND62   0x40000000U   // Clear INTR62 Pending
#define NVIC_ICPR1_CLRPEND63   0x80000000U   // Clear INTR63 Pending

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IABR0 register
//
//*************************************************************************************************
#define NVIC_IABR0_ACTIVE0    0x1U          // INTR0 Active
#define NVIC_IABR0_ACTIVE1    0x2U          // INTR1 Active
#define NVIC_IABR0_ACTIVE2    0x4U          // INTR2 Active
#define NVIC_IABR0_ACTIVE3    0x8U          // INTR3 Active
#define NVIC_IABR0_ACTIVE4    0x10U         // INTR4 Active
#define NVIC_IABR0_ACTIVE5    0x20U         // INTR5 Active
#define NVIC_IABR0_ACTIVE6    0x40U         // INTR6 Active
#define NVIC_IABR0_ACTIVE7    0x80U         // INTR7 Active
#define NVIC_IABR0_ACTIVE8    0x100U        // INTR8 Active
#define NVIC_IABR0_ACTIVE9    0x200U        // INTR9 Active
#define NVIC_IABR0_ACTIVE10   0x400U        // INTR10 Active
#define NVIC_IABR0_ACTIVE11   0x800U        // INTR11 Active
#define NVIC_IABR0_ACTIVE12   0x1000U       // INTR12 Active
#define NVIC_IABR0_ACTIVE13   0x2000U       // INTR13 Active
#define NVIC_IABR0_ACTIVE14   0x4000U       // INTR14 Active
#define NVIC_IABR0_ACTIVE15   0x8000U       // INTR15 Active
#define NVIC_IABR0_ACTIVE16   0x10000U      // INTR16 Active
#define NVIC_IABR0_ACTIVE17   0x20000U      // INTR17 Active
#define NVIC_IABR0_ACTIVE18   0x40000U      // INTR18 Active
#define NVIC_IABR0_ACTIVE19   0x80000U      // INTR19 Active
#define NVIC_IABR0_ACTIVE20   0x100000U     // INTR20 Active
#define NVIC_IABR0_ACTIVE21   0x200000U     // INTR21 Active
#define NVIC_IABR0_ACTIVE22   0x400000U     // INTR22 Active
#define NVIC_IABR0_ACTIVE23   0x800000U     // INTR23 Active
#define NVIC_IABR0_ACTIVE24   0x1000000U    // INTR24 Active
#define NVIC_IABR0_ACTIVE25   0x2000000U    // INTR25 Active
#define NVIC_IABR0_ACTIVE26   0x4000000U    // INTR26 Active
#define NVIC_IABR0_ACTIVE27   0x8000000U    // INTR27 Active
#define NVIC_IABR0_ACTIVE28   0x10000000U   // INTR28 Active
#define NVIC_IABR0_ACTIVE29   0x20000000U   // INTR29 Active
#define NVIC_IABR0_ACTIVE30   0x40000000U   // INTR30 Active
#define NVIC_IABR0_ACTIVE31   0x80000000U   // INTR31 Active

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IABR1 register
//
//*************************************************************************************************
#define NVIC_IABR1_ACTIVE32   0x1U          // INTR32 Active
#define NVIC_IABR1_ACTIVE33   0x2U          // INTR33 Active
#define NVIC_IABR1_ACTIVE34   0x4U          // INTR34 Active
#define NVIC_IABR1_ACTIVE35   0x8U          // INTR35 Active
#define NVIC_IABR1_ACTIVE36   0x10U         // INTR36 Active
#define NVIC_IABR1_ACTIVE37   0x20U         // INTR37 Active
#define NVIC_IABR1_ACTIVE38   0x40U         // INTR38 Active
#define NVIC_IABR1_ACTIVE39   0x80U         // INTR39 Active
#define NVIC_IABR1_ACTIVE40   0x100U        // INTR40 Active
#define NVIC_IABR1_ACTIVE41   0x200U        // INTR41 Active
#define NVIC_IABR1_ACTIVE42   0x400U        // INTR42 Active
#define NVIC_IABR1_ACTIVE43   0x800U        // INTR43 Active
#define NVIC_IABR1_ACTIVE44   0x1000U       // INTR44 Active
#define NVIC_IABR1_ACTIVE45   0x2000U       // INTR45 Active
#define NVIC_IABR1_ACTIVE46   0x4000U       // INTR46 Active
#define NVIC_IABR1_ACTIVE47   0x8000U       // INTR47 Active
#define NVIC_IABR1_ACTIVE48   0x10000U      // INTR48 Active
#define NVIC_IABR1_ACTIVE49   0x20000U      // INTR49 Active
#define NVIC_IABR1_ACTIVE50   0x40000U      // INTR50 Active
#define NVIC_IABR1_ACTIVE51   0x80000U      // INTR51 Active
#define NVIC_IABR1_ACTIVE52   0x100000U     // INTR52 Active
#define NVIC_IABR1_ACTIVE53   0x200000U     // INTR53 Active
#define NVIC_IABR1_ACTIVE54   0x400000U     // INTR54 Active
#define NVIC_IABR1_ACTIVE55   0x800000U     // INTR55 Active
#define NVIC_IABR1_ACTIVE56   0x1000000U    // INTR56 Active
#define NVIC_IABR1_ACTIVE57   0x2000000U    // INTR57 Active
#define NVIC_IABR1_ACTIVE58   0x4000000U    // INTR58 Active
#define NVIC_IABR1_ACTIVE59   0x8000000U    // INTR59 Active
#define NVIC_IABR1_ACTIVE60   0x10000000U   // INTR60 Active
#define NVIC_IABR1_ACTIVE61   0x20000000U   // INTR61 Active
#define NVIC_IABR1_ACTIVE62   0x40000000U   // INTR62 Active
#define NVIC_IABR1_ACTIVE63   0x80000000U   // INTR63 Active

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR0 register
//
//*************************************************************************************************
#define NVIC_IPR0_PRI_0_S   5U
#define NVIC_IPR0_PRI_0_M   0xE0U         // Priority, byte offset 0
#define NVIC_IPR0_PRI_1_S   13U
#define NVIC_IPR0_PRI_1_M   0xE000U       // Priority, byte offset 1
#define NVIC_IPR0_PRI_2_S   21U
#define NVIC_IPR0_PRI_2_M   0xE00000U     // Priority, byte offset 2
#define NVIC_IPR0_PRI_3_S   29U
#define NVIC_IPR0_PRI_3_M   0xE0000000U   // Priority, byte offset 3

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR1 register
//
//*************************************************************************************************
#define NVIC_IPR1_PRI_4_S   5U
#define NVIC_IPR1_PRI_4_M   0xE0U         // Priority, byte offset 4
#define NVIC_IPR1_PRI_5_S   13U
#define NVIC_IPR1_PRI_5_M   0xE000U       // Priority, byte offset 5
#define NVIC_IPR1_PRI_6_S   21U
#define NVIC_IPR1_PRI_6_M   0xE00000U     // Priority, byte offset 6
#define NVIC_IPR1_PRI_7_S   29U
#define NVIC_IPR1_PRI_7_M   0xE0000000U   // Priority, byte offset 7

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR2 register
//
//*************************************************************************************************
#define NVIC_IPR2_PRI_8_S    5U
#define NVIC_IPR2_PRI_8_M    0xE0U         // Priority, byte offset 8
#define NVIC_IPR2_PRI_9_S    13U
#define NVIC_IPR2_PRI_9_M    0xE000U       // Priority, byte offset 9
#define NVIC_IPR2_PRI_10_S   21U
#define NVIC_IPR2_PRI_10_M   0xE00000U     // Priority, byte offset 10
#define NVIC_IPR2_PRI_11_S   29U
#define NVIC_IPR2_PRI_11_M   0xE0000000U   // Priority, byte offset 11

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR3 register
//
//*************************************************************************************************
#define NVIC_IPR3_PRI_12_S   5U
#define NVIC_IPR3_PRI_12_M   0xE0U         // Priority, byte offset 12
#define NVIC_IPR3_PRI_13_S   13U
#define NVIC_IPR3_PRI_13_M   0xE000U       // Priority, byte offset 13
#define NVIC_IPR3_PRI_14_S   21U
#define NVIC_IPR3_PRI_14_M   0xE00000U     // Priority, byte offset 14
#define NVIC_IPR3_PRI_15_S   29U
#define NVIC_IPR3_PRI_15_M   0xE0000000U   // Priority, byte offset 15

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR4 register
//
//*************************************************************************************************
#define NVIC_IPR4_PRI_16_S   5U
#define NVIC_IPR4_PRI_16_M   0xE0U         // Priority, byte offset 16
#define NVIC_IPR4_PRI_17_S   13U
#define NVIC_IPR4_PRI_17_M   0xE000U       // Priority, byte offset 17
#define NVIC_IPR4_PRI_18_S   21U
#define NVIC_IPR4_PRI_18_M   0xE00000U     // Priority, byte offset 18
#define NVIC_IPR4_PRI_19_S   29U
#define NVIC_IPR4_PRI_19_M   0xE0000000U   // Priority, byte offset 19

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR5 register
//
//*************************************************************************************************
#define NVIC_IPR5_PRI_20_S   5U
#define NVIC_IPR5_PRI_20_M   0xE0U         // Priority, byte offset 20
#define NVIC_IPR5_PRI_21_S   13U
#define NVIC_IPR5_PRI_21_M   0xE000U       // Priority, byte offset 21
#define NVIC_IPR5_PRI_22_S   21U
#define NVIC_IPR5_PRI_22_M   0xE00000U     // Priority, byte offset 22
#define NVIC_IPR5_PRI_23_S   29U
#define NVIC_IPR5_PRI_23_M   0xE0000000U   // Priority, byte offset 23

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR6 register
//
//*************************************************************************************************
#define NVIC_IPR6_PRI_24_S   5U
#define NVIC_IPR6_PRI_24_M   0xE0U         // Priority, byte offset 24
#define NVIC_IPR6_PRI_25_S   13U
#define NVIC_IPR6_PRI_25_M   0xE000U       // Priority, byte offset 25
#define NVIC_IPR6_PRI_26_S   21U
#define NVIC_IPR6_PRI_26_M   0xE00000U     // Priority, byte offset 26
#define NVIC_IPR6_PRI_27_S   29U
#define NVIC_IPR6_PRI_27_M   0xE0000000U   // Priority, byte offset 27

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR7 register
//
//*************************************************************************************************
#define NVIC_IPR7_PRI_28_S   5U
#define NVIC_IPR7_PRI_28_M   0xE0U         // Priority, byte offset 28
#define NVIC_IPR7_PRI_29_S   13U
#define NVIC_IPR7_PRI_29_M   0xE000U       // Priority, byte offset 29
#define NVIC_IPR7_PRI_30_S   21U
#define NVIC_IPR7_PRI_30_M   0xE00000U     // Priority, byte offset 30
#define NVIC_IPR7_PRI_31_S   29U
#define NVIC_IPR7_PRI_31_M   0xE0000000U   // Priority, byte offset 31

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR8 register
//
//*************************************************************************************************
#define NVIC_IPR8_PRI_32_S   5U
#define NVIC_IPR8_PRI_32_M   0xE0U         // Priority, byte offset 32
#define NVIC_IPR8_PRI_33_S   13U
#define NVIC_IPR8_PRI_33_M   0xE000U       // Priority, byte offset 33
#define NVIC_IPR8_PRI_34_S   21U
#define NVIC_IPR8_PRI_34_M   0xE00000U     // Priority, byte offset 34
#define NVIC_IPR8_PRI_35_S   29U
#define NVIC_IPR8_PRI_35_M   0xE0000000U   // Priority, byte offset 35

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR9 register
//
//*************************************************************************************************
#define NVIC_IPR9_PRI_36_S   5U
#define NVIC_IPR9_PRI_36_M   0xE0U         // Priority, byte offset 36
#define NVIC_IPR9_PRI_37_S   13U
#define NVIC_IPR9_PRI_37_M   0xE000U       // Priority, byte offset 37
#define NVIC_IPR9_PRI_38_S   21U
#define NVIC_IPR9_PRI_38_M   0xE00000U     // Priority, byte offset 38
#define NVIC_IPR9_PRI_39_S   29U
#define NVIC_IPR9_PRI_39_M   0xE0000000U   // Priority, byte offset 39

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR10 register
//
//*************************************************************************************************
#define NVIC_IPR10_PRI_40_S   5U
#define NVIC_IPR10_PRI_40_M   0xE0U         // Priority, byte offset 40
#define NVIC_IPR10_PRI_41_S   13U
#define NVIC_IPR10_PRI_41_M   0xE000U       // Priority, byte offset 41
#define NVIC_IPR10_PRI_42_S   21U
#define NVIC_IPR10_PRI_42_M   0xE00000U     // Priority, byte offset 42
#define NVIC_IPR10_PRI_43_S   29U
#define NVIC_IPR10_PRI_43_M   0xE0000000U   // Priority, byte offset 43

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR11 register
//
//*************************************************************************************************
#define NVIC_IPR11_PRI_44_S   5U
#define NVIC_IPR11_PRI_44_M   0xE0U         // Priority, byte offset 44
#define NVIC_IPR11_PRI_45_S   13U
#define NVIC_IPR11_PRI_45_M   0xE000U       // Priority, byte offset 45
#define NVIC_IPR11_PRI_46_S   21U
#define NVIC_IPR11_PRI_46_M   0xE00000U     // Priority, byte offset 46
#define NVIC_IPR11_PRI_47_S   29U
#define NVIC_IPR11_PRI_47_M   0xE0000000U   // Priority, byte offset 47

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR12 register
//
//*************************************************************************************************
#define NVIC_IPR12_PRI_48_S   5U
#define NVIC_IPR12_PRI_48_M   0xE0U         // Priority, byte offset 48
#define NVIC_IPR12_PRI_49_S   13U
#define NVIC_IPR12_PRI_49_M   0xE000U       // Priority, byte offset 49
#define NVIC_IPR12_PRI_50_S   21U
#define NVIC_IPR12_PRI_50_M   0xE00000U     // Priority, byte offset 50
#define NVIC_IPR12_PRI_51_S   29U
#define NVIC_IPR12_PRI_51_M   0xE0000000U   // Priority, byte offset 51

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR13 register
//
//*************************************************************************************************
#define NVIC_IPR13_PRI_52_S   5U
#define NVIC_IPR13_PRI_52_M   0xE0U         // Priority, byte offset 52
#define NVIC_IPR13_PRI_53_S   13U
#define NVIC_IPR13_PRI_53_M   0xE000U       // Priority, byte offset 53
#define NVIC_IPR13_PRI_54_S   21U
#define NVIC_IPR13_PRI_54_M   0xE00000U     // Priority, byte offset 54
#define NVIC_IPR13_PRI_55_S   29U
#define NVIC_IPR13_PRI_55_M   0xE0000000U   // Priority, byte offset 55

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR14 register
//
//*************************************************************************************************
#define NVIC_IPR14_PRI_56_S   5U
#define NVIC_IPR14_PRI_56_M   0xE0U         // Priority, byte offset 56
#define NVIC_IPR14_PRI_57_S   13U
#define NVIC_IPR14_PRI_57_M   0xE000U       // Priority, byte offset 57
#define NVIC_IPR14_PRI_58_S   21U
#define NVIC_IPR14_PRI_58_M   0xE00000U     // Priority, byte offset 58
#define NVIC_IPR14_PRI_59_S   29U
#define NVIC_IPR14_PRI_59_M   0xE0000000U   // Priority, byte offset 59

//*************************************************************************************************
//
// The following are defines for the bit fields in the NVIC_IPR15 register
//
//*************************************************************************************************
#define NVIC_IPR15_PRI_60_S   5U
#define NVIC_IPR15_PRI_60_M   0xE0U         // Priority, byte offset 60
#define NVIC_IPR15_PRI_61_S   13U
#define NVIC_IPR15_PRI_61_M   0xE000U       // Priority, byte offset 61
#define NVIC_IPR15_PRI_62_S   21U
#define NVIC_IPR15_PRI_62_M   0xE00000U     // Priority, byte offset 62
#define NVIC_IPR15_PRI_63_S   29U
#define NVIC_IPR15_PRI_63_M   0xE0000000U   // Priority, byte offset 63

//*************************************************************************************************
//
// The following are defines for the bit fields in the STIR register
//
//*************************************************************************************************
#define NVIC_STIR_INTID_S   0U
#define NVIC_STIR_INTID_M   0x1FFU   // Software Trigger Interrupt Register.


//*************************************************************************************************
//
// The following are defines for the bit fields in the ACTLR register
//
//*************************************************************************************************
#define NVIC_ACTLR_DISMCYCINT   0x1U     // Disable interruption of load/store multiple
                                         // instruction.
#define NVIC_ACTLR_DISDEFWBUF   0x2U     // Disable write buffer on default memory map.
#define NVIC_ACTLR_DISFOLD      0x4U     // Disables IT folding.
#define NVIC_ACTLR_DISFPCA      0x100U   // Disables automatic update of CONTROL.FPCA.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPUID register
//
//*************************************************************************************************
#define NVIC_CPUID_REVISION_S      0U
#define NVIC_CPUID_REVISION_M      0xFU          // Revision
#define NVIC_CPUID_PARTNO_S        4U
#define NVIC_CPUID_PARTNO_M        0xFFF0U       // PartNo
#define NVIC_CPUID_CONSTANT_S      16U
#define NVIC_CPUID_CONSTANT_M      0xF0000U      // Constant
#define NVIC_CPUID_VARIANT_S       20U
#define NVIC_CPUID_VARIANT_M       0xF00000U     // Variant
#define NVIC_CPUID_IMPLEMENTER_S   24U
#define NVIC_CPUID_IMPLEMENTER_M   0xFF000000U   // Implementer

//*************************************************************************************************
//
// The following are defines for the bit fields in the ICSR register
//
//*************************************************************************************************
#define NVIC_ICSR_VECTACTIVE_S    0U
#define NVIC_ICSR_VECTACTIVE_M    0x1FFU        //  Active exception number
#define NVIC_ICSR_RETTOBASE       0x800U        // Indicates presence of preempted active
                                                // exceptions.
#define NVIC_ICSR_VECTPENDING_S   12U
#define NVIC_ICSR_VECTPENDING_M   0x3F000U      // Exception number of highest priority pending
                                                // exception.
#define NVIC_ICSR_ISRPENDING      0x400000U     // Interrupt pending flag
#define NVIC_ICSR_PENDSTCLR       0x2000000U    // SysTick exception clear-pending bit
#define NVIC_ICSR_PENDSTSET       0x4000000U    // SysTick exception set-pending bit.
#define NVIC_ICSR_PENDSVCLR       0x8000000U    // PendSV clear-pending bit.
#define NVIC_ICSR_PENDSVSET       0x10000000U   // PendSV set-pending bit.
#define NVIC_ICSR_NMIPENDSET      0x80000000U   // NMI set-pending bit.

//*************************************************************************************************
//
// The following are defines for the bit fields in the VTOR register
//
//*************************************************************************************************
#define NVIC_VTOR_TBLOFF_S   7U
#define NVIC_VTOR_TBLOFF_M   0xFFFFFF80U   // Vector table offset.

//*************************************************************************************************
//
// The following are defines for the bit fields in the AIRCR register
//
//*************************************************************************************************
#define NVIC_AIRCR_VECTRESET       0x1U          // CPU Reset
#define NVIC_AIRCR_VECTCLRACTIVE   0x2U          // Reserved for Debug use.
#define NVIC_AIRCR_SYSRESETREQ     0x4U          // System reset request bit
#define NVIC_AIRCR_PRIGROUP_S      8U
#define NVIC_AIRCR_PRIGROUP_M      0x700U        // Interrupt priority grouping field
#define NVIC_AIRCR_ENDIANNESS      0x8000U       // Data endianness bit
#define NVIC_AIRCR_VECTKEY_S       16U
#define NVIC_AIRCR_VECTKEY_M       0xFFFF0000U   // Vector Key.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SCR register
//
//*************************************************************************************************
#define NVIC_SCR_SLEEPONEXIT   0x2U   // sleep-on-exit when returning from Handler mode.

//*************************************************************************************************
//
// The following are defines for the bit fields in the CCR register
//
//*************************************************************************************************
#define NVIC_CCR_NONBASETHRDENA   0x1U     // Indicates how the processor enters Thread mode
#define NVIC_CCR_USERSETMPEND     0x2U     // Enables unprivileged software access to the STIR.
#define NVIC_CCR_UNALIGN_TRP      0x8U     // Enables unaligned access traps.
#define NVIC_CCR_DIV_0_TRP        0x10U    // faulting/halting on DIV by 0 exception.
#define NVIC_CCR_BFHFNMIGN        0x100U   // Ignore data BusFaults caused by load and store
                                           // instructions.
#define NVIC_CCR_STKALIGN         0x200U   // Indicates stack alignment on exception entry.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SHPR1 register
//
//*************************************************************************************************
#define NVIC_SHPR1_PRI_4_S   5U
#define NVIC_SHPR1_PRI_4_M   0xE0U       // Priority of system handler 4, MemManage
#define NVIC_SHPR1_PRI_5_S   13U
#define NVIC_SHPR1_PRI_5_M   0xE000U     // Priority of system handler 5,  BusFault
#define NVIC_SHPR1_PRI_6_S   21U
#define NVIC_SHPR1_PRI_6_M   0xE00000U   // Priority of system handler 6, UsageFault

//*************************************************************************************************
//
// The following are defines for the bit fields in the SHPR2 register
//
//*************************************************************************************************
#define NVIC_SHPR2_PRI_11_S   29U
#define NVIC_SHPR2_PRI_11_M   0xE0000000U   // Priority of system handler 11, SVCall

//*************************************************************************************************
//
// The following are defines for the bit fields in the SHPR3 register
//
//*************************************************************************************************
#define NVIC_SHPR3_PRI_14_S   21U
#define NVIC_SHPR3_PRI_14_M   0xE00000U     // Priority of system handler 14, PendSV
#define NVIC_SHPR3_PRI_15_S   29U
#define NVIC_SHPR3_PRI_15_M   0xE0000000U   // Priority of system handler 15, SysTick exception

//*************************************************************************************************
//
// The following are defines for the bit fields in the SHCSRS register
//
//*************************************************************************************************
#define NVIC_SHCSRS_MEMFAULTACT      0x1U       // MemManage exception active bit
#define NVIC_SHCSRS_BUSFAULTACT      0x2U       // BusFault exception active bit
#define NVIC_SHCSRS_USGFAULTACT      0x8U       // UsageFault exception active bit
#define NVIC_SHCSRS_SVCALLACT        0x80U      // SVCall active bit
#define NVIC_SHCSRS_MONITORACT       0x100U     // Debug monitor active bit
#define NVIC_SHCSRS_PENDSVACT        0x400U     // PendSV exception active bit
#define NVIC_SHCSRS_SYSTICKACT       0x800U     // SysTick exception active bit
#define NVIC_SHCSRS_USGFAULTPENDED   0x1000U    // UsageFault exception pending bit
#define NVIC_SHCSRS_MEMFAULTPENDED   0x2000U    // MemManage exception pending bit
#define NVIC_SHCSRS_BUSFAULTPENDED   0x4000U    // BusFault exception pending bit
#define NVIC_SHCSRS_SVCALLPENDED     0x8000U    // SVCall pending bit
#define NVIC_SHCSRS_MEMFAULTENA      0x10000U   // MemManage enable bit
#define NVIC_SHCSRS_BUSFAULTENA      0x20000U   // BusFault enable bit
#define NVIC_SHCSRS_USGFAULTENA      0x40000U   // UsageFault enable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CFSR register
//
//*************************************************************************************************
#define NVIC_CFSR_IACCVIOL      0x1U         // Instruction access violation flag
#define NVIC_CFSR_DACCVIOL      0x2U         // Data access violation flag
#define NVIC_CFSR_MUNSTKERR     0x8U         // MemManage fault on unstacking for a return from
                                             // exception
#define NVIC_CFSR_MSTKERR       0x10U        // MemManage fault on stacking for exception entry
#define NVIC_CFSR_MMARVALID     0x80U        // MemManage Fault Address Register (MMFAR) valid flag
#define NVIC_CFSR_IBUSERR       0x100U       // Instruction bus error
#define NVIC_CFSR_PRECISERR     0x200U       // Precise data bus error
#define NVIC_CFSR_IMPRECISERR   0x400U       // Imprecise data bus error
#define NVIC_CFSR_UNSTKERR      0x800U       // BusFault on unstacking for a return from exception
#define NVIC_CFSR_STKERR        0x1000U      // BusFault on stacking for exception entry
#define NVIC_CFSR_BFARVALID     0x8000U      // BusFault Address Register (BFAR) valid flag
#define NVIC_CFSR_UNDEFINSTR    0x10000U     // Undefined instruction UsageFault
#define NVIC_CFSR_INVSTATE      0x20000U     // Invalid state UsageFault
#define NVIC_CFSR_INVPC         0x40000U     // Invalid PC load UsageFault
#define NVIC_CFSR_NOCP          0x80000U     // No coprocessor UsageFault
#define NVIC_CFSR_UNALIGNED     0x1000000U   // Unaligned access UsageFault
#define NVIC_CFSR_DIVBYZERO     0x2000000U   // Divide by zero UsageFault

//*************************************************************************************************
//
// The following are defines for the bit fields in the HFSR register
//
//*************************************************************************************************
#define NVIC_HFSR_VECTTBL    0x2U          // BusFault on a vector table read.
#define NVIC_HFSR_FORCED     0x40000000U   // Indicates a forced hard fault
#define NVIC_HFSR_DEBUGEVT   0x80000000U   // Indicates a forced DEBUG event fault


//*************************************************************************************************
//
// The following are defines for the bit fields in the MMSR register
//
//*************************************************************************************************
#define NVIC_MMSR_IACCVIOL    0x1U    // Instruction access violation flag
#define NVIC_MMSR_DACCVIOL    0x2U    // Data access violation flag
#define NVIC_MMSR_MUNSTKERR   0x8U    // MemManage fault on unstacking for a return from exception
#define NVIC_MMSR_MSTKERR     0x10U   // MemManage fault on stacking for exception entry
#define NVIC_MMSR_MMARVALID   0x80U   // MemManage Fault Address Register (MMFAR) valid flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the BFSR register
//
//*************************************************************************************************
#define NVIC_BFSR_IBUSERR       0x1U    // Instruction bus error
#define NVIC_BFSR_PRECISERR     0x2U    // Precise data bus error
#define NVIC_BFSR_IMPRECISERR   0x4U    // Imprecise data bus error
#define NVIC_BFSR_UNSTKERR      0x8U    // BusFault on unstacking for a return from exception
#define NVIC_BFSR_STKERR        0x10U   // BusFault on stacking for exception entry
#define NVIC_BFSR_BFARVALID     0x80U   // BusFault Address Register (BFAR) valid flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the UFSR register
//
//*************************************************************************************************
#define NVIC_UFSR_UNDEFINSTR   0x1U     // Undefined instruction UsageFault
#define NVIC_UFSR_INVSTATE     0x2U     // Invalid state UsageFault
#define NVIC_UFSR_INVPC        0x4U     // Invalid PC load UsageFault
#define NVIC_UFSR_NOCP         0x8U     // No coprocessor UsageFault
#define NVIC_UFSR_UNALIGNED    0x100U   // Unaligned access UsageFault
#define NVIC_UFSR_DIVBYZERO    0x200U   // Divide by zero UsageFault


//*************************************************************************************************
//
// The following are defines for the bit fields in the SYST_CSR register
//
//*************************************************************************************************
#define NVIC_SYST_CSR_ENABLE      0x1U       // Enables the counter
#define NVIC_SYST_CSR_TICKINT     0x2U       // Enables SysTick exception request
#define NVIC_SYST_CSR_CLKSOURCE   0x4U       // Indicates the clock source
#define NVIC_SYST_CSR_COUNTFLAG   0x10000U   // timer counted to 0 since last read.

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYST_RVR register
//
//*************************************************************************************************
#define NVIC_SYST_RVR_RELOAD_S   0U
#define NVIC_SYST_RVR_RELOAD_M   0xFFFFFFU   // Counter reload value

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYST_CVR register
//
//*************************************************************************************************
#define NVIC_SYST_CVR_CURRENT_S   0U
#define NVIC_SYST_CVR_CURRENT_M   0xFFFFFFU   // Current counter value

//*************************************************************************************************
//
// The following are defines for the bit fields in the SYST_CALIB register
//
//*************************************************************************************************
#define NVIC_SYST_CALIB_TENMS_S   0U
#define NVIC_SYST_CALIB_TENMS_M   0xFFFFFFU     // Current counter value
#define NVIC_SYST_CALIB_SKEW      0x40000000U   // Indicates whether the TENMS value is exact
#define NVIC_SYST_CALIB_NOREF     0x80000000U   // Device provides a reference clock to the
                                                // processor


//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_TYPE register
//
//*************************************************************************************************
#define NVIC_MPU_TYPE_SEPARATE    0x1U        // unified/separate instruction and date memory maps
#define NVIC_MPU_TYPE_DREGION_S   8U
#define NVIC_MPU_TYPE_DREGION_M   0xFF00U     // Indicates the number of supported MPU data regions
#define NVIC_MPU_TYPE_IREGION_S   16U
#define NVIC_MPU_TYPE_IREGION_M   0xFF0000U   // Indicates the number of supported MPU instruction
                                              // regions

//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_CTRL register
//
//*************************************************************************************************
#define NVIC_MPU_CTRL_ENABLE       0x1U   // Enables the MPU
#define NVIC_MPU_CTRL_HFNMIENA     0x2U   // Enables MPU during hard fault, NMI, and FAULTMASK
                                          // handlers.
#define NVIC_MPU_CTRL_PRIVDEFENA   0x4U   // Enables privileged software access to the default
                                          // memory map

//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_RNR register
//
//*************************************************************************************************
#define NVIC_MPU_RNR_REGION_S   0U
#define NVIC_MPU_RNR_REGION_M   0xFFU   // MPU region referred by the MPU_RBAR and MPU_RASR
                                        // registers.

//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_RBAR register
//
//*************************************************************************************************
#define NVIC_MPU_RBAR_REGION_S   0U
#define NVIC_MPU_RBAR_REGION_M   0xFU          // MPU region field
#define NVIC_MPU_RBAR_VALID      0x10U         // MPU Region Number valid bit
#define NVIC_MPU_RBAR_ADDR_S     5U
#define NVIC_MPU_RBAR_ADDR_M     0xFFFFFFE0U   // Region base address field

//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_RASR register
//
//*************************************************************************************************
#define NVIC_MPU_RASR_ENABLE   0x1U          // Region enable bit.
#define NVIC_MPU_RASR_SIZE_S   1U
#define NVIC_MPU_RASR_SIZE_M   0x3EU         // Specifies the size of the MPU protection region.
#define NVIC_MPU_RASR_SRD_S    8U
#define NVIC_MPU_RASR_SRD_M    0xFF00U       // Subregion disable bits
#define NVIC_MPU_RASR_B        0x10000U      // Memory access attribute
#define NVIC_MPU_RASR_C        0x20000U      // Memory access attribute
#define NVIC_MPU_RASR_S        0x40000U      // Memory access attribute
#define NVIC_MPU_RASR_TEX_S    19U
#define NVIC_MPU_RASR_TEX_M    0x380000U     // Memory access attribute
#define NVIC_MPU_RASR_AP_S     24U
#define NVIC_MPU_RASR_AP_M     0x7000000U    // Memory access attribute
#define NVIC_MPU_RASR_XN       0x10000000U   // Instruction access disable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_RBAR_A1 register
//
//*************************************************************************************************
#define NVIC_MPU_RBAR_A1_REGION_S   0U
#define NVIC_MPU_RBAR_A1_REGION_M   0xFU          // MPU region field
#define NVIC_MPU_RBAR_A1_VALID      0x10U         // MPU Region Number valid bit
#define NVIC_MPU_RBAR_A1_ADDR_S     5U
#define NVIC_MPU_RBAR_A1_ADDR_M     0xFFFFFFE0U   // Region base address field

//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_RASR_A1 register
//
//*************************************************************************************************
#define NVIC_MPU_RASR_A1_ENABLE   0x1U          // Region enable bit.
#define NVIC_MPU_RASR_A1_SIZE_S   1U
#define NVIC_MPU_RASR_A1_SIZE_M   0x3EU         // Specifies the size of the MPU protection region.
#define NVIC_MPU_RASR_A1_SRD_S    8U
#define NVIC_MPU_RASR_A1_SRD_M    0xFF00U       // Subregion disable bits
#define NVIC_MPU_RASR_A1_B        0x10000U      // Memory access attribute
#define NVIC_MPU_RASR_A1_C        0x20000U      // Memory access attribute
#define NVIC_MPU_RASR_A1_S        0x40000U      // Memory access attribute
#define NVIC_MPU_RASR_A1_TEX_S    19U
#define NVIC_MPU_RASR_A1_TEX_M    0x380000U     // Memory access attribute
#define NVIC_MPU_RASR_A1_AP_S     24U
#define NVIC_MPU_RASR_A1_AP_M     0x7000000U    // Memory access attribute
#define NVIC_MPU_RASR_A1_XN       0x10000000U   // Instruction access disable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_RBAR_A2 register
//
//*************************************************************************************************
#define NVIC_MPU_RBAR_A2_REGION_S   0U
#define NVIC_MPU_RBAR_A2_REGION_M   0xFU          // MPU region field
#define NVIC_MPU_RBAR_A2_VALID      0x10U         // MPU Region Number valid bit
#define NVIC_MPU_RBAR_A2_ADDR_S     5U
#define NVIC_MPU_RBAR_A2_ADDR_M     0xFFFFFFE0U   // Region base address field

//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_RASR_A2 register
//
//*************************************************************************************************
#define NVIC_MPU_RASR_A2_ENABLE   0x1U          // Region enable bit.
#define NVIC_MPU_RASR_A2_SIZE_S   1U
#define NVIC_MPU_RASR_A2_SIZE_M   0x3EU         // Specifies the size of the MPU protection region.
#define NVIC_MPU_RASR_A2_SRD_S    8U
#define NVIC_MPU_RASR_A2_SRD_M    0xFF00U       // Subregion disable bits
#define NVIC_MPU_RASR_A2_B        0x10000U      // Memory access attribute
#define NVIC_MPU_RASR_A2_C        0x20000U      // Memory access attribute
#define NVIC_MPU_RASR_A2_S        0x40000U      // Memory access attribute
#define NVIC_MPU_RASR_A2_TEX_S    19U
#define NVIC_MPU_RASR_A2_TEX_M    0x380000U     // Memory access attribute
#define NVIC_MPU_RASR_A2_AP_S     24U
#define NVIC_MPU_RASR_A2_AP_M     0x7000000U    // Memory access attribute
#define NVIC_MPU_RASR_A2_XN       0x10000000U   // Instruction access disable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_RBAR_A3 register
//
//*************************************************************************************************
#define NVIC_MPU_RBAR_A3_REGION_S   0U
#define NVIC_MPU_RBAR_A3_REGION_M   0xFU          // MPU region field
#define NVIC_MPU_RBAR_A3_VALID      0x10U         // MPU Region Number valid bit
#define NVIC_MPU_RBAR_A3_ADDR_S     5U
#define NVIC_MPU_RBAR_A3_ADDR_M     0xFFFFFFE0U   // Region base address field

//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_RASR_A3 register
//
//*************************************************************************************************
#define NVIC_MPU_RASR_A3_ENABLE   0x1U          // Region enable bit.
#define NVIC_MPU_RASR_A3_SIZE_S   1U
#define NVIC_MPU_RASR_A3_SIZE_M   0x3EU         // Specifies the size of the MPU protection region.
#define NVIC_MPU_RASR_A3_SRD_S    8U
#define NVIC_MPU_RASR_A3_SRD_M    0xFF00U       // Subregion disable bits
#define NVIC_MPU_RASR_A3_B        0x10000U      // Memory access attribute
#define NVIC_MPU_RASR_A3_C        0x20000U      // Memory access attribute
#define NVIC_MPU_RASR_A3_S        0x40000U      // Memory access attribute
#define NVIC_MPU_RASR_A3_TEX_S    19U
#define NVIC_MPU_RASR_A3_TEX_M    0x380000U     // Memory access attribute
#define NVIC_MPU_RASR_A3_AP_S     24U
#define NVIC_MPU_RASR_A3_AP_M     0x7000000U    // Memory access attribute
#define NVIC_MPU_RASR_A3_XN       0x10000000U   // Instruction access disable bit



#endif
