% Read image
src = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Part_1\\p1_board.jpg');

src = rgb2gray(src);

% Threshold and apply close operation
border = src;
border(border<250) = 0;

se = strel('square', 11);
border = imclose(border, se);

map = hsv(256);
border = ind2rgb(border, map);

% Apply threshold to convert the black and white spots on board to black and white
src(src>225) = 255;
src = ind2rgb(src, map);

% Convert all white pixels to green and all black pixels to red
src(src==255, 1) = 0;
src(src==255, 2) = 0;
src(src==255, 3) = 255;

src(src==0, 1) = 0;
src(src==0, 2) = 255;
src(src==0, 3) = 0;

% Restore border and display result
src = src + border;

imshow(src);
imwrite(src,'p1_matlab_result.png');