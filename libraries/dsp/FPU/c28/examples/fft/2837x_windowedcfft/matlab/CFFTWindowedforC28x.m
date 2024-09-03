%//#############################################################################
%//! \file /2837x_WindowedCFFT/matlab/CFFTWindowedforC28x.m
%//!
%//! \brief  MATLAB code for the Complex Fast Fourier Transform (Windowed)
%//! \author Vishal Coelho
%//! \date   03/08/2015
%//! 
%//  Group:             C2000
%//  Target Family:     x86
%//
%//#############################################################################
%//
%//
%// 
%// C2000Ware v5.03.00.00
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

clear all
close all

disp('This is Matlab version of C28x Windowed CFFT code');
disp('The result is stored in array X');
disp('The signal is stored in array Rx');

RadStep = 0.1963495408494;

stages=input('Please enter stages (>=3) =');
N=2^stages;
halfSize=N-1;

Rad=[0:RadStep:(halfSize)*RadStep];

even_idx=0:halfSize;
odd_idx=even_idx+1;

CFFTinBuf1=zeros(1,N);

Rx=sin(Rad)+cos(Rad*2.3567);
realOnly=input('Input is \n 1. Real\n 2. Complex: ');
if(realOnly == 1)
    Ix = zeros(1, length(Rx));
else
    Ix=cos(Rad*8.345) + sin(Rad*5.789);
end

windows = ['barthannwin   ';
    'bartlett      ';
    'blackman      ';
    'blackmanharris';
    'bohmanwin     ';
    'chebwin       ';
    'flattopwin    ';
    'gausswin      ';
    'hamming       ';
    'hann          ';
    'kaiser        ';
    'nuttallwin    ';
    'parzenwin     ';
    'rectwin       ';
    'taylorwin     ';
    'triang        ';
    'tukeywin      '];
i = input('Choose window 1-17: ');
windowHandleName = regexprep(windows(i,:), '\s*', '');
W = window(windowHandleName, N)';
Rx = W.*Rx;
Ix = W.*Ix;

x=Rx+ 1i * Ix;

%bit reverse algorithm
for i=1:N
    dr(i) = bin2dec(fliplr(dec2bin(i-1,stages)))+1;
end

dr_1=dr-1;
Rx=Rx(dr);
Ix=Ix(dr);

%stage 1 and 2
for i=1:N/4
    idx=(i-1)*4+1;
    D0=Rx(idx+0);
    D1=Ix(idx+0);
    D2=Rx(idx+1);
    D3=Ix(idx+1);
    D4=Rx(idx+2);
    D5=Ix(idx+2);
    D6=Rx(idx+3);
    D7=Ix(idx+3);
    D0prime=(D0 + D2)+(D4 + D6);
    D1prime=(D1 + D3)+(D5 + D7);
    D2prime=(D0 - D2)+(D5 - D7);
    D3prime=(D1 - D3)-(D4 - D6);
    D4prime=(D0 + D2)-(D4 + D6);
    D5prime=(D1 + D3)-(D5 + D7);
    D6prime=(D0 - D2)-(D5 - D7);
    D7prime=(D1 - D3)+(D4 - D6);  
    
    x_out_2nd(idx+0)=D0prime+j*D1prime;
    x_out_2nd(idx+1)=D2prime+j*D3prime;
    x_out_2nd(idx+2)=D4prime+j*D5prime;
    x_out_2nd(idx+3)=D6prime+j*D7prime;
    
end

x_out=x_out_2nd;

x_out=[x_out,zeros(1,N*2)];

%Twiddle factors generation
table_idx=0:N-1;
cos_table=cos(2*pi*table_idx/N);
sin_table=sin(2*pi*table_idx/N);
coef_table=[sin_table(1:N/4),cos_table(1:N/2)];

CurrentInPtr=1;
CurrentOutPtr=1;
AR2=CurrentInPtr;
AR3=CurrentInPtr;
AR6=CurrentOutPtr;
AR7=CurrentOutPtr;

%stage 3 and up
%num_of_loop=stages-2;
StagesCounter=stages-2;
OuterCounter=N/8;
CoefPtrInc=N/8;
CoefPtr=0;
CurrentSinPtr=CoefPtr;
CurrentCosPtr=CoefPtr+N/4;
InnerCounter=3;
DataPtrInc=4;

AR5=CurrentSinPtr+1;
AR4=CurrentCosPtr+1;

for k=1:StagesCounter
    
    AR0=DataPtrInc;
    AR3=AR3+AR0;
    AR7=AR7+AR0;
    
    AR0=CoefPtrInc;
    D2_1=real(x_out(AR3));%R1H=D2_1
    R1H=D2_1;
    
    for m=1:OuterCounter
        
        Cos_1=coef_table(AR4);
        R2H=Cos_1;
        AR4=AR4+AR0;
        
        %R7H=D2_1*Cos_1;
        R7H=R1H*R2H;
        
        D3_1=imag(x_out(AR3)); %R0H=D3_1
        R0H=D3_1;
        AR3=AR3+1;
        
        Sin_1=coef_table(AR5);
        R3H=Sin_1;
        AR5=AR5+AR0;
        
        %R6H=D3_1*Sin_1;
        R6H=R0H*R3H;
        %R5H=D2_1*Sin_1;
        R5H=R1H*R3H;
        
         for i=1:InnerCounter

             %R7H = (D2_1*Cos_1 + D3_1*Sin_1); %R7H=R7H+R6H
             R7H=R7H+R6H;
             
             D2_2=real(x_out(AR3));%R1H=D2_2
             R1H=D2_2;
             
             %R6H = D3_1*Cos_1;
             R6H=R0H*R2H;
             
             D0_1=real(x_out(AR2));%R3H=D0_1
             R3H=D0_1;
           
             %R4H=D0_1 + (D2_1*Cos_1 + D3_1*Sin_1);%R4H=R3H+R7H;
             R4H=R3H+R7H;
             
             Cos_2=coef_table(AR4);
             R2H=Cos_2;
             AR4=AR4+AR0;
             
             %R6H = (D3_1*Cos_1 - D2_1*Sin_1);%R6H=R6H-R5H;
             R6H=R6H-R5H;
             
             D3_2=imag(x_out(AR3));%R0H
             R0H=D3_2;
             AR3=AR3+1;
             
             D0_1prime=R4H;
             AR6;
             %X(AR6)=D0_1prime;
             
             %R4H = D0_1 - (D2_1*Cos_1 + D3_1*Sin_1);%R4H=R3H-R7H;
             R4H=R3H-R7H;
             
             D2_1prime=R4H;
             %X(AR7)=D2_1prime;
             
             R7H = D2_2*Cos_2;
             
             D1_1=imag(x_out(AR2));%R3H=D1_1
             R3H=D1_1;
             AR2=AR2+1;
             
             %R4H = D1_1 + (D3_1*Cos_1 - D2_1*Sin_1);%R4H=R3H+R6H
             R4H=R3H+R6H;
             
             %R5H = D1_1 - (D3_1*Cos_1 - D2_1*Sin_1);%R5H=R3H-R6H
             R5H=R3H-R6H;
             D2_1=real(x_out(AR3));
             R1H=D2_1;
             
             Sin_2=coef_table(AR5);
             R3H=Sin_2;
             AR5=AR5+AR0;
             
             %R6H = D3_2*Sin_2;%R6H=R0H*R3H
             R6H=R0H*R3H;
             
             D1_1prime=R4H;
             X(AR6)=D0_1prime+j*D1_1prime;
             AR6=AR6+1;
             
             D3_1prime=R5H;
             X(AR7)=D2_1prime+j*D3_1prime;
             AR7=AR7+1;
             
             R5H = D2_2*Sin_2;
             
         end
         
         AR0=DataPtrInc;
         AR4=CurrentCosPtr+1;
         AR5=CurrentSinPtr+1;
         
         %R7H = (D2_2*COS_2 + D3_2*SIN_2)
         R7H=R7H+R6H;

         R6H=real(x_out(AR3));                
         AR3=AR3-1;
         
         % R6H = D3_2*COS_2
         R6H=R0H*R2H;
         
         D0_2=real(x_out(AR2));
         R3H=D0_2;
         
         %R4H = D0_2 + (D2_2*COS_2 + D3_2*SIN_2)
         R4H=R3H+R7H;
 
         D0_2prime=R4H;
         %X(AR6)=D0_2prime
         
         % R6H = (D3_2*COS_2 - D2_2*SIN_2)
         R6H=R6H-R5H;
         
         R5H=imag(x_out(AR3));
         AR3 = AR3 + DataPtrInc+1;
         
         % R4H = D0_2 - (D2_2*COS_2 + D3_2*SIN_2)
         R4H=R3H-R7H;
         D2_2prime=R4H;
         %X(AR7)=D2_2prime;         

         
         D1_2=imag(x_out(AR2));
         R3H=D1_2;
         AR2=AR2+DataPtrInc+1;
         
         % R4H = D1_2 + (D3_2*COS_2 - D2_2*SIN_2)
         R4H=R3H+R6H;   
         
         % R5H = D1_2 - (D3_2*COS_2 - D2_2*SIN_2)
         R5H=R3H-R6H;
         
         AR3;
         D2_1=real(x_out(AR3));
         R1H=D2_1;
         %AR3=AR3+1;
         
         D1_2prime=R4H;
         X(AR6)=D0_2prime+j*D1_2prime;
         AR6=AR6+DataPtrInc+1;
         
         D3_2prime=R5H;
         X(AR7)=D2_2prime+j*D3_2prime;
         AR7=AR7+DataPtrInc+1;
         
         AR0=CoefPtrInc;
    end
    x_out(1:length(X))=X;
    
    DataPtrInc=DataPtrInc*2;
    CoefPtrInc=CoefPtrInc/2;
    
    AR7=CurrentInPtr;
    AR3=CurrentOutPtr;
    AR6=CurrentInPtr;
    AR2=CurrentOutPtr;
    
    InnerCounter=InnerCounter*2+1;
    
    OuterCounter=OuterCounter/2;
end

Magnitude=abs(X);
Phase=angle(X);


% End of file
