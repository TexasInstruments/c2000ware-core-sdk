%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% C2000 Floating Point Window Generator
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%//! \brief Generate the sampling windows for the floating point libraries
%//!
%//! \author Vishal Coelho
%//!
%//! \details This routine will generate the sampling windows to
%//! be used in the C28x Fixed point library.
%//!
%//! The following windows are generated:
%//! 1.  barthannwin
%//! 2.  bartlett
%//! 3.  blackman
%//! 4.  blackmanharris
%//! 5.  bohmanwin
%//! 6.  chebwin
%//! 7.  flattopwin
%//! 8.  gausswin
%//! 9.  hamming
%//! 10. hann
%//! 11. kaiser
%//! 12. nuttallwin
%//! 13. parzenwin
%//! 14. rectwin
%//! 15. taylorwin
%//! 16. triang
%//! 17. tukeywin
%//!
%//! The size of the window equals the size of the FFT and can range
%//! from 32 to 1024. The function iterates through the different windows,
%//! creates them for N = 32 to 1024 and then writes to an appropriate
%//! header file as #defines
%//!
%//!
function C28xFPULib_Window_Generator()

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Parse Arguments
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Routine
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
i = 5 : 12;
N = 2.^i;

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
    windowName       = regexprep(windows(i,:), 'win', '');
    windowName       = regexprep(windowName, '\s*', '');
    windowFilename   = windowName;
    windowName(1)    = upper(windowName(1));
    windowHandleName = regexprep(windows(i,:), '\s*', '');
    % Open a header file for the "window" and write the preamble
    filename = ['fpu_fft_', windowFilename,'.h'];
    FN_DEF = ['_',upper(strtok(filename,'.')),'_H_'];
    HEAD_string = ['//',repmat(sprintf('='), 1, 77),'\n'];
    fid = fopen(filename,'w');
    fprintf(fid,HEAD_string);
    fprintf(fid,['// ',windowName,' Window \n']);
    fprintf(fid,HEAD_string);
    fprintf(fid,['#ifndef ',FN_DEF,'\n']);
    fprintf(fid,['#define ',FN_DEF,'\n\n']);
    
    % iterate through the different sizes i.e. N and generate the
    % #defines
    figure();
    for j = 1 : length(N)
        % Generate the ith window (with default options) of size N(j)
        W = window(windowHandleName, N(j));
        %plot each window
        subplot(length(N)/2, 2, j), plot(W);
        title([windowName,' Window, N = ', num2str(N(j))]);
        %Write this window to the file, we only write half the window,
        %since the windows are symmetric, the fft_win() uses this to 
        % its advantage by walking across the array forwards and backwards
        fprintf(fid,['#define ',upper(windowName),num2str(N(j)),...
            ' {\\\n']);
        W_str = sprintf('%10.8f, %10.8f, %10.8f, %10.8f, %10.8f, \\\\\n',...
            W(1:(N(j)/2)));
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

%% End of File
