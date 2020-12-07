% GENERATE DIAL TONES FOR INDIVIDUAL DIGITS, AREA CODES, and PHONE NUMBERS

fs = 44100;  % sampling frequency

% dial the digit 5 for two seconds
dialTone5 = dial_digit('5', 2, fs);  
sound(dialTone5, fs);
audiowrite('touch-tone-5.wav',  dialTone5,  fs);
figure;  plot(1:1000, dialTone5(1:1000));
hold on; plot(1:1000, dialTone5(1:1000), 'r*');
xlabel('Sample number (only the first 1000)');
ylabel('Amplitude');
title('The dial tone wave for the digit 5');
pause(3)

% dial the digit 1 for one second 
dialTone1 = dial_digit('1', 1, fs);  
sound(dialTone1, fs);
audiowrite('touch-tone-1.wav',  dialTone1, fs);
figure;  plot(1:1000, dialTone1(1:1000));
hold on; plot(1:1000, dialTone1(1:1000), 'r*');
xlabel('Sample number (only the first 1000)');
ylabel('Amplitude');
title('The dial tone wave for the digit 1');
pause(3)

% plot the two waves on the same plot
figure;  plot(1:1000, dialTone1(1:1000), 'b');
hold on;  plot(1:1000, dialTone5(1:1000), 'r');
legend('1', '5');
xlabel('Sample number (only the first 1000)');
ylabel('Amplitude');
title('The dial tone waves for the digits 1 and 5');

% dial area code 515
dialAreaCode = dial_number('515', 0.5, 0.2, fs);  
sound(dialAreaCode, fs);
audiowrite('touch-tone-515.wav', dialAreaCode, fs);
pause(5)

% dial 204-009-9212
dialNumber = dial_number('2040099212', 0.4, 0.1, fs);  
sound(dialNumber, fs);
audiowrite('touch-tone-204-009-9212.wav', dialNumber, fs);
pause(10)

% dial 312-555-0690 (with random duration for digits and paueses)
dialNumberRand = dial_numberRandomPause('3125550690', fs);
sound(dialNumberRand, fs);
audiowrite('touch-tone-312-555-0690.wav', dialNumberRand, fs);
pause(2)
