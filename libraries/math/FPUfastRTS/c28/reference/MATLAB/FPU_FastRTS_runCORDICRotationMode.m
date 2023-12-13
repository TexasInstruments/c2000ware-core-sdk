%##############################################################################
% \file   reference/MATLAB/$FILENAME$
% \brief  CORDIC Iterations (Rotation Mode)
% \author Vishal Coelho
% \date   11/01/2016
%
% Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/
% ALL RIGHTS RESERVED
%##############################################################################
%
%
%##############################################################################
%% The CORDIC Algorithm
% \brief Perform the CORDIC Iterations (Rotation Mode)
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
% $$d_{n} = 1\ if\ z_{n} \geq 0, -1\ otherwise$$
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

function [xn, yn, zn] = FPU_FastRTS_runCORDICRotationMode(x0, y0, z0, N, AT, ST)

%<<VC161115: you dont need to perform a rotation
%     z0_max = 1.74322866204723400035;
%     f_need_final_rotation = 0;
%     if (abs(z0) > z0_max)
%         f_need_final_rotation = 1;
%         rot_mat = [cos(1.74322866204723400035), -sign(z0)*sin(1.74322866204723400035);
%                    sign(z0)*sin(1.74322866204723400035),  cos(1.74322866204723400035)];
%         %Wrap the angle to the permissible range
%         z0 = z0 - sign(z0)*z0_max;
%     end
%  VC161115>>

%preserve sign of the original angle
sign_z0 = sign(z0);
if(abs(z0) <= pi/2)
    % First quadrant for +ive theta and fourth quadrant for -ive theta
    z0 = abs(z0);
elseif (abs(z0) <= pi)
    % Second quadrant for +ive theta and third quadrant for -ive theta
    z0 = pi - abs(z0);
    x0 = -x0;
    sign_z0 = -sign_z0;
elseif (abs(z0) <= 3*(pi/2))
    % Third quadrant for +ive theta and second quadrant for -ive theta
    z0 = abs(z0) - pi;
    x0 = -x0;
else
    % Fourth quadrant for +ive theta and first quadrant for -ive theta
    z0 = 2*pi - abs(z0);
    sign_z0 = -sign_z0;
end

x      = zeros(1, N); x(1) = x0;
y      = zeros(1, N); y(1) = y0;
z      = zeros(1, N); z(1) = z0;
for i = 1 : N-1
    if(z(i) >= 0)
        dn = 1;
    else
        dn = -1;
    end
    x(i + 1) = x(i) - dn*y(i)*(2^-(i - 1));
    y(i + 1) = y(i) + dn*x(i)*(2^-(i - 1));
    z(i + 1) = z(i) - dn*AT(i);
end
xn = x(N);
yn = sign_z0*y(N);
zn = z(N);

%<<VC161115: dont do a final rotation
%     % Apply final rotation if necessary
%     if(f_need_final_rotation == 1)
%         temp = rot_mat*[xn; yn];
%         xn = temp(1);
%         yn = temp(2);
%     end
%  VC161115>>

%Check the final vector lies on the unit circle
info_AT = whos('AT');
if(strcmp(info_AT.class, 'single') == 1)
    assert(((xn^2 + yn^2) - 1) < 1e-7);
else
    assert(((xn^2 + yn^2) - 1) < 1e-14);
end
end

% End of file
