//###########################################################################
//
// FILE:   f2802x_examples/LED_Boost_CapTouch/SciCommsGuiCapTouchInt.c
//
// TITLE:  Interrupt driven SCI driver and CapTouch command processor
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2023 Texas Instruments Incorporated - http://www.ti.com/
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
#include "DSP28x_Project.h"

#include "IQmathLib.h"

//
// Defines
//
#define    PktSize                6
#define    CmdNumber            16
#define    MAX_CMD_NUM            8

typedef struct
{
    _iq15 qHue;
    _iq15 qSaturation;
    _iq15 qValue;        
    
}tHSV;

//
// Function prototypes for Command RECEIVE State machine
// 
void GetFirstByte(void);
void GetSecondByte(void);
void CmdInterpreter(void);
void CmdInspector(void);

void SendData(void);

//
// Variable declarations
//
void (*RcvTaskPointer)(void);       // State pointer for Command Packet Receive

//
// Array of pointers to Function (i.e. tasks)
//
void (*CmdDispatcher[CmdNumber])(void);    

//
// Globals
//
extern int16 ChannelEnable1;
extern int16 ChannelEnable2;
extern int16 ChannelEnable3;
extern int16 AutoColor;
extern int16 EnableAll;
extern int16 StopAll;
extern tHSV gHSV;

extern int16 CommsOKflg, SerialCommsTimer;

Uint16    LowByteFlag, SendTaskPtr;
Uint16    RxChar, RxWord;
Uint16    CmdPacket[PktSize];
Uint16    TaskDoneFlag, NumWords, wordsLeftToGet;

Uint16 dataOut;
int16 *memDataPtr;

int16  RcvTskPtrShdw;    // for debug

int16     delayer;

int16    MemGetPtr;
Uint32    MemGetAddress;
int16    MemGetAmount;

Uint32 Temp;

static unsigned char ucByte;
unsigned char pucCommandBuffer[16];
unsigned char ucCommandIndex;

//
// SCIA_Init - 
//
void SCIA_Init()
{    
//
// Note: Assumes Clocks to SCIA are turned on in InitSysCtrl()
// Note: Assumes GPIO pins for SCIA are configured to Primary function    
//
    int j = 0;

    //
    // 1 stop bit,  No loopback, No parity, 8 char bits, async mode, 
    // idle-line protocol
    //
    SciaRegs.SCICCR.all =0x0007;
    
    //
    // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
    //
    SciaRegs.SCICTL1.all =0x0003; 
    SciaRegs.SCICTL2.all =0x0003; 
    SciaRegs.SCICTL2.bit.TXINTENA =0;
    SciaRegs.SCICTL2.bit.RXBKINTENA =1; //Enable RX interrupt
    SciaRegs.SCIHBAUD    =0x0000;

    #if DSP2833x_DEVICE_H
    //SciaRegs.SCILBAUD = 0x0079;      // 79h = 38.4Kbaud @ LSPCLK = 150/4 MHz
    SciaRegs.SCILBAUD = 0x0050;        // 50h = 57.6Kbaud @ LSPCLK = 150 /4 MHz
    //SciaRegs.SCILBAUD = 0x0028;      // 28h = 115.2Kbaud @ LSPCLK = 150/4 MHz
    #elif DSP2802x_DEVICE_H || DSP2803x_DEVICE_H
    SciaRegs.SCILBAUD = 0x00C2;        // C2h = 9.6Kbaud @ LSPCLK = 60/4 MHz
    //SciaRegs.SCILBAUD = 0x0031;      // 31h = 38.4Kbaud @ LSPCLK = 60/4 MHz
    //SciaRegs.SCILBAUD = 0x0020;      // 20h = 57.6Kbaud @ LSPCLK = 60/4 MHz
    //SciaRegs.SCILBAUD = 0x0010;      // 10h = 115.2Kbaud @ LSPCLK = 60/4 MHz
    #else         // F280x or F2804x
    //SciaRegs.SCILBAUD  =0x00A2;      // A2h = 19.2Kbaud @ LSPCLK = 100/4 MHz
    //SciaRegs.SCILBAUD  =0x0050;      // 50h = 38.4Kbaud @ LSPCLK = 100/4 MHz
    SciaRegs.SCILBAUD = 0x0035;        // 35h = 57.6Kbaud @ LSPCLK = 100/4 MHz
    //SciaRegs.SCILBAUD = 0x001B;      // 1Bh = 115.2Kbaud @ LSPCLK = 100/4 MHz
    #endif

    SciaRegs.SCICTL1.all =0x0023;        // Relinquish SCI from Reset 

    //SciaRegs.SCIFFTX.all=0xE040;      // ENable FIFO enhancement
    SciaRegs.SCIFFTX.all=0x8040;        // DISable FIFO enhancement
    SciaRegs.SCIFFRX.all=0x204f;
    SciaRegs.SCIFFCT.all=0x0;
    SciaRegs.SCIPRI.bit.SOFT=0x1;
    SciaRegs.SCIPRI.bit.FREE=0x1;

    //
    // Initialize the CmdPacket Rcv Handler state machine ptr
    //
    RcvTaskPointer = &CmdInterpreter; 
    
    RcvTskPtrShdw = 1;          // DEBUG
    SendTaskPtr = 0;            // Init to 1st state
    LowByteFlag = 1;            // Start with LSB during Byte-to-Word packing

    dataOut = 0;
    *memDataPtr = 0;

    RcvTskPtrShdw = 0;          // for debug

    delayer = 0;

    MemGetPtr = 0;
    MemGetAddress = 0x00000000;
    MemGetAmount = 0;

    //
    // clear Command Packet
    //
    for (j=0; j<PktSize; j++)
    {
        CmdPacket[j] = 0x0;
    }

    j=0;
    
    ucByte = 0;
    ucCommandIndex = 0;            
}

//
// Host Command RECEIVE and DISPATCH State Machine
//

//
// SerialHostComms - SM Entry Point
//
void SerialHostComms()
{        
    (*RcvTaskPointer)();    // Call routine pointed to by state pointer
}

//
// SciISR -
//
interrupt void SciISR(void) // Task 1
{
    //
    // check if a char has been received
    //
    if (SciaRegs.SCIRXST.bit.RXRDY == 1) 
    {
        switch(ucByte)
        {
            case 0:
                RxChar = (SciaRegs.SCIRXBUF.all << 8) & 0xFF00;
                SerialCommsTimer = 0;
                ucByte++;
                break;
            case 1:
                RxChar |= SciaRegs.SCIRXBUF.all;
                SerialCommsTimer = 0;
                ucByte = 0;
                //
                // Is there space in the command buffer
                //
                if(ucCommandIndex < 15)
                {
                    pucCommandBuffer[ucCommandIndex++] = RxChar;
                }
        }
    }

    //
    // ~2 s timeout
    //
    else if (SciaRegs.SCIRXST.bit.BRKDT == 1 || SerialCommsTimer > 30)
    {   
        //
        // If break detected or serialport times out, reset SCI
        // Needed by some serialports when code is run with an emulator  
        //
        
        //
        // 1 stop bit,  No loopback, No parity,8 char bits, async mode, 
        // idle-line protocol
        //
        SciaRegs.SCICCR.all =0x0007;              
        
        //
        // enable TX, RX, internal SCICLK, Disable RX ERR, SLEEP, TXWAKE
        //
        SciaRegs.SCICTL1.all =0x0003;
        
        SciaRegs.SCICTL2.all =0x0000;

        SciaRegs.SCICTL1.all =0x0023;        // Relinquish SCI from Reset        

        asm(" RPT#8 || NOP");

        SendTaskPtr = 0;                    // Init to 1st state    
        SerialCommsTimer = 0;
                                                                      
        CommsOKflg = 0;                     
    }
    
    //
    // Acknowledge Interrupt
    //
    PieCtrlRegs.PIEACK.bit.ACK9 = 1;
}

//
// CmdInterpreter - Task 3
//
void CmdInterpreter(void)
{
    if (SerialCommsTimer > 30)        // 1000*1mS = 1.0 sec timeout
    {
        ucByte = 0;
        SerialCommsTimer = 0;
    }
    
    if (ucCommandIndex)
    {
        switch(pucCommandBuffer[ucCommandIndex-1])
        {
            //
            // Wakeup
            //
            case 0xBEEF:
                asm(" nop");
                break;
            
            //
            // Sleep
            //
            case 0xDEAD:
                asm(" nop");
                break;
            
            // 
            // Center Button Press
            // Enable/Disable LEDs
            //
            case 0x8080:
                if(ChannelEnable1 && ChannelEnable2 && ChannelEnable3)
                {
                    StopAll = 1;
                }
                else
                {
                    EnableAll = 1;
                    AutoColor = 1;
                }
                break;
            
            //
            // Gesture Stop
            //
            case 0xFBFB:
                asm(" nop");
                break;
            
            //
            // Packet needs more inspection
            //
            default:
                CmdInspector();
                break;
        }            
        ucCommandIndex--;    
    }
    
    //
    // Incase Task never finishes 
    //
    if (SerialCommsTimer > 30)            // 2500*1mS = 2.5 sec timeout
    {
        ucByte = 0;
        SerialCommsTimer = 0;
    }
}

//
// CmdInspector - 
//
void CmdInspector(void)
{
    if((RxChar & 0x3030) == 0x3030)
    {
        //
        // Wheel Touch
        //        
    }
    else if((RxChar & 0xFC20) == 0xFC20)
    {
        //
        // Gesture Start
        //
    }
    else if((RxChar & 0x0020) == 0x0020)
    {
        //
        // Gesture and End Position
        //
        if(RxChar & 0x8000)
        {
            //
            // If counter clockwise, decrement    
            //
            gHSV.qHue = gHSV.qHue - 
                        (_IQ15mpy(_IQ15((RxChar & 0x7F00) >> 8), _IQ15(10)));
            
            //
            // check for overflow and correct
            //
            if(_IQ15int(gHSV.qHue) < 0)
            {
                gHSV.qHue = _IQ15(360) - _IQ15abs(gHSV.qHue);
            }
        }
        else
        {
            //
            // If clockwise, increment
            //
            gHSV.qHue = gHSV.qHue + 
                        (_IQ15mpy(_IQ15((RxChar & 0x7F00) >> 8), _IQ15(10)));
                            
            //
            // check for overflow and correct
            //
            if(_IQ15int(gHSV.qHue) > 360)
            {
                gHSV.qHue = gHSV.qHue - _IQ15(360);
            }
        }
        
    }
    else
    {
        //
        // Invalid Command    
        //
    }   
}

//
// End of File
//

