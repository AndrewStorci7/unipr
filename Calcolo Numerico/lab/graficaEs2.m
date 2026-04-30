clear
clc
close all

grid on
yscale log

for m = 1:6
    x1 = linspace(-m, 0, 101);
    x2 = linspace(0, m, 101);

    f = @(x) (m - (x.^2)/m).^m;
    f2 = @(x) ((x.^2)/m + m).^m;

    hold on
    % figure
    % plot(x1, f(x1), 'r', x2, f2(x2), 'g')
    plot([x1 x2], [f(x1) f2(x2)])
end

figure
for m = 1:6
    x1 = linspace(-m, 0, 101);
    x2 = linspace(0, m, 101);

    f = @(x) (m - (x.^2)/m).^m;
    f2 = @(x) ((x.^2)/m + m).^m;

    hold on
    subplot(2, 3, m)
    
    % plot([x1 x2], [f(x1) f2(x2)])
    semilogy([x1 x2], [f(x1) f2(x2)])
end
