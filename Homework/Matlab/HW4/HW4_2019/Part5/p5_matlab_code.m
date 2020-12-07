% Call function to draw spectrogram for all audio files
drawSpectrogram('PokemonBattleMusic.wav');
drawSpectrogram('PokemonHealingSounds.wav');
drawSpectrogram('PokemonMusicWall.wav');

% Function that draws the spectrogram of input audio file
function drawSpectrogram(fileName)
    % Read the audio
    [Y,fs]=audioread(fileName); % read the WAV file

    % FFT and inverse FFT (can be changed to updated spectrogram format)
    Y = fft(Y);
    Y = ifft(Y);

    % Display the resulting spectrogram
    figure; spectrogram(Y(:,1), 512, 256, 512, fs, 'yaxis'); 
    title(strcat(strcat('Spectrogram for =', fileName)));
end