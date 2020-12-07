x = [0, 0.7071, 1, 0.7071, 0, -0.7071, -1, -0.7071];
mySDFT(x);

% Function that implements the slow discrete fourier transform
function r = mySDFT(x)
    % Transpose the input vector to enable matrix multiplication
    x = x.';
    % Compute the DFT matrix to multiply against the input array to get the
    % fourier transform
    a = dftmtx(length(x));
    % Matrix multiply the input with the DFT matrix to determine the DFT of
    % the input vector
    r = a*x;
end