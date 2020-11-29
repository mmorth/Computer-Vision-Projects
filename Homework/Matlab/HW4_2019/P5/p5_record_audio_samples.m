recObj = audiorecorder;
disp('Start Speaking.');
recordblocking(recObj,5);
disp('End of Recording');
play(recObj);