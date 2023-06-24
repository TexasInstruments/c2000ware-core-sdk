
SECTIONS
{
#if defined (_FLASH)

    .try_sect	: > FLASH_BANK0_SEC1

#else

    .try_sect : > RAMLS4

#endif
}
