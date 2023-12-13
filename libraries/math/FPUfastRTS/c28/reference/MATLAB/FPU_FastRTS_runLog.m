
%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate Log Input/Ouput Vectors
% \author Vishal Coelho
% \date   01/25/2017
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Logarithm Algorithm
% This is a table lookup algorithm. The steps are as follows,
%
% * calculate the absolute of x, |x|
%
% * A floating point number is represented as X=[S]1.M*2^E where S is the 
%   sign bit, M the mantissa, and E the biased exponent. The natural
%   logarithm of such a number is given by
%
% $$log(X) = log(1.M) + E*log(2)$$
%
% * Separate the exponent of the input, store it as a float.
%
% * Separate the mantissa (1.M), and then the fractional portion Xm = M
%
% * Subtract the bias from the exponent and multiply by log(2)
%
% * Calculate log(1.M) using the polynomial approximation 
%
% $$log(1 + M) = a0 + M*(a1 + M*a2)$$
%
% * The result is $log(1+M) + E*log(2)$, where E is now the unbiased exponent
%
%% Required Parameters
% * *N* , the size of the input/output array
% * *SWP* , array indicating the desired input sweep, e.g. [1, 100].
%
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *Filename(table)*, name of file to write the table to. If defined it is
%    passed on to the genTable function
% * *Filename(input)*, name of file to write the input vector to
% * *Filename(output)*, name of file to write the output vector to
% The filenames can only have a .asm or .c extension
%
%% Returns
% *LOG*, the calculated logarithm
% *REF*, the reference logarithm (calculated using matlab in-built functions)
% *AERR*, Absolute error
% *RERR*, Relative error

%% Function Prototype
%  An Example: Generate a 512 logarithm input/output vector
%
%  [L,R,AE,RE] = FPU_FastRTS_runLog(512, [1,100], 'TYPE_FLOAT',
%  'logTable.asm', 'logInput.asm', 'logOutput.asm')
%
% or
%
%  [L,R,AE,RE] = FPU_FastRTS_runLog(512, [1,100], 'TYPE_FLOAT',
%  'logTable.c', 'logInput.c', 'logOutput.c')
%
function [LOG,REF,AERR,RERR] = FPU_FastRTS_runLog(N, SWP, varargin)
%% Parse Arguments
nOptArgs = 4;
numvarargs = length(varargin);
if numvarargs > nOptArgs
    error('myfunc:TooManyInputs',...
        ['requires at most ',num2str(nOptArgs),' optional input(s)']);
end

% Assign optional argument
optArgs = {'TYPE_FLOAT','NULL', 'NULL','NULL'};

% Check contents of varargin: if empty skip
newVals = cellfun(@(x) ~isempty(x), varargin);

% now put these defaults into the valuesToUse cell array,
% and overwrite the ones specified in varargin.
optArgs(newVals) = varargin(newVals);
% or ...
% [optargs{1:numvarargs}] = varargin{:};

% Place optional args in memorable variable names
[precision, TblFn, InFn, OutFn] = optArgs{:};

% filenames must have an asm or c extenstion
if (~strcmp(TblFn,'NULL'))
    [~,~,ext] = fileparts(TblFn);
    assert((strcmp(ext,'.asm') || strcmp(ext,'.c')), ['Filename needs to have',...
        ' an .asm or .c extension']);
end
if (~strcmp(InFn,'NULL'))
    [~,~,ext] = fileparts(InFn);
    assert((strcmp(ext,'.asm') || strcmp(ext,'.c')), ['Filename needs to have',...
        ' an .asm or .c extension']);
end
if (~strcmp(OutFn,'NULL'))
    [~,~,ext] = fileparts(OutFn);
    assert((strcmp(ext,'.asm') || strcmp(ext,'.c')), ['Filename needs to have',...
        'an .asm or .c extension']);
end
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

assert( N <= 1024 && N > 0, 'Valid values are between 1 and 1024');
assert( mod(N,2) == 0, 'N needs to be a power of 2');
SWP_s  = size(SWP);
assert((SWP_s(1) == 1 && SWP_s(2) == 2),...
    'SWP needs to be 1x2');
assert((min(SWP) >= 1), 'Values in the input need to be greater than 1');
TBL_SIZE = 32;

%% Generate the lookup table and the coefficients
if (~strcmp(TblFn,'NULL'))
    T = FPU_FastRTS_genTableLog(TBL_SIZE, precision, TblFn);
else
    T = FPU_FastRTS_genTableLog(TBL_SIZE);
end

figure;
plot(T,'-b'), title('Natural Log Lookup Table');
FPULOG2     = log(2);

%% Calculate the logarithm for the sweep range and plot the response
istep = (SWP(2)-SWP(1))/N;
x     = SWP(1);
RERR  = zeros(1,N);
AERR  = zeros(1,N);
REF   = zeros(1,N);
LOG   = zeros(1,N);
t     = zeros(1,N);
for i = 1 : N
    t(i) = x;
    % Calculate the Log for the current x
    x_a = abs(x);
    [f, e] = log2(x_a);
    x_exp_unbiased = e - 1;
    x_mantissa     = 2*f - 1; % remove the implicit 1
    log_exp        = x_exp_unbiased * FPULOG2;
    tbl_index      = floor(x_mantissa*TBL_SIZE)*3 + 1;
    A0             = T(tbl_index);
    A1             = T(tbl_index+1);
    A2             = T(tbl_index+2);
    log_1pmantissa = A0 + x_mantissa*(A1 + x_mantissa*A2);
    
    LOG(i) = log_1pmantissa + log_exp;
    REF(i) = log(x);
    AERR(i) = abs(REF(i) - LOG(i));
    RERR(i) = AERR(i)/max(abs(x), abs(REF(i)));
    x       = x + istep;
end
figure;
subplot(2,2,1), plot(t,LOG,'-b',t,REF,'--r'), legend('Table Lookup log',...
    'Reference MATLAB Log'), xlabel('x'), ylabel('log(x)'),
title('Log: Table Lookup'), grid on;
subplot(2,2,2), plot(t,AERR),xlabel('x'), ylabel('log(x)'),
title('Absolute Error'), grid on;
subplot(2,2,3), plot(t,RERR),xlabel('x'), ylabel('log(x)'),
title('Relative Error'), grid on;

%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,[HEAD_string                                    ,...
        ';;! \\file %s \n'                                      ,...
        ';;! \\brief  Log Input Vector (%s) \n'                 ,...
        ';;! \\author Vishal Coelho \n'                         ,...
        ';;! \\date   %s\n;;! \n;;\n'                           ,...
        ';;  Group:\t\t\tC2000\n'                               ,...
        ';;  Target Family:\t$DEVICE$\n;;\n'                    ,...
        ';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n'                               ,...
        ';; ALL RIGHTS RESERVED\n'                              ,...
        HEAD_string                                             ,...
        ';; \n'                       ,...
        ';; \n'             ,...
        HEAD_string                                             ,...
        '\n'                                                    ,...
        '\t.def\t_test_input%s \n'                              ,...
        '\n'                                                    ,...
        '\t.sect\t".econst"\n'                                  ,...
        '\n'], InFn, num2str(N), date, num2str(N));
    % Start the vector
    fprintf(fid,['_test_input',num2str(N),':\n']);
    if (strcmp(precision,'TYPE_FLOAT'))
        S = sprintf('\t.float\t%15.12f, %15.12f, %15.12f, %15.12f \n',t);
    else
        S = sprintf('\t.xldouble\t%15.12f, %15.12f, %15.12f, %15.12f \n',t);
    end
    fprintf(fid,S);
    fprintf(fid,'\n;; End of File\n');
    fclose(fid);
end
if (~strcmp(OutFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(OutFn,'w');
    fprintf(fid,[HEAD_string                                    ,...
        ';;! \\file %s\n'                                       ,...
        ';;! \\brief  Log Output Vector (%s) \n'                ,...
        ';;! \\author Vishal Coelho \n'                         ,...
        ';;! \\date   %s\n;;! \n;;\n'                           ,...
        ';;  Group:\t\t\tC2000\n'                               ,...
        ';;  Target Family:\tF2837x\n;;\n'                      ,...
        ';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n'                               ,...
        ';; ALL RIGHTS RESERVED\n'                              ,...
        HEAD_string                                             ,...
        ';; \n'                       ,...
        ';; \n'             ,...
        HEAD_string                                             ,...
        '\n'                                                    ,...
        '\t.def\t_test_golden%s \n'                             ,...
        '\n'                                                    ,...
        '\t.sect\t".econst"\n'                                  ,...
        '\n'], OutFn, num2str(N), date, num2str(N));
    % Start the vector
    fprintf(fid, ['_test_golden',num2str(N),':\n']);
    if (strcmp(precision,'TYPE_FLOAT'))
        S = sprintf('\t.float\t%15.12f, %15.12f, %15.12f, %15.12f \n',REF);
    else
        S = sprintf('\t.xldouble\t%15.12f, %15.12f, %15.12f, %15.12f \n',REF);
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
    fprintf(fid,[HEAD_string                                             ,...
        '//! \\file %s\n'                                       ,...
        '//! \\brief  Log Input Vector (%s) \n'                 ,...
        '//! \\author Vishal Coelho \n'                         ,...
        '//! \\date   %s\n//! \n//\n'                           ,...
        '//  Group:\t\t\tC2000\n'                               ,...
        '//  Target Family:\t$DEVICE$\n//\n'                    ,...
        '// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n'                               ,...
        '// ALL RIGHTS RESERVED\n'                              ,...
        HEAD_string                                             ,...
        '\n'                       ,...
        '// \n'             ,...
        HEAD_string                                             ,...
        '\n'], InFn, num2str(N), date);
    
    % Start the vector
    fprintf(fid, ['const ',ftype,' test_input[',num2str(N),...
        '] = {\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',t);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',t);
    end
    fprintf(fid,S);
    fprintf(fid,['}; \n\n',...
        '\n// End of File\n']);
    fclose(fid);
end
if (~strcmp(OutFn,'NULL') && strcmp(ext,'.c'))
    fid = fopen(OutFn,'w');
    fprintf(fid,[HEAD_string                                            ,...
        '//! \\file %s\n'                                       ,...
        '//! \\brief  Log Ouput Vector (%s) \n'                 ,...
        '//! \\author Vishal Coelho \n'                         ,...
        '//! \\date   %s\n//! \n//\n'                           ,...
        '//  Group:\t\t\tC2000\n'                               ,...
        '//  Target Family:\t$DEVICE$\n//\n'                    ,...
        '// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n'                               ,...
        '// ALL RIGHTS RESERVED\n'                              ,...
        HEAD_string                                             ,...
        '\n'                       ,...
        '// \n'             ,...
        HEAD_string                                             ,...
        '\n'], OutFn, num2str(N), date);
    
    % Start th e vector
    fprintf(fid, ['const ',ftype,' test_golden[',num2str(N),...
        '] = {\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',REF);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',REF);
    end
    fprintf(fid,S);
    fprintf(fid,['}; \n\n',...
        '\n// End of File\n']);
    fclose(fid);
end
%%
% End of file
