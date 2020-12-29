%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Read from a WAV file and plot the Spectrogram
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[Y,fs]=audioread('c4-piano.wav'); % read the WAV file
Y = (Y(:,1) + Y(:,2)) / 2;
figure;
plot(1:1000,Y(1:1000), 'b.')     % plot the first 1000 samples 
xlabel('Sample number (only the first 1000)');
ylabel('Y');
title('The wave for a 440 Hz sine, sampled at 44,100 Hz');

% Y   - audio data samples
% 512 - window size  (in samples)
% 256 - overlap      (in samples)
% 512 - FFT size     (in samples)
% fs  - sampling frequency (in Hz)
% 'yaxis' - put the frequencies along the y axis
figure; spectrogram(Y, 512, 256, 512, fs, 'yaxis'); 
title('Spectrogram for 440 Hz Sine');

% store the spectrogram data in the complex matrix S
S=spectrogram(Y, 512, 256, 512, fs, 'yaxis');

% play it
sound(Y, fs)