//###########################################################################
//
// FILE:    f28p65x_ipc.h
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

#ifndef F28P65X_IPC_H
#define F28P65X_IPC_H

#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// IPC Individual Register Bit Definitions:

struct CPU1TOCPU2IPCACK_BITS {          // bits description
    Uint16 IPC0:1;                      // 0 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC0 bit
    Uint16 IPC1:1;                      // 1 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC1 bit
    Uint16 IPC2:1;                      // 2 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC2 bit
    Uint16 IPC3:1;                      // 3 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC3 bit
    Uint16 IPC4:1;                      // 4 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC4 bit
    Uint16 IPC5:1;                      // 5 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC5 bit
    Uint16 IPC6:1;                      // 6 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC6 bit
    Uint16 IPC7:1;                      // 7 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC7 bit
    Uint16 IPC8:1;                      // 8 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC8 bit
    Uint16 IPC9:1;                      // 9 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC9 bit
    Uint16 IPC10:1;                     // 10 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC10 bit
    Uint16 IPC11:1;                     // 11 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC11 bit
    Uint16 IPC12:1;                     // 12 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC12 bit
    Uint16 IPC13:1;                     // 13 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC13 bit
    Uint16 IPC14:1;                     // 14 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC14 bit
    Uint16 IPC15:1;                     // 15 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC15 bit
    Uint16 IPC16:1;                     // 16 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC16 bit
    Uint16 IPC17:1;                     // 17 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC17 bit
    Uint16 IPC18:1;                     // 18 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC18 bit
    Uint16 IPC19:1;                     // 19 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC19 bit
    Uint16 IPC20:1;                     // 20 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC20 bit
    Uint16 IPC21:1;                     // 21 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC21 bit
    Uint16 IPC22:1;                     // 22 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC22 bit
    Uint16 IPC23:1;                     // 23 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC23 bit
    Uint16 IPC24:1;                     // 24 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC24 bit
    Uint16 IPC25:1;                     // 25 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC25 bit
    Uint16 IPC26:1;                     // 26 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC26 bit
    Uint16 IPC27:1;                     // 27 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC27 bit
    Uint16 IPC28:1;                     // 28 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC28 bit
    Uint16 IPC29:1;                     // 29 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC29 bit
    Uint16 IPC30:1;                     // 30 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC30 bit
    Uint16 IPC31:1;                     // 31 Acknowledgement from CPU1 to CPU2TOCPU1IPCFLG.IPC31 bit
};

union CPU1TOCPU2IPCACK_REG {
    Uint32  all;
    struct  CPU1TOCPU2IPCACK_BITS  bit;
};

struct CPU2TOCPU1IPCSTS_BITS {          // bits description
    Uint16 IPC0:1;                      // 0 IPC0 Request from  CPU2 to CPU1
    Uint16 IPC1:1;                      // 1 IPC1 Request from  CPU2 to CPU1
    Uint16 IPC2:1;                      // 2 IPC2 Request from  CPU2 to CPU1
    Uint16 IPC3:1;                      // 3 IPC3 Request from  CPU2 to CPU1
    Uint16 IPC4:1;                      // 4 IPC4 Request from  CPU2 to CPU1
    Uint16 IPC5:1;                      // 5 IPC5 Request from  CPU2 to CPU1
    Uint16 IPC6:1;                      // 6 IPC6 Request from  CPU2 to CPU1
    Uint16 IPC7:1;                      // 7 IPC7 Request from  CPU2 to CPU1
    Uint16 IPC8:1;                      // 8 IPC8 Request from  CPU2 to CPU1
    Uint16 IPC9:1;                      // 9 IPC9 Request from  CPU2 to CPU1
    Uint16 IPC10:1;                     // 10 IPC10 Request from  CPU2 to CPU1
    Uint16 IPC11:1;                     // 11 IPC11 Request from  CPU2 to CPU1
    Uint16 IPC12:1;                     // 12 IPC12 Request from  CPU2 to CPU1
    Uint16 IPC13:1;                     // 13 IPC13 Request from  CPU2 to CPU1
    Uint16 IPC14:1;                     // 14 IPC14 Request from  CPU2 to CPU1
    Uint16 IPC15:1;                     // 15 IPC15 Request from  CPU2 to CPU1
    Uint16 IPC16:1;                     // 16 IPC16 Request from  CPU2 to CPU1
    Uint16 IPC17:1;                     // 17 IPC17 Request from  CPU2 to CPU1
    Uint16 IPC18:1;                     // 18 IPC18 Request from  CPU2 to CPU1
    Uint16 IPC19:1;                     // 19 IPC19 Request from  CPU2 to CPU1
    Uint16 IPC20:1;                     // 20 IPC20 Request from  CPU2 to CPU1
    Uint16 IPC21:1;                     // 21 IPC21 Request from  CPU2 to CPU1
    Uint16 IPC22:1;                     // 22 IPC22 Request from  CPU2 to CPU1
    Uint16 IPC23:1;                     // 23 IPC23 Request from  CPU2 to CPU1
    Uint16 IPC24:1;                     // 24 IPC24 Request from  CPU2 to CPU1
    Uint16 IPC25:1;                     // 25 IPC25 Request from  CPU2 to CPU1
    Uint16 IPC26:1;                     // 26 IPC26 Request from  CPU2 to CPU1
    Uint16 IPC27:1;                     // 27 IPC27 Request from  CPU2 to CPU1
    Uint16 IPC28:1;                     // 28 IPC28 Request from  CPU2 to CPU1
    Uint16 IPC29:1;                     // 29 IPC29 Request from  CPU2 to CPU1
    Uint16 IPC30:1;                     // 30 IPC30 Request from  CPU2 to CPU1
    Uint16 IPC31:1;                     // 31 IPC31 Request from  CPU2 to CPU1
};

union CPU2TOCPU1IPCSTS_REG {
    Uint32  all;
    struct  CPU2TOCPU1IPCSTS_BITS  bit;
};

struct CPU1TOCPU2IPCSET_BITS {          // bits description
    Uint16 IPC0:1;                      // 0 Set CPU1TOCPU2IPCFLG.IPC0 Flag
    Uint16 IPC1:1;                      // 1 Set CPU1TOCPU2IPCFLG.IPC1 Flag
    Uint16 IPC2:1;                      // 2 Set CPU1TOCPU2IPCFLG.IPC2 Flag
    Uint16 IPC3:1;                      // 3 Set CPU1TOCPU2IPCFLG.IPC3 Flag
    Uint16 IPC4:1;                      // 4 Set CPU1TOCPU2IPCFLG.IPC4 Flag
    Uint16 IPC5:1;                      // 5 Set CPU1TOCPU2IPCFLG.IPC5 Flag
    Uint16 IPC6:1;                      // 6 Set CPU1TOCPU2IPCFLG.IPC6 Flag
    Uint16 IPC7:1;                      // 7 Set CPU1TOCPU2IPCFLG.IPC7 Flag
    Uint16 IPC8:1;                      // 8 Set CPU1TOCPU2IPCFLG.IPC8 Flag
    Uint16 IPC9:1;                      // 9 Set CPU1TOCPU2IPCFLG.IPC9 Flag
    Uint16 IPC10:1;                     // 10 Set CPU1TOCPU2IPCFLG.IPC10 Flag
    Uint16 IPC11:1;                     // 11 Set CPU1TOCPU2IPCFLG.IPC11 Flag
    Uint16 IPC12:1;                     // 12 Set CPU1TOCPU2IPCFLG.IPC12 Flag
    Uint16 IPC13:1;                     // 13 Set CPU1TOCPU2IPCFLG.IPC13 Flag
    Uint16 IPC14:1;                     // 14 Set CPU1TOCPU2IPCFLG.IPC14 Flag
    Uint16 IPC15:1;                     // 15 Set CPU1TOCPU2IPCFLG.IPC15 Flag
    Uint16 IPC16:1;                     // 16 Set CPU1TOCPU2IPCFLG.IPC16 Flag
    Uint16 IPC17:1;                     // 17 Set CPU1TOCPU2IPCFLG.IPC17 Flag
    Uint16 IPC18:1;                     // 18 Set CPU1TOCPU2IPCFLG.IPC18 Flag
    Uint16 IPC19:1;                     // 19 Set CPU1TOCPU2IPCFLG.IPC19 Flag
    Uint16 IPC20:1;                     // 20 Set CPU1TOCPU2IPCFLG.IPC20 Flag
    Uint16 IPC21:1;                     // 21 Set CPU1TOCPU2IPCFLG.IPC21 Flag
    Uint16 IPC22:1;                     // 22 Set CPU1TOCPU2IPCFLG.IPC22 Flag
    Uint16 IPC23:1;                     // 23 Set CPU1TOCPU2IPCFLG.IPC23 Flag
    Uint16 IPC24:1;                     // 24 Set CPU1TOCPU2IPCFLG.IPC24 Flag
    Uint16 IPC25:1;                     // 25 Set CPU1TOCPU2IPCFLG.IPC25 Flag
    Uint16 IPC26:1;                     // 26 Set CPU1TOCPU2IPCFLG.IPC26 Flag
    Uint16 IPC27:1;                     // 27 Set CPU1TOCPU2IPCFLG.IPC27 Flag
    Uint16 IPC28:1;                     // 28 Set CPU1TOCPU2IPCFLG.IPC28 Flag
    Uint16 IPC29:1;                     // 29 Set CPU1TOCPU2IPCFLG.IPC29 Flag
    Uint16 IPC30:1;                     // 30 Set CPU1TOCPU2IPCFLG.IPC30 Flag
    Uint16 IPC31:1;                     // 31 Set CPU1TOCPU2IPCFLG.IPC31 Flag
};

union CPU1TOCPU2IPCSET_REG {
    Uint32  all;
    struct  CPU1TOCPU2IPCSET_BITS  bit;
};

struct CPU1TOCPU2IPCCLR_BITS {          // bits description
    Uint16 IPC0:1;                      // 0 Clear CPU1TOCPU2IPCFLG.IPC0 Flag
    Uint16 IPC1:1;                      // 1 Clear CPU1TOCPU2IPCFLG.IPC1 Flag
    Uint16 IPC2:1;                      // 2 Clear CPU1TOCPU2IPCFLG.IPC2 Flag
    Uint16 IPC3:1;                      // 3 Clear CPU1TOCPU2IPCFLG.IPC3 Flag
    Uint16 IPC4:1;                      // 4 Clear CPU1TOCPU2IPCFLG.IPC4 Flag
    Uint16 IPC5:1;                      // 5 Clear CPU1TOCPU2IPCFLG.IPC5 Flag
    Uint16 IPC6:1;                      // 6 Clear CPU1TOCPU2IPCFLG.IPC6 Flag
    Uint16 IPC7:1;                      // 7 Clear CPU1TOCPU2IPCFLG.IPC7 Flag
    Uint16 IPC8:1;                      // 8 Clear CPU1TOCPU2IPCFLG.IPC8 Flag
    Uint16 IPC9:1;                      // 9 Clear CPU1TOCPU2IPCFLG.IPC9 Flag
    Uint16 IPC10:1;                     // 10 Clear CPU1TOCPU2IPCFLG.IPC10 Flag
    Uint16 IPC11:1;                     // 11 Clear CPU1TOCPU2IPCFLG.IPC11 Flag
    Uint16 IPC12:1;                     // 12 Clear CPU1TOCPU2IPCFLG.IPC12 Flag
    Uint16 IPC13:1;                     // 13 Clear CPU1TOCPU2IPCFLG.IPC13 Flag
    Uint16 IPC14:1;                     // 14 Clear CPU1TOCPU2IPCFLG.IPC14 Flag
    Uint16 IPC15:1;                     // 15 Clear CPU1TOCPU2IPCFLG.IPC15 Flag
    Uint16 IPC16:1;                     // 16 Clear CPU1TOCPU2IPCFLG.IPC16 Flag
    Uint16 IPC17:1;                     // 17 Clear CPU1TOCPU2IPCFLG.IPC17 Flag
    Uint16 IPC18:1;                     // 18 Clear CPU1TOCPU2IPCFLG.IPC18 Flag
    Uint16 IPC19:1;                     // 19 Clear CPU1TOCPU2IPCFLG.IPC19 Flag
    Uint16 IPC20:1;                     // 20 Clear CPU1TOCPU2IPCFLG.IPC20 Flag
    Uint16 IPC21:1;                     // 21 Clear CPU1TOCPU2IPCFLG.IPC21 Flag
    Uint16 IPC22:1;                     // 22 Clear CPU1TOCPU2IPCFLG.IPC22 Flag
    Uint16 IPC23:1;                     // 23 Clear CPU1TOCPU2IPCFLG.IPC23 Flag
    Uint16 IPC24:1;                     // 24 Clear CPU1TOCPU2IPCFLG.IPC24 Flag
    Uint16 IPC25:1;                     // 25 Clear CPU1TOCPU2IPCFLG.IPC25 Flag
    Uint16 IPC26:1;                     // 26 Clear CPU1TOCPU2IPCFLG.IPC26 Flag
    Uint16 IPC27:1;                     // 27 Clear CPU1TOCPU2IPCFLG.IPC27 Flag
    Uint16 IPC28:1;                     // 28 Clear CPU1TOCPU2IPCFLG.IPC28 Flag
    Uint16 IPC29:1;                     // 29 Clear CPU1TOCPU2IPCFLG.IPC29 Flag
    Uint16 IPC30:1;                     // 30 Clear CPU1TOCPU2IPCFLG.IPC30 Flag
    Uint16 IPC31:1;                     // 31 Clear CPU1TOCPU2IPCFLG.IPC31 Flag
};

union CPU1TOCPU2IPCCLR_REG {
    Uint32  all;
    struct  CPU1TOCPU2IPCCLR_BITS  bit;
};

struct CPU1TOCPU2IPCFLG_BITS {          // bits description
    Uint16 IPC0:1;                      // 0 CPU1 to CPU2 IPC0 Flag Status
    Uint16 IPC1:1;                      // 1 CPU1 to CPU2 IPC1 Flag Status
    Uint16 IPC2:1;                      // 2 CPU1 to CPU2 IPC2 Flag Status
    Uint16 IPC3:1;                      // 3 CPU1 to CPU2 IPC3 Flag Status
    Uint16 IPC4:1;                      // 4 CPU1 to CPU2 IPC4 Flag Status
    Uint16 IPC5:1;                      // 5 CPU1 to CPU2 IPC5 Flag Status
    Uint16 IPC6:1;                      // 6 CPU1 to CPU2 IPC6 Flag Status
    Uint16 IPC7:1;                      // 7 CPU1 to CPU2 IPC7 Flag Status
    Uint16 IPC8:1;                      // 8 CPU1 to CPU2 IPC8 Flag Status
    Uint16 IPC9:1;                      // 9 CPU1 to CPU2 IPC9 Flag Status
    Uint16 IPC10:1;                     // 10 CPU1 to CPU2 IPC10 Flag Status
    Uint16 IPC11:1;                     // 11 CPU1 to CPU2 IPC11 Flag Status
    Uint16 IPC12:1;                     // 12 CPU1 to CPU2 IPC12 Flag Status
    Uint16 IPC13:1;                     // 13 CPU1 to CPU2 IPC13 Flag Status
    Uint16 IPC14:1;                     // 14 CPU1 to CPU2 IPC14 Flag Status
    Uint16 IPC15:1;                     // 15 CPU1 to CPU2 IPC15 Flag Status
    Uint16 IPC16:1;                     // 16 CPU1 to CPU2 IPC16 Flag Status
    Uint16 IPC17:1;                     // 17 CPU1 to CPU2 IPC17 Flag Status
    Uint16 IPC18:1;                     // 18 CPU1 to CPU2 IPC18 Flag Status
    Uint16 IPC19:1;                     // 19 CPU1 to CPU2 IPC19 Flag Status
    Uint16 IPC20:1;                     // 20 CPU1 to CPU2 IPC20 Flag Status
    Uint16 IPC21:1;                     // 21 CPU1 to CPU2 IPC21 Flag Status
    Uint16 IPC22:1;                     // 22 CPU1 to CPU2 IPC22 Flag Status
    Uint16 IPC23:1;                     // 23 CPU1 to CPU2 IPC23 Flag Status
    Uint16 IPC24:1;                     // 24 CPU1 to CPU2 IPC24 Flag Status
    Uint16 IPC25:1;                     // 25 CPU1 to CPU2 IPC25 Flag Status
    Uint16 IPC26:1;                     // 26 CPU1 to CPU2 IPC26 Flag Status
    Uint16 IPC27:1;                     // 27 CPU1 to CPU2 IPC27 Flag Status
    Uint16 IPC28:1;                     // 28 CPU1 to CPU2 IPC28 Flag Status
    Uint16 IPC29:1;                     // 29 CPU1 to CPU2 IPC29 Flag Status
    Uint16 IPC30:1;                     // 30 CPU1 to CPU2 IPC30 Flag Status
    Uint16 IPC31:1;                     // 31 CPU1 to CPU2 IPC31 Flag Status
};

union CPU1TOCPU2IPCFLG_REG {
    Uint32  all;
    struct  CPU1TOCPU2IPCFLG_BITS  bit;
};

struct FLASHCTLSEM_BITS {               // bits description
    Uint16 SEM:2;                       // 1:0 Flash Controller Access Semaphore between CPU1 and CPU2
    Uint16 rsvd1:14;                    // 15:2 Reserved
    Uint16 KEY:16;                      // 31:16 Key Qualifier for writes to this register
};

union FLASHCTLSEM_REG {
    Uint32  all;
    struct  FLASHCTLSEM_BITS  bit;
};

struct CPU1TOCPU2_IPC_REGS_CPU1VIEW {
    union   CPU1TOCPU2IPCACK_REG             CPU1TOCPU2IPCACK;             // CPU1TOCPU2IPCACK Register
    union   CPU2TOCPU1IPCSTS_REG             CPU2TOCPU1IPCSTS;             // CPU2TOCPU1IPCSTS Register
    union   CPU1TOCPU2IPCSET_REG             CPU1TOCPU2IPCSET;             // CPU1TOCPU2IPCSET Register
    union   CPU1TOCPU2IPCCLR_REG             CPU1TOCPU2IPCCLR;             // CPU1TOCPU2IPCCLR Register
    union   CPU1TOCPU2IPCFLG_REG             CPU1TOCPU2IPCFLG;             // CPU1TOCPU2IPCFLG Register
    Uint16                                   rsvd1[2];                     // Reserved
    Uint32                                   IPCCOUNTERL;                  // IPCCOUNTERL Register
    Uint32                                   IPCCOUNTERH;                  // IPCCOUNTERH Register
    Uint32                                   CPU1TOCPU2IPCSENDCOM;         // CPU1TOCPU2IPCSENDCOM Register
    Uint32                                   CPU1TOCPU2IPCSENDADDR;        // CPU1TOCPU2IPCSENDADDR Register
    Uint32                                   CPU1TOCPU2IPCSENDDATA;        // CPU1TOCPU2IPCSENDDATA Register
    Uint32                                   CPU2TOCPU1IPCREPLY;           // CPU2TOCPU1IPCREPLY Register
    Uint32                                   CPU2TOCPU1IPCRECVCOM;         // CPU2TOCPU1IPCRECVCOM Register
    Uint32                                   CPU2TOCPU1IPCRECVADDR;        // CPU2TOCPU1IPCRECVADDR Register
    Uint32                                   CPU2TOCPU1IPCRECVDATA;        // CPU2TOCPU1IPCRECVDATA Register
    Uint32                                   CPU1TOCPU2IPCREPLY;           // CPU1TOCPU2IPCREPLY Register
    Uint32                                   CPU2TOCPU1IPCBOOTSTS;         // CPU2TOCPU1IPCBOOTSTS Register
    Uint32                                   CPU1TOCPU2IPCBOOTMODE;        // CPU1TOCPU2IPCBOOTMODE Register
    union   FLASHCTLSEM_REG                  FLASHCTLSEM;                  // FLASHCTLSEM Register
};

struct CPU2TOCPU1IPCACK_BITS {          // bits description
    Uint16 IPC0:1;                      // 0 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC0 bit
    Uint16 IPC1:1;                      // 1 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC1 bit
    Uint16 IPC2:1;                      // 2 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC2 bit
    Uint16 IPC3:1;                      // 3 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC3 bit
    Uint16 IPC4:1;                      // 4 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC4 bit
    Uint16 IPC5:1;                      // 5 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC5 bit
    Uint16 IPC6:1;                      // 6 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC6 bit
    Uint16 IPC7:1;                      // 7 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC7 bit
    Uint16 IPC8:1;                      // 8 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC8 bit
    Uint16 IPC9:1;                      // 9 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC9 bit
    Uint16 IPC10:1;                     // 10 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC10 bit
    Uint16 IPC11:1;                     // 11 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC11 bit
    Uint16 IPC12:1;                     // 12 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC12 bit
    Uint16 IPC13:1;                     // 13 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC13 bit
    Uint16 IPC14:1;                     // 14 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC14 bit
    Uint16 IPC15:1;                     // 15 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC15 bit
    Uint16 IPC16:1;                     // 16 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC16 bit
    Uint16 IPC17:1;                     // 17 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC17 bit
    Uint16 IPC18:1;                     // 18 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC18 bit
    Uint16 IPC19:1;                     // 19 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC19 bit
    Uint16 IPC20:1;                     // 20 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC20 bit
    Uint16 IPC21:1;                     // 21 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC21 bit
    Uint16 IPC22:1;                     // 22 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC22 bit
    Uint16 IPC23:1;                     // 23 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC23 bit
    Uint16 IPC24:1;                     // 24 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC24 bit
    Uint16 IPC25:1;                     // 25 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC25 bit
    Uint16 IPC26:1;                     // 26 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC26 bit
    Uint16 IPC27:1;                     // 27 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC27 bit
    Uint16 IPC28:1;                     // 28 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC28 bit
    Uint16 IPC29:1;                     // 29 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC29 bit
    Uint16 IPC30:1;                     // 30 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC30 bit
    Uint16 IPC31:1;                     // 31 Acknowledgement from CPU2 to CPU1TOCPU2IPCFLG.IPC31 bit
};

union CPU2TOCPU1IPCACK_REG {
    Uint32  all;
    struct  CPU2TOCPU1IPCACK_BITS  bit;
};

struct CPU1TOCPU2IPCSTS_BITS {          // bits description
    Uint16 IPC0:1;                      // 0 IPC0 Request from  CPU1 to CPU2
    Uint16 IPC1:1;                      // 1 IPC1 Request from  CPU1 to CPU2
    Uint16 IPC2:1;                      // 2 IPC2 Request from  CPU1 to CPU2
    Uint16 IPC3:1;                      // 3 IPC3 Request from  CPU1 to CPU2
    Uint16 IPC4:1;                      // 4 IPC4 Request from  CPU1 to CPU2
    Uint16 IPC5:1;                      // 5 IPC5 Request from  CPU1 to CPU2
    Uint16 IPC6:1;                      // 6 IPC6 Request from  CPU1 to CPU2
    Uint16 IPC7:1;                      // 7 IPC7 Request from  CPU1 to CPU2
    Uint16 IPC8:1;                      // 8 IPC8 Request from  CPU1 to CPU2
    Uint16 IPC9:1;                      // 9 IPC9 Request from  CPU1 to CPU2
    Uint16 IPC10:1;                     // 10 IPC10 Request from  CPU1 to CPU2
    Uint16 IPC11:1;                     // 11 IPC11 Request from  CPU1 to CPU2
    Uint16 IPC12:1;                     // 12 IPC12 Request from  CPU1 to CPU2
    Uint16 IPC13:1;                     // 13 IPC13 Request from  CPU1 to CPU2
    Uint16 IPC14:1;                     // 14 IPC14 Request from  CPU1 to CPU2
    Uint16 IPC15:1;                     // 15 IPC15 Request from  CPU1 to CPU2
    Uint16 IPC16:1;                     // 16 IPC16 Request from  CPU1 to CPU2
    Uint16 IPC17:1;                     // 17 IPC17 Request from  CPU1 to CPU2
    Uint16 IPC18:1;                     // 18 IPC18 Request from  CPU1 to CPU2
    Uint16 IPC19:1;                     // 19 IPC19 Request from  CPU1 to CPU2
    Uint16 IPC20:1;                     // 20 IPC20 Request from  CPU1 to CPU2
    Uint16 IPC21:1;                     // 21 IPC21 Request from  CPU1 to CPU2
    Uint16 IPC22:1;                     // 22 IPC22 Request from  CPU1 to CPU2
    Uint16 IPC23:1;                     // 23 IPC23 Request from  CPU1 to CPU2
    Uint16 IPC24:1;                     // 24 IPC24 Request from  CPU1 to CPU2
    Uint16 IPC25:1;                     // 25 IPC25 Request from  CPU1 to CPU2
    Uint16 IPC26:1;                     // 26 IPC26 Request from  CPU1 to CPU2
    Uint16 IPC27:1;                     // 27 IPC27 Request from  CPU1 to CPU2
    Uint16 IPC28:1;                     // 28 IPC28 Request from  CPU1 to CPU2
    Uint16 IPC29:1;                     // 29 IPC29 Request from  CPU1 to CPU2
    Uint16 IPC30:1;                     // 30 IPC30 Request from  CPU1 to CPU2
    Uint16 IPC31:1;                     // 31 IPC31 Request from  CPU1 to CPU2
};

union CPU1TOCPU2IPCSTS_REG {
    Uint32  all;
    struct  CPU1TOCPU2IPCSTS_BITS  bit;
};

struct CPU2TOCPU1IPCSET_BITS {          // bits description
    Uint16 IPC0:1;                      // 0 Set CPU2TOCPU1IPCFLG.IPC0 Flag
    Uint16 IPC1:1;                      // 1 Set CPU2TOCPU1IPCFLG.IPC1 Flag
    Uint16 IPC2:1;                      // 2 Set CPU2TOCPU1IPCFLG.IPC2 Flag
    Uint16 IPC3:1;                      // 3 Set CPU2TOCPU1IPCFLG.IPC3 Flag
    Uint16 IPC4:1;                      // 4 Set CPU2TOCPU1IPCFLG.IPC4 Flag
    Uint16 IPC5:1;                      // 5 Set CPU2TOCPU1IPCFLG.IPC5 Flag
    Uint16 IPC6:1;                      // 6 Set CPU2TOCPU1IPCFLG.IPC6 Flag
    Uint16 IPC7:1;                      // 7 Set CPU2TOCPU1IPCFLG.IPC7 Flag
    Uint16 IPC8:1;                      // 8 Set CPU2TOCPU1IPCFLG.IPC8 Flag
    Uint16 IPC9:1;                      // 9 Set CPU2TOCPU1IPCFLG.IPC9 Flag
    Uint16 IPC10:1;                     // 10 Set CPU2TOCPU1IPCFLG.IPC10 Flag
    Uint16 IPC11:1;                     // 11 Set CPU2TOCPU1IPCFLG.IPC11 Flag
    Uint16 IPC12:1;                     // 12 Set CPU2TOCPU1IPCFLG.IPC12 Flag
    Uint16 IPC13:1;                     // 13 Set CPU2TOCPU1IPCFLG.IPC13 Flag
    Uint16 IPC14:1;                     // 14 Set CPU2TOCPU1IPCFLG.IPC14 Flag
    Uint16 IPC15:1;                     // 15 Set CPU2TOCPU1IPCFLG.IPC15 Flag
    Uint16 IPC16:1;                     // 16 Set CPU2TOCPU1IPCFLG.IPC16 Flag
    Uint16 IPC17:1;                     // 17 Set CPU2TOCPU1IPCFLG.IPC17 Flag
    Uint16 IPC18:1;                     // 18 Set CPU2TOCPU1IPCFLG.IPC18 Flag
    Uint16 IPC19:1;                     // 19 Set CPU2TOCPU1IPCFLG.IPC19 Flag
    Uint16 IPC20:1;                     // 20 Set CPU2TOCPU1IPCFLG.IPC20 Flag
    Uint16 IPC21:1;                     // 21 Set CPU2TOCPU1IPCFLG.IPC21 Flag
    Uint16 IPC22:1;                     // 22 Set CPU2TOCPU1IPCFLG.IPC22 Flag
    Uint16 IPC23:1;                     // 23 Set CPU2TOCPU1IPCFLG.IPC23 Flag
    Uint16 IPC24:1;                     // 24 Set CPU2TOCPU1IPCFLG.IPC24 Flag
    Uint16 IPC25:1;                     // 25 Set CPU2TOCPU1IPCFLG.IPC25 Flag
    Uint16 IPC26:1;                     // 26 Set CPU2TOCPU1IPCFLG.IPC26 Flag
    Uint16 IPC27:1;                     // 27 Set CPU2TOCPU1IPCFLG.IPC27 Flag
    Uint16 IPC28:1;                     // 28 Set CPU2TOCPU1IPCFLG.IPC28 Flag
    Uint16 IPC29:1;                     // 29 Set CPU2TOCPU1IPCFLG.IPC29 Flag
    Uint16 IPC30:1;                     // 30 Set CPU2TOCPU1IPCFLG.IPC30 Flag
    Uint16 IPC31:1;                     // 31 Set CPU2TOCPU1IPCFLG.IPC31 Flag
};

union CPU2TOCPU1IPCSET_REG {
    Uint32  all;
    struct  CPU2TOCPU1IPCSET_BITS  bit;
};

struct CPU2TOCPU1IPCCLR_BITS {          // bits description
    Uint16 IPC0:1;                      // 0 Clear CPU2TOCPU1IPCFLG.IPC0 Flag
    Uint16 IPC1:1;                      // 1 Clear CPU2TOCPU1IPCFLG.IPC1 Flag
    Uint16 IPC2:1;                      // 2 Clear CPU2TOCPU1IPCFLG.IPC2 Flag
    Uint16 IPC3:1;                      // 3 Clear CPU2TOCPU1IPCFLG.IPC3 Flag
    Uint16 IPC4:1;                      // 4 Clear CPU2TOCPU1IPCFLG.IPC4 Flag
    Uint16 IPC5:1;                      // 5 Clear CPU2TOCPU1IPCFLG.IPC5 Flag
    Uint16 IPC6:1;                      // 6 Clear CPU2TOCPU1IPCFLG.IPC6 Flag
    Uint16 IPC7:1;                      // 7 Clear CPU2TOCPU1IPCFLG.IPC7 Flag
    Uint16 IPC8:1;                      // 8 Clear CPU2TOCPU1IPCFLG.IPC8 Flag
    Uint16 IPC9:1;                      // 9 Clear CPU2TOCPU1IPCFLG.IPC9 Flag
    Uint16 IPC10:1;                     // 10 Clear CPU2TOCPU1IPCFLG.IPC10 Flag
    Uint16 IPC11:1;                     // 11 Clear CPU2TOCPU1IPCFLG.IPC11 Flag
    Uint16 IPC12:1;                     // 12 Clear CPU2TOCPU1IPCFLG.IPC12 Flag
    Uint16 IPC13:1;                     // 13 Clear CPU2TOCPU1IPCFLG.IPC13 Flag
    Uint16 IPC14:1;                     // 14 Clear CPU2TOCPU1IPCFLG.IPC14 Flag
    Uint16 IPC15:1;                     // 15 Clear CPU2TOCPU1IPCFLG.IPC15 Flag
    Uint16 IPC16:1;                     // 16 Clear CPU2TOCPU1IPCFLG.IPC16 Flag
    Uint16 IPC17:1;                     // 17 Clear CPU2TOCPU1IPCFLG.IPC17 Flag
    Uint16 IPC18:1;                     // 18 Clear CPU2TOCPU1IPCFLG.IPC18 Flag
    Uint16 IPC19:1;                     // 19 Clear CPU2TOCPU1IPCFLG.IPC19 Flag
    Uint16 IPC20:1;                     // 20 Clear CPU2TOCPU1IPCFLG.IPC20 Flag
    Uint16 IPC21:1;                     // 21 Clear CPU2TOCPU1IPCFLG.IPC21 Flag
    Uint16 IPC22:1;                     // 22 Clear CPU2TOCPU1IPCFLG.IPC22 Flag
    Uint16 IPC23:1;                     // 23 Clear CPU2TOCPU1IPCFLG.IPC23 Flag
    Uint16 IPC24:1;                     // 24 Clear CPU2TOCPU1IPCFLG.IPC24 Flag
    Uint16 IPC25:1;                     // 25 Clear CPU2TOCPU1IPCFLG.IPC25 Flag
    Uint16 IPC26:1;                     // 26 Clear CPU2TOCPU1IPCFLG.IPC26 Flag
    Uint16 IPC27:1;                     // 27 Clear CPU2TOCPU1IPCFLG.IPC27 Flag
    Uint16 IPC28:1;                     // 28 Clear CPU2TOCPU1IPCFLG.IPC28 Flag
    Uint16 IPC29:1;                     // 29 Clear CPU2TOCPU1IPCFLG.IPC29 Flag
    Uint16 IPC30:1;                     // 30 Clear CPU2TOCPU1IPCFLG.IPC30 Flag
    Uint16 IPC31:1;                     // 31 Clear CPU2TOCPU1IPCFLG.IPC31 Flag
};

union CPU2TOCPU1IPCCLR_REG {
    Uint32  all;
    struct  CPU2TOCPU1IPCCLR_BITS  bit;
};

struct CPU2TOCPU1IPCFLG_BITS {          // bits description
    Uint16 IPC0:1;                      // 0 CPU2 to CPU1 IPC0 Flag Status
    Uint16 IPC1:1;                      // 1 CPU2 to CPU1 IPC1 Flag Status
    Uint16 IPC2:1;                      // 2 CPU2 to CPU1 IPC2 Flag Status
    Uint16 IPC3:1;                      // 3 CPU2 to CPU1 IPC3 Flag Status
    Uint16 IPC4:1;                      // 4 CPU2 to CPU1 IPC4 Flag Status
    Uint16 IPC5:1;                      // 5 CPU2 to CPU1 IPC5 Flag Status
    Uint16 IPC6:1;                      // 6 CPU2 to CPU1 IPC6 Flag Status
    Uint16 IPC7:1;                      // 7 CPU2 to CPU1 IPC7 Flag Status
    Uint16 IPC8:1;                      // 8 CPU2 to CPU1 IPC8 Flag Status
    Uint16 IPC9:1;                      // 9 CPU2 to CPU1 IPC9 Flag Status
    Uint16 IPC10:1;                     // 10 CPU2 to CPU1 IPC10 Flag Status
    Uint16 IPC11:1;                     // 11 CPU2 to CPU1 IPC11 Flag Status
    Uint16 IPC12:1;                     // 12 CPU2 to CPU1 IPC12 Flag Status
    Uint16 IPC13:1;                     // 13 CPU2 to CPU1 IPC13 Flag Status
    Uint16 IPC14:1;                     // 14 CPU2 to CPU1 IPC14 Flag Status
    Uint16 IPC15:1;                     // 15 CPU2 to CPU1 IPC15 Flag Status
    Uint16 IPC16:1;                     // 16 CPU2 to CPU1 IPC16 Flag Status
    Uint16 IPC17:1;                     // 17 CPU2 to CPU1 IPC17 Flag Status
    Uint16 IPC18:1;                     // 18 CPU2 to CPU1 IPC18 Flag Status
    Uint16 IPC19:1;                     // 19 CPU2 to CPU1 IPC19 Flag Status
    Uint16 IPC20:1;                     // 20 CPU2 to CPU1 IPC20 Flag Status
    Uint16 IPC21:1;                     // 21 CPU2 to CPU1 IPC21 Flag Status
    Uint16 IPC22:1;                     // 22 CPU2 to CPU1 IPC22 Flag Status
    Uint16 IPC23:1;                     // 23 CPU2 to CPU1 IPC23 Flag Status
    Uint16 IPC24:1;                     // 24 CPU2 to CPU1 IPC24 Flag Status
    Uint16 IPC25:1;                     // 25 CPU2 to CPU1 IPC25 Flag Status
    Uint16 IPC26:1;                     // 26 CPU2 to CPU1 IPC26 Flag Status
    Uint16 IPC27:1;                     // 27 CPU2 to CPU1 IPC27 Flag Status
    Uint16 IPC28:1;                     // 28 CPU2 to CPU1 IPC28 Flag Status
    Uint16 IPC29:1;                     // 29 CPU2 to CPU1 IPC29 Flag Status
    Uint16 IPC30:1;                     // 30 CPU2 to CPU1 IPC30 Flag Status
    Uint16 IPC31:1;                     // 31 CPU2 to CPU1 IPC31 Flag Status
};

union CPU2TOCPU1IPCFLG_REG {
    Uint32  all;
    struct  CPU2TOCPU1IPCFLG_BITS  bit;
};

struct CPU1TOCPU2_IPC_REGS_CPU2VIEW {
    union   CPU2TOCPU1IPCACK_REG             CPU2TOCPU1IPCACK;             // CPU2TOCPU1IPCACK Register
    union   CPU1TOCPU2IPCSTS_REG             CPU1TOCPU2IPCSTS;             // CPU1TOCPU2IPCSTS Register
    union   CPU2TOCPU1IPCSET_REG             CPU2TOCPU1IPCSET;             // CPU2TOCPU1IPCSET Register
    union   CPU2TOCPU1IPCCLR_REG             CPU2TOCPU1IPCCLR;             // CPU2TOCPU1IPCCLR Register
    union   CPU2TOCPU1IPCFLG_REG             CPU2TOCPU1IPCFLG;             // CPU2TOCPU1IPCFLG Register
    Uint16                                   rsvd1[2];                     // Reserved
    Uint32                                   IPCCOUNTERL;                  // IPCCOUNTERL Register
    Uint32                                   IPCCOUNTERH;                  // IPCCOUNTERH Register
    Uint32                                   CPU1TOCPU2IPCRECVCOM;         // CPU1TOCPU2IPCRECVCOM Register
    Uint32                                   CPU1TOCPU2IPCRECVADDR;        // CPU1TOCPU2IPCRECVADDR Register
    Uint32                                   CPU1TOCPU2IPCRECVDATA;        // CPU1TOCPU2IPCRECVDATA Register
    Uint32                                   CPU2TOCPU1IPCREPLY;           // CPU2TOCPU1IPCREPLY Register
    Uint32                                   CPU2TOCPU1IPCSENDCOM;         // CPU2TOCPU1IPCSENDCOM Register
    Uint32                                   CPU2TOCPU1IPCSENDADDR;        // CPU2TOCPU1IPCSENDADDR Register
    Uint32                                   CPU2TOCPU1IPCSENDDATA;        // CPU2TOCPU1IPCSENDDATA Register
    Uint32                                   CPU1TOCPU2IPCREPLY;           // CPU1TOCPU2IPCREPLY Register
    Uint32                                   CPU2TOCPU1IPCBOOTSTS;         // CPU2TOCPU1IPCBOOTSTS Register
    Uint32                                   CPU1TOCPU2IPCBOOTMODE;        // CPU1TOCPU2IPCBOOTMODE Register
    union   FLASHCTLSEM_REG                  FLASHCTLSEM;                  // FLASHCTLSEM Register
};

//---------------------------------------------------------------------------
// IPC External References & Function Declarations:
//
#ifdef CPU1
extern volatile struct CPU1TOCPU2_IPC_REGS_CPU1VIEW Cpu1toCpu2IpcRegs;
#endif
#ifdef CPU2
extern volatile struct CPU1TOCPU2_IPC_REGS_CPU2VIEW Cpu2toCpu1IpcRegs;
#endif
#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif

//===========================================================================
// End of file.
//===========================================================================
