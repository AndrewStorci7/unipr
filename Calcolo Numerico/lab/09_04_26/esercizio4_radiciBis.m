% Esercizio 4 scheda Radici Bis

clear
clc
close all
format long

tolleranza = 10^-10;

f = @(x) ((cos(2*x).^2) - x.^2);
f_d = @(x) (-2*sin(4*x) - 2*x);

x = linspace(-10, 10);
subplot(1, 2, 1);
plot(x, f(x))
grid on
title funzione

subplot(1, 2, 2);
plot(x, f_d(x))
grid on
title derivata

function [s, it] = newton(f, f_d, x, t, n_it)
    if (abs(f(x)) > t)
        if (abs(f_d(x)) ~= 0)
            x_k = abs(x - (f(x)/f_d(x)));
            n_it = n_it + 1;
            [s, it] = newton(f, f_d, x_k, t, n_it);
        else
            error("La derivata risulta 0");
        end
    else
        s = x;
        it = n_it;
        return
    end
end

function [sol, it] = corde(f, x, a, b, t, n_it)
    if (n_it > 10000)
        sol = x
        it = n_it
        return
    end

    if (abs(f(x)) > t)
        x_k = x - (f(x)*((b - a)/(f(b) - f(a))));
        n_it = n_it + 1;
        [sol, it] = corde(f, x_k, a, b, t, n_it);
    else
        sol = x;
        it = n_it;
        return
    end
end

[sol1, it1] = newton(f, f_d, 1, tolleranza, 0)
[sol2, it2] = corde(f, 1, 0, 1000, tolleranza, 0)

fzero = fzero(f, 1)
