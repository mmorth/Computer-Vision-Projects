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
    cout << "p4_opencv_code.cpp\n";

    // Read image and template and make a copy to have the original image
    Mat src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_4\\p4_search.png", IMREAD_GRAYSCALE);
    Mat temp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\A.png", IMREAD_GRAYSCALE);
    Mat dst = src.clone();

    // Source: https://stackoverflow.com/questions/32041063/multiple-template-matching-only-detects-one-match/32095085#32095085

    // Match the A template on the grid
    Mat1f result;
    matchTemplate(src, temp, result, TM_CCOEFF_NORMED);

    // Replace all pixels with a value less than 0.95 with 0, so they are not processed as a match (confidence threshold)
    double thresh = 0.95;
    threshold(result, result, thresh, 1., THRESH_BINARY);

    // Find the contours of the grayscale match result (these will be all the points where A's are located)
    Mat1b resb;
    result.convertTo(resb, CV_8U, 255);

    vector<vector<Point>> contours;
    findContours(resb, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);

    // Convert the source to BGR to allow the A's to be colored red
    cvtColor(src, src, COLOR_GRAY2BGR);

    // Process each matching A
    for (int i=0; i<contours.size(); ++i)
    {
        // Mask out all other matching A's except the one that corresponds to the current contour
        Mat1b mask(result.rows, result.cols, uchar(0));
        drawContours(mask, contours, i, Scalar(255), FILLED);

        // Find the maximum matching location
        Point max_point;
        double max_val;
        minMaxLoc(result, NULL, &max_val, NULL, &max_point, mask);

        // Highlight squares with A's with red
        rectangle(src, Rect(max_point.x, max_point.y, temp.cols, temp.rows), Scalar(0,0,255), FILLED);
    }

    // Convert dst to BGR to color A matches
    cvtColor(dst, dst, COLOR_GRAY2BGR);
    addWeighted(src, 0.5, dst, 0.5, 0, dst);

    // Display result
    imshow("Result", dst);

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
