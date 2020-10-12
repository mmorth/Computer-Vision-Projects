A = [2 6; 3 9]
B = [1 2; 3 4]
C = [-5 5; 5 3]

G = [A, zeros(2, 4); zeros(2,2), B, zeros(2,2); zeros(2,4), C]

% Delete the last row and column from the matrix
G(:,end) = []
G(end,:) = []

% Extract the first 4x4 submatrix from G
G(1:4, 1:4)

% Replace G(5,5) with 4
G(5, 5) = 4

% What do you get if you type G(13) and hit return? Can you explain how
% MATLAB got that answer?
G(13)
% It starts at row 1 and iterates through each column, counting by 1. Then
% when the end of that row is reached, it goes to the next row. It
% continues this until it reaches the 13th element.

% What happens if you type G(12,1)=1 and hit return?
G(12,1) = 1
% It adds 0 elements for all new rows created until row 13 where it sets the
% first element in the 13th row to 1 and sets the rest to 0