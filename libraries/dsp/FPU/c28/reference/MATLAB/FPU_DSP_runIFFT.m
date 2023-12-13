%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate Inverse FFT Input/Ouput Vectors
% \author Vishal Coelho
% \date   11/09/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Inverse Fast Fourier Transform
% There are a few ways to do this using the forward inverse transform
%   n = 0:31
%   x = sin(2*pi*0.1*n)
%   y = fft(x)
% # The offplace method (requires two separate buffers to implement)
%   p = fft(y)./32;
%   q = [p(1) p(end:-1:2)]
% # The inplace method - conjugate the input and outputs
%   This is the method being used here. Each stage does a divide by 2
%   p = fft(conj(y))./32;
%   q = conj(p);
% # The inplace method - flip the real imaginary parts before and after
%   the fft
%   p = imag(y)+1i.*real(y)
%   q = fft(p)./32
%   r = imag(q)+1i.*real(q)
% You can find the error between the original and recreated using the norm
%   e = norm(x - q)
%
%% Required Parameters
% * *iffttype*, must be one of the following
% # 'real'
% # 'complex'
% * *radix*, must be one of the following
% # 2
% # 4
% * *N* size of the input vector (32=<N<=1024, even)
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *filetype*, (opt) can be 'FTYPE_C' or 'FTYPE_ASM', dfaults to FTYPE_C
%% Returns
% *RES*, the calculated result

%% Function Prototype
%  An Example:
%  OUT = FPU_DSP_runIFFT('complex', 2, 1024);
%  OUT = FPU_DSP_runIFFT('real', 4, 1024, 'TYPE_FLOAT', 'FTYPE_C');
%
function OUT = FPU_DSP_runIFFT(iffttype, radix, N, varargin)
%% Parse Arguments
close all
clc

assert(strcmp(iffttype,'complex')    || ...
    strcmp(iffttype,'real'),...
    ['First argument must be one of the following, \n',...
    '''complex''\n',...
    '''real''\n']);
assert((radix == 2) || (radix ==4), 'radix = 2 or 4');
% assert((N >=32) && (N<=1024) && (mod(N,2)==0), ' 32<=N<=1024\n');

nOptArgs = 2;
numvarargs = length(varargin);
if numvarargs > nOptArgs
    error('myfunc:TooManyInputs',...
        ['requires at most ',num2str(nOptArgs),' optional input(s)']);
end

% Assign optional argument
optArgs = {'TYPE_FLOAT', 'FTYPE_C'};

% Check contents of varargin: if empty skip
newVals = cellfun(@(x) ~isempty(x), varargin);

% now put these defaults into the valuesToUse cell array,
% and overwrite the ones specified in varargin.
optArgs(newVals) = varargin(newVals);
% or ...
% [optargs{1:numvarargs}] = varargin{:};

% Place optional args in memorable variable names
[precision, filetype] = optArgs{:};

if (strcmp(precision,'TYPE_FLOAT'))
    ftype = 'float';
elseif (strcmp(precision,'TYPE_DOUBLE'))
    ftype = 'long double';
else
    assert(0,'precision needs to be "TYPE_FLOAT" or "TYPE_DOUBLE"');
end
% Long, fixed-decimal format with 15 digits after the decimal point for double
% values, and 7 digits after the decimal point for single values.
format long
% Now that we have a legitimate function, we create an input/output
% file
assert((strcmp(filetype,'FTYPE_C') || ...
    strcmp(filetype,'FTYPE_ASM')),...
    'Argment needs to be ''FTYPE_C'' or ''FTYPE_ASM''\n');
if(strcmp(filetype, 'FTYPE_C'))
    TblFn = 'fft_tables.c';
    InFn  = strcat(strcat('i',iffttype(1),'fft',num2str(radix)),'Input.c');
    OutFn = strcat(strcat('i',iffttype(1),'fft',num2str(radix)),'Output.c');
    ext = '.c';
else % FTYPE_ASM
    TblFn = 'fft_tables.asm';
    InFn  = strcat(strcat('i',iffttype(1),'fft',num2str(radix)),'Input.asm');
    OutFn = strcat(strcat('i',iffttype(1),'fft',num2str(radix)),'Output.asm');
    ext = '.asm';
end

%% Generate the twiddle factor tables (size 1024)
TBL_SIZE  = 1024;
[T, R] = FPU_DSP_genTableFFT(TBL_SIZE, precision, TblFn);

%% The Input Signal
if(strcmp(iffttype,'complex'))
    b_complexOutput = true;
else %(strcmp(iffttype,'real'))
    b_complexOutput = false;
end
% Get the sampling rate from the user
Fs = input('Sampling Rate (Hz) : ');
% Generate the input signal from n_sines sines
n_sines = input('Enter number of sines: ');
Fmpy = randi([2 25], n_sines, 1);
Ampy = randi([1 1], n_sines, 1);
% Pmpy = randi([1 8], n_sines, 1);
% <<VC151019 DEBUG-> 
% IN = ones(N,1); 
%   VC151019>>
% <<VC151113 DEBUG-> 
%   n = 0 : N-1;
%   IN = cos(2*pi*0.1*n)+1i.*sin(2*pi*0.1*n);
%   VC151113>>
IN = zeros(N,1);
for  i = 1: n_sines
    % Commented the phase offet attribute of the system object
    % 'PhaseOffset', pi/Pmpy(i),...
    Signal = dsp.SineWave('SampleRate', Fs,...
        'Amplitude', Ampy(i),...
        'Frequency', Fs/Fmpy(i),...
        'ComplexOutput', b_complexOutput,...
        'SamplesPerFrame', N);
    IN = IN + step(Signal);
end
% Take the MATLAB FFT of the input
% Also make a copy of the input before bit-reverse ordering (debugging)
IN                = fft(IN); % Note if IN is real, the fft will take the 
                           % imaginary points to be 0. You do not have to
                           % manually add in zeros
TEMP              = ifft(IN); 
if (strcmp(iffttype,'complex'))
    GOLD(1:2:2*N-1,1) = real(TEMP);
    GOLD(2:2:2*N,1)   = imag(TEMP);
elseif (strcmp(iffttype,'real'))
    GOLD = TEMP;
end
% plot the input signal
figure(1),
subplot(3,2,1), plot(real(TEMP)), legend('Input Signal(real) from MATLAB IFFT');
subplot(3,2,2), plot(imag(TEMP)), legend('Input Signal(imag) from MATLAB IFFT');
subplot(3,2,3), plot(abs(IN)), legend('FFT(MATLAB)');
clear TEMP i;

%% The bit reversal of the input

% Rearrange the input in a sequential order Re, Im, Re, Im ... 
IN2(1:2:2*N-1,1) = real(IN);
IN2(2:2:2*N,1)   = imag(IN);
Ni               = length(IN2);
%% Running the FFT
if (strcmp(iffttype,'complex'))
    TEMP             = bitrevorder(IN);
    IN(1:2:2*N-1,1)  = real(TEMP);
    IN(2:2:2*N,1)    = imag(TEMP);
    disp('Complex IFFT');
    if(radix==2)
        OUT          = FPU_DSP_runRadix2ICFFT(N, IN, T, TBL_SIZE);
    elseif (radix==4)
        OUT          = FPU_DSP_runRadix4ICFFT(N, IN, T, TBL_SIZE);
    else
        assert(0,'Radix is incorrect');
    end
    TEMP             = OUT(1:2:2*N-1,1) + 1i * OUT(2:2:2*N,1);
elseif (strcmp(iffttype,'real'))
    disp('Real IFFT');
    % "Pack" the input to the complex N/2 point IFFT to get the original
    % signal
    TEMP             = FPU_DSP_pack(N, IN2, T, TBL_SIZE);
    IN               = TEMP(1:2:N-1,1)+1i.*TEMP(2:2:N,1);
    TEMP             = bitrevorder(IN);
    IN(1:2:N-1,1)    = real(TEMP);
    IN(2:2:N,1)      = imag(TEMP);
    % Run a complex FFT while treaing the real input as an N/2 point
    % complex vector
    if(radix==2)
        OUT          = FPU_DSP_runRadix2ICFFT(N/2, IN, T, TBL_SIZE);
    elseif (radix==4)
        OUT          = FPU_DSP_runRadix4ICFFT(N/2, IN, T, TBL_SIZE);
    else
        assert(0,'Radix is incorrect');
    end
    TEMP             = OUT;
else
    assert(0,'Problem with the first argument\n');
end

%Set the size of the output vector
No = length(OUT);
%Calculate the error (absolute) between the expected and result
ERR = abs(OUT - GOLD);

% plot the ouput signal
figure(1),
subplot(3,2,4), plot(real(TEMP)), legend('IFFT Real(Routine)');
subplot(3,2,5), plot(imag(TEMP)), legend('IFFT Imag(Routine)');
subplot(3,2,6), stem(ERR), legend('Error between FFTs');
clear temp;

%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',InFn,'\n']);
    fprintf(fid,[';;! \\brief  Input Vector (',num2str(N),') \n']);
    fprintf(fid,';;! \\author Vishal Coelho \n');
    fprintf(fid,[';;! \\date   ',date,'\n;;! \n;;\n']);
    fprintf(fid,';;  Group:\t\t\tC2000\n');
    fprintf(fid,';;  Target Family:\t$DEVICE$\n;;\n');
    fprintf(fid,[';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,';; ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,';;\n');
    fprintf(fid,';;\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    fprintf(fid,'\t.def\t_test_input\n');
    fprintf(fid,'\n');
    fprintf(fid,'\t.sect\t".data"\n');
    fprintf(fid,'\n');
    % Start the vector
    fprintf(fid, '_test_input:\n');
    if (strcmp(precision,'TYPE_FLOAT'))
        STR = sprintf('\t.float\t%15.12f, %15.12f, %15.12f, %15.12f \n',IN2);
    else
        STR = sprintf('\t.xldouble\t%15.12f, %15.12f, %15.12f, %15.12f \n',IN2);
    end
    fprintf(fid,STR);
    fprintf(fid,'\n;; End of File\n');
    fclose(fid);
end
if (~strcmp(OutFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(OutFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',OutFn,'\n']);
    fprintf(fid,[';;! \\brief  Output Vector (',num2str(N),') \n']);
    fprintf(fid,';;! \\author Vishal Coelho \n');
    fprintf(fid,[';;! \\date   ',date,'\n;;! \n;;\n']);
    fprintf(fid,';;  Group:\t\t\tC2000\n');
    fprintf(fid,';;  Target Family:\tF2837x\n;;\n');
    fprintf(fid,[';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,';; ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,';;\n');
    fprintf(fid,';;\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    fprintf(fid,'\t.def\t_test_golden\n');
    fprintf(fid,'\n');
    fprintf(fid,'\t.sect\t".econst"\n');
    fprintf(fid,'\n');
    % Start the vector
    fprintf(fid, '_test_golden:\n');
    if (strcmp(precision,'TYPE_FLOAT'))
        STR = sprintf('\t.float\t%15.12f, %15.12f, %15.12f, %15.12f \n',OUT);
    else
        STR = sprintf('\t.xldouble\t%15.12f, %15.12f, %15.12f, %15.12f \n',OUT);
    end
    fprintf(fid,STR);
    fprintf(fid,'\n;; End of File\n');
    fclose(fid);
end
%% Formatted print to .c file
HEAD_string = ['//',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = ['//',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.c'))
    fid = fopen(InFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,['//! \\file ',InFn,'\n']);
    fprintf(fid,['//! \\brief  Input Vector (',num2str(N),') \n']);
    fprintf(fid,'//! \\author Vishal Coelho \n');
    fprintf(fid,['//! \\date   ',date,'\n//! \n//\n']);
    fprintf(fid,'//  Group:\t\t\tC2000\n');
    fprintf(fid,'//  Target Family:\t$DEVICE$\n//\n');
    fprintf(fid,['// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,'// ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'//\n');
    fprintf(fid,'//\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    % Start the vector
    fprintf(fid, [ftype,' test_input[',num2str(Ni),...
        '] = {\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        STR = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',IN2);
    else
        STR = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',IN2);
    end
    fprintf(fid,STR);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end
if (~strcmp(OutFn,'NULL') && strcmp(ext,'.c'))
    fid = fopen(OutFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,['//! \\file ',OutFn,'\n']);
    fprintf(fid,['//! \\brief  Ouput Vector (',num2str(N),') \n']);
    fprintf(fid,'//! \\author Vishal Coelho \n');
    fprintf(fid,['//! \\date   ',date,'\n//! \n//\n']);
    fprintf(fid,'//  Group:\t\t\tC2000\n');
    fprintf(fid,'//  Target Family:\t$DEVICE$\n//\n');
    fprintf(fid,['// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,'// ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'//\n');
    fprintf(fid,'//\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    % Start the vector
    fprintf(fid, ['const ',ftype,' test_golden[',num2str(No),...
        '] = {\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        STR = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',OUT);
    else
        STR = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',OUT);
    end
    fprintf(fid,STR);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end
end

% End of file
