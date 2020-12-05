% TODO: Determine how to find these parameters without guess and check
generateSignal(0.01875, 600, 115, 'extralife-generated.wav');

% Function that generates a synthesized wave
function generateSignal(time, lowf, lowscale, outputFileName)
    % The time of one step of the signal up or down (length of a single
    % segment)
    % base frequency values
    % low frequency is the top frequency value of the first segment
    % low scale is the size of the up/down step

    %initialize the sound samples array
    soundarr=[];

    %set the sample rate
    fs = 44100;

    % Create time interval from 0 to time
    t = 0 : 1/fs : time;

    triangle = 0 : 1/fs : time;

    % generate the triangle wave function
    % for N=1:4
    %     
    %     triangle = triangle + wave;
    % end

    % generate 5 periods of the siren
    for v = 1:18
        %generate the up
        for stair = 0:10
            triangle = (2*lowf*(t-(1/lowf).*floor(t.*lowf + 1/2)).*(-1).^(floor(t*lowf + 1/2)));
            lowf = lowf + lowscale;

            %add this segment to the sound
            soundarr = [soundarr, triangle];
        end

        %generate the down
        for stair = 0:10
            triangle = (2*lowf*(t-(1/lowf).*floor(t.*lowf + 1/2)).*(-1).^(floor(t*lowf + 1/2)));

            lowf = lowf - lowscale;

            soundarr = [soundarr, triangle];
        end
    end

    %display the spectrogram
    figure; spectrogram(soundarr,512,256,512,fs, 'yaxis');
    title(strcat(strcat('Spectrogram for =', outputFileName)));

    %play the sound
    %sound(soundarr,fs);

    %save the sound to file
    audiowrite(outputFileName, soundarr, fs);
end