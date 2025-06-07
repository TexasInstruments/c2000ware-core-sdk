%//#############################################################################
%//! \file /2837x_FIR/matlab/FIR32forC28x.m
%//!
%//! \brief  MATLAB code for the Finite Impulse Response Filter
%//! \author C2000
%//! 
%//  Group:             C2000
%//  Target Family:     x86
%//
%//#############################################################################
%//
%//
%// 
%// C2000Ware v5.05.00.00
%//Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
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
%//#############################################################################

clc
clear all
close all

FREQ1 = 1e3;    %1KHz signal
FREQ2 = 33e3;   %33KHz signal
SAMPLING_FREQ = 100e3; %100KHz

FIR_ORDER = 63;
BUFFER_SIZE = (FIR_ORDER+1) * 4;

k1 = FREQ1/SAMPLING_FREQ;
k2 = FREQ2/SAMPLING_FREQ;

i = 1 : 1 : BUFFER_SIZE;

S = 0.5*(sin(2*pi*k1*i) + sin(2*pi*k2*i));

N     = FIR_ORDER;   % Order
Fpass = 0.07;  % Passband Frequency
Fstop = 0.15;  % Stopband Frequency
Wpass = 1;    % Passband Weight
Wstop = 1;    % Stopband Weight
dens  = 20;   % Density Factor

% Calculate the coefficients using the FIRPM function.
b  = firpm(N, [0 Fpass Fstop 1], [1 1 0 0], [Wpass Wstop], {dens});
Hd = dfilt.dffir(b);

Fc = Hd.Numerator;

S_filt = conv(S,Fc);
S_filt = S_filt(1:BUFFER_SIZE);

%plot of the signal
subplot(1,2,1),plot(S),grid on;
axis([0 BUFFER_SIZE-1 -2 2]);
title('Signal')
xlabel('time (microseconds)')

%plot of the filtered signal
subplot(1,2,2),
plot(S_filt),grid on;
axis([0 BUFFER_SIZE-1 -2 2]);
title('LPF Signal')
xlabel('time (microseconds)')


% End of file
