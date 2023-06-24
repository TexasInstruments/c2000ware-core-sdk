//###########################################################################
//
// FILE:   ethernet.h
//
// TITLE:  CM Ethernet driver.
//
//###########################################################################
//
//
// $Copyright:
// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
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

#ifndef ETHERNET_H
#define ETHERNET_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif
//*****************************************************************************
//
//! \addtogroup ethernet_api Ethernet
//! @{
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_emac.h"
#include "inc/hw_emac_ss.h"
#include "interrupt.h"
#include "platform_port.h"
//
//Transmit Store and Forward Shift Value
//
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TSF_S      1U
#define ETHERNET_MAC_CONFIGURATION_DM_S             13U//Duplex Mode Shift Value
#define ETHERNET_MAC_CONFIGURATION_LM_S             12U
//
//MAC Packet Filter Register Bit Field Enumerations
//
#define ETHERNET_MAC_PACKET_FILTER_PCF_FILTER_ALL_CTRL                  0U
#define ETHERNET_MAC_PACKET_FILTER_PCF_FWD_ALL_EXCEPTPASS               1U
#define ETHERNET_MAC_PACKET_FILTER_PCF_FWD_ALL_WITHOUT_ADDRESS_FILTER   2U
#define ETHERNET_MAC_PACKET_FILTER_PCF_FWD_ALL_WITH_ADDRESS_FILTER      3U
//
//MAC Configuration Enumerations
//
#define ETHERNET_MAC_CONFIGURATION_DM_FULL_DUPLEX               1U
#define ETHERNET_MAC_CONFIGURATION_DM_HALF_DUPLEX               0U
#define ETHERNET_MAC_CONFIGURATION_LM_LOOPBACK_ENABLED          1U
#define ETHERNET_MAC_CONFIGURATION_LM_LOOPBACK_DISABLED         0U
#define ETHERNET_MAC_RXQ_CONTROL_RXQEN_ENABLED_GENERIC          2U
//
//MAC WatchDog Timeout Enumerations
//
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_2KB                   0U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_3KB                   1U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_4KB                   2U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_5KB                   3U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_6KB                   4U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_7KB                   5U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_8KB                   6U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_9KB                   7U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_10KB                  8U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_11KB                  9U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_12KB                  10U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_13KB                  11U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_14KB                  12U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_15KB                  13U
#define ETHERNET_MAC_WATCHDOG_TIMEOUT_WTO_15383                 14U
//
//Value of F for WTO is reserved and hence not defined
//
//Threshold value defines for Transmit Threshold
//Enumerations for MTL_TXQn_OPMode Register
//These values can be used as an argument for Ethernet_setMTLTxQueueOpMode func
//
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_32                 0U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_64                 1U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_96                 2U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_128                3U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_192                4U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_256                5U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_384                6U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TTC_512                7U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TXQ_DISABLED           0U
#define ETHERNET_MTL_TXQ0_OPERATION_MODE_TXQ_ENABLED            2U

//
//Enumerations for DMA_Mode Register
//
#define ETHERNET_DMA_OPERATION_MODE_PR_TX1_RX1                  0U
#define ETHERNET_DMA_OPERATION_MODE_PR_TX2_RX1                  1U
#define ETHERNET_DMA_OPERATION_MODE_PR_TX3_RX1                  2U
#define ETHERNET_DMA_OPERATION_MODE_PR_TX4_RX1                  3U
#define ETHERNET_DMA_OPERATION_MODE_PR_TX5_RX1                  4U
#define ETHERNET_DMA_OPERATION_MODE_PR_TX6_RX1                  5U
#define ETHERNET_DMA_OPERATION_MODE_PR_TX7_RX1                  6U
#define ETHERNET_DMA_OPERATION_MODE_PR_TX8_RX1                  7U
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_TXQ_DISABLED           0U
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_TXQ_ENABLED            2U
#define ETHERNET_DMA_OPERATION_MODE_DA_ROUND_ROBIN              0U
#define ETHERNET_DMA_OPERATION_MODE_DA_FIXED_PRIORITY           1U

//
//MTL OP Mode Register Bit Field Enumerations
//
#define ETHERNET_MTL_OPERATON_MODE_SCHALG_WRR                   0U
#define ETHERNET_MTL_OPERATON_MODE_SCHALG_WFQ                   1U
#define ETHERNET_MTL_OPERATON_MODE_SCHALG_DWRR                  2U
#define ETHERNET_MTL_OPERATON_MODE_SCHALG_STRICT_PRIORITY       3U
#define ETHERNET_MTL_OPERATION_MODE_RAA_SP                      0U
#define ETHERNET_MTL_OPERATION_MODE_RAA_WSP                     1U
#define ETHERNET_MTL_OPERATION_MODE_RAA_S                       2U
#define ETHERNET_MTL_Q_OP_MODE_QSIZE_256                        0U
#define ETHERNET_MTL_Q_OP_MODE_QSIZE_512                        1U
#define ETHERNET_MTL_Q_OP_MODE_QSIZE_768                        2U
#define ETHERNET_MTL_Q_OP_MODE_QSIZE_1024                       3U
#define ETHERNET_MTL_Q_OP_MODE_QSIZE_1280                       4U
#define ETHERNET_MTL_Q_OP_MODE_QSIZE_1536                       5U
#define ETHERNET_MTL_Q_OP_MODE_QSIZE_1792                       6U
#define ETHERNET_MTL_Q_OP_MODE_QSIZE_2048                       7U
#define ETHERNET_MTL_Q_OP_MODE_QSIZE_4096                       15U
//
//Enumeration for MTL_TxQ0_Operation_Mode Register
//
#define ETHERNET_MTL_TXQ_OPMODE_TSF_ENABLE          1U
#define ETHERNET_MTL_TXQ_OPMODE_TSF_DISABLE         0U
//
//Enumeration for MTL_RxQ0_Operation_Mode Register
//
#define ETHERNET_MTL_RX_Q_OP_MODE_RSF_ENABLE        1U
#define ETHERNET_MTL_RX_Q_OP_MODE_RSF_DISABLE       0U
//
//Enumerations for MTL_RXQn_OPMode Register
//
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RTC_64     0U
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RTC_32     1U
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RTC_96     2U
#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RTC_128    3U

#define ETHERNET_MTL_RXQ0_OPERATION_MODE_RSF_S      5U

//
//Enumeration for DMA_CH(#i)_RX_Control Register
//Received Buffer Size
//Our Configuration has 2bits(since 4 bytes is burst size)
//for the lower bits and Bit 0 is for Enable
//Hence it should be left shift by 3
//
#define ETHERNET_DMA_CHX_RX_CONTROL_RBSZ_16         4U
#define ETHERNET_DMA_CHX_RX_CONTROL_RBSZ_32         8U
#define ETHERNET_DMA_CHX_RX_CONTROL_RBSZ_64         16U
#define ETHERNET_DMA_CHX_RX_CONTROL_RBSZ_128        32U
#define ETHERNET_DMA_CHX_RX_CONTROL_RBSZ_256        64U
#define ETHERNET_DMA_CHX_RX_CONTROL_RBSZ_512        128U
#define ETHERNET_DMA_CHX_RX_CONTROL_RBSZ_1K         256U
#define ETHERNET_DMA_CHX_RX_CONTROL_RBSZ_2K         512U

//
// Following defines are used for Timestamping module configuration.
//
#define ETHERNET_MAC_SUBNANOSECONDS_INC_MULTIPLIER      0x100U  // 2^8
#define ETHERNET_MAC_DIGITAL_ROLLOVER_ACCURACY          1U      // 1ns acc.
#define ETHERNET_MAC_BINARY_ROLLOVER_ACCURACY           0.465F  // 0.465 ns acc.

//
// MAC_PPSx_Target_Time_Nanoseconds Register bit fields
//
/*
 * TODO : This register can have many instances depending on the
 * instances of the PPS in MAC.
 */
#define ETHERNET_MAC_PPS_TARGET_TIME_SECONDS                    0x0B80U
#define ETHERNET_MAC_PPS_TARGET_TIME_NANOSECONDS                0x0B84U
#define ETHERNET_MAC_PPS_WIDTH                                  0x0B8CU
#define ETHERNET_MAC_PPS_INTERVAL                               0x0B88U
#define ETHERNET_MAC_PPS_TARGET_TIME_NANOSECONDS_TRGTBUSY       0x80000000U
#define ETHERNET_MAC_PPS_OUT_INSTANCE_0                         0x0U
#define ETHERNET_MAC_PPS_OUT_INSTANCE_1                         0x1U

//
// AUX Timestamp related
//
#define ETHERNET_MAC_AUX_TIMESTAMP_FIFO_DEPTH               0x4U

//
// Enumeration for ETHERNET_SS_O_PTPTSTRIGSEL0/1 register
//
#define ETHERNET_SS_PTPTSTRIGSEL_AUX_TRIG_SEL0              0x1U
#define ETHERNET_SS_PTPTSTRIGSEL_AUX_TRIG_SEL1              0x2U

//
// Enumeration for EMACSS_PTPTSSWTRIG0/1 register
//
#define ETHERNET_SS_PTPTSSWTRIG_PTP_AUX_TS_SW_TRIG0         0x1U
#define ETHERNET_SS_PTPTSSWTRIG_PTP_AUX_TS_SW_TRIG1         0x2U

//
// Maximum 32 configurations are allowed.
//
#define ETHERNET_SS_PTPTSTRIGSEL_AUX_TRIG_SEL_MAX_VALUE     0x1FU

//
//MAC_PPS_Control Register bit-fields
//
#define ETHERNET_MAC_PPS_CONTROL_PPSEN0                     4U
#define ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL0_S              5U
#define ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL0_M              3U
#define ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL1_S              13U
#define ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL1_M              3U

//
//Enumeration for MAC_PPS_Control Register
//
#define ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL_INTERRUPT               0x0U
#define ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL_RESERVED                0x1U
#define ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL_INTERRUPT_PULSE         0x2U
#define ETHERNET_MAC_PPS_CONTROL_TRGTMODSEL_PULSE                   0x3U

#define ETHERNET_MAC_PPS_CONTROL_PPSEN0_PPS_FIXED_MODE              0x0U
#define ETHERNET_MAC_PPS_CONTROL_PPSEN0_PPS_FLEXIBLE_MODE           0x1U

#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_SINGLE_PULSE    0x0U
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_1HZ             0x1U
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_2HZ             0x2U
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_4HZ             0x3U
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_8HZ             0x4U
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_16HZ            0x5U
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_32HZ            0x6U
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_64HZ            0x7U
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_128HZ           0x8U
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_256HZ           0x9U
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_512HZ           0xAU
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_1024HZ          0xBU
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_2048HZ          0xCU
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_4096HZ          0xDU
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_8192HZ          0xEU
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_16384HZ         0xFU
#define ETHERNET_MAC_PPS_CONTROL_PPSCTRL_PPS_OUTPUT_32768HZ         0x10U

#define ETHERNET_MAC_PPS_CONTROL_PPSCMD_COMMAND_NONE            0x0U
#define ETHERNET_MAC_PPS_CONTROL_PPSCMD_COMMAND_START_SINGLE    0x1U
#define ETHERNET_MAC_PPS_CONTROL_PPSCMD_COMMAND_START_TRAIN     0x2U
#define ETHERNET_MAC_PPS_CONTROL_PPSCMD_COMMAND_CANCEL_START    0x3U
#define ETHERNET_MAC_PPS_CONTROL_PPSCMD_COMMAND_STOP_AT_TIME    0x4U
#define ETHERNET_MAC_PPS_CONTROL_PPSCMD_COMMAND_STOP_NOW        0x5U
#define ETHERNET_MAC_PPS_CONTROL_PPSCMD_COMMAND_CANCEL_STOP     0x6U

//
//Enumerations for VLAN Incl Register
//

#define ETHERNET_MAC_VLAN_INCL_VLP_S    18U

//
//Static means the Tag control is provided in the VLC Field
//
#define ETHERNET_MAC_VLAN_INCL_VLP_STATIC       1U

//
//Dynamic means the VLC field is ignored and uses Context Descriptor
//
#define ETHERNET_MAC_VLAN_INCL_VLP_DYNAMIC      0U

#define ETHERNET_MAC_VLAN_INCL_CSVL_S           19U
#define ETHERNET_MAC_VLAN_INCL_VLTI_S           20U
#define ETHERNET_MAC_VLAN_INCL_CBTI_S           21U
#define ETHERNET_MAC_VLAN_INCL_ADDR_S           24U
#define ETHERNET_MAC_VLAN_INCL_ADDR_M           0x1000000U
#define ETHERNET_MAC_VLAN_INCL_RDWR_S           30U
#define ETHERNET_MAC_VLAN_INCL_BUSY_S           31U

//
//For MAC_ Inner VLAN Register
//
#define ETHERNET_MAC_INNER_VLAN_INCL_VLP_S      18U
#define ETHERNET_MAC_INNER_VLAN_INCL_CSVL_S     19U
#define ETHERNET_MAC_INNER_VLAN_INCL_VLTI_S     20U

//
//For MAC_VLAN_TAG_DATA Register
//
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_16_S    16U
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_17_S    17U
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_18_S    18U
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_19_S    19U
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_20_S    20U
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_24_S    24U
#define ETHERNET_MAC_VLAN_TAG_DATA_DATA_25_S    25U

//
//For MAC_VLAN_TAG_Ctrl Register
//
#define ETHERNET_MAC_VLAN_TAG_CTRL_CT_READ      1U
#define ETHERNET_MAC_VLAN_TAG_CTRL_CT_WRITE     0U
#define ETHERNET_MAC_VLAN_TAG_CTRL_ERIVLT_S     27U
#define ETHERNET_MAC_VLAN_TAG_CTRL_ERIVLT_M     0x8000000U

//
// VLAN Tag Hash Table Match
//
#define ETHERNET_MAC_VLAN_TAG_CTRL_VTHM_M       0x2000000U

//
//Enumerations for DMA Mode Register
//
#define ETHERNET_DMA_MODE_INTM_MODE0    0U
#define ETHERNET_DMA_MODE_INTM_MODE1    1U
#define ETHERNET_DMA_MODE_INTM_MODE2    2U

//
//Defines for MDIO_ADDRESS register
//
#define ETHERNET_MDIO_ADDRESS_C45E_S                    1U
#define ETHERNET_MDIO_ADDRESS_HIGHCLK_ENABLE_S          11U
#define ETHERNET_MAC_MDIO_ADDRESS_GOC_0_S               2U

#define ETHERNET_MAC_MDIO_ADDRESS_GOC_WRITE             1U
#define ETHERNET_MAC_MDIO_ADDRESS_GOC_READ              3U
#define ETHERNET_MAC_MDIO_ADDRESS_GOC_POSTREAD_INC      2U

//
//Defines for MAC_ADDRESS Register
//
#define ETHERNET_MAC_ADDRESS0_HIGH_DCS_S                16U

//
//Defines for MTL_RXQ_DMA_MAP0 register
//
#define ETHERNET_MTL_RXQ_DMA_MAP0_DDMACH_S              4U
#define ETHERNET_MTL_RXQ_DMA_MAP0_QDMACH_S              8U

//
//Defines for REVMII Registers
//
#define ETHERNET_REVMII_PHY_CONTROL                     0x0U
#define ETHERNET_REVMII_COMMON_STATUS                   0x1U
#define ETHERNET_REVMII_COMMON_EXT_STATUS               0xFU
#define ETHERNET_REVMII_INTERRUPT_STATUS_MASK           0x10U
#define ETHERNET_REVMII_REMOTE_PHY_STATUS               0x11U

//
//Bit field defines for the REVMII Registers used
//
//REVMII Interrupt Status Mask Register
//
#define ETHERNET_REVMII_INTERRUPT_STATUS_MASK_LSI_M     0x100U

//
//Generic Enable Disable Defines
//
#define ETHERNET_ENABLE                     1U
#define ETHERNET_DISABLE                    0U

//
//hw_emac.h defines ends
//

//
//hw_emac_SS.h defines
//
#define ETHERNET_SS_CTRLSTS_CLK_LM_S                    4U
#define ETHERNET_SS_CTRLSTS_CLK_SRC_SEL_S               7U

//
//Enumerations for CTRLSTS Register
//

#define ETHERNET_SS_CTRLSTS_PHY_INTF_SEL_GMII           0U
/* Values 1-3 Reserved*/
#define ETHERNET_SS_CTRLSTS_PHY_INTF_SEL_RMII           4U
#define ETHERNET_SS_CTRLSTS_PHY_INTF_SEL_REVMII         7U

#define ETHERNET_SS_CTRLSTS_LMCLKSEL_NORMAL             0U
#define ETHERNET_SS_CTRLSTS_LMCLKSEL_INTERNAL           1U

#define ETHERNET_SS_CTRLSTS_CLK_SRC_SEL_EXTERNAL        0U
#define ETHERNET_SS_CTRLSTS_CLK_SRC_SEL_INTERNAL        1U

#define ETHERNET_SS_CTRLSTS_FLOW_CTRL_EN_ENABLED        3U
#define ETHERNET_SS_CTRLSTS_FLOW_CTRL_EN_DISABLED       0U

#define ETHERNET_SS_CTRLSTS_WRITE_KEY_VALUE             0xA5U

//
//hw_emac_SS.h ends
//

#define ETHERNET_NUMSTATS                               56U
#define ETHERNET_MAX_NUM_DMA_CHANNELS                   2U
#define ETHERNET_MAX_DMA_DIR                            2U
#define ETHERNET_CH_DIR_TX                              0U
#define ETHERNET_CH_DIR_RX                              1U
/*Hardware Descriptor related flags*/
/* Interrupt on Completion */
#define ETHERNET_TX_DESC_IOC                            0x80000000U
/*Owner ship Flag in Buffer Descriptor */
#define ETHERNET_DESC_OWNER                             0x80000000U

/*First/Last Descriptor indicator Flag*/
#define ETHERNET_TX_DESC_FIRST_DESC                     0x20000000U
#define ETHERNET_TX_DESC_LAST_DESC                      0x10000000U

#define ETHERNET_TX_DESC_TTSE                           0x40000000U
#define ETHERNET_RX_DESC_IOC                            0x40000000U
#define ETHERNET_RX_DESC_BUF1_VALID                     0x01000000U  //24th Bit
#define ETHERNET_RX_DESC_BUF2_VALID                     0x02000000U //25th Bit
#define ETHERNET_TX_DESC_TSE_ENABLE                     0x00040000U //18th Bit
#define ETHERNET_TX_DESC_BUF2LENGTH_S                   16U
#define ETHERNET_TX_DESC_SAIC_NO_SA_INC                 0U
#define ETHERNET_TX_DESC_SAIC_INS_SA                    1U
#define ETHERNET_TX_DESC_SAIC_REPL_SA                   2U
#define ETHERNET_TX_DESC_SAIC_S                         23U
#define ETHERNET_TX_DESC_CPC_S                          26U
#define ETHERNET_TX_DESC_CIC_S                          16U
#define ETHERNET_TX_CTXT_DESC_IVLAN_TAG_S               16U
#define ETHERNET_TX_DESC_VTIR_S                         14U

#define ETHERNET_TX_DESC_TTSS                           0x00020000U
#define ETHERNET_TX_CTXT_DESC_IVTIR_TAG_S               18U
#define ETHERNET_DESCRIPTORS_NUM_TX                     16U
#define ETHERNET_DESCRIPTORS_NUM_TX_PER_CHANNEL         8U

#define ETHERNET_DESCRIPTORS_NUM_RX                     16U
#define ETHERNET_DESCRIPTORS_NUM_RX_PER_CHANNEL         8U

#define ETHERNET_DESCRIPTORS_NUM (ETHERNET_DESCRIPTORS_NUM_TX +                \
                                        ETHERNET_DESCRIPTORS_NUM_RX )
/*
 *       |          31:16            | 15:14 |         13:0                |
 *       |     Inner VLAN Tag        |  x    |     Max Seg. Size           |
 */
#define ETHERNET_PKT_EXTENDED_FLAG_IVT_S                16U
#define ETHERNET_PKT_EXTENDED_FLAG_MSS_S                0U

#define ETHERNET_PKT_EXTENDED_FLAG_IVT_M                0xFFFF0000U
#define ETHERNET_PKT_EXTENDED_FLAG_MSS_M                0x00003FFFU


/*
 *       | 31 | 30 |29:28| 27 |  26  |25:24|23 |22:20|19:18|  17 | 16 |15:0|
 *       | OWN|CTXT|  x  |OSTC|TCMSSV|  x  |CDE|  x  |IVTIR|IVLTV|VLTV| VT |
 */
#define ETHERNET_PKT_EXTENDED_FLAG_IVTIR_S              18U
#define ETHERNET_PKT_EXTENDED_FLAG_VT_S                 0U

#define ETHERNET_PKT_EXTENDED_FLAG_CTXT                 0x40000000U
#define ETHERNET_PKT_EXTENDED_FLAG_OSTC                 0x08000000U
#define ETHERNET_PKT_EXTENDED_FLAG_TCMSSV               0x04000000U
#define ETHERNET_PKT_EXTENDED_FLAG_CDE                  0x00800000U
#define ETHERNET_PKT_EXTENDED_FLAG_VTIR_M               0x000C0000U
#define ETHERNET_PKT_EXTENDED_FLAG_VTIR_S               18U
#define ETHERNET_PKT_EXTENDED_FLAG_VTIR_NOTAG           0U
#define ETHERNET_PKT_EXTENDED_FLAG_VTIR_REMOVE          1U
#define ETHERNET_PKT_EXTENDED_FLAG_VTIR_INSERT          2U
#define ETHERNET_PKT_EXTENDED_FLAG_VTIR_REPLACE         3U
#define ETHERNET_PKT_EXTENDED_FLAG_IVLTV                0x00020000U
#define ETHERNET_PKT_EXTENDED_FLAG_VLTV                 0x00010000U
#define ETHERNET_PKT_EXTENDED_FLAG_VT_M                 0x0000FFFFU

#define ETHERNET_PKT_EXTENDED_FLAG_VLAN                 0x5U
#define ETHERNET_PKT_EXTENDED_FLAG_TSO                  0x6U
#define ETHERNET_PKT_EXTENDED_FLAG_OST                  0x7U

//
//Layout of Flags Field in Tx Packet Descriptor
//|31|30|29 |28 |27 |26 |25  |24  |23  |22  |21|20|19|18 |17 |16 |
//|x |x |SOP|EOP|CPC|CPC|SAIC|SAIC|VLIC|VLIC|x | x|x |TSE|CIC|CIC|
//

#define ETHERNET_PKT_FLAG_SOP_S                         29U
#define ETHERNET_PKT_FLAG_EOP_S                         28U
#define ETHERNET_PKT_FLAG_CPC_S                         26U
#define ETHERNET_PKT_FLAG_SAIC_S                        24U
#define ETHERNET_PKT_FLAG_VLIC_S                        22U
#define ETHERNET_PKT_FLAG_TSE_S                         18U
#define ETHERNET_PKT_FLAG_CIC_S                         16U

//
// Per packet control flags
//
#define ETHERNET_PKT_FLAG_TTSE              0x40000000U
#define ETHERNET_PKT_FLAG_SOP               0x20000000U
#define ETHERNET_PKT_FLAG_EOP               0x10000000U
#define ETHERNET_PKT_FLAG_CPC               0x0c000000U
#define ETHERNET_PKT_FLAG_SAIC              0x03000000U
#define ETHERNET_PKT_FLAG_VLIC              0x00C00000U
#define ETHERNET_PKT_FLAG_TSE               0x00040000U
#define ETHERNET_PKT_FLAG_CIC               0x00030000U

//
//VLAN Tag Insertion Flags
//
#define ETHERNET_PKT_FLAG_NO_VLAN           0x00000000U
#define ETHERNET_PKT_FLAG_VLAN_REMOVAL      0x00400000U
#define ETHERNET_PKT_FLAG_VLAN_INSERTION    0x00800000U
#define ETHERNET_PKT_FLAG_VLAN_REPLACE      0x00C00000U
//
//CRC insertion Control Flags
//
#define ETHERNET_PKT_FLAG_CRC_PAD_INS       0x00000000U
#define ETHERNET_PKT_FLAG_CRC_INS_NO_PAD    0x04000000U
#define ETHERNET_PKT_FLAG_CRC_PAD_DIS       0x08000000U
#define ETHERNET_PKT_FLAG_CRC_REPL_NO_PAD   0x0C000000U
//
//SA Insertion Flags
//
#define ETHERNET_PKT_FLAG_SA_NO_INS         0x00000000U
#define ETHERNET_PKT_FLAG_SA_INS            0x01000000U
#define ETHERNET_PKT_FLAG_SA_REPLACE        0x02000000U
//
//L3 L4 Checksum Control Flags
//
#define ETHERNET_PKT_FLAG_CS_NO_INS                         0x00000000U
#define ETHERNET_PKT_FLAG_CS_IP_INS                         0x00010000U
#define ETHERNET_PKT_FLAG_CS_IP_PAYLOAD_INS_NO_PSEUDO       0x00020000U
#define ETHERNET_PKT_FLAG_CS_IP_PAYLOAD_PSEUDO_INS          0x00030000U

#define ETHERNET_NUM_PORTS                  1U

#define ETHERNET_DMA_CHANNEL_NUM_0          0U
#define ETHERNET_DMA_CHANNEL_NUM_1          1U

//
#define ETHERNET_RX_NORMAL_DESC_RDES1_TSA_LBIT_POS          0xeU
#define ETHERNET_RX_CONTEXT_DESC_RDES3_CTXT_HBIT_POS        0x1eU



#define ETHERNET_DRV_DEVMAGIC            0x0acefaceU

#define ETHERNET_ERROR_CODE              (0x2000000U)
#define ETHERNET_ERROR_INFO              (ETHERNET_ERROR_CODE)
#define ETHERNET_ERROR_WARNING           (ETHERNET_ERROR_CODE | 0x10000000U)
#define ETHERNET_ERROR_MINOR             (ETHERNET_ERROR_CODE | 0x20000000U)
#define ETHERNET_ERROR_MAJOR             (ETHERNET_ERROR_CODE | 0x30000000U)
#define ETHERNET_ERROR_CRITICAL          (ETHERNET_ERROR_CODE | 0x40000000U)


#define ETHERNET_ERR_INVALID_HANDLE     (ETHERNET_ERROR_MAJOR + 1U)
#define ETHERNET_ERR_INVALID_PARAM      (ETHERNET_ERROR_MAJOR + 2U)
#define ETHERNET_ERR_BAD_PACKET         (ETHERNET_ERROR_MAJOR + 3U)

#define ETHERNET_RET_SUCCESS    0U
//
//Interrupt related defines
//
#define ETHERNET_GENERIC_INTERRUPT        0U
#define ETHERNET_TX_INTR_CH0                        1U
#define ETHERNET_TX_INTR_CH1                        2U
#define ETHERNET_RX_INTR_CH0                        3U
#define ETHERNET_RX_INTR_CH1                        4U
#define ETHERNET_NUM_INTERRUPTS               5U
//
// Define for deriving the offset of channel specific registers
//
#define ETHERNET_CHANNEL_OFFSET        (0x80U)

//
// Define for deriving the offset of Queue specific registers
//

#define ETHERNET_QUEUE_OFFSET          (0x40U)

//
//Define for Signalling Early Rx Completion
//
typedef enum
{
    ETHERNET_COMPLETION_NORMAL        = 0x00U, //!Normal Packet Completion
    ETHERNET_COMPLETION_EARLY         = 0x01U  //!<Master write to slave
} Ethernet_CompletionMode;

//
//These Flags are used by the LLD during the Interrupt callbacks
//Layout of Flags Field in  Completion Callback
//|31|30|29   |28 |27 |26 |25  |24  |23  |22  |21|20|19|18|17 |16 |
//|Tx|Rx|Early|
//
// To signal Tx, Rx and Early completion
//
#define ETHERNET_INTERRUPT_FLAG_TRANSMIT 0x80000000U
#define ETHERNET_INTERRUPT_FLAG_RECEIVE  0x40000000U
#define ETHERNET_INTERRUPT_FLAG_EARLY    0x20000000U

//*****************************************************************************
//
//! PTP Ingress/Egress Correction related defines follow.
//
//*****************************************************************************
#define ETHERNET_MAC_TIMESTAMP_CONTROL_DIGITAL_ROLLOVER                        \
                                       ETHERNET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR

#define ETHERNET_MAC_TIMESTAMP_CONTROL_BINARY_ROLLOVER          0x0U

#define ETHERNET_MAC_TIMESTAMP_CONTROL_DIGITAL_ROLLOVER_MAX     0x3B9AC9FFU
#define ETHERNET_MAC_TIMESTAMP_CONTROL_BINARY_ROLLOVER_MAX      0x7FFFFFFFU

//
// Sub nanosecond scalar value : (2^8) = 256
//
#define ETHERNET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_SCALAR   0x00000100U

//
// Asym correction (Ingress/Egress) is programmed by first scaling the
// nanoseconds asym by the value : (2^16) = 65536 = 0x10000
//
#define ETHERNET_MAC_TIMESTAMP_ASYM_CORR_SCALAR     0x10000U

//*****************************************************************************
//
//! PTP Higher Word related defines follow.
//
//*****************************************************************************
#define ETHERNET_MAC_TIMESTAMP_SYSTEM_TIME_SOURCE_INTERNAL      0x0U
#define ETHERNET_MAC_TIMESTAMP_SYSTEM_TIME_SOURCE_EXTERNAL                     \
                                    ETHERNET_MAC_TIMESTAMP_CONTROL_ESTI
#define ETHERNET_MAC_SYSTEM_TIME_HIGHER_WORD_NOT_VALID          0xFFFFFFFFU

//*****************************************************************************
//
//! PTP Offload related Enums and Structures follow.
//
//*****************************************************************************

/*
 * Triggers for two PTP message types are supported in the driver.
 * 1. Sync Message
 * 2. Peer Delay Request Message
 */
typedef enum
{
    ETHERNET_PTO_P_DELAY_REQ_MESSAGE_TRIGGER,
    ETHERNET_PTO_SYNC_MESSAGE_TRIGGER
}Ethernet_PTPOffloadMsgTrigger;

/*
 * The switch for automatic sending of Delay Request and Delay Response
 * messages when PTP Offload is enabled.
 */
typedef enum
{
    ETHERNET_PTO_DELAY_REQ_DELAY_RESP_DISABLE =
                                             ETHERNET_MAC_PTO_CONTROL_DRRDIS,
    ETHERNET_PTO_DELAY_REQ_DELAY_RESP_ENABLE =
                                             !ETHERNET_MAC_PTO_CONTROL_DRRDIS
}Ethernet_PTPOffloadDelayReqRespMode;

typedef enum
{
    ETHERNET_PTO_AUTO_SYNC_MESSAGE_ENABLE =
                                            ETHERNET_MAC_PTO_CONTROL_ASYNCEN,
    ETHERNET_PTO_AUTO_SYNC_MESSAGE_DISABLE =
                                            !ETHERNET_MAC_PTO_CONTROL_ASYNCEN
}Ethernet_PTPOffloadAutoSyncMode;

typedef enum
{
    ETHERNET_PTO_AUTO_P_DELAY_REQ_MESSAGE_ENABLE =
                                           ETHERNET_MAC_PTO_CONTROL_APDREQEN,
    ETHERNET_PTO_AUTO_P_DELAY_REQ_MESSAGE_DISABLE =
                                           !ETHERNET_MAC_PTO_CONTROL_APDREQEN
}Ethernet_PTPOffloadAutoPDelayReqMode;

typedef enum
{
    ETHERNET_PTO_P_DELAY_RESP_MESSAGE_DISABLE =
                                            ETHERNET_MAC_PTO_CONTROL_PDRDIS,
    ETHERNET_PTO_P_DELAY_RESP_MESSAGE_ENABLE =
                                           !ETHERNET_MAC_PTO_CONTROL_PDRDIS
}Ethernet_PTPOffloadPDelayRespMode;

typedef enum
{
    ETHERNET_PTP_OFFLOAD_ENABLE = ETHERNET_MAC_PTO_CONTROL_PTOEN,
    ETHERNET_PTP_OFFLOAD_DISABLE = !ETHERNET_MAC_PTO_CONTROL_PTOEN
}Ethernet_PTPOffloadEnableMode;

typedef enum
{
    ETHERNET_PTO_DELAY_REQ_DELAY_RESP_GENERATION,
    ETHERNET_PTO_AUTO_SYNC_MESSAGE,
    ETHERNET_PTO_AUTO_P_DELAY_REQ_MESSAGE,
    ETHERNET_PTO_P_DELAY_RESP_GENERATION,
} Ethernet_PTPOffloadModeType;

//*****************************************************************************
//
//! Log Message Interval structure that is needed to notify the driver of the
//! three values -
//! 1. Minimum Interval between successive Peer Delay Request messages
//! 2. Delay Request messages to Sync message ratio, that is for how many
//!    Sync messages that a slave receives, it should send a Delay Request
//!    message.
//! 3. Minimum Interval between successive Sync messages in the master.
//!
//! The driver programs these value in the corresponding register which is then
//! used to send automated PTP messages by the hardware when PTP Offloading is
//! enabled.
//
//*****************************************************************************
typedef struct
{
    int8_t logMinPdelayReqInterval;
    int8_t delayReqToSyncRatio;
    int8_t logSyncInterval;
}Ethernet_LogMsgIntervalConfig;

//*****************************************************************************
//
//! Source Port Identity structure that is needed to notify the driver of the
//! source_port_id value as needed by the PTP Offload Engine to frame the PTP
//! header in the hardware when PTP Offloading is enabled. This is a 10 Byte
//! long field as specified in the IEEE 1588 Protocol.
//
//*****************************************************************************
typedef struct
{
    uint32_t id0;
    uint32_t id1;
    uint32_t id2;

} Ethernet_SourcePortIdentity;

//*****************************************************************************
//
//! PTP Offload Configuration Parameters structure, that the application/higher
//! layer may use to set configuration and send this structure to the driver
//! to enable corresponding PTP Offload features.
//
//*****************************************************************************
typedef struct
{
    uint8_t domainNumber;
    Ethernet_PTPOffloadDelayReqRespMode ptoDelayReqRespMode;
    Ethernet_PTPOffloadAutoSyncMode ptoAutoPtpSyncMode;
    Ethernet_PTPOffloadAutoPDelayReqMode ptoAutoPDelayReqMode;
    Ethernet_PTPOffloadPDelayRespMode ptoPDelayRespMode;
    Ethernet_SourcePortIdentity srcPortId;
    Ethernet_LogMsgIntervalConfig logMsgIntervalConf;
}Ethernet_PTPOffloadConfigParams;



//*****************************************************************************
//
//! Statistics Software defines Structure that groups the different
//! RMON Statistics in the Peripheral. Refer to TRM for further details
//! of each of the elements
//
//*****************************************************************************


typedef struct  {
    //
    //TX Statistics
    //
    uint32_t txOctetCountGoodBad;   //0x714
    uint32_t txPacketCountGoodBad;  //0x718
    uint32_t txBroadcastPacketsGood; //0x71C
    uint32_t txMulticastPacketsGood; //0x720
    uint32_t tx64OctetsPacketsGood;
    uint32_t tx65to127OctetsPacketsGood;
    uint32_t tx128to255OctetsPacketsGood;
    uint32_t tx256to511OctetsPacketsGood;
    uint32_t tx512to1023OctetsPacketsGood;
    uint32_t tx1024toMaxOctetsPacketsGood;
    uint32_t txUnicastPacketsGoodBad;
    uint32_t txMulticastPacketsGoodBad;
    uint32_t txBroadcastPacketsGoodBad;
    uint32_t txUnderFlowErrorPackets;
    uint32_t txSingleCollisionGoodPackets;
    uint32_t txMultipleCollisionGoodPackets;
    uint32_t txDeferredPackets;
    uint32_t txLateCollisionPackets;
    uint32_t txExcessiveCollisionPackets;
    uint32_t txCarrierErrorPackets;
    uint32_t txOctetCountGood;
    uint32_t txPacketCountGood;
    uint32_t txExcessiveDeferralError;
    uint32_t txPausePackets;
    uint32_t txVLANPacketsGood;
    uint32_t txOSizePacketsGood;
    uint32_t reserved_1;
    //
    //RX Statistics
    //
    uint32_t rxPacketsCountGoodBad;
    uint32_t rxOctetCountGoodBad;
    uint32_t rxOctetCountGood;
    uint32_t rxBroadcastPacketsGood;
    uint32_t rxMulticastPacketsGood;
    uint32_t rxCRCErrorPackets;
    uint32_t rxAlignmentErrorPackets;
    uint32_t rxRuntErrorPackets;
    uint32_t rxJabberErrorPackets;
    uint32_t rxUnderSizePacketsGood;
    uint32_t rxOverSizePacketsGood;
    uint32_t rx64OctetsPacketsGoodBad;
    uint32_t rx65to127OctetsPacketsGoodBad;
    uint32_t rx128to255OctetsPacketsGoodBad;
    uint32_t rx256to511OctetsPacketsGoodBad;
    uint32_t rx512to1023OctetsPacketsGoodBad;
    uint32_t rx1024toMaxOctetsPacketsGoodBad;
    uint32_t rxUnicastPacketsGood;
    uint32_t rxLengthErrorPackets;
    uint32_t rxOutOfRangeTypePackets;
    uint32_t rxPausePackets;
    uint32_t rxFIFOOverFlowPackets;
    uint32_t rxVLANPacketsGoodBad;
    uint32_t rxWatchDogErrorPackets;
    uint32_t rxReceiveErrorPackets;
    uint32_t rxControlPacketsGood;

    //
    //LPI Related Statistics
    //
    uint32_t txLPIUsecCounter;
    uint32_t txLPITranCounter;
    uint32_t rxLPIUsecCounter;
    uint32_t rxLPITranCounter;
}Ethernet_Statistics;
//*****************************************************************************
//
//! Generic Hardware Descriptor Structure definition
//! that can be used for Transmit,Receive and Context Descriptors
//
//*****************************************************************************


typedef struct  {
    uint32_t des0;
    uint32_t des1;
    uint32_t des2;
    uint32_t des3;
} Ethernet_HW_descriptor;

typedef uint32_t Ethernet_Pkt_Flag_T;
typedef uint32_t Ethernet_Pkt_Extended_Flag_T;

//*****************************************************************************
//
//! EMAC Packet Structure, that the application/higher layer
//! uses to Send a packet
//! and Driver notifies to the higher layer using this structure
//! For Multiple Packets/Buffers this structure is chained
//
//*****************************************************************************

typedef struct Ethernet_Pkt_Desc_T

{
    /**< Next descriptor pointer use this if multiple
     descriptors are chained else keep it 0 */
    struct Ethernet_Pkt_Desc_T     *nextPacketDesc;
    /** < Pointer to the Buffer/Header if TSO is enabled                      */
    uint8_t                            *dataBuffer;
    /** < Pointer to Second Buffer               */
    uint8_t                             *dataBuffer2;
     /**< Physical Length of the buffer (read only)                         */
    uint32_t                            bufferLength;
    /**< Physical Length of the buffer dataBuffer2 (read only)             */
    uint32_t                            buffer2Length;
    /**< Tx/Rx Channel 0-1 (Valid on SOP only)                           */
    uint32_t                            pktChannel;
    /**< Length of Packet (Valid on SOP only)
        (same as validLength on single frag Pkt)  */
    uint32_t                            pktLength;
     /**< Packet flags, SOP, EOP                                             */
    Ethernet_Pkt_Flag_T            flags;
         /**< No of frags in packet (SOP only), normally 1                   */
    uint32_t                              numPktFrags;
    /* Data Offset usually set it to Zero can be used if buffer does
    not start from address 0 of pBuffer*/
    uint32_t                 dataOffset;
    /* No of bytes of packet valid in this buffer*/
    uint32_t                 validLength;
    /*
     * Rx Descriptor use - case:
     * Thes two fields are filled by the hardware and returned to application
     * in the callback.
     *
     * Tx Descriptor use - case:
     * This timestamp placeholder can also be used by the application to send
     * a custom timestamp to the driver (tx context descriptor for one - step
     * timestamping).
     */

    uint32_t                  timeStampLow;
    uint32_t                  timeStampHigh;

    /* Flag to indicate to the application that a buffer is discarded. */
    uint8_t          nextBufferDiscarded;



    Ethernet_Pkt_Extended_Flag_T        extendedFlags;

    uint16_t innerVlanTag;
    uint32_t mssTso;
    uint16_t vlanTag;


}Ethernet_Pkt_Desc;

//*****************************************************************************
//
//! MAC Address Structure to by used
//! by Higher layer to pass MAC address to the Driver
//
//*****************************************************************************

typedef struct  {
    uint8_t channelNum;
    /* Receive Channel number to which the MAC address to be assigned */
    uint8_t addr[6];
    /* MAC address specific to channel */
} Ethernet_MACAddrConfig;

//*****************************************************************************
//
//! EMAC Wrapper Subsystem Configuration used in Initializing the
//! Configuration during Ethernet_Init
//
//*****************************************************************************



typedef struct  {
    uint8_t         phyIntfSel;
    uint8_t     LoopBackModeClkSel;
    uint8_t     clkSrcSel;
    uint8_t         flowControlEn;
} Ethernet_SubSystemConfig;

//*****************************************************************************
//
//! Filter Coniguration Structure
//! That maps to MAC Filter Configuration Register of the MAC
//
//*****************************************************************************
typedef struct  {
    uint32_t promiscuousMode:1;
    uint32_t hashUnicast:1;
    uint32_t hashMulticast:1;
    uint32_t daInverseFilter:1;
    uint32_t passAllMulticast:1;
    uint32_t disableBroadCastPackets:1;
    uint32_t passControlPackets:2;
    uint32_t saInverseFilter:1;
    uint32_t saFilterEnable:1;
    uint32_t hashPerfectFilter:1;
    uint32_t reserved1:5;
    uint32_t vlanFilterEnable:1;
    uint32_t reserved2:3;
    uint32_t l3L4FilterEnable:1;
    uint32_t dropNonTCP:1;
    uint32_t reserved3:9;
    uint32_t receiveAll:1;
}Ethernet_MACFilterConfig;
//*****************************************************************************
//
//! Generic Handle structure
//! Not used now but for NDK Layer
//
//*****************************************************************************

typedef void   *Ethernet_Handle;



typedef enum
{
    ETHERNET_TX_CHANNEL_TSE_DISABLE ,
   ETHERNET_TX_CHANNEL_TSE_ENABLE
}Ethernet_EnableTSO;

//*****************************************************************************
//
//! Per Channel Information Structure
//! Stores the individual channel Parameters
//
//*****************************************************************************
typedef struct
{
   uint32_t     chNum;
    /**< Channel Number                                                     */
   uint32_t     chDir;
    /**< Channel Direction                                                  */
   uint32_t     numBD;
    /**< Maximum Number of Buffer Descriptors allocated for this channel    */
   uint32_t     bufSize;
    /**< Buffer size                                                        */
   uint32_t     enableSplitHeader;
    /**< Enables the Split Header Option in the RX Path */
   uint32_t     descriptorSkipLength;
   /** For Storing the flag whether the
   Store and Forward mode is enabled or Threshold mode is enabled **/
   uint32_t     storeNForward;
    /**Threshold level for transmit and receive used by hardware
    only in Threshold mode**/
   uint32_t     queueThreshold;
    /** It has to be a multiple of 8
    For Receive, the number of beats(Each beat is 32 bit / 4 bytes)
    This plays a role in when Early Interrupts are generated for
    received packets.
    For Transmit, the number of bytes to be transferred in a block
    by the DMA**/
   uint32_t     burstLength;
   /**<Queue Size for Tx and Rx should be in range
   ETHERNET_MTL_Q_OP_MODE_QSIZE_256  to ETHERNET_MTL_Q_OP_MODE_QSIZE_4096 */
   uint32_t     dmaQueueSize;
   /** Used only for Receive Channel: Configures the Receive buffer size
    For Threshold mode: It is recommended to configure this as integral multiple
    of burstLength.
    Each Receive buffer is of this size*/
   uint32_t     dmaBufferSize;
   //**< Enable/Disable of Transport Segmentation in Hardware                */
   Ethernet_EnableTSO enableTSE;
   /** used only with TCP Segmentation Offload Enabled**/
   uint16_t    maximumSegmentSize;
}Ethernet_ChInfo;

//*****************************************************************************
//
//! This structure maps to the bit fields of DMA Mode of Ethernet module.
//! Used to fill DMA Mode register. Default values are configured in
//! Ethernet_getInitConfig() and can be overwritten before calling
//! Ethernet_getHandle() API
//
//*****************************************************************************
typedef struct {
    uint32_t SoftwareReset:1;
    uint32_t TxRxArbitration:1;
    uint32_t TransmitArbitration:3;
    uint32_t Reserved4:3;
    uint32_t DescriptorPostedWrite:1;
    uint32_t Reserved3:2;
    uint32_t TransmitPriority:1;
    uint32_t PriorityRatio:3;
    uint32_t Reserved2:1;
    /** DMA Interrupt mode can be one of the following values:
    ETHERNET_DMA_MODE_INTM_MODE0
    ETHERNET_DMA_MODE_INTM_MODE1
    ETHERNET_DMA_MODE_INTM_MODE2
    Refer TRM for the definition of these modes */
    uint32_t InterruptMode:2;
    uint32_t Reserved1:14;
}Ethernet_DmaMode;
typedef enum
{
    ETHERNET_EEE_RX_LPI_MAGICPKT_RECEIVED = 0U,
    ETHERNET_EEE_RX_LPI_RMTWKUP_PKT_RECEIVED = 1U
}Ethernet_EEE_eventType;


//*****************************************************************************
//
//! Init Configuration Structure used in Ethernet_getHandle
//! The Ethernet_getInitConfig() API fills a known good value of this structure
//! can be modified to change the default settings.
//! An instance of this is stored fully in the Global Book Keeping structure
//! for Maintaining the Configuration Specified by the Higher Layer/User
//
//*****************************************************************************

typedef struct
{
    /**Link Speed- Currently not used by driver.
    use Ethernet_setMACConfiguration() to set different Speed
    only 10 / 100 Mbps supported*/
    uint8_t                        linkSpeed;
    /**Link Mode ETHERNET_MAC_CONFIGURATION_DM_FULL_DUPLEX or
    ETHERNET_MAC_CONFIGURATION_DM_HALF_DUPLEX                                 */
      uint8_t                      linkMode;
    /** Total number of MAC addresses to be assigned for
    all receive channels - not used by driver currently. */
    uint8_t                        totalNumMacAddrs;
    /** Enables or disables the Loopback mode
    ETHERNET_MAC_CONFIGURATION_LM_LOOPBACK_ENABLED or
    ETHERNET_MAC_CONFIGURATION_LM_LOOPBACK_DISABLED */
    uint8_t                        loopbackMode;
    /** Not used by driver currently - For Future use*/
    Ethernet_MACAddrConfig         *macAddr;
    /** Subsystem Configuration Settings */
    Ethernet_SubSystemConfig       emacSSConfig;
    /*DMA Mode Register Settings */
    /**Priority Ratio between Tx and RX.
    Use macro ETHERNET_DMA_OPERATION_MODE_PR_TXx_RX1 */
    uint8_t                        priorityRatio;
    /**Transmit Arbitration Algorithm when multiple Tx DMAs are selected
    - reserved for future use.Use Ethernet_setDMAMode() to set this parameter
    of DMA*/
    uint8_t                        transmitArbitrationAlgorithm;
    /** DMA Arbitration between Tx and Rx Path - reserved for future use
    use Ethernet_setDMAMode() to set this parameter */
    uint8_t                        dmaArbitrationScheme;
    /**MAC Transfer Layer Operation Mode Settings Tx Scheduling either
    ETHERNET_MTL_OPERATON_MODE_SCHALG_STRICT_PRIORITY or
    ETHERNET_MTL_OPERATON_MODE_SCHALG_WRR*/
    uint8_t                        txSchedulingAlgoritm;
    /**Receive Arbitration algorithm must be ETHERNET_MTL_OPERATION_MODE_RAA_SP
    or ETHERNET_MTL_OPERATION_MODE_RAA_WSP*/
    uint8_t                        receiveArbitrationAlgorithm;

    /** MAC Filter Settings not currently used by this driver.
    Use Ethernet_setMACPacketFilter() API for setting the Filter configs*/
    Ethernet_MACFilterConfig   macFilterConfig;
    /** Not currently used by driver. reserved for Future Use */
    uint32_t                        noofPacketsRxBuffer;
    /** Maximum Packet Length of Rx Buffer. Not currently used by Driver*/
    uint32_t                        maxPacketLengthRxBuffer;
    /** Channel Configuration for each channel available in Hardware*/
    Ethernet_ChInfo
        chInfo[ETHERNET_MAX_DMA_DIR][ETHERNET_MAX_NUM_DMA_CHANNELS];
    /** Number of DMA Channels 1 to ETHERNET_MAX_NUM_DMA_CHANNELS */
    uint32_t                        numChannels;
    /** Packet Maximum Transfer Unit. For checking Packet Length in
    Ethernet_sendPacket() API */
    uint32_t                        pktMTU;
    /** DMA Mode configuration settings used by Ethernet_getHandle() API */
    Ethernet_DmaMode                dmaMode;

    /** can be used by higher layer for buffer handling */
    void                             *pBuf;
    /** This must be passed by application before calling Ethernet_getHandle()
    API. This is the Receive Buffer for incoming packets*/
    uint8_t                         *rxBuffer;
    /** Receive packet call back  called when a Packet is Received by the LLD
     */
    Ethernet_Pkt_Desc *  (*pfcbRxPacket)(Ethernet_Handle handleApplication,
        Ethernet_Pkt_Desc *pPacket);
     /** Get packet call back  called by this driver when it needs a packet
     from Application                                        */
    Ethernet_Pkt_Desc * (*pfcbGetPacket)(void);
     /** Free packet call back called after the completion of Tx and
       when the buffer needs to handled back to application */
    void             (*pfcbFreePacket)(Ethernet_Handle handleApplication,
                        Ethernet_Pkt_Desc *pPacket);
     /** Clear enqueued packets call back called during RBU error to drop
     all enqueued RX packets*/
    void            (*pfcbDeletePackets)();
     /** Callback for Asynchronous EEE Events Magic Packet Received
     or Remote Wakeup Packet Received */
     void          (*pfcbLPIPacketReceived)(Ethernet_EEE_eventType type,
                               void *buff);

}Ethernet_InitConfig;
typedef enum
{
     ETHERNET_SS_PHY_INTF_SEL_MII  = 0U,
        /* Values 1-3 Reserved*/
     ETHERNET_SS_PHY_INTF_SEL_RMII = 4U,
     ETHERNET_SS_PHY_INTF_SEL_REVMII = 7U
} Ethernet_SS_phyInterfaceMode;
typedef enum
{
    ETHERNET_SS_CLK_SRC_EXTERNAL = 0U ,
    ETHERNET_SS_CLK_SRC_INTERNAL = 1U
}Ethernet_SS_clockSelection;

//*****************************************************************************
//
//! This Structure should be passed to Ethernet_InitInterface() API
//
//*****************************************************************************
typedef struct
{
    uint32_t ssbase; //!Base Address of Subsystem Wrapper Registers
    uint32_t enet_base; //!Base Address of Ethernet Registers
    Ethernet_SS_phyInterfaceMode phyMode; //!Physical interface selected
    //!Clock Configuration selection for ReVMII/RMII modes
    Ethernet_SS_clockSelection clockSel;
    uint8_t localPhyAddress; //!used in case of RevMII
    uint8_t remotePhyAddress; //!used in case of RevMII
    /** Peripheral Number to be used when calling the
       ptrPlatformPeripheralEnable(), ptrPlatformPeripheralReset() APIs*/
    uint32_t        peripheralNum;
    /** Platform specific Peripheral Enable API to be called to enable
    Ethernet, Ethernet Subsystem module clocks */
    void             (*ptrPlatformPeripheralEnable)(uint32_t peripheralNum);
    /** Platform specific Peripheral Reset API to be called to reset
    Ethernet and Ethernet Subsystem module */
    void             (*ptrPlatformPeripheralReset)(uint32_t peripheralNum);
    /** Platform specific Interrupt Enable API to enable a specific interrupt
    shall be called with interruptNum entries*/
    void             (*ptrPlatformInterruptEnable)(uint32_t interruptNumber);
    /** Platform specific Interrupt Disable API to enable a specific interrupt
    shall be called with interruptNum entries*/
    void             (*ptrPlatformInterruptDisable)(uint32_t interruptNumber);
    /** Platform specific Interrupt Numbers for Ethernet interrupts that
    should be passed to ptrPlatformInterruptEnable() and
    ptrPlatformInterruptDisable() APIs*/
    uint32_t interruptNum[ETHERNET_NUM_INTERRUPTS];
}Ethernet_InitInterfaceConfig;
//*****************************************************************************
//
//! Generic Packet Queue Structure - Contains a head and Tail pointer
//! Two instances of such Structure is used in each channel
//
//*****************************************************************************
typedef struct  {
    /**
     * @brief   Number of packets in queue
     */
    uint32_t                   count;

    /**
     * @brief   Pointer to first packet
     */
    Ethernet_Pkt_Desc          *head;

    /**
     * @brief   Pointer to last packet
     */
    Ethernet_Pkt_Desc          *tail;
} Ethernet_PKT_Queue_T;

//*****************************************************************************
//
//! Forward Declaration of Device Structure see structure Definition below
//!
//
//*****************************************************************************

typedef struct Ethernet_Devicest Ethernet_Device;

//*****************************************************************************
//
//! Per Channel Channel Descriptor Structure
//! Maintains two queues one for Wait Queue that is submitted by the User
//! Desc Queue that is Queued to the Hardware
//! It also maintains the Descriptor pointers
//*****************************************************************************

typedef struct  {
    Ethernet_Device                *devicePtr;
    Ethernet_PKT_Queue_T           descQueue;
    /**< Packets queued as desc                                             */
    Ethernet_PKT_Queue_T           waitQueue;
    /**< Packets waiting for TX desc                                        */
    Ethernet_ChInfo                *chInfo;
    /**< Channel info                                                       */
    uint32_t                       descMax;
    /**< Max number of desc (buffs)                                         */
    uint32_t                       descCount;
   /**< Current number of desc                                             */
    Ethernet_HW_descriptor       *descFirst;

    uint32_t indexFirst;
    uint32_t indexLast;
    uint32_t indexRead;
    uint32_t indexWrite;
    uint32_t                       dmaInProgress;
    /* Flag to indicate DMA transaction is in progress */
} Ethernet_DescCh;

typedef Ethernet_DescCh Ethernet_TxChDesc;
typedef Ethernet_DescCh Ethernet_RxChDesc;

//*****************************************************************************
//
//!DMA Object that combines the  Tx and Rx Channel Descritor Structures
//!
//
//*****************************************************************************

typedef struct
{
    Ethernet_TxChDesc   txDma[ETHERNET_MAX_NUM_DMA_CHANNELS];
    Ethernet_RxChDesc  rxDma[ETHERNET_MAX_NUM_DMA_CHANNELS];
    bool    chIsInit[ETHERNET_MAX_DMA_DIR][ETHERNET_MAX_NUM_DMA_CHANNELS];
}Ethernet_DmaObj;

//*****************************************************************************
//
//! Base Address Definition Structure
//! Stores the Base Address of the Subsystem and the Ethernet module
//
//*****************************************************************************

typedef struct  {
    uint32_t ss_base;
    uint32_t enet_base;
 }Ethernet_BaseConfig;

//*****************************************************************************
//
//! Global Book keeping Structure maintained throughout
//!
//
//*****************************************************************************

struct Ethernet_Devicest{
    /**The Base addresses populated from the _InitInterfaceConfig structure
    in the Ethernet_initInterface() API call*/
    Ethernet_BaseConfig         baseAddresses;
    /** Main DMA Book keeping structure of the driver*/
    Ethernet_DmaObj             dmaObj;
    /** Handle provided to application with callbacks*/
    Ethernet_Handle             handleApplication[ETHERNET_NUM_PORTS];
    /** Phy number - useful if phy number is discovered - RFU*/
    uint32_t                    phyNum;
    /** Pointer to Descriptor array*/
    Ethernet_HW_descriptor    *descs;
    /** Pointer to Transmit Descriptor Array*/
    Ethernet_HW_descriptor    *txDesc;
    /** Pointer to Receive Descriptor Array*/
    Ethernet_HW_descriptor    *rxDesc;
    /** Receive Buffer Address initialized in Ethernet_getHandle() API*/
    uint8_t                     *rxBuffer;
    /** Buffer index for the sample simple buffer handling function of this
    driver Ethernet_getPacketBuffer()*/
    uint8_t                     rxBuffIndex;
    /** Maximum Size of Ethernet Packet */
    uint32_t                    pktMTU;
    /** A reference number stored to make sure that this structure is not
    corrupted*/
    uint32_t                    devMagic;
    /** The Driver initialization configuration structure returned in
    Ethernet_initInterface() can be filled with known good values with a call to
    Ethernet_getInitConfig() and used by Ethernet_getHandle() to initialize the
    hardware */
    Ethernet_InitConfig         initConfig;
    /** The following parameters are copied from the
    Ethernet_InitInterfaceConfig structure when the driver is initialized with
    Ethernet_initInterface() API call */
    void             (*ptrPlatformPeripheralEnable)(uint32_t PeripheralName);
    void             (*ptrPlatformPeripheralReset)(uint32_t PeripheralName);
    void             (*ptrPlatformInterruptEnable)(uint32_t interruptNumber);
    void             (*ptrPlatformInterruptDisable)(uint32_t interruptNumber);
    uint32_t interruptNum[ETHERNET_NUM_INTERRUPTS];
};


//
//Define for Signalling Early Rx Completion
//
typedef enum
{
    //
    //When Static it indicates that the routing is based on the
    //Static configuration configured
    //
    ETHERNET_RX_DMA_QUEUE_STATIC        = 0x00U,

    //
    //When Dynamic this bit indicates that the packets received in
    //Queue are routed to a particular DMA channel as decided
    //in the MAC Receiver based on the DMA channel number
    //programmed in the L3-L4 filter registers, or the Ethernet DA
    //address
    //
    ETHERNET_RX_DMA_QUEUE_DYNAMIC    = 0x01U
} Ethernet_RxDMAQueueMode;

//*****************************************************************************
//
//! The structure for Rx Queue Configuration
//! Used by the driver in Rx Queue Configuration
//
//*****************************************************************************
typedef struct {
           uint32_t reserved_0:4;
            uint32_t PTPQ:1;
           uint32_t reserved_1:7;
           uint32_t UPQ:1;
           uint32_t reserved_2:3;
           uint32_t MCBCQ:1;
           uint32_t reserved_3:3;
           uint32_t MCBCQEN:1;
           uint32_t reserved_4:1;
           uint32_t TPQC:1;
           uint32_t reserved_5:9;
} Ethernet_RxQControl;

typedef enum
{
    ETHERNET_CHANNEL_0 ,
    ETHERNET_CHANNEL_1
} Ethernet_ChannelNum;

typedef enum
{
    ETHERNET_QUEUE_0 ,
    ETHERNET_QUEUE_1
} Ethernet_QueueNum;

typedef enum
{
    ETHERNET_SET_CONFIG_VLAN_TX_OUTER ,
    ETHERNET_SET_CONFIG_VLAN_TX_INNER,
    ETHERNET_SET_CONFIG_VLAN_TX_CHANNEL_BASED,
    ETHERNET_SET_CONFIG_VLAN_TX_DOUBLE_VLAN,
    ETHERNET_SET_CONFIG_VLAN_TX_PACKET_BASED,
    ETHERNET_SET_CONFIG_VLAN_INNER_TX_PACKET_BASED,
    ETHERNET_SET_CONFIG_DOUBLE_VLAN,
    ETHERNET_SET_CONFIG_FILTER_VLAN_PERFECT,
    ETHERNET_SET_CONFIG_FILTER_VLAN_HASH,
    ETHERNET_SET_CONFIG_FILTER_L3_L4,
    ETHERNET_SET_CONFIG_EEE_TX,
    ETHERNET_SET_CONFIG_EEE_TX_ENABLE,
    ETHERNET_SET_CONFIG_EEE_TX_DISABLE,
    ETHERNET_SET_CONFIG_RX_MAGIC_DETECT_ENABLE,
    ETHERNET_SET_CONFIG_RX_REMOTE_WAKEUP_FILTER,
    ETHERNET_SET_CONFIG_RX_REMOTE_WAKEUP_ENABLE,
    ETHERNET_SET_CONFIG_MAX
}Ethernet_SetConfigParam;

typedef enum
{
   ETHERNET_VLAN_TX_NONE,
   ETHERNET_VLAN_TX_DELETE,
   ETHERNET_VLAN_TX_INSERT,
   ETHERNET_VLAN_TX_REPLACE
}Ethernet_VlanTxTagControl;

typedef enum
{
    ETHERNET_VLAN_TYPE_C ,// CVLAN TYPE 0x8100 Tag
    ETHERNET_VLAN_TYPE_S
}Ethernet_VlanType;

typedef enum
{
    ETHERNET_VLAN_TAG_SOURCE_REG,
    ETHERNET_VLAN_TAG_SOURCE_DESC
}Ethernet_VlanTagSource;

//*****************************************************************************
//
//! The structure for VLAN Tag Configuration
//! Used in Transmit VLAN Tagging
//
//*****************************************************************************
typedef struct
{
    //!16 bit VLAN ID
    uint16_t vlan_tag;
    //!Whether the tag has to inserted/replaced/Deleted
    Ethernet_VlanTxTagControl  vlanTagControl;
    //!S-VLAN or C-VLAN Type
    Ethernet_VlanType  vlanType;
}Ethernet_VlanConfig;

//*****************************************************************************
//
//! The structure for Dual VLAN Tag Configuration
//! Used in Transmit Dual VLAN Tagging
//
//*****************************************************************************
typedef struct
{
     Ethernet_VlanConfig outerVLANConfig;
     Ethernet_VlanConfig innerVLANConfig;

 }Ethernet_DoubleVLANConfig;

//*****************************************************************************
//
//! The structure for Channel based VLAN Tag Insertion Configuration
//! Used in Transmit VLAN Tagging
//
//*****************************************************************************
typedef struct
{
    //!16 bit VLAN ID
    uint16_t vlan_tag;
    //!S-VLAN or C-VLAN Type
    Ethernet_VlanType  vlanType;
    //! Channel Number
    Ethernet_ChannelNum channelNum;

}Ethernet_VLANCBTIConfig;
//
//Rx Filter Configuration
//
typedef enum
{
    ETHERNET_VLAN_PERFECT_FILTER_DISABLED,
    ETHERNET_VLAN_PERFECT_FILTER_ENABLED
}Ethernet_VlanRxPerfectFilterEnable;

typedef enum
{
    ETHERNET_VLAN_PERFECT_FILTER_COMPARE_16BITS,
    ETHERNET_VLAN_PERFECT_FILTER_COMPARE_12BITS
}Ethernet_VlanRxPerfectFilterCompareMode;

typedef enum
{
   ETHERNET_VLAN_PERFECT_FILTER_TYPE_COMPARISON_ENABLED,
    ETHERNET_VLAN_PERFECT_FILTER_TYPE_COMPARISON_DISABLED
}Ethernet_VlanRxPerfectFilterTypeComparison;

typedef enum
{
    ETHERNET_VLAN_RX_FILTER_INNER_VLAN_DISABLED,
    ETHERNET_VLAN_RX_FILTER_INNER_VLAN_ENABLED
}Ethernet_VlanRxFilter_InnerVLANEnable;

typedef enum
{
    ETHERNET_DMA_CHANNELNUM_DISABLED,
    ETHERNET_DMA_CHANNELNUM_ENABLED
}Ethernet_DMA_channelEnableDisable;

//*****************************************************************************
//
//! The structure for VLAN Perfect Filter Configuration
//! Used in Receive VLAN Filter
//
//*****************************************************************************
typedef struct
{
    uint8_t filterid;
    //!<Index of VLAN Filter 0-3
    uint16_t vlanid;
    //!<VLAN ID to be compared with
    Ethernet_VlanRxPerfectFilterEnable vlanEnableDisable;
    //!<Filter is Enabled or Disabled
    Ethernet_VlanRxPerfectFilterCompareMode vlanFilterMode;
    //!<12 bit or 16 bit Comparison
    Ethernet_VlanRxPerfectFilterTypeComparison vlanPerfectTypeComparisonDisable;
    //!<Disable or enable Type comparison
    //
    //Set if SVLAN comparison Reset for CVLAN
    //
    Ethernet_VlanType vlanType;
    //!<CVLAN 0x8100 or SVLAN 0x88A8
    Ethernet_VlanRxFilter_InnerVLANEnable innerVLANEnabled;
    //!<InnerVLAN comparison Enable
    Ethernet_DMA_channelEnableDisable dmaChannelEnable;
    //!<DMA Channel number enable
    Ethernet_ChannelNum dmaChannelNum;
    //!< DMA Channel Num to which matching packets received should be Routed
}Ethernet_VLAN_Perfect_FilterParams;

//*****************************************************************************
//
//! The structure for VLAN Hash Filter
//! Used in Receive VLAN Filtering
//
//*****************************************************************************
typedef struct
{
    Ethernet_VlanRxFilter_InnerVLANEnable innerVLANEnabled;
    uint16_t hashFilterMap;
}Ethernet_Vlan_Hash_FilterParams;

//*****************************************************************************
//
//! Value that can be passed to Ethernet_setConfig() as the buffPtr
//! parameter.
//! If layer3ProtocolSel is 1(for IPv6) make sure only
//! either of layer3IPDestAddressMatchEnable or layer3IPSrcAddressMatchEnable
//! is set
//
//*****************************************************************************
typedef struct
{
    uint8_t filterid;//!< Filter number 0-3
    Ethernet_DMA_channelEnableDisable dmaChannelEnable;
    //!< Channel Num Enabled/Disabled
    Ethernet_ChannelNum dmaChannelNum;
    //!< DMA Channel Number where the packets should be destined if passes
    uint8_t layer4DestinationPortMatchEnable;
    //!< If Set Enables Destination Port Matching for L4
    uint8_t layer4SourcePortMatchEnable;
    //!< If Set Enables Source Port Matching for L4
    uint8_t layer4ProtocolSel;//!< 0- TCP 1-UDP
    uint16_t layer4DestinationPort;
    //!< 16bit Layer 4 Destination Port number to be matched
    uint16_t layer4SourcePort;
    //!<16bit Layer 4 Port Source Port number to be matched
    //
    //For L3HDBM
    //
    uint8_t layer3ProtocolSel;
    //!<0- IPv4 1- IPV6
    uint8_t layer3DestHigherBitsMask;
    //!< Number of Bits to be masked for Layer 3 Destination Address
    uint8_t layer3SrcHigherBitsMask;
    //!< Number of Bits to be masked for Layer 3 Source Address
    uint8_t layer3IPDestAddressMatchEnable;
    //!< Enables Comparison of IP Dest Address
    uint8_t layer3IPSrcAddressMatchEnable;
    //!<Enables Comparison of IP Src Address
    uint32_t layer3Address0;
    //!< Source Address for IPv4 or Bits[31:0] for IPv6
    uint32_t layer3Address1;
    //!< Destination Address for IPv4 or Bits[63:32] for IPv6
    uint32_t layer3Address2;
    //!< Bits[95:64] for IPv6 ,Unused for IPv4
    uint32_t layer3Address3;
    //!< Bits[127:96] for IPv6 ,Unused for IPv4
}Ethernet_L3_L4_FilterParams;

//*****************************************************************************
//
//! The structure for L3/L4 Filter configuration
//! Used by the driver in L3/L4 Filter Configuration programming
//
//*****************************************************************************
typedef struct {
           uint32_t L3PEN:1;
           uint32_t reserved_0:1;
           uint32_t L3SAM:1;
           uint32_t L3SAIM:1;
           uint32_t L3DAM:1;
           uint32_t L3DAIM:1;
           uint32_t L3HSBM:5;
           uint32_t L3HDBM:5;
           uint32_t L4PEN:1;
           uint32_t reserved_1:1;
           uint32_t L4SPM:1;
           uint32_t L4SPIM:1;
           uint32_t L4DPM:1;
           uint32_t L4DPIM:1;
           uint32_t reserved_2:2;
           uint32_t DMACHN:1;
           uint32_t reserved_3:3;
           uint32_t DMACHEN:1;
           uint32_t reserved_4:3;
} Ethernet_L3_L4_Control;

//*****************************************************************************
//
//! The structure for Energy Efficient Ethernet Configuration(EEE)
//! Used in Transmit EEE configuration
//
//*****************************************************************************
typedef struct
{
//
//b31   |b30   |b29   |b28      |b27   |
//LSTVAL|TWTVAL|LETVAL|TMICROVAL|PLSVAL|
//b3.......|b2    |b1 |b0
//TXCLKGATE|LPITXA|PLS|Rsvd
//
    uint32_t flags;
    //!<Specifies minimum time in Milliseconds for which Link Status
    //!< has to be up for LPI pattern to be sent to PHY from MAC
    //!< Hardware default is 1 Second as per IEEE Standard
    uint16_t linkStatusTimer;
    //!< Specifies the minimum time for which MAC should wait to
    //!< from when it stops sending LPI to when it starts transmission
    //!< specified in micro Seconds
    uint16_t transitionWaitTimer;
    //!<Time in micro Seconds MAC will wait to enter EEE
    //!<Bits 0-2 reserved Granularity in Steps of 8 micro seconds
    uint32_t   entryTimer;
    //!< Number of Clock cycles of IP in 1 us
    //! < If clock is 125 Mhz then program 125 -1 =124
    uint16_t    tickOneMicroSecCounter;
}Ethernet_EEE_Tx_Params;

#define ETHERNET_EEE_TX_CONTROL_LST_VALID 0x80000000U
#define ETHERNET_EEE_TX_CONTROL_TWT_VALID 0x40000000U
#define ETHERNET_EEE_TX_CONTROL_LET_VALID  0x20000000U
#define ETHERNET_EEE_TX_CONTROL_TMICRO_VALID    0x10000000U
#define ETHERNET_EEE_TX_CONTROL_PLS_VALID   0x80000000U
#define ETHERNET_EEE_TX_CONTROL_PLS_UP      0x00000002U
#define ETHERNET_EEE_TX_CONTROL_AUTOEEE_ENABLED 0x00000004U
#define ETHERNET_EEE_TX_CONTROL_EEE_ENABLED 0x00000001U
#define ETHERNET_EEE_TX_CONTROL_TXCLKGATE_ENABLED 0x00000008U
//*****************************************************************************
//
//! The structure for Remote Wake up Filter Configuration.
//! Used in Receive EEE Path
//! The device supports 1 to ETHERNET_RWKUP_FILTER_NUM number of filters
//! This structure configures the filters for the same.
//
//*****************************************************************************
typedef struct
{
    /** The CRC of the selected bytes for filter 0 */
    uint16_t filterCRC0;
    /** The CRC of the selected bytes for filter 1 */
    uint16_t filterCRC1;
    /** The CRC of the selected bytes for filter 2 */
    uint16_t filterCRC2;
    /** The CRC of the selected bytes for filter 3 */
    uint16_t filterCRC3;
    /**The Bytes to be selected for Filter 0.A bit set to 1 selects that byte*/
    uint32_t filterByteMask0;
    /**The Bytes to be selected for Filter 1.A bit set to 1 selects that byte*/
    uint32_t filterByteMask1;
    /**The Bytes to be selected for Filter 2.A bit set to 1 selects that byte*/
    uint32_t filterByteMask2;
    /**The Bytes to be selected for Filter 3.A bit set to 1 selects that byte*/
    uint32_t filterByteMask3;
    /**The offset in incoming packet from where filter 0 has to be applied*/
    uint8_t filterOffset0;
    /**The offset in incoming packet from where filter 1 has to be applied*/
    uint8_t filterOffset1;
    /**The offset in incoming packet from where filter 2 has to be applied*/
    uint8_t filterOffset2;
    /**The offset in incoming packet from where filter 3 has to be applied*/
    uint8_t filterOffset3;
    /**The filter commands for the filter 0 can be an OR of
        ETHERNET_RWKUP_FILTER_COMMAND_ENABLE - this must be set to enable filter
        ETHERNET_RWKUP_FILTER_COMMAND_AND_PREVIOUS - implements Boolean logic
        of combining with previous filter
        ETHERNET_RWKUP_FILTER_COMMAND_INVERSE - reverses logic of CRC function
        that rejects packets with matching CRC value
        ETHERNET_RWKUP_FILTER_COMMAND_MULTICAST - applies only to multicast
        packets
    */
    uint8_t filterCommand0;
    /**The filter commands for the filter 1 can be an OR of
        ETHERNET_RWKUP_FILTER_COMMAND_ENABLE - this must be set to enable filter
        ETHERNET_RWKUP_FILTER_COMMAND_AND_PREVIOUS - implements Boolean logic
        of combining with previous filter
        ETHERNET_RWKUP_FILTER_COMMAND_INVERSE - reverses logic of CRC function
        that rejects packets with matching CRC value
        ETHERNET_RWKUP_FILTER_COMMAND_MULTICAST - applies only to multicast
        packets
    */
    uint8_t filterCommand1;
    /**The filter commands for the filter 2 can be an OR of
        ETHERNET_RWKUP_FILTER_COMMAND_ENABLE - this must be set to enable filter
        ETHERNET_RWKUP_FILTER_COMMAND_AND_PREVIOUS - implements Boolean logic
        of combining with previous filter
        ETHERNET_RWKUP_FILTER_COMMAND_INVERSE - reverses logic of CRC function
        that rejects packets with matching CRC value
        ETHERNET_RWKUP_FILTER_COMMAND_MULTICAST - applies only to multicast
        packets
    */
    uint8_t filterCommand2;
    /**The filter commands for the filter 3 can be an OR of
        ETHERNET_RWKUP_FILTER_COMMAND_ENABLE - this must be set to enable filter
        ETHERNET_RWKUP_FILTER_COMMAND_AND_PREVIOUS - implements Boolean logic
        of combining with previous filter
        ETHERNET_RWKUP_FILTER_COMMAND_INVERSE - reverses logic of CRC function
        that rejects packets with matching CRC value
        ETHERNET_RWKUP_FILTER_COMMAND_MULTICAST - applies only to multicast
        packets
    */
    uint8_t filterCommand3;
    /** ORed value of any of the following Macros:
    ETHERNET_RWKUP_FILTER_CONFIG0_ENABLED - only if this is set Filter 0 is
    configured.
    ETHERNET_RWKUP_FILTER_CONFIG1_ENABLED - only if this is set Filter 1 is
    configured.
    ETHERNET_RWKUP_FILTER_CONFIG2_ENABLED - only if this is set Filter 2 is
    configured.
    ETHERNET_RWKUP_FILTER_CONFIG3_ENABLED - only if this is set Filter 3 is
    configured */
    uint8_t flags;
}Ethernet_RemoteWakeUp_Filter_Config;

#define ETHERNET_RWKUP_FILTER_CONFIG0_ENABLED 0x1U
#define ETHERNET_RWKUP_FILTER_CONFIG1_ENABLED 0x2U
#define ETHERNET_RWKUP_FILTER_CONFIG2_ENABLED 0x4U
#define ETHERNET_RWKUP_FILTER_CONFIG3_ENABLED 0x8U

#define ETHERNET_RWKUP_FILTER_COMMAND_ENABLE 0x1U
#define ETHERNET_RWKUP_FILTER_COMMAND_AND_PREVIOUS 0x2U
#define ETHERNET_RWKUP_FILTER_COMMAND_INVERSE   0x4U
#define ETHERNET_RWKUP_FILTER_COMMAND_MULTICAST 0x8U

#define ETHERNET_RWKUP_FILTER_NUM 0x4U
#define ETHERNET_RWKUP_FILTER_NUM_WORDS 0x8U
typedef enum
{
    ETHERNET_RX_FLOW_CONTROL_1KB,
    ETHERNET_RX_FLOW_CONTROL_1_5_KB, //For1.5 KB
    ETHERNET_RX_FLOW_CONTROL_2KB,
    ETHERNET_RX_FLOW_CONTROL_2_5KB,
    ETHERNET_RX_FLOW_CONTROL_3KB,
    ETHERNET_RX_FLOW_CONTROL_3_5KB,
    ETHERNET_RX_FLOW_CONTROL_4KB,
}Ethernet_ReceiveFlowControlLevel;

//*****************************************************************************
//
//! Ethernet_initInterface
//! Initialise the Ethernet Interface with this API.
//! This is the First API of the Low Level Driver
//! that should be called by application/Higher layer stack.
//! Turns on the Clocks to Ethernet interface.
//! The Module Initialization is done in Ethernet_getHandle API the user must
//! fill the Parameters for Init in the Struture returned by the API
//!
//! \param interfaceConfig Configuration Structure to be used for initializing
//! interface
//! \return Pointer to Init Config Structure
//!     to be used in Ethernet_getHandle() API
//
//*****************************************************************************

extern Ethernet_InitConfig *Ethernet_initInterface(
                            Ethernet_InitInterfaceConfig    interfaceConfig);

//*************************************************************************
//
// Ethernet_initRxChannel
//
//! Initializes the Rx DMA Channel and makes it ready for receive
//! \param
//! chInfo : Pointer to the Channel info Structure for the channel to be init
//! \return none
//
//************************************************************************

extern uint32_t Ethernet_initRxChannel(Ethernet_ChInfo *chInfo);

//**********************************************************************
//! Enables MAC for transmission and reception
//!
//! \param base Base Address of the Ethernet Module
//! \param flags ORed value of flags to be set
//!  (ETHERNET_MAC_CONFIGURATION_RE, ETHERNET_MAC_CONFIGURATION_TE)
//! \return None
//***********************************************************************
extern void Ethernet_setMACConfiguration(uint32_t base,
        uint32_t flags);

//**********************************************************************
//! Disables MAC for transmission and reception
//!
//! \param base Base Address of the Ethernet Module
//! \param flags ORed value of flags to be set
//!  (ETHERNET_MAC_CONFIGURATION_RE, ETHERNET_MAC_CONFIGURATION_TE)
//! \return None
//***********************************************************************
extern void Ethernet_clearMACConfiguration(uint32_t base,
                    uint32_t flags);

//*****************************************************************************
//
//! Ethernet_shutdownInterface
//! This API can be used for dynamically shutting down the
//! Ethernet interface. This shutsdown the DMA Receiver, Transmit
//! Engines and disables the MAC Reception and transmission.
//! For getting the interface to work the application should use
//! Ethernet_initInterface() and Ethernet_getHandle() APIs
//! to get the interface back to Normal operation.
//!
//! \param None
//! \return None
//
//*****************************************************************************

extern void Ethernet_shutdownInterface(void);

//*****************************************************************************
//
//! Ethernet_getInitConfig()
//! Builds a default Configuration of the Module
//! The Module Initialization is done in Ethernet_getHandle API the user must
//! fill the Parameters for Init using the Ethernet_InitConfig Struture.
//! This API helps to fill the contents of the Init Config Structure
//! The Ethernet_InitConfig structure variables are populated to a known
//! good values
//! Higher Layer/User can refer to this implementation for creating a different
//! Configuration
//! \param pConfig Ethernet_InitConfig structure pointer could be returned
//! Ethernet_InitInterface() API
//! \returns Nothing
//
//*****************************************************************************

extern void Ethernet_getInitConfig(Ethernet_InitConfig *pConfig);
//*****************************************************************************
//
//! Ethernet_getHandle must be called before using the interface
//! For Sending and Receiving the Packets over Ethernet
//! Must pass the filled Init Configuration Structure(that is returned by
//! _initInterface call
//! This initializes the Ethernet module as per the configuration
//! structure provided.
//! The Driver moves to initialized state
//! ready for Sending/Receiving the packets
//!
//! \param handleApplication - can be any application specific passed back
//! during callbacks
//! \param ethernetInitConfigPtr - Pointer to the Filled up InitConfig Structure
//!  that is provided in _initInterface call
//! \param ethernetHandlePtr - returns a handle
//!     (Pointer to Book Keeping Structure).
//! This must be provided in subsequent calls to SendPacket or other APIs
//! \return ETHERNET_RET_SUCCESS on Success
//!
//


//*****************************************************************************

extern uint32_t Ethernet_getHandle(Ethernet_Handle handleApplication,
        Ethernet_InitConfig *ethernetInitConfigPtr,
        Ethernet_Handle *ethernetHandlePtr);

//*****************************************************************************
//
//! Configure the Specified aspect of the Ethernet driver
//! \param hEMAC handle returned by Ethernet_getHandle API
//! \param setParam the parameter to be set can be any of the following values:
//!    - \b ETHERNET_SET_CONFIG_VLAN_TX_OUTER -
//!         for setting outer VLAN  TX Parameters
//!   in case of dual VLAN or single VLAN
//!    - \b ETHERNET_SET_CONFIG_VLAN_TX_INNER - for setting inner VLAN TX
//!         Parameters
//!.    in case of inner VLAN
//!    - \b ETHERNET_SET_CONFIG_VLAN_TX_DOUBLE_VLAN -
//!         configures both Inner and Outer VLAN
//!TX parameters
//!    - \b ETHERNET_SET_CONFIG_FILTER_VLAN_PERFECT -
//!         for configuring the VLAN Tag Perfect Filtering
//!    - \b ETHERNET_SET_CONFIG_FILTER_L3_L4 - for configuring L3,L4 Filters
//! \param buffPtr the pointer to the Parameter structure being set
//!    - if setParam is ETHERNET_SET_CONFIG_VLAN_TX_OUTER address of
//!         Ethernet_VlanConfig structure
//!    - if setParam is ETHERNET_SET_CONFIG_VLAN_TX_INNER address of
//!         Ethernet_VlanConfig structure
//!    - if setParam is ETHERNET_SET_CONFIG_VLAN_TX_DOUBLE_VLAN address of
//!         Ethernet_DoubleVLANConfig structure
//!    - if setParam is ETHERNET_SET_CONFIG_FILTER_VLAN_PERFECT address
//!         of Ethernet_VLAN_Perfect_FilterParams structure
//!    - if setParam is ETHERNET_SET_CONFIG_FILTER_L3_L4 address of
//!      Ethernet_L3_L4_FilterParams structure
//! \param size size of the buffer being passed in buffPtr
//!
//! \return ETHERNET_RET_SUCCESS in case of Success and
//!     other Error code in case of failure
//!
//*****************************************************************************

extern uint32_t Ethernet_setConfig(Ethernet_Handle hEMAC,
            Ethernet_SetConfigParam setParam,
            void *buffPtr,
            uint32_t size);

//*****************************************************************************
//
//! Configure PTP Currently not implemented
//!
//*****************************************************************************

extern uint32_t Ethernet_configurePTP(Ethernet_Handle hEMAC);

//*****************************************************************************
//
//! Ethernet_sendPacket
//! This API is to be used to Send Packet(s) over Ethernet
//! This does a non Blocking Send over the Ethernet Interface
//! The Master DMA inbuilt with the module is Programmed to pick up the
//! Provided buffers
//! and transfer to the Ethernet module TX FIFO.
//! The Completion of DMA results in a Per channel DMA completion interrupt,
//! for which there is a completion ISR
//! The ISR is used to signal the end of packet transmission.
//! The Buffers provided to the LLD over this API
//! can be reclaimed as part of the TX.
//! The Higher layer has to prepare Packet Descriptors for each Buffer
//! and chain them if needed
//! The Packet Boundaries can be specified in the flags using
//! the ETHERNET_PKT_FLAG_SOP and ETHERNET_PKT_FLAG_SOP flags.
//! If there is a single packet it must use
//! both the flags ORred in the packet flags.
//! On completion of Transmit of a Paket,
//! the Driver picks up the Submitted Packet from Queue
//! and returns the Packet Structure as an argument to the Callback function.
//! Interrupt callback handling
//! \param   hEMAC- Handle to the EMAC returned in _Open call
//! \param pktPtr - Pointer to the Packet Descriptor structure.
//! If Multiple packets are to be transmitted
//! multiple Descriptors can be chained
//! and single call to _SendPacket can be done
//! Even if a single packet is split into multiple buffers,
//!  multiple Descriptors to be chained
//! The First Descriptor should have SOP set and EOP should be set in the last
//! The number of fragments must be specified
//! \return  ETHERNET_RET_SUCCESS on Success  or Error Codes on Failture
//
//*****************************************************************************

extern uint32_t Ethernet_sendPacket(Ethernet_Handle hEMAC,
                                    Ethernet_Pkt_Desc *pktPtr);


//*****************************************************************************
//
//! Ethernet_getStatistics()
//! API To get the RMON Statistics
//! Combines all the RMON Statistics in a single call
//!
//! \param hEMAC - Handle Provided by _Open call
//! \param statisticsPtr- the Pointer to Statistics structure to be filled
//! \return ETHERNET_RET_SUCCESS on success
//!
//
//*****************************************************************************
extern uint32_t Ethernet_getStatistics(Ethernet_Handle hEMAC,
                                    Ethernet_Statistics *statisticsPtr);
//***************************************************************************
//
//! Ethernet_clearHandle
//! Not implemented Currently
//!
//**************************************************************************
extern void Ethernet_clearHandle(Ethernet_Handle *phEMAC);

//**************************************************************************
//! Ethernet_shutdownInterface()
//! Used to Shutdown the interface - To be implemented
//! No Arguments and Does not Return anything
//**************************************************************************
extern void Ethernet_shutdownInterface(void);

//**************************************************************************
//! Ethernet_clearStatistics()
//! Used to Clear the RMON Statistics - To be implemeted
//! \param ethernetHandlePtr - Handle provided in Ethernet_getHandle API call
//! \return none
//**************************************************************************

extern void Ethernet_clearStatistics(Ethernet_Handle *ethernetHandlePtr);

//*****************************************************************************
//
//! Configures the Queueing model for a given DMA Queue and assigns
//! static channel number for Static mapping of Queue to Channel number
//!
//! \param base is the base address of the controller.
//! \param Ethernet_RxDMAQueueMode configures whether it is Static or Dynamic
//! mapping of the Channels
//! ETHERNET_RX_DMA_QUEUE_STATIC - provides a static mapping of given queue
//! to channel specified in mappedChannel for the queue queueNum
//! ETHERNET_RX_DMA_QUEUE_DYNAMIC - provides a dynamic mapping based on the
//! filters like MAC/L3/L4/VLAN
//! \param queueNum specifies the queue number for which the parameter
//! is getting configured
//! \param mappedChannel is the channel number which is assigned in case
//! of static mapping in case of Dynamic mapping this parameter is ignored
//!
//! \return None.
//
//*****************************************************************************

extern void Ethernet_setDMARxQueueMode(uint32_t base,
            Ethernet_RxDMAQueueMode mode,
            Ethernet_QueueNum queueNum,
            Ethernet_ChannelNum mappedChannel);


//*********************************************************************
//! Ethernet_transmitISR()
//! Transmit Packet Completion Interrupt Service Routine
//! This low level driver currently uses the design where every transmit
//! packet will have the Interrupt on Completion Set
//! For each packet provided by the application for Transmit the driver
//! forms a Transmit Descriptor which is submitted into the Transmit Ring
//! of the Ethernet module
//! Each packet's Interrupt on Completion flag is Set in the Tx Descriptor
//! For each packet Completion interrupt the ISR sees which channel
//! has completion interrupt and handles the corresponding Tx Desc Queue
//! The Packet completion is signalled to the application by calling
//! the Callback function provided by the application
//! \return None
//************************************************************************

extern interrupt void Ethernet_transmitISR(void);


//************************************************************************
//! Ethernet_receiveISR()
//! Receive Packet Completion Interrupt Service Routine
//! for each buffer which is submitted to the Ethernet channel Rx Ring
//! the IOC flag in the Received descriptor is set which
//! results in an interrupt for each packet
//! The ISR pops the packet from Descriptor Queue DescQueue and
//! calls the Rx Callback function registered by the Hiher layer
//! calls Ethernet_removePacketsFromRxQueue to implement the same
//! \return None
//***********************************************************************
extern interrupt void Ethernet_receiveISR(void);

//************************************************************************
//! Ethernet_genericISR()
//! Generic Interrupt Service Routine
//! \return None
//***********************************************************************

extern interrupt void Ethernet_genericISR(void);
//
//Application specific Callback functions
//

//****************************************************************************
//!
//! This function is a callback function called by the Driver when it needs
//! a Packet for Receive Operation.
//!This can be replaced by the Higher layer stack
//! application while integrating this layer of driver
//!
//****************************************************************************


extern Ethernet_Pkt_Desc *Ethernet_getPacketBuffer(void);

//****************************************************************************
//!
//! This function is a callback function called by the Driver to handle the
//! Transmit Complete Callback that can be used to reclaim the buffer
//! Placeholder function that can be changed while initializing the Init
//! Structure
//!
//****************************************************************************

extern void Ethernet_releaseTxPacketBuffer(Ethernet_Handle handleApplication,
    Ethernet_Pkt_Desc *pPacket);

//*****************************************************************************
//!
//! This callback function is called by the application
//! when a Rx packet is available
//! Can be changed by the higher layer stack
//!
//*****************************************************************************
extern Ethernet_Pkt_Desc *Ethernet_receivePacketCallback(
        Ethernet_Handle handleApplication,
        Ethernet_Pkt_Desc *pPacket);


//*****************************************************************************
//
//! Configures the Ethernet MAC's IEEE 1588 timestamping options.
//!
//! \param base is the base address of the controller.
//! \param config contains flags selecting particular configuration
//! options.
//! \param subSecondInc is the number that the IEEE 1588 subsecond clock
//! should increment on each tick.
//!
//! This function is used to configure the operation of the Ethernet MAC's
//! internal timestamping clock.  This clock is used to timestamp incoming
//! and outgoing packets and as an accurate system time reference when
//! IEEE 1588 Precision Time Protocol is in use.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_setConfigTimestampPTP(uint32_t base, uint32_t config,
                                           float subSecondInc);

//*****************************************************************************
//
//! Returns the current IEEE 1588 timestamping configuration.
//!
//! \param base is the base address of the controller.
//! \param subSecondInc points to storage that is written with the
//! current subsecond increment value for the IEEE 1588 clock.
//!
//! This function may be used to retrieve the current MAC timestamping
//! configuration.
//!
//! \return current state of the \e ETHERNET_O_MAC_TIMESTAMP_CONTROL register.
//
//*****************************************************************************
extern uint32_t Ethernet_getConfigTimestampPTP(uint32_t base,
                                               float *subSecondInc);

//*****************************************************************************
//
//! Enables packet timestamping and starts the system clock running.
//!
//! \param base is the base address of the controller.
//!
//! This function is used to enable the system clock used to timestamp
//! Ethernet frames and to enable that timestamping.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_enableSysTimePTP(uint32_t base);

//*****************************************************************************
//
//! Disables packet timestamping and stops the system clock.
//!
//! \param base is the base address of the controller.
//!
//! This function is used to stop the system clock used to timestamp
//! Ethernet frames and to disable timestamping.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_disableSysTimePTP(uint32_t base);

//*****************************************************************************
//
//! Sets the current system time.
//!
//! \param base is the base address of the controller.
//! \param seconds is the seconds value of the new system clock setting.
//! \param subSeconds is the subseconds value of the new system clock
//! setting.
//!
//! This function may be used to set the current system time.  The system
//! clock is set to the value passed in the \e seconds and
//! \e subSeconds parameters.
//!
//! The meaning of \e subseconds depends on the current system time
//! configuration.  If Ethernet_setConfigTimestampPTP() was previously called
//! with the "DIGITAL ROLLOVER" configuration option, each bit in the
//! \e subSeconds value represents 1 ns. If "BINARY ROLLOVER" was
//! specified instead, a \e subSeconds bit represents 0.46 ns.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_setSysTimePTP(uint32_t base, uint32_t seconds,
                                   uint32_t subSeconds);

//*****************************************************************************
//
//! Gets the current system time.
//!
//! \param base is the base address of the controller.
//! \param seconds points to storage for the current seconds value.
//! \param subSeconds points to storage for the current subseconds value.
//!
//! This function may be used to get the current system time.
//!
//! The meaning of \e subseconds depends on the current system time
//! configuration.  If Ethernet_setConfigTimestampPTP() was previously called
//! with the "DIGITAL ROLLOVER" configuration option, each bit in the
//! \e subSeconds value represents 1 ns. If "BINARY ROLLOVER" was
//! specified instead, a \e subSeconds bit represents 0.46 ns.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_getSysTimePTP(uint32_t base, uint32_t *seconds,
                                   uint32_t *subSeconds);

//*****************************************************************************
//
//! Adjusts the current system time upwards or downwards by a given amount.
//!
//! \param base is the base address of the controller.
//! \param seconds is the seconds value of the time update to apply.
//! \param subSeconds is the subseconds value of the time update to apply.
//! \param addSub defines the direction of the update, whether to add or.
//!
//! This function may be used to adjust the current system time either upwards
//! or downwards by a given amount.  The size of the adjustment is given by
//! the \e seconds and \e subSeconds parameter and the direction
//! by the \e addSub parameter.  When \e addSub is \e true, the system time is
//! advanced by the interval given.  When it is \e false, the time is retarded
//! by the interval.
//!
//! The meaning of \e subseconds depends on the current system time
//! configuration.  If Ethernet_setConfigTimestampPTP() was previously called
//! with the "DIGITAL ROLLOVER" configuration option, each bit in the
//! \e subSeconds value represents 1 ns. If "BINARY ROLLOVER" was
//! specified instead, a \e subSeconds bit represents 0.46 ns.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_updateSysTimePTP(uint32_t base, uint32_t seconds,
                                      uint32_t subSeconds, bool addSub);

//*****************************************************************************
//
//! This API fetches the transmit timestamp of the PTP packet sent out on the
//! line which is captured when PTP Offload is enabled.
//!
//! \param base is the base address of the controller.
//! \param seconds is the seconds field of the captured transmit timestamp.
//! \param nanoSeconds is the nano-seconds field of the captured transmit
//! timestamp.
//!
//! When PTP Offload is enabled, the transmit timestamp of the packet is
//! captured and corresponding interrupt status bit is set. For example, if
//! the device is configured as slave, then transmit timestamp for outgoing
//! 'Delay Request' packet is captured.
//!
//! \return Transmit Timestamp Status Missed indicator.
//
//*****************************************************************************
extern uint32_t Ethernet_getOneStepTransmitTimestampPTP(uint32_t base,
                                                        uint32_t *seconds,
                                                        uint32_t *nanoSeconds);

//*****************************************************************************
//
//! Adjusts the system time update rate when using the fine correction method.
//!
//! \param base is the base address of the controller.
//! \param addend is the number to add to the accumulator register on
//! each tick of the Reference PTP Clock.
//!
//! This function is used to control the rate of update of the system time
//! when in fine update mode.  Fine correction mode is selected if
//! \e ETHERNET_MAC_TIMESTAMP_CONTROL_TSCFUPDT is supplied in the \e config
//! parameter passed to a previous call to Ethernet_setConfigTimestampPTP().
//! Fine update mode is typically used when synchronizing the local clock to
//! the IEEE 1588 master clock.  The subsecond counter is incremented by the
//! number passed to Ethernet_setConfigTimestampPTP() in the \e subSecondInc
//! parameter each time a 32-bit accumulator register generates a carry.
//! The accumulator register is incremented by the "addend" value on each main
//! oscillator tick, and this addend value is modified to allow fine control
//! over the rate of change of the timestamp counter.  The addend value is
//! calculated using the ratio of the main oscillator clock rate and the
//! desired IEEE 1588 clock rate and the \e subSecondInc value is set to
//! correspond to the desired IEEE 1588 clock rate.
//!
//! As an example, using digital rollover mode and a 100 MHz Reference PTP
//! clock with a desired IEEE 1588 clock accuracy of 50 MHz, and having made
//! a previous call to Ethernet_setConfigTimestampPTP() with \e subSecondInc
//! set to the 50 MHz clock period of 20 ns, the initial \e addend value
//! would be set to 0x80000000 to generate a carry on every second Reference
//! PTP clock tick. Because the system time updates each time the accumulator
//! overflows, small changes in the \e addend value can be used to very
//! finely control the system time rate.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_setAddend(uint32_t base, uint32_t addend);

//*****************************************************************************
//
//! Returns the number of Auxiliary Timestamp Snapshots available in the
//! Auxiliary Snapshot FIFO.
//!
//! \param base is the base address of the controller.
//!
//! A value equal to \e ETHERNET_MAC_AUX_TIMESTAMP_FIFO_DEPTH indicates that
//! the Auxiliary Snapshot FIFO is full.
//!
//! \return None.
//
//*****************************************************************************
extern uint32_t Ethernet_getDepthAuxSnapshotFIFO(uint32_t base);

//*****************************************************************************
//
//! Sets the software trigger for Auxiliary Timestamp.
//!
//! \param base is the base address of the controller.
//! \param trigSelect is the trigger input for which software trigger is
//! intended.
//!
//! This function can be used to trigger an auxiliary timestamp event initiated
//! by the software.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_setTimestampSWTrigger(uint32_t base, uint32_t trigSelect);

//*****************************************************************************
//
//! Configures the Auxiliary Timestamp Unit with intended Triggers.
//!
//! \param base is the base address of the controller.
//! \param trigSelect is the auxiliary snapshot input to be programmed.
//! \param trigValue
//!
//! This function configures the Auxiliary Timestamp unit to store a snapshot
//! of the system time based on an external event. The snapshots taken for
//! any input are stored in a common FIFO. \e Ethernet_getAuxSnapshotTrigId()
//! can be used to know the Input/Trigger Id is for which Timestamp is
//! available for reading at the top of this FIFO.
//! \e Ethernet_dequeueAuxSnapshotFIFO() can then be used to get the 64-bit
//! timestamp. FIFO is cleared by calling \e Ethernet_clearAuxSnapshotFIFO().
//! Auxiliary timestamp snapshots can be recorded based on triggers of system
//! events to track the sequence of events as well as measure latency/delay
//! between two events and so on. The feature can then be used effectively to
//! feed further control signaling choices, trace the sequence of events for
//! debug or analysis purposes. CPU subsystem & device level exceptions like
//! NMI, causes of NMI, Error pin status can be explicitly tracked with
//! timestamp to aid debug or to report any systemic errors.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_configAuxTimestampTrigger(uint32_t base,
                                               uint32_t trigSelect,
                                               uint32_t trigValue);

//*****************************************************************************
//
//! Clears/Resets the Auxiliary Timestamp Snapshot FIFO.
//!
//! \param base is the base address of the controller.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_clearAuxSnapshotFIFO(uint32_t base);

//*****************************************************************************
//
//! Disable the Auxiliary Timestamping for events.
//!
//! \param base is the base address of the controller.
//! \param trigInstance denotes the Auxiliary Snapshot Trigger Instance.
//!
//! This function can be used to disable the trigger instance for which
//! Auxiliary Timestamp Snapshots need not be captured.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_disableAuxSnapshot(uint32_t base, uint32_t trigInstance);

//*****************************************************************************
//
//! Enables the Auxiliary Timestamping for events.
//!
//! \param base is the base address of the controller.
//! \param trigInstance denotes the Auxiliary Snapshot Trigger Instance.
//!
//! This function can be used to enable the trigger instance for which
//! Auxiliary Timestamp Snapshots needs to be captured.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_enableAuxSnapshot(uint32_t base, uint32_t trigInstance);

//*****************************************************************************
//
//! Read the top of Auxiliary Timestamp Snapshot FIFO.
//!
//! \param base is the base address of the controller.
//! \param seconds denotes the Higher 32 bits of the 64-bit Auxiliary Timestamp
//! stored in the Auxiliary Timestamp Snapshot FIFO.
//! \param nanoSeconds denotes the Lower 32 bits of the 64-bit Auxiliary
//! Timestamp stored in the Auxiliary Timestamp Snapshot FIFO.
//!
//! This function can be used to read the content of a 64-bit wide Auxiliary
//! Timestamp Snapshot FIFO with a depth configured as
//! \e ETHERNET_MAC_AUX_TIMESTAMP_FIFO_DEPTH. The top of the FIFO is removed
//! only when the last byte of \e ETHERNET_O_MAC_AUXILIARY_TIMESTAMP_SECONDS
//! is read.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_dequeueAuxSnapshotFIFO(uint32_t base, uint32_t *seconds,
                                            uint32_t *nanoSeconds);

//*****************************************************************************
//
//! Get the Id of trigger instance for the top item of Auxiliary Snapshot FIFO.
//!
//! \param base is the base address of the controller.
//! \param id is pointer to the value of trigger instance identifier.
//!
//! This function can be used to identify the Auxiliary trigger inputs for
//! which the timestamp is available in the Auxiliary Snapshot FIFO.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_getAuxSnapshotTrigId(uint32_t base, uint32_t *id);

//*****************************************************************************
//!
//! Sets the action to be triggered when the target system time is reached.
//!
//! \param base is the base address of the controller.
//! \param target is the intended action upon reaching target time.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_selectTargetInterruptOrPulsePPS(uint32_t base,
                                                     uint32_t ppsNum,
                                                     uint32_t target);
//*****************************************************************************
//!
//! Sets the PPS output in fixed pulse mode.
//!
//! \param base is the base address of the controller.
//! \param freq is the frequency of the output generated on the PPS pin.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setFixedModePPS(uint32_t base, uint32_t freq);

//*****************************************************************************
//!
//! Sets the PPS output in flexible/command mode.
//!
//! \param base is the base address of the controller.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setFlexibleModePPS(uint32_t base);


//*****************************************************************************
//!
//! Sets the target and mode of PPS in one API.
//! Internally calls Ethernet_setTargetPPS(), Ethernet_setFixedModePPS() and
//! Ethernet_setFlexibleModePPS() to configure the PPS in one shot.
//!
//! \param base is the base address of the controller.
//! \param target is the intended action upon reaching target time.
//! \param mode is the PPS output mode.
//! \param fixedFreq is the frequency of the output generated on the PPS pin.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_configurePPS(uint32_t base, uint32_t target, uint32_t mode,
                      uint32_t fixedFreq);

//*****************************************************************************
//
//! Sets the target system time at which the next PPS interrupt/pulse is
//! generated.
//!
//! \param base is the base address of the controller.
//! \param ppsNum is the instance of the PPS.
//! \param seconds is the second value of the desired target time.
//! \param subSeconds is the subseconds value of the desired target time.
//!
//! This function may be used to schedule an interrupt/PPS at some future time.
//! The time reference for the function is the IEEE 1588 time as returned by
//! Ethernet_getSysTimePTP(). To generate an interrupt when the system
//! time exceeds a given value, call this function to set the desired time,
//! then Ethernet_selectTargetInterruptOrPulsePPS() to enable the interrupt.
//! When the system time increments past the target time, an Ethernet interrupt
//! is generated.
//!
//! The accuracy of the interrupt timing depends on the Ethernet timer
//! update frequency and the subsecond increment value currently in use.  The
//! interrupt is generated on the first timer increment that causes the
//! system time to be greater than or equal to the target time set.
//!
//! \return None.
//
//*****************************************************************************
extern void Ethernet_setTargetTimePPS(uint32_t base, uint32_t ppsNum,
                                      uint32_t seconds, uint32_t subSeconds);

//*****************************************************************************
//!
//! Sets the interval and width of the pulse that is to be generated in
//! flexible/command PPS mode.
//!
//! \param base is the base address of the controller.
//! \param ppsNum is the instance of the PPS.
//! \param width is the pulse width.
//! \param interval is the pulse interval.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setPeriodPPS(uint32_t base, uint32_t ppsNum,
                                  uint32_t width, uint32_t interval);

//*****************************************************************************
//!
//! Programs the command to control the pulse/train start/stop behaviour
//! when PPS flexible/command mode is set.
//!
//! \param base is the base address of the controller.
//! \param ppsNum is the instance of the PPS.
//! \param ppsCmd is the command to be programmed.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setCmdPPS(uint32_t base, uint32_t ppsNum,
                               uint32_t ppsCmd);

//*****************************************************************************
//!
//! Programs the PTP Offload Configuration into the PTO_Control Register.
//!
//! \param base is the base address of the controller.
//! \param config is the 32 bit register value to be programmed.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_writeConfigPTPOffload(uint32_t base, uint32_t config);

//*****************************************************************************
//!
//! Returns the raw PTP Offload Configuration from the PTO_Control Register.
//!
//! \param base is the base address of the controller.
//!
//! \return 32 bit PTO_Control Register dump.
//!
//*****************************************************************************
extern uint32_t Ethernet_readConfigPTPOffload(uint32_t base);

//*****************************************************************************
//!
//! Programs the Log Message Interval register with the configuration needed
//! for sending automatic messages when PTP Offloading is enabled.
//!
//! \param base is the base address of the controller.
//! \param config is the 32 bit register value to be programmed.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_writeLogMsgIntervalPTPOffload(uint32_t base,
                                            uint32_t config);

//*****************************************************************************
//!
//! Returns the raw Log Message Interval register value.
//!
//! \param base is the base address of the controller.
//!
//! \return 32 bit Log Message Interval Register dump.
//!
//*****************************************************************************
extern uint32_t Ethernet_readLogMsgIntervalPTPOffload(uint32_t base);

//*****************************************************************************
//!
//! Sets the bit that will trigger one-time sending of PTP Peer Delay Request
//! message by the hardware when PTP Offloading is enabled. Before PTP Offload
//! engine can send this message, it expects that the PTP header related
//! information should have been already programmed by the application.
//!
//! \param base is the base address of the controller.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setPDelayReqMsgTriggerPTPOffload(uint32_t base);

//*****************************************************************************
//!
//! Sets the bit that will trigger one-time sending of PTP SYNC
//! message by the hardware when PTP Offloading is enabled. Before PTP Offload
//! engine can send this message, it expects that the PTP header related
//! information to be already programmed by the application.
//!
//! \param base is the base address of the controller.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setSyncMsgTriggerPTPOffload(uint32_t base);

//*****************************************************************************
//!
//! To enable or disable the PTP Offload engine. Once enabled, it arms the
//! hardware to automatically send or respond to PTP messages on the line.
//! Before this feature can be used, the engine expects that the PTP header
//! related information to be already programmed by the application.
//!
//! \param base is the base address of the controller.
//! \param enableDisable is the on/off switch value that is to be programmed.
//!
//! \return None.
//!
//*****************************************************************************
extern void
Ethernet_enableDisablePTPOffload(uint32_t base,
                                 Ethernet_PTPOffloadEnableMode enableDisable);

//*****************************************************************************
//!
//! To switch on/off multiple automatic PTP send/response messages for master
//! or slave mode.
//! Ordinary/Boundary clock: In Master mode, hardware can generate Sync or
//! Delay Response messages. Similarly, when configured in slave mode, the
//! hardware can generate automatic responses to Delay Request messages.
//! Transparent clock: Whether the hardware is configured in master or slave
//! mode, it can generate the Peer Delay Request messages or respond with
//! Peer Delay Response messages.
//!
//! \param base is the base address of the controller.
//! \param ptoModeType type of the message for which the switch setting needs
//!         to be programmed. This can be any of the following automatic types:
//!         1. Delay Request/ Delay Response message generation.
//!         2. Sync message generation.
//!         3. Peer Delay Request message generation.
//!         4. Peer Delay Response message generation.
//! \param ptoModeConf is the on/off switch value corresponding to ptoModeType.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setMsgSwitchesPTPOffload(uint32_t base,
                                    Ethernet_PTPOffloadModeType ptoModeType,
                                    void *ptoModeConf);

//*****************************************************************************
//!
//! This API configures the Domain Number in the hardware. This is a part of
//! standard PTP Header and the hardware uses this pre-configured value
//! while sending automatic PTP messages.
//!
//! \param base is the base address of the controller.
//! \param domainNumber is the 8-bit value to be programmed in the controller.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setDomainNumberPTPOffload(uint32_t base,
                                                uint8_t domainNumber);

//*****************************************************************************
//!
//! This API configures the Source Port Id in the hardware. This is a part of
//! standard PTP Header and the hardware uses this pre-configured value
//! while sending automatic PTP messages. This is a 10-octet value.
//!
//! \param base is the base address of the controller.
//! \param spi0 is octet 1 to octet 4 of the Source Port Id.
//! \param spi1 is octet 5 to octet 8 of the Source Port Id.
//! \param spi2 is octet 9 and octet 10 of the Source Port Id.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setSourcePortIdPTPOffload(uint32_t base,
                                               uint32_t spi0,
                                               uint32_t spi1,
                                               uint32_t spi2);

//*****************************************************************************
//!
//! This API configures the periodicity of the automatically generated SYNC
//! message when the PTP node is Master. Allowed values are -15 to 15.
//! For a given value of the log sync interval (n), the time interval between
//! consective Sync packets is given by:
//!             2^(30+n) nanoSec, when -15 <= n <= -1
//!             2^n sec, when 0 <= n <= 15
//!
//! \param base is the base address of the controller.
//! \param value is actual value of periodicity to be configured.
//!         Allowed values are -15 to 15. Negative value must be represented
//!         in 2's-complement form. For example, if the required value is -1,
//!         the value programmed must be 0xFF.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setLogSyncIntervalPTPOffload(uint32_t base, uint8_t value);

//*****************************************************************************
//!
//! This API configures the frequency of the automatically generated Delay
//! Request messages. Delay Request messages are generated by the slave node.
//! The master sends this information (logMinDelayReqInterval) in the DelayResp
//! PTP messages to the slave. The Receiver(slave) processes this value
//! from the received DelayResp messages and updates this field accordingly.
//! In the Slave mode, the host must not write/update this register unless it
//! has to override the received value.

//! \param base is the base address of the controller.
//! \param value is the 8-bit frequency value of DelayReq messages to be
//!         configured. It can be one of the following:
//!         0: DelayReq generated for every received SYNC
//!         1: DelayReq generated every alternate reception of SYNC
//!         2: for every 4 SYNC messages
//!         3: for every 8 SYNC messages
//!         4: for every 16 SYNC messages
//!         5: for every 32 SYNC messages
//!         6-7: Reserved
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setDelaySyncRatioPTPOffload(uint32_t base, uint8_t value);

//*****************************************************************************
//!
//! This API configures the periodicity of the automatically generated Peer
//! Delay Request message when the node is configured as transparent clock.
//! Allowed values are -15 to 15.
//!
//! \param base is the base address of the controller.
//! \param value is actual value of periodicity to be configured.
//!         Allowed values are -15 to 15. Negative value must be represented
//!         in 2's-complement form. For example, if the required value is -1,
//!         the value programmed must be 0xFF.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setLogMinPDelayReqIntervalPTPOffload(uint32_t base,
                                    uint8_t value);

//*****************************************************************************
//!
//! This is a wrapper API that allows configuring the PTP Offload engine in
//! the hardware. This includes the PTP header related information such as
//! Domain Number, Source Port Id, LogSyncInterval, Delay Sync Ratio,
//! LogMinPDelayInterval. It also configures various automatic PTP message
//! switches such as Sync, Delay Request, Delay Response, Peer Delay Request.
//!
//! \param base is the base address of the controller.
//! \param ptoConfigParams is the structure that holds PTP Offload related
//!         settings like source port id, domain number, log message interval,
//!         automatic PTP message switches.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setConfigPTPOffload(uint32_t base,
                            Ethernet_PTPOffloadConfigParams ptoConfigParams);

//*****************************************************************************
//!
//! This API enables One-step timestamping feature for PTP packets over UDP.
//! PTP requires the timestamp to be captured while the packet (SFD of the
//! packet) is on the line and one step timestamp requires the origin timestamp
//! and/or correction field to be updated in the PTP header while the packet is
//! being transmitted on the line. Because the PTP message is present in the
//! UDP payload, it is not possible to update the checksum field in the UDP
//! header for modifications made to the PTP message, because it is already
//! transmitted by then.
//! Hence the hardware appends two bytes to the UDP payload and modifies those
//! two bytes in order to keep the already transmitted UDP checksum same.
//!
//! \param base is the base address of the controller.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_enableUDPChecksumUpdatePTP(uint32_t base);

//*****************************************************************************
//!
//! This API enables the correction for latency and synchronization in the
//! timestamp captured in the Receive side at the internal snapshot point. It
//! is achieved by configuring the correction value (Ingress Correction Value)
//! in the hardware. This value is always negative.
//! According to the IEEE 1588 specification, a timestamp must be captured when
//! the message timestamp point (leading edge of the first bit of the octet
//! immediately following the Start Frame Delimiter octet) crosses the boundary
//! between the node and the network.Because the reference timing source (the
//! PTP clock clk_ptp_ref_i) is different from the MAC Tx or Rx clock, the
//! captured timestamp must be corrected for latency issues because of
//! synchronization. In addition, latency issues between the internal snapshot
//! point and the recommended capture point (the boundary between the node and
//! the network), must also be corrected.
//!
//! \param base is the base address of the controller.
//! \param nanoSeconds is the Ingress Correction value to be programmed.
//!         For Binary Rollover, accuracy is 1 ns. For Digital Rollover,
//!         accuracy is ~0.466ns.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setIngressCorrectionPTP(uint32_t base,
                                             int32_t nanoSeconds);

//*****************************************************************************
//!
//! This API enables the correction for latency and synchronization in the
//! timestamp captured in the Transmit side at the internal snapshot point. It
//! is achieved by configuring the correction value (Egress Correction Value)
//! in the hardware.
//! According to the IEEE 1588 specification, a timestamp must be captured when
//! the message timestamp point (leading edge of the first bit of the octet
//! immediately following the Start Frame Delimiter octet) crosses the boundary
//! between the node and the network. Because the reference timing source (the
//! PTP clock clk_ptp_ref_i) is different from the MAC Tx or Rx clock, the
//! captured timestamp must be corrected for latency issues because of
//! synchronization. In addition, latency issues between the internal snapshot
//! point and the recommended capture point (the boundary between the node and
//! the network), must also be corrected.
//!
//! \param base is the base address of the controller.
//! \param nanoSeconds is the Egress Correction value to be programmed.
//!         For Binary Rollover, accuracy is 1 ns. For Digital Rollover,
//!         accuracy is ~0.466ns.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setEgressCorrectionPTP(uint32_t base,
                                            int32_t nanoSeconds);

//*****************************************************************************
//!
//! This API fetches the 80-bit timestamp from the hardware. IEEE 1588-2008
//! defines a reference time in 64-bit format whereas IEEE 1588-2002 defines
//! an 80-bit format. Further the PTP subsystem provides two input sources:
//! 1. External Timestamp Input (Only 64 bit)
//! 2. Internal Timestamp Input (80 bit)
//!     The timestamp maintained in the hardware is 64-bit wide. The overflow
//!     to upper 16-bits of seconds register happens once in 130 years. The
//!     values of the upper 16-bits of the seconds field are exposed through
//!     this API.
//!
//! \param base is the base address of the controller.
//! \param higherWord is the upper 16-bits of seconds value.
//! \param seconds is the lower 32-bits of seconds value.
//! \param subSeconds is the 32-bit subSecond(nanoseconds) value.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_getSysTimeWithHigherWordPTP(uint32_t base,
                                                 uint32_t *higherWord,
                                                 uint32_t *seconds,
                                                 uint32_t *subSeconds);

//*****************************************************************************
//!
//! This API programs the Egress correction with sub-nanoseconds accuracy.
//! The fractional part of the egress correction value represents the
//! sub-nanoseconds value that needs to be programmed. The integer part
//! represents the nanoseconds value.
//!
//! \param base is the base address of the controller.
//! \param nanoSeconds is the floating point nanosecond value from which the
//!         fractional part is extrapolated by multiplying with 2^8 and
//!         programmed in the hardware.
//!
//! \return None.
//!
//*****************************************************************************
extern void Ethernet_setSubNanosecEgressCorrectionPTP(uint32_t base,
                                               float nanoSeconds);

//*****************************************************************************
//!
//! This API programs the Ingress correction with sub-nanoseconds accuracy.
//! The fractional part of the Ingress correction value represents the
//! sub-nanoseconds value that needs to be programmed. The integer part
//! represents the nanoseconds value.
//!
//! \param base is the base address of the controller.
//! \param nanoSeconds is the floating point nanosecond value from which the
//!         fractional part is extrapolated by multiplying with 2^8 and
//!         programmed in the hardware.
//!
//! \return None.
//*****************************************************************************
extern void Ethernet_setSubNanosecIngressCorrectionPTP(uint32_t base,
                                               float nanoSeconds);

//*****************************************************************************
//!
//! This API programs the Asymmetric Egress correction value in nanosecs
//! which is subtracted from the correction field of the PTP packet being
//! transmitted on the line.
//!
//! \param base is the base address of the controller.
//! \param nanoSeconds is the floating point nanosecond value which is to be
//!        subtracted from the correction field of the outgoing PTP packet.
//!
//! \return None.
//*****************************************************************************
extern void Ethernet_setAsymEgressCorrectionPTP(uint32_t base,
                                                float nanoSeconds);

//*****************************************************************************
//!
//! This API programs the Asymmetric Ingress correction value in nanosecs
//! which is added to the correction field of the PTP packet being received
//! on the line.
//!
//! \param base is the base address of the controller.
//! \param nanoSeconds is the floating point nanosecond value which is to be
//!        added to the correction field of the incoming PTP packet.
//!
//! \return None.
//*****************************************************************************
extern void Ethernet_setAsymIngressCorrectionPTP(uint32_t base,
                                                 float nanoSeconds);

//*************************************************************************
//! Ethernet_isTimestampIntActive()
//!
//! This API checks whether the source of an interrupt (generic) is
//! timestamp based. A Timestamp interrupt may arise due to following
//! reasons:
//! 1. Transmit timestamp is captured for a packet when PTP Offload mode is
//!    enabled.
//! 2. The system time value is equal to or exceeds the value specified in
//!    the Target Time High and Low registers.
//! 3. There is an overflow in the Seconds register.
//! 4. Target Time Error occurred, that is, programmed target time already
//!    elapsed.
//! 5. Auxiliary snapshot trigger is asserted when Auxiliary Snapshot
//!    feature is enabled.
//!
//! \param none
//!
//! \return \e true if the Timestamp Interrupt Status bit is set.
//!         \e false if the Timestamp Interrupt Status bit is reset.
//
//************************************************************************
extern bool Ethernet_isTimestampIntActive(void);

//*************************************************************************
//! Ethernet_isTransmitTimestampStatusSet()
//!
//! This API checks whether the source of the timestamp interrupt is
//! "Transmit timestamp is captured for a packet when PTP Offload mode is
//!  enabled."
//! If it is set, the application shall use the \e
//! Ethernet_getOneStepTransmitTimestampPTP() API to read the captured
//! timestamp for the transmitted packet.
//! Note that this Transmit Timestamp Status will be reset only if the
//! captured timestamp is read by calling above API.
//!
//! \param none
//!
//! \return \e true if the Transmit Timestamp Status bit is set.
//!         \e false if the Transmit Timestamp Status bit is reset.
//
//************************************************************************
extern bool Ethernet_isTransmitTimestampStatusSet(void);

//
//MDIO Functions
//
//***************************************************************************
//
//! Configures the Parameters of MDIO/Station Management Interface
//!
//! The MDIO interface is used to access the external PHY
//! \param base - Base Address of the Ethernet Module
//! \param clockHigh
//!    - \b 0 - for Lower frequency ranges between 1Mhz to 2.5 Mhz range
//!    - \b 1- for higher frequency ranges
//! as programmed in clockRange parameter
//!
//! \param clockRange- following are the allowed values
//!    - \b 0-5 with clockHigh 0 configures between 1 Mhz to 2.5 Mhz Range
//!    - \b  0-7 with clockHigh 1 For higher Frequency ranges,
//!         refer TRM other values are reserved
//! \param clause45Enable
//!    - \b 0 -Operates Clause22 Mode
//!    - \b 1 - Operates in Clause45 Mode
//! \return None
//
//***************************************************************************
extern void Ethernet_configureMDIO(uint32_t base,
                            uint32_t clockHigh,
                            uint32_t clockRange,
                            uint32_t clause45Enable
                            );

//************************************************************************
//! Configures the Address of PHY which is addressed by this MAC
//! For RevMII Interface mode, this API configures the address of
//! RevMII module as to be programmed from the other MAC
//! \param base Base Address of the Ethernet Module
//! \param phyAddr Address of the PHY
//!         0-31 are valid addresses. Other values are reserved
//! \return None
//***********************************************************************
extern void Ethernet_configurePHYAddress(uint32_t base,
                                  uint8_t phyAddr);
extern uint8_t Ethernet_getPHYMode(uint32_t base);

extern uint16_t Ethernet_readPHYRegister(uint32_t base,
                                 uint16_t regAddress);
extern void Ethernet_writePHYRegister(uint32_t base,
                               uint8_t regAddress,
                               uint16_t writeData);

//*************************************************************************
//
// Ethernet_setMACAddr
//
//! \param
//! base: Base Address of Ethernet module
//! instanceNum : 0-3 , the instance of MAC address register to be programmed
//! MacAddr High : Higher two bytes of MAC address in the lower two bytes
//! Higher 16 bits are ignored
//! MacAddrLow : Lower 4 bytes of the MAC address
//! channelNum DMA Channel number to which this is mapped
//! Function to program the MAC Address
//! \return  none
//
//************************************************************************
void Ethernet_setMACAddr(uint32_t base, uint8_t instanceNum,
        uint32_t MACAddrHigh, uint32_t MACAddrLow,
        Ethernet_ChannelNum channelNum);

//**********************************************************************
//! Gives the MAC address of the instance passed
//!
//! \param base Base Address of the Ethernet Module
//! \param instanceNum instance number of MAC address
//!         0-3 are valid instance numbers
//! \param MACAddrHigh Higher two bytes of MAC address
//!         in the lower nibble
//! \param MACAddrLow Lower word of MAC address bytes
//! \return None
//***********************************************************************
extern void Ethernet_getMACAddr(uint32_t base,
                                   uint8_t instanceNum,
                                   uint32_t *macAddrHigh,
                                   uint32_t *macAddrLow);
//**********************************************************************
//! Clears the Interrupt flags of the specific DMA Channel number
//!
//! \param base Base Address of the Ethernet Module
//! \param ChannelNum Channel number of DMA
//!         0,1 are valid Channel Numbers
//! \param flags ORed value of flags to be cleared
//!         the set flags will be cleared in the DMA Channel
//! \return None
//***********************************************************************
extern void Ethernet_clearDMAChannelInterrupt(uint32_t base,
                                              uint32_t channelNum,
                                              uint32_t flags);

//***************************************************************************
//! This function helps to enable specified flags in
//! DMA_CH0_INTERRUPT_ENABLE register of the Ethernet Module
//!
//! \param baseAddress Base Address of the Ethernet modules
//! \param channelNum Channel number which has to be programmed 0 or 1
//! \param flags ORed Flags of the Register to be enabled
//! \return none
//**************************************************************************
extern void Ethernet_enableDmaInterrupt(uint32_t baseAddress,
                                 uint32_t channelNum,
                                 uint32_t flags);

//***************************************************************************
//! This function helps to disable specified flags in
//! DMA_CHn_INTERRUPT_ENABLE register of the Ethernet Module
//!
//! \param baseAddress Base Address of the Ethernet modules
//! \param channelNum Channel number which has to be programmed 0 or 1
//! \param flags ORed Flags of the Register to be enabled. Example:
//! ETHERNET_DMA_CH0_INTERRUPT_ENABLE_TBUE,
//! ETHERNET_DMA_CH0_INTERRUPT_ENABLE_NIE,
//! ETHERNET_DMA_CH0_INTERRUPT_ENABLE_RBUE.
//! \return none
//**************************************************************************
extern void Ethernet_disableDmaInterrupt(uint32_t baseAddress,
                                 uint32_t channelNum,
                                 uint32_t flags);

//***************************************************************************
//! This function helps to enable specified flags in
//! MTL_Qn_INTERRUPT_CONTROL_STATUS register of the Ethernet Module
//!
//! \param baseAddress Base Address of the Ethernet modules
//! \param queueNum Queue number which has to be programmed 0 or 1
//! \param flags ORed Flags of the Register to be enabled. Example:
//! ETHERNET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOIE,
//! ETHERNET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUIE,
//! ETHERNET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS.
//! \return none
//**************************************************************************
extern void Ethernet_enableMTLInterrupt(uint32_t baseAddress,
                                 uint32_t queueNum,
                                 uint32_t flags);

//***************************************************************************
//! This function disables the DMA from receiving anymore packets from fifo
//!
//! \param baseAddress Base Address of the Ethernet modules
//! \param channelNum Channel number which has to be programmed 0 or 1
//! \return none
//**************************************************************************
extern void Ethernet_disableRxDMAReception(uint32_t base,
                uint8_t channelNum);

//***************************************************************************
//! This function enables the DMA for receiving packets from fifo
//!
//! \param baseAddress Base Address of the Ethernet modules
//! \param channelNum Channel number which has to be programmed 0 or 1
//! \return none
//**************************************************************************
extern void Ethernet_enableRxDMAReception(uint32_t base,
                uint8_t channelNum);

//*************************************************************************
//! This function sets the Transmit Descriptor Tail Pointer of the Transmit
//! DMA Ring. Configures the End of Tx Descriptor Ring
//! \param baseAddress Base Address of Ethernet module
//! \param channelNum the channel number of the register to be configured
//!                   0,1 are valid Channel numbers
//! \param write_data pointer to the Descriptor
//!              32 bit pointer to the hardware descriptor structure
//! \return none
//*************************************************************************
extern void Ethernet_writeTxDescTailPointer(uint32_t baseAddress,
        uint32_t channelNum, Ethernet_HW_descriptor *write_data);
//**********************************************************************
//! This sets the Transmit Start Bit in DMA Channel Tx Control
//! Register
//! \param base Base Address of the Ethernet Module
//! \param channelNum instance number of DMA channel
//!         0,1 are valid Channel Numbers
//! \return None
//**********************************************************

void Ethernet_setDMAChannelTransmitStart(uint32_t base, uint32_t channelNum);
//**********************************************************************
//! This returns the Count of the Fragments which have been DMAed
//! in the packet which is currently being written by DMA from line
//! This is typically used in Early Receive Interrupt (Generic Interrupt)
//! handling to identify how many chunks(programmed Buffer size)
//! has been received during Threshold mode/Early Receive interrupt handling.
//! This shall be reset if the Receive Completion interrupt has been
//! asserted for the current packet
//!
//! \param base Base Address of the Ethernet Module
//! \param channelNum instance number of DMA channel
//!         0,1 are valid Channel Numbers
//! \return 16 bit value of number of chunks received in current packet
//***********************************************************************
extern uint16_t Ethernet_getRxERICount(uint32_t base, uint32_t channelNum);

//***********************************************************************
//! Ethernet_addPacketsIntoRxQueue
//!
//! \param:
//! channelDescPtr - Pointer to Channel Descriptor Structure
//! to which the Receive buffer has to be enqueued
//! This function calls the higher layer callback function to get the buffers
//! for receive from application and queues them up in Desc Queue
//! For the Receive channels the Wait queue is not used only the Desc Queue
//! is used by the driver
//! \return none
//***********************************************************************
extern void Ethernet_addPacketsIntoRxQueue(Ethernet_DescCh *channelDescPtr);

//**********************************************************************
//! Ethernet_removePacketsFromRxQueue()
//!
//! \param
//! channelDescPtr - Receive channel Desctiptor Pointer from which the
//! Packet has to be Defines
//! completionMode
//!
//! This function is called from the Receive Completion Interrupt Handler
//! This fills the PacketDescriptor Structure for handing over the packet
//! And fills with the received packet details
//! Calls the Receive Packet Callback function provided by higher layer
//! \return None
//**********************************************************************
extern void Ethernet_removePacketsFromRxQueue(Ethernet_DescCh *channelDescPtr,
                            Ethernet_CompletionMode completionMode);

//*************************************************************************
//
// Ethernet_writeRxDescTailPointer
//
//! \param
//! baseAddress: Base Address of Ethernet module
//! channelNum : 0 or 1, the channel number of the register to be configured
//! write_data : pointer to the Descriptor
//! Function to write to DMA_CHx_RXDESC_TAIL_POINTER register
//! This configures the beginning of Rx Descriptor Ring
//! \return none
//
//*************************************************************************
extern void Ethernet_writeRxDescTailPointer(uint32_t baseAddress,
        uint32_t channelNum, Ethernet_HW_descriptor *write_data);

//**********************************************************************
//! Enables the Flow Control in the Transmit Path for the given
//! queue number
//!
//! \param base Base Address of the Ethernet Module
//! \param queueNum instance number of MAC address
//!         0,1 are valid queue Numbers
//! \return None
//***********************************************************************
static inline void Ethernet_enableTransmitFlowControl(uint32_t base,
                                uint8_t queueNum)
{
    //
    //Set the Transmit Flow Control Enable bit
    //This is applicable to both Full duplex and
    //Half duplex modes
    //Subsequent Queue registers are offset by 0x4 in
    //the register memory map
    //
    HWREG(base + ETHERNET_O_MAC_Q0_TX_FLOW_CTRL + (queueNum*4U)) |=
            ETHERNET_MAC_Q0_TX_FLOW_CTRL_TFE;
}
//**********************************************************************
//! Disables the Flow Control in the Transmit Path for the given
//! queue number
//!
//! \param base Base Address of the Ethernet Module
//! \param queueNum instance number of MAC address
//!         0,1 are valid queue Numbers
//! \return None
//***********************************************************************
static inline void Ethernet_disableTransmitFlowControl(uint32_t base,
                                uint8_t queueNum)
{
    //
    //Clear the Transmit Flow Control Enable bit
    //This is applicable to both Full duplex and
    //Half duplex modes
    //Subsequent Queue registers are offset by 0x4 in
    //the register memory map
    //
    HWREG(base + ETHERNET_O_MAC_Q0_TX_FLOW_CTRL + (queueNum*4U)) &=
            ~ETHERNET_MAC_Q0_TX_FLOW_CTRL_TFE;
}

//**********************************************************************
//! Programs the Pause Time in the Transmit Path for the given
//! queue number. This shall be used when sending Pause Packets
//! in full duplex mode for Flow control. The MAC Address 0 shall
//! be used as the source address
//!
//! \param base Base Address of the Ethernet Module
//! \param queueNum instance number of MAC address
//!         0,1 are valid queue Numbers
//! \param pauseTime 16 bit Pause Time to be used in the Pause packets
//!
//! \return None
//***********************************************************************

static inline void Ethernet_setTransmitPauseTime(uint32_t base,
                            uint8_t queueNum,
                            uint16_t pauseTime)
{
    HWREG(base + ETHERNET_O_MAC_Q0_TX_FLOW_CTRL + (queueNum * 4U)) &=
            ~ETHERNET_MAC_Q0_TX_FLOW_CTRL_PT_M;
    HWREG(base + ETHERNET_O_MAC_Q0_TX_FLOW_CTRL + (queueNum * 4U)) |=
            pauseTime << ETHERNET_MAC_Q0_TX_FLOW_CTRL_PT_S;
}
//**********************************************************************
//! Triggers the Flow Control in the Transmit Path for the given
//! queue number. In full duplex mode this results in Pause Frame
//! sent on the line and in half duplex mode the Back pressure
//! is activated. This API should not be called when the Flow control
//! is already in progress. Use Ethernet_getTransmitFlowControlStatus()
//! to get the status and call this if Flow control is not active
//!
//! \param base Base Address of the Ethernet Module
//! \param queueNum instance number of MAC address
//!         0,1 are valid queue Numbers
//! \return None
//***********************************************************************
static inline void Ethernet_triggerTransmitFlowControl(uint32_t base,
                                uint8_t queueNum)
{
    //
    //This triggers transmit of Pause frames in full duplex mode
    //or activation of back presssure in half duplex mode
    //
    HWREG(base + ETHERNET_O_MAC_Q0_TX_FLOW_CTRL + (queueNum * 4U)) |=
        ETHERNET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA;
}
//**********************************************************************
//! Gives the Transmit Flow control Status of the given Queue
//! This API can be used before calling Ethernet_triggerTransmitFlowControl()
//!
//! \param base Base Address of the Ethernet Module
//! \param queueNum instance number of MAC address
//!         0,1 are valid queue Numbers
//! \return 0 if Flow Control is not active
//!         1 if Flow Control is active
//***********************************************************************
static inline uint8_t Ethernet_getTransmitFlowControlStatus(uint32_t base,
                                    uint8_t queueNum)
{
    return(HWREG(base + ETHERNET_O_MAC_Q0_TX_FLOW_CTRL + (queueNum * 4U)) &
                ETHERNET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA);
}
//**********************************************************************
//! This API enables the Hardware Flow Control Mechanism in the receive Path
//! When a Pause Packet is received in Full duplex mode,the flow control
//! mechanism is triggered in Transmit path. For Half Duplex mode
//! the pause packets are only detected as control Packets.
//! It may be practically efficient to use this feature if the Receive Queue
//! size is 4K bytes.
//! By default only Pause Packets with special MAC address 0180C2000001
//! If unicast Pause Packets are to be handled then use
//! Ethernet_enableUnicastPauseFrameDetect() API to enable Unicast Pause.
//! Suggested use after calling Ethernet_enableMACReceiveFlowControl()
//! after enabling Receive Flow Control at MAC level.and configuring the
//! thresholds using Ethernet_configureReceiveFlowcontrol() API.
//! To disable the same use Ethernet_disableReceiveFlowControl() API
//!
//! \param base Base Address of the Ethernet Module
//! \param queueNum instance number of MAC address
//!         0,1 are valid queue Numbers
//! \return None
//***********************************************************************
static inline void Ethernet_enableReceiveFlowControl(uint32_t base,
                                    uint8_t queueNum)
{
    //
    //Enable the Hardware Flow Control
    //
    HWREG(base + ETHERNET_O_MTL_RXQ0_OPERATION_MODE +
          (queueNum * ETHERNET_QUEUE_OFFSET)) |=
        ETHERNET_MTL_RXQ0_OPERATION_MODE_EHFC;
}
//**********************************************************************
//! This API disables the Hardware Flow Control Mechanism in the receive Path
//! To Enable use Ethernet_disableReceiveFlowControl()
//!
//! \param base Base Address of the Ethernet Module
//! \param queueNum instance number of MAC address
//!         0,1 are valid queue Numbers
//! \return None
//***********************************************************************
static inline void Ethernet_disableReceiveFlowControl(uint32_t base,
                                        uint8_t queueNum)
{
    //
    //Clear the EHFC bit for the queueNumber provided
    //
      HWREG(base + ETHERNET_O_MTL_RXQ0_OPERATION_MODE +
            (queueNum * ETHERNET_QUEUE_OFFSET)) &=
        ~ETHERNET_MTL_RXQ0_OPERATION_MODE_EHFC;
}
//**********************************************************************
//! This API configures the parameters for the Hardware Flow Control Mechanism
//! in the receive Path of the Receive Queue
//! When a Pause Packet is received in Full duplex mode,the flow control
//! mechanism is triggered in Transmit path. For Half Duplex mode
//! the pause packets are only detected as control Packets
//! The Activation level controls when it is triggered and Deactivation level
//! controls when it is deactivated.
//!
//! \param base Base Address of the Ethernet Module
//! \param queueNum instance number of MAC address
//!         0,1 are valid queue Numbers
//! \return None
//***********************************************************************
static inline void Ethernet_configureReceiveFlowcontrol(uint32_t base,
                            uint8_t queueNum,
                            Ethernet_ReceiveFlowControlLevel activationLevel,
                            Ethernet_ReceiveFlowControlLevel deActivationLevel)
{
    //
    //First clear the contents of the Activation and Deactivation
    //Levels
    //
    HWREG(base + (queueNum * ETHERNET_QUEUE_OFFSET) +
          ETHERNET_O_MTL_RXQ0_OPERATION_MODE) &=
        ~ETHERNET_MTL_RXQ0_OPERATION_MODE_RFA_M;
    HWREG(base + (queueNum * ETHERNET_QUEUE_OFFSET) +
          ETHERNET_O_MTL_RXQ0_OPERATION_MODE) &=
        ~ETHERNET_MTL_RXQ0_OPERATION_MODE_RFD_M;
    //
    //Program the Threshold levels
    //
    HWREG(base + (queueNum * ETHERNET_QUEUE_OFFSET) +
          ETHERNET_O_MTL_RXQ0_OPERATION_MODE) |=
        (uint8_t)activationLevel << ETHERNET_MTL_RXQ0_OPERATION_MODE_RFA_S;
    //
    //Deactivation level for Receive Flow Control
    //
    HWREG(base + (queueNum * ETHERNET_QUEUE_OFFSET) +
          ETHERNET_O_MTL_RXQ0_OPERATION_MODE) |=
        (uint8_t)deActivationLevel << ETHERNET_MTL_RXQ0_OPERATION_MODE_RFD_S;
}
//**********************************************************************
//! This API enables the Receive Flow control at MAC Level
//!
//! \param base Base Address of the Ethernet Module
//! \return None
//***********************************************************************
static inline void Ethernet_enableMACReceiveFlowControl(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_RX_FLOW_CTRL) |=
        ETHERNET_MAC_RX_FLOW_CTRL_RFE;
}
//**********************************************************************
//! This API disables the Receive Flow control at MAC Level
//!
//! \param base Base Address of the Ethernet Module
//! \return None
//***********************************************************************
static inline void Ethernet_disableMACReceiveFlowControl(uint32_t base)
{
     HWREG(base + ETHERNET_O_MAC_RX_FLOW_CTRL) &=
        ~ETHERNET_MAC_RX_FLOW_CTRL_RFE;
}
//**********************************************************************
//! This API enables the Received unicast Pause Packets to be treated
//! as Flow control packets. By default only the Multicast address
//! pause packets are treated as Flow Control Packets
//! This API enables MAC Address 0 also to be considered as a unicast
//!
//! \param base Base Address of the Ethernet Module
//! \return None
//***********************************************************************
static inline void Ethernet_enableUnicastPauseFrameDetect(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_RX_FLOW_CTRL) |=
    ETHERNET_MAC_RX_FLOW_CTRL_UP;
}
//**********************************************************************
//! This API disables the Received unicast Pause Packets to be treated
//! as Flow control packets. Only the special Multicast address
//! pause packets are treated as Flow Control Packets
//! This API enables MAC Address 0 also to be considered as a unicast
//!
//! \param base Base Address of the Ethernet Module
//! \return None
//***********************************************************************
static inline void Ethernet_disableUnicastPauseFrameDetect(uint32_t base)
{
    HWREG(base + ETHERNET_O_MAC_RX_FLOW_CTRL) &=
         ~ETHERNET_MAC_RX_FLOW_CTRL_UP;
}

//*****************************************************************************
//
// Close the Doxygen group
//! @}
//
//****************************************************************************

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif
#endif
