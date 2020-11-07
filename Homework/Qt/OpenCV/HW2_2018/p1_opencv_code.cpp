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
    Mat src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2018\\HW2\\input\\Part_1\\p1_board.jpg", IMREAD_GRAYSCALE);
    Mat border = src.clone();

    // Threshold and apply close operation to remove all pixels that are not part of the border
    threshold(border, border, 248, 255, THRESH_BINARY);

    int elementValue = 5;
    Mat element = getStructuringElement( MORPH_RECT, Size( 2*elementValue + 1, 2*elementValue+1 ), Point( elementValue, elementValue ) );
    morphologyEx( border, border, MORPH_CLOSE, element );

    cvtColor(border, border, COLOR_GRAY2BGR);

    // Apply threshold to convert the black and white spots on board to black and white
    threshold(src, src, 225, 255, THRESH_BINARY);
    cvtColor(src, src, COLOR_GRAY2BGR);

    // Convert all white pixels to green and all black pixels to red
    Mat mask;
    inRange(src, Scalar(255, 255, 255), Scalar(255, 255, 255), mask);
    src.setTo(Scalar(0, 255, 0), mask);
    inRange(src, Scalar(0, 0, 0), Scalar(0, 0, 0), mask);
    src.setTo(Scalar(0, 0, 255), mask);

    // Restore border and display reslt
    src = src + border;

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
