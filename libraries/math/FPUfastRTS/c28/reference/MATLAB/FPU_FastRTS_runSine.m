%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate Sine Input/Ouput Vectors
% \author Vishal Coelho
% \date   08/13/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Sine Algorithm
% This is a table lookup algorithm where the size of the table, $N_{table}$
% is assumed to be some power of two. The steps are as follows,
%
% * The Angle, $\theta$ (in Radians), is used to determine the index into 
%   the SinCos Table as follows
%
% $$k = (N_{table}-1)\ \&\ (int(\theta\times\frac{N_{table}}{2\times\pi}))$$
% 
% If we take this index k and convert it back to radians we get 
%
% $$\theta_{int} = k \times \frac{2 \times \pi}{N_{table}}$$
%
% * There is a fractional portion that lands between two table entries, we 
%   calculate this
%
% $$\theta_{frac} = x = fractional(\theta\times\frac{N_{table}}{2\times\pi})
% \times \frac{(2\times\pi)}{N_{table}}$$
%
% * We approximate the Sine at $\theta_{int}$ using the Taylor's Series 
% Expansion
%
% $$f(x) = \sum\limits_{n=0}^{\infty}\frac{f^{n}(a)(x - a)^{n}}{n!}$$
%
% The exapansion is as follows
%
% $$\sin(\theta) = \sin(\theta_{int}) +(\cos(\theta_{int})(\theta -
% \theta_{int}) + \frac{-\sin(\theta_{int})(\theta-\theta_{int})^2}{2!}
% + \frac{-\cos(\theta_{int})(\theta - \theta_{int})^3}{6!}$$
%
% Note that $\theta = \theta_{int} + \theta_{frac}$, and 
% $cos(\theta_{int})\equiv C[k]$, $sin(\theta_{int})\equiv S[k]$ , where
% *C* and *S* are the Sine and Cosine tables and *k* is the table index. We
% finally end up with this equation
%
% $$\sin(\theta) = S[k] + x\times (C[k] + x\times (-0.5\times S[k] -
% 0.166667\times x \times C[k])))$$
%
%% Required Parameters
% * *N*, desired size of the lookup table
% * *SWP* , array indicating the desired input sweep, e.g. [-pi, +pi]
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
% *SIN*, the calculated Sine
% *REF*, the reference Sine (calculated using matlab in-built functions)
% *AERR*, Absolute error
% *RERR*, Relative error

%% Function Prototype
%  An Example: Generate a 512 sine/cosine table (640 entries), input/output
%  vector
%
%  [S,R,AE,RE] = FPU_FastRTS_runSine(512, [-pi,pi], 'TYPE_FLOAT',
%  'sincosTable.asm', 'sinInput.asm', 'sinOutput.asm')
% 
% or
%
%  [S,R,AE,RE] = FPU_FastRTS_runSine(512, [-pi,pi], 'TYPE_FLOAT',
%  'sincosTable.c', 'sinInput.c', 'sinOutput.c')
% 
function [SIN,REF,AERR,RERR] = FPU_FastRTS_runSine(N, SWP, varargin)
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

%% Generate the lookup table and the coefficients
if (~strcmp(TblFn,'NULL'))
    T = FPU_FastRTS_genTableSineCosine(N, precision, TblFn);
else
    T = FPU_FastRTS_genTableSineCosine(N);
end
% The cosine portion of the table
C = T(N/4+1 : N/4 + N + 1); 
% The sine portion of the table
S = T(1 : N + 1);

figure;
t = linspace(0,2*pi + 2*pi/N, N + 1);
subplot(2,1,1), plot(t,S,'-b'), title('Sine Lookup Table');
subplot(2,1,2), plot(t,C,'-b'), title('Cosine Lookup Table');
if (strcmp(precision,'TYPE_FLOAT'))
    a0 = single(1/factorial(1));
    a1 = single(-1/factorial(2));
    a2 = single(-1/factorial(3));
else %precision = double
    a0 =  1/factorial(1);
    a1 = -1/factorial(2);
    a2 = -1/factorial(3);
    a3 =  1/factorial(4);
    a4 =  1/factorial(5);
    a5 = 0;
%     a5 = -1/factorial(6);
end
%% Calculate the Sine for the sweep range and plot the response
istep = (SWP(2)-SWP(1))/N;
tstep = 2*pi/N; %The table step
theta = SWP(1);
RERR = zeros(1,N);
AERR = zeros(1,N);
REF = zeros(1,N);
SIN = zeros(1,N); 
t   = zeros(1,N);
for i = 1 : N
    % Calculate the Sine for the current theta
    k =  floor(abs(theta/tstep)) + 1; %the +1 accounts for the indexing from 1
    x_f = abs(theta)/tstep;
    x = (x_f - floor(x_f))* tstep; 
    if(theta < 0)
        sb = -1;
    else
        sb = 1;
    end
    
    if (strcmp(precision,'TYPE_FLOAT'))
        SIN(i) = sb*(S(k) + ...
            x*(a0*C(k) + ...
            x*(a1*S(k) + ...
            x*(a2*C(k)))));
    else %precision = double
        SIN(i) = sb*(S(k) + ...
            x*(a0*C(k) + ...
            x*(a1*S(k) + ...
            x*(a2*C(k) + ...
            x*(a3*S(k) + ...
            x*(a4*C(k) + ...
            x*(a5*S(k))))))));
    end
    REF(i) = sin(theta);
    AERR(i) = abs(REF(i) - SIN(i));
    RERR(i) = AERR(i)/max(abs(theta), abs(REF(i)));
    t(i)  = theta;
    theta  = theta + istep;
end
figure; 
subplot(2,2,1), plot(t,SIN,'-b',t,REF,'--r'), legend('Table Lookup Sine',...
    'Reference MATLAB Sine'), xlabel('theta'), ylabel('Amplitude'),
    title('Sine: Taylor Series Expansion and Table Lookup'), grid on;
subplot(2,2,2), plot(t,AERR),xlabel('theta'), ylabel('Amplitude'),
    title('Absolute Error'), grid on;
subplot(2,2,3), plot(t,RERR),xlabel('theta'), ylabel('Amplitude'),
    title('Relative Error'), grid on;
    
%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',InFn,'\n']);
    fprintf(fid,[';;! \\brief  Sine Input Vector (',num2str(N),') \n']);
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
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',OutFn,'\n']);
    fprintf(fid,[';;! \\brief  Sine Output Vector (',num2str(N),') \n']);
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
    fprintf(fid,HEAD_string);
    fprintf(fid,['//! \\file ',InFn,'\n']);
    fprintf(fid,['//! \\brief  Sine Input Vector (',num2str(N),') \n']);
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
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',t);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',t);
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
    fprintf(fid,['//! \\brief  Sine Ouput Vector (',num2str(N),') \n']);
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
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',REF);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',REF);
    end
    fprintf(fid,S);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end  
%%
% End of file
