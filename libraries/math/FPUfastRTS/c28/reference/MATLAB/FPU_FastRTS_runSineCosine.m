%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate SineCosine Input/Ouput Vectors
% \author Vishal Coelho
% \date   08/20/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Algorithm
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
% * We approximate the Cosine at $\theta_{int}$ using the Taylor's Series 
% Expansion
%
% $$f(x) = \sum\limits_{n=0}^{\infty}\frac{f^{n}(a)(x - a)^{n}}{n!}$$
%
% The exapansion is as follows
%
% $$\cos(\theta) = \cos(\theta_{int}) +(-\sin(\theta_{int})(\theta -
% \theta_{int}) - \frac{\cos(\theta_{int})(\theta-\theta_{int})^2}{2!}
% + \frac{\sin(\theta_{int})(\theta - \theta_{int})^3}{6!}$$
%
% Note that $\theta = \theta_{int} + \theta_{frac}$, and 
% $cos(\theta_{int})\equiv C[k]$, $sin(\theta_{int})\equiv S[k]$ , where
% *C* and *S* are the Sine and Cosine tables and *k* is the table index. We
% finally end up with these equations
%
% $$\sin(\theta) = S[k] + x\times (C[k] + x\times (-0.5\times S[k] -
% 0.166667\times x \times C[k])))$$
%
% $$\cos(\theta) = C[k] + x\times (-S[k] + x\times (-0.5\times C[k] +
% 0.166667\times x \times S[k])))$$
%
%% Required Parameters
% * *N*, desired size of the lookup table
% * *SWP* , array indicating the desired input sweep, e.g. [-pi, +pi]
%
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *whofirst*, (opt) can be 'SINE_FIRST' or 'COSINE_FIRST', defaults to
%    sine values being stored first in the output file array
% * *Filename(table)*, name of file to write the table to. If defined it is 
%    passed on to the genTable function
% * *Filename(input)*, name of file to write the input vector to
% * *Filename(output)*, name of file to write the output vector to
% The filenames can only have a .asm or .c extension
%
%% Returns
% *SIN*, the calculated Sine
% *COS*, the calculated cosine
% *REFS*, the reference Sine (calculated using matlab in-built functions)
% *REFC*, the reference cosine (calculated using matlab in-built functions)
% *AERRS*, Absolute error (Sine)
% *RERRS*, Relative error (Sine)
% *AERRC*, Absolute error (Cosine)
% *RERRC*, Relative error (Cosine)
%% Function Prototype
%  An Example: Generate a 512 sine/cosine table (640 entries), input/output
%  vector. The ouput vector will have the cosine value first followed 
%  by the sine.
%
%  [S,C,RS,RC,AES,RES,AEC,REC] = FPU_FastRTS_runSineCosine(512, [-pi,pi], 
%  'TYPE_FLOAT', 'COSINE_FIRST', 'sincosTable.asm', 
%  'sincosInput.asm', 'sincosOutput.asm')
% 
% or
%
%  [S,C,RS,RC,AES,RES,AEC,REC] = FPU_FastRTS_runSineCosine(512, [-pi,pi],
%  'TYPE_FLOAT', 'SINE_FIRST', 'sincosTable.c', 
%  'sincosInput.c', 'sincosOutput.c')
% 
function [SIN,COS,REFS,REFC,AERRS,RERRS,AERRC,RERRC] =...
          FPU_FastRTS_runSineCosine(N, SWP, varargin)
%% Parse Arguments
nOptArgs = 5;
numvarargs = length(varargin);
if numvarargs > nOptArgs
    error('myfunc:TooManyInputs',...
        ['requires at most ',num2str(nOptArgs),' optional input(s)']);
end

% Assign optional argument
optArgs = {'TYPE_FLOAT','SINE_FIRST','NULL', 'NULL','NULL'};

% Check contents of varargin: if empty skip
newVals = cellfun(@(x) ~isempty(x), varargin);

% now put these defaults into the valuesToUse cell array,
% and overwrite the ones specified in varargin.
optArgs(newVals) = varargin(newVals);
% or ...
% [optargs{1:numvarargs}] = varargin{:};

% Place optional args in memorable variable names
[precision, whofirst, TblFn, InFn, OutFn] = optArgs{:};

% filenames must have an asm or h extenstion
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
if (strcmp(whofirst,'COSINE_FIRST'))
    outfileString = 'The data is organized cosine first';
elseif (strcmp(whofirst,'SINE_FIRST'))
    outfileString = 'The data is organized sine first';
else
    assert(0,'argument can be "SINE_FIRST" or "COSINE_FIRST"');
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
    b0 = -1/factorial(1);
    b1 = -1/factorial(2);
    b2 =  1/factorial(3);
else %precision = double
    a0 =  1/factorial(1);
    a1 = -1/factorial(2);
    a2 = -1/factorial(3);
    a3 =  1/factorial(4);
    a4 =  1/factorial(5);
    a5 = 0;
    %     a5 = -1/factorial(6);
    b0 = -1/factorial(1);
    b1 = -1/factorial(2);
    b2 =  1/factorial(3);
    b3 =  1/factorial(4);
    b4 = -1/factorial(5);
    b5 = 0;
    %     b5 = -1/factorial(6);
end
%% Calculate the Sine and Cosine for the sweep range
istep = (SWP(2)-SWP(1))/N;
tstep = 2*pi/N; %The table step
theta = SWP(1);
SIN = zeros(1,N); 
RERRS = zeros(1,N);
AERRS = zeros(1,N);
REFS = zeros(1,N);
COS = zeros(1,N);
RERRC = zeros(1,N);
AERRC = zeros(1,N);
REFC = zeros(1,N);
COMB = zeros(1,2*N);
REF = zeros(1,2*N);
t   = zeros(1,N);
j = 1;
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
    REFS(i) = sin(theta);
    AERRS(i) = abs(REFS(i) - SIN(i));
    RERRS(i) = AERRS(i)/max(abs(theta), abs(REFS(i)));
    if (strcmp(precision,'TYPE_FLOAT'))
        COS(i) = (C(k) + ...
            x*(b0*S(k) + ...
            x*(b1*C(k) + ...
            x*(b2*S(k)))));
    else %precision = double
        COS(i) = (C(k) + ...
            x*(b0*S(k) + ...
            x*(b1*C(k) + ...
            x*(b2*S(k) + ...
            x*(b3*C(k) + ...
            x*(b4*S(k) + ...
            x*(b5*C(k))))))));
    end
    REFC(i) = cos(theta);
    AERRC(i) = abs(REFC(i) - COS(i));
    RERRC(i) = AERRC(i)/max(abs(theta), abs(REFC(i)));
    if (strcmp(whofirst,'SINE_FIRST'))
        COMB(j)   = SIN(i);
        COMB(j+1) = COS(i);
        REF(j)    = REFS(i);
        REF(j+1)  = REFC(i);
    else
        COMB(j)   = COS(i);
        COMB(j+1) = SIN(i);
        REF(j)    = REFC(i);
        REF(j+1)  = REFS(i);
    end
    j = j + 2;
    t(i)  = theta;
    theta  = theta + istep;
end
%% Plot of the Sine
figure; 
subplot(2,2,1), plot(t,SIN,'-b',t,REFS,'--r'), legend('Table Lookup Sine',...
    'Reference MATLAB Sine'), xlabel('theta'), ylabel('Amplitude'),
    title('Sine: Taylor Series Expansion and Table Lookup'), grid on;
subplot(2,2,2), plot(t,AERRS),xlabel('theta'), ylabel('Amplitude'),
    title('Absolute Error'), grid on;
subplot(2,2,3), plot(t,RERRS),xlabel('theta'), ylabel('Amplitude'),
    title('Relative Error'), grid on;
    
%% Plot of the Cosine
figure;
subplot(2,2,1), plot(t,COS,'-b',t,REFC,'--r'), legend('Table Lookup Cosine',...
    'Reference MATLAB Cosine'), xlabel('theta'), ylabel('Amplitude'),
    title('Cosine: Taylor Series Expansion and Table Lookup'), grid on;
subplot(2,2,2), plot(t,AERRC),xlabel('theta'), ylabel('Amplitude'),
    title('Absolute Error'), grid on;
subplot(2,2,3), plot(t,RERRC),xlabel('theta'), ylabel('Amplitude'),
    title('Relative Error'), grid on;
%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',InFn,'\n']);
    fprintf(fid,[';;! \\brief  Sine/Cosine Input Vector (',num2str(N),') \n']);
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
    fprintf(fid,[';;! \\brief  Sine/Cosine Output Vector (',num2str(N),') \n']);
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
    fprintf(fid,[';; ',outfileString,'\n']);
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
    fprintf(fid,['//! \\brief  Sine/Cosine Input Vector (',num2str(N),') \n']);
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
    fprintf(fid,['//! \\brief  Sine/Cosine Ouput Vector (',num2str(N),') \n']);
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
    fprintf(fid,['// ',outfileString,'\n']);
    % Start the vector
    fprintf(fid, ['const ',ftype,' test_golden[',num2str(2*N),...
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
