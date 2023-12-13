/* Example_F28069_GSM.c
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
*/

// header files
#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "F2806x_GlobalPrototypes.h"
#include "DCLF32.h"
#include "DCL_fdlog.h"

// function prototypes
float32_t GSM_target_fcn(float32_t x);

// global  variables
uint16_t i = 0;
float32_t dx, xk, yk;

// controller
DCL_GSM F = GSM_DEFAULTS;
DCL_CSS Fcss = DCL_CSS_DEFAULTS;
DCL_GSM_SPS Fsps = GSM_SPS_DEFAULTS;

// result buffer
#pragma DATA_SECTION(s_array, "SDataLogSection")
float32_t s_array[FDLOG_DEFAULT_SIZE];
FDLOG sBuf = FDLOG_DEFAULTS;


/* main */
main()
{
    /* initialise system */
    InitSysCtrl();                          // [F2806x_SysCtrl.c]
    DINT;                                   // disable interrupts
 
    /* result buffer initialization */
    DCL_initLog(&sBuf, s_array, FDLOG_DEFAULT_SIZE);
    DCL_clearLog(&sBuf);
	
	/* initialize GSM support structures */
	F.sps = &Fsps;
	F.css = &Fcss;

	/* load GSM offset coefficients */
    xk = 0;
    for (i=1; i<=GSM_N; i++)
    {
        xk += F.h;
        F.sps->c[i] = GSM_target_fcn(xk);
    }

    /* load GSM gain table */
    DCL_loadGSMgains(&F);

	/* load active GSM */
	DCL_REQUEST_UPDATE(&F);
	DCL_updateGSM(&F);
		
	/* load input-output curve */
	dx = 2.2f / FDLOG_DEFAULT_SIZE;
	for (xk=-1.1f; xk<1.1f; xk+=dx)
	{
		yk = DCL_runGSM_C1(&F, xk);
		DCL_writeLog(&sBuf, yk);
	}
	
    /* infinite loop */
    while(1)
    {
        asm(" NOP");
    } // while

} // main


/* target function for gain scheduler profile */
float32_t GSM_target_fcn(float32_t x)
{
	return(x*x);
}


/* end of file */
