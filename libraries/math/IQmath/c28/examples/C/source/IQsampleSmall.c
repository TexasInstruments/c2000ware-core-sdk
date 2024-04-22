// TI File $Revision: /main/1 $
// Checkin $Date: June 2, 2009   15:53:00 $
//############################################################################
//
// FILE:    IQsampleSmall.c
//
// TITLE:   IQ Math Sample Program In C (for V1.5 of the IQmath library)
//
//  This example is similar to IQsample.c except it has been reduced
//  in size to easily fit in devices with smaller amounts of RAM.
//
//############################################################################
//
//
// $Copyright: Copyright (C) 2014-2024 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

// Select the global Q value to use:
#define GLOBAL_Q    24
long GlobalQ = GLOBAL_Q;      // Used for legacy GEL & Graph Debug.

// Include The Following Definition Files:
#include <stdio.h>
#include <stdlib.h>
#include "IQmathLib.h"

// Specify the data logging size:
#define DATA_LOG_SIZE   64

// Define constants used:
#define X_GAIN          1.0
#define X_FREQ          1.0
#define Y_GAIN          1.0
#define Y_FREQ          1.0
#define PI2             1.570796327
#define PI              3.141592654
#define STEP_X_SIZE     0.314159265
#define STEP_Y_SIZE     0.314159265

// Allocate data log buffers:
struct  DATA_LOG_C {
    _iq   Xwaveform[DATA_LOG_SIZE];
    _iq   Ywaveform[DATA_LOG_SIZE];
    long  Phase[DATA_LOG_SIZE];
    _iq   Mag[DATA_LOG_SIZE];
    _iq   Exp[DATA_LOG_SIZE];
	_iq   Asin[DATA_LOG_SIZE];
    _iq   Log[DATA_LOG_SIZE];
} Dlog;

// Define waveform global variables:
struct  STEP {
    _iq   Xsize;
    _iq  Ysize;
    _iq   Yoffset;
    _iq   X;
    _iq   Y;
    _iq   GainX;
    _iq   GainY;
    _iq   FreqX;
    _iq   FreqY;
} Step;

//----------------------------------------------------------------------------
// Main code:
//----------------------------------------------------------------------------
int main(void)
{
    unsigned int  i;

    _iq tempX, tempY, tempP, tempM, tempMmax;
//  char buffer[20];

    int *WatchdogWDCR = (void *) 0x7029;

    // Disable the watchdog:
    asm(" EALLOW ");
    *WatchdogWDCR = 0x0068;
    asm(" EDIS ");

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

    Step.GainX = _IQ(X_GAIN);
	Step.FreqX = _IQ(X_FREQ);
	Step.GainY = _IQ(Y_GAIN);
	Step.FreqY = _IQ(Y_FREQ);

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
        
        // Use the Log function
        Dlog.Log[i] = _IQlog(Dlog.Exp[i]);

		// Use the asin function
		Dlog.Asin[i] = _IQasin(Dlog.Xwaveform[i]);
                
        // Calculate next offset
        // Sweep from 0 to 2pi, then start over
        Step.X = Step.X + _IQmpy(Step.Xsize, Step.FreqX);
        if( Step.X > _IQ(2*PI) )
            Step.X -= _IQ(2*PI);

        Step.Y = Step.Y + _IQmpy(Step.Ysize, Step.FreqY);
        if( Step.Y > _IQ(2*PI) )
            Step.Y -= _IQ(2*PI);        
    }
}

//############################################################################
// No more.
//############################################################################
