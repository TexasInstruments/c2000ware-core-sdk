
SECTIONS
{
#if defined (_FLASH)

    #if defined(__TI_EABI__)
    .delayFunc :> FLASH_BANK0_SEC1
                    LOAD_START(delayFuncStart),
                    LOAD_END(delayFuncEnd)
    #else
    .delayFunc :> FLASH_BANK0_SEC1
                    LOAD_START(_delayFuncStart),
                    LOAD_END(_delayFuncEnd)
    #endif

#else

    #if defined(__TI_EABI__)
    .delayFunc :> RAMLS4
                    LOAD_START(delayFuncStart),
                    LOAD_END(delayFuncEnd)
    #else
    .delayFunc :> RAMLS4
                    LOAD_START(_delayFuncStart),
                    LOAD_END(_delayFuncEnd)
    #endif

#endif
}
