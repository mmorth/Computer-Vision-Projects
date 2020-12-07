% Source: https://www.mathworks.com/matlabcentral/fileexchange/66893-inverse-fast-fourier-transform

I = [ 29.0000 + 0.0000i   2.0000 - 8.6603i   2.0000 + 8.6603i
      -3.0000 - 0.0000i   0.0000 - 1.7321i  -0.0000 + 1.7321i];
myIFFT(I)
  
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