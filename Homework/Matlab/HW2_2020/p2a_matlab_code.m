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
figure, imshow(src1);
matchBlackPawnFeaturesAndDraw(src1, bpd);
matchWhitePawnFeaturesAndDraw(src1, wpd);
matchWhitePawnFeaturesAndDraw(src1, wpl);

% Drawn the pawns on board 2
figure, imshow(src2);
matchBlackPawnFeaturesAndDraw(src2, bpd);
matchWhitePawnFeaturesAndDraw(src2, wpd);
matchWhitePawnFeaturesAndDraw(src2, wpl);

% Drawn the pawns on board 3
figure, imshow(src3);
matchBlackPawnFeaturesAndDraw(src3, bpd);
matchWhitePawnFeaturesAndDraw(src3, wpd);
matchWhitePawnFeaturesAndDraw(src3, wpl);

function matchBlackPawnFeaturesAndDraw(src, temp)
    points1 = detectHarrisFeatures(src);
    points2 = detectHarrisFeatures(temp);

    [features1,valid_points1] = extractFeatures(src,points1);
    [features2,valid_points2] = extractFeatures(temp,points2);

    indexPairs = matchFeatures(features1, features2);

    matchedPoints1 = valid_points1(indexPairs(:,1),:);
    matchedPoints2 = valid_points2(indexPairs(:,2),:);

    hold on;
    for i = 1:2:size(matchedPoints1,1)
        rectangle('Position', [matchedPoints1.Location(i,1)-22, matchedPoints1.Location(i,2)-32, 59, 59], 'EdgeColor', 'r', 'LineWidth', 3);
    end
    figure; showMatchedFeatures(src,temp,matchedPoints1,matchedPoints2);
end

function matchWhitePawnFeaturesAndDraw(src, temp)
    points1 = detectHarrisFeatures(src);
    points2 = detectHarrisFeatures(temp);

    [features1,valid_points1] = extractFeatures(src,points1);
    [features2,valid_points2] = extractFeatures(temp,points2);

    indexPairs = matchFeatures(features1, features2);

    matchedPoints1 = valid_points1(indexPairs(:,1),:);
    matchedPoints2 = valid_points2(indexPairs(:,2),:);

    for i = 1:4:size(matchedPoints1,1)
        rectangle('Position', [matchedPoints1.Location(i,1)-21, matchedPoints1.Location(i,2)-25, 59, 59], 'EdgeColor', 'r', 'LineWidth', 3);
    end
    figure; showMatchedFeatures(src,temp,matchedPoints1,matchedPoints2);
end