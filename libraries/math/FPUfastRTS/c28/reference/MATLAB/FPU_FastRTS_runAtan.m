%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate Arctan Input/Ouput Vectors
% \author Vishal Coelho
% \date   08/26/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Arctan Algorithm
% This is a table lookup algorithm for atan(x). The steps are as follows,
%
% * Establish the argument as a ratio,
%
%   if (1.0 >= |x|)
%      N = |x|
%      D = 1.0
%   else
%      N = 1.0
%      D = |x|
%
% * The ratio, $r = \frac{N}{D}$. Its range is always 0.0 to 1.0
% * Use $r \times TABLE\_SIZE \times N\_TUPLES$ as the index into the 
% table. The table is a set of 64 3-tuples, $A_{0}$, $A_{1}$, and $A_{2}$
% * Calculate the angle as follows
% 
% $$\arctan(r) = A_{0} + r\times (A_{1} + A_{2}\times r)$$
%
% * The final angle, $\theta$, is determined as follows
%
%   if( x >= 0 and 1.0 >= |x| )
%
% $$\theta = \arctan(\frac{|x|}{1.0})$$
%
%   if( x >= 0 and 1.0 < |x| )
%
% $$\theta = \frac{\pi}{2} - \arctan(\frac{1.0}{|x|})$$
%
%   if( x < 0 )
%
% $$\theta = -\theta$$
%
%% Required Parameters
% * *N*, desired size of the input/output vector
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
% *ATAN*, the calculated arctangent
% *REF*, the reference arctangent (calculated using matlab in-built functions)
% *AERR*, Absolute error
% *RERR*, Relative error

%% Function Prototype
%  An Example: Generate a 512 arctangent input/output vector
%
%  [A,R,AE,RE] = FPU_FastRTS_runAtan(64, [-1,1], 'TYPE_FLOAT',
%  'atan2Table.asm', 'atanInput.asm', 'atanOutput.asm')
% 
% or
%
%  [A,R,AE,RE] = FPU_FastRTS_runAtan(64, [-1,0.9], 'TYPE_FLOAT',
%  'atan2Table.c', 'atanInput.c', 'atanOutput.c')
% 
function [ATAN,REF,AERR,RERR] = FPU_FastRTS_runAtan(N, SWP, varargin)
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
%     T = FPU_FastRTS_genTableArctan(N, precision, TblFn);
    T = FPU_FastRTS_genTableArctan(64, precision, TblFn);
else
%     T = FPU_FastRTS_genTableArctan(N);
    T = FPU_FastRTS_genTableArctan(64);
end

%% Calculate the Arctan for the sweep range and plot the response

% TABLE_SIZE = N;
TABLE_SIZE = 64;
NTUPLE = 3;

istep = (SWP(2)-SWP(1))/N;
x     = SWP(1);
RERR  = zeros(1,N);
AERR  = zeros(1,N);
REF   = zeros(1,N);
ATAN  = zeros(1,N); 
t     = zeros(1,N);
for i = 1 : N
    if(1.0 >= abs(x))
        n = abs(x);
        d = 1.0;
    else
        n = 1.0;
        d = abs(x);
    end
    R = n/d;
    k = (floor(R * TABLE_SIZE) * NTUPLE)+1;
    A0 = T(k);
    A1 = T(k+1);
    A2 = T(k+2);
    TEMP = A0 + R*(A1 + A2*R);
    if(1.0 >= abs(x))
        % First Quadrant (upto pi/4)
        ATAN(i) = TEMP;
    end
    if (1.0 < abs(x))
        % First Quadrant (pi/4 to pi/2)
        % identitiy: arctan(x) = pi/2 - arctan(1/x)
        ATAN(i) = pi/2 - TEMP;
    end
    if (x < 0)
        % Second and fourth quadrants
        ATAN(i) = -ATAN(i);
    end
    REF(i) = atan(x);
    AERR(i) = abs(REF(i) - ATAN(i));
    RERR(i) = AERR(i)/max(abs(x), abs(REF(i)));
    t(i)  = x;
    x  = x + istep;
end
figure; 
subplot(2,2,1), plot(t,ATAN,'-b',t,REF,'--r'), legend('Table Lookup Arctangent',...
    'Reference MATLAB Arctangent'), xlabel('x'), ylabel('theta'),
    title('Arctangent: Table Lookup'), grid on;
subplot(2,2,2), plot(t,AERR),xlabel('x'), ylabel('theta'),
    title('Absolute Error'), grid on;
subplot(2,2,3), plot(t,RERR),xlabel('x'), ylabel('theta'),
    title('Relative Error'), grid on;
    
%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',InFn,'\n']);
    fprintf(fid,[';;! \\brief  Arctangent Input Vector (',num2str(N),') \n']);
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
    fprintf(fid,[';;! \\brief  Arctangent Output Vector (',num2str(N),') \n']);
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
        S = sprintf('\t.float\t%15.12f, %15.12f, %15.12f, %15.12f \n',ATAN);
    else
        S = sprintf('\t.xldouble\t%15.12f, %15.12f, %15.12f, %15.12f \n',ATAN);
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
    fprintf(fid,['//! \\brief  Arctangent Input Vector (',num2str(N),') \n']);
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
    fprintf(fid,['//! \\brief  Arctangent Ouput Vector (',num2str(N),') \n']);
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
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',ATAN);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',ATAN);
    end
    fprintf(fid,S);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end  
%%
% End of file
