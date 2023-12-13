%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate a natural log lookup table (double precision table)
% \author Vishal Coelho
% \date   01/24/2017
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% Log Table Generation Function
%  This function generates the Log coefficients
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
%  An Example: Generate a 32 3-tuple Log table (32*3 entries)
%
%  FPU_FastRTS_genTableLog(32,  'TYPE_FLOAT', 'FPU_FastRTS_LogTable.asm')
%
function T = FPU_FastRTS_genTableLog(N, varargin)

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
    itype = 'long';
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

FPULOG2     = log(2);
FPUINVLOG10 = 1/log(10);
if (strcmp(precision,'TYPE_FLOAT'))
    FPUEXPBIAS  = 127.0;
    FPULOG_TABLE_MASK1 = '0x3FFFFFFF';
    FPULOG_TABLE_MASK2 = '0x3F800000';
else %precision =='TYPE_DOUBLE'
    FPUEXPBIAS  = 1023.0;
    FPULOG_TABLE_MASK1   = '0x3FFFFFFFFFFFFFFF';
    FPULOG_TABLE_MASK1_L = '0xFFFFFFFF';
    FPULOG_TABLE_MASK1_H = '0x3FFFFFFF';
    FPULOG_TABLE_MASK2   = '0x3FF0000000000000';
    FPULOG_TABLE_MASK2_L = '0x00000000';
    FPULOG_TABLE_MASK2_H = '0x3FF00000';
end

% The domain for the lookup table is the range of permissible
% mantissa values, 1.0 to ~2.0
x0    = 0.0;
x1    = 1/(2*N); % x1    = 1/64 * 0.5
x2    = 1/N;	   % x2    = 1/64
xstep = 1/N;	   % xstep = 1/64
a0    = zeros(1,N);
a1    = zeros(1,N);
a2    = zeros(1,N);
x_0   = zeros(1,N);
x_1   = zeros(1,N);
x_2   = zeros(1,N);
t     = zeros(1,N);
T     = zeros(1, (N+1)*3);
j     = 1;
for i = 0:N
    k   = i+1;
    c12 = x0;
    c13 = x0*x0;
    b1  = log(1+x0);
    c22 = x1;
    c23 = x1*x1;
    b2  = log(1+x1);
    c32 = x2;
    c33 = x2*x2;
    b3  = log(1+x2);
    
    a2(k) = ((b2-b1)*(c32-c12) - (b3-b1)*(c22-c12))/((c13-c33)*(c22-c12) - (c13-c23)*(c32-c12));
    a1(k) = ((b3-b1) + a2(k)*(c13-c33))/(c32-c12);
    a0(k) = b1 - a1(k)*c12 - a2(k)*c13;
    x_0(k)= x0;
    x_1(k)= x1;
    x_2(k)= x2;
    x0    = x0 + xstep;
    x1    = x1 + xstep;
    x2    = x2 + xstep;
    T(j)  = a0(k);
    T(j+1)= a1(k);
    T(j+2)= a2(k);
    j     = j + 3;
end

figure;
subplot(2,2,1), plot(x_0,a0,'-r'),title('a0'),
subplot(2,2,2),plot(x_1,a1,'--b'),title('a1'),
subplot(2,2,3),plot(x_2,a2,'og'),title('a2'),
xlabel('Index'); ylabel('Amplitude');

%% Formatted print to .asm file
if (~strcmp(filename,'NULL') && strcmp(ext,'.asm'))
    HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(filename,'w');
    fprintf(fid,[HEAD_string,...
        ';;! \\file ',filename,'\n',...
        ';;! \\brief  Natural Logarithm Lookup Table (',num2str(N),') \n',...
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
        '\t.def\t_FPULOG2\n',...
        '\t.def\t_FPUINVLOG10\n',...
        '\t.def\t_FPUEXPBIAS\n',...
        '\t.def\t_FPULOG_TABLE_MASK1\n',...
        '\t.def\t_FPULOG_TABLE_MASK2\n',...
        '\t.def\t_FPUlogTable\n',...
        '\t.def\t_FPUlogTableEnd\n',...
        '\n',...
        '\t.sect\t"FPUmathTables"\n',...
        '\n',...
        '_FPULOG2:\t\t\t\t.',ftype,'\t%16.13f\n',...
        '_FPUINVLOG10:\t\t\t.',ftype,'\t%16.13f\n',...
        '_FPUEXPBIAS:\t\t\t.',ftype,'\t%16.13f\n'],...
         FPULOG2, FPUINVLOG10, FPUEXPBIAS);
    if(strcmp(precision, 'TYPE_FLOAT'))
        fprintf(fid,...
            ['_FPULOG_TABLE_MASK1:\t.',itype,'\t%s\n',...
            '_FPULOG_TABLE_MASK2:\t.',itype,'\t%s\n',...
            '\n',...
            '_FPUlogTable:\n'],...
            FPULOG_TABLE_MASK1, FPULOG_TABLE_MASK2);
     else %precision == 'TYPE_DOUBLE'
         fprintf(fid,...
             ['_FPULOG_TABLE_MASK1:\t.',itype,'\t%s, %s\n',...
             '_FPULOG_TABLE_MASK2:\t.',itype,'\t%s, %s\n',...
             '\n',...
             '_FPUlogTable:\n'],...
             FPULOG_TABLE_MASK1_L, FPULOG_TABLE_MASK1_H,...
             FPULOG_TABLE_MASK2_L, FPULOG_TABLE_MASK2_H);
    end
    
    for i = 1 : N+1
        n = i - 1;
        S = sprintf('\t.%s\t%16.13f, %16.13f, %16.13f ; %3d -> a0 a1 a2 \n',...
            ftype,a0(i), a1(i), a2(i), n);
        fprintf(fid,S);
    end
    
    % End the Table
    fprintf(fid, ['_FPUlogTableEnd:\n',...
                  '\n;; End of File\n']);
    fclose(fid);
end

%% Formatted print to .c file
if (~strcmp(filename,'NULL') && strcmp(ext,'.c'))
    HEAD_string = ['//',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = ['//',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(filename,'w');
    fprintf(fid,[HEAD_string,...
        '//! \\file ',filename,'\n',...
        '//! \\brief  Natural Logarithm Lookup Table (',num2str(N),') \n',...
        '//! \\author Vishal Coelho \n',...
        '//! \\date   ',date,'\n//! \n//\n',...
        '//  Group:\t\t\tC2000\n',...
        '//  Target Family:\t$DEVICE$\n//\n',...
        '// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n',...
        '// ALL RIGHTS RESERVED\n',...
        HEAD_string,...
        '\n',...
        '// \n',...
        HEAD_string,...
        '\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        fprintf(fid,...
            ['const ', ftype,' FPULOG2             = %16.13fF; \n',...
            'const ', ftype, ' FPUINVLOG10         = %16.13fF; \n',...
            'const ', ftype, ' FPUEXPBIAS          = %16.13fF; \n',...
            'const ', itype, ' FPULOG_TABLE_MASK1  = %s; \n',...
            'const ', itype, ' FPULOG_TABLE_MASK2  = %s; \n',...
            ],FPULOG2,...
            FPUINVLOG10, FPUEXPBIAS,...
            FPULOG_TABLE_MASK1, FPULOG_TABLE_MASK2);
    else %precision == 'TYPE_DOUBLE'
        fprintf(fid,...
            ['const ', ftype,' FPULOG2             = %16.13fL; \n',...
            'const ', ftype, ' FPUINVLOG10         = %16.13fL; \n',...
            'const ', ftype, ' FPUEXPBIAS          = %16.13fL; \n',...
            'const ', itype, ' FPULOG_TABLE_MASK1  = %s; \n',...
            'const ', itype, ' FPULOG_TABLE_MASK2  = %s; \n',...
            ],FPULOG2,...
            FPUINVLOG10, FPUEXPBIAS,...
            FPULOG_TABLE_MASK1, FPULOG_TABLE_MASK2);
    end
    fprintf(fid, ['\n',...
        '//This table has ',num2str((N+1)*3),' entries\n',...
        'const ',ftype,' FastRTS_logTable[',num2str((N+1)*3),...
        '] = {\n']);
    for i = 1 : N+1
        n = i - 1;
        if(strcmp(precision, 'TYPE_FLOAT'))
            S = sprintf(['\t%16.13fF, \t%16.13fF, \t%16.13fF,//',...
                ' %3d -> a0 a1 a2\n'],a0(i),a1(i),a2(i),n);
        else %precision == 'TYPE_DOUBLE'
            S = sprintf(['\t%16.13fL, \t%16.13fL, \t%16.13fL,//',...
                ' %3d -> a0 a1 a2\n'],a0(i),a1(i),a2(i),n);
        end
        
        fprintf(fid,S);
    end
    fprintf(fid,['}; \n\n',...
                '\n// End of File\n']);
    fclose(fid);
end

%%
% End of file
