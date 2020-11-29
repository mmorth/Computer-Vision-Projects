[Y,fs]=audioread('NoMusic_1_Audio.mp3'); % read the WAV file

% figure; spectrogram(Y(:,2), 512, 256, 512, fs, 'yaxis'); 
[S,F,T] = spectrogram(Y(:,2), 512, 256, 512, fs, 'yaxis'); 
% title(strcat(strcat('Spectrogram for =', fileName)));

% S = abs(S);

% drawSpectrogram('NoMusic_1_Audio.mp3');
% drawSpectrogram('NoMusic_2_Audio.mp3');
% 
% function drawSpectrogram(fileName)
%     
% end