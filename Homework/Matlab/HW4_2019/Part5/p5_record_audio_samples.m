% Configure the Matlab audio recorder
Fs = 44100;
numBits = 24;
numChannels = 1;

% Record the game audio
recObj = audiorecorder(Fs, numBits, numChannels);
disp('Start Recording...');
recordblocking(recObj,5);
disp('End of Recording');

% Save the resulting game audio to a file
audiowrite('PokemonMusic.wav', getaudiodata(recObj), Fs);