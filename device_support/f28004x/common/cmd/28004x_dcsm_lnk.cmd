/* this linker command file is to be included if user wants to use the DCSM
 * feature on the device DCSM  means Dual Zone Code Security Module. This
 * linker command file works as an addendum ot the already existing Flash/RAM
 * linker command file that the project has.
 * The sections in the *_ZoneSelectBlock.asm source file is linked as per the
 * commands given in the file NOTE - please note fill=0xFFFF, this helps if
 * users include this file in the project by mistake and doesn't provide the
 * needed proper *_ZoneSelectBlock.asm sources.
 * Please refer to the Blinky DCSM example for proper usage of this.
 *
 * Once users are confident t`hat they want to program the passwords in OTP, the
 * DSECT section type can be removed.
 *
*/

MEMORY
{
PAGE 0 :  /* Program Memory */

   /* BANK0 */
   /* B0 Z1 OTP.  LinkPointers */
   B0_DCSM_OTP_Z1_LINKPOINTER   : origin = 0x78000, length = 0x00000C
   /* B0 Z1 OTP.  GPREG1/GPREG2 */
   B0_DCSM_OTP_Z1_GPREG         : origin = 0x7800C, length = 0x000004
   /* B0 Z1 OTP.  PSWDLOCK/RESERVED */
   B0_DCSM_OTP_Z1_PSWDLOCK	    : origin = 0x78010, length = 0x000004
   /* B0 Z1 OTP.  CRCLOCK/RESERVED */
   B0_DCSM_OTP_Z1_CRCLOCK	    : origin = 0x78014, length = 0x000004
   /* B0 Z1 OTP.  GPREG3/BOOTCTRL */
   B0_DCSM_OTP_Z1_BOOTCTRL	    : origin = 0x7801C, length = 0x000004

   /* DCSM Z1 Zone Select Contents (!!Movable!!) */
   /* B0 Z1 OTP.  Z1 password locations / Flash and RAM partitioning */
   B0_DCSM_ZSEL_Z1_P0	        : origin = 0x78020, length = 0x000010

   /* B0 Z2 OTP.  LinkPointers */
   B0_DCSM_OTP_Z2_LINKPOINTER	: origin = 0x78200, length = 0x00000C
   /* B0 Z2 OTP.  GPREG1/GPREG2 */
   B0_DCSM_OTP_Z2_GPREG	        : origin = 0x7820C, length = 0x000004
   /* B0 Z2 OTP.  PSWDLOCK/RESERVED */
   B0_DCSM_OTP_Z2_PSWDLOCK	    : origin = 0x78210, length = 0x000004
   /* B0 Z2 OTP.  CRCLOCK/RESERVED */
   B0_DCSM_OTP_Z2_CRCLOCK	    : origin = 0x78214, length = 0x000004
   /* B0 Z2 OTP.  GPREG3/BOOTCTRL */
   B0_DCSM_OTP_Z2_BOOTCTRL	    : origin = 0x7821C, length = 0x000004

   /* DCSM Z1 Zone Select Contents (!!Movable!!) */
   /* B0 Z2 OTP.  Z2 password locations / Flash and RAM partitioning  */
   B0_DCSM_ZSEL_Z2_P0	        : origin = 0x78220, length = 0x000010


   /* BANK1 */
   /* B1 Z1 OTP.  LinkPointers */
   B1_DCSM_OTP_Z1_LINKPOINTER	: origin = 0x78400, length = 0x00000C

   /* DCSM B1 Z1 Zone Select Contents (!!Movable!!) */
   /* B1 Z1 OTP.  Flash partitioning */
   B1_DCSM_ZSEL_Z1_P0	        : origin = 0x78420, length = 0x000010

   /* B1 Z2 OTP.  LinkPointers */
   B1_DCSM_OTP_Z2_LINKPOINTER	: origin = 0x78600, length = 0x00000C

   /* DCSM B1 Z1 Zone Select Contents (!!Movable!!) */
   /* B1 Z2 OTP.  Flash partitioning  */
   B1_DCSM_ZSEL_Z2_P0	        : origin = 0x78620, length = 0x000010
}

SECTIONS
{
   b0_dcsm_otp_z1_linkpointer 	: > B0_DCSM_OTP_Z1_LINKPOINTER		PAGE = 0, type = DSECT
   b0_dcsm_otp_z1_gpreg			: > B0_DCSM_OTP_Z1_GPREG			PAGE = 0, type = DSECT
   b0_dcsm_otp_z1_pswdlock		: > B0_DCSM_OTP_Z1_PSWDLOCK			PAGE = 0, type = DSECT
   b0_dcsm_otp_z1_crclock		: > B0_DCSM_OTP_Z1_CRCLOCK			PAGE = 0, type = DSECT
   b0_dcsm_otp_z1_bootctrl		: > B0_DCSM_OTP_Z1_BOOTCTRL			PAGE = 0, type = DSECT
   b0_dcsm_zsel_z1				: > B0_DCSM_ZSEL_Z1_P0				PAGE = 0, type = DSECT

   b0_dcsm_otp_z2_linkpointer	: > B0_DCSM_OTP_Z2_LINKPOINTER		PAGE = 0, type = DSECT
   b0_dcsm_otp_z2_gpreg			: > B0_DCSM_OTP_Z2_GPREG			PAGE = 0, type = DSECT
   b0_dcsm_otp_z2_pswdlock		: > B0_DCSM_OTP_Z2_PSWDLOCK			PAGE = 0, type = DSECT
   b0_dcsm_otp_z2_crclock		: > B0_DCSM_OTP_Z2_CRCLOCK			PAGE = 0, type = DSECT
   b0_dcsm_otp_z2_bootctrl		: > B0_DCSM_OTP_Z2_BOOTCTRL			PAGE = 0, type = DSECT
   b0_dcsm_zsel_z2				: > B0_DCSM_ZSEL_Z2_P0				PAGE = 0, type = DSECT

   b1_dcsm_otp_z1_linkpointer 	: > B1_DCSM_OTP_Z1_LINKPOINTER		PAGE = 0, type = DSECT
   b1_dcsm_zsel_z1				: > B1_DCSM_ZSEL_Z1_P0				PAGE = 0, type = DSECT

   b1_dcsm_otp_z2_linkpointer	: > B1_DCSM_OTP_Z2_LINKPOINTER		PAGE = 0, type = DSECT
   b1_dcsm_zsel_z2				: > B1_DCSM_ZSEL_Z2_P0				PAGE = 0, type = DSECT
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
