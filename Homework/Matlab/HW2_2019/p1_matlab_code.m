% Read image
[pixels, colorMap] = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_1\\p1_search.png');
src = ind2gray(pixels, colorMap);

% Extract vertical lines from grid
src = imcomplement(src);
se = strel('rectangle', [34, 1]);
vert = imopen(src, se);

% Extract horizontal lines from grid
se = strel('rectangle', [1, 21]);
horiz = imopen(src, se);

% Determine the grid boundary positions
grid = vert+horiz;

searchingRight = false;
foundResult = false;
minRow = 0;
maxRow = 0;
minCol = 0;
maxCol = 0;
for r = 1:size(grid, 1)    % for number of rows of the image
    for c = 1:size(grid, 2)    % for number of columns of the image
        if grid(r, c) > 0 && minRow == 0
            minRow = r;
            minCol = c;
            searchingRight = true;
        elseif grid(r, c) == 0 && searchingRight == true
            maxCol = c;
            maxRow = minRow + (maxCol-minCol);
            foundResult = true;
            break;
        end
    end
    if foundResult == true
        break;
    end
end

% Remove all pixels not contained within grid
src = imcomplement(src);
dst = src;
for r = 1:size(grid, 1)    % for number of rows of the image
    for c = 1:size(grid, 2)    % for number of columns of the image
        if not (r >= minRow && r <= maxRow && c >= minCol && c <= maxCol) 
            dst(r, c) = 255;
        end
    end
end

imshow(dst);
imwrite(dst,'p1_matlab_result.png');