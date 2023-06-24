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

//*****************************************************************************
//
// The following are defines for the IPC register offsets
//
//*****************************************************************************
#define IPC_O_ACK                 0x0U         // IPC incoming flag clear
                                               // (acknowledge) register
#define IPC_O_STS                 0x2U         // IPC incoming flag status
                                               // register
#define IPC_O_SET                 0x4U         // IPC remote flag set register
#define IPC_O_CLR                 0x6U         // IPC remote flag clear
                                               // register
#define IPC_O_FLG                 0x8U         // IPC remote flag status
                                               // register
#define IPC_O_COUNTERL            0xCU         // IPC Counter Low Register
#define IPC_O_COUNTERH            0xEU         // IPC Counter High Register
#ifndef CPU2
#define IPC_O_SENDCOM             0x10U        // Local to Remote IPC Command
                                               // Register
#define IPC_O_SENDADDR            0x12U        // Local to Remote IPC Address
                                               // Register
#define IPC_O_SENDDATA            0x14U        // Local to Remote IPC Data
                                               // Register
#define IPC_O_REMOTEREPLY         0x16U        // Remote to Local IPC Reply
                                               // Data Register
#define IPC_O_RECVCOM             0x18U        // Remote to Local IPC Command
                                               // Register
#define IPC_O_RECVADDR            0x1AU        // Remote to Local IPC Address
                                               // Register
#define IPC_O_RECVDATA            0x1CU        // Remote to Local IPC Data
                                               // Register
#define IPC_O_LOCALREPLY          0x1EU        // Local to Remote IPC Reply
                                               // Data Register
#else
#define IPC_O_RECVCOM             0x10U        // Remote to Local IPC Command
                                               // Register
#define IPC_O_RECVADDR            0x12U        // Remote to Local IPC Address
                                               // Register
#define IPC_O_RECVDATA            0x14U        // Remote to Local IPC Data
                                               // Register
#define IPC_O_LOCALREPLY          0x16U        // Local to Remote IPC Reply
                                               // Data Register
#define IPC_O_SENDCOM             0x18U        // Local to Remote IPC Command
                                               // Register
#define IPC_O_SENDADDR            0x1AU        // Local to Remote IPC Address
                                               // Register
#define IPC_O_SENDDATA            0x1CU        // Local to Remote IPC Data
                                               // Register
#define IPC_O_REMOTEREPLY         0x1EU        // Remote to Local IPC Reply
                                               // Data Register
#endif
#define IPC_O_BOOTSTS             0x20U        // CPU2 to CPU1 IPC Boot Status
                                               // Register
#define IPC_O_BOOTMODE            0x22U        // CPU1 to CPU2 IPC Boot Mode
                                               // Register

//*****************************************************************************
//
// The following are defines for the bit fields in the IPCACK register
//
//*****************************************************************************
#define IPC_ACK_IPC0              0x1U         // Local IPC Flag 0
                                               // Acknowledgement
#define IPC_ACK_IPC1              0x2U         // Local IPC Flag 1
                                               // Acknowledgement
#define IPC_ACK_IPC2              0x4U         // Local IPC Flag 2
                                               // Acknowledgement
#define IPC_ACK_IPC3              0x8U         // Local IPC Flag 3
                                               // Acknowledgement
#define IPC_ACK_IPC4              0x10U        // Local IPC Flag 4
                                               // Acknowledgement
#define IPC_ACK_IPC5              0x20U        // Local IPC Flag 5
                                               // Acknowledgement
#define IPC_ACK_IPC6              0x40U        // Local IPC Flag 6
                                               // Acknowledgement
#define IPC_ACK_IPC7              0x80U        // Local IPC Flag 7
                                               // Acknowledgement
#define IPC_ACK_IPC8              0x100U       // Local IPC Flag 8
                                               // Acknowledgement
#define IPC_ACK_IPC9              0x200U       // Local IPC Flag 9
                                               // Acknowledgement
#define IPC_ACK_IPC10             0x400U       // Local IPC Flag 10
                                               // Acknowledgement
#define IPC_ACK_IPC11             0x800U       // Local IPC Flag 11
                                               // Acknowledgement
#define IPC_ACK_IPC12             0x1000U      // Local IPC Flag 12
                                               // Acknowledgement
#define IPC_ACK_IPC13             0x2000U      // Local IPC Flag 13
                                               // Acknowledgement
#define IPC_ACK_IPC14             0x4000U      // Local IPC Flag 14
                                               // Acknowledgement
#define IPC_ACK_IPC15             0x8000U      // Local IPC Flag 15
                                               // Acknowledgement
#define IPC_ACK_IPC16             0x10000U     // Local IPC Flag 16
                                               // Acknowledgement
#define IPC_ACK_IPC17             0x20000U     // Local IPC Flag 17
                                               // Acknowledgement
#define IPC_ACK_IPC18             0x40000U     // Local IPC Flag 18
                                               // Acknowledgement
#define IPC_ACK_IPC19             0x80000U     // Local IPC Flag 19
                                               // Acknowledgement
#define IPC_ACK_IPC20             0x100000U    // Local IPC Flag 20
                                               // Acknowledgement
#define IPC_ACK_IPC21             0x200000U    // Local IPC Flag 21
                                               // Acknowledgement
#define IPC_ACK_IPC22             0x400000U    // Local IPC Flag 22
                                               // Acknowledgement
#define IPC_ACK_IPC23             0x800000U    // Local IPC Flag 23
                                               // Acknowledgement
#define IPC_ACK_IPC24             0x1000000U   // Local IPC Flag 24
                                               // Acknowledgement
#define IPC_ACK_IPC25             0x2000000U   // Local IPC Flag 25
                                               // Acknowledgement
#define IPC_ACK_IPC26             0x4000000U   // Local IPC Flag 26
                                               // Acknowledgement
#define IPC_ACK_IPC27             0x8000000U   // Local IPC Flag 27
                                               // Acknowledgement
#define IPC_ACK_IPC28             0x10000000U  // Local IPC Flag 28
                                               // Acknowledgement
#define IPC_ACK_IPC29             0x20000000U  // Local IPC Flag 29
                                               // Acknowledgement
#define IPC_ACK_IPC30             0x40000000U  // Local IPC Flag 30
                                               // Acknowledgement
#define IPC_ACK_IPC31             0x80000000U  // Local IPC Flag 31
                                               // Acknowledgement

//*****************************************************************************
//
// The following are defines for the bit fields in the IPCSTS register
//
//*****************************************************************************
#define IPC_STS_IPC0              0x1U         // Local IPC Flag 0 Status
#define IPC_STS_IPC1              0x2U         // Local IPC Flag 1 Status
#define IPC_STS_IPC2              0x4U         // Local IPC Flag 2 Status
#define IPC_STS_IPC3              0x8U         // Local IPC Flag 3 Status
#define IPC_STS_IPC4              0x10U        // Local IPC Flag 4 Status
#define IPC_STS_IPC5              0x20U        // Local IPC Flag 5 Status
#define IPC_STS_IPC6              0x40U        // Local IPC Flag 6 Status
#define IPC_STS_IPC7              0x80U        // Local IPC Flag 7 Status
#define IPC_STS_IPC8              0x100U       // Local IPC Flag 8 Status
#define IPC_STS_IPC9              0x200U       // Local IPC Flag 9 Status
#define IPC_STS_IPC10             0x400U       // Local IPC Flag 10 Status
#define IPC_STS_IPC11             0x800U       // Local IPC Flag 11 Status
#define IPC_STS_IPC12             0x1000U      // Local IPC Flag 12 Status
#define IPC_STS_IPC13             0x2000U      // Local IPC Flag 13 Status
#define IPC_STS_IPC14             0x4000U      // Local IPC Flag 14 Status
#define IPC_STS_IPC15             0x8000U      // Local IPC Flag 15 Status
#define IPC_STS_IPC16             0x10000U     // Local IPC Flag 16 Status
#define IPC_STS_IPC17             0x20000U     // Local IPC Flag 17 Status
#define IPC_STS_IPC18             0x40000U     // Local IPC Flag 18 Status
#define IPC_STS_IPC19             0x80000U     // Local IPC Flag 19 Status
#define IPC_STS_IPC20             0x100000U    // Local IPC Flag 20 Status
#define IPC_STS_IPC21             0x200000U    // Local IPC Flag 21 Status
#define IPC_STS_IPC22             0x400000U    // Local IPC Flag 22 Status
#define IPC_STS_IPC23             0x800000U    // Local IPC Flag 23 Status
#define IPC_STS_IPC24             0x1000000U   // Local IPC Flag 24 Status
#define IPC_STS_IPC25             0x2000000U   // Local IPC Flag 25 Status
#define IPC_STS_IPC26             0x4000000U   // Local IPC Flag 26 Status
#define IPC_STS_IPC27             0x8000000U   // Local IPC Flag 27 Status
#define IPC_STS_IPC28             0x10000000U  // Local IPC Flag 28 Status
#define IPC_STS_IPC29             0x20000000U  // Local IPC Flag 29 Status
#define IPC_STS_IPC30             0x40000000U  // Local IPC Flag 30 Status
#define IPC_STS_IPC31             0x80000000U  // Local IPC Flag 31 Status

//*****************************************************************************
//
// The following are defines for the bit fields in the IPCSET register
//
//*****************************************************************************
#define IPC_SET_IPC0              0x1U         // Set Remote IPC0 Flag
#define IPC_SET_IPC1              0x2U         // Set Remote IPC1 Flag
#define IPC_SET_IPC2              0x4U         // Set Remote IPC2 Flag
#define IPC_SET_IPC3              0x8U         // Set Remote IPC3 Flag
#define IPC_SET_IPC4              0x10U        // Set Remote IPC4 Flag
#define IPC_SET_IPC5              0x20U        // Set Remote IPC5 Flag
#define IPC_SET_IPC6              0x40U        // Set Remote IPC6 Flag
#define IPC_SET_IPC7              0x80U        // Set Remote IPC7 Flag
#define IPC_SET_IPC8              0x100U       // Set Remote IPC8 Flag
#define IPC_SET_IPC9              0x200U       // Set Remote IPC9 Flag
#define IPC_SET_IPC10             0x400U       // Set Remote IPC10 Flag
#define IPC_SET_IPC11             0x800U       // Set Remote IPC11 Flag
#define IPC_SET_IPC12             0x1000U      // Set Remote IPC12 Flag
#define IPC_SET_IPC13             0x2000U      // Set Remote IPC13 Flag
#define IPC_SET_IPC14             0x4000U      // Set Remote IPC14 Flag
#define IPC_SET_IPC15             0x8000U      // Set Remote IPC15 Flag
#define IPC_SET_IPC16             0x10000U     // Set Remote IPC16 Flag
#define IPC_SET_IPC17             0x20000U     // Set Remote IPC17 Flag
#define IPC_SET_IPC18             0x40000U     // Set Remote IPC18 Flag
#define IPC_SET_IPC19             0x80000U     // Set Remote IPC19 Flag
#define IPC_SET_IPC20             0x100000U    // Set Remote IPC20 Flag
#define IPC_SET_IPC21             0x200000U    // Set Remote IPC21 Flag
#define IPC_SET_IPC22             0x400000U    // Set Remote IPC22 Flag
#define IPC_SET_IPC23             0x800000U    // Set Remote IPC23 Flag
#define IPC_SET_IPC24             0x1000000U   // Set Remote IPC24 Flag
#define IPC_SET_IPC25             0x2000000U   // Set Remote IPC25 Flag
#define IPC_SET_IPC26             0x4000000U   // Set Remote IPC26 Flag
#define IPC_SET_IPC27             0x8000000U   // Set Remote IPC27 Flag
#define IPC_SET_IPC28             0x10000000U  // Set Remote IPC28 Flag
#define IPC_SET_IPC29             0x20000000U  // Set Remote IPC29 Flag
#define IPC_SET_IPC30             0x40000000U  // Set Remote IPC30 Flag
#define IPC_SET_IPC31             0x80000000U  // Set Remote IPC31 Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the IPCCLR register
//
//*****************************************************************************
#define IPC_CLR_IPC0              0x1U         // Clear Remote IPC0 Flag
#define IPC_CLR_IPC1              0x2U         // Clear Remote IPC1 Flag
#define IPC_CLR_IPC2              0x4U         // Clear Remote IPC2 Flag
#define IPC_CLR_IPC3              0x8U         // Clear Remote IPC3 Flag
#define IPC_CLR_IPC4              0x10U        // Clear Remote IPC4 Flag
#define IPC_CLR_IPC5              0x20U        // Clear Remote IPC5 Flag
#define IPC_CLR_IPC6              0x40U        // Clear Remote IPC6 Flag
#define IPC_CLR_IPC7              0x80U        // Clear Remote IPC7 Flag
#define IPC_CLR_IPC8              0x100U       // Clear Remote IPC8 Flag
#define IPC_CLR_IPC9              0x200U       // Clear Remote IPC9 Flag
#define IPC_CLR_IPC10             0x400U       // Clear Remote IPC10 Flag
#define IPC_CLR_IPC11             0x800U       // Clear Remote IPC11 Flag
#define IPC_CLR_IPC12             0x1000U      // Clear Remote IPC12 Flag
#define IPC_CLR_IPC13             0x2000U      // Clear Remote IPC13 Flag
#define IPC_CLR_IPC14             0x4000U      // Clear Remote IPC14 Flag
#define IPC_CLR_IPC15             0x8000U      // Clear Remote IPC15 Flag
#define IPC_CLR_IPC16             0x10000U     // Clear Remote IPC16 Flag
#define IPC_CLR_IPC17             0x20000U     // Clear Remote IPC17 Flag
#define IPC_CLR_IPC18             0x40000U     // Clear Remote IPC18 Flag
#define IPC_CLR_IPC19             0x80000U     // Clear Remote IPC19 Flag
#define IPC_CLR_IPC20             0x100000U    // Clear Remote IPC20 Flag
#define IPC_CLR_IPC21             0x200000U    // Clear Remote IPC21 Flag
#define IPC_CLR_IPC22             0x400000U    // Clear Remote IPC22 Flag
#define IPC_CLR_IPC23             0x800000U    // Clear Remote IPC23 Flag
#define IPC_CLR_IPC24             0x1000000U   // Clear Remote IPC24 Flag
#define IPC_CLR_IPC25             0x2000000U   // Clear Remote IPC25 Flag
#define IPC_CLR_IPC26             0x4000000U   // Clear Remote IPC26 Flag
#define IPC_CLR_IPC27             0x8000000U   // Clear Remote IPC27 Flag
#define IPC_CLR_IPC28             0x10000000U  // Clear Remote IPC28 Flag
#define IPC_CLR_IPC29             0x20000000U  // Clear Remote IPC29 Flag
#define IPC_CLR_IPC30             0x40000000U  // Clear Remote IPC30 Flag
#define IPC_CLR_IPC31             0x80000000U  // Clear Remote IPC31 Flag

//*****************************************************************************
//
// The following are defines for the bit fields in the IPCFLG register
//
//*****************************************************************************
#define IPC_FLG_IPC0              0x1U         // Remote IPC0 Flag Status
#define IPC_FLG_IPC1              0x2U         // Remote IPC1 Flag Status
#define IPC_FLG_IPC2              0x4U         // Remote IPC2 Flag Status
#define IPC_FLG_IPC3              0x8U         // Remote IPC3 Flag Status
#define IPC_FLG_IPC4              0x10U        // Remote IPC4 Flag Status
#define IPC_FLG_IPC5              0x20U        // Remote IPC5 Flag Status
#define IPC_FLG_IPC6              0x40U        // Remote IPC6 Flag Status
#define IPC_FLG_IPC7              0x80U        // Remote IPC7 Flag Status
#define IPC_FLG_IPC8              0x100U       // Remote IPC8 Flag Status
#define IPC_FLG_IPC9              0x200U       // Remote IPC9 Flag Status
#define IPC_FLG_IPC10             0x400U       // Remote IPC10 Flag Status
#define IPC_FLG_IPC11             0x800U       // Remote IPC11 Flag Status
#define IPC_FLG_IPC12             0x1000U      // Remote IPC12 Flag Status
#define IPC_FLG_IPC13             0x2000U      // Remote IPC13 Flag Status
#define IPC_FLG_IPC14             0x4000U      // Remote IPC14 Flag Status
#define IPC_FLG_IPC15             0x8000U      // Remote IPC15 Flag Status
#define IPC_FLG_IPC16             0x10000U     // Remote IPC16 Flag Status
#define IPC_FLG_IPC17             0x20000U     // Remote IPC17 Flag Status
#define IPC_FLG_IPC18             0x40000U     // Remote IPC18 Flag Status
#define IPC_FLG_IPC19             0x80000U     // Remote IPC19 Flag Status
#define IPC_FLG_IPC20             0x100000U    // Remote IPC20 Flag Status
#define IPC_FLG_IPC21             0x200000U    // Remote IPC21 Flag Status
#define IPC_FLG_IPC22             0x400000U    // Remote IPC22 Flag Status
#define IPC_FLG_IPC23             0x800000U    // Remote IPC23 Flag Status
#define IPC_FLG_IPC24             0x1000000U   // Remote IPC24 Flag Status
#define IPC_FLG_IPC25             0x2000000U   // Remote IPC25 Flag Status
#define IPC_FLG_IPC26             0x4000000U   // Remote IPC26 Flag Status
#define IPC_FLG_IPC27             0x8000000U   // Remote IPC27 Flag Status
#define IPC_FLG_IPC28             0x10000000U  // Remote IPC28 Flag Status
#define IPC_FLG_IPC29             0x20000000U  // Remote IPC29 Flag Status
#define IPC_FLG_IPC30             0x40000000U  // Remote IPC30 Flag Status
#define IPC_FLG_IPC31             0x80000000U  // Remote IPC31 Flag Status
#endif
