//#############################################################################
//
// FILE:   i2c_ex5_master_slave_interrupt.c
//
// TITLE:  I2C master slave communication using FIFO interrupts
//
//! \addtogroup driver_example_list
//! <h1>I2C master slave communication using FIFO interrupts</h1>
//!
//! This program shows how to use I2CA and I2CB modules in both master and slave
//! configuration This example uses I2C FIFO interrupts and doesn't using polling
//!
//! Example1: I2CA as Master Transmitter and I2CB working Slave Receiver
//! Example2: I2CA as Master Receiver and I2CB working Slave Transmitter
//! Example3: I2CB as Master Transmitter and I2CA working Slave Receiver
//! Example4: I2CB as Master Receiver and I2CA working Slave Transmitter
//!
//! \b External \b Connections on launchpad should be made as shown below \n
//!  --------------------------------
//!    Signal   |  I2CA   |  I2CB
//!  --------------------------------
//!     SCL     | GPIO105 |  GPIO41
//!     SDA     | GPIO104 |  GPIO40
//!  --------------------------------
//!
//! \b Watch \b Variables in memory window\n
//!  - \b I2CA_TXdata
//!  - \b I2CA_RXdata
//!  - \b I2CB_TXdata
//!  - \b I2CB_RXdata
//!    stream for error checking
//!
//#############################################################################
//
// $Release Date: $
// $Copyright:
// Copyright (C) 2014-2023 Texas Instruments Incorporated - http://www.ti.com/
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
//#############################################################################
//
// Included Files
//
#include "driverlib.h"
#include "device.h"


#include "i2cLib_FIFO_master_slave_interrupt.h"

//
// Defines
//
#define I2CA_ADDRESS   0x30
#define I2CB_ADDRESS   0x40

//!  --------------------------------
//!    Signal   |  I2CA   |  I2CB
//!  --------------------------------
//!     SCL     | GPIO105 |  GPIO41
//!     SDA     | GPIO104 |  GPIO40
//!  --------------------------------

//
// Globals
//
uint16_t status = 0;

struct I2CHandle I2CA;
struct I2CHandle I2CB;

//
// Function Prototypes
//
__interrupt void i2cAISR(void);
__interrupt void i2cAFIFOISR(void);

__interrupt void i2cBISR(void);
__interrupt void i2cBFIFOISR(void);

uint16_t AvailableI2C_slaves[MAX_I2C_IN_NETWORK];

uint16_t I2CA_TXdata[MAX_BUFFER_SIZE];
uint16_t I2CB_TXdata[MAX_BUFFER_SIZE];

uint16_t I2CA_RXdata[MAX_BUFFER_SIZE];
uint16_t I2CB_RXdata[MAX_BUFFER_SIZE];

uint32_t I2CA_ControlAddr;
uint32_t I2CB_ControlAddr;
uint16_t status;

void I2C_GPIO_init(void);
void I2Cinit(void);

//
// Main
//
void main(void)
{

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    //
    // Board initialization
    //

    I2C_GPIO_init();

    //
    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    //
    Interrupt_initModule();

    //
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    //
    Interrupt_initVectorTable();

    I2Cinit();


    I2C_setOwnSlaveAddress(I2CA_BASE, I2CA_ADDRESS);
    I2C_setOwnSlaveAddress(I2CB_BASE, I2CB_ADDRESS);



    //I2Cs connected to I2CA will be found in AvailableI2C_slaves buffer
    //after you run I2CBusScan function.
    //When you run I2C BusScan you need to disable I2C interrupts and clear
    //the flag set during I2CBusScan
    uint16_t i;

    for(i=0;i<MAX_I2C_IN_NETWORK;i++)
    {
        AvailableI2C_slaves[i] = 0;
    }

    I2C_disableInterrupt(I2CA_BASE, (I2C_INT_ADDR_SLAVE|I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));
    I2C_disableInterrupt(I2CB_BASE, (I2C_INT_ADDR_SLAVE|I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));

    uint16_t *pAvailableI2C_slaves = AvailableI2C_slaves;
    status = I2CBusScan(I2CA_BASE, pAvailableI2C_slaves);

    I2C_clearStatus(I2CA_BASE,I2C_STS_NO_ACK|I2C_STS_ARB_LOST|I2C_STS_REG_ACCESS_RDY|I2C_STS_STOP_CONDITION);
    I2C_clearStatus(I2CB_BASE,I2C_STS_NO_ACK|I2C_STS_ARB_LOST|I2C_STS_REG_ACCESS_RDY|I2C_STS_STOP_CONDITION);

    ESTOP0;
    I2C_disableInterrupt(I2CA_BASE, (I2C_INT_ADDR_SLAVE|I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));
    I2C_disableInterrupt(I2CB_BASE, (I2C_INT_ADDR_SLAVE|I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));

    status = I2CBusScan(I2CB_BASE, pAvailableI2C_slaves);

    I2C_clearStatus(I2CA_BASE,I2C_STS_NO_ACK|I2C_STS_ARB_LOST|I2C_STS_REG_ACCESS_RDY|I2C_STS_STOP_CONDITION);
    I2C_clearStatus(I2CB_BASE,I2C_STS_NO_ACK|I2C_STS_ARB_LOST|I2C_STS_REG_ACCESS_RDY|I2C_STS_STOP_CONDITION);


    I2C_enableInterrupt(I2CA_BASE, (I2C_INT_ADDR_SLAVE|I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));
    I2C_enableInterrupt(I2CB_BASE, (I2C_INT_ADDR_SLAVE|I2C_INT_STOP_CONDITION | I2C_INT_ARB_LOST | I2C_INT_NO_ACK));


    //
    // Set I2C use, initializing it for FIFO mode
    //

    Interrupt_register(INT_I2CA, &i2cAISR);
    Interrupt_enable(INT_I2CA);

    Interrupt_register(INT_I2CB, &i2cBISR);
    Interrupt_enable(INT_I2CB);

    Interrupt_register(INT_I2CA_FIFO, &i2cAFIFOISR);
    Interrupt_enable(INT_I2CA_FIFO);

    Interrupt_register(INT_I2CB_FIFO, &i2cBFIFOISR);
    Interrupt_enable(INT_I2CB_FIFO);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;


    for(i=0;i<MAX_BUFFER_SIZE;i++)
    {
        I2CA_TXdata[i] = i+1;
        I2CA_RXdata[i] = 0;
        I2CB_TXdata[i] = 0;
        I2CB_RXdata[i] = 0;
    }

    I2CA.currentHandlePtr = &I2CA;
    I2CA.base             = I2CA_BASE;
    I2CA.SlaveAddr        = I2CB_ADDRESS;
    I2CA.pControlAddr     = &I2CA_ControlAddr;
    I2CA.NumOfAddrBytes   = 4;
    I2CA.pTX_MsgBuffer    = I2CA_TXdata;
    I2CA.pRX_MsgBuffer    = I2CA_RXdata;
    I2CA.NumOfDataBytes   = 64;

    I2CB.currentHandlePtr = &I2CB;
    I2CB.base             = I2CB_BASE;
    I2CB.SlaveAddr        = I2CB_ADDRESS;
    I2CB.NumOfAddrBytes   = 4;
    I2CB.pControlAddr     = (uint32_t *)0;
    I2CB.pTX_MsgBuffer    = (uint16_t *)0;
    I2CB.pRX_MsgBuffer    = (uint16_t *)0;

// Example1: I2CA as Master Transmitter and I2CB working Slave Receiver //

    // I2CA = Master Transmitter
    // I2CB = Slave Receiver
    // I2CA generates
    // 1) START condition
    // 2) I2CB address (Slave address) + Write mode
    // 3) Transmit start address of I2CB_RXdata
    // 4) Transmit contents of I2CA_TXdata array
    // 5) I2CB received data is stored in I2CB_RXdata array
    // 6) Contents of I2CA_TXdata and I2CB_RXdata should match

    //Slave pControlAddr should be 0 proper operation.
    //Slave pControlAddr is transmitted by I2CA master
    I2CB.pControlAddr   = (uint32_t *)0;
    I2CA_ControlAddr    =  (uint32_t)I2CB_RXdata;
    status = I2C_MasterTransmitter(&I2CA);

    // Wait for I2CA to be complete transmission of data
    while(I2C_getStatus(I2CA.base) & I2C_STS_BUS_BUSY);

    for(i=0;i<I2CA.NumOfDataBytes;i++)
    {
        if((I2CB_RXdata[i] != I2CA_TXdata[i]) || (status != 0))
        {
            //Fail condition. Code shouldn't reach here
            //Check status (global variable) for I2C errors
            ESTOP0;
        }
    }


    //If code reached below ESTOP0, I2CA as master transmitter and
    //I2CB as slave receiver worked correctly
    //Observe the contents of I2CA_TXdata and I2CB_RXdata in memory browser
    // Example1: I2CA as Master Transmitter and I2CB working Slave Receiver - PASSED//
    ESTOP0;

// Example2: I2CA as Master Receiver and I2CB working Slave Transmitter //

    // I2CA = Master Receiver
    // I2CB = Slave Transmitter
    // I2CA generates
    // 1) START condition
    // 2) I2CB address (Slave address) + Write mode
    // 3) Transmit start address of I2CB_TXdata
    // 4) I2CA generates repeated START condition + Read mode
    // 4) I2CB (slave) transmits contents of I2CB_TXdata
    // 5) I2CA received data is stored in I2CA_RXdata array
    // 6) Contents of I2CB_TXdata and I2CA_RXdata should match

    for(i=0;i<MAX_BUFFER_SIZE;i++)
    {
        I2CA_TXdata[i] = 0;
        I2CA_RXdata[i] = 0;
        I2CB_TXdata[i] = i+1;
        I2CB_RXdata[i] = 0;
    }

    //Slave pControlAddr should be 0 proper operation.
    //Slave pControlAddr is transmitted by I2CA master
    I2CB.pControlAddr   = (uint32_t *)0;
    I2CA_ControlAddr    =  (uint32_t)I2CB_TXdata;
    status = I2C_MasterReceiver(&I2CA);

    // Wait for I2CA to be complete transmission of data
    while(I2C_getStatus(I2CA.base) & I2C_STS_BUS_BUSY);

    for(i=0;i<I2CA.NumOfDataBytes;i++)
    {
        if((I2CB_TXdata[i] != I2CA_RXdata[i]) || (status != 0))
        {
            //Fail condition. Code shouldn't reach here
            //Check status (global variable) for I2C errors
            ESTOP0;
        }
    }

    //If code reached below ESTOP0, then I2CA as master receiver and
    //I2CB as slave transmitter worked correctly
    //Observe the contents of I2CB_TXdata and I2CA_RXdata in memory browser
    // Example2: I2CA as Master Receiver and I2CB working Slave Transmitter - PASSED//
    ESTOP0;

// Example3: I2CB as Master Transmitter and I2CA working Slave Receiver //

        // I2CB = Master Transmitter
        // I2CA = Slave Receiver
        // I2CB generates
        // 1) START condition
        // 2) I2CA address (Slave address) + Write mode
        // 3) Transmit start address of I2CA_RXdata
        // 4) Transmit contents of I2CB_TXdata array
        // 5) I2CA received data is stored in I2CA_RXdata array
        // 6) Contents of I2CB_TXdata and I2CA_RXdata should match

    for(i=0;i<MAX_BUFFER_SIZE;i++)
    {
       I2CA_TXdata[i] = 0;
       I2CA_RXdata[i] = 0;
       I2CB_TXdata[i] = i+1;
       I2CB_RXdata[i] = 0;
    }

    I2CB.currentHandlePtr = &I2CB;
    I2CB.base             = I2CB_BASE;
    I2CB.SlaveAddr        = I2CA_ADDRESS;
    I2CB.pControlAddr     = &I2CB_ControlAddr;
    I2CB.NumOfAddrBytes   = 4;
    I2CB.pTX_MsgBuffer    = I2CB_TXdata;
    I2CB.pRX_MsgBuffer    = I2CB_RXdata;
    I2CB.NumOfDataBytes   = 64;


    I2CA.currentHandlePtr = &I2CA;
    I2CA.base             = I2CA_BASE;
    I2CA.SlaveAddr        = I2CB_ADDRESS;
    I2CA.NumOfAddrBytes   = 4;
    I2CA.pControlAddr     = (uint32_t *)0;
    I2CA.pTX_MsgBuffer    = (uint16_t *)0;
    I2CA.pRX_MsgBuffer    = (uint16_t *)0;

    //Slave pControlAddr should be 0 proper operation.
    //Slave pControlAddr is transmitted by I2CB master
    I2CA.pControlAddr   = (uint32_t *)0;
    I2CB_ControlAddr    = (uint32_t)I2CA_RXdata;
    status = I2C_MasterTransmitter(&I2CB);

    // Wait for I2CB to be complete transmission of data
    while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);

    for(i=0;i<I2CB.NumOfDataBytes;i++)
    {
        if((I2CB_TXdata[i] != I2CA_RXdata[i]) || (status != 0))
        {
            //Fail condition. Code shouldn't reach here
            //Check status (global variable) for I2C errors
            ESTOP0;
        }
    }

    //If code reached below ESTOP0, I2CB as master transmitter and
    //I2CA as slave receiver worked correctly
    //Observe the contents of I2CB_TXdata and I2CA_RXdata in memory browser
    // Example3: I2CB as Master Transmitter and I2CA working Slave Receiver - PASSED//
    ESTOP0;

// Example4: I2CB as Master Receiver and I2CA working Slave Transmitter //

        // I2CB = Master Receiver
        // I2CA = Slave Transmitter
        // I2CB generates
        // 1) START condition
        // 2) I2CA address (Slave address) + Write mode
        // 3) Transmit start address of I2CA_TXdata
        // 4) I2CB generates repeated START condition + Read mode
        // 4) I2CA (slave) transmits contents of I2CA_TXdata
        // 5) I2CB received data is stored in I2CB_RXdata array
        // 6) Contents of I2CA_TXdata and I2CB_RXdata should match

        for(i=0;i<MAX_BUFFER_SIZE;i++)
        {
            I2CA_TXdata[i] = i+1;
            I2CA_RXdata[i] = 0;
            I2CB_TXdata[i] = 0;
            I2CB_RXdata[i] = 0;
        }

        //Slave pControlAddr should be 0 proper operation.
        //Slave pControlAddr is transmitted by I2CA master
        I2CA.pControlAddr   = (uint32_t *)0;
        I2CB_ControlAddr    =  (uint32_t)I2CA_TXdata;
        status = I2C_MasterReceiver(&I2CB);

        // Wait for I2CA to be complete transmission of data
        while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);

        for(i=0;i<I2CB.NumOfDataBytes;i++)
        {
            if((I2CA_TXdata[i] != I2CB_RXdata[i]) || (status != 0))
            {
                //Fail condition. Code shouldn't reach here
                //Check status (global variable) for I2C errors
                ESTOP0;
            }
        }

        //If code reached below ESTOP0, I2CB as Master Receiver and
        //I2CA as Slave Transmitter worked correctly
        //Observe the contents of I2CA_TXdata and I2CB_RXdata in memory browser
        // Example4: I2CB as Master Receiver and I2CA working Slave Transmitter - PASSED//
        ESTOP0;

    //
    // Loop forever. Suspend or place breakpoints to observe the buffers.
    //
    while(1)
    {
     // A FIFO interrupt will be generated for each Tx and Rx based
     // on the Interrupt levels configured.
     // The ISR will handle pushing/pulling data to/from the TX and
     // RX FIFOs resp.
    }

}

//
// pass condition
//
void
pass(void)
{
    asm("   ESTOP0");
    for(;;);
}

//
// fail condition
//
void fail(void)
{
    asm("   ESTOP0");
    for(;;);
}


//
// I2CA ISR
//
__interrupt void i2cAISR(void)
{
    uint16_t MasterSlave = I2C_getStatus(I2CA.base) & I2C_STS_ADDR_SLAVE;

    if(MasterSlave)
    {
        //I2CA working as slave
        //Disable I2CB FIFO interrupt to first trigger I2CA FIFO interrupt to read control address
        I2C_disableInterrupt(I2CB.base, (I2C_INT_TXFF));
    }

    handleI2C_ErrorCondition(&I2CA);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

//
// I2CA FIFO ISR
//
__interrupt void i2cAFIFOISR(void)
{
    Write_Read_TX_RX_FIFO(&I2CA);

    uint16_t MasterSlave = HWREGH(I2CA.base + I2C_O_MDR);

    if(MasterSlave & I2C_MDR_MST)
    {
        //I2CA working in master configuration
        if(MasterSlave & I2C_MDR_TRX)
        {
          //I2CA working as Master Transmitter
          I2C_disableInterrupt(I2CA.base, (I2C_INT_TXFF));
        }
        else
        {
          //I2CA working as Master Receiver
          I2C_enableInterrupt(I2CB.base, (I2C_INT_TXFF));
          I2C_clearInterruptStatus(I2CB.base,(I2C_INT_TXFF));
        }
    }
    else
    {
        //I2CA working in slave configuration
        if(MasterSlave & I2C_MDR_TRX)
        {
            //I2CA = Slave Transmitter & I2CB = Master Receiver
            //So, I2CB RXFIFO interrupt is enabled  &
            //    I2CB TXFIFO interrupt is disabled
            I2C_enableInterrupt(I2CB.base, (I2C_INT_RXFF));
            I2C_disableInterrupt(I2CB.base, (I2C_INT_TXFF));
            I2C_clearInterruptStatus(I2CB.base,(I2C_INT_RXFF));

            I2C_disableInterrupt(I2CA.base, (I2C_INT_TXFF));
        }
       else
       {
           //I2CA working as slave receiver
           if(HWREGH(I2CB.base + I2C_O_CNT) == I2CB.NumOfAddrBytes)
           {
               //Enable I2CB Register Access Ready interrupt to change
               //to master receiver
               I2C_enableInterrupt(I2CB.base, I2C_INT_REG_ACCESS_RDY);
               if(I2CA.pTX_MsgBuffer == 0x0)
               {
                    I2CA.pTX_MsgBuffer = (uint16_t *)((uint32_t)(I2CA.pControlAddr) & 0x00FFFFFF);
                    I2CA.pRX_MsgBuffer = (uint16_t *)0;
               }
           }
           else
           {
               //Continue with I2CB master transmitter mode
               I2C_enableInterrupt(I2CB.base, (I2C_INT_TXFF));
               I2C_disableInterrupt(I2CB.base, (I2C_INT_RXFF));
               I2C_clearInterruptStatus(I2CB.base,(I2C_INT_TXFF | I2C_INT_RXFF));
               if(I2CA.pRX_MsgBuffer == 0x0)
               {
                   I2CA.pRX_MsgBuffer = (uint16_t *)((uint32_t)(I2CA.pControlAddr) & 0x00FFFFFF);
                   I2CA.pTX_MsgBuffer = (uint16_t *)0;
               }
           }
       }
   }

   Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

//
// I2CB ISR
//
__interrupt void i2cBISR(void)
{
   uint16_t MasterSlave = I2C_getStatus(I2CB.base) & I2C_STS_ADDR_SLAVE;

   if(MasterSlave)
   {
       //I2CB working as slave
       //Disable I2CA FIFO interrupt to first trigger I2CB FIFO interrupt to read control address
       I2C_disableInterrupt(I2CA.base, (I2C_INT_TXFF));
   }


   handleI2C_ErrorCondition(&I2CB);

   Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

//
// I2CB FIFO ISR
//
__interrupt void i2cBFIFOISR(void)
{
    Write_Read_TX_RX_FIFO(&I2CB);

    uint16_t MasterSlave = HWREGH(I2CB.base + I2C_O_MDR);

    if(MasterSlave & I2C_MDR_MST)
    {
        //I2CB working in master configuration
        if(MasterSlave & I2C_MDR_TRX)
        {
           //I2CB working as Master Transmitter
           I2C_disableInterrupt(I2CB.base, (I2C_INT_TXFF));
        }
        else
        {
           //I2CB working as Master Receiver
           I2C_enableInterrupt(I2CA.base, (I2C_INT_TXFF));
           I2C_clearInterruptStatus(I2CA.base,(I2C_INT_TXFF));
        }
    }
   else
   {
       //I2CB working in slave configuration
       if(MasterSlave & I2C_MDR_TRX)
       {
           //I2CA = Master Receiver & I2CB = Slave Transmitter
           //So, I2CA RXFIFO interrupt is enabled  &
           //    I2CA TXFIFO interrupt is disabled
           I2C_enableInterrupt(I2CA.base, (I2C_INT_RXFF));
           I2C_disableInterrupt(I2CA.base, (I2C_INT_TXFF));
           I2C_clearInterruptStatus(I2CA.base,(I2C_INT_RXFF));

           I2C_disableInterrupt(I2CB.base, (I2C_INT_TXFF));
       }
       else
       {
           //I2CB working as slave receiver
           if(HWREGH(I2CA.base + I2C_O_CNT) == I2CA.NumOfAddrBytes)
           {
               //Enable I2CA Register Access Ready interrupt to change
               //to master receiver
               I2C_enableInterrupt(I2CA.base, I2C_INT_REG_ACCESS_RDY);
               if(I2CB.pTX_MsgBuffer == 0x0)
               {
                    I2CB.pTX_MsgBuffer = (uint16_t *)((uint32_t)(I2CB.pControlAddr) & 0x00FFFFFF);
                    I2CB.pRX_MsgBuffer = (uint16_t *)0;
               }
           }
           else
           {
               //Continue with I2CA master transmitter mode
               I2C_enableInterrupt(I2CA.base, (I2C_INT_TXFF));
               I2C_disableInterrupt(I2CA.base, (I2C_INT_RXFF));
               I2C_clearInterruptStatus(I2CA.base,(I2C_INT_TXFF | I2C_INT_RXFF));
               if(I2CB.pRX_MsgBuffer == 0x0)
               {
                   I2CB.pRX_MsgBuffer = (uint16_t *)((uint32_t)(I2CB.pControlAddr) & 0x00FFFFFF);
                   I2CB.pTX_MsgBuffer = (uint16_t *)0;
               }
           }
       }
   }

   Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

void I2C_GPIO_init(void)
{
    // I2CA pins (SDAA / SCLA)
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SDAA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SDAA, GPIO_PIN_TYPE_PULLUP);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SDAA, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SDAA, GPIO_QUAL_ASYNC);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCLA, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCLA, GPIO_PIN_TYPE_PULLUP);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCLA, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCLA, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SDAA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCLA);

    // I2CB pins (SDAB / SCLB)
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SDAB, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SDAB, GPIO_PIN_TYPE_PULLUP);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SDAB, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SDAB, GPIO_QUAL_ASYNC);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCLB, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCLB, GPIO_PIN_TYPE_PULLUP);
    GPIO_setMasterCore(DEVICE_GPIO_PIN_SCLB, GPIO_CORE_CPU1);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCLB, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SDAB);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCLB);
}

void I2Cinit(void)
{
    //I2CA initialization
    I2C_disableModule(I2CA_BASE);
    I2C_initMaster(I2CA_BASE, DEVICE_SYSCLK_FREQ, 100000, I2C_DUTYCYCLE_50);
    I2C_setConfig(I2CA_BASE, I2C_MASTER_SEND_MODE);
    I2C_setSlaveAddress(I2CA_BASE, 80);
    I2C_disableLoopback(I2CA_BASE);
    I2C_setBitCount(I2CA_BASE, I2C_BITCOUNT_8);
    I2C_setDataCount(I2CA_BASE, 2);
    I2C_setAddressMode(I2CA_BASE, I2C_ADDR_MODE_7BITS);
    I2C_enableFIFO(I2CA_BASE);
    I2C_clearInterruptStatus(I2CA_BASE, I2C_INT_ADDR_SLAVE | I2C_INT_ARB_LOST | I2C_INT_NO_ACK | I2C_INT_STOP_CONDITION);
    I2C_setFIFOInterruptLevel(I2CA_BASE, I2C_FIFO_TXEMPTY, I2C_FIFO_RX16);
    I2C_enableInterrupt(I2CA_BASE, I2C_INT_ADDR_SLAVE | I2C_INT_ARB_LOST | I2C_INT_NO_ACK | I2C_INT_STOP_CONDITION);
    I2C_setEmulationMode(I2CA_BASE, I2C_EMULATION_FREE_RUN);
    I2C_enableModule(I2CA_BASE);

    //I2CB initialization
    I2C_disableModule(I2CB_BASE);
    I2C_initMaster(I2CB_BASE, DEVICE_SYSCLK_FREQ, 100000, I2C_DUTYCYCLE_50);
    I2C_setConfig(I2CB_BASE, I2C_MASTER_SEND_MODE);
    I2C_setSlaveAddress(I2CB_BASE, 80);
    I2C_disableLoopback(I2CB_BASE);
    I2C_setBitCount(I2CB_BASE, I2C_BITCOUNT_8);
    I2C_setDataCount(I2CB_BASE, 2);
    I2C_setAddressMode(I2CB_BASE, I2C_ADDR_MODE_7BITS);
    I2C_enableFIFO(I2CB_BASE);
    I2C_clearInterruptStatus(I2CB_BASE, I2C_INT_ADDR_SLAVE | I2C_INT_ARB_LOST | I2C_INT_NO_ACK | I2C_INT_STOP_CONDITION);
    I2C_setFIFOInterruptLevel(I2CB_BASE, I2C_FIFO_TXEMPTY, I2C_FIFO_RX16);
    I2C_enableInterrupt(I2CB_BASE, I2C_INT_ADDR_SLAVE | I2C_INT_ARB_LOST | I2C_INT_NO_ACK | I2C_INT_STOP_CONDITION);
    I2C_setEmulationMode(I2CB_BASE, I2C_EMULATION_FREE_RUN);
    I2C_enableModule(I2CB_BASE);

}
//
// End of File
//


