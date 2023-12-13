% PID_plots : plot selected results in separate graphs

% Figure handle index:
% 1 = servo response
% 2 = feedback data
% 3 = control effort
% 4 = input stimulus
% 5 = servo error
% 6 = saturation limit

% plot response
if data.rsp.plot == 1
    figure(1);
    plot(fresponse)
    grid on
    hold all
    title('Servo Response Plot')
    xlabel('Time (s)')
    ylabel('Output y(t)')
    % overlay input data
    stairs(time,finput)
end

% plot feedback
if data.fbk.plot == 1
    figure(2);
    stairs(time,ffeedback)
    grid on
    hold all
    title('Feedback Plot')
    xlabel('Time (s)')
    ylabel('Feedback ym(k)')
end

% plot control effort
if data.act.plot == 1
    figure(3);
    stairs(time,fcontrol)
    grid on
    hold all
    title('Control Plot')
    xlabel('Time (s)')
    ylabel('Control Effort u(k)')
end

% plot input stimulus
if data.inp.plot == 1
    figure(4);
    stairs(time,finput)
    grid on
    hold all
    title('Input Plot')
    xlabel('Time (s)')
    ylabel('Input r(k)')
end

% plot servo error
if data.err.plot == 1
    figure(5);
    stairs(time,ferror)
    grid on
    hold all
    title('Servo Error Plot')
    xlabel('Time (s)')
    ylabel('Error e(k)')
end

% plot saturation data
if data.sat.plot == 1
    figure(6);
    stairs(time,fsat)
    grid on
    hold all
    title('Saturation Limit Data Plot')
    xlabel('Time (s)')
    ylabel('Data lim(k)')
end

% end of file
