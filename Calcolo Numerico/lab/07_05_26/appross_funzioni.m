%% Esercitazione sull'approssimazione delle funzioni

clc
clear
close all

% Utilizzo di polyfit
% restituisce il vettore riga contenente i vari polinomi di grado N
% dove N è il grado del polinomio.

% utilizzo di polyval
% analogo a polyfit ma 

n = 5;

x = linspace(0, 2, n + 1);

f = @(x) exp(x).*sin(2 * x);

P = polyfit(x, f(x), n);

y = @(x) polyval(x, P);

x2 = linspace(0, 2, 1000);

grid on;
plot(x2, f(), 'Color', 'g', 'DisplayName', 'f(x)');
hold on;

grid on;
plot(x2, y, 'Color', 'r', 'DisplayName', 'p(x)');
hold on;

grid on;
plot(x2, P, 'DisplayName', 'Punti di interpolazione');
hold on;

legend()




