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
//    Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_2\\p2_board_1.jpg", IMREAD_GRAYSCALE);;
//    Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_3\\p3_board_2.jpg", IMREAD_GRAYSCALE);;
//    Mat src3 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_4\\p4_board_1.jpg", IMREAD_GRAYSCALE);;
//    Mat src4 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_3\\p3_board_1.jpg", IMREAD_GRAYSCALE);;

//    imshow("src1", src1);
//    imshow("src2", src2);
//    imshow("src3", src3);
//    imshow("src4", src4);

//    // Create a template image for all chess pieces, colors, and board positions (24 in total, 6 pieces and 4 templates for each piece)
//    createChessPieceTemplate(src1, 241, 61, "blackPawnDark.jpg");
//    createChessPieceTemplate(src1, 181, 61, "blackPawnLight.jpg");
//    createChessPieceTemplate(src1, 181, 361, "whitePawnDark.jpg");
//    createChessPieceTemplate(src1, 241, 361, "whitePawnLight.jpg");

//    createChessPieceTemplate(src1, 421, 1, "blackRookDark.jpg");
//    createChessPieceTemplate(src1, 1, 1, "blackRookLight.jpg");
//    createChessPieceTemplate(src1, 1, 421, "whiteRookDark.jpg");
//    createChessPieceTemplate(src1, 421, 421, "whiteRookLight.jpg");

//    createChessPieceTemplate(src1, 301, 1, "blackBishopDark.jpg");
//    createChessPieceTemplate(src1, 121, 1, "blackBishopLight.jpg");
//    createChessPieceTemplate(src1, 121, 421, "whiteBishopDark.jpg");
//    createChessPieceTemplate(src1, 301, 421, "whiteBishopLight.jpg");

//    createChessPieceTemplate(src1, 61, 1, "blackKnightDark.jpg");
//    createChessPieceTemplate(src1, 361, 1, "blackKnightLight.jpg");
//    createChessPieceTemplate(src1, 61, 421, "whiteKnightDark.jpg");
//    createChessPieceTemplate(src1, 361, 421, "whiteKnightLight.jpg");

//    createChessPieceTemplate(src4, 421, 1, "blackQueenDark.jpg");
//    createChessPieceTemplate(src3, 241, 121, "blackQueenLight.jpg");
//    createChessPieceTemplate(src1, 241, 421, "whiteQueenDark.jpg");
//    createChessPieceTemplate(src3, 181, 301, "whiteQueenLight.jpg");

//    createChessPieceTemplate(src2, 241, 61, "blackKingDark.jpg");
//    createChessPieceTemplate(src1, 181, 1, "blackKingLight.jpg");
//    createChessPieceTemplate(src2, 421, 121, "whiteKingDark.jpg");
//    createChessPieceTemplate(src1, 181, 421, "whiteKingLight.jpg");

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
//    Rect roi(topLeftX, topLeftY, 59, 59);
//    Mat temp = src(roi);

//    imwrite(fileName, temp);
//}
