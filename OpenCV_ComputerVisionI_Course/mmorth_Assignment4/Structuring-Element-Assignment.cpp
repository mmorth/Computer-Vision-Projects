
#include <iostream>

#include "../resource/lib/public/includeLibraries.h"
#include "../resource/lib/public/matplotlibcpp.h"
#include "../resource/lib/public/displayImages.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <time.h>

using namespace std;

using namespace cv;

using namespace matplotlibcpp;

Mat demoImage = Mat::zeros(Size(10,10),CV_8U);

cout << demoImage;

plt::figure();
plt::imshow(demoImage);
auto pltImg = displayImage(demoImage);

pltImg

demoImage.at<uchar>(0,1) = 1;

demoImage.at<uchar>(9,0) = 1;

demoImage.at<uchar>(8,9) = 1;

demoImage.at<uchar>(2,2) = 1;

demoImage(Range(5,8),Range(5,8)).setTo(1);

cout << demoImage;

plt::figure();
plt::imshow(demoImage*255);
pltImg = displayImage(demoImage*255);
pltImg

Mat element = getStructuringElement(MORPH_CROSS, Size(3,3));

cout << element;

plt::figure();
plt::imshow(element*255);
pltImg = displayImage(element*255);
pltImg

int ksize = element.size().height;

int height, width;
height = demoImage.size().height;
width  = demoImage.size().width;

Mat dilatedCrossKernel;
dilate(demoImage, dilatedCrossKernel, element);
cout << dilatedCrossKernel;

plt::figure();
plt::imshow(dilatedCrossKernel*255);
pltImg = displayImage(dilatedCrossKernel*255);
pltImg

int border = ksize/2;
Mat paddedDemoImage = Mat::zeros(Size(height + border*2, width + border*2),CV_8UC1);
copyMakeBorder(demoImage,paddedDemoImage,border,border,border,border,BORDER_CONSTANT);

Mat paddedDilatedImage = paddedDemoImage.clone();
Mat mask;
Mat resizedFrame;

double maxVal;

// Create a VideoWriter object
// Use frame size as 50x50
///
/// YOUR CODE HERE
///
VideoWriter out("dilationScratch.avi", VideoWriter::fourcc('M','J','P','G'), 10, Size(50, 50));

for (int h_i = border; h_i < height + border; h_i++){
    for (int w_i = border; w_i < width + border; w_i++){
        ///
        /// YOUR CODE HERE
        ///
        // Find and save 3x3 ROI around the pixel in question
        // Bitwise and the element with the surrounding 3x3 region
        // Use countNonZero. If greater than 0, set current to 1, otherwise, set to 0
        cout << "(" << h_i-1 << "->" << h_i+1 << ", " << w_i-1 << "->" << w_i+1 << ")" << endl;
        Mat roi = paddedDilatedImage(Range(h_i-1, h_i+2), Range(w_i-1, w_i+2)).clone();
        cout << roi << endl;
        bitwise_and(roi, element, roi);
        minMaxLoc(roi, 0, &maxVal, 0, 0);
        paddedDemoImage.at<uchar>(h_i, w_i) = maxVal;
        ///
        /// YOUR CODE HERE
        ///
        // Resize output to 50x50 before writing it to the video
        resizedFrame = paddedDemoImage(Range(border,border+height),Range(border,border+width)).clone();
        resizedFrame = resizedFrame * 255;
        resize(resizedFrame, resizedFrame, cv::Size(50, 50), 0, 0, INTER_NEAREST);
        ///
        /// YOUR CODE HERE
        ///
        // Convert resizedFrame to BGR before writing
        cvtColor(resizedFrame, resizedFrame, COLOR_GRAY2BGR);
        ///
        /// YOUR CODE HERE
        ///
        out.write(resizedFrame);
    }
}

// Release the VideoWriter object
///
/// YOUR CODE HERE
///
out.release();

// Display final image (cropped)
///
/// YOUR CODE HERE
///
Mat dilatedImage = paddedDemoImage(Range(border,border+height),Range(border,border+width));
plt::figure();
plt::imshow(dilatedImage*255);
pltImg = displayImage(dilatedImage*255);
pltImg

Mat ErodedCrossKernel;
erode(demoImage, ErodedCrossKernel, element);
cout << ErodedCrossKernel;

plt::figure();
plt::imshow(ErodedCrossKernel*255);
pltImg = displayImage(ErodedCrossKernel*255);
pltImg

border = ksize/2;
paddedDemoImage = Mat::zeros(Size(height + border*2, width + border*2),CV_8UC1);
copyMakeBorder(demoImage,paddedDemoImage,border,border,border,border,BORDER_CONSTANT,0);

Mat paddedErodedImage = paddedDemoImage.clone();

double minVal = 0;

// Create a VideoWriter object
// Use frame size as 50x50
///
/// YOUR CODE HERE
///
VideoWriter outErode("erosionScratch.avi", VideoWriter::fourcc('M','J','P','G'), 10, Size(50, 50));

for (int h_i = border; h_i < height + border; h_i++){
    for (int w_i = border; w_i < width + border; w_i++){
        ///
        /// YOUR CODE HERE
        ///
        // Find and save 3x3 ROI around the pixel in question
        // Bitwise and the element with the surrounding 3x3 region
        // Use countNonZero. If greater than 0, set current to 1, otherwise, set to 0
        cout << "(" << h_i-1 << "->" << h_i+1 << ", " << w_i-1 << "->" << w_i+1 << ")" << endl;
        Mat roi = paddedErodedImage(Range(h_i-1, h_i+2), Range(w_i-1, w_i+2)).clone();
        cout << roi << endl;
        bitwise_and(roi, element, roi);
        minMaxLoc(roi, &minVal, 0, 0, 0);
        paddedDemoImage.at<uchar>(h_i, w_i) = minVal;
        ///
        /// YOUR CODE HERE
        ///
        // Resize output to 50x50 before writing it to the video
        resizedFrame = paddedDemoImage(Range(border,border+height),Range(border,border+width)).clone();
        resizedFrame = resizedFrame * 255;
        resize(resizedFrame, resizedFrame, cv::Size(50, 50), 0, 0, INTER_NEAREST);
        ///
        /// YOUR CODE HERE
        ///
        // Convert resizedFrame to BGR before writing
        cvtColor(resizedFrame, resizedFrame, COLOR_GRAY2BGR);
        ///
        /// YOUR CODE HERE
        ///
        outErode.write(resizedFrame);
    }
}

// Release the VideoWriter object
///
/// YOUR CODE HERE
///
outErode.release();

// Display final image (cropped)
///
/// YOUR CODE HERE
///
Mat erodedImage = paddedDemoImage(Range(border,border+height),Range(border,border+width));
plt::figure();
plt::imshow(erodedImage*255);
pltImg = displayImage(erodedImage*255);
pltImg
