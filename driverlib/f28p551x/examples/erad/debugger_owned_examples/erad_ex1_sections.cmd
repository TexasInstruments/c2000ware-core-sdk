SECTIONS
{
#if defined (_FLASH)
    .funcToProfile :> FLASH_BANK0
                    LOAD_START(funcStart),
                    LOAD_END(funcEnd)
#else
    .funcToProfile :> RAMLS4
                    LOAD_START(funcStart),
                    LOAD_END(funcEnd)
#endif
}
