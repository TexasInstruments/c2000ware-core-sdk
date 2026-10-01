MEMORY
{
   BEGIN            : origin = 0x080000, length = 0x000002

   BOOT_RSVD        : origin = 0x000002, length = 0x000121     
   RAMM0            : origin = 0x000123, length = 0x0002DD
   RAMM1            : origin = 0x000400, length = 0x0003F8
// RAMM1_RSVD       : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMD0            : origin = 0x00B000, length = 0x000800
   RAMD1            : origin = 0x00B800, length = 0x000800

   RAMLS01          : origin = 0x008000, length = 0x001000
   RAMLS2345        : origin = 0x009000, length = 0x002000

   RAMGS04          : origin = 0x00C000, length = 0x005000
   RAMGS57          : origin = 0x011000, length = 0x003000
   RAMGS8           : origin = 0x014000, length = 0x001000
   RAMGS9           : origin = 0x015000, length = 0x001000
   RAMGS10          : origin = 0x016000, length = 0x001000
   RAMGS11          : origin = 0x017000, length = 0x001000     
   RAMGS12          : origin = 0x018000, length = 0x001000     
   RAMGS13          : origin = 0x019000, length = 0x001000     
   RAMGS14          : origin = 0x01A000, length = 0x001000     
   RAMGS15          : origin = 0x01B000, length = 0x000FF8     
// RAMGS15_RSVD     : origin = 0x01BFF8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   CPU2TOCPU1RAM    : origin = 0x03F800, length = 0x000400
   CPU1TOCPU2RAM    : origin = 0x03FC00, length = 0x000400

   CLATOCPURAM      : origin = 0x001480, length = 0x000080
   CPUTOCLARAM      : origin = 0x001500, length = 0x000080
   CLATODMARAM      : origin = 0x001680, length = 0x000080
   DMATOCLARAM      : origin = 0x001700, length = 0x000080

   RESET            : origin = 0x3FFFC0, length = 0x000002

   /* Flash sectors */
   FLASHA           : origin = 0x080002, length = 0x001FFE     
   FLASHB           : origin = 0x082000, length = 0x002000     
   FLASHC           : origin = 0x084000, length = 0x002000     
   FLASHD           : origin = 0x086000, length = 0x002000     
   FLASHE           : origin = 0x088000, length = 0x008000     
   FLASHF           : origin = 0x090000, length = 0x008000     
   FLASHG           : origin = 0x098000, length = 0x008000     
   FLASHH           : origin = 0x0A0000, length = 0x008000     
   FLASHI           : origin = 0x0A8000, length = 0x008000     
   FLASHJ           : origin = 0x0B0000, length = 0x008000     
   FLASHK           : origin = 0x0B8000, length = 0x002000     
   FLASHL           : origin = 0x0BA000, length = 0x002000     
   FLASHM           : origin = 0x0BC000, length = 0x002000     
   FLASHN           : origin = 0x0BE000, length = 0x001FF0     
// FLASHN_RSVD      : origin = 0x0BFFF0, length = 0x000010     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
}


SECTIONS
{
   codestart        : > BEGIN
   .cinit           : > FLASHB, ALIGN(8)
   .switch          : > FLASHB, ALIGN(8)
   .text            : >> FLASHC | FLASHD | FLASHE | FLASHF, ALIGN(8)
   .reset           : > RESET, TYPE = DSECT /* not used */
   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .init_array      : > FLASHB, ALIGN(8)
   .const           : > FLASHB, ALIGN(8)
   .bss             : > RAMLS2345
   .bss:output      : > RAMLS2345
   .data            : > RAMLS2345
   .sysmem          : > RAMLS2345
#else
   .pinit           : > FLASHB, ALIGN(8)
   .econst          : > FLASHB, ALIGN(8)
   .ebss            : > RAMLS2345
   .esysmem         : > RAMLS2345
#endif

   .rodata.tvm      : >> FLASHG | FLASHH | FLASHI | FLASHJ, ALIGN(8)
   .bss.noinit.tvm  : > RAMGS04

   FFT_buffer_1     : > RAMGS57
   FPUfftTables     : > RAMGS57

   #if defined(__TI_EABI__)
   GROUP{
       .TI.ramfunc :
       {-l c28x_fpu_dsp_library_eabi.lib}
       {-l rts2800_fpu32_fast_supplement_eabi.lib}
   }
            LOAD = FLASHC,
            RUN = RAMLS01,
            LOAD_START(RamfuncsLoadStart),
            LOAD_SIZE(RamfuncsLoadSize),
            LOAD_END(RamfuncsLoadEnd),
            RUN_START(RamfuncsRunStart),
            RUN_SIZE(RamfuncsRunSize),
            RUN_END(RamfuncsRunEnd),
            ALIGN(8)
   #else
       .TI.ramfunc : {} LOAD = FLASHC,
                        RUN = RAMLS01,
                        LOAD_START(_RamfuncsLoadStart),
                        LOAD_SIZE(_RamfuncsLoadSize),
                        LOAD_END(_RamfuncsLoadEnd),
                        RUN_START(_RamfuncsRunStart),
                        RUN_SIZE(_RamfuncsRunSize),
                        RUN_END(_RamfuncsRunEnd),
                        ALIGN(8)
   #endif

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
