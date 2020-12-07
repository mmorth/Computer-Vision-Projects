x1 = [0, 0.7071, 1, 0.7071, 0, -0.7071, -1, -0.7071];

m1 = myFFT(x1.')
b1 = fft(x1.')

x2 = [-0.0144+0.0709i, -0.1586-0.0502i, 0.5764, -0.1586-0.0502i, -0.4631-0.0709i, -0.1586-0.0502i, 0.5764, -0.1586-0.0502i];

m2 = myFFT(x2.')
b2 = fft(x2.')

function X = myFFT(x)
    %only works if N = 2^k
    N = numel(x);
    xp = x(1:2:end);
    xpp = x(2:2:end);
    if N>=8
        Xp = myFFT(xp);
        Xpp = myFFT(xpp);
        X = zeros(N,1);
        Wn = exp(-1i*2*pi*((0:N/2-1)')/N);
        tmp = Wn .* Xpp;
        X = [(Xp + tmp);(Xp -tmp)];
    else
        switch N
            case 2
                X = [1 1;1 -1]*x;
            case 4
                X = [1 0 1 0; 0 1 0 -1i; 1 0 -1 0;0 1 0 1i]*[1 0 1 0;1 0 -1 0;0 1 0 1;0 1 0 -1]*x;
            otherwise
                error('N not correct.');
        end
    end
end
