A=rand(10)

% Multiply all elements by 100 and then round off all elements of the
% matrix to integers with the command A=fix(A)
A = 100*A
A=fix(A)

% Replace all elements of A < 10 with zeros
A(A < 10) = 0

% Replace all elements of A > 90 with infinity (inf)
A(A > 90) = inf

% Extract all 30 <= aij <= 50 in a vector b, that is, find all elements of
% A that are between 30 and 50 and put them in a vector b
b = A(A >= 30 & A <= 50)