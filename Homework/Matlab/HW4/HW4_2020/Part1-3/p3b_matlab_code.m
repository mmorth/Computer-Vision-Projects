% Source: https://www.mathworks.com/matlabcentral/fileexchange/66893-inverse-fast-fourier-transform

I = [0, -4i, 0, 0, 0, 0, 0, 4i];
mi1 = myIFFT(I);
bi1 = ifft(I);

I = [0.0409-0.2008i, 0.4487+0.1418i, -1.6303+0.0000i, 0.4487+0.1418i, 1.3097+0.2008i, 0.4487+0.1418i, -1.6303+0.0000i, 0.4487+0.1418i];
mi2 = myIFFT(I);
bi2 = ifft(I);
  
function f = myIFFT(I)
    [m,n]=size(I);
    wm=zeros(m,m);
    wn=zeros(n,n);
    for x=0:m-1
        for y=0:m-1
            wm(x+1,y+1)=(1/m)*exp(2*pi*i/m*x*y);
        end
    end
    for x=0:n-1
        for y=0:n-1
            wn(x+1,y+1)=(1/n)*exp(2*pi*i/n*x*y);
        end
    end
    ifft2(I);
    f=wm*I*wn;
end