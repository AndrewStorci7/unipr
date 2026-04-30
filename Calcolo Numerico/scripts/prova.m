clc
clear
close all
format long

x = 5;
y = @(x) 5 - x;

% T = table([], [], [], "VariableNames", [ "N", "Error", "Percentual" ]);
T = table('Size',[0,3],'VariableTypes',["double","double","double"],'VariableNames',["N","Error","Percentual"]);

function [err, T] = calc_errore(x, y, n, T)
    
    err = (((x - (y(n)))*(1 + eps) - (x - y(n)))/(x - y(x)));
    
    row = table(n, err, err * 100, 'VariableNames',["N","Error","Percentual"]);
    T = [T; row];
    if (n < 0)
        return;
    end
    [err, T] = calc_errore(x, y, n - 0.001, T);
end

[error, resultT] = calc_errore(x, y, 0.1, T);

disp(resultT)


