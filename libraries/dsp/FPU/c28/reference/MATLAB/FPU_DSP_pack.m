%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  Pack Function
% \author Vishal Coelho
% \date   11/09/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################
%% The Pack Function
% \brief Pre IFFT operation when the original input was know to be real
% \param[in] N  , Size of the real FFT
% \param[in] In , Spectrum of the Input, a Complex Vector (Re, Im 
%            ordered sequentially)
% \param[in] T  , Twiddle factor table
% \param[in] TBL_SIZE , Size of the twiddle factor table
% \return    Out, The FFT of the original input from bins K = 0 to Fs/2 (Re, 
%            Im ordered sequentially)
function OUT = FPU_DSP_pack(N, IN, T, TBL_SIZE)
    F = IN;
    Z = zeros(N/2,1);
    szofcomplex = 2;
    skip_factor = TBL_SIZE/N;
    tf_sep      = TBL_SIZE/4;
    p_sin = 1;
    p_cos = p_sin + tf_sep;
    % 0 to N/2 - 1
    for i = 0 : (N/2 - 1)
        % convert index to complex size and start at 1
        k           = i*szofcomplex + 1; 
        N_o_two_m_k = (N/2 - i)*szofcomplex + 1;
        Fr     = F(k);
        Fi     = F(k+1);
        Fcr    = F(N_o_two_m_k);
        Fci    = F(N_o_two_m_k + 1);
        S      = T(p_sin);
        C      = T(p_cos);
        assert(((C^2+S^2)-1.0) < 1e-14,'Twiddles dont lie on the unit circle');
        IA     = Fi + Fci; % Imaginarys add
        RS     = Fr - Fcr; % Reals subtract
        RA     = Fr + Fcr; % Reals add
        IS     = Fi - Fci; % Imaginarys subtract
        Z(k)   = 0.5*(RA - C*IA - S*RS);
        Z(k+1) = 0.5*(IS + C*RS - S*IA);
        % setup twiddle pointer for next butterfly
        p_sin = p_sin + skip_factor;
        p_cos = p_sin + tf_sep;
    end
    OUT = Z;
end

% End of file
