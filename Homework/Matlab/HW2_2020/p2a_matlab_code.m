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
matchBlackPawnFeaturesAndDraw(src1, bpl);
matchWhitePawnFeaturesAndDraw(src1, wpd);
matchWhitePawnFeaturesAndDraw(src1, wpl);

% Drawn the pawns on board 2
figure, imshow(src2);
matchBlackPawnFeaturesAndDraw(src2, bpd);
matchBlackPawnFeaturesAndDraw(src2, bpl);
matchWhitePawnFeaturesAndDraw(src2, wpd);
matchWhitePawnFeaturesAndDraw(src2, wpl);

% Drawn the pawns on board 3
figure, imshow(src3);
matchBlackPawnFeaturesAndDraw(src3, bpd);
matchBlackPawnFeaturesAndDraw(src3, bpl);
matchWhitePawnFeaturesAndDraw(src3, wpd);
matchWhitePawnFeaturesAndDraw(src3, wpl);

function matchBlackPawnFeaturesAndDraw(src, temp)
    points1 = detectHarrisFeatures(src);
    points2 = detectHarrisFeatures(temp);

    [features1,valid_points1] = extractFeatures(src,points1);
    [features2,valid_points2] = extractFeatures(temp,points2);

    indexPairs = matchFeatures(features1, features2);

    matchedPoints1 = valid_points1(indexPairs(:,1),:);
    
    colMatch = 0;
    lastX = 0;
    i = 1;
    while i <= size(matchedPoints1,1)
        if lastX == 0 || colMatch == 0
            rectangle('Position', [60*floor((matchedPoints1.Location(i,1)-21)/60)+1, 60*floor((matchedPoints1.Location(i,2)-25)/60), 58, 58], 'EdgeColor', 'r', 'LineWidth', 3);
            lastX = matchedPoints1.Location(i,1);
            colMatch = colMatch + 1;
            i = i + 1;
        elseif abs(matchedPoints1.Location(i,1) - lastX) < 1
            rectangle('Position', [60*floor((matchedPoints1.Location(i,1)-21)/60)+1, 60*floor((matchedPoints1.Location(i,2)-25)/60), 58, 58], 'EdgeColor', 'r', 'LineWidth', 3);
            lastX = matchedPoints1.Location(i,1);
            colMatch = colMatch + 1;
            i = i + 1;
        else
            i = i + 2*colMatch - colMatch;
            colMatch = 0;
        end
    end
end

function matchWhitePawnFeaturesAndDraw(src, temp)
    points1 = detectHarrisFeatures(src);
    points2 = detectHarrisFeatures(temp);

    [features1,valid_points1] = extractFeatures(src,points1);
    [features2,valid_points2] = extractFeatures(temp,points2);

    indexPairs = matchFeatures(features1, features2);

    matchedPoints1 = valid_points1(indexPairs(:,1),:);
    
    colMatch = 0;
    lastX = 0;
    i = 1;
    while i <= size(matchedPoints1,1)
        if lastX == 0 || colMatch == 0
            rectangle('Position', [60*floor((matchedPoints1.Location(i,1)-21)/60)+1, 60*floor((matchedPoints1.Location(i,2)-25)/60), 58, 58], 'EdgeColor', 'r', 'LineWidth', 3);
            lastX = matchedPoints1.Location(i,1);
            colMatch = colMatch + 1;
            i = i + 1;
        elseif abs(matchedPoints1.Location(i,1) - lastX) < 1
            rectangle('Position', [60*floor((matchedPoints1.Location(i,1)-21)/60)+1, 60*floor((matchedPoints1.Location(i,2)-25)/60), 58, 58], 'EdgeColor', 'r', 'LineWidth', 3);
            lastX = matchedPoints1.Location(i,1);
            colMatch = colMatch + 1;
            i = i + 1;
        else
            i = i + 4*colMatch - colMatch;
            colMatch = 0;
        end
    end
end