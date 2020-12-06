% Determine each audio file's dialed digits
detectAreaCode('phone-number-1.wav');
detectAreaCode('phone-number-2.wav');
detectAreaCode('phone-number-3.wav');
detectAreaCode('phone-number-4.wav');
detectAreaCode('phone-number-5.wav');

% Function that detects an area code of an audio file using a spectrogram
function detectAreaCode(fileName)
    % Read in the game audio file
    [Y,fs]=audioread(fileName);

    % Obtain the necessary spectrogram variables for processing
    [s,f,t,p] = spectrogram(Y, 1024, 256, 1024, fs, 'yaxis');

    % Filter the spectral response to isolate the possible digit frequencies
    minFreq = 640;
    maxFreq = 1536;
    f1 = (f >= minFreq & f <= maxFreq);
    t1 = t > 0.0;
    p = p(f1,t1);
    p(10*log10(abs(p)) < -78) = 0;

    % Compute which digits are recognized at certain locations
    result = "";
    searchingFlag = true;
    matchSpan = 0;
    numDigits = 0;
    % Search through all time instances
    for i = 1:size(p(1,:), 2)
        % Determine whether all values are zero in the ith time column
        allZeros = 1 && all(p(:,i) == 0);
        if allZeros
            % Reset searching flag to true when all values are 0s (the next
            % non-zero column will correspond to the next recognized digit)
            searchingFlag = true;
            matchSpan = 0;
        elseif searchingFlag && ~allZeros
            % Detect the next digit on a non-zero column
            if matchSpan >= 5
                k = find(p(:,i));
                result = result + detectDigit(k, minFreq, maxFreq);
                numDigits = numDigits + 1;
                searchingFlag = false;
                matchSpan = 0;

                if numDigits == 3 || numDigits == 6
                    result = result + "-";
                end
            else
                matchSpan = matchSpan + 1;
            end
        end
    end

    % Print the detected area code
    text = sprintf("%s's area code = %s", fileName, result);
    disp(text);
end

% Function that detects the dial digit using a spectrogram
function result = detectDigit(k, minFreq, maxFreq)
    % Determine the upper and lower k values
    lowerK = k(1);
    upperK = k(end);
%     upperK = 0;
%     for i = 1:length(k)
%         if k(i)-lowerK >= 5
%             upperK = k(i);
%             break;
%         end
%     end

    % Determine the upper and lower number digit value for classification
    lowerFreq = minFreq + 46.875*(lowerK);
    upperFreq = minFreq + 46.875*(upperK-1);
    digitLocations = [1 2 3; 4 5 6; 7 8 9; 0 0 0];

    % Find lower frequency bin
    if lowerFreq >= 665 && lowerFreq <= 737
        lowerFreq = 1;
    elseif lowerFreq >= 738 && lowerFreq <= 802
        lowerFreq = 2;
    elseif lowerFreq >= 820 && lowerFreq <= 884
        lowerFreq = 3;
    else
        lowerFreq = 4;
    end

    % Find upper frequency bin
    if upperFreq >= 1177 && upperFreq <= 1265
        upperFreq = 1;
    elseif upperFreq >= 1280 && upperFreq <= 1368
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