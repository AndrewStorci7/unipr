%% Esercizio 1 calcolo interpolazione

clc
clear
close all

max_it = 1000;
tolleranza = 1e-10;
x0 = 1;

A = [[3 0 4]; [7 4 2]; [-1 -1 -2]]
b = [7; 13; -4];

function [r, xk1, it] = gauss_sediel(A, b, x0, max_it, tol)
    xk = x0;
    it = 0;

    diagonale = diag(A);
    D = diag(diagonale);
    E = tril(A, -1);
    F = triu(A, 1);

    B = -inv(D+E)*F;
    q = inv(D+E).*b;
    r = max(abs(eig(B)));
    xk1 = B*xk + q;
    it = it + 1;

    while norm(xk1 - xk) > tol && it <= max_it
        xk = xk1;
        xk1 = B * xk  + q;
        it = it + 1;
    end
end

[r, x, i] = gauss_sediel(A, b, x0, max_it, tolleranza)