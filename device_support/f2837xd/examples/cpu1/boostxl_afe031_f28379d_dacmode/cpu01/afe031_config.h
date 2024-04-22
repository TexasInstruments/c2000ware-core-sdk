//#############################################################################
//
// FILE:   AFE031_Config.c
//
// TITLE:  AFE Setup Functions
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

#ifndef AFE031_CONFIG_H_
#define AFE031_CONFIG_H_

//
// Included Files
//
#include "afe031_config.h"
#include "hal_afe031.h"
#include "hal_spi.h"

/*****************************************************************************/
/* Data Structures                                                           */
/*****************************************************************************/
/* AFE handle */
#define HAL_SPI_BRR       1//SPICLK=60/4=15MHz // changed from 2
#define HAL_status_t Uint16
typedef struct
{
 UINT16 HAL_afe_spiErrCnt;
 UINT16 HAL_afe_spiReadBack;
 UINT16 HAL_afe_spiRecoverCnt;
 UINT16 HAL_afe_spiRecoverFailCnt;
}HAL_afe032_spiTest_t;

typedef struct
{
  Uint16          txSize;           // 0 TX size
  Uint16          txActive;         // 1 TX active flag

  Uint16 updateGainFlag;            // 2 AGC gain update flag
  int16  agcGainVal;                // 3 AGC gain value

  /* Added for ADC int */
  volatile Uint16 *rxBufPtr_p[2];   // 4 5 6 7 RX buffer address (ping-pong buffer)
  volatile Uint16 *rxBufDat_p;      // 8 9
  Uint16 rxBufSize[2];              // 10 11 RX buffer size (Number of bursts in a transfer - 1)
  Uint16 rxBufIdx;                  // 12 RX buffer buffer index (next active buffer being filled)
  Uint16 adcCnt;                    // 13
  Uint16 rxBufCnt;                  // 14
  Uint16 adcIntCnt;                 // 15
  Uint16 activeBufIdx;              // 16 Active buffer index. Reload rxBufIdx @symbol done
  Uint16 activeBufSize;             // 17 Active buffer size. Reload rxBufSize[activeBufIdx] @symbol done

  /* For TX Buffers */
  volatile Uint16 *txBufReady_p;    // 18 19 TX buffer ready to be read
  volatile Uint16 *bufDat_p;        // 20 21 TX active buffer pointer
  Uint16 txBufIdx;                  // 22
  Uint16 txIntCnt;                  // 23
  Uint16 txBufSize;                 // 24

  UINT16 timer01ShotFlag;           //  25 Timer 0 cfg flags
                                    
  Uint32 cb_param;                  
  Uint32 rxDmaTime;                 // RX DMA time (in 10us)
  Uint32 zcaTime;                   // Zero-crossing time (in 10us)
                                    
  //Uint16 zcaPeriod;               // half-cycle period (in 10us)
                                    
  Uint32 zcaLatency;                // Zero-crossing latency (in CPU ticks)
  Uint32 zcaCap1;                   // Zero-crossing captured (in CPU ticks)
  Uint32 zcbTime;                   // Zero-crossing time (in 10us)
  Uint32 zcbLatency;                // Zero-crossing latency (in CPU ticks)
  Uint32 zcbCap1;                   // Zero-crossing captured (in CPU ticks)
                                                                                                          
  Uint32 t0Prd;                     // T0 period in us (Q1)
                                                                                                          
  UINT16 txPgaAttn;                 
  Uint16 zcaPeriod;                 // half-cycle period (in 10us)

}HAL_afe_handle_t;

//
// Function Prototypes
//
HAL_status_t HAL_afe_init(void);
HAL_status_t HAL_afe_cfg(void *setParms);

HAL_status_t HAL_afe_rxCfg(void *setParms);
HAL_status_t HAL_afe_rxStart(void *setParms);
HAL_status_t HAL_afe_rxStop(void *setParms);
HAL_status_t HAL_afe_rxReCfg(void *setParms);
HAL_status_t HAL_afe_setGain(void *setParms);
HAL_status_t HAL_afe_updateGain(void *setParms);
HAL_status_t HAL_afe_cancelGain(void *setParms);
HAL_status_t HAL_afe_adcOffsetAdj(void *setParms);
HAL_status_t HAL_afe_txDmaSize(void *setParms);
HAL_status_t HAL_afe_txDmaAddr(void *setParms);
HAL_status_t HAL_cpuTimer1CfgStart(void);
Uint32 HAL_cpuTimer1GetCount(void);
HAL_status_t HAL_cpuTimer0TimeoutCfg(void *setParms);
HAL_status_t HAL_cpuTimer0Cfg(UINT16 t0Prd);
HAL_status_t HAL_cpuTimer0Start();
HAL_status_t HAL_cpuTimer0Stop();


HAL_status_t HAL_cpuTimerCfg();

HAL_status_t HAL_afe_txCfg(void *setParms);
HAL_status_t HAL_afe_txStart(void *setParms);

HAL_status_t HAL_afe_txStop(void *setParms);
HAL_status_t HAL_afe_txReCfg(void *setParms);

HAL_status_t HAL_afe_rxDmaTime(void *getParms);
HAL_status_t HAL_afe_zcTime(void *getParms);
HAL_status_t HAL_afe_rxDmaIdx(void *getParms);

HAL_status_t HAL_afe_prfCfg(void *setParms);

Uint16 HAL_afe031_readIntFlag(void);

#endif /* AFE031_CONFIG_H_ */

//
// End of file
//
