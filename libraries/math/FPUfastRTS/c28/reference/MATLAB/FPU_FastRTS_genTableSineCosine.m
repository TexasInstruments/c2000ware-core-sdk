%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate a Sine/Cosine lookup table (double precision table)
% \author Vishal Coelho
% \date   08/13/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% Sine/Cosine Table Generation Function
%  This function basically generates the sine of N + N/4 + 1 points around the
%  unit circle. For example, if N = 512, then this function will create
%  641 sine entries, where the first N entries are the sines while the
%  last N entries (offset by N/4) for the cosine
%
% $$\cos(\theta) = \sin(\pi+\theta)$$
%
%  On the unit circle, a positive 90 degree shift translates to the
%  N/4 th table entry
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
% *T*, the table



%% Function Prototype
%  An Example: Generate a 512 sine/cosine table (640 entries)
%
%  FPU_FastRTS_genTableSineCosine(512,  'TYPE_FLOAT',
%  'FPU_FastRTS_SineCosineTable.asm')
%
function T = FPU_FastRTS_genTableSineCosine(N, varargin)

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
        itype = 'long long';
    else
        ftype = 'xldouble';
        itype = 'long';
    end
else
   assert(0,'precision needs to be "TYPE_FLOAT" or "TYPE_DOUBLE"'); 
end
%% Table Generation (Double-Precision)
format long
n = 0 : (N + N/4);
T = sin((2*pi/N).*n);
% MATLAB calculates sin(2*pi) as -2.449293598294706e-16, which is -0.00
% when printed to file. The negative sine causes issues on the embedded
% controller so we manually set this value to 0
T(N+1) = 0.0;
figure;
plot(T);
title('Plot of the Sine/Cosine Table');
xlabel('Index'); ylabel('Amplitude');
TBLSZ_O_TWOPI = N/(2*pi);
TWOPI_O_TBLSZ = (2*pi)/N;
COEFF1 =  1/factorial(2);
COEFF2 =  1/factorial(3);
COEFF3 =  1/factorial(4);
COEFF4 =  1/factorial(5);
TBLSZ_O_TWOPI_L = '0x6DC9C883';
TBLSZ_O_TWOPI_H = '0x40545F30';
TWOPI_O_TBLSZ_L = '0x54442D18';
TWOPI_O_TBLSZ_H = '0x3F8921FB';
COEFF1_L = '0x00000000';
COEFF1_H = '0x3FE00000';
COEFF2_L = '0x55555555';
COEFF2_H = '0x3FC55555';
COEFF3_L = '0x55555555';
COEFF3_H = '0x3FA55555';
COEFF4_L = '0x11111111';
COEFF4_H = '0x3F811111';

%% Formatted print to .asm file
if (~strcmp(filename,'NULL') && strcmp(ext,'.asm'))
    HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(filename,'w');
    fprintf(fid,[HEAD_string,...
            ';;! \\file ',filename,'\n',...
            ';;! \\brief  Sine/Cosine Lookup Table (',num2str(N),') \n',...
            ';;! \\author Vishal Coelho \n',...
            ';;! \\date   ',date,'\n;;! \n;;\n',...
            ';;  Group:\t\t\tC2000\n',...
            ';;  Target Family:\t$DEVICE$\n;;\n',...
            ';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
            '- http://www.ti.com/ \n',...
            ';; ALL RIGHTS RESERVED\n',...
            HEAD_string,...
            ';; \n',...
            ';; \n',...
            HEAD_string,...
            '\n',...
            '\t.def\t_FPUsinTable\n',...
            '\t.def\t_FPUcosTable\n',...
            '\t.def\t_FPUsinTableEnd\n',...
            '\t.def\t_FPUcosTableEnd\n',...
            '\t.def\t_FPUsincos_TABLE_SIZE_O_TWOPI\n',...
            '\t.def\t_FPUsincos_TWOPI_O_TABLE_SIZE\n',...
            '\t.def\t_FPUsincos_Coef1\n',...
            '\t.def\t_FPUsincos_Coef2\n',...
            '\t.def\t_FPUsincos_Coef3\n',...
            '\t.def\t_FPUsincos_Coef4\n',...
            '\n',...
            '\t.sect\t"FPUmathTables"\n',...
            '\n',...
            '; The following 24 words must lie on the same page for the\n',...
            '; DP addressing to be efficient\n',...
            '\t.page\n',...
            '; 512/(2*pi) = 512/6.283185307179586\n',...
            ';            = 81.487330863050417\n',...
            ';            = 0x40545f306dc9c883\n',...
            '_FPUsincos_TABLE_SIZE_O_TWOPI\t.', itype, '\t%s, %s\n',...
            '\n',...
            '; (2*pi)/512 = 0.012271846303085\n',...
            ';            = 0x3f8921fb54442d18\n',...
            '_FPUsincos_TWOPI_O_TABLE_SIZE\t.', itype, '\t%s, %s\n',...
            '\n',...
            '; 0.5 = 0x3fe0000000000000\n',...
            '_FPUsincos_Coef1\t\t\t\t.', itype, '\t%s, %s\n',...
            '; 0.166666666666667 = 0x3fc5555555555555\n',...
            '_FPUsincos_Coef2\t\t\t\t.', itype, '\t%s, %s\n',...
            '; 4.1666666666666e-2 = 0x3fa5555555555555\n',...
            '_FPUsincos_Coef3\t\t\t\t.', itype, '\t%s, %s\n',...
            '; 8.3333333333333e-3 = 0x3f81111111111111\n',...
            '_FPUsincos_Coef4\t\t\t\t.', itype, '\t%s, %s\n',...
            '\n'],...
            TBLSZ_O_TWOPI_L, TBLSZ_O_TWOPI_H,...
            TWOPI_O_TBLSZ_L, TWOPI_O_TBLSZ_H,...
            COEFF1_L, COEFF1_H, COEFF2_L, COEFF2_H,...
            COEFF3_L, COEFF3_H, COEFF4_L, COEFF4_H);
            
    % Start the Sine Table
    fprintf(fid, '_FPUsinTable:\n');
    for i = 1 : N/4
        n = i - 1;
        S = sprintf('\t.%s\t%16.13f\t; sin(2 * pi * %4d/%4d)\n',ftype, T(i),n,N);
        fprintf(fid,S);
    end
    
    % Start the Cosine Table at the N/4 th point
    fprintf(fid, '_FPUcosTable:\n');
    for i = N/4+1 : N+N/4+1
        n = i - 1;
        S = sprintf('\t.%s\t%16.13f\t; sin(2 * pi * %4d/%4d)\n',...
            ftype,T(i),n,N);
        fprintf(fid,S);
        % End the Sine Table N-1 element, since MATLAB starts at 1, the Nth
        % element.
        if(i == N)
            fprintf(fid, '_FPUsinTableEnd:\n');
        end
    end
    % End the Cosine Table
    fprintf(fid, '_FPUcosTableEnd:\n');
    fprintf(fid,'\n;; End of File\n');
    fclose(fid);
end

%% Formatted print to .c file
if (~strcmp(filename,'NULL') && strcmp(ext,'.c'))
    HEAD_string = ['//',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = ['//',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(filename,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,['//! \\file ',filename,'\n']);
    fprintf(fid,['//! \\brief  Sine/Cosine Lookup Table (',num2str(N),') \n']);
    fprintf(fid,'//! \\author Vishal Coelho \n');
    fprintf(fid,['//! \\date   ',date,'\n//! \n//\n']);
    fprintf(fid,'//  Group:\t\t\tC2000\n');
    fprintf(fid,'//  Target Family:\t$DEVICE$\n//\n');
    fprintf(fid,['// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,'// ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    fprintf(fid,'// \n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    % Start the Combined Table
    fprintf(fid, ['//This table has ',num2str(N+N/4+1),' entries\n']);
    fprintf(fid, ['const ',ftype,' FastRTS_SinCosTbl[',num2str(N+N/4+1),...
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
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end

%%
% End of file
