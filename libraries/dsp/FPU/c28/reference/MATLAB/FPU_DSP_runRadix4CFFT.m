%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  Radix 4 Fast Fourier Transform
% \author Vishal Coelho
% \date   11/12/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################
%% The FFT Function
% \brief Run a complex FFT
% \param[in] N  , Size of the complex FFT
% \param[in] In , Input Complex Vector (Re, Im ordered sequentially)
% \param[in] T  , Twiddle factor table
% \param[in] TBL_SIZE , Size of the twiddle factor table
% \return    Out, The FFT of the input (Re, Im ordered sequentially)
function OUT = FPU_DSP_runRadix4CFFT(N, IN, T, TBL_SIZE)
OUT            = IN;
szofcomplex    = 2;
n_stages       = log2(N);
n_combo_stages = floor(n_stages/2) * 2;

%******************************************************************************
%% Stages 1 & 2
%******************************************************************************
% - The twiddle factors have the following relationship with each other
%   +---------------------------------+-------------------------------------+
%   | Stage N | P |  cos(1) - j sin(1)| W(N,0)..W(N,N/4 -1)                 |
%   |         | Q | -cos(1) + j sin(1)| W(N,N/2)..W(N,N/2 + N/4 -1)         |
%   | Stage N1| R |  cos(2) - j sin(2)| W(N1,0)..W(N1,N1/4-1)               |
%   |         | S | -sin(2) - j cos(2)| W(N1,N1/4)..W(N1,N1/2-1)            |
%   |         | T | -cos(2) + j sin(2)| W(N1,N1/2)..W(N1/N1/2+N1/4-1)       |
%   |         | U |  sin(2) + j cos(2)| W(N1,3N1/4)..W(N1,N1-1)             |
%   +---------------------------------+-------------------------------------+
%
%
%                     Stage N               Stage N+1
% p_top_n1   --Ar+jAi---------o----*---Er+jEi----------o--------*--Ir+jIi----->
%                       |      \ (P)               |    \      /       
%                    in_sep_n1  \/                 |     \   (R)        
%                       |       /\             in_sep_n2  \  /         
%                       V      /  \                |       \/          
% p_bot_n1   --Br+jBi---------o-(Q)*---Fr+jFi------|---o---/\---*--Jr+jJi----->
%                                                  |    \ /  \(S)          
%                                                  |     \    \        
%                                                  V    / \  / \      
% p_top_n2   --Cr+jCi---------o----*---Gr+jGi----------o---\(T)-*--Kr+jKi----->
%                        |     \ (P)                       /\              
%                        |      \/                        /  \         
%                        |      /\                       /    \        
%                        |     /  \                     /      \      
% p_bot_n2   --Dr+jDi----|----o-(Q)*---Hr+jHi----------o----(U)-*--Lr+jLi----->
%                        |
%                     grp_sep
%                        |
%                        |
%                        |
%                        V
%******************************************************************************
curr_stage = 2;
% Number of groups of butteflys
n_grps     = N/(2^curr_stage);
% Number of radix 4 butterflies in a group
n_bflys    = (N/4)/n_grps;
%Set the input datum seperation for a given stage
in_sep_n1    = 2^(curr_stage - 2) * szofcomplex;
in_sep_n2    = 2^(curr_stage - 1) * szofcomplex;
grp_sep      = 2*in_sep_n1;
% Setup data pointers
p_top_n1 = 1;
p_bot_n1 = p_top_n1 + in_sep_n1;
p_top_n2 = p_top_n1 + in_sep_n2;
p_bot_n2 = p_top_n2 + in_sep_n1;
%Iterate through the groups
for p = 1 : n_grps
    Ar              = OUT(p_top_n1);
    Ai              = OUT(p_top_n1+1);
    Br              = OUT(p_bot_n1);
    Bi              = OUT(p_bot_n1+1);
    Cr              = OUT(p_top_n2);
    Ci              = OUT(p_top_n2+1);
    Dr              = OUT(p_bot_n2);
    Di              = OUT(p_bot_n2+1);
    Er              = Ar+Br;
    Ei              = Ai+Bi;
    Fr              = Ar-Br;
    Fi              = Ai-Bi;
    Gr              = Cr+Dr;
    Gi              = Ci+Di;
    Hr              = Cr-Dr;
    Hi              = Ci-Di;
    Ir              = Er+Gr;
    Ii              = Ei+Gi;
    Jr              = Fr+Hi;
    Ji              = Fi-Hr;
    Kr              = Er-Gr;
    Ki              = Ei-Gi;
    Lr              = Fr-Hi;
    Li              = Fi+Hr;
    OUT(p_top_n1)   = Ir;
    OUT(p_top_n1+1) = Ii;
    OUT(p_bot_n1)   = Jr;
    OUT(p_bot_n1+1) = Ji;
    OUT(p_top_n2)   = Kr;
    OUT(p_top_n2+1) = Ki;
    OUT(p_bot_n2)   = Lr;
    OUT(p_bot_n2+1) = Li;
    % setup p_top and p_bot for next group
    p_top_n1        = p_top_n2 + grp_sep;
    p_bot_n1        = p_top_n1 + in_sep_n1;
    p_top_n2        = p_top_n1 + in_sep_n2;
    p_bot_n2        = p_top_n2 + in_sep_n1;
end
%<<VC151113 -> DEBUG
disp(['Stage ',num2str(curr_stage)]);
OUT
%  VC151113>>
figure(2)
subplot(n_stages, 2, 1), plot(OUT(1:2:2*N-1)), legend('Stage 1 and 2(real)');
subplot(n_stages, 2, 2), plot(OUT(2:2:2*N)), legend('Stage 1 and 2(imag)');

%******************************************************************************
%% Combined Stages (n1, n2) to floor(log2(N)/2)*2                             %
%******************************************************************************
% - The twiddle factors have the following relationship with each other
%   +---------------------------------+-------------------------------------+
%   | Stage N | P |  cos(1) - j sin(1)| W(N,0)..W(N,N/4 -1)                 |
%   |         | Q | -cos(1) + j sin(1)| W(N,N/2)..W(N,N/2 + N/4 -1)         |
%   | Stage N1| R |  cos(2) - j sin(2)| W(N1,0)..W(N1,N1/4-1)               |
%   |         | S | -sin(2) - j cos(2)| W(N1,N1/4)..W(N1,N1/2-1)            |
%   |         | T | -cos(2) + j sin(2)| W(N1,N1/2)..W(N1/N1/2+N1/4-1)       |
%   |         | U |  sin(2) + j cos(2)| W(N1,3N1/4)..W(N1,N1-1)             |
%   +---------------------------------+-------------------------------------+
%
%
%                     Stage N               Stage N+1
% p_top_n1   --Ar+jAi---------o----*---Er+jEi----------o--------*--Ir+jIi----->
%                       |      \ (P)               |    \      /       
%                    in_sep_n1  \/                 |     \   (R)        
%                       |       /\             in_sep_n2  \  /         
%                       V      /  \                |       \/          
% p_bot_n1   --Br+jBi---------o-(Q)*---Fr+jFi------|---o---/\---*--Jr+jJi----->
%                                                  |    \ /  \(S)          
%                                                  |     \    \        
%                                                  V    / \  / \      
% p_top_n2   --Cr+jCi---------o----*---Gr+jGi----------o---\(T)-*--Kr+jKi----->
%                        |     \ (P)                       /\              
%                        |      \/                        /  \         
%                        |      /\                       /    \        
%                        |     /  \                     /      \      
% p_bot_n2   --Dr+jDi----|----o-(Q)*---Hr+jHi----------o----(U)-*--Lr+jLi----->
%                        |
%                     grp_sep
%                        |
%                        |
%                        |
%                        V
%******************************************************************************
% The non-trivial stages 3 till log2(N)
for k = 3 : 2 : n_combo_stages
    curr_stage = curr_stage + 2;
    % Number of groups of butteflys
    n_grps     = N/(2^curr_stage);
    % Number of butterflies in a group
    n_bflys    = (N/4)/n_grps;
    %Set the input datum and twiddle factor seperation for a
    %given stage; the skip factor determines the gap between the
    %twiddle factors for a lookup table of size TBL_SIZE
    %Set the input datum and group seperation for a given stage
    in_sep_n1       = 2^(curr_stage - 2) * szofcomplex;
    in_sep_n2       = 2^(curr_stage - 1) * szofcomplex;
    skip_factor_n1  = TBL_SIZE/(2^(curr_stage-1));
    skip_factor_n2  = TBL_SIZE/(2^(curr_stage));
    tf_sep          = TBL_SIZE/4;
    grp_sep         = 2*in_sep_n1;
    % Setup data and twiddle pointers
    p_top_n1 = 1;
    p_bot_n1 = p_top_n1 + in_sep_n1;
    p_top_n2 = p_top_n1 + in_sep_n2;
    p_bot_n2 = p_top_n2 + in_sep_n1;
    
    p_sin_n1 = 1;
    p_cos_n1 = p_sin_n1 + tf_sep;
    p_sin_n2 = 1;
    p_cos_n2 = p_sin_n2 + tf_sep;
    %Iterate through the groups
    for p = 1 : n_grps
        %iterate through the butterflies
        for r = 1 : n_bflys
            Ar              = OUT(p_top_n1);
            Ai              = OUT(p_top_n1+1);
            Br              = OUT(p_bot_n1);
            Bi              = OUT(p_bot_n1+1);
            Cr              = OUT(p_top_n2);
            Ci              = OUT(p_top_n2+1);
            Dr              = OUT(p_bot_n2);
            Di              = OUT(p_bot_n2+1);
            S1              = T(p_sin_n1);
            C1              = T(p_cos_n1);
            S2              = T(p_sin_n2);
            C2              = T(p_cos_n2);
            assert(((C1^2+S1^2)-1.0) < 1e-14 && ((C2^2+S2^2)-1.0) < 1e-14,...
                'Twiddles dont lie on the unit circle');
            Er              = Ar+(Br*C1+Bi*S1);
            Ei              = Ai+(Bi*C1-Br*S1);
            Fr              = Ar-(Br*C1+Bi*S1);
            Fi              = Ai-(Bi*C1-Br*S1);
            Gr              = Cr+(Dr*C1+Di*S1);
            Gi              = Ci+(Di*C1-Dr*S1);
            Hr              = Cr-(Dr*C1+Di*S1);
            Hi              = Ci-(Di*C1-Dr*S1);
            Ir              = Er+(Gr*C2+Gi*S2);
            Ii              = Ei+(Gi*C2-Gr*S2);
            Jr              = Fr-(Hr*S2-Hi*C2);
            Ji              = Fi-(Hi*S2+Hr*C2);
            Kr              = Er-(Gr*C2+Gi*S2);
            Ki              = Ei-(Gi*C2-Gr*S2);
            Lr              = Fr+(Hr*S2-Hi*C2);
            Li              = Fi+(Hr*C2+Hi*S2);
            OUT(p_top_n1)   = Ir;
            OUT(p_top_n1+1) = Ii;
            OUT(p_bot_n1)   = Jr;
            OUT(p_bot_n1+1) = Ji;
            OUT(p_top_n2)   = Kr;
            OUT(p_top_n2+1) = Ki;
            OUT(p_bot_n2)   = Lr;
            OUT(p_bot_n2+1) = Li;
            % setup p_top and p_bot for next butterfly
            p_top_n1        = p_top_n1 + szofcomplex;
            p_bot_n1        = p_top_n1 + in_sep_n1;
            p_top_n2        = p_top_n1 + in_sep_n2;
            p_bot_n2        = p_top_n2 + in_sep_n1;
            % setup twiddle pointer for next butterfly
            p_sin_n1        = p_sin_n1 + skip_factor_n1;
            p_cos_n1        = p_sin_n1 + tf_sep;
            p_sin_n2        = p_sin_n2 + skip_factor_n2;
            p_cos_n2        = p_sin_n2 + tf_sep;
        end
        % setup p_top and p_bot for next group
        p_top_n1    = p_bot_n2;
        p_bot_n1    = p_top_n1 + in_sep_n1;
        p_top_n2    = p_top_n1 + in_sep_n2;
        p_bot_n2    = p_top_n2 + in_sep_n1;
        % reset twiddle pointers for next group
        p_sin_n1    = 1;
        p_cos_n1    = p_sin_n1 + tf_sep;
        p_sin_n2    = 1;
        p_cos_n2    = p_sin_n2 + tf_sep;
    end
    %<<VC151113 -> DEBUG
    disp(['Stage ',num2str(curr_stage)]);
    OUT
    %  VC151113>>
    subplot(n_stages, 2, curr_stage*2-1), plot(OUT(1:2:2*N-1)),...
        legend(['Stage ',num2str(curr_stage-1),' and ',...
        num2str(curr_stage),' (real)']);
    subplot(n_stages, 2, curr_stage*2), plot(OUT(2:2:2*N)),...
        legend(['Stage ',num2str(curr_stage-1),' and ',...
        num2str(curr_stage),' (imag)']);
end

if((n_stages - n_combo_stages) == 1)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Possible last single stage log2(N) %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
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
            Cr    = Ar+C*Br-S*Bi;
            Ci    = Ai+C*Bi+S*Br;
            Dr    = Ar-C*Br+S*Bi;
            Di    = Ai-C*Bi-S*Br;
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
    %<<VC151113 -> DEBUG
    disp(['Stage ',num2str(curr_stage)]);
    OUT
    %  VC151113>>
    subplot(n_stages, 2, curr_stage*2-1), plot(OUT(1:2:2*N-1)),...
        legend(['Stage ',num2str(curr_stage),' (real)']);
    subplot(n_stages, 2, curr_stage*2), plot(OUT(2:2:2*N)),...
        legend(['Stage ',num2str(curr_stage),' (imag)']);
end
end

% End of file
