//#############################################################################
//
// FILE:   hw_drv8329.h
//
// TITLE:  Definitions for DRV8329 Gate Driver Registers
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

#ifndef HW_DRV8329_H
#define HW_DRV8329_H

//*************************************************************************************************
//
// The following are defines for the DRV8329 register offsets
//
//*************************************************************************************************
#define DRV8329_O_STATUS                    0x20U   // DRV8329 STATUS Register
#define DRV8329_O_CTRL1                     0x23U   // DRV8329 CTRL1 Register
#define DRV8329_O_CLEAR                     0x24U   // DRV8329 CLEAR Register
#define DRV8329_O_CTRL2                     0x27U   // DRV8329 CTRL2 Register

//*************************************************************************************************
//
// The following are defines for the bit fields in the DRV8329 STATUS register
//
//*************************************************************************************************
#define DRV8329_STATUS_FAULT              0x1U
#define DRV8329_STATUS_DRVOFF             0x2U
#define DRV8329_STATUS_GVDD_UV_FLT        0x4U
#define DRV8329_STATUS_BST_UV_FLT         0x8U
#define DRV8329_STATUS_OCP_SNS_FLT        0x10U
#define DRV8329_STATUS_OCP_VDS_FLT        0x20U
#define DRV8329_STATUS_OTS_FLT            0x40U
#define DRV8329_STATUS_PWR_ON             0x80U

//*************************************************************************************************
//
// The following are defines for the bit fields in the DRV8329 CTRL1 register
//
//*************************************************************************************************
#define DRV8329_CTRL1_SEL_VDSLVL_S          1U
#define DRV8329_CTRL1_SEL_VDSLVL_M          0x1EU
#define DRV8329_CTRL1_SEL_VDS_SPI           0x20U
#define DRV8329_CTRL1_DIS_VDS_FLT           0x40U
#define DRV8329_CTRL1_DIS_SNS_FLT           0x80U

//*************************************************************************************************
//
// The following are defines for the bit fields in the DRV8329 CLEAR register
//
//*************************************************************************************************
#define DRV8329_CLEAR_CLR_FLT               0x1U

//*************************************************************************************************
//
// The following are defines for the bit fields in the DRV8329 CTRL2 register
//
//*************************************************************************************************
#define DRV8329_CTRL2_DIS_DRV               0x8U
#define DRV8329_CTRL2_DIS_TCP               0x10U
#define DRV8329_CTRL2_OTS_AUTO_RECOVER      0x20U
#define DRV8329_CTRL2_DIS_BST_FLT           0x40U

#endif // HW_DRV8329_H
