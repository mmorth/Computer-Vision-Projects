A=ones(20)
A(6:15, 6:15) = zeros(10,10)
spy(A)

A(1:5, 16:20) = zeros(5,5)
A(16:20, 16:20) = zeros(5,5)
spy(A)