//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void createMarioTemplate(Mat src, int topLeftX, int topLeftY, string fileName);

//// This program was used to generate the mario templates used for template matching and keypoint matching
//int main()
//{
//    char keyPress;
//    cout << "p1_opencv\n";
//    // Read image
//    Mat marioSmallLeftEnv = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallLeftEnv.png", IMREAD_GRAYSCALE);
//    Mat marioSmallRightEnv = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallRightEnv.png", IMREAD_GRAYSCALE);
//    Mat marioSmallTurningLeftEnv = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallTurningLeftEnv.png", IMREAD_GRAYSCALE);
//    Mat marioSmallTurningRightEnv = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\marioSmallTurningRightEnv.png", IMREAD_GRAYSCALE);

//    imshow("marioSmallLeftEnv", marioSmallLeftEnv);
//    imshow("marioSmallRightEnv", marioSmallRightEnv);
//    imshow("marioSmallTurningLeftEnv", marioSmallTurningLeftEnv);
//    imshow("marioSmallTurningRightEnv", marioSmallTurningRightEnv);

//    // Create a template image for all chess pieces, colors, and board positions (24 in total, 6 pieces and 4 templates for each piece)
//    createMarioTemplate(marioSmallLeftEnv, 575, 769, "marioSmallLeftFace.png");
//    createMarioTemplate(marioSmallRightEnv, 840, 769, "marioSmallRightFace.png");
//    createMarioTemplate(marioSmallTurningLeftEnv, 843, 769, "marioSmallTurningLeftFace.png");
//    createMarioTemplate(marioSmallTurningRightEnv, 841, 769, "marioSmallTurningRightFace.png");

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
//void createMarioTemplate(Mat src, int topLeftX, int topLeftY, string fileName) {
//    Rect roi(topLeftX, topLeftY, 48, 28);
//    Mat temp = src(roi);

//    imwrite(fileName, temp);
//}
