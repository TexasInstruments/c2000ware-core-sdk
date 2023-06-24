//###########################################################################
//
// FILE:    hw_aes_ss.h
//
// TITLE:   Definitions for the AES_SS registers.
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

#ifndef HW_AES_SS_H
#define HW_AES_SS_H

//*************************************************************************************************
//
// The following are defines for the AES_SS register offsets
//
//*************************************************************************************************
#define AES_SS_O_AESDMAINTEN       0x0U   // DMA Done Interrupt enable register
#define AES_SS_O_AESDMASTATUS      0x4U   // DMA Done Interrupt status register
#define AES_SS_O_AESDMASTATUSCLR   0x8U   // DMA Done Interrupt status clear register


//*************************************************************************************************
//
// The following are defines for the bit fields in the AESDMAINTEN register
//
//*************************************************************************************************
#define AES_SS_AESDMAINTEN_DMADONECTXIN    0x1U   // Enable bit for DMADONECTXIN
#define AES_SS_AESDMAINTEN_DMADONEDIN      0x2U   // Enable bit for DMADONEDIN
#define AES_SS_AESDMAINTEN_DMADONEDOUT     0x4U   // Enable bit for DMADONEDOUT
#define AES_SS_AESDMAINTEN_DMADONECTXOUT   0x8U   // Enable bit for DMADONECTXOUT

//*************************************************************************************************
//
// The following are defines for the bit fields in the AESDMASTATUS register
//
//*************************************************************************************************
#define AES_SS_AESDMASTATUS_DMADONECTXIN    0x1U   // Status bit for DMADONECTXIN
#define AES_SS_AESDMASTATUS_DMADONEDIN      0x2U   // Status bit for DMADONEDIN
#define AES_SS_AESDMASTATUS_DMADONEDOUT     0x4U   // Status bit for DMADONEDOUT
#define AES_SS_AESDMASTATUS_DMADONECTXOUT   0x8U   // Status bit for DMADONECTXOUT

//*************************************************************************************************
//
// The following are defines for the bit fields in the AESDMASTATUSCLR register
//
//*************************************************************************************************
#define AES_SS_AESDMASTATUSCLR_DMADONECTXIN    0x1U   // Clear bit for AESDMASTSTAUS.DMADONECTXIN
#define AES_SS_AESDMASTATUSCLR_DMADONEDIN      0x2U   // Clear bit for AESDMASTSTAUS.DMADONEDIN
#define AES_SS_AESDMASTATUSCLR_DMADONEDOUT     0x4U   // Clear bit for AESDMASTSTAUS.DMADONEDOUT
#define AES_SS_AESDMASTATUSCLR_DMADONECTXOUT   0x8U   // Clear bit for AESDMASTSTAUS.DMADONECTXOUT



#endif
