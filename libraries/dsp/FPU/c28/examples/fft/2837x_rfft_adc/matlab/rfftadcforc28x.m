%//#############################################################################
%//! \file /2837x_RFFT_ADC/matlab/RFFTAdcforC28x.m
%//!
%//! \brief  MATLAB code for the Real Fast Fourier Transform (real-time ADC)
%//! \author C2000
%//!  This matlab code is reference code for debugging FPU library
%//!  function RFFT_adc_f32
%//!   
%//!  Minimum CFFT_Stages is 5. The raw data with 12-bit ADC input format
%//!  is stored in "signal.txt". The data is read out by the matlab fscanf
%//!  function and normalized to the range of 0.0 to 0.1 by dividing by 4096. 
%//!  The real FFT result is stored in the variable X.
%//!
%//!  Watch Variables:
%//!    S               Normalized input signal
%//!    X               Output
%//
%//  Group:             C2000
%//  Target Family:     x86
%//
%//#############################################################################
%//
%//
%// $Copyright:
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
%//#############################################################################
clc
clear all
close all

disp('this is Matlab version of C28x RFFT for 12-bit ADC input');
disp('The result is stored in array X');
disp('The signal is stored in signal.txt ');

stages=input('Please enter stages (>=3) =');
N=2^stages;

fid=fopen('signal.txt')

S=fscanf(fid,'%x');
S=S/4096;

X=fft(S(1:N));


% End of file
