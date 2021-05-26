//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//// This function removes the background from the document
//// Assumption: The document is light and the background is dark
//Mat removeBackground(Mat document)
//{
//    // Threshold to remove most of the background from the image
//    Mat docGray, dst;
//    cvtColor(document, docGray, COLOR_BGR2GRAY);
//    threshold(docGray, dst, 200, 255, 0);
//    return dst;
//}

//// This function finds the contours fo the binary image
//// Assumption: The document is fully contained in the image
//vector<Point> findBinaryContours(Mat binaryImage)
//{
//    vector<vector<Point> > contours;
//    vector<Vec4i> hierarchy;

//    // Find contours of image (other smaller background components are present)
//    findContours(binaryImage, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

//    double area;
//    vector<Point> corners;
//    for (size_t i=0; i < contours.size(); i++){
//        // Only the largest contour area corresponds to the document
//        // Assumption: The document occupies a large portion of the image
//        area = contourArea(contours[i]);

//        if (area > 10000)
//        {
//            // Process only the document (10 is used for epsilon to return the 4 corners of the document)
//            approxPolyDP(Mat(contours[i]), corners, 10, true);
//            break;
//        }
//    }

//    return corners;
//}

//// This function performs a perspective transform to create a rectified document image of 500 pixels
//Mat perspectiveTransform(Mat document, vector<Point> corners)
//{
//    // Create the resulting image and the homography Points (assumption aspect ratio is standard letter)
//    Mat result(647, 500, CV_8UC3, Scalar(0,0,0));
//    vector<Point> cornersDst {Point(499, 0),Point(0, 0),Point(0, 646),Point(499, 646)};

//    // Calculate Homography
//    Mat h = findHomography(corners, cornersDst);

//    // Warp source image to destination based on homography
//    Mat scan;
//    warpPerspective(document, scan, h, result.size());

//    // Return scanned document
//    return scan;
//}

//int main()
//{
//    // Read document image
//    Mat document = imread("scanned-form.jpg");

//    Mat binaryImage;
//    binaryImage = removeBackground(document);

//    vector<Point> corners = findBinaryContours(binaryImage);

//    Mat scannedDocument = perspectiveTransform(document, corners);

//    imshow("Input Image", document);
//    // Rectified image (front-facing) with a width of 500 pixels
//    imwrite("rectified-form.jpg", scannedDocument);
//    imshow("Scanned Document", scannedDocument);

//    waitKey(0);
//}
