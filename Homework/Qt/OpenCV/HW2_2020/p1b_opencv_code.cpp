#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

int main()
{
    char keyPress;
    cout << "p1_opencv\n";

    // Read image
    Mat src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2020\\HW2\\input\\Part_1\\p1_board.jpg", IMREAD_GRAYSCALE);

    // Apply threshold to convert the black and white spots on board to black and white
    threshold(src, src, 225, 255, THRESH_BINARY);

    // Flip the colors of the black and white squares
    Mat mask;
    inRange(src, Scalar(255), Scalar(255), mask);
    src.setTo(Scalar(160), mask);
    inRange(src, Scalar(0), Scalar(0), mask);
    src.setTo(Scalar(240), mask);

    // Display results
    imshow("Input", src);

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
