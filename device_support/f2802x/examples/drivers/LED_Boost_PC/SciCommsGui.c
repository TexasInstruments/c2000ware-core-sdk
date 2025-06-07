//============================================================================
//
// FILE:    SciCommsGui.c
//
// TITLE:   GP Comms kernel as an interface to external GUI
// 
// Version: 22 April 2009 - Release 1.2 - Internal Release (BRL)
//============================================================================
// $TI Release:  $
// $Release Date:  $
// $Copyright:
// Copyright (C) 2009-2025 Texas Instruments Incorporated - http://www.ti.com/
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
//============================================================================

//
// Included Files
//
#include "DSP28x_Project.h"

//
// Defines
//
#define PktSize             6
#define CmdNumber           16
#define MAX_CMD_NUM         8

//
// Function prototypes for Command RECEIVE State machine
//
void GetCmdByte(void);
void EchoCmdByte(void);
void GetSizeByte(void);
void EchoSizeByte(void);
void GetDataByte(void);
void EchoDataByte(void);
void PackWord(void);
void PackArray(void);
void CmdInterpreter(void);

//
// Function prototypes for Command Interpreter and dispatcher
//
void LifePulseTsk(void);        // 0
void TextSet(void);             // 1
void ButtonSet(void);           // 2
void SliderSet(void);           // 3
void VariableGet(void);         // 4
void ArrayGet(void);            // 5
void DataGet(void);             // 6
void SpareTsk07(void);          // 7
void SpareTsk08(void);          // 8

void SendData(void);

//
// Variable declarations
//
void (*RcvTaskPointer)(void);      // State pointer for Command Packet Receive

//
// Array of pointers to Function (i.e. tasks)
//
void (*CmdDispatcher[CmdNumber])(void);

extern int *varSetTxtList[];
extern int *varSetBtnList[];
extern int *varSetSldrList[];
extern int *varGetList[];
extern int *arrayGetList[];
extern int *dataGetList[];

extern int16 CommsOKflg;
extern int16 SerialCommsTimer;

Uint16 LowByteFlag;
Uint16 SendTaskPtr;
Uint16 RxChar;
Uint16 RxWord;
Uint16 CmdPacket[PktSize];
Uint16 TaskDoneFlag;
Uint16 NumWords;
Uint16 wordsLeftToGet;

Uint16 dataOut;
int16 *memDataPtr;

int16  RcvTskPtrShdw;   // for debug

int16   delayer;

int16   MemGetPtr;
Uint32  MemGetAddress;
int16   MemGetAmount;

Uint32 Temp;

uint16_t test123;

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
    SciaRegs.SCICTL2.bit.RXBKINTENA =0;
    SciaRegs.SCIHBAUD    =0x0000;

   #if DSP2833x_DEVICE_H
    //SciaRegs.SCILBAUD = 0x0079;      // 79h = 38.4Kbaud @ LSPCLK = 150/4 MHz
    SciaRegs.SCILBAUD = 0x0050;        // 50h = 57.6Kbaud @ LSPCLK = 150 /4 MHz
    //SciaRegs.SCILBAUD = 0x0028;      // 28h = 115.2Kbaud @ LSPCLK = 150/4 MHz
    #elif DSP2802x_DEVICE_H || DSP2803x_DEVICE_H
    //SciaRegs.SCILBAUD = 0x0031;       // 31h = 38.4Kbaud @ LSPCLK = 60/4 MHz
    SciaRegs.SCILBAUD = 0x0020;         // 20h = 57.6Kbaud @ LSPCLK = 60/4 MHz
    //SciaRegs.SCILBAUD = 0x0010;       // 10h = 115.2Kbaud @ LSPCLK = 60/4 MHz
    #else       // F280x or F2804x
    //SciaRegs.SCILBAUD  =0x00A2;      // A2h = 19.2Kbaud @ LSPCLK = 100/4 MHz
    //SciaRegs.SCILBAUD  =0x0050;      // 50h = 38.4Kbaud @ LSPCLK = 100/4 MHz
    SciaRegs.SCILBAUD = 0x0035;        // 35h = 57.6Kbaud @ LSPCLK = 100/4 MHz
    //SciaRegs.SCILBAUD = 0x001B;      // 1Bh = 115.2Kbaud @ LSPCLK = 100/4 MHz
    #endif

    SciaRegs.SCICTL1.all =0x0023;       // Relinquish SCI from Reset 

    //SciaRegs.SCIFFTX.all=0xE040;      // ENable FIFO enhancement
    SciaRegs.SCIFFTX.all=0x8040;        // DISable FIFO enhancement
    SciaRegs.SCIFFRX.all=0x204f;
    SciaRegs.SCIFFCT.all=0x0;
    SciaRegs.SCIPRI.bit.SOFT=0x0;
    SciaRegs.SCIPRI.bit.FREE=0x1;

    //
    // Initialize the CmdPacket Rcv Handler state machine ptr
    //
    RcvTaskPointer = &GetCmdByte;
    RcvTskPtrShdw = 1;           // DEBUG
    SendTaskPtr = 0;             // Init to 1st state
    LowByteFlag = 1;             // Start with LSB during Byte-to-Word packing

    dataOut = 0;
    *memDataPtr = 0;

    RcvTskPtrShdw = 0;           // for debug

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
    
    //
    // init all dispatch Tasks
    //
    CmdDispatcher[0] = LifePulseTsk;             
    CmdDispatcher[1] = TextSet;                  
    CmdDispatcher[2] = ButtonSet;                
    CmdDispatcher[3] = SliderSet;                
    CmdDispatcher[4] = VariableGet;              
    CmdDispatcher[5] = ArrayGet;                 
    CmdDispatcher[6] = DataGet;                  
    CmdDispatcher[7] = SpareTsk07;               
    CmdDispatcher[8] = SpareTsk08;               
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
// GetCmdByte - 
//
void GetCmdByte(void) // Task 1
{
    if (SciaRegs.SCIRXST.bit.RXRDY == 1)   // check if a char has been received
    {
        RxChar = SciaRegs.SCIRXBUF.all;
        RcvTaskPointer = &EchoCmdByte;      // point to next state
        SerialCommsTimer = 0;
        //RcvTskPtrShdw = 2;                // DEBUG
        EchoCmdByte();
    }                                                                      

    //
    // ~2 s timeout
    //
    else if (SciaRegs.SCIRXST.bit.BRKDT == 1 || SerialCommsTimer > 2500)
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
        RcvTaskPointer = &GetCmdByte;       // go back and wait for new CMD                       
    }
}

//
// EchoCmdByte - Task 2
//
void EchoCmdByte(void) 
{
    if(SciaRegs.SCICTL2.bit.TXRDY == 1) // is TXBUF empty ?, i.e. TXRDY = 1
    {
        SciaRegs.SCITXBUF=RxChar;       // if yes, echo back the received char
        CmdPacket[0] = RxChar;
        RcvTaskPointer = &GetSizeByte;
        //RcvTskPtrShdw = 3             // DEBUG
        //RcvTaskPointer = &GetCmdByte; // Un-comment for simple echo test
        SerialCommsTimer = 0;           // Reset Time-out timer
    }
}

//
// GetSizeByte - Task 3
//
void GetSizeByte(void) 
{
    if (SciaRegs.SCIRXST.bit.RXRDY == 1)  // check if a char has been received
    {
        RxChar = SciaRegs.SCIRXBUF.all;

        RcvTaskPointer = &EchoSizeByte;  // point to next state
        //RcvTskPtrShdw = 4;             // DEBUG
        EchoSizeByte();
    }

    else if (SerialCommsTimer > 1000)   // 1000*1mS = 1.0 sec timeout
    {
        CommsOKflg = 0;
        RcvTaskPointer = &GetCmdByte;   // Abort, go back wait for new CMD
        SerialCommsTimer = 0;
    }
}

//
// EchoSizeByte - Task 4
//
void EchoSizeByte(void)
{
    if(SciaRegs.SCICTL2.bit.TXRDY == 1)   // is TXBUF empty ?, i.e. TXRDY = 1
    {
        SciaRegs.SCITXBUF=RxChar;        // if yes, echo back the received char
        CmdPacket[1] = RxChar;
        RcvTaskPointer = &GetDataByte;
        //RcvTskPtrShdw = 5;             // DEBUG
        //RcvTaskPointer = &GetCmdByte;  // Un-comment for Test
        SerialCommsTimer = 0;            // Reset Time-out timer
    }
}

//
// GetDataByte - Task 5
//
void GetDataByte(void)
{
    if (SciaRegs.SCIRXST.bit.RXRDY == 1)  // check if a char has been received
    {
        RxChar = SciaRegs.SCIRXBUF.all;
        RcvTaskPointer = &EchoDataByte;   // point to next state
        //RcvTskPtrShdw = 6;              // DEBUG
        EchoDataByte();             
    }

    else if (SerialCommsTimer > 500)      // 1000*1mS = 1 sec timeout
    {
        CommsOKflg = 0;
        RcvTaskPointer = &GetCmdByte;     // Abort, go back wait for new CMD
        SerialCommsTimer = 0;
    }
}

//
// EchoDataByte - Task 6
//
void EchoDataByte(void)
{
    if(SciaRegs.SCICTL2.bit.TXRDY == 1)  // is TXBUF empty ?, i.e. TXRDY = 1
    {
        SciaRegs.SCITXBUF=RxChar;        // if yes, echo back the received char
        RcvTaskPointer = &PackWord;
        //RcvTskPtrShdw = 7;             // DEBUG
    }
}

//
// PackWord - expects LSB first then MSB (Task 7)
//
void PackWord(void)
{
    if(LowByteFlag == 1)
    { 
        RxWord = RxChar;
        LowByteFlag = 0;
        RcvTaskPointer = &GetDataByte;
        //RcvTskPtrShdw = 5;                // DEBUG
        GetDataByte();
    }
    else
    {
        RxWord = RxWord | (RxChar<<8);
        LowByteFlag = 1;
        CmdPacket[2] = RxWord;              // store data in packet
        RcvTaskPointer = &CmdInterpreter;
        //RcvTskPtrShdw = 8;                // DEBUG
        TaskDoneFlag = 0;                   // indicate new task underway   
    }
}

//
// CmdInterpreter - Task 8
//
void CmdInterpreter(void)
{
    if (TaskDoneFlag == 0)
    {
        (*CmdDispatcher[ CmdPacket[0] ] )();    // dispatch Task                    
    }

    //
    // Incase Task never finishes 
    //
    if (SerialCommsTimer > 2500)            // 2500*1mS = 2.5 sec timeout
    {
        CommsOKflg = 0;
        RcvTaskPointer = &GetCmdByte;       // Abort, go back wait for new CMD
        SerialCommsTimer = 0;
    }
    if (TaskDoneFlag == 1)
    {
        RcvTaskPointer = &GetCmdByte;
        //RcvTskPtrShdw = 1;                // DEBUG
    }
}

//
// LifePulseTsk - Slave Tasks commanded by Host CmdPacket[0] = 0
//
void LifePulseTsk(void)
{
    if (CmdPacket[2]==0x0000 && CmdPacket[1]==0x00)  //LED2-ON
    {
        #if DSP2802x_DEVICE   
        GpioDataRegs.GPASET.bit.GPIO12=1;       
        #else
        GpioDataRegs.GPASET.bit.GPIO31=1;
        #endif
    }
    if (CmdPacket[2]==0x0001 && CmdPacket[1]==0x00)   //LED2-OFF
    {
        #if DSP2802x_DEVICE
        GpioDataRegs.GPACLEAR.bit.GPIO12=1;
        #else
        GpioDataRegs.GPACLEAR.bit.GPIO31=1;
        #endif      
    }
    if (CmdPacket[2]==0x0002 && CmdPacket[1]==0x00)  //LED2-Toggle
    {
        #if DSP2802x_DEVICE
        GpioDataRegs.GPATOGGLE.bit.GPIO12=1;
        #else
        GpioDataRegs.GPATOGGLE.bit.GPIO31=1;
        #endif
    }

    CommsOKflg = 1;
    SerialCommsTimer = 0;
    TaskDoneFlag = 1;
}

//
// TextSet - CmdPacket[0] = 1
//
void TextSet(void)
{   
    *varSetTxtList[CmdPacket[1]] = CmdPacket[2];

    TaskDoneFlag = 1; // indicate Task execution is complete
}

//
// ButtonSet - CmdPacket[0] = 2
//
void ButtonSet(void)
{
    *varSetBtnList[CmdPacket[1]] = CmdPacket[2];

    TaskDoneFlag = 1; // indicate Task execution is complete
}

//
// SliderSet - CmdPacket[0] = 3
//
void SliderSet(void)
{
    *varSetSldrList[CmdPacket[1]] = CmdPacket[2];

    TaskDoneFlag = 1; // indicate Task execution is complete
}

//
// VariableGet - CmdPacket[0] = 4
//
void VariableGet(void)
{
    SendData();
}

//
// ArrayGet - Send a Uint16 array one element at a time. CmdPacket[0] = 5
//
void ArrayGet(void)
{
    SendData(); 
}

//
// DataGet - CmdPacket[0] = 6
//
void DataGet(void)
{
    switch(MemGetPtr)
    {
        case 0:
            MemGetAddress = CmdPacket[2];
            MemGetPtr = 1;

            wordsLeftToGet = 1;
            SendTaskPtr = 1;
            TaskDoneFlag = 1;
            break;

        case 1:
            Temp = CmdPacket[2];
            MemGetAddress = MemGetAddress + (Temp<<16);
            memDataPtr = (int16*)MemGetAddress;
            dataOut = *memDataPtr;      
            SendData();     

            if(TaskDoneFlag == 1)
            {
                MemGetPtr = 0;
            }
            break;
        }

    //TaskDoneFlag = 1;     // indicate Task execution is complete
}

//
// SpareTsk07 - CmdPacket[0] = 7
//
void SpareTsk07(void)
{
    TaskDoneFlag = 1;       // indicate Task execution is complete
}

//
// SpareTsk08 - CmdPacket[0] = 8
//
void SpareTsk08(void)
{
    TaskDoneFlag = 1;       // indicate Task execution is complete
}

//
// SendData - 
//
void SendData(void)
{
    switch(SendTaskPtr)
    {
        case 0:  //initialization 
            if(CmdPacket[0] == 0x04)
            {
                memDataPtr = (int16 *) varGetList[CmdPacket[1]];
            }
            else
            {
                memDataPtr = (int16 *) arrayGetList[CmdPacket[1]];
            }
            
            dataOut = *memDataPtr;
            wordsLeftToGet = CmdPacket[2];
            //
            // Note that case 0 rolls into case 1 (no break)
            //

        case 1:  //send LSB
            if(wordsLeftToGet > 0)
            {
                if (SciaRegs.SCICTL2.bit.TXRDY == 1)
                {
                    SciaRegs.SCITXBUF = dataOut & 0x000000FF;
                    SendTaskPtr = 2;
                }
                else
                {
                    TaskDoneFlag = TaskDoneFlag;
                    break;
                }
            }
            else
            {
                SendTaskPtr = 0;
                TaskDoneFlag = 1;
                break;
            }       

        case 2: //send MSB
            if (SciaRegs.SCICTL2.bit.TXRDY == 1)
            {
                SciaRegs.SCITXBUF = (dataOut>>8 & 0x000000FF);

                memDataPtr = memDataPtr + 1;
                dataOut = *memDataPtr;
                wordsLeftToGet = wordsLeftToGet - 1;
                SendTaskPtr = 1;
            }
            break;
    }
}

//
// End of File
//

