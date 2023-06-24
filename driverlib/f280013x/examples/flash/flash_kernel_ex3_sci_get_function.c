//###########################################################################
//
// FILE:    flash_kernel_ex3_sci_get_function.c
//
// TITLE:   SCI Kernel Routines
//! \addtogroup driver_example_list
//!
//! Functions:
//!
//!     uint32_t sciBoot(void)
//!     void sciaInit(void)
//!     uint32_t sciaGetWordData(void)
//
//###########################################################################
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
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
// Includes
//
#include "cpu1bootrom.h"
#include "cpu1brom_boot_modes.h"
#include "flash_kernel_ex3_commands.h"
#include "flash_kernel_ex3_erase.h"
#include "flash_kernel_ex3_verify.h"
#include "driverlib.h"
#include "device.h"
#include "stdint.h"
#include "sci.h"
#include "sysctl.h"
#include "device.h"
#include "gpio.h"
#include "dcsm.h"

//
// Globals
//
typedef struct
{
   uint16_t status;
   uint32_t address;
   uint16_t flashAPIError;
   uint32_t flashAPIFsmStatus;
}  StatusCode;
StatusCode statusCode;

uint16_t checksum;

//
// getWordData is a pointer to the function that interfaces to the peripheral.
// Each loader assigns this pointer to it's particular getWordData function.
//
extern uint16fptr getWordData;


//
// Function Prototypes (Private)
//
uint16_t sciaGetWordData(void);
uint16_t sciaGetOnlyWordData(void);
void sendACK(void);
void sendNAK(void);
inline uint16_t sciaGetACK(void);
void sciaFlush(void); 
void sciaInit(uint32_t  BootMode);
void sciPinmuxOption(uint32_t BootMode);
uint32_t sciGetFunction(uint32_t  BootMode);
uint16_t sciGetPacket(uint16_t* length, uint16_t* data);
uint16_t sciSendPacket(uint16_t command, uint16_t status, uint16_t length,
                       uint16_t* data1, uint16_t flashAPIError, uint16_t* data2);
void sciSendWord(uint16_t word);
void sciSendChecksum(void);

//
// Function Prototypes (External)
//
extern uint32_t sciBootApplication(uint32_t BootMode);
extern void sharedErase(uint32_t sectors1, uint32_t sectors2);
extern void copyData(void);
extern void verifyData(void);
extern uint32_t getLongData(void);
extern void readReservedFn(void);

//
// sciGetFunction -  This function first initializes SCIA and performs
//                   an autobaud lock. It contains a while loop waiting on
//                   commands from the host.  It processes each
//                   command and sends a response except for Run and
//                   Reset commands.  On Run the kernel exits and branches
//                   to the Entry Point.  On Reset, the kernel exits the
//                   while loop and does a WatchDog Time-out.
//
uint32_t sciGetFunction(uint32_t BootMode)
{
    volatile uint32_t EntryAddr;
    uint16_t command;
    uint16_t data[10]; // 16*10 = 128 + 32
    uint16_t length;

    //
    // Assign GetWordData to the SCI-A version of the
    // function. GetWordData is a pointer to a function.
    //
    getWordData = sciaGetWordData;

    //
    // Initialize the SCI-A port for communications
    // with the host.
    //
    sciaInit(BootMode);

    //
    // driverlib autobaud lock:
    //
    SCI_lockAutobaud(SCIA_BASE);

    //
    // echo back the autoBaud success, driverlib.
    //
    uint16_t byteData = SCI_readCharBlockingNonFIFO(SCIA_BASE);
    SCI_writeCharBlockingNonFIFO(SCIA_BASE, byteData);

    //
    // get user command through console.
    //
    command = sciGetPacket(&length, data);

    while(command != RESET_CPU1)
    {
        //
        // Reset the statusCode.
        //
        statusCode.status = NO_ERROR;
        statusCode.address = 0x12345678;
        statusCode.flashAPIError = NO_ERROR;
        statusCode.flashAPIFsmStatus = 0;
        checksum = 0;

        //
        // The LDFU build configurations only support the Live DFU command;
        // the Live DFU command is not included in other build configurations
        //
#ifdef LIVE_UPDATE

           //
           // Live DFU
           //
           if (command == LIVE_DFU_CPU1)
           {
               liveDFU();
           }
#endif

#ifndef LIVE_UPDATE
        //
        // CPU1_UNLOCK_Z1
        //
        if(command == CPU1_UNLOCK_Z1)
        {
            //
            // driverlib struct for csmKey.
            //
            DCSM_CSMPasswordKey psCMDKey;

            psCMDKey.csmKey0 = (uint32_t)data[0] | ((uint32_t)data[1] << 16);
            psCMDKey.csmKey1 = (uint32_t)data[2] | ((uint32_t)data[3] << 16);
            psCMDKey.csmKey2 = (uint32_t)data[4] | ((uint32_t)data[5] << 16);
            psCMDKey.csmKey3 = (uint32_t)data[6] | ((uint32_t)data[7] << 16);


            //
            // Unlock the zone 1, driverlib.
            //
            DCSM_unlockZone1CSM(&psCMDKey);

            //
            // check if it is unlocked.
            //
            if(DCSM_getZone1CSMSecurityStatus() == DCSM_STATUS_LOCKED) {
                statusCode.status = UNLOCK_ERROR;
            }

        }

        //
        // CPU1_UNLOCK_Z2
        //
        else if(command == CPU1_UNLOCK_Z2)
        {
            //
            // driver lib implementation of csmKeys
            //
            DCSM_CSMPasswordKey psCMDKey;

            psCMDKey.csmKey0 = (uint32_t) data[0] | ((uint32_t) data[1] << 16);
            psCMDKey.csmKey1 = (uint32_t) data[2] | ((uint32_t) data[3] << 16);
            psCMDKey.csmKey2 = (uint32_t) data[4] | ((uint32_t) data[5] << 16);
            psCMDKey.csmKey3 = (uint32_t) data[6] | ((uint32_t) data[7] << 16);

            //
            // Unlock the zone 2, driverlib.
            //
            DCSM_unlockZone2CSM(&psCMDKey);

            //
            // check if zone 2 is unlocked.
            //
            if (DCSM_getZone2CSMSecurityStatus() == DCSM_STATUS_LOCKED)
            {
                statusCode.status = UNLOCK_ERROR;
            }
        }

        //
        // DFU_CPU1
        //
        else if(command == DFU_CPU1)
        {
            //
            // loads application into CPU1 FLASH
            //
            EntryAddr = sciBootApplication(BootMode);
            if(statusCode.status == NO_ERROR)
            {
                statusCode.address = EntryAddr;
            }
        }

        //
        // ERASE_CPU1
        //
        else if(command == ERASE_CPU1)
        {
            uint32_t sectors_0to31 = (uint32_t)(((uint32_t)data[1] << 16) |
                    (uint32_t)data[0]);
            uint32_t sectors_32to127 = (uint32_t)data[2];
            
            sharedErase(sectors_0to31, sectors_32to127);
            
        }

        //
        // VERIFY_CPU1
        //
        else if(command == VERIFY_CPU1)
        {
            verifyData();
        }

        //
        // RUN_CPU1
        //
        else if(command == RUN_CPU1)
        {
            EntryAddr = (uint32_t)(((uint32_t)data[1] << 16) | (uint32_t)data[0]);
            return(EntryAddr);
        }

        //
        // COMMAND_ERROR
        //
        else
        {
            statusCode.status = COMMAND_ERROR;
        }

        //
        // Send the packet and if NAK send again.
        //
        while(sciSendPacket(command, statusCode.status, 12,
                           (uint16_t*)&statusCode.address, statusCode.flashAPIError,
                           (uint16_t*)&statusCode.flashAPIFsmStatus)){}
#endif
        //
        // Get next Packet
        //
        command = sciGetPacket(&length, data); //get next packet
    }

    //
    // Reset with WatchDog Timeout
    //
    EALLOW;

    //
    // driverlib, Watchdog reset enable = WDENINT->0 and WDOVERRIDE->0
    //
     SysCtl_enableWatchdogReset();

    //
    // enable the Watchdog, driverlib; // same as HWREGH(WD_BASE + SYSCTL_O_WDCR) = SYSCTL_WD_CHKBITS;
    //
    SysCtl_enableWatchdog();
    EDIS;

    while(1){}
}


//
// sciSendPacket -  Sends a Packet to the host which contains
//                  status in the data and address.  It sends the
//                  statusCode global variable contents.  It then waits
//                  for an ACK or NAK from the host.
//
uint16_t sciSendPacket(uint16_t command, uint16_t status, uint16_t length,
                      uint16_t* data1, uint16_t flashAPIError, uint16_t* data2)
{
    int i;

    sciaFlush();
    DEVICE_DELAY_US(100000);
    sciSendWord(0x1BE4);
    sciSendWord(length);

    checksum = 0;
    sciSendWord(command);
    sciSendWord(status);

    for(i = 0; i < 2; i++)
    {
        sciSendWord(*(data1 + i));
    }

    sciSendWord(flashAPIError);

    for(i = 0; i < 2; i++)
    {
        sciSendWord(*(data2 + i));
    }
    sciSendChecksum();
    sciSendWord(0xE41B);

    //
    // Receive an ACK or NAK
    //
    return sciaGetACK();
}

//
// sciaGetACK - Gets 1-byte ACK from the host.
//
inline uint16_t sciaGetACK()
{
    uint16_t wordData;

    //
    // wait for and read a char blocking nonFIFO, driverlib.
    //
    wordData = SCI_readCharBlockingNonFIFO(SCIA_BASE);

    if(wordData != ACK)
    {
        return(1);
    }

    return(0);
}

//
// sciSendChecksum - Sends the Global checksum value
//
void sciSendChecksum()
{
    //
    // wait for SCIA_TX to be free and write LSB of checksum to it.
    //
    SCI_writeCharBlockingNonFIFO(SCIA_BASE, (checksum & 0xFF));

    sciaFlush();
    sciaGetACK();

    //
    // wait for SCIA_TX to be free and write MSB of checksum to it.
    //
    SCI_writeCharBlockingNonFIFO(SCIA_BASE, ((checksum >> 8) & 0xFF));

    sciaFlush();
    sciaGetACK();
}

//
// sciSendWord - Sends a uint16_t word.
//
void sciSendWord(uint16_t word)
{
    //
    // send LSB of word, driverlib.
    //
    SCI_writeCharBlockingNonFIFO(SCIA_BASE, (word & 0xFF));

    checksum += word & 0xFF;

    sciaFlush();
    sciaGetACK();

    //
    // send MSB of word, driverlib.
    //
    SCI_writeCharBlockingNonFIFO(SCIA_BASE, ((word>>8) & 0xFF));

    checksum += word>>8 & 0xFF;

    sciaFlush();
    sciaGetACK();
}

//
// sciaInit - Initialize the SCI-A port for communications with the host.
//
void sciaInit(uint32_t  BootMode)
{
    //
    // Enable the SCI-A clocks
    //
    EALLOW;

    //
    // Device_enableAllPeripherals enabled PCLKCR7.SCI_A already.
    //

    //
    // TRM, 0x0007 -> scaler of 14. OSCLOK low speed scaling for SCI.
    //
    SysCtl_setLowSpeedClock(SYSCTL_LSPCLK_PRESCALE_14);

    // reset SCI channels.
    SCI_resetChannels(SCIA_BASE);

    //
    // 1 stop bit, No parity, 8-bit character
    // No loopback
    //
    // CLK speed and Baud rate get overwritten in autobaud_lock function later.
    //
    SCI_setConfig(
            SCIA_BASE, DEVICE_LSPCLK_FREQ, DEFAULT_BAUD,
            SCI_CONFIG_WLEN_8 | SCI_CONFIG_STOP_ONE | SCI_CONFIG_PAR_NONE);


    //
    // Enable TX, RX, Use internal SCICLK
    //
    SCI_enableModule(SCIA_BASE);

    //
    // Disable RxErr, Sleep, TX Wake,
    // Disable Rx Interrupt, Tx Interrupt
    //
    SCI_disableInterrupt(
            SCIA_BASE,
            SCI_INT_RXRDY_BRKDT | SCI_INT_TXRDY | SCI_INT_RXERR | SCI_INT_TXRDY);

    //
    // Relinquish SCI-A from reset
    //
    SCI_performSoftwareReset(SCIA_BASE);
    EDIS;

    // pick SCIA TX and RX GPIO pin according to BootMode.
    sciPinmuxOption(BootMode);

    return;
}

//
// sciaGetWordData -  This routine fetches two bytes from the SCI-A
//                    port and puts them together to form a single
//                    16-bit value.  It is assumed that the host is
//                    sending the data in the order LSB followed by MSB.
//
uint16_t sciaGetWordData(void)
{
   uint16_t wordData;
   uint16_t byteData;

   wordData = 0x0000;
   byteData = 0x0000;

   //
   // Fetch the LSB and verify back to the host
   //
   wordData = SCI_readCharBlockingNonFIFO(SCIA_BASE); // wait until RX is rdy then read.

#if !checksum_enable

   //
   // wait until TX is rdy then write.
   //
   SCI_writeCharBlockingNonFIFO(SCIA_BASE, wordData);

#endif

   //
   // Fetch the MSB and verify back to the host
   //
   byteData = SCI_readCharBlockingNonFIFO(SCIA_BASE); // read

#if !checksum_enable

   //
   // write
   //
   SCI_writeCharBlockingNonFIFO(SCIA_BASE, wordData);

#endif

//
// form checksum.
//
#if checksum_enable
    checksum += wordData + byteData;
#endif

   //
   // form the wordData from the MSB:LSB
   //
   wordData |= (byteData << 8);

   return wordData;
}

//
// sciaGetOnlyWordData -  This routine fetches two bytes from the SCI-A
//                        port and puts them together to form a single
//                        16-bit value.  It is assumed that the host is
//                        sending the data in the order LSB followed by MSB.
//
uint16_t sciaGetOnlyWordData(void)
{
   uint16_t wordData;
   uint16_t byteData;

   wordData = 0x0000;
   byteData = 0x0000;

   //
   // Fetch the LSB and verify back to the host
   //
   wordData = SCI_readCharBlockingNonFIFO(SCIA_BASE);

   //
   // Fetch the MSB and verify back to the host
   //
   byteData = SCI_readCharBlockingNonFIFO(SCIA_BASE);

   // compute checksum.
   checksum += wordData + byteData;

   //
   // form the wordData from the MSB:LSB
   //
   wordData |= (byteData << 8);

   return wordData;
}

//
// sciGetPacket -  This routine receives the packet, returns the
//                 command and puts the data length in Uin16* length
//                 and data in uint16_t* data
//
uint16_t sciGetPacket(uint16_t* length, uint16_t* data)
{
    if(sciaGetOnlyWordData() != 0x1BE4)
    {
        sendNAK();

        //
        // start packet error
        //
        return(100);
    }

    *length = sciaGetOnlyWordData();

    //
    // checksum of command and data
    //
    checksum = 0;
    uint16_t command = sciaGetOnlyWordData();

    int i = 0;
    for(i = 0; i < (*length)/2; i++)
    {
        *(data+i) = sciaGetOnlyWordData();
    }

    uint16_t dataChecksum = checksum;
    if(dataChecksum != sciaGetOnlyWordData())
    {
        sendNAK();

        //
        // checksum error
        //
        return(101);
    }
    if(sciaGetOnlyWordData() != 0xE41B)
    {
        sendNAK();

        //
        // end packet error
        //
        return(102);
    }

    sendACK();
    return(command);
}

//
// sendACK - This routine transmits ACK.
//
void sendACK(void)
{
    //
    // write ACKowledged.
    //
    SCI_writeCharBlockingNonFIFO(SCIA_BASE, ACK);

    sciaFlush();
}

//
// sendNAK - This routine transmits NAK.
//
void sendNAK(void)
{
    //
    // write NotAcKowledged.
    //
    SCI_writeCharBlockingNonFIFO(SCIA_BASE, NAK);

    sciaFlush();
}

//
// sciaFlush - This routine flushes SCIA.
//
void sciaFlush(void)
{
    //
    // wait while TX is busy.
    //
    while(SCI_isTransmitterBusy(SCIA_BASE))
    {
    }
}

//
// sciPinmuxOption -     This routine configures correct set of GPIO pins
//                       as SCI pins according to BootMode :-
//                       1) Configure GPIO Tx as SCITXDA pin
//                       2) Configure GPIO Rx as SCIRXDA pin
//                       3) Configure GPIO Rx as asynchronous pin
//
void sciPinmuxOption(uint32_t BootMode)
{
    if(BootMode == SCI_BOOT)
    {
        // Configure GPIO29 as SCITXDA (Output pin)
        // Configure GPIO28 as SCIRXDA (Input pin)
        //

        //
        // GPIO29 is the SCI Tx pin.
        //
        GPIO_setPinConfig(DEVICE_GPIO_CFG_SCITXDA);
        GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_DIR_MODE_OUT);
        GPIO_setPadConfig(DEVICE_GPIO_PIN_SCITXDA, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCITXDA, GPIO_QUAL_ASYNC);

        //
        // GPIO28 is the SCI Rx pin.
        //
        GPIO_setPinConfig(DEVICE_GPIO_CFG_SCIRXDA);
        GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_DIR_MODE_IN);
        GPIO_setPadConfig(DEVICE_GPIO_PIN_SCIRXDA, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCIRXDA, GPIO_QUAL_ASYNC);

    }
    else if(BootMode == SCI_BOOT_ALT1)
    {
        //
        // Configure GPIO16 as SCITXDA (Output pin)
        // Configure GPIO17 as SCIRXDA (Input pin)
        //

        //
        // GPIO16 is the SCI Tx pin.
        //
        GPIO_setPinConfig(GPIO_16_SCIA_TX);
        GPIO_setDirectionMode(16, GPIO_DIR_MODE_OUT);
        GPIO_setPadConfig(16, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(16, GPIO_QUAL_ASYNC);

        //
        // GPIO17 is the SCI Rx pin.
        //
        GPIO_setPinConfig(GPIO_17_SCIA_RX);
        GPIO_setDirectionMode(17, GPIO_DIR_MODE_IN);
        GPIO_setPadConfig(17, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(17, GPIO_QUAL_ASYNC);
    }
    else if(BootMode == SCI_BOOT_ALT2)
    {
        //
        // Configure GPIO8 as SCITXDA (Output pin)
        // Configure GPIO9 as SCIRXDA (Input pin)
        //

        //
        // GPIO8 is the SCI Tx pin.
        //
        GPIO_setPinConfig(GPIO_8_SCIA_TX);
        GPIO_setDirectionMode(8, GPIO_DIR_MODE_OUT);
        GPIO_setPadConfig(8, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(8, GPIO_QUAL_ASYNC);

        //
        // GPIO9 is the SCI Rx pin.
        //
        GPIO_setPinConfig(GPIO_9_SCIA_RX);
        GPIO_setDirectionMode(9, GPIO_DIR_MODE_IN);
        GPIO_setPadConfig(9, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(9, GPIO_QUAL_ASYNC);

    }
    else if(BootMode == SCI_BOOT_ALT3)
    {
        //
        // Configure GPIO2 as SCITXDA (Output pin)
        // Configure GPIO3 as SCIRXDA (Input pin)
        //

        //
        // GPIO2 is the SCI Tx pin.
        //
        GPIO_setPinConfig(GPIO_2_SCIA_TX);
        GPIO_setDirectionMode(2, GPIO_DIR_MODE_OUT);
        GPIO_setPadConfig(2, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(2, GPIO_QUAL_ASYNC);

        //
        // GPIO23 is the SCI Rx pin.
        //
        GPIO_setPinConfig(GPIO_3_SCIA_RX);
        GPIO_setDirectionMode(3, GPIO_DIR_MODE_IN);
        GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(3, GPIO_QUAL_ASYNC);

    }
    else if(BootMode == SCI_BOOT_ALT4)
    {
        //
        // Configure GPIO16 as SCITXDA (Output pin)
        // Configure GPIO3 as SCIRXDA (Input pin)
        //

        //
        // GPIO16 is the SCI Tx pin.
        //
        GPIO_setPinConfig(GPIO_16_SCIA_TX);
        GPIO_setDirectionMode(16, GPIO_DIR_MODE_OUT);
        GPIO_setPadConfig(16, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(16, GPIO_QUAL_ASYNC);

        //
        // GPIO3 is the SCI Rx pin.
        //
        GPIO_setPinConfig(GPIO_3_SCIA_RX);
        GPIO_setDirectionMode(3, GPIO_DIR_MODE_IN);
        GPIO_setPadConfig(3, GPIO_PIN_TYPE_STD);
        GPIO_setQualificationMode(3, GPIO_QUAL_ASYNC);

    }
}

//
// End of file
//
