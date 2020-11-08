#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

void processPieceMatch(Mat src, Mat hl, Mat temp);

int main()
{
    char keyPress;
    cout << "p1_opencv\n";
    // Read image
    Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Part_3a\\p3a_board_1.jpg", IMREAD_GRAYSCALE);
    Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Part_3a\\p3a_board_2.jpg", IMREAD_GRAYSCALE);
    Mat src3 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Part_3a\\p3a_board_3.jpg", IMREAD_GRAYSCALE);

    // Load the knight chess piece templates
    Mat bkd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\blackKnightDark.jpg", IMREAD_GRAYSCALE);
    Mat bkl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\blackKnightLight.jpg", IMREAD_GRAYSCALE);
    Mat wkd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\whiteKnightDark.jpg", IMREAD_GRAYSCALE);
    Mat wkl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\whiteKnightLight.jpg", IMREAD_GRAYSCALE);
    Mat bbd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\blackBishopDark.jpg", IMREAD_GRAYSCALE);
    Mat bbl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\blackBishopLight.jpg", IMREAD_GRAYSCALE);
    Mat wbd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\whiteBishopDark.jpg", IMREAD_GRAYSCALE);
    Mat wbl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\whiteBishopLight.jpg", IMREAD_GRAYSCALE);
    Mat brd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\blackRookDark.jpg", IMREAD_GRAYSCALE);
    Mat brl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\blackRookLight.jpg", IMREAD_GRAYSCALE);
    Mat wrd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\whiteRookDark.jpg", IMREAD_GRAYSCALE);
    Mat wrl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\whiteRookLight.jpg", IMREAD_GRAYSCALE);
    Mat bqd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\blackQueenDark.jpg", IMREAD_GRAYSCALE);
    Mat bql = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\blackQueenLight.jpg", IMREAD_GRAYSCALE);
    Mat wqd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\whiteQueenDark.jpg", IMREAD_GRAYSCALE);
    Mat wql = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\whiteQueenLight.jpg", IMREAD_GRAYSCALE);
    Mat bgd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\blackKingDark.jpg", IMREAD_GRAYSCALE);
    Mat wgd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\whiteKingDark.jpg", IMREAD_GRAYSCALE);
    Mat wgl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Chess_Piece_Templates\\whiteKingLight.jpg", IMREAD_GRAYSCALE);

    Mat pieceTemplates[] = {bkd,bkl,wkd,wkl,bbd,bbl,wbd,wbl,brd,brl,wrd,wrl,bqd,bql,wqd,wql,bgd,wgd,wgl};
    int numPieceTemplates = 19;

    Mat dst1;
    Mat dst2;
    Mat dst3;
    cvtColor(src1, dst1, COLOR_GRAY2BGR);
    cvtColor(src2, dst2, COLOR_GRAY2BGR);
    cvtColor(src3, dst3, COLOR_GRAY2BGR);

    for (int i = 0; i < numPieceTemplates; i++) {
        processPieceMatch(src1, dst1, pieceTemplates[i]);
        processPieceMatch(src2, dst2, pieceTemplates[i]);
        processPieceMatch(src3, dst3, pieceTemplates[i]);
    }

    // Display results
    imshow("Board 1 Results", dst1);
    imshow("Board 2 Results", dst2);
    imshow("Board 3 Results", dst3);

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
void processPieceMatch(Mat src, Mat hl, Mat temp) {
    // Match the A template on the grid
    Mat1f result;
    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
    double thresh = 0.95;
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

        // Draw the font in different colors
        rectangle(hl, Rect(max_point.x, max_point.y, temp.cols, temp.rows), Scalar(0, 0, 255), 5);
    }
}
