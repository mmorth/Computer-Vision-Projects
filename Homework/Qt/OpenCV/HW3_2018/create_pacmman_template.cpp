//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//void createPacmanLifeTemplate(Mat src, int topLeftX, int topLeftY, string fileName);

//// This program was used to generate the mario templates used for template matching and keypoint matching
//int main()
//{
//    char keyPress;
//    cout << "p1_opencv\n";
//    // Read image
//    Mat pacmanLivesFrame = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework3\\HW3_2018\\HW3\\input\\pacman_templates\\pacmanLivesFrame.png");

//    imshow("pacmanLivesFrame", pacmanLivesFrame);

//    // Create a template image for all chess pieces, colors, and board positions (24 in total, 6 pieces and 4 templates for each piece)
//    createPacmanLifeTemplate(pacmanLivesFrame, 18, 273, "pacmanLifeTemplate.png");

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
//void createPacmanLifeTemplate(Mat src, int topLeftX, int topLeftY, string fileName) {
//    Rect roi(topLeftX, topLeftY, 11, 12);
//    Mat temp = src(roi);

//    imwrite(fileName, temp);
//}
