% Lezione del 19/03/2026

clear
clc

% Al variare di p = 10^a

format long

alpha = 1:10;

[x1, x2, x3, x4] = radici(alpha)

function [s1, s2, s3, s4] = radici(alpha)
    p = 10.^alpha;
    b = (1 + p.^2)./p;
    s1 = sqrt((b + sqrt((-b).^2 - 4)) / 2);
    s2 = -s1;
    s3 = sqrt((b - sqrt((-b).^2 - 4)) / 2);
    s4 = -s3;
end

% for a = 1:10
%     p = 10^a;
% 
%     x1 = sqrt(p);
%     x2 = -x1;
% 
%     x3 = sqrt(1/p);
%     x4 = -x3;
% 
%     b = (1 + p^2)/2;
%     y = x1^4 - b*(x1^2) + 1
% end
