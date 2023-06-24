//###########################################################################
//
// FILE:    hw_cmmpu.h
//
// TITLE:   Definitions for the CMMPU registers.
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

#ifndef HW_CMMPU_H
#define HW_CMMPU_H

//*************************************************************************************************
//
// The following are defines for the CMMPU register offsets
//
//*************************************************************************************************
#define CMMPU_O_MPU_CONTROL_REG         0x0U    // MPU control regster
#define CMMPU_O_ACC_VIO_INTEN           0x20U   // Access violation interrupt enable
#define CMMPU_O_ACC_VIO_FLAGS           0x24U   // Access violation flag register
#define CMMPU_O_ACC_VIO_FLAGS_SET       0x28U   // Acesss violation set register
#define CMMPU_O_ACC_VIO_FLAGS_CLR       0x2CU   // Access violation clear register
#define CMMPU_O_ACC_VIO_ADDR_REG        0x30U   // Access violation address register
#define CMMPU_O_REGION0_STARTADDRESSS   0x40U   // Region 0 start address register
#define CMMPU_O_REGION0_CONFIG          0x44U   // Region 0 configuration register
#define CMMPU_O_REGION1_STARTADDRESSS   0x48U   // Region 1 start address register
#define CMMPU_O_REGION1_CONFIG          0x4CU   // Region 1 configuration register
#define CMMPU_O_REGION2_STARTADDRESSS   0x50U   // Region 2 start address register
#define CMMPU_O_REGION2_CONFIG          0x54U   // Region 2 configuration register
#define CMMPU_O_REGION3_STARTADDRESSS   0x58U   // Region 3 start address register
#define CMMPU_O_REGION3_CONFIG          0x5CU   // Region 3 configuration register
#define CMMPU_O_REGION4_STARTADDRESSS   0x60U   // Region 4 start address register
#define CMMPU_O_REGION4_CONFIG          0x64U   // Region 4 configuration register
#define CMMPU_O_REGION5_STARTADDRESSS   0x68U   // Region 5 start address register
#define CMMPU_O_REGION5_CONFIG          0x6CU   // Region 5 configuration register
#define CMMPU_O_REGION6_STARTADDRESSS   0x70U   // Region 6 start address register
#define CMMPU_O_REGION6_CONFIG          0x74U   // Region 6 configuration register
#define CMMPU_O_REGION7_STARTADDRESSS   0x78U   // Region 7 start address register
#define CMMPU_O_REGION7_CONFIG          0x7CU   // Region 7 configuration register


//*************************************************************************************************
//
// The following are defines for the bit fields in the MPU_CONTROL_REG register
//
//*************************************************************************************************
#define CMMPU_MPU_CONTROL_REG_ENABLE   0x1U   // Global Enable register

//*************************************************************************************************
//
// The following are defines for the bit fields in the ACC_VIO_INTEN register
//
//*************************************************************************************************
#define CMMPU_ACC_VIO_INTEN_INTEN   0x1U          // Interrupt enable register
#define CMMPU_ACC_VIO_INTEN_KEY_S   16U
#define CMMPU_ACC_VIO_INTEN_KEY_M   0xFFFF0000U   // KEY to allow write access

//*************************************************************************************************
//
// The following are defines for the bit fields in the ACC_VIO_FLAGS register
//
//*************************************************************************************************
#define CMMPU_ACC_VIO_FLAGS_RD   0x1U   // Read access violation flag
#define CMMPU_ACC_VIO_FLAGS_WR   0x2U   // Write access violation flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the ACC_VIO_FLAGS_SET register
//
//*************************************************************************************************
#define CMMPU_ACC_VIO_FLAGS_SET_RD      0x1U          // Read access violation flag set
#define CMMPU_ACC_VIO_FLAGS_SET_WR      0x2U          // Write access violation flag set
#define CMMPU_ACC_VIO_FLAGS_SET_KEY_S   16U
#define CMMPU_ACC_VIO_FLAGS_SET_KEY_M   0xFFFF0000U   // KEY to allow write access

//*************************************************************************************************
//
// The following are defines for the bit fields in the ACC_VIO_FLAGS_CLR register
//
//*************************************************************************************************
#define CMMPU_ACC_VIO_FLAGS_CLR_RD      0x1U          // Read access violation flag clear
#define CMMPU_ACC_VIO_FLAGS_CLR_WR      0x2U          // Write access violation flag clear
#define CMMPU_ACC_VIO_FLAGS_CLR_KEY_S   16U
#define CMMPU_ACC_VIO_FLAGS_CLR_KEY_M   0xFFFF0000U   // KEY to allow write access

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGION0_CONFIG register
//
//*************************************************************************************************
#define CMMPU_REGION0_CONFIG_ENABLE               0x1U        // Region Enable bit
#define CMMPU_REGION0_CONFIG_PROT_TYPE_S          4U
#define CMMPU_REGION0_CONFIG_PROT_TYPE_M          0x30U       // Access permission configuration
                                                              // bits
#define CMMPU_REGION0_CONFIG_SIZE_S               8U
#define CMMPU_REGION0_CONFIG_SIZE_M               0x1F00U     // Size of the region 0
#define CMMPU_REGION0_CONFIG_SUBREGION0_DISABLE   0x10000U    // Sub region 0 disable bit
#define CMMPU_REGION0_CONFIG_SUBREGION1_DISABLE   0x20000U    // Sub region 1 disable bit
#define CMMPU_REGION0_CONFIG_SUBREGION2_DISABLE   0x40000U    // Sub region 2 disable bit
#define CMMPU_REGION0_CONFIG_SUBREGION3_DISABLE   0x80000U    // Sub region 3 disable bit
#define CMMPU_REGION0_CONFIG_SUBREGION4_DISABLE   0x100000U   // Sub region 4 disable bit
#define CMMPU_REGION0_CONFIG_SUBREGION5_DISABLE   0x200000U   // Sub region 5 disable bit
#define CMMPU_REGION0_CONFIG_SUBREGION6_DISABLE   0x400000U   // Sub region 6 disable bit
#define CMMPU_REGION0_CONFIG_SUBREGION7_DISABLE   0x800000U   // Sub region 7 disable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGION1_CONFIG register
//
//*************************************************************************************************
#define CMMPU_REGION1_CONFIG_ENABLE               0x1U        // Region Enable bit
#define CMMPU_REGION1_CONFIG_PROT_TYPE_S          4U
#define CMMPU_REGION1_CONFIG_PROT_TYPE_M          0x30U       // Access permission configuration
                                                              // bits
#define CMMPU_REGION1_CONFIG_SIZE_S               8U
#define CMMPU_REGION1_CONFIG_SIZE_M               0x1F00U     // Size of the region 1
#define CMMPU_REGION1_CONFIG_SUBREGION0_DISABLE   0x10000U    // Sub region 0 disable bit
#define CMMPU_REGION1_CONFIG_SUBREGION1_DISABLE   0x20000U    // Sub region 1 disable bit
#define CMMPU_REGION1_CONFIG_SUBREGION2_DISABLE   0x40000U    // Sub region 2 disable bit
#define CMMPU_REGION1_CONFIG_SUBREGION3_DISABLE   0x80000U    // Sub region 3 disable bit
#define CMMPU_REGION1_CONFIG_SUBREGION4_DISABLE   0x100000U   // Sub region 4 disable bit
#define CMMPU_REGION1_CONFIG_SUBREGION5_DISABLE   0x200000U   // Sub region 5 disable bit
#define CMMPU_REGION1_CONFIG_SUBREGION6_DISABLE   0x400000U   // Sub region 6 disable bit
#define CMMPU_REGION1_CONFIG_SUBREGION7_DISABLE   0x800000U   // Sub region 7 disable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGION2_CONFIG register
//
//*************************************************************************************************
#define CMMPU_REGION2_CONFIG_ENABLE               0x1U        // Region Enable bit
#define CMMPU_REGION2_CONFIG_PROT_TYPE_S          4U
#define CMMPU_REGION2_CONFIG_PROT_TYPE_M          0x30U       // Access permission configuration
                                                              // bits
#define CMMPU_REGION2_CONFIG_SIZE_S               8U
#define CMMPU_REGION2_CONFIG_SIZE_M               0x1F00U     // Size of the region 2
#define CMMPU_REGION2_CONFIG_SUBREGION0_DISABLE   0x10000U    // Sub region 0 disable bit
#define CMMPU_REGION2_CONFIG_SUBREGION1_DISABLE   0x20000U    // Sub region 1 disable bit
#define CMMPU_REGION2_CONFIG_SUBREGION2_DISABLE   0x40000U    // Sub region 2 disable bit
#define CMMPU_REGION2_CONFIG_SUBREGION3_DISABLE   0x80000U    // Sub region 3 disable bit
#define CMMPU_REGION2_CONFIG_SUBREGION4_DISABLE   0x100000U   // Sub region 4 disable bit
#define CMMPU_REGION2_CONFIG_SUBREGION5_DISABLE   0x200000U   // Sub region 5 disable bit
#define CMMPU_REGION2_CONFIG_SUBREGION6_DISABLE   0x400000U   // Sub region 6 disable bit
#define CMMPU_REGION2_CONFIG_SUBREGION7_DISABLE   0x800000U   // Sub region 7 disable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGION3_CONFIG register
//
//*************************************************************************************************
#define CMMPU_REGION3_CONFIG_ENABLE               0x1U        // Region Enable bit
#define CMMPU_REGION3_CONFIG_PROT_TYPE_S          4U
#define CMMPU_REGION3_CONFIG_PROT_TYPE_M          0x30U       // Access permission configuration
                                                              // bits
#define CMMPU_REGION3_CONFIG_SIZE_S               8U
#define CMMPU_REGION3_CONFIG_SIZE_M               0x1F00U     // Size of the region 3
#define CMMPU_REGION3_CONFIG_SUBREGION0_DISABLE   0x10000U    // Sub region 0 disable bit
#define CMMPU_REGION3_CONFIG_SUBREGION1_DISABLE   0x20000U    // Sub region 1 disable bit
#define CMMPU_REGION3_CONFIG_SUBREGION2_DISABLE   0x40000U    // Sub region 2 disable bit
#define CMMPU_REGION3_CONFIG_SUBREGION3_DISABLE   0x80000U    // Sub region 3 disable bit
#define CMMPU_REGION3_CONFIG_SUBREGION4_DISABLE   0x100000U   // Sub region 4 disable bit
#define CMMPU_REGION3_CONFIG_SUBREGION5_DISABLE   0x200000U   // Sub region 5 disable bit
#define CMMPU_REGION3_CONFIG_SUBREGION6_DISABLE   0x400000U   // Sub region 6 disable bit
#define CMMPU_REGION3_CONFIG_SUBREGION7_DISABLE   0x800000U   // Sub region 7 disable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGION4_CONFIG register
//
//*************************************************************************************************
#define CMMPU_REGION4_CONFIG_ENABLE               0x1U        // Region Enable bit
#define CMMPU_REGION4_CONFIG_PROT_TYPE_S          4U
#define CMMPU_REGION4_CONFIG_PROT_TYPE_M          0x30U       // Access permission configuration
                                                              // bits
#define CMMPU_REGION4_CONFIG_SIZE_S               8U
#define CMMPU_REGION4_CONFIG_SIZE_M               0x1F00U     // Size of the region 4
#define CMMPU_REGION4_CONFIG_SUBREGION0_DISABLE   0x10000U    // Sub region 0 disable bit
#define CMMPU_REGION4_CONFIG_SUBREGION1_DISABLE   0x20000U    // Sub region 1 disable bit
#define CMMPU_REGION4_CONFIG_SUBREGION2_DISABLE   0x40000U    // Sub region 2 disable bit
#define CMMPU_REGION4_CONFIG_SUBREGION3_DISABLE   0x80000U    // Sub region 3 disable bit
#define CMMPU_REGION4_CONFIG_SUBREGION4_DISABLE   0x100000U   // Sub region 4 disable bit
#define CMMPU_REGION4_CONFIG_SUBREGION5_DISABLE   0x200000U   // Sub region 5 disable bit
#define CMMPU_REGION4_CONFIG_SUBREGION6_DISABLE   0x400000U   // Sub region 6 disable bit
#define CMMPU_REGION4_CONFIG_SUBREGION7_DISABLE   0x800000U   // Sub region 7 disable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGION5_CONFIG register
//
//*************************************************************************************************
#define CMMPU_REGION5_CONFIG_ENABLE               0x1U        // Region Enable bit
#define CMMPU_REGION5_CONFIG_PROT_TYPE_S          4U
#define CMMPU_REGION5_CONFIG_PROT_TYPE_M          0x30U       // Access permission configuration
                                                              // bits
#define CMMPU_REGION5_CONFIG_SIZE_S               8U
#define CMMPU_REGION5_CONFIG_SIZE_M               0x1F00U     // Size of the region 5
#define CMMPU_REGION5_CONFIG_SUBREGION0_DISABLE   0x10000U    // Sub region 0 disable bit
#define CMMPU_REGION5_CONFIG_SUBREGION1_DISABLE   0x20000U    // Sub region 1 disable bit
#define CMMPU_REGION5_CONFIG_SUBREGION2_DISABLE   0x40000U    // Sub region 2 disable bit
#define CMMPU_REGION5_CONFIG_SUBREGION3_DISABLE   0x80000U    // Sub region 3 disable bit
#define CMMPU_REGION5_CONFIG_SUBREGION4_DISABLE   0x100000U   // Sub region 4 disable bit
#define CMMPU_REGION5_CONFIG_SUBREGION5_DISABLE   0x200000U   // Sub region 5 disable bit
#define CMMPU_REGION5_CONFIG_SUBREGION6_DISABLE   0x400000U   // Sub region 6 disable bit
#define CMMPU_REGION5_CONFIG_SUBREGION7_DISABLE   0x800000U   // Sub region 7 disable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGION6_CONFIG register
//
//*************************************************************************************************
#define CMMPU_REGION6_CONFIG_ENABLE               0x1U        // Region Enable bit
#define CMMPU_REGION6_CONFIG_PROT_TYPE_S          4U
#define CMMPU_REGION6_CONFIG_PROT_TYPE_M          0x30U       // Access permission configuration
                                                              // bits
#define CMMPU_REGION6_CONFIG_SIZE_S               8U
#define CMMPU_REGION6_CONFIG_SIZE_M               0x1F00U     // Size of the region 6
#define CMMPU_REGION6_CONFIG_SUBREGION0_DISABLE   0x10000U    // Sub region 0 disable bit
#define CMMPU_REGION6_CONFIG_SUBREGION1_DISABLE   0x20000U    // Sub region 1 disable bit
#define CMMPU_REGION6_CONFIG_SUBREGION2_DISABLE   0x40000U    // Sub region 2 disable bit
#define CMMPU_REGION6_CONFIG_SUBREGION3_DISABLE   0x80000U    // Sub region 3 disable bit
#define CMMPU_REGION6_CONFIG_SUBREGION4_DISABLE   0x100000U   // Sub region 4 disable bit
#define CMMPU_REGION6_CONFIG_SUBREGION5_DISABLE   0x200000U   // Sub region 5 disable bit
#define CMMPU_REGION6_CONFIG_SUBREGION6_DISABLE   0x400000U   // Sub region 6 disable bit
#define CMMPU_REGION6_CONFIG_SUBREGION7_DISABLE   0x800000U   // Sub region 7 disable bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the REGION7_CONFIG register
//
//*************************************************************************************************
#define CMMPU_REGION7_CONFIG_ENABLE               0x1U        // Region Enable bit
#define CMMPU_REGION7_CONFIG_PROT_TYPE_S          4U
#define CMMPU_REGION7_CONFIG_PROT_TYPE_M          0x30U       // Access permission configuration
                                                              // bits
#define CMMPU_REGION7_CONFIG_SIZE_S               8U
#define CMMPU_REGION7_CONFIG_SIZE_M               0x1F00U     // Size of the region 7
#define CMMPU_REGION7_CONFIG_SUBREGION0_DISABLE   0x10000U    // Sub region 0 disable bit
#define CMMPU_REGION7_CONFIG_SUBREGION1_DISABLE   0x20000U    // Sub region 1 disable bit
#define CMMPU_REGION7_CONFIG_SUBREGION2_DISABLE   0x40000U    // Sub region 2 disable bit
#define CMMPU_REGION7_CONFIG_SUBREGION3_DISABLE   0x80000U    // Sub region 3 disable bit
#define CMMPU_REGION7_CONFIG_SUBREGION4_DISABLE   0x100000U   // Sub region 4 disable bit
#define CMMPU_REGION7_CONFIG_SUBREGION5_DISABLE   0x200000U   // Sub region 5 disable bit
#define CMMPU_REGION7_CONFIG_SUBREGION6_DISABLE   0x400000U   // Sub region 6 disable bit
#define CMMPU_REGION7_CONFIG_SUBREGION7_DISABLE   0x800000U   // Sub region 7 disable bit



#endif
