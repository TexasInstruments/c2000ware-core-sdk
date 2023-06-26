

MEMORY
{
    PAGE 0 :   /* Program Memory */
       
    
    PAGE 1 :   /* Data Memory */

}

/* 
    Allocate sections to memory blocks.   
*/


SECTIONS
{

   /* Allocate program areas: */
   
   isrfunc            : LOAD = RAMD0 |  RAMLS0 | RAMLS1 | RAMLS2 | RAMLS3 | RAMLS4,
                         RUN = RAMGS14,
                         LOAD_START(_isrfuncLoadStart),
                         LOAD_END(_isrfuncLoadEnd),
                         RUN_START(_isrfuncRunStart),
						 LOAD_SIZE(_isrfuncLoadSize),
						 PAGE = 0
						 
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/

