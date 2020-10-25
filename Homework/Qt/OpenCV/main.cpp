#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat image;
    char keyPress;
    cout << "Welcome to Qt\n";
    // Read image
    image = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\OpenCV.jpeg", IMREAD_COLOR);
    imshow("OpenCV and Qt", image);

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