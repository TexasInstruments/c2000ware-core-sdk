//#############################################################################
//
// FILE:   eqep_ex1_calculation.c
//
// TITLE:  Position and Speed Measurement Using eQEP (Calculations)
//
// This file includes the eQEP position and speed calculation function called
// by eqep_ex2_pos_speed.c.  The position and speed calculation steps performed
// by PosSpeed_calculate() are described below:
//
// 1. This program calculates: **thetaMech**
//
//      thetaMech = QPOSCNT / mechScaler
//                = QPOSCNT / 4000, where 4000 is the number of counts in 1 rev
//                                (4000 / 4 = 1000 line/rev quadrature encoder)
//
// Note this example uses mechScaler = 16776 which is _IQ26(1 / 4000)
//
// 2. This program calculates: **thetaElec**
//
//      thetaElec = (pole pairs) * thetaMech = 2 * QPOSCNT / 4000 in this case
//
// 3. This program calculates: **speedRPMFR**
//
//      speedRPMFR = [(x2 - x1) / 4000] / T                         -Equation 1
//
// Note (x2 - x1) = difference in number of QPOSCNT counts. Dividing (x2 - x1)
// by 4000 gives position relative to Index in one revolution.
//
// If base RPM = 6000 rpm:
//      6000 rpm = [(x2 - x1) / 4000] / 10ms                        -Equation 2
//               = [(x2 - x1) / 4000] / (.01s * 1 min / 60 sec)
//               = [(x2 - x1) / 4000] / (1 / 6000) min
//
//      max (x2 - x1) = 4000 counts or 1 revolution in 10 ms
//
// If both sides of Equation 2 are divided by 6000 rpm, then:
//      1 = [(x2 - x1) / 4000] rev / [(1 / 6000) min * 6000rpm]
//
// Because (x2 - x1) must be < 4000 (max) for QPOSCNT increment,
// (x2 - x1) / 4000 < 1 for CW rotation, and because (x2 - x1) must be >- 4000
// for QPOSCNT decrement, (x2 - x1) / 4000 > -1  for CCW rotation
//
//      speedFR = [(x2 - x1) / 4000] / [(1 / 6000) min * 6000rpm]
//              = (x2 - x1) / 4000                                  -Equation 3
//
// To convert speedFR to RPM, multiply Equation 3 by 6000 rpm:
//      speedRPMFR = 6000rpm * (x2 - x1) / 4000                 -Final Equation
//
//
// 2. **min rpm ** = selected at 10 rpm based on CCPS prescaler options
// available (128 is greatest)
//
// 3. **speedRPMPR**
//      speedRPMPR = X / (t2 - t1)                                  -Equation 4
//
// where X = QCAPCTL [UPPS] / 4000 rev (position relative to Index in 1 rev)
//
// If max / base speed = 6000 rpm:
//      6000 = (32 / 4000) / [(t2 - t1) / (SYSCLKFREQ / 64)]
//
// where 32 = QCAPCTL[UPPS] (Unit timeout once every 32 edges)
//
//      32 / 4000 = position in 1 rev (position as a fraction of 1 revolution)
//
//      t2 - t1 / (SYSCLKFREQ / 64), t2 - t1 = # of QCAPCLK cycles
//
//      QCAPCLK cycle = 1 / (SYSCLKFREQ / 64)
//                    = QCPRDLAT
//
// So:
//      6000 rpm = [32(SYSCLKFREQ / 64) * 60s/min] / [4000(t2 - t1)]
//
//      t2 - t1 = [32(SYSCLKFREQ / 64) * 60s/min]/(4000 * 6000rpm)  -Equation 5
//              = 250 CAPCLK cycles
//              = maximum (t2 - t1) = speedScaler
//
// Divide both sides by (t2 - t1) and:
//      1 = 32 / (t2 - t1)
//        = [32(SYSCLKFREQ / 64) * 60 s/min] / (4000 * 6000rpm) / (t2 - t1)
//
// Because (t2 - t1) must be < 250 for QPOSCNT, increment 250 / (t2 - t1) < 1
// for CW rotation, and because (t2 - t1) must be > -250 for QPOSCNT decrement
// 250 / (t2 - t1) > -1 for CCW rotation
//
//    speedPR = 250 / (t2 - t1)
//            = [32(SYSCLKFREQ / 64) * 60 s/min] / (4000 * 6000rpm) / (t2 - t1)
//                                                                  -Equation 6
//
// To convert speedPR to RPM, multiply Equation 6 by 6000rpm:
//      speedRPMFR = [32(SYSCLKFREQ / 64) * 60s/min] / [4000 * (t2 - t1)]
//                 = [(32 / 4000) rev * 60s/min] / [(t2 - t1)(QCPRDLAT)]
//                                                              -Final Equation
//
// More detailed calculation results can be found in the
// eqep_ex2_calculation.xls spreadsheet included in the example folder.
//
//#############################################################################
//
// 
// $Copyright:
// Copyright (C) 2013-2024 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include "eqep_ex2_calculation.h"

//
// Function to calculate the frequency of the input signal using both the unit
// timer and the quadrature capture units.
//
// For a more detailed explanation of the calculations, read the description at
// the top of this file.
//
void PosSpeed_calculate(PosSpeed_Object *p)
{
    int32_t temp;
    uint16_t pos16bVal, temp1;
    _iq temp2, newPosCnt, oldPosCnt;

    //
    // **** Position calculation - mechanical and electrical motor angle ****
    //
    // Get the motor direction: -1 = CCW/reverse, 1 = CW/forward
    //
    p->directionQEP = EQEP_getDirection(EQEP1_BASE);

    //
    // Capture position once per QA/QB period
    //
    pos16bVal = (uint16_t)EQEP_getPosition(EQEP1_BASE);

    //
    // Raw theta = current pos. + ang. offset from QA
    //
    p->thetaRaw = pos16bVal + p->calAngle;

    //
    // The following lines calculate
    //
    // p->thetaMech ~= QPOSCNT / mechScaler [current cnt/(total cnt in 1 rev)]
    //
    // where mechScaler = 4000 cnts/revolution
    //
    temp = (int32_t)p->thetaRaw * (int32_t)p->mechScaler;   // Q0 * Q26 = Q26
    temp &= 0x03FFF000;

    p->thetaMech = (int16_t)(temp >> 11);                    // Q26 -> Q15
    p->thetaMech &= 0x7FFF;

    //
    // The following lines calculate p->elec_mech
    //
    p->thetaElec = p->polePairs * p->thetaMech;               // Q0 * Q15 = Q15
    p->thetaElec &= 0x7FFF;

    //
    // Check for an index occurrence
    //
    if((EQEP_getInterruptStatus(EQEP1_BASE) & EQEP_INT_INDEX_EVNT_LATCH) != 0U)
    {
        EQEP_clearInterruptStatus(EQEP1_BASE, EQEP_INT_INDEX_EVNT_LATCH);
    }

    //
    // **** High Speed Calculation using QEP Position counter ****
    //
    // Check for unit timeout event
    //
    if((EQEP_getInterruptStatus(EQEP1_BASE) & EQEP_INT_UNIT_TIME_OUT) != 0)
    {
        //
        // The following lines calculate position:
        // (x2 - x1) / 4000 (position in 1 revolution)
        //
        pos16bVal = (uint16_t)EQEP_getPositionLatch(EQEP1_BASE);
        temp = (int32_t)pos16bVal * (int32_t)p->mechScaler; // Q0 * Q26 = Q26
        temp &= 0x03FFF000;

        temp = (int16_t)(temp >> 11);                        // Q26 -> Q15
        temp &= 0x7FFF;

        newPosCnt = _IQ15toIQ(temp);
        oldPosCnt = p->oldPos;

        //
        // POSCNT is counting down
        //
        if(p->directionQEP == -1)
        {
            if(newPosCnt > oldPosCnt)
            {
                //
                // x2 - x1 should be negative
                //
                temp2 = -(_IQ(1) - newPosCnt + oldPosCnt);
            }
            else
            {
                temp2 = newPosCnt -oldPosCnt;
            }
        }
        //
        // POSCNT is counting up
        //
        else if(p->directionQEP == 1)
        {
            if(newPosCnt < oldPosCnt)
            {
                temp2 = _IQ(1) + newPosCnt - oldPosCnt;
            }
            else
            {
                //
                // x2 - x1 should be positive
                //
                temp2 = newPosCnt - oldPosCnt;
            }
        }

        if(temp2 > _IQ(1))
        {
            p->speedFR = _IQ(1);
        }
        else if(temp2 < _IQ(-1))
        {
            p->speedFR = _IQ(-1);
        }
        else
        {
            p->speedFR = temp2;
        }

        //
        // Update the electrical angle
        //
        p->oldPos = newPosCnt;

        //
        // Change motor speed from pu value to rpm value (Q15 -> Q0)
        // Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
        //
        p->speedRPMFR = _IQmpy(p->baseRPM, p->speedFR);

        //
        // Clear unit time out flag
        //
        EQEP_clearInterruptStatus(EQEP1_BASE, EQEP_INT_UNIT_TIME_OUT);
    }

    //
    // **** Low-speed computation using QEP capture counter ****
    //
    // Check for unit position event
    //
    if((EQEP_getStatus(EQEP1_BASE) & EQEP_STS_UNIT_POS_EVNT) != 0)
    {
        //
        // No Capture overflow
        //
        if((EQEP_getStatus(EQEP1_BASE) & EQEP_STS_CAP_OVRFLW_ERROR) == 0)
        {
            temp1 = (uint32_t)EQEP_getCapturePeriodLatch(EQEP1_BASE);
        }
        else
        {
            //
            // Capture overflow, saturate the result
            //
            temp1 = 0xFFFF;
        }

        //
        // p->speedPR = p->speedScaler / temp1
        //
        p->speedPR = _IQdiv(p->speedScaler, temp1);
        temp2 = p->speedPR;

        if(temp2 > _IQ(1))
        {
           p->speedPR = _IQ(1);
        }
        else
        {
           p->speedPR = temp2;
        }

        //
        // Convert p->speedPR to RPM
        //
        // Reverse direction = negative
        //
        if(p->directionQEP == -1)
        {
            //
            // Q0 = Q0 * GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
            //
            p->speedRPMPR = -_IQmpy(p->baseRPM, p->speedPR);
        }
        //
        // Forward direction = positive
        //
        else
        {
            //
            // Q0 = Q0 * GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
            //
            p->speedRPMPR = _IQmpy(p->baseRPM, p->speedPR);
        }

        //
        // Clear unit position event flag and overflow error flag
        //
        EQEP_clearStatus(EQEP1_BASE, (EQEP_STS_UNIT_POS_EVNT |
                                      EQEP_STS_CAP_OVRFLW_ERROR));
    }
}
