drawSpectrogram('siren1.wav');
drawSpectrogram('siren2.wav');
drawSpectrogram('siren3.wav');
drawSpectrogram('siren4.wav');
drawSpectrogram('siren5.wav');

function drawSpectrogram(fileName)
    [Y,fs]=audioread(fileName); % read the WAV file

    figure; spectrogram(Y(:,1), 512, 256, 512, fs, 'yaxis'); 
    title(strcat(strcat('Spectrogram for =', fileName)));
end