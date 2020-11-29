drawSpectrogram('MC_animal_mono.wav');
drawSpectrogram('MC_piston_mono.wav');
drawSpectrogram('MC_water_mono.wav');

function drawSpectrogram(fileName)
    [Y,fs]=audioread(fileName); % read the WAV file

    figure; spectrogram(Y(:,1), 512, 256, 512, fs, 'yaxis'); 
    title(strcat(strcat('Spectrogram for =', fileName)));
end