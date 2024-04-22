//############################################################################
//
// FILE:    IQsample.c
//
// TITLE:   IQ Math Sample Program In C++ 
//
//############################################################################
//###########################################################################
//
//
// $Copyright: Copyright (C) 2014-2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

// Select the global Q value to use:
#define GLOBAL_Q    24
long GlobalQ = GLOBAL_Q;      // Used for GEL & Graph Debug.

// Include The Following Definition Files:
#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include "IQmathLib.h"
}
#include "IQmathCPP.h"

// Specify the data logging size:
#define DATA_LOG_SIZE   64

// Define constants used:
#define X_GAIN          1.0f
#define X_FREQ          1.0f
#define Y_GAIN          1.0f
#define Y_FREQ          1.0f
#define PI2             1.570796327f
#define PI              3.141592654f
#define STEP_X_SIZE     0.314159265f
#define STEP_Y_SIZE     0.314159265f

// Allocate data log buffers:
struct  DATA_LOG_C {
    iq   Xwaveform[DATA_LOG_SIZE];
    iq   Ywaveform[DATA_LOG_SIZE];
    long  Phase[DATA_LOG_SIZE];
    iq   Mag[DATA_LOG_SIZE];
    iq   Exp[DATA_LOG_SIZE];    
    iq   Log[DATA_LOG_SIZE]; 
} Dlog;

// Define waveform global variables:
struct  STEP {
    iq   Xsize;
    iq   Ysize;
    iq   Yoffset;
    iq   X;
    iq   Y;
    iq   GainX;
    iq   GainY;
    iq   FreqX;
    iq   FreqY;
} Step;

//----------------------------------------------------------------------------
// Main code:
//----------------------------------------------------------------------------
int main(void)
{
    unsigned int  i;

    iq  tempX, tempY, tempP, tempM, tempMmax;

    int *WatchdogWDCR = (int *) 0x7029;

    // Disable the watchdog:
    asm(" EALLOW ");
    *WatchdogWDCR = 0x0068;
    asm(" EDIS ");

    Step.Xsize = IQ(STEP_X_SIZE);
    Step.Ysize = IQ(STEP_Y_SIZE);
    Step.Yoffset = 0;
    Step.X = 0;
    Step.Y = Step.Yoffset;

    for(i=0; i < DATA_LOG_SIZE; i++)
    {
        Dlog.Xwaveform[i] = 0;
        Dlog.Ywaveform[i] = 0;
        Dlog.Phase[i]     = 0;
        Dlog.Mag[i]       = 0;
        Dlog.Exp[i]       = 0;
        Dlog.Log[i]       = 0;
    }

    Step.GainX = _IQ(X_GAIN);
	Step.FreqX = _IQ(X_FREQ);
	Step.GainY = _IQ(Y_GAIN);
	Step.FreqY = _IQ(Y_FREQ);

    // Calculate maximum magnitude value:
    tempMmax = IQmag(Step.GainX, Step.GainY);

    for(i=0; i < DATA_LOG_SIZE; i++)
        {
        // Calculate waveforms:
        Step.X = Step.X + Step.Xsize * Step.FreqX;
        if( Step.X >  IQ(2*PI) )
            Step.X -= IQ(2*PI);

        Step.Y = Step.Y + Step.Ysize * Step.FreqY;
        if( Step.Y >  IQ(2*PI) )
            Step.Y -= IQ(2*PI);

        Dlog.Xwaveform[i] = tempX = IQsin(Step.X) * Step.GainX;
        Dlog.Ywaveform[i] = tempY = IQabs(IQsin(Step.Y)) * Step.GainY;

        // Calculate normalized magnitude:
        //
        // Mag = sqrt(X^2 + Y^2)/sqrt(GainX^2 + GainY^2);
        tempM = IQmag(tempX, tempY);
        Dlog.Mag[i] = tempM / tempMmax;

        // Calculate normalized phase:
        //
        // Phase = (long) (atan2PU(X,Y) * 360);
        tempP = IQatan2PU(tempY,tempX);
        Dlog.Phase[i] = IQmpyI32int(tempP, 360);
        
        // Use the exp function
        Dlog.Exp[i] = IQexp(IQ(.075L) * IQ(i));
        
        // Use the log function
        Dlog.Log[i] = IQlog(Dlog.Exp[i]);
        
    }
}

//############################################################################
// No more.
//############################################################################
