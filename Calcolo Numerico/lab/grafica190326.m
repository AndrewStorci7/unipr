clear
clc
close all

x = linspace(0, 1, 101);
% x = 0:0.05:1;

y = ((1 - x./24)./(1 + x./24 + (x.^2)./384)).^8;

plot(x, y, 'r')

ylabel('ordinate')
xlabel('ascisse')
grid on
title Lezione 19/03/2026

figure
g = @(x) (2 - (x.^2)/2).^2
g2 = @(x) (x.^2/2 + 2).^2

x1 = linspace(-2, 0, 101);
x2 = linspace(0, 2, 101);

plot([x1 x2], [g(x1) g2(x2)], 'r')
% plot(x1, g(x1))
% hold on
% plot (x2, g2(x2))
