% Read image
src = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_1\\p1_board.jpg');
dst = src;

% Pad the side of the image with 255 pixels for grid detection
src(1,:) = 100;
src(end,:) = 100;
src(:,1) = 100;
src(:,end) = 100;

% Detect the corner points and use those for grid box labels
corners = corner(src);

% Round each corner to the nearest multiple of 60 (grid square size)
for i = 1:size(corners,1)
    if mod(corners(i,1),60)>5
        corners(i,1) = 60*ceil(corners(i,1)/60);
    elseif mod(corners(i,1),60)>0
        corners(i,1) = 60*floor(corners(i,1)/60);
    end
end

for i = 1:size(corners,1)
    if mod(corners(i,2),60)>5
        corners(i,2) = 60*ceil(corners(i,2)/60);
    elseif mod(corners(i,2),60)>0
        corners(i,2) = 60*floor(corners(i,2)/60);
    end
end

% Sort the corner points by column ascending
corners = sortrows(corners, 2);

% Display the correct grid labels
imshow(src);
col = 'A';
row = 8;
elementRange = [60, 120, 180, 240, 300, 360, 420, 480];
for i = 1:size(elementRange,2)
    for j = 1:size(corners, 1)
        if corners(j,1) >= elementRange(i)-60 && corners(j,1) < elementRange(i) && corners(j,2) < 480
            gridLabel = sprintf('%c%d', col, row);
            text(corners(j,1)+10, corners(j,2)+35, gridLabel, 'Color', 'r', 'FontSize', 18);

            row = row - 1;
            if row == 0
                row = 8;
                col = col+1;
            end
        end
    end
end