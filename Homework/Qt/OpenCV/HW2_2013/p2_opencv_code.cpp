//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include <iostream>

//using namespace cv;
//using namespace std;

//void processVerticalAndHorizontalProjections(Mat src);

//int main()
//{
//  // Read in the input image and create separate images for the handle and disk
//  Mat src1 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2013\\inputs\\p2\\2a.png", IMREAD_GRAYSCALE);
//  Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2013\\inputs\\p2\\2b.png", IMREAD_GRAYSCALE);

//  // Process the images
//  processVerticalAndHorizontalProjections(src1);
//  processVerticalAndHorizontalProjections(src2);

//  waitKey(0);
//  return 0;
//}

//void processVerticalAndHorizontalProjections(Mat src) {
//    // Apply the close operation to enclose disconnected objects
//    // Store a vector containing the four side pixel locations of the object
//    // Run find contours in the image (each contour represents an object in the row)
//    // For each contour, check if it is within a threshold of 50 pixels from the top dimension of the stored vectors
//        // If so, update the side information if the object is an extreme element
//        // If not, create a new entry for the object in the vector
//}
