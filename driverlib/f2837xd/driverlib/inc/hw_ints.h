//###########################################################################
//
// FILE:   hw_ints.h
//
// TITLE:  Definitions of interrupt numbers for use with interrupt.c.
//
//###########################################################################
//
//
//###########################################################################

#ifndef HW_INTS_H
#define HW_INTS_H

//*****************************************************************************
//
// PIE Interrupt Numbers
//
// 0x00FF = PIE Table Row #
// 0xFF00 = PIE Table Column #
// 0xFFFF0000 = PIE Vector ID
//
//*****************************************************************************

// Lower PIE Group 1
#define INT_ADCA1                   0x00200101U // 1.1 - ADCA Interrupt 1
#define INT_ADCB1                   0x00210102U // 1.2 - ADCB Interrupt 1
#define INT_ADCC1                   0x00220103U // 1.3 - ADCC Interrupt 1
#define INT_XINT1                   0x00230104U // 1.4 - XINT1 Interrupt
#define INT_XINT2                   0x00240105U // 1.5 - XINT2 Interrupt
#define INT_ADCD1                   0x00250106U // 1.6 - ADCD Interrupt 1
#define INT_TIMER0                  0x00260107U // 1.7 - Timer 0 Interrupt
#define INT_WAKE                    0x00270108U // 1.8 - Standby and Halt Wakeup Interrupt

// Lower PIE Group 2
#define INT_EPWM1_TZ                0x00280201U // 2.1 - ePWM1 Trip Zone Interrupt
#define INT_EPWM2_TZ                0x00290202U // 2.2 - ePWM2 Trip Zone Interrupt
#define INT_EPWM3_TZ                0x002A0203U // 2.3 - ePWM3 Trip Zone Interrupt
#define INT_EPWM4_TZ                0x002B0204U // 2.4 - ePWM4 Trip Zone Interrupt
#define INT_EPWM5_TZ                0x002C0205U // 2.5 - ePWM5 Trip Zone Interrupt
#define INT_EPWM6_TZ                0x002D0206U // 2.6 - ePWM6 Trip Zone Interrupt
#define INT_EPWM7_TZ                0x002E0207U // 2.7 - ePWM7 Trip Zone Interrupt
#define INT_EPWM8_TZ                0x002F0208U // 2.8 - ePWM8 Trip Zone Interrupt

// Lower PIE Group 3
#define INT_EPWM1                   0x00300301U // 3.1 - ePWM1 Interrupt
#define INT_EPWM2                   0x00310302U // 3.2 - ePWM2 Interrupt
#define INT_EPWM3                   0x00320303U // 3.3 - ePWM3 Interrupt
#define INT_EPWM4                   0x00330304U // 3.4 - ePWM4 Interrupt
#define INT_EPWM5                   0x00340305U // 3.5 - ePWM5 Interrupt
#define INT_EPWM6                   0x00350306U // 3.6 - ePWM6 Interrupt
#define INT_EPWM7                   0x00360307U // 3.7 - ePWM7 Interrupt
#define INT_EPWM8                   0x00370308U // 3.8 - ePWM8 Interrupt

// Lower PIE Group 4
#define INT_ECAP1                   0x00380401U // 4.1 - eCAP1 Interrupt
#define INT_ECAP2                   0x00390402U // 4.2 - eCAP2 Interrupt
#define INT_ECAP3                   0x003A0403U // 4.3 - eCAP3 Interrupt
#define INT_ECAP4                   0x003B0404U // 4.4 - eCAP4 Interrupt
#define INT_ECAP5                   0x003C0405U // 4.5 - eCAP5 Interrupt
#define INT_ECAP6                   0x003D0406U // 4.6 - eCAP6 Interrupt
// Lower PIE Group 5
#define INT_EQEP1                   0x00400501U // 5.1 - eQEP1 Interrupt
#define INT_EQEP2                   0x00410502U // 5.2 - eQEP2 Interrupt
#define INT_EQEP3                   0x00420503U // 5.3 - eQEP3 Interrupt
#define INT_CLB1                    0x00440505U // 5.5 - CLB1 (Reconfigurable Logic) Interrupt
#define INT_CLB2                    0x00450506U // 5.6 - CLB2 (Reconfigurable Logic) Interrupt
#define INT_CLB3                    0x00460507U // 5.7 - CLB3 (Reconfigurable Logic) Interrupt
#define INT_CLB4                    0x00470508U // 5.8 - CLB4 (Reconfigurable Logic) Interrupt

// Lower PIE Group 6
#define INT_SPIA_RX                 0x00480601U // 6.1 - SPIA Receive Interrupt
#define INT_SPIA_TX                 0x00490602U // 6.2 - SPIA Transmit Interrupt
#define INT_SPIB_RX                 0x004A0603U // 6.3 - SPIB Receive Interrupt
#define INT_SPIB_TX                 0x004B0604U // 6.4 - SPIB Transmit Interrupt
#define INT_MCBSPA_RX               0x004C0605U // 6.5 - McBSPA Receive Interrupt
#define INT_MCBSPA_TX               0x004D0606U // 6.6 - McBSPA Transmit Interrupt
#define INT_MCBSPB_RX               0x004E0607U // 6.7 - McBSPB Receive Interrupt
#define INT_MCBSPB_TX               0x004F0608U // 6.8 - McBSPB Transmit Interrupt

// Lower PIE Group 7
#define INT_DMA_CH1                 0x00500701U // 7.1 - DMA Channel 1 Interrupt
#define INT_DMA_CH2                 0x00510702U // 7.2 - DMA Channel 2 Interrupt
#define INT_DMA_CH3                 0x00520703U // 7.3 - DMA Channel 3 Interrupt
#define INT_DMA_CH4                 0x00530704U // 7.4 - DMA Channel 4 Interrupt
#define INT_DMA_CH5                 0x00540705U // 7.5 - DMA Channel 5 Interrupt
#define INT_DMA_CH6                 0x00550706U // 7.6 - DMA Channel 6 Interrupt

// Lower PIE Group 8
#define INT_I2CA                    0x00580801U // 8.1 - I2CA Interrupt 1
#define INT_I2CA_FIFO               0x00590802U // 8.2 - I2CA Interrupt 2
#define INT_I2CB                    0x005A0803U // 8.3 - I2CB Interrupt 1
#define INT_I2CB_FIFO               0x005B0804U // 8.4 - I2CB Interrupt 2
#define INT_SCIC_RX                 0x005C0805U // 8.5 - SCIC Receive Interrupt
#define INT_SCIC_TX                 0x005D0806U // 8.6 - SCIC Transmit Interrupt
#define INT_SCID_RX                 0x005E0807U // 8.7 - SCID Receive Interrupt
#define INT_SCID_TX                 0x005F0808U // 8.8 - SCID Transmit Interrupt

// Lower PIE Group 9
#define INT_SCIA_RX                 0x00600901U // 9.1 - SCIA Receive Interrupt
#define INT_SCIA_TX                 0x00610902U // 9.2 - SCIA Transmit Interrupt
#define INT_SCIB_RX                 0x00620903U // 9.3 - SCIB Receive Interrupt
#define INT_SCIB_TX                 0x00630904U // 9.4 - SCIB Transmit Interrupt
#define INT_CANA0                   0x00640905U // 9.5 - CANA Interrupt 0
#define INT_CANA1                   0x00650906U // 9.6 - CANA Interrupt 1
#define INT_CANB0                   0x00660907U // 9.7 - CANB Interrupt 0
#define INT_CANB1                   0x00670908U // 9.8 - CANB Interrupt 1

// Lower PIE Group 10
#define INT_ADCA_EVT                0x00680A01U // 10.1 - ADCA Event Interrupt
#define INT_ADCA2                   0x00690A02U // 10.2 - ADCA Interrupt 2
#define INT_ADCA3                   0x006A0A03U // 10.3 - ADCA Interrupt 3
#define INT_ADCA4                   0x006B0A04U // 10.4 - ADCA Interrupt 4
#define INT_ADCB_EVT                0x006C0A05U // 10.5 - ADCB Event Interrupt
#define INT_ADCB2                   0x006D0A06U // 10.6 - ADCB Interrupt 2
#define INT_ADCB3                   0x006E0A07U // 10.7 - ADCB Interrupt 3
#define INT_ADCB4                   0x006F0A08U // 10.8 - ADCB Interrupt 4

// Lower PIE Group 11
#define INT_CLA1_1                  0x00700B01U // 11.1 - CLA1 Interrupt 1
#define INT_CLA1_2                  0x00710B02U // 11.2 - CLA1 Interrupt 2
#define INT_CLA1_3                  0x00720B03U // 11.3 - CLA1 Interrupt 3
#define INT_CLA1_4                  0x00730B04U // 11.4 - CLA1 Interrupt 4
#define INT_CLA1_5                  0x00740B05U // 11.5 - CLA1 Interrupt 5
#define INT_CLA1_6                  0x00750B06U // 11.6 - CLA1 Interrupt 6
#define INT_CLA1_7                  0x00760B07U // 11.7 - CLA1 Interrupt 7
#define INT_CLA1_8                  0x00770B08U // 11.8 - CLA1 Interrupt 8

// Lower PIE Group 12
#define INT_XINT3                   0x00780C01U // 12.1 - XINT3 Interrupt
#define INT_XINT4                   0x00790C02U // 12.2 - XINT4 Interrupt
#define INT_XINT5                   0x007A0C03U // 12.3 - XINT5 Interrupt
#define INT_PBIST                   0x007B0C04U // 12.4 - PBIST Interrupt
#define INT_FMC                     0x007C0C05U // 12.5 - Flash Wrapper Operation Done Interrupt
#define INT_VCU                     0x007D0C06U // 12.6 - VCU Interrupt
#define INT_FPU_OVERFLOW            0x007E0C07U // 12.7 - FPU Overflow Interrupt
#define INT_FPU_UNDERFLOW           0x007F0C08U // 12.8 - FPU Underflow Interrupt

// Upper PIE Group 1
#define INT_IPC_0                   0x0084010DU // 1.13 - IPC Interrupt 1
#define INT_IPC_1                   0x0085010EU // 1.14 - IPC Interrupt 2
#define INT_IPC_2                   0x0086010FU // 1.15 - IPC Interrupt 3
#define INT_IPC_3                   0x00870110U // 1.16 - IPC Interrupt 4

// Upper PIE Group 2
#define INT_EPWM9_TZ                0x00880209U // 2.9 - ePWM9 Trip Zone Interrupt
#define INT_EPWM10_TZ               0x0089020AU // 2.10 - ePWM10 Trip Zone Interrupt
#define INT_EPWM11_TZ               0x008A020BU // 2.11 - ePWM11 Trip Zone Interrupt
#define INT_EPWM12_TZ               0x008B020CU // 2.12 - ePWM12 Trip Zone Interrupt

// Upper PIE Group 3
#define INT_EPWM9                   0x00900309U // 3.9 - ePWM9 Interrupt
#define INT_EPWM10                  0x0091030AU // 3.10 - ePWM10 Interrupt
#define INT_EPWM11                  0x0092030BU // 3.11 - ePWM11 Interrupt
#define INT_EPWM12                  0x0093030CU // 3.12 - ePWM12 Interrupt

// Upper PIE Group 5
#define INT_SD1                     0x00A00509U // 5.9 - SD1 Interrupt
#define INT_SD2                     0x00A1050AU // 5.10 - SD2 Interrupt

// Upper PIE Group 6
#define INT_SPIC_RX                 0x00A80609U // 6.9 - SPIC Receive Interrupt
#define INT_SPIC_TX                 0x00A9060AU // 6.10 - SPIC Transmit Interrupt

// Upper PIE Group 8
#define INT_UPPA                    0x00BE080FU // 8.15 - uPPA Interrupt

// Upper PIE Group 9
#define INT_USBA                    0x00C6090FU // 9.15 - USBA Interrupt

// Upper PIE Group 10
#define INT_ADCC_EVT                0x00C80A09U // 10.9 - ADCC Event Interrupt
#define INT_ADCC2                   0x00C90A0AU // 10.10 - ADCC Interrupt 2
#define INT_ADCC3                   0x00CA0A0BU // 10.11 - ADCC Interrupt 3
#define INT_ADCC4                   0x00CB0A0CU // 10.12 - ADCC Interrupt 4
#define INT_ADCD_EVT                0x00CC0A0DU // 10.13 - ADCD Event Interrupt
#define INT_ADCD2                   0x00CD0A0EU // 10.14 - ADCD Interrupt 2
#define INT_ADCD3                   0x00CE0A0FU // 10.15 - ADCD Interrupt 3
#define INT_ADCD4                   0x00CF0A10U // 10.16 - ADCD Interrupt 4

// Upper PIE Group 12
#define INT_EMIF_ERROR              0x00D80C09U // 12.9 - EMIF Error Interrupt
#define INT_RAM_CORR_ERR            0x00D90C0AU // 12.10 - RAM Correctable Error Interrupt
#define INT_FLASH_CORR_ERR          0x00DA0C0BU // 12.11 - Flash Correctable Error Interrupt
#define INT_RAM_ACC_VIOL            0x00DB0C0CU // 12.12 - RAM Access Violation Interrupt
#define INT_SYS_PLL_SLIP            0x00DC0C0DU // 12.13 - System PLL Slip Interrupt
#define INT_AUX_PLL_SLIP            0x00DD0C0EU // 12.14 - Auxiliary PLL Slip Interrupt
#define INT_CLA_OVERFLOW            0x00DE0C0FU // 12.15 - CLA Overflow Interrupt
#define INT_CLA_UNDERFLOW           0x00DF0C10U // 12.16 - CLA Underflow Interrupt

// Other interrupts
#define INT_TIMER1                  0x000D0000U // CPU Timer 1 Interrupt
#define INT_TIMER2                  0x000E0000U // CPU Timer 2 Interrupt
#define INT_DATALOG                 0x000F0000U // Datalogging Interrupt
#define INT_RTOS                    0x00100000U // RTOS Interrupt
#define INT_EMU                     0x00110000U // Emulation Interrupt
#define INT_NMI                     0x00120000U // Non-Maskable Interrupt
#define INT_ILLEGAL                 0x00130000U // Illegal Operation Trap
#define INT_USER1                   0x00140000U // User Defined Trap 1
#define INT_USER2                   0x00150000U // User Defined Trap 2
#define INT_USER3                   0x00160000U // User Defined Trap 3
#define INT_USER4                   0x00170000U // User Defined Trap 4
#define INT_USER5                   0x00180000U // User Defined Trap 5
#define INT_USER6                   0x00190000U // User Defined Trap 6
#define INT_USER7                   0x001A0000U // User Defined Trap 7
#define INT_USER8                   0x001B0000U // User Defined Trap 8
#define INT_USER9                   0x001C0000U // User Defined Trap 9
#define INT_USER10                  0x001D0000U // User Defined Trap 10
#define INT_USER11                  0x001E0000U // User Defined Trap 11
#define INT_USER12                  0x001F0000U // User Defined Trap 12

#endif // HW_INTS_H
