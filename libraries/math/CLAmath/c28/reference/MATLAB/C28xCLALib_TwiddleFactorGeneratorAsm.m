%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% C2000 CLA Library Twiddle Factor and bit reversal table Generator
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%//! \brief Generate the Twiddle factors for an N-pt FFT(floating point)
%//!
%//! \author Vishal Coelho
%//! \concept Alex T.
%//!
%//! \details This routine will generate the twiddle factors table
%//! used in the C28x CLA FFT library in an assembly file
%//!
%//! The table generated is a sequence of sine: cosine values in
%//! single precision float. This routine will also generate a bit 
%//! reversal table for the 12-bit addressing space used by the CLA
%//!
%//! The twiddle factor table represents a quarter period of a sine and
%//! cosine wave
%//!
%//! The bit shifted table looks like this (Alex T.)
%//! Index      Index 10 bit Value    Index Bit Rev *4 Value   
%//! 0          0000 0000 0000 0000   0000 0000 0000 0000
%//! 1          0000 0000 0000 0001   0000 1000 0000 0000
%//! 2          0000 0000 0000 0010   0000 0100 0000 0000
%//! 3          0000 0000 0000 0011   0000 1100 0000 0000
%//! 5          0000 0000 0000 0100   0000 0010 0000 0000
%//! ..
%//! ..
%//! ..
%//! 1019       0000 0011 1111 1011   0000 1101 1111 1100
%//! 1020       0000 0011 1111 1100   0000 0011 1111 1100
%//! 1021       0000 0011 1111 1101   0000 1011 1111 1100
%//! 1022       0000 0011 1111 1110   0000 0111 1111 1100
%//! 1023       0000 0011 1111 1111   0000 1111 1111 1100
%//! 
%//! \param[in]  N       size of the FFT(has to be greater than 32)
%//! \param[in] filename  name of file to write the twiddle factors to.
%//!                  It will not write to any file if this argument is 0
%//!
%//! \returns    TF  Twiddle Factors
%//!             BR  Bit reversal table
%//!
function [TF BR] = C28xVCU2Lib_TwiddleFactorGeneratorAsm(N,filename)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Parse Arguments
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
sizeTF = N/4;
TF = single(zeros([1 2*sizeTF]));
BR = single(zeros([1 N]));

HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
fid = fopen(filename,'w');
fprintf(fid,HEAD_string);
fprintf(fid,[';;//! \\file ',filename,'\n;;// \n']);
fprintf(fid,[';;//! \\brief  Twiddle Factors for ',num2str(N),'-pt FFT \n']);
fprintf(fid,';;//! \\author Vishal Coelho \n');
fprintf(fid,[';;//! \\date   ',date,'\n;;//! \n;;//\n']);
fprintf(fid,';;//  Group:\t\t\tC2000\n');
fprintf(fid,';;//  Target Family:\tC28x + CLA\n;;//\n');
fprintf(fid,';;//  (C)Copyright 2013, Texas Instruments, Inc.\n');
fprintf(fid,HEAD_string);
fprintf(fid,';;//$TI Release: PACKAGE NAME $\n');
fprintf(fid,';;//$Release Date: PACKAGE RELEASE DATE $\n');
fprintf(fid,HEAD_string);
fprintf(fid,'\n');

fprintf(fid,BODY_string);
fprintf(fid,';;// includes\n');
fprintf(fid,BODY_string);
fprintf(fid,[';;//!\n;;//! \\addtogroup CLA_FFT Twiddle Factors and',...
    'Bit Reversal Tables\n;;// @{\n']);

fprintf(fid,BODY_string);
fprintf(fid,';;// globals\n');
fprintf(fid,BODY_string);
fprintf(fid,[';;//! \brief Twiddle Factors\n']);
fprintf(fid,[';;//! For N = ',num2str(N),'-pt Complex FFT there are ',...
    num2str(log2(N)),' stages\n;;//! requiring ',num2str(sizeTF),...
    ' complex twiddle factors for the CLA implementation\n']);
fprintf(fid,[';;//! Total space requirement = ',num2str(sizeTF * 2),...
    ' long words(32-bit) or ',num2str(sizeTF * 8),' bytes\n']);

fprintf(fid,'    .sect ".const_cla"\n');
fprintf(fid,'    .global _cla_twiddleFactors\n');
fprintf(fid,'_cla_twiddleFactors:\n');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Twiddle factor table
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
EVEN_IDX = 1;
ODD_IDX = 2;
PIBYTWO = pi/2;
Np = N/4;
for k = 0: 1 : (N/4-1)
    % we are actually caculating e^jwn not e^-jwn
    TF(EVEN_IDX) = single(sin(PIBYTWO*k/Np)); %Store imaginary part
    TF(ODD_IDX) = single(cos(PIBYTWO*k/Np)); %store real part
    S = sprintf(['    .float      %12.10f, %12.10f  ',...
        ';; Sin(pi/2*%4d/%4d) : Cos(pi/2*%4d/%4d)\n'],...
        TF(EVEN_IDX),TF(ODD_IDX),k,Np,k,Np);
    fprintf(fid,S);
    %increment indices
    EVEN_IDX = EVEN_IDX + 2;
    ODD_IDX = ODD_IDX + 2;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Table for Bit reversal
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
bitWidth = 12;
  
fprintf(fid, '\n');
fprintf(fid,BODY_string);
fprintf(fid,';;// Bit Reversal Table\n');
fprintf(fid,BODY_string);
fprintf(fid,'    .align 2"\n');
fprintf(fid,'    .sect ".const_cla"\n');
fprintf(fid,'    .global _cla_bitReversalTable\n');
fprintf(fid,'_cla_bitReversalTable:\n');
S = sprintf([';; Index (Decimal) | Index (Binary)     | Bit Reversed Index (Binary)\n']);
fprintf(fid,S);

for i = 0 : 1 : N-1
  k = bitReverse(i, bitWidth);
  BR(i+1) = k;
   S = sprintf('    .word    %4d  ;; %s(%4d), %s\n',...
        uint16(k),dec2bin(i,12),i,dec2bin(k,12));
    fprintf(fid,S);
end


fprintf(fid,';; @} //addtogroup\n\n');
fprintf(fid,';; End of file\n');
fclose(fid);
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Subroutines
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function T = bitReverse(P,bitWidth)
  maxWidth = 32;
  CLA = fimath();
  CLA.ProductMode       = 'KeepLSB';
  CLA.ProductWordLength = maxWidth;
  CLA.SumMode           = 'KeepLSB';
  CLA.SumWordLength     = maxWidth;
  CLA.OverflowMode      = 'wrap';
  CLA.RoundMode         = 'floor';
  CLA.CastBeforeSum     = true;
  setdefaultfimath(CLA);
  CLA_TYPE = numerictype('Signed',0,'WordLength',maxWidth,'FractionLength',0);
  
  p2 = log2(maxWidth);
  finalShift = 32 - bitWidth;
  T = fi(P, CLA_TYPE, CLA);
  
  for i = 0 : p2-1
      skip = 2 ^ i;
      pattern = fi(hex2dec('FFFFFFFF'),CLA_TYPE, CLA);
      for j = 1 : maxWidth/skip - 1
          pattern = bitxor(pattern, bitshift(pattern,skip));
      end
      A = fi(bitshift(bitand(T,pattern),skip),CLA_TYPE, CLA);
      B = fi(bitand(bitshift(T,-skip),pattern),CLA_TYPE, CLA);
      T = bitor(A,B);
  end
  T = bitshift(T, -finalShift);
end

% End of File
