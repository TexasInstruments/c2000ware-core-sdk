MEMORY
{
   BEGIN            : origin = 0x080000, length = 0x000002

   BOOT_RSVD        : origin = 0x000002, length = 0x0001AF    
   RAMM0            : origin = 0x0001B1, length = 0x00024F     
   RAMM1            : origin = 0x000400, length = 0x0003F8
// RAMM1_RSVD       : origin = 0x0007F8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   RAMLS01          : origin = 0x008000, length = 0x001000     
   RAMBSS           : origin = 0x009000, length = 0x004000     

   RAMDATA          : origin = 0x017000, length = 0x005000     

   RAMGS04          : origin = 0x00D000, length = 0x008000
   RAMGS8           : origin = 0x015000, length = 0x002000
   RAMGS15          : origin = 0x01C000, length = 0x000FF8
// RAMGS15_RSVD     : origin = 0x01CFF8, length = 0x000008     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */

   CPU1TOCPU2RAM    : origin = 0x03A000, length = 0x000800
   CPU2TOCPU1RAM    : origin = 0x03B000, length = 0x000800
   CPUTOCMRAM       : origin = 0x039000, length = 0x000800
   CMTOCPURAM       : origin = 0x038000, length = 0x000800

   CANA_MSG_RAM     : origin = 0x049000, length = 0x000800
   CANB_MSG_RAM     : origin = 0x04B000, length = 0x000800

   RESET            : origin = 0x3FFFC0, length = 0x000002


   FLASH_INIT       : origin = 0x080002, length = 0x003FFE    

   FLASH2           : origin = 0x084000, length = 0x002000     
   FLASH3           : origin = 0x086000, length = 0x002000     
   FLASH4           : origin = 0x088000, length = 0x008000   
   FLASH5           : origin = 0x090000, length = 0x008000     

   FLASH67          : origin = 0x098000, length = 0x010000
   FLASH8           : origin = 0x0A8000, length = 0x008000
   FLASH9           : origin = 0x0B0000, length = 0x008000     
   FLASH10          : origin = 0x0B8000, length = 0x002000    
   FLASH11          : origin = 0x0BA000, length = 0x002000   
   FLASH12          : origin = 0x0BC000, length = 0x002000     
   FLASH13          : origin = 0x0BE000, length = 0x001FF0    
// FLASH13_RSVD     : origin = 0x0BFFF0, length = 0x000010     /* Reserve and do not use for code as per the errata advisory "Memory: Prefetching Beyond Valid Memory" */
}


SECTIONS
{
   codestart        : > BEGIN
   .cinit           : > FLASH_INIT, ALIGN(8)
   .switch          : > FLASH10, ALIGN(8)

   .text            : >> FLASH2 | FLASH3 | FLASH4 | FLASH5, ALIGN(8)
   .reset           : > RESET, TYPE = DSECT /* not used */
   .stack           : > RAMM1

#if defined(__TI_EABI__)
   .init_array      : > FLASH10, ALIGN(8)
   .const           : >> FLASH10 | FLASH11 | FLASH12, ALIGN(8)
   .bss             : > RAMBSS
   .bss:output      : > RAMBSS
   .data            : > RAMDATA
   .sysmem          : > RAMGS15
#else
   .pinit           : > FLASH10, ALIGN(8)
   .econst          : >> FLASH10 | FLASH11, ALIGN(8)
   .ebss            : > RAMBSS
   .esysmem         : > RAMGS15
#endif

   .rodata.tvm      : > FLASH67, ALIGN(8)
   .bss.noinit.tvm  : > RAMGS04

   FFT_buffer_1     : > RAMGS8
   FPUfftTables     : > RAMGS8

   #if defined(__TI_EABI__)
   GROUP{
       .TI.ramfunc :
       {-l c28x_fpu_dsp_library_eabi.lib}
       {-l rts2800_fpu32_fast_supplement_eabi.lib}
   }
            LOAD = FLASH2,
            RUN = RAMLS01,
            LOAD_START(RamfuncsLoadStart),
            LOAD_SIZE(RamfuncsLoadSize),
            LOAD_END(RamfuncsLoadEnd),
            RUN_START(RamfuncsRunStart),
            RUN_SIZE(RamfuncsRunSize),
            RUN_END(RamfuncsRunEnd),
            ALIGN(8)
   #else
       .TI.ramfunc : {} LOAD = FLASH2,
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
