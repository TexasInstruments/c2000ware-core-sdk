%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate Cosine Input/Ouput Vectors
% \author Vishal Coelho
% \date   11/07/2016
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The CORDIC Algorithm
% This is a table lookup algorithm where we start on the x-axis at the unit
% circle and rotate counter clockwise until we meet our desired angle, the
% x-component is the cosine of the angle, while the y-component is the sine
% of the angle
%
%% Required Parameters
% * *N*, desired test vector size (<= 2048)
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
% *COS*, the calculated Cosine
% *REF*, the reference Cosine (calculated using matlab in-built functions)
% *AERR*, Absolute error
% *RERR*, Relative error

%% Function Prototype
%  An Example: Generate a 64 Cosine input/output vector along with a 64
%  entry CORDIC arctangents and scale factor tables.
%
%  [C,R,AE,RE] = FPU_FastRTS_CORDIC_runCosine(64, [-pi,pi], 'TYPE_FLOAT',
%  'FPU_FastRTS_cordicTable.asm', 'cordic_cosInput.asm', 
%  'cordic_cosOutput.asm')
% 
% or
%
%  [C,R,AE,RE] = FPU_FastRTS_CORDIC_runCosine(64, [-pi,pi], 'TYPE_FLOAT',
%  'FPU_FastRTS_cordicTable.c', 'cordic_cosInput.c', 'cordic_cosOutput.c')
% 
function [COS,REF,AERR,RERR] = FPU_FastRTS_CORDIC_runCosine(N, SWP, varargin)
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
SWP_s  = size(SWP);
assert((SWP_s(1) == 1 && SWP_s(2) == 2),...
    'SWP needs to be 1x2');

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

%% Calculate the Cosine for the sweep range and plot the response
istep = (SWP(2)-SWP(1))/N;
theta = SWP(1);
RERR  = zeros(1,N);
AERR  = zeros(1,N);
REF   = zeros(1,N);
SIN   = zeros(1,N); COS = zeros(1,N); THETA_ERR = zeros(1,N);
t     = zeros(1,N);
for i = 1 : N
    % Calculate the Cosine for the current theta
    x0 = SCALEFACTOR(MAX_CORDIC_ITERATIONS); %Its 1/prod_k=0_N-1(K)
    y0 = 0;
    z0 = theta;
    
    [COS(i), SIN(i), THETA_ERR(i)] = FPU_FastRTS_runCORDICRotationMode(x0,...
        y0, z0, MAX_CORDIC_ITERATIONS, ATANFACTOR, SCALEFACTOR);
    
    REF(i)  = cos(theta);
    AERR(i) = abs(REF(i) - COS(i));
    RERR(i) = AERR(i)/max(abs(theta), abs(REF(i)));
    t(i)    = theta;
    theta   = theta + istep;
end
figure; 
subplot(2,2,1), plot(t,COS,'-b',t,REF,'--r'), legend('CORDIC Cosine',...
    'Reference MATLAB Cosine'), xlabel('theta'), ylabel('Amplitude'),
    title('Cosine: CORDIC'), grid on;
subplot(2,2,2), plot(t,AERR),xlabel('theta'), ylabel('Amplitude'),
    title('Absolute Error'), grid on;
subplot(2,2,3), plot(t,RERR),xlabel('theta'), ylabel('Amplitude'),
    title('Relative Error'), grid on;
    
%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,[HEAD_string                                    ,...
        ';;! \\file %s \n'                                      ,...
        ';;! \\brief  Cosine Input Vector (%s) \n'              ,...
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
    fprintf(fid,[HEAD_string                                    ,...
        ';;! \\file %s\n'                                       ,...
        ';;! \\brief  Cosine Output Vector (%s) \n'             ,...
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
        S = sprintf('\t.float\t%15.12f, %15.12f, %15.12f, %15.12f \n',COS);
    else
        S = sprintf('\t.xldouble\t%15.12f, %15.12f, %15.12f, %15.12f \n',COS);
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
                 '//! \\brief  Cosine Input Vector (%s) \n'              ,...
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
                '//! \\brief  Cosine Ouput Vector (%s) \n'              ,...
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
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',COS);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',COS);
    end
    fprintf(fid,S);
    fprintf(fid,['}; \n\n',...
                 '\n// End of File\n']);
    fclose(fid);
end  
%%
% End of file
