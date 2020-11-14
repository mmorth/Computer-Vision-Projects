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

% Convert destinations to color


% Match the template on the grid
% tMatcher = vision.TemplateMatcher('Metric', 'Sum of squared differences');
% location = tMatcher(src1, bpd)

% Find the highest value matches and draw a bounding box around them
imshow(src1);
hold on;
rectangle('Position', [location(1)-29, location(2)-29, 60, 60], 'EdgeColor', 'r', 'LineWidth', 3);

% Display results
% figure, imshow(src1);
% figure, imshow(src2);
% figure, imshow(src3);