%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate the CORDIC lookup tables
% \author Vishal Coelho
% \date   11/01/2016
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% CORDIC Table Generation Function
%  This function generates the CORDIC table. 
%
% =============================================================================
% DATE       |      |
% =============================================================================
% 12/21/2016 | V.C. | Although this script will generate 64 entries for the
%            |      | scaleTable, the assembly table that is packaged under
%            |      | c28\source\fpu64 has a single entry 
%            |      |       IQ61(1/sqrt(1 + 2^(-2* 63)))
%            |      | the scale values dont change after the 26th entry and
%            |      | its unlikely will use this for less than 26
%            |      | iterations anyway so its an acceptable tradeoff
% =============================================================================
%% Required Parameters
% * *N*, desired size of the lookup table
%
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *filename*, (opt) name of c or assembly file to write the table to. This is
%         an optional argument
% The filenames can only have a .asm or .c extension. Note that in the case
% of assembly, the table is generated in IQ format where the fractional
% portion is 2 less than the chosen bit format. For example, if the user
% choose TYPE_FLOAT and assembly file generation, the table is written in
% IQ30 format. For TYPE_DOUBLE the output is written in IQ62 format.
%
%% Returns
% *A*, the table of arctans of negative powers of 2
% *S*, the table of scaling factors

%% Function Prototype
%  An Example: Generate a 64 entry table
%
% [A, S] = FPU_FastRTS_genCORDICTable(64,  'TYPE_FLOAT',
%  'FPU_FastRTS_cordicTable.asm')
%
function [ATANFACTOR, SCALEFACTOR] = FPU_FastRTS_genCORDICTable(N, varargin)

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
    if(strcmp(ext,'.c'))
        ftype = 'long long';
    else %.asm
        assert(N <= 32, 'N <= 32 for single precision assembly table');
        QBITS = 29;
        ftype = 'long';
    end
elseif (strcmp(precision,'TYPE_DOUBLE'))
    
    if(strcmp(ext,'.c'))
        ftype = 'long long';
    else %.asm
        assert(N <= 64, 'N <= 64 for double precision assembly table');
        QBITS = 61;
        ftype = 'long';
    end
else
    assert(0,'precision needs to be "TYPE_FLOAT" or "TYPE_DOUBLE"');
end
%% Table Generation (Double-Precision)
format long
N_a = N;
N_s = N; SCALEFACTOR = zeros(1, N);
if (strcmp(precision,'TYPE_FLOAT'))
    ATANFACTOR  = single(zeros(1, N));
    SCALEFACTOR = single(zeros(1, N));
elseif (strcmp(precision,'TYPE_DOUBLE'))
    ATANFACTOR  = zeros(1, N);
    SCALEFACTOR = zeros(1, N);
else
    assert(0,'precision needs to be "TYPE_FLOAT" or "TYPE_DOUBLE"');
end
for i = 0 : N-1
    k = i + 1;
    if (strcmp(precision,'TYPE_FLOAT'))
        ATANFACTOR(k) = single(atan(2^-i));
        SCALEFACTOR(k) = single(1/sqrt(1 + 2^(-2*i)));
        expressable_limit = realmin('single');
    elseif (strcmp(precision,'TYPE_DOUBLE'))
        ATANFACTOR(k) = atan(2^-i);
        SCALEFACTOR(k) = 1/sqrt(1 + 2^(-2*i));
        expressable_limit = realmin('double');
    else
        assert(0,'precision needs to be "TYPE_FLOAT" or "TYPE_DOUBLE"');
    end
    % Get the product of previous scale factors
    if(k > 1)
        SCALEFACTOR(k) = SCALEFACTOR(k) * SCALEFACTOR(k - 1);
    end
    
    if ATANFACTOR(k) < expressable_limit
        N_a = i; %stop processing here
    end
    if SCALEFACTOR(k) < expressable_limit
        N_s = i; %stop processing here
    end
end

%% Formatted print to .asm file
if (~strcmp(filename,'NULL') && strcmp(ext,'.asm'))
    HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(filename,'w');
    fprintf(fid,[HEAD_string                                      ,...
        ';;! \\file %s \n'                                        ,...
        ';;! \\brief  CORDIC Tables (%s) \n'                      ,...
        ';;! \\author Vishal Coelho \n'                           ,...
        ';;! \\date   %s\n'                                       ,...
        ';;! \n;;\n'                                              ,...
        ';;  Group:\t\t\tC2000\n'                                 ,...
        ';;  Target Family:\t$DEVICE$\n;;\n'                      ,...
        ';; Copyright (C) $YEAR$ Texas Instruments Incorporated'  ,...
        '- http://www.ti.com/ \n'                                 ,...
        ';; ALL RIGHTS RESERVED\n'                                ,...
        HEAD_string                                               ,...
        ';; \n'                         ,...
        ';; \n'               ,...
        HEAD_string                                               ,...
        '\n'                                                      ,...
        '\t.def\t_CORDIC_F64_atanTable\n'                           ,...
        '\t.def\t_CORDIC_F64_atanTableEnd\n'                        ,...
        '\n'                                                      ,...
        '\t.sect\t"FPUmathTables"\n'                              ,...
        '\t.align\t2\n'                                           ,...
        '_CORDIC_F64_atanTable:\n'], filename, num2str(N), date);
    % Start the Atan Table
    for i = 1 : N_a
        n = i - 1;
        if(strcmp(precision, 'TYPE_FLOAT'))
            S = sprintf('\t.%s\t0x%08X   ; IQ%d(arctan(2^-%3d)) \n',...
                ftype, uint32(ATANFACTOR(i)*2^QBITS), QBITS, n);
        else %precision == 'TYPE_DOUBLE'
            S = sprintf('\t.%s\t0x%08X, 0x%08X  ; IQ%d(arctan(2^-%3d)) \n',...
                ftype,...
                uint32(bitand(uint64(ATANFACTOR(i)*2^QBITS),4294967295)),...
                uint32(bitshift(uint64(ATANFACTOR(i)*2^QBITS), -32)),...
                QBITS, n);
        end
        fprintf(fid,S);
    end
    
    % End the Atan Table and start the scale table
    fprintf(fid, ['_CORDIC_F64_atanTableEnd:\n'                     ,...
        '\n'                                                      ,...
        '\t.def\t_CORDIC_F64_scaleTable\n'                           ,...
        '\t.def\t_CORDIC_F64_scaleTableEnd\n'                        ,...
        '\t.sect\t"FPUmathTables"\n'                              ,...
        '\t.align\t2\n'                                           ,...
        '_CORDIC_F64_scaleTable:\n']);
    for i = 1 : N_s
        n = i - 1;
        if(strcmp(precision, 'TYPE_FLOAT'))
            S = sprintf('\t.%s\t0x%08X    ; IQ%d(1/sqrt(1 + 2^(-2*%3d))) \n',...
                ftype, uint32(SCALEFACTOR(i)*2^QBITS), QBITS, n);
        else %precision == 'TYPE_DOUBLE'
            S = sprintf('\t.%s\t0x%08X, 0x%08X   ; IQ%d(1/sqrt(1 + 2^(-2*%3d)))\n',...
                ftype,...
                uint32(bitand(uint64(SCALEFACTOR(i)*2^QBITS),4294967295)),...
                uint32(bitshift(uint64(SCALEFACTOR(i)*2^QBITS), -32)),...
                QBITS, n);
        end
        fprintf(fid,S);
    end
    % End the Table
    fprintf(fid, '_CORDIC_F64_scaleTableEnd:\n\n');
        
    if(strcmp(precision, 'TYPE_FLOAT'))
        S = sprintf(['\t.def\t_CORDIC_F32_PI_O_2\n',...
            '_CORDIC_F32_PI_O_2:\n\t.%s\t0x%08X \n',...
            '\t.def\t_CORDIC_F32_PI\n',...
            '_CORDIC_F32_PI:\n\t.%s\t0x%08X \n',...
            '\t.def\t_CORDIC_F32_3PI_O_2\n',...
            '_CORDIC_F32_3PI_O_2:\n\t.%s\t0x%08X \n',...
            '\t.def\t_CORDIC_F32_2PI\n',...
            '_CORDIC_F32_2PI:\n\t.%s\t0x%08X \n'],...
            ftype, single(pi/2), ftype, single(pi), ftype, single(3*(pi/2)),...
            ftype, single(2*pi));
    else %precision == 'TYPE_DOUBLE'
        PI = upper(num2hex(pi));
        PI_O_2 = upper(num2hex(pi/2));
        THREEPI_O_2 = upper(num2hex(3*(pi/2)));
        TWOPI = upper(num2hex(2*pi));
        S = sprintf(['\t.def\t_CORDIC_F64_PI_O_2\n',...
            '_CORDIC_F64_PI_O_2:\n\t.%s\t0x%s, 0x%s\n',...
            '\t.def\t_CORDIC_F64_PI\n',...
            '_CORDIC_F64_PI:\n\t.%s\t0x%s, 0x%s \n',...
            '\t.def\t_CORDIC_F64_3PI_O_2\n',...
            '_CORDIC_F64_3PI_O_2:\n\t.%s\t0x%s, 0x%s \n',...
            '\t.def\t_CORDIC_F64_2PI\n',...
            '_CORDIC_F64_2PI:\n\t.%s\t0x%s, 0x%s \n'],...
            ftype, PI_O_2(9:16), PI_O_2(1:8),...
            ftype, PI(9:16), PI(1:8),...
            ftype, THREEPI_O_2(9:16), THREEPI_O_2(1:8),...
            ftype, TWOPI(9:16), TWOPI(1:8));
    end
    fprintf(fid,S);
    fprintf(fid, '\n;; End of File\n');
    fclose(fid);
end

%% Formatted print to .c file
if (~strcmp(filename,'NULL') && strcmp(ext,'.c'))
    HEAD_string = ['//',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = ['//',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(filename,'w');
    fprintf(fid,[HEAD_string                                      ,...
        '//! \\file %s\n'                                         ,...
        '//! \\brief CORDIC Tables (%s) \n'                       ,...
        '//! \\author Vishal Coelho \n'                           ,...
        '//! \\date   %s\n//! \n//\n'                             ,...
        '//  Group:\t\t\tC2000\n'                                 ,...
        '//  Target Family:\t$DEVICE$\n//\n'                      ,...
        '// Copyright (C) $YEAR$ Texas Instruments Incorporated'  ,...
        '- http://www.ti.com/ \n'                                 ,...
        '// ALL RIGHTS RESERVED\n'                                ,...
        HEAD_string                                               ,...
        '\n'                         ,...
        '// \n'               ,...
        HEAD_string                                               ,...
        '\n'], filename, num2str(N), date);
    
    % Start the Atan Table
    fprintf(fid, ['//This table has ',num2str(N_a),' entries\n']);
    fprintf(fid, ['const ',ftype,' FastRTS_CORDIC_atanTbl[',num2str(N_a),...
        '] = {\n']);
    for i = 1 : N_a
        n = i - 1;
        if(strcmp(precision, 'TYPE_FLOAT'))
            S = sprintf(['\t0x%s,    //',...
                ' arctan(2^-%3d)\n'], num2hex(ATANFACTOR(i)), n);
        else %precision == 'TYPE_DOUBLE'
            S = sprintf(['\t0x%s,    //',...
                ' arctan(2^-%3d)\n'], num2hex(ATANFACTOR(i)), n);
        end
        
        fprintf(fid,S);
    end
    fprintf(fid, '}; \n\n');
    
    fprintf(fid, ['//This table has ',num2str(N_s),' entries\n']);
    fprintf(fid, ['const ',ftype,' FastRTS_CORDIC_scaleTbl[',num2str(N_s),...
        '] = {\n']);
    for i = 1 : N_s
        n = i - 1;
        if(strcmp(precision, 'TYPE_FLOAT'))
            S = sprintf(['\t0x%s,    //',...
                ' 1/sqrt(1 + 2^(-2*%3d))\n'], num2hex(SCALEFACTOR(i)), n);
        else %precision == 'TYPE_DOUBLE'
            S = sprintf(['\t0x%s,    //',...
                ' 1/sqrt(1 + 2^(-2*%3d))\n'], num2hex(SCALEFACTOR(i)), n);
        end
        
        fprintf(fid,S);
    end
    fprintf(fid, ['}; \n\n',...
        '\n// End of File\n']);
    fclose(fid);
end

%%
% End of file
