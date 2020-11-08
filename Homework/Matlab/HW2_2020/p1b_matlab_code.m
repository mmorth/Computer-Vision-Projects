% Read image
src = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_1\\p1_board.jpg');

% Apply threshold to convert the black and white spots on board to black and white
src(src>225) = 255;
src(src<=225) = 0;

% Convert all white pixels to green and all black pixels to red
src(src==255) = 160;
src(src==0) = 240;

imshow(src);