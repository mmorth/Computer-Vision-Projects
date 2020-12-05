% TODO: Determine how to find these parameters without guess and check
generateSignal('extralife-generated.wav');

% Function that generates a synthesized wave
function generateSignal(outputFileName)
    %set the sample rate
    fs = 44100;

    % Setup Pause Time
    wave = 0;
    pauseTime = 0 : 1/fs : 0.05;
	pauseWave = sin(pauseTime);
    wave = [wave pauseWave];
    
	pauseTime = 0 : 1/fs : 0.01;
	pauseWave = sin(pauseTime);
	
	for i = 1 : 10
		wave = [wave generateFrequencies(fs)];
		wave = [wave pauseWave];
	end

    figure; spectrogram(wave,512,256,512,fs, 'yaxis');
    title(strcat(strcat('Spectrogram for =', outputFileName)));
    
    %save the sound to file
    audiowrite(outputFileName, wave, fs);
end

function [soundarr] = generateFrequencies(fs)
    % Create time interval from 0 to time
	t = 0 : 1/fs : 0.19;

    % Calculate corresponding row and column waves
    % High = 10, low = 0.2
    freqInterval = 375;
    numLevels = 58;
    soundarr = 0;
    soundarr = soundarr + 2.*exp(-t*5).*sin(2 * pi * 10 * t);
    amplitudes = [10 10 0.055 10 0.055 0.055 0.055 10 0.055 1 0.055 0.05 0.05 0.05 0.4 0 1 0.05 0.05 0.05 0.055 0.055 0.05 5 0.05 .05 .05 1 .05 .3 .4 0 .4 0.05 .05 .4 .05 .05 .05 3 .05 .05 .05 .05 .05 0.05 0.05 0 0.05 0.05 .05 .05 0.05 0.05 .05 1.5 .05 .05 .05 .4 .05 .05 0.05 0.05 0];
    for i = 1:numLevels
       soundarr = soundarr + amplitudes(i).*exp(-t*10).*sin(2 * pi * (i)*freqInterval * t); 
    end
	
	% Calculate final wave
	soundarr = soundarr / numLevels;
end