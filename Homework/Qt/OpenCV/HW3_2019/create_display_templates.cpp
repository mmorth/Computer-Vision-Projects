//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void createDigitTemplate(Mat src, int topLeftX, int topLeftY, string fileName);

//// This program was used to generate the mario templates used for template matching and keypoint matching
//int main()
//{
//    char keyPress;
//    cout << "p1_opencv\n";
//    // Read image
//    Mat displayFrame1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\frame2.png");
//    Mat displayFrame2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\frame62.png");
//    Mat displayFrame3 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2019\\HW3\\display_templates\\frame336.png");

//    imshow("displayFrame1", displayFrame1);
//    imshow("displayFrame2", displayFrame2);
//    imshow("displayFrame3", displayFrame3);

//    // Create a template image for all chess pieces, colors, and board positions (24 in total, 6 pieces and 4 templates for each piece)
//    createDigitTemplate(displayFrame2, 249, 71, "digit0Template.png");
//    createDigitTemplate(displayFrame2, 287, 71, "digit1Template.png");
//    createDigitTemplate(displayFrame3, 249, 71, "digit2Template.png");
//    createDigitTemplate(displayFrame2, 350, 71, "digit3Template.png");
//    createDigitTemplate(displayFrame2, 165, 71, "digit4Template.png");
//    createDigitTemplate(displayFrame2, 131, 71, "digit5Template.png");
//    createDigitTemplate(displayFrame2, 26, 71, "digit6Template.png");
//    createDigitTemplate(displayFrame2, 70, 71, "digit7Template.png");
//    createDigitTemplate(displayFrame1, 163, 71, "digit8Template.png");
//    createDigitTemplate(displayFrame3, 350, 71, "digit9Template.png");

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
//void createDigitTemplate(Mat src, int topLeftX, int topLeftY, string fileName) {
//    Rect roi(topLeftX, topLeftY, 28, 39);
//    Mat temp = src(roi);

//    imwrite(fileName, temp);
//}
