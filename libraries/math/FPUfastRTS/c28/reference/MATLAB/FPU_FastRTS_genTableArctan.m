%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  generate an Arc-Tangent lookup table (double precision table)
% \author Vishal Coelho
% \date   08/25/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% Arc Tangent Table Generation Function
%  This function generates the arctangent coefficients
%
%% Required Parameters
% * *N*, desired size of the lookup table
%
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *filename*, (opt) name of assembly file to write the table to. This is
%         an optional argument
% The filenames can only have a .asm or .c extension
%
%% Returns
% *T*, the table



%% Function Prototype
%  An Example: Generate a 64 3-tuple arctangent table (64*3 entries)
%
%  FPU_FastRTS_genTableArctan(64,  'TYPE_FLOAT',
%  'FPU_FastRTS_ArctanTable.asm')
%
function T = FPU_FastRTS_genTableArctan(N, varargin)

%% Parse Arguments
nOptArgs = 2;
numvarargs = length(varargin);
if numvarargs > nOptArgs
    error('myfunc:TooManyInputs',...
        ['requires at most ',num2str(nArgs),' optional input(s)']);
end

% Assign optional argument
optArgs = {'TYPE_FLOAT','NULL'};

% Check contents of varargin: if empty skip
newVals = cellfun(@(x) ~isempty(x), varargin);

% now put these defaults into the valuesToUse cell array,
% and overwrite the ones specified in varargin.
optArgs(newVals) = varargin(newVals);
% or ...
% [optargs{1:numvarargs}] = varargin{:};

% Place optional args in memorable variable names
[precision, filename] = optArgs{:};

% filename must have an asm or c extenstion
if (~strcmp(filename,'NULL'))
    [~,~,ext] = fileparts(filename);
    assert((strcmp(ext,'.asm') || strcmp(ext,'.c')), ['Filename needs to have',...
        ' an .asm or .c extension']);
end

if (strcmp(precision,'TYPE_FLOAT'))
    ftype = 'float';
elseif (strcmp(precision,'TYPE_DOUBLE'))
    if(strcmp(ext,'.c'))
        ftype = 'long double';
    else
        ftype = 'xldouble';
    end
else
    assert(0,'precision needs to be "TYPE_FLOAT" or "TYPE_DOUBLE"');
end
%% Table Generation (Double-Precision)
format long
x0 = 0.0;
x1 = 1/(2*N);	% x1    = 1/64 * 0.5
x2 = 1/N;		% x2    = 1/64
xstep = 1/N;	% xstep = 1/64
a0 = zeros(1,N);
a1 = zeros(1,N);
a2 = zeros(1,N);
x_0 = zeros(1,N);
x_1 = zeros(1,N);
x_2 = zeros(1,N);
t  = zeros(1,N);
T  = zeros(1, (N+1)*3);
j = 1;
for i = 0:N
    k = i+1;
    c12 = x0;
    c13 = x0*x0;
    b1  = atan(x0);
    c22 = x1;
    c23 = x1*x1;
    b2  = atan(x1);
    c32 = x2;
    c33 = x2*x2;
    b3  = atan(x2);
    
    a2(k) = ((b2-b1)*(c32-c12) - (b3-b1)*(c22-c12))/((c13-c33)*(c22-c12) - (c13-c23)*(c32-c12));
    a1(k) = ((b3-b1) + a2(k)*(c13-c33))/(c32-c12);
    a0(k) = b1 - a1(k)*c12 - a2(k)*c13;
    x_0(k)  = x0;
    x_1(k)  = x1;
    x_2(k)  = x2;
    x0 = x0 + xstep;
    x1 = x1 + xstep;
    x2 = x2 + xstep;
    T(j)   = a0(k);
    T(j+1) = a1(k);
    T(j+2) = a2(k);
    j = j + 3;
end

figure;
subplot(2,2,1), plot(x_0,a0,'-r'),title('a0'),
subplot(2,2,2),plot(x_1,a1,'--b'),title('a1'),
subplot(2,2,3),plot(x_2,a2,'og'),title('a2'),
xlabel('Index'); ylabel('Amplitude');

%% Formatted print to .asm file
if (~strcmp(filename,'NULL') && strcmp(ext,'.asm'))
    HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(filename,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',filename,'\n']);
    fprintf(fid,[';;! \\brief  Arctangent Lookup Table (',num2str(N),') \n']);
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
    
    fprintf(fid,'\t.def\t_FPUatan2HalfPITable\n');
    fprintf(fid,'\t.def\t_FPUatan2Table\n');
    fprintf(fid,'\t.def\t_FPUatan2TableEnd\n');
    fprintf(fid,'\n');
    fprintf(fid,'\t.sect\t"FPUmathTables"\n');
    fprintf(fid,'\n');
    fprintf(fid, '_FPUatan2HalfPITable:\n');
    fprintf(fid,'\t.%s\t%16.13f\n',ftype, 2.0);
    fprintf(fid,'\t.%s\t%16.13f\n',ftype, pi/2);
    fprintf(fid,'\n');
    % Start the Table
    fprintf(fid, '_FPUatan2Table:\n');
    for i = 1 : N+1
        n = i - 1;
        S = sprintf('\t.%s\t%16.13f, %16.13f, %16.13f ; %3d -> a0 a1 a2 \n',...
            ftype,a0(i), a1(i), a2(i), n);
        fprintf(fid,S);
    end
    
    % End the Table
    fprintf(fid, '_FPUatan2TableEnd:\n');
    fprintf(fid,'\n;; End of File\n');
    fclose(fid);
end

%% Formatted print to .c file
if (~strcmp(filename,'NULL') && strcmp(ext,'.c'))
    HEAD_string = ['//',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = ['//',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(filename,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,['//! \\file ',filename,'\n']);
    fprintf(fid,['//! \\brief  Arctangent Lookup Table (',num2str(N),') \n']);
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
    
    % Start the Table
    fprintf(fid, ['//This table has ',num2str((N+1)*3),' entries\n']);
    fprintf(fid, ['const ',ftype,' FastRTS_Arctan2Tbl[',num2str((N+1)*3),...
        '] = {\n']);
    for i = 1 : N+1
        n = i - 1;
        if(strcmp(precision, 'TYPE_FLOAT'))
            S = sprintf(['\t%16.13fF, \t%16.13fF, \t%16.13fF,//',...
                ' %3d -> a0 a1 a2\n'],a0(i),a1(i),a2(i),n);
        else %precision == 'TYPE_DOUBLE'
            S = sprintf(['\t%16.13fL, \t%16.13fL, \t%16.13fL,//',...
                ' %3d -> a0 a1 a2\n'],a0(i),a1(i),a2(i),n);
        end
        
        fprintf(fid,S);
    end
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end

%%
% End of file
