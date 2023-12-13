% // TI File $Revision: /main/3 $
% // Checkin $Date: November 1, 2010   13:05:07 $
% // =====================================================================================
% //  This software is licensed for use with Texas Instruments C28x
% //  family DSCs.  This license was provided to you prior to installing
% //  the software.  You may review this license by consulting a copy of
% //  the agreement in the doc directory of this library.
% //======================================================================================
% //
% // 	FILE:    FixedPointFIR16.m
% //
% // 	TITLE:   DSP2833x Device Fixed Point FIR16 Test Program.   
% //
% //
% // 	ASSUMPTIONS:
% //
% //   	This matlab code is reference code for debugging FixedPoint DSP library
% //    16 bit FIR module and example project 2833x_FixedPoint_FIR16. 
% //
% //
% //   
% //    Watch Variables:
% //
% //      x_raw_sig         Input signal (float)
% //      fir_lpfxx_Q15		FIR filter coefficients (Q15)
% //      x_Q15             Input signal in Q15 format
% //      output            Filtered signal (Q15)
% //
% //######################################################################################
% //
% // 
% // $Copyright:
%// Copyright (C) 2022 Texas Instruments Incorporated - http://www.ti.com
%//
%// Redistribution and use in source and binary forms, with or without 
%// modification, are permitted provided that the following conditions 
%// are met:
%// 
%//   Redistributions of source code must retain the above copyright 
%//   notice, this list of conditions and the following disclaimer.
%// 
%//   Redistributions in binary form must reproduce the above copyright
%//   notice, this list of conditions and the following disclaimer in the 
%//   documentation and/or other materials provided with the   
%//   distribution.
%// 
%//   Neither the name of Texas Instruments Incorporated nor the names of
%//   its contributors may be used to endorse or promote products derived
%//   from this software without specific prior written permission.
%// 
%// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
%// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
%// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
%// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
%// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
%// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
%// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
%// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
%// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
%// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
%// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
%//$
% //######################################################################################

clear all
close all

disp('==============================================================');
disp('==============================================================');
disp('this is Matlab version of C28x Fixed Point FIR16 code');
disp('The result is stored in array output Q15');
disp('The signal is stored in array x_raw_sig (float)');
disp('The signal in Q15 format is stored in array x_Q15');
disp('==============================================================');

RadStep = 0.1963495408494;

N=input('Please enter signal length N =');
halfSize=N-1;

Rad=[0:RadStep:(halfSize)*RadStep];

Rx=sin(Rad)+cos(Rad*2.3567);
Ix=0*(cos(Rad*8.345) + sin(Rad*5.789));

x=Rx+j*Ix;
x_raw_sig=x/2;

x_Q15=2^15*x/2;

fir_lpf6_Q15=[-3368,347,17612,17612,347,-3368];

fir_lpf7_Q15=[-891,  -4096,   9083,  21178,   9083,  -4096,   -891];

fir_lpf32_Q15=[-31,    -61,     92,    122,   -186,   -248,    348,    449,   -607, -778,   1043,   1370,  -1909,  -2789,   4835,  14710,  14710,   4835, -2789,  -1909,   1370,   1043,   -778,   -607,    449,    348,   -248, -186,    122,     92,    -61,    -31];

%result=conv(fir_lpf6_Q15,x_Q15)*2^7/2^6/2^16;
%result=conv(fir_lpf7_Q15,x_Q15)*2^7/2^6/2^16;
result=conv(fir_lpf32_Q15,x_Q15)*2^7/2^6/2^16;

output=floor(result(1:N));

plot(output)

















