%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  Generate the sampling windows for the floating point libraries
% \author Vishal Coelho
% \date   11/04/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################

%% Sampling Window Generation Function
% This function generates the sampling windows for the floating point libraries
%
% The following windows are generated:
% # barthannwin
% # bartlett
% # blackman
% # blackmanharris
% # bohmanwin
% # chebwin
% # flattopwin
% # gausswin
% # hamming
% # hann
% # kaiser
% # nuttallwin
% # parzenwin
% # rectwin
% # taylorwin
% # triang
% # tukeywin
%
% The size of the window equals the size of the FFT and can range
% from 32 to 1024. The function iterates through the different windows,
% creates them for N = 32 to 1024 and then writes to an appropriate
% header file as #defines
%

%% Required Parameters
% * *u_window*, must be one of the following
% # 'barthannwin'
% # 'bartlett'
% # 'blackman'
% # 'blackmanharris'
% # 'bohmanwin'
% # 'chebwin'
% # 'flattopwin'
% # 'gausswin'
% # 'hamming'
% # 'hann'
% # 'kaiser'
% # 'nuttallwin'
% # 'parzenwin'
% # 'rectwin'
% # 'taylorwin'
% # 'triang'
% # 'tukeywin'
% * *N*, desired size of the window (32 <= N <= 1024). Note this affects
% the window that is returned by the function. The function will still
% create, and write to file, windows of each type and powers of 2 starting
% from 32 up to 1024
%
%% Optional Parameters
% * *precision*, (opt) can be 'TYPE_FLOAT' or 'TYPE_DOUBLE', defaults to
%    float
% * *u_filename*, (opt) name of assembly file to write the selected window to. 
%    This is an optional argument
% The filenames can only have a .asm or .c extension
%
%% Returns
% *WIN*, the window

%% Function Prototype
%  An Example: 
%
%  WIN = FPU_DSP_genWindowFFT(1024, 'hann')
%  WIN = FPU_DSP_genWindowFFT(1024, 'hann', 'TYPE_FLOAT', 'window.c')
%

function WIN = FPU_DSP_genWindowFFT(N, u_window, varargin)
%% Parse Arguments
assert((N >=32) && (N<=1024) && (mod(N,2)==0), ' 32<=N<=1024\n');
estr = sprintf(['First argument must be one of the following, \n',...
    '''barthannwin''\n',...
    '''bartlett''\n',...
    '''blackman''\n',...
    '''blackmanharris''\n',...
    '''bohmanwin''\n',...
    '''chebwin''\n',...
    '''flattopwin''\n',...
    '''gausswin''\n',...
    '''hamming''\n',...
    '''hann''\n',...
    '''kaiser''\n',...
    '''nuttallwin''\n',...
    '''parzenwin''\n',...
    '''rectwin''\n',...
    '''taylorwin''\n',...
    '''triang''\n',...
    '''tukeywin''\n',...
    ]);
assert(strcmp(u_window, 'barthannwin')       || ...
    strcmp(u_window, 'bartlett')          || ...
    strcmp(u_window, 'blackman')          || ...
    strcmp(u_window, 'blackmanharris')    || ...
    strcmp(u_window, 'bohmanwin')         || ...
    strcmp(u_window, 'chebwin')           || ...
    strcmp(u_window, 'flattopwin')        || ...
    strcmp(u_window, 'gausswin')          || ...
    strcmp(u_window, 'hamming')           || ...
    strcmp(u_window, 'hann')              || ...
    strcmp(u_window, 'kaiser')            || ...
    strcmp(u_window, 'nuttallwin')        || ...
    strcmp(u_window, 'parzenwin')         || ...
    strcmp(u_window, 'rectwin')           || ...
    strcmp(u_window, 'taylorwin')         || ...
    strcmp(u_window, 'triang')            || ...
    strcmp(u_window, 'tukeywin'),...
    estr);

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
[precision, u_filename] = optArgs{:};

% filename must have an asm or c extenstion
if (~strcmp(u_filename,'NULL'))
    [~,~,ext] = fileparts(u_filename);
    assert((strcmp(ext,'.asm') || strcmp(ext,'.c')), ['Filename needs to have',...
        ' an .asm or .c extension']);
end

if (strcmp(precision,'TYPE_FLOAT'))
    ftype = 'float';
elseif (strcmp(precision,'TYPE_DOUBLE'))
    ftype = 'long double';
else
   assert(0,'precision needs to be "TYPE_FLOAT" or "TYPE_DOUBLE"'); 
end

%% Window Generation
i = 5 : 12;
Q = 2.^i;

windows = ['barthannwin   ';
    'bartlett      ';
    'blackman      ';
    'blackmanharris';
    'bohmanwin     ';
    'chebwin       ';
    'flattopwin    ';
    'gausswin      ';
    'hamming       ';
    'hann          ';
    'kaiser        ';
    'nuttallwin    ';
    'parzenwin     ';
    'rectwin       ';
    'taylorwin     ';
    'triang        ';
    'tukeywin      '];


for i = 1 : length(windows)
    
    % Take the name of the window and split out the "win" part if it has
    % one to reveal the name of the window and then capitalize the first
    % letter of the name
    windowName          = regexprep(windows(i,:), 'win', '');
    windowName          = regexprep(windowName, '\s*', '');
    windowFilename      = windowName;
    windowName(1)       = upper(windowName(1));
    chosenwindowName    = u_window;
    chosenwindowName(1) = upper(chosenwindowName(1));
    windowHandleName    = regexprep(windows(i,:), '\s*', '');
    % Open a header file for the "window" and write the preamble
    filename = ['fpu_fft_', windowFilename,'.h'];
    FN_DEF = ['_',upper(strtok(filename,'.')),'_H_'];
    HEAD_string = ['//',repmat(sprintf('='), 1, 77),'\n'];
    fid = fopen(filename,'w');
    
    fprintf(fid,HEAD_string);
    fprintf(fid,['#ifndef ',FN_DEF,'\n']);
    fprintf(fid,['#define ',FN_DEF,'\n\n']);
    fprintf(fid,['//! \\file ',filename,'\n']);
    fprintf(fid,['//! \\brief ',windowName,' Window \n']);
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
    
    % iterate through the different sizes i.e. N and generate the
    % #defines
    figure();
    for j = 1 : length(Q)
        % Generate the ith window (with default options) of size N(j)
        W = window(windowHandleName, Q(j));
        
        if((strcmp(u_window, windowHandleName) == 1) && (Q(j) == N))
            WIN = W;
        end
        %plot each window
        subplot(length(Q)/2, 2, j), plot(W);
        title([windowName,' Window, N = ', num2str(Q(j))]);
        %Write this window to the file, we only write half the window,
        %since the windows are symmetric, the fft_win() uses this to 
        % its advantage by walking across the array forwards and backwards
        fprintf(fid,['#define ',upper(windowName),num2str(Q(j)),...
            ' {\\\n']);
        W_str = sprintf('%10.8f, %10.8f, %10.8f, %10.8f, %10.8f, \\\\\n',...
            W(1:(Q(j)/2)));
        fprintf(fid, W_str);
        fprintf(fid,'} \n\n');
    end
    
    % Write out epilogue, close file
    fprintf(fid,['\n #endif // ',FN_DEF,'\n']);
    fprintf(fid,HEAD_string);
    fprintf(fid,'// End of File\n');
    fprintf(fid,HEAD_string);
    fclose(fid);
end

%% Formatted print to .asm file
if (~strcmp(u_filename,'NULL') && strcmp(ext,'.asm'))
    HEAD_string = [';;',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = [';;',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(u_filename,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,[';;! \\file ',u_filename,'\n']);
    fprintf(fid,[';;! \\brief ',chosenwindowName,' Window (',...
        num2str(N),') \n']);
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
    
    fprintf(fid,'\t.def\t_FPUfftWindow\n');
    fprintf(fid,'\t.def\t_FPUfftWindowEnd\n');
    fprintf(fid,'\n');
    fprintf(fid,'\t.sect\t"FPUfftWindow"\n');
    fprintf(fid,'\n');
    % Start the Sine Table
    fprintf(fid, '_FPUfftWindow:\n');
    for i = 1 : length(WIN)/2
        n = i - 1;
        S = sprintf('\t.%s\t%16.13f\t; %d\n',ftype, WIN(i),n);
        fprintf(fid,S);
    end
    % End the Cosine Table
    fprintf(fid, '_FPUfftWindowEnd:\n');
    fprintf(fid,'\n;; End of File\n');
    fclose(fid);
end

%% Formatted print to .c file
if (~strcmp(u_filename,'NULL') && strcmp(ext,'.c'))
    HEAD_string = ['//',repmat(sprintf('#'), 1, 77),'\n'];
    BODY_string = ['//',repmat(sprintf('*'), 1, 77),'\n'];
    fid = fopen(u_filename,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,['//! \\file ',u_filename,'\n']);
    fprintf(fid,['//! \\brief ',chosenwindowName,' Window (',...
        num2str(N),') \n']);
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
    
    % Start the Combined Table
    fprintf(fid, ['//This table has ',num2str(length(WIN)),' entries\n']);
    fprintf(fid, ['const ',ftype,' DSP_window[',num2str(length(WIN)),...
        '] = {\n']);
    for i = 1 : length(WIN)/2
        n = i - 1;
        if(strcmp(precision, 'TYPE_FLOAT'))
            S = sprintf('\t%16.13fF,\t// %d\n',WIN(i),n);
        else %precision == 'TYPE_DOUBLE'
            S = sprintf('\t%16.13fL,\t// %d\n',WIN(i),n);
        end
        
        fprintf(fid,S);
    end
    fprintf(fid,'}; \n\n');
    fprintf(fid,'\n// End of File\n');
    fclose(fid);
end


%% End of File
