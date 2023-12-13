MEMORY
{
   BEGIN            : origin = 0x00000000, length = 0x00000002
   BOOT_RSVD        : origin = 0x00000002, length = 0x00000126

   RAMM01           : origin = 0x00000128, length = 0x000006D0
   //RAMM01            : origin = 0x00000400, length = 0x000003F8
   // RAMM01_RSVD       : origin = 0x000007F8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMLS			: origin = 0x00008000, length = 0x00003FF8
   //RAMLS           : origin = 0x00008000, length = 0x00002000
   //RAMLS1           : origin = 0x0000A000, length = 0x00001FF8
   // RAMLS1_RSVD      : origin = 0x0000BFF8, length = 0x00000008 /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RESET            : origin = 0x003FFFC0, length = 0x00000002
}


SECTIONS
{
   codestart        : > BEGIN
   .text            : >> RAMLS
   .cinit           : > RAMM01
   .switch          : > RAMM01
   .reset           : > RESET, TYPE = DSECT /* not used, */

   .stack           : > RAMM01
#if defined(__TI_EABI__)
   .bss             : > RAMLS
   .bss:output      : > RAMLS
   .init_array      : > RAMM01
   .const           : > RAMLS
   .data            : > RAMLS
   .sysmem          : > RAMLS
   .TI.crctab	    : > RAMLS
   /* Test specific sections */
   testInput        : > RAMLS,
                      crc_table(linkerCrcTable, algorithm = CRC24_FLEXRAY)
#else
   .pinit           : > RAMM01
   .ebss            : >> RAMLS
   .econst          : > RAMLS
   .esysmem         : > RAMLS
#endif



    .TI.ramfunc : {} > RAMM01

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
