//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void createUndergroundCoinTemplate(Mat src, int topLeftX, int topLeftY, string fileName);
//void createCoinTemplate(Mat src, int topLeftX, int topLeftY, string fileName);

//// This program was used to generate the mario templates used for template matching and keypoint matching
//int main()
//{
//    char keyPress;
//    cout << "p1_opencv\n";
//    // Read image

//    Mat coinTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\coinCollected.png");
//    Mat coinUndergroundBright = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\coinUnderground.png");
//    Mat coinUndergroundMid = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\frame206.png");
//    Mat coinUndergroundDark = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\frame210.png");

//    Mat mask;
//    Mat fc = coinTemp.clone();
//    // Mask the blue background
//    inRange(fc, Scalar(220,127,79), Scalar(255,140,95), mask);
//    fc.setTo(Scalar(0, 0, 0), mask);
//    // Mask the green hills
//    inRange(fc, Scalar(0,100,0), Scalar(50,190,50), mask);
//    fc.setTo(Scalar(0, 0, 0), mask);
//    // Mask the green bushes
//    inRange(fc, Scalar(0,120,0), Scalar(80,255,160), mask);
//    fc.setTo(Scalar(0, 0, 0), mask);
//    // Mask the colored outlines
//    inRange(fc, Scalar(140,60,30), Scalar(255,150,120), mask);
//    fc.setTo(Scalar(0, 0, 0), mask);
//    // Mask the dark outlines
//    inRange(fc, Scalar(0,0,0), Scalar(100,100,100), mask);
//    fc.setTo(Scalar(0, 0, 0), mask);

//    imshow("fc", fc);

////    imshow("coinUnderground", coinUndergroundBright);
////    imshow("coinTemp", coinTemp);

////    createCoinTemplate(coinTemp, 817, 416, "coinCollectedTemp.png");
////    createUndergroundCoinTemplate(coinUndergroundBright, 262, 358, "coinUndergroundBright.png");
////    createUndergroundCoinTemplate(coinUndergroundMid, 262, 358, "coinUndergroundMid.png");
////    createUndergroundCoinTemplate(coinUndergroundDark, 262, 358, "coinUndergroundDark.png");

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
//void createCoinTemplate(Mat src, int topLeftX, int topLeftY, string fileName) {
//    Rect roi(topLeftX, topLeftY, 56, 111);
//    Mat temp = src(roi);

//    imwrite(fileName, temp);
//}

//// This function creates a template for the the specified paramters and saves the resulting image
//void createUndergroundCoinTemplate(Mat src, int topLeftX, int topLeftY, string fileName) {
//    Rect roi(topLeftX, topLeftY, 31, 54);
//    Mat temp = src(roi);

//    imwrite(fileName, temp);
//}
