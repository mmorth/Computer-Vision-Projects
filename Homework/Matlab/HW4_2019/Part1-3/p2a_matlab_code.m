x = [0, 0.7071, 1, 0.7071, 0, -0.7071, -1, -0.7071];
x = double(x);
myFFTResult = myFFT(x)';
matlabFFTResult = fft(x)';

function F = myFFT(f)
    n = length(f);
    
    if n == 1
        F = f(1);
        return;
    end
    
    F = zeros(1, n);
    fEven = f(2:2:end);
    fOdd = f(1:2:end);
    
    FEven = myFFT(fEven);
    FOdd = myFFT(fOdd);
    
    n2 = floor(n/2);
    
    for i = 1:n2
        twiddle = exp(-2*1i*pi*double(i)./n);
        oddTerm = FOdd(i) .* twiddle;
        F(i) = FEven(i) + oddTerm;
        F(i+n2) = FEven(i) - oddTerm;
    end
end
