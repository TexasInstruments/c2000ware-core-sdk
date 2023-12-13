% PID_example.m - C2000 Digital Control Library - PID control example
clc;  close all; clear; 

%- Configuration ---------------------------------------------------------

% input stimulus
% 0 : step
% 1 : pulse (return step)
% 2 : bi-directional pulse
% 3 : reverse bi-directional pulse
% 4 : chirp (oscillation burst)
% 5 : unit pulse
% 6 : static offset
% 7 : triangle ramp
input_config = 1;

%- Plots -----------------------------------------------------------------

% system plots: set to 1 to plot
data.inp.plot = 0;    % input stimulus
data.rsp.plot = 1;    % servo response
data.act.plot = 0;    % control effort
data.fbk.plot = 0;    % feedback
data.err.plot = 0;    % servo error
data.sat.plot = 0;    % saturation

% system data: set to 1 to save to file
data.inp.save = 1;    % input stimulus
data.fbk.save = 1;    % feedback
data.sat.save = 1;    % saturation limit
data.act.save = 1;    % control effort

%- Read configuration ----------------------------------------------------

filename = 'PID_config.m';
open(filename);
run(filename);
run('PID_inputs.m')

%- Simulation ------------------------------------------------------------

open 'PID_sim.slx';
sim('PID_sim', timespan, [], []);
%  note: inspect command window for assertions
fprintf('Simulation complete.\n');

%- Results ---------------------------------------------------------------

% display selected plots
run('PID_plots.m')

% compute performance indices & display in command window
% IES = sum(ferror.^2)
% IAE = norm(ferror,1)
ITAE = T * sum(time.*abs(ferror))

%- Data export -----------------------------------------------------------

% write test data to text files for CCS access

% 1. input stimulus
if data.inp.save == 1
    filename = strcat('PID_input.dat');
    File1 = fopen(filename,'w');
    fprintf(File1,'1651 9 c000 1 641 10\r\n');  % TI header
    fprintf(File1,'%12.8e\r\n',finput');
    fclose(File1);
end

% 2. feedback data
if data.fbk.save == 1
    filename = strcat('PID_fbk.dat');
    File2 = fopen(filename,'w');
    fprintf(File2,'1651 9 e000 1 641 10\r\n');  % TI header
    fprintf(File2,'%12.8e\r\n',ffeedback');
    fclose(File2);
end

% 3. saturation data
if data.sat.save == 1
    filename = strcat('PID_sat.dat');
    File3 = fopen(filename,'w');
    fprintf(File3,'1651 9 10000 1 641 10\r\n');  % TI header
    fprintf(File3,'%12.8e\r\n',fsat');
    fclose(File3);
end

% 4. control data
if data.act.save == 1
    filename = strcat('PID_ctl.dat');
    File4 = fopen(filename,'w');
    fprintf(File4,'%12.8e\r\n',fcontrol');
    fclose(File4);
end

% end of file
