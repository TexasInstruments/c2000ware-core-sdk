//###########################################################################
//
// FILE:   pmbus_eeprom.c
//
// TITLE:  PMBus EEPROM APIs
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2023 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Includes
//
#include "pmbus_eeprom.h"

//*****************************************************************************
//
// dummyWrite
//
//*****************************************************************************
void dummyWrite(void)
{
    uint16_t txbuf = 0U;

    //
    // Write 1 byte of data
    //
    PMBus_putControllerData(BASE, &txbuf, ONE_BYTE);
    PMBus_configController(BASE, TARGET_ADDRESS, ONE_BYTE, PMBUS_WRITE);

    //
    // Wait until PMBus is free
    //
    DELAY_TIME_MICROSECS(400);  //Wait till PMBus is free
}

//*****************************************************************************
//
// waitUntilBusBusy
//
//*****************************************************************************
uint32_t waitUntilBusBusy(void)
{
    uint32_t PMBusStatus;

    //
    // Poll status until PMBus interface is free
    //
    while(1)
    {
        PMBusStatus = PMBus_getStatus(BASE);

        if(PMBus_isUnitFree(PMBusStatus))
        {
           DELAY_TIME_MICROSECS(100);
           break;
        }
    }

    return PMBusStatus;
}

//*****************************************************************************
//
// isWritecycleComplete
//
//*****************************************************************************
void isWritecycleComplete(void)
{
    //
    // Read PMBus status
    //
    uint32_t PMBusStatus = PMBus_getStatus(BASE);

    //
    // Dummy write data until EOM received and ACK received
    //
    while(1U)
    {
        dummyWrite();

        PMBusStatus = waitUntilBusBusy();

        if(PMBus_isEOMReceived(PMBusStatus))
        {
            if(PMBus_isAckReceived(PMBusStatus))
            {
               break;
            }
        }
    }

    dummyWrite();
}

//*****************************************************************************
//
// checkBusStatus
//
//*****************************************************************************
uint16_t checkBusStatus(void)
{
    //
    // Read PMBus status
    //
    uint32_t PMBusStatus = PMBus_getStatus(BASE);

    //
    // Report any identified bus errors
    //
    if(PMBus_isBusBusy(PMBusStatus))
    {
        return BUS_BUSY_ERROR;
    }
    if(PMBus_isArbitrationLost(PMBusStatus))
    {
        return ARBITRATION_LOST_ERROR;
    }

    return SUCCESS;
}

//*****************************************************************************
//
// waitUntilEOM
//
//*****************************************************************************
uint32_t waitUntilEOM(void)
{
    uint32_t PMBusStatus;

    //
    // Poll status for EOM until received
    //
    while(1)
    {
        PMBusStatus |= PMBus_getStatus(BASE);

        if(PMBus_isEOMReceived(PMBusStatus))
        {
           break;
        }
    }

    return PMBusStatus;
}

//*****************************************************************************
//
// waitUntilSCLHigh
//
//*****************************************************************************
uint32_t waitUntilSCLHigh(void)
{
    uint32_t PMBusStatus;

    //
    // Poll status until SCL goes high
    //
    while(1)
    {
        PMBusStatus = PMBus_getStatus(BASE);

        if(PMBus_isSCLHigh(PMBusStatus))
        {
           break;
        }
    }

    return PMBusStatus;
}

//*****************************************************************************
//
// waitUntilSDAHigh
//
//*****************************************************************************
uint32_t waitUntilSDAHigh(void)
{
    uint32_t PMBusStatus;

    //
    // Poll status until SDA goes high
    //
    while(1)
    {
        PMBusStatus = PMBus_getStatus(BASE);

        if(PMBus_isSDAHigh(PMBusStatus))
        {
           break;
        }
    }

    return PMBusStatus;
}

//*****************************************************************************
//
// PMBusEEPROM_transmitAddress
//
//*****************************************************************************
uint16_t PMBusEEPROM_transmitAddress(uint16_t eepromAddress)
{
    uint16_t status = SUCCESS;

    //
    // Confirm bus is ready/free
    //
    status = checkBusStatus();

    if(status)
    {
        return status;
    }

    uint16_t txbuf[2];

    txbuf[0] = (eepromAddress & 0xFF00U) >> 8U;
    txbuf[1] = (eepromAddress & 0xFFU);

    //
    // Target Address + PMBus_eeprom address is transmitted in WRITE mode
    //
    PMBus_configController(BASE, TARGET_ADDRESS, TWO_BYTES , PMBUS_WRITE);

    PMBus_putControllerData(BASE, txbuf, TWO_BYTES);

    status = PMBusEEPROM_waitForAck();

    waitUntilBusBusy();

    return status;
}

//*****************************************************************************
//
// PMBusEEPROM_writeByte
//
//*****************************************************************************
uint16_t PMBusEEPROM_writeByte(uint16_t eepromAddress, uint16_t data)
{
    ASSERT(data <= 0xFFU);

    uint16_t totalBytes = ONE_BYTE + TWO_BYTES;
    uint16_t txbuf[3];
    uint16_t status = SUCCESS;

    //
    // Confirm bus is ready/free
    //
    status = checkBusStatus();

    if(status)
    {
        return status;
    }

    txbuf[0] = (eepromAddress & 0xFF00) >> 8;
    txbuf[1] = (eepromAddress & 0xFF);
    txbuf[2] = (uint16_t)data;

    //
    // Target Address + PMBus_eeprom address + databyte to be
    // programmed is transmitted in write mode
    //
    PMBus_configController(BASE, TARGET_ADDRESS, totalBytes , PMBUS_WRITE);

    PMBus_putControllerData(BASE, txbuf, totalBytes);
    status = PMBusEEPROM_waitForAck();

    if(status)
    {
        return status;
    }

    isWritecycleComplete();

    return status;
}

//*****************************************************************************
//
// PMBusEEPROM_writePage
//
//*****************************************************************************
uint16_t PMBusEEPROM_writePage(uint16_t eepromAddress, uint16_t *pbuffer,
                               uint16_t numOfBytes)
{
    ASSERT(numOfBytes<=EEPROM_PAGE_SIZE);

    uint16_t totalBytes = numOfBytes + 2U;
    uint16_t numofFourByte  = totalBytes / 4U;
    uint16_t remainingBytes = totalBytes % 4U;
    uint16_t status = SUCCESS;

    //
    // Confirm bus is ready/free
    //
    status = checkBusStatus();

    if(status)
    {
        return status;
    }

    *(pbuffer + 0) = (eepromAddress & 0xFF00U) >> 8U;
    *(pbuffer + 1) = (eepromAddress & 0xFFU);

    uint16_t count;

    //
    // Target Address + PMBus_eeprom address + batch of 4 bytes of data
    // is transmitted at a time in WRITE mode
    //
    PMBus_configController(BASE, TARGET_ADDRESS, totalBytes, PMBUS_WRITE);

    for(count = 1U; count <= numofFourByte; count++)
    {
        PMBus_putControllerData(BASE, pbuffer, FOUR_BYTES);

        status = PMBusEEPROM_waitForAck();

        if(status)
        {
            return status;
        }

        pbuffer = pbuffer + FOUR_BYTES;
    }

    if(remainingBytes)
    {
       PMBus_putControllerData(BASE, pbuffer, remainingBytes);
       status = PMBusEEPROM_waitForAck();
    }

    if(status)
    {
        return status;
    }

    isWritecycleComplete();

    return status;
}

//*****************************************************************************
//
// PMBusEEPROM_readCurrentAddress
//
//*****************************************************************************
uint16_t PMBusEEPROM_readCurrentAddress(uint16_t* pbuffer, byteCount_t numOfBytes)
{
    ASSERT(numOfBytes <= FOUR_BYTES);

	uint16_t status = SUCCESS;

    //
    // Confirm bus is ready/free
    //
	status = checkBusStatus();

    if(status)
    {
        //
        // Halted due to bus not ready/free
        //
        ESTOP0;
        return status;
    }

    PMBus_configController(BASE, TARGET_ADDRESS, numOfBytes, PMBUS_READ);

    status = PMBusEEPROM_waitForAck();

    if(status)
    {
        return status;
    }

    //
    // Read current address
    //
    PMBus_getData(BASE, pbuffer, numOfBytes);

    waitUntilBusBusy();

    return status;
}

//*****************************************************************************
//
// PMBusEEPROM_performRandomRead
//
//*****************************************************************************
uint16_t PMBusEEPROM_performRandomRead(uint16_t eepromAddress,
                                       uint16_t * pbuffer, byteCount_t numOfBytes)
{
    ASSERT(numOfBytes <= FOUR_BYTES);

    //
    // Transmit Target address + EEPROM address
    //
    uint16_t status = PMBusEEPROM_transmitAddress(eepromAddress);

    if(status)
    {
        return status;
    }

    //
    // Target Address + PMBus_eeprom address + batch of 4 bytes of data
    // is read in WRITE mode
    //
    PMBus_configController(BASE, TARGET_ADDRESS, numOfBytes, PMBUS_READ);
    status = PMBusEEPROM_waitForAck();

    if(status)
    {
        return status;
    }

    PMBus_getControllerData(BASE, pbuffer, FOUR_BYTES);

    waitUntilBusBusy();

    return status;
}

//*****************************************************************************
//
// PMBusEEPROM_performSequentialRead
//
//*****************************************************************************
uint16_t PMBusEEPROM_performSequentialRead(uint16_t eepromAddress,
                                           uint16_t * pbuffer, uint16_t numOfBytes)
{
    ASSERT(numOfBytes <= 0xFFU);

    //
    // Transmit Target address + EEPROM address
    //
    uint16_t status = PMBusEEPROM_transmitAddress(eepromAddress);

    if(status)
    {
        return status;
    }

    uint16_t totalBytes = numOfBytes;

    uint16_t numofFourByte  = totalBytes / 4;
    uint16_t remainingBytes = totalBytes % 4;

    uint16_t count;

    //
    // Receive 4 bytes of data at a time in READ mode
    //
    PMBus_configController(BASE, TARGET_ADDRESS, totalBytes, PMBUS_READ);

    for(count = 1U; count <= numofFourByte; count++)
    {
        status = PMBusEEPROM_waitForAck();

        if(status)
        {
            return status;
        }

        PMBus_getControllerData(BASE, pbuffer, FOUR_BYTES);

        pbuffer = pbuffer + FOUR_BYTES;
    }

    if(remainingBytes)
    {
        status = PMBusEEPROM_waitForAck();

        if(status)
        {
            return status;
        }

       PMBus_getControllerData(BASE, pbuffer, remainingBytes);
    }

    if(status)
    {
        return status;
    }

    waitUntilBusBusy();

    return status;
}

//*****************************************************************************
//
// PMBusEEPROM_waitForAck
//
//*****************************************************************************
uint16_t PMBusEEPROM_waitForAck(void)
{
    uint32_t PMBusStatus = 0;
    uint16_t status = SUCCESS;

    //
    // Poll PMBus status until NACK, ACK, data request,
    // or data ready occurs
    //
    while(1)
    {
        PMBusStatus |= PMBus_getStatus(BASE);

        if(PMBus_isEOMReceived(PMBusStatus))
        {
            if(PMBus_isNackReceived(PMBusStatus))
            {
                status = TARGET_NOT_READY_ERROR;
                break;
            }
            else
            {
                //
                // Received ACK from target
                //
                status = SUCCESS;
                break;
            }
        }

        if(PMBus_isDataRequestReceived(PMBusStatus))
        {
            status = SUCCESS;
            break;
        }

        if(PMBus_isDataReadyReceived(PMBusStatus))
        {
            status = SUCCESS;
            break;
        }
    }

    return status;
}

//
// End of file
//
