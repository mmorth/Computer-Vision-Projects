x = [0, -4i, 0, 0, 0, 0, 0, 4i];
myFFTResult = abs(myIFFT(x)).*sign(angle(myIFFT(x)))
matlabFFTResult = fft(x)

% Recursive function that computes the Fast Fourier Transform in O(nlogn)
% time
function F = myIFFT(f)
    % Check for the base case
    n = length(f);
    if n == 1
        F = f;
        return;
    end
    
    % Split the signal up into even and odd elements for faster computing
    fEven = f(1:2:n);
    fOdd = f(2:2:n);
    
    FEven = myIFFT(fEven);
    FOdd = myIFFT(fOdd);
    
    % Apply the vectorized wn constants from the DFT matrix
    wn = exp(-2*pi*1i.*[0:1:(n/2)-1]/n);
    FOdd = FOdd.*wn;
    
    % Store the final result
    F = [FEven+FOdd FEven-FOdd];
end
