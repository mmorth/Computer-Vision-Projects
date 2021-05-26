#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

using namespace std;
using namespace cv;

// This function removes the background from the document
Mat removeBackground(Mat document)
{
    Mat docGray, dst;
    cvtColor(document, docGray, COLOR_BGR2GRAY);
    threshold(docGray, dst, 200, 255, 0);
//    imshow("docGray", dst);
//    waitKey(0);
    return dst;
}

// This function finds the contours fo the binary image
vector<Point> findBinaryContours(Mat binaryImage)
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(binaryImage, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

    double area;
    vector<Point> corners;
    for (size_t i=0; i < contours.size(); i++){
        area = contourArea(contours[i]);

        if (area > 10000)
        {
            approxPolyDP(Mat(contours[i]), corners, 10, true);
            break;
        }
    }

    for (size_t i = 0; i < corners.size(); i++)
    {
        cout << corners.at(i) << endl;
    }

    return corners;
}

// This function performs a perspective transform to create a rectified document image of 500 pixels
Mat perspectiveTransform(Mat document, vector<Point> corners)
{
    // Create the resulting image and the homography Point2fs
    Mat result(647, 500, CV_8UC3, Scalar(0,0,0));
    vector<Point> cornersDst {Point(646, 0),Point(0, 0),Point(0, 499),Point(646, 499)};

    // Calculate Homography
    Mat h = findHomography(corners, cornersDst);

    // Warp source image to destination based on homography
    Mat scan;
    warpPerspective(document, scan, h, result.size());

    return scan;
}

int main()
{
    // Assumptions:
    // The document is light and the background is dark
    // The document is fully contained in the image
    // The document occupies a large portion of the image

    // Output:
    // Rectified image (front-facing) with a width of 500 pixels

    // Approach
    // Use grabcut to binarize the image (remove the background)
    // Use findContours to find the contours of the binary image
    // Use approxPolyDP to find the rectangle around the document
        // Need to use the known aspect ratio of the image

    // Read document image
    Mat document = imread("scanned-form.jpg");

    Mat binaryImage;
    binaryImage = removeBackground(document);

    vector<Point> corners = findBinaryContours(binaryImage);

    Mat scannedDocument = perspectiveTransform(document, corners);

    imshow("Scanned Document", scannedDocument);
    waitKey(0);
}
