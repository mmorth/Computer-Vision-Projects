% Read image
src = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Part_1\\p1_board.jpg');

src = rgb2gray(src);

% Threshold and apply close operation
border = src;
border(border<250) = 0;

se = strel('square', 11);
border = imclose(border, se);

border = cat(3, border, border, border);

% Apply threshold to convert the black and white spots on board to black and white
src(src>225) = 255;
src(src<=225) = 0;
src = cat(3, src, src, src);

r = src(:,:,1); % Red channel
g = src(:,:,2); % Green channel
b = src(:,:,3); % Blue channel

% Convert all white pixels to green and all black pixels to red
r(r==255) = 1;
g(g==255) = 255;
b(b==255) = 1;

r(r==0) = 255;
g(g==0) = 1;
b(b==0) = 1;

src = cat(3, r, g, b);

% Restore border and display result
src = src + border;

imshow(src);
imwrite(src,'p1_matlab_result.jpg');