A = [2 6; 3 9]
B = [1 3; 3 4]
C = [-5 5; 5 3]

fprintf('Is matrix addition communtative?\n')
isequal(A+B, B+A)
fprintf('Yes')

fprintf('\nIs matrix addition associative?\n')
isequal((A+B)+C, A+(B+C))
fprintf('Yes')

fprintf('\nIs multiplication with a scalar distributive?\n')
a = 5
isequal(a*(A+B), a*A+a*B)
fprintf('Yes')

fprintf('\nIs multiplication with a matrix distributive?\n')
isequal(A*(B+C), A*B+A*C)
fprintf('Yes')

fprintf('\nMatrices are different from scalars\n')
isequal(A*B, A*C)
fprintf('No')
isequal(A*B, B*A)