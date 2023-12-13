%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate FFT Input/Ouput Vectors
% \author Vishal Coelho
% \date   10/15/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Fast Fourier Transform
%
%% Required Parameters
% * *ffttype*, must be one of the following
% # 'real'
% # 'real_alt'
% # 'real_adc'
% # 'complex'
% * *radix*, must be one of the following
% # 2
% # 4
% the real_alt will do an N point FFT treating the imaginary portion as
% zero, while the real option will do an N/2 point complex FFT followed
% by the unpack function. The real_alt option is only available for
% radix 2. real_adc implements the real_alt version of the FFT with usigned
% short input data
% * *N* size of the input vector (32=<N<=1024, even)
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *filetype*, (opt) can be 'FTYPE_C' or 'FTYPE_ASM', dfaults to FTYPE_C
%% Returns
% *RES*, the calculated result

%% Function Prototype
%  An Example:
%  OUT = FPU_DSP_runFFT('complex', 2, 1024);
%  OUT = FPU_DSP_runFFT('real', 4, 1024, 'TYPE_FLOAT', 'FTYPE_C');
%
function OUT = FPU_DSP_runFFT(ffttype, radix, N, varargin)
%% Parse Arguments
close all
clc

assert(strcmp(ffttype,'complex')    || ...
    strcmp(ffttype,'real_alt')    || ...
    strcmp(ffttype,'real_adc')    || ...
    strcmp(ffttype,'real'),...
    ['First argument must be one of the following, \n',...
    '''complex''\n',...
    '''real_alt''\n',...
    '''real_adc''\n',...
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

% Now that we have a legitimate function, we create an input/output
% file
if(strcmp(ffttype,'real_alt') || strcmp(ffttype,'real_adc'))
    radix = 2; %only radix 2 algorithm available
end
assert((strcmp(filetype,'FTYPE_C') || ...
    strcmp(filetype,'FTYPE_ASM')),...
    'Argment needs to be ''FTYPE_C'' or ''FTYPE_ASM''\n');
if(strcmp(filetype, 'FTYPE_C'))
    TblFn = 'fft_tables.c';
    InFn  = strcat(strcat(ffttype(1),'fft',num2str(radix)),'Input.c');
    OutFn = strcat(strcat(ffttype(1),'fft',num2str(radix)),'Output.c');
    ext = '.c';
else % FTYPE_ASM
    TblFn = 'fft_tables.asm';
    InFn  = strcat(strcat(ffttype(1),'fft',num2str(radix)),'Input.asm');
    OutFn = strcat(strcat(ffttype(1),'fft',num2str(radix)),'Output.asm');
    ext = '.asm';
end

if (strcmp(precision,'TYPE_FLOAT'))
    ftype = 'float';
    sizeofType = 2;
elseif (strcmp(precision,'TYPE_DOUBLE'))
    sizeofType = 4;
    if(strcmp(ext,'.c'))
        ftype = 'long double';
    else
        ftype = 'xldouble';
    end
else
    assert(0,'precision needs to be "TYPE_FLOAT" or "TYPE_DOUBLE"');
end
% Long, fixed-decimal format with 15 digits after the decimal point for double
% values, and 7 digits after the decimal point for single values.
format long

%% Generate the twiddle factor tables (size 1024)
TBL_SIZE  = 1024;
ADC_BITS  = 12;
[T, R] = FPU_DSP_genTableFFT(TBL_SIZE, precision, TblFn);

%% The Input Signal
if(strcmp(ffttype,'complex'))
    b_complexOutput = true;
else %(strcmp(ffttype,'real'))
    b_complexOutput = false;
end
% Get the sampling rate from the user
Fs = input('Sampling Rate (Hz) : ');
% Generate the input signal from n_sines sines
n_sines = input('Enter number of sines: ');
Fmpy = randi([2 25], n_sines, 1);
Ampy = randi([10 20], n_sines, 1);
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
%
% Note if IN2 is real, the fft will take the
% imaginary points to be 0. You do not have to
% manually add in zeros
if(strcmp(ffttype,'real_adc'))
    IN = double(floor(IN + abs(min(IN))));
    TEMP              = fft(IN./(2^ADC_BITS - 1));
else
    TEMP              = fft(IN);
end

if(strcmp(ffttype,'real_alt') || strcmp(ffttype,'real_adc'))
    GOLD(1:N/2,1)   = real(TEMP(1:N/2));
    if strcmp(ffttype,'real_adc')
        GOLD(N/2+1,1)   = (sum(IN(1:2:N-1)) - sum(IN(2:2:N)))/(2^ADC_BITS - 1);
    else
        GOLD(N/2+1,1)   = sum(IN(1:2:N-1)) - sum(IN(2:2:N));
    end
    GOLD(N/2+2:N,1) = imag(TEMP(N/2:-1:2));
    
else
    GOLD(1:2:2*N-1,1) = real(TEMP);
    GOLD(2:2:2*N,1)   = imag(TEMP);
end

% plot the input signal
figure(1),
subplot(4,2,1), plot(real(IN)), legend('Input Signal(real)');
subplot(4,2,2), plot(imag(IN)), legend('Input Signal(imag)');
subplot(4,2,3), plot(abs(TEMP)), legend('FFT(MATLAB)');
clear TEMP i;

%% The bit reversal of the input

% Rearrange the input in a sequential order Re, Im, Re, Im ... for complex
% For real FFT treat the N point real input as an N/2 point complex data
if strcmp(ffttype,'complex')
    IN2(1:2:2*N-1,1) = real(IN);
    IN2(2:2:2*N,1)   = imag(IN);
    IN               = bitrevorder(IN);
    OUT(1:2:2*N-1,1) = real(IN);
    OUT(2:2:2*N,1)   = imag(IN);
    IN               = OUT;
elseif strcmp(ffttype,'real')
    IN2              = IN;
    %Treat the input as N/2 point complex before bit reversal
    TEMP             = IN(1:2:N-1,1)+1i.*IN(2:2:N,1);
    TEMP             = bitrevorder(TEMP);
    IN(1:2:N-1,1)    = real(TEMP);
    IN(2:2:N,1)      = imag(TEMP);
    clear TEMP;
else  % strcmp(ffttype,'real_alt') || strcmp(ffttype,'real_adc')
    IN2              = IN;
    IN               = bitrevorder(IN);
end
Ni                   = length(IN);

%% Running the FFT
if (strcmp(ffttype,'complex'))
    disp('Complex FFT');
    if(radix==2)
        OUT = FPU_DSP_runRadix2CFFT(N, IN, T, TBL_SIZE);
    elseif (radix==4)
        OUT = FPU_DSP_runRadix4CFFT(N, IN, T, TBL_SIZE);
    else
        assert(0,'Radix is incorrect');
    end
elseif (strcmp(ffttype,'real'))
    disp('Real FFT');
    % Run a complex FFT while treating the real input as an N/2 point
    % complex vector
    if(radix==2)
        TEMP = FPU_DSP_runRadix2CFFT(N/2, IN, T, TBL_SIZE);
    elseif (radix==4)
        TEMP = FPU_DSP_runRadix4CFFT(N/2, IN, T, TBL_SIZE);
    else
        assert(0,'Radix is incorrect');
    end
    % "Unpack" the output of the complex N/2 point FFT to get the real
    % spectrum (K = 0 to Fs/2 bins)
    OUT  = FPU_DSP_unpack(N, TEMP, T, TBL_SIZE);
elseif (strcmp(ffttype,'real_alt'))
    disp('Real (Alternate) FFT');
    % Run a real FFT while treating the imaginary part of the input as 0
    if(radix==2)
        OUT = FPU_DSP_runRadix2RFFT(N, IN, R, TBL_SIZE);
    else
        assert(0,'Radix must be 2');
    end
elseif (strcmp(ffttype,'real_adc'))
    disp('Real (Alternate) FFT with ADC input');
    % Run a real FFT while treating the imaginary part of the input as 0
    if(radix==2)
        OUT = FPU_DSP_runRadix2RFFT(N, IN./(2^ADC_BITS - 1), R, TBL_SIZE);
    else
        assert(0,'Radix must be 2');
    end
else
    assert(0,'Problem with the first argument\n');
end

%Calculate the error (absolute) between the expected and result
ERR = abs(OUT - GOLD);

% cast OUT as a complex variable and plot
if(strcmp(ffttype,'real_alt') || strcmp(ffttype,'real_adc'))
    temp(1)       = OUT(1) + 1i*0;
    temp(N/2+1)   = OUT(N/2+1) + 1i*0;
    temp(2:N/2)   = OUT(2:N/2) + 1i.*OUT(end:-1:N/2+2);
    temp(N/2+2:N) = conj(temp(N/2:-1:2));
else
    temp = OUT(1:2:2*N-1,1) + 1i * OUT(2:2:2*N,1);
end
% plot the ouput signal
figure(1),
subplot(4,2,4), plot(abs(temp)), legend('FFT(Routine)');
subplot(4,2,5), stem(ERR), legend('Error between FFTs');

%% Magnitude and Phase
% Now convert OUT to a complex format and calculate its magnitude
if(strcmp(ffttype,'real_alt') || strcmp(ffttype,'real_adc'))
    OUT(N+1 : 3*N/2 + 1,1) = abs(temp(1:(N/2+1)));
    subplot(4,2,6), plot(OUT(N+1 : 3*N/2 + 1)), legend('Magnitude');
    OUT(3*N/2 + 2 : 2*N+2) = angle(temp(1:(N/2+1)));
    subplot(4,2,7), plot(OUT(3*N/2 + 2 : 2*N+2)), legend('Phase');
else
    OUT(2*N+1 : 3*N,1) = abs(temp);
    subplot(4,2,6), plot(OUT(2*N+1 : 3*N)), legend('Magnitude');
    OUT(3*N+1 : 4*N,1) = angle(temp);
    subplot(4,2,7), plot(OUT(3*N+1 : 4*N)), legend('Phase');
end
%Set the size of the output vector
No = length(OUT);

clear temp;

%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,[HEAD_string,...
        ';;! \\file ',InFn,'\n',...
        ';;! \\brief  Input Vector (',num2str(N),') \n',...
        ';;! \\author Vishal Coelho \n',...
        ';;! \\date   ',date,'\n;;! \n;;\n',...
        ';;  Group:\t\t\tC2000\n',...
        ';;  Target Family:\t$DEVICE$\n;;\n',...
        ';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n',...
        ';; ALL RIGHTS RESERVED\n',...
        HEAD_string,...
        ';;\n',...
        ';;\n',...
        HEAD_string,...
        '\n',...
        '\t.def\t_test_input\n',...
        '\n',...
        '\t.sect\t".data"\n',...
        '\n']);
    % Start the vector
    fprintf(fid, '_test_input:\n');
    if strcmp(ffttype,'real_adc')
        STR = sprintf('\t.uword\t%7d, %7d, %7d, %7d, \n',IN2);
    elseif (strcmp(precision,'TYPE_FLOAT'))
        STR = sprintf('\t.float\t%17.12f, %17.12f, %17.12f, %17.12f \n',IN2);
    else
        STR = sprintf('\t.xldouble\t%17.12f, %17.12f, %17.12f, %17.12f \n',IN2);
    end
    fprintf(fid,STR);
    fprintf(fid,'\n;; End of File\n');
    fclose(fid);
end
if (~strcmp(OutFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(OutFn,'w');
    fprintf(fid,[HEAD_string,...
        ';;! \\file ',OutFn,'\n',...
        ';;! \\brief  Output Vector (',num2str(N),') \n',...
        ';;! \\author Vishal Coelho \n',...
        ';;! \\date   ',date,'\n;;! \n;;\n',...
        ';;  Group:\t\t\tC2000\n',...
        ';;  Target Family:\tF2837x\n;;\n',...
        ';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n',...
        ';; ALL RIGHTS RESERVED\n',...
        HEAD_string,...
        ';;\n',...
        ';;\n',...
        HEAD_string,...
        '\n',...
        '\t.def\t_test_golden\n',...
        '\n',...
        '\t.sect\t".econst"\n',...
        '\n']);
    % Start the vector
    fprintf(fid, '_test_golden:\n');
    if (strcmp(precision,'TYPE_FLOAT'))
        STR = sprintf('\t.float\t%17.12f, %17.12f, %17.12f, %17.12f \n',OUT);
    else
        STR = sprintf('\t.xldouble\t%17.12f, %17.12f, %17.12f, %17.12f \n',OUT);
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
    fprintf(fid,[HEAD_string,...
        '//! \\file ',InFn,'\n',...
        '//! \\brief  Input Vector (',num2str(N),') \n',...
        '//! \\author Vishal Coelho \n',...
        '//! \\date   ',date,'\n//! \n//\n',...
        '//  Group:\t\t\tC2000\n',...
        '//  Target Family:\t$DEVICE$\n//\n',...
        '// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n',...
        '// ALL RIGHTS RESERVED\n',...
        HEAD_string,...
        '//\n',...
        '//\n',...
        HEAD_string,...
        '\n']);
    
    % Start the vector
    if strcmp(ffttype,'real_adc')
        fprintf(fid, [...
            '// Matrix is ', num2str(sizeofType),' times its required size',...
            'as it will be used to store\n',...
            '// ',num2str(Ni),' ', ftype,'s at a later point \n',...
            'uint16_t test_input[',num2str(2*Ni),...
            '] = {\n']);
        STR = sprintf('\t%7d, %7d, %7d, %7d, \n',IN2);
    else
        fprintf(fid, [ftype,' test_input[',num2str(Ni),...
            '] = {\n']);
        if(strcmp(precision, 'TYPE_FLOAT'))
            STR = sprintf('\t%17.12fF, %17.12fF, %17.12fF, %17.12fF, \n',IN2);
        else
            STR = sprintf('\t%17.12fL, %17.12fL, %17.12fL, %17.12fL, \n',IN2);
        end
    end
    fprintf(fid,STR);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end
if (~strcmp(OutFn,'NULL') && strcmp(ext,'.c'))
    fid = fopen(OutFn,'w');
    fprintf(fid,[HEAD_string,...
        '//! \\file ',OutFn,'\n',...
        '//! \\brief  Ouput Vector (',num2str(N),') \n',...
        '//! \\author Vishal Coelho \n',...
        '//! \\date   ',date,'\n//! \n//\n',...
        '//  Group:\t\t\tC2000\n',...
        '//  Target Family:\t$DEVICE$\n//\n',...
        '// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n',...
        '// ALL RIGHTS RESERVED\n',...
        HEAD_string,...
        '//\n',...
        '//\n',...
        HEAD_string,...
        '\n']);
    
    % Start the vector
    fprintf(fid, ['const ',ftype,' test_golden[',num2str(No),...
        '] = {\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        STR = sprintf('\t%17.12fF, %17.12fF, %17.12fF, %17.12fF, \n',OUT);
    else
        STR = sprintf('\t%17.12fL, %17.12fL, %17.12fL, %17.12fL, \n',OUT);
    end
    fprintf(fid,STR);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end
end

% End of file
