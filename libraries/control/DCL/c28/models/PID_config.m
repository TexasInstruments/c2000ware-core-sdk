% PID_config.m - 3rd order linear plant

endtime = 16;   % test duration (sec)
fs = 400;       % sample rate in Hz
T = 1 / fs;     % sample period (sec)

%- Controller ------------------------------------------------------------

% controller parameters
Kp = 7.5;       % proportional loop gain
Ki = 0.005;     % integral gain
Kd = 0.35;      % differential gain
Kr = 1;         % set-point weight
fc = 100;       % cut-off frequency (Hz)

% controller output saturation
Umax = inf;
Umin = -inf;

%- Plant model -----------------------------------------------------------

% plant transfer function:
%
%                  s + 1
%   G(s) = ---------------------
%          s^3 + 3 s^2 + 5 s + 1

G = tf([1 1], [1 3 5 1]);
[num_G,den_G] = tfdata(G,'v');
G = tf(num_G,den_G);    % save TF in workspace

% plant saturation limits
Psatmax = inf;
Psatmin = -inf;

% time delay
Tdly = T/10;

% feedback path dynamics
num_H = 1;
den_H = 1;
H = tf(num_H,den_H);

%- ADC model ------------------------------------------------------------

% ADC parameters
Kn = 0;             % feedback noise gain
Vadc_max = inf;     % positive input limit
Vadc_min = -inf;    % negative input limit
Nadc = 16;          % resolution in bits

% ADC quantizer interval
if isfinite(Vadc_max) & isfinite(Vadc_min)
    Qadc = (Vadc_max - Vadc_min)/2^Nadc;
else
    Qadc = 1/2^Nadc;
end

%- DAC model ------------------------------------------------------------

% DAC parameters
Umax = inf;         % upper output saturation
Umin = -inf;        % lower output saturation
Ndac = 16;          % resolution in bits

% DAC quantizer interval
if isfinite(Umax) & isfinite(Umin)
    Qdac = (Umax - Umin)/2^Ndac;
else
    Qdac = 1/2^Ndac;
end

% end of file
