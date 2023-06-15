% https://www.mathworks.com/help/matlab/import_export/read-streaming-data-from-arduino.html
clc; clear; close all; format compact; format shortG

%% Preparing the serial communication
% Select the correct port and correct Baudrate
% Set the terminator to "CR/LF" (CR = Carriage Return and LF = Line Feed)
% Flush previous data
s = serialport('COM7', 9600);
configureTerminator(s, "CR/LF");

%% Use this code to read data from the serial port
% Break the loop by pushing Ctrl+C
flush(s);
while 1
    data = str2double(strsplit(readline(s), ','))
end

%% Use this code to save and plot data
% Save n number of data
delay = .05;    % delay in the serial communication (depending on the variable in Arduino code)
duration = 5;  % duration of the experiment in sec
n = duration/delay + 1;
i=1;
flush(s); pause(.1);

while i <= n
    tmp = str2double(strsplit(readline(s), ','))
    data(i,:) = tmp;
    i = i+1;
end

% Create figure: one quarter of the screen size, top left
screen_property = get(0,'screensize');
h = figure('outerposition', ...
            [0, screen_property(4)/2, ...  
            screen_property(3)/2, screen_property(4)/2]); 
grid on; hold on; 
plot(data(:,1)/1000,data(:,2)); grid on
xlabel("Time (s)"); 
ylabel("Angle (deg)"); 

%% More interactive plot




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
