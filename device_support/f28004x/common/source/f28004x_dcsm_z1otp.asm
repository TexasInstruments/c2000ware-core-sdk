;;#############################################################################
;;
;; FILE:   f28004x_dcsm_z1otp.asm
;;
;; TITLE:  Dual Code Security Module Zone 1 OTP
;;
;; DESCRIPTION:
;;
;;         This file is used to specify Z1 DCSM OTP and zone select block
;;         values to program.
;;
;;         In addition, the 60 reserved values after the zone select block
;;         are all programmed to 0x0000 as well.
;;
;; !!IMPORTANT!! The below memory sections are mapped to OTP (one-time
;; programmable) memory with the *dcsm_lnk.cmd linker command file. In order
;; to program the below memory sections, user should uncomment the .long words
;; of each section and change the value to what is desired. Additionally, the
;; corresponding section of *dcsm_lnk.cmd should no longer be labelled as a
;; dummy section. Remove ", type = DSECT" in SECTIONS from the memory section
;; that is being programmed.
;;
;; !!IMPORTANT!! The "dcsm_otp_bx_z1" section contains the Z1 LINKPOINTER which
;; determines the location of the Z1 Zone Select block.  If the LINKPOINTER
;; is changed, then the "dcsm_zsel_bx_z1" section in the *_dcsm_lnk.cmd
;; command linker file must also change to an address decoded from the value
;; specified in the Z1-LINKPOINTER location.
;;
;; The "dcsm_zsel_bx_z1" section contains the actual Z1 Zone Select Block
;; values that will be linked and programmed into to the DCSM Z1 OTP Zone
;; Select block in OTP.
;; These values must be known in order to unlock the CSM module.
;; Refer TRM for default values for the password locations.
;;
;; It is recommended that all values be left as at default during code
;; development. When code development is complete, modify values as required.
;; The new values has to take ECC values as well in to consideration (only bits 
;; with value of '1' can be changed to '0' and NOT vice versa).
;;
;; TI ships this example commenting out the initialization of all the
;; below locations, users need to enable them for programming these values.
;;
;;#############################################################################
;; $Copyright:
;// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
;//
;// Redistribution and use in source and binary forms, with or without 
;// modification, are permitted provided that the following conditions 
;// are met:
;// 
;//   Redistributions of source code must retain the above copyright 
;//   notice, this list of conditions and the following disclaimer.
;// 
;//   Redistributions in binary form must reproduce the above copyright
;//   notice, this list of conditions and the following disclaimer in the 
;//   documentation and/or other materials provided with the   
;//   distribution.
;// 
;//   Neither the name of Texas Instruments Incorporated nor the names of
;//   its contributors may be used to endorse or promote products derived
;//   from this software without specific prior written permission.
;// 
;// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
;// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
;// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
;// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
;// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
;// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
;// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
;// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
;// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
;// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;// $
;;#############################################################################

      .sect "b0_dcsm_otp_z1_linkpointer"
	  .retain
;;    .long 0x1FFFFFFF     ;B0_Z1OTP_LINKPOINTER1
;;    .long 0xFFFFFFFF     ;Reserved
;;    .long 0x1FFFFFFF     ;B0_Z1OTP_LINKPOINTER2
;;    .long 0xFFFFFFFF     ;Reserved
;;    .long 0x1FFFFFFF     ;B0_Z1OTP_LINKPOINTER3
;;    .long 0xFFFFFFFF     ;Reserved

      .sect "b0_dcsm_otp_z1_gpreg"
	  .retain
;;    See the ROM Code and Peripheral Booting chapter of TRM for more details.
;;
;;    Below is a description of the bit fields of Z1OTP_BOOTPIN_CONFIG
;;    used by Boot ROM.
;;
;;    | Key (31-24) | BMSP2 (23-16) | BMSP1 (15-8) | BMSP0 (7-0) |
;;
;;    Below is a description of the bit fields of Z1OTP_GPREG2 used by 
;;    Boot ROM.
;;
;;    | Key (31-24) | RSVD (23-8) |  RSVD (7-6) | ESP (5-4) | RSVD (3-0) |
;;
;;    .long 0xFFFFFFFF     ;Z1OTP_BOOTPIN_CONFIG
;;    .long 0xFFFFFFFF     ;Z1OTP_GPREG2

      .sect "b0_dcsm_otp_z1_pswdlock"
	  .retain
;;    .long 0xfb7fffff     ;Z1-PSWDLOCK
;;    .long 0x7fffffff     ;Reserved

      .sect "b0_dcsm_otp_z1_crclock"
	  .retain
;;    .long 0x4bffffff     ;Z1-CRCLOCK
;;    .long 0x3fffffff     ;Reserved

      .sect "b0_dcsm_otp_z1_bootctrl"
	  .retain
;;    See the ROM Code and Peripheral Booting chapter of TRM for more details.
;;
;;    Below is a description of the bit fields of Z1OTP_BOOTDEF_LOW used by 
;;    Boot ROM.
;;
;;    | BOOT_DEF3(31-24) | BOOT_DEF2(23-16) | BOOT_DEF1(15-8) | BOOT_DEF0(7-0) |
;;
;;    Below is a description of the bit fields of Z1OTP_BOOTDEF_HIGH
;;    used by Boot ROM.
;;
;;    | BOOT_DEF7(31-24) | BOOT_DEF6(23-16) | BOOT_DEF5(15-8) | BOOT_DEF4(7-0) |
;;
;;    .long 0xFFFFFFFF     ;Z1OTP_BOOTDEF_LOW
;;    .long 0xFFFFFFFF     ;Z1OTP_BOOTDEF_HIGH

      .sect "b0_dcsm_zsel_z1"
	  .retain

;;    .long 0xFFFFFFFF     ;B0_Z1OTP_EXEONLYRAM
;;    .long 0xFFFFFFFF     ;B0_Z1OTP_EXEONLYSECT
;;    .long 0xFFFFFFFF     ;B0_Z1OTP_GRABRAM
;;    .long 0xFFFFFFFF     ;B0_Z1OTP_GRABSECT

;;    .long 0xFFFFFFFF     ;B0_Z1OTP_CSMPSWD0 (LSW of 128-bit password)
;;    .long 0x47ffffff     ;B0_Z1OTP_CSMPSWD1 // this value is for ZSB0
;;    .long 0xFFFFFFFF     ;B0_Z1OTP_CSMPSWD2
;;    .long 0xFFFFFFFF     ;B0_Z1OTP_CSMPSWD3 (MSW of 128-bit password)

      .sect "b1_dcsm_otp_z1_linkpointer"
	  .retain
;;    .long 0x1FFFFFFF     ;B1_Z1OTP_LINKPOINTER1
;;    .long 0xFFFFFFFF     ;Reserved
;;    .long 0x1FFFFFFF     ;B1_Z1OTP_LINKPOINTER2
;;    .long 0xFFFFFFFF     ;Reserved
;;    .long 0x1FFFFFFF     ;B1_Z1OTP_LINKPOINTER3
;;    .long 0xFFFFFFFF     ;Reserved

      .sect "b1_dcsm_zsel_z1"
	  .retain
;;    .long 0xFFFFFFFF     ;Reserved
;;    .long 0xFFFFFFFF     ;B1_Z1OTP_EXEONLYSECT
;;    .long 0xFFFFFFFF     ;Reserved
;;    .long 0xFFFFFFFF     ;B1_Z1OTP_GRABSECT

;;    .long 0xFFFFFFFF     ;Reserved
;;    .long 0xFFFFFFFF     ;Reserved
;;    .long 0xFFFFFFFF     ;Reserved
;;    .long 0xFFFFFFFF     ;Reserved

;;----------------------------------------------------------------------

;; For code security operation,after development has completed, prior to
;; production, all other zone select block locations should be programmed
;; to 0x0000 for maximum security.
;; If the first zone select block at offset 0x10 is used, the section
;; "dcsm_rsvd_z1" can be used to program these locations to 0x0000.
;; This code is commented out for development.

;;        .sect "dcsm_rsvd_z1"
;;        .retain
;;        .loop (1e0h)
;;              .int 0x0000
;;        .endloop


;;#############################################################################
;; End of file
;;#############################################################################
