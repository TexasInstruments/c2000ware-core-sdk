//###########################################################################
//
// FILE:   pmbus_over_i2c_stack_config.c
//
// TITLE:  PMBUS over I2C Communications Stack Configuration
//
//#############################################################################
//!
//! Copyright: Copyright (C) 2023 Texas Instruments Incorporated -
//!	All rights reserved not granted herein.
//!	Limited License.
//!
//! Texas Instruments Incorporated grants a world-wide, royalty-free,
//! non-exclusive license under copyrights and patents it now or hereafter
//! owns or controls to make, have made, use, import, offer to sell and sell
//! ("Utilize") this software subject to the terms herein. With respect to the
//! foregoing patent license, such license is granted solely to the extent that
//! any such patent is necessary to Utilize the software alone. The patent
//! license shall not apply to any combinations which include this software,
//! other than combinations with devices manufactured by or for TI 
//! ("TI Devices").
//! No hardware patent is licensed hereunder.
//!
//! Redistributions must preserve existing copyright notices and reproduce this
//! license (including the above copyright notice and the disclaimer and
//! (if applicable) source code license limitations below) in the documentation
//!  and/or other materials provided with the distribution.
//!
//! Redistribution and use in binary form, without modification, are permitted
//! provided that the following conditions are met:
//!
//! * No reverse engineering, decompilation, or disassembly of this software is 
//! permitted with respect to any software provided in binary form.
//! * Any redistribution and use are licensed by TI for use only 
//!   with TI Devices.
//! * Nothing shall obligate TI to provide you with source code for the 
//!   software licensed and provided to you in object code.
//!
//! If software source code is provided to you, modification and redistribution
//! of the source code are permitted provided that the following conditions 
//! are met:
//!
//! * any redistribution and use of the source code, including any resulting
//!   derivative works, are licensed by TI for use only with TI Devices.
//! * any redistribution and use of any object code compiled from the source
//!   code and any resulting derivative works, are licensed by TI for use 
//!   only with TI Devices.
//!
//! Neither the name of Texas Instruments Incorporated nor the names of its
//! suppliers may be used to endorse or promote products derived from this 
//! software without specific prior written permission.
//#############################################################################


#ifdef PMBUS_OVER_I2C
//
// Includes
//
#include <stdint.h>
#include <stdbool.h>
#include "pmbus_over_i2c_stack_config.h"
#ifdef TIMEOUT
#include "device.h"
#endif
#ifdef PEC_ENABLED
#include "vcu2_crc.h"
#endif

// Function prototypes
void PMBus_over_I2C_initTarget(uint32_t base, uint16_t address, uint16_t mask);
void PMBus_over_I2C_initControllerMode(uint32_t base,  uint16_t address);
uint16_t PMBus_over_I2C_getData(uint32_t base, uint16_t *buffer);
void PMBus_over_I2C_putData(uint32_t base, uint16_t *buffer, uint16_t nBytes);

//
// Defines
//
PMBUS_STACK_FILENUM(1)

#define PMBUS_STACK_TARGET_ADDRESS  0U
#define PMBUS_STACK_CONTROLLER_ADDRESS 0x40U
#define PMBUS_STACK_TARGET_MASK     0x7FU

//
// Globals
//
PMBus_StackObject PMBusStackTarget;
PMBus_StackHandle PMBusStackTargetHandle = &PMBusStackTarget;

//*****************************************************************************
//
// PMBusStack_initModule
// This function is used to initialize the PMBUS stack
// Based on the mode of operation (TARGET/CONTROLLER), the PMBus object is
// configured
//
//*****************************************************************************
bool PMBusStack_initModule(PMBus_StackHandle handle, const uint32_t moduleBase,
                           uint16_t *buffer, uint16_t *CRCBuffer)
{
    //
    // Locals
    //
    bool status = false;

    //
    // Set the module base address
    //
    PMBusStackObject_setModuleBase(handle, moduleBase);

    //
    // Assign the buffer pointer to the object, set the current pointer to
    // the head of the buffer
    //
    PMBusStackObject_setBufferPointer(handle, buffer);
    PMBusStackObject_setCurrentPositionPointer(handle, buffer);
    PMBusStackObject_setCRCBufferPointer(handle,CRCBuffer );

    // Reset the I2C Module
    //
    I2C_disableModule(PMBusStackObject_getModuleBase(handle));

    //
    // Initialize depending upon whether in target or controller mode
    //
    if(PMBusStackObject_getMode(handle) == PMBUS_STACK_MODE_TARGET)
    {
        //
        // Initialize the target module
        //
        // Setup a CPU timer
#ifdef TIMEOUT
        initCPUTimers(PMBusStackObject_getTimerBase(handle));

        configCPUTimer(PMBusStackObject_getTimerBase(handle), DEVICE_SYSCLK_FREQ, PMBusStackObject_getTimeout(handle));
#endif

        //
        // Initialize the target module
        //
        PMBus_over_I2C_initTarget(PMBusStackObject_getModuleBase(handle),
                        PMBusStackObject_getTargetAddress(handle),
                        PMBusStackObject_getTargetAddressMask(handle));



        //Enable FIFO Interrupt
        I2C_setFIFOInterruptLevel(PMBusStackObject_getModuleBase(handle),I2C_FIFO_TX16,I2C_FIFO_RX5);


        //
        // Enable interrupts
        //
        I2C_enableInterrupt(PMBusStackObject_getModuleBase(handle),
                              (I2C_INT_STOP_CONDITION | I2C_INT_TX_DATA_RDY | I2C_INT_RXFF ));

        //
        // Reset the state machine
        //
        PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_IDLE);
        PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);

        status = true;
    }
    else // (PMBusStackObject_getMode(handle) == PMBUS_STACK_MODE_CONTROLLER)
    {

        // Initialize the controller module
        //
        PMBus_over_I2C_initControllerMode(PMBusStackObject_getModuleBase(handle), PMBusStackObject_getTargetAddress(handle) );

        //
        // Enable interrupts
        //
        I2C_enableInterrupt(PMBusStackObject_getModuleBase(handle),
                              (I2C_INT_STOP_CONDITION ));

        //
        // Reset the state machine
        //
        PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_IDLE);
        PMBusStackObject_setNextState(handle, PMBUS_STACK_STATE_IDLE);

        status = true;
    }

    //
     // Take the I2C module out of reset
     //
     I2C_enableModule(PMBusStackObject_getModuleBase(handle));

    return(status);
}

//*****************************************************************************
//
// PMBusStack_defaultTransactionHandler
// This function is the default transaction handler
//
//*****************************************************************************
int32_t PMBusStack_defaultTransactionHandler(PMBus_StackHandle handle)
{
    //
    // Replace with an actual handler. This will stop emulation
    //
    PMBUS_STACK_ASSERT(0);

    return(-1);
}

//*****************************************************************************
//
// PMBus_over_I2C_initTarget
// This function is used to initialize the TARGET mode
//
//*****************************************************************************
void PMBus_over_I2C_initTarget(uint32_t base, uint16_t address, uint16_t mask)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));
    ASSERT(address <= 0x7FU);
    ASSERT(mask <= 0x7FU);

    EALLOW;

    //
    // Configure the target in Receive mode
    //
    I2C_setConfig(base, I2C_TARGET_RECEIVE_MODE);

    I2C_setBitCount(base, I2C_BITCOUNT_8);

    //
    // Write the address to own address
    I2C_setOwnAddress(base, address);

    I2C_setEmulationMode(base, I2C_EMULATION_FREE_RUN);

    //
    // FIFO and interrupt configuration
    //
    I2C_enableFIFO(base);
    I2C_clearInterruptStatus(base, I2C_INT_TXFF);
    I2C_clearInterruptStatus(base, I2C_INT_RXFF);
    I2C_clearStatus(base,I2C_STS_NO_ACK|I2C_STS_ARB_LOST|I2C_STS_REG_ACCESS_RDY|I2C_STS_STOP_CONDITION);

    I2C_disableInterrupt(base, (I2C_INT_ARB_LOST | I2C_INT_NO_ACK));


    EDIS;

}

//*****************************************************************************
//
// PMBus_initControllerMode
// This function is used to initialize the CONTROLLER mode
//
//*****************************************************************************
void PMBus_over_I2C_initControllerMode(uint32_t base,  uint16_t address)
{
    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    EALLOW;

    //
    // Write the address to own address
    I2C_setOwnAddress(base, PMBUS_STACK_CONTROLLER_ADDRESS);

     I2C_setTargetAddress(base, address);

    //
    // Configure I2C in controller send mode
    //
     I2C_setConfig(base, I2C_CONTROLLER_SEND_MODE);

     //
     // FIFO and interrupt configuration
     //
     I2C_enableFIFO(base);
     I2C_clearInterruptStatus(base, I2C_INT_TXFF);
     I2C_clearInterruptStatus(base, I2C_INT_RXFF);
     I2C_clearStatus(base,I2C_STS_NO_ACK|I2C_STS_ARB_LOST|I2C_STS_REG_ACCESS_RDY|I2C_STS_STOP_CONDITION);

     I2C_disableInterrupt(base, (I2C_INT_ADDR_TARGET| I2C_INT_ARB_LOST | I2C_INT_NO_ACK));
     I2C_setEmulationMode(base, I2C_EMULATION_FREE_RUN);

     EDIS;
}

/***************************************************************************//**
//
//! write to the transmit buffer (Controller mode)
//!
//! \param base is the base address of the PMBus instance used.
//! \param buffer pointer to the message buffer where the transmit bytes
//!   are stored
//! \param nBytes number of transmit bytes, up to 255
//!
//! This function can write up to 255 bytes in the transmit buffer.
//!
//! \note
//! -# The user must check the UNIT_BUSY bit before attempting the
//! first transmission.
//! -# The buffer should be at least 4 words long; anything smaller will
//! lead to the possibility of memory overrun when a transaction of 4 bytes
//! happens.
//!
//! \return None.
//
 ******************************************************************************/
void PMBus_over_I2C_putData(uint32_t base, uint16_t *buffer, uint16_t nBytes)
{
    //
    // Locals
    //
    uint32_t tx_data = 0U;
    uint16_t *pBuffer = buffer;

    //
     // Check the arguments.
     //
     ASSERT(I2C_isBaseValid(base));

     /*
     while(i < nBytes)
     {
         tx_data |= (((uint32_t)*pBuffer & 0x000000FFUL) <<
                        ((uint32_t)i << 3U));
         pBuffer++;
         i++;
     }
     */

     /***************Write******************/
    if(nBytes != 0)
    {

        while(nBytes > 0)    //check that there are still bytes to send
        {
            tx_data = (*pBuffer & 0x000000FFUL);
            I2C_putData(base,tx_data);
            //tx_data = tx_data >> (8U);
            pBuffer++;
            nBytes--;
        }


    }
}


//*****************************************************************************
//
// PMBus_over_I2C_getData
//
//
//! Read from the receive buffer
//!
//! \param base is the base address of the PMBus instance used.
//! \param buffer pointer to the message buffer where the received bytes
//!  will be stored
//!
//! \return num_rx_bytes - Number of bytes that are received.
//
//*****************************************************************************
uint16_t PMBus_over_I2C_getData(uint32_t base, uint16_t *buffer)
{

    //
    // Locals
    //
    uint32_t temp, i;
    uint16_t num_rx_bytes;

    //
    // Check the arguments.
    //
    ASSERT(I2C_isBaseValid(base));

    //
    // Get the contents of the Receive buffer.
    //
    num_rx_bytes = (uint16_t)I2C_getRxFIFOStatus(base);

    if(num_rx_bytes != 0U)
    {

        for(i = 0U; i < num_rx_bytes; i++)
        {
            temp = HWREG(base + I2C_O_DRR);
            buffer[i] = (uint16_t)(temp & 0x000000FFUL);
            //temp      = temp >> 8U;
        }
    }

    return(num_rx_bytes);

}

#ifdef PEC_ENABLED
uint16_t PMBusTarget_CrcMsgSize = 0;
uint16_t PMBusTarget_CrcMsg[5];
uint16_t PMBusTarget_CrcControllerGenerated = 0;
uint16_t PMBusTarget_CrcTargetGenerated = 0;

uint16_t calc_PEC(uint16_t *CRCMsgBuffer, uint16_t CRCMsgSize, uint16_t *pMsgBuffer, uint16_t nBytes)
{
      uint16_t crcResultVcu =0U ;
      uint16_t CRCBuffer[256];
      uint16_t index =0, u8Index=0;
      uint16_t count =0;

// initialize to zero

      // CRCMsgSize - if index is even, use __byte(&CRCBuffer[index],0)

      for(index =0;index<CRCMsgSize;index++)
      {
          if(count%2 ==0)
          {
              __byte(&CRCBuffer[u8Index],0) = CRCMsgBuffer[index];
              count++;
          }
          else
          {
              __byte(&CRCBuffer[u8Index],1) = CRCMsgBuffer[index];
              count++;
          }
          if(count%2==0)
          {
              u8Index++;
          }
      }

      for(index =0;index<nBytes;index++)
      {
          if(count%2 ==0)
          {
              __byte(&CRCBuffer[u8Index],0) = pMsgBuffer[index];
              count++;
          }
          else
          {
              __byte(&CRCBuffer[u8Index],1) = pMsgBuffer[index];
              count++;
          }
          if(count%2==0)
          {
              u8Index++;
          }
      }

      CRC_Obj    CRC;
      CRC_Handle handleCRC;
      // Step 1: Initialize the CRC object
      CRC.seedValue    = 0;
      CRC.nMsgBytes    = nBytes + CRCMsgSize;
      CRC.parity       = CRC_parity_even;
      CRC.crcResult    = 0;
      CRC.pMsgBuffer   = (uint16_t *)&CRCBuffer[0];
      //CRC.pCrcTable    = (uint16_t *)&crc8Table[0];
      CRC.init         = (void (*)(void *))CRC_init8Bit;

      // Step 2: Initialize the handle
      handleCRC = &CRC;

      //! Now we run the VCU routine on the vector testInput. The
      //! polynomial employed by the VCU is fixed i.e.
      //! \f$ x^{8}+x^{2}+x^{1}+1 \f$ (0x07)
      //! The parity chosen was CRC_parity_even indicating that the CRC will start
      //! from the low byte of the first word.
      //!
      CRC.init(handleCRC);

      CRC.crcResult    = 0;
      CRC.run          = (void (*)(void *))CRC_run8Bit;

      // Step 2: Run the VCU 8-bit CRC routine and save the result
      CRC.run(handleCRC);
      crcResultVcu = CRC.crcResult & 0x00FF;       //We only want one byte (lower);

      return(crcResultVcu);
}


bool verifyPEC(uint16_t *CRCMsgBuffer, uint16_t CRCMsgSize, uint16_t *pMsgBuffer, uint16_t nBytes, uint16_t receivedPEC)
{
    uint16_t calcPEC = 0U;
    bool bVerifyPEC= false;
    calcPEC=calc_PEC(CRCMsgBuffer, CRCMsgSize,pMsgBuffer,nBytes);

    if(calcPEC ==receivedPEC)
    {
        bVerifyPEC =true;
    }
    return (bVerifyPEC);

}

#endif

#ifdef TIMEOUT
void
configCPUTimer(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    //
    // Initialize timer period:
    //
    temp = (uint32_t)((freq / 1000000) * period);
    CPUTimer_setPeriod(cpuTimer, temp);

    //
    // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    //
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);

}

void
initCPUTimers(uint32_t cpuTimer)
{
    //
    // Initialize timer period to maximum
    //
    CPUTimer_setPeriod(cpuTimer, 0xFFFFFFFF);


    //
    // Initialize pre-scale counter to divide by 1 (SYSCLKOUT)
    //
    CPUTimer_setPreScaler(cpuTimer, 0);

    //
    // Make sure timer is stopped
    //
    CPUTimer_stopTimer(cpuTimer);

    //
    // Reload all counter register with period value
    //
    CPUTimer_reloadTimerCounter(cpuTimer);


}

PMBusStack_targetTimeoutHandler(PMBus_StackHandle handle)
{
    uint16_t *buffer = PMBusStackObject_getBufferPointer(handle);

    //
    // Set the current state to idle
    //
    PMBusStackObject_setCurrentState(handle, PMBUS_STACK_STATE_IDLE);

    //
    // Rewind the current pointer
    //
    PMBusStackObject_setCurrentPositionPointer(handle, buffer);

    //
    // Set the object transaction type
    //
    PMBusStackObject_setTransactionType(handle, PMBUS_TRANSACTION_NONE);

}
#endif
#endif

//
// End of File
//
