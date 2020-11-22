x = [0, 0.7071, 1, 0.7071, 0, -0.7071, -1, -0.7071];

result = myFFT(x.')

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