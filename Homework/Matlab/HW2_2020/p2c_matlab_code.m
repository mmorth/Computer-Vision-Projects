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

% Create checkerboard matrix
checker = checkerboard(8);

% Drawn the pawns on board 1
board = zeros(8,8);
board = matchBlackPawnFeatures(src1, bpd, board, 1);
board = matchBlackPawnFeatures(src1, bpl, board, 1);
board = matchBlackPawnFeatures(src1, wpd, board, 2);
board = matchBlackPawnFeatures(src1, wpl, board, 2);
drawBoard(src1, board, checker, bpd, bpl, wpd, wpl);

% Drawn the pawns on board 2
board = zeros(8,8);
board = matchBlackPawnFeatures(src2, bpd, board, 1);
board = matchBlackPawnFeatures(src2, bpl, board, 1);
board = matchBlackPawnFeatures(src2, wpd, board, 2);
board = matchBlackPawnFeatures(src2, wpl, board, 2);
drawBoard(src2, board, checker, bpd, bpl, wpd, wpl);

% Drawn the pawns on board 3
board = zeros(8,8);
board = matchBlackPawnFeatures(src3, bpd, board, 1);
board = matchBlackPawnFeatures(src3, bpl, board, 1);
board = matchBlackPawnFeatures(src3, wpd, board, 2);
board = matchBlackPawnFeatures(src3, wpl, board, 2);
drawBoard(src3, board, checker, bpd, bpl, wpd, wpl);

% Find black pawn locations using feature extraction
function b = matchBlackPawnFeatures(src, temp, board, color)
    points1 = detectHarrisFeatures(src);
    points2 = detectHarrisFeatures(temp);

    [features1,valid_points1] = extractFeatures(src,points1);
    [features2,valid_points2] = extractFeatures(temp,points2);

    indexPairs = matchFeatures(features1, features2);

    matchedPoints1 = valid_points1(indexPairs(:,1),:);
    
    b = board;
    for i = 1:size(matchedPoints1,1)
       b(floor(matchedPoints1.Location(i,2)/60)+1,floor(matchedPoints1.Location(i,1)/60)+1) = color;
    end
end

% For each pawn location, replace that pawn with a pawn of a different
% color
function drawBoard(src, board, checker, bpd, bpl, wpd, wpl)
    for row = 1:size(board,1)
        for col = 1:size(board,2)
            aCol = (col-1)*60+1;
            aRow = (row-1)*60+1;
            if board(row,col) == 1
                if checker(row,col) == 0
                    src(aRow:aRow+59,aCol:aCol+59) = wpl;
                else
                    src(aRow:aRow+59,aCol:aCol+59) = wpd;
                end
            elseif board(row,col) == 2
                if checker(row,col) == 0
                    src(aRow:aRow+59,aCol:aCol+59) = bpl;
                else
                    src(aRow:aRow+59,aCol:aCol+59) = bpd;
                end
            end
        end
    end
    figure, imshow(src);
end

% Creates a checkerboard matrix to determine what color background is at a
% location
% Source: https://www.mathworks.com/matlabcentral/answers/356307-how-to-create-a-checkerboard-matrix-without-inbuilt-function
function a = checkerboard(n)
    a = zeros(n);
    for i = 1:n
        for j = 1:n
            if (i == j)
                a (i, j) = 0;
            elseif (mod(j, 2) == 0) && (mod(i,2) == 0)
                 a(i,j) = 0;
            elseif (mod(j, 2) == 0) || (mod(i,2) == 0)
                a(i,j) = 1;
            end
        end
    end
end