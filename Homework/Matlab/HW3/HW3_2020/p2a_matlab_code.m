[x, mapx] = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallEnv.png');
[y, mapy] = imread('C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\smallMarioFace.png');

I1 = rgb2gray(mapx);
I2 = rgb2gray(mapy);

points1 = detectHarrisFeatures(I1);
points2 = detectHarrisFeatures(I2);

[features1,valid_points1] = extractFeatures(I1,points1);
[features2,valid_points2] = extractFeatures(I2,points2);

indexPairs = matchFeatures(features1,features2);

matchedPoints1 = valid_points1(indexPairs(:,1),:);
matchedPoints2 = valid_points2(indexPairs(:,2),:);

figure; showMatchedFeatures(I1,I2,matchedPoints1,matchedPoints2);