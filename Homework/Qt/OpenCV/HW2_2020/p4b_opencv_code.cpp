#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

struct piece {
    string name;
    Rect roi;
    Mat temp;
    Mat replacementTemp;
    double value = 0;
};

piece board1[8][8];
piece board2[8][8];
piece board3[8][8];

void processPieceMatch(Mat src, Mat dst, Mat temp, Mat replacementTemp, double thresh, bool isBlack, int board);

int main()
{
    char keyPress;
    cout << "p4a_opencv\n";
    // Read image
    Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_4\\p4_board_1_grain.jpg", IMREAD_GRAYSCALE);
    Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_4\\p4_board_2_grain.jpg", IMREAD_GRAYSCALE);
    Mat src3 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_4\\p4_board_3_grain.jpg", IMREAD_GRAYSCALE);

    // Load the knight chess piece templates
    Mat bpd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnDark.jpg", IMREAD_GRAYSCALE);
    Mat bpl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnLight.jpg", IMREAD_GRAYSCALE);
    Mat wpd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnDark.jpg", IMREAD_GRAYSCALE);
    Mat wpl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnLight.jpg", IMREAD_GRAYSCALE);

    Mat bqd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackQueenDark.jpg", IMREAD_GRAYSCALE);
    Mat bql = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackQueenLight.jpg", IMREAD_GRAYSCALE);
    Mat wqd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteQueenDark.jpg", IMREAD_GRAYSCALE);
    Mat wql = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteQueenLight.jpg", IMREAD_GRAYSCALE);

    Mat dst1 = src1.clone();
    Mat dst2 = src2.clone();
    Mat dst3 = src3.clone();

    // Apply median blur to reduce the noise in the images
    int b = 5;
    medianBlur(src1, src1, b);
    medianBlur(src2, src2, b);
    medianBlur(src3, src3, b);
    medianBlur(bpd, bpd, b);
    medianBlur(bpl, bpl, b);
    medianBlur(wpd, wpd, b);
    medianBlur(wpl, wpl, b);

    bitwise_not(src1, src1);
    bitwise_not(src2, src2);
    bitwise_not(src3, src3);
    bitwise_not(bpd, bpd);
    bitwise_not(bpl, bpl);
    bitwise_not(wpd, wpd);
    bitwise_not(wpl, wpl);

    // Detect pawn positions and flip colors
    processPieceMatch(src1, dst1, wpl, wql, 0.95, false, 1);
    processPieceMatch(src1, dst1, wpd, wqd, 0.95, false, 1);
    processPieceMatch(src1, dst1, bpd, bqd, 0.95, true, 1);
    processPieceMatch(src1, dst1, bpl, bql, 0.95, true, 1);

//    processPieceMatch(src2, dst2, wpd, wqd, 0.98, false, 2);
//    processPieceMatch(src2, dst2, wpl, wql, 0.98, false, 2);
//    processPieceMatch(src2, dst2, bpd, bqd, 0.99, true, 2);
//    processPieceMatch(src2, dst2, bpl, bql, 0.99, true, 2);

//    processPieceMatch(src3, dst3, wpd, wqd, 0.98, false, 3);
//    processPieceMatch(src3, dst3, wpl, wql, 0.99, false, 3);
//    processPieceMatch(src3, dst3, bpd, bqd, 0.99, true, 3);
//    processPieceMatch(src3, dst3, bpl, bql, 0.99, true, 3);

    // Replace top and bottom pawn pieces
    for (int col = 0; col < 8; col++) {
        if (board1[0][col].name == "White Pawn") {
            piece p = board1[0][col];
            p.replacementTemp.copyTo(dst1(p.roi));
        } else if (board1[7][col].name == "Black Pawn") {
            piece p = board1[7][col];
            p.replacementTemp.copyTo(dst1(p.roi));
        }
    }

    // Display results
    imshow("Board 1 Results", dst1);
//    imshow("Board 2 Results", dst2);
//    imshow("Board 3 Results", dst3);

    while(1)
    {
        keyPress = waitKey();
        // Press q key to close window
        if (keyPress == 'q')
        {
            destroyAllWindows();
            break;
        }
    }
    return 0;
}

// Source: https://stackoverflow.com/questions/32041063/multiple-template-matching-only-detects-one-match/32095085#32095085
// This code is based on the solution at this link
void processPieceMatch(Mat src, Mat dst, Mat temp, Mat replacementTemp, double thresh, bool isBlack, int board) {
    // Match the A template on the grid
    Mat1f result;
    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
    threshold(result, result, thresh, 1., THRESH_BINARY);

    // Convert result to CV_8U to support finding contours
    Mat resb;
    result.convertTo(resb, CV_8U, 255);

    // Find the contours of the grayscale match result
    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Process each matching A
    for (uint i=0; i<contours.size(); ++i)
    {
        // Mask out all other matching A's except the one that corresponds to the current contour
        Mat mask(result.rows, result.cols, uchar(0));
        drawContours(mask, contours, i, Scalar(255), FILLED);

        // Find the maximum matching location
        Point max_point;
        double max_val;
        minMaxLoc(result, NULL, &max_val, NULL, &max_point, mask);

        // Replace the pixels at this pawn with the pixels for the flipped color
        if (board == 1 && max_val > board1[max_point.y/60][max_point.x/60].value) {
            piece p;
            p.name = isBlack ? "Black Pawn" : "White Pawn";
            if (p.name == "Black Pawn") {
                printf("board1[%d][%d] = %s\n", max_point.x, max_point.y, p.name.c_str());
            }
            Rect roi(max_point.x, max_point.y, 59, 59);
            p.roi = roi;
            p.temp = temp;
            p.replacementTemp = replacementTemp;
            p.value = max_val;
            board1[max_point.y/60][max_point.x/60] = p;
        } else if (board == 2 && max_val > board2[max_point.y/60][max_point.x/60].value) {
            if (isBlack) {
                Rect roi(max_point.x, max_point.y, 60, 60);
                replacementTemp.copyTo(dst(roi));
            } else if (!isBlack) {
                Rect roi(max_point.x, max_point.y, 60, 60);
                replacementTemp.copyTo(dst(roi));
            }
        } else if (board == 3 && max_val > board3[max_point.y/60][max_point.x/60].value) {
            if (isBlack) {
                Rect roi(max_point.x, max_point.y, 59, 59);
                replacementTemp.copyTo(dst(roi));
            } else if (!isBlack) {
                Rect roi(max_point.x, max_point.y, 59, 59);
                replacementTemp.copyTo(dst(roi));
            }
        }
//         && max_point.y >= 420
//         and max_point.y < 60
//        Rect roi(max_point.x, max_point.y, 60, 60);
//        replacementTemp.copyTo(dst(roi));
    }
}

// Store the board location with a struct containing: Mat of the piece, max_point, and max_val
