//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//bool board1[8][8];
//bool board2[8][8];
//bool board3[8][8];

//void processPieceMatch(Mat src, Mat temp, int board);

//int main()
//{
//    char keyPress;
//    cout << "p1_opencv\n";
//    // Read image
//    Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_2\\p2_board_1.jpg", IMREAD_GRAYSCALE);
//    Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_2\\p2_board_2.jpg", IMREAD_GRAYSCALE);
//    Mat src3 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_2\\p2_board_3.jpg", IMREAD_GRAYSCALE);

//    // Load the knight chess piece templates
//    Mat bpd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnDark.jpg", IMREAD_GRAYSCALE);
//    Mat bpl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnLight.jpg", IMREAD_GRAYSCALE);
//    Mat wpd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnDark.jpg", IMREAD_GRAYSCALE);
//    Mat wpl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnLight.jpg", IMREAD_GRAYSCALE);

//    Mat pieceTemplates[] = {bpd, bpl, wpd, wpl};
//    int numPieceTemplates = 4;

//    Mat dst1;
//    Mat dst2;
//    Mat dst3;
//    cvtColor(src1, dst1, COLOR_GRAY2BGR);
//    cvtColor(src2, dst2, COLOR_GRAY2BGR);
//    cvtColor(src3, dst3, COLOR_GRAY2BGR);

//    for (int i = 0; i < 4; i++) {
//        processPieceMatch(src1, pieceTemplates[i], 1);
//        processPieceMatch(src2, pieceTemplates[i], 2);
//        processPieceMatch(src3, pieceTemplates[i], 3);
//    }

//    // Loop through the board and put the overlay where there is a pawn
//    int index1 = 1;
//    int index2 = 1;
//    int index3 = 1;
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (board1[j][i]) {
//                putText(dst1, std::to_string(index1++), Point(j*60+10, i*60+35), FONT_HERSHEY_TRIPLEX, 1, Scalar(0, 0, 255), 3);
//            }
//            if (board2[j][i]) {
//                putText(dst2, std::to_string(index2++), Point(j*60+10, i*60+35), FONT_HERSHEY_TRIPLEX, 1, Scalar(0, 0, 255), 3);
//            }
//            if (board3[j][i]) {
//                putText(dst3, std::to_string(index3++), Point(j*60+10, i*60+35), FONT_HERSHEY_TRIPLEX, 1, Scalar(0, 0, 255), 3);
//            }
//        }
//    }

//    // Display results
//    imshow("Board 1 Results", dst1);
//    imshow("Board 2 Results", dst2);
//    imshow("Board 3 Results", dst3);

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
//void processPieceMatch(Mat src, Mat temp, int board) {
//    // Match the A template on the grid
//    Mat1f result;
//    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

//    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
//    double thresh = 0.95;
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

//        // Signal that a pawn was found at the current location
//        if (board == 1) {
//            board1[max_point.x/60][max_point.y/60] = true;
//        } else if (board == 2) {
//            board2[max_point.x/60][max_point.y/60] = true;
//        } else {
//            board3[max_point.x/60][max_point.y/60] = true;
//        }
//    }
//}
