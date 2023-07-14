%% Preparing the serial communication
% https://www.mathworks.com/help/matlab/import_export/read-streaming-data-from-arduino.html

% Clear the workspace
% Select the correct port and correct Baudrate
% Set the terminator to "CR/LF" (CR = Carriage Return and LF = Line Feed)
clc; clear; close all; format compact; format shortG
s = serialport('COM7', 115200);
configureTerminator(s, "CR/LF");

%% Use this code to read data from the serial port
% Flush the previous data
% Read the data from the serial COM
% Break the loop with Ctrl+C
flush(s);
while 1
    data = str2double(strsplit(readline(s), ','))
end

%% Use this code to save data and plot data (no real-time visualization)
% Clean the workspace
% Set the time interval of the measurement in ms
% Flush the previous data
clc; close all; clear data
disp('Serial COM reading')
interval = 3*1e3;  
flush(s); 

% Read the first data from the COM - the first data is usually corrupted
% Read the second data from the COM - the second data is usually good
% Initialize the start time and the loop variable
str2double(strsplit(readline(s), ','))
tmp = str2double(strsplit(readline(s), ','))
time_init = tmp(1);
i = 1; 

% Start the serial COM reading
while tmp(1) <= time_init+interval
    tmp = str2double(strsplit(readline(s), ','));
    data(i,:) = tmp;
    i = i+1;
end

% Create figure: one quarter of the screen size, top left
screen_property = get(0,'screensize');
h = figure('outerposition', ...
            [0, screen_property(4)/2, ...  
            screen_property(3)/2, screen_property(4)/2]); 
grid on; hold on; 

% Plot the acquired data
plot(data(:,1)/1000,data(:,3)); grid on
xlabel("Time (s)"); 
ylabel("Angle (deg)"); 

%% Use this code for real-time data vizualisation (plot angle vs time)
clc; close all; flush(s);
% Prepare the parameters for the animated line
h1 = animatedline('Color','b','LineWidth',2, 'MaximumNumPoints',500); grid on; 
screen_property = get(0,'screensize');
set(gcf, "OuterPosition", [0, screen_property(4)/2, ...  
    screen_property(3)/2, screen_property(4)/2])
xlabel("Time (s)"); ylabel("Angle (deg)"); 
ylim([-5 305]);

% Start the serial COM reading and animation
% Break the loop with Ctrl+C
while 1
    data  = str2double(strsplit(readline(s), ',')); 
    addpoints(h1,data(1)/1000,data(2));
    drawnow;
end

%% Use this code for real-time data vizualisation - Angle Display
clc; close all; flush(s);
% Prepare the parameters for the animated line
h1 = animatedline('Color','b','LineWidth',2, 'MaximumNumPoints',2); grid on; 
screen_property = get(0,'screensize');
set(gcf, "OuterPosition", [0, screen_property(4)/2, ...  
    screen_property(3)/2, screen_property(4)/2])
xlim([-1.2 1.2]); ylim([-1.2 1.2]); axis square

% Start the serial COM reading and animation
% Break the loop with Ctrl+C
while 1
    data  = str2double(strsplit(readline(s), ',')); % Read serial COM
    x = cosd(data(2)); y = sind(data(2)); 
    addpoints(h1,[0, x],[0, y]);
%     text(0.8,0.8,['\leftarrow' num2str(data(2))] , 'Color','red','FontSize',14)
    drawnow;
end
