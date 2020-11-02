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
    cout << "p3_opencv_code.cpp\n";

    // Read image and template and make a copy to have the original image
    Mat src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Part_4\\p4_search.png", IMREAD_GRAYSCALE);
    Mat temp = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2019\\HW2\\Letter_Cutouts\\A.png", IMREAD_GRAYSCALE);
    Mat dst = src.clone();

    // Execute template matching
    Mat matchResult;
    matchTemplate(src, temp, matchResult, TM_CCOEFF_NORMED);
    cv::threshold(matchResult, matchResult, 0.90, 1., THRESH_BINARY);

    /// Create the result matrix
    int result_cols =  src.cols - temp.cols + 1;
    int result_rows = src.rows - temp.rows + 1;

    Mat result;
    result.create( result_cols, result_rows, CV_32FC1 );

    // Do the Matching and Normalize
    int match_method = TM_CCOEFF;
    matchTemplate( src, temp, result, match_method );
    normalize( result, result, 0, 1, NORM_MINMAX, -1, Mat() );

    // Convert the source to BGR to allow the A's to be colored red
    cvtColor(src, src, COLOR_GRAY2BGR);

    // Localizing the best match with minMaxLoc
    Point minLoc; Point maxLoc;
    Point matchLoc;
    double minVal; double maxVal;
    for(int k=1;k<=1;k++)
    {
        // Create the threshold and determine the min and max locations
        double threshold = 0.999;
        minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

        // TODO: Update this masking to prevent from matching the same instance multiple times
        result.at<float>(minLoc.x,minLoc.y)=1.0;
        result.at<float>(maxLoc.x,maxLoc.y)=0.0;

        // For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
        if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED )
        { matchLoc = minLoc; }
        else
        { matchLoc = maxLoc; }

        printf("maxVal = %.2lf\n", maxVal);
        // Draw the bounding box around all A template matches
        if(maxVal >= threshold && matchLoc.x != 0 && matchLoc.y != 0)
        {
            rectangle( src, matchLoc, Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows ), Scalar(0, 0, 255), FILLED, 8, 0 );
            rectangle( result, matchLoc, Point( matchLoc.x + temp.cols , matchLoc.y + temp.rows ), Scalar::all(0), 2, 8, 0 );
        }
    }

    // TODO: Remote duplicate matching for same A instance
    // TODO: Determine how to remove the random match in top left

    // Color all the A's red in the original image
    cvtColor(dst, dst, COLOR_GRAY2BGR);
    addWeighted(src, 0.5, dst, 0.5, 0, dst);

    imshow( "Display", dst );
//    imshow( "Result", result );

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
