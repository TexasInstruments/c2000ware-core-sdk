#ifndef DRIVER_INCLUSIVE_TERMINOLOGY_MAPPING_H_
#define DRIVER_INCLUSIVE_TERMINOLOGY_MAPPING_H_




//*****************************************************************************
// LIN
//*****************************************************************************
#define LIN_MODE_LIN_SLAVE          LIN_MODE_LIN_RESPONDER
#define LIN_MODE_LIN_MASTER         LIN_MODE_LIN_COMMANDER

#define LIN_MSG_FILTER_IDSLAVE      LIN_MSG_FILTER_IDRESPONDER

#define LIN_setIDSlaveTask          LIN_setIDResponderTask

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

//*****************************************************************************
// PMBUS
//*****************************************************************************
#define PMBUS_MASTER_ENABLE_PRC_CALL      PMBUS_CONTROLLER_ENABLE_PRC_CALL
#define PMBUS_MASTER_ENABLE_GRP_CMD       PMBUS_CONTROLLER_ENABLE_GRP_CMD
#define PMBUS_MASTER_ENABLE_PEC           PMBUS_CONTROLLER_ENABLE_PEC
#define PMBUS_MASTER_ENABLE_EXT_CMD       PMBUS_CONTROLLER_ENABLE_EXT_CMD
#define PMBUS_MASTER_ENABLE_CMD           PMBUS_CONTROLLER_ENABLE_CMD
#define PMBUS_MASTER_ENABLE_READ          PMBUS_CONTROLLER_ENABLE_READ
#define PMBUS_INT_SLAVE_ADDR_READY        PMBUS_INT_TARGET_ADDR_READY
#define PMBUS_SLAVE_ENABLE_MANUAL_ACK     PMBUS_TARGET_ENABLE_MANUAL_ACK
#define PMBUS_SLAVE_ENABLE_PEC_PROCESSING PMBUS_TARGET_ENABLE_PEC_PROCESSING
#define PMBUS_SLAVE_TRANSMIT_PEC          PMBUS_TARGET_TRANSMIT_PEC
#define PMBUS_SLAVE_ENABLE_MANUAL_CMD_ACK PMBUS_TARGET_ENABLE_MANUAL_CMD_ACK
#define PMBUS_SLAVE_DISABLE_ADDRESS_MASK  PMBUS_TARGET_DISABLE_ADDRESS_MASK
#define PMBUS_SLAVE_AUTO_ACK_1_BYTES      PMBUS_TARGET_AUTO_ACK_1_BYTES
#define PMBUS_SLAVE_AUTO_ACK_2_BYTES      PMBUS_TARGET_AUTO_ACK_2_BYTES
#define PMBUS_SLAVE_AUTO_ACK_3_BYTES      PMBUS_TARGET_AUTO_ACK_3_BYTES
#define PMBUS_SLAVE_AUTO_ACK_4_BYTES      PMBUS_TARGET_AUTO_ACK_4_BYTES
#define PMBUS_ENABLE_SLAVE_ALERT          PMBUS_ENABLE_TARGET_ALERT
#define PMBUS_ENABLE_SLAVE_MODE           PMBUS_ENABLE_TARGET_MODE
#define PMBUS_ENABLE_MASTER_MODE          PMBUS_ENABLE_CONTROLLER_MODE
#define PMBUS_INTSRC_SLAVE_ADDR_READY     PMBUS_INTSRC_TARGET_ADDR_READY
#define PMBus_getMasterData               PMBus_getControllerData
#define PMBus_getSlaveData                PMBus_getTargetData

#define PMBus_configMaster                PMBus_configControlleer
#define PMBus_putMasterData               PMBus_putControllerData
#define PMBus_putSlaveData                PMBus_putTargetData
#define PMBus_initSlaveMode               PMBus_initTargetMode
#define PMBus_initMasterMode              PMBus_initControllerMode

#endif /* DRIVER_INCLUSIVE_TERMINOLOGY_MAPPING_H_ */
