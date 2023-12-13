%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate Finite Integer Division (FID) Input/Output Vectors
% \author Vishal Coelho
% \date   03/21/2016
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Slow Division Algorithms
% The algorithms are based on the standard recurrence equation
%
% $$P_{j+1} = R{\times}P_{j} - q_{n-(j+1)}{\times}D$$,
%
% where
% * $P_{j}$ is the jth partial remainder of the division
% * *R* is the radix
% * $q_{n-(j+1)}$ is the n-(j+1) digit of the quotient
% * *n* is the number of digits in the quotient
% * *D* is the divisor
%
% References:
% Wikipedia (<https://en.wikipedia.org/wiki/Division_algorithm>)

%% Required Parameters
% * *N*, desired size
% * *FID_TYPE* , must be one of the following
% # 'UI32BYUI32'
% # 'I32BYI32'
% # 'I32BYUI32'
% # 'UI64BYUI32'
% # 'I64BYI32'
% # 'I64BYUI32'
% # 'UI64BYUI64'
% # 'I64BYI64'
% # 'I64BYUI64'
% # 'UI16BYUI16'
% # 'I16BYI16'
% # 'UI32BYUI16'
% # 'I32BYI16'
% # 'F64BYF64'
% * *DIV_TYPE* , must be one of the following
% # 'TRUNCATED'
% # 'FLOORED' or 'MODULO'
% # 'EUCLIDEAN'


%% Optional Parameters
% * *Filename(input)*, name of file to write the input vector to
% * *Filename(output)*, name of file to write the output vector to
% The filenames can only have a .asm or .c extension
%
%% Returns
% *QUO*, the calculated quotient
% *QUO_R*,  the reference Qutotient (calculated using matlab in-built
% functions)
% *REM*, the calculated remainder
% *REM_R*,  the reference remainder (calculated using matlab in-built
% functions)
% *AERR_Q*, Absolute error of the quotient
% *RERR_Q*, Relative error of the quotient
% *AERR_R*, Absolute error of the remainder
% *RERR_R*, Relative error of the remainder


%% Function Prototype
%  An Example: Generate a 512 input/output vector
%
%  [Q,Q_r,R,R_r,AE_Q,RE_Q,AE_R,RE_R] = FPU_FastRTS_runFID(512, 'UI32BYUI32',
%  'FLOORED', 'ui32byui32Input.asm', 'ui32byui32Output.asm')
%
% or
%
%  [Q,Q_r,R,R_r,AE_Q,RE_Q,AE_R,RE_R] = FPU_FastRTS_runFID(512, 'UI32BYUI32',
%  'FLOORED', 'ui32byui32Input.c', 'ui32byui32Output.c')
%
function [QUO,QUO_R,REM,REM_R,AERR_Q,RERR_Q,AERR_R,RERR_R] = ...
    FPU_FastRTS_runFID(N, FID_TYPE, DIV_TYPE, varargin)
%% Parse Arguments
nOptArgs = 2;
numvarargs = length(varargin);
if numvarargs > nOptArgs
    error('myfunc:TooManyInputs',...
        ['requires at most ',num2str(nOptArgs),' optional input(s)']);
end

% Assign optional argument
optArgs = {'NULL','NULL'};

% Check contents of varargin: if empty skip
newVals = cellfun(@(x) ~isempty(x), varargin);

% now put these defaults into the valuesToUse cell array,
% and overwrite the ones specified in varargin.
optArgs(newVals) = varargin(newVals);
% or ...
% [optargs{1:numvarargs}] = varargin{:};

% Place optional args in memorable variable names
[InFn, OutFn] = optArgs{:};

% filenames must have an asm or c extenstion
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

% Long, fixed-decimal format with 15 digits after the decimal point for double
% values, and 7 digits after the decimal point for single values.
format long

assert( N <= 1024 && N > 0, 'Valid values are between 1 and 1024');
assert( mod(N,2) == 0, 'N needs to be even (preferably a power of 2)');
estr = sprintf(['Second argument must be one of the following, \n',...
    '''UI32BYUI32''\n',...
    '''I32BYI32''\n',...
    '''I32BYUI32''\n',...
    '''UI64BYUI32''\n',...
    '''I64BYI32''\n',...
    '''I64BYUI32''\n',...
    '''UI64BYUI64''\n',...
    '''I64BYI64''\n',...
    '''I64BYUI64''\n',...
    '''UI16BYUI16''\n',...
    '''I16BYI16''\n',...
    '''UI32BYUI16''\n',...
    '''I32BYI16''\n',...
    '''F64BYF64''\n',...
    ]);
assert(strcmp(FID_TYPE,'UI32BYUI32')    || ...
    strcmp(FID_TYPE,'I32BYI32')         || ...
    strcmp(FID_TYPE,'I32BYUI32')        || ...
    strcmp(FID_TYPE,'UI64BYUI32')       || ...
    strcmp(FID_TYPE,'I64BYI32')         || ...
    strcmp(FID_TYPE,'I64BYUI32')        || ...
    strcmp(FID_TYPE,'I64BYI64')         || ...
    strcmp(FID_TYPE,'UI64BYUI64')       || ...
    strcmp(FID_TYPE,'I64BYUI64')        || ...
    strcmp(FID_TYPE,'UI16BYUI16')       || ...
    strcmp(FID_TYPE,'I16BYI16')         || ...
    strcmp(FID_TYPE,'UI32BYUI16')       || ...
    strcmp(FID_TYPE,'I32BYI16')         || ...
    strcmp(FID_TYPE,'F64BYF64'),...
    estr);

estr = sprintf(['Third argument must be one of the following, \n',...
    '''TRUNCATED''\n',...
    '''FLOORED or MODULO''\n',...
    '''EUCLIDEAN''\n',...
    ]);
assert(strcmp(DIV_TYPE,'TRUNCATED')    || ...
    strcmp(DIV_TYPE,'FLOORED')         || ...
    strcmp(DIV_TYPE,'MODULO')          || ...
    strcmp(DIV_TYPE,'EUCLIDEAN'),...
    estr);

%% Perform the integer division
num_low = double(0);   den_low  = double(0);
num_high = double(0);  den_high = double(0);
num_bias = double(0);  den_bias = double(0);
if (strcmp(FID_TYPE, 'UI32BYUI32'))
    asm_num_type = 'ulong';    asm_den_type = 'ulong';
    asm_quo_type = 'ulong';    asm_rem_type = 'ulong';
    c_num_type   = 'uint32_t'; c_den_type   = 'uint32_t';
    c_num_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_den_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_quo_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_rem_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_quo_type   = 'uint32_t'; c_rem_type   = 'uint32_t';
    flag_signed_op = 0;
    e_n = 32;                e_d = 32;
    num_low = 0;             den_low  = 0;
    num_high = 2^e_n - 1;    den_high = 2^e_d - 1;
    num_bias = 0;            den_bias = 0;
    % Override the DIV_TYPE
    disp(['Ignoring user DIV_TYPE, only TRUNCATED supported for this ',...
        'division type']);
    DIV_TYPE = 'TRUNCATED';
elseif (strcmp(FID_TYPE, 'I32BYI32'))
    asm_num_type = 'long';    asm_den_type = 'long';
    asm_quo_type = 'long';    asm_rem_type = 'long';
    c_num_type   = 'int32_t'; c_den_type   = 'int32_t';
    c_quo_type   = 'int32_t'; c_rem_type   = 'int32_t';
    c_num_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    c_den_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    c_quo_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    c_rem_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    flag_signed_op = 1;
    e_n = 32;                e_d = 32;
    num_low = -(2^(e_n-1));  den_low  = -(2^(e_d-1));
    num_high = 2^(e_n-1)- 1; den_high = 2^(e_d-1)- 1;
    num_bias = 0;            den_bias = 0;
elseif (strcmp(FID_TYPE, 'I32BYUI32'))
    asm_num_type = 'long';    asm_den_type = 'ulong';
    asm_quo_type = 'long';    asm_rem_type = 'long';
    c_num_type   = 'int32_t'; c_den_type   = 'uint32_t';
    c_quo_type   = 'int32_t'; c_rem_type   = 'int32_t';
    c_num_pfmt   = '    %12d, %12d, %12d, %12d,\n';
    c_den_pfmt   = '    %12u, %12u, %12u, %12u,\n';
    c_quo_pfmt   = '    %12d, %12d, %12d, %12d,\n';
    c_rem_pfmt   = '    %12d, %12d, %12d, %12d,\n';
    flag_signed_op = 1;
    e_n = 32;                e_d = 32;
    num_low = -(2^(e_n-1));  den_low = -(2^(e_d-1));
    num_high = 2^(e_n-1)- 1; den_high = 2^(e_d-1)- 1;
    num_bias = 0;            den_bias = 2^(e_d-1);
    % Override the DIV_TYPE
    disp(['Ignoring user DIV_TYPE, only TRUNCATED supported for this ',...
        'division type']);
    DIV_TYPE = 'TRUNCATED';
elseif (strcmp(FID_TYPE, 'UI64BYUI32'))
    asm_num_type = 'field';asm_den_type = 'ulong';
    asm_quo_type = 'field';asm_rem_type = 'ulong';
    c_num_type   = 'uint64_t';c_den_type   = 'uint32_t';
    c_quo_type   = 'uint64_t';c_rem_type   = 'uint32_t';
    c_num_pfmt   = '    %20luUL, %20luUL, %20luUL, %20luUL, \n';
    c_den_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_quo_pfmt   = '    %20luUL, %20luUL, %20luUL, %20luUL, \n';
    c_rem_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    flag_signed_op = 0;
    e_n = 64; e_d = 32;
    num_low = 0;             den_low  = 0;
    num_high = 2^e_n - 1;    den_high = 2^e_d - 1;
    num_bias = 0;            den_bias = 0;
elseif (strcmp(FID_TYPE, 'I64BYI32'))
    asm_num_type = 'field';asm_den_type = 'long';
    asm_quo_type = 'field';asm_rem_type = 'long';
    c_num_type   = 'int64_t';c_den_type   = 'int32_t';
    c_quo_type   = 'int64_t';c_rem_type   = 'int32_t';
    c_num_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    c_den_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    c_quo_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    c_rem_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    flag_signed_op = 1;
    e_n = 64; e_d = 32;
    num_low = -(2^(e_n-1));    den_low  = -(2^(e_d-1));
    num_high = 2^(e_n-1)- 1;   den_high = 2^(e_d-1)- 1;
    num_bias = 0;              den_bias = 0;
elseif (strcmp(FID_TYPE, 'I64BYUI32'))
    asm_num_type = 'field';asm_den_type = 'ulong';
    asm_quo_type = 'field';asm_rem_type = 'field';
    c_num_type   = 'int64_t';c_den_type   = 'uint32_t';
    c_quo_type   = 'int64_t';c_rem_type   = 'int64_t';
    c_num_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    c_den_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_quo_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    c_rem_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    flag_signed_op = 1;
    e_n = 64; e_d = 32;
    num_low = -(2^(e_n-1));    den_low  = 0;
    num_high = 2^(e_n-1)- 1;   den_high = 2^e_d - 1;
    num_bias = 0;              den_bias = 0;
    % Override the DIV_TYPE
    disp(['Ignoring user DIV_TYPE, only TRUNCATED supported for this ',...
        'division type']);
    DIV_TYPE = 'TRUNCATED';
elseif (strcmp(FID_TYPE, 'UI64BYUI64'))
    asm_num_type = 'field';asm_den_type = 'field';
    asm_quo_type = 'field';asm_rem_type = 'field';
    c_num_type   = 'uint64_t';c_den_type   = 'uint64_t';
    c_quo_type   = 'uint64_t';c_rem_type   = 'uint64_t';
    c_num_pfmt   = '    %20luUL, %20luUL, %20luUL, %20luUL, \n';
    c_den_pfmt   = '    %20luUL, %20luUL, %20luUL, %20luUL, \n';
    c_quo_pfmt   = '    %20luUL, %20luUL, %20luUL, %20luUL, \n';
    c_rem_pfmt   = '    %20luUL, %20luUL, %20luUL, %20luUL, \n';
    flag_signed_op = 0;
    e_n = 64; e_d = 64;
    num_low = 0;             den_low  = 0;
    num_high = 2^e_n - 1;    den_high = 2^e_d - 1;
    num_bias = 0;            den_bias = 0;
    % Override the DIV_TYPE
    disp(['Ignoring user DIV_TYPE, only TRUNCATED supported for this ',...
        'division type']);
    DIV_TYPE = 'TRUNCATED';
elseif (strcmp(FID_TYPE, 'I64BYI64'))
    asm_num_type = 'field';asm_den_type = 'field';
    asm_quo_type = 'field';asm_rem_type = 'field';
    c_num_type   = 'int64_t';c_den_type   = 'int64_t';
    c_quo_type   = 'int64_t';c_rem_type   = 'int64_t';
    c_num_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    c_den_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    c_quo_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    c_rem_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    flag_signed_op = 1;
    e_n = 64; e_d = 64;
    num_low = -(2^(e_n-1));    den_low  = -(2^(e_d-1));
    num_high = 2^(e_n-1)- 1;   den_high = 2^(e_d-1)- 1;
    num_bias = 0;              den_bias = 0;
elseif (strcmp(FID_TYPE, 'I64BYUI64'))
    asm_num_type = 'field';asm_den_type = 'field';
    asm_quo_type = 'field';asm_rem_type = 'field';
    c_num_type   = 'int64_t';c_den_type   = 'uint64_t';
    c_quo_type   = 'int64_t';c_rem_type   = 'int64_t';
    c_num_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    c_den_pfmt   = '    %20luUL, %20luUL, %20luUL, %20luUL, \n';
    c_quo_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    c_rem_pfmt   = '    %20ldL, %20ldL, %20ldL, %20ldL, \n';
    %This is supposed to be a signed operation but at the moment 64-bit
    %restoring division isnt working so leave it out
    flag_signed_op = 0; 
    e_n = 64; e_d = 64;
    num_low = -(2^(e_n-1));    den_low  = 0;
    num_high = 2^(e_n-1)- 1;   den_high = 2^e_d - 1;
    num_bias = 0;              den_bias = 0;
    % Override the DIV_TYPE
    disp(['Ignoring user DIV_TYPE, only TRUNCATED supported for this ',...
        'division type']);
    DIV_TYPE = 'TRUNCATED';
elseif (strcmp(FID_TYPE, 'UI16BYUI16'))
    asm_num_type = 'uword';    asm_den_type = 'uword';
    asm_quo_type = 'uword';    asm_rem_type = 'uword';
    c_num_type   = 'uint16_t'; c_den_type   = 'uint16_t';
    c_num_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_den_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_quo_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_rem_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_quo_type   = 'uint16_t'; c_rem_type   = 'uint16_t';
    flag_signed_op = 0;
    e_n = 16;                e_d = 16;
    num_low = 0;             den_low  = 0;
    num_high = 2^e_n - 1;    den_high = 2^e_d - 1;
    num_bias = 0;            den_bias = 0;
    % Override the DIV_TYPE
    disp(['Ignoring user DIV_TYPE, only TRUNCATED supported for this ',...
        'division type']);
    DIV_TYPE = 'TRUNCATED';
elseif (strcmp(FID_TYPE, 'I16BYI16'))
    asm_num_type = 'word';    asm_den_type = 'word';
    asm_quo_type = 'word';    asm_rem_type = 'word';
    c_num_type   = 'int16_t'; c_den_type   = 'int16_t';
    c_quo_type   = 'int16_t'; c_rem_type   = 'int16_t';
    c_num_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    c_den_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    c_quo_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    c_rem_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    flag_signed_op = 1;
    e_n = 16;                e_d = 16;
    num_low = -(2^(e_n-1));  den_low  = -(2^(e_d-1));
    num_high = 2^(e_n-1)- 1; den_high = 2^(e_d-1)- 1;
    num_bias = 0;            den_bias = 0;
elseif (strcmp(FID_TYPE, 'UI32BYUI16'))
    asm_num_type = 'ulong';    asm_den_type = 'uword';
    asm_quo_type = 'ulong';    asm_rem_type = 'uword';
    c_num_type   = 'uint32_t'; c_den_type   = 'uint16_t';
    c_num_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_den_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_quo_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_rem_pfmt   = '    %12u, %12u, %12u, %12u, \n';
    c_quo_type   = 'uint32_t'; c_rem_type   = 'uint16_t';
    flag_signed_op = 0;
    e_n = 32;                e_d = 16;
    num_low = 0;             den_low  = 0;
    num_high = 2^e_n - 1;    den_high = 2^e_d - 1;
    num_bias = 0;            den_bias = 0;
    % Override the DIV_TYPE
    disp(['Ignoring user DIV_TYPE, only TRUNCATED supported for this ',...
        'division type']);
    DIV_TYPE = 'TRUNCATED';
elseif (strcmp(FID_TYPE, 'I32BYI16'))
    asm_num_type = 'long';    asm_den_type = 'word';
    asm_quo_type = 'long';    asm_rem_type = 'word';
    c_num_type   = 'int32_t'; c_den_type   = 'int16_t';
    c_num_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    c_den_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    c_quo_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    c_rem_pfmt   = '    %12d, %12d, %12d, %12d, \n';
    c_quo_type   = 'int32_t'; c_rem_type   = 'int16_t';
    flag_signed_op = 1;
    e_n = 32;                e_d = 16;
    num_low = -(2^(e_n-1));  den_low  = -(2^(e_d-1));
    num_high = 2^(e_n-1)- 1; den_high = 2^(e_d-1)- 1;
    num_bias = 0;            den_bias = 0;
elseif (strcmp(FID_TYPE, 'F64BYF64'))
    asm_num_type = 'xldouble';    asm_den_type = 'xldouble';
    asm_quo_type = 'xldouble';    asm_rem_type = 'xldouble';
    c_num_type   = 'long double'; c_den_type   = 'long double';
    c_num_pfmt   = '    %20e, %20e, %20e, %20e, \n';
    c_den_pfmt   = '    %20e, %20e, %20e, %20e, \n';
    c_quo_pfmt   = '    %20e, %20e, %20e, %20e, \n';
    c_rem_pfmt   = '    %20e, %20e, %20e, %20e, \n';
    flag_signed_op = 0;
    e_n = 0;                e_d = 0;
    c_quo_type   = 'long double'; c_rem_type   = 'long double';
    num_low = realmin('double');  den_low  = realmin('double');
    num_high = realmax('double'); den_high = realmax('double');
    num_bias = 0;            den_bias = 0;
    % Ignore the DIV_TYPE
    disp(['Ignoring user DIV_TYPE']);
    DIV_TYPE = 'TRUNCATED';
end

if(strcmp(FID_TYPE, 'UI64BYUI32') || strcmp(FID_TYPE, 'UI64BYUI64'))
    % <<VC160404 At the current date the resotring division
    % does not work correctly when you have 64 bits as the bitshifts of
    % 1 result in 0 which throws off the rest of the calculations. I
    % have left this as a todo for the future VC160404>>
    num_r = uint64(num_low + (num_high - num_low)*rand(1,N) + num_bias); num = num_r;
    den_r = uint64(den_low + (den_high - den_low)*rand(1,N) + den_bias); den = den_r;
elseif (strcmp(FID_TYPE, 'F64BYF64'))
    num_r = (num_low + (num_high - num_low)*rand(1,N) + num_bias); num = num_r;
    den_r = (den_low + (den_high - den_low)*rand(1,N) + den_bias); den = den_r;
else
    num_r = int64(num_low + (num_high - num_low)*rand(1,N) + num_bias); num = num_r;
    if(strcmp(FID_TYPE, 'I64BYUI64'))
        den_r = uint64(den_low + (den_high - den_low)*rand(1,N) + den_bias); den = den_r;
    else
        den_r = int64(den_low + (den_high - den_low)*rand(1,N) + den_bias); den = den_r;
    end
end
RERR_Q = zeros(1,N);
AERR_Q = zeros(1,N);
QUO_R  = zeros(1,N);
QUO    = zeros(1,N);
RERR_R = zeros(1,N);
AERR_R = zeros(1,N);
REM_R  = zeros(1,N);
REM    = zeros(1,N);

IN     = zeros(1,2*N);
OUT    = zeros(1,2*N);
j = 1;
for i = 1 : N
    
    IN(j)   = num_r(i);
    IN(j+1) = den_r(i);
    
    if(strcmp(DIV_TYPE, 'TRUNCATED'))
        if(strcmp(FID_TYPE, 'UI64BYUI32') || strcmp(FID_TYPE, 'UI64BYUI64'))
            % Remainder same sign as dividend (numerator)
            QUO_R(i) = uint64(fix(double(num(i))/double(den(i))));
            REM_R(i) = uint64(num(i)) - uint64(den(i))*uint64(QUO_R(i));
        elseif(strcmp(FID_TYPE, 'F64BYF64'))
            % Remainder same sign as dividend (numerator)
            QUO_R(i) = num(i)/den(i);
            REM_R(i) = 0;
        else
            % Remainder same sign as dividend (numerator)
            QUO_R(i) = int64(fix(double(num(i))/double(den(i))));
            % <<VC160413: Its possible rem*quo exceeds 64 bits - probably
            % at most 65 bits. I have converted them to 128-bit integers
            % done the calculation (the result <= 64-bits) and trucated to
            % signed 64-bits
            % REM_R(i) = int64(double(num(i)) - double(den(i))*double(QUO_R(i)));
            % VC160413>>
            REM_R(i) = int64(fi(num(i),1,128,0) - fi(den(i),1,128,0)*fi(QUO_R(i),1,128,0));
        end
    elseif(strcmp(DIV_TYPE, 'FLOORED') || strcmp(DIV_TYPE, 'MODULO'))
        % Remainder same sign as divisor
        QUO_R(i) = int64(floor(double(num(i))/double(den(i))));
        % <<VC160413: Its possible rem*quo exceeds 64 bits - probably
        % at most 65 bits. I have converted them to 128-bit integers
        % done the calculation (the result <= 64-bits) and trucated to
        % signed 64-bits
        % REM_R(i) = int64(double(num(i)) - double(den(i))*double(QUO_R(i)));
        % VC160413>>
        REM_R(i) = int64(fi(num(i),1,128,0) - fi(den(i),1,128,0)*fi(QUO_R(i),1,128,0));
    elseif (strcmp(DIV_TYPE, 'EUCLIDEAN'))
        % Remainder always positive
        if(den(i) > 0)
            QUO_R(i) = int64(floor(double(num(i))/double(den(i))));
            % <<VC160413: Its possible rem*quo exceeds 64 bits - probably
            % at most 65 bits. I have converted them to 128-bit integers
            % done the calculation (the result <= 64-bits) and trucated to
            % signed 64-bits
            % REM_R(i) = int64(double(num(i)) - double(den(i))*double(QUO_R(i)));
            % VC160413>>
            REM_R(i) = int64(fi(num(i),1,128,0) - fi(den(i),1,128,0)*fi(QUO_R(i),1,128,0));
        else
            QUO_R(i) = int64(ceil(double(num(i))/double(den(i))));
            % <<VC160413: Its possible rem*quo exceeds 64 bits - probably
            % at most 65 bits. I have converted them to 128-bit integers
            % done the calculation (the result <= 64-bits) and trucated to
            % signed 64-bits
            % REM_R(i) = int64(double(num(i)) - double(den(i))*double(QUO_R(i)));
            % VC160413>>
            REM_R(i) = int64(fi(num(i),1,128,0) - fi(den(i),1,128,0)*fi(QUO_R(i),1,128,0));
        end
        
    end
    
    if(flag_signed_op == 1) % a signed operation
        %flag_neg_quotient = sign(num) ^ sign(den)
        flag_TF  = bitand(bitxor(bitshift(num(i), -(e_n-1)),...
            bitshift(den(i), -(e_d-1))), 1);
        % flag_neg_remainder = sign(num)
        flag_NI = bitand(bitshift(num(i), -(e_n-1)), 1);
        % take the absolute value of the numerator and denominator
        if(num(i) < 0)
            num(i) = -num(i);
        end
        if(den(i) < 0)
            den(i) = -den(i);
        end
    end
    
    if(strcmp(FID_TYPE, 'UI64BYUI32') || strcmp(FID_TYPE, 'I64BYI32') || ...
            strcmp(FID_TYPE, 'I64BYUI32') || strcmp(FID_TYPE, 'UI64BYUI64') ||...
            strcmp(FID_TYPE, 'I64BYI64') || strcmp(FID_TYPE, 'I64BYUI64')||...
            strcmp(FID_TYPE, 'F64BYF64'))
        % <<VC160404 At the current date the resotring division
        % does not work correctly when you have 64 bits as the bitshifts of
        % 1 result in 0 which throws off the rest of the calculations. I
        % have left this as a todo for the future VC160404>>
        QUO(i) = QUO_R(i);
        REM(i) = REM_R(i);
    else
        % Treat the numerator and denominator as unsgined and proceed with
        % restoring division
        [QUO(i), REM(i)] = FPU_FastRTS_runRestoringDivision(num(i), den(i));
        
        if(REM(i) == 0)
            flag_ZI = 1;
        else
            flag_ZI = 0;
        end
        
        if(flag_signed_op == 1) % a signed operation
            if(strcmp(DIV_TYPE, 'TRUNCATED'))
                % Remainder same sign as dividend (numerator)
                if(flag_TF ~= 0)
                    QUO(i) = -QUO(i);
                end
                if(flag_NI ~= 0)
                    REM(i) = -REM(i);
                end
            elseif(strcmp(DIV_TYPE, 'FLOORED') || strcmp(DIV_TYPE, 'MODULO'))
                % Remainder same sign as divisor
                if((flag_TF ~= 0) && (flag_ZI == 0))
                    QUO(i) = QUO(i) + 1;
                    REM(i) = den(i) - REM(i);
                end
                if(flag_TF ~= 0)
                    QUO(i) = -QUO(i);
                end
                if(bitxor(flag_NI, flag_TF))
                    REM(i) = - REM(i);
                end
            elseif (strcmp(DIV_TYPE, 'EUCLIDEAN'))
                % Remainder always positive
                if((flag_NI ~= 0) && (flag_ZI == 0))
                    QUO(i) = QUO(i) + 1;
                    REM(i) = den(i) - REM(i);
                end
                if(flag_TF ~= 0)
                    QUO(i) = -QUO(i);
                end
            end
        end
    end
    AERR_Q(i) = abs(QUO_R(i) - QUO(i));
    RERR_Q(i) = AERR_Q(i)/abs(QUO_R(i));
    AERR_R(i) = abs(REM_R(i) - REM(i));
    RERR_R(i) = AERR_R(i)/abs(REM_R(i));
    
    OUT(j)   = QUO(i);
    OUT(j+1) = REM(i);
    
    j = j + 2;
    
end
figure;
t = linspace(1,N, N);
subplot(3,2,1), plot(t,QUO,'-b',t,QUO_R,'--r'),...
    legend('FID Quotient','Reference MATLAB Quotient'),...
    xlabel('sample'), ylabel('Quotient'),...
    title('Qutotient'), grid on;
subplot(3,2,3), plot(t,AERR_Q),xlabel('sample'), ylabel('Amplitude'),
title('Absolute Error (Quotient)'), grid on;
subplot(3,2,4), plot(t,RERR_Q),xlabel('sample'), ylabel('Amplitude'),
title('Relative Error (Quotient)'), grid on;
subplot(3,2,2), plot(t,REM,'-b',t,REM_R,'--r'),...
    legend('FID Remainder','Reference MATLAB Remainder'),...
    xlabel('sample'), ylabel('Remainder'),...
    title('Remainder'), grid on;
subplot(3,2,5), plot(t,AERR_Q),xlabel('sample'), ylabel('Amplitude'),
title('Absolute Error (Remainder)'), grid on;
subplot(3,2,6), plot(t,RERR_Q),xlabel('sample'), ylabel('Amplitude'),
title('Relative Error (Remainder)'), grid on;

%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',InFn,'\n']);
    fprintf(fid,[';;! \\brief  FID Input Vectors (',num2str(N),') \n']);
    fprintf(fid,';;! \\author Vishal Coelho \n');
    fprintf(fid,[';;! \\date   ',date,'\n;;! \n;;\n']);
    fprintf(fid,';;  Group:            C2000\n');
    fprintf(fid,';;  Target Family:    $DEVICE$\n;;\n');
    fprintf(fid,[';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,';; ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,';; \n');
    fprintf(fid,';; \n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    fprintf(fid,['    .def    _test_dividend_', num2str(N),'\n']);
    fprintf(fid,['    .def    _test_divisor_', num2str(N),'\n']);
    fprintf(fid,'\n');
    fprintf(fid,'    .sect    ".econst"\n');
    fprintf(fid,'\n');
    % Start the vector
    fprintf(fid, ['_test_dividend_', num2str(N),':\n']);
    S = sprintf(['    .',asm_num_type,' %12d, %12d, %12d, %12d \n'], num_r);
    fprintf(fid,S);
    fprintf(fid, '\n\n');
    fprintf(fid, ['_test_divisor_', num2str(N),':\n']);
    S = sprintf(['    .',asm_den_type,' %12d, %12d, %12d, %12d \n'], den_r);
    fprintf(fid,S);
    fprintf(fid,'\n;; End of File\n');
    fclose(fid);
end
if (~strcmp(OutFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(OutFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',OutFn,'\n']);
    fprintf(fid,[';;! \\brief  FID Output Vector (',num2str(N),') \n']);
    fprintf(fid,';;! \\author Vishal Coelho \n');
    fprintf(fid,[';;! \\date   ',date,'\n;;! \n;;\n']);
    fprintf(fid,';;  Group:            C2000\n');
    fprintf(fid,';;  Target Family:    F2837x\n;;\n');
    fprintf(fid,[';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,';; ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,';; \n');
    fprintf(fid,';; \n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    fprintf(fid,['    .def    _test_quotient_',num2str(N),'\n']);
    fprintf(fid,['    .def    _test_remainder_',num2str(N),'\n']);
    fprintf(fid,'\n');
    fprintf(fid,'    .sect    ".econst"\n');
    fprintf(fid,'\n');
    % Start the vector
    fprintf(fid, ['_test_quotient_',num2str(N),':\n']);
    S = sprintf(['    .',asm_quo_type,' %12d, %12d, %12d, %12d \n'], QUO);
    fprintf(fid,S);
    fprintf(fid, '\n\n');
    S = sprintf(['    .',asm_rem_type,' %12d, %12d, %12d, %12d \n'], REM);
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
    fprintf(fid,['//! \\brief  FID Input Vectors (',num2str(N),') \n']);
    fprintf(fid,'//! \\author Vishal Coelho \n');
    fprintf(fid,['//! \\date   ',date,'\n//! \n//\n']);
    fprintf(fid,'//  Group:            C2000\n');
    fprintf(fid,'//  Target Family:    $DEVICE$\n//\n');
    fprintf(fid,['// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,'// ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    fprintf(fid,'// \n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    fprintf(fid, '#include <stdint.h>\n\n');
    % Start the vector
    fprintf(fid, ['const ',c_num_type,' test_dividend','[',num2str(N),...
        '] = {\n']);
    S = sprintf(c_num_pfmt, num_r);
    fprintf(fid,S);
    fprintf(fid,'}; \n\n');
    fprintf(fid, ['const ',c_den_type,' test_divisor','[',num2str(N),...
        '] = {\n']);
    S = sprintf(c_den_pfmt, den_r);
    fprintf(fid,S);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end
if (~strcmp(OutFn,'NULL') && strcmp(ext,'.c'))
    fid = fopen(OutFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,['//! \\file ',OutFn,'\n']);
    fprintf(fid,['//! \\brief  FID Ouput Vector (',num2str(N),') \n']);
    fprintf(fid,'//! \\author Vishal Coelho \n');
    fprintf(fid,['//! \\date   ',date,'\n//! \n//\n']);
    fprintf(fid,'//  Group:            C2000\n');
    fprintf(fid,'//  Target Family:    $DEVICE$\n//\n');
    fprintf(fid,['// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,'// ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    fprintf(fid,'// \n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    fprintf(fid, '#include <stdint.h>\n\n');
    
    % Start the vector
    fprintf(fid, ['const ',c_quo_type,' test_quotient','[',num2str(N),...
        '] = {\n']);
    S = sprintf(c_quo_pfmt, QUO);
    fprintf(fid,S);
    fprintf(fid,'}; \n\n');
    fprintf(fid, ['const ',c_rem_type,' test_remainder','[',num2str(N),...
        '] = {\n']);
    S = sprintf(c_rem_pfmt, REM);
    fprintf(fid,S);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end
%%
% End of file
