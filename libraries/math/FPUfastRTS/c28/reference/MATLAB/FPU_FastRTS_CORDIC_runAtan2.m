%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate Arctan Input/Ouput Vectors
% \author Vishal Coelho
% \date   11/08/2016
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The CORDIC Algorithm
% This is a table lookup algorithm where we start with the passed co-ordinates
% x and y and rotate clockwise until we land on the x-axis or as close to it, 
% the resulting rotation is the negative of the desired angle
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
% * Calculate the angle using the CORDIC vectoring mode
% 
% $$\theta = -z_{n} $$
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
% * *N*, desired test vector size (<= 2048)
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
%  An Example: Generate a 64 Arctan input/output vector along with a 64
%  entry CORDIC arctangents and scale factor tables.
%
%  [A2,R,AE,RE] = FPU_FastRTS_CORDIC_runAtan2(64, [-1,0.9], [-0.5,0.24], 
%  'TYPE_FLOAT', 'FPU_FastRTS_cordicTable.asm', 'cordic_atan2Input.asm', 
%  'cordic_atan2Output.asm')
% 
% or
%
%  [A2,R,AE,RE] = FPU_FastRTS_CORDIC_runAtan2(64, [-1,0.9], [-0.5,0.24], 
%  'TYPE_FLOAT', 'FPU_FastRTS_cordicTable.c', 'cordic_atan2Input.c', 
%  'cordic_atan2Output.c')
% 
function [ATAN2,REF,AERR,RERR] = FPU_FastRTS_CORDIC_runAtan2(N, SWPY, SWPX, varargin)
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

assert( N <= 2048 && N > 0, 'Valid values are between 1 and 2048');
MAX_CORDIC_ITERATIONS = 128;
assert( mod(N,2) == 0, 'N needs to be a power of 2');
SWP_s  = size(SWPY);
assert((SWP_s(1) == 1 && SWP_s(2) == 2),...
    'SWPY needs to be 1x2');
SWP_s  = size(SWPX);
assert((SWP_s(1) == 1 && SWP_s(2) == 2),...
    'SWPX needs to be 1x2');

%% Generate the lookup table and the coefficients
if (~strcmp(TblFn,'NULL'))
    [ATANFACTOR, SCALEFACTOR] = FPU_FastRTS_genCORDICTable(MAX_CORDIC_ITERATIONS,...
        precision, TblFn);
else
    [ATANFACTOR, SCALEFACTOR] = FPU_FastRTS_genCORDICTable(MAX_CORDIC_ITERATIONS);
end
figure;
subplot(2,1,1), plot(ATANFACTOR,'-b'), title('Arctangent Lookup Table');
subplot(2,1,2), plot(SCALEFACTOR,'-b'), title('Scaling Factor Lookup Table');

%% Calculate the Sine for the sweep range and plot the response

ystep = (SWPY(2)-SWPY(1))/N;
xstep = (SWPX(2)-SWPX(1))/N;
y     = SWPY(1);
x     = SWPX(1);
RERR  = zeros(1,N);
AERR  = zeros(1,N);
REF   = zeros(1,N);
ATAN2 = zeros(1,N); 
SIN   = zeros(1,N); 
COS   = zeros(1,N);
THETA = zeros(1,N);
t     = zeros(1,N);
IN    = zeros(1, 2*N);
j     = 1;

for i = 1 : N
    %Calculate theta for the current x, y
    if(abs(x) < abs(y))
        X_h  = abs(y);
        Y_h  = abs(x);
    else % abs(x) >= abs(y)
        X_h  = abs(x);
        Y_h  = abs(y);
    end
    [COS(i), SIN(i), THETA(i)] = FPU_FastRTS_runCORDICVectoringMode(X_h,...
        Y_h, 0, MAX_CORDIC_ITERATIONS, ATANFACTOR, SCALEFACTOR);

    if((x >= 0) && (abs(x) >= abs(y)))
        % First Quadrant (upto pi/4)
        % calculated arctan(|y|/|x|)
        ATAN2(i) = THETA(i);
    end

   if((x >= 0) && (abs(x) < abs(y)))
        % First Quadrant (pi/4 to pi/2)
        % calculated arctan(|x|/|y|)
        % identitiy: arctan(y/x) = pi/2 - arctan(|x|/|y|)
        ATAN2(i) = pi/2 - THETA(i);
   end

    if ((x < 0) && (abs(x) < abs(y)))
        % Second quadrant (pi/2 to 3pi/4) (x <0 && |y| > |x|)
        % calculated arctan(|x|/|y|)
        % identitiy: arctan(y/x) = pi/2 - arctan(-|x|/|y|)
        %                        = pi/2 - -arctan(|x|/|y|)
        %                        = pi/2 + arctan(|x|/|y|)
        ATAN2(i) = pi/2 + THETA(i);
    end
    if ((x < 0) && (abs(x) >= abs(y)))
        % Second quadrant (3pi/4 to pi) (x <0 && |y| <= |x|)
        % calculated arctan(|y|/|x|)
        % identitiy: arctan(y/-x) = -arctan(|y|/|x|)
        % We want to represent angles in the range [0,pi] as
        % positive, so we use this instead
        % identitiy: arctan(y/-x) = pi - arctan(|y|/|x|)
        ATAN2(i) = pi - THETA(i);
    end
    if ( y < 0 ) 
        % Third and Fourth quadrants
        ATAN2(i) = -ATAN2(i);

    end
    REF(i)  = atan2(y,x);
    AERR(i) = abs(REF(i) - ATAN2(i));
    RERR(i) = AERR(i)/max(abs(y), abs(REF(i)));
    t(i)    = i;
    IN(j)   = y;
    IN(j+1) = x;
    j       = j + 2;
    y       = y + ystep;
    x       = x + xstep;
end
figure; 
subplot(2,2,1), plot(t,ATAN2,'-b',t,REF,'--r'), legend('CORDIC Arctangent',...
    'Reference MATLAB Arctangent(y,x)'), xlabel('i'), ylabel('theta'),
    title('Arctangent(y,x): CORDIC'), grid on;
subplot(2,2,2), plot(t,AERR),xlabel('i'), ylabel('theta'),
    title('Absolute Error'), grid on;
subplot(2,2,3), plot(t,RERR),xlabel('i'), ylabel('theta'),
    title('Relative Error'), grid on;
    
    
%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,[HEAD_string                                            ,...
                ';;! \\file %s\n'                                       ,...
                ';;! \\brief  Arctangent(y,x) Input Vector (%s) \n'     ,...
                ';;! \\author Vishal Coelho \n'                         ,...
                ';;! \\date   %s \n;;! \n;;\n'                          ,...
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
                '\t.def\t_test_input%s\n'                               ,...
                '\n'                                                    ,...
                '\t.sect\t".econst"\n'                                  ,...
                '\n'], InFn, num2str(N), date, num2str(N));
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
    fprintf(fid,[HEAD_string                                             ,...
                 ';;! \\file %s\n'                                       ,...
                 ';;! \\brief  Arctangent(y,x) Output Vector (%s) \n'    ,...
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
    fprintf(fid,[HEAD_string                                            ,...
                '//! \\file %s\n'                                       ,...
                '//! \\brief  Arctangent(y,x) Input Vector (%s) \n'     ,...
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
                '\n'],InFn, num2str(N), date );
    
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
                '//! \\brief  Arctangent(y,x) Ouput Vector (%s) \n'     ,...
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
                
    % Start the vector
    fprintf(fid, ['const ',ftype,' test_golden[',num2str(N),...
        '] = {\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',ATAN2);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',ATAN2);
    end
    fprintf(fid,S);
    fprintf(fid,['}; \n\n',...
                 '\n// End of File\n']);
    fclose(fid);
end  
%%
% End of file
