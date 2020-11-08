//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void createChessPieceTemplate(Mat src, int topLeftX, int topLeftY, string fileName);

//// This program was used to generate the chess piece templates used for template matching
//int main()
//{
//    char keyPress;
//    cout << "p1_opencv\n";
//    // Read image
//    Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Part_3a\\p3a_board_1.jpg", IMREAD_GRAYSCALE);
//    Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Part_2\\p2_board_1.jpg", IMREAD_GRAYSCALE);
//    Mat src3 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Part_3b\\p3b_board_3.jpg", IMREAD_GRAYSCALE);
//    Mat src4 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Part_2\\p2_board_2.jpg", IMREAD_GRAYSCALE);

//    // Create a template image for all chess pieces, colors, and board positions (24 in total, 6 pieces and 4 templates for each piece)
//    createChessPieceTemplate(src1, 10, 662, "whiteKnightDark.jpg");
//    createChessPieceTemplate(src1, 530, 792, "whiteKnightLight.jpg");
//    createChessPieceTemplate(src1, 660, 272, "blackKnightDark.jpg");
//    createChessPieceTemplate(src2, 786, 7, "blackKnightLight.jpg");

////    imshow("src1", src1);
////    imshow("src2", src2);
////    imshow("src3", src3);
////    imshow("src4", src4);

//    createChessPieceTemplate(src1, 270, 402, "whiteBishopDark.jpg");
//    createChessPieceTemplate(src1, 660, 662, "whiteBishopLight.jpg");
//    createChessPieceTemplate(src1, 920, 272, "blackBishopDark.jpg");
//    createChessPieceTemplate(src1, 10, 272, "blackBishopLight.jpg");

//    createChessPieceTemplate(src2, 6, 917, "whiteRookDark.jpg");
//    createChessPieceTemplate(src1, 10, 532, "whiteRookLight.jpg");
//    createChessPieceTemplate(src1, 660, 12, "blackRookDark.jpg");
//    createChessPieceTemplate(src2, 6, 7, "blackRookLight.jpg");

//    createChessPieceTemplate(src2, 526, 917, "whiteQueenDark.jpg");
//    createChessPieceTemplate(src1, 140, 662, "whiteQueenLight.jpg");
//    createChessPieceTemplate(src3, 135, 8, "blackQueenDark.jpg");
//    createChessPieceTemplate(src4, 397, 919, "blackQueenLight.jpg");

//    createChessPieceTemplate(src4, 527, 919, "whiteKingDark.jpg");
//    createChessPieceTemplate(src1, 400, 662, "whiteKingLight.jpg");
//    createChessPieceTemplate(src1, 140, 12, "blackKingDark.jpg");
////    createChessPieceTemplate(src1, , , "blackKingLight.jpg");

//    // Run function to display location overlay
////    imshow("Result", src2);

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

//// This function creates a template for the the specified paramters and saves the resulting image
//void createChessPieceTemplate(Mat src, int topLeftX, int topLeftY, string fileName) {
//    Rect roi(topLeftX, topLeftY, 130, 130);
//    Mat temp = src(roi);

//    imwrite(fileName, temp);
//}
