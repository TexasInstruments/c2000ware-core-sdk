/* This linker command file is to be included if user wants to use the DCSM
 * feature on the device DCSM  means Dual Zone Code Security Module. This
 * linker command file works as an addendum to the already existing Flash/RAM
 * linker command file that the project has.
 * The sections in the *_dcsm_zxotp.asm source file is linked as per the
 * commands given in the file 
 * NOTE - Once users are confident that they want to program the passwords in
 * OTP, the DSECT section type can be removed.
 *
*/

MEMORY
{
   /* DCSM Z1 & Z2 Zone Select Contents (!!Movable!!) */

   /* Z1 OTP.  Z1 password locations / Flash and RAM partitioning */
   DCSM_OTP_Z1_LINK            : origin = 0x78000, length = 0x00006
   DCSM_OTP_Z1_JLM_ENABLE      : origin = 0x78006, length = 0x00002
   DCSM_OTP_Z1_GPREG           : origin = 0x78008, length = 0x00008
   DCSM_OTP_Z1_PSWD_LOCK       : origin = 0x78010, length = 0x00002
   DCSM_OTP_Z1_CRC_LOCK        : origin = 0x78012, length = 0x00002
   DCSM_OTP_Z1_JTAG_PSWDH      : origin = 0x78014, length = 0x00004
   DCSM_OTP_Z1_CMAC_KEY        : origin = 0x78018, length = 0x00008
   
   DCSM_ZSEL_Z1_P0             : origin = 0x78020, length = 0x000020

   /* Z2 OTP.  Z2 password locations / Flash and RAM partitioning */
   DCSM_OTP_Z2_LINK            : origin = 0x78200, length = 0x00006
   DCSM_OTP_Z2_RSVD            : origin = 0x78206, length = 0x00002
   DCSM_OTP_Z2_GPREG           : origin = 0x78208, length = 0x00008
   DCSM_OTP_Z2_PSWD_LOCK       : origin = 0x78210, length = 0x00002
   DCSM_OTP_Z2_CRC_LOCK        : origin = 0x78212, length = 0x00002
   DCSM_OTP_Z2_RSVD1           : origin = 0x78214, length = 0x0000C
   
   DCSM_ZSEL_Z2_P0             : origin = 0x78220, length = 0x000020
}


SECTIONS
{
    /* The following section definitions are for DCSM examples */
    ZONE1_RAM                   : > RAMLS2
    UNSECURE_RAM                : > RAMLS4
    CSMKEY_RAM                  : > RAMM0
	
	/* The following section definitions are generic for DCSM */
    dcsm_zsel_z1                : > DCSM_ZSEL_Z1_P0,            type = DSECT
    dcsm_zsel_z2                : > DCSM_ZSEL_Z2_P0,            type = DSECT
    dcsm_z1otp_link_pointer     : > DCSM_OTP_Z1_LINK,           type = DSECT
    dcsm_z2otp_link_pointer     : > DCSM_OTP_Z2_LINK,           type = DSECT
    dcsm_z1otp_jlm_enable       : > DCSM_OTP_Z1_JLM_ENABLE,     type = DSECT
    dcsm_rsvd_z2                : > DCSM_OTP_Z2_RSVD,           type = DSECT
    dcsm_z1otp_gpreg            : > DCSM_OTP_Z1_GPREG,          type = DSECT
    dcsm_z2otp_gpreg            : > DCSM_OTP_Z2_GPREG,          type = DSECT
    dcsm_z1otp_pswd_lock        : > DCSM_OTP_Z1_PSWD_LOCK,      type = DSECT
    dcsm_z2otp_pswd_lock        : > DCSM_OTP_Z2_PSWD_LOCK,      type = DSECT
    dcsm_z1otp_crc_lock         : > DCSM_OTP_Z1_CRC_LOCK,       type = DSECT
    dcsm_z2otp_crc_lock         : > DCSM_OTP_Z2_CRC_LOCK,       type = DSECT
    dcsm_z1otp_jtag_pswdh       : > DCSM_OTP_Z1_JTAG_PSWDH,     type = DSECT
    dcsm_rsvd1_z2               : > DCSM_OTP_Z2_RSVD1,          type = DSECT
    dcsm_z1otp_cmac_key         : > DCSM_OTP_Z1_CMAC_KEY,       type = DSECT
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
