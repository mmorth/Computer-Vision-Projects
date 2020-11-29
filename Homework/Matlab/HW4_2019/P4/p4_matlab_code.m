[y, Fs] = audioread('ball_bounce_brick_mono.wav');

s = fft(y);
f = Fs/2*linspace(0,1,length(y)/2+1);

plot(f,abs(s(1:floor(length(y)/2)+1)));