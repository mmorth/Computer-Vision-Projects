% Read images
src1 = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_2\\p2_board_1.jpg');
src2 = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_2\\p2_board_2.jpg');
src3 = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_2\\p2_board_3.jpg');
dst1 = src1;
dst2 = src2;
dst3 = src3;

bpd = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnDark.jpg');
bpl = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnLight.jpg');
wpd = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnDark.jpg');
wpl = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnLight.jpg');

% Drawn the pawns on board 1
board = zeros(8,8);
figure, imshow(src1);
board = matchBlackPawnFeatures(src1, bpd, board);
board = matchBlackPawnFeatures(src1, bpl, board);
board = matchBlackPawnFeatures(src1, wpd, board);
board = matchBlackPawnFeatures(src1, wpl, board);
drawBoard(board);


% Drawn the pawns on board 2
board = zeros(8,8);
figure, imshow(src2);
board = matchBlackPawnFeatures(src2, bpd, board);
board = matchBlackPawnFeatures(src2, bpl, board);
board = matchBlackPawnFeatures(src2, wpd, board);
board = matchBlackPawnFeatures(src2, wpl, board);
drawBoard(board);

% Drawn the pawns on board 3
board = zeros(8,8);
figure, imshow(src3);
board = matchBlackPawnFeatures(src3, bpd, board);
board = matchBlackPawnFeatures(src3, bpl, board);
board = matchBlackPawnFeatures(src3, wpd, board);
board = matchBlackPawnFeatures(src3, wpl, board);
drawBoard(board);

% Find the locations of black pawns given template
function b = matchBlackPawnFeatures(src, temp, board)
    points1 = detectHarrisFeatures(src);
    points2 = detectHarrisFeatures(temp);

    [features1,valid_points1] = extractFeatures(src,points1);
    [features2,valid_points2] = extractFeatures(temp,points2);

    indexPairs = matchFeatures(features1, features2);

    matchedPoints1 = valid_points1(indexPairs(:,1),:);
    
    b = board;
    for i = 1:size(matchedPoints1,1)
       b(floor(matchedPoints1.Location(i,2)/60)+1,floor(matchedPoints1.Location(i,1)/60)+1) = 1;
    end
end

% Draws the number text overlay for the pawns
function drawBoard(board)
    num = 1;
    for row = 1:size(board,1)
        for col = 1:size(board,2)
            if board(row,col) == 1
                gridLabel = sprintf('%d', num);
                text((col-1)*60+15, (row-1)*60+25, gridLabel, 'Color', 'r', 'FontSize', 18, 'FontWeight', 'bold');
                num = num + 1;
            end
        end
    end
end