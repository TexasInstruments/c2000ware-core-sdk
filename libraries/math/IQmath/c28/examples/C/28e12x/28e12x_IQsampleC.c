//############################################################################
//
// FILE:    28e12x_IQsampleC.c
//
// TITLE:   IQ Math Sample Program In C 
//
//############################################################################
//#############################################################################
//
//
// $Copyright: Copyright (C) 2014-2025 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

// Select the global Q value to use:
#define GLOBAL_Q    24
long GlobalQ = GLOBAL_Q;      // Used for legacy GEL & Graph Debug.

// Include The Following Definition Files:
#include <stdio.h>
#include <stdlib.h>
#if defined(SYCONFIG)
#include "c2000ware_libraries.h"
#endif 

// Specify the data logging size:
#define DATA_LOG_SIZE   64

// Define constants used:
#define PI2             1.570796327f
#define PI              3.141592654f
#define STEP_X_SIZE     0.314159265f
#define STEP_Y_SIZE     0.314159265f

// Allocate data log buffers:
struct  DATA_LOG_C {
    _iq   Xwaveform[DATA_LOG_SIZE];
    _iq   Ywaveform[DATA_LOG_SIZE];
    long  Phase[DATA_LOG_SIZE];
    _iq   Mag[DATA_LOG_SIZE];
    _iq   Exp[DATA_LOG_SIZE];
    _iq   Log[DATA_LOG_SIZE];
} Dlog;

// Define waveform global variables:
struct  STEP {
    _iq   Xsize;
    _iq   Ysize;
    _iq   Yoffset;
    _iq   X;
    _iq   Y;
    _iq   GainX;
    _iq   GainY;
    _iq   FreqX;
    _iq   FreqY;
} Step;

extern _iq test_Xwaveform_golden[64];
extern _iq test_Ywaveform_golden[64];
extern _iq test_Exp_golden[64];
extern _iq test_Mag_golden[64];
extern long test_Phase_golden[64];
extern _iq test_Log_golden[64];

// The global pass, fail values
uint16_t pass = 0U, fail = 0U;

//----------------------------------------------------------------------------
// Main code:
//----------------------------------------------------------------------------
void main(void)
{
    unsigned int  i;

    _iq tempX, tempY, tempP, tempM, tempMmax;
    SysCtl_disableWatchdog();
    
    tempX = _IQacos(_IQ(.3492));

    Step.Xsize = _IQ(STEP_X_SIZE);
    Step.Ysize = _IQ(STEP_Y_SIZE);
    Step.Yoffset = 0;
    Step.X = 0;
    Step.Y = Step.Yoffset;

    // Fill the buffers with some initial value
    for(i=0; i < DATA_LOG_SIZE; i++)
    {
        Dlog.Xwaveform[i] = _IQ(0.0);
        Dlog.Ywaveform[i] = _IQ(0.0);
        Dlog.Mag[i] = _IQ(0.0);
        Dlog.Phase[i] = _IQ(0.0);
        Dlog.Exp[i] = _IQ(0.0);
        Dlog.Log[i] = _IQ(0.0);
    }

    Step.GainX = _IQ(2.0);
    Step.FreqX = _IQ(2.0);
    Step.GainY = _IQ(3.0);
    Step.FreqY = _IQ(3.0);

    // Calculate maximum magnitude value:
    tempMmax = _IQmag(Step.GainX, Step.GainY);

    for(i=0; i < DATA_LOG_SIZE; i++)
    {

        Dlog.Xwaveform[i] = tempX = _IQmpy(_IQsin(Step.X), Step.GainX);
        Dlog.Ywaveform[i] = tempY = _IQmpy(_IQabs(_IQsin(Step.Y)), Step.GainY);

        // Calculate normalized magnitude:
        //
        // Mag = sqrt(X^2 + Y^2)/sqrt(GainX^2 + GainY^2);
        tempM = _IQmag(tempX, tempY);
        Dlog.Mag[i] = _IQdiv(tempM, tempMmax);

        // Calculate normalized phase:
        //
        // Phase = (long) (atan2PU(X,Y) * 360);
        tempP = _IQatan2PU(tempY,tempX);
        Dlog.Phase[i] = _IQmpyI32int(tempP, 360);

        // Use the exp function
        Dlog.Exp[i] = _IQexp(_IQmpy(_IQ(.075L),_IQ(i)));
        
        // Use the log function
        Dlog.Log[i] = _IQlog(Dlog.Exp[i]);
        
        // Calculate next step:
        Step.X = Step.X + _IQmpy(Step.Xsize, Step.FreqX);
        if( Step.X > _IQ(2*PI) )
            Step.X -= _IQ(2*PI);

        Step.Y = Step.Y + _IQmpy(Step.Ysize, Step.FreqY);
        if( Step.Y > _IQ(2*PI) )
            Step.Y -= _IQ(2*PI);
    
    }
    
    // Check the output
    for(i = 0; i < DATA_LOG_SIZE; i++)
    {
        if((Dlog.Xwaveform[i] == test_Xwaveform_golden[i])&& 
           (Dlog.Ywaveform[i] == test_Ywaveform_golden[i])&&
           (Dlog.Exp[i] == test_Exp_golden[i])&&
           (Dlog.Mag[i] == test_Mag_golden[i])&&
           (Dlog.Phase[i] == test_Phase_golden[i])&&
           (Dlog.Log[i] == test_Log_golden[i]))
        {
            pass++;
        }
        else
        {
            fail++;
        }
    }
}

//############################################################################
// No more.
//############################################################################
