% Read input image
src = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2017\\input\\Part_1\\pendulum.jpg');

% Threshold image
src = rgb2gray(src);
src(src<120) = 0;
src(src>=120) = 255;

% Apply close operation to isolate disk
se = strel('disk', 12);
disk = imclose(src, se);

% Manipulate disk and src to create handle
disk = imcomplement(disk);
src = imcomplement(src);
handle = src - disk;

% Remove noise from subtraction
se = strel('line', 5, 1);
handle = imerode(handle, se);
disk = imcomplement(disk);
handle = imcomplement(handle);

% Display results
figure; imshow(disk);
figure; imshow(handle);

% Write results
imwrite(disk, 'disk_matlab.jpg');
imwrite(handle, 'handle_matlab.jpg');