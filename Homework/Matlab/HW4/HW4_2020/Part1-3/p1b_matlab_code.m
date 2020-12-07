x = [0, -4i, 0, 0, 0, 0, 0, 4i];
mySIDFT(x);

% A function that represents the slow inverse discrete foruier transform
function r = mySIDFT(x)
    % Transpose the input vector to enable matrix multiplication
    x = x.';
    % Compute the inverse DFT matrix to multiply against the input array to get the
	% fourier transform
    a = conj(dftmtx(length(x)))/length(x);
    % Matrix multiply the input with the DFT matrix to determine the DFT of
	% the input vector
    r = a*x;
end