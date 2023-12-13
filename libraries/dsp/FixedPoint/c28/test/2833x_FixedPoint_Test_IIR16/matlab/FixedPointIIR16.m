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
% // 	FILE:    FixedPointIIR16.m
% //
% // 	TITLE:   DSP2833x Device Fixed Point 16 Bit IIR Test Program   
% //
% //
% // 	ASSUMPTIONS:
% //
% //   	This matlab code is reference code for debugging FixedPoint DSP library
% //    function IIR32_calc and example project 2833x_FixedPoint_IIR16. 
% //
% //
% //   
% //    Watch Variables:
% //
% //      x_raw_sig         Input signal (float)
% //      x_Q15             Input signal (Q15)
% //      B,A               IIR filter coefficients array b,a
% //      filter_out_Q15    Filtered result using standard MATLAB filter function
% //                        filer. It is used as reference to compare with
% //                        the fixed point result. (Q15)
% //      x_output_final    Output data by fixed point algorithm (Q15). 
% //
% //######################################################################################
% //
% // 
% //######################################################################################

clear all
close all

disp('==============================================================');
disp('input signal is stored as Q16 format');
disp('==============================================================');
disp('this is Matlab version of IIR16 code');
disp('The result is stored in array x_output_final in Q15 format');
disp('The signal is stored in array x_raw_sig');
disp('The fixed point input signal is stored in x_Q15 in Q15 format');
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

x_Q15=2^15*x/2;

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
 
 filter_out_Q15=filter(B,A,x_Q15);

% good
 isos=[         307         307           0        8192       -3794           0
         668        1335         668        8192       -7894        2159
         541        1082         541        8192       -8904        3483
       13364       26729       13364        8192      -10923        6131];

%  isos=[         2456         2456           0        8192       -7587           0
%          1329        2658         1329        8192       -15789        4319
%          1032        2064         1032        8192       -17808        6967
%        7039       14079       7039        8192      -21846        12261];

% isos=[15468       30936       15468       16384       10598        4039];

isf=4398;
nbiq=4;
qfmat=13;
 
d=zeros(nbiq,3);
taps=3;

for k=1:length(x_Q15)
    
    accum=floor(x_Q15(k)*isf);
    
    for j=1:nbiq

        b_temp=isos(j,1:3);
        a_temp=isos(j,4:6);
        
        for ii=2:taps
            accum=accum-floor(a_temp(ii)*d(j,ii));
        end
        
%         d(j,1)=accum*2^3/2^16;
        d(j,1)=floor(accum/2^qfmat);
        
        accum1=0;
        
        for ii=1:taps
            accum1=accum1+floor(b_temp(ii)*d(j,ii));
        end
        
        for ii=(taps-2+1):-1:1
            d(j,ii+1)=d(j,ii);
        end
        
        accum=floor(accum1);
    
    end
    
    x_no_scale_biq_fixed(k)=(accum1)/2^qfmat;      % direct I form high order implementation output
    
end
   
figure(1)
plot(filter_out_Q15)
peak1=max(filter_out_Q15);
hold on
peak2=max(x_no_scale_biq_fixed);
plot(x_no_scale_biq_fixed,'r')

x_output_final=floor(x_no_scale_biq_fixed/2);













