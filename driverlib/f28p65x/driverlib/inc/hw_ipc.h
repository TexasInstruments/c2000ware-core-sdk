//###########################################################################
//
// FILE:    hw_ipc.h
//
// TITLE:   Definitions for the IPC registers.
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

#ifndef HW_IPC_H
#define HW_IPC_H

//*************************************************************************************************
//
// The following are defines for the IPC register offsets
//
//*************************************************************************************************
#define IPC_O_CPU1TOCPU2IPCACK        0x0U    // CPU1TOCPU2IPCACK Register
#define IPC_O_CPU2TOCPU1IPCSTS        0x2U    // CPU2TOCPU1IPCSTS Register
#define IPC_O_CPU1TOCPU2IPCSET        0x4U    // CPU1TOCPU2IPCSET Register
#define IPC_O_CPU1TOCPU2IPCCLR        0x6U    // CPU1TOCPU2IPCCLR Register
#define IPC_O_CPU1TOCPU2IPCFLG        0x8U    // CPU1TOCPU2IPCFLG Register
#define IPC_O_COUNTERL                0xCU    // IPCCOUNTERL Register
#define IPC_O_COUNTERH                0xEU    // IPCCOUNTERH Register
#define IPC_O_CPU1TOCPU2IPCSENDCOM    0x10U   // CPU1TOCPU2IPCSENDCOM Register
#define IPC_O_CPU1TOCPU2IPCSENDADDR   0x12U   // CPU1TOCPU2IPCSENDADDR Register
#define IPC_O_CPU1TOCPU2IPCSENDDATA   0x14U   // CPU1TOCPU2IPCSENDDATA Register
#define IPC_O_CPU2TOCPU1IPCREPLY      0x16U   // CPU2TOCPU1IPCREPLY Register
#define IPC_O_CPU2TOCPU1IPCRECVCOM    0x18U   // CPU2TOCPU1IPCRECVCOM Register
#define IPC_O_CPU2TOCPU1IPCRECVADDR   0x1AU   // CPU2TOCPU1IPCRECVADDR Register
#define IPC_O_CPU2TOCPU1IPCRECVDATA   0x1CU   // CPU2TOCPU1IPCRECVDATA Register
#define IPC_O_CPU1TOCPU2IPCREPLY      0x1EU   // CPU1TOCPU2IPCREPLY Register
#define IPC_O_CPU2TOCPU1IPCBOOTSTS    0x20U   // CPU2TOCPU1IPCBOOTSTS Register
#define IPC_O_CPU1TOCPU2IPCBOOTMODE   0x22U   // CPU1TOCPU2IPCBOOTMODE Register
#define IPC_O_FLASHCTLSEM             0x24U   // FLASHCTLSEM Register

#define IPC_O_CPU2TOCPU1IPCACK        0x0U    // CPU2TOCPU1IPCACK Register
#define IPC_O_CPU1TOCPU2IPCSTS        0x2U    // CPU1TOCPU2IPCSTS Register
#define IPC_O_CPU2TOCPU1IPCSET        0x4U    // CPU2TOCPU1IPCSET Register
#define IPC_O_CPU2TOCPU1IPCCLR        0x6U    // CPU2TOCPU1IPCCLR Register
#define IPC_O_CPU2TOCPU1IPCFLG        0x8U    // CPU2TOCPU1IPCFLG Register
#define IPC_O_COUNTERL                0xCU    // IPCCOUNTERL Register
#define IPC_O_COUNTERH                0xEU    // IPCCOUNTERH Register
#define IPC_O_CPU1TOCPU2IPCRECVCOM    0x10U   // CPU1TOCPU2IPCRECVCOM Register
#define IPC_O_CPU1TOCPU2IPCRECVADDR   0x12U   // CPU1TOCPU2IPCRECVADDR Register
#define IPC_O_CPU1TOCPU2IPCRECVDATA   0x14U   // CPU1TOCPU2IPCRECVDATA Register
#define IPC_O_CPU2TOCPU1IPCREPLY      0x16U   // CPU2TOCPU1IPCREPLY Register
#define IPC_O_CPU2TOCPU1IPCSENDCOM    0x18U   // CPU2TOCPU1IPCSENDCOM Register
#define IPC_O_CPU2TOCPU1IPCSENDADDR   0x1AU   // CPU2TOCPU1IPCSENDADDR Register
#define IPC_O_CPU2TOCPU1IPCSENDDATA   0x1CU   // CPU2TOCPU1IPCSENDDATA Register
#define IPC_O_CPU1TOCPU2IPCREPLY      0x1EU   // CPU1TOCPU2IPCREPLY Register
#define IPC_O_CPU2TOCPU1IPCBOOTSTS    0x20U   // CPU2TOCPU1IPCBOOTSTS Register
#define IPC_O_CPU1TOCPU2IPCBOOTMODE   0x22U   // CPU1TOCPU2IPCBOOTMODE Register
#define IPC_O_FLASHCTLSEM             0x24U   // FLASHCTLSEM Register


//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU1TOCPU2IPCACK register
//
//*************************************************************************************************
#define IPC_CPU1TOCPU2IPCACK_IPC0    0x1U          // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC0 bit
#define IPC_CPU1TOCPU2IPCACK_IPC1    0x2U          // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC1 bit
#define IPC_CPU1TOCPU2IPCACK_IPC2    0x4U          // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC2 bit
#define IPC_CPU1TOCPU2IPCACK_IPC3    0x8U          // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC3 bit
#define IPC_CPU1TOCPU2IPCACK_IPC4    0x10U         // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC4 bit
#define IPC_CPU1TOCPU2IPCACK_IPC5    0x20U         // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC5 bit
#define IPC_CPU1TOCPU2IPCACK_IPC6    0x40U         // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC6 bit
#define IPC_CPU1TOCPU2IPCACK_IPC7    0x80U         // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC7 bit
#define IPC_CPU1TOCPU2IPCACK_IPC8    0x100U        // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC8 bit
#define IPC_CPU1TOCPU2IPCACK_IPC9    0x200U        // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC9 bit
#define IPC_CPU1TOCPU2IPCACK_IPC10   0x400U        // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC10 bit
#define IPC_CPU1TOCPU2IPCACK_IPC11   0x800U        // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC11 bit
#define IPC_CPU1TOCPU2IPCACK_IPC12   0x1000U       // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC12 bit
#define IPC_CPU1TOCPU2IPCACK_IPC13   0x2000U       // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC13 bit
#define IPC_CPU1TOCPU2IPCACK_IPC14   0x4000U       // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC14 bit
#define IPC_CPU1TOCPU2IPCACK_IPC15   0x8000U       // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC15 bit
#define IPC_CPU1TOCPU2IPCACK_IPC16   0x10000U      // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC16 bit
#define IPC_CPU1TOCPU2IPCACK_IPC17   0x20000U      // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC17 bit
#define IPC_CPU1TOCPU2IPCACK_IPC18   0x40000U      // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC18 bit
#define IPC_CPU1TOCPU2IPCACK_IPC19   0x80000U      // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC19 bit
#define IPC_CPU1TOCPU2IPCACK_IPC20   0x100000U     // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC20 bit
#define IPC_CPU1TOCPU2IPCACK_IPC21   0x200000U     // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC21 bit
#define IPC_CPU1TOCPU2IPCACK_IPC22   0x400000U     // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC22 bit
#define IPC_CPU1TOCPU2IPCACK_IPC23   0x800000U     // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC23 bit
#define IPC_CPU1TOCPU2IPCACK_IPC24   0x1000000U    // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC24 bit
#define IPC_CPU1TOCPU2IPCACK_IPC25   0x2000000U    // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC25 bit
#define IPC_CPU1TOCPU2IPCACK_IPC26   0x4000000U    // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC26 bit
#define IPC_CPU1TOCPU2IPCACK_IPC27   0x8000000U    // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC27 bit
#define IPC_CPU1TOCPU2IPCACK_IPC28   0x10000000U   // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC28 bit
#define IPC_CPU1TOCPU2IPCACK_IPC29   0x20000000U   // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC29 bit
#define IPC_CPU1TOCPU2IPCACK_IPC30   0x40000000U   // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC30 bit
#define IPC_CPU1TOCPU2IPCACK_IPC31   0x80000000U   // Acknowledgement from CPU1 to
                                                   // CPU2TOCPU1IPCFLG.IPC31 bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU2TOCPU1IPCSTS register
//
//*************************************************************************************************
#define IPC_CPU2TOCPU1IPCSTS_IPC0    0x1U          // IPC0 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC1    0x2U          // IPC1 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC2    0x4U          // IPC2 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC3    0x8U          // IPC3 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC4    0x10U         // IPC4 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC5    0x20U         // IPC5 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC6    0x40U         // IPC6 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC7    0x80U         // IPC7 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC8    0x100U        // IPC8 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC9    0x200U        // IPC9 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC10   0x400U        // IPC10 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC11   0x800U        // IPC11 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC12   0x1000U       // IPC12 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC13   0x2000U       // IPC13 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC14   0x4000U       // IPC14 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC15   0x8000U       // IPC15 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC16   0x10000U      // IPC16 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC17   0x20000U      // IPC17 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC18   0x40000U      // IPC18 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC19   0x80000U      // IPC19 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC20   0x100000U     // IPC20 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC21   0x200000U     // IPC21 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC22   0x400000U     // IPC22 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC23   0x800000U     // IPC23 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC24   0x1000000U    // IPC24 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC25   0x2000000U    // IPC25 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC26   0x4000000U    // IPC26 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC27   0x8000000U    // IPC27 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC28   0x10000000U   // IPC28 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC29   0x20000000U   // IPC29 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC30   0x40000000U   // IPC30 Request from  CPU2 to CPU1
#define IPC_CPU2TOCPU1IPCSTS_IPC31   0x80000000U   // IPC31 Request from  CPU2 to CPU1

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU1TOCPU2IPCSET register
//
//*************************************************************************************************
#define IPC_CPU1TOCPU2IPCSET_IPC0    0x1U          // Set CPU1TOCPU2IPCFLG.IPC0 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC1    0x2U          // Set CPU1TOCPU2IPCFLG.IPC1 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC2    0x4U          // Set CPU1TOCPU2IPCFLG.IPC2 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC3    0x8U          // Set CPU1TOCPU2IPCFLG.IPC3 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC4    0x10U         // Set CPU1TOCPU2IPCFLG.IPC4 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC5    0x20U         // Set CPU1TOCPU2IPCFLG.IPC5 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC6    0x40U         // Set CPU1TOCPU2IPCFLG.IPC6 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC7    0x80U         // Set CPU1TOCPU2IPCFLG.IPC7 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC8    0x100U        // Set CPU1TOCPU2IPCFLG.IPC8 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC9    0x200U        // Set CPU1TOCPU2IPCFLG.IPC9 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC10   0x400U        // Set CPU1TOCPU2IPCFLG.IPC10 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC11   0x800U        // Set CPU1TOCPU2IPCFLG.IPC11 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC12   0x1000U       // Set CPU1TOCPU2IPCFLG.IPC12 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC13   0x2000U       // Set CPU1TOCPU2IPCFLG.IPC13 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC14   0x4000U       // Set CPU1TOCPU2IPCFLG.IPC14 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC15   0x8000U       // Set CPU1TOCPU2IPCFLG.IPC15 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC16   0x10000U      // Set CPU1TOCPU2IPCFLG.IPC16 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC17   0x20000U      // Set CPU1TOCPU2IPCFLG.IPC17 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC18   0x40000U      // Set CPU1TOCPU2IPCFLG.IPC18 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC19   0x80000U      // Set CPU1TOCPU2IPCFLG.IPC19 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC20   0x100000U     // Set CPU1TOCPU2IPCFLG.IPC20 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC21   0x200000U     // Set CPU1TOCPU2IPCFLG.IPC21 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC22   0x400000U     // Set CPU1TOCPU2IPCFLG.IPC22 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC23   0x800000U     // Set CPU1TOCPU2IPCFLG.IPC23 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC24   0x1000000U    // Set CPU1TOCPU2IPCFLG.IPC24 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC25   0x2000000U    // Set CPU1TOCPU2IPCFLG.IPC25 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC26   0x4000000U    // Set CPU1TOCPU2IPCFLG.IPC26 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC27   0x8000000U    // Set CPU1TOCPU2IPCFLG.IPC27 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC28   0x10000000U   // Set CPU1TOCPU2IPCFLG.IPC28 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC29   0x20000000U   // Set CPU1TOCPU2IPCFLG.IPC29 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC30   0x40000000U   // Set CPU1TOCPU2IPCFLG.IPC30 Flag
#define IPC_CPU1TOCPU2IPCSET_IPC31   0x80000000U   // Set CPU1TOCPU2IPCFLG.IPC31 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU1TOCPU2IPCCLR register
//
//*************************************************************************************************
#define IPC_CPU1TOCPU2IPCCLR_IPC0    0x1U          // Clear CPU1TOCPU2IPCFLG.IPC0 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC1    0x2U          // Clear CPU1TOCPU2IPCFLG.IPC1 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC2    0x4U          // Clear CPU1TOCPU2IPCFLG.IPC2 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC3    0x8U          // Clear CPU1TOCPU2IPCFLG.IPC3 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC4    0x10U         // Clear CPU1TOCPU2IPCFLG.IPC4 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC5    0x20U         // Clear CPU1TOCPU2IPCFLG.IPC5 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC6    0x40U         // Clear CPU1TOCPU2IPCFLG.IPC6 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC7    0x80U         // Clear CPU1TOCPU2IPCFLG.IPC7 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC8    0x100U        // Clear CPU1TOCPU2IPCFLG.IPC8 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC9    0x200U        // Clear CPU1TOCPU2IPCFLG.IPC9 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC10   0x400U        // Clear CPU1TOCPU2IPCFLG.IPC10 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC11   0x800U        // Clear CPU1TOCPU2IPCFLG.IPC11 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC12   0x1000U       // Clear CPU1TOCPU2IPCFLG.IPC12 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC13   0x2000U       // Clear CPU1TOCPU2IPCFLG.IPC13 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC14   0x4000U       // Clear CPU1TOCPU2IPCFLG.IPC14 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC15   0x8000U       // Clear CPU1TOCPU2IPCFLG.IPC15 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC16   0x10000U      // Clear CPU1TOCPU2IPCFLG.IPC16 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC17   0x20000U      // Clear CPU1TOCPU2IPCFLG.IPC17 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC18   0x40000U      // Clear CPU1TOCPU2IPCFLG.IPC18 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC19   0x80000U      // Clear CPU1TOCPU2IPCFLG.IPC19 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC20   0x100000U     // Clear CPU1TOCPU2IPCFLG.IPC20 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC21   0x200000U     // Clear CPU1TOCPU2IPCFLG.IPC21 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC22   0x400000U     // Clear CPU1TOCPU2IPCFLG.IPC22 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC23   0x800000U     // Clear CPU1TOCPU2IPCFLG.IPC23 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC24   0x1000000U    // Clear CPU1TOCPU2IPCFLG.IPC24 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC25   0x2000000U    // Clear CPU1TOCPU2IPCFLG.IPC25 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC26   0x4000000U    // Clear CPU1TOCPU2IPCFLG.IPC26 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC27   0x8000000U    // Clear CPU1TOCPU2IPCFLG.IPC27 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC28   0x10000000U   // Clear CPU1TOCPU2IPCFLG.IPC28 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC29   0x20000000U   // Clear CPU1TOCPU2IPCFLG.IPC29 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC30   0x40000000U   // Clear CPU1TOCPU2IPCFLG.IPC30 Flag
#define IPC_CPU1TOCPU2IPCCLR_IPC31   0x80000000U   // Clear CPU1TOCPU2IPCFLG.IPC31 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU1TOCPU2IPCFLG register
//
//*************************************************************************************************
#define IPC_CPU1TOCPU2IPCFLG_IPC0    0x1U          // CPU1 to CPU2 IPC0 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC1    0x2U          // CPU1 to CPU2 IPC1 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC2    0x4U          // CPU1 to CPU2 IPC2 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC3    0x8U          // CPU1 to CPU2 IPC3 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC4    0x10U         // CPU1 to CPU2 IPC4 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC5    0x20U         // CPU1 to CPU2 IPC5 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC6    0x40U         // CPU1 to CPU2 IPC6 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC7    0x80U         // CPU1 to CPU2 IPC7 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC8    0x100U        // CPU1 to CPU2 IPC8 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC9    0x200U        // CPU1 to CPU2 IPC9 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC10   0x400U        // CPU1 to CPU2 IPC10 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC11   0x800U        // CPU1 to CPU2 IPC11 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC12   0x1000U       // CPU1 to CPU2 IPC12 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC13   0x2000U       // CPU1 to CPU2 IPC13 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC14   0x4000U       // CPU1 to CPU2 IPC14 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC15   0x8000U       // CPU1 to CPU2 IPC15 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC16   0x10000U      // CPU1 to CPU2 IPC16 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC17   0x20000U      // CPU1 to CPU2 IPC17 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC18   0x40000U      // CPU1 to CPU2 IPC18 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC19   0x80000U      // CPU1 to CPU2 IPC19 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC20   0x100000U     // CPU1 to CPU2 IPC20 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC21   0x200000U     // CPU1 to CPU2 IPC21 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC22   0x400000U     // CPU1 to CPU2 IPC22 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC23   0x800000U     // CPU1 to CPU2 IPC23 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC24   0x1000000U    // CPU1 to CPU2 IPC24 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC25   0x2000000U    // CPU1 to CPU2 IPC25 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC26   0x4000000U    // CPU1 to CPU2 IPC26 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC27   0x8000000U    // CPU1 to CPU2 IPC27 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC28   0x10000000U   // CPU1 to CPU2 IPC28 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC29   0x20000000U   // CPU1 to CPU2 IPC29 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC30   0x40000000U   // CPU1 to CPU2 IPC30 Flag Status
#define IPC_CPU1TOCPU2IPCFLG_IPC31   0x80000000U   // CPU1 to CPU2 IPC31 Flag Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the FLASHCTLSEM register
//
//*************************************************************************************************
#define IPC_FLASHCTLSEM_SEM_S   0U
#define IPC_FLASHCTLSEM_SEM_M   0x3U          // Flash Controller Access Semaphore between CPU1 and
                                              // CPU2
#define IPC_FLASHCTLSEM_KEY_S   16U
#define IPC_FLASHCTLSEM_KEY_M   0xFFFF0000U   // Key Qualifier for writes to this register


//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU2TOCPU1IPCACK register
//
//*************************************************************************************************
#define IPC_CPU2TOCPU1IPCACK_IPC0    0x1U          // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC0 bit
#define IPC_CPU2TOCPU1IPCACK_IPC1    0x2U          // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC1 bit
#define IPC_CPU2TOCPU1IPCACK_IPC2    0x4U          // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC2 bit
#define IPC_CPU2TOCPU1IPCACK_IPC3    0x8U          // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC3 bit
#define IPC_CPU2TOCPU1IPCACK_IPC4    0x10U         // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC4 bit
#define IPC_CPU2TOCPU1IPCACK_IPC5    0x20U         // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC5 bit
#define IPC_CPU2TOCPU1IPCACK_IPC6    0x40U         // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC6 bit
#define IPC_CPU2TOCPU1IPCACK_IPC7    0x80U         // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC7 bit
#define IPC_CPU2TOCPU1IPCACK_IPC8    0x100U        // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC8 bit
#define IPC_CPU2TOCPU1IPCACK_IPC9    0x200U        // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC9 bit
#define IPC_CPU2TOCPU1IPCACK_IPC10   0x400U        // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC10 bit
#define IPC_CPU2TOCPU1IPCACK_IPC11   0x800U        // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC11 bit
#define IPC_CPU2TOCPU1IPCACK_IPC12   0x1000U       // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC12 bit
#define IPC_CPU2TOCPU1IPCACK_IPC13   0x2000U       // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC13 bit
#define IPC_CPU2TOCPU1IPCACK_IPC14   0x4000U       // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC14 bit
#define IPC_CPU2TOCPU1IPCACK_IPC15   0x8000U       // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC15 bit
#define IPC_CPU2TOCPU1IPCACK_IPC16   0x10000U      // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC16 bit
#define IPC_CPU2TOCPU1IPCACK_IPC17   0x20000U      // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC17 bit
#define IPC_CPU2TOCPU1IPCACK_IPC18   0x40000U      // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC18 bit
#define IPC_CPU2TOCPU1IPCACK_IPC19   0x80000U      // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC19 bit
#define IPC_CPU2TOCPU1IPCACK_IPC20   0x100000U     // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC20 bit
#define IPC_CPU2TOCPU1IPCACK_IPC21   0x200000U     // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC21 bit
#define IPC_CPU2TOCPU1IPCACK_IPC22   0x400000U     // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC22 bit
#define IPC_CPU2TOCPU1IPCACK_IPC23   0x800000U     // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC23 bit
#define IPC_CPU2TOCPU1IPCACK_IPC24   0x1000000U    // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC24 bit
#define IPC_CPU2TOCPU1IPCACK_IPC25   0x2000000U    // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC25 bit
#define IPC_CPU2TOCPU1IPCACK_IPC26   0x4000000U    // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC26 bit
#define IPC_CPU2TOCPU1IPCACK_IPC27   0x8000000U    // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC27 bit
#define IPC_CPU2TOCPU1IPCACK_IPC28   0x10000000U   // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC28 bit
#define IPC_CPU2TOCPU1IPCACK_IPC29   0x20000000U   // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC29 bit
#define IPC_CPU2TOCPU1IPCACK_IPC30   0x40000000U   // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC30 bit
#define IPC_CPU2TOCPU1IPCACK_IPC31   0x80000000U   // Acknowledgement from CPU2 to
                                                   // CPU1TOCPU2IPCFLG.IPC31 bit

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU1TOCPU2IPCSTS register
//
//*************************************************************************************************
#define IPC_CPU1TOCPU2IPCSTS_IPC0    0x1U          // IPC0 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC1    0x2U          // IPC1 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC2    0x4U          // IPC2 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC3    0x8U          // IPC3 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC4    0x10U         // IPC4 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC5    0x20U         // IPC5 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC6    0x40U         // IPC6 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC7    0x80U         // IPC7 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC8    0x100U        // IPC8 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC9    0x200U        // IPC9 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC10   0x400U        // IPC10 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC11   0x800U        // IPC11 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC12   0x1000U       // IPC12 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC13   0x2000U       // IPC13 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC14   0x4000U       // IPC14 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC15   0x8000U       // IPC15 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC16   0x10000U      // IPC16 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC17   0x20000U      // IPC17 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC18   0x40000U      // IPC18 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC19   0x80000U      // IPC19 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC20   0x100000U     // IPC20 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC21   0x200000U     // IPC21 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC22   0x400000U     // IPC22 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC23   0x800000U     // IPC23 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC24   0x1000000U    // IPC24 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC25   0x2000000U    // IPC25 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC26   0x4000000U    // IPC26 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC27   0x8000000U    // IPC27 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC28   0x10000000U   // IPC28 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC29   0x20000000U   // IPC29 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC30   0x40000000U   // IPC30 Request from  CPU1 to CPU2
#define IPC_CPU1TOCPU2IPCSTS_IPC31   0x80000000U   // IPC31 Request from  CPU1 to CPU2

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU2TOCPU1IPCSET register
//
//*************************************************************************************************
#define IPC_CPU2TOCPU1IPCSET_IPC0    0x1U          // Set CPU2TOCPU1IPCFLG.IPC0 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC1    0x2U          // Set CPU2TOCPU1IPCFLG.IPC1 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC2    0x4U          // Set CPU2TOCPU1IPCFLG.IPC2 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC3    0x8U          // Set CPU2TOCPU1IPCFLG.IPC3 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC4    0x10U         // Set CPU2TOCPU1IPCFLG.IPC4 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC5    0x20U         // Set CPU2TOCPU1IPCFLG.IPC5 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC6    0x40U         // Set CPU2TOCPU1IPCFLG.IPC6 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC7    0x80U         // Set CPU2TOCPU1IPCFLG.IPC7 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC8    0x100U        // Set CPU2TOCPU1IPCFLG.IPC8 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC9    0x200U        // Set CPU2TOCPU1IPCFLG.IPC9 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC10   0x400U        // Set CPU2TOCPU1IPCFLG.IPC10 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC11   0x800U        // Set CPU2TOCPU1IPCFLG.IPC11 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC12   0x1000U       // Set CPU2TOCPU1IPCFLG.IPC12 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC13   0x2000U       // Set CPU2TOCPU1IPCFLG.IPC13 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC14   0x4000U       // Set CPU2TOCPU1IPCFLG.IPC14 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC15   0x8000U       // Set CPU2TOCPU1IPCFLG.IPC15 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC16   0x10000U      // Set CPU2TOCPU1IPCFLG.IPC16 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC17   0x20000U      // Set CPU2TOCPU1IPCFLG.IPC17 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC18   0x40000U      // Set CPU2TOCPU1IPCFLG.IPC18 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC19   0x80000U      // Set CPU2TOCPU1IPCFLG.IPC19 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC20   0x100000U     // Set CPU2TOCPU1IPCFLG.IPC20 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC21   0x200000U     // Set CPU2TOCPU1IPCFLG.IPC21 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC22   0x400000U     // Set CPU2TOCPU1IPCFLG.IPC22 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC23   0x800000U     // Set CPU2TOCPU1IPCFLG.IPC23 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC24   0x1000000U    // Set CPU2TOCPU1IPCFLG.IPC24 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC25   0x2000000U    // Set CPU2TOCPU1IPCFLG.IPC25 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC26   0x4000000U    // Set CPU2TOCPU1IPCFLG.IPC26 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC27   0x8000000U    // Set CPU2TOCPU1IPCFLG.IPC27 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC28   0x10000000U   // Set CPU2TOCPU1IPCFLG.IPC28 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC29   0x20000000U   // Set CPU2TOCPU1IPCFLG.IPC29 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC30   0x40000000U   // Set CPU2TOCPU1IPCFLG.IPC30 Flag
#define IPC_CPU2TOCPU1IPCSET_IPC31   0x80000000U   // Set CPU2TOCPU1IPCFLG.IPC31 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU2TOCPU1IPCCLR register
//
//*************************************************************************************************
#define IPC_CPU2TOCPU1IPCCLR_IPC0    0x1U          // Clear CPU2TOCPU1IPCFLG.IPC0 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC1    0x2U          // Clear CPU2TOCPU1IPCFLG.IPC1 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC2    0x4U          // Clear CPU2TOCPU1IPCFLG.IPC2 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC3    0x8U          // Clear CPU2TOCPU1IPCFLG.IPC3 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC4    0x10U         // Clear CPU2TOCPU1IPCFLG.IPC4 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC5    0x20U         // Clear CPU2TOCPU1IPCFLG.IPC5 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC6    0x40U         // Clear CPU2TOCPU1IPCFLG.IPC6 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC7    0x80U         // Clear CPU2TOCPU1IPCFLG.IPC7 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC8    0x100U        // Clear CPU2TOCPU1IPCFLG.IPC8 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC9    0x200U        // Clear CPU2TOCPU1IPCFLG.IPC9 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC10   0x400U        // Clear CPU2TOCPU1IPCFLG.IPC10 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC11   0x800U        // Clear CPU2TOCPU1IPCFLG.IPC11 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC12   0x1000U       // Clear CPU2TOCPU1IPCFLG.IPC12 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC13   0x2000U       // Clear CPU2TOCPU1IPCFLG.IPC13 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC14   0x4000U       // Clear CPU2TOCPU1IPCFLG.IPC14 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC15   0x8000U       // Clear CPU2TOCPU1IPCFLG.IPC15 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC16   0x10000U      // Clear CPU2TOCPU1IPCFLG.IPC16 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC17   0x20000U      // Clear CPU2TOCPU1IPCFLG.IPC17 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC18   0x40000U      // Clear CPU2TOCPU1IPCFLG.IPC18 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC19   0x80000U      // Clear CPU2TOCPU1IPCFLG.IPC19 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC20   0x100000U     // Clear CPU2TOCPU1IPCFLG.IPC20 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC21   0x200000U     // Clear CPU2TOCPU1IPCFLG.IPC21 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC22   0x400000U     // Clear CPU2TOCPU1IPCFLG.IPC22 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC23   0x800000U     // Clear CPU2TOCPU1IPCFLG.IPC23 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC24   0x1000000U    // Clear CPU2TOCPU1IPCFLG.IPC24 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC25   0x2000000U    // Clear CPU2TOCPU1IPCFLG.IPC25 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC26   0x4000000U    // Clear CPU2TOCPU1IPCFLG.IPC26 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC27   0x8000000U    // Clear CPU2TOCPU1IPCFLG.IPC27 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC28   0x10000000U   // Clear CPU2TOCPU1IPCFLG.IPC28 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC29   0x20000000U   // Clear CPU2TOCPU1IPCFLG.IPC29 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC30   0x40000000U   // Clear CPU2TOCPU1IPCFLG.IPC30 Flag
#define IPC_CPU2TOCPU1IPCCLR_IPC31   0x80000000U   // Clear CPU2TOCPU1IPCFLG.IPC31 Flag

//*************************************************************************************************
//
// The following are defines for the bit fields in the CPU2TOCPU1IPCFLG register
//
//*************************************************************************************************
#define IPC_CPU2TOCPU1IPCFLG_IPC0    0x1U          // CPU2 to CPU1 IPC0 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC1    0x2U          // CPU2 to CPU1 IPC1 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC2    0x4U          // CPU2 to CPU1 IPC2 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC3    0x8U          // CPU2 to CPU1 IPC3 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC4    0x10U         // CPU2 to CPU1 IPC4 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC5    0x20U         // CPU2 to CPU1 IPC5 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC6    0x40U         // CPU2 to CPU1 IPC6 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC7    0x80U         // CPU2 to CPU1 IPC7 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC8    0x100U        // CPU2 to CPU1 IPC8 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC9    0x200U        // CPU2 to CPU1 IPC9 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC10   0x400U        // CPU2 to CPU1 IPC10 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC11   0x800U        // CPU2 to CPU1 IPC11 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC12   0x1000U       // CPU2 to CPU1 IPC12 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC13   0x2000U       // CPU2 to CPU1 IPC13 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC14   0x4000U       // CPU2 to CPU1 IPC14 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC15   0x8000U       // CPU2 to CPU1 IPC15 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC16   0x10000U      // CPU2 to CPU1 IPC16 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC17   0x20000U      // CPU2 to CPU1 IPC17 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC18   0x40000U      // CPU2 to CPU1 IPC18 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC19   0x80000U      // CPU2 to CPU1 IPC19 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC20   0x100000U     // CPU2 to CPU1 IPC20 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC21   0x200000U     // CPU2 to CPU1 IPC21 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC22   0x400000U     // CPU2 to CPU1 IPC22 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC23   0x800000U     // CPU2 to CPU1 IPC23 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC24   0x1000000U    // CPU2 to CPU1 IPC24 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC25   0x2000000U    // CPU2 to CPU1 IPC25 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC26   0x4000000U    // CPU2 to CPU1 IPC26 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC27   0x8000000U    // CPU2 to CPU1 IPC27 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC28   0x10000000U   // CPU2 to CPU1 IPC28 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC29   0x20000000U   // CPU2 to CPU1 IPC29 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC30   0x40000000U   // CPU2 to CPU1 IPC30 Flag Status
#define IPC_CPU2TOCPU1IPCFLG_IPC31   0x80000000U   // CPU2 to CPU1 IPC31 Flag Status

//*************************************************************************************************
//
// The following are defines for the bit fields in the FLASHCTLSEM register
//
//*************************************************************************************************
#define IPC_FLASHCTLSEM_SEM_S   0U
#define IPC_FLASHCTLSEM_SEM_M   0x3U          // Flash Controller Access Semaphore between CPU1 and
                                              // CPU2
#define IPC_FLASHCTLSEM_KEY_S   16U
#define IPC_FLASHCTLSEM_KEY_M   0xFFFF0000U   // Key Qualifier for writes to this register



#endif
