%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  Radix 2 Real Fast Fourier Transform
% \author Vishal Coelho
% \date   07/01/2016
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################
%% The FFT Function
% \brief Run a real FFT
% \param[in] N  , Size of the real FFT
% \param[in] In , Input Real Vector
% \param[in] T  , Twiddle factor table
% \param[in] TBL_SIZE , Size of the twiddle factor table
% \return    Out, The FFT of the input (Re[0], Re[1]....Re[N/2-1], Re[N/2],
% Im[N/2-1], Im[N/2-2]......Im[1])
function OUT = FPU_DSP_runRadix2RFFT(N, IN, T, TBL_SIZE)
OUT = IN;
n_stages = log2(N);

% The trivial stages
%%%%%%%%%%%%%%%%%%%%%%%%%%
% Stages 1, 2 and 3      %
%%%%%%%%%%%%%%%%%%%%%%%%%%
curr_stage = 3;
% Number of groups of butteflys
n_grps     = N/(2^curr_stage);
% Number of butterflies in a group
n_bflys    = (N/2)/n_grps;
%Set the group datum seperation for a given stage
grp_sep     = 2^(curr_stage);
% Setup data pointers
p_top = 1;
C = T(1);   S = T(2);
%Iterate through the groups
for p = 1 : n_grps
    
    D0  = OUT(p_top + 0);    D1 = OUT(p_top + 1);
    D2  = OUT(p_top + 2);    D3 = OUT(p_top + 3);
    D4  = OUT(p_top + 4);    D5 = OUT(p_top + 5);
    D6  = OUT(p_top + 6);    D7 = OUT(p_top + 7);
    
    D0_hh = (D0+D1)+(D2+D3)+(D4+D5)+(D6+D7); % (A)
    D1_hh = (D0-D1)+(C*((D4-D5)+(D7-D6)));   % (B)
    I1_hh = (C*((D7-D6)-(D4-D5)))+(D3-D2);   % (H)
    D2_hh = (D0+D1)-(D2+D3);                 % (C)
    I2_hh = (D6+D7)-(D4+D5);                 % (G)
    D3_hh = (D0-D1)-(C*((D4-D5)+(D7-D6)));   % (D)
    I3_hh = (C*((D7-D6)-(D4-D5)))-(D3-D2);   % (F)
    D4_hh = (D0+D1)+(D2+D3)-(D4+D5)-(D6+D7); % (E)
    
    OUT(p_top + 0)  = D0_hh;    OUT(p_top + 1)   = D1_hh;
    OUT(p_top + 2)  = D2_hh;    OUT(p_top + 3)   = D3_hh;
    OUT(p_top + 4)  = D4_hh;    OUT(p_top + 5)   = I3_hh;
    OUT(p_top + 6)  = I2_hh;    OUT(p_top + 7)   = I1_hh;
    % setup p_top and p_bot for next group
    p_top = p_top + grp_sep;
end
%<<VC151113 -> DEBUG
disp(['Stage ',num2str(curr_stage)]);
OUT
%  VC151113>>

figure(2)
subplot(n_stages-2, 2, 1), plot(OUT(1:N/2+1)), legend('Stage 1,2,3(real)');
subplot(n_stages-2, 2, 2), plot(OUT(N/2+2:N)), legend('Stage 1,2,3(imag)');

%%%%%%%%%%%%%%%%%%%%%%%%%%
% Stage 4 to log2(N)     %
%%%%%%%%%%%%%%%%%%%%%%%%%%
p_top = 1;
p_X1  = 0;  p_X2 = 0;
p_X3  = 0;  p_X4 = 0;
p_cos = 1;
X1X3offset = 8;
X2X4offset = 8;
% The non-trivial stages 4 till log2(N)
for k = 4 : n_stages
    curr_stage = curr_stage + 1;
    % Number of groups of butteflys
    n_grps     = N/(2^curr_stage);
    % Number of butterflies in a group
    n_bflys    = (N/2)/n_grps;
    % Number of loop calculations in a group
    n_calcs     = (n_bflys/2) - 1;
    %Set the group datum seperation for a given stage
    grp_sep     = 2^(curr_stage);
    % Initialize the pointers
    p_X1  = 0;        p_X3  = p_X1 + X1X3offset;
    p_X2 = p_X3 - 1;  p_X4  = p_X2 + X2X4offset;
    p_cos       = p_cos + (2^(curr_stage-2));
    p_sin       = p_cos + 1;
    p_temp      = p_cos;
    
    %Iterate through the groups
    for p = 1 : n_grps
        X1 = OUT(p_top + p_X1);  X3 = OUT(p_top + p_X3);
        Y1 = X1 + X3;
        Y3 = X1 - X3;
        OUT(p_top + p_X1) = Y1; p_X1 = p_X1 + 1;
        OUT(p_top + p_X3) = Y3; p_X3 = p_X3 + 1;
        %iterate through the inner calculations
        for r = 1 : n_calcs
            X1   = OUT(p_top + p_X1);
            X2   = OUT(p_top + p_X2);
            X3   = OUT(p_top + p_X3);
            X4   = OUT(p_top + p_X4);
            C    = T(p_cos); p_cos = p_cos + 2;
            S    = T(p_sin); p_sin = p_sin + 2;
            
            Y1   = X1 + (X3*C + X4*S);
            Y2   = X1 - (X3*C + X4*S);
            Y3   = (X4*C - X3*S) - X2;
            Y4   = (X4*C - X3*S) + X2;
            
            OUT(p_top + p_X1) = Y1;  p_X1 = p_X1 + 1;
            OUT(p_top + p_X2) = Y2;  p_X2 = p_X2 - 1;
            OUT(p_top + p_X3) = Y3;  p_X3 = p_X3 + 1;
            OUT(p_top + p_X4) = Y4;  p_X4 = p_X4 - 1;
        end
        Y4 = -OUT(p_top + p_X4);
        OUT(p_top + p_X4) = Y4;
        % setup pointers for next group
        p_top = p_top + grp_sep;
        p_X1  = 0;        p_X3  = p_X1 + X1X3offset;
        p_X2 = p_X3 - 1;  p_X4  = p_X2 + X2X4offset;
        % reset twiddle pointers for next group
        p_cos = p_temp;
        p_sin = p_cos + 1;
    end
    % update the pointers
    p_top = 1;
    
    % update the offsets
    X1X3offset = X1X3offset*2;
    X2X4offset = X2X4offset*2;
    %<<VC151113 -> DEBUG
    disp(['Stage ',num2str(curr_stage)]);
    OUT
    %  VC151113>>
    subplot(n_stages-2, 2, (curr_stage-2)*2-1), plot(OUT(1:N/2+1)),...
        legend(['Stage ',num2str(curr_stage),' (real)']);
    subplot(n_stages-2, 2, (curr_stage-2)*2), plot(OUT(N/2+2:N)),...
        legend(['Stage ',num2str(curr_stage),' (imag)']);
end
end

% End of file
