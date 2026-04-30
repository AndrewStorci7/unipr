%% Esercizio 3 grafici

t = linspace(0, 2*pi, 361);

% f = @(t) (3 + 6*cos(t));
% f2 = @(t) (8 + 6*sin(t));

x = 3 + 6*cos(t);
y = 8 + 6*sin(t);

plot(x, y)
axis equal
grid on