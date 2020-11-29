drawSpectrogram('ball_bounce_brick_mono.wav');
drawSpectrogram('ball_bounce_paddle_mono.wav');
drawSpectrogram('paddle_widening_mono.wav');

function drawSpectrogram(fileName)
    [Y,fs]=audioread(fileName); % read the WAV file

    Y = fft(Y);
    Y = ifft(Y);

    figure; spectrogram(Y(:,1), 512, 256, 512, fs, 'yaxis'); 
    title(strcat(strcat('Spectrogram for =', fileName)));
end