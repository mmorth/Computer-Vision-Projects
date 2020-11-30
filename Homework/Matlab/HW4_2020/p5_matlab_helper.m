% [Y,fs]=audioread('NoMusic_1_Audio.mp3'); % read the WAV file
[Y,fs]=audioread('areacode1.wav'); % read the WAV file

% figure; spectrogram(Y(:,2), 512, 256, 512, fs, 'yaxis'); 
% title(strcat(strcat('Spectrogram for =', fileName)));
[sb,fb,tb,pb] = spectrogram(Y, 512, 256, 512, fs, 'yaxis'); 

% for i = 1:size(s, 1) r
%    s(i,:) = log(abs(s(i,:)));
% end

figure; plot(sb);
figure; surf(tb,fb,log(abs(sb)),'EdgeColor','none');
axis xy; axis tight; colormap(jet); view(0,90);
% figure; plot(t,s+18);

% drawSpectrogram('NoMusic_1_Audio.mp3');
% drawSpectrogram('NoMusic_2_Audio.mp3');
% 
% function drawSpectrogram(fileName)
%     
% end