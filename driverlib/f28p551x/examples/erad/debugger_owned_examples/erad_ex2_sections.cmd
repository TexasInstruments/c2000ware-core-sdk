SECTIONS
{
#if defined (_FLASH)
    .performFIR  :> FLASH_BANK0
                    LOAD_START(performFIRFuncStart),
                    LOAD_END(performFIRFuncEnd)
    .sortMax     :> FLASH_BANK0
                    LOAD_START(sortMaxFuncStart),
                    LOAD_END(sortMaxFuncEnd)
#else
    .performFIR  :> RAMLS4
                    LOAD_START(performFIRFuncStart),
                    LOAD_END(performFIRFuncEnd)
    .sortMax     :> RAMLS4
                    LOAD_START(sortMaxFuncStart),
                    LOAD_END(sortMaxFuncEnd)
#endif
}
