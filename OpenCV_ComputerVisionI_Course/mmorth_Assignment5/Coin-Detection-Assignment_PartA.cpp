
#include <iostream>

#include "../resource/lib/public/includeLibraries.h"

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "../resource/lib/public/matplotlibcpp.h"
#include "../resource/lib/public/displayImages.h"

using namespace std;

using namespace cv;

using namespace matplotlibcpp;

// Image path
string imagePath = DATA_PATH + "images/CoinsA.png";
// Read image
// Store it in the variable image
///
/// YOUR CODE HERE
///
Mat image = imread(imagePath);
Mat imageCopy = image.clone();

plt::figure();
plt::imshow(image);
auto pltImg = displayImage(image);

pltImg

// Convert image to grayscale
// Store it in the variable imageGray
///
/// YOUR CODE HERE
///
Mat imageGray;
cvtColor(image, imageGray, COLOR_BGR2GRAY);

plt::figure();
plt::imshow(imageGray);
pltImg = displayImage(imageGray);
pltImg

// Split cell into channels
// Store them in variables imageB, imageG, imageR
///
/// YOUR CODE HERE
///
Mat imgChannels[3];
split(image, imgChannels);
Mat imageB = imgChannels[0];
Mat imageG = imgChannels[1];
Mat imageR = imgChannels[2];

Mat altImg;

plt::figure_size(900,200);
plt::subplot(1,3,1);
plt::imshow(imageB);
pltImg = displayImage(imageB);
plt::subplot(1,3,2);
plt::imshow(imageG);
pltImg = displayImage(imageG);
plt::subplot(1,3,3);
plt::imshow(imageR);
pltImg = displayImage(imageR)

///
/// YOUR CODE HERE
///
altImg = imageG.clone();
// I chose the grayscale image because morphological operations operate on the grayscale image, and it was the image with the largest difference between the background and the coins
// I started off with 100 then went to 50, 60, 65 and found that 60 resulted in the best trade off between getting the coins and having the background be separable
threshold(altImg, altImg, 20, 255, THRESH_BINARY_INV);

// Display image using matplotlibcpp
// We have provided the sample code here
// Please modify it as required
plt::figure();
plt::imshow(altImg);
pltImg = displayImage(altImg);
pltImg

///
/// YOUR CODE HERE
///
int kernelSize = 7;

// Create the kernel
Mat element = getStructuringElement(MORPH_ELLIPSE, Size(2*kernelSize+1, 2*kernelSize+1), Point(kernelSize, kernelSize));

Mat closeImage = altImg.clone();

///
/// YOUR CODE HERE
///
morphologyEx(closeImage, closeImage, MORPH_CLOSE, element);

// Display image using matplotlibcpp
// We have provided the sample code here
// Please modify it as required
plt::figure();
plt::imshow(closeImage);
pltImg = displayImage(closeImage);
pltImg

// Get structuring element/kernel which will be used for dilation
///
/// YOUR CODE HERE
///
// Note: The below experiement was not used in the final result
kernelSize = 2;

// Create the kernel
element = getStructuringElement(MORPH_ELLIPSE, Size(2*kernelSize+1, 2*kernelSize+1), Point(kernelSize, kernelSize));

openImage = closeImage.clone();

///
/// YOUR CODE HERE
///
morphologyEx(openImage, openImage, MORPH_OPEN, element);

// Display image using matplotlibcpp
// We have provided the sample code here
// Please modify it as required
plt::figure();
plt::imshow(openImage);
pltImg = displayImage(openImage);
pltImg

// Setup SimpleBlobDetector parameters.
SimpleBlobDetector::Params params;
// params;

params.blobColor = 0;

params.minDistBetweenBlobs = 2;

// Filter by Area
params.filterByArea = false;

// Filter by Circularity
params.filterByCircularity = true;
params.minCircularity = 0.8;

// Filter by Convexity
params.filterByConvexity = true;
params.minConvexity = 0.8;

// Filter by Inertia
params.filterByInertia = true;
params.minInertiaRatio = 0.8;

// Set up detector with params
Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);
// detector = SimpleBlobDetector::create(params);

// Detect blobs
///
/// YOUR CODE HERE
///
std::vector<KeyPoint> keypoints;
detector->detect(closeImage, keypoints);

// Print number of coins detected
///
/// YOUR CODE HERE
///
cout << "Number of coins detected = " << keypoints.size() << endl;

// Mark coins using image annotation concepts we have studied so far
int x,y;
int radius;
double diameter;
///
/// YOUR CODE HERE
///
Mat blobCoins = image.clone();
for (int i=0; i < keypoints.size(); i++){
    KeyPoint k = keypoints[i];
    Point keyPt;
    keyPt = k.pt;
    x=(int)keyPt.x;
    y=(int)keyPt.y;
    // Mark center in BLACK
    circle(blobCoins,Point(x,y),5,Scalar(255,0,0),-1);
    // Get radius of coin
    diameter = k.size;
    radius = (int)diameter/2.0;
    // Mark blob in GREEN
    circle(blobCoins, Point(x,y),radius,Scalar(0,255,0),2);
}

// Display image using matplotlibcpp
// We have provided the sample code here
// Please modify it as required
plt::figure();
plt::imshow(blobCoins);
pltImg = displayImage(blobCoins);
pltImg

Mat displayConnectedComponents(Mat &im)
{
 // Make a copy of the image
 Mat imLabels = im.clone();

 // First let's find the min and max values in imLabels
 Point minLoc, maxLoc;
 double min, max;

 // The following line finds the min and max pixel values
 // and their locations in an image.
 minMaxLoc(imLabels, &min, &max, &minLoc, &maxLoc);
 
 // Normalize the image so the min value is 0 and max value is 255.
 imLabels = 255 * (imLabels - min) / (max - min);
 
 // Convert image to 8-bits
 imLabels.convertTo(imLabels, CV_8U);
 
 // Apply a color map
 Mat imColorMap;
 applyColorMap(imLabels, imColorMap, COLORMAP_JET);

 return imColorMap;
}

// Find connected components
// Use displayConnectedComponents function provided above
///
/// YOUR CODE HERE
///
Mat colorMap = displayConnectedComponents(closeImage);

// Display image using matplotlibcpp
// We have provided the sample code here
// Please modify it as required
plt::figure();
plt::imshow(colorMap);
pltImg = displayImage(colorMap);
pltImg

// Find all contours in the image
///
/// YOUR CODE HERE
///
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

findContours(closeImage, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

// Print the number of contours found
///
/// YOUR CODE HERE
///
cout << "Number of contours found = " << contours.size();

// Draw all contours
///
/// YOUR CODE HERE
///
Mat contourImg = image.clone();
drawContours(image, contours, -1, Scalar(0,0,255), 6);
plt::figure();
plt::imshow(contourImg);
pltImg = displayImage(contourImg);
pltImg

// Remove the inner contours
// Display the result
///
/// YOUR CODE HERE
///
findContours(closeImage, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
cout << "Number of contours found = " << contours.size();
Mat outerContour;
drawContours(outerContour, contours, -1, Scalar(0,0,255), 20);

plt::figure();
plt::imshow(outerContour);
pltImg = displayImage(outerContour);
pltImg

// Print area and perimeter of all contours
///
/// YOUR CODE HERE
///
int maxContourArea = -1;
int maxContourIndex = -1;
for (int i = 0; i < contours.size(); i++) {
    cout << "Countour #" << i+1 << " has area = " << contourArea(contours[i]) << " and perimeter = " << arcLength(contours[i], true);
    if (contourArea(contours[i])) {
        maxContourArea = contourArea(contours[i]);
        maxContourIndex = i;
    }
}

// Print maximum area of contour
// This will be the box that we want to remove
///
/// YOUR CODE HERE
///
cout << "Maximum area of contour = " << maxContourArea << endl;

// Remove this contour and plot others
///
/// YOUR CODE HERE
///
Mat innerContours;
contours.remove(maxContourIndex);
drawContours(innerContour, contours, -1, Scalar(0,0,255), 20);
plt::figure();
plt::imshow(innerContour);
pltImg = displayImage(innerContour);
pltImg

// Fit circles on coins
///
/// YOUR CODE HERE
///
drawContours(innerContour, contours, 1, Scalar(0,0,255), 20);

cout << "Number of coins detected = " << contours.size() << endl;

plt::figure();
plt::imshow(image);
pltImg = displayImage(image);
pltImg

// Image path
imagePath = DATA_PATH + "images/CoinsB.png";
// Read image
// Store it in variable image
///
/// YOUR CODE HERE
///
Mat image = imread(DATA_PATH)
imageCopy = image.clone();

// Convert image to grayscale
// Store it in the variable imageGray
///
/// YOUR CODE HERE
///
Mat imageGray;
cvtColor(image, imageGray, COLOR_BGR2GRAY);

// Display image
plt::figure();
plt::imshow(imageGray);
pltImg = displayImage(imageGray);
pltImg

// Split cell into channels
// Store them in variables imageB, imageG, imageR
///
/// YOUR CODE HERE
///
Mat imgChannels[3];
split(image, imgChannels);
Mat imageB = imgChannels[0];
Mat imageG = imgChannels[1];
Mat imageR = imgChannels[2];

Mat altImg;

plt::figure_size(1100,200);
plt::subplot(1,3,1);
plt::imshow(imageB);
pltImg = displayImage(imageB);
plt::subplot(1,3,2);
plt::imshow(imageG);
pltImg = displayImage(imageG);
plt::subplot(1,3,3);
plt::imshow(imageR);
pltImg = displayImage(imageR)

///
/// YOUR CODE HERE
///


plt::figure();
plt::imshow(dst);
pltImg = displayImage(dst);
pltImg

///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///
pltImg

///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///
pltImg

///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///
pltImg

///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///
pltImg

///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///
pltImg

///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///
pltImg

// Setup SimpleBlobDetector parameters.

params.blobColor = 0;

params.minDistBetweenBlobs = 2;

// Filter by Area
params.filterByArea = false;

// Filter by Circularity
params.filterByCircularity = true;
params.minCircularity = 0.8;

// Filter by Convexity
params.filterByConvexity = true;
params.minConvexity = 0.8;

// Filter by Inertia
params.filterByInertia = true;
params.minInertiaRatio = 0.8;

// Set up detector with params
detector = SimpleBlobDetector::create(params);

// Detect blobs
///
/// YOUR CODE HERE
///


// Print number of coins detected
///
/// YOUR CODE HERE
///


// Mark coins using image annotation concepts we have studied so far
///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///
pltImg

// # Find connected components
///
/// YOUR CODE HERE
///


///
/// YOUR CODE HERE
///
pltImg

// Find all contours in the image
///
/// YOUR CODE HERE
///


// Print the number of contours found
///
/// YOUR CODE HERE
///


// Draw all contours
///
/// YOUR CODE HERE
///
pltImg

// Remove the inner contours
// Display the result
///
/// YOUR CODE HERE
///


plt::figure();
plt::imshow(image);
pltImg = displayImage(image);
pltImg

// Print area and perimeter of all contours
///
/// YOUR CODE HERE
///


// Print maximum area of contour
// This will be the box that we want to remove
///
/// YOUR CODE HERE
///


// Remove this contour and plot others
///
/// YOUR CODE HERE
///
pltImg

// Print area and perimeter of all contours
///
/// YOUR CODE HERE
///


// Remove contours
///
/// YOUR CODE HERE
///


// Draw revised contours
///
/// YOUR CODE HERE
///
pltImg

// Fit circles on coins
///
/// YOUR CODE HERE
///


plt::figure();
plt::imshow(image);
pltImg = displayImage(image);
pltImg


