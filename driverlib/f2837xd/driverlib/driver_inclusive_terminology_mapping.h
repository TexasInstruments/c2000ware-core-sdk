#ifndef DRIVER_INCLUSIVE_TERMINOLOGY_MAPPING_H_
#define DRIVER_INCLUSIVE_TERMINOLOGY_MAPPING_H_


//*****************************************************************************
// CLB
//*****************************************************************************
#define CLB_LOCAL_IN_MUX_SPISIMO_SLAVE          CLB_LOCAL_IN_MUX_SPIPICO_PERIPHERAL
#define CLB_LOCAL_IN_MUX_SPISIMO_MASTER         CLB_LOCAL_IN_MUX_SPIPICO_CONTROLLER
#define CLB_GLOBAL_IN_MUX_SPI1_SPISOMI_MASTER   CLB_GLOBAL_IN_MUX_SPI1_SPIPOCI_CONTROLLER
#define CLB_GLOBAL_IN_MUX_SPI1_SPISTE           CLB_GLOBAL_IN_MUX_SPI1_SPIPTE
#define CLB_GLOBAL_IN_MUX_SPI2_SPISOMI_MASTER   CLB_GLOBAL_IN_MUX_SPI2_SPIPOCI_CONTROLLER
#define CLB_GLOBAL_IN_MUX_SPI2_SPISTE           CLB_GLOBAL_IN_MUX_SPI2_SPIPTE
#define CLB_GLOBAL_IN_MUX_SPI3_SPISOMI_MASTER   CLB_GLOBAL_IN_MUX_SPI3_SPIPOCI_CONTROLLER
#define CLB_GLOBAL_IN_MUX_SPI3_SPISTE           CLB_GLOBAL_IN_MUX_SPI3_SPIPTE
#define CLB_GLOBAL_IN_MUX_SPI4_SPISOMI_MASTER   CLB_GLOBAL_IN_MUX_SPI4_SPIPOCI_CONTROLLER
#define CLB_GLOBAL_IN_MUX_SPI4_SPISTE           CLB_GLOBAL_IN_MUX_SPI4_SPIPTE



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
#define SYSCTL_SEC_MASTER_CLA   SYSCTL_SEC_CONTROLLER_CLA
#define SYSCTL_SEC_MASTER_DMA   SYSCTL_SEC_CONTROLLER_DMA
#define SysCtl_selectSecMaster  SysCtl_selectSecController


//*****************************************************************************
// GPIO
//*****************************************************************************
#define GPIO_setMasterCore GPIO_setControllerCore



//*****************************************************************************
// Memcfg
//*****************************************************************************
#define MemCfg_LSRAMMMasterSel          MemCfg_LSRAMMControllerSel
#define MEMCFG_LSRAMMASTER_CPU_ONLY     MEMCFG_LSRAMCONTROLLER_CPU_ONLY
#define MEMCFG_LSRAMMASTER_CPU_CLA1     MEMCFG_LSRAMCONTROLLER_CPU_CLA1
#define MemCfg_setLSRAMMasterSel        MemCfg_setLSRAMControllerSel

#define MemCfg_GSRAMMasterSel           MemCfg_GSRAMControllerSel
#define MEMCFG_GSRAMMASTER_CPU1         MEMCFG_GSRAMCONTROLLER_CPU1
#define MEMCFG_GSRAMMASTER_CPU2         MEMCFG_GSRAMCONTROLLER_CPU2
#define MemCfg_setGSRAMMasterSel        MemCfg_setGSRAMControllerSel

//*****************************************************************************
// EMIF
//*****************************************************************************
#define EMIF_MasterSelect               EMIF_ControllerSelect
#define EMIF_selectMaster               EMIF_selectController
#define EMIF_MASTER_CPU1_NG             EMIF_CONTROLLER_CPU1_NG
#define EMIF_MASTER_CPU1_G              EMIF_CONTROLLER_CPU1_G
#define EMIF_MASTER_CPU2_G              EMIF_CONTROLLER_CPU2_G
#define EMIF_MASTER_CPU1_NG2            EMIF_CONTROLLER_CPU1_NG2


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
// SDFM
//*****************************************************************************
#define SDFM_enableMasterInterrupt      SDFM_enableMainInterrupt
#define SDFM_disableMasterInterrupt     SDFM_disableMainInterrupt
#define SDFM_enableMasterFilter         SDFM_enableMainFilter
#define SDFM_disableMasterFilter        SDFM_disableMainFilter

#define SDFM_MASTER_INTERRUPT_FLAG      SDFM_MAIN_INTERRUPT_FLAG

#endif /* DRIVER_INCLUSIVE_TERMINOLOGY_MAPPING_H_ */
