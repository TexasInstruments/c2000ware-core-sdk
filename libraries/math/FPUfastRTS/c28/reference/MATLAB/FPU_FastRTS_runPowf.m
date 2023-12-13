%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate powf Input/Ouput Vectors
% \author Vishal Coelho
% \date   02/07/2017
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Powf Algorithm
% This is a table lookup algorithm. The steps are as follows,
%
% * $x^y$   can be calculated as $e^{y*log(x)}$
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
% * calculate the absolute of x' = y*log(x), |x'|
%
% * Separate the integer and fractional portion of the input
%
% * Get e^integer(x') from the table
%
% * Calculate e^(fraction) by using the Taylor series expansion for
% exponents
%
% $$e^{x'} = 1 + x*(1+\frac{x'}{2}(1+(\frac{x'}{3})(1+\frac{x'}{4}(1+\frac{x'}{5}*(1+\frac{x'}{6}*(1+\frac{x'}{7})))))) $$
%
% * The result,  $e^{x'} = e^{integer}*e^{fraction}$
%
% * If x' was negative, calculate the inverse of the result
%
%% Required Parameters
% * *N* , the size of the input/output array
% * *SWPY* , array indicating the desired input sweep, e.g. [-pi, +pi]
% * *SWPX* , array indicating the desired input sweep, e.g. [1, 50]
%
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *Filename1(table)*, name of file to write the log table to. If defined it 
%    is passed on to the genTable function
% * *Filename2(table)*, name of file to write the exp table to. If defined it 
%    is passed on to the genTable function
% * *Filename(input)*, name of file to write the input vector to
% * *Filename(output)*, name of file to write the output vector to
% The filenames can only have a .asm or .c extension
%
%% Returns
% *POWF*, the calculated powf
% *REF*, the reference powf (calculated using matlab in-built functions)
% *AERR*, Absolute error
% *RERR*, Relative error

%% Function Prototype
%  An Example: Generate a 512 powf input/output vector
%
%  [P,R,AE,RE] = FPU_FastRTS_runPowf(512, [-pi,pi], [1,50], 'TYPE_FLOAT',
%  'logTable.asm', 'expTable.asm', 'powfInput.asm', 'powfOutput.asm')
%
% or
%
%  [P,R,AE,RE] = FPU_FastRTS_runPowf(512, [-pi,pi], [1,50], 'TYPE_FLOAT',
%  'logTable.c', 'expTable.c', 'powfInput.c', 'powfOutput.c')
%
function [POWF,REF,AERR,RERR] = FPU_FastRTS_runPowf(N, SWPY, SWPX, varargin)
%% Parse Arguments
nOptArgs = 5;
numvarargs = length(varargin);
if numvarargs > nOptArgs
    error('myfunc:TooManyInputs',...
        ['requires at most ',num2str(nOptArgs),' optional input(s)']);
end

% Assign optional argument
optArgs = {'TYPE_FLOAT','NULL', 'NULL','NULL', 'NULL'};

% Check contents of varargin: if empty skip
newVals = cellfun(@(x) ~isempty(x), varargin);

% now put these defaults into the valuesToUse cell array,
% and overwrite the ones specified in varargin.
optArgs(newVals) = varargin(newVals);
% or ...
% [optargs{1:numvarargs}] = varargin{:};

% Place optional args in memorable variable names
[precision, Tbl1Fn, Tbl2Fn, InFn, OutFn] = optArgs{:};

% filenames must have an asm or c extenstion
if (~strcmp(Tbl1Fn,'NULL'))
    [~,~,ext] = fileparts(Tbl1Fn);
    assert((strcmp(ext,'.asm') || strcmp(ext,'.c')), ['Filename needs to have',...
        ' an .asm or .c extension']);
end
if (~strcmp(Tbl2Fn,'NULL'))
    [~,~,ext] = fileparts(Tbl2Fn);
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
SWP_s  = size(SWPY);
assert((SWP_s(1) == 1 && SWP_s(2) == 2),...
    'SWPY needs to be 1x2');
SWP_s  = size(SWPX);
assert((SWP_s(1) == 1 && SWP_s(2) == 2),...
    'SWPX needs to be 1x2');
assert((min(SWPX) >= 1), 'Values of x need to be greater than 1');
TBL_SIZE = 32;

%% Generate the lookup table and the coefficients
if (~strcmp(Tbl1Fn,'NULL'))
    T1 = FPU_FastRTS_genTableLog(TBL_SIZE, precision, Tbl1Fn);
    T2 = FPU_FastRTS_genTableExp(precision, Tbl2Fn);
else
    T1 = FPU_FastRTS_genTableLog(TBL_SIZE);
    T2 = FPU_FastRTS_genTableExp();
end

figure;
subplot(2,1,1), plot(T1,'-b'), title('Natural Log Lookup Table');
subplot(2,1,2), plot(T2,'-r'), title('Exponent Lookup Table');
FPULOG2     = log(2);
if (strcmp(precision,'TYPE_FLOAT'))
    FPUINV1  = single(1);
    FPUINV2  = single(1/2);
    FPUINV3  = single(1/3);
    FPUINV4  = single(1/4);
    FPUINV5  = single(1/5);
    FPUINV6  = single(1/6);
    FPUINV7  = single(1/7);
    FPULOG10 = single(log10(exp(1)));
else %precision = double
    FPUINV1  = double(1);
    FPUINV2  = double(1/2);
    FPUINV3  = double(1/3);
    FPUINV4  = double(1/4);
    FPUINV5  = double(1/5);
    FPUINV6  = double(1/6);
    FPUINV7  = double(1/7);
    FPUINV8  = double(1/8);
    FPUINV9  = double(1/9);
    FPUINV10 = double(1/10);
    FPUINV11 = double(1/11);
    FPUINV12 = double(1/12);
    FPUINV13 = double(1/13);
    FPUINV14 = double(1/14);
    FPULOG10 = double(log10(exp(1)));
end
%% Calculate the powf for the sweep range and plot the response
ystep = (SWPY(2)-SWPY(1))/N;
xstep = (SWPX(2)-SWPX(1))/N;
y     = SWPY(1);
x     = SWPX(1);
RERR  = zeros(1,N);
AERR  = zeros(1,N);
REF   = zeros(1,N);
LOG   = zeros(1,N);
EXP   = zeros(1,N);
POWF  = zeros(1,N);
t     = zeros(1,N);
IN    = zeros(1, 2*N);
j     = 1;
for i = 1 : N
    % step 1: Calculate the Log for the current x
    x_a = abs(x);
    [f, e] = log2(x_a);
    x_exp_unbiased = e - 1;
    x_mantissa     = 2*f - 1; % remove the implicit 1
    log_exp        = x_exp_unbiased * FPULOG2;
    tbl_index      = floor(x_mantissa*TBL_SIZE)*3 + 1;
    A0             = T1(tbl_index);
    A1             = T1(tbl_index+1);
    A2             = T1(tbl_index+2);
    log_1pmantissa = A0 + x_mantissa*(A1 + x_mantissa*A2);
    LOG(i) = log_1pmantissa + log_exp;
    
    % step 2: x_p or x' = y*log(x)
    x_p = y*LOG(i);
    
    % step 3: Calculate the Exp for the current x_p
    x_a = abs(x_p);
    if (strcmp(precision,'TYPE_FLOAT'))
        x_i = int32(floor(x_a));
        x_f = single(x_a - floor(x_a));
        e_intx  = single(T2(x_i + 1));
        e_fracx = 1 + x_f*(1 + x_f*FPUINV2 *...
            (1 + x_f*FPUINV3 *...
            (1 + x_f*FPUINV4 *...
            (1 + x_f*FPUINV5 *...
            (1 + x_f*FPUINV6 *...
            (1 + x_f*FPUINV7))))));
    else %precision = double
        x_i = int64(floor(x_a));
        x_f = double(x_a - floor(x_a));
        e_intx  = double(T2(x_i + 1));
        e_fracx = 1 + x_f*(1 + x_f*FPUINV2 *...
            (1 + x_f*FPUINV3 *...
            (1 + x_f*FPUINV4 *...
            (1 + x_f*FPUINV5 *...
            (1 + x_f*FPUINV6 *...
            (1 + x_f*FPUINV7 *...
            (1 + x_f*FPUINV8 *...
            (1 + x_f*FPUINV9 *...
            (1 + x_f*FPUINV10 *...
            (1 + x_f*FPUINV11 *...
            (1 + x_f*FPUINV12 *...
            (1 + x_f*FPUINV13 *...
            (1 + x_f*FPUINV14)))))))))))));
    end
    
    e_x     = e_intx*e_fracx;
    if(x_p < 0)
        e_x = 1/e_x;
    end
    EXP(i) = e_x;
    POWF(i) = EXP(i);
    
    REF(i)  = x^y;
    AERR(i) = abs(REF(i) - POWF(i));
    RERR(i) = AERR(i)/max(abs(x), abs(REF(i)));
    
    t(i)    = i;
    IN(j)   = x;
    IN(j+1) = y;
    j = j + 2;
    y  = y + ystep;
    x  = x + xstep;
end
figure;
subplot(2,2,1), plot(t,POWF,'-b',t,REF,'--r'), legend('Table Lookup powf',...
    'Reference MATLAB powf'), xlabel('x'), ylabel('x^y'),
title('Powf: Table Lookup'), grid on;
subplot(2,2,2), plot(t,AERR),xlabel('x'), ylabel('x^y'),
title('Absolute Error'), grid on;
subplot(2,2,3), plot(t,RERR),xlabel('x'), ylabel('x^y'),
title('Relative Error'), grid on;

%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,[HEAD_string                                    ,...
        ';;! \\file %s \n'                                      ,...
        ';;! \\brief  Powf Input Vector (%s) \n'                ,...
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
    fprintf(fid,[HEAD_string                                    ,...
        ';;! \\file %s\n'                                       ,...
        ';;! \\brief  Powf Output Vector (%s) \n'               ,...
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
        '//! \\brief  Powf Input Vector (%s) \n'                ,...
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
    fprintf(fid, ['const ',ftype,' test_input[',num2str(2*N),...
        '] = {\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',IN);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',IN);
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
        '//! \\brief  Powf Ouput Vector (%s) \n'                ,...
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
