#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

// This program was used to generate the mario templates used for template matching and keypoint matching
int main()
{
    char keyPress;
    cout << "p1_opencv\n";
    // Read image
    Mat twoCupsFrame1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2017\\template\\frame_processing\\two_cups1.png");
    Mat threeCupsFrame1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2017\\template\\frame_processing\\three_cups1.png");

//    // Detect the orange ball color
//    Mat mask;
//    inRange(twoCupsFrame1, Scalar(100,130,200), Scalar(180,220,255), mask);
//    twoCupsFrame1.setTo(Scalar(0, 0, 0), mask);

    // Detect the red cup
//    Mat mask;
//    inRange(twoCupsFrame1, Scalar(40,30,140), Scalar(140,100,220), mask);
//    twoCupsFrame1.setTo(Scalar(0, 0, 0), mask);

//    // Detect the green cup
//    Mat mask;
//    inRange(twoCupsFrame1, Scalar(100,180,70), Scalar(200,255,150), mask);
//    twoCupsFrame1.setTo(Scalar(0, 0, 0), mask);

    // Detect the blue cup
    Mat mask;
    inRange(threeCupsFrame1, Scalar(180,60,0), Scalar(255,130,80), mask);
    threeCupsFrame1.setTo(Scalar(0, 0, 0), mask);

    imshow("twoCupsFrame1", twoCupsFrame1);
    imshow("threeCupsFrame1", threeCupsFrame1);

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
