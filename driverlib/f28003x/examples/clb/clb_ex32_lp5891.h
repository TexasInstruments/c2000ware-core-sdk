//#############################################################################
//
// FILE:   clb_ex32_lp5891.h
//
// TITLE:  LP5891 register and bit definitions.
//
//#############################################################################
// $TI Release: F28003x Support Library v6.00.01.00 $
// 
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
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

#ifndef CLB_EX32_LP5891_H_
#define CLB_EX32_LP5891_H_

enum WRITE_COMMAND_ID{
    W_FC0 = 0xAA00,
    W_FC1,
    W_FC2,
    W_FC3,
    W_FC4,
    W_FC14 = 0xAA0E,
    W_FC15,
    W_CHIP_INDEX = 0xAA10,
    W_VSYNC = 0XAAF0,
    W_SOFT_RESET = 0XAA80,
    W_SRAM = 0xAA30
};

enum READ_COMMAND_ID{
    R_FC0 = 0xAA60,
    R_FC1,
    R_FC2,
    R_FC3,
    R_FC4,
    R_FC14 = 0xAA6E,
    R_FC15,
    R_FC16 = 0xAAA0,
    R_FC17,
    R_FC18,
    R_FC19,
    R_FC20,
    R_FC21,
    R_CHIP_INDEX = 0xAA70
};

#define RGB_CHANNEL_CNT 16
#define CHANNEL_CNT 48
#define LP589X 1
#define LP5891 1

/* FC0  Bits */
#define LSD_RM_EN_1                        (0x800000000000)        /* enable */
#define LSD_RM_EN_0                        (0x000000000000)        /* disable */
#define LSD_RM_EN__1                       (0x800000000000)        /* enable */
#define LSD_RM_EN__0                       (0x000000000000)        /* disable */
#define GRP_DLY_B_7                        (0x1C0000000000)        /* 7 GCLK */
#define GRP_DLY_B_6                        (0x180000000000)        /* 6 GCLK */
#define GRP_DLY_B_5                        (0x140000000000)        /* 5 GCLK */
#define GRP_DLY_B_4                        (0x100000000000)        /* 4 GCLK */
#define GRP_DLY_B_3                        (0x0C0000000000)        /* 3 GCLK */
#define GRP_DLY_B_2                        (0x080000000000)        /* 2 GCLK */
#define GRP_DLY_B_1                        (0x040000000000)        /* 1 GCLK */
#define GRP_DLY_B_0                        (0x000000000000)        /* no delay */
#define GRP_DLY_B__7                       (0x1C0000000000)        /* 7 GCLK */
#define GRP_DLY_B__6                       (0x180000000000)        /* 6 GCLK */
#define GRP_DLY_B__5                       (0x140000000000)        /* 5 GCLK */
#define GRP_DLY_B__4                       (0x100000000000)        /* 4 GCLK */
#define GRP_DLY_B__3                       (0x0C0000000000)        /* 3 GCLK */
#define GRP_DLY_B__2                       (0x080000000000)        /* 2 GCLK */
#define GRP_DLY_B__1                       (0x040000000000)        /* 1 GCLK */
#define GRP_DLY_B__0                       (0x000000000000)        /* no delay */
#define GRP_DLY_G_7                        (0x038000000000)        /* 7 GCLK */
#define GRP_DLY_G_6                        (0x030000000000)        /* 6 GCLK */
#define GRP_DLY_G_5                        (0x028000000000)        /* 5 GCLK */
#define GRP_DLY_G_4                        (0x020000000000)        /* 4 GCLK */
#define GRP_DLY_G_3                        (0x018000000000)        /* 3 GCLK */
#define GRP_DLY_G_2                        (0x010000000000)        /* 2 GCLK */
#define GRP_DLY_G_1                        (0x008000000000)        /* 1 GCLK */
#define GRP_DLY_G_0                        (0x000000000000)        /* no delay */
#define GRP_DLY_G__7                       (0x038000000000)        /* 7 GCLK */
#define GRP_DLY_G__6                       (0x030000000000)        /* 6 GCLK */
#define GRP_DLY_G__5                       (0x028000000000)        /* 5 GCLK */
#define GRP_DLY_G__4                       (0x020000000000)        /* 4 GCLK */
#define GRP_DLY_G__3                       (0x018000000000)        /* 3 GCLK */
#define GRP_DLY_G__2                       (0x010000000000)        /* 2 GCLK */
#define GRP_DLY_G__1                       (0x008000000000)        /* 1 GCLK */
#define GRP_DLY_G__0                       (0x000000000000)        /* no delay */
#define GRP_DLY_R_7                        (0x007000000000)        /* 7 GCLK */
#define GRP_DLY_R_6                        (0x006000000000)        /* 6 GCLK */
#define GRP_DLY_R_5                        (0x005000000000)        /* 5 GCLK */
#define GRP_DLY_R_4                        (0x004000000000)        /* 4 GCLK */
#define GRP_DLY_R_3                        (0x003000000000)        /* 3 GCLK */
#define GRP_DLY_R_2                        (0x002000000000)        /* 2 GCLK */
#define GRP_DLY_R_1                        (0x001000000000)        /* 1 GCLK */
#define GRP_DLY_R_0                        (0x000000000000)        /* no delay */
#define GRP_DLY_R__7                       (0x007000000000)        /* 7 GCLK */
#define GRP_DLY_R__6                       (0x006000000000)        /* 6 GCLK */
#define GRP_DLY_R__5                       (0x005000000000)        /* 5 GCLK */
#define GRP_DLY_R__4                       (0x004000000000)        /* 4 GCLK */
#define GRP_DLY_R__3                       (0x003000000000)        /* 3 GCLK */
#define GRP_DLY_R__2                       (0x002000000000)        /* 2 GCLK */
#define GRP_DLY_R__1                       (0x001000000000)        /* 1 GCLK */
#define GRP_DLY_R__0                       (0x000000000000)        /* no delay */
#define FREQ_MUL_15                        (0x0001E0000000)        /* 16 x SCLK frequency */
#define FREQ_MUL_14                        (0x0001C0000000)        /* 15 x SCLK frequency */
#define FREQ_MUL_13                        (0x0001A0000000)        /* 14 x SCLK frequency */
#define FREQ_MUL_12                        (0x000180000000)        /* 13 x SCLK frequency */
#define FREQ_MUL_11                        (0x000160000000)        /* 12 x SCLK frequency */
#define FREQ_MUL_10                        (0x000140000000)        /* 11 x SCLK frequency */
#define FREQ_MUL_9                         (0x000120000000)        /* 10 x SCLK frequency */
#define FREQ_MUL_8                         (0x000100000000)        /* 9 x SCLK frequency */
#define FREQ_MUL_7                         (0x0000E0000000)        /* 8 x SCLK frequency */
#define FREQ_MUL_6                         (0x0000C0000000)        /* 7 x SCLK frequency */
#define FREQ_MUL_5                         (0x0000A0000000)        /* 6 x SCLK frequency */
#define FREQ_MUL_4                         (0x000080000000)        /* 5 x SCLK frequency */
#define FREQ_MUL_3                         (0x000060000000)        /* 4 x SCLK frequency */
#define FREQ_MUL_2                         (0x000040000000)        /* 3 x SCLK frequency */
#define FREQ_MUL_1                         (0x000020000000)        /* 2 x SCLK frequency */
#define FREQ_MUL_0                         (0x000000000000)        /* 1 x SCLK frequency */
#define FREQ_MUL__16                       (0x0001E0000000)        /* 16 x SCLK frequency */
#define FREQ_MUL__15                       (0x0001C0000000)        /* 15 x SCLK frequency */
#define FREQ_MUL__14                       (0x0001A0000000)        /* 14 x SCLK frequency */
#define FREQ_MUL__13                       (0x000180000000)        /* 13 x SCLK frequency */
#define FREQ_MUL__12                       (0x000160000000)        /* 12 x SCLK frequency */
#define FREQ_MUL__11                       (0x000140000000)        /* 11 x SCLK frequency */
#define FREQ_MUL__10                       (0x000120000000)        /* 10 x SCLK frequency */
#define FREQ_MUL__9                        (0x000100000000)        /* 9 x SCLK frequency */
#define FREQ_MUL__8                        (0x0000E0000000)        /* 8 x SCLK frequency */
#define FREQ_MUL__7                        (0x0000C0000000)        /* 7 x SCLK frequency */
#define FREQ_MUL__6                        (0x0000A0000000)        /* 6 x SCLK frequency */
#define FREQ_MUL__5                        (0x000080000000)        /* 5 x SCLK frequency */
#define FREQ_MUL__4                        (0x000060000000)        /* 4 x SCLK frequency */
#define FREQ_MUL__3                        (0x000040000000)        /* 3 x SCLK frequency */
#define FREQ_MUL__2                        (0x000020000000)        /* 2 x SCLK frequency */
#define FREQ_MUL__1                        (0x000000000000)        /* 1 x SCLK frequency */
#define FREQ_MOD_1                         (0x000010000000)        /* low frequency mode, 40MHz to 80MHz */
#define FREQ_MOD_0                         (0x000000000000)        /* high frequency mode, 80MHz to 160MHz */
#define FREQ_MOD__1                        (0x000010000000)        /* low frequency mode, 40MHz to 80MHz */
#define FREQ_MOD__0                        (0x000000000000)        /* high frequency mode, 80MHz to 160MHz */
#define FREQ_MOD__LF                       (0x000010000000)        /* low frequency mode, 40MHz to 80MHz */
#define FREQ_MOD__HF                       (0x000000000000)        /* high frequency mode, 80MHz to 160MHz */
#define SUBP_NUM_7                         (0x000001C00000)        /* 128 */
#define SUBP_NUM_6                         (0x000001800000)        /* 112 */
#define SUBP_NUM_5                         (0x000001400000)        /* 96 */
#define SUBP_NUM_4                         (0x000001000000)        /* 80 */
#define SUBP_NUM_3                         (0x000000C00000)        /* 64 */
#define SUBP_NUM_2                         (0x000000800000)        /* 48 */
#define SUBP_NUM_1                         (0x000000400000)        /* 32 */
#define SUBP_NUM_0                         (0x000000000000)        /* 16 */
#define SUBP_NUM__128                      (0x000001C00000)        /* 128 */
#define SUBP_NUM__112                      (0x000001800000)        /* 112 */
#define SUBP_NUM__96                       (0x000001400000)        /* 96 */
#define SUBP_NUM__80                       (0x000001000000)        /* 80 */
#define SUBP_NUM__64                       (0x000000C00000)        /* 64 */
#define SUBP_NUM__48                       (0x000000800000)        /* 48 */
#define SUBP_NUM__32                       (0x000000400000)        /* 32 */
#define SUBP_NUM__16                       (0x000000000000)        /* 16 */
#define SCAN_NUM_63                        (0x0000003F0000)        /* 64 lines */
#define SCAN_NUM_62                        (0x0000003E0000)        /* 63 lines */
#define SCAN_NUM_61                        (0x0000003D0000)        /* 62 lines */
#define SCAN_NUM_60                        (0x0000003C0000)        /* 61 lines */
#define SCAN_NUM_59                        (0x0000003B0000)        /* 60 lines */
#define SCAN_NUM_58                        (0x0000003A0000)        /* 59 lines */
#define SCAN_NUM_57                        (0x000000390000)        /* 58 lines */
#define SCAN_NUM_56                        (0x000000380000)        /* 57 lines */
#define SCAN_NUM_55                        (0x000000370000)        /* 56 lines */
#define SCAN_NUM_54                        (0x000000360000)        /* 55 lines */
#define SCAN_NUM_53                        (0x000000350000)        /* 54 lines */
#define SCAN_NUM_52                        (0x000000340000)        /* 53 lines */
#define SCAN_NUM_51                        (0x000000330000)        /* 52 lines */
#define SCAN_NUM_50                        (0x000000320000)        /* 51 lines */
#define SCAN_NUM_49                        (0x000000310000)        /* 50 lines */
#define SCAN_NUM_48                        (0x000000300000)        /* 49 lines */
#define SCAN_NUM_47                        (0x0000002F0000)        /* 48 lines */
#define SCAN_NUM_46                        (0x0000002E0000)        /* 47 lines */
#define SCAN_NUM_45                        (0x0000002D0000)        /* 46 lines */
#define SCAN_NUM_44                        (0x0000002C0000)        /* 45 lines */
#define SCAN_NUM_43                        (0x0000002B0000)        /* 44 lines */
#define SCAN_NUM_42                        (0x0000002A0000)        /* 43 lines */
#define SCAN_NUM_41                        (0x000000290000)        /* 42 lines */
#define SCAN_NUM_40                        (0x000000280000)        /* 41 lines */
#define SCAN_NUM_39                        (0x000000270000)        /* 40 lines */
#define SCAN_NUM_38                        (0x000000260000)        /* 39 lines */
#define SCAN_NUM_37                        (0x000000250000)        /* 38 lines */
#define SCAN_NUM_36                        (0x000000240000)        /* 37 lines */
#define SCAN_NUM_35                        (0x000000230000)        /* 36 lines */
#define SCAN_NUM_34                        (0x000000220000)        /* 35 lines */
#define SCAN_NUM_33                        (0x000000210000)        /* 34 lines */
#define SCAN_NUM_32                        (0x000000200000)        /* 33 lines */
#define SCAN_NUM_31                        (0x0000001F0000)        /* 32 lines */
#define SCAN_NUM_30                        (0x0000001E0000)        /* 31 lines */
#define SCAN_NUM_29                        (0x0000001D0000)        /* 30 lines */
#define SCAN_NUM_28                        (0x0000001C0000)        /* 29 lines */
#define SCAN_NUM_27                        (0x0000001B0000)        /* 28 lines */
#define SCAN_NUM_26                        (0x0000001A0000)        /* 27 lines */
#define SCAN_NUM_25                        (0x000000190000)        /* 26 lines */
#define SCAN_NUM_24                        (0x000000180000)        /* 25 lines */
#define SCAN_NUM_23                        (0x000000170000)        /* 24 lines */
#define SCAN_NUM_22                        (0x000000160000)        /* 23 lines */
#define SCAN_NUM_21                        (0x000000150000)        /* 22 lines */
#define SCAN_NUM_20                        (0x000000140000)        /* 21 lines */
#define SCAN_NUM_19                        (0x000000130000)        /* 20 lines */
#define SCAN_NUM_18                        (0x000000120000)        /* 19 lines */
#define SCAN_NUM_17                        (0x000000110000)        /* 18 lines */
#define SCAN_NUM_16                        (0x000000100000)        /* 17 lines */
#define SCAN_NUM_15                        (0x0000000F0000)        /* 16 lines */
#define SCAN_NUM_14                        (0x0000000E0000)        /* 15 lines */
#define SCAN_NUM_13                        (0x0000000D0000)        /* 14 lines */
#define SCAN_NUM_12                        (0x0000000C0000)        /* 13 lines */
#define SCAN_NUM_11                        (0x0000000B0000)        /* 12 lines */
#define SCAN_NUM_10                        (0x0000000A0000)        /* 11 lines */
#define SCAN_NUM_9                         (0x000000090000)        /* 10 lines */
#define SCAN_NUM_8                         (0x000000080000)        /* 9 lines */
#define SCAN_NUM_7                         (0x000000070000)        /* 8 lines */
#define SCAN_NUM_6                         (0x000000060000)        /* 7 lines */
#define SCAN_NUM_5                         (0x000000050000)        /* 6 lines */
#define SCAN_NUM_4                         (0x000000040000)        /* 5 lines */
#define SCAN_NUM_3                         (0x000000030000)        /* 4 lines */
#define SCAN_NUM_2                         (0x000000020000)        /* 3 lines */
#define SCAN_NUM_1                         (0x000000010000)        /* 2 lines */
#define SCAN_NUM_0                         (0x000000000000)        /* 1 lines */
#define SCAN_NUM__MAX                      (0x0000003F0000)        /* 64 lines */
#define SCAN_NUM__64                       (0x0000003F0000)        /* 64 lines */
#define SCAN_NUM__63                       (0x0000003E0000)        /* 63 lines */
#define SCAN_NUM__62                       (0x0000003D0000)        /* 62 lines */
#define SCAN_NUM__61                       (0x0000003C0000)        /* 61 lines */
#define SCAN_NUM__60                       (0x0000003B0000)        /* 60 lines */
#define SCAN_NUM__59                       (0x0000003A0000)        /* 59 lines */
#define SCAN_NUM__58                       (0x000000390000)        /* 58 lines */
#define SCAN_NUM__57                       (0x000000380000)        /* 57 lines */
#define SCAN_NUM__56                       (0x000000370000)        /* 56 lines */
#define SCAN_NUM__55                       (0x000000360000)        /* 55 lines */
#define SCAN_NUM__54                       (0x000000350000)        /* 54 lines */
#define SCAN_NUM__53                       (0x000000340000)        /* 53 lines */
#define SCAN_NUM__52                       (0x000000330000)        /* 52 lines */
#define SCAN_NUM__51                       (0x000000320000)        /* 51 lines */
#define SCAN_NUM__50                       (0x000000310000)        /* 50 lines */
#define SCAN_NUM__49                       (0x000000300000)        /* 49 lines */
#define SCAN_NUM__48                       (0x0000002F0000)        /* 48 lines */
#define SCAN_NUM__47                       (0x0000002E0000)        /* 47 lines */
#define SCAN_NUM__46                       (0x0000002D0000)        /* 46 lines */
#define SCAN_NUM__45                       (0x0000002C0000)        /* 45 lines */
#define SCAN_NUM__44                       (0x0000002B0000)        /* 44 lines */
#define SCAN_NUM__43                       (0x0000002A0000)        /* 43 lines */
#define SCAN_NUM__42                       (0x000000290000)        /* 42 lines */
#define SCAN_NUM__41                       (0x000000280000)        /* 41 lines */
#define SCAN_NUM__40                       (0x000000270000)        /* 40 lines */
#define SCAN_NUM__39                       (0x000000260000)        /* 39 lines */
#define SCAN_NUM__38                       (0x000000250000)        /* 38 lines */
#define SCAN_NUM__37                       (0x000000240000)        /* 37 lines */
#define SCAN_NUM__36                       (0x000000230000)        /* 36 lines */
#define SCAN_NUM__35                       (0x000000220000)        /* 35 lines */
#define SCAN_NUM__34                       (0x000000210000)        /* 34 lines */
#define SCAN_NUM__33                       (0x000000200000)        /* 33 lines */
#define SCAN_NUM__32                       (0x0000001F0000)        /* 32 lines */
#define SCAN_NUM__31                       (0x0000001E0000)        /* 31 lines */
#define SCAN_NUM__30                       (0x0000001D0000)        /* 30 lines */
#define SCAN_NUM__29                       (0x0000001C0000)        /* 29 lines */
#define SCAN_NUM__28                       (0x0000001B0000)        /* 28 lines */
#define SCAN_NUM__27                       (0x0000001A0000)        /* 27 lines */
#define SCAN_NUM__26                       (0x000000190000)        /* 26 lines */
#define SCAN_NUM__25                       (0x000000180000)        /* 25 lines */
#define SCAN_NUM__24                       (0x000000170000)        /* 24 lines */
#define SCAN_NUM__23                       (0x000000160000)        /* 23 lines */
#define SCAN_NUM__22                       (0x000000150000)        /* 22 lines */
#define SCAN_NUM__21                       (0x000000140000)        /* 21 lines */
#define SCAN_NUM__20                       (0x000000130000)        /* 20 lines */
#define SCAN_NUM__19                       (0x000000120000)        /* 19 lines */
#define SCAN_NUM__18                       (0x000000110000)        /* 18 lines */
#define SCAN_NUM__17                       (0x000000100000)        /* 17 lines */
#define SCAN_NUM__16                       (0x0000000F0000)        /* 16 lines */
#define SCAN_NUM__15                       (0x0000000E0000)        /* 15 lines */
#define SCAN_NUM__14                       (0x0000000D0000)        /* 14 lines */
#define SCAN_NUM__13                       (0x0000000C0000)        /* 13 lines */
#define SCAN_NUM__12                       (0x0000000B0000)        /* 12 lines */
#define SCAN_NUM__11                       (0x0000000A0000)        /* 11 lines */
#define SCAN_NUM__10                       (0x000000090000)        /* 10 lines */
#define SCAN_NUM__9                        (0x000000080000)        /* 9 lines */
#define SCAN_NUM__8                        (0x000000070000)        /* 8 lines */
#define SCAN_NUM__7                        (0x000000060000)        /* 7 lines */
#define SCAN_NUM__6                        (0x000000050000)        /* 6 lines */
#define SCAN_NUM__5                        (0x000000040000)        /* 5 lines */
#define SCAN_NUM__4                        (0x000000030000)        /* 4 lines */
#define SCAN_NUM__3                        (0x000000020000)        /* 3 lines */
#define SCAN_NUM__2                        (0x000000010000)        /* 2 lines */
#define SCAN_NUM__1                        (0x000000000000)        /* 1 lines */
#define LODRM_EN_1                         (0x000000008000)        /* enable */
#define LODRM_EN_0                         (0x000000000000)        /* disable */
#define LODRM_EN__1                        (0x000000008000)        /* enable */
#define LODRM_EN__0                        (0x000000000000)        /* disable */
#define PSP_MOD_3                          (0x000000006000)        /* save power at low level */
#define PSP_MOD_2                          (0x000000004000)        /* save power at middle level */
#define PSP_MOD_1                          (0x000000002000)        /* save power at high level */
#define PSP_MOD_0                          (0x000000000000)        /* disable */
#define PSP_MOD__3                         (0x000000006000)        /* save power at low level */
#define PSP_MOD__2                         (0x000000004000)        /* save power at middle level */
#define PSP_MOD__1                         (0x000000002000)        /* save power at high level */
#define PSP_MOD__0                         (0x000000000000)        /* disable */
#define PS_EN_1                            (0x000000001000)        /* enable */
#define PS_EN_0                            (0x000000000000)        /* disable */
#define PS_EN__1                           (0x000000001000)        /* enable */
#define PS_EN__0                           (0x000000000000)        /* disable */
#define PDC_EN_1                           (0x000000000100)        /* enable */
#define PDC_EN_0                           (0x000000000000)        /* disable */
#define PDC_EN__1                          (0x000000000100)        /* enable */
#define PDC_EN__0                          (0x000000000000)        /* disable */
#define CHIP_NUM_31                        (0x00000000001F)        /* 32 devices */
#define CHIP_NUM_30                        (0x00000000001E)        /* 31 devices */
#define CHIP_NUM_29                        (0x00000000001D)        /* 30 devices */
#define CHIP_NUM_28                        (0x00000000001C)        /* 29 devices */
#define CHIP_NUM_27                        (0x00000000001B)        /* 28 devices */
#define CHIP_NUM_26                        (0x00000000001A)        /* 27 devices */
#define CHIP_NUM_25                        (0x000000000019)        /* 26 devices */
#define CHIP_NUM_24                        (0x000000000018)        /* 25 devices */
#define CHIP_NUM_23                        (0x000000000017)        /* 24 devices */
#define CHIP_NUM_22                        (0x000000000016)        /* 23 devices */
#define CHIP_NUM_21                        (0x000000000015)        /* 22 devices */
#define CHIP_NUM_20                        (0x000000000014)        /* 21 devices */
#define CHIP_NUM_19                        (0x000000000013)        /* 20 devices */
#define CHIP_NUM_18                        (0x000000000012)        /* 19 devices */
#define CHIP_NUM_17                        (0x000000000011)        /* 18 devices */
#define CHIP_NUM_16                        (0x000000000010)        /* 17 devices */
#define CHIP_NUM_15                        (0x00000000000F)        /* 16 devices */
#define CHIP_NUM_14                        (0x00000000000E)        /* 15 devices */
#define CHIP_NUM_13                        (0x00000000000D)        /* 14 devices */
#define CHIP_NUM_12                        (0x00000000000C)        /* 13 devices */
#define CHIP_NUM_11                        (0x00000000000B)        /* 12 devices */
#define CHIP_NUM_10                        (0x00000000000A)        /* 11 devices */
#define CHIP_NUM_9                         (0x000000000009)        /* 10 devices */
#define CHIP_NUM_8                         (0x000000000008)        /* 9 devices */
#define CHIP_NUM_7                         (0x000000000007)        /* 8 devices */
#define CHIP_NUM_6                         (0x000000000006)        /* 7 devices */
#define CHIP_NUM_5                         (0x000000000005)        /* 6 devices */
#define CHIP_NUM_4                         (0x000000000004)        /* 5 devices */
#define CHIP_NUM_3                         (0x000000000003)        /* 4 devices */
#define CHIP_NUM_2                         (0x000000000002)        /* 3 devices */
#define CHIP_NUM_1                         (0x000000000001)        /* 2 devices */
#define CHIP_NUM_0                         (0x000000000000)        /* 1 devices */
#define CHIP_NUM__32                       (0x00000000001F)        /* 32 devices */
#define CHIP_NUM__31                       (0x00000000001E)        /* 31 devices */
#define CHIP_NUM__30                       (0x00000000001D)        /* 30 devices */
#define CHIP_NUM__29                       (0x00000000001C)        /* 29 devices */
#define CHIP_NUM__28                       (0x00000000001B)        /* 28 devices */
#define CHIP_NUM__27                       (0x00000000001A)        /* 27 devices */
#define CHIP_NUM__26                       (0x000000000019)        /* 26 devices */
#define CHIP_NUM__25                       (0x000000000018)        /* 25 devices */
#define CHIP_NUM__24                       (0x000000000017)        /* 24 devices */
#define CHIP_NUM__23                       (0x000000000016)        /* 23 devices */
#define CHIP_NUM__22                       (0x000000000015)        /* 22 devices */
#define CHIP_NUM__21                       (0x000000000014)        /* 21 devices */
#define CHIP_NUM__20                       (0x000000000013)        /* 20 devices */
#define CHIP_NUM__19                       (0x000000000012)        /* 19 devices */
#define CHIP_NUM__18                       (0x000000000011)        /* 18 devices */
#define CHIP_NUM__17                       (0x000000000010)        /* 17 devices */
#define CHIP_NUM__16                       (0x00000000000F)        /* 16 devices */
#define CHIP_NUM__15                       (0x00000000000E)        /* 15 devices */
#define CHIP_NUM__14                       (0x00000000000D)        /* 14 devices */
#define CHIP_NUM__13                       (0x00000000000C)        /* 13 devices */
#define CHIP_NUM__12                       (0x00000000000B)        /* 12 devices */
#define CHIP_NUM__11                       (0x00000000000A)        /* 11 devices */
#define CHIP_NUM__10                       (0x000000000009)        /* 10 devices */
#define CHIP_NUM__9                        (0x000000000008)        /* 9 devices */
#define CHIP_NUM__8                        (0x000000000007)        /* 8 devices */
#define CHIP_NUM__7                        (0x000000000006)        /* 7 devices */
#define CHIP_NUM__6                        (0x000000000005)        /* 6 devices */
#define CHIP_NUM__5                        (0x000000000004)        /* 5 devices */
#define CHIP_NUM__4                        (0x000000000003)        /* 4 devices */
#define CHIP_NUM__3                        (0x000000000002)        /* 3 devices */
#define CHIP_NUM__2                        (0x000000000001)        /* 2 devices */
#define CHIP_NUM__1                        (0x000000000000)        /* 1 devices */

/* FC1  Bits */
#define BLK_ADJ_63                         (0x7E0000000000)        /* 63 GCLK */
#define BLK_ADJ_62                         (0x7C0000000000)        /* 62 GCLK */
#define BLK_ADJ_61                         (0x7A0000000000)        /* 61 GCLK */
#define BLK_ADJ_60                         (0x780000000000)        /* 60 GCLK */
#define BLK_ADJ_59                         (0x760000000000)        /* 59 GCLK */
#define BLK_ADJ_58                         (0x740000000000)        /* 58 GCLK */
#define BLK_ADJ_57                         (0x720000000000)        /* 57 GCLK */
#define BLK_ADJ_56                         (0x700000000000)        /* 56 GCLK */
#define BLK_ADJ_55                         (0x6E0000000000)        /* 55 GCLK */
#define BLK_ADJ_54                         (0x6C0000000000)        /* 54 GCLK */
#define BLK_ADJ_53                         (0x6A0000000000)        /* 53 GCLK */
#define BLK_ADJ_52                         (0x680000000000)        /* 52 GCLK */
#define BLK_ADJ_51                         (0x660000000000)        /* 51 GCLK */
#define BLK_ADJ_50                         (0x640000000000)        /* 50 GCLK */
#define BLK_ADJ_49                         (0x620000000000)        /* 49 GCLK */
#define BLK_ADJ_48                         (0x600000000000)        /* 48 GCLK */
#define BLK_ADJ_47                         (0x5E0000000000)        /* 47 GCLK */
#define BLK_ADJ_46                         (0x5C0000000000)        /* 46 GCLK */
#define BLK_ADJ_45                         (0x5A0000000000)        /* 45 GCLK */
#define BLK_ADJ_44                         (0x580000000000)        /* 44 GCLK */
#define BLK_ADJ_43                         (0x560000000000)        /* 43 GCLK */
#define BLK_ADJ_42                         (0x540000000000)        /* 42 GCLK */
#define BLK_ADJ_41                         (0x520000000000)        /* 41 GCLK */
#define BLK_ADJ_40                         (0x500000000000)        /* 40 GCLK */
#define BLK_ADJ_39                         (0x4E0000000000)        /* 39 GCLK */
#define BLK_ADJ_38                         (0x4C0000000000)        /* 38 GCLK */
#define BLK_ADJ_37                         (0x4A0000000000)        /* 37 GCLK */
#define BLK_ADJ_36                         (0x480000000000)        /* 36 GCLK */
#define BLK_ADJ_35                         (0x460000000000)        /* 35 GCLK */
#define BLK_ADJ_34                         (0x440000000000)        /* 34 GCLK */
#define BLK_ADJ_33                         (0x420000000000)        /* 33 GCLK */
#define BLK_ADJ_32                         (0x400000000000)        /* 32 GCLK */
#define BLK_ADJ_31                         (0x3E0000000000)        /* 31 GCLK */
#define BLK_ADJ_30                         (0x3C0000000000)        /* 30 GCLK */
#define BLK_ADJ_29                         (0x3A0000000000)        /* 29 GCLK */
#define BLK_ADJ_28                         (0x380000000000)        /* 28 GCLK */
#define BLK_ADJ_27                         (0x360000000000)        /* 27 GCLK */
#define BLK_ADJ_26                         (0x340000000000)        /* 26 GCLK */
#define BLK_ADJ_25                         (0x320000000000)        /* 25 GCLK */
#define BLK_ADJ_24                         (0x300000000000)        /* 24 GCLK */
#define BLK_ADJ_23                         (0x2E0000000000)        /* 23 GCLK */
#define BLK_ADJ_22                         (0x2C0000000000)        /* 22 GCLK */
#define BLK_ADJ_21                         (0x2A0000000000)        /* 21 GCLK */
#define BLK_ADJ_20                         (0x280000000000)        /* 20 GCLK */
#define BLK_ADJ_19                         (0x260000000000)        /* 19 GCLK */
#define BLK_ADJ_18                         (0x240000000000)        /* 18 GCLK */
#define BLK_ADJ_17                         (0x220000000000)        /* 17 GCLK */
#define BLK_ADJ_16                         (0x200000000000)        /* 16 GCLK */
#define BLK_ADJ_15                         (0x1E0000000000)        /* 15 GCLK */
#define BLK_ADJ_14                         (0x1C0000000000)        /* 14 GCLK */
#define BLK_ADJ_13                         (0x1A0000000000)        /* 13 GCLK */
#define BLK_ADJ_12                         (0x180000000000)        /* 12 GCLK */
#define BLK_ADJ_11                         (0x160000000000)        /* 11 GCLK */
#define BLK_ADJ_10                         (0x140000000000)        /* 10 GCLK */
#define BLK_ADJ_9                          (0x120000000000)        /* 9 GCLK */
#define BLK_ADJ_8                          (0x100000000000)        /* 8 GCLK */
#define BLK_ADJ_7                          (0x0E0000000000)        /* 7 GCLK */
#define BLK_ADJ_6                          (0x0C0000000000)        /* 6 GCLK */
#define BLK_ADJ_5                          (0x0A0000000000)        /* 5 GCLK */
#define BLK_ADJ_4                          (0x080000000000)        /* 4 GCLK */
#define BLK_ADJ_3                          (0x060000000000)        /* 3 GCLK */
#define BLK_ADJ_2                          (0x040000000000)        /* 2 GCLK */
#define BLK_ADJ_1                          (0x020000000000)        /* 1 GCLK */
#define BLK_ADJ_0                          (0x000000000000)        /* 0 GCLK */
#define BLK_ADJ__63                        (0x7E0000000000)        /* 63 GCLK */
#define BLK_ADJ__62                        (0x7C0000000000)        /* 62 GCLK */
#define BLK_ADJ__61                        (0x7A0000000000)        /* 61 GCLK */
#define BLK_ADJ__60                        (0x780000000000)        /* 60 GCLK */
#define BLK_ADJ__59                        (0x760000000000)        /* 59 GCLK */
#define BLK_ADJ__58                        (0x740000000000)        /* 58 GCLK */
#define BLK_ADJ__57                        (0x720000000000)        /* 57 GCLK */
#define BLK_ADJ__56                        (0x700000000000)        /* 56 GCLK */
#define BLK_ADJ__55                        (0x6E0000000000)        /* 55 GCLK */
#define BLK_ADJ__54                        (0x6C0000000000)        /* 54 GCLK */
#define BLK_ADJ__53                        (0x6A0000000000)        /* 53 GCLK */
#define BLK_ADJ__52                        (0x680000000000)        /* 52 GCLK */
#define BLK_ADJ__51                        (0x660000000000)        /* 51 GCLK */
#define BLK_ADJ__50                        (0x640000000000)        /* 50 GCLK */
#define BLK_ADJ__49                        (0x620000000000)        /* 49 GCLK */
#define BLK_ADJ__48                        (0x600000000000)        /* 48 GCLK */
#define BLK_ADJ__47                        (0x5E0000000000)        /* 47 GCLK */
#define BLK_ADJ__46                        (0x5C0000000000)        /* 46 GCLK */
#define BLK_ADJ__45                        (0x5A0000000000)        /* 45 GCLK */
#define BLK_ADJ__44                        (0x580000000000)        /* 44 GCLK */
#define BLK_ADJ__43                        (0x560000000000)        /* 43 GCLK */
#define BLK_ADJ__42                        (0x540000000000)        /* 42 GCLK */
#define BLK_ADJ__41                        (0x520000000000)        /* 41 GCLK */
#define BLK_ADJ__40                        (0x500000000000)        /* 40 GCLK */
#define BLK_ADJ__39                        (0x4E0000000000)        /* 39 GCLK */
#define BLK_ADJ__38                        (0x4C0000000000)        /* 38 GCLK */
#define BLK_ADJ__37                        (0x4A0000000000)        /* 37 GCLK */
#define BLK_ADJ__36                        (0x480000000000)        /* 36 GCLK */
#define BLK_ADJ__35                        (0x460000000000)        /* 35 GCLK */
#define BLK_ADJ__34                        (0x440000000000)        /* 34 GCLK */
#define BLK_ADJ__33                        (0x420000000000)        /* 33 GCLK */
#define BLK_ADJ__32                        (0x400000000000)        /* 32 GCLK */
#define BLK_ADJ__31                        (0x3E0000000000)        /* 31 GCLK */
#define BLK_ADJ__30                        (0x3C0000000000)        /* 30 GCLK */
#define BLK_ADJ__29                        (0x3A0000000000)        /* 29 GCLK */
#define BLK_ADJ__28                        (0x380000000000)        /* 28 GCLK */
#define BLK_ADJ__27                        (0x360000000000)        /* 27 GCLK */
#define BLK_ADJ__26                        (0x340000000000)        /* 26 GCLK */
#define BLK_ADJ__25                        (0x320000000000)        /* 25 GCLK */
#define BLK_ADJ__24                        (0x300000000000)        /* 24 GCLK */
#define BLK_ADJ__23                        (0x2E0000000000)        /* 23 GCLK */
#define BLK_ADJ__22                        (0x2C0000000000)        /* 22 GCLK */
#define BLK_ADJ__21                        (0x2A0000000000)        /* 21 GCLK */
#define BLK_ADJ__20                        (0x280000000000)        /* 20 GCLK */
#define BLK_ADJ__19                        (0x260000000000)        /* 19 GCLK */
#define BLK_ADJ__18                        (0x240000000000)        /* 18 GCLK */
#define BLK_ADJ__17                        (0x220000000000)        /* 17 GCLK */
#define BLK_ADJ__16                        (0x200000000000)        /* 16 GCLK */
#define BLK_ADJ__15                        (0x1E0000000000)        /* 15 GCLK */
#define BLK_ADJ__14                        (0x1C0000000000)        /* 14 GCLK */
#define BLK_ADJ__13                        (0x1A0000000000)        /* 13 GCLK */
#define BLK_ADJ__12                        (0x180000000000)        /* 12 GCLK */
#define BLK_ADJ__11                        (0x160000000000)        /* 11 GCLK */
#define BLK_ADJ__10                        (0x140000000000)        /* 10 GCLK */
#define BLK_ADJ__9                         (0x120000000000)        /* 9 GCLK */
#define BLK_ADJ__8                         (0x100000000000)        /* 8 GCLK */
#define BLK_ADJ__7                         (0x0E0000000000)        /* 7 GCLK */
#define BLK_ADJ__6                         (0x0C0000000000)        /* 6 GCLK */
#define BLK_ADJ__5                         (0x0A0000000000)        /* 5 GCLK */
#define BLK_ADJ__4                         (0x080000000000)        /* 4 GCLK */
#define BLK_ADJ__3                         (0x060000000000)        /* 3 GCLK */
#define BLK_ADJ__2                         (0x040000000000)        /* 2 GCLK */
#define BLK_ADJ__1                         (0x020000000000)        /* 1 GCLK */
#define BLK_ADJ__0                         (0x000000000000)        /* 0 GCLK */
#define LINE_SWT__480                      (0x01E000000000)        /* 480 GCLK */
#define LINE_SWT__450                      (0x01C000000000)        /* 450 GCLK */
#define LINE_SWT__420                      (0x01A000000000)        /* 420 GCLK */
#define LINE_SWT__390                      (0x018000000000)        /* 390 GCLK */
#define LINE_SWT__360                      (0x016000000000)        /* 360 GCLK */
#define LINE_SWT__330                      (0x014000000000)        /* 330 GCLK */
#define LINE_SWT__300                      (0x012000000000)        /* 300 GCLK */
#define LINE_SWT__270                      (0x010000000000)        /* 270 GCLK */
#define LINE_SWT__240                      (0x00E000000000)        /* 240 GCLK */
#define LINE_SWT__210                      (0x00C000000000)        /* 210 GCLK */
#define LINE_SWT__180                      (0x00A000000000)        /* 180 GCLK */
#define LINE_SWT__150                      (0x008000000000)        /* 150 GCLK */
#define LINE_SWT__120                      (0x006000000000)        /* 120 GCLK */
#define LINE_SWT__90                       (0x004000000000)        /* 90 GCLK */
#define LINE_SWT__60                       (0x002000000000)        /* 60 GCLK */
#define LINE_SWT__45                       (0x000000000000)        /* 45 GCLK */
#define LINE_SWT_15                        (0x01E000000000)        /* 480 GCLK */
#define LINE_SWT_14                        (0x01C000000000)        /* 450 GCLK */
#define LINE_SWT_13                        (0x01A000000000)        /* 420 GCLK */
#define LINE_SWT_12                        (0x018000000000)        /* 390 GCLK */
#define LINE_SWT_11                        (0x016000000000)        /* 360 GCLK */
#define LINE_SWT_10                        (0x014000000000)        /* 330 GCLK */
#define LINE_SWT_9                         (0x012000000000)        /* 300 GCLK */
#define LINE_SWT_8                         (0x010000000000)        /* 270 GCLK */
#define LINE_SWT_7                         (0x00E000000000)        /* 240 GCLK */
#define LINE_SWT_6                         (0x00C000000000)        /* 210 GCLK */
#define LINE_SWT_5                         (0x00A000000000)        /* 180 GCLK */
#define LINE_SWT_4                         (0x008000000000)        /* 150 GCLK */
#define LINE_SWT_3                         (0x006000000000)        /* 120 GCLK */
#define LINE_SWT_2                         (0x004000000000)        /* 90 GCLK */
#define LINE_SWT_1                         (0x002000000000)        /* 60 GCLK */
#define LINE_SWT_0                         (0x000000000000)        /* 45 GCLK */
#define LG_ENH_B_15                        (0x001E00000000)        /* 15 */
#define LG_ENH_B_14                        (0x001C00000000)        /* 14 */
#define LG_ENH_B_13                        (0x001A00000000)        /* 13 */
#define LG_ENH_B_12                        (0x001800000000)        /* 12 */
#define LG_ENH_B_11                        (0x001600000000)        /* 11 */
#define LG_ENH_B_10                        (0x001400000000)        /* 10 */
#define LG_ENH_B_9                         (0x001200000000)        /* 9 */
#define LG_ENH_B_8                         (0x001000000000)        /* 8 */
#define LG_ENH_B_7                         (0x000E00000000)        /* 7 */
#define LG_ENH_B_6                         (0x000C00000000)        /* 6 */
#define LG_ENH_B_5                         (0x000A00000000)        /* 5 */
#define LG_ENH_B_4                         (0x000800000000)        /* 4 */
#define LG_ENH_B_3                         (0x000600000000)        /* 3 */
#define LG_ENH_B_2                         (0x000400000000)        /* 2 */
#define LG_ENH_B_1                         (0x000200000000)        /* 1 */
#define LG_ENH_B_0                         (0x000000000000)        /* 0 */
#define LG_ENH_B__15                       (0x001E00000000)        /* 15 */
#define LG_ENH_B__14                       (0x001C00000000)        /* 14 */
#define LG_ENH_B__13                       (0x001A00000000)        /* 13 */
#define LG_ENH_B__12                       (0x001800000000)        /* 12 */
#define LG_ENH_B__11                       (0x001600000000)        /* 11 */
#define LG_ENH_B__10                       (0x001400000000)        /* 10 */
#define LG_ENH_B__9                        (0x001200000000)        /* 9 */
#define LG_ENH_B__8                        (0x001000000000)        /* 8 */
#define LG_ENH_B__7                        (0x000E00000000)        /* 7 */
#define LG_ENH_B__6                        (0x000C00000000)        /* 6 */
#define LG_ENH_B__5                        (0x000A00000000)        /* 5 */
#define LG_ENH_B__4                        (0x000800000000)        /* 4 */
#define LG_ENH_B__3                        (0x000600000000)        /* 3 */
#define LG_ENH_B__2                        (0x000400000000)        /* 2 */
#define LG_ENH_B__1                        (0x000200000000)        /* 1 */
#define LG_ENH_B__0                        (0x000000000000)        /* 0 */
#define LG_ENH_G_15                        (0x0001E0000000)        /* 15 */
#define LG_ENH_G_14                        (0x0001C0000000)        /* 14 */
#define LG_ENH_G_13                        (0x0001A0000000)        /* 13 */
#define LG_ENH_G_12                        (0x000180000000)        /* 12 */
#define LG_ENH_G_11                        (0x000160000000)        /* 11 */
#define LG_ENH_G_10                        (0x000140000000)        /* 10 */
#define LG_ENH_G_9                         (0x000120000000)        /* 9 */
#define LG_ENH_G_8                         (0x000100000000)        /* 8 */
#define LG_ENH_G_7                         (0x0000E0000000)        /* 7 */
#define LG_ENH_G_6                         (0x0000C0000000)        /* 6 */
#define LG_ENH_G_5                         (0x0000A0000000)        /* 5 */
#define LG_ENH_G_4                         (0x000080000000)        /* 4 */
#define LG_ENH_G_3                         (0x000060000000)        /* 3 */
#define LG_ENH_G_2                         (0x000040000000)        /* 2 */
#define LG_ENH_G_1                         (0x000020000000)        /* 1 */
#define LG_ENH_G_0                         (0x000000000000)        /* 0 */
#define LG_ENH_G__15                       (0x0001E0000000)        /* 15 */
#define LG_ENH_G__14                       (0x0001C0000000)        /* 14 */
#define LG_ENH_G__13                       (0x0001A0000000)        /* 13 */
#define LG_ENH_G__12                       (0x000180000000)        /* 12 */
#define LG_ENH_G__11                       (0x000160000000)        /* 11 */
#define LG_ENH_G__10                       (0x000140000000)        /* 10 */
#define LG_ENH_G__9                        (0x000120000000)        /* 9 */
#define LG_ENH_G__8                        (0x000100000000)        /* 8 */
#define LG_ENH_G__7                        (0x0000E0000000)        /* 7 */
#define LG_ENH_G__6                        (0x0000C0000000)        /* 6 */
#define LG_ENH_G__5                        (0x0000A0000000)        /* 5 */
#define LG_ENH_G__4                        (0x000080000000)        /* 4 */
#define LG_ENH_G__3                        (0x000060000000)        /* 3 */
#define LG_ENH_G__2                        (0x000040000000)        /* 2 */
#define LG_ENH_G__1                        (0x000020000000)        /* 1 */
#define LG_ENH_G__0                        (0x000000000000)        /* 0 */
#define LG_ENH_R_15                        (0x00001E000000)        /* 15 */
#define LG_ENH_R_14                        (0x00001C000000)        /* 14 */
#define LG_ENH_R_13                        (0x00001A000000)        /* 13 */
#define LG_ENH_R_12                        (0x000018000000)        /* 12 */
#define LG_ENH_R_11                        (0x000016000000)        /* 11 */
#define LG_ENH_R_10                        (0x000014000000)        /* 10 */
#define LG_ENH_R_9                         (0x000012000000)        /* 9 */
#define LG_ENH_R_8                         (0x000010000000)        /* 8 */
#define LG_ENH_R_7                         (0x00000E000000)        /* 7 */
#define LG_ENH_R_6                         (0x00000C000000)        /* 6 */
#define LG_ENH_R_5                         (0x00000A000000)        /* 5 */
#define LG_ENH_R_4                         (0x000008000000)        /* 4 */
#define LG_ENH_R_3                         (0x000006000000)        /* 3 */
#define LG_ENH_R_2                         (0x000004000000)        /* 2 */
#define LG_ENH_R_1                         (0x000002000000)        /* 1 */
#define LG_ENH_R_0                         (0x000000000000)        /* 0 */
#define LG_ENH_R__15                       (0x00001E000000)        /* 15 */
#define LG_ENH_R__14                       (0x00001C000000)        /* 14 */
#define LG_ENH_R__13                       (0x00001A000000)        /* 13 */
#define LG_ENH_R__12                       (0x000018000000)        /* 12 */
#define LG_ENH_R__11                       (0x000016000000)        /* 11 */
#define LG_ENH_R__10                       (0x000014000000)        /* 10 */
#define LG_ENH_R__9                        (0x000012000000)        /* 9 */
#define LG_ENH_R__8                        (0x000010000000)        /* 8 */
#define LG_ENH_R__7                        (0x00000E000000)        /* 7 */
#define LG_ENH_R__6                        (0x00000C000000)        /* 6 */
#define LG_ENH_R__5                        (0x00000A000000)        /* 5 */
#define LG_ENH_R__4                        (0x000008000000)        /* 4 */
#define LG_ENH_R__3                        (0x000006000000)        /* 3 */
#define LG_ENH_R__2                        (0x000004000000)        /* 2 */
#define LG_ENH_R__1                        (0x000002000000)        /* 1 */
#define LG_ENH_R__0                        (0x000000000000)        /* 0 */
#define LG_STEP_B__32                      (0x000001F00000)        /* 32 */
#define LG_STEP_B__31                      (0x000001E00000)        /* 31 */
#define LG_STEP_B__30                      (0x000001D00000)        /* 30 */
#define LG_STEP_B__29                      (0x000001C00000)        /* 29 */
#define LG_STEP_B__28                      (0x000001B00000)        /* 28 */
#define LG_STEP_B__27                      (0x000001A00000)        /* 27 */
#define LG_STEP_B__26                      (0x000001900000)        /* 26 */
#define LG_STEP_B__25                      (0x000001800000)        /* 25 */
#define LG_STEP_B__24                      (0x000001700000)        /* 24 */
#define LG_STEP_B__23                      (0x000001600000)        /* 23 */
#define LG_STEP_B__22                      (0x000001500000)        /* 22 */
#define LG_STEP_B__21                      (0x000001400000)        /* 21 */
#define LG_STEP_B__20                      (0x000001300000)        /* 20 */
#define LG_STEP_B__19                      (0x000001200000)        /* 19 */
#define LG_STEP_B__18                      (0x000001100000)        /* 18 */
#define LG_STEP_B__17                      (0x000001000000)        /* 17 */
#define LG_STEP_B__16                      (0x000000F00000)        /* 16 */
#define LG_STEP_B__15                      (0x000000E00000)        /* 15 */
#define LG_STEP_B__14                      (0x000000D00000)        /* 14 */
#define LG_STEP_B__13                      (0x000000C00000)        /* 13 */
#define LG_STEP_B__12                      (0x000000B00000)        /* 12 */
#define LG_STEP_B__11                      (0x000000A00000)        /* 11 */
#define LG_STEP_B__10                      (0x000000900000)        /* 10 */
#define LG_STEP_B__9                       (0x000000800000)        /* 9 */
#define LG_STEP_B__8                       (0x000000700000)        /* 8 */
#define LG_STEP_B__7                       (0x000000600000)        /* 7 */
#define LG_STEP_B__6                       (0x000000500000)        /* 6 */
#define LG_STEP_B__5                       (0x000000400000)        /* 5 */
#define LG_STEP_B__4                       (0x000000300000)        /* 4 */
#define LG_STEP_B__3                       (0x000000200000)        /* 3 */
#define LG_STEP_B__2                       (0x000000100000)        /* 2 */
#define LG_STEP_B__1                       (0x000000000000)        /* 1 */
#define LG_STEP_G__32                      (0x0000000F8000)        /* 32 */
#define LG_STEP_G__31                      (0x0000000F0000)        /* 31 */
#define LG_STEP_G__30                      (0x0000000E8000)        /* 30 */
#define LG_STEP_G__29                      (0x0000000E0000)        /* 29 */
#define LG_STEP_G__28                      (0x0000000D8000)        /* 28 */
#define LG_STEP_G__27                      (0x0000000D0000)        /* 27 */
#define LG_STEP_G__26                      (0x0000000C8000)        /* 26 */
#define LG_STEP_G__25                      (0x0000000C0000)        /* 25 */
#define LG_STEP_G__24                      (0x0000000B8000)        /* 24 */
#define LG_STEP_G__23                      (0x0000000B0000)        /* 23 */
#define LG_STEP_G__22                      (0x0000000A8000)        /* 22 */
#define LG_STEP_G__21                      (0x0000000A0000)        /* 21 */
#define LG_STEP_G__20                      (0x000000098000)        /* 20 */
#define LG_STEP_G__19                      (0x000000090000)        /* 19 */
#define LG_STEP_G__18                      (0x000000088000)        /* 18 */
#define LG_STEP_G__17                      (0x000000080000)        /* 17 */
#define LG_STEP_G__16                      (0x000000078000)        /* 16 */
#define LG_STEP_G__15                      (0x000000070000)        /* 15 */
#define LG_STEP_G__14                      (0x000000068000)        /* 14 */
#define LG_STEP_G__13                      (0x000000060000)        /* 13 */
#define LG_STEP_G__12                      (0x000000058000)        /* 12 */
#define LG_STEP_G__11                      (0x000000050000)        /* 11 */
#define LG_STEP_G__10                      (0x000000048000)        /* 10 */
#define LG_STEP_G__9                       (0x000000040000)        /* 9 */
#define LG_STEP_G__8                       (0x000000038000)        /* 8 */
#define LG_STEP_G__7                       (0x000000030000)        /* 7 */
#define LG_STEP_G__6                       (0x000000028000)        /* 6 */
#define LG_STEP_G__5                       (0x000000020000)        /* 5 */
#define LG_STEP_G__4                       (0x000000018000)        /* 4 */
#define LG_STEP_G__3                       (0x000000010000)        /* 3 */
#define LG_STEP_G__2                       (0x000000008000)        /* 2 */
#define LG_STEP_G__1                       (0x000000000000)        /* 1 */
#define LG_STEP_R__32                      (0x000000007C00)        /* 32 */
#define LG_STEP_R__31                      (0x000000007800)        /* 31 */
#define LG_STEP_R__30                      (0x000000007400)        /* 30 */
#define LG_STEP_R__29                      (0x000000007000)        /* 29 */
#define LG_STEP_R__28                      (0x000000006C00)        /* 28 */
#define LG_STEP_R__27                      (0x000000006800)        /* 27 */
#define LG_STEP_R__26                      (0x000000006400)        /* 26 */
#define LG_STEP_R__25                      (0x000000006000)        /* 25 */
#define LG_STEP_R__24                      (0x000000005C00)        /* 24 */
#define LG_STEP_R__23                      (0x000000005800)        /* 23 */
#define LG_STEP_R__22                      (0x000000005400)        /* 22 */
#define LG_STEP_R__21                      (0x000000005000)        /* 21 */
#define LG_STEP_R__20                      (0x000000004C00)        /* 20 */
#define LG_STEP_R__19                      (0x000000004800)        /* 19 */
#define LG_STEP_R__18                      (0x000000004400)        /* 18 */
#define LG_STEP_R__17                      (0x000000004000)        /* 17 */
#define LG_STEP_R__16                      (0x000000003C00)        /* 16 */
#define LG_STEP_R__15                      (0x000000003800)        /* 15 */
#define LG_STEP_R__14                      (0x000000003400)        /* 14 */
#define LG_STEP_R__13                      (0x000000003000)        /* 13 */
#define LG_STEP_R__12                      (0x000000002C00)        /* 12 */
#define LG_STEP_R__11                      (0x000000002800)        /* 11 */
#define LG_STEP_R__10                      (0x000000002400)        /* 10 */
#define LG_STEP_R__9                       (0x000000002000)        /* 9 */
#define LG_STEP_R__8                       (0x000000001C00)        /* 8 */
#define LG_STEP_R__7                       (0x000000001800)        /* 7 */
#define LG_STEP_R__6                       (0x000000001400)        /* 6 */
#define LG_STEP_R__5                       (0x000000001000)        /* 5 */
#define LG_STEP_R__4                       (0x000000000C00)        /* 4 */
#define LG_STEP_R__3                       (0x000000000800)        /* 3 */
#define LG_STEP_R__2                       (0x000000000400)        /* 2 */
#define LG_STEP_R__1                       (0x000000000000)        /* 1 */
#define SEG_LENGTH__1024                   (0x0000000003FF)        /* 1024 GCLK */
#define SEG_LENGTH__1023                   (0x0000000003FE)        /* 1023 GCLK */
#define SEG_LENGTH__1022                   (0x0000000003FD)        /* 1022 GCLK */
#define SEG_LENGTH__1021                   (0x0000000003FC)        /* 1021 GCLK */
#define SEG_LENGTH__1020                   (0x0000000003FB)        /* 1020 GCLK */
#define SEG_LENGTH__1019                   (0x0000000003FA)        /* 1019 GCLK */
#define SEG_LENGTH__1018                   (0x0000000003F9)        /* 1018 GCLK */
#define SEG_LENGTH__1017                   (0x0000000003F8)        /* 1017 GCLK */
#define SEG_LENGTH__1016                   (0x0000000003F7)        /* 1016 GCLK */
#define SEG_LENGTH__1015                   (0x0000000003F6)        /* 1015 GCLK */
#define SEG_LENGTH__1014                   (0x0000000003F5)        /* 1014 GCLK */
#define SEG_LENGTH__1013                   (0x0000000003F4)        /* 1013 GCLK */
#define SEG_LENGTH__1012                   (0x0000000003F3)        /* 1012 GCLK */
#define SEG_LENGTH__1011                   (0x0000000003F2)        /* 1011 GCLK */
#define SEG_LENGTH__1010                   (0x0000000003F1)        /* 1010 GCLK */
#define SEG_LENGTH__1009                   (0x0000000003F0)        /* 1009 GCLK */
#define SEG_LENGTH__1008                   (0x0000000003EF)        /* 1008 GCLK */
#define SEG_LENGTH__1007                   (0x0000000003EE)        /* 1007 GCLK */
#define SEG_LENGTH__1006                   (0x0000000003ED)        /* 1006 GCLK */
#define SEG_LENGTH__1005                   (0x0000000003EC)        /* 1005 GCLK */
#define SEG_LENGTH__1004                   (0x0000000003EB)        /* 1004 GCLK */
#define SEG_LENGTH__1003                   (0x0000000003EA)        /* 1003 GCLK */
#define SEG_LENGTH__1002                   (0x0000000003E9)        /* 1002 GCLK */
#define SEG_LENGTH__1001                   (0x0000000003E8)        /* 1001 GCLK */
#define SEG_LENGTH__1000                   (0x0000000003E7)        /* 1000 GCLK */
#define SEG_LENGTH__999                    (0x0000000003E6)        /* 999 GCLK */
#define SEG_LENGTH__998                    (0x0000000003E5)        /* 998 GCLK */
#define SEG_LENGTH__997                    (0x0000000003E4)        /* 997 GCLK */
#define SEG_LENGTH__996                    (0x0000000003E3)        /* 996 GCLK */
#define SEG_LENGTH__995                    (0x0000000003E2)        /* 995 GCLK */
#define SEG_LENGTH__994                    (0x0000000003E1)        /* 994 GCLK */
#define SEG_LENGTH__993                    (0x0000000003E0)        /* 993 GCLK */
#define SEG_LENGTH__992                    (0x0000000003DF)        /* 992 GCLK */
#define SEG_LENGTH__991                    (0x0000000003DE)        /* 991 GCLK */
#define SEG_LENGTH__990                    (0x0000000003DD)        /* 990 GCLK */
#define SEG_LENGTH__989                    (0x0000000003DC)        /* 989 GCLK */
#define SEG_LENGTH__988                    (0x0000000003DB)        /* 988 GCLK */
#define SEG_LENGTH__987                    (0x0000000003DA)        /* 987 GCLK */
#define SEG_LENGTH__986                    (0x0000000003D9)        /* 986 GCLK */
#define SEG_LENGTH__985                    (0x0000000003D8)        /* 985 GCLK */
#define SEG_LENGTH__984                    (0x0000000003D7)        /* 984 GCLK */
#define SEG_LENGTH__983                    (0x0000000003D6)        /* 983 GCLK */
#define SEG_LENGTH__982                    (0x0000000003D5)        /* 982 GCLK */
#define SEG_LENGTH__981                    (0x0000000003D4)        /* 981 GCLK */
#define SEG_LENGTH__980                    (0x0000000003D3)        /* 980 GCLK */
#define SEG_LENGTH__979                    (0x0000000003D2)        /* 979 GCLK */
#define SEG_LENGTH__978                    (0x0000000003D1)        /* 978 GCLK */
#define SEG_LENGTH__977                    (0x0000000003D0)        /* 977 GCLK */
#define SEG_LENGTH__976                    (0x0000000003CF)        /* 976 GCLK */
#define SEG_LENGTH__975                    (0x0000000003CE)        /* 975 GCLK */
#define SEG_LENGTH__974                    (0x0000000003CD)        /* 974 GCLK */
#define SEG_LENGTH__973                    (0x0000000003CC)        /* 973 GCLK */
#define SEG_LENGTH__972                    (0x0000000003CB)        /* 972 GCLK */
#define SEG_LENGTH__971                    (0x0000000003CA)        /* 971 GCLK */
#define SEG_LENGTH__970                    (0x0000000003C9)        /* 970 GCLK */
#define SEG_LENGTH__969                    (0x0000000003C8)        /* 969 GCLK */
#define SEG_LENGTH__968                    (0x0000000003C7)        /* 968 GCLK */
#define SEG_LENGTH__967                    (0x0000000003C6)        /* 967 GCLK */
#define SEG_LENGTH__966                    (0x0000000003C5)        /* 966 GCLK */
#define SEG_LENGTH__965                    (0x0000000003C4)        /* 965 GCLK */
#define SEG_LENGTH__964                    (0x0000000003C3)        /* 964 GCLK */
#define SEG_LENGTH__963                    (0x0000000003C2)        /* 963 GCLK */
#define SEG_LENGTH__962                    (0x0000000003C1)        /* 962 GCLK */
#define SEG_LENGTH__961                    (0x0000000003C0)        /* 961 GCLK */
#define SEG_LENGTH__960                    (0x0000000003BF)        /* 960 GCLK */
#define SEG_LENGTH__959                    (0x0000000003BE)        /* 959 GCLK */
#define SEG_LENGTH__958                    (0x0000000003BD)        /* 958 GCLK */
#define SEG_LENGTH__957                    (0x0000000003BC)        /* 957 GCLK */
#define SEG_LENGTH__956                    (0x0000000003BB)        /* 956 GCLK */
#define SEG_LENGTH__955                    (0x0000000003BA)        /* 955 GCLK */
#define SEG_LENGTH__954                    (0x0000000003B9)        /* 954 GCLK */
#define SEG_LENGTH__953                    (0x0000000003B8)        /* 953 GCLK */
#define SEG_LENGTH__952                    (0x0000000003B7)        /* 952 GCLK */
#define SEG_LENGTH__951                    (0x0000000003B6)        /* 951 GCLK */
#define SEG_LENGTH__950                    (0x0000000003B5)        /* 950 GCLK */
#define SEG_LENGTH__949                    (0x0000000003B4)        /* 949 GCLK */
#define SEG_LENGTH__948                    (0x0000000003B3)        /* 948 GCLK */
#define SEG_LENGTH__947                    (0x0000000003B2)        /* 947 GCLK */
#define SEG_LENGTH__946                    (0x0000000003B1)        /* 946 GCLK */
#define SEG_LENGTH__945                    (0x0000000003B0)        /* 945 GCLK */
#define SEG_LENGTH__944                    (0x0000000003AF)        /* 944 GCLK */
#define SEG_LENGTH__943                    (0x0000000003AE)        /* 943 GCLK */
#define SEG_LENGTH__942                    (0x0000000003AD)        /* 942 GCLK */
#define SEG_LENGTH__941                    (0x0000000003AC)        /* 941 GCLK */
#define SEG_LENGTH__940                    (0x0000000003AB)        /* 940 GCLK */
#define SEG_LENGTH__939                    (0x0000000003AA)        /* 939 GCLK */
#define SEG_LENGTH__938                    (0x0000000003A9)        /* 938 GCLK */
#define SEG_LENGTH__937                    (0x0000000003A8)        /* 937 GCLK */
#define SEG_LENGTH__936                    (0x0000000003A7)        /* 936 GCLK */
#define SEG_LENGTH__935                    (0x0000000003A6)        /* 935 GCLK */
#define SEG_LENGTH__934                    (0x0000000003A5)        /* 934 GCLK */
#define SEG_LENGTH__933                    (0x0000000003A4)        /* 933 GCLK */
#define SEG_LENGTH__932                    (0x0000000003A3)        /* 932 GCLK */
#define SEG_LENGTH__931                    (0x0000000003A2)        /* 931 GCLK */
#define SEG_LENGTH__930                    (0x0000000003A1)        /* 930 GCLK */
#define SEG_LENGTH__929                    (0x0000000003A0)        /* 929 GCLK */
#define SEG_LENGTH__928                    (0x00000000039F)        /* 928 GCLK */
#define SEG_LENGTH__927                    (0x00000000039E)        /* 927 GCLK */
#define SEG_LENGTH__926                    (0x00000000039D)        /* 926 GCLK */
#define SEG_LENGTH__925                    (0x00000000039C)        /* 925 GCLK */
#define SEG_LENGTH__924                    (0x00000000039B)        /* 924 GCLK */
#define SEG_LENGTH__923                    (0x00000000039A)        /* 923 GCLK */
#define SEG_LENGTH__922                    (0x000000000399)        /* 922 GCLK */
#define SEG_LENGTH__921                    (0x000000000398)        /* 921 GCLK */
#define SEG_LENGTH__920                    (0x000000000397)        /* 920 GCLK */
#define SEG_LENGTH__919                    (0x000000000396)        /* 919 GCLK */
#define SEG_LENGTH__918                    (0x000000000395)        /* 918 GCLK */
#define SEG_LENGTH__917                    (0x000000000394)        /* 917 GCLK */
#define SEG_LENGTH__916                    (0x000000000393)        /* 916 GCLK */
#define SEG_LENGTH__915                    (0x000000000392)        /* 915 GCLK */
#define SEG_LENGTH__914                    (0x000000000391)        /* 914 GCLK */
#define SEG_LENGTH__913                    (0x000000000390)        /* 913 GCLK */
#define SEG_LENGTH__912                    (0x00000000038F)        /* 912 GCLK */
#define SEG_LENGTH__911                    (0x00000000038E)        /* 911 GCLK */
#define SEG_LENGTH__910                    (0x00000000038D)        /* 910 GCLK */
#define SEG_LENGTH__909                    (0x00000000038C)        /* 909 GCLK */
#define SEG_LENGTH__908                    (0x00000000038B)        /* 908 GCLK */
#define SEG_LENGTH__907                    (0x00000000038A)        /* 907 GCLK */
#define SEG_LENGTH__906                    (0x000000000389)        /* 906 GCLK */
#define SEG_LENGTH__905                    (0x000000000388)        /* 905 GCLK */
#define SEG_LENGTH__904                    (0x000000000387)        /* 904 GCLK */
#define SEG_LENGTH__903                    (0x000000000386)        /* 903 GCLK */
#define SEG_LENGTH__902                    (0x000000000385)        /* 902 GCLK */
#define SEG_LENGTH__901                    (0x000000000384)        /* 901 GCLK */
#define SEG_LENGTH__900                    (0x000000000383)        /* 900 GCLK */
#define SEG_LENGTH__899                    (0x000000000382)        /* 899 GCLK */
#define SEG_LENGTH__898                    (0x000000000381)        /* 898 GCLK */
#define SEG_LENGTH__897                    (0x000000000380)        /* 897 GCLK */
#define SEG_LENGTH__896                    (0x00000000037F)        /* 896 GCLK */
#define SEG_LENGTH__895                    (0x00000000037E)        /* 895 GCLK */
#define SEG_LENGTH__894                    (0x00000000037D)        /* 894 GCLK */
#define SEG_LENGTH__893                    (0x00000000037C)        /* 893 GCLK */
#define SEG_LENGTH__892                    (0x00000000037B)        /* 892 GCLK */
#define SEG_LENGTH__891                    (0x00000000037A)        /* 891 GCLK */
#define SEG_LENGTH__890                    (0x000000000379)        /* 890 GCLK */
#define SEG_LENGTH__889                    (0x000000000378)        /* 889 GCLK */
#define SEG_LENGTH__888                    (0x000000000377)        /* 888 GCLK */
#define SEG_LENGTH__887                    (0x000000000376)        /* 887 GCLK */
#define SEG_LENGTH__886                    (0x000000000375)        /* 886 GCLK */
#define SEG_LENGTH__885                    (0x000000000374)        /* 885 GCLK */
#define SEG_LENGTH__884                    (0x000000000373)        /* 884 GCLK */
#define SEG_LENGTH__883                    (0x000000000372)        /* 883 GCLK */
#define SEG_LENGTH__882                    (0x000000000371)        /* 882 GCLK */
#define SEG_LENGTH__881                    (0x000000000370)        /* 881 GCLK */
#define SEG_LENGTH__880                    (0x00000000036F)        /* 880 GCLK */
#define SEG_LENGTH__879                    (0x00000000036E)        /* 879 GCLK */
#define SEG_LENGTH__878                    (0x00000000036D)        /* 878 GCLK */
#define SEG_LENGTH__877                    (0x00000000036C)        /* 877 GCLK */
#define SEG_LENGTH__876                    (0x00000000036B)        /* 876 GCLK */
#define SEG_LENGTH__875                    (0x00000000036A)        /* 875 GCLK */
#define SEG_LENGTH__874                    (0x000000000369)        /* 874 GCLK */
#define SEG_LENGTH__873                    (0x000000000368)        /* 873 GCLK */
#define SEG_LENGTH__872                    (0x000000000367)        /* 872 GCLK */
#define SEG_LENGTH__871                    (0x000000000366)        /* 871 GCLK */
#define SEG_LENGTH__870                    (0x000000000365)        /* 870 GCLK */
#define SEG_LENGTH__869                    (0x000000000364)        /* 869 GCLK */
#define SEG_LENGTH__868                    (0x000000000363)        /* 868 GCLK */
#define SEG_LENGTH__867                    (0x000000000362)        /* 867 GCLK */
#define SEG_LENGTH__866                    (0x000000000361)        /* 866 GCLK */
#define SEG_LENGTH__865                    (0x000000000360)        /* 865 GCLK */
#define SEG_LENGTH__864                    (0x00000000035F)        /* 864 GCLK */
#define SEG_LENGTH__863                    (0x00000000035E)        /* 863 GCLK */
#define SEG_LENGTH__862                    (0x00000000035D)        /* 862 GCLK */
#define SEG_LENGTH__861                    (0x00000000035C)        /* 861 GCLK */
#define SEG_LENGTH__860                    (0x00000000035B)        /* 860 GCLK */
#define SEG_LENGTH__859                    (0x00000000035A)        /* 859 GCLK */
#define SEG_LENGTH__858                    (0x000000000359)        /* 858 GCLK */
#define SEG_LENGTH__857                    (0x000000000358)        /* 857 GCLK */
#define SEG_LENGTH__856                    (0x000000000357)        /* 856 GCLK */
#define SEG_LENGTH__855                    (0x000000000356)        /* 855 GCLK */
#define SEG_LENGTH__854                    (0x000000000355)        /* 854 GCLK */
#define SEG_LENGTH__853                    (0x000000000354)        /* 853 GCLK */
#define SEG_LENGTH__852                    (0x000000000353)        /* 852 GCLK */
#define SEG_LENGTH__851                    (0x000000000352)        /* 851 GCLK */
#define SEG_LENGTH__850                    (0x000000000351)        /* 850 GCLK */
#define SEG_LENGTH__849                    (0x000000000350)        /* 849 GCLK */
#define SEG_LENGTH__848                    (0x00000000034F)        /* 848 GCLK */
#define SEG_LENGTH__847                    (0x00000000034E)        /* 847 GCLK */
#define SEG_LENGTH__846                    (0x00000000034D)        /* 846 GCLK */
#define SEG_LENGTH__845                    (0x00000000034C)        /* 845 GCLK */
#define SEG_LENGTH__844                    (0x00000000034B)        /* 844 GCLK */
#define SEG_LENGTH__843                    (0x00000000034A)        /* 843 GCLK */
#define SEG_LENGTH__842                    (0x000000000349)        /* 842 GCLK */
#define SEG_LENGTH__841                    (0x000000000348)        /* 841 GCLK */
#define SEG_LENGTH__840                    (0x000000000347)        /* 840 GCLK */
#define SEG_LENGTH__839                    (0x000000000346)        /* 839 GCLK */
#define SEG_LENGTH__838                    (0x000000000345)        /* 838 GCLK */
#define SEG_LENGTH__837                    (0x000000000344)        /* 837 GCLK */
#define SEG_LENGTH__836                    (0x000000000343)        /* 836 GCLK */
#define SEG_LENGTH__835                    (0x000000000342)        /* 835 GCLK */
#define SEG_LENGTH__834                    (0x000000000341)        /* 834 GCLK */
#define SEG_LENGTH__833                    (0x000000000340)        /* 833 GCLK */
#define SEG_LENGTH__832                    (0x00000000033F)        /* 832 GCLK */
#define SEG_LENGTH__831                    (0x00000000033E)        /* 831 GCLK */
#define SEG_LENGTH__830                    (0x00000000033D)        /* 830 GCLK */
#define SEG_LENGTH__829                    (0x00000000033C)        /* 829 GCLK */
#define SEG_LENGTH__828                    (0x00000000033B)        /* 828 GCLK */
#define SEG_LENGTH__827                    (0x00000000033A)        /* 827 GCLK */
#define SEG_LENGTH__826                    (0x000000000339)        /* 826 GCLK */
#define SEG_LENGTH__825                    (0x000000000338)        /* 825 GCLK */
#define SEG_LENGTH__824                    (0x000000000337)        /* 824 GCLK */
#define SEG_LENGTH__823                    (0x000000000336)        /* 823 GCLK */
#define SEG_LENGTH__822                    (0x000000000335)        /* 822 GCLK */
#define SEG_LENGTH__821                    (0x000000000334)        /* 821 GCLK */
#define SEG_LENGTH__820                    (0x000000000333)        /* 820 GCLK */
#define SEG_LENGTH__819                    (0x000000000332)        /* 819 GCLK */
#define SEG_LENGTH__818                    (0x000000000331)        /* 818 GCLK */
#define SEG_LENGTH__817                    (0x000000000330)        /* 817 GCLK */
#define SEG_LENGTH__816                    (0x00000000032F)        /* 816 GCLK */
#define SEG_LENGTH__815                    (0x00000000032E)        /* 815 GCLK */
#define SEG_LENGTH__814                    (0x00000000032D)        /* 814 GCLK */
#define SEG_LENGTH__813                    (0x00000000032C)        /* 813 GCLK */
#define SEG_LENGTH__812                    (0x00000000032B)        /* 812 GCLK */
#define SEG_LENGTH__811                    (0x00000000032A)        /* 811 GCLK */
#define SEG_LENGTH__810                    (0x000000000329)        /* 810 GCLK */
#define SEG_LENGTH__809                    (0x000000000328)        /* 809 GCLK */
#define SEG_LENGTH__808                    (0x000000000327)        /* 808 GCLK */
#define SEG_LENGTH__807                    (0x000000000326)        /* 807 GCLK */
#define SEG_LENGTH__806                    (0x000000000325)        /* 806 GCLK */
#define SEG_LENGTH__805                    (0x000000000324)        /* 805 GCLK */
#define SEG_LENGTH__804                    (0x000000000323)        /* 804 GCLK */
#define SEG_LENGTH__803                    (0x000000000322)        /* 803 GCLK */
#define SEG_LENGTH__802                    (0x000000000321)        /* 802 GCLK */
#define SEG_LENGTH__801                    (0x000000000320)        /* 801 GCLK */
#define SEG_LENGTH__800                    (0x00000000031F)        /* 800 GCLK */
#define SEG_LENGTH__799                    (0x00000000031E)        /* 799 GCLK */
#define SEG_LENGTH__798                    (0x00000000031D)        /* 798 GCLK */
#define SEG_LENGTH__797                    (0x00000000031C)        /* 797 GCLK */
#define SEG_LENGTH__796                    (0x00000000031B)        /* 796 GCLK */
#define SEG_LENGTH__795                    (0x00000000031A)        /* 795 GCLK */
#define SEG_LENGTH__794                    (0x000000000319)        /* 794 GCLK */
#define SEG_LENGTH__793                    (0x000000000318)        /* 793 GCLK */
#define SEG_LENGTH__792                    (0x000000000317)        /* 792 GCLK */
#define SEG_LENGTH__791                    (0x000000000316)        /* 791 GCLK */
#define SEG_LENGTH__790                    (0x000000000315)        /* 790 GCLK */
#define SEG_LENGTH__789                    (0x000000000314)        /* 789 GCLK */
#define SEG_LENGTH__788                    (0x000000000313)        /* 788 GCLK */
#define SEG_LENGTH__787                    (0x000000000312)        /* 787 GCLK */
#define SEG_LENGTH__786                    (0x000000000311)        /* 786 GCLK */
#define SEG_LENGTH__785                    (0x000000000310)        /* 785 GCLK */
#define SEG_LENGTH__784                    (0x00000000030F)        /* 784 GCLK */
#define SEG_LENGTH__783                    (0x00000000030E)        /* 783 GCLK */
#define SEG_LENGTH__782                    (0x00000000030D)        /* 782 GCLK */
#define SEG_LENGTH__781                    (0x00000000030C)        /* 781 GCLK */
#define SEG_LENGTH__780                    (0x00000000030B)        /* 780 GCLK */
#define SEG_LENGTH__779                    (0x00000000030A)        /* 779 GCLK */
#define SEG_LENGTH__778                    (0x000000000309)        /* 778 GCLK */
#define SEG_LENGTH__777                    (0x000000000308)        /* 777 GCLK */
#define SEG_LENGTH__776                    (0x000000000307)        /* 776 GCLK */
#define SEG_LENGTH__775                    (0x000000000306)        /* 775 GCLK */
#define SEG_LENGTH__774                    (0x000000000305)        /* 774 GCLK */
#define SEG_LENGTH__773                    (0x000000000304)        /* 773 GCLK */
#define SEG_LENGTH__772                    (0x000000000303)        /* 772 GCLK */
#define SEG_LENGTH__771                    (0x000000000302)        /* 771 GCLK */
#define SEG_LENGTH__770                    (0x000000000301)        /* 770 GCLK */
#define SEG_LENGTH__769                    (0x000000000300)        /* 769 GCLK */
#define SEG_LENGTH__768                    (0x0000000002FF)        /* 768 GCLK */
#define SEG_LENGTH__767                    (0x0000000002FE)        /* 767 GCLK */
#define SEG_LENGTH__766                    (0x0000000002FD)        /* 766 GCLK */
#define SEG_LENGTH__765                    (0x0000000002FC)        /* 765 GCLK */
#define SEG_LENGTH__764                    (0x0000000002FB)        /* 764 GCLK */
#define SEG_LENGTH__763                    (0x0000000002FA)        /* 763 GCLK */
#define SEG_LENGTH__762                    (0x0000000002F9)        /* 762 GCLK */
#define SEG_LENGTH__761                    (0x0000000002F8)        /* 761 GCLK */
#define SEG_LENGTH__760                    (0x0000000002F7)        /* 760 GCLK */
#define SEG_LENGTH__759                    (0x0000000002F6)        /* 759 GCLK */
#define SEG_LENGTH__758                    (0x0000000002F5)        /* 758 GCLK */
#define SEG_LENGTH__757                    (0x0000000002F4)        /* 757 GCLK */
#define SEG_LENGTH__756                    (0x0000000002F3)        /* 756 GCLK */
#define SEG_LENGTH__755                    (0x0000000002F2)        /* 755 GCLK */
#define SEG_LENGTH__754                    (0x0000000002F1)        /* 754 GCLK */
#define SEG_LENGTH__753                    (0x0000000002F0)        /* 753 GCLK */
#define SEG_LENGTH__752                    (0x0000000002EF)        /* 752 GCLK */
#define SEG_LENGTH__751                    (0x0000000002EE)        /* 751 GCLK */
#define SEG_LENGTH__750                    (0x0000000002ED)        /* 750 GCLK */
#define SEG_LENGTH__749                    (0x0000000002EC)        /* 749 GCLK */
#define SEG_LENGTH__748                    (0x0000000002EB)        /* 748 GCLK */
#define SEG_LENGTH__747                    (0x0000000002EA)        /* 747 GCLK */
#define SEG_LENGTH__746                    (0x0000000002E9)        /* 746 GCLK */
#define SEG_LENGTH__745                    (0x0000000002E8)        /* 745 GCLK */
#define SEG_LENGTH__744                    (0x0000000002E7)        /* 744 GCLK */
#define SEG_LENGTH__743                    (0x0000000002E6)        /* 743 GCLK */
#define SEG_LENGTH__742                    (0x0000000002E5)        /* 742 GCLK */
#define SEG_LENGTH__741                    (0x0000000002E4)        /* 741 GCLK */
#define SEG_LENGTH__740                    (0x0000000002E3)        /* 740 GCLK */
#define SEG_LENGTH__739                    (0x0000000002E2)        /* 739 GCLK */
#define SEG_LENGTH__738                    (0x0000000002E1)        /* 738 GCLK */
#define SEG_LENGTH__737                    (0x0000000002E0)        /* 737 GCLK */
#define SEG_LENGTH__736                    (0x0000000002DF)        /* 736 GCLK */
#define SEG_LENGTH__735                    (0x0000000002DE)        /* 735 GCLK */
#define SEG_LENGTH__734                    (0x0000000002DD)        /* 734 GCLK */
#define SEG_LENGTH__733                    (0x0000000002DC)        /* 733 GCLK */
#define SEG_LENGTH__732                    (0x0000000002DB)        /* 732 GCLK */
#define SEG_LENGTH__731                    (0x0000000002DA)        /* 731 GCLK */
#define SEG_LENGTH__730                    (0x0000000002D9)        /* 730 GCLK */
#define SEG_LENGTH__729                    (0x0000000002D8)        /* 729 GCLK */
#define SEG_LENGTH__728                    (0x0000000002D7)        /* 728 GCLK */
#define SEG_LENGTH__727                    (0x0000000002D6)        /* 727 GCLK */
#define SEG_LENGTH__726                    (0x0000000002D5)        /* 726 GCLK */
#define SEG_LENGTH__725                    (0x0000000002D4)        /* 725 GCLK */
#define SEG_LENGTH__724                    (0x0000000002D3)        /* 724 GCLK */
#define SEG_LENGTH__723                    (0x0000000002D2)        /* 723 GCLK */
#define SEG_LENGTH__722                    (0x0000000002D1)        /* 722 GCLK */
#define SEG_LENGTH__721                    (0x0000000002D0)        /* 721 GCLK */
#define SEG_LENGTH__720                    (0x0000000002CF)        /* 720 GCLK */
#define SEG_LENGTH__719                    (0x0000000002CE)        /* 719 GCLK */
#define SEG_LENGTH__718                    (0x0000000002CD)        /* 718 GCLK */
#define SEG_LENGTH__717                    (0x0000000002CC)        /* 717 GCLK */
#define SEG_LENGTH__716                    (0x0000000002CB)        /* 716 GCLK */
#define SEG_LENGTH__715                    (0x0000000002CA)        /* 715 GCLK */
#define SEG_LENGTH__714                    (0x0000000002C9)        /* 714 GCLK */
#define SEG_LENGTH__713                    (0x0000000002C8)        /* 713 GCLK */
#define SEG_LENGTH__712                    (0x0000000002C7)        /* 712 GCLK */
#define SEG_LENGTH__711                    (0x0000000002C6)        /* 711 GCLK */
#define SEG_LENGTH__710                    (0x0000000002C5)        /* 710 GCLK */
#define SEG_LENGTH__709                    (0x0000000002C4)        /* 709 GCLK */
#define SEG_LENGTH__708                    (0x0000000002C3)        /* 708 GCLK */
#define SEG_LENGTH__707                    (0x0000000002C2)        /* 707 GCLK */
#define SEG_LENGTH__706                    (0x0000000002C1)        /* 706 GCLK */
#define SEG_LENGTH__705                    (0x0000000002C0)        /* 705 GCLK */
#define SEG_LENGTH__704                    (0x0000000002BF)        /* 704 GCLK */
#define SEG_LENGTH__703                    (0x0000000002BE)        /* 703 GCLK */
#define SEG_LENGTH__702                    (0x0000000002BD)        /* 702 GCLK */
#define SEG_LENGTH__701                    (0x0000000002BC)        /* 701 GCLK */
#define SEG_LENGTH__700                    (0x0000000002BB)        /* 700 GCLK */
#define SEG_LENGTH__699                    (0x0000000002BA)        /* 699 GCLK */
#define SEG_LENGTH__698                    (0x0000000002B9)        /* 698 GCLK */
#define SEG_LENGTH__697                    (0x0000000002B8)        /* 697 GCLK */
#define SEG_LENGTH__696                    (0x0000000002B7)        /* 696 GCLK */
#define SEG_LENGTH__695                    (0x0000000002B6)        /* 695 GCLK */
#define SEG_LENGTH__694                    (0x0000000002B5)        /* 694 GCLK */
#define SEG_LENGTH__693                    (0x0000000002B4)        /* 693 GCLK */
#define SEG_LENGTH__692                    (0x0000000002B3)        /* 692 GCLK */
#define SEG_LENGTH__691                    (0x0000000002B2)        /* 691 GCLK */
#define SEG_LENGTH__690                    (0x0000000002B1)        /* 690 GCLK */
#define SEG_LENGTH__689                    (0x0000000002B0)        /* 689 GCLK */
#define SEG_LENGTH__688                    (0x0000000002AF)        /* 688 GCLK */
#define SEG_LENGTH__687                    (0x0000000002AE)        /* 687 GCLK */
#define SEG_LENGTH__686                    (0x0000000002AD)        /* 686 GCLK */
#define SEG_LENGTH__685                    (0x0000000002AC)        /* 685 GCLK */
#define SEG_LENGTH__684                    (0x0000000002AB)        /* 684 GCLK */
#define SEG_LENGTH__683                    (0x0000000002AA)        /* 683 GCLK */
#define SEG_LENGTH__682                    (0x0000000002A9)        /* 682 GCLK */
#define SEG_LENGTH__681                    (0x0000000002A8)        /* 681 GCLK */
#define SEG_LENGTH__680                    (0x0000000002A7)        /* 680 GCLK */
#define SEG_LENGTH__679                    (0x0000000002A6)        /* 679 GCLK */
#define SEG_LENGTH__678                    (0x0000000002A5)        /* 678 GCLK */
#define SEG_LENGTH__677                    (0x0000000002A4)        /* 677 GCLK */
#define SEG_LENGTH__676                    (0x0000000002A3)        /* 676 GCLK */
#define SEG_LENGTH__675                    (0x0000000002A2)        /* 675 GCLK */
#define SEG_LENGTH__674                    (0x0000000002A1)        /* 674 GCLK */
#define SEG_LENGTH__673                    (0x0000000002A0)        /* 673 GCLK */
#define SEG_LENGTH__672                    (0x00000000029F)        /* 672 GCLK */
#define SEG_LENGTH__671                    (0x00000000029E)        /* 671 GCLK */
#define SEG_LENGTH__670                    (0x00000000029D)        /* 670 GCLK */
#define SEG_LENGTH__669                    (0x00000000029C)        /* 669 GCLK */
#define SEG_LENGTH__668                    (0x00000000029B)        /* 668 GCLK */
#define SEG_LENGTH__667                    (0x00000000029A)        /* 667 GCLK */
#define SEG_LENGTH__666                    (0x000000000299)        /* 666 GCLK */
#define SEG_LENGTH__665                    (0x000000000298)        /* 665 GCLK */
#define SEG_LENGTH__664                    (0x000000000297)        /* 664 GCLK */
#define SEG_LENGTH__663                    (0x000000000296)        /* 663 GCLK */
#define SEG_LENGTH__662                    (0x000000000295)        /* 662 GCLK */
#define SEG_LENGTH__661                    (0x000000000294)        /* 661 GCLK */
#define SEG_LENGTH__660                    (0x000000000293)        /* 660 GCLK */
#define SEG_LENGTH__659                    (0x000000000292)        /* 659 GCLK */
#define SEG_LENGTH__658                    (0x000000000291)        /* 658 GCLK */
#define SEG_LENGTH__657                    (0x000000000290)        /* 657 GCLK */
#define SEG_LENGTH__656                    (0x00000000028F)        /* 656 GCLK */
#define SEG_LENGTH__655                    (0x00000000028E)        /* 655 GCLK */
#define SEG_LENGTH__654                    (0x00000000028D)        /* 654 GCLK */
#define SEG_LENGTH__653                    (0x00000000028C)        /* 653 GCLK */
#define SEG_LENGTH__652                    (0x00000000028B)        /* 652 GCLK */
#define SEG_LENGTH__651                    (0x00000000028A)        /* 651 GCLK */
#define SEG_LENGTH__650                    (0x000000000289)        /* 650 GCLK */
#define SEG_LENGTH__649                    (0x000000000288)        /* 649 GCLK */
#define SEG_LENGTH__648                    (0x000000000287)        /* 648 GCLK */
#define SEG_LENGTH__647                    (0x000000000286)        /* 647 GCLK */
#define SEG_LENGTH__646                    (0x000000000285)        /* 646 GCLK */
#define SEG_LENGTH__645                    (0x000000000284)        /* 645 GCLK */
#define SEG_LENGTH__644                    (0x000000000283)        /* 644 GCLK */
#define SEG_LENGTH__643                    (0x000000000282)        /* 643 GCLK */
#define SEG_LENGTH__642                    (0x000000000281)        /* 642 GCLK */
#define SEG_LENGTH__641                    (0x000000000280)        /* 641 GCLK */
#define SEG_LENGTH__640                    (0x00000000027F)        /* 640 GCLK */
#define SEG_LENGTH__639                    (0x00000000027E)        /* 639 GCLK */
#define SEG_LENGTH__638                    (0x00000000027D)        /* 638 GCLK */
#define SEG_LENGTH__637                    (0x00000000027C)        /* 637 GCLK */
#define SEG_LENGTH__636                    (0x00000000027B)        /* 636 GCLK */
#define SEG_LENGTH__635                    (0x00000000027A)        /* 635 GCLK */
#define SEG_LENGTH__634                    (0x000000000279)        /* 634 GCLK */
#define SEG_LENGTH__633                    (0x000000000278)        /* 633 GCLK */
#define SEG_LENGTH__632                    (0x000000000277)        /* 632 GCLK */
#define SEG_LENGTH__631                    (0x000000000276)        /* 631 GCLK */
#define SEG_LENGTH__630                    (0x000000000275)        /* 630 GCLK */
#define SEG_LENGTH__629                    (0x000000000274)        /* 629 GCLK */
#define SEG_LENGTH__628                    (0x000000000273)        /* 628 GCLK */
#define SEG_LENGTH__627                    (0x000000000272)        /* 627 GCLK */
#define SEG_LENGTH__626                    (0x000000000271)        /* 626 GCLK */
#define SEG_LENGTH__625                    (0x000000000270)        /* 625 GCLK */
#define SEG_LENGTH__624                    (0x00000000026F)        /* 624 GCLK */
#define SEG_LENGTH__623                    (0x00000000026E)        /* 623 GCLK */
#define SEG_LENGTH__622                    (0x00000000026D)        /* 622 GCLK */
#define SEG_LENGTH__621                    (0x00000000026C)        /* 621 GCLK */
#define SEG_LENGTH__620                    (0x00000000026B)        /* 620 GCLK */
#define SEG_LENGTH__619                    (0x00000000026A)        /* 619 GCLK */
#define SEG_LENGTH__618                    (0x000000000269)        /* 618 GCLK */
#define SEG_LENGTH__617                    (0x000000000268)        /* 617 GCLK */
#define SEG_LENGTH__616                    (0x000000000267)        /* 616 GCLK */
#define SEG_LENGTH__615                    (0x000000000266)        /* 615 GCLK */
#define SEG_LENGTH__614                    (0x000000000265)        /* 614 GCLK */
#define SEG_LENGTH__613                    (0x000000000264)        /* 613 GCLK */
#define SEG_LENGTH__612                    (0x000000000263)        /* 612 GCLK */
#define SEG_LENGTH__611                    (0x000000000262)        /* 611 GCLK */
#define SEG_LENGTH__610                    (0x000000000261)        /* 610 GCLK */
#define SEG_LENGTH__609                    (0x000000000260)        /* 609 GCLK */
#define SEG_LENGTH__608                    (0x00000000025F)        /* 608 GCLK */
#define SEG_LENGTH__607                    (0x00000000025E)        /* 607 GCLK */
#define SEG_LENGTH__606                    (0x00000000025D)        /* 606 GCLK */
#define SEG_LENGTH__605                    (0x00000000025C)        /* 605 GCLK */
#define SEG_LENGTH__604                    (0x00000000025B)        /* 604 GCLK */
#define SEG_LENGTH__603                    (0x00000000025A)        /* 603 GCLK */
#define SEG_LENGTH__602                    (0x000000000259)        /* 602 GCLK */
#define SEG_LENGTH__601                    (0x000000000258)        /* 601 GCLK */
#define SEG_LENGTH__600                    (0x000000000257)        /* 600 GCLK */
#define SEG_LENGTH__599                    (0x000000000256)        /* 599 GCLK */
#define SEG_LENGTH__598                    (0x000000000255)        /* 598 GCLK */
#define SEG_LENGTH__597                    (0x000000000254)        /* 597 GCLK */
#define SEG_LENGTH__596                    (0x000000000253)        /* 596 GCLK */
#define SEG_LENGTH__595                    (0x000000000252)        /* 595 GCLK */
#define SEG_LENGTH__594                    (0x000000000251)        /* 594 GCLK */
#define SEG_LENGTH__593                    (0x000000000250)        /* 593 GCLK */
#define SEG_LENGTH__592                    (0x00000000024F)        /* 592 GCLK */
#define SEG_LENGTH__591                    (0x00000000024E)        /* 591 GCLK */
#define SEG_LENGTH__590                    (0x00000000024D)        /* 590 GCLK */
#define SEG_LENGTH__589                    (0x00000000024C)        /* 589 GCLK */
#define SEG_LENGTH__588                    (0x00000000024B)        /* 588 GCLK */
#define SEG_LENGTH__587                    (0x00000000024A)        /* 587 GCLK */
#define SEG_LENGTH__586                    (0x000000000249)        /* 586 GCLK */
#define SEG_LENGTH__585                    (0x000000000248)        /* 585 GCLK */
#define SEG_LENGTH__584                    (0x000000000247)        /* 584 GCLK */
#define SEG_LENGTH__583                    (0x000000000246)        /* 583 GCLK */
#define SEG_LENGTH__582                    (0x000000000245)        /* 582 GCLK */
#define SEG_LENGTH__581                    (0x000000000244)        /* 581 GCLK */
#define SEG_LENGTH__580                    (0x000000000243)        /* 580 GCLK */
#define SEG_LENGTH__579                    (0x000000000242)        /* 579 GCLK */
#define SEG_LENGTH__578                    (0x000000000241)        /* 578 GCLK */
#define SEG_LENGTH__577                    (0x000000000240)        /* 577 GCLK */
#define SEG_LENGTH__576                    (0x00000000023F)        /* 576 GCLK */
#define SEG_LENGTH__575                    (0x00000000023E)        /* 575 GCLK */
#define SEG_LENGTH__574                    (0x00000000023D)        /* 574 GCLK */
#define SEG_LENGTH__573                    (0x00000000023C)        /* 573 GCLK */
#define SEG_LENGTH__572                    (0x00000000023B)        /* 572 GCLK */
#define SEG_LENGTH__571                    (0x00000000023A)        /* 571 GCLK */
#define SEG_LENGTH__570                    (0x000000000239)        /* 570 GCLK */
#define SEG_LENGTH__569                    (0x000000000238)        /* 569 GCLK */
#define SEG_LENGTH__568                    (0x000000000237)        /* 568 GCLK */
#define SEG_LENGTH__567                    (0x000000000236)        /* 567 GCLK */
#define SEG_LENGTH__566                    (0x000000000235)        /* 566 GCLK */
#define SEG_LENGTH__565                    (0x000000000234)        /* 565 GCLK */
#define SEG_LENGTH__564                    (0x000000000233)        /* 564 GCLK */
#define SEG_LENGTH__563                    (0x000000000232)        /* 563 GCLK */
#define SEG_LENGTH__562                    (0x000000000231)        /* 562 GCLK */
#define SEG_LENGTH__561                    (0x000000000230)        /* 561 GCLK */
#define SEG_LENGTH__560                    (0x00000000022F)        /* 560 GCLK */
#define SEG_LENGTH__559                    (0x00000000022E)        /* 559 GCLK */
#define SEG_LENGTH__558                    (0x00000000022D)        /* 558 GCLK */
#define SEG_LENGTH__557                    (0x00000000022C)        /* 557 GCLK */
#define SEG_LENGTH__556                    (0x00000000022B)        /* 556 GCLK */
#define SEG_LENGTH__555                    (0x00000000022A)        /* 555 GCLK */
#define SEG_LENGTH__554                    (0x000000000229)        /* 554 GCLK */
#define SEG_LENGTH__553                    (0x000000000228)        /* 553 GCLK */
#define SEG_LENGTH__552                    (0x000000000227)        /* 552 GCLK */
#define SEG_LENGTH__551                    (0x000000000226)        /* 551 GCLK */
#define SEG_LENGTH__550                    (0x000000000225)        /* 550 GCLK */
#define SEG_LENGTH__549                    (0x000000000224)        /* 549 GCLK */
#define SEG_LENGTH__548                    (0x000000000223)        /* 548 GCLK */
#define SEG_LENGTH__547                    (0x000000000222)        /* 547 GCLK */
#define SEG_LENGTH__546                    (0x000000000221)        /* 546 GCLK */
#define SEG_LENGTH__545                    (0x000000000220)        /* 545 GCLK */
#define SEG_LENGTH__544                    (0x00000000021F)        /* 544 GCLK */
#define SEG_LENGTH__543                    (0x00000000021E)        /* 543 GCLK */
#define SEG_LENGTH__542                    (0x00000000021D)        /* 542 GCLK */
#define SEG_LENGTH__541                    (0x00000000021C)        /* 541 GCLK */
#define SEG_LENGTH__540                    (0x00000000021B)        /* 540 GCLK */
#define SEG_LENGTH__539                    (0x00000000021A)        /* 539 GCLK */
#define SEG_LENGTH__538                    (0x000000000219)        /* 538 GCLK */
#define SEG_LENGTH__537                    (0x000000000218)        /* 537 GCLK */
#define SEG_LENGTH__536                    (0x000000000217)        /* 536 GCLK */
#define SEG_LENGTH__535                    (0x000000000216)        /* 535 GCLK */
#define SEG_LENGTH__534                    (0x000000000215)        /* 534 GCLK */
#define SEG_LENGTH__533                    (0x000000000214)        /* 533 GCLK */
#define SEG_LENGTH__532                    (0x000000000213)        /* 532 GCLK */
#define SEG_LENGTH__531                    (0x000000000212)        /* 531 GCLK */
#define SEG_LENGTH__530                    (0x000000000211)        /* 530 GCLK */
#define SEG_LENGTH__529                    (0x000000000210)        /* 529 GCLK */
#define SEG_LENGTH__528                    (0x00000000020F)        /* 528 GCLK */
#define SEG_LENGTH__527                    (0x00000000020E)        /* 527 GCLK */
#define SEG_LENGTH__526                    (0x00000000020D)        /* 526 GCLK */
#define SEG_LENGTH__525                    (0x00000000020C)        /* 525 GCLK */
#define SEG_LENGTH__524                    (0x00000000020B)        /* 524 GCLK */
#define SEG_LENGTH__523                    (0x00000000020A)        /* 523 GCLK */
#define SEG_LENGTH__522                    (0x000000000209)        /* 522 GCLK */
#define SEG_LENGTH__521                    (0x000000000208)        /* 521 GCLK */
#define SEG_LENGTH__520                    (0x000000000207)        /* 520 GCLK */
#define SEG_LENGTH__519                    (0x000000000206)        /* 519 GCLK */
#define SEG_LENGTH__518                    (0x000000000205)        /* 518 GCLK */
#define SEG_LENGTH__517                    (0x000000000204)        /* 517 GCLK */
#define SEG_LENGTH__516                    (0x000000000203)        /* 516 GCLK */
#define SEG_LENGTH__515                    (0x000000000202)        /* 515 GCLK */
#define SEG_LENGTH__514                    (0x000000000201)        /* 514 GCLK */
#define SEG_LENGTH__513                    (0x000000000200)        /* 513 GCLK */
#define SEG_LENGTH__512                    (0x0000000001FF)        /* 512 GCLK */
#define SEG_LENGTH__511                    (0x0000000001FE)        /* 511 GCLK */
#define SEG_LENGTH__510                    (0x0000000001FD)        /* 510 GCLK */
#define SEG_LENGTH__509                    (0x0000000001FC)        /* 509 GCLK */
#define SEG_LENGTH__508                    (0x0000000001FB)        /* 508 GCLK */
#define SEG_LENGTH__507                    (0x0000000001FA)        /* 507 GCLK */
#define SEG_LENGTH__506                    (0x0000000001F9)        /* 506 GCLK */
#define SEG_LENGTH__505                    (0x0000000001F8)        /* 505 GCLK */
#define SEG_LENGTH__504                    (0x0000000001F7)        /* 504 GCLK */
#define SEG_LENGTH__503                    (0x0000000001F6)        /* 503 GCLK */
#define SEG_LENGTH__502                    (0x0000000001F5)        /* 502 GCLK */
#define SEG_LENGTH__501                    (0x0000000001F4)        /* 501 GCLK */
#define SEG_LENGTH__500                    (0x0000000001F3)        /* 500 GCLK */
#define SEG_LENGTH__499                    (0x0000000001F2)        /* 499 GCLK */
#define SEG_LENGTH__498                    (0x0000000001F1)        /* 498 GCLK */
#define SEG_LENGTH__497                    (0x0000000001F0)        /* 497 GCLK */
#define SEG_LENGTH__496                    (0x0000000001EF)        /* 496 GCLK */
#define SEG_LENGTH__495                    (0x0000000001EE)        /* 495 GCLK */
#define SEG_LENGTH__494                    (0x0000000001ED)        /* 494 GCLK */
#define SEG_LENGTH__493                    (0x0000000001EC)        /* 493 GCLK */
#define SEG_LENGTH__492                    (0x0000000001EB)        /* 492 GCLK */
#define SEG_LENGTH__491                    (0x0000000001EA)        /* 491 GCLK */
#define SEG_LENGTH__490                    (0x0000000001E9)        /* 490 GCLK */
#define SEG_LENGTH__489                    (0x0000000001E8)        /* 489 GCLK */
#define SEG_LENGTH__488                    (0x0000000001E7)        /* 488 GCLK */
#define SEG_LENGTH__487                    (0x0000000001E6)        /* 487 GCLK */
#define SEG_LENGTH__486                    (0x0000000001E5)        /* 486 GCLK */
#define SEG_LENGTH__485                    (0x0000000001E4)        /* 485 GCLK */
#define SEG_LENGTH__484                    (0x0000000001E3)        /* 484 GCLK */
#define SEG_LENGTH__483                    (0x0000000001E2)        /* 483 GCLK */
#define SEG_LENGTH__482                    (0x0000000001E1)        /* 482 GCLK */
#define SEG_LENGTH__481                    (0x0000000001E0)        /* 481 GCLK */
#define SEG_LENGTH__480                    (0x0000000001DF)        /* 480 GCLK */
#define SEG_LENGTH__479                    (0x0000000001DE)        /* 479 GCLK */
#define SEG_LENGTH__478                    (0x0000000001DD)        /* 478 GCLK */
#define SEG_LENGTH__477                    (0x0000000001DC)        /* 477 GCLK */
#define SEG_LENGTH__476                    (0x0000000001DB)        /* 476 GCLK */
#define SEG_LENGTH__475                    (0x0000000001DA)        /* 475 GCLK */
#define SEG_LENGTH__474                    (0x0000000001D9)        /* 474 GCLK */
#define SEG_LENGTH__473                    (0x0000000001D8)        /* 473 GCLK */
#define SEG_LENGTH__472                    (0x0000000001D7)        /* 472 GCLK */
#define SEG_LENGTH__471                    (0x0000000001D6)        /* 471 GCLK */
#define SEG_LENGTH__470                    (0x0000000001D5)        /* 470 GCLK */
#define SEG_LENGTH__469                    (0x0000000001D4)        /* 469 GCLK */
#define SEG_LENGTH__468                    (0x0000000001D3)        /* 468 GCLK */
#define SEG_LENGTH__467                    (0x0000000001D2)        /* 467 GCLK */
#define SEG_LENGTH__466                    (0x0000000001D1)        /* 466 GCLK */
#define SEG_LENGTH__465                    (0x0000000001D0)        /* 465 GCLK */
#define SEG_LENGTH__464                    (0x0000000001CF)        /* 464 GCLK */
#define SEG_LENGTH__463                    (0x0000000001CE)        /* 463 GCLK */
#define SEG_LENGTH__462                    (0x0000000001CD)        /* 462 GCLK */
#define SEG_LENGTH__461                    (0x0000000001CC)        /* 461 GCLK */
#define SEG_LENGTH__460                    (0x0000000001CB)        /* 460 GCLK */
#define SEG_LENGTH__459                    (0x0000000001CA)        /* 459 GCLK */
#define SEG_LENGTH__458                    (0x0000000001C9)        /* 458 GCLK */
#define SEG_LENGTH__457                    (0x0000000001C8)        /* 457 GCLK */
#define SEG_LENGTH__456                    (0x0000000001C7)        /* 456 GCLK */
#define SEG_LENGTH__455                    (0x0000000001C6)        /* 455 GCLK */
#define SEG_LENGTH__454                    (0x0000000001C5)        /* 454 GCLK */
#define SEG_LENGTH__453                    (0x0000000001C4)        /* 453 GCLK */
#define SEG_LENGTH__452                    (0x0000000001C3)        /* 452 GCLK */
#define SEG_LENGTH__451                    (0x0000000001C2)        /* 451 GCLK */
#define SEG_LENGTH__450                    (0x0000000001C1)        /* 450 GCLK */
#define SEG_LENGTH__449                    (0x0000000001C0)        /* 449 GCLK */
#define SEG_LENGTH__448                    (0x0000000001BF)        /* 448 GCLK */
#define SEG_LENGTH__447                    (0x0000000001BE)        /* 447 GCLK */
#define SEG_LENGTH__446                    (0x0000000001BD)        /* 446 GCLK */
#define SEG_LENGTH__445                    (0x0000000001BC)        /* 445 GCLK */
#define SEG_LENGTH__444                    (0x0000000001BB)        /* 444 GCLK */
#define SEG_LENGTH__443                    (0x0000000001BA)        /* 443 GCLK */
#define SEG_LENGTH__442                    (0x0000000001B9)        /* 442 GCLK */
#define SEG_LENGTH__441                    (0x0000000001B8)        /* 441 GCLK */
#define SEG_LENGTH__440                    (0x0000000001B7)        /* 440 GCLK */
#define SEG_LENGTH__439                    (0x0000000001B6)        /* 439 GCLK */
#define SEG_LENGTH__438                    (0x0000000001B5)        /* 438 GCLK */
#define SEG_LENGTH__437                    (0x0000000001B4)        /* 437 GCLK */
#define SEG_LENGTH__436                    (0x0000000001B3)        /* 436 GCLK */
#define SEG_LENGTH__435                    (0x0000000001B2)        /* 435 GCLK */
#define SEG_LENGTH__434                    (0x0000000001B1)        /* 434 GCLK */
#define SEG_LENGTH__433                    (0x0000000001B0)        /* 433 GCLK */
#define SEG_LENGTH__432                    (0x0000000001AF)        /* 432 GCLK */
#define SEG_LENGTH__431                    (0x0000000001AE)        /* 431 GCLK */
#define SEG_LENGTH__430                    (0x0000000001AD)        /* 430 GCLK */
#define SEG_LENGTH__429                    (0x0000000001AC)        /* 429 GCLK */
#define SEG_LENGTH__428                    (0x0000000001AB)        /* 428 GCLK */
#define SEG_LENGTH__427                    (0x0000000001AA)        /* 427 GCLK */
#define SEG_LENGTH__426                    (0x0000000001A9)        /* 426 GCLK */
#define SEG_LENGTH__425                    (0x0000000001A8)        /* 425 GCLK */
#define SEG_LENGTH__424                    (0x0000000001A7)        /* 424 GCLK */
#define SEG_LENGTH__423                    (0x0000000001A6)        /* 423 GCLK */
#define SEG_LENGTH__422                    (0x0000000001A5)        /* 422 GCLK */
#define SEG_LENGTH__421                    (0x0000000001A4)        /* 421 GCLK */
#define SEG_LENGTH__420                    (0x0000000001A3)        /* 420 GCLK */
#define SEG_LENGTH__419                    (0x0000000001A2)        /* 419 GCLK */
#define SEG_LENGTH__418                    (0x0000000001A1)        /* 418 GCLK */
#define SEG_LENGTH__417                    (0x0000000001A0)        /* 417 GCLK */
#define SEG_LENGTH__416                    (0x00000000019F)        /* 416 GCLK */
#define SEG_LENGTH__415                    (0x00000000019E)        /* 415 GCLK */
#define SEG_LENGTH__414                    (0x00000000019D)        /* 414 GCLK */
#define SEG_LENGTH__413                    (0x00000000019C)        /* 413 GCLK */
#define SEG_LENGTH__412                    (0x00000000019B)        /* 412 GCLK */
#define SEG_LENGTH__411                    (0x00000000019A)        /* 411 GCLK */
#define SEG_LENGTH__410                    (0x000000000199)        /* 410 GCLK */
#define SEG_LENGTH__409                    (0x000000000198)        /* 409 GCLK */
#define SEG_LENGTH__408                    (0x000000000197)        /* 408 GCLK */
#define SEG_LENGTH__407                    (0x000000000196)        /* 407 GCLK */
#define SEG_LENGTH__406                    (0x000000000195)        /* 406 GCLK */
#define SEG_LENGTH__405                    (0x000000000194)        /* 405 GCLK */
#define SEG_LENGTH__404                    (0x000000000193)        /* 404 GCLK */
#define SEG_LENGTH__403                    (0x000000000192)        /* 403 GCLK */
#define SEG_LENGTH__402                    (0x000000000191)        /* 402 GCLK */
#define SEG_LENGTH__401                    (0x000000000190)        /* 401 GCLK */
#define SEG_LENGTH__400                    (0x00000000018F)        /* 400 GCLK */
#define SEG_LENGTH__399                    (0x00000000018E)        /* 399 GCLK */
#define SEG_LENGTH__398                    (0x00000000018D)        /* 398 GCLK */
#define SEG_LENGTH__397                    (0x00000000018C)        /* 397 GCLK */
#define SEG_LENGTH__396                    (0x00000000018B)        /* 396 GCLK */
#define SEG_LENGTH__395                    (0x00000000018A)        /* 395 GCLK */
#define SEG_LENGTH__394                    (0x000000000189)        /* 394 GCLK */
#define SEG_LENGTH__393                    (0x000000000188)        /* 393 GCLK */
#define SEG_LENGTH__392                    (0x000000000187)        /* 392 GCLK */
#define SEG_LENGTH__391                    (0x000000000186)        /* 391 GCLK */
#define SEG_LENGTH__390                    (0x000000000185)        /* 390 GCLK */
#define SEG_LENGTH__389                    (0x000000000184)        /* 389 GCLK */
#define SEG_LENGTH__388                    (0x000000000183)        /* 388 GCLK */
#define SEG_LENGTH__387                    (0x000000000182)        /* 387 GCLK */
#define SEG_LENGTH__386                    (0x000000000181)        /* 386 GCLK */
#define SEG_LENGTH__385                    (0x000000000180)        /* 385 GCLK */
#define SEG_LENGTH__384                    (0x00000000017F)        /* 384 GCLK */
#define SEG_LENGTH__383                    (0x00000000017E)        /* 383 GCLK */
#define SEG_LENGTH__382                    (0x00000000017D)        /* 382 GCLK */
#define SEG_LENGTH__381                    (0x00000000017C)        /* 381 GCLK */
#define SEG_LENGTH__380                    (0x00000000017B)        /* 380 GCLK */
#define SEG_LENGTH__379                    (0x00000000017A)        /* 379 GCLK */
#define SEG_LENGTH__378                    (0x000000000179)        /* 378 GCLK */
#define SEG_LENGTH__377                    (0x000000000178)        /* 377 GCLK */
#define SEG_LENGTH__376                    (0x000000000177)        /* 376 GCLK */
#define SEG_LENGTH__375                    (0x000000000176)        /* 375 GCLK */
#define SEG_LENGTH__374                    (0x000000000175)        /* 374 GCLK */
#define SEG_LENGTH__373                    (0x000000000174)        /* 373 GCLK */
#define SEG_LENGTH__372                    (0x000000000173)        /* 372 GCLK */
#define SEG_LENGTH__371                    (0x000000000172)        /* 371 GCLK */
#define SEG_LENGTH__370                    (0x000000000171)        /* 370 GCLK */
#define SEG_LENGTH__369                    (0x000000000170)        /* 369 GCLK */
#define SEG_LENGTH__368                    (0x00000000016F)        /* 368 GCLK */
#define SEG_LENGTH__367                    (0x00000000016E)        /* 367 GCLK */
#define SEG_LENGTH__366                    (0x00000000016D)        /* 366 GCLK */
#define SEG_LENGTH__365                    (0x00000000016C)        /* 365 GCLK */
#define SEG_LENGTH__364                    (0x00000000016B)        /* 364 GCLK */
#define SEG_LENGTH__363                    (0x00000000016A)        /* 363 GCLK */
#define SEG_LENGTH__362                    (0x000000000169)        /* 362 GCLK */
#define SEG_LENGTH__361                    (0x000000000168)        /* 361 GCLK */
#define SEG_LENGTH__360                    (0x000000000167)        /* 360 GCLK */
#define SEG_LENGTH__359                    (0x000000000166)        /* 359 GCLK */
#define SEG_LENGTH__358                    (0x000000000165)        /* 358 GCLK */
#define SEG_LENGTH__357                    (0x000000000164)        /* 357 GCLK */
#define SEG_LENGTH__356                    (0x000000000163)        /* 356 GCLK */
#define SEG_LENGTH__355                    (0x000000000162)        /* 355 GCLK */
#define SEG_LENGTH__354                    (0x000000000161)        /* 354 GCLK */
#define SEG_LENGTH__353                    (0x000000000160)        /* 353 GCLK */
#define SEG_LENGTH__352                    (0x00000000015F)        /* 352 GCLK */
#define SEG_LENGTH__351                    (0x00000000015E)        /* 351 GCLK */
#define SEG_LENGTH__350                    (0x00000000015D)        /* 350 GCLK */
#define SEG_LENGTH__349                    (0x00000000015C)        /* 349 GCLK */
#define SEG_LENGTH__348                    (0x00000000015B)        /* 348 GCLK */
#define SEG_LENGTH__347                    (0x00000000015A)        /* 347 GCLK */
#define SEG_LENGTH__346                    (0x000000000159)        /* 346 GCLK */
#define SEG_LENGTH__345                    (0x000000000158)        /* 345 GCLK */
#define SEG_LENGTH__344                    (0x000000000157)        /* 344 GCLK */
#define SEG_LENGTH__343                    (0x000000000156)        /* 343 GCLK */
#define SEG_LENGTH__342                    (0x000000000155)        /* 342 GCLK */
#define SEG_LENGTH__341                    (0x000000000154)        /* 341 GCLK */
#define SEG_LENGTH__340                    (0x000000000153)        /* 340 GCLK */
#define SEG_LENGTH__339                    (0x000000000152)        /* 339 GCLK */
#define SEG_LENGTH__338                    (0x000000000151)        /* 338 GCLK */
#define SEG_LENGTH__337                    (0x000000000150)        /* 337 GCLK */
#define SEG_LENGTH__336                    (0x00000000014F)        /* 336 GCLK */
#define SEG_LENGTH__335                    (0x00000000014E)        /* 335 GCLK */
#define SEG_LENGTH__334                    (0x00000000014D)        /* 334 GCLK */
#define SEG_LENGTH__333                    (0x00000000014C)        /* 333 GCLK */
#define SEG_LENGTH__332                    (0x00000000014B)        /* 332 GCLK */
#define SEG_LENGTH__331                    (0x00000000014A)        /* 331 GCLK */
#define SEG_LENGTH__330                    (0x000000000149)        /* 330 GCLK */
#define SEG_LENGTH__329                    (0x000000000148)        /* 329 GCLK */
#define SEG_LENGTH__328                    (0x000000000147)        /* 328 GCLK */
#define SEG_LENGTH__327                    (0x000000000146)        /* 327 GCLK */
#define SEG_LENGTH__326                    (0x000000000145)        /* 326 GCLK */
#define SEG_LENGTH__325                    (0x000000000144)        /* 325 GCLK */
#define SEG_LENGTH__324                    (0x000000000143)        /* 324 GCLK */
#define SEG_LENGTH__323                    (0x000000000142)        /* 323 GCLK */
#define SEG_LENGTH__322                    (0x000000000141)        /* 322 GCLK */
#define SEG_LENGTH__321                    (0x000000000140)        /* 321 GCLK */
#define SEG_LENGTH__320                    (0x00000000013F)        /* 320 GCLK */
#define SEG_LENGTH__319                    (0x00000000013E)        /* 319 GCLK */
#define SEG_LENGTH__318                    (0x00000000013D)        /* 318 GCLK */
#define SEG_LENGTH__317                    (0x00000000013C)        /* 317 GCLK */
#define SEG_LENGTH__316                    (0x00000000013B)        /* 316 GCLK */
#define SEG_LENGTH__315                    (0x00000000013A)        /* 315 GCLK */
#define SEG_LENGTH__314                    (0x000000000139)        /* 314 GCLK */
#define SEG_LENGTH__313                    (0x000000000138)        /* 313 GCLK */
#define SEG_LENGTH__312                    (0x000000000137)        /* 312 GCLK */
#define SEG_LENGTH__311                    (0x000000000136)        /* 311 GCLK */
#define SEG_LENGTH__310                    (0x000000000135)        /* 310 GCLK */
#define SEG_LENGTH__309                    (0x000000000134)        /* 309 GCLK */
#define SEG_LENGTH__308                    (0x000000000133)        /* 308 GCLK */
#define SEG_LENGTH__307                    (0x000000000132)        /* 307 GCLK */
#define SEG_LENGTH__306                    (0x000000000131)        /* 306 GCLK */
#define SEG_LENGTH__305                    (0x000000000130)        /* 305 GCLK */
#define SEG_LENGTH__304                    (0x00000000012F)        /* 304 GCLK */
#define SEG_LENGTH__303                    (0x00000000012E)        /* 303 GCLK */
#define SEG_LENGTH__302                    (0x00000000012D)        /* 302 GCLK */
#define SEG_LENGTH__301                    (0x00000000012C)        /* 301 GCLK */
#define SEG_LENGTH__300                    (0x00000000012B)        /* 300 GCLK */
#define SEG_LENGTH__299                    (0x00000000012A)        /* 299 GCLK */
#define SEG_LENGTH__298                    (0x000000000129)        /* 298 GCLK */
#define SEG_LENGTH__297                    (0x000000000128)        /* 297 GCLK */
#define SEG_LENGTH__296                    (0x000000000127)        /* 296 GCLK */
#define SEG_LENGTH__295                    (0x000000000126)        /* 295 GCLK */
#define SEG_LENGTH__294                    (0x000000000125)        /* 294 GCLK */
#define SEG_LENGTH__293                    (0x000000000124)        /* 293 GCLK */
#define SEG_LENGTH__292                    (0x000000000123)        /* 292 GCLK */
#define SEG_LENGTH__291                    (0x000000000122)        /* 291 GCLK */
#define SEG_LENGTH__290                    (0x000000000121)        /* 290 GCLK */
#define SEG_LENGTH__289                    (0x000000000120)        /* 289 GCLK */
#define SEG_LENGTH__288                    (0x00000000011F)        /* 288 GCLK */
#define SEG_LENGTH__287                    (0x00000000011E)        /* 287 GCLK */
#define SEG_LENGTH__286                    (0x00000000011D)        /* 286 GCLK */
#define SEG_LENGTH__285                    (0x00000000011C)        /* 285 GCLK */
#define SEG_LENGTH__284                    (0x00000000011B)        /* 284 GCLK */
#define SEG_LENGTH__283                    (0x00000000011A)        /* 283 GCLK */
#define SEG_LENGTH__282                    (0x000000000119)        /* 282 GCLK */
#define SEG_LENGTH__281                    (0x000000000118)        /* 281 GCLK */
#define SEG_LENGTH__280                    (0x000000000117)        /* 280 GCLK */
#define SEG_LENGTH__279                    (0x000000000116)        /* 279 GCLK */
#define SEG_LENGTH__278                    (0x000000000115)        /* 278 GCLK */
#define SEG_LENGTH__277                    (0x000000000114)        /* 277 GCLK */
#define SEG_LENGTH__276                    (0x000000000113)        /* 276 GCLK */
#define SEG_LENGTH__275                    (0x000000000112)        /* 275 GCLK */
#define SEG_LENGTH__274                    (0x000000000111)        /* 274 GCLK */
#define SEG_LENGTH__273                    (0x000000000110)        /* 273 GCLK */
#define SEG_LENGTH__272                    (0x00000000010F)        /* 272 GCLK */
#define SEG_LENGTH__271                    (0x00000000010E)        /* 271 GCLK */
#define SEG_LENGTH__270                    (0x00000000010D)        /* 270 GCLK */
#define SEG_LENGTH__269                    (0x00000000010C)        /* 269 GCLK */
#define SEG_LENGTH__268                    (0x00000000010B)        /* 268 GCLK */
#define SEG_LENGTH__267                    (0x00000000010A)        /* 267 GCLK */
#define SEG_LENGTH__266                    (0x000000000109)        /* 266 GCLK */
#define SEG_LENGTH__265                    (0x000000000108)        /* 265 GCLK */
#define SEG_LENGTH__264                    (0x000000000107)        /* 264 GCLK */
#define SEG_LENGTH__263                    (0x000000000106)        /* 263 GCLK */
#define SEG_LENGTH__262                    (0x000000000105)        /* 262 GCLK */
#define SEG_LENGTH__261                    (0x000000000104)        /* 261 GCLK */
#define SEG_LENGTH__260                    (0x000000000103)        /* 260 GCLK */
#define SEG_LENGTH__259                    (0x000000000102)        /* 259 GCLK */
#define SEG_LENGTH__258                    (0x000000000101)        /* 258 GCLK */
#define SEG_LENGTH__257                    (0x000000000100)        /* 257 GCLK */
#define SEG_LENGTH__256                    (0x0000000000FF)        /* 256 GCLK */
#define SEG_LENGTH__255                    (0x0000000000FE)        /* 255 GCLK */
#define SEG_LENGTH__254                    (0x0000000000FD)        /* 254 GCLK */
#define SEG_LENGTH__253                    (0x0000000000FC)        /* 253 GCLK */
#define SEG_LENGTH__252                    (0x0000000000FB)        /* 252 GCLK */
#define SEG_LENGTH__251                    (0x0000000000FA)        /* 251 GCLK */
#define SEG_LENGTH__250                    (0x0000000000F9)        /* 250 GCLK */
#define SEG_LENGTH__249                    (0x0000000000F8)        /* 249 GCLK */
#define SEG_LENGTH__248                    (0x0000000000F7)        /* 248 GCLK */
#define SEG_LENGTH__247                    (0x0000000000F6)        /* 247 GCLK */
#define SEG_LENGTH__246                    (0x0000000000F5)        /* 246 GCLK */
#define SEG_LENGTH__245                    (0x0000000000F4)        /* 245 GCLK */
#define SEG_LENGTH__244                    (0x0000000000F3)        /* 244 GCLK */
#define SEG_LENGTH__243                    (0x0000000000F2)        /* 243 GCLK */
#define SEG_LENGTH__242                    (0x0000000000F1)        /* 242 GCLK */
#define SEG_LENGTH__241                    (0x0000000000F0)        /* 241 GCLK */
#define SEG_LENGTH__240                    (0x0000000000EF)        /* 240 GCLK */
#define SEG_LENGTH__239                    (0x0000000000EE)        /* 239 GCLK */
#define SEG_LENGTH__238                    (0x0000000000ED)        /* 238 GCLK */
#define SEG_LENGTH__237                    (0x0000000000EC)        /* 237 GCLK */
#define SEG_LENGTH__236                    (0x0000000000EB)        /* 236 GCLK */
#define SEG_LENGTH__235                    (0x0000000000EA)        /* 235 GCLK */
#define SEG_LENGTH__234                    (0x0000000000E9)        /* 234 GCLK */
#define SEG_LENGTH__233                    (0x0000000000E8)        /* 233 GCLK */
#define SEG_LENGTH__232                    (0x0000000000E7)        /* 232 GCLK */
#define SEG_LENGTH__231                    (0x0000000000E6)        /* 231 GCLK */
#define SEG_LENGTH__230                    (0x0000000000E5)        /* 230 GCLK */
#define SEG_LENGTH__229                    (0x0000000000E4)        /* 229 GCLK */
#define SEG_LENGTH__228                    (0x0000000000E3)        /* 228 GCLK */
#define SEG_LENGTH__227                    (0x0000000000E2)        /* 227 GCLK */
#define SEG_LENGTH__226                    (0x0000000000E1)        /* 226 GCLK */
#define SEG_LENGTH__225                    (0x0000000000E0)        /* 225 GCLK */
#define SEG_LENGTH__224                    (0x0000000000DF)        /* 224 GCLK */
#define SEG_LENGTH__223                    (0x0000000000DE)        /* 223 GCLK */
#define SEG_LENGTH__222                    (0x0000000000DD)        /* 222 GCLK */
#define SEG_LENGTH__221                    (0x0000000000DC)        /* 221 GCLK */
#define SEG_LENGTH__220                    (0x0000000000DB)        /* 220 GCLK */
#define SEG_LENGTH__219                    (0x0000000000DA)        /* 219 GCLK */
#define SEG_LENGTH__218                    (0x0000000000D9)        /* 218 GCLK */
#define SEG_LENGTH__217                    (0x0000000000D8)        /* 217 GCLK */
#define SEG_LENGTH__216                    (0x0000000000D7)        /* 216 GCLK */
#define SEG_LENGTH__215                    (0x0000000000D6)        /* 215 GCLK */
#define SEG_LENGTH__214                    (0x0000000000D5)        /* 214 GCLK */
#define SEG_LENGTH__213                    (0x0000000000D4)        /* 213 GCLK */
#define SEG_LENGTH__212                    (0x0000000000D3)        /* 212 GCLK */
#define SEG_LENGTH__211                    (0x0000000000D2)        /* 211 GCLK */
#define SEG_LENGTH__210                    (0x0000000000D1)        /* 210 GCLK */
#define SEG_LENGTH__209                    (0x0000000000D0)        /* 209 GCLK */
#define SEG_LENGTH__208                    (0x0000000000CF)        /* 208 GCLK */
#define SEG_LENGTH__207                    (0x0000000000CE)        /* 207 GCLK */
#define SEG_LENGTH__206                    (0x0000000000CD)        /* 206 GCLK */
#define SEG_LENGTH__205                    (0x0000000000CC)        /* 205 GCLK */
#define SEG_LENGTH__204                    (0x0000000000CB)        /* 204 GCLK */
#define SEG_LENGTH__203                    (0x0000000000CA)        /* 203 GCLK */
#define SEG_LENGTH__202                    (0x0000000000C9)        /* 202 GCLK */
#define SEG_LENGTH__201                    (0x0000000000C8)        /* 201 GCLK */
#define SEG_LENGTH__200                    (0x0000000000C7)        /* 200 GCLK */
#define SEG_LENGTH__199                    (0x0000000000C6)        /* 199 GCLK */
#define SEG_LENGTH__198                    (0x0000000000C5)        /* 198 GCLK */
#define SEG_LENGTH__197                    (0x0000000000C4)        /* 197 GCLK */
#define SEG_LENGTH__196                    (0x0000000000C3)        /* 196 GCLK */
#define SEG_LENGTH__195                    (0x0000000000C2)        /* 195 GCLK */
#define SEG_LENGTH__194                    (0x0000000000C1)        /* 194 GCLK */
#define SEG_LENGTH__193                    (0x0000000000C0)        /* 193 GCLK */
#define SEG_LENGTH__192                    (0x0000000000BF)        /* 192 GCLK */
#define SEG_LENGTH__191                    (0x0000000000BE)        /* 191 GCLK */
#define SEG_LENGTH__190                    (0x0000000000BD)        /* 190 GCLK */
#define SEG_LENGTH__189                    (0x0000000000BC)        /* 189 GCLK */
#define SEG_LENGTH__188                    (0x0000000000BB)        /* 188 GCLK */
#define SEG_LENGTH__187                    (0x0000000000BA)        /* 187 GCLK */
#define SEG_LENGTH__186                    (0x0000000000B9)        /* 186 GCLK */
#define SEG_LENGTH__185                    (0x0000000000B8)        /* 185 GCLK */
#define SEG_LENGTH__184                    (0x0000000000B7)        /* 184 GCLK */
#define SEG_LENGTH__183                    (0x0000000000B6)        /* 183 GCLK */
#define SEG_LENGTH__182                    (0x0000000000B5)        /* 182 GCLK */
#define SEG_LENGTH__181                    (0x0000000000B4)        /* 181 GCLK */
#define SEG_LENGTH__180                    (0x0000000000B3)        /* 180 GCLK */
#define SEG_LENGTH__179                    (0x0000000000B2)        /* 179 GCLK */
#define SEG_LENGTH__178                    (0x0000000000B1)        /* 178 GCLK */
#define SEG_LENGTH__177                    (0x0000000000B0)        /* 177 GCLK */
#define SEG_LENGTH__176                    (0x0000000000AF)        /* 176 GCLK */
#define SEG_LENGTH__175                    (0x0000000000AE)        /* 175 GCLK */
#define SEG_LENGTH__174                    (0x0000000000AD)        /* 174 GCLK */
#define SEG_LENGTH__173                    (0x0000000000AC)        /* 173 GCLK */
#define SEG_LENGTH__172                    (0x0000000000AB)        /* 172 GCLK */
#define SEG_LENGTH__171                    (0x0000000000AA)        /* 171 GCLK */
#define SEG_LENGTH__170                    (0x0000000000A9)        /* 170 GCLK */
#define SEG_LENGTH__169                    (0x0000000000A8)        /* 169 GCLK */
#define SEG_LENGTH__168                    (0x0000000000A7)        /* 168 GCLK */
#define SEG_LENGTH__167                    (0x0000000000A6)        /* 167 GCLK */
#define SEG_LENGTH__166                    (0x0000000000A5)        /* 166 GCLK */
#define SEG_LENGTH__165                    (0x0000000000A4)        /* 165 GCLK */
#define SEG_LENGTH__164                    (0x0000000000A3)        /* 164 GCLK */
#define SEG_LENGTH__163                    (0x0000000000A2)        /* 163 GCLK */
#define SEG_LENGTH__162                    (0x0000000000A1)        /* 162 GCLK */
#define SEG_LENGTH__161                    (0x0000000000A0)        /* 161 GCLK */
#define SEG_LENGTH__160                    (0x00000000009F)        /* 160 GCLK */
#define SEG_LENGTH__159                    (0x00000000009E)        /* 159 GCLK */
#define SEG_LENGTH__158                    (0x00000000009D)        /* 158 GCLK */
#define SEG_LENGTH__157                    (0x00000000009C)        /* 157 GCLK */
#define SEG_LENGTH__156                    (0x00000000009B)        /* 156 GCLK */
#define SEG_LENGTH__155                    (0x00000000009A)        /* 155 GCLK */
#define SEG_LENGTH__154                    (0x000000000099)        /* 154 GCLK */
#define SEG_LENGTH__153                    (0x000000000098)        /* 153 GCLK */
#define SEG_LENGTH__152                    (0x000000000097)        /* 152 GCLK */
#define SEG_LENGTH__151                    (0x000000000096)        /* 151 GCLK */
#define SEG_LENGTH__150                    (0x000000000095)        /* 150 GCLK */
#define SEG_LENGTH__149                    (0x000000000094)        /* 149 GCLK */
#define SEG_LENGTH__148                    (0x000000000093)        /* 148 GCLK */
#define SEG_LENGTH__147                    (0x000000000092)        /* 147 GCLK */
#define SEG_LENGTH__146                    (0x000000000091)        /* 146 GCLK */
#define SEG_LENGTH__145                    (0x000000000090)        /* 145 GCLK */
#define SEG_LENGTH__144                    (0x00000000008F)        /* 144 GCLK */
#define SEG_LENGTH__143                    (0x00000000008E)        /* 143 GCLK */
#define SEG_LENGTH__142                    (0x00000000008D)        /* 142 GCLK */
#define SEG_LENGTH__141                    (0x00000000008C)        /* 141 GCLK */
#define SEG_LENGTH__140                    (0x00000000008B)        /* 140 GCLK */
#define SEG_LENGTH__139                    (0x00000000008A)        /* 139 GCLK */
#define SEG_LENGTH__138                    (0x000000000089)        /* 138 GCLK */
#define SEG_LENGTH__137                    (0x000000000088)        /* 137 GCLK */
#define SEG_LENGTH__136                    (0x000000000087)        /* 136 GCLK */
#define SEG_LENGTH__135                    (0x000000000086)        /* 135 GCLK */
#define SEG_LENGTH__134                    (0x000000000085)        /* 134 GCLK */
#define SEG_LENGTH__133                    (0x000000000084)        /* 133 GCLK */
#define SEG_LENGTH__132                    (0x000000000083)        /* 132 GCLK */
#define SEG_LENGTH__131                    (0x000000000082)        /* 131 GCLK */
#define SEG_LENGTH__130                    (0x000000000081)        /* 130 GCLK */
#define SEG_LENGTH__129                    (0x000000000080)        /* 129 GCLK */
#define SEG_LENGTH__128                    (0x00000000007F)        /* 128 GCLK */

/* FC2  Bits */
#define MPSM_EN_1                          (0x800000000000)        /* enable */
#define MPSM_EN_0                          (0x000000000000)        /* disable */
#define MOD_SIZE_7                         (0x380000000000)        /* 4 devices stackable operation - mode8 D1->D4->D2->D3 */
#define MOD_SIZE_6                         (0x300000000000)        /* 4 devices stackable operation - mode7 D1->D2->D3->D4 */
#define MOD_SIZE_5                         (0x280000000000)        /* 3 devices stackable operation - mode6 D1->D3->D2 */
#define MOD_SIZE_4                         (0x200000000000)        /* 3 devices stackable operation - mode5 D1->D2->D3 */
#define MOD_SIZE_3                         (0x180000000000)        /* 3 devices stackable operation - mode4 D1->D3->D2 */
#define MOD_SIZE_2                         (0x100000000000)        /* 3 devices stackable operation - mode3 D1->D2->D3 */
#define MOD_SIZE_1                         (0x080000000000)        /* 2 devices stackable operation */
#define MOD_SIZE_0                         (0x000000000000)        /* 1 device non-stackable operation, SCAN_NUM must <=16 */
#define MOD_SIZE__4_8                      (0x380000000000)        /* 4 devices stackable operation - mode8 D1->D4->D2->D3 */
#define MOD_SIZE__4_7                      (0x300000000000)        /* 4 devices stackable operation - mode7 D1->D2->D3->D4 */
#define MOD_SIZE__3_6                      (0x280000000000)        /* 3 devices stackable operation - mode6 D1->D3->D2 */
#define MOD_SIZE__3_5                      (0x200000000000)        /* 3 devices stackable operation - mode5 D1->D2->D3 */
#define MOD_SIZE__3_4                      (0x180000000000)        /* 3 devices stackable operation - mode4 D1->D3->D2 */
#define MOD_SIZE__3_3                      (0x100000000000)        /* 3 devices stackable operation - mode3 D1->D2->D3 */
#define MOD_SIZE__2                        (0x080000000000)        /* 2 devices stackable operation */
#define MOD_SIZE__1                        (0x000000000000)        /* 1 device non-stackable operation, SCAN_NUM must <=16 */
#define SUBP_MAX_256_1                     (0x040000000000)        /* enable */
#define SUBP_MAX_256_0                     (0x000000000000)        /* disable */
#define SUBP_MAX_256__1                    (0x040000000000)        /* enable */
#define SUBP_MAX_256__0                    (0x000000000000)        /* disable */
#define CH_B_IMMUNITY_1                    (0x020000000000)        /* low immunity */
#define CH_B_IMMUNITY_0                    (0x000000000000)        /* high immunity */
#define CH_B_IMMUNITY__1                   (0x020000000000)        /* low immunity */
#define CH_B_IMMUNITY__0                   (0x000000000000)        /* high immunity */
#define CH_G_IMMUNITY_1                    (0x010000000000)        /* low immunity */
#define CH_G_IMMUNITY_0                    (0x000000000000)        /* high immunity */
#define CH_G_IMMUNITY__1                   (0x010000000000)        /* low immunity */
#define CH_G_IMMUNITY__0                   (0x000000000000)        /* high immunity */
#define CH_R_IMMUNITY_1                    (0x008000000000)        /* low immunity */
#define CH_R_IMMUNITY_0                    (0x000000000000)        /* high immunity */
#define CH_R_IMMUNITY__1                   (0x008000000000)        /* low immunity */
#define CH_R_IMMUNITY__0                   (0x000000000000)        /* high immunity */
#define LG_COLOR_B__16                     (0x000F00000000)        /* 16 */
#define LG_COLOR_B__15                     (0x000E00000000)        /* 15 */
#define LG_COLOR_B__14                     (0x000D00000000)        /* 14 */
#define LG_COLOR_B__13                     (0x000C00000000)        /* 13 */
#define LG_COLOR_B__12                     (0x000B00000000)        /* 12 */
#define LG_COLOR_B__11                     (0x000A00000000)        /* 11 */
#define LG_COLOR_B__10                     (0x000900000000)        /* 10 */
#define LG_COLOR_B__9                      (0x000800000000)        /* 9 */
#define LG_COLOR_B__8                      (0x000700000000)        /* 8 */
#define LG_COLOR_B__7                      (0x000600000000)        /* 7 */
#define LG_COLOR_B__6                      (0x000500000000)        /* 6 */
#define LG_COLOR_B__5                      (0x000400000000)        /* 5 */
#define LG_COLOR_B__4                      (0x000300000000)        /* 4 */
#define LG_COLOR_B__3                      (0x000200000000)        /* 3 */
#define LG_COLOR_B__2                      (0x000100000000)        /* 2 */
#define LG_COLOR_B__1                      (0x000000000000)        /* 1 */
#define LG_COLOR_G__16                     (0x0000F0000000)        /* 16 */
#define LG_COLOR_G__15                     (0x0000E0000000)        /* 15 */
#define LG_COLOR_G__14                     (0x0000D0000000)        /* 14 */
#define LG_COLOR_G__13                     (0x0000C0000000)        /* 13 */
#define LG_COLOR_G__12                     (0x0000B0000000)        /* 12 */
#define LG_COLOR_G__11                     (0x0000A0000000)        /* 11 */
#define LG_COLOR_G__10                     (0x000090000000)        /* 10 */
#define LG_COLOR_G__9                      (0x000080000000)        /* 9 */
#define LG_COLOR_G__8                      (0x000070000000)        /* 8 */
#define LG_COLOR_G__7                      (0x000060000000)        /* 7 */
#define LG_COLOR_G__6                      (0x000050000000)        /* 6 */
#define LG_COLOR_G__5                      (0x000040000000)        /* 5 */
#define LG_COLOR_G__4                      (0x000030000000)        /* 4 */
#define LG_COLOR_G__3                      (0x000020000000)        /* 3 */
#define LG_COLOR_G__2                      (0x000010000000)        /* 2 */
#define LG_COLOR_G__1                      (0x000000000000)        /* 1 */
#define LG_COLOR_R__16                     (0x00000F000000)        /* 16 */
#define LG_COLOR_R__15                     (0x00000E000000)        /* 15 */
#define LG_COLOR_R__14                     (0x00000D000000)        /* 14 */
#define LG_COLOR_R__13                     (0x00000C000000)        /* 13 */
#define LG_COLOR_R__12                     (0x00000B000000)        /* 12 */
#define LG_COLOR_R__11                     (0x00000A000000)        /* 11 */
#define LG_COLOR_R__10                     (0x000009000000)        /* 10 */
#define LG_COLOR_R__9                      (0x000008000000)        /* 9 */
#define LG_COLOR_R__8                      (0x000007000000)        /* 8 */
#define LG_COLOR_R__7                      (0x000006000000)        /* 7 */
#define LG_COLOR_R__6                      (0x000005000000)        /* 6 */
#define LG_COLOR_R__5                      (0x000004000000)        /* 5 */
#define LG_COLOR_R__4                      (0x000003000000)        /* 4 */
#define LG_COLOR_R__3                      (0x000002000000)        /* 3 */
#define LG_COLOR_R__2                      (0x000001000000)        /* 2 */
#define LG_COLOR_R__1                      (0x000000000000)        /* 1 */
#define COLOR_B__16                        (0x000F00000000)        /* 16 */
#define COLOR_B__15                        (0x000E00000000)        /* 15 */
#define COLOR_B__14                        (0x000D00000000)        /* 14 */
#define COLOR_B__13                        (0x000C00000000)        /* 13 */
#define COLOR_B__12                        (0x000B00000000)        /* 12 */
#define COLOR_B__11                        (0x000A00000000)        /* 11 */
#define COLOR_B__10                        (0x000900000000)        /* 10 */
#define COLOR_B__9                         (0x000800000000)        /* 9 */
#define COLOR_B__8                         (0x000700000000)        /* 8 */
#define COLOR_B__7                         (0x000600000000)        /* 7 */
#define COLOR_B__6                         (0x000500000000)        /* 6 */
#define COLOR_B__5                         (0x000400000000)        /* 5 */
#define COLOR_B__4                         (0x000300000000)        /* 4 */
#define COLOR_B__3                         (0x000200000000)        /* 3 */
#define COLOR_B__2                         (0x000100000000)        /* 2 */
#define COLOR_B__1                         (0x000000000000)        /* 1 */
#define COLOR_G__16                        (0x0000F0000000)        /* 16 */
#define COLOR_G__15                        (0x0000E0000000)        /* 15 */
#define COLOR_G__14                        (0x0000D0000000)        /* 14 */
#define COLOR_G__13                        (0x0000C0000000)        /* 13 */
#define COLOR_G__12                        (0x0000B0000000)        /* 12 */
#define COLOR_G__11                        (0x0000A0000000)        /* 11 */
#define COLOR_G__10                        (0x000090000000)        /* 10 */
#define COLOR_G__9                         (0x000080000000)        /* 9 */
#define COLOR_G__8                         (0x000070000000)        /* 8 */
#define COLOR_G__7                         (0x000060000000)        /* 7 */
#define COLOR_G__6                         (0x000050000000)        /* 6 */
#define COLOR_G__5                         (0x000040000000)        /* 5 */
#define COLOR_G__4                         (0x000030000000)        /* 4 */
#define COLOR_G__3                         (0x000020000000)        /* 3 */
#define COLOR_G__2                         (0x000010000000)        /* 2 */
#define COLOR_G__1                         (0x000000000000)        /* 1 */
#define COLOR_R__16                        (0x00000F000000)        /* 16 */
#define COLOR_R__15                        (0x00000E000000)        /* 15 */
#define COLOR_R__14                        (0x00000D000000)        /* 14 */
#define COLOR_R__13                        (0x00000C000000)        /* 13 */
#define COLOR_R__12                        (0x00000B000000)        /* 12 */
#define COLOR_R__11                        (0x00000A000000)        /* 11 */
#define COLOR_R__10                        (0x000009000000)        /* 10 */
#define COLOR_R__9                         (0x000008000000)        /* 9 */
#define COLOR_R__8                         (0x000007000000)        /* 8 */
#define COLOR_R__7                         (0x000006000000)        /* 7 */
#define COLOR_R__6                         (0x000005000000)        /* 6 */
#define COLOR_R__5                         (0x000004000000)        /* 5 */
#define COLOR_R__4                         (0x000003000000)        /* 4 */
#define COLOR_R__3                         (0x000002000000)        /* 3 */
#define COLOR_R__2                         (0x000001000000)        /* 2 */
#define COLOR_R__1                         (0x000000000000)        /* 1 */
#define DE_COUPLE1_B__16                   (0x000000F00000)        /* 16 */
#define DE_COUPLE1_B__15                   (0x000000E00000)        /* 15 */
#define DE_COUPLE1_B__14                   (0x000000D00000)        /* 14 */
#define DE_COUPLE1_B__13                   (0x000000C00000)        /* 13 */
#define DE_COUPLE1_B__12                   (0x000000B00000)        /* 12 */
#define DE_COUPLE1_B__11                   (0x000000A00000)        /* 11 */
#define DE_COUPLE1_B__10                   (0x000000900000)        /* 10 */
#define DE_COUPLE1_B__9                    (0x000000800000)        /* 9 */
#define DE_COUPLE1_B__8                    (0x000000700000)        /* 8 */
#define DE_COUPLE1_B__7                    (0x000000600000)        /* 7 */
#define DE_COUPLE1_B__6                    (0x000000500000)        /* 6 */
#define DE_COUPLE1_B__5                    (0x000000400000)        /* 5 */
#define DE_COUPLE1_B__4                    (0x000000300000)        /* 4 */
#define DE_COUPLE1_B__3                    (0x000000200000)        /* 3 */
#define DE_COUPLE1_B__2                    (0x000000100000)        /* 2 */
#define DE_COUPLE1_B__1                    (0x000000000000)        /* 1 */
#define DE_COUPLE1_G__16                   (0x0000000F0000)        /* 16 */
#define DE_COUPLE1_G__15                   (0x0000000E0000)        /* 15 */
#define DE_COUPLE1_G__14                   (0x0000000D0000)        /* 14 */
#define DE_COUPLE1_G__13                   (0x0000000C0000)        /* 13 */
#define DE_COUPLE1_G__12                   (0x0000000B0000)        /* 12 */
#define DE_COUPLE1_G__11                   (0x0000000A0000)        /* 11 */
#define DE_COUPLE1_G__10                   (0x000000090000)        /* 10 */
#define DE_COUPLE1_G__9                    (0x000000080000)        /* 9 */
#define DE_COUPLE1_G__8                    (0x000000070000)        /* 8 */
#define DE_COUPLE1_G__7                    (0x000000060000)        /* 7 */
#define DE_COUPLE1_G__6                    (0x000000050000)        /* 6 */
#define DE_COUPLE1_G__5                    (0x000000040000)        /* 5 */
#define DE_COUPLE1_G__4                    (0x000000030000)        /* 4 */
#define DE_COUPLE1_G__3                    (0x000000020000)        /* 3 */
#define DE_COUPLE1_G__2                    (0x000000010000)        /* 2 */
#define DE_COUPLE1_G__1                    (0x000000000000)        /* 1 */
#define DE_COUPLE1_R__16                   (0x00000000F000)        /* 16 */
#define DE_COUPLE1_R__15                   (0x00000000E000)        /* 15 */
#define DE_COUPLE1_R__14                   (0x00000000D000)        /* 14 */
#define DE_COUPLE1_R__13                   (0x00000000C000)        /* 13 */
#define DE_COUPLE1_R__12                   (0x00000000B000)        /* 12 */
#define DE_COUPLE1_R__11                   (0x00000000A000)        /* 11 */
#define DE_COUPLE1_R__10                   (0x000000009000)        /* 10 */
#define DE_COUPLE1_R__9                    (0x000000008000)        /* 9 */
#define DE_COUPLE1_R__8                    (0x000000007000)        /* 8 */
#define DE_COUPLE1_R__7                    (0x000000006000)        /* 7 */
#define DE_COUPLE1_R__6                    (0x000000005000)        /* 6 */
#define DE_COUPLE1_R__5                    (0x000000004000)        /* 5 */
#define DE_COUPLE1_R__4                    (0x000000003000)        /* 4 */
#define DE_COUPLE1_R__3                    (0x000000002000)        /* 3 */
#define DE_COUPLE1_R__2                    (0x000000001000)        /* 2 */
#define DE_COUPLE1_R__1                    (0x000000000000)        /* 1 */
#define V_PDC_B__2V1                       (0x000000000F00)        /* 2.1 V */
#define V_PDC_B__1V9                       (0x000000000E00)        /* 1.9 V */
#define V_PDC_B__1V7                       (0x000000000D00)        /* 1.7 V */
#define V_PDC_B__1V5                       (0x000000000C00)        /* 1.5 V */
#define V_PDC_B__1V3                       (0x000000000B00)        /* 1.3 V */
#define V_PDC_B__1V1                       (0x000000000A00)        /* 1.1 V */
#define V_PDC_B__1V0                       (0x000000000900)        /* 1 V */
#define V_PDC_B__0V9                       (0x000000000800)        /* 0.9 V */
#define V_PDC_B__0V8                       (0x000000000700)        /* 0.8 V */
#define V_PDC_B__0V7                       (0x000000000600)        /* 0.7 V */
#define V_PDC_B__0V6                       (0x000000000500)        /* 0.6 V */
#define V_PDC_B__0V5                       (0x000000000400)        /* 0.5 V */
#define V_PDC_B__0V4                       (0x000000000300)        /* 0.4 V */
#define V_PDC_B__0V3                       (0x000000000200)        /* 0.3 V */
#define V_PDC_B__0V2                       (0x000000000100)        /* 0.2 V */
#define V_PDC_B__0V1                       (0x000000000000)        /* 0.1 V */
#define V_PDC_G__2V1                       (0x0000000000F0)        /* 2.1 V */
#define V_PDC_G__1V9                       (0x0000000000E0)        /* 1.9 V */
#define V_PDC_G__1V7                       (0x0000000000D0)        /* 1.7 V */
#define V_PDC_G__1V5                       (0x0000000000C0)        /* 1.5 V */
#define V_PDC_G__1V3                       (0x0000000000B0)        /* 1.3 V */
#define V_PDC_G__1V1                       (0x0000000000A0)        /* 1.1 V */
#define V_PDC_G__1V0                       (0x000000000090)        /* 1 V */
#define V_PDC_G__0V9                       (0x000000000080)        /* 0.9 V */
#define V_PDC_G__0V8                       (0x000000000070)        /* 0.8 V */
#define V_PDC_G__0V7                       (0x000000000060)        /* 0.7 V */
#define V_PDC_G__0V6                       (0x000000000050)        /* 0.6 V */
#define V_PDC_G__0V5                       (0x000000000040)        /* 0.5 V */
#define V_PDC_G__0V4                       (0x000000000030)        /* 0.4 V */
#define V_PDC_G__0V3                       (0x000000000020)        /* 0.3 V */
#define V_PDC_G__0V2                       (0x000000000010)        /* 0.2 V */
#define V_PDC_G__0V1                       (0x000000000000)        /* 0.1 V */
#define V_PDC_R__2V1                       (0x00000000000F)        /* 2.1 V */
#define V_PDC_R__1V9                       (0x00000000000E)        /* 1.9 V */
#define V_PDC_R__1V7                       (0x00000000000D)        /* 1.7 V */
#define V_PDC_R__1V5                       (0x00000000000C)        /* 1.5 V */
#define V_PDC_R__1V3                       (0x00000000000B)        /* 1.3 V */
#define V_PDC_R__1V1                       (0x00000000000A)        /* 1.1 V */
#define V_PDC_R__1V0                       (0x000000000009)        /* 1 V */
#define V_PDC_R__0V9                       (0x000000000008)        /* 0.9 V */
#define V_PDC_R__0V8                       (0x000000000007)        /* 0.8 V */
#define V_PDC_R__0V7                       (0x000000000006)        /* 0.7 V */
#define V_PDC_R__0V6                       (0x000000000005)        /* 0.6 V */
#define V_PDC_R__0V5                       (0x000000000004)        /* 0.5 V */
#define V_PDC_R__0V4                       (0x000000000003)        /* 0.4 V */
#define V_PDC_R__0V3                       (0x000000000002)        /* 0.3 V */
#define V_PDC_R__0V2                       (0x000000000001)        /* 0.2 V */
#define V_PDC_R__0V1                       (0x000000000000)        /* 0.1 V */

/* FC3  Bits */
#define LSDVTH_B__2V8                      (0xE00000000000)        /* 2.8 V */
#define LSDVTH_B__2V4                      (0xC00000000000)        /* 2.4 V */
#define LSDVTH_B__2V0                      (0xA00000000000)        /* 2 V */
#define LSDVTH_B__1V6                      (0x800000000000)        /* 1.6 V */
#define LSDVTH_B__1V2                      (0x600000000000)        /* 1.2 V */
#define LSDVTH_B__0V8                      (0x400000000000)        /* 0.8 V */
#define LSDVTH_B__0V4                      (0x200000000000)        /* 0.4 V */
#define LSDVTH_B__0V2                      (0x000000000000)        /* 0.2 V */
#define LSDVTH_G__2V8                      (0x1C0000000000)        /* 2.8 V */
#define LSDVTH_G__2V4                      (0x180000000000)        /* 2.4 V */
#define LSDVTH_G__2V0                      (0x140000000000)        /* 2 V */
#define LSDVTH_G__1V6                      (0x100000000000)        /* 1.6 V */
#define LSDVTH_G__1V2                      (0x0C0000000000)        /* 1.2 V */
#define LSDVTH_G__0V8                      (0x080000000000)        /* 0.8 V */
#define LSDVTH_G__0V4                      (0x040000000000)        /* 0.4 V */
#define LSDVTH_G__0V2                      (0x000000000000)        /* 0.2 V */
#define LSDVTH_R__2V8                      (0x038000000000)        /* 2.8 V */
#define LSDVTH_R__2V4                      (0x030000000000)        /* 2.4 V */
#define LSDVTH_R__2V0                      (0x028000000000)        /* 2 V */
#define LSDVTH_R__1V6                      (0x020000000000)        /* 1.6 V */
#define LSDVTH_R__1V2                      (0x018000000000)        /* 1.2 V */
#define LSDVTH_R__0V8                      (0x010000000000)        /* 0.8 V */
#define LSDVTH_R__0V4                      (0x008000000000)        /* 0.4 V */
#define LSDVTH_R__0V2                      (0x000000000000)        /* 0.2 V */
#define LSD_RM__16                         (0x007800000000)        /* 16 */
#define LSD_RM__15                         (0x007000000000)        /* 15 */
#define LSD_RM__14                         (0x006800000000)        /* 14 */
#define LSD_RM__13                         (0x006000000000)        /* 13 */
#define LSD_RM__12                         (0x005800000000)        /* 12 */
#define LSD_RM__11                         (0x005000000000)        /* 11 */
#define LSD_RM__10                         (0x004800000000)        /* 10 */
#define LSD_RM__9                          (0x004000000000)        /* 9 */
#define LSD_RM__8                          (0x003800000000)        /* 8 */
#define LSD_RM__7                          (0x003000000000)        /* 7 */
#define LSD_RM__6                          (0x002800000000)        /* 6 */
#define LSD_RM__5                          (0x002000000000)        /* 5 */
#define LSD_RM__4                          (0x001800000000)        /* 4 */
#define LSD_RM__3                          (0x001000000000)        /* 3 */
#define LSD_RM__2                          (0x000800000000)        /* 2 */
#define LSD_RM__1                          (0x000000000000)        /* 1 */
#define BC_7                               (0x000700000000)        /* 7 */
#define BC_6                               (0x000600000000)        /* 6 */
#define BC_5                               (0x000500000000)        /* 5 */
#define BC_4                               (0x000400000000)        /* 4 */
#define BC_3                               (0x000300000000)        /* 3 */
#define BC_2                               (0x000200000000)        /* 2 */
#define BC_1                               (0x000100000000)        /* 1 */
#define BC_0                               (0x000000000000)        /* 0 */
#define BC__7                              (0x000700000000)        /* 7 */
#define BC__6                              (0x000600000000)        /* 6 */
#define BC__5                              (0x000500000000)        /* 5 */
#define BC__4                              (0x000400000000)        /* 4 */
#define BC__3                              (0x000300000000)        /* 3 */
#define BC__2                              (0x000200000000)        /* 2 */
#define BC__1                              (0x000100000000)        /* 1 */
#define BC__0                              (0x000000000000)        /* 0 */
#define CC_B_255                           (0x0000FF000000)        /* 255 */
#define CC_B_254                           (0x0000FE000000)        /* 254 */
#define CC_B_253                           (0x0000FD000000)        /* 253 */
#define CC_B_252                           (0x0000FC000000)        /* 252 */
#define CC_B_251                           (0x0000FB000000)        /* 251 */
#define CC_B_250                           (0x0000FA000000)        /* 250 */
#define CC_B_249                           (0x0000F9000000)        /* 249 */
#define CC_B_248                           (0x0000F8000000)        /* 248 */
#define CC_B_247                           (0x0000F7000000)        /* 247 */
#define CC_B_246                           (0x0000F6000000)        /* 246 */
#define CC_B_245                           (0x0000F5000000)        /* 245 */
#define CC_B_244                           (0x0000F4000000)        /* 244 */
#define CC_B_243                           (0x0000F3000000)        /* 243 */
#define CC_B_242                           (0x0000F2000000)        /* 242 */
#define CC_B_241                           (0x0000F1000000)        /* 241 */
#define CC_B_240                           (0x0000F0000000)        /* 240 */
#define CC_B_239                           (0x0000EF000000)        /* 239 */
#define CC_B_238                           (0x0000EE000000)        /* 238 */
#define CC_B_237                           (0x0000ED000000)        /* 237 */
#define CC_B_236                           (0x0000EC000000)        /* 236 */
#define CC_B_235                           (0x0000EB000000)        /* 235 */
#define CC_B_234                           (0x0000EA000000)        /* 234 */
#define CC_B_233                           (0x0000E9000000)        /* 233 */
#define CC_B_232                           (0x0000E8000000)        /* 232 */
#define CC_B_231                           (0x0000E7000000)        /* 231 */
#define CC_B_230                           (0x0000E6000000)        /* 230 */
#define CC_B_229                           (0x0000E5000000)        /* 229 */
#define CC_B_228                           (0x0000E4000000)        /* 228 */
#define CC_B_227                           (0x0000E3000000)        /* 227 */
#define CC_B_226                           (0x0000E2000000)        /* 226 */
#define CC_B_225                           (0x0000E1000000)        /* 225 */
#define CC_B_224                           (0x0000E0000000)        /* 224 */
#define CC_B_223                           (0x0000DF000000)        /* 223 */
#define CC_B_222                           (0x0000DE000000)        /* 222 */
#define CC_B_221                           (0x0000DD000000)        /* 221 */
#define CC_B_220                           (0x0000DC000000)        /* 220 */
#define CC_B_219                           (0x0000DB000000)        /* 219 */
#define CC_B_218                           (0x0000DA000000)        /* 218 */
#define CC_B_217                           (0x0000D9000000)        /* 217 */
#define CC_B_216                           (0x0000D8000000)        /* 216 */
#define CC_B_215                           (0x0000D7000000)        /* 215 */
#define CC_B_214                           (0x0000D6000000)        /* 214 */
#define CC_B_213                           (0x0000D5000000)        /* 213 */
#define CC_B_212                           (0x0000D4000000)        /* 212 */
#define CC_B_211                           (0x0000D3000000)        /* 211 */
#define CC_B_210                           (0x0000D2000000)        /* 210 */
#define CC_B_209                           (0x0000D1000000)        /* 209 */
#define CC_B_208                           (0x0000D0000000)        /* 208 */
#define CC_B_207                           (0x0000CF000000)        /* 207 */
#define CC_B_206                           (0x0000CE000000)        /* 206 */
#define CC_B_205                           (0x0000CD000000)        /* 205 */
#define CC_B_204                           (0x0000CC000000)        /* 204 */
#define CC_B_203                           (0x0000CB000000)        /* 203 */
#define CC_B_202                           (0x0000CA000000)        /* 202 */
#define CC_B_201                           (0x0000C9000000)        /* 201 */
#define CC_B_200                           (0x0000C8000000)        /* 200 */
#define CC_B_199                           (0x0000C7000000)        /* 199 */
#define CC_B_198                           (0x0000C6000000)        /* 198 */
#define CC_B_197                           (0x0000C5000000)        /* 197 */
#define CC_B_196                           (0x0000C4000000)        /* 196 */
#define CC_B_195                           (0x0000C3000000)        /* 195 */
#define CC_B_194                           (0x0000C2000000)        /* 194 */
#define CC_B_193                           (0x0000C1000000)        /* 193 */
#define CC_B_192                           (0x0000C0000000)        /* 192 */
#define CC_B_191                           (0x0000BF000000)        /* 191 */
#define CC_B_190                           (0x0000BE000000)        /* 190 */
#define CC_B_189                           (0x0000BD000000)        /* 189 */
#define CC_B_188                           (0x0000BC000000)        /* 188 */
#define CC_B_187                           (0x0000BB000000)        /* 187 */
#define CC_B_186                           (0x0000BA000000)        /* 186 */
#define CC_B_185                           (0x0000B9000000)        /* 185 */
#define CC_B_184                           (0x0000B8000000)        /* 184 */
#define CC_B_183                           (0x0000B7000000)        /* 183 */
#define CC_B_182                           (0x0000B6000000)        /* 182 */
#define CC_B_181                           (0x0000B5000000)        /* 181 */
#define CC_B_180                           (0x0000B4000000)        /* 180 */
#define CC_B_179                           (0x0000B3000000)        /* 179 */
#define CC_B_178                           (0x0000B2000000)        /* 178 */
#define CC_B_177                           (0x0000B1000000)        /* 177 */
#define CC_B_176                           (0x0000B0000000)        /* 176 */
#define CC_B_175                           (0x0000AF000000)        /* 175 */
#define CC_B_174                           (0x0000AE000000)        /* 174 */
#define CC_B_173                           (0x0000AD000000)        /* 173 */
#define CC_B_172                           (0x0000AC000000)        /* 172 */
#define CC_B_171                           (0x0000AB000000)        /* 171 */
#define CC_B_170                           (0x0000AA000000)        /* 170 */
#define CC_B_169                           (0x0000A9000000)        /* 169 */
#define CC_B_168                           (0x0000A8000000)        /* 168 */
#define CC_B_167                           (0x0000A7000000)        /* 167 */
#define CC_B_166                           (0x0000A6000000)        /* 166 */
#define CC_B_165                           (0x0000A5000000)        /* 165 */
#define CC_B_164                           (0x0000A4000000)        /* 164 */
#define CC_B_163                           (0x0000A3000000)        /* 163 */
#define CC_B_162                           (0x0000A2000000)        /* 162 */
#define CC_B_161                           (0x0000A1000000)        /* 161 */
#define CC_B_160                           (0x0000A0000000)        /* 160 */
#define CC_B_159                           (0x00009F000000)        /* 159 */
#define CC_B_158                           (0x00009E000000)        /* 158 */
#define CC_B_157                           (0x00009D000000)        /* 157 */
#define CC_B_156                           (0x00009C000000)        /* 156 */
#define CC_B_155                           (0x00009B000000)        /* 155 */
#define CC_B_154                           (0x00009A000000)        /* 154 */
#define CC_B_153                           (0x000099000000)        /* 153 */
#define CC_B_152                           (0x000098000000)        /* 152 */
#define CC_B_151                           (0x000097000000)        /* 151 */
#define CC_B_150                           (0x000096000000)        /* 150 */
#define CC_B_149                           (0x000095000000)        /* 149 */
#define CC_B_148                           (0x000094000000)        /* 148 */
#define CC_B_147                           (0x000093000000)        /* 147 */
#define CC_B_146                           (0x000092000000)        /* 146 */
#define CC_B_145                           (0x000091000000)        /* 145 */
#define CC_B_144                           (0x000090000000)        /* 144 */
#define CC_B_143                           (0x00008F000000)        /* 143 */
#define CC_B_142                           (0x00008E000000)        /* 142 */
#define CC_B_141                           (0x00008D000000)        /* 141 */
#define CC_B_140                           (0x00008C000000)        /* 140 */
#define CC_B_139                           (0x00008B000000)        /* 139 */
#define CC_B_138                           (0x00008A000000)        /* 138 */
#define CC_B_137                           (0x000089000000)        /* 137 */
#define CC_B_136                           (0x000088000000)        /* 136 */
#define CC_B_135                           (0x000087000000)        /* 135 */
#define CC_B_134                           (0x000086000000)        /* 134 */
#define CC_B_133                           (0x000085000000)        /* 133 */
#define CC_B_132                           (0x000084000000)        /* 132 */
#define CC_B_131                           (0x000083000000)        /* 131 */
#define CC_B_130                           (0x000082000000)        /* 130 */
#define CC_B_129                           (0x000081000000)        /* 129 */
#define CC_B_128                           (0x000080000000)        /* 128 */
#define CC_B_127                           (0x00007F000000)        /* 127 */
#define CC_B_126                           (0x00007E000000)        /* 126 */
#define CC_B_125                           (0x00007D000000)        /* 125 */
#define CC_B_124                           (0x00007C000000)        /* 124 */
#define CC_B_123                           (0x00007B000000)        /* 123 */
#define CC_B_122                           (0x00007A000000)        /* 122 */
#define CC_B_121                           (0x000079000000)        /* 121 */
#define CC_B_120                           (0x000078000000)        /* 120 */
#define CC_B_119                           (0x000077000000)        /* 119 */
#define CC_B_118                           (0x000076000000)        /* 118 */
#define CC_B_117                           (0x000075000000)        /* 117 */
#define CC_B_116                           (0x000074000000)        /* 116 */
#define CC_B_115                           (0x000073000000)        /* 115 */
#define CC_B_114                           (0x000072000000)        /* 114 */
#define CC_B_113                           (0x000071000000)        /* 113 */
#define CC_B_112                           (0x000070000000)        /* 112 */
#define CC_B_111                           (0x00006F000000)        /* 111 */
#define CC_B_110                           (0x00006E000000)        /* 110 */
#define CC_B_109                           (0x00006D000000)        /* 109 */
#define CC_B_108                           (0x00006C000000)        /* 108 */
#define CC_B_107                           (0x00006B000000)        /* 107 */
#define CC_B_106                           (0x00006A000000)        /* 106 */
#define CC_B_105                           (0x000069000000)        /* 105 */
#define CC_B_104                           (0x000068000000)        /* 104 */
#define CC_B_103                           (0x000067000000)        /* 103 */
#define CC_B_102                           (0x000066000000)        /* 102 */
#define CC_B_101                           (0x000065000000)        /* 101 */
#define CC_B_100                           (0x000064000000)        /* 100 */
#define CC_B_99                            (0x000063000000)        /* 99 */
#define CC_B_98                            (0x000062000000)        /* 98 */
#define CC_B_97                            (0x000061000000)        /* 97 */
#define CC_B_96                            (0x000060000000)        /* 96 */
#define CC_B_95                            (0x00005F000000)        /* 95 */
#define CC_B_94                            (0x00005E000000)        /* 94 */
#define CC_B_93                            (0x00005D000000)        /* 93 */
#define CC_B_92                            (0x00005C000000)        /* 92 */
#define CC_B_91                            (0x00005B000000)        /* 91 */
#define CC_B_90                            (0x00005A000000)        /* 90 */
#define CC_B_89                            (0x000059000000)        /* 89 */
#define CC_B_88                            (0x000058000000)        /* 88 */
#define CC_B_87                            (0x000057000000)        /* 87 */
#define CC_B_86                            (0x000056000000)        /* 86 */
#define CC_B_85                            (0x000055000000)        /* 85 */
#define CC_B_84                            (0x000054000000)        /* 84 */
#define CC_B_83                            (0x000053000000)        /* 83 */
#define CC_B_82                            (0x000052000000)        /* 82 */
#define CC_B_81                            (0x000051000000)        /* 81 */
#define CC_B_80                            (0x000050000000)        /* 80 */
#define CC_B_79                            (0x00004F000000)        /* 79 */
#define CC_B_78                            (0x00004E000000)        /* 78 */
#define CC_B_77                            (0x00004D000000)        /* 77 */
#define CC_B_76                            (0x00004C000000)        /* 76 */
#define CC_B_75                            (0x00004B000000)        /* 75 */
#define CC_B_74                            (0x00004A000000)        /* 74 */
#define CC_B_73                            (0x000049000000)        /* 73 */
#define CC_B_72                            (0x000048000000)        /* 72 */
#define CC_B_71                            (0x000047000000)        /* 71 */
#define CC_B_70                            (0x000046000000)        /* 70 */
#define CC_B_69                            (0x000045000000)        /* 69 */
#define CC_B_68                            (0x000044000000)        /* 68 */
#define CC_B_67                            (0x000043000000)        /* 67 */
#define CC_B_66                            (0x000042000000)        /* 66 */
#define CC_B_65                            (0x000041000000)        /* 65 */
#define CC_B_64                            (0x000040000000)        /* 64 */
#define CC_B_63                            (0x00003F000000)        /* 63 */
#define CC_B_62                            (0x00003E000000)        /* 62 */
#define CC_B_61                            (0x00003D000000)        /* 61 */
#define CC_B_60                            (0x00003C000000)        /* 60 */
#define CC_B_59                            (0x00003B000000)        /* 59 */
#define CC_B_58                            (0x00003A000000)        /* 58 */
#define CC_B_57                            (0x000039000000)        /* 57 */
#define CC_B_56                            (0x000038000000)        /* 56 */
#define CC_B_55                            (0x000037000000)        /* 55 */
#define CC_B_54                            (0x000036000000)        /* 54 */
#define CC_B_53                            (0x000035000000)        /* 53 */
#define CC_B_52                            (0x000034000000)        /* 52 */
#define CC_B_51                            (0x000033000000)        /* 51 */
#define CC_B_50                            (0x000032000000)        /* 50 */
#define CC_B_49                            (0x000031000000)        /* 49 */
#define CC_B_48                            (0x000030000000)        /* 48 */
#define CC_B_47                            (0x00002F000000)        /* 47 */
#define CC_B_46                            (0x00002E000000)        /* 46 */
#define CC_B_45                            (0x00002D000000)        /* 45 */
#define CC_B_44                            (0x00002C000000)        /* 44 */
#define CC_B_43                            (0x00002B000000)        /* 43 */
#define CC_B_42                            (0x00002A000000)        /* 42 */
#define CC_B_41                            (0x000029000000)        /* 41 */
#define CC_B_40                            (0x000028000000)        /* 40 */
#define CC_B_39                            (0x000027000000)        /* 39 */
#define CC_B_38                            (0x000026000000)        /* 38 */
#define CC_B_37                            (0x000025000000)        /* 37 */
#define CC_B_36                            (0x000024000000)        /* 36 */
#define CC_B_35                            (0x000023000000)        /* 35 */
#define CC_B_34                            (0x000022000000)        /* 34 */
#define CC_B_33                            (0x000021000000)        /* 33 */
#define CC_B_32                            (0x000020000000)        /* 32 */
#define CC_B_31                            (0x00001F000000)        /* 31 */
#define CC_B_30                            (0x00001E000000)        /* 30 */
#define CC_B_29                            (0x00001D000000)        /* 29 */
#define CC_B_28                            (0x00001C000000)        /* 28 */
#define CC_B_27                            (0x00001B000000)        /* 27 */
#define CC_B_26                            (0x00001A000000)        /* 26 */
#define CC_B_25                            (0x000019000000)        /* 25 */
#define CC_B_24                            (0x000018000000)        /* 24 */
#define CC_B_23                            (0x000017000000)        /* 23 */
#define CC_B_22                            (0x000016000000)        /* 22 */
#define CC_B_21                            (0x000015000000)        /* 21 */
#define CC_B_20                            (0x000014000000)        /* 20 */
#define CC_B_19                            (0x000013000000)        /* 19 */
#define CC_B_18                            (0x000012000000)        /* 18 */
#define CC_B_17                            (0x000011000000)        /* 17 */
#define CC_B_16                            (0x000010000000)        /* 16 */
#define CC_B_15                            (0x00000F000000)        /* 15 */
#define CC_B_14                            (0x00000E000000)        /* 14 */
#define CC_B_13                            (0x00000D000000)        /* 13 */
#define CC_B_12                            (0x00000C000000)        /* 12 */
#define CC_B_11                            (0x00000B000000)        /* 11 */
#define CC_B_10                            (0x00000A000000)        /* 10 */
#define CC_B_9                             (0x000009000000)        /* 9 */
#define CC_B_8                             (0x000008000000)        /* 8 */
#define CC_B_7                             (0x000007000000)        /* 7 */
#define CC_B_6                             (0x000006000000)        /* 6 */
#define CC_B_5                             (0x000005000000)        /* 5 */
#define CC_B_4                             (0x000004000000)        /* 4 */
#define CC_B_3                             (0x000003000000)        /* 3 */
#define CC_B_2                             (0x000002000000)        /* 2 */
#define CC_B_1                             (0x000001000000)        /* 1 */
#define CC_B_0                             (0x000000000000)        /* 0 */
#define CC_B__255                          (0x0000FF000000)        /* 255 */
#define CC_B__254                          (0x0000FE000000)        /* 254 */
#define CC_B__253                          (0x0000FD000000)        /* 253 */
#define CC_B__252                          (0x0000FC000000)        /* 252 */
#define CC_B__251                          (0x0000FB000000)        /* 251 */
#define CC_B__250                          (0x0000FA000000)        /* 250 */
#define CC_B__249                          (0x0000F9000000)        /* 249 */
#define CC_B__248                          (0x0000F8000000)        /* 248 */
#define CC_B__247                          (0x0000F7000000)        /* 247 */
#define CC_B__246                          (0x0000F6000000)        /* 246 */
#define CC_B__245                          (0x0000F5000000)        /* 245 */
#define CC_B__244                          (0x0000F4000000)        /* 244 */
#define CC_B__243                          (0x0000F3000000)        /* 243 */
#define CC_B__242                          (0x0000F2000000)        /* 242 */
#define CC_B__241                          (0x0000F1000000)        /* 241 */
#define CC_B__240                          (0x0000F0000000)        /* 240 */
#define CC_B__239                          (0x0000EF000000)        /* 239 */
#define CC_B__238                          (0x0000EE000000)        /* 238 */
#define CC_B__237                          (0x0000ED000000)        /* 237 */
#define CC_B__236                          (0x0000EC000000)        /* 236 */
#define CC_B__235                          (0x0000EB000000)        /* 235 */
#define CC_B__234                          (0x0000EA000000)        /* 234 */
#define CC_B__233                          (0x0000E9000000)        /* 233 */
#define CC_B__232                          (0x0000E8000000)        /* 232 */
#define CC_B__231                          (0x0000E7000000)        /* 231 */
#define CC_B__230                          (0x0000E6000000)        /* 230 */
#define CC_B__229                          (0x0000E5000000)        /* 229 */
#define CC_B__228                          (0x0000E4000000)        /* 228 */
#define CC_B__227                          (0x0000E3000000)        /* 227 */
#define CC_B__226                          (0x0000E2000000)        /* 226 */
#define CC_B__225                          (0x0000E1000000)        /* 225 */
#define CC_B__224                          (0x0000E0000000)        /* 224 */
#define CC_B__223                          (0x0000DF000000)        /* 223 */
#define CC_B__222                          (0x0000DE000000)        /* 222 */
#define CC_B__221                          (0x0000DD000000)        /* 221 */
#define CC_B__220                          (0x0000DC000000)        /* 220 */
#define CC_B__219                          (0x0000DB000000)        /* 219 */
#define CC_B__218                          (0x0000DA000000)        /* 218 */
#define CC_B__217                          (0x0000D9000000)        /* 217 */
#define CC_B__216                          (0x0000D8000000)        /* 216 */
#define CC_B__215                          (0x0000D7000000)        /* 215 */
#define CC_B__214                          (0x0000D6000000)        /* 214 */
#define CC_B__213                          (0x0000D5000000)        /* 213 */
#define CC_B__212                          (0x0000D4000000)        /* 212 */
#define CC_B__211                          (0x0000D3000000)        /* 211 */
#define CC_B__210                          (0x0000D2000000)        /* 210 */
#define CC_B__209                          (0x0000D1000000)        /* 209 */
#define CC_B__208                          (0x0000D0000000)        /* 208 */
#define CC_B__207                          (0x0000CF000000)        /* 207 */
#define CC_B__206                          (0x0000CE000000)        /* 206 */
#define CC_B__205                          (0x0000CD000000)        /* 205 */
#define CC_B__204                          (0x0000CC000000)        /* 204 */
#define CC_B__203                          (0x0000CB000000)        /* 203 */
#define CC_B__202                          (0x0000CA000000)        /* 202 */
#define CC_B__201                          (0x0000C9000000)        /* 201 */
#define CC_B__200                          (0x0000C8000000)        /* 200 */
#define CC_B__199                          (0x0000C7000000)        /* 199 */
#define CC_B__198                          (0x0000C6000000)        /* 198 */
#define CC_B__197                          (0x0000C5000000)        /* 197 */
#define CC_B__196                          (0x0000C4000000)        /* 196 */
#define CC_B__195                          (0x0000C3000000)        /* 195 */
#define CC_B__194                          (0x0000C2000000)        /* 194 */
#define CC_B__193                          (0x0000C1000000)        /* 193 */
#define CC_B__192                          (0x0000C0000000)        /* 192 */
#define CC_B__191                          (0x0000BF000000)        /* 191 */
#define CC_B__190                          (0x0000BE000000)        /* 190 */
#define CC_B__189                          (0x0000BD000000)        /* 189 */
#define CC_B__188                          (0x0000BC000000)        /* 188 */
#define CC_B__187                          (0x0000BB000000)        /* 187 */
#define CC_B__186                          (0x0000BA000000)        /* 186 */
#define CC_B__185                          (0x0000B9000000)        /* 185 */
#define CC_B__184                          (0x0000B8000000)        /* 184 */
#define CC_B__183                          (0x0000B7000000)        /* 183 */
#define CC_B__182                          (0x0000B6000000)        /* 182 */
#define CC_B__181                          (0x0000B5000000)        /* 181 */
#define CC_B__180                          (0x0000B4000000)        /* 180 */
#define CC_B__179                          (0x0000B3000000)        /* 179 */
#define CC_B__178                          (0x0000B2000000)        /* 178 */
#define CC_B__177                          (0x0000B1000000)        /* 177 */
#define CC_B__176                          (0x0000B0000000)        /* 176 */
#define CC_B__175                          (0x0000AF000000)        /* 175 */
#define CC_B__174                          (0x0000AE000000)        /* 174 */
#define CC_B__173                          (0x0000AD000000)        /* 173 */
#define CC_B__172                          (0x0000AC000000)        /* 172 */
#define CC_B__171                          (0x0000AB000000)        /* 171 */
#define CC_B__170                          (0x0000AA000000)        /* 170 */
#define CC_B__169                          (0x0000A9000000)        /* 169 */
#define CC_B__168                          (0x0000A8000000)        /* 168 */
#define CC_B__167                          (0x0000A7000000)        /* 167 */
#define CC_B__166                          (0x0000A6000000)        /* 166 */
#define CC_B__165                          (0x0000A5000000)        /* 165 */
#define CC_B__164                          (0x0000A4000000)        /* 164 */
#define CC_B__163                          (0x0000A3000000)        /* 163 */
#define CC_B__162                          (0x0000A2000000)        /* 162 */
#define CC_B__161                          (0x0000A1000000)        /* 161 */
#define CC_B__160                          (0x0000A0000000)        /* 160 */
#define CC_B__159                          (0x00009F000000)        /* 159 */
#define CC_B__158                          (0x00009E000000)        /* 158 */
#define CC_B__157                          (0x00009D000000)        /* 157 */
#define CC_B__156                          (0x00009C000000)        /* 156 */
#define CC_B__155                          (0x00009B000000)        /* 155 */
#define CC_B__154                          (0x00009A000000)        /* 154 */
#define CC_B__153                          (0x000099000000)        /* 153 */
#define CC_B__152                          (0x000098000000)        /* 152 */
#define CC_B__151                          (0x000097000000)        /* 151 */
#define CC_B__150                          (0x000096000000)        /* 150 */
#define CC_B__149                          (0x000095000000)        /* 149 */
#define CC_B__148                          (0x000094000000)        /* 148 */
#define CC_B__147                          (0x000093000000)        /* 147 */
#define CC_B__146                          (0x000092000000)        /* 146 */
#define CC_B__145                          (0x000091000000)        /* 145 */
#define CC_B__144                          (0x000090000000)        /* 144 */
#define CC_B__143                          (0x00008F000000)        /* 143 */
#define CC_B__142                          (0x00008E000000)        /* 142 */
#define CC_B__141                          (0x00008D000000)        /* 141 */
#define CC_B__140                          (0x00008C000000)        /* 140 */
#define CC_B__139                          (0x00008B000000)        /* 139 */
#define CC_B__138                          (0x00008A000000)        /* 138 */
#define CC_B__137                          (0x000089000000)        /* 137 */
#define CC_B__136                          (0x000088000000)        /* 136 */
#define CC_B__135                          (0x000087000000)        /* 135 */
#define CC_B__134                          (0x000086000000)        /* 134 */
#define CC_B__133                          (0x000085000000)        /* 133 */
#define CC_B__132                          (0x000084000000)        /* 132 */
#define CC_B__131                          (0x000083000000)        /* 131 */
#define CC_B__130                          (0x000082000000)        /* 130 */
#define CC_B__129                          (0x000081000000)        /* 129 */
#define CC_B__128                          (0x000080000000)        /* 128 */
#define CC_B__127                          (0x00007F000000)        /* 127 */
#define CC_B__126                          (0x00007E000000)        /* 126 */
#define CC_B__125                          (0x00007D000000)        /* 125 */
#define CC_B__124                          (0x00007C000000)        /* 124 */
#define CC_B__123                          (0x00007B000000)        /* 123 */
#define CC_B__122                          (0x00007A000000)        /* 122 */
#define CC_B__121                          (0x000079000000)        /* 121 */
#define CC_B__120                          (0x000078000000)        /* 120 */
#define CC_B__119                          (0x000077000000)        /* 119 */
#define CC_B__118                          (0x000076000000)        /* 118 */
#define CC_B__117                          (0x000075000000)        /* 117 */
#define CC_B__116                          (0x000074000000)        /* 116 */
#define CC_B__115                          (0x000073000000)        /* 115 */
#define CC_B__114                          (0x000072000000)        /* 114 */
#define CC_B__113                          (0x000071000000)        /* 113 */
#define CC_B__112                          (0x000070000000)        /* 112 */
#define CC_B__111                          (0x00006F000000)        /* 111 */
#define CC_B__110                          (0x00006E000000)        /* 110 */
#define CC_B__109                          (0x00006D000000)        /* 109 */
#define CC_B__108                          (0x00006C000000)        /* 108 */
#define CC_B__107                          (0x00006B000000)        /* 107 */
#define CC_B__106                          (0x00006A000000)        /* 106 */
#define CC_B__105                          (0x000069000000)        /* 105 */
#define CC_B__104                          (0x000068000000)        /* 104 */
#define CC_B__103                          (0x000067000000)        /* 103 */
#define CC_B__102                          (0x000066000000)        /* 102 */
#define CC_B__101                          (0x000065000000)        /* 101 */
#define CC_B__100                          (0x000064000000)        /* 100 */
#define CC_B__99                           (0x000063000000)        /* 99 */
#define CC_B__98                           (0x000062000000)        /* 98 */
#define CC_B__97                           (0x000061000000)        /* 97 */
#define CC_B__96                           (0x000060000000)        /* 96 */
#define CC_B__95                           (0x00005F000000)        /* 95 */
#define CC_B__94                           (0x00005E000000)        /* 94 */
#define CC_B__93                           (0x00005D000000)        /* 93 */
#define CC_B__92                           (0x00005C000000)        /* 92 */
#define CC_B__91                           (0x00005B000000)        /* 91 */
#define CC_B__90                           (0x00005A000000)        /* 90 */
#define CC_B__89                           (0x000059000000)        /* 89 */
#define CC_B__88                           (0x000058000000)        /* 88 */
#define CC_B__87                           (0x000057000000)        /* 87 */
#define CC_B__86                           (0x000056000000)        /* 86 */
#define CC_B__85                           (0x000055000000)        /* 85 */
#define CC_B__84                           (0x000054000000)        /* 84 */
#define CC_B__83                           (0x000053000000)        /* 83 */
#define CC_B__82                           (0x000052000000)        /* 82 */
#define CC_B__81                           (0x000051000000)        /* 81 */
#define CC_B__80                           (0x000050000000)        /* 80 */
#define CC_B__79                           (0x00004F000000)        /* 79 */
#define CC_B__78                           (0x00004E000000)        /* 78 */
#define CC_B__77                           (0x00004D000000)        /* 77 */
#define CC_B__76                           (0x00004C000000)        /* 76 */
#define CC_B__75                           (0x00004B000000)        /* 75 */
#define CC_B__74                           (0x00004A000000)        /* 74 */
#define CC_B__73                           (0x000049000000)        /* 73 */
#define CC_B__72                           (0x000048000000)        /* 72 */
#define CC_B__71                           (0x000047000000)        /* 71 */
#define CC_B__70                           (0x000046000000)        /* 70 */
#define CC_B__69                           (0x000045000000)        /* 69 */
#define CC_B__68                           (0x000044000000)        /* 68 */
#define CC_B__67                           (0x000043000000)        /* 67 */
#define CC_B__66                           (0x000042000000)        /* 66 */
#define CC_B__65                           (0x000041000000)        /* 65 */
#define CC_B__64                           (0x000040000000)        /* 64 */
#define CC_B__63                           (0x00003F000000)        /* 63 */
#define CC_B__62                           (0x00003E000000)        /* 62 */
#define CC_B__61                           (0x00003D000000)        /* 61 */
#define CC_B__60                           (0x00003C000000)        /* 60 */
#define CC_B__59                           (0x00003B000000)        /* 59 */
#define CC_B__58                           (0x00003A000000)        /* 58 */
#define CC_B__57                           (0x000039000000)        /* 57 */
#define CC_B__56                           (0x000038000000)        /* 56 */
#define CC_B__55                           (0x000037000000)        /* 55 */
#define CC_B__54                           (0x000036000000)        /* 54 */
#define CC_B__53                           (0x000035000000)        /* 53 */
#define CC_B__52                           (0x000034000000)        /* 52 */
#define CC_B__51                           (0x000033000000)        /* 51 */
#define CC_B__50                           (0x000032000000)        /* 50 */
#define CC_B__49                           (0x000031000000)        /* 49 */
#define CC_B__48                           (0x000030000000)        /* 48 */
#define CC_B__47                           (0x00002F000000)        /* 47 */
#define CC_B__46                           (0x00002E000000)        /* 46 */
#define CC_B__45                           (0x00002D000000)        /* 45 */
#define CC_B__44                           (0x00002C000000)        /* 44 */
#define CC_B__43                           (0x00002B000000)        /* 43 */
#define CC_B__42                           (0x00002A000000)        /* 42 */
#define CC_B__41                           (0x000029000000)        /* 41 */
#define CC_B__40                           (0x000028000000)        /* 40 */
#define CC_B__39                           (0x000027000000)        /* 39 */
#define CC_B__38                           (0x000026000000)        /* 38 */
#define CC_B__37                           (0x000025000000)        /* 37 */
#define CC_B__36                           (0x000024000000)        /* 36 */
#define CC_B__35                           (0x000023000000)        /* 35 */
#define CC_B__34                           (0x000022000000)        /* 34 */
#define CC_B__33                           (0x000021000000)        /* 33 */
#define CC_B__32                           (0x000020000000)        /* 32 */
#define CC_B__31                           (0x00001F000000)        /* 31 */
#define CC_B__30                           (0x00001E000000)        /* 30 */
#define CC_B__29                           (0x00001D000000)        /* 29 */
#define CC_B__28                           (0x00001C000000)        /* 28 */
#define CC_B__27                           (0x00001B000000)        /* 27 */
#define CC_B__26                           (0x00001A000000)        /* 26 */
#define CC_B__25                           (0x000019000000)        /* 25 */
#define CC_B__24                           (0x000018000000)        /* 24 */
#define CC_B__23                           (0x000017000000)        /* 23 */
#define CC_B__22                           (0x000016000000)        /* 22 */
#define CC_B__21                           (0x000015000000)        /* 21 */
#define CC_B__20                           (0x000014000000)        /* 20 */
#define CC_B__19                           (0x000013000000)        /* 19 */
#define CC_B__18                           (0x000012000000)        /* 18 */
#define CC_B__17                           (0x000011000000)        /* 17 */
#define CC_B__16                           (0x000010000000)        /* 16 */
#define CC_B__15                           (0x00000F000000)        /* 15 */
#define CC_B__14                           (0x00000E000000)        /* 14 */
#define CC_B__13                           (0x00000D000000)        /* 13 */
#define CC_B__12                           (0x00000C000000)        /* 12 */
#define CC_B__11                           (0x00000B000000)        /* 11 */
#define CC_B__10                           (0x00000A000000)        /* 10 */
#define CC_B__9                            (0x000009000000)        /* 9 */
#define CC_B__8                            (0x000008000000)        /* 8 */
#define CC_B__7                            (0x000007000000)        /* 7 */
#define CC_B__6                            (0x000006000000)        /* 6 */
#define CC_B__5                            (0x000005000000)        /* 5 */
#define CC_B__4                            (0x000004000000)        /* 4 */
#define CC_B__3                            (0x000003000000)        /* 3 */
#define CC_B__2                            (0x000002000000)        /* 2 */
#define CC_B__1                            (0x000001000000)        /* 1 */
#define CC_B__0                            (0x000000000000)        /* 0 */
#define CC_G_255                           (0x000000FF0000)        /* 255 */
#define CC_G_254                           (0x000000FE0000)        /* 254 */
#define CC_G_253                           (0x000000FD0000)        /* 253 */
#define CC_G_252                           (0x000000FC0000)        /* 252 */
#define CC_G_251                           (0x000000FB0000)        /* 251 */
#define CC_G_250                           (0x000000FA0000)        /* 250 */
#define CC_G_249                           (0x000000F90000)        /* 249 */
#define CC_G_248                           (0x000000F80000)        /* 248 */
#define CC_G_247                           (0x000000F70000)        /* 247 */
#define CC_G_246                           (0x000000F60000)        /* 246 */
#define CC_G_245                           (0x000000F50000)        /* 245 */
#define CC_G_244                           (0x000000F40000)        /* 244 */
#define CC_G_243                           (0x000000F30000)        /* 243 */
#define CC_G_242                           (0x000000F20000)        /* 242 */
#define CC_G_241                           (0x000000F10000)        /* 241 */
#define CC_G_240                           (0x000000F00000)        /* 240 */
#define CC_G_239                           (0x000000EF0000)        /* 239 */
#define CC_G_238                           (0x000000EE0000)        /* 238 */
#define CC_G_237                           (0x000000ED0000)        /* 237 */
#define CC_G_236                           (0x000000EC0000)        /* 236 */
#define CC_G_235                           (0x000000EB0000)        /* 235 */
#define CC_G_234                           (0x000000EA0000)        /* 234 */
#define CC_G_233                           (0x000000E90000)        /* 233 */
#define CC_G_232                           (0x000000E80000)        /* 232 */
#define CC_G_231                           (0x000000E70000)        /* 231 */
#define CC_G_230                           (0x000000E60000)        /* 230 */
#define CC_G_229                           (0x000000E50000)        /* 229 */
#define CC_G_228                           (0x000000E40000)        /* 228 */
#define CC_G_227                           (0x000000E30000)        /* 227 */
#define CC_G_226                           (0x000000E20000)        /* 226 */
#define CC_G_225                           (0x000000E10000)        /* 225 */
#define CC_G_224                           (0x000000E00000)        /* 224 */
#define CC_G_223                           (0x000000DF0000)        /* 223 */
#define CC_G_222                           (0x000000DE0000)        /* 222 */
#define CC_G_221                           (0x000000DD0000)        /* 221 */
#define CC_G_220                           (0x000000DC0000)        /* 220 */
#define CC_G_219                           (0x000000DB0000)        /* 219 */
#define CC_G_218                           (0x000000DA0000)        /* 218 */
#define CC_G_217                           (0x000000D90000)        /* 217 */
#define CC_G_216                           (0x000000D80000)        /* 216 */
#define CC_G_215                           (0x000000D70000)        /* 215 */
#define CC_G_214                           (0x000000D60000)        /* 214 */
#define CC_G_213                           (0x000000D50000)        /* 213 */
#define CC_G_212                           (0x000000D40000)        /* 212 */
#define CC_G_211                           (0x000000D30000)        /* 211 */
#define CC_G_210                           (0x000000D20000)        /* 210 */
#define CC_G_209                           (0x000000D10000)        /* 209 */
#define CC_G_208                           (0x000000D00000)        /* 208 */
#define CC_G_207                           (0x000000CF0000)        /* 207 */
#define CC_G_206                           (0x000000CE0000)        /* 206 */
#define CC_G_205                           (0x000000CD0000)        /* 205 */
#define CC_G_204                           (0x000000CC0000)        /* 204 */
#define CC_G_203                           (0x000000CB0000)        /* 203 */
#define CC_G_202                           (0x000000CA0000)        /* 202 */
#define CC_G_201                           (0x000000C90000)        /* 201 */
#define CC_G_200                           (0x000000C80000)        /* 200 */
#define CC_G_199                           (0x000000C70000)        /* 199 */
#define CC_G_198                           (0x000000C60000)        /* 198 */
#define CC_G_197                           (0x000000C50000)        /* 197 */
#define CC_G_196                           (0x000000C40000)        /* 196 */
#define CC_G_195                           (0x000000C30000)        /* 195 */
#define CC_G_194                           (0x000000C20000)        /* 194 */
#define CC_G_193                           (0x000000C10000)        /* 193 */
#define CC_G_192                           (0x000000C00000)        /* 192 */
#define CC_G_191                           (0x000000BF0000)        /* 191 */
#define CC_G_190                           (0x000000BE0000)        /* 190 */
#define CC_G_189                           (0x000000BD0000)        /* 189 */
#define CC_G_188                           (0x000000BC0000)        /* 188 */
#define CC_G_187                           (0x000000BB0000)        /* 187 */
#define CC_G_186                           (0x000000BA0000)        /* 186 */
#define CC_G_185                           (0x000000B90000)        /* 185 */
#define CC_G_184                           (0x000000B80000)        /* 184 */
#define CC_G_183                           (0x000000B70000)        /* 183 */
#define CC_G_182                           (0x000000B60000)        /* 182 */
#define CC_G_181                           (0x000000B50000)        /* 181 */
#define CC_G_180                           (0x000000B40000)        /* 180 */
#define CC_G_179                           (0x000000B30000)        /* 179 */
#define CC_G_178                           (0x000000B20000)        /* 178 */
#define CC_G_177                           (0x000000B10000)        /* 177 */
#define CC_G_176                           (0x000000B00000)        /* 176 */
#define CC_G_175                           (0x000000AF0000)        /* 175 */
#define CC_G_174                           (0x000000AE0000)        /* 174 */
#define CC_G_173                           (0x000000AD0000)        /* 173 */
#define CC_G_172                           (0x000000AC0000)        /* 172 */
#define CC_G_171                           (0x000000AB0000)        /* 171 */
#define CC_G_170                           (0x000000AA0000)        /* 170 */
#define CC_G_169                           (0x000000A90000)        /* 169 */
#define CC_G_168                           (0x000000A80000)        /* 168 */
#define CC_G_167                           (0x000000A70000)        /* 167 */
#define CC_G_166                           (0x000000A60000)        /* 166 */
#define CC_G_165                           (0x000000A50000)        /* 165 */
#define CC_G_164                           (0x000000A40000)        /* 164 */
#define CC_G_163                           (0x000000A30000)        /* 163 */
#define CC_G_162                           (0x000000A20000)        /* 162 */
#define CC_G_161                           (0x000000A10000)        /* 161 */
#define CC_G_160                           (0x000000A00000)        /* 160 */
#define CC_G_159                           (0x0000009F0000)        /* 159 */
#define CC_G_158                           (0x0000009E0000)        /* 158 */
#define CC_G_157                           (0x0000009D0000)        /* 157 */
#define CC_G_156                           (0x0000009C0000)        /* 156 */
#define CC_G_155                           (0x0000009B0000)        /* 155 */
#define CC_G_154                           (0x0000009A0000)        /* 154 */
#define CC_G_153                           (0x000000990000)        /* 153 */
#define CC_G_152                           (0x000000980000)        /* 152 */
#define CC_G_151                           (0x000000970000)        /* 151 */
#define CC_G_150                           (0x000000960000)        /* 150 */
#define CC_G_149                           (0x000000950000)        /* 149 */
#define CC_G_148                           (0x000000940000)        /* 148 */
#define CC_G_147                           (0x000000930000)        /* 147 */
#define CC_G_146                           (0x000000920000)        /* 146 */
#define CC_G_145                           (0x000000910000)        /* 145 */
#define CC_G_144                           (0x000000900000)        /* 144 */
#define CC_G_143                           (0x0000008F0000)        /* 143 */
#define CC_G_142                           (0x0000008E0000)        /* 142 */
#define CC_G_141                           (0x0000008D0000)        /* 141 */
#define CC_G_140                           (0x0000008C0000)        /* 140 */
#define CC_G_139                           (0x0000008B0000)        /* 139 */
#define CC_G_138                           (0x0000008A0000)        /* 138 */
#define CC_G_137                           (0x000000890000)        /* 137 */
#define CC_G_136                           (0x000000880000)        /* 136 */
#define CC_G_135                           (0x000000870000)        /* 135 */
#define CC_G_134                           (0x000000860000)        /* 134 */
#define CC_G_133                           (0x000000850000)        /* 133 */
#define CC_G_132                           (0x000000840000)        /* 132 */
#define CC_G_131                           (0x000000830000)        /* 131 */
#define CC_G_130                           (0x000000820000)        /* 130 */
#define CC_G_129                           (0x000000810000)        /* 129 */
#define CC_G_128                           (0x000000800000)        /* 128 */
#define CC_G_127                           (0x0000007F0000)        /* 127 */
#define CC_G_126                           (0x0000007E0000)        /* 126 */
#define CC_G_125                           (0x0000007D0000)        /* 125 */
#define CC_G_124                           (0x0000007C0000)        /* 124 */
#define CC_G_123                           (0x0000007B0000)        /* 123 */
#define CC_G_122                           (0x0000007A0000)        /* 122 */
#define CC_G_121                           (0x000000790000)        /* 121 */
#define CC_G_120                           (0x000000780000)        /* 120 */
#define CC_G_119                           (0x000000770000)        /* 119 */
#define CC_G_118                           (0x000000760000)        /* 118 */
#define CC_G_117                           (0x000000750000)        /* 117 */
#define CC_G_116                           (0x000000740000)        /* 116 */
#define CC_G_115                           (0x000000730000)        /* 115 */
#define CC_G_114                           (0x000000720000)        /* 114 */
#define CC_G_113                           (0x000000710000)        /* 113 */
#define CC_G_112                           (0x000000700000)        /* 112 */
#define CC_G_111                           (0x0000006F0000)        /* 111 */
#define CC_G_110                           (0x0000006E0000)        /* 110 */
#define CC_G_109                           (0x0000006D0000)        /* 109 */
#define CC_G_108                           (0x0000006C0000)        /* 108 */
#define CC_G_107                           (0x0000006B0000)        /* 107 */
#define CC_G_106                           (0x0000006A0000)        /* 106 */
#define CC_G_105                           (0x000000690000)        /* 105 */
#define CC_G_104                           (0x000000680000)        /* 104 */
#define CC_G_103                           (0x000000670000)        /* 103 */
#define CC_G_102                           (0x000000660000)        /* 102 */
#define CC_G_101                           (0x000000650000)        /* 101 */
#define CC_G_100                           (0x000000640000)        /* 100 */
#define CC_G_99                            (0x000000630000)        /* 99 */
#define CC_G_98                            (0x000000620000)        /* 98 */
#define CC_G_97                            (0x000000610000)        /* 97 */
#define CC_G_96                            (0x000000600000)        /* 96 */
#define CC_G_95                            (0x0000005F0000)        /* 95 */
#define CC_G_94                            (0x0000005E0000)        /* 94 */
#define CC_G_93                            (0x0000005D0000)        /* 93 */
#define CC_G_92                            (0x0000005C0000)        /* 92 */
#define CC_G_91                            (0x0000005B0000)        /* 91 */
#define CC_G_90                            (0x0000005A0000)        /* 90 */
#define CC_G_89                            (0x000000590000)        /* 89 */
#define CC_G_88                            (0x000000580000)        /* 88 */
#define CC_G_87                            (0x000000570000)        /* 87 */
#define CC_G_86                            (0x000000560000)        /* 86 */
#define CC_G_85                            (0x000000550000)        /* 85 */
#define CC_G_84                            (0x000000540000)        /* 84 */
#define CC_G_83                            (0x000000530000)        /* 83 */
#define CC_G_82                            (0x000000520000)        /* 82 */
#define CC_G_81                            (0x000000510000)        /* 81 */
#define CC_G_80                            (0x000000500000)        /* 80 */
#define CC_G_79                            (0x0000004F0000)        /* 79 */
#define CC_G_78                            (0x0000004E0000)        /* 78 */
#define CC_G_77                            (0x0000004D0000)        /* 77 */
#define CC_G_76                            (0x0000004C0000)        /* 76 */
#define CC_G_75                            (0x0000004B0000)        /* 75 */
#define CC_G_74                            (0x0000004A0000)        /* 74 */
#define CC_G_73                            (0x000000490000)        /* 73 */
#define CC_G_72                            (0x000000480000)        /* 72 */
#define CC_G_71                            (0x000000470000)        /* 71 */
#define CC_G_70                            (0x000000460000)        /* 70 */
#define CC_G_69                            (0x000000450000)        /* 69 */
#define CC_G_68                            (0x000000440000)        /* 68 */
#define CC_G_67                            (0x000000430000)        /* 67 */
#define CC_G_66                            (0x000000420000)        /* 66 */
#define CC_G_65                            (0x000000410000)        /* 65 */
#define CC_G_64                            (0x000000400000)        /* 64 */
#define CC_G_63                            (0x0000003F0000)        /* 63 */
#define CC_G_62                            (0x0000003E0000)        /* 62 */
#define CC_G_61                            (0x0000003D0000)        /* 61 */
#define CC_G_60                            (0x0000003C0000)        /* 60 */
#define CC_G_59                            (0x0000003B0000)        /* 59 */
#define CC_G_58                            (0x0000003A0000)        /* 58 */
#define CC_G_57                            (0x000000390000)        /* 57 */
#define CC_G_56                            (0x000000380000)        /* 56 */
#define CC_G_55                            (0x000000370000)        /* 55 */
#define CC_G_54                            (0x000000360000)        /* 54 */
#define CC_G_53                            (0x000000350000)        /* 53 */
#define CC_G_52                            (0x000000340000)        /* 52 */
#define CC_G_51                            (0x000000330000)        /* 51 */
#define CC_G_50                            (0x000000320000)        /* 50 */
#define CC_G_49                            (0x000000310000)        /* 49 */
#define CC_G_48                            (0x000000300000)        /* 48 */
#define CC_G_47                            (0x0000002F0000)        /* 47 */
#define CC_G_46                            (0x0000002E0000)        /* 46 */
#define CC_G_45                            (0x0000002D0000)        /* 45 */
#define CC_G_44                            (0x0000002C0000)        /* 44 */
#define CC_G_43                            (0x0000002B0000)        /* 43 */
#define CC_G_42                            (0x0000002A0000)        /* 42 */
#define CC_G_41                            (0x000000290000)        /* 41 */
#define CC_G_40                            (0x000000280000)        /* 40 */
#define CC_G_39                            (0x000000270000)        /* 39 */
#define CC_G_38                            (0x000000260000)        /* 38 */
#define CC_G_37                            (0x000000250000)        /* 37 */
#define CC_G_36                            (0x000000240000)        /* 36 */
#define CC_G_35                            (0x000000230000)        /* 35 */
#define CC_G_34                            (0x000000220000)        /* 34 */
#define CC_G_33                            (0x000000210000)        /* 33 */
#define CC_G_32                            (0x000000200000)        /* 32 */
#define CC_G_31                            (0x0000001F0000)        /* 31 */
#define CC_G_30                            (0x0000001E0000)        /* 30 */
#define CC_G_29                            (0x0000001D0000)        /* 29 */
#define CC_G_28                            (0x0000001C0000)        /* 28 */
#define CC_G_27                            (0x0000001B0000)        /* 27 */
#define CC_G_26                            (0x0000001A0000)        /* 26 */
#define CC_G_25                            (0x000000190000)        /* 25 */
#define CC_G_24                            (0x000000180000)        /* 24 */
#define CC_G_23                            (0x000000170000)        /* 23 */
#define CC_G_22                            (0x000000160000)        /* 22 */
#define CC_G_21                            (0x000000150000)        /* 21 */
#define CC_G_20                            (0x000000140000)        /* 20 */
#define CC_G_19                            (0x000000130000)        /* 19 */
#define CC_G_18                            (0x000000120000)        /* 18 */
#define CC_G_17                            (0x000000110000)        /* 17 */
#define CC_G_16                            (0x000000100000)        /* 16 */
#define CC_G_15                            (0x0000000F0000)        /* 15 */
#define CC_G_14                            (0x0000000E0000)        /* 14 */
#define CC_G_13                            (0x0000000D0000)        /* 13 */
#define CC_G_12                            (0x0000000C0000)        /* 12 */
#define CC_G_11                            (0x0000000B0000)        /* 11 */
#define CC_G_10                            (0x0000000A0000)        /* 10 */
#define CC_G_9                             (0x000000090000)        /* 9 */
#define CC_G_8                             (0x000000080000)        /* 8 */
#define CC_G_7                             (0x000000070000)        /* 7 */
#define CC_G_6                             (0x000000060000)        /* 6 */
#define CC_G_5                             (0x000000050000)        /* 5 */
#define CC_G_4                             (0x000000040000)        /* 4 */
#define CC_G_3                             (0x000000030000)        /* 3 */
#define CC_G_2                             (0x000000020000)        /* 2 */
#define CC_G_1                             (0x000000010000)        /* 1 */
#define CC_G_0                             (0x000000000000)        /* 0 */
#define CC_G__255                          (0x000000FF0000)        /* 255 */
#define CC_G__254                          (0x000000FE0000)        /* 254 */
#define CC_G__253                          (0x000000FD0000)        /* 253 */
#define CC_G__252                          (0x000000FC0000)        /* 252 */
#define CC_G__251                          (0x000000FB0000)        /* 251 */
#define CC_G__250                          (0x000000FA0000)        /* 250 */
#define CC_G__249                          (0x000000F90000)        /* 249 */
#define CC_G__248                          (0x000000F80000)        /* 248 */
#define CC_G__247                          (0x000000F70000)        /* 247 */
#define CC_G__246                          (0x000000F60000)        /* 246 */
#define CC_G__245                          (0x000000F50000)        /* 245 */
#define CC_G__244                          (0x000000F40000)        /* 244 */
#define CC_G__243                          (0x000000F30000)        /* 243 */
#define CC_G__242                          (0x000000F20000)        /* 242 */
#define CC_G__241                          (0x000000F10000)        /* 241 */
#define CC_G__240                          (0x000000F00000)        /* 240 */
#define CC_G__239                          (0x000000EF0000)        /* 239 */
#define CC_G__238                          (0x000000EE0000)        /* 238 */
#define CC_G__237                          (0x000000ED0000)        /* 237 */
#define CC_G__236                          (0x000000EC0000)        /* 236 */
#define CC_G__235                          (0x000000EB0000)        /* 235 */
#define CC_G__234                          (0x000000EA0000)        /* 234 */
#define CC_G__233                          (0x000000E90000)        /* 233 */
#define CC_G__232                          (0x000000E80000)        /* 232 */
#define CC_G__231                          (0x000000E70000)        /* 231 */
#define CC_G__230                          (0x000000E60000)        /* 230 */
#define CC_G__229                          (0x000000E50000)        /* 229 */
#define CC_G__228                          (0x000000E40000)        /* 228 */
#define CC_G__227                          (0x000000E30000)        /* 227 */
#define CC_G__226                          (0x000000E20000)        /* 226 */
#define CC_G__225                          (0x000000E10000)        /* 225 */
#define CC_G__224                          (0x000000E00000)        /* 224 */
#define CC_G__223                          (0x000000DF0000)        /* 223 */
#define CC_G__222                          (0x000000DE0000)        /* 222 */
#define CC_G__221                          (0x000000DD0000)        /* 221 */
#define CC_G__220                          (0x000000DC0000)        /* 220 */
#define CC_G__219                          (0x000000DB0000)        /* 219 */
#define CC_G__218                          (0x000000DA0000)        /* 218 */
#define CC_G__217                          (0x000000D90000)        /* 217 */
#define CC_G__216                          (0x000000D80000)        /* 216 */
#define CC_G__215                          (0x000000D70000)        /* 215 */
#define CC_G__214                          (0x000000D60000)        /* 214 */
#define CC_G__213                          (0x000000D50000)        /* 213 */
#define CC_G__212                          (0x000000D40000)        /* 212 */
#define CC_G__211                          (0x000000D30000)        /* 211 */
#define CC_G__210                          (0x000000D20000)        /* 210 */
#define CC_G__209                          (0x000000D10000)        /* 209 */
#define CC_G__208                          (0x000000D00000)        /* 208 */
#define CC_G__207                          (0x000000CF0000)        /* 207 */
#define CC_G__206                          (0x000000CE0000)        /* 206 */
#define CC_G__205                          (0x000000CD0000)        /* 205 */
#define CC_G__204                          (0x000000CC0000)        /* 204 */
#define CC_G__203                          (0x000000CB0000)        /* 203 */
#define CC_G__202                          (0x000000CA0000)        /* 202 */
#define CC_G__201                          (0x000000C90000)        /* 201 */
#define CC_G__200                          (0x000000C80000)        /* 200 */
#define CC_G__199                          (0x000000C70000)        /* 199 */
#define CC_G__198                          (0x000000C60000)        /* 198 */
#define CC_G__197                          (0x000000C50000)        /* 197 */
#define CC_G__196                          (0x000000C40000)        /* 196 */
#define CC_G__195                          (0x000000C30000)        /* 195 */
#define CC_G__194                          (0x000000C20000)        /* 194 */
#define CC_G__193                          (0x000000C10000)        /* 193 */
#define CC_G__192                          (0x000000C00000)        /* 192 */
#define CC_G__191                          (0x000000BF0000)        /* 191 */
#define CC_G__190                          (0x000000BE0000)        /* 190 */
#define CC_G__189                          (0x000000BD0000)        /* 189 */
#define CC_G__188                          (0x000000BC0000)        /* 188 */
#define CC_G__187                          (0x000000BB0000)        /* 187 */
#define CC_G__186                          (0x000000BA0000)        /* 186 */
#define CC_G__185                          (0x000000B90000)        /* 185 */
#define CC_G__184                          (0x000000B80000)        /* 184 */
#define CC_G__183                          (0x000000B70000)        /* 183 */
#define CC_G__182                          (0x000000B60000)        /* 182 */
#define CC_G__181                          (0x000000B50000)        /* 181 */
#define CC_G__180                          (0x000000B40000)        /* 180 */
#define CC_G__179                          (0x000000B30000)        /* 179 */
#define CC_G__178                          (0x000000B20000)        /* 178 */
#define CC_G__177                          (0x000000B10000)        /* 177 */
#define CC_G__176                          (0x000000B00000)        /* 176 */
#define CC_G__175                          (0x000000AF0000)        /* 175 */
#define CC_G__174                          (0x000000AE0000)        /* 174 */
#define CC_G__173                          (0x000000AD0000)        /* 173 */
#define CC_G__172                          (0x000000AC0000)        /* 172 */
#define CC_G__171                          (0x000000AB0000)        /* 171 */
#define CC_G__170                          (0x000000AA0000)        /* 170 */
#define CC_G__169                          (0x000000A90000)        /* 169 */
#define CC_G__168                          (0x000000A80000)        /* 168 */
#define CC_G__167                          (0x000000A70000)        /* 167 */
#define CC_G__166                          (0x000000A60000)        /* 166 */
#define CC_G__165                          (0x000000A50000)        /* 165 */
#define CC_G__164                          (0x000000A40000)        /* 164 */
#define CC_G__163                          (0x000000A30000)        /* 163 */
#define CC_G__162                          (0x000000A20000)        /* 162 */
#define CC_G__161                          (0x000000A10000)        /* 161 */
#define CC_G__160                          (0x000000A00000)        /* 160 */
#define CC_G__159                          (0x0000009F0000)        /* 159 */
#define CC_G__158                          (0x0000009E0000)        /* 158 */
#define CC_G__157                          (0x0000009D0000)        /* 157 */
#define CC_G__156                          (0x0000009C0000)        /* 156 */
#define CC_G__155                          (0x0000009B0000)        /* 155 */
#define CC_G__154                          (0x0000009A0000)        /* 154 */
#define CC_G__153                          (0x000000990000)        /* 153 */
#define CC_G__152                          (0x000000980000)        /* 152 */
#define CC_G__151                          (0x000000970000)        /* 151 */
#define CC_G__150                          (0x000000960000)        /* 150 */
#define CC_G__149                          (0x000000950000)        /* 149 */
#define CC_G__148                          (0x000000940000)        /* 148 */
#define CC_G__147                          (0x000000930000)        /* 147 */
#define CC_G__146                          (0x000000920000)        /* 146 */
#define CC_G__145                          (0x000000910000)        /* 145 */
#define CC_G__144                          (0x000000900000)        /* 144 */
#define CC_G__143                          (0x0000008F0000)        /* 143 */
#define CC_G__142                          (0x0000008E0000)        /* 142 */
#define CC_G__141                          (0x0000008D0000)        /* 141 */
#define CC_G__140                          (0x0000008C0000)        /* 140 */
#define CC_G__139                          (0x0000008B0000)        /* 139 */
#define CC_G__138                          (0x0000008A0000)        /* 138 */
#define CC_G__137                          (0x000000890000)        /* 137 */
#define CC_G__136                          (0x000000880000)        /* 136 */
#define CC_G__135                          (0x000000870000)        /* 135 */
#define CC_G__134                          (0x000000860000)        /* 134 */
#define CC_G__133                          (0x000000850000)        /* 133 */
#define CC_G__132                          (0x000000840000)        /* 132 */
#define CC_G__131                          (0x000000830000)        /* 131 */
#define CC_G__130                          (0x000000820000)        /* 130 */
#define CC_G__129                          (0x000000810000)        /* 129 */
#define CC_G__128                          (0x000000800000)        /* 128 */
#define CC_G__127                          (0x0000007F0000)        /* 127 */
#define CC_G__126                          (0x0000007E0000)        /* 126 */
#define CC_G__125                          (0x0000007D0000)        /* 125 */
#define CC_G__124                          (0x0000007C0000)        /* 124 */
#define CC_G__123                          (0x0000007B0000)        /* 123 */
#define CC_G__122                          (0x0000007A0000)        /* 122 */
#define CC_G__121                          (0x000000790000)        /* 121 */
#define CC_G__120                          (0x000000780000)        /* 120 */
#define CC_G__119                          (0x000000770000)        /* 119 */
#define CC_G__118                          (0x000000760000)        /* 118 */
#define CC_G__117                          (0x000000750000)        /* 117 */
#define CC_G__116                          (0x000000740000)        /* 116 */
#define CC_G__115                          (0x000000730000)        /* 115 */
#define CC_G__114                          (0x000000720000)        /* 114 */
#define CC_G__113                          (0x000000710000)        /* 113 */
#define CC_G__112                          (0x000000700000)        /* 112 */
#define CC_G__111                          (0x0000006F0000)        /* 111 */
#define CC_G__110                          (0x0000006E0000)        /* 110 */
#define CC_G__109                          (0x0000006D0000)        /* 109 */
#define CC_G__108                          (0x0000006C0000)        /* 108 */
#define CC_G__107                          (0x0000006B0000)        /* 107 */
#define CC_G__106                          (0x0000006A0000)        /* 106 */
#define CC_G__105                          (0x000000690000)        /* 105 */
#define CC_G__104                          (0x000000680000)        /* 104 */
#define CC_G__103                          (0x000000670000)        /* 103 */
#define CC_G__102                          (0x000000660000)        /* 102 */
#define CC_G__101                          (0x000000650000)        /* 101 */
#define CC_G__100                          (0x000000640000)        /* 100 */
#define CC_G__99                           (0x000000630000)        /* 99 */
#define CC_G__98                           (0x000000620000)        /* 98 */
#define CC_G__97                           (0x000000610000)        /* 97 */
#define CC_G__96                           (0x000000600000)        /* 96 */
#define CC_G__95                           (0x0000005F0000)        /* 95 */
#define CC_G__94                           (0x0000005E0000)        /* 94 */
#define CC_G__93                           (0x0000005D0000)        /* 93 */
#define CC_G__92                           (0x0000005C0000)        /* 92 */
#define CC_G__91                           (0x0000005B0000)        /* 91 */
#define CC_G__90                           (0x0000005A0000)        /* 90 */
#define CC_G__89                           (0x000000590000)        /* 89 */
#define CC_G__88                           (0x000000580000)        /* 88 */
#define CC_G__87                           (0x000000570000)        /* 87 */
#define CC_G__86                           (0x000000560000)        /* 86 */
#define CC_G__85                           (0x000000550000)        /* 85 */
#define CC_G__84                           (0x000000540000)        /* 84 */
#define CC_G__83                           (0x000000530000)        /* 83 */
#define CC_G__82                           (0x000000520000)        /* 82 */
#define CC_G__81                           (0x000000510000)        /* 81 */
#define CC_G__80                           (0x000000500000)        /* 80 */
#define CC_G__79                           (0x0000004F0000)        /* 79 */
#define CC_G__78                           (0x0000004E0000)        /* 78 */
#define CC_G__77                           (0x0000004D0000)        /* 77 */
#define CC_G__76                           (0x0000004C0000)        /* 76 */
#define CC_G__75                           (0x0000004B0000)        /* 75 */
#define CC_G__74                           (0x0000004A0000)        /* 74 */
#define CC_G__73                           (0x000000490000)        /* 73 */
#define CC_G__72                           (0x000000480000)        /* 72 */
#define CC_G__71                           (0x000000470000)        /* 71 */
#define CC_G__70                           (0x000000460000)        /* 70 */
#define CC_G__69                           (0x000000450000)        /* 69 */
#define CC_G__68                           (0x000000440000)        /* 68 */
#define CC_G__67                           (0x000000430000)        /* 67 */
#define CC_G__66                           (0x000000420000)        /* 66 */
#define CC_G__65                           (0x000000410000)        /* 65 */
#define CC_G__64                           (0x000000400000)        /* 64 */
#define CC_G__63                           (0x0000003F0000)        /* 63 */
#define CC_G__62                           (0x0000003E0000)        /* 62 */
#define CC_G__61                           (0x0000003D0000)        /* 61 */
#define CC_G__60                           (0x0000003C0000)        /* 60 */
#define CC_G__59                           (0x0000003B0000)        /* 59 */
#define CC_G__58                           (0x0000003A0000)        /* 58 */
#define CC_G__57                           (0x000000390000)        /* 57 */
#define CC_G__56                           (0x000000380000)        /* 56 */
#define CC_G__55                           (0x000000370000)        /* 55 */
#define CC_G__54                           (0x000000360000)        /* 54 */
#define CC_G__53                           (0x000000350000)        /* 53 */
#define CC_G__52                           (0x000000340000)        /* 52 */
#define CC_G__51                           (0x000000330000)        /* 51 */
#define CC_G__50                           (0x000000320000)        /* 50 */
#define CC_G__49                           (0x000000310000)        /* 49 */
#define CC_G__48                           (0x000000300000)        /* 48 */
#define CC_G__47                           (0x0000002F0000)        /* 47 */
#define CC_G__46                           (0x0000002E0000)        /* 46 */
#define CC_G__45                           (0x0000002D0000)        /* 45 */
#define CC_G__44                           (0x0000002C0000)        /* 44 */
#define CC_G__43                           (0x0000002B0000)        /* 43 */
#define CC_G__42                           (0x0000002A0000)        /* 42 */
#define CC_G__41                           (0x000000290000)        /* 41 */
#define CC_G__40                           (0x000000280000)        /* 40 */
#define CC_G__39                           (0x000000270000)        /* 39 */
#define CC_G__38                           (0x000000260000)        /* 38 */
#define CC_G__37                           (0x000000250000)        /* 37 */
#define CC_G__36                           (0x000000240000)        /* 36 */
#define CC_G__35                           (0x000000230000)        /* 35 */
#define CC_G__34                           (0x000000220000)        /* 34 */
#define CC_G__33                           (0x000000210000)        /* 33 */
#define CC_G__32                           (0x000000200000)        /* 32 */
#define CC_G__31                           (0x0000001F0000)        /* 31 */
#define CC_G__30                           (0x0000001E0000)        /* 30 */
#define CC_G__29                           (0x0000001D0000)        /* 29 */
#define CC_G__28                           (0x0000001C0000)        /* 28 */
#define CC_G__27                           (0x0000001B0000)        /* 27 */
#define CC_G__26                           (0x0000001A0000)        /* 26 */
#define CC_G__25                           (0x000000190000)        /* 25 */
#define CC_G__24                           (0x000000180000)        /* 24 */
#define CC_G__23                           (0x000000170000)        /* 23 */
#define CC_G__22                           (0x000000160000)        /* 22 */
#define CC_G__21                           (0x000000150000)        /* 21 */
#define CC_G__20                           (0x000000140000)        /* 20 */
#define CC_G__19                           (0x000000130000)        /* 19 */
#define CC_G__18                           (0x000000120000)        /* 18 */
#define CC_G__17                           (0x000000110000)        /* 17 */
#define CC_G__16                           (0x000000100000)        /* 16 */
#define CC_G__15                           (0x0000000F0000)        /* 15 */
#define CC_G__14                           (0x0000000E0000)        /* 14 */
#define CC_G__13                           (0x0000000D0000)        /* 13 */
#define CC_G__12                           (0x0000000C0000)        /* 12 */
#define CC_G__11                           (0x0000000B0000)        /* 11 */
#define CC_G__10                           (0x0000000A0000)        /* 10 */
#define CC_G__9                            (0x000000090000)        /* 9 */
#define CC_G__8                            (0x000000080000)        /* 8 */
#define CC_G__7                            (0x000000070000)        /* 7 */
#define CC_G__6                            (0x000000060000)        /* 6 */
#define CC_G__5                            (0x000000050000)        /* 5 */
#define CC_G__4                            (0x000000040000)        /* 4 */
#define CC_G__3                            (0x000000030000)        /* 3 */
#define CC_G__2                            (0x000000020000)        /* 2 */
#define CC_G__1                            (0x000000010000)        /* 1 */
#define CC_G__0                            (0x000000000000)        /* 0 */
#define CC_R_255                           (0x00000000FF00)        /* 255 */
#define CC_R_254                           (0x00000000FE00)        /* 254 */
#define CC_R_253                           (0x00000000FD00)        /* 253 */
#define CC_R_252                           (0x00000000FC00)        /* 252 */
#define CC_R_251                           (0x00000000FB00)        /* 251 */
#define CC_R_250                           (0x00000000FA00)        /* 250 */
#define CC_R_249                           (0x00000000F900)        /* 249 */
#define CC_R_248                           (0x00000000F800)        /* 248 */
#define CC_R_247                           (0x00000000F700)        /* 247 */
#define CC_R_246                           (0x00000000F600)        /* 246 */
#define CC_R_245                           (0x00000000F500)        /* 245 */
#define CC_R_244                           (0x00000000F400)        /* 244 */
#define CC_R_243                           (0x00000000F300)        /* 243 */
#define CC_R_242                           (0x00000000F200)        /* 242 */
#define CC_R_241                           (0x00000000F100)        /* 241 */
#define CC_R_240                           (0x00000000F000)        /* 240 */
#define CC_R_239                           (0x00000000EF00)        /* 239 */
#define CC_R_238                           (0x00000000EE00)        /* 238 */
#define CC_R_237                           (0x00000000ED00)        /* 237 */
#define CC_R_236                           (0x00000000EC00)        /* 236 */
#define CC_R_235                           (0x00000000EB00)        /* 235 */
#define CC_R_234                           (0x00000000EA00)        /* 234 */
#define CC_R_233                           (0x00000000E900)        /* 233 */
#define CC_R_232                           (0x00000000E800)        /* 232 */
#define CC_R_231                           (0x00000000E700)        /* 231 */
#define CC_R_230                           (0x00000000E600)        /* 230 */
#define CC_R_229                           (0x00000000E500)        /* 229 */
#define CC_R_228                           (0x00000000E400)        /* 228 */
#define CC_R_227                           (0x00000000E300)        /* 227 */
#define CC_R_226                           (0x00000000E200)        /* 226 */
#define CC_R_225                           (0x00000000E100)        /* 225 */
#define CC_R_224                           (0x00000000E000)        /* 224 */
#define CC_R_223                           (0x00000000DF00)        /* 223 */
#define CC_R_222                           (0x00000000DE00)        /* 222 */
#define CC_R_221                           (0x00000000DD00)        /* 221 */
#define CC_R_220                           (0x00000000DC00)        /* 220 */
#define CC_R_219                           (0x00000000DB00)        /* 219 */
#define CC_R_218                           (0x00000000DA00)        /* 218 */
#define CC_R_217                           (0x00000000D900)        /* 217 */
#define CC_R_216                           (0x00000000D800)        /* 216 */
#define CC_R_215                           (0x00000000D700)        /* 215 */
#define CC_R_214                           (0x00000000D600)        /* 214 */
#define CC_R_213                           (0x00000000D500)        /* 213 */
#define CC_R_212                           (0x00000000D400)        /* 212 */
#define CC_R_211                           (0x00000000D300)        /* 211 */
#define CC_R_210                           (0x00000000D200)        /* 210 */
#define CC_R_209                           (0x00000000D100)        /* 209 */
#define CC_R_208                           (0x00000000D000)        /* 208 */
#define CC_R_207                           (0x00000000CF00)        /* 207 */
#define CC_R_206                           (0x00000000CE00)        /* 206 */
#define CC_R_205                           (0x00000000CD00)        /* 205 */
#define CC_R_204                           (0x00000000CC00)        /* 204 */
#define CC_R_203                           (0x00000000CB00)        /* 203 */
#define CC_R_202                           (0x00000000CA00)        /* 202 */
#define CC_R_201                           (0x00000000C900)        /* 201 */
#define CC_R_200                           (0x00000000C800)        /* 200 */
#define CC_R_199                           (0x00000000C700)        /* 199 */
#define CC_R_198                           (0x00000000C600)        /* 198 */
#define CC_R_197                           (0x00000000C500)        /* 197 */
#define CC_R_196                           (0x00000000C400)        /* 196 */
#define CC_R_195                           (0x00000000C300)        /* 195 */
#define CC_R_194                           (0x00000000C200)        /* 194 */
#define CC_R_193                           (0x00000000C100)        /* 193 */
#define CC_R_192                           (0x00000000C000)        /* 192 */
#define CC_R_191                           (0x00000000BF00)        /* 191 */
#define CC_R_190                           (0x00000000BE00)        /* 190 */
#define CC_R_189                           (0x00000000BD00)        /* 189 */
#define CC_R_188                           (0x00000000BC00)        /* 188 */
#define CC_R_187                           (0x00000000BB00)        /* 187 */
#define CC_R_186                           (0x00000000BA00)        /* 186 */
#define CC_R_185                           (0x00000000B900)        /* 185 */
#define CC_R_184                           (0x00000000B800)        /* 184 */
#define CC_R_183                           (0x00000000B700)        /* 183 */
#define CC_R_182                           (0x00000000B600)        /* 182 */
#define CC_R_181                           (0x00000000B500)        /* 181 */
#define CC_R_180                           (0x00000000B400)        /* 180 */
#define CC_R_179                           (0x00000000B300)        /* 179 */
#define CC_R_178                           (0x00000000B200)        /* 178 */
#define CC_R_177                           (0x00000000B100)        /* 177 */
#define CC_R_176                           (0x00000000B000)        /* 176 */
#define CC_R_175                           (0x00000000AF00)        /* 175 */
#define CC_R_174                           (0x00000000AE00)        /* 174 */
#define CC_R_173                           (0x00000000AD00)        /* 173 */
#define CC_R_172                           (0x00000000AC00)        /* 172 */
#define CC_R_171                           (0x00000000AB00)        /* 171 */
#define CC_R_170                           (0x00000000AA00)        /* 170 */
#define CC_R_169                           (0x00000000A900)        /* 169 */
#define CC_R_168                           (0x00000000A800)        /* 168 */
#define CC_R_167                           (0x00000000A700)        /* 167 */
#define CC_R_166                           (0x00000000A600)        /* 166 */
#define CC_R_165                           (0x00000000A500)        /* 165 */
#define CC_R_164                           (0x00000000A400)        /* 164 */
#define CC_R_163                           (0x00000000A300)        /* 163 */
#define CC_R_162                           (0x00000000A200)        /* 162 */
#define CC_R_161                           (0x00000000A100)        /* 161 */
#define CC_R_160                           (0x00000000A000)        /* 160 */
#define CC_R_159                           (0x000000009F00)        /* 159 */
#define CC_R_158                           (0x000000009E00)        /* 158 */
#define CC_R_157                           (0x000000009D00)        /* 157 */
#define CC_R_156                           (0x000000009C00)        /* 156 */
#define CC_R_155                           (0x000000009B00)        /* 155 */
#define CC_R_154                           (0x000000009A00)        /* 154 */
#define CC_R_153                           (0x000000009900)        /* 153 */
#define CC_R_152                           (0x000000009800)        /* 152 */
#define CC_R_151                           (0x000000009700)        /* 151 */
#define CC_R_150                           (0x000000009600)        /* 150 */
#define CC_R_149                           (0x000000009500)        /* 149 */
#define CC_R_148                           (0x000000009400)        /* 148 */
#define CC_R_147                           (0x000000009300)        /* 147 */
#define CC_R_146                           (0x000000009200)        /* 146 */
#define CC_R_145                           (0x000000009100)        /* 145 */
#define CC_R_144                           (0x000000009000)        /* 144 */
#define CC_R_143                           (0x000000008F00)        /* 143 */
#define CC_R_142                           (0x000000008E00)        /* 142 */
#define CC_R_141                           (0x000000008D00)        /* 141 */
#define CC_R_140                           (0x000000008C00)        /* 140 */
#define CC_R_139                           (0x000000008B00)        /* 139 */
#define CC_R_138                           (0x000000008A00)        /* 138 */
#define CC_R_137                           (0x000000008900)        /* 137 */
#define CC_R_136                           (0x000000008800)        /* 136 */
#define CC_R_135                           (0x000000008700)        /* 135 */
#define CC_R_134                           (0x000000008600)        /* 134 */
#define CC_R_133                           (0x000000008500)        /* 133 */
#define CC_R_132                           (0x000000008400)        /* 132 */
#define CC_R_131                           (0x000000008300)        /* 131 */
#define CC_R_130                           (0x000000008200)        /* 130 */
#define CC_R_129                           (0x000000008100)        /* 129 */
#define CC_R_128                           (0x000000008000)        /* 128 */
#define CC_R_127                           (0x000000007F00)        /* 127 */
#define CC_R_126                           (0x000000007E00)        /* 126 */
#define CC_R_125                           (0x000000007D00)        /* 125 */
#define CC_R_124                           (0x000000007C00)        /* 124 */
#define CC_R_123                           (0x000000007B00)        /* 123 */
#define CC_R_122                           (0x000000007A00)        /* 122 */
#define CC_R_121                           (0x000000007900)        /* 121 */
#define CC_R_120                           (0x000000007800)        /* 120 */
#define CC_R_119                           (0x000000007700)        /* 119 */
#define CC_R_118                           (0x000000007600)        /* 118 */
#define CC_R_117                           (0x000000007500)        /* 117 */
#define CC_R_116                           (0x000000007400)        /* 116 */
#define CC_R_115                           (0x000000007300)        /* 115 */
#define CC_R_114                           (0x000000007200)        /* 114 */
#define CC_R_113                           (0x000000007100)        /* 113 */
#define CC_R_112                           (0x000000007000)        /* 112 */
#define CC_R_111                           (0x000000006F00)        /* 111 */
#define CC_R_110                           (0x000000006E00)        /* 110 */
#define CC_R_109                           (0x000000006D00)        /* 109 */
#define CC_R_108                           (0x000000006C00)        /* 108 */
#define CC_R_107                           (0x000000006B00)        /* 107 */
#define CC_R_106                           (0x000000006A00)        /* 106 */
#define CC_R_105                           (0x000000006900)        /* 105 */
#define CC_R_104                           (0x000000006800)        /* 104 */
#define CC_R_103                           (0x000000006700)        /* 103 */
#define CC_R_102                           (0x000000006600)        /* 102 */
#define CC_R_101                           (0x000000006500)        /* 101 */
#define CC_R_100                           (0x000000006400)        /* 100 */
#define CC_R_99                            (0x000000006300)        /* 99 */
#define CC_R_98                            (0x000000006200)        /* 98 */
#define CC_R_97                            (0x000000006100)        /* 97 */
#define CC_R_96                            (0x000000006000)        /* 96 */
#define CC_R_95                            (0x000000005F00)        /* 95 */
#define CC_R_94                            (0x000000005E00)        /* 94 */
#define CC_R_93                            (0x000000005D00)        /* 93 */
#define CC_R_92                            (0x000000005C00)        /* 92 */
#define CC_R_91                            (0x000000005B00)        /* 91 */
#define CC_R_90                            (0x000000005A00)        /* 90 */
#define CC_R_89                            (0x000000005900)        /* 89 */
#define CC_R_88                            (0x000000005800)        /* 88 */
#define CC_R_87                            (0x000000005700)        /* 87 */
#define CC_R_86                            (0x000000005600)        /* 86 */
#define CC_R_85                            (0x000000005500)        /* 85 */
#define CC_R_84                            (0x000000005400)        /* 84 */
#define CC_R_83                            (0x000000005300)        /* 83 */
#define CC_R_82                            (0x000000005200)        /* 82 */
#define CC_R_81                            (0x000000005100)        /* 81 */
#define CC_R_80                            (0x000000005000)        /* 80 */
#define CC_R_79                            (0x000000004F00)        /* 79 */
#define CC_R_78                            (0x000000004E00)        /* 78 */
#define CC_R_77                            (0x000000004D00)        /* 77 */
#define CC_R_76                            (0x000000004C00)        /* 76 */
#define CC_R_75                            (0x000000004B00)        /* 75 */
#define CC_R_74                            (0x000000004A00)        /* 74 */
#define CC_R_73                            (0x000000004900)        /* 73 */
#define CC_R_72                            (0x000000004800)        /* 72 */
#define CC_R_71                            (0x000000004700)        /* 71 */
#define CC_R_70                            (0x000000004600)        /* 70 */
#define CC_R_69                            (0x000000004500)        /* 69 */
#define CC_R_68                            (0x000000004400)        /* 68 */
#define CC_R_67                            (0x000000004300)        /* 67 */
#define CC_R_66                            (0x000000004200)        /* 66 */
#define CC_R_65                            (0x000000004100)        /* 65 */
#define CC_R_64                            (0x000000004000)        /* 64 */
#define CC_R_63                            (0x000000003F00)        /* 63 */
#define CC_R_62                            (0x000000003E00)        /* 62 */
#define CC_R_61                            (0x000000003D00)        /* 61 */
#define CC_R_60                            (0x000000003C00)        /* 60 */
#define CC_R_59                            (0x000000003B00)        /* 59 */
#define CC_R_58                            (0x000000003A00)        /* 58 */
#define CC_R_57                            (0x000000003900)        /* 57 */
#define CC_R_56                            (0x000000003800)        /* 56 */
#define CC_R_55                            (0x000000003700)        /* 55 */
#define CC_R_54                            (0x000000003600)        /* 54 */
#define CC_R_53                            (0x000000003500)        /* 53 */
#define CC_R_52                            (0x000000003400)        /* 52 */
#define CC_R_51                            (0x000000003300)        /* 51 */
#define CC_R_50                            (0x000000003200)        /* 50 */
#define CC_R_49                            (0x000000003100)        /* 49 */
#define CC_R_48                            (0x000000003000)        /* 48 */
#define CC_R_47                            (0x000000002F00)        /* 47 */
#define CC_R_46                            (0x000000002E00)        /* 46 */
#define CC_R_45                            (0x000000002D00)        /* 45 */
#define CC_R_44                            (0x000000002C00)        /* 44 */
#define CC_R_43                            (0x000000002B00)        /* 43 */
#define CC_R_42                            (0x000000002A00)        /* 42 */
#define CC_R_41                            (0x000000002900)        /* 41 */
#define CC_R_40                            (0x000000002800)        /* 40 */
#define CC_R_39                            (0x000000002700)        /* 39 */
#define CC_R_38                            (0x000000002600)        /* 38 */
#define CC_R_37                            (0x000000002500)        /* 37 */
#define CC_R_36                            (0x000000002400)        /* 36 */
#define CC_R_35                            (0x000000002300)        /* 35 */
#define CC_R_34                            (0x000000002200)        /* 34 */
#define CC_R_33                            (0x000000002100)        /* 33 */
#define CC_R_32                            (0x000000002000)        /* 32 */
#define CC_R_31                            (0x000000001F00)        /* 31 */
#define CC_R_30                            (0x000000001E00)        /* 30 */
#define CC_R_29                            (0x000000001D00)        /* 29 */
#define CC_R_28                            (0x000000001C00)        /* 28 */
#define CC_R_27                            (0x000000001B00)        /* 27 */
#define CC_R_26                            (0x000000001A00)        /* 26 */
#define CC_R_25                            (0x000000001900)        /* 25 */
#define CC_R_24                            (0x000000001800)        /* 24 */
#define CC_R_23                            (0x000000001700)        /* 23 */
#define CC_R_22                            (0x000000001600)        /* 22 */
#define CC_R_21                            (0x000000001500)        /* 21 */
#define CC_R_20                            (0x000000001400)        /* 20 */
#define CC_R_19                            (0x000000001300)        /* 19 */
#define CC_R_18                            (0x000000001200)        /* 18 */
#define CC_R_17                            (0x000000001100)        /* 17 */
#define CC_R_16                            (0x000000001000)        /* 16 */
#define CC_R_15                            (0x000000000F00)        /* 15 */
#define CC_R_14                            (0x000000000E00)        /* 14 */
#define CC_R_13                            (0x000000000D00)        /* 13 */
#define CC_R_12                            (0x000000000C00)        /* 12 */
#define CC_R_11                            (0x000000000B00)        /* 11 */
#define CC_R_10                            (0x000000000A00)        /* 10 */
#define CC_R_9                             (0x000000000900)        /* 9 */
#define CC_R_8                             (0x000000000800)        /* 8 */
#define CC_R_7                             (0x000000000700)        /* 7 */
#define CC_R_6                             (0x000000000600)        /* 6 */
#define CC_R_5                             (0x000000000500)        /* 5 */
#define CC_R_4                             (0x000000000400)        /* 4 */
#define CC_R_3                             (0x000000000300)        /* 3 */
#define CC_R_2                             (0x000000000200)        /* 2 */
#define CC_R_1                             (0x000000000100)        /* 1 */
#define CC_R_0                             (0x000000000000)        /* 0 */
#define CC_R__255                          (0x00000000FF00)        /* 255 */
#define CC_R__254                          (0x00000000FE00)        /* 254 */
#define CC_R__253                          (0x00000000FD00)        /* 253 */
#define CC_R__252                          (0x00000000FC00)        /* 252 */
#define CC_R__251                          (0x00000000FB00)        /* 251 */
#define CC_R__250                          (0x00000000FA00)        /* 250 */
#define CC_R__249                          (0x00000000F900)        /* 249 */
#define CC_R__248                          (0x00000000F800)        /* 248 */
#define CC_R__247                          (0x00000000F700)        /* 247 */
#define CC_R__246                          (0x00000000F600)        /* 246 */
#define CC_R__245                          (0x00000000F500)        /* 245 */
#define CC_R__244                          (0x00000000F400)        /* 244 */
#define CC_R__243                          (0x00000000F300)        /* 243 */
#define CC_R__242                          (0x00000000F200)        /* 242 */
#define CC_R__241                          (0x00000000F100)        /* 241 */
#define CC_R__240                          (0x00000000F000)        /* 240 */
#define CC_R__239                          (0x00000000EF00)        /* 239 */
#define CC_R__238                          (0x00000000EE00)        /* 238 */
#define CC_R__237                          (0x00000000ED00)        /* 237 */
#define CC_R__236                          (0x00000000EC00)        /* 236 */
#define CC_R__235                          (0x00000000EB00)        /* 235 */
#define CC_R__234                          (0x00000000EA00)        /* 234 */
#define CC_R__233                          (0x00000000E900)        /* 233 */
#define CC_R__232                          (0x00000000E800)        /* 232 */
#define CC_R__231                          (0x00000000E700)        /* 231 */
#define CC_R__230                          (0x00000000E600)        /* 230 */
#define CC_R__229                          (0x00000000E500)        /* 229 */
#define CC_R__228                          (0x00000000E400)        /* 228 */
#define CC_R__227                          (0x00000000E300)        /* 227 */
#define CC_R__226                          (0x00000000E200)        /* 226 */
#define CC_R__225                          (0x00000000E100)        /* 225 */
#define CC_R__224                          (0x00000000E000)        /* 224 */
#define CC_R__223                          (0x00000000DF00)        /* 223 */
#define CC_R__222                          (0x00000000DE00)        /* 222 */
#define CC_R__221                          (0x00000000DD00)        /* 221 */
#define CC_R__220                          (0x00000000DC00)        /* 220 */
#define CC_R__219                          (0x00000000DB00)        /* 219 */
#define CC_R__218                          (0x00000000DA00)        /* 218 */
#define CC_R__217                          (0x00000000D900)        /* 217 */
#define CC_R__216                          (0x00000000D800)        /* 216 */
#define CC_R__215                          (0x00000000D700)        /* 215 */
#define CC_R__214                          (0x00000000D600)        /* 214 */
#define CC_R__213                          (0x00000000D500)        /* 213 */
#define CC_R__212                          (0x00000000D400)        /* 212 */
#define CC_R__211                          (0x00000000D300)        /* 211 */
#define CC_R__210                          (0x00000000D200)        /* 210 */
#define CC_R__209                          (0x00000000D100)        /* 209 */
#define CC_R__208                          (0x00000000D000)        /* 208 */
#define CC_R__207                          (0x00000000CF00)        /* 207 */
#define CC_R__206                          (0x00000000CE00)        /* 206 */
#define CC_R__205                          (0x00000000CD00)        /* 205 */
#define CC_R__204                          (0x00000000CC00)        /* 204 */
#define CC_R__203                          (0x00000000CB00)        /* 203 */
#define CC_R__202                          (0x00000000CA00)        /* 202 */
#define CC_R__201                          (0x00000000C900)        /* 201 */
#define CC_R__200                          (0x00000000C800)        /* 200 */
#define CC_R__199                          (0x00000000C700)        /* 199 */
#define CC_R__198                          (0x00000000C600)        /* 198 */
#define CC_R__197                          (0x00000000C500)        /* 197 */
#define CC_R__196                          (0x00000000C400)        /* 196 */
#define CC_R__195                          (0x00000000C300)        /* 195 */
#define CC_R__194                          (0x00000000C200)        /* 194 */
#define CC_R__193                          (0x00000000C100)        /* 193 */
#define CC_R__192                          (0x00000000C000)        /* 192 */
#define CC_R__191                          (0x00000000BF00)        /* 191 */
#define CC_R__190                          (0x00000000BE00)        /* 190 */
#define CC_R__189                          (0x00000000BD00)        /* 189 */
#define CC_R__188                          (0x00000000BC00)        /* 188 */
#define CC_R__187                          (0x00000000BB00)        /* 187 */
#define CC_R__186                          (0x00000000BA00)        /* 186 */
#define CC_R__185                          (0x00000000B900)        /* 185 */
#define CC_R__184                          (0x00000000B800)        /* 184 */
#define CC_R__183                          (0x00000000B700)        /* 183 */
#define CC_R__182                          (0x00000000B600)        /* 182 */
#define CC_R__181                          (0x00000000B500)        /* 181 */
#define CC_R__180                          (0x00000000B400)        /* 180 */
#define CC_R__179                          (0x00000000B300)        /* 179 */
#define CC_R__178                          (0x00000000B200)        /* 178 */
#define CC_R__177                          (0x00000000B100)        /* 177 */
#define CC_R__176                          (0x00000000B000)        /* 176 */
#define CC_R__175                          (0x00000000AF00)        /* 175 */
#define CC_R__174                          (0x00000000AE00)        /* 174 */
#define CC_R__173                          (0x00000000AD00)        /* 173 */
#define CC_R__172                          (0x00000000AC00)        /* 172 */
#define CC_R__171                          (0x00000000AB00)        /* 171 */
#define CC_R__170                          (0x00000000AA00)        /* 170 */
#define CC_R__169                          (0x00000000A900)        /* 169 */
#define CC_R__168                          (0x00000000A800)        /* 168 */
#define CC_R__167                          (0x00000000A700)        /* 167 */
#define CC_R__166                          (0x00000000A600)        /* 166 */
#define CC_R__165                          (0x00000000A500)        /* 165 */
#define CC_R__164                          (0x00000000A400)        /* 164 */
#define CC_R__163                          (0x00000000A300)        /* 163 */
#define CC_R__162                          (0x00000000A200)        /* 162 */
#define CC_R__161                          (0x00000000A100)        /* 161 */
#define CC_R__160                          (0x00000000A000)        /* 160 */
#define CC_R__159                          (0x000000009F00)        /* 159 */
#define CC_R__158                          (0x000000009E00)        /* 158 */
#define CC_R__157                          (0x000000009D00)        /* 157 */
#define CC_R__156                          (0x000000009C00)        /* 156 */
#define CC_R__155                          (0x000000009B00)        /* 155 */
#define CC_R__154                          (0x000000009A00)        /* 154 */
#define CC_R__153                          (0x000000009900)        /* 153 */
#define CC_R__152                          (0x000000009800)        /* 152 */
#define CC_R__151                          (0x000000009700)        /* 151 */
#define CC_R__150                          (0x000000009600)        /* 150 */
#define CC_R__149                          (0x000000009500)        /* 149 */
#define CC_R__148                          (0x000000009400)        /* 148 */
#define CC_R__147                          (0x000000009300)        /* 147 */
#define CC_R__146                          (0x000000009200)        /* 146 */
#define CC_R__145                          (0x000000009100)        /* 145 */
#define CC_R__144                          (0x000000009000)        /* 144 */
#define CC_R__143                          (0x000000008F00)        /* 143 */
#define CC_R__142                          (0x000000008E00)        /* 142 */
#define CC_R__141                          (0x000000008D00)        /* 141 */
#define CC_R__140                          (0x000000008C00)        /* 140 */
#define CC_R__139                          (0x000000008B00)        /* 139 */
#define CC_R__138                          (0x000000008A00)        /* 138 */
#define CC_R__137                          (0x000000008900)        /* 137 */
#define CC_R__136                          (0x000000008800)        /* 136 */
#define CC_R__135                          (0x000000008700)        /* 135 */
#define CC_R__134                          (0x000000008600)        /* 134 */
#define CC_R__133                          (0x000000008500)        /* 133 */
#define CC_R__132                          (0x000000008400)        /* 132 */
#define CC_R__131                          (0x000000008300)        /* 131 */
#define CC_R__130                          (0x000000008200)        /* 130 */
#define CC_R__129                          (0x000000008100)        /* 129 */
#define CC_R__128                          (0x000000008000)        /* 128 */
#define CC_R__127                          (0x000000007F00)        /* 127 */
#define CC_R__126                          (0x000000007E00)        /* 126 */
#define CC_R__125                          (0x000000007D00)        /* 125 */
#define CC_R__124                          (0x000000007C00)        /* 124 */
#define CC_R__123                          (0x000000007B00)        /* 123 */
#define CC_R__122                          (0x000000007A00)        /* 122 */
#define CC_R__121                          (0x000000007900)        /* 121 */
#define CC_R__120                          (0x000000007800)        /* 120 */
#define CC_R__119                          (0x000000007700)        /* 119 */
#define CC_R__118                          (0x000000007600)        /* 118 */
#define CC_R__117                          (0x000000007500)        /* 117 */
#define CC_R__116                          (0x000000007400)        /* 116 */
#define CC_R__115                          (0x000000007300)        /* 115 */
#define CC_R__114                          (0x000000007200)        /* 114 */
#define CC_R__113                          (0x000000007100)        /* 113 */
#define CC_R__112                          (0x000000007000)        /* 112 */
#define CC_R__111                          (0x000000006F00)        /* 111 */
#define CC_R__110                          (0x000000006E00)        /* 110 */
#define CC_R__109                          (0x000000006D00)        /* 109 */
#define CC_R__108                          (0x000000006C00)        /* 108 */
#define CC_R__107                          (0x000000006B00)        /* 107 */
#define CC_R__106                          (0x000000006A00)        /* 106 */
#define CC_R__105                          (0x000000006900)        /* 105 */
#define CC_R__104                          (0x000000006800)        /* 104 */
#define CC_R__103                          (0x000000006700)        /* 103 */
#define CC_R__102                          (0x000000006600)        /* 102 */
#define CC_R__101                          (0x000000006500)        /* 101 */
#define CC_R__100                          (0x000000006400)        /* 100 */
#define CC_R__99                           (0x000000006300)        /* 99 */
#define CC_R__98                           (0x000000006200)        /* 98 */
#define CC_R__97                           (0x000000006100)        /* 97 */
#define CC_R__96                           (0x000000006000)        /* 96 */
#define CC_R__95                           (0x000000005F00)        /* 95 */
#define CC_R__94                           (0x000000005E00)        /* 94 */
#define CC_R__93                           (0x000000005D00)        /* 93 */
#define CC_R__92                           (0x000000005C00)        /* 92 */
#define CC_R__91                           (0x000000005B00)        /* 91 */
#define CC_R__90                           (0x000000005A00)        /* 90 */
#define CC_R__89                           (0x000000005900)        /* 89 */
#define CC_R__88                           (0x000000005800)        /* 88 */
#define CC_R__87                           (0x000000005700)        /* 87 */
#define CC_R__86                           (0x000000005600)        /* 86 */
#define CC_R__85                           (0x000000005500)        /* 85 */
#define CC_R__84                           (0x000000005400)        /* 84 */
#define CC_R__83                           (0x000000005300)        /* 83 */
#define CC_R__82                           (0x000000005200)        /* 82 */
#define CC_R__81                           (0x000000005100)        /* 81 */
#define CC_R__80                           (0x000000005000)        /* 80 */
#define CC_R__79                           (0x000000004F00)        /* 79 */
#define CC_R__78                           (0x000000004E00)        /* 78 */
#define CC_R__77                           (0x000000004D00)        /* 77 */
#define CC_R__76                           (0x000000004C00)        /* 76 */
#define CC_R__75                           (0x000000004B00)        /* 75 */
#define CC_R__74                           (0x000000004A00)        /* 74 */
#define CC_R__73                           (0x000000004900)        /* 73 */
#define CC_R__72                           (0x000000004800)        /* 72 */
#define CC_R__71                           (0x000000004700)        /* 71 */
#define CC_R__70                           (0x000000004600)        /* 70 */
#define CC_R__69                           (0x000000004500)        /* 69 */
#define CC_R__68                           (0x000000004400)        /* 68 */
#define CC_R__67                           (0x000000004300)        /* 67 */
#define CC_R__66                           (0x000000004200)        /* 66 */
#define CC_R__65                           (0x000000004100)        /* 65 */
#define CC_R__64                           (0x000000004000)        /* 64 */
#define CC_R__63                           (0x000000003F00)        /* 63 */
#define CC_R__62                           (0x000000003E00)        /* 62 */
#define CC_R__61                           (0x000000003D00)        /* 61 */
#define CC_R__60                           (0x000000003C00)        /* 60 */
#define CC_R__59                           (0x000000003B00)        /* 59 */
#define CC_R__58                           (0x000000003A00)        /* 58 */
#define CC_R__57                           (0x000000003900)        /* 57 */
#define CC_R__56                           (0x000000003800)        /* 56 */
#define CC_R__55                           (0x000000003700)        /* 55 */
#define CC_R__54                           (0x000000003600)        /* 54 */
#define CC_R__53                           (0x000000003500)        /* 53 */
#define CC_R__52                           (0x000000003400)        /* 52 */
#define CC_R__51                           (0x000000003300)        /* 51 */
#define CC_R__50                           (0x000000003200)        /* 50 */
#define CC_R__49                           (0x000000003100)        /* 49 */
#define CC_R__48                           (0x000000003000)        /* 48 */
#define CC_R__47                           (0x000000002F00)        /* 47 */
#define CC_R__46                           (0x000000002E00)        /* 46 */
#define CC_R__45                           (0x000000002D00)        /* 45 */
#define CC_R__44                           (0x000000002C00)        /* 44 */
#define CC_R__43                           (0x000000002B00)        /* 43 */
#define CC_R__42                           (0x000000002A00)        /* 42 */
#define CC_R__41                           (0x000000002900)        /* 41 */
#define CC_R__40                           (0x000000002800)        /* 40 */
#define CC_R__39                           (0x000000002700)        /* 39 */
#define CC_R__38                           (0x000000002600)        /* 38 */
#define CC_R__37                           (0x000000002500)        /* 37 */
#define CC_R__36                           (0x000000002400)        /* 36 */
#define CC_R__35                           (0x000000002300)        /* 35 */
#define CC_R__34                           (0x000000002200)        /* 34 */
#define CC_R__33                           (0x000000002100)        /* 33 */
#define CC_R__32                           (0x000000002000)        /* 32 */
#define CC_R__31                           (0x000000001F00)        /* 31 */
#define CC_R__30                           (0x000000001E00)        /* 30 */
#define CC_R__29                           (0x000000001D00)        /* 29 */
#define CC_R__28                           (0x000000001C00)        /* 28 */
#define CC_R__27                           (0x000000001B00)        /* 27 */
#define CC_R__26                           (0x000000001A00)        /* 26 */
#define CC_R__25                           (0x000000001900)        /* 25 */
#define CC_R__24                           (0x000000001800)        /* 24 */
#define CC_R__23                           (0x000000001700)        /* 23 */
#define CC_R__22                           (0x000000001600)        /* 22 */
#define CC_R__21                           (0x000000001500)        /* 21 */
#define CC_R__20                           (0x000000001400)        /* 20 */
#define CC_R__19                           (0x000000001300)        /* 19 */
#define CC_R__18                           (0x000000001200)        /* 18 */
#define CC_R__17                           (0x000000001100)        /* 17 */
#define CC_R__16                           (0x000000001000)        /* 16 */
#define CC_R__15                           (0x000000000F00)        /* 15 */
#define CC_R__14                           (0x000000000E00)        /* 14 */
#define CC_R__13                           (0x000000000D00)        /* 13 */
#define CC_R__12                           (0x000000000C00)        /* 12 */
#define CC_R__11                           (0x000000000B00)        /* 11 */
#define CC_R__10                           (0x000000000A00)        /* 10 */
#define CC_R__9                            (0x000000000900)        /* 9 */
#define CC_R__8                            (0x000000000800)        /* 8 */
#define CC_R__7                            (0x000000000700)        /* 7 */
#define CC_R__6                            (0x000000000600)        /* 6 */
#define CC_R__5                            (0x000000000500)        /* 5 */
#define CC_R__4                            (0x000000000400)        /* 4 */
#define CC_R__3                            (0x000000000300)        /* 3 */
#define CC_R__2                            (0x000000000200)        /* 2 */
#define CC_R__1                            (0x000000000100)        /* 1 */
#define CC_R__0                            (0x000000000000)        /* 0 */
#define LOD_LSD_RB_1                       (0x000000000080)        /* enable */
#define LOD_LSD_RB_0                       (0x000000000000)        /* disable */
#define LOD_LSD_RB__1                      (0x000000000080)        /* enable */
#define LOD_LSD_RB__0                      (0x000000000000)        /* disable */
#define LODVTH_B__1V2                      (0x000000000030)        /* VLEDB-1.2 V */
#define LODVTH_B__0V9                      (0x000000000020)        /* VLEDB-0.9 V */
#define LODVTH_B__0V5                      (0x000000000010)        /* VLEDB-0.5 V */
#define LODVTH_B__0V2                      (0x000000000000)        /* VLEDB-0.2 V */
#define LODVTH_G__1V2                      (0x00000000000C)        /* VLEDG-1.2 V */
#define LODVTH_G__0V9                      (0x000000000008)        /* VLEDG-0.9 V */
#define LODVTH_G__0V5                      (0x000000000004)        /* VLEDG-0.5 V */
#define LODVTH_G__0V2                      (0x000000000000)        /* VLEDG-0.2 V */
#define LODVTH_R__1V2                      (0x000000000003)        /* VLEDR-1.2 V */
#define LODVTH_R__0V9                      (0x000000000002)        /* VLEDR-0.9 V */
#define LODVTH_R__0V5                      (0x000000000001)        /* VLEDR-0.5 V */
#define LODVTH_R__0V2                      (0x000000000000)        /* VLEDR-0.2 V */

/* FC4  Bits */
#define DE_COUPLE3_EN_1                    (0x100000000000)        /* enabled */
#define DE_COUPLE3_EN_0                    (0x000000000000)        /* disabled */
#define DE_COUPLE3_EN__1                   (0x100000000000)        /* enabled */
#define DE_COUPLE3_EN__0                   (0x000000000000)        /* disabled */
#define DE_COUPLE3__16                     (0x0F0000000000)        /* 16 */
#define DE_COUPLE3__15                     (0x0E0000000000)        /* 15 */
#define DE_COUPLE3__14                     (0x0D0000000000)        /* 14 */
#define DE_COUPLE3__13                     (0x0C0000000000)        /* 13 */
#define DE_COUPLE3__12                     (0x0B0000000000)        /* 12 */
#define DE_COUPLE3__11                     (0x0A0000000000)        /* 11 */
#define DE_COUPLE3__10                     (0x090000000000)        /* 10 */
#define DE_COUPLE3__9                      (0x080000000000)        /* 9 */
#define DE_COUPLE3__8                      (0x070000000000)        /* 8 */
#define DE_COUPLE3__7                      (0x060000000000)        /* 7 */
#define DE_COUPLE3__6                      (0x050000000000)        /* 6 */
#define DE_COUPLE3__5                      (0x040000000000)        /* 5 */
#define DE_COUPLE3__4                      (0x030000000000)        /* 4 */
#define DE_COUPLE3__3                      (0x020000000000)        /* 3 */
#define DE_COUPLE3__2                      (0x010000000000)        /* 2 */
#define DE_COUPLE3__1                      (0x000000000000)        /* 1 */
#define DE_COUPLE2_1                       (0x008000000000)        /* enabled */
#define DE_COUPLE2_0                       (0x000000000000)        /* disabled */
#define DE_COUPLE2__1                      (0x008000000000)        /* enabled */
#define DE_COUPLE2__0                      (0x000000000000)        /* disabled */
#define FIRST_LINE_DIM__16                 (0x007800000000)        /* 16 */
#define FIRST_LINE_DIM__15                 (0x007000000000)        /* 15 */
#define FIRST_LINE_DIM__14                 (0x006800000000)        /* 14 */
#define FIRST_LINE_DIM__13                 (0x006000000000)        /* 13 */
#define FIRST_LINE_DIM__12                 (0x005800000000)        /* 12 */
#define FIRST_LINE_DIM__11                 (0x005000000000)        /* 11 */
#define FIRST_LINE_DIM__10                 (0x004800000000)        /* 10 */
#define FIRST_LINE_DIM__9                  (0x004000000000)        /* 9 */
#define FIRST_LINE_DIM__8                  (0x003800000000)        /* 8 */
#define FIRST_LINE_DIM__7                  (0x003000000000)        /* 7 */
#define FIRST_LINE_DIM__6                  (0x002800000000)        /* 6 */
#define FIRST_LINE_DIM__5                  (0x002000000000)        /* 5 */
#define FIRST_LINE_DIM__4                  (0x001800000000)        /* 4 */
#define FIRST_LINE_DIM__3                  (0x001000000000)        /* 3 */
#define FIRST_LINE_DIM__2                  (0x000800000000)        /* 2 */
#define FIRST_LINE_DIM__1                  (0x000000000000)        /* 1 */
#define LG_CAURSE_B_1                      (0x000400000000)        /* enabled */
#define LG_CAURSE_B_0                      (0x000000000000)        /* disabled */
#define LG_CAURSE_B__1                     (0x000400000000)        /* enabled */
#define LG_CAURSE_B__0                     (0x000000000000)        /* disabled */
#define LG_CAURSE_G_1                      (0x000200000000)        /* enabled */
#define LG_CAURSE_G_0                      (0x000000000000)        /* disabled */
#define LG_CAURSE_G__1                     (0x000200000000)        /* enabled */
#define LG_CAURSE_G__0                     (0x000000000000)        /* disabled */
#define LG_CAURSE_R_1                      (0x000100000000)        /* enabled */
#define LG_CAURSE_R_0                      (0x000000000000)        /* disabled */
#define LG_CAURSE_R__1                     (0x000100000000)        /* enabled */
#define LG_CAURSE_R__0                     (0x000000000000)        /* disabled */
#define CAURSE_B_1                         (0x000400000000)        /* enabled */
#define CAURSE_B_0                         (0x000000000000)        /* disabled */
#define CAURSE_B__1                        (0x000400000000)        /* enabled */
#define CAURSE_B__0                        (0x000000000000)        /* disabled */
#define CAURSE_G_1                         (0x000200000000)        /* enabled */
#define CAURSE_G_0                         (0x000000000000)        /* disabled */
#define CAURSE_G__1                        (0x000200000000)        /* enabled */
#define CAURSE_G__0                        (0x000000000000)        /* disabled */
#define CAURSE_R_1                         (0x000100000000)        /* enabled */
#define CAURSE_R_0                         (0x000000000000)        /* disabled */
#define CAURSE_R__1                        (0x000100000000)        /* enabled */
#define CAURSE_R__0                        (0x000000000000)        /* disabled */
#define SR_ON_B_3                          (0x00000C000000)        /* faster slew rate */
#define SR_ON_B_2                          (0x000008000000)        /* fast slew rate */
#define SR_ON_B_1                          (0x000004000000)        /* slow slew rate */
#define SR_ON_B_0                          (0x000000000000)        /* slower slew rate */
#define SR_ON_B__3                         (0x00000C000000)        /* faster slew rate */
#define SR_ON_B__2                         (0x000008000000)        /* fast slew rate */
#define SR_ON_B__1                         (0x000004000000)        /* slow slew rate */
#define SR_ON_B__0                         (0x000000000000)        /* slower slew rate */
#define SR_ON_G_3                          (0x000003000000)        /* faster slew rate */
#define SR_ON_G_2                          (0x000002000000)        /* fast slew rate */
#define SR_ON_G_1                          (0x000001000000)        /* slow slew rate */
#define SR_ON_G_0                          (0x000000000000)        /* slower slew rate */
#define SR_ON_G__3                         (0x000003000000)        /* faster slew rate */
#define SR_ON_G__2                         (0x000002000000)        /* fast slew rate */
#define SR_ON_G__1                         (0x000001000000)        /* slow slew rate */
#define SR_ON_G__0                         (0x000000000000)        /* slower slew rate */
#define SR_ON_R_3                          (0x000000C00000)        /* faster slew rate */
#define SR_ON_R_2                          (0x000000800000)        /* fast slew rate */
#define SR_ON_R_1                          (0x000000400000)        /* slow slew rate */
#define SR_ON_R_0                          (0x000000000000)        /* slower slew rate */
#define SR_ON_R__3                         (0x000000C00000)        /* faster slew rate */
#define SR_ON_R__2                         (0x000000800000)        /* fast slew rate */
#define SR_ON_R__1                         (0x000000400000)        /* slow slew rate */
#define SR_ON_R__0                         (0x000000000000)        /* slower slew rate */
#define SR_OFF_B_1                         (0x000000200000)        /* fast slew rate */
#define SR_OFF_B_0                         (0x000000000000)        /* slow slew rate */
#define SR_OFF_B__1                        (0x000000200000)        /* fast slew rate */
#define SR_OFF_B__0                        (0x000000000000)        /* slow slew rate */
#define SR_OFF_G_1                         (0x000000100000)        /* fast slew rate */
#define SR_OFF_G_0                         (0x000000000000)        /* slow slew rate */
#define SR_OFF_G__1                        (0x000000100000)        /* fast slew rate */
#define SR_OFF_G__0                        (0x000000000000)        /* slow slew rate */
#define SR_OFF_R_1                         (0x000000080000)        /* fast slew rate */
#define SR_OFF_R_0                         (0x000000000000)        /* slow slew rate */
#define SR_OFF_R__1                        (0x000000080000)        /* fast slew rate */
#define SR_OFF_R__0                        (0x000000000000)        /* slow slew rate */
#define LG_FINE_B_1                        (0x000000040000)        /* enable */
#define LG_FINE_B_0                        (0x000000000000)        /* disable */
#define LG_FINE_B__1                       (0x000000040000)        /* enable */
#define LG_FINE_B__0                       (0x000000000000)        /* disable */
#define LG_FINE_G_1                        (0x000000020000)        /* enable */
#define LG_FINE_G_0                        (0x000000000000)        /* disable */
#define LG_FINE_G__1                       (0x000000020000)        /* enable */
#define LG_FINE_G__0                       (0x000000000000)        /* disable */
#define LG_FINE_R_1                        (0x000000010000)        /* enable */
#define LG_FINE_R_0                        (0x000000000000)        /* disable */
#define LG_FINE_R__1                       (0x000000010000)        /* enable */
#define LG_FINE_R__0                       (0x000000000000)        /* disable */
#define FINE_B_1                           (0x000000040000)        /* enable */
#define FINE_B_0                           (0x000000000000)        /* disable */
#define FINE_B__1                          (0x000000040000)        /* enable */
#define FINE_B__0                          (0x000000000000)        /* disable */
#define FINE_G_1                           (0x000000020000)        /* enable */
#define FINE_G_0                           (0x000000000000)        /* disable */
#define FINE_G__1                          (0x000000020000)        /* enable */
#define FINE_G__0                          (0x000000000000)        /* disable */
#define FINE_R_1                           (0x000000010000)        /* enable */
#define FINE_R_0                           (0x000000000000)        /* disable */
#define FINE_R__1                          (0x000000010000)        /* enable */
#define FINE_R__0                          (0x000000000000)        /* disable */
#define SCAN_REV_1                         (0x000000004000)        /* L0-L15, L31-L16 */
#define SCAN_REV_0                         (0x000000000000)        /* L0-L15, L16-L31 */
#define SCAN_REV__1                        (0x000000004000)        /* L0-L15, L31-L16 */
#define SCAN_REV__0                        (0x000000000000)        /* L0-L15, L16-L31 */
#define IMAX_1                             (0x000000000002)        /* 20 mA maximum */
#define IMAX_0                             (0x000000000000)        /* 10 mA maximum */
#define IMAX__20                           (0x000000000002)        /* 20 mA maximum */
#define IMAX__10                           (0x000000000000)        /* 10 mA maximum */

#endif /* CLB_EX32_LP5891_H_ */
