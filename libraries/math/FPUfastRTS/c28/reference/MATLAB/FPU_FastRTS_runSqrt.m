%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate Square Root Input/Ouput Vectors
% \author Vishal Coelho
% \date   08/21/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Square Root Algorithm
% The algorithm begins by taking the inverse square root of the operand.
% Note that on the C28x this is an estimated value (EISQRTF32)
%
% $$Y_{e} = Estimate(\frac{1}{sqrt{X}}) $$
%
% This is followed by multiple iterations of the Newton-Raphson iterations
% to arrive at an accurate result. For single precision operands, 2
% iterations are required, while for double precision operands 4 iterations
% are required.
%
% References:
% Wikipedia (<https://en.wikipedia.org/wiki/Newton%27s_method>)
% Wikipedia (<https://en.wikipedia.org/wiki/Methods_of_computing_square_roots>)
%
% Newton's approximations of the root of a polynomial is,
%
% $$x_{n+1} = x_{n} - \frac{f(x_{n})}{f'(x_{n})}$$
%
% Since we are attempting to find the square root of some real positive
% number, S, we use Newton's Iterative method to approximate 
% $\frac{1}{\sqrt{S}}$ first and them multiply by $S$ to get $\sqrt{S}$
%
% To do this, we try to solve $\frac{1}{x^{2}} - S = 0$. The advantage of 
% trying to solve this equation over $x^{2}-\frac{1}{S}=0$ is that we dont end
% up having to do any division.
%
% Applying Newton's method we get
% $$x_{n+1} = \frac{1}{2}x_{n}(3 - S{\times}x_{n}^{2}) $$

%% Required Parameters
% * *N*, desired size of the lookup table
% * *SWP* , array indicating the desired input sweep, e.g. [0.002, +pi]
% positive non-zero arguments only. Try and keep the sweep within a decade
% else you will see a very large step between successive values
%
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *Filename(input)*, name of file to write the input vector to
% * *Filename(output)*, name of file to write the output vector to
% The filenames can only have a .asm or .c extension
%
%% Returns
% *SQRT*, the calculated Square Root
% *REF*,  the reference Square Root (calculated using matlab in-built
% functions)
% *AERR*, Absolute error
% *RERR*, Relative error

%% Function Prototype
%  An Example: Generate a 512 input/output
%  vector
%
%  [S,R,AE,RE] = FPU_FastRTS_runSqrt(512, [1,10], 'TYPE_FLOAT',
%  'sqrtInput.asm', 'sqrtOutput.asm')
% 
% or
%
%  [S,R,AE,RE] = FPU_FastRTS_runSqrt(512, [exp(1), pi], 'TYPE_FLOAT',
%  'sqrtInput.c', 'sqrtOutput.c')
% 
function [SQRT,REF,AERR,RERR] = FPU_FastRTS_runSqrt(N, SWP, varargin)
%% Parse Arguments
nOptArgs = 3;
numvarargs = length(varargin);
if numvarargs > nOptArgs
    error('myfunc:TooManyInputs',...
        ['requires at most ',num2str(nOptArgs),' optional input(s)']);
end

% Assign optional argument
optArgs = {'TYPE_FLOAT','NULL','NULL'};

% Check contents of varargin: if empty skip
newVals = cellfun(@(x) ~isempty(x), varargin);

% now put these defaults into the valuesToUse cell array,
% and overwrite the ones specified in varargin.
optArgs(newVals) = varargin(newVals);
% or ...
% [optargs{1:numvarargs}] = varargin{:};

% Place optional args in memorable variable names
[precision, InFn, OutFn] = optArgs{:};

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
assert((SWP(1) > 0) && (SWP(2) > SWP(1)),...
    'Sweep must be over the postive range');

%% Calculate the Square Root for the sweep range and plot the response
op = SWP(1);
step = (SWP(2)-SWP(1))/ N;
RERR = zeros(1,N);
AERR = zeros(1,N);
REF = zeros(1,N);
SQRT = zeros(1,N); 
t   = zeros(1,N);
for i = 1 : N
    % Take an estimate of the inverse sqrt. Now since this is 
    % MATLAB and not the C28x, the isqrt will be accurate and
    % not an estimate - this will have to be replaced by a function
    % that does an estimate instead
    xn = 1/sqrt(op);
    %NR iterations 2 for float, 4 for double
    xn = xn*(1.5 - xn*xn*op*0.5);
    xn = xn*(1.5 - xn*xn*op*0.5);
if (strcmp(precision,'TYPE_DOUBLE'))    
    xn = xn*(1.5 - xn*xn*op*0.5);
    xn = xn*(1.5 - xn*xn*op*0.5);
end
    SQRT(i) = xn * op;
    REF(i) = sqrt(op);
    AERR(i) = abs(REF(i) - SQRT(i));
    RERR(i) = AERR(i)/max(abs(op), abs(REF(i)));
    t(i)  = op;
    op  = op + step;
end
figure; 
subplot(2,2,1), plot(t,SQRT,'-b',t,REF,'--r'),...
    legend('Newton-Raphson Square Root','Reference MATLAB Square Root'),...
    xlabel('theta'), ylabel('Amplitude'),...
    title('Square Root'), grid on;
subplot(2,2,2), plot(t,AERR),xlabel('x'), ylabel('Amplitude'),
    title('Absolute Error'), grid on;
subplot(2,2,3), plot(t,RERR),xlabel('x'), ylabel('Amplitude'),
    title('Relative Error'), grid on;
    
%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',InFn,'\n']);
    fprintf(fid,[';;! \\brief  Square Root Input Vector (',num2str(N),') \n']);
    fprintf(fid,';;! \\author Vishal Coelho \n');
    fprintf(fid,[';;! \\date   ',date,'\n;;! \n;;\n']);
    fprintf(fid,';;  Group:\t\t\tC2000\n');
    fprintf(fid,';;  Target Family:\t$DEVICE$\n;;\n');
    fprintf(fid,[';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,';; ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,';; \n');
    fprintf(fid,';; \n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    fprintf(fid,['\t.def\t_test_input',num2str(N),'\n']);
    fprintf(fid,'\n');
    fprintf(fid,'\t.sect\t".econst"\n');
    fprintf(fid,'\n');
    % Start the vector
    fprintf(fid, ['_test_input',num2str(N),':\n']);
    if (strcmp(precision,'TYPE_FLOAT'))
        S = sprintf('\t.float\t%15.12e, %15.12e, %15.12e, %15.12e \n',t);
    else
        S = sprintf('\t.xldouble\t%15.12e, %15.12e, %15.12e, %15.12e \n',t);
    end
    fprintf(fid,S);
    fprintf(fid,'\n;; End of File\n');
    fclose(fid);
end
if (~strcmp(OutFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(OutFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',OutFn,'\n']);
    fprintf(fid,[';;! \\brief  Square Root Output Vector (',num2str(N),') \n']);
    fprintf(fid,';;! \\author Vishal Coelho \n');
    fprintf(fid,[';;! \\date   ',date,'\n;;! \n;;\n']);
    fprintf(fid,';;  Group:\t\t\tC2000\n');
    fprintf(fid,';;  Target Family:\tF2837x\n;;\n');
    fprintf(fid,[';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,';; ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,';; \n');
    fprintf(fid,';; \n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    fprintf(fid,['\t.def\t_test_golden',num2str(N),'\n']);
    fprintf(fid,'\n');
    fprintf(fid,'\t.sect\t".econst"\n');
    fprintf(fid,'\n');
    % Start the vector
    fprintf(fid, ['_test_golden',num2str(N),':\n']);
    if (strcmp(precision,'TYPE_FLOAT'))
        S = sprintf('\t.float\t%15.12e, %15.12e, %15.12e, %15.12e \n',SQRT);
    else
        S = sprintf('\t.xldouble\t%15.12e, %15.12e, %15.12e, %15.12e \n',SQRT);
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
    fprintf(fid,['//! \\brief  Square Root Input Vector (',num2str(N),') \n']);
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
    
    % Start the vector
    fprintf(fid, ['const ',ftype,' test_input[',num2str(N),...
        '] = {\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        S = sprintf('\t%14.11eF, %14.11eF, %14.11eF, \n',t);
    else
        S = sprintf('\t%15.12eL, %15.12eL, %15.12eL, \n',t);
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
    fprintf(fid,['//! \\brief  Square Root Ouput Vector (',num2str(N),') \n']);
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
    
    % Start the vector
    fprintf(fid, ['const ',ftype,' test_golden[',num2str(N),...
        '] = {\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        S = sprintf('\t%14.11eF, %14.11eF, %14.11eF, \n',SQRT);
    else
        S = sprintf('\t%15.12eL, %15.12eL, %15.12eL, \n',SQRT);
    end
    fprintf(fid,S);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end  
%%
% End of file
