MEMORY
{

   /* BEGIN is used for the "boot to SARAM" bootloader mode   */
   BEGIN            : origin = 0x000000, length = 0x000002
   BOOT_RSVD        : origin = 0x000002, length = 0x0001AF     /* Part of M0, BOOT rom will use this for stack */
   RAMM0            : origin = 0x0001B1, length = 0x00024F
   RAMM1            : origin = 0x000400, length = 0x0003F8     /* on-chip RAM block M1 */
//   RAMM1_RSVD       : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
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
   //RAMGS1_code      : origin = 0x00E000, length = 0x000B00
   //RAMGS1_data	  :origin = 0xEB000,   length = 0x400

   RAMGS2           : origin = 0x00F000, length = 0x001000
   RAMGS3           : origin = 0x010000, length = 0x001000
   RAMGS4           : origin = 0x011000, length = 0x001000
   RAMGS5           : origin = 0x012000, length = 0x001000
   RAMGS6           : origin = 0x013000, length = 0x001000
   RAMGS7           : origin = 0x014000, length = 0x001000
   RAMGS8           : origin = 0x015000, length = 0x001000
   RAMGS9           : origin = 0x016000, length = 0x001000
   RAMGS10          : origin = 0x017000, length = 0x001000
   RAMGS11          : origin = 0x018000, length = 0x001000
   RAMGS12          : origin = 0x019000, length = 0x001000
   RAMGS13          : origin = 0x01A000, length = 0x001000
   RAMGS14          : origin = 0x01B000, length = 0x001000
   RAMGS15          : origin = 0x01C000, length = 0x000FF8
//   RAMGS15_RSVD     : origin = 0x01CFF8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   CPU1TOCPU2RAM    : origin = 0x03A000, length = 0x000800
   CPU2TOCPU1RAM    : origin = 0x03B000, length = 0x000800

   CPUTOCMRAM_0     : origin = 0x039000, length = 0x000400
   CPUTOCMRAM_1     : origin = 0x039400, length = 0x000400
   CMTOCPURAM       : origin = 0x038000, length = 0x000800

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800
   RESET            : origin = 0x3FFFC0, length = 0x000002
}


SECTIONS
{
   codestart        : > BEGIN
   .text            : >>RAMGS1 | RAMGS2 | RAMGS3 | RAMGS4
   .cinit           : > RAMM0
   .switch          : > RAMM0
   .reset           : > RESET,    TYPE = DSECT /* not used, */

   .stack           : > RAMM1
#if defined(__TI_EABI__)
   .bss            : > RAMGS5
   .data           : > RAMGS5
   .const          : > RAMGS5
   .init_arry      : > RAMM0
   .sysmem         : > RAMGS5
#else
   .pinit           : > RAMM0
   .ebss            : > RAMGS5
   .econst          : > RAMGS5
   .esysmem         : > RAMGS5
#endif
   Filter_RegsFile  : > RAMGS5

#ifdef __TI_COMPILER_VERSION__
    #if __TI_COMPILER_VERSION__ >= 15009000
       .TI.ramfunc      : > RAMGS5
    #else
       ramfuncs         : > RAMGS5
    #endif
#endif

   MSGRAM_CPU1_TO_CPU2 > CPU1TOCPU2RAM, type=NOINIT
   MSGRAM_CPU2_TO_CPU1 > CPU2TOCPU1RAM, type=NOINIT
   MSGRAM_CPU_TO_CM   > CPUTOCMRAM_0, type=NOINIT
   MSGRAM_CPU_TO_CM_COPY_TO_S0_RAM > CPUTOCMRAM_1, type=NOINIT
   MSGRAM_CM_TO_CPU   > CMTOCPURAM, type=NOINIT




    /* The following section definition are for SDFM examples */
   Filter1_RegsFile : > RAMGS10,	 fill=0x1111
   Filter2_RegsFile : > RAMGS11,	 fill=0x2222
   Filter3_RegsFile : > RAMGS12,	 fill=0x3333
   Filter4_RegsFile : > RAMGS13,     fill=0x4444
   Difference_RegsFile : >RAMGS14, 	 fill=0x3333

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
