/* F28069_stdmem.cmd - standard memory linker command file for F28069
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 *
*/

_Cla1Prog_Start = _Cla1funcsRunStart;

CLA_SCRATCHPAD_SIZE = 0x100;
--undef_sym=__cla_scratchpad_end
--undef_sym=__cla_scratchpad_start

MEMORY
{

PAGE 0:    /* Program Memory */

   BOOTM0      : origin = 0x000000, length = 0x000002	  /* boot vector */
   RAML3       : origin = 0x009000, length = 0x001000     /* CLA program RAM */
   RAML4L      : origin = 0x00A000, length = 0x001C00     /* on-chip RAM block L4 */

   OTP         : origin = 0x3D7800, length = 0x000400     /* on-chip OTP */
   FLASHH      : origin = 0x3D8000, length = 0x004000     /* on-chip FLASH */
   FLASHG      : origin = 0x3DC000, length = 0x004000     /* on-chip FLASH */
   FLASHF      : origin = 0x3E0000, length = 0x004000     /* on-chip FLASH */
   FLASHE      : origin = 0x3E4000, length = 0x004000     /* on-chip FLASH */
   FLASHD      : origin = 0x3E8000, length = 0x004000     /* on-chip FLASH */
   FLASHC      : origin = 0x3EC000, length = 0x004000     /* on-chip FLASH */
   FLASHA      : origin = 0x3F4000, length = 0x003F80     /* on-chip FLASH */
   CSM_RSVD    : origin = 0x3F7F80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
   BEGIN       : origin = 0x3F7FF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */
   CSM_PWL_P0  : origin = 0x3F7FF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA */

   FPUTABLES   : origin = 0x3FD860, length = 0x0006A0	  /* FPU Tables in Boot ROM */
   IQTABLES    : origin = 0x3FDF00, length = 0x000B50     /* IQ Math Tables in Boot ROM */
   IQTABLES2   : origin = 0x3FEA50, length = 0x00008C     /* IQ Math Tables in Boot ROM */
   IQTABLES3   : origin = 0x3FEADC, length = 0x0000AA	  /* IQ Math Tables in Boot ROM */

   ROM         : origin = 0x3FF3B0, length = 0x000C10     /* Boot ROM */
   RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */
   VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM  */


PAGE 1 :   /* Data Memory */

   BOOT_RSVD   : origin = 0x000002, length = 0x00004E     /* Part of M0, BOOT rom will use this for stack */
   RAMM0       : origin = 0x000050, length = 0x0003B0     /* on-chip RAM block M0 */
   RAMM1       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   CLARAM2     : origin = 0x008000, length = 0x000800	  /* on-chip RAM block L0 */
   CLARAM0     : origin = 0x008800, length = 0x000400	  /* on-chip RAM block L1 */
   CLARAM1     : origin = 0x008C00, length = 0x000400	  /* on-chip RAM block L1 */
   RAML4H      : origin = 0x00B800, length = 0x000400     /* on-chip RAM block L4 */
   RAML5       : origin = 0x00C000, length = 0x002000     /* on-chip RAM block L5 */
   RAML6       : origin = 0x00E000, length = 0x002000     /* on-chip RAM block L6 */
   RAML7       : origin = 0x010000, length = 0x002000     /* on-chip RAM block L7 */
   RAML8       : origin = 0x012000, length = 0x002000     /* on-chip RAM block L8 */
   USB_RAM     : origin = 0x040000, length = 0x000800     /* USB RAM		  */
   FLASHB      : origin = 0x3F0000, length = 0x004000     /* on-chip FLASH */

   CLA1_MSGRAMLOW       : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH      : origin = 0x001500, length = 0x000080

}

/* end of file */
