//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void processPieceMatch(Mat src, Mat hl, Mat temp, Mat replacementTemp);
//void processColorChange(Mat src);
//void colorPieces(Mat temp, Mat hlTemp, Scalar color);

//int main()
//{
//    char keyPress;
//    cout << "p1_opencv\n";
//    // Read image
//    Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_3\\p3_board_1.jpg", IMREAD_GRAYSCALE);
//    Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_3\\p3_board_2.jpg", IMREAD_GRAYSCALE);
//    Mat src3 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_3\\p3_board_3.jpg", IMREAD_GRAYSCALE);

//    // Load the knight chess piece templates
//    Mat brd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackRookDark.jpg", IMREAD_GRAYSCALE);
//    Mat brl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackRookLight.jpg", IMREAD_GRAYSCALE);
//    Mat wrd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteRookDark.jpg", IMREAD_GRAYSCALE);
//    Mat wrl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteRookLight.jpg", IMREAD_GRAYSCALE);

//    Mat bbd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackBishopDark.jpg", IMREAD_GRAYSCALE);
//    Mat bbl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackBishopLight.jpg", IMREAD_GRAYSCALE);
//    Mat wbd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteBishopDark.jpg", IMREAD_GRAYSCALE);
//    Mat wbl = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteBishopLight.jpg", IMREAD_GRAYSCALE);

//    Mat bqd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackQueenDark.jpg", IMREAD_GRAYSCALE);
//    Mat bql = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\blackQueenLight.jpg", IMREAD_GRAYSCALE);
//    Mat wqd = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteQueenDark.jpg", IMREAD_GRAYSCALE);
//    Mat wql = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Chess_Piece_Templates\\whiteQueenLight.jpg", IMREAD_GRAYSCALE);

//    Mat pieceTemplates[] = {brd,brl,wrd,wrl,bbd,bbl,wbd,wbl,bqd,bql,wqd,wql};
//    int numPieceTemplates = 12;

//    Mat dst1;
//    Mat dst2;
//    Mat dst3;
//    cvtColor(src1, dst1, COLOR_GRAY2BGR);
//    cvtColor(src2, dst2, COLOR_GRAY2BGR);
//    cvtColor(src3, dst3, COLOR_GRAY2BGR);

//    // Fill in the piece wil the color
//    Mat brdc = brd.clone();
//    Mat brlc = brl.clone();
//    Mat wrdc = wrd.clone();
//    Mat wrlc = wrl.clone();
//    Mat bbdc = bbd.clone();
//    Mat bblc = bbl.clone();
//    Mat wbdc = wbd.clone();
//    Mat wblc = wbl.clone();
//    Mat bqdc = bqd.clone();
//    Mat bqlc = bql.clone();
//    Mat wqdc = wqd.clone();
//    Mat wqlc = wql.clone();
//    cvtColor(brdc, brdc, COLOR_GRAY2BGR);
//    cvtColor(brlc, brlc, COLOR_GRAY2BGR);
//    cvtColor(wrdc, wrdc, COLOR_GRAY2BGR);
//    cvtColor(wrlc, wrlc, COLOR_GRAY2BGR);
//    cvtColor(bbdc, bbdc, COLOR_GRAY2BGR);
//    cvtColor(bblc, bblc, COLOR_GRAY2BGR);
//    cvtColor(wbdc, wbdc, COLOR_GRAY2BGR);
//    cvtColor(wblc, wblc, COLOR_GRAY2BGR);
//    cvtColor(bqdc, bqdc, COLOR_GRAY2BGR);
//    cvtColor(bqlc, bqlc, COLOR_GRAY2BGR);
//    cvtColor(wqdc, wqdc, COLOR_GRAY2BGR);
//    cvtColor(wqlc, wqlc, COLOR_GRAY2BGR);
//    Mat pieceTemplatesReplacements[] = {brdc,brlc,wrdc,wrlc,bbdc,bblc,wbdc,wblc,bqdc,bqlc,wqdc,wqlc};

//    // Fill in chess pieces
//    Scalar colors[] = {Scalar(0, 0, 255), Scalar(0, 128, 255), Scalar(255, 255, 0)};
//    for (int i = 0; i < numPieceTemplates; i++) {
//        colorPieces(pieceTemplates[i], pieceTemplatesReplacements[i], colors[i/4]);
//    }

//    for (int i = 0; i < numPieceTemplates; i++) {
//        processPieceMatch(src1, dst1, pieceTemplates[i], pieceTemplatesReplacements[i]);
//        processPieceMatch(src2, dst2, pieceTemplates[i], pieceTemplatesReplacements[i]);
//        processPieceMatch(src3, dst3, pieceTemplates[i], pieceTemplatesReplacements[i]);
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
//void processPieceMatch(Mat src, Mat dst, Mat temp, Mat replacementTemp) {
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

//        // Draw the font in different colors
//        Rect roi(max_point.x, max_point.y, 59, 59);
//        replacementTemp.copyTo(dst(roi));
//    }
//}

//// Highlights the rooks
//void colorPieces(Mat temp, Mat hlTemp, Scalar color) {
//    Mat resb;
//    Mat oTemp = temp.clone();
//    threshold(oTemp, oTemp, 246, 255, THRESH_BINARY);
//    oTemp.convertTo(resb, CV_8U, 255);

//    // Find the contours of the grayscale match result
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    // Fill in the chess pieces
//    for (uint i=0; i<contours.size(); ++i)
//    {
//        drawContours(hlTemp, contours, i, color, FILLED);
//    }
//}
