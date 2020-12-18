//#include "opencv2/imgproc.hpp"
//#include "opencv2/highgui.hpp"
//#include <iostream>
//using namespace cv;
//using namespace std;
//Mat src, erosion_dst, dilation_dst;
//int erosion_elem = 0;
//int erosion_height = 0;
//int erosion_width = 0;
//int dilation_elem = 0;
//int dilation_height = 0;
//int dilation_width = 0;
//int const max_elem = 2;
//int const max_kernel_size = 100;
//void Erosion( int, void* );
//void Dilation( int, void* );

//void process1A(Mat src);
//void process1B(Mat src);

//int main( int argc, char** argv )
//{
//  // Read in the input image and create separate images for the handle and disk
//  src = imread("C:\\Users\\mmort\\GIT\\CprE575\\Final Project\\Images\\personOutline.png", IMREAD_GRAYSCALE);
//  medianBlur(src, src, 11);
////  Mat src2 = imread("C:\\Users\\mmort\\GIT\\CprE575\\Homework\\Homework2\\HW2_2013\\inputs\\p2\\2b.png", IMREAD_GRAYSCALE);

//  namedWindow( "Erosion Demo", WINDOW_AUTOSIZE );
//  namedWindow( "Dilation Demo", WINDOW_AUTOSIZE );
//  moveWindow( "Dilation Demo", src.cols, 0 );
//  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
//          &erosion_elem, max_elem,
//          Erosion );
//  createTrackbar( "Erosion height:\n 2n +1", "Erosion Demo",
//          &erosion_height, max_kernel_size,
//          Erosion );
//  createTrackbar( "Erosion width:\n 2n +1", "Erosion Demo",
//          &erosion_width, max_kernel_size,
//          Erosion );
//  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
//          &dilation_elem, max_elem,
//          Dilation );
//  createTrackbar( "Erosion height:\n 2n +1", "Dilation Demo",
//          &dilation_height, max_kernel_size,
//          Dilation );
//  createTrackbar( "Erosion width:\n 2n +1", "Dilation Demo",
//          &dilation_width, max_kernel_size,
//          Dilation );
//  Erosion( 0, 0 );
//  Dilation( 0, 0 );
//  waitKey(0);
//  return 0;
//}

//void Erosion( int, void* )
//{
//  int erosion_type = 0;
//  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
//  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
//  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
//  Mat element = getStructuringElement( erosion_type,
//                       Size( 2*erosion_width + 1, 2*erosion_height+1 ),
//                       Point( erosion_width, erosion_height ) );
////  erode( src, erosion_dst, element );
//  morphologyEx( src, erosion_dst, MORPH_OPEN, element );
//  imshow( "Erosion Demo", erosion_dst );
//}
//void Dilation( int, void* )
//{
//  int dilation_type = 0;
//  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
//  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
//  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }
//  Mat element = getStructuringElement( dilation_type,
//                       Size( 2*dilation_width + 1, 2*dilation_height+1 ),
//                       Point( dilation_width, dilation_height ) );
////  dilate( src, dilation_dst, element );
//  morphologyEx( src, dilation_dst, MORPH_CLOSE, element );
//  imshow( "Dilation Demo", dilation_dst );
//}
