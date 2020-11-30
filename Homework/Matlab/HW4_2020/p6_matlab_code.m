[Y,fs]=audioread('NoMusic_1_Audio.mp3'); % read the WAV file

% figure; spectrogram(Y(:,2), 512, 256, 512, fs, 'yaxis'); 
% title(strcat(strcat('Spectrogram for =', fileName)));
spectrogram(Y(:,2), 512, 256, 512, fs, 'yaxis');
colormap bone;
[s,f,t,p] = spectrogram(Y(:,2), 512, 256, 512, fs, 'yaxis'); 

% f1 = f > 1000 & f < 9500;
% t1 = t > 0.0;
% 
% p = p(f1,t1);
% 
% m1 = medfreq(p,f(f1));
% 
% hold on
% plot(t(t1),m1/1000,'linewidth',4)
% hold off

% p = 10*log10(abs(p));

% figure; plot(s);
% figure; surf(t,f,log(abs(s)),'EdgeColor','none');
% axis xy; axis tight; colormap(jet); view(0,90);

% drawSpectrogram('NoMusic_1_Audio.mp3');
% drawSpectrogram('NoMusic_2_Audio.mp3');
% 
% function drawSpectrogram(fileName)
%     
% end