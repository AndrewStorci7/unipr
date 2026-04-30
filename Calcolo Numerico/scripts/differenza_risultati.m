clear
clc

% con x circa 1 i risultati sono diversi
x = 0.999998; 
% x = 1; con x = 1 i risultati sono uguali

y = (1 - x)^6

y2 = (x^6 - 6*x^5 + 15*x^4 - 20*x^3 + 15*x^2 - 6*x + 1)

y == y2