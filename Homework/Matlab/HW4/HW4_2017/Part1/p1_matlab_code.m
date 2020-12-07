detectDigit('single-digit-1.wav');
detectDigit('single-digit-2.wav');
detectDigit('single-digit-3.wav');
detectDigit('single-digit-4.wav');
detectDigit('single-digit-5.wav');
detectDigit('single-digit-6.wav');
detectDigit('single-digit-7.wav');
detectDigit('single-digit-8.wav');
detectDigit('single-digit-9.wav');
detectDigit('single-digit-10.wav');
detectDigit('single-digit-11.wav');
detectDigit('single-digit-12.wav');

% Function that detects the dial digit using a spectrogram
function detectDigit(audioFileName)
    % Read in the game audio file
    [Y,fs]=audioread(audioFileName);

    % Obtain the necessary spectrogram variables for processing
    [s,f,t,p] = spectrogram(Y, 1024, 256, 1024, fs, 'yaxis'); 

    % Filter the spectral response to isolate the possible digit frequencies
    minFreq = 640;
    maxFreq = 1536;
    f1 = (f >= minFreq & f <= maxFreq);
    t1 = t > 0.0;
    p = p(f1,t1);
    p(10*log10(abs(p)) < -27) = 0;

    % Find the indices of non-zero filtered power that correspond to certain
    % frequencies
    k = find(p(:,1));

    % Determine the upper and lower number digit value for classification
    lowerFreq = minFreq + 32*(k(1)-1);
    upperFreq = minFreq + 32*(k(2)-1);
    digitLocations = [1 2 3; 4 5 6; 7 8 9; 0 0 0];

    % Find lower frequency bin
    if lowerFreq >= 672 && lowerFreq <= 704
        lowerFreq = 1;
    elseif lowerFreq >= 768 && lowerFreq <= 800
        lowerFreq = 2;
    elseif lowerFreq >= 832 && lowerFreq <= 864
        lowerFreq = 3;
    else
        lowerFreq = 4;
    end

    % Find upper frequency bin
    if upperFreq >= 1184 && upperFreq <= 1216
        upperFreq = 1;
    elseif upperFreq >= 1312 && upperFreq <= 1344
        upperFreq = 2;
    else
        upperFreq = 3;
    end
    
    % Print results
    if lowerFreq == 4 && upperFreq ~= 2
        result = sprintf("%s detectedDigit = ", audioFileName);
        if upperFreq == 1
           result = result + "*";
        else
            result = result + "#";
        end
    else
        result = sprintf("%s detectedDigit = %d", audioFileName, digitLocations(lowerFreq, upperFreq));
    end
    
    disp(result);
end