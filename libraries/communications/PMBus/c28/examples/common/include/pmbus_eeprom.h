//###########################################################################
//
// FILE:   pmbus_eeprom.h
//
// TITLE:  PMBus EEPROM APIs
//
//###########################################################################
//
//
// $Copyright: Copyright (C) 2015-2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef PMBUSEEPROM_H
#define PMBUSEEPROM_H

//
// Includes
//
#include "driverlib.h"
#include "pmbus.h"
#include "device.h"

//
// Defines
//
#define TARGET_ADDRESS               0x50U
#define EEPROM_HIGH_ADDR            0x00U
#define EEPROM_LOW_ADDR             0x00U
#define EEPROM_ADDRESS_BYTES        2U

//
// EEPROM used for this example AT24C256
// (http://www.ti.com/lit/an/slaa208a/slaa208a.pdf)
// Macros specific to AT24C256
//
#define EEPROM_PAGE_SIZE            64U    //64 bytes
#define EEPROM_TOTAL_BYTES          32768U //256K bits (or) 32K bytes
#define EEPROM_MAX_NUM_PAGE         (EEPROM_TOTAL_BYTES / EEPROM_PAGE_SIZE)
#define EEPROM_MAX_WRITE_CYCLE      5U     //5ms

#define WRITE_DELAY_TIME            ((((EEPROM_MAX_WRITE_CYCLE * SYSCLK_FREQ)/1000U)-9U)/5U)
#define DELAY_TIME_MICROSECS(x)     SysCtl_delay(((x * (uint32_t)100U)-9U)/5U)

//
// To change the PMBus module used. Default to PMBus-A
//
#define BASE                        (uint32_t)PMBUSA_BASE

#define PMBUS_READ                  1U
#define PMBUS_WRITE                 0U

//
// Return codes
//
#define BUS_BUSY_ERROR              0x1000U
#define ARBITRATION_LOST_ERROR      0x2000U
#define TARGET_NOT_READY_ERROR       0x3000U
#define SUCCESS                     0x0000U

//
// Enumeration for number of bytes
//
typedef enum
{
  ONE_BYTE    = 1,
  TWO_BYTES   = 2,
  THREE_BYTES = 3,
  FOUR_BYTES  = 4
} byteCount_t;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
//*****************************************************************************
//
// Configure PMBus to use default timing parameters
//
// param: base is the base address of the PMBus instance used.
//
// return None.
//
//*****************************************************************************
static inline void PMBus_setDefaultTimingParameter(uint32_t base)
{
    EALLOW;
    HWREG(base + PMBUS_O_PMBTIMCTL) &= ~(uint32_t)PMBUS_PMBTIMCTL_TIM_OVERRIDE;
    EDIS;
}

//*****************************************************************************
//
// Check if the PMBus interface is busy
//
// param: status is the value read from the PMBus status register
//
// return Interface is free returns true, otherwise false.
//
//*****************************************************************************
static inline bool PMBus_isUnitFree(uint32_t status)
{
    return(((status & PMBUS_PMBSTS_UNIT_BUSY) == 0U) ? true : false);
}

//*****************************************************************************
//
// Check if the PMBus SCL pin is high or low
//
// param: status is the value read from the PMBus status register
//
// return SCL is high returns true, otherwise false.
//
//*****************************************************************************
static inline bool PMBus_isSCLHigh(uint32_t status)
{
    return(((status & PMBUS_PMBSTS_SCL_RAW) == 0U) ? false : true);
}

//*****************************************************************************
//
// Check if the PMBus SDA pin is high or low
//
// param: status is the value read from the PMBus status register
//
// return SDA is high returns true, otherwise false.
//
//*****************************************************************************
static inline bool PMBus_isSDAHigh(uint32_t status)
{
    return(((status & PMBUS_PMBSTS_SDA_RAW) == 0U) ? false : true);
}

//*****************************************************************************
//
// Check if the PMBus bus is free
//
// param: status is the value read from the PMBus status register
//
// return Bus is free returns true, otherwise false.
//
//*****************************************************************************
static inline bool PMBus_isBusFree(uint32_t status)
{
    return(((status & PMBUS_PMBSTS_BUS_FREE) == 0U) ? false : true);
}

//*****************************************************************************
//
// Check if the PMBus received NACK
//
// param: status is the value read from the PMBus status register
//
// return NACK is received returns true, otherwise false.
//
//*****************************************************************************
static inline bool PMBus_isNackReceived(uint32_t status)
{
    return(((status & PMBUS_PMBSTS_NACK)) ? true : false);
}

//*****************************************************************************
//
// Check if the PMBus received EOM
//
// param: status is the value read from the PMBus status register
//
// return EOM is received returns true, otherwise false.
//
//*****************************************************************************
static inline bool PMBus_isEOMReceived(uint32_t status)
{
    return(((status & PMBUS_PMBSTS_EOM)) ? true : false);
}

//*****************************************************************************
//
// Check if the PMBus received data ready
//
// param: status is the value read from the PMBus status register
//
// return data ready is received returns true, otherwise false.
//
//*****************************************************************************
static inline bool PMBus_isDataReadyReceived(uint32_t status)
{
    return(((status & PMBUS_PMBSTS_DATA_READY)) ? true : false);
}

//*****************************************************************************
//
// Check if the PMBus received data request
//
// param: status is the value read from the PMBus status register
//
// return data request is received returns true, otherwise false.
//
//*****************************************************************************
static inline bool PMBus_isDataRequestReceived(uint32_t status)
{
    return(((status & PMBUS_PMBSTS_DATA_REQUEST)) ? true : false);
}

//*****************************************************************************
//
// Check if the PMBus received ACK
//
// param: status is the value read from the PMBus status register
//
// return ACK is received returns true, otherwise false.
//
//*****************************************************************************
static inline bool PMBus_isAckReceived(uint32_t status)
{
    return(((status & PMBUS_PMBSTS_NACK)) ? false : true);
}

//*****************************************************************************
//
// Check if the PMBus lost arbitration
//
// param: status is the value read from the PMBus status register
//
// return PMBus controller lost arbitration returns true, otherwise false.
//
//*****************************************************************************
static inline bool PMBus_isArbitrationLost(uint32_t status)
{
    return(((status & PMBUS_PMBSTS_LOST_ARB)) ? true : false);
}

//*****************************************************************************
//
// Write a byte of data to EEPROM
//
// param: eepromAddress is the EEPROM memory address
// param: data is the byte data to be written
//
// return API execution status
//        SUCCESS - Returned for successful completion
//        BUS_BUSY_ERROR - Returned if error due to busy being busy
//        ARBITRATION_LOST_ERROR - Returned if error due to losing arbitration
//        TARGET_NOT_READY_ERROR - Returned if received NACK from target
//
//*****************************************************************************
extern uint16_t PMBusEEPROM_writeByte(uint16_t eepromAddress, uint16_t data);

//*****************************************************************************
//
// Write a page of data to EEPROM
//
// param: eepromAddress is the EEPROM memory address
// param: pbuffer is a pointer to an array of data
// param: numOfBytes is the number of bytes of data in the buffer
//
// return API execution status
//        SUCCESS - Returned for successful completion
//        BUS_BUSY_ERROR - Returned if error due to busy being busy
//        ARBITRATION_LOST_ERROR - Returned if error due to losing arbitration
//        TARGET_NOT_READY_ERROR - Returned if received NACK from target
//
//*****************************************************************************
extern uint16_t PMBusEEPROM_writePage(uint16_t eepromAddress, uint16_t *pbuffer,
                                      uint16_t numOfBytes);

//*****************************************************************************
//
// Read data from current EEPROM address
//
// param: pbuffer is a pointer to an array for storing received data
// param: numOfBytes is the number of bytes to read (1 to 4 bytes)
//
// return API execution status
//        SUCCESS - Returned for successful completion
//        BUS_BUSY_ERROR - Returned if error due to busy being busy
//        ARBITRATION_LOST_ERROR - Returned if error due to losing arbitration
//        TARGET_NOT_READY_ERROR - Returned if received NACK from target
//
//*****************************************************************************
extern uint16_t PMBusEEPROM_readCurrentAddress(uint16_t* pbuffer,
                                               byteCount_t numOfBytes);

//*****************************************************************************
//
// Read up to 4 bytes of data from EEPROM address
//
// param: eepromAddress is the EEPROM memory address
// param: pbuffer is a pointer to an array for storing received data
// param: numOfBytes is the number of bytes to read (1 to 4 bytes)
//
// return API execution status
//        SUCCESS - Returned for successful completion
//        BUS_BUSY_ERROR - Returned if error due to busy being busy
//        ARBITRATION_LOST_ERROR - Returned if error due to losing arbitration
//        TARGET_NOT_READY_ERROR - Returned if received NACK from target
//
//*****************************************************************************
extern uint16_t PMBusEEPROM_performSequentialRead(uint16_t eepromAddress,
                                                  uint16_t* pbuffer,
                                                  uint16_t numOfBytes);

//*****************************************************************************
//
// Read up to 255 bytes of data starting from EEPROM address
//
// param: eepromAddress is the EEPROM memory address
// param: pbuffer is a pointer to an array for storing received data
// param: numOfBytes is the number of bytes to read (1 to 255 bytes)
//
// return API execution status
//        SUCCESS - Returned for successful completion
//        BUS_BUSY_ERROR - Returned if error due to busy being busy
//        ARBITRATION_LOST_ERROR - Returned if error due to losing arbitration
//        TARGET_NOT_READY_ERROR - Returned if received NACK from target
//
//*****************************************************************************
extern uint16_t PMBusEEPROM_performRandomRead(uint16_t eepromAddress,
                                              uint16_t * pbuffer,
                                              byteCount_t numOfBytes);

//*****************************************************************************
//
// Wait for PMBus target ACK or NACK
//
//
// return API execution status
//        SUCCESS - Returned for successful completion (ACK)
//        TARGET_NOT_READY_ERROR - Returned if received NACK from target
//
//*****************************************************************************
extern uint16_t PMBusEEPROM_waitForAck(void);

//*****************************************************************************
//
// Transmit only the Target Address + EEPROM Address (No Data)
//
// param: eepromAddress is the EEPROM memory address
//
// return API execution status
//        SUCCESS - Returned for successful completion
//        BUS_BUSY_ERROR - Returned if error due to busy being busy
//        ARBITRATION_LOST_ERROR - Returned if error due to losing arbitration
//        TARGET_NOT_READY_ERROR - Returned if received NACK from target
//
//*****************************************************************************
extern uint16_t PMBusEEPROM_transmitAddress(uint16_t eepromAddress);

#endif // PMBUSEEPROM_H

//
// End of file
//
