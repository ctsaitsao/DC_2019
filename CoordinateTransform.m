% Written by Tiger Nie for the 2019 McCormick robotics competition
% 
% This script calculates and visualise the coefficients to a multiple 
% regression model for calibrating a sensor coordinate system to a known 
% real coordinate system, where
% real_x = bx(1) + bx(2)*sensor_x + bx(3)*sensor_y + bx(4)*sensor_x.*sensor_y;
% real_y = by(1) + by(2)*sensor_x + by(3)*sensor_y + by(4)*sensor_x.*sensor_y;


% Linear coordinate transform
sensor_x = [3.67,3.77,3.88,2.4,2.5,2.6,0.9,1.06,1.19]';
sensor_y = [1.69,0.25,-1.22,1.85,0.13,-1.56,2.44,0.025,-2.13]'; 
real_x = [0,300,600,0,300,600,0,300,600]';
real_y = [600,600,600,300,300,300,0,0,0]';


X = [ones(size(sensor_x)) sensor_x sensor_y sensor_x.*sensor_y];

% Regression for real x
bx = regress(real_x,X);    % Removes NaN data
figure();hold on;
scatter3(sensor_x,sensor_y,real_x,'filled')
title("X")
sensor_xfit = min(sensor_x):0.1:max(sensor_x);
sensor_yfit = min(sensor_y):0.1:max(sensor_y);
[sensor_xFIT,sensor_yFIT] = meshgrid(sensor_xfit,sensor_yfit);
XFIT = bx(1) + bx(2)*sensor_xFIT + bx(3)*sensor_yFIT + bx(4)*sensor_xFIT.*sensor_yFIT;
mesh(sensor_xFIT,sensor_yFIT,XFIT)
xlabel('sensor_x')
ylabel('sensor_y')
zlabel('real_x')
view(50,10)
hold off

% Regression for real y
by = regress(real_y,X);    % Removes NaN data
figure();hold on;
scatter3(sensor_x,sensor_y,real_y,'filled')
title("Y")
sensor_xfit = min(sensor_x):0.1:max(sensor_x);
sensor_yfit = min(sensor_y):0.1:max(sensor_y);
[sensor_xFIT,sensor_yFIT] = meshgrid(sensor_xfit,sensor_yfit);
YFIT = by(1) + by(2)*sensor_xFIT + by(3)*sensor_yFIT + by(4)*sensor_xFIT.*sensor_yFIT;
mesh(sensor_xFIT,sensor_yFIT,YFIT)
xlabel('sensor_x')
ylabel('sensor_y')
zlabel('real_y')
view(50,10)
hold off