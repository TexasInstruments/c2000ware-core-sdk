
SECTIONS
{
#if defined (_FLASH)

    .try_sect	: > FLASH0

#else

    .try_sect : > RAMLS4

#endif
}
