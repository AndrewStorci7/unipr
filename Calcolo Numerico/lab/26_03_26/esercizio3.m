% Esercizio 3 26/03/26
clear
clc
close all

format long
interval = [0.6:1];
max_iter = 100;

function [s, c] = bisezione(f, a, b, count)
    tollerance = 1e-15;
    count = count + 1;

    if f(0.6) * f(1) > 0
        error("La funzione cambia di segno");
        % s = -1;
        % return
    end

    medio = (a + b)./2;

    % disp(f(medio))
    
    if f(medio) == 0 || abs(f(medio)) < tollerance
        s = medio;
        c = count;
        return
    else
        if f(a) * f(medio) < 0
            [s, c] = bisezione(f, a, medio, count);
        else
            [s, c] = bisezione(f, medio, b, count);
        end
    end
end

x = linspace(0.6, 1);
f = @(x) (x./8).*(63*x.^4 - 70*x.^2 + 15);
f_polyval = @(x) polyval([63/8, 0, -70/8, 0, 15/8, 0], x);

plot(x, f(x))
grid on;

[prova1, c1] = bisezione(f, 0.6, 1, 0)

[prova2, c2] = bisezione(f_polyval, 0.6, 1, 0)

fzero_f = fzero(f, 1)