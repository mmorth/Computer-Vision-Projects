% Try finding the max k points in spectrogram
% Try the chernogram method again
% Short look for other solutions
% Look for intensity thresholds to determine when notes change
% Look for max k for chord detection
% Make sure the window is small enough to match the min length of the note

% Find the fundamental frequency
[Y,fs]=audioread('piano-note3.wav');
x = (Y(:,1) + Y(:,2)) / 2;

[s,f,t,p] = spectrogram(x, 1024, 256, 1024, fs, 'yaxis');
% spectrogram(Y, 1024, 256, 1024, fs, 'yaxis');
plot(abs(s));

p(10*log10(abs(p)) < -480) = 0;

maximum = max(max(p));
[x, y] = find(p == maximum);

% determineNote('c4-piano.wav');
% determineNote('piano-note2.wav');
% determineNote('piano-note3.wav');
% determineNote('piano-note4.wav');
% determineNote('piano-note5.wav');
% determineNote('piano-note6.wav');
% determineNote('piano-note7.wav');

% Source: https://www.phon.ucl.ac.uk/courses/spsci/matlab/lect10.html
% The code for this function was adapted from the code found in the above
% link to solve this problem
function determineNote(fileName)
    % Read in the game audio file and convert to mono
    [Y,fs]=audioread(fileName);
    x = (Y(:,1) + Y(:,2)) / 2;

    % Define the time interval between 
    ms1=fs/1000;
    ms20=fs/50;

    % Compute the windowed fourier transformed signal
    Y=fft(x.*hamming(length(x)));

    % Compute the cepstrum of the resulting frequency-domain wave
    C=fft(log(abs(Y)+eps));

    % Find the peak that corresponds to the fundamental frequency
    [c,fx]=max(abs(C(ms1:ms20)));
    fprintf('Fx=%gHz\n',fs/(ms1+fx-1));
end

% [Y,fs]=audioread('c4-piano.wav');
% x = (Y(:,1) + Y(:,2)) / 2;
% f = abs(fft(x));
% m = maxk(f, 10);

% p = pitch(Y, fs);
% 
% dt = 1/fs;
% % x = (Y(:,1) + Y(:,2)) / 2;
% 
% c = cceps(x);
% 
% t = 0:dt:length(x)*dt-dt;
% 
% trng = t(t>=2e-3 & t<=10e-3);
% crng = c(t>=2e-3 & t<=10e-3);
% 
% [~,I] = max(crng);
% 
% fprintf('Complex cepstrum F0 estimate is %3.2f Hz.\n',1/trng(I))
% 
% plot(trng*1e3,crng)
% xlabel('ms')
% 
% hold on
% plot(trng(I)*1e3,crng(I),'o')
% hold off
% 
% [b0,a0] = butter(2,325/(fs/2));
% xin = abs(x);
% xin = filter(b0,a0,xin);
% xin = xin-mean(xin);
% x2 = zeros(length(xin),1);
% x2(1:length(x)-1) = xin(2:length(x));
% zc = length(find((xin>0 & x2<0) | (xin<0 & x2>0)));
% F0 = 0.5*fs*zc/length(x);
% fprintf('Zero-crossing F0 estimate is %3.2f Hz.\n',F0)

% cx = cceps(Y.*hamming(length(Y)));
% stem(abs(cx));
% axis tight;

% [pxx, f] = pwelch(Y);
% plot(f,10*log10(pxx));
% maximum = max(pxx);
% [x, y] = find(pxx == maximum);

% f = [16.35 17.32 18.35 19.45 20.6 21.83 23.12 24.5 25.96 27.5 29.14 30.87 32.7 34.65 36.71 38.89 41.2 43.65 46.25 49 51.91 55 58.27 61.74 65.41 69.3 73.42 77.78 82.41 87.31 92.5 98 103.83 110 116.54 123.47 130.81 138.59 146.83 155.56 164.81 174.61 185 196 207.65 220 233.08 246.94 261.63 277.18 293.66 311.13 329.63 349.23 369.99 392 415.3 440 466.16 493.88 523.25 554.37 587.33 622.25 659.25 698.46 739.99 783.99 830.61 880 932.33 987.77 1046.5 1108.73 1174.66 1244.51 1318.51 1396.91 1479.98 1567.98 1661.22 1760 1864.66 1975.53 2093 2217.46 2349.32 2489.02 2637.02 2793.83 2959.96 3135.96 3322.44 3520 3729.31 3951.07 4186.01 4434.92 4698.63 4978.03 5274.04 5587.65 5919.91 6271.93 6644.88 7040 7458.62 7902.13];
% freq_indices = round(f/fs*length(Y)) + 1;   
% dfftdata = goertzel(Y, freq_indices);
% figure; stem(f, abs(dfftdata));
% p = pitch(Y, fs);
% figure; plot(p);

% f = abs(fft(Y));
% [pks,frqs] = findpeaks(abs(f));
% maximum = max(f);
% [x, y] = find(f == maximum);

% Obtain the necessary spectrogram variables for processing
% figure; spectrogram(Y, 2048, 256, 2048, fs, 'yaxis'); 
% axis xy; axis tight; colormap(jet); view(0,90);
% title(strcat(strcat('Spectrogram for =', fileName)));
% p = pitch(Y, fs);
% plot(p);
% [s,f,t,p] = spectrogram(Y, 1024, 256, 1024, fs, 'yaxis');
% spectrogram(Y, 1024, 256, 1024, fs, 'yaxis');

% p(10*log10(abs(p)) < -480) = 0;

% maximum = max(max(p));
% [x, y] = find(p == maximum);

% Use the built-in pitch function from Matlab and map that to the correct
% note

% Use the above max spectrogram finder and keep dividing by 2 until the
% power is no longer greater than a minimum threshold