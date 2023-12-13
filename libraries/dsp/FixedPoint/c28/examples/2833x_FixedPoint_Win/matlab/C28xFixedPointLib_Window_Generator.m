%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% C2000 Fixed Point Window Generator
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%//! \brief Generate the sampling windows for the fixed point libraries
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
%//! \param[in]  Q_fmt    Q-format for the window
%//!
function C28xFixedPointLib_Window_Generator(Q_fmt)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Parse Arguments
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if (Q_fmt < 0 || Q_fmt > 31)
    Q_fmt = 15;  % Default Q format
    disp('Invalid Q format, defaulting to Q15\n');
end
Q = power(2,Q_fmt)-1;    %multiply by (2^Q - 1) to get a Q number

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
    filename = ['fft_', windowFilename,'_Q',num2str(Q_fmt),'.h'];
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
        % Multiply by Q to convert to appropriate Q format and then
        % convert to integer
        W = int32(round(W.*Q));
        %Write this window to the file, we only write half the window,
        %since the windows are symmetric, the fft_win() uses this to 
        % its advantage by walking across the array forwards and backwards
        fprintf(fid,['#define ',upper(windowName),num2str(N(j)),...
            ' {\\\n']);
        W_str = sprintf('%14d, %14d, %14d, %14d, %14d, %14d, %14d, %14d, \\\\\n',...
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
