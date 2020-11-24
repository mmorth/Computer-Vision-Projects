//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void createUndergroundCoinTemplate(Mat src, int topLeftX, int topLeftY, string fileName);
//void createCoinTemplate(Mat src, int topLeftX, int topLeftY, string fileName);
//void createFireballTemplate(Mat src, int topLeftX, int topLeftY, string fileName);

//// This program was used to generate the mario templates used for template matching and keypoint matching
//int main()
//{
//    char keyPress;
//    cout << "p1_opencv\n";
//    // Read image

////    Mat coinTemp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\coinCollected.png");
////    Mat coinUndergroundBright = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\coinUnderground.png");
////    Mat coinUndergroundMid = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\frame206.png");
////    Mat coinUndergroundDark = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\frame210.png");

//////    imshow("coinUnderground", coinUndergroundBright);
//////    imshow("coinTemp", coinTemp);

//////    createCoinTemplate(coinTemp, 817, 416, "coinCollectedTemp.png");
//////    createUndergroundCoinTemplate(coinUndergroundBright, 262, 358, "coinUndergroundBright.png");
//////    createUndergroundCoinTemplate(coinUndergroundMid, 262, 358, "coinUndergroundMid.png");
//////    createUndergroundCoinTemplate(coinUndergroundDark, 262, 358, "coinUndergroundDark.png");

////    Mat coinBackgroundQuestion = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\coinBackgroundQuestion.png");
////    Mat coinBackgroundUnderground = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\coinBackgroundUnderground.png");
////    Mat fireballBackground = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\fireballBackground.png");

////    imshow("coinBackgroundQuestion", coinBackgroundQuestion);
////    imshow("coinBckgroundUnderground", coinBackgroundUnderground);
////    imshow("fireballBackground", fireballBackground);

////    createCoinTemplate(coinBackgroundQuestion, 854, 416, "coinBackgroundQuestionTemp.png");
////    createCoinTemplate(coinBackgroundUnderground, 821, 406, "coinBackgroundUndergroundTemp.png");
////    createFireballTemplate(fireballBackground, 836, 613, "fireballBackgroundTemp.png");

//    Mat frame = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2020\\HW3\\mario_templates\\frame1008.png");

//    Mat mask;
//    inRange(frame, Scalar(110, 110, 110), Scalar(120, 120, 120), mask);

//    // Convert result to CV_8U to support finding contours
//    Mat resb;
//    mask.convertTo(resb, CV_8U, 255);

//    // Find the contours of the grayscale match result
//    vector<vector<Point>> contours;
//    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    printf("# Contours = %d\n", contours.size());
//    for (int i = 0; i < contours.size(); i++) {
//        if (contourArea(contours[i]) > 800000 && contourArea(contours[i]) < 900000) {
//            drawContours(frame, contours, i, Scalar(0, 0, 255), 1);
//            Rect br = boundingRect(contours[i]);
//            printf("x = %d\n", br.x);
//            printf("y = %d\n", br.y);
//        }
//    }

//    imshow("tetrisWindow", frame);

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

//// This function creates a template for the frame when mario shoots out a fireball
//void createFireballTemplate(Mat src, int topLeftX, int topLeftY, string fileName) {
//    Rect roi(topLeftX, topLeftY, 95, 120);
//    Mat temp = src(roi);

//    imwrite(fileName, temp);
//}
