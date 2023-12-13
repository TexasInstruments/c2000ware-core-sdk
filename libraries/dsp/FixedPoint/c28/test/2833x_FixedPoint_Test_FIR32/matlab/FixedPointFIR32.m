% // TI File $Revision: /main/3 $
% // Checkin $Date: November 1, 2010   13:05:07 $
% // =====================================================================================
% //  This software is licensed for use with Texas Instruments C28x
% //  family DSCs.  This license was provided to you prior to installing
% //  the software.  You may review this license by consulting a copy of
% //  the agreement in the doc directory of this library.
% // -------------------------------------------------------------------------------------
% //          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
% //                          All Rights Reserved.
% //======================================================================================
% //
% // 	FILE:    FixedPointFIR32.m
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
% //      fir_lpfxx_Q31		FIR filter coefficients (Q31)
% //      x_Q31             Input signal in Q31 format
% //      result            Filtered signal (Q30)
% //
% //######################################################################################
% //
% // 
% //######################################################################################

clear all
close all

disp('==============================================================');
disp('==============================================================');
disp('this is Matlab version of C28x Fixed Point FIR32 code');
disp('The result is stored in array result Q30');
disp('The signal is stored in array x_raw_sig (float)');
disp('The signal in Q31 format is stored in array x_Q31');
disp('==============================================================');

RadStep = 0.1963495408494;

N=input('Please enter signal length N =');
halfSize=N-1;

Rad=[0:RadStep:(halfSize)*RadStep];

Rx=sin(Rad)+cos(Rad*2.3567);
Ix=0*(cos(Rad*8.345) + sin(Rad*5.789));

x=Rx+j*Ix;
x_raw_sig=x/2;

x_Q31=2^31*x/2;

fir_lpf6_Q31=[-173028710,   422295164,  1025797365,  1025797365,   422295164,  -173028710];
fir_lpf32_Q31=[-2013465,    -3972436,     6056023,     8015159,   -12191477,   -16239507,22805854,    29416457,   -39784147,   -51018844,    68331981,    89804355,-125125486,  -182784383,   316867161,   964016297,   964016297,   316867161,-182784383,  -125125486,    89804355,    68331981,   -51018844,   -39784147,29416457,    22805854,   -16239507,   -12191477,     8015159,     6056023,-3972436,    -2013465];

result=conv(fir_lpf32_Q31,x_Q31)/2^32;

plot(result)


















