% Determine each audio file's dialed digits
detectAreaCode('area-code-1.wav');
detectAreaCode('area-code-2.wav');
detectAreaCode('area-code-3.wav');
detectAreaCode('area-code-4.wav');
detectAreaCode('area-code-5.wav');
detectAreaCode('area-code-6.wav');
detectAreaCode('area-code-7.wav');
detectAreaCode('area-code-8.wav');
detectAreaCode('area-code-9.wav');
detectAreaCode('area-code-10.wav');


% Function that detects an area code of an audio file using a spectrogram
function detectAreaCode(fileName)
    % Read in the game audio file
    [Y,fs]=audioread(fileName);

    % Obtain the necessary spectrogram variables for processing
    %     figure; spectrogram(Y(:,1), 1024, 256, 1024, fs, 'yaxis'); 
    %     title(strcat(strcat('Spectrogram for =', fileName)));
    [s,f,t,p] = spectrogram(Y, 1024, 256, 1024, fs, 'yaxis');

    % Filter the spectral response to isolate the possible digit frequencies
    minFreq = 640;
    maxFreq = 1536;
    f1 = (f >= minFreq & f <= maxFreq);
    t1 = t > 0.0;
    p = p(f1,t1);
    p(10*log10(abs(p)) < -27) = 0;

    % Compute which digits are recognized at certain locations
    result = "";
    searchingFlag = true;
    waitone = false;
    % Search through all time instances
    for i = 1:size(p(1,:), 2)
        % Determine whether all values are zero in the ith time column
        allZeros = 1 && all(p(:,i) == 0);
        if allZeros
            % Reset searching flag to true when all values are 0s (the next
            % non-zero column will correspond to the next recognized digit)
            searchingFlag = true;
        elseif searchingFlag && ~allZeros
            % Detect the next digit on a non-zero column
            if waitone
                k = find(p(:,i));
                result = result + detectDigit(k, minFreq, maxFreq);
                searchingFlag = false;
                waitone = false;
            else
                waitone = true;
            end
        end
    end

    % Print the detected area code
    text = sprintf("%s's area code = %s", fileName, result);
    disp(text);
end

% Function that detects the dial digit using a spectrogram
function result = detectDigit(k, minFreq, maxFreq)
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
        if upperFreq == 1
           result = "*";
        else
            result = "#";
        end
    else
        result = num2str(digitLocations(lowerFreq, upperFreq));
    end
end