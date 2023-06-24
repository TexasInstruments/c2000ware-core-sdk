#ifndef DRIVER_INCLUSIVE_TERMINOLOGY_MAPPING_H_
#define DRIVER_INCLUSIVE_TERMINOLOGY_MAPPING_H_





//*****************************************************************************
// SPI
//*****************************************************************************
#define SPI_MODE_SLAVE              SPI_MODE_PERIPHERAL
#define SPI_MODE_MASTER             SPI_MODE_CONTROLLER
#define SPI_MODE_SLAVE_OD           SPI_MODE_PERIPHERAL_OD
#define SPI_MODE_MASTER_OD          SPI_MODE_CONTROLLER_OD

#define SPI_STE_ACTIVE_LOW          SPI_PTE_ACTIVE_LOW
#define SPI_STE_ACTIVE_HIGH         SPI_PTE_ACTIVE_HIGH

#define SPI_setSTESignalPolarity    SPI_setPTESignalPolarity


//*****************************************************************************
// Interrupt
//*****************************************************************************
#define Interrupt_enableMaster      Interrupt_enableGlobal
#define Interrupt_disableMaster     Interrupt_disableGlobal


//*****************************************************************************
// SysCtrl
//*****************************************************************************
#define SysCtl_AccessMaster     SysCtl_AccessController






//*****************************************************************************
// I2C
//*****************************************************************************
#define I2C_MASTER_SEND_MODE              I2C_CONTROLLER_SEND_MODE
#define I2C_MASTER_RECEIVE_MODE           I2C_CONTROLLER_RECEIVE_MODE
#define I2C_SLAVE_SEND_MODE               I2C_TARGET_SEND_MODE
#define I2C_SLAVE_RECEIVE_MODE            I2C_TARGET_RECEIVE_MODE
#define I2C_INT_ADDR_SLAVE                I2C_INT_ADDR_TARGET
#define I2C_STS_ADDR_SLAVE                I2C_STS_ADDR_TARGET
#define I2C_STS_SLAVE_DIR                 I2C_STS_TARGET_DIR
#define I2C_INTSRC_ADDR_SLAVE             I2C_INTSRC_ADDR_TARGET

#define I2C_initMaster                    I2C_initController
#define I2C_setSlaveAddress               I2C_setTargetAddress
#define I2C_setOwnSlaveAddress            I2C_setOwnAddress


#endif /* DRIVER_INCLUSIVE_TERMINOLOGY_MAPPING_H_ */
