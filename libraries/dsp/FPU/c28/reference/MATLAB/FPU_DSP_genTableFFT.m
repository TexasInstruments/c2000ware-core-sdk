%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate a Sine/Cosine lookup table (double precision table) for
%         the complex FFT and separate tables for the alternate real FFT
%         implementation
% \author Vishal Coelho
% \date   10/19/2015
%+---------+--------------------------------------------------------------+
%| Date    |                 History                                      |
%+---------+--------------------------------------------------------------+
%| 06/16/16| Added code for the RFFT (alt) table generation               |
%| 08/22/16| - Assembly tables to be aligned to even boundary             |
%|         | - CFFT table to have 3*N/4 entries (not 3*N/4+1)             |
%+---------+--------------------------------------------------------------+
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% Sine/Cosine Table Generation Function
% <<VC160822: N/2+N/4+1-> N/2+N/4, 769->768>>
%  This function basically generates the sine of N/2 + N/4 points around
%  the unit circle. For example, if N = 1024, then this function will create
%  768 sine entries, where the first N/2 entries are the sines while the
%  last N/2 entries (offset by N/4) for the cosine
%
% $$\cos(\theta) = \sin(\pi+\theta)$$
%
%  On the unit circle, a positive 90 degree shift translates to the
%  N/4 th table entry
%
% For the alternate RFFT implementation, the twiddles for each stage of the
% FFT are generated. For example, for a 5 stage FFT we first generate two
% complex twiddles for the third (non-trivial) stage, 4 for stage 4, 8 for
% stage 5.
%
%% Required Parameters
% * *N*, desired size of the lookup table
%
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *filename*, (opt) name of assembly file to write the table to. This is
%         an optional argument
% The filenames can only have a .asm or .c extension
%
%% Returns
% *T*, the complex FFT table
% *R*, the real FFT table

%% Function Prototype
%  An Example: Generate a 512 Twiddle Factor Table (384 entries for the
%  complex FFT table, 508 for the real FFT)
%
%  FPU_DSP_genTableFFT(512,  'TYPE_FLOAT',
%  'FPU_DSP_twiddleFactorTable.asm')
%
function [T, R] = FPU_DSP_genTableFFT(N, varargin)

%% Parse Arguments
nOptArgs = 2;
numvarargs = length(varargin);
if numvarargs > nOptArgs
    error('myfunc:TooManyInputs',...
        ['requires at most ',num2str(nArgs),' optional input(s)']);
end

% Assign optional argument
optArgs = {'TYPE_FLOAT','NULL'};

% Check contents of varargin: if empty skip
newVals = cellfun(@(x) ~isempty(x), varargin);

% now put these defaults into the valuesToUse cell array,
% and overwrite the ones specified in varargin.
optArgs(newVals) = varargin(newVals);
% or ...
% [optargs{1:numvarargs}] = varargin{:};

% Place optional args in memorable variable names
[precision, filename] = optArgs{:};

% filename must have an asm or c extenstion
if (~strcmp(filename,'NULL'))
    [~,~,ext] = fileparts(filename);
    assert((strcmp(ext,'.asm') || strcmp(ext,'.c')), ['Filename needs to have',...
        ' an .asm or .c extension']);
end

if (strcmp(precision,'TYPE_FLOAT'))
    ftype = 'float';
elseif (strcmp(precision,'TYPE_DOUBLE'))
    if(strcmp(ext,'.c'))
        ftype = 'long double';
    else
        ftype = 'xldouble';
    end
else
    assert(0,'precision needs to be "TYPE_FLOAT" or "TYPE_DOUBLE"');
end
%% Table Generation (Double-Precision)
format long

% The complex FFT table
%<<VC160822: 2N/4 -> 3N/4-1>>
n = 0 : (3*N/4-1);
sizeT = 3*N/4;
T = sin((2*pi/N).*n);
figure;
plot(T);
title('Plot of the Sine/Cosine Table');
xlabel('Index'); ylabel('Amplitude');

% The real FFT table
sizeR = sum(2.^(((3:log2(N)) - 1)));
R = zeros(1,sizeR);

%% Formatted print to .asm file
if (~strcmp(filename,'NULL') && strcmp(ext,'.asm'))
    HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(filename,'w');
    fprintf(fid,[HEAD_string                                              ,...
        ';;! \\file %s \n'                                        ,...
        ';;! \\brief  Twiddle Factor Table (%s) \n'               ,...
        ';;! \\author Vishal Coelho \n'                           ,...
        ';;! \\date   %s\n'                                       ,...
        ';;! \n;;\n'                                              ,...
        ';;  Group:\t\t\tC2000\n'                                 ,...
        ';;  Target Family:\t$DEVICE$\n;;\n'                      ,...
        ';; Copyright (C) $YEAR$ Texas Instruments Incorporated'  ,...
        '- http://www.ti.com/ \n'                                 ,...
        ';; ALL RIGHTS RESERVED\n'                                ,...
        HEAD_string                                               ,...
        ';;\n'                         ,...
        ';;\n'               ,...
        HEAD_string                                               ,...
        '\n'                                                      ,...
        '\t.def\t_FPUfftTable\n'                                  ,...
        '\t.def\t_FPUfftTableEnd\n'                               ,...
        '\t.def\t_FPUrfftTable\n'                                 ,...
        '\t.def\t_FPUrfftTableEnd\n'                              ,...
        '\n'                                                      ,...
        '\t.sect\t"FPUfftTables"\n'                               ,...
        '\t.align\t2\n'                                           ,...
        '_FPUfftTable:\n'], filename, num2str(N), date );

    %<<VC160822: for i = 1 : 3*N/4+1 >>
    for i = 1 : 3*N/4
        n = i - 1;
        S = sprintf('\t.%s\t%16.13f\t; sin(2 * pi * %4d/%4d)\n',ftype, T(i),n,N);
        fprintf(fid,S);
    end
    % End the Cosine Table
    fprintf(fid,['_FPUfftTableEnd:\n\n']);
    
    % Start the RFFT table
    fprintf(fid,['\t.sect\t"FPUfftTables"\n'                       ,...
        '\t.align\t2\n'                                            ,...
        '_FPUrfftTable:\n']);
    i = 1;
    for s = 3 : log2(N) % the stage
        fprintf(fid, '\t\t\t\t\t\t\t\t; +---------Stage %2d--------+\n' , s);
        for t = 1 : 2^(s-2) % number of complex twiddles
            R(i)   = cos(t*2*pi/(2^s));
            fprintf(fid, '\t.xldouble\t%15.13f\t; | Cos(%3d * 2 * pi / %4d)|\n',...
                R(i), t, 2^s);
            R(i+1) = sin(t*2*pi/(2^s));
            fprintf(fid, '\t.xldouble\t%15.13f\t; | Sin(%3d * 2 * pi / %4d)|\n',...
                R(i+1), t, 2^s);
            i      = i + 2;
        end
    end
    fprintf(fid,['\t\t\t\t\t\t\t\t; +-------------------------+\n'          ,...
        '_FPUrfftTableEnd:\n\n'                                    ,...
        '\n;; End of File\n']);
    fclose(fid);
end

%% Formatted print to .c file
if (~strcmp(filename,'NULL') && strcmp(ext,'.c'))
    HEAD_string = ['//',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = ['//',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(filename,'w');
    fprintf(fid,[HEAD_string                                               ,...
        '//! \\file %s\n'                                         ,...
        '//! \\brief Twiddle Factor Table (%s) \n'                ,...
        '//! \\author Vishal Coelho \n'                           ,...
        '//! \\date   %s\n//! \n//\n'                             ,...
        '//  Group:\t\t\tC2000\n'                                 ,...
        '//  Target Family:\t$DEVICE$\n//\n'                      ,...
        '// Copyright (C) $YEAR$ Texas Instruments Incorporated'  ,...
        '- http://www.ti.com/ \n'                                 ,...
        '// ALL RIGHTS RESERVED\n'                                ,...
        HEAD_string                                               ,...
        '//\n'                         ,...
        '//\n'               ,...
        HEAD_string                                               ,...
        '\n'], filename, num2str(N), date);
    
    % Start the Combined Table
    fprintf(fid, ['//This table has ',num2str(sizeT),' entries\n'        ,...
        'const ',ftype,' DSP_twiddleFactorTbl[',num2str(sizeT) ,...
        '] = {\n']);
    for i = 1 : length(T)
        n = i - 1;
        if(strcmp(precision, 'TYPE_FLOAT'))
            S = sprintf('\t%16.13fF,\t// sin(2 * pi * %4d/%4d)\n',T(i),n,N);
        else %precision == 'TYPE_DOUBLE'
            S = sprintf('\t%16.13fL,\t// sin(2 * pi * %4d/%4d)\n',T(i),n,N);
        end
        
        fprintf(fid,S);
    end
    fprintf(fid,'}; \n\n');
    
    % Start the RFFT Table
    fprintf(fid, ['//This table has ',num2str(sizeR),' entries\n'        ,...
        'const ',ftype,' DSP_rfftTwiddleFactorTbl[',num2str(sizeR) ,...
        '] = {\n']);
    i = 1;
    for s = 3 : log2(N) % the stage
        fprintf(fid, '\t\t\t\t\t\t// +---------Stage %2d--------+\n' , s);
        for t = 1 : 2^(s-2) % number of complex twiddles
            R(i)   = cos(t*2*pi/(2^s));
            if(strcmp(precision, 'TYPE_FLOAT'))
                fprintf(fid, '\t%15.13fF,\t// | Cos(%3d * 2 * pi / %4d)|\n',...
                    R(i), t, 2^s);
                R(i+1) = sin(t*2*pi/(2^s));
                fprintf(fid, '\t%15.13fF,\t// | Sin(%3d * 2 * pi / %4d)|\n',...
                    R(i+1), t, 2^s);
            else
                fprintf(fid, '\t%15.13fL,\t// | Cos(%3d * 2 * pi / %4d)|\n',...
                    R(i), t, 2^s);
                R(i+1) = sin(t*2*pi/(2^s));
                fprintf(fid, '\t%15.13fL,\t// | Sin(%3d * 2 * pi / %4d)|\n',...
                    R(i+1), t, 2^s);
            end
            i      = i + 2;
        end
    end
    fprintf(fid, '\t\t\t\t\t\t// +-------------------------+\n');
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end

%%
% End of file

