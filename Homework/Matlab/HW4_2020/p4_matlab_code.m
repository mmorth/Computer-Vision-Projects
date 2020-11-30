% Read audio file
[v, Fs] = audioread('areacode1.wav');

% r = spectrogram(v, 512, 256, 512, fs, 'yaxis'); 

% 1) Split the input vector into small overlapping segments
cs=512;
sh=256;
segments = v(bsxfun(@plus,(1:cs),(0:sh:length(v)-cs)'));
% segments = buffer(v,cs,sh,'nodelay')';

% 2) Apply the Hamming window function to each segment
hw = hamming(size(segments,2))';
hw = repmat(hw, size(segments,1), 1);
segments = segments.*hw;

% 3) Compute the FFTs of the resulting vectors
segments = fft(segments,cs,2);

% 4) Discard the redundant frequency bins for the negative frequencies from these vectors (because the input is real


% 5) Compute the logarithms of the magnitudes of the frequency bins
inc = (length(v) ./ Fs) ./ size(segments, 1);
tm = 0:inc:(inc*(size(segments,1)-1));
inc = (Fs ./ 2) ./ size(segments,2);
fm = 0:inc:(inc*(size(segments,2)-1));
fm = fm';
segments = segments';

figure; plot(segments);

figure; surf(tm,fm,log(abs(segments)),'EdgeColor','none');
axis xy; axis tight; colormap(jet); view(0,90);