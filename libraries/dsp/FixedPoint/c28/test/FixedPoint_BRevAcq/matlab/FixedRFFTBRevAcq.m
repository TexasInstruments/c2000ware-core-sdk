% // TI File $Revision: /main/3 $
% // Checkin $Date: November 1, 2010   13:05:07 $
% // =====================================================================================
% //  This software is licensed for use with Texas Instruments C28x
% //  family DSCs.  This license was provided to you prior to installing
% //  the software.  You may review this license by consulting a copy of
% //  the agreement in the doc directory of this library.
% //======================================================================================
% //
% // 	FILE:    FixedRFFBRevAcq.m
% //
% // 	TITLE:   DSP2833x Device Fixed Point Real Input Point by Point Bit
% //             Reversed Test Program.   
% //
% //
% // 	ASSUMPTIONS:
% //
% //   	This matlab code is reference code for debugging FixedPoint DSP library
% //    module BRevAcq and example project 2833x_FixedPoint_BrevAcq. 
% //
% //
% //   
% //    Watch Variables:
% //
% //      x_raw_sig         Input signal (float)
% //      Rx,Ix				Bit-revesed real and imaginary part of signal
% //                        (Q31)
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
disp('input signal is stored as Q31 format');
disp('==============================================================');
disp('this is Matlab version of C28x Fixed Point RFFT code');
disp('The result is stored in array X');
disp('The signal is stored in array x_raw_sig');
disp('==============================================================');

RadStep = 0.1963495408494;

stages=input('Please enter stages (>=3) =');
N=2^stages;
halfSize=N-1;

Rad=[0:RadStep:(halfSize)*RadStep];

even_idx=0:halfSize;
odd_idx=even_idx+1;

CFFTinBuf1=zeros(1,N);

Rx=sin(Rad)+cos(Rad*2.3567);
Ix=0*(cos(Rad*8.345) + sin(Rad*5.789));

x=Rx+j*Ix;
x_raw_sig=x/2;

x_win=Rx.*hamming(N)';

fft_float=2^31*fft(x/2)/N;

%bit reverse algorithm
for i=1:N
    dr(i) = bin2dec(fliplr(dec2bin(i-1,stages)))+1;
end

dr_1=dr-1;
Rx=2^31*x(dr)/2;
Ix=2^31*Ix(dr)/2;




















