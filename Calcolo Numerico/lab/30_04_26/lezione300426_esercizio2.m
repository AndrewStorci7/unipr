% Esercizio 1 Esercitazione Calcolo numerico Esercizi Algebra Lineare

clc
clear
close all
format short

n = 10;

% v = rand(1, n);
% v2 = rand(1, n-1);
v = 10 * ones(1, n);
v2 = 2 * ones(1, n-1);
% v3 = rand(1, n - 1);

A = diag(v) + ...
    diag(v2, 1) + ...
    diag(v2, -1);

disp(A);

function [d] = calc_det(A, i, n)
    if i == n
        return;
    end

    if i <= 1
        % d(0) = 1;
        d(1) = A(1, 1);
        return;
    end
    
    d(i) = (A(i, i) * d(i - 1)) - (A(i + 1, i)*A(i, i + 1)*d(i - 2));

    [d] = calc_det(A, i + 1, n); 
end

function [L, U] = LU(A, n)
    [det] = calc_det(A, 0, n); 
    
    if det == 0
        error("Questa matrice non può essere fattorizzata in una matrice L*U");
    end

    L = eye(n);
    U = 0* ones(n);
    U(1, 1:n) = A(1, 1:n);

    for k = 1:n

        for j = k:n
            sommatoria = 0;
            for p = 1:k-1
                sommatoria = L(k, p)*U(p, j);
            end
        
            U(k, j) = (A(k, j) - sommatoria);
        end

        for i = k+1:n
            sommatoria = 0;
            for p = 1:k-1
                sommatoria = L(i, p)*U(p, j);
            end

            L(i, k) = (A(i, k) - sommatoria) / U(k, k);
        end
    end
end

[L, U] = LU(A, n)
disp(L)
disp(U)

% controllo che la fattorizzazione ottenuta sia corretta
% utilizzando la funzione lu() di matlab
[L_c, U_c] = lu(A)
L == L_c
U == U_c

% controllo che la fattorizzazione ottenuta si corretta
L * U == A