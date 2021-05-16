
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
// I first chose the grayscale image because morphological operations operate on the grayscale image, and I thought it was the image with the largest difference between the background and the coins
// However, it was difficult to completely isolate the coins from the background without having dots in the middle of the coins, so I decided to go with the green channel since I was getting better results
// This was a great exercise to learn that sometimes the different color channels can result in better morphological operation results
// I started off with 100 then went to 50, then 25 then 20 resulted in the best trade off between getting the coins and having the background be separable
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
// I first started with a kernel size of 5 and then found that 7 resulted in slightly better results
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
// kernelSize = 2;

// // Create the kernel
// element = getStructuringElement(MORPH_ELLIPSE, Size(2*kernelSize+1, 2*kernelSize+1), Point(kernelSize, kernelSize));

// openImage = closeImage.clone();

///
/// YOUR CODE HERE
///
// morphologyEx(openImage, openImage, MORPH_OPEN, element);

// Display image using matplotlibcpp
// We have provided the sample code here
// Please modify it as required
// As seen in the closing and opening plots, the closing operation alone resulting in significantly better results compared to the opening operation
// This is not surprising since the closing operation removes smaller black dots from the image
// plt::figure();
// plt::imshow(openImage);
// pltImg = displayImage(openImage);
// pltImg

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
Mat labels;
Mat invCloseImage;
bitwise_not(closeImage, invCloseImage);
cout << "Number of Connected Components = " << connectedComponents(invCloseImage, labels) << endl;
Mat colorMap = displayConnectedComponents(labels);

// Display image using matplotlibcpp
// We have provided the sample code here
// Please modify it as required
// Yes we can use CCA to compute the number of coins where each blob roughly represents a coin in the image.
// We can see that similar to other methods, the specific number of coins detected may be off due to the blob computation.
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

findContours(closeImage, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE  );

// Print the number of contours found
///
/// YOUR CODE HERE
///
cout << "Number of contours found = " << contours.size()-1;
// The 11th coin is the little contour on the larger coin. This could be removed by checking whether the contour area is creater than a certain value
// This is done in the later parts of this problem

// Draw all contours
///
/// YOUR CODE HERE
///
Mat contourImg = image.clone();
drawContours(contourImg, contours, -1, Scalar(0,0,255), 6);
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
Mat outerContour = image.clone();
drawContours(outerContour, contours, -1, Scalar(0,0,255), 20);

plt::figure();
plt::imshow(outerContour);
pltImg = displayImage(outerContour);
pltImg

// Print area and perimeter of all contours
///
/// YOUR CODE HERE
///
findContours(closeImage, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE  );
int maxContourArea = -1;
int maxContourIndex = -1;
for (int i = 0; i < contours.size(); i++) {
    cout << "Countour #" << i+1 << " has area = " << contourArea(contours[i]) << " and perimeter = " << arcLength(contours[i], true) << endl;
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
cout << "Maximum area of contour = " << maxContourArea << " at contour #" << maxContourIndex+1 << endl;

// Remove this contour and plot others
///
/// YOUR CODE HERE
///
// We avoid printing the contour with largest area and the small false coin contour on the larger coin
Mat innerContours = image.clone();
for (int i = 0; i < contours.size(); i++) {
    if (i != maxContourIndex && i != 2) {
        std::vector<std::vector<cv::Point> > contourVec;
        contourVec.push_back(contours[i]);
        drawContours(innerContours, contourVec, -1, Scalar(0,0,255), 5);
    }
}
plt::figure();
plt::imshow(innerContours);
pltImg = displayImage(innerContours);
pltImg

// Fit circles on coins
///
/// YOUR CODE HERE
///
Mat coinCircles = image.clone();
Point2f centerCnt;
float radiusCnt;
for (size_t i=0; i < contours.size(); i++){
    if (i != 2 && i != maxContourIndex) {
        // Fit a circle
        minEnclosingCircle(contours[i],centerCnt,radiusCnt);
        circle(coinCircles,centerCnt,radiusCnt, Scalar(255,255,255), 5);
    }
}

cout << "Number of coins detected = " << contours.size()-2 << endl;

plt::figure();
plt::imshow(coinCircles);
pltImg = displayImage(coinCircles);
pltImg

// Image path
imagePath = DATA_PATH + "images/CoinsB.png";
// Read image
// Store it in variable image
///
/// YOUR CODE HERE
///
Mat image2 = imread(imagePath);
Mat imageCopy2 = image2.clone();

// Convert image to grayscale
// Store it in the variable imageGray
///
/// YOUR CODE HERE
///
Mat imageGray2;
cvtColor(image2, imageGray2, COLOR_BGR2GRAY);

// Display image
plt::figure();
plt::imshow(imageGray2);
pltImg = displayImage(imageGray2);
pltImg

// Split cell into channels
// Store them in variables imageB, imageG, imageR
///
/// YOUR CODE HERE
///
Mat imgChannels2[3];
split(image2, imgChannels2);
Mat imageB2 = imgChannels2[0];
Mat imageG2 = imgChannels2[1];
Mat imageR2 = imgChannels2[2];

Mat altImg2;

plt::figure_size(1100,200);
plt::subplot(1,3,1);
plt::imshow(imageB2);
pltImg = displayImage(imageB2);
plt::subplot(1,3,2);
plt::imshow(imageG2);
pltImg = displayImage(imageG2);
plt::subplot(1,3,3);
plt::imshow(imageR2);
pltImg = displayImage(imageR2)

///
/// YOUR CODE HERE
///
// I chose the blue color channel image because it had the largest contrast between the background and coins and all the coins had similar color and minimized erosion
altImg2 = imageB2.clone();
// TODO: Comments
threshold(altImg2, altImg2, 150, 255, THRESH_BINARY);

plt::figure();
plt::imshow(altImg2);
pltImg = displayImage(altImg2);
pltImg

///
/// YOUR CODE HERE
///
// Closing operation removes the black blob noise from the background
int kernelSize2 = 20;

// Create the kernel
Mat element2 = getStructuringElement(MORPH_ELLIPSE, Size(2*kernelSize2+1, 2*kernelSize2+1), Point(kernelSize2, kernelSize2));

Mat closeImage2 = altImg2.clone();

///
/// YOUR CODE HERE
///
morphologyEx(closeImage2, closeImage2, MORPH_CLOSE, element2);

///
/// YOUR CODE HERE
///
plt::figure();
plt::imshow(closeImage2);
pltImg = displayImage(closeImage2);
pltImg

///
/// YOUR CODE HERE
///
// Opening operation to close the center of the coin. Any kernel size greater than 60 begins to combine the coins, which is undesirable
kernelSize2 = 65;

// Create the kernel
element2 = getStructuringElement(MORPH_ELLIPSE, Size(2*kernelSize2+1, 2*kernelSize2+1), Point(kernelSize2, kernelSize2));

Mat openImage2 = closeImage2.clone();

///
/// YOUR CODE HERE
///
morphologyEx(openImage2, openImage2, MORPH_OPEN, element2);

///
/// YOUR CODE HERE
///
// We can see that the below image improves on the given image as it does not contain any extra black blobs from the background noise
plt::figure();
plt::imshow(openImage2);
pltImg = displayImage(openImage2);
pltImg

///
/// YOUR CODE HERE
///
// All experimentation was done using the closing and opening operations as any other morphological operation would change the shape charactersitic of the coins

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


///
/// YOUR CODE HERE
///

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
detector->detect(openImage2, keypoints);

// Print number of coins detected
///
/// YOUR CODE HERE
///
// We can detect all but 2 coins (the ones without the centers filled in)
cout << "Number of coins detected = " << keypoints.size() << endl;

// Mark coins using image annotation concepts we have studied so far
///
/// YOUR CODE HERE
///
Mat blobCoins2 = image2.clone();
for (int i=0; i < keypoints.size(); i++){
    KeyPoint k = keypoints[i];
    Point keyPt;
    keyPt = k.pt;
    x=(int)keyPt.x;
    y=(int)keyPt.y;
    // Mark center in BLACK
    circle(blobCoins2,Point(x,y),10,Scalar(255,0,0),-1);
    // Get radius of coin
    diameter = k.size;
    radius = (int)diameter/2.0;
    // Mark blob in GREEN
    circle(blobCoins2, Point(x,y),radius,Scalar(0,0,255),5);
}

///
/// YOUR CODE HERE
///
plt::figure();
plt::imshow(blobCoins2);
pltImg = displayImage(blobCoins2);
pltImg

// # Find connected components
///
/// YOUR CODE HERE
///
// Yes we can use CCA to compute the number of coins. However, the number of detected coins may be over estimated based on any smaller dots or remaining background noise
Mat invOpenImage2;
bitwise_not(openImage2, invOpenImage2);
cout << "Number of Connected Components = " << connectedComponents(invOpenImage2, labels) << endl;
Mat colorMap2 = displayConnectedComponents(labels);

///
/// YOUR CODE HERE
///
plt::figure();
plt::imshow(colorMap2);
pltImg = displayImage(colorMap2);
pltImg

// Find all contours in the image
///
/// YOUR CODE HERE
///
findContours(openImage2, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

// Print the number of contours found
///
/// YOUR CODE HERE
///
cout << "Number of contours found = " << contours.size();

// Draw all contours
///
/// YOUR CODE HERE
///
// All coin contours + outer border + 2 inner coin contours
Mat contourImg2 = image2.clone();
drawContours(contourImg2, contours, -1, Scalar(0,0,255), 6);
plt::figure();
plt::imshow(contourImg2);
pltImg = displayImage(contourImg2);
pltImg

// Remove the inner contours
// Display the result
///
/// YOUR CODE HERE
///
findContours(openImage2, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
cout << "Number of contours found = " << contours.size();
Mat outerContour2 = image2.clone();
drawContours(outerContour2, contours, -1, Scalar(0,0,255), 100);

plt::figure();
plt::imshow(outerContour2);
pltImg = displayImage(outerContour2);
pltImg

// Print area and perimeter of all contours
///
/// YOUR CODE HERE
///
findContours(openImage2, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE  );
maxContourArea = -1;
maxContourIndex = -1;
for (int i = 0; i < contours.size(); i++) {
    cout << "Countour #" << i+1 << " has area = " << contourArea(contours[i]) << " and perimeter = " << arcLength(contours[i], true) << endl;
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
Mat innerContours2 = image2.clone();
for (int i = 0; i < contours.size(); i++) {
    if (i != maxContourIndex) {
        std::vector<std::vector<cv::Point> > contourVec;
        contourVec.push_back(contours[i]);
        drawContours(innerContours2, contourVec, -1, Scalar(0,0,255), 10);
    }
}
plt::figure();
plt::imshow(innerContours2);
pltImg = displayImage(innerContours2);
pltImg

// Print area and perimeter of all contours
///
/// YOUR CODE HERE
///
findContours(openImage2, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE  );
maxContourArea = -1;
maxContourIndex = -1;
for (int i = 0; i < contours.size(); i++) {
    cout << "Countour #" << i+1 << " has area = " << contourArea(contours[i]) << " and perimeter = " << arcLength(contours[i], true) << endl;
    if (contourArea(contours[i])) {
        maxContourArea = contourArea(contours[i]);
        maxContourIndex = i;
    }
}

// Remove contours
///
/// YOUR CODE HERE
///
Mat coinContours2 = image2.clone();
for (int i = 0; i < contours.size(); i++) {
    if (i != maxContourIndex && i != 5 && i != 6) {
        std::vector<std::vector<cv::Point> > contourVec;
        contourVec.push_back(contours[i]);
        drawContours(coinContours2, contourVec, -1, Scalar(0,0,255), 10);
    }
}

// Draw revised contours
///
/// YOUR CODE HERE
///
plt::figure();
plt::imshow(coinContours2);
pltImg = displayImage(coinContours2);
pltImg

// Fit circles on coins
///
/// YOUR CODE HERE
///
Mat coinCircles2 = image2.clone();
Point2f center2;
float radius2;
for (size_t i=0; i < contours.size(); i++){
    if (i != maxContourIndex && i != 5 && i != 6) {
        // Fit a circle
        minEnclosingCircle(contours[i],center2,radius2);
        circle(coinCircles2,center2,radius2, Scalar(255,255,255), 5);
    }
}

plt::figure();
plt::imshow(coinCircles2);
pltImg = displayImage(coinCircles2);
pltImg


