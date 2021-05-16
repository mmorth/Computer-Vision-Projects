
// Import libraries
#include <iostream>
#include "../resource/lib/public/includeLibraries.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include "../resource/lib/public/displayImages.h"

#include "../resource/lib/public/matplotlibcpp.h"

#include <cmath>

using namespace std;

using namespace cv;

using namespace matplotlibcpp;

// Implement Variance of absolute values of Laplacian - Method 1
// Input: image
// Output: Floating point number denoting the measure of sharpness of image

// Do NOT change the function name and definition

double var_abs_laplacian(Mat image){
    ///
    /// YOUR CODE HERE
    ///
    int kernelSize = 3;
    Mat roi = image.clone();
    cvtColor(roi, roi, COLOR_BGR2GRAY);
    Laplacian(roi, roi, CV_32F, kernelSize, 1, 0);
    roi = cv::abs(roi);
    Mat mean, stdDev;
    meanStdDev(roi, mean, stdDev);
    return sum(mean)[0];
}

// Implement Sum Modified Laplacian - Method 2
// Input: image
// Output: Floating point number denoting the measure of sharpness of image

// Do NOT change the function name and definition

double sum_modified_laplacian(Mat image){
    ///
    /// YOUR CODE HERE
    ///
    int step = 1;
    Mat roi = image.clone();
    cvtColor(roi, roi, COLOR_BGR2GRAY);
    roi.convertTo(roi, CV_32FC1, 1/255.0);
    for(int i=0; i<image.rows; i++) {
        for(int j=0; j<image.cols; j++) {
            roi.at<float>(i,j) = abs(2*roi.at<float>(i,j) - roi.at<float>(i-step,j) - roi.at<float>(i+step,j)) 
                                    + abs(2*roi.at<float>(i,j) - roi.at<float>(i,j-step) - roi.at<float>(i,j+step));
        }
    }
    
    return sum(roi)[0];
}

// Read input video filename
string filename = DATA_PATH + "videos/focus-test.mp4";

// Create a VideoCapture object
VideoCapture cap(filename);

// Read first frame from the video
Mat frame;
cap >> frame;

// Display total number of frames in the video
cout << "Total number of frames : " << (int)cap.get(CAP_PROP_FRAME_COUNT);

double maxV1 = 0;
double maxV2 = 0;

// Frame with maximum measure of focus
// Obtained using methods 1 and 2
Mat bestFrame1;
Mat bestFrame2;

// Frame ID of frame with maximum measure
// of focus
// Obtained using methods 1 and 2
int bestFrameId1 = 0;
int bestFrameId2 = 0;

// Get measures of focus from both methods
double val1 = var_abs_laplacian(frame);
double val2 = sum_modified_laplacian(frame);

// Specify the ROI for flower in the frame
// UPDATE THE VALUES BELOW
int topCorner = 50;
int leftCorner = 50;
int bottomCorner = 700;
int rightCorner = 1200;

Mat flower;
flower = frame(Range(topCorner,bottomCorner),Range(leftCorner,rightCorner));

// Iterate over all the frames present in the video
while (1){
    // Crop the flower region out of the frame
    flower = frame(Range(topCorner,bottomCorner),Range(leftCorner,rightCorner));
    // Get measures of focus from both methods
    val1 = var_abs_laplacian(flower);
    val2 = sum_modified_laplacian(flower);
    // If the current measure of focus is greater 
    // than the current maximum
    if (val1 > maxV1){
        // Revise the current maximum
        maxV1 = val1;
        // Get frame ID of the new best frame
        bestFrameId1 = (int)cap.get(CAP_PROP_POS_FRAMES);
        // Revise the new best frame
        bestFrame1 = frame.clone();
        cout << "Frame ID of the best frame [Method 1]: " << bestFrameId1 << endl;
    }
    // If the current measure of focus is greater 
    // than the current maximum
    if (val2 > maxV2){
        // Revise the current maximum
        maxV2 = val2;
        // Get frame ID of the new best frame
        bestFrameId2 = (int)cap.get(CAP_PROP_POS_FRAMES);
        // Revise the new best frame
        bestFrame2 = frame.clone();
        cout << "Frame ID of the best frame [Method 2]: " << bestFrameId2 << endl;
    }
    cap >> frame;
    if (frame.empty())
        break;
}

cout << "================================================" << endl;

// Print the Frame ID of the best frame
cout << "Frame ID of the best frame [Method 1]: " << bestFrameId1 << endl;
cout << "Frame ID of the best frame [Method 2]: " << bestFrameId2 << endl;

cap.release();

Mat out;
hconcat(bestFrame1, bestFrame2, out);

plt::figure_size(1200,500);
plt::imshow(out);
auto pltImg = displayImage(out);
pltImg

///
/// AUTOGRADER TEST - DO NOT REMOVE
///


///
/// AUTOGRADER TEST - DO NOT REMOVE
///

