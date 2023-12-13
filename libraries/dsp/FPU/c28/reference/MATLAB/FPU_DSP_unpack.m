%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  Unpack Function
% \author Vishal Coelho
% \date   10/15/2015
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################
%% The Unpack Function
% \brief Post CFFT operation when the original input was know to be real
% \param[in] N  , Size of the real FFT
% \param[in] In , Spectrum of the Input, a Complex Vector (Re, Im 
%            ordered sequentially)
% \param[in] T  , Twiddle factor table
% \param[in] TBL_SIZE , Size of the twiddle factor table
% \return    Out, The FFT of the original input from bins K = 0 to Fs/2 (Re, 
%            Im ordered sequentially)
function OUT = FPU_DSP_unpack(N, IN, T, TBL_SIZE)
    Z = IN;
    F = zeros(2*N, 1);
    szofcomplex = 2;
    skip_factor = TBL_SIZE/N;
    tf_sep      = TBL_SIZE/4;
    % NOTE: We dont actually need p_sin, p_cos for the first calculation
    % but i have shown it here nonetheless
    p_sin = 1;
    p_cos = p_sin + tf_sep;
    % 0th element
    i  = 0;
    k  = i*szofcomplex + 1;
    F(k)   = Z(k) + Z(k+1); %Re(Z(0)) + Im(Z(0))
    F(k+1) = 0;
    % setup twiddle pointer for next butterfly
    p_sin = p_sin + skip_factor;
    p_cos = p_sin + tf_sep;
    % 1 to N/2 - 1 and N/2+1 to N-1
    for i = 1 : (N/2 - 1)
        % convert index to complex size and start at 1
        k           = i*szofcomplex + 1; 
        N_o_two_m_k = (N/2 - i)*szofcomplex + 1; 
        N_m_k       = (N - i)*szofcomplex + 1; 
        Zr     = Z(k);
        Zi     = Z(k+1);
        Zcr    = Z(N_o_two_m_k);
        Zci    = Z(N_o_two_m_k + 1);
        S      = -T(p_sin);
        C      = T(p_cos);
        assert(((C^2+S^2)-1.0) < 1e-14,'Twiddles dont lie on the unit circle');
        IA     = Zi + Zci; % Imaginarys add
        RS     = Zr - Zcr; % Reals subtract
        RA     = Zr + Zcr; % Reals add
        IS     = Zi - Zci; % Imaginarys subtract
        F(k)   = 0.5*(RA + C*IA + S*RS);
        F(k+1) = 0.5*(IS - C*RS + S*IA);
        % F(N-k) = F*(k)
        F(N_m_k)     = F(k);
        F(N_m_k + 1) = -F(k+1);
        % setup twiddle pointer for next butterfly
        p_sin = p_sin + skip_factor;
        p_cos = p_sin + tf_sep;
    end
    % midpoint N/2 is real
    i     = N/2;
    k     = i*szofcomplex + 1; 
    F(k)  = Z(1) - Z(2); %Z(N/2) = Re(Z(0))-Im(Z(0))
    F(k+1)= 0;
    
    OUT = F;
end

% End of file
