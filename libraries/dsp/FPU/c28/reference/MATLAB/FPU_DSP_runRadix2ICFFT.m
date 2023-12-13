%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  Radix 2 Inverse Complex FFT
% \author Vishal Coelho
% \date   11/09/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################
%% The FFT Function
% \brief Run an inverse complex FFT (radix 2)
% \param[in] N  , Size of the complex FFT
% \param[in] In , Input Complex Vector (Re, Im ordered sequentially)
% \param[in] T  , Twiddle factor table
% \param[in] TBL_SIZE , Size of the twiddle factor table
% \return    Out, The FFT of the input (Re, Im ordered sequentially)
function OUT = FPU_DSP_runRadix2ICFFT(N, IN, T, TBL_SIZE)
OUT = IN;
szofcomplex = 2;
n_stages = log2(N);
% The trivial stages
%%%%%%%%%%%%%%%%%%%%%%%%%%
% Stage 1                %
%%%%%%%%%%%%%%%%%%%%%%%%%%
curr_stage = 1;
% Number of groups of butteflys
n_grps     = N/(2^curr_stage);
% Number of butterflies in a group
n_bflys    = (N/2)/n_grps;
%Set the input datum seperation for a given stage
in_sep     = 2^(curr_stage - 1) * szofcomplex;
% Setup data pointers
p_top = 1;
p_bot = p_top + in_sep;
%Iterate through the groups
for p = 1 : n_grps
    Ar    = OUT(p_top);
    Ai    = OUT(p_top+1);
    Br    = OUT(p_bot);
    Bi    = OUT(p_bot+1);
    Cr    = 0.5*( Ar+Br);
    Ci    = 0.5*(-Ai-Bi);
    Dr    = 0.5*( Ar-Br);
    Di    = 0.5*(-Ai+Bi);
    OUT(p_top)   = Cr;
    OUT(p_top+1) = Ci;
    OUT(p_bot)   = Dr;
    OUT(p_bot+1) = Di;
    % setup p_top and p_bot for next group
    p_top = p_top + in_sep + szofcomplex;
    p_bot = p_top + in_sep;
end
figure(2)
subplot(n_stages, 2, 1), plot(OUT(1:2:2*N-1)), legend('Stage 1(real)');
subplot(n_stages, 2, 2), plot(OUT(2:2:2*N)), legend('Stage 1(imag)');
%%%%%%%%%%%%%%%%%%%%%%%%%%
% Stage 2                %
%%%%%%%%%%%%%%%%%%%%%%%%%%
curr_stage = 2;
% Number of groups of butteflys
n_grps     = N/(2^curr_stage);
% Number of butterflies in a group
n_bflys    = (N/2)/n_grps;
%Set the input datum seperation for a given stage
in_sep     = 2^(curr_stage - 1) * szofcomplex;
% Setup data pointers
p_top = 1;
p_bot = p_top + in_sep;
%Iterate through the groups
for p = 1 : n_grps
    %first bfly
    Ar    = OUT(p_top);
    Ai    = OUT(p_top+1);
    Br    = OUT(p_bot);
    Bi    = OUT(p_bot+1);
    Cr    = 0.5*(Ar+Br);
    Ci    = 0.5*(Ai+Bi);
    Dr    = 0.5*(Ar-Br);
    Di    = 0.5*(Ai-Bi);
    OUT(p_top)   = Cr;
    OUT(p_top+1) = Ci;
    OUT(p_bot)   = Dr;
    OUT(p_bot+1) = Di;
    %second bfly
    p_top = p_top + szofcomplex;
    p_bot = p_top + in_sep;
    Ar    = OUT(p_top);
    Ai    = OUT(p_top+1);
    Br    = OUT(p_bot);
    Bi    = OUT(p_bot+1);
    Cr    = 0.5*(Ar+Bi);
    Ci    = 0.5*(Ai-Br);
    Dr    = 0.5*(Ar-Bi);
    Di    = 0.5*(Ai+Br);
    OUT(p_top)   = Cr;
    OUT(p_top+1) = Ci;
    OUT(p_bot)   = Dr;
    OUT(p_bot+1) = Di;
    % setup p_top and p_bot for next group
    p_top = p_top + in_sep + szofcomplex;
    p_bot = p_top + in_sep;
end
subplot(n_stages, 2, 3), plot(OUT(1:2:2*N-1)), legend('Stage 2(real)');
subplot(n_stages, 2, 4), plot(OUT(2:2:2*N)), legend('Stage 2(imag)');
%%%%%%%%%%%%%%%%%%%%%%%%%%
% Stage 3 to log2(N)-1   %
%%%%%%%%%%%%%%%%%%%%%%%%%%
% The non-trivial stages 3 till log2(N)
for k = 3 : n_stages-1
    curr_stage = curr_stage + 1;
    % Number of groups of butteflys
    n_grps     = N/(2^curr_stage);
    % Number of butterflies in a group
    n_bflys    = (N/2)/n_grps;
    %Set the input datum and twiddle factor seperation for a
    %given stage; the skip factor determines the gap between the
    %twiddle factors for a lookup table of size TBL_SIZE
    %Set the input datum and group seperation for a given stage
    in_sep      = 2^(curr_stage - 1) * szofcomplex;
    skip_factor = TBL_SIZE/(2^curr_stage);
    tf_sep      = TBL_SIZE/4;
    % Setup data and twiddle pointers
    p_top = 1;
    p_bot = p_top + in_sep;
    p_sin = 1;
    p_cos = p_sin + tf_sep;
    %Iterate through the groups
    for p = 1 : n_grps
        %iterate through the butterflies
        for r = 1 : n_bflys
            Ar    = OUT(p_top);
            Ai    = OUT(p_top+1);
            Br    = OUT(p_bot);
            Bi    = OUT(p_bot+1);
            S     = -T(p_sin);
            C     = T(p_cos);
            assert(((C^2+S^2)-1.0) < 1e-14,...
                'Twiddles dont lie on the unit circle');
            Cr    = 0.5*(Ar+C*Br-S*Bi);
            Ci    = 0.5*(Ai+C*Bi+S*Br);
            Dr    = 0.5*(Ar-C*Br+S*Bi);
            Di    = 0.5*(Ai-C*Bi-S*Br);
            OUT(p_top)   = Cr;
            OUT(p_top+1) = Ci;
            OUT(p_bot)   = Dr;
            OUT(p_bot+1) = Di;
            % setup p_top and p_bot for next butterfly
            p_top = p_top + szofcomplex;
            p_bot = p_top + in_sep;
            % setup twiddle pointer for next butterfly
            p_sin = p_sin + skip_factor;
            p_cos = p_sin + tf_sep;
        end
        % setup p_top and p_bot for next group
        p_top = p_top + in_sep;
        p_bot = p_top + in_sep;
        % reset twiddle pointers for next group
        p_sin = 1;
        p_cos = p_sin + tf_sep;
    end
    
    subplot(n_stages, 2, curr_stage*2-1), plot(OUT(1:2:2*N-1)),...
        legend(['Stage ',num2str(curr_stage),' (real)']);
    subplot(n_stages, 2, curr_stage*2), plot(OUT(2:2:2*N)),...
        legend(['Stage ',num2str(curr_stage),' (imag)']);
end
%%%%%%%%%%%%%%%%%%%%%%%%%%
% Stage log2(N)          %
%%%%%%%%%%%%%%%%%%%%%%%%%%
curr_stage = curr_stage + 1;
% Number of groups of butteflys
n_grps     = N/(2^curr_stage);
% Number of butterflies in a group
n_bflys    = (N/2)/n_grps;
%Set the input datum and twiddle factor seperation for a
%given stage; the skip factor determines the gap between the
%twiddle factors for a lookup table of size TBL_SIZE
%Set the input datum and group seperation for a given stage
in_sep      = 2^(curr_stage - 1) * szofcomplex;
skip_factor = TBL_SIZE/(2^curr_stage);
tf_sep      = TBL_SIZE/4;
% Setup data and twiddle pointers
p_top = 1;
p_bot = p_top + in_sep;
p_sin = 1;
p_cos = p_sin + tf_sep;
%Iterate through the groups
for p = 1 : n_grps
    %iterate through the butterflies
    for r = 1 : n_bflys
        Ar    = OUT(p_top);
        Ai    = OUT(p_top+1);
        Br    = OUT(p_bot);
        Bi    = OUT(p_bot+1);
        S     = -T(p_sin);
        C     = T(p_cos);
        assert(((C^2+S^2)-1.0) < 1e-14,...
            'Twiddles dont lie on the unit circle');
        Cr    = 0.5*( Ar+C*Br-S*Bi);
        Ci    = 0.5*(-Ai-C*Bi-S*Br);
        Dr    = 0.5*( Ar-C*Br+S*Bi);
        Di    = 0.5*(-Ai+C*Bi+S*Br);
        OUT(p_top)   = Cr;
        OUT(p_top+1) = Ci;
        OUT(p_bot)   = Dr;
        OUT(p_bot+1) = Di;
        % setup p_top and p_bot for next butterfly
        p_top = p_top + szofcomplex;
        p_bot = p_top + in_sep;
        % setup twiddle pointer for next butterfly
        p_sin = p_sin + skip_factor;
        p_cos = p_sin + tf_sep;
    end
    % setup p_top and p_bot for next group
    p_top = p_top + in_sep;
    p_bot = p_top + in_sep;
    % reset twiddle pointers for next group
    p_sin = 1;
    p_cos = p_sin + tf_sep;
end

subplot(n_stages, 2, curr_stage*2-1), plot(OUT(1:2:2*N-1)),...
    legend(['Stage ',num2str(curr_stage),' (real)']);
subplot(n_stages, 2, curr_stage*2), plot(OUT(2:2:2*N)),...
    legend(['Stage ',num2str(curr_stage),' (imag)']);
end

% End of file
