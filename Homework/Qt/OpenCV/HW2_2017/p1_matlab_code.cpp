//#include <iostream>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgcodecs/imgcodecs.hpp>

//using namespace std;
//using namespace cv;

//int main()
//{
//  // Read in the input image and create separate images for the handle and disk
//  Mat src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2017\\input\\Part_1\\pendulum.jpg", IMREAD_GRAYSCALE);
//  Mat disk = src.clone();
//  Mat handle = src.clone();

//  // Threshold the image to make it easier to work with
//  threshold(src, src, 120, 255, THRESH_BINARY);

//  // Apply closing operation to isolate the disk
//  int dilation_size = 12;
//  Mat element = getStructuringElement( MORPH_ELLIPSE,
//                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
//                       Point( dilation_size, dilation_size ) );
//  morphologyEx( src, disk, MORPH_CLOSE, element );

//  // Manipulate the original image to generate the handle
//  bitwise_not(disk, disk);
//  bitwise_not(src, src);
//  handle = src - disk;

//  // Remove extra noise from subtraction
//  int erosion_size = 1;
//  element = getStructuringElement( MORPH_RECT,
//                     Size( 2*erosion_size + 1, 2*erosion_size+1 ),
//                     Point( erosion_size, erosion_size ) );
//  erode( handle, handle, element );
//  bitwise_not(handle, handle);
//  bitwise_not(disk, disk);

//  // Display final results
//  imshow("disk", disk);
//  imshow("handle", handle);

//  waitKey(0);
//  return 0;
//}
