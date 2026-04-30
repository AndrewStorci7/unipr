% Esercizio 

clc
clear
close all
format long

n = 1000;

A = tril(rand(n));

% disp(A)

x = ones(n, 1);

b = A * x;

function [x] = sost_avanti(b, A, n)
    
    x = [];
    x(1) = b(1) / A(1, 1);

    for i = 2:n
        sommatoria = 0;
        for j = 1:(i-1)
            sommatoria = sommatoria + (A(i, j) * x(j));
        end

        x(i) = (b(i) - sommatoria) / A(i, i);
    end

    return;
end

[x1] = sost_avanti(b, A, n);

% disp(x1);

errore = norm(x - x1)
% disp(errore)

condizionamento = cond(A)