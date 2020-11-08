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

//    imshow("src", src1);

//    // Create a template image for all chess pieces, colors, and board positions (24 in total, 6 pieces and 4 templates for each piece)
//    createChessPieceTemplate(src1, 241, 61, "blackPawnDark.jpg");
//    createChessPieceTemplate(src1, 181, 61, "blackPawnLight.jpg");
//    createChessPieceTemplate(src1, 181, 361, "whitePawnDark.jpg");
//    createChessPieceTemplate(src1, 241, 361, "whitePawnLight.jpg");

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
