%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate IIR Input/Ouput Vectors
% \author Vishal Coelho
% \date   10/13/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Infinite Impulse Response Filter
% 
%% Required Parameters
% * *filtertype*, must be one of the following
% # 'bandpass'
% # 'bandstop'
% # 'highpass'
% # 'lowpass'
% * *N* size of the input vector (32=<N<=1024, even)
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *filetype*, (opt) can be 'FTYPE_C' or 'FTYPE_ASM', dfaults to FTYPE_C
%% Returns
% *RES*, the calculated result

%% Function Prototype
%  An Example:
%  R = FPU_DSP_runIIRFilter('lowpass', 1024);
%  R = FPU_DSP_runIIRFilter('lowpass', 1024, 'TYPE_FLOAT', 'FTYPE_C');
%
function R = FPU_DSP_runIIRFilter(fn, N, varargin)
%% Parse Arguments
assert((N >=32) && (N<=1024) && (mod(N,2)==0), ' 32<=N<=1024\n');

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
estr = sprintf(['First argument must be one of the following, \n',...
    '''bandpass''\n',...
    '''bandstop''\n',...
    '''highpass''\n',...
    '''lowpass''\n',...
    ]);
assert(strcmp(fn,'bandpass')    || ...
    strcmp(fn,'bandstop')       || ...
    strcmp(fn,'highpass')       || ...
    strcmp(fn,'lowpass'),...
    estr);

% Now that we have a legitimate function, we create an input/output
% file
assert((strcmp(filetype,'FTYPE_C') || ...
    strcmp(filetype,'FTYPE_ASM')),...
    'Argment needs to be ''FTYPE_C'' or ''FTYPE_ASM''\n');
if(strcmp(filetype, 'FTYPE_C'))
    InFn = 'iirInput.c';
    OutFn = 'iirOutput.c';
    ext = '.c';
else % FTYPE_ASM
    InFn = 'iirInput.asm';
    OutFn = 'iirOutput.asm';
    ext = '.asm';
end

%% The Input Signal
% Get the sampling rate from the user
Fs = input('Sampling Rate (Hz) : ');
% Generate the input signal from 20 sines
Fmpy = randi([2 25], 20, 1);
Pmpy = randi([1 8], 20, 1);
IN = zeros(N,1);
for  i = 1: 20
    Signal = dsp.SineWave('SampleRate', Fs,...
        'Frequency', Fs/Fmpy(i),...
        'PhaseOffset', pi/Pmpy(i),...
        'SamplesPerFrame', N);
    IN = IN + step(Signal);
end
% plot the input signal
figure(1), 
subplot(2,2,1), plot(IN), legend('Input Signal');
subplot(2,2,2), plot(abs(fft(IN))), legend('FFT(Input Signal)');

%% The Filter
if (strcmp(fn,'bandpass'))
    disp('Bandpass Filter Design');
    str  = input(['Fst1(Hz),Fp1(Hz),Fp2(Hz),Fst2(Hz),',...
        'Ast1(dB),Ap(dB),Ast2(dB):'], 's');
    spec = sscanf(str, '%f');
    Fst1 = spec(1)/(Fs/2);
    Fp1  = spec(2)/(Fs/2);
    Fp2  = spec(3)/(Fs/2);
    Fst2 = spec(4)/(Fs/2);
    Ast1 = spec(5);
    Ap   = spec(6);
    Ast2 = spec(7);
    filtSpecObj = fdesign.bandpass('Fst1,Fp1,Fp2,Fst2,Ast1,Ap,Ast2',...
        Fst1,Fp1,Fp2,Fst2,Ast1,Ap,Ast2);
elseif (strcmp(fn,'bandstop'))
    disp('Bandstop Filter Design');
    str  = input(['Fp1(Hz),Fst1(Hz),Fst2(Hz),Fp2(Hz),Ap1(dB)',...
                 'Ast(dB),Ap2(dB): '], 's');
    spec = sscanf(str, '%f');
    Fp1  = spec(1)/(Fs/2);
    Fst1 = spec(2)/(Fs/2);
    Fst2 = spec(3)/(Fs/2);
    Fp2  = spec(4)/(Fs/2);
    Ap1  = spec(5);
    Ast  = spec(6);
    Ap2  = spec(7);
    filtSpecObj = fdesign.bandstop('Fp1,Fst1,Fst2,Fp2,Ap1,Ast,Ap2',...
        Fp1,Fst1,Fst2,Fp2,Ap1,Ast,Ap2);
elseif (strcmp(fn,'highpass'))
    disp('Highpass Filter Design');
    str  = input('Fst(Hz) Fp(Hz) Ast(dB) Ap(dB):', 's');
    spec = sscanf(str, '%f');
    Fst  = spec(1)/(Fs/2);
    Fp   = spec(2)/(Fs/2);
    Ast  = spec(3);
    Ap   = spec(4);
    filtSpecObj = fdesign.highpass('Fst,Fp,Ast,Ap',Fst,Fp,Ast,Ap);
elseif (strcmp(fn,'lowpass'))
    disp('Lowpass Filter Design');
    str = input('Fp(Hz) Fst(Hz) Ap(dB) Ast(dB):', 's');
    spec = sscanf(str, '%f');
    Fp  = spec(1)/(Fs/2);
    Fst = spec(2)/(Fs/2);
    Ap  = spec(3);
    Ast = spec(4);
    filtSpecObj = fdesign.lowpass('Fp,Fst,Ap,Ast',Fp,Fst,Ap,Ast);
else
    assert(0,'Problem with the first argument\n');
end
filtObj = design(filtSpecObj, 'IIR',...
    'FilterStructure', 'df2tsos');
fvtool(filtObj);
measure(filtObj)
[p , q] = size(filtObj.sosMatrix);
N2 = N + (p*q); %Set the input vector size
IN(N + 1 : N2) = filtObj.sosMatrix';
Ni = N2 + p; %Set the input vector size again
IN(N2 + 1: Ni) = filtObj.ScaleValues(1:p);
disp(['Num of SOS = ',num2str(p)]);
% Convolution
R = filter(filtObj, IN(1:N));
No  = length(R);

% plot the ouput signal
figure(1),
subplot(2,2,3), plot(R), legend('Ouput Signal');
subplot(2,2,4), plot(abs(fft(R))), legend('FFT(Ouput Signal)');


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
        S = sprintf('\t.float\t%15.12f, %15.12f, %15.12f, %15.12f \n',IN);
    else
        S = sprintf('\t.xldouble\t%15.12f, %15.12f, %15.12f, %15.12f \n',IN);
    end
    fprintf(fid,S);
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
        S = sprintf('\t.float\t%15.12f, %15.12f, %15.12f, %15.12f \n',R);
    else
        S = sprintf('\t.xldouble\t%15.12f, %15.12f, %15.12f, %15.12f \n',R);
    end
    fprintf(fid,S);
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
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',IN);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',IN);
    end
    fprintf(fid,S);
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
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',R);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',R);
    end
    fprintf(fid,S);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end
%%
% End of file
