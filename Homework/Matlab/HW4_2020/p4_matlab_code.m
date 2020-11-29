% Read audio file
[v, Fs] = audioread('areacode1.wav');

% r = spectrogram(v, 512, 256, 512, fs, 'yaxis'); 

% 1) Split the input vector into small overlapping segments
cs=724;
sh=362;
segments = v(bsxfun(@plus,(1:cs),(0:sh:length(v)-cs)'));

% 2) Apply the Hamming window function to each segment
% hw = hamming(22050);
% segments = segments*hw;
win = dsp.Window;
for i = 1:size(segments, 1) 
   segments(i,:) = win(segments(i,:));
end

% 3) Compute the FFTs of the resulting vectors
for i = 1:size(segments, 1) 
   segments(i,:) = fft(segments(i,:));
end

% 4) Discard the redundant frequency bins for the negative frequencies from these vectors (because the input is real


% 5) Compute the logarithms of the magnitudes of the frequency bins
for i = 1:size(segments, 1) 
   segments(i,:) = log(norm(segments(i,:)));
end

plot(segments);