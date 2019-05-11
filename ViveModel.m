% Written by Tiger Nie for the 2019 McCormick robotics competition
% 
% For testing the multiple regression matrix calculated from the
% transformation of the vive sensor coordinate system into a real
% coordinate system
% 
% Usage: [rea_x, real_y] = ViveModel(sensor_x,sensor_y)

function [real_x, real_y] = ViveModel(sensor_x,sensor_y)

bx = [2.912864742803728e+02;14.007261060748366;-1.021303206395161e+02;-28.018365770908364];
by = [-2.374575670196188e+02;2.192273053010640e+02;12.998587140608503;0.541769828988158];

real_x = bx(1) + bx(2)*sensor_x + bx(3)*sensor_y + bx(4)*sensor_x.*sensor_y;
real_y = by(1) + by(2)*sensor_x + by(3)*sensor_y + by(4)*sensor_x.*sensor_y;
