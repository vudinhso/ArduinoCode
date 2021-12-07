clc; clear all; close all; format compact; format shortG

% Create figure
screen_property = get(0,'screensize');
h = figure('outerposition', ...
            [0, screen_property(4)/2, ...  
            screen_property(3)/2, screen_property(4)/2]); 
xlim([0,10]); xlabel('Time (s)');
ylim([-5 275]); ylabel('Angle (deg)');
grid on; hold on; 

% Initialize data
n = 60000; data = zeros(n,2); 
i = 1; j = 1; index_ref = 1;
% p = plot(data(1), data(2), '.', 'MarkerSize', 20);
p = plot(data(1), data(2), '-', 'LineWidth', 2); hold on 

s = serial('COM4', 'BaudRate', 9600);       % Create the serial com
s.Terminator = 'CR/LF';                     % Set the terminator
s.UserData = struct('Data',[],'Count',1);   % Data: y-axis, count: x-axis

fopen(s)        % Open serial com
pause(.5)
flushinput(s)

tic; 

while data(i,1)/1000 < 60
    i=i+1;
    data_str   = fscanf(s);
    data_split = strsplit(data_str, ',');
    data(i,:)  = str2double(data_split);
    
    if data(i,1)/1000 >= 10*j
        index_ref = i;              % setting a new index reference
        xlim([10*j,10*(j+1)]);      % change x-lim
        j = j+1;
    end
    xdata = linspace(   data(index_ref, 1), ...
                        data(i,1), 100);
    if (i-index_ref)>= 100
        dt      = round(linspace(index_ref,i,100));
        ydata   = interp1(data(dt,1), data(dt,2), xdata);
    else
        ydata   = interp1(data(1:i,1), data(1:i,2), xdata);
    end
    
    set(p,  'XData', xdata/1000, ...
            'YData', ydata)
    drawnow
end
toc
fclose(s)
