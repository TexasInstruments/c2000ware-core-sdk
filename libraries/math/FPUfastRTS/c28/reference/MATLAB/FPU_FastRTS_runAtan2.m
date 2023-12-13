%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate Arctan2 Input/Ouput Vectors
% \author Vishal Coelho
% \date   08/26/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Arctan2 Algorithm
% This is a table lookup algorithm for atan(y/x). The steps are as follows,
%
% * Establish the argument as a ratio,
%
%   if (|x| >= |y|)
%      N = |y|
%      D = |x|
%   else
%      N = |x|
%      D = |y|
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
%   if((x>=0 && y>=0) && (|x|>=|y|) )
%
% $$\theta = \arctan(\frac{|y|}{|x|})$$
%
%   if((x>=0 && y>=0) && (|x|<|y|) )
%
% $$\theta = \frac{\pi}{2} - \arctan(\frac{|x|}{|y|})$$
%
%   if((x<0 && y>=0) && (|x|<|y|) )
%
% $$\theta = \frac{\pi}{2} + \arctan(\frac{|x|}{|y|})$$
%
%   if((x<0 && y>=0) && (|x|>=|y|) )
%
% $$\theta = \pi - \arctan(\frac{|y|}{|x|})$$
%
%   if( y < 0 )
%
% $$\theta = -\theta$$
%
%% Required Parameters
% * *N*, desired size of the input/output vector
% * *SWPY* , array indicating the desired input sweep, e.g. [-pi, +pi]
% * *SWPX* , array indicating the desired input sweep, e.g. [-pi, +pi]
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
% *ATAN2*, the calculated arctangent(y/x)
% *REF*, the reference arctangent2 (calculated using matlab in-built functions)
% *AERR*, Absolute error
% *RERR*, Relative error

%% Function Prototype
%  An Example: Generate a 512 arctangent input/output vector
%
%  [A2,R,AE,RE] = FPU_FastRTS_runAtan2(64, [-1,0.9], [-0.5,0.24], 'TYPE_FLOAT',
%  'atan2Table.asm', 'atan2Input.asm', 'atan2Output.asm')
% 
% or
%
%  [A2,R,AE,RE] = FPU_FastRTS_runAtan2(64, [-1,0.9], [-0.5,0.24], 'TYPE_FLOAT',
%  'atan2Table.c', 'atan2Input.c', 'atan2Output.c')
% 
function [ATAN2,REF,AERR,RERR] = FPU_FastRTS_runAtan2(N, SWPY, SWPX, varargin)
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
SWP_s  = size(SWPY);
assert((SWP_s(1) == 1 && SWP_s(2) == 2),...
    'SWPY needs to be 1x2');
SWP_s  = size(SWPX);
assert((SWP_s(1) == 1 && SWP_s(2) == 2),...
    'SWPX needs to be 1x2');

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

ystep = (SWPY(2)-SWPY(1))/N;
xstep = (SWPX(2)-SWPX(1))/N;
y     = SWPY(1);
x     = SWPX(1);
RERR  = zeros(1,N);
AERR  = zeros(1,N);
REF   = zeros(1,N);
ATAN2  = zeros(1,N); 
t     = zeros(1,N);
IN    = zeros(1, 2*N);
j     = 1;
for i = 1 : N
    if(abs(x) >= abs(y))
        n = abs(y);
        d = abs(x);
    else
        n = abs(x);
        d = abs(y);
    end
    R = n/d;
    k = (floor(R * TABLE_SIZE) * NTUPLE)+1;
    A0 = T(k);
    A1 = T(k+1);
    A2 = T(k+2);
    TEMP = A0 + R*(A1 + A2*R);
% <<VC150826 - these conditions were in the prologue comments in the legacy
% assembly code
%     if((y >= 0 && x >= 0) && (abs(x) >= abs(y)))
% VC150826>>
    if((x >= 0) && (abs(x) >= abs(y)))
        % First Quadrant (upto pi/4)
        % calculated arctan(|y|/|x|)
        ATAN2(i) = TEMP;
    end
% <<VC150826 - these conditions were in the prologue comments in the legacy
% assembly code
%     if((y >= 0 && x >= 0) && (abs(x) < abs(y)))
% VC150826>>
   if((x >= 0) && (abs(x) < abs(y)))
        % First Quadrant (pi/4 to pi/2)
        % calculated arctan(|x|/|y|)
        % identitiy: arctan(y/x) = pi/2 - arctan(|x|/|y|)
        ATAN2(i) = pi/2 - TEMP;
   end
% <<VC150826 - these conditions were in the prologue comments in the legacy
% assembly code
%     if ((y >= 0 && x < 0) && (abs(x) < abs(y)))
% VC150826>>
    if ((x < 0) && (abs(x) < abs(y)))
        % Second quadrant (pi/2 to 3pi/4) (x <0 && |y| > |x|)
        % calculated arctan(|x|/|y|)
        % identitiy: arctan(y/x) = pi/2 - arctan(-|x|/|y|)
        %                        = pi/2 - -arctan(|x|/|y|)
        %                        = pi/2 + arctan(|x|/|y|)
        ATAN2(i) = pi/2 + TEMP;
    end
% <<VC150826 - these conditions were in the prologue comments in the legacy
% assembly code
%     if ((y >= 0 && x < 0) && (abs(x) >= abs(y)))
% VC150826>>
    if ((x < 0) && (abs(x) >= abs(y)))
        % Second quadrant (3pi/4 to pi) (x <0 && |y| <= |x|)
        % calculated arctan(|y|/|x|)
        % identitiy: arctan(y/-x) = -arctan(|y|/|x|)
        % We want to represent angles in the range [0,pi] as
        % positive, so we use this instead
        % identitiy: arctan(y/-x) = pi - arctan(|y|/|x|)
        ATAN2(i) = pi - TEMP;
    end
    if ( y < 0 ) 
        % Third and Fourth quadrants
% <<VC150826 - these conditions were in the prologue comments in the legacy
% assembly code
%         ATAN2(i) = -TEMP;
% VC150826>>
        ATAN2(i) = -ATAN2(i);

    end
    REF(i) = atan2(y,x);
    AERR(i) = abs(REF(i) - ATAN2(i));
    RERR(i) = AERR(i)/max(abs(y), abs(REF(i)));
    t(i)  = i;
    IN(j) = y;
    IN(j+1) = x;
    j = j + 2;
    y  = y + ystep;
    x  = x + xstep;
end
figure; 
subplot(2,2,1), plot(t,ATAN2,'-b',t,REF,'--r'), legend('Table Lookup Arctangent',...
    'Reference MATLAB Arctangent(y,x)'), xlabel('i'), ylabel('theta'),
    title('Arctangent(y,x): Table Lookup'), grid on;
subplot(2,2,2), plot(t,AERR),xlabel('i'), ylabel('theta'),
    title('Absolute Error'), grid on;
subplot(2,2,3), plot(t,RERR),xlabel('i'), ylabel('theta'),
    title('Relative Error'), grid on;
    
%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',InFn,'\n']);
    fprintf(fid,[';;! \\brief  Arctangent(y,x) Input Vector (',num2str(N),') \n']);
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
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',OutFn,'\n']);
    fprintf(fid,[';;! \\brief  Arctangent(y,x) Output Vector (',num2str(N),') \n']);
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
        S = sprintf('\t.float\t%15.12f, %15.12f, %15.12f, %15.12f \n',ATAN2);
    else
        S = sprintf('\t.xldouble\t%15.12f, %15.12f, %15.12f, %15.12f \n',ATAN2);
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
    fprintf(fid,['//! \\brief  Arctangent(y,x) Input Vector (',num2str(N),') \n']);
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
    fprintf(fid, ['const ',ftype,' test_input[',num2str(2*N),...
        '] = {\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',IN);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',IN);
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
    fprintf(fid,['//! \\brief  Arctangent(y,x) Ouput Vector (',num2str(N),') \n']);
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
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',ATAN2);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',ATAN2);
    end
    fprintf(fid,S);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end  
%%
% End of file
