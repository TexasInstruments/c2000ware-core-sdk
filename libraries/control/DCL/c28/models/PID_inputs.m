% PID_inputs : configure test input stimulus

stepamp = 0.1;      % input step size

%--------------------------------------------------------------------------

% single unit step 0 -> 1
if input_config == 0
    % create time vector
    time = (0:T:endtime)';
    timespan = [0,endtime];

    % define times (seconds)
    t0 = 0;
    t1 = 0.1 * endtime;     % step up
    
    % construct input stimulus
    input = stepamp * ones(size(time));
    input(1:ceil(t1/T)) = 0;            % step at t1
end

%--------------------------------------------------------------------------

% pulse (return unit step) 0 -> 1 -> 0
if input_config == 1
    % create time vector
    time = (0:T:endtime)';
    timespan = [0,endtime];

    % define times (seconds)
    t0 = 0;
    t1 = 0.1 * endtime;     % step up
    t2 = 0.5 * endtime;     % step down

    % construct input stimulus
    input = stepamp * ones(size(time));
    input(1:ceil(t1/T)) = 0;            % step at t1
    input(ceil(t2/T):size(time)) = 0;   % recover at t2    
end

%--------------------------------------------------------------------------

% wiggle 0 -> 1 -> -1 -> 0
if input_config == 2
    % create time vector
    time = (0:T:endtime)';
    timespan = [0,endtime];

    % define times (seconds)
    t0 = 0;
    t1 = 0.1 * endtime;     % step up
    t2 = 0.4 * endtime;     % step down
    t3 = 0.7 * endtime;     % step up

    % construct input stimulus
    input = zeros(size(time));
    input(ceil(t1/T):ceil(t2/T)) = stepamp;
    input(ceil(t2/T)+1:ceil(t3/T)) = -stepamp; 
    input(ceil(t3/T)+1:size(time)) = 0; 
end

%--------------------------------------------------------------------------

% reverse wiggle 0 -> -1 -> 1 -> 0
if input_config == 3
    % create time vector
    time = (0:T:endtime)';
    timespan = [0,endtime];

    % define times (seconds)
    t0 = 0;
    t1 = 0.1 * endtime;     % step up
    t2 = 0.4 * endtime;     % step down
    t3 = 0.7 * endtime;     % step up

    % construct input stimulus
    input = zeros(size(time));
    input(ceil(t1/T):ceil(t2/T)) = -stepamp;
    input(ceil(t2/T)+1:ceil(t3/T)) = stepamp; 
    input(ceil(t3/T)+1:size(time)) = 0; 
end

%--------------------------------------------------------------------------

% oscillation burst
oscamp = 0.1;   % oscillation amplitude
k = 2;          % number of cycles in burst
if input_config == 4
    % create time vector
    time = (0:T:endtime)';
    timespan = [0,endtime];

    % define times (seconds)
    % t0 = 0;
    t1 = 0.1 * endtime;     % osc start
    t2 = 0.7 * endtime;     % osc stop
    N = (t2 - t1) / T;      % points in test phase
    
    % construct input stimulus
    input = zeros(size(time));
    n1 = ceil(t1/T);        % first point in test phase
    for i = n1:ceil(t2/T)
        input(i) = oscamp * sin(2*pi*(i-n1)*k/N);
    end
        % input(ceil(t2/T)+1:size(time)) = 0; 
end

%--------------------------------------------------------------------------

% unit pulse
impulseamp = 0.1;
if input_config == 5
    % create time vector
    time = (0:T:endtime)';
    timespan = [0,endtime];

    % define times (seconds)
    t0 = 0.1 * endtime;     % step up
    
    % construct input stimulus
    input = zeros(size(time));
    input(ceil(t0/T)) = impulseamp;      % impulse at t1
end

%--------------------------------------------------------------------------

% static
impulseamp = 0.01;
if input_config == 6
    % create time vector
    time = (0:T:endtime)';
    timespan = [0,endtime];
    
    % construct input stimulus
    input = impulseamp * ones(size(time));
end

%--------------------------------------------------------------------------

% triangle : 0 -> 1 ramp up : 1 -> 0 ramp down
if input_config == 7
    % create time vector
    time = (0:T:endtime)';
    timespan = [0,endtime];
    val = 0;

    % define times (seconds)
    t0 = 0;
    t1 = 0.1 * endtime;     % ramp up
    t2 = 0.5 * endtime;     % ramp down
    t3 = 0.9 * endtime;     % stop

    % construct input stimulus
    input = zeros(size(time));
    delta_y = stepamp / (t2 - t1);
    
    for index = ceil(t1/T):ceil(t2/T)
        val = val + delta_y;
        input(index) = val;
    end
    
    for index = ceil(t2/T):ceil(t3/T)
        val = val - delta_y;
        input(index) = val;
    end
    
end

% end of file
