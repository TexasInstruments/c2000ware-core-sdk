MEMORY
{
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
#if defined(RAM)
   BEGIN       : origin = 0x000000, length = 0x000002     /* Boot to M0 will go here                      */
#elif defined(_FLASH)
   BEGIN       : origin = 0x080000, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */
#endif
//   BEGIN            : origin = 0x000000, length = 0x000002
   BOOT_RSVD        : origin = 0x000002, length = 0x0001AE     /* Part of M0, BOOT rom will use this for stack */
   RAMM01            : origin = 0x0001B0, length = 0x000650
  // RAMM1            : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAMD0            : origin = 0x00C000, length = 0x000800
   RAMD1            : origin = 0x00C800, length = 0x000800
   RAMLS0           : origin = 0x008000, length = 0x000800
   RAMLS1           : origin = 0x008800, length = 0x000800
   RAMLS2           : origin = 0x009000, length = 0x000800
   RAMLS3           : origin = 0x009800, length = 0x000800
   RAMLS4           : origin = 0x00A000, length = 0x000800
   RAMLS5           : origin = 0x00A800, length = 0x000800
   RAMLS6           : origin = 0x00B000, length = 0x000800
   RAMLS7           : origin = 0x00B800, length = 0x000800
   RAMGS0           : origin = 0x00D000, length = 0x001000
   RAMGS1           : origin = 0x00E000, length = 0x001000
   RAMGS2           : origin = 0x00F000, length = 0x001000
   RAMGS3           : origin = 0x010000, length = 0x001000
   RAMGS4           : origin = 0x011000, length = 0x001000
   RAMGS5           : origin = 0x012000, length = 0x001000
   RAMGS6           : origin = 0x013000, length = 0x001000
   RAMGS7           : origin = 0x014000, length = 0x001000
   RAMGS89          : origin = 0x015000, length = 0x002000
   RAMGS1011        : origin = 0x017000, length = 0x002000
   RAMGS12          : origin = 0x019000, length = 0x001000
   RAMGS13          : origin = 0x01A000, length = 0x001000
   RAMGS14          : origin = 0x01B000, length = 0x001000
   RAMGS15          : origin = 0x01C000, length = 0x001000

   /* Flash sectors */
   FLASH0           : origin = 0x080002, length = 0x001FFE  /* on-chip Flash */
   FLASH1           : origin = 0x082000, length = 0x002000  /* on-chip Flash */
   FLASH2           : origin = 0x084000, length = 0x002000  /* on-chip Flash */
   FLASH3           : origin = 0x086000, length = 0x002000  /* on-chip Flash */
   FLASH4           : origin = 0x088000, length = 0x008000  /* on-chip Flash */
   FLASH5           : origin = 0x090000, length = 0x008000  /* on-chip Flash */
   FLASH6           : origin = 0x098000, length = 0x008000  /* on-chip Flash */
   FLASH7           : origin = 0x0A0000, length = 0x008000  /* on-chip Flash */
   FLASH8           : origin = 0x0A8000, length = 0x008000  /* on-chip Flash */
   FLASH9           : origin = 0x0B0000, length = 0x008000  /* on-chip Flash */
   FLASH10          : origin = 0x0B8000, length = 0x002000  /* on-chip Flash */
   FLASH11          : origin = 0x0BA000, length = 0x002000  /* on-chip Flash */
   FLASH12          : origin = 0x0BC000, length = 0x002000  /* on-chip Flash */
   FLASH13          : origin = 0x0BE000, length = 0x002000  /* on-chip Flash */
   CPU1TOCPU2RAM    : origin = 0x03A000, length = 0x000800
   CPU2TOCPU1RAM    : origin = 0x03B000, length = 0x000800

   CPUTOCMRAM       : origin = 0x039000, length = 0x000800
   CMTOCPURAM       : origin = 0x038000, length = 0x000800

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800
   RESET            : origin = 0x3FFFC0, length = 0x000002
}


SECTIONS
{
   codestart        : > BEGIN, ALIGN(4)
   .reset           : > RESET, TYPE = DSECT /* not used, */

#if defined(RAM)
   .text            : >> RAMD0 | RAMD1 | RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMGS15
   .cinit           : > RAMM01
   .switch          : > RAMLS0
   .stack           : > RAMLS1
   .data            : > RAMLS5
   .TI.ramfunc 		: > RAMM01
#if defined(__TI_EABI__)
   .bss             : >> RAMLS5 | RAMLS6 | RAMLS7
   .bss:output      : > RAMLS3
   .init_array      : > RAMLS0
   .const           : >> RAMLS5 | RAMLS6
   .sysmem          : > RAMLS4
#else
   .pinit           : > RAMLS0
   .ebss            : >> RAMLS5 | RAMLS6 | RAMLS7
   .cio				: > RAMLS3
   .econst          : > RAMLS5 | RAMLS6
   .esysmem         : > RAMLS4
#endif //EABI

#elif defined(_FLASH)
   .cinit           : > FLASH0
   .text            : >> FLASH1 | FLASH2
   .switch          : > FLASH3
   .stack           : > RAMM01
   .data            : > RAMGS1
#if defined(__TI_EABI__)
   .bss             : > RAMLS0
   .bss:output      : > RAMLS1
   .init_array      : > FLASH0
   .const           : > FLASH4
   .sysmem          : > RAMLS2
#else
   .pinit           : > FLASH0
   .ebss            : > RAMLS0
   .cio				: >	RAMLS1
   .econst          : > FLASH4
   .esysmem         : > RAMLS2
#endif //EABI

#if defined(__TI_EABI__)
   .TI.ramfunc : {} LOAD = FLASH3,
                    RUN = RAMGS0,
                    LOAD_START(RamfuncsLoadStart),
                    LOAD_SIZE(RamfuncsLoadSize),
                    LOAD_END(RamfuncsLoadEnd),
                    RUN_START(RamfuncsRunStart),
                    RUN_SIZE(RamfuncsRunSize),
                    RUN_END(RamfuncsRunEnd),
                    ALIGN(4)

#else
   .TI.ramfunc : {} LOAD = FLASH3,
                    RUN = RAMLS0,
                    LOAD_START(_RamfuncsLoadStart),
                    LOAD_SIZE(_RamfuncsLoadSize),
                    LOAD_END(_RamfuncsLoadEnd),
                    RUN_START(_RamfuncsRunStart),
                    RUN_SIZE(_RamfuncsRunSize),
                    RUN_END(_RamfuncsRunEnd),
                    ALIGN(4)
#endif//EABI
#endif//FLASH

   ramgs0 : > RAMGS0, type=NOINIT
  ramgs1 : > RAMGS1, type=NOINIT

   firfilt 			: >> RAMGS0 | RAMGS1
   firldb 			: > RAMGS0, ALIGN(0x100)
#if defined(RAM)
   coefffilt		: > RAMGS1, ALIGN(0x100)
#elif defined(_FLASH)
   coefffilt  		:> FLASH2, ALIGN(0x100)
#endif

   revcoeff		    : > RAMGS1
   sigIn			: >> RAMGS0	| RAMGS1
   sigOut			: >> RAMGS0 | RAMGS1

   MSGRAM_CPU1_TO_CPU2 > CPU1TOCPU2RAM, type=NOINIT
   MSGRAM_CPU2_TO_CPU1 > CPU2TOCPU1RAM, type=NOINIT
   MSGRAM_CPU_TO_CM    > CPUTOCMRAM, type=NOINIT
   MSGRAM_CM_TO_CPU    > CMTOCPURAM, type=NOINIT
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
