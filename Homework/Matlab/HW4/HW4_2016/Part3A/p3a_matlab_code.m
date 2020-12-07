fileName = 'example-chord-1.wav';

% Read in the game audio file
[Y,fs]=audioread(fileName);

Y = (Y(:,1) + Y(:,2)) / 2;
p = pitch(Y, fs);
plot(p);

figure; spectrogram(Y, 2048, 256, 2048, fs, 'yaxis'); 
title(strcat(strcat('Spectrogram for =', fileName)));