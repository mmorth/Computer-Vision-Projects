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
//    createChessPieceTemplate(src1, 240, 60, "blackPawnDark.jpg");
//    createChessPieceTemplate(src1, 180, 60, "blackPawnLight.jpg");
//    createChessPieceTemplate(src1, 180, 360, "whitePawnDark.jpg");
//    createChessPieceTemplate(src1, 240, 360, "whitePawnLight.jpg");

//    createChessPieceTemplate(src1, 420, 0, "blackRookDark.jpg");
//    createChessPieceTemplate(src1, 0, 0, "blackRookLight.jpg");
//    createChessPieceTemplate(src1, 0, 420, "whiteRookDark.jpg");
//    createChessPieceTemplate(src1, 420, 420, "whiteRookLight.jpg");

//    createChessPieceTemplate(src1, 300, 0, "blackBishopDark.jpg");
//    createChessPieceTemplate(src1, 120, 0, "blackBishopLight.jpg");
//    createChessPieceTemplate(src1, 120, 420, "whiteBishopDark.jpg");
//    createChessPieceTemplate(src1, 300, 420, "whiteBishopLight.jpg");

//    createChessPieceTemplate(src1, 60, 0, "blackKnightDark.jpg");
//    createChessPieceTemplate(src1, 360, 0, "blackKnightLight.jpg");
//    createChessPieceTemplate(src1, 60, 420, "whiteKnightDark.jpg");
//    createChessPieceTemplate(src1, 360, 420, "whiteKnightLight.jpg");

//    createChessPieceTemplate(src4, 420, 0, "blackQueenDark.jpg");
//    createChessPieceTemplate(src3, 240, 120, "blackQueenLight.jpg");
//    createChessPieceTemplate(src1, 240, 420, "whiteQueenDark.jpg");
//    createChessPieceTemplate(src3, 180, 300, "whiteQueenLight.jpg");

//    createChessPieceTemplate(src2, 240, 60, "blackKingDark.jpg");
//    createChessPieceTemplate(src1, 180, 0, "blackKingLight.jpg");
//    createChessPieceTemplate(src2, 420, 120, "whiteKingDark.jpg");
//    createChessPieceTemplate(src1, 180, 420, "whiteKingLight.jpg");

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
//    Rect roi(topLeftX, topLeftY, 60, 60);
//    Mat temp = src(roi);

//    imwrite(fileName, temp);
//}
