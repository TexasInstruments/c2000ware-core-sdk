%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate Vector Routine Input/Ouput Vectors
% \author Vishal Coelho
% \date   09/30/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% The Vector Routines
%  The following routines are supported:
%
% # Absolute value (magnitude) of a complex vector
% # Inverse Absolute value (magnitude) of a complex vector
% # Add a complex scalar to a complex vector
% # Add a complex scalar to a complex vector
% # Multiply-and-Accumulate of a Real Vector and a Complex Vector
% # Multiply-and-Accumulate of a Complex Vector and a Complex Vector
% # Index of Maximum Value of a Real Array
% # Mean of Real and Imaginary Parts of a Complex Vector
% # Median of a Real Valued Array of Floats
% # Median of a Real Valued Array of Floats (Preserved Inputs)
% # Complex Multiply of Two Complex Values
% # Complex Multiply of Two Complex Vectors
% # Multiplication of a Complex Vector and the Complex Conjugate of
%   another Vector
% # Multiplication of two Real Matrices
% # Multiplication of a Real scalar and a Real Vector
% # Multiplication of a Real Scalar, a Real Vector, and another Real
%   Vector
% # Multiplication of a Real Vector and a Complex Vector
% # Sorts a real array
% # Rounding (Unbiased) of a Scalar
% # Subtraction of a Complex Scalar from a Complex Vector
% # Subtraction of a Complex Vector and another Complex Vector
%
%% Required Parameters
% * *routine*, must be one of the followin
% # 'absCV'
% # 'iabsCV'
% # 'addCStoCV'
% # 'addCVtoCV'
% # 'macRVbyCV'
% # 'macCVbyCV'
% # 'maxidxRV'
% # 'meanCV'
% # 'medianRV'
% # 'medianNoreorderRV'
% # 'mpyCSbyCS'
% # 'mpyCVbyCV'
% # 'mpyCVbyCVC'
% # 'mpyRMbyRM'
% # 'mpyRSbyRV'
% # 'mpyRSbyRVbyRV'
% # 'mpyRVbyCV'
% # 'qsortRV'
% # 'roundRS'
% # 'subCSfromCV'
% # 'subCVfromCV'
% * *N* size of the input vector (32=<N<=1024, even)
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *filetype*, (opt) can be 'FTYPE_C' or 'FTYPE_ASM', defaults to FTYPE_C
%% Returns
% *RES*, the calculated result

%% Function Prototype
%  An Example:
%  R = FPU_DSP_runVectorRoutines('meanCV', 64);
%  R = FPU_DSP_runVectorRoutines('meanCV', 64, 'TYPE_FLOAT', 'FTYPE_C');
%
function R = FPU_DSP_runVectorRoutines(fn, N, varargin)
%% Parse Arguments
assert((N >=32) && (N<=1024) && (mod(N,2)==0), ' 32<=N<=1024\n');

nOptArgs = 2;
numvarargs = length(varargin);
if numvarargs > nOptArgs
    error('myfunc:TooManyInputs',...
        ['requires at most ',num2str(nOptArgs),' optional input(s)']);
end

% Assign optional argument
optArgs = {'TYPE_FLOAT', 'FTYPE_C'};

% Check contents of varargin: if empty skip
newVals = cellfun(@(x) ~isempty(x), varargin);

% now put these defaults into the valuesToUse cell array,
% and overwrite the ones specified in varargin.
optArgs(newVals) = varargin(newVals);
% or ...
% [optargs{1:numvarargs}] = varargin{:};

% Place optional args in memorable variable names
[precision, filetype] = optArgs{:};

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
estr = sprintf(['First argument must be one of the following, \n',...
    '''absCV''\n',...
    '''iabsCV''\n',...
    '''addCStoCV''\n',...
    '''addCVtoCV''\n',...
    '''macCVbyCV''\n',...
    '''macRVbyCV''\n',...
    '''maxidxRV''\n',...
    '''meanCV''\n',...
    '''medianRV''\n',...
    '''medianNoreorderRV''\n',...
    '''mpyCSbyCS''\n',...
    '''mpyCVbyCV''\n',...
    '''mpyCVbyCVC''\n',...
    '''mpyRMbyRM''\n',...
    '''mpyRSbyRV''\n',...
    '''mpyRSbyRVbyRV''\n',...
    '''mpyRVbyCV''\n',...
    '''qsortRV''\n',...
    '''roundRS''\n',...
    '''subCSfromCV''\n',...
    '''subCVfromCV''\n',...
    ]);
assert((strcmp(fn,'absCV')             || ...
    strcmp(fn,'iabsCV')            || ...
    strcmp(fn,'addCStoCV')         || ...
    strcmp(fn,'addCVtoCV')         || ...
    strcmp(fn,'macCVbyCV')         || ...
    strcmp(fn,'macRVbyCV')         || ...
    strcmp(fn,'maxidxRV')          || ...
    strcmp(fn,'meanCV')            || ...
    strcmp(fn,'medianRV')          || ...
    strcmp(fn,'medianNoreorderRV') || ...
    strcmp(fn,'mpyCSbyCS')         || ...
    strcmp(fn,'mpyCVbyCV')         || ...
    strcmp(fn,'mpyCVbyCVC')        || ...
    strcmp(fn,'mpyRMbyRM')         || ...
    strcmp(fn,'mpyRSbyRV')         || ...
    strcmp(fn,'mpyRSbyRVbyRV')     || ...
    strcmp(fn,'mpyRVbyCV')         || ...
    strcmp(fn,'qsortRV')           || ...
    strcmp(fn,'roundRS')           || ...
    strcmp(fn,'subCSfromCV')       || ...
    strcmp(fn,'subCVfromCV')),...
    estr);

% Now that we have a legitimate function, we create an input/output
% file
assert((strcmp(filetype,'FTYPE_C') || ...
    strcmp(filetype,'FTYPE_ASM')),...
    'Argment needs to be ''FTYPE_C'' or ''FTYPE_ASM''\n');
if(strcmp(filetype, 'FTYPE_C'))
    InFn = strcat(fn,'Input.c');
    OutFn = strcat(fn,'Output.c');
    ext = '.c';
else % FTYPE_ASM
    InFn = strcat(fn,'Input.asm');
    OutFn = strcat(fn,'Output.asm');
    ext = '.asm';
end

%% Perform the vector functions
if (strcmp(fn,'absCV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    CV = r1 + 1i*r2;
    R = abs(CV);
    % Arrange the inputs,outputs
    t(1:2:2*N-1) = real(CV);
    t(2:2:2*N)   = imag(CV);
    Ni           = 2*N;
    No           = N;
elseif (strcmp(fn,'iabsCV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    CV = r1 + 1i*r2;
    R = 1./abs(CV);
    % Arrange the inputs,outputs
    t(1:2:2*N-1) = real(CV);
    t(2:2:2*N)   = imag(CV);
    Ni           = 2*N;
    No           = N;
elseif (strcmp(fn,'addCStoCV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    CV = r1 + 1i*r2;
    CS = a + (b - a)*rand(1) + 1i*a + (b - a)*rand(1);
    Rt = CS + CV;
    % Arrange the inputs,outputs
    t(1:2:2*N-1) = real(CV);
    t(2:2:2*N)   = imag(CV);
    t(2*N+1)     = real(CS);
    t(2*N+2)     = imag(CS);
    disp(['Use this value as the argument to the C function, ''{',...
        num2str(real(CS)),', ', num2str(imag(CS)),'}''']);
    Ni           = 2*N + 2;
    % Arrange the inputs,outputs
    R(1:2:2*N-1) = real(Rt);
    R(2:2:2*N)   = imag(Rt);
    No           = 2*N;
elseif (strcmp(fn,'addCVtoCV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    r3 = a + (b - a)*rand(N,1);
    r4 = a + (b - a)*rand(N,1);
    CV  = r1 + 1i*r2;
    CV2 = r3 + 1i*r4;
    Rt = CV + CV2;
    % Arrange the inputs,outputs
    t(1:2:2*N-1) = real(CV);
    t(2:2:2*N)   = imag(CV);
    t(2*N+1:2:4*N-1)  = real(CV2);
    t(2*N+2:2:4*N)    = imag(CV2);
    Ni           = 4*N;
    R(1:2:2*N-1) = real(Rt);
    R(2:2:2*N)   = imag(Rt);
    No           = 2*N;
elseif (strcmp(fn,'macCVbyCV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    r3 = a + (b - a)*rand(N,1);
    r4 = a + (b - a)*rand(N,1);
    CV1  = [r1 + 1i*r2].';
    CV2  = r3 + 1i*r4;
    Rt = CV1*CV2;
    % Arrange the inputs,outputs
    t(1:2:2*N-1)      = real(CV1);
    t(2:2:2*N)        = imag(CV1);
    t(2*N+1:2:4*N-1)  = real(CV2);
    t(2*N+2:2:4*N)    = imag(CV2);
    Ni                = 4*N;
    R(1)              = real(Rt);
    R(2)              = imag(Rt);
    No                = 2;
elseif (strcmp(fn,'macRVbyCV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    r3 = a + (b - a)*rand(N,1);
    CV  = r1 + 1i*r2;
    RV  = r3;
    Rt = sum(RV .* CV);
    % Arrange the inputs,outputs
    t(1:2:2*N-1)   = real(CV);
    t(2:2:2*N)     = imag(CV);
    t(2*N+1:1:3*N) = RV;
    Ni             = 3*N;
    R(1) = real(Rt);
    R(2) = imag(Rt);
    No   = 2;
elseif (strcmp(fn,'maxidxRV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    RV  = r1;
    [M,I] = max(RV);
    % Arrange the inputs,outputs
    t  = RV;
    Ni = N;
    R    = uint16(I - 1);
    No   = 1;
elseif (strcmp(fn,'meanCV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    CV = r1 + 1i*r2;
    Rt = mean(CV);
    % Arrange the inputs,outputs
    t(1:2:2*N-1)   = real(CV);
    t(2:2:2*N)     = imag(CV);
    Ni = 2*N;
    R(1)    = real(Rt);
    R(2)    = imag(Rt);
    No      = 2;
elseif (strcmp(fn,'medianRV') || strcmp(fn,'medianNoreorderRV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    RV  = r1;
    M = median(RV);
    % Arrange the inputs,outputs
    t  = RV;
    Ni = N;
    R    = M;
    No   = 1;
elseif (strcmp(fn,'mpyCSbyCS') || strcmp(fn,'mpyCVbyCV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    r3 = a + (b - a)*rand(N,1);
    r4 = a + (b - a)*rand(N,1);
    CV1  = r1 + 1i*r2;
    CV2  = r3 + 1i*r4;
    Rt = CV1 .* CV2;
    % Arrange the inputs,outputs
    t(1:2:2*N-1)      = real(CV1);
    t(2:2:2*N)        = imag(CV1);
    t(2*N+1:2:4*N-1)  = real(CV2);
    t(2*N+2:2:4*N)    = imag(CV2);
    Ni                = 4*N;
    R(1:2:2*N-1) = real(Rt);
    R(2:2:2*N)   = imag(Rt);
    No           = 2*N;
elseif (strcmp(fn,'mpyCVbyCVC'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    r3 = a + (b - a)*rand(N,1);
    r4 = a + (b - a)*rand(N,1);
    CV1  = r1 + 1i*r2;
    CV2  = r3 + 1i*r4;
    Rt = CV1 .* conj(CV2);
    % Arrange the inputs,outputs
    t(1:2:2*N-1)      = real(CV1);
    t(2:2:2*N)        = imag(CV1);
    t(2*N+1:2:4*N-1)  = real(CV2);
    t(2*N+2:2:4*N)    = imag(CV2);
    Ni                = 4*N;
    R(1:2:2*N-1) = real(Rt);
    R(2:2:2*N)   = imag(Rt);
    No           = 2*N;
elseif (strcmp(fn,'mpyRMbyRM'))
    % Generate two matrices m x n, n x p with values in the range of [-pi, pi]
    m = 2^(log2(N) - 2);
    n = N / m;
    p = m;
    a = -pi; b = pi;
    RM1 = a + (b - a).*rand(m,n);
    RM2 = a + (b - a).*rand(n,p);
    RO  = RM1 * RM2;
    % Arrange the inputs,outputs
    % Input matrices are stored in column order
    t(1:N,1)     = reshape(RM1,N, 1);
    t(N+1:2*N,1) = reshape(RM2, N, 1);
    Ni           = 2*N;
    No           = m*p;
    R            = reshape(RO, No, 1);
    disp(['Use this value as the argument to the C function, ''{',...
        num2str(m),', ', num2str(n),'}''']);
elseif (strcmp(fn,'mpyRSbyRV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(1,1);
    r2 = a + (b - a)*rand(N,1);
    RS  = r1;
    RV  = r2;
    R   = RS .* RV;
    % Arrange the inputs,outputs
    t(1:N) = RV;
    t(N+1) = RS;
    Ni     = N+1;
    No     = N;
    disp(['Use this value as the argument to the C function, ''{',...
        num2str(RS),'}''']);
elseif (strcmp(fn,'mpyRSbyRVbyRV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(1,1);
    r2 = a + (b - a)*rand(N,1);
    r3 = a + (b - a)*rand(N,1);
    RS  = r1;
    RV  = r2;
    RV2 = r3;
    R   = RS .* RV .* RV2;
    % Arrange the inputs,outputs
    t(1:N)     = RV;
    t(N+1:2*N) = RV2;
    t(2*N+1)   = RS;
    Ni         = 2*N+1;
    No     = N;
    disp(['Use this value as the argument to the C function, ''{',...
        num2str(RS),'}''']);
elseif (strcmp(fn,'mpyRVbyCV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    r3 = a + (b - a)*rand(N,1);
    RV = r1;
    CV = r2 + 1i*r3;
    Rt = RV .* CV;
    % Arrange the inputs,outputs
    t(1:2:2*N-1)      = real(CV);
    t(2:2:2*N)        = imag(CV);
    t(2*N+1:3*N)      = RV;
    Ni                = 3*N;
    R(1:2:2*N-1) = real(Rt);
    R(2:2:2*N)   = imag(Rt);
    No           = 2*N;
elseif (strcmp(fn,'qsortRV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    RV  = r1;
    R = sort(RV);
    % Arrange the inputs,outputs
    t  = RV;
    Ni = N;
    No   = N;
elseif (strcmp(fn,'roundRS'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -1000; b = 1000;
    r1 = a + (b - a)*rand(N,1);
    RS = r1;
    Rt = round(RS);
    % Arrange the inputs,outputs
    t             = RS;
    Ni            = N;
    R             = Rt;
    No            = N;
elseif (strcmp(fn,'subCSfromCV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    CV = r1 + 1i*r2;
    CS = a + (b - a)*rand(1) + 1i*a + (b - a)*rand(1);
    Rt = CV - CS;
    % Arrange the inputs,outputs
    t(1:2:2*N-1) = real(CV);
    t(2:2:2*N)   = imag(CV);
    t(2*N+1)     = real(CS);
    t(2*N+2)     = imag(CS);
    disp(['Use this value as the argument to the C function, ''{',...
        num2str(real(CS)),', ', num2str(imag(CS)),'}''']);
    Ni           = 2*N + 2;
    R(1:2:2*N-1) = real(Rt);
    R(2:2:2*N)   = imag(Rt);
    No           = 2*N;
elseif (strcmp(fn,'subCVfromCV'))
    % Generate a vector of N points in the range of [-pi, pi]
    a = -pi; b = pi;
    r1 = a + (b - a)*rand(N,1);
    r2 = a + (b - a)*rand(N,1);
    r3 = a + (b - a)*rand(N,1);
    r4 = a + (b - a)*rand(N,1);
    CV  = r1 + 1i*r2;
    CV2 = r3 + 1i*r4;
    Rt = CV - CV2;
    % Arrange the inputs,outputs
    t(1:2:2*N-1) = real(CV);
    t(2:2:2*N)   = imag(CV);
    t(2*N+1:2:4*N-1)  = real(CV2);
    t(2*N+2:2:4*N)    = imag(CV2);
    Ni           = 4*N;
    R(1:2:2*N-1) = real(Rt);
    R(2:2:2*N)   = imag(Rt);
    No           = 2*N;
else
    assert(0,'Problem with the first argument\n');
end


%% Formatted print to .asm file
HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
if (~strcmp(InFn,'NULL') && strcmp(ext,'.asm'))
    fid = fopen(InFn,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',InFn,'\n']);
    fprintf(fid,[';;! \\brief  Input Vector (',num2str(N),') \n']);
    fprintf(fid,';;! \\author Vishal Coelho \n');
    fprintf(fid,[';;! \\date   ',date,'\n;;! \n;;\n']);
    fprintf(fid,';;  Group:\t\t\tC2000\n');
    fprintf(fid,';;  Target Family:\t$DEVICE$\n;;\n');
    fprintf(fid,[';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,';; ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,';;\n');
    fprintf(fid,';;\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    fprintf(fid,'\t.def\t_test_input\n');
    fprintf(fid,'\n');
    if(strcmp(fn,'medianRV'))
        fprintf(fid,'\t.sect\t".data"\n');
    else
        fprintf(fid,'\t.sect\t".econst"\n');
    end
    fprintf(fid,'\n');
    % Start the vector
    fprintf(fid, '_test_input:\n');
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
    fprintf(fid,[';;! \\brief  Output Vector (',num2str(N),') \n']);
    fprintf(fid,';;! \\author Vishal Coelho \n');
    fprintf(fid,[';;! \\date   ',date,'\n;;! \n;;\n']);
    fprintf(fid,';;  Group:\t\t\tC2000\n');
    fprintf(fid,';;  Target Family:\tF2837x\n;;\n');
    fprintf(fid,[';; Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,';; ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,';;\n');
    fprintf(fid,';;\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    fprintf(fid,'\t.def\t_test_golden\n');
    fprintf(fid,'\n');
    fprintf(fid,'\t.sect\t".econst"\n');
    fprintf(fid,'\n');
    % Start the vector
    fprintf(fid, '_test_golden:\n');
    if (strcmp(precision,'TYPE_FLOAT'))
        S = sprintf('\t.float\t%15.12f, %15.12f, %15.12f, %15.12f \n',R);
    else
        S = sprintf('\t.xldouble\t%15.12f, %15.12f, %15.12f, %15.12f \n',R);
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
    fprintf(fid,['//! \\brief  Input Vector (',num2str(N),') \n']);
    fprintf(fid,'//! \\author Vishal Coelho \n');
    fprintf(fid,['//! \\date   ',date,'\n//! \n//\n']);
    fprintf(fid,'//  Group:\t\t\tC2000\n');
    fprintf(fid,'//  Target Family:\t$DEVICE$\n//\n');
    fprintf(fid,['// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,'// ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'//\n');
    fprintf(fid,'//\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    % Start the vector
    if(strcmp(fn,'medianRV'))
        fprintf(fid, [ftype,' test_input[',num2str(Ni),...
            '] = {\n']);
    else
        fprintf(fid, ['const ',ftype,' test_input[',num2str(Ni),...
            '] = {\n']);
    end
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
    fprintf(fid,['//! \\brief  Ouput Vector (',num2str(N),') \n']);
    fprintf(fid,'//! \\author Vishal Coelho \n');
    fprintf(fid,['//! \\date   ',date,'\n//! \n//\n']);
    fprintf(fid,'//  Group:\t\t\tC2000\n');
    fprintf(fid,'//  Target Family:\t$DEVICE$\n//\n');
    fprintf(fid,['// Copyright (C) $YEAR$ Texas Instruments Incorporated',...
        '- http://www.ti.com/ \n']);
    fprintf(fid,'// ALL RIGHTS RESERVED\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'//\n');
    fprintf(fid,'//\n');
    fprintf(fid,HEAD_string);
    fprintf(fid,'\n');
    
    % Start the vector
    fprintf(fid, ['const ',ftype,' test_golden[',num2str(No),...
        '] = {\n']);
    if(strcmp(precision, 'TYPE_FLOAT'))
        S = sprintf('\t%14.11fF, %14.11fF, %14.11fF, %14.11fF, \n',R);
    else
        S = sprintf('\t%15.12fL, %15.12fL, %15.12fL, %15.12fL, \n',R);
    end
    fprintf(fid,S);
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end
%%
% End of file
