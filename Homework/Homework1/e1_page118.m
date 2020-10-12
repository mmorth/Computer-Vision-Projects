%SINSERIES: computes sin(x) from series expansion

% Does sinseries exist?
exist('sinseries');
% Retruns the type of name as a number where the value describes the value

% sinseries code
x = pi/6;
n = 4;

sinx = 0;
for k=1:n
    sinx = sinx + (-1)^(k-1) * ((x^(2*k-1) / factorial(2*k-1)));
end

sinx