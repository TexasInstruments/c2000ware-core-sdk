%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate Exponent Input/Ouput Vectors
% \author Vishal Coelho
% \date   01/06/2017
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Exponent Algorithm
% This is a table lookup algorithm. The steps are as follows,
%
% * calculate the absolute of x, |x|
%
% * Separate the integer and fractional portion of the input
%
% * Get e^integer(x) from the table
%
% * Calculate e^(fraction) by using the Taylor series expansion for
% exponents
%
% $$e^{x} = 1 + x*(1+\frac{x}{2}(1+(\frac{x}{3})(1+\frac{x}{4}(1+\frac{x}{5}*(1+\frac{x}{6}*(1+\frac{x}{7})))))) $$
%
% * The result,  $e^{x} = e^{integer}*e^{fraction}$
%
% * If x was negative, calculate the inverse of the result
%
%
%% Required Parameters
% * *N* , the size of the input/output array
% * *SWP* , array indicating the desired input sweep, e.g. [-pi, +pi].
%   Note that the input cannot exceed floor(log(realmax)). For single
%   precision data the input must be lesser than 89
%   (floor(log(3.4028e+38))) and for double precision the input must be
%   lesser than 710 (floor(log(1.7977e+308)))
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
% *EXP*, the calculated Exponent
% *REF*, the reference Exponent (calculated using matlab in-built functions)
% *AERR*, Absolute error
% *RERR*, Relative error

%% Function Prototype
%  An Example: Generate a 512 exponent input/output vector
%
%  [E,R,AE,RE] = FPU_FastRTS_runExp(512, [-pi,pi], 'TYPE_FLOAT',
%  'expTable.asm', 'expInput.asm', 'expOutput.asm')
%
% or
%
%  [E,R,AE,RE] = FPU_FastRTS_runExp(512, [-pi,pi], 'TYPE_FLOAT',
%  'expTable.c', 'expInput.c', 'expOutput.c')
%
function [EXP,REF,AERR,RERR] = FPU_FastRTS_runExp(N, SWP, varargin)
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
    limit = floor(log(realmax('single')));
elseif (strcmp(precision,'TYPE_DOUBLE'))
    ftype = 'long double';
    limit = floor(log(realmax('double')));
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
assert((max(SWP) <= limit), ['Values in the input need to be lesser than ',...
    num2str(limit),' for exponents of the chosen floating point precision']);

%% Generate the lookup table and the coefficients
if (~strcmp(TblFn,'NULL'))
    T = FPU_FastRTS_genTableExp(precision, TblFn);
else
    T = FPU_FastRTS_genTableExp();
end

figure;
plot(T,'-b'), title('Exponent Lookup Table');
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


%% Calculate the Exponent for the sweep range and plot the response
istep = (SWP(2)-SWP(1))/N;
x     = SWP(1);
RERR  = zeros(1,N);
AERR  = zeros(1,N);
REF   = zeros(1,N);
EXP   = zeros(1,N);
t     = zeros(1,N);

for i = 1 : N
    t(i) = x;
    % Calculate the Exp for the current x
    x_a = abs(x);
    if (strcmp(precision,'TYPE_FLOAT'))
        x_i = int32(floor(x_a));
        x_f = single(x_a - floor(x_a));
        e_intx  = single(T(x_i + 1));
        e_fracx = 1 + x_f*(1 + x_f*FPUINV2 *...
            (1 + x_f*FPUINV3 *...
            (1 + x_f*FPUINV4 *...
            (1 + x_f*FPUINV5 *...
            (1 + x_f*FPUINV6 *...
            (1 + x_f*FPUINV7))))));
    else %precision = double
        x_i = int64(floor(x_a));
        x_f = double(x_a - floor(x_a));
        e_intx  = double(T(x_i + 1));
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
    if(x < 0)
        e_x = 1/e_x;
    end
    EXP(i) = e_x;
    REF(i) = exp(x);
    AERR(i) = abs(REF(i) - EXP(i));
    RERR(i) = AERR(i)/max(abs(x), abs(REF(i)));
    x       = x + istep;
end
figure;
subplot(2,2,1), plot(t,EXP,'-b',t,REF,'--r'), legend('Table Lookup Exp',...
    'Reference MATLAB Exp'), xlabel('x'), ylabel('exp(x)'),
title('Exp: Taylor Series Expansion and Table Lookup'), grid on;
subplot(2,2,2), plot(t,AERR),xlabel('x'), ylabel('exp(x)'),
title('Absolute Error'), grid on;
subplot(2,2,3), plot(t,RERR),xlabel('x'), ylabel('exp(x)'),
title('Relative Error'), grid on;

%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,[HEAD_string                                    ,...
        ';;! \\file %s \n'                                      ,...
        ';;! \\brief  Exp Input Vector (%s) \n'                 ,...
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
        ';;! \\brief  Exp Output Vector (%s) \n'                ,...
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
        '//! \\brief  Exp Input Vector (%s) \n'                 ,...
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
        '//! \\brief  Exp Ouput Vector (%s) \n'                 ,...
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
