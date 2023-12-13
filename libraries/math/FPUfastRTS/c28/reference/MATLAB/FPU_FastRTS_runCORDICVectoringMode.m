%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  CORDIC Iterations (Vectoring Mode)
% \author Vishal Coelho
% \date   11/08/2016
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################
%% The CORDIC Algorithm
% \brief Perform the CORDIC Iterations (Vectoring Mode)
% The CORDIC algorithm is run for N iterations. We start with the following
% parameters
%
% $x_{0} = 1/K = 0.6072529350088812561694\ $ where 
% $\ K = \prod_{n=0}^{\infty}\sqrt{1 + 2^{-2n}}$
%
% $$y_{0} = 0$$
%
% $$z_{0} = \theta$$
%
% where $\theta$ is the angle in radians
%
% The *Non Restoring Decomposition* algorithm proceeds as follows:
%
% $$ x_{n+1} = x_{n} - d_{n}y_{n}2^{-n} $$
%
% $$ y_{n+1} = y_{n} + d_{n}x_{n}2^{-n} $$
%
% $$ z_{n+1} = z_{n} - d_{n}arctan(2^{-n}) $$
%
% where 
%
% $$d_{n} = 1\ if\ y_{n} \lt 0, -1\ otherwise$$
%
% Once $y_{n} \lt 0$ our required angle $\theta = -z_{n}$
%
% Note that $$\ |\theta| \leq \theta_{max}\ $$ and 
% $$\ \theta_{max} = \sum_{k=0}^{\infty} arctan(2^{-k})\ $$
%
%% Required Parameters
% * *x0*  , Initial x component
% * *y0*  , Initial y component
% * *z0*  , Initial z component
% * *N*   , Number of iterations
% * *AT*  , Arctangent table
% * *ST*  , Scaling Factor table
%
%% Returns
% * *x* , final xn component
% * *y* , final yn component
% * *z* , final zn component

function [xn, yn, zn] = FPU_FastRTS_runCORDICVectoringMode(x0, y0, z0, N, AT, ST)
    x      = zeros(1, N); x(1) = x0;
    y      = zeros(1, N); y(1) = y0;
    z      = zeros(1, N); z(1) = z0;
    for i = 1 : N-1
        if(y(i) >= 0)
            dn = 1;
        else
            dn = -1;
        end
        x(i + 1) = x(i) + dn*y(i)*(2^-(i - 1));
        y(i + 1) = y(i) - dn*x(i)*(2^-(i - 1));
        z(i + 1) = z(i) - dn*AT(i);
    end
    xn =  x(N);
    yn =  y(N);
    zn = -z(N);

    %Check the final vector has the same magnitude as the original
    info_AT = whos('AT');
    if(strcmp(info_AT.class, 'single') == 1)
        assert((ST(N)*sqrt(xn^2 + yn^2) - sqrt(x0^2 + y0^2)) < 1e-7);
    else
        assert((ST(N)*sqrt(xn^2 + yn^2) - sqrt(x0^2 + y0^2)) < 1e-14);
    end

end

% End of file
