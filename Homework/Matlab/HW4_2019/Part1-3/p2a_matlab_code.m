x = [0, 0.7071, 1, 0.7071, 0, -0.7071, -1, -0.7071];
x = double(x);
myFFTResult = myFFT(x)';
matlabFFTResult = fft(x)';

function F = myFFT(f)
    n = length(f);
    
    if n == 1
        F = f;
        return;
    end

    wn = exp(2*pi*1i/n);
    w = 1;
    
    fEven = f(2:2:end);
    fOdd = f(1:2:end);
    
    FEven = myFFT(fEven);
    FOdd = myFFT(fOdd);
    
    n2 = floor(n/2);
    
    for i = 1:n2
        F(i) = FEven(i) + w*FOdd(i);
        F(i+n2) = FEven(i) - w*FOdd(i);
        w = w*wn;
    end
end
