A = [2 6; 3 9]
B = [1 2; 3 4]
C = [-5 5; 5 3]

G = [A, zeros(2, 4); zeros(2,2), B, zeros(2,2); zeros(2,4), C]
% You can use any combination of the zeros matrix that would lead to this
% result. E.g. instead of zeros(2,4) you could do 2 zeros(2,2)