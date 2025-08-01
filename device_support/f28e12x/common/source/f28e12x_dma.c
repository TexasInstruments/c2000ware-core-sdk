//###########################################################################
//
// FILE:    f28e12x_dma.c
//
// TITLE:   F28P65x Device DMA Initialization & Support Functions.
//
//###########################################################################
//
//
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

//
// Included Files
//
#include "f28e12x_device.h"
#include "f28e12x_examples.h"

//
// DMAInitialize - This function initializes the DMA to a known state.
//
void DMAInitialize(void)
{
    EALLOW;

    //
    // Perform a hard reset on DMA
    //
    DmaRegs.DMACTRL.bit.HARDRESET = 1;
   __asm (" nop"); // one NOP required after HARDRESET

    //
    // Allow DMA to run free on emulation suspend
    //
    DmaRegs.DEBUGCTRL.bit.FREE = 1;

    EDIS;
}

//
// DMACH1AddrConfig - DMA Channel 1 Address Configuration
//
void DMACH1AddrConfig(volatile Uint16 *DMA_Dest,volatile Uint16 *DMA_Source)
{
    EALLOW;

    //
    // Set up SOURCE address:
    //
    DmaRegs.CH1.SRC_BEG_ADDR_SHADOW = (Uint32)DMA_Source;   // Point to
                                                            // beginning of
                                                            // source buffer
    DmaRegs.CH1.SRC_ADDR_SHADOW =     (Uint32)DMA_Source;

    //
    // Set up DESTINATION address:
    //
    DmaRegs.CH1.DST_BEG_ADDR_SHADOW = (Uint32)DMA_Dest;  // Point to
                                                         // beginning of
                                                         // destination buffer
    DmaRegs.CH1.DST_ADDR_SHADOW =     (Uint32)DMA_Dest;

    EDIS;
}

//
// DMACH1BurstConfig - DMA Channel 1 Burst size configuration
//
void DMACH1BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep)
{
    EALLOW;

    //
    // Set up BURST registers:
    //
    DmaRegs.CH1.BURST_SIZE.all = bsize;      // Number of words(X-1)
                                             // x-ferred in a burst.
    DmaRegs.CH1.SRC_BURST_STEP = srcbstep;   // Increment source addr between
                                             // each word x-ferred.
    DmaRegs.CH1.DST_BURST_STEP = desbstep;   // Increment dest addr between
                                             // each word x-ferred.

    EDIS;
}

//
// DMACH1TransferConfig - DMA Channel 1 Transfer size configuration
//
void DMACH1TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep)
{
    EALLOW;

    //
    // Set up TRANSFER registers:
    //
    DmaRegs.CH1.TRANSFER_SIZE.bit.TRANSFERSIZE = tsize;  // Number of bursts 
                                              // per transfer, DMA interrupt will 
                                              // occur aftercompleted transfer.
    DmaRegs.CH1.SRC_TRANSFER_STEP = srctstep; // TRANSFER_STEP is ignored
                                              // when WRAP occurs.
    DmaRegs.CH1.DST_TRANSFER_STEP = deststep; // TRANSFER_STEP is ignored
                                              // when WRAP occurs.

    EDIS;
}

//
// DMACH1WrapConfig - DMA Channel 1 Wrap size configuration
//
void DMACH1WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                      int16 deswstep)
{
    EALLOW;

    //
    // Set up WRAP registers:
    //
    DmaRegs.CH1.SRC_WRAP_SIZE.bit.WRAPSIZE = srcwsize; // Wrap source address after N bursts
    DmaRegs.CH1.SRC_WRAP_STEP = srcwstep; // Step for source wrap

    DmaRegs.CH1.DST_WRAP_SIZE.bit.WRAPSIZE = deswsize; // Wrap destination address after
                                          // N bursts.
    DmaRegs.CH1.DST_WRAP_STEP = deswstep; // Step for destination wrap

    EDIS;
}

//
// DMACH1ModeConfig - DMA Channel 1 Mode configuration
//
void DMACH1ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                      Uint16 cont, Uint16 synce, Uint16 syncsel,
                      Uint16 ovrinte, Uint16 datasize, Uint16 chintmode,
                      Uint16 chinte)
{
    EALLOW;

    //
    // Set up MODE Register:
    // persel - Source select
    // PERINTSEL - Should be hard coded to channel, above now selects source
    // PERINTE - Peripheral interrupt enable
    // ONESHOT - Oneshot enable
    // CONTINUOUS - Continuous enable
    // OVRINTE - Enable/disable the overflow interrupt
    // DATASIZE - 16-bit/32-bit data size transfers
    // CHINTMODE - Generate interrupt to CPU at beginning/end of transfer
    // CHINTE - Channel Interrupt to  CPU enable
    //
    DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH1 = persel;
    DmaRegs.CH1.MODE.bit.PERINTSEL = 1;
    DmaRegs.CH1.MODE.bit.PERINTE = perinte;
    DmaRegs.CH1.MODE.bit.ONESHOT = oneshot;
    DmaRegs.CH1.MODE.bit.CONTINUOUS = cont;
    DmaRegs.CH1.MODE.bit.OVRINTE = ovrinte;
    DmaRegs.CH1.MODE.bit.DATASIZE = datasize;
    DmaRegs.CH1.MODE.bit.CHINTMODE = chintmode;
    DmaRegs.CH1.MODE.bit.CHINTE = chinte;

    //
    // Clear any spurious flags: interrupt and sync error flags
    //
    DmaRegs.CH1.CONTROL.bit.PERINTCLR = 1;
    DmaRegs.CH1.CONTROL.bit.ERRCLR = 1;

    //
    // Initialize PIE vector for CPU interrupt:
    // Enable DMA CH1 interrupt in PIE
    //
    PieCtrlRegs.PIEIER7.bit.INTx1 = 1;

    EDIS;
}

//
// StartDMACH1 - This function starts DMA Channel 1.
//
void StartDMACH1(void)
{
    EALLOW;
    DmaRegs.CH1.CONTROL.bit.RUN = 1;
    EDIS;
}

//
// DMACH2AddrConfig - DMA Channel 2 Address Configuration
//
void DMACH2AddrConfig(volatile Uint16 *DMA_Dest,volatile Uint16 *DMA_Source)
{
    EALLOW;

    //
    // Set up SOURCE address:
    //
    DmaRegs.CH2.SRC_BEG_ADDR_SHADOW = (Uint32)DMA_Source;   // Point to
                                                            // beginning of
                                                            // source buffer.
    DmaRegs.CH2.SRC_ADDR_SHADOW =     (Uint32)DMA_Source;

    //
    // Set up DESTINATION address:
    //
    DmaRegs.CH2.DST_BEG_ADDR_SHADOW = (Uint32)DMA_Dest;  // Point to beginning
                                                         // of destination
                                                         // buffer.
    DmaRegs.CH2.DST_ADDR_SHADOW =     (Uint32)DMA_Dest;

    EDIS;
}

//
// DMACH2BurstConfig - DMA Channel 2 Burst size configuration
//
void DMACH2BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep)
{
    EALLOW;

    //
    // Set up BURST registers:
    //
    DmaRegs.CH2.BURST_SIZE.all = bsize;     // Number of words(X-1) x-ferred in
                                            // a burst.
    DmaRegs.CH2.SRC_BURST_STEP = srcbstep;  // Increment source addr between
                                            // each word x-ferred.
    DmaRegs.CH2.DST_BURST_STEP = desbstep;  // Increment dest addr between each
                                            // word x-ferred.

    EDIS;
}

//
// DMACH2TransferConfig - DMA Channel 2 Transfer size Configuration
//
void DMACH2TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep)
{
    EALLOW;

    //
    // Set up TRANSFER registers:
    //
    DmaRegs.CH2.TRANSFER_SIZE.bit.TRANSFERSIZE = tsize;   // Number of bursts per transfer,
                                              // DMA interrupt will occur after
                                              // completed transfer.
    DmaRegs.CH2.SRC_TRANSFER_STEP = srctstep; // TRANSFER_STEP is ignored when
                                              // WRAP occurs.
    DmaRegs.CH2.DST_TRANSFER_STEP = deststep; // TRANSFER_STEP is ignored when
                                              // WRAP occurs.

    EDIS;
}

//
// DMACH2WrapConfig - DMA Channel 2 Wrap size configuration
//
void DMACH2WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                      int16 deswstep)
{
    EALLOW;

    //
    // Set up WRAP registers:
    //
    DmaRegs.CH2.SRC_WRAP_SIZE.bit.WRAPSIZE = srcwsize; // Wrap source address after N bursts
    DmaRegs.CH2.SRC_WRAP_STEP = srcwstep; // Step for source wrap

    DmaRegs.CH2.DST_WRAP_SIZE.bit.WRAPSIZE = deswsize; // Wrap destination address after
                                          // N bursts.
    DmaRegs.CH2.DST_WRAP_STEP = deswstep; // Step for destination wrap

    EDIS;
}

//
// DMACH2ModeConfig - DMA Channel 2 Mode configuration
//
void DMACH2ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                      Uint16 cont, Uint16 synce, Uint16 syncsel,
                      Uint16 ovrinte, Uint16 datasize, Uint16 chintmode,
                      Uint16 chinte)
{
    EALLOW;

    //
    // Set up MODE Register:
    // persel - Source select
    // PERINTSEL - Should be hard coded to channel, above now selects source
    // PERINTE - Peripheral interrupt enable
    // ONESHOT - Oneshot enable
    // CONTINUOUS - Continuous enable
    // OVRINTE - Enable/disable the overflow interrupt
    // DATASIZE - 16-bit/32-bit data size transfers
    // CHINTMODE - Generate interrupt to CPU at beginning/end of transfer
    // CHINTE - Channel Interrupt to  CPU enable
    //
    DmaClaSrcSelRegs.DMACHSRCSEL1.bit.CH2 = persel;
    DmaRegs.CH2.MODE.bit.PERINTSEL = 2;
    DmaRegs.CH2.MODE.bit.PERINTE = perinte;
    DmaRegs.CH2.MODE.bit.ONESHOT = oneshot;
    DmaRegs.CH2.MODE.bit.CONTINUOUS = cont;
    DmaRegs.CH2.MODE.bit.OVRINTE = ovrinte;
    DmaRegs.CH2.MODE.bit.DATASIZE = datasize;
    DmaRegs.CH2.MODE.bit.CHINTMODE = chintmode;
    DmaRegs.CH2.MODE.bit.CHINTE = chinte;

    //
    // Clear any spurious flags: Interrupt flags and sync error flags
    //
    DmaRegs.CH2.CONTROL.bit.PERINTCLR = 1;
    DmaRegs.CH2.CONTROL.bit.ERRCLR = 1;

    //
    // Initialize PIE vector for CPU interrupt:
    // Enable DMA CH2 interrupt in PIE
    //
    PieCtrlRegs.PIEIER7.bit.INTx2 = 1;

    EDIS;
}

//
// StartDMACH2 - This function starts DMA Channel 2.
//
void StartDMACH2(void)
{
    EALLOW;
    DmaRegs.CH2.CONTROL.bit.RUN = 1;
    EDIS;
}

//
// NOTE:
// Following functions are required for EMIF as the address is out of
// 22bit range
//

//
// DMACH1AddrConfig32bit - DMA Channel 1 address configuration for 32bit
//
void DMACH1AddrConfig32bit(volatile Uint32 *DMA_Dest,
                           volatile Uint32 *DMA_Source)
{
    EALLOW;

    //
    // Set up SOURCE address:
    //
    DmaRegs.CH1.SRC_BEG_ADDR_SHADOW = (Uint32)DMA_Source; // Point to beginning
                                                          // of source buffer
    DmaRegs.CH1.SRC_ADDR_SHADOW =     (Uint32)DMA_Source;

    //
    // Set up DESTINATION address:
    //
    DmaRegs.CH1.DST_BEG_ADDR_SHADOW = (Uint32)DMA_Dest;  // Point to beginning
                                                         // of destination
                                                         // buffer
    DmaRegs.CH1.DST_ADDR_SHADOW =     (Uint32)DMA_Dest;

    EDIS;
}

//
// DMACH2AddrConfig32bit - DMA Channel 2 address configuration for 32bit
//
void DMACH2AddrConfig32bit(volatile Uint32 *DMA_Dest,
                           volatile Uint32 *DMA_Source)
{
    EALLOW;

    //
    // Set up SOURCE address:
    //
    DmaRegs.CH2.SRC_BEG_ADDR_SHADOW = (Uint32)DMA_Source; // Point to beginning
                                                          // of source buffer
    DmaRegs.CH2.SRC_ADDR_SHADOW =     (Uint32)DMA_Source;

    //
    // Set up DESTINATION address:
    //
    DmaRegs.CH2.DST_BEG_ADDR_SHADOW = (Uint32)DMA_Dest;  // Point to beginning
                                                         // of destination
                                                         // buffer
    DmaRegs.CH2.DST_ADDR_SHADOW =     (Uint32)DMA_Dest;

    EDIS;
}

//
// End of file
//
