//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void processPieceMatch(Mat src, Mat dst, Mat temp, Mat replacementTemp, double thresh);

//int main()
//{
//    char keyPress;
//    cout << "p2c_opencv\n";
//    // Read image
//    Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_2\\p2_board_1.jpg", IMREAD_GRAYSCALE);
//    Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_2\\p2_board_2.jpg", IMREAD_GRAYSCALE);
//    Mat src3 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_2\\p2_board_3.jpg", IMREAD_GRAYSCALE);

//    // Load the knight chess piece templates
//    Mat bpd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnDark.jpg", IMREAD_GRAYSCALE);
//    Mat bpl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackPawnLight.jpg", IMREAD_GRAYSCALE);
//    Mat wpd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnDark.jpg", IMREAD_GRAYSCALE);
//    Mat wpl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whitePawnLight.jpg", IMREAD_GRAYSCALE);

//    Mat dst1 = src1.clone();
//    Mat dst2 = src2.clone();
//    Mat dst3 = src3.clone();

//    // Detect pawn positions and flip colors
//    processPieceMatch(src1, dst1, wpd, bpd, 0.95);
//    processPieceMatch(src1, dst1, wpl, bpl, 0.95);
//    processPieceMatch(src1, dst1, bpd, wpd, 0.999);
//    processPieceMatch(src1, dst1, bpl, wpl, 0.9998);

//    processPieceMatch(src2, dst2, wpd, bpd, 0.95);
//    processPieceMatch(src2, dst2, wpl, bpl, 0.95);
//    processPieceMatch(src2, dst2, bpd, wpd, 0.999);
//    processPieceMatch(src2, dst2, bpl, wpl, 0.9998);

//    processPieceMatch(src3, dst3, wpd, bpd, 0.95);
//    processPieceMatch(src3, dst3, wpl, bpl, 0.95);
//    processPieceMatch(src3, dst3, bpd, wpd, 0.999);
//    processPieceMatch(src3, dst3, bpl, wpl, 0.9998);

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
//void processPieceMatch(Mat src, Mat dst, Mat temp, Mat replacementTemp, double thresh) {
//    // Match the A template on the grid
//    Mat1f result;
//    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

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
//        Rect roi(max_point.x, max_point.y, 59, 59);
//        replacementTemp.copyTo(dst(roi));
//    }
//}
