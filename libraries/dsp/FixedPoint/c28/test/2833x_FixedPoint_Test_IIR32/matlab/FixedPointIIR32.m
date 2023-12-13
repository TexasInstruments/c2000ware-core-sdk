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
% // 	FILE:    FixedPointIIR32.m
% //
% // 	TITLE:   DSP2833x Device Fixed Point 32 Bit IIR Test Program   
% //
% //
% // 	ASSUMPTIONS:
% //
% //   	This matlab code is reference code for debugging FixedPoint DSP library
% //    function IIR32_calc and example project 2833x_FixedPoint_IIR32. 
% //
% //
% //   
% //    Watch Variables:
% //
% //      x_raw_sig         Input signal (float)
% //      x_Q31             Input signal (Q31)
% //      B,A               IIR filter coefficients array b,a
% //      filter_out_Q31    Filtered result using standard MATLAB filter function
% //                        filer. It is used as reference to compare with
% //                        the fixed point result. (Q31)
% //      x_output_final    Output data by fixed point algorithm (Q31). 
% //
% //######################################################################################
% //
% // 
% //######################################################################################

clear all
close all

disp('==============================================================');
disp('input signal is stored as Q31 format');
disp('==============================================================');
disp('this is Matlab version of IIR32 code');
disp('The result is stored in array x_output_final in Q31 format');
disp('The signal is stored in array x_raw_sig');
disp('The fixed point input signal is stored in x_Q31 in Q31 format');
disp('==============================================================');

MAX_TAPS=5;

RadStep = 0.1963495408494;

N=input('Please enter signal length N =');
halfSize=N-1;

Rad=[0:RadStep:(halfSize)*RadStep];

Rx=sin(Rad)+cos(Rad*2.3567);
Ix=0*(cos(Rad*8.345) + sin(Rad*5.789));

x=Rx+j*Ix;
x_raw_sig=x/2;

x_Q31=2^31*x/2;

B=[      0.000176614401432267
       0.00123630081002587
       0.00370890243007761
       0.00618150405012935
       0.00618150405012935
       0.00370890243007761
       0.00123630081002587
      0.000176614401432267];

A=[                         1
         -3.84708594662977
          6.78600477287384
         -6.96288772960265
          4.44516236478943
         -1.75415688503484
          0.39441771610976
       -0.0388476491224433];
   
 A=A';B=B';
 
 filter_out_Q31=filter(B,A,x_Q31);

% good
 isos=[ 20118017   20118017   0         536870912  -248624377     0
        43749199   87498398  43749199   536870912  -517372703   141524868
        35450657   70901314  35450657   536870912  -583544331   228291242
       875854244   1751708488 875854244 536870912  -715847129   401770939];

 isf=288246535;
 
d=zeros(4,3);
taps=3;

for k=1:length(x_Q31)
    
    accum=floor(x_Q31(k)*isf/2^32);
    
    for j=1:4

        b_temp=isos(j,1:3);
        a_temp=isos(j,4:6);
        
        for ii=2:taps
            accum=accum-ceil(a_temp(ii)*d(j,ii)/2^32);
        end

        d(j,1)=floor(accum*2^3);
        
        accum1=0;
        
        for ii=1:taps
            accum1=accum1+floor(b_temp(ii)*d(j,ii)/2^32);
        end
        
        for ii=(taps-2+1):-1:1
            d(j,ii+1)=d(j,ii);
        end
        
        accum=floor(accum1);
    
    end
    
    x_no_scale_biq_fixed(k)=(accum1)*2^3;      % direct I form high order implementation output
    
end
   
figure(1)
plot(filter_out_Q31)
peak1=max(filter_out_Q31);
hold on
peak2=max(x_no_scale_biq_fixed);
plot(x_no_scale_biq_fixed,'r')

x_output_final=floor(x_no_scale_biq_fixed/2);












