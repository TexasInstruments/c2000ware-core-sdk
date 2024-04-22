//#############################################################################
//
// FILE:   hal_afe031.h
//
// TITLE:  AFE031 Functions
//
//###########################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
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
//###########################################################################

#ifndef _HAL_AFE031_H
#define _HAL_AFE031_H

//
// Included Files
//
#include "F28x_Project.h"     // Device Headerfile and Examples Include File

//
// Defines
//
#define UINT16 Uint16
#define HAL_AFE031_CMD_SHIFT 8
#define HAL_AFE031_CMD_MASK  0xFF
#define HAL_AFE031_DATA_SHIFT 0
#define HAL_AFE031_DATA_MASK  0xFF

#define HAL_AFE031_CMD_WR 0x0
#define HAL_AFE031_CMD_RD 0x8
#define HAL_AFE031_CMD_RW_SHIFT 4
#define HAL_AFE031_CMD_RW_MASK  0xF

#define HAL_AFE031_ENABLE_REG   0x1
#define HAL_AFE031_ENABLE2_REG  0x3
#define HAL_AFE031_GAINSEL_REG  0x2
#define HAL_AFE031_CTRL_REG     0x4
#define HAL_AFE031_CTRL2_REG    0x5
#define HAL_AFE031_FUSE1_REG    0x8
#define HAL_AFE031_RESET_REG    0x9
#define HAL_AFE031_DIEID_REG    0xA
#define HAL_AFE031_REV_REG      0xB
#define HAL_AFE031_IFLAG_REG    0xC

/* Register Bit Definitions */
/* Enable Register */
#define HAL_AFE031_ENABLE_PA            0x1
#define HAL_AFE031_ENABLE_TX            0x2
#define HAL_AFE031_ENABLE_RX            0x4
#define HAL_AFE031_ENABLE_ERX           0x8
#define HAL_AFE031_ENABLE_ETX           0x10
#define HAL_AFE031_ENABLE_DAC           0x20

/* Enable2 Register */
#define HAL_AFE031_ENABLE2_ZC           0x1
#define HAL_AFE031_ENABLE2_REF1         0x2
#define HAL_AFE031_ENABLE2_REF2         0x4
#define HAL_AFE031_ENABLE2_REF          0x6
#define HAL_AFE031_ENABLE2_PAOUT        0x8
#define HAL_AFE031_ENABLE2_OVWR         0x80

/* Fuse1 Register */
#define HAL_AFE031_FUSE1_TX0            0x1
#define HAL_AFE031_FUSE1_TX1            0x2
#define HAL_AFE031_FUSE1_TX2            0x4
#define HAL_AFE031_FUSE1_TX3            0x8
#define HAL_AFE031_FUSE1_RX0            0x10
#define HAL_AFE031_FUSE1_RX1            0x20
#define HAL_AFE031_FUSE1_RX2            0x40
#define HAL_AFE031_FUSE1_RX3            0x80

/* Reset Register */
#define HAL_AFE031_RESET_SOFTRST0       0x4   //write only
#define HAL_AFE031_RESET_SOFTRST1       0x8   //write only
#define HAL_AFE031_RESET_SOFTRST2       0x10  //write only
#define HAL_AFE031_RESET_SOFTRST_MASK   0x1C
#define HAL_AFE031_RESET_SOFTRST        0x14  //101 to reset
#define HAL_AFE031_RESET_TFLAG          0x20  //read only (status)
#define HAL_AFE031_RESET_IFLAG          0x40  //read only (status)
#define HAL_AFE031_RESET_PWRFLAG        0x80  //read only (status)

/* Gain Select Register */
#define HAL_AFE031_GAINSEL_RXGAIN_MASK  0xF   //b3-0
#define HAL_AFE031_GAINSEL_TXGAIN_MASK  0x3   //b5b4
#define HAL_AFE031_GAINSEL_TXGAIN_SHIFT 0x4

/* Control Register */
#define HAL_AFE031_CTRL_TXCAL           0x1   //b0
#define HAL_AFE031_CTRL_RXCAL           0x2   //b1
#define HAL_AFE031_CTRL_TXPGACAL        0x4   //b2
#define HAL_AFE031_CTRL_BAND            0x8   //b3 (0-A; 1-BCD)
#define HAL_AFE031_CTRL_ABAND           0
#define HAL_AFE031_CTRL_BCDBAND         1
#define HAL_AFE031_CTRL_BAND_SHIFT      3
#define HAL_AFE031_CTRL_TXFLAG          0x40  //b6 (read only)
#define HAL_AFE031_CTRL_RXFLAG          0x80  //b7 (read only)

/* Control2 Register */
#define HAL_AFE031_CTRL2_TFLAG          0x20  //b5
#define HAL_AFE031_CTRL2_IFLAG          0x40  //b6
#define HAL_AFE031_CTRL2_PFLAG          0x80  //b7

#define HAL_AFE031_BIAS_ON_DELAY        2000  //in us

/* For true SPI (F28035), 10-bit SPI I/F for DAC
   For McBSP/SPI, 12-bit I/F for DAC */
//#ifdef F2803X
#define HAL_AFE031_SPI_DAC_LEN              10

#define HAL_AFE031_SPI_DEFAULT_LEN          16

typedef enum
{
  HAL_AFE031_ABAND   = 0,
  HAL_AFE031_BCDBAND = 1
}HAL_afe031_band_t;

/*****************************************************************************/
/* Macro Definistions                                                        */
/*****************************************************************************/
#define HAL_afe031_softReset() \
  {HAL_afe031_reg_s.reset.bits.SOFT_RST = HAL_AFE031_RESET_SOFTRST;\
   HAL_afe031_regWrite(HAL_AFE031_RESET_REG, HAL_afe031_reg_s.reset.all);}

#define HAL_afe031_biasEnable() \
  {HAL_afe031_reg_s.enable2.bits.REF = 3; \
   HAL_afe031_regWrite(HAL_AFE031_ENABLE2_REG, HAL_afe031_reg_s.enable2.all);\
   DELAY_US(HAL_AFE031_BIAS_ON_DELAY);}

#define HAL_afe031_txDACEnable() \
  {HAL_afe031_reg_s.enable.bits.TX = 1; \
   HAL_afe031_reg_s.enable.bits.DAC = 1; \
   HAL_afe031_reg_s.enable.bits.PA = 1; \
   HAL_afe031_regWrite(HAL_AFE031_ENABLE_REG, HAL_afe031_reg_s.enable.all); \
   DELAY_US(2); \
   HAL_afe031_reg_s.enable2.bits.PA_OUT = 1; \
   HAL_afe031_regWrite(HAL_AFE031_ENABLE2_REG, HAL_afe031_reg_s.enable2.all); }

#define HAL_afe031_txPWMEnable() \
  {HAL_afe031_reg_s.enable.bits.TX = 1; \
   HAL_afe031_reg_s.enable.bits.DAC = 0; \
   HAL_afe031_reg_s.enable.bits.PA = 1; \
   HAL_afe031_regWrite(HAL_AFE031_ENABLE_REG, HAL_afe031_reg_s.enable.all); \
   DELAY_US(2); \
   HAL_afe031_reg_s.enable2.bits.PA_OUT = 1; \
   HAL_afe031_regWrite(HAL_AFE031_ENABLE2_REG, HAL_afe031_reg_s.enable2.all); }

#define HAL_afe031_txDisable() \
  {HAL_afe031_reg_s.enable2.bits.PA_OUT = 0; \
   HAL_afe031_regWrite(HAL_AFE031_ENABLE2_REG, HAL_afe031_reg_s.enable2.all); \
   HAL_afe031_reg_s.enable.bits.TX = 0; \
   HAL_afe031_reg_s.enable.bits.PA = 0; \
   HAL_afe031_regWrite(HAL_AFE031_ENABLE_REG, HAL_afe031_reg_s.enable.all);}

#define HAL_afe031_dacEnable() \
  {HAL_afe031_reg_s.enable.bits.DAC = 1; \
   HAL_afe031_regWrite(HAL_AFE031_ENABLE_REG, HAL_afe031_reg_s.enable.all); \
   DELAY_US(2); \
   HAL_afe031_cfgWdLen(HAL_AFE031_SPI_DAC_LEN); \
   GPIO_WritePin(2, 1);}


#define HAL_afe031_dacDisable() \
  {GpioDataRegs.GPADAT.bit.GPIO7 = 0; \
   DELAY_US(10); \
   HAL_afe031_cfgWdLen(HAL_AFE031_SPI_DEFAULT_LEN); \
   GPIO_WritePin(2, 0); \
   HAL_afe031_regWrite(HAL_AFE031_ENABLE_REG, HAL_afe031_reg_s.enable.all);}


#define HAL_afe031_rxEnable() \
  {HAL_afe031_reg_s.enable.bits.RX = 1; \
   HAL_afe031_regWrite(HAL_AFE031_ENABLE_REG, HAL_afe031_reg_s.enable.all);}

#define HAL_afe031_rxDisable() \
  {HAL_afe031_reg_s.enable.bits.RX = 0; \
   HAL_afe031_regWrite(HAL_AFE031_ENABLE_REG, HAL_afe031_reg_s.enable.all);}

#define HAL_afe031_bandSelect(band) \
 {HAL_afe031_reg_s.control.bits.CA_BCD = band; \
  HAL_afe031_regWrite(HAL_AFE031_CTRL_REG, HAL_afe031_reg_s.control.all);}

#define HAL_afe031_zcEnable() \
{ HAL_afe031_reg_s.enable2.bits.ZC = 1;\
  HAL_afe031_regWrite(HAL_AFE031_ENABLE2_REG, HAL_afe031_reg_s.enable2.all);}

/*****************************************************************************/
/* Data Structures                                                           */
/*****************************************************************************/
typedef struct
{
  UINT16 PA  :1;   //b0 - PA enable
  UINT16 TX  :1;   //b1 - TX enable
  UINT16 RX  :1;   //b2 - RX enable
  UINT16 ERX :1;   //b3 - ERX enable
  UINT16 ETX :1;   //b4 - ETX enable
  UINT16 DAC :1;   //b5 - DAC enable
  UINT16 rsvd :10;   //reserved
}HAL_afe031_enable_t;

typedef struct
{
  UINT16 ZC   :1;   //b0 - ZC enable
  UINT16 REF  :2;   //b2:1 - Ref12Ref1 enable
  UINT16 PA_OUT :1; //b3 - PA out enable
  UINT16 rsvd   :3; //b6:4 - reserved
  UINT16 OVWR   :1; //Fuse1 overwrite enable
  UINT16 rsvd1  :8; //reserved
}HAL_afe031_enable2_t;

typedef struct
{
  UINT16 RXG    :4; //b1:0 - RX PGA1 gain
                    //b3:2 - RX PGA2 gain
  UINT16 TXG    :2; //b5:4 - TX PGA gain
  UINT16 rsvd   :10; //b15:6 reserved
}HAL_afe031_gain_sel_t;

typedef struct
{
  UINT16 TX_CAL :1; //b0 - TX calibration enable
  UINT16 RX_CAL :1; //b1 - RX calibration enable
  UINT16 TXPGA_CAL :1; //b2 - TXPGA calibration enable
  UINT16 CA_BCD    :1; //b3 - Cenelec A (0) or BCD (1) band
  UINT16 rsvd      :2; //b5:4 - reserved
  UINT16 TX_FLAG   :1; //b6 - TX flag status (read only)
  UINT16 RX_FLAG   :1; //b7 - RX flag status (read only)
  UINT16 rsvd1     :8; //reserved
}HAL_afe031_control_t;

typedef struct
{
  UINT16 rsvd      :5; //b4:0 - reserved
  UINT16 TFLAG_EN  :1; //b5 - TFlag enable
  UINT16 IFLAG_EN  :1; //b6 - IFlag enable
  UINT16 PFLAG_EN  :1; //b7 - PFlag enable
  UINT16 rsvd1     :8; //reserved
}HAL_afe031_control2_t;

typedef struct
{
  UINT16 TX_TRIM   :4; //b3:0 - Each bit, 0:Clear TX trim fuse; 1:Set TX trim fuse
  UINT16 RX_TRIM   :4; //b7:4 - Each bit, 0:Clear RX trim fuse; 1:Set RX trim fuse
  UINT16 rsvd      :8; //reserved
}HAL_afe031_fuse1_t;

typedef struct
{
  UINT16 rsvd      :2; //b1:0 - reserved
  UINT16 SOFT_RST  :3; //b4:2 - Writing 101 to soft reset
  UINT16 TFLAG     :1; //b5 - TFlag status (write 0 to clear)
  UINT16 IFLAG     :1; //b6 - IFlag status (write 0 to clear)
  UINT16 PFLAG     :1; //b7 - PFlag status (write 0 to clear)
  UINT16 rsvd1     :8; //reserved
}HAL_afe031_reset_t;


typedef struct
{
  union
  {
    UINT16 all;
    HAL_afe031_enable_t bits;
  }enable;

  union
  {
    UINT16 all;
	HAL_afe031_enable2_t bits;
  }enable2;
  
  union
  {
    UINT16 all;
    HAL_afe031_gain_sel_t bits;
  }gain_sel;
  
  union
  {
    UINT16 all;
    HAL_afe031_control_t bits;
  }control;
  
  union
  {
    UINT16 all;
	HAL_afe031_control2_t bits;
  }control2;
  
  union
  {
    UINT16 all;
	HAL_afe031_fuse1_t bits;
  }fuse1;

  union
  {
    UINT16 all;
	HAL_afe031_reset_t bits;
  }reset;

  UINT16 iflag_tm;

  UINT16 die_id;

  UINT16 rev;
}HAL_afe031_reg_t;

//
// Externals
//
extern HAL_afe031_reg_t HAL_afe031_reg_s;

//
// Function Prototypes
//
void HAL_afe031_regWrite(UINT16 addr, UINT16 data);
UINT16 HAL_afe031_regRead(UINT16 addr);
void HAL_afe031_writeGain(UINT16 rxgain, UINT16 txgain);
void HAL_afe031_clrAllInt(void);
void HAL_afe031_cfgInt(void);
void HAL_afe031_clrInt(UINT16 flag);
UINT16 HAL_afe031_intAsserted(void);
void HAL_afe031_shutdown(UINT16 sd);
void HAL_afe031_cfgGpio(void);
void HAL_afe031_cfgWdLen(UINT16 len);
void HAL_afe031Init(void);

#endif

//
// End of file
//
