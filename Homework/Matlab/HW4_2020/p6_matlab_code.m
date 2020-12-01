% Process and write videos for both
processAudioAndWriteVideo('NoMusic_1_Audio.mp3', 'NoMusic_1.mp4', 'NoMusic_1_Coins.avi');
processAudioAndWriteVideo('NoMusic_2_Audio.mp3', 'NoMusic_2.mp4', 'NoMusic_2_Coins.avi');

% Processes audio and writes the output to a video
function processAudioAndWriteVideo(audioFileName, videoFileName, outputVideoName)
    % Read in the game audio file
    [Y,fs]=audioread(audioFileName);

    % Obtain the necessary spectrogram variables for processing
    [s,f,t,p] = spectrogram(Y(:,2), 512, 256, 512, fs, 'yaxis'); 

    % Filter the spectral response to only the frequencies and powers that
    % correspond to the coin collected response
    f1 = (f > 1200 & f < 1400) | (f > 3850 & f < 4100) | (f > 6500 & f < 6600) | (f > 9100 & f < 9350);
    t1 = t > 0.0;
    p = p(f1,t1);
    p(10*log10(abs(p)) < -45) = 0;

    m1 = medfreq(p,f(f1));

    % Store variables for storing the coin collected locations
    coinCollectionTimes = [];
    first = 0;
    streak = 0;
    for i = 1:length(m1)
        % Check if value is non-NAN (could correspond to a coin collected
        % spectral response
        if ~isnan(m1(i))
            if streak == 0
               first = i; 
            end
            streak = streak + 1;
        else
            % Check if the streak of non-NAN values is larger than 60 (matches
            % spectral response for coin collected
            if streak > 60
               coinCollectionTimes = [coinCollectionTimes, first]; 
            end
            % Reset streak
            streak = 0;
        end
    end

    % Compute the frames when the coin counter should be incremented
    coinCollectionTimes = coinCollectionTimes ./ 174.44;
    coinCollectionTimes = floor(coinCollectionTimes * 60);

    % Create the video reader and writer objects to read and write from
    % file
    vr = VideoReader(videoFileName);
    vw = VideoWriter(outputVideoName, 'Motion JPEG AVI');
    vw.FrameRate = 60;
    open(vw);

    % Read the video frame by frame
    numCoins = 0;
    for frameNum = 1:vr.NumberOfFrames-1
        frame = read(vr, frameNum);
        % Add the number of coin information to the video
        if any(coinCollectionTimes(:) == frameNum)
            numCoins = numCoins + 1;
        end
        text = sprintf('#Coins = %d', numCoins);
        frame = insertText(frame, [100 100], text, 'FontSize', 32, 'TextColor', 'black');
        writeVideo(vw, frame);
    end

    % Close the video writer
    close(vw);
end