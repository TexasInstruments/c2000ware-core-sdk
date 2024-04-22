//#############################################################################
//
// FILE:    fastrts_examples_lnk.cmd.cmd
//
// TITLE:   Linker Command File for the Fast RTS library examples that run 
//          on the F2838x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          F2838x
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################
// NOTES:
// 1. Memory blocks on F2838x are uniform (ie same physical memory) in both
//    PAGE 0 and PAGE 1. That is, the same memory region should not be defined 
//    for both PAGE 0 and PAGE 1. Doing so will result in corruption of program
//    and/or data.
//    
//    Contiguous SARAM memory blocks can be combined if required to create a 
//    larger memory block.
//
//#############################################################################
___TI_pprof_out_hndl=-1;
#if (!defined(RAM) && !defined(_FLASH))
#error Requires either RAM or _FLASH to be defined, do this \
from the project properties, C2000 Linker -> Advanced Options -> \
Command File Preprocessing -> --define. Dont forget to also define the \
variable in the predefined symbols under the compiler setting.
#endif //(!defined(RAM) || !defined(_FLASH))

MEMORY
{
PAGE 0 :
   // BEGIN is used for the "boot to SARAM" bootloader mode
#if defined(RAM)
   BEGIN           : origin = 0x000000, length = 0x000002
#elif defined(_FLASH)
   BEGIN           : origin = 0x080000, length = 0x000002
#endif 
   RAMM0           : origin = 0x000122, length = 0x0002DE
   RAMM1           : origin = 0x000400, length = 0x000400
   
   RAMLS0          : origin = 0x008000, length = 0x000800
   RAMLS1          : origin = 0x008800, length = 0x000800
   RAMLS2          : origin = 0x009000, length = 0x000800
   RAMLS3          : origin = 0x009800, length = 0x000800
   
   RESET           : origin = 0x3FFFC0, length = 0x000002
   
   FLASHA          : origin = 0x080002, length = 0x001FFE // on-chip Flash
   FLASHC          : origin = 0x084000, length = 0x002000 // on-chip Flash
   FLASHD          : origin = 0x086000, length = 0x002000 // on-chip Flash
   FLASHE          : origin = 0x088000, length = 0x008000 // on-chip Flash
   FLASHF          : origin = 0x090000, length = 0x008000 // on-chip Flash
   FLASHG          : origin = 0x098000, length = 0x008000 // on-chip Flash

PAGE 1 :
   FPU             : origin = 0x000F00, length = 0x000100 // FPU registers*/
   // Part of M0, BOOT rom will use this for stack 
   BOOT_RSVD       : origin = 0x000002, length = 0x000120   

   RAMLS456          : origin = 0x00A000, length = 0x001800
  // RAMLS5          : origin = 0x00A800, length = 0x000800
  // RAMLS6          : origin = 0x00B000, length = 0x000800
   RAMLS7          : origin = 0x00B800, length = 0x000800
   
   RAMGS0          : origin = 0x00C000, length = 0x002000
   RAMGS1          : origin = 0x00E000, length = 0x002000
   RAMGS23         : origin = 0x010000, length = 0x004000
   //RAMGS3          : origin = 0x012000, length = 0x002000

   FLASHB          : origin = 0x082000, length = 0x002000 // on-chip Flash
}
 
SECTIONS
{
   codestart       : > BEGIN,     PAGE = 0
#if defined(RAM)
#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
    .TI.ramfunc : {} > RAMM0,      PAGE = 0
   #else
    ramfuncs        : > RAMM0,     PAGE = 0
   #endif
#endif                                        
   ramfuncs        : > RAMM0,     PAGE = 0
   .text           :>> RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3,
                                  PAGE = 0
   .cinit          : > RAMM0,     PAGE = 0
#if defined(__TI_EABI__)
   .init_array	   : > RAMM0,     PAGE = 0
   .const          : > RAMGS0,    PAGE = 1
#else
   .pinit          : > RAMM0,     PAGE = 0
   .econst         : > RAMGS0,    PAGE = 1
#endif //__TI_EABI__
   .switch         : > RAMM0,     PAGE = 0

#if !defined(ROMTABLES)
#if defined(__TMS320C28XX_FPU64__)
   FPU64mathTables   : > RAMGS1,    PAGE = 1
#else
  FPUmathTables   : > RAMGS1,    PAGE = 1
#endif
#endif //ROMTABLES

#elif defined(_FLASH)
#ifdef __TI_COMPILER_VERSION__
   #if __TI_COMPILER_VERSION__ >= 15009000
     #if defined(__TI_EABI__)
        .TI.ramfunc     :  LOAD = FLASHC,
                           RUN = RAMLS1,
                           RUN_START(RamfuncsRunStart),
                           LOAD_START(RamfuncsLoadStart),
                           LOAD_SIZE(RamfuncsLoadSize),
                           PAGE = 0
                           {
                            --library=driverlib.lib<flash.obj> (.text)
                           }
     #else
        .TI.ramfunc     :  LOAD = FLASHC,
                           RUN = RAMLS1,
                           RUN_START(_RamfuncsRunStart),
                           LOAD_START(_RamfuncsLoadStart),
                           LOAD_SIZE(_RamfuncsLoadSize),
                           PAGE = 0
                           {
                            --library=driverlib.lib<flash.obj> (.text)
                           }
     #endif
    #else
   ramfuncs        :     LOAD = FLASHC,
                         RUN = RAMLS1,
                         RUN_START(_RamfuncsRunStart),
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_SIZE(_RamfuncsLoadSize),
                         PAGE = 0
                         {
                           --library=driverlib.lib<flash.obj> (.text)
                         }
   #endif
  #endif

   .text           : > FLASHA,    PAGE = 0
   .cinit          : > FLASHC,    PAGE = 0
#if defined(__TI_EABI__)
   .init_array	   : > FLASHC,    PAGE = 0
   .const          : > FLASHB,    PAGE = 1
#else
   .pinit          : > FLASHC,    PAGE = 0
   .econst         : > FLASHB,    PAGE = 1
 #endif //__TI_EABI__
   .switch         : > FLASHC,    PAGE = 0

#if !defined(ROMTABLES)
#if defined(__TMS320C28XX_FPU64__)
  #if defined(__TI_EABI__)
   FPU64mathTables  : LOAD = FLASHB,
                     RUN = RAMLS456,
                     RUN_START(FPU64mathTablesRunStart),
                     LOAD_START(FPU64mathTablesLoadStart),
                     LOAD_SIZE(FPU64mathTablesLoadSize),
                     PAGE = 1
  #else
   FPU64mathTables  : LOAD = FLASHB,
                     RUN = RAMLS456,
                     RUN_START(_FPU64mathTablesRunStart),
                     LOAD_START(_FPU64mathTablesLoadStart),
                     LOAD_SIZE(_FPU64mathTablesLoadSize),
                     PAGE = 1
  #endif
#else
  #if defined(__TI_EABI__)
   FPUmathTables    : LOAD = FLASHB,
                     RUN = RAMLS456,
                     RUN_START(FPUmathTablesRunStart),
                     LOAD_START(FPUmathTablesLoadStart),
                     LOAD_SIZE(FPUmathTablesLoadSize),
                     PAGE = 1
  #else
   FPUmathTables    : LOAD = FLASHB,
                     RUN = RAMLS456,
                     RUN_START(_FPUmathTablesRunStart),
                     LOAD_START(_FPUmathTablesLoadStart),
                     LOAD_SIZE(_FPUmathTablesLoadSize),
                     PAGE = 1
  #endif
 #endif
#endif //ROMTABLES

#endif //defined(RAM)
   FpuRegsFile      : > FPU,       PAGE = 1
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT // not used
   .stack           : > RAMLS456,    PAGE = 1
   .data			: > RAMLS456,    PAGE = 1
   .sysmem          : > RAMLS456,    PAGE = 1
#if defined(__TI_EABI__)
   .bss             : > RAMGS23,   PAGE = 1
   .bss:.cio        : > RAMLS456,    PAGE = 1
#else
   .cio             : > RAMLS456,    PAGE = 1
   .ebss            : > RAMGS23,   PAGE = 1
   .esysmem         : > RAMLS7,    PAGE = 1
#endif //__TI_EABI__

}
//
//===========================================================================
// End of file.
//===========================================================================
//
