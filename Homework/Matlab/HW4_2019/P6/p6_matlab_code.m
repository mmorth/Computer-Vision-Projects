%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Create the dial tone audio files for various area codes %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
fs = 44100;

% Dial area code for Chicago, IL (312)
dialAreaCode = dial_number('312', 0.5, 0.2, fs);  
sound(dialAreaCode, fs);
audiowrite('dial-tone-312.wav', dialAreaCode, fs);

% Dial area code for Orlando, FL (927)
dialNumber = dial_number('927', 1, 0.3, fs);  
sound(dialNumber, fs);
audiowrite('dial-tone-927.wav', dialNumber, fs);

% Dial area code for Mason City, IA (641)
dialNumber = dial_number('641', 0.4, 0.1, fs);  
sound(dialNumber, fs);
audiowrite('dial-tone-641.wav', dialNumber, fs);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Plot the spectograms for the dial tone audio waves %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

plotSpectogram('dial-tone-312.wav');
plotSpectogram('dial-tone-927.wav');
plotSpectogram('dial-tone-641.wav');

% This function plots the spectogram for the given audio file (must be in
% active directory
function plotSpectogram(fileName)
    [Y,fs]=audioread(fileName); % read the WAV file

    % Y   - audio data samples
    % 512 - window size  (in samples)
    % 256 - overlap      (in samples)
    % 512 - FFT size     (in samples)
    % fs  - sampling frequency (in Hz)
    % 'yaxis' - put the frequencies along the y axis
    figure; spectrogram(Y, 512, 256, 512, fs, 'yaxis'); 
    title(strcat('Spectrogram for =', fileName));
end