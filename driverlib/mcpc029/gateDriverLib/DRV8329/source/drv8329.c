//#############################################################################
//
// FILE:   drv8329.c
//
// TITLE:  Drivers for DRV8329 with generic communication interface
//
//#############################################################################
// $Copyright:
// Copyright (C) 2026 Texas Instruments Incorporated - http://www.ti.com/
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

#include "drv8329.h"
#include "gateDriver.h"

//*****************************************************************************
//
// DRV8329_clearFaults
//
//*****************************************************************************
void DRV8329_clearFaults(void)
{
    uint16_t registerValue = DRV8329_CLEAR_CLR_FLT;
    DRV_Interface_WriteRegister(DRV8329_O_CLEAR, registerValue);
}

//*****************************************************************************
//
// DRV8329_disableDrv
//
//*****************************************************************************
void DRV8329_disableDrv(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL2);
    registerValue = registerValue | (DRV8329_CTRL2_DIS_DRV);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL2,registerValue);
}

//*****************************************************************************
//
// DRV8329_enableDrv
//
//*****************************************************************************
void DRV8329_enableDrv(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL2);
    registerValue = registerValue & ~(DRV8329_CTRL2_DIS_DRV);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL2,registerValue);
}

//*****************************************************************************
//
// DRV8329_disableSnsFault
//
//*****************************************************************************
void DRV8329_disableSnsFault(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL1);
    registerValue = registerValue | (DRV8329_CTRL1_DIS_SNS_FLT);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL1,registerValue);
}

//*****************************************************************************
//
// DRV8329_enableSnsFault
//
//*****************************************************************************
void DRV8329_enableSnsFault(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL1);
    registerValue = registerValue & ~(DRV8329_CTRL1_DIS_SNS_FLT);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL1,registerValue);
}

//*****************************************************************************
//
// DRV8329_disableVdsFault
//
//*****************************************************************************
void DRV8329_disableVdsFault(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL1);
    registerValue = registerValue | (DRV8329_CTRL1_DIS_VDS_FLT);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL1,registerValue);
}

//*****************************************************************************
//
// DRV8329_enableVdsFault
//
//*****************************************************************************
void DRV8329_enableVdsFault(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL1);
    registerValue = registerValue & ~(DRV8329_CTRL1_DIS_VDS_FLT);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL1,registerValue);
}

//*****************************************************************************
//
// DRV8329_setVdsLevel
//
//*****************************************************************************
void DRV8329_setVdsLevel(DRV8329_VdsLevel level){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL1);
    registerValue = ((registerValue & ~(DRV8329_CTRL1_SEL_VDSLVL_M)) | 
                        ((level << DRV8329_CTRL1_SEL_VDSLVL_S) & 
                            DRV8329_CTRL1_SEL_VDSLVL_M));
    DRV_Interface_WriteRegister(DRV8329_O_CTRL1,registerValue);
}

//*****************************************************************************
//
// DRV8329_disableBstFault
//
//*****************************************************************************
void DRV8329_disableBstFault(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL2);
    registerValue = registerValue | (DRV8329_CTRL2_DIS_BST_FLT);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL2,registerValue);
}

//*****************************************************************************
//
// DRV8329_enableBstFault
//
//*****************************************************************************
void DRV8329_enableBstFault(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL2);
    registerValue = registerValue & ~(DRV8329_CTRL2_DIS_BST_FLT);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL2,registerValue);
}

//*****************************************************************************
//
// DRV8329_setOtsRecoveryMode
//
//*****************************************************************************
void DRV8329_setOtsRecoveryMode(DRV8329_OtsRecoveryMode option){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL2);
    registerValue = (registerValue & ~(DRV8329_CTRL2_OTS_AUTO_RECOVER)) | 
                        option;
    DRV_Interface_WriteRegister(DRV8329_O_CTRL2,registerValue);
}

//*****************************************************************************
//
// DRV8329_disableVdsLevelSelectionThroughSpi
//
//*****************************************************************************
void DRV8329_disableVdsLevelSelectionThroughSpi(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL1);
    registerValue = registerValue & ~(DRV8329_CTRL1_SEL_VDS_SPI);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL1,registerValue);
}

//*****************************************************************************
//
// DRV8329_enableVdsLevelSelectionThroughSpi
//
//*****************************************************************************
void DRV8329_enableVdsLevelSelectionThroughSpi(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL1);
    registerValue = registerValue | (DRV8329_CTRL1_SEL_VDS_SPI);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL1,registerValue);
}

//*****************************************************************************
//
// DRV8329_disableTcp
//
//*****************************************************************************
void DRV8329_disableTcp(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL2);
    registerValue = registerValue | (DRV8329_CTRL2_DIS_TCP);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL2,registerValue);
}

//*****************************************************************************
//
// DRV8329_enableTcp
//
//*****************************************************************************
void DRV8329_enableTcp(void){
    uint16_t registerValue = DRV_Interface_ReadRegister(DRV8329_O_CTRL2);
    registerValue = registerValue & ~(DRV8329_CTRL2_DIS_TCP);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL2,registerValue);
}

//*****************************************************************************
//
// DRV8329_configureParams
//
//*****************************************************************************
void DRV8329_configureParams(DRV8329_CONFIG_T *config)
{
    uint16_t drv8329_ctrl_config = 0x00;

    //
    // Configure DRV8329 CTRL1 register
    //
    drv8329_ctrl_config = (DRV8329_CTRL1_REG_DEFAULT_CONFIG |
                            (DRV8329_CTRL1_REG_DEFAULT_MASK & 
                                ((config->gateDrvCfg1.w & GD1_CTRL1_MASK) 
                                    >> GD1_CTRL1_SHIFT)));
    DRV_Interface_WriteRegister(DRV8329_O_CTRL1, drv8329_ctrl_config);

    //
    // Configure DRV8329 CTRL2 register
    //
    drv8329_ctrl_config = (DRV8329_CTRL2_REG_DEFAULT_CONFIG |
                            (DRV8329_CTRL2_REG_DEFAULT_MASK & 
                                ((config->gateDrvCfg1.w & GD1_CTRL2_MASK) 
                                    >> GD1_CTRL2_SHIFT)));
    DRV_Interface_WriteRegister(DRV8329_O_CTRL2, drv8329_ctrl_config);

    // 
    // Read fault status from DRV8329
    //
    gateDriverFaultReport.w |=  DRV8329_getFaultStatus();
    gateDriverFaultAction.w = gateDriverFaultAction.w | gateDriverFaultReport.w;

    //
    // Fault configuration for SnsFlt
    //
    if(config->gateDrvCfg1.b.disSnsFlt)
    {
        gateDriverFaultReport.w  &= ~(DRV8329_FAULT_STATUS_OCP_SNS);
        gateDriverFaultAction.w  &= ~(DRV8329_FAULT_STATUS_OCP_SNS);
    }
    else
    {
        gateDriverFaultReport.w |=  DRV8329_FAULT_STATUS_OCP_SNS;
        gateDriverFaultAction.w |=  DRV8329_FAULT_STATUS_OCP_SNS;
    }

    //
    // Fault configuration for VdsFlt
    //
    if(config->gateDrvCfg1.b.disVdsFlt)
    {
        gateDriverFaultReport.w  &= ~(DRV8329_FAULT_STATUS_OCP_VDS);
        gateDriverFaultAction.w  &= ~(DRV8329_FAULT_STATUS_OCP_VDS);
    }
    else
    {
        gateDriverFaultReport.w  |=  DRV8329_FAULT_STATUS_OCP_VDS;
        gateDriverFaultAction.w  |=  DRV8329_FAULT_STATUS_OCP_VDS;
    }

    //
    // Fault configuration for BstFlt
    //
    if(config->gateDrvCfg1.b.disBstFlt)
    {
        gateDriverFaultReport.w &= ~(DRV8329_FAULT_STATUS_BST_UV);
        gateDriverFaultAction.w &= ~(DRV8329_FAULT_STATUS_BST_UV);
    }
    else
    {
        gateDriverFaultReport.w |=  DRV8329_FAULT_STATUS_BST_UV;
        gateDriverFaultAction.w |=  DRV8329_FAULT_STATUS_BST_UV;
    }
}

//*****************************************************************************
//
// DRV8329_configureParamsDefault
//
//*****************************************************************************
void DRV8329_configureParamsDefault(void)
{
    DRV_Interface_WriteRegister(DRV8329_O_CTRL1, DRV8329_CTRL1_REG_DEFAULT_CONFIG);
    DRV_Interface_WriteRegister(DRV8329_O_CTRL2, DRV8329_CTRL2_REG_DEFAULT_CONFIG);
}

//*****************************************************************************
//
// DRV8329_resetFaultStatus
//
//*****************************************************************************
void DRV8329_resetFaultStatus(void)
{
    DRV8329_clearFaults();
    gateDriverFaultReport.w = DRV8329_FAULT_STATUS_DEFAULT;
    gateDriverFaultAction.w = DRV8329_FAULT_STATUS_DEFAULT;
}

//*****************************************************************************
//
// DRV8329_getFaultStatus
//
//*****************************************************************************
uint32_t DRV8329_getFaultStatus(void)
{
    uint32_t faultStatus = 0;
    uint16_t registerValue = 0;

    registerValue = DRV_Interface_ReadRegister(DRV8329_O_STATUS);

    if((registerValue & DRV8329_STATUS_FAULT) != 0)
    {
        faultStatus |= DRV8329_FAULT_STATUS_FAULT_COMMON;
    }
    else
    {
        faultStatus &= ~(DRV8329_FAULT_STATUS_FAULT_COMMON);
    }

    return (faultStatus & DRV8329_FAULT_STATUS_MASK);
}

//*****************************************************************************
//
// DRV8329_getAllRegisters
//
//*****************************************************************************
void DRV8329_getAllRegisters(uint16_t* registerArray)
{
    uint16_t i=0;

    registerArray[i++] = DRV_Interface_ReadRegister(DRV8329_O_STATUS);
    registerArray[i++] = DRV_Interface_ReadRegister(DRV8329_O_CTRL1);
    registerArray[i++] = DRV_Interface_ReadRegister(DRV8329_O_CTRL2);
}

#ifdef DEBUG
//*****************************************************************************
//
// DRV8329_readbackRegisters
//
//*****************************************************************************
void DRV8329_readbackRegisters(DRV8329_REGS_T *pRegs)
{
    pRegs->status.w = DRV_Interface_ReadRegister(DRV8329_O_STATUS);
    pRegs->ctrl1.w  = DRV_Interface_ReadRegister(DRV8329_O_CTRL1);
    pRegs->ctrl2.w  = DRV_Interface_ReadRegister(DRV8329_O_CTRL2);
}
#endif // DEBUG

