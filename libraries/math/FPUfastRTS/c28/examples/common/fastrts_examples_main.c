//#############################################################################
//
//! \file   fastrts_examples_main.c
//!
//! \brief  Fast RTS Examples - The main()
//! \author Ritvik Sadana
//! \date   Feb 2, 2018
//
//  Group:          C2000
//
//#############################################################################
//
//
// $Copyright: Copyright (C) 2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################


//*****************************************************************************
// the includes
//*****************************************************************************
#include "fastrts_examples_setup.h"
#include <assert.h>

//*****************************************************************************
// the globals
//*****************************************************************************

//*****************************************************************************
// the function definitions
//*****************************************************************************
int main(void)
{
#if defined(_FLASH)
    //
    // Setup the FLASH Banks
    //
    FastRTS_Example_setupFlash();
#endif //defined(_FLASH)
    
    //
    // Setup system clocking
    //
    FastRTS_Example_setupSysCtrl();
    
    //
    // Run the test
    //
    FastRTS_runTest();
    
    // 
    //
    // End Test - loop forever
    //
    done();
    
    //
    // Code does not get to this point
    //
    return(1);
}

//*****************************************************************************
// FID_Example_calcError
//*****************************************************************************
int16_t FID_Example_calcError(const void *p_out,
                              const void *p_gold,
                              const void *p_err,
                              const void *p_tol,
                              const FASTRTS_error_t et)
{
    int16_t status  = -1;
    
    if(et == ERRORTYPE_UI16)
    {
        *((uint16_t *)p_err)  = abs((*((uint16_t *)p_out) - *((uint16_t *)p_gold)));
        if(*((uint16_t *)p_err) <= *((uint16_t *)p_tol))
        {
            status = 1;
        }
    }
    else if(et == ERRORTYPE_I16)
    {
        *((int16_t *)p_err)  = abs((*((int16_t *)p_out) - *((int16_t *)p_gold)));
        if(*((int16_t *)p_err) <= *((int16_t *)p_tol))
        {
            status = 1;
        }
    }
    else if(et == ERRORTYPE_UI32)
    {
        *((uint32_t *)p_err)  = abs((*((uint32_t *)p_out) - *((uint32_t *)p_gold)));
        if(*((uint32_t *)p_err) <= *((uint32_t *)p_tol))
        {
            status = 1;
        }
    }
    else if(et == ERRORTYPE_I32)
    {
        *((int32_t *)p_err)  = abs((*((int32_t *)p_out) - *((int32_t *)p_gold)));
        if(*((int32_t *)p_err) <= *((int32_t *)p_tol))
        {
            status = 1;
        }
    }
    else if(et == ERRORTYPE_UI64)
    {
        *((uint64_t *)p_err)  = abs((*((uint64_t *)p_out) - *((uint64_t *)p_gold)));
        if(*((uint64_t *)p_err) <= *((uint64_t *)p_tol))
        {
            status = 1;
        }
    }
    else if(et == ERRORTYPE_I64)
    {
        *((int64_t *)p_err)  = abs((*((int64_t *)p_out) - *((int64_t *)p_gold)));
        if(*((int64_t *)p_err) <= *((int64_t *)p_tol))
        {
            status = 1;
        }
    }
    else
    {
        // Invalid argument
        assert(0);
    }
    
    return(status);
}

// End of File
