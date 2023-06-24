#ifndef HW_REG_INCLUSIVE_TERMINOLOGY_H
#define HW_REG_INCLUSIVE_TERMINOLOGY_H



//*****************************************************************************
// SPI
//*****************************************************************************
#define SPI_CTL_CONTROLLER_PERIPHERAL    SPI_CTL_MASTER_SLAVE
#define SPI_PRI_PTEINV                   SPI_PRI_STEINV

//*****************************************************************************
// I2C
//*****************************************************************************
#define I2C_O_TAR         I2C_O_SAR

#define I2C_TAR_TAR_S     I2C_SAR_SAR_S
#define I2C_TAR_TAR_M     I2C_SAR_SAR_M

#define I2C_IER_AAT       I2C_IER_AAS

#define I2C_STR_AAT       I2C_STR_AAS
#define I2C_STR_TDIR      I2C_STR_SDIR

#define I2C_MDR_CNT       I2C_MDR_MST



#endif // HW_REG_INCLUSIVE_TERMINOLOGY_H
