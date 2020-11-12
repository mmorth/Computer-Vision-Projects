//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void processPieceMatch(Mat src, Mat dst, Mat temp, Mat replacementTemp, double thresh, bool isBlack);

//int main()
//{
//    char keyPress;
//    cout << "p4a_opencv\n";
//    // Read image
//    Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_4\\p4_board_1_grain.jpg", IMREAD_GRAYSCALE);
//    Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_4\\p4_board_2_grain.jpg", IMREAD_GRAYSCALE);
//    Mat src3 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_4\\p4_board_3_grain.jpg", IMREAD_GRAYSCALE);

//    // Load the knight chess piece templates
//    Mat bpd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnDark.jpg", IMREAD_GRAYSCALE);
//    Mat bpl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnLight.jpg", IMREAD_GRAYSCALE);
//    Mat wpd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnDark.jpg", IMREAD_GRAYSCALE);
//    Mat wpl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnLight.jpg", IMREAD_GRAYSCALE);

//    Mat bqd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackQueenDark.jpg", IMREAD_GRAYSCALE);
//    Mat bql = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackQueenLight.jpg", IMREAD_GRAYSCALE);
//    Mat wqd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteQueenDark.jpg", IMREAD_GRAYSCALE);
//    Mat wql = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteQueenLight.jpg", IMREAD_GRAYSCALE);

//    Mat dst1 = src1.clone();
//    Mat dst2 = src2.clone();
//    Mat dst3 = src3.clone();

//    // Apply median blur to reduce the noise in the images
//    int b = 11;
//    medianBlur(src1, src1, b);
//    medianBlur(src2, src2, b);
//    medianBlur(src3, src3, b);
//    medianBlur(bpd, bpd, b);
//    medianBlur(bpl, bpl, b);
//    medianBlur(wpd, wpd, b);
//    medianBlur(wpl, wpl, b);

//    bitwise_not(src1, src1);
//    bitwise_not(src2, src2);
//    bitwise_not(src3, src3);
//    bitwise_not(bpd, bpd);
//    bitwise_not(bpl, bpl);
//    bitwise_not(wpd, wpd);
//    bitwise_not(wpl, wpl);

//    // Detect pawn positions and flip colors
//    processPieceMatch(src1, dst1, wpl, wql, 0.98, false);
//    processPieceMatch(src1, dst1, wpd, wqd, 0.99, false);
//    processPieceMatch(src1, dst1, bpd, bqd, 0.99, true);
//    processPieceMatch(src1, dst1, bpl, bql, 0.99, true);

//    processPieceMatch(src2, dst2, wpd, wqd, 0.98, false);
//    processPieceMatch(src2, dst2, wpl, wql, 0.98, false);
//    processPieceMatch(src2, dst2, bpd, bqd, 0.99, true);
//    processPieceMatch(src2, dst2, bpl, bql, 0.99, true);

//    processPieceMatch(src3, dst3, wpd, wqd, 0.98, false);
//    processPieceMatch(src3, dst3, wpl, wql, 0.99, false);
//    processPieceMatch(src3, dst3, bpd, bqd, 0.99, true);
//    processPieceMatch(src3, dst3, bpl, bql, 0.99, true);

//    // Display results
////    imshow("Board 1 Results", dst1);
//    imshow("Board 2 Results", dst2);
////    imshow("Board 3 Results", dst3);

//    while(1)
//    {
//        keyPress = waitKey();
//        // Press q key to close window
//        if (keyPress == 'q')
//        {
//            destroyAllWindows();
//            break;
//        }
//    }
//    return 0;
//}

//// Source: https://stackoverflow.com/questions/32041063/multiple-template-matching-only-detects-one-match/32095085#32095085
//// This code is based on the solution at this link
//void processPieceMatch(Mat src, Mat dst, Mat temp, Mat replacementTemp, double thresh, bool isBlack) {
//    // Match the A template on the grid
//    Mat1f result;
//    matchTemplate(src, temp, result, TM_CCORR_NORMED);

//    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
//    threshold(result, result, thresh, 1., THRESH_BINARY);

//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    result.convertTo(resb, CV_8U, 255);

//    // Find the contours of the grayscale match result
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    // Process each matching A
//    for (uint i=0; i<contours.size(); ++i)
//    {
//        // Mask out all other matching A's except the one that corresponds to the current contour
//        Mat mask(result.rows, result.cols, uchar(0));
//        drawContours(mask, contours, i, Scalar(255), FILLED);

//        // Find the maximum matching location
//        Point max_point;
//        double max_val;
//        minMaxLoc(result, NULL, &max_val, NULL, &max_point, mask);

//        // Replace the pixels at this pawn with the pixels for the flipped color
//        if (isBlack) {
//            Rect roi(max_point.x, max_point.y, 60, 60);
//            replacementTemp.copyTo(dst(roi));
//        } else if (!isBlack) {
//            Rect roi(max_point.x, max_point.y, 60, 60);
//            replacementTemp.copyTo(dst(roi));
//        }
////         && max_point.y >= 420
////         and max_point.y < 60
//    }
//}

// Store the board location with a struct containing: Mat of the piece, max_point, and max_val
