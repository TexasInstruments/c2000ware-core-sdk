% GSM_example.m - example script for the Gain Scheduler Module
close all; clc; clear all;

% plot target function
dx = 0.01;
x = 0:dx:1;
y = zeros(1, size(x,2));
k = 1;
for i = 0:dx:1
   y(k) = target(x(k));
   k = k+1;
end
plot(x,y)

%% find sector index
N = 8;
n = zeros(1,N);
I = 1/N;
i = 0;
for k = 1:N
    i = i + I;
    n(k) = i;
end

%% load LUT offsets
c = zeros(1,N);
for k = 1:N
    c(k) = target(n(k));
end

%% load LUT slopes
m = zeros(1,N);
m(1) = c(1) / I;
for k = 2:N
   m(k) = (c(k) - c(k-1)) / I;
end

%% plot GSM segments
L = fix(size(x,2)/N);
y1 = zeros(1,L);
y2 = zeros(1,L);
y3 = zeros(1,L);
y4 = zeros(1,L);
y5 = zeros(1,L);
y6 = zeros(1,L);
y7 = zeros(1,L);
y8 = zeros(1,L);
x1 = 0:dx:I;
x2 = I:dx:2*I;
x3 = 2*I:dx:3*I;
x4 = 3*I:dx:4*I;
x5 = 4*I:dx:5*I;
x6 = 5*I:dx:6*I;
x7 = 6*I:dx:7*I;
x8 = 7*I:dx:8*I;

k = 1;
for xi = 0:dx:I
    y1(k) = m(1)*xi;
    y2(k) = m(2)*xi + c(1);
    y3(k) = m(3)*xi + c(2);
    y4(k) = m(4)*xi + c(3);
    y5(k) = m(5)*xi + c(4);
    y6(k) = m(6)*xi + c(5);
    y7(k) = m(7)*xi + c(6);
    y8(k) = m(8)*xi + c(7);
    k = k + 1;
end
hold all
plot(x1,y1)
plot(x2,y2)
plot(x3,y3)
plot(x4,y4)
plot(x5,y5)
plot(x6,y6)
plot(x7,y7)
plot(x8,y8)

% target function
function y = target(x)
%    y = sin(2*pi*x);
%    y = x*x;
    y = x*(3*x - 2);
%    y = exp(2*x) - 1;
%    y = -tan(pi*x/3);
end

% end of file
